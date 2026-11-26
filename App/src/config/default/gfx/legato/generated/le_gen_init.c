#include "gfx/legato/generated/le_gen_init.h"

static int32_t currentScreen;
static int32_t changingToScreen;

void legato_initializeScreenState(void)
{
    leSetStringTable(&stringTable);

    initializeStrings();

    screenInit_SN_SET();
    screenInit_leftPowerMissingScreen();
    screenInit_actionScreen();
    screenInit_avInputScreen();
    screenInit_dacGainSimpleView();
    screenInit_digitalSetupScreen();
    screenInit_displayIntensityScreen();
    screenInit_displaySimpleView();
    screenInit_dsdLpSimpleView();
    screenInit_errorDisplay();
    screenInit_filterSimpleView();
    screenInit_greenBiasScreen();
    screenInit_inpLvlMatchScreen();
    screenInit_irSourceScreen();
    screenInit_mainMenuScreen();
    screenInit_pickupSelectScreen();
    screenInit_qwertyScreen();
    screenInit_renameInputsScreen();
    screenInit_restoreSettingScreen();
    screenInit_simpleViewScreen();
    screenInit_splashScreen();
    screenInit_volSettingsScreen();
    screenInit_wrongAcVoltageScreen();

    currentScreen = -1;
    changingToScreen = -1;

    legato_showScreen(screenID_splashScreen);
}

uint32_t legato_getCurrentScreen(void)
{
    return currentScreen;
}

static void legato_hideCurrentScreen(void)
{
    switch(currentScreen)
    {
        case screenID_SN_SET:
        {
            screenHide_SN_SET();
            currentScreen = 0;
            break;
        }
        case screenID_leftPowerMissingScreen:
        {
            screenHide_leftPowerMissingScreen();
            currentScreen = 0;
            break;
        }
        case screenID_actionScreen:
        {
            screenHide_actionScreen();
            currentScreen = 0;
            break;
        }
        case screenID_avInputScreen:
        {
            screenHide_avInputScreen();
            currentScreen = 0;
            break;
        }
        case screenID_dacGainSimpleView:
        {
            screenHide_dacGainSimpleView();
            currentScreen = 0;
            break;
        }
        case screenID_digitalSetupScreen:
        {
            screenHide_digitalSetupScreen();
            currentScreen = 0;
            break;
        }
        case screenID_displayIntensityScreen:
        {
            screenHide_displayIntensityScreen();
            currentScreen = 0;
            break;
        }
        case screenID_displaySimpleView:
        {
            screenHide_displaySimpleView();
            currentScreen = 0;
            break;
        }
        case screenID_dsdLpSimpleView:
        {
            screenHide_dsdLpSimpleView();
            currentScreen = 0;
            break;
        }
        case screenID_errorDisplay:
        {
            screenHide_errorDisplay();
            currentScreen = 0;
            break;
        }
        case screenID_filterSimpleView:
        {
            screenHide_filterSimpleView();
            currentScreen = 0;
            break;
        }
        case screenID_greenBiasScreen:
        {
            screenHide_greenBiasScreen();
            currentScreen = 0;
            break;
        }
        case screenID_inpLvlMatchScreen:
        {
            screenHide_inpLvlMatchScreen();
            currentScreen = 0;
            break;
        }
        case screenID_irSourceScreen:
        {
            screenHide_irSourceScreen();
            currentScreen = 0;
            break;
        }
        case screenID_mainMenuScreen:
        {
            screenHide_mainMenuScreen();
            currentScreen = 0;
            break;
        }
        case screenID_pickupSelectScreen:
        {
            screenHide_pickupSelectScreen();
            currentScreen = 0;
            break;
        }
        case screenID_qwertyScreen:
        {
            screenHide_qwertyScreen();
            currentScreen = 0;
            break;
        }
        case screenID_renameInputsScreen:
        {
            screenHide_renameInputsScreen();
            currentScreen = 0;
            break;
        }
        case screenID_restoreSettingScreen:
        {
            screenHide_restoreSettingScreen();
            currentScreen = 0;
            break;
        }
        case screenID_simpleViewScreen:
        {
            screenHide_simpleViewScreen();
            currentScreen = 0;
            break;
        }
        case screenID_splashScreen:
        {
            screenHide_splashScreen();
            currentScreen = 0;
            break;
        }
        case screenID_volSettingsScreen:
        {
            screenHide_volSettingsScreen();
            currentScreen = 0;
            break;
        }
        case screenID_wrongAcVoltageScreen:
        {
            screenHide_wrongAcVoltageScreen();
            currentScreen = 0;
            break;
        }
    }
}

void legato_showScreen(uint32_t id)
{
    if(changingToScreen >= 0)
        return;

    changingToScreen = id;
}

