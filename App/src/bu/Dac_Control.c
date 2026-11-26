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
    if(legato_getCurrentScreen() == screenID_actionScreen)
    {
        printf("pre update infopanel: %x\n", status); 
        updateDigiInfoPanel();  
    }
    
}
#define I2C_TIMEOUT_US  20000u  // 20 ms, justér efter 100k/400kHz

static bool wait_i2c_done_us(uint32_t us)
{
    uint32_t start = CORETIMER_CounterGet();
    uint32_t ticks_per_us = (CORETIMER_FrequencyGet() / 1000000u);

    while (I2C2_IsBusy())
    {
        uint32_t elapsed = (CORETIMER_CounterGet() - start) / ticks_per_us;
        if (elapsed >= us) return false;
    }
    return true;
}

uint16_t readDacIoExpInputs(void)
{
    // 1) Vent på fri bus (med timeout)
    if (!wait_i2c_done_us(I2C_TIMEOUT_US))
    {
        printf("I2C busy before start\r\n");
        return 0;
    }

    // 2) Peg på første input-register (Port 0 = 0x00)
    writeBuffer[0] = 0x00;

    // 3) Start WriteRead: skriv 1 byte adresse, læs 2 bytes data
    if (!I2C2_WriteRead(dacIoExpAddress, writeBuffer, 1, readBuffer, 2))
    {
        printf("I2C WriteRead start failed\r\n");
        return 0;
    }

    // 4) Vent på transaktion færdig (med timeout)
    if (!wait_i2c_done_us(I2C_TIMEOUT_US))
    {
        printf("I2C timed out\r\n");
        return 0;
    }

    // 5) Saml 16-bit værdi: [Port1]<<8 | [Port0]
    uint16_t v = ((uint16_t)readBuffer[1] << 8) | (uint16_t)readBuffer[0];
    return v;
}
//uint16_t readDacIoExpInputs (void)
//{
//    uint16_t input_0_15;
//    
//    writeBuffer[0] = 0; //Peger på register 1
//    while(I2C2_IsBusy());
//    if(!I2C2_WriteRead(dacIoExpAddress, writeBuffer, 1, readBuffer , 3)) 
//    {
//        printf("i2c read error"); 
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
    writeBuffer[0] = 0x6; //Peger på register 4
    writeBuffer[1] = data; //U26 Output 0-2 Port2
    I2C2_Write(dacIoExpAddress, &writeBuffer[0], 2);
    CORETIMER_DelayMs(4);
}


void handleDacStatusChange(void)
{
    if(appData.dacRegiFlg)
    {
    //printf("dacData.usbFs 0x%X \n",dacData.usbFs);
//    if(dacData.signalLockFlg)
//        printf("dacData.signalLockFlg\r\n");
//    else
//        printf("UNLockFlg\r\n");
//    if(dacData.dirIntFlg)
//        printf("dacData.dirIntFlg\r\n");
//    else
//        printf("NOT dirIntFlg\r\n");
//    if(dacData.usbCharging)
//        printf("dacData.usbCharging\r\n");
//    else
//        printf("usbCharge NOT Done\r\n");
//    if(dacData.dsdOnFlg)
//        printf("dacData.dsdOnFlg\r\n");
//    else
//        printf("dsdOFF\r\n");
    if(!dacData.usbPluggedFlg && appData.curInp == 7)
    {
        dacSetupSpDif();
    }
    else if (dacData.usbPluggedFlg && appData.curInp == 7)
    {
        dacSetupI2s();
    }
    
//    if(dacData.dacMuteFlg)
//        printf("dacMuteFlg\r\n");
//    else
//        printf("dacUnMuteFlg\r\n");
    }
}

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
    I2C2_Write(dacAddress, &writeBuffer[0], 2);
    CORETIMER_DelayUs (2000);  
}


