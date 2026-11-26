#include "definitions.h" // indeholder app.h, system headers, legato types mm.
#include "gfx/legato/generated/screen/le_gen_screen_actionScreen.h" // for actionScreen_dispOnButton
#include "gfx/legato/generated/screen/le_gen_screen_simpleViewScreen.h" // for simpleViewScreen_dispOnButton
#include "ui_globals.h"
#include "app.h"




#define U16_address     34 // 0x22 Left Volume
#define U20_address     35 // 0x23 Right Volume

static uint8_t writeBuffer[WRITE_BUFFER_SIZE];

void setVolI2cCallback ( uintptr_t context )
{
  appData.volWrite_Done = 1;
}


// <editor-fold defaultstate="collapsed" desc="Volume Functions I/O expander (U16 og U20)">


//********************************************************************************
//******************    UPDATE VOLUME VALUE      *********************************
//********************************************************************************

void UpdateVolume (void)            
{ 

uint8_t            volWriteBuffer[4];
//uint8_t            GainedLevel;

//    old_Vol1 = Vol1;
//    old_Vol2 = Vol2;
//    old_Vol3 = Vol3;
//     
//DEBUG_PRINT("update Volume, cur scr: %d\r\n",legato_getCurrentScreen());

    U26_UpdateGreenBiasFromLevel();
    
    oldVolLeft = volLeft;
    oldVolRight = volRight;
    
    if(appData.curInp >= 7)   
    {    
        if(dacData.digiGain)
        {
          DEBUG_PRINT("digigain : volleft: %d", volLeft);
          volLeft = appData.curLvl + 6 + leftBal[appData.balance];
          volRight = appData.curLvl + 6 + rightBal[appData.balance]; 
          if(volLeft > 84)
             volLeft = 84;
          if(volRight > 84)
             volRight = 84;
        }
        else
        {
          DEBUG_PRINT("Not digigain : volleft: %d", volLeft);
          volLeft = appData.curLvl + leftBal[appData.balance];
          volRight = appData.curLvl + rightBal[appData.balance]; 
        }

    }
    else
     {
         volLeft = appData.curLvl + leftBal[appData.balance] + appData.inpSens[appData.curInp];
         if(volLeft > 84)
           volLeft = 84;
         volRight = appData.curLvl + rightBal[appData.balance] + appData.inpSens[appData.curInp];
         if(volRight > 84)
           volRight = 84;
     }  
    
    if(appData.curLvl == 0 && !AvSelected(appData.avInp, appData.curInp))
    {
       //DEBUG_PRINT("appData.curLvl == 0\r\n");
       muteOn();
       appData.muteFlg = 0;
       appData.skipUnmuteFlg = 0;
       if(legato_getCurrentScreen() == screenID_actionScreen)
       {
         //DEBUG_PRINT("screenID_actionScreen\r\n");
         actionScreen_actMuteBut->fn->setEnabled(actionScreen_actMuteBut,LE_FALSE);
         //actionScreen_actMuteBut->fn->setScheme(actionScreen_actMuteBut, &grayedOutScheme);
         actionScreen_actMuteBut->fn->setScheme(actionScreen_actMuteBut, &BlackScheme);
         //actionScreen_actMuteBut->fn->setVisible(actionScreen_actMuteBut,LE_FALSE);
         //actionScreen_actionMuteKryds->fn->setVisible(actionScreen_actionMuteKryds, LE_FALSE);
       }
       if(legato_getCurrentScreen() == screenID_simpleViewScreen)
       {
           simpleViewScreen_smpleViewMuteKryds->fn->setVisible(simpleViewScreen_smpleViewMuteKryds, LE_FALSE);
           //DEBUG_PRINT("screenID_simpleViewScreen\r\n");
       }
    }
    else if(!appData.startupFlg)
    {
       //DEBUG_PRINT("!appData.startupFlg\r\n");
       if(!appData.inputMuteActiveFlg && !appData.skipUnmuteFlg)
       {
           if(!appData.skipUnmuteFlg) DEBUG_PRINT("!skipUnmute\r\n");
           setInputRelay();//muteOff();
           CORETIMER_DelayMs(2); 
           appData.skipUnmuteFlg = 1;
           //DEBUG_PRINT("muteOff i forb. med volume update\r\n");
       
       
           if(legato_getCurrentScreen() == screenID_actionScreen)
           {
             //DEBUG_PRINT("screenID_actionScreen2 aktive mute but\r\n"); 
             actionScreen_actMuteBut->fn->setEnabled(actionScreen_actMuteBut,LE_TRUE);
             actionScreen_actMuteBut->fn->setScheme(actionScreen_actMuteBut, &BlackScheme);
             actionScreen_actMuteBut->fn->setVisible(actionScreen_actMuteBut,LE_TRUE);
             //actionScreen_actionMuteKryds->fn->setVisible(actionScreen_actionMuteKryds, LE_FALSE);
           }
           if(legato_getCurrentScreen() == screenID_simpleViewScreen)
           {
               //DEBUG_PRINT("screenID_simpleViewScreen2\r\n");
               simpleViewScreen_smpleViewMuteKryds->fn->setVisible(simpleViewScreen_smpleViewMuteKryds, LE_FALSE);
           }
           appData.muteFlg = 0;
       }
    }
    
     volWriteBuffer[0] = 0x84; //Output register 0 med autoincrement 
     IR_RC5_InterruptDisable();
     volWriteBuffer[1] = (VolumeByte1[volLeft] & 0xFC) | VolumeByte1[oldVolLeft]; 
     volWriteBuffer[2] = VolumeByte2[volLeft] | VolumeByte2[oldVolLeft];
     volWriteBuffer[3] = VolumeByte3[volLeft] | VolumeByte3[oldVolLeft];
     
     //i = volWriteBuffer[4];
     I2C3_Write(U16_address,&volWriteBuffer[0],4);
     CORETIMER_DelayMs(2); 
     //DEBUG_PRINT("u16 1\r\n");
     volWriteBuffer[1] = (VolumeByte1[volRight] & 0xFC) | VolumeByte1[oldVolRight]; 
     volWriteBuffer[2] = VolumeByte2[volRight] | VolumeByte2[oldVolRight];
     volWriteBuffer[3] = VolumeByte3[volRight] | VolumeByte3[oldVolRight];
     I2C3_Write(U20_address,&volWriteBuffer[0],4);
     //DEBUG_PRINT("u20 1\r\n");
     CORETIMER_DelayMs(2); 

     volWriteBuffer[1] = VolumeByte1[volLeft] | VolumeByte1[oldVolLeft]; 
     volWriteBuffer[2] = VolumeByte2[volLeft] | VolumeByte2[oldVolLeft];
     volWriteBuffer[3] = VolumeByte3[volLeft] | VolumeByte3[oldVolLeft];
     I2C3_Write(U16_address,&volWriteBuffer[0],4);
     CORETIMER_DelayMs(2); 
     //DEBUG_PRINT("u16 2\r\n");
     volWriteBuffer[1] = VolumeByte1[volRight] | VolumeByte1[oldVolRight]; 
     volWriteBuffer[2] = VolumeByte2[volRight] | VolumeByte2[oldVolRight];
     volWriteBuffer[3] = VolumeByte3[volRight] | VolumeByte3[oldVolRight];
     I2C3_Write(U20_address,&volWriteBuffer[0],4);
     CORETIMER_DelayMs(2); 
     //DEBUG_PRINT("u20 2\r\n");
     
     volWriteBuffer[1] = VolumeByte1[volLeft];
     volWriteBuffer[2] = VolumeByte2[volLeft];
     volWriteBuffer[3] = VolumeByte3[volLeft];
     I2C3_Write(U16_address,&volWriteBuffer[0],4);
     CORETIMER_DelayMs(2); 
     volWriteBuffer[1] = VolumeByte1[volRight];
     volWriteBuffer[2] = VolumeByte2[volRight];
     volWriteBuffer[3] = VolumeByte3[volRight];
     I2C3_Write(U20_address,&volWriteBuffer[0],4);
     CORETIMER_DelayMs(2); 
     IR_RC5_InterruptEnable();

}   

