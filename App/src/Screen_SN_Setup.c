#include "definitions.h" // indeholder app.h, system headers, legato types mm.
#include "gfx/legato/generated/screen/le_gen_screen_SN_SET.h"
#include "ui_globals.h"
#include "app.h"


static leFixedString singlesString;
static leFixedString tensString;
static leFixedString hundredsString;
static leFixedString thousandsString;


static char singlesBuffer[8];
static char tensBuffer[8];
static char hundredsBuffer[8];
static char thousandsBuffer[8];

static unsigned int oldSinglesValue = 0;
static unsigned int oldTensValue = 0;
static unsigned int oldHundredsValue = 0;
static unsigned int oldThousandsValue = 0;

static leChar legatoSinglesBuffer[8] = {0};
static leChar legatoTensBuffer[8] = {0};
static leChar legatoHundredsBuffer[8] = {0};
static leChar legatoThousandBuffer[8] = {0};
/******************************************************************************
// *****************************************************************************
// *****************************************************************************
// Section: Serial Number Setup Functions
// *****************************************************************************
// *****************************************************************************/

// <editor-fold defaultstate="collapsed" desc="SN Setup Functions">

void updateSnSetScreen (void)
{
    if (oldSinglesValue != appData.snSingles)
    {
            //create the c character array string counter value
            sprintf(singlesBuffer, "%u", appData.snSingles); 
            oldSinglesValue = appData.snSingles;
            //convert the character string to leFixedString object
            singlesString.fn->setFromCStr(&singlesString, singlesBuffer);    
            //Set counterString string to label
            SN_SET_singles->fn->setString(SN_SET_singles, (leString*)&singlesString);   
    }
  if (oldTensValue != appData.snTens)
    {
            //create the c character array string counter value
            sprintf(tensBuffer, "%u", appData.snTens); 
            oldTensValue = appData.snTens;
            //convert the character string to leFixedString object
            tensString.fn->setFromCStr(&tensString, tensBuffer);    
            //Set counterString string to label
            SN_SET_tens->fn->setString(SN_SET_tens, (leString*)&tensString);   
    }
  if (oldHundredsValue != appData.snHundreds)
    {
            //create the c character array string counter value
            sprintf(hundredsBuffer, "%u", appData.snHundreds); 
            oldHundredsValue = appData.snHundreds;
            //convert the character string to leFixedString object
            hundredsString.fn->setFromCStr(&hundredsString, hundredsBuffer);    
            //Set counterString string to label
            SN_SET_hundreds->fn->setString(SN_SET_hundreds, (leString*)&hundredsString);   
    }
  if (oldThousandsValue != appData.snThousands)
    {
            //create the c character array string counter value
            sprintf(thousandsBuffer, "%u", appData.snThousands); 
            oldThousandsValue = appData.snThousands;
            //convert the character string to leFixedString object
            thousandsString.fn->setFromCStr(&thousandsString, thousandsBuffer);    
            //Set counterString string to label
            SN_SET_thousands->fn->setString(SN_SET_thousands, (leString*)&thousandsString);   
    }
}

void createSN(void)
{
    sprintf(singlesBuffer, "%u", appData.snSingles); 
    sprintf(tensBuffer, "%u", appData.snTens); 
    sprintf(hundredsBuffer, "%u", appData.snHundreds); 
    sprintf(thousandsBuffer, "%u", appData.snThousands); 
    strcpy(serialNumber, "SN: 584");
    strcat(serialNumber, thousandsBuffer);
    strcat(serialNumber, hundredsBuffer);
    strcat(serialNumber, tensBuffer);
    strcat(serialNumber, singlesBuffer);
    //DEBUG_PRINT("%s\r\n",serialNumber);
    strncpy(cSerialNoBuffer, serialNumber, 11);
}

