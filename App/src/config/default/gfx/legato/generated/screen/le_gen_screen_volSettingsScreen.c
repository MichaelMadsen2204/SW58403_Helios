#include "gfx/legato/generated/screen/le_gen_screen_volSettingsScreen.h"

// screen member widget declarations
static leWidget* root0;

leWidget* volSettingsScreen_background;
leImageWidget* volSettingsScreen_BalanceImg;
leImageWidget* volSettingsScreen_startVolButImg;
leImageWidget* volSettingsScreen_maxVolButImg;
leImageWidget* volSettingsScreen_volBackToMenuImg;
leLabelWidget* volSettingsScreen_volSettingMenuHeader;
leRectangleWidget* volSettingsScreen_volSettingLineRightSide;
leRectangleWidget* volSettingsScreen_volSettingLineLeftSide;
leLabelWidget* volSettingsScreen_startVolLabel;
leLabelWidget* volSettingsScreen_VolStartLabel;
leLabelWidget* volSettingsScreen_volSettingCurStartLevelLabel;
leButtonWidget* volSettingsScreen_volSetStartVolPlusBut;
leButtonWidget* volSettingsScreen_volSetStartVolMinusBut;
leLabelWidget* volSettingsScreen_maxVolLabel;
leLabelWidget* volSettingsScreen_volMaxLabel;
leLabelWidget* volSettingsScreen_volSettingCurMaxLevelLabel;
leButtonWidget* volSettingsScreen_volSetMaxVolPlusBut;
leButtonWidget* volSettingsScreen_volSetMaxVolMinusBut;
leButtonWidget* volSettingsScreen_volSetBackToMenuBut;
leTextFieldWidget* volSettingsScreen_balance;
leTextFieldWidget* volSettingsScreen_balanceHeader;
leButtonWidget* volSettingsScreen_balanceLeftBut;
leButtonWidget* volSettingsScreen_balanceRightBut;

static leBool initialized = LE_FALSE;
static leBool showing = LE_FALSE;

leResult screenInit_volSettingsScreen(void)
{
    if(initialized == LE_TRUE)
        return LE_FAILURE;

    initialized = LE_TRUE;

    return LE_SUCCESS;
}

