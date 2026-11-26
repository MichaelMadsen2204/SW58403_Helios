/*******************************************************************************
 Module for Microchip Legato Graphics Library

  Company:
    Microchip Technology Inc.

  File Name:
    le_gen_assets.h

  Summary:
    Header file containing a list of asset specifications for use with the
    Legato Graphics Stack.


  Description:
    Header file containing a list of asset specifications for use with the
    Legato Graphics Stack.

*******************************************************************************/


// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C)  Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/

// DOM-IGNORE-END

#ifndef LE_GEN_ASSETS_H
#define LE_GEN_ASSETS_H

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

#include "gfx/legato/legato.h"

extern const lePalette leGlobalPalette;

/*****************************************************************************
 * Legato Graphics Asset Location IDs
 *****************************************************************************/

/*****************************************************************************
 * Legato Graphics Image Assets
 *****************************************************************************/
/*********************************
 * Legato Image Asset
 * Name:   Image0
 * Size:   70x70 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage Image0;

/*********************************
 * Legato Image Asset
 * Name:   Image1
 * Size:   70x70 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage Image1;

/*********************************
 * Legato Image Asset
 * Name:   smallNotSelected
 * Size:   15x15 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage smallNotSelected;

/*********************************
 * Legato Image Asset
 * Name:   smallSelected
 * Size:   15x15 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage smallSelected;

/*********************************
 * Legato Image Asset
 * Name:   ActVolButtons2
 * Size:   75x100 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage ActVolButtons2;

/*********************************
 * Legato Image Asset
 * Name:   fanActive
 * Size:   125x30 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage fanActive;

/*********************************
 * Legato Image Asset
 * Name:   fanInactive
 * Size:   125x30 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage fanInactive;

/*********************************
 * Legato Image Asset
 * Name:   actAnaDigiButtonImg
 * Size:   110x50 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage actAnaDigiButtonImg;

/*********************************
 * Legato Image Asset
 * Name:   padLockLocked
 * Size:   30x39 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage padLockLocked;

/*********************************
 * Legato Image Asset
 * Name:   padLockUnlocked
 * Size:   30x39 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage padLockUnlocked;

/*********************************
 * Legato Image Asset
 * Name:   BackToMenu
 * Size:   110x50 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage BackToMenu;

/*********************************
 * Legato Image Asset
 * Name:   ILMVolButtons
 * Size:   60x80 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage ILMVolButtons;

/*********************************
 * Legato Image Asset
 * Name:   largeNotSelected
 * Size:   30x30 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage largeNotSelected;

/*********************************
 * Legato Image Asset
 * Name:   largeSelected
 * Size:   30x30 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage largeSelected;

/*********************************
 * Legato Image Asset
 * Name:   smallNotSelected2
 * Size:   15x20 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage smallNotSelected2;

/*********************************
 * Legato Image Asset
 * Name:   smallNotSelected3
 * Size:   15x18 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage smallNotSelected3;

/*********************************
 * Legato Image Asset
 * Name:   smallSelected2
 * Size:   15x18 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage smallSelected2;

/*********************************
 * Legato Image Asset
 * Name:   Backspace
 * Size:   40x40 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage Backspace;

/*********************************
 * Legato Image Asset
 * Name:   BattCharging
 * Size:   30x39 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage BattCharging;

/*********************************
 * Legato Image Asset
 * Name:   BattCharged
 * Size:   30x39 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage BattCharged;

/*********************************
 * Legato Image Asset
 * Name:   okLed
 * Size:   100x25 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage okLed;

/*********************************
 * Legato Image Asset
 * Name:   errorLed
 * Size:   100x25 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage errorLed;

/*********************************
 * Legato Image Asset
 * Name:   Alpha
 * Size:   44x50 pixels
 * Type:   RGB Data
 * Format: RGB_888
 ***********************************/
extern leImage Alpha;

/*********************************
 * Legato Image Asset
 * Name:   numbers
 * Size:   44x50 pixels
 * Type:   RGB Data
 * Format: RGB_888
 ***********************************/
extern leImage numbers;

