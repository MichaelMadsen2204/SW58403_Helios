#ifndef LE_GEN_SCREEN_ACTIONSCREEN_H
#define LE_GEN_SCREEN_ACTIONSCREEN_H

#include "gfx/legato/legato.h"

#include "gfx/legato/generated/le_gen_scheme.h"
#include "gfx/legato/generated/le_gen_assets.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

// screen member widget declarations
extern leWidget* actionScreen_BackGround;
extern leWidget* actionScreen_anaInpNamePanel;
extern leWidget* actionScreen_digiInpNamePanel;
extern leWidget* actionScreen_digInfoPanel;
extern leButtonWidget* actionScreen_dispOnButton;
extern leImageWidget* actionScreen_fanErrorImg;
extern leImageWidget* actionScreen_actionMuteKryds;
extern leLabelWidget* actionScreen_actVolumeHeader;
extern leLabelWidget* actionScreen_avLevLabel;
extern leLabelWidget* actionScreen_actCurLevel;
extern leButtonWidget* actionScreen_actMuteBut;
extern leButtonWidget* actionScreen_actMenuBut;
extern leButtonWidget* actionScreen_actAnaDigiSelectionBut;
extern leImageWidget* actionScreen_actVolumeButImg;
extern leButtonWidget* actionScreen_actVolPlusBut;
extern leButtonWidget* actionScreen_actVolMinusBut;
extern leLabelWidget* actionScreen_anaInpNameHeader;
extern leButtonWidget* actionScreen_anaInp1But;
extern leButtonWidget* actionScreen_anaInp2But;
extern leButtonWidget* actionScreen_anaInp3But;
extern leButtonWidget* actionScreen_anaInp4But;
extern leButtonWidget* actionScreen_anaInp5But;
extern leButtonWidget* actionScreen_anaInp6But;
extern leLabelWidget* actionScreen_digiInpNameHeader;
extern leButtonWidget* actionScreen_digiInp7But;
extern leButtonWidget* actionScreen_digiInp8But;
extern leButtonWidget* actionScreen_digiInp9But;
extern leButtonWidget* actionScreen_digiInp10But;
extern leButtonWidget* actionScreen_digiInp11But;
extern leButtonWidget* actionScreen_padLockImg;
extern leLabelWidget* actionScreen_digiInfoFSLabel;
extern leLabelWidget* actionScreen_digiInfoFilterLabel1;
extern leLabelWidget* actionScreen_digiInfoFilterLabel2;
extern leLabelWidget* actionScreen_digiInfoFilterLabel3;
extern leLabelWidget* actionScreen_dsdLpOff;
extern leLabelWidget* actionScreen_dsdLpOn;
extern leLabelWidget* actionScreen_gain0db;
extern leLabelWidget* actionScreen_gainMinus6dB;
extern leWidget* actionScreen_batteryPanel;
extern leImageWidget* actionScreen_BattCharged;
extern leImageWidget* actionScreen_BattCharging;

// event handlers
// !!THESE MUST BE IMPLEMENTED IN THE APPLICATION CODE!!
void event_actionScreen_dispOnButton_OnPressed(leButtonWidget* btn);
void event_actionScreen_actMuteBut_OnPressed(leButtonWidget* btn);
void event_actionScreen_actMenuBut_OnPressed(leButtonWidget* btn);
void event_actionScreen_actAnaDigiSelectionBut_OnPressed(leButtonWidget* btn);
void event_actionScreen_actAnaDigiSelectionBut_OnReleased(leButtonWidget* btn);
void event_actionScreen_actVolPlusBut_OnPressed(leButtonWidget* btn);
void event_actionScreen_actVolPlusBut_OnReleased(leButtonWidget* btn);
void event_actionScreen_actVolMinusBut_OnPressed(leButtonWidget* btn);
void event_actionScreen_actVolMinusBut_OnReleased(leButtonWidget* btn);
void event_actionScreen_anaInp1But_OnPressed(leButtonWidget* btn);
void event_actionScreen_anaInp2But_OnPressed(leButtonWidget* btn);
void event_actionScreen_anaInp3But_OnPressed(leButtonWidget* btn);
void event_actionScreen_anaInp4But_OnPressed(leButtonWidget* btn);
void event_actionScreen_anaInp5But_OnPressed(leButtonWidget* btn);
void event_actionScreen_anaInp6But_OnPressed(leButtonWidget* btn);
void event_actionScreen_digiInp7But_OnPressed(leButtonWidget* btn);
void event_actionScreen_digiInp8But_OnPressed(leButtonWidget* btn);
void event_actionScreen_digiInp9But_OnPressed(leButtonWidget* btn);
void event_actionScreen_digiInp10But_OnPressed(leButtonWidget* btn);
void event_actionScreen_digiInp11But_OnPressed(leButtonWidget* btn);

// screen lifecycle functions
// DO NOT CALL THESE DIRECTLY
leResult screenInit_actionScreen(void); // called when Legato is initialized
leResult screenShow_actionScreen(void); // called when screen is shown
void screenHide_actionScreen(void); // called when screen is hidden
void screenDestroy_actionScreen(void); // called when Legato is destroyed
void screenUpdate_actionScreen(void); // called when Legato is updating

leWidget* screenGetRoot_actionScreen(uint32_t lyrIdx); // gets a root widget for this screen

// Screen Events:
void actionScreen_OnShow(void); // called when this screen is shown

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // LE_GEN_SCREEN_ACTIONSCREEN_H
