#include "definitions.h" // indeholder app.h, system headers, legato types mm.
#include "gfx/legato/generated/screen/le_gen_screen_renameInputsScreen.h"
#include "ui_globals.h"
#include "app.h"


static uint8_t cCnt = 0;



// *****************************************************************************
// *****************************************************************************
// Section: Application Rename Inputs Screen Functions 
// *****************************************************************************
// *****************************************************************************
// <editor-fold defaultstate="collapsed" desc="Rename Inputs Screen Functions">
void clrSelectedRenameInput(void)
{
    renameInputsScreen_selInp1ButWdgt->fn->setPressed(renameInputsScreen_selInp1ButWdgt, LE_FALSE);
    renameInputsScreen_selInp1ButWdgt->fn->setEnabled(renameInputsScreen_selInp1ButWdgt,LE_TRUE);
    
    renameInputsScreen_selInp2ButWdgt->fn->setPressed(renameInputsScreen_selInp2ButWdgt, LE_FALSE);
    renameInputsScreen_selInp2ButWdgt->fn->setEnabled(renameInputsScreen_selInp2ButWdgt,LE_TRUE);
    
    renameInputsScreen_selInp3ButWdgt->fn->setPressed(renameInputsScreen_selInp3ButWdgt, LE_FALSE);
    renameInputsScreen_selInp3ButWdgt->fn->setEnabled(renameInputsScreen_selInp3ButWdgt,LE_TRUE);
    
    renameInputsScreen_selInp4ButWdgt->fn->setPressed(renameInputsScreen_selInp4ButWdgt, LE_FALSE);
    renameInputsScreen_selInp4ButWdgt->fn->setEnabled(renameInputsScreen_selInp4ButWdgt,LE_TRUE);
    
    renameInputsScreen_selInp5ButWdgt->fn->setPressed(renameInputsScreen_selInp5ButWdgt, LE_FALSE);
    renameInputsScreen_selInp5ButWdgt->fn->setEnabled(renameInputsScreen_selInp5ButWdgt,LE_TRUE);
    
    renameInputsScreen_selInp6ButWdgt->fn->setPressed(renameInputsScreen_selInp6ButWdgt, LE_FALSE);
    renameInputsScreen_selInp6ButWdgt->fn->setEnabled(renameInputsScreen_selInp6ButWdgt,LE_TRUE);
    
    renameInputsScreen_selInp7ButWdgt->fn->setPressed(renameInputsScreen_selInp7ButWdgt, LE_FALSE);
    renameInputsScreen_selInp7ButWdgt->fn->setEnabled(renameInputsScreen_selInp7ButWdgt,LE_TRUE);
    
    renameInputsScreen_selInp8ButWdgt->fn->setPressed(renameInputsScreen_selInp8ButWdgt, LE_FALSE);
    renameInputsScreen_selInp8ButWdgt->fn->setEnabled(renameInputsScreen_selInp8ButWdgt,LE_TRUE);
    
    renameInputsScreen_selInp9ButWdgt->fn->setPressed(renameInputsScreen_selInp9ButWdgt, LE_FALSE);
    renameInputsScreen_selInp9ButWdgt->fn->setEnabled(renameInputsScreen_selInp9ButWdgt,LE_TRUE);
    
    renameInputsScreen_selInp10ButWdgt->fn->setPressed(renameInputsScreen_selInp10ButWdgt, LE_FALSE);
    renameInputsScreen_selInp10ButWdgt->fn->setEnabled(renameInputsScreen_selInp10ButWdgt,LE_TRUE);

    renameInputsScreen_selInp11ButWdgt->fn->setPressed(renameInputsScreen_selInp11ButWdgt, LE_FALSE);
    renameInputsScreen_selInp11ButWdgt->fn->setEnabled(renameInputsScreen_selInp11ButWdgt,LE_TRUE);
    
    renameInputsScreen_selInp1ButWdgt->fn->setReleasedImage(renameInputsScreen_selInp1ButWdgt, (leImage*)&smallNotSelected3);    
    renameInputsScreen_selInp2ButWdgt->fn->setReleasedImage(renameInputsScreen_selInp2ButWdgt, (leImage*)&smallNotSelected3);
    renameInputsScreen_selInp3ButWdgt->fn->setReleasedImage(renameInputsScreen_selInp3ButWdgt, (leImage*)&smallNotSelected3);
    renameInputsScreen_selInp4ButWdgt->fn->setReleasedImage(renameInputsScreen_selInp4ButWdgt, (leImage*)&smallNotSelected3);
    renameInputsScreen_selInp5ButWdgt->fn->setReleasedImage(renameInputsScreen_selInp5ButWdgt, (leImage*)&smallNotSelected3);
    renameInputsScreen_selInp6ButWdgt->fn->setReleasedImage(renameInputsScreen_selInp6ButWdgt, (leImage*)&smallNotSelected3);
    renameInputsScreen_selInp7ButWdgt->fn->setReleasedImage(renameInputsScreen_selInp7ButWdgt, (leImage*)&smallNotSelected3);
    renameInputsScreen_selInp8ButWdgt->fn->setReleasedImage(renameInputsScreen_selInp8ButWdgt, (leImage*)&smallNotSelected3);
    renameInputsScreen_selInp9ButWdgt->fn->setReleasedImage(renameInputsScreen_selInp9ButWdgt, (leImage*)&smallNotSelected3);
    renameInputsScreen_selInp10ButWdgt->fn->setReleasedImage(renameInputsScreen_selInp10ButWdgt, (leImage*)&smallNotSelected3);
    renameInputsScreen_selInp11ButWdgt->fn->setReleasedImage(renameInputsScreen_selInp11ButWdgt, (leImage*)&smallNotSelected3);
    
}
void setSelectedInputToRename (void)
{
    switch(appData.inpToRename)
    {
        case 1    : {
            renameInputsScreen_selInp1ButWdgt->fn->setEnabled(renameInputsScreen_selInp1ButWdgt, LE_FALSE); 
            renameInputsScreen_selInp1ButWdgt->fn->setReleasedImage(renameInputsScreen_selInp1ButWdgt, (leImage*)&smallSelected2);    
            break;
        }
        case 2    : {
            renameInputsScreen_selInp2ButWdgt->fn->setEnabled(renameInputsScreen_selInp2ButWdgt, LE_FALSE); 
            renameInputsScreen_selInp2ButWdgt->fn->setReleasedImage(renameInputsScreen_selInp2ButWdgt, (leImage*)&smallSelected2);    
            break;
        }
        case 3    : {
            renameInputsScreen_selInp3ButWdgt->fn->setEnabled(renameInputsScreen_selInp3ButWdgt, LE_FALSE); 
            renameInputsScreen_selInp3ButWdgt->fn->setReleasedImage(renameInputsScreen_selInp3ButWdgt, (leImage*)&smallSelected2);    
            break;
        }
        case 4    : {
            renameInputsScreen_selInp4ButWdgt->fn->setEnabled(renameInputsScreen_selInp4ButWdgt, LE_FALSE); 
            renameInputsScreen_selInp4ButWdgt->fn->setReleasedImage(renameInputsScreen_selInp4ButWdgt, (leImage*)&smallSelected2);    
            break;
        }
        case 5    : {
            renameInputsScreen_selInp5ButWdgt->fn->setEnabled(renameInputsScreen_selInp5ButWdgt, LE_FALSE); 
            renameInputsScreen_selInp5ButWdgt->fn->setReleasedImage(renameInputsScreen_selInp5ButWdgt, (leImage*)&smallSelected2);    
            break;
        }
        case 6    : {
            renameInputsScreen_selInp6ButWdgt->fn->setEnabled(renameInputsScreen_selInp6ButWdgt, LE_FALSE); 
            renameInputsScreen_selInp6ButWdgt->fn->setReleasedImage(renameInputsScreen_selInp6ButWdgt, (leImage*)&smallSelected2);    
            break;
        }
        case 7    : {
            renameInputsScreen_selInp7ButWdgt->fn->setEnabled(renameInputsScreen_selInp7ButWdgt, LE_FALSE); 
            renameInputsScreen_selInp7ButWdgt->fn->setReleasedImage(renameInputsScreen_selInp7ButWdgt, (leImage*)&smallSelected2);    
            break;
        }
        case 8    : {
            renameInputsScreen_selInp8ButWdgt->fn->setEnabled(renameInputsScreen_selInp8ButWdgt, LE_FALSE); 
            renameInputsScreen_selInp8ButWdgt->fn->setReleasedImage(renameInputsScreen_selInp8ButWdgt, (leImage*)&smallSelected2);    
            break;
        }
        case 9    : {
            renameInputsScreen_selInp9ButWdgt->fn->setEnabled(renameInputsScreen_selInp9ButWdgt, LE_FALSE); 
            renameInputsScreen_selInp9ButWdgt->fn->setReleasedImage(renameInputsScreen_selInp9ButWdgt, (leImage*)&smallSelected2);    
            break;
        }
        case 10    : {
            renameInputsScreen_selInp10ButWdgt->fn->setEnabled(renameInputsScreen_selInp10ButWdgt, LE_FALSE); 
            renameInputsScreen_selInp10ButWdgt->fn->setReleasedImage(renameInputsScreen_selInp10ButWdgt, (leImage*)&smallSelected2);    
            break;
        }
        case 11    : {
            renameInputsScreen_selInp11ButWdgt->fn->setEnabled(renameInputsScreen_selInp11ButWdgt, LE_FALSE); 
            renameInputsScreen_selInp11ButWdgt->fn->setReleasedImage(renameInputsScreen_selInp11ButWdgt, (leImage*)&smallSelected2);    
            break;
        }
    }
}

