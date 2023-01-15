#include <melee/lb/lbfile.h>

#include <dolphin/dvd/dvd.h>
#include <dolphin/os/os.h>
#include <dolphin/os/OSInterrupt.h>
#include <melee/lb/lbdvd.h>
#include <melee/lb/lbheap.h>
#include <melee/lb/lblanguage.h>
#include <melee/lb/lbunknown_004.h>
#include <string.h>
#include <sysdolphin/baselib/archive.h>
#include <sysdolphin/baselib/debug.h>
#include <sysdolphin/baselib/devcom.h>

static char lbl_803BA508[] = __FILE__;

static bool cancel;

void lbFile_8001615C(int r3, int r4, int r5, bool cancelflag)
{
    if (cancelflag) {
        __assert(lbl_803BA508, 71, "!cancelflag");
    }
    cancel = true;
}

#ifdef MUST_MATCH

#pragma push
asm bool lbFile_800161A0()
{
    // clang-format off
    nofralloc
/* 800161A0 00012D80  7C 08 02 A6 */	mflr r0
/* 800161A4 00012D84  90 01 00 04 */	stw r0, 4(r1)
/* 800161A8 00012D88  94 21 FF F8 */	stwu r1, -8(r1)
/* 800161AC 00012D8C  48 00 34 25 */	bl func_800195D0
/* 800161B0 00012D90  80 6D AD 28 */	lwz r3, cancel(r13)
/* 800161B4 00012D94  80 01 00 0C */	lwz r0, 0xc(r1)
/* 800161B8 00012D98  38 21 00 08 */	addi r1, r1, 8
/* 800161BC 00012D9C  7C 08 03 A6 */	mtlr r0
/* 800161C0 00012DA0  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#else

bool lbFile_800161A0(void)
{
    func_800195D0();
    return cancel;
}

#endif

void func_800161C4(int arg0, int arg1, HSD_Archive* arg2, int arg3, int arg4,
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
static char lbl_80432058[MAX_FILENAME_LENGTH];

// append file extension (if needed)
char* func_80016204(const char* basename)
{
    const char* cur = basename;
    s32 pos = 0;

    while (cur[0] != '\0' && cur[0] != '.') {
        // no room for file extension?
        if (pos > MAX_BASENAME_LENGTH) {
            OSReport("Error : file name too long %s.", basename);
            __assert(lbl_803BA508, 0x99, "NULL");
        }
        lbl_80432058[pos++] = cur++[0];
    }
    // keep any existing file extension
    if (cur[0] != '\0' && cur[1] != '\0') {
        strcpy(lbl_80432058, basename);
        // otherwise, append the appropriate extension for the locale
    } else if (cur[0] == '.') {
        lbl_80432058[pos++] = '.';
        if (lbLang_IsSettingUS()) {
            strcpy(&lbl_80432058[pos], "usd");
        } else {
            strcpy(&lbl_80432058[pos], "dat");
        }
    } else {
        lbl_80432058[pos++] = '.';
        if (lbLang_IsSavedLanguageUS()) {
            strcpy(&lbl_80432058[pos], "usd");
        } else {
            strcpy(&lbl_80432058[pos], "dat");
        }
    }
    return lbl_80432058;
}

size_t func_8001634C(s32 fileno)
{
    DVDFileInfo info;
    size_t length;
    bool intr = OSDisableInterrupts();

    if (!DVDFastOpen(fileno, &info)) {
        OSReport("Cannot open file no=%d.", fileno);
        __assert(lbl_803BA508, 0xD8, "0");
    }

    length = info.length;
    DVDClose(&info);
    OSRestoreInterrupts(intr);
    return length;
}

s32 func_800163D8(const char* basename)
{
    s32 entry_num;
    const char* filename = func_80016204(basename);
    entry_num = DVDConvertPathToEntrynum(filename);
    if (entry_num == -1) {
        OSReport("file isn't exist %s = %d\n", filename, entry_num);
        __assert(lbl_803BA508, 0xEE, "entry_num != -1");
    }
    return func_8001634C(entry_num);
}

void func_800164A4(s32 arg0, HSD_Archive* arg1, s32* arg2, s32 arg3,
                   HSD_DevComCallback arg4, s32 arg5)
{
    s32 var_r0;
    *arg2 = func_8001634C(arg0);
    var_r0 = ((u32) arg1 >= 0x80000000) ? 0x21 : 0x23;
    HSD_DevComRequest(arg0, 0, arg1, (*arg2 + 0x1F) & 0xFFFFFFE0, var_r0, arg3,
                      arg4, arg5);
}

void func_80016580(const char* basename, HSD_Archive* arg1, s32* arg2,
                   HSD_DevComCallback arg3, s32 arg4)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused[4];
#endif

    const char* filename = func_80016204(basename);
    s32 entry_num = DVDConvertPathToEntrynum(filename);

    if (entry_num == -1) {
        OSReport("file isn't exist %s = %d\n", filename, entry_num);
        __assert(lbl_803BA508, 0x11A, "entry_num != -1");
    }

    func_800164A4(entry_num, arg1, arg2, 1, arg3, arg4);
}

void func_8001668C(const char* arg0, HSD_Archive* arg1, s32* arg2)
{
    cancel = false;
    func_80016580(arg0, arg1, arg2, lbFile_8001615C, 0);
    do {
    } while (!lbFile_800161A0());
}

inline void qwer(s32 a, const char* arg0, HSD_Archive** arg1, s32* arg2)
{
    *arg2 = func_800163D8(arg0);
    *arg1 = func_80015BD0(a, (*arg2 + 0x1F) & 0xFFFFFFE0);
    func_80016580(arg0, *arg1, arg2, lbFile_8001615C, 0);

    do {
        continue;
    } while (!lbFile_800161A0());
}

void func_80016760(const char* arg0, HSD_Archive** arg1, s32* arg2)
{
    cancel = false;
    qwer(0, arg0, arg1, arg2);
}

inline s32 func_800163D8_inline(const char* arg1)
{
    return func_800163D8(arg1);
}

bool func_800168A0(s32 arg0, const char* arg1, HSD_Archive** arg2, s32* arg3)
{
    if ((*arg2 = func_8001819C(arg1))) {
        *arg3 = func_800163D8_inline(arg1);
        return true;
    } else {
        cancel = false;
        qwer(arg0, arg1, arg2, arg3);
        return false;
    }
}
