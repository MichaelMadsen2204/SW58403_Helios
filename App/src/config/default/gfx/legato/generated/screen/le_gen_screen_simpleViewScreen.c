#include "gfx/legato/generated/screen/le_gen_screen_simpleViewScreen.h"

// screen member widget declarations
static leWidget* root0;

leWidget* simpleViewScreen_background;
leWidget* simpleViewScreen_batteryPanel;
leImageWidget* simpleViewScreen_fanErrorImg;
leImageWidget* simpleViewScreen_smpleViewMuteKryds;
leLabelWidget* simpleViewScreen_simpleViewVolHeader;
leLabelWidget* simpleViewScreen_simpleViewCurLevelLabel;
leLabelWidget* simpleViewScreen_avLevLabel;
leLabelWidget* simpleViewScreen_smpleViewInputHeaderLabel;
leLabelWidget* simpleViewScreen_simpleViewInputNameLabel;
leButtonWidget* simpleViewScreen_simpleViewAnyTouchBut;
leImageWidget* simpleViewScreen_BattCharged;
leImageWidget* simpleViewScreen_BattCharging;

static leBool initialized = LE_FALSE;
static leBool showing = LE_FALSE;

leResult screenInit_simpleViewScreen(void)
{
    if(initialized == LE_TRUE)
        return LE_FAILURE;

    initialized = LE_TRUE;

    return LE_SUCCESS;
}

