#ifndef AV_INPUT_H
#define AV_INPUT_H

#include <stdint.h>
#include <stdbool.h>

#define AV_NONE 0x00u
#define AV_3    0x01u
#define AV_4    0x02u

static inline bool AvSelected(uint8_t avMask, uint8_t curInp)
{
    if (curInp == 3u) return (avMask & AV_3) != 0u;
    if (curInp == 4u) return (avMask & AV_4) != 0u;
    return false;
}

#endif
