
// MB_IOexp_U26_Control.c  (optimeret version)
// Styring af IO-expander U26
//
// NOTE: GB0=P24, GB1=P25, GB2=P26 (aktive-HØJE).
// Hvis de i virkeligheden er aktive-LAVE, skal mønstrene inverteres.

#include "definitions.h"
#include "ui_globals.h"
#include "app.h"

// ---------- U26 ADRESSE & REGISTRE ----------
#define U26_ADDR                (0x23)          // 7-bit
#define U26_REG_OUT0            (0x84)          // OUT0..2
#define U26_REG_CFG0            (0x8C)          // CONFIG0..2
#define U26_REG_PUEN0           (0xCC)          // PULL-UP EN 0..2
#define U26_REG_INTMASK0        (0xD4)          // INT MASK 0..2
#define U26_REG_INTEDGE1        (0x62)          // Edge ctrl for port1B (eksempel)

// ---------- PINMAP ----------
#define U26_OUT_MUTE_MASK       (0x80u)         // byte0 bit7
#define U26_OUT_INPUT_MASK      (0x7Fu)         // byte0 bit0..6 (input-relæ 1..6 + digital)
#define U26_OUT_MINUS6_MASK     (0x02u)         // byte2 bit1
#define U26_OUT_PHONO_REG_MASK  (0x04u)         // bit2
#define U26_OUT_DAC_REG_MASK    (0x08u)         // bit3

// ==== PICKUP (MM / MC) =====================================================
// RET HER hvis dit MM/MC-bit er et andet sted eller aktiv-lav:
// Antagelse: U26 OUT2 bit0: 1=MM, 0=MC
#define U26_OUT_PICKUP_MM_BIT   (0x01u)       // OUT2 bit0
#define U26_OUT_PICKUP_MASK     (U26_OUT_PICKUP_MM_BIT)

typedef enum {
    PICKUP_MODE_MM = 0,   // Moving Magnet
    PICKUP_MODE_MC = 1    // Moving Coil
} pickup_mode_e;

// GreenBias (GB0=P24, GB1=P25, GB2=P26) => byte2 bit4..6
#define U26_OUT_GB0_MASK        (0x10u)  // bit4
#define U26_OUT_GB1_MASK        (0x20u)  // bit5
#define U26_OUT_GB2_MASK        (0x40u)  // bit6
#define U26_OUT_GB_ALL          (U26_OUT_GB0_MASK | U26_OUT_GB1_MASK | U26_OUT_GB2_MASK)



// ---------- SKYGGEKOPIER ----------
static uint8_t s_out0 = 0x00;   // OUT0
static uint8_t s_out1 = 0x00;   // OUT1
static uint8_t s_out2 = 0x0C;   // OUT2 (som i din oprindelige kode)

// ---- I2C: blokkerende helpers med timeout ----
#define I2C_WRITE_TIMEOUT_MS       20u   // typisk rigeligt for 3 byte
#define I2C_WRITEREAD_TIMEOUT_MS   50u   // lidt mere luft for read-sekvens

static inline void U26_SetBits2(uint8_t mask, bool on);

static bool I2C2_WaitDone_TimeoutMs(uint32_t timeout_ms)
{
    uint32_t t0 = SYS_TIME_CounterGet();
    uint32_t lim = SYS_TIME_MSToCount(timeout_ms);

    // Vent til evt. *tidligere* transaktion er væk
    while (I2C2_IsBusy())
    {
        if ((SYS_TIME_CounterGet() - t0) >= lim) return false;
    }

    // Nu er bussen ledig ? OK
    return true;
}

static inline bool U26_Write1(uint8_t reg, uint8_t v)
{
    uint8_t buf[2] = { reg, v };

    // 1) Vent til bussen er fri
    if (!I2C2_WaitDone_TimeoutMs(I2C_WRITE_TIMEOUT_MS)) return false;
    //DEBUG_PRINT("U26_write1\n");
    // 2) Start transaktion
    //DEBUG_PRINT("bus ledig\n");
    if (!I2C2_Write(U26_ADDR, buf, 2)) return false;
    
    // 3) Vent til *denne* transaktion er færdig
    uint32_t t0 = SYS_TIME_CounterGet();
    uint32_t lim = SYS_TIME_MSToCount(I2C_WRITE_TIMEOUT_MS);
    while (I2C2_IsBusy())
    {
        if ((SYS_TIME_CounterGet() - t0) >= lim) return false;
    }
    //DEBUG_PRINT("i2c wait done bus ledig igen\n");
    return true;
}

