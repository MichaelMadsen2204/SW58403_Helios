#ifndef LE_GEN_SCREEN_IRSOURCESCREEN_H
#define LE_GEN_SCREEN_IRSOURCESCREEN_H

#include "gfx/legato/legato.h"

#include "gfx/legato/generated/le_gen_scheme.h"
#include "gfx/legato/generated/le_gen_assets.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

// screen member widget declarations
extern leWidget* irSourceScreen_background;
extern leRectangleWidget* irSourceScreen_irSourceLineLeft;
extern leRectangleWidget* irSourceScreen_irSourceLineRight;
extern leLabelWidget* irSourceScreen_irSourceHeader;
extern leImageWidget* irSourceScreen_irSourceBackToMenuButImg;
extern leButtonWidget* irSourceScreen_irSourceFrontBut;
extern leButtonWidget* irSourceScreen_irSourceBackBut;
extern leButtonWidget* irSourceScreen_irSourceBackToMenuBut;

// event handlers
// !!THESE MUST BE IMPLEMENTED IN THE APPLICATION CODE!!
void event_irSourceScreen_irSourceFrontBut_OnPressed(leButtonWidget* btn);
void event_irSourceScreen_irSourceBackBut_OnPressed(leButtonWidget* btn);
void event_irSourceScreen_irSourceBackToMenuBut_OnPressed(leButtonWidget* btn);

// screen lifecycle functions
// DO NOT CALL THESE DIRECTLY
leResult screenInit_irSourceScreen(void); // called when Legato is initialized
leResult screenShow_irSourceScreen(void); // called when screen is shown
void screenHide_irSourceScreen(void); // called when screen is hidden
void screenDestroy_irSourceScreen(void); // called when Legato is destroyed
void screenUpdate_irSourceScreen(void); // called when Legato is updating

leWidget* screenGetRoot_irSourceScreen(uint32_t lyrIdx); // gets a root widget for this screen

// Screen Events:
void irSourceScreen_OnShow(void); // called when this screen is shown

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // LE_GEN_SCREEN_IRSOURCESCREEN_H
