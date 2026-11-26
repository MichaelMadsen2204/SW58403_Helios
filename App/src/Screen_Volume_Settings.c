#include "definitions.h" // indeholder app.h, system headers, legato types mm.
#include "gfx/legato/generated/screen/le_gen_screen_volSettingsScreen.h"
#include "ui_globals.h"
#include "app.h"

static leFixedString startLvlString;
static leFixedString maxLvlString;

char            BalanceDisplay[13][20]  =   {"L :|.....:......: R",
                                             "L :.|....:......: R",
                                             "L :..|...:......: R",
                                             "L :...|..:......: R",
                                             "L :....|.:......: R",
                                             "L :.....|:......: R",
                                             "L :......|......: R",
                                             "L :......:|.....: R",
                                             "L :......:.|....: R",
                                             "L :......:..|...: R",
                                             "L :......:...|..: R",
                                             "L :......:....|.: R",
                                             "L :......:.....|: R"};

static leChar legatoStartLvlCharBuffer[8] = {0};
static leChar legatoMaxLvlCharBuffer[8] = {0};
static leChar legatoBalanceBuffer[20] = {0};

// *****************************************************************************
// *****************************************************************************
// Section: Application Volume Settings Screen Functions 
// *****************************************************************************
// *****************************************************************************
// <editor-fold defaultstate="collapsed" desc="Volume Settings Screen Functions">

void updateVolSettingScreen (void)
{
    if (appData.oldStartLvl != appData.startLvl)
    {
        sprintf(cCharBuffer, "%u", appData.startLvl); 
        appData.oldStartLvl = appData.startLvl;
        //convert the character string to leFixedString object
        startLvlString.fn->setFromCStr(&startLvlString, cCharBuffer);    
        //Set counterString string to label
        volSettingsScreen_volSettingCurStartLevelLabel->fn->setString(volSettingsScreen_volSettingCurStartLevelLabel, (leString*)&startLvlString);   
    }
    if (appData.oldMaxLvl != appData.maxLvl)
    {
        sprintf(cCharBuffer, "%u", appData.maxLvl); 
        appData.oldMaxLvl = appData.maxLvl;
        //convert the character string to leFixedString object
        maxLvlString.fn->setFromCStr(&maxLvlString, cCharBuffer);    
        //Set counterString string to label
        volSettingsScreen_volSettingCurMaxLevelLabel->fn->setString(volSettingsScreen_volSettingCurMaxLevelLabel, (leString*)&maxLvlString);   
    }
}


#define STARTLVL_MIN 0
#define STARTLVL_MAX 66
#define MAXLVL_MIN   20
#define MAXLVL_MAX   84

//************* START VOLUME ***********************************************
void event_volSettingsScreen_volSetStartVolPlusBut_OnPressed(leButtonWidget* btn)
{
    if (appData.startLvl < STARTLVL_MAX) {
        appData.startLvl++;
        if (appData.startLvl > appData.maxLvl) {
            appData.maxLvl = appData.startLvl;   // max følger op
        }
    }
}

void event_volSettingsScreen_volSetStartVolMinusBut_OnPressed(leButtonWidget* btn)
{
    if (appData.startLvl > STARTLVL_MIN) {
        appData.startLvl--;
        // Relation max>=start er stadig opfyldt, intet at gøre her
    }
}

//************* MAX VOLUME ***********************************************
void event_volSettingsScreen_volSetMaxVolPlusBut_OnPressed(leButtonWidget* btn)
{
    if (appData.maxLvl < MAXLVL_MAX) {
        appData.maxLvl++;
        // startLvl-constraint (<=66) og relationen er stadig OK
    }
}

void event_volSettingsScreen_volSetMaxVolMinusBut_OnPressed(leButtonWidget* btn)
{
    if (appData.maxLvl > MAXLVL_MIN) {
        appData.maxLvl--;
        if (appData.maxLvl < appData.startLvl) {
            appData.startLvl = appData.maxLvl;   // start følger ned
        }
    }
}

void event_volSettingsScreen_volSetBackToMenuBut_OnPressed(leButtonWidget* btn)
{
    legato_showScreen(screenID_mainMenuScreen); 
};
void event_volSettingsScreen_volSetStartVolMinusBut_OnReleased(leButtonWidget* btn){};
void event_volSettingsScreen_volSetStartVolPlusBut_OnReleased(leButtonWidget* btn){};
void event_volSettingsScreen_volSetMaxVolMinusBut_OnReleased(leButtonWidget* btn){};
void event_volSettingsScreen_volSetMaxVolPlusBut_OnReleased(leButtonWidget* btn){};

