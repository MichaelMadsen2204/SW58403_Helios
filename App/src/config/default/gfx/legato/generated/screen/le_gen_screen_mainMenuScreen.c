#include "gfx/legato/generated/screen/le_gen_screen_mainMenuScreen.h"

// screen member widget declarations
static leWidget* root0;

leWidget* mainMenuScreen_BackgroundPanel;
leWidget* mainMenuScreen_fanErrorPanel;
leButtonWidget* mainMenuScreen_menuExitBut;
leButtonWidget* mainMenuScreen_menuVolBut;
leButtonWidget* mainMenuScreen_menuDisplayBut;
leButtonWidget* mainMenuScreen_menuIrSrcBut;
leButtonWidget* mainMenuScreen_menuDigitalBut;
leButtonWidget* mainMenuScreen_menuInpLevMatchBut;
leButtonWidget* mainMenuScreen_menuNameInpBut;
leButtonWidget* mainMenuScreen_menuAvInpBut;
leButtonWidget* mainMenuScreen_menuRestSetBut;
leButtonWidget* mainMenuScreen_menuRiaaBut;
leButtonWidget* mainMenuScreen_menuBiasBut;
leLabelWidget* mainMenuScreen_mainMenuHeader;
leRectangleWidget* mainMenuScreen_menuLineRightSide;
leRectangleWidget* mainMenuScreen_menuLineLeftSide;
leImageWidget* mainMenuScreen_ImageWidget_0;
leTextFieldWidget* mainMenuScreen_TextFieldWidget_0;
leTextFieldWidget* mainMenuScreen_TextFieldWidget_1;
leTextFieldWidget* mainMenuScreen_TextFieldWidget_2;
leRectangleWidget* mainMenuScreen_RectangleWidget_0;
leButtonWidget* mainMenuScreen_cancelButton;

static leBool initialized = LE_FALSE;
static leBool showing = LE_FALSE;

leResult screenInit_mainMenuScreen(void)
{
    if(initialized == LE_TRUE)
        return LE_FAILURE;

    initialized = LE_TRUE;

    return LE_SUCCESS;
}

