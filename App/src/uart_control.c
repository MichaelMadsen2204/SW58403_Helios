#include "definitions.h" // indeholder app.h, system headers, legato types mm.
#include "gfx/legato/generated/screen/le_gen_screen_actionScreen.h" // for actionScreen_dispOnButton
#include "gfx/legato/generated/screen/le_gen_screen_simpleViewScreen.h" // for simpleViewScreen_dispOnButton
#include "ui_globals.h"
#include "app.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>

#define UART_BUFFER_SIZE       64
//uint8_t uartReadBuffer[UART_BUFFER_SIZE] = {0};

// UART kommando-ID'er
#define CMD_SET_VOLUME         '1'
#define CMD_SET_INPUT          '2'
#define CMD_SET_MUTE           '3'
#define CMD_SET_IR_SOURCE      '5'
#define CMD_FACTORY_RESET      '6'
#define CMD_PRINT_FW_INFO      '8'
#define CMD_PRINT_SERIAL_NUM   '9'
#define CMD_SN_THOUSANDS       'T'
#define CMD_SN_HUNDREDS        'H'
#define CMD_SN_TENS            't'
#define CMD_SN_SINGLES         'S'
#define CMD_GET_AC_RESULT      'B'



void uartClearBuffer(void)
{
 uint8_t dummy = 0;   
 while(UART1_ReceiverIsReady())
 {
   dummy += UART1_ReadByte();      //Ryd op i Uart buffer  
 }
}
//
//void uartCtrl(void)
//{
//    
// uint8_t    i, command, value, calculatedInpValue = 0;     
//        
//     CORETIMER_DelayMs(10); 
//     i=0;
//     while(UART1_ReceiverIsReady())
//     {
//         uartReadBuffer[i] = UART1_ReadByte();
//         i++;
//     }
//     if(uartReadBuffer[1] == 'T' || uartReadBuffer[1] == 'H' || uartReadBuffer[1] == 't' || uartReadBuffer[1] == 'S' || uartReadBuffer[1] == 'B' || uartReadBuffer[1] == 'C' || uartReadBuffer[1] == 'D' )
//         command = uartReadBuffer[1];
//     else
//         command = uartReadBuffer[1] - 48;
//     
//     value = (uartReadBuffer[3]-48) * 10;
//     value = value + (uartReadBuffer[4] - 48);
//     //printf("uart buffer %s\r\n", uartReadBuffer);
//     //printf("uart value %d\r\n", value);
//     
//     if(uartReadBuffer[0] == '$' && uartReadBuffer[2] == ':' && uartReadBuffer[5] == ';' )//&& uartReadBuffer[5] == ';' )
//      {
// 
//          switch(command)
//          {
//              case  1   : {
//                  if(value <= appData.maxLvl)
//                    appData.curLvl = value;
//                  UpdateVolume();
//                  printf("#1:%02d;\r\n", appData.curLvl); //Kvittering for Uart kommando
//                  break;
//              }
//              case  2   : {
//                  if(value <= 7)
//                    appData.curInp = value;
//                  if(legato_getCurrentScreen() == screenID_actionScreen)
//                    {
//                        if(appData.curInp > 0 && appData.curInp < 7)
//                        {
//                            actionScreen_actAnaDigiSelectionBut->fn->setPressed(actionScreen_actAnaDigiSelectionBut, LE_FALSE);
//                            actionScreen_digiInpNamePanel->fn->setEnabled(actionScreen_digiInpNamePanel, LE_FALSE);
//                            actionScreen_digiInpNamePanel->fn->setVisible(actionScreen_digiInpNamePanel, LE_FALSE);
//                            actionScreen_anaInpNamePanel->fn->setEnabled(actionScreen_anaInpNamePanel, LE_TRUE);
//                            actionScreen_anaInpNamePanel->fn->setVisible(actionScreen_anaInpNamePanel, LE_TRUE);
//                        }
//                        else if(appData.dacRegiFlg)
//                        {
//                            actionScreen_actAnaDigiSelectionBut->fn->setPressed(actionScreen_actAnaDigiSelectionBut, LE_TRUE);
//                            actionScreen_digiInpNamePanel->fn->setEnabled(actionScreen_digiInpNamePanel, LE_TRUE);
//                            actionScreen_digiInpNamePanel->fn->setVisible(actionScreen_digiInpNamePanel, LE_TRUE);
//                            actionScreen_anaInpNamePanel->fn->setEnabled(actionScreen_anaInpNamePanel, LE_FALSE);
//                            actionScreen_anaInpNamePanel->fn->setVisible(actionScreen_anaInpNamePanel, LE_FALSE);
//                        }
//                      clrSelectedInput();
//                      setActiveInput();
//                  }
//                  if(legato_getCurrentScreen() == screenID_simpleViewScreen)
//                    {
//                       sprintf(cCharBuffer2, inpNames[appData.curInp]);
//                       simpleViewInputString.fn-> setFromCStr(&simpleViewInputString, cCharBuffer2);  
//                    }
//                  appData.u26Byte0 &= 0x7F;//mute
//                  u26WriteOutputs (appData.u26Byte0,appData.u26Byte2);
//                  if(appData.curInp <= 6)
//                    {
//                        calculatedInpValue = 1 << (appData.curInp - 1);
//                    }
//                  else if (appData.curInp >= 7 && appData.curInp <= 11)
//                        calculatedInpValue = 0x20;
//                  appData.u26Byte0 &= 0xC0;
//                  appData.u26Byte0 |= calculatedInpValue;
//                  u26WriteOutputs (appData.u26Byte0,appData.u26Byte2);//set input
//
//                  CORETIMER_DelayMs(50);
//                  appData.u26Byte0 |= 0x80; // Unmute  
//                  u26WriteOutputs (appData.u26Byte0,appData.u26Byte2);
//                  
//                  //printf("Test input set to %d", appData.curInp);
//                  printf("#2:%02d;\r\n", appData.curInp); //Kvittering for Uart kommando
//                  break;
//              }
//              case  3   : {
//                  if(value == 1)
//                  {
//                      appData.muteFlg = 1;
//                      muteOn();
//                      if(legato_getCurrentScreen() == screenID_actionScreen)
//                        {
//                          if(!appData.muteFlg)
//                              actionScreen_actionMuteKryds->fn->setVisible(actionScreen_actionMuteKryds, LE_FALSE);
//                          else
//                              actionScreen_actionMuteKryds->fn->setVisible(actionScreen_actionMuteKryds, LE_TRUE);
//                        }
//                      else if (legato_getCurrentScreen() == screenID_simpleViewScreen)
//                        {
//                            if(appData.muteFlg)
//                               simpleViewScreen_smpleViewMuteKryds->fn->setVisible(simpleViewScreen_smpleViewMuteKryds, LE_TRUE);
//                            else
//                               simpleViewScreen_smpleViewMuteKryds->fn->setVisible(simpleViewScreen_smpleViewMuteKryds, LE_FALSE);
//                        }
//                      printf("#3:01;\r\n"); //Kvittering for Uart kommando
//                      //printf("Test mute ON");
//                  }
//                  else
//                  {
//                      appData.muteFlg = 0;
//                      muteOff();
//                      if(legato_getCurrentScreen() == screenID_actionScreen)
//                        {
//                          if(!appData.muteFlg)
//                              actionScreen_actionMuteKryds->fn->setVisible(actionScreen_actionMuteKryds, LE_FALSE);
//                          else
//                              actionScreen_actionMuteKryds->fn->setVisible(actionScreen_actionMuteKryds, LE_TRUE);
//                        }
//                      else if (legato_getCurrentScreen() == screenID_simpleViewScreen)
//                        {
//                            if(appData.muteFlg)
//                               simpleViewScreen_smpleViewMuteKryds->fn->setVisible(simpleViewScreen_smpleViewMuteKryds, LE_TRUE);
//                            else
//                               simpleViewScreen_smpleViewMuteKryds->fn->setVisible(simpleViewScreen_smpleViewMuteKryds, LE_FALSE);
//                        }
//
//                      printf("#3:00;\r\n"); //Kvittering for Uart kommando
//                  }
//                  break;
//              }
//              case  5   : 
//                {
//                    if(value == 0)
//                       IR_SOURCE_Set();  
//                    else if(value == 1)
//                       IR_SOURCE_Clear();
//                    printf("#5:%02d;\r\n", value); 
//                  break;
//                }
//              case  6   : 
//                {
//                    printf("#6:%2d;\r\n", value); 
//                    if(value == 0)
//                    {
//                      writeEEpromDefault(); 
//                      appData.curInp = 1;
//                      setInput();
//                      printf("#6:%2d;\r\n", value); 
//                    }
//                  break;
//                }
//              case  8   : 
//                {
//                    printf("#8:%02d;\r\n", value); 
//                    if(value == 0)
//                    {
//                      printf("%s  -  ", firmware); 
//                      if(appData.voltageSetting == VoltageHigh)
//                          printf("Voltage Setting = High\r\n"); 
//                      else
//                          printf("Voltage Setting = Low\r\n");
//                    }
//                  break;
//                }
//              case  9   : 
//                {
//                    printf("#9:%02d;\r\n", value); 
//                    if(value == 0)
//                    {
//                       getSNFromEEProm();
//                       createSN();
//                       printf("%s\r\n",serialNumber);
//                    }
//                  break;
//                }
//              case  'B'   : // RETURN AC_RESULT
//                {
//                    if(value <= 9)
//                    {
//                        if(AC_RESULT_Get())
//                           printf("#B:01;\r\n"); 
//                        else
//                           printf("#B:00;\r\n");  
//                    }
//                    break;
//                }
//              case  'T'   : 
//                {
//                    if(value <= 9)
//                    {
//                      appData.snThousands = value;
//                      printf("#T:%2d;\r\n", value); 
//                    }
//                    break;
//                }
//              case  'H'   : 
//                {
//                    if(value <= 9)
//                    {
//                      appData.snHundreds = value;
//                      printf("#H:%2d;\r\n", value); 
//                    }
//                    break;
//                }
//              case  't'   : 
//                {
//                    if(value <= 9)
//                    {
//                      appData.snTens = value;
//                      printf("#t:%2d;\r\n", value); 
//                    }
//                    break;
//                }
//              case  'S'   : 
//                {
//                    if(value <= 9)  
//                    {
//                        appData.snSingles = value;
//                        printf("#S:%2d;\r\n", value); 
//                        createSN();
//                        printf("%s\r\n",serialNumber);
//                        saveSNToEEProm();
//                    }
//                    break;
//                  
//                }
//              
//
//              
//              default   : 
//                  //printf("Command = %d\r\n Value = %d\r\n",command, value);
//                  break;
//          }
//      }
//      else
//        printf("uart read error"); 
// 
//  
//  
//}
//
//


