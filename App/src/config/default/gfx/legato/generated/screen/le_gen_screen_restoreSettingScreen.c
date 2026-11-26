#include "gfx/legato/generated/screen/le_gen_screen_restoreSettingScreen.h"

// screen member widget declarations
static leWidget* root0;

leWidget* restoreSettingScreen_PanelWidget0;
leRectangleWidget* restoreSettingScreen_RectangleWidget0;
leRectangleWidget* restoreSettingScreen_RectangleWidget1;
leLabelWidget* restoreSettingScreen_LabelWidget0;
leLabelWidget* restoreSettingScreen_LabelWidget1;
leLabelWidget* restoreSettingScreen_LabelWidget2;
leLabelWidget* restoreSettingScreen_LabelWidget3;
leLabelWidget* restoreSettingScreen_LabelWidget4;
leLabelWidget* restoreSettingScreen_LabelWidget5;
leButtonWidget* restoreSettingScreen_ResContiniueYesButton;
leButtonWidget* restoreSettingScreen_ResContiniueNoButton;
leWidget* restoreSettingScreen_splashResSetSure;
leWidget* restoreSettingScreen_settingsRestoredPanel;
leLabelWidget* restoreSettingScreen_fwLabel;
leRectangleWidget* restoreSettingScreen_RectangleWidget2;
leButtonWidget* restoreSettingScreen_yesButton;
leButtonWidget* restoreSettingScreen_cancelButton;
leLabelWidget* restoreSettingScreen_LabelWidget6;
leLabelWidget* restoreSettingScreen_LabelWidget7;
leRectangleWidget* restoreSettingScreen_RectangleWidget3;
leLabelWidget* restoreSettingScreen_LabelWidget8;
leLabelWidget* restoreSettingScreen_LabelWidget9;
leButtonWidget* restoreSettingScreen_backAfterRestoreBut;

static leBool initialized = LE_FALSE;
static leBool showing = LE_FALSE;

leResult screenInit_restoreSettingScreen(void)
{
    if(initialized == LE_TRUE)
        return LE_FAILURE;

    initialized = LE_TRUE;

    return LE_SUCCESS;
}

