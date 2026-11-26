#include "definitions.h" // indeholder app.h, system headers, legato types mm.
#include "gfx/legato/generated/screen/le_gen_screen_qwertyScreen.h"
#include "ui_globals.h"
#include "app.h"


// *****************************************************************************
// *****************************************************************************
// Section: Application qwerty keypad Screen Functions 
// *****************************************************************************
// *****************************************************************************
// <editor-fold defaultstate="collapsed" desc="qwerty keypad Screen Functions">

typedef enum
{
    QWERTY_STATE_ALPHA=0,
    QWERTY_STATE_NUM,
    QWERTY_STATE_KEYPAD_CLICK,       
    QWERTY_STATE_SPACE,        
    QWERTY_STATE_TXT_FIELD_CHANGE,                    
    QWERTY_STATE_OK,
    QWERTY_STATE_IDLE,
} QWERTY_STATES;

static QWERTY_STATES qwertyState;

static uint8_t cCnt = 0;

static leChar legatoEditInpNameBuffer[9] = {0};
static leChar legatoDefaultInpNameBuffer[9] = {0};

static char cQwertyTable[7][12] = {"QWERTYUIOP≈",
                                   "ASDFGHJKL∆ÿ",
                                   " ZXCVBNM.  ",
                                   "1234567890+",
                                   "!'#%&/()=?~",
                                   "<>$;:,.-_^ "};

void initQwerty(void)
{
  cQwertyTable[2][10] = 8;
  cQwertyTable[5][10] = 8;
}

