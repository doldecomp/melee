.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240

.global func_800E2778
func_800E2778:
/* 800E2778 000DF358  7C 08 02 A6 */	mflr r0
/* 800E277C 000DF35C  90 01 00 04 */	stw r0, 4(r1)
/* 800E2780 000DF360  94 21 FF B8 */	stwu r1, -0x48(r1)
/* 800E2784 000DF364  BF 61 00 34 */	stmw r27, 0x34(r1)
/* 800E2788 000DF368  3B 63 00 00 */	addi r27, r3, 0
/* 800E278C 000DF36C  3C 60 80 3C */	lis r3, lbl_803C72A0@ha
/* 800E2790 000DF370  38 83 72 A0 */	addi r4, r3, lbl_803C72A0@l
/* 800E2794 000DF374  38 7B 00 00 */	addi r3, r27, 0
/* 800E2798 000DF378  83 9B 00 2C */	lwz r28, 0x2c(r27)
/* 800E279C 000DF37C  4B F9 FD 05 */	bl func_800824A0
/* 800E27A0 000DF380  2C 03 00 00 */	cmpwi r3, 0
/* 800E27A4 000DF384  41 82 00 78 */	beq lbl_800E281C
/* 800E27A8 000DF388  83 BB 00 2C */	lwz r29, 0x2c(r27)
/* 800E27AC 000DF38C  3B E0 00 00 */	li r31, 0
/* 800E27B0 000DF390  83 DD 02 D4 */	lwz r30, 0x2d4(r29)
/* 800E27B4 000DF394  7F A3 EB 78 */	mr r3, r29
/* 800E27B8 000DF398  93 FD 22 08 */	stw r31, 0x2208(r29)
/* 800E27BC 000DF39C  4B F9 B0 41 */	bl func_8007D7FC
/* 800E27C0 000DF3A0  C0 62 98 00 */	lfs f3, lbl_804D91E0@sda21(r2)
/* 800E27C4 000DF3A4  3C 80 0C 4C */	lis r4, 0x0C4C508A@ha
/* 800E27C8 000DF3A8  38 A4 50 8A */	addi r5, r4, 0x0C4C508A@l
/* 800E27CC 000DF3AC  D0 7D 00 84 */	stfs f3, 0x84(r29)
/* 800E27D0 000DF3B0  38 7B 00 00 */	addi r3, r27, 0
/* 800E27D4 000DF3B4  38 80 01 5D */	li r4, 0x15d
/* 800E27D8 000DF3B8  93 FD 22 34 */	stw r31, 0x2234(r29)
/* 800E27DC 000DF3BC  38 C0 00 00 */	li r6, 0
/* 800E27E0 000DF3C0  C0 3D 08 94 */	lfs f1, 0x894(r29)
/* 800E27E4 000DF3C4  C0 42 98 04 */	lfs f2, lbl_804D91E4@sda21(r2)
/* 800E27E8 000DF3C8  4B F8 6B C5 */	bl Fighter_ActionStateChange_800693AC
/* 800E27EC 000DF3CC  7F A3 EB 78 */	mr r3, r29
/* 800E27F0 000DF3D0  C0 3E 00 3C */	lfs f1, 0x3c(r30)
/* 800E27F4 000DF3D4  4B F9 A4 85 */	bl func_8007CC78
/* 800E27F8 000DF3D8  3C 60 80 06 */	lis r3, efLib_PauseAll@ha
/* 800E27FC 000DF3DC  38 03 BA 40 */	addi r0, r3, efLib_PauseAll@l
/* 800E2800 000DF3E0  3C 60 80 06 */	lis r3, efLib_ResumeAll@ha
/* 800E2804 000DF3E4  90 1D 21 D4 */	stw r0, 0x21d4(r29)
/* 800E2808 000DF3E8  38 03 BA C4 */	addi r0, r3, efLib_ResumeAll@l
/* 800E280C 000DF3EC  90 1D 21 D8 */	stw r0, 0x21d8(r29)
/* 800E2810 000DF3F0  38 00 00 01 */	li r0, 1
/* 800E2814 000DF3F4  90 1C 23 4C */	stw r0, 0x234c(r28)
/* 800E2818 000DF3F8  48 00 00 0C */	b lbl_800E2824
lbl_800E281C:
/* 800E281C 000DF3FC  38 00 00 00 */	li r0, 0
/* 800E2820 000DF400  90 1C 23 4C */	stw r0, 0x234c(r28)
lbl_800E2824:
/* 800E2824 000DF404  83 BB 00 2C */	lwz r29, 0x2c(r27)
/* 800E2828 000DF408  80 1D 22 0C */	lwz r0, 0x220c(r29)
/* 800E282C 000DF40C  28 00 00 00 */	cmplwi r0, 0
/* 800E2830 000DF410  41 82 00 34 */	beq lbl_800E2864
/* 800E2834 000DF414  80 1D 23 4C */	lwz r0, 0x234c(r29)
/* 800E2838 000DF418  2C 00 00 00 */	cmpwi r0, 0
/* 800E283C 000DF41C  41 82 00 28 */	beq lbl_800E2864
/* 800E2840 000DF420  C0 3D 08 44 */	lfs f1, 0x844(r29)
/* 800E2844 000DF424  C0 5D 08 48 */	lfs f2, 0x848(r29)
/* 800E2848 000DF428  4B F4 03 E9 */	bl func_someCalcAngle_80022C30
/* 800E284C 000DF42C  C0 1D 00 2C */	lfs f0, 0x2c(r29)
/* 800E2850 000DF430  38 7D 00 00 */	addi r3, r29, 0
/* 800E2854 000DF434  38 80 00 00 */	li r4, 0
/* 800E2858 000DF438  EC 20 00 72 */	fmuls f1, f0, f1
/* 800E285C 000DF43C  4B F9 30 D1 */	bl func_8007592C
/* 800E2860 000DF440  48 00 00 14 */	b lbl_800E2874
lbl_800E2864:
/* 800E2864 000DF444  C0 22 98 00 */	lfs f1, lbl_804D91E0@sda21(r2)
/* 800E2868 000DF448  38 7D 00 00 */	addi r3, r29, 0
/* 800E286C 000DF44C  38 80 00 00 */	li r4, 0
/* 800E2870 000DF450  4B F9 30 BD */	bl func_8007592C
lbl_800E2874:
/* 800E2874 000DF454  BB 61 00 34 */	lmw r27, 0x34(r1)
/* 800E2878 000DF458  80 01 00 4C */	lwz r0, 0x4c(r1)
/* 800E287C 000DF45C  38 21 00 48 */	addi r1, r1, 0x48
/* 800E2880 000DF460  7C 08 03 A6 */	mtlr r0
/* 800E2884 000DF464  4E 80 00 20 */	blr 


