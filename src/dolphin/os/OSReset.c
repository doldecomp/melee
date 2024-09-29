#include <placeholder.h>

#include <__mem.h>
#include <dolphin/os.h>
#include <dolphin/os/OSAudioSystem.h>
#include <dolphin/os/OSCache.h>
#include <dolphin/os/OSInterrupt.h>
#include <dolphin/os/OSReboot.h>
#include <dolphin/os/OSReset.h>
#include <dolphin/os/OSRtc.h>
#include <dolphin/os/OSThread.h>
#include <dolphin/pad/pad.h>

typedef struct OSResetQueue {
    OSResetFunctionInfo* first;
    OSResetFunctionInfo* last;
} OSResetQueue;

static OSResetQueue ResetFunctionQueue;

void OSRegisterResetFunction(OSResetFunctionInfo* func)
{
    OSResetFunctionInfo* tmp;
    OSResetFunctionInfo* iter;

    for (iter = ResetFunctionQueue.first;
         iter && iter->priority <= func->priority; iter = iter->next)
    {
    }

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

static void Reset(s32 arg0)
{
    NOT_IMPLEMENTED;
}

typedef struct Unk2 {
    u16 _0;
    u16 _2;
} Unk2;

extern volatile Unk2 DAT_cc002000 AT_ADDRESS(0xCC002000);

extern OSSram* __OSLockSram(void);

extern OSThreadQueue __OSActiveThreadQueue AT_ADDRESS(0x800000DC);

bool __OSCallResetFunctions(bool funcs_arg)
{
    OSResetFunctionInfo* iter;
    bool anyReset = false;

    for (iter = ResetFunctionQueue.first; iter != NULL; iter = iter->next) {
        anyReset |= !iter->func(funcs_arg);
    }

    anyReset |= !__OSSyncSram();

    return anyReset ? false : true;
}

static void KillThreads(void)
{
    OSThread* thread;
    OSThread* next;

    for (thread = __OSActiveThreadQueue.head; thread; thread = next) {
        next = thread->linkActive.next;
        switch (thread->state) {
        case 1:
        case 4:
            OSCancelThread(thread);
            continue;
        default:
            continue;
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

void OSResetSystem(int reset, u32 resetCode, bool forceMenu)
{
    u8 _[12];

    // Not initialized in all branches?
    bool disableRecalibration;

    OSDisableScheduler();
    __OSStopAudioSystem();

    if (reset == OS_RESET_SHUTDOWN) {
        disableRecalibration = __PADDisableRecalibration(true);
    }

    while (!__OSCallResetFunctions(false)) {
        continue;
    }

    if (reset == OS_RESET_HOTRESET && forceMenu) {
        OSSram* sram = __OSLockSram();
        sram->flags |= (1 << 6);

        __OSUnlockSram(true);

        while (!__OSSyncSram()) {
            continue;
        }
    }

    OSDisableInterrupts();
    __OSCallResetFunctions(true);
    LCDisable();

    if (reset == OS_RESET_HOTRESET) {
        __OSDoHotReset(resetCode);
    } else if (reset == OS_RESET_RESTART) {
        KillThreads();
        OSEnableScheduler();
        __OSReboot(resetCode, forceMenu);
    }

    KillThreads();
    memset(OSPhysicalToCached(0x40), 0, 0xCC - 0x40);
    memset(OSPhysicalToCached(0xD4), 0, 0xE8 - 0xD4);
    memset(OSPhysicalToCached(0xF4), 0, 0xF8 - 0xF4);
    memset(OSPhysicalToCached(0x3000), 0, 0xC0);
    memset(OSPhysicalToCached(0x30C8), 0, 0xD4 - 0xC8);

    __PADDisableRecalibration(disableRecalibration);
}

extern volatile u8 DAT_800030e2 AT_ADDRESS(0x800030E2);

typedef struct Unk {
    u8 pad[0x24];
    u32 resetCode;
} Unk;

extern volatile Unk DAT_cc003000 AT_ADDRESS(0xCC003000);

u32 OSGetResetCode(void)
{
    if (DAT_800030e2 != 0) {
        return 0x80000000;
    }

    return ((DAT_cc003000.resetCode & ~7) >> 3);
}
