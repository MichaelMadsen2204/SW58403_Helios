#ifndef LE_GEN_SCREEN_LEFTPOWERMISSINGSCREEN_H
#define LE_GEN_SCREEN_LEFTPOWERMISSINGSCREEN_H

#include "gfx/legato/legato.h"

#include "gfx/legato/generated/le_gen_scheme.h"
#include "gfx/legato/generated/le_gen_assets.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

// screen member widget declarations
extern leWidget* leftPowerMissingScreen_Panel_0;
extern leLabelWidget* leftPowerMissingScreen_LabelWidget_0;
extern leLabelWidget* leftPowerMissingScreen_LabelWidget_1;

// screen lifecycle functions
// DO NOT CALL THESE DIRECTLY
leResult screenInit_leftPowerMissingScreen(void); // called when Legato is initialized
leResult screenShow_leftPowerMissingScreen(void); // called when screen is shown
void screenHide_leftPowerMissingScreen(void); // called when screen is hidden
void screenDestroy_leftPowerMissingScreen(void); // called when Legato is destroyed
void screenUpdate_leftPowerMissingScreen(void); // called when Legato is updating

leWidget* screenGetRoot_leftPowerMissingScreen(uint32_t lyrIdx); // gets a root widget for this screen

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // LE_GEN_SCREEN_LEFTPOWERMISSINGSCREEN_H
