// ui_voltage_error.c (eller i en eksisterende UI-fil)
#include "ac_check.h"
#include "definitions.h"

void UI_ShowVoltageError(voltage_setting_t expected, voltage_setting_t actual)
{
    GLCD_DISP_ON_STBY_Set();   // sørg for backlight/panel on
    GAD_LOGO_Set();

    // TODO: kald Legato screen + sæt labels:
    // screen_VoltageError_Show();
    // leLabelWidget_SetString(L_expected, expected==VoltageHigh ? &string_230V : &string_115V);
    // leLabelWidget_SetString(L_actual,   actual==VoltageHigh   ? &string_230V : &string_115V);

    DEBUG_PRINT("AC ERROR: expected=%s actual=%s\r\n",
        expected==VoltageHigh ? "HIGH" : "LOW",
        actual==VoltageHigh   ? "HIGH" : "LOW");
}
