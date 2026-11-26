#include "definitions.h" // indeholder app.h, system headers, legato types mm.
#include "ui_globals.h"
#include "app.h"

static uint8_t writeBuffer[32];
static uint8_t readBuffer[32];


void getDacStatus (void)
{
    uint16_t status;
    status = readDacIoExpInputs();
    
    dacData.usbFs           = status & 0x000F;
    dacData.signalLockFlg   = status & 0x0100;
    dacData.dirIntFlg       = status & 0x0400;
    dacData.usbCharging     = status & 0x0800;
    dacData.dsdOnFlg        = status & 0x1000;
    dacData.usbPluggedFlg   = status & 0x2000;
    dacData.dacMuteFlg      = status & 0x4000;
    
    g_digiInfoDirty = true;
//    if(legato_getCurrentScreen() == screenID_actionScreen)
//    {
//        DEBUG_PRINT("pre update infopanel: %x\n", status); 
//        updateDigiInfoPanel();  
//    }
    
}
#define I2C_TIMEOUT_US  20000u  // 20 ms, justr efter 100k/400kHz

static bool wait_i2c_done_us(uint32_t us)
{
    uint32_t f = CORETIMER_FrequencyGet();
    uint32_t ticks_per_us = f / 1000000u;
    if (ticks_per_us == 0u) ticks_per_us = 1u;

    uint32_t start = CORETIMER_CounterGet();
    uint32_t timeout_ticks = us * ticks_per_us;

    while (I2C2_IsBusy())
    {
        if ((uint32_t)(CORETIMER_CounterGet() - start) >= timeout_ticks)
            return false;
    }
    return true;
}


#define I2C_WAIT_OR_RET0() \
    do { if (!wait_i2c_done_us(I2C_TIMEOUT_US)) { DEBUG_PRINT("I2C timeout\r\n"); return 0; } } while (0)

#define I2C_WAIT_OR_RET() \
    do { if (!wait_i2c_done_us(I2C_TIMEOUT_US)) { DEBUG_PRINT("I2C timeout\r\n"); return; } } while (0)

uint16_t readDacIoExpInputs(void)
{
    // 1) Vent p fri bus (med timeout)
    I2C_WAIT_OR_RET0();

    // 2) Peg p frste input-register (Port 0 = 0x00)
    writeBuffer[0] = 0x00;

    // 3) Start WriteRead: skriv 1 byte adresse, ls 2 bytes data
    if (!I2C2_WriteRead(dacIoExpAddress, writeBuffer, 1, readBuffer, 2))
    {
        DEBUG_PRINT("I2C WriteRead start failed\r\n");
        return 0;
    }

    I2C_WAIT_OR_RET0();

    // 5) Saml 16-bit vrdi: [Port1]<<8 | [Port0]
    uint16_t v = ((uint16_t)readBuffer[1] << 8) | (uint16_t)readBuffer[0];
    return v;
}
//uint16_t readDacIoExpInputs (void)
//{
//    uint16_t input_0_15;
//    
//    writeBuffer[0] = 0; //Peger p register 1
//    while(I2C2_IsBusy());
//    if(!I2C2_WriteRead(dacIoExpAddress, writeBuffer, 1, readBuffer , 3)) 
//    {
//        DEBUG_PRINT("i2c read error"); 
//        return 0;
//    }
//    CORETIMER_DelayMs(7);
//    
//    input_0_15 = readBuffer[1];
//    input_0_15 = input_0_15 << 8;
//    input_0_15 |= readBuffer[0];
//    return input_0_15;
//    
//}
void setDacIOExpOut(uint8_t data)
{
    writeBuffer[0] = 0x6; //Peger p register 4
    writeBuffer[1] = data; //U26 Output 0-2 Port2
    I2C_WAIT_OR_RET();
    I2C2_Write(dacIoExpAddress, &writeBuffer[0], 2);
    I2C_WAIT_OR_RET();
}

void dsdLpOn (void)
{  
    dacData.dacIoExpOutByte |= 0x04; // DSD LP Filter ON
    setDacIOExpOut(dacData.dacIoExpOutByte);        
}

void dsdLpOff (void)
{
    dacData.dacIoExpOutByte &= 0xFB; // DSD LP Filter OFF
    setDacIOExpOut(dacData.dacIoExpOutByte);        
}


// --- HW helpers (ingen UI) ---
static void dacApplyPcmFilter_NoUI(uint8_t rawIdx)
{
    uint8_t idx = (rawIdx >= 1 && rawIdx <= 7) ? rawIdx : 1;
    static const uint8_t regVal[8] = { 0x00, 0xB8, 0xB9, 0xBA, 0xBC, 0xBD, 0xBE, 0xBF };

    writeBuffer[0] = dacReg88;
    writeBuffer[1] = regVal[idx];
    I2C2_Write(dacAddress, &writeBuffer[0], 2);

    uint32_t t0 = SYS_TIME_CounterGet();
    while (I2C2_IsBusy())
        if (SYS_TIME_CountToMS(SYS_TIME_CounterGet() - t0) > 5U) return;
}

