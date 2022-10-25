.include "macros.inc"

.section .text  # 0x803486E4 - 0x80348A8C

.global OSGetResetSwitchState
OSGetResetSwitchState:
/* 80348A70 00345650  7C 08 02 A6 */	mflr r0
/* 80348A74 00345654  90 01 00 04 */	stw r0, 4(r1)
/* 80348A78 00345658  94 21 FF F8 */	stwu r1, -8(r1)
/* 80348A7C 0034565C  4B FF FD 5D */	bl OSGetResetButtonState
/* 80348A80 00345660  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80348A84 00345664  38 21 00 08 */	addi r1, r1, 8
/* 80348A88 00345668  7C 08 03 A6 */	mtlr r0
/* 80348A8C 0034566C  4E 80 00 20 */	blr 


.section .sbss

.global lbl_804D73A8
lbl_804D73A8:
	.skip 0x4
.global lbl_804D73AC
lbl_804D73AC:
	.skip 0x4
.global OSResetSW_LastState
OSResetSW_LastState:
	.skip 0x8
.global HoldUp
HoldUp:
	.skip 0x4
.global lbl_804D73BC
lbl_804D73BC:
	.skip 0x4
.global HoldDown
HoldDown:
	.skip 0x4
.global lbl_804D73C4
lbl_804D73C4:
	.skip 0x4