leResult screenShow_mainMenuScreen(void)
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

    mainMenuScreen_BackgroundPanel = leWidget_New();
    mainMenuScreen_BackgroundPanel->fn->setPosition(mainMenuScreen_BackgroundPanel, 0, 0);
    mainMenuScreen_BackgroundPanel->fn->setSize(mainMenuScreen_BackgroundPanel, 480, 272);
    mainMenuScreen_BackgroundPanel->fn->setScheme(mainMenuScreen_BackgroundPanel, &BlackScheme);
    root0->fn->addChild(root0, (leWidget*)mainMenuScreen_BackgroundPanel);

    mainMenuScreen_menuExitBut = leButtonWidget_New();
    mainMenuScreen_menuExitBut->fn->setPosition(mainMenuScreen_menuExitBut, 360, 232);
    mainMenuScreen_menuExitBut->fn->setSize(mainMenuScreen_menuExitBut, 93, 27);
    mainMenuScreen_menuExitBut->fn->setAlphaEnabled(mainMenuScreen_menuExitBut, LE_TRUE);
    mainMenuScreen_menuExitBut->fn->setScheme(mainMenuScreen_menuExitBut, &BlackScheme);
    mainMenuScreen_menuExitBut->fn->setBackgroundType(mainMenuScreen_menuExitBut, LE_WIDGET_BACKGROUND_NONE);
    mainMenuScreen_menuExitBut->fn->setVAlignment(mainMenuScreen_menuExitBut, LE_VALIGN_TOP);
    mainMenuScreen_menuExitBut->fn->setMargins(mainMenuScreen_menuExitBut, 4, 1, 4, 5);
    mainMenuScreen_menuExitBut->fn->setString(mainMenuScreen_menuExitBut, (leString*)&string_menuExitStr);
    mainMenuScreen_menuExitBut->fn->setPressedEventCallback(mainMenuScreen_menuExitBut, event_mainMenuScreen_menuExitBut_OnPressed);
    mainMenuScreen_BackgroundPanel->fn->addChild(mainMenuScreen_BackgroundPanel, (leWidget*)mainMenuScreen_menuExitBut);

    mainMenuScreen_menuVolBut = leButtonWidget_New();
    mainMenuScreen_menuVolBut->fn->setPosition(mainMenuScreen_menuVolBut, 22, 40);
    mainMenuScreen_menuVolBut->fn->setSize(mainMenuScreen_menuVolBut, 180, 25);
    mainMenuScreen_menuVolBut->fn->setScheme(mainMenuScreen_menuVolBut, &BlackScheme);
    mainMenuScreen_menuVolBut->fn->setBorderType(mainMenuScreen_menuVolBut, LE_WIDGET_BORDER_NONE);
    mainMenuScreen_menuVolBut->fn->setHAlignment(mainMenuScreen_menuVolBut, LE_HALIGN_LEFT);
    mainMenuScreen_menuVolBut->fn->setVAlignment(mainMenuScreen_menuVolBut, LE_VALIGN_TOP);
    mainMenuScreen_menuVolBut->fn->setString(mainMenuScreen_menuVolBut, (leString*)&string_menuVolStr);
    mainMenuScreen_menuVolBut->fn->setPressedEventCallback(mainMenuScreen_menuVolBut, event_mainMenuScreen_menuVolBut_OnPressed);
    mainMenuScreen_BackgroundPanel->fn->addChild(mainMenuScreen_BackgroundPanel, (leWidget*)mainMenuScreen_menuVolBut);

    mainMenuScreen_menuDisplayBut = leButtonWidget_New();
    mainMenuScreen_menuDisplayBut->fn->setPosition(mainMenuScreen_menuDisplayBut, 280, 40);
    mainMenuScreen_menuDisplayBut->fn->setSize(mainMenuScreen_menuDisplayBut, 175, 25);
    mainMenuScreen_menuDisplayBut->fn->setScheme(mainMenuScreen_menuDisplayBut, &BlackScheme);
    mainMenuScreen_menuDisplayBut->fn->setBorderType(mainMenuScreen_menuDisplayBut, LE_WIDGET_BORDER_NONE);
    mainMenuScreen_menuDisplayBut->fn->setHAlignment(mainMenuScreen_menuDisplayBut, LE_HALIGN_RIGHT);
    mainMenuScreen_menuDisplayBut->fn->setVAlignment(mainMenuScreen_menuDisplayBut, LE_VALIGN_TOP);
    mainMenuScreen_menuDisplayBut->fn->setString(mainMenuScreen_menuDisplayBut, (leString*)&string_menuDisplayStr);
    mainMenuScreen_menuDisplayBut->fn->setPressedEventCallback(mainMenuScreen_menuDisplayBut, event_mainMenuScreen_menuDisplayBut_OnPressed);
    mainMenuScreen_BackgroundPanel->fn->addChild(mainMenuScreen_BackgroundPanel, (leWidget*)mainMenuScreen_menuDisplayBut);

    mainMenuScreen_menuIrSrcBut = leButtonWidget_New();
    mainMenuScreen_menuIrSrcBut->fn->setPosition(mainMenuScreen_menuIrSrcBut, 280, 75);
    mainMenuScreen_menuIrSrcBut->fn->setSize(mainMenuScreen_menuIrSrcBut, 176, 25);
    mainMenuScreen_menuIrSrcBut->fn->setScheme(mainMenuScreen_menuIrSrcBut, &BlackScheme);
    mainMenuScreen_menuIrSrcBut->fn->setBorderType(mainMenuScreen_menuIrSrcBut, LE_WIDGET_BORDER_NONE);
    mainMenuScreen_menuIrSrcBut->fn->setHAlignment(mainMenuScreen_menuIrSrcBut, LE_HALIGN_RIGHT);
    mainMenuScreen_menuIrSrcBut->fn->setVAlignment(mainMenuScreen_menuIrSrcBut, LE_VALIGN_TOP);
    mainMenuScreen_menuIrSrcBut->fn->setString(mainMenuScreen_menuIrSrcBut, (leString*)&string_menuIrSourceStr);
    mainMenuScreen_menuIrSrcBut->fn->setPressedEventCallback(mainMenuScreen_menuIrSrcBut, event_mainMenuScreen_menuIrSrcBut_OnPressed);
    mainMenuScreen_BackgroundPanel->fn->addChild(mainMenuScreen_BackgroundPanel, (leWidget*)mainMenuScreen_menuIrSrcBut);

    mainMenuScreen_menuDigitalBut = leButtonWidget_New();
    mainMenuScreen_menuDigitalBut->fn->setPosition(mainMenuScreen_menuDigitalBut, 281, 110);
    mainMenuScreen_menuDigitalBut->fn->setSize(mainMenuScreen_menuDigitalBut, 175, 25);
    mainMenuScreen_menuDigitalBut->fn->setScheme(mainMenuScreen_menuDigitalBut, &BlackScheme);
    mainMenuScreen_menuDigitalBut->fn->setBorderType(mainMenuScreen_menuDigitalBut, LE_WIDGET_BORDER_NONE);
    mainMenuScreen_menuDigitalBut->fn->setHAlignment(mainMenuScreen_menuDigitalBut, LE_HALIGN_RIGHT);
    mainMenuScreen_menuDigitalBut->fn->setVAlignment(mainMenuScreen_menuDigitalBut, LE_VALIGN_TOP);
    mainMenuScreen_menuDigitalBut->fn->setString(mainMenuScreen_menuDigitalBut, (leString*)&string_menuDigitalStr);
    mainMenuScreen_menuDigitalBut->fn->setPressedEventCallback(mainMenuScreen_menuDigitalBut, event_mainMenuScreen_menuDigitalBut_OnPressed);
    mainMenuScreen_BackgroundPanel->fn->addChild(mainMenuScreen_BackgroundPanel, (leWidget*)mainMenuScreen_menuDigitalBut);

    mainMenuScreen_menuInpLevMatchBut = leButtonWidget_New();
    mainMenuScreen_menuInpLevMatchBut->fn->setPosition(mainMenuScreen_menuInpLevMatchBut, 22, 75);
    mainMenuScreen_menuInpLevMatchBut->fn->setSize(mainMenuScreen_menuInpLevMatchBut, 204, 25);
    mainMenuScreen_menuInpLevMatchBut->fn->setScheme(mainMenuScreen_menuInpLevMatchBut, &BlackScheme);
    mainMenuScreen_menuInpLevMatchBut->fn->setBorderType(mainMenuScreen_menuInpLevMatchBut, LE_WIDGET_BORDER_NONE);
    mainMenuScreen_menuInpLevMatchBut->fn->setHAlignment(mainMenuScreen_menuInpLevMatchBut, LE_HALIGN_LEFT);
    mainMenuScreen_menuInpLevMatchBut->fn->setVAlignment(mainMenuScreen_menuInpLevMatchBut, LE_VALIGN_TOP);
    mainMenuScreen_menuInpLevMatchBut->fn->setString(mainMenuScreen_menuInpLevMatchBut, (leString*)&string_menuInpLevMatchStr);
    mainMenuScreen_menuInpLevMatchBut->fn->setPressedEventCallback(mainMenuScreen_menuInpLevMatchBut, event_mainMenuScreen_menuInpLevMatchBut_OnPressed);
    mainMenuScreen_BackgroundPanel->fn->addChild(mainMenuScreen_BackgroundPanel, (leWidget*)mainMenuScreen_menuInpLevMatchBut);

    mainMenuScreen_menuNameInpBut = leButtonWidget_New();
    mainMenuScreen_menuNameInpBut->fn->setPosition(mainMenuScreen_menuNameInpBut, 22, 180);
    mainMenuScreen_menuNameInpBut->fn->setSize(mainMenuScreen_menuNameInpBut, 176, 25);
    mainMenuScreen_menuNameInpBut->fn->setScheme(mainMenuScreen_menuNameInpBut, &BlackScheme);
    mainMenuScreen_menuNameInpBut->fn->setBorderType(mainMenuScreen_menuNameInpBut, LE_WIDGET_BORDER_NONE);
    mainMenuScreen_menuNameInpBut->fn->setHAlignment(mainMenuScreen_menuNameInpBut, LE_HALIGN_LEFT);
    mainMenuScreen_menuNameInpBut->fn->setVAlignment(mainMenuScreen_menuNameInpBut, LE_VALIGN_TOP);
    mainMenuScreen_menuNameInpBut->fn->setString(mainMenuScreen_menuNameInpBut, (leString*)&string_menuNameInputStr);
    mainMenuScreen_menuNameInpBut->fn->setPressedEventCallback(mainMenuScreen_menuNameInpBut, event_mainMenuScreen_menuNameInpBut_OnPressed);
    mainMenuScreen_BackgroundPanel->fn->addChild(mainMenuScreen_BackgroundPanel, (leWidget*)mainMenuScreen_menuNameInpBut);

    mainMenuScreen_menuAvInpBut = leButtonWidget_New();
    mainMenuScreen_menuAvInpBut->fn->setPosition(mainMenuScreen_menuAvInpBut, 22, 145);
    mainMenuScreen_menuAvInpBut->fn->setSize(mainMenuScreen_menuAvInpBut, 170, 25);
    mainMenuScreen_menuAvInpBut->fn->setScheme(mainMenuScreen_menuAvInpBut, &BlackScheme);
    mainMenuScreen_menuAvInpBut->fn->setBorderType(mainMenuScreen_menuAvInpBut, LE_WIDGET_BORDER_NONE);
    mainMenuScreen_menuAvInpBut->fn->setHAlignment(mainMenuScreen_menuAvInpBut, LE_HALIGN_LEFT);
    mainMenuScreen_menuAvInpBut->fn->setVAlignment(mainMenuScreen_menuAvInpBut, LE_VALIGN_TOP);
    mainMenuScreen_menuAvInpBut->fn->setString(mainMenuScreen_menuAvInpBut, (leString*)&string_menuAvInputStr);
    mainMenuScreen_menuAvInpBut->fn->setPressedEventCallback(mainMenuScreen_menuAvInpBut, event_mainMenuScreen_menuAvInpBut_OnPressed);
    mainMenuScreen_BackgroundPanel->fn->addChild(mainMenuScreen_BackgroundPanel, (leWidget*)mainMenuScreen_menuAvInpBut);

    mainMenuScreen_menuRestSetBut = leButtonWidget_New();
    mainMenuScreen_menuRestSetBut->fn->setPosition(mainMenuScreen_menuRestSetBut, 267, 180);
    mainMenuScreen_menuRestSetBut->fn->setSize(mainMenuScreen_menuRestSetBut, 189, 25);
    mainMenuScreen_menuRestSetBut->fn->setScheme(mainMenuScreen_menuRestSetBut, &BlackScheme);
    mainMenuScreen_menuRestSetBut->fn->setBorderType(mainMenuScreen_menuRestSetBut, LE_WIDGET_BORDER_NONE);
    mainMenuScreen_menuRestSetBut->fn->setHAlignment(mainMenuScreen_menuRestSetBut, LE_HALIGN_RIGHT);
    mainMenuScreen_menuRestSetBut->fn->setVAlignment(mainMenuScreen_menuRestSetBut, LE_VALIGN_TOP);
    mainMenuScreen_menuRestSetBut->fn->setString(mainMenuScreen_menuRestSetBut, (leString*)&string_menuRestoreSettingStr);
    mainMenuScreen_menuRestSetBut->fn->setPressedEventCallback(mainMenuScreen_menuRestSetBut, event_mainMenuScreen_menuRestSetBut_OnPressed);
    mainMenuScreen_BackgroundPanel->fn->addChild(mainMenuScreen_BackgroundPanel, (leWidget*)mainMenuScreen_menuRestSetBut);

    mainMenuScreen_menuRiaaBut = leButtonWidget_New();
    mainMenuScreen_menuRiaaBut->fn->setPosition(mainMenuScreen_menuRiaaBut, 289, 145);
    mainMenuScreen_menuRiaaBut->fn->setSize(mainMenuScreen_menuRiaaBut, 167, 25);
    mainMenuScreen_menuRiaaBut->fn->setScheme(mainMenuScreen_menuRiaaBut, &BlackScheme);
    mainMenuScreen_menuRiaaBut->fn->setBorderType(mainMenuScreen_menuRiaaBut, LE_WIDGET_BORDER_NONE);
    mainMenuScreen_menuRiaaBut->fn->setHAlignment(mainMenuScreen_menuRiaaBut, LE_HALIGN_RIGHT);
    mainMenuScreen_menuRiaaBut->fn->setVAlignment(mainMenuScreen_menuRiaaBut, LE_VALIGN_TOP);
    mainMenuScreen_menuRiaaBut->fn->setString(mainMenuScreen_menuRiaaBut, (leString*)&string_menuRiaaStr);
    mainMenuScreen_menuRiaaBut->fn->setPressedEventCallback(mainMenuScreen_menuRiaaBut, event_mainMenuScreen_menuRiaaBut_OnPressed);
    mainMenuScreen_BackgroundPanel->fn->addChild(mainMenuScreen_BackgroundPanel, (leWidget*)mainMenuScreen_menuRiaaBut);

    mainMenuScreen_menuBiasBut = leButtonWidget_New();
    mainMenuScreen_menuBiasBut->fn->setPosition(mainMenuScreen_menuBiasBut, 22, 110);
    mainMenuScreen_menuBiasBut->fn->setSize(mainMenuScreen_menuBiasBut, 190, 25);
    mainMenuScreen_menuBiasBut->fn->setScheme(mainMenuScreen_menuBiasBut, &BlackScheme);
    mainMenuScreen_menuBiasBut->fn->setBackgroundType(mainMenuScreen_menuBiasBut, LE_WIDGET_BACKGROUND_NONE);
    mainMenuScreen_menuBiasBut->fn->setBorderType(mainMenuScreen_menuBiasBut, LE_WIDGET_BORDER_NONE);
    mainMenuScreen_menuBiasBut->fn->setHAlignment(mainMenuScreen_menuBiasBut, LE_HALIGN_LEFT);
    mainMenuScreen_menuBiasBut->fn->setVAlignment(mainMenuScreen_menuBiasBut, LE_VALIGN_TOP);
    mainMenuScreen_menuBiasBut->fn->setString(mainMenuScreen_menuBiasBut, (leString*)&string_menuGreenBiasStr);
    mainMenuScreen_menuBiasBut->fn->setPressedEventCallback(mainMenuScreen_menuBiasBut, event_mainMenuScreen_menuBiasBut_OnPressed);
    mainMenuScreen_BackgroundPanel->fn->addChild(mainMenuScreen_BackgroundPanel, (leWidget*)mainMenuScreen_menuBiasBut);

    mainMenuScreen_mainMenuHeader = leLabelWidget_New();
    mainMenuScreen_mainMenuHeader->fn->setPosition(mainMenuScreen_mainMenuHeader, 0, 12);
    mainMenuScreen_mainMenuHeader->fn->setSize(mainMenuScreen_mainMenuHeader, 480, 25);
    mainMenuScreen_mainMenuHeader->fn->setScheme(mainMenuScreen_mainMenuHeader, &BlackScheme);
    mainMenuScreen_mainMenuHeader->fn->setBackgroundType(mainMenuScreen_mainMenuHeader, LE_WIDGET_BACKGROUND_NONE);
    mainMenuScreen_mainMenuHeader->fn->setHAlignment(mainMenuScreen_mainMenuHeader, LE_HALIGN_CENTER);
    mainMenuScreen_mainMenuHeader->fn->setString(mainMenuScreen_mainMenuHeader, (leString*)&string_menuHeaderStr);
    mainMenuScreen_BackgroundPanel->fn->addChild(mainMenuScreen_BackgroundPanel, (leWidget*)mainMenuScreen_mainMenuHeader);

    mainMenuScreen_menuLineRightSide = leRectangleWidget_New();
    mainMenuScreen_menuLineRightSide->fn->setPosition(mainMenuScreen_menuLineRightSide, 279, 25);
    mainMenuScreen_menuLineRightSide->fn->setSize(mainMenuScreen_menuLineRightSide, 175, 3);
    mainMenuScreen_menuLineRightSide->fn->setScheme(mainMenuScreen_menuLineRightSide, &WhiteScheme);
    mainMenuScreen_menuLineRightSide->fn->setBorderType(mainMenuScreen_menuLineRightSide, LE_WIDGET_BORDER_NONE);
    mainMenuScreen_BackgroundPanel->fn->addChild(mainMenuScreen_BackgroundPanel, (leWidget*)mainMenuScreen_menuLineRightSide);

    mainMenuScreen_menuLineLeftSide = leRectangleWidget_New();
    mainMenuScreen_menuLineLeftSide->fn->setPosition(mainMenuScreen_menuLineLeftSide, 26, 25);
    mainMenuScreen_menuLineLeftSide->fn->setSize(mainMenuScreen_menuLineLeftSide, 175, 3);
    mainMenuScreen_menuLineLeftSide->fn->setScheme(mainMenuScreen_menuLineLeftSide, &WhiteScheme);
    mainMenuScreen_menuLineLeftSide->fn->setBorderType(mainMenuScreen_menuLineLeftSide, LE_WIDGET_BORDER_NONE);
    mainMenuScreen_BackgroundPanel->fn->addChild(mainMenuScreen_BackgroundPanel, (leWidget*)mainMenuScreen_menuLineLeftSide);

    mainMenuScreen_fanErrorPanel = leWidget_New();
    mainMenuScreen_fanErrorPanel->fn->setPosition(mainMenuScreen_fanErrorPanel, 107, 45);
    mainMenuScreen_fanErrorPanel->fn->setSize(mainMenuScreen_fanErrorPanel, 268, 199);
    mainMenuScreen_fanErrorPanel->fn->setVisible(mainMenuScreen_fanErrorPanel, LE_FALSE);
    mainMenuScreen_fanErrorPanel->fn->setScheme(mainMenuScreen_fanErrorPanel, &BlackScheme);
    root0->fn->addChild(root0, (leWidget*)mainMenuScreen_fanErrorPanel);

    mainMenuScreen_ImageWidget_0 = leImageWidget_New();
    mainMenuScreen_ImageWidget_0->fn->setPosition(mainMenuScreen_ImageWidget_0, 106, 5);
    mainMenuScreen_ImageWidget_0->fn->setSize(mainMenuScreen_ImageWidget_0, 55, 70);
    mainMenuScreen_ImageWidget_0->fn->setScheme(mainMenuScreen_ImageWidget_0, &BlackScheme);
    mainMenuScreen_ImageWidget_0->fn->setBorderType(mainMenuScreen_ImageWidget_0, LE_WIDGET_BORDER_NONE);
    mainMenuScreen_ImageWidget_0->fn->setImage(mainMenuScreen_ImageWidget_0, (leImage*)&fanError);
    mainMenuScreen_fanErrorPanel->fn->addChild(mainMenuScreen_fanErrorPanel, (leWidget*)mainMenuScreen_ImageWidget_0);

    mainMenuScreen_TextFieldWidget_0 = leTextFieldWidget_New();
    mainMenuScreen_TextFieldWidget_0->fn->setPosition(mainMenuScreen_TextFieldWidget_0, 82, 78);
    mainMenuScreen_TextFieldWidget_0->fn->setScheme(mainMenuScreen_TextFieldWidget_0, &BlackScheme);
    mainMenuScreen_TextFieldWidget_0->fn->setBackgroundType(mainMenuScreen_TextFieldWidget_0, LE_WIDGET_BACKGROUND_NONE);
    mainMenuScreen_TextFieldWidget_0->fn->setBorderType(mainMenuScreen_TextFieldWidget_0, LE_WIDGET_BORDER_NONE);
    mainMenuScreen_TextFieldWidget_0->fn->setHAlignment(mainMenuScreen_TextFieldWidget_0, LE_HALIGN_LEFT);
    mainMenuScreen_TextFieldWidget_0->fn->setString(mainMenuScreen_TextFieldWidget_0, (leString*)&string_fanErrStr1);
    mainMenuScreen_TextFieldWidget_0->fn->setFont(mainMenuScreen_TextFieldWidget_0, (leFont*)&Avenir16);
    mainMenuScreen_fanErrorPanel->fn->addChild(mainMenuScreen_fanErrorPanel, (leWidget*)mainMenuScreen_TextFieldWidget_0);

    mainMenuScreen_TextFieldWidget_1 = leTextFieldWidget_New();
    mainMenuScreen_TextFieldWidget_1->fn->setPosition(mainMenuScreen_TextFieldWidget_1, 36, 106);
    mainMenuScreen_TextFieldWidget_1->fn->setSize(mainMenuScreen_TextFieldWidget_1, 200, 25);
    mainMenuScreen_TextFieldWidget_1->fn->setScheme(mainMenuScreen_TextFieldWidget_1, &BlackScheme);
    mainMenuScreen_TextFieldWidget_1->fn->setBackgroundType(mainMenuScreen_TextFieldWidget_1, LE_WIDGET_BACKGROUND_NONE);
    mainMenuScreen_TextFieldWidget_1->fn->setBorderType(mainMenuScreen_TextFieldWidget_1, LE_WIDGET_BORDER_NONE);
    mainMenuScreen_TextFieldWidget_1->fn->setHAlignment(mainMenuScreen_TextFieldWidget_1, LE_HALIGN_LEFT);
    mainMenuScreen_TextFieldWidget_1->fn->setString(mainMenuScreen_TextFieldWidget_1, (leString*)&string_fanErrStr2);
    mainMenuScreen_TextFieldWidget_1->fn->setFont(mainMenuScreen_TextFieldWidget_1, (leFont*)&Avenir16);
    mainMenuScreen_fanErrorPanel->fn->addChild(mainMenuScreen_fanErrorPanel, (leWidget*)mainMenuScreen_TextFieldWidget_1);

    mainMenuScreen_TextFieldWidget_2 = leTextFieldWidget_New();
    mainMenuScreen_TextFieldWidget_2->fn->setPosition(mainMenuScreen_TextFieldWidget_2, 30, 135);
    mainMenuScreen_TextFieldWidget_2->fn->setSize(mainMenuScreen_TextFieldWidget_2, 200, 25);
    mainMenuScreen_TextFieldWidget_2->fn->setScheme(mainMenuScreen_TextFieldWidget_2, &BlackScheme);
    mainMenuScreen_TextFieldWidget_2->fn->setBackgroundType(mainMenuScreen_TextFieldWidget_2, LE_WIDGET_BACKGROUND_NONE);
    mainMenuScreen_TextFieldWidget_2->fn->setBorderType(mainMenuScreen_TextFieldWidget_2, LE_WIDGET_BORDER_NONE);
    mainMenuScreen_TextFieldWidget_2->fn->setHAlignment(mainMenuScreen_TextFieldWidget_2, LE_HALIGN_LEFT);
    mainMenuScreen_TextFieldWidget_2->fn->setString(mainMenuScreen_TextFieldWidget_2, (leString*)&string_fanErrStr3);
    mainMenuScreen_TextFieldWidget_2->fn->setFont(mainMenuScreen_TextFieldWidget_2, (leFont*)&Avenir16);
    mainMenuScreen_fanErrorPanel->fn->addChild(mainMenuScreen_fanErrorPanel, (leWidget*)mainMenuScreen_TextFieldWidget_2);

    mainMenuScreen_RectangleWidget_0 = leRectangleWidget_New();
    mainMenuScreen_RectangleWidget_0->fn->setPosition(mainMenuScreen_RectangleWidget_0, 1, 1);
    mainMenuScreen_RectangleWidget_0->fn->setSize(mainMenuScreen_RectangleWidget_0, 266, 195);
    mainMenuScreen_RectangleWidget_0->fn->setScheme(mainMenuScreen_RectangleWidget_0, &WhiteScheme);
    mainMenuScreen_RectangleWidget_0->fn->setBackgroundType(mainMenuScreen_RectangleWidget_0, LE_WIDGET_BACKGROUND_NONE);
    mainMenuScreen_RectangleWidget_0->fn->setBorderType(mainMenuScreen_RectangleWidget_0, LE_WIDGET_BORDER_NONE);
    mainMenuScreen_RectangleWidget_0->fn->setThickness(mainMenuScreen_RectangleWidget_0, 2);
    mainMenuScreen_fanErrorPanel->fn->addChild(mainMenuScreen_fanErrorPanel, (leWidget*)mainMenuScreen_RectangleWidget_0);

    mainMenuScreen_cancelButton = leButtonWidget_New();
    mainMenuScreen_cancelButton->fn->setPosition(mainMenuScreen_cancelButton, 85, 165);
    mainMenuScreen_cancelButton->fn->setScheme(mainMenuScreen_cancelButton, &BlackScheme);
    mainMenuScreen_cancelButton->fn->setBackgroundType(mainMenuScreen_cancelButton, LE_WIDGET_BACKGROUND_NONE);
    mainMenuScreen_cancelButton->fn->setString(mainMenuScreen_cancelButton, (leString*)&string_cancelStr);
    mainMenuScreen_cancelButton->fn->setPressedEventCallback(mainMenuScreen_cancelButton, event_mainMenuScreen_cancelButton_OnPressed);
    mainMenuScreen_fanErrorPanel->fn->addChild(mainMenuScreen_fanErrorPanel, (leWidget*)mainMenuScreen_cancelButton);

    leAddRootWidget(root0, 0);
    leSetLayerColorMode(0, LE_COLOR_MODE_RGB_565);

    mainMenuScreen_OnShow(); // raise event

    showing = LE_TRUE;

    return LE_SUCCESS;
}