static void uartAck(char cmd, uint8_t val)
{
    printf("#%c:%02d;\r\n", cmd, val);
}

static void updateGuiAfterInputChange(void)
{
    if (legato_getCurrentScreen() == screenID_actionScreen)
    {
        if (appData.curInp > 0 && appData.curInp < 7)
        {
            actionScreen_actAnaDigiSelectionBut->fn->setPressed(actionScreen_actAnaDigiSelectionBut, LE_FALSE);
            actionScreen_digiInpNamePanel->fn->setEnabled(actionScreen_digiInpNamePanel, LE_FALSE);
            actionScreen_digiInpNamePanel->fn->setVisible(actionScreen_digiInpNamePanel, LE_FALSE);
            actionScreen_anaInpNamePanel->fn->setEnabled(actionScreen_anaInpNamePanel, LE_TRUE);
            actionScreen_anaInpNamePanel->fn->setVisible(actionScreen_anaInpNamePanel, LE_TRUE);
        }
        else if (appData.dacRegiFlg)
        {
            actionScreen_actAnaDigiSelectionBut->fn->setPressed(actionScreen_actAnaDigiSelectionBut, LE_TRUE);
            actionScreen_digiInpNamePanel->fn->setEnabled(actionScreen_digiInpNamePanel, LE_TRUE);
            actionScreen_digiInpNamePanel->fn->setVisible(actionScreen_digiInpNamePanel, LE_TRUE);
            actionScreen_anaInpNamePanel->fn->setEnabled(actionScreen_anaInpNamePanel, LE_FALSE);
            actionScreen_anaInpNamePanel->fn->setVisible(actionScreen_anaInpNamePanel, LE_FALSE);
        }
    }
    else if (legato_getCurrentScreen() == screenID_simpleViewScreen)
    {
        sprintf(cCharBuffer2, inpNames[appData.curInp]);
        simpleViewInputString.fn->setFromCStr(&simpleViewInputString, cCharBuffer2);
    }
}

