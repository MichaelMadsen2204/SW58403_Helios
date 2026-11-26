#include "gfx/legato/generated/screen/le_gen_screen_renameInputsScreen.h"

// screen member widget declarations
static leWidget* root0;

leWidget* renameInputsScreen_Background;
leWidget* renameInputsScreen_digitalInputs;
leButtonWidget* renameInputsScreen_BackToMenuButttonWdgt;
leButtonWidget* renameInputsScreen_renameButtonWdgt;
leRectangleWidget* renameInputsScreen_RectangleWidget0;
leRectangleWidget* renameInputsScreen_RectangleWidget1;
leLabelWidget* renameInputsScreen_LabelWidget2;
leWidget* renameInputsScreen_analogInputs;
leLabelWidget* renameInputsScreen_LabelWidget1;
leButtonWidget* renameInputsScreen_selInp7ButWdgt;
leButtonWidget* renameInputsScreen_selInp8ButWdgt;
leButtonWidget* renameInputsScreen_selInp9ButWdgt;
leButtonWidget* renameInputsScreen_selInp10ButWdgt;
leButtonWidget* renameInputsScreen_selInp11ButWdgt;
leButtonWidget* renameInputsScreen_selInp1ButWdgt;
leButtonWidget* renameInputsScreen_selInp2ButWdgt;
leButtonWidget* renameInputsScreen_selInp3ButWdgt;
leButtonWidget* renameInputsScreen_selInp4ButWdgt;
leButtonWidget* renameInputsScreen_selInp5ButWdgt;
leLabelWidget* renameInputsScreen_LabelWidget0;
leButtonWidget* renameInputsScreen_selInp6ButWdgt;

static leBool initialized = LE_FALSE;
static leBool showing = LE_FALSE;

leResult screenInit_renameInputsScreen(void)
{
    if(initialized == LE_TRUE)
        return LE_FAILURE;

    initialized = LE_TRUE;

    return LE_SUCCESS;
}