/*********************************
 * Legato Image Asset
 * Name:   fanError
 * Size:   50x70 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage fanError;

/*********************************
 * Legato Image Asset
 * Name:   actionMuteKryds
 * Size:   118x81 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage actionMuteKryds;

/*********************************
 * Legato Image Asset
 * Name:   actionMuteKryds181x90
 * Size:   118x90 pixels
 * Type:   RGB Data
 * Format: RGB_888
 ***********************************/
extern leImage actionMuteKryds181x90;

/*********************************
 * Legato Image Asset
 * Name:   actionMuteKryds118x118
 * Size:   115x118 pixels
 * Type:   RGB Data
 * Format: RGB_888
 ***********************************/
extern leImage actionMuteKryds118x118;

/*********************************
 * Legato Image Asset
 * Name:   BatteriCharged2
 * Size:   23x30 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage BatteriCharged2;

/*********************************
 * Legato Image Asset
 * Name:   BatteriCharging2
 * Size:   23x30 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage BatteriCharging2;

/*********************************
 * Legato Image Asset
 * Name:   PadLockLocked2
 * Size:   23x30 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage PadLockLocked2;

/*********************************
 * Legato Image Asset
 * Name:   PadLockUnlocked2
 * Size:   23x30 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage PadLockUnlocked2;

/*********************************
 * Legato Image Asset
 * Name:   balButtons
 * Size:   80x60 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage balButtons;

/*********************************
 * Legato Image Asset
 * Name:   display_logo_v22
 * Size:   480x272 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage display_logo_v22;

/*****************************************************************************
 * Legato Graphics Font Assets
 *****************************************************************************/
/*********************************
 * Legato Font Asset
 * Name:         Avenir16
 * Height:       18
 * Baseline:     16
 * Style:        Antialias
 * Glyph Count:  115
 * Range Count:  10
 * Glyph Ranges: 0x20-0x7E
                 0xC5-0xD8
***********************************/
extern leRasterFont Avenir16;

/*********************************
 * Legato Font Asset
 * Name:         Avenir100_Tal
 * Height:       18
 * Baseline:     73
 * Style:        Antialias
 * Glyph Count:  32
 * Range Count:  5
 * Glyph Ranges: 0x30-0x39
                 0x41-0x56
***********************************/
extern leRasterFont Avenir100_Tal;

/*********************************
 * Legato Font Asset
 * Name:         Avenir18
 * Height:       18
 * Baseline:     18
 * Style:        Antialias
 * Glyph Count:  115
 * Range Count:  17
 * Glyph Ranges: 0x20-0x7E
                 0xC5-0xD8
***********************************/
extern leRasterFont Avenir18;

/*********************************
 * Legato Font Asset
 * Name:         Avenir12
 * Height:       18
 * Baseline:     12
 * Style:        Antialias
 * Glyph Count:  115
 * Range Count:  15
 * Glyph Ranges: 0x20-0x7E
                 0xC5-0xD8
***********************************/
extern leRasterFont Avenir12;

/*********************************
 * Legato Font Asset
 * Name:         avenir48
 * Height:       18
 * Baseline:     39
 * Style:        Antialias
 * Glyph Count:  57
 * Range Count:  10
 * Glyph Ranges: 0x20
                 0x23-0x5A
***********************************/
extern leRasterFont avenir48;

/*********************************
 * Legato Font Asset
 * Name:         Avenir30
 * Height:       18
 * Baseline:     28
 * Style:        Antialias
 * Glyph Count:  115
 * Range Count:  9
 * Glyph Ranges: 0x20-0x7E
                 0xC5-0xD8
***********************************/
extern leRasterFont Avenir30;

/*********************************
 * Legato Font Asset
 * Name:         Avenir64
 * Height:       18
 * Baseline:     59
 * Style:        Antialias
 * Glyph Count:  115
 * Range Count:  13
 * Glyph Ranges: 0x20-0x7E
                 0xC5-0xD8
***********************************/
extern leRasterFont Avenir64;

/*********************************
 * Legato Font Asset
 * Name:         Avenir17
 * Height:       18
 * Baseline:     16
 * Style:        Antialias
 * Glyph Count:  115
 * Range Count:  9
 * Glyph Ranges: 0x20-0x7E
                 0xC5-0xD8
***********************************/
extern leRasterFont Avenir17;

/*****************************************************************************
 * Legato String Table
 * Encoding        UTF16
 * Language Count: 1
 * String Count:   251
 *****************************************************************************/

