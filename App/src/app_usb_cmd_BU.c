/*******************************************************************************
  USB command file handler + ACK writer

  Læser 584_CMD.TXT fra /mnt/myDrive1, tolker VOLTAGE (HIGH/LOW eller 1/0),
  gemmer i EEPROM via dine eeprom-funktioner (via voltageSetting.c),
  og skriver 584_ACK.RTF. Rebooter KUN hvis værdien ændres ? efter ACK.
*******************************************************************************/

#include "app_usb_cmd.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#include "app.h"
#include "user.h"               // APP_SystemReset()
#include "voltageSetting.h"     // EEPROM_* + parsing
#include "ui_globals.h"

APP1_DATA app1Data USB_ALIGN;

/* Buffere som i din eksisterende kode */
USB_ALIGN char writeData[512] = "";
USB_ALIGN char readData[512];
uint16_t    bytesRead = 0;
char CMD[20] = "";
char VALUE[64] = "";
char FW[20] = "0.1x";
char SN[20] = "5840000";
char VS[20] = "HIGH";
char lines[10][128];

uint8_t I = 0;
uint8_t numberOfCommands = 0;
char voltageSetting = 0;

/* Kun lokalt i denne fil */
static bool s_rebootPending = false;

/* ---- helpers ---- */
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
    if (*p == '#' || *p == 0) return;

    char *key = p;
    while (*p && *p != ':' && *p != '=' && !isspace((unsigned char)*p)) ++p;
    if (*p) { *p++ = 0; }
    p = lskip_ws(p);

    if (*key == 0) return;
    *outKey = key;
    *outVal = p && *p ? p : (char*)"";
}

static void wrtAckFile (void)
{
    char tempStr[64] = "";

    strcpy(writeData,"");
    strcat(writeData, "****************************************\r\n");
    strcat(writeData, "****      THE GRYPHON HELIOS       *****\r\n");
    strcat(writeData, "****************************************\r\n");

    sprintf(tempStr,"\r\nFIRMWARE VERSION: %s\r\n", firmware);
    strcat(writeData, tempStr);
    sprintf(tempStr, "SERIAL NUMBER: %s\r\n", SN);
    strcat(writeData,tempStr);
    sprintf(tempStr,"VOLTAGE SETTING: %s\r\n", VS);
    strcat(writeData, tempStr);

    if (s_rebootPending) {
        strcat(writeData, "ACTION: Rebooting to apply voltage setting\r\n");
    }
}

