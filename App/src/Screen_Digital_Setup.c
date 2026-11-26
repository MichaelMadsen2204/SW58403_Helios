#include "definitions.h" // indeholder app.h, system headers, legato types mm.
#include "gfx/legato/generated/screen/le_gen_screen_digitalSetupScreen.h"
#include "ui_globals.h"
#include "app.h"

void updateDigitaleSettingScreen(void)
{
     if(dacData.pcmFilter != dacData.oldPcmFilter)
      {
        dacData.oldPcmFilter = dacData.pcmFilter;
        sprintf(cCharBuffer, "%u", dacData.pcmFilter); 
        pcmFilterString.fn->setFromCStr(&pcmFilterString, cCharBuffer);  
        digitalSetupScreen_curPcmFilterLabel->fn->setString(digitalSetupScreen_curPcmFilterLabel, (leString*)&pcmFilterString);   

        DacUi_SyncPcmFilter_CurrentScreen();
        appData.reqApplyPcmFilter = 1;
      }

}

void event_digitalSetupScreen_dsdLpFilterOnButton_OnPressed(leButtonWidget* btn)
{
    if(!ignoreEvent)
    {
      dacData.dsdLpFilter = 1;
      digitalSetupScreen_dsdLpFilterOffButton->fn->setPressed(digitalSetupScreen_dsdLpFilterOffButton, LE_FALSE);
      digitalSetupScreen_dsdLpFilterOffButton->fn->setEnabled(digitalSetupScreen_dsdLpFilterOffButton, LE_TRUE);
      digitalSetupScreen_dsdLpFilterOnButton->fn->setEnabled(digitalSetupScreen_dsdLpFilterOnButton, LE_FALSE);
      appData.reqApplyDsdLp = 1;
    }    
};
void event_digitalSetupScreen_dsdLpFilterOffButton_OnPressed(leButtonWidget* btn)
{
    if(!ignoreEvent)
    {
      dacData.dsdLpFilter = 0;
      digitalSetupScreen_dsdLpFilterOnButton->fn->setPressed(digitalSetupScreen_dsdLpFilterOnButton, LE_FALSE);
      digitalSetupScreen_dsdLpFilterOnButton->fn->setEnabled(digitalSetupScreen_dsdLpFilterOnButton, LE_TRUE);
      digitalSetupScreen_dsdLpFilterOffButton->fn->setEnabled(digitalSetupScreen_dsdLpFilterOffButton, LE_FALSE);
      appData.reqApplyDsdLp = 1;
    }    
};
void event_digitalSetupScreen_digitalGain0dBButton_OnPressed(leButtonWidget* btn)
{
    if(!ignoreEvent)
    {
      dacData.digiGain = 1;
      digitalSetupScreen_digitalGainMinus6dBButton->fn->setPressed(digitalSetupScreen_digitalGainMinus6dBButton, LE_FALSE);
      digitalSetupScreen_digitalGainMinus6dBButton->fn->setEnabled(digitalSetupScreen_digitalGainMinus6dBButton, LE_TRUE);
      digitalSetupScreen_digitalGain0dBButton->fn->setEnabled(digitalSetupScreen_digitalGain0dBButton, LE_FALSE);
    }
};
void event_digitalSetupScreen_digitalGainMinus6dBButton_OnPressed(leButtonWidget* btn)
{
    if(!ignoreEvent)
    {
      dacData.digiGain = 0;
      digitalSetupScreen_digitalGain0dBButton->fn->setPressed(digitalSetupScreen_digitalGain0dBButton, LE_FALSE);
      digitalSetupScreen_digitalGain0dBButton->fn->setEnabled(digitalSetupScreen_digitalGain0dBButton, LE_TRUE);
      digitalSetupScreen_digitalGainMinus6dBButton->fn->setEnabled(digitalSetupScreen_digitalGainMinus6dBButton, LE_FALSE);
    }    
};
void event_digitalSetupScreen_dsdFilterUpButton_OnPressed(leButtonWidget* btn){};
void event_digitalSetupScreen_dsdFilterDwnButton_OnPressed(leButtonWidget* btn){};

