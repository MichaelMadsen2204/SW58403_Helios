#include "definitions.h" // indeholder app.h, system headers, legato types mm.


void fadeBacklightIn(void)
{
    uint8_t i = 0;
    i=0;
    for(i=0;i<40;i++)
    {
       setBackLightIntensity(i);  // tænd display backlight 
       CORETIMER_DelayMs (50);
    }
}

void fadeBacklightOut(void)
{
    uint8_t i = 0;
    i=0;
    for(i=0;i<40;i++)
    {
       setBackLightIntensity(40-i);  // Fade display backlight ud
       CORETIMER_DelayMs (50);
    }
}


void setBackLightIntensity(uint16_t intensity)
{
    if(intensity > 0)
    {
        OCMP9_Enable();
        OC9RS = 5000 * 2 / 100 * intensity;
    }
    else
       OCMP9_Disable();        
}

void screenSwap(void)
{
    if(appData.screenSwapDelayExpired)
    {
        DEBUG_PRINT("ScreenSwapDelayExpired\r\n");
        setDisplayIntensity();
        appData.screenSwapDelayExpired = 0;
    }
}