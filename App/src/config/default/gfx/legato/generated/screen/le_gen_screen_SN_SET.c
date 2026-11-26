#include "gfx/legato/generated/screen/le_gen_screen_SN_SET.h"

// screen member widget declarations
static leWidget* root0;

leWidget* SN_SET_BackGnd;
leLabelWidget* SN_SET_thousands;
leLabelWidget* SN_SET_hundreds;
leLabelWidget* SN_SET_tens;
leLabelWidget* SN_SET_singles;
leLabelWidget* SN_SET_LabelWidget_6;
leImageWidget* SN_SET_ImageWidget_0;
leImageWidget* SN_SET_ImageWidget_1;
leImageWidget* SN_SET_ImageWidget_2;
leImageWidget* SN_SET_ImageWidget_3;
leButtonWidget* SN_SET_oneUp;
leButtonWidget* SN_SET_oneDwn;
leButtonWidget* SN_SET_tenUp;
leButtonWidget* SN_SET_tenDwn;
leButtonWidget* SN_SET_hundredUp;
leButtonWidget* SN_SET_hundredDwn;
leButtonWidget* SN_SET_thousandUp;
leButtonWidget* SN_SET_thousandDwn;
leButtonWidget* SN_SET_save;

static leBool initialized = LE_FALSE;
static leBool showing = LE_FALSE;

leResult screenInit_SN_SET(void)
{
    if(initialized == LE_TRUE)
        return LE_FAILURE;

    initialized = LE_TRUE;

    return LE_SUCCESS;
}

