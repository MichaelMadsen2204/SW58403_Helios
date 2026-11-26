// eeProm_Functions.c ? robust version (ACK-poll, retries, klar OK/FEJL)
// Bevarer dine funktionsnavne og adresser.
//
// Afhænger af Harmony I2C2 (I2C_ERROR, I2C2_*), CoreTimer og appData.
//
#include "definitions.h"   // indeholder app.h, system headers, Legato types mm.
#include "ui_globals.h"
#include "app.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

// ============================================================
//  Konfiguration / layout (samme adresser som i din fil)
// ============================================================
#ifndef EE_DEV_MAIN
#  define EE_DEV_MAIN      0x50    // hoved-konfig (24xx)
#endif
#ifndef EE_DEV_ERR
#  define EE_DEV_ERR       0x51    // fejlflag
#endif
#ifndef EE_PAGE_SIZE
#  define EE_PAGE_SIZE     16      // konservativ
#endif

#define STARTLVL_MIN 0
#define STARTLVL_MAX 66
#define MAXLVL_MAX   84


#define EE_ADDR_VOLTAGE_SETTING   (0x86u)

// ? interne I2C status/?lås?
static volatile uint8_t s_ee_rw_state = 0;   // 0=busy, 1=ok, 2=err
static volatile bool    s_eep_lock    = false;

// Dine globale buffere
static uint8_t writeBuffer[WRITE_BUFFER_SIZE];
//static uint8_t readBuffer[READ_BUFFER_SIZE];

// ============================================================
//  Hjælpere
// ============================================================
static inline uint8_t clamp_u8(uint8_t v, uint8_t lo, uint8_t hi)
{ return (v < lo) ? lo : (v > hi) ? hi : v; }

static inline void normalizeVolLevels(void)
{
    appData.startLvl = clamp_u8(appData.startLvl, STARTLVL_MIN, STARTLVL_MAX);
    if (appData.maxLvl < appData.startLvl) appData.maxLvl = appData.startLvl;
    if (appData.maxLvl > MAXLVL_MAX)       appData.maxLvl = MAXLVL_MAX;
}

static inline void eep_lock_acquire(void)
{
    while (s_eep_lock) { CORETIMER_DelayUs(50); }
    s_eep_lock = true;
}
static inline void eep_lock_release(void)
{
    s_eep_lock = false;
}

// ============================================================
//  I2C callback + vent/flyt (robust)
// ============================================================

// SÆT DENNE i init (du gør det allerede i initAmp):
// I2C2_CallbackRegister(eePromCallback, (uintptr_t)NULL);
void eePromCallback(uintptr_t context)
{
    I2C_ERROR e = I2C2_ErrorGet();
    if (e == I2C_ERROR_NONE) {
        s_ee_rw_state         = 1;    // OK
        appData.eepromRW_Done = 1;    // til bagud-kompatibilitet
    } else {
        s_ee_rw_state         = 2;    // FEJL
        appData.eepromRW_Done = 2;
    }
}

static bool wait_done_us(uint32_t total_us)
{
    uint32_t t = 0;
    const uint32_t step = 50;
    while (s_ee_rw_state == 0 && t < total_us) {
        CORETIMER_DelayUs(step);
        t += step;
    }
    return (s_ee_rw_state == 1);
}

// ACK-poll: prøv at skrive 1 byte (adressepeger) indtil enheden ACK?er
static bool ee_ack_poll(uint8_t dev, uint8_t any_addr, uint32_t timeout_us)
{
    uint32_t elapsed = 0;
    while (elapsed < timeout_us) {
        while (I2C2_IsBusy());
        s_ee_rw_state         = 0;
        appData.eepromRW_Done = 0;

        uint8_t a = any_addr; // typisk 0 er fint
        // Hvis EEPROM stadig skriver internt, NACK?er den control-byte => wait_done_us bliver false
        if (I2C2_Write(dev, &a, 1) && wait_done_us(2000)) return true;

        CORETIMER_DelayUs(500);
        elapsed += 500;
    }
    return false;
}

static bool i2c_write_block(uint8_t dev, const uint8_t *buf, size_t len)
{
    while (I2C2_IsBusy());
    s_ee_rw_state         = 0;
    appData.eepromRW_Done = 0;

    if (!I2C2_Write(dev, (uint8_t*)buf, (uint32_t)len)) return false;
    return wait_done_us(20000);
}

