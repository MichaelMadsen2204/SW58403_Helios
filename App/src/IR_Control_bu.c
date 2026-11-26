#include "definitions.h" // indeholder app.h, system headers, legato types mm.
#include "gfx/legato/generated/screen/le_gen_screen_actionScreen.h" // for actionScreen_dispOnButton
#include "gfx/legato/generated/screen/le_gen_screen_simpleViewScreen.h" // for simpleViewScreen_dispOnButton
#include "ui_globals.h"
#include "app.h"




static uint8_t   OldIrCommand = 0;
static uint8_t ignoreToggleCnt = 0;
static bool oldIrToggle = 0;
static bool ignoreToggleFlg = 0;
static bool irOneStepVol = 0;
static bool volCmdDelayed = 0;

static volatile bool s_irWakePending = false;
static volatile bool s_irRxPending = false;


//static inline bool in_isr(void) {
//    unsigned int s;
//    __asm__ volatile("mfc0 %0,$12,0" : "=r"(s));   // CP0 Status
//    return ((s >> 10) & 0x7) != 0;                 // IPL>0 => i ISR
//}




/*****************************************************************************************************************************/
/*************          IR hjlpefunktioner                                                                                  */
/******************************************************************************************************************************/

//void remoteViewDelay_Callback(uintptr_t context)
//{
//    //DEBUG_PRINT("remote view timeout callback     \r\n");
//    if(appData.enableSimpleViewFlg)    
//      legato_showScreen(screenID_simpleViewScreen);
//    appData.remoteViewDelayFlg = 0;
//}
#define IR_POLL_WINDOW_MS   500u
#define IR_POLL_SLICE_US    200u   // lille pause for ikke at busy-spinne alt for hårdt
static inline uint32_t ms_elapsed(uint32_t now, uint32_t then) {
    // 100% wrap-safe (uint32 overflow er defineret)
    return (uint32_t) (now - then);
}
 bool PollIrForOn(uint32_t window_ms)
{
    const uint32_t t0 = millis_32();

    key = 0;

    while (ms_elapsed(millis_32(), t0) < window_ms)
    {
        // RC5-linjen er aktiv-lav når der er aktivitet
        if (!IR_RC5_Get())
        {
            // Forsøg at decode (din irReceive må gerne selv ?spise? en hel frame)
            irReceive();

            if (key == KeyOnOff)
            {
                key = 0;
                return true;
            }
        }

        // Giv lidt luft (og hjælp på sampling/timing afhængigt af din irReceive-implementering)
        CORETIMER_DelayUs(IR_POLL_SLICE_US);
    }

    return false;
}



void irReceiveEventHandler(GPIO_PIN pin, uintptr_t context)
{
    (void)pin; (void)context;

    if (!IR_RC5_Get())
    {
        if (appData.powerOnFlg && !appData.menuFlg)
        {
            s_irRxPending = true;     // modtag i task context
        }
        else if (!appData.powerOnFlg)
        {
            s_irWakePending = true;   // wakeUp i task context
        }
    }
}
void ServiceIr(void)
{
    if (s_irRxPending)
    {
        s_irRxPending = false;
        irReceive();   // tungt OK her
    }

    if (s_irWakePending)
    {
        s_irWakePending = false;
        wakeUp();      // OK her
    }
}

void remoteViewDelay_Callback(uintptr_t context)
{
    if(appData.enableSimpleViewFlg)
        appData.reqUiAction = UIREQ_GOTO_SIMPLE;
    appData.remoteViewDelayFlg = 0;
}

void remoteViewDispDelay_Callback(uintptr_t context)
{
    if(appData.preRemoteDispChange == actionScr)
        appData.reqUiAction = UIREQ_GOTO_ACTION;
    else if(appData.preRemoteDispChange == simpViewScr)
        appData.reqUiAction = UIREQ_GOTO_SIMPLE;
    if(appData.remoteViewShiftDelayHandle)
        SYS_TIME_TimerDestroy(appData.remoteViewShiftDelayHandle);
    appData.preRemoteDispChange = 0;
    appData.remoteViewDelayFlg = 0;
    appData.saveDisplayFlg = 1;
}