leResult screenShow_volSettingsScreen(void)
{
    if(showing == LE_TRUE)
        return LE_FAILURE;

    // layer 0
    root0 = leWidget_New();
    root0->fn->setSize(root0, 480, 272);
    root0->fn->setBackgroundType(root0, LE_WIDGET_BACKGROUND_NONE);
    root0->fn->setMargins(root0, 0, 0, 0, 0);
    root0->flags |= LE_WIDGET_IGNOREEVENTS;
    root0->flags |= LE_WIDGET_IGNOREPICK;

    volSettingsScreen_background = leWidget_New();
    volSettingsScreen_background->fn->setPosition(volSettingsScreen_background, 0, 0);
    volSettingsScreen_background->fn->setSize(volSettingsScreen_background, 480, 272);
    volSettingsScreen_background->fn->setScheme(volSettingsScreen_background, &BlackScheme);
    root0->fn->addChild(root0, (leWidget*)volSettingsScreen_background);

    volSettingsScreen_startVolButImg = leImageWidget_New();
    volSettingsScreen_startVolButImg->fn->setPosition(volSettingsScreen_startVolButImg, 30, 56);
    volSettingsScreen_startVolButImg->fn->setSize(volSettingsScreen_startVolButImg, 75, 188);
    volSettingsScreen_startVolButImg->fn->setScheme(volSettingsScreen_startVolButImg, &BlackScheme);
    volSettingsScreen_startVolButImg->fn->setBorderType(volSettingsScreen_startVolButImg, LE_WIDGET_BORDER_NONE);
    volSettingsScreen_startVolButImg->fn->setVAlignment(volSettingsScreen_startVolButImg, LE_VALIGN_BOTTOM);
    volSettingsScreen_startVolButImg->fn->setImage(volSettingsScreen_startVolButImg, (leImage*)&ILMVolButtons);
    volSettingsScreen_background->fn->addChild(volSettingsScreen_background, (leWidget*)volSettingsScreen_startVolButImg);

    volSettingsScreen_startVolLabel = leLabelWidget_New();
    volSettingsScreen_startVolLabel->fn->setPosition(volSettingsScreen_startVolLabel, -13, 18);
    volSettingsScreen_startVolLabel->fn->setScheme(volSettingsScreen_startVolLabel, &BlackScheme);
    volSettingsScreen_startVolLabel->fn->setHAlignment(volSettingsScreen_startVolLabel, LE_HALIGN_CENTER);
    volSettingsScreen_startVolLabel->fn->setVAlignment(volSettingsScreen_startVolLabel, LE_VALIGN_TOP);
    volSettingsScreen_startVolLabel->fn->setString(volSettingsScreen_startVolLabel, (leString*)&string_volSettingVolStr);
    volSettingsScreen_startVolButImg->fn->addChild(volSettingsScreen_startVolButImg, (leWidget*)volSettingsScreen_startVolLabel);

    volSettingsScreen_VolStartLabel = leLabelWidget_New();
    volSettingsScreen_VolStartLabel->fn->setPosition(volSettingsScreen_VolStartLabel, -15, -2);
    volSettingsScreen_VolStartLabel->fn->setScheme(volSettingsScreen_VolStartLabel, &BlackScheme);
    volSettingsScreen_VolStartLabel->fn->setHAlignment(volSettingsScreen_VolStartLabel, LE_HALIGN_CENTER);
    volSettingsScreen_VolStartLabel->fn->setVAlignment(volSettingsScreen_VolStartLabel, LE_VALIGN_TOP);
    volSettingsScreen_VolStartLabel->fn->setString(volSettingsScreen_VolStartLabel, (leString*)&string_volSettingStartStr);
    volSettingsScreen_startVolButImg->fn->addChild(volSettingsScreen_startVolButImg, (leWidget*)volSettingsScreen_VolStartLabel);

    volSettingsScreen_volSettingCurStartLevelLabel = leLabelWidget_New();
    volSettingsScreen_volSettingCurStartLevelLabel->fn->setPosition(volSettingsScreen_volSettingCurStartLevelLabel, 2, 46);
    volSettingsScreen_volSettingCurStartLevelLabel->fn->setSize(volSettingsScreen_volSettingCurStartLevelLabel, 70, 48);
    volSettingsScreen_volSettingCurStartLevelLabel->fn->setScheme(volSettingsScreen_volSettingCurStartLevelLabel, &BlackScheme);
    volSettingsScreen_volSettingCurStartLevelLabel->fn->setBackgroundType(volSettingsScreen_volSettingCurStartLevelLabel, LE_WIDGET_BACKGROUND_NONE);
    volSettingsScreen_volSettingCurStartLevelLabel->fn->setHAlignment(volSettingsScreen_volSettingCurStartLevelLabel, LE_HALIGN_CENTER);
    volSettingsScreen_volSettingCurStartLevelLabel->fn->setString(volSettingsScreen_volSettingCurStartLevelLabel, (leString*)&string_curStartLevelStr);
    volSettingsScreen_startVolButImg->fn->addChild(volSettingsScreen_startVolButImg, (leWidget*)volSettingsScreen_volSettingCurStartLevelLabel);

    volSettingsScreen_volSetStartVolPlusBut = leButtonWidget_New();
    volSettingsScreen_volSetStartVolPlusBut->fn->setPosition(volSettingsScreen_volSetStartVolPlusBut, 5, 88);
    volSettingsScreen_volSetStartVolPlusBut->fn->setSize(volSettingsScreen_volSetStartVolPlusBut, 64, 40);
    volSettingsScreen_volSetStartVolPlusBut->fn->setBackgroundType(volSettingsScreen_volSetStartVolPlusBut, LE_WIDGET_BACKGROUND_NONE);
    volSettingsScreen_volSetStartVolPlusBut->fn->setBorderType(volSettingsScreen_volSetStartVolPlusBut, LE_WIDGET_BORDER_NONE);
    volSettingsScreen_volSetStartVolPlusBut->fn->setPressedEventCallback(volSettingsScreen_volSetStartVolPlusBut, event_volSettingsScreen_volSetStartVolPlusBut_OnPressed);
    volSettingsScreen_volSetStartVolPlusBut->fn->setReleasedEventCallback(volSettingsScreen_volSetStartVolPlusBut, event_volSettingsScreen_volSetStartVolPlusBut_OnReleased);
    volSettingsScreen_startVolButImg->fn->addChild(volSettingsScreen_startVolButImg, (leWidget*)volSettingsScreen_volSetStartVolPlusBut);

    volSettingsScreen_volSetStartVolMinusBut = leButtonWidget_New();
    volSettingsScreen_volSetStartVolMinusBut->fn->setPosition(volSettingsScreen_volSetStartVolMinusBut, 4, 147);
    volSettingsScreen_volSetStartVolMinusBut->fn->setSize(volSettingsScreen_volSetStartVolMinusBut, 64, 40);
    volSettingsScreen_volSetStartVolMinusBut->fn->setBackgroundType(volSettingsScreen_volSetStartVolMinusBut, LE_WIDGET_BACKGROUND_NONE);
    volSettingsScreen_volSetStartVolMinusBut->fn->setBorderType(volSettingsScreen_volSetStartVolMinusBut, LE_WIDGET_BORDER_NONE);
    volSettingsScreen_volSetStartVolMinusBut->fn->setPressedEventCallback(volSettingsScreen_volSetStartVolMinusBut, event_volSettingsScreen_volSetStartVolMinusBut_OnPressed);
    volSettingsScreen_volSetStartVolMinusBut->fn->setReleasedEventCallback(volSettingsScreen_volSetStartVolMinusBut, event_volSettingsScreen_volSetStartVolMinusBut_OnReleased);
    volSettingsScreen_startVolButImg->fn->addChild(volSettingsScreen_startVolButImg, (leWidget*)volSettingsScreen_volSetStartVolMinusBut);

    volSettingsScreen_maxVolButImg = leImageWidget_New();
    volSettingsScreen_maxVolButImg->fn->setPosition(volSettingsScreen_maxVolButImg, 190, 55);
    volSettingsScreen_maxVolButImg->fn->setSize(volSettingsScreen_maxVolButImg, 75, 188);
    volSettingsScreen_maxVolButImg->fn->setScheme(volSettingsScreen_maxVolButImg, &BlackScheme);
    volSettingsScreen_maxVolButImg->fn->setBorderType(volSettingsScreen_maxVolButImg, LE_WIDGET_BORDER_NONE);
    volSettingsScreen_maxVolButImg->fn->setVAlignment(volSettingsScreen_maxVolButImg, LE_VALIGN_BOTTOM);
    volSettingsScreen_maxVolButImg->fn->setImage(volSettingsScreen_maxVolButImg, (leImage*)&ILMVolButtons);
    volSettingsScreen_background->fn->addChild(volSettingsScreen_background, (leWidget*)volSettingsScreen_maxVolButImg);

    volSettingsScreen_maxVolLabel = leLabelWidget_New();
    volSettingsScreen_maxVolLabel->fn->setPosition(volSettingsScreen_maxVolLabel, -13, 18);
    volSettingsScreen_maxVolLabel->fn->setScheme(volSettingsScreen_maxVolLabel, &BlackScheme);
    volSettingsScreen_maxVolLabel->fn->setHAlignment(volSettingsScreen_maxVolLabel, LE_HALIGN_CENTER);
    volSettingsScreen_maxVolLabel->fn->setVAlignment(volSettingsScreen_maxVolLabel, LE_VALIGN_TOP);
    volSettingsScreen_maxVolLabel->fn->setString(volSettingsScreen_maxVolLabel, (leString*)&string_volSettingVolStr);
    volSettingsScreen_maxVolButImg->fn->addChild(volSettingsScreen_maxVolButImg, (leWidget*)volSettingsScreen_maxVolLabel);

    volSettingsScreen_volMaxLabel = leLabelWidget_New();
    volSettingsScreen_volMaxLabel->fn->setPosition(volSettingsScreen_volMaxLabel, -12, -2);
    volSettingsScreen_volMaxLabel->fn->setScheme(volSettingsScreen_volMaxLabel, &BlackScheme);
    volSettingsScreen_volMaxLabel->fn->setHAlignment(volSettingsScreen_volMaxLabel, LE_HALIGN_CENTER);
    volSettingsScreen_volMaxLabel->fn->setVAlignment(volSettingsScreen_volMaxLabel, LE_VALIGN_TOP);
    volSettingsScreen_volMaxLabel->fn->setString(volSettingsScreen_volMaxLabel, (leString*)&string_volSettingMaxStr);
    volSettingsScreen_maxVolButImg->fn->addChild(volSettingsScreen_maxVolButImg, (leWidget*)volSettingsScreen_volMaxLabel);

    volSettingsScreen_volSettingCurMaxLevelLabel = leLabelWidget_New();
    volSettingsScreen_volSettingCurMaxLevelLabel->fn->setPosition(volSettingsScreen_volSettingCurMaxLevelLabel, 3, 47);
    volSettingsScreen_volSettingCurMaxLevelLabel->fn->setSize(volSettingsScreen_volSettingCurMaxLevelLabel, 70, 48);
    volSettingsScreen_volSettingCurMaxLevelLabel->fn->setScheme(volSettingsScreen_volSettingCurMaxLevelLabel, &BlackScheme);
    volSettingsScreen_volSettingCurMaxLevelLabel->fn->setBackgroundType(volSettingsScreen_volSettingCurMaxLevelLabel, LE_WIDGET_BACKGROUND_NONE);
    volSettingsScreen_volSettingCurMaxLevelLabel->fn->setHAlignment(volSettingsScreen_volSettingCurMaxLevelLabel, LE_HALIGN_CENTER);
    volSettingsScreen_volSettingCurMaxLevelLabel->fn->setString(volSettingsScreen_volSettingCurMaxLevelLabel, (leString*)&string_curMaxLevelStr);
    volSettingsScreen_maxVolButImg->fn->addChild(volSettingsScreen_maxVolButImg, (leWidget*)volSettingsScreen_volSettingCurMaxLevelLabel);

    volSettingsScreen_volSetMaxVolPlusBut = leButtonWidget_New();
    volSettingsScreen_volSetMaxVolPlusBut->fn->setPosition(volSettingsScreen_volSetMaxVolPlusBut, 5, 88);
    volSettingsScreen_volSetMaxVolPlusBut->fn->setSize(volSettingsScreen_volSetMaxVolPlusBut, 64, 40);
    volSettingsScreen_volSetMaxVolPlusBut->fn->setBackgroundType(volSettingsScreen_volSetMaxVolPlusBut, LE_WIDGET_BACKGROUND_NONE);
    volSettingsScreen_volSetMaxVolPlusBut->fn->setBorderType(volSettingsScreen_volSetMaxVolPlusBut, LE_WIDGET_BORDER_NONE);
    volSettingsScreen_volSetMaxVolPlusBut->fn->setPressedEventCallback(volSettingsScreen_volSetMaxVolPlusBut, event_volSettingsScreen_volSetMaxVolPlusBut_OnPressed);
    volSettingsScreen_volSetMaxVolPlusBut->fn->setReleasedEventCallback(volSettingsScreen_volSetMaxVolPlusBut, event_volSettingsScreen_volSetMaxVolPlusBut_OnReleased);
    volSettingsScreen_maxVolButImg->fn->addChild(volSettingsScreen_maxVolButImg, (leWidget*)volSettingsScreen_volSetMaxVolPlusBut);

    volSettingsScreen_volSetMaxVolMinusBut = leButtonWidget_New();
    volSettingsScreen_volSetMaxVolMinusBut->fn->setPosition(volSettingsScreen_volSetMaxVolMinusBut, 6, 147);
    volSettingsScreen_volSetMaxVolMinusBut->fn->setSize(volSettingsScreen_volSetMaxVolMinusBut, 64, 40);
    volSettingsScreen_volSetMaxVolMinusBut->fn->setBackgroundType(volSettingsScreen_volSetMaxVolMinusBut, LE_WIDGET_BACKGROUND_NONE);
    volSettingsScreen_volSetMaxVolMinusBut->fn->setBorderType(volSettingsScreen_volSetMaxVolMinusBut, LE_WIDGET_BORDER_NONE);
    volSettingsScreen_volSetMaxVolMinusBut->fn->setPressedEventCallback(volSettingsScreen_volSetMaxVolMinusBut, event_volSettingsScreen_volSetMaxVolMinusBut_OnPressed);
    volSettingsScreen_volSetMaxVolMinusBut->fn->setReleasedEventCallback(volSettingsScreen_volSetMaxVolMinusBut, event_volSettingsScreen_volSetMaxVolMinusBut_OnReleased);
    volSettingsScreen_maxVolButImg->fn->addChild(volSettingsScreen_maxVolButImg, (leWidget*)volSettingsScreen_volSetMaxVolMinusBut);

    volSettingsScreen_volBackToMenuImg = leImageWidget_New();
    volSettingsScreen_volBackToMenuImg->fn->setPosition(volSettingsScreen_volBackToMenuImg, 340, 200);
    volSettingsScreen_volBackToMenuImg->fn->setSize(volSettingsScreen_volBackToMenuImg, 115, 54);
    volSettingsScreen_volBackToMenuImg->fn->setScheme(volSettingsScreen_volBackToMenuImg, &BlackScheme);
    volSettingsScreen_volBackToMenuImg->fn->setBorderType(volSettingsScreen_volBackToMenuImg, LE_WIDGET_BORDER_NONE);
    volSettingsScreen_volBackToMenuImg->fn->setImage(volSettingsScreen_volBackToMenuImg, (leImage*)&BackToMenu);
    volSettingsScreen_background->fn->addChild(volSettingsScreen_background, (leWidget*)volSettingsScreen_volBackToMenuImg);

    volSettingsScreen_volSetBackToMenuBut = leButtonWidget_New();
    volSettingsScreen_volSetBackToMenuBut->fn->setPosition(volSettingsScreen_volSetBackToMenuBut, 2, 6);
    volSettingsScreen_volSetBackToMenuBut->fn->setSize(volSettingsScreen_volSetBackToMenuBut, 111, 49);
    volSettingsScreen_volSetBackToMenuBut->fn->setBackgroundType(volSettingsScreen_volSetBackToMenuBut, LE_WIDGET_BACKGROUND_NONE);
    volSettingsScreen_volSetBackToMenuBut->fn->setBorderType(volSettingsScreen_volSetBackToMenuBut, LE_WIDGET_BORDER_NONE);
    volSettingsScreen_volSetBackToMenuBut->fn->setPressedEventCallback(volSettingsScreen_volSetBackToMenuBut, event_volSettingsScreen_volSetBackToMenuBut_OnPressed);
    volSettingsScreen_volBackToMenuImg->fn->addChild(volSettingsScreen_volBackToMenuImg, (leWidget*)volSettingsScreen_volSetBackToMenuBut);

    volSettingsScreen_volSettingMenuHeader = leLabelWidget_New();
    volSettingsScreen_volSettingMenuHeader->fn->setPosition(volSettingsScreen_volSettingMenuHeader, 0, 12);
    volSettingsScreen_volSettingMenuHeader->fn->setSize(volSettingsScreen_volSettingMenuHeader, 480, 25);
    volSettingsScreen_volSettingMenuHeader->fn->setScheme(volSettingsScreen_volSettingMenuHeader, &BlackScheme);
    volSettingsScreen_volSettingMenuHeader->fn->setBackgroundType(volSettingsScreen_volSettingMenuHeader, LE_WIDGET_BACKGROUND_NONE);
    volSettingsScreen_volSettingMenuHeader->fn->setHAlignment(volSettingsScreen_volSettingMenuHeader, LE_HALIGN_CENTER);
    volSettingsScreen_volSettingMenuHeader->fn->setString(volSettingsScreen_volSettingMenuHeader, (leString*)&string_volSettingHeaderStr);
    volSettingsScreen_background->fn->addChild(volSettingsScreen_background, (leWidget*)volSettingsScreen_volSettingMenuHeader);

    volSettingsScreen_volSettingLineRightSide = leRectangleWidget_New();
    volSettingsScreen_volSettingLineRightSide->fn->setPosition(volSettingsScreen_volSettingLineRightSide, 337, 25);
    volSettingsScreen_volSettingLineRightSide->fn->setSize(volSettingsScreen_volSettingLineRightSide, 117, 3);
    volSettingsScreen_volSettingLineRightSide->fn->setScheme(volSettingsScreen_volSettingLineRightSide, &WhiteScheme);
    volSettingsScreen_volSettingLineRightSide->fn->setBorderType(volSettingsScreen_volSettingLineRightSide, LE_WIDGET_BORDER_NONE);
    volSettingsScreen_volSettingLineRightSide->fn->setThickness(volSettingsScreen_volSettingLineRightSide, 3);
    volSettingsScreen_background->fn->addChild(volSettingsScreen_background, (leWidget*)volSettingsScreen_volSettingLineRightSide);

    volSettingsScreen_volSettingLineLeftSide = leRectangleWidget_New();
    volSettingsScreen_volSettingLineLeftSide->fn->setPosition(volSettingsScreen_volSettingLineLeftSide, 26, 25);
    volSettingsScreen_volSettingLineLeftSide->fn->setSize(volSettingsScreen_volSettingLineLeftSide, 117, 3);
    volSettingsScreen_volSettingLineLeftSide->fn->setScheme(volSettingsScreen_volSettingLineLeftSide, &WhiteScheme);
    volSettingsScreen_volSettingLineLeftSide->fn->setBorderType(volSettingsScreen_volSettingLineLeftSide, LE_WIDGET_BORDER_NONE);
    volSettingsScreen_volSettingLineLeftSide->fn->setThickness(volSettingsScreen_volSettingLineLeftSide, 3);
    volSettingsScreen_background->fn->addChild(volSettingsScreen_background, (leWidget*)volSettingsScreen_volSettingLineLeftSide);

    volSettingsScreen_BalanceImg = leImageWidget_New();
    volSettingsScreen_BalanceImg->fn->setPosition(volSettingsScreen_BalanceImg, 332, 57);
    volSettingsScreen_BalanceImg->fn->setSize(volSettingsScreen_BalanceImg, 126, 134);
    volSettingsScreen_BalanceImg->fn->setScheme(volSettingsScreen_BalanceImg, &BlackScheme);
    volSettingsScreen_BalanceImg->fn->setBorderType(volSettingsScreen_BalanceImg, LE_WIDGET_BORDER_NONE);
    volSettingsScreen_BalanceImg->fn->setVAlignment(volSettingsScreen_BalanceImg, LE_VALIGN_BOTTOM);
    volSettingsScreen_BalanceImg->fn->setImage(volSettingsScreen_BalanceImg, (leImage*)&balButtons);
    root0->fn->addChild(root0, (leWidget*)volSettingsScreen_BalanceImg);

    volSettingsScreen_balance = leTextFieldWidget_New();
    volSettingsScreen_balance->fn->setPosition(volSettingsScreen_balance, 7, 32);
    volSettingsScreen_balance->fn->setSize(volSettingsScreen_balance, 112, 25);
    volSettingsScreen_balance->fn->setScheme(volSettingsScreen_balance, &BlackScheme);
    volSettingsScreen_balance->fn->setBackgroundType(volSettingsScreen_balance, LE_WIDGET_BACKGROUND_NONE);
    volSettingsScreen_balance->fn->setBorderType(volSettingsScreen_balance, LE_WIDGET_BORDER_NONE);
    volSettingsScreen_balance->fn->setHAlignment(volSettingsScreen_balance, LE_HALIGN_LEFT);
    volSettingsScreen_balance->fn->setString(volSettingsScreen_balance, (leString*)&string_balanceStr);
    volSettingsScreen_balance->fn->setFont(volSettingsScreen_balance, (leFont*)&Avenir18);
    volSettingsScreen_balance->fn->setCursorEnabled(volSettingsScreen_balance, LE_FALSE);
    volSettingsScreen_balance->fn->setClearValueOnFirstEdit(volSettingsScreen_balance, LE_FALSE);
    volSettingsScreen_BalanceImg->fn->addChild(volSettingsScreen_BalanceImg, (leWidget*)volSettingsScreen_balance);

    volSettingsScreen_balanceHeader = leTextFieldWidget_New();
    volSettingsScreen_balanceHeader->fn->setPosition(volSettingsScreen_balanceHeader, 13, -4);
    volSettingsScreen_balanceHeader->fn->setScheme(volSettingsScreen_balanceHeader, &BlackScheme);
    volSettingsScreen_balanceHeader->fn->setBorderType(volSettingsScreen_balanceHeader, LE_WIDGET_BORDER_NONE);
    volSettingsScreen_balanceHeader->fn->setString(volSettingsScreen_balanceHeader, (leString*)&string_balanceHeader);
    volSettingsScreen_BalanceImg->fn->addChild(volSettingsScreen_BalanceImg, (leWidget*)volSettingsScreen_balanceHeader);

    volSettingsScreen_balanceLeftBut = leButtonWidget_New();
    volSettingsScreen_balanceLeftBut->fn->setPosition(volSettingsScreen_balanceLeftBut, 4, 69);
    volSettingsScreen_balanceLeftBut->fn->setSize(volSettingsScreen_balanceLeftBut, 50, 63);
    volSettingsScreen_balanceLeftBut->fn->setScheme(volSettingsScreen_balanceLeftBut, &BlackScheme);
    volSettingsScreen_balanceLeftBut->fn->setBackgroundType(volSettingsScreen_balanceLeftBut, LE_WIDGET_BACKGROUND_NONE);
    volSettingsScreen_balanceLeftBut->fn->setBorderType(volSettingsScreen_balanceLeftBut, LE_WIDGET_BORDER_NONE);
    volSettingsScreen_balanceLeftBut->fn->setPressedEventCallback(volSettingsScreen_balanceLeftBut, event_volSettingsScreen_balanceLeftBut_OnPressed);
    volSettingsScreen_balanceLeftBut->fn->setReleasedEventCallback(volSettingsScreen_balanceLeftBut, event_volSettingsScreen_balanceLeftBut_OnReleased);
    volSettingsScreen_BalanceImg->fn->addChild(volSettingsScreen_BalanceImg, (leWidget*)volSettingsScreen_balanceLeftBut);

    volSettingsScreen_balanceRightBut = leButtonWidget_New();
    volSettingsScreen_balanceRightBut->fn->setPosition(volSettingsScreen_balanceRightBut, 72, 69);
    volSettingsScreen_balanceRightBut->fn->setSize(volSettingsScreen_balanceRightBut, 50, 63);
    volSettingsScreen_balanceRightBut->fn->setScheme(volSettingsScreen_balanceRightBut, &BlackScheme);
    volSettingsScreen_balanceRightBut->fn->setBackgroundType(volSettingsScreen_balanceRightBut, LE_WIDGET_BACKGROUND_NONE);
    volSettingsScreen_balanceRightBut->fn->setBorderType(volSettingsScreen_balanceRightBut, LE_WIDGET_BORDER_NONE);
    volSettingsScreen_balanceRightBut->fn->setPressedEventCallback(volSettingsScreen_balanceRightBut, event_volSettingsScreen_balanceRightBut_OnPressed);
    volSettingsScreen_balanceRightBut->fn->setReleasedEventCallback(volSettingsScreen_balanceRightBut, event_volSettingsScreen_balanceRightBut_OnReleased);
    volSettingsScreen_BalanceImg->fn->addChild(volSettingsScreen_BalanceImg, (leWidget*)volSettingsScreen_balanceRightBut);

    leAddRootWidget(root0, 0);
    leSetLayerColorMode(0, LE_COLOR_MODE_RGB_565);

    volSettingsScreen_OnShow(); // raise event

    showing = LE_TRUE;

    return LE_SUCCESS;
}

