#include <dolphin/os/OSError.h>
#include <dolphin/os/OSInterrupt.h>
#include <dolphin/os/OSMemory.h>

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

extern OSErrorHandler __OSErrorTable[];
extern unk_t __OSUnhandledException();

#pragma push
asm unk_t MEMIntrruptHandler()
{ // clang-format off
    nofralloc
/* 80347C38 00344818  7C 08 02 A6 */	mflr r0
/* 80347C3C 0034481C  3C 60 CC 00 */	lis r3, 0xCC004000@ha
/* 80347C40 00344820  90 01 00 04 */	stw r0, 4(r1)
/* 80347C44 00344824  39 03 40 00 */	addi r8, r3, 0xCC004000@l
/* 80347C48 00344828  38 00 00 00 */	li r0, 0
/* 80347C4C 0034482C  94 21 FF F8 */	stwu r1, -8(r1)
/* 80347C50 00344830  A0 E3 40 24 */	lhz r7, 0x4024(r3)
/* 80347C54 00344834  3C 60 80 4A */	lis r3, __OSErrorTable@ha
/* 80347C58 00344838  A0 C8 00 22 */	lhz r6, 0x22(r8)
/* 80347C5C 0034483C  38 63 7C 40 */	addi r3, r3, __OSErrorTable@l
/* 80347C60 00344840  A0 A8 00 1E */	lhz r5, 0x1e(r8)
/* 80347C64 00344844  50 E6 81 9E */	rlwimi r6, r7, 0x10, 6, 0xf
/* 80347C68 00344848  B0 08 00 20 */	sth r0, 0x20(r8)
/* 80347C6C 0034484C  81 83 00 3C */	lwz r12, 0x3c(r3)
/* 80347C70 00344850  28 0C 00 00 */	cmplwi r12, 0
/* 80347C74 00344854  41 82 00 18 */	beq lbl_80347C8C
/* 80347C78 00344858  7D 88 03 A6 */	mtlr r12
/* 80347C7C 0034485C  38 60 00 0F */	li r3, 0xf
/* 80347C80 00344860  4C C6 31 82 */	crclr 6
/* 80347C84 00344864  4E 80 00 21 */	blrl 
/* 80347C88 00344868  48 00 00 0C */	b lbl_80347C94
lbl_80347C8C:
/* 80347C8C 0034486C  38 60 00 0F */	li r3, 0xf
/* 80347C90 00344870  4B FF DB E1 */	bl __OSUnhandledException
lbl_80347C94:
/* 80347C94 00344874  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80347C98 00344878  38 21 00 08 */	addi r1, r1, 8
/* 80347C9C 0034487C  7C 08 03 A6 */	mtlr r0
/* 80347CA0 00344880  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t Config24MB()
{ // clang-format off
    nofralloc
/* 80347CA4 00344884  38 E0 00 00 */	li r7, 0
/* 80347CA8 00344888  3C 80 00 00 */	lis r4, 0x00000002@ha
/* 80347CAC 0034488C  38 84 00 02 */	addi r4, r4, 0x00000002@l
/* 80347CB0 00344890  3C 60 80 00 */	lis r3, 0x800001FF@ha
/* 80347CB4 00344894  38 63 01 FF */	addi r3, r3, 0x800001FF@l
/* 80347CB8 00344898  3C C0 01 00 */	lis r6, 0x01000002@ha
/* 80347CBC 0034489C  38 C6 00 02 */	addi r6, r6, 0x01000002@l
/* 80347CC0 003448A0  3C A0 81 00 */	lis r5, 0x810000FF@ha
/* 80347CC4 003448A4  38 A5 00 FF */	addi r5, r5, 0x810000FF@l
/* 80347CC8 003448A8  4C 00 01 2C */	isync 
/* 80347CCC 003448AC  7C F8 83 A6 */	mtdbatu 0, r7
/* 80347CD0 003448B0  7C 99 83 A6 */	mtdbatl 0, r4
/* 80347CD4 003448B4  7C 78 83 A6 */	mtdbatu 0, r3
/* 80347CD8 003448B8  4C 00 01 2C */	isync 
/* 80347CDC 003448BC  7C F0 83 A6 */	mtibatu 0, r7
/* 80347CE0 003448C0  7C 91 83 A6 */	mtibatl 0, r4
/* 80347CE4 003448C4  7C 70 83 A6 */	mtibatu 0, r3
/* 80347CE8 003448C8  4C 00 01 2C */	isync 
/* 80347CEC 003448CC  7C FC 83 A6 */	mtdbatu 2, r7
/* 80347CF0 003448D0  7C DD 83 A6 */	mtdbatl 2, r6
/* 80347CF4 003448D4  7C BC 83 A6 */	mtdbatu 2, r5
/* 80347CF8 003448D8  4C 00 01 2C */	isync 
/* 80347CFC 003448DC  7C F4 83 A6 */	mtibatu 2, r7
/* 80347D00 003448E0  7C D5 83 A6 */	mtibatl 2, r6
/* 80347D04 003448E4  7C B4 83 A6 */	mtibatu 2, r5
/* 80347D08 003448E8  4C 00 01 2C */	isync 
/* 80347D0C 003448EC  7C 60 00 A6 */	mfmsr r3
/* 80347D10 003448F0  60 63 00 30 */	ori r3, r3, 0x30
/* 80347D14 003448F4  7C 7B 03 A6 */	mtspr 0x1b, r3
/* 80347D18 003448F8  7C 68 02 A6 */	mflr r3
/* 80347D1C 003448FC  7C 7A 03 A6 */	mtspr 0x1a, r3
/* 80347D20 00344900  4C 00 00 64 */	rfi 
} // clang-format on
#pragma pop
