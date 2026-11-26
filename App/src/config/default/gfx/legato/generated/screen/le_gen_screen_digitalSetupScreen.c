#include "gfx/legato/generated/screen/le_gen_screen_digitalSetupScreen.h"

// screen member widget declarations
static leWidget* root0;

leWidget* digitalSetupScreen_digitalBackground;
leImageWidget* digitalSetupScreen_dsdFilterImg;
leImageWidget* digitalSetupScreen_pcmFilterImg;
leRectangleWidget* digitalSetupScreen_digitalSetHeaderLineRight;
leRectangleWidget* digitalSetupScreen_digitaleSetHeaderLineLeft;
leLabelWidget* digitalSetupScreen_digitalSetupHeader;
leButtonWidget* digitalSetupScreen_dsdLpFilterOnButton;
leButtonWidget* digitalSetupScreen_dsdLpFilterOffButton;
leButtonWidget* digitalSetupScreen_digitalGain0dBButton;
leButtonWidget* digitalSetupScreen_digitalGainMinus6dBButton;
leLabelWidget* digitalSetupScreen_dsdLpFilterHeader1;
leLabelWidget* digitalSetupScreen_LabelWidget1;
leImageWidget* digitalSetupScreen_digitaBackToMenuButtonImg;
leLabelWidget* digitalSetupScreen_filterNameLine1;
leLabelWidget* digitalSetupScreen_filterNameLine2;
leLabelWidget* digitalSetupScreen_dsdLpHeader2;
leLabelWidget* digitalSetupScreen_dsdLabel;
leLabelWidget* digitalSetupScreen_dsdFilterLabel;
leLabelWidget* digitalSetupScreen_curDsdFilterLabel;
leButtonWidget* digitalSetupScreen_dsdFilterUpButton;
leButtonWidget* digitalSetupScreen_dsdFilterDwnButton;
leLabelWidget* digitalSetupScreen_pcmLabel;
leLabelWidget* digitalSetupScreen_pcmFilterLabel;
leLabelWidget* digitalSetupScreen_curPcmFilterLabel;
leButtonWidget* digitalSetupScreen_pcmFilterUpButton;
leButtonWidget* digitalSetupScreen_pcmFilterDwnButton;
leButtonWidget* digitalSetupScreen_digitaBackToMenuButton;

static leBool initialized = LE_FALSE;
static leBool showing = LE_FALSE;

leResult screenInit_digitalSetupScreen(void)
{
    if(initialized == LE_TRUE)
        return LE_FAILURE;

    initialized = LE_TRUE;

    return LE_SUCCESS;
}

