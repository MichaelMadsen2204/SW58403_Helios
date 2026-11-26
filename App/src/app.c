/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It
    implements the logic of the application's state machine and it may call
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "app.h"
#include "config/Default/definitions.h"
#include <math.h>
#include "ui_globals.h" 
#include "system/input/sys_input.h"


APP_DATA appData;
DAC_DATA dacData;

extern void ActionScreen_VolumeUiPump(void);

void destroyDisplayTiming(void) {
    if (appData.actionViewTimeOutHandle != SYS_TIME_HANDLE_INVALID)
        (void)SYS_TIME_TimerDestroy(appData.actionViewTimeOutHandle);
    if (appData.autoDispTimeOutHandle != SYS_TIME_HANDLE_INVALID)
        (void)SYS_TIME_TimerDestroy(appData.autoDispTimeOutHandle);
    appData.autoDispTimeOutHandle = SYS_TIME_HANDLE_INVALID;
    appData.actionViewTimeOutHandle = SYS_TIME_HANDLE_INVALID;
}

void showAcError(void) {
    if (appData.acErrorFlg) {
        int scr = legato_getCurrentScreen();
        if (scr != screenID_leftPowerMissingScreen && scr != screenID_wrongAcVoltageScreen) {

            if (!AC_RESET_Get()) {
                DEBUG_PRINT("screenID_leftPowerMissingScreen\r\n\n");
                legato_showScreen(screenID_leftPowerMissingScreen);
            } else {
                DEBUG_PRINT("screenID_wrongAcVoltageScreen\r\n\n");
                legato_showScreen(screenID_wrongAcVoltageScreen);
            }
        }
    }
}

// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

void handleUIRequests(void) {
    // 1) Håndter UI-requests (ALT UI sker herfra)
    if (appData.reqUiAction == UIREQ_SHOW_DSDLP) {
        appData.reqUiAction = UIREQ_NONE;
        legato_showScreen(screenID_dsdLpSimpleView);

        if (appData.irDeferredDisplayOnFlg)
            initScreenSwapDelay();
    } else if (appData.reqUiAction == UIREQ_GOTO_SIMPLE) {
        appData.reqUiAction = UIREQ_NONE;
        appData.uiOverlayActive = 0;
        appData.state = appData.prevStateForOverlay;
        legato_showScreen(screenID_simpleViewScreen);
    } else if (appData.reqUiAction == UIREQ_GOTO_ACTION) {
        appData.reqUiAction = UIREQ_NONE;
        legato_showScreen(screenID_actionScreen);
    } else if (appData.reqUiAction == UIREQ_SHOW_FILTER_SIMPLE) {
        appData.reqUiAction = UIREQ_NONE;
        legato_showScreen(screenID_filterSimpleView);

        if (appData.irDeferredDisplayOnFlg)
            initScreenSwapDelay();
    } else if (appData.reqUiAction == UIREQ_SHOW_GAIN_SIMPLE) {
        appData.reqUiAction = UIREQ_NONE;
        legato_showScreen(screenID_dacGainSimpleView);

        if (appData.irDeferredDisplayOnFlg)
            initScreenSwapDelay();
    } else if (appData.reqUiAction == UIREQ_SHOW_DISP_SIMPLE) {
        appData.reqUiAction = UIREQ_NONE;
        legato_showScreen(screenID_displaySimpleView);

        if (appData.irDeferredDisplayOnFlg)
            initScreenSwapDelay();
    } else if (appData.reqUiAction == UIREQ_GOTO_MENU) {
        appData.reqUiAction = UIREQ_NONE;
        muteOn();
        destroyDisplayTiming();
        if (appData.inputShiftMuteDelayHandle)
            SYS_TIME_TimerDestroy(appData.inputShiftMuteDelayHandle);
        appData.inputShiftMuteDelayHandle = SYS_TIME_HANDLE_INVALID;

        legato_showScreen(screenID_mainMenuScreen);
        appData.state = APP_STATE_IDLE;
    } else if (appData.reqUiAction == UIREQ_EXIT_MENU) {
        appData.reqUiAction = UIREQ_NONE;
        legato_showScreen(screenID_actionScreen);
        if ((appData.curLvl > 0 || AvSelected(appData.avInp, appData.curInp)) && !appData.muteFlg) {
            if (AvSelected(appData.avInp, appData.curInp))
                setAvLevel();
            else
                UpdateVolume();

            muteOff();
        }
    }
   
    // 2) Håndter afledte UI-opdateringer
    if (appData.reqApplyDsdLp) {
        appData.reqApplyDsdLp = 0;
        DacHw_ApplyDsdLpFilterFromState();
        DacUi_SyncDsdLp_CurrentScreen();
    }

    if (appData.reqApplyPcmFilter) {
        appData.reqApplyPcmFilter = 0;
        DacHw_ApplyPcmFilterFromState();
        DacUi_SyncPcmFilter_CurrentScreen();
    }
}

