#include <dolphin/os/OSInterrupt.h>

void lbl_80347374(void);

#pragma push
asm BOOL OSDisableInterrupts(void)
{ // clang-format off
    nofralloc
/* 80347364 00343F44  7C 60 00 A6 */	mfmsr r3
/* 80347368 00343F48  54 64 04 5E */	rlwinm r4, r3, 0, 0x11, 0xf
/* 8034736C 00343F4C  7C 80 01 24 */	mtmsr r4
/* 80347370 00343F50  54 63 8F FE */	rlwinm r3, r3, 0x11, 0x1f, 0x1f
entry lbl_80347374
/* 80347374 00343F54  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm BOOL OSEnableInterrupts(void)
{ // clang-format off
    nofralloc
/* 80347378 00343F58  7C 60 00 A6 */	mfmsr r3
/* 8034737C 00343F5C  60 64 80 00 */	ori r4, r3, 0x8000
/* 80347380 00343F60  7C 80 01 24 */	mtmsr r4
/* 80347384 00343F64  54 63 8F FE */	rlwinm r3, r3, 0x11, 0x1f, 0x1f
/* 80347388 00343F68  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm BOOL OSRestoreInterrupts(BOOL)
{ // clang-format off
    nofralloc
/* 8034738C 00343F6C  2C 03 00 00 */	cmpwi r3, 0
/* 80347390 00343F70  7C 80 00 A6 */	mfmsr r4
/* 80347394 00343F74  41 82 00 0C */	beq lbl_803473A0
/* 80347398 00343F78  60 85 80 00 */	ori r5, r4, 0x8000
/* 8034739C 00343F7C  48 00 00 08 */	b lbl_803473A4
lbl_803473A0:
/* 803473A0 00343F80  54 85 04 5E */	rlwinm r5, r4, 0, 0x11, 0xf
lbl_803473A4:
/* 803473A4 00343F84  7C A0 01 24 */	mtmsr r5
/* 803473A8 00343F88  54 84 8F FE */	rlwinm r4, r4, 0x11, 0x1f, 0x1f
/* 803473AC 00343F8C  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern unk_t lbl_804D7378;

#pragma push
asm OSInterruptHandler __OSSetInterruptHandler(OSInterruptType, OSInterruptHandler)
{ // clang-format off
    nofralloc
/* 803473B0 00343F90  7C 60 07 34 */	extsh r0, r3
/* 803473B4 00343F94  80 6D BC D8 */	lwz r3, lbl_804D7378(r13)
/* 803473B8 00343F98  54 00 10 3A */	slwi r0, r0, 2
/* 803473BC 00343F9C  7C A3 02 14 */	add r5, r3, r0
/* 803473C0 00343FA0  80 65 00 00 */	lwz r3, 0(r5)
/* 803473C4 00343FA4  90 85 00 00 */	stw r4, 0(r5)
/* 803473C8 00343FA8  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm OSInterruptHandler __OSGetInterruptHandler(OSInterruptType)
{ // clang-format off
    nofralloc
/* 803473CC 00343FAC  7C 60 07 34 */	extsh r0, r3
/* 803473D0 00343FB0  80 6D BC D8 */	lwz r3, lbl_804D7378(r13)
/* 803473D4 00343FB4  54 00 10 3A */	slwi r0, r0, 2
/* 803473D8 00343FB8  7C 63 00 2E */	lwzx r3, r3, r0
/* 803473DC 00343FBC  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern unk_t lbl_80347B80();
extern unk_t __OSSetExceptionHandler();
extern unk_t memset();

#pragma push
asm void __OSInterruptInit(void)
{ // clang-format off
    nofralloc
/* 803473E0 00343FC0  7C 08 02 A6 */	mflr r0
/* 803473E4 00343FC4  90 01 00 04 */	stw r0, 4(r1)
/* 803473E8 00343FC8  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 803473EC 00343FCC  93 E1 00 0C */	stw r31, 0xc(r1)
/* 803473F0 00343FD0  3F E0 80 00 */	lis r31, 0x80003040@ha
/* 803473F4 00343FD4  38 1F 30 40 */	addi r0, r31, 0x80003040@l
/* 803473F8 00343FD8  90 0D BC D8 */	stw r0, lbl_804D7378(r13)
/* 803473FC 00343FDC  38 80 00 00 */	li r4, 0
/* 80347400 00343FE0  38 A0 00 80 */	li r5, 0x80
/* 80347404 00343FE4  80 6D BC D8 */	lwz r3, lbl_804D7378(r13)
/* 80347408 00343FE8  4B CB BC F9 */	bl memset
/* 8034740C 00343FEC  38 00 00 00 */	li r0, 0
/* 80347410 00343FF0  90 1F 00 C4 */	stw r0, 0xc4(r31)
/* 80347414 00343FF4  3C 60 CC 00 */	lis r3, 0xCC003000@ha
/* 80347418 00343FF8  38 83 30 00 */	addi r4, r3, 0xCC003000@l
/* 8034741C 00343FFC  90 1F 00 C8 */	stw r0, 0xc8(r31)
/* 80347420 00344000  38 00 00 F0 */	li r0, 0xf0
/* 80347424 00344004  38 60 FF E0 */	li r3, -32
/* 80347428 00344008  90 04 00 04 */	stw r0, 4(r4)
/* 8034742C 0034400C  48 00 03 01 */	bl __OSMaskInterrupts
/* 80347430 00344010  3C 60 80 34 */	lis r3, lbl_80347B80@ha
/* 80347434 00344014  38 83 7B 80 */	addi r4, r3, lbl_80347B80@l
/* 80347438 00344018  38 60 00 04 */	li r3, 4
/* 8034743C 0034401C  4B FF C1 79 */	bl __OSSetExceptionHandler
/* 80347440 00344020  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80347444 00344024  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80347448 00344028  38 21 00 10 */	addi r1, r1, 0x10
/* 8034744C 0034402C  7C 08 03 A6 */	mtlr r0
/* 80347450 00344030  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