leResult screenShow_renameInputsScreen(void)
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

    renameInputsScreen_Background = leWidget_New();
    renameInputsScreen_Background->fn->setPosition(renameInputsScreen_Background, 0, 0);
    renameInputsScreen_Background->fn->setSize(renameInputsScreen_Background, 480, 272);
    renameInputsScreen_Background->fn->setScheme(renameInputsScreen_Background, &BlackScheme);
    root0->fn->addChild(root0, (leWidget*)renameInputsScreen_Background);

    renameInputsScreen_digitalInputs = leWidget_New();
    renameInputsScreen_digitalInputs->fn->setPosition(renameInputsScreen_digitalInputs, 255, 25);
    renameInputsScreen_digitalInputs->fn->setSize(renameInputsScreen_digitalInputs, 175, 180);
    renameInputsScreen_digitalInputs->fn->setScheme(renameInputsScreen_digitalInputs, &BlackScheme);
    root0->fn->addChild(root0, (leWidget*)renameInputsScreen_digitalInputs);

    renameInputsScreen_LabelWidget1 = leLabelWidget_New();
    renameInputsScreen_LabelWidget1->fn->setPosition(renameInputsScreen_LabelWidget1, 2, 15);
    renameInputsScreen_LabelWidget1->fn->setSize(renameInputsScreen_LabelWidget1, 153, 25);
    renameInputsScreen_LabelWidget1->fn->setScheme(renameInputsScreen_LabelWidget1, &BlackScheme);
    renameInputsScreen_LabelWidget1->fn->setString(renameInputsScreen_LabelWidget1, (leString*)&string_actDigitalInpHeader);
    renameInputsScreen_digitalInputs->fn->addChild(renameInputsScreen_digitalInputs, (leWidget*)renameInputsScreen_LabelWidget1);

    renameInputsScreen_selInp7ButWdgt = leButtonWidget_New();
    renameInputsScreen_selInp7ButWdgt->fn->setPosition(renameInputsScreen_selInp7ButWdgt, 4, 35);
    renameInputsScreen_selInp7ButWdgt->fn->setSize(renameInputsScreen_selInp7ButWdgt, 170, 25);
    renameInputsScreen_selInp7ButWdgt->fn->setScheme(renameInputsScreen_selInp7ButWdgt, &BlackScheme);
    renameInputsScreen_selInp7ButWdgt->fn->setBackgroundType(renameInputsScreen_selInp7ButWdgt, LE_WIDGET_BACKGROUND_NONE);
    renameInputsScreen_selInp7ButWdgt->fn->setBorderType(renameInputsScreen_selInp7ButWdgt, LE_WIDGET_BORDER_NONE);
    renameInputsScreen_selInp7ButWdgt->fn->setHAlignment(renameInputsScreen_selInp7ButWdgt, LE_HALIGN_LEFT);
    renameInputsScreen_selInp7ButWdgt->fn->setVAlignment(renameInputsScreen_selInp7ButWdgt, LE_VALIGN_TOP);
    renameInputsScreen_selInp7ButWdgt->fn->setString(renameInputsScreen_selInp7ButWdgt, (leString*)&string_Inp7Name);
    renameInputsScreen_selInp7ButWdgt->fn->setPressedImage(renameInputsScreen_selInp7ButWdgt, (leImage*)&smallSelected2);
    renameInputsScreen_selInp7ButWdgt->fn->setReleasedImage(renameInputsScreen_selInp7ButWdgt, (leImage*)&smallNotSelected3);
    renameInputsScreen_selInp7ButWdgt->fn->setImageMargin(renameInputsScreen_selInp7ButWdgt, 4);
    renameInputsScreen_selInp7ButWdgt->fn->setPressedOffset(renameInputsScreen_selInp7ButWdgt, 0);
    renameInputsScreen_selInp7ButWdgt->fn->setPressedEventCallback(renameInputsScreen_selInp7ButWdgt, event_renameInputsScreen_selInp7ButWdgt_OnPressed);
    renameInputsScreen_digitalInputs->fn->addChild(renameInputsScreen_digitalInputs, (leWidget*)renameInputsScreen_selInp7ButWdgt);

    renameInputsScreen_selInp8ButWdgt = leButtonWidget_New();
    renameInputsScreen_selInp8ButWdgt->fn->setPosition(renameInputsScreen_selInp8ButWdgt, 4, 63);
    renameInputsScreen_selInp8ButWdgt->fn->setSize(renameInputsScreen_selInp8ButWdgt, 170, 25);
    renameInputsScreen_selInp8ButWdgt->fn->setScheme(renameInputsScreen_selInp8ButWdgt, &BlackScheme);
    renameInputsScreen_selInp8ButWdgt->fn->setBackgroundType(renameInputsScreen_selInp8ButWdgt, LE_WIDGET_BACKGROUND_NONE);
    renameInputsScreen_selInp8ButWdgt->fn->setBorderType(renameInputsScreen_selInp8ButWdgt, LE_WIDGET_BORDER_NONE);
    renameInputsScreen_selInp8ButWdgt->fn->setHAlignment(renameInputsScreen_selInp8ButWdgt, LE_HALIGN_LEFT);
    renameInputsScreen_selInp8ButWdgt->fn->setVAlignment(renameInputsScreen_selInp8ButWdgt, LE_VALIGN_TOP);
    renameInputsScreen_selInp8ButWdgt->fn->setString(renameInputsScreen_selInp8ButWdgt, (leString*)&string_Inp8Name);
    renameInputsScreen_selInp8ButWdgt->fn->setPressedImage(renameInputsScreen_selInp8ButWdgt, (leImage*)&smallSelected2);
    renameInputsScreen_selInp8ButWdgt->fn->setReleasedImage(renameInputsScreen_selInp8ButWdgt, (leImage*)&smallNotSelected3);
    renameInputsScreen_selInp8ButWdgt->fn->setImageMargin(renameInputsScreen_selInp8ButWdgt, 4);
    renameInputsScreen_selInp8ButWdgt->fn->setPressedOffset(renameInputsScreen_selInp8ButWdgt, 0);
    renameInputsScreen_selInp8ButWdgt->fn->setPressedEventCallback(renameInputsScreen_selInp8ButWdgt, event_renameInputsScreen_selInp8ButWdgt_OnPressed);
    renameInputsScreen_digitalInputs->fn->addChild(renameInputsScreen_digitalInputs, (leWidget*)renameInputsScreen_selInp8ButWdgt);

    renameInputsScreen_selInp9ButWdgt = leButtonWidget_New();
    renameInputsScreen_selInp9ButWdgt->fn->setPosition(renameInputsScreen_selInp9ButWdgt, 4, 91);
    renameInputsScreen_selInp9ButWdgt->fn->setSize(renameInputsScreen_selInp9ButWdgt, 170, 25);
    renameInputsScreen_selInp9ButWdgt->fn->setScheme(renameInputsScreen_selInp9ButWdgt, &BlackScheme);
    renameInputsScreen_selInp9ButWdgt->fn->setBackgroundType(renameInputsScreen_selInp9ButWdgt, LE_WIDGET_BACKGROUND_NONE);
    renameInputsScreen_selInp9ButWdgt->fn->setBorderType(renameInputsScreen_selInp9ButWdgt, LE_WIDGET_BORDER_NONE);
    renameInputsScreen_selInp9ButWdgt->fn->setHAlignment(renameInputsScreen_selInp9ButWdgt, LE_HALIGN_LEFT);
    renameInputsScreen_selInp9ButWdgt->fn->setVAlignment(renameInputsScreen_selInp9ButWdgt, LE_VALIGN_TOP);
    renameInputsScreen_selInp9ButWdgt->fn->setString(renameInputsScreen_selInp9ButWdgt, (leString*)&string_Inp9Name);
    renameInputsScreen_selInp9ButWdgt->fn->setPressedImage(renameInputsScreen_selInp9ButWdgt, (leImage*)&smallSelected2);
    renameInputsScreen_selInp9ButWdgt->fn->setReleasedImage(renameInputsScreen_selInp9ButWdgt, (leImage*)&smallNotSelected3);
    renameInputsScreen_selInp9ButWdgt->fn->setImageMargin(renameInputsScreen_selInp9ButWdgt, 4);
    renameInputsScreen_selInp9ButWdgt->fn->setPressedOffset(renameInputsScreen_selInp9ButWdgt, 0);
    renameInputsScreen_selInp9ButWdgt->fn->setPressedEventCallback(renameInputsScreen_selInp9ButWdgt, event_renameInputsScreen_selInp9ButWdgt_OnPressed);
    renameInputsScreen_digitalInputs->fn->addChild(renameInputsScreen_digitalInputs, (leWidget*)renameInputsScreen_selInp9ButWdgt);

    renameInputsScreen_selInp10ButWdgt = leButtonWidget_New();
    renameInputsScreen_selInp10ButWdgt->fn->setPosition(renameInputsScreen_selInp10ButWdgt, 4, 119);
    renameInputsScreen_selInp10ButWdgt->fn->setSize(renameInputsScreen_selInp10ButWdgt, 170, 25);
    renameInputsScreen_selInp10ButWdgt->fn->setScheme(renameInputsScreen_selInp10ButWdgt, &BlackScheme);
    renameInputsScreen_selInp10ButWdgt->fn->setBackgroundType(renameInputsScreen_selInp10ButWdgt, LE_WIDGET_BACKGROUND_NONE);
    renameInputsScreen_selInp10ButWdgt->fn->setBorderType(renameInputsScreen_selInp10ButWdgt, LE_WIDGET_BORDER_NONE);
    renameInputsScreen_selInp10ButWdgt->fn->setHAlignment(renameInputsScreen_selInp10ButWdgt, LE_HALIGN_LEFT);
    renameInputsScreen_selInp10ButWdgt->fn->setVAlignment(renameInputsScreen_selInp10ButWdgt, LE_VALIGN_TOP);
    renameInputsScreen_selInp10ButWdgt->fn->setString(renameInputsScreen_selInp10ButWdgt, (leString*)&string_Inp10Name);
    renameInputsScreen_selInp10ButWdgt->fn->setPressedImage(renameInputsScreen_selInp10ButWdgt, (leImage*)&smallSelected2);
    renameInputsScreen_selInp10ButWdgt->fn->setReleasedImage(renameInputsScreen_selInp10ButWdgt, (leImage*)&smallNotSelected3);
    renameInputsScreen_selInp10ButWdgt->fn->setImageMargin(renameInputsScreen_selInp10ButWdgt, 4);
    renameInputsScreen_selInp10ButWdgt->fn->setPressedOffset(renameInputsScreen_selInp10ButWdgt, 0);
    renameInputsScreen_selInp10ButWdgt->fn->setPressedEventCallback(renameInputsScreen_selInp10ButWdgt, event_renameInputsScreen_selInp10ButWdgt_OnPressed);
    renameInputsScreen_digitalInputs->fn->addChild(renameInputsScreen_digitalInputs, (leWidget*)renameInputsScreen_selInp10ButWdgt);

    renameInputsScreen_selInp11ButWdgt = leButtonWidget_New();
    renameInputsScreen_selInp11ButWdgt->fn->setPosition(renameInputsScreen_selInp11ButWdgt, 4, 147);
    renameInputsScreen_selInp11ButWdgt->fn->setSize(renameInputsScreen_selInp11ButWdgt, 170, 25);
    renameInputsScreen_selInp11ButWdgt->fn->setScheme(renameInputsScreen_selInp11ButWdgt, &BlackScheme);
    renameInputsScreen_selInp11ButWdgt->fn->setBackgroundType(renameInputsScreen_selInp11ButWdgt, LE_WIDGET_BACKGROUND_NONE);
    renameInputsScreen_selInp11ButWdgt->fn->setBorderType(renameInputsScreen_selInp11ButWdgt, LE_WIDGET_BORDER_NONE);
    renameInputsScreen_selInp11ButWdgt->fn->setHAlignment(renameInputsScreen_selInp11ButWdgt, LE_HALIGN_LEFT);
    renameInputsScreen_selInp11ButWdgt->fn->setVAlignment(renameInputsScreen_selInp11ButWdgt, LE_VALIGN_TOP);
    renameInputsScreen_selInp11ButWdgt->fn->setString(renameInputsScreen_selInp11ButWdgt, (leString*)&string_Inp11Name);
    renameInputsScreen_selInp11ButWdgt->fn->setPressedImage(renameInputsScreen_selInp11ButWdgt, (leImage*)&smallSelected2);
    renameInputsScreen_selInp11ButWdgt->fn->setReleasedImage(renameInputsScreen_selInp11ButWdgt, (leImage*)&smallNotSelected3);
    renameInputsScreen_selInp11ButWdgt->fn->setImageMargin(renameInputsScreen_selInp11ButWdgt, 4);
    renameInputsScreen_selInp11ButWdgt->fn->setPressedOffset(renameInputsScreen_selInp11ButWdgt, 0);
    renameInputsScreen_selInp11ButWdgt->fn->setPressedEventCallback(renameInputsScreen_selInp11ButWdgt, event_renameInputsScreen_selInp11ButWdgt_OnPressed);
    renameInputsScreen_digitalInputs->fn->addChild(renameInputsScreen_digitalInputs, (leWidget*)renameInputsScreen_selInp11ButWdgt);

    renameInputsScreen_BackToMenuButttonWdgt = leButtonWidget_New();
    renameInputsScreen_BackToMenuButttonWdgt->fn->setPosition(renameInputsScreen_BackToMenuButttonWdgt, 340, 205);
    renameInputsScreen_BackToMenuButttonWdgt->fn->setSize(renameInputsScreen_BackToMenuButttonWdgt, 110, 50);
    renameInputsScreen_BackToMenuButttonWdgt->fn->setBackgroundType(renameInputsScreen_BackToMenuButttonWdgt, LE_WIDGET_BACKGROUND_NONE);
    renameInputsScreen_BackToMenuButttonWdgt->fn->setBorderType(renameInputsScreen_BackToMenuButttonWdgt, LE_WIDGET_BORDER_NONE);
    renameInputsScreen_BackToMenuButttonWdgt->fn->setPressedImage(renameInputsScreen_BackToMenuButttonWdgt, (leImage*)&BackToMenu);
    renameInputsScreen_BackToMenuButttonWdgt->fn->setReleasedImage(renameInputsScreen_BackToMenuButttonWdgt, (leImage*)&BackToMenu);
    renameInputsScreen_BackToMenuButttonWdgt->fn->setPressedOffset(renameInputsScreen_BackToMenuButttonWdgt, 0);
    renameInputsScreen_BackToMenuButttonWdgt->fn->setReleasedEventCallback(renameInputsScreen_BackToMenuButttonWdgt, event_renameInputsScreen_BackToMenuButttonWdgt_OnReleased);
    root0->fn->addChild(root0, (leWidget*)renameInputsScreen_BackToMenuButttonWdgt);

    renameInputsScreen_renameButtonWdgt = leButtonWidget_New();
    renameInputsScreen_renameButtonWdgt->fn->setPosition(renameInputsScreen_renameButtonWdgt, 200, 207);
    renameInputsScreen_renameButtonWdgt->fn->setSize(renameInputsScreen_renameButtonWdgt, 124, 47);
    renameInputsScreen_renameButtonWdgt->fn->setScheme(renameInputsScreen_renameButtonWdgt, &BlackScheme);
    renameInputsScreen_renameButtonWdgt->fn->setBackgroundType(renameInputsScreen_renameButtonWdgt, LE_WIDGET_BACKGROUND_NONE);
    renameInputsScreen_renameButtonWdgt->fn->setString(renameInputsScreen_renameButtonWdgt, (leString*)&string_RenameInputButtonStr);
    renameInputsScreen_renameButtonWdgt->fn->setPressedEventCallback(renameInputsScreen_renameButtonWdgt, event_renameInputsScreen_renameButtonWdgt_OnPressed);
    root0->fn->addChild(root0, (leWidget*)renameInputsScreen_renameButtonWdgt);

    renameInputsScreen_RectangleWidget0 = leRectangleWidget_New();
    renameInputsScreen_RectangleWidget0->fn->setPosition(renameInputsScreen_RectangleWidget0, 26, 25);
    renameInputsScreen_RectangleWidget0->fn->setSize(renameInputsScreen_RectangleWidget0, 135, 3);
    renameInputsScreen_RectangleWidget0->fn->setScheme(renameInputsScreen_RectangleWidget0, &WhiteScheme);
    renameInputsScreen_RectangleWidget0->fn->setBorderType(renameInputsScreen_RectangleWidget0, LE_WIDGET_BORDER_NONE);
    renameInputsScreen_RectangleWidget0->fn->setThickness(renameInputsScreen_RectangleWidget0, 2);
    root0->fn->addChild(root0, (leWidget*)renameInputsScreen_RectangleWidget0);

    renameInputsScreen_RectangleWidget1 = leRectangleWidget_New();
    renameInputsScreen_RectangleWidget1->fn->setPosition(renameInputsScreen_RectangleWidget1, 319, 25);
    renameInputsScreen_RectangleWidget1->fn->setSize(renameInputsScreen_RectangleWidget1, 135, 3);
    renameInputsScreen_RectangleWidget1->fn->setScheme(renameInputsScreen_RectangleWidget1, &WhiteScheme);
    renameInputsScreen_RectangleWidget1->fn->setBorderType(renameInputsScreen_RectangleWidget1, LE_WIDGET_BORDER_NONE);
    renameInputsScreen_RectangleWidget1->fn->setThickness(renameInputsScreen_RectangleWidget1, 2);
    root0->fn->addChild(root0, (leWidget*)renameInputsScreen_RectangleWidget1);

    renameInputsScreen_LabelWidget2 = leLabelWidget_New();
    renameInputsScreen_LabelWidget2->fn->setPosition(renameInputsScreen_LabelWidget2, 0, 12);
    renameInputsScreen_LabelWidget2->fn->setSize(renameInputsScreen_LabelWidget2, 480, 25);
    renameInputsScreen_LabelWidget2->fn->setScheme(renameInputsScreen_LabelWidget2, &BlackScheme);
    renameInputsScreen_LabelWidget2->fn->setBackgroundType(renameInputsScreen_LabelWidget2, LE_WIDGET_BACKGROUND_NONE);
    renameInputsScreen_LabelWidget2->fn->setHAlignment(renameInputsScreen_LabelWidget2, LE_HALIGN_CENTER);
    renameInputsScreen_LabelWidget2->fn->setString(renameInputsScreen_LabelWidget2, (leString*)&string_editInputNameStr);
    root0->fn->addChild(root0, (leWidget*)renameInputsScreen_LabelWidget2);

    renameInputsScreen_analogInputs = leWidget_New();
    renameInputsScreen_analogInputs->fn->setPosition(renameInputsScreen_analogInputs, 21, 24);
    renameInputsScreen_analogInputs->fn->setSize(renameInputsScreen_analogInputs, 175, 210);
    renameInputsScreen_analogInputs->fn->setScheme(renameInputsScreen_analogInputs, &BlackScheme);
    renameInputsScreen_analogInputs->fn->setBackgroundType(renameInputsScreen_analogInputs, LE_WIDGET_BACKGROUND_NONE);
    root0->fn->addChild(root0, (leWidget*)renameInputsScreen_analogInputs);

    renameInputsScreen_selInp1ButWdgt = leButtonWidget_New();
    renameInputsScreen_selInp1ButWdgt->fn->setPosition(renameInputsScreen_selInp1ButWdgt, 4, 35);
    renameInputsScreen_selInp1ButWdgt->fn->setSize(renameInputsScreen_selInp1ButWdgt, 170, 25);
    renameInputsScreen_selInp1ButWdgt->fn->setEnabled(renameInputsScreen_selInp1ButWdgt, LE_FALSE);
    renameInputsScreen_selInp1ButWdgt->fn->setScheme(renameInputsScreen_selInp1ButWdgt, &BlackScheme);
    renameInputsScreen_selInp1ButWdgt->fn->setBorderType(renameInputsScreen_selInp1ButWdgt, LE_WIDGET_BORDER_NONE);
    renameInputsScreen_selInp1ButWdgt->fn->setHAlignment(renameInputsScreen_selInp1ButWdgt, LE_HALIGN_LEFT);
    renameInputsScreen_selInp1ButWdgt->fn->setVAlignment(renameInputsScreen_selInp1ButWdgt, LE_VALIGN_TOP);
    renameInputsScreen_selInp1ButWdgt->fn->setString(renameInputsScreen_selInp1ButWdgt, (leString*)&string_Inp1Name);
    renameInputsScreen_selInp1ButWdgt->fn->setPressedImage(renameInputsScreen_selInp1ButWdgt, (leImage*)&smallSelected2);
    renameInputsScreen_selInp1ButWdgt->fn->setReleasedImage(renameInputsScreen_selInp1ButWdgt, (leImage*)&smallNotSelected3);
    renameInputsScreen_selInp1ButWdgt->fn->setImageMargin(renameInputsScreen_selInp1ButWdgt, 4);
    renameInputsScreen_selInp1ButWdgt->fn->setPressedOffset(renameInputsScreen_selInp1ButWdgt, 0);
    renameInputsScreen_selInp1ButWdgt->fn->setPressedEventCallback(renameInputsScreen_selInp1ButWdgt, event_renameInputsScreen_selInp1ButWdgt_OnPressed);
    renameInputsScreen_analogInputs->fn->addChild(renameInputsScreen_analogInputs, (leWidget*)renameInputsScreen_selInp1ButWdgt);

    renameInputsScreen_selInp2ButWdgt = leButtonWidget_New();
    renameInputsScreen_selInp2ButWdgt->fn->setPosition(renameInputsScreen_selInp2ButWdgt, 4, 63);
    renameInputsScreen_selInp2ButWdgt->fn->setSize(renameInputsScreen_selInp2ButWdgt, 170, 25);
    renameInputsScreen_selInp2ButWdgt->fn->setScheme(renameInputsScreen_selInp2ButWdgt, &BlackScheme);
    renameInputsScreen_selInp2ButWdgt->fn->setBackgroundType(renameInputsScreen_selInp2ButWdgt, LE_WIDGET_BACKGROUND_NONE);
    renameInputsScreen_selInp2ButWdgt->fn->setBorderType(renameInputsScreen_selInp2ButWdgt, LE_WIDGET_BORDER_NONE);
    renameInputsScreen_selInp2ButWdgt->fn->setHAlignment(renameInputsScreen_selInp2ButWdgt, LE_HALIGN_LEFT);
    renameInputsScreen_selInp2ButWdgt->fn->setVAlignment(renameInputsScreen_selInp2ButWdgt, LE_VALIGN_TOP);
    renameInputsScreen_selInp2ButWdgt->fn->setString(renameInputsScreen_selInp2ButWdgt, (leString*)&string_Inp2Name);
    renameInputsScreen_selInp2ButWdgt->fn->setPressedImage(renameInputsScreen_selInp2ButWdgt, (leImage*)&smallSelected2);
    renameInputsScreen_selInp2ButWdgt->fn->setReleasedImage(renameInputsScreen_selInp2ButWdgt, (leImage*)&smallNotSelected3);
    renameInputsScreen_selInp2ButWdgt->fn->setImageMargin(renameInputsScreen_selInp2ButWdgt, 4);
    renameInputsScreen_selInp2ButWdgt->fn->setPressedOffset(renameInputsScreen_selInp2ButWdgt, 0);
    renameInputsScreen_selInp2ButWdgt->fn->setPressedEventCallback(renameInputsScreen_selInp2ButWdgt, event_renameInputsScreen_selInp2ButWdgt_OnPressed);
    renameInputsScreen_analogInputs->fn->addChild(renameInputsScreen_analogInputs, (leWidget*)renameInputsScreen_selInp2ButWdgt);

    renameInputsScreen_selInp3ButWdgt = leButtonWidget_New();
    renameInputsScreen_selInp3ButWdgt->fn->setPosition(renameInputsScreen_selInp3ButWdgt, 4, 91);
    renameInputsScreen_selInp3ButWdgt->fn->setSize(renameInputsScreen_selInp3ButWdgt, 170, 25);
    renameInputsScreen_selInp3ButWdgt->fn->setScheme(renameInputsScreen_selInp3ButWdgt, &BlackScheme);
    renameInputsScreen_selInp3ButWdgt->fn->setBackgroundType(renameInputsScreen_selInp3ButWdgt, LE_WIDGET_BACKGROUND_NONE);
    renameInputsScreen_selInp3ButWdgt->fn->setBorderType(renameInputsScreen_selInp3ButWdgt, LE_WIDGET_BORDER_NONE);
    renameInputsScreen_selInp3ButWdgt->fn->setHAlignment(renameInputsScreen_selInp3ButWdgt, LE_HALIGN_LEFT);
    renameInputsScreen_selInp3ButWdgt->fn->setVAlignment(renameInputsScreen_selInp3ButWdgt, LE_VALIGN_TOP);
    renameInputsScreen_selInp3ButWdgt->fn->setString(renameInputsScreen_selInp3ButWdgt, (leString*)&string_inp3Name);
    renameInputsScreen_selInp3ButWdgt->fn->setPressedImage(renameInputsScreen_selInp3ButWdgt, (leImage*)&smallSelected2);
    renameInputsScreen_selInp3ButWdgt->fn->setReleasedImage(renameInputsScreen_selInp3ButWdgt, (leImage*)&smallNotSelected3);
    renameInputsScreen_selInp3ButWdgt->fn->setImageMargin(renameInputsScreen_selInp3ButWdgt, 4);
    renameInputsScreen_selInp3ButWdgt->fn->setPressedOffset(renameInputsScreen_selInp3ButWdgt, 0);
    renameInputsScreen_selInp3ButWdgt->fn->setPressedEventCallback(renameInputsScreen_selInp3ButWdgt, event_renameInputsScreen_selInp3ButWdgt_OnPressed);
    renameInputsScreen_analogInputs->fn->addChild(renameInputsScreen_analogInputs, (leWidget*)renameInputsScreen_selInp3ButWdgt);

    renameInputsScreen_selInp4ButWdgt = leButtonWidget_New();
    renameInputsScreen_selInp4ButWdgt->fn->setPosition(renameInputsScreen_selInp4ButWdgt, 4, 119);
    renameInputsScreen_selInp4ButWdgt->fn->setSize(renameInputsScreen_selInp4ButWdgt, 170, 25);
    renameInputsScreen_selInp4ButWdgt->fn->setScheme(renameInputsScreen_selInp4ButWdgt, &BlackScheme);
    renameInputsScreen_selInp4ButWdgt->fn->setBackgroundType(renameInputsScreen_selInp4ButWdgt, LE_WIDGET_BACKGROUND_NONE);
    renameInputsScreen_selInp4ButWdgt->fn->setBorderType(renameInputsScreen_selInp4ButWdgt, LE_WIDGET_BORDER_NONE);
    renameInputsScreen_selInp4ButWdgt->fn->setHAlignment(renameInputsScreen_selInp4ButWdgt, LE_HALIGN_LEFT);
    renameInputsScreen_selInp4ButWdgt->fn->setVAlignment(renameInputsScreen_selInp4ButWdgt, LE_VALIGN_TOP);
    renameInputsScreen_selInp4ButWdgt->fn->setString(renameInputsScreen_selInp4ButWdgt, (leString*)&string_Inp4Name);
    renameInputsScreen_selInp4ButWdgt->fn->setPressedImage(renameInputsScreen_selInp4ButWdgt, (leImage*)&smallSelected2);
    renameInputsScreen_selInp4ButWdgt->fn->setReleasedImage(renameInputsScreen_selInp4ButWdgt, (leImage*)&smallNotSelected3);
    renameInputsScreen_selInp4ButWdgt->fn->setImageMargin(renameInputsScreen_selInp4ButWdgt, 4);
    renameInputsScreen_selInp4ButWdgt->fn->setPressedOffset(renameInputsScreen_selInp4ButWdgt, 0);
    renameInputsScreen_selInp4ButWdgt->fn->setPressedEventCallback(renameInputsScreen_selInp4ButWdgt, event_renameInputsScreen_selInp4ButWdgt_OnPressed);
    renameInputsScreen_analogInputs->fn->addChild(renameInputsScreen_analogInputs, (leWidget*)renameInputsScreen_selInp4ButWdgt);

    renameInputsScreen_selInp5ButWdgt = leButtonWidget_New();
    renameInputsScreen_selInp5ButWdgt->fn->setPosition(renameInputsScreen_selInp5ButWdgt, 4, 147);
    renameInputsScreen_selInp5ButWdgt->fn->setSize(renameInputsScreen_selInp5ButWdgt, 170, 25);
    renameInputsScreen_selInp5ButWdgt->fn->setScheme(renameInputsScreen_selInp5ButWdgt, &BlackScheme);
    renameInputsScreen_selInp5ButWdgt->fn->setBackgroundType(renameInputsScreen_selInp5ButWdgt, LE_WIDGET_BACKGROUND_NONE);
    renameInputsScreen_selInp5ButWdgt->fn->setBorderType(renameInputsScreen_selInp5ButWdgt, LE_WIDGET_BORDER_NONE);
    renameInputsScreen_selInp5ButWdgt->fn->setHAlignment(renameInputsScreen_selInp5ButWdgt, LE_HALIGN_LEFT);
    renameInputsScreen_selInp5ButWdgt->fn->setVAlignment(renameInputsScreen_selInp5ButWdgt, LE_VALIGN_TOP);
    renameInputsScreen_selInp5ButWdgt->fn->setString(renameInputsScreen_selInp5ButWdgt, (leString*)&string_Inp5Name);
    renameInputsScreen_selInp5ButWdgt->fn->setPressedImage(renameInputsScreen_selInp5ButWdgt, (leImage*)&smallSelected2);
    renameInputsScreen_selInp5ButWdgt->fn->setReleasedImage(renameInputsScreen_selInp5ButWdgt, (leImage*)&smallNotSelected3);
    renameInputsScreen_selInp5ButWdgt->fn->setImageMargin(renameInputsScreen_selInp5ButWdgt, 4);
    renameInputsScreen_selInp5ButWdgt->fn->setPressedOffset(renameInputsScreen_selInp5ButWdgt, 0);
    renameInputsScreen_selInp5ButWdgt->fn->setPressedEventCallback(renameInputsScreen_selInp5ButWdgt, event_renameInputsScreen_selInp5ButWdgt_OnPressed);
    renameInputsScreen_analogInputs->fn->addChild(renameInputsScreen_analogInputs, (leWidget*)renameInputsScreen_selInp5ButWdgt);

    renameInputsScreen_LabelWidget0 = leLabelWidget_New();
    renameInputsScreen_LabelWidget0->fn->setPosition(renameInputsScreen_LabelWidget0, 4, 15);
    renameInputsScreen_LabelWidget0->fn->setSize(renameInputsScreen_LabelWidget0, 163, 25);
    renameInputsScreen_LabelWidget0->fn->setScheme(renameInputsScreen_LabelWidget0, &BlackScheme);
    renameInputsScreen_LabelWidget0->fn->setBackgroundType(renameInputsScreen_LabelWidget0, LE_WIDGET_BACKGROUND_NONE);
    renameInputsScreen_LabelWidget0->fn->setString(renameInputsScreen_LabelWidget0, (leString*)&string_actAnalogInpHeader);
    renameInputsScreen_analogInputs->fn->addChild(renameInputsScreen_analogInputs, (leWidget*)renameInputsScreen_LabelWidget0);

    renameInputsScreen_selInp6ButWdgt = leButtonWidget_New();
    renameInputsScreen_selInp6ButWdgt->fn->setPosition(renameInputsScreen_selInp6ButWdgt, 4, 175);
    renameInputsScreen_selInp6ButWdgt->fn->setSize(renameInputsScreen_selInp6ButWdgt, 170, 25);
    renameInputsScreen_selInp6ButWdgt->fn->setScheme(renameInputsScreen_selInp6ButWdgt, &BlackScheme);
    renameInputsScreen_selInp6ButWdgt->fn->setBackgroundType(renameInputsScreen_selInp6ButWdgt, LE_WIDGET_BACKGROUND_NONE);
    renameInputsScreen_selInp6ButWdgt->fn->setBorderType(renameInputsScreen_selInp6ButWdgt, LE_WIDGET_BORDER_NONE);
    renameInputsScreen_selInp6ButWdgt->fn->setHAlignment(renameInputsScreen_selInp6ButWdgt, LE_HALIGN_LEFT);
    renameInputsScreen_selInp6ButWdgt->fn->setVAlignment(renameInputsScreen_selInp6ButWdgt, LE_VALIGN_TOP);
    renameInputsScreen_selInp6ButWdgt->fn->setString(renameInputsScreen_selInp6ButWdgt, (leString*)&string_Inp6Name);
    renameInputsScreen_selInp6ButWdgt->fn->setPressedImage(renameInputsScreen_selInp6ButWdgt, (leImage*)&smallSelected2);
    renameInputsScreen_selInp6ButWdgt->fn->setReleasedImage(renameInputsScreen_selInp6ButWdgt, (leImage*)&smallNotSelected3);
    renameInputsScreen_selInp6ButWdgt->fn->setImageMargin(renameInputsScreen_selInp6ButWdgt, 4);
    renameInputsScreen_selInp6ButWdgt->fn->setPressedOffset(renameInputsScreen_selInp6ButWdgt, 0);
    renameInputsScreen_selInp6ButWdgt->fn->setPressedEventCallback(renameInputsScreen_selInp6ButWdgt, event_renameInputsScreen_selInp6ButWdgt_OnPressed);
    renameInputsScreen_analogInputs->fn->addChild(renameInputsScreen_analogInputs, (leWidget*)renameInputsScreen_selInp6ButWdgt);

    leAddRootWidget(root0, 0);
    leSetLayerColorMode(0, LE_COLOR_MODE_RGB_565);

    renameInputsScreen_OnShow(); // raise event

    showing = LE_TRUE;

    return LE_SUCCESS;
}