void dacSetupI2s (void)
{
    writeBuffer[0] = dacReg59;
    writeBuffer[1] = 0x01;
    I2C2_Write(dacAddress, &writeBuffer[0], 2);
    CORETIMER_DelayUs (2000);  

//    writeBuffer[0] = dacReg64;
//    writeBuffer[1] = 0x00;
//    writeBuffer[2] = 0x01;
//    I2C2_Write(dacAddress, &writeBuffer[0], 3);
//    CORETIMER_DelayUs (4000);  

}
void dacSetupSpDif (void)
{
    writeBuffer[0] = dacReg59;
    writeBuffer[1] = 0x04;
    I2C2_Write(dacAddress, &writeBuffer[0], 2);
    CORETIMER_DelayUs (2000);  

//    writeBuffer[0] = dacReg64;
//    writeBuffer[1] = 0x00;
//    writeBuffer[2] = 0x01;
    
//    I2C2_Write(dacAddress, &writeBuffer[0], 3);
//    CORETIMER_DelayUs (4000);  

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
    
    I2C2_Write(dacAddress, &writeBuffer[0], 9);
    CORETIMER_DelayUs (15000);  
    
}

void setAutoMuteEnableOff(void)
{
   writeBuffer[0] = dacReg123;
   writeBuffer[1] = 0x00;
   I2C2_Write(dacAddress, &writeBuffer[0], 2);
   CORETIMER_DelayUs (2000); 
}

void setAutoMuteEnableOn(void)
{
   writeBuffer[0] = dacReg123;
   writeBuffer[1] = 0xFF;
   I2C2_Write(dacAddress, &writeBuffer[0], 2);
   CORETIMER_DelayUs (2000); 
}


void setMuteRampToGndOff(void)
{
   writeBuffer[0] = dacReg125;
   writeBuffer[1] = 0x00;
   I2C2_Write(dacAddress, &writeBuffer[0], 2);
   CORETIMER_DelayUs (2000); 
}

void setMuteRampToGndOn(void)
{
   writeBuffer[0] = dacReg125;
   writeBuffer[1] = 0x08;
   I2C2_Write(dacAddress, &writeBuffer[0], 2);
   CORETIMER_DelayUs (2000); 
}


void dacOff (void)
{
    writeBuffer[0] = dacReg0;
    writeBuffer[1] = 0x00;
    I2C2_Write(dacAddress, &writeBuffer[0], 2);
    CORETIMER_DelayUs (2000); 
}

void setDacSysModeConfig(void)
{
  writeBuffer[0] = dacReg1;
  writeBuffer[1] = 0xBF; //Enables decoding of all formats
  I2C2_Write(dacAddress, &writeBuffer[0], 2);
  CORETIMER_DelayMs(2);
}


