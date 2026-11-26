#include "gfx/legato/generated/screen/le_gen_screen_greenBiasScreen.h"

// screen member widget declarations
static leWidget* root0;

leWidget* greenBiasScreen_background;
leLabelWidget* greenBiasScreen_Instruction;
leLabelWidget* greenBiasScreen_Setting1M;
leLabelWidget* greenBiasScreen_Setting1H;
leLabelWidget* greenBiasScreen_Setting2M;
leLabelWidget* greenBiasScreen_Setting2H;
leRectangleWidget* greenBiasScreen_irSourceLineLeft;
leRectangleWidget* greenBiasScreen_irSourceLineRight;
leLabelWidget* greenBiasScreen_greenBiasHeader;
leImageWidget* greenBiasScreen_irSourceBackToMenuButImg;
leButtonWidget* greenBiasScreen_BIAS_SETTING1;
leButtonWidget* greenBiasScreen_BIAS_SETTING2;
leButtonWidget* greenBiasScreen_GreenBiasBackToMenuBut;

static leBool initialized = LE_FALSE;
static leBool showing = LE_FALSE;

leResult screenInit_greenBiasScreen(void)
{
    if(initialized == LE_TRUE)
        return LE_FAILURE;

    initialized = LE_TRUE;

    return LE_SUCCESS;
}

