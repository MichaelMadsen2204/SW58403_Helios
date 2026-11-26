#ifndef LE_GEN_SCREEN_DSDLPSIMPLEVIEW_H
#define LE_GEN_SCREEN_DSDLPSIMPLEVIEW_H

#include "gfx/legato/legato.h"

#include "gfx/legato/generated/le_gen_scheme.h"
#include "gfx/legato/generated/le_gen_assets.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

// screen member widget declarations
extern leWidget* dsdLpSimpleView_Panel_0;
extern leLabelWidget* dsdLpSimpleView_dsdHeader;
extern leLabelWidget* dsdLpSimpleView_lowPassHeader;
extern leLabelWidget* dsdLpSimpleView_offValue;
extern leLabelWidget* dsdLpSimpleView_onValue;

// screen lifecycle functions
// DO NOT CALL THESE DIRECTLY
leResult screenInit_dsdLpSimpleView(void); // called when Legato is initialized
leResult screenShow_dsdLpSimpleView(void); // called when screen is shown
void screenHide_dsdLpSimpleView(void); // called when screen is hidden
void screenDestroy_dsdLpSimpleView(void); // called when Legato is destroyed
void screenUpdate_dsdLpSimpleView(void); // called when Legato is updating

leWidget* screenGetRoot_dsdLpSimpleView(uint32_t lyrIdx); // gets a root widget for this screen

// Screen Events:
void dsdLpSimpleView_OnShow(void); // called when this screen is shown

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // LE_GEN_SCREEN_DSDLPSIMPLEVIEW_H