leResult screenShow_digitalSetupScreen(void)
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

    digitalSetupScreen_digitalBackground = leWidget_New();
    digitalSetupScreen_digitalBackground->fn->setPosition(digitalSetupScreen_digitalBackground, 0, 0);
    digitalSetupScreen_digitalBackground->fn->setSize(digitalSetupScreen_digitalBackground, 480, 272);
    digitalSetupScreen_digitalBackground->fn->setScheme(digitalSetupScreen_digitalBackground, &BlackScheme);
    root0->fn->addChild(root0, (leWidget*)digitalSetupScreen_digitalBackground);

    digitalSetupScreen_dsdFilterImg = leImageWidget_New();
    digitalSetupScreen_dsdFilterImg->fn->setPosition(digitalSetupScreen_dsdFilterImg, 150, 55);
    digitalSetupScreen_dsdFilterImg->fn->setSize(digitalSetupScreen_dsdFilterImg, 75, 181);
    digitalSetupScreen_dsdFilterImg->fn->setEnabled(digitalSetupScreen_dsdFilterImg, LE_FALSE);
    digitalSetupScreen_dsdFilterImg->fn->setVisible(digitalSetupScreen_dsdFilterImg, LE_FALSE);
    digitalSetupScreen_dsdFilterImg->fn->setScheme(digitalSetupScreen_dsdFilterImg, &BlackScheme);
    digitalSetupScreen_dsdFilterImg->fn->setBorderType(digitalSetupScreen_dsdFilterImg, LE_WIDGET_BORDER_NONE);
    digitalSetupScreen_dsdFilterImg->fn->setVAlignment(digitalSetupScreen_dsdFilterImg, LE_VALIGN_BOTTOM);
    digitalSetupScreen_dsdFilterImg->fn->setImage(digitalSetupScreen_dsdFilterImg, (leImage*)&ILMVolButtons);
    root0->fn->addChild(root0, (leWidget*)digitalSetupScreen_dsdFilterImg);

    digitalSetupScreen_dsdLabel = leLabelWidget_New();
    digitalSetupScreen_dsdLabel->fn->setPosition(digitalSetupScreen_dsdLabel, 0, -2);
    digitalSetupScreen_dsdLabel->fn->setSize(digitalSetupScreen_dsdLabel, 75, 25);
    digitalSetupScreen_dsdLabel->fn->setScheme(digitalSetupScreen_dsdLabel, &BlackScheme);
    digitalSetupScreen_dsdLabel->fn->setHAlignment(digitalSetupScreen_dsdLabel, LE_HALIGN_CENTER);
    digitalSetupScreen_dsdLabel->fn->setString(digitalSetupScreen_dsdLabel, (leString*)&string_digitalSettingDsdString);
    digitalSetupScreen_dsdFilterImg->fn->addChild(digitalSetupScreen_dsdFilterImg, (leWidget*)digitalSetupScreen_dsdLabel);

    digitalSetupScreen_dsdFilterLabel = leLabelWidget_New();
    digitalSetupScreen_dsdFilterLabel->fn->setPosition(digitalSetupScreen_dsdFilterLabel, 0, 18);
    digitalSetupScreen_dsdFilterLabel->fn->setSize(digitalSetupScreen_dsdFilterLabel, 75, 25);
    digitalSetupScreen_dsdFilterLabel->fn->setScheme(digitalSetupScreen_dsdFilterLabel, &BlackScheme);
    digitalSetupScreen_dsdFilterLabel->fn->setHAlignment(digitalSetupScreen_dsdFilterLabel, LE_HALIGN_CENTER);
    digitalSetupScreen_dsdFilterLabel->fn->setString(digitalSetupScreen_dsdFilterLabel, (leString*)&string_digitalSettingFilterString);
    digitalSetupScreen_dsdFilterImg->fn->addChild(digitalSetupScreen_dsdFilterImg, (leWidget*)digitalSetupScreen_dsdFilterLabel);

    digitalSetupScreen_curDsdFilterLabel = leLabelWidget_New();
    digitalSetupScreen_curDsdFilterLabel->fn->setPosition(digitalSetupScreen_curDsdFilterLabel, 0, 44);
    digitalSetupScreen_curDsdFilterLabel->fn->setSize(digitalSetupScreen_curDsdFilterLabel, 75, 50);
    digitalSetupScreen_curDsdFilterLabel->fn->setScheme(digitalSetupScreen_curDsdFilterLabel, &BlackScheme);
    digitalSetupScreen_curDsdFilterLabel->fn->setHAlignment(digitalSetupScreen_curDsdFilterLabel, LE_HALIGN_CENTER);
    digitalSetupScreen_curDsdFilterLabel->fn->setString(digitalSetupScreen_curDsdFilterLabel, (leString*)&string_curDsdFilterString);
    digitalSetupScreen_dsdFilterImg->fn->addChild(digitalSetupScreen_dsdFilterImg, (leWidget*)digitalSetupScreen_curDsdFilterLabel);

    digitalSetupScreen_dsdFilterUpButton = leButtonWidget_New();
    digitalSetupScreen_dsdFilterUpButton->fn->setPosition(digitalSetupScreen_dsdFilterUpButton, 0, 83);
    digitalSetupScreen_dsdFilterUpButton->fn->setSize(digitalSetupScreen_dsdFilterUpButton, 75, 45);
    digitalSetupScreen_dsdFilterUpButton->fn->setBackgroundType(digitalSetupScreen_dsdFilterUpButton, LE_WIDGET_BACKGROUND_NONE);
    digitalSetupScreen_dsdFilterUpButton->fn->setBorderType(digitalSetupScreen_dsdFilterUpButton, LE_WIDGET_BORDER_NONE);
    digitalSetupScreen_dsdFilterUpButton->fn->setPressedEventCallback(digitalSetupScreen_dsdFilterUpButton, event_digitalSetupScreen_dsdFilterUpButton_OnPressed);
    digitalSetupScreen_dsdFilterImg->fn->addChild(digitalSetupScreen_dsdFilterImg, (leWidget*)digitalSetupScreen_dsdFilterUpButton);

    digitalSetupScreen_dsdFilterDwnButton = leButtonWidget_New();
    digitalSetupScreen_dsdFilterDwnButton->fn->setPosition(digitalSetupScreen_dsdFilterDwnButton, 0, 147);
    digitalSetupScreen_dsdFilterDwnButton->fn->setSize(digitalSetupScreen_dsdFilterDwnButton, 75, 45);
    digitalSetupScreen_dsdFilterDwnButton->fn->setBackgroundType(digitalSetupScreen_dsdFilterDwnButton, LE_WIDGET_BACKGROUND_NONE);
    digitalSetupScreen_dsdFilterDwnButton->fn->setBorderType(digitalSetupScreen_dsdFilterDwnButton, LE_WIDGET_BORDER_NONE);
    digitalSetupScreen_dsdFilterDwnButton->fn->setPressedEventCallback(digitalSetupScreen_dsdFilterDwnButton, event_digitalSetupScreen_dsdFilterDwnButton_OnPressed);
    digitalSetupScreen_dsdFilterImg->fn->addChild(digitalSetupScreen_dsdFilterImg, (leWidget*)digitalSetupScreen_dsdFilterDwnButton);

    digitalSetupScreen_pcmFilterImg = leImageWidget_New();
    digitalSetupScreen_pcmFilterImg->fn->setPosition(digitalSetupScreen_pcmFilterImg, 25, 55);
    digitalSetupScreen_pcmFilterImg->fn->setSize(digitalSetupScreen_pcmFilterImg, 75, 181);
    digitalSetupScreen_pcmFilterImg->fn->setScheme(digitalSetupScreen_pcmFilterImg, &BlackScheme);
    digitalSetupScreen_pcmFilterImg->fn->setBorderType(digitalSetupScreen_pcmFilterImg, LE_WIDGET_BORDER_NONE);
    digitalSetupScreen_pcmFilterImg->fn->setVAlignment(digitalSetupScreen_pcmFilterImg, LE_VALIGN_BOTTOM);
    digitalSetupScreen_pcmFilterImg->fn->setImage(digitalSetupScreen_pcmFilterImg, (leImage*)&ILMVolButtons);
    root0->fn->addChild(root0, (leWidget*)digitalSetupScreen_pcmFilterImg);

    digitalSetupScreen_pcmLabel = leLabelWidget_New();
    digitalSetupScreen_pcmLabel->fn->setPosition(digitalSetupScreen_pcmLabel, 0, -2);
    digitalSetupScreen_pcmLabel->fn->setSize(digitalSetupScreen_pcmLabel, 75, 25);
    digitalSetupScreen_pcmLabel->fn->setScheme(digitalSetupScreen_pcmLabel, &BlackScheme);
    digitalSetupScreen_pcmLabel->fn->setHAlignment(digitalSetupScreen_pcmLabel, LE_HALIGN_CENTER);
    digitalSetupScreen_pcmLabel->fn->setString(digitalSetupScreen_pcmLabel, (leString*)&string_digitalSettingPcmString);
    digitalSetupScreen_pcmFilterImg->fn->addChild(digitalSetupScreen_pcmFilterImg, (leWidget*)digitalSetupScreen_pcmLabel);

    digitalSetupScreen_pcmFilterLabel = leLabelWidget_New();
    digitalSetupScreen_pcmFilterLabel->fn->setPosition(digitalSetupScreen_pcmFilterLabel, 0, 18);
    digitalSetupScreen_pcmFilterLabel->fn->setSize(digitalSetupScreen_pcmFilterLabel, 75, 25);
    digitalSetupScreen_pcmFilterLabel->fn->setScheme(digitalSetupScreen_pcmFilterLabel, &BlackScheme);
    digitalSetupScreen_pcmFilterLabel->fn->setHAlignment(digitalSetupScreen_pcmFilterLabel, LE_HALIGN_CENTER);
    digitalSetupScreen_pcmFilterLabel->fn->setString(digitalSetupScreen_pcmFilterLabel, (leString*)&string_digitalSettingFilterString);
    digitalSetupScreen_pcmFilterImg->fn->addChild(digitalSetupScreen_pcmFilterImg, (leWidget*)digitalSetupScreen_pcmFilterLabel);

    digitalSetupScreen_curPcmFilterLabel = leLabelWidget_New();
    digitalSetupScreen_curPcmFilterLabel->fn->setPosition(digitalSetupScreen_curPcmFilterLabel, 0, 44);
    digitalSetupScreen_curPcmFilterLabel->fn->setSize(digitalSetupScreen_curPcmFilterLabel, 75, 50);
    digitalSetupScreen_curPcmFilterLabel->fn->setScheme(digitalSetupScreen_curPcmFilterLabel, &BlackScheme);
    digitalSetupScreen_curPcmFilterLabel->fn->setHAlignment(digitalSetupScreen_curPcmFilterLabel, LE_HALIGN_CENTER);
    digitalSetupScreen_curPcmFilterLabel->fn->setString(digitalSetupScreen_curPcmFilterLabel, (leString*)&string_curPcmFilterString);
    digitalSetupScreen_pcmFilterImg->fn->addChild(digitalSetupScreen_pcmFilterImg, (leWidget*)digitalSetupScreen_curPcmFilterLabel);

    digitalSetupScreen_pcmFilterUpButton = leButtonWidget_New();
    digitalSetupScreen_pcmFilterUpButton->fn->setPosition(digitalSetupScreen_pcmFilterUpButton, 0, 82);
    digitalSetupScreen_pcmFilterUpButton->fn->setSize(digitalSetupScreen_pcmFilterUpButton, 75, 45);
    digitalSetupScreen_pcmFilterUpButton->fn->setBackgroundType(digitalSetupScreen_pcmFilterUpButton, LE_WIDGET_BACKGROUND_NONE);
    digitalSetupScreen_pcmFilterUpButton->fn->setBorderType(digitalSetupScreen_pcmFilterUpButton, LE_WIDGET_BORDER_NONE);
    digitalSetupScreen_pcmFilterUpButton->fn->setPressedEventCallback(digitalSetupScreen_pcmFilterUpButton, event_digitalSetupScreen_pcmFilterUpButton_OnPressed);
    digitalSetupScreen_pcmFilterImg->fn->addChild(digitalSetupScreen_pcmFilterImg, (leWidget*)digitalSetupScreen_pcmFilterUpButton);

    digitalSetupScreen_pcmFilterDwnButton = leButtonWidget_New();
    digitalSetupScreen_pcmFilterDwnButton->fn->setPosition(digitalSetupScreen_pcmFilterDwnButton, 0, 146);
    digitalSetupScreen_pcmFilterDwnButton->fn->setSize(digitalSetupScreen_pcmFilterDwnButton, 75, 45);
    digitalSetupScreen_pcmFilterDwnButton->fn->setBackgroundType(digitalSetupScreen_pcmFilterDwnButton, LE_WIDGET_BACKGROUND_NONE);
    digitalSetupScreen_pcmFilterDwnButton->fn->setBorderType(digitalSetupScreen_pcmFilterDwnButton, LE_WIDGET_BORDER_NONE);
    digitalSetupScreen_pcmFilterDwnButton->fn->setPressedEventCallback(digitalSetupScreen_pcmFilterDwnButton, event_digitalSetupScreen_pcmFilterDwnButton_OnPressed);
    digitalSetupScreen_pcmFilterImg->fn->addChild(digitalSetupScreen_pcmFilterImg, (leWidget*)digitalSetupScreen_pcmFilterDwnButton);

    digitalSetupScreen_digitalSetHeaderLineRight = leRectangleWidget_New();
    digitalSetupScreen_digitalSetHeaderLineRight->fn->setPosition(digitalSetupScreen_digitalSetHeaderLineRight, 319, 25);
    digitalSetupScreen_digitalSetHeaderLineRight->fn->setSize(digitalSetupScreen_digitalSetHeaderLineRight, 135, 3);
    digitalSetupScreen_digitalSetHeaderLineRight->fn->setScheme(digitalSetupScreen_digitalSetHeaderLineRight, &WhiteScheme);
    digitalSetupScreen_digitalSetHeaderLineRight->fn->setBorderType(digitalSetupScreen_digitalSetHeaderLineRight, LE_WIDGET_BORDER_NONE);
    digitalSetupScreen_digitalSetHeaderLineRight->fn->setThickness(digitalSetupScreen_digitalSetHeaderLineRight, 3);
    root0->fn->addChild(root0, (leWidget*)digitalSetupScreen_digitalSetHeaderLineRight);

    digitalSetupScreen_digitaleSetHeaderLineLeft = leRectangleWidget_New();
    digitalSetupScreen_digitaleSetHeaderLineLeft->fn->setPosition(digitalSetupScreen_digitaleSetHeaderLineLeft, 26, 25);
    digitalSetupScreen_digitaleSetHeaderLineLeft->fn->setSize(digitalSetupScreen_digitaleSetHeaderLineLeft, 135, 3);
    digitalSetupScreen_digitaleSetHeaderLineLeft->fn->setScheme(digitalSetupScreen_digitaleSetHeaderLineLeft, &WhiteScheme);
    digitalSetupScreen_digitaleSetHeaderLineLeft->fn->setBorderType(digitalSetupScreen_digitaleSetHeaderLineLeft, LE_WIDGET_BORDER_NONE);
    digitalSetupScreen_digitaleSetHeaderLineLeft->fn->setThickness(digitalSetupScreen_digitaleSetHeaderLineLeft, 3);
    root0->fn->addChild(root0, (leWidget*)digitalSetupScreen_digitaleSetHeaderLineLeft);

    digitalSetupScreen_digitalSetupHeader = leLabelWidget_New();
    digitalSetupScreen_digitalSetupHeader->fn->setPosition(digitalSetupScreen_digitalSetupHeader, 0, 12);
    digitalSetupScreen_digitalSetupHeader->fn->setSize(digitalSetupScreen_digitalSetupHeader, 480, 25);
    digitalSetupScreen_digitalSetupHeader->fn->setScheme(digitalSetupScreen_digitalSetupHeader, &BlackScheme);
    digitalSetupScreen_digitalSetupHeader->fn->setBackgroundType(digitalSetupScreen_digitalSetupHeader, LE_WIDGET_BACKGROUND_NONE);
    digitalSetupScreen_digitalSetupHeader->fn->setHAlignment(digitalSetupScreen_digitalSetupHeader, LE_HALIGN_CENTER);
    digitalSetupScreen_digitalSetupHeader->fn->setString(digitalSetupScreen_digitalSetupHeader, (leString*)&string_DigitalSetupHeaderString);
    root0->fn->addChild(root0, (leWidget*)digitalSetupScreen_digitalSetupHeader);

    digitalSetupScreen_dsdLpFilterOnButton = leButtonWidget_New();
    digitalSetupScreen_dsdLpFilterOnButton->fn->setPosition(digitalSetupScreen_dsdLpFilterOnButton, 380, 55);
    digitalSetupScreen_dsdLpFilterOnButton->fn->setEnabled(digitalSetupScreen_dsdLpFilterOnButton, LE_FALSE);
    digitalSetupScreen_dsdLpFilterOnButton->fn->setScheme(digitalSetupScreen_dsdLpFilterOnButton, &radioButtonScheme);
    digitalSetupScreen_dsdLpFilterOnButton->fn->setBackgroundType(digitalSetupScreen_dsdLpFilterOnButton, LE_WIDGET_BACKGROUND_NONE);
    digitalSetupScreen_dsdLpFilterOnButton->fn->setBorderType(digitalSetupScreen_dsdLpFilterOnButton, LE_WIDGET_BORDER_NONE);
    digitalSetupScreen_dsdLpFilterOnButton->fn->setHAlignment(digitalSetupScreen_dsdLpFilterOnButton, LE_HALIGN_LEFT);
    digitalSetupScreen_dsdLpFilterOnButton->fn->setVAlignment(digitalSetupScreen_dsdLpFilterOnButton, LE_VALIGN_BOTTOM);
    digitalSetupScreen_dsdLpFilterOnButton->fn->setToggleable(digitalSetupScreen_dsdLpFilterOnButton, LE_TRUE);
    digitalSetupScreen_dsdLpFilterOnButton->fn->setString(digitalSetupScreen_dsdLpFilterOnButton, (leString*)&string_onString18);
    digitalSetupScreen_dsdLpFilterOnButton->fn->setPressedImage(digitalSetupScreen_dsdLpFilterOnButton, (leImage*)&smallSelected2);
    digitalSetupScreen_dsdLpFilterOnButton->fn->setReleasedImage(digitalSetupScreen_dsdLpFilterOnButton, (leImage*)&smallNotSelected3);
    digitalSetupScreen_dsdLpFilterOnButton->fn->setPressedOffset(digitalSetupScreen_dsdLpFilterOnButton, 0);
    digitalSetupScreen_dsdLpFilterOnButton->fn->setPressedEventCallback(digitalSetupScreen_dsdLpFilterOnButton, event_digitalSetupScreen_dsdLpFilterOnButton_OnPressed);
    root0->fn->addChild(root0, (leWidget*)digitalSetupScreen_dsdLpFilterOnButton);

    digitalSetupScreen_dsdLpFilterOffButton = leButtonWidget_New();
    digitalSetupScreen_dsdLpFilterOffButton->fn->setPosition(digitalSetupScreen_dsdLpFilterOffButton, 380, 85);
    digitalSetupScreen_dsdLpFilterOffButton->fn->setEnabled(digitalSetupScreen_dsdLpFilterOffButton, LE_FALSE);
    digitalSetupScreen_dsdLpFilterOffButton->fn->setScheme(digitalSetupScreen_dsdLpFilterOffButton, &radioButtonScheme);
    digitalSetupScreen_dsdLpFilterOffButton->fn->setBackgroundType(digitalSetupScreen_dsdLpFilterOffButton, LE_WIDGET_BACKGROUND_NONE);
    digitalSetupScreen_dsdLpFilterOffButton->fn->setBorderType(digitalSetupScreen_dsdLpFilterOffButton, LE_WIDGET_BORDER_NONE);
    digitalSetupScreen_dsdLpFilterOffButton->fn->setHAlignment(digitalSetupScreen_dsdLpFilterOffButton, LE_HALIGN_LEFT);
    digitalSetupScreen_dsdLpFilterOffButton->fn->setVAlignment(digitalSetupScreen_dsdLpFilterOffButton, LE_VALIGN_BOTTOM);
    digitalSetupScreen_dsdLpFilterOffButton->fn->setToggleable(digitalSetupScreen_dsdLpFilterOffButton, LE_TRUE);
    digitalSetupScreen_dsdLpFilterOffButton->fn->setString(digitalSetupScreen_dsdLpFilterOffButton, (leString*)&string_offStr18);
    digitalSetupScreen_dsdLpFilterOffButton->fn->setPressedImage(digitalSetupScreen_dsdLpFilterOffButton, (leImage*)&smallSelected2);
    digitalSetupScreen_dsdLpFilterOffButton->fn->setReleasedImage(digitalSetupScreen_dsdLpFilterOffButton, (leImage*)&smallNotSelected3);
    digitalSetupScreen_dsdLpFilterOffButton->fn->setPressedOffset(digitalSetupScreen_dsdLpFilterOffButton, 0);
    digitalSetupScreen_dsdLpFilterOffButton->fn->setPressedEventCallback(digitalSetupScreen_dsdLpFilterOffButton, event_digitalSetupScreen_dsdLpFilterOffButton_OnPressed);
    root0->fn->addChild(root0, (leWidget*)digitalSetupScreen_dsdLpFilterOffButton);

    digitalSetupScreen_digitalGain0dBButton = leButtonWidget_New();
    digitalSetupScreen_digitalGain0dBButton->fn->setPosition(digitalSetupScreen_digitalGain0dBButton, 380, 120);
    digitalSetupScreen_digitalGain0dBButton->fn->setEnabled(digitalSetupScreen_digitalGain0dBButton, LE_FALSE);
    digitalSetupScreen_digitalGain0dBButton->fn->setScheme(digitalSetupScreen_digitalGain0dBButton, &radioButtonScheme);
    digitalSetupScreen_digitalGain0dBButton->fn->setBackgroundType(digitalSetupScreen_digitalGain0dBButton, LE_WIDGET_BACKGROUND_NONE);
    digitalSetupScreen_digitalGain0dBButton->fn->setBorderType(digitalSetupScreen_digitalGain0dBButton, LE_WIDGET_BORDER_NONE);
    digitalSetupScreen_digitalGain0dBButton->fn->setHAlignment(digitalSetupScreen_digitalGain0dBButton, LE_HALIGN_LEFT);
    digitalSetupScreen_digitalGain0dBButton->fn->setToggleable(digitalSetupScreen_digitalGain0dBButton, LE_TRUE);
    digitalSetupScreen_digitalGain0dBButton->fn->setString(digitalSetupScreen_digitalGain0dBButton, (leString*)&string_string0dB);
    digitalSetupScreen_digitalGain0dBButton->fn->setPressedImage(digitalSetupScreen_digitalGain0dBButton, (leImage*)&smallSelected2);
    digitalSetupScreen_digitalGain0dBButton->fn->setReleasedImage(digitalSetupScreen_digitalGain0dBButton, (leImage*)&smallNotSelected3);
    digitalSetupScreen_digitalGain0dBButton->fn->setImageMargin(digitalSetupScreen_digitalGain0dBButton, 16);
    digitalSetupScreen_digitalGain0dBButton->fn->setPressedOffset(digitalSetupScreen_digitalGain0dBButton, 0);
    digitalSetupScreen_digitalGain0dBButton->fn->setPressedEventCallback(digitalSetupScreen_digitalGain0dBButton, event_digitalSetupScreen_digitalGain0dBButton_OnPressed);
    root0->fn->addChild(root0, (leWidget*)digitalSetupScreen_digitalGain0dBButton);

    digitalSetupScreen_digitalGainMinus6dBButton = leButtonWidget_New();
    digitalSetupScreen_digitalGainMinus6dBButton->fn->setPosition(digitalSetupScreen_digitalGainMinus6dBButton, 380, 150);
    digitalSetupScreen_digitalGainMinus6dBButton->fn->setEnabled(digitalSetupScreen_digitalGainMinus6dBButton, LE_FALSE);
    digitalSetupScreen_digitalGainMinus6dBButton->fn->setScheme(digitalSetupScreen_digitalGainMinus6dBButton, &radioButtonScheme);
    digitalSetupScreen_digitalGainMinus6dBButton->fn->setBackgroundType(digitalSetupScreen_digitalGainMinus6dBButton, LE_WIDGET_BACKGROUND_NONE);
    digitalSetupScreen_digitalGainMinus6dBButton->fn->setBorderType(digitalSetupScreen_digitalGainMinus6dBButton, LE_WIDGET_BORDER_NONE);
    digitalSetupScreen_digitalGainMinus6dBButton->fn->setHAlignment(digitalSetupScreen_digitalGainMinus6dBButton, LE_HALIGN_LEFT);
    digitalSetupScreen_digitalGainMinus6dBButton->fn->setToggleable(digitalSetupScreen_digitalGainMinus6dBButton, LE_TRUE);
    digitalSetupScreen_digitalGainMinus6dBButton->fn->setString(digitalSetupScreen_digitalGainMinus6dBButton, (leString*)&string_stringMinus6dB);
    digitalSetupScreen_digitalGainMinus6dBButton->fn->setPressedImage(digitalSetupScreen_digitalGainMinus6dBButton, (leImage*)&smallSelected2);
    digitalSetupScreen_digitalGainMinus6dBButton->fn->setReleasedImage(digitalSetupScreen_digitalGainMinus6dBButton, (leImage*)&smallNotSelected3);
    digitalSetupScreen_digitalGainMinus6dBButton->fn->setPressedOffset(digitalSetupScreen_digitalGainMinus6dBButton, 0);
    digitalSetupScreen_digitalGainMinus6dBButton->fn->setPressedEventCallback(digitalSetupScreen_digitalGainMinus6dBButton, event_digitalSetupScreen_digitalGainMinus6dBButton_OnPressed);
    root0->fn->addChild(root0, (leWidget*)digitalSetupScreen_digitalGainMinus6dBButton);

    digitalSetupScreen_dsdLpFilterHeader1 = leLabelWidget_New();
    digitalSetupScreen_dsdLpFilterHeader1->fn->setPosition(digitalSetupScreen_dsdLpFilterHeader1, 233, 55);
    digitalSetupScreen_dsdLpFilterHeader1->fn->setSize(digitalSetupScreen_dsdLpFilterHeader1, 140, 25);
    digitalSetupScreen_dsdLpFilterHeader1->fn->setScheme(digitalSetupScreen_dsdLpFilterHeader1, &BlackScheme);
    digitalSetupScreen_dsdLpFilterHeader1->fn->setString(digitalSetupScreen_dsdLpFilterHeader1, (leString*)&string_dsdAnalogueString16);
    root0->fn->addChild(root0, (leWidget*)digitalSetupScreen_dsdLpFilterHeader1);

    digitalSetupScreen_LabelWidget1 = leLabelWidget_New();
    digitalSetupScreen_LabelWidget1->fn->setPosition(digitalSetupScreen_LabelWidget1, 324, 120);
    digitalSetupScreen_LabelWidget1->fn->setSize(digitalSetupScreen_LabelWidget1, 50, 25);
    digitalSetupScreen_LabelWidget1->fn->setScheme(digitalSetupScreen_LabelWidget1, &BlackScheme);
    digitalSetupScreen_LabelWidget1->fn->setString(digitalSetupScreen_LabelWidget1, (leString*)&string_gainString);
    root0->fn->addChild(root0, (leWidget*)digitalSetupScreen_LabelWidget1);

    digitalSetupScreen_digitaBackToMenuButtonImg = leImageWidget_New();
    digitalSetupScreen_digitaBackToMenuButtonImg->fn->setPosition(digitalSetupScreen_digitaBackToMenuButtonImg, 340, 205);
    digitalSetupScreen_digitaBackToMenuButtonImg->fn->setSize(digitalSetupScreen_digitaBackToMenuButtonImg, 110, 50);
    digitalSetupScreen_digitaBackToMenuButtonImg->fn->setScheme(digitalSetupScreen_digitaBackToMenuButtonImg, &BlackScheme);
    digitalSetupScreen_digitaBackToMenuButtonImg->fn->setBorderType(digitalSetupScreen_digitaBackToMenuButtonImg, LE_WIDGET_BORDER_NONE);
    digitalSetupScreen_digitaBackToMenuButtonImg->fn->setImage(digitalSetupScreen_digitaBackToMenuButtonImg, (leImage*)&BackToMenu);
    root0->fn->addChild(root0, (leWidget*)digitalSetupScreen_digitaBackToMenuButtonImg);

    digitalSetupScreen_digitaBackToMenuButton = leButtonWidget_New();
    digitalSetupScreen_digitaBackToMenuButton->fn->setPosition(digitalSetupScreen_digitaBackToMenuButton, 2, 3);
    digitalSetupScreen_digitaBackToMenuButton->fn->setSize(digitalSetupScreen_digitaBackToMenuButton, 111, 49);
    digitalSetupScreen_digitaBackToMenuButton->fn->setScheme(digitalSetupScreen_digitaBackToMenuButton, &BlackScheme);
    digitalSetupScreen_digitaBackToMenuButton->fn->setBackgroundType(digitalSetupScreen_digitaBackToMenuButton, LE_WIDGET_BACKGROUND_NONE);
    digitalSetupScreen_digitaBackToMenuButton->fn->setBorderType(digitalSetupScreen_digitaBackToMenuButton, LE_WIDGET_BORDER_NONE);
    digitalSetupScreen_digitaBackToMenuButton->fn->setPressedOffset(digitalSetupScreen_digitaBackToMenuButton, 0);
    digitalSetupScreen_digitaBackToMenuButton->fn->setPressedEventCallback(digitalSetupScreen_digitaBackToMenuButton, event_digitalSetupScreen_digitaBackToMenuButton_OnPressed);
    digitalSetupScreen_digitaBackToMenuButtonImg->fn->addChild(digitalSetupScreen_digitaBackToMenuButtonImg, (leWidget*)digitalSetupScreen_digitaBackToMenuButton);

    digitalSetupScreen_filterNameLine1 = leLabelWidget_New();
    digitalSetupScreen_filterNameLine1->fn->setPosition(digitalSetupScreen_filterNameLine1, 118, 158);
    digitalSetupScreen_filterNameLine1->fn->setSize(digitalSetupScreen_filterNameLine1, 213, 25);
    digitalSetupScreen_filterNameLine1->fn->setScheme(digitalSetupScreen_filterNameLine1, &BlackScheme);
    digitalSetupScreen_filterNameLine1->fn->setBackgroundType(digitalSetupScreen_filterNameLine1, LE_WIDGET_BACKGROUND_NONE);
    digitalSetupScreen_filterNameLine1->fn->setString(digitalSetupScreen_filterNameLine1, (leString*)&string_MinPhase);
    root0->fn->addChild(root0, (leWidget*)digitalSetupScreen_filterNameLine1);

    digitalSetupScreen_filterNameLine2 = leLabelWidget_New();
    digitalSetupScreen_filterNameLine2->fn->setPosition(digitalSetupScreen_filterNameLine2, 118, 185);
    digitalSetupScreen_filterNameLine2->fn->setSize(digitalSetupScreen_filterNameLine2, 214, 25);
    digitalSetupScreen_filterNameLine2->fn->setScheme(digitalSetupScreen_filterNameLine2, &BlackScheme);
    digitalSetupScreen_filterNameLine2->fn->setBackgroundType(digitalSetupScreen_filterNameLine2, LE_WIDGET_BACKGROUND_NONE);
    digitalSetupScreen_filterNameLine2->fn->setString(digitalSetupScreen_filterNameLine2, (leString*)&string_SloRollLoDisp);
    root0->fn->addChild(root0, (leWidget*)digitalSetupScreen_filterNameLine2);

    digitalSetupScreen_dsdLpHeader2 = leLabelWidget_New();
    digitalSetupScreen_dsdLpHeader2->fn->setPosition(digitalSetupScreen_dsdLpHeader2, 233, 83);
    digitalSetupScreen_dsdLpHeader2->fn->setSize(digitalSetupScreen_dsdLpHeader2, 140, 25);
    digitalSetupScreen_dsdLpHeader2->fn->setScheme(digitalSetupScreen_dsdLpHeader2, &BlackScheme);
    digitalSetupScreen_dsdLpHeader2->fn->setString(digitalSetupScreen_dsdLpHeader2, (leString*)&string_lowPassString16);
    root0->fn->addChild(root0, (leWidget*)digitalSetupScreen_dsdLpHeader2);

    leAddRootWidget(root0, 0);
    leSetLayerColorMode(0, LE_COLOR_MODE_RGB_565);

    digitalSetupScreen_OnShow(); // raise event

    showing = LE_TRUE;

    return LE_SUCCESS;
}

