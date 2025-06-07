#include <dolphin.h>
#include <dolphin/os.h>

#include "__os.h"

// These macros are copied from OSThread.c. Or ARE they the same
// macros? They dont seem to be in the SDK headers.
#define ENQUEUE_INFO(info, queue)                            \
    do {                                                     \
        struct OSResetFunctionInfo * __prev = (queue)->tail; \
        if (__prev == 0) {                                   \
            (queue)->head = (info);                          \
        } else {                                             \
            __prev->next = (info);                           \
        }                                                    \
        (info)->prev = __prev;                               \
        (info)->next = 0;                                    \
        (queue)->tail = (info);                              \
    } while(0);

#define DEQUEUE_INFO(info, queue)                           \
    do {                                                    \
        struct OSResetFunctionInfo * __next = (info)->next; \
        struct OSResetFunctionInfo * __prev = (info)->prev; \
        if (__next == 0) {                                  \
            (queue)->tail = __prev;                         \
        } else {                                            \
            __next->prev = __prev;                          \
        }                                                   \
        if (__prev == 0) {                                  \
            (queue)->head = __next;                         \
        } else {                                            \
            __prev->next = __next;                          \
        }                                                   \
    } while(0);

#define ENQUEUE_INFO_PRIO(info, queue)               \
    do {                                             \
        struct OSResetFunctionInfo * __prev;         \
        struct OSResetFunctionInfo * __next;         \
        for(__next = (queue)->head; __next           \
          && (__next->priority <= (info)->priority); \
                __next = __next->next) ;             \
                                                     \
        if (__next == 0) {                           \
            ENQUEUE_INFO(info, queue);               \
        } else {                                     \
            (info)->next = __next;                   \
            __prev = __next->prev;                   \
            __next->prev = (info);                   \
            (info)->prev = __prev;                   \
            if (__prev == 0) {                       \
                (queue)->head = (info);              \
            } else {                                 \
                __prev->next = (info);               \
            }                                        \
        }                                            \
    } while(0);

static struct OSResetFunctionQueue ResetFunctionQueue;

static int CallResetFunctions(int final);
static asm void Reset(unsigned long resetCode);

void OSRegisterResetFunction(struct OSResetFunctionInfo * info) {
    ASSERTLINE(0x76, info->func);

    ENQUEUE_INFO_PRIO(info, &ResetFunctionQueue);
}

void OSUnregisterResetFunction(struct OSResetFunctionInfo * info) {
    DEQUEUE_INFO(info, &ResetFunctionQueue);
}

static int CallResetFunctions(int final) {
    struct OSResetFunctionInfo * info;
    int err = 0;

    for(info = ResetFunctionQueue.head; info; info = info->next) {
        err |= !info->func(final);
    }
    err |= !__OSSyncSram();
    if (err) {
        return 0;
    }
    return 1;
}

static asm void Reset(unsigned long resetCode) {
    nofralloc
    b L_000001BC
L_000001A0:
    mfspr r8, HID0
    ori r8, r8, 0x8
    mtspr HID0, r8
    isync
    sync
    nop
    b L_000001C0
L_000001BC:
    b L_000001DC
L_000001C0:
    mftb r5, 268
L_000001C4:
    mftb r6, 268
    subf r7, r5, r6
    cmplwi r7, 0x1124
    blt L_000001C4
    nop
    b L_000001E0
L_000001DC:
    b L_000001FC
L_000001E0:
    lis r8, 0xcc00
    ori r8, r8, 0x3000
    li r4, 0x3
    stw r4, 0x24(r8)
    stw r3, 0x24(r8)
    nop
    b L_00000200
L_000001FC:
    b L_00000208
L_00000200:
    nop
    b L_00000200
L_00000208:
    b L_000001A0
}

int __PADDisableRecalibration(int);

static void CancelThreads(void)
{
    OSThread* thread = __OSActiveThreadQueue.head;
    while (thread != NULL) {
        OSThread* next = thread->linkActive.next;
        switch (thread->state) {
        case 1:
        case 4:
            OSCancelThread(thread);
        default:
            break;
        }
        thread = next;
    }
}

void __OSDoHotReset(int arg0)
{
    OSDisableInterrupts();
    __VIRegs[1] = 0;
    ICFlashInvalidate();
    Reset(arg0 << 3);
}

void OSResetSystem(int reset, unsigned long resetCode, int forceMenu) {
    int rc;
    int enabled;
    int padcal;
    struct OSSram * sram;
    u8 _[8];

    OSDisableScheduler();
    __OSStopAudioSystem();

    if (reset == 2) {
        padcal = __PADDisableRecalibration(1);
    }

    do {} while (CallResetFunctions(0) == 0);

    if ((reset == 1 && (forceMenu != 0))) {
        sram = __OSLockSram();
        sram->flags |= 0x40;
        __OSUnlockSram(1);
        do {} while(__OSSyncSram() == 0);
    }
    enabled = OSDisableInterrupts();
    rc = CallResetFunctions(1);
    LCDisable();
    ASSERTLINE(0x117, rc);
    if (reset == 1) {
        enabled = OSDisableInterrupts();
        __VIRegs[1] = 0;
        ICFlashInvalidate();
        Reset(resetCode * 8);
    } else if (reset == 0) {
        CancelThreads();
        OSEnableScheduler();
        __OSReboot(resetCode, forceMenu);
    }

    CancelThreads();

    memset((void*) 0x80000040, 0, 0x8C);
    memset((void*) 0x800000D4, 0, 0x14);
    memset((void*) 0x800000F4, 0, 4);
    memset((void*) 0x80003000, 0, 0xC0);
    memset((void*) 0x800030C8, 0, 0xC);

    __PADDisableRecalibration(padcal);
}

u8 unk : 0x800030E2;

unsigned long OSGetResetCode() {
    if (unk != 0) {
        return 0x80000000;
    }
    return (__PIRegs[9] & ~7) >> 3;
}
