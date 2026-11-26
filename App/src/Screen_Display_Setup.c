#include "definitions.h" // indeholder app.h, system headers, legato types mm.
#include "gfx/legato/generated/screen/le_gen_screen_digitalSetupScreen.h"
#include "ui_globals.h"
#include "app.h"


// *****************************************************************************
// *****************************************************************************
// Section: Display Setup Functions
// *****************************************************************************
// *****************************************************************************

// <editor-fold defaultstate="collapsed" desc="Display Setup Functions">
void setDisplayIntensity(void)
{
    
    DEBUG_PRINT("backlight disp mode: %d\r\n", appData.dispMode & 0x7F);
    switch(appData.dispMode & 0x7F)
    {
        case  mode100 : {
            setBackLightIntensity(100);            
            break;
        }
        case  mode75  : {
            setBackLightIntensity(60); //var 75
            break;
        }
        case  mode50  : {
            setBackLightIntensity(40); //var 50
            break;
        }    
        case  mode25  : {
            setBackLightIntensity(15); //var 25
            break;
        }
        case  modeOff : {
            setBackLightIntensity(100);
            break;
        }
        case  modeDim : {
            setBackLightIntensity(100);
            break;
        }
    }
}

void clrSelectedDisplayMode(void)
{
    displayIntensityScreen_disp100Button->fn->setPressed(displayIntensityScreen_disp100Button, LE_FALSE);
    displayIntensityScreen_disp75Button->fn->setPressed(displayIntensityScreen_disp75Button, LE_FALSE);
    displayIntensityScreen_disp50Button->fn->setPressed(displayIntensityScreen_disp50Button, LE_FALSE);
    displayIntensityScreen_disp25Button->fn->setPressed(displayIntensityScreen_disp25Button, LE_FALSE);
    displayIntensityScreen_dispOffButton->fn->setPressed(displayIntensityScreen_dispOffButton, LE_FALSE);
    displayIntensityScreen_dispDimButton->fn->setPressed(displayIntensityScreen_dispDimButton, LE_FALSE);
    
    displayIntensityScreen_disp100Button->fn->setEnabled(displayIntensityScreen_disp100Button, LE_TRUE);
    displayIntensityScreen_disp75Button->fn->setEnabled(displayIntensityScreen_disp75Button, LE_TRUE);
    displayIntensityScreen_disp50Button->fn->setEnabled(displayIntensityScreen_disp50Button, LE_TRUE);
    displayIntensityScreen_disp25Button->fn->setEnabled(displayIntensityScreen_disp25Button, LE_TRUE);
    displayIntensityScreen_dispOffButton->fn->setEnabled(displayIntensityScreen_dispOffButton, LE_TRUE);
    displayIntensityScreen_dispDimButton->fn->setEnabled(displayIntensityScreen_dispDimButton, LE_TRUE);
    
    displayIntensityScreen_disp100Button->fn->setReleasedImage(displayIntensityScreen_disp100Button, (leImage*)&smallNotSelected3);
    displayIntensityScreen_disp75Button->fn->setReleasedImage(displayIntensityScreen_disp75Button, (leImage*)&smallNotSelected3);
    displayIntensityScreen_disp50Button->fn->setReleasedImage(displayIntensityScreen_disp50Button, (leImage*)&smallNotSelected3);
    displayIntensityScreen_disp25Button->fn->setReleasedImage(displayIntensityScreen_disp25Button, (leImage*)&smallNotSelected3);
    displayIntensityScreen_dispOffButton->fn->setReleasedImage(displayIntensityScreen_dispOffButton, (leImage*)&smallNotSelected3);
    displayIntensityScreen_dispDimButton->fn->setReleasedImage(displayIntensityScreen_dispDimButton, (leImage*)&smallNotSelected3);
}

