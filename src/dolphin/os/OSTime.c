#include <dolphin/os/OSTime.h>

#pragma push
asm s64 OSGetTime(void)
{ // clang-format off
    nofralloc
/* 8034C3F0 00348FD0  7C 6D 42 E6 */	mftbu r3
/* 8034C3F4 00348FD4  7C 8C 42 E6 */	mftb r4, 0x10c
/* 8034C3F8 00348FD8  7C AD 42 E6 */	mftbu r5
/* 8034C3FC 00348FDC  7C 03 28 00 */	cmpw r3, r5
/* 8034C400 00348FE0  40 82 FF F0 */	bne OSGetTime
/* 8034C404 00348FE4  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm OSTick OSGetTick(void)
{ // clang-format off
    nofralloc
/* 8034C408 00348FE8  7C 6C 42 E6 */	mftb r3, 0x10c
/* 8034C40C 00348FEC  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop
