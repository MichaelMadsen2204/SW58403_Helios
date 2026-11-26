#include "ui_globals.h"

char firmware[] = "FW Ver." firmwareVersion;  
char serialNumber[] = "SN: 584"; //VISES ALDRIG - BRUGES IKKE MERE


ON_OFF_SEKVENS_STATES onOffState;
ON_OFF_SEKVENS_DATA onOffSekvensData;

leChar legatoInpNameBuffer1[16] = {0};
leChar legatoInpNameBuffer2[16] = {0};
leChar legatoInpNameBuffer3[16] = {0};
leChar legatoInpNameBuffer4[16] = {0};
leChar legatoInpNameBuffer5[16] = {0};
leChar legatoInpNameBuffer6[16] = {0};
leChar legatoInpNameBuffer7[16] = {0};
leChar legatoInpNameBuffer8[16] = {0};
leChar legatoInpNameBuffer9[16] = {0};
leChar legatoInpNameBuffer10[16] = {0};
leChar legatoInpNameBuffer11[16] = {0};
leChar legatoFsCharBuffer[16] = {0};
leChar legatoPcmFilterBuffer[8] = {0};

leChar legatoCharBuffer[8] = {0};

leFixedString inp1Str;
leFixedString inp2Str;
leFixedString inp3Str;
leFixedString inp4Str;
leFixedString inp5Str;
leFixedString inp6Str;
leFixedString inp7Str;
leFixedString inp8Str;
leFixedString inp9Str;
leFixedString inp10Str;
leFixedString inp11Str;

leFixedString editInputNameString;
leFixedString defaultInputNameString;
leFixedString balanceString;
leFixedString dispModeSimpleViewString;
leFixedString simpleViewInputString;
leFixedString pcmFilterString;

leFixedString levelString;
leFixedString dacFsStr;

leFixedString dacFsStr;

leFixedString snString;
leFixedString fwString;


char dispModeStrings[7][9] ={"100%",
                            "75%",
                            "50%",
                            "25%",
                            "AUTO OFF",
                            "AUTO DIM"};

char dacFsTabel[15][14] =   {"FS: 44.1kHz  ",
                             "NO SIGNAL    ", 
                             "FS: 48kHz    ",
                             "FS: 32kHz    ",
                             "FS: 22.05kHz ",
                             "FS: 11.025kHz",
                             "FS: 24kHz    ",
                             "FS: 16kHz    ",
                             "FS: 88.2kHz  ",
                             "FS: 8kHz     ",
                             "FS: 96kHz    ",
                             "FS: 64kHz    ",
                             "FS: 176.4kHz ",
                             "    NA       ", 
                             "FS: 192kHz   "
                            };

char usbFsTabel[16][14] = {"FS: 32kHz    ",
                          "FS: 44.1kHz  ", 
                          "FS: 48kHz    ",
                          "FS: 88.2kHz  ",
                          "FS: 96kHz    ",
                          "FS: 176.4kHz ",
                          "FS: 192kHz   ",
                          "FS: 352.8kHz ",
                          "FS: 384kHz   ",
                          "DSD 64       ",
                          "DSD 128      ",
                          "DSD 256      ",
                          "DSD 512      ",
                          "             ",  //13
                          "USB UNPLUGGED"   //14
                        };

char defaultInputNames[12][9] = {"  NA    ",
                                "INPUT1",
                                "INPUT2",
                                "INPUT3",
                                "INPUT4",
                                "INPUT5",    
                                "PHONO",
                                "USB",
                                "AES/EBU",
                                "S/PDIF1",
                                "S/PDIF2",
                                "TOSLINK"
                                };

char cCharBuffer[16] = {0};
char cCharBuffer2[16] = {0};
char cChBuffer[15] = {0};
char cSerialNoBuffer[15] = {0};


char inpNames[12][9];



uint8_t key = 0;
bool keyAccept = 0;
bool ignoreEvent = 0;

unsigned int oldLevelValue = 0;
uint8_t volLeft = 0;
uint8_t volRight = 0;
uint8_t oldVol = 0;
uint8_t oldVolLeft = 0;
uint8_t oldVolRight = 0;

uint8_t balance = 6;
uint8_t leftBal[] = {6,5,4,3,2,1,0,0,0,0,0,0,0};
uint8_t rightBal[] = {0,0,0,0,0,0,0,1,2,3,4,5,6};

uint8_t         VolumeByte1[] =   {0x00,0x00,0x01,0x02,0x03,0x00,0x01,0x02,0x03,0x00,0x01,0x02,0x03,0x00,0x01,0x02,0x03,0x00,0x01,0x02,0x03,0x00,0x01,0x02,0x03,
                                 0x00,0x01,0x02,0x03,0x00,0x01,0x02,0x03,0x00,0x01,0x02,0x03,0x00,0x01,0x02,0x03,0x00,0x01,0x02,0x03,0x00,0x01,0x02,0x03,0x00,
                                 0x01,0x02,0x03,0x00,0x01,0x02,0x03,0x80,0x81,0x82,0x83,0x40,0x41,0x42,0x43,0x20,0x21,0x22,0x23,0x10,0x11,0x12,0x13,0x08,0x09,
                                 0x0A,0x0B,0x04,0x05,0x06,0x07,0x00,0x01,0x02,0x03};
                                 
uint8_t         VolumeByte2[] =   {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x00,0x80,0x80,0x80,0x80,
                                 0x40,0x40,0x40,0x40,0x30,0x30,0x30,0x30,0x20,0x20,0x20,0x20,0x10,0x10,0x10,0x10,0x08,0x08,0x08,0x08,0x04,0x04,0x04,0x04,0x02,
                                 0x02,0x02,0x02,0x01,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                                 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
                                 
uint8_t         VolumeByte3[] =   {0x06,0x06,0x06,0x06,0x06,0x04,0x04,0x04,0x04,0x02,0x02,0x02,0x02,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0x00,0x00,
                                 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                                 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                                 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};



