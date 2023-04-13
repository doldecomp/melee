#include <placeholder.h>
#include <string.h>
#include <dolphin/os/OSCache.h>
#include <dolphin/os/OSSync.h>
#include <MetroTRK/intrinsics.h>
#include <Runtime/__mem.h>

#define OS_SYS_CALL_HANDLER ((void*) 0x80000C00)
#define OS_HANDLER_SLOT_SIZE (0x100)

void __OSSystemCallVectorStart(void);
void __OSSystemCallVectorEnd(void);

#ifdef MWERKS_GEKKO

asm void __OSSystemCallVector(void)
{ // clang-format off
    nofralloc
entry __OSSystemCallVectorStart
    mfspr r9, DBSR
    ori r10, r9, 8
    mtspr DBSR, r10
    isync
    sync
    mtspr DBSR, r9
    rfi
entry __OSSystemCallVectorEnd
    nop
} //clang-format on

#else

void __OSSystemCallVector(void)
{
    NOT_IMPLEMENTED;
}

#endif

/// @attention <tt>peephole off</tt> is needed to match.
void __OSInitSystemCall(void)
{
    void* handler = OS_SYS_CALL_HANDLER;
    memcpy(handler, __OSSystemCallVectorStart,
        (u32) __OSSystemCallVectorEnd - (u32) __OSSystemCallVectorStart);
    DCFlushRangeNoSync(handler, OS_HANDLER_SLOT_SIZE);
    __sync();
    ICInvalidateRange(handler, OS_HANDLER_SLOT_SIZE);
}
