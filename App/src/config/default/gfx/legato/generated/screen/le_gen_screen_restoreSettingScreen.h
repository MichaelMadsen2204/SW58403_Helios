#ifndef LE_GEN_SCREEN_RESTORESETTINGSCREEN_H
#define LE_GEN_SCREEN_RESTORESETTINGSCREEN_H

#include "gfx/legato/legato.h"

#include "gfx/legato/generated/le_gen_scheme.h"
#include "gfx/legato/generated/le_gen_assets.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

// screen member widget declarations
extern leWidget* restoreSettingScreen_PanelWidget0;
extern leRectangleWidget* restoreSettingScreen_RectangleWidget0;
extern leRectangleWidget* restoreSettingScreen_RectangleWidget1;
extern leLabelWidget* restoreSettingScreen_LabelWidget0;
extern leLabelWidget* restoreSettingScreen_LabelWidget1;
extern leLabelWidget* restoreSettingScreen_LabelWidget2;
extern leLabelWidget* restoreSettingScreen_LabelWidget3;
extern leLabelWidget* restoreSettingScreen_LabelWidget4;
extern leLabelWidget* restoreSettingScreen_LabelWidget5;
extern leButtonWidget* restoreSettingScreen_ResContiniueYesButton;
extern leButtonWidget* restoreSettingScreen_ResContiniueNoButton;
extern leWidget* restoreSettingScreen_splashResSetSure;
extern leWidget* restoreSettingScreen_settingsRestoredPanel;
extern leLabelWidget* restoreSettingScreen_fwLabel;
extern leRectangleWidget* restoreSettingScreen_RectangleWidget2;
extern leButtonWidget* restoreSettingScreen_yesButton;
extern leButtonWidget* restoreSettingScreen_cancelButton;
extern leLabelWidget* restoreSettingScreen_LabelWidget6;
extern leLabelWidget* restoreSettingScreen_LabelWidget7;
extern leRectangleWidget* restoreSettingScreen_RectangleWidget3;
extern leLabelWidget* restoreSettingScreen_LabelWidget8;
extern leLabelWidget* restoreSettingScreen_LabelWidget9;
extern leButtonWidget* restoreSettingScreen_backAfterRestoreBut;

// event handlers
// !!THESE MUST BE IMPLEMENTED IN THE APPLICATION CODE!!
void event_restoreSettingScreen_ResContiniueYesButton_OnPressed(leButtonWidget* btn);
void event_restoreSettingScreen_ResContiniueNoButton_OnPressed(leButtonWidget* btn);
void event_restoreSettingScreen_yesButton_OnPressed(leButtonWidget* btn);
void event_restoreSettingScreen_cancelButton_OnPressed(leButtonWidget* btn);
void event_restoreSettingScreen_backAfterRestoreBut_OnPressed(leButtonWidget* btn);

// screen lifecycle functions
// DO NOT CALL THESE DIRECTLY
leResult screenInit_restoreSettingScreen(void); // called when Legato is initialized
leResult screenShow_restoreSettingScreen(void); // called when screen is shown
void screenHide_restoreSettingScreen(void); // called when screen is hidden
void screenDestroy_restoreSettingScreen(void); // called when Legato is destroyed
void screenUpdate_restoreSettingScreen(void); // called when Legato is updating

leWidget* screenGetRoot_restoreSettingScreen(uint32_t lyrIdx); // gets a root widget for this screen

// Screen Events:
void restoreSettingScreen_OnShow(void); // called when this screen is shown

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // LE_GEN_SCREEN_RESTORESETTINGSCREEN_H
