#include "definitions.h" // indeholder app.h, system headers, legato types mm.
#include "gfx/legato/generated/screen/le_gen_screen_restoreSettingScreen.h"
#include "ui_globals.h"
#include "app.h"

static leChar FWCharBuffer[16] = {0};


// *****************************************************************************
// *****************************************************************************
// Section: Restore Settings Functions
// *****************************************************************************
// *****************************************************************************

// <editor-fold defaultstate="collapsed" desc="Restore Settings Functions">

void event_restoreSettingScreen_ResContiniueYesButton_OnPressed(leButtonWidget* btn)
{
    restoreSettingScreen_splashResSetSure->fn->setVisible(restoreSettingScreen_splashResSetSure, LE_TRUE);
    restoreSettingScreen_splashResSetSure->fn->setEnabled(restoreSettingScreen_splashResSetSure, LE_TRUE);
    restoreSettingScreen_yesButton->fn->setEnabled(restoreSettingScreen_yesButton,LE_TRUE); 
    restoreSettingScreen_cancelButton->fn->setEnabled(restoreSettingScreen_cancelButton,LE_TRUE); 
};
void event_restoreSettingScreen_ResContiniueNoButton_OnPressed(leButtonWidget* btn)
{
    legato_showScreen(screenID_mainMenuScreen); 
};
void event_restoreSettingScreen_yesButton_OnPressed(leButtonWidget* btn)
{
    writeEEpromDefault();
    restoreSettingScreen_splashResSetSure->fn->setVisible(restoreSettingScreen_splashResSetSure, LE_FALSE);
    restoreSettingScreen_splashResSetSure->fn->setEnabled(restoreSettingScreen_splashResSetSure, LE_FALSE);
    restoreSettingScreen_settingsRestoredPanel->fn->setVisible(restoreSettingScreen_settingsRestoredPanel, LE_TRUE);
    restoreSettingScreen_settingsRestoredPanel->fn->setEnabled(restoreSettingScreen_settingsRestoredPanel, LE_TRUE);
};
void event_restoreSettingScreen_cancelButton_OnPressed(leButtonWidget* btn)
{
    legato_showScreen(screenID_mainMenuScreen); 
};
void event_restoreSettingScreen_backAfterRestoreBut_OnPressed(leButtonWidget* btn)
{
   getInpNamesFromEEProm();
   getEEPromValues();
   if(appData.irSource == frontPanelIR)
      IR_SOURCE_Set();
   else
      IR_SOURCE_Clear();
   
   legato_showScreen(screenID_mainMenuScreen);  
};
void restoreSettingScreen_OnShow(void)
{
     leFixedString_Constructor(&fwString, FWCharBuffer, 16);
     fwString.fn->setFont(&fwString, leStringTable_GetStringFont(leGetState()->stringTable, stringID_fwString, 0));      
     
     fwString.fn->setFromCStr(&fwString, firmware);  
     restoreSettingScreen_fwLabel->fn->setString(restoreSettingScreen_fwLabel, (leString*)&fwString);   
};

// </editor-fold>
