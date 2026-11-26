#ifndef LE_GEN_SCREEN_ERRORDISPLAY_H
#define LE_GEN_SCREEN_ERRORDISPLAY_H

#include "gfx/legato/legato.h"

#include "gfx/legato/generated/le_gen_scheme.h"
#include "gfx/legato/generated/le_gen_assets.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

// screen member widget declarations
extern leWidget* errorDisplay_PanelWidget0;
extern leLabelWidget* errorDisplay_LabelWidget0;
extern leLabelWidget* errorDisplay_LabelWidget1;
extern leLabelWidget* errorDisplay_LabelWidget2;
extern leLabelWidget* errorDisplay_LabelWidget3;
extern leLabelWidget* errorDisplay_LabelWidget4;
extern leLabelWidget* errorDisplay_rightTempLed;
extern leLabelWidget* errorDisplay_LabelWidget6;
extern leLabelWidget* errorDisplay_LabelWidget7;
extern leButtonWidget* errorDisplay_leftTempLed;
extern leButtonWidget* errorDisplay_leftDcHfLed;
extern leButtonWidget* errorDisplay_rightTempLed_;
extern leButtonWidget* errorDisplay_rightDcHfLed;
extern leLabelWidget* errorDisplay_LabelWidget8;
extern leLabelWidget* errorDisplay_LabelWidget_0;

// screen lifecycle functions
// DO NOT CALL THESE DIRECTLY
leResult screenInit_errorDisplay(void); // called when Legato is initialized
leResult screenShow_errorDisplay(void); // called when screen is shown
void screenHide_errorDisplay(void); // called when screen is hidden
void screenDestroy_errorDisplay(void); // called when Legato is destroyed
void screenUpdate_errorDisplay(void); // called when Legato is updating

leWidget* screenGetRoot_errorDisplay(uint32_t lyrIdx); // gets a root widget for this screen

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // LE_GEN_SCREEN_ERRORDISPLAY_H
