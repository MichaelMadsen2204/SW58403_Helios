#include "definitions.h" // indeholder app.h, system headers, legato types mm.
#include "gfx/legato/generated/screen/le_gen_screen_actionScreen.h" // for actionScreen_dispOnButton
#include "gfx/legato/generated/screen/le_gen_screen_simpleViewScreen.h" // for simpleViewScreen_dispOnButton
#include "ui_globals.h"
#include "app.h"

/*
 * IR_control.c (drop-in)
 * - Robust RC5/RC5X decoder:
 *   * Sync on first falling edge (TSOP idle high -> low burst)
 *   * Samples mid-half-bit
 *   * Produces RC5X 7-bit command (0..127) via field bit (S2)
 *
 * NOTE:
 * - Expects TSOP-style demodulated IR input:
 *     idle = 1, burst = 0
 * - Uses IR_RC5_Get() and CORETIMER_DelayUs() already present in your project.
 */

static uint8_t OldIrCommand = 0;
static uint8_t ignoreToggleCnt = 0;
static bool oldIrToggle = 0;
static bool ignoreToggleFlg = 0;
static bool irOneStepVol = 0;
static bool volCmdDelayed = 0;

static volatile bool s_irWakePending = false;
static volatile bool s_irRxPending = false;

/*****************************************************************************************************************************/
/*************          IR hjælpefunktioner                                                                                 */
/*****************************************************************************************************************************/

#define IR_POLL_WINDOW_MS   500u
#define IR_POLL_SLICE_US    200u   // lille pause for ikke at busy-spinne alt for hårdt

static inline uint32_t ms_elapsed(uint32_t now, uint32_t then) {
    // 100% wrap-safe (uint32 overflow er defineret)
    return (uint32_t) (now - then);
}

bool PollIrForOn(uint32_t window_ms) {
    const uint32_t t0 = millis_32();

    key = 0;

    while (ms_elapsed(millis_32(), t0) < window_ms) {
        // RC5-linjen er aktiv-lav når der er aktivitet
        if (!IR_RC5_Get()) {
            // Forsøg at decode (din irReceive må gerne selv “spise” en hel frame)
            irReceive();

            if (key == KeyOnOff) {
                key = 0;
                return true;
            }
        }

        // Giv lidt luft (og hjælp på sampling/timing afhængigt af din irReceive-implementering)
        CORETIMER_DelayUs(IR_POLL_SLICE_US);
    }

    return false;
}

void irReceiveEventHandler(GPIO_PIN pin, uintptr_t context) {
    (void) pin;
    (void) context;

    if (!IR_RC5_Get()) {
        if (appData.powerOnFlg) {
            s_irRxPending = true; // modtag i task context
        } else if (!appData.powerOnFlg) {
            s_irWakePending = true; // wakeUp i task context
        }
    }
}

void ServiceIr(void) {
    if (s_irRxPending) {
        s_irRxPending = false;
        irReceive(); // tungt OK her
    }

    if (s_irWakePending) {
        s_irWakePending = false;
        wakeUp(); // OK her
    }
}

void remoteViewDelay_Callback(uintptr_t context) {
    (void) context;

    if (appData.enableSimpleViewFlg)
        appData.reqUiAction = UIREQ_GOTO_SIMPLE;
    appData.remoteViewDelayFlg = 0;
}

void remoteViewDispDelay_Callback(uintptr_t context) {
    (void) context;

    if (appData.preRemoteDispChange == actionScr)
        appData.reqUiAction = UIREQ_GOTO_ACTION;
    else if (appData.preRemoteDispChange == simpViewScr)
        appData.reqUiAction = UIREQ_GOTO_SIMPLE;

    if (appData.remoteViewShiftDelayHandle)
        SYS_TIME_TimerDestroy(appData.remoteViewShiftDelayHandle);

    appData.preRemoteDispChange = 0;
    appData.remoteViewDelayFlg = 0;
    appData.saveDisplayFlg = 1;
}

