

#ifndef _APP_H
#define _APP_H
/* === Debug Tripwire (safe by default) === */
#ifndef APP_DEBUG_TRIP
#define APP_DEBUG_TRIP 0
#endif

#if APP_DEBUG_TRIP
static inline bool in_isr(void)
{
    unsigned int s;
    __asm__ volatile("mfc0 %0,$12,0" : "=r"(s));
    return ((s >> 10) & 0x7) != 0;
}

#define UI_TRIP(tag, scr) do {                                      \
    extern APP_DATA appData;                                         \
    extern DAC_DATA dacData;                                         \
    TRC("UI_TRIP %-18s isr=%d curScr=%d curInp=%d dsdOn=%d\n",      \
        (tag), (int)in_isr(), (int)legato_getCurrentScreen(),        \
        (int)appData.curInp, (int)dacData.dsdOnFlg);                 \
} while(0)

#define CALL_SHOW(scr, tag) do {                                     \
    TRC("ABOUT_TO_SHOW %-14s scr=%d\n", (tag), (int)(scr));          \
    legato_showScreen(scr);                                          \
    TRC("SHOW_DONE %-14s\n", (tag));                                 \
} while(0)

#else
#define UI_TRIP(tag, scr)     ((void)0)
#define CALL_SHOW(scr, tag)   legato_showScreen(scr)
#endif


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "configuration.h"
#include "config/Default/peripheral/evic/plib_evic.h"
#include "definitions.h"                // SYS function prototypes
#include "screen_Action.h"
#include "ScreenAV_Setup.h"
#include "voltageSetting.h"

//static uint32_t *ramStart = (uint32_t *)BTL_TRIGGER_RAM_START;

#define binFileName     "FW58403_Ver_"
#define firmwareVersion "1.0"

// Aktiver eller deaktiver debug prints globalt
#define ENABLE_DEBUG_PRINTS   0   // St til 0 for at sl fra

#if ENABLE_DEBUG_PRINTS
    #define DEBUG_PRINT(...)     printf(__VA_ARGS__)
#else
    #define DEBUG_PRINT(...)     ((void)0)
#endif

#define TRC(fmt, ...) DEBUG_PRINT("[TRC] " fmt, ##__VA_ARGS__)

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Type Definitions
// *****************************************************************************
// *****************************************************************************
#define ActionViewTimeOut         6000 //10000  
#define DimOffTimeOut             8000 //20000 
#define screenSwapTimeOut           300    


    
    
#define KeyOnOff        1
#define KeyMute         2
#define KeyVolDwn       3
#define KeyVolUp        4
#define KeyInpDwn       5
#define KeyInpUp        6
#define KeyMonitor      7
#define KeyDirectSelect 9
#define KeyDisplay      10

#define com_on_off      0b00001100  //12 
#define com_mute        0b00001101  //13
#define com_vol_up      0b00010000  //16
#define com_vol_dwn     0b00010001  //17
#define com_inp_up      0b00100000  //32
#define com_inp_dwn     0b00100001  //33
#define com_monitor     21
#define com_disp        15
#define com_OutputGain  36 
#define com_DsdLP       48
#define com_Filter      50 
#define com_power_on    123u
#define com_power_off   124u
    
    
    
#define IR_POLL_WINDOW_MS   500u
#define IR_POLL_SLICE_US    200u   // lille pause for ikke at busy-spinne alt for hårdt
    

#define U26_address     35 // 0x23 Input Ctrl / dac/phone reg and ctrl 
    

#define WRITE_BUFFER_SIZE  128
#define READ_BUFFER_SIZE  128
#define MEM_ADDRESS  0x00

#define PHONO_REGI   0x01
#define DAC_STATUS_CHANGE     0x0040
#define DAC_REGI     0x02
#define DSD_ON_OFF   0x2000
#define CHARGING     0x4000
#define USB_PLUGGED  0x8000
#define PHONO_REG_LED_OFF    0x04
#define DAC_REG_LED_OFF      0x08
#define PHONO_REG_LED_ON   0xFB
#define DAC_REG_LED_ON     0xF7
#define PICKUP_MM    0x01
#define PICKUP_MC    0xFE   

#define mode100 0
#define mode75  1
#define mode50  2
#define mode25  3
#define modeOff 4
#define modeDim 5
    