leResult screenShow_simpleViewScreen(void)
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

    simpleViewScreen_background = leWidget_New();
    simpleViewScreen_background->fn->setPosition(simpleViewScreen_background, 0, 0);
    simpleViewScreen_background->fn->setSize(simpleViewScreen_background, 480, 272);
    simpleViewScreen_background->fn->setScheme(simpleViewScreen_background, &BlackScheme);
    root0->fn->addChild(root0, (leWidget*)simpleViewScreen_background);

    simpleViewScreen_smpleViewMuteKryds = leImageWidget_New();
    simpleViewScreen_smpleViewMuteKryds->fn->setPosition(simpleViewScreen_smpleViewMuteKryds, 182, 33);
    simpleViewScreen_smpleViewMuteKryds->fn->setSize(simpleViewScreen_smpleViewMuteKryds, 115, 106);
    simpleViewScreen_smpleViewMuteKryds->fn->setVisible(simpleViewScreen_smpleViewMuteKryds, LE_FALSE);
    simpleViewScreen_smpleViewMuteKryds->fn->setBorderType(simpleViewScreen_smpleViewMuteKryds, LE_WIDGET_BORDER_NONE);
    simpleViewScreen_smpleViewMuteKryds->fn->setImage(simpleViewScreen_smpleViewMuteKryds, (leImage*)&actionMuteKryds118x118);
    simpleViewScreen_background->fn->addChild(simpleViewScreen_background, (leWidget*)simpleViewScreen_smpleViewMuteKryds);

    simpleViewScreen_simpleViewVolHeader = leLabelWidget_New();
    simpleViewScreen_simpleViewVolHeader->fn->setPosition(simpleViewScreen_simpleViewVolHeader, 188, 15);
    simpleViewScreen_simpleViewVolHeader->fn->setScheme(simpleViewScreen_simpleViewVolHeader, &BlackScheme);
    simpleViewScreen_simpleViewVolHeader->fn->setBackgroundType(simpleViewScreen_simpleViewVolHeader, LE_WIDGET_BACKGROUND_NONE);
    simpleViewScreen_simpleViewVolHeader->fn->setHAlignment(simpleViewScreen_simpleViewVolHeader, LE_HALIGN_CENTER);
    simpleViewScreen_simpleViewVolHeader->fn->setString(simpleViewScreen_simpleViewVolHeader, (leString*)&string_volSettingVolStr);
    simpleViewScreen_background->fn->addChild(simpleViewScreen_background, (leWidget*)simpleViewScreen_simpleViewVolHeader);

    simpleViewScreen_simpleViewCurLevelLabel = leLabelWidget_New();
    simpleViewScreen_simpleViewCurLevelLabel->fn->setPosition(simpleViewScreen_simpleViewCurLevelLabel, 180, 31);
    simpleViewScreen_simpleViewCurLevelLabel->fn->setSize(simpleViewScreen_simpleViewCurLevelLabel, 120, 100);
    simpleViewScreen_simpleViewCurLevelLabel->fn->setScheme(simpleViewScreen_simpleViewCurLevelLabel, &BlackScheme);
    simpleViewScreen_simpleViewCurLevelLabel->fn->setBackgroundType(simpleViewScreen_simpleViewCurLevelLabel, LE_WIDGET_BACKGROUND_NONE);
    simpleViewScreen_simpleViewCurLevelLabel->fn->setHAlignment(simpleViewScreen_simpleViewCurLevelLabel, LE_HALIGN_CENTER);
    simpleViewScreen_simpleViewCurLevelLabel->fn->setString(simpleViewScreen_simpleViewCurLevelLabel, (leString*)&string_curLevelStr);
    simpleViewScreen_background->fn->addChild(simpleViewScreen_background, (leWidget*)simpleViewScreen_simpleViewCurLevelLabel);

    simpleViewScreen_avLevLabel = leLabelWidget_New();
    simpleViewScreen_avLevLabel->fn->setPosition(simpleViewScreen_avLevLabel, 171, 37);
    simpleViewScreen_avLevLabel->fn->setSize(simpleViewScreen_avLevLabel, 133, 89);
    simpleViewScreen_avLevLabel->fn->setVisible(simpleViewScreen_avLevLabel, LE_FALSE);
    simpleViewScreen_avLevLabel->fn->setScheme(simpleViewScreen_avLevLabel, &BlackScheme);
    simpleViewScreen_avLevLabel->fn->setBackgroundType(simpleViewScreen_avLevLabel, LE_WIDGET_BACKGROUND_NONE);
    simpleViewScreen_avLevLabel->fn->setHAlignment(simpleViewScreen_avLevLabel, LE_HALIGN_CENTER);
    simpleViewScreen_avLevLabel->fn->setString(simpleViewScreen_avLevLabel, (leString*)&string_AV_100);
    simpleViewScreen_background->fn->addChild(simpleViewScreen_background, (leWidget*)simpleViewScreen_avLevLabel);

    simpleViewScreen_smpleViewInputHeaderLabel = leLabelWidget_New();
    simpleViewScreen_smpleViewInputHeaderLabel->fn->setPosition(simpleViewScreen_smpleViewInputHeaderLabel, 190, 147);
    simpleViewScreen_smpleViewInputHeaderLabel->fn->setScheme(simpleViewScreen_smpleViewInputHeaderLabel, &BlackScheme);
    simpleViewScreen_smpleViewInputHeaderLabel->fn->setHAlignment(simpleViewScreen_smpleViewInputHeaderLabel, LE_HALIGN_CENTER);
    simpleViewScreen_smpleViewInputHeaderLabel->fn->setString(simpleViewScreen_smpleViewInputHeaderLabel, (leString*)&string_simpleViewInputHeaderStr);
    simpleViewScreen_background->fn->addChild(simpleViewScreen_background, (leWidget*)simpleViewScreen_smpleViewInputHeaderLabel);

    simpleViewScreen_simpleViewInputNameLabel = leLabelWidget_New();
    simpleViewScreen_simpleViewInputNameLabel->fn->setPosition(simpleViewScreen_simpleViewInputNameLabel, 0, 170);
    simpleViewScreen_simpleViewInputNameLabel->fn->setSize(simpleViewScreen_simpleViewInputNameLabel, 480, 71);
    simpleViewScreen_simpleViewInputNameLabel->fn->setScheme(simpleViewScreen_simpleViewInputNameLabel, &BlackScheme);
    simpleViewScreen_simpleViewInputNameLabel->fn->setBackgroundType(simpleViewScreen_simpleViewInputNameLabel, LE_WIDGET_BACKGROUND_NONE);
    simpleViewScreen_simpleViewInputNameLabel->fn->setHAlignment(simpleViewScreen_simpleViewInputNameLabel, LE_HALIGN_CENTER);
    simpleViewScreen_simpleViewInputNameLabel->fn->setVAlignment(simpleViewScreen_simpleViewInputNameLabel, LE_VALIGN_TOP);
    simpleViewScreen_simpleViewInputNameLabel->fn->setString(simpleViewScreen_simpleViewInputNameLabel, (leString*)&string_simpleViewInputNameStr);
    simpleViewScreen_background->fn->addChild(simpleViewScreen_background, (leWidget*)simpleViewScreen_simpleViewInputNameLabel);

    simpleViewScreen_simpleViewAnyTouchBut = leButtonWidget_New();
    simpleViewScreen_simpleViewAnyTouchBut->fn->setPosition(simpleViewScreen_simpleViewAnyTouchBut, 0, 0);
    simpleViewScreen_simpleViewAnyTouchBut->fn->setSize(simpleViewScreen_simpleViewAnyTouchBut, 480, 272);
    simpleViewScreen_simpleViewAnyTouchBut->fn->setBackgroundType(simpleViewScreen_simpleViewAnyTouchBut, LE_WIDGET_BACKGROUND_NONE);
    simpleViewScreen_simpleViewAnyTouchBut->fn->setBorderType(simpleViewScreen_simpleViewAnyTouchBut, LE_WIDGET_BORDER_NONE);
    simpleViewScreen_simpleViewAnyTouchBut->fn->setPressedOffset(simpleViewScreen_simpleViewAnyTouchBut, 0);
    simpleViewScreen_simpleViewAnyTouchBut->fn->setPressedEventCallback(simpleViewScreen_simpleViewAnyTouchBut, event_simpleViewScreen_simpleViewAnyTouchBut_OnPressed);
    simpleViewScreen_background->fn->addChild(simpleViewScreen_background, (leWidget*)simpleViewScreen_simpleViewAnyTouchBut);

    simpleViewScreen_batteryPanel = leWidget_New();
    simpleViewScreen_batteryPanel->fn->setPosition(simpleViewScreen_batteryPanel, 280, 137);
    simpleViewScreen_batteryPanel->fn->setSize(simpleViewScreen_batteryPanel, 30, 43);
    simpleViewScreen_batteryPanel->fn->setEnabled(simpleViewScreen_batteryPanel, LE_FALSE);
    simpleViewScreen_batteryPanel->fn->setVisible(simpleViewScreen_batteryPanel, LE_FALSE);
    simpleViewScreen_batteryPanel->fn->setScheme(simpleViewScreen_batteryPanel, &BlackScheme);
    root0->fn->addChild(root0, (leWidget*)simpleViewScreen_batteryPanel);

    simpleViewScreen_BattCharged = leImageWidget_New();
    simpleViewScreen_BattCharged->fn->setPosition(simpleViewScreen_BattCharged, -1, 0);
    simpleViewScreen_BattCharged->fn->setSize(simpleViewScreen_BattCharged, 30, 39);
    simpleViewScreen_BattCharged->fn->setBorderType(simpleViewScreen_BattCharged, LE_WIDGET_BORDER_NONE);
    simpleViewScreen_BattCharged->fn->setImage(simpleViewScreen_BattCharged, (leImage*)&BattCharged);
    simpleViewScreen_batteryPanel->fn->addChild(simpleViewScreen_batteryPanel, (leWidget*)simpleViewScreen_BattCharged);

    simpleViewScreen_BattCharging = leImageWidget_New();
    simpleViewScreen_BattCharging->fn->setPosition(simpleViewScreen_BattCharging, -1, 0);
    simpleViewScreen_BattCharging->fn->setSize(simpleViewScreen_BattCharging, 30, 39);
    simpleViewScreen_BattCharging->fn->setBorderType(simpleViewScreen_BattCharging, LE_WIDGET_BORDER_NONE);
    simpleViewScreen_BattCharging->fn->setImage(simpleViewScreen_BattCharging, (leImage*)&BattCharging);
    simpleViewScreen_batteryPanel->fn->addChild(simpleViewScreen_batteryPanel, (leWidget*)simpleViewScreen_BattCharging);

    simpleViewScreen_fanErrorImg = leImageWidget_New();
    simpleViewScreen_fanErrorImg->fn->setPosition(simpleViewScreen_fanErrorImg, 331, 27);
    simpleViewScreen_fanErrorImg->fn->setVisible(simpleViewScreen_fanErrorImg, LE_FALSE);
    simpleViewScreen_fanErrorImg->fn->setScheme(simpleViewScreen_fanErrorImg, &BlackScheme);
    simpleViewScreen_fanErrorImg->fn->setBackgroundType(simpleViewScreen_fanErrorImg, LE_WIDGET_BACKGROUND_NONE);
    simpleViewScreen_fanErrorImg->fn->setBorderType(simpleViewScreen_fanErrorImg, LE_WIDGET_BORDER_NONE);
    simpleViewScreen_fanErrorImg->fn->setImage(simpleViewScreen_fanErrorImg, (leImage*)&fanError);
    root0->fn->addChild(root0, (leWidget*)simpleViewScreen_fanErrorImg);

    leAddRootWidget(root0, 0);
    leSetLayerColorMode(0, LE_COLOR_MODE_RGB_565);

    simpleViewScreen_OnShow(); // raise event

    showing = LE_TRUE;

    return LE_SUCCESS;
}

