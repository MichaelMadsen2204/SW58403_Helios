#include "voltageSetting.h"
#include <string.h>
#include <ctype.h>
#include <stddef.h>

/* Brug dine wrappers fra eeProm_Functions.c */
extern bool getVoltageSettingFromEEProm(uint8_t *out);  // 0/1/0xFF
extern bool saveVoltageSettingToEEProm(uint8_t v);      // 0 eller 1

#define EE_VOLTAGE_UNINIT  (0xFFu)

ee_vs_status_t EEPROM_TryLoadVoltageSetting(voltage_setting_t *out)
{
    if (!out) return EE_VS_ERR;
    uint8_t b = EE_VOLTAGE_UNINIT;
    if (!getVoltageSettingFromEEProm(&b)) return EE_VS_ERR;
    if (b == EE_VOLTAGE_UNINIT)          return EE_VS_UNINIT;
    if (b > (uint8_t)VoltageHigh)        return EE_VS_ERR;   // korrupt
    *out = (voltage_setting_t)b;
    return EE_VS_OK;
}

bool EEPROM_LoadVoltageSetting(voltage_setting_t *out)
{
    if (!out) return false;
    uint8_t b = EE_VOLTAGE_UNINIT;
    if (!getVoltageSettingFromEEProm(&b)) return false;

    if (b == EE_VOLTAGE_UNINIT) return false;                  // ikke sat endnu
    if (b > (uint8_t)VoltageHigh) return false;                 // korrupt
    *out = (voltage_setting_t)b;
    return true;
}

bool EEPROM_SaveVoltageSetting(voltage_setting_t v)
{
    uint8_t b = (uint8_t)((v != 0) ? 1u : 0u);
    return saveVoltageSettingToEEProm(b);
}

const char* VoltageSetting_ToString(voltage_setting_t v)
{
    return (v == VoltageHigh) ? "HIGH" : "LOW";
}

/* Case-insensitive parsing uden strncasecmp() */
bool VoltageSetting_FromString(const char* s, voltage_setting_t *out)
{
    if (!s || !out) return false;
    while (*s && isspace((unsigned char)*s)) s++;

    char buf[8]; size_t n = 0;
    while (s[n] && !isspace((unsigned char)s[n]) && n < sizeof(buf)-1) {
        buf[n] = (char)toupper((unsigned char)s[n]);
        n++;
    }
    buf[n] = 0;

    if (strcmp(buf, "HIGH") == 0 || strcmp(buf, "1") == 0) { *out = VoltageHigh; return true; }
    if (strcmp(buf, "LOW")  == 0 || strcmp(buf, "0") == 0) { *out = VoltageLow;  return true; }
    return false;
}