void event_displayIntensityScreen_disp100Button_OnPressed(leButtonWidget* btn)
{
    //DEBUG_PRINT("displaymode 100 Pressed\r\n");
    if((appData.dispMode & 0x7F) != mode100)
      clrSelectedDisplayMode();
    appData.dispMode &= 0x80;
    appData.dispMode |= mode100;
    displayIntensityScreen_disp100Button->fn->setEnabled(displayIntensityScreen_disp100Button, LE_FALSE);  
    displayIntensityScreen_disp100Button->fn->setReleasedImage(displayIntensityScreen_disp100Button, (leImage*)&smallSelected2);    
};
void event_displayIntensityScreen_disp75Button_OnPressed(leButtonWidget* btn)
{
    //DEBUG_PRINT("displaymode 75 Pressed\r\n");
    if((appData.dispMode & 0x7F) != mode75)
      clrSelectedDisplayMode();
    appData.dispMode &= 0x80;
    appData.dispMode |= mode75;
    displayIntensityScreen_disp75Button->fn->setEnabled(displayIntensityScreen_disp75Button, LE_FALSE);  
    displayIntensityScreen_disp75Button->fn->setReleasedImage(displayIntensityScreen_disp75Button, (leImage*)&smallSelected2);
};
void event_displayIntensityScreen_disp50Button_OnPressed(leButtonWidget* btn)
{
    //DEBUG_PRINT("displaymode 50 Pressed\r\n");
    if((appData.dispMode & 0x7F) !=  mode50)
      clrSelectedDisplayMode();
    appData.dispMode &= 0x80;
    appData.dispMode |= mode50;
    displayIntensityScreen_disp50Button->fn->setEnabled(displayIntensityScreen_disp50Button, LE_FALSE);
    displayIntensityScreen_disp50Button->fn->setReleasedImage(displayIntensityScreen_disp50Button, (leImage*)&smallSelected2);
};
void event_displayIntensityScreen_disp25Button_OnPressed(leButtonWidget* btn)
{
   // DEBUG_PRINT("displaymode 25 Pressed\r\n");
    if((appData.dispMode & 0x7F) !=  mode25)
      clrSelectedDisplayMode();
    appData.dispMode &= 0x80;
    appData.dispMode |= mode25;
    displayIntensityScreen_disp25Button->fn->setEnabled(displayIntensityScreen_disp25Button, LE_FALSE);  
    displayIntensityScreen_disp25Button->fn->setReleasedImage(displayIntensityScreen_disp25Button, (leImage*)&smallSelected2);
};
void event_displayIntensityScreen_dispDimButton_OnPressed(leButtonWidget* btn)
{
    //DEBUG_PRINT("displaymode Dim Pressed \r\n");
    if((appData.dispMode & 0x7F) != modeDim)
      clrSelectedDisplayMode();
    appData.dispMode &= 0x80;
    appData.dispMode |= modeDim;
    displayIntensityScreen_dispDimButton->fn->setEnabled(displayIntensityScreen_dispDimButton, LE_FALSE);  
    displayIntensityScreen_dispDimButton->fn->setReleasedImage(displayIntensityScreen_dispDimButton, (leImage*)&smallSelected2);
};
void event_displayIntensityScreen_dispOffButton_OnPressed(leButtonWidget* btn)
{
    //DEBUG_PRINT("displaymode Off Pressed\r\n");
    if((appData.dispMode & 0x7F) !=  modeOff)
      clrSelectedDisplayMode();
    appData.dispMode &= 0x80;
    appData.dispMode |= modeOff;
    displayIntensityScreen_dispOffButton->fn->setEnabled(displayIntensityScreen_dispOffButton, LE_FALSE);  
    displayIntensityScreen_dispOffButton->fn->setReleasedImage(displayIntensityScreen_dispOffButton, (leImage*)&smallSelected2);
};
void event_displayIntensityScreen_simpleViewOnButton_OnPressed(leButtonWidget* btn)
{
        if(!appData.enableSimpleViewFlg)
        {
            appData.enableSimpleViewFlg = 0x80;
            //appData.dispMode |= 0x80;

            displayIntensityScreen_simpViewOffButton->fn->setEnabled(displayIntensityScreen_simpViewOffButton, LE_TRUE);
            displayIntensityScreen_simpViewOffButton->fn->setPressed(displayIntensityScreen_simpViewOffButton, LE_FALSE);
            displayIntensityScreen_simpleViewOnButton->fn->setEnabled(displayIntensityScreen_simpleViewOnButton, LE_FALSE);
        }
};
void event_displayIntensityScreen_simpViewOffButton_OnPressed(leButtonWidget* btn)
{
      if(appData.enableSimpleViewFlg)
        {
            appData.enableSimpleViewFlg = 0;
            appData.dispMode &= 0x7F;

            displayIntensityScreen_simpViewOffButton->fn->setEnabled(displayIntensityScreen_simpViewOffButton, LE_FALSE);
            displayIntensityScreen_simpleViewOnButton->fn->setEnabled(displayIntensityScreen_simpleViewOnButton, LE_TRUE);
            displayIntensityScreen_simpleViewOnButton->fn->setPressed(displayIntensityScreen_simpleViewOnButton, LE_FALSE);
        }
};
void event_displayIntensityScreen_dispExitButton_OnPressed(leButtonWidget* btn)
{
    legato_showScreen(screenID_mainMenuScreen); 
};


