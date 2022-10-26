#include <dolphin/os/OSInterrupt.h>
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

#pragma push
asm unk_t __OSGetSystemTime()
{ // clang-format off
    nofralloc
/* 8034C410 00348FF0  7C 08 02 A6 */	mflr r0
/* 8034C414 00348FF4  90 01 00 04 */	stw r0, 4(r1)
/* 8034C418 00348FF8  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8034C41C 00348FFC  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8034C420 00349000  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8034C424 00349004  93 A1 00 14 */	stw r29, 0x14(r1)
/* 8034C428 00349008  4B FF AF 3D */	bl OSDisableInterrupts
/* 8034C42C 0034900C  7C 7F 1B 78 */	mr r31, r3
/* 8034C430 00349010  4B FF FF C1 */	bl OSGetTime
/* 8034C434 00349014  3C C0 80 00 */	lis r6, 0x800030DC@ha
/* 8034C438 00349018  80 A6 30 DC */	lwz r5, 0x800030DC@l(r6)
/* 8034C43C 0034901C  80 06 30 D8 */	lwz r0, 0x30d8(r6)
/* 8034C440 00349020  7F A5 20 14 */	addc r29, r5, r4
/* 8034C444 00349024  7F C0 19 14 */	adde r30, r0, r3
/* 8034C448 00349028  7F E3 FB 78 */	mr r3, r31
/* 8034C44C 0034902C  4B FF AF 41 */	bl OSRestoreInterrupts
/* 8034C450 00349030  7F A4 EB 78 */	mr r4, r29
/* 8034C454 00349034  7F C3 F3 78 */	mr r3, r30
/* 8034C458 00349038  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8034C45C 0034903C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8034C460 00349040  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8034C464 00349044  7C 08 03 A6 */	mtlr r0
/* 8034C468 00349048  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 8034C46C 0034904C  38 21 00 20 */	addi r1, r1, 0x20
/* 8034C470 00349050  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop
