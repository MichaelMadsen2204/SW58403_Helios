#include "gfx/legato/generated/screen/le_gen_screen_avInputScreen.h"

// screen member widget declarations
static leWidget* root0;

leWidget* avInputScreen_PanelWidget0;
leRectangleWidget* avInputScreen_RectangleWidget0;
leRectangleWidget* avInputScreen_RectangleWidget1;
leLabelWidget* avInputScreen_avInpHeader;
leLabelWidget* avInputScreen_LabelWidget0;
leLabelWidget* avInputScreen_LabelWidget1;
leLabelWidget* avInputScreen_LabelWidget2;
leLabelWidget* avInputScreen_LabelWidget3;
leButtonWidget* avInputScreen_inp3Button;
leButtonWidget* avInputScreen_inp4Button;
leButtonWidget* avInputScreen_noneButton;
leLabelWidget* avInputScreen_LabelWidget4;
leLabelWidget* avInputScreen_LabelWidget5;
leLabelWidget* avInputScreen_LabelWidget6;
leLabelWidget* avInputScreen_LabelWidget7;
leLabelWidget* avInputScreen_LabelWidget8;
leImageWidget* avInputScreen_ImageWidget0;
leButtonWidget* avInputScreen_menuExitButton;

static leBool initialized = LE_FALSE;
static leBool showing = LE_FALSE;

leResult screenInit_avInputScreen(void)
{
    if(initialized == LE_TRUE)
        return LE_FAILURE;

    initialized = LE_TRUE;

    return LE_SUCCESS;
}

