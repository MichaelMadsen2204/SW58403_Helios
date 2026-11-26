#include "gfx/legato/generated/screen/le_gen_screen_actionScreen.h"

// screen member widget declarations
static leWidget* root0;

leWidget* actionScreen_BackGround;
leWidget* actionScreen_anaInpNamePanel;
leWidget* actionScreen_digiInpNamePanel;
leWidget* actionScreen_digInfoPanel;
leButtonWidget* actionScreen_dispOnButton;
leImageWidget* actionScreen_fanErrorImg;
leImageWidget* actionScreen_actionMuteKryds;
leLabelWidget* actionScreen_actVolumeHeader;
leLabelWidget* actionScreen_avLevLabel;
leLabelWidget* actionScreen_actCurLevel;
leButtonWidget* actionScreen_actMuteBut;
leButtonWidget* actionScreen_actMenuBut;
leButtonWidget* actionScreen_actAnaDigiSelectionBut;
leImageWidget* actionScreen_actVolumeButImg;
leButtonWidget* actionScreen_actVolPlusBut;
leButtonWidget* actionScreen_actVolMinusBut;
leLabelWidget* actionScreen_anaInpNameHeader;
leButtonWidget* actionScreen_anaInp1But;
leButtonWidget* actionScreen_anaInp2But;
leButtonWidget* actionScreen_anaInp3But;
leButtonWidget* actionScreen_anaInp4But;
leButtonWidget* actionScreen_anaInp5But;
leButtonWidget* actionScreen_anaInp6But;
leLabelWidget* actionScreen_digiInpNameHeader;
leButtonWidget* actionScreen_digiInp7But;
leButtonWidget* actionScreen_digiInp8But;
leButtonWidget* actionScreen_digiInp9But;
leButtonWidget* actionScreen_digiInp10But;
leButtonWidget* actionScreen_digiInp11But;
leButtonWidget* actionScreen_padLockImg;
leLabelWidget* actionScreen_digiInfoFSLabel;
leLabelWidget* actionScreen_digiInfoFilterLabel1;
leLabelWidget* actionScreen_digiInfoFilterLabel2;
leLabelWidget* actionScreen_digiInfoFilterLabel3;
leLabelWidget* actionScreen_dsdLpOff;
leLabelWidget* actionScreen_dsdLpOn;
leLabelWidget* actionScreen_gain0db;
leLabelWidget* actionScreen_gainMinus6dB;
leWidget* actionScreen_batteryPanel;
leImageWidget* actionScreen_BattCharged;
leImageWidget* actionScreen_BattCharging;

static leBool initialized = LE_FALSE;
static leBool showing = LE_FALSE;

leResult screenInit_actionScreen(void)
{
    if(initialized == LE_TRUE)
        return LE_FAILURE;

    initialized = LE_TRUE;

    return LE_SUCCESS;
}