static void irPowerOn(void) {
    // Brug samme key som din eksisterende "On/Off"-wake logik forventer.
    // PollIrForOn() kigger efter key == KeyOnOff.
    key = KeyOnOff;
    keyAccept = 1;
    DEBUG_PRINT("IR: POWER ON (cmd=123)\r\n");
}

static void irPowerOff(void) {
    key = KeyOnOff;
    keyAccept = 1;
    DEBUG_PRINT("IR: POWER OFF (cmd=124)\r\n");

    if (appData.powerOnFlg) {
        RequestPowerOff_FromIR();
    }
}

void irOff(void) {
    key = KeyOnOff;
    keyAccept = 1;
    DEBUG_PRINT("key = On Off\r\n");
    if (appData.powerOnFlg) {
        // VIGTIGT: sørg for at policy ved, at vi slukker via IR
        RequestPowerOff_FromIR();
    }
}

void directInputSelect(uint8_t command) {
    if (!appData.remoteViewDelayFlg) {
        DEBUG_PRINT("MAX inp : %d", appData.maxInp);
        if ((command > 0) && (command <= appData.maxInp)) {
            if (command != 6 || appData.phonoRegiFlg)
                appData.curInp = command;
            appData.irInputChangeFlg = 1;
        }
        if (command == 0 && appData.maxInp == 11) {
            appData.curInp = 10;
            appData.irInputChangeFlg = 1;
        }
        if (appData.irInputChangeFlg == 1) {
            key = KeyDirectSelect;
            DEBUG_PRINT("input IR: %d : Cur iNput: %d\r\n", command, appData.curInp);
            keyAccept = 1;
        }
    }
}

void irVolUp(void) {
    if (!appData.remoteViewDelayFlg) {
        key = KeyVolUp;
        if (appData.curLvl == 0 || appData.muteFlg)
            appData.skipUnmuteFlg = 0;

        if ((appData.curLvl < appData.maxLvl) && appData.inputMuteActiveFlg == 0 && !appData.avFlg)
            appData.curLvl++;
        keyAccept = 1;
    }
}

void irVolDwn(void) {
    if (!appData.remoteViewDelayFlg) {
        key = KeyVolDwn;
        if (appData.curLvl > 0 && appData.inputMuteActiveFlg == 0 && !appData.avFlg)
            appData.curLvl--;
        keyAccept = 1;

        appData.skipUnmuteFlg = 1;
    }
}

void irInpUp(void) {
    if (!appData.remoteViewDelayFlg) {
        key = KeyInpUp;
        if (appData.curInp < appData.maxInp) {
            appData.curInp++;
            if (appData.curInp == 6 && !appData.phonoRegiFlg)
                appData.curInp = 7;

            appData.irInputChangeFlg = 1;
        }
        keyAccept = 1;
    }
}

void irInpDwn(void) {
    if (!appData.remoteViewDelayFlg) {
        key = KeyInpDwn;
        if (appData.curInp > 1) {
            appData.curInp--;
            if (appData.curInp == 6 && !appData.phonoRegiFlg)
                appData.curInp = 5;

            appData.irInputChangeFlg = 1;
        }

        keyAccept = 1;
    }
}

void irMute(void) {
    if (!appData.remoteViewDelayFlg) {
        if (appData.curLvl > 0 || AvSelected(appData.avInp, appData.curInp)) {
            appData.muteToggleFlg = 1;
            key = KeyMute;
            //printf("key = KeyMute\r\n");
            keyAccept = 1;
        }
    }
}

