#ifndef LE_GEN_SCREEN_MAINMENUSCREEN_H
#define LE_GEN_SCREEN_MAINMENUSCREEN_H

#include "gfx/legato/legato.h"

#include "gfx/legato/generated/le_gen_scheme.h"
#include "gfx/legato/generated/le_gen_assets.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

// screen member widget declarations
extern leWidget* mainMenuScreen_BackgroundPanel;
extern leWidget* mainMenuScreen_fanErrorPanel;
extern leButtonWidget* mainMenuScreen_menuExitBut;
extern leButtonWidget* mainMenuScreen_menuVolBut;
extern leButtonWidget* mainMenuScreen_menuDisplayBut;
extern leButtonWidget* mainMenuScreen_menuIrSrcBut;
extern leButtonWidget* mainMenuScreen_menuDigitalBut;
extern leButtonWidget* mainMenuScreen_menuInpLevMatchBut;
extern leButtonWidget* mainMenuScreen_menuNameInpBut;
extern leButtonWidget* mainMenuScreen_menuAvInpBut;
extern leButtonWidget* mainMenuScreen_menuRestSetBut;
extern leButtonWidget* mainMenuScreen_menuRiaaBut;
extern leButtonWidget* mainMenuScreen_menuBiasBut;
extern leLabelWidget* mainMenuScreen_mainMenuHeader;
extern leRectangleWidget* mainMenuScreen_menuLineRightSide;
extern leRectangleWidget* mainMenuScreen_menuLineLeftSide;
extern leImageWidget* mainMenuScreen_ImageWidget_0;
extern leTextFieldWidget* mainMenuScreen_TextFieldWidget_0;
extern leTextFieldWidget* mainMenuScreen_TextFieldWidget_1;
extern leTextFieldWidget* mainMenuScreen_TextFieldWidget_2;
extern leRectangleWidget* mainMenuScreen_RectangleWidget_0;
extern leButtonWidget* mainMenuScreen_cancelButton;

// event handlers
// !!THESE MUST BE IMPLEMENTED IN THE APPLICATION CODE!!
void event_mainMenuScreen_menuExitBut_OnPressed(leButtonWidget* btn);
void event_mainMenuScreen_menuVolBut_OnPressed(leButtonWidget* btn);
void event_mainMenuScreen_menuDisplayBut_OnPressed(leButtonWidget* btn);
void event_mainMenuScreen_menuIrSrcBut_OnPressed(leButtonWidget* btn);
void event_mainMenuScreen_menuDigitalBut_OnPressed(leButtonWidget* btn);
void event_mainMenuScreen_menuInpLevMatchBut_OnPressed(leButtonWidget* btn);
void event_mainMenuScreen_menuNameInpBut_OnPressed(leButtonWidget* btn);
void event_mainMenuScreen_menuAvInpBut_OnPressed(leButtonWidget* btn);
void event_mainMenuScreen_menuRestSetBut_OnPressed(leButtonWidget* btn);
void event_mainMenuScreen_menuRiaaBut_OnPressed(leButtonWidget* btn);
void event_mainMenuScreen_menuBiasBut_OnPressed(leButtonWidget* btn);
void event_mainMenuScreen_cancelButton_OnPressed(leButtonWidget* btn);

// screen lifecycle functions
// DO NOT CALL THESE DIRECTLY
leResult screenInit_mainMenuScreen(void); // called when Legato is initialized
leResult screenShow_mainMenuScreen(void); // called when screen is shown
void screenHide_mainMenuScreen(void); // called when screen is hidden
void screenDestroy_mainMenuScreen(void); // called when Legato is destroyed
void screenUpdate_mainMenuScreen(void); // called when Legato is updating

leWidget* screenGetRoot_mainMenuScreen(uint32_t lyrIdx); // gets a root widget for this screen

// Screen Events:
void mainMenuScreen_OnShow(void); // called when this screen is shown
void mainMenuScreen_OnHide(void); // called when this screen is hidden

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // LE_GEN_SCREEN_MAINMENUSCREEN_H