leResult screenShow_actionScreen(void)
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

    actionScreen_BackGround = leWidget_New();
    actionScreen_BackGround->fn->setPosition(actionScreen_BackGround, 0, 0);
    actionScreen_BackGround->fn->setSize(actionScreen_BackGround, 480, 272);
    actionScreen_BackGround->fn->setScheme(actionScreen_BackGround, &BlackScheme);
    root0->fn->addChild(root0, (leWidget*)actionScreen_BackGround);

    actionScreen_actionMuteKryds = leImageWidget_New();
    actionScreen_actionMuteKryds->fn->setPosition(actionScreen_actionMuteKryds, 362, 30);
    actionScreen_actionMuteKryds->fn->setSize(actionScreen_actionMuteKryds, 118, 106);
    actionScreen_actionMuteKryds->fn->setEnabled(actionScreen_actionMuteKryds, LE_FALSE);
    actionScreen_actionMuteKryds->fn->setVisible(actionScreen_actionMuteKryds, LE_FALSE);
    actionScreen_actionMuteKryds->fn->setBackgroundType(actionScreen_actionMuteKryds, LE_WIDGET_BACKGROUND_NONE);
    actionScreen_actionMuteKryds->fn->setBorderType(actionScreen_actionMuteKryds, LE_WIDGET_BORDER_NONE);
    actionScreen_actionMuteKryds->fn->setImage(actionScreen_actionMuteKryds, (leImage*)&actionMuteKryds118x118);
    actionScreen_BackGround->fn->addChild(actionScreen_BackGround, (leWidget*)actionScreen_actionMuteKryds);

    actionScreen_actVolumeHeader = leLabelWidget_New();
    actionScreen_actVolumeHeader->fn->setPosition(actionScreen_actVolumeHeader, 381, 15);
    actionScreen_actVolumeHeader->fn->setSize(actionScreen_actVolumeHeader, 79, 25);
    actionScreen_actVolumeHeader->fn->setScheme(actionScreen_actVolumeHeader, &BlackScheme);
    actionScreen_actVolumeHeader->fn->setBackgroundType(actionScreen_actVolumeHeader, LE_WIDGET_BACKGROUND_NONE);
    actionScreen_actVolumeHeader->fn->setHAlignment(actionScreen_actVolumeHeader, LE_HALIGN_CENTER);
    actionScreen_actVolumeHeader->fn->setString(actionScreen_actVolumeHeader, (leString*)&string_actVolumeHeaderStr);
    actionScreen_BackGround->fn->addChild(actionScreen_BackGround, (leWidget*)actionScreen_actVolumeHeader);

    actionScreen_avLevLabel = leLabelWidget_New();
    actionScreen_avLevLabel->fn->setPosition(actionScreen_avLevLabel, 348, 44);
    actionScreen_avLevLabel->fn->setSize(actionScreen_avLevLabel, 132, 79);
    actionScreen_avLevLabel->fn->setVisible(actionScreen_avLevLabel, LE_FALSE);
    actionScreen_avLevLabel->fn->setScheme(actionScreen_avLevLabel, &BlackScheme);
    actionScreen_avLevLabel->fn->setBackgroundType(actionScreen_avLevLabel, LE_WIDGET_BACKGROUND_NONE);
    actionScreen_avLevLabel->fn->setHAlignment(actionScreen_avLevLabel, LE_HALIGN_CENTER);
    actionScreen_avLevLabel->fn->setString(actionScreen_avLevLabel, (leString*)&string_AV_100);
    actionScreen_BackGround->fn->addChild(actionScreen_BackGround, (leWidget*)actionScreen_avLevLabel);

    actionScreen_actCurLevel = leLabelWidget_New();
    actionScreen_actCurLevel->fn->setPosition(actionScreen_actCurLevel, 362, 41);
    actionScreen_actCurLevel->fn->setSize(actionScreen_actCurLevel, 118, 81);
    actionScreen_actCurLevel->fn->setScheme(actionScreen_actCurLevel, &BlackScheme);
    actionScreen_actCurLevel->fn->setBackgroundType(actionScreen_actCurLevel, LE_WIDGET_BACKGROUND_NONE);
    actionScreen_actCurLevel->fn->setHAlignment(actionScreen_actCurLevel, LE_HALIGN_CENTER);
    actionScreen_actCurLevel->fn->setString(actionScreen_actCurLevel, (leString*)&string_curLevelStr);
    actionScreen_BackGround->fn->addChild(actionScreen_BackGround, (leWidget*)actionScreen_actCurLevel);

    actionScreen_actMuteBut = leButtonWidget_New();
    actionScreen_actMuteBut->fn->setPosition(actionScreen_actMuteBut, 250, 236);
    actionScreen_actMuteBut->fn->setSize(actionScreen_actMuteBut, 100, 27);
    actionScreen_actMuteBut->fn->setScheme(actionScreen_actMuteBut, &BlackScheme);
    actionScreen_actMuteBut->fn->setVAlignment(actionScreen_actMuteBut, LE_VALIGN_TOP);
    actionScreen_actMuteBut->fn->setMargins(actionScreen_actMuteBut, 4, 1, 4, 4);
    actionScreen_actMuteBut->fn->setString(actionScreen_actMuteBut, (leString*)&string_actMuteButtonStr);
    actionScreen_actMuteBut->fn->setPressedEventCallback(actionScreen_actMuteBut, event_actionScreen_actMuteBut_OnPressed);
    actionScreen_BackGround->fn->addChild(actionScreen_BackGround, (leWidget*)actionScreen_actMuteBut);

    actionScreen_actMenuBut = leButtonWidget_New();
    actionScreen_actMenuBut->fn->setPosition(actionScreen_actMenuBut, 129, 236);
    actionScreen_actMenuBut->fn->setSize(actionScreen_actMenuBut, 100, 27);
    actionScreen_actMenuBut->fn->setScheme(actionScreen_actMenuBut, &BlackScheme);
    actionScreen_actMenuBut->fn->setVAlignment(actionScreen_actMenuBut, LE_VALIGN_TOP);
    actionScreen_actMenuBut->fn->setMargins(actionScreen_actMenuBut, 4, 1, 4, 4);
    actionScreen_actMenuBut->fn->setString(actionScreen_actMenuBut, (leString*)&string_actMenuButtonStr);
    actionScreen_actMenuBut->fn->setImagePosition(actionScreen_actMenuBut, LE_RELATIVE_POSITION_BEHIND);
    actionScreen_actMenuBut->fn->setPressedEventCallback(actionScreen_actMenuBut, event_actionScreen_actMenuBut_OnPressed);
    actionScreen_BackGround->fn->addChild(actionScreen_BackGround, (leWidget*)actionScreen_actMenuBut);

    actionScreen_actAnaDigiSelectionBut = leButtonWidget_New();
    actionScreen_actAnaDigiSelectionBut->fn->setPosition(actionScreen_actAnaDigiSelectionBut, 185, 16);
    actionScreen_actAnaDigiSelectionBut->fn->setSize(actionScreen_actAnaDigiSelectionBut, 111, 51);
    actionScreen_actAnaDigiSelectionBut->fn->setVisible(actionScreen_actAnaDigiSelectionBut, LE_FALSE);
    actionScreen_actAnaDigiSelectionBut->fn->setBackgroundType(actionScreen_actAnaDigiSelectionBut, LE_WIDGET_BACKGROUND_NONE);
    actionScreen_actAnaDigiSelectionBut->fn->setBorderType(actionScreen_actAnaDigiSelectionBut, LE_WIDGET_BORDER_NONE);
    actionScreen_actAnaDigiSelectionBut->fn->setToggleable(actionScreen_actAnaDigiSelectionBut, LE_TRUE);
    actionScreen_actAnaDigiSelectionBut->fn->setPressedImage(actionScreen_actAnaDigiSelectionBut, (leImage*)&actAnaDigiButtonImg);
    actionScreen_actAnaDigiSelectionBut->fn->setReleasedImage(actionScreen_actAnaDigiSelectionBut, (leImage*)&actAnaDigiButtonImg);
    actionScreen_actAnaDigiSelectionBut->fn->setImagePosition(actionScreen_actAnaDigiSelectionBut, LE_RELATIVE_POSITION_BEHIND);
    actionScreen_actAnaDigiSelectionBut->fn->setPressedOffset(actionScreen_actAnaDigiSelectionBut, 0);
    actionScreen_actAnaDigiSelectionBut->fn->setPressedEventCallback(actionScreen_actAnaDigiSelectionBut, event_actionScreen_actAnaDigiSelectionBut_OnPressed);
    actionScreen_actAnaDigiSelectionBut->fn->setReleasedEventCallback(actionScreen_actAnaDigiSelectionBut, event_actionScreen_actAnaDigiSelectionBut_OnReleased);
    actionScreen_BackGround->fn->addChild(actionScreen_BackGround, (leWidget*)actionScreen_actAnaDigiSelectionBut);

    actionScreen_actVolumeButImg = leImageWidget_New();
    actionScreen_actVolumeButImg->fn->setPosition(actionScreen_actVolumeButImg, 383, 145);
    actionScreen_actVolumeButImg->fn->setSize(actionScreen_actVolumeButImg, 75, 103);
    actionScreen_actVolumeButImg->fn->setScheme(actionScreen_actVolumeButImg, &BlackScheme);
    actionScreen_actVolumeButImg->fn->setBorderType(actionScreen_actVolumeButImg, LE_WIDGET_BORDER_NONE);
    actionScreen_actVolumeButImg->fn->setImage(actionScreen_actVolumeButImg, (leImage*)&ActVolButtons2);
    actionScreen_BackGround->fn->addChild(actionScreen_BackGround, (leWidget*)actionScreen_actVolumeButImg);

    actionScreen_actVolPlusBut = leButtonWidget_New();
    actionScreen_actVolPlusBut->fn->setPosition(actionScreen_actVolPlusBut, 1, -20);
    actionScreen_actVolPlusBut->fn->setSize(actionScreen_actVolPlusBut, 74, 60);
    actionScreen_actVolPlusBut->fn->setAlphaEnabled(actionScreen_actVolPlusBut, LE_TRUE);
    actionScreen_actVolPlusBut->fn->setAlphaAmount(actionScreen_actVolPlusBut, 0);
    actionScreen_actVolPlusBut->fn->setBackgroundType(actionScreen_actVolPlusBut, LE_WIDGET_BACKGROUND_NONE);
    actionScreen_actVolPlusBut->fn->setBorderType(actionScreen_actVolPlusBut, LE_WIDGET_BORDER_NONE);
    actionScreen_actVolPlusBut->fn->setPressedEventCallback(actionScreen_actVolPlusBut, event_actionScreen_actVolPlusBut_OnPressed);
    actionScreen_actVolPlusBut->fn->setReleasedEventCallback(actionScreen_actVolPlusBut, event_actionScreen_actVolPlusBut_OnReleased);
    actionScreen_actVolumeButImg->fn->addChild(actionScreen_actVolumeButImg, (leWidget*)actionScreen_actVolPlusBut);

    actionScreen_actVolMinusBut = leButtonWidget_New();
    actionScreen_actVolMinusBut->fn->setPosition(actionScreen_actVolMinusBut, 0, 62);
    actionScreen_actVolMinusBut->fn->setSize(actionScreen_actVolMinusBut, 75, 61);
    actionScreen_actVolMinusBut->fn->setAlphaEnabled(actionScreen_actVolMinusBut, LE_TRUE);
    actionScreen_actVolMinusBut->fn->setAlphaAmount(actionScreen_actVolMinusBut, 0);
    actionScreen_actVolMinusBut->fn->setScheme(actionScreen_actVolMinusBut, &BlackScheme);
    actionScreen_actVolMinusBut->fn->setBackgroundType(actionScreen_actVolMinusBut, LE_WIDGET_BACKGROUND_NONE);
    actionScreen_actVolMinusBut->fn->setBorderType(actionScreen_actVolMinusBut, LE_WIDGET_BORDER_NONE);
    actionScreen_actVolMinusBut->fn->setPressedEventCallback(actionScreen_actVolMinusBut, event_actionScreen_actVolMinusBut_OnPressed);
    actionScreen_actVolMinusBut->fn->setReleasedEventCallback(actionScreen_actVolMinusBut, event_actionScreen_actVolMinusBut_OnReleased);
    actionScreen_actVolumeButImg->fn->addChild(actionScreen_actVolumeButImg, (leWidget*)actionScreen_actVolMinusBut);

    actionScreen_anaInpNamePanel = leWidget_New();
    actionScreen_anaInpNamePanel->fn->setPosition(actionScreen_anaInpNamePanel, 8, 11);
    actionScreen_anaInpNamePanel->fn->setSize(actionScreen_anaInpNamePanel, 177, 219);
    actionScreen_anaInpNamePanel->fn->setScheme(actionScreen_anaInpNamePanel, &BlackScheme);
    actionScreen_anaInpNamePanel->fn->setBackgroundType(actionScreen_anaInpNamePanel, LE_WIDGET_BACKGROUND_NONE);
    root0->fn->addChild(root0, (leWidget*)actionScreen_anaInpNamePanel);

    actionScreen_anaInpNameHeader = leLabelWidget_New();
    actionScreen_anaInpNameHeader->fn->setPosition(actionScreen_anaInpNameHeader, 2, 6);
    actionScreen_anaInpNameHeader->fn->setSize(actionScreen_anaInpNameHeader, 171, 25);
    actionScreen_anaInpNameHeader->fn->setScheme(actionScreen_anaInpNameHeader, &BlackScheme);
    actionScreen_anaInpNameHeader->fn->setString(actionScreen_anaInpNameHeader, (leString*)&string_actAnalogInpHeader);
    actionScreen_anaInpNamePanel->fn->addChild(actionScreen_anaInpNamePanel, (leWidget*)actionScreen_anaInpNameHeader);

    actionScreen_anaInp1But = leButtonWidget_New();
    actionScreen_anaInp1But->fn->setPosition(actionScreen_anaInp1But, 1, 35);
    actionScreen_anaInp1But->fn->setSize(actionScreen_anaInp1But, 166, 25);
    actionScreen_anaInp1But->fn->setScheme(actionScreen_anaInp1But, &BlackScheme);
    actionScreen_anaInp1But->fn->setBorderType(actionScreen_anaInp1But, LE_WIDGET_BORDER_NONE);
    actionScreen_anaInp1But->fn->setHAlignment(actionScreen_anaInp1But, LE_HALIGN_LEFT);
    actionScreen_anaInp1But->fn->setToggleable(actionScreen_anaInp1But, LE_TRUE);
    actionScreen_anaInp1But->fn->setString(actionScreen_anaInp1But, (leString*)&string_Inp1Name);
    actionScreen_anaInp1But->fn->setPressedImage(actionScreen_anaInp1But, (leImage*)&smallSelected2);
    actionScreen_anaInp1But->fn->setReleasedImage(actionScreen_anaInp1But, (leImage*)&smallNotSelected3);
    actionScreen_anaInp1But->fn->setImageMargin(actionScreen_anaInp1But, 4);
    actionScreen_anaInp1But->fn->setPressedOffset(actionScreen_anaInp1But, 0);
    actionScreen_anaInp1But->fn->setPressedEventCallback(actionScreen_anaInp1But, event_actionScreen_anaInp1But_OnPressed);
    actionScreen_anaInpNamePanel->fn->addChild(actionScreen_anaInpNamePanel, (leWidget*)actionScreen_anaInp1But);

    actionScreen_anaInp2But = leButtonWidget_New();
    actionScreen_anaInp2But->fn->setPosition(actionScreen_anaInp2But, 1, 66);
    actionScreen_anaInp2But->fn->setSize(actionScreen_anaInp2But, 166, 25);
    actionScreen_anaInp2But->fn->setScheme(actionScreen_anaInp2But, &BlackScheme);
    actionScreen_anaInp2But->fn->setBorderType(actionScreen_anaInp2But, LE_WIDGET_BORDER_NONE);
    actionScreen_anaInp2But->fn->setHAlignment(actionScreen_anaInp2But, LE_HALIGN_LEFT);
    actionScreen_anaInp2But->fn->setToggleable(actionScreen_anaInp2But, LE_TRUE);
    actionScreen_anaInp2But->fn->setString(actionScreen_anaInp2But, (leString*)&string_Inp2Name);
    actionScreen_anaInp2But->fn->setPressedImage(actionScreen_anaInp2But, (leImage*)&smallSelected2);
    actionScreen_anaInp2But->fn->setReleasedImage(actionScreen_anaInp2But, (leImage*)&smallNotSelected3);
    actionScreen_anaInp2But->fn->setImageMargin(actionScreen_anaInp2But, 4);
    actionScreen_anaInp2But->fn->setPressedOffset(actionScreen_anaInp2But, 0);
    actionScreen_anaInp2But->fn->setPressedEventCallback(actionScreen_anaInp2But, event_actionScreen_anaInp2But_OnPressed);
    actionScreen_anaInpNamePanel->fn->addChild(actionScreen_anaInpNamePanel, (leWidget*)actionScreen_anaInp2But);

    actionScreen_anaInp3But = leButtonWidget_New();
    actionScreen_anaInp3But->fn->setPosition(actionScreen_anaInp3But, 1, 97);
    actionScreen_anaInp3But->fn->setSize(actionScreen_anaInp3But, 166, 25);
    actionScreen_anaInp3But->fn->setScheme(actionScreen_anaInp3But, &BlackScheme);
    actionScreen_anaInp3But->fn->setBorderType(actionScreen_anaInp3But, LE_WIDGET_BORDER_NONE);
    actionScreen_anaInp3But->fn->setHAlignment(actionScreen_anaInp3But, LE_HALIGN_LEFT);
    actionScreen_anaInp3But->fn->setToggleable(actionScreen_anaInp3But, LE_TRUE);
    actionScreen_anaInp3But->fn->setString(actionScreen_anaInp3But, (leString*)&string_inp3Name);
    actionScreen_anaInp3But->fn->setPressedImage(actionScreen_anaInp3But, (leImage*)&smallSelected2);
    actionScreen_anaInp3But->fn->setReleasedImage(actionScreen_anaInp3But, (leImage*)&smallNotSelected3);
    actionScreen_anaInp3But->fn->setImageMargin(actionScreen_anaInp3But, 4);
    actionScreen_anaInp3But->fn->setPressedOffset(actionScreen_anaInp3But, 0);
    actionScreen_anaInp3But->fn->setPressedEventCallback(actionScreen_anaInp3But, event_actionScreen_anaInp3But_OnPressed);
    actionScreen_anaInpNamePanel->fn->addChild(actionScreen_anaInpNamePanel, (leWidget*)actionScreen_anaInp3But);

    actionScreen_anaInp4But = leButtonWidget_New();
    actionScreen_anaInp4But->fn->setPosition(actionScreen_anaInp4But, 1, 128);
    actionScreen_anaInp4But->fn->setSize(actionScreen_anaInp4But, 166, 25);
    actionScreen_anaInp4But->fn->setScheme(actionScreen_anaInp4But, &BlackScheme);
    actionScreen_anaInp4But->fn->setBorderType(actionScreen_anaInp4But, LE_WIDGET_BORDER_NONE);
    actionScreen_anaInp4But->fn->setHAlignment(actionScreen_anaInp4But, LE_HALIGN_LEFT);
    actionScreen_anaInp4But->fn->setToggleable(actionScreen_anaInp4But, LE_TRUE);
    actionScreen_anaInp4But->fn->setString(actionScreen_anaInp4But, (leString*)&string_Inp4Name);
    actionScreen_anaInp4But->fn->setPressedImage(actionScreen_anaInp4But, (leImage*)&smallSelected2);
    actionScreen_anaInp4But->fn->setReleasedImage(actionScreen_anaInp4But, (leImage*)&smallNotSelected3);
    actionScreen_anaInp4But->fn->setImageMargin(actionScreen_anaInp4But, 4);
    actionScreen_anaInp4But->fn->setPressedOffset(actionScreen_anaInp4But, 0);
    actionScreen_anaInp4But->fn->setPressedEventCallback(actionScreen_anaInp4But, event_actionScreen_anaInp4But_OnPressed);
    actionScreen_anaInpNamePanel->fn->addChild(actionScreen_anaInpNamePanel, (leWidget*)actionScreen_anaInp4But);

    actionScreen_anaInp5But = leButtonWidget_New();
    actionScreen_anaInp5But->fn->setPosition(actionScreen_anaInp5But, 1, 159);
    actionScreen_anaInp5But->fn->setSize(actionScreen_anaInp5But, 166, 25);
    actionScreen_anaInp5But->fn->setScheme(actionScreen_anaInp5But, &BlackScheme);
    actionScreen_anaInp5But->fn->setBorderType(actionScreen_anaInp5But, LE_WIDGET_BORDER_NONE);
    actionScreen_anaInp5But->fn->setHAlignment(actionScreen_anaInp5But, LE_HALIGN_LEFT);
    actionScreen_anaInp5But->fn->setToggleable(actionScreen_anaInp5But, LE_TRUE);
    actionScreen_anaInp5But->fn->setString(actionScreen_anaInp5But, (leString*)&string_Inp5Name);
    actionScreen_anaInp5But->fn->setPressedImage(actionScreen_anaInp5But, (leImage*)&smallSelected2);
    actionScreen_anaInp5But->fn->setReleasedImage(actionScreen_anaInp5But, (leImage*)&smallNotSelected3);
    actionScreen_anaInp5But->fn->setImageMargin(actionScreen_anaInp5But, 4);
    actionScreen_anaInp5But->fn->setPressedOffset(actionScreen_anaInp5But, 0);
    actionScreen_anaInp5But->fn->setPressedEventCallback(actionScreen_anaInp5But, event_actionScreen_anaInp5But_OnPressed);
    actionScreen_anaInpNamePanel->fn->addChild(actionScreen_anaInpNamePanel, (leWidget*)actionScreen_anaInp5But);

    actionScreen_anaInp6But = leButtonWidget_New();
    actionScreen_anaInp6But->fn->setPosition(actionScreen_anaInp6But, 1, 190);
    actionScreen_anaInp6But->fn->setSize(actionScreen_anaInp6But, 166, 25);
    actionScreen_anaInp6But->fn->setEnabled(actionScreen_anaInp6But, LE_FALSE);
    actionScreen_anaInp6But->fn->setVisible(actionScreen_anaInp6But, LE_FALSE);
    actionScreen_anaInp6But->fn->setScheme(actionScreen_anaInp6But, &BlackScheme);
    actionScreen_anaInp6But->fn->setBorderType(actionScreen_anaInp6But, LE_WIDGET_BORDER_NONE);
    actionScreen_anaInp6But->fn->setHAlignment(actionScreen_anaInp6But, LE_HALIGN_LEFT);
    actionScreen_anaInp6But->fn->setToggleable(actionScreen_anaInp6But, LE_TRUE);
    actionScreen_anaInp6But->fn->setString(actionScreen_anaInp6But, (leString*)&string_Inp6Name);
    actionScreen_anaInp6But->fn->setPressedImage(actionScreen_anaInp6But, (leImage*)&smallSelected2);
    actionScreen_anaInp6But->fn->setReleasedImage(actionScreen_anaInp6But, (leImage*)&smallNotSelected3);
    actionScreen_anaInp6But->fn->setImageMargin(actionScreen_anaInp6But, 4);
    actionScreen_anaInp6But->fn->setPressedOffset(actionScreen_anaInp6But, 0);
    actionScreen_anaInp6But->fn->setPressedEventCallback(actionScreen_anaInp6But, event_actionScreen_anaInp6But_OnPressed);
    actionScreen_anaInpNamePanel->fn->addChild(actionScreen_anaInpNamePanel, (leWidget*)actionScreen_anaInp6But);

    actionScreen_digiInpNamePanel = leWidget_New();
    actionScreen_digiInpNamePanel->fn->setPosition(actionScreen_digiInpNamePanel, 8, 11);
    actionScreen_digiInpNamePanel->fn->setSize(actionScreen_digiInpNamePanel, 177, 219);
    actionScreen_digiInpNamePanel->fn->setEnabled(actionScreen_digiInpNamePanel, LE_FALSE);
    actionScreen_digiInpNamePanel->fn->setVisible(actionScreen_digiInpNamePanel, LE_FALSE);
    actionScreen_digiInpNamePanel->fn->setScheme(actionScreen_digiInpNamePanel, &BlackScheme);
    root0->fn->addChild(root0, (leWidget*)actionScreen_digiInpNamePanel);

    actionScreen_digiInpNameHeader = leLabelWidget_New();
    actionScreen_digiInpNameHeader->fn->setPosition(actionScreen_digiInpNameHeader, 2, 6);
    actionScreen_digiInpNameHeader->fn->setSize(actionScreen_digiInpNameHeader, 159, 25);
    actionScreen_digiInpNameHeader->fn->setScheme(actionScreen_digiInpNameHeader, &BlackScheme);
    actionScreen_digiInpNameHeader->fn->setString(actionScreen_digiInpNameHeader, (leString*)&string_actDigitalInpHeader);
    actionScreen_digiInpNamePanel->fn->addChild(actionScreen_digiInpNamePanel, (leWidget*)actionScreen_digiInpNameHeader);

    actionScreen_digiInp7But = leButtonWidget_New();
    actionScreen_digiInp7But->fn->setPosition(actionScreen_digiInp7But, 1, 35);
    actionScreen_digiInp7But->fn->setSize(actionScreen_digiInp7But, 170, 25);
    actionScreen_digiInp7But->fn->setScheme(actionScreen_digiInp7But, &BlackScheme);
    actionScreen_digiInp7But->fn->setBorderType(actionScreen_digiInp7But, LE_WIDGET_BORDER_NONE);
    actionScreen_digiInp7But->fn->setHAlignment(actionScreen_digiInp7But, LE_HALIGN_LEFT);
    actionScreen_digiInp7But->fn->setToggleable(actionScreen_digiInp7But, LE_TRUE);
    actionScreen_digiInp7But->fn->setString(actionScreen_digiInp7But, (leString*)&string_Inp7Name);
    actionScreen_digiInp7But->fn->setPressedImage(actionScreen_digiInp7But, (leImage*)&smallSelected2);
    actionScreen_digiInp7But->fn->setReleasedImage(actionScreen_digiInp7But, (leImage*)&smallNotSelected3);
    actionScreen_digiInp7But->fn->setImageMargin(actionScreen_digiInp7But, 4);
    actionScreen_digiInp7But->fn->setPressedOffset(actionScreen_digiInp7But, 0);
    actionScreen_digiInp7But->fn->setPressedEventCallback(actionScreen_digiInp7But, event_actionScreen_digiInp7But_OnPressed);
    actionScreen_digiInpNamePanel->fn->addChild(actionScreen_digiInpNamePanel, (leWidget*)actionScreen_digiInp7But);

    actionScreen_digiInp8But = leButtonWidget_New();
    actionScreen_digiInp8But->fn->setPosition(actionScreen_digiInp8But, 1, 66);
    actionScreen_digiInp8But->fn->setSize(actionScreen_digiInp8But, 166, 25);
    actionScreen_digiInp8But->fn->setScheme(actionScreen_digiInp8But, &BlackScheme);
    actionScreen_digiInp8But->fn->setBorderType(actionScreen_digiInp8But, LE_WIDGET_BORDER_NONE);
    actionScreen_digiInp8But->fn->setHAlignment(actionScreen_digiInp8But, LE_HALIGN_LEFT);
    actionScreen_digiInp8But->fn->setToggleable(actionScreen_digiInp8But, LE_TRUE);
    actionScreen_digiInp8But->fn->setString(actionScreen_digiInp8But, (leString*)&string_Inp8Name);
    actionScreen_digiInp8But->fn->setPressedImage(actionScreen_digiInp8But, (leImage*)&smallSelected2);
    actionScreen_digiInp8But->fn->setReleasedImage(actionScreen_digiInp8But, (leImage*)&smallNotSelected3);
    actionScreen_digiInp8But->fn->setImageMargin(actionScreen_digiInp8But, 4);
    actionScreen_digiInp8But->fn->setPressedOffset(actionScreen_digiInp8But, 0);
    actionScreen_digiInp8But->fn->setPressedEventCallback(actionScreen_digiInp8But, event_actionScreen_digiInp8But_OnPressed);
    actionScreen_digiInpNamePanel->fn->addChild(actionScreen_digiInpNamePanel, (leWidget*)actionScreen_digiInp8But);

    actionScreen_digiInp9But = leButtonWidget_New();
    actionScreen_digiInp9But->fn->setPosition(actionScreen_digiInp9But, 1, 97);
    actionScreen_digiInp9But->fn->setSize(actionScreen_digiInp9But, 166, 25);
    actionScreen_digiInp9But->fn->setScheme(actionScreen_digiInp9But, &BlackScheme);
    actionScreen_digiInp9But->fn->setBackgroundType(actionScreen_digiInp9But, LE_WIDGET_BACKGROUND_NONE);
    actionScreen_digiInp9But->fn->setBorderType(actionScreen_digiInp9But, LE_WIDGET_BORDER_NONE);
    actionScreen_digiInp9But->fn->setHAlignment(actionScreen_digiInp9But, LE_HALIGN_LEFT);
    actionScreen_digiInp9But->fn->setToggleable(actionScreen_digiInp9But, LE_TRUE);
    actionScreen_digiInp9But->fn->setString(actionScreen_digiInp9But, (leString*)&string_Inp9Name);
    actionScreen_digiInp9But->fn->setPressedImage(actionScreen_digiInp9But, (leImage*)&smallSelected2);
    actionScreen_digiInp9But->fn->setReleasedImage(actionScreen_digiInp9But, (leImage*)&smallNotSelected3);
    actionScreen_digiInp9But->fn->setImageMargin(actionScreen_digiInp9But, 4);
    actionScreen_digiInp9But->fn->setPressedOffset(actionScreen_digiInp9But, 0);
    actionScreen_digiInp9But->fn->setPressedEventCallback(actionScreen_digiInp9But, event_actionScreen_digiInp9But_OnPressed);
    actionScreen_digiInpNamePanel->fn->addChild(actionScreen_digiInpNamePanel, (leWidget*)actionScreen_digiInp9But);

    actionScreen_digiInp10But = leButtonWidget_New();
    actionScreen_digiInp10But->fn->setPosition(actionScreen_digiInp10But, 1, 128);
    actionScreen_digiInp10But->fn->setSize(actionScreen_digiInp10But, 166, 25);
    actionScreen_digiInp10But->fn->setScheme(actionScreen_digiInp10But, &BlackScheme);
    actionScreen_digiInp10But->fn->setBorderType(actionScreen_digiInp10But, LE_WIDGET_BORDER_NONE);
    actionScreen_digiInp10But->fn->setHAlignment(actionScreen_digiInp10But, LE_HALIGN_LEFT);
    actionScreen_digiInp10But->fn->setToggleable(actionScreen_digiInp10But, LE_TRUE);
    actionScreen_digiInp10But->fn->setString(actionScreen_digiInp10But, (leString*)&string_Inp10Name);
    actionScreen_digiInp10But->fn->setPressedImage(actionScreen_digiInp10But, (leImage*)&smallSelected2);
    actionScreen_digiInp10But->fn->setReleasedImage(actionScreen_digiInp10But, (leImage*)&smallNotSelected3);
    actionScreen_digiInp10But->fn->setImageMargin(actionScreen_digiInp10But, 4);
    actionScreen_digiInp10But->fn->setPressedOffset(actionScreen_digiInp10But, 0);
    actionScreen_digiInp10But->fn->setPressedEventCallback(actionScreen_digiInp10But, event_actionScreen_digiInp10But_OnPressed);
    actionScreen_digiInpNamePanel->fn->addChild(actionScreen_digiInpNamePanel, (leWidget*)actionScreen_digiInp10But);

    actionScreen_digiInp11But = leButtonWidget_New();
    actionScreen_digiInp11But->fn->setPosition(actionScreen_digiInp11But, 1, 159);
    actionScreen_digiInp11But->fn->setSize(actionScreen_digiInp11But, 166, 25);
    actionScreen_digiInp11But->fn->setScheme(actionScreen_digiInp11But, &BlackScheme);
    actionScreen_digiInp11But->fn->setBorderType(actionScreen_digiInp11But, LE_WIDGET_BORDER_NONE);
    actionScreen_digiInp11But->fn->setHAlignment(actionScreen_digiInp11But, LE_HALIGN_LEFT);
    actionScreen_digiInp11But->fn->setToggleable(actionScreen_digiInp11But, LE_TRUE);
    actionScreen_digiInp11But->fn->setString(actionScreen_digiInp11But, (leString*)&string_Inp11Name);
    actionScreen_digiInp11But->fn->setPressedImage(actionScreen_digiInp11But, (leImage*)&smallSelected2);
    actionScreen_digiInp11But->fn->setReleasedImage(actionScreen_digiInp11But, (leImage*)&smallNotSelected3);
    actionScreen_digiInp11But->fn->setImageMargin(actionScreen_digiInp11But, 4);
    actionScreen_digiInp11But->fn->setPressedOffset(actionScreen_digiInp11But, 0);
    actionScreen_digiInp11But->fn->setPressedEventCallback(actionScreen_digiInp11But, event_actionScreen_digiInp11But_OnPressed);
    actionScreen_digiInpNamePanel->fn->addChild(actionScreen_digiInpNamePanel, (leWidget*)actionScreen_digiInp11But);

    actionScreen_digInfoPanel = leWidget_New();
    actionScreen_digInfoPanel->fn->setPosition(actionScreen_digInfoPanel, 185, 80);
    actionScreen_digInfoPanel->fn->setSize(actionScreen_digInfoPanel, 165, 141);
    actionScreen_digInfoPanel->fn->setEnabled(actionScreen_digInfoPanel, LE_FALSE);
    actionScreen_digInfoPanel->fn->setScheme(actionScreen_digInfoPanel, &BlackScheme);
    actionScreen_digInfoPanel->fn->setBackgroundType(actionScreen_digInfoPanel, LE_WIDGET_BACKGROUND_NONE);
    root0->fn->addChild(root0, (leWidget*)actionScreen_digInfoPanel);

    actionScreen_padLockImg = leButtonWidget_New();
    actionScreen_padLockImg->fn->setPosition(actionScreen_padLockImg, 94, 98);
    actionScreen_padLockImg->fn->setSize(actionScreen_padLockImg, 30, 39);
    actionScreen_padLockImg->fn->setEnabled(actionScreen_padLockImg, LE_FALSE);
    actionScreen_padLockImg->fn->setBackgroundType(actionScreen_padLockImg, LE_WIDGET_BACKGROUND_NONE);
    actionScreen_padLockImg->fn->setBorderType(actionScreen_padLockImg, LE_WIDGET_BORDER_NONE);
    actionScreen_padLockImg->fn->setToggleable(actionScreen_padLockImg, LE_TRUE);
    actionScreen_padLockImg->fn->setPressedImage(actionScreen_padLockImg, (leImage*)&PadLockLocked2);
    actionScreen_padLockImg->fn->setReleasedImage(actionScreen_padLockImg, (leImage*)&PadLockUnlocked2);
    actionScreen_padLockImg->fn->setImageMargin(actionScreen_padLockImg, 0);
    actionScreen_padLockImg->fn->setPressedOffset(actionScreen_padLockImg, 0);
    actionScreen_digInfoPanel->fn->addChild(actionScreen_digInfoPanel, (leWidget*)actionScreen_padLockImg);

    actionScreen_digiInfoFSLabel = leLabelWidget_New();
    actionScreen_digiInfoFSLabel->fn->setPosition(actionScreen_digiInfoFSLabel, 1, 5);
    actionScreen_digiInfoFSLabel->fn->setSize(actionScreen_digiInfoFSLabel, 122, 25);
    actionScreen_digiInfoFSLabel->fn->setScheme(actionScreen_digiInfoFSLabel, &BlackScheme);
    actionScreen_digiInfoFSLabel->fn->setString(actionScreen_digiInfoFSLabel, (leString*)&string_actDigiInfoFsStr);
    actionScreen_digInfoPanel->fn->addChild(actionScreen_digInfoPanel, (leWidget*)actionScreen_digiInfoFSLabel);

    actionScreen_digiInfoFilterLabel1 = leLabelWidget_New();
    actionScreen_digiInfoFilterLabel1->fn->setPosition(actionScreen_digiInfoFilterLabel1, 1, 25);
    actionScreen_digiInfoFilterLabel1->fn->setSize(actionScreen_digiInfoFilterLabel1, 158, 25);
    actionScreen_digiInfoFilterLabel1->fn->setScheme(actionScreen_digiInfoFilterLabel1, &BlackScheme);
    actionScreen_digiInfoFilterLabel1->fn->setString(actionScreen_digiInfoFilterLabel1, (leString*)&string_pcmFilt1);
    actionScreen_digInfoPanel->fn->addChild(actionScreen_digInfoPanel, (leWidget*)actionScreen_digiInfoFilterLabel1);

    actionScreen_digiInfoFilterLabel2 = leLabelWidget_New();
    actionScreen_digiInfoFilterLabel2->fn->setPosition(actionScreen_digiInfoFilterLabel2, 1, 45);
    actionScreen_digiInfoFilterLabel2->fn->setSize(actionScreen_digiInfoFilterLabel2, 158, 25);
    actionScreen_digiInfoFilterLabel2->fn->setScheme(actionScreen_digiInfoFilterLabel2, &BlackScheme);
    actionScreen_digiInfoFilterLabel2->fn->setString(actionScreen_digiInfoFilterLabel2, (leString*)&string_MinPhase12);
    actionScreen_digInfoPanel->fn->addChild(actionScreen_digInfoPanel, (leWidget*)actionScreen_digiInfoFilterLabel2);

    actionScreen_digiInfoFilterLabel3 = leLabelWidget_New();
    actionScreen_digiInfoFilterLabel3->fn->setPosition(actionScreen_digiInfoFilterLabel3, 1, 65);
    actionScreen_digiInfoFilterLabel3->fn->setSize(actionScreen_digiInfoFilterLabel3, 161, 25);
    actionScreen_digiInfoFilterLabel3->fn->setScheme(actionScreen_digiInfoFilterLabel3, &BlackScheme);
    actionScreen_digiInfoFilterLabel3->fn->setBackgroundType(actionScreen_digiInfoFilterLabel3, LE_WIDGET_BACKGROUND_NONE);
    actionScreen_digiInfoFilterLabel3->fn->setString(actionScreen_digiInfoFilterLabel3, (leString*)&string_SloRollLoDisp12);
    actionScreen_digInfoPanel->fn->addChild(actionScreen_digInfoPanel, (leWidget*)actionScreen_digiInfoFilterLabel3);

    actionScreen_dsdLpOff = leLabelWidget_New();
    actionScreen_dsdLpOff->fn->setPosition(actionScreen_dsdLpOff, 1, 25);
    actionScreen_dsdLpOff->fn->setSize(actionScreen_dsdLpOff, 158, 25);
    actionScreen_dsdLpOff->fn->setVisible(actionScreen_dsdLpOff, LE_FALSE);
    actionScreen_dsdLpOff->fn->setScheme(actionScreen_dsdLpOff, &BlackScheme);
    actionScreen_dsdLpOff->fn->setString(actionScreen_dsdLpOff, (leString*)&string_dsdLpOff12);
    actionScreen_digInfoPanel->fn->addChild(actionScreen_digInfoPanel, (leWidget*)actionScreen_dsdLpOff);

    actionScreen_dsdLpOn = leLabelWidget_New();
    actionScreen_dsdLpOn->fn->setPosition(actionScreen_dsdLpOn, 1, 25);
    actionScreen_dsdLpOn->fn->setSize(actionScreen_dsdLpOn, 158, 25);
    actionScreen_dsdLpOn->fn->setVisible(actionScreen_dsdLpOn, LE_FALSE);
    actionScreen_dsdLpOn->fn->setScheme(actionScreen_dsdLpOn, &BlackScheme);
    actionScreen_dsdLpOn->fn->setString(actionScreen_dsdLpOn, (leString*)&string_dsdLpOn12);
    actionScreen_digInfoPanel->fn->addChild(actionScreen_digInfoPanel, (leWidget*)actionScreen_dsdLpOn);

    actionScreen_gain0db = leLabelWidget_New();
    actionScreen_gain0db->fn->setPosition(actionScreen_gain0db, 1, 85);
    actionScreen_gain0db->fn->setSize(actionScreen_gain0db, 83, 25);
    actionScreen_gain0db->fn->setScheme(actionScreen_gain0db, &BlackScheme);
    actionScreen_gain0db->fn->setString(actionScreen_gain0db, (leString*)&string_gain0dB_12);
    actionScreen_digInfoPanel->fn->addChild(actionScreen_digInfoPanel, (leWidget*)actionScreen_gain0db);

    actionScreen_gainMinus6dB = leLabelWidget_New();
    actionScreen_gainMinus6dB->fn->setPosition(actionScreen_gainMinus6dB, 1, 85);
    actionScreen_gainMinus6dB->fn->setSize(actionScreen_gainMinus6dB, 83, 25);
    actionScreen_gainMinus6dB->fn->setScheme(actionScreen_gainMinus6dB, &BlackScheme);
    actionScreen_gainMinus6dB->fn->setString(actionScreen_gainMinus6dB, (leString*)&string_gainMinus6dB_12);
    actionScreen_digInfoPanel->fn->addChild(actionScreen_digInfoPanel, (leWidget*)actionScreen_gainMinus6dB);

    actionScreen_batteryPanel = leWidget_New();
    actionScreen_batteryPanel->fn->setPosition(actionScreen_batteryPanel, 134, 98);
    actionScreen_batteryPanel->fn->setSize(actionScreen_batteryPanel, 19, 37);
    actionScreen_batteryPanel->fn->setScheme(actionScreen_batteryPanel, &BlackScheme);
    actionScreen_digInfoPanel->fn->addChild(actionScreen_digInfoPanel, (leWidget*)actionScreen_batteryPanel);

    actionScreen_BattCharged = leImageWidget_New();
    actionScreen_BattCharged->fn->setPosition(actionScreen_BattCharged, -6, 2);
    actionScreen_BattCharged->fn->setSize(actionScreen_BattCharged, 30, 36);
    actionScreen_BattCharged->fn->setBackgroundType(actionScreen_BattCharged, LE_WIDGET_BACKGROUND_NONE);
    actionScreen_BattCharged->fn->setBorderType(actionScreen_BattCharged, LE_WIDGET_BORDER_NONE);
    actionScreen_BattCharged->fn->setImage(actionScreen_BattCharged, (leImage*)&BatteriCharged2);
    actionScreen_batteryPanel->fn->addChild(actionScreen_batteryPanel, (leWidget*)actionScreen_BattCharged);

    actionScreen_BattCharging = leImageWidget_New();
    actionScreen_BattCharging->fn->setPosition(actionScreen_BattCharging, -6, 2);
    actionScreen_BattCharging->fn->setSize(actionScreen_BattCharging, 30, 36);
    actionScreen_BattCharging->fn->setBackgroundType(actionScreen_BattCharging, LE_WIDGET_BACKGROUND_NONE);
    actionScreen_BattCharging->fn->setBorderType(actionScreen_BattCharging, LE_WIDGET_BORDER_NONE);
    actionScreen_BattCharging->fn->setImage(actionScreen_BattCharging, (leImage*)&BatteriCharging2);
    actionScreen_batteryPanel->fn->addChild(actionScreen_batteryPanel, (leWidget*)actionScreen_BattCharging);

    actionScreen_dispOnButton = leButtonWidget_New();
    actionScreen_dispOnButton->fn->setPosition(actionScreen_dispOnButton, -1, 0);
    actionScreen_dispOnButton->fn->setSize(actionScreen_dispOnButton, 478, 270);
    actionScreen_dispOnButton->fn->setEnabled(actionScreen_dispOnButton, LE_FALSE);
    actionScreen_dispOnButton->fn->setVisible(actionScreen_dispOnButton, LE_FALSE);
    actionScreen_dispOnButton->fn->setScheme(actionScreen_dispOnButton, &BlackScheme);
    actionScreen_dispOnButton->fn->setBackgroundType(actionScreen_dispOnButton, LE_WIDGET_BACKGROUND_NONE);
    actionScreen_dispOnButton->fn->setBorderType(actionScreen_dispOnButton, LE_WIDGET_BORDER_NONE);
    actionScreen_dispOnButton->fn->setPressedEventCallback(actionScreen_dispOnButton, event_actionScreen_dispOnButton_OnPressed);
    root0->fn->addChild(root0, (leWidget*)actionScreen_dispOnButton);

    actionScreen_fanErrorImg = leImageWidget_New();
    actionScreen_fanErrorImg->fn->setPosition(actionScreen_fanErrorImg, 301, 19);
    actionScreen_fanErrorImg->fn->setSize(actionScreen_fanErrorImg, 54, 78);
    actionScreen_fanErrorImg->fn->setVisible(actionScreen_fanErrorImg, LE_FALSE);
    actionScreen_fanErrorImg->fn->setScheme(actionScreen_fanErrorImg, &BlackScheme);
    actionScreen_fanErrorImg->fn->setBackgroundType(actionScreen_fanErrorImg, LE_WIDGET_BACKGROUND_NONE);
    actionScreen_fanErrorImg->fn->setBorderType(actionScreen_fanErrorImg, LE_WIDGET_BORDER_NONE);
    actionScreen_fanErrorImg->fn->setImage(actionScreen_fanErrorImg, (leImage*)&fanError);
    root0->fn->addChild(root0, (leWidget*)actionScreen_fanErrorImg);

    leAddRootWidget(root0, 0);
    leSetLayerColorMode(0, LE_COLOR_MODE_RGB_565);

    actionScreen_OnShow(); // raise event

    showing = LE_TRUE;

    return LE_SUCCESS;
}