#define GB1     0
#define GB2     1


#define avLevInp    66

#define frontPanelIR 1
#define rearPanelIR  0

#define movingMagnet 1
#define movingCoil  0



#define dacIoExpAddress 0x20
#define dirAddress 0x10
#define dacAddress 0x48

#define dirReg1         1
#define dirReg3         3
#define dirReg3Setting  0x48
#define dirReg1Setting  0x5A    //DFS default, DEM1-0 default,  

#define dacReg0         0
#define dacReg1         1
#define dacReg37        37
#define dacReg42        42
#define dacReg57        57
#define dacReg58        58
#define dacReg59        59
#define dacReg62        62
#define dacReg64        64
#define dacReg74        74
#define dacReg75        75

#define dacReg82        82
#define dacReg83        83
#define dacReg86        86
#define dacReg88        88
#define dacReg89        89
#define dacReg123       123
#define dacReg124       124
#define dacReg125       125

#define dacMute         0xFF
#define dacUnMute       0x00

#define dacEnable       0x02
#define dacDisable      0x00

#define modeI2sPcm      0x41
#define modeI2sDsd      0x43
#define modeSpDif       0x46 //Var 0x46

#define actionScr       0x11
#define simpViewScr     0xff

    
#define WRITE_BUFFER_SIZE  128
#define READ_BUFFER_SIZE  128
#define MEM_ADDRESS  0x00

// ---------- GreenBias modes ----------
typedef enum {
    GB_MODE_OFF,   // GB0
    GB_MODE_MID,   // GB1
    GB_MODE_LOW,   // GB2
    GB_MODE_HIGH   // GB1+GB2
} greenbias_mode_t;   
    
// *****************************************************************************
/* Application states

  Summary:
    Application states enumeration

  Description:
    This enumeration defines the valid application states.  These states
    determine the behavior of the application at various times.
*/
typedef enum
{
     UIREQ_NONE,
     UIREQ_SHOW_DSDLP,
     UIREQ_GOTO_SIMPLE,
     UIREQ_GOTO_ACTION,
     UIREQ_SHOW_FILTER_SIMPLE,
     UIREQ_SHOW_GAIN_SIMPLE,
     UIREQ_SHOW_DISP_SIMPLE,
     UIREQ_GOTO_MENU,
     UIREQ_EXIT_MENU    
}UI_REQ;

typedef enum
{
    /* Application's state machine's initial state. */
    APP_STATE_INIT=0,
    APP_ACTION_SCREEN_TASKS,
    APP_SIMPLEVIEW_SCREEN_TASKS,        
    APP_VOL_SETTING_SCREEN_TASKS,   
    APP_INPUT_LVL_MATCH_SCREEN_TASKS,
    APP_STABILIZING_PROGRESS_TASKS,        
    APP_DIGTAL_SETTING_TASKS,
    APP_QWERTY_TASKS,            
    APP_STATE_IDLE,
    APP_LEFT_AC_ERROR,        
    APP_ACTIVATE_BOOTLOADER,
    //APP_DISPLAY_ERROR, 
    APP_SN_SET_SCREEN_TASKS,
            
                
    /* TODO: Define states used by the application state machine. */

} APP_STATES;


//typedef enum
//{
//    QWERTY_STATE_ALPHA=0,
//    QWERTY_STATE_NUM,
//    QWERTY_STATE_KEYPAD_CLICK,       
//    QWERTY_STATE_SPACE,        
//    QWERTY_STATE_TXT_FIELD_CHANGE,                    
//    QWERTY_STATE_OK,
//    QWERTY_STATE_IDLE,
//} QWERTY_STATES;