void screenUpdate_renameInputsScreen(void)
{
    root0->fn->setSize(root0, root0->rect.width, root0->rect.height);
}

void screenHide_renameInputsScreen(void)
{
    renameInputsScreen_OnHide(); // raise event


    leRemoveRootWidget(root0, 0);
    leWidget_Delete(root0);
    root0 = NULL;

    renameInputsScreen_Background = NULL;
    renameInputsScreen_digitalInputs = NULL;
    renameInputsScreen_BackToMenuButttonWdgt = NULL;
    renameInputsScreen_renameButtonWdgt = NULL;
    renameInputsScreen_RectangleWidget0 = NULL;
    renameInputsScreen_RectangleWidget1 = NULL;
    renameInputsScreen_LabelWidget2 = NULL;
    renameInputsScreen_analogInputs = NULL;
    renameInputsScreen_LabelWidget1 = NULL;
    renameInputsScreen_selInp7ButWdgt = NULL;
    renameInputsScreen_selInp8ButWdgt = NULL;
    renameInputsScreen_selInp9ButWdgt = NULL;
    renameInputsScreen_selInp10ButWdgt = NULL;
    renameInputsScreen_selInp11ButWdgt = NULL;
    renameInputsScreen_selInp1ButWdgt = NULL;
    renameInputsScreen_selInp2ButWdgt = NULL;
    renameInputsScreen_selInp3ButWdgt = NULL;
    renameInputsScreen_selInp4ButWdgt = NULL;
    renameInputsScreen_selInp5ButWdgt = NULL;
    renameInputsScreen_LabelWidget0 = NULL;
    renameInputsScreen_selInp6ButWdgt = NULL;


    showing = LE_FALSE;
}

void screenDestroy_renameInputsScreen(void)
{
    if(initialized == LE_FALSE)
        return;

    initialized = LE_FALSE;
}

leWidget* screenGetRoot_renameInputsScreen(uint32_t lyrIdx)
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