// --- n sand kilde til HW-tilstand p digitale inputs ---
static void ApplyDigiAudioState(void)
{
    if (appData.curInp <= 6 || !appData.dacRegiFlg)
        return;

    const bool isUSB   = (appData.curInp == 7);
    const bool locked  = (dacData.signalLockFlg != 0);
    const bool plugged = (dacData.usbPluggedFlg  != 0);

    if (isUSB)
    {
        // DSD/PCM hardware
        if (dacData.dsdOnFlg)
        {
            if (dacData.dsdLpFilter) dsdLpOn();
            else                     dsdLpOff();
        }
        else
        {
            // PCM-visning: LP altid OFF og skriv PCM-filter til DAC
            dsdLpOff();
            dacApplyPcmFilter_NoUI(dacData.pcmFilter);
        }

        // USB mute/unmute hard gate (skrmuafhngig)
        if (plugged && locked && !appData.muteFlg) dacChMute(dacUnMute);
        else                   dacChMute(dacMute);
    }
    else
    {
        // SPDIF/AES/TOS: Kun PCM-filter til DAC; mute hndteres af automute/analog mute
        dacApplyPcmFilter_NoUI(dacData.pcmFilter);
    }
}

void handleDacStatusChange(void)
{
    if (appData.dacRegiFlg)
    {
        if (!dacData.usbPluggedFlg && appData.curInp == 7)
            dacSetupSpDif();
        else if (dacData.usbPluggedFlg && appData.curInp == 7)
            dacSetupI2s();
    }

    // NYT: hold HW i sync uanset screen
    ApplyDigiAudioState();
}

//void handleDacStatusChange(void)
//{
//    if(appData.dacRegiFlg)
//    {
//        if(!dacData.usbPluggedFlg && appData.curInp == 7)
//        {
//            dacSetupSpDif();
//            dacChMute(dacMute);
//            dacData.dacUnpluggedMuteFlg = 1;
//        }
//        else if (dacData.usbPluggedFlg && appData.curInp == 7)
//        {
//            dacSetupI2s();
//            dacChMute(dacUnMute);
//            dacData.dacUnpluggedMuteFlg = 0;
//        }
//        else if (appData.curInp > 7 && dacData.dacUnpluggedMuteFlg)
//            dacChMute(dacUnMute);
//        
//    }
//}

void dacSetup(void)
{
  dacEnableGpio();  
  setDacSysModeConfig();
  dacGpioConfig();
  tdmChConfig();
  dacsetVolRateUp(1);
  dacsetVolRateDwn(1);
  dacSetPcmFilter();
  dacSetupSpDif ();

  dacSetupI2s();
  setDacSpdifInput();
  setInputFormat(modeI2sPcm);
  
  setAutoMuteEnableOff();
  setMuteRampToGndOff();
  dacOn();
  toggleMasterSlaveBit();
  
  i2sDirOn();
  CORETIMER_DelayUs (1000);  
  setAutoMuteEnableOn();
  
 
}

void dacOn (void)
{
    writeBuffer[0] = dacReg0;
    writeBuffer[1] = 0x02;
    I2C_WAIT_OR_RET();
    I2C2_Write(dacAddress, &writeBuffer[0], 2);
    I2C_WAIT_OR_RET();
}


void dacSetupI2s (void)
{
    writeBuffer[0] = dacReg59;
    writeBuffer[1] = 0x01;
    I2C_WAIT_OR_RET();
    I2C2_Write(dacAddress, &writeBuffer[0], 2);
    I2C_WAIT_OR_RET();
    
}
void dacSetupSpDif (void)
{
    writeBuffer[0] = dacReg59;
    writeBuffer[1] = 0x04;
    I2C_WAIT_OR_RET();
    I2C2_Write(dacAddress, &writeBuffer[0], 2);
    I2C_WAIT_OR_RET();
}

void tdmChConfig (void)
{
    writeBuffer[0] = dacReg64;
    writeBuffer[1] = 0x00;
    writeBuffer[2] = 0x01;
    writeBuffer[3] = 0x20;
    writeBuffer[4] = 0x21;
    writeBuffer[5] = 0x40;
    writeBuffer[6] = 0x41;
    writeBuffer[7] = 0x60;
    writeBuffer[8] = 0x61; 
    I2C_WAIT_OR_RET();
    I2C2_Write(dacAddress, &writeBuffer[0], 9);
    I2C_WAIT_OR_RET();
    
}

void setAutoMuteEnableOff(void)
{
   writeBuffer[0] = dacReg123;
   writeBuffer[1] = 0x00;
   I2C_WAIT_OR_RET();
   I2C2_Write(dacAddress, &writeBuffer[0], 2);
   I2C_WAIT_OR_RET();
}

void setAutoMuteEnableOn(void)
{
   writeBuffer[0] = dacReg123;
   writeBuffer[1] = 0xFF;
   I2C_WAIT_OR_RET();
   I2C2_Write(dacAddress, &writeBuffer[0], 2);
   I2C_WAIT_OR_RET();
}


void setMuteRampToGndOff(void)
{
   writeBuffer[0] = dacReg125;
   writeBuffer[1] = 0x00;
   I2C_WAIT_OR_RET();
   I2C2_Write(dacAddress, &writeBuffer[0], 2);
   I2C_WAIT_OR_RET();
}

void setMuteRampToGndOn(void)
{
   writeBuffer[0] = dacReg125;
   writeBuffer[1] = 0x08;
   I2C_WAIT_OR_RET();
   I2C2_Write(dacAddress, &writeBuffer[0], 2);
   I2C_WAIT_OR_RET();
}


