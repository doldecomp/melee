.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240

.global lbl_8014222C
lbl_8014222C:
/* 8014222C 0013EE0C  7C 08 02 A6 */	mflr r0
/* 80142230 0013EE10  38 80 00 00 */	li r4, 0
/* 80142234 0013EE14  90 01 00 04 */	stw r0, 4(r1)
/* 80142238 0013EE18  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8014223C 0013EE1C  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80142240 0013EE20  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80142244 0013EE24  C8 22 A2 60 */	lfd f1, lbl_804D9C40@sda21(r2)
/* 80142248 0013EE28  C0 1F 00 2C */	lfs f0, 0x2c(r31)
/* 8014224C 0013EE2C  7F E3 FB 78 */	mr r3, r31
/* 80142250 0013EE30  FC 21 00 32 */	fmul f1, f1, f0
/* 80142254 0013EE34  FC 20 08 18 */	frsp f1, f1
/* 80142258 0013EE38  4B F3 38 99 */	bl func_80075AF0
/* 8014225C 0013EE3C  C0 1F 00 80 */	lfs f0, 0x80(r31)
/* 80142260 0013EE40  FC 00 00 50 */	fneg f0, f0
/* 80142264 0013EE44  D0 1F 00 80 */	stfs f0, 0x80(r31)
/* 80142268 0013EE48  C0 1F 00 EC */	lfs f0, 0xec(r31)
/* 8014226C 0013EE4C  FC 00 00 50 */	fneg f0, f0
/* 80142270 0013EE50  D0 1F 00 EC */	stfs f0, 0xec(r31)
/* 80142274 0013EE54  C0 1F 00 E4 */	lfs f0, 0xe4(r31)
/* 80142278 0013EE58  FC 00 00 50 */	fneg f0, f0
/* 8014227C 0013EE5C  D0 1F 00 E4 */	stfs f0, 0xe4(r31)
/* 80142280 0013EE60  C0 1F 23 50 */	lfs f0, 0x2350(r31)
/* 80142284 0013EE64  FC 00 00 50 */	fneg f0, f0
/* 80142288 0013EE68  D0 1F 23 50 */	stfs f0, 0x2350(r31)
/* 8014228C 0013EE6C  C0 1F 23 54 */	lfs f0, 0x2354(r31)
/* 80142290 0013EE70  FC 00 00 50 */	fneg f0, f0
/* 80142294 0013EE74  D0 1F 23 54 */	stfs f0, 0x2354(r31)
/* 80142298 0013EE78  C0 1F 23 58 */	lfs f0, 0x2358(r31)
/* 8014229C 0013EE7C  FC 00 00 50 */	fneg f0, f0
/* 801422A0 0013EE80  D0 1F 23 58 */	stfs f0, 0x2358(r31)
/* 801422A4 0013EE84  C0 1F 23 5C */	lfs f0, 0x235c(r31)
/* 801422A8 0013EE88  FC 00 00 50 */	fneg f0, f0
/* 801422AC 0013EE8C  D0 1F 23 5C */	stfs f0, 0x235c(r31)
/* 801422B0 0013EE90  C0 1F 23 60 */	lfs f0, 0x2360(r31)
/* 801422B4 0013EE94  FC 00 00 50 */	fneg f0, f0
/* 801422B8 0013EE98  D0 1F 23 60 */	stfs f0, 0x2360(r31)
/* 801422BC 0013EE9C  C0 1F 23 74 */	lfs f0, 0x2374(r31)
/* 801422C0 0013EEA0  FC 00 00 50 */	fneg f0, f0
/* 801422C4 0013EEA4  D0 1F 23 74 */	stfs f0, 0x2374(r31)
/* 801422C8 0013EEA8  C0 1F 23 78 */	lfs f0, 0x2378(r31)
/* 801422CC 0013EEAC  FC 00 00 50 */	fneg f0, f0
/* 801422D0 0013EEB0  D0 1F 23 78 */	stfs f0, 0x2378(r31)
/* 801422D4 0013EEB4  80 01 00 24 */	lwz r0, 0x24(r1)
/* 801422D8 0013EEB8  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 801422DC 0013EEBC  38 21 00 20 */	addi r1, r1, 0x20
/* 801422E0 0013EEC0  7C 08 03 A6 */	mtlr r0
/* 801422E4 0013EEC4  4E 80 00 20 */	blr 

