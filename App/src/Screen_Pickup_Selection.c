#include "definitions.h" // indeholder app.h, system headers, legato types mm.
#include "gfx/legato/generated/screen/le_gen_screen_pickupSelectScreen.h"
#include "ui_globals.h"
#include "app.h"

// *****************************************************************************
// *****************************************************************************
// Section: Application Pickup Selection Screen Functions 
// *****************************************************************************
// *****************************************************************************
// <editor-fold defaultstate="collapsed" desc="pickup Selection Screen Functions">

void stabilizingProgressDelay_Callback( uintptr_t context )
{
    appData.stabilizingProgress ++;
}


void updateProgressBar(void)
{
    if(appData.stabilizingProgress < 100)
    {
      pickupSelectScreen_ProgressBar->fn->setValue(pickupSelectScreen_ProgressBar, appData.stabilizingProgress);  
    }
    else
    {
      SYS_TIME_TimerDestroy(appData.stabilizingProgressDelayHandle);

      appData.state = APP_STATE_IDLE;
      legato_showScreen(screenID_mainMenuScreen);
     }
}
void event_pickupSelectScreen_pickupMMBut_OnPressed(leButtonWidget* btn)
{
    pickupSelectScreen_pickupMCBut->fn->setPressed(pickupSelectScreen_pickupMCBut, LE_FALSE);  
    pickupSelectScreen_pickupMCBut->fn->setEnabled(pickupSelectScreen_pickupMCBut, LE_TRUE);  
    pickupSelectScreen_pickupMMBut->fn->setEnabled(pickupSelectScreen_pickupMMBut, LE_FALSE); 
    appData.pickupSelection = movingMagnet;
    
};
void event_pickupSelectScreen_pickupMCBut_OnPressed(leButtonWidget* btn)
{
    pickupSelectScreen_pickupMMBut->fn->setPressed(pickupSelectScreen_pickupMMBut, LE_FALSE);  
    pickupSelectScreen_pickupMMBut->fn->setEnabled(pickupSelectScreen_pickupMMBut, LE_TRUE);  
    pickupSelectScreen_pickupMCBut->fn->setEnabled(pickupSelectScreen_pickupMCBut, LE_FALSE); 
    appData.pickupSelection = movingCoil;
    
};
void event_pickupSelectScreen_pickupSelBackToMenuBut_OnPressed(leButtonWidget* btn)
{
     if (appData.oldPickupSelection != appData.pickupSelection)
    {
        // 1) Sikring af niveau og gem valg
        setLevelZero();
        savePickupSelection();

        // 2) Skriv HW nu (erstatter u26WriteOutputs(appData.u26Byte0, appData.u26Byte2))
        U26_ApplyPickupHwFromSelection();

        // 3) Vis stabiliserings-panel og kør progress ? identisk flow som før
        pickupSelectScreen_stabilizingPanel->fn->setVisible(pickupSelectScreen_stabilizingPanel, LE_TRUE);
        appData.stabilizingProgress = 0;
        pickupSelectScreen_ProgressBar->fn->setValue(pickupSelectScreen_ProgressBar, appData.stabilizingProgress);
        appData.stabilizingProgressDelayHandle =
            SYS_TIME_CallbackRegisterMS(stabilizingProgressDelay_Callback, 0, 250, SYS_TIME_PERIODIC);

        appData.state = APP_STABILIZING_PROGRESS_TASKS;
    }
    else
    {
        legato_showScreen(screenID_mainMenuScreen);
    }
        
};
void pickupSelectScreen_OnShow(void)
{
  //DEBUG_PRINT("pickupSelection_OnShow : %d\r\n",appData.pickupSelection); //slet  
  pickupSelectScreen_stabilizingPanel->fn->setVisible(pickupSelectScreen_stabilizingPanel, LE_FALSE);
  if(appData.pickupSelection == movingMagnet)
  {
    pickupSelectScreen_pickupMMBut->fn->setPressed(pickupSelectScreen_pickupMMBut, LE_TRUE);  
    pickupSelectScreen_pickupMCBut->fn->setPressed(pickupSelectScreen_pickupMCBut, LE_FALSE);  
    pickupSelectScreen_pickupMCBut->fn->setEnabled(pickupSelectScreen_pickupMCBut, LE_TRUE);  
    pickupSelectScreen_pickupMMBut->fn->setEnabled(pickupSelectScreen_pickupMMBut, LE_FALSE); 
  }
  else
  {
    pickupSelectScreen_pickupMCBut->fn->setPressed(pickupSelectScreen_pickupMCBut, LE_TRUE);  
    pickupSelectScreen_pickupMMBut->fn->setPressed(pickupSelectScreen_pickupMMBut, LE_FALSE);  
    pickupSelectScreen_pickupMMBut->fn->setEnabled(pickupSelectScreen_pickupMMBut, LE_TRUE);  
    pickupSelectScreen_pickupMCBut->fn->setEnabled(pickupSelectScreen_pickupMCBut, LE_FALSE); 
  }
  appData.oldPickupSelection = appData.pickupSelection;
};

// </editor-fold>
