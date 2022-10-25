.include "macros.inc"

.section .text  # 0x80348310 - 0x803486E0

.global OSGetResetCode
OSGetResetCode:
/* 803486B4 00345294  3C 60 80 00 */	lis r3, 0x800030E2@ha
/* 803486B8 00345298  88 03 30 E2 */	lbz r0, 0x800030E2@l(r3)
/* 803486BC 0034529C  28 00 00 00 */	cmplwi r0, 0
/* 803486C0 003452A0  41 82 00 0C */	beq lbl_803486CC
/* 803486C4 003452A4  3C 60 80 00 */	lis r3, 0x8000
/* 803486C8 003452A8  48 00 00 18 */	b lbl_803486E0
lbl_803486CC:
/* 803486CC 003452AC  3C 60 CC 00 */	lis r3, 0xCC003000@ha
/* 803486D0 003452B0  38 63 30 00 */	addi r3, r3, 0xCC003000@l
/* 803486D4 003452B4  80 03 00 24 */	lwz r0, 0x24(r3)
/* 803486D8 003452B8  54 00 00 38 */	rlwinm r0, r0, 0, 0, 0x1c
/* 803486DC 003452BC  54 03 E8 FE */	srwi r3, r0, 3
lbl_803486E0:
/* 803486E0 003452C0  4E 80 00 20 */	blr 


.section .sbss

.global ResetFunctionQueue
ResetFunctionQueue:
	.skip 0x8