void displayIntensityScreen_OnShow(void)
{
    uint8_t tempDispMode = 0;
    clrSelectedDisplayMode();
    //appData.enableSimpleViewFlg = appData.dispMode & 0x80;
    
    tempDispMode = appData.dispMode & 0x7F;
    switch(tempDispMode) 
    {
        case    mode100 :   {
            displayIntensityScreen_disp100Button->fn->setEnabled(displayIntensityScreen_disp100Button, LE_FALSE);  
            displayIntensityScreen_disp100Button->fn->setReleasedImage(displayIntensityScreen_disp100Button, (leImage*)&smallSelected2);
            break;
        }
        case    mode75 :   {
            displayIntensityScreen_disp75Button->fn->setEnabled(displayIntensityScreen_disp75Button, LE_FALSE);
            displayIntensityScreen_disp75Button->fn->setReleasedImage(displayIntensityScreen_disp75Button, (leImage*)&smallSelected2);
            break;
        }
        case    mode50 :   {
            displayIntensityScreen_disp50Button->fn->setEnabled(displayIntensityScreen_disp50Button, LE_FALSE);
            displayIntensityScreen_disp50Button->fn->setReleasedImage(displayIntensityScreen_disp50Button, (leImage*)&smallSelected2);   
            break;
        }
        case    mode25 :   {
            displayIntensityScreen_disp25Button->fn->setEnabled(displayIntensityScreen_disp25Button, LE_FALSE);
            displayIntensityScreen_disp25Button->fn->setReleasedImage(displayIntensityScreen_disp25Button, (leImage*)&smallSelected2);
            break;
        }
        case    modeDim :   {
            displayIntensityScreen_dispDimButton->fn->setEnabled(displayIntensityScreen_dispDimButton, LE_FALSE);
            displayIntensityScreen_dispDimButton->fn->setReleasedImage(displayIntensityScreen_dispDimButton, (leImage*)&smallSelected2);
            break;
        }
        case    modeOff :   {
            displayIntensityScreen_dispOffButton->fn->setEnabled(displayIntensityScreen_dispOffButton, LE_FALSE);
            displayIntensityScreen_dispOffButton->fn->setReleasedImage(displayIntensityScreen_dispOffButton, (leImage*)&smallSelected2);
            break;
        }
        default :           {
            break;
        }

    }
       // DEBUG_PRINT("simple view flg %d\r\n",appData.enableSimpleViewFlg);       
        if(appData.enableSimpleViewFlg)
        {
            displayIntensityScreen_simpViewOffButton->fn->setEnabled(displayIntensityScreen_simpViewOffButton, LE_TRUE);
            displayIntensityScreen_simpViewOffButton->fn->setPressed(displayIntensityScreen_simpViewOffButton, LE_FALSE);
            displayIntensityScreen_simpleViewOnButton->fn->setEnabled(displayIntensityScreen_simpleViewOnButton, LE_FALSE);
            displayIntensityScreen_simpleViewOnButton->fn->setPressed(displayIntensityScreen_simpleViewOnButton, LE_TRUE);
         //   DEBUG_PRINT("on show simple view ON\r\n");       
        }
        else
        {
            displayIntensityScreen_simpViewOffButton->fn->setEnabled(displayIntensityScreen_simpViewOffButton, LE_FALSE);
            displayIntensityScreen_simpViewOffButton->fn->setPressed(displayIntensityScreen_simpViewOffButton, LE_TRUE);
            displayIntensityScreen_simpleViewOnButton->fn->setEnabled(displayIntensityScreen_simpleViewOnButton, LE_TRUE);
            displayIntensityScreen_simpleViewOnButton->fn->setPressed(displayIntensityScreen_simpleViewOnButton, LE_FALSE);
          //  DEBUG_PRINT("on show simple view OFF\r\n");
        }

};
void displayIntensityScreen_OnHide(void)
{
    //saveDisplaySettings();
    appData.saveDisplayFlg = 1;
};
// </editor-fold>