void dacSetPcmFilter(void)
{
    switch(dacData.pcmFilter)
    {
        case    1   :   {
            writeBuffer[1] = 0xB8;
            if(legato_getCurrentScreen() == screenID_digitalSetupScreen)
            {
              digitalSetupScreen_filterNameLine1->fn->setString(digitalSetupScreen_filterNameLine1, (leString*)&string_MinPhase);
              digitalSetupScreen_filterNameLine2->fn->setString(digitalSetupScreen_filterNameLine2, (leString*)&string_emtyString);
            }
            else if(legato_getCurrentScreen() == screenID_actionScreen)
            {
               actionScreen_digiInfoFilterLabel1->fn->setString(actionScreen_digiInfoFilterLabel1, (leString*)&string_pcmFilt1);
               actionScreen_digiInfoFilterLabel2->fn->setString(actionScreen_digiInfoFilterLabel2, (leString*)&string_MinPhase12);
               actionScreen_digiInfoFilterLabel3->fn->setString(actionScreen_digiInfoFilterLabel3, (leString*)&string_emtyString);
            }
            else if(legato_getCurrentScreen() == screenID_filterSimpleView)
            {
                filterSimpleView_filterNumber->fn->setString(filterSimpleView_filterNumber, (leString*)&string_pcmFilt1_48);
                filterSimpleView_LabelWidget_1->fn->setString(filterSimpleView_LabelWidget_1, (leString*)&string_MinPhase30);
                filterSimpleView_LabelWidget_2->fn->setString(filterSimpleView_LabelWidget_2, (leString*)&string_emtyString);
                if(appData.remoteViewShiftDelayHandle)
                   SYS_TIME_TimerDestroy(appData.remoteViewShiftDelayHandle);
                appData.remoteViewShiftDelayHandle = SYS_TIME_CallbackRegisterMS(remoteViewDelay_Callback, 0, 3000, SYS_TIME_SINGLE);
                appData.remoteViewDelayFlg = 1;
            }   
            break;
        }
        case    2   :   {
            writeBuffer[1] = 0xB9;
            if(legato_getCurrentScreen() == screenID_digitalSetupScreen)
            {
              digitalSetupScreen_filterNameLine1->fn->setString(digitalSetupScreen_filterNameLine1, (leString*)&string_LinPhase);
              digitalSetupScreen_filterNameLine2->fn->setString(digitalSetupScreen_filterNameLine2, (leString*)&string_Apodiz);
            }
            else if(legato_getCurrentScreen() == screenID_actionScreen)
            {
               actionScreen_digiInfoFilterLabel1->fn->setString(actionScreen_digiInfoFilterLabel1, (leString*)&string_pcmFilt2);
               actionScreen_digiInfoFilterLabel2->fn->setString(actionScreen_digiInfoFilterLabel2, (leString*)&string_LinPhase12);
               actionScreen_digiInfoFilterLabel3->fn->setString(actionScreen_digiInfoFilterLabel3, (leString*)&string_Apodiz12);
            }
            else if(legato_getCurrentScreen() == screenID_filterSimpleView)
            {
                filterSimpleView_filterNumber->fn->setString(filterSimpleView_filterNumber, (leString*)&string_pcmFilt2_48);
                filterSimpleView_LabelWidget_1->fn->setString(filterSimpleView_LabelWidget_1, (leString*)&string_LinPhase30);
                filterSimpleView_LabelWidget_2->fn->setString(filterSimpleView_LabelWidget_2, (leString*)&string_Apodiz30);
                if(appData.remoteViewShiftDelayHandle)
                   SYS_TIME_TimerDestroy(appData.remoteViewShiftDelayHandle);
                appData.remoteViewShiftDelayHandle = SYS_TIME_CallbackRegisterMS(remoteViewDelay_Callback, 0, 3000, SYS_TIME_SINGLE);
                appData.remoteViewDelayFlg = 1;
            }   
            break;
        }
        case    3   :   {
            writeBuffer[1] = 0xBA;
            if(legato_getCurrentScreen() == screenID_digitalSetupScreen)
            {
              digitalSetupScreen_filterNameLine1->fn->setString(digitalSetupScreen_filterNameLine1, (leString*)&string_LinPhase);
              digitalSetupScreen_filterNameLine2->fn->setString(digitalSetupScreen_filterNameLine2, (leString*)&string_FastRoll);
            }
            else if(legato_getCurrentScreen() == screenID_actionScreen)
            {
               actionScreen_digiInfoFilterLabel1->fn->setString(actionScreen_digiInfoFilterLabel1, (leString*)&string_pcmFilt3);
               actionScreen_digiInfoFilterLabel2->fn->setString(actionScreen_digiInfoFilterLabel2, (leString*)&string_LinPhase12);
               actionScreen_digiInfoFilterLabel3->fn->setString(actionScreen_digiInfoFilterLabel3, (leString*)&string_FastRoll12);
            }
            else if(legato_getCurrentScreen() == screenID_filterSimpleView)
            {
                filterSimpleView_filterNumber->fn->setString(filterSimpleView_filterNumber, (leString*)&string_pcmFilt3_48);
                filterSimpleView_LabelWidget_1->fn->setString(filterSimpleView_LabelWidget_1, (leString*)&string_LinPhase30);
                filterSimpleView_LabelWidget_2->fn->setString(filterSimpleView_LabelWidget_2, (leString*)&string_FastRoll30);
                if(appData.remoteViewShiftDelayHandle)
                   SYS_TIME_TimerDestroy(appData.remoteViewShiftDelayHandle);
                appData.remoteViewShiftDelayHandle = SYS_TIME_CallbackRegisterMS(remoteViewDelay_Callback, 0, 3000, SYS_TIME_SINGLE);
                appData.remoteViewDelayFlg = 1;
            }   
            break;
        }
        case    4   :   {
            writeBuffer[1] = 0xBC;
            if(legato_getCurrentScreen() == screenID_digitalSetupScreen)
            {
              digitalSetupScreen_filterNameLine1->fn->setString(digitalSetupScreen_filterNameLine1, (leString*)&string_LinPhase);
              digitalSetupScreen_filterNameLine2->fn->setString(digitalSetupScreen_filterNameLine2, (leString*)&string_SloRoll);
            }
            else if(legato_getCurrentScreen() == screenID_actionScreen)
            {
               actionScreen_digiInfoFilterLabel1->fn->setString(actionScreen_digiInfoFilterLabel1, (leString*)&string_pcmFilt4);
               actionScreen_digiInfoFilterLabel2->fn->setString(actionScreen_digiInfoFilterLabel2, (leString*)&string_LinPhase12);
               actionScreen_digiInfoFilterLabel3->fn->setString(actionScreen_digiInfoFilterLabel3, (leString*)&string_SloRoll12);
            }
            else if(legato_getCurrentScreen() == screenID_filterSimpleView)
            {
                filterSimpleView_filterNumber->fn->setString(filterSimpleView_filterNumber, (leString*)&string_pcmFilt4_48);
                filterSimpleView_LabelWidget_1->fn->setString(filterSimpleView_LabelWidget_1, (leString*)&string_LinPhase30);
                filterSimpleView_LabelWidget_2->fn->setString(filterSimpleView_LabelWidget_2, (leString*)&string_SloRoll30);
                if(appData.remoteViewShiftDelayHandle)
                   SYS_TIME_TimerDestroy(appData.remoteViewShiftDelayHandle);
                appData.remoteViewShiftDelayHandle = SYS_TIME_CallbackRegisterMS(remoteViewDelay_Callback, 0, 3000, SYS_TIME_SINGLE);
                appData.remoteViewDelayFlg = 1;
            }   
            break;
        }
        case    5   :   {
            writeBuffer[1] = 0xBD;
            if(legato_getCurrentScreen() == screenID_digitalSetupScreen)
            {
              digitalSetupScreen_filterNameLine1->fn->setString(digitalSetupScreen_filterNameLine1, (leString*)&string_MinPhase);
              digitalSetupScreen_filterNameLine2->fn->setString(digitalSetupScreen_filterNameLine2, (leString*)&string_FastRoll);
            }
            else if(legato_getCurrentScreen() == screenID_actionScreen)
            {
               actionScreen_digiInfoFilterLabel1->fn->setString(actionScreen_digiInfoFilterLabel1, (leString*)&string_pcmFilt5);
               actionScreen_digiInfoFilterLabel2->fn->setString(actionScreen_digiInfoFilterLabel2, (leString*)&string_MinPhase12);
               actionScreen_digiInfoFilterLabel3->fn->setString(actionScreen_digiInfoFilterLabel3, (leString*)&string_FastRoll12);
            }
            else if(legato_getCurrentScreen() == screenID_filterSimpleView)
            {
                filterSimpleView_filterNumber->fn->setString(filterSimpleView_filterNumber, (leString*)&string_pcmFilt5_48);
                filterSimpleView_LabelWidget_1->fn->setString(filterSimpleView_LabelWidget_1, (leString*)&string_MinPhase30);
                filterSimpleView_LabelWidget_2->fn->setString(filterSimpleView_LabelWidget_2, (leString*)&string_FastRoll30);
                if(appData.remoteViewShiftDelayHandle)
                   SYS_TIME_TimerDestroy(appData.remoteViewShiftDelayHandle);
                appData.remoteViewShiftDelayHandle = SYS_TIME_CallbackRegisterMS(remoteViewDelay_Callback, 0, 3000, SYS_TIME_SINGLE);
                appData.remoteViewDelayFlg = 1;
            }   
            break;
        }
        case    6   :   {
            writeBuffer[1] = 0xBE;
            if(legato_getCurrentScreen() == screenID_digitalSetupScreen)
            {
              digitalSetupScreen_filterNameLine1->fn->setString(digitalSetupScreen_filterNameLine1, (leString*)&string_MinPhase);
              digitalSetupScreen_filterNameLine2->fn->setString(digitalSetupScreen_filterNameLine2, (leString*)&string_SloRoll);
            }
            else if(legato_getCurrentScreen() == screenID_actionScreen)
            {
               actionScreen_digiInfoFilterLabel1->fn->setString(actionScreen_digiInfoFilterLabel1, (leString*)&string_pcmFilt6);
               actionScreen_digiInfoFilterLabel2->fn->setString(actionScreen_digiInfoFilterLabel2, (leString*)&string_MinPhase12);
               actionScreen_digiInfoFilterLabel3->fn->setString(actionScreen_digiInfoFilterLabel3, (leString*)&string_SloRoll12);
            }
            else if(legato_getCurrentScreen() == screenID_filterSimpleView)
            {
                filterSimpleView_filterNumber->fn->setString(filterSimpleView_filterNumber, (leString*)&string_pcmFilt6_48);
                filterSimpleView_LabelWidget_1->fn->setString(filterSimpleView_LabelWidget_1, (leString*)&string_MinPhase30);
                filterSimpleView_LabelWidget_2->fn->setString(filterSimpleView_LabelWidget_2, (leString*)&string_SloRoll30);
                if(appData.remoteViewShiftDelayHandle)
                   SYS_TIME_TimerDestroy(appData.remoteViewShiftDelayHandle);
                appData.remoteViewShiftDelayHandle = SYS_TIME_CallbackRegisterMS(remoteViewDelay_Callback, 0, 3000, SYS_TIME_SINGLE);
                appData.remoteViewDelayFlg = 1;
            }   
            break;
        }
        case    7   :   {
            writeBuffer[1] = 0xBF;
            if(legato_getCurrentScreen() == screenID_digitalSetupScreen)
            {
              digitalSetupScreen_filterNameLine1->fn->setString(digitalSetupScreen_filterNameLine1, (leString*)&string_MinPhase);
              digitalSetupScreen_filterNameLine2->fn->setString(digitalSetupScreen_filterNameLine2, (leString*)&string_SloRollLoDisp);
            }
            else if(legato_getCurrentScreen() == screenID_actionScreen)
            {
               actionScreen_digiInfoFilterLabel1->fn->setString(actionScreen_digiInfoFilterLabel1, (leString*)&string_pcmFilt7);
               actionScreen_digiInfoFilterLabel2->fn->setString(actionScreen_digiInfoFilterLabel2, (leString*)&string_MinPhase12);
               actionScreen_digiInfoFilterLabel3->fn->setString(actionScreen_digiInfoFilterLabel3, (leString*)&string_SloRollLoDisp12);
            }
            else if(legato_getCurrentScreen() == screenID_filterSimpleView)
            {
                filterSimpleView_filterNumber->fn->setString(filterSimpleView_filterNumber, (leString*)&string_pcmFilt7_48);
                filterSimpleView_LabelWidget_1->fn->setString(filterSimpleView_LabelWidget_1, (leString*)&string_MinPhase30);
                filterSimpleView_LabelWidget_2->fn->setString(filterSimpleView_LabelWidget_2, (leString*)&string_SloRollLoDisp30);
                if(appData.remoteViewShiftDelayHandle)
                   SYS_TIME_TimerDestroy(appData.remoteViewShiftDelayHandle);
                appData.remoteViewShiftDelayHandle = SYS_TIME_CallbackRegisterMS(remoteViewDelay_Callback, 0, 3000, SYS_TIME_SINGLE);
                appData.remoteViewDelayFlg = 1;
            }   
            break;
        }
        default : {
            writeBuffer[1] = 0xB8;
            break;
        }
    }
     
    
    writeBuffer[0] = dacReg88;
    I2C2_Write(dacAddress, &writeBuffer[0], 2);
    CORETIMER_DelayMs(2);
}