leResult screenShow_SN_SET(void)
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

    SN_SET_BackGnd = leWidget_New();
    SN_SET_BackGnd->fn->setPosition(SN_SET_BackGnd, 0, 0);
    SN_SET_BackGnd->fn->setSize(SN_SET_BackGnd, 480, 272);
    SN_SET_BackGnd->fn->setScheme(SN_SET_BackGnd, &BlackScheme);
    root0->fn->addChild(root0, (leWidget*)SN_SET_BackGnd);

    SN_SET_thousands = leLabelWidget_New();
    SN_SET_thousands->fn->setPosition(SN_SET_thousands, 172, 50);
    SN_SET_thousands->fn->setSize(SN_SET_thousands, 40, 70);
    SN_SET_thousands->fn->setScheme(SN_SET_thousands, &BlackScheme);
    SN_SET_thousands->fn->setVAlignment(SN_SET_thousands, LE_VALIGN_TOP);
    SN_SET_thousands->fn->setString(SN_SET_thousands, (leString*)&string_sn_thousands);
    root0->fn->addChild(root0, (leWidget*)SN_SET_thousands);

    SN_SET_hundreds = leLabelWidget_New();
    SN_SET_hundreds->fn->setPosition(SN_SET_hundreds, 235, 50);
    SN_SET_hundreds->fn->setSize(SN_SET_hundreds, 40, 70);
    SN_SET_hundreds->fn->setScheme(SN_SET_hundreds, &BlackScheme);
    SN_SET_hundreds->fn->setVAlignment(SN_SET_hundreds, LE_VALIGN_TOP);
    SN_SET_hundreds->fn->setString(SN_SET_hundreds, (leString*)&string_sn_hundreds);
    root0->fn->addChild(root0, (leWidget*)SN_SET_hundreds);

    SN_SET_tens = leLabelWidget_New();
    SN_SET_tens->fn->setPosition(SN_SET_tens, 300, 50);
    SN_SET_tens->fn->setSize(SN_SET_tens, 40, 70);
    SN_SET_tens->fn->setScheme(SN_SET_tens, &BlackScheme);
    SN_SET_tens->fn->setVAlignment(SN_SET_tens, LE_VALIGN_TOP);
    SN_SET_tens->fn->setString(SN_SET_tens, (leString*)&string_sn_tens);
    root0->fn->addChild(root0, (leWidget*)SN_SET_tens);

    SN_SET_singles = leLabelWidget_New();
    SN_SET_singles->fn->setPosition(SN_SET_singles, 365, 50);
    SN_SET_singles->fn->setSize(SN_SET_singles, 40, 70);
    SN_SET_singles->fn->setScheme(SN_SET_singles, &BlackScheme);
    SN_SET_singles->fn->setVAlignment(SN_SET_singles, LE_VALIGN_TOP);
    SN_SET_singles->fn->setString(SN_SET_singles, (leString*)&string_sn_singles);
    root0->fn->addChild(root0, (leWidget*)SN_SET_singles);

    SN_SET_LabelWidget_6 = leLabelWidget_New();
    SN_SET_LabelWidget_6->fn->setPosition(SN_SET_LabelWidget_6, 57, 50);
    SN_SET_LabelWidget_6->fn->setSize(SN_SET_LabelWidget_6, 120, 70);
    SN_SET_LabelWidget_6->fn->setScheme(SN_SET_LabelWidget_6, &BlackScheme);
    SN_SET_LabelWidget_6->fn->setVAlignment(SN_SET_LabelWidget_6, LE_VALIGN_TOP);
    SN_SET_LabelWidget_6->fn->setString(SN_SET_LabelWidget_6, (leString*)&string_sn_fixedPart);
    root0->fn->addChild(root0, (leWidget*)SN_SET_LabelWidget_6);

    SN_SET_ImageWidget_0 = leImageWidget_New();
    SN_SET_ImageWidget_0->fn->setPosition(SN_SET_ImageWidget_0, 356, 140);
    SN_SET_ImageWidget_0->fn->setSize(SN_SET_ImageWidget_0, 60, 80);
    SN_SET_ImageWidget_0->fn->setBorderType(SN_SET_ImageWidget_0, LE_WIDGET_BORDER_NONE);
    SN_SET_ImageWidget_0->fn->setImage(SN_SET_ImageWidget_0, (leImage*)&ILMVolButtons);
    root0->fn->addChild(root0, (leWidget*)SN_SET_ImageWidget_0);

    SN_SET_ImageWidget_1 = leImageWidget_New();
    SN_SET_ImageWidget_1->fn->setPosition(SN_SET_ImageWidget_1, 291, 140);
    SN_SET_ImageWidget_1->fn->setSize(SN_SET_ImageWidget_1, 60, 80);
    SN_SET_ImageWidget_1->fn->setBorderType(SN_SET_ImageWidget_1, LE_WIDGET_BORDER_NONE);
    SN_SET_ImageWidget_1->fn->setImage(SN_SET_ImageWidget_1, (leImage*)&ILMVolButtons);
    root0->fn->addChild(root0, (leWidget*)SN_SET_ImageWidget_1);

    SN_SET_ImageWidget_2 = leImageWidget_New();
    SN_SET_ImageWidget_2->fn->setPosition(SN_SET_ImageWidget_2, 226, 140);
    SN_SET_ImageWidget_2->fn->setSize(SN_SET_ImageWidget_2, 60, 80);
    SN_SET_ImageWidget_2->fn->setBorderType(SN_SET_ImageWidget_2, LE_WIDGET_BORDER_NONE);
    SN_SET_ImageWidget_2->fn->setImage(SN_SET_ImageWidget_2, (leImage*)&ILMVolButtons);
    root0->fn->addChild(root0, (leWidget*)SN_SET_ImageWidget_2);

    SN_SET_ImageWidget_3 = leImageWidget_New();
    SN_SET_ImageWidget_3->fn->setPosition(SN_SET_ImageWidget_3, 161, 140);
    SN_SET_ImageWidget_3->fn->setSize(SN_SET_ImageWidget_3, 60, 80);
    SN_SET_ImageWidget_3->fn->setBorderType(SN_SET_ImageWidget_3, LE_WIDGET_BORDER_NONE);
    SN_SET_ImageWidget_3->fn->setImage(SN_SET_ImageWidget_3, (leImage*)&ILMVolButtons);
    root0->fn->addChild(root0, (leWidget*)SN_SET_ImageWidget_3);

    SN_SET_oneUp = leButtonWidget_New();
    SN_SET_oneUp->fn->setPosition(SN_SET_oneUp, 371, 110);
    SN_SET_oneUp->fn->setSize(SN_SET_oneUp, 30, 60);
    SN_SET_oneUp->fn->setBackgroundType(SN_SET_oneUp, LE_WIDGET_BACKGROUND_NONE);
    SN_SET_oneUp->fn->setBorderType(SN_SET_oneUp, LE_WIDGET_BORDER_NONE);
    SN_SET_oneUp->fn->setPressedOffset(SN_SET_oneUp, 0);
    SN_SET_oneUp->fn->setPressedEventCallback(SN_SET_oneUp, event_SN_SET_oneUp_OnPressed);
    root0->fn->addChild(root0, (leWidget*)SN_SET_oneUp);

    SN_SET_oneDwn = leButtonWidget_New();
    SN_SET_oneDwn->fn->setPosition(SN_SET_oneDwn, 371, 190);
    SN_SET_oneDwn->fn->setSize(SN_SET_oneDwn, 30, 60);
    SN_SET_oneDwn->fn->setBackgroundType(SN_SET_oneDwn, LE_WIDGET_BACKGROUND_NONE);
    SN_SET_oneDwn->fn->setBorderType(SN_SET_oneDwn, LE_WIDGET_BORDER_NONE);
    SN_SET_oneDwn->fn->setPressedOffset(SN_SET_oneDwn, 0);
    SN_SET_oneDwn->fn->setPressedEventCallback(SN_SET_oneDwn, event_SN_SET_oneDwn_OnPressed);
    root0->fn->addChild(root0, (leWidget*)SN_SET_oneDwn);

    SN_SET_tenUp = leButtonWidget_New();
    SN_SET_tenUp->fn->setPosition(SN_SET_tenUp, 306, 110);
    SN_SET_tenUp->fn->setSize(SN_SET_tenUp, 30, 60);
    SN_SET_tenUp->fn->setBackgroundType(SN_SET_tenUp, LE_WIDGET_BACKGROUND_NONE);
    SN_SET_tenUp->fn->setBorderType(SN_SET_tenUp, LE_WIDGET_BORDER_NONE);
    SN_SET_tenUp->fn->setPressedOffset(SN_SET_tenUp, 0);
    SN_SET_tenUp->fn->setPressedEventCallback(SN_SET_tenUp, event_SN_SET_tenUp_OnPressed);
    root0->fn->addChild(root0, (leWidget*)SN_SET_tenUp);

    SN_SET_tenDwn = leButtonWidget_New();
    SN_SET_tenDwn->fn->setPosition(SN_SET_tenDwn, 306, 190);
    SN_SET_tenDwn->fn->setSize(SN_SET_tenDwn, 30, 60);
    SN_SET_tenDwn->fn->setBackgroundType(SN_SET_tenDwn, LE_WIDGET_BACKGROUND_NONE);
    SN_SET_tenDwn->fn->setBorderType(SN_SET_tenDwn, LE_WIDGET_BORDER_NONE);
    SN_SET_tenDwn->fn->setPressedOffset(SN_SET_tenDwn, 0);
    SN_SET_tenDwn->fn->setPressedEventCallback(SN_SET_tenDwn, event_SN_SET_tenDwn_OnPressed);
    root0->fn->addChild(root0, (leWidget*)SN_SET_tenDwn);

    SN_SET_hundredUp = leButtonWidget_New();
    SN_SET_hundredUp->fn->setPosition(SN_SET_hundredUp, 241, 110);
    SN_SET_hundredUp->fn->setSize(SN_SET_hundredUp, 30, 60);
    SN_SET_hundredUp->fn->setBackgroundType(SN_SET_hundredUp, LE_WIDGET_BACKGROUND_NONE);
    SN_SET_hundredUp->fn->setBorderType(SN_SET_hundredUp, LE_WIDGET_BORDER_NONE);
    SN_SET_hundredUp->fn->setPressedOffset(SN_SET_hundredUp, 0);
    SN_SET_hundredUp->fn->setPressedEventCallback(SN_SET_hundredUp, event_SN_SET_hundredUp_OnPressed);
    root0->fn->addChild(root0, (leWidget*)SN_SET_hundredUp);

    SN_SET_hundredDwn = leButtonWidget_New();
    SN_SET_hundredDwn->fn->setPosition(SN_SET_hundredDwn, 241, 190);
    SN_SET_hundredDwn->fn->setSize(SN_SET_hundredDwn, 30, 60);
    SN_SET_hundredDwn->fn->setBackgroundType(SN_SET_hundredDwn, LE_WIDGET_BACKGROUND_NONE);
    SN_SET_hundredDwn->fn->setBorderType(SN_SET_hundredDwn, LE_WIDGET_BORDER_NONE);
    SN_SET_hundredDwn->fn->setPressedOffset(SN_SET_hundredDwn, 0);
    SN_SET_hundredDwn->fn->setPressedEventCallback(SN_SET_hundredDwn, event_SN_SET_hundredDwn_OnPressed);
    root0->fn->addChild(root0, (leWidget*)SN_SET_hundredDwn);

    SN_SET_thousandUp = leButtonWidget_New();
    SN_SET_thousandUp->fn->setPosition(SN_SET_thousandUp, 176, 111);
    SN_SET_thousandUp->fn->setSize(SN_SET_thousandUp, 30, 60);
    SN_SET_thousandUp->fn->setBackgroundType(SN_SET_thousandUp, LE_WIDGET_BACKGROUND_NONE);
    SN_SET_thousandUp->fn->setBorderType(SN_SET_thousandUp, LE_WIDGET_BORDER_NONE);
    SN_SET_thousandUp->fn->setPressedOffset(SN_SET_thousandUp, 0);
    SN_SET_thousandUp->fn->setPressedEventCallback(SN_SET_thousandUp, event_SN_SET_thousandUp_OnPressed);
    root0->fn->addChild(root0, (leWidget*)SN_SET_thousandUp);

    SN_SET_thousandDwn = leButtonWidget_New();
    SN_SET_thousandDwn->fn->setPosition(SN_SET_thousandDwn, 176, 190);
    SN_SET_thousandDwn->fn->setSize(SN_SET_thousandDwn, 30, 60);
    SN_SET_thousandDwn->fn->setBackgroundType(SN_SET_thousandDwn, LE_WIDGET_BACKGROUND_NONE);
    SN_SET_thousandDwn->fn->setBorderType(SN_SET_thousandDwn, LE_WIDGET_BORDER_NONE);
    SN_SET_thousandDwn->fn->setPressedOffset(SN_SET_thousandDwn, 0);
    SN_SET_thousandDwn->fn->setPressedEventCallback(SN_SET_thousandDwn, event_SN_SET_thousandDwn_OnPressed);
    root0->fn->addChild(root0, (leWidget*)SN_SET_thousandDwn);

    SN_SET_save = leButtonWidget_New();
    SN_SET_save->fn->setPosition(SN_SET_save, 22, 226);
    SN_SET_save->fn->setScheme(SN_SET_save, &BlackScheme);
    SN_SET_save->fn->setString(SN_SET_save, (leString*)&string_saveStr);
    SN_SET_save->fn->setPressedEventCallback(SN_SET_save, event_SN_SET_save_OnPressed);
    root0->fn->addChild(root0, (leWidget*)SN_SET_save);

    leAddRootWidget(root0, 0);
    leSetLayerColorMode(0, LE_COLOR_MODE_RGB_565);

    SN_SET_OnShow(); // raise event

    showing = LE_TRUE;

    return LE_SUCCESS;
}

