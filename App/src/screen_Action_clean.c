/* 
 * screen_Action.c (cleaned)
 * 
 * Fokus: rydde op efter FS/lock/infopanel forsøg.
 * - Fjernet store udkommenterede blokke
 * - DIR_FS acquisition er samlet i én wrap-safe state machine
 * - updateDigiInfoPanel opdaterer ALT der kan hænge "fast" (labels/lock/fs/battery)
 * - Debug prints: rate-limited + kun ved ændringer, så systemet ikke bliver "optaget"
 *
 * Bemærk:
 *  - Denne fil forudsætter dine eksisterende symboler fra ui_globals.h, app.h
 *    og Legato generated headers.
 *  - Hvis du har andre funktioner i din tidligere screen_Action.c som ikke er
 *    med her, så skal de stadig findes et andet sted i projektet.
 */

#include "definitions.h"
#include "app.h"
#include "ui_globals.h"
#include "gfx/legato/generated/le_gen_harmony.h"
#include "gfx/legato/generated/screen/le_gen_screen_actionScreen.h"

#include "system/time/sys_time.h"
#include "system/input/sys_input.h"
#include "gfx/legato/common/legato_rect.h"

#include <stdarg.h>

/* =========================================================
 * Time helpers (wrap-safe)
 * ========================================================= */
static inline uint32_t millis(void)
{
    // CORETIMER_FrequencyGet() er typisk sysclk/2 på PIC32; division er OK her (UI-rate).
    const uint32_t hz = (uint32_t)CORETIMER_FrequencyGet();
    if (hz == 0u) return 0u;
    return (uint32_t)(CORETIMER_CounterGet() / (hz / 1000u));
}

static inline bool time_due(uint32_t now, uint32_t *tNext, uint32_t periodMs)
{
    // wrap-safe: true når now >= *tNext
    if ((int32_t)(now - *tNext) < 0) return false;
    *tNext = now + periodMs;
    return true;
}

/* =========================================================
 * Digital FS acquisition for DIR (SPDIF inputs 8..11)
 * ========================================================= */

static void DIR_FS_ResetState(void)
{
    dacData.dirFs.state = DIR_FS_IDLE;
    dacData.dirFs.tNextMs = 0u;

    dacData.dirFs.curFs = 1u;        // 1 = blank/unknown in your tables
    dacData.dirFs.lastValidFs = 1u;

    dacData.dirFs.retryCnt = 0u;
    dacData.dirFs.failCycles = 0u;
    dacData.dirFs.reinitCnt = 0u;
    dacData.dirFs.reinitBlockUntilMs = 0u;
}

static void DIR_FS_ReinitHw(void)
{
    // Disse tre er dine eksisterende funktioner
    dirReset();
    dirSetup();
    setDirInput();
}

#if 1
#define DIRFS_DBG 1
#else
#define DIRFS_DBG 0
#endif

#if DIRFS_DBG
static void dirfs_dbg_1hz(const char *fmt, ...)
{
    static uint32_t nextMs = 0;
    uint32_t now = millis();
    if (!time_due(now, &nextMs, 1000u)) return;

    va_list ap;
    va_start(ap, fmt);
    vprintf(fmt, ap);
    va_end(ap);
}
#endif

