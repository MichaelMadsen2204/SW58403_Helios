#ifndef LE_GEN_SCREEN_SIMPLEVIEWSCREEN_H
#define LE_GEN_SCREEN_SIMPLEVIEWSCREEN_H

#include "gfx/legato/legato.h"

#include "gfx/legato/generated/le_gen_scheme.h"
#include "gfx/legato/generated/le_gen_assets.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

// screen member widget declarations
extern leWidget* simpleViewScreen_background;
extern leWidget* simpleViewScreen_batteryPanel;
extern leImageWidget* simpleViewScreen_fanErrorImg;
extern leImageWidget* simpleViewScreen_smpleViewMuteKryds;
extern leLabelWidget* simpleViewScreen_simpleViewVolHeader;
extern leLabelWidget* simpleViewScreen_simpleViewCurLevelLabel;
extern leLabelWidget* simpleViewScreen_avLevLabel;
extern leLabelWidget* simpleViewScreen_smpleViewInputHeaderLabel;
extern leLabelWidget* simpleViewScreen_simpleViewInputNameLabel;
extern leButtonWidget* simpleViewScreen_simpleViewAnyTouchBut;
extern leImageWidget* simpleViewScreen_BattCharged;
extern leImageWidget* simpleViewScreen_BattCharging;

// event handlers
// !!THESE MUST BE IMPLEMENTED IN THE APPLICATION CODE!!
void event_simpleViewScreen_simpleViewAnyTouchBut_OnPressed(leButtonWidget* btn);

// screen lifecycle functions
// DO NOT CALL THESE DIRECTLY
leResult screenInit_simpleViewScreen(void); // called when Legato is initialized
leResult screenShow_simpleViewScreen(void); // called when screen is shown
void screenHide_simpleViewScreen(void); // called when screen is hidden
void screenDestroy_simpleViewScreen(void); // called when Legato is destroyed
void screenUpdate_simpleViewScreen(void); // called when Legato is updating

leWidget* screenGetRoot_simpleViewScreen(uint32_t lyrIdx); // gets a root widget for this screen

// Screen Events:
void simpleViewScreen_OnShow(void); // called when this screen is shown

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // LE_GEN_SCREEN_SIMPLEVIEWSCREEN_H
