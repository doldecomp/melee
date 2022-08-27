#include <dolphin/types.h>
#include <string.h>

#define OS_SYS_CALL_HANDLER ((void*) 0x80000C00)
#define OS_HANDLER_SLOT_SIZE 0x100

void __OSSystemCallVectorStart(void);
void __OSSystemCallVectorEnd(void);

#pragma push
asm unk_t SystemCallVector()
{ // clang-format off
    nofralloc
entry __OSSystemCallVectorStart
/* 80092ACC 0008FA0C  7D 30 FA A6 */	mfspr r9, 0x3f0
/* 80092AD0 0008FA10  61 2A 00 08 */	ori r10, r9, 8
/* 80092AD4 0008FA14  7D 50 FB A6 */	mtspr 0x3f0, r10
/* 80092AD8 0008FA18  4C 00 01 2C */	isync
/* 80092ADC 0008FA1C  7C 00 04 AC */	sync
/* 80092AE0 0008FA20  7D 30 FB A6 */	mtspr 0x3f0, r9
/* 80092AE4 0008FA24  4C 00 00 64 */	rfi 
entry __OSSystemCallVectorEnd
/* 80092AE8 0008FA28  60 00 00 00 */	nop 
} // clang-format on
#pragma pop

extern void ICInvalidateRange(void*, u32);
extern unk_t DCFlushRangeNoSync();

void __OSInitSystemCall(void)
{
    memcpy(OS_SYS_CALL_HANDLER, __OSSystemCallVectorStart, (u32) __OSSystemCallVectorEnd - (u32) __OSSystemCallVectorStart);

    DCFlushRangeNoSync(OS_SYS_CALL_HANDLER, OS_HANDLER_SLOT_SIZE);
    __sync();
    ICInvalidateRange(OS_SYS_CALL_HANDLER, OS_HANDLER_SLOT_SIZE);
}