leResult screenShow_avInputScreen(void)
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

    avInputScreen_PanelWidget0 = leWidget_New();
    avInputScreen_PanelWidget0->fn->setPosition(avInputScreen_PanelWidget0, 0, 0);
    avInputScreen_PanelWidget0->fn->setSize(avInputScreen_PanelWidget0, 480, 272);
    avInputScreen_PanelWidget0->fn->setScheme(avInputScreen_PanelWidget0, &BlackScheme);
    root0->fn->addChild(root0, (leWidget*)avInputScreen_PanelWidget0);

    avInputScreen_RectangleWidget0 = leRectangleWidget_New();
    avInputScreen_RectangleWidget0->fn->setPosition(avInputScreen_RectangleWidget0, 26, 25);
    avInputScreen_RectangleWidget0->fn->setSize(avInputScreen_RectangleWidget0, 160, 3);
    avInputScreen_RectangleWidget0->fn->setScheme(avInputScreen_RectangleWidget0, &WhiteScheme);
    avInputScreen_RectangleWidget0->fn->setBorderType(avInputScreen_RectangleWidget0, LE_WIDGET_BORDER_NONE);
    avInputScreen_RectangleWidget0->fn->setThickness(avInputScreen_RectangleWidget0, 2);
    root0->fn->addChild(root0, (leWidget*)avInputScreen_RectangleWidget0);

    avInputScreen_RectangleWidget1 = leRectangleWidget_New();
    avInputScreen_RectangleWidget1->fn->setPosition(avInputScreen_RectangleWidget1, 294, 25);
    avInputScreen_RectangleWidget1->fn->setSize(avInputScreen_RectangleWidget1, 160, 3);
    avInputScreen_RectangleWidget1->fn->setScheme(avInputScreen_RectangleWidget1, &WhiteScheme);
    avInputScreen_RectangleWidget1->fn->setBorderType(avInputScreen_RectangleWidget1, LE_WIDGET_BORDER_NONE);
    avInputScreen_RectangleWidget1->fn->setThickness(avInputScreen_RectangleWidget1, 2);
    root0->fn->addChild(root0, (leWidget*)avInputScreen_RectangleWidget1);

    avInputScreen_avInpHeader = leLabelWidget_New();
    avInputScreen_avInpHeader->fn->setPosition(avInputScreen_avInpHeader, 0, 12);
    avInputScreen_avInpHeader->fn->setSize(avInputScreen_avInpHeader, 480, 25);
    avInputScreen_avInpHeader->fn->setScheme(avInputScreen_avInpHeader, &BlackScheme);
    avInputScreen_avInpHeader->fn->setBackgroundType(avInputScreen_avInpHeader, LE_WIDGET_BACKGROUND_NONE);
    avInputScreen_avInpHeader->fn->setHAlignment(avInputScreen_avInpHeader, LE_HALIGN_CENTER);
    avInputScreen_avInpHeader->fn->setString(avInputScreen_avInpHeader, (leString*)&string_menuAvInputStr);
    root0->fn->addChild(root0, (leWidget*)avInputScreen_avInpHeader);

    avInputScreen_LabelWidget0 = leLabelWidget_New();
    avInputScreen_LabelWidget0->fn->setPosition(avInputScreen_LabelWidget0, 0, 52);
    avInputScreen_LabelWidget0->fn->setSize(avInputScreen_LabelWidget0, 480, 25);
    avInputScreen_LabelWidget0->fn->setScheme(avInputScreen_LabelWidget0, &BlackScheme);
    avInputScreen_LabelWidget0->fn->setBackgroundType(avInputScreen_LabelWidget0, LE_WIDGET_BACKGROUND_NONE);
    avInputScreen_LabelWidget0->fn->setHAlignment(avInputScreen_LabelWidget0, LE_HALIGN_CENTER);
    avInputScreen_LabelWidget0->fn->setString(avInputScreen_LabelWidget0, (leString*)&string_avInpLine1);
    root0->fn->addChild(root0, (leWidget*)avInputScreen_LabelWidget0);

    avInputScreen_LabelWidget1 = leLabelWidget_New();
    avInputScreen_LabelWidget1->fn->setPosition(avInputScreen_LabelWidget1, 0, 80);
    avInputScreen_LabelWidget1->fn->setSize(avInputScreen_LabelWidget1, 480, 25);
    avInputScreen_LabelWidget1->fn->setScheme(avInputScreen_LabelWidget1, &BlackScheme);
    avInputScreen_LabelWidget1->fn->setBackgroundType(avInputScreen_LabelWidget1, LE_WIDGET_BACKGROUND_NONE);
    avInputScreen_LabelWidget1->fn->setHAlignment(avInputScreen_LabelWidget1, LE_HALIGN_CENTER);
    avInputScreen_LabelWidget1->fn->setString(avInputScreen_LabelWidget1, (leString*)&string_avInpLine2);
    root0->fn->addChild(root0, (leWidget*)avInputScreen_LabelWidget1);

    avInputScreen_LabelWidget2 = leLabelWidget_New();
    avInputScreen_LabelWidget2->fn->setPosition(avInputScreen_LabelWidget2, 0, 108);
    avInputScreen_LabelWidget2->fn->setSize(avInputScreen_LabelWidget2, 480, 25);
    avInputScreen_LabelWidget2->fn->setScheme(avInputScreen_LabelWidget2, &warningScheme);
    avInputScreen_LabelWidget2->fn->setBackgroundType(avInputScreen_LabelWidget2, LE_WIDGET_BACKGROUND_NONE);
    avInputScreen_LabelWidget2->fn->setHAlignment(avInputScreen_LabelWidget2, LE_HALIGN_CENTER);
    avInputScreen_LabelWidget2->fn->setString(avInputScreen_LabelWidget2, (leString*)&string_avInpLine3);
    root0->fn->addChild(root0, (leWidget*)avInputScreen_LabelWidget2);

    avInputScreen_LabelWidget3 = leLabelWidget_New();
    avInputScreen_LabelWidget3->fn->setPosition(avInputScreen_LabelWidget3, 0, 136);
    avInputScreen_LabelWidget3->fn->setSize(avInputScreen_LabelWidget3, 480, 25);
    avInputScreen_LabelWidget3->fn->setScheme(avInputScreen_LabelWidget3, &warningScheme);
    avInputScreen_LabelWidget3->fn->setBackgroundType(avInputScreen_LabelWidget3, LE_WIDGET_BACKGROUND_NONE);
    avInputScreen_LabelWidget3->fn->setHAlignment(avInputScreen_LabelWidget3, LE_HALIGN_CENTER);
    avInputScreen_LabelWidget3->fn->setString(avInputScreen_LabelWidget3, (leString*)&string_avInpLine4);
    root0->fn->addChild(root0, (leWidget*)avInputScreen_LabelWidget3);

    avInputScreen_inp3Button = leButtonWidget_New();
    avInputScreen_inp3Button->fn->setPosition(avInputScreen_inp3Button, 35, 190);
    avInputScreen_inp3Button->fn->setSize(avInputScreen_inp3Button, 40, 66);
    avInputScreen_inp3Button->fn->setScheme(avInputScreen_inp3Button, &BlackScheme);
    avInputScreen_inp3Button->fn->setBackgroundType(avInputScreen_inp3Button, LE_WIDGET_BACKGROUND_NONE);
    avInputScreen_inp3Button->fn->setBorderType(avInputScreen_inp3Button, LE_WIDGET_BORDER_NONE);
    avInputScreen_inp3Button->fn->setToggleable(avInputScreen_inp3Button, LE_TRUE);
    avInputScreen_inp3Button->fn->setPressedImage(avInputScreen_inp3Button, (leImage*)&largeSelected);
    avInputScreen_inp3Button->fn->setReleasedImage(avInputScreen_inp3Button, (leImage*)&largeNotSelected);
    avInputScreen_inp3Button->fn->setPressedEventCallback(avInputScreen_inp3Button, event_avInputScreen_inp3Button_OnPressed);
    avInputScreen_inp3Button->fn->setReleasedEventCallback(avInputScreen_inp3Button, event_avInputScreen_inp3Button_OnReleased);
    root0->fn->addChild(root0, (leWidget*)avInputScreen_inp3Button);

    avInputScreen_inp4Button = leButtonWidget_New();
    avInputScreen_inp4Button->fn->setPosition(avInputScreen_inp4Button, 155, 190);
    avInputScreen_inp4Button->fn->setSize(avInputScreen_inp4Button, 40, 66);
    avInputScreen_inp4Button->fn->setScheme(avInputScreen_inp4Button, &BlackScheme);
    avInputScreen_inp4Button->fn->setBackgroundType(avInputScreen_inp4Button, LE_WIDGET_BACKGROUND_NONE);
    avInputScreen_inp4Button->fn->setBorderType(avInputScreen_inp4Button, LE_WIDGET_BORDER_NONE);
    avInputScreen_inp4Button->fn->setToggleable(avInputScreen_inp4Button, LE_TRUE);
    avInputScreen_inp4Button->fn->setPressedImage(avInputScreen_inp4Button, (leImage*)&largeSelected);
    avInputScreen_inp4Button->fn->setReleasedImage(avInputScreen_inp4Button, (leImage*)&largeNotSelected);
    avInputScreen_inp4Button->fn->setPressedEventCallback(avInputScreen_inp4Button, event_avInputScreen_inp4Button_OnPressed);
    avInputScreen_inp4Button->fn->setReleasedEventCallback(avInputScreen_inp4Button, event_avInputScreen_inp4Button_OnReleased);
    root0->fn->addChild(root0, (leWidget*)avInputScreen_inp4Button);

    avInputScreen_noneButton = leButtonWidget_New();
    avInputScreen_noneButton->fn->setPosition(avInputScreen_noneButton, 275, 190);
    avInputScreen_noneButton->fn->setSize(avInputScreen_noneButton, 40, 66);
    avInputScreen_noneButton->fn->setScheme(avInputScreen_noneButton, &BlackScheme);
    avInputScreen_noneButton->fn->setBackgroundType(avInputScreen_noneButton, LE_WIDGET_BACKGROUND_NONE);
    avInputScreen_noneButton->fn->setBorderType(avInputScreen_noneButton, LE_WIDGET_BORDER_NONE);
    avInputScreen_noneButton->fn->setToggleable(avInputScreen_noneButton, LE_TRUE);
    avInputScreen_noneButton->fn->setPressedImage(avInputScreen_noneButton, (leImage*)&largeSelected);
    avInputScreen_noneButton->fn->setReleasedImage(avInputScreen_noneButton, (leImage*)&largeNotSelected);
    avInputScreen_noneButton->fn->setPressedEventCallback(avInputScreen_noneButton, event_avInputScreen_noneButton_OnPressed);
    root0->fn->addChild(root0, (leWidget*)avInputScreen_noneButton);

    avInputScreen_LabelWidget4 = leLabelWidget_New();
    avInputScreen_LabelWidget4->fn->setPosition(avInputScreen_LabelWidget4, 5, 180);
    avInputScreen_LabelWidget4->fn->setScheme(avInputScreen_LabelWidget4, &BlackScheme);
    avInputScreen_LabelWidget4->fn->setBackgroundType(avInputScreen_LabelWidget4, LE_WIDGET_BACKGROUND_NONE);
    avInputScreen_LabelWidget4->fn->setHAlignment(avInputScreen_LabelWidget4, LE_HALIGN_CENTER);
    avInputScreen_LabelWidget4->fn->setString(avInputScreen_LabelWidget4, (leString*)&string_avInp3Str);
    root0->fn->addChild(root0, (leWidget*)avInputScreen_LabelWidget4);

    avInputScreen_LabelWidget5 = leLabelWidget_New();
    avInputScreen_LabelWidget5->fn->setPosition(avInputScreen_LabelWidget5, 5, 240);
    avInputScreen_LabelWidget5->fn->setScheme(avInputScreen_LabelWidget5, &BlackScheme);
    avInputScreen_LabelWidget5->fn->setBackgroundType(avInputScreen_LabelWidget5, LE_WIDGET_BACKGROUND_NONE);
    avInputScreen_LabelWidget5->fn->setHAlignment(avInputScreen_LabelWidget5, LE_HALIGN_CENTER);
    avInputScreen_LabelWidget5->fn->setString(avInputScreen_LabelWidget5, (leString*)&string_avBalanced);
    root0->fn->addChild(root0, (leWidget*)avInputScreen_LabelWidget5);

    avInputScreen_LabelWidget6 = leLabelWidget_New();
    avInputScreen_LabelWidget6->fn->setPosition(avInputScreen_LabelWidget6, 126, 180);
    avInputScreen_LabelWidget6->fn->setScheme(avInputScreen_LabelWidget6, &BlackScheme);
    avInputScreen_LabelWidget6->fn->setBackgroundType(avInputScreen_LabelWidget6, LE_WIDGET_BACKGROUND_NONE);
    avInputScreen_LabelWidget6->fn->setHAlignment(avInputScreen_LabelWidget6, LE_HALIGN_CENTER);
    avInputScreen_LabelWidget6->fn->setString(avInputScreen_LabelWidget6, (leString*)&string_avInp4Str);
    root0->fn->addChild(root0, (leWidget*)avInputScreen_LabelWidget6);

    avInputScreen_LabelWidget7 = leLabelWidget_New();
    avInputScreen_LabelWidget7->fn->setPosition(avInputScreen_LabelWidget7, 111, 240);
    avInputScreen_LabelWidget7->fn->setSize(avInputScreen_LabelWidget7, 126, 25);
    avInputScreen_LabelWidget7->fn->setScheme(avInputScreen_LabelWidget7, &BlackScheme);
    avInputScreen_LabelWidget7->fn->setBackgroundType(avInputScreen_LabelWidget7, LE_WIDGET_BACKGROUND_NONE);
    avInputScreen_LabelWidget7->fn->setHAlignment(avInputScreen_LabelWidget7, LE_HALIGN_CENTER);
    avInputScreen_LabelWidget7->fn->setString(avInputScreen_LabelWidget7, (leString*)&string_avSingleStr);
    root0->fn->addChild(root0, (leWidget*)avInputScreen_LabelWidget7);

    avInputScreen_LabelWidget8 = leLabelWidget_New();
    avInputScreen_LabelWidget8->fn->setPosition(avInputScreen_LabelWidget8, 246, 180);
    avInputScreen_LabelWidget8->fn->setScheme(avInputScreen_LabelWidget8, &BlackScheme);
    avInputScreen_LabelWidget8->fn->setBackgroundType(avInputScreen_LabelWidget8, LE_WIDGET_BACKGROUND_NONE);
    avInputScreen_LabelWidget8->fn->setHAlignment(avInputScreen_LabelWidget8, LE_HALIGN_CENTER);
    avInputScreen_LabelWidget8->fn->setString(avInputScreen_LabelWidget8, (leString*)&string_avNone);
    root0->fn->addChild(root0, (leWidget*)avInputScreen_LabelWidget8);

    avInputScreen_ImageWidget0 = leImageWidget_New();
    avInputScreen_ImageWidget0->fn->setPosition(avInputScreen_ImageWidget0, 340, 205);
    avInputScreen_ImageWidget0->fn->setSize(avInputScreen_ImageWidget0, 110, 50);
    avInputScreen_ImageWidget0->fn->setScheme(avInputScreen_ImageWidget0, &BlackScheme);
    avInputScreen_ImageWidget0->fn->setBackgroundType(avInputScreen_ImageWidget0, LE_WIDGET_BACKGROUND_NONE);
    avInputScreen_ImageWidget0->fn->setBorderType(avInputScreen_ImageWidget0, LE_WIDGET_BORDER_NONE);
    avInputScreen_ImageWidget0->fn->setImage(avInputScreen_ImageWidget0, (leImage*)&BackToMenu);
    root0->fn->addChild(root0, (leWidget*)avInputScreen_ImageWidget0);

    avInputScreen_menuExitButton = leButtonWidget_New();
    avInputScreen_menuExitButton->fn->setPosition(avInputScreen_menuExitButton, 1, 1);
    avInputScreen_menuExitButton->fn->setSize(avInputScreen_menuExitButton, 110, 50);
    avInputScreen_menuExitButton->fn->setBackgroundType(avInputScreen_menuExitButton, LE_WIDGET_BACKGROUND_NONE);
    avInputScreen_menuExitButton->fn->setBorderType(avInputScreen_menuExitButton, LE_WIDGET_BORDER_NONE);
    avInputScreen_menuExitButton->fn->setPressedEventCallback(avInputScreen_menuExitButton, event_avInputScreen_menuExitButton_OnPressed);
    avInputScreen_ImageWidget0->fn->addChild(avInputScreen_ImageWidget0, (leWidget*)avInputScreen_menuExitButton);

    leAddRootWidget(root0, 0);
    leSetLayerColorMode(0, LE_COLOR_MODE_RGB_565);

    avInputScreen_OnShow(); // raise event

    showing = LE_TRUE;

    return LE_SUCCESS;
}

