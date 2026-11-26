#include "gfx/legato/generated/screen/le_gen_screen_dsdLpSimpleView.h"

// screen member widget declarations
static leWidget* root0;

leWidget* dsdLpSimpleView_Panel_0;
leLabelWidget* dsdLpSimpleView_dsdHeader;
leLabelWidget* dsdLpSimpleView_lowPassHeader;
leLabelWidget* dsdLpSimpleView_offValue;
leLabelWidget* dsdLpSimpleView_onValue;

static leBool initialized = LE_FALSE;
static leBool showing = LE_FALSE;

leResult screenInit_dsdLpSimpleView(void)
{
    if(initialized == LE_TRUE)
        return LE_FAILURE;

    initialized = LE_TRUE;

    return LE_SUCCESS;
}

leResult screenShow_dsdLpSimpleView(void)
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

    dsdLpSimpleView_Panel_0 = leWidget_New();
    dsdLpSimpleView_Panel_0->fn->setPosition(dsdLpSimpleView_Panel_0, 0, 0);
    dsdLpSimpleView_Panel_0->fn->setSize(dsdLpSimpleView_Panel_0, 480, 272);
    dsdLpSimpleView_Panel_0->fn->setScheme(dsdLpSimpleView_Panel_0, &BlackScheme);
    root0->fn->addChild(root0, (leWidget*)dsdLpSimpleView_Panel_0);

    dsdLpSimpleView_dsdHeader = leLabelWidget_New();
    dsdLpSimpleView_dsdHeader->fn->setPosition(dsdLpSimpleView_dsdHeader, 0, 58);
    dsdLpSimpleView_dsdHeader->fn->setSize(dsdLpSimpleView_dsdHeader, 480, 32);
    dsdLpSimpleView_dsdHeader->fn->setScheme(dsdLpSimpleView_dsdHeader, &BlackScheme);
    dsdLpSimpleView_dsdHeader->fn->setHAlignment(dsdLpSimpleView_dsdHeader, LE_HALIGN_CENTER);
    dsdLpSimpleView_dsdHeader->fn->setString(dsdLpSimpleView_dsdHeader, (leString*)&string_dsd_Str_30);
    root0->fn->addChild(root0, (leWidget*)dsdLpSimpleView_dsdHeader);

    dsdLpSimpleView_lowPassHeader = leLabelWidget_New();
    dsdLpSimpleView_lowPassHeader->fn->setPosition(dsdLpSimpleView_lowPassHeader, 0, 95);
    dsdLpSimpleView_lowPassHeader->fn->setSize(dsdLpSimpleView_lowPassHeader, 480, 50);
    dsdLpSimpleView_lowPassHeader->fn->setScheme(dsdLpSimpleView_lowPassHeader, &BlackScheme);
    dsdLpSimpleView_lowPassHeader->fn->setHAlignment(dsdLpSimpleView_lowPassHeader, LE_HALIGN_CENTER);
    dsdLpSimpleView_lowPassHeader->fn->setString(dsdLpSimpleView_lowPassHeader, (leString*)&string_lowPass48);
    root0->fn->addChild(root0, (leWidget*)dsdLpSimpleView_lowPassHeader);

    dsdLpSimpleView_offValue = leLabelWidget_New();
    dsdLpSimpleView_offValue->fn->setPosition(dsdLpSimpleView_offValue, 0, 145);
    dsdLpSimpleView_offValue->fn->setSize(dsdLpSimpleView_offValue, 480, 66);
    dsdLpSimpleView_offValue->fn->setScheme(dsdLpSimpleView_offValue, &BlackScheme);
    dsdLpSimpleView_offValue->fn->setHAlignment(dsdLpSimpleView_offValue, LE_HALIGN_CENTER);
    dsdLpSimpleView_offValue->fn->setString(dsdLpSimpleView_offValue, (leString*)&string_off_String_64);
    root0->fn->addChild(root0, (leWidget*)dsdLpSimpleView_offValue);

    dsdLpSimpleView_onValue = leLabelWidget_New();
    dsdLpSimpleView_onValue->fn->setPosition(dsdLpSimpleView_onValue, 0, 145);
    dsdLpSimpleView_onValue->fn->setSize(dsdLpSimpleView_onValue, 480, 66);
    dsdLpSimpleView_onValue->fn->setScheme(dsdLpSimpleView_onValue, &BlackScheme);
    dsdLpSimpleView_onValue->fn->setHAlignment(dsdLpSimpleView_onValue, LE_HALIGN_CENTER);
    dsdLpSimpleView_onValue->fn->setString(dsdLpSimpleView_onValue, (leString*)&string_on_String_64);
    root0->fn->addChild(root0, (leWidget*)dsdLpSimpleView_onValue);

    leAddRootWidget(root0, 0);
    leSetLayerColorMode(0, LE_COLOR_MODE_RGB_565);

    dsdLpSimpleView_OnShow(); // raise event

    showing = LE_TRUE;

    return LE_SUCCESS;
}

void screenUpdate_dsdLpSimpleView(void)
{
    root0->fn->setSize(root0, root0->rect.width, root0->rect.height);
}

void screenHide_dsdLpSimpleView(void)
{

    leRemoveRootWidget(root0, 0);
    leWidget_Delete(root0);
    root0 = NULL;

    dsdLpSimpleView_Panel_0 = NULL;
    dsdLpSimpleView_dsdHeader = NULL;
    dsdLpSimpleView_lowPassHeader = NULL;
    dsdLpSimpleView_offValue = NULL;
    dsdLpSimpleView_onValue = NULL;


    showing = LE_FALSE;
}

void screenDestroy_dsdLpSimpleView(void)
{
    if(initialized == LE_FALSE)
        return;

    initialized = LE_FALSE;
}

leWidget* screenGetRoot_dsdLpSimpleView(uint32_t lyrIdx)
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

