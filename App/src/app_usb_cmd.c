/*******************************************************************************
  USB command file handler + ACK writer
  (boot counter increments ONLY on "power on" via explicit call)

  WHAT CHANGED (2025-09-25):
  - Removed unused build_SN_digits() to fix -Werror=unused-function.
  - Boot counter increments only when calling APP_USB_CMD_OnPowerOnIncrement().

  Command file (/mnt/myDrive1/584_CMD.TXT), any order:
    - "SN:584dddd"    -> saves last 4 digits of serial to EEPROM
    - "VOLTAGE=HIGH"  -> saves voltage setting (HIGH/LOW/1/0) to EEPROM
    - "BOOT"          -> prints *current* 16-bit boot counter in ACK (NO INC here)
    - "FW"            -> no change, just ensures values are echoed in ACK

  Always writes 584_ACK.RTF with FW/SN/VOLTAGE. BOOT COUNTER appears only
  if "BOOT" is present in the command file. If VOLTAGE changed, we reboot
  AFTER ACK is closed.
*******************************************************************************/

#include "app_usb_cmd.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include "app.h"
#include "user.h"                       // APP_SystemReset()
#include "voltageSetting.h"             // voltage setting helpers
#include "config/default/definitions.h" // SYS_FS_* APIs
#include "ui_globals.h"                 // firmware[], serialNumber[]

// ====== External EEPROM helpers ======
extern void getSNFromEEProm(void);
extern void saveSNToEEProm(void);
extern bool incBootCounterInEEProm(uint16_t *newVal);
extern bool getBootCounterFromEEProm(uint16_t *out);

// ====== Paths ======
#define CMD_PATH    "/mnt/myDrive1/584_CMD.TXT"
#define ACK_PATH    "/mnt/myDrive1/584_ACK.RTF"

// ====== App data & global buffers (to match your existing layout) ======
APP1_DATA app1Data USB_ALIGN;

USB_ALIGN char writeData[512] = "";
USB_ALIGN char readData[512];
uint16_t    bytesRead = 0;
char CMD[20]   = "";
char VALUE[64] = "";
char FW[20]    = firmwareVersion;          // mirrored from ui_globals.firmware at runtime
char SN[20]    = "5840000";       // updated from EEPROM / parsed command
char VS[20]    = "HIGH";
char lines[10][128];

uint8_t I = 0;
uint8_t numberOfCommands = 0;
char voltageSetting = 0;          // legacy; not used directly but preserved

// ====== Local flags ======
static bool s_rebootPending = false;
static bool s_bootReported  = false;    // print boot counter in ACK if true
uint16_t s_bootValue = 0;        // value printed to ACK when s_bootReported

// Track per-MCU-session "this ON cycle increment done"
static bool s_incDoneThisOnCycle = false;

// ====== Utilities ======
static void rtrim_inplace(char *s)
{
    if (!s) return;
    size_t n = strlen(s);
    while (n && (s[n-1] == '\r' || s[n-1] == '\n' || isspace((unsigned char)s[n-1])))
        s[--n] = 0;
}
static char* lskip_ws(char *s)
{
    while (s && *s && isspace((unsigned char)*s)) ++s;
    return s;
}
static void parse_kv(char *line, char **outKey, char **outVal)
{
    *outKey = *outVal = NULL;
    if (!line) return;

    char *p = lskip_ws(line);
    if (*p == '#' || *p == ';' || *p == 0) return;

    char *key = p;
    while (*p && *p != ':' && *p != '=' && !isspace((unsigned char)*p)) ++p;
    if (*p) { *p++ = 0; }
    p = lskip_ws(p);

    if (*key == 0) return;
    *outKey = key;
    *outVal = p && *p ? p : (char*)"";
}