leResult screenShow_restoreSettingScreen(void)
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

    restoreSettingScreen_PanelWidget0 = leWidget_New();
    restoreSettingScreen_PanelWidget0->fn->setPosition(restoreSettingScreen_PanelWidget0, 0, 0);
    restoreSettingScreen_PanelWidget0->fn->setSize(restoreSettingScreen_PanelWidget0, 480, 272);
    restoreSettingScreen_PanelWidget0->fn->setScheme(restoreSettingScreen_PanelWidget0, &BlackScheme);
    root0->fn->addChild(root0, (leWidget*)restoreSettingScreen_PanelWidget0);

    restoreSettingScreen_RectangleWidget0 = leRectangleWidget_New();
    restoreSettingScreen_RectangleWidget0->fn->setPosition(restoreSettingScreen_RectangleWidget0, 339, 25);
    restoreSettingScreen_RectangleWidget0->fn->setSize(restoreSettingScreen_RectangleWidget0, 115, 3);
    restoreSettingScreen_RectangleWidget0->fn->setScheme(restoreSettingScreen_RectangleWidget0, &WhiteScheme);
    restoreSettingScreen_RectangleWidget0->fn->setBorderType(restoreSettingScreen_RectangleWidget0, LE_WIDGET_BORDER_NONE);
    restoreSettingScreen_RectangleWidget0->fn->setThickness(restoreSettingScreen_RectangleWidget0, 2);
    root0->fn->addChild(root0, (leWidget*)restoreSettingScreen_RectangleWidget0);

    restoreSettingScreen_RectangleWidget1 = leRectangleWidget_New();
    restoreSettingScreen_RectangleWidget1->fn->setPosition(restoreSettingScreen_RectangleWidget1, 26, 25);
    restoreSettingScreen_RectangleWidget1->fn->setSize(restoreSettingScreen_RectangleWidget1, 115, 3);
    restoreSettingScreen_RectangleWidget1->fn->setScheme(restoreSettingScreen_RectangleWidget1, &WhiteScheme);
    restoreSettingScreen_RectangleWidget1->fn->setBorderType(restoreSettingScreen_RectangleWidget1, LE_WIDGET_BORDER_NONE);
    restoreSettingScreen_RectangleWidget1->fn->setThickness(restoreSettingScreen_RectangleWidget1, 2);
    root0->fn->addChild(root0, (leWidget*)restoreSettingScreen_RectangleWidget1);

    restoreSettingScreen_LabelWidget0 = leLabelWidget_New();
    restoreSettingScreen_LabelWidget0->fn->setPosition(restoreSettingScreen_LabelWidget0, 0, 12);
    restoreSettingScreen_LabelWidget0->fn->setSize(restoreSettingScreen_LabelWidget0, 480, 25);
    restoreSettingScreen_LabelWidget0->fn->setScheme(restoreSettingScreen_LabelWidget0, &BlackScheme);
    restoreSettingScreen_LabelWidget0->fn->setBackgroundType(restoreSettingScreen_LabelWidget0, LE_WIDGET_BACKGROUND_NONE);
    restoreSettingScreen_LabelWidget0->fn->setHAlignment(restoreSettingScreen_LabelWidget0, LE_HALIGN_CENTER);
    restoreSettingScreen_LabelWidget0->fn->setString(restoreSettingScreen_LabelWidget0, (leString*)&string_menuRestoreSettingStr);
    root0->fn->addChild(root0, (leWidget*)restoreSettingScreen_LabelWidget0);

    restoreSettingScreen_LabelWidget1 = leLabelWidget_New();
    restoreSettingScreen_LabelWidget1->fn->setPosition(restoreSettingScreen_LabelWidget1, 40, 57);
    restoreSettingScreen_LabelWidget1->fn->setSize(restoreSettingScreen_LabelWidget1, 400, 25);
    restoreSettingScreen_LabelWidget1->fn->setScheme(restoreSettingScreen_LabelWidget1, &BlackScheme);
    restoreSettingScreen_LabelWidget1->fn->setHAlignment(restoreSettingScreen_LabelWidget1, LE_HALIGN_CENTER);
    restoreSettingScreen_LabelWidget1->fn->setString(restoreSettingScreen_LabelWidget1, (leString*)&string_restoreSettingLine1);
    root0->fn->addChild(root0, (leWidget*)restoreSettingScreen_LabelWidget1);

    restoreSettingScreen_LabelWidget2 = leLabelWidget_New();
    restoreSettingScreen_LabelWidget2->fn->setPosition(restoreSettingScreen_LabelWidget2, 40, 84);
    restoreSettingScreen_LabelWidget2->fn->setSize(restoreSettingScreen_LabelWidget2, 400, 25);
    restoreSettingScreen_LabelWidget2->fn->setScheme(restoreSettingScreen_LabelWidget2, &BlackScheme);
    restoreSettingScreen_LabelWidget2->fn->setHAlignment(restoreSettingScreen_LabelWidget2, LE_HALIGN_CENTER);
    restoreSettingScreen_LabelWidget2->fn->setString(restoreSettingScreen_LabelWidget2, (leString*)&string_restoreSettingLine2);
    root0->fn->addChild(root0, (leWidget*)restoreSettingScreen_LabelWidget2);

    restoreSettingScreen_LabelWidget3 = leLabelWidget_New();
    restoreSettingScreen_LabelWidget3->fn->setPosition(restoreSettingScreen_LabelWidget3, 40, 111);
    restoreSettingScreen_LabelWidget3->fn->setSize(restoreSettingScreen_LabelWidget3, 400, 25);
    restoreSettingScreen_LabelWidget3->fn->setScheme(restoreSettingScreen_LabelWidget3, &BlackScheme);
    restoreSettingScreen_LabelWidget3->fn->setHAlignment(restoreSettingScreen_LabelWidget3, LE_HALIGN_CENTER);
    restoreSettingScreen_LabelWidget3->fn->setString(restoreSettingScreen_LabelWidget3, (leString*)&string_restoreSettingLine3);
    root0->fn->addChild(root0, (leWidget*)restoreSettingScreen_LabelWidget3);

    restoreSettingScreen_LabelWidget4 = leLabelWidget_New();
    restoreSettingScreen_LabelWidget4->fn->setPosition(restoreSettingScreen_LabelWidget4, 0, 172);
    restoreSettingScreen_LabelWidget4->fn->setSize(restoreSettingScreen_LabelWidget4, 480, 25);
    restoreSettingScreen_LabelWidget4->fn->setScheme(restoreSettingScreen_LabelWidget4, &BlackScheme);
    restoreSettingScreen_LabelWidget4->fn->setHAlignment(restoreSettingScreen_LabelWidget4, LE_HALIGN_CENTER);
    restoreSettingScreen_LabelWidget4->fn->setString(restoreSettingScreen_LabelWidget4, (leString*)&string_restoreSettingLine4);
    root0->fn->addChild(root0, (leWidget*)restoreSettingScreen_LabelWidget4);

    restoreSettingScreen_LabelWidget5 = leLabelWidget_New();
    restoreSettingScreen_LabelWidget5->fn->setPosition(restoreSettingScreen_LabelWidget5, 0, 198);
    restoreSettingScreen_LabelWidget5->fn->setSize(restoreSettingScreen_LabelWidget5, 480, 25);
    restoreSettingScreen_LabelWidget5->fn->setScheme(restoreSettingScreen_LabelWidget5, &BlackScheme);
    restoreSettingScreen_LabelWidget5->fn->setBackgroundType(restoreSettingScreen_LabelWidget5, LE_WIDGET_BACKGROUND_NONE);
    restoreSettingScreen_LabelWidget5->fn->setHAlignment(restoreSettingScreen_LabelWidget5, LE_HALIGN_CENTER);
    restoreSettingScreen_LabelWidget5->fn->setString(restoreSettingScreen_LabelWidget5, (leString*)&string_restoreSettingLine3);
    root0->fn->addChild(root0, (leWidget*)restoreSettingScreen_LabelWidget5);

    restoreSettingScreen_ResContiniueYesButton = leButtonWidget_New();
    restoreSettingScreen_ResContiniueYesButton->fn->setPosition(restoreSettingScreen_ResContiniueYesButton, 30, 205);
    restoreSettingScreen_ResContiniueYesButton->fn->setSize(restoreSettingScreen_ResContiniueYesButton, 100, 30);
    restoreSettingScreen_ResContiniueYesButton->fn->setScheme(restoreSettingScreen_ResContiniueYesButton, &BlackScheme);
    restoreSettingScreen_ResContiniueYesButton->fn->setBackgroundType(restoreSettingScreen_ResContiniueYesButton, LE_WIDGET_BACKGROUND_NONE);
    restoreSettingScreen_ResContiniueYesButton->fn->setBorderType(restoreSettingScreen_ResContiniueYesButton, LE_WIDGET_BORDER_NONE);
    restoreSettingScreen_ResContiniueYesButton->fn->setHAlignment(restoreSettingScreen_ResContiniueYesButton, LE_HALIGN_LEFT);
    restoreSettingScreen_ResContiniueYesButton->fn->setString(restoreSettingScreen_ResContiniueYesButton, (leString*)&string_yesString);
    restoreSettingScreen_ResContiniueYesButton->fn->setPressedImage(restoreSettingScreen_ResContiniueYesButton, (leImage*)&largeSelected);
    restoreSettingScreen_ResContiniueYesButton->fn->setReleasedImage(restoreSettingScreen_ResContiniueYesButton, (leImage*)&largeNotSelected);
    restoreSettingScreen_ResContiniueYesButton->fn->setImageMargin(restoreSettingScreen_ResContiniueYesButton, 5);
    restoreSettingScreen_ResContiniueYesButton->fn->setPressedEventCallback(restoreSettingScreen_ResContiniueYesButton, event_restoreSettingScreen_ResContiniueYesButton_OnPressed);
    root0->fn->addChild(root0, (leWidget*)restoreSettingScreen_ResContiniueYesButton);

    restoreSettingScreen_ResContiniueNoButton = leButtonWidget_New();
    restoreSettingScreen_ResContiniueNoButton->fn->setPosition(restoreSettingScreen_ResContiniueNoButton, 350, 205);
    restoreSettingScreen_ResContiniueNoButton->fn->setSize(restoreSettingScreen_ResContiniueNoButton, 100, 30);
    restoreSettingScreen_ResContiniueNoButton->fn->setScheme(restoreSettingScreen_ResContiniueNoButton, &BlackScheme);
    restoreSettingScreen_ResContiniueNoButton->fn->setBackgroundType(restoreSettingScreen_ResContiniueNoButton, LE_WIDGET_BACKGROUND_NONE);
    restoreSettingScreen_ResContiniueNoButton->fn->setBorderType(restoreSettingScreen_ResContiniueNoButton, LE_WIDGET_BORDER_NONE);
    restoreSettingScreen_ResContiniueNoButton->fn->setHAlignment(restoreSettingScreen_ResContiniueNoButton, LE_HALIGN_RIGHT);
    restoreSettingScreen_ResContiniueNoButton->fn->setString(restoreSettingScreen_ResContiniueNoButton, (leString*)&string_noString);
    restoreSettingScreen_ResContiniueNoButton->fn->setPressedImage(restoreSettingScreen_ResContiniueNoButton, (leImage*)&largeSelected);
    restoreSettingScreen_ResContiniueNoButton->fn->setReleasedImage(restoreSettingScreen_ResContiniueNoButton, (leImage*)&largeNotSelected);
    restoreSettingScreen_ResContiniueNoButton->fn->setImagePosition(restoreSettingScreen_ResContiniueNoButton, LE_RELATIVE_POSITION_RIGHTOF);
    restoreSettingScreen_ResContiniueNoButton->fn->setImageMargin(restoreSettingScreen_ResContiniueNoButton, 5);
    restoreSettingScreen_ResContiniueNoButton->fn->setPressedEventCallback(restoreSettingScreen_ResContiniueNoButton, event_restoreSettingScreen_ResContiniueNoButton_OnPressed);
    root0->fn->addChild(root0, (leWidget*)restoreSettingScreen_ResContiniueNoButton);

    restoreSettingScreen_splashResSetSure = leWidget_New();
    restoreSettingScreen_splashResSetSure->fn->setPosition(restoreSettingScreen_splashResSetSure, 102, 66);
    restoreSettingScreen_splashResSetSure->fn->setSize(restoreSettingScreen_splashResSetSure, 270, 131);
    restoreSettingScreen_splashResSetSure->fn->setEnabled(restoreSettingScreen_splashResSetSure, LE_FALSE);
    restoreSettingScreen_splashResSetSure->fn->setVisible(restoreSettingScreen_splashResSetSure, LE_FALSE);
    restoreSettingScreen_splashResSetSure->fn->setScheme(restoreSettingScreen_splashResSetSure, &BlackScheme);
    root0->fn->addChild(root0, (leWidget*)restoreSettingScreen_splashResSetSure);

    restoreSettingScreen_RectangleWidget2 = leRectangleWidget_New();
    restoreSettingScreen_RectangleWidget2->fn->setPosition(restoreSettingScreen_RectangleWidget2, 3, 2);
    restoreSettingScreen_RectangleWidget2->fn->setSize(restoreSettingScreen_RectangleWidget2, 263, 125);
    restoreSettingScreen_RectangleWidget2->fn->setScheme(restoreSettingScreen_RectangleWidget2, &WhiteScheme);
    restoreSettingScreen_RectangleWidget2->fn->setBackgroundType(restoreSettingScreen_RectangleWidget2, LE_WIDGET_BACKGROUND_NONE);
    restoreSettingScreen_RectangleWidget2->fn->setBorderType(restoreSettingScreen_RectangleWidget2, LE_WIDGET_BORDER_LINE);
    restoreSettingScreen_RectangleWidget2->fn->setThickness(restoreSettingScreen_RectangleWidget2, 2);
    restoreSettingScreen_splashResSetSure->fn->addChild(restoreSettingScreen_splashResSetSure, (leWidget*)restoreSettingScreen_RectangleWidget2);

    restoreSettingScreen_yesButton = leButtonWidget_New();
    restoreSettingScreen_yesButton->fn->setPosition(restoreSettingScreen_yesButton, 23, 83);
    restoreSettingScreen_yesButton->fn->setSize(restoreSettingScreen_yesButton, 54, 25);
    restoreSettingScreen_yesButton->fn->setScheme(restoreSettingScreen_yesButton, &BlackScheme);
    restoreSettingScreen_yesButton->fn->setBorderType(restoreSettingScreen_yesButton, LE_WIDGET_BORDER_NONE);
    restoreSettingScreen_yesButton->fn->setString(restoreSettingScreen_yesButton, (leString*)&string_yes16Str);
    restoreSettingScreen_yesButton->fn->setPressedImage(restoreSettingScreen_yesButton, (leImage*)&smallSelected2);
    restoreSettingScreen_yesButton->fn->setReleasedImage(restoreSettingScreen_yesButton, (leImage*)&smallNotSelected3);
    restoreSettingScreen_yesButton->fn->setImageMargin(restoreSettingScreen_yesButton, 5);
    restoreSettingScreen_yesButton->fn->setPressedEventCallback(restoreSettingScreen_yesButton, event_restoreSettingScreen_yesButton_OnPressed);
    restoreSettingScreen_splashResSetSure->fn->addChild(restoreSettingScreen_splashResSetSure, (leWidget*)restoreSettingScreen_yesButton);

    restoreSettingScreen_cancelButton = leButtonWidget_New();
    restoreSettingScreen_cancelButton->fn->setPosition(restoreSettingScreen_cancelButton, 152, 85);
    restoreSettingScreen_cancelButton->fn->setScheme(restoreSettingScreen_cancelButton, &BlackScheme);
    restoreSettingScreen_cancelButton->fn->setBackgroundType(restoreSettingScreen_cancelButton, LE_WIDGET_BACKGROUND_NONE);
    restoreSettingScreen_cancelButton->fn->setBorderType(restoreSettingScreen_cancelButton, LE_WIDGET_BORDER_NONE);
    restoreSettingScreen_cancelButton->fn->setString(restoreSettingScreen_cancelButton, (leString*)&string_cancelStr);
    restoreSettingScreen_cancelButton->fn->setPressedImage(restoreSettingScreen_cancelButton, (leImage*)&smallSelected2);
    restoreSettingScreen_cancelButton->fn->setReleasedImage(restoreSettingScreen_cancelButton, (leImage*)&smallNotSelected3);
    restoreSettingScreen_cancelButton->fn->setImagePosition(restoreSettingScreen_cancelButton, LE_RELATIVE_POSITION_RIGHTOF);
    restoreSettingScreen_cancelButton->fn->setImageMargin(restoreSettingScreen_cancelButton, 5);
    restoreSettingScreen_cancelButton->fn->setPressedEventCallback(restoreSettingScreen_cancelButton, event_restoreSettingScreen_cancelButton_OnPressed);
    restoreSettingScreen_splashResSetSure->fn->addChild(restoreSettingScreen_splashResSetSure, (leWidget*)restoreSettingScreen_cancelButton);

    restoreSettingScreen_LabelWidget6 = leLabelWidget_New();
    restoreSettingScreen_LabelWidget6->fn->setPosition(restoreSettingScreen_LabelWidget6, 42, 20);
    restoreSettingScreen_LabelWidget6->fn->setSize(restoreSettingScreen_LabelWidget6, 190, 25);
    restoreSettingScreen_LabelWidget6->fn->setScheme(restoreSettingScreen_LabelWidget6, &warningScheme);
    restoreSettingScreen_LabelWidget6->fn->setBackgroundType(restoreSettingScreen_LabelWidget6, LE_WIDGET_BACKGROUND_NONE);
    restoreSettingScreen_LabelWidget6->fn->setHAlignment(restoreSettingScreen_LabelWidget6, LE_HALIGN_CENTER);
    restoreSettingScreen_LabelWidget6->fn->setString(restoreSettingScreen_LabelWidget6, (leString*)&string_menuRestoreSettingStr);
    restoreSettingScreen_splashResSetSure->fn->addChild(restoreSettingScreen_splashResSetSure, (leWidget*)restoreSettingScreen_LabelWidget6);

    restoreSettingScreen_LabelWidget7 = leLabelWidget_New();
    restoreSettingScreen_LabelWidget7->fn->setPosition(restoreSettingScreen_LabelWidget7, 41, 50);
    restoreSettingScreen_LabelWidget7->fn->setSize(restoreSettingScreen_LabelWidget7, 200, 25);
    restoreSettingScreen_LabelWidget7->fn->setScheme(restoreSettingScreen_LabelWidget7, &warningScheme);
    restoreSettingScreen_LabelWidget7->fn->setHAlignment(restoreSettingScreen_LabelWidget7, LE_HALIGN_CENTER);
    restoreSettingScreen_LabelWidget7->fn->setString(restoreSettingScreen_LabelWidget7, (leString*)&string_areYouSureStr);
    restoreSettingScreen_splashResSetSure->fn->addChild(restoreSettingScreen_splashResSetSure, (leWidget*)restoreSettingScreen_LabelWidget7);

    restoreSettingScreen_settingsRestoredPanel = leWidget_New();
    restoreSettingScreen_settingsRestoredPanel->fn->setPosition(restoreSettingScreen_settingsRestoredPanel, 102, 66);
    restoreSettingScreen_settingsRestoredPanel->fn->setSize(restoreSettingScreen_settingsRestoredPanel, 270, 131);
    restoreSettingScreen_settingsRestoredPanel->fn->setEnabled(restoreSettingScreen_settingsRestoredPanel, LE_FALSE);
    restoreSettingScreen_settingsRestoredPanel->fn->setVisible(restoreSettingScreen_settingsRestoredPanel, LE_FALSE);
    restoreSettingScreen_settingsRestoredPanel->fn->setScheme(restoreSettingScreen_settingsRestoredPanel, &BlackScheme);
    root0->fn->addChild(root0, (leWidget*)restoreSettingScreen_settingsRestoredPanel);

    restoreSettingScreen_RectangleWidget3 = leRectangleWidget_New();
    restoreSettingScreen_RectangleWidget3->fn->setPosition(restoreSettingScreen_RectangleWidget3, 3, 2);
    restoreSettingScreen_RectangleWidget3->fn->setSize(restoreSettingScreen_RectangleWidget3, 263, 125);
    restoreSettingScreen_RectangleWidget3->fn->setScheme(restoreSettingScreen_RectangleWidget3, &WhiteScheme);
    restoreSettingScreen_RectangleWidget3->fn->setBackgroundType(restoreSettingScreen_RectangleWidget3, LE_WIDGET_BACKGROUND_NONE);
    restoreSettingScreen_RectangleWidget3->fn->setBorderType(restoreSettingScreen_RectangleWidget3, LE_WIDGET_BORDER_NONE);
    restoreSettingScreen_RectangleWidget3->fn->setThickness(restoreSettingScreen_RectangleWidget3, 2);
    restoreSettingScreen_settingsRestoredPanel->fn->addChild(restoreSettingScreen_settingsRestoredPanel, (leWidget*)restoreSettingScreen_RectangleWidget3);

    restoreSettingScreen_backAfterRestoreBut = leButtonWidget_New();
    restoreSettingScreen_backAfterRestoreBut->fn->setPosition(restoreSettingScreen_backAfterRestoreBut, 84, 75);
    restoreSettingScreen_backAfterRestoreBut->fn->setSize(restoreSettingScreen_backAfterRestoreBut, 102, 42);
    restoreSettingScreen_backAfterRestoreBut->fn->setScheme(restoreSettingScreen_backAfterRestoreBut, &BlackScheme);
    restoreSettingScreen_backAfterRestoreBut->fn->setVAlignment(restoreSettingScreen_backAfterRestoreBut, LE_VALIGN_TOP);
    restoreSettingScreen_backAfterRestoreBut->fn->setString(restoreSettingScreen_backAfterRestoreBut, (leString*)&string_OK_String);
    restoreSettingScreen_backAfterRestoreBut->fn->setPressedEventCallback(restoreSettingScreen_backAfterRestoreBut, event_restoreSettingScreen_backAfterRestoreBut_OnPressed);
    restoreSettingScreen_RectangleWidget3->fn->addChild(restoreSettingScreen_RectangleWidget3, (leWidget*)restoreSettingScreen_backAfterRestoreBut);

    restoreSettingScreen_LabelWidget8 = leLabelWidget_New();
    restoreSettingScreen_LabelWidget8->fn->setPosition(restoreSettingScreen_LabelWidget8, 35, 11);
    restoreSettingScreen_LabelWidget8->fn->setSize(restoreSettingScreen_LabelWidget8, 200, 25);
    restoreSettingScreen_LabelWidget8->fn->setScheme(restoreSettingScreen_LabelWidget8, &BlackScheme);
    restoreSettingScreen_LabelWidget8->fn->setHAlignment(restoreSettingScreen_LabelWidget8, LE_HALIGN_CENTER);
    restoreSettingScreen_LabelWidget8->fn->setString(restoreSettingScreen_LabelWidget8, (leString*)&string_settingsRestoredString);
    restoreSettingScreen_settingsRestoredPanel->fn->addChild(restoreSettingScreen_settingsRestoredPanel, (leWidget*)restoreSettingScreen_LabelWidget8);

    restoreSettingScreen_LabelWidget9 = leLabelWidget_New();
    restoreSettingScreen_LabelWidget9->fn->setPosition(restoreSettingScreen_LabelWidget9, 67, 36);
    restoreSettingScreen_LabelWidget9->fn->setSize(restoreSettingScreen_LabelWidget9, 136, 25);
    restoreSettingScreen_LabelWidget9->fn->setScheme(restoreSettingScreen_LabelWidget9, &BlackScheme);
    restoreSettingScreen_LabelWidget9->fn->setHAlignment(restoreSettingScreen_LabelWidget9, LE_HALIGN_CENTER);
    restoreSettingScreen_LabelWidget9->fn->setString(restoreSettingScreen_LabelWidget9, (leString*)&string_succesfullyString);
    restoreSettingScreen_settingsRestoredPanel->fn->addChild(restoreSettingScreen_settingsRestoredPanel, (leWidget*)restoreSettingScreen_LabelWidget9);

    restoreSettingScreen_fwLabel = leLabelWidget_New();
    restoreSettingScreen_fwLabel->fn->setPosition(restoreSettingScreen_fwLabel, 0, 236);
    restoreSettingScreen_fwLabel->fn->setSize(restoreSettingScreen_fwLabel, 480, 25);
    restoreSettingScreen_fwLabel->fn->setScheme(restoreSettingScreen_fwLabel, &BlackScheme);
    restoreSettingScreen_fwLabel->fn->setHAlignment(restoreSettingScreen_fwLabel, LE_HALIGN_CENTER);
    restoreSettingScreen_fwLabel->fn->setString(restoreSettingScreen_fwLabel, (leString*)&string_fwString);
    root0->fn->addChild(root0, (leWidget*)restoreSettingScreen_fwLabel);

    leAddRootWidget(root0, 0);
    leSetLayerColorMode(0, LE_COLOR_MODE_RGB_565);

    restoreSettingScreen_OnShow(); // raise event

    showing = LE_TRUE;

    return LE_SUCCESS;
}

