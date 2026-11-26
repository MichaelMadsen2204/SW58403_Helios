/*******************************************************************************
  User Configuration Header

  File Name:
    user.h

  Summary:
    Build-time configuration header for the user defined by this project.

  Description:
    An MPLAB Project may have multiple configurations.  This file defines the
    build-time options for a single configuration.

  Remarks:
    It only provides macro definitions for build-time configuration options

*******************************************************************************/

#ifndef USER_H
#define USER_H

#include <device.h>
#include <pic32m-libs/sys/kmem.h>

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: User Configuration macros
// *****************************************************************************
// *****************************************************************************
#define BTL_TRIGGER_RAM_START   KVA0_TO_KVA1(0x80000000)

#define DCACHE_CLEAN_BY_ADDR(start, sz)
#define BTL_TRIGGER_PATTERN (0x5048434DUL)    

static inline void APP_SystemReset( void )
{
    /* Perform system unlock sequence */ 
    SYSKEY = 0x00000000U;
    SYSKEY = 0xAA996655U;
    SYSKEY = 0x556699AAU;

    RSWRSTSET = _RSWRST_SWRST_MASK;
    (void)RSWRST;
}

static inline void APP_TriggerBootloader(void)
{
    volatile uint32_t* p = (volatile uint32_t*)BTL_TRIGGER_RAM_START;
    p[0] = BTL_TRIGGER_PATTERN;
    p[1] = BTL_TRIGGER_PATTERN;
    p[2] = BTL_TRIGGER_PATTERN;
    p[3] = BTL_TRIGGER_PATTERN;
    DCACHE_CLEAN_BY_ADDR((void*)p, 16);
    APP_SystemReset();
}


//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // USER_H
/*******************************************************************************
 End of File
*/