void DIR_FS_AcqTask(bool dacLocked)
{
    static bool s_prevLocked = false;

    // stable sampling
    static uint8_t s_lastSample = 1u;
    static uint8_t s_stableCnt  = 0u;
    static uint8_t s_invalidCnt = 0u;

    uint32_t now = millis();

    // ---- Unlock: hard reset (so UI blanks correctly) ----
    if (!dacLocked)
    {
        s_prevLocked = false;
        s_lastSample = 1u;
        s_stableCnt  = 0u;
        s_invalidCnt = 0u;
        DIR_FS_ResetState();
        return;
    }

    // ---- Lock rising edge: reinit once + quick settle ----
    if (dacLocked && !s_prevLocked)
    {
        DIR_FS_ReinitHw();
        DIR_FS_ResetState();
        dacData.dirFs.state = DIR_FS_POLL;
        dacData.dirFs.tNextMs = now + DIR_FS_LOCK_EDGE_REINIT_DELAY_MS;

        s_lastSample = 1u;
        s_stableCnt  = 0u;
        s_invalidCnt = 0u;

#if DIRFS_DBG
        DEBUG_PRINT("[dirfs] lock edge -> reinit\n");
#endif
    }
    s_prevLocked = true;

    // ---- Poll at a modest rate (avoid busy system) ----
    if ((int32_t)(now - dacData.dirFs.tNextMs) < 0)
        return;

    dacData.dirFs.tNextMs = now + DIR_FS_POLL_PERIOD_MS;

    // Only meaningful on SPDIF inputs
    uint8_t fs = dirGetFs();

#if DIRFS_DBG
    // Optional: comment out if too noisy
    // DEBUG_PRINT("DIR FS raw: %u\r\n", (unsigned)fs);
#endif

    // fs==1 is "blank/unknown"
    if (fs == 1u)
    {
        s_invalidCnt++;
        s_stableCnt = 0u;

        if (s_invalidCnt >= DIR_FS_INVALID_BEFORE_REINIT)
        {
            // blank for a while while locked -> consider reinit, but not too often
            if ((int32_t)(now - dacData.dirFs.reinitBlockUntilMs) >= 0)
            {
                if (dacData.dirFs.reinitCnt < DIR_FS_REINIT_MAX_PER_LOCK)
                {
                    DIR_FS_ReinitHw();
                    dacData.dirFs.reinitCnt++;
                    dacData.dirFs.reinitBlockUntilMs = now + DIR_FS_REINIT_COOLDOWN_MS;

#if DIRFS_DBG
                    DEBUG_PRINT("[dirfs] REINIT (blank x%u, reinitCnt=%u)\r\n",
                                (unsigned)s_invalidCnt, (unsigned)dacData.dirFs.reinitCnt);
#endif
                }
            }
            s_invalidCnt = 0u; // reset streak after we attempted (or skipped) reinit
        }

        // When blank persists, reflect it in curFs (but keep lastValidFs if you want history)
        dacData.dirFs.curFs = 1u;
        return;
    }

    // fs != 1
    s_invalidCnt = 0u;

    if (fs == s_lastSample)
    {
        if (s_stableCnt < 255u) s_stableCnt++;
    }
    else
    {
        s_lastSample = fs;
        s_stableCnt = 1u;
    }

    // Commit only after N stable samples to avoid flapping
    if (s_stableCnt >= DIR_FS_STABLE_SAMPLES)
    {
        if (dacData.dirFs.curFs != fs)
        {
            uint8_t prev = dacData.dirFs.curFs;
            dacData.dirFs.curFs = fs;
            dacData.dirFs.lastValidFs = fs;

#if DIRFS_DBG
            DEBUG_PRINT("[dirfs] FS change %u -> %u\r\n", (unsigned)prev, (unsigned)fs);
#endif
        }
    }

    dacData.dirFs.state = DIR_FS_MONITOR;
}

/* =========================================================
 * Digi info panel UI
 * ========================================================= */

static inline void Digi_SetFsLabel(const char *s)
{
    dacFsStr.fn->setFromCStr(&dacFsStr, s);
    dacFsStr.fn->setFont(&dacFsStr,
            leStringTable_GetStringFont(leGetState()->stringTable, stringID_actDigiInfoFsStr, 0));
    actionScreen_digiInfoFSLabel->fn->setString(actionScreen_digiInfoFSLabel, (leString*)&dacFsStr);
}

static void Digi_EnsureCommonPanelState(bool isUsb)
{
    // Battery is only relevant for USB input (7)
    actionScreen_batteryPanel->fn->setVisible(actionScreen_batteryPanel, isUsb ? LE_TRUE : LE_FALSE);

    if (isUsb)
    {
        actionScreen_BattCharging->fn->setVisible(actionScreen_BattCharging,
                dacData.usbCharging ? LE_TRUE : LE_FALSE);
    }
    else
    {
        // ensure "USB leftovers" are hidden
        actionScreen_BattCharging->fn->setVisible(actionScreen_BattCharging, LE_FALSE);
    }

    // DSD LP buttons are never used in action-screen panel in your original logic (hidden)
    actionScreen_dsdLpOn->fn->setVisible(actionScreen_dsdLpOn, LE_FALSE);
    actionScreen_dsdLpOff->fn->setVisible(actionScreen_dsdLpOff, LE_FALSE);

    // Filter labels: visible for PCM, hidden for USB+DSD
    bool showFilters = true;
    if (isUsb && dacData.dsdOnFlg) showFilters = false;

    actionScreen_digiInfoFilterLabel1->fn->setVisible(actionScreen_digiInfoFilterLabel1, showFilters ? LE_TRUE : LE_FALSE);
    actionScreen_digiInfoFilterLabel2->fn->setVisible(actionScreen_digiInfoFilterLabel2, showFilters ? LE_TRUE : LE_FALSE);
    actionScreen_digiInfoFilterLabel3->fn->setVisible(actionScreen_digiInfoFilterLabel3, showFilters ? LE_TRUE : LE_FALSE);

    // Apply filter HW once per call (cheap)
    if (isUsb)
    {
        if (dacData.dsdOnFlg) dacSetDsdLpFilter();
        else                  dacSetPcmFilter();
    }
    else
    {
        dacSetPcmFilter();
    }
}

void hideDigiInfoPanel(void)
{
    if (actionScreen_digInfoPanel->fn->getVisible(actionScreen_digInfoPanel))
        actionScreen_digInfoPanel->fn->setVisible(actionScreen_digInfoPanel, LE_FALSE);
}