void dacOff (void)
{
    writeBuffer[0] = dacReg0;
    writeBuffer[1] = 0x00;
    I2C_WAIT_OR_RET();
    I2C2_Write(dacAddress, &writeBuffer[0], 2);
    I2C_WAIT_OR_RET();
}

void setDacSysModeConfig(void)
{
  writeBuffer[0] = dacReg1;
  writeBuffer[1] = 0xBF; //Enables decoding of all formats
  I2C_WAIT_OR_RET();
  I2C2_Write(dacAddress, &writeBuffer[0], 2);
  I2C_WAIT_OR_RET();
}



// =========================
// PCM filter: split HW vs UI
// =========================

static uint8_t PcmFilter_ToHwVal(uint8_t f)
{
    switch (f)
    {
        case 1: return 0xB8;
        case 2: return 0xB9;
        case 3: return 0xBA;
        case 4: return 0xBC;
        case 5: return 0xBD;
        case 6: return 0xBE;
        case 7: return 0xBF;
        default: return 0xB8;
    }
}

void DacHw_ApplyPcmFilterFromState(void)
{
    // PCM filter giver ikke mening i USB-DSD mode
    if (appData.curInp == 7u && dacData.dsdOnFlg)
        return;

    uint8_t f = dacData.pcmFilter;
    if (f < 1u || f > 7u)
    {
        f = 4u;              // behold jeres default
        dacData.pcmFilter = f;
    }

    // undga at spamme I2C, selvom UI bruger dacData.oldPcmFilter som cache
    static uint8_t s_applied = 0xFFu;
    if (s_applied == f)
        return;

    uint8_t wb[2];
    wb[0] = dacReg88;
    wb[1] = PcmFilter_ToHwVal(f);

    I2C_WAIT_OR_RET();
    I2C2_Write(dacAddress, &wb[0], 2);
    I2C_WAIT_OR_RET();

    s_applied = f;
    return;
}

void DacUi_SyncDigiGain_CurrentScreen(void)
{
    // UI-only. INGEN HW her.

    const uint32_t scr = legato_getCurrentScreen();
    const bool on0dB = (dacData.digiGain != 0u);   // 1 = 0 dB, 0 = -6 dB (som i din OnShow)

    if (scr == screenID_actionScreen)
    {
        // Kun én må være synlig
        actionScreen_gain0db->fn->setVisible(actionScreen_gain0db, on0dB ? LE_TRUE : LE_FALSE);
        actionScreen_gainMinus6dB->fn->setVisible(actionScreen_gainMinus6dB, on0dB ? LE_FALSE : LE_TRUE);
        return;
    }

    if (scr == screenID_dacGainSimpleView)
    {
        // Her har du også to labels: dacGainSimpleView_gain0dB og _gainMinus6dB
        dacGainSimpleView_gain0dB->fn->setVisible(dacGainSimpleView_gain0dB, on0dB ? LE_TRUE : LE_FALSE);
        dacGainSimpleView_gainMinus6dB->fn->setVisible(dacGainSimpleView_gainMinus6dB, on0dB ? LE_FALSE : LE_TRUE);
        return;
    }

    // digitalSetupScreen håndteres i OnShow og events (som du allerede gør)
}