void screenUpdate_volSettingsScreen(void)
{
    root0->fn->setSize(root0, root0->rect.width, root0->rect.height);
}

void screenHide_volSettingsScreen(void)
{
    volSettingsScreen_OnHide(); // raise event


    leRemoveRootWidget(root0, 0);
    leWidget_Delete(root0);
    root0 = NULL;

    volSettingsScreen_background = NULL;
    volSettingsScreen_BalanceImg = NULL;
    volSettingsScreen_startVolButImg = NULL;
    volSettingsScreen_maxVolButImg = NULL;
    volSettingsScreen_volBackToMenuImg = NULL;
    volSettingsScreen_volSettingMenuHeader = NULL;
    volSettingsScreen_volSettingLineRightSide = NULL;
    volSettingsScreen_volSettingLineLeftSide = NULL;
    volSettingsScreen_startVolLabel = NULL;
    volSettingsScreen_VolStartLabel = NULL;
    volSettingsScreen_volSettingCurStartLevelLabel = NULL;
    volSettingsScreen_volSetStartVolPlusBut = NULL;
    volSettingsScreen_volSetStartVolMinusBut = NULL;
    volSettingsScreen_maxVolLabel = NULL;
    volSettingsScreen_volMaxLabel = NULL;
    volSettingsScreen_volSettingCurMaxLevelLabel = NULL;
    volSettingsScreen_volSetMaxVolPlusBut = NULL;
    volSettingsScreen_volSetMaxVolMinusBut = NULL;
    volSettingsScreen_volSetBackToMenuBut = NULL;
    volSettingsScreen_balance = NULL;
    volSettingsScreen_balanceHeader = NULL;
    volSettingsScreen_balanceLeftBut = NULL;
    volSettingsScreen_balanceRightBut = NULL;


    showing = LE_FALSE;
}

void screenDestroy_volSettingsScreen(void)
{
    if(initialized == LE_FALSE)
        return;

    initialized = LE_FALSE;
}

leWidget* screenGetRoot_volSettingsScreen(uint32_t lyrIdx)
{
    if(lyrIdx >= LE_LAYER_COUNT)
        return NULL;

    switch(lyrIdx)
    {
        case 0:
        {
            return root0;
        }
        default:
        {
            return NULL;
        }
    }
}

