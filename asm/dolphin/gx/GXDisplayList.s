.include "macros.inc"

.section .text

# https://decomp.me/scratch/HEw0V
.global GXCallDisplayList
GXCallDisplayList:
/* 803410D8 0033DCB8  7C 08 02 A6 */	mflr r0
/* 803410DC 0033DCBC  90 01 00 04 */	stw r0, 4(r1)
/* 803410E0 0033DCC0  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 803410E4 0033DCC4  93 E1 00 14 */	stw r31, 0x14(r1)
/* 803410E8 0033DCC8  3B E4 00 00 */	addi r31, r4, 0
/* 803410EC 0033DCCC  93 C1 00 10 */	stw r30, 0x10(r1)
/* 803410F0 0033DCD0  3B C3 00 00 */	addi r30, r3, 0
/* 803410F4 0033DCD4  80 AD A5 08 */	lwz r5, __GXContexts@sda21(r13)
/* 803410F8 0033DCD8  80 05 04 F0 */	lwz r0, 0x4f0(r5)
/* 803410FC 0033DCDC  28 00 00 00 */	cmplwi r0, 0
/* 80341100 0033DCE0  41 82 00 08 */	beq lbl_80341108
/* 80341104 0033DCE4  4B FF BF 4D */	bl __GXSetDirtyState
lbl_80341108:
/* 80341108 0033DCE8  80 6D A5 08 */	lwz r3, __GXContexts@sda21(r13)
/* 8034110C 0033DCEC  80 03 00 00 */	lwz r0, 0(r3)
/* 80341110 0033DCF0  28 00 00 00 */	cmplwi r0, 0
/* 80341114 0033DCF4  40 82 00 08 */	bne lbl_8034111C
/* 80341118 0033DCF8  4B FF C0 A1 */	bl __GXSendFlushPrim
lbl_8034111C:
/* 8034111C 0033DCFC  38 00 00 40 */	li r0, 0x40
/* 80341120 0033DD00  3C 60 CC 01 */	lis r3, 0xCC008000@ha
/* 80341124 0033DD04  98 03 80 00 */	stb r0, 0xCC008000@l(r3)
/* 80341128 0033DD08  93 C3 80 00 */	stw r30, -0x8000(r3)
/* 8034112C 0033DD0C  93 E3 80 00 */	stw r31, -0x8000(r3)
/* 80341130 0033DD10  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80341134 0033DD14  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80341138 0033DD18  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8034113C 0033DD1C  38 21 00 18 */	addi r1, r1, 0x18
/* 80341140 0033DD20  7C 08 03 A6 */	mtlr r0
/* 80341144 0033DD24  4E 80 00 20 */	blr 
