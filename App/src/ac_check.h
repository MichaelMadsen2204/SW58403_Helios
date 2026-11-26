// ac_check.h
#ifndef AC_CHECK_H
#define AC_CHECK_H

#include <stdbool.h>
#include "voltageSetting.h"
#include "config/default/definitions.h"

//

//#define BTL_TRIGGER_PATTERN (0x5048434DUL)
//static uint32_t *ramStart = (uint32_t *)BTL_TRIGGER_RAM_START;

typedef enum {
    ACCHK_IDLE = 0,
    ACCHK_WAIT_50MS,       // én stabiliseringsperiode
    ACCHK_EVAL,            // sammenlign + sæt relæ / fejl
    ACCHK_MISMATCH,        // fejl: blink + re-check periodisk
    ACCHK_DONE_OK
} acchk_state_t;

void ACCHK_Init(void);
void ACCHK_Begin(voltage_setting_t expected);
void ACCHK_Tasks(void);
void ACCHK_Abort(void);

bool ACCHK_IsBusy(void);
bool ACCHK_Done(void);
bool ACCHK_Passed(void);
bool ACCHK_50mS_Passed(void);

/* (valgfrit) få fat i værdier for UI/log */
voltage_setting_t ACCHK_GetExpected(void);
voltage_setting_t ACCHK_GetActual(void);

/* Disse hooks implementerer du i dit projekt: */
void UI_ShowVoltageError(voltage_setting_t expected, voltage_setting_t actual);

/* Mapping af din HW-sense:
   AC_RESULT_Get() == 1  => VoltageLow
   AC_RESULT_Get() == 0  => VoltageHigh
*/
static inline voltage_setting_t AC_ReadActualFromPins(void)
{
    if(!AC_RESET_Get())
        return leftMissing;
    
    return AC_RESULT_Get() ? VoltageLow : VoltageHigh;
}

#endif