void legato_updateScreenState(void)
{
    if(leIsDrawing() == LE_TRUE)
        return;

    if(changingToScreen >= 0)
    {
        legato_hideCurrentScreen();

        switch(changingToScreen)
        {
            case screenID_SN_SET:
            {
                screenShow_SN_SET();
                break;
            }
            case screenID_leftPowerMissingScreen:
            {
                screenShow_leftPowerMissingScreen();
                break;
            }
            case screenID_actionScreen:
            {
                screenShow_actionScreen();
                break;
            }
            case screenID_avInputScreen:
            {
                screenShow_avInputScreen();
                break;
            }
            case screenID_dacGainSimpleView:
            {
                screenShow_dacGainSimpleView();
                break;
            }
            case screenID_digitalSetupScreen:
            {
                screenShow_digitalSetupScreen();
                break;
            }
            case screenID_displayIntensityScreen:
            {
                screenShow_displayIntensityScreen();
                break;
            }
            case screenID_displaySimpleView:
            {
                screenShow_displaySimpleView();
                break;
            }
            case screenID_dsdLpSimpleView:
            {
                screenShow_dsdLpSimpleView();
                break;
            }
            case screenID_errorDisplay:
            {
                screenShow_errorDisplay();
                break;
            }
            case screenID_filterSimpleView:
            {
                screenShow_filterSimpleView();
                break;
            }
            case screenID_greenBiasScreen:
            {
                screenShow_greenBiasScreen();
                break;
            }
            case screenID_inpLvlMatchScreen:
            {
                screenShow_inpLvlMatchScreen();
                break;
            }
            case screenID_irSourceScreen:
            {
                screenShow_irSourceScreen();
                break;
            }
            case screenID_mainMenuScreen:
            {
                screenShow_mainMenuScreen();
                break;
            }
            case screenID_pickupSelectScreen:
            {
                screenShow_pickupSelectScreen();
                break;
            }
            case screenID_qwertyScreen:
            {
                screenShow_qwertyScreen();
                break;
            }
            case screenID_renameInputsScreen:
            {
                screenShow_renameInputsScreen();
                break;
            }
            case screenID_restoreSettingScreen:
            {
                screenShow_restoreSettingScreen();
                break;
            }
            case screenID_simpleViewScreen:
            {
                screenShow_simpleViewScreen();
                break;
            }
            case screenID_splashScreen:
            {
                screenShow_splashScreen();
                break;
            }
            case screenID_volSettingsScreen:
            {
                screenShow_volSettingsScreen();
                break;
            }
            case screenID_wrongAcVoltageScreen:
            {
                screenShow_wrongAcVoltageScreen();
                break;
            }
        }

        currentScreen = changingToScreen;
        changingToScreen = -1;
    }

    switch(currentScreen)
    {
        case screenID_SN_SET:
        {
            screenUpdate_SN_SET();
            break;
        }
        case screenID_leftPowerMissingScreen:
        {
            screenUpdate_leftPowerMissingScreen();
            break;
        }
        case screenID_actionScreen:
        {
            screenUpdate_actionScreen();
            break;
        }
        case screenID_avInputScreen:
        {
            screenUpdate_avInputScreen();
            break;
        }
        case screenID_dacGainSimpleView:
        {
            screenUpdate_dacGainSimpleView();
            break;
        }
        case screenID_digitalSetupScreen:
        {
            screenUpdate_digitalSetupScreen();
            break;
        }
        case screenID_displayIntensityScreen:
        {
            screenUpdate_displayIntensityScreen();
            break;
        }
        case screenID_displaySimpleView:
        {
            screenUpdate_displaySimpleView();
            break;
        }
        case screenID_dsdLpSimpleView:
        {
            screenUpdate_dsdLpSimpleView();
            break;
        }
        case screenID_errorDisplay:
        {
            screenUpdate_errorDisplay();
            break;
        }
        case screenID_filterSimpleView:
        {
            screenUpdate_filterSimpleView();
            break;
        }
        case screenID_greenBiasScreen:
        {
            screenUpdate_greenBiasScreen();
            break;
        }
        case screenID_inpLvlMatchScreen:
        {
            screenUpdate_inpLvlMatchScreen();
            break;
        }
        case screenID_irSourceScreen:
        {
            screenUpdate_irSourceScreen();
            break;
        }
        case screenID_mainMenuScreen:
        {
            screenUpdate_mainMenuScreen();
            break;
        }
        case screenID_pickupSelectScreen:
        {
            screenUpdate_pickupSelectScreen();
            break;
        }
        case screenID_qwertyScreen:
        {
            screenUpdate_qwertyScreen();
            break;
        }
        case screenID_renameInputsScreen:
        {
            screenUpdate_renameInputsScreen();
            break;
        }
        case screenID_restoreSettingScreen:
        {
            screenUpdate_restoreSettingScreen();
            break;
        }
        case screenID_simpleViewScreen:
        {
            screenUpdate_simpleViewScreen();
            break;
        }
        case screenID_splashScreen:
        {
            screenUpdate_splashScreen();
            break;
        }
        case screenID_volSettingsScreen:
        {
            screenUpdate_volSettingsScreen();
            break;
        }
        case screenID_wrongAcVoltageScreen:
        {
            screenUpdate_wrongAcVoltageScreen();
            break;
        }
    }
}

leBool legato_isChangingScreens(void)
{
    return changingToScreen != -1;
}