//// Update ui string "serialNumber" robustly (no truncation warnings)
//// Also updates SN[] ("584dddd") used in ACK content.
//static void update_ui_serial(void)
//{
//    char d0 = '0' + appData.snThousands;
//    char d1 = '0' + appData.snHundreds;
//    char d2 = '0' + appData.snTens;
//    char d3 = '0' + appData.snSingles;
//
//    // Update SN buffer (used for ACK)
//    snprintf(SN, sizeof(SN), "584%c%c%c%c", d0,d1,d2,d3);
//
//    // serialNumber[] may be small (often 11). Prefer "SN:584dddd" (10 chars + NUL)
//    size_t cap = sizeof(serialNumber);
//    if (cap >= 11u) {
//        // no spaces to conserve room
//        snprintf(serialNumber, cap, "SN:%c%c%c%c%c%c%c", '5','8','4', d0,d1,d2,d3);
//    } else if (cap > 0u) {
//        // fallback: just the digits
//        snprintf(serialNumber, cap, "%c%c%c%c%c%c%c", '5','8','4', d0,d1,d2,d3);
//    }
//}

// Accepts arbitrary prefix; uses the LAST four digits in the string.
//static bool handle_SN_command(const char* val)
//{
//    if (!val) return false;
//    const char* p = val;
//    while (*p==' ' || *p=='\t') ++p;
//    size_t n = strlen(p);
//    if (n < 4) return false;
//
//    const char* q = p + n - 4; // last 4 chars must be digits
//    for (int i=0;i<4;i++) {
//        if (q[i] < '0' || q[i] > '9') return false;
//    }
//    appData.snThousands = (uint8_t)(q[0] - '0');
//    appData.snHundreds  = (uint8_t)(q[1] - '0');
//    appData.snTens      = (uint8_t)(q[2] - '0');
//    appData.snSingles   = (uint8_t)(q[3] - '0');
//
//    saveSNToEEProm();          // your implementation returns void
//    update_ui_serial();        // keep UI in sync
//    return true;
//}

// Preload current values so ACK is meaningful even if file only contains "FW"
static void preload_values_for_ack(void)
{
    // FW: mirror from ui_globals so ACK stays in sync with UI
   // snprintf(FW, sizeof(FW), "%s", firmware);

    // SN from EEPROM -> appData -> SN[]/serialNumber[]
   // getSNFromEEProm();
    //update_ui_serial();

    // Voltage setting -> VS[]
    voltage_setting_t cur;
    if (!EEPROM_LoadVoltageSetting(&cur)) cur = VoltageSetting_Default();
    snprintf(VS, sizeof(VS), "%s", VoltageSetting_ToString(cur));
}

static void wrtAckFile (void)
{
    char tempStr[64] = "";

    strcpy(writeData,"");
    strcat(writeData, "****************************************\r\n");
    strcat(writeData, "****      THE GRYPHON HELIOS       *****\r\n");
    strcat(writeData, "****************************************\r\n");

    // Use FW (mirrored from firmware[] at preload)
    sprintf(tempStr,"\r\nFIRMWARE VERSION: %s\r\n", FW);
    strcat(writeData, tempStr);

//    sprintf(tempStr, "SERIAL NUMBER: %s\r\n", SN);
//    strcat(writeData,tempStr);

    sprintf(tempStr,"VOLTAGE SETTING: %s\r\n", VS);
    strcat(writeData, tempStr);

    if (s_bootReported) {
        sprintf(tempStr,"BOOT COUNTER: %u\r\n", (unsigned)s_bootValue);
        strcat(writeData, tempStr);
    }

    if (s_rebootPending) {
        strcat(writeData, "ACTION: Rebooting to apply voltage setting\r\n");
    }
}

/* ---- Public helpers to control boot counter policy ---- */
void APP_USB_CMD_OnPowerOnIncrement(void)
{
    if (s_incDoneThisOnCycle)
        return;

    (void)incBootCounterInEEProm(NULL);
    s_incDoneThisOnCycle = true;
}

void APP_USB_CMD_OnPowerOffClear(void)
{
    s_incDoneThisOnCycle = false;
}

/* ---- Harmony init + event handlers ---- */
void APP_USB_CMD_Initialize ( void )
{
    app1Data.state1 = APP1_STATE_BUS_ENABLE;
    app1Data.deviceIsConnected = false;
    s_rebootPending = false;
    s_bootReported  = false;
    s_bootValue     = 0;
    // NOTE: No EEPROM access here to avoid "too-early I2C" issues.

    DEBUG_PRINT("app usb cmd init\r\n");
    // Touch legacy globals to avoid -Wunused-variable with -Werror
    snprintf(CMD, sizeof(CMD), "INIT");
    snprintf(VALUE, sizeof(VALUE), "0");
}