.section .data
    .balign 8

.global as_table_purin
as_table_purin:
    .4byte 0x00000127
    .4byte NULL
    .4byte 0x01000000
    .4byte func_800D7590
    .4byte func_800D7614
    .4byte func_800D7634
    .4byte func_800D767C
    .4byte func_800761C8
    .4byte 0x00000128
    .4byte NULL
    .4byte 0x01000000
    .4byte func_800D7590
    .4byte func_800D7614
    .4byte func_800D7634
    .4byte func_800D767C
    .4byte func_800761C8
    .4byte 0x00000129
    .4byte NULL
    .4byte 0x01000000
    .4byte func_800D7590
    .4byte func_800D7614
    .4byte func_800D7634
    .4byte func_800D767C
    .4byte func_800761C8
    .4byte 0x0000012A
    .4byte NULL
    .4byte 0x01000000
    .4byte func_800D7590
    .4byte func_800D7614
    .4byte func_800D7634
    .4byte func_800D767C
    .4byte func_800761C8
    .4byte 0x0000012B
    .4byte NULL
    .4byte 0x01000000
    .4byte func_800D7590
    .4byte func_800D7614
    .4byte func_800D7634
    .4byte func_800D767C
    .4byte func_800761C8
    .4byte 0x0000012C
    .4byte 0x00340211
    .4byte 0x12000000
    .4byte lbl_8013E014
    .4byte lbl_8013FF00
    .4byte lbl_80140620
    .4byte lbl_80140FA4
    .4byte func_800761C8
    .4byte 0x0000012D
    .4byte 0x00340211
    .4byte 0x12000000
    .4byte lbl_8013E014
    .4byte lbl_8013FF00
    .4byte lbl_80140620
    .4byte lbl_80140FA4
    .4byte func_800761C8
    .4byte 0x0000012E
    .4byte 0x003C0211
    .4byte 0x12000000
    .4byte lbl_8013E0F0
    .4byte lbl_8013FF04
    .4byte lbl_80140650
    .4byte lbl_80141054
    .4byte func_800761C8
    .4byte 0x0000012F
    .4byte 0x003C0211
    .4byte 0x12000000
    .4byte lbl_8013E2A0
    .4byte lbl_80140064
    .4byte lbl_80140680
    .4byte lbl_80141154
    .4byte func_800761C8
    .4byte 0x00000130
    .4byte 0x00340211
    .4byte 0x12000000
    .4byte lbl_8013E410
    .4byte lbl_801401C4
    .4byte lbl_801406B0
    .4byte lbl_80141254
    .4byte func_800761C8
    .4byte 0x00000131
    .4byte 0x00340211
    .4byte 0x12000000
    .4byte lbl_8013E7E0
    .4byte lbl_80140344
    .4byte lbl_801408B8
    .4byte lbl_801415F4
    .4byte func_800761C8
    .4byte 0x00000132
    .4byte 0x00340211
    .4byte 0x12000000
    .4byte lbl_8013EAD8
    .4byte lbl_80140348
    .4byte lbl_80140BAC
    .4byte lbl_801416D0
    .4byte func_800761C8
    .4byte 0x00000133
    .4byte 0x00340211
    .4byte 0x12000000
    .4byte lbl_8013EAD8
    .4byte lbl_80140348
    .4byte lbl_80140BAC
    .4byte lbl_801416D0
    .4byte func_800761C8
    .4byte 0x00000134
    .4byte 0x00340611
    .4byte 0x12000000
    .4byte lbl_8013EDB0
    .4byte lbl_8014034C
    .4byte lbl_80140BE8
    .4byte lbl_80141730
    .4byte func_800761C8
    .4byte 0x00000135
    .4byte 0x00340611
    .4byte 0x12000000
    .4byte lbl_8013EDB0
    .4byte lbl_8014034C
    .4byte lbl_80140BE8
    .4byte lbl_80141730
    .4byte func_800761C8
    .4byte 0x00000136
    .4byte 0x003C0611
    .4byte 0x12000000
    .4byte lbl_8013EE84
    .4byte lbl_80140350
    .4byte lbl_80140C18
    .4byte lbl_801417E0
    .4byte func_800761C8
    .4byte 0x00000137
    .4byte 0x003C0611
    .4byte 0x12000000
    .4byte lbl_8013F034
    .4byte lbl_801404B0
    .4byte lbl_80140C48
    .4byte lbl_801418E0
    .4byte func_800761C8
    .4byte 0x00000138
    .4byte 0x00340611
    .4byte 0x12000000
    .4byte lbl_8013F1A4
    .4byte lbl_80140610
    .4byte lbl_80140C78
    .4byte lbl_801419E0
    .4byte func_800761C8
    .4byte 0x00000139
    .4byte 0x00340211
    .4byte 0x12000000
    .4byte lbl_8013F708
    .4byte lbl_80140614
    .4byte lbl_80140DF8
    .4byte lbl_80141FB8
    .4byte func_800761C8
    .4byte 0x0000013A
    .4byte 0x00340611
    .4byte 0x12000000
    .4byte lbl_8013F9C0
    .4byte lbl_80140618
    .4byte lbl_80140F10
    .4byte lbl_80142070
    .4byte func_800761C8
    .4byte 0x0000013B
    .4byte 0x00340611
    .4byte 0x12000000
    .4byte lbl_8013F9C0
    .4byte lbl_80140618
    .4byte lbl_80140F10
    .4byte lbl_80142070
    .4byte func_800761C8
    .4byte 0x0000013C
    .4byte 0x00340611
    .4byte 0x12000000
    .4byte lbl_8013FCAC
    .4byte lbl_8014061C
    .4byte lbl_80140F40
    .4byte lbl_801420D0
    .4byte func_800761C8
    .4byte 0x0000013D
    .4byte 0x00340212
    .4byte 0x13000000
    .4byte lbl_8013D30C
    .4byte lbl_8013D384
    .4byte lbl_8013D38C
    .4byte lbl_8013D518
    .4byte func_800761C8
    .4byte 0x0000013E
    .4byte 0x00340612
    .4byte 0x13000000
    .4byte lbl_8013D348
    .4byte lbl_8013D388
    .4byte lbl_8013D3AC
    .4byte lbl_8013D554
    .4byte func_800761C8
    .4byte 0x0000013F
    .4byte 0x00340013
    .4byte 0x14000000
    .4byte lbl_8013CB68
    .4byte lbl_8013CC60
    .4byte lbl_8013CC68
    .4byte lbl_8013CCA8
    .4byte func_800761C8
    .4byte 0x00000140
    .4byte 0x00340413
    .4byte 0x14000000
    .4byte lbl_8013CBE4
    .4byte lbl_8013CC64
    .4byte lbl_8013CC88
    .4byte lbl_8013CCE4
    .4byte func_800761C8
    .4byte 0x00000141
    .4byte 0x00340013
    .4byte 0x14000000
    .4byte lbl_8013CB68
    .4byte lbl_8013CC60
    .4byte lbl_8013CC68
    .4byte lbl_8013CCA8
    .4byte func_800761C8
    .4byte 0x00000142
    .4byte 0x00340413
    .4byte 0x14000000
    .4byte lbl_8013CBE4
    .4byte lbl_8013CC64
    .4byte lbl_8013CC88
    .4byte lbl_8013CCE4
    .4byte func_800761C8
    .4byte 0x00000143
    .4byte 0x00340014
    .4byte 0x15000000
    .4byte lbl_8013CFCC
    .4byte lbl_8013D044
    .4byte lbl_8013D04C
    .4byte lbl_8013D08C
    .4byte func_800761C8
    .4byte 0x00000144
    .4byte 0x00340414
    .4byte 0x15000000
    .4byte lbl_8013D008
    .4byte lbl_8013D048
    .4byte lbl_8013D06C
    .4byte lbl_8013D0C8
    .4byte func_800761C8
    .4byte 0x00000145
    .4byte 0x00340014
    .4byte 0x15000000
    .4byte lbl_8013CFCC
    .4byte lbl_8013D044
    .4byte lbl_8013D04C
    .4byte lbl_8013D08C
    .4byte func_800761C8
    .4byte 0x00000146
    .4byte 0x00340414
    .4byte 0x15000000
    .4byte lbl_8013D008
    .4byte lbl_8013D048
    .4byte lbl_8013D06C
    .4byte lbl_8013D0C8
    .4byte func_800761C8

