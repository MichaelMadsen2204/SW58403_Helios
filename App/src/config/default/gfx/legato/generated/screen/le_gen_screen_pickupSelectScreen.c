#include "gfx/legato/generated/screen/le_gen_screen_pickupSelectScreen.h"

// screen member widget declarations
static leWidget* root0;

leWidget* pickupSelectScreen_background;
leWidget* pickupSelectScreen_stabilizingPanel;
leRectangleWidget* pickupSelectScreen_pickupSelLineLeft;
leRectangleWidget* pickupSelectScreen_pickupSelLineRight;
leLabelWidget* pickupSelectScreen_pickupSelectHeader;
leImageWidget* pickupSelectScreen_irSourceBackToMenuButImg;
leButtonWidget* pickupSelectScreen_pickupMMBut;
leButtonWidget* pickupSelectScreen_pickupMCBut;
leButtonWidget* pickupSelectScreen_pickupSelBackToMenuBut;
leRectangleWidget* pickupSelectScreen_RectangleWidget_0;
leProgressBarWidget* pickupSelectScreen_ProgressBar;
leLabelWidget* pickupSelectScreen_LabelWidget_0;
leLabelWidget* pickupSelectScreen_LabelWidget_1;

static leBool initialized = LE_FALSE;
static leBool showing = LE_FALSE;

leResult screenInit_pickupSelectScreen(void)
{
    if(initialized == LE_TRUE)
        return LE_FAILURE;

    initialized = LE_TRUE;

    return LE_SUCCESS;
}