void DacUi_SyncPcmFilterLabels_ActionScreen(uint8_t f)
{
    // UI-only: ActionScreen PCM filter labels

    if (legato_getCurrentScreen() != screenID_actionScreen)
        return;

    // PCM labels må IKKE vises i USB + DSD mode
    const bool showPcm =
        !((appData.curInp == 7u) && (dacData.dsdOnFlg != 0u));

    if (!showPcm)
    {
        // Skjul PCM filter labels
        actionScreen_digiInfoFilterLabel1->fn->setVisible(actionScreen_digiInfoFilterLabel1, LE_FALSE);
        actionScreen_digiInfoFilterLabel2->fn->setVisible(actionScreen_digiInfoFilterLabel2, LE_FALSE);
        actionScreen_digiInfoFilterLabel3->fn->setVisible(actionScreen_digiInfoFilterLabel3, LE_FALSE);
        return;
    }

    // ---------- NYT: PCM ejer linjen -> DSD LP SKAL skjules ----------
    actionScreen_dsdLpOn->fn->setVisible(actionScreen_dsdLpOn, LE_FALSE);
    actionScreen_dsdLpOff->fn->setVisible(actionScreen_dsdLpOff, LE_FALSE);
    // ----------------------------------------------------------------

    // PCM mode: vis labels og sync tekst
    actionScreen_digiInfoFilterLabel1->fn->setVisible(actionScreen_digiInfoFilterLabel1, LE_TRUE);
    actionScreen_digiInfoFilterLabel2->fn->setVisible(actionScreen_digiInfoFilterLabel2, LE_TRUE);
    actionScreen_digiInfoFilterLabel3->fn->setVisible(actionScreen_digiInfoFilterLabel3, LE_TRUE);

    switch (f)
    {
        case 1:
            actionScreen_digiInfoFilterLabel1->fn->setString(actionScreen_digiInfoFilterLabel1, (leString*)&string_pcmFilt1);
            actionScreen_digiInfoFilterLabel2->fn->setString(actionScreen_digiInfoFilterLabel2, (leString*)&string_MinPhase12);
            actionScreen_digiInfoFilterLabel3->fn->setString(actionScreen_digiInfoFilterLabel3, (leString*)&string_emtyString);
            break;

        case 2:
            actionScreen_digiInfoFilterLabel1->fn->setString(actionScreen_digiInfoFilterLabel1, (leString*)&string_pcmFilt2);
            actionScreen_digiInfoFilterLabel2->fn->setString(actionScreen_digiInfoFilterLabel2, (leString*)&string_LinPhase12);
            actionScreen_digiInfoFilterLabel3->fn->setString(actionScreen_digiInfoFilterLabel3, (leString*)&string_Apodiz12);
            break;

        case 3:
            actionScreen_digiInfoFilterLabel1->fn->setString(actionScreen_digiInfoFilterLabel1, (leString*)&string_pcmFilt3);
            actionScreen_digiInfoFilterLabel2->fn->setString(actionScreen_digiInfoFilterLabel2, (leString*)&string_LinPhase12);
            actionScreen_digiInfoFilterLabel3->fn->setString(actionScreen_digiInfoFilterLabel3, (leString*)&string_FastRoll12);
            break;

        case 4:
            actionScreen_digiInfoFilterLabel1->fn->setString(actionScreen_digiInfoFilterLabel1, (leString*)&string_pcmFilt4);
            actionScreen_digiInfoFilterLabel2->fn->setString(actionScreen_digiInfoFilterLabel2, (leString*)&string_LinPhase12);
            actionScreen_digiInfoFilterLabel3->fn->setString(actionScreen_digiInfoFilterLabel3, (leString*)&string_SloRoll12);
            break;

        case 5:
            actionScreen_digiInfoFilterLabel1->fn->setString(actionScreen_digiInfoFilterLabel1, (leString*)&string_pcmFilt5);
            actionScreen_digiInfoFilterLabel2->fn->setString(actionScreen_digiInfoFilterLabel2, (leString*)&string_MinPhase12);
            actionScreen_digiInfoFilterLabel3->fn->setString(actionScreen_digiInfoFilterLabel3, (leString*)&string_FastRoll12);
            break;

        case 6:
            actionScreen_digiInfoFilterLabel1->fn->setString(actionScreen_digiInfoFilterLabel1, (leString*)&string_pcmFilt6);
            actionScreen_digiInfoFilterLabel2->fn->setString(actionScreen_digiInfoFilterLabel2, (leString*)&string_MinPhase12);
            actionScreen_digiInfoFilterLabel3->fn->setString(actionScreen_digiInfoFilterLabel3, (leString*)&string_SloRoll12);
            break;

        case 7:
            actionScreen_digiInfoFilterLabel1->fn->setString(actionScreen_digiInfoFilterLabel1, (leString*)&string_pcmFilt7);
            actionScreen_digiInfoFilterLabel2->fn->setString(actionScreen_digiInfoFilterLabel2, (leString*)&string_MinPhase12);
            actionScreen_digiInfoFilterLabel3->fn->setString(actionScreen_digiInfoFilterLabel3, (leString*)&string_SloRollLoDisp12);
            break;

        default:
            actionScreen_digiInfoFilterLabel1->fn->setString(actionScreen_digiInfoFilterLabel1, (leString*)&string_emtyString);
            actionScreen_digiInfoFilterLabel2->fn->setString(actionScreen_digiInfoFilterLabel2, (leString*)&string_emtyString);
            actionScreen_digiInfoFilterLabel3->fn->setString(actionScreen_digiInfoFilterLabel3, (leString*)&string_emtyString);
            break;
    }
}