static bool i2c_writeread(uint8_t dev, const uint8_t *w, size_t wn, uint8_t *r, size_t rn)
{
    while (I2C2_IsBusy());
    s_ee_rw_state         = 0;
    appData.eepromRW_Done = 0;

    if (!I2C2_WriteRead(dev, (uint8_t*)w, (uint32_t)wn, r, (uint32_t)rn)) return false;
    return wait_done_us(20000);
}
// --- 1-byte write + ACK-poll ---
static bool ee_write_byte(uint8_t dev, uint8_t addr, uint8_t value)
{
    uint8_t tmp[2] = { addr, value };

    // Brug din eksisterende i2c_write_block() der sætter s_ee_rw_state og venter på callback
    if (!i2c_write_block(dev, tmp, 2))
        return false;

    // Vent robust på at EEPROM?s interne write-cyklus er færdig
    return ee_ack_poll(dev, 0x00, 15000);
}
// Sikker page-write (krydser aldrig sidegrænser) + ACK-poll efter hver page
static bool ee_write_paged(uint8_t dev, uint8_t addr, const uint8_t *data, size_t len)
{
    size_t off = 0;
    while (off < len) {
        uint8_t a      = (uint8_t)(addr + off);
        uint8_t within = (uint8_t)(a % EE_PAGE_SIZE);
        uint8_t room   = (uint8_t)(EE_PAGE_SIZE - within);
        uint8_t chunk  = (uint8_t)((len - off) < room ? (len - off) : room);

        writeBuffer[0] = a;
        for (uint8_t i = 0; i < chunk; i++) writeBuffer[1 + i] = data[off + i];

        if (!i2c_write_block(dev, writeBuffer, (size_t)1 + chunk)) return false;

        // VENT robust: ACK-poll, ikke kun fast 5 ms (undgår ?for tidlig læsning?)
        if (!ee_ack_poll(dev, 0x00, 15000)) return false;

        off += chunk;
    }
    return true;
}

static bool ee_read_retry(uint8_t dev, uint8_t addr, uint8_t *dst, size_t len, int tries)
{
    while (tries-- > 0) {
        if (i2c_writeread(dev, &addr, 1, dst, len)) return true;
        CORETIMER_DelayUs(2000); // kort backoff
    }
    return false;
}

static bool ee_read(uint8_t dev, uint8_t addr, uint8_t *dst, size_t len)
{
    return ee_read_retry(dev, addr, dst, len, 5);
}

// ============================================================
//                H Ø J N I V E A U - A P I ' s
// ============================================================

void getInpNamesFromEEProm(void)
{
    // 11 navne á 8 bytes: 0x20,0x28,0x30, ... (din layout)
    uint8_t addr = 0x20;
    for (uint8_t i = 1; i <= 11; i++, addr = (uint8_t)(addr + 8)) {
        uint8_t tmp[8];
        if (ee_read(EE_DEV_MAIN, addr, tmp, 8)) {
            memcpy(inpNames[i], tmp, 8);
        } else {
            // ved fejl: lad eksisterende inpNames[i] stå; log kun
            DEBUG_PRINT("EEPROM read err @names[%u]\r\n", i);
        }
    }
}
void getEEPromValues(void)
{
    uint8_t b[16];

    if (ee_read(EE_DEV_MAIN, 0x00, b, 16)) {
        CORETIMER_DelayUs(5000);

        if (b[0] != 0) appData.curInp = b[0];

        appData.startLvl     = b[1];
        appData.maxLvl       = b[2];
        appData.balance      = b[3];
        appData.dispMode     = (b[4] & 0x7F);
        appData.enableSimpleViewFlg = (b[4] & 0x80) ? 1 : 0;
        appData.irSource     = b[5];
        appData.avInp        = b[6];
        dacData.pcmFilter    = b[7];
        dacData.dsdFilter    = b[8];
        dacData.dsdLpFilter  = b[9];
        dacData.digiGain     = b[10];
        appData.pickupSelection = b[11];
        appData.greenBias    = b[12];

//        printf("\r\nEEPROM values @0x00:\r\n");
//        printf("startLvl            = %u\r\n", appData.startLvl);
//        printf("maxLvl              = %u\r\n", appData.maxLvl);
//        printf("balance             = %u\r\n", appData.balance);
//        printf("dispMode             = %u\r\n", appData.dispMode);
//        printf("simpleViewEnabled   = %u\r\n", appData.enableSimpleViewFlg);
//        printf("irSource            = %u\r\n", appData.irSource);
//        printf("avInp               = %u\r\n", appData.avInp);
//        printf("pcmFilter           = %u\r\n", dacData.pcmFilter);
//        printf("dsdFilter           = %u\r\n", dacData.dsdFilter);
//        printf("dsdLpFilter         = %u\r\n", dacData.dsdLpFilter);
//        printf("digiGain            = %u\r\n", dacData.digiGain);
//        printf("pickupSelection     = %u\r\n", appData.pickupSelection);
//        printf("greenBias           = %u\r\n", appData.greenBias);
    } else {
        printf("EEPROM read error @0x00..0x0F\r\n");
    }

    if (ee_read(EE_DEV_MAIN, 0x10, b, 16)) {
        for (uint8_t k = 0; k < 6; k++) {
            appData.inpSens[1 + k] = b[k];
            //printf("inpSens[%u]          = %u\r\n", 1 + k, b[k]);
        }
    } else {
        printf("EEPROM read error @0x10..0x1F\r\n");
    }

    normalizeVolLevels();
}