static void irPowerOn(void)
{
    // Brug samme key som din eksisterende "On/Off"-wake logik forventer.
    // PollIrForOn() kigger efter key == KeyOnOff.
    key = KeyOnOff;
    keyAccept = 1;
    DEBUG_PRINT("IR: POWER ON (cmd=123)\r\n");
}

static void irPowerOff(void)
{
    key = KeyOnOff;
    keyAccept = 1;
    DEBUG_PRINT("IR: POWER OFF (cmd=124)\r\n");

    if (appData.powerOnFlg)
    {
        RequestPowerOff_FromIR();
    }
}


void irOff(void)
{
    key = KeyOnOff;
    keyAccept = 1;
    DEBUG_PRINT("key = On Off\r\n");
    if (appData.powerOnFlg) {
        // VIGTIGT: srg for at policy ved, at vi slukker via IR
        RequestPowerOff_FromIR();
   }   

}
void directInputSelect(uint8_t command)
{
   if(!appData.remoteViewDelayFlg)
    {
       if(appData.dispOffFlg)
       {
          appData.dispOffFlg = 0;
          setDisplayIntensity();
          return;
       }

       DEBUG_PRINT("MAX inp : %d", appData.maxInp);
        if ((command > 0) && (command <= appData.maxInp) )
        {
            if(command != 6 || appData.phonoRegiFlg)
              appData.curInp = command;
            appData.irInputChangeFlg = 1;
        }
        if(command == 0 && appData.maxInp == 11)
        {
            appData.curInp = 10;
            appData.irInputChangeFlg = 1;
        }
        if(appData.irInputChangeFlg == 1)
        {
        key = KeyDirectSelect;
        DEBUG_PRINT("input IR: %d : Cur iNput: %d\r\n", command, appData.curInp);
        keyAccept = 1;
        }
        //DEBUG_PRINT("input IR: %d : Cur iNput: %d\r\n", command, appData.curInp);
    }
}

void irVolUp(void)
{
    if(!appData.remoteViewDelayFlg)
    {
       if(appData.dispOffFlg)
       {
          appData.dispOffFlg = 0;
          setDisplayIntensity();
          return;
       }

        //DEBUG_PRINT("com vol up\r\n");
        key = KeyVolUp;
        if(appData.curLvl == 0 || appData.muteFlg)
          appData.skipUnmuteFlg = 0;
            
        if((appData.curLvl < appData.maxLvl) && appData.inputMuteActiveFlg == 0 && !appData.avFlg)
            appData.curLvl++;
        keyAccept = 1;
        
    }
}

void irVolDwn(void)
{
    if(!appData.remoteViewDelayFlg)
    {
       if(appData.dispOffFlg)
       {
          appData.dispOffFlg = 0;
          setDisplayIntensity();
          return;
       }

        //DEBUG_PRINT("com vol dwn\r\n");
        key = KeyVolDwn;
        if(appData.curLvl > 0 && appData.inputMuteActiveFlg == 0 && !appData.avFlg)
            appData.curLvl--;
        keyAccept = 1;
        
        appData.skipUnmuteFlg = 1;
    }
}

void irInpUp (void)
{
    if(!appData.remoteViewDelayFlg)
    {
       if(appData.dispOffFlg)
       {
          appData.dispOffFlg = 0;
          setDisplayIntensity();
          return;
       }

        key = KeyInpUp;
        //DEBUG_PRINT("com inp up: %d\r\n", appData.curInp);
        if(appData.curInp < appData.maxInp) //maxInput)
        {
            appData.curInp++;
            if(appData.curInp == 6 && !appData.phonoRegiFlg)
                appData.curInp = 7;
            //DEBUG_PRINT("inp up After: %d\r\n", appData.curInp);
            appData.irInputChangeFlg = 1;    
        }
        keyAccept = 1;
    }
    
}