//void irDisp(void)
//{
//    if (!appData.menuFlg)
//    {
//        if (legato_getCurrentScreen() == screenID_simpleViewScreen || legato_getCurrentScreen() == screenID_actionScreen)
//        {
//            if (legato_getCurrentScreen() == screenID_actionScreen)
//            {
//                if (appData.actionViewTimeOutHandle)
//                    SYS_TIME_TimerDestroy(appData.actionViewTimeOutHandle);
//                if (appData.autoDispTimeOutHandle)
//                    SYS_TIME_TimerDestroy(appData.autoDispTimeOutHandle);
//
//                appData.preRemoteDispChange = actionScr;
//
//                if (appData.remoteViewShiftDelayHandle)
//                    SYS_TIME_TimerDestroy(appData.remoteViewShiftDelayHandle);
//                appData.remoteViewShiftDelayHandle =
//                    SYS_TIME_CallbackRegisterMS(remoteViewDispDelay_Callback, 0, 3000, SYS_TIME_SINGLE);
//                appData.remoteViewDelayFlg = 1;
//            }
//            else
//            {
//                if (appData.remoteViewShiftDelayHandle)
//                    SYS_TIME_TimerDestroy(appData.remoteViewShiftDelayHandle);
//                appData.remoteViewShiftDelayHandle =
//                    SYS_TIME_CallbackRegisterMS(remoteViewDispDelay_Callback, 0, 3000, SYS_TIME_SINGLE);
//                appData.remoteViewDelayFlg = 1;
//                appData.preRemoteDispChange = simpViewScr;
//                if (appData.autoDispTimeOutHandle)
//                    SYS_TIME_TimerDestroy(appData.autoDispTimeOutHandle);
//            }
//            legato_showScreen(screenID_displaySimpleView);
//            initScreenSwapDelay();
//            //setDisplayIntensity();
//        }
//        else
//        {
//            if (legato_getCurrentScreen() == screenID_displaySimpleView)
//            {
//                if (appData.dispMode < 5)
//                    appData.dispMode++;
//                else
//                    appData.dispMode = 0;
//
//                if (appData.remoteViewShiftDelayHandle)
//                {
//                    SYS_TIME_TimerDestroy(appData.remoteViewShiftDelayHandle);
//                }
//
//                appData.remoteViewShiftDelayHandle =
//                    SYS_TIME_CallbackRegisterMS(remoteViewDispDelay_Callback, 0, 3000, SYS_TIME_SINGLE);
//                appData.remoteViewDelayFlg = 1;
//
//                dispModeSimpleViewString.fn->setFromCStr(&dispModeSimpleViewString, dispModeStrings[appData.dispMode]);
//                displaySimpleView_dispMode->fn->setString(displaySimpleView_dispMode, (leString *)&dispModeSimpleViewString);
//                initScreenSwapDelay();
//                //setDisplayIntensity();
//                keyAccept = 1;
//            }
//        }
//        key = KeyDisplay;
//        keyAccept = 1;
//    }
//}

void irDisp(void) {
    if (!appData.menuFlg) {
        if (legato_getCurrentScreen() == screenID_simpleViewScreen ||
                legato_getCurrentScreen() == screenID_actionScreen) {
            if (legato_getCurrentScreen() == screenID_actionScreen) {
                if (appData.actionViewTimeOutHandle)
                    SYS_TIME_TimerDestroy(appData.actionViewTimeOutHandle);

                if (appData.autoDispTimeOutHandle)
                    SYS_TIME_TimerDestroy(appData.autoDispTimeOutHandle);

                appData.preRemoteDispChange = actionScr;

                if (appData.remoteViewShiftDelayHandle)
                    SYS_TIME_TimerDestroy(appData.remoteViewShiftDelayHandle);

                appData.remoteViewShiftDelayHandle =
                        SYS_TIME_CallbackRegisterMS(remoteViewDispDelay_Callback, 0, 3000, SYS_TIME_SINGLE);

                appData.remoteViewDelayFlg = 1;
            } else {
                if (appData.remoteViewShiftDelayHandle)
                    SYS_TIME_TimerDestroy(appData.remoteViewShiftDelayHandle);

                appData.remoteViewShiftDelayHandle =
                        SYS_TIME_CallbackRegisterMS(remoteViewDispDelay_Callback, 0, 3000, SYS_TIME_SINGLE);

                appData.remoteViewDelayFlg = 1;
                appData.preRemoteDispChange = simpViewScr;

                if (appData.autoDispTimeOutHandle)
                    SYS_TIME_TimerDestroy(appData.autoDispTimeOutHandle);
            }

            appData.reqUiAction = UIREQ_SHOW_DISP_SIMPLE;
            //initScreenSwapDelay();
        } else {
            if (legato_getCurrentScreen() == screenID_displaySimpleView) {
                if (appData.dispMode < 5)
                    appData.dispMode++;
                else
                    appData.dispMode = 0;

                if (appData.remoteViewShiftDelayHandle)
                    SYS_TIME_TimerDestroy(appData.remoteViewShiftDelayHandle);

                appData.remoteViewShiftDelayHandle =
                        SYS_TIME_CallbackRegisterMS(remoteViewDispDelay_Callback, 0, 3000, SYS_TIME_SINGLE);

                appData.remoteViewDelayFlg = 1;

                dispModeSimpleViewString.fn->setFromCStr(&dispModeSimpleViewString, dispModeStrings[appData.dispMode]);
                displaySimpleView_dispMode->fn->setString(displaySimpleView_dispMode, (leString *) & dispModeSimpleViewString);

                //initScreenSwapDelay();
                keyAccept = 1;
            }
        }

        key = KeyDisplay;
        keyAccept = 1;
    }
}

