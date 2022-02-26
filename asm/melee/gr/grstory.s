.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240
.set lbl_804DB274, 0x804DB274
.set lbl_804DB278, 0x804DB278
.set _SDA2_BASE_, 0x804DF9E0

.global lbl_801E36D0
lbl_801E36D0:
/* 801E36D0 001E02B0  38 60 00 00 */	li r3, 0
/* 801E36D4 001E02B4  4E 80 00 20 */	blr 
.global lbl_801E36D8
lbl_801E36D8:
/* 801E36D8 001E02B8  7C 08 02 A6 */	mflr r0
/* 801E36DC 001E02BC  38 80 00 00 */	li r4, 0
/* 801E36E0 001E02C0  90 01 00 04 */	stw r0, 4(r1)
/* 801E36E4 001E02C4  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 801E36E8 001E02C8  93 E1 00 24 */	stw r31, 0x24(r1)
/* 801E36EC 001E02CC  3B E3 00 00 */	addi r31, r3, 0
/* 801E36F0 001E02D0  38 65 00 00 */	addi r3, r5, 0
/* 801E36F4 001E02D4  38 A1 00 14 */	addi r5, r1, 0x14
/* 801E36F8 001E02D8  4B E2 7A D5 */	bl func_8000B1CC
/* 801E36FC 001E02DC  C0 42 B8 94 */	lfs f2, lbl_804DB274-_SDA2_BASE_(r2)
/* 801E3700 001E02E0  C0 3F 00 04 */	lfs f1, 4(r31)
/* 801E3704 001E02E4  C0 01 00 18 */	lfs f0, 0x18(r1)
/* 801E3708 001E02E8  EC 22 08 2A */	fadds f1, f2, f1
/* 801E370C 001E02EC  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 801E3710 001E02F0  40 81 00 0C */	ble lbl_801E371C
/* 801E3714 001E02F4  38 60 00 01 */	li r3, 1
/* 801E3718 001E02F8  48 00 00 08 */	b lbl_801E3720
lbl_801E371C:
/* 801E371C 001E02FC  38 60 00 00 */	li r3, 0
lbl_801E3720:
/* 801E3720 001E0300  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 801E3724 001E0304  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 801E3728 001E0308  38 21 00 28 */	addi r1, r1, 0x28
/* 801E372C 001E030C  7C 08 03 A6 */	mtlr r0
/* 801E3730 001E0310  4E 80 00 20 */	blr 


.section .data
    .balign 8
.global lbl_803E26F0
lbl_803E26F0:
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
	.4byte lbl_801E31C0
	.4byte lbl_801E3224
	.4byte lbl_801E322C
	.4byte lbl_801E3230
    .4byte NULL
	.4byte lbl_801E3370
	.4byte lbl_801E33D8
	.4byte lbl_801E33E0
	.4byte lbl_801E3414
    .4byte NULL
	.4byte lbl_801E3234
	.4byte lbl_801E332C
	.4byte lbl_801E3334
	.4byte lbl_801E336C
    .4byte 0xC0000000
.global lbl_803E2740
lbl_803E2740:
    .4byte 0x2F477253
    .4byte 0x742E6461
    .4byte 0x74000000
.global lbl_803E274C
lbl_803E274C:
    .4byte 0x0000000A
    .4byte lbl_803E26F0
    .4byte lbl_803E2740
	.4byte func_801E3030
	.4byte func_801E302C
	.4byte lbl_801E30A8
	.4byte lbl_801E30AC
	.4byte lbl_801E30D0
	.4byte lbl_801E36D0
	.4byte lbl_801E36D8
    .4byte 0x00000001
    .4byte NULL
    .4byte NULL
    .4byte 0x25733A25
    .4byte 0x643A2063
    .4byte 0x6F756C64
    .4byte 0x6E207420
    .4byte 0x67657420
    .4byte 0x676F626A
    .4byte 0x2869643D
    .4byte 0x2564290A
    .4byte NULL
    .4byte 0x67727374
    .4byte 0x6F72792E
    .4byte 0x63000000
    .4byte 0xC3920000
    .4byte 0x42D20000
    .4byte 0xC3920000
    .4byte 0x42960000
    .4byte 0xC3920000
    .4byte 0x42480000
    .4byte 0x43980000
    .4byte 0x42DC0000
    .4byte 0x43980000
    .4byte 0x42B40000
    .4byte NULL
    .4byte NULL