void updateQwerty (void)
{
    switch (qwertyState)
    {
        case    QWERTY_STATE_ALPHA  :   {
            qwertyScreen_KeyPadAlpaNum->fn->setPosition(qwertyScreen_KeyPadAlpaNum, 0, 0);
            qwertyState = QWERTY_STATE_IDLE;
            break;
        }
        case    QWERTY_STATE_NUM  :   {
            qwertyScreen_KeyPadAlpaNum->fn->setPosition(qwertyScreen_KeyPadAlpaNum, 0, -160);
            qwertyState = QWERTY_STATE_IDLE;
            break;
        }
        case    QWERTY_STATE_KEYPAD_CLICK   :   {
            
            editInputNameString.fn->setFromCStr(&editInputNameString,cChBuffer);
            qwertyScreen_TextFieldWidget0->fn->setString(qwertyScreen_TextFieldWidget0,(leString*) &editInputNameString);
            qwertyScreen_TextFieldWidget0->fn->setCursorPosition(qwertyScreen_TextFieldWidget0,cCnt);
            qwertyScreen_TextFieldWidget0->fn->setCursorPosition(qwertyScreen_TextFieldWidget0,cCnt);

//            if(cCnt <= 8)
//            {
//                if(cQwertyTable[row][col] == 0x08 && cCnt > 0  && cQwertyTable[row][col] != 0)
//                {
//                  cCnt--;
//                  cChBuffer[cCnt] = 0; //0x20;
//                  editInputNameString.fn->setFromCStr(&editInputNameString,cChBuffer);
//                  qwertyScreen_TextFieldWidget0->fn->setString(qwertyScreen_TextFieldWidget0,(leString*) &editInputNameString);
//                  qwertyScreen_TextFieldWidget0->fn->setCursorPosition(qwertyScreen_TextFieldWidget0,cCnt);
//                  //DEBUG_PRINT("charbuffer: %s\r\n",cChBuffer);
//                  //DEBUG_PRINT("∆ÿ≈ ROW: %d COL: %d - cCnt = %d\r\n",row,col,cCnt);
//                }
//                else if(cQwertyTable[row][col] != 0x08 && cCnt < 8 && cQwertyTable[row][col] != 0)
//                {
//                  cChBuffer[cCnt] = cQwertyTable[row][col];
//                  cCnt++;
//                  editInputNameString.fn->setFromCStr(&editInputNameString,cChBuffer);
//                  qwertyScreen_TextFieldWidget0->fn->setString(qwertyScreen_TextFieldWidget0,(leString*) &editInputNameString);
//                  qwertyScreen_TextFieldWidget0->fn->setCursorPosition(qwertyScreen_TextFieldWidget0,cCnt);
//                  qwertyScreen_TextFieldWidget0->fn->setCursorPosition(qwertyScreen_TextFieldWidget0,cCnt);
//                  //DEBUG_PRINT("∆ÿ≈ ROW: %d COL: %d + cCnt = %d\r\n",row,col,cCnt);
//                }
                if(cCnt == 0)
                {
                  editInputNameString.fn->setFromCStr(&editInputNameString,cChBuffer);
                  qwertyScreen_TextFieldWidget0->fn->setString(qwertyScreen_TextFieldWidget0,(leString*) &editInputNameString);
                  qwertyScreen_TextFieldWidget0->fn->setCursorPosition(qwertyScreen_TextFieldWidget0,cCnt);
                  qwertyScreen_TextFieldWidget0->fn->editClear(qwertyScreen_TextFieldWidget0);
                }
//
//            }
            qwertyState = QWERTY_STATE_IDLE;
            break;
        }       
        case    QWERTY_STATE_SPACE  :   {
            if(cCnt < 8)
            {
                cChBuffer[cCnt] = 0x20;
                cCnt++;
                editInputNameString.fn->setFromCStr(&editInputNameString,cChBuffer);
                qwertyScreen_TextFieldWidget0->fn->setString(qwertyScreen_TextFieldWidget0,(leString*) &editInputNameString);
                qwertyScreen_TextFieldWidget0->fn->setCursorPosition(qwertyScreen_TextFieldWidget0,cCnt);
                //DEBUG_PRINT("SPACE\r\n");
            }
            qwertyState = QWERTY_STATE_IDLE;
            break;
        }        
        case    QWERTY_STATE_TXT_FIELD_CHANGE  :   {
            qwertyScreen_TextFieldWidget0->fn->setCursorPosition(qwertyScreen_TextFieldWidget0,cCnt);
            qwertyState = QWERTY_STATE_IDLE;
            break;
        }                    
        case    QWERTY_STATE_OK  :   {
            if(cCnt > 0)
            {
            inpNames[appData.inpToRename][0] = cChBuffer[0];
            inpNames[appData.inpToRename][1] = cChBuffer[1];
            inpNames[appData.inpToRename][2] = cChBuffer[2];
            inpNames[appData.inpToRename][3] = cChBuffer[3];
            inpNames[appData.inpToRename][4] = cChBuffer[4];
            inpNames[appData.inpToRename][5] = cChBuffer[5];
            inpNames[appData.inpToRename][6] = cChBuffer[6];
            inpNames[appData.inpToRename][7] = cChBuffer[7];
            }

            inp1Str.fn-> setFromCStr(&inp1Str, inpNames[1]); 
            inp2Str.fn-> setFromCStr(&inp2Str, inpNames[2]); 
            inp3Str.fn-> setFromCStr(&inp3Str, inpNames[3]); 
            inp4Str.fn-> setFromCStr(&inp4Str, inpNames[4]); 
            inp5Str.fn-> setFromCStr(&inp5Str, inpNames[5]); 

            inp6Str.fn-> setFromCStr(&inp6Str, inpNames[6]); 
            inp7Str.fn-> setFromCStr(&inp7Str, inpNames[7]); 
            inp8Str.fn-> setFromCStr(&inp8Str, inpNames[8]); 
            inp9Str.fn-> setFromCStr(&inp9Str, inpNames[9]); 
            inp10Str.fn-> setFromCStr(&inp10Str, inpNames[10]); 
            inp11Str.fn-> setFromCStr(&inp11Str, inpNames[11]); 
            saveInpName();
            legato_showScreen(screenID_renameInputsScreen); 
            qwertyState = QWERTY_STATE_IDLE;
            break;
        }
        case    QWERTY_STATE_IDLE  :   {
            break;
        }
    }
}


