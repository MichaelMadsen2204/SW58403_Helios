#include "gfx/legato/generated/screen/le_gen_screen_splashScreen.h"

// screen member widget declarations
static leWidget* root0;

leRectangleWidget* splashScreen_RectangleWidget0;
leImageWidget* splashScreen_ImageWidget0;
leTouchTestWidget* splashScreen_TouchTestWidget0;

static leBool initialized = LE_FALSE;
static leBool showing = LE_FALSE;

leResult screenInit_splashScreen(void)
{
    if(initialized == LE_TRUE)
        return LE_FAILURE;

    initialized = LE_TRUE;

    return LE_SUCCESS;
}

leResult screenShow_splashScreen(void)
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

    splashScreen_RectangleWidget0 = leRectangleWidget_New();
    splashScreen_RectangleWidget0->fn->setPosition(splashScreen_RectangleWidget0, 0, 0);
    splashScreen_RectangleWidget0->fn->setSize(splashScreen_RectangleWidget0, 480, 272);
    splashScreen_RectangleWidget0->fn->setScheme(splashScreen_RectangleWidget0, &BlackScheme);
    splashScreen_RectangleWidget0->fn->setBorderType(splashScreen_RectangleWidget0, LE_WIDGET_BORDER_NONE);
    splashScreen_RectangleWidget0->fn->setThickness(splashScreen_RectangleWidget0, 2);
    root0->fn->addChild(root0, (leWidget*)splashScreen_RectangleWidget0);

    splashScreen_ImageWidget0 = leImageWidget_New();
    splashScreen_ImageWidget0->fn->setPosition(splashScreen_ImageWidget0, 0, 0);
    splashScreen_ImageWidget0->fn->setSize(splashScreen_ImageWidget0, 480, 272);
    splashScreen_ImageWidget0->fn->setAlphaEnabled(splashScreen_ImageWidget0, LE_TRUE);
    splashScreen_ImageWidget0->fn->setBorderType(splashScreen_ImageWidget0, LE_WIDGET_BORDER_NONE);
    splashScreen_ImageWidget0->fn->setImage(splashScreen_ImageWidget0, (leImage*)&display_logo_v22);
    root0->fn->addChild(root0, (leWidget*)splashScreen_ImageWidget0);

    splashScreen_TouchTestWidget0 = leTouchTestWidget_New();
    splashScreen_TouchTestWidget0->fn->setPosition(splashScreen_TouchTestWidget0, 462, 14);
    splashScreen_TouchTestWidget0->fn->setSize(splashScreen_TouchTestWidget0, 12, 13);
    splashScreen_TouchTestWidget0->fn->setBackgroundType(splashScreen_TouchTestWidget0, LE_WIDGET_BACKGROUND_NONE);
    splashScreen_TouchTestWidget0->fn->setBorderType(splashScreen_TouchTestWidget0, LE_WIDGET_BORDER_NONE);
    splashScreen_TouchTestWidget0->fn->setPointAddedEventCallback(splashScreen_TouchTestWidget0, event_splashScreen_TouchTestWidget0_OnPointAdded);
    root0->fn->addChild(root0, (leWidget*)splashScreen_TouchTestWidget0);

    leAddRootWidget(root0, 0);
    leSetLayerColorMode(0, LE_COLOR_MODE_RGB_565);

    splashScreen_OnShow(); // raise event

    showing = LE_TRUE;

    return LE_SUCCESS;
}

void screenUpdate_splashScreen(void)
{
    root0->fn->setSize(root0, root0->rect.width, root0->rect.height);
}

void screenHide_splashScreen(void)
{

    leRemoveRootWidget(root0, 0);
    leWidget_Delete(root0);
    root0 = NULL;

    splashScreen_RectangleWidget0 = NULL;
    splashScreen_ImageWidget0 = NULL;
    splashScreen_TouchTestWidget0 = NULL;


    showing = LE_FALSE;
}

void screenDestroy_splashScreen(void)
{
    if(initialized == LE_FALSE)
        return;

    initialized = LE_FALSE;
}

leWidget* screenGetRoot_splashScreen(uint32_t lyrIdx)
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

