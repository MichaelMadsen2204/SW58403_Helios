// ac_check.c
#include "ac_check.h"
#include "definitions.h"
#include "app.h"
#include "user.h"
#include <stdint.h>   // for uintptr_t


/* Makroer fra din eksisterende kode */
#ifndef ONSTBY_LED_Toggle
#error "ONSTBY_LED_Toggle() mangler makro"
#endif

#ifndef SP_RELAY_Set
#error "SP_RELAY_Set() mangler makro"
#endif
#ifndef SP_RELAY_Clear
#error "SP_RELAY_Clear() mangler makro"
#endif

typedef struct {
    acchk_state_t st;
    voltage_setting_t expected;
    voltage_setting_t actual;
    SYS_TIME_HANDLE t50; // one-shot 50ms
    SYS_TIME_HANDLE tBlink; // 1000ms blink
    SYS_TIME_HANDLE tPoll; // 200ms re-check
    volatile bool f50; // flag fra timer ISR
    volatile bool fBlink;
    volatile bool fPoll;
    volatile bool errorIndicated;
    volatile int cnt;
} acchk_ctx_t;

static acchk_ctx_t s_acchk;

static void cb_50(uintptr_t ctx) {
    (void) ctx;
    s_acchk.f50 = true;
}

static void cb_blink(uintptr_t ctx) {
    (void) ctx;
    s_acchk.fBlink = true;
}

static void cb_poll(uintptr_t ctx) {
    (void) ctx;
    s_acchk.fPoll = true;
}

void ACCHK_Init(void) {
    s_acchk.st = ACCHK_IDLE;
    s_acchk.expected = VoltageHigh;
    s_acchk.actual = VoltageHigh;
    s_acchk.cnt = 0;
    s_acchk.t50 = s_acchk.tBlink = s_acchk.tPoll = SYS_TIME_HANDLE_INVALID;
    s_acchk.f50 = s_acchk.fBlink = s_acchk.fPoll = false;
    s_acchk.errorIndicated = false;
}

void ACCHK_Abort(void) {
    if (s_acchk.t50 != SYS_TIME_HANDLE_INVALID) SYS_TIME_TimerDestroy(s_acchk.t50);
    if (s_acchk.tBlink != SYS_TIME_HANDLE_INVALID) SYS_TIME_TimerDestroy(s_acchk.tBlink);
    if (s_acchk.tPoll != SYS_TIME_HANDLE_INVALID) SYS_TIME_TimerDestroy(s_acchk.tPoll);
    s_acchk.t50 = s_acchk.tBlink = s_acchk.tPoll = SYS_TIME_HANDLE_INVALID;
    s_acchk.f50 = s_acchk.fBlink = s_acchk.fPoll = false;
    s_acchk.errorIndicated = false;
    s_acchk.st = ACCHK_IDLE;
}

void ACCHK_Begin(voltage_setting_t expected) {
    ACCHK_Abort(); // ryd alt

    s_acchk.expected = expected;
    s_acchk.errorIndicated = false;
    s_acchk.cnt = 0;
    /* lille stabilisering: 50ms ? samme idé som dine delays, men ikke-blokerende */
    //    s_acchk.t50 = SYS_TIME_CallbackRegisterMS(cb_50, 0, 20, SYS_TIME_SINGLE);

    s_acchk.st = ACCHK_WAIT_50MS;
}

static void set_relay_for(voltage_setting_t v) {
    if (v == VoltageLow) SP_RELAY_Set();
    else SP_RELAY_Clear();
}