typedef struct
{
    /* The application's current state */
    APP_STATES state;
    
    uint8_t     uiOverlayActive;
    APP_STATES  prevStateForOverlay;
    SYS_TIME_HANDLE remoteViewShiftDelayHandle;    
    SYS_TIME_HANDLE keyPressedDelayHandle;    
    SYS_TIME_HANDLE inputShiftMuteDelayHandle;    
    SYS_TIME_HANDLE keyRepeatDelayHandle;    
    SYS_TIME_HANDLE screenSwapDelayHandle;    
    SYS_TIME_HANDLE actionViewTimeOutHandle;    
    SYS_TIME_HANDLE autoDispTimeOutHandle;  
    SYS_TIME_HANDLE fanCheckTimeOutHandle;  
    SYS_TIME_HANDLE stabilizingProgressDelayHandle;
    
    volatile UI_REQ reqUiAction;      // UI-request fra ikke-UI kontekst
    volatile uint8_t reqApplyDsdLp;    // Anmodning om at kre dacSetDsdLpFilter()
    volatile uint8_t reqApplyPcmFilter; // Anmodning om at apply PCM filter (HW+evt UI)
    volatile uint8_t irDeferredDisplayOnFlg;
    volatile uint32_t irDeferredDisplayScreenId;
    volatile uint8_t irDeferredDisplayArmFlg;
    
    volatile bool keyPressedDelayExpired;    
    volatile bool screenSwapDelayExpired;    
    volatile bool fanCheckTimeOutExpired;    
    volatile bool actionViewTimeOutExpired;    
    volatile bool keyRepeatDelayExpired;    
    volatile bool dispTimeOutExpired;    
    volatile bool plusKeyPressed;    
    volatile bool minusKeyPressed;
    volatile uint8_t eepromRW_Done;
    volatile bool volWrite_Done;
    volatile bool dacInstalled;
    volatile bool skipUnmuteFlg;
    volatile bool muteFlg;
    volatile bool muteToggleFlg;
    volatile bool oldMuteFlg;
    volatile bool monitorFlg;
    volatile bool menuFlg;
    volatile bool phonoRegiFlg;
    volatile bool dacRegiFlg;
    volatile bool leftDcHfFlg;
    volatile bool rightDcHfFlg;
    volatile bool leftTempFlg;
    volatile bool rightTempFlg;
    volatile bool acErrorFlg;
    volatile bool irInputChangeFlg;
    volatile bool saveDisplayFlg;
    volatile bool dispSleepActiveFlg;
    volatile bool wakingUpFlg;
//    volatile bool usbPluggedFlg;
    volatile bool ampStatusChangeFlg;
    volatile bool powerOnFlg;
    volatile bool wakeUpFlg;
    volatile bool shutDwnStartedFlg;
    volatile bool avFlg;
    volatile bool startupFlg;
    volatile bool fanErrorFlg;
    volatile bool inputMuteActiveFlg;
    volatile uint32_t   inputMuteUntilMs;
    volatile bool inputMuteTimedOutFlg;
    volatile bool errorCheckFlg;
    volatile bool remoteViewDelayFlg;
    
    volatile uint8_t  preRemoteDispChange;
    volatile uint8_t  wakeUpCnt;
    volatile uint8_t  activeActionButton;
    volatile uint8_t  snSingles;
    volatile uint8_t  snTens;
    volatile uint8_t  snHundreds;
    volatile uint8_t  snThousands;
    volatile uint8_t  errorStatus;
    volatile uint8_t  tempErrorStatus;
    volatile uint8_t  touchState;
    volatile uint8_t  voltageSetting;
    volatile uint8_t  stabilizingProgress;
    volatile uint8_t  enableSimpleViewFlg;
    volatile uint8_t  inpToRename;
    volatile uint8_t  maxLvl;
    volatile uint8_t  balance;
    volatile uint8_t  oldMaxLvl;
    volatile uint8_t  startLvl;
    volatile uint8_t  oldStartLvl;
    volatile uint8_t  maxInp;
    volatile uint8_t  curInp;
    volatile uint8_t  oldInp;
    volatile uint8_t  curLvl;
    volatile uint8_t  dispMode;
    volatile uint8_t  greenBias;
    volatile uint8_t  irSource;
    volatile uint8_t  avInp;
    volatile uint8_t reqSimpleViewPopup; // 0=none, 1=Filter, 2=Gain, 3=DSDLP
//    volatile uint8_t  pcmFilter;
//    volatile uint8_t  dsdFilter;
//    volatile uint8_t  dsdLpFilter;
//    volatile uint8_t  digiGain;
    volatile uint8_t  pickupSelection;
    volatile uint8_t  oldPickupSelection;
    volatile uint8_t  inpSens[7];
    volatile uint8_t  oldInpSensValue;
    volatile uint8_t  inpToLvlMatch;
    volatile uint8_t  fanSpeed;
    volatile uint8_t  u13Byte0;
    volatile uint8_t  u26Byte0;
    volatile uint8_t  u26Byte1;
    volatile uint8_t  u26Byte2;
    
//    uint64_t prevCounterVal;        

} APP_DATA;