.section .data
    .balign 8
.global lbl_803C7120
lbl_803C7120:
    .4byte 0xFFFFFFFF
    .4byte NULL
    .4byte 0x01000000
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0xFFFFFFFF
    .4byte NULL
    .4byte 0x01000000
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x00000127
    .4byte 0x00340111
    .4byte 0x12000000
    .4byte func_800E0E18
    .4byte func_800E0E54
    .4byte func_800E0E84
    .4byte func_800E0EA4
    .4byte func_800761C8
    .4byte 0x00000128
    .4byte 0x00340511
    .4byte 0x12000000
    .4byte func_800E10B0
    .4byte func_800E10EC
    .4byte func_800E111C
    .4byte func_800E113C
    .4byte func_800761C8
    .4byte 0x00000129
    .4byte 0x00341012
    .4byte 0x13000000
    .4byte func_800E1550
    .4byte func_800E15C8
    .4byte func_800E15D0
    .4byte func_800E1840
    .4byte func_800761C8
    .4byte 0x0000012A
    .4byte 0x00341012
    .4byte 0x13000000
    .4byte func_800E158C
    .4byte func_800E15CC
    .4byte func_800E16E0
    .4byte func_800E187C
    .4byte func_800761C8
    .4byte 0x0000012B
    .4byte 0x00340213
    .4byte 0x14000000
    .4byte func_800E1B24
    .4byte func_800E1BE4
    .4byte func_800E1E74
    .4byte func_800E1F70
    .4byte func_800761C8
    .4byte 0x0000012C
    .4byte 0x00340613
    .4byte 0x14000000
    .4byte func_800E1B84
    .4byte func_800E1D2C
    .4byte func_800E1EAC
    .4byte func_800E1FE0
    .4byte func_800761C8
    .4byte 0x0000012D
    .4byte 0x00340214
    .4byte 0x15000000
    .4byte func_800E22BC
    .4byte func_800E23DC
    .4byte func_800E23E4
    .4byte func_800E25C4
    .4byte func_800761C8
    .4byte 0x0000012E
    .4byte 0x00340614
    .4byte 0x15000000
    .4byte func_800E2308
    .4byte func_800E23E0
    .4byte func_800E2508
    .4byte func_800E2778
    .4byte func_800761C8
