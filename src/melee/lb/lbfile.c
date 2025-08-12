#include "lb/lbfile.h"

#include "lb/lb_0192.h"
#include "lb/lbdvd.h"
#include "lb/lbheap.h"
#include "lb/lblanguage.h"

#include <string.h>
#include <dolphin/dvd.h>
#include <dolphin/os/OSError.h>
#include <dolphin/os/OSInterrupt.h>
#include <baselib/debug.h>
#include <baselib/devcom.h>

static char lbFile_803BA508[] = __FILE__;

static bool cancel;

void lbFile_8001615C(void* r3, int r4, void* r5, bool cancelflag)
{
    if (cancelflag) {
        __assert(lbFile_803BA508, 71, "!cancelflag");
    }
    cancel = true;
}

#pragma push
#pragma dont_inline on
bool lbFile_800161A0(void)
{
    lb_800195D0();
    return cancel;
}
#pragma pop

void lbFile_800161C4(int file, u32 src, u32 dest, u32 size, int type, int pri)
{
    cancel = false;
    HSD_DevComRequest(file, src, dest, size, type, pri, lbFile_8001615C, 0);

    do {
        continue;
    } while (!lbFile_800161A0());
}

#define MAX_FILENAME_LENGTH 0x20
const int FILE_EXTENSION_LENGTH = 4; // ".usd" or ".dat"
const int MAX_BASENAME_LENGTH = MAX_FILENAME_LENGTH - FILE_EXTENSION_LENGTH;
static char lbFile_80432058[MAX_FILENAME_LENGTH];

// append file extension (if needed)
char* lbFile_80016204(const char* basename)
{
    const char* cur = basename;
    s32 pos = 0;

    while (cur[0] != '\0' && cur[0] != '.') {
        // no room for file extension?
        if (pos > MAX_BASENAME_LENGTH) {
            OSReport("Error : file name too long %s.", basename);
            __assert(lbFile_803BA508, 0x99, "NULL");
        }
        lbFile_80432058[pos++] = cur++[0];
    }
    // keep any existing file extension
    if (cur[0] != '\0' && cur[1] != '\0') {
        strcpy(lbFile_80432058, basename);
        // otherwise, append the appropriate extension for the locale
    } else if (cur[0] == '.') {
        lbFile_80432058[pos++] = '.';
        if (lbLang_IsSettingUS()) {
            strcpy(&lbFile_80432058[pos], "usd");
        } else {
            strcpy(&lbFile_80432058[pos], "dat");
        }
    } else {
        lbFile_80432058[pos++] = '.';
        if (lbLang_IsSavedLanguageUS()) {
            strcpy(&lbFile_80432058[pos], "usd");
        } else {
            strcpy(&lbFile_80432058[pos], "dat");
        }
    }
    return lbFile_80432058;
}

#ifndef BUGFIX
typedef struct OldDVDFileInfo {
    /*0x00*/ DVDCommandBlock cb;
    /*0x30*/ u32 startAddr;
    /*0x34*/ u32 length;
} OldDVDFileInfo;
#endif

/// @bug OldDVDFileInfo is needed to match stack allocation sizes. However,
/// the actual DVDFileInfo is 4 bytes longer due to callback.
/// This means that calls to lbFile_8001634C write 4 bytes past where it should
/// on the stack.
///
/// Get file size:
size_t lbFile_8001634C(s32 fileno)
{
#ifdef BUGFIX
    DVDFileInfo info;
#else
    OldDVDFileInfo info;
#endif
    size_t length;
    bool intr = OSDisableInterrupts();

    if (!DVDFastOpen(fileno, (DVDFileInfo*) &info)) {
        OSReport("Cannot open file no=%d.", fileno);
        __assert(lbFile_803BA508, 0xD8, "0");
    }

    length = info.length;
    DVDClose((DVDFileInfo*) &info);
    OSRestoreInterrupts(intr);
    return length;
}

s32 lbFile_800163D8(const char* basename)
{
    s32 entry_num;
    char* filename = lbFile_80016204(basename);
    entry_num = DVDConvertPathToEntrynum(filename);
    if (entry_num == -1) {
        OSReport("file isn't exist %s = %d\n", filename, entry_num);
        __assert(lbFile_803BA508, 0xEE, "entry_num != -1");
    }
    return lbFile_8001634C(entry_num);
}

#define ROUND_UP_32(x) (((x) + 31) & ~31)

void lbFile_800164A4(s32 file, u32 dest, size_t* size, s32 pri,
                     HSD_DevComCallback callback, void* args)
{
    int type;
    *size = lbFile_8001634C(file);
    type = (dest >= 0x80000000) ? 0x21 : 0x23;
    HSD_DevComRequest(file, 0, dest, ROUND_UP_32(*size), type, pri, callback,
                      args);
}

void lbFile_80016580(const char* basename, u32 src, u32* dest,
                     HSD_DevComCallback callback, void* args)
{
    char* filename = lbFile_80016204(basename);
    s32 entry_num = DVDConvertPathToEntrynum(filename);
    PAD_STACK(4);

    if (entry_num == -1) {
        OSReport("file isn't exist %s = %d\n", filename, entry_num);
        __assert(lbFile_803BA508, 0x11A, "entry_num != -1");
    }

    lbFile_800164A4(entry_num, src, dest, 1, callback, args);
}

void lbFile_8001668C(const char* basename, u32* src, u32* dest)
{
    cancel = false;
    lbFile_80016580(basename, (u32) src, dest, lbFile_8001615C, 0);
    do {
    } while (!lbFile_800161A0());
}

inline void qwer(s32 a, const char* basename, u32* src, u32* dest)
{
    *dest = lbFile_800163D8(basename);
    *src = (u32) lbHeap_80015BD0(a, ROUND_UP_32(*dest));
    lbFile_80016580(basename, *src, dest, lbFile_8001615C, 0);

    do {
        continue;
    } while (!lbFile_800161A0());
}

void lbFile_80016760(const char* basename, u32* src, u32* dest)
{
    cancel = false;
    qwer(0, basename, src, dest);
}

inline u32 func_800163D8_inline(const char* basename)
{
    return lbFile_800163D8(basename);
}

bool lbFile_800168A0(s32 arg0, const char* basename, u32* src, u32* dest)
{
    if ((*src = (u32) lbDvd_8001819C(basename))) {
        *dest = func_800163D8_inline(basename);
        return true;
    } else {
        cancel = false;
        qwer(arg0, basename, src, dest);
        return false;
    }
}