static inline bool U26_Write3(uint8_t reg, uint8_t v0, uint8_t v1, uint8_t v2)
{
    uint8_t buf[4] = { reg, v0, v1, v2 };

    if (!I2C2_WaitDone_TimeoutMs(I2C_WRITE_TIMEOUT_MS)) return false;
    if (!I2C2_Write(U26_ADDR, buf, 4)) return false;

    uint32_t t0 = SYS_TIME_CounterGet();
    uint32_t lim = SYS_TIME_MSToCount(I2C_WRITE_TIMEOUT_MS);
    while (I2C2_IsBusy())
    {
        if ((SYS_TIME_CounterGet() - t0) >= lim) return false;
    }
    return true;
}

static inline bool U26_Read1(uint8_t reg, uint8_t *out)
{
    if (out == NULL) return false;

    if (!I2C2_WaitDone_TimeoutMs(I2C_WRITEREAD_TIMEOUT_MS)) return false;
    if (!I2C2_WriteRead(U26_ADDR, &reg, 1, out, 1)) return false;

    uint32_t t0 = SYS_TIME_CounterGet();
    uint32_t lim = SYS_TIME_MSToCount(I2C_WRITEREAD_TIMEOUT_MS);
    while (I2C2_IsBusy())
    {
        if ((SYS_TIME_CounterGet() - t0) >= lim) return false;
    }
    return true;
}

// Flush: skriv kun de bytes, der ændres
static void U26_FlushChanged(uint8_t old0, uint8_t old1, uint8_t old2)
{
    if (s_out0 != old0 && s_out1 != old1 && s_out2 != old2)
    {
        (void)U26_Write3(U26_REG_OUT0, s_out0, s_out1, s_out2);
        return;
    }
    if (s_out0 != old0) (void)U26_Write1(U26_REG_OUT0 + 0, s_out0);
    if (s_out1 != old1) (void)U26_Write1(U26_REG_OUT0 + 1, s_out1);
    if (s_out2 != old2) (void)U26_Write1(U26_REG_OUT0 + 2, s_out2);
}
// ---------- Små OUT2 AND/OR hjælpere (spejler din gamle &= / |= adfærd) ----------
static inline void U26_Out2_AND(uint8_t and_mask)
{
    uint8_t o0 = s_out0, o1 = s_out1, o2 = s_out2;
    s_out2 &= and_mask;
    U26_FlushChanged(o0, o1, o2);
}
static inline void U26_Out2_OR(uint8_t or_mask)
{
    uint8_t o0 = s_out0, o1 = s_out1, o2 = s_out2;
    s_out2 |= or_mask;
    U26_FlushChanged(o0, o1, o2);
}
// ---------- INIT ----------
void u26InitIoExp(void)
{
    (void)U26_Write3(U26_REG_OUT0, s_out0, s_out1, s_out2);

    // Retning: 0=out, 1=in
    (void)U26_Write3(U26_REG_CFG0, 0x00, 0x07, 0x00);

    // Pull-ups: byte1 bit2
    (void)U26_Write3(U26_REG_PUEN0, 0x00, 0x04, 0x00);

    // Interrupt masker
    (void)U26_Write3(U26_REG_INTMASK0, 0xFF, 0xFB, 0xFF);

    // Edge setup
    (void)U26_Write1(U26_REG_INTEDGE1, 0x20);
}

// ---------- READ ----------
static uint8_t U26_ReadInputs_8_15(void)
{
    uint8_t v = 0;
    if (!U26_Read1(0x01, &v)) { DEBUG_PRINT("u26 read err\r\n"); }
    return v;
}

void inpShiftMuteDelay_Callback (uintptr_t context )
{
    DEBUG_PRINT("inpShift call back\r\n");
 
    appData.inputMuteTimedOutFlg = 1;
 }