void event_digitalSetupScreen_pcmFilterUpButton_OnPressed(leButtonWidget* btn)
{
    if(dacData.pcmFilter < 7)
        dacData.pcmFilter++;    
};
void event_digitalSetupScreen_pcmFilterDwnButton_OnPressed(leButtonWidget* btn)
{
    if(dacData.pcmFilter > 1)
        dacData.pcmFilter--;    
};
void event_digitalSetupScreen_digitaBackToMenuButton_OnPressed(leButtonWidget* btn)
{
    saveDigitalSetup ();
    appData.state = APP_STATE_IDLE;
    legato_showScreen(screenID_mainMenuScreen);    
};
void digitalSetupScreen_OnShow(void)
{
    appData.state = APP_DIGTAL_SETTING_TASKS;
    dacData.oldPcmFilter = 0xff;
    //Create and initialize a legato string object, this string object will be used
    //to construct the string that will be used by the label object for showing on the 
    //screen
    leFixedString_Constructor(&pcmFilterString, legatoPcmFilterBuffer, 16);

    //Assign a font to the string object. The font must contain all the glyphs/characters
    //that will be used in the dynamic string. In the case of a numeric counter, it needs
    //to have all the numbers (0-9)
    pcmFilterString.fn->setFont(&pcmFilterString, leStringTable_GetStringFont(leGetState()->stringTable, stringID_curPcmFilterString, 0));      
    if(dacData.pcmFilter < 1 || dacData.pcmFilter > 7)
        dacData.pcmFilter = 4;
        
    sprintf(cCharBuffer, "%u", dacData.pcmFilter); 
    pcmFilterString.fn->setFromCStr(&pcmFilterString, cCharBuffer);  
    
    digitalSetupScreen_curPcmFilterLabel->fn->setString(digitalSetupScreen_curPcmFilterLabel, (leString*)&pcmFilterString);   
    
     ignoreEvent = 1;   

    if (dacData.dsdLpFilter)
    {
      digitalSetupScreen_dsdLpFilterOnButton->fn->setPressed(digitalSetupScreen_dsdLpFilterOnButton, LE_TRUE);
      digitalSetupScreen_dsdLpFilterOffButton->fn->setPressed(digitalSetupScreen_dsdLpFilterOffButton, LE_FALSE);      
      digitalSetupScreen_dsdLpFilterOffButton->fn->setEnabled(digitalSetupScreen_dsdLpFilterOffButton, LE_TRUE);
      digitalSetupScreen_dsdLpFilterOnButton->fn->setEnabled(digitalSetupScreen_dsdLpFilterOnButton, LE_FALSE);
      
    }
    else
    {
      digitalSetupScreen_dsdLpFilterOffButton->fn->setPressed(digitalSetupScreen_dsdLpFilterOffButton, LE_TRUE);
      digitalSetupScreen_dsdLpFilterOnButton->fn->setPressed(digitalSetupScreen_dsdLpFilterOnButton, LE_FALSE);      
      digitalSetupScreen_dsdLpFilterOnButton->fn->setEnabled(digitalSetupScreen_dsdLpFilterOnButton, LE_TRUE);
      digitalSetupScreen_dsdLpFilterOffButton->fn->setEnabled(digitalSetupScreen_dsdLpFilterOffButton, LE_FALSE);
    }
    
    if (dacData.digiGain)
    {
      digitalSetupScreen_digitalGain0dBButton->fn->setPressed(digitalSetupScreen_digitalGain0dBButton, LE_TRUE);
      digitalSetupScreen_digitalGainMinus6dBButton->fn->setPressed(digitalSetupScreen_digitalGainMinus6dBButton, LE_FALSE);
      digitalSetupScreen_digitalGainMinus6dBButton->fn->setEnabled(digitalSetupScreen_digitalGainMinus6dBButton, LE_TRUE);
      digitalSetupScreen_digitalGain0dBButton->fn->setEnabled(digitalSetupScreen_digitalGain0dBButton, LE_FALSE);      
    }
    else
    {
      digitalSetupScreen_digitalGainMinus6dBButton->fn->setPressed(digitalSetupScreen_digitalGainMinus6dBButton, LE_TRUE);
      digitalSetupScreen_digitalGain0dBButton->fn->setPressed(digitalSetupScreen_digitalGain0dBButton, LE_FALSE);
      digitalSetupScreen_digitalGain0dBButton->fn->setEnabled(digitalSetupScreen_digitalGain0dBButton, LE_TRUE);
      digitalSetupScreen_digitalGainMinus6dBButton->fn->setEnabled(digitalSetupScreen_digitalGainMinus6dBButton, LE_FALSE);
    }

    ignoreEvent = 0;
};