void irInpDwn (void)
{
    if(!appData.remoteViewDelayFlg)
    {
       if(appData.dispOffFlg)
       {
          appData.dispOffFlg = 0;
          setDisplayIntensity();
          return;
       }

        key = KeyInpDwn;
        //DEBUG_PRINT("com inp dwn: %d\r\n", appData.curInp);
        if(appData.curInp > 1) //maxInput)
        {
            appData.curInp--;
            if(appData.curInp == 6 && !appData.phonoRegiFlg)
                appData.curInp = 5;

            appData.irInputChangeFlg = 1;
        }

        keyAccept = 1;
     }
    
}

void irMute(void)
{
    
    if(!appData.remoteViewDelayFlg)
    {
       if(appData.dispOffFlg)
       {
          appData.dispOffFlg = 0;
          setDisplayIntensity();
          return;
       }
       if(appData.curLvl > 0 || appData.curInp == appData.avInp)
       {
           
        appData.muteToggleFlg = 1;
        //DEBUG_PRINT("IR MUTE\r\n");

        key = KeyMute;
        keyAccept = 1;
       }
    }
}
    
void irDisp(void)
{
   if(!appData.menuFlg)
     {
         if(legato_getCurrentScreen() == screenID_simpleViewScreen || legato_getCurrentScreen() == screenID_actionScreen)
         {
            if(legato_getCurrentScreen() == screenID_actionScreen)
            {
               if(appData.actionViewTimeOutHandle)
                  SYS_TIME_TimerDestroy( appData.actionViewTimeOutHandle); 
               if(appData.autoDispTimeOutHandle)
                 SYS_TIME_TimerDestroy(appData.autoDispTimeOutHandle);
               appData.preRemoteDispChange = actionScr;
               //appData.actionViewTimeOutHandle = SYS_TIME_CallbackRegisterMS(actionViewTimeOut_Callback, 0, ActionViewTimeOut , SYS_TIME_SINGLE);
              if(appData.remoteViewShiftDelayHandle)
                 SYS_TIME_TimerDestroy(appData.remoteViewShiftDelayHandle);
               appData.remoteViewShiftDelayHandle = SYS_TIME_CallbackRegisterMS(remoteViewDispDelay_Callback, 0, 3000, SYS_TIME_SINGLE);
               appData.remoteViewDelayFlg = 1;
            }
            else
            {
               if(appData.remoteViewShiftDelayHandle)
                 SYS_TIME_TimerDestroy(appData.remoteViewShiftDelayHandle);
               appData.remoteViewShiftDelayHandle = SYS_TIME_CallbackRegisterMS(remoteViewDispDelay_Callback, 0, 3000, SYS_TIME_SINGLE); 
               appData.remoteViewDelayFlg = 1;
               appData.preRemoteDispChange = simpViewScr;
               if(appData.autoDispTimeOutHandle)
                 SYS_TIME_TimerDestroy(appData.autoDispTimeOutHandle);
            }
            legato_showScreen(screenID_displaySimpleView);
            setDisplayIntensity();
         }
         else
         {
            if(legato_getCurrentScreen() == screenID_displaySimpleView)
            {
              if(appData.dispMode < 5)
                appData.dispMode++;
              else
                appData.dispMode = 0;

              if(appData.remoteViewShiftDelayHandle)
              {
                SYS_TIME_TimerDestroy(appData.remoteViewShiftDelayHandle);
              }

              appData.remoteViewShiftDelayHandle = SYS_TIME_CallbackRegisterMS(remoteViewDispDelay_Callback, 0, 3000, SYS_TIME_SINGLE); 
              appData.remoteViewDelayFlg = 1;

              dispModeSimpleViewString.fn->setFromCStr(&dispModeSimpleViewString, dispModeStrings[appData.dispMode]);  
              displaySimpleView_dispMode->fn->setString(displaySimpleView_dispMode, (leString*)&dispModeSimpleViewString);

              setDisplayIntensity();
              keyAccept = 1;
            }
         }
         key = KeyDisplay;
         keyAccept = 1;
     }
}

