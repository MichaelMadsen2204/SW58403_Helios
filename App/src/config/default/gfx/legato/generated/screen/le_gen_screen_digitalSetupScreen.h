#ifndef LE_GEN_SCREEN_DIGITALSETUPSCREEN_H
#define LE_GEN_SCREEN_DIGITALSETUPSCREEN_H

#include "gfx/legato/legato.h"

#include "gfx/legato/generated/le_gen_scheme.h"
#include "gfx/legato/generated/le_gen_assets.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

// screen member widget declarations
extern leWidget* digitalSetupScreen_digitalBackground;
extern leImageWidget* digitalSetupScreen_dsdFilterImg;
extern leImageWidget* digitalSetupScreen_pcmFilterImg;
extern leRectangleWidget* digitalSetupScreen_digitalSetHeaderLineRight;
extern leRectangleWidget* digitalSetupScreen_digitaleSetHeaderLineLeft;
extern leLabelWidget* digitalSetupScreen_digitalSetupHeader;
extern leButtonWidget* digitalSetupScreen_dsdLpFilterOnButton;
extern leButtonWidget* digitalSetupScreen_dsdLpFilterOffButton;
extern leButtonWidget* digitalSetupScreen_digitalGain0dBButton;
extern leButtonWidget* digitalSetupScreen_digitalGainMinus6dBButton;
extern leLabelWidget* digitalSetupScreen_dsdLpFilterHeader1;
extern leLabelWidget* digitalSetupScreen_LabelWidget1;
extern leImageWidget* digitalSetupScreen_digitaBackToMenuButtonImg;
extern leLabelWidget* digitalSetupScreen_filterNameLine1;
extern leLabelWidget* digitalSetupScreen_filterNameLine2;
extern leLabelWidget* digitalSetupScreen_dsdLpHeader2;
extern leLabelWidget* digitalSetupScreen_dsdLabel;
extern leLabelWidget* digitalSetupScreen_dsdFilterLabel;
extern leLabelWidget* digitalSetupScreen_curDsdFilterLabel;
extern leButtonWidget* digitalSetupScreen_dsdFilterUpButton;
extern leButtonWidget* digitalSetupScreen_dsdFilterDwnButton;
extern leLabelWidget* digitalSetupScreen_pcmLabel;
extern leLabelWidget* digitalSetupScreen_pcmFilterLabel;
extern leLabelWidget* digitalSetupScreen_curPcmFilterLabel;
extern leButtonWidget* digitalSetupScreen_pcmFilterUpButton;
extern leButtonWidget* digitalSetupScreen_pcmFilterDwnButton;
extern leButtonWidget* digitalSetupScreen_digitaBackToMenuButton;

// event handlers
// !!THESE MUST BE IMPLEMENTED IN THE APPLICATION CODE!!
void event_digitalSetupScreen_dsdLpFilterOnButton_OnPressed(leButtonWidget* btn);
void event_digitalSetupScreen_dsdLpFilterOffButton_OnPressed(leButtonWidget* btn);
void event_digitalSetupScreen_digitalGain0dBButton_OnPressed(leButtonWidget* btn);
void event_digitalSetupScreen_digitalGainMinus6dBButton_OnPressed(leButtonWidget* btn);
void event_digitalSetupScreen_dsdFilterUpButton_OnPressed(leButtonWidget* btn);
void event_digitalSetupScreen_dsdFilterDwnButton_OnPressed(leButtonWidget* btn);
void event_digitalSetupScreen_pcmFilterUpButton_OnPressed(leButtonWidget* btn);
void event_digitalSetupScreen_pcmFilterDwnButton_OnPressed(leButtonWidget* btn);
void event_digitalSetupScreen_digitaBackToMenuButton_OnPressed(leButtonWidget* btn);

// screen lifecycle functions
// DO NOT CALL THESE DIRECTLY
leResult screenInit_digitalSetupScreen(void); // called when Legato is initialized
leResult screenShow_digitalSetupScreen(void); // called when screen is shown
void screenHide_digitalSetupScreen(void); // called when screen is hidden
void screenDestroy_digitalSetupScreen(void); // called when Legato is destroyed
void screenUpdate_digitalSetupScreen(void); // called when Legato is updating

leWidget* screenGetRoot_digitalSetupScreen(uint32_t lyrIdx); // gets a root widget for this screen

// Screen Events:
void digitalSetupScreen_OnShow(void); // called when this screen is shown

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // LE_GEN_SCREEN_DIGITALSETUPSCREEN_H
