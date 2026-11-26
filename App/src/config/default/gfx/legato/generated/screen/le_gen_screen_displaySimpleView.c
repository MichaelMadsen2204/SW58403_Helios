#include "gfx/legato/generated/screen/le_gen_screen_displaySimpleView.h"

// screen member widget declarations
static leWidget* root0;

leWidget* displaySimpleView_Panel_0;
leLabelWidget* displaySimpleView_header;
leLabelWidget* displaySimpleView_dispMode;

static leBool initialized = LE_FALSE;
static leBool showing = LE_FALSE;

leResult screenInit_displaySimpleView(void)
{
    if(initialized == LE_TRUE)
        return LE_FAILURE;

    initialized = LE_TRUE;

    return LE_SUCCESS;
}

leResult screenShow_displaySimpleView(void)
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

    displaySimpleView_Panel_0 = leWidget_New();
    displaySimpleView_Panel_0->fn->setPosition(displaySimpleView_Panel_0, 0, 0);
    displaySimpleView_Panel_0->fn->setSize(displaySimpleView_Panel_0, 480, 272);
    displaySimpleView_Panel_0->fn->setScheme(displaySimpleView_Panel_0, &BlackScheme);
    root0->fn->addChild(root0, (leWidget*)displaySimpleView_Panel_0);

    displaySimpleView_header = leLabelWidget_New();
    displaySimpleView_header->fn->setPosition(displaySimpleView_header, 0, 70);
    displaySimpleView_header->fn->setSize(displaySimpleView_header, 480, 50);
    displaySimpleView_header->fn->setScheme(displaySimpleView_header, &BlackScheme);
    displaySimpleView_header->fn->setHAlignment(displaySimpleView_header, LE_HALIGN_CENTER);
    displaySimpleView_header->fn->setString(displaySimpleView_header, (leString*)&string_dispHeader);
    root0->fn->addChild(root0, (leWidget*)displaySimpleView_header);

    displaySimpleView_dispMode = leLabelWidget_New();
    displaySimpleView_dispMode->fn->setPosition(displaySimpleView_dispMode, 0, 140);
    displaySimpleView_dispMode->fn->setSize(displaySimpleView_dispMode, 480, 50);
    displaySimpleView_dispMode->fn->setScheme(displaySimpleView_dispMode, &BlackScheme);
    displaySimpleView_dispMode->fn->setHAlignment(displaySimpleView_dispMode, LE_HALIGN_CENTER);
    displaySimpleView_dispMode->fn->setString(displaySimpleView_dispMode, (leString*)&string_dispModeStr);
    root0->fn->addChild(root0, (leWidget*)displaySimpleView_dispMode);

    leAddRootWidget(root0, 0);
    leSetLayerColorMode(0, LE_COLOR_MODE_RGB_565);

    displaySimpleView_OnShow(); // raise event

    showing = LE_TRUE;

    return LE_SUCCESS;
}

void screenUpdate_displaySimpleView(void)
{
    root0->fn->setSize(root0, root0->rect.width, root0->rect.height);
}

void screenHide_displaySimpleView(void)
{

    leRemoveRootWidget(root0, 0);
    leWidget_Delete(root0);
    root0 = NULL;

    displaySimpleView_Panel_0 = NULL;
    displaySimpleView_header = NULL;
    displaySimpleView_dispMode = NULL;


    showing = LE_FALSE;
}

void screenDestroy_displaySimpleView(void)
{
    if(initialized == LE_FALSE)
        return;

    initialized = LE_FALSE;
}

leWidget* screenGetRoot_displaySimpleView(uint32_t lyrIdx)
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