leResult screenShow_greenBiasScreen(void)
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

    greenBiasScreen_background = leWidget_New();
    greenBiasScreen_background->fn->setPosition(greenBiasScreen_background, 0, 0);
    greenBiasScreen_background->fn->setSize(greenBiasScreen_background, 480, 272);
    greenBiasScreen_background->fn->setScheme(greenBiasScreen_background, &BlackScheme);
    root0->fn->addChild(root0, (leWidget*)greenBiasScreen_background);

    greenBiasScreen_irSourceLineLeft = leRectangleWidget_New();
    greenBiasScreen_irSourceLineLeft->fn->setPosition(greenBiasScreen_irSourceLineLeft, 26, 25);
    greenBiasScreen_irSourceLineLeft->fn->setSize(greenBiasScreen_irSourceLineLeft, 150, 3);
    greenBiasScreen_irSourceLineLeft->fn->setScheme(greenBiasScreen_irSourceLineLeft, &WhiteScheme);
    greenBiasScreen_irSourceLineLeft->fn->setBorderType(greenBiasScreen_irSourceLineLeft, LE_WIDGET_BORDER_NONE);
    greenBiasScreen_irSourceLineLeft->fn->setThickness(greenBiasScreen_irSourceLineLeft, 2);
    greenBiasScreen_background->fn->addChild(greenBiasScreen_background, (leWidget*)greenBiasScreen_irSourceLineLeft);

    greenBiasScreen_irSourceLineRight = leRectangleWidget_New();
    greenBiasScreen_irSourceLineRight->fn->setPosition(greenBiasScreen_irSourceLineRight, 304, 25);
    greenBiasScreen_irSourceLineRight->fn->setSize(greenBiasScreen_irSourceLineRight, 150, 3);
    greenBiasScreen_irSourceLineRight->fn->setScheme(greenBiasScreen_irSourceLineRight, &WhiteScheme);
    greenBiasScreen_irSourceLineRight->fn->setBorderType(greenBiasScreen_irSourceLineRight, LE_WIDGET_BORDER_NONE);
    greenBiasScreen_irSourceLineRight->fn->setThickness(greenBiasScreen_irSourceLineRight, 2);
    greenBiasScreen_background->fn->addChild(greenBiasScreen_background, (leWidget*)greenBiasScreen_irSourceLineRight);

    greenBiasScreen_greenBiasHeader = leLabelWidget_New();
    greenBiasScreen_greenBiasHeader->fn->setPosition(greenBiasScreen_greenBiasHeader, 0, 12);
    greenBiasScreen_greenBiasHeader->fn->setSize(greenBiasScreen_greenBiasHeader, 480, 25);
    greenBiasScreen_greenBiasHeader->fn->setScheme(greenBiasScreen_greenBiasHeader, &BlackScheme);
    greenBiasScreen_greenBiasHeader->fn->setBackgroundType(greenBiasScreen_greenBiasHeader, LE_WIDGET_BACKGROUND_NONE);
    greenBiasScreen_greenBiasHeader->fn->setHAlignment(greenBiasScreen_greenBiasHeader, LE_HALIGN_CENTER);
    greenBiasScreen_greenBiasHeader->fn->setString(greenBiasScreen_greenBiasHeader, (leString*)&string_menuGreenBiasStr);
    greenBiasScreen_background->fn->addChild(greenBiasScreen_background, (leWidget*)greenBiasScreen_greenBiasHeader);

    greenBiasScreen_irSourceBackToMenuButImg = leImageWidget_New();
    greenBiasScreen_irSourceBackToMenuButImg->fn->setPosition(greenBiasScreen_irSourceBackToMenuButImg, 340, 205);
    greenBiasScreen_irSourceBackToMenuButImg->fn->setSize(greenBiasScreen_irSourceBackToMenuButImg, 110, 50);
    greenBiasScreen_irSourceBackToMenuButImg->fn->setScheme(greenBiasScreen_irSourceBackToMenuButImg, &BlackScheme);
    greenBiasScreen_irSourceBackToMenuButImg->fn->setBorderType(greenBiasScreen_irSourceBackToMenuButImg, LE_WIDGET_BORDER_NONE);
    greenBiasScreen_irSourceBackToMenuButImg->fn->setImage(greenBiasScreen_irSourceBackToMenuButImg, (leImage*)&BackToMenu);
    greenBiasScreen_background->fn->addChild(greenBiasScreen_background, (leWidget*)greenBiasScreen_irSourceBackToMenuButImg);

    greenBiasScreen_GreenBiasBackToMenuBut = leButtonWidget_New();
    greenBiasScreen_GreenBiasBackToMenuBut->fn->setPosition(greenBiasScreen_GreenBiasBackToMenuBut, 2, 1);
    greenBiasScreen_GreenBiasBackToMenuBut->fn->setSize(greenBiasScreen_GreenBiasBackToMenuBut, 108, 48);
    greenBiasScreen_GreenBiasBackToMenuBut->fn->setBackgroundType(greenBiasScreen_GreenBiasBackToMenuBut, LE_WIDGET_BACKGROUND_NONE);
    greenBiasScreen_GreenBiasBackToMenuBut->fn->setBorderType(greenBiasScreen_GreenBiasBackToMenuBut, LE_WIDGET_BORDER_NONE);
    greenBiasScreen_GreenBiasBackToMenuBut->fn->setPressedEventCallback(greenBiasScreen_GreenBiasBackToMenuBut, event_greenBiasScreen_GreenBiasBackToMenuBut_OnPressed);
    greenBiasScreen_irSourceBackToMenuButImg->fn->addChild(greenBiasScreen_irSourceBackToMenuButImg, (leWidget*)greenBiasScreen_GreenBiasBackToMenuBut);

    greenBiasScreen_BIAS_SETTING1 = leButtonWidget_New();
    greenBiasScreen_BIAS_SETTING1->fn->setPosition(greenBiasScreen_BIAS_SETTING1, 125, 85);
    greenBiasScreen_BIAS_SETTING1->fn->setSize(greenBiasScreen_BIAS_SETTING1, 39, 42);
    greenBiasScreen_BIAS_SETTING1->fn->setScheme(greenBiasScreen_BIAS_SETTING1, &BlackScheme);
    greenBiasScreen_BIAS_SETTING1->fn->setBorderType(greenBiasScreen_BIAS_SETTING1, LE_WIDGET_BORDER_NONE);
    greenBiasScreen_BIAS_SETTING1->fn->setHAlignment(greenBiasScreen_BIAS_SETTING1, LE_HALIGN_LEFT);
    greenBiasScreen_BIAS_SETTING1->fn->setVAlignment(greenBiasScreen_BIAS_SETTING1, LE_VALIGN_TOP);
    greenBiasScreen_BIAS_SETTING1->fn->setToggleable(greenBiasScreen_BIAS_SETTING1, LE_TRUE);
    greenBiasScreen_BIAS_SETTING1->fn->setPressedImage(greenBiasScreen_BIAS_SETTING1, (leImage*)&largeSelected);
    greenBiasScreen_BIAS_SETTING1->fn->setReleasedImage(greenBiasScreen_BIAS_SETTING1, (leImage*)&largeNotSelected);
    greenBiasScreen_BIAS_SETTING1->fn->setImageMargin(greenBiasScreen_BIAS_SETTING1, 5);
    greenBiasScreen_BIAS_SETTING1->fn->setPressedOffset(greenBiasScreen_BIAS_SETTING1, 0);
    greenBiasScreen_BIAS_SETTING1->fn->setPressedEventCallback(greenBiasScreen_BIAS_SETTING1, event_greenBiasScreen_BIAS_SETTING1_OnPressed);
    greenBiasScreen_background->fn->addChild(greenBiasScreen_background, (leWidget*)greenBiasScreen_BIAS_SETTING1);

    greenBiasScreen_BIAS_SETTING2 = leButtonWidget_New();
    greenBiasScreen_BIAS_SETTING2->fn->setPosition(greenBiasScreen_BIAS_SETTING2, 322, 85);
    greenBiasScreen_BIAS_SETTING2->fn->setSize(greenBiasScreen_BIAS_SETTING2, 38, 42);
    greenBiasScreen_BIAS_SETTING2->fn->setScheme(greenBiasScreen_BIAS_SETTING2, &BlackScheme);
    greenBiasScreen_BIAS_SETTING2->fn->setBorderType(greenBiasScreen_BIAS_SETTING2, LE_WIDGET_BORDER_NONE);
    greenBiasScreen_BIAS_SETTING2->fn->setHAlignment(greenBiasScreen_BIAS_SETTING2, LE_HALIGN_LEFT);
    greenBiasScreen_BIAS_SETTING2->fn->setVAlignment(greenBiasScreen_BIAS_SETTING2, LE_VALIGN_TOP);
    greenBiasScreen_BIAS_SETTING2->fn->setToggleable(greenBiasScreen_BIAS_SETTING2, LE_TRUE);
    greenBiasScreen_BIAS_SETTING2->fn->setPressedImage(greenBiasScreen_BIAS_SETTING2, (leImage*)&largeSelected);
    greenBiasScreen_BIAS_SETTING2->fn->setReleasedImage(greenBiasScreen_BIAS_SETTING2, (leImage*)&largeNotSelected);
    greenBiasScreen_BIAS_SETTING2->fn->setImageMargin(greenBiasScreen_BIAS_SETTING2, 5);
    greenBiasScreen_BIAS_SETTING2->fn->setPressedOffset(greenBiasScreen_BIAS_SETTING2, 0);
    greenBiasScreen_BIAS_SETTING2->fn->setPressedEventCallback(greenBiasScreen_BIAS_SETTING2, event_greenBiasScreen_BIAS_SETTING2_OnPressed);
    greenBiasScreen_background->fn->addChild(greenBiasScreen_background, (leWidget*)greenBiasScreen_BIAS_SETTING2);

    greenBiasScreen_Instruction = leLabelWidget_New();
    greenBiasScreen_Instruction->fn->setPosition(greenBiasScreen_Instruction, 0, 50);
    greenBiasScreen_Instruction->fn->setSize(greenBiasScreen_Instruction, 480, 25);
    greenBiasScreen_Instruction->fn->setScheme(greenBiasScreen_Instruction, &BlackScheme);
    greenBiasScreen_Instruction->fn->setBackgroundType(greenBiasScreen_Instruction, LE_WIDGET_BACKGROUND_NONE);
    greenBiasScreen_Instruction->fn->setHAlignment(greenBiasScreen_Instruction, LE_HALIGN_CENTER);
    greenBiasScreen_Instruction->fn->setString(greenBiasScreen_Instruction, (leString*)&string_GB_Setting_Instruction);
    root0->fn->addChild(root0, (leWidget*)greenBiasScreen_Instruction);

    greenBiasScreen_Setting1M = leLabelWidget_New();
    greenBiasScreen_Setting1M->fn->setPosition(greenBiasScreen_Setting1M, 45, 130);
    greenBiasScreen_Setting1M->fn->setSize(greenBiasScreen_Setting1M, 200, 25);
    greenBiasScreen_Setting1M->fn->setScheme(greenBiasScreen_Setting1M, &BlackScheme);
    greenBiasScreen_Setting1M->fn->setBackgroundType(greenBiasScreen_Setting1M, LE_WIDGET_BACKGROUND_NONE);
    greenBiasScreen_Setting1M->fn->setHAlignment(greenBiasScreen_Setting1M, LE_HALIGN_CENTER);
    greenBiasScreen_Setting1M->fn->setString(greenBiasScreen_Setting1M, (leString*)&string_BIAS_SETTING_1M);
    root0->fn->addChild(root0, (leWidget*)greenBiasScreen_Setting1M);

    greenBiasScreen_Setting1H = leLabelWidget_New();
    greenBiasScreen_Setting1H->fn->setPosition(greenBiasScreen_Setting1H, 45, 160);
    greenBiasScreen_Setting1H->fn->setSize(greenBiasScreen_Setting1H, 200, 25);
    greenBiasScreen_Setting1H->fn->setScheme(greenBiasScreen_Setting1H, &BlackScheme);
    greenBiasScreen_Setting1H->fn->setBackgroundType(greenBiasScreen_Setting1H, LE_WIDGET_BACKGROUND_NONE);
    greenBiasScreen_Setting1H->fn->setHAlignment(greenBiasScreen_Setting1H, LE_HALIGN_CENTER);
    greenBiasScreen_Setting1H->fn->setString(greenBiasScreen_Setting1H, (leString*)&string_BIAS_SETTING_1H);
    root0->fn->addChild(root0, (leWidget*)greenBiasScreen_Setting1H);

    greenBiasScreen_Setting2M = leLabelWidget_New();
    greenBiasScreen_Setting2M->fn->setPosition(greenBiasScreen_Setting2M, 242, 130);
    greenBiasScreen_Setting2M->fn->setSize(greenBiasScreen_Setting2M, 200, 25);
    greenBiasScreen_Setting2M->fn->setScheme(greenBiasScreen_Setting2M, &BlackScheme);
    greenBiasScreen_Setting2M->fn->setBackgroundType(greenBiasScreen_Setting2M, LE_WIDGET_BACKGROUND_NONE);
    greenBiasScreen_Setting2M->fn->setHAlignment(greenBiasScreen_Setting2M, LE_HALIGN_CENTER);
    greenBiasScreen_Setting2M->fn->setString(greenBiasScreen_Setting2M, (leString*)&string_BIAS_SETTING_2M);
    root0->fn->addChild(root0, (leWidget*)greenBiasScreen_Setting2M);

    greenBiasScreen_Setting2H = leLabelWidget_New();
    greenBiasScreen_Setting2H->fn->setPosition(greenBiasScreen_Setting2H, 242, 160);
    greenBiasScreen_Setting2H->fn->setSize(greenBiasScreen_Setting2H, 200, 25);
    greenBiasScreen_Setting2H->fn->setScheme(greenBiasScreen_Setting2H, &BlackScheme);
    greenBiasScreen_Setting2H->fn->setBackgroundType(greenBiasScreen_Setting2H, LE_WIDGET_BACKGROUND_NONE);
    greenBiasScreen_Setting2H->fn->setHAlignment(greenBiasScreen_Setting2H, LE_HALIGN_CENTER);
    greenBiasScreen_Setting2H->fn->setString(greenBiasScreen_Setting2H, (leString*)&string_BIAS_SETTING_2H);
    root0->fn->addChild(root0, (leWidget*)greenBiasScreen_Setting2H);

    leAddRootWidget(root0, 0);
    leSetLayerColorMode(0, LE_COLOR_MODE_RGB_565);

    greenBiasScreen_OnShow(); // raise event

    showing = LE_TRUE;

    return LE_SUCCESS;
}

