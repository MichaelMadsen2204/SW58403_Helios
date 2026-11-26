#ifndef LE_GEN_SCREEN_PICKUPSELECTSCREEN_H
#define LE_GEN_SCREEN_PICKUPSELECTSCREEN_H

#include "gfx/legato/legato.h"

#include "gfx/legato/generated/le_gen_scheme.h"
#include "gfx/legato/generated/le_gen_assets.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

// screen member widget declarations
extern leWidget* pickupSelectScreen_background;
extern leWidget* pickupSelectScreen_stabilizingPanel;
extern leRectangleWidget* pickupSelectScreen_pickupSelLineLeft;
extern leRectangleWidget* pickupSelectScreen_pickupSelLineRight;
extern leLabelWidget* pickupSelectScreen_pickupSelectHeader;
extern leImageWidget* pickupSelectScreen_irSourceBackToMenuButImg;
extern leButtonWidget* pickupSelectScreen_pickupMMBut;
extern leButtonWidget* pickupSelectScreen_pickupMCBut;
extern leButtonWidget* pickupSelectScreen_pickupSelBackToMenuBut;
extern leRectangleWidget* pickupSelectScreen_RectangleWidget_0;
extern leProgressBarWidget* pickupSelectScreen_ProgressBar;
extern leLabelWidget* pickupSelectScreen_LabelWidget_0;
extern leLabelWidget* pickupSelectScreen_LabelWidget_1;

// event handlers
// !!THESE MUST BE IMPLEMENTED IN THE APPLICATION CODE!!
void event_pickupSelectScreen_pickupMMBut_OnPressed(leButtonWidget* btn);
void event_pickupSelectScreen_pickupMCBut_OnPressed(leButtonWidget* btn);
void event_pickupSelectScreen_pickupSelBackToMenuBut_OnPressed(leButtonWidget* btn);

// screen lifecycle functions
// DO NOT CALL THESE DIRECTLY
leResult screenInit_pickupSelectScreen(void); // called when Legato is initialized
leResult screenShow_pickupSelectScreen(void); // called when screen is shown
void screenHide_pickupSelectScreen(void); // called when screen is hidden
void screenDestroy_pickupSelectScreen(void); // called when Legato is destroyed
void screenUpdate_pickupSelectScreen(void); // called when Legato is updating

leWidget* screenGetRoot_pickupSelectScreen(uint32_t lyrIdx); // gets a root widget for this screen

// Screen Events:
void pickupSelectScreen_OnShow(void); // called when this screen is shown

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // LE_GEN_SCREEN_PICKUPSELECTSCREEN_H
