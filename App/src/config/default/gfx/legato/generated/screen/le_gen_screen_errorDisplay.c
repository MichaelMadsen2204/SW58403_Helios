#include "gfx/legato/generated/screen/le_gen_screen_errorDisplay.h"

// screen member widget declarations
static leWidget* root0;

leWidget* errorDisplay_PanelWidget0;
leLabelWidget* errorDisplay_LabelWidget0;
leLabelWidget* errorDisplay_LabelWidget1;
leLabelWidget* errorDisplay_LabelWidget2;
leLabelWidget* errorDisplay_LabelWidget3;
leLabelWidget* errorDisplay_LabelWidget4;
leLabelWidget* errorDisplay_rightTempLed;
leLabelWidget* errorDisplay_LabelWidget6;
leLabelWidget* errorDisplay_LabelWidget7;
leButtonWidget* errorDisplay_leftTempLed;
leButtonWidget* errorDisplay_leftDcHfLed;
leButtonWidget* errorDisplay_rightTempLed_;
leButtonWidget* errorDisplay_rightDcHfLed;
leLabelWidget* errorDisplay_LabelWidget8;
leLabelWidget* errorDisplay_LabelWidget_0;

static leBool initialized = LE_FALSE;
static leBool showing = LE_FALSE;

leResult screenInit_errorDisplay(void)
{
    if(initialized == LE_TRUE)
        return LE_FAILURE;

    initialized = LE_TRUE;

    return LE_SUCCESS;
}