void screenUpdate_actionScreen(void)
{
    root0->fn->setSize(root0, root0->rect.width, root0->rect.height);
}

void screenHide_actionScreen(void)
{

    leRemoveRootWidget(root0, 0);
    leWidget_Delete(root0);
    root0 = NULL;

    actionScreen_BackGround = NULL;
    actionScreen_anaInpNamePanel = NULL;
    actionScreen_digiInpNamePanel = NULL;
    actionScreen_digInfoPanel = NULL;
    actionScreen_dispOnButton = NULL;
    actionScreen_fanErrorImg = NULL;
    actionScreen_actionMuteKryds = NULL;
    actionScreen_actVolumeHeader = NULL;
    actionScreen_avLevLabel = NULL;
    actionScreen_actCurLevel = NULL;
    actionScreen_actMuteBut = NULL;
    actionScreen_actMenuBut = NULL;
    actionScreen_actAnaDigiSelectionBut = NULL;
    actionScreen_actVolumeButImg = NULL;
    actionScreen_actVolPlusBut = NULL;
    actionScreen_actVolMinusBut = NULL;
    actionScreen_anaInpNameHeader = NULL;
    actionScreen_anaInp1But = NULL;
    actionScreen_anaInp2But = NULL;
    actionScreen_anaInp3But = NULL;
    actionScreen_anaInp4But = NULL;
    actionScreen_anaInp5But = NULL;
    actionScreen_anaInp6But = NULL;
    actionScreen_digiInpNameHeader = NULL;
    actionScreen_digiInp7But = NULL;
    actionScreen_digiInp8But = NULL;
    actionScreen_digiInp9But = NULL;
    actionScreen_digiInp10But = NULL;
    actionScreen_digiInp11But = NULL;
    actionScreen_padLockImg = NULL;
    actionScreen_digiInfoFSLabel = NULL;
    actionScreen_digiInfoFilterLabel1 = NULL;
    actionScreen_digiInfoFilterLabel2 = NULL;
    actionScreen_digiInfoFilterLabel3 = NULL;
    actionScreen_dsdLpOff = NULL;
    actionScreen_dsdLpOn = NULL;
    actionScreen_gain0db = NULL;
    actionScreen_gainMinus6dB = NULL;
    actionScreen_batteryPanel = NULL;
    actionScreen_BattCharged = NULL;
    actionScreen_BattCharging = NULL;


    showing = LE_FALSE;
}

void screenDestroy_actionScreen(void)
{
    if(initialized == LE_FALSE)
        return;

    initialized = LE_FALSE;
}

leWidget* screenGetRoot_actionScreen(uint32_t lyrIdx)
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

