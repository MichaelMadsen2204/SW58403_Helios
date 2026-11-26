#ifndef LE_GEN_SCREEN_DISPLAYSIMPLEVIEW_H
#define LE_GEN_SCREEN_DISPLAYSIMPLEVIEW_H

#include "gfx/legato/legato.h"

#include "gfx/legato/generated/le_gen_scheme.h"
#include "gfx/legato/generated/le_gen_assets.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

// screen member widget declarations
extern leWidget* displaySimpleView_Panel_0;
extern leLabelWidget* displaySimpleView_header;
extern leLabelWidget* displaySimpleView_dispMode;

// screen lifecycle functions
// DO NOT CALL THESE DIRECTLY
leResult screenInit_displaySimpleView(void); // called when Legato is initialized
leResult screenShow_displaySimpleView(void); // called when screen is shown
void screenHide_displaySimpleView(void); // called when screen is hidden
void screenDestroy_displaySimpleView(void); // called when Legato is destroyed
void screenUpdate_displaySimpleView(void); // called when Legato is updating

leWidget* screenGetRoot_displaySimpleView(uint32_t lyrIdx); // gets a root widget for this screen

// Screen Events:
void displaySimpleView_OnShow(void); // called when this screen is shown

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // LE_GEN_SCREEN_DISPLAYSIMPLEVIEW_H
