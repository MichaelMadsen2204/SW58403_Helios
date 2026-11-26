#ifndef LE_GEN_SCREEN_INPLVLMATCHSCREEN_H
#define LE_GEN_SCREEN_INPLVLMATCHSCREEN_H

#include "gfx/legato/legato.h"

#include "gfx/legato/generated/le_gen_scheme.h"
#include "gfx/legato/generated/le_gen_assets.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

// screen member widget declarations
extern leWidget* inpLvlMatchScreen_background;
extern leButtonWidget* inpLvlMatchScreen_inpBut_1;
extern leButtonWidget* inpLvlMatchScreen_inpBut_2;
extern leButtonWidget* inpLvlMatchScreen_inpBut_3;
extern leButtonWidget* inpLvlMatchScreen_inpBut_4;
extern leButtonWidget* inpLvlMatchScreen_inpBut_5;
extern leButtonWidget* inpLvlMatchScreen_inpBut_6;
extern leLabelWidget* inpLvlMatchScreen_inpLvlMatchValue_1;
extern leLabelWidget* inpLvlMatchScreen_inpLvlMatchValue_2;
extern leLabelWidget* inpLvlMatchScreen_inpLvlMatchValue_3;
extern leLabelWidget* inpLvlMatchScreen_inpLvlMatchValue_4;
extern leLabelWidget* inpLvlMatchScreen_inpLvlMatchValue_5;
extern leLabelWidget* inpLvlMatchScreen_inpLvlMatchValue_6;
extern leImageWidget* inpLvlMatchScreen_maxVolButImg;
extern leImageWidget* inpLvlMatchScreen_inpSenseBackToMenuImg;
extern leLabelWidget* inpLvlMatchScreen_inpSenseMenuHeader;
extern leRectangleWidget* inpLvlMatchScreen_inPSenseLineRightSide;
extern leRectangleWidget* inpLvlMatchScreen_inpSenseLineLeftSide;
extern leButtonWidget* inpLvlMatchScreen_inpLvlMatchPlusBut;
extern leButtonWidget* inpLvlMatchScreen_inpLvlMatchMinusBut;
extern leButtonWidget* inpLvlMatchScreen_inpSenseBackToMenuBut;

// event handlers
// !!THESE MUST BE IMPLEMENTED IN THE APPLICATION CODE!!
void event_inpLvlMatchScreen_inpBut_1_OnPressed(leButtonWidget* btn);
void event_inpLvlMatchScreen_inpBut_2_OnPressed(leButtonWidget* btn);
void event_inpLvlMatchScreen_inpBut_3_OnPressed(leButtonWidget* btn);
void event_inpLvlMatchScreen_inpBut_4_OnPressed(leButtonWidget* btn);
void event_inpLvlMatchScreen_inpBut_5_OnPressed(leButtonWidget* btn);
void event_inpLvlMatchScreen_inpBut_6_OnPressed(leButtonWidget* btn);
void event_inpLvlMatchScreen_inpLvlMatchPlusBut_OnPressed(leButtonWidget* btn);
void event_inpLvlMatchScreen_inpLvlMatchPlusBut_OnReleased(leButtonWidget* btn);
void event_inpLvlMatchScreen_inpLvlMatchMinusBut_OnPressed(leButtonWidget* btn);
void event_inpLvlMatchScreen_inpLvlMatchMinusBut_OnReleased(leButtonWidget* btn);
void event_inpLvlMatchScreen_inpSenseBackToMenuBut_OnPressed(leButtonWidget* btn);

// screen lifecycle functions
// DO NOT CALL THESE DIRECTLY
leResult screenInit_inpLvlMatchScreen(void); // called when Legato is initialized
leResult screenShow_inpLvlMatchScreen(void); // called when screen is shown
void screenHide_inpLvlMatchScreen(void); // called when screen is hidden
void screenDestroy_inpLvlMatchScreen(void); // called when Legato is destroyed
void screenUpdate_inpLvlMatchScreen(void); // called when Legato is updating

leWidget* screenGetRoot_inpLvlMatchScreen(uint32_t lyrIdx); // gets a root widget for this screen

// Screen Events:
void inpLvlMatchScreen_OnShow(void); // called when this screen is shown
void inpLvlMatchScreen_OnHide(void); // called when this screen is hidden

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // LE_GEN_SCREEN_INPLVLMATCHSCREEN_H
