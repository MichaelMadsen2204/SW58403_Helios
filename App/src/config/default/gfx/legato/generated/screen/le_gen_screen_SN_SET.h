#ifndef LE_GEN_SCREEN_SN_SET_H
#define LE_GEN_SCREEN_SN_SET_H

#include "gfx/legato/legato.h"

#include "gfx/legato/generated/le_gen_scheme.h"
#include "gfx/legato/generated/le_gen_assets.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

// screen member widget declarations
extern leWidget* SN_SET_BackGnd;
extern leLabelWidget* SN_SET_thousands;
extern leLabelWidget* SN_SET_hundreds;
extern leLabelWidget* SN_SET_tens;
extern leLabelWidget* SN_SET_singles;
extern leLabelWidget* SN_SET_LabelWidget_6;
extern leImageWidget* SN_SET_ImageWidget_0;
extern leImageWidget* SN_SET_ImageWidget_1;
extern leImageWidget* SN_SET_ImageWidget_2;
extern leImageWidget* SN_SET_ImageWidget_3;
extern leButtonWidget* SN_SET_oneUp;
extern leButtonWidget* SN_SET_oneDwn;
extern leButtonWidget* SN_SET_tenUp;
extern leButtonWidget* SN_SET_tenDwn;
extern leButtonWidget* SN_SET_hundredUp;
extern leButtonWidget* SN_SET_hundredDwn;
extern leButtonWidget* SN_SET_thousandUp;
extern leButtonWidget* SN_SET_thousandDwn;
extern leButtonWidget* SN_SET_save;

// event handlers
// !!THESE MUST BE IMPLEMENTED IN THE APPLICATION CODE!!
void event_SN_SET_oneUp_OnPressed(leButtonWidget* btn);
void event_SN_SET_oneDwn_OnPressed(leButtonWidget* btn);
void event_SN_SET_tenUp_OnPressed(leButtonWidget* btn);
void event_SN_SET_tenDwn_OnPressed(leButtonWidget* btn);
void event_SN_SET_hundredUp_OnPressed(leButtonWidget* btn);
void event_SN_SET_hundredDwn_OnPressed(leButtonWidget* btn);
void event_SN_SET_thousandUp_OnPressed(leButtonWidget* btn);
void event_SN_SET_thousandDwn_OnPressed(leButtonWidget* btn);
void event_SN_SET_save_OnPressed(leButtonWidget* btn);

// screen lifecycle functions
// DO NOT CALL THESE DIRECTLY
leResult screenInit_SN_SET(void); // called when Legato is initialized
leResult screenShow_SN_SET(void); // called when screen is shown
void screenHide_SN_SET(void); // called when screen is hidden
void screenDestroy_SN_SET(void); // called when Legato is destroyed
void screenUpdate_SN_SET(void); // called when Legato is updating

leWidget* screenGetRoot_SN_SET(uint32_t lyrIdx); // gets a root widget for this screen

// Screen Events:
void SN_SET_OnShow(void); // called when this screen is shown

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // LE_GEN_SCREEN_SN_SET_H