leResult screenShow_errorDisplay(void)
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

    errorDisplay_PanelWidget0 = leWidget_New();
    errorDisplay_PanelWidget0->fn->setPosition(errorDisplay_PanelWidget0, 0, 0);
    errorDisplay_PanelWidget0->fn->setSize(errorDisplay_PanelWidget0, 480, 272);
    errorDisplay_PanelWidget0->fn->setScheme(errorDisplay_PanelWidget0, &BlackScheme);
    root0->fn->addChild(root0, (leWidget*)errorDisplay_PanelWidget0);

    errorDisplay_LabelWidget0 = leLabelWidget_New();
    errorDisplay_LabelWidget0->fn->setPosition(errorDisplay_LabelWidget0, 58, 55);
    errorDisplay_LabelWidget0->fn->setScheme(errorDisplay_LabelWidget0, &BlackScheme);
    errorDisplay_LabelWidget0->fn->setBackgroundType(errorDisplay_LabelWidget0, LE_WIDGET_BACKGROUND_NONE);
    errorDisplay_LabelWidget0->fn->setHAlignment(errorDisplay_LabelWidget0, LE_HALIGN_CENTER);
    errorDisplay_LabelWidget0->fn->setString(errorDisplay_LabelWidget0, (leString*)&string_Left);
    root0->fn->addChild(root0, (leWidget*)errorDisplay_LabelWidget0);

    errorDisplay_LabelWidget1 = leLabelWidget_New();
    errorDisplay_LabelWidget1->fn->setPosition(errorDisplay_LabelWidget1, 36, 80);
    errorDisplay_LabelWidget1->fn->setSize(errorDisplay_LabelWidget1, 145, 25);
    errorDisplay_LabelWidget1->fn->setScheme(errorDisplay_LabelWidget1, &BlackScheme);
    errorDisplay_LabelWidget1->fn->setBackgroundType(errorDisplay_LabelWidget1, LE_WIDGET_BACKGROUND_NONE);
    errorDisplay_LabelWidget1->fn->setHAlignment(errorDisplay_LabelWidget1, LE_HALIGN_CENTER);
    errorDisplay_LabelWidget1->fn->setString(errorDisplay_LabelWidget1, (leString*)&string_Temp);
    root0->fn->addChild(root0, (leWidget*)errorDisplay_LabelWidget1);

    errorDisplay_LabelWidget2 = leLabelWidget_New();
    errorDisplay_LabelWidget2->fn->setPosition(errorDisplay_LabelWidget2, 58, 150);
    errorDisplay_LabelWidget2->fn->setScheme(errorDisplay_LabelWidget2, &BlackScheme);
    errorDisplay_LabelWidget2->fn->setHAlignment(errorDisplay_LabelWidget2, LE_HALIGN_CENTER);
    errorDisplay_LabelWidget2->fn->setString(errorDisplay_LabelWidget2, (leString*)&string_Left);
    root0->fn->addChild(root0, (leWidget*)errorDisplay_LabelWidget2);

    errorDisplay_LabelWidget3 = leLabelWidget_New();
    errorDisplay_LabelWidget3->fn->setPosition(errorDisplay_LabelWidget3, 58, 175);
    errorDisplay_LabelWidget3->fn->setScheme(errorDisplay_LabelWidget3, &BlackScheme);
    errorDisplay_LabelWidget3->fn->setHAlignment(errorDisplay_LabelWidget3, LE_HALIGN_CENTER);
    errorDisplay_LabelWidget3->fn->setString(errorDisplay_LabelWidget3, (leString*)&string_DcHf);
    root0->fn->addChild(root0, (leWidget*)errorDisplay_LabelWidget3);

    errorDisplay_LabelWidget4 = leLabelWidget_New();
    errorDisplay_LabelWidget4->fn->setPosition(errorDisplay_LabelWidget4, 329, 55);
    errorDisplay_LabelWidget4->fn->setScheme(errorDisplay_LabelWidget4, &BlackScheme);
    errorDisplay_LabelWidget4->fn->setBackgroundType(errorDisplay_LabelWidget4, LE_WIDGET_BACKGROUND_NONE);
    errorDisplay_LabelWidget4->fn->setHAlignment(errorDisplay_LabelWidget4, LE_HALIGN_CENTER);
    errorDisplay_LabelWidget4->fn->setString(errorDisplay_LabelWidget4, (leString*)&string_Right);
    root0->fn->addChild(root0, (leWidget*)errorDisplay_LabelWidget4);

    errorDisplay_rightTempLed = leLabelWidget_New();
    errorDisplay_rightTempLed->fn->setPosition(errorDisplay_rightTempLed, 311, 80);
    errorDisplay_rightTempLed->fn->setSize(errorDisplay_rightTempLed, 140, 25);
    errorDisplay_rightTempLed->fn->setScheme(errorDisplay_rightTempLed, &BlackScheme);
    errorDisplay_rightTempLed->fn->setString(errorDisplay_rightTempLed, (leString*)&string_Temp);
    root0->fn->addChild(root0, (leWidget*)errorDisplay_rightTempLed);

    errorDisplay_LabelWidget6 = leLabelWidget_New();
    errorDisplay_LabelWidget6->fn->setPosition(errorDisplay_LabelWidget6, 329, 150);
    errorDisplay_LabelWidget6->fn->setScheme(errorDisplay_LabelWidget6, &BlackScheme);
    errorDisplay_LabelWidget6->fn->setHAlignment(errorDisplay_LabelWidget6, LE_HALIGN_CENTER);
    errorDisplay_LabelWidget6->fn->setString(errorDisplay_LabelWidget6, (leString*)&string_Right);
    root0->fn->addChild(root0, (leWidget*)errorDisplay_LabelWidget6);

    errorDisplay_LabelWidget7 = leLabelWidget_New();
    errorDisplay_LabelWidget7->fn->setPosition(errorDisplay_LabelWidget7, 329, 175);
    errorDisplay_LabelWidget7->fn->setScheme(errorDisplay_LabelWidget7, &BlackScheme);
    errorDisplay_LabelWidget7->fn->setHAlignment(errorDisplay_LabelWidget7, LE_HALIGN_CENTER);
    errorDisplay_LabelWidget7->fn->setString(errorDisplay_LabelWidget7, (leString*)&string_DcHf);
    root0->fn->addChild(root0, (leWidget*)errorDisplay_LabelWidget7);

    errorDisplay_leftTempLed = leButtonWidget_New();
    errorDisplay_leftTempLed->fn->setPosition(errorDisplay_leftTempLed, 58, 110);
    errorDisplay_leftTempLed->fn->setEnabled(errorDisplay_leftTempLed, LE_FALSE);
    errorDisplay_leftTempLed->fn->setBorderType(errorDisplay_leftTempLed, LE_WIDGET_BORDER_NONE);
    errorDisplay_leftTempLed->fn->setToggleable(errorDisplay_leftTempLed, LE_TRUE);
    errorDisplay_leftTempLed->fn->setPressedImage(errorDisplay_leftTempLed, (leImage*)&errorLed);
    errorDisplay_leftTempLed->fn->setReleasedImage(errorDisplay_leftTempLed, (leImage*)&okLed);
    root0->fn->addChild(root0, (leWidget*)errorDisplay_leftTempLed);

    errorDisplay_leftDcHfLed = leButtonWidget_New();
    errorDisplay_leftDcHfLed->fn->setPosition(errorDisplay_leftDcHfLed, 58, 205);
    errorDisplay_leftDcHfLed->fn->setEnabled(errorDisplay_leftDcHfLed, LE_FALSE);
    errorDisplay_leftDcHfLed->fn->setBorderType(errorDisplay_leftDcHfLed, LE_WIDGET_BORDER_NONE);
    errorDisplay_leftDcHfLed->fn->setToggleable(errorDisplay_leftDcHfLed, LE_TRUE);
    errorDisplay_leftDcHfLed->fn->setPressedImage(errorDisplay_leftDcHfLed, (leImage*)&errorLed);
    errorDisplay_leftDcHfLed->fn->setReleasedImage(errorDisplay_leftDcHfLed, (leImage*)&okLed);
    root0->fn->addChild(root0, (leWidget*)errorDisplay_leftDcHfLed);

    errorDisplay_rightTempLed_ = leButtonWidget_New();
    errorDisplay_rightTempLed_->fn->setPosition(errorDisplay_rightTempLed_, 330, 110);
    errorDisplay_rightTempLed_->fn->setEnabled(errorDisplay_rightTempLed_, LE_FALSE);
    errorDisplay_rightTempLed_->fn->setBorderType(errorDisplay_rightTempLed_, LE_WIDGET_BORDER_NONE);
    errorDisplay_rightTempLed_->fn->setToggleable(errorDisplay_rightTempLed_, LE_TRUE);
    errorDisplay_rightTempLed_->fn->setPressedImage(errorDisplay_rightTempLed_, (leImage*)&errorLed);
    errorDisplay_rightTempLed_->fn->setReleasedImage(errorDisplay_rightTempLed_, (leImage*)&okLed);
    root0->fn->addChild(root0, (leWidget*)errorDisplay_rightTempLed_);

    errorDisplay_rightDcHfLed = leButtonWidget_New();
    errorDisplay_rightDcHfLed->fn->setPosition(errorDisplay_rightDcHfLed, 330, 205);
    errorDisplay_rightDcHfLed->fn->setEnabled(errorDisplay_rightDcHfLed, LE_FALSE);
    errorDisplay_rightDcHfLed->fn->setBorderType(errorDisplay_rightDcHfLed, LE_WIDGET_BORDER_NONE);
    errorDisplay_rightDcHfLed->fn->setToggleable(errorDisplay_rightDcHfLed, LE_TRUE);
    errorDisplay_rightDcHfLed->fn->setPressedImage(errorDisplay_rightDcHfLed, (leImage*)&errorLed);
    errorDisplay_rightDcHfLed->fn->setReleasedImage(errorDisplay_rightDcHfLed, (leImage*)&okLed);
    root0->fn->addChild(root0, (leWidget*)errorDisplay_rightDcHfLed);

    errorDisplay_LabelWidget8 = leLabelWidget_New();
    errorDisplay_LabelWidget8->fn->setPosition(errorDisplay_LabelWidget8, 0, 13);
    errorDisplay_LabelWidget8->fn->setSize(errorDisplay_LabelWidget8, 480, 25);
    errorDisplay_LabelWidget8->fn->setScheme(errorDisplay_LabelWidget8, &BlackScheme);
    errorDisplay_LabelWidget8->fn->setBackgroundType(errorDisplay_LabelWidget8, LE_WIDGET_BACKGROUND_NONE);
    errorDisplay_LabelWidget8->fn->setHAlignment(errorDisplay_LabelWidget8, LE_HALIGN_CENTER);
    errorDisplay_LabelWidget8->fn->setString(errorDisplay_LabelWidget8, (leString*)&string_ampStatus);
    root0->fn->addChild(root0, (leWidget*)errorDisplay_LabelWidget8);

    errorDisplay_LabelWidget_0 = leLabelWidget_New();
    errorDisplay_LabelWidget_0->fn->setPosition(errorDisplay_LabelWidget_0, 14, 238);
    errorDisplay_LabelWidget_0->fn->setSize(errorDisplay_LabelWidget_0, 480, 25);
    errorDisplay_LabelWidget_0->fn->setScheme(errorDisplay_LabelWidget_0, &warningScheme);
    errorDisplay_LabelWidget_0->fn->setHAlignment(errorDisplay_LabelWidget_0, LE_HALIGN_CENTER);
    errorDisplay_LabelWidget_0->fn->setString(errorDisplay_LabelWidget_0, (leString*)&string_CyclePowerStr);
    root0->fn->addChild(root0, (leWidget*)errorDisplay_LabelWidget_0);

    leAddRootWidget(root0, 0);
    leSetLayerColorMode(0, LE_COLOR_MODE_RGB_565);

    showing = LE_TRUE;

    return LE_SUCCESS;
}

