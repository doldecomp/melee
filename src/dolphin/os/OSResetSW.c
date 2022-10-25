#include <dolphin/os/OSInterrupt.h>
#include <dolphin/os/OSResetSW.h>

/* 00345650 */ s32 OSGetResetSwitchState(OSResetSW_Unk1 *);

extern unk_t lbl_804D73C4;
extern unk_t HoldDown;
extern unk_t OSResetSW_LastState;
extern unk_t lbl_804D73A8;
extern unk_t lbl_804D73AC;
extern unk_t __OSGetSystemTime();

#pragma push
asm unk_t __OSResetSWInterruptHandler()
{ // clang-format off
    nofralloc
/* 803486E4 003452C4  7C 08 02 A6 */	mflr r0
/* 803486E8 003452C8  90 01 00 04 */	stw r0, 4(r1)
/* 803486EC 003452CC  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 803486F0 003452D0  93 E1 00 24 */	stw r31, 0x24(r1)
/* 803486F4 003452D4  93 C1 00 20 */	stw r30, 0x20(r1)
/* 803486F8 003452D8  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 803486FC 003452DC  48 00 3D 15 */	bl __OSGetSystemTime
/* 80348700 003452E0  3C A0 80 00 */	lis r5, 0x800000F8@ha
/* 80348704 003452E4  90 8D BD 24 */	stw r4, lbl_804D73C4(r13)
/* 80348708 003452E8  80 05 00 F8 */	lwz r0, 0x800000F8@l(r5)
/* 8034870C 003452EC  3C 80 43 1C */	lis r4, 0x431BDE83@ha
/* 80348710 003452F0  38 84 DE 83 */	addi r4, r4, 0x431BDE83@l
/* 80348714 003452F4  90 6D BD 20 */	stw r3, HoldDown(r13)
/* 80348718 003452F8  54 00 F0 BE */	srwi r0, r0, 2
/* 8034871C 003452FC  7C 04 00 16 */	mulhwu r0, r4, r0
/* 80348720 00345300  54 00 8B FE */	srwi r0, r0, 0xf
/* 80348724 00345304  1C 00 00 64 */	mulli r0, r0, 0x64
/* 80348728 00345308  54 1D E8 FE */	srwi r29, r0, 3
/* 8034872C 0034530C  3B C0 00 00 */	li r30, 0
/* 80348730 00345310  3F E0 CC 00 */	lis r31, 0xcc00
lbl_80348734:
/* 80348734 00345314  48 00 3C DD */	bl __OSGetSystemTime
/* 80348738 00345318  80 CD BD 24 */	lwz r6, lbl_804D73C4(r13)
/* 8034873C 0034531C  6F C5 80 00 */	xoris r5, r30, 0x8000
/* 80348740 00345320  80 0D BD 20 */	lwz r0, HoldDown(r13)
/* 80348744 00345324  7C 86 20 10 */	subfc r4, r6, r4
/* 80348748 00345328  7C 00 19 10 */	subfe r0, r0, r3
/* 8034874C 0034532C  6C 03 80 00 */	xoris r3, r0, 0x8000
/* 80348750 00345330  7C 1D 20 10 */	subfc r0, r29, r4
/* 80348754 00345334  7C A5 19 10 */	subfe r5, r5, r3
/* 80348758 00345338  7C A3 19 10 */	subfe r5, r3, r3
/* 8034875C 0034533C  7C A5 00 D1 */	neg. r5, r5
/* 80348760 00345340  41 82 00 10 */	beq lbl_80348770
/* 80348764 00345344  80 1F 30 00 */	lwz r0, 0x3000(r31)
/* 80348768 00345348  54 00 03 DF */	rlwinm. r0, r0, 0, 0xf, 0xf
/* 8034876C 0034534C  41 82 FF C8 */	beq lbl_80348734
lbl_80348770:
/* 80348770 00345350  3C 60 CC 00 */	lis r3, 0xCC003000@ha
/* 80348774 00345354  80 03 30 00 */	lwz r0, 0xCC003000@l(r3)
/* 80348778 00345358  54 00 03 DF */	rlwinm. r0, r0, 0, 0xf, 0xf
/* 8034877C 0034535C  40 82 00 34 */	bne lbl_803487B0
/* 80348780 00345360  38 00 00 01 */	li r0, 1
/* 80348784 00345364  90 0D BD 0C */	stw r0, lbl_804D73AC(r13)
/* 80348788 00345368  38 60 02 00 */	li r3, 0x200
/* 8034878C 0034536C  90 0D BD 10 */	stw r0, OSResetSW_LastState(r13)
/* 80348790 00345370  4B FF EF 9D */	bl __OSMaskInterrupts
/* 80348794 00345374  81 8D BD 08 */	lwz r12, lbl_804D73A8(r13)
/* 80348798 00345378  28 0C 00 00 */	cmplwi r12, 0
/* 8034879C 0034537C  41 82 00 14 */	beq lbl_803487B0
/* 803487A0 00345380  38 00 00 00 */	li r0, 0
/* 803487A4 00345384  7D 88 03 A6 */	mtlr r12
/* 803487A8 00345388  90 0D BD 08 */	stw r0, lbl_804D73A8(r13)
/* 803487AC 0034538C  4E 80 00 21 */	blrl 
lbl_803487B0:
/* 803487B0 00345390  38 00 00 02 */	li r0, 2
/* 803487B4 00345394  3C 60 CC 00 */	lis r3, 0xCC003000@ha
/* 803487B8 00345398  90 03 30 00 */	stw r0, 0xCC003000@l(r3)
/* 803487BC 0034539C  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 803487C0 003453A0  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 803487C4 003453A4  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 803487C8 003453A8  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 803487CC 003453AC  38 21 00 28 */	addi r1, r1, 0x28
/* 803487D0 003453B0  7C 08 03 A6 */	mtlr r0
/* 803487D4 003453B4  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop
