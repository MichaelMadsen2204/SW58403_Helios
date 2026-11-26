
#include "definitions.h" // indeholder app.h, system headers, legato types mm.
#include "gfx/legato/generated/screen/le_gen_screen_simpleViewScreen.h"
#include "gfx/legato/generated/screen/le_gen_screen_dacGainSimpleView.h"
#include "gfx/legato/generated/screen/le_gen_screen_filterSimpleView.h"
#include "gfx/legato/generated/screen/le_gen_screen_displaySimpleView.h"
#include "ui_globals.h"
#include "app.h"

static leChar legatoSimpleViewInputCharBuffer[8] = {0};
//static leFixedString simpleViewInputString;
static leChar legatodispModeBuffer[9] = {0};

// *****************************************************************************
// *****************************************************************************
// Section: Application Simple View Screen Functions 
// *****************************************************************************
// *****************************************************************************
// <editor-fold defaultstate="collapsed" desc="Simple View Screen Functions">
void updateSimpleViewScreen(void)
{
    if ((oldLevelValue != appData.curLvl || dacData.dacDigiChangeFlg) && appData.powerOnFlg)
    {
       UpdateVolume();
       dacData.dacDigiChangeFlg = 0;
    }

    if(appData.muteFlg)
       simpleViewScreen_smpleViewMuteKryds->fn->setVisible(simpleViewScreen_smpleViewMuteKryds, LE_TRUE);
    else
       simpleViewScreen_smpleViewMuteKryds->fn->setVisible(simpleViewScreen_smpleViewMuteKryds, LE_FALSE);
    

    if (oldLevelValue != appData.curLvl && legato_getCurrentScreen() == screenID_simpleViewScreen)
    {
            //create the c character array string counter value
            sprintf(cCharBuffer, "%u", appData.curLvl); 
            oldLevelValue = appData.curLvl;
            //convert the character string to leFixedString object
            levelString.fn->setFromCStr(&levelString, cCharBuffer);    
            //Set counterString string to label
            simpleViewScreen_simpleViewCurLevelLabel->fn->setString(simpleViewScreen_simpleViewCurLevelLabel, (leString*)&levelString);  
    }

    if(legato_getCurrentScreen() == screenID_simpleViewScreen)
    {
        if(appData.irInputChangeFlg)
        {
            if(legato_getCurrentScreen() == screenID_simpleViewScreen)
            {
               sprintf(cCharBuffer2, inpNames[appData.curInp]);
               simpleViewInputString.fn-> setFromCStr(&simpleViewInputString, cCharBuffer2);  
            }

            setInput();
            appData.irInputChangeFlg = 0;
        }
        if(AvSelected(appData.avInp, appData.curInp))
          {  
            if(!appData.avFlg)
            {    
              setAvLevel();
              simpleViewScreen_simpleViewCurLevelLabel->fn->setVisible(simpleViewScreen_simpleViewCurLevelLabel,LE_FALSE);
              simpleViewScreen_avLevLabel->fn->setVisible(simpleViewScreen_avLevLabel,LE_TRUE);
            }
            appData.avFlg = 1;  
          }
        else if (appData.avFlg)
        {    
            simpleViewScreen_simpleViewCurLevelLabel->fn->setVisible(simpleViewScreen_simpleViewCurLevelLabel,LE_TRUE);
            simpleViewScreen_avLevLabel->fn->setVisible(simpleViewScreen_avLevLabel,LE_FALSE);
            oldLevelValue = avLevInp;
            appData.avFlg = 0;
        }
    } 
}

