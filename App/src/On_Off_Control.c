#include "definitions.h" // indeholder app.h, system headers, legato types mm.
#include "ui_globals.h"
#include "app.h"
#include "user.h"
#include "config/default/peripheral/gpio/plib_gpio.h"


#include "voltageSetting.h"
#include "system/time/sys_time.h"
#include "ac_check.h"
#include "app_usb_cmd.h"

static uint32_t wakeUpTm = 0;
static uint32_t StUpTm = 0;

#define NOISE_GUARD_MS   500u

static uint32_t s_noiseStartMs = 0;
static bool     s_noiseArmed   = false;




static inline void NoiseGuard_Disarm(void)
{
    s_noiseArmed = false;
}

static inline bool NoiseGuard_Expired(uint32_t now)
{
    return s_noiseArmed && (ms_elapsed(now, s_noiseStartMs) >= NOISE_GUARD_MS);
}

static inline uint32_t ms_elapsed(uint32_t now, uint32_t then) {
    // 100% wrap-safe (uint32 overflow er defineret)
    return (uint32_t) (now - then);
}

static inline uint32_t millis(void) {
    const uint32_t f = (uint32_t) SYS_TIME_FrequencyGet();
    if (f == 0u) return 0u;

    const uint64_t c = (uint64_t) SYS_TIME_CounterGet();
    return (uint32_t) ((c * 1000u) / (uint64_t) f);
}

static inline uint16_t millis16_raw(void) {
    // Hvis din SYS_TIME allerede krer i 1ms ticks og CounterGet() er tick-count:
    // return (uint16_t)SYS_TIME_CounterGet();
    //
    // Hvis du SKAL bruge din eksisterende millis()-beregning, s kan du tage low16 af den:
    return (uint16_t) millis(); // bruger din nuvrende millis(), men antager den wrap'er ved ~65s
}

uint32_t millis_32(void) {
    static uint16_t s_last16 = 0;
    static uint32_t s_high = 0;

    uint16_t cur16 = millis16_raw();

    // wrap detektion
    if (cur16 < s_last16) {
        s_high += 0x10000u;
    }

    s_last16 = cur16;
    return (s_high | (uint32_t) cur16);
}

static inline void NoiseGuard_Arm(void)
{
    s_noiseStartMs = millis_32();
    s_noiseArmed   = true;
}

static void CloseHandle(SYS_TIME_HANDLE *handle)
{
    if (*handle != SYS_TIME_HANDLE_INVALID)
    {
        (void)SYS_TIME_TimerDestroy(*handle);
        *handle = SYS_TIME_HANDLE_INVALID;
    }
}

void CloseAllHandles(void)
{
    CloseHandle(&appData.remoteViewShiftDelayHandle);
    CloseHandle(&appData.keyPressedDelayHandle);
    CloseHandle(&appData.inputShiftMuteDelayHandle);
    CloseHandle(&appData.keyRepeatDelayHandle);
    CloseHandle(&appData.screenSwapDelayHandle);
    CloseHandle(&appData.actionViewTimeOutHandle);
    CloseHandle(&appData.autoDispTimeOutHandle);
    CloseHandle(&appData.fanCheckTimeOutHandle);
    CloseHandle(&appData.stabilizingProgressDelayHandle);
    CloseHandle(&appData.screenSwapDelayHandle);
    appData.screenSwapDelayExpired = 0;
}



typedef enum { PWR_EVT_NONE = 0, PWR_EVT_BTN, PWR_EVT_IR, PWR_EVT_12V } pwr_evt_t;

static struct {
    bool        link_blocked;     // true => ignorr 12V_link indtil manuel ON+OFF er set
    bool        manual_on_seen;   // set nr en manuel ON er sket i blokeret tilstand
    pwr_evt_t   last_on_cause;    // hvem tndte sidst
} pwrPolicy = {0};

static inline bool Link12V_IsActive(void)   { return (LINK_12V_Get() == 0); }  // aktiv-lav
static inline bool Link12V_IsInactive(void) { return (LINK_12V_Get() != 0); }

// --- 12V link edge detection (debounced) ---
// Vi arbejder på den LOGISKE tilstand (IsActive), så "rising" betyder Inactive->Active.
// Dette bruges til at kunne slukke på 12V uanset om der blev tændt via knap/IR/12V.
#define LINK12V_DEBOUNCE_MS  30u

static bool     s_link12v_lastRaw    = false;
static bool     s_link12v_lastStable = false;
static uint32_t s_link12v_lastChgMs  = 0u;

static inline void Link12V_EdgeInitIfNeeded(void)
{
    static bool inited = false;
    if (!inited)
    {
        bool a = Link12V_IsActive();
        s_link12v_lastRaw    = a;
        s_link12v_lastStable = a;
        s_link12v_lastChgMs  = millis_32();
        inited = true;
    }
}

static inline bool Link12V_FallingEdge(void)
{
    Link12V_EdgeInitIfNeeded();

    const uint32_t now = millis_32();
    const bool raw = Link12V_IsActive();

    if (raw != s_link12v_lastRaw)
    {
        s_link12v_lastRaw   = raw;
        s_link12v_lastChgMs = now;
    }

    if (ms_elapsed(now, s_link12v_lastChgMs) < LINK12V_DEBOUNCE_MS)
        return false;

    if (raw != s_link12v_lastStable)
    {
        const bool prev = s_link12v_lastStable;
        s_link12v_lastStable = raw;
        // falling: Active -> Inactive
        return (prev == true) && (raw == false);
    }
    return false;
}

static void Policy_OnPowerOn(pwr_evt_t cause)
{
    pwrPolicy.last_on_cause = cause;
    if (pwrPolicy.link_blocked && (cause == PWR_EVT_BTN || cause == PWR_EVT_IR)) {
        // Frste manuelle ON efter blokering
        pwrPolicy.manual_on_seen = true;
    }
}