//void getEEPromValues(void)
//{
//    // Baseblok 0x00..0x0F (vi bruger kun 0x00..0x0B i praksis)
//    uint8_t b[16];
//    
//    if (ee_read(EE_DEV_MAIN, 0x00, b, 16)) {
//        CORETIMER_DelayUs(5000);
//        DEBUG_PRINT("EEPROM read dispmode : %x\r\n", b[4]);
//        if (b[0] != 0) appData.curInp = b[0];  // rør ikke curInp ved 0/fejl
//        appData.startLvl     = b[1];
//        appData.maxLvl       = b[2];
//        appData.balance      = b[3];
//        appData.dispMode     = (b[4] & 0x7F);
//        appData.enableSimpleViewFlg = (b[4] & 0x80);
//        appData.irSource     = b[5];
//        appData.avInp        = b[6];
//        dacData.pcmFilter    = b[7];
//        dacData.dsdFilter    = b[8];
//        dacData.dsdLpFilter  = b[9];
//        dacData.digiGain     = b[10];
//        appData.pickupSelection = b[11];
//        appData.greenBias    = b[12];   
//    } else {
//        DEBUG_PRINT("EEPROM read err @0x00..0x0F\r\n");
//        // intet memset til 0 her ? bevar gyldige RAM-værdier
//    }
//
//    // Input level match 0x10..0x15
//    if (ee_read(EE_DEV_MAIN, 0x10, b, 16)) {
//        for (uint8_t k = 0; k < 6; k++) appData.inpSens[1 + k] = b[k];
//    } else {
//        DEBUG_PRINT("EEPROM read err @0x10..0x1F\r\n");
//    }
//
//    normalizeVolLevels();
//}

void getSNFromEEProm(void)
{
    uint8_t b[4];
    if (ee_read(EE_DEV_MAIN, 0x80, b, 4)) {
        appData.snSingles   = b[0];
        appData.snTens      = b[1];
        appData.snHundreds  = b[2];
        appData.snThousands = b[3];
    } else {
        DEBUG_PRINT("EEPROM read err @serial\r\n");
    }
}

void saveSNToEEProm(void)
{
    uint8_t payload[4] = {
        appData.snSingles,
        appData.snTens,
        appData.snHundreds,
        appData.snThousands
    };
    (void)ee_write_paged(EE_DEV_MAIN, 0x80, payload, sizeof payload);
}

void saveVolumeSettings(void)
{
    normalizeVolLevels();
    // [addr=0x01] startLvl, maxLvl, balance
    uint8_t payload[3] = { appData.startLvl, appData.maxLvl, appData.balance };
    (void)ee_write_paged(EE_DEV_MAIN, 0x01, payload, sizeof payload);
}

