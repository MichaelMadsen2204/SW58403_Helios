#ifndef LEGATO_INIT_H
#define LEGATO_INIT_H

#include "gfx/legato/legato.h"

#include "gfx/legato/generated/le_gen_scheme.h"
#include "gfx/legato/generated/le_gen_assets.h"

#include "gfx/legato/generated/screen/le_gen_screen_SN_SET.h"
#include "gfx/legato/generated/screen/le_gen_screen_leftPowerMissingScreen.h"
#include "gfx/legato/generated/screen/le_gen_screen_actionScreen.h"
#include "gfx/legato/generated/screen/le_gen_screen_avInputScreen.h"
#include "gfx/legato/generated/screen/le_gen_screen_dacGainSimpleView.h"
#include "gfx/legato/generated/screen/le_gen_screen_digitalSetupScreen.h"
#include "gfx/legato/generated/screen/le_gen_screen_displayIntensityScreen.h"
#include "gfx/legato/generated/screen/le_gen_screen_displaySimpleView.h"
#include "gfx/legato/generated/screen/le_gen_screen_dsdLpSimpleView.h"
#include "gfx/legato/generated/screen/le_gen_screen_errorDisplay.h"
#include "gfx/legato/generated/screen/le_gen_screen_filterSimpleView.h"
#include "gfx/legato/generated/screen/le_gen_screen_greenBiasScreen.h"
#include "gfx/legato/generated/screen/le_gen_screen_inpLvlMatchScreen.h"
#include "gfx/legato/generated/screen/le_gen_screen_irSourceScreen.h"
#include "gfx/legato/generated/screen/le_gen_screen_mainMenuScreen.h"
#include "gfx/legato/generated/screen/le_gen_screen_pickupSelectScreen.h"
#include "gfx/legato/generated/screen/le_gen_screen_qwertyScreen.h"
#include "gfx/legato/generated/screen/le_gen_screen_renameInputsScreen.h"
#include "gfx/legato/generated/screen/le_gen_screen_restoreSettingScreen.h"
#include "gfx/legato/generated/screen/le_gen_screen_simpleViewScreen.h"
#include "gfx/legato/generated/screen/le_gen_screen_splashScreen.h"
#include "gfx/legato/generated/screen/le_gen_screen_volSettingsScreen.h"
#include "gfx/legato/generated/screen/le_gen_screen_wrongAcVoltageScreen.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

// screen IDs
#define screenID_SN_SET    0
#define screenID_leftPowerMissingScreen    1
#define screenID_actionScreen    2
#define screenID_avInputScreen    3
#define screenID_dacGainSimpleView    4
#define screenID_digitalSetupScreen    5
#define screenID_displayIntensityScreen    6
#define screenID_displaySimpleView    7
#define screenID_dsdLpSimpleView    8
#define screenID_errorDisplay    9
#define screenID_filterSimpleView    10
#define screenID_greenBiasScreen    11
#define screenID_inpLvlMatchScreen    12
#define screenID_irSourceScreen    13
#define screenID_mainMenuScreen    14
#define screenID_pickupSelectScreen    15
#define screenID_qwertyScreen    16
#define screenID_renameInputsScreen    17
#define screenID_restoreSettingScreen    18
#define screenID_simpleViewScreen    19
#define screenID_splashScreen    20
#define screenID_volSettingsScreen    21
#define screenID_wrongAcVoltageScreen    22

void legato_initializeScreenState(void);

// global screen control functions
uint32_t legato_getCurrentScreen(void);
void legato_showScreen(uint32_t id);
void legato_updateScreenState(void);

// do not do anything in the application if this returns true
leBool legato_isChangingScreens(void);


//DOM-IGNORE-BEGIN

#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // LEGATO_INIT_H