static void Policy_OnPowerOff(pwr_evt_t cause)
{
   #if ENABLE_DEBUG_PRINTS
    const char* cause_str = "?";
    switch(cause) {
        case PWR_EVT_NONE: cause_str = "NONE"; break;
        case PWR_EVT_BTN:  cause_str = "BUTTON"; break;
        case PWR_EVT_IR:   cause_str = "IR"; break;
        case PWR_EVT_12V:  cause_str = "12V"; break;
    }
    
    DEBUG_PRINT("Policy_OnPowerOff: cause=%s, last_on_cause=%d, link_blocked=%d, manual_on_seen=%d\r\n",
                cause_str, pwrPolicy.last_on_cause,
                pwrPolicy.link_blocked, pwrPolicy.manual_on_seen);    
    #endif
    // NY politik (B + manuel ON altid tilladt):
    // Hvis der slukkes manuelt mens 12V er aktiv -> bloker 12V->ON indtil 12V har været inaktiv.
    if ((cause == PWR_EVT_BTN || cause == PWR_EVT_IR) && Link12V_IsActive())
    {
        pwrPolicy.link_blocked   = true;
        pwrPolicy.manual_on_seen = false;
        DEBUG_PRINT("Policy: Manual OFF while 12V active -> block 12V->ON until link inactive\r\n");
    }

    pwrPolicy.last_on_cause = PWR_EVT_NONE;
}

void RequestPowerOff_FromIR(void)
{
    Policy_OnPowerOff(PWR_EVT_IR);
    onOffState = OFF_SEKVENS_1;
}

void enterBootloaderMode(void)
{
    DEBUG_PRINT("\n\r####### Bootloader Triggered #######\n\r");
    DEBUG_PRINT("\n\r####### Program new firmware from Bootloader #######\n\r");

    APP_TriggerBootloader();

  
}

void PollPowerInputs_12V_ForOff(void) {
    // Sluk på 12V falling-edge UANSET tænd-kilde (krav fra dig)
    if (appData.powerOnFlg || appData.startupFlg)
    {
        if (Link12V_FallingEdge())
        {
            DEBUG_PRINT("12V falling -> power off\r\n");
            Policy_OnPowerOff(PWR_EVT_12V);
            onOffState = OFF_SEKVENS_1;
        }
    }

    // Frigiv blokering når link er inaktiv (så næste rising kan tænde igen)
    if (pwrPolicy.link_blocked && Link12V_IsInactive())
    {
        pwrPolicy.link_blocked   = false;
        pwrPolicy.manual_on_seen = false;
        DEBUG_PRINT("Policy: Link inactive -> unblock 12V\r\n");
    }
}


void activateBootloaderEventHandler(GPIO_PIN pin, uintptr_t context)
{
    if(!ACTIVATE_BOOTLOADER_Get())
      appData.state = APP_ACTIVATE_BOOTLOADER;
}


//void irReceiveEventHandler(GPIO_PIN pin, uintptr_t context)
//{
//    
//    if(!IR_RC5_Get() && appData.powerOnFlg && !appData.menuFlg) //!appData.startupFlg
//      irReceive(); 
//    if(!IR_RC5_Get() && !appData.powerOnFlg)
//        wakeUp();
//    //DEBUG_PRINT("ir int\r\n");
//}




void wakeUp(void);

void APP_PIN_Handler(GPIO_PIN pin, uintptr_t context)
{
//    RGB_LED_R_On();
  ///  RGB_LED_B_Off();
 //   RGB_LED_G_Off();
//    if(appData.powerOnFlg == 1)
//        onOffState = OFF_SEKVENS_1;
//    if(ON_OFF_BUTTON_Get() && !appData.powerOnFlg)
//    {
//       CORETIMER_DelayMs (20); 
//       if(ON_OFF_BUTTON_Get() && !appData.powerOnFlg)
//            wakeUp();
//    }

    
    
    // OFF (IDLE-hold): tillad ON via CN/IOC (INT0 kan være låst høj af 12V)
    if (ON_OFF_BUTTON_Get() && !appData.powerOnFlg && !appData.startupFlg)
    {
        // lille debounce (samme stil som din eksisterende OFF ved ON-tilstand)
        CORETIMER_DelayMs(20);
        if (ON_OFF_BUTTON_Get() && !appData.powerOnFlg && !appData.startupFlg)
        {
#if ENABLE_DEBUG_PRINTS
            DEBUG_PRINT("Power on by button (CN)\r\n");
#endif
            // Brug den eksisterende wakeUp() logik (sætter onOffState + Policy_OnPowerOn)
            wakeUp();
            return;
        }
    }

if(ON_OFF_BUTTON_Get() && appData.powerOnFlg)
    {
       CORETIMER_DelayMs (20); 
       if(ON_OFF_BUTTON_Get() && appData.powerOnFlg)
       { 
          Policy_OnPowerOff(PWR_EVT_BTN);
          onOffState = OFF_SEKVENS_1; //Start On sequence
          DEBUG_PRINT("Power off by button\r\n");
       }
       
    }    
        
}

void onOffButtonEventHandler(EXTERNAL_INT_PIN pin, uintptr_t context)
    {
      //DEBUG_PRINT("int0");
      if(!appData.powerOnFlg && !appData.startupFlg)
      {
        if(POWER_DS_WakeupSourceGet() == POWER_DS_WAKEUP_SOURCE_DSINT0)
         {
           POWER_DS_WakeupSourceClear(POWER_DS_WAKEUP_SOURCE_DSINT0);
         }
        wakeUp();
      }
        
    }