void DacUi_SyncPcmFilter_CurrentScreen(void)
{
    uint8_t f = dacData.pcmFilter;
    if (f < 1u || f > 7u) f = 4u;

    const uint32_t scr = legato_getCurrentScreen();

    if (scr == screenID_actionScreen)
    {
        DacUi_SyncPcmFilterLabels_ActionScreen(f);
        return;
    }

    if (scr == screenID_digitalSetupScreen)
    {
        switch (f)
        {
            case 1:
                digitalSetupScreen_filterNameLine1->fn->setString(digitalSetupScreen_filterNameLine1, (leString*)&string_MinPhase);
                digitalSetupScreen_filterNameLine2->fn->setString(digitalSetupScreen_filterNameLine2, (leString*)&string_emtyString);
                break;
            case 2:
                digitalSetupScreen_filterNameLine1->fn->setString(digitalSetupScreen_filterNameLine1, (leString*)&string_LinPhase);
                digitalSetupScreen_filterNameLine2->fn->setString(digitalSetupScreen_filterNameLine2, (leString*)&string_Apodiz);
                break;
            case 3:
                digitalSetupScreen_filterNameLine1->fn->setString(digitalSetupScreen_filterNameLine1, (leString*)&string_LinPhase);
                digitalSetupScreen_filterNameLine2->fn->setString(digitalSetupScreen_filterNameLine2, (leString*)&string_FastRoll);
                break;
            case 4:
                digitalSetupScreen_filterNameLine1->fn->setString(digitalSetupScreen_filterNameLine1, (leString*)&string_LinPhase);
                digitalSetupScreen_filterNameLine2->fn->setString(digitalSetupScreen_filterNameLine2, (leString*)&string_SloRoll);
                break;
            case 5:
                digitalSetupScreen_filterNameLine1->fn->setString(digitalSetupScreen_filterNameLine1, (leString*)&string_MinPhase);
                digitalSetupScreen_filterNameLine2->fn->setString(digitalSetupScreen_filterNameLine2, (leString*)&string_FastRoll);
                break;
            case 6:
                digitalSetupScreen_filterNameLine1->fn->setString(digitalSetupScreen_filterNameLine1, (leString*)&string_MinPhase);
                digitalSetupScreen_filterNameLine2->fn->setString(digitalSetupScreen_filterNameLine2, (leString*)&string_SloRoll);
                break;
            case 7:
                digitalSetupScreen_filterNameLine1->fn->setString(digitalSetupScreen_filterNameLine1, (leString*)&string_MinPhase);
                digitalSetupScreen_filterNameLine2->fn->setString(digitalSetupScreen_filterNameLine2, (leString*)&string_SloRollLoDisp);
                break;
            default:
                break;
        }
        return;
    }

    if (scr == screenID_filterSimpleView)
    {
        switch (f)
        {
            case 1:
                filterSimpleView_filterNumber->fn->setString(filterSimpleView_filterNumber, (leString*)&string_pcmFilt1_48);
                filterSimpleView_LabelWidget_1->fn->setString(filterSimpleView_LabelWidget_1, (leString*)&string_MinPhase30);
                filterSimpleView_LabelWidget_2->fn->setString(filterSimpleView_LabelWidget_2, (leString*)&string_emtyString);
                break;
            case 2:
                filterSimpleView_filterNumber->fn->setString(filterSimpleView_filterNumber, (leString*)&string_pcmFilt2_48);
                filterSimpleView_LabelWidget_1->fn->setString(filterSimpleView_LabelWidget_1, (leString*)&string_LinPhase30);
                filterSimpleView_LabelWidget_2->fn->setString(filterSimpleView_LabelWidget_2, (leString*)&string_Apodiz30);
                break;
            case 3:
                filterSimpleView_filterNumber->fn->setString(filterSimpleView_filterNumber, (leString*)&string_pcmFilt3_48);
                filterSimpleView_LabelWidget_1->fn->setString(filterSimpleView_LabelWidget_1, (leString*)&string_LinPhase30);
                filterSimpleView_LabelWidget_2->fn->setString(filterSimpleView_LabelWidget_2, (leString*)&string_FastRoll30);
                break;
            case 4:
                filterSimpleView_filterNumber->fn->setString(filterSimpleView_filterNumber, (leString*)&string_pcmFilt4_48);
                filterSimpleView_LabelWidget_1->fn->setString(filterSimpleView_LabelWidget_1, (leString*)&string_LinPhase30);
                filterSimpleView_LabelWidget_2->fn->setString(filterSimpleView_LabelWidget_2, (leString*)&string_SloRoll30);
                break;
            case 5:
                filterSimpleView_filterNumber->fn->setString(filterSimpleView_filterNumber, (leString*)&string_pcmFilt5_48);
                filterSimpleView_LabelWidget_1->fn->setString(filterSimpleView_LabelWidget_1, (leString*)&string_MinPhase30);
                filterSimpleView_LabelWidget_2->fn->setString(filterSimpleView_LabelWidget_2, (leString*)&string_FastRoll30);
                break;
            case 6:
                filterSimpleView_filterNumber->fn->setString(filterSimpleView_filterNumber, (leString*)&string_pcmFilt6_48);
                filterSimpleView_LabelWidget_1->fn->setString(filterSimpleView_LabelWidget_1, (leString*)&string_MinPhase30);
                filterSimpleView_LabelWidget_2->fn->setString(filterSimpleView_LabelWidget_2, (leString*)&string_SloRoll30);
                break;
            case 7:
                filterSimpleView_filterNumber->fn->setString(filterSimpleView_filterNumber, (leString*)&string_pcmFilt7_48);
                filterSimpleView_LabelWidget_1->fn->setString(filterSimpleView_LabelWidget_1, (leString*)&string_MinPhase30);
                filterSimpleView_LabelWidget_2->fn->setString(filterSimpleView_LabelWidget_2, (leString*)&string_SloRollLoDisp30);
                break;
            default:
                break;
        }

        // behold din remoteView timer her (giver mening kun her)
        if (appData.remoteViewShiftDelayHandle)
            SYS_TIME_TimerDestroy(appData.remoteViewShiftDelayHandle);
        appData.remoteViewShiftDelayHandle = SYS_TIME_CallbackRegisterMS(remoteViewDelay_Callback, 0, 3000, SYS_TIME_SINGLE);
        appData.remoteViewDelayFlg = 1;

        return;
    }
}

// =========================
// DSD LP filter (HW-only / UI-only)
// =========================

void DacHw_ApplyDsdLpFilterFromState(void)
{
    // NOTE: Dette er en ren HW-funktion. Ingen Legato/UI her.

    static int8_t s_applied = -1; // -1 = ukendt (tving fÃ¸rste write)

    const uint8_t enable = (dacData.dsdLpFilter != 0u) ? 1u : 0u;

    if (s_applied == (int8_t)enable)
        return;

    if (enable)
        dacData.dacIoExpOutByte |= 0x04u;
    else
        dacData.dacIoExpOutByte &= (uint8_t)~0x04u;

    setDacIOExpOut(dacData.dacIoExpOutByte);
    s_applied = (int8_t)enable;
}