void dacSetDSDFilter(void)
{
    
}

void dacSetDsdLpFilter(void)
{
    if(dacData.dsdLpFilter == 1)
    {
            dacData.dacIoExpOutByte |= 0x04;
            if(legato_getCurrentScreen() == screenID_digitalSetupScreen)
            {
              digitalSetupScreen_dsdLpFilterOnButton->fn->setPressed(digitalSetupScreen_dsdLpFilterOnButton, LE_TRUE);
              digitalSetupScreen_dsdLpFilterOnButton->fn->setPressed(digitalSetupScreen_dsdLpFilterOnButton, LE_FALSE);
            }
            else if(legato_getCurrentScreen() == screenID_actionScreen)
            {
               actionScreen_dsdLpOn->fn->setVisible(actionScreen_dsdLpOn, LE_TRUE);
               actionScreen_dsdLpOff->fn->setVisible(actionScreen_dsdLpOff, LE_FALSE);
            }
            else if(legato_getCurrentScreen() == screenID_dsdLpSimpleView)
            {
                dsdLpSimpleView_onValue->fn->setVisible(dsdLpSimpleView_onValue,LE_TRUE);
                if(appData.remoteViewShiftDelayHandle)
                   SYS_TIME_TimerDestroy(appData.remoteViewShiftDelayHandle);
                appData.remoteViewShiftDelayHandle = SYS_TIME_CallbackRegisterMS(remoteViewDelay_Callback, 0, 3000, SYS_TIME_SINGLE);
                appData.remoteViewDelayFlg = 1;
            }   
    }
    else
    {
            dacData.dacIoExpOutByte &= 0xFB;
            if(legato_getCurrentScreen() == screenID_digitalSetupScreen)
            {
              digitalSetupScreen_dsdLpFilterOnButton->fn->setPressed(digitalSetupScreen_dsdLpFilterOnButton, LE_FALSE);
              digitalSetupScreen_dsdLpFilterOnButton->fn->setPressed(digitalSetupScreen_dsdLpFilterOnButton, LE_TRUE);
            }
            else if(legato_getCurrentScreen() == screenID_actionScreen)
            {
               actionScreen_dsdLpOn->fn->setVisible(actionScreen_dsdLpOn, LE_FALSE);
               actionScreen_dsdLpOff->fn->setVisible(actionScreen_dsdLpOff, LE_TRUE);
            }
            else if(legato_getCurrentScreen() == screenID_dsdLpSimpleView)
            {
                dsdLpSimpleView_onValue->fn->setVisible(dsdLpSimpleView_onValue,LE_FALSE);
                if(appData.remoteViewShiftDelayHandle)
                   SYS_TIME_TimerDestroy(appData.remoteViewShiftDelayHandle);
                appData.remoteViewShiftDelayHandle = SYS_TIME_CallbackRegisterMS(remoteViewDelay_Callback, 0, 3000, SYS_TIME_SINGLE);
                appData.remoteViewDelayFlg = 1;
            }   
        
    }
    setDacIOExpOut(dacData.dacIoExpOutByte);
    
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
            //printf("digiGain ON currentScreen %d\r\n",legato_getCurrentScreen());
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
            //printf("digiGain OFF\r\n");
    }
    //printf("Volume to be Updated\r\n");
    dacData.dacDigiChangeFlg = 1; //UpdateVolume ();
    if(appData.muteFlg)
      appData.skipUnmuteFlg = 1;

    //printf("Volume Updated\r\n");
}


