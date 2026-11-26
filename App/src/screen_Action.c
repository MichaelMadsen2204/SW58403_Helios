#include "definitions.h" // indeholder app.h, system headers, legato types mm.
#include "gfx/legato/generated/screen/le_gen_screen_actionScreen.h" // for actionScreen_dispOnButton
#include "ui_globals.h"
#include "app.h"
#include "gfx/legato/generated/le_gen_harmony.h"

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>


// --- Touch-hold volume repeat (safe) additions ---
#include "system/time/sys_time.h"
#include "system/input/sys_input.h"
#include "gfx/legato/common/legato_rect.h"

/* ============================================================================
 *  Volume hold/repeat (safe)
 *  - UI opdateres kun i UI-kontekst (ActionScreen_VolumeUiPump).
 *  - Callbacks ændrer kun flag/values.
 *  - Stopper på: touch-up, out-of-rect, stale touch, eller touch error.
 * ==========================================================================*/

typedef enum {
    VOL_DIR_NONE = 0,
    VOL_DIR_UP,
    VOL_DIR_DOWN
} vol_dir_t;

#define VOL_INIT_DELAY_MS   400u
#define VOL_REPEAT_MS       120u
#define VOL_FAILSAFE_TICKS  84u     // max repeats before force stop
#define TOUCH_STALE_MS      250u    // stop if no touch updates within this time

static SYS_TIME_HANDLE s_volInitialHandle = SYS_TIME_HANDLE_INVALID;
static SYS_TIME_HANDLE s_volRepeatHandle = SYS_TIME_HANDLE_INVALID;

static volatile bool s_volUiDirty = false;
volatile bool g_digiInfoDirty = false;


static leButtonWidget* s_activeBtn = NULL; // last pressed vol button
static volatile bool s_forceVisualRelease = false; // request to "unpress" in UI context

static vol_dir_t s_volDir = VOL_DIR_NONE;
static uint32_t s_volRepeatTicks = 0;

static volatile bool s_touchIsDown = false;
static volatile int16_t s_touchX = -1, s_touchY = -1;
static volatile uint32_t s_lastTouchMs = 0;

static leRect s_captureRect; // active while holding a vol button
static int16_t s_rectPad = 12; // pixels margin

static bool s_inpActive = false; // true if global touch events are being fed
static volatile bool s_lastInRect = false;
static volatile bool s_touchErrorAbort = false;

volatile bool digiCacheInvalid = true;


/* Debug */
#define TD_ENABLE  1
#if TD_ENABLE
#define TD_PRINTF(...)   DEBUG_PRINT(__VA_ARGS__)
#else
#define TD_PRINTF(...)   ((void)0)
#endif

static inline uint32_t millis(void) {
    const uint32_t f = (uint32_t) SYS_TIME_FrequencyGet();
    if (f == 0u) return 0u;

    const uint64_t c = (uint64_t) SYS_TIME_CounterGet();
    return (uint32_t) ((c * 1000u) / (uint64_t) f);
}

static inline uint16_t millis16_raw(void) {
    // Hvis din SYS_TIME allerede kører i 1ms ticks og CounterGet() er tick-count:
    // return (uint16_t)SYS_TIME_CounterGet();
    //
    // Hvis du SKAL bruge din eksisterende millis()-beregning, så kan du tage low16 af den:
    return (uint16_t) millis(); // bruger din nuværende millis(), men antager den wrap'er ved ~65s
}