void screenUpdate_SN_SET(void)
{
    root0->fn->setSize(root0, root0->rect.width, root0->rect.height);
}

void screenHide_SN_SET(void)
{

    leRemoveRootWidget(root0, 0);
    leWidget_Delete(root0);
    root0 = NULL;

    SN_SET_BackGnd = NULL;
    SN_SET_thousands = NULL;
    SN_SET_hundreds = NULL;
    SN_SET_tens = NULL;
    SN_SET_singles = NULL;
    SN_SET_LabelWidget_6 = NULL;
    SN_SET_ImageWidget_0 = NULL;
    SN_SET_ImageWidget_1 = NULL;
    SN_SET_ImageWidget_2 = NULL;
    SN_SET_ImageWidget_3 = NULL;
    SN_SET_oneUp = NULL;
    SN_SET_oneDwn = NULL;
    SN_SET_tenUp = NULL;
    SN_SET_tenDwn = NULL;
    SN_SET_hundredUp = NULL;
    SN_SET_hundredDwn = NULL;
    SN_SET_thousandUp = NULL;
    SN_SET_thousandDwn = NULL;
    SN_SET_save = NULL;


    showing = LE_FALSE;
}

void screenDestroy_SN_SET(void)
{
    if(initialized == LE_FALSE)
        return;

    initialized = LE_FALSE;
}

leWidget* screenGetRoot_SN_SET(uint32_t lyrIdx)
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