void APP_Initialize(void) {
    appData.state = APP_STATE_INIT;
    //CORETIMER_Start();
    DRV_TOUCH_PIN_RESET_Set();
    DEBUG_PRINT("app intialized\r\n");
    SYS_INP_Init(); // <- vigtig!
    dacData.lockedButNoSignalTimeOutHandle = SYS_MODULE_OBJ_INVALID;
}

/******************************************************************************/

void APP_Tasks(void) {
    static uint8_t first = 1;
    if (first) {
        first = 0;
        DEBUG_PRINT("FIRST APP_Tasks tick: t=%lu ms, onOffState=%d\r\n",
                (uint32_t) millis_32(),
                (int) onOffState);
    }
    ServiceIr();
    onOffSekvens();
    showAcError();
    if (appData.wakeUpFlg)
        return;
    PollPowerInputs_12V_ForOff();
    checkForLeftPSFallOut();
    screenSwap();
    saveDisp();
    irToggleMute();
    InputMute_Service();
    handleUIRequests();


    switch (appData.state) {
            /* Application's initial state. */
        case APP_STATE_INIT:
        {
            appData.state = APP_STATE_IDLE;
            break;
        }

        case APP_ACTION_SCREEN_TASKS:
        {
            if (!legato_getCurrentScreen() == screenID_actionScreen)
                break;
            ActionScreen_VolumeUiPump();
            updateActionScreen();
            checkStatus();
            if (UART1_ReceiverIsReady() && legato_getCurrentScreen() == screenID_actionScreen && appData.startupFlg == 0)
                uartCtrl();
            break;
        }

        case APP_SIMPLEVIEW_SCREEN_TASKS:
        {

            if (dacData.dacDigiChangeFlg) {
                UpdateVolume();
                dacData.dacDigiChangeFlg = 0;
            }

            if (appData.uiOverlayActive || legato_getCurrentScreen() != screenID_simpleViewScreen) {
                break;
            }
            
            updateSimpleViewScreen();
            
            checkStatus();
            
            
            if (UART1_ReceiverIsReady() && legato_getCurrentScreen() == screenID_simpleViewScreen && appData.startupFlg == 0)
                uartCtrl();
            
            break;
        }

        case APP_VOL_SETTING_SCREEN_TASKS:
        {
            updateVolSettingScreen();
            checkStatus();
            break;
        }

        case APP_INPUT_LVL_MATCH_SCREEN_TASKS:
        {
            updateInpLvlMatchScreen();
            checkStatus();
            break;
        }

        case APP_STABILIZING_PROGRESS_TASKS:
        {
            updateProgressBar();
            checkStatus();
            break;
        }

        case APP_DIGTAL_SETTING_TASKS:
        {
            updateDigitaleSettingScreen();
            checkStatus();
            break;
        }

        case APP_QWERTY_TASKS:
        {
            updateQwerty();
            break;
        }


        case APP_ACTIVATE_BOOTLOADER:
        {
            enterBootloaderMode();
            break;
        }

        case APP_SN_SET_SCREEN_TASKS:
        {
            updateSnSetScreen();
            break;
        }
        case APP_LEFT_AC_ERROR:
        {
            updateLeftAcMissingScreen();
            break;
        }
        case APP_STATE_IDLE:
        {
            if ((!IO_EXP_INT_Get() || appData.ampStatusChangeFlg) && !appData.startupFlg) {
                DEBUG_PRINT("\n\r  UTIDIG INDBLANDING!!!   \n\r");
                getAmpStatus();
                handleDacStatusChange();
                appData.ampStatusChangeFlg = 0;
            }

            if (UART1_ReceiverIsReady())
                uartCtrl();

            break;
        }

    }

}


