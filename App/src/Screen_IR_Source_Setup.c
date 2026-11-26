#include "definitions.h" // indeholder app.h, system headers, legato types mm.
#include "gfx/legato/generated/screen/le_gen_screen_irSourceScreen.h" 
#include "ui_globals.h"
#include "app.h"

// *****************************************************************************
// *****************************************************************************
// Section: Application IR Source Screen Functions 
// *****************************************************************************
// *****************************************************************************
// <editor-fold defaultstate="collapsed" desc="IR Source Screen Functions">

void event_irSourceScreen_irSourceFrontBut_OnPressed(leButtonWidget* btn)
{
  irSourceScreen_irSourceBackBut->fn->setPressed(irSourceScreen_irSourceBackBut, LE_FALSE);  
  irSourceScreen_irSourceBackBut->fn->setEnabled(irSourceScreen_irSourceBackBut, LE_TRUE);  
  irSourceScreen_irSourceFrontBut->fn->setEnabled(irSourceScreen_irSourceFrontBut, LE_FALSE); 
  appData.irSource = frontPanelIR;
  IR_SOURCE_Set();    
};
void event_irSourceScreen_irSourceBackBut_OnPressed(leButtonWidget* btn)
{
  irSourceScreen_irSourceFrontBut->fn->setPressed(irSourceScreen_irSourceFrontBut, LE_FALSE); 
  irSourceScreen_irSourceFrontBut->fn->setEnabled(irSourceScreen_irSourceFrontBut, LE_TRUE);  
  irSourceScreen_irSourceBackBut->fn->setEnabled(irSourceScreen_irSourceBackBut, LE_FALSE);  
  appData.irSource = rearPanelIR;
  IR_SOURCE_Clear();
};
void event_irSourceScreen_irSourceBackToMenuBut_OnPressed(leButtonWidget* btn)
{
   saveIRSourceSetting(); 
   legato_showScreen(screenID_mainMenuScreen);
};
void irSourceScreen_OnShow(void)
{
  //printf("irSourceScreen_OnShow\r\n"); //slet  
  if(appData.irSource == frontPanelIR)
  {
    irSourceScreen_irSourceFrontBut->fn->setPressed(irSourceScreen_irSourceFrontBut, LE_TRUE); 
    irSourceScreen_irSourceBackBut->fn->setPressed(irSourceScreen_irSourceBackBut, LE_FALSE);  
    irSourceScreen_irSourceBackBut->fn->setEnabled(irSourceScreen_irSourceBackBut, LE_TRUE);  
    irSourceScreen_irSourceFrontBut->fn->setEnabled(irSourceScreen_irSourceFrontBut, LE_FALSE); 
  }
  else
  {
    irSourceScreen_irSourceBackBut->fn->setPressed(irSourceScreen_irSourceBackBut, LE_TRUE);    
    irSourceScreen_irSourceFrontBut->fn->setPressed(irSourceScreen_irSourceFrontBut, LE_FALSE); 
    irSourceScreen_irSourceFrontBut->fn->setEnabled(irSourceScreen_irSourceFrontBut, LE_TRUE); 
    irSourceScreen_irSourceBackBut->fn->setEnabled(irSourceScreen_irSourceBackBut, LE_FALSE);  
  }
};

// </editor-fold>
