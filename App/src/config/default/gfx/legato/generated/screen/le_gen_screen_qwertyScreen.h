#ifndef LE_GEN_SCREEN_QWERTYSCREEN_H
#define LE_GEN_SCREEN_QWERTYSCREEN_H

#include "gfx/legato/legato.h"

#include "gfx/legato/generated/le_gen_scheme.h"
#include "gfx/legato/generated/le_gen_assets.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

// screen member widget declarations
extern leWidget* qwertyScreen_BackGround;
extern leLabelWidget* qwertyScreen_LabelWidget0;
extern leLabelWidget* qwertyScreen_LabelWidget1;
extern leTextFieldWidget* qwertyScreen_TextFieldWidget0;
extern leButtonWidget* qwertyScreen_okButtonWidget;
extern leButtonWidget* qwertyScreen_spaceButtonWidget;
extern leButtonWidget* qwertyScreen_numAlphaBut;
extern leWidget* qwertyScreen_keypadPanel;
extern leKeyPadWidget* qwertyScreen_KeyPadAlpaNum;

// event handlers
// !!THESE MUST BE IMPLEMENTED IN THE APPLICATION CODE!!
void event_qwertyScreen_TextFieldWidget0_OnTextChanged(leTextFieldWidget* btn);
void event_qwertyScreen_okButtonWidget_OnReleased(leButtonWidget* btn);
void event_qwertyScreen_spaceButtonWidget_OnReleased(leButtonWidget* btn);
void event_qwertyScreen_numAlphaBut_OnPressed(leButtonWidget* btn);
void event_qwertyScreen_numAlphaBut_OnReleased(leButtonWidget* btn);
void event_qwertyScreen_KeyPadAlpaNum_OnKeyClick(leKeyPadWidget* wgt, leButtonWidget* cell, uint32_t row, uint32_t col);

// screen lifecycle functions
// DO NOT CALL THESE DIRECTLY
leResult screenInit_qwertyScreen(void); // called when Legato is initialized
leResult screenShow_qwertyScreen(void); // called when screen is shown
void screenHide_qwertyScreen(void); // called when screen is hidden
void screenDestroy_qwertyScreen(void); // called when Legato is destroyed
void screenUpdate_qwertyScreen(void); // called when Legato is updating

leWidget* screenGetRoot_qwertyScreen(uint32_t lyrIdx); // gets a root widget for this screen

// Screen Events:
void qwertyScreen_OnShow(void); // called when this screen is shown
void qwertyScreen_OnHide(void); // called when this screen is hidden

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // LE_GEN_SCREEN_QWERTYSCREEN_H