void ACCHK_Tasks(void) {
    switch (s_acchk.st) {
        case ACCHK_IDLE:
            break;

        case ACCHK_WAIT_50MS:
            s_acchk.cnt++;
            CORETIMER_DelayUs(100);

            if (ACCHK_50mS_Passed()) {
                //                if (s_acchk.t50 != SYS_TIME_HANDLE_INVALID) {
                //                    SYS_TIME_TimerDestroy(s_acchk.t50);
                //                    s_acchk.t50 = SYS_TIME_HANDLE_INVALID;
                s_acchk.st = ACCHK_EVAL;
            }
            break;

        case ACCHK_EVAL:
            s_acchk.actual = AC_ReadActualFromPins();

            if (s_acchk.actual == s_acchk.expected && AC_RESET_Get()) {
                /* OK ? sæt relæ korrekt og færdig */
                set_relay_for(s_acchk.expected);
                s_acchk.st = ACCHK_DONE_OK;
                DEBUG_PRINT("ACCHK_DONE_OK\r\n\n");
            } else {
                if (s_acchk.actual == 2)
                    DEBUG_PRINT("AC Check found left missing\r\n\n");
                /* Mismatch ? vis fejlskærm + start blink + periodisk re-check */
                UI_ShowVoltageError(s_acchk.expected, s_acchk.actual);

                s_acchk.tBlink = SYS_TIME_CallbackRegisterMS(cb_blink, 0, 1000, SYS_TIME_PERIODIC);
                s_acchk.tPoll = SYS_TIME_CallbackRegisterMS(cb_poll, 0, 200, SYS_TIME_PERIODIC);
                s_acchk.st = ACCHK_MISMATCH;
            }
            break;

        case ACCHK_MISMATCH:
            if (s_acchk.fBlink) {
                s_acchk.fBlink = false;
                ONSTBY_LED_Toggle();
            }
            if (!s_acchk.errorIndicated) {

                TMR2_Start();
                DRV_TOUCH_PIN_RESET_Set();
                GLCD_DISP_ON_STBY_Set();
                appData.acErrorFlg = true;
                setBackLightIntensity(100);
                if (!AC_RESET_Get()) {
                    DEBUG_PRINT("screenID_leftPowerMissingScreen\r\n\n");
                    legato_showScreen(screenID_leftPowerMissingScreen);
                } else {
                    DEBUG_PRINT("screenID_wrongAcVoltageScreen\r\n\n");
                    legato_showScreen(screenID_wrongAcVoltageScreen);
                }
                s_acchk.errorIndicated = true;
            }

            if (s_acchk.fPoll) {
                s_acchk.fPoll = false;

                /* bootloader-trigger som i din gamle while(1) */
                if (appData.state == APP_ACTIVATE_BOOTLOADER) {
                    APP_TriggerBootloader();
                }

                /* Tjek om spændingen nu matcher ? så resetter vi for clean startup */
                s_acchk.actual = AC_ReadActualFromPins();
                if (s_acchk.actual == s_acchk.expected) {
                    /* Stop timers før reset */
                    if (s_acchk.tBlink != SYS_TIME_HANDLE_INVALID) {
                        SYS_TIME_TimerDestroy(s_acchk.tBlink);
                        s_acchk.tBlink = SYS_TIME_HANDLE_INVALID;
                    }
                    if (s_acchk.tPoll != SYS_TIME_HANDLE_INVALID) {
                        SYS_TIME_TimerDestroy(s_acchk.tPoll);
                        s_acchk.tPoll = SYS_TIME_HANDLE_INVALID;
                    }
                    /* Relæ skal stå til forventet ved næste boot ? vi resetter nu */
                    setBackLightIntensity(0);
                    appData.acErrorFlg = false;
                    APP_SystemReset();
                }
            }
            break;

        case ACCHK_DONE_OK:
        default:
            break;
    }
}

/* status helpers */
bool ACCHK_IsBusy(void) {
    return (s_acchk.st != ACCHK_IDLE) && (s_acchk.st != ACCHK_DONE_OK);
}

bool ACCHK_Done(void) {
    return (s_acchk.st == ACCHK_DONE_OK);
}

bool ACCHK_Passed(void) {
    return (s_acchk.st == ACCHK_DONE_OK);
}

bool ACCHK_50mS_Passed(void) {
    return (s_acchk.cnt >= 10);
}

voltage_setting_t ACCHK_GetExpected(void) {
    return s_acchk.expected;
}

voltage_setting_t ACCHK_GetActual(void) {
    return s_acchk.actual;
}
