#include "gfx/legato/generated/screen/le_gen_screen_dacGainSimpleView.h"

// screen member widget declarations
static leWidget* root0;

leWidget* dacGainSimpleView_Panel_0;
leLabelWidget* dacGainSimpleView_header;
leLabelWidget* dacGainSimpleView_header2;
leLabelWidget* dacGainSimpleView_gain0dB;
leLabelWidget* dacGainSimpleView_gainMinus6dB;

static leBool initialized = LE_FALSE;
static leBool showing = LE_FALSE;

leResult screenInit_dacGainSimpleView(void)
{
    if(initialized == LE_TRUE)
        return LE_FAILURE;

    initialized = LE_TRUE;

    return LE_SUCCESS;
}

leResult screenShow_dacGainSimpleView(void)
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

    dacGainSimpleView_Panel_0 = leWidget_New();
    dacGainSimpleView_Panel_0->fn->setPosition(dacGainSimpleView_Panel_0, 0, 0);
    dacGainSimpleView_Panel_0->fn->setSize(dacGainSimpleView_Panel_0, 480, 272);
    dacGainSimpleView_Panel_0->fn->setScheme(dacGainSimpleView_Panel_0, &BlackScheme);
    root0->fn->addChild(root0, (leWidget*)dacGainSimpleView_Panel_0);

    dacGainSimpleView_header = leLabelWidget_New();
    dacGainSimpleView_header->fn->setPosition(dacGainSimpleView_header, 0, 58);
    dacGainSimpleView_header->fn->setSize(dacGainSimpleView_header, 480, 32);
    dacGainSimpleView_header->fn->setScheme(dacGainSimpleView_header, &BlackScheme);
    dacGainSimpleView_header->fn->setHAlignment(dacGainSimpleView_header, LE_HALIGN_CENTER);
    dacGainSimpleView_header->fn->setString(dacGainSimpleView_header, (leString*)&string_DAC_str);
    root0->fn->addChild(root0, (leWidget*)dacGainSimpleView_header);

    dacGainSimpleView_header2 = leLabelWidget_New();
    dacGainSimpleView_header2->fn->setPosition(dacGainSimpleView_header2, 0, 95);
    dacGainSimpleView_header2->fn->setSize(dacGainSimpleView_header2, 480, 50);
    dacGainSimpleView_header2->fn->setScheme(dacGainSimpleView_header2, &BlackScheme);
    dacGainSimpleView_header2->fn->setHAlignment(dacGainSimpleView_header2, LE_HALIGN_CENTER);
    dacGainSimpleView_header2->fn->setString(dacGainSimpleView_header2, (leString*)&string_dacGain_str48);
    root0->fn->addChild(root0, (leWidget*)dacGainSimpleView_header2);

    dacGainSimpleView_gain0dB = leLabelWidget_New();
    dacGainSimpleView_gain0dB->fn->setPosition(dacGainSimpleView_gain0dB, 0, 145);
    dacGainSimpleView_gain0dB->fn->setSize(dacGainSimpleView_gain0dB, 480, 65);
    dacGainSimpleView_gain0dB->fn->setScheme(dacGainSimpleView_gain0dB, &BlackScheme);
    dacGainSimpleView_gain0dB->fn->setHAlignment(dacGainSimpleView_gain0dB, LE_HALIGN_CENTER);
    dacGainSimpleView_gain0dB->fn->setString(dacGainSimpleView_gain0dB, (leString*)&string_String0dB_64);
    root0->fn->addChild(root0, (leWidget*)dacGainSimpleView_gain0dB);

    dacGainSimpleView_gainMinus6dB = leLabelWidget_New();
    dacGainSimpleView_gainMinus6dB->fn->setPosition(dacGainSimpleView_gainMinus6dB, 0, 145);
    dacGainSimpleView_gainMinus6dB->fn->setSize(dacGainSimpleView_gainMinus6dB, 480, 65);
    dacGainSimpleView_gainMinus6dB->fn->setVisible(dacGainSimpleView_gainMinus6dB, LE_FALSE);
    dacGainSimpleView_gainMinus6dB->fn->setScheme(dacGainSimpleView_gainMinus6dB, &BlackScheme);
    dacGainSimpleView_gainMinus6dB->fn->setHAlignment(dacGainSimpleView_gainMinus6dB, LE_HALIGN_CENTER);
    dacGainSimpleView_gainMinus6dB->fn->setString(dacGainSimpleView_gainMinus6dB, (leString*)&string_StringMinus6dB_64);
    root0->fn->addChild(root0, (leWidget*)dacGainSimpleView_gainMinus6dB);

    leAddRootWidget(root0, 0);
    leSetLayerColorMode(0, LE_COLOR_MODE_RGB_565);

    dacGainSimpleView_OnShow(); // raise event

    showing = LE_TRUE;

    return LE_SUCCESS;
}

void screenUpdate_dacGainSimpleView(void)
{
    root0->fn->setSize(root0, root0->rect.width, root0->rect.height);
}

void screenHide_dacGainSimpleView(void)
{

    leRemoveRootWidget(root0, 0);
    leWidget_Delete(root0);
    root0 = NULL;

    dacGainSimpleView_Panel_0 = NULL;
    dacGainSimpleView_header = NULL;
    dacGainSimpleView_header2 = NULL;
    dacGainSimpleView_gain0dB = NULL;
    dacGainSimpleView_gainMinus6dB = NULL;


    showing = LE_FALSE;
}

void screenDestroy_dacGainSimpleView(void)
{
    if(initialized == LE_FALSE)
        return;

    initialized = LE_FALSE;
}

leWidget* screenGetRoot_dacGainSimpleView(uint32_t lyrIdx)
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

