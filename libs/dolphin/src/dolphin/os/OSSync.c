#include <dolphin.h>

#include "__os.h"
#include <dolphin/os.h>

void __OSSystemCallVectorStart();
void __OSSystemCallVectorEnd();

static asm void SystemCallVector(void)
{
    // clang-format off
entry __OSSystemCallVectorStart
    nofralloc
    mfspr r9, HID0
    ori r10, r9, 0x8
    mtspr HID0, r10
    isync
    sync
    mtspr HID0, r9
    rfi
entry __OSSystemCallVectorEnd
    nop
    // clang-format on
}

void __OSInitSystemCall(void)
{
    void* addr = (void*) OSPhysicalToCached(0xC00);

    memcpy(addr, __OSSystemCallVectorStart,
           (u32) &__OSSystemCallVectorEnd - (u32) &__OSSystemCallVectorStart);
    DCFlushRangeNoSync(addr, 0x100);
    __sync();
    ICInvalidateRange(addr, 0x100);
}
