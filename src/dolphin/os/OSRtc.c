#include <dolphin/types.h>

extern unk_t lbl_804A7D60;
extern unk_t WriteSram();

#pragma push
asm unk_t WriteSramCallback()
{ // clang-format off
    nofralloc
/* 80348A90 00345670  7C 08 02 A6 */	mflr r0
/* 80348A94 00345674  3C 60 80 4A */	lis r3, lbl_804A7D60@ha
/* 80348A98 00345678  90 01 00 04 */	stw r0, 4(r1)
/* 80348A9C 0034567C  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80348AA0 00345680  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80348AA4 00345684  3B E3 7D 60 */	addi r31, r3, lbl_804A7D60@l
/* 80348AA8 00345688  93 C1 00 10 */	stw r30, 0x10(r1)
/* 80348AAC 0034568C  3B DF 00 40 */	addi r30, r31, 0x40
/* 80348AB0 00345690  80 9F 00 40 */	lwz r4, 0x40(r31)
/* 80348AB4 00345694  7C 7F 22 14 */	add r3, r31, r4
/* 80348AB8 00345698  20 A4 00 40 */	subfic r5, r4, 0x40
/* 80348ABC 0034569C  48 00 00 35 */	bl WriteSram
/* 80348AC0 003456A0  90 7F 00 4C */	stw r3, 0x4c(r31)
/* 80348AC4 003456A4  80 1F 00 4C */	lwz r0, 0x4c(r31)
/* 80348AC8 003456A8  2C 00 00 00 */	cmpwi r0, 0
/* 80348ACC 003456AC  41 82 00 0C */	beq lbl_80348AD8
/* 80348AD0 003456B0  38 00 00 40 */	li r0, 0x40
/* 80348AD4 003456B4  90 1E 00 00 */	stw r0, 0(r30)
lbl_80348AD8:
/* 80348AD8 003456B8  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80348ADC 003456BC  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80348AE0 003456C0  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 80348AE4 003456C4  7C 08 03 A6 */	mtlr r0
/* 80348AE8 003456C8  38 21 00 18 */	addi r1, r1, 0x18
/* 80348AEC 003456CC  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop
