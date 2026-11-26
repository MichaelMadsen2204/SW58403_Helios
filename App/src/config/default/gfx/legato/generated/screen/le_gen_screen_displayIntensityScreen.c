#include "gfx/legato/generated/screen/le_gen_screen_displayIntensityScreen.h"

// screen member widget declarations
static leWidget* root0;

leWidget* displayIntensityScreen_PanelWidget0;
leRectangleWidget* displayIntensityScreen_RectangleWidget0;
leRectangleWidget* displayIntensityScreen_RectangleWidget1;
leLabelWidget* displayIntensityScreen_dispIntensHeader;
leButtonWidget* displayIntensityScreen_disp100Button;
leButtonWidget* displayIntensityScreen_disp75Button;
leButtonWidget* displayIntensityScreen_disp50Button;
leButtonWidget* displayIntensityScreen_disp25Button;
leButtonWidget* displayIntensityScreen_dispDimButton;
leButtonWidget* displayIntensityScreen_dispOffButton;
leLabelWidget* displayIntensityScreen_LabelWidget0;
leLabelWidget* displayIntensityScreen_LabelWidget1;
leButtonWidget* displayIntensityScreen_simpleViewOnButton;
leButtonWidget* displayIntensityScreen_simpViewOffButton;
leImageWidget* displayIntensityScreen_ImageWidget0;
leButtonWidget* displayIntensityScreen_dispExitButton;

static leBool initialized = LE_FALSE;
static leBool showing = LE_FALSE;

leResult screenInit_displayIntensityScreen(void)
{
    if(initialized == LE_TRUE)
        return LE_FAILURE;

    initialized = LE_TRUE;

    return LE_SUCCESS;
}