void screenUpdate_greenBiasScreen(void)
{
    root0->fn->setSize(root0, root0->rect.width, root0->rect.height);
}

void screenHide_greenBiasScreen(void)
{

    leRemoveRootWidget(root0, 0);
    leWidget_Delete(root0);
    root0 = NULL;

    greenBiasScreen_background = NULL;
    greenBiasScreen_Instruction = NULL;
    greenBiasScreen_Setting1M = NULL;
    greenBiasScreen_Setting1H = NULL;
    greenBiasScreen_Setting2M = NULL;
    greenBiasScreen_Setting2H = NULL;
    greenBiasScreen_irSourceLineLeft = NULL;
    greenBiasScreen_irSourceLineRight = NULL;
    greenBiasScreen_greenBiasHeader = NULL;
    greenBiasScreen_irSourceBackToMenuButImg = NULL;
    greenBiasScreen_BIAS_SETTING1 = NULL;
    greenBiasScreen_BIAS_SETTING2 = NULL;
    greenBiasScreen_GreenBiasBackToMenuBut = NULL;


    showing = LE_FALSE;
}

void screenDestroy_greenBiasScreen(void)
{
    if(initialized == LE_FALSE)
        return;

    initialized = LE_FALSE;
}

leWidget* screenGetRoot_greenBiasScreen(uint32_t lyrIdx)
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