//void DacUi_SyncDsdLp_CurrentScreen(void)
//{
//    // NOTE: Dette er en ren UI-funktion. Ingen HW her.
//
//    const const uint32_t scr = legato_getCurrentScreen();
//    const bool enable = (dacData.dsdLpFilter != 0u);
//
//    if (scr == screenID_actionScreen)
//    {
//        actionScreen_dsdLpOn->fn->setVisible(actionScreen_dsdLpOn,  enable ? LE_TRUE : LE_FALSE);
//        actionScreen_dsdLpOff->fn->setVisible(actionScreen_dsdLpOff, enable ? LE_FALSE : LE_TRUE);
//    }
//    else if (scr == screenID_dsdLpSimpleView)
//    {
//        dsdLpSimpleView_onValue->fn->setVisible(dsdLpSimpleView_onValue, enable ? LE_TRUE : LE_FALSE);
//    }
//
//    // Digital setup screen synces allerede i digitalSetupScreen_OnShow() med ignoreEvent
//    // og i knap-events. Vi undgÃ¥r at pille ved pressed/enabled her for ikke at trigge events.
//}

void DacUi_SyncDsdLp_CurrentScreen(void)
{
    // UI-only

    const uint32_t scr = legato_getCurrentScreen();
    const bool dsdLpEnabled = (dacData.dsdLpFilter != 0u);

    if (scr == screenID_actionScreen)
    {
        // DSD LP-linjen skal kun vises i USB + DSD mode
        const bool show = (appData.curInp == 7u) && (dacData.dsdOnFlg != 0u);

        if (!show)
        {
            actionScreen_dsdLpOn->fn->setVisible(actionScreen_dsdLpOn,  LE_FALSE);
            actionScreen_dsdLpOff->fn->setVisible(actionScreen_dsdLpOff, LE_FALSE);
            return;
        }

        // show==true: vis ON eller OFF afhængigt af state
        actionScreen_dsdLpOn->fn->setVisible(actionScreen_dsdLpOn,  dsdLpEnabled ? LE_TRUE : LE_FALSE);
        actionScreen_dsdLpOff->fn->setVisible(actionScreen_dsdLpOff, dsdLpEnabled ? LE_FALSE : LE_TRUE);
        return;
    }

    if (scr == screenID_dsdLpSimpleView)
    {
        // SimpleView er kun relevant når du allerede vælger at vise den.
        // Vi viser bare state.
        dsdLpSimpleView_onValue->fn->setVisible(dsdLpSimpleView_onValue,
                                               dsdLpEnabled ? LE_TRUE : LE_FALSE);
        return;
    }

    // Digital setup screen synces i OnShow/events -> ikke her.
}


void dacSetPcmFilter(void)
{
    // Legacy wrapper: behold kompatibilitet mens vi flytter callsites.
    DacUi_SyncPcmFilter_CurrentScreen();
    DacHw_ApplyPcmFilterFromState();
}

void dacSetDSDFilter(void)
{
    
}

void dacSetDsdLpFilter(void)
{
    // Legacy wrapper: beholdt for kompatibilitet.
    // Fremover bÃ¸r kald ske via reqApplyDsdLp + DacHw_Apply... i APP_Tasks.
    DacHw_ApplyDsdLpFilterFromState();
    DacUi_SyncDsdLp_CurrentScreen();
}

void dacSetGain(void)
{
    if(dacData.digiGain == 0)
    {
            if(legato_getCurrentScreen() == screenID_digitalSetupScreen)
            {
              digitalSetupScreen_digitalGain0dBButton->fn->setPressed(digitalSetupScreen_digitalGain0dBButton, LE_FALSE);
              digitalSetupScreen_digitalGainMinus6dBButton->fn->setPressed(digitalSetupScreen_digitalGainMinus6dBButton, LE_TRUE);
            }
            else if(legato_getCurrentScreen() == screenID_actionScreen)
            {
               actionScreen_gainMinus6dB->fn->setVisible(actionScreen_gainMinus6dB, LE_TRUE);
            }
            else if(legato_getCurrentScreen() == screenID_dacGainSimpleView)
            {
                dacGainSimpleView_gainMinus6dB->fn->setVisible(dacGainSimpleView_gainMinus6dB,LE_TRUE);
                if(appData.remoteViewShiftDelayHandle)
                   SYS_TIME_TimerDestroy(appData.remoteViewShiftDelayHandle);
                appData.remoteViewShiftDelayHandle = SYS_TIME_CallbackRegisterMS(remoteViewDelay_Callback, 0, 3000, SYS_TIME_SINGLE);
                appData.remoteViewDelayFlg = 1;
            } 
            //DEBUG_PRINT("digiGain ON currentScreen %d\r\n",legato_getCurrentScreen());
    }
    else
    {
            if(legato_getCurrentScreen() == screenID_digitalSetupScreen)
            {
              digitalSetupScreen_digitalGain0dBButton->fn->setPressed(digitalSetupScreen_digitalGain0dBButton, LE_TRUE);
              digitalSetupScreen_digitalGainMinus6dBButton->fn->setPressed(digitalSetupScreen_digitalGainMinus6dBButton, LE_FALSE);
            }
            else if(legato_getCurrentScreen() == screenID_actionScreen)
            {
               actionScreen_gainMinus6dB->fn->setVisible(actionScreen_gainMinus6dB, LE_FALSE);
            }
            else if(legato_getCurrentScreen() == screenID_dacGainSimpleView)
            {
                dacGainSimpleView_gainMinus6dB->fn->setVisible(dacGainSimpleView_gainMinus6dB,LE_FALSE);
                if(appData.remoteViewShiftDelayHandle)
                   SYS_TIME_TimerDestroy(appData.remoteViewShiftDelayHandle);
                appData.remoteViewShiftDelayHandle = SYS_TIME_CallbackRegisterMS(remoteViewDelay_Callback, 0, 3000, SYS_TIME_SINGLE);
                appData.remoteViewDelayFlg = 1;
            }   
            //DEBUG_PRINT("digiGain OFF\r\n");
    }
    //DEBUG_PRINT("Volume to be Updated\r\n");
    dacData.dacDigiChangeFlg = 1; //UpdateVolume ();
    if(appData.muteFlg)
      appData.skipUnmuteFlg = 1;

    //DEBUG_PRINT("Volume Updated\r\n");
}