void cleanUp (void)
{
    if(onOffSekvensData.initBlinkTimer)
      SYS_TIME_TimerDestroy(onOffSekvensData.initBlinkTimer); //Stop Logoblink
    if(appData.remoteViewShiftDelayHandle)    
        SYS_TIME_TimerDestroy(appData.remoteViewShiftDelayHandle);
    if(appData.inputShiftMuteDelayHandle)    
        SYS_TIME_TimerDestroy(appData.inputShiftMuteDelayHandle);
    if(appData.actionViewTimeOutHandle)    
        SYS_TIME_TimerDestroy(appData.actionViewTimeOutHandle); 
    if(appData.autoDispTimeOutHandle)
        SYS_TIME_TimerDestroy(appData.autoDispTimeOutHandle);
    if(appData.stabilizingProgressDelayHandle)
        SYS_TIME_TimerDestroy(appData.stabilizingProgressDelayHandle);

    if(appData.keyPressedDelayHandle)
   {
      SYS_TIME_TimerDestroy(appData.keyPressedDelayHandle);
      appData.keyPressedDelayExpired = false;
   }
   if(appData.keyRepeatDelayHandle)
   {
       SYS_TIME_TimerDestroy(appData.keyRepeatDelayHandle);
       appData.keyRepeatDelayExpired = false;
   }
   appData.minusKeyPressed = false;
   appData.plusKeyPressed = false;
//   DEBUG_PRINT("\r\n*** Cleanup Done ***\r\n");
}



void onSekvens1_Callback ( uintptr_t context )
{
    onOffState = ON_SEKVENS_2;
    //DEBUG_PRINT("onSekvens1_Callback\r\n");
}
void onSekvens2_Callback ( uintptr_t context )
{
    onOffState = ON_SEKVENS_3;
    //DEBUG_PRINT("onSekvens2_Callback\r\n");
}

void onSekvens3_Callback ( uintptr_t context )
{
    onOffState = ON_SEKVENS_4;
    //DEBUG_PRINT("onSekvens3_Callback\r\n");
}

void onSekvens4_Callback ( uintptr_t context )
{
    onOffState = ON_SEKVENS_5;
    //DEBUG_PRINT("onSekvens4_Callback\r\n");
}
void onSekvens5_Callback ( uintptr_t context )
{
    onOffState = ON_SEKVENS_6;
    //DEBUG_PRINT("onSekvens5_Callback\r\n");
}

void onSekvens6_Callback ( uintptr_t context )
{
    onOffState = ON_SEKVENS_7;
    //DEBUG_PRINT("onSekvens6_Callback\r\n");
}
void onSekvens7_Callback ( uintptr_t context )
{
    onOffState = ON_SEKVENS_8;
    //DEBUG_PRINT("onSekvens6_Callback\r\n");
}

//void offSekvens1_Callback ( uintptr_t context )
//{
//    onOffState = OFF_SEKVENS_2;
//}

void logoBlink_Callback ( uintptr_t context )
{
   GAD_LOGO_Toggle(); 
}

/*********************************************************************************
**********************    AC_CHECK    ********************************************
*********************************************************************************/   

void AC_CHECK(void)
{
    uint8_t ActualVoltage = 0;

    
    CORETIMER_DelayMs(10); 
    
    
    if(AC_RESULT_Get())
      ActualVoltage = VoltageLow;
    else
      ActualVoltage = VoltageHigh;
 
    CORETIMER_DelayMs(50);                           
    if (ActualVoltage != appData.voltageSetting)
    {
 //       DEBUG_PRINT("\r\n wrong AC Voltage : %x\r\n",appData.voltageSetting);
        while(1)
        {
            CORETIMER_DelayMs(1000);
            ONSTBY_LED_Toggle();
            if(appData.state == APP_ACTIVATE_BOOTLOADER )
            {
                DEBUG_PRINT("\n\r####### Bootloader Triggered #######\n\r");
                DEBUG_PRINT("\n\r####### Program new firmware from Bootloader #######\n\r");

                APP_TriggerBootloader();

            }
            if(AC_RESULT_Get())
               ActualVoltage = VoltageLow;
            else
               ActualVoltage = VoltageHigh;
            if(ActualVoltage == appData.voltageSetting)
              APP_SystemReset( );//break;
        }
    } 
    
    if(appData.voltageSetting == VoltageLow)
      SP_RELAY_Set();
    else
      SP_RELAY_Clear();
    CORETIMER_DelayMs(50);
    
}

void updateLeftAcMissingScreen(void)
{
  const bool ac = AC_RESET_Get();  
  static bool leftPowerMissingIndicated = false;
  if(!leftPowerMissingIndicated)
    {
      printf("left missing \r\n");
        TMR2_Start();
        DRV_TOUCH_PIN_RESET_Set();
        GLCD_DISP_ON_STBY_Set();
        setBackLightIntensity(100);
        legato_showScreen(screenID_leftPowerMissingScreen);                
        leftPowerMissingIndicated = true;
    }
    
  if(ac)
  {
    CORETIMER_DelayMs(50);
    if(ac)
    {
        printf("left ok - reset \r\n");
        CORETIMER_DelayMs(50);
       APP_SystemReset(); 
    }
  }

}

static inline uint32_t ct_now(void) { return _CP0_GET_COUNT(); }

// Blokerer indtil AC_RESET_get() har vret high i 100ms i trk.
// Imens AC_RESET_get() er low toggles GAD_LOGO_Toggle() hver 2sek.
void WaitFor_AC_RESET_High_100ms(void)
{
    
    const uint32_t need_high = CORE_TIMER_FREQUENCY / 10u;       // 100 ms
    const uint32_t blink_int = CORE_TIMER_FREQUENCY * 2; // 10u;       // 100 ms

    uint32_t high_start = 0;
    uint32_t last_blink = ct_now();

    for (;;)
    {
        const bool ac = AC_RESET_Get();
        const uint32_t now = ct_now();

        if (ac)
        {
            if (high_start == 0)
                high_start = now;

            if ((uint32_t)(now - high_start) >= need_high)
                return;
        }
        else
        {
            high_start = 0;

            if ((uint32_t)(now - last_blink) >= blink_int)
            {
                //GAD_LOGO_Toggle();
                last_blink = now;
                appData.state = APP_LEFT_AC_ERROR;
                return;
            }
        }
    }
}