// States (eksempel)
typedef enum {
    DIR_FS_IDLE = 0,
    DIR_FS_WAIT_FIRST,
    DIR_FS_RETRY,
    DIR_FS_POLL,
    DIR_FS_MONITOR        
} dir_fs_state_t;

typedef struct
{
    dir_fs_state_t state;
    uint32_t tNextMs;

    uint8_t  curFs;        
    uint8_t  lastValidFs;  
    uint8_t  retryCnt;

    // reinit logic
    uint8_t  failCycles;      // antal gange vi har ramt "retry max" i trk
    uint8_t  reinitCnt;       // reinits i den nuvrende lock-periode
    uint32_t reinitBlockUntilMs; // cooldown, s vi ikke reinit'er for ofte
} dir_fs_acq_t;



typedef struct
{
    volatile bool lockedButNoSignalTimeOutExpired;    
    SYS_TIME_HANDLE lockedButNoSignalTimeOutHandle;  
    SYS_TIME_HANDLE forceUpdateTimeOutHandle;
    volatile bool forceUpdateTimeOutExpired;    
    volatile bool usbCharging;
    volatile bool dirIntFlg;
    volatile bool dsdOnFlg;
    volatile bool usbPluggedFlg;
    volatile bool signalLockFlg;
    volatile bool dacMuteFlg;
    volatile bool dacUnpluggedMuteFlg;
    volatile bool dacDigiChangeFlg;
    volatile bool dacStatusChangeFlg;
    
    volatile uint8_t  pcmFilter;
    volatile uint8_t  oldPcmFilter;
    volatile uint8_t  dsdFilter;
    volatile uint8_t  oldDsdLpFilter;
    volatile uint8_t  dsdLpFilter;
    volatile uint8_t  digiGain;
    volatile uint8_t  lockedButNoFsCnt;
    
    volatile uint8_t  dacIoExpStatus;
    volatile uint8_t  dacIoExpOutByte;
        
    volatile uint8_t  usbFs;
    volatile uint8_t  spdifFs;
    dir_fs_acq_t dirFs;

     
} DAC_DATA;

#define DIR_FS_FIRST_DELAY_MS        30u
#define DIR_FS_RETRY_DELAY_MS        20u
#define DIR_FS_RETRY_MAX             10u   // 200ms pr cycle
//
#define DIR_FS_FAIL_CYCLES_BEFORE_REINIT  3u   // 3 * 400ms ~ 1.2s konstant FS=1
//#define DIR_FS_REINIT_COOLDOWN_MS        1000u // mindst 1s mellem reinits
//#define DIR_FS_REINIT_MAX_PER_LOCK       2u    // max 2 reinits mens locked
// Tune disse s de passer til din DIR og din UI-rate
#define DIR_FS_POLL_MS                 60u   // hvor tit vi lser DIR nr locked
#define DIR_FS_LOCK_EDGE_REINIT_DELAY  20u   // kort settle efter reinit
#define DIR_FS_STABLE_SAMPLES          2u    // antal ens samples fr commit
#define DIR_FS_INVALID_BEFORE_REINIT   6u    // 6*60ms = 360ms med fs==1 -> reinit
//#define DIR_FS_REINIT_COOLDOWN_MS      400u  // undg reinit-spam
#define DIR_FS_REINIT_MAX_PER_LOCK     3u
// Poll-intervaller (tune dem)
#define DIR_FS_LOCK_EDGE_REINIT_SETTLE_MS   20u
#define DIR_FS_POLL_PERIOD_MS              150u   // hvor tit vi tjekker FS nr locked
#//define DIR_FS_RETRY_DELAY_MS              50u
//#define DIR_FS_RETRY_MAX                   4u
#define DIR_FS_FAIL_CYCLES_BEFORE_REINIT   3u
#define DIR_FS_REINIT_COOLDOWN_MS          600u
#define DIR_FS_REINIT_MAX_PER_LOCK         3u