void event_volSettingsScreen_balanceLeftBut_OnPressed(leButtonWidget* btn)
{
    if(appData.balance > 0)
        appData.balance--;
    balanceString.fn->setFromCStr(&balanceString,BalanceDisplay[appData.balance]);
    DEBUG_PRINT("balance: %s ", BalanceDisplay[appData.balance]);
    volSettingsScreen_balance->fn->setString(volSettingsScreen_balance,(leString*) &balanceString);
};
void event_volSettingsScreen_balanceLeftBut_OnReleased(leButtonWidget* btn){};
void event_volSettingsScreen_balanceRightBut_OnPressed(leButtonWidget* btn)
{
    if(appData.balance < 12)
        appData.balance++;
    balanceString.fn->setFromCStr(&balanceString,BalanceDisplay[appData.balance]);
    DEBUG_PRINT("balance: %s ", BalanceDisplay[appData.balance]);
    volSettingsScreen_balance->fn->setString(volSettingsScreen_balance,(leString*) &balanceString);

};
void event_volSettingsScreen_balanceRightBut_OnReleased(leButtonWidget* btn){};


void volSettingsScreen_OnShow(void)
{
    DEBUG_PRINT("volSettingsScreen_OnShow\r\n"); //slet
    // opdater indikatorer med aktuelle værdier
    
    
    leFixedString_Constructor(&balanceString, legatoBalanceBuffer, 20);
    balanceString.fn->setFont(&balanceString, leStringTable_GetStringFont(leGetState()->stringTable, stringID_balanceStr, 0)); 
    balanceString.fn->setFromCStr(&balanceString,BalanceDisplay[appData.balance]);
    DEBUG_PRINT("balance: %s ", BalanceDisplay[appData.balance]);
    
    volSettingsScreen_balance->fn->setString(volSettingsScreen_balance,(leString*) &balanceString);
    
    //Create and initialize a legato string object, this string object will be used
    //to construct the string that will be used by the label object for showing on the 
    //screen
    leFixedString_Constructor(&startLvlString, legatoStartLvlCharBuffer, 16);

    //Assign a font to the string object. The font must contain all the glyphs/characters
    //that will be used in the dynamic string. In the case of a numeric counter, it needs
    //to have all the numbers (0-9)
    startLvlString.fn->setFont(&startLvlString, leStringTable_GetStringFont(leGetState()->stringTable, stringID_curStartLevelStr, 0));      
   
    sprintf(cCharBuffer, "%u", appData.startLvl); 
    startLvlString.fn->setFromCStr(&startLvlString, cCharBuffer);  
    volSettingsScreen_volSettingCurStartLevelLabel->fn->setString(volSettingsScreen_volSettingCurStartLevelLabel, (leString*)&startLvlString);   

    ///************************************************************************
 
    //Create and initialize a legato string object, this string object will be used
    //to construct the string that will be used by the label object for showing on the 
    //screen
    leFixedString_Constructor(&maxLvlString, legatoMaxLvlCharBuffer, 16);

    //Assign a font to the string object. The font must contain all the glyphs/characters
    //that will be used in the dynamic string. In the case of a numeric counter, it needs
    //to have all the numbers (0-9)
    maxLvlString.fn->setFont(&maxLvlString, leStringTable_GetStringFont(leGetState()->stringTable, stringID_curStartLevelStr, 0));      
   
    sprintf(cCharBuffer, "%u", appData.maxLvl); 
    maxLvlString.fn->setFromCStr(&maxLvlString, cCharBuffer);  
    volSettingsScreen_volSettingCurMaxLevelLabel->fn->setString(volSettingsScreen_volSettingCurMaxLevelLabel, (leString*)&maxLvlString);   
    appData.state = APP_VOL_SETTING_SCREEN_TASKS;
}; 




void volSettingsScreen_OnHide(void)
{
   //DEBUG_PRINT("volSettingsScreen_OnHide\r\n"); //slet
    appData.state = APP_ACTION_SCREEN_TASKS;
    saveVolumeSettings();   // gem nye værdier i eeProm
}; 

// </editor-fold>
