#include "definitions.h" // indeholder app.h, system headers, legato types mm.
#include "gfx/legato/generated/screen/le_gen_screen_inpLvlMatchScreen.h" 
#include "ui_globals.h"
#include "app.h"

static leFixedString lvlMatchValueStr1;
static leFixedString lvlMatchValueStr2;
static leFixedString lvlMatchValueStr3;
static leFixedString lvlMatchValueStr4;
static leFixedString lvlMatchValueStr5;
static leFixedString lvlMatchValueStr6;

static leChar legatoInpLvlMatchBuffer1[9] = {0};
static leChar legatoInpLvlMatchBuffer2[9] = {0};
static leChar legatoInpLvlMatchBuffer3[9] = {0};
static leChar legatoInpLvlMatchBuffer4[9] = {0};
static leChar legatoInpLvlMatchBuffer5[9] = {0};
static leChar legatoInpLvlMatchBuffer6[9] = {0};

// *****************************************************************************
// *****************************************************************************
// Section: Input Level Match Screen Functions 
// *****************************************************************************
// *****************************************************************************


// <editor-fold defaultstate="collapsed" desc="Input Level Match Screen Functions">
void updateInpLvlMatchScreen(void)
{
            if (appData.oldInpSensValue != appData.inpSens[appData.inpToLvlMatch])
            {
                sprintf(cCharBuffer, "%u", appData.inpSens[appData.inpToLvlMatch]); 
                appData.oldInpSensValue = appData.inpSens[appData.inpToLvlMatch];
                switch(appData.inpToLvlMatch)
                {
                    case    1   :   {
                                        sprintf(cCharBuffer, "+%u dB", appData.inpSens[1]); 
                                        lvlMatchValueStr1.fn->setFromCStr(&lvlMatchValueStr1, cCharBuffer);  
                                        inpLvlMatchScreen_inpLvlMatchValue_1->fn->setString(inpLvlMatchScreen_inpLvlMatchValue_1, (leString*)&lvlMatchValueStr1);                     
                                        break;   
                                    }
                    case    2   :   {
                                        sprintf(cCharBuffer, "+%u dB", appData.inpSens[2]); 
                                        lvlMatchValueStr2.fn->setFromCStr(&lvlMatchValueStr2, cCharBuffer);  
                                        inpLvlMatchScreen_inpLvlMatchValue_2->fn->setString(inpLvlMatchScreen_inpLvlMatchValue_2, (leString*)&lvlMatchValueStr2);                     
                                        break;   
                                    }
                    case    3   :   {
                                        sprintf(cCharBuffer, "+%u dB", appData.inpSens[3]); 
                                        lvlMatchValueStr3.fn->setFromCStr(&lvlMatchValueStr3, cCharBuffer);  
                                        inpLvlMatchScreen_inpLvlMatchValue_3->fn->setString(inpLvlMatchScreen_inpLvlMatchValue_3, (leString*)&lvlMatchValueStr3);                     
                                        break;   
                                    }
                    case    4   :   {
                                        sprintf(cCharBuffer, "+%u dB", appData.inpSens[4]); 
                                        lvlMatchValueStr4.fn->setFromCStr(&lvlMatchValueStr4, cCharBuffer);  
                                        inpLvlMatchScreen_inpLvlMatchValue_4->fn->setString(inpLvlMatchScreen_inpLvlMatchValue_4, (leString*)&lvlMatchValueStr4);                     
                                        break;   
                                    }
                    case    5   :   {
                                        sprintf(cCharBuffer, "+%u dB", appData.inpSens[5]); 
                                        lvlMatchValueStr5.fn->setFromCStr(&lvlMatchValueStr5, cCharBuffer);  
                                        inpLvlMatchScreen_inpLvlMatchValue_5->fn->setString(inpLvlMatchScreen_inpLvlMatchValue_5, (leString*)&lvlMatchValueStr5);   
                                        break;   
                                    }
                    case    6   :   {
                                        sprintf(cCharBuffer, "+%u dB", appData.inpSens[6]); 
                                        lvlMatchValueStr6.fn->setFromCStr(&lvlMatchValueStr6, cCharBuffer);  
                                        inpLvlMatchScreen_inpLvlMatchValue_6->fn->setString(inpLvlMatchScreen_inpLvlMatchValue_6, (leString*)&lvlMatchValueStr6);   
                                        break;   
                                    }

                }
            }  
}