void initAmp(void)
{
   // WaitFor_AC_RESET_High_100ms();
    
    initQwerty();
    
//    {
//    voltage_setting_t vs;
//    if (!EEPROM_LoadVoltageSetting(&vs)) {
//        // I2C/EEPROM er mske ikke klar p dette tidspunkt ? brug default i RAM
//        vs = VoltageSetting_Default();
//        // VIGTIGT: ingen EEPROM_SaveVoltageSetting(vs) her!
//        // Vi skriver senere via USB-kommando eller nr systemet er helt oppe.
//        printf("eepromlsning fejlet\n");
//    }
//    appData.voltageSetting = vs;
//    }
//    {
//      voltage_setting_t vs;
//      if (!EEPROM_LoadVoltageSetting(&vs)) {
//          vs = VoltageSetting_Default();
//          (void)EEPROM_SaveVoltageSetting(vs);   // skriv default frste gang
//      }
//      appData.voltageSetting = vs;
//    }
//
//    
//    appData.voltageSetting = VoltageSetting_Default();
//    printf("Init Amp Voltage Setting set = Default\n");
    DRV_TOUCH_PIN_RESET_OutputEnable();
    //SN_CHANGE_InputEnable();
    //CORETIMER_DelayMs(50);  
    
    //CORETIMER_Start();
    appData.powerOnFlg = 0;
    
    I2C2_CallbackRegister(eePromCallback, (uintptr_t)NULL);
    I2C3_CallbackRegister(setVolI2cCallback, (uintptr_t)NULL);

    onOffState = ON_OFF_SEKVENS_IDLE;
    IR_SOURCE_Set();
    if(GPIO_PinInterruptCallbackRegister(ON_OFF_BUTTON_PIN, APP_PIN_Handler,(uintptr_t) NULL))
    {
    // callback got registered
        ON_OFF_BUTTON_InterruptEnable();
        
    }
    
   if(GPIO_PinInterruptCallbackRegister( IR_RC5_PIN, irReceiveEventHandler, (uintptr_t) NULL ))
     {
         //DEBUG_PRINT("irINT\r\n");
       IR_RC5_InterruptDisable(); 
     }   
    
    
     if(GPIO_PinInterruptCallbackRegister( ACTIVATE_BOOTLOADER_PIN, activateBootloaderEventHandler, (uintptr_t) NULL ))
     {
        // DEBUG_PRINT("Bootloader Activated\r\n");
            ACTIVATE_BOOTLOADER_InterruptEnable();
     }   
    
    

    if(EVIC_ExternalInterruptCallbackRegister(EXTERNAL_INT_0, &onOffButtonEventHandler,(uintptr_t)NULL))
    {
        EVIC_ExternalInterruptEnable( EXTERNAL_INT_0 );
        EVIC_SourceStatusClear( EXTERNAL_INT_0 );
        // callback got registered
    } 
    appData.wakeUpFlg = 0;
    // Hvis 12V allerede er aktiv ved boot (ingen INT0-flanke endnu), s start ON-sekvens med det samme.
    if (Link12V_IsActive()&& !pwrPolicy.link_blocked)
    {
        CORETIMER_DelayMs(50);
        if (Link12V_IsActive()&& !pwrPolicy.link_blocked)
        {
           DEBUG_PRINT("12V present at boot -> start ON sequence\r\n");
           onOffState = ON_SEKVENS_AC_CHECK;
           Policy_OnPowerOn(PWR_EVT_12V);
           //EVIC_ExternalInterruptDisable( EXTERNAL_INT_0 );
        }
    }
    else if((POWER_DS_WakeupSourceGet() != POWER_DS_WAKEUP_SOURCE_DSINT0) && (appData.state != APP_LEFT_AC_ERROR)  )
    {
        DEBUG_PRINT("WAKEUP SOURCE: %x : SLEEEEP\r\n", POWER_DS_WakeupSourceGet());
        EVIC_ExternalInterruptEnable( EXTERNAL_INT_0 );
        CORETIMER_DelayMs(50);
        onOffState = OFF_SEKVENS_1;
        //POWER_LowPowerModeEnter( LOW_POWER_DEEP_SLEEP_MODE);
    }
//       
//////    if(POWER_DS_WakeupSourceGet() != POWER_DS_WAKEUP_SOURCE_DSINT0 )
//////    {
//////        DEBUG_PRINT("WAKEUP SOURCE: %x : SLEEEEP\r\n",POWER_DS_WakeupSourceGet());
//////       CORETIMER_DelayMs (50); 
//////       onOffState = OFF_SEKVENS_1;
//////       //POWER_LowPowerModeEnter( LOW_POWER_DEEP_SLEEP_MODE);
//////    }
////////        
    
    //DEBUG_PRINT("WAKEUP SOURCE: %x\r\n",POWER_DS_WakeupSourceGet());
    //writeEEpromDefaultIfEmty ();
    
//    AC_CHECK();
    getEEPromValues();
    dacData.forceUpdateTimeOutExpired = 0;
    
    if (appData.irSource)
        IR_SOURCE_Set();
    else
        IR_SOURCE_Clear();
    
    wakeUp();
}