void screenUpdate_restoreSettingScreen(void)
{
    root0->fn->setSize(root0, root0->rect.width, root0->rect.height);
}

void screenHide_restoreSettingScreen(void)
{

    leRemoveRootWidget(root0, 0);
    leWidget_Delete(root0);
    root0 = NULL;

    restoreSettingScreen_PanelWidget0 = NULL;
    restoreSettingScreen_RectangleWidget0 = NULL;
    restoreSettingScreen_RectangleWidget1 = NULL;
    restoreSettingScreen_LabelWidget0 = NULL;
    restoreSettingScreen_LabelWidget1 = NULL;
    restoreSettingScreen_LabelWidget2 = NULL;
    restoreSettingScreen_LabelWidget3 = NULL;
    restoreSettingScreen_LabelWidget4 = NULL;
    restoreSettingScreen_LabelWidget5 = NULL;
    restoreSettingScreen_ResContiniueYesButton = NULL;
    restoreSettingScreen_ResContiniueNoButton = NULL;
    restoreSettingScreen_splashResSetSure = NULL;
    restoreSettingScreen_settingsRestoredPanel = NULL;
    restoreSettingScreen_fwLabel = NULL;
    restoreSettingScreen_RectangleWidget2 = NULL;
    restoreSettingScreen_yesButton = NULL;
    restoreSettingScreen_cancelButton = NULL;
    restoreSettingScreen_LabelWidget6 = NULL;
    restoreSettingScreen_LabelWidget7 = NULL;
    restoreSettingScreen_RectangleWidget3 = NULL;
    restoreSettingScreen_LabelWidget8 = NULL;
    restoreSettingScreen_LabelWidget9 = NULL;
    restoreSettingScreen_backAfterRestoreBut = NULL;


    showing = LE_FALSE;
}

void screenDestroy_restoreSettingScreen(void)
{
    if(initialized == LE_FALSE)
        return;

    initialized = LE_FALSE;
}

leWidget* screenGetRoot_restoreSettingScreen(uint32_t lyrIdx)
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