#define DIR_FS_LOCK_EDGE_REINIT_DELAY_MS   20u
#define DIR_FS_MONITOR_POLL_MS            200u   // hvor tit vi check'er FS mens lock er 1
#define DIR_FS_MONITOR_BAD_TO_BLANK         3u   // antal gange fs==1 fr vi blanker

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Routines
// *****************************************************************************
// *****************************************************************************
/* These routines are called by drivers when certain events occur.
*/
//
//typedef enum
//{
//    /* ON_OFF sekvens state machine's initial state. */
//    ON_SEKVENS_1=0,
//    ON_SEKVENS_2,
//    ON_SEKVENS_3,
//    ON_SEKVENS_4,
//    ON_SEKVENS_5,
//    ON_SEKVENS_6,
//    ON_SEKVENS_7,        
//    OFF_SEKVENS_1,
//    ON_OFF_SEKVENS_IDLE,
//    /* TODO: Define states used by the application state machine. */
//
//} ON_OFF_SEKVENS_STATES;
//typedef struct
//{
//   SYS_TIME_HANDLE onOffSekvensTimer; 
//   SYS_TIME_HANDLE initBlinkTimer; 
//   
//}ON_OFF_SEKVENS_DATA;

extern volatile bool g_digiInfoDirty;
extern volatile bool digiCacheInvalid;
extern uint32_t millis32(void);
/* Match dine eksisterende EEPROM-funktioner */
bool getBootCounterFromEEProm(uint16_t *out);
bool saveBootCounterToEEProm(uint16_t v);
bool incBootCounterInEEProm(uint16_t *newVal);

void asyncOn(void);
void syncOn(void);
void dacSetup(void);
void dirSetup(void);
void lockedButNoFs_Callback (uintptr_t context);
void onOffButtonEventHandler(EXTERNAL_INT_PIN pin, uintptr_t context);
void APP_PIN_Handler(GPIO_PIN pin, uintptr_t context);   
void setDisplayIntensity(void);
void setBackLightIntensity(uint16_t intensity);
void screenSwap(void);
void saveDisp(void);
void toggleMute(void);
void unMuteInput(void);
void irToggleMute(void);
void inputMuteTimeOut(void);
void InputMute_Service(void);
void initQwerty(void);
void irReceive (void);
void RequestPowerOff_FromIR(void);
void irReceiveEventHandler(GPIO_PIN pin, uintptr_t context);
void actionViewTimeOut_Callback( uintptr_t context );
void autoDispTimeOut_Callback( uintptr_t context );
void forceUpdate_Callback (uintptr_t context);
void getInpNamesFromEEProm(void);
void showDigiInfoPanel (void);
void updateDigiInfoPanel (void);
void writeEEpromDefault (void);
void writeEEpromDefaultIfEmty (void);
void getInpNamesFromEEProm(void);
void getEEPromValues(void);
void saveInpName(void);
void getSNFromEEProm(void);
void saveSNToEEProm(void);
void saveDigitalSetup(void);
void saveDisplaySettings(void);
void saveInpLvlMatchValues (void);
void saveIRSourceSetting(void);
void savePickupSelection(void);
void saveGreenBias(void);
void setGreenBiasMode(greenbias_mode_t mode);
void u26WriteOutputs (uint8_t u26Byte0,uint8_t u26Byte2);
void U26_SetInputRelayBits(uint8_t relayMaskByte0);
void U26_UpdateGreenBiasFromLevel(void);
void eePromCallback ( uintptr_t context );
void hideDigiInfoPanel (void);
void initScreenSwapDelay (void);
void clrSelectedInput(void);
void inpShiftMuteDelay_Callback(uintptr_t context);
void remoteViewDelay_Callback(uintptr_t context);
void remoteViewDispDelay_Callback(uintptr_t context);
void dacsetVolRateUp(uint8_t rate);
void dacsetVolRateDwn(uint8_t rate);
void dacU26InitIoExp(void);
void setActiveInput(void);
void dacSetDsdLpFilter(void);
void getDacStatus (void);
void setDacSpdifInput(void);
void setLevelZero (void);
void checkForLeftPSFallOut(void);
uint16_t readDacIoExpInputs (void);
void setAutoMuteEnableOff(void);
void setDacSysModeConfig(void);
void dacSetupSpDif (void);
void dacSetGain(void);
void setInputFormat(uint8_t format);
void toggleMasterSlaveBit(void);
void dacSetPcmFilter(void);
void DacHw_ApplyPcmFilterFromState(void);
void DacUi_SyncPcmFilter_CurrentScreen(void);
void DacUi_SyncDigiGain_CurrentScreen(void);

