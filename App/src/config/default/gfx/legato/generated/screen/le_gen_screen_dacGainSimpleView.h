#ifndef LE_GEN_SCREEN_DACGAINSIMPLEVIEW_H
#define LE_GEN_SCREEN_DACGAINSIMPLEVIEW_H

#include "gfx/legato/legato.h"

#include "gfx/legato/generated/le_gen_scheme.h"
#include "gfx/legato/generated/le_gen_assets.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

// screen member widget declarations
extern leWidget* dacGainSimpleView_Panel_0;
extern leLabelWidget* dacGainSimpleView_header;
extern leLabelWidget* dacGainSimpleView_header2;
extern leLabelWidget* dacGainSimpleView_gain0dB;
extern leLabelWidget* dacGainSimpleView_gainMinus6dB;

// screen lifecycle functions
// DO NOT CALL THESE DIRECTLY
leResult screenInit_dacGainSimpleView(void); // called when Legato is initialized
leResult screenShow_dacGainSimpleView(void); // called when screen is shown
void screenHide_dacGainSimpleView(void); // called when screen is hidden
void screenDestroy_dacGainSimpleView(void); // called when Legato is destroyed
void screenUpdate_dacGainSimpleView(void); // called when Legato is updating

leWidget* screenGetRoot_dacGainSimpleView(uint32_t lyrIdx); // gets a root widget for this screen

// Screen Events:
void dacGainSimpleView_OnShow(void); // called when this screen is shown

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // LE_GEN_SCREEN_DACGAINSIMPLEVIEW_H