uint32_t millis32(void) {
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
// Safe elapsed (wrap-safe hvis tiden bare kører modulo 2^32)

static inline uint32_t ms_since_u32(uint32_t now, uint32_t then) {
    return (uint32_t) (now - then);
}

// Wrap-safe "now reached target?"

static inline bool ms_reached_u32(uint32_t now, uint32_t target) {
    return ((int32_t) (now - target) >= 0);
}

static inline bool PointInRect(int16_t x, int16_t y, const leRect* rc) {
    return (x >= rc->x) && (y >= rc->y) &&
            (x < (rc->x + rc->width)) &&
            (y < (rc->y + rc->height));
}

static inline void CloseHandleLocal(SYS_TIME_HANDLE *h) {
    if (h && *h != SYS_TIME_HANDLE_INVALID) {
        (void) SYS_TIME_TimerDestroy(*h);
        *h = SYS_TIME_HANDLE_INVALID;
    }
}

static void StopVolumeRepeat(void);

static inline void dbg_touch(const char* tag) {
    TD_PRINTF("[touch] %s: down=%d x=%d y=%d in=%d act=%d dir=%d lvl=%u/%u\r\n",
            tag,
            (int) s_touchIsDown, (int) s_touchX, (int) s_touchY,
            (int) s_lastInRect, (int) s_inpActive,
            (int) s_volDir, (unsigned) appData.curLvl, (unsigned) appData.maxLvl);
}

/* --- Touch hooks (call from Legato touch handlers / widget events) --- */

void ActionTouch_OnError(void) {
    // Må gerne kaldes fra driver/ISR-kontekst: kun flag
    s_touchErrorAbort = true;
}

void ActionTouch_OnDown(int16_t x, int16_t y) {
    s_lastTouchMs = millis();
    s_touchIsDown = true;
    s_touchX = x;
    s_touchY = y;

    s_lastInRect = PointInRect(s_touchX, s_touchY, &s_captureRect);
    s_inpActive = true;

    dbg_touch("down");
}

void ActionTouch_OnMove(int16_t x, int16_t y) {
    s_lastTouchMs = millis();
    s_touchX = x;
    s_touchY = y;
    s_lastInRect = PointInRect(s_touchX, s_touchY, &s_captureRect);

    dbg_touch("move");
}

void ActionTouch_OnUp(int16_t x, int16_t y) {
    s_lastTouchMs = millis();
    s_touchIsDown = false;
    s_touchX = x;
    s_touchY = y;
    s_lastInRect = PointInRect(s_touchX, s_touchY, &s_captureRect);

    StopVolumeRepeat();
    s_forceVisualRelease = true;
    s_volUiDirty = true;

    dbg_touch("up");
}

static void SetCaptureRect(const leWidget* w) {
    leRect r;
    ((leWidget*) w)->fn->rectToScreen((leWidget*) w, &r);

    s_captureRect.x = r.x - s_rectPad;
    s_captureRect.y = r.y - s_rectPad;
    s_captureRect.width = r.width + (2 * s_rectPad);
    s_captureRect.height = r.height + (2 * s_rectPad);
}

static void StopVolumeRepeat(void) {
    s_volDir = VOL_DIR_NONE;
    s_volRepeatTicks = 0U;

    CloseHandleLocal(&s_volInitialHandle);
    CloseHandleLocal(&s_volRepeatHandle);
}

static void VolumeStepOnce_Core(vol_dir_t dir) {
    if (appData.inputMuteActiveFlg)
        return;

    const uint8_t prev = appData.curLvl;
    const bool wasMuted = (appData.muteFlg != 0);

    if (dir == VOL_DIR_UP) {
        if (prev < appData.maxLvl) {
            appData.curLvl = (uint8_t) (prev + 1u);

            const bool leavingZero = (prev == 0u);
            const bool needUnmute = wasMuted || leavingZero;

            appData.skipUnmuteFlg = needUnmute ? 0u : 1u;
        }
    } else if (dir == VOL_DIR_DOWN) {
        if (prev > 0u) {
            appData.curLvl = (uint8_t) (prev - 1u);
            appData.skipUnmuteFlg = 1u;
        }
    }
}

static void HardStopRepeat_AndRelease(void) {
    StopVolumeRepeat();
    s_forceVisualRelease = true;
    s_volUiDirty = true;

    s_inpActive = false;
    s_touchIsDown = false;
}

static void VolRepeat_Callback(uintptr_t ctx) {
    (void) ctx;

    if (s_volDir == VOL_DIR_NONE) {
        StopVolumeRepeat();
        return;
    }

    if (s_inpActive) {
        const uint32_t now = millis();
        if ((uint32_t) (now - s_lastTouchMs) > TOUCH_STALE_MS) {
            HardStopRepeat_AndRelease();
            return;
        }

        if (!s_touchIsDown || !PointInRect(s_touchX, s_touchY, &s_captureRect)) {
            HardStopRepeat_AndRelease();
            return;
        }
    }

    VolumeStepOnce_Core(s_volDir);
    s_volUiDirty = true;

    if (appData.curLvl == 0u || appData.curLvl >= appData.maxLvl) {
        StopVolumeRepeat();
        return;
    }

    if (++s_volRepeatTicks >= VOL_FAILSAFE_TICKS) {
        StopVolumeRepeat();
        return;
    }
}

static void VolInitialDelay_Callback(uintptr_t ctx) {
    (void) ctx;

    CloseHandleLocal(&s_volInitialHandle);

    s_volRepeatHandle = SYS_TIME_CallbackRegisterMS(VolRepeat_Callback, 0, VOL_REPEAT_MS, SYS_TIME_PERIODIC);
    if (s_volRepeatHandle == SYS_TIME_HANDLE_INVALID)
        StopVolumeRepeat();
}

static void StartVolumeRepeat(vol_dir_t dir) {
    StopVolumeRepeat(); // clean start

    s_lastInRect = PointInRect(s_touchX, s_touchY, &s_captureRect);
    dbg_touch("start");

    VolumeStepOnce_Core(dir);
    s_volUiDirty = true;

    if (appData.curLvl == 0u || appData.curLvl >= appData.maxLvl) {
        StopVolumeRepeat();
        return;
    }

    s_volDir = dir;
    s_volInitialHandle = SYS_TIME_CallbackRegisterMS(VolInitialDelay_Callback, 0, VOL_INIT_DELAY_MS, SYS_TIME_SINGLE);
    if (s_volInitialHandle == SYS_TIME_HANDLE_INVALID)
        StopVolumeRepeat();
}

/* ============================================================================
 *  Screen timers
 * ==========================================================================*/

void setActionViewTimeOut(void) {
    if (appData.actionViewTimeOutHandle != SYS_TIME_HANDLE_INVALID)
        (void)SYS_TIME_TimerDestroy(appData.actionViewTimeOutHandle);

    appData.actionViewTimeOutHandle =
            SYS_TIME_CallbackRegisterMS(actionViewTimeOut_Callback, 0, ActionViewTimeOut, SYS_TIME_SINGLE);
}

void setDispDimTimeOut(void) {
    if (appData.autoDispTimeOutHandle != SYS_TIME_HANDLE_INVALID)
        (void)SYS_TIME_TimerDestroy(appData.autoDispTimeOutHandle);

    appData.autoDispTimeOutHandle =
            SYS_TIME_CallbackRegisterMS(autoDispTimeOut_Callback, 0, DimOffTimeOut, SYS_TIME_SINGLE);
}

void screenSwapTimeOut_Callback(uintptr_t context) {
    (void) context;
    appData.screenSwapDelayExpired = 1;
}

void lockedButNoFs_Callback(uintptr_t context) {
    (void) context;
    dacData.lockedButNoSignalTimeOutExpired = 1;
    appData.irInputChangeFlg = 1;
}

void actionViewTimeOut_Callback(uintptr_t context) {
    (void) context;

    if(appData.menuFlg)
        return;

    if (appData.enableSimpleViewFlg)
        legato_showScreen(screenID_simpleViewScreen);
}

void autoDispTimeOut_Callback(uintptr_t context)
{
    (void)context;
    if(appData.menuFlg)
        return;
    
    if ((appData.dispMode & 0x7Fu) == modeDim)
    {
        setBackLightIntensity(15);
        //appData.dispSleepActiveFlg = 1;   // <-- VIGTIG: dim tæller også som ?sleep?

        if (legato_getCurrentScreen() == screenID_actionScreen)
        {
            actionScreen_dispOnButton->fn->setEnabled(actionScreen_dispOnButton, LE_TRUE);
            actionScreen_dispOnButton->fn->setVisible(actionScreen_dispOnButton, LE_TRUE);
        }
    }
    else if ((appData.dispMode & 0x7Fu) == modeOff)
    {
        setBackLightIntensity(0);
        appData.dispSleepActiveFlg = 1;

        if (legato_getCurrentScreen() == screenID_actionScreen)
        {
            actionScreen_dispOnButton->fn->setEnabled(actionScreen_dispOnButton, LE_TRUE);
            actionScreen_dispOnButton->fn->setVisible(actionScreen_dispOnButton, LE_TRUE);
        }
    }

    if (appData.autoDispTimeOutHandle != SYS_TIME_HANDLE_INVALID)
        (void)SYS_TIME_TimerDestroy(appData.autoDispTimeOutHandle);

    appData.autoDispTimeOutHandle = SYS_TIME_HANDLE_INVALID;
}

/* ============================================================================
 *  Input UI helpers
 * ==========================================================================*/

void hideDigiInfoPanel(void) {
    if (actionScreen_digInfoPanel->fn->getVisible(actionScreen_digInfoPanel))
        actionScreen_digInfoPanel->fn->setVisible(actionScreen_digInfoPanel, LE_FALSE);
}

void showDigiInfoPanel(void) {
    if (!actionScreen_digInfoPanel->fn->getVisible(actionScreen_digInfoPanel))
        actionScreen_digInfoPanel->fn->setVisible(actionScreen_digInfoPanel, LE_TRUE);

    updateDigiInfoPanel();
}

void setActiveInput(void) {
    switch (appData.curInp) {
        case 1:
            actionScreen_anaInp1But->fn->setEnabled(actionScreen_anaInp1But, LE_FALSE);
            actionScreen_anaInp1But->fn->setReleasedImage(actionScreen_anaInp1But, (leImage*) & smallSelected2);
            hideDigiInfoPanel();
            break;
        case 2:
            actionScreen_anaInp2But->fn->setEnabled(actionScreen_anaInp2But, LE_FALSE);
            actionScreen_anaInp2But->fn->setReleasedImage(actionScreen_anaInp2But, (leImage*) & smallSelected2);
            hideDigiInfoPanel();
            break;
        case 3:
            actionScreen_anaInp3But->fn->setEnabled(actionScreen_anaInp3But, LE_FALSE);
            actionScreen_anaInp3But->fn->setReleasedImage(actionScreen_anaInp3But, (leImage*) & smallSelected2);
            hideDigiInfoPanel();
            break;
        case 4:
            actionScreen_anaInp4But->fn->setEnabled(actionScreen_anaInp4But, LE_FALSE);
            actionScreen_anaInp4But->fn->setReleasedImage(actionScreen_anaInp4But, (leImage*) & smallSelected2);
            hideDigiInfoPanel();
            break;
        case 5:
            actionScreen_anaInp5But->fn->setEnabled(actionScreen_anaInp5But, LE_FALSE);
            actionScreen_anaInp5But->fn->setReleasedImage(actionScreen_anaInp5But, (leImage*) & smallSelected2);
            hideDigiInfoPanel();
            break;
        case 6:
            actionScreen_anaInp6But->fn->setEnabled(actionScreen_anaInp6But, LE_FALSE);
            actionScreen_anaInp6But->fn->setReleasedImage(actionScreen_anaInp6But, (leImage*) & smallSelected2);
            hideDigiInfoPanel();
            break;
        case 7:
            actionScreen_digiInp7But->fn->setEnabled(actionScreen_digiInp7But, LE_FALSE);
            actionScreen_digiInp7But->fn->setReleasedImage(actionScreen_digiInp7But, (leImage*) & smallSelected2);
            showDigiInfoPanel();
            break;
        case 8:
            actionScreen_digiInp8But->fn->setEnabled(actionScreen_digiInp8But, LE_FALSE);
            actionScreen_digiInp8But->fn->setReleasedImage(actionScreen_digiInp8But, (leImage*) & smallSelected2);
            showDigiInfoPanel();
            break;
        case 9:
            actionScreen_digiInp9But->fn->setEnabled(actionScreen_digiInp9But, LE_FALSE);
            actionScreen_digiInp9But->fn->setReleasedImage(actionScreen_digiInp9But, (leImage*) & smallSelected2);
            showDigiInfoPanel();
            break;
        case 10:
            actionScreen_digiInp10But->fn->setEnabled(actionScreen_digiInp10But, LE_FALSE);
            actionScreen_digiInp10But->fn->setReleasedImage(actionScreen_digiInp10But, (leImage*) & smallSelected2);
            showDigiInfoPanel();
            break;
        case 11:
            actionScreen_digiInp11But->fn->setEnabled(actionScreen_digiInp11But, LE_FALSE);
            actionScreen_digiInp11But->fn->setReleasedImage(actionScreen_digiInp11But, (leImage*) & smallSelected2);
            showDigiInfoPanel();
            break;
        default:
            break;
    }
}

void clrSelectedInput(void) {
    leButtonWidget * buttons[] = {
        actionScreen_anaInp1But,
        actionScreen_anaInp2But,
        actionScreen_anaInp3But,
        actionScreen_anaInp4But,
        actionScreen_anaInp5But,
        actionScreen_anaInp6But,
        actionScreen_digiInp7But,
        actionScreen_digiInp8But,
        actionScreen_digiInp9But,
        actionScreen_digiInp10But,
        actionScreen_digiInp11But
    };

    const int n = (int) (sizeof (buttons) / sizeof (buttons[0]));
    for (int i = 0; i < n; i++) {
        leButtonWidget* b = buttons[i];
        b->fn->setPressed(b, LE_FALSE);
        b->fn->setEnabled(b, LE_TRUE);
        b->fn->setReleasedImage(b, (leImage*) & smallNotSelected3);
    }
}

void showValidInputs(void) {
    appData.maxInp = 5;

    if (appData.phonoRegiFlg) {
        actionScreen_anaInp6But->fn->setVisible(actionScreen_anaInp6But, LE_TRUE);
        appData.maxInp = 6;
    }

    if (appData.dacRegiFlg) {
        actionScreen_actAnaDigiSelectionBut->fn->setVisible(actionScreen_actAnaDigiSelectionBut, LE_TRUE);
        appData.maxInp = 11;

        if (appData.curInp > 6) {
            actionScreen_actAnaDigiSelectionBut->fn->setPressed(actionScreen_actAnaDigiSelectionBut, LE_TRUE);
            actionScreen_digInfoPanel->fn->setVisible(actionScreen_digInfoPanel, LE_TRUE);

            actionScreen_digiInpNamePanel->fn->setEnabled(actionScreen_digiInpNamePanel, LE_TRUE);
            actionScreen_digiInpNamePanel->fn->setVisible(actionScreen_digiInpNamePanel, LE_TRUE);

            actionScreen_anaInpNamePanel->fn->setEnabled(actionScreen_anaInpNamePanel, LE_FALSE);
            actionScreen_anaInpNamePanel->fn->setVisible(actionScreen_anaInpNamePanel, LE_FALSE);

            actionScreen_padLockImg->fn->setPressed(actionScreen_padLockImg, dacData.signalLockFlg ? LE_TRUE : LE_FALSE);

            if (appData.curInp == 7) {
                actionScreen_batteryPanel->fn->setVisible(actionScreen_batteryPanel, LE_TRUE);
                actionScreen_BattCharged->fn->setVisible(actionScreen_BattCharged, LE_TRUE);
                actionScreen_BattCharging->fn->setVisible(actionScreen_BattCharging, dacData.usbCharging ? LE_TRUE : LE_FALSE);
            } else {
                actionScreen_batteryPanel->fn->setVisible(actionScreen_batteryPanel, LE_FALSE);
            }
        }
    } else {
        actionScreen_actAnaDigiSelectionBut->fn->setVisible(actionScreen_actAnaDigiSelectionBut, LE_FALSE);
    }
}

/* ============================================================================
 *  Action screen events
 * ==========================================================================*/

void event_actionScreen_dispOnButton_OnPressed(leButtonWidget* btn) {
    (void) btn;

    actionScreen_dispOnButton->fn->setEnabled(actionScreen_dispOnButton, LE_FALSE);
    actionScreen_dispOnButton->fn->setVisible(actionScreen_dispOnButton, LE_FALSE);
    //printf("dispOnButton\n");
    setActionViewTimeOut();
    setDispDimTimeOut();
    setDisplayIntensity();
}

void event_actionScreen_actMuteBut_OnPressed(leButtonWidget* btn) {
    (void) btn;

    if (!ignoreEvent) {
        if (appData.curLvl > 0 || AvSelected(appData.avInp, appData.curInp))
            toggleMute();

        if (appData.muteFlg)
            actionScreen_actMuteBut->fn->setScheme(actionScreen_actMuteBut, &WhiteScheme);
        else
            actionScreen_actMuteBut->fn->setScheme(actionScreen_actMuteBut, &BlackScheme);

        appData.oldMuteFlg = appData.muteFlg;

        setActionViewTimeOut();
        setDispDimTimeOut();
        //DEBUG_PRINT("actMuteBut\n");
        //setDisplayIntensity();
    }
}

void event_actionScreen_actMenuBut_OnPressed(leButtonWidget* btn) {
    (void) btn;
    appData.reqUiAction = UIREQ_GOTO_MENU;
    
}

void event_actionScreen_actAnaDigiSelectionBut_OnPressed(leButtonWidget* btn) {
    (void) btn;

    actionScreen_digiInpNamePanel->fn->setEnabled(actionScreen_digiInpNamePanel, LE_TRUE);
    actionScreen_digiInpNamePanel->fn->setVisible(actionScreen_digiInpNamePanel, LE_TRUE);

    actionScreen_anaInpNamePanel->fn->setEnabled(actionScreen_anaInpNamePanel, LE_FALSE);
    actionScreen_anaInpNamePanel->fn->setVisible(actionScreen_anaInpNamePanel, LE_FALSE);

    setActionViewTimeOut();
    setDispDimTimeOut();
    //DEBUG_PRINT("actANADIGIpressed\n");
    //setDisplayIntensity();
}

void event_actionScreen_actAnaDigiSelectionBut_OnReleased(leButtonWidget* btn) {
    (void) btn;

    actionScreen_digiInpNamePanel->fn->setEnabled(actionScreen_digiInpNamePanel, LE_FALSE);
    actionScreen_digiInpNamePanel->fn->setVisible(actionScreen_digiInpNamePanel, LE_FALSE);

    actionScreen_anaInpNamePanel->fn->setEnabled(actionScreen_anaInpNamePanel, LE_TRUE);
    actionScreen_anaInpNamePanel->fn->setVisible(actionScreen_anaInpNamePanel, LE_TRUE);

    setActionViewTimeOut();
    //DEBUG_PRINT("actANADIGIReleased\n");
    setDispDimTimeOut();
    //setDisplayIntensity();
}

/* --- Volume +/- buttons --- */

void event_actionScreen_actVolPlusBut_OnPressed(leButtonWidget* btn) {
    s_activeBtn = btn;
    SetCaptureRect((leWidget*) btn);
    StartVolumeRepeat(VOL_DIR_UP);
}

void event_actionScreen_actVolPlusBut_OnReleased(leButtonWidget* btn) {
    (void) btn;
    StopVolumeRepeat();
    s_activeBtn = NULL;
}

void event_actionScreen_actVolMinusBut_OnPressed(leButtonWidget* btn) {
    s_activeBtn = btn;
    SetCaptureRect((leWidget*) btn);
    StartVolumeRepeat(VOL_DIR_DOWN);
}

void event_actionScreen_actVolMinusBut_OnReleased(leButtonWidget* btn) {
    (void) btn;
    StopVolumeRepeat();
    s_activeBtn = NULL;
}

/* --- Input buttons --- */

static void CommonInputPress(uint8_t inp, leButtonWidget* btn, bool showDigi) {
    if (!ignoreEvent) {
        if (appData.curInp != inp)
            clrSelectedInput();

        appData.curInp = inp;
        btn->fn->setEnabled(btn, LE_FALSE);
        btn->fn->setReleasedImage(btn, (leImage*) & smallSelected2);

        if (showDigi) showDigiInfoPanel();
        else hideDigiInfoPanel();

        setInput();
        setActionViewTimeOut();
        setDispDimTimeOut();
        //DEBUG_PRINT("CommonInput\n");
        //setDisplayIntensity();
    }
}

void event_actionScreen_anaInp1But_OnPressed(leButtonWidget* btn) {
    CommonInputPress(1, btn, false);
}

void event_actionScreen_anaInp2But_OnPressed(leButtonWidget* btn) {
    CommonInputPress(2, btn, false);
}

void event_actionScreen_anaInp3But_OnPressed(leButtonWidget* btn) {
    CommonInputPress(3, btn, false);
}

void event_actionScreen_anaInp4But_OnPressed(leButtonWidget* btn) {
    CommonInputPress(4, btn, false);
}

void event_actionScreen_anaInp5But_OnPressed(leButtonWidget* btn) {
    CommonInputPress(5, btn, false);
}

void event_actionScreen_anaInp6But_OnPressed(leButtonWidget* btn) {
    CommonInputPress(6, btn, false);
}

void event_actionScreen_digiInp7But_OnPressed(leButtonWidget* btn) {
    CommonInputPress(7, btn, true);
}

void event_actionScreen_digiInp8But_OnPressed(leButtonWidget* btn) {
    CommonInputPress(8, btn, true);
}

void event_actionScreen_digiInp9But_OnPressed(leButtonWidget* btn) {
    CommonInputPress(9, btn, true);
}

void event_actionScreen_digiInp10But_OnPressed(leButtonWidget* btn) {
    CommonInputPress(10, btn, true);
}

void event_actionScreen_digiInp11But_OnPressed(leButtonWidget* btn) {
    CommonInputPress(11, btn, true);
}

/* ============================================================================
 *  Strings / labels
 * ==========================================================================*/

static void updateInputNames(void) {
    /* INPUT 1 NAME */
    leFixedString_Constructor(&inp1Str, legatoInpNameBuffer1, 16);
    strncpy(cCharBuffer2, inpNames[1], 8);
    inp1Str.fn->setFont(&inp1Str, leStringTable_GetStringFont(leGetState()->stringTable, stringID_Inp1Name, 0));
    inp1Str.fn->setFromCStr(&inp1Str, cCharBuffer2);
    actionScreen_anaInp1But->fn->setString(actionScreen_anaInp1But, (leString*) & inp1Str);

    /* INPUT 2 NAME */
    leFixedString_Constructor(&inp2Str, legatoInpNameBuffer2, 16);
    strncpy(cCharBuffer2, inpNames[2], 8);
    inp2Str.fn->setFont(&inp2Str, leStringTable_GetStringFont(leGetState()->stringTable, stringID_Inp2Name, 0));
    inp2Str.fn->setFromCStr(&inp2Str, cCharBuffer2);
    actionScreen_anaInp2But->fn->setString(actionScreen_anaInp2But, (leString*) & inp2Str);

    /* INPUT 3 NAME */
    leFixedString_Constructor(&inp3Str, legatoInpNameBuffer3, 16);
    strncpy(cCharBuffer2, inpNames[3], 8);
    inp3Str.fn->setFont(&inp3Str, leStringTable_GetStringFont(leGetState()->stringTable, stringID_inp3Name, 0));
    inp3Str.fn->setFromCStr(&inp3Str, cCharBuffer2);
    actionScreen_anaInp3But->fn->setString(actionScreen_anaInp3But, (leString*) & inp3Str);

    /* INPUT 4 NAME */
    leFixedString_Constructor(&inp4Str, legatoInpNameBuffer4, 16);
    strncpy(cCharBuffer2, inpNames[4], 8);
    inp4Str.fn->setFont(&inp4Str, leStringTable_GetStringFont(leGetState()->stringTable, stringID_Inp4Name, 0));
    inp4Str.fn->setFromCStr(&inp4Str, cCharBuffer2);
    actionScreen_anaInp4But->fn->setString(actionScreen_anaInp4But, (leString*) & inp4Str);

    /* INPUT 5 NAME */
    leFixedString_Constructor(&inp5Str, legatoInpNameBuffer5, 16);
    strncpy(cCharBuffer2, inpNames[5], 8);
    inp5Str.fn->setFont(&inp5Str, leStringTable_GetStringFont(leGetState()->stringTable, stringID_Inp5Name, 0));
    inp5Str.fn->setFromCStr(&inp5Str, cCharBuffer2);
    actionScreen_anaInp5But->fn->setString(actionScreen_anaInp5But, (leString*) & inp5Str);

    /* INPUT 6 NAME */
    leFixedString_Constructor(&inp6Str, legatoInpNameBuffer6, 16);
    strncpy(cCharBuffer2, inpNames[6], 8);
    inp6Str.fn->setFont(&inp6Str, leStringTable_GetStringFont(leGetState()->stringTable, stringID_Inp6Name, 0));
    inp6Str.fn->setFromCStr(&inp6Str, cCharBuffer2);
    actionScreen_anaInp6But->fn->setString(actionScreen_anaInp6But, (leString*) & inp6Str);

    /* INPUT 7 NAME */
    leFixedString_Constructor(&inp7Str, legatoInpNameBuffer7, 16);
    strncpy(cCharBuffer2, inpNames[7], 8);
    inp7Str.fn->setFont(&inp7Str, leStringTable_GetStringFont(leGetState()->stringTable, stringID_Inp7Name, 0));
    inp7Str.fn->setFromCStr(&inp7Str, cCharBuffer2);
    actionScreen_digiInp7But->fn->setString(actionScreen_digiInp7But, (leString*) & inp7Str);

    /* INPUT 8 NAME */
    leFixedString_Constructor(&inp8Str, legatoInpNameBuffer8, 16);
    strncpy(cCharBuffer2, inpNames[8], 8);
    inp8Str.fn->setFont(&inp8Str, leStringTable_GetStringFont(leGetState()->stringTable, stringID_Inp8Name, 0));
    inp8Str.fn->setFromCStr(&inp8Str, cCharBuffer2);
    actionScreen_digiInp8But->fn->setString(actionScreen_digiInp8But, (leString*) & inp8Str);

    /* INPUT 9 NAME */
    leFixedString_Constructor(&inp9Str, legatoInpNameBuffer9, 16);
    strncpy(cCharBuffer2, inpNames[9], 8);
    inp9Str.fn->setFont(&inp9Str, leStringTable_GetStringFont(leGetState()->stringTable, stringID_Inp9Name, 0));
    inp9Str.fn->setFromCStr(&inp9Str, cCharBuffer2);
    actionScreen_digiInp9But->fn->setString(actionScreen_digiInp9But, (leString*) & inp9Str);

    /* INPUT 10 NAME */
    leFixedString_Constructor(&inp10Str, legatoInpNameBuffer10, 16);
    strncpy(cCharBuffer2, inpNames[10], 8);
    inp10Str.fn->setFont(&inp10Str, leStringTable_GetStringFont(leGetState()->stringTable, stringID_Inp10Name, 0));
    inp10Str.fn->setFromCStr(&inp10Str, cCharBuffer2);
    actionScreen_digiInp10But->fn->setString(actionScreen_digiInp10But, (leString*) & inp10Str);

    /* INPUT 11 NAME */
    leFixedString_Constructor(&inp11Str, legatoInpNameBuffer11, 16);
    strncpy(cCharBuffer2, inpNames[11], 8);
    inp11Str.fn->setFont(&inp11Str, leStringTable_GetStringFont(leGetState()->stringTable, stringID_Inp11Name, 0));
    inp11Str.fn->setFromCStr(&inp11Str, cCharBuffer2);
    actionScreen_digiInp11But->fn->setString(actionScreen_digiInp11But, (leString*) & inp11Str);
}

void updateVolumeDisplay(void) {
    leFixedString_Constructor(&levelString, legatoCharBuffer, 16);
    levelString.fn->setFont(&levelString, leStringTable_GetStringFont(leGetState()->stringTable, stringID_curLevelStr, 0));
    sprintf(cCharBuffer, "%u", appData.curLvl);
    levelString.fn->setFromCStr(&levelString, cCharBuffer);
    actionScreen_actCurLevel->fn->setString(actionScreen_actCurLevel, (leString*) & levelString);
}

/* ============================================================================
 *  Action screen lifecycle
 * ==========================================================================*/

void initScreenSwapDelay(void) {
    if (appData.screenSwapDelayHandle != SYS_TIME_HANDLE_INVALID)
        (void)SYS_TIME_TimerDestroy(appData.screenSwapDelayHandle);

    appData.screenSwapDelayHandle =
            SYS_TIME_CallbackRegisterMS(screenSwapTimeOut_Callback, 0, screenSwapTimeOut, SYS_TIME_SINGLE);
}



void actionScreen_OnShow(void) {
    actionScreen_actVolumeHeader->fn->setBackgroundType(actionScreen_actVolumeHeader, LE_WIDGET_BACKGROUND_NONE);

    appData.state = APP_ACTION_SCREEN_TASKS;
    ignoreEvent = 1;

    showValidInputs();
    clrSelectedInput();
    setActiveInput();
    
    if(appData.curLvl == 0 && !AvSelected(appData.avInp, appData.curInp))
    {
      actionScreen_actMuteBut->fn->setEnabled(actionScreen_actMuteBut,LE_FALSE);
      actionScreen_actMuteBut->fn->setVisible(actionScreen_actMuteBut,LE_TRUE);
      actionScreen_actMuteBut->fn->setScheme(actionScreen_actMuteBut, &BlackScheme);
    }
    else
    {
      actionScreen_actMuteBut->fn->setEnabled(actionScreen_actMuteBut,LE_TRUE);
        
    }
        
    if (appData.muteFlg)
    {
        actionScreen_actMuteBut->fn->setScheme(actionScreen_actMuteBut, &WhiteScheme);
        appData.skipUnmuteFlg = 1;
    }

    updateVolumeDisplay();
    if (AvSelected(appData.avInp, appData.curInp)) {
            setAvLevel();
            actionScreen_actCurLevel->fn->setVisible(actionScreen_actCurLevel, LE_FALSE);
            actionScreen_avLevLabel->fn->setVisible(actionScreen_avLevLabel, LE_TRUE);
            actionScreen_actVolumeButImg->fn->setVisible(actionScreen_actVolumeButImg, LE_FALSE);
            actionScreen_actMuteBut->fn->setEnabled(actionScreen_actMuteBut, LE_TRUE);
            appData.avFlg = 1;
        }
 
    
    
    updateInputNames();

    setActionViewTimeOut();
    setDispDimTimeOut();



    leFixedString_Constructor(&dacFsStr, legatoFsCharBuffer, 16);

    if (appData.curInp > 6) {
        digiCacheInvalid = true;
        appData.ampStatusChangeFlg = 1;
        showDigiInfoPanel();
    }

    initScreenSwapDelay();

    ignoreEvent = 0;
}

void actionScreen_OnHide(void) {
    StopVolumeRepeat();
}

/* ============================================================================
 *  DIR FS acquisition + Digi Info panel
 * ==========================================================================*/

static inline uint32_t ms_now(void) {
    return millis(); // din eksisterende millis()
}

static inline uint32_t ms_elapsed(uint32_t now, uint32_t then) {
    // 100% wrap-safe (uint32 overflow er defineret)
    return (uint32_t) (now - then);
}

static inline bool ms_due(uint32_t now, uint32_t *tNext) {
    // wrap-safe: true når now er nået eller passeret tNext
    return (ms_elapsed(now, *tNext) < 0x80000000u);
}

void DIR_FS_MonitorTask(bool dacLocked) {
    static uint32_t nextPollMs = 0;
    static uint32_t lastChangeMs = 0;
    static uint8_t lastFs = 1u;

    const uint32_t now = ms_now();

    if (!dacLocked) {
        nextPollMs = 0;
        lastChangeMs = now;
        lastFs = 1u;
        return;
    }

    if (!ms_due(now, &nextPollMs))
        return;

    nextPollMs = now + 200u;

    const uint8_t fs = dacData.dirFs.curFs; // <-- LÆS KUN (fra AcqTask)

    if (fs != lastFs) {
        lastFs = fs;
        lastChangeMs = now;
    }

    if (fs != 1u && ms_elapsed(now, lastChangeMs) > 2200u) {
        DEBUG_PRINT("[digi] WARNING: lock=1 curFs stuck=%u for %lu ms (dirState=%u)\r\n",
                (unsigned) fs,
                (unsigned long) ms_elapsed(now, lastChangeMs),
                (unsigned) dacData.dirFs.state);
        lastChangeMs = now; // throttle
    }
}


#define DIGI_DBG  1
#if DIGI_DBG

static inline bool DigiDbg_1Hz(uint32_t nowMs) {
    static uint32_t nextMs = 0;
    if ((int32_t) (nowMs - nextMs) < 0)
        return false;

    nextMs = nowMs + 1000u;
    return true;
}
#else

static inline bool DigiDbg_1Hz(uint32_t nowMs) {
    (void) nowMs;
    return false;
}
#endif

void updateDigiInfoPanel(void)
{
#if DIGI_DBG
    static uint32_t last;
    uint32_t _now = millis32();
    if ((_now - last) > 1000u)
    {
        last = _now;
        DEBUG_PRINT("[digi] alive scr=%u inp=%u vis=%u lock=%u curFs=%u dsd=%u gain=%u pcm=%u\r\n",
                    (unsigned)legato_getCurrentScreen(),
                    (unsigned)appData.curInp,
                    (unsigned)actionScreen_digInfoPanel->fn->getVisible(actionScreen_digInfoPanel),
                    (unsigned)(dacData.signalLockFlg != 0),
                    (unsigned)dacData.dirFs.curFs,
                    (unsigned)dacData.dsdOnFlg,
                    (unsigned)dacData.digiGain,
                    (unsigned)dacData.pcmFilter);
    }
#endif

    // Fast exits
    if (legato_getCurrentScreen() != screenID_actionScreen) return;
    if (appData.curInp <= 6u) return;
    if (!actionScreen_digInfoPanel->fn->getVisible(actionScreen_digInfoPanel)) return;

    typedef struct
    {
        bool     lastLockPressed;
        bool     lastIsUsb;
        uint8_t  lastFsIndexKey;

        // debug/stuck tracking (valgfrit)
        uint8_t  lastSeenCurFs;
        uint32_t lastFsChangeMs;

        // USB battery UI cache
        bool     lastUsbCharging;
        bool     lastBattPanelVisible;

        // Gain cache
        bool     lastDigiGain;

        // DSD LP / PCM label gating caches
        bool     lastDsdLpVisible;
        bool     lastPcmVisible;
        uint8_t  lastPcmFilter;

        // FS stability gate (USB)
        bool     lastDsdOn;
        bool     lastUsbOk;
        uint8_t  lastUsbFs;
        uint32_t fsHoldUntilMs;
    } digi_cache_t;

    static digi_cache_t s;

    // Cache invalidate
    if (digiCacheInvalid)
    {
        memset(&s, 0xFF, sizeof(s));    // force refresh
        digiCacheInvalid = false;

        // VIGTIGT: memset -> 0xFFFFFFFF, så nulstil hold
        s.fsHoldUntilMs = 0u;
    }

    const bool isUsb   = (appData.curInp == 7u);
    const bool isSpdif = (appData.curInp > 7u);
    const uint32_t now = millis32();

    // ------------------------------------
    // USB battery panel (UI-only)
    // ------------------------------------
    if (isUsb)
    {
        if (!s.lastBattPanelVisible)
        {
            actionScreen_batteryPanel->fn->setVisible(actionScreen_batteryPanel, LE_TRUE);
            s.lastBattPanelVisible = true;
        }

        if (s.lastUsbCharging != dacData.usbCharging)
        {
            actionScreen_BattCharging->fn->setVisible(actionScreen_BattCharging,
                                                      dacData.usbCharging ? LE_TRUE : LE_FALSE);
            s.lastUsbCharging = dacData.usbCharging;
        }
    }
    else
    {
        if (s.lastBattPanelVisible)
        {
            actionScreen_batteryPanel->fn->setVisible(actionScreen_batteryPanel, LE_FALSE);
            actionScreen_BattCharging->fn->setVisible(actionScreen_BattCharging, LE_FALSE);
            s.lastBattPanelVisible = false;
            s.lastUsbCharging = false;
        }
    }

    // ------------------------------------
    // FS + lock (UI-only)
    // ------------------------------------
    bool lockPressed = false;
    const char* fsStr = " ";
    uint8_t fsKey = 0;

    // --- USB: robust hold trigger ---
    if (isUsb)
    {
        const bool dsdNow = (dacData.dsdOnFlg != 0u);
        const bool usbOk  = (dacData.signalLockFlg && dacData.usbPluggedFlg && !dacData.dacMuteFlg);
        const uint8_t usbFs = dacData.usbFs;

        // trigger hold on ANY instability during transitions
        bool trig = false;
        if (s.lastDsdOn != dsdNow) { s.lastDsdOn = dsdNow; trig = true; }
        if (s.lastUsbOk != usbOk)  { s.lastUsbOk = usbOk;  trig = true; }
        if (s.lastUsbFs != usbFs)  { s.lastUsbFs = usbFs;  trig = true; }

        if (trig)
        {
            // start/extend hold (do not shorten)
            uint32_t until = now + 350u; // 350ms er ofte mere realistisk end 200ms
            // enkel "extend" logik; wrap er sjældent relevant her, men dette er robust nok:
            if ((int32_t)(until - s.fsHoldUntilMs) > 0)
                s.fsHoldUntilMs = until;
        }

        lockPressed = usbOk;

        if (usbOk)
        {
            fsKey = (uint8_t)(0x80u | (usbFs & 0x7Fu));
            fsStr = usbFsTabel[usbFs];
        }
        else
        {
            fsKey = (uint8_t)(0x80u | (dacData.usbPluggedFlg ? 13u : 14u));
            fsStr = usbFsTabel[dacData.usbPluggedFlg ? 13 : 14];
        }
    }
    else
    {
        // not USB -> no hold
        s.fsHoldUntilMs = 0u;

        if (isSpdif)
        {
            lockPressed = (dacData.signalLockFlg != 0);

            if (dacData.signalLockFlg)
            {
                uint8_t fs = dacData.dirFs.curFs;
                fsKey = fs;
                fsStr = dacFsTabel[fs];
            }
            else
            {
                fsKey = 1u;
                fsStr = "NO SIGNAL";
            }
        }
    }

    // Lock ikon (cache)
    if (s.lastLockPressed != lockPressed)
    {
        s.lastLockPressed = lockPressed;
        actionScreen_padLockImg->fn->setPressed(actionScreen_padLockImg,
                                                lockPressed ? LE_TRUE : LE_FALSE);
    }

    // FS label (cache + hold gate)
    if (!isUsb || (now >= s.fsHoldUntilMs))
    {
        if ((s.lastFsIndexKey != fsKey) || (s.lastIsUsb != isUsb))
        {
            s.lastFsIndexKey = fsKey;
            s.lastIsUsb = isUsb;

            dacFsStr.fn->setFromCStr(&dacFsStr, fsStr);
            dacFsStr.fn->setFont(&dacFsStr,
                leStringTable_GetStringFont(leGetState()->stringTable, stringID_actDigiInfoFsStr, 0));

            actionScreen_digiInfoFSLabel->fn->setString(actionScreen_digiInfoFSLabel,
                                                        (leString*)&dacFsStr);
        }
    }

    // ------------------------------------
    // Resten af digi info panelet (UI-only sync) - cached
    // ------------------------------------
    // DSD LP (kun USB+DSD)
    const bool showDsdLp = (isUsb && (dacData.dsdOnFlg != 0u));
    if (s.lastDsdLpVisible != showDsdLp)
    {
        s.lastDsdLpVisible = showDsdLp;
        DacUi_SyncDsdLp_CurrentScreen();  // skal selv håndtere at skjule ved PCM
    }

    // PCM filter labels (kun når ikke USB+DSD)
    const bool showPcm = !showDsdLp;
    uint8_t f = dacData.pcmFilter;
    if (f < 1u || f > 7u) f = 4u;

    if ((s.lastPcmFilter != f) || (s.lastPcmVisible != showPcm))
    {
        s.lastPcmFilter = f;
        s.lastPcmVisible = showPcm;
        DacUi_SyncPcmFilterLabels_ActionScreen(f); // forventes at slukke DSD LP widgets i PCM
    }

    // Gain (UI-only) - stable
    const bool on0dB = (dacData.digiGain != 0u);
    if (s.lastDigiGain != on0dB)
    {
        s.lastDigiGain = on0dB;
        actionScreen_gain0db->fn->setVisible(actionScreen_gain0db, on0dB ? LE_TRUE : LE_FALSE);
        actionScreen_gainMinus6dB->fn->setVisible(actionScreen_gainMinus6dB, on0dB ? LE_FALSE : LE_TRUE);
    }

#if DIGI_DBG
    // evt. ekstra debug kan ligge her
#endif
}

void DIR_FS_AcqTask(bool dacLocked) {
    const uint32_t now = ms_now();
    static bool s_prevLocked = false;
    static uint8_t s_badCnt = 0;

    // ---- Unlock: reset state ----
    if (!dacLocked) {
        s_prevLocked = false;
        s_badCnt = 0;

        dacData.dirFs.state = DIR_FS_IDLE;
        dacData.dirFs.curFs = 1u;
        dacData.dirFs.lastValidFs = 1u;
        dacData.dirFs.retryCnt = 0u;
        dacData.dirFs.failCycles = 0u;
        dacData.dirFs.reinitCnt = 0u;
        dacData.dirFs.reinitBlockUntilMs = 0u;
        dacData.dirFs.tNextMs = 0u;
        return;
    }

    // ---- Lock rising edge: reinit once ----
    if (dacLocked && !s_prevLocked) {
        s_badCnt = 0;

        dirReset();
        dirSetup();
        setDirInput();

        dacData.dirFs.state = DIR_FS_WAIT_FIRST;
        dacData.dirFs.tNextMs = now + DIR_FS_LOCK_EDGE_REINIT_DELAY_MS;
        dacData.dirFs.retryCnt = 0u;
        dacData.dirFs.failCycles = 0u;
        dacData.dirFs.curFs = 1u;
        dacData.dirFs.lastValidFs = 1u;
        dacData.dirFs.reinitCnt = 0u;
        dacData.dirFs.reinitBlockUntilMs = 0u;

        // DEBUG_PRINT("[dirfs] lock edge: 0 -> 1\r\n");
    }
    s_prevLocked = true;

    switch (dacData.dirFs.state) {
        case DIR_FS_IDLE:
        {
            dacData.dirFs.state = DIR_FS_MONITOR;
            dacData.dirFs.tNextMs = now + DIR_FS_MONITOR_POLL_MS;
            return;
        }

        case DIR_FS_WAIT_FIRST:
        case DIR_FS_RETRY:
        {
            if (!ms_due(now, &dacData.dirFs.tNextMs))
                return;

            // Plan næste ?due?
            dacData.dirFs.tNextMs = now + ((dacData.dirFs.state == DIR_FS_RETRY) ?
                    DIR_FS_RETRY_DELAY_MS :
                    DIR_FS_FIRST_DELAY_MS);

            const uint8_t fs = dirGetFs();
            dacData.dirFs.curFs = fs;

            // ?valid?
            if (fs != 1u) {
                dacData.dirFs.lastValidFs = fs;
                dacData.dirFs.retryCnt = 0u;
                dacData.dirFs.failCycles = 0u;

                dacData.dirFs.state = DIR_FS_MONITOR;
                dacData.dirFs.tNextMs = now + DIR_FS_MONITOR_POLL_MS;
                return;
            }

            // fs == 1 => retry logic
            dacData.dirFs.retryCnt++;

            if (dacData.dirFs.retryCnt < DIR_FS_RETRY_MAX) {
                dacData.dirFs.state = DIR_FS_RETRY;
                dacData.dirFs.tNextMs = now + DIR_FS_RETRY_DELAY_MS;
                return;
            }

            // retry streak ended => count a fail-cycle
            dacData.dirFs.retryCnt = 0u;
            dacData.dirFs.failCycles++;

            dacData.dirFs.state = DIR_FS_WAIT_FIRST;
            dacData.dirFs.tNextMs = now + DIR_FS_FIRST_DELAY_MS;

            // optional reinit after too many fail cycles (cooldown protected)
            if (dacData.dirFs.failCycles >= DIR_FS_FAIL_CYCLES_BEFORE_REINIT) {
                if (dacData.dirFs.reinitCnt < DIR_FS_REINIT_MAX_PER_LOCK &&
                        ms_elapsed(now, dacData.dirFs.reinitBlockUntilMs) >= 0x80000000u ? false : true) {
                    // ms_due-agtig check: vi vil kun reinit når now >= blockUntil
                    if (ms_elapsed(now, dacData.dirFs.reinitBlockUntilMs) < 0x80000000u) {
                        dirReset();
                        dirSetup();
                        setDirInput();

                        DEBUG_PRINT("[dirfs] REINIT (failCycles=%u)\r\n",
                                (unsigned) dacData.dirFs.failCycles);

                        dacData.dirFs.reinitCnt++;
                        dacData.dirFs.reinitBlockUntilMs = now + DIR_FS_REINIT_COOLDOWN_MS;

                        dacData.dirFs.failCycles = 0u;
                        dacData.dirFs.tNextMs = now + DIR_FS_LOCK_EDGE_REINIT_DELAY_MS;
                    }
                }
            }
            return;
        }

        case DIR_FS_MONITOR:
        {
            if (!ms_due(now, &dacData.dirFs.tNextMs))
                return;

            dacData.dirFs.tNextMs = now + DIR_FS_MONITOR_POLL_MS;

            const uint8_t fs = dirGetFs();

            // DEBUG_PRINT("DIR FS raw: %u\r\n", (unsigned)fs);

            if (fs == 1u) {
                if (s_badCnt < 255u) s_badCnt++;

                if (s_badCnt >= DIR_FS_MONITOR_BAD_TO_BLANK) {
                    if (dacData.dirFs.curFs != 1u) {
                        DEBUG_PRINT("[dirfs] monitor -> BLANK (fs==1 x%u)\r\n",
                                (unsigned) s_badCnt);
                        dacData.dirFs.curFs = 1u;
                        dacData.dirFs.lastValidFs = 1u;
                    }
                }
                return;
            }

            // fs != 1
            s_badCnt = 0u;

            if (fs != dacData.dirFs.curFs) {
                DEBUG_PRINT("[dirfs] monitor -> FS change %u -> %u\r\n",
                        (unsigned) dacData.dirFs.curFs, (unsigned) fs);
                dacData.dirFs.curFs = fs;
                dacData.dirFs.lastValidFs = fs;
            }
            return;
        }

        default:
        {
            dacData.dirFs.state = DIR_FS_WAIT_FIRST;
            dacData.dirFs.tNextMs = now + DIR_FS_FIRST_DELAY_MS;
            return;
        }
    }
}


/* ============================================================================
 *  Main Action screen updater
 * ==========================================================================*/

static uint32_t s_nextDigiUiMs = 0;
static uint32_t s_nextDigiUiMs2 = 0;

static bool DigiUi_TimeToRun(void) {
    const uint32_t now = millis32();
    if ((int32_t) (now - s_nextDigiUiMs) < 0)
        return false;

    s_nextDigiUiMs = now + 200u; // 5 Hz
    //DEBUG_PRINT("TTR %ul\r\n",s_nextDigiUiMs);  
    return true;
}

static bool DigiUi_TimeToRun2000(void) {
    const uint32_t now = millis32();
    if ((int32_t) (now - s_nextDigiUiMs2) < 0)
        return false;

    s_nextDigiUiMs2 = now + 2000u; // 
    //DEBUG_PRINT("HB %ul\r\n",s_nextDigiUiMs2);  
    return true;
}

void updateActionScreen(void) {
    DigiUi_TimeToRun2000();

    if (legato_getCurrentScreen() == screenID_actionScreen) {
        if (appData.irInputChangeFlg) {
            if (appData.curInp > 0u && appData.curInp < 7u) {
                actionScreen_actAnaDigiSelectionBut->fn->setPressed(actionScreen_actAnaDigiSelectionBut, LE_FALSE);
                actionScreen_digiInpNamePanel->fn->setEnabled(actionScreen_digiInpNamePanel, LE_FALSE);
                actionScreen_digiInpNamePanel->fn->setVisible(actionScreen_digiInpNamePanel, LE_FALSE);

                actionScreen_anaInpNamePanel->fn->setEnabled(actionScreen_anaInpNamePanel, LE_TRUE);
                actionScreen_anaInpNamePanel->fn->setVisible(actionScreen_anaInpNamePanel, LE_TRUE);
            } else if (appData.dacRegiFlg) {
                showDigiInfoPanel();
                actionScreen_actAnaDigiSelectionBut->fn->setPressed(actionScreen_actAnaDigiSelectionBut, LE_TRUE);

                actionScreen_digiInpNamePanel->fn->setEnabled(actionScreen_digiInpNamePanel, LE_TRUE);
                actionScreen_digiInpNamePanel->fn->setVisible(actionScreen_digiInpNamePanel, LE_TRUE);

                actionScreen_anaInpNamePanel->fn->setEnabled(actionScreen_anaInpNamePanel, LE_FALSE);
                actionScreen_anaInpNamePanel->fn->setVisible(actionScreen_anaInpNamePanel, LE_FALSE);
            }

            clrSelectedInput();
            setActiveInput();

            setInput();

            appData.irInputChangeFlg = 0;
            DEBUG_PRINT("Set Input done\r\n");
        }

        if (DigiUi_TimeToRun() && appData.curInp > 6u) {
            if (appData.curInp > 7u) {
                DIR_FS_AcqTask(dacData.signalLockFlg);
                DIR_FS_MonitorTask(dacData.signalLockFlg);
            }
            updateDigiInfoPanel();
        }
        if (g_digiInfoDirty) {
            g_digiInfoDirty = false;
            DEBUG_PRINT("g_digiInfoDirty\r\n");
            // Kun her må du røre Legato widgets
            updateDigiInfoPanel();
        }
        if (AvSelected(appData.avInp, appData.curInp)) {
            if (!appData.avFlg) {
                setAvLevel();
                actionScreen_actCurLevel->fn->setVisible(actionScreen_actCurLevel, LE_FALSE);
                actionScreen_avLevLabel->fn->setVisible(actionScreen_avLevLabel, LE_TRUE);
                actionScreen_actVolumeButImg->fn->setVisible(actionScreen_actVolumeButImg, LE_FALSE);
                actionScreen_actMuteBut->fn->setEnabled(actionScreen_actMuteBut, LE_TRUE);
            }
            appData.avFlg = 1;
        } else if (appData.avFlg) {
            actionScreen_actCurLevel->fn->setVisible(actionScreen_actCurLevel, LE_TRUE);
            actionScreen_avLevLabel->fn->setVisible(actionScreen_avLevLabel, LE_FALSE);
            actionScreen_actVolumeButImg->fn->setVisible(actionScreen_actVolumeButImg, LE_TRUE);
            oldLevelValue = avLevInp;
            appData.avFlg = 0;
        }
    }

    if ((dacData.dacDigiChangeFlg || oldLevelValue != appData.curLvl) &&
            legato_getCurrentScreen() == screenID_actionScreen) {
        sprintf(cCharBuffer, "%u", appData.curLvl);
        oldLevelValue = appData.curLvl;

        levelString.fn->setFromCStr(&levelString, cCharBuffer);
        actionScreen_actCurLevel->fn->setString(actionScreen_actCurLevel, (leString*) & levelString);

        UpdateVolume();
        dacData.dacDigiChangeFlg = 0;
    }

    if (appData.muteFlg != appData.oldMuteFlg && legato_getCurrentScreen() == screenID_actionScreen) {
        if (appData.muteFlg)
            actionScreen_actMuteBut->fn->setScheme(actionScreen_actMuteBut, &WhiteScheme);
        else
            actionScreen_actMuteBut->fn->setScheme(actionScreen_actMuteBut, &BlackScheme);

        appData.oldMuteFlg = appData.muteFlg;
    }

    if (legato_getCurrentScreen() == screenID_actionScreen &&
            dacData.lockedButNoSignalTimeOutExpired &&
            appData.curInp > 7u &&
            dacData.signalLockFlg) {
        appData.ampStatusChangeFlg = 1;
        appData.irInputChangeFlg = 1;
        DEBUG_PRINT("Set changeFlag and IRChangeFlag= 1\r\n");
        dacData.lockedButNoSignalTimeOutExpired = 0;
    }
}

/* ============================================================================
 *  UI pump for volume (call from APP_Tasks / UI context)
 * ==========================================================================*/

void ActionScreen_VolumeUiPump(void) {
    if (s_touchErrorAbort) {
        s_touchErrorAbort = false;

        StopVolumeRepeat();
        s_forceVisualRelease = true;
        s_volUiDirty = true;

        s_inpActive = false;
        s_touchIsDown = false;
    }

    if (!s_volUiDirty && !s_forceVisualRelease)
        return;

    s_volUiDirty = false;
    dbg_touch("ui-pump");

    if (s_forceVisualRelease) {
        s_forceVisualRelease = false;

        if (s_activeBtn && s_activeBtn->fn->getPressed(s_activeBtn))
            s_activeBtn->fn->setPressed(s_activeBtn, LE_FALSE);

        s_activeBtn = NULL;
    }

    setActionViewTimeOut();
    setDispDimTimeOut();
    //setDisplayIntensity();
}