void irFilter(void)
{
  if((appData.curInp == 7 && !appData.menuFlg && !dacData.dsdOnFlg) || (appData.curInp >= 8 && !appData.menuFlg))
    {
     if(legato_getCurrentScreen() == screenID_simpleViewScreen)
     {
        if(appData.remoteViewShiftDelayHandle)
           SYS_TIME_TimerDestroy(appData.remoteViewShiftDelayHandle);
        appData.remoteViewShiftDelayHandle = SYS_TIME_CallbackRegisterMS(remoteViewDelay_Callback, 0, 3000, SYS_TIME_SINGLE);
        appData.remoteViewDelayFlg = 1;
        appData.reqUiAction = UIREQ_SHOW_FILTER_SIMPLE;
        keyAccept = 1;
     }
     else
     {
        if(dacData.pcmFilter < 7)
           dacData.pcmFilter++;
        else if(dacData.pcmFilter == 7)
            dacData.pcmFilter = 1;

        DacUi_SyncPcmFilter_CurrentScreen();
        appData.reqApplyPcmFilter = 1;
        keyAccept = 1;
     }  
    }    
}

void irDsdLP(void)
 {
    TRC("IR DSDLP: curScr=%d dsdOn=%d curInp=%d\n",
    (int)legato_getCurrentScreen(), (int)dacData.dsdOnFlg, (int)appData.curInp);
    
     if (appData.curInp == 7 && !appData.menuFlg && dacData.dsdOnFlg)
     {
        if (legato_getCurrentScreen() == screenID_simpleViewScreen)
        {
            if (appData.remoteViewShiftDelayHandle)
                SYS_TIME_TimerDestroy(appData.remoteViewShiftDelayHandle);
            appData.remoteViewShiftDelayHandle =
                SYS_TIME_CallbackRegisterMS(remoteViewDelay_Callback, 0, 3000, SYS_TIME_SINGLE);
            appData.remoteViewDelayFlg = 1;
            appData.reqUiAction = UIREQ_SHOW_DSDLP;   // <-- DEFER UI
            keyAccept = 1;
        }
         else
         {
            // Toggled straks, men selve UI-opdateringen kres i APP_Tasks()
            if (dacData.dsdLpFilter == 0) dacData.dsdLpFilter = 1; else dacData.dsdLpFilter = 0;
            appData.reqApplyDsdLp = 1;               // <-- DEFER UI
             keyAccept = 1;
         }
     }
 }
////void irDsdLP(void)
////{
////    if (appData.curInp == 7 && !appData.menuFlg && dacData.dsdOnFlg)
////    {
////        if (legato_getCurrentScreen() == screenID_simpleViewScreen)
////        {
////            if (appData.remoteViewShiftDelayHandle)
////                SYS_TIME_TimerDestroy(appData.remoteViewShiftDelayHandle);
////
////            appData.remoteViewShiftDelayHandle =
////                SYS_TIME_CallbackRegisterMS(remoteViewDelay_Callback, 0, 3000, SYS_TIME_SINGLE);
////            appData.remoteViewDelayFlg = 1;
////
////            appData.reqSimpleViewPopup = 3;   // <- bed om DSD-LP popup
////            keyAccept = 1;
////            return;
////        }
////        // ikke i simpleview? toggle som fr:
////        dacData.dsdLpFilter ^= 1;
////        dacSetDsdLpFilter();
////        keyAccept = 1;
////    }
////}

//void irDsdLP(void)
//{
//    if(appData.curInp == 7 && !appData.menuFlg && dacData.dsdOnFlg)
//    {
//     if(legato_getCurrentScreen() == screenID_simpleViewScreen)
//     {
//        if(appData.remoteViewShiftDelayHandle)
//           SYS_TIME_TimerDestroy(appData.remoteViewShiftDelayHandle);
//        appData.remoteViewShiftDelayHandle = SYS_TIME_CallbackRegisterMS(remoteViewDelay_Callback, 0, 3000, SYS_TIME_SINGLE);
//        appData.remoteViewDelayFlg = 1;
//        appData.reqUiAction = UIREQ_SHOW_DSDLP;
//        keyAccept = 1;
//     }
//     else
//     {
//        if(dacData.dsdLpFilter == 0)
//           dacData.dsdLpFilter = 1;
//        else 
//           dacData.dsdLpFilter = 0; 
//        dacSetDsdLpFilter();
//        keyAccept = 1;
//     }  
//    }
//    
//}