void screenUpdate_simpleViewScreen(void)
{
    root0->fn->setSize(root0, root0->rect.width, root0->rect.height);
}

void screenHide_simpleViewScreen(void)
{

    leRemoveRootWidget(root0, 0);
    leWidget_Delete(root0);
    root0 = NULL;

    simpleViewScreen_background = NULL;
    simpleViewScreen_batteryPanel = NULL;
    simpleViewScreen_fanErrorImg = NULL;
    simpleViewScreen_smpleViewMuteKryds = NULL;
    simpleViewScreen_simpleViewVolHeader = NULL;
    simpleViewScreen_simpleViewCurLevelLabel = NULL;
    simpleViewScreen_avLevLabel = NULL;
    simpleViewScreen_smpleViewInputHeaderLabel = NULL;
    simpleViewScreen_simpleViewInputNameLabel = NULL;
    simpleViewScreen_simpleViewAnyTouchBut = NULL;
    simpleViewScreen_BattCharged = NULL;
    simpleViewScreen_BattCharging = NULL;


    showing = LE_FALSE;
}

void screenDestroy_simpleViewScreen(void)
{
    if(initialized == LE_FALSE)
        return;

    initialized = LE_FALSE;
}

leWidget* screenGetRoot_simpleViewScreen(uint32_t lyrIdx)
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