//void wakeUp(void)
//{
//    if(appData.startupFlg || appData.wakeUpFlg)
//        return;
//    
//    if (!IR_RC5_Get()) {
//        irReceive(); // kan stte key
//    }
//
//    // IR: tnd
//    if (key == KeyOnOff && !appData.powerOnFlg  && !appData.startupFlg) {
//        
//        DEBUG_PRINT("IR accepted: t=%lu ms -> state=%d\r\n",
//            (unsigned long)millis_32(),
//            (int)onOffState);
//        onOffState = ON_SEKVENS_AC_CHECK;
//        wakeUpTm = millis_32();
//        appData.wakeUpFlg = 1;
//        appData.wakeUpCnt = 0;
//        Policy_OnPowerOn(PWR_EVT_IR);
//        
//        key = 0;
//    }
//
//    // ON/STBY-knap: tnd
//    if (ON_OFF_BUTTON_Get() && !appData.powerOnFlg && !appData.startupFlg) {
//        CORETIMER_DelayMs(20);
//        if (ON_OFF_BUTTON_Get() && !appData.powerOnFlg) {
//            wakeUpTm = millis_32();
//            onOffState = ON_SEKVENS_AC_CHECK;
//            DEBUG_PRINT("wakeup starting on sequence\r\n");
//            appData.wakeUpFlg = 1;
//            appData.wakeUpCnt = 0;
//            Policy_OnPowerOn(PWR_EVT_BTN);
//            
//        }
//    }
//
//    // 12V link: tnd (aktiv-lav) ? kun hvis ikke blokeret
//    if (Link12V_IsActive() && !appData.powerOnFlg  && !appData.startupFlg) {
//        CORETIMER_DelayMs(20);
//        if (Link12V_IsActive() && !pwrPolicy.link_blocked) {
//            DEBUG_PRINT("wakeup by 12V\r\n");
//            appData.wakeUpFlg = 1;
//            appData.wakeUpCnt = 0;
//            onOffState = ON_SEKVENS_AC_CHECK;
//            Policy_OnPowerOn(PWR_EVT_12V);
//            
//        }
//    }
//
//    // Noise-vagt (som fr)
//    if (!appData.wakeUpFlg) {
//        appData.wakeUpCnt++;
//        DEBUG_PRINT("WAKEUPCNT %d\r\n", appData.wakeUpCnt);
//        if (appData.wakeUpCnt > 5) {
//            appData.wakeUpCnt = 0;
//            DEBUG_PRINT("WAKEUP by Noise - go back to sleep\r\n");
//            
//            onOffState = OFF_SEKVENS_1;
//        }
//    }
//}
void wakeUp(void)
{
    if (appData.startupFlg || appData.wakeUpFlg)
        return;

    const uint32_t now = millis_32();

    // Arm noise-guard frste gang vi lander her i OFF-tilstand
    // (vi giver 0,5s til at f en gyldig tnd-rsag)
    if (!s_noiseArmed)
    {
        NoiseGuard_Arm();
    }

   // OFF: hvis vi er vkket og IR kan vre rsagen, s poll i et vindue
    if (!appData.powerOnFlg)
    {
        // Hvis IR-linjen er lav nu, eller du ved du kommer fra IR/IOC,
        // s prv at fange ON-koden via polling.
        if (!IR_RC5_Get())
        {
            const bool gotOn = PollIrForOn(IR_POLL_WINDOW_MS);

            if (gotOn)
            {
                //onOffState = ON_SEKVENS_AC_CHECK;
                DEBUG_PRINT("wakeup by IR (polled) starting on sequence\r\n");

                wakeUpTm = millis_32();
                appData.wakeUpFlg = 1;
                appData.wakeUpCnt = 0;
                //NoiseGuard_Disarm();
                Policy_OnPowerOn(PWR_EVT_IR);
                //return;
            }
            if(!appData.wakeUpFlg)
            {
            // Timeout: vi blev vkket af IR-aktivitet/noise men fik ikke gyldig ON
            DEBUG_PRINT("IR poll timeout %u ms -> back to sleep\r\n", IR_POLL_WINDOW_MS);
            onOffState = OFF_SEKVENS_1;
            return;
            }
        }
    }
    // ON/STBY-knap: tnd
    if ((ON_OFF_BUTTON_Get() && !appData.powerOnFlg && !appData.startupFlg)||appData.wakeUpFlg)
    {
        CORETIMER_DelayMs(20);
        if ((ON_OFF_BUTTON_Get() && !appData.powerOnFlg)||appData.wakeUpFlg)
        {
            onOffState = ON_SEKVENS_AC_CHECK;
            DEBUG_PRINT("wakeup by BUTTON starting on sequence\r\n");

            appData.wakeUpFlg = 1;
            Policy_OnPowerOn(PWR_EVT_BTN);

            NoiseGuard_Disarm();
            return;
        }
    }

    // 12V link: tnd (aktiv-lav) ? kun hvis ikke blokeret
    if (Link12V_IsActive() && !appData.powerOnFlg && !appData.startupFlg)
    {
        CORETIMER_DelayMs(20);
        if (Link12V_IsActive() && !pwrPolicy.link_blocked)
        {
            DEBUG_PRINT("wakeup by 12V\r\n");

            appData.wakeUpFlg = 1;
            onOffState = ON_SEKVENS_AC_CHECK;

            Policy_OnPowerOn(PWR_EVT_12V);

            NoiseGuard_Disarm();
            return;
        }
    }

    // Ingen gyldig rsag endnu:
    // Hvis 0,5s er get siden vi blev vkket -> tilbage i sleep
    if (NoiseGuard_Expired(now))
    {
        DEBUG_PRINT("WAKEUP noise timeout (%u ms) -> back to sleep\r\n", NOISE_GUARD_MS);

        NoiseGuard_Disarm();
        onOffState = OFF_SEKVENS_1;
    }
}


////////void wakeUp(void)
////////{
////////   // EVIC_ExternalInterruptDisable( EXTERNAL_INT_0 ); //Disable int0
////////     if (!IR_RC5_Get())
////////     {
////////        irReceive();
////////     }
////////     
////////     if(key == KeyOnOff && !appData.powerOnFlg)
////////        {
////////            onOffState = ON_SEKVENS_1; //Start On sequence
////////            DEBUG_PRINT("wakeup by IR starting on sequence\r\n");
////////            appData.wakeUpFlg = 1;
////////            key = 0;
////////        }
////////        
////////        //Receive IR
////////   
////////    if(ON_OFF_BUTTON_Get() && !appData.powerOnFlg)
////////    {
////////       CORETIMER_DelayMs (20); 
////////       if(ON_OFF_BUTTON_Get() && !appData.powerOnFlg)
////////       { 
////////          onOffState = ON_SEKVENS_1; //Start On sequence
////////          DEBUG_PRINT("wakeup starting on sequence\r\n");
////////          appData.wakeUpFlg = 1;
////////       }
////////       
////////    }
////////    if(!LINK_12V_Get() && !appData.powerOnFlg)
////////    {
////////      CORETIMER_DelayMs (20); 
////////      if(!LINK_12V_Get() && !appData.powerOnFlg)
////////       {
////////            DEBUG_PRINT("wakeup by 12V\r\n");
////////            onOffState = ON_SEKVENS_1; //Start On sequence
////////            DEBUG_PRINT("wakeup starting on sequence\r\n");
////////            appData.wakeUpFlg = 1;
////////       }
////////    }
////////    if(!appData.wakeUpFlg)
////////    {
////////        appData.wakeUpCnt++;
////////        DEBUG_PRINT("WAKEUPCNT %d\r\n",appData.wakeUpCnt);
////////        if(appData.wakeUpCnt > 0)
////////        {
////////           appData.wakeUpCnt = 0;
////////           DEBUG_PRINT("WAKEUP by Noise - go back to sleep\r\n");
////////           onOffState = OFF_SEKVENS_1;
//////////           CORETIMER_DelayMs (50); 
//////////           POWER_LowPowerModeEnter( LOW_POWER_DEEP_SLEEP_MODE);
//////////           
////////        }
////////    }
////////}