.global lbl_803C7260
lbl_803C7260:
    .4byte 0x0000000E
    .4byte NULL
    .4byte 0x01000000
    .4byte NULL
    .4byte NULL
    .4byte func_800C7158
    .4byte NULL
    .4byte NULL
    .4byte 0x0000000F
    .4byte NULL
    .4byte 0x01000000
    .4byte NULL
    .4byte NULL
    .4byte func_800C7200
    .4byte NULL
    .4byte NULL
.global lbl_803C72A0
lbl_803C72A0:
    .asciz "A@"
    .balign 4
    .4byte NULL
    .4byte 0xC0C00000
    .4byte 0x40C00000
    .4byte 0x40C00000
    .4byte 0x40C00000


.section .sdata2
    .balign 8
.global lbl_804D9198
lbl_804D9198:
    .4byte 0x00000000
.global lbl_804D919C
lbl_804D919C:
    .4byte 0x3F800000 
.global lbl_804D91A0
lbl_804D91A0:
	.4byte 0x00000000
.global lbl_804D91A4
lbl_804D91A4:
	.4byte 0x3F800000
.global lbl_804D91A8
lbl_804D91A8:
	.4byte 0x40400000
.global lbl_804D91AC
lbl_804D91AC:
	.4byte 0x3F666666
.global lbl_804D91B0
lbl_804D91B0:
	.4byte 0x3CA3D70A
.global lbl_804D91B4
lbl_804D91B4:
	.4byte 0x3F860A92
.global lbl_804D91B8
lbl_804D91B8:
	.4byte 0x3DCCCCCD
	.4byte 0x00000000
.global lbl_804D91C0
lbl_804D91C0:
	.4byte 0x00000000
.global lbl_804D91C4
lbl_804D91C4:
	.4byte 0x3F800000
.global lbl_804D91C8
lbl_804D91C8:
	.4byte 0x3FF00000
	.4byte 0x00000000
.global lbl_804D91D0
lbl_804D91D0:
	.4byte 0x3C8EFA35
	.4byte 0x00000000
.global lbl_804D91D8
lbl_804D91D8:
	.4byte 0x3FF921FB
	.4byte 0x54442D18
.global lbl_804D91E0
lbl_804D91E0:
	.4byte 0x00000000
.global lbl_804D91E4
lbl_804D91E4:
	.4byte 0x3F800000
.global lbl_804D91E8
lbl_804D91E8:
	.4byte 0x00000000
	.4byte 0x00000000
.global lbl_804D91F0
lbl_804D91F0:
	.4byte 0x43300000
	.4byte 0x80000000
