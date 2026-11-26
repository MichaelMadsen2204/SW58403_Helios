#include "uart_driver.h"
#include <string.h>

// Kaldes efter SYS_Initialize()
void DBG_UART_Init(void)
{
    // Hvis du vil ændre baud/format dynamisk: USART1_SerialSetup(...)
    // Ellers gør MCC det allerede via UART1_Initialize() i SYS_Initialize().
}

// Blokkerende TX for én byte
static inline void UART_Putc(char c)
{
    while (U1STAbits.UTXBF != 0) { /* vent */ }
    U1TXREG = c;
}

// Slank "puts" uden printf
void UART_Puts(const char *s)
{
    if (!s) return;
    while (*s) UART_Putc(*s++);
}

void UART_CRLF(void)
{
    UART_Puts("\r\n");
}

// Skriver et heltal i decimal via UART_Puts / UART_Putc
void UART_PutDec(int value)
{
    char buf[12];    // nok til -2.147.483.648
    char *p = &buf[sizeof(buf) - 1];
    bool neg = false;

    *p = '\0';
    if (value == 0)
    {
        UART_Putc('0');
        return;
    }

    if (value < 0)
    {
        neg = true;
        value = -value;
    }

    while (value > 0 && p > buf)
    {
        *--p = (char)('0' + (value % 10));
        value /= 10;
    }

    if (neg && p > buf)
        *--p = '-';

    UART_Puts(p);
}