/***********************************************************************************************************************/

static void setOnOffSekvensTimer(uint32_t delay_ms, SYS_TIME_CALLBACK callback)
{
    if (onOffSekvensData.onOffSekvensTimer)
        SYS_TIME_TimerDestroy(onOffSekvensData.onOffSekvensTimer);

    onOffSekvensData.onOffSekvensTimer =
        SYS_TIME_CallbackRegisterMS(callback, 0, delay_ms, SYS_TIME_SINGLE);
}

void handleOnSekvens1(void)
{
     
    // (valgfrit) lille engangs-retry hvis frste lsning fejler
//    voltage_setting_t vs;
//    ee_vs_status_t st = EEPROM_TryLoadVoltageSetting(&vs);
//    if (st == EE_VS_ERR) {
//        CORETIMER_DelayMs(2);
//        st = EEPROM_TryLoadVoltageSetting(&vs);
//    }
//
//    if (st == EE_VS_OK) {
//        appData.voltageSetting = vs;
//    } else if (st == EE_VS_UNINIT) {
//        vs = VoltageSetting_Default();          // HIGH
//        appData.voltageSetting = vs;
//        (void)EEPROM_SaveVoltageSetting(vs);    // skriv KUN frste gang
//        DEBUG_PRINT("defaultVoltage skrevet i eeprom\r\n");
//    } else { // EE_VS_ERR
//        // Ingen skrivning ved fejl; kr med safe default i RAM
//        appData.voltageSetting = VoltageSetting_Default();
//        DEBUG_PRINT("EEPROM read error -> using default in RAM\r\n");
//    }
//
//    DEBUG_PRINT("VoltageSetting = %d \r\n", appData.voltageSetting);
//    
//    AC_CHECK();
//    
    
    setGreenBiasMode(GB_MODE_OFF);
    StUpTm = millis_32();
    DPS_RELAY_ON_OFF_Set();
    DEBUG_PRINT("DELAY MS: %u mS\r\n",StUpTm-wakeUpTm);
    TMR2_Start();
    DRV_TOUCH_PIN_RESET_Set();
    GLCD_DISP_ON_STBY_Set();
    appData.startupFlg = 1;
    if (onOffSekvensData.initBlinkTimer)
        SYS_TIME_TimerDestroy(onOffSekvensData.initBlinkTimer);

    onOffSekvensData.initBlinkTimer =
        SYS_TIME_CallbackRegisterMS(logoBlink_Callback, 0, 250, SYS_TIME_PERIODIC);

    setOnOffSekvensTimer(500, onSekvens1_Callback);

    
    onOffState = ON_OFF_SEKVENS_IDLE;
    DEBUG_PRINT("ON_SEKVENS_1\r\n");
    //SYS_TIME_TimerStart(SYS_TIME_INDEX_0);
}

void handleOnSekvens2(void)
{
    setOnOffSekvensTimer(500, onSekvens2_Callback);
    
    Legato_Initialize();
    onOffState = ON_OFF_SEKVENS_IDLE;
    DEBUG_PRINT("ON_SEKVENS_2\r\n");
}

void handleOnSekvens3(void)
{
    fadeBacklightIn();

    setOnOffSekvensTimer(1500, onSekvens3_Callback);

    SOFT_START_ON_OFF_Set();
    onOffState = ON_OFF_SEKVENS_IDLE;
    DEBUG_PRINT("ON_SEKVENS_3\r\n");
}

static void initOnSekvens4(void)
{
    //EVIC_ExternalInterruptDisable( EXTERNAL_INT_0 );
    //DEBUG_PRINT("INT 0 Disable\r\n");
    getEEPromValues();
    DEBUG_PRINT("Init ON_SEKVENS_4 Current Input = %d\r\n", appData.curInp);
    if (appData.curInp > 11)
        writeEEpromDefaultIfEmty();

    CORETIMER_DelayMs(50);
    getInpNamesFromEEProm();
    
    getEEPromValues();
    DEBUG_PRINT("PCMFILTER: %d", dacData.pcmFilter);
    appData.curLvl = appData.startLvl;
    
    
    IR_RC5_InterruptEnable(); 
    appData.wakeUpFlg = 0;

    CORETIMER_DelayMs(10);
    appData.powerOnFlg = 1;
    u20InitIoExp();
    u16InitIoExp();
    u26InitIoExp();
    
    U26_UpdateGreenBiasFromLevel();
}

void handleOnSekvens4(void)
{
    DEBUG_PRINT("ON_SEKVENS_4 fr eeprom\r\n");

    initOnSekvens4();
    
    APP_USB_CMD_OnPowerOnIncrement();
    setOnOffSekvensTimer(3000, onSekvens4_Callback);

    onOffState = ON_OFF_SEKVENS_IDLE;
    incBootCounterInEEProm(&s_bootValue);
    DEBUG_PRINT("Boot Count %u\r\n",(unsigned)s_bootValue);
    DEBUG_PRINT("ON_SEKVENS_4 Current Input = %d\r\n", appData.curInp);
}

static void initOnSekvens5(void)
{
    appData.errorCheckFlg = 1;
    uartClearBuffer();
    getAmpStatus();
    U26_showModulesInstalled();
    appData.maxInp = 5;
}

