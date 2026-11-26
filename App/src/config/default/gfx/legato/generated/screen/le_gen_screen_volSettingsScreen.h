#ifndef LE_GEN_SCREEN_VOLSETTINGSSCREEN_H
#define LE_GEN_SCREEN_VOLSETTINGSSCREEN_H

#include "gfx/legato/legato.h"

#include "gfx/legato/generated/le_gen_scheme.h"
#include "gfx/legato/generated/le_gen_assets.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

// screen member widget declarations
extern leWidget* volSettingsScreen_background;
extern leImageWidget* volSettingsScreen_BalanceImg;
extern leImageWidget* volSettingsScreen_startVolButImg;
extern leImageWidget* volSettingsScreen_maxVolButImg;
extern leImageWidget* volSettingsScreen_volBackToMenuImg;
extern leLabelWidget* volSettingsScreen_volSettingMenuHeader;
extern leRectangleWidget* volSettingsScreen_volSettingLineRightSide;
extern leRectangleWidget* volSettingsScreen_volSettingLineLeftSide;
extern leLabelWidget* volSettingsScreen_startVolLabel;
extern leLabelWidget* volSettingsScreen_VolStartLabel;
extern leLabelWidget* volSettingsScreen_volSettingCurStartLevelLabel;
extern leButtonWidget* volSettingsScreen_volSetStartVolPlusBut;
extern leButtonWidget* volSettingsScreen_volSetStartVolMinusBut;
extern leLabelWidget* volSettingsScreen_maxVolLabel;
extern leLabelWidget* volSettingsScreen_volMaxLabel;
extern leLabelWidget* volSettingsScreen_volSettingCurMaxLevelLabel;
extern leButtonWidget* volSettingsScreen_volSetMaxVolPlusBut;
extern leButtonWidget* volSettingsScreen_volSetMaxVolMinusBut;
extern leButtonWidget* volSettingsScreen_volSetBackToMenuBut;
extern leTextFieldWidget* volSettingsScreen_balance;
extern leTextFieldWidget* volSettingsScreen_balanceHeader;
extern leButtonWidget* volSettingsScreen_balanceLeftBut;
extern leButtonWidget* volSettingsScreen_balanceRightBut;

// event handlers
// !!THESE MUST BE IMPLEMENTED IN THE APPLICATION CODE!!
void event_volSettingsScreen_volSetStartVolPlusBut_OnPressed(leButtonWidget* btn);
void event_volSettingsScreen_volSetStartVolPlusBut_OnReleased(leButtonWidget* btn);
void event_volSettingsScreen_volSetStartVolMinusBut_OnPressed(leButtonWidget* btn);
void event_volSettingsScreen_volSetStartVolMinusBut_OnReleased(leButtonWidget* btn);
void event_volSettingsScreen_volSetMaxVolPlusBut_OnPressed(leButtonWidget* btn);
void event_volSettingsScreen_volSetMaxVolPlusBut_OnReleased(leButtonWidget* btn);
void event_volSettingsScreen_volSetMaxVolMinusBut_OnPressed(leButtonWidget* btn);
void event_volSettingsScreen_volSetMaxVolMinusBut_OnReleased(leButtonWidget* btn);
void event_volSettingsScreen_volSetBackToMenuBut_OnPressed(leButtonWidget* btn);
void event_volSettingsScreen_balanceLeftBut_OnPressed(leButtonWidget* btn);
void event_volSettingsScreen_balanceLeftBut_OnReleased(leButtonWidget* btn);
void event_volSettingsScreen_balanceRightBut_OnPressed(leButtonWidget* btn);
void event_volSettingsScreen_balanceRightBut_OnReleased(leButtonWidget* btn);

// screen lifecycle functions
// DO NOT CALL THESE DIRECTLY
leResult screenInit_volSettingsScreen(void); // called when Legato is initialized
leResult screenShow_volSettingsScreen(void); // called when screen is shown
void screenHide_volSettingsScreen(void); // called when screen is hidden
void screenDestroy_volSettingsScreen(void); // called when Legato is destroyed
void screenUpdate_volSettingsScreen(void); // called when Legato is updating

leWidget* screenGetRoot_volSettingsScreen(uint32_t lyrIdx); // gets a root widget for this screen

// Screen Events:
void volSettingsScreen_OnShow(void); // called when this screen is shown
void volSettingsScreen_OnHide(void); // called when this screen is hidden

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // LE_GEN_SCREEN_VOLSETTINGSSCREEN_H