USB_HOST_EVENT_RESPONSE APP_USBHostEventHandler (USB_HOST_EVENT event, void * eventData, uintptr_t context)
{
    switch (event)
    {
        case USB_HOST_EVENT_DEVICE_UNSUPPORTED:
            break;
        default:
            break;
    }
    return USB_HOST_EVENT_RESPONSE_NONE;
}

void APP_SYSFSEventHandler(SYS_FS_EVENT event, void * eventData, uintptr_t context)
{
    switch(event)
    {
        case SYS_FS_EVENT_MOUNT:
            app1Data.deviceIsConnected = true;
            break;

        case SYS_FS_EVENT_UNMOUNT:
            app1Data.deviceIsConnected = false;
            LED1_Off();
            break;

        default:
            break;
    }
}

/* ---- Main state machine ---- */
void APP_USB_CMD_Tasks ( void )
{
    switch(app1Data.state1)
    {
        case APP1_STATE_BUS_ENABLE:
            SYS_FS_EventHandlerSet((void *)APP_SYSFSEventHandler, (uintptr_t)NULL);
            USB_HOST_EventHandlerSet(APP_USBHostEventHandler, 0);
            USB_HOST_BusEnable(USB_HOST_BUS_ALL);
            app1Data.state1 = APP1_STATE_WAIT_FOR_BUS_ENABLE_COMPLETE;
            break;

        case APP1_STATE_WAIT_FOR_BUS_ENABLE_COMPLETE:
            if(USB_HOST_BusIsEnabled(USB_HOST_BUS_ALL))
            {
                app1Data.state1 = APP1_STATE_WAIT_FOR_DEVICE_ATTACH;
            }
            break;

        case APP1_STATE_WAIT_FOR_DEVICE_ATTACH:
            if(app1Data.deviceIsConnected)
            {
                app1Data.state1 = APP1_STATE_DEVICE_CONNECTED;
            }
            break;

        case APP1_STATE_DEVICE_CONNECTED:
            app1Data.state1 = APP1_STATE_OPEN_FILE;
            break;

        case APP1_STATE_OPEN_FILE:
            app1Data.fileHandle = SYS_FS_FileOpen(CMD_PATH, SYS_FS_FILE_OPEN_READ);
            if(app1Data.fileHandle == SYS_FS_HANDLE_INVALID )
            {
                app1Data.state1 = APP1_STATE_ERROR;
            }
            else
            {
                app1Data.state1 = APP1_STATE_READ_FILE;
            }
            break;

        case APP1_STATE_READ_FILE:
        {
            app1Data.nBytesRead = SYS_FS_FileRead(app1Data.fileHandle, app1Data.data, sizeof(app1Data.data)-1);
            if(app1Data.nBytesRead > 0)
            {
                // Terminate & mirror into readData/bytesRead (to avoid -Wunused warnings)
                app1Data.data[ (app1Data.nBytesRead < (sizeof(app1Data.data)-1)) ? app1Data.nBytesRead : (sizeof(app1Data.data)-1) ] = 0;
                bytesRead = (uint16_t)app1Data.nBytesRead;
                size_t copyN = (bytesRead < sizeof(readData)-1) ? bytesRead : (sizeof(readData)-1);
                memcpy(readData, app1Data.data, copyN);
                readData[copyN] = 0;

                // Preload current values so ACK is always meaningful
                preload_values_for_ack();

                /* split til linjer */
                char *p = strtok(app1Data.data, "\r\n");
                if (p) { snprintf(lines[0], sizeof(lines[0]), "%s", p); }
                I = 0;
                while(p != NULL && I < (uint8_t)(sizeof(lines)/sizeof(lines[0]) - 1))
                {
                    I++;
                    p = strtok(NULL, "\r\n");
                    if(p != NULL)
                    {
                        snprintf(lines[I], sizeof(lines[I]), "%s", p);
                    }
                }
                numberOfCommands = I;

                bool anyChange   = false;
                bool seenVolt    = false;

                for (I=0; I<numberOfCommands; I++)
                {
                    char *line = lines[I];
                    rtrim_inplace(line);

                    char *key=NULL, *val=NULL;
                    parse_kv(line, &key, &val);
                    if (!key) continue;

//                    /* SN:584xxxx */
//                    if (strcmp(key, "SN") == 0) {
//                        (void)handle_SN_command(val);
//                        continue;
//                    }

                    /* VOLTAGE (HIGH/LOW/1/0) */
                    if (strcmp(key, "VOLTAGE") == 0 || strcmp(key, "VOLT") == 0) {
                        seenVolt = true;
                        voltage_setting_t cur, want;
                        if (!EEPROM_LoadVoltageSetting(&cur)) cur = VoltageSetting_Default();

                        if (VoltageSetting_FromString(val, &want)) {
                            snprintf(VS, sizeof(VS), "%s", VoltageSetting_ToString(want));
                            if (want != cur) {
                                if (EEPROM_SaveVoltageSetting(want)) {
                                    anyChange = true;   // reboot efter ACK
                                }
                            }
                        }
                        continue;
                    }

                    /* FW -> no-op, ACK already includes FW/SN/VS */
                    if (strcmp(key, "FW") == 0) {
                        continue;
                    }

                    /* BOOT -> read & include current counter (NO increment here) */
                    if (strcmp(key, "BOOT") == 0) {
                        if (getBootCounterFromEEProm(&s_bootValue)) {
                            s_bootReported = true;
                        } else {
                            s_bootReported = false;
                        }
                        continue;
                    }
                }

                /* Ingen VOLTAGE-linje? VS er allerede preloaded til current */
                (void)seenVolt;

                s_rebootPending = anyChange;

                DEBUG_PRINT("\r\nSERIAL NUMBER:%s\r\n",SN);
                DEBUG_PRINT("VOLTAGE SETTING:%s\r\n",VS);
                if (s_bootReported) {
                    DEBUG_PRINT("BOOT COUNTER:%u\r\n", (unsigned)s_bootValue);
                }
            }

            app1Data.state1 = APP1_STATE_CLOSE_READ_FILE;
            break;
        }

        case APP1_STATE_CLOSE_READ_FILE:
            if(app1Data.nBytesRead > 0)
            {
                SYS_FS_FileClose(app1Data.fileHandle);
                wrtAckFile();

                app1Data.fileHandle1 = SYS_FS_FileOpen(ACK_PATH, SYS_FS_FILE_OPEN_WRITE_PLUS);
                app1Data.state1 = APP1_STATE_WRITE_TO_FILE;
            }
            else
            {
                SYS_FS_FileClose(app1Data.fileHandle);
                app1Data.state1 = APP1_STATE_IDLE;
            }
            break;

        case APP1_STATE_WRITE_TO_FILE:
            if (SYS_FS_FileWrite(app1Data.fileHandle1,
                                 (const void *) writeData,
                                 strlen(writeData)) == -1)
            {
                SYS_FS_FileClose(app1Data.fileHandle1);
                s_rebootPending = false;  // no reboot when ACK fails
                s_bootReported  = false;
                app1Data.state1 = APP1_STATE_ERROR;
            }
            else
            {
                app1Data.state1 = APP1_STATE_CLOSE_WRT_FILE;
            }
            break;

        case APP1_STATE_CLOSE_WRT_FILE:
            SYS_FS_FileClose(app1Data.fileHandle1);
            if (s_rebootPending) {
                APP_SystemReset();        /* AFTER ACK is closed */
            }
            // Reset BOOT flag so next run doesn't print it unless BOOT was requested again
            s_bootReported  = false;
            s_bootValue     = 0;
            app1Data.state1 = APP1_STATE_IDLE;
            break;

        case APP1_STATE_IDLE:
            if(app1Data.deviceIsConnected == false)
            {
                app1Data.state1 = APP1_STATE_WAIT_FOR_DEVICE_ATTACH;
            }
            break;

        case APP1_STATE_ERROR:
            if(SYS_FS_Unmount("/mnt/myDrive1") != 0)
            {
                app1Data.state1 = APP1_STATE_ERROR;
            }
            else
            {
                app1Data.state1 = APP1_STATE_WAIT_FOR_DEVICE_ATTACH;
                app1Data.deviceIsConnected = false;
            }
            break;

        default:
            break;
    }
}
/* End of File */