leResult screenShow_pickupSelectScreen(void)
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

    pickupSelectScreen_background = leWidget_New();
    pickupSelectScreen_background->fn->setPosition(pickupSelectScreen_background, 0, 0);
    pickupSelectScreen_background->fn->setSize(pickupSelectScreen_background, 480, 272);
    pickupSelectScreen_background->fn->setScheme(pickupSelectScreen_background, &BlackScheme);
    root0->fn->addChild(root0, (leWidget*)pickupSelectScreen_background);

    pickupSelectScreen_pickupSelLineLeft = leRectangleWidget_New();
    pickupSelectScreen_pickupSelLineLeft->fn->setPosition(pickupSelectScreen_pickupSelLineLeft, 26, 25);
    pickupSelectScreen_pickupSelLineLeft->fn->setSize(pickupSelectScreen_pickupSelLineLeft, 117, 3);
    pickupSelectScreen_pickupSelLineLeft->fn->setScheme(pickupSelectScreen_pickupSelLineLeft, &WhiteScheme);
    pickupSelectScreen_pickupSelLineLeft->fn->setBorderType(pickupSelectScreen_pickupSelLineLeft, LE_WIDGET_BORDER_NONE);
    pickupSelectScreen_pickupSelLineLeft->fn->setThickness(pickupSelectScreen_pickupSelLineLeft, 2);
    pickupSelectScreen_background->fn->addChild(pickupSelectScreen_background, (leWidget*)pickupSelectScreen_pickupSelLineLeft);

    pickupSelectScreen_pickupSelLineRight = leRectangleWidget_New();
    pickupSelectScreen_pickupSelLineRight->fn->setPosition(pickupSelectScreen_pickupSelLineRight, 337, 25);
    pickupSelectScreen_pickupSelLineRight->fn->setSize(pickupSelectScreen_pickupSelLineRight, 117, 3);
    pickupSelectScreen_pickupSelLineRight->fn->setScheme(pickupSelectScreen_pickupSelLineRight, &WhiteScheme);
    pickupSelectScreen_pickupSelLineRight->fn->setBorderType(pickupSelectScreen_pickupSelLineRight, LE_WIDGET_BORDER_NONE);
    pickupSelectScreen_pickupSelLineRight->fn->setThickness(pickupSelectScreen_pickupSelLineRight, 2);
    pickupSelectScreen_background->fn->addChild(pickupSelectScreen_background, (leWidget*)pickupSelectScreen_pickupSelLineRight);

    pickupSelectScreen_pickupSelectHeader = leLabelWidget_New();
    pickupSelectScreen_pickupSelectHeader->fn->setPosition(pickupSelectScreen_pickupSelectHeader, 0, 12);
    pickupSelectScreen_pickupSelectHeader->fn->setSize(pickupSelectScreen_pickupSelectHeader, 480, 25);
    pickupSelectScreen_pickupSelectHeader->fn->setScheme(pickupSelectScreen_pickupSelectHeader, &BlackScheme);
    pickupSelectScreen_pickupSelectHeader->fn->setBackgroundType(pickupSelectScreen_pickupSelectHeader, LE_WIDGET_BACKGROUND_NONE);
    pickupSelectScreen_pickupSelectHeader->fn->setHAlignment(pickupSelectScreen_pickupSelectHeader, LE_HALIGN_CENTER);
    pickupSelectScreen_pickupSelectHeader->fn->setString(pickupSelectScreen_pickupSelectHeader, (leString*)&string_pickupSelectHeader);
    pickupSelectScreen_background->fn->addChild(pickupSelectScreen_background, (leWidget*)pickupSelectScreen_pickupSelectHeader);

    pickupSelectScreen_irSourceBackToMenuButImg = leImageWidget_New();
    pickupSelectScreen_irSourceBackToMenuButImg->fn->setPosition(pickupSelectScreen_irSourceBackToMenuButImg, 340, 205);
    pickupSelectScreen_irSourceBackToMenuButImg->fn->setSize(pickupSelectScreen_irSourceBackToMenuButImg, 110, 50);
    pickupSelectScreen_irSourceBackToMenuButImg->fn->setScheme(pickupSelectScreen_irSourceBackToMenuButImg, &BlackScheme);
    pickupSelectScreen_irSourceBackToMenuButImg->fn->setBorderType(pickupSelectScreen_irSourceBackToMenuButImg, LE_WIDGET_BORDER_NONE);
    pickupSelectScreen_irSourceBackToMenuButImg->fn->setImage(pickupSelectScreen_irSourceBackToMenuButImg, (leImage*)&BackToMenu);
    pickupSelectScreen_background->fn->addChild(pickupSelectScreen_background, (leWidget*)pickupSelectScreen_irSourceBackToMenuButImg);

    pickupSelectScreen_pickupSelBackToMenuBut = leButtonWidget_New();
    pickupSelectScreen_pickupSelBackToMenuBut->fn->setPosition(pickupSelectScreen_pickupSelBackToMenuBut, 2, 1);
    pickupSelectScreen_pickupSelBackToMenuBut->fn->setSize(pickupSelectScreen_pickupSelBackToMenuBut, 108, 48);
    pickupSelectScreen_pickupSelBackToMenuBut->fn->setBackgroundType(pickupSelectScreen_pickupSelBackToMenuBut, LE_WIDGET_BACKGROUND_NONE);
    pickupSelectScreen_pickupSelBackToMenuBut->fn->setBorderType(pickupSelectScreen_pickupSelBackToMenuBut, LE_WIDGET_BORDER_NONE);
    pickupSelectScreen_pickupSelBackToMenuBut->fn->setPressedEventCallback(pickupSelectScreen_pickupSelBackToMenuBut, event_pickupSelectScreen_pickupSelBackToMenuBut_OnPressed);
    pickupSelectScreen_irSourceBackToMenuButImg->fn->addChild(pickupSelectScreen_irSourceBackToMenuButImg, (leWidget*)pickupSelectScreen_pickupSelBackToMenuBut);

    pickupSelectScreen_pickupMMBut = leButtonWidget_New();
    pickupSelectScreen_pickupMMBut->fn->setPosition(pickupSelectScreen_pickupMMBut, 169, 75);
    pickupSelectScreen_pickupMMBut->fn->setSize(pickupSelectScreen_pickupMMBut, 150, 42);
    pickupSelectScreen_pickupMMBut->fn->setScheme(pickupSelectScreen_pickupMMBut, &BlackScheme);
    pickupSelectScreen_pickupMMBut->fn->setBorderType(pickupSelectScreen_pickupMMBut, LE_WIDGET_BORDER_NONE);
    pickupSelectScreen_pickupMMBut->fn->setHAlignment(pickupSelectScreen_pickupMMBut, LE_HALIGN_LEFT);
    pickupSelectScreen_pickupMMBut->fn->setVAlignment(pickupSelectScreen_pickupMMBut, LE_VALIGN_TOP);
    pickupSelectScreen_pickupMMBut->fn->setToggleable(pickupSelectScreen_pickupMMBut, LE_TRUE);
    pickupSelectScreen_pickupMMBut->fn->setString(pickupSelectScreen_pickupMMBut, (leString*)&string_pickupSelectMM);
    pickupSelectScreen_pickupMMBut->fn->setPressedImage(pickupSelectScreen_pickupMMBut, (leImage*)&largeSelected);
    pickupSelectScreen_pickupMMBut->fn->setReleasedImage(pickupSelectScreen_pickupMMBut, (leImage*)&largeNotSelected);
    pickupSelectScreen_pickupMMBut->fn->setImageMargin(pickupSelectScreen_pickupMMBut, 5);
    pickupSelectScreen_pickupMMBut->fn->setPressedOffset(pickupSelectScreen_pickupMMBut, 0);
    pickupSelectScreen_pickupMMBut->fn->setPressedEventCallback(pickupSelectScreen_pickupMMBut, event_pickupSelectScreen_pickupMMBut_OnPressed);
    pickupSelectScreen_background->fn->addChild(pickupSelectScreen_background, (leWidget*)pickupSelectScreen_pickupMMBut);

    pickupSelectScreen_pickupMCBut = leButtonWidget_New();
    pickupSelectScreen_pickupMCBut->fn->setPosition(pickupSelectScreen_pickupMCBut, 170, 129);
    pickupSelectScreen_pickupMCBut->fn->setSize(pickupSelectScreen_pickupMCBut, 150, 42);
    pickupSelectScreen_pickupMCBut->fn->setScheme(pickupSelectScreen_pickupMCBut, &BlackScheme);
    pickupSelectScreen_pickupMCBut->fn->setBorderType(pickupSelectScreen_pickupMCBut, LE_WIDGET_BORDER_NONE);
    pickupSelectScreen_pickupMCBut->fn->setHAlignment(pickupSelectScreen_pickupMCBut, LE_HALIGN_LEFT);
    pickupSelectScreen_pickupMCBut->fn->setToggleable(pickupSelectScreen_pickupMCBut, LE_TRUE);
    pickupSelectScreen_pickupMCBut->fn->setString(pickupSelectScreen_pickupMCBut, (leString*)&string_pickupSelectMC);
    pickupSelectScreen_pickupMCBut->fn->setPressedImage(pickupSelectScreen_pickupMCBut, (leImage*)&largeSelected);
    pickupSelectScreen_pickupMCBut->fn->setReleasedImage(pickupSelectScreen_pickupMCBut, (leImage*)&largeNotSelected);
    pickupSelectScreen_pickupMCBut->fn->setImageMargin(pickupSelectScreen_pickupMCBut, 5);
    pickupSelectScreen_pickupMCBut->fn->setPressedOffset(pickupSelectScreen_pickupMCBut, 0);
    pickupSelectScreen_pickupMCBut->fn->setPressedEventCallback(pickupSelectScreen_pickupMCBut, event_pickupSelectScreen_pickupMCBut_OnPressed);
    pickupSelectScreen_background->fn->addChild(pickupSelectScreen_background, (leWidget*)pickupSelectScreen_pickupMCBut);

    pickupSelectScreen_stabilizingPanel = leWidget_New();
    pickupSelectScreen_stabilizingPanel->fn->setPosition(pickupSelectScreen_stabilizingPanel, 119, 69);
    pickupSelectScreen_stabilizingPanel->fn->setSize(pickupSelectScreen_stabilizingPanel, 252, 108);
    pickupSelectScreen_stabilizingPanel->fn->setVisible(pickupSelectScreen_stabilizingPanel, LE_FALSE);
    pickupSelectScreen_stabilizingPanel->fn->setScheme(pickupSelectScreen_stabilizingPanel, &BlackScheme);
    root0->fn->addChild(root0, (leWidget*)pickupSelectScreen_stabilizingPanel);

    pickupSelectScreen_RectangleWidget_0 = leRectangleWidget_New();
    pickupSelectScreen_RectangleWidget_0->fn->setPosition(pickupSelectScreen_RectangleWidget_0, 1, 1);
    pickupSelectScreen_RectangleWidget_0->fn->setSize(pickupSelectScreen_RectangleWidget_0, 240, 101);
    pickupSelectScreen_RectangleWidget_0->fn->setScheme(pickupSelectScreen_RectangleWidget_0, &WhiteScheme);
    pickupSelectScreen_RectangleWidget_0->fn->setBackgroundType(pickupSelectScreen_RectangleWidget_0, LE_WIDGET_BACKGROUND_NONE);
    pickupSelectScreen_RectangleWidget_0->fn->setBorderType(pickupSelectScreen_RectangleWidget_0, LE_WIDGET_BORDER_NONE);
    pickupSelectScreen_RectangleWidget_0->fn->setThickness(pickupSelectScreen_RectangleWidget_0, 2);
    pickupSelectScreen_stabilizingPanel->fn->addChild(pickupSelectScreen_stabilizingPanel, (leWidget*)pickupSelectScreen_RectangleWidget_0);

    pickupSelectScreen_ProgressBar = leProgressBarWidget_New();
    pickupSelectScreen_ProgressBar->fn->setPosition(pickupSelectScreen_ProgressBar, 11, 69);
    pickupSelectScreen_ProgressBar->fn->setSize(pickupSelectScreen_ProgressBar, 220, 25);
    pickupSelectScreen_ProgressBar->fn->setScheme(pickupSelectScreen_ProgressBar, &progressScheme);
    pickupSelectScreen_ProgressBar->fn->setBorderType(pickupSelectScreen_ProgressBar, LE_WIDGET_BORDER_LINE);
    pickupSelectScreen_ProgressBar->fn->setValue(pickupSelectScreen_ProgressBar, 100);
    pickupSelectScreen_stabilizingPanel->fn->addChild(pickupSelectScreen_stabilizingPanel, (leWidget*)pickupSelectScreen_ProgressBar);

    pickupSelectScreen_LabelWidget_0 = leLabelWidget_New();
    pickupSelectScreen_LabelWidget_0->fn->setPosition(pickupSelectScreen_LabelWidget_0, 55, 10);
    pickupSelectScreen_LabelWidget_0->fn->setSize(pickupSelectScreen_LabelWidget_0, 130, 25);
    pickupSelectScreen_LabelWidget_0->fn->setScheme(pickupSelectScreen_LabelWidget_0, &BlackScheme);
    pickupSelectScreen_LabelWidget_0->fn->setHAlignment(pickupSelectScreen_LabelWidget_0, LE_HALIGN_CENTER);
    pickupSelectScreen_LabelWidget_0->fn->setString(pickupSelectScreen_LabelWidget_0, (leString*)&string_pcCircuitSter);
    pickupSelectScreen_stabilizingPanel->fn->addChild(pickupSelectScreen_stabilizingPanel, (leWidget*)pickupSelectScreen_LabelWidget_0);

    pickupSelectScreen_LabelWidget_1 = leLabelWidget_New();
    pickupSelectScreen_LabelWidget_1->fn->setPosition(pickupSelectScreen_LabelWidget_1, 70, 37);
    pickupSelectScreen_LabelWidget_1->fn->setScheme(pickupSelectScreen_LabelWidget_1, &BlackScheme);
    pickupSelectScreen_LabelWidget_1->fn->setBackgroundType(pickupSelectScreen_LabelWidget_1, LE_WIDGET_BACKGROUND_NONE);
    pickupSelectScreen_LabelWidget_1->fn->setHAlignment(pickupSelectScreen_LabelWidget_1, LE_HALIGN_CENTER);
    pickupSelectScreen_LabelWidget_1->fn->setString(pickupSelectScreen_LabelWidget_1, (leString*)&string_stabilizingStr);
    pickupSelectScreen_stabilizingPanel->fn->addChild(pickupSelectScreen_stabilizingPanel, (leWidget*)pickupSelectScreen_LabelWidget_1);

    leAddRootWidget(root0, 0);
    leSetLayerColorMode(0, LE_COLOR_MODE_RGB_565);

    pickupSelectScreen_OnShow(); // raise event

    showing = LE_TRUE;

    return LE_SUCCESS;
}