void clrSelectedInputToLvlMatch(void)
{
    inpLvlMatchScreen_inpBut_1->fn->setPressed(inpLvlMatchScreen_inpBut_1, LE_FALSE);
    inpLvlMatchScreen_inpBut_2->fn->setPressed(inpLvlMatchScreen_inpBut_2, LE_FALSE);
    inpLvlMatchScreen_inpBut_3->fn->setPressed(inpLvlMatchScreen_inpBut_3, LE_FALSE);
    inpLvlMatchScreen_inpBut_4->fn->setPressed(inpLvlMatchScreen_inpBut_4, LE_FALSE);
    inpLvlMatchScreen_inpBut_5->fn->setPressed(inpLvlMatchScreen_inpBut_5, LE_FALSE);
    inpLvlMatchScreen_inpBut_6->fn->setPressed(inpLvlMatchScreen_inpBut_6, LE_FALSE);
      
    inpLvlMatchScreen_inpBut_1->fn->setEnabled(inpLvlMatchScreen_inpBut_1, LE_TRUE);
    inpLvlMatchScreen_inpBut_2->fn->setEnabled(inpLvlMatchScreen_inpBut_2, LE_TRUE);
    inpLvlMatchScreen_inpBut_3->fn->setEnabled(inpLvlMatchScreen_inpBut_3, LE_TRUE);
    inpLvlMatchScreen_inpBut_4->fn->setEnabled(inpLvlMatchScreen_inpBut_4, LE_TRUE);
    inpLvlMatchScreen_inpBut_5->fn->setEnabled(inpLvlMatchScreen_inpBut_5, LE_TRUE);
    inpLvlMatchScreen_inpBut_6->fn->setEnabled(inpLvlMatchScreen_inpBut_6, LE_TRUE);
  
    inpLvlMatchScreen_inpBut_1->fn->setReleasedImage(inpLvlMatchScreen_inpBut_1, (leImage*)&smallNotSelected3);
    inpLvlMatchScreen_inpBut_2->fn->setReleasedImage(inpLvlMatchScreen_inpBut_2, (leImage*)&smallNotSelected3); 
    inpLvlMatchScreen_inpBut_3->fn->setReleasedImage(inpLvlMatchScreen_inpBut_3, (leImage*)&smallNotSelected3);
    inpLvlMatchScreen_inpBut_4->fn->setReleasedImage(inpLvlMatchScreen_inpBut_4, (leImage*)&smallNotSelected3);
    inpLvlMatchScreen_inpBut_5->fn->setReleasedImage(inpLvlMatchScreen_inpBut_5, (leImage*)&smallNotSelected3);
    inpLvlMatchScreen_inpBut_6->fn->setReleasedImage(inpLvlMatchScreen_inpBut_6, (leImage*)&smallNotSelected3);
  }