void event_simpleViewScreen_simpleViewAnyTouchBut_OnPressed(leButtonWidget* btn)
{
  legato_showScreen(screenID_actionScreen);  
  setBackLightIntensity(0);
  
  //appData.state = APP_ACTION_SCREEN_TASKS;
  if(appData.remoteViewShiftDelayHandle)
     SYS_TIME_TimerDestroy(appData.remoteViewShiftDelayHandle);
};
void simpleViewScreen_OnShow(void)
{
    
    appData.state = APP_SIMPLEVIEW_SCREEN_TASKS;
    leFixedString_Constructor(&simpleViewInputString, legatoSimpleViewInputCharBuffer, 16);
    sprintf(cCharBuffer2, inpNames[appData.curInp]);

    simpleViewInputString.fn->setFont(&simpleViewInputString, leStringTable_GetStringFont(leGetState()->stringTable, stringID_simpleViewInputNameStr, 0));      
    simpleViewInputString.fn-> setFromCStr(&simpleViewInputString, cCharBuffer2); 
    simpleViewScreen_simpleViewInputNameLabel->fn->setString(simpleViewScreen_simpleViewInputNameLabel, (leString*)&simpleViewInputString);   

    //Create and initialize a legato string object, this string object will be used
    //to construct the string that will be used by the label object for showing on the 
    //screen
    leFixedString_Constructor(&levelString, legatoCharBuffer, 16);

    //Assign a font to the string object. The font must contain all the glyphs/characters
    //that will be used in the dynamic string. In the case of a numeric counter, it needs
    //to have all the numbers (0-9)
    levelString.fn->setFont(&levelString, leStringTable_GetStringFont(leGetState()->stringTable, stringID_curLevelStr, 0));      
    
    
    sprintf(cCharBuffer, "%u", appData.curLvl); 
    levelString.fn->setFromCStr(&levelString, cCharBuffer);  

    simpleViewScreen_simpleViewCurLevelLabel->fn->setString(simpleViewScreen_simpleViewCurLevelLabel, (leString*)&levelString);   

    if(!appData.muteFlg)
      simpleViewScreen_smpleViewMuteKryds->fn->setVisible(simpleViewScreen_smpleViewMuteKryds, LE_FALSE);
    else
      simpleViewScreen_smpleViewMuteKryds->fn->setVisible(simpleViewScreen_smpleViewMuteKryds, LE_TRUE);
    appData.avFlg = 0;
    
    if(AvSelected(appData.avInp, appData.curInp))
      {  
        if(!appData.avFlg)
        {    
          setAvLevel();
          simpleViewScreen_simpleViewCurLevelLabel->fn->setVisible(simpleViewScreen_simpleViewCurLevelLabel,LE_FALSE);
          simpleViewScreen_avLevLabel->fn->setVisible(simpleViewScreen_avLevLabel,LE_TRUE);
        }
       // appData.avFlg = 1;  
      }
    else if (appData.avFlg)
    {    
        simpleViewScreen_simpleViewCurLevelLabel->fn->setVisible(simpleViewScreen_simpleViewCurLevelLabel,LE_TRUE);
        simpleViewScreen_avLevLabel->fn->setVisible(simpleViewScreen_avLevLabel,LE_FALSE);
        oldLevelValue = avLevInp;
        appData.avFlg = 0;
    }
    initScreenSwapDelay();
    
    if(appData.curInp > 6)
    {
       appData.ampStatusChangeFlg = 1;
       
    }
         
};
// </editor-fold>


// *****************************************************************************
// *****************************************************************************
// Section: Display Mode Remote View Functions
// *****************************************************************************
// *****************************************************************************

// <editor-fold defaultstate="collapsed" desc="Display Mode Remote View Functions">

void displaySimpleView_OnShow(void)
{
  
  leFixedString_Constructor(&dispModeSimpleViewString, legatodispModeBuffer, 16);
  dispModeSimpleViewString.fn->setFont(&dispModeSimpleViewString, leStringTable_GetStringFont(leGetState()->stringTable, stringID_dispModeStr, 0));  
  //DEBUG_PRINT("dispmode %d\r\n",appData.dispMode);
  dispModeSimpleViewString.fn->setFromCStr(&dispModeSimpleViewString, dispModeStrings[appData.dispMode]);  
  displaySimpleView_dispMode->fn->setString(displaySimpleView_dispMode, (leString*)&dispModeSimpleViewString); //&string_dispModeStr);

}


// *****************************************************************************
// *****************************************************************************
// Section: Filter SImple View Functions
// *****************************************************************************
// *****************************************************************************