void showDigiInfoPanel(void)
{
    if (!actionScreen_digInfoPanel->fn->getVisible(actionScreen_digInfoPanel))
        actionScreen_digInfoPanel->fn->setVisible(actionScreen_digInfoPanel, LE_TRUE);

    updateDigiInfoPanel();
}

#if 1
#define DIGI_DBG 1
#else
#define DIGI_DBG 0
#endif

void updateDigiInfoPanel(void)
{
    // ---- guard ----
    if (legato_getCurrentScreen() != screenID_actionScreen) return;
    if (appData.curInp <= 6) return;
    if (!actionScreen_digInfoPanel->fn->getVisible(actionScreen_digInfoPanel)) return;

    const bool isUsb   = (appData.curInp == 7);
    const bool isSpdif = (appData.curInp > 7);

    typedef struct {
        uint8_t lastInp;
        uint8_t lastFsKey;
        bool    lastLockPressed;
        bool    lastIsUsb;
    } digi_cache_t;

    static digi_cache_t s = {0};

    // Always clean up panel "leftovers" when input changes
    if (s.lastInp != appData.curInp)
    {
        Digi_EnsureCommonPanelState(isUsb);
        s.lastInp = appData.curInp;
        s.lastFsKey = 0;
        s.lastLockPressed = false;
        s.lastIsUsb = false;
    }
    else
    {
        Digi_EnsureCommonPanelState(isUsb);
    }

    bool lockPressed = false;
    uint8_t fsKey = 1u; // default blank
    const char *fsStr = "             ";

    if (isUsb)
    {
        const bool usbOk = (dacData.signalLockFlg && dacData.usbPluggedFlg && !dacData.dacMuteFlg);
        lockPressed = usbOk;

        if (usbOk)
        {
            // USB fs table index
            fsKey = (uint8_t)(0x80u | (dacData.usbFs & 0x7Fu));
            fsStr = usbFsTabel[dacData.usbFs];
        }
        else
        {
            // Show plugged/unplugged string
            const uint8_t idx = dacData.usbPluggedFlg ? 13u : 14u;
            fsKey = (uint8_t)(0x80u | idx);
            fsStr = usbFsTabel[idx];
        }
    }
    else if (isSpdif)
    {
        lockPressed = (dacData.signalLockFlg != 0);

        if (dacData.signalLockFlg)
        {
            // IMPORTANT: do NOT call dirGetFs() here (it can be slow/noisy).
            const uint8_t fs = dacData.dirFs.curFs; // 1 = blank
            fsKey = fs;
            fsStr = dacFsTabel[fs];
        }
        else
        {
            fsKey = 1u;
            fsStr = dacFsTabel[1];
        }
    }

    // ---- lock icon ----
    if (s.lastLockPressed != lockPressed)
    {
        s.lastLockPressed = lockPressed;
        actionScreen_padLockImg->fn->setPressed(actionScreen_padLockImg, lockPressed ? LE_TRUE : LE_FALSE);

#if DIGI_DBG
        DEBUG_PRINT("[digi] lock UI: %u -> %u\r\n", (unsigned)!lockPressed, (unsigned)lockPressed);
#endif
    }

    // ---- FS label ----
    if (s.lastFsKey != fsKey || s.lastIsUsb != isUsb)
    {
        s.lastFsKey = fsKey;
        s.lastIsUsb = isUsb;
        Digi_SetFsLabel(fsStr);

#if DIGI_DBG
        DEBUG_PRINT("[digi] FS UI update: inp=%u fsKey=%u isUsb=%u text='%s'\r\n",
                    (unsigned)appData.curInp, (unsigned)fsKey, (unsigned)isUsb, fsStr);
#endif
    }

    // Gain update: keep it, but don't hammer it in tight loops.
    dacSetGain();
}

/* =========================================================
 * Action screen periodic update hook
 * ========================================================= */

static uint32_t s_nextDigiUiMs = 0;

static bool DigiUi_TimeToRun(void)
{
    uint32_t now = millis();
    // 5 Hz is enough; prevents "system feels busy"
    return time_due(now, &s_nextDigiUiMs, 200u);
}

/* 
 * IMPORTANT:
 * Du har en masse anden logik i updateActionScreen().
 * Her viser vi kun den del der kører digi-panel / FS.
 * Behold resten af din eksisterende updateActionScreen() hvis du har mere end dette.
 */
void updateActionScreen(void)
{
    if (legato_getCurrentScreen() != screenID_actionScreen)
        return;

    // Digi panel updates (rate-limited)
    if (appData.curInp > 6 && DigiUi_TimeToRun())
    {
        // SPDIF: kør DIR FS acquisition når vi er på 8..11
        if (appData.curInp > 7)
        {
            DIR_FS_AcqTask(dacData.signalLockFlg);
        }

        updateDigiInfoPanel();
    }

    // Resten af din updateActionScreen() (volume label, mute UI, input change osv.)
    // ligger typisk i samme fil i dit projekt. Hvis du har det i en anden fil,
    // så er det fint. Hvis ikke: kopier det ind her fra din gamle version.
}

/* End of file */