void irFilter(void) {
    if ((appData.curInp == 7 && !appData.menuFlg && !dacData.dsdOnFlg) || (appData.curInp >= 8 && !appData.menuFlg)) {
        if (legato_getCurrentScreen() == screenID_simpleViewScreen) {
            if (appData.remoteViewShiftDelayHandle)
                SYS_TIME_TimerDestroy(appData.remoteViewShiftDelayHandle);
            appData.remoteViewShiftDelayHandle = SYS_TIME_CallbackRegisterMS(remoteViewDelay_Callback, 0, 3000, SYS_TIME_SINGLE);
            appData.remoteViewDelayFlg = 1;
            appData.reqUiAction = UIREQ_SHOW_FILTER_SIMPLE;
            keyAccept = 1;
        } else {
            if (dacData.pcmFilter < 7)
                dacData.pcmFilter++;
            else if (dacData.pcmFilter == 7)
                dacData.pcmFilter = 1;

            DacUi_SyncPcmFilter_CurrentScreen();
            appData.reqApplyPcmFilter = 1;
            keyAccept = 1;
        }
    }
}

void irDsdLP(void) {
    TRC("IR DSDLP: curScr=%d dsdOn=%d curInp=%d\n",
            (int) legato_getCurrentScreen(), (int) dacData.dsdOnFlg, (int) appData.curInp);

    if (appData.curInp == 7 && !appData.menuFlg && dacData.dsdOnFlg) {
        if (legato_getCurrentScreen() == screenID_simpleViewScreen) {
            if (appData.remoteViewShiftDelayHandle)
                SYS_TIME_TimerDestroy(appData.remoteViewShiftDelayHandle);
            appData.remoteViewShiftDelayHandle =
                    SYS_TIME_CallbackRegisterMS(remoteViewDelay_Callback, 0, 3000, SYS_TIME_SINGLE);
            appData.remoteViewDelayFlg = 1;
            appData.reqUiAction = UIREQ_SHOW_DSDLP; // <-- DEFER UI
            keyAccept = 1;
        } else {
            // Toggled straks, men selve UI-opdateringen køres i APP_Tasks()
            if (dacData.dsdLpFilter == 0)
                dacData.dsdLpFilter = 1;
            else
                dacData.dsdLpFilter = 0;
            appData.reqApplyDsdLp = 1; // <-- DEFER UI
            keyAccept = 1;
        }
    }
}

