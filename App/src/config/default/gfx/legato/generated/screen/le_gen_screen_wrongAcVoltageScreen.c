#include "gfx/legato/generated/screen/le_gen_screen_wrongAcVoltageScreen.h"

// screen member widget declarations
static leWidget* root0;

leWidget* wrongAcVoltageScreen_Panel_0;
leLabelWidget* wrongAcVoltageScreen_LabelWidget_0;
leLabelWidget* wrongAcVoltageScreen_LabelWidget_1;

static leBool initialized = LE_FALSE;
static leBool showing = LE_FALSE;

leResult screenInit_wrongAcVoltageScreen(void)
{
    if(initialized == LE_TRUE)
        return LE_FAILURE;

    initialized = LE_TRUE;

    return LE_SUCCESS;
}

leResult screenShow_wrongAcVoltageScreen(void)
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

    wrongAcVoltageScreen_Panel_0 = leWidget_New();
    wrongAcVoltageScreen_Panel_0->fn->setPosition(wrongAcVoltageScreen_Panel_0, 0, 0);
    wrongAcVoltageScreen_Panel_0->fn->setSize(wrongAcVoltageScreen_Panel_0, 480, 272);
    wrongAcVoltageScreen_Panel_0->fn->setScheme(wrongAcVoltageScreen_Panel_0, &BlackScheme);
    root0->fn->addChild(root0, (leWidget*)wrongAcVoltageScreen_Panel_0);

    wrongAcVoltageScreen_LabelWidget_0 = leLabelWidget_New();
    wrongAcVoltageScreen_LabelWidget_0->fn->setPosition(wrongAcVoltageScreen_LabelWidget_0, 0, 60);
    wrongAcVoltageScreen_LabelWidget_0->fn->setSize(wrongAcVoltageScreen_LabelWidget_0, 480, 50);
    wrongAcVoltageScreen_LabelWidget_0->fn->setScheme(wrongAcVoltageScreen_LabelWidget_0, &BlackScheme);
    wrongAcVoltageScreen_LabelWidget_0->fn->setHAlignment(wrongAcVoltageScreen_LabelWidget_0, LE_HALIGN_CENTER);
    wrongAcVoltageScreen_LabelWidget_0->fn->setString(wrongAcVoltageScreen_LabelWidget_0, (leString*)&string_wrongACHeader);
    root0->fn->addChild(root0, (leWidget*)wrongAcVoltageScreen_LabelWidget_0);

    wrongAcVoltageScreen_LabelWidget_1 = leLabelWidget_New();
    wrongAcVoltageScreen_LabelWidget_1->fn->setPosition(wrongAcVoltageScreen_LabelWidget_1, 0, 129);
    wrongAcVoltageScreen_LabelWidget_1->fn->setSize(wrongAcVoltageScreen_LabelWidget_1, 480, 25);
    wrongAcVoltageScreen_LabelWidget_1->fn->setScheme(wrongAcVoltageScreen_LabelWidget_1, &BlackScheme);
    wrongAcVoltageScreen_LabelWidget_1->fn->setHAlignment(wrongAcVoltageScreen_LabelWidget_1, LE_HALIGN_CENTER);
    wrongAcVoltageScreen_LabelWidget_1->fn->setString(wrongAcVoltageScreen_LabelWidget_1, (leString*)&string_WrongAcInstructionStr);
    root0->fn->addChild(root0, (leWidget*)wrongAcVoltageScreen_LabelWidget_1);

    leAddRootWidget(root0, 0);
    leSetLayerColorMode(0, LE_COLOR_MODE_RGB_565);

    showing = LE_TRUE;

    return LE_SUCCESS;
}

void screenUpdate_wrongAcVoltageScreen(void)
{
    root0->fn->setSize(root0, root0->rect.width, root0->rect.height);
}

void screenHide_wrongAcVoltageScreen(void)
{

    leRemoveRootWidget(root0, 0);
    leWidget_Delete(root0);
    root0 = NULL;

    wrongAcVoltageScreen_Panel_0 = NULL;
    wrongAcVoltageScreen_LabelWidget_0 = NULL;
    wrongAcVoltageScreen_LabelWidget_1 = NULL;


    showing = LE_FALSE;
}

void screenDestroy_wrongAcVoltageScreen(void)
{
    if(initialized == LE_FALSE)
        return;

    initialized = LE_FALSE;
}

leWidget* screenGetRoot_wrongAcVoltageScreen(uint32_t lyrIdx)
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

