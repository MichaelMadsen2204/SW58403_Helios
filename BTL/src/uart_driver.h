#ifndef UART_DRIVER_PLIB_H
#define UART_DRIVER_PLIB_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "definitions.h"   // giver USART1_Write, U1STAbits, etc.

#ifdef __cplusplus
extern "C" {
#endif

void DBG_UART_Init(void);
void UART_Puts(const char *s);
void UART_CRLF(void);
void UART_PutDec(int value);


#ifdef __cplusplus
}
#endif
#endif