//void setCurrentLevel (void)            
//{ 
//
//uint8_t            volWriteBuffer[4];
//
//    volWriteBuffer[0] = 4;
//    volWriteBuffer[1] =  VolumeByte1[0];
//    volWriteBuffer[2] =  VolumeByte2[0];
//    volWriteBuffer[3] =  VolumeByte3[0];   
//
//    while(I2C3_IsBusy());
//    I2C3_Write(34, &volWriteBuffer[0],4);
//    CORETIMER_DelayMs(2);  
//    
//}   

void setLevelZero (void)            
{ 

uint8_t            volWriteBuffer[4];

    volWriteBuffer[0] = 4;
    volWriteBuffer[1] =  VolumeByte1[0];
    volWriteBuffer[2] =  VolumeByte2[0];
    volWriteBuffer[3] =  VolumeByte3[0];   
    while(I2C3_IsBusy());
    I2C3_Write(U16_address,&volWriteBuffer[0],4);
    while(I2C3_IsBusy());
    CORETIMER_DelayMs(2); 
    I2C3_Write(U20_address,&volWriteBuffer[0],4);
    CORETIMER_DelayMs(2); 
}   

void setAvLevel (void)            
{ 

    uint8_t            volWriteBuffer[4];
    
    volWriteBuffer[0] = 4;
    volWriteBuffer[1] =  VolumeByte1[avLevInp];
    volWriteBuffer[2] =  VolumeByte2[avLevInp];
    volWriteBuffer[3] =  VolumeByte3[avLevInp];   

    while(I2C3_IsBusy());
    I2C3_Write(U16_address, &volWriteBuffer[0],4);
    CORETIMER_DelayMs(2);  

    while(I2C3_IsBusy());
    I2C3_Write(U20_address, &volWriteBuffer[0],4);
    CORETIMER_DelayMs(2);  
 
   if(legato_getCurrentScreen() == screenID_actionScreen)
   {
     //DEBUG_PRINT("screenID_actionScreen2\r\n"); 
     actionScreen_actMuteBut->fn->setEnabled(actionScreen_actMuteBut,LE_TRUE);
     actionScreen_actMuteBut->fn->setVisible(actionScreen_actMuteBut,LE_TRUE);
     if(!appData.muteFlg)
       actionScreen_actMuteBut->fn->setScheme(actionScreen_actMuteBut, &BlackScheme);
     else
       actionScreen_actMuteBut->fn->setScheme(actionScreen_actMuteBut, &WhiteScheme);
   }
    
   // DEBUG_PRINT("av level for input: %d\r\n",appData.avInp);
    
}   


void u16InitIoExp (void)
{
    writeBuffer[0] = 0x0C; //Peger på register 0x0c
    writeBuffer[1] = 0x00; //U21 PIN 0-7
    writeBuffer[2] = 0x00; //U21 PIN 8-15
    writeBuffer[3] = 0x00; //U21 PIN 16-23
    //while(I2C3_IsBusy());
    
    I2C3_Write(U16_address, &writeBuffer[0], 4);
    CORETIMER_DelayMs(7);
    DEBUG_PRINT("u16 init\r\n");
}

void u20InitIoExp (void)
{
    writeBuffer[0] = 0x0C; //Peger på register 0x0c
    writeBuffer[1] = 0x00; //U21 PIN 0-7
    writeBuffer[2] = 0x00; //U21 PIN 8-15
    writeBuffer[3] = 0x00; //U21 PIN 16-23
    //while(I2C3_IsBusy());
    I2C3_Write(U20_address, &writeBuffer[0], 4);
    CORETIMER_DelayMs(7);
    DEBUG_PRINT("u20 init\r\n");
}


// </editor-fold>