void event_renameInputsScreen_BackToMenuButttonWdgt_OnReleased(leButtonWidget* btn)
{
   legato_showScreen(screenID_mainMenuScreen);   
};





void event_renameInputsScreen_renameButtonWdgt_OnPressed(leButtonWidget* btn)
{
    cCnt = 0;
    legato_showScreen(screenID_qwertyScreen);
};

void event_renameInputsScreen_selInp1ButWdgt_OnPressed(leButtonWidget* btn)
{
    //DEBUG_PRINT("event_renameInputsScreen_selInp1ButWdgt_OnPressed\r\n");
    if(appData.inpToRename != 1)
      clrSelectedRenameInput();
    appData.inpToRename = 1;
    renameInputsScreen_selInp1ButWdgt->fn->setEnabled(renameInputsScreen_selInp1ButWdgt, LE_FALSE); 
    renameInputsScreen_selInp1ButWdgt->fn->setReleasedImage(renameInputsScreen_selInp1ButWdgt, (leImage*)&smallSelected2);
};
void event_renameInputsScreen_selInp2ButWdgt_OnPressed(leButtonWidget* btn)
{
   //DEBUG_PRINT("event_renameInputsScreen_selInp2ButWdgt_OnPressed\r\n");
    if(appData.inpToRename != 2)
      clrSelectedRenameInput();
    appData.inpToRename = 2;
    renameInputsScreen_selInp2ButWdgt->fn->setEnabled(renameInputsScreen_selInp2ButWdgt, LE_FALSE); 
    renameInputsScreen_selInp2ButWdgt->fn->setReleasedImage(renameInputsScreen_selInp2ButWdgt, (leImage*)&smallSelected2);
};
void event_renameInputsScreen_selInp3ButWdgt_OnPressed(leButtonWidget* btn)
{
   //DEBUG_PRINT("event_renameInputsScreen_selInp3ButWdgt_OnPressed\r\n");
    if(appData.inpToRename != 3)
      clrSelectedRenameInput();
    appData.inpToRename = 3;
    renameInputsScreen_selInp3ButWdgt->fn->setEnabled(renameInputsScreen_selInp3ButWdgt, LE_FALSE); 
    renameInputsScreen_selInp3ButWdgt->fn->setReleasedImage(renameInputsScreen_selInp3ButWdgt, (leImage*)&smallSelected2);
};
void event_renameInputsScreen_selInp4ButWdgt_OnPressed(leButtonWidget* btn)
{
    //DEBUG_PRINT("event_renameInputsScreen_selInp4ButWdgt_OnPressed\r\n");
    if(appData.inpToRename != 4)
      clrSelectedRenameInput();
    appData.inpToRename = 4;
    renameInputsScreen_selInp4ButWdgt->fn->setEnabled(renameInputsScreen_selInp4ButWdgt, LE_FALSE); 
    renameInputsScreen_selInp4ButWdgt->fn->setReleasedImage(renameInputsScreen_selInp4ButWdgt, (leImage*)&smallSelected2);
};
void event_renameInputsScreen_selInp5ButWdgt_OnPressed(leButtonWidget* btn)
{
    //DEBUG_PRINT("event_renameInputsScreen_selInp5ButWdgt_OnPressed\r\n");
    if(appData.inpToRename != 5)
      clrSelectedRenameInput();
    appData.inpToRename = 5;
    renameInputsScreen_selInp5ButWdgt->fn->setEnabled(renameInputsScreen_selInp5ButWdgt, LE_FALSE); 
    renameInputsScreen_selInp5ButWdgt->fn->setReleasedImage(renameInputsScreen_selInp5ButWdgt, (leImage*)&smallSelected2);
};
void event_renameInputsScreen_selInp6ButWdgt_OnPressed(leButtonWidget* btn)
{
    //DEBUG_PRINT("event_renameInputsScreen_selInp6ButWdgt_OnPressed\r\n");
    if(appData.inpToRename != 6)
      clrSelectedRenameInput();
    appData.inpToRename = 6;
    renameInputsScreen_selInp6ButWdgt->fn->setEnabled(renameInputsScreen_selInp6ButWdgt, LE_FALSE);  
    renameInputsScreen_selInp6ButWdgt->fn->setReleasedImage(renameInputsScreen_selInp6ButWdgt, (leImage*)&smallSelected2);
};
void event_renameInputsScreen_selInp7ButWdgt_OnPressed(leButtonWidget* btn)
{
    //DEBUG_PRINT("event_renameInputsScreen_selInp7ButWdgt_OnPressed\r\n");
    if(appData.inpToRename != 7)
      clrSelectedRenameInput();
    appData.inpToRename = 7;
    renameInputsScreen_selInp7ButWdgt->fn->setEnabled(renameInputsScreen_selInp7ButWdgt, LE_FALSE);  
    renameInputsScreen_selInp7ButWdgt->fn->setReleasedImage(renameInputsScreen_selInp7ButWdgt, (leImage*)&smallSelected2);
};
void event_renameInputsScreen_selInp8ButWdgt_OnPressed(leButtonWidget* btn)
{
    //DEBUG_PRINT("event_renameInputsScreen_selInp8ButWdgt_OnPressed\r\n");
    if(appData.inpToRename != 8)
      clrSelectedRenameInput();
    appData.inpToRename = 8;
    renameInputsScreen_selInp8ButWdgt->fn->setEnabled(renameInputsScreen_selInp8ButWdgt, LE_FALSE);  
    renameInputsScreen_selInp8ButWdgt->fn->setReleasedImage(renameInputsScreen_selInp8ButWdgt, (leImage*)&smallSelected2);
};
void event_renameInputsScreen_selInp9ButWdgt_OnPressed(leButtonWidget* btn)
{
    //DEBUG_PRINT("event_renameInputsScreen_selInp9ButWdgt_OnPressed\r\n");
    if(appData.inpToRename != 9)
      clrSelectedRenameInput();
    appData.inpToRename = 9;
    renameInputsScreen_selInp9ButWdgt->fn->setEnabled(renameInputsScreen_selInp9ButWdgt, LE_FALSE);  
    renameInputsScreen_selInp9ButWdgt->fn->setReleasedImage(renameInputsScreen_selInp9ButWdgt, (leImage*)&smallSelected2);
};
void event_renameInputsScreen_selInp10ButWdgt_OnPressed(leButtonWidget* btn)
{
   //DEBUG_PRINT("event_renameInputsScreen_selInp10ButWdgt_OnPressed\r\n");
    if(appData.inpToRename != 10)
      clrSelectedRenameInput();
    appData.inpToRename = 10;
    renameInputsScreen_selInp10ButWdgt->fn->setEnabled(renameInputsScreen_selInp10ButWdgt, LE_FALSE);  
    renameInputsScreen_selInp10ButWdgt->fn->setReleasedImage(renameInputsScreen_selInp10ButWdgt, (leImage*)&smallSelected2);
};
void event_renameInputsScreen_selInp11ButWdgt_OnPressed(leButtonWidget* btn)
{
   //DEBUG_PRINT("event_renameInputsScreen_selInp10ButWdgt_OnPressed\r\n");
    if(appData.inpToRename != 11)
      clrSelectedRenameInput();
    appData.inpToRename = 11;
    renameInputsScreen_selInp11ButWdgt->fn->setEnabled(renameInputsScreen_selInp11ButWdgt, LE_FALSE);  
    renameInputsScreen_selInp11ButWdgt->fn->setReleasedImage(renameInputsScreen_selInp11ButWdgt, (leImage*)&smallSelected2);
};

