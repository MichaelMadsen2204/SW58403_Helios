#include "gfx/legato/generated/screen/le_gen_screen_qwertyScreen.h"

// screen member widget declarations
static leWidget* root0;

leWidget* qwertyScreen_BackGround;
leLabelWidget* qwertyScreen_LabelWidget0;
leLabelWidget* qwertyScreen_LabelWidget1;
leTextFieldWidget* qwertyScreen_TextFieldWidget0;
leButtonWidget* qwertyScreen_okButtonWidget;
leButtonWidget* qwertyScreen_spaceButtonWidget;
leButtonWidget* qwertyScreen_numAlphaBut;
leWidget* qwertyScreen_keypadPanel;
leKeyPadWidget* qwertyScreen_KeyPadAlpaNum;

static leBool initialized = LE_FALSE;
static leBool showing = LE_FALSE;

leResult screenInit_qwertyScreen(void)
{
    if(initialized == LE_TRUE)
        return LE_FAILURE;

    initialized = LE_TRUE;

    return LE_SUCCESS;
}

leResult screenShow_qwertyScreen(void)
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

    qwertyScreen_BackGround = leWidget_New();
    qwertyScreen_BackGround->fn->setPosition(qwertyScreen_BackGround, 0, 0);
    qwertyScreen_BackGround->fn->setSize(qwertyScreen_BackGround, 480, 272);
    qwertyScreen_BackGround->fn->setScheme(qwertyScreen_BackGround, &BlackScheme);
    root0->fn->addChild(root0, (leWidget*)qwertyScreen_BackGround);

    qwertyScreen_TextFieldWidget0 = leTextFieldWidget_New();
    qwertyScreen_TextFieldWidget0->fn->setPosition(qwertyScreen_TextFieldWidget0, 305, 7);
    qwertyScreen_TextFieldWidget0->fn->setSize(qwertyScreen_TextFieldWidget0, 169, 30);
    qwertyScreen_TextFieldWidget0->fn->setEnabled(qwertyScreen_TextFieldWidget0, LE_FALSE);
    qwertyScreen_TextFieldWidget0->fn->setHAlignment(qwertyScreen_TextFieldWidget0, LE_HALIGN_RIGHT);
    qwertyScreen_TextFieldWidget0->fn->setFont(qwertyScreen_TextFieldWidget0, (leFont*)&Avenir18);
    qwertyScreen_TextFieldWidget0->fn->setCursorDelay(qwertyScreen_TextFieldWidget0, 250);
    qwertyScreen_TextFieldWidget0->fn->setTextChangedEventCallback(qwertyScreen_TextFieldWidget0, event_qwertyScreen_TextFieldWidget0_OnTextChanged);
    qwertyScreen_BackGround->fn->addChild(qwertyScreen_BackGround, (leWidget*)qwertyScreen_TextFieldWidget0);

    qwertyScreen_okButtonWidget = leButtonWidget_New();
    qwertyScreen_okButtonWidget->fn->setPosition(qwertyScreen_okButtonWidget, 433, 205);
    qwertyScreen_okButtonWidget->fn->setSize(qwertyScreen_okButtonWidget, 42, 49);
    qwertyScreen_okButtonWidget->fn->setScheme(qwertyScreen_okButtonWidget, &keypadScheme);
    qwertyScreen_okButtonWidget->fn->setBorderType(qwertyScreen_okButtonWidget, LE_WIDGET_BORDER_LINE);
    qwertyScreen_okButtonWidget->fn->setString(qwertyScreen_okButtonWidget, (leString*)&string_qwerty_ok);
    qwertyScreen_okButtonWidget->fn->setReleasedEventCallback(qwertyScreen_okButtonWidget, event_qwertyScreen_okButtonWidget_OnReleased);
    qwertyScreen_BackGround->fn->addChild(qwertyScreen_BackGround, (leWidget*)qwertyScreen_okButtonWidget);

    qwertyScreen_spaceButtonWidget = leButtonWidget_New();
    qwertyScreen_spaceButtonWidget->fn->setPosition(qwertyScreen_spaceButtonWidget, 92, 206);
    qwertyScreen_spaceButtonWidget->fn->setSize(qwertyScreen_spaceButtonWidget, 298, 48);
    qwertyScreen_spaceButtonWidget->fn->setScheme(qwertyScreen_spaceButtonWidget, &keypadScheme);
    qwertyScreen_spaceButtonWidget->fn->setBorderType(qwertyScreen_spaceButtonWidget, LE_WIDGET_BORDER_LINE);
    qwertyScreen_spaceButtonWidget->fn->setString(qwertyScreen_spaceButtonWidget, (leString*)&string_qwerty_space);
    qwertyScreen_spaceButtonWidget->fn->setReleasedEventCallback(qwertyScreen_spaceButtonWidget, event_qwertyScreen_spaceButtonWidget_OnReleased);
    qwertyScreen_BackGround->fn->addChild(qwertyScreen_BackGround, (leWidget*)qwertyScreen_spaceButtonWidget);

    qwertyScreen_numAlphaBut = leButtonWidget_New();
    qwertyScreen_numAlphaBut->fn->setPosition(qwertyScreen_numAlphaBut, 5, 205);
    qwertyScreen_numAlphaBut->fn->setSize(qwertyScreen_numAlphaBut, 44, 50);
    qwertyScreen_numAlphaBut->fn->setScheme(qwertyScreen_numAlphaBut, &keypadScheme);
    qwertyScreen_numAlphaBut->fn->setBorderType(qwertyScreen_numAlphaBut, LE_WIDGET_BORDER_LINE);
    qwertyScreen_numAlphaBut->fn->setToggleable(qwertyScreen_numAlphaBut, LE_TRUE);
    qwertyScreen_numAlphaBut->fn->setPressedImage(qwertyScreen_numAlphaBut, (leImage*)&Alpha);
    qwertyScreen_numAlphaBut->fn->setReleasedImage(qwertyScreen_numAlphaBut, (leImage*)&numbers);
    qwertyScreen_numAlphaBut->fn->setPressedOffset(qwertyScreen_numAlphaBut, 0);
    qwertyScreen_numAlphaBut->fn->setPressedEventCallback(qwertyScreen_numAlphaBut, event_qwertyScreen_numAlphaBut_OnPressed);
    qwertyScreen_numAlphaBut->fn->setReleasedEventCallback(qwertyScreen_numAlphaBut, event_qwertyScreen_numAlphaBut_OnReleased);
    qwertyScreen_BackGround->fn->addChild(qwertyScreen_BackGround, (leWidget*)qwertyScreen_numAlphaBut);

    qwertyScreen_keypadPanel = leWidget_New();
    qwertyScreen_keypadPanel->fn->setPosition(qwertyScreen_keypadPanel, 5, 41);
    qwertyScreen_keypadPanel->fn->setSize(qwertyScreen_keypadPanel, 470, 162);
    qwertyScreen_keypadPanel->fn->setScheme(qwertyScreen_keypadPanel, &BlackScheme);
    qwertyScreen_BackGround->fn->addChild(qwertyScreen_BackGround, (leWidget*)qwertyScreen_keypadPanel);

    qwertyScreen_KeyPadAlpaNum = leKeyPadWidget_New(6, 11);
    qwertyScreen_KeyPadAlpaNum->fn->setPosition(qwertyScreen_KeyPadAlpaNum, 0, 0);
    qwertyScreen_KeyPadAlpaNum->fn->setSize(qwertyScreen_KeyPadAlpaNum, 470, 320);
    qwertyScreen_KeyPadAlpaNum->fn->setScheme(qwertyScreen_KeyPadAlpaNum, &keypadScheme);
    qwertyScreen_KeyPadAlpaNum->fn->setBackgroundType(qwertyScreen_KeyPadAlpaNum, LE_WIDGET_BACKGROUND_NONE);
    qwertyScreen_KeyPadAlpaNum->fn->setBorderType(qwertyScreen_KeyPadAlpaNum, LE_WIDGET_BORDER_LINE);
    qwertyScreen_KeyPadAlpaNum->fn->setVAlignment(qwertyScreen_KeyPadAlpaNum, LE_VALIGN_TOP);
    leButtonWidget* cell_0_0 = qwertyScreen_KeyPadAlpaNum->fn->getCellButton(qwertyScreen_KeyPadAlpaNum, 0, 0);
    qwertyScreen_KeyPadAlpaNum->fn->setKeyValue(qwertyScreen_KeyPadAlpaNum, 0, 0, (leString*)&string_qwerty_Q);
    cell_0_0->fn->setString(cell_0_0, (leString*)&string_qwerty_Q);
    leButtonWidget* cell_0_1 = qwertyScreen_KeyPadAlpaNum->fn->getCellButton(qwertyScreen_KeyPadAlpaNum, 0, 1);
    qwertyScreen_KeyPadAlpaNum->fn->setKeyValue(qwertyScreen_KeyPadAlpaNum, 0, 1, (leString*)&string_qwerty_W);
    cell_0_1->fn->setString(cell_0_1, (leString*)&string_qwerty_W);
    leButtonWidget* cell_0_2 = qwertyScreen_KeyPadAlpaNum->fn->getCellButton(qwertyScreen_KeyPadAlpaNum, 0, 2);
    cell_0_2->fn->setString(cell_0_2, (leString*)&string_qwerty_E);
    leButtonWidget* cell_0_3 = qwertyScreen_KeyPadAlpaNum->fn->getCellButton(qwertyScreen_KeyPadAlpaNum, 0, 3);
    cell_0_3->fn->setString(cell_0_3, (leString*)&string_qwerty_R);
    leButtonWidget* cell_0_4 = qwertyScreen_KeyPadAlpaNum->fn->getCellButton(qwertyScreen_KeyPadAlpaNum, 0, 4);
    cell_0_4->fn->setString(cell_0_4, (leString*)&string_qwerty_T);
    leButtonWidget* cell_0_5 = qwertyScreen_KeyPadAlpaNum->fn->getCellButton(qwertyScreen_KeyPadAlpaNum, 0, 5);
    cell_0_5->fn->setString(cell_0_5, (leString*)&string_qwerty_Y);
    leButtonWidget* cell_0_6 = qwertyScreen_KeyPadAlpaNum->fn->getCellButton(qwertyScreen_KeyPadAlpaNum, 0, 6);
    cell_0_6->fn->setString(cell_0_6, (leString*)&string_qwerty_U);
    leButtonWidget* cell_0_7 = qwertyScreen_KeyPadAlpaNum->fn->getCellButton(qwertyScreen_KeyPadAlpaNum, 0, 7);
    cell_0_7->fn->setString(cell_0_7, (leString*)&string_qwerty_I);
    leButtonWidget* cell_0_8 = qwertyScreen_KeyPadAlpaNum->fn->getCellButton(qwertyScreen_KeyPadAlpaNum, 0, 8);
    cell_0_8->fn->setString(cell_0_8, (leString*)&string_qwerty_O);
    leButtonWidget* cell_0_9 = qwertyScreen_KeyPadAlpaNum->fn->getCellButton(qwertyScreen_KeyPadAlpaNum, 0, 9);
    cell_0_9->fn->setString(cell_0_9, (leString*)&string_qwerty_P);
    leButtonWidget* cell_0_10 = qwertyScreen_KeyPadAlpaNum->fn->getCellButton(qwertyScreen_KeyPadAlpaNum, 0, 10);
    cell_0_10->fn->setString(cell_0_10, (leString*)&string_qwerty_AA);
    leButtonWidget* cell_1_0 = qwertyScreen_KeyPadAlpaNum->fn->getCellButton(qwertyScreen_KeyPadAlpaNum, 1, 0);
    cell_1_0->fn->setString(cell_1_0, (leString*)&string_qwerty_A);
    leButtonWidget* cell_1_1 = qwertyScreen_KeyPadAlpaNum->fn->getCellButton(qwertyScreen_KeyPadAlpaNum, 1, 1);
    cell_1_1->fn->setString(cell_1_1, (leString*)&string_qwerty_S);
    leButtonWidget* cell_1_2 = qwertyScreen_KeyPadAlpaNum->fn->getCellButton(qwertyScreen_KeyPadAlpaNum, 1, 2);
    cell_1_2->fn->setString(cell_1_2, (leString*)&string_qwerty_D);
    leButtonWidget* cell_1_3 = qwertyScreen_KeyPadAlpaNum->fn->getCellButton(qwertyScreen_KeyPadAlpaNum, 1, 3);
    cell_1_3->fn->setString(cell_1_3, (leString*)&string_qwerty_F);
    leButtonWidget* cell_1_4 = qwertyScreen_KeyPadAlpaNum->fn->getCellButton(qwertyScreen_KeyPadAlpaNum, 1, 4);
    cell_1_4->fn->setString(cell_1_4, (leString*)&string_qwerty_G);
    leButtonWidget* cell_1_5 = qwertyScreen_KeyPadAlpaNum->fn->getCellButton(qwertyScreen_KeyPadAlpaNum, 1, 5);
    cell_1_5->fn->setString(cell_1_5, (leString*)&string_qwerty_H);
    leButtonWidget* cell_1_6 = qwertyScreen_KeyPadAlpaNum->fn->getCellButton(qwertyScreen_KeyPadAlpaNum, 1, 6);
    cell_1_6->fn->setString(cell_1_6, (leString*)&string_qwerty_J);
    leButtonWidget* cell_1_7 = qwertyScreen_KeyPadAlpaNum->fn->getCellButton(qwertyScreen_KeyPadAlpaNum, 1, 7);
    cell_1_7->fn->setString(cell_1_7, (leString*)&string_qwerty_K);
    leButtonWidget* cell_1_8 = qwertyScreen_KeyPadAlpaNum->fn->getCellButton(qwertyScreen_KeyPadAlpaNum, 1, 8);
    cell_1_8->fn->setString(cell_1_8, (leString*)&string_qwerty_L);
    leButtonWidget* cell_1_9 = qwertyScreen_KeyPadAlpaNum->fn->getCellButton(qwertyScreen_KeyPadAlpaNum, 1, 9);
    cell_1_9->fn->setString(cell_1_9, (leString*)&string_qwerty_AE);
    leButtonWidget* cell_1_10 = qwertyScreen_KeyPadAlpaNum->fn->getCellButton(qwertyScreen_KeyPadAlpaNum, 1, 10);
    cell_1_10->fn->setString(cell_1_10, (leString*)&string_qwerty_OE);
    leButtonWidget* cell_2_0 = qwertyScreen_KeyPadAlpaNum->fn->getCellButton(qwertyScreen_KeyPadAlpaNum, 2, 0);
    qwertyScreen_KeyPadAlpaNum->fn->setKeyVisible(qwertyScreen_KeyPadAlpaNum, 2, 0, LE_FALSE);
    cell_2_0->fn->setString(cell_2_0, (leString*)&string_emtyString);
    leButtonWidget* cell_2_1 = qwertyScreen_KeyPadAlpaNum->fn->getCellButton(qwertyScreen_KeyPadAlpaNum, 2, 1);
    cell_2_1->fn->setString(cell_2_1, (leString*)&string_qwerty_Z);
    leButtonWidget* cell_2_2 = qwertyScreen_KeyPadAlpaNum->fn->getCellButton(qwertyScreen_KeyPadAlpaNum, 2, 2);
    cell_2_2->fn->setString(cell_2_2, (leString*)&string_qwerty_X);
    leButtonWidget* cell_2_3 = qwertyScreen_KeyPadAlpaNum->fn->getCellButton(qwertyScreen_KeyPadAlpaNum, 2, 3);
    cell_2_3->fn->setString(cell_2_3, (leString*)&string_qwerty_C);
    leButtonWidget* cell_2_4 = qwertyScreen_KeyPadAlpaNum->fn->getCellButton(qwertyScreen_KeyPadAlpaNum, 2, 4);
    cell_2_4->fn->setString(cell_2_4, (leString*)&string_qwerty_V);
    leButtonWidget* cell_2_5 = qwertyScreen_KeyPadAlpaNum->fn->getCellButton(qwertyScreen_KeyPadAlpaNum, 2, 5);
    cell_2_5->fn->setString(cell_2_5, (leString*)&string_qwerty_B);
    leButtonWidget* cell_2_6 = qwertyScreen_KeyPadAlpaNum->fn->getCellButton(qwertyScreen_KeyPadAlpaNum, 2, 6);
    cell_2_6->fn->setString(cell_2_6, (leString*)&string_qwerty_N);
    leButtonWidget* cell_2_7 = qwertyScreen_KeyPadAlpaNum->fn->getCellButton(qwertyScreen_KeyPadAlpaNum, 2, 7);
    cell_2_7->fn->setString(cell_2_7, (leString*)&string_qwerty_M);
    leButtonWidget* cell_2_8 = qwertyScreen_KeyPadAlpaNum->fn->getCellButton(qwertyScreen_KeyPadAlpaNum, 2, 8);
    qwertyScreen_KeyPadAlpaNum->fn->setKeyValue(qwertyScreen_KeyPadAlpaNum, 2, 8, (leString*)&string_qwerty_punktum);
    cell_2_8->fn->setString(cell_2_8, (leString*)&string_qwerty_punktum);
    leButtonWidget* cell_2_9 = qwertyScreen_KeyPadAlpaNum->fn->getCellButton(qwertyScreen_KeyPadAlpaNum, 2, 9);
    qwertyScreen_KeyPadAlpaNum->fn->setKeyVisible(qwertyScreen_KeyPadAlpaNum, 2, 9, LE_FALSE);
    cell_2_9->fn->setString(cell_2_9, (leString*)&string_emtyString);
    leButtonWidget* cell_2_10 = qwertyScreen_KeyPadAlpaNum->fn->getCellButton(qwertyScreen_KeyPadAlpaNum, 2, 10);
    qwertyScreen_KeyPadAlpaNum->fn->setKeyValue(qwertyScreen_KeyPadAlpaNum, 2, 10, (leString*)&string_qwerty_bksp);
    cell_2_10->fn->setPressedImage(cell_2_10, &Backspace);
    cell_2_10->fn->setReleasedImage(cell_2_10, &Backspace);
    cell_2_10->fn->setImageMargin(cell_2_10, 0);
    leButtonWidget* cell_3_0 = qwertyScreen_KeyPadAlpaNum->fn->getCellButton(qwertyScreen_KeyPadAlpaNum, 3, 0);
    qwertyScreen_KeyPadAlpaNum->fn->setKeyValue(qwertyScreen_KeyPadAlpaNum, 3, 0, (leString*)&string_qwerty_1);
    cell_3_0->fn->setString(cell_3_0, (leString*)&string_qwerty_1);
    leButtonWidget* cell_3_1 = qwertyScreen_KeyPadAlpaNum->fn->getCellButton(qwertyScreen_KeyPadAlpaNum, 3, 1);
    qwertyScreen_KeyPadAlpaNum->fn->setKeyValue(qwertyScreen_KeyPadAlpaNum, 3, 1, (leString*)&string_qwerty_2);
    cell_3_1->fn->setString(cell_3_1, (leString*)&string_qwerty_2);
    leButtonWidget* cell_3_2 = qwertyScreen_KeyPadAlpaNum->fn->getCellButton(qwertyScreen_KeyPadAlpaNum, 3, 2);
    qwertyScreen_KeyPadAlpaNum->fn->setKeyValue(qwertyScreen_KeyPadAlpaNum, 3, 2, (leString*)&string_qwerty_3);
    cell_3_2->fn->setString(cell_3_2, (leString*)&string_qwerty_3);
    leButtonWidget* cell_3_3 = qwertyScreen_KeyPadAlpaNum->fn->getCellButton(qwertyScreen_KeyPadAlpaNum, 3, 3);
    qwertyScreen_KeyPadAlpaNum->fn->setKeyValue(qwertyScreen_KeyPadAlpaNum, 3, 3, (leString*)&string_qwerty_4);
    cell_3_3->fn->setString(cell_3_3, (leString*)&string_qwerty_4);
    leButtonWidget* cell_3_4 = qwertyScreen_KeyPadAlpaNum->fn->getCellButton(qwertyScreen_KeyPadAlpaNum, 3, 4);
    qwertyScreen_KeyPadAlpaNum->fn->setKeyValue(qwertyScreen_KeyPadAlpaNum, 3, 4, (leString*)&string_qwerty_5);
    cell_3_4->fn->setString(cell_3_4, (leString*)&string_qwerty_5);
    leButtonWidget* cell_3_5 = qwertyScreen_KeyPadAlpaNum->fn->getCellButton(qwertyScreen_KeyPadAlpaNum, 3, 5);
    qwertyScreen_KeyPadAlpaNum->fn->setKeyValue(qwertyScreen_KeyPadAlpaNum, 3, 5, (leString*)&string_qwerty_6);
    cell_3_5->fn->setString(cell_3_5, (leString*)&string_qwerty_6);
    leButtonWidget* cell_3_6 = qwertyScreen_KeyPadAlpaNum->fn->getCellButton(qwertyScreen_KeyPadAlpaNum, 3, 6);
    qwertyScreen_KeyPadAlpaNum->fn->setKeyValue(qwertyScreen_KeyPadAlpaNum, 3, 6, (leString*)&string_qwerty_7);
    cell_3_6->fn->setString(cell_3_6, (leString*)&string_qwerty_7);
    leButtonWidget* cell_3_7 = qwertyScreen_KeyPadAlpaNum->fn->getCellButton(qwertyScreen_KeyPadAlpaNum, 3, 7);
    qwertyScreen_KeyPadAlpaNum->fn->setKeyValue(qwertyScreen_KeyPadAlpaNum, 3, 7, (leString*)&string_qwerty_8);
    cell_3_7->fn->setString(cell_3_7, (leString*)&string_qwerty_8);
    leButtonWidget* cell_3_8 = qwertyScreen_KeyPadAlpaNum->fn->getCellButton(qwertyScreen_KeyPadAlpaNum, 3, 8);
    qwertyScreen_KeyPadAlpaNum->fn->setKeyValue(qwertyScreen_KeyPadAlpaNum, 3, 8, (leString*)&string_qwerty_9);
    cell_3_8->fn->setString(cell_3_8, (leString*)&string_qwerty_9);
    leButtonWidget* cell_3_9 = qwertyScreen_KeyPadAlpaNum->fn->getCellButton(qwertyScreen_KeyPadAlpaNum, 3, 9);
    qwertyScreen_KeyPadAlpaNum->fn->setKeyValue(qwertyScreen_KeyPadAlpaNum, 3, 9, (leString*)&string_qwerty_0);
    cell_3_9->fn->setString(cell_3_9, (leString*)&string_qwerty_0);
    leButtonWidget* cell_3_10 = qwertyScreen_KeyPadAlpaNum->fn->getCellButton(qwertyScreen_KeyPadAlpaNum, 3, 10);
    qwertyScreen_KeyPadAlpaNum->fn->setKeyValue(qwertyScreen_KeyPadAlpaNum, 3, 10, (leString*)&string_qwerty_plus);
    cell_3_10->fn->setString(cell_3_10, (leString*)&string_qwerty_plus);
    leButtonWidget* cell_4_0 = qwertyScreen_KeyPadAlpaNum->fn->getCellButton(qwertyScreen_KeyPadAlpaNum, 4, 0);
    qwertyScreen_KeyPadAlpaNum->fn->setKeyValue(qwertyScreen_KeyPadAlpaNum, 4, 0, (leString*)&string_qwerty_exclamation);
    cell_4_0->fn->setString(cell_4_0, (leString*)&string_qwerty_exclamation);
    leButtonWidget* cell_4_1 = qwertyScreen_KeyPadAlpaNum->fn->getCellButton(qwertyScreen_KeyPadAlpaNum, 4, 1);
    qwertyScreen_KeyPadAlpaNum->fn->setKeyValue(qwertyScreen_KeyPadAlpaNum, 4, 1, (leString*)&string_qwerty_appostrof);
    cell_4_1->fn->setString(cell_4_1, (leString*)&string_qwerty_appostrof);
    leButtonWidget* cell_4_2 = qwertyScreen_KeyPadAlpaNum->fn->getCellButton(qwertyScreen_KeyPadAlpaNum, 4, 2);
    qwertyScreen_KeyPadAlpaNum->fn->setKeyValue(qwertyScreen_KeyPadAlpaNum, 4, 2, (leString*)&string_qwerty_havelaage);
    cell_4_2->fn->setString(cell_4_2, (leString*)&string_qwerty_havelaage);
    leButtonWidget* cell_4_3 = qwertyScreen_KeyPadAlpaNum->fn->getCellButton(qwertyScreen_KeyPadAlpaNum, 4, 3);
    qwertyScreen_KeyPadAlpaNum->fn->setKeyValue(qwertyScreen_KeyPadAlpaNum, 4, 3, (leString*)&string_qwerty_percent);
    cell_4_3->fn->setString(cell_4_3, (leString*)&string_qwerty_percent);
    leButtonWidget* cell_4_4 = qwertyScreen_KeyPadAlpaNum->fn->getCellButton(qwertyScreen_KeyPadAlpaNum, 4, 4);
    qwertyScreen_KeyPadAlpaNum->fn->setKeyValue(qwertyScreen_KeyPadAlpaNum, 4, 4, (leString*)&string_qwerty_and);
    cell_4_4->fn->setString(cell_4_4, (leString*)&string_qwerty_and);
    leButtonWidget* cell_4_5 = qwertyScreen_KeyPadAlpaNum->fn->getCellButton(qwertyScreen_KeyPadAlpaNum, 4, 5);
    qwertyScreen_KeyPadAlpaNum->fn->setKeyValue(qwertyScreen_KeyPadAlpaNum, 4, 5, (leString*)&string_qwerty_slash);
    cell_4_5->fn->setString(cell_4_5, (leString*)&string_qwerty_slash);
    leButtonWidget* cell_4_6 = qwertyScreen_KeyPadAlpaNum->fn->getCellButton(qwertyScreen_KeyPadAlpaNum, 4, 6);
    qwertyScreen_KeyPadAlpaNum->fn->setKeyValue(qwertyScreen_KeyPadAlpaNum, 4, 6, (leString*)&string_qwerty_left_parantes);
    cell_4_6->fn->setString(cell_4_6, (leString*)&string_qwerty_left_parantes);
    leButtonWidget* cell_4_7 = qwertyScreen_KeyPadAlpaNum->fn->getCellButton(qwertyScreen_KeyPadAlpaNum, 4, 7);
    qwertyScreen_KeyPadAlpaNum->fn->setKeyValue(qwertyScreen_KeyPadAlpaNum, 4, 7, (leString*)&string_qwerty_right_parantes);
    cell_4_7->fn->setString(cell_4_7, (leString*)&string_qwerty_right_parantes);
    leButtonWidget* cell_4_8 = qwertyScreen_KeyPadAlpaNum->fn->getCellButton(qwertyScreen_KeyPadAlpaNum, 4, 8);
    qwertyScreen_KeyPadAlpaNum->fn->setKeyValue(qwertyScreen_KeyPadAlpaNum, 4, 8, (leString*)&string_qwerty_equal);
    cell_4_8->fn->setString(cell_4_8, (leString*)&string_qwerty_equal);
    leButtonWidget* cell_4_9 = qwertyScreen_KeyPadAlpaNum->fn->getCellButton(qwertyScreen_KeyPadAlpaNum, 4, 9);
    qwertyScreen_KeyPadAlpaNum->fn->setKeyValue(qwertyScreen_KeyPadAlpaNum, 4, 9, (leString*)&string_qwerty_question);
    cell_4_9->fn->setString(cell_4_9, (leString*)&string_qwerty_question);
    leButtonWidget* cell_4_10 = qwertyScreen_KeyPadAlpaNum->fn->getCellButton(qwertyScreen_KeyPadAlpaNum, 4, 10);
    qwertyScreen_KeyPadAlpaNum->fn->setKeyValue(qwertyScreen_KeyPadAlpaNum, 4, 10, (leString*)&string_qwerty_ca);
    cell_4_10->fn->setString(cell_4_10, (leString*)&string_qwerty_ca);
    leButtonWidget* cell_5_0 = qwertyScreen_KeyPadAlpaNum->fn->getCellButton(qwertyScreen_KeyPadAlpaNum, 5, 0);
    qwertyScreen_KeyPadAlpaNum->fn->setKeyValue(qwertyScreen_KeyPadAlpaNum, 5, 0, (leString*)&string_qwerty_smaller);
    cell_5_0->fn->setString(cell_5_0, (leString*)&string_qwerty_smaller);
    leButtonWidget* cell_5_1 = qwertyScreen_KeyPadAlpaNum->fn->getCellButton(qwertyScreen_KeyPadAlpaNum, 5, 1);
    qwertyScreen_KeyPadAlpaNum->fn->setKeyValue(qwertyScreen_KeyPadAlpaNum, 5, 1, (leString*)&string_qwerty_larger);
    cell_5_1->fn->setString(cell_5_1, (leString*)&string_qwerty_larger);
    leButtonWidget* cell_5_2 = qwertyScreen_KeyPadAlpaNum->fn->getCellButton(qwertyScreen_KeyPadAlpaNum, 5, 2);
    qwertyScreen_KeyPadAlpaNum->fn->setKeyValue(qwertyScreen_KeyPadAlpaNum, 5, 2, (leString*)&string_qwerty_dollar);
    cell_5_2->fn->setString(cell_5_2, (leString*)&string_qwerty_dollar);
    leButtonWidget* cell_5_3 = qwertyScreen_KeyPadAlpaNum->fn->getCellButton(qwertyScreen_KeyPadAlpaNum, 5, 3);
    qwertyScreen_KeyPadAlpaNum->fn->setKeyValue(qwertyScreen_KeyPadAlpaNum, 5, 3, (leString*)&string_qwerty_semicolon);
    cell_5_3->fn->setString(cell_5_3, (leString*)&string_qwerty_semicolon);
    leButtonWidget* cell_5_4 = qwertyScreen_KeyPadAlpaNum->fn->getCellButton(qwertyScreen_KeyPadAlpaNum, 5, 4);
    qwertyScreen_KeyPadAlpaNum->fn->setKeyValue(qwertyScreen_KeyPadAlpaNum, 5, 4, (leString*)&string_qwerty_colon);
    cell_5_4->fn->setString(cell_5_4, (leString*)&string_qwerty_colon);
    leButtonWidget* cell_5_5 = qwertyScreen_KeyPadAlpaNum->fn->getCellButton(qwertyScreen_KeyPadAlpaNum, 5, 5);
    qwertyScreen_KeyPadAlpaNum->fn->setKeyValue(qwertyScreen_KeyPadAlpaNum, 5, 5, (leString*)&string_qwerty_comma);
    cell_5_5->fn->setString(cell_5_5, (leString*)&string_qwerty_comma);
    leButtonWidget* cell_5_6 = qwertyScreen_KeyPadAlpaNum->fn->getCellButton(qwertyScreen_KeyPadAlpaNum, 5, 6);
    qwertyScreen_KeyPadAlpaNum->fn->setKeyValue(qwertyScreen_KeyPadAlpaNum, 5, 6, (leString*)&string_qwerty_fullstop);
    cell_5_6->fn->setString(cell_5_6, (leString*)&string_qwerty_fullstop);
    leButtonWidget* cell_5_7 = qwertyScreen_KeyPadAlpaNum->fn->getCellButton(qwertyScreen_KeyPadAlpaNum, 5, 7);
    qwertyScreen_KeyPadAlpaNum->fn->setKeyValue(qwertyScreen_KeyPadAlpaNum, 5, 7, (leString*)&string_qwerty_dash);
    cell_5_7->fn->setString(cell_5_7, (leString*)&string_qwerty_dash);
    leButtonWidget* cell_5_8 = qwertyScreen_KeyPadAlpaNum->fn->getCellButton(qwertyScreen_KeyPadAlpaNum, 5, 8);
    qwertyScreen_KeyPadAlpaNum->fn->setKeyValue(qwertyScreen_KeyPadAlpaNum, 5, 8, (leString*)&string_qwerty_underscore);
    cell_5_8->fn->setString(cell_5_8, (leString*)&string_qwerty_underscore);
    leButtonWidget* cell_5_9 = qwertyScreen_KeyPadAlpaNum->fn->getCellButton(qwertyScreen_KeyPadAlpaNum, 5, 9);
    qwertyScreen_KeyPadAlpaNum->fn->setKeyValue(qwertyScreen_KeyPadAlpaNum, 5, 9, (leString*)&string_qwerty_pow);
    cell_5_9->fn->setString(cell_5_9, (leString*)&string_qwerty_pow);
    leButtonWidget* cell_5_10 = qwertyScreen_KeyPadAlpaNum->fn->getCellButton(qwertyScreen_KeyPadAlpaNum, 5, 10);
    qwertyScreen_KeyPadAlpaNum->fn->setKeyAction(qwertyScreen_KeyPadAlpaNum, 5, 10, LE_KEYPAD_CELL_ACTION_BACKSPACE);
    cell_5_10->fn->setPressedImage(cell_5_10, &Backspace);
    cell_5_10->fn->setReleasedImage(cell_5_10, &Backspace);
    qwertyScreen_KeyPadAlpaNum->fn->setKeyClickEventCallback(qwertyScreen_KeyPadAlpaNum, event_qwertyScreen_KeyPadAlpaNum_OnKeyClick);
    qwertyScreen_keypadPanel->fn->addChild(qwertyScreen_keypadPanel, (leWidget*)qwertyScreen_KeyPadAlpaNum);

    qwertyScreen_LabelWidget0 = leLabelWidget_New();
    qwertyScreen_LabelWidget0->fn->setPosition(qwertyScreen_LabelWidget0, 5, 8);
    qwertyScreen_LabelWidget0->fn->setSize(qwertyScreen_LabelWidget0, 95, 29);
    qwertyScreen_LabelWidget0->fn->setScheme(qwertyScreen_LabelWidget0, &BlackScheme);
    qwertyScreen_LabelWidget0->fn->setString(qwertyScreen_LabelWidget0, (leString*)&string_Qwerty_RenameInputStr);
    root0->fn->addChild(root0, (leWidget*)qwertyScreen_LabelWidget0);

    qwertyScreen_LabelWidget1 = leLabelWidget_New();
    qwertyScreen_LabelWidget1->fn->setPosition(qwertyScreen_LabelWidget1, 95, 8);
    qwertyScreen_LabelWidget1->fn->setSize(qwertyScreen_LabelWidget1, 184, 29);
    qwertyScreen_LabelWidget1->fn->setScheme(qwertyScreen_LabelWidget1, &BlackScheme);
    qwertyScreen_LabelWidget1->fn->setString(qwertyScreen_LabelWidget1, (leString*)&string_curEditInputNameString);
    root0->fn->addChild(root0, (leWidget*)qwertyScreen_LabelWidget1);

    leAddRootWidget(root0, 0);
    leSetLayerColorMode(0, LE_COLOR_MODE_RGB_565);

    qwertyScreen_OnShow(); // raise event

    showing = LE_TRUE;

    return LE_SUCCESS;
}

void screenUpdate_qwertyScreen(void)
{
    root0->fn->setSize(root0, root0->rect.width, root0->rect.height);
}

void screenHide_qwertyScreen(void)
{
    qwertyScreen_OnHide(); // raise event


    leRemoveRootWidget(root0, 0);
    leWidget_Delete(root0);
    root0 = NULL;

    qwertyScreen_BackGround = NULL;
    qwertyScreen_LabelWidget0 = NULL;
    qwertyScreen_LabelWidget1 = NULL;
    qwertyScreen_TextFieldWidget0 = NULL;
    qwertyScreen_okButtonWidget = NULL;
    qwertyScreen_spaceButtonWidget = NULL;
    qwertyScreen_numAlphaBut = NULL;
    qwertyScreen_keypadPanel = NULL;
    qwertyScreen_KeyPadAlpaNum = NULL;


    showing = LE_FALSE;
}

void screenDestroy_qwertyScreen(void)
{
    if(initialized == LE_FALSE)
        return;

    initialized = LE_FALSE;
}

leWidget* screenGetRoot_qwertyScreen(uint32_t lyrIdx)
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