void screenUpdate_mainMenuScreen(void)
{
    root0->fn->setSize(root0, root0->rect.width, root0->rect.height);
}

void screenHide_mainMenuScreen(void)
{
    mainMenuScreen_OnHide(); // raise event


    leRemoveRootWidget(root0, 0);
    leWidget_Delete(root0);
    root0 = NULL;

    mainMenuScreen_BackgroundPanel = NULL;
    mainMenuScreen_fanErrorPanel = NULL;
    mainMenuScreen_menuExitBut = NULL;
    mainMenuScreen_menuVolBut = NULL;
    mainMenuScreen_menuDisplayBut = NULL;
    mainMenuScreen_menuIrSrcBut = NULL;
    mainMenuScreen_menuDigitalBut = NULL;
    mainMenuScreen_menuInpLevMatchBut = NULL;
    mainMenuScreen_menuNameInpBut = NULL;
    mainMenuScreen_menuAvInpBut = NULL;
    mainMenuScreen_menuRestSetBut = NULL;
    mainMenuScreen_menuRiaaBut = NULL;
    mainMenuScreen_menuBiasBut = NULL;
    mainMenuScreen_mainMenuHeader = NULL;
    mainMenuScreen_menuLineRightSide = NULL;
    mainMenuScreen_menuLineLeftSide = NULL;
    mainMenuScreen_ImageWidget_0 = NULL;
    mainMenuScreen_TextFieldWidget_0 = NULL;
    mainMenuScreen_TextFieldWidget_1 = NULL;
    mainMenuScreen_TextFieldWidget_2 = NULL;
    mainMenuScreen_RectangleWidget_0 = NULL;
    mainMenuScreen_cancelButton = NULL;


    showing = LE_FALSE;
}

void screenDestroy_mainMenuScreen(void)
{
    if(initialized == LE_FALSE)
        return;

    initialized = LE_FALSE;
}

leWidget* screenGetRoot_mainMenuScreen(uint32_t lyrIdx)
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