void dirSetup(void)
{
    writeBuffer[0] = dirReg1;
    writeBuffer[1] = dirReg1Setting;
    I2C2_Write(dirAddress, &writeBuffer[0], 2);
    CORETIMER_DelayMs(7);
}

uint8_t dirGetFs(void)
{
    uint8_t fs;
    
    writeBuffer[0] = 0x07; //Peger på register 7
    while(I2C2_IsBusy());
    if(!I2C2_WriteRead(dirAddress, writeBuffer, 1, readBuffer , 1)) 
    {
        printf("i2c read error"); 
        return 0;
    }
    CORETIMER_DelayMs(4);
    
    fs = readBuffer[0] & 0xF0;
    
    return fs >> 4;
    
}    

void dirReset(void)
{
    writeBuffer[0] = 0x00; //Peger på register 0
    writeBuffer[1] = 0x00;
    I2C2_Write(dirAddress, &writeBuffer[0], 2);
    CORETIMER_DelayMs(7);
    writeBuffer[0] = 0x00; //Peger på register 0
    writeBuffer[1] = 0x03;
    I2C2_Write(dirAddress, &writeBuffer[0], 2);
    CORETIMER_DelayMs(7);
    
}    


void setInputFormat(uint8_t format)
{
    writeBuffer[0] = dacReg57;
    writeBuffer[1] = format;
    I2C2_Write(dacAddress, &writeBuffer[0], 2);
    CORETIMER_DelayMs(7);
}