void U26_showModulesInstalled(void)
{
  U26_SetBits2(U26_OUT_PHONO_REG_MASK,appData.phonoRegiFlg? 0:1);
  U26_SetBits2(U26_OUT_DAC_REG_MASK,appData.dacRegiFlg? 0:1);
}

void getAmpStatus(void)
{
    uint8_t status = U26_ReadInputs_8_15();

    appData.phonoRegiFlg = (status & PHONO_REGI) ? 1 : 0;
    appData.dacRegiFlg   = (status & DAC_REGI)   ? 1 : 0;
            
    if (appData.dacRegiFlg && appData.curInp > 6)
    {
        DEBUG_PRINT("getDacStatus\r\n");
        getDacStatus();
    }
}
void checkStatus(void)
{
  if(appData.ampStatusChangeFlg || !IO_EXP_INT_Get())
    {
        
      getAmpStatus(); 
        handleDacStatusChange();
        appData.ampStatusChangeFlg = 0;
    }
}
// ---------- PRIMITIVER ----------
static inline void U26_SetBits0(uint8_t mask, bool on)
{
    uint8_t o0 = s_out0, o1 = s_out1, o2 = s_out2;
    s_out0 = on ? (s_out0 | mask) : (s_out0 & (uint8_t)~mask);
    U26_FlushChanged(o0, o1, o2);
}

static inline void U26_SetBits2(uint8_t mask, bool on)
{
    uint8_t o0 = s_out0, o1 = s_out1, o2 = s_out2;
    s_out2 = on ? (s_out2 | mask) : (s_out2 & (uint8_t)~mask);
    U26_FlushChanged(o0, o1, o2);
}

// ---------- API: INPUT MUTE ----------
// Slukker alle input-relæer (P00..P06) men bevarer MUTE-bit (P07).
void inputMuteAll(void)
{
    uint8_t o0 = s_out0, o1 = s_out1, o2 = s_out2;

    // ryd input-bits (0..6), bevar bit7 (mute)
    s_out0 &= U26_OUT_MUTE_MASK;

    U26_FlushChanged(o0, o1, o2);
}

void unMuteInput(void)
{
    uint8_t m = 0;

    if (appData.curInp <= 6)
    {
        m = (uint8_t)(1u << (appData.curInp - 1u));
        DEBUG_PRINT("set input bit: %d  curInp = %d\n",m,appData.curInp);
    }
    else // 7..11
    {
        m = 0x40u;      // digital marker
        DEBUG_PRINT("set input bit: %d  curInp = %d\n",m,appData.curInp);
        //setDigitalInput();
    }
    U26_SetInputRelayBits(m);
}

// ---------- API: MUTE / -6dB ----------
void muteOn(void)  
{
    if(appData.curInp < 7 || appData.oldInp < 7)
    {
        if(appData.oldInp >= 7)
            dacChMute(dacMute);
        inputMuteAll();
    }
    else 
        dacChMute(dacMute);
    
    //CORETIMER_DelayMs(2); 
}

void muteOff(void) 
{   
    const bool isUSB   = (appData.curInp == 7);
    const bool plugged = (dacData.usbPluggedFlg  != 0);    
    
    if(appData.curInp < 7)
        unMuteInput(); 
    else
    {
        unMuteInput(); 
        if(isUSB)
        {
           if(plugged)
              dacChMute(dacUnMute);
        }
        else
          dacChMute(dacUnMute);  
    }
    //CORETIMER_DelayMs(10); 
    //UpdateVolume();
    //CORETIMER_DelayMs(2); 
}


//void mute (void) 
//{
//    appData.muteFlg = !appData.muteFlg;
//    appData.muteToggleFlg = 1;
//    
//}

void irToggleMute(void)
{
   if(appData.muteToggleFlg)
    {
      appData.muteFlg = !appData.muteFlg;
      appData.muteFlg? muteOn() : muteOff();
      //printf("Mute : %s\r\n",appData.muteFlg?"muted":"unmuted");
      
      appData.muteToggleFlg = 0;
    }

}
void toggleMute(void)
{
//   if(appData.muteToggleFlg)
//    {
      appData.muteFlg = !appData.muteFlg;
      appData.muteFlg? muteOn() : muteOff();
      
      appData.muteToggleFlg = 0;
//    }

}