void screenUpdate_pickupSelectScreen(void)
{
    root0->fn->setSize(root0, root0->rect.width, root0->rect.height);
}

void screenHide_pickupSelectScreen(void)
{

    leRemoveRootWidget(root0, 0);
    leWidget_Delete(root0);
    root0 = NULL;

    pickupSelectScreen_background = NULL;
    pickupSelectScreen_stabilizingPanel = NULL;
    pickupSelectScreen_pickupSelLineLeft = NULL;
    pickupSelectScreen_pickupSelLineRight = NULL;
    pickupSelectScreen_pickupSelectHeader = NULL;
    pickupSelectScreen_irSourceBackToMenuButImg = NULL;
    pickupSelectScreen_pickupMMBut = NULL;
    pickupSelectScreen_pickupMCBut = NULL;
    pickupSelectScreen_pickupSelBackToMenuBut = NULL;
    pickupSelectScreen_RectangleWidget_0 = NULL;
    pickupSelectScreen_ProgressBar = NULL;
    pickupSelectScreen_LabelWidget_0 = NULL;
    pickupSelectScreen_LabelWidget_1 = NULL;


    showing = LE_FALSE;
}

void screenDestroy_pickupSelectScreen(void)
{
    if(initialized == LE_FALSE)
        return;

    initialized = LE_FALSE;
}

leWidget* screenGetRoot_pickupSelectScreen(uint32_t lyrIdx)
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