void toggleMasterSlaveBit(void)
{
    writeBuffer[0] = dacReg57;
    writeBuffer[1] = 0x50;
    I2C2_Write(dacAddress, &writeBuffer[0], 2);
    CORETIMER_DelayMs(7);
    writeBuffer[0] = dacReg57;
    writeBuffer[1] = 0x40;
    I2C2_Write(dacAddress, &writeBuffer[0], 2);
    CORETIMER_DelayMs(7);
    
}

void setDirInput(void)
{
    writeBuffer[0] = 0x03; //Peger på register 3
    writeBuffer[1] = dirReg3Setting + appData.curInp - 8;
    I2C2_Write(dirAddress, &writeBuffer[0], 2);
    CORETIMER_DelayMs(7);
}

void dacEnableGpio(void)
{
    writeBuffer[0] = dacReg42;
    writeBuffer[1] = 0x38; //enable GPIO4, GPIO5 og GPIO6
    I2C2_Write(dacAddress, &writeBuffer[0], 2);
    CORETIMER_DelayMs(7);
    
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
    I2C2_Write(dacAddress, &writeBuffer[0], 2);
    CORETIMER_DelayMs(7);
    
}

void dacBckInvToggle(void)
{
    writeBuffer[0] = dacReg58;
    writeBuffer[1] = 0x41; //BCK INVERT SLAVE 
    I2C2_Write(dacAddress, &writeBuffer[0], 2);
    CORETIMER_DelayMs(7);
    writeBuffer[0] = dacReg58;
    writeBuffer[1] = 0x01; //BCK NORMAL OPERATION
    I2C2_Write(dacAddress, &writeBuffer[0], 2);
    CORETIMER_DelayMs(7);
    
}