// <editor-fold defaultstate="collapsed" desc="Filter Simple View Functions">
void filterSimpleView_OnShow(void)
{
    //DEBUG_PRINT("filterSimpleView_OnShow - dacData.pcmFilter: %d",dacData.pcmFilter);
    appData.state = APP_STATE_IDLE;
    switch(dacData.pcmFilter)
    {
        case    1   :   {
                filterSimpleView_filterNumber->fn->setString(filterSimpleView_filterNumber, (leString*)&string_pcmFilt1_48);
                filterSimpleView_LabelWidget_1->fn->setString(filterSimpleView_LabelWidget_1, (leString*)&string_MinPhase30);
                filterSimpleView_LabelWidget_2->fn->setString(filterSimpleView_LabelWidget_2, (leString*)&string_emtyString);
                break;
        }
        case    2   :   {
                filterSimpleView_filterNumber->fn->setString(filterSimpleView_filterNumber, (leString*)&string_pcmFilt2_48);
                filterSimpleView_LabelWidget_1->fn->setString(filterSimpleView_LabelWidget_1, (leString*)&string_LinPhase30);
                filterSimpleView_LabelWidget_2->fn->setString(filterSimpleView_LabelWidget_2, (leString*)&string_Apodiz30);
                break;
        }
        case    3   :   {
                filterSimpleView_filterNumber->fn->setString(filterSimpleView_filterNumber, (leString*)&string_pcmFilt3_48);
                filterSimpleView_LabelWidget_1->fn->setString(filterSimpleView_LabelWidget_1, (leString*)&string_LinPhase30);
                filterSimpleView_LabelWidget_2->fn->setString(filterSimpleView_LabelWidget_2, (leString*)&string_FastRoll30);
                break;
        }
        case    4   :   {
                filterSimpleView_filterNumber->fn->setString(filterSimpleView_filterNumber, (leString*)&string_pcmFilt4_48);
                filterSimpleView_LabelWidget_1->fn->setString(filterSimpleView_LabelWidget_1, (leString*)&string_LinPhase30);
                filterSimpleView_LabelWidget_2->fn->setString(filterSimpleView_LabelWidget_2, (leString*)&string_SloRoll30);
                break;
        }
        case    5   :   {
                filterSimpleView_filterNumber->fn->setString(filterSimpleView_filterNumber, (leString*)&string_pcmFilt5_48);
                filterSimpleView_LabelWidget_1->fn->setString(filterSimpleView_LabelWidget_1, (leString*)&string_MinPhase30);
                filterSimpleView_LabelWidget_2->fn->setString(filterSimpleView_LabelWidget_2, (leString*)&string_FastRoll30);
                break;
        }
        case    6   :   {
                filterSimpleView_filterNumber->fn->setString(filterSimpleView_filterNumber, (leString*)&string_pcmFilt6_48);
                filterSimpleView_LabelWidget_1->fn->setString(filterSimpleView_LabelWidget_1, (leString*)&string_MinPhase30);
                filterSimpleView_LabelWidget_2->fn->setString(filterSimpleView_LabelWidget_2, (leString*)&string_SloRoll30);
                break;
        }
        case    7   :   {
                filterSimpleView_filterNumber->fn->setString(filterSimpleView_filterNumber, (leString*)&string_pcmFilt7_48);
                filterSimpleView_LabelWidget_1->fn->setString(filterSimpleView_LabelWidget_1, (leString*)&string_MinPhase30);
                filterSimpleView_LabelWidget_2->fn->setString(filterSimpleView_LabelWidget_2, (leString*)&string_SloRollLoDisp30);
                break;
        }
        default : {
            break;
        }
    }

}

// </editor-fold>




void dsdLpSimpleView_OnShow(void)
{
    if(dacData.dsdLpFilter == 1)
      dsdLpSimpleView_onValue->fn->setVisible(dsdLpSimpleView_onValue,LE_TRUE);
    else
      dsdLpSimpleView_onValue->fn->setVisible(dsdLpSimpleView_onValue,LE_FALSE);    
}

void dacGainSimpleView_OnShow(void)
{
    if(dacData.digiGain == 0)
      dacGainSimpleView_gainMinus6dB->fn->setVisible(dacGainSimpleView_gainMinus6dB,LE_TRUE);
    else
      dacGainSimpleView_gainMinus6dB->fn->setVisible(dacGainSimpleView_gainMinus6dB,LE_FALSE);
}


// </editor-fold>


void filterSimpleView_OnHide(void)
{
    appData.state           = appData.prevStateForOverlay;
    appData.uiOverlayActive = 0;
}

void dsdLpSimpleView_OnHide(void)
{
    appData.state           = appData.prevStateForOverlay;
    appData.uiOverlayActive = 0;
}

void dacGainSimpleView_OnHide(void)
{
    appData.state           = appData.prevStateForOverlay;
    appData.uiOverlayActive = 0;
}
