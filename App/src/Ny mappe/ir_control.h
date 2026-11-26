#ifndef IR_CONTROL_H
#define IR_CONTROL_H

#include <stdint.h>
#include <stdbool.h>

uint16_t irDecodeRawCode(void);
uint8_t irExtractCommand(uint16_t rawCode);
uint8_t irExtractSystem(uint16_t rawCode);
void handleIrCommand(uint8_t system, uint8_t command, bool toggle);
void irReceive(void);

#endif // IR_CONTROL_H