void dacChMute(uint8_t muteValue)
{
    writeBuffer[0] = dacReg86;
    writeBuffer[1] = muteValue; 
    I2C2_Write(dacAddress, &writeBuffer[0], 2);
    CORETIMER_DelayMs(150);
}

void dacsetVolRateUp(uint8_t rate)
{
    writeBuffer[0] = dacReg82;
    writeBuffer[1] = rate; 
    I2C2_Write(dacAddress, &writeBuffer[0], 2);
    CORETIMER_DelayMs(150);
}
void dacsetVolRateDwn(uint8_t rate)
{
    writeBuffer[0] = dacReg83;
    writeBuffer[1] = rate; 
    I2C2_Write(dacAddress, &writeBuffer[0], 2);
    CORETIMER_DelayMs(150);
}




void setDacSpdifInput(void)
{
    writeBuffer[0] = dacReg89; //Peger på register 89
    if(appData.curInp >= 8 && appData.curInp <= 11)
      writeBuffer[1] = ((appData.curInp - 2)*16)+4;
    else
      writeBuffer[1] = 0x04;
    I2C2_Write(dacAddress, &writeBuffer[0], 2);
    CORETIMER_DelayMs(7);
    
}


void setDigitalInput(void)
{
    if(appData.curInp == 7)
    {
        //printf("setInputFormat(modeI2sPcm) - CurInp: %d\r\n",appData.curInp);
        dacSetupI2s();
        //i2sUsbOn ();
        setDacSpdifInput();
        
        setInputFormat(modeI2sPcm);
        
        
        
        //dacOn();
    }
    else
    {
        //printf("setInputFormat(modeSpDif) - CurInp: %d\r\n",appData.curInp);
        //dacSetupI2sDisable();
        //i2sDirOn ();
         //dacSetupI2s();
        dacSetupSpDif();
        setDacSpdifInput();
        setInputFormat(modeSpDif);
        setDirInput();
        setDacSpdifInput();
        dacBckInvToggle();
        //dacOn();
    }
    appData.ampStatusChangeFlg = 1;
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
    
    I2C2_Write(dacIoExpAddress, &writeBuffer[0], 2);
    
    CORETIMER_DelayMs(7);
    writeBuffer[0] = 0x0E; //Peger på register 0x0c
    writeBuffer[1] = 0x00; //U26 PIN 0-7
    I2C2_Write(dacIoExpAddress, &writeBuffer[0], 2);
    CORETIMER_DelayMs(10);

    writeBuffer[0] = 0x54; //Enable Interrupts
    writeBuffer[1] = 0xF0; //U26 PIN 0-7
    writeBuffer[2] = 0x86; //U26 PIN 8-15

    I2C2_Write(dacIoExpAddress, &writeBuffer[0], 3);
    CORETIMER_DelayMs(10);
    
    writeBuffer[0] = 0x60; //Peger på register 0x60 Interrupt Edge port0
    writeBuffer[1] = 0xFF; //Set port0 og port 1 til at give interrupt ved any change
    writeBuffer[2] = 0xFF; //Set port0 og port 1 til at give interrupt ved any change
    writeBuffer[3] = 0xFF; //Set port0 og port 1 til at give interrupt ved any change
    writeBuffer[4] = 0xFf; //Set port0 og port 1 til at give interrupt ved any change
    I2C2_Write(dacIoExpAddress, &writeBuffer[0], 5);
    CORETIMER_DelayMs(10);

}