void dirSetup(void)
{
    writeBuffer[0] = dirReg1;
    writeBuffer[1] = dirReg1Setting;
    I2C_WAIT_OR_RET();
    I2C2_Write(dirAddress, &writeBuffer[0], 2);
    I2C_WAIT_OR_RET();
}

uint8_t dirGetFs(void)
{
    uint8_t fs;
    
    writeBuffer[0] = 0x07; //Peger p register 7
    I2C_WAIT_OR_RET0();
    if(!I2C2_WriteRead(dirAddress, writeBuffer, 1, readBuffer , 1)) 
    {
        DEBUG_PRINT("i2c read error"); 
        return 0;
    }
    I2C_WAIT_OR_RET0();
    
    fs = readBuffer[0] & 0xF0;
    
    return fs >> 4;
    
}    

void dirReset(void)
{
    writeBuffer[0] = 0x00; //Peger p register 0
    writeBuffer[1] = 0x00;
    I2C_WAIT_OR_RET();
    I2C2_Write(dirAddress, &writeBuffer[0], 2);
    I2C_WAIT_OR_RET();
    writeBuffer[0] = 0x00; //Peger p register 0
    writeBuffer[1] = 0x03;
    I2C2_Write(dirAddress, &writeBuffer[0], 2);
    I2C_WAIT_OR_RET();
    
}    


void setInputFormat(uint8_t format)
{
    writeBuffer[0] = dacReg57;
    writeBuffer[1] = format;
    I2C_WAIT_OR_RET();
    I2C2_Write(dacAddress, &writeBuffer[0], 2);
    I2C_WAIT_OR_RET();
}

void toggleMasterSlaveBit(void)
{
    writeBuffer[0] = dacReg57;
    writeBuffer[1] = 0x50;
    I2C_WAIT_OR_RET();
    I2C2_Write(dacAddress, &writeBuffer[0], 2);
    I2C_WAIT_OR_RET();
    writeBuffer[0] = dacReg57;
    writeBuffer[1] = 0x40;
    I2C2_Write(dacAddress, &writeBuffer[0], 2);
    I2C_WAIT_OR_RET();
    
}

void setDirInput(void)
{
    writeBuffer[0] = 0x03; //Peger p register 3
    writeBuffer[1] = dirReg3Setting + appData.curInp - 8;
    I2C_WAIT_OR_RET();
    I2C2_Write(dirAddress, &writeBuffer[0], 2);
    I2C_WAIT_OR_RET();
}

void dacEnableGpio(void)
{
    writeBuffer[0] = dacReg42;
    writeBuffer[1] = 0x38; //enable GPIO4, GPIO5 og GPIO6
    I2C_WAIT_OR_RET();
    I2C2_Write(dacAddress, &writeBuffer[0], 2);
    I2C_WAIT_OR_RET();
    
}
//void dacIgnorePcmDC (void)
//{
//    writeBuffer[0] = dacReg62;
//    writeBuffer[1] = 0x34; //
//    I2C2_Write(dacAddress, &writeBuffer[0], 2);
//    CORETIMER_DelayMs(7);
//    
//}

void dacGpioConfig(void)
{
    writeBuffer[0] = dacReg37;
    writeBuffer[1] = 0x7D; //GPIO = shutdown - GPIO2 = lock_status
    I2C_WAIT_OR_RET();
    I2C2_Write(dacAddress, &writeBuffer[0], 2);
    I2C_WAIT_OR_RET();
    
}

void dacBckInvToggle(void)
{
    writeBuffer[0] = dacReg58;
    writeBuffer[1] = 0x41; //BCK INVERT SLAVE 
    I2C_WAIT_OR_RET();
    I2C2_Write(dacAddress, &writeBuffer[0], 2);
    I2C_WAIT_OR_RET();
    CORETIMER_DelayMs(5);
    writeBuffer[0] = dacReg58;
    writeBuffer[1] = 0x01; //BCK NORMAL OPERATION
    I2C2_Write(dacAddress, &writeBuffer[0], 2);
    I2C_WAIT_OR_RET();
    CORETIMER_DelayMs(5);
    
}


