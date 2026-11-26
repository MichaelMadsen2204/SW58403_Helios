#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "system/fs/sys_fs.h"
#include "uart_driver.h"

#ifndef BOOTLOADER_MOUNT_NAME
#define BOOTLOADER_MOUNT_NAME   "/mnt/mydrive"   // skal matche .mountName i sysFSInit[]
#endif

#define FW_PREFIX   "FW58403_Ver_"               // ét sted at ændre navn

/* Case-insensitive tolower for ASCII only */
static inline char lower_ascii(char c)
{
    return (c >= 'A' && c <= 'Z') ? (char)(c + ('a' - 'A')) : c;
}

/* Case-insensitive startsWith for ASCII */
static bool istarts_with(const char *s, const char *prefix)
{
    while (*prefix != '\0' && *s != '\0')
    {
        if (lower_ascii(*s) != lower_ascii(*prefix))
            return false;
        s++; prefix++;
    }
    return (*prefix == '\0');
}

/* Parse "<prefix><maj>.<min>.bin" (case-insensitive). */
static bool parse_fw_longname(const char *name, int *outMaj, int *outMin)
{
    if (name == NULL)
        return false;

    size_t len = strlen(name);
    if (len < 11U)
        return false;

    /* Require ".bin" suffix */
    if (!(len >= 4U &&
          lower_ascii(name[len-4]) == '.' &&
          lower_ascii(name[len-3]) == 'b' &&
          lower_ascii(name[len-2]) == 'i' &&
          lower_ascii(name[len-1]) == 'n'))
        return false;

    /* Basename uden .bin */
    char _base[256];
    size_t blen = len - 4U;
    if (blen >= sizeof(_base))
        return false;
    memcpy(_base, name, blen);
    _base[blen] = '\0';

    /* Prefix check */
    if (!istarts_with(_base, FW_PREFIX))
        return false;

    const char *p = _base + strlen(FW_PREFIX);

    int maj = 0, min = 0;

    if (*p < '0' || *p > '9')
        return false;
    while (*p >= '0' && *p <= '9')
        maj = maj * 10 + (*p++ - '0');

    if (*p++ != '.')
        return false;

    if (*p < '0' || *p > '9')
        return false;
    while (*p >= '0' && *p <= '9')
        min = min * 10 + (*p++ - '0');

    if (*p != '\0')
        return false;

    if (outMaj) *outMaj = maj;
    if (outMin) *outMin = min;
    return true;
}

/* Finder nyeste "FW_PREFIX<maj>.<min>.bin" i root og returnerer fuld sti. */
bool SelectLatestFirmware_LFN(char *outPath, size_t outSize)
{
    if (!outPath || outSize < 8)
        return false;

    /* Byg mount + '/' */
    char dirPath[64];
    size_t m = strlen(BOOTLOADER_MOUNT_NAME);
    if (m == 0 || m + 2 > sizeof(dirPath))
        return false;
    memcpy(dirPath, BOOTLOADER_MOUNT_NAME, m);
    if (dirPath[m-1] != '/')
        dirPath[m++] = '/';
    dirPath[m] = '\0';

    SYS_FS_HANDLE dir = SYS_FS_DirOpen(dirPath);
    if (dir == SYS_FS_HANDLE_INVALID) {
        UART_Puts("DirOpen FAIL, err=");
        UART_PutDec(SYS_FS_Error());
        UART_CRLF();
        return false;
    }

    char bestName[256] = {0};
    int bestMaj = -1, bestMin = -1;

    SYS_FS_FSTAT fstat;
    memset(&fstat, 0, sizeof(fstat));

    /* Hvis din SYS_FS_FSTAT har pointer-lfname + lfsize, så fjern kommentar her */
    /*
    static char lfnBuf[256];
    fstat.lfname = lfnBuf;
    fstat.lfsize = sizeof(lfnBuf);
    */

    while (1)
    {
        SYS_FS_RESULT r = SYS_FS_DirRead(dir, &fstat);
        if (r != SYS_FS_RES_SUCCESS)
            break;

        if (fstat.fname[0] == '\0')
            break;  // end-of-dir

        const char* name = fstat.fname;
#ifdef SYS_FS_LFN_ENABLE
        if (((const char*)fstat.lfname)[0] != '\0')
            name = (const char*)fstat.lfname;
#endif

        if (!(fstat.fattrib & SYS_FS_ATTR_DIR)) {
            int maj=-1, min=-1;
            if (parse_fw_longname(name, &maj, &min)) {
                if (maj > bestMaj || (maj == bestMaj && min > bestMin)) {
                    bestMaj = maj;
                    bestMin = min;
                    strncpy(bestName, name, sizeof(bestName)-1);
                    bestName[sizeof(bestName)-1] = '\0';
                }
            }
        }

#ifdef SYS_FS_LFN_ENABLE
        if (((const char*)fstat.lfname)[0] != '\0')
            ((char*)fstat.lfname)[0] = '\0';
#endif
        fstat.fname[0] = '\0';
    }

    SYS_FS_DirClose(dir);

    if (bestMaj < 0)
        return false;

    size_t need = strlen(BOOTLOADER_MOUNT_NAME) + 1 + strlen(bestName) + 1;
    if (need > outSize)
        return false;

    strcpy(outPath, BOOTLOADER_MOUNT_NAME);
    strcat(outPath, "/");
    strcat(outPath, bestName);

    UART_Puts("Selected firmware: ");
    UART_Puts(outPath);
    UART_CRLF();

    return true;
}