void saveDisplaySettings(void)
{
    uint8_t v = (uint8_t)((appData.dispMode & 0x7F) | (appData.enableSimpleViewFlg ? 0x80 : 0));
    (void)ee_write_byte(EE_DEV_MAIN, 0x04, v);
    
}

void saveAvSettings(void)
{
   (void)ee_write_byte(EE_DEV_MAIN, 0x06, appData.avInp);
}

void saveIRSourceSetting(void)
{
    (void)ee_write_byte(EE_DEV_MAIN, 0x05, appData.irSource);
}

void saveCurrentInput(void)
{
    if (appData.curInp == 0) return; // gem aldrig 0
    (void)ee_write_byte(EE_DEV_MAIN, 0x00, appData.curInp);
}

void savePickupSelection(void)
{
    (void)ee_write_byte(EE_DEV_MAIN, 0x0B, appData.pickupSelection);
}

void saveDigitalSetup(void)
{
    DEBUG_PRINT("[EEP] saveDigitalSetup pcm=%u dsd=%u lp=%u gain=%u\r\n",
           dacData.pcmFilter, dacData.dsdFilter, dacData.dsdLpFilter, dacData.digiGain);
//    
//    uint8_t payload[4] = { dacData.pcmFilter, dacData.dsdFilter, dacData.dsdLpFilter, dacData.digiGain };
//    (void)ee_write_paged(EE_DEV_MAIN, 0x07, payload, sizeof payload);
    
    (void)ee_write_byte(EE_DEV_MAIN, 0x07, dacData.pcmFilter);
    (void)ee_write_byte(EE_DEV_MAIN, 0x08, dacData.dsdFilter);
    (void)ee_write_byte(EE_DEV_MAIN, 0x09, dacData.dsdLpFilter);
    (void)ee_write_byte(EE_DEV_MAIN, 0x0A, dacData.digiGain);
    
}

void saveInpLvlMatchValues(void)
{
    uint8_t payload[6];
    for (uint8_t i = 0; i < 6; i++) payload[i] = appData.inpSens[1 + i];
    (void)ee_write_paged(EE_DEV_MAIN, 0x10, payload, sizeof payload);
}

void saveErrorStatus(void)
{
    // separat EE på 0x51 som du havde ? med ACK-poll via ee_write_paged
    (void)ee_write_byte(EE_DEV_ERR, 0x00, appData.errorStatus);
}
void saveGreenBias(void)
{
    (void)ee_write_byte(EE_DEV_MAIN, 0x0C, appData.greenBias);
}
void getErrorStatus(void)
{
    uint8_t b;
    if (ee_read(EE_DEV_ERR, 0x00, &b, 1)) {
        appData.errorStatus     = b;
        appData.tempErrorStatus = b;
    } else {
        DEBUG_PRINT("EEPROM read err @err\r\n");
        // bevar seneste status i RAM
    }
}

// ----------------------- Defaults -----------------------

static void write_default_block0(void)
{
    // 0x00.. : curInp,startLvl,maxLvl,balance,dispMode|flag,irSource,avInp,
    // pcm, dsd, dsdLP, digiGain, pickup, (4x reserved)
    uint8_t blk[16] = {
        1,    // curInp
        0,    // startLvl
        84,   // maxLvl
        6,    // balance
        (uint8_t)(modeDim | 0x80), // dispMode|enableSimpleViewFlg
        1,    // irSource (Front)
        0,    // avInp
        4,    // pcmFilter
        3,    // dsdFilter
        0,    // dsdLpFilter
        1,    // digiGain
        appData.pickupSelection,    // pickupSelection (MM/MC)
        0,    // greenBias  
        0,0,0 // reserved
    };
    (void)ee_write_paged(EE_DEV_MAIN, 0x00, blk, sizeof blk);
}

static void write_default_inpLvl(void)
{
    uint8_t blk[16] = { 0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0 };
    (void)ee_write_paged(EE_DEV_MAIN, 0x10, blk, sizeof blk);
}

static void write_default_names(void)
{
    // Skriv parvis: (1,2), (3,4), ... som i din oprindelige fil
    uint8_t addr = 0x20;
    for (uint8_t i = 1; i <= 11; ) {
        uint8_t tmp[16];
        memcpy(&tmp[0], defaultInputNames[i], 8);
        if (i+1 <= 11) memcpy(&tmp[8], defaultInputNames[i+1], 8);
        size_t len = (i+1 <= 11) ? 16 : 8;
        (void)ee_write_paged(EE_DEV_MAIN, addr, tmp, len);
        addr = (uint8_t)(addr + 0x10);
        i += 2;
    }
}