void event_inpLvlMatchScreen_inpBut_1_OnPressed(leButtonWidget* btn)
{
    if(!ignoreEvent)
    {
     if(appData.inpToLvlMatch != 1)
      clrSelectedInputToLvlMatch();
    appData.inpToLvlMatch = 1;
    inpLvlMatchScreen_inpBut_1->fn->setEnabled(inpLvlMatchScreen_inpBut_1, LE_FALSE);  
    inpLvlMatchScreen_inpBut_1->fn->setReleasedImage(inpLvlMatchScreen_inpBut_1, (leImage*)&smallSelected2);
    }
};
void event_inpLvlMatchScreen_inpBut_2_OnPressed(leButtonWidget* btn)
{
    if(!ignoreEvent)
    {
    if(appData.inpToLvlMatch != 2)
      clrSelectedInputToLvlMatch();
    appData.inpToLvlMatch = 2;
    inpLvlMatchScreen_inpBut_2->fn->setEnabled(inpLvlMatchScreen_inpBut_2, LE_FALSE); 
    inpLvlMatchScreen_inpBut_2->fn->setReleasedImage(inpLvlMatchScreen_inpBut_2, (leImage*)&smallSelected2);
    }
};
void event_inpLvlMatchScreen_inpBut_3_OnPressed(leButtonWidget* btn)
{
    if(!ignoreEvent)
    {
    if(appData.inpToLvlMatch != 3)
      clrSelectedInputToLvlMatch();
    appData.inpToLvlMatch = 3;
    inpLvlMatchScreen_inpBut_3->fn->setEnabled(inpLvlMatchScreen_inpBut_3, LE_FALSE);  
    inpLvlMatchScreen_inpBut_3->fn->setReleasedImage(inpLvlMatchScreen_inpBut_3, (leImage*)&smallSelected2);
    }
};
void event_inpLvlMatchScreen_inpBut_4_OnPressed(leButtonWidget* btn)
{
    if(!ignoreEvent)
    {
    
    if(appData.inpToLvlMatch != 4)
      clrSelectedInputToLvlMatch();
    appData.inpToLvlMatch = 4;
    inpLvlMatchScreen_inpBut_4->fn->setEnabled(inpLvlMatchScreen_inpBut_4, LE_FALSE); 
    inpLvlMatchScreen_inpBut_4->fn->setReleasedImage(inpLvlMatchScreen_inpBut_4, (leImage*)&smallSelected2);
    }    
};
void event_inpLvlMatchScreen_inpBut_5_OnPressed(leButtonWidget* btn)
{
    if(!ignoreEvent)
    {
    
    if(appData.inpToLvlMatch != 5)
      clrSelectedInputToLvlMatch();
    appData.inpToLvlMatch = 5;
    inpLvlMatchScreen_inpBut_5->fn->setEnabled(inpLvlMatchScreen_inpBut_5, LE_FALSE); 
    inpLvlMatchScreen_inpBut_5->fn->setReleasedImage(inpLvlMatchScreen_inpBut_5, (leImage*)&smallSelected2);
    }    
};
void event_inpLvlMatchScreen_inpBut_6_OnPressed(leButtonWidget* btn)
{
    if(!ignoreEvent)
    {
    
    if(appData.inpToLvlMatch != 6)
      clrSelectedInputToLvlMatch();
    appData.inpToLvlMatch = 6;
    inpLvlMatchScreen_inpBut_6->fn->setEnabled(inpLvlMatchScreen_inpBut_6, LE_FALSE); 
    inpLvlMatchScreen_inpBut_6->fn->setReleasedImage(inpLvlMatchScreen_inpBut_6, (leImage*)&smallSelected2);
    }    
};

