#ifndef LE_GEN_SCREEN_FILTERSIMPLEVIEW_H
#define LE_GEN_SCREEN_FILTERSIMPLEVIEW_H

#include "gfx/legato/legato.h"

#include "gfx/legato/generated/le_gen_scheme.h"
#include "gfx/legato/generated/le_gen_assets.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

// screen member widget declarations
extern leWidget* filterSimpleView_Panel_0;
extern leLabelWidget* filterSimpleView_filterNumber;
extern leLabelWidget* filterSimpleView_LabelWidget_1;
extern leLabelWidget* filterSimpleView_LabelWidget_2;

// screen lifecycle functions
// DO NOT CALL THESE DIRECTLY
leResult screenInit_filterSimpleView(void); // called when Legato is initialized
leResult screenShow_filterSimpleView(void); // called when screen is shown
void screenHide_filterSimpleView(void); // called when screen is hidden
void screenDestroy_filterSimpleView(void); // called when Legato is destroyed
void screenUpdate_filterSimpleView(void); // called when Legato is updating

leWidget* screenGetRoot_filterSimpleView(uint32_t lyrIdx); // gets a root widget for this screen

// Screen Events:
void filterSimpleView_OnShow(void); // called when this screen is shown

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // LE_GEN_SCREEN_FILTERSIMPLEVIEW_H
