#include <dolphin/os/OSInterrupt.h>
#include <dolphin/os/OSReset.h>
#include <dolphin/os/OSThread.h>
#include <dolphin/os/os.h>

typedef struct OSResetQueue {
    OSResetFunctionInfo* first;
    OSResetFunctionInfo* last;
} OSResetQueue;

static OSResetQueue ResetFunctionQueue;

void OSRegisterResetFunction(OSResetFunctionInfo* func)
{
    OSResetFunctionInfo* tmp;
    OSResetFunctionInfo* iter;

    for (iter = ResetFunctionQueue.first; iter && iter->priority <= func->priority; iter = iter->next) {}

    if (iter == NULL) {
        tmp = ResetFunctionQueue.last;
        if (tmp == NULL) {
            ResetFunctionQueue.first = func;
        } else {
            tmp->next = func;
        }
        func->prev = tmp;
        func->next = NULL;
        ResetFunctionQueue.last = func;
        return;
    }

    func->next = iter;
    tmp = iter->prev;
    iter->prev = func;
    func->prev = tmp;
    if (tmp == NULL) {
        ResetFunctionQueue.first = func;
        return;
    }
    tmp->next = func;
}

static asm unk_t Reset()
{ // clang-format off
    nofralloc
/* 80348394 00344F74  48 00 00 20 */	b lbl_803483B4
lbl_80348398:
/* 80348398 00344F78  7D 10 FA A6 */	mfspr r8, 0x3f0
/* 8034839C 00344F7C  61 08 00 08 */	ori r8, r8, 8
/* 803483A0 00344F80  7D 10 FB A6 */	mtspr 0x3f0, r8
/* 803483A4 00344F84  4C 00 01 2C */	isync 
/* 803483A8 00344F88  7C 00 04 AC */	sync
/* 803483AC 00344F8C  60 00 00 00 */	nop 
/* 803483B0 00344F90  48 00 00 08 */	b lbl_803483B8
lbl_803483B4:
/* 803483B4 00344F94  48 00 00 20 */	b lbl_803483D4
lbl_803483B8:
/* 803483B8 00344F98  7C AC 42 E6 */	mftb r5, 0x10c
lbl_803483BC:
/* 803483BC 00344F9C  7C CC 42 E6 */	mftb r6, 0x10c
/* 803483C0 00344FA0  7C E5 30 50 */	subf r7, r5, r6
/* 803483C4 00344FA4  28 07 11 24 */	cmplwi r7, 0x1124
/* 803483C8 00344FA8  41 80 FF F4 */	blt lbl_803483BC
/* 803483CC 00344FAC  60 00 00 00 */	nop 
/* 803483D0 00344FB0  48 00 00 08 */	b lbl_803483D8
lbl_803483D4:
/* 803483D4 00344FB4  48 00 00 20 */	b lbl_803483F4
lbl_803483D8:
/* 803483D8 00344FB8  3D 00 CC 00 */	lis r8, 0xCC003000@h
/* 803483DC 00344FBC  61 08 30 00 */	ori r8, r8, 0xCC003000@l
/* 803483E0 00344FC0  38 80 00 03 */	li r4, 3
/* 803483E4 00344FC4  90 88 00 24 */	stw r4, 0x24(r8)
/* 803483E8 00344FC8  90 68 00 24 */	stw r3, 0x24(r8)
/* 803483EC 00344FCC  60 00 00 00 */	nop 
/* 803483F0 00344FD0  48 00 00 08 */	b lbl_803483F8
lbl_803483F4:
/* 803483F4 00344FD4  48 00 00 0C */	b lbl_80348400
lbl_803483F8:
/* 803483F8 00344FD8  60 00 00 00 */	nop 
/* 803483FC 00344FDC  4B FF FF FC */	b lbl_803483F8
lbl_80348400:
/* 80348400 00344FE0  4B FF FF 98 */	b lbl_80348398
} // clang-format on

typedef struct Unk2 {
    u16 _0;
    u16 _2;
} Unk2;

volatile Unk2 DAT_cc002000 : 0xcc002000;

typedef struct OSSram {
    u16 checkSum;
    u16 checkSumInv;
    u32 ead0;
    u32 ead1;
    u32 counterBias;
    s8 displayOffsetH;
    u8 ntd;
    u8 language;
    u8 flags;
} OSSram;

extern OSSram* __OSLockSram(void);

OSThreadQueue __OSActiveThreadQueue : 0x800000DC;

BOOL __OSCallResetFunctions(u32 arg0)
{
    OSResetFunctionInfo* iter;
    s32 retCode = 0;

    for (iter = ResetFunctionQueue.first; iter != NULL; iter = iter->next) {
        retCode |= !iter->func(arg0);
    }
    retCode |= !__OSSyncSram();
    if (retCode) {
        return 0;
    }
    return 1;
}

static void KillThreads(void)
{
    OSThread* thread;
    OSThread* next;

    for (thread = __OSActiveThreadQueue.head; thread; thread = next) {
        next = thread->next2;
        switch (thread->state) {
        case 1:
        case 4:
            OSCancelThread(thread);
            break;
        default:
            break;
        }
    }
}

void __OSDoHotReset(s32 arg0)
{
    OSDisableInterrupts();
    DAT_cc002000._2 = 0;
    ICFlashInvalidate();
    Reset(arg0 * 8);
}

void OSResetSystem(int reset, u32 resetCode, BOOL forceMenu)
{
    BOOL rc;
    BOOL disableRecalibration;
    u32 unk[3];
    OSDisableScheduler();
    __OSStopAudioSystem();

    if (reset == OS_RESET_SHUTDOWN) {
        disableRecalibration = __PADDisableRecalibration(TRUE);
    }

    while (!__OSCallResetFunctions(FALSE)) {}

    if (reset == OS_RESET_HOTRESET && forceMenu) {
        OSSram* sram;

        sram = __OSLockSram();
        sram->flags |= 0x40;
        __OSUnlockSram(TRUE);

        while (!__OSSyncSram()) {}
    }
    OSDisableInterrupts();
    __OSCallResetFunctions(TRUE);
    LCDisable();
    if (reset == OS_RESET_HOTRESET) {
        __OSDoHotReset(resetCode);
    } else if (reset == OS_RESET_RESTART) {
        KillThreads();
        OSEnableScheduler();
        __OSReboot(resetCode, forceMenu);
    }
    KillThreads();
    memset(OSPhysicalToCached(0x40), 0, 0xcc - 0x40);
    memset(OSPhysicalToCached(0xd4), 0, 0xe8 - 0xd4);
    memset(OSPhysicalToCached(0xf4), 0, 0xf8 - 0xf4);
    memset(OSPhysicalToCached(0x3000), 0, 0xc0);
    memset(OSPhysicalToCached(0x30c8), 0, 0xd4 - 0xc8);

    __PADDisableRecalibration(disableRecalibration);
}

volatile u8 DAT_800030e2 : 0x800030e2;
typedef struct Unk {
    u8 pad[0x24];
    u32 resetCode;
} Unk;
volatile Unk DAT_cc003000 : 0xcc003000;

u32 OSGetResetCode(void)
{
    if (DAT_800030e2 != 0) {
        return 0x80000000;
    }
    return ((DAT_cc003000.resetCode & ~7) >> 3);
}
