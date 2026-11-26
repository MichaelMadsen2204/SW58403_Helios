#ifndef LE_GEN_SCREEN_DISPLAYINTENSITYSCREEN_H
#define LE_GEN_SCREEN_DISPLAYINTENSITYSCREEN_H

#include "gfx/legato/legato.h"

#include "gfx/legato/generated/le_gen_scheme.h"
#include "gfx/legato/generated/le_gen_assets.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

// screen member widget declarations
extern leWidget* displayIntensityScreen_PanelWidget0;
extern leRectangleWidget* displayIntensityScreen_RectangleWidget0;
extern leRectangleWidget* displayIntensityScreen_RectangleWidget1;
extern leLabelWidget* displayIntensityScreen_dispIntensHeader;
extern leButtonWidget* displayIntensityScreen_disp100Button;
extern leButtonWidget* displayIntensityScreen_disp75Button;
extern leButtonWidget* displayIntensityScreen_disp50Button;
extern leButtonWidget* displayIntensityScreen_disp25Button;
extern leButtonWidget* displayIntensityScreen_dispDimButton;
extern leButtonWidget* displayIntensityScreen_dispOffButton;
extern leLabelWidget* displayIntensityScreen_LabelWidget0;
extern leLabelWidget* displayIntensityScreen_LabelWidget1;
extern leButtonWidget* displayIntensityScreen_simpleViewOnButton;
extern leButtonWidget* displayIntensityScreen_simpViewOffButton;
extern leImageWidget* displayIntensityScreen_ImageWidget0;
extern leButtonWidget* displayIntensityScreen_dispExitButton;

// event handlers
// !!THESE MUST BE IMPLEMENTED IN THE APPLICATION CODE!!
void event_displayIntensityScreen_disp100Button_OnPressed(leButtonWidget* btn);
void event_displayIntensityScreen_disp75Button_OnPressed(leButtonWidget* btn);
void event_displayIntensityScreen_disp50Button_OnPressed(leButtonWidget* btn);
void event_displayIntensityScreen_disp25Button_OnPressed(leButtonWidget* btn);
void event_displayIntensityScreen_dispDimButton_OnPressed(leButtonWidget* btn);
void event_displayIntensityScreen_dispOffButton_OnPressed(leButtonWidget* btn);
void event_displayIntensityScreen_simpleViewOnButton_OnPressed(leButtonWidget* btn);
void event_displayIntensityScreen_simpViewOffButton_OnPressed(leButtonWidget* btn);
void event_displayIntensityScreen_dispExitButton_OnPressed(leButtonWidget* btn);

// screen lifecycle functions
// DO NOT CALL THESE DIRECTLY
leResult screenInit_displayIntensityScreen(void); // called when Legato is initialized
leResult screenShow_displayIntensityScreen(void); // called when screen is shown
void screenHide_displayIntensityScreen(void); // called when screen is hidden
void screenDestroy_displayIntensityScreen(void); // called when Legato is destroyed
void screenUpdate_displayIntensityScreen(void); // called when Legato is updating

leWidget* screenGetRoot_displayIntensityScreen(uint32_t lyrIdx); // gets a root widget for this screen

// Screen Events:
void displayIntensityScreen_OnShow(void); // called when this screen is shown
void displayIntensityScreen_OnHide(void); // called when this screen is hidden

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // LE_GEN_SCREEN_DISPLAYINTENSITYSCREEN_H