/* ---- Harmony init + event handlers ---- */
void APP_USB_CMD_Initialize ( void )
{
    app1Data.state1 = APP1_STATE_BUS_ENABLE;
    app1Data.deviceIsConnected = false;
    s_rebootPending = false;
    DEBUG_PRINT("app usb cmd init\r\n");
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

/* ---- Hoved-state-maskine ---- */
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
            app1Data.fileHandle = SYS_FS_FileOpen("/mnt/myDrive1/584_CMD.TXT",
                                                  SYS_FS_FILE_OPEN_READ);
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
            app1Data.nBytesRead = SYS_FS_FileRead(app1Data.fileHandle,
                                                  app1Data.data, 1024);
            if(app1Data.nBytesRead > 0)
            {
                app1Data.data[ (app1Data.nBytesRead < 1024) ? app1Data.nBytesRead : 1023 ] = 0;

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

                bool anyChange = false;
                VS[0] = 0; /* hvis ikke VOLTAGE findes i fil, udfylder vi senere */

                for (I=0; I<numberOfCommands; I++)
                {
                    char *line = lines[I];
                    rtrim_inplace(line);

                    char *key=NULL, *val=NULL;
                    parse_kv(line, &key, &val);
                    if (!key) continue;

                    /* SN */
                    if (strcmp(key, "SN") == 0) {
                        if (val) snprintf(SN, sizeof(SN), "%s", val);
                        continue;
                    }

                    /* VOLTAGE (HIGH/LOW/1/0) */
                    if (strcmp(key, "VOLTAGE") == 0 || strcmp(key, "VOLT") == 0) {
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

                    /* FW ? ignoreres foreløbig */
                    if (strcmp(key, "FW") == 0) {
                        continue;
                    }
                }

                /* Ingen VOLTAGE-linje? Brug nuværende værdi i ACK */
                if (VS[0] == 0) {
                    voltage_setting_t cur;
                    if (!EEPROM_LoadVoltageSetting(&cur)) cur = VoltageSetting_Default();
                    snprintf(VS, sizeof(VS), "%s", VoltageSetting_ToString(cur));
                }

                s_rebootPending = anyChange;

                DEBUG_PRINT("\r\nSERIAL NUMBER:%s\r\n",SN);
                DEBUG_PRINT("VOLTAGE SETTING:%s\r\n",VS);
            }

            app1Data.state1 = APP1_STATE_CLOSE_READ_FILE;
            break;
        }

        case APP1_STATE_CLOSE_READ_FILE:
            if(app1Data.nBytesRead > 0)
            {
                SYS_FS_FileClose(app1Data.fileHandle);
                wrtAckFile();

                app1Data.fileHandle1 = SYS_FS_FileOpen("/mnt/myDrive1/584_ACK.RTF",
                                                       SYS_FS_FILE_OPEN_WRITE_PLUS);
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
                s_rebootPending = false;  // ingen reboot når ACK fejler
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
                APP_SystemReset();        /* først EFTER ACK er lukket */
            }
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



///////*******************************************************************************
//////  MPLAB Harmony Application Source File
//////
//////  Company:
//////    Microchip Technology Inc.
//////
//////  File Name:
//////    app_usb_cmd.c
//////
//////  Summary:
//////    This file contains the source code for the MPLAB Harmony application.
//////
//////  Description:
//////    This file contains the source code for the MPLAB Harmony application.  It
//////    implements the logic of the application's state machine and it may call
//////    API routines of other MPLAB Harmony modules in the system, such as drivers,
//////    system services, and middleware.  However, it does not call any of the
//////    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
//////    the modules in the system or make any assumptions about when those functions
//////    are called.  That is the responsibility of the configuration-specific system
//////    files.
////// *******************************************************************************/
//////
//////// *****************************************************************************
//////// *****************************************************************************
//////// Section: Included Files
//////// *****************************************************************************
//////// *****************************************************************************
//////
//////#include "app_usb_cmd.h"
//////#include <string.h>
//////// *****************************************************************************
//////// *****************************************************************************
//////// Section: Global Data Definitions
//////// *****************************************************************************
//////// *****************************************************************************
//////
//////// *****************************************************************************
///////* Application Data
//////
//////  Summary:
//////    Holds application data
//////
//////  Description:
//////    This structure holds the application's data.
//////
//////  Remarks:
//////    This structure should be initialized by the APP_Initialize function.
//////    
//////    Application strings and buffers are be defined outside this structure.
//////*/
//////
//////APP1_DATA app1Data USB_ALIGN;
//////
///////* This is the string that will written to the file */
//////USB_ALIGN char writeData[512] = "";
//////USB_ALIGN char readData[512];
//////uint16_t    bytesRead = 0; 
//////char CMD[20] = "";
//////char VALUE[20] = "";
//////char FW[20] = "0.1x";
//////char SN[20] = "5840001";
//////char VS[20] = "HIGH";
//////char lines[10][20];
//////
//////
//////
//////uint8_t I = 0;
//////uint8_t numberOfCommands = 0;
//////char voltageSetting = 0;
//////
//////
//////
//////// *****************************************************************************
//////// *****************************************************************************
//////// Section: Application Callback Functions
//////// *****************************************************************************
//////// *****************************************************************************
//////
///////* TODO:  Add any necessary callback functions.
//////*/
//////
//////// *****************************************************************************
//////// *****************************************************************************
//////// Section: Application Local Functions
//////// *****************************************************************************
//////// *****************************************************************************
//////
///////* TODO:  Add any necessary local functions.
//////*/
//////#include <string.h>
//////#include <ctype.h>
//////#include "system/time/sys_time.h"
//////#include "app.h"
//////#include "user.h"               // for APP_SystemReset
//////#include "voltageSetting.h"     // for EEPROM_* og parsing af VOLTAGE
//////
//////// ...
//////static bool s_rebootPending = false;
//////
//////// Fremad-deklarationer
////////bool EEPROM_SaveVoltageSetting(voltage_setting_t v);
//////
//////// Trim helpers (enkle, sikre)
//////static const char* skip_ws(const char* s) { while (*s && isspace((unsigned char)*s)) s++; return s; }
//////static void rtrim(char* s) { size_t n=strlen(s); while (n && isspace((unsigned char)s[n-1])) s[--n]=0; }
//////
//////// Returnerer true hvis linjen håndterede VOLTAGE-kommando
//////static bool handle_voltage_command_line(const char* line, bool *outChanged, voltage_setting_t *outNew)
//////{
//////    if (!line) return false;
//////    // Arbejd på en kopi vi kan ændre
//////    char buf[64];
//////    strncpy(buf, line, sizeof(buf)-1);
//////    buf[sizeof(buf)-1] = 0;
//////
//////    char* p = (char*)skip_ws(buf);
//////
//////    // accepter "VOLTAGE=HIGH", "VOLT=LOW", "SET VOLTAGE HIGH", osv. (case-insensitive)
//////    // Gør det simpelt: find "VOLT" i starten eller efter "SET "
//////    bool seenSet = false;
//////    if (strncasecmp(p, "SET", 3) == 0 && isspace((unsigned char)p[3])) {
//////        p = (char*)skip_ws(p+3);
//////        seenSet = true;
//////    }
//////
//////    if (strncasecmp(p, "VOLTAGE", 7) != 0 && strncasecmp(p, "VOLT", 4) != 0) {
//////        return false; // ikke en voltage-linje
//////    }
//////
//////    // hop over nøglen
//////    while (*p && !isspace((unsigned char)*p) && *p != '=') p++;
//////    // spring whitespace over
//////    p = (char*)skip_ws(p);
//////
//////    // tillad både "KEY=VALUE" og "KEY VALUE"
//////    if (*p == '=') {
//////        p++;
//////        p = (char*)skip_ws(p);
//////    }
//////
//////    // p peger nu (forhåbentlig) på "HIGH"/"LOW"
//////    rtrim(p);
//////    if (*p == 0) return false;
//////
//////    voltage_setting_t want;
//////    if (strncasecmp(p, "HIGH", 4) == 0) {
//////        want = VoltageHigh;
//////    } else if (strncasecmp(p, "LOW", 3) == 0) {
//////        want = VoltageLow;
//////    } else {
//////        return false; // ukendt værdi -> lad din overordnede parser skrive en fejl-ACK
//////    }
//////
//////    if (outChanged) *outChanged = (appData.voltageSetting != want);
//////    if (outNew)     *outNew     = want;
//////    return true;
//////}
//////
//////// Kald denne fra din eksisterende linje-for-linje parser:
//////static void process_command_line_with_voltage(const char* line)
//////{
//////    bool changed = false;
//////    voltage_setting_t newVal = appData.voltageSetting;
//////
//////    if (handle_voltage_command_line(line, &changed, &newVal)) {
//////        if (!changed) {
//////            usb_ack_printf("VOLTAGE unchanged (%s)\r\n", (newVal==VoltageHigh) ? "HIGH" : "LOW");
//////            return;
//////        }
//////        if (!EEPROM_SaveVoltageSetting(newVal)) {
//////            usb_ack_printf("VOLTAGE write FAILED\r\n");
//////            return;
//////        }
//////
//////        // Opdater RAM-kopi for logikkens skyld (valgfrit ? vi rebooter alligevel)
//////        appData.voltageSetting = newVal;
//////
//////        usb_ack_printf("VOLTAGE set to %s -> rebooting\r\n", (newVal==VoltageHigh) ? "HIGH" : "LOW");
//////
//////        // VIGTIGT: flush/luk ACK-filen i din eksisterende commit/teardown-rutine
//////        // Her kan vi blot markere, at der skal resettes efter filerne er lukket:
//////        schedule_reboot_after_ack();
//////    }
//////}
//////
//////// Simpel planlægger: reset kort efter ACK er skrevet og filsystemet lukket
//////static bool s_rebootPending = false;
//////
//////void schedule_reboot_after_ack(void)
//////{
//////    s_rebootPending = true;
//////}
//////
//////// Kald dette ét sted, hvor du i forvejen afslutter behandlingen og HAR lukket filer/mounts:
//////void maybe_do_pending_reboot(void)
//////{
//////    if (!s_rebootPending) return;
//////
//////    // Lille sikkerhedsmargin så vært (PC) når at se ACK-filen
//////    // (Hvis du allerede un-mounter, kan 100-200 ms være nok)
//////    SYS_TIME_DelayMS(300);
//////    SYS_RESET_SoftwareReset();  // Harmony 3 software reset
//////}
//////
//////
//////void wrtAckFile (void)
//////{
//////    char tempStr[50] = "";
//////    
//////    strcpy(writeData,"");
//////    strcat(writeData, "****************************************\r\n");
//////    strcat(writeData, "****      THE GRYPHON HELIOS       *****\r\n");
//////    strcat(writeData, "****************************************\r\n");
//////    sprintf(tempStr,"\r\nFIRMWARE VERSION: %s\r\n", FW);
//////    strcat(writeData, tempStr);
//////    sprintf(tempStr, "SERIAL NUMBER: %s\r\n", SN);
//////    strcat(writeData,tempStr);
//////    sprintf(tempStr,"VOLTAGE SETTING: %s\r\n", VS);
//////    strcat(writeData, tempStr);
//////    if (s_rebootPending) strcat(writeData, "ACTION: Rebooting to apply voltage setting\r\n");
//////
//////}
//////
//////// *****************************************************************************
//////// *****************************************************************************
//////// Section: Application Initialization and State Machine Functions
//////// *****************************************************************************
//////// *****************************************************************************
//////
///////*******************************************************************************
//////  Function:
//////    void APP_Initialize ( void )
//////
//////  Remarks:
//////    See prototype in app.h.
////// */
//////
//////void APP_USB_CMD_Initialize ( void )
//////{
//////    /* Place the App state machine in its initial state. */
//////    app1Data.state1 = APP1_STATE_BUS_ENABLE;
//////    app1Data.deviceIsConnected = false;
//////    DEBUG_PRINT("app usb cmd init\r\n");
//////    /* TODO: Initialize your application's state machine and other
//////     * parameters.
//////     */
//////}
//////
//////
//////
//////
//////USB_HOST_EVENT_RESPONSE APP_USBHostEventHandler (USB_HOST_EVENT event, void * eventData, uintptr_t context)
//////{
//////    switch (event)
//////    {
//////        case USB_HOST_EVENT_DEVICE_UNSUPPORTED:
//////            break;
//////        default:
//////            break;
//////                    
//////    }
//////    
//////    return(USB_HOST_EVENT_RESPONSE_NONE);
//////}
//////
//////void APP_SYSFSEventHandler(SYS_FS_EVENT event, void * eventData, uintptr_t context)
//////{
//////    switch(event)
//////    {
//////        case SYS_FS_EVENT_MOUNT:
//////            app1Data.deviceIsConnected = true;
//////            
//////            break;
//////            
//////        case SYS_FS_EVENT_UNMOUNT:
//////            app1Data.deviceIsConnected = false;
//////            LED1_Off();
//////            break;
//////            
//////        default:
//////            break;
//////    }
//////}
///////******************************************************************************
//////  Function:
//////    void APP_Tasks ( void )
//////
//////  Remarks:
//////    See prototype in app.h.
////// */
//////
//////void APP_USB_CMD_Tasks ( void )
//////{
//////    switch(app1Data.state1)
//////    {
//////        case APP1_STATE_BUS_ENABLE:
//////                      
//////           /* Set the event handler and enable the bus */
//////            SYS_FS_EventHandlerSet((void *)APP_SYSFSEventHandler, (uintptr_t)NULL);
//////            USB_HOST_EventHandlerSet(APP_USBHostEventHandler, 0);
//////            USB_HOST_BusEnable(USB_HOST_BUS_ALL);
//////            app1Data.state1 = APP1_STATE_WAIT_FOR_BUS_ENABLE_COMPLETE;
//////            break;
//////            
//////        case APP1_STATE_WAIT_FOR_BUS_ENABLE_COMPLETE:
//////            if(USB_HOST_BusIsEnabled(USB_HOST_BUS_ALL))
//////            {
//////                app1Data.state1 = APP1_STATE_WAIT_FOR_DEVICE_ATTACH;
//////            }
//////            break;
//////       
//////        case APP1_STATE_WAIT_FOR_DEVICE_ATTACH:
//////
//////            /* Wait for device attach. The state machine will move
//////             * to the next state when the attach event
//////             * is received.  */
//////            if(app1Data.deviceIsConnected)
//////            {
//////                app1Data.state1 = APP1_STATE_DEVICE_CONNECTED;
//////            }
//////
//////            break;
//////
//////        case APP1_STATE_DEVICE_CONNECTED:
//////
//////            /* Device was connected. We can try mounting the disk */
//////            app1Data.state1 = APP1_STATE_OPEN_FILE;
//////            break;
//////
//////        case APP1_STATE_OPEN_FILE:
//////
//////            /* Try opening the file for append */
//////            app1Data.fileHandle = SYS_FS_FileOpen("/mnt/myDrive1/584_CMD.TXT", (SYS_FS_FILE_OPEN_READ));
////// 
//////            
//////            if(app1Data.fileHandle == SYS_FS_HANDLE_INVALID )
//////            {
//////                /* Could not open the file. Error out*/
//////                app1Data.state1 = APP1_STATE_ERROR;
//////
//////            }
//////            else
//////            {
//////                /* File opened successfully. Write to file */
//////                app1Data.state1 = APP1_STATE_READ_FILE;
//////
//////            }
//////            break;
//////
//////        case APP1_STATE_WRITE_TO_FILE:
//////
//////            /* Try writing to the file */
//////            
//////            if (SYS_FS_FileWrite( app1Data.fileHandle1, (const void *) writeData,strlen(writeData)) == -1)
//////            {
//////                /* Write was not successful. Close the file
//////                 * and error out.*/
//////                SYS_FS_FileClose(app1Data.fileHandle1);
//////                app1Data.state1 = APP1_STATE_ERROR;
//////
//////            }
//////            else
//////            {
//////                /* We are done writing. Close the file */
//////                app1Data.state1 = APP1_STATE_CLOSE_WRT_FILE;
//////            }
//////
//////            break;
//////            
//////        case APP1_STATE_READ_FILE:
//////
//////            /* Try writing to the file */
//////             app1Data.nBytesRead = SYS_FS_FileRead( app1Data.fileHandle, app1Data.data, 1024 );
//////             if(app1Data.nBytesRead > 0)
//////             {
//////                DEBUG_PRINT("\r\n%d\r\n",app1Data.nBytesRead);  
//////             
//////                 char *p = strtok(app1Data.data, "\r\n");
//////                 sprintf(lines[0],"%s",p);
//////                 I = 0;
//////                 while(p != NULL)
//////                 {
//////                     I++;
//////                     p = strtok(NULL, "\r\n");
//////                     if(p !=NULL)
//////                      {
//////                       sprintf(lines[I],"%s",p);  
//////                      }
//////                 }
//////
//////                 //DEBUG_PRINT("Line 0: %s",lines[0]);
//////                 //DEBUG_PRINT("Line 1: %s",lines[1]);
//////
//////                 numberOfCommands = I;
//////
//////                 I=0;
//////                 for(I=0;I<numberOfCommands;I++)
//////                 {
//////                     p = strtok(lines[I],":");
//////                     sprintf(CMD, "%s", p);
//////                     p = strtok(NULL,":");
//////                     sprintf(VALUE, "%s", p);
//////
//////                     if(strcmp(CMD,"SN")==0)
//////                     {
//////                       sprintf(SN, "%s", VALUE);
//////                    }
//////
//////                    if (strcmp(CMD, "VOLTAGE") == 0 || strcmp(CMD, "VOLT") == 0) {
//////                        // Tillad både "VOLTAGE:HIGH" og "VOLTAGE=HIGH"
//////                        char *val = VALUE;
//////                        char *eq = strchr(VALUE, '=');
//////                        if (eq && eq[1] != '\0') val = eq + 1;
//////
//////                        // Trim venstre whitespace
//////                        while (*val == ' ' || *val == '\t') val++;
//////
//////                        voltage_setting_t want, cur;
//////                        // Læs nuværende fra EEPROM (fallback = HIGH)
//////                        if (!EEPROM_LoadVoltageSetting(&cur)) cur = VoltageSetting_Default();
//////
//////                        if (VoltageSetting_FromString(val, &want)) {
//////                            sprintf(VS, "%s", VoltageSetting_ToString(want)); // til ACK
//////
//////                            if (want != cur) {
//////                                if (EEPROM_SaveVoltageSetting(want)) {
//////                                    s_rebootPending = true; // markér at vi skal genstarte pga. ændring
//////                                } else {
//////                                    // Gemmes ikke -> behold cur i EEPROM; skriv evt. fejl i ACK-nedenfor
//////                                    // (valgfrit: append " (WRITE FAILED)" til VS)
//////                                }
//////                            } else {
//////                                // uændret; VS svarer stadig til aktuel værdi
//////                            }
//////                        } else {
//////                            // Ukendt værdi -> lad VS stå uændret; skriv evt. fejlnote i ACK
//////                            // (valgfrit: sprintf(VS, "INVALID");)
//////                        }
//////                    }
//////
//////                     {
//////                       sprintf(VS, "%s", VALUE);
//////                     }                 
//////                     if(strcmp(CMD,"FW")==0)
//////                     {
//////                         //sprintf(VS, "%s", VALUE);
//////                     }                 
//////
//////                 }
//////                 DEBUG_PRINT("\r\nSERIAL NUMBER:%s\r\n",SN);
//////                 DEBUG_PRINT("VOLTAGE SETTING:%s\r\n",VS);
//////                
//////             }
//////             app1Data.state1 = APP1_STATE_CLOSE_READ_FILE;
//////            
//////
//////            break;
//////
//////        case APP1_STATE_CLOSE_READ_FILE:
//////
//////            /* Close the file */
//////            
//////            if(app1Data.nBytesRead > 0)
//////            {
//////              SYS_FS_FileClose(app1Data.fileHandle);
//////              wrtAckFile ();
//////              app1Data.fileHandle1 = SYS_FS_FileOpen("/mnt/myDrive1/584_ACK.RTF", (SYS_FS_FILE_OPEN_WRITE_PLUS));
//////              app1Data.state1 = APP1_STATE_WRITE_TO_FILE;
//////            }
//////            else
//////            {
//////               SYS_FS_FileClose(app1Data.fileHandle);
//////               app1Data.state1 = APP1_STATE_IDLE;
//////            }
//////            break;
//////
//////        case APP1_STATE_CLOSE_WRT_FILE:
//////
//////            /* Close the file */
//////            SYS_FS_FileClose(app1Data.fileHandle1);
//////            /* Indicate User that File operation has been completed */
//////            //LED1_On(); 
//////            /* The test was successful. Lets idle. */
//////            APP_SystemReset();
//////
//////            app1Data.state1 = APP1_STATE_IDLE;
//////            break;
//////
//////        case APP1_STATE_IDLE:
//////
//////            /* The application comes here when the demo has completed
//////             * successfully. Provide LED indication. Wait for device detach
//////             * and if detached, wait for attach. */
//////            
//////            if(app1Data.deviceIsConnected == false)
//////            {
//////                app1Data.state1 = APP1_STATE_WAIT_FOR_DEVICE_ATTACH;
//////            }
//////            APP_SystemReset( );
//////            break;
//////
//////        case APP1_STATE_ERROR:
//////
//////            /* The application comes here when the demo
//////             * has failed. Provide LED indication .*/
//////
//////            if(SYS_FS_Unmount("/mnt/myDrive1") != 0)
//////            {
//////                /* The disk could not be un mounted. Try
//////                 * un mounting again untill success. */
//////
//////                app1Data.state1 = APP1_STATE_ERROR;
//////            }
//////            else
//////            {
//////                /* UnMount was successful. Wait for device attach */
//////                app1Data.state1 =  APP1_STATE_WAIT_FOR_DEVICE_ATTACH;
//////                app1Data.deviceIsConnected = false; 
//////
//////            }
//////            break;
//////
//////        default:
//////            break;
//////
//////    }
//////}
////// 
//////
///////*******************************************************************************
////// End of File
////// */