void screenUpdate_errorDisplay(void)
{
    root0->fn->setSize(root0, root0->rect.width, root0->rect.height);
}

void screenHide_errorDisplay(void)
{

    leRemoveRootWidget(root0, 0);
    leWidget_Delete(root0);
    root0 = NULL;

    errorDisplay_PanelWidget0 = NULL;
    errorDisplay_LabelWidget0 = NULL;
    errorDisplay_LabelWidget1 = NULL;
    errorDisplay_LabelWidget2 = NULL;
    errorDisplay_LabelWidget3 = NULL;
    errorDisplay_LabelWidget4 = NULL;
    errorDisplay_rightTempLed = NULL;
    errorDisplay_LabelWidget6 = NULL;
    errorDisplay_LabelWidget7 = NULL;
    errorDisplay_leftTempLed = NULL;
    errorDisplay_leftDcHfLed = NULL;
    errorDisplay_rightTempLed_ = NULL;
    errorDisplay_rightDcHfLed = NULL;
    errorDisplay_LabelWidget8 = NULL;
    errorDisplay_LabelWidget_0 = NULL;


    showing = LE_FALSE;
}

void screenDestroy_errorDisplay(void)
{
    if(initialized == LE_FALSE)
        return;

    initialized = LE_FALSE;
}

leWidget* screenGetRoot_errorDisplay(uint32_t lyrIdx)
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