.global lbl_803D02F0
lbl_803D02F0:
    .asciz "PlPr.dat"
    .balign 4

.global lbl_803D02FC
lbl_803D02FC:
    .asciz "ftDataPurin"
    .balign 4

.global lbl_803D0308
lbl_803D0308:
    .asciz "PlPrNr.dat"
    .balign 4

.global lbl_803D0314
lbl_803D0314:
    .asciz "PlyPurin5K_Share_joint"
    .balign 4

.global lbl_803D032C
lbl_803D032C:
    .asciz "PlyPurin5K_Share_matanim_joint"
    .balign 4

.global lbl_803D034C
lbl_803D034C:
    .asciz "PlPrRe.dat"
    .balign 4

.global lbl_803D0358
lbl_803D0358:
    .asciz "PlyPurin5KRe_Share_joint"
    .balign 4

.global lbl_803D0374
lbl_803D0374:
    .asciz "PlyPurin5KRe_Share_matanim_joint"
    .balign 4

.global lbl_803D0398
lbl_803D0398:
    .asciz "PlPrBu.dat"
    .balign 4

.global lbl_803D03A4
lbl_803D03A4:
    .asciz "PlyPurin5KBu_Share_joint"
    .balign 4

.global lbl_803D03C0
lbl_803D03C0:
    .asciz "PlyPurin5KBu_Share_matanim_joint"
    .balign 4

