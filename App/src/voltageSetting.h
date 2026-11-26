#ifndef VOLTAGE_SETTING_H
#define VOLTAGE_SETTING_H

#include <stdbool.h>
#include <stdint.h>

typedef enum {
    VoltageLow = 0, 
    VoltageHigh = 1,
    leftMissing = 2        
} voltage_setting_t;



typedef enum { EE_VS_OK = 0, EE_VS_UNINIT, EE_VS_ERR } ee_vs_status_t;

ee_vs_status_t EEPROM_TryLoadVoltageSetting(voltage_setting_t *out);

bool EEPROM_LoadVoltageSetting(voltage_setting_t *out);
bool EEPROM_SaveVoltageSetting(voltage_setting_t v);

const char* VoltageSetting_ToString(voltage_setting_t v);

bool VoltageSetting_FromString(const char* s, voltage_setting_t *out);

static inline voltage_setting_t VoltageSetting_Default(void) {
    return VoltageHigh;
}

//typedef enum {
//    VoltageLow  = 0,
//    VoltageHigh = 1,
//} voltage_setting_t;
//
//// VÆLG en fri EEPROM-adresse i dit layout.
//// 0x0021 er et forslag; flyt den, hvis den kolliderer med andet i dit projekt.
//#define EE_ADDR_VOLTAGE_SETTING   ((uint16_t)0x0021)
//
//// API
//bool EEPROM_LoadVoltageSetting(voltage_setting_t *out);
//bool EEPROM_SaveVoltageSetting(voltage_setting_t v);
//
//static inline voltage_setting_t VoltageSetting_Default(void) { return VoltageHigh; }
//const char* VoltageSetting_ToString(voltage_setting_t v);
//bool VoltageSetting_FromString(const char* s, voltage_setting_t *out);

#endif
