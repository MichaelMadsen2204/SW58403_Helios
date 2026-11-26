#ifndef LE_GEN_SCREEN_GREENBIASSCREEN_H
#define LE_GEN_SCREEN_GREENBIASSCREEN_H

#include "gfx/legato/legato.h"

#include "gfx/legato/generated/le_gen_scheme.h"
#include "gfx/legato/generated/le_gen_assets.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

// screen member widget declarations
extern leWidget* greenBiasScreen_background;
extern leLabelWidget* greenBiasScreen_Instruction;
extern leLabelWidget* greenBiasScreen_Setting1M;
extern leLabelWidget* greenBiasScreen_Setting1H;
extern leLabelWidget* greenBiasScreen_Setting2M;
extern leLabelWidget* greenBiasScreen_Setting2H;
extern leRectangleWidget* greenBiasScreen_irSourceLineLeft;
extern leRectangleWidget* greenBiasScreen_irSourceLineRight;
extern leLabelWidget* greenBiasScreen_greenBiasHeader;
extern leImageWidget* greenBiasScreen_irSourceBackToMenuButImg;
extern leButtonWidget* greenBiasScreen_BIAS_SETTING1;
extern leButtonWidget* greenBiasScreen_BIAS_SETTING2;
extern leButtonWidget* greenBiasScreen_GreenBiasBackToMenuBut;

// event handlers
// !!THESE MUST BE IMPLEMENTED IN THE APPLICATION CODE!!
void event_greenBiasScreen_BIAS_SETTING1_OnPressed(leButtonWidget* btn);
void event_greenBiasScreen_BIAS_SETTING2_OnPressed(leButtonWidget* btn);
void event_greenBiasScreen_GreenBiasBackToMenuBut_OnPressed(leButtonWidget* btn);

// screen lifecycle functions
// DO NOT CALL THESE DIRECTLY
leResult screenInit_greenBiasScreen(void); // called when Legato is initialized
leResult screenShow_greenBiasScreen(void); // called when screen is shown
void screenHide_greenBiasScreen(void); // called when screen is hidden
void screenDestroy_greenBiasScreen(void); // called when Legato is destroyed
void screenUpdate_greenBiasScreen(void); // called when Legato is updating

leWidget* screenGetRoot_greenBiasScreen(uint32_t lyrIdx); // gets a root widget for this screen

// Screen Events:
void greenBiasScreen_OnShow(void); // called when this screen is shown

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // LE_GEN_SCREEN_GREENBIASSCREEN_H
