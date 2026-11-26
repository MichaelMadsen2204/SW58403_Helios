
#include "definitions.h" // indeholder app.h, system headers, legato types mm.
#include "gfx/legato/generated/screen/le_gen_screen_greenBiasScreen.h" 
#include "ui_globals.h"
#include "app.h"


// *****************************************************************************
// *****************************************************************************
// Section: Application Green Bias Screen Functions 
// *****************************************************************************
// *****************************************************************************
// <editor-fold defaultstate="collapsed" desc="Green Bias Screen Functions">

void event_greenBiasScreen_BIAS_SETTING1_OnPressed(leButtonWidget* btn)
{
  greenBiasScreen_BIAS_SETTING2->fn->setPressed(greenBiasScreen_BIAS_SETTING2, LE_FALSE);  
  greenBiasScreen_BIAS_SETTING2->fn->setEnabled(greenBiasScreen_BIAS_SETTING2, LE_TRUE);  
  greenBiasScreen_BIAS_SETTING1->fn->setEnabled(greenBiasScreen_BIAS_SETTING1, LE_FALSE); 
  appData.greenBias = GB1;
     
};
void event_greenBiasScreen_BIAS_SETTING2_OnPressed(leButtonWidget* btn)
{
  greenBiasScreen_BIAS_SETTING1->fn->setPressed(greenBiasScreen_BIAS_SETTING1, LE_FALSE); 
  greenBiasScreen_BIAS_SETTING1->fn->setEnabled(greenBiasScreen_BIAS_SETTING1, LE_TRUE);  
  greenBiasScreen_BIAS_SETTING2->fn->setEnabled(greenBiasScreen_BIAS_SETTING2, LE_FALSE);  
  appData.greenBias = GB2;
  
};
void event_greenBiasScreen_GreenBiasBackToMenuBut_OnPressed(leButtonWidget* btn)
{
   saveGreenBias();
   legato_showScreen(screenID_mainMenuScreen);
};
void greenBiasScreen_OnShow(void) // called when this screen is shown
{
  //DEBUG_PRINT("irSourceScreen_OnShow\r\n"); //slet  
  if(appData.greenBias == GB1)
  {
    greenBiasScreen_BIAS_SETTING1->fn->setPressed(greenBiasScreen_BIAS_SETTING1, LE_TRUE); 
    greenBiasScreen_BIAS_SETTING2->fn->setPressed(greenBiasScreen_BIAS_SETTING2, LE_FALSE);  
    greenBiasScreen_BIAS_SETTING2->fn->setEnabled(greenBiasScreen_BIAS_SETTING2, LE_TRUE);  
    greenBiasScreen_BIAS_SETTING1->fn->setEnabled(greenBiasScreen_BIAS_SETTING1, LE_FALSE); 
  }
  else
  {
    greenBiasScreen_BIAS_SETTING2->fn->setPressed(greenBiasScreen_BIAS_SETTING2, LE_TRUE);    
    greenBiasScreen_BIAS_SETTING1->fn->setPressed(greenBiasScreen_BIAS_SETTING1, LE_FALSE); 
    greenBiasScreen_BIAS_SETTING1->fn->setEnabled(greenBiasScreen_BIAS_SETTING1, LE_TRUE); 
    greenBiasScreen_BIAS_SETTING2->fn->setEnabled(greenBiasScreen_BIAS_SETTING2, LE_FALSE);  
  }
};

// </editor-fold>