void irOutputGain(void) {
    DEBUG_PRINT("irOutputGain\r\n");
    if (appData.curInp >= 7 && !appData.menuFlg) {
        if (legato_getCurrentScreen() == screenID_simpleViewScreen) {
            DEBUG_PRINT("irOutputGain (IF) \r\n");
            if (appData.remoteViewShiftDelayHandle)
                SYS_TIME_TimerDestroy(appData.remoteViewShiftDelayHandle);
            appData.remoteViewShiftDelayHandle =
                    SYS_TIME_CallbackRegisterMS(remoteViewDelay_Callback, 0, 3000, SYS_TIME_SINGLE);
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

/*****************************************************************************************************************************/
/*************          RC5/RC5X decoder (drop-in, minimal risiko)                                                         */
/*****************************************************************************************************************************/
/*
 * Du havde en decoder der virkede stabilt for 0..63 kommandoer.
 * Problemet med 123/124 var fase/sync + RC5X field-bit.
 *
 * Her beholder vi samme “2 samples pr bit” Manchester-check som før,
 * men vi synker mere deterministisk:
 *   1) vent på idle HIGH
 *   2) vent på første LOW (start aktivitet)
 *   3) vent ~1/4 bit og læs derefter 14 bits (S1..C0)
 *
 * TSOP output: idle=1, burst=0
 */

#define RC5_HALF_US         889u
#define RC5_QTR_US          (RC5_HALF_US/2u)
#define RC5_TIMEOUT_US      40000u

static bool ir_wait_level(uint8_t level, uint32_t timeout_us) {
    while (timeout_us--) {
        if ((uint8_t) IR_RC5_Get() == level) return true;
        CORETIMER_DelayUs(1);
    }
    return false;
}

uint16_t irDecodeRawCode(void) {
    uint8_t bit_cnt = 0;
    uint8_t single_bit;
    uint16_t ir_code = 0;

    // 0) S�rg for at vi faktisk er inde i et burst (LOW). Hvis du kalder fra pending-flag,
    //    kan du ramme lidt sent ? s� vent kort p� LOW.
    if (!ir_wait_level(0u, RC5_TIMEOUT_US)) return 0xFFFF;

    // 1) Vi antager vi er p� faldende kant i midten af S1 (S1=1 => "10")
    //    G� til midten af S2 f�rste halvbit:
    CORETIMER_DelayUs(RC5_HALF_US + RC5_QTR_US); // ~889 + 444 = ~1333us

    // 2) S1 er kendt = 1
    ir_code = 1u;

    // 3) L�s de resterende 13 bits: S2..C0
    for (bit_cnt = 0; bit_cnt < 13u; bit_cnt++) {
        ir_code <<= 1;
        single_bit = 0;

        if (IR_RC5_Get()) single_bit |= 0b10;
        CORETIMER_DelayUs(RC5_HALF_US);

        if (IR_RC5_Get()) single_bit |= 0b01;
        CORETIMER_DelayUs(RC5_HALF_US);

        if (single_bit == 0b10) ir_code |= 0x01; // bit=1
        else if (single_bit == 0b01); // bit=0
        else {
            CORETIMER_DelayMs(25);
            return 0xFFFF;
        }
    }

    return ir_code; // 14-bit: S1..C0 (MSB f�rst)
}

/*****************************************************************************************************************************/
/*************          UI timing helpers                                                                                   */

/*****************************************************************************************************************************/
typedef enum {
    IR_DISP_ON = 0,
    IR_DISP_DIMMED,
    IR_DISP_OFF
} IR_DISPLAY_STATE;

static bool IrScreenNeedsDisplayActivityRefresh(uint32_t screenId) {
    return (screenId == screenID_actionScreen ||
            screenId == screenID_simpleViewScreen ||
            screenId == screenID_displaySimpleView ||
            screenId == screenID_filterSimpleView ||
            screenId == screenID_dsdLpSimpleView ||
            screenId == screenID_dacGainSimpleView);
}

static void IrRefreshDisplayActivityForCurrentScreen(bool allowBacklightOn) {
    uint32_t scr;

    if (!keyAccept)
        return;

    scr = legato_getCurrentScreen();

    if (!IrScreenNeedsDisplayActivityRefresh(scr))
        return;

    if (appData.autoDispTimeOutHandle)
        SYS_TIME_TimerDestroy(appData.autoDispTimeOutHandle);

    appData.autoDispTimeOutHandle =
            SYS_TIME_CallbackRegisterMS(autoDispTimeOut_Callback, 0, DimOffTimeOut, SYS_TIME_SINGLE);

    if (scr == screenID_actionScreen) {
        if (appData.actionViewTimeOutHandle)
            SYS_TIME_TimerDestroy(appData.actionViewTimeOutHandle);

        appData.actionViewTimeOutHandle =
                SYS_TIME_CallbackRegisterMS(actionViewTimeOut_Callback, 0, ActionViewTimeOut, SYS_TIME_SINGLE);
    }

    if (allowBacklightOn) {
        setDisplayIntensity();
    }
}

static void RestartDisplayTimeouts_Unconditional(void) {
    if (appData.autoDispTimeOutHandle)
        SYS_TIME_TimerDestroy(appData.autoDispTimeOutHandle);

    appData.autoDispTimeOutHandle =
            SYS_TIME_CallbackRegisterMS(autoDispTimeOut_Callback, 0, DimOffTimeOut, SYS_TIME_SINGLE);

    if (legato_getCurrentScreen() == screenID_actionScreen) {
        if (appData.actionViewTimeOutHandle)
            SYS_TIME_TimerDestroy(appData.actionViewTimeOutHandle);

        appData.actionViewTimeOutHandle =
                SYS_TIME_CallbackRegisterMS(actionViewTimeOut_Callback, 0, ActionViewTimeOut, SYS_TIME_SINGLE);
    }
}

static IR_DISPLAY_STATE IrGetDisplayState(void) {
    const uint8_t dm = (uint8_t) (appData.dispMode & 0x7Fu);

    if (!appData.dispSleepActiveFlg)
        return IR_DISP_ON;

    if (dm == modeDim)
        return IR_DISP_DIMMED;

    if (dm == modeOff)
        return IR_DISP_OFF;

    return IR_DISP_ON;
}

static bool isVolumeCommand(uint8_t command) {
    return (command == com_vol_up || command == com_vol_dwn);
}

static bool isImmediateWhenDisplayOff(uint8_t command) {
    return (command == com_power_off ||
            command == com_on_off ||
            command == com_Filter ||
            command == com_DsdLP ||
            command == com_OutputGain ||
            command == com_disp);
}

static bool isDeferredUiWakeCommand(uint8_t command) {
    return (command == com_Filter ||
            command == com_DsdLP ||
            command == com_OutputGain ||
            command == com_disp);
}

static void IrWakeDisplayNow(void) {
    appData.dispSleepActiveFlg = 0;
    setDisplayIntensity();
    RestartDisplayTimeouts_Unconditional();
}

static void IrPrepareDeferredDisplayWake(void) {
    appData.dispSleepActiveFlg = 0;
    appData.irDeferredDisplayOnFlg = 1;
    appData.screenSwapDelayExpired = 0;
}

void irActionScreenDisplayTiming(void) {
    if (keyAccept && legato_getCurrentScreen() == screenID_actionScreen) {
        if (appData.preRemoteDispChange == 0) {
            if (appData.actionViewTimeOutHandle)
                SYS_TIME_TimerDestroy(appData.actionViewTimeOutHandle);
            appData.actionViewTimeOutHandle =
                    SYS_TIME_CallbackRegisterMS(actionViewTimeOut_Callback, 0, ActionViewTimeOut, SYS_TIME_SINGLE);

            if (appData.autoDispTimeOutHandle)
                SYS_TIME_TimerDestroy(appData.autoDispTimeOutHandle);
            appData.autoDispTimeOutHandle =
                    SYS_TIME_CallbackRegisterMS(autoDispTimeOut_Callback, 0, DimOffTimeOut, SYS_TIME_SINGLE);

            setDisplayIntensity();
        }
    }
}

void irSimpleViewScreenDisplayTiming(void) {
    if (keyAccept && legato_getCurrentScreen() == screenID_simpleViewScreen) {
        if (appData.autoDispTimeOutHandle)
            SYS_TIME_TimerDestroy(appData.autoDispTimeOutHandle);
        appData.autoDispTimeOutHandle =
                SYS_TIME_CallbackRegisterMS(autoDispTimeOut_Callback, 0, DimOffTimeOut, SYS_TIME_SINGLE);
        setDisplayIntensity();
    }
}

static bool isPowerCommandImmediateInDisplayOff(uint8_t command) {
    return (command == com_power_off || command == com_on_off);
}

static bool isSimpleOverlayCommand(uint8_t command) {
    return (command == com_Filter ||
            command == com_DsdLP ||
            command == com_OutputGain);
}

static bool IrIsSimpleLikeScreen(uint32_t screenId) {
    return (screenId == screenID_simpleViewScreen ||
            screenId == screenID_displaySimpleView ||
            screenId == screenID_filterSimpleView ||
            screenId == screenID_dsdLpSimpleView ||
            screenId == screenID_dacGainSimpleView);
}
/*****************************************************************************************************************************/
/*************          Command gating                                                                                      */

/*****************************************************************************************************************************/
static bool IrIsExclusiveSimpleOverlayScreen(uint32_t screenId)
{
    return (screenId == screenID_filterSimpleView ||
            screenId == screenID_dsdLpSimpleView ||
            screenId == screenID_dacGainSimpleView);
}

static bool IrCommandMatchesExclusiveOverlay(uint32_t screenId, uint8_t command)
{
    if (screenId == screenID_filterSimpleView)
        return (command == com_Filter);

    if (screenId == screenID_dsdLpSimpleView)
        return (command == com_DsdLP);

    if (screenId == screenID_dacGainSimpleView)
        return (command == com_OutputGain);

    return true;
}

static bool IrIsOverlaySelectCommand(uint8_t command) {
    return (command == com_Filter ||
            command == com_DsdLP ||
            command == com_OutputGain);
}

static bool isRepeatVolCommand(uint8_t command, bool irToggle) {
    return ((OldIrCommand == com_vol_up && command == com_vol_up) ||
            (OldIrCommand == com_vol_dwn && command == com_vol_dwn)) &&
            (ignoreToggleCnt <= 100) && !volCmdDelayed && (irToggle == oldIrToggle);
}

static bool shouldProcessCommand(uint8_t system, uint8_t command, bool irToggle) {
    if (system != 16u) return false;

    // Discrete power commands: tillad dem kun i relevant state
    if ((command == com_power_on) && (appData.powerOnFlg == false)) return true;
    if ((command == com_power_off) && (appData.powerOnFlg == true)) return true;

    // On/Off (toggle) må gerne virke som "power on" når vi er slukket
    if ((command == com_on_off) && (appData.powerOnFlg == false)) return true;

    // Volume og “special cases”
    if (command == com_vol_up || command == com_vol_dwn) return true;
    if (volCmdDelayed || ignoreToggleFlg) return true;

    // Normal RC5 toggle-regel
    return (irToggle != oldIrToggle);
}

static bool s_wakeGuardActive = false;
static bool s_wakeGuardToggle = false;

void handleIrCommand(uint8_t system, uint8_t command, bool irToggle) {
    bool refreshDisplayActivity = true;
    bool allowBacklightOn = true;

    if (appData.wakeUpFlg)
        return;

    if (appData.powerOnFlg &&
            appData.startupFlg &&
            appData.menuFlg &&
            (command != com_on_off && command != com_power_off)) {
        return;
    }

    if (system != 16u)
        return;

    if (appData.menuFlg) {
        if (command != com_on_off && command != com_power_off) {
            return;
        }
    }
 

 
    const IR_DISPLAY_STATE dispState = IrGetDisplayState();

    /******************************************************************
     * DISPLAY OFF
     ******************************************************************/
    const uint32_t curScreen = legato_getCurrentScreen();
    const bool simpleLike = IrIsSimpleLikeScreen(curScreen);
 
    if (IrIsExclusiveSimpleOverlayScreen(curScreen) &&
            IrIsOverlaySelectCommand(command) &&
            !IrCommandMatchesExclusiveOverlay(curScreen, command)) {
        return;
    }
    if (dispState == IR_DISP_OFF) {
        if (isPowerCommandImmediateInDisplayOff(command)) {
            refreshDisplayActivity = false;
            allowBacklightOn = false;
        } else if (isSimpleOverlayCommand(command) && simpleLike) {
            IrPrepareDeferredDisplayWake();
            refreshDisplayActivity = true;
            allowBacklightOn = false;
        } else {
            IrWakeDisplayNow();

            s_wakeGuardActive = true;
            s_wakeGuardToggle = irToggle;

            oldIrToggle = irToggle;
            OldIrCommand = command;
            volCmdDelayed = 0;
            irOneStepVol = 0;

            return;
        }
    }

    /******************************************************************
     * DISPLAY DIMMED
     ******************************************************************/
    if (dispState == IR_DISP_DIMMED) {
        IrWakeDisplayNow();
        s_wakeGuardActive = false;
    }

    /******************************************************************
     * Wake guard
     ******************************************************************/
    if (s_wakeGuardActive) {
        if (irToggle == s_wakeGuardToggle) {
            RestartDisplayTimeouts_Unconditional();
            return;
        }

        s_wakeGuardActive = false;
    }

    /******************************************************************
     * Volume repeat
     ******************************************************************/
    if (isRepeatVolCommand(command, irToggle)) {
        volCmdDelayed = 1;
        CORETIMER_DelayMs(200);
        return;
    }

    if (!shouldProcessCommand(system, command, irToggle))
        return;

    if (irToggle != oldIrToggle) {
        irOneStepVol = 0;
        volCmdDelayed = 0;
    }

    oldIrToggle = irToggle;
    ignoreToggleCnt = 0;
    ignoreToggleFlg = 0;

    switch (command) {
        case com_power_on: irPowerOn();
            break;
        case com_power_off: irPowerOff();
            break;
        case com_on_off: irOff();
            break;
        case 0 ... 0x0B: directInputSelect(command);
            break;
        case com_vol_up: irVolUp();
            break;
        case com_vol_dwn: irVolDwn();
            break;
        case com_inp_up: irInpUp();
            break;
        case com_inp_dwn: irInpDwn();
            break;
        case com_mute: irMute();
            break;
        case com_disp: irDisp();
            break;
        case com_Filter: irFilter();
            break;
        case com_DsdLP: irDsdLP();
            break;
        case com_OutputGain: irOutputGain();
            break;
        default: break;
    }

    OldIrCommand = command;

    if (refreshDisplayActivity) {
        IrRefreshDisplayActivityForCurrentScreen(allowBacklightOn);
    }
    keyAccept = 0;
}
/******************************************************************************************************************************************************/
/*************          Receive + decode                                                                                                            */

/******************************************************************************************************************************************************/

void irReceive(void) {
    uint16_t raw14 = irDecodeRawCode();

    //printf("raw14=0x%04X", (unsigned)raw14);

    if (raw14 == 0xFFFFu)
        return;

    // raw layout (MSB først):
    // bit13=S1, bit12=S2(field), bit11=T, bit10..6=address(5), bit5..0=command(6)
    uint8_t system = (uint8_t) ((raw14 >> 6) & 0x1Fu);
    bool toggle = (((raw14 >> 11) & 0x01u) != 0u);
    uint8_t field = (uint8_t) ((raw14 >> 12) & 0x01u);
    uint8_t cmd6 = (uint8_t) (raw14 & 0x3Fu);

    // RC5X udvidelse:
    // field=1 => command 0..63
    // field=0 => command 64..127
    uint8_t command = (field == 0u) ? (uint8_t) (cmd6 + 64u) : cmd6;

    handleIrCommand(system, command, toggle);
}
