#ifndef LE_GEN_SCREEN_SPLASHSCREEN_H
#define LE_GEN_SCREEN_SPLASHSCREEN_H

#include "gfx/legato/legato.h"

#include "gfx/legato/generated/le_gen_scheme.h"
#include "gfx/legato/generated/le_gen_assets.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

// screen member widget declarations
extern leRectangleWidget* splashScreen_RectangleWidget0;
extern leImageWidget* splashScreen_ImageWidget0;
extern leTouchTestWidget* splashScreen_TouchTestWidget0;

// event handlers
// !!THESE MUST BE IMPLEMENTED IN THE APPLICATION CODE!!
void event_splashScreen_TouchTestWidget0_OnPointAdded(leTouchTestWidget* tch, lePoint* pnt);

// screen lifecycle functions
// DO NOT CALL THESE DIRECTLY
leResult screenInit_splashScreen(void); // called when Legato is initialized
leResult screenShow_splashScreen(void); // called when screen is shown
void screenHide_splashScreen(void); // called when screen is hidden
void screenDestroy_splashScreen(void); // called when Legato is destroyed
void screenUpdate_splashScreen(void); // called when Legato is updating

leWidget* screenGetRoot_splashScreen(uint32_t lyrIdx); // gets a root widget for this screen

// Screen Events:
void splashScreen_OnShow(void); // called when this screen is shown

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // LE_GEN_SCREEN_SPLASHSCREEN_H
