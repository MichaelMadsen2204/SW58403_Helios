#include "gfx/legato/generated/screen/le_gen_screen_irSourceScreen.h"

// screen member widget declarations
static leWidget* root0;

leWidget* irSourceScreen_background;
leRectangleWidget* irSourceScreen_irSourceLineLeft;
leRectangleWidget* irSourceScreen_irSourceLineRight;
leLabelWidget* irSourceScreen_irSourceHeader;
leImageWidget* irSourceScreen_irSourceBackToMenuButImg;
leButtonWidget* irSourceScreen_irSourceFrontBut;
leButtonWidget* irSourceScreen_irSourceBackBut;
leButtonWidget* irSourceScreen_irSourceBackToMenuBut;

static leBool initialized = LE_FALSE;
static leBool showing = LE_FALSE;

leResult screenInit_irSourceScreen(void)
{
    if(initialized == LE_TRUE)
        return LE_FAILURE;

    initialized = LE_TRUE;

    return LE_SUCCESS;
}

leResult screenShow_irSourceScreen(void)
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

    irSourceScreen_background = leWidget_New();
    irSourceScreen_background->fn->setPosition(irSourceScreen_background, 0, 0);
    irSourceScreen_background->fn->setSize(irSourceScreen_background, 480, 272);
    irSourceScreen_background->fn->setScheme(irSourceScreen_background, &BlackScheme);
    root0->fn->addChild(root0, (leWidget*)irSourceScreen_background);

    irSourceScreen_irSourceLineLeft = leRectangleWidget_New();
    irSourceScreen_irSourceLineLeft->fn->setPosition(irSourceScreen_irSourceLineLeft, 26, 25);
    irSourceScreen_irSourceLineLeft->fn->setSize(irSourceScreen_irSourceLineLeft, 155, 3);
    irSourceScreen_irSourceLineLeft->fn->setScheme(irSourceScreen_irSourceLineLeft, &WhiteScheme);
    irSourceScreen_irSourceLineLeft->fn->setBorderType(irSourceScreen_irSourceLineLeft, LE_WIDGET_BORDER_NONE);
    irSourceScreen_irSourceLineLeft->fn->setThickness(irSourceScreen_irSourceLineLeft, 2);
    irSourceScreen_background->fn->addChild(irSourceScreen_background, (leWidget*)irSourceScreen_irSourceLineLeft);

    irSourceScreen_irSourceLineRight = leRectangleWidget_New();
    irSourceScreen_irSourceLineRight->fn->setPosition(irSourceScreen_irSourceLineRight, 299, 25);
    irSourceScreen_irSourceLineRight->fn->setSize(irSourceScreen_irSourceLineRight, 155, 3);
    irSourceScreen_irSourceLineRight->fn->setScheme(irSourceScreen_irSourceLineRight, &WhiteScheme);
    irSourceScreen_irSourceLineRight->fn->setBorderType(irSourceScreen_irSourceLineRight, LE_WIDGET_BORDER_NONE);
    irSourceScreen_irSourceLineRight->fn->setThickness(irSourceScreen_irSourceLineRight, 2);
    irSourceScreen_background->fn->addChild(irSourceScreen_background, (leWidget*)irSourceScreen_irSourceLineRight);

    irSourceScreen_irSourceHeader = leLabelWidget_New();
    irSourceScreen_irSourceHeader->fn->setPosition(irSourceScreen_irSourceHeader, 0, 12);
    irSourceScreen_irSourceHeader->fn->setSize(irSourceScreen_irSourceHeader, 480, 25);
    irSourceScreen_irSourceHeader->fn->setScheme(irSourceScreen_irSourceHeader, &BlackScheme);
    irSourceScreen_irSourceHeader->fn->setBackgroundType(irSourceScreen_irSourceHeader, LE_WIDGET_BACKGROUND_NONE);
    irSourceScreen_irSourceHeader->fn->setHAlignment(irSourceScreen_irSourceHeader, LE_HALIGN_CENTER);
    irSourceScreen_irSourceHeader->fn->setString(irSourceScreen_irSourceHeader, (leString*)&string_irSourceHeaderStr);
    irSourceScreen_background->fn->addChild(irSourceScreen_background, (leWidget*)irSourceScreen_irSourceHeader);

    irSourceScreen_irSourceBackToMenuButImg = leImageWidget_New();
    irSourceScreen_irSourceBackToMenuButImg->fn->setPosition(irSourceScreen_irSourceBackToMenuButImg, 340, 205);
    irSourceScreen_irSourceBackToMenuButImg->fn->setSize(irSourceScreen_irSourceBackToMenuButImg, 110, 50);
    irSourceScreen_irSourceBackToMenuButImg->fn->setScheme(irSourceScreen_irSourceBackToMenuButImg, &BlackScheme);
    irSourceScreen_irSourceBackToMenuButImg->fn->setBorderType(irSourceScreen_irSourceBackToMenuButImg, LE_WIDGET_BORDER_NONE);
    irSourceScreen_irSourceBackToMenuButImg->fn->setImage(irSourceScreen_irSourceBackToMenuButImg, (leImage*)&BackToMenu);
    irSourceScreen_background->fn->addChild(irSourceScreen_background, (leWidget*)irSourceScreen_irSourceBackToMenuButImg);

    irSourceScreen_irSourceBackToMenuBut = leButtonWidget_New();
    irSourceScreen_irSourceBackToMenuBut->fn->setPosition(irSourceScreen_irSourceBackToMenuBut, 2, 1);
    irSourceScreen_irSourceBackToMenuBut->fn->setSize(irSourceScreen_irSourceBackToMenuBut, 108, 48);
    irSourceScreen_irSourceBackToMenuBut->fn->setBackgroundType(irSourceScreen_irSourceBackToMenuBut, LE_WIDGET_BACKGROUND_NONE);
    irSourceScreen_irSourceBackToMenuBut->fn->setBorderType(irSourceScreen_irSourceBackToMenuBut, LE_WIDGET_BORDER_NONE);
    irSourceScreen_irSourceBackToMenuBut->fn->setPressedEventCallback(irSourceScreen_irSourceBackToMenuBut, event_irSourceScreen_irSourceBackToMenuBut_OnPressed);
    irSourceScreen_irSourceBackToMenuButImg->fn->addChild(irSourceScreen_irSourceBackToMenuButImg, (leWidget*)irSourceScreen_irSourceBackToMenuBut);

    irSourceScreen_irSourceFrontBut = leButtonWidget_New();
    irSourceScreen_irSourceFrontBut->fn->setPosition(irSourceScreen_irSourceFrontBut, 100, 76);
    irSourceScreen_irSourceFrontBut->fn->setSize(irSourceScreen_irSourceFrontBut, 340, 42);
    irSourceScreen_irSourceFrontBut->fn->setScheme(irSourceScreen_irSourceFrontBut, &BlackScheme);
    irSourceScreen_irSourceFrontBut->fn->setBorderType(irSourceScreen_irSourceFrontBut, LE_WIDGET_BORDER_NONE);
    irSourceScreen_irSourceFrontBut->fn->setHAlignment(irSourceScreen_irSourceFrontBut, LE_HALIGN_LEFT);
    irSourceScreen_irSourceFrontBut->fn->setVAlignment(irSourceScreen_irSourceFrontBut, LE_VALIGN_TOP);
    irSourceScreen_irSourceFrontBut->fn->setToggleable(irSourceScreen_irSourceFrontBut, LE_TRUE);
    irSourceScreen_irSourceFrontBut->fn->setString(irSourceScreen_irSourceFrontBut, (leString*)&string_irSourceFrontStr);
    irSourceScreen_irSourceFrontBut->fn->setPressedImage(irSourceScreen_irSourceFrontBut, (leImage*)&largeSelected);
    irSourceScreen_irSourceFrontBut->fn->setReleasedImage(irSourceScreen_irSourceFrontBut, (leImage*)&largeNotSelected);
    irSourceScreen_irSourceFrontBut->fn->setImageMargin(irSourceScreen_irSourceFrontBut, 5);
    irSourceScreen_irSourceFrontBut->fn->setPressedOffset(irSourceScreen_irSourceFrontBut, 0);
    irSourceScreen_irSourceFrontBut->fn->setPressedEventCallback(irSourceScreen_irSourceFrontBut, event_irSourceScreen_irSourceFrontBut_OnPressed);
    irSourceScreen_background->fn->addChild(irSourceScreen_background, (leWidget*)irSourceScreen_irSourceFrontBut);

    irSourceScreen_irSourceBackBut = leButtonWidget_New();
    irSourceScreen_irSourceBackBut->fn->setPosition(irSourceScreen_irSourceBackBut, 100, 129);
    irSourceScreen_irSourceBackBut->fn->setSize(irSourceScreen_irSourceBackBut, 340, 42);
    irSourceScreen_irSourceBackBut->fn->setScheme(irSourceScreen_irSourceBackBut, &BlackScheme);
    irSourceScreen_irSourceBackBut->fn->setBorderType(irSourceScreen_irSourceBackBut, LE_WIDGET_BORDER_NONE);
    irSourceScreen_irSourceBackBut->fn->setHAlignment(irSourceScreen_irSourceBackBut, LE_HALIGN_LEFT);
    irSourceScreen_irSourceBackBut->fn->setVAlignment(irSourceScreen_irSourceBackBut, LE_VALIGN_TOP);
    irSourceScreen_irSourceBackBut->fn->setToggleable(irSourceScreen_irSourceBackBut, LE_TRUE);
    irSourceScreen_irSourceBackBut->fn->setString(irSourceScreen_irSourceBackBut, (leString*)&string_irSourceBackPanelStr);
    irSourceScreen_irSourceBackBut->fn->setPressedImage(irSourceScreen_irSourceBackBut, (leImage*)&largeSelected);
    irSourceScreen_irSourceBackBut->fn->setReleasedImage(irSourceScreen_irSourceBackBut, (leImage*)&largeNotSelected);
    irSourceScreen_irSourceBackBut->fn->setImageMargin(irSourceScreen_irSourceBackBut, 5);
    irSourceScreen_irSourceBackBut->fn->setPressedOffset(irSourceScreen_irSourceBackBut, 0);
    irSourceScreen_irSourceBackBut->fn->setPressedEventCallback(irSourceScreen_irSourceBackBut, event_irSourceScreen_irSourceBackBut_OnPressed);
    irSourceScreen_background->fn->addChild(irSourceScreen_background, (leWidget*)irSourceScreen_irSourceBackBut);

    leAddRootWidget(root0, 0);
    leSetLayerColorMode(0, LE_COLOR_MODE_RGB_565);

    irSourceScreen_OnShow(); // raise event

    showing = LE_TRUE;

    return LE_SUCCESS;
}

void screenUpdate_irSourceScreen(void)
{
    root0->fn->setSize(root0, root0->rect.width, root0->rect.height);
}

void screenHide_irSourceScreen(void)
{

    leRemoveRootWidget(root0, 0);
    leWidget_Delete(root0);
    root0 = NULL;

    irSourceScreen_background = NULL;
    irSourceScreen_irSourceLineLeft = NULL;
    irSourceScreen_irSourceLineRight = NULL;
    irSourceScreen_irSourceHeader = NULL;
    irSourceScreen_irSourceBackToMenuButImg = NULL;
    irSourceScreen_irSourceFrontBut = NULL;
    irSourceScreen_irSourceBackBut = NULL;
    irSourceScreen_irSourceBackToMenuBut = NULL;


    showing = LE_FALSE;
}

void screenDestroy_irSourceScreen(void)
{
    if(initialized == LE_FALSE)
        return;

    initialized = LE_FALSE;
}

leWidget* screenGetRoot_irSourceScreen(uint32_t lyrIdx)
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

