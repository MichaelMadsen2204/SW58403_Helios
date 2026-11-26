#ifndef LE_GEN_SCREEN_RENAMEINPUTSSCREEN_H
#define LE_GEN_SCREEN_RENAMEINPUTSSCREEN_H

#include "gfx/legato/legato.h"

#include "gfx/legato/generated/le_gen_scheme.h"
#include "gfx/legato/generated/le_gen_assets.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

// screen member widget declarations
extern leWidget* renameInputsScreen_Background;
extern leWidget* renameInputsScreen_digitalInputs;
extern leButtonWidget* renameInputsScreen_BackToMenuButttonWdgt;
extern leButtonWidget* renameInputsScreen_renameButtonWdgt;
extern leRectangleWidget* renameInputsScreen_RectangleWidget0;
extern leRectangleWidget* renameInputsScreen_RectangleWidget1;
extern leLabelWidget* renameInputsScreen_LabelWidget2;
extern leWidget* renameInputsScreen_analogInputs;
extern leLabelWidget* renameInputsScreen_LabelWidget1;
extern leButtonWidget* renameInputsScreen_selInp7ButWdgt;
extern leButtonWidget* renameInputsScreen_selInp8ButWdgt;
extern leButtonWidget* renameInputsScreen_selInp9ButWdgt;
extern leButtonWidget* renameInputsScreen_selInp10ButWdgt;
extern leButtonWidget* renameInputsScreen_selInp11ButWdgt;
extern leButtonWidget* renameInputsScreen_selInp1ButWdgt;
extern leButtonWidget* renameInputsScreen_selInp2ButWdgt;
extern leButtonWidget* renameInputsScreen_selInp3ButWdgt;
extern leButtonWidget* renameInputsScreen_selInp4ButWdgt;
extern leButtonWidget* renameInputsScreen_selInp5ButWdgt;
extern leLabelWidget* renameInputsScreen_LabelWidget0;
extern leButtonWidget* renameInputsScreen_selInp6ButWdgt;

// event handlers
// !!THESE MUST BE IMPLEMENTED IN THE APPLICATION CODE!!
void event_renameInputsScreen_BackToMenuButttonWdgt_OnReleased(leButtonWidget* btn);
void event_renameInputsScreen_renameButtonWdgt_OnPressed(leButtonWidget* btn);
void event_renameInputsScreen_selInp7ButWdgt_OnPressed(leButtonWidget* btn);
void event_renameInputsScreen_selInp8ButWdgt_OnPressed(leButtonWidget* btn);
void event_renameInputsScreen_selInp9ButWdgt_OnPressed(leButtonWidget* btn);
void event_renameInputsScreen_selInp10ButWdgt_OnPressed(leButtonWidget* btn);
void event_renameInputsScreen_selInp11ButWdgt_OnPressed(leButtonWidget* btn);
void event_renameInputsScreen_selInp1ButWdgt_OnPressed(leButtonWidget* btn);
void event_renameInputsScreen_selInp2ButWdgt_OnPressed(leButtonWidget* btn);
void event_renameInputsScreen_selInp3ButWdgt_OnPressed(leButtonWidget* btn);
void event_renameInputsScreen_selInp4ButWdgt_OnPressed(leButtonWidget* btn);
void event_renameInputsScreen_selInp5ButWdgt_OnPressed(leButtonWidget* btn);
void event_renameInputsScreen_selInp6ButWdgt_OnPressed(leButtonWidget* btn);

// screen lifecycle functions
// DO NOT CALL THESE DIRECTLY
leResult screenInit_renameInputsScreen(void); // called when Legato is initialized
leResult screenShow_renameInputsScreen(void); // called when screen is shown
void screenHide_renameInputsScreen(void); // called when screen is hidden
void screenDestroy_renameInputsScreen(void); // called when Legato is destroyed
void screenUpdate_renameInputsScreen(void); // called when Legato is updating

leWidget* screenGetRoot_renameInputsScreen(uint32_t lyrIdx); // gets a root widget for this screen

// Screen Events:
void renameInputsScreen_OnShow(void); // called when this screen is shown
void renameInputsScreen_OnHide(void); // called when this screen is hidden

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // LE_GEN_SCREEN_RENAMEINPUTSSCREEN_H
