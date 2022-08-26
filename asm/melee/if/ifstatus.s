.include "macros.inc"

.section .text

.global func_802F7220
func_802F7220:
/* 802F7220 002F3E00  7C 08 02 A6 */	mflr r0
/* 802F7224 002F3E04  3C 60 80 40 */	lis r3, lbl_803F9628@ha
/* 802F7228 002F3E08  90 01 00 04 */	stw r0, 4(r1)
/* 802F722C 002F3E0C  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 802F7230 002F3E10  93 E1 00 14 */	stw r31, 0x14(r1)
/* 802F7234 002F3E14  3B E0 00 00 */	li r31, 0
/* 802F7238 002F3E18  93 C1 00 10 */	stw r30, 0x10(r1)
/* 802F723C 002F3E1C  3B C3 96 28 */	addi r30, r3, lbl_803F9628@l
/* 802F7240 002F3E20  93 A1 00 0C */	stw r29, 0xc(r1)
/* 802F7244 002F3E24  3B A0 00 00 */	li r29, 0
lbl_802F7248:
/* 802F7248 002F3E28  80 7E 00 00 */	lwz r3, 0(r30)
/* 802F724C 002F3E2C  28 03 00 00 */	cmplwi r3, 0
/* 802F7250 002F3E30  41 82 00 0C */	beq lbl_802F725C
/* 802F7254 002F3E34  48 09 8F D5 */	bl func_80390228
/* 802F7258 002F3E38  93 FE 00 00 */	stw r31, 0(r30)
lbl_802F725C:
/* 802F725C 002F3E3C  3B BD 00 01 */	addi r29, r29, 1
/* 802F7260 002F3E40  2C 1D 00 08 */	cmpwi r29, 8
/* 802F7264 002F3E44  3B DE 00 28 */	addi r30, r30, 0x28
/* 802F7268 002F3E48  41 80 FF E0 */	blt lbl_802F7248
/* 802F726C 002F3E4C  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 802F7270 002F3E50  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 802F7274 002F3E54  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 802F7278 002F3E58  83 A1 00 0C */	lwz r29, 0xc(r1)
/* 802F727C 002F3E5C  38 21 00 18 */	addi r1, r1, 0x18
/* 802F7280 002F3E60  7C 08 03 A6 */	mtlr r0
/* 802F7284 002F3E64  4E 80 00 20 */	blr 


.section .data
    .balign 8
.global lbl_803F9598
lbl_803F9598:
    .asciz "DmgNum_scene_models"
    .balign 4
.global lbl_803F95AC
lbl_803F95AC:
    .asciz "DmgMrk_scene_models"
    .balign 4
.global lbl_803F95C0
lbl_803F95C0:
    .asciz "translate"
    .balign 4
    .asciz "Error : gobj dont't get (ifAddMark)\n"
    .balign 4
    .asciz "ifstatus.c"
    .balign 4
    .asciz "Error : jobj dont't get (ifAddMark)\n"
    .balign 4
.global lbl_803F9628
lbl_803F9628:
    .4byte NULL
    .4byte NULL
	.4byte lbl_802F74D0
    .4byte 0x0007C860
    .4byte 0x08000000
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
	.4byte lbl_802F73C4
    .4byte 0x0000C351
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
	.4byte lbl_802F74D0
    .4byte 0x0007C85E
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
	.4byte lbl_802F73C4
    .4byte 0x0007C85D
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
	.4byte lbl_802F73C4
    .4byte 0x0007C857
    .4byte 0x0A000000
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
	.4byte lbl_802F74D0
    .4byte 0x0007C855
    .4byte 0x08000000
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
	.4byte lbl_802F74D0
    .4byte 0x00009C48
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
	.4byte lbl_802F74D0
    .4byte 0x00009C46
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x5363496E
    .4byte 0x66436E74
    .4byte 0x5F736365
    .4byte 0x6E655F6D
    .4byte 0x6F64656C
    .4byte 0x73000000


.section .sdata
    .balign 8
.global lbl_804D57A8
lbl_804D57A8:
	.4byte 0xFFFFFFFF
.global lbl_804D57AC
lbl_804D57AC:
    .asciz "P"
    .byte 0x00
    .byte 0xFF
.global lbl_804D57B0
lbl_804D57B0:
    .asciz "jobj.h"
    .balign 4
.global lbl_804D57B8
lbl_804D57B8:
    .asciz "jobj"
    .balign 4
.global lbl_804D57C0
lbl_804D57C0:
    .asciz "0"
    .balign 4


.section .bss, "wa"
    .balign 8
.global lbl_804A10C8
lbl_804A10C8:
	.skip 0x278


.section .sbss
    .balign 8
.global lbl_804D6D60
lbl_804D6D60:
	.skip 0x1
.global lbl_804D6D61
lbl_804D6D61:
	.skip 0x7


.section .sdata2
    .balign 8
.global lbl_804DDA48
lbl_804DDA48:
	.4byte 0x3F800000
.global lbl_804DDA4C
lbl_804DDA4C:
	.4byte 0x00000000
.global lbl_804DDA50
lbl_804DDA50:
	.4byte 0x40000000
	.4byte 0x00000000
.global lbl_804DDA58
lbl_804DDA58:
	.4byte 0x43300000
	.4byte 0x00000000
.global lbl_804DDA60
lbl_804DDA60:
	.4byte 0x43300000
	.4byte 0x80000000
.global lbl_804DDA68
lbl_804DDA68:
	.4byte 0x43960000
.global lbl_804DDA6C
lbl_804DDA6C:
	.4byte 0x42C80000
.global lbl_804DDA70
lbl_804DDA70:
	.4byte 0x3F01C433
.global lbl_804DDA74
lbl_804DDA74:
	.4byte 0x3F1BB98C
.global lbl_804DDA78
lbl_804DDA78:
	.4byte 0x3E9BB2FF
.global lbl_804DDA7C
lbl_804DDA7C:
	.4byte 0x3F9BB646
.global lbl_804DDA80
lbl_804DDA80:
	.4byte 0x3F4F9DB2
.global lbl_804DDA84
lbl_804DDA84:
	.4byte 0x3DCFAACE
.global lbl_804DDA88
lbl_804DDA88:
	.4byte 0x3FC2A64C
.global lbl_804DDA8C
lbl_804DDA8C:
	.4byte 0xC2C80000
.global lbl_804DDA90
lbl_804DDA90:
	.4byte 0x3E4FAACE
.global lbl_804DDA94
lbl_804DDA94:
	.4byte 0x3F000000
.global lbl_804DDA98
lbl_804DDA98:
	.4byte 0x3F266666
.global lbl_804DDA9C
lbl_804DDA9C:
	.4byte 0x3DCCCCCD
.global lbl_804DDAA0
lbl_804DDAA0:
	.4byte 0x3E800000
	.4byte 0x00000000
.global lbl_804DDAA8
lbl_804DDAA8:
	.4byte 0x00000000
	.4byte 0x00000000
