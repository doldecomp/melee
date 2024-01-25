#include <dolphin/dvd/forward.h>

#include "lb/lbfile.h"

#include "lb/lb_0192.h"
#include "lb/lbdvd.h"
#include "lb/lbheap.h"
#include "lb/lblanguage.h"

#include <string.h>
#include <dolphin/dvd/dvd.h>
#include <dolphin/os.h>
#include <dolphin/os/OSInterrupt.h>
#include <baselib/debug.h>
#include <baselib/devcom.h>

static char lbFile_803BA508[] = __FILE__;

static bool cancel;

void lbFile_8001615C(int r3, int r4, int r5, bool cancelflag)
{
    if (cancelflag) {
        __assert(lbFile_803BA508, 71, "!cancelflag");
    }
    cancel = true;
}

#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif
bool lbFile_800161A0(void)
{
    lb_800195D0();
    return cancel;
}
#ifdef MUST_MATCH
#pragma pop
#endif

void lbFile_800161C4(int arg0, int arg1, HSD_Archive* arg2, int arg3, int arg4,
                     int arg5)
{
    cancel = false;
    HSD_DevComRequest(arg0, arg1, arg2, arg3, arg4, arg5, lbFile_8001615C, 0);

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

typedef struct OldDVDFileInfo {
    /*0x00*/ DVDCommandBlock cb;
    /*0x30*/ u32 startAddr;
    /*0x34*/ u32 length;
} OldDVDFileInfo;

/// @bug OldDVDFileInfo is needed to match stack allocation sizes. However,
/// the actual DVDFileInfo is 4 bytes longer due to callback.
/// This means that calls to lbFile_8001634C write 4 bytes past where it should
/// on the stack.
///
size_t lbFile_8001634C(s32 fileno)
{
    OldDVDFileInfo info;
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
    const char* filename = lbFile_80016204(basename);
    entry_num = DVDConvertPathToEntrynum(filename);
    if (entry_num == -1) {
        OSReport("file isn't exist %s = %d\n", filename, entry_num);
        __assert(lbFile_803BA508, 0xEE, "entry_num != -1");
    }
    return lbFile_8001634C(entry_num);
}

void lbFile_800164A4(s32 arg0, HSD_Archive* arg1, s32* arg2, s32 arg3,
                     HSD_DevComCallback arg4, s32 arg5)
{
    s32 var_r0;
    *arg2 = lbFile_8001634C(arg0);
    var_r0 = ((u32) arg1 >= 0x80000000) ? 0x21 : 0x23;
    HSD_DevComRequest(arg0, 0, arg1, (*arg2 + 0x1F) & 0xFFFFFFE0, var_r0, arg3,
                      arg4, arg5);
}

void lbFile_80016580(const char* basename, HSD_Archive* arg1, s32* arg2,
                     HSD_DevComCallback arg3, s32 arg4)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    const char* filename = lbFile_80016204(basename);
    s32 entry_num = DVDConvertPathToEntrynum(filename);

    if (entry_num == -1) {
        OSReport("file isn't exist %s = %d\n", filename, entry_num);
        __assert(lbFile_803BA508, 0x11A, "entry_num != -1");
    }

    lbFile_800164A4(entry_num, arg1, arg2, 1, arg3, arg4);
}

void lbFile_8001668C(const char* arg0, HSD_Archive* arg1, s32* arg2)
{
    cancel = false;
    lbFile_80016580(arg0, arg1, arg2, lbFile_8001615C, 0);
    do {
    } while (!lbFile_800161A0());
}

inline void qwer(s32 a, const char* arg0, HSD_Archive** arg1, s32* arg2)
{
    *arg2 = lbFile_800163D8(arg0);
    *arg1 = lbHeap_80015BD0(a, (*arg2 + 0x1F) & 0xFFFFFFE0);
    lbFile_80016580(arg0, *arg1, arg2, lbFile_8001615C, 0);

    do {
        continue;
    } while (!lbFile_800161A0());
}

void lbFile_80016760(const char* arg0, HSD_Archive** arg1, s32* arg2)
{
    cancel = false;
    qwer(0, arg0, arg1, arg2);
}

inline s32 func_800163D8_inline(const char* arg1)
{
    return lbFile_800163D8(arg1);
}

bool lbFile_800168A0(s32 arg0, const char* arg1, HSD_Archive** arg2, s32* arg3)
{
    if ((*arg2 = lbDvd_8001819C(arg1))) {
        *arg3 = func_800163D8_inline(arg1);
        return true;
    } else {
        cancel = false;
        qwer(arg0, arg1, arg2, arg3);
        return false;
    }
}
