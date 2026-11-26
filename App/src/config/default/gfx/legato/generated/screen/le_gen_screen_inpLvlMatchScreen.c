#include "gfx/legato/generated/screen/le_gen_screen_inpLvlMatchScreen.h"

// screen member widget declarations
static leWidget* root0;

leWidget* inpLvlMatchScreen_background;
leButtonWidget* inpLvlMatchScreen_inpBut_1;
leButtonWidget* inpLvlMatchScreen_inpBut_2;
leButtonWidget* inpLvlMatchScreen_inpBut_3;
leButtonWidget* inpLvlMatchScreen_inpBut_4;
leButtonWidget* inpLvlMatchScreen_inpBut_5;
leButtonWidget* inpLvlMatchScreen_inpBut_6;
leLabelWidget* inpLvlMatchScreen_inpLvlMatchValue_1;
leLabelWidget* inpLvlMatchScreen_inpLvlMatchValue_2;
leLabelWidget* inpLvlMatchScreen_inpLvlMatchValue_3;
leLabelWidget* inpLvlMatchScreen_inpLvlMatchValue_4;
leLabelWidget* inpLvlMatchScreen_inpLvlMatchValue_5;
leLabelWidget* inpLvlMatchScreen_inpLvlMatchValue_6;
leImageWidget* inpLvlMatchScreen_maxVolButImg;
leImageWidget* inpLvlMatchScreen_inpSenseBackToMenuImg;
leLabelWidget* inpLvlMatchScreen_inpSenseMenuHeader;
leRectangleWidget* inpLvlMatchScreen_inPSenseLineRightSide;
leRectangleWidget* inpLvlMatchScreen_inpSenseLineLeftSide;
leButtonWidget* inpLvlMatchScreen_inpLvlMatchPlusBut;
leButtonWidget* inpLvlMatchScreen_inpLvlMatchMinusBut;
leButtonWidget* inpLvlMatchScreen_inpSenseBackToMenuBut;

static leBool initialized = LE_FALSE;
static leBool showing = LE_FALSE;

leResult screenInit_inpLvlMatchScreen(void)
{
    if(initialized == LE_TRUE)
        return LE_FAILURE;

    initialized = LE_TRUE;

    return LE_SUCCESS;
}

