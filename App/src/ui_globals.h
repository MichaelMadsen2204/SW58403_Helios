#ifndef UI_GLOBALS_H
#define UI_GLOBALS_H

#include "gfx/legato/string/legato_fixedstring.h"
#include "config/default/definitions.h"

#ifdef __cplusplus
extern "C" {
#endif
    
typedef enum
{
    /* ON_OFF sekvens state machine's initial state. */
    ON_SEKVENS_AC_CHECK=0,
    ON_SEKVENS_1,
    ON_SEKVENS_2,
    ON_SEKVENS_3,
    ON_SEKVENS_4,
    ON_SEKVENS_5,
    ON_SEKVENS_6,
    ON_SEKVENS_7,  
    ON_SEKVENS_8,
    OFF_SEKVENS_1,
    ON_OFF_SEKVENS_IDLE,
    /* TODO: Define states used by the application state machine. */

} ON_OFF_SEKVENS_STATES;
typedef struct
{
   SYS_TIME_HANDLE onOffSekvensTimer; 
   SYS_TIME_HANDLE initBlinkTimer; 
   
}ON_OFF_SEKVENS_DATA;

extern ON_OFF_SEKVENS_STATES onOffState;
extern ON_OFF_SEKVENS_DATA onOffSekvensData;    
    

// Eksterne variable
extern leChar legatoInpNameBuffer1[16];
extern leChar legatoInpNameBuffer2[16];
extern leChar legatoInpNameBuffer3[16];
extern leChar legatoInpNameBuffer4[16];
extern leChar legatoInpNameBuffer5[16];
extern leChar legatoInpNameBuffer6[16];
extern leChar legatoInpNameBuffer7[16];
extern leChar legatoInpNameBuffer8[16];
extern leChar legatoInpNameBuffer9[16];
extern leChar legatoInpNameBuffer10[16];
extern leChar legatoInpNameBuffer11[16];
extern leChar legatoFsCharBuffer[16];
extern leChar legatoPcmFilterBuffer[8];
extern leChar legatoCharBuffer[8];

extern leFixedString inp1Str;
extern leFixedString inp2Str;
extern leFixedString inp3Str;
extern leFixedString inp4Str;
extern leFixedString inp5Str;
extern leFixedString inp6Str;
extern leFixedString inp7Str;
extern leFixedString inp8Str;
extern leFixedString inp9Str;
extern leFixedString inp10Str;
extern leFixedString inp11Str;

extern leFixedString editInputNameString;
extern leFixedString defaultInputNameString;
extern leFixedString balanceString;
extern leFixedString dispModeSimpleViewString;
extern leFixedString simpleViewInputString;
extern leFixedString pcmFilterString;

extern leFixedString levelString;
extern leFixedString dacFsStr;

extern leFixedString dacFsStr;

extern leFixedString snString;
extern leFixedString fwString;


extern char cChBuffer[15];
extern char cCharBuffer[16];
extern char cCharBuffer2[16];
extern char cSerialNoBuffer[15];
extern char serialNumber[15];
extern char firmware[15];

extern char inpNames[12][9];
extern char defaultInputNames[12][9];
extern char dispModeStrings[7][9];
extern char dacFsTabel[15][14];
extern char usbFsTabel[16][14];

extern uint8_t key;
extern bool keyAccept;
extern bool ignoreEvent;

extern unsigned int oldLevelValue;
extern uint8_t volLeft;
extern uint8_t volRight;
extern uint8_t oldVol;
extern uint8_t oldVolLeft;
extern uint8_t oldVolRight;

extern uint8_t balance;
extern uint8_t leftBal[];
extern uint8_t rightBal[];

extern uint8_t  VolumeByte1[];
extern uint8_t  VolumeByte2[];
extern uint8_t  VolumeByte3[];

extern uint16_t s_bootValue;

#ifdef __cplusplus
}
#endif

#endif // UI_GLOBALS_H