void screenUpdate_digitalSetupScreen(void)
{
    root0->fn->setSize(root0, root0->rect.width, root0->rect.height);
}

void screenHide_digitalSetupScreen(void)
{

    leRemoveRootWidget(root0, 0);
    leWidget_Delete(root0);
    root0 = NULL;

    digitalSetupScreen_digitalBackground = NULL;
    digitalSetupScreen_dsdFilterImg = NULL;
    digitalSetupScreen_pcmFilterImg = NULL;
    digitalSetupScreen_digitalSetHeaderLineRight = NULL;
    digitalSetupScreen_digitaleSetHeaderLineLeft = NULL;
    digitalSetupScreen_digitalSetupHeader = NULL;
    digitalSetupScreen_dsdLpFilterOnButton = NULL;
    digitalSetupScreen_dsdLpFilterOffButton = NULL;
    digitalSetupScreen_digitalGain0dBButton = NULL;
    digitalSetupScreen_digitalGainMinus6dBButton = NULL;
    digitalSetupScreen_dsdLpFilterHeader1 = NULL;
    digitalSetupScreen_LabelWidget1 = NULL;
    digitalSetupScreen_digitaBackToMenuButtonImg = NULL;
    digitalSetupScreen_filterNameLine1 = NULL;
    digitalSetupScreen_filterNameLine2 = NULL;
    digitalSetupScreen_dsdLpHeader2 = NULL;
    digitalSetupScreen_dsdLabel = NULL;
    digitalSetupScreen_dsdFilterLabel = NULL;
    digitalSetupScreen_curDsdFilterLabel = NULL;
    digitalSetupScreen_dsdFilterUpButton = NULL;
    digitalSetupScreen_dsdFilterDwnButton = NULL;
    digitalSetupScreen_pcmLabel = NULL;
    digitalSetupScreen_pcmFilterLabel = NULL;
    digitalSetupScreen_curPcmFilterLabel = NULL;
    digitalSetupScreen_pcmFilterUpButton = NULL;
    digitalSetupScreen_pcmFilterDwnButton = NULL;
    digitalSetupScreen_digitaBackToMenuButton = NULL;


    showing = LE_FALSE;
}

void screenDestroy_digitalSetupScreen(void)
{
    if(initialized == LE_FALSE)
        return;

    initialized = LE_FALSE;
}

leWidget* screenGetRoot_digitalSetupScreen(uint32_t lyrIdx)
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