void outputMuteOn(void)  { U26_SetBits0(U26_OUT_MUTE_MASK, false); }
void outputMuteOff(void) { U26_SetBits0(U26_OUT_MUTE_MASK, true ); }

void minus6dBOn(void)  { U26_SetBits2(U26_OUT_MINUS6_MASK, true ); DEBUG_PRINT("minus6dBOn\r\n");  }
void minus6dBOff(void) { U26_SetBits2(U26_OUT_MINUS6_MASK, false); DEBUG_PRINT("minus6dBOff\r\n"); }

// ---------- API: GREENBIAS ----------
static inline void setGreenBiasPattern(uint8_t pattern_0_7)
{
    uint8_t o0 = s_out0, o1 = s_out1, o2 = s_out2;
    s_out2 = (uint8_t)((s_out2 & (uint8_t)~U26_OUT_GB_ALL) | (uint8_t)((pattern_0_7 & 0x7u) << 4));
    U26_FlushChanged(o0, o1, o2);
}

void setGreenBiasMode(greenbias_mode_t mode)
{
    switch (mode)
    {
        case GB_MODE_OFF:   // GB0
            setGreenBiasPattern(0b001);
            break;
        case GB_MODE_MID:   // GB1
            setGreenBiasPattern(0b010);
            break;
        case GB_MODE_LOW:   // GB2
            setGreenBiasPattern(0b100);
            break;
        case GB_MODE_HIGH:  // GB1+GB2
            setGreenBiasPattern(0b000);
            break;
        default:
            setGreenBiasPattern(0b001); // failsafe: alt slukket
            break;
    }
}

// ---------- API: GreenBias automatisk ud fra curLvl og greenBias ----------
void U26_UpdateGreenBiasFromLevel(void)
{
    greenbias_mode_t mode = GB_MODE_OFF;   // default failsafe

    if (appData.greenBias == 0)
    {
        if (appData.curLvl <= 26)
            mode = GB_MODE_LOW;
        else if (appData.curLvl <= 46)
            mode = GB_MODE_MID;
        else if (appData.curLvl <= 84)
            mode = GB_MODE_HIGH;
    }
    else if (appData.greenBias == 1)
    {
        if (appData.curLvl <= 38)
            mode = GB_MODE_LOW;
        else if (appData.curLvl <= 58)
            mode = GB_MODE_MID;
        else if (appData.curLvl <= 84)
            mode = GB_MODE_HIGH;
    }
    
    setGreenBiasMode(mode);
}
// Sæt HW-bit i OUT2 efter den gemte selection.
// MM: sæt bit -> 1; MC: ryd bit -> 0.
void U26_ApplyPickupHwFromSelection(void)
{
    const bool mm = (appData.pickupSelection == movingMagnet);

    uint8_t o0 = s_out0, o1 = s_out1, o2 = s_out2;

    if (mm)  s_out2 |=  U26_OUT_PICKUP_MM_BIT;   // MM
    else     s_out2 &= (uint8_t)~U26_OUT_PICKUP_MM_BIT;  // MC

    U26_FlushChanged(o0, o1, o2);
}

// ---------- INPUT RELÆ ----------
void U26_SetInputRelayBits(uint8_t relayMaskByte0)
{
    uint8_t o0 = s_out0, o1 = s_out1, o2 = s_out2;
    s_out0 = (s_out0 & U26_OUT_MUTE_MASK) | (relayMaskByte0 & U26_OUT_INPUT_MASK);
    U26_FlushChanged(o0, o1, o2);
}

void setInputRelay(void)
{
    uint8_t m = 0;

    if (appData.curInp <= 6)
    {
        m = (uint8_t)(1u << (appData.curInp - 1u));
        DEBUG_PRINT("set input bit: %d  curInp = %d\n",m,appData.curInp);
    }
    else // 7..11
    {
        
        dacChMute(dacMute);
        m = 0x40u;      // digital marker
        DEBUG_PRINT("set input bit: %d  curInp = %d\n",m,appData.curInp);
        //setDigitalInput();
        if (appData.curInp != 7 || dacData.usbPluggedFlg)
            dacChMute(dacUnMute);
    }
    
    U26_SetInputRelayBits(m);
}