void irOutputGain(void)
{
                
    DEBUG_PRINT("irOutputGain\r\n");
    if (appData.curInp >= 7 && !appData.menuFlg) {
        if (legato_getCurrentScreen() == screenID_simpleViewScreen) 
        {
            DEBUG_PRINT("irOutputGain (IF) \r\n");
            if (appData.remoteViewShiftDelayHandle)
                SYS_TIME_TimerDestroy(appData.remoteViewShiftDelayHandle);
            appData.remoteViewShiftDelayHandle = SYS_TIME_CallbackRegisterMS(remoteViewDelay_Callback, 0, 3000, SYS_TIME_SINGLE);
            appData.remoteViewDelayFlg = 1;
            appData.reqUiAction = UIREQ_SHOW_GAIN_SIMPLE;
            keyAccept = 1;
        } else {
            DEBUG_PRINT("irOutputGain (ELSE) \r\n");
            
            if (dacData.digiGain == 0)
                dacData.digiGain = 1;
            else
                dacData.digiGain = 0;
            dacSetGain();
            keyAccept = 1;
        }
    }

}


uint16_t irDecodeRawCode(void)
{
    uint8_t bit_cnt = 0;
    uint8_t single_bit;
    uint16_t ir_code = 0;

    while(IR_RC5_Get() == 0);

    ir_code |= 0x0001;
    CORETIMER_DelayUs(440);

    for (bit_cnt = 0; bit_cnt < 13; bit_cnt++)
    {
        ir_code <<= 1;
        single_bit = 0;

        if (IR_RC5_Get())
            single_bit |= 0b10;
        CORETIMER_DelayUs(890);
        if (IR_RC5_Get())
            single_bit |= 0b01;
        CORETIMER_DelayUs(890);

        if (single_bit == 0b10)
            ir_code |= 0x01;
        else if ((single_bit == 0b00) || (single_bit == 0b11))
        {
            DEBUG_PRINT("IR ERR at bit %u: single_bit=%u (raw=%u)\r\n",
                        bit_cnt, single_bit, IR_RC5_Get());
            CORETIMER_DelayMs(25);
            return 0xFFFF;
        }
    }

    return ir_code;
}


void irActionScreenDisplayTiming(void)
{
  if(keyAccept && legato_getCurrentScreen() == screenID_actionScreen)  
    {
      if(appData.preRemoteDispChange == 0)
      {
          if(appData.actionViewTimeOutHandle)
             SYS_TIME_TimerDestroy( appData.actionViewTimeOutHandle); 
          appData.actionViewTimeOutHandle = SYS_TIME_CallbackRegisterMS(actionViewTimeOut_Callback, 0, ActionViewTimeOut , SYS_TIME_SINGLE);
          if(appData.autoDispTimeOutHandle)
             SYS_TIME_TimerDestroy(appData.autoDispTimeOutHandle); 
          appData.autoDispTimeOutHandle = SYS_TIME_CallbackRegisterMS(autoDispTimeOut_Callback, 0, DimOffTimeOut , SYS_TIME_SINGLE);
          setDisplayIntensity();
      }
    }    
}

void irSimpleViewScreenDisplayTiming(void)
{
  if(keyAccept && legato_getCurrentScreen() == screenID_simpleViewScreen)  
    {
      if(appData.autoDispTimeOutHandle)
         SYS_TIME_TimerDestroy(appData.autoDispTimeOutHandle); 
      appData.autoDispTimeOutHandle = SYS_TIME_CallbackRegisterMS(autoDispTimeOut_Callback, 0, DimOffTimeOut , SYS_TIME_SINGLE);
      setDisplayIntensity();
    }    
}
static bool isRepeatVolCommand(uint8_t command, bool irToggle)
{
    return ((OldIrCommand == com_vol_up && command == com_vol_up) ||
            (OldIrCommand == com_vol_dwn && command == com_vol_dwn)) &&
           (ignoreToggleCnt <= 100) && !volCmdDelayed && (irToggle == oldIrToggle);
}