leResult screenShow_inpLvlMatchScreen(void)
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

    inpLvlMatchScreen_background = leWidget_New();
    inpLvlMatchScreen_background->fn->setPosition(inpLvlMatchScreen_background, 0, 0);
    inpLvlMatchScreen_background->fn->setSize(inpLvlMatchScreen_background, 480, 272);
    inpLvlMatchScreen_background->fn->setScheme(inpLvlMatchScreen_background, &BlackScheme);
    root0->fn->addChild(root0, (leWidget*)inpLvlMatchScreen_background);

    inpLvlMatchScreen_maxVolButImg = leImageWidget_New();
    inpLvlMatchScreen_maxVolButImg->fn->setPosition(inpLvlMatchScreen_maxVolButImg, 363, 58);
    inpLvlMatchScreen_maxVolButImg->fn->setSize(inpLvlMatchScreen_maxVolButImg, 75, 124);
    inpLvlMatchScreen_maxVolButImg->fn->setScheme(inpLvlMatchScreen_maxVolButImg, &BlackScheme);
    inpLvlMatchScreen_maxVolButImg->fn->setBorderType(inpLvlMatchScreen_maxVolButImg, LE_WIDGET_BORDER_NONE);
    inpLvlMatchScreen_maxVolButImg->fn->setImage(inpLvlMatchScreen_maxVolButImg, (leImage*)&ILMVolButtons);
    inpLvlMatchScreen_background->fn->addChild(inpLvlMatchScreen_background, (leWidget*)inpLvlMatchScreen_maxVolButImg);

    inpLvlMatchScreen_inpLvlMatchPlusBut = leButtonWidget_New();
    inpLvlMatchScreen_inpLvlMatchPlusBut->fn->setPosition(inpLvlMatchScreen_inpLvlMatchPlusBut, 4, -5);
    inpLvlMatchScreen_inpLvlMatchPlusBut->fn->setSize(inpLvlMatchScreen_inpLvlMatchPlusBut, 64, 58);
    inpLvlMatchScreen_inpLvlMatchPlusBut->fn->setBackgroundType(inpLvlMatchScreen_inpLvlMatchPlusBut, LE_WIDGET_BACKGROUND_NONE);
    inpLvlMatchScreen_inpLvlMatchPlusBut->fn->setBorderType(inpLvlMatchScreen_inpLvlMatchPlusBut, LE_WIDGET_BORDER_NONE);
    inpLvlMatchScreen_inpLvlMatchPlusBut->fn->setPressedEventCallback(inpLvlMatchScreen_inpLvlMatchPlusBut, event_inpLvlMatchScreen_inpLvlMatchPlusBut_OnPressed);
    inpLvlMatchScreen_inpLvlMatchPlusBut->fn->setReleasedEventCallback(inpLvlMatchScreen_inpLvlMatchPlusBut, event_inpLvlMatchScreen_inpLvlMatchPlusBut_OnReleased);
    inpLvlMatchScreen_maxVolButImg->fn->addChild(inpLvlMatchScreen_maxVolButImg, (leWidget*)inpLvlMatchScreen_inpLvlMatchPlusBut);

    inpLvlMatchScreen_inpLvlMatchMinusBut = leButtonWidget_New();
    inpLvlMatchScreen_inpLvlMatchMinusBut->fn->setPosition(inpLvlMatchScreen_inpLvlMatchMinusBut, 6, 71);
    inpLvlMatchScreen_inpLvlMatchMinusBut->fn->setSize(inpLvlMatchScreen_inpLvlMatchMinusBut, 64, 56);
    inpLvlMatchScreen_inpLvlMatchMinusBut->fn->setBackgroundType(inpLvlMatchScreen_inpLvlMatchMinusBut, LE_WIDGET_BACKGROUND_NONE);
    inpLvlMatchScreen_inpLvlMatchMinusBut->fn->setBorderType(inpLvlMatchScreen_inpLvlMatchMinusBut, LE_WIDGET_BORDER_NONE);
    inpLvlMatchScreen_inpLvlMatchMinusBut->fn->setPressedEventCallback(inpLvlMatchScreen_inpLvlMatchMinusBut, event_inpLvlMatchScreen_inpLvlMatchMinusBut_OnPressed);
    inpLvlMatchScreen_inpLvlMatchMinusBut->fn->setReleasedEventCallback(inpLvlMatchScreen_inpLvlMatchMinusBut, event_inpLvlMatchScreen_inpLvlMatchMinusBut_OnReleased);
    inpLvlMatchScreen_maxVolButImg->fn->addChild(inpLvlMatchScreen_maxVolButImg, (leWidget*)inpLvlMatchScreen_inpLvlMatchMinusBut);

    inpLvlMatchScreen_inpSenseBackToMenuImg = leImageWidget_New();
    inpLvlMatchScreen_inpSenseBackToMenuImg->fn->setPosition(inpLvlMatchScreen_inpSenseBackToMenuImg, 340, 205);
    inpLvlMatchScreen_inpSenseBackToMenuImg->fn->setSize(inpLvlMatchScreen_inpSenseBackToMenuImg, 110, 50);
    inpLvlMatchScreen_inpSenseBackToMenuImg->fn->setScheme(inpLvlMatchScreen_inpSenseBackToMenuImg, &BlackScheme);
    inpLvlMatchScreen_inpSenseBackToMenuImg->fn->setBorderType(inpLvlMatchScreen_inpSenseBackToMenuImg, LE_WIDGET_BORDER_NONE);
    inpLvlMatchScreen_inpSenseBackToMenuImg->fn->setImage(inpLvlMatchScreen_inpSenseBackToMenuImg, (leImage*)&BackToMenu);
    inpLvlMatchScreen_background->fn->addChild(inpLvlMatchScreen_background, (leWidget*)inpLvlMatchScreen_inpSenseBackToMenuImg);

    inpLvlMatchScreen_inpSenseBackToMenuBut = leButtonWidget_New();
    inpLvlMatchScreen_inpSenseBackToMenuBut->fn->setPosition(inpLvlMatchScreen_inpSenseBackToMenuBut, 2, 3);
    inpLvlMatchScreen_inpSenseBackToMenuBut->fn->setSize(inpLvlMatchScreen_inpSenseBackToMenuBut, 111, 49);
    inpLvlMatchScreen_inpSenseBackToMenuBut->fn->setBackgroundType(inpLvlMatchScreen_inpSenseBackToMenuBut, LE_WIDGET_BACKGROUND_NONE);
    inpLvlMatchScreen_inpSenseBackToMenuBut->fn->setBorderType(inpLvlMatchScreen_inpSenseBackToMenuBut, LE_WIDGET_BORDER_NONE);
    inpLvlMatchScreen_inpSenseBackToMenuBut->fn->setPressedEventCallback(inpLvlMatchScreen_inpSenseBackToMenuBut, event_inpLvlMatchScreen_inpSenseBackToMenuBut_OnPressed);
    inpLvlMatchScreen_inpSenseBackToMenuImg->fn->addChild(inpLvlMatchScreen_inpSenseBackToMenuImg, (leWidget*)inpLvlMatchScreen_inpSenseBackToMenuBut);

    inpLvlMatchScreen_inpSenseMenuHeader = leLabelWidget_New();
    inpLvlMatchScreen_inpSenseMenuHeader->fn->setPosition(inpLvlMatchScreen_inpSenseMenuHeader, 0, 12);
    inpLvlMatchScreen_inpSenseMenuHeader->fn->setSize(inpLvlMatchScreen_inpSenseMenuHeader, 480, 25);
    inpLvlMatchScreen_inpSenseMenuHeader->fn->setScheme(inpLvlMatchScreen_inpSenseMenuHeader, &BlackScheme);
    inpLvlMatchScreen_inpSenseMenuHeader->fn->setBackgroundType(inpLvlMatchScreen_inpSenseMenuHeader, LE_WIDGET_BACKGROUND_NONE);
    inpLvlMatchScreen_inpSenseMenuHeader->fn->setHAlignment(inpLvlMatchScreen_inpSenseMenuHeader, LE_HALIGN_CENTER);
    inpLvlMatchScreen_inpSenseMenuHeader->fn->setString(inpLvlMatchScreen_inpSenseMenuHeader, (leString*)&string_inpSenseHeaderStr);
    inpLvlMatchScreen_background->fn->addChild(inpLvlMatchScreen_background, (leWidget*)inpLvlMatchScreen_inpSenseMenuHeader);

    inpLvlMatchScreen_inPSenseLineRightSide = leRectangleWidget_New();
    inpLvlMatchScreen_inPSenseLineRightSide->fn->setPosition(inpLvlMatchScreen_inPSenseLineRightSide, 344, 25);
    inpLvlMatchScreen_inPSenseLineRightSide->fn->setSize(inpLvlMatchScreen_inPSenseLineRightSide, 110, 3);
    inpLvlMatchScreen_inPSenseLineRightSide->fn->setScheme(inpLvlMatchScreen_inPSenseLineRightSide, &WhiteScheme);
    inpLvlMatchScreen_inPSenseLineRightSide->fn->setBorderType(inpLvlMatchScreen_inPSenseLineRightSide, LE_WIDGET_BORDER_NONE);
    inpLvlMatchScreen_inPSenseLineRightSide->fn->setThickness(inpLvlMatchScreen_inPSenseLineRightSide, 3);
    inpLvlMatchScreen_background->fn->addChild(inpLvlMatchScreen_background, (leWidget*)inpLvlMatchScreen_inPSenseLineRightSide);

    inpLvlMatchScreen_inpSenseLineLeftSide = leRectangleWidget_New();
    inpLvlMatchScreen_inpSenseLineLeftSide->fn->setPosition(inpLvlMatchScreen_inpSenseLineLeftSide, 26, 25);
    inpLvlMatchScreen_inpSenseLineLeftSide->fn->setSize(inpLvlMatchScreen_inpSenseLineLeftSide, 110, 3);
    inpLvlMatchScreen_inpSenseLineLeftSide->fn->setScheme(inpLvlMatchScreen_inpSenseLineLeftSide, &WhiteScheme);
    inpLvlMatchScreen_inpSenseLineLeftSide->fn->setBorderType(inpLvlMatchScreen_inpSenseLineLeftSide, LE_WIDGET_BORDER_NONE);
    inpLvlMatchScreen_inpSenseLineLeftSide->fn->setThickness(inpLvlMatchScreen_inpSenseLineLeftSide, 3);
    inpLvlMatchScreen_background->fn->addChild(inpLvlMatchScreen_background, (leWidget*)inpLvlMatchScreen_inpSenseLineLeftSide);

    inpLvlMatchScreen_inpBut_1 = leButtonWidget_New();
    inpLvlMatchScreen_inpBut_1->fn->setPosition(inpLvlMatchScreen_inpBut_1, 30, 65);
    inpLvlMatchScreen_inpBut_1->fn->setSize(inpLvlMatchScreen_inpBut_1, 170, 30);
    inpLvlMatchScreen_inpBut_1->fn->setEnabled(inpLvlMatchScreen_inpBut_1, LE_FALSE);
    inpLvlMatchScreen_inpBut_1->fn->setScheme(inpLvlMatchScreen_inpBut_1, &BlackScheme);
    inpLvlMatchScreen_inpBut_1->fn->setBackgroundType(inpLvlMatchScreen_inpBut_1, LE_WIDGET_BACKGROUND_NONE);
    inpLvlMatchScreen_inpBut_1->fn->setBorderType(inpLvlMatchScreen_inpBut_1, LE_WIDGET_BORDER_NONE);
    inpLvlMatchScreen_inpBut_1->fn->setHAlignment(inpLvlMatchScreen_inpBut_1, LE_HALIGN_LEFT);
    inpLvlMatchScreen_inpBut_1->fn->setVAlignment(inpLvlMatchScreen_inpBut_1, LE_VALIGN_TOP);
    inpLvlMatchScreen_inpBut_1->fn->setString(inpLvlMatchScreen_inpBut_1, (leString*)&string_Inp1Name);
    inpLvlMatchScreen_inpBut_1->fn->setPressedImage(inpLvlMatchScreen_inpBut_1, (leImage*)&smallSelected2);
    inpLvlMatchScreen_inpBut_1->fn->setReleasedImage(inpLvlMatchScreen_inpBut_1, (leImage*)&smallSelected2);
    inpLvlMatchScreen_inpBut_1->fn->setPressedOffset(inpLvlMatchScreen_inpBut_1, 0);
    inpLvlMatchScreen_inpBut_1->fn->setPressedEventCallback(inpLvlMatchScreen_inpBut_1, event_inpLvlMatchScreen_inpBut_1_OnPressed);
    root0->fn->addChild(root0, (leWidget*)inpLvlMatchScreen_inpBut_1);

    inpLvlMatchScreen_inpBut_2 = leButtonWidget_New();
    inpLvlMatchScreen_inpBut_2->fn->setPosition(inpLvlMatchScreen_inpBut_2, 30, 95);
    inpLvlMatchScreen_inpBut_2->fn->setSize(inpLvlMatchScreen_inpBut_2, 170, 30);
    inpLvlMatchScreen_inpBut_2->fn->setScheme(inpLvlMatchScreen_inpBut_2, &BlackScheme);
    inpLvlMatchScreen_inpBut_2->fn->setBorderType(inpLvlMatchScreen_inpBut_2, LE_WIDGET_BORDER_NONE);
    inpLvlMatchScreen_inpBut_2->fn->setHAlignment(inpLvlMatchScreen_inpBut_2, LE_HALIGN_LEFT);
    inpLvlMatchScreen_inpBut_2->fn->setVAlignment(inpLvlMatchScreen_inpBut_2, LE_VALIGN_TOP);
    inpLvlMatchScreen_inpBut_2->fn->setString(inpLvlMatchScreen_inpBut_2, (leString*)&string_Inp2Name);
    inpLvlMatchScreen_inpBut_2->fn->setPressedImage(inpLvlMatchScreen_inpBut_2, (leImage*)&smallSelected2);
    inpLvlMatchScreen_inpBut_2->fn->setReleasedImage(inpLvlMatchScreen_inpBut_2, (leImage*)&smallNotSelected3);
    inpLvlMatchScreen_inpBut_2->fn->setPressedOffset(inpLvlMatchScreen_inpBut_2, 0);
    inpLvlMatchScreen_inpBut_2->fn->setPressedEventCallback(inpLvlMatchScreen_inpBut_2, event_inpLvlMatchScreen_inpBut_2_OnPressed);
    root0->fn->addChild(root0, (leWidget*)inpLvlMatchScreen_inpBut_2);

    inpLvlMatchScreen_inpBut_3 = leButtonWidget_New();
    inpLvlMatchScreen_inpBut_3->fn->setPosition(inpLvlMatchScreen_inpBut_3, 30, 125);
    inpLvlMatchScreen_inpBut_3->fn->setSize(inpLvlMatchScreen_inpBut_3, 170, 30);
    inpLvlMatchScreen_inpBut_3->fn->setScheme(inpLvlMatchScreen_inpBut_3, &BlackScheme);
    inpLvlMatchScreen_inpBut_3->fn->setBorderType(inpLvlMatchScreen_inpBut_3, LE_WIDGET_BORDER_NONE);
    inpLvlMatchScreen_inpBut_3->fn->setHAlignment(inpLvlMatchScreen_inpBut_3, LE_HALIGN_LEFT);
    inpLvlMatchScreen_inpBut_3->fn->setVAlignment(inpLvlMatchScreen_inpBut_3, LE_VALIGN_TOP);
    inpLvlMatchScreen_inpBut_3->fn->setString(inpLvlMatchScreen_inpBut_3, (leString*)&string_inp3Name);
    inpLvlMatchScreen_inpBut_3->fn->setPressedImage(inpLvlMatchScreen_inpBut_3, (leImage*)&smallSelected2);
    inpLvlMatchScreen_inpBut_3->fn->setReleasedImage(inpLvlMatchScreen_inpBut_3, (leImage*)&smallNotSelected3);
    inpLvlMatchScreen_inpBut_3->fn->setPressedOffset(inpLvlMatchScreen_inpBut_3, 0);
    inpLvlMatchScreen_inpBut_3->fn->setPressedEventCallback(inpLvlMatchScreen_inpBut_3, event_inpLvlMatchScreen_inpBut_3_OnPressed);
    root0->fn->addChild(root0, (leWidget*)inpLvlMatchScreen_inpBut_3);

    inpLvlMatchScreen_inpBut_4 = leButtonWidget_New();
    inpLvlMatchScreen_inpBut_4->fn->setPosition(inpLvlMatchScreen_inpBut_4, 30, 155);
    inpLvlMatchScreen_inpBut_4->fn->setSize(inpLvlMatchScreen_inpBut_4, 170, 30);
    inpLvlMatchScreen_inpBut_4->fn->setScheme(inpLvlMatchScreen_inpBut_4, &BlackScheme);
    inpLvlMatchScreen_inpBut_4->fn->setBorderType(inpLvlMatchScreen_inpBut_4, LE_WIDGET_BORDER_NONE);
    inpLvlMatchScreen_inpBut_4->fn->setHAlignment(inpLvlMatchScreen_inpBut_4, LE_HALIGN_LEFT);
    inpLvlMatchScreen_inpBut_4->fn->setVAlignment(inpLvlMatchScreen_inpBut_4, LE_VALIGN_TOP);
    inpLvlMatchScreen_inpBut_4->fn->setString(inpLvlMatchScreen_inpBut_4, (leString*)&string_Inp4Name);
    inpLvlMatchScreen_inpBut_4->fn->setPressedImage(inpLvlMatchScreen_inpBut_4, (leImage*)&smallSelected2);
    inpLvlMatchScreen_inpBut_4->fn->setReleasedImage(inpLvlMatchScreen_inpBut_4, (leImage*)&smallNotSelected3);
    inpLvlMatchScreen_inpBut_4->fn->setPressedOffset(inpLvlMatchScreen_inpBut_4, 0);
    inpLvlMatchScreen_inpBut_4->fn->setPressedEventCallback(inpLvlMatchScreen_inpBut_4, event_inpLvlMatchScreen_inpBut_4_OnPressed);
    root0->fn->addChild(root0, (leWidget*)inpLvlMatchScreen_inpBut_4);

    inpLvlMatchScreen_inpBut_5 = leButtonWidget_New();
    inpLvlMatchScreen_inpBut_5->fn->setPosition(inpLvlMatchScreen_inpBut_5, 30, 185);
    inpLvlMatchScreen_inpBut_5->fn->setSize(inpLvlMatchScreen_inpBut_5, 170, 30);
    inpLvlMatchScreen_inpBut_5->fn->setScheme(inpLvlMatchScreen_inpBut_5, &BlackScheme);
    inpLvlMatchScreen_inpBut_5->fn->setBorderType(inpLvlMatchScreen_inpBut_5, LE_WIDGET_BORDER_NONE);
    inpLvlMatchScreen_inpBut_5->fn->setHAlignment(inpLvlMatchScreen_inpBut_5, LE_HALIGN_LEFT);
    inpLvlMatchScreen_inpBut_5->fn->setVAlignment(inpLvlMatchScreen_inpBut_5, LE_VALIGN_TOP);
    inpLvlMatchScreen_inpBut_5->fn->setString(inpLvlMatchScreen_inpBut_5, (leString*)&string_Inp5Name);
    inpLvlMatchScreen_inpBut_5->fn->setPressedImage(inpLvlMatchScreen_inpBut_5, (leImage*)&smallSelected2);
    inpLvlMatchScreen_inpBut_5->fn->setReleasedImage(inpLvlMatchScreen_inpBut_5, (leImage*)&smallNotSelected3);
    inpLvlMatchScreen_inpBut_5->fn->setPressedOffset(inpLvlMatchScreen_inpBut_5, 0);
    inpLvlMatchScreen_inpBut_5->fn->setPressedEventCallback(inpLvlMatchScreen_inpBut_5, event_inpLvlMatchScreen_inpBut_5_OnPressed);
    root0->fn->addChild(root0, (leWidget*)inpLvlMatchScreen_inpBut_5);

    inpLvlMatchScreen_inpBut_6 = leButtonWidget_New();
    inpLvlMatchScreen_inpBut_6->fn->setPosition(inpLvlMatchScreen_inpBut_6, 30, 215);
    inpLvlMatchScreen_inpBut_6->fn->setScheme(inpLvlMatchScreen_inpBut_6, &BlackScheme);
    inpLvlMatchScreen_inpBut_6->fn->setBackgroundType(inpLvlMatchScreen_inpBut_6, LE_WIDGET_BACKGROUND_NONE);
    inpLvlMatchScreen_inpBut_6->fn->setBorderType(inpLvlMatchScreen_inpBut_6, LE_WIDGET_BORDER_NONE);
    inpLvlMatchScreen_inpBut_6->fn->setHAlignment(inpLvlMatchScreen_inpBut_6, LE_HALIGN_LEFT);
    inpLvlMatchScreen_inpBut_6->fn->setVAlignment(inpLvlMatchScreen_inpBut_6, LE_VALIGN_TOP);
    inpLvlMatchScreen_inpBut_6->fn->setString(inpLvlMatchScreen_inpBut_6, (leString*)&string_Inp6Name);
    inpLvlMatchScreen_inpBut_6->fn->setPressedImage(inpLvlMatchScreen_inpBut_6, (leImage*)&smallSelected2);
    inpLvlMatchScreen_inpBut_6->fn->setReleasedImage(inpLvlMatchScreen_inpBut_6, (leImage*)&smallNotSelected3);
    inpLvlMatchScreen_inpBut_6->fn->setPressedEventCallback(inpLvlMatchScreen_inpBut_6, event_inpLvlMatchScreen_inpBut_6_OnPressed);
    root0->fn->addChild(root0, (leWidget*)inpLvlMatchScreen_inpBut_6);

    inpLvlMatchScreen_inpLvlMatchValue_1 = leLabelWidget_New();
    inpLvlMatchScreen_inpLvlMatchValue_1->fn->setPosition(inpLvlMatchScreen_inpLvlMatchValue_1, 200, 65);
    inpLvlMatchScreen_inpLvlMatchValue_1->fn->setScheme(inpLvlMatchScreen_inpLvlMatchValue_1, &BlackScheme);
    inpLvlMatchScreen_inpLvlMatchValue_1->fn->setString(inpLvlMatchScreen_inpLvlMatchValue_1, (leString*)&string_inpLvlMatch_1);
    root0->fn->addChild(root0, (leWidget*)inpLvlMatchScreen_inpLvlMatchValue_1);

    inpLvlMatchScreen_inpLvlMatchValue_2 = leLabelWidget_New();
    inpLvlMatchScreen_inpLvlMatchValue_2->fn->setPosition(inpLvlMatchScreen_inpLvlMatchValue_2, 200, 95);
    inpLvlMatchScreen_inpLvlMatchValue_2->fn->setScheme(inpLvlMatchScreen_inpLvlMatchValue_2, &BlackScheme);
    inpLvlMatchScreen_inpLvlMatchValue_2->fn->setString(inpLvlMatchScreen_inpLvlMatchValue_2, (leString*)&string_inpLvlMatch_2);
    root0->fn->addChild(root0, (leWidget*)inpLvlMatchScreen_inpLvlMatchValue_2);

    inpLvlMatchScreen_inpLvlMatchValue_3 = leLabelWidget_New();
    inpLvlMatchScreen_inpLvlMatchValue_3->fn->setPosition(inpLvlMatchScreen_inpLvlMatchValue_3, 199, 125);
    inpLvlMatchScreen_inpLvlMatchValue_3->fn->setScheme(inpLvlMatchScreen_inpLvlMatchValue_3, &BlackScheme);
    inpLvlMatchScreen_inpLvlMatchValue_3->fn->setString(inpLvlMatchScreen_inpLvlMatchValue_3, (leString*)&string_inpLvlMatch_3);
    root0->fn->addChild(root0, (leWidget*)inpLvlMatchScreen_inpLvlMatchValue_3);

    inpLvlMatchScreen_inpLvlMatchValue_4 = leLabelWidget_New();
    inpLvlMatchScreen_inpLvlMatchValue_4->fn->setPosition(inpLvlMatchScreen_inpLvlMatchValue_4, 200, 155);
    inpLvlMatchScreen_inpLvlMatchValue_4->fn->setScheme(inpLvlMatchScreen_inpLvlMatchValue_4, &BlackScheme);
    inpLvlMatchScreen_inpLvlMatchValue_4->fn->setString(inpLvlMatchScreen_inpLvlMatchValue_4, (leString*)&string_inpLvlMatch_4);
    root0->fn->addChild(root0, (leWidget*)inpLvlMatchScreen_inpLvlMatchValue_4);

    inpLvlMatchScreen_inpLvlMatchValue_5 = leLabelWidget_New();
    inpLvlMatchScreen_inpLvlMatchValue_5->fn->setPosition(inpLvlMatchScreen_inpLvlMatchValue_5, 200, 185);
    inpLvlMatchScreen_inpLvlMatchValue_5->fn->setScheme(inpLvlMatchScreen_inpLvlMatchValue_5, &BlackScheme);
    inpLvlMatchScreen_inpLvlMatchValue_5->fn->setString(inpLvlMatchScreen_inpLvlMatchValue_5, (leString*)&string_inpLvlMatch_5);
    root0->fn->addChild(root0, (leWidget*)inpLvlMatchScreen_inpLvlMatchValue_5);

    inpLvlMatchScreen_inpLvlMatchValue_6 = leLabelWidget_New();
    inpLvlMatchScreen_inpLvlMatchValue_6->fn->setPosition(inpLvlMatchScreen_inpLvlMatchValue_6, 200, 215);
    inpLvlMatchScreen_inpLvlMatchValue_6->fn->setScheme(inpLvlMatchScreen_inpLvlMatchValue_6, &BlackScheme);
    inpLvlMatchScreen_inpLvlMatchValue_6->fn->setBackgroundType(inpLvlMatchScreen_inpLvlMatchValue_6, LE_WIDGET_BACKGROUND_NONE);
    inpLvlMatchScreen_inpLvlMatchValue_6->fn->setString(inpLvlMatchScreen_inpLvlMatchValue_6, (leString*)&string_inpLvlMatch_6);
    root0->fn->addChild(root0, (leWidget*)inpLvlMatchScreen_inpLvlMatchValue_6);

    leAddRootWidget(root0, 0);
    leSetLayerColorMode(0, LE_COLOR_MODE_RGB_565);

    inpLvlMatchScreen_OnShow(); // raise event

    showing = LE_TRUE;

    return LE_SUCCESS;
}

