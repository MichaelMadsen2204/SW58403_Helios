#include "definitions.h" // indeholder app.h, system headers, legato types mm.
#include "gfx/legato/generated/screen/le_gen_screen_avInputScreen.h" // for actionScreen_dispOnButton
#include "ui_globals.h"
#include "app.h"
#include "ScreenAV_Setup.h"


static volatile bool g_avUiProgrammatic = false;

static inline void AvNoneUi_Update(void)
{
    const leBool isNone = (appData.avInp == AV_NONE) ? LE_TRUE : LE_FALSE;
    g_avUiProgrammatic = true;
    avInputScreen_noneButton->fn->setEnabled(avInputScreen_noneButton, isNone ? LE_FALSE : LE_TRUE);
    avInputScreen_noneButton->fn->setPressed(avInputScreen_noneButton, isNone);
    g_avUiProgrammatic = false;
}


void event_avInputScreen_inp3Button_OnPressed(leButtonWidget* btn)
{
    if (g_avUiProgrammatic) return;
    appData.avInp |= AV_3;
    
    AvNoneUi_Update();
    
    
    //printf("3 pressed\r\n");
}

void event_avInputScreen_inp3Button_OnReleased(leButtonWidget* btn)
{
    if (g_avUiProgrammatic) return;
    appData.avInp &= (uint8_t)~AV_3;

    
    AvNoneUi_Update();
    

    //printf("3 released\r\n");
}

void event_avInputScreen_inp4Button_OnPressed(leButtonWidget* btn)
{
    if (g_avUiProgrammatic) return;
    appData.avInp |= AV_4;
    
    AvNoneUi_Update();
    

    
    //printf("4 pressed\r\n");
}

void event_avInputScreen_inp4Button_OnReleased(leButtonWidget* btn)
{
    if (g_avUiProgrammatic) return;
    appData.avInp &= (uint8_t)~AV_4;

    AvNoneUi_Update();
    
    //printf("4 released\r\n");
}


void event_avInputScreen_noneButton_OnPressed(leButtonWidget* btn)
{
    if (g_avUiProgrammatic || appData.avInp == AV_NONE) return;

    appData.avInp = AV_NONE;

    g_avUiProgrammatic = true;
    avInputScreen_inp3Button->fn->setPressed(avInputScreen_inp3Button, LE_FALSE);
    avInputScreen_inp4Button->fn->setPressed(avInputScreen_inp4Button, LE_FALSE);
    avInputScreen_noneButton->fn->setEnabled(avInputScreen_noneButton, LE_FALSE);
    g_avUiProgrammatic = false;

   // printf("none pressed\r\n");
}


void event_avInputScreen_menuExitButton_OnPressed(leButtonWidget* btn)
{
    legato_showScreen(screenID_mainMenuScreen);  
};
void avInputScreen_OnShow(void)
{
    g_avUiProgrammatic = true;

    avInputScreen_inp3Button->fn->setPressed(avInputScreen_inp3Button, (appData.avInp & AV_3) ? LE_TRUE : LE_FALSE);
    avInputScreen_inp4Button->fn->setPressed(avInputScreen_inp4Button, (appData.avInp & AV_4) ? LE_TRUE : LE_FALSE);
    avInputScreen_noneButton->fn->setEnabled(avInputScreen_noneButton,(appData.avInp == AV_NONE) ? LE_FALSE : LE_TRUE);
    avInputScreen_noneButton->fn->setPressed(avInputScreen_noneButton, (appData.avInp == AV_NONE) ? LE_TRUE : LE_FALSE);
    
    g_avUiProgrammatic = false;
}


void avInputScreen_OnHide(void)
{
    saveAvSettings();
};