.global lbl_803D03E4
lbl_803D03E4:
    .asciz "PlPrGr.dat"
    .balign 4

.global lbl_803D03F0
lbl_803D03F0:
    .asciz "PlyPurin5KGr_Share_joint"
    .balign 4

.global lbl_803D040C
lbl_803D040C:
    .asciz "PlyPurin5KGr_Share_matanim_joint"
    .balign 4

.global lbl_803D0430
lbl_803D0430:
    .asciz "PlPrYe.dat"
    .balign 4

.global lbl_803D043C
lbl_803D043C:
    .asciz "PlyPurin5KYe_Share_joint"
    .balign 4

.global lbl_803D0458
lbl_803D0458:
    .asciz "PlyPurin5KYe_Share_matanim_joint"
    .balign 4

.global lbl_803D047C
lbl_803D047C:
    .asciz "PlPrAJ.dat"
    .balign 4

.global lbl_803D0488
lbl_803D0488:
    .asciz "ftDemoResultMotionFilePurin"
    .balign 4

.global lbl_803D04A4
lbl_803D04A4:
    .asciz "ftDemoIntroMotionFilePurin"
    .balign 4

.global lbl_803D04C0
lbl_803D04C0:
    .asciz "ftDemoEndingMotionFilePurin"
    .balign 4

.global lbl_803D04DC
lbl_803D04DC:
    .asciz "ftDemoViWaitMotionFilePurin"
    .balign 4

.global lbl_803D04F8
lbl_803D04F8:
    .4byte lbl_803D0488
    .4byte lbl_803D04A4
    .4byte lbl_803D04C0
    .4byte lbl_803D04DC

.global lbl_803D0508
lbl_803D0508:
    .4byte lbl_803D0308
    .4byte lbl_803D0314
    .4byte lbl_803D032C
    .4byte lbl_803D034C
    .4byte lbl_803D0358
    .4byte lbl_803D0374
    .4byte lbl_803D0398
    .4byte lbl_803D03A4
    .4byte lbl_803D03C0
    .4byte lbl_803D03E4
    .4byte lbl_803D03F0
    .4byte lbl_803D040C
    .4byte lbl_803D0430
    .4byte lbl_803D043C
    .4byte lbl_803D0458

.global lbl_803D0544
lbl_803D0544:
    .asciz "PlyPurinReHat_TopN_joint"
    .balign 4