// language IDs
#define language_Default    0

// string IDs
#define stringID_noString    0
#define stringID_digitalSettingDsdString    1
#define stringID_Temp    2
#define stringID_inpLvlMatch_6    3
#define stringID_SloRoll30    4
#define stringID_menuInpLevMatchStr    5
#define stringID_serialNumber    6
#define stringID_qwerty_AE    7
#define stringID_curPcmFilterString    8
#define stringID_avInpLine4    9
#define stringID_DigitalSetupHeaderString    10
#define stringID_qwerty_F    11
#define stringID_avNone    12
#define stringID_menuGreenBiasStr    13
#define stringID_qwerty_space    14
#define stringID_menuRestoreSettingStr    15
#define stringID_qwerty_underscore    16
#define stringID_Qwerty_RenameInputStr    17
#define stringID_qwerty_A    18
#define stringID_qwerty_slash    19
#define stringID_avString    20
#define stringID_actMuteButtonStr    21
#define stringID_inpSenseHeaderStr    22
#define stringID_Inp8Name    23
#define stringID_sn_hundreds    24
#define stringID_menuHeaderStr    25
#define stringID_sn_fixedPart    26
#define stringID_pcmFilt4_48    27
#define stringID_dispHeader    28
#define stringID_qwerty_4    29
#define stringID_menuDigitalStr    30
#define stringID_qwerty_question    31
#define stringID_menuIrSourceStr    32
#define stringID_MM    33
#define stringID_qwerty_9    34
#define stringID_restoreSettingLine4    35
#define stringID_qwerty_Y    36
#define stringID_Apodiz30    37
#define stringID_pcmFilt1    38
#define stringID_BIAS_SETTING_2M    39
#define stringID_percent100Str    40
#define stringID_pcmFilt1_48    41
#define stringID_balanceHeader    42
#define stringID_restoreSettingLine3    43
#define stringID_lowPassString16    44
#define stringID_percent75Str    45
#define stringID_saveStr    46
#define stringID_qwerty_and    47
#define stringID_qwerty_M    48
#define stringID_volSettingHeaderStr    49
#define stringID_gain0dB_12    50
#define stringID_avInpLine2    51
#define stringID_qwerty_C    52
#define stringID_qwerty_percent    53
#define stringID_OK_String    54
#define stringID_qwerty_pow    55
#define stringID_pickupSelectMM    56
#define stringID_Inp11Name    57
#define stringID_LinPhase12    58
#define stringID_Inp4Name    59
#define stringID_menuDisplayStr    60
#define stringID_digitalSettingFilterString    61
#define stringID_dsdLpOn12    62
#define stringID_pcmFilt7_48    63
#define stringID_dsdLpOff12    64
#define stringID_MinPhase30    65
#define stringID_qwerty_larger    66
#define stringID_gainString    67
#define stringID_LeftSidePowerMissingStr    68
#define stringID_autoOffStr    69
#define stringID_qwerty_3    70
#define stringID_qwerty_G    71
#define stringID_stabilizingStr    72
#define stringID_pcmFilt6    73
#define stringID_emtyString    74
#define stringID_actAnalogInpHeader    75
#define stringID_settingsRestoredString    76
#define stringID_FastRoll30    77
#define stringID_qwerty_T    78
#define stringID_avInp3Str    79
#define stringID_qwerty_ok    80
#define stringID_qwerty_1    81
#define stringID_qwerty_star    82
#define stringID_menuVolStr    83
#define stringID_qwerty_H    84
#define stringID_curEditInputNameString    85
#define stringID_pcmFilt3_48    86
#define stringID_qwerty_exclamation    87
#define stringID_qwerty_P    88
#define stringID_irSourceBackPanelStr    89
#define stringID_Apodiz    90
#define stringID_lowPass48    91
#define stringID_offStr18    92
#define stringID_digitalSettingPcmString    93
#define stringID_MinPhase12    94
#define stringID_yesString    95
#define stringID_Inp9Name    96
#define stringID_CyclePowerStr    97
#define stringID_cntDownStr    98
#define stringID_pcCircuitSter    99
#define stringID_qwerty_2    100
#define stringID_inpLvlMatch_5    101
#define stringID_qwerty_colon    102
#define stringID_qwerty_comma    103
#define stringID_volSettingVolStr    104
#define stringID_dacGain_str48    105
#define stringID_qwerty_K    106
#define stringID_actDigiInfoFilterLabel2    107
#define stringID_on_String_64    108
#define stringID_avInpLine1    109
#define stringID_fanErrStr2    110
#define stringID_qwerty_U    111
#define stringID_qwerty_right_parantes    112
#define stringID_SloRoll12    113
#define stringID_OFFStr    114
#define stringID_simpleViewInputNameStr    115
#define stringID_qwerty_0    116
#define stringID_qwerty_J    117
#define stringID_String0dB_64    118
#define stringID_irSourceFrontStr    119
#define stringID_qwerty_N    120
#define stringID_qwerty_punktum    121
#define stringID_curStartLevelStr    122
#define stringID_actMenuButtonStr    123
#define stringID_curLevelStr    124
#define stringID_Left    125
#define stringID_GB_Setting_Instruction    126
#define stringID_MinPhase    127
#define stringID_CheckPowerCordStr    128
#define stringID_SloRollLoDisp30    129
#define stringID_balanceStr    130
#define stringID_cancelStr    131
#define stringID_string0dB    132
#define stringID_disIntensStr    133
#define stringID_pcmFilt5    134
#define stringID_menuExitStr    135
#define stringID_qwerty_6    136
#define stringID_succesfullyString    137
#define stringID_fanErrStr1    138
#define stringID_qwerty_O    139
#define stringID_BIAS_SETTING_2H    140
#define stringID_pickupSelectMC    141
#define stringID_pickupSelectHeader    142
#define stringID_avSingleStr    143
#define stringID_sn_thousands    144
#define stringID_qwerty_L    145
#define stringID_BIAS_SETTING_1H    146
#define stringID_qwerty_D    147
#define stringID_RenameInputButtonStr    148
#define stringID_qwerty_8    149
#define stringID_avInp4Str    150
#define stringID_DAC_str    151
#define stringID_StringMinus6dB_64    152
#define stringID_qwerty_fullstop    153
#define stringID_actDigiInfoFsStr    154
#define stringID_qwerty_7    155
#define stringID_avInpLine3    156
#define stringID_qwerty_W    157
#define stringID_simpleViewStr    158
#define stringID_qwerty_dash    159
#define stringID_irSourceHeaderStr    160
#define stringID_inpLvlMatch_4    161
#define stringID_Inp6Name    162
#define stringID_simpleViewInputHeaderStr    163
#define stringID_qwerty_OE    164
#define stringID_onString18    165
#define stringID_FastRoll12    166
#define stringID_DcHf    167
#define stringID_percent50Str    168
#define stringID_pcmFilt5_48    169
#define stringID_dispModeStr    170
#define stringID_dsdAnalogueString16    171
#define stringID_inpLvlMatch_1    172
#define stringID_percent25Str    173
#define stringID_SloRollLoDisp12    174
#define stringID_AV_100    175
#define stringID_onStr    176
#define stringID_qwerty_equal    177
#define stringID_fwString    178
#define stringID_Inp5Name    179
#define stringID_LinPhase    180
#define stringID_actMonitorButtonStr    181
#define stringID_qwerty_X    182
#define stringID_fanErrStr3    183
#define stringID_volSettingStartStr    184
#define stringID_inpLvlMatch_2    185
#define stringID_pcmFilt7    186
#define stringID_qwerty_appostrof    187
#define stringID_qwerty_Q    188
#define stringID_FastRoll    189
#define stringID_qwerty_minus    190
#define stringID_actDigitalInpHeader    191
#define stringID_editInputNameStr    192
#define stringID_qwerty_dollar    193
#define stringID_Right    194
#define stringID_qwerty_R    195
#define stringID_off_String_64    196
#define stringID_curMaxLevelStr    197
#define stringID_dsd_Str_30    198
#define stringID_BIAS_SETTING_1M    199
#define stringID_ampStatus    200
#define stringID_pcmFilt6_48    201
#define stringID_autoDimStr    202
#define stringID_gainMinus6dB_12    203
#define stringID_yes16Str    204
#define stringID_qwerty_B    205
#define stringID_menuAvInputStr    206
#define stringID_LinPhase30    207
#define stringID_WrongAcInstructionStr    208
#define stringID_Inp2Name    209
#define stringID_inp3Name    210
#define stringID_qwerty_smaller    211
#define stringID_qwerty_left_parantes    212
#define stringID_menuNameInputStr    213
#define stringID_menuRiaaStr    214
#define stringID_qwerty_quotation    215
#define stringID_areYouSureStr    216
#define stringID_pcmFilt4    217
#define stringID_Apodiz12    218
#define stringID_qwerty_I    219
#define stringID_qwerty_Z    220
#define stringID_qwerty_5    221
#define stringID_pcmFilt3    222
#define stringID_restoreSettingLine2    223
#define stringID_pcmFilt2    224
#define stringID_curDsdFilterString    225
#define stringID_avBalanced    226
#define stringID_qwerty_havelaage    227
#define stringID_qwerty_plus    228
#define stringID_qwerty_E    229
#define stringID_pcmFilt2_48    230
#define stringID_Inp7Name    231
#define stringID_qwerty_AA    232
#define stringID_restoreSettingLine1    233
#define stringID_qwerty_ca    234
#define stringID_volSettingMaxStr    235
#define stringID_qwerty_V    236
#define stringID_qwerty_semicolon    237
#define stringID_SloRollLoDisp    238
#define stringID_Inp1Name    239
#define stringID_sn_tens    240
#define stringID_Inp10Name    241
#define stringID_sn_singles    242
#define stringID_inpLvlMatch_3    243
#define stringID_actVolumeHeaderStr    244
#define stringID_SloRoll    245
#define stringID_qwerty_backslash    246
#define stringID_wrongACHeader    247
#define stringID_qwerty_S    248
#define stringID_stringMinus6dB    249
#define stringID_qwerty_bksp    250

