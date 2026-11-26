#ifndef LE_GEN_SCREEN_AVINPUTSCREEN_H
#define LE_GEN_SCREEN_AVINPUTSCREEN_H

#include "gfx/legato/legato.h"

#include "gfx/legato/generated/le_gen_scheme.h"
#include "gfx/legato/generated/le_gen_assets.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

// screen member widget declarations
extern leWidget* avInputScreen_PanelWidget0;
extern leRectangleWidget* avInputScreen_RectangleWidget0;
extern leRectangleWidget* avInputScreen_RectangleWidget1;
extern leLabelWidget* avInputScreen_avInpHeader;
extern leLabelWidget* avInputScreen_LabelWidget0;
extern leLabelWidget* avInputScreen_LabelWidget1;
extern leLabelWidget* avInputScreen_LabelWidget2;
extern leLabelWidget* avInputScreen_LabelWidget3;
extern leButtonWidget* avInputScreen_inp3Button;
extern leButtonWidget* avInputScreen_inp4Button;
extern leButtonWidget* avInputScreen_noneButton;
extern leLabelWidget* avInputScreen_LabelWidget4;
extern leLabelWidget* avInputScreen_LabelWidget5;
extern leLabelWidget* avInputScreen_LabelWidget6;
extern leLabelWidget* avInputScreen_LabelWidget7;
extern leLabelWidget* avInputScreen_LabelWidget8;
extern leImageWidget* avInputScreen_ImageWidget0;
extern leButtonWidget* avInputScreen_menuExitButton;

// event handlers
// !!THESE MUST BE IMPLEMENTED IN THE APPLICATION CODE!!
void event_avInputScreen_inp3Button_OnPressed(leButtonWidget* btn);
void event_avInputScreen_inp3Button_OnReleased(leButtonWidget* btn);
void event_avInputScreen_inp4Button_OnPressed(leButtonWidget* btn);
void event_avInputScreen_inp4Button_OnReleased(leButtonWidget* btn);
void event_avInputScreen_noneButton_OnPressed(leButtonWidget* btn);
void event_avInputScreen_menuExitButton_OnPressed(leButtonWidget* btn);

// screen lifecycle functions
// DO NOT CALL THESE DIRECTLY
leResult screenInit_avInputScreen(void); // called when Legato is initialized
leResult screenShow_avInputScreen(void); // called when screen is shown
void screenHide_avInputScreen(void); // called when screen is hidden
void screenDestroy_avInputScreen(void); // called when Legato is destroyed
void screenUpdate_avInputScreen(void); // called when Legato is updating

leWidget* screenGetRoot_avInputScreen(uint32_t lyrIdx); // gets a root widget for this screen

// Screen Events:
void avInputScreen_OnShow(void); // called when this screen is shown
void avInputScreen_OnHide(void); // called when this screen is hidden

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // LE_GEN_SCREEN_AVINPUTSCREEN_H