void DacHw_ApplyDsdLpFilterFromState(void);
void DacUi_SyncDsdLp_CurrentScreen(void);
//void DacUi_SyncPcmFilter_ActionScreen(uint8_t f);
void DacUi_SyncPcmFilterLabels_ActionScreen(uint8_t f);
void dacEnableGpio(void);
void setDigitalInput(void);
void dacChMute(uint8_t muteValue);
void dacGpioConfig(void);
void setAutoMuteEnableOn(void);
void setMuteRampToGndOff(void);
void setInput(void);
void setAvLevel(void);
void saveAvSettings(void);
void saveCurrentInput (void);
void saveVolumeSettings(void);
bool EEPROM_SaveVoltageSetting(voltage_setting_t v);
void u16InitIoExp (void);
void u20InitIoExp (void);
void UpdateVolume(void);
void showValidInputs(void);
void tdmChConfig (void);
void dacSetupI2s (void);
void dacOn (void);
uint8_t dirGetFs(void);
void dsdLpOff(void);
void i2sDirOn (void);
void dirReset(void);
void dirSetup(void);
void enterBootloaderMode(void);
void setDirInput(void);
void setInputRelay(void);
void mute (void);
void muteOn (void);
void muteOff (void);
void outputMuteOn(void); 
void outputMuteOff(void); 
void createSN(void);
void updateInpLvlMatchScreen(void);
void updateDigitaleSettingScreen(void);
void updateVolSettingScreen (void);
void updateSnSetScreen (void);
void updateProgressBar(void);
void U26_showModulesInstalled(void);
void getAmpStatus(void);
void handleDacStatusChange(void);
void handlePhonoConfiguration(void);
void handleDacConfiguration(void);
void checkStatus(void);
void u26InitIoExp (void);
void U26_ApplyPickupHwFromSelection(void);
void uartClearBuffer(void);
void uartCtrl(void);
void updateSimpleViewScreen(void);
void updateActionScreen (void);
void updateVolumeDisplay(void);
void updateQwerty(void);
void updateLeftAcMissingScreen(void);
void wakeUp(void);
void PollPowerInputs_12V_ForOff(void);
void cleanUp (void);
void fadeBacklightIn(void);
extern void initAmp(void);
extern void onOffSekvens(void);
extern APP_DATA appData;
extern DAC_DATA dacData;
//extern ON_OFF_SEKVENS_STATES onOffState;
void setVolI2cCallback ( uintptr_t context );
void activateBootloaderEventHandler(GPIO_PIN pin, uintptr_t context);
void fadeBacklightOut(void);
void ActionTouch_OnError(void);
void irReceiveEventHandler(GPIO_PIN pin, uintptr_t context);
void ServiceIr(void);
static inline uint32_t ms_elapsed(uint32_t now, uint32_t then);

bool PollIrForOn(uint32_t window_ms);

void outputMuteOn(void);
void outputMuteOff(void);

void minus6dBOn(void);
void minus6dBOff(void);
uint32_t millis_32(void);

//extern void emulateEEProm(void);


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Summary:
     MPLAB Harmony application initialization routine.

  Description:
    This function initializes the Harmony application.  It places the
    application in its initial state and prepares it to run so that its
    APP_Tasks function can be called.

  Precondition:
    All other system initialization routines should be called before calling
    this routine (in "SYS_Initialize").

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    APP_Initialize();
    </code>

  Remarks:
    This routine must be called from the SYS_Initialize function.
*/

void APP_Initialize ( void );


/*******************************************************************************
  Function:
    void APP_Tasks ( void )

  Summary:
    MPLAB Harmony Demo application tasks function

  Description:
    This routine is the Harmony Demo application's tasks function.  It
    defines the application's state machine and core logic.

  Precondition:
    The system and application initialization ("SYS_Initialize") should be
    called before calling this.

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    APP_Tasks();
    </code>

  Remarks:
    This routine must be called from SYS_Tasks() routine.
 */

void APP_Tasks( void );

#endif /* _APP_H */

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

/*******************************************************************************
 End of File
 */