// ---------- INPUT SKIFT ----------
//void setInputMuteTiming(void)
//{
//    if (appData.oldInp < 7  || appData.curInp < 7 || appData.startupFlg)
//    {
//        if (appData.inputShiftMuteDelayHandle)
//            SYS_TIME_TimerDestroy(appData.inputShiftMuteDelayHandle);
//
//        uint32_t delayMs = (appData.curLvl > 0 || AvSelected(appData.avInp, appData.curInp)) ? 2000u : 200u;
//        appData.inputShiftMuteDelayHandle =
//            SYS_TIME_CallbackRegisterMS(inpShiftMuteDelay_Callback, 0, delayMs, SYS_TIME_SINGLE);
//
//        appData.inputMuteActiveFlg = 1;
//    }
//}
void StartInputMuteWindow(uint32_t delayMs)
{
    appData.inputMuteActiveFlg = 1u;
    appData.inputMuteUntilMs = millis32() + delayMs;
}

void setInput(void)
{
    if (appData.curInp == appData.oldInp) return;

    if (appData.oldInp < 7 || appData.curInp < 7)
    {
        muteOn();
        appData.inputMuteActiveFlg = 1;
        CORETIMER_DelayMs(20);
    }
    
    if(appData.curInp >= 7)
    {
        setDigitalInput();
        digiCacheInvalid = true;
    }
    
    //if (appData.curInp == appData.avInp) setAvLevel(); else UpdateVolume();

    //setInputRelay();

    if (appData.curInp == 4 || appData.curInp == 5)  minus6dBOn(); else minus6dBOff();
    
    uint32_t delayMs = (appData.curLvl > 0 || AvSelected(appData.avInp, appData.curInp)) ? 2000u : 200u;
    
    StartInputMuteWindow(delayMs);
    
    appData.oldInp = appData.curInp;
}

void handlePhonoConfiguration(void)
{
    if (appData.phonoRegiFlg)
    {
        appData.maxInp = 6;

        // Hvis MC valgt, anvend dit oprindelige AND-maskemønster:
        if (appData.pickupSelection == movingCoil)
            U26_Out2_AND(PICKUP_MC);           // svarer til: appData.u26Byte2 &= PICKUP_MC;

        // LED ON efter dit oprindelige mønster:
        U26_Out2_AND(PHONO_REG_LED_ON);        // svarer til: appData.u26Byte2 &= PHONO_REG_LED_ON;
    }
    else
    {
        // LED OFF efter dit oprindelige mønster:
        U26_Out2_OR(PHONO_REG_LED_OFF);        // svarer til: appData.u26Byte2 |= PHONO_REG_LED_OFF;

        if (appData.curInp == 6)
            appData.curInp = 1;
    }
}

void handleDacConfiguration(void)
{
    if (appData.dacRegiFlg)
    {
        appData.maxInp = 11;

        // LED ON efter dit oprindelige mønster:
        U26_Out2_AND(DAC_REG_LED_ON);          // svarer til: appData.u26Byte2 &= DAC_REG_LED_ON;

        // Din init-sekvens uændret:
        dacU26InitIoExp();
        asyncOn();
        CORETIMER_DelayMs(500);
        dacSetup();
        dirSetup();
    }
    else
    {
        // LED OFF efter dit oprindelige mønster:
        U26_Out2_OR(DAC_REG_LED_OFF);          // svarer til: appData.u26Byte2 |= DAC_REG_LED_OFF;

        if (appData.curInp > 6)
            appData.curInp = 1;
    }
}

void InputMute_Service(void)
{
    bool avSelected;

    if (!appData.inputMuteActiveFlg)
        return;

    if ((int32_t)(millis32() - appData.inputMuteUntilMs) < 0)
        return;

    avSelected = AvSelected(appData.avInp, appData.curInp);

    if ((avSelected || appData.curLvl > 0u) && !appData.muteFlg)
    {
        setInputRelay();

        if (avSelected)
            setAvLevel();
        else
            UpdateVolume();
    }

    appData.inputMuteActiveFlg = 0u;
    appData.inputMuteUntilMs = 0u;
}
//void inputMuteTimeOut(void)
//{
//    if(appData.inputMuteTimedOutFlg)
//    {
//           if((appData.avFlg || appData.curLvl > 0)  && !appData.muteFlg)
//           {
//              setInputRelay();//muteOff();
//              if (AvSelected(appData.avInp, appData.curInp)) setAvLevel(); else UpdateVolume();
//              DEBUG_PRINT("mute off\r\n");
//            }
//            appData.inputMuteTimedOutFlg = 0;
//            appData.inputMuteActiveFlg = 0;
//    }
//    
//}