void uartCtrl(void)
{
    uint8_t i = 0;
    char uartReadBuffer[UART_BUFFER_SIZE] = {0};
    char command;
    uint8_t value = 0;

    CORETIMER_DelayMs(10);

    // Læs UART buffer med sikkerhed
    while (UART1_ReceiverIsReady() && i < UART_BUFFER_SIZE - 1)
    {
        uartReadBuffer[i++] = UART1_ReadByte();
    }
    uartReadBuffer[i] = '\0'; // Null-terminér

    // Tjek kommandoformat
    if (uartReadBuffer[0] == '$' && uartReadBuffer[2] == ':' && uartReadBuffer[5] == ';')
    {
        if (sscanf(uartReadBuffer, "$%c:%2hhu;", &command, &value) != 2)
        {
            printf("uart parse error\r\n");
            return;
        }

        switch (command)
        {
            case CMD_SET_VOLUME:
                if (value <= appData.maxLvl)
                    appData.curLvl = value;
                UpdateVolume();
                uartAck(CMD_SET_VOLUME, appData.curLvl);
                break;

            case CMD_SET_INPUT:
                if (value <= appData.maxInp)
                    appData.curInp = value;
                
                updateGuiAfterInputChange();
                appData.irInputChangeFlg = 1;
                muteOn();
                setInputRelay();
                if (appData.curInp == 4 || appData.curInp == 5)  minus6dBOn(); else minus6dBOff();
                CORETIMER_DelayMs(50);
                muteOff();
//                
//                appData.u26Byte0 &= 0x7F;  // Mute
//                u26WriteOutputs(appData.u26Byte0, appData.u26Byte2);
//
//                if (appData.curInp <= 6)
//                    calculatedInpValue = 1 << (appData.curInp - 1);
//                else if (appData.curInp >= 7 && appData.curInp <= 11)
//                    calculatedInpValue = 0x40;
//
//                appData.u26Byte0 &= 0xC0;
//                appData.u26Byte0 |= calculatedInpValue;
//                u26WriteOutputs(appData.u26Byte0, appData.u26Byte2);
//
//                CORETIMER_DelayMs(50);
//
//                appData.u26Byte0 |= 0x80;  // Unmute
//                u26WriteOutputs(appData.u26Byte0, appData.u26Byte2);

                uartAck(CMD_SET_INPUT, appData.curInp);
                break;

            case CMD_SET_MUTE:
                appData.muteFlg = (value == 1);
                if (appData.muteFlg)
                    muteOn();
                else
                    muteOff();

                if (legato_getCurrentScreen() == screenID_actionScreen)
                {
                    if(appData.muteFlg)
                        actionScreen_actMuteBut->fn->setScheme(actionScreen_actMuteBut, &WhiteScheme);
                    else
                        actionScreen_actMuteBut->fn->setScheme(actionScreen_actMuteBut, &BlackScheme);
                }
                else if (legato_getCurrentScreen() == screenID_simpleViewScreen)
                    simpleViewScreen_smpleViewMuteKryds->fn->setVisible(simpleViewScreen_smpleViewMuteKryds, appData.muteFlg);

                uartAck(CMD_SET_MUTE, appData.muteFlg);
                break;

            case CMD_SET_IR_SOURCE:
                if (value == 0)
                    IR_SOURCE_Set();
                else if (value == 1)
                    IR_SOURCE_Clear();
                uartAck(CMD_SET_IR_SOURCE, value);
                break;

            case CMD_FACTORY_RESET:
                uartAck(CMD_FACTORY_RESET, value);
                if (value == 0)
                {
                    writeEEpromDefault();
                    appData.curInp = 1;
                    setInput();
                }
                break;

            case CMD_PRINT_FW_INFO:
                uartAck(CMD_PRINT_FW_INFO, value);
                if (value == 0)
                {
                    printf("%s  -  ", firmware);
                    printf("Voltage Setting = %s\r\n", appData.voltageSetting == VoltageHigh ? "High" : "Low");
                }
                break;

            case CMD_PRINT_SERIAL_NUM:
                uartAck(CMD_PRINT_SERIAL_NUM, value);
                if (value == 0)
                {
                    getSNFromEEProm();
                    createSN();
                    printf("%s\r\n", serialNumber);
                }
                break;

            case CMD_SN_THOUSANDS:
                if (value <= 9)
                {
                    appData.snThousands = value;
                    uartAck(CMD_SN_THOUSANDS, value);
                }
                break;

            case CMD_SN_HUNDREDS:
                if (value <= 9)
                {
                    appData.snHundreds = value;
                    uartAck(CMD_SN_HUNDREDS, value);
                }
                break;

            case CMD_SN_TENS:
                if (value <= 9)
                {
                    appData.snTens = value;
                    uartAck(CMD_SN_TENS, value);
                }
                break;

            case CMD_SN_SINGLES:
                if (value <= 9)
                {
                    appData.snSingles = value;
                    uartAck(CMD_SN_SINGLES, value);
                    createSN();
                    printf("%s\r\n", serialNumber);
                    saveSNToEEProm();
                }
                break;

            case CMD_GET_AC_RESULT:
                if (value <= 9)
                    printf("#%c:%02d;\r\n", CMD_GET_AC_RESULT, AC_RESULT_Get() ? 1 : 0);
                break;

            default:
                printf("uart unknown command '%c'\r\n", command);
                break;
        }
    }
    else
    {
        printf("uart read error\r\n");
    }
}