void event_SN_SET_oneUp_OnPressed(leButtonWidget* btn)
{
  if(appData.snSingles < 9)
      appData.snSingles++;
    
}
void event_SN_SET_oneDwn_OnPressed(leButtonWidget* btn)
{
  if(appData.snSingles >= 1)
      appData.snSingles--;
    
}
void event_SN_SET_tenUp_OnPressed(leButtonWidget* btn)
{
  if(appData.snTens < 9)
      appData.snTens++;
    
}
void event_SN_SET_tenDwn_OnPressed(leButtonWidget* btn)
{
  if(appData.snTens >= 1)
      appData.snTens--;
    
}
void event_SN_SET_hundredUp_OnPressed(leButtonWidget* btn)
{
  if(appData.snHundreds < 9)
      appData.snHundreds++;
    
}
void event_SN_SET_hundredDwn_OnPressed(leButtonWidget* btn)
{
  if(appData.snHundreds >= 1)
      appData.snHundreds--;
    
}
void event_SN_SET_thousandUp_OnPressed(leButtonWidget* btn)
{
  if(appData.snThousands < 9)
      appData.snThousands++;
    
}
void event_SN_SET_thousandDwn_OnPressed(leButtonWidget* btn)
{
  if(appData.snThousands >= 1)
      appData.snThousands--;
}
void event_SN_SET_save_OnPressed(leButtonWidget* btn)
{
    /// Write SN to eeprom
    saveSNToEEProm();
    
    appData.state = APP_ACTION_SCREEN_TASKS;
    legato_showScreen(screenID_actionScreen);
}

// Screen Events:
void SN_SET_OnShow(void)
{
     getSNFromEEProm();
     appData.state = APP_SN_SET_SCREEN_TASKS;
     createSN();

     leFixedString_Constructor(&thousandsString, legatoThousandBuffer, 6);
     thousandsString.fn->setFont(&thousandsString, leStringTable_GetStringFont(leGetState()->stringTable, stringID_sn_thousands, 0));      
     //sprintf(thousandsBuffer, "%u", appData.snThousands); 
     thousandsString.fn->setFromCStr(&thousandsString, thousandsBuffer);  
     SN_SET_thousands->fn->setString(SN_SET_thousands, (leString*)&thousandsString);   
     
     leFixedString_Constructor(&hundredsString, legatoHundredsBuffer, 6);
     hundredsString.fn->setFont(&hundredsString, leStringTable_GetStringFont(leGetState()->stringTable, stringID_sn_hundreds, 0));      
     //sprintf(hundredsBuffer, "%u", appData.snHundreds); 
     hundredsString.fn->setFromCStr(&hundredsString, hundredsBuffer);  
     SN_SET_hundreds->fn->setString(SN_SET_hundreds, (leString*)&hundredsString);   
     
     leFixedString_Constructor(&tensString, legatoTensBuffer, 6);
     tensString.fn->setFont(&tensString, leStringTable_GetStringFont(leGetState()->stringTable, stringID_sn_tens, 0));      
     //sprintf(tensBuffer, "%u", appData.snTens); 
     tensString.fn->setFromCStr(&tensString, tensBuffer);  
     SN_SET_tens->fn->setString(SN_SET_tens, (leString*)&tensString);   

     leFixedString_Constructor(&singlesString, legatoSinglesBuffer, 6);
     singlesString.fn->setFont(&singlesString, leStringTable_GetStringFont(leGetState()->stringTable, stringID_sn_singles, 0));      
     //sprintf(singlesBuffer, "%u", appData.snSingles); 
     singlesString.fn->setFromCStr(&singlesString, singlesBuffer);  
     SN_SET_singles->fn->setString(SN_SET_singles, (leString*)&singlesString);   



     
     DEBUG_PRINT("\r\nSing: %s\r\n",singlesBuffer);
     DEBUG_PRINT("Tens: %s\r\n",tensBuffer);
     DEBUG_PRINT("Hun: %s\r\n",hundredsBuffer);
     DEBUG_PRINT("Thou: %s\r\n",thousandsBuffer);
     
     
}

// </editor-fold>