//static void handlePhonoConfiguration(void)
//{
//    if (appData.phonoRegiFlg)
//    {
//        appData.maxInp = 6;
//        if (appData.pickupSelection == movingCoil)
//            appData.u26Byte2 &= PICKUP_MC;
//        appData.u26Byte2 &= PHONO_REG_LED_ON;
//    }
//    else
//    {
//        appData.u26Byte2 |= PHONO_REG_LED_OFF;
//        if (appData.curInp == 6)
//            appData.curInp = 1;
//    }
//}
//
//static void handleDacConfiguration(void)
//{
//    if (appData.dacRegiFlg)
//    {
//        appData.maxInp = 11;
//        appData.u26Byte2 &= DAC_REG_LED_ON;
//        dacU26InitIoExp();
//        asyncOn();
//        CORETIMER_DelayMs(500);
//        dacSetup();
//        dirSetup();
//    }
//    else
//    {
//        appData.u26Byte2 |= DAC_REG_LED_OFF;
//        if (appData.curInp > 6)
//            appData.curInp = 1;
//    }
//}

static void validateCurrentInput(void)
{
   if ((appData.curInp == 0) || (appData.curInp > appData.maxInp))
        appData.curInp = 1;

    appData.oldInp = 0;
}

static void setupOnSekvens5Timer(void)
{
    const uint32_t PHONO_STARTUP_MS   = 23000u;
    const uint32_t DEFAULT_STARTUP_MS = 18000u;

    const bool isPhono = (appData.phonoRegiFlg != 0u) && (appData.curInp == 6);
    const uint32_t startupMs = isPhono ? PHONO_STARTUP_MS : DEFAULT_STARTUP_MS;

    (void)setOnOffSekvensTimer(startupMs, onSekvens5_Callback);
}


void handleOnSekvens5(void)
{
    initOnSekvens5();

    if (appData.phonoRegiFlg || appData.dacRegiFlg)
    {
        U26_ApplyPickupHwFromSelection();
        //handlePhonoConfiguration();
        handleDacConfiguration();
        //u26WriteOutputs(appData.u26Byte0, appData.u26Byte2);
    }

    validateCurrentInput();
    setupOnSekvens5Timer();

    onOffState = ON_OFF_SEKVENS_IDLE;
    DEBUG_PRINT("ON_SEKVENS_5\r\n");
}

void handleOnSekvens6(void)
{
    fadeBacklightOut();
    setBackLightIntensity(0);

    setOnOffSekvensTimer(1000, onSekvens6_Callback);

    onOffState = ON_OFF_SEKVENS_IDLE;
    DEBUG_PRINT("ON_SEKVENS_6\r\n");
}

void handleOnSekvens7(void)
{
    if (appData.enableSimpleViewFlg)
    {
        legato_showScreen(screenID_simpleViewScreen);
        if (appData.autoDispTimeOutHandle)
            SYS_TIME_TimerDestroy(appData.autoDispTimeOutHandle);

        appData.autoDispTimeOutHandle =
            SYS_TIME_CallbackRegisterMS(autoDispTimeOut_Callback, 0, DimOffTimeOut, SYS_TIME_SINGLE);
    }
    else
    {
        legato_showScreen(screenID_actionScreen);
    }


    if (onOffSekvensData.initBlinkTimer)
        SYS_TIME_TimerDestroy(onOffSekvensData.initBlinkTimer);

    GAD_LOGO_Set();
    appData.startupFlg = 0;
    outputMuteOff();
    setInput();
    setOnOffSekvensTimer(500, onSekvens7_Callback);
    printf("#0:01;\r\n");
    onOffState = ON_OFF_SEKVENS_IDLE;
}
void handleOnSekvens8(void)
{
     setDisplayIntensity();
     onOffState = ON_OFF_SEKVENS_IDLE;
}
static void shutdownAndCleanup(void)
{
    CloseAllHandles();
    muteOn();
    outputMuteOn();
    saveCurrentInput();
    saveDigitalSetup();
    //saveDisplaySettings();

    appData.errorCheckFlg = 0;
    setBackLightIntensity(0);
    CORETIMER_DelayMs(5);
    SOFT_START_ON_OFF_Clear();
    DPS_RELAY_ON_OFF_Clear();
    DRV_TOUCH_PIN_RESET_Clear();
    GLCD_DISP_ON_STBY_Clear();
    ONSTBY_LED_Clear();
    GAD_LOGO_Clear();

    cleanUp();
    CORETIMER_DelayMs(700);
    appData.menuFlg = 0;
    appData.powerOnFlg = 0;
    appData.startupFlg = 0;
    if (onOffSekvensData.onOffSekvensTimer)
       SYS_TIME_TimerDestroy(onOffSekvensData.onOffSekvensTimer);

}

void handleOffSekvens1(void)
{
    shutdownAndCleanup();

    printf("#0:00;\r\n");
    APP_USB_CMD_OnPowerOffClear();

    CORETIMER_DelayMs(50);

    // Ryd pending wake flags før vi går i low-power
    IR_RC5_InterruptDisable();
    EVIC_SourceStatusClear(EXTERNAL_INT_0);       // INT0 (AND-gate udgang)

    if(appData.state == APP_LEFT_AC_ERROR)
    {
        onOffState = ON_OFF_SEKVENS_IDLE;
        DEBUG_PRINT("left ac error  - onOffState = idle\r\n");
        return;
    }

    DEBUG_PRINT("pwrPolicy.link_blocked: %s\n", pwrPolicy.link_blocked ? "true" : "false");

    // Hvis vi er slukket manuelt mens 12V-link stadig er aktiv:
    // - INT0 (AND-gate) giver ingen flanke -> deep sleep kan ikke vækkes manuelt
    // - Vi går derfor i en mindre dyb mode, så CN/IOC (knap/IR) kan vække.
    if (pwrPolicy.link_blocked && Link12V_IsActive())
    {
        // Undgå at INT0 holder os vågne / giver højere forbrug i denne mode
        //EVIC_ExternalInterruptDisable(EXTERNAL_INT_0);
        //EVIC_SourceStatusClear(EXTERNAL_INT_0);
        EVIC_ExternalInterruptEnable(EXTERNAL_INT_0);
        // Klargør CN wake for ON/STBY + IR
        EVIC_SourceStatusClear(INT_SOURCE_CHANGE_NOTICE_H); // IR på RH11 (CN port H)
        EVIC_SourceStatusClear(INT_SOURCE_CHANGE_NOTICE_J); // ON/STBY på RJ15 (CN port J)
        ON_OFF_BUTTON_InterruptEnable();
        IR_RC5_InterruptEnable();

        DEBUG_PRINT("OFF_LINK_HOLD: om 50ms LOW POWER IDLE (CN wake)\r\n");
        CORETIMER_DelayMs(50);

        POWER_LowPowerModeEnter(LOW_POWER_IDLE_MODE);
    }
    else
    {
        // Normal dyb sleep (lavt forbrug) - wake via INT0 (AND-gate udgang)
        EVIC_ExternalInterruptEnable(EXTERNAL_INT_0);
        DEBUG_PRINT("INT 0 Enable\r\n");

        DEBUG_PRINT("OFF_NORMAL: om 50ms DEEP SLEEP MODE\r\n");
        CORETIMER_DelayMs(50);

        POWER_LowPowerModeEnter(LOW_POWER_DEEP_SLEEP_MODE);
    }

    // Hvis vi returnerer herfra, er vi vågnet af en IRQ.
    // Overstyr IKKE en allerede-requestet ON-sekvens fra IRQ handler.
    if (onOffState == OFF_SEKVENS_1)
    {
        onOffState = ON_OFF_SEKVENS_IDLE;
    }
}