leResult screenShow_displayIntensityScreen(void)
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

    displayIntensityScreen_PanelWidget0 = leWidget_New();
    displayIntensityScreen_PanelWidget0->fn->setPosition(displayIntensityScreen_PanelWidget0, 0, 0);
    displayIntensityScreen_PanelWidget0->fn->setSize(displayIntensityScreen_PanelWidget0, 480, 272);
    displayIntensityScreen_PanelWidget0->fn->setScheme(displayIntensityScreen_PanelWidget0, &BlackScheme);
    root0->fn->addChild(root0, (leWidget*)displayIntensityScreen_PanelWidget0);

    displayIntensityScreen_RectangleWidget0 = leRectangleWidget_New();
    displayIntensityScreen_RectangleWidget0->fn->setPosition(displayIntensityScreen_RectangleWidget0, 26, 25);
    displayIntensityScreen_RectangleWidget0->fn->setSize(displayIntensityScreen_RectangleWidget0, 165, 3);
    displayIntensityScreen_RectangleWidget0->fn->setScheme(displayIntensityScreen_RectangleWidget0, &WhiteScheme);
    displayIntensityScreen_RectangleWidget0->fn->setBorderType(displayIntensityScreen_RectangleWidget0, LE_WIDGET_BORDER_NONE);
    displayIntensityScreen_RectangleWidget0->fn->setThickness(displayIntensityScreen_RectangleWidget0, 2);
    root0->fn->addChild(root0, (leWidget*)displayIntensityScreen_RectangleWidget0);

    displayIntensityScreen_RectangleWidget1 = leRectangleWidget_New();
    displayIntensityScreen_RectangleWidget1->fn->setPosition(displayIntensityScreen_RectangleWidget1, 289, 25);
    displayIntensityScreen_RectangleWidget1->fn->setSize(displayIntensityScreen_RectangleWidget1, 165, 3);
    displayIntensityScreen_RectangleWidget1->fn->setScheme(displayIntensityScreen_RectangleWidget1, &WhiteScheme);
    displayIntensityScreen_RectangleWidget1->fn->setBorderType(displayIntensityScreen_RectangleWidget1, LE_WIDGET_BORDER_NONE);
    displayIntensityScreen_RectangleWidget1->fn->setThickness(displayIntensityScreen_RectangleWidget1, 2);
    root0->fn->addChild(root0, (leWidget*)displayIntensityScreen_RectangleWidget1);

    displayIntensityScreen_dispIntensHeader = leLabelWidget_New();
    displayIntensityScreen_dispIntensHeader->fn->setPosition(displayIntensityScreen_dispIntensHeader, 0, 12);
    displayIntensityScreen_dispIntensHeader->fn->setSize(displayIntensityScreen_dispIntensHeader, 480, 25);
    displayIntensityScreen_dispIntensHeader->fn->setScheme(displayIntensityScreen_dispIntensHeader, &BlackScheme);
    displayIntensityScreen_dispIntensHeader->fn->setBackgroundType(displayIntensityScreen_dispIntensHeader, LE_WIDGET_BACKGROUND_NONE);
    displayIntensityScreen_dispIntensHeader->fn->setHAlignment(displayIntensityScreen_dispIntensHeader, LE_HALIGN_CENTER);
    displayIntensityScreen_dispIntensHeader->fn->setString(displayIntensityScreen_dispIntensHeader, (leString*)&string_menuDisplayStr);
    root0->fn->addChild(root0, (leWidget*)displayIntensityScreen_dispIntensHeader);

    displayIntensityScreen_disp100Button = leButtonWidget_New();
    displayIntensityScreen_disp100Button->fn->setPosition(displayIntensityScreen_disp100Button, 31, 60);
    displayIntensityScreen_disp100Button->fn->setSize(displayIntensityScreen_disp100Button, 150, 30);
    displayIntensityScreen_disp100Button->fn->setScheme(displayIntensityScreen_disp100Button, &BlackScheme);
    displayIntensityScreen_disp100Button->fn->setBackgroundType(displayIntensityScreen_disp100Button, LE_WIDGET_BACKGROUND_NONE);
    displayIntensityScreen_disp100Button->fn->setBorderType(displayIntensityScreen_disp100Button, LE_WIDGET_BORDER_NONE);
    displayIntensityScreen_disp100Button->fn->setHAlignment(displayIntensityScreen_disp100Button, LE_HALIGN_LEFT);
    displayIntensityScreen_disp100Button->fn->setString(displayIntensityScreen_disp100Button, (leString*)&string_percent100Str);
    displayIntensityScreen_disp100Button->fn->setPressedImage(displayIntensityScreen_disp100Button, (leImage*)&smallSelected2);
    displayIntensityScreen_disp100Button->fn->setReleasedImage(displayIntensityScreen_disp100Button, (leImage*)&smallNotSelected3);
    displayIntensityScreen_disp100Button->fn->setImageMargin(displayIntensityScreen_disp100Button, 5);
    displayIntensityScreen_disp100Button->fn->setPressedOffset(displayIntensityScreen_disp100Button, 0);
    displayIntensityScreen_disp100Button->fn->setPressedEventCallback(displayIntensityScreen_disp100Button, event_displayIntensityScreen_disp100Button_OnPressed);
    root0->fn->addChild(root0, (leWidget*)displayIntensityScreen_disp100Button);

    displayIntensityScreen_disp75Button = leButtonWidget_New();
    displayIntensityScreen_disp75Button->fn->setPosition(displayIntensityScreen_disp75Button, 31, 90);
    displayIntensityScreen_disp75Button->fn->setSize(displayIntensityScreen_disp75Button, 150, 30);
    displayIntensityScreen_disp75Button->fn->setScheme(displayIntensityScreen_disp75Button, &BlackScheme);
    displayIntensityScreen_disp75Button->fn->setBackgroundType(displayIntensityScreen_disp75Button, LE_WIDGET_BACKGROUND_NONE);
    displayIntensityScreen_disp75Button->fn->setBorderType(displayIntensityScreen_disp75Button, LE_WIDGET_BORDER_NONE);
    displayIntensityScreen_disp75Button->fn->setHAlignment(displayIntensityScreen_disp75Button, LE_HALIGN_LEFT);
    displayIntensityScreen_disp75Button->fn->setString(displayIntensityScreen_disp75Button, (leString*)&string_percent75Str);
    displayIntensityScreen_disp75Button->fn->setPressedImage(displayIntensityScreen_disp75Button, (leImage*)&smallSelected2);
    displayIntensityScreen_disp75Button->fn->setReleasedImage(displayIntensityScreen_disp75Button, (leImage*)&smallNotSelected3);
    displayIntensityScreen_disp75Button->fn->setImageMargin(displayIntensityScreen_disp75Button, 5);
    displayIntensityScreen_disp75Button->fn->setPressedOffset(displayIntensityScreen_disp75Button, 0);
    displayIntensityScreen_disp75Button->fn->setPressedEventCallback(displayIntensityScreen_disp75Button, event_displayIntensityScreen_disp75Button_OnPressed);
    root0->fn->addChild(root0, (leWidget*)displayIntensityScreen_disp75Button);

    displayIntensityScreen_disp50Button = leButtonWidget_New();
    displayIntensityScreen_disp50Button->fn->setPosition(displayIntensityScreen_disp50Button, 31, 120);
    displayIntensityScreen_disp50Button->fn->setSize(displayIntensityScreen_disp50Button, 150, 30);
    displayIntensityScreen_disp50Button->fn->setScheme(displayIntensityScreen_disp50Button, &BlackScheme);
    displayIntensityScreen_disp50Button->fn->setBackgroundType(displayIntensityScreen_disp50Button, LE_WIDGET_BACKGROUND_NONE);
    displayIntensityScreen_disp50Button->fn->setBorderType(displayIntensityScreen_disp50Button, LE_WIDGET_BORDER_NONE);
    displayIntensityScreen_disp50Button->fn->setHAlignment(displayIntensityScreen_disp50Button, LE_HALIGN_LEFT);
    displayIntensityScreen_disp50Button->fn->setString(displayIntensityScreen_disp50Button, (leString*)&string_percent50Str);
    displayIntensityScreen_disp50Button->fn->setPressedImage(displayIntensityScreen_disp50Button, (leImage*)&smallSelected2);
    displayIntensityScreen_disp50Button->fn->setReleasedImage(displayIntensityScreen_disp50Button, (leImage*)&smallNotSelected3);
    displayIntensityScreen_disp50Button->fn->setImageMargin(displayIntensityScreen_disp50Button, 5);
    displayIntensityScreen_disp50Button->fn->setPressedOffset(displayIntensityScreen_disp50Button, 0);
    displayIntensityScreen_disp50Button->fn->setPressedEventCallback(displayIntensityScreen_disp50Button, event_displayIntensityScreen_disp50Button_OnPressed);
    root0->fn->addChild(root0, (leWidget*)displayIntensityScreen_disp50Button);

    displayIntensityScreen_disp25Button = leButtonWidget_New();
    displayIntensityScreen_disp25Button->fn->setPosition(displayIntensityScreen_disp25Button, 31, 150);
    displayIntensityScreen_disp25Button->fn->setSize(displayIntensityScreen_disp25Button, 150, 30);
    displayIntensityScreen_disp25Button->fn->setScheme(displayIntensityScreen_disp25Button, &BlackScheme);
    displayIntensityScreen_disp25Button->fn->setBackgroundType(displayIntensityScreen_disp25Button, LE_WIDGET_BACKGROUND_NONE);
    displayIntensityScreen_disp25Button->fn->setBorderType(displayIntensityScreen_disp25Button, LE_WIDGET_BORDER_NONE);
    displayIntensityScreen_disp25Button->fn->setHAlignment(displayIntensityScreen_disp25Button, LE_HALIGN_LEFT);
    displayIntensityScreen_disp25Button->fn->setString(displayIntensityScreen_disp25Button, (leString*)&string_percent25Str);
    displayIntensityScreen_disp25Button->fn->setPressedImage(displayIntensityScreen_disp25Button, (leImage*)&smallSelected2);
    displayIntensityScreen_disp25Button->fn->setReleasedImage(displayIntensityScreen_disp25Button, (leImage*)&smallNotSelected3);
    displayIntensityScreen_disp25Button->fn->setImageMargin(displayIntensityScreen_disp25Button, 5);
    displayIntensityScreen_disp25Button->fn->setPressedOffset(displayIntensityScreen_disp25Button, 0);
    displayIntensityScreen_disp25Button->fn->setPressedEventCallback(displayIntensityScreen_disp25Button, event_displayIntensityScreen_disp25Button_OnPressed);
    root0->fn->addChild(root0, (leWidget*)displayIntensityScreen_disp25Button);

    displayIntensityScreen_dispDimButton = leButtonWidget_New();
    displayIntensityScreen_dispDimButton->fn->setPosition(displayIntensityScreen_dispDimButton, 31, 210);
    displayIntensityScreen_dispDimButton->fn->setSize(displayIntensityScreen_dispDimButton, 150, 30);
    displayIntensityScreen_dispDimButton->fn->setScheme(displayIntensityScreen_dispDimButton, &BlackScheme);
    displayIntensityScreen_dispDimButton->fn->setBackgroundType(displayIntensityScreen_dispDimButton, LE_WIDGET_BACKGROUND_NONE);
    displayIntensityScreen_dispDimButton->fn->setBorderType(displayIntensityScreen_dispDimButton, LE_WIDGET_BORDER_NONE);
    displayIntensityScreen_dispDimButton->fn->setHAlignment(displayIntensityScreen_dispDimButton, LE_HALIGN_LEFT);
    displayIntensityScreen_dispDimButton->fn->setString(displayIntensityScreen_dispDimButton, (leString*)&string_autoDimStr);
    displayIntensityScreen_dispDimButton->fn->setPressedImage(displayIntensityScreen_dispDimButton, (leImage*)&smallSelected2);
    displayIntensityScreen_dispDimButton->fn->setReleasedImage(displayIntensityScreen_dispDimButton, (leImage*)&smallNotSelected3);
    displayIntensityScreen_dispDimButton->fn->setImageMargin(displayIntensityScreen_dispDimButton, 5);
    displayIntensityScreen_dispDimButton->fn->setPressedOffset(displayIntensityScreen_dispDimButton, 0);
    displayIntensityScreen_dispDimButton->fn->setPressedEventCallback(displayIntensityScreen_dispDimButton, event_displayIntensityScreen_dispDimButton_OnPressed);
    root0->fn->addChild(root0, (leWidget*)displayIntensityScreen_dispDimButton);

    displayIntensityScreen_dispOffButton = leButtonWidget_New();
    displayIntensityScreen_dispOffButton->fn->setPosition(displayIntensityScreen_dispOffButton, 31, 180);
    displayIntensityScreen_dispOffButton->fn->setSize(displayIntensityScreen_dispOffButton, 150, 30);
    displayIntensityScreen_dispOffButton->fn->setScheme(displayIntensityScreen_dispOffButton, &BlackScheme);
    displayIntensityScreen_dispOffButton->fn->setBackgroundType(displayIntensityScreen_dispOffButton, LE_WIDGET_BACKGROUND_NONE);
    displayIntensityScreen_dispOffButton->fn->setBorderType(displayIntensityScreen_dispOffButton, LE_WIDGET_BORDER_NONE);
    displayIntensityScreen_dispOffButton->fn->setHAlignment(displayIntensityScreen_dispOffButton, LE_HALIGN_LEFT);
    displayIntensityScreen_dispOffButton->fn->setString(displayIntensityScreen_dispOffButton, (leString*)&string_autoOffStr);
    displayIntensityScreen_dispOffButton->fn->setPressedImage(displayIntensityScreen_dispOffButton, (leImage*)&smallSelected2);
    displayIntensityScreen_dispOffButton->fn->setReleasedImage(displayIntensityScreen_dispOffButton, (leImage*)&smallNotSelected3);
    displayIntensityScreen_dispOffButton->fn->setImageMargin(displayIntensityScreen_dispOffButton, 5);
    displayIntensityScreen_dispOffButton->fn->setPressedOffset(displayIntensityScreen_dispOffButton, 0);
    displayIntensityScreen_dispOffButton->fn->setPressedEventCallback(displayIntensityScreen_dispOffButton, event_displayIntensityScreen_dispOffButton_OnPressed);
    root0->fn->addChild(root0, (leWidget*)displayIntensityScreen_dispOffButton);

    displayIntensityScreen_LabelWidget0 = leLabelWidget_New();
    displayIntensityScreen_LabelWidget0->fn->setPosition(displayIntensityScreen_LabelWidget0, 31, 35);
    displayIntensityScreen_LabelWidget0->fn->setSize(displayIntensityScreen_LabelWidget0, 157, 25);
    displayIntensityScreen_LabelWidget0->fn->setScheme(displayIntensityScreen_LabelWidget0, &BlackScheme);
    displayIntensityScreen_LabelWidget0->fn->setBackgroundType(displayIntensityScreen_LabelWidget0, LE_WIDGET_BACKGROUND_NONE);
    displayIntensityScreen_LabelWidget0->fn->setString(displayIntensityScreen_LabelWidget0, (leString*)&string_disIntensStr);
    root0->fn->addChild(root0, (leWidget*)displayIntensityScreen_LabelWidget0);

    displayIntensityScreen_LabelWidget1 = leLabelWidget_New();
    displayIntensityScreen_LabelWidget1->fn->setPosition(displayIntensityScreen_LabelWidget1, 313, 35);
    displayIntensityScreen_LabelWidget1->fn->setSize(displayIntensityScreen_LabelWidget1, 140, 25);
    displayIntensityScreen_LabelWidget1->fn->setScheme(displayIntensityScreen_LabelWidget1, &BlackScheme);
    displayIntensityScreen_LabelWidget1->fn->setBackgroundType(displayIntensityScreen_LabelWidget1, LE_WIDGET_BACKGROUND_NONE);
    displayIntensityScreen_LabelWidget1->fn->setHAlignment(displayIntensityScreen_LabelWidget1, LE_HALIGN_RIGHT);
    displayIntensityScreen_LabelWidget1->fn->setString(displayIntensityScreen_LabelWidget1, (leString*)&string_simpleViewStr);
    root0->fn->addChild(root0, (leWidget*)displayIntensityScreen_LabelWidget1);

    displayIntensityScreen_simpleViewOnButton = leButtonWidget_New();
    displayIntensityScreen_simpleViewOnButton->fn->setPosition(displayIntensityScreen_simpleViewOnButton, 340, 80);
    displayIntensityScreen_simpleViewOnButton->fn->setSize(displayIntensityScreen_simpleViewOnButton, 100, 30);
    displayIntensityScreen_simpleViewOnButton->fn->setScheme(displayIntensityScreen_simpleViewOnButton, &BlackScheme);
    displayIntensityScreen_simpleViewOnButton->fn->setBackgroundType(displayIntensityScreen_simpleViewOnButton, LE_WIDGET_BACKGROUND_NONE);
    displayIntensityScreen_simpleViewOnButton->fn->setBorderType(displayIntensityScreen_simpleViewOnButton, LE_WIDGET_BORDER_NONE);
    displayIntensityScreen_simpleViewOnButton->fn->setHAlignment(displayIntensityScreen_simpleViewOnButton, LE_HALIGN_LEFT);
    displayIntensityScreen_simpleViewOnButton->fn->setToggleable(displayIntensityScreen_simpleViewOnButton, LE_TRUE);
    displayIntensityScreen_simpleViewOnButton->fn->setString(displayIntensityScreen_simpleViewOnButton, (leString*)&string_onStr);
    displayIntensityScreen_simpleViewOnButton->fn->setPressedImage(displayIntensityScreen_simpleViewOnButton, (leImage*)&largeSelected);
    displayIntensityScreen_simpleViewOnButton->fn->setReleasedImage(displayIntensityScreen_simpleViewOnButton, (leImage*)&largeNotSelected);
    displayIntensityScreen_simpleViewOnButton->fn->setImageMargin(displayIntensityScreen_simpleViewOnButton, 5);
    displayIntensityScreen_simpleViewOnButton->fn->setPressedOffset(displayIntensityScreen_simpleViewOnButton, 0);
    displayIntensityScreen_simpleViewOnButton->fn->setPressedEventCallback(displayIntensityScreen_simpleViewOnButton, event_displayIntensityScreen_simpleViewOnButton_OnPressed);
    root0->fn->addChild(root0, (leWidget*)displayIntensityScreen_simpleViewOnButton);

    displayIntensityScreen_simpViewOffButton = leButtonWidget_New();
    displayIntensityScreen_simpViewOffButton->fn->setPosition(displayIntensityScreen_simpViewOffButton, 340, 120);
    displayIntensityScreen_simpViewOffButton->fn->setSize(displayIntensityScreen_simpViewOffButton, 100, 30);
    displayIntensityScreen_simpViewOffButton->fn->setScheme(displayIntensityScreen_simpViewOffButton, &BlackScheme);
    displayIntensityScreen_simpViewOffButton->fn->setBackgroundType(displayIntensityScreen_simpViewOffButton, LE_WIDGET_BACKGROUND_NONE);
    displayIntensityScreen_simpViewOffButton->fn->setBorderType(displayIntensityScreen_simpViewOffButton, LE_WIDGET_BORDER_NONE);
    displayIntensityScreen_simpViewOffButton->fn->setHAlignment(displayIntensityScreen_simpViewOffButton, LE_HALIGN_LEFT);
    displayIntensityScreen_simpViewOffButton->fn->setToggleable(displayIntensityScreen_simpViewOffButton, LE_TRUE);
    displayIntensityScreen_simpViewOffButton->fn->setString(displayIntensityScreen_simpViewOffButton, (leString*)&string_OFFStr);
    displayIntensityScreen_simpViewOffButton->fn->setPressedImage(displayIntensityScreen_simpViewOffButton, (leImage*)&largeSelected);
    displayIntensityScreen_simpViewOffButton->fn->setReleasedImage(displayIntensityScreen_simpViewOffButton, (leImage*)&largeNotSelected);
    displayIntensityScreen_simpViewOffButton->fn->setImageMargin(displayIntensityScreen_simpViewOffButton, 5);
    displayIntensityScreen_simpViewOffButton->fn->setPressedOffset(displayIntensityScreen_simpViewOffButton, 0);
    displayIntensityScreen_simpViewOffButton->fn->setPressedEventCallback(displayIntensityScreen_simpViewOffButton, event_displayIntensityScreen_simpViewOffButton_OnPressed);
    root0->fn->addChild(root0, (leWidget*)displayIntensityScreen_simpViewOffButton);

    displayIntensityScreen_ImageWidget0 = leImageWidget_New();
    displayIntensityScreen_ImageWidget0->fn->setPosition(displayIntensityScreen_ImageWidget0, 340, 205);
    displayIntensityScreen_ImageWidget0->fn->setSize(displayIntensityScreen_ImageWidget0, 110, 50);
    displayIntensityScreen_ImageWidget0->fn->setBorderType(displayIntensityScreen_ImageWidget0, LE_WIDGET_BORDER_NONE);
    displayIntensityScreen_ImageWidget0->fn->setImage(displayIntensityScreen_ImageWidget0, (leImage*)&BackToMenu);
    root0->fn->addChild(root0, (leWidget*)displayIntensityScreen_ImageWidget0);

    displayIntensityScreen_dispExitButton = leButtonWidget_New();
    displayIntensityScreen_dispExitButton->fn->setPosition(displayIntensityScreen_dispExitButton, 1, 2);
    displayIntensityScreen_dispExitButton->fn->setSize(displayIntensityScreen_dispExitButton, 108, 48);
    displayIntensityScreen_dispExitButton->fn->setScheme(displayIntensityScreen_dispExitButton, &BlackScheme);
    displayIntensityScreen_dispExitButton->fn->setBackgroundType(displayIntensityScreen_dispExitButton, LE_WIDGET_BACKGROUND_NONE);
    displayIntensityScreen_dispExitButton->fn->setBorderType(displayIntensityScreen_dispExitButton, LE_WIDGET_BORDER_NONE);
    displayIntensityScreen_dispExitButton->fn->setPressedEventCallback(displayIntensityScreen_dispExitButton, event_displayIntensityScreen_dispExitButton_OnPressed);
    displayIntensityScreen_ImageWidget0->fn->addChild(displayIntensityScreen_ImageWidget0, (leWidget*)displayIntensityScreen_dispExitButton);

    leAddRootWidget(root0, 0);
    leSetLayerColorMode(0, LE_COLOR_MODE_RGB_565);

    displayIntensityScreen_OnShow(); // raise event

    showing = LE_TRUE;

    return LE_SUCCESS;
}