void event_inpLvlMatchScreen_inpLvlMatchPlusBut_OnPressed(leButtonWidget* btn)
{
   if(appData.inpSens[appData.inpToLvlMatch] < 8)
      appData.inpSens[appData.inpToLvlMatch] = appData.inpSens[appData.inpToLvlMatch] + 1;  
 
};
void event_inpLvlMatchScreen_inpLvlMatchPlusBut_OnReleased(leButtonWidget* btn){};
void event_inpLvlMatchScreen_inpLvlMatchMinusBut_OnPressed(leButtonWidget* btn)
{
   if(appData.inpSens[appData.inpToLvlMatch] >= 1)
      appData.inpSens[appData.inpToLvlMatch] = appData.inpSens[appData.inpToLvlMatch] - 1;  
};
void event_inpLvlMatchScreen_inpLvlMatchMinusBut_OnReleased(leButtonWidget* btn){};
void event_inpLvlMatchScreen_inpSenseBackToMenuBut_OnPressed(leButtonWidget* btn)
{
    legato_showScreen(screenID_mainMenuScreen);  
};
void inpLvlMatchScreen_OnShow(void)
{
    inpLvlMatchScreen_inpBut_1->fn->setString(inpLvlMatchScreen_inpBut_1, (leString*)&inp1Str);   
    inpLvlMatchScreen_inpBut_2->fn->setString(inpLvlMatchScreen_inpBut_2, (leString*)&inp2Str);   
    inpLvlMatchScreen_inpBut_3->fn->setString(inpLvlMatchScreen_inpBut_3, (leString*)&inp3Str);   
    inpLvlMatchScreen_inpBut_4->fn->setString(inpLvlMatchScreen_inpBut_4, (leString*)&inp4Str);   
    inpLvlMatchScreen_inpBut_5->fn->setString(inpLvlMatchScreen_inpBut_5, (leString*)&inp5Str);   
    inpLvlMatchScreen_inpBut_6->fn->setString(inpLvlMatchScreen_inpBut_6, (leString*)&inp6Str);   
    
    if(!appData.phonoRegiFlg)
    {
        inpLvlMatchScreen_inpBut_6->fn->setVisible(inpLvlMatchScreen_inpBut_6, LE_FALSE);
         inpLvlMatchScreen_inpLvlMatchValue_6->fn->setVisible(inpLvlMatchScreen_inpLvlMatchValue_6,LE_FALSE);
    }
    
    leFixedString_Constructor(&lvlMatchValueStr1, legatoInpLvlMatchBuffer1, 16);
    lvlMatchValueStr1.fn->setFont(&lvlMatchValueStr1, leStringTable_GetStringFont(leGetState()->stringTable, stringID_inpLvlMatch_1, 0));      
    sprintf(cCharBuffer, "+%u dB", appData.inpSens[1]); 
    lvlMatchValueStr1.fn->setFromCStr(&lvlMatchValueStr1, cCharBuffer);  
    inpLvlMatchScreen_inpLvlMatchValue_1->fn->setString(inpLvlMatchScreen_inpLvlMatchValue_1, (leString*)&lvlMatchValueStr1);  

    leFixedString_Constructor(&lvlMatchValueStr2, legatoInpLvlMatchBuffer2, 16);
    lvlMatchValueStr2.fn->setFont(&lvlMatchValueStr2, leStringTable_GetStringFont(leGetState()->stringTable, stringID_inpLvlMatch_2, 0));      
    sprintf(cCharBuffer, "+%u dB", appData.inpSens[2]); 
    lvlMatchValueStr2.fn->setFromCStr(&lvlMatchValueStr2, cCharBuffer);  
    inpLvlMatchScreen_inpLvlMatchValue_2->fn->setString(inpLvlMatchScreen_inpLvlMatchValue_2, (leString*)&lvlMatchValueStr2);  

    leFixedString_Constructor(&lvlMatchValueStr3, legatoInpLvlMatchBuffer3, 16);
    lvlMatchValueStr3.fn->setFont(&lvlMatchValueStr3, leStringTable_GetStringFont(leGetState()->stringTable, stringID_inpLvlMatch_3, 0));      
    sprintf(cCharBuffer, "+%u dB", appData.inpSens[3]); 
    lvlMatchValueStr3.fn->setFromCStr(&lvlMatchValueStr3, cCharBuffer);  
    inpLvlMatchScreen_inpLvlMatchValue_3->fn->setString(inpLvlMatchScreen_inpLvlMatchValue_3, (leString*)&lvlMatchValueStr3);  

    leFixedString_Constructor(&lvlMatchValueStr4, legatoInpLvlMatchBuffer4, 16);
    lvlMatchValueStr4.fn->setFont(&lvlMatchValueStr4, leStringTable_GetStringFont(leGetState()->stringTable, stringID_inpLvlMatch_4, 0));      
    sprintf(cCharBuffer, "+%u dB", appData.inpSens[4]); 
    lvlMatchValueStr4.fn->setFromCStr(&lvlMatchValueStr4, cCharBuffer);  
    inpLvlMatchScreen_inpLvlMatchValue_4->fn->setString(inpLvlMatchScreen_inpLvlMatchValue_4, (leString*)&lvlMatchValueStr4);  

    leFixedString_Constructor(&lvlMatchValueStr5, legatoInpLvlMatchBuffer5, 16);
    lvlMatchValueStr5.fn->setFont(&lvlMatchValueStr5, leStringTable_GetStringFont(leGetState()->stringTable, stringID_inpLvlMatch_5, 0));      
    sprintf(cCharBuffer, "+%u dB", appData.inpSens[5]); 
    lvlMatchValueStr5.fn->setFromCStr(&lvlMatchValueStr5, cCharBuffer);  
    inpLvlMatchScreen_inpLvlMatchValue_5->fn->setString(inpLvlMatchScreen_inpLvlMatchValue_5, (leString*)&lvlMatchValueStr5);  
    
    leFixedString_Constructor(&lvlMatchValueStr6, legatoInpLvlMatchBuffer6, 16);
    lvlMatchValueStr6.fn->setFont(&lvlMatchValueStr6, leStringTable_GetStringFont(leGetState()->stringTable, stringID_inpLvlMatch_6, 0));      
    sprintf(cCharBuffer, "+%u dB", appData.inpSens[6]); 
    lvlMatchValueStr6.fn->setFromCStr(&lvlMatchValueStr6, cCharBuffer);  
    inpLvlMatchScreen_inpLvlMatchValue_6->fn->setString(inpLvlMatchScreen_inpLvlMatchValue_6, (leString*)&lvlMatchValueStr6);  

    appData.inpToLvlMatch = 1;
    appData.state = APP_INPUT_LVL_MATCH_SCREEN_TASKS;
};
void inpLvlMatchScreen_OnHide(void)
{
   saveInpLvlMatchValues();
   appData.state = APP_ACTION_SCREEN_TASKS;
};

// </editor-fold>

