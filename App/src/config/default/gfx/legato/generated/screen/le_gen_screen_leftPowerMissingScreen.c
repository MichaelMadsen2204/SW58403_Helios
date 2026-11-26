#include "gfx/legato/generated/screen/le_gen_screen_leftPowerMissingScreen.h"

// screen member widget declarations
static leWidget* root0;

leWidget* leftPowerMissingScreen_Panel_0;
leLabelWidget* leftPowerMissingScreen_LabelWidget_0;
leLabelWidget* leftPowerMissingScreen_LabelWidget_1;

static leBool initialized = LE_FALSE;
static leBool showing = LE_FALSE;

leResult screenInit_leftPowerMissingScreen(void)
{
    if(initialized == LE_TRUE)
        return LE_FAILURE;

    initialized = LE_TRUE;

    return LE_SUCCESS;
}

leResult screenShow_leftPowerMissingScreen(void)
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

    leftPowerMissingScreen_Panel_0 = leWidget_New();
    leftPowerMissingScreen_Panel_0->fn->setPosition(leftPowerMissingScreen_Panel_0, 0, 0);
    leftPowerMissingScreen_Panel_0->fn->setSize(leftPowerMissingScreen_Panel_0, 480, 272);
    leftPowerMissingScreen_Panel_0->fn->setScheme(leftPowerMissingScreen_Panel_0, &BlackScheme);
    root0->fn->addChild(root0, (leWidget*)leftPowerMissingScreen_Panel_0);

    leftPowerMissingScreen_LabelWidget_0 = leLabelWidget_New();
    leftPowerMissingScreen_LabelWidget_0->fn->setPosition(leftPowerMissingScreen_LabelWidget_0, 0, 60);
    leftPowerMissingScreen_LabelWidget_0->fn->setSize(leftPowerMissingScreen_LabelWidget_0, 480, 50);
    leftPowerMissingScreen_LabelWidget_0->fn->setScheme(leftPowerMissingScreen_LabelWidget_0, &BlackScheme);
    leftPowerMissingScreen_LabelWidget_0->fn->setHAlignment(leftPowerMissingScreen_LabelWidget_0, LE_HALIGN_CENTER);
    leftPowerMissingScreen_LabelWidget_0->fn->setString(leftPowerMissingScreen_LabelWidget_0, (leString*)&string_LeftSidePowerMissingStr);
    root0->fn->addChild(root0, (leWidget*)leftPowerMissingScreen_LabelWidget_0);

    leftPowerMissingScreen_LabelWidget_1 = leLabelWidget_New();
    leftPowerMissingScreen_LabelWidget_1->fn->setPosition(leftPowerMissingScreen_LabelWidget_1, 0, 129);
    leftPowerMissingScreen_LabelWidget_1->fn->setSize(leftPowerMissingScreen_LabelWidget_1, 480, 25);
    leftPowerMissingScreen_LabelWidget_1->fn->setScheme(leftPowerMissingScreen_LabelWidget_1, &BlackScheme);
    leftPowerMissingScreen_LabelWidget_1->fn->setHAlignment(leftPowerMissingScreen_LabelWidget_1, LE_HALIGN_CENTER);
    leftPowerMissingScreen_LabelWidget_1->fn->setString(leftPowerMissingScreen_LabelWidget_1, (leString*)&string_CheckPowerCordStr);
    root0->fn->addChild(root0, (leWidget*)leftPowerMissingScreen_LabelWidget_1);

    leAddRootWidget(root0, 0);
    leSetLayerColorMode(0, LE_COLOR_MODE_RGB_565);

    showing = LE_TRUE;

    return LE_SUCCESS;
}

void screenUpdate_leftPowerMissingScreen(void)
{
    root0->fn->setSize(root0, root0->rect.width, root0->rect.height);
}

void screenHide_leftPowerMissingScreen(void)
{

    leRemoveRootWidget(root0, 0);
    leWidget_Delete(root0);
    root0 = NULL;

    leftPowerMissingScreen_Panel_0 = NULL;
    leftPowerMissingScreen_LabelWidget_0 = NULL;
    leftPowerMissingScreen_LabelWidget_1 = NULL;


    showing = LE_FALSE;
}

void screenDestroy_leftPowerMissingScreen(void)
{
    if(initialized == LE_FALSE)
        return;

    initialized = LE_FALSE;
}

leWidget* screenGetRoot_leftPowerMissingScreen(uint32_t lyrIdx)
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