extern const leStringTable stringTable;


// string list
extern leTableString string_noString;
extern leTableString string_digitalSettingDsdString;
extern leTableString string_Temp;
extern leTableString string_inpLvlMatch_6;
extern leTableString string_SloRoll30;
extern leTableString string_menuInpLevMatchStr;
extern leTableString string_serialNumber;
extern leTableString string_qwerty_AE;
extern leTableString string_curPcmFilterString;
extern leTableString string_avInpLine4;
extern leTableString string_DigitalSetupHeaderString;
extern leTableString string_qwerty_F;
extern leTableString string_avNone;
extern leTableString string_menuGreenBiasStr;
extern leTableString string_qwerty_space;
extern leTableString string_menuRestoreSettingStr;
extern leTableString string_qwerty_underscore;
extern leTableString string_Qwerty_RenameInputStr;
extern leTableString string_qwerty_A;
extern leTableString string_qwerty_slash;
extern leTableString string_avString;
extern leTableString string_actMuteButtonStr;
extern leTableString string_inpSenseHeaderStr;
extern leTableString string_Inp8Name;
extern leTableString string_sn_hundreds;
extern leTableString string_menuHeaderStr;
extern leTableString string_sn_fixedPart;
extern leTableString string_pcmFilt4_48;
extern leTableString string_dispHeader;
extern leTableString string_qwerty_4;
extern leTableString string_menuDigitalStr;
extern leTableString string_qwerty_question;
extern leTableString string_menuIrSourceStr;
extern leTableString string_MM;
extern leTableString string_qwerty_9;
extern leTableString string_restoreSettingLine4;
extern leTableString string_qwerty_Y;
extern leTableString string_Apodiz30;
extern leTableString string_pcmFilt1;
extern leTableString string_BIAS_SETTING_2M;
extern leTableString string_percent100Str;
extern leTableString string_pcmFilt1_48;
extern leTableString string_balanceHeader;
extern leTableString string_restoreSettingLine3;
extern leTableString string_lowPassString16;
extern leTableString string_percent75Str;
extern leTableString string_saveStr;
extern leTableString string_qwerty_and;
extern leTableString string_qwerty_M;
extern leTableString string_volSettingHeaderStr;
extern leTableString string_gain0dB_12;
extern leTableString string_avInpLine2;
extern leTableString string_qwerty_C;
extern leTableString string_qwerty_percent;
extern leTableString string_OK_String;
extern leTableString string_qwerty_pow;
extern leTableString string_pickupSelectMM;
extern leTableString string_Inp11Name;
extern leTableString string_LinPhase12;
extern leTableString string_Inp4Name;
extern leTableString string_menuDisplayStr;
extern leTableString string_digitalSettingFilterString;
extern leTableString string_dsdLpOn12;
extern leTableString string_pcmFilt7_48;
extern leTableString string_dsdLpOff12;
extern leTableString string_MinPhase30;
extern leTableString string_qwerty_larger;
extern leTableString string_gainString;
extern leTableString string_LeftSidePowerMissingStr;
extern leTableString string_autoOffStr;
extern leTableString string_qwerty_3;
extern leTableString string_qwerty_G;
extern leTableString string_stabilizingStr;
extern leTableString string_pcmFilt6;
extern leTableString string_emtyString;
extern leTableString string_actAnalogInpHeader;
extern leTableString string_settingsRestoredString;
extern leTableString string_FastRoll30;
extern leTableString string_qwerty_T;
extern leTableString string_avInp3Str;
extern leTableString string_qwerty_ok;
extern leTableString string_qwerty_1;
extern leTableString string_qwerty_star;
extern leTableString string_menuVolStr;
extern leTableString string_qwerty_H;
extern leTableString string_curEditInputNameString;
extern leTableString string_pcmFilt3_48;
extern leTableString string_qwerty_exclamation;
extern leTableString string_qwerty_P;
extern leTableString string_irSourceBackPanelStr;
extern leTableString string_Apodiz;
extern leTableString string_lowPass48;
extern leTableString string_offStr18;
extern leTableString string_digitalSettingPcmString;
extern leTableString string_MinPhase12;
extern leTableString string_yesString;
extern leTableString string_Inp9Name;
extern leTableString string_CyclePowerStr;
extern leTableString string_cntDownStr;
extern leTableString string_pcCircuitSter;
extern leTableString string_qwerty_2;
extern leTableString string_inpLvlMatch_5;
extern leTableString string_qwerty_colon;
extern leTableString string_qwerty_comma;
extern leTableString string_volSettingVolStr;
extern leTableString string_dacGain_str48;
extern leTableString string_qwerty_K;
extern leTableString string_actDigiInfoFilterLabel2;
extern leTableString string_on_String_64;
extern leTableString string_avInpLine1;
extern leTableString string_fanErrStr2;
extern leTableString string_qwerty_U;
extern leTableString string_qwerty_right_parantes;
extern leTableString string_SloRoll12;
extern leTableString string_OFFStr;
extern leTableString string_simpleViewInputNameStr;
extern leTableString string_qwerty_0;
extern leTableString string_qwerty_J;
extern leTableString string_String0dB_64;
extern leTableString string_irSourceFrontStr;
extern leTableString string_qwerty_N;
extern leTableString string_qwerty_punktum;
extern leTableString string_curStartLevelStr;
extern leTableString string_actMenuButtonStr;
extern leTableString string_curLevelStr;
extern leTableString string_Left;
extern leTableString string_GB_Setting_Instruction;
extern leTableString string_MinPhase;
extern leTableString string_CheckPowerCordStr;
extern leTableString string_SloRollLoDisp30;
extern leTableString string_balanceStr;
extern leTableString string_cancelStr;
extern leTableString string_string0dB;
extern leTableString string_disIntensStr;
extern leTableString string_pcmFilt5;
extern leTableString string_menuExitStr;
extern leTableString string_qwerty_6;
extern leTableString string_succesfullyString;
extern leTableString string_fanErrStr1;
extern leTableString string_qwerty_O;
extern leTableString string_BIAS_SETTING_2H;
extern leTableString string_pickupSelectMC;
extern leTableString string_pickupSelectHeader;
extern leTableString string_avSingleStr;
extern leTableString string_sn_thousands;
extern leTableString string_qwerty_L;
extern leTableString string_BIAS_SETTING_1H;
extern leTableString string_qwerty_D;
extern leTableString string_RenameInputButtonStr;
extern leTableString string_qwerty_8;
extern leTableString string_avInp4Str;
extern leTableString string_DAC_str;
extern leTableString string_StringMinus6dB_64;
extern leTableString string_qwerty_fullstop;
extern leTableString string_actDigiInfoFsStr;
extern leTableString string_qwerty_7;
extern leTableString string_avInpLine3;
extern leTableString string_qwerty_W;
extern leTableString string_simpleViewStr;
extern leTableString string_qwerty_dash;
extern leTableString string_irSourceHeaderStr;
extern leTableString string_inpLvlMatch_4;
extern leTableString string_Inp6Name;
extern leTableString string_simpleViewInputHeaderStr;
extern leTableString string_qwerty_OE;
extern leTableString string_onString18;
extern leTableString string_FastRoll12;
extern leTableString string_DcHf;
extern leTableString string_percent50Str;
extern leTableString string_pcmFilt5_48;
extern leTableString string_dispModeStr;
extern leTableString string_dsdAnalogueString16;
extern leTableString string_inpLvlMatch_1;
extern leTableString string_percent25Str;
extern leTableString string_SloRollLoDisp12;
extern leTableString string_AV_100;
extern leTableString string_onStr;
extern leTableString string_qwerty_equal;
extern leTableString string_fwString;
extern leTableString string_Inp5Name;
extern leTableString string_LinPhase;
extern leTableString string_actMonitorButtonStr;
extern leTableString string_qwerty_X;
extern leTableString string_fanErrStr3;
extern leTableString string_volSettingStartStr;
extern leTableString string_inpLvlMatch_2;
extern leTableString string_pcmFilt7;
extern leTableString string_qwerty_appostrof;
extern leTableString string_qwerty_Q;
extern leTableString string_FastRoll;
extern leTableString string_qwerty_minus;
extern leTableString string_actDigitalInpHeader;
extern leTableString string_editInputNameStr;
extern leTableString string_qwerty_dollar;
extern leTableString string_Right;
extern leTableString string_qwerty_R;
extern leTableString string_off_String_64;
extern leTableString string_curMaxLevelStr;
extern leTableString string_dsd_Str_30;
extern leTableString string_BIAS_SETTING_1M;
extern leTableString string_ampStatus;
extern leTableString string_pcmFilt6_48;
extern leTableString string_autoDimStr;
extern leTableString string_gainMinus6dB_12;
extern leTableString string_yes16Str;
extern leTableString string_qwerty_B;
extern leTableString string_menuAvInputStr;
extern leTableString string_LinPhase30;
extern leTableString string_WrongAcInstructionStr;
extern leTableString string_Inp2Name;
extern leTableString string_inp3Name;
extern leTableString string_qwerty_smaller;
extern leTableString string_qwerty_left_parantes;
extern leTableString string_menuNameInputStr;
extern leTableString string_menuRiaaStr;
extern leTableString string_qwerty_quotation;
extern leTableString string_areYouSureStr;
extern leTableString string_pcmFilt4;
extern leTableString string_Apodiz12;
extern leTableString string_qwerty_I;
extern leTableString string_qwerty_Z;
extern leTableString string_qwerty_5;
extern leTableString string_pcmFilt3;
extern leTableString string_restoreSettingLine2;
extern leTableString string_pcmFilt2;
extern leTableString string_curDsdFilterString;
extern leTableString string_avBalanced;
extern leTableString string_qwerty_havelaage;
extern leTableString string_qwerty_plus;
extern leTableString string_qwerty_E;
extern leTableString string_pcmFilt2_48;
extern leTableString string_Inp7Name;
extern leTableString string_qwerty_AA;
extern leTableString string_restoreSettingLine1;
extern leTableString string_qwerty_ca;
extern leTableString string_volSettingMaxStr;
extern leTableString string_qwerty_V;
extern leTableString string_qwerty_semicolon;
extern leTableString string_SloRollLoDisp;
extern leTableString string_Inp1Name;
extern leTableString string_sn_tens;
extern leTableString string_Inp10Name;
extern leTableString string_sn_singles;
extern leTableString string_inpLvlMatch_3;
extern leTableString string_actVolumeHeaderStr;
extern leTableString string_SloRoll;
extern leTableString string_qwerty_backslash;
extern leTableString string_wrongACHeader;
extern leTableString string_qwerty_S;
extern leTableString string_stringMinus6dB;
extern leTableString string_qwerty_bksp;

void initializeStrings(void);
//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif /* LE_GEN_ASSETS_H */