void onOffSekvens(void)
{
    switch (onOffState)
{
        case ON_SEKVENS_AC_CHECK:
        {
            
            static bool acchkStarted = false;
            GAD_LOGO_Set();
            
            if (!acchkStarted) {
                // Hent forventet setting (kun ls; skriv default frste gang gr din handleOnSekvens1 allerede)
                voltage_setting_t vs;
                if (!EEPROM_LoadVoltageSetting(&vs)) {
                    vs = VoltageSetting_Default(); // fallback, hvis EE endnu ikke sat
                }
                appData.voltageSetting = vs;

                // Start ikke-blokerende AC-check mod den forventede vrdi
                ACCHK_Begin(appData.voltageSetting);
                acchkStarted = true;
                DEBUG_PRINT("AC_CHECK: started (expected=%d)\r\n", appData.voltageSetting);
            }

            // Pump state-maskinen t tik
            ACCHK_Tasks();

            // Nr frdig, beslutter vi nste state
            if (ACCHK_Done()) {
                acchkStarted = false;

                if (ACCHK_Passed()) {
                    // OK ? fortst prcis som fr: din originale handleOnSekvens1 krer hele sekvensen
                    
                    ONSTBY_LED_Set();
                    GAD_LOGO_Set();
                    onOffState = ON_SEKVENS_1;
                } else {
                    // Mismatch ? ACCHK har vist fejl-UI, blinker LED og poller spndingen.
                    // Vi gr i IDLE og lader ACCHK resette, nr spndingen matcher.
                    DEBUG_PRINT("AC_CHECK: mismatch -> stay IDLE\r\n");
                    onOffState = ON_OFF_SEKVENS_IDLE;
                    ONSTBY_LED_Clear();
                    GAD_LOGO_Set();
                }
            }
        }
        break;
        case ON_SEKVENS_1: handleOnSekvens1(); break;
        case ON_SEKVENS_2: handleOnSekvens2(); break;
        case ON_SEKVENS_3: handleOnSekvens3(); break;
        case ON_SEKVENS_4: handleOnSekvens4(); break;
        case ON_SEKVENS_5: handleOnSekvens5(); break;
        case ON_SEKVENS_6: handleOnSekvens6(); break;
        case ON_SEKVENS_7: handleOnSekvens7(); break;
        case ON_SEKVENS_8: handleOnSekvens8(); break;
        case OFF_SEKVENS_1: handleOffSekvens1(); break;
        case ON_OFF_SEKVENS_IDLE: break;
    }
}

#define LEFT_PS_POLL_MS        10u
#define LEFT_PS_FAIL_SAMPLES   5u   // 50ms

static SYS_TIME_HANDLE s_leftPsPollTmr = SYS_TIME_HANDLE_INVALID;
static volatile bool   s_leftPsPollFlg = false;

static void LeftPsPollCb(uintptr_t ctx)
{
    (void)ctx;
    s_leftPsPollFlg = true;
}

void checkForLeftPSFallOut(void)
{
    static uint8_t failCnt = 0;
    static bool OffSeqDoneFlg = false; 
    /* start poll timer n gang */
    if (s_leftPsPollTmr == SYS_TIME_HANDLE_INVALID)
    {
        s_leftPsPollTmr = SYS_TIME_CallbackRegisterMS(LeftPsPollCb, 0, LEFT_PS_POLL_MS, SYS_TIME_PERIODIC);

        /* fallback hvis timer fejler */
        if (s_leftPsPollTmr == SYS_TIME_HANDLE_INVALID)
        {
            s_leftPsPollFlg = true;
        }
    }

    if (!s_leftPsPollFlg)
        return;

    s_leftPsPollFlg = false;

    if (AC_RESET_Get())
    {
        failCnt = 0;
        return;
    }

    if (failCnt < 255) failCnt++;

    if (failCnt >= LEFT_PS_FAIL_SAMPLES)
    {
        /* gte udfald -> error state + pn nedlukning */
        
        if(!OffSeqDoneFlg && onOffState != ON_SEKVENS_AC_CHECK)
        {
          //appData.state = APP_LEFT_AC_ERROR;
          onOffState = OFF_SEKVENS_1;
          OffSeqDoneFlg = true;
        }

        failCnt = LEFT_PS_FAIL_SAMPLES; // latch
    }
}


//void checkForLeftPSFallOut(void)
//{
//    if(AC_RESET_Get())
//        return;
//    else
//    {
//      CORETIMER_DelayMs(50);
//      if(AC_RESET_Get())
//          return;
//      else
//      {
//          onOffState = OFF_SEKVENS_1;
//      }
//    }
//}