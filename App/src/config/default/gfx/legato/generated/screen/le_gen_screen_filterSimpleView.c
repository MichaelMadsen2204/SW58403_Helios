#include "gfx/legato/generated/screen/le_gen_screen_filterSimpleView.h"

// screen member widget declarations
static leWidget* root0;

leWidget* filterSimpleView_Panel_0;
leLabelWidget* filterSimpleView_filterNumber;
leLabelWidget* filterSimpleView_LabelWidget_1;
leLabelWidget* filterSimpleView_LabelWidget_2;

static leBool initialized = LE_FALSE;
static leBool showing = LE_FALSE;

leResult screenInit_filterSimpleView(void)
{
    if(initialized == LE_TRUE)
        return LE_FAILURE;

    initialized = LE_TRUE;

    return LE_SUCCESS;
}

leResult screenShow_filterSimpleView(void)
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

    filterSimpleView_Panel_0 = leWidget_New();
    filterSimpleView_Panel_0->fn->setPosition(filterSimpleView_Panel_0, 0, 0);
    filterSimpleView_Panel_0->fn->setSize(filterSimpleView_Panel_0, 480, 272);
    filterSimpleView_Panel_0->fn->setScheme(filterSimpleView_Panel_0, &BlackScheme);
    root0->fn->addChild(root0, (leWidget*)filterSimpleView_Panel_0);

    filterSimpleView_filterNumber = leLabelWidget_New();
    filterSimpleView_filterNumber->fn->setPosition(filterSimpleView_filterNumber, 0, 51);
    filterSimpleView_filterNumber->fn->setSize(filterSimpleView_filterNumber, 480, 50);
    filterSimpleView_filterNumber->fn->setScheme(filterSimpleView_filterNumber, &BlackScheme);
    filterSimpleView_filterNumber->fn->setHAlignment(filterSimpleView_filterNumber, LE_HALIGN_CENTER);
    filterSimpleView_filterNumber->fn->setString(filterSimpleView_filterNumber, (leString*)&string_pcmFilt2_48);
    filterSimpleView_Panel_0->fn->addChild(filterSimpleView_Panel_0, (leWidget*)filterSimpleView_filterNumber);

    filterSimpleView_LabelWidget_1 = leLabelWidget_New();
    filterSimpleView_LabelWidget_1->fn->setPosition(filterSimpleView_LabelWidget_1, 0, 116);
    filterSimpleView_LabelWidget_1->fn->setSize(filterSimpleView_LabelWidget_1, 480, 50);
    filterSimpleView_LabelWidget_1->fn->setScheme(filterSimpleView_LabelWidget_1, &BlackScheme);
    filterSimpleView_LabelWidget_1->fn->setHAlignment(filterSimpleView_LabelWidget_1, LE_HALIGN_CENTER);
    filterSimpleView_LabelWidget_1->fn->setString(filterSimpleView_LabelWidget_1, (leString*)&string_LinPhase30);
    filterSimpleView_Panel_0->fn->addChild(filterSimpleView_Panel_0, (leWidget*)filterSimpleView_LabelWidget_1);

    filterSimpleView_LabelWidget_2 = leLabelWidget_New();
    filterSimpleView_LabelWidget_2->fn->setPosition(filterSimpleView_LabelWidget_2, 0, 166);
    filterSimpleView_LabelWidget_2->fn->setSize(filterSimpleView_LabelWidget_2, 480, 50);
    filterSimpleView_LabelWidget_2->fn->setScheme(filterSimpleView_LabelWidget_2, &BlackScheme);
    filterSimpleView_LabelWidget_2->fn->setHAlignment(filterSimpleView_LabelWidget_2, LE_HALIGN_CENTER);
    filterSimpleView_LabelWidget_2->fn->setString(filterSimpleView_LabelWidget_2, (leString*)&string_Apodiz30);
    filterSimpleView_Panel_0->fn->addChild(filterSimpleView_Panel_0, (leWidget*)filterSimpleView_LabelWidget_2);

    leAddRootWidget(root0, 0);
    leSetLayerColorMode(0, LE_COLOR_MODE_RGB_565);

    filterSimpleView_OnShow(); // raise event

    showing = LE_TRUE;

    return LE_SUCCESS;
}

void screenUpdate_filterSimpleView(void)
{
    root0->fn->setSize(root0, root0->rect.width, root0->rect.height);
}

void screenHide_filterSimpleView(void)
{

    leRemoveRootWidget(root0, 0);
    leWidget_Delete(root0);
    root0 = NULL;

    filterSimpleView_Panel_0 = NULL;
    filterSimpleView_filterNumber = NULL;
    filterSimpleView_LabelWidget_1 = NULL;
    filterSimpleView_LabelWidget_2 = NULL;


    showing = LE_FALSE;
}

void screenDestroy_filterSimpleView(void)
{
    if(initialized == LE_FALSE)
        return;

    initialized = LE_FALSE;
}

leWidget* screenGetRoot_filterSimpleView(uint32_t lyrIdx)
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