void screenUpdate_avInputScreen(void)
{
    root0->fn->setSize(root0, root0->rect.width, root0->rect.height);
}

void screenHide_avInputScreen(void)
{
    avInputScreen_OnHide(); // raise event


    leRemoveRootWidget(root0, 0);
    leWidget_Delete(root0);
    root0 = NULL;

    avInputScreen_PanelWidget0 = NULL;
    avInputScreen_RectangleWidget0 = NULL;
    avInputScreen_RectangleWidget1 = NULL;
    avInputScreen_avInpHeader = NULL;
    avInputScreen_LabelWidget0 = NULL;
    avInputScreen_LabelWidget1 = NULL;
    avInputScreen_LabelWidget2 = NULL;
    avInputScreen_LabelWidget3 = NULL;
    avInputScreen_inp3Button = NULL;
    avInputScreen_inp4Button = NULL;
    avInputScreen_noneButton = NULL;
    avInputScreen_LabelWidget4 = NULL;
    avInputScreen_LabelWidget5 = NULL;
    avInputScreen_LabelWidget6 = NULL;
    avInputScreen_LabelWidget7 = NULL;
    avInputScreen_LabelWidget8 = NULL;
    avInputScreen_ImageWidget0 = NULL;
    avInputScreen_menuExitButton = NULL;


    showing = LE_FALSE;
}

void screenDestroy_avInputScreen(void)
{
    if(initialized == LE_FALSE)
        return;

    initialized = LE_FALSE;
}

leWidget* screenGetRoot_avInputScreen(uint32_t lyrIdx)
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