void dacChMute(uint8_t muteValue)
{
    writeBuffer[0] = dacReg86;
    writeBuffer[1] = muteValue; 
    I2C_WAIT_OR_RET();
    I2C2_Write(dacAddress, &writeBuffer[0], 2);
    I2C_WAIT_OR_RET();
//    writeBuffer[0] = dacReg74;
//    writeBuffer[1] = muteValue; 
//    I2C_WAIT_OR_RET();
//    I2C2_Write(dacAddress, &writeBuffer[0], 2);
//    I2C_WAIT_OR_RET();
//    writeBuffer[0] = dacReg75;
//    I2C2_Write(dacAddress, &writeBuffer[0], 2);    
//    I2C_WAIT_OR_RET();
    CORETIMER_DelayMs(75);
}

void dacsetVolRateUp(uint8_t rate)
{
    //writeBuffer[0] = dacReg82;
    writeBuffer[0] = dacReg82;
    writeBuffer[1] = rate; 
    I2C_WAIT_OR_RET();
    I2C2_Write(dacAddress, &writeBuffer[0], 2);
    I2C_WAIT_OR_RET();
    CORETIMER_DelayMs(150);
}
void dacsetVolRateDwn(uint8_t rate)
{
    writeBuffer[0] = dacReg83;
    writeBuffer[1] = rate; 
    I2C_WAIT_OR_RET();
    I2C2_Write(dacAddress, &writeBuffer[0], 2);
    I2C_WAIT_OR_RET();
    CORETIMER_DelayMs(150);
}




void setDacSpdifInput(void)
{
    writeBuffer[0] = dacReg89; //Peger p register 89
    if(appData.curInp >= 8 && appData.curInp <= 11)
      writeBuffer[1] = ((appData.curInp - 2)*16)+4;
    else
      writeBuffer[1] = 0x04;
    I2C_WAIT_OR_RET();
    I2C2_Write(dacAddress, &writeBuffer[0], 2);
    I2C_WAIT_OR_RET();
 }


void setDigitalInput(void)
{
    dacChMute(dacMute);
    CORETIMER_DelayMs(100);
    if(appData.curInp == 7)
    {
        //DEBUG_PRINT("setInputFormat(modeI2sPcm) - CurInp: %d\r\n",appData.curInp);
        dacSetupI2s();
        //i2sUsbOn ();
        setDacSpdifInput();
        
        setInputFormat(modeI2sPcm);
  
        //dacOn();
    }
    else
    {
        //DEBUG_PRINT("setInputFormat(modeSpDif) - CurInp: %d\r\n",appData.curInp);
        //dacSetupI2sDisable();
        //i2sDirOn ();
         //dacSetupI2s();
        dacSetupSpDif();
        setDacSpdifInput();
        setInputFormat(modeSpDif);
//        dirReset();
//        dirSetup();
        setDirInput();
        setDacSpdifInput();
        dacBckInvToggle();
        CORETIMER_DelayMs(30);
        //dacOn();
        dacChMute(dacUnMute);
    }
    //dacChMute(dacUnMute);
    appData.ampStatusChangeFlg = 1;
    
}


void i2sDirOn (void)
{  
    dacData.dacIoExpOutByte |= 0x01; // i2s Dir ON
    setDacIOExpOut(dacData.dacIoExpOutByte);        
}

void i2sUsbOn (void)
{
    dacData.dacIoExpOutByte &= 0xFE; // i2s USB ON
    setDacIOExpOut(dacData.dacIoExpOutByte);        
}
void asyncOn (void)
{  
    dacData.dacIoExpOutByte |= 0x02; // ASYNC ON
    setDacIOExpOut(dacData.dacIoExpOutByte);        
}

void syncOn (void)
{
    dacData.dacIoExpOutByte &= 0xFD; // SYNC ON
    setDacIOExpOut(dacData.dacIoExpOutByte);        
}



void dacU26InitIoExp (void)
{
    
    writeBuffer[0] = 0x06; 
    writeBuffer[1] = 00;
    
    I2C_WAIT_OR_RET();
    I2C2_Write(dacIoExpAddress, &writeBuffer[0], 2);
    I2C_WAIT_OR_RET();
    writeBuffer[0] = 0x0E; //Peger p register 0x0c
    writeBuffer[1] = 0x00; //U26 PIN 0-7
    I2C2_Write(dacIoExpAddress, &writeBuffer[0], 2);
    I2C_WAIT_OR_RET();

    writeBuffer[0] = 0x54; //Enable Interrupts
    writeBuffer[1] = 0xF0; //U26 PIN 0-7
    writeBuffer[2] = 0x86; //U26 PIN 8-15

    I2C2_Write(dacIoExpAddress, &writeBuffer[0], 3);
    I2C_WAIT_OR_RET();
    
    writeBuffer[0] = 0x60; //Peger p register 0x60 Interrupt Edge port0
    writeBuffer[1] = 0xFF; //Set port0 og port 1 til at give interrupt ved any change
    writeBuffer[2] = 0xFF; //Set port0 og port 1 til at give interrupt ved any change
    writeBuffer[3] = 0xFF; //Set port0 og port 1 til at give interrupt ved any change
    writeBuffer[4] = 0xFf; //Set port0 og port 1 til at give interrupt ved any change
    I2C2_Write(dacIoExpAddress, &writeBuffer[0], 5);
    I2C_WAIT_OR_RET();

}