////////////#include "definitions.h" // indeholder app.h, system headers, legato types mm.
//////////////#include "gfx/legato/generated/screen/le_gen_screen_actionScreen.h" // for actionScreen_dispOnButton
//////////////#include "gfx/legato/generated/screen/le_gen_screen_simpleViewScreen.h" // for simpleViewScreen_dispOnButton
////////////#include "ui_globals.h"
////////////#include "app.h"
////////////
////////////
////////////static uint8_t writeBuffer[WRITE_BUFFER_SIZE];
////////////static uint8_t readBuffer[READ_BUFFER_SIZE];
////////////
////////////
////////////void inpShiftMuteDelay_Callback (uintptr_t context )
////////////{
////////////    DEBUG_PRINT("inpShift call back\r\n");
////////////    if((appData.avFlg || appData.curLvl > 0)  && !appData.muteFlg)
////////////    {
////////////        muteOff();
////////////        DEBUG_PRINT("inp mute off\r\n");
////////////    }
////////////    appData.inputMuteActiveFlg = 0;
//////////// }
////////////
////////////
////////////
////////////void checkStatus(void)
////////////{
////////////  if(appData.ampStatusChangeFlg || !IO_EXP_INT_Get())
////////////    {
////////////        getAmpStatus(); 
////////////        handleDacStatusChange();
////////////        appData.ampStatusChangeFlg = 0;
////////////    }
////////////}
////////////
////////////
////////////void u26InitIoExp (void)
////////////{
////////////    appData.u26Byte0 = 0x00;
////////////    appData.u26Byte1 = 0x00;
////////////    appData.u26Byte2 = 0x0C;
////////////
////////////    writeBuffer[0] = 0x84; //Peger på register 0x84
////////////    writeBuffer[1] = appData.u26Byte0; //0x00; //U21 PIN 0-7
////////////    writeBuffer[2] = appData.u26Byte1; //0x18; //U21 PIN 8-15
////////////    writeBuffer[3] = appData.u26Byte2;
////////////    I2C2_Write(0x23, &writeBuffer[0], 4);
////////////    
////////////    CORETIMER_DelayMs(7);
////////////    
////////////    writeBuffer[0] = 0x8C; //Peger på register 0x8c
////////////    writeBuffer[1] = 0x00; //U21 PIN 0-7
////////////    writeBuffer[2] = 0x07; //U21 PIN 8-15
////////////    writeBuffer[3] = 0x00; //U21 PIN 16-23
////////////    I2C2_Write(0x23, &writeBuffer[0], 4);
////////////    CORETIMER_DelayMs(10);
////////////    
////////////    writeBuffer[0] = 0xCC; //Peger på register 0x4C Enable pull-Up
////////////    writeBuffer[1] = 0x00; //U21 PIN 0-7
////////////    writeBuffer[2] = 0x04; //U21 PIN 8-15
////////////    writeBuffer[3] = 0x00; //U21 PIN 16-23
////////////    I2C2_Write(0x23, &writeBuffer[0], 4);
////////////    CORETIMER_DelayMs(10);
////////////    writeBuffer[0] = 0xD4; //Peger på register 0x4C Interrupt Mask Register
////////////    writeBuffer[1] = 0xFF; //U21 PIN 0-7
////////////    writeBuffer[2] = 0xFB; //U21 PIN 8-15
////////////    writeBuffer[3] = 0xFF; //U21 PIN 16-23
////////////    I2C2_Write(0x23, &writeBuffer[0], 4);
////////////    CORETIMER_DelayMs(10);
////////////
////////////    writeBuffer[0] = 0x62; //Peger på register 0x63 Interrupt Edge port1B
////////////    writeBuffer[1] = 0x20; //Set port17 til at give interrupt ved Negativ flanke
////////////    I2C2_Write(0x23, &writeBuffer[0], 2);
////////////    CORETIMER_DelayMs(5);
////////////    
////////////    
////////////}
////////////
////////////uint8_t u26ReadInputs (void)
////////////{
////////////    uint8_t input_8_15;
////////////    
////////////    writeBuffer[0] = 1; //Peger på register 1
////////////    while(I2C2_IsBusy());
////////////    if(!I2C2_WriteRead(0x23, writeBuffer, 1, readBuffer , 1)) 
////////////    {
////////////        DEBUG_PRINT("i2c read error"); 
////////////        return 0;
////////////    }
////////////    CORETIMER_DelayMs(7);
////////////    
////////////    input_8_15 = readBuffer[0];
////////////    //DEBUG_PRINT("\r\nU21: %x\r\n",input_8_15); 
////////////    return input_8_15;
////////////    
////////////}
////////////
////////////void getAmpStatus(void)
////////////{
////////////    uint8_t status;
////////////    status = u26ReadInputs();
////////////    
////////////    //DEBUG_PRINT("Amp Status %02x\r\n",status);
////////////    //appData.errorStatus = status >> 8;
////////////    // appData.errorStatus &= 0x0F;
////////////    
////////////    if(status & PHONO_REGI)
////////////      appData.phonoRegiFlg = 1;
////////////    else
////////////      appData.phonoRegiFlg = 0;
////////////    
////////////    if(status & DAC_REGI)
////////////      appData.dacRegiFlg = 1;
////////////    else
////////////      appData.dacRegiFlg = 0;
////////////    
////////////    if(appData.dacRegiFlg && appData.curInp > 6)
////////////    {
////////////        DEBUG_PRINT("get DAC Status \n");
////////////        getDacStatus ();
////////////    }
////////////}
////////////
////////////void u26WriteOutputs (uint8_t u26Byte0,uint8_t u26Byte2)
////////////{
////////////    writeBuffer[0] = 0x84; //Peger på register 4
////////////    writeBuffer[1] = u26Byte0; //U21 Output 0-7
////////////    I2C2_Write(U26_address, &writeBuffer[0], 2);
////////////    CORETIMER_DelayMs(2);
////////////    
////////////    writeBuffer[0] = 0x86; //Peger på register 4
////////////    writeBuffer[1] = u26Byte2; //U21 Output 8-15
////////////    I2C2_Write(U26_address, &writeBuffer[0], 2);
////////////    CORETIMER_DelayMs(2);
////////////}
////////////
////////////void mute (void)
////////////{
////////////    if(!appData.muteFlg)
////////////    {
////////////      appData.u26Byte0 &= 0x7F; // Mute
////////////      appData.muteFlg = 1;
////////////    }
////////////    else
////////////    {
////////////      appData.u26Byte0 |= 0x80; // Unmute  
////////////      appData.muteFlg = 0;
////////////    }
////////////    writeBuffer[0] = 0x84; //Peger på register 4
////////////    writeBuffer[1] = appData.u26Byte0;
////////////    I2C2_Write(U26_address, &writeBuffer[0], 2);
////////////    CORETIMER_DelayMs(2);
////////////
////////////    //u26WriteOutputs (appData.u26Byte0,appData.u26Byte2);
////////////    //DEBUG_PRINT("mute written\r\n");
////////////}
////////////void muteOn (void)
////////////{
////////////    appData.u26Byte0 &= 0x7F; // Mute
////////////    writeBuffer[0] = 0x84; //Peger på register 4
////////////    writeBuffer[1] = appData.u26Byte0;
////////////    I2C2_Write(U26_address, &writeBuffer[0], 2);
////////////    CORETIMER_DelayMs(2);
////////////    
//////////////    u26WriteOutputs (appData.u26Byte0,appData.u26Byte2);
////////////}
////////////void muteOff (void)
////////////{
////////////    appData.u26Byte0 |= 0x80; // Unmute  
//////////////    u26WriteOutputs (appData.u26Byte0,appData.u26Byte2);
////////////    writeBuffer[0] = 0x84; //Peger på register 4
////////////    writeBuffer[1] = appData.u26Byte0;
////////////    I2C2_Write(U26_address, &writeBuffer[0], 2);
////////////    CORETIMER_DelayMs(2);
////////////    
////////////}
////////////
////////////void minus6dBOn (void)
////////////{
////////////    appData.u26Byte2 |= 0x02; // -6 dB ON 
////////////    writeBuffer[0] = 0x86; //Peger på register 4
////////////    writeBuffer[1] = appData.u26Byte2;
////////////    I2C2_Write(U26_address, &writeBuffer[0], 2);  
////////////    DEBUG_PRINT("minus6dBOn\r\n");
////////////    //u26WriteOutputs (appData.u26Byte0,appData.u26Byte2);
////////////}
////////////void minus6dBOff (void)
////////////{
////////////    appData.u26Byte2 &= 0xFd; // -6 dB OFF  
////////////    writeBuffer[0] = 0x86; //Peger på register 4
////////////    writeBuffer[1] = appData.u26Byte2;
////////////    I2C2_Write(U26_address, &writeBuffer[0], 2);    
////////////    DEBUG_PRINT("minus6dBOff\r\n");
////////////    //u26WriteOutputs (appData.u26Byte0,appData.u26Byte2);
////////////}
////////////
////////////void setInputRelay(void)
////////////{
////////////    uint8_t calculatedInpValue = 0;
////////////    if(appData.curInp <= 6)
////////////    {
////////////      calculatedInpValue = 1 << (appData.curInp - 1);
////////////    }
////////////    else if (appData.curInp >= 7 && appData.curInp <= 11)
////////////    {
////////////      dacChMute(dacMute);
////////////      calculatedInpValue = 0x40;
////////////      setDigitalInput();
////////////      if(appData.curInp != 7 || dacData.usbPluggedFlg)
////////////        dacChMute(dacUnMute);
////////////    }
////////////
////////////    writeBuffer[0] = 0x84; //Peger på register 4
////////////    appData.u26Byte0 &= 0x80;
////////////    appData.u26Byte0 |= calculatedInpValue;
////////////    writeBuffer[1] = appData.u26Byte0;
////////////    I2C2_Write(U26_address, &writeBuffer[0], 2);
////////////    CORETIMER_DelayMs(2);    
////////////    //DEBUG_PRINT("Input: %d\r\n",calculatedInpValue);
////////////}
////////////
////////////void setInputMuteTiming(void)
////////////{
////////////    if(appData.oldInp < 7  || appData.curInp < 7 || appData.startupFlg)
////////////    {
////////////        if(appData.inputShiftMuteDelayHandle)
////////////            SYS_TIME_TimerDestroy(appData.inputShiftMuteDelayHandle);
////////////
////////////        if(appData.curLvl > 0 || appData.curInp == appData.avInp)
////////////            appData.inputShiftMuteDelayHandle = SYS_TIME_CallbackRegisterMS(inpShiftMuteDelay_Callback, 0, 2000, SYS_TIME_SINGLE);
////////////        else
////////////            appData.inputShiftMuteDelayHandle = SYS_TIME_CallbackRegisterMS(inpShiftMuteDelay_Callback, 0, 200, SYS_TIME_SINGLE);
////////////            
////////////        appData.inputMuteActiveFlg = 1;
////////////
////////////    }    
////////////}
////////////void setInput(void)
////////////{
////////////    
////////////    //DEBUG_PRINT("set Input old: %d  Cur: %d\r\n", appData.oldInp, appData.curInp);
////////////    if(appData.curInp != appData.oldInp)
////////////    {
////////////    
////////////    if(appData.oldInp < 7 || appData.curInp < 7)
////////////    {
////////////      muteOn();
////////////      appData.inputMuteActiveFlg = 1;
////////////      CORETIMER_DelayMs(20);
////////////    }
////////////   
////////////    if(appData.curInp == appData.avInp)
////////////        setAvLevel();
////////////    else
////////////        UpdateVolume();
////////////
////////////    setInputRelay();
////////////    
////////////    if(appData.curInp == 4 || appData.curInp == 5)
////////////        minus6dBOn();
////////////    else
////////////        minus6dBOff();
////////////    
////////////    setInputMuteTiming();
////////////    
////////////    appData.oldInp = appData.curInp;
////////////    }
////////////}
////////////