void writeEEpromDefaultIfEmty(void)
{
    // Samme adfærd som din tidligere (ingen signatur-check): skriv defaults
    appData.curLvl              = 0;
    appData.avInp               = AV_NONE;
    appData.maxLvl              = 84;
    appData.balance             = 6;
    appData.startLvl            = 0;
    appData.irSource            = 1;
    appData.enableSimpleViewFlg = 1;
    appData.dispMode            = modeDim;
    appData.greenBias           = 0;
    appData.pickupSelection = 0;
    for (uint8_t i = 1; i <= 6; i++) appData.inpSens[i] = 0;
    dacData.pcmFilter = 4;
    dacData.digiGain = 1;
    dacData.dsdLpFilter = 0;

    write_default_block0();
    write_default_inpLvl();
    write_default_names();
}

void writeEEpromDefault(void)
{
    // Init RAM defaults (som før)
    appData.curLvl              = 0;
    appData.avInp               = AV_NONE;
    appData.maxLvl              = 84;
    appData.balance             = 6;
    appData.startLvl            = 0;
    appData.irSource            = 1;
    appData.enableSimpleViewFlg = 1;
    appData.dispMode            = modeDim;
    appData.greenBias           = 0;
    //appData.pickupSelection = 0;
    for (uint8_t i = 1; i <= 6; i++) appData.inpSens[i] = 0;
    dacData.pcmFilter = 4;
    dacData.digiGain = 1;
    dacData.dsdLpFilter = 0;

    // Skriv til EEPROM
    write_default_block0();
    write_default_inpLvl();
    write_default_names();
}

void saveInpName(void)
{
    // én blok á 8 bytes ved (0x18 + 8*i) = 0x20 + 8*(i-1)
    uint8_t addr = (uint8_t)(0x20 + 8 * (appData.inpToRename - 1u));
    (void)ee_write_paged(EE_DEV_MAIN, addr, (uint8_t*)inpNames[appData.inpToRename], 8);
}


void saveDisp(void)
{
  if(appData.saveDisplayFlg)
    {
        saveDisplaySettings();
        appData.saveDisplayFlg = 0;
    }
}

/* === VoltageSetting wrappers (bruges af voltageSetting.c) === */
/* Gemmer 0=LOW, 1=HIGH i EE_DEV_MAIN @ 0x0D */
bool saveVoltageSettingToEEProm(uint8_t v)
{
    /* clamp til 0/1 for sikkerhed */
    v = (v != 0) ? 1u : 0u;
    return ee_write_byte(EE_DEV_MAIN, EE_ADDR_VOLTAGE_SETTING, v);
}

/* Returnerer true hvis læsning lykkes, *out = 0/1 på succes */
bool getVoltageSettingFromEEProm(uint8_t *out)
{
    if (!out) return false;
    uint8_t b = 0xFF;
    if (!ee_read(EE_DEV_MAIN, EE_ADDR_VOLTAGE_SETTING, &b, 1)) return false;
    *out = b;
    return true;
}


// ===== Boot counter (16-bit, LE) @ 0x84 =====
bool getBootCounterFromEEProm(uint16_t *out)
{
    if (!out) return false;
    uint8_t b[2] = {0,0};
    if (!ee_read(EE_DEV_MAIN, 0x84, b, 2)) return false;
    *out = (uint16_t)(b[0] | ((uint16_t)b[1] << 8));
    return true;
}

bool saveBootCounterToEEProm(uint16_t v)
{
    uint8_t b[2] = { (uint8_t)(v & 0xFF), (uint8_t)(v >> 8) };
    return ee_write_paged(EE_DEV_MAIN, 0x84, b, 2);
}

bool incBootCounterInEEProm(uint16_t *newVal)
{
    uint16_t cur = 0;
    (void)getBootCounterFromEEProm(&cur);
    cur = (uint16_t)(cur + 1u);
    if (!saveBootCounterToEEProm(cur)) return false;
    if (newVal) *newVal = cur;
    return true;
}