.global lbl_803D0560
lbl_803D0560:
    .asciz "PlyPurinBuHat_TopN_joint"
    .balign 4

.global lbl_803D057C
lbl_803D057C:
    .asciz "PlyPurinGrHat_TopN_joint"
    .balign 4

.global lbl_803D0598
lbl_803D0598:
    .asciz "PlyPurinYeHat_TopN_joint"
    .balign 4

.global lbl_803D05B4
lbl_803D05B4:
    .4byte NULL
    .4byte lbl_803D0544
    .4byte lbl_803D0560
    .4byte lbl_803D057C
    .4byte lbl_803D0598

.global lbl_803D05C8
lbl_803D05C8:
    .4byte 0x3F266666
    .4byte 0x3F333333
    .4byte 0x3F4CCCCD
    .4byte 0x3F800000

.global lbl_803D05D8
lbl_803D05D8:
    .4byte 0x3F8CCCCD
    .4byte 0x3FACCCCD
    .4byte 0x3FA66666
    .4byte 0x3F99999A
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4

.global lbl_803D0610
lbl_803D0610:
    .4byte 0x41000000
    .4byte NULL
    .4byte 0xC0800000
    .4byte 0x40800000
    .4byte 0x40800000
    .4byte 0x40800000


.section .sdata
    .balign 8


.global lbl_804D3E98
lbl_804D3E98:
    .asciz "jobj.h"
    .balign 4

.global lbl_804D3EA0
lbl_804D3EA0:
    .asciz "jobj"
    .balign 4

.global lbl_804D3EA8
lbl_804D3EA8:
    .asciz "scale"
    .balign 4


.section .sdata2
    .balign 8


.global lbl_804D9C10
lbl_804D9C10:
	.4byte 0xBF800000

.global lbl_804D9C14
lbl_804D9C14:
	.4byte 0x00000000

.global lbl_804D9C18
lbl_804D9C18:
	.4byte 0x3F800000
	.4byte 0x00000000

.global lbl_804D9C20
lbl_804D9C20:
	.4byte 0xBF800000

.global lbl_804D9C24
lbl_804D9C24:
	.4byte 0x00000000

.global lbl_804D9C28
lbl_804D9C28:
	.4byte 0x3F800000
	.4byte 0x00000000

.global lbl_804D9C30
lbl_804D9C30:
	.4byte 0x00000000

.global lbl_804D9C34
lbl_804D9C34:
	.4byte 0x3C8EFA35

.global lbl_804D9C38
lbl_804D9C38:
	.4byte 0x3F800000
	.4byte 0x00000000

.global lbl_804D9C40
lbl_804D9C40:
	.4byte 0x3FF921FB
	.4byte 0x54442D18

.global lbl_804D9C48
lbl_804D9C48:
	.4byte 0x00000000

.global lbl_804D9C4C
lbl_804D9C4C:
	.4byte 0x3FC90FDB

.global lbl_804D9C50
lbl_804D9C50:
	.4byte 0x3F800000

.global lbl_804D9C54
lbl_804D9C54:
	.4byte 0x3F000000

.global lbl_804D9C58
lbl_804D9C58:
	.4byte 0x401921FB
	.4byte 0x54442D18

.global lbl_804D9C60
lbl_804D9C60:
	.4byte 0xBF800000

.global lbl_804D9C64
lbl_804D9C64:
	.4byte 0x38D1B717

.global lbl_804D9C68
lbl_804D9C68:
	.4byte 0x3C8EFA35
	.4byte 0x00000000

.global lbl_804D9C70
lbl_804D9C70:
	.4byte 0x43300000
	.4byte 0x80000000

.global lbl_804D9C78
lbl_804D9C78:
	.4byte 0x3FC99999
	.4byte 0x9999999A

.global lbl_804D9C80
lbl_804D9C80:
	.4byte 0x4012D97C
	.4byte 0x7F3321D2

.global lbl_804D9C88
lbl_804D9C88:
	.4byte 0x400921FB
	.4byte 0x54442D18

.global lbl_804D9C90
lbl_804D9C90:
	.4byte 0xBD4CCCCD
	.4byte 0x00000000