void renameInputsScreen_OnShow(void)
{
    //DEBUG_PRINT("renameInputsScreen_OnShow\r\n");
    renameInputsScreen_selInp1ButWdgt->fn->setString(renameInputsScreen_selInp1ButWdgt, (leString*)&inp1Str);   
    renameInputsScreen_selInp2ButWdgt->fn->setString(renameInputsScreen_selInp2ButWdgt, (leString*)&inp2Str);   
    renameInputsScreen_selInp3ButWdgt->fn->setString(renameInputsScreen_selInp3ButWdgt, (leString*)&inp3Str);   
    renameInputsScreen_selInp4ButWdgt->fn->setString(renameInputsScreen_selInp4ButWdgt, (leString*)&inp4Str);   
    renameInputsScreen_selInp5ButWdgt->fn->setString(renameInputsScreen_selInp5ButWdgt, (leString*)&inp5Str);   
    renameInputsScreen_selInp6ButWdgt->fn->setString(renameInputsScreen_selInp6ButWdgt, (leString*)&inp6Str);   
    renameInputsScreen_selInp7ButWdgt->fn->setString(renameInputsScreen_selInp7ButWdgt, (leString*)&inp7Str);   
    renameInputsScreen_selInp8ButWdgt->fn->setString(renameInputsScreen_selInp8ButWdgt, (leString*)&inp8Str);   
    renameInputsScreen_selInp9ButWdgt->fn->setString(renameInputsScreen_selInp9ButWdgt, (leString*)&inp9Str);   
    renameInputsScreen_selInp10ButWdgt->fn->setString(renameInputsScreen_selInp10ButWdgt, (leString*)&inp10Str);   
    renameInputsScreen_selInp11ButWdgt->fn->setString(renameInputsScreen_selInp11ButWdgt, (leString*)&inp11Str);   
    cCnt = 0;
    
    setSelectedInputToRename ();
    if(!appData.dacRegiFlg)
    {
        renameInputsScreen_digitalInputs->fn->setVisible(renameInputsScreen_digitalInputs, LE_FALSE);  
        
    }
    
    if(!appData.phonoRegiFlg)
    {
        renameInputsScreen_selInp6ButWdgt->fn->setVisible(renameInputsScreen_selInp6ButWdgt, LE_FALSE);  
    }
};
void renameInputsScreen_OnHide(void){};
// </editor-fold>
