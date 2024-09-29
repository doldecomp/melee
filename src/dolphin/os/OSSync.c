#include <platform.h>
#include <placeholder.h>

#include <__mem.h>
#include <dolphin/os/OSCache.h>
#include <dolphin/os/OSSync.h>
#include <MetroTRK/intrinsics.h>

#define OS_SYS_CALL_HANDLER ((void*) 0x80000C00)
#define OS_HANDLER_SLOT_SIZE (0x100)

static void __OSSystemCallVectorStart(void);
static void __OSSystemCallVectorEnd(void);

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
} // clang-format on
#else

void __OSSystemCallVector(void)
{
    NOT_IMPLEMENTED;
}
#endif

#ifdef MWERKS_GEKKO
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
#else

void __OSInitSystemCall(void)
{
    NOT_IMPLEMENTED;
}
#endif