void screenUpdate_displayIntensityScreen(void)
{
    root0->fn->setSize(root0, root0->rect.width, root0->rect.height);
}

void screenHide_displayIntensityScreen(void)
{
    displayIntensityScreen_OnHide(); // raise event


    leRemoveRootWidget(root0, 0);
    leWidget_Delete(root0);
    root0 = NULL;

    displayIntensityScreen_PanelWidget0 = NULL;
    displayIntensityScreen_RectangleWidget0 = NULL;
    displayIntensityScreen_RectangleWidget1 = NULL;
    displayIntensityScreen_dispIntensHeader = NULL;
    displayIntensityScreen_disp100Button = NULL;
    displayIntensityScreen_disp75Button = NULL;
    displayIntensityScreen_disp50Button = NULL;
    displayIntensityScreen_disp25Button = NULL;
    displayIntensityScreen_dispDimButton = NULL;
    displayIntensityScreen_dispOffButton = NULL;
    displayIntensityScreen_LabelWidget0 = NULL;
    displayIntensityScreen_LabelWidget1 = NULL;
    displayIntensityScreen_simpleViewOnButton = NULL;
    displayIntensityScreen_simpViewOffButton = NULL;
    displayIntensityScreen_ImageWidget0 = NULL;
    displayIntensityScreen_dispExitButton = NULL;


    showing = LE_FALSE;
}

void screenDestroy_displayIntensityScreen(void)
{
    if(initialized == LE_FALSE)
        return;

    initialized = LE_FALSE;
}

leWidget* screenGetRoot_displayIntensityScreen(uint32_t lyrIdx)
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