void screenUpdate_inpLvlMatchScreen(void)
{
    root0->fn->setSize(root0, root0->rect.width, root0->rect.height);
}

void screenHide_inpLvlMatchScreen(void)
{
    inpLvlMatchScreen_OnHide(); // raise event


    leRemoveRootWidget(root0, 0);
    leWidget_Delete(root0);
    root0 = NULL;

    inpLvlMatchScreen_background = NULL;
    inpLvlMatchScreen_inpBut_1 = NULL;
    inpLvlMatchScreen_inpBut_2 = NULL;
    inpLvlMatchScreen_inpBut_3 = NULL;
    inpLvlMatchScreen_inpBut_4 = NULL;
    inpLvlMatchScreen_inpBut_5 = NULL;
    inpLvlMatchScreen_inpBut_6 = NULL;
    inpLvlMatchScreen_inpLvlMatchValue_1 = NULL;
    inpLvlMatchScreen_inpLvlMatchValue_2 = NULL;
    inpLvlMatchScreen_inpLvlMatchValue_3 = NULL;
    inpLvlMatchScreen_inpLvlMatchValue_4 = NULL;
    inpLvlMatchScreen_inpLvlMatchValue_5 = NULL;
    inpLvlMatchScreen_inpLvlMatchValue_6 = NULL;
    inpLvlMatchScreen_maxVolButImg = NULL;
    inpLvlMatchScreen_inpSenseBackToMenuImg = NULL;
    inpLvlMatchScreen_inpSenseMenuHeader = NULL;
    inpLvlMatchScreen_inPSenseLineRightSide = NULL;
    inpLvlMatchScreen_inpSenseLineLeftSide = NULL;
    inpLvlMatchScreen_inpLvlMatchPlusBut = NULL;
    inpLvlMatchScreen_inpLvlMatchMinusBut = NULL;
    inpLvlMatchScreen_inpSenseBackToMenuBut = NULL;


    showing = LE_FALSE;
}

void screenDestroy_inpLvlMatchScreen(void)
{
    if(initialized == LE_FALSE)
        return;

    initialized = LE_FALSE;
}

leWidget* screenGetRoot_inpLvlMatchScreen(uint32_t lyrIdx)
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

