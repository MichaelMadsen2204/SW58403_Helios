#include "ir_control.h"
#include "definitions.h" // For CORETIMER, appData, SYS_TIME, etc.
#include <stdio.h>

extern APP_DATA appData;
extern uint8_t key;
extern bool keyAccept;
extern bool irToggle, oldIrToggle, volCmdDelayed;
extern uint8_t OldIrCommand;
extern uint16_t ignoreToggleCnt;
extern bool ignoreToggleFlg;

uint16_t irDecodeRawCode(void)
{
    uint8_t bit_cnt = 0;
    uint8_t single_bit;
    uint16_t ir_code = 0;

    while(IR_RC5_Get() == 0);

    ir_code |= 0x0001;
    CORETIMER_DelayUs(440);

    for (bit_cnt = 0; bit_cnt < 13; bit_cnt++)
    {
        ir_code <<= 1;
        single_bit = 0;

        if (IR_RC5_Get())
            single_bit |= 0b10;
        CORETIMER_DelayUs(890);
        if (IR_RC5_Get())
            single_bit |= 0b01;
        CORETIMER_DelayUs(890);

        if (single_bit == 0b10)
            ir_code |= 0x01;
        else if ((single_bit == 0b00) || (single_bit == 0b11))
        {
            printf("IR error\r\n");
            CORETIMER_DelayMs(25);
            return 0xFFFF; // Error code
        }
    }

    return ir_code;
}

uint8_t irExtractCommand(uint16_t rawCode)
{
    uint8_t command = 0;
    for (int i = 0; i < 6; i++)
    {
        command >>= 1;
        if (rawCode & 0x01)
            command |= 0x20;
        rawCode >>= 1;
    }

    if (rawCode & 0x40)
        command &= 0x3F;
    else
        command |= 0x40;

    return command;
}

uint8_t irExtractSystem(uint16_t rawCode)
{
    rawCode >>= 7;
    uint8_t system = 0;
    for (int i = 0; i < 5; i++)
    {
        system >>= 1;
        if (rawCode & 0x01)
            system |= 0x10;
        rawCode >>= 1;
    }
    return system;
}

void handleIrCommand(uint8_t system, uint8_t command, bool toggle)
{
    
    switch(command)
    {
        case com_on_off:
            key = KeyOnOff;
            keyAccept = 1;
            if(appData.powerOnFlg)
                onOffState = OFF_SEKVENS_1;
            break;

        case 0 ... 9:
            if(!appData.remoteViewDelayFlg)
            {
                if ((command > 0) && (command <= appData.maxInp))
                {
                    if(command != 6 || appData.phonoRegiFlg)
                        appData.curInp = command;
                    appData.irInputChangeFlg = 1;
                }
                if(command == 0 && appData.maxInp == 11)
                {
                    appData.curInp = 10;
                    appData.irInputChangeFlg = 1;
                }
                if(appData.irInputChangeFlg == 1)
                {
                    key = KeyDirectSelect;
                    keyAccept = 1;
                }
            }
            break;

        case com_vol_up:
            if(!appData.remoteViewDelayFlg)
            {
                key = KeyVolUp;
                if((appData.curLvl < 84) && appData.inputMuteActiveFlg == 0 && !appData.avFlg)
                    appData.curLvl++;
                keyAccept = 1;
                appData.skipUnmuteFlg = 0;
            }
            break;

        case com_vol_dwn:
            if(!appData.remoteViewDelayFlg)
            {
                key = KeyVolDwn;
                if(appData.curLvl > 0 && appData.inputMuteActiveFlg == 0 && !appData.avFlg)
                    appData.curLvl--;
                keyAccept = 1;
                appData.skipUnmuteFlg = 1;
            }
            break;

        case com_inp_up:
            if(!appData.remoteViewDelayFlg)
            {
                key = KeyInpUp;
                if(appData.curInp < appData.maxInp)
                {
                    appData.curInp++;
                    if(appData.curInp == 6 && !appData.phonoRegiFlg)
                        appData.curInp = 7;
                    appData.irInputChangeFlg = 1;
                }
                keyAccept = 1;
            }
            break;

        case com_inp_dwn:
            if(!appData.remoteViewDelayFlg)
            {
                key = KeyInpDwn;
                if(appData.curInp > 1)
                {
                    appData.curInp--;
                    if(appData.curInp == 6 && !appData.phonoRegiFlg)
                        appData.curInp = 5;
                    appData.irInputChangeFlg = 1;
                }
                keyAccept = 1;
            }
            break;

        case com_mute:
            if(!appData.remoteViewDelayFlg)
            {
                if((appData.curLvl > 0 || appData.curInp == appData.avInp))
                {
                    mute(); 
                    key = KeyMute;
                    keyAccept = 1;
                }
            }
            break;

        case com_disp:
            if(!appData.menuFlg)
            {
                key = KeyDisplay;
                keyAccept = 1;
            }
            break;

        case com_Filter:
            if((appData.curInp == 7 && !appData.menuFlg && !dacData.dsdOnFlg) || (appData.curInp >= 8 && !appData.menuFlg))
            {
                keyAccept = 1;
            }
            break;

        case com_DsdLP:
            if(appData.curInp == 7 && !appData.menuFlg && dacData.dsdOnFlg)
            {
                keyAccept = 1;
            }
            break;

        case com_OutputGain:
            if(appData.curInp >= 7 && !appData.menuFlg)
            {
                keyAccept = 1;
            }
            break;

        default:
            break;
    }

    if (system != 16) return;

    if (((OldIrCommand == com_vol_up && command == com_vol_up) ||
         (OldIrCommand == com_vol_dwn && command == com_vol_dwn)) &&
         ignoreToggleCnt <= 100 && !volCmdDelayed && (toggle == oldIrToggle))
    {
        command = 0xFF;
        volCmdDelayed = true;
        CORETIMER_DelayMs(200);
    }

    oldIrToggle = toggle;
    ignoreToggleCnt = 0;
    ignoreToggleFlg = false;

    if (command != 0xFF)
    {
        OldIrCommand = command;
        // key handling etc...
    }
}

void irReceive(void)
{
    uint16_t rawCode = irDecodeRawCode();
    if (rawCode == 0xFFFF)
        return;

    bool toggle = (rawCode & 0x1000) ? true : false;
    uint8_t command = irExtractCommand(rawCode);
    uint8_t system = irExtractSystem(rawCode);

    handleIrCommand(system, command, toggle);
}
