#ifndef LE_GEN_SCREEN_WRONGACVOLTAGESCREEN_H
#define LE_GEN_SCREEN_WRONGACVOLTAGESCREEN_H

#include "gfx/legato/legato.h"

#include "gfx/legato/generated/le_gen_scheme.h"
#include "gfx/legato/generated/le_gen_assets.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

// screen member widget declarations
extern leWidget* wrongAcVoltageScreen_Panel_0;
extern leLabelWidget* wrongAcVoltageScreen_LabelWidget_0;
extern leLabelWidget* wrongAcVoltageScreen_LabelWidget_1;

// screen lifecycle functions
// DO NOT CALL THESE DIRECTLY
leResult screenInit_wrongAcVoltageScreen(void); // called when Legato is initialized
leResult screenShow_wrongAcVoltageScreen(void); // called when screen is shown
void screenHide_wrongAcVoltageScreen(void); // called when screen is hidden
void screenDestroy_wrongAcVoltageScreen(void); // called when Legato is destroyed
void screenUpdate_wrongAcVoltageScreen(void); // called when Legato is updating

leWidget* screenGetRoot_wrongAcVoltageScreen(uint32_t lyrIdx); // gets a root widget for this screen

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // LE_GEN_SCREEN_WRONGACVOLTAGESCREEN_H
