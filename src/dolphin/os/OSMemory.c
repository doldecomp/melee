#include <dolphin/os/OSMemory.h>
#include <dolphin/os/OSInterrupt.h>

u32 OSGetPhysicalMemSize(void)
{
    return *(u32*) 0x80000028;
}

#pragma push
asm unk_t OSGetConsoleSimulatedMemSize()
{ // clang-format off
    nofralloc
/* 80347BF0 003447D0  3C 60 80 00 */	lis r3, 0x800000F0@ha
/* 80347BF4 003447D4  80 63 00 F0 */	lwz r3, 0x800000F0@l(r3)
/* 80347BF8 003447D8  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t OSOnReset()
{ // clang-format off
    nofralloc
/* 80347BFC 003447DC  7C 08 02 A6 */	mflr r0
/* 80347C00 003447E0  2C 03 00 00 */	cmpwi r3, 0
/* 80347C04 003447E4  90 01 00 04 */	stw r0, 4(r1)
/* 80347C08 003447E8  94 21 FF F8 */	stwu r1, -8(r1)
/* 80347C0C 003447EC  41 82 00 18 */	beq lbl_80347C24
/* 80347C10 003447F0  3C 60 CC 00 */	lis r3, 0xCC004010@ha
/* 80347C14 003447F4  38 00 00 FF */	li r0, 0xff
/* 80347C18 003447F8  B0 03 40 10 */	sth r0, 0xCC004010@l(r3)
/* 80347C1C 003447FC  3C 60 F0 00 */	lis r3, 0xf000
/* 80347C20 00344800  4B FF FB 0D */	bl __OSMaskInterrupts
lbl_80347C24:
/* 80347C24 00344804  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80347C28 00344808  38 60 00 01 */	li r3, 1
/* 80347C2C 0034480C  38 21 00 08 */	addi r1, r1, 8
/* 80347C30 00344810  7C 08 03 A6 */	mtlr r0
/* 80347C34 00344814  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop
