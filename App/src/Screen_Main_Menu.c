#include "definitions.h" // indeholder app.h, system headers, legato types mm.
#include "gfx/legato/generated/screen/le_gen_screen_mainMenuScreen.h" 
#include "ui_globals.h"
#include "app.h"





// *****************************************************************************
// *****************************************************************************
// Section: Application mainMenuScreen Functions 
// *****************************************************************************
// *****************************************************************************
// <editor-fold defaultstate="collapsed" desc="Main Menu Screen Functions">

void event_mainMenuScreen_menuExitBut_OnPressed(leButtonWidget* btn)
{
    appData.reqUiAction = UIREQ_EXIT_MENU;
    appData.menuFlg = 0;    
};
void event_mainMenuScreen_menuVolBut_OnPressed(leButtonWidget* btn)
{
    legato_showScreen(screenID_volSettingsScreen); 
};
void event_mainMenuScreen_menuDisplayBut_OnPressed(leButtonWidget* btn)
{
    legato_showScreen(screenID_displayIntensityScreen);      
};
void event_mainMenuScreen_menuIrSrcBut_OnPressed(leButtonWidget* btn)
{
    legato_showScreen(screenID_irSourceScreen);
};
void event_mainMenuScreen_menuDigitalBut_OnPressed(leButtonWidget* btn)
{
    legato_showScreen(screenID_digitalSetupScreen);
};
void event_mainMenuScreen_menuInpLevMatchBut_OnPressed(leButtonWidget* btn)
{
    legato_showScreen(screenID_inpLvlMatchScreen);
};
void event_mainMenuScreen_menuNameInpBut_OnPressed(leButtonWidget* btn)
{
    appData.inpToRename = 1;
    legato_showScreen(screenID_renameInputsScreen);     
};
void event_mainMenuScreen_menuAvInpBut_OnPressed(leButtonWidget* btn)
{
    legato_showScreen(screenID_avInputScreen);     
};
void event_mainMenuScreen_menuRestSetBut_OnPressed(leButtonWidget* btn)
{
    legato_showScreen(screenID_restoreSettingScreen);     
};
void event_mainMenuScreen_menuRiaaBut_OnPressed(leButtonWidget* btn)
{
    legato_showScreen(screenID_pickupSelectScreen);
}
void event_mainMenuScreen_menuBiasBut_OnPressed(leButtonWidget* btn)
{
    legato_showScreen(screenID_greenBiasScreen); 
}

void event_mainMenuScreen_cancelButton_OnPressed(leButtonWidget* btn){};
void mainMenuScreen_OnShow(void)
{
  appData.menuFlg = 1;
  if(!appData.dacRegiFlg)  
    mainMenuScreen_menuDigitalBut->fn->setVisible(mainMenuScreen_menuDigitalBut, LE_FALSE);  
  if(!appData.phonoRegiFlg)  
    mainMenuScreen_menuRiaaBut->fn->setVisible(mainMenuScreen_menuRiaaBut, LE_FALSE);  

  setBackLightIntensity(100);
  

  
};

void mainMenuScreen_OnHide(void)
{
    appData.irInputChangeFlg = 1;
};

// </editor-fold>