void event_qwertyScreen_TextFieldWidget0_OnTextChanged(leTextFieldWidget* btn)
{
   //qwertyScreen_TextFieldWidget0->fn->setCursorPosition(qwertyScreen_TextFieldWidget0,cCnt);
   qwertyState = QWERTY_STATE_TXT_FIELD_CHANGE;
   //DEBUG_PRINT("CURSOR POS: %d\r\n",cCnt);
};
void event_qwertyScreen_okButtonWidget_OnReleased(leButtonWidget* btn)
{
    qwertyState = QWERTY_STATE_OK;
//    //DEBUG_PRINT("event_qwertyScreen_okButtonWidget_OnReleased\r\n");
//    //setBackLightIntensity(0);
//    //appData.screenSwapDelayHandle = SYS_TIME_CallbackRegisterMS(screenSwapDelay_Callback, 0, SCREENSWAP_DELAY_MS, SYS_TIME_SINGLE);
//    if(cCnt > 0)
//    {
//    inpNames[appData.inpToRename][0] = cChBuffer[0];
//    inpNames[appData.inpToRename][1] = cChBuffer[1];
//    inpNames[appData.inpToRename][2] = cChBuffer[2];
//    inpNames[appData.inpToRename][3] = cChBuffer[3];
//    inpNames[appData.inpToRename][4] = cChBuffer[4];
//    inpNames[appData.inpToRename][5] = cChBuffer[5];
//    inpNames[appData.inpToRename][6] = cChBuffer[6];
//    inpNames[appData.inpToRename][7] = cChBuffer[7];
//    }
//    
//    inp1Str.fn-> setFromCStr(&inp1Str, inpNames[1]); 
//    inp2Str.fn-> setFromCStr(&inp2Str, inpNames[2]); 
//    inp3Str.fn-> setFromCStr(&inp3Str, inpNames[3]); 
//    inp4Str.fn-> setFromCStr(&inp4Str, inpNames[4]); 
//    inp5Str.fn-> setFromCStr(&inp5Str, inpNames[5]); 
//    
//    inp6Str.fn-> setFromCStr(&inp6Str, inpNames[6]); 
//    inp7Str.fn-> setFromCStr(&inp7Str, inpNames[7]); 
//    inp8Str.fn-> setFromCStr(&inp8Str, inpNames[8]); 
//    inp9Str.fn-> setFromCStr(&inp9Str, inpNames[9]); 
//    inp10Str.fn-> setFromCStr(&inp10Str, inpNames[10]); 
//    saveInpName();
//    legato_showScreen(screenID_renameInputsScreen); 
};
void event_qwertyScreen_spaceButtonWidget_OnReleased(leButtonWidget* btn)
{
    qwertyState = QWERTY_STATE_SPACE;
//    if(cCnt < 8)
//    {
//        cChBuffer[cCnt] = 0x20;
//        cCnt++;
//        editInputNameString.fn->setFromCStr(&editInputNameString,cChBuffer);
//        qwertyScreen_TextFieldWidget0->fn->setString(qwertyScreen_TextFieldWidget0,(leString*) &editInputNameString);
//        qwertyScreen_TextFieldWidget0->fn->setCursorPosition(qwertyScreen_TextFieldWidget0,cCnt);
//        //DEBUG_PRINT("SPACE\r\n");
//    }
};
void event_qwertyScreen_numAlphaBut_OnPressed(leButtonWidget* btn)
{
    qwertyState = QWERTY_STATE_NUM;
   // qwertyScreen_KeyPadAlpaNum->fn->setPosition(qwertyScreen_KeyPadAlpaNum, 0, -161);
};

void event_qwertyScreen_numAlphaBut_OnReleased(leButtonWidget* btn)
{
    qwertyState = QWERTY_STATE_ALPHA;
    //qwertyScreen_KeyPadAlpaNum->fn->setPosition(qwertyScreen_KeyPadAlpaNum, 0, 0);
};