static bool shouldProcessCommand(uint8_t system, uint8_t command, bool irToggle)
{
    if (system != 16u) return false;

    // Discrete power commands: tillad dem kun i relevant state
    if ((command == com_power_on)  && (appData.powerOnFlg == false)) return true;
    if ((command == com_power_off) && (appData.powerOnFlg == true))  return true;

    // On/Off (toggle) må gerne virke som "power on" når vi er slukket
    if ((command == com_on_off) && (appData.powerOnFlg == false)) return true;

    // Volume og ?special cases?
    if (command == com_vol_up || command == com_vol_dwn) return true;
    if (volCmdDelayed || ignoreToggleFlg) return true;

    // Normal RC5 toggle-regel
    return (irToggle != oldIrToggle);
}



void handleIrCommand(uint8_t system, uint8_t command, bool irToggle)
{
    if(appData.wakeUpFlg)
        return;
    if(appData.powerOnFlg && appData.startupFlg && command != com_on_off)
        return;
    
    if (isRepeatVolCommand(command, irToggle))
    {
        command = 0xFF;
        volCmdDelayed = 1;
        CORETIMER_DelayMs(200);
        return;
    }
    
    if (shouldProcessCommand(system, command, irToggle))
    {
        if (irToggle != oldIrToggle)
        {
            irOneStepVol = 0;
            volCmdDelayed = 0;
        }

        oldIrToggle = irToggle;
        ignoreToggleCnt = 0;
        ignoreToggleFlg = 0;

        switch (command)
        {
            case com_power_on:      irPowerOn();                break;
            case com_power_off:     irPowerOff();               break;
            case com_on_off:        irOff();                    break;
            case 0 ... 0x0B:        directInputSelect(command); break;
            case com_vol_up:        irVolUp();                  break;
            case com_vol_dwn:       irVolDwn();                 break;
            case com_inp_up:        irInpUp();                  break;
            case com_inp_dwn:       irInpDwn();                 break;
            case com_mute:          irMute();                   break;
            case com_disp:          irDisp();                   break;
            case com_Filter:        irFilter();                 break;
            case com_DsdLP:         irDsdLP();                  break;
            case com_OutputGain:    irOutputGain();             break;
            default: break;
        }

        OldIrCommand = command;
        irActionScreenDisplayTiming();
        irSimpleViewScreenDisplayTiming();
        keyAccept = 0;
    }
}



uint8_t irExtractSystem(uint16_t rawCode)
{
    rawCode >>= 6;
    uint8_t system = 0;
    for (int i = 0; i < 5; i++)
    {
        system >>= 1;
        if (rawCode & 0x01)
            system |= 0x10;
        rawCode >>= 1;
    }
    return system;
}

uint8_t irExtractCommand(uint16_t rawCode)
{
    uint8_t command = 0;

    // Bit 0?5: command bits
    for (int i = 0; i < 6; i++)
    {
        command >>= 1;
        if (rawCode & 0x01)
            command |= 0x20;
        rawCode >>= 1;
    }

    // Bit 12 (S2) ? rawCode er nu shifet 6 gange, s bit 6 = system bit 0, og bit 6 mere ? bit 12 = S2
    uint8_t s2 = (rawCode >> 6) & 0x01;

    // Invert S2 ? bliver til command bit 6
    if (s2 == 0)
        command |= 0x40;

    return command;
}

/******************************************************************************************************************************************************/
void irReceive(void)
{
    uint16_t rawCode = irDecodeRawCode();
    printf("raw %u\r\n",rawCode);
    if (rawCode == 0xFFFF)
        return;
    
    bool toggle = (rawCode & 0x800) ? true : false;
    uint8_t command = irExtractCommand(rawCode);
    uint8_t system = irExtractSystem(rawCode);
    //DEBUG_PRINT("com: %d\nsys: %d\ntoggle:%s\n",command,system,toggle ? "true":"false");
    handleIrCommand(system, command, toggle);
}