void event_qwertyScreen_KeyPadAlpaNum_OnKeyClick(leKeyPadWidget* wgt, leButtonWidget* cell, uint32_t row, uint32_t col)
{
   qwertyState = QWERTY_STATE_KEYPAD_CLICK;
    if(cCnt <= 8)
    {
        if(cQwertyTable[row][col] == 0x08 && cCnt > 0  && cQwertyTable[row][col] != 0)
        {
          cCnt--;
          cChBuffer[cCnt] = 0; //0x20;
//          editInputNameString.fn->setFromCStr(&editInputNameString,cChBuffer);
//          qwertyScreen_TextFieldWidget0->fn->setString(qwertyScreen_TextFieldWidget0,(leString*) &editInputNameString);
//          qwertyScreen_TextFieldWidget0->fn->setCursorPosition(qwertyScreen_TextFieldWidget0,cCnt);
//          //DEBUG_PRINT("charbuffer: %s\r\n",cChBuffer);
//          //DEBUG_PRINT("∆ÿ≈ ROW: %d COL: %d - cCnt = %d\r\n",row,col,cCnt);
        }
        else if(cQwertyTable[row][col] != 0x08 && cCnt < 8 && cQwertyTable[row][col] != 0)
        {
          cChBuffer[cCnt] = cQwertyTable[row][col];
          cCnt++;
//          editInputNameString.fn->setFromCStr(&editInputNameString,cChBuffer);
//          qwertyScreen_TextFieldWidget0->fn->setString(qwertyScreen_TextFieldWidget0,(leString*) &editInputNameString);
//          qwertyScreen_TextFieldWidget0->fn->setCursorPosition(qwertyScreen_TextFieldWidget0,cCnt);
//          qwertyScreen_TextFieldWidget0->fn->setCursorPosition(qwertyScreen_TextFieldWidget0,cCnt);
//          //DEBUG_PRINT("∆ÿ≈ ROW: %d COL: %d + cCnt = %d\r\n",row,col,cCnt);
        }
//        if(cCnt == 0)
//        {
//          editInputNameString.fn->setFromCStr(&editInputNameString,cChBuffer);
//          qwertyScreen_TextFieldWidget0->fn->setString(qwertyScreen_TextFieldWidget0,(leString*) &editInputNameString);
//          qwertyScreen_TextFieldWidget0->fn->setCursorPosition(qwertyScreen_TextFieldWidget0,cCnt);
//          qwertyScreen_TextFieldWidget0->fn->editClear(qwertyScreen_TextFieldWidget0);
//        }
//        
    }
};
void qwertyScreen_OnShow(void)
{
    cCnt = strlen(inpNames[appData.inpToRename]);
    qwertyScreen_TextFieldWidget0->fn->setCursorEnabled(qwertyScreen_TextFieldWidget0,LE_TRUE);
    qwertyScreen_TextFieldWidget0->fn->setCursorPosition(qwertyScreen_TextFieldWidget0,cCnt);
    qwertyScreen_TextFieldWidget0->fn->setCursorDelay(qwertyScreen_TextFieldWidget0,250);
    
    cChBuffer[0] = inpNames[appData.inpToRename][0];
    cChBuffer[1] = inpNames[appData.inpToRename][1];
    cChBuffer[2] = inpNames[appData.inpToRename][2];
    cChBuffer[3] = inpNames[appData.inpToRename][3];
    cChBuffer[4] = inpNames[appData.inpToRename][4];
    cChBuffer[5] = inpNames[appData.inpToRename][5];
    cChBuffer[6] = inpNames[appData.inpToRename][6];
    cChBuffer[7] = inpNames[appData.inpToRename][7];
    //cCnt = 8;

    //DEBUG_PRINT("qwertyScreen_OnShow %s\r\n",defaultInputNames[appData.inpToRename]); //slet
    leFixedString_Constructor(&editInputNameString, legatoEditInpNameBuffer, 16);
    leFixedString_Constructor(&defaultInputNameString, legatoDefaultInpNameBuffer, 16);
    editInputNameString.fn->setFromCStr(&editInputNameString,cChBuffer);
    qwertyScreen_TextFieldWidget0->fn->setString(qwertyScreen_TextFieldWidget0,(leString*) &editInputNameString);

    //cChBuffer = defaultInputNames[appData.inpToRename];
    defaultInputNameString.fn->setFont(&defaultInputNameString, leStringTable_GetStringFont(leGetState()->stringTable, stringID_curEditInputNameString, 0));      
    defaultInputNameString.fn->setFromCStr(&defaultInputNameString,defaultInputNames[appData.inpToRename]);
    qwertyScreen_LabelWidget1->fn->setString(qwertyScreen_LabelWidget1,(leString*) &defaultInputNameString);
    appData.state = APP_QWERTY_TASKS;
}; 
void qwertyScreen_OnHide(void){
    appData.state = APP_STATE_IDLE;
}; 

// </editor-fold>