.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240

.global ftNess_AttackLw4_Release_Action
ftNess_AttackLw4_Release_Action:
/* 80116AE8 001136C8  7C 08 02 A6 */	mflr r0
/* 80116AEC 001136CC  38 80 01 5B */	li r4, 0x15b
/* 80116AF0 001136D0  90 01 00 04 */	stw r0, 4(r1)
/* 80116AF4 001136D4  3C A0 00 04 */	lis r5, 4
/* 80116AF8 001136D8  38 C0 00 00 */	li r6, 0
/* 80116AFC 001136DC  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80116B00 001136E0  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80116B04 001136E4  93 C1 00 10 */	stw r30, 0x10(r1)
/* 80116B08 001136E8  7C 7E 1B 78 */	mr r30, r3
/* 80116B0C 001136EC  C0 22 9D 34 */	lfs f1, lbl_804D9714/*13.0f*/@sda21(r2)
/* 80116B10 001136F0  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80116B14 001136F4  C0 42 9D 1C */	lfs f2, lbl_804D96FC/*1.0f*/@sda21(r2)
/* 80116B18 001136F8  C0 62 9D 18 */	lfs f3, lbl_804D96F8/*0.0f*/@sda21(r2)
# SPLIT NO EARLIER THAN HERE
/* 80116B1C 001136FC  4B F5 28 91 */	bl Fighter_ActionStateChange_800693AC
/* 80116B20 00113700  7F C3 F3 78 */	mr r3, r30
/* 80116B24 00113704  4B F5 80 81 */	bl func_8006EBA4
/* 80116B28 00113708  7F C3 F3 78 */	mr r3, r30
/* 80116B2C 0011370C  4B FF EB 55 */	bl ftNess_YoyoSetChargeDamage
/* 80116B30 00113710  88 1F 22 22 */	lbz r0, 0x2222(r31)
/* 80116B34 00113714  38 60 00 01 */	li r3, 1
/* 80116B38 00113718  50 60 2E B4 */	rlwimi r0, r3, 5, 0x1a, 0x1a
/* 80116B3C 0011371C  3C 60 80 11 */	lis r3, ftNess_YoyoStartTimedRehit@ha
/* 80116B40 00113720  98 1F 22 22 */	stb r0, 0x2222(r31)
/* 80116B44 00113724  38 03 5C 74 */	addi r0, r3, ftNess_YoyoStartTimedRehit@l
/* 80116B48 00113728  3C 60 80 11 */	lis r3, ftNess_YoyoUpdateHitPos@ha
/* 80116B4C 0011372C  90 1F 21 C0 */	stw r0, 0x21c0(r31)
/* 80116B50 00113730  38 03 4E B8 */	addi r0, r3, ftNess_YoyoUpdateHitPos@l
/* 80116B54 00113734  90 1F 21 BC */	stw r0, 0x21bc(r31)
/* 80116B58 00113738  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80116B5C 0011373C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80116B60 00113740  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 80116B64 00113744  38 21 00 18 */	addi r1, r1, 0x18
/* 80116B68 00113748  7C 08 03 A6 */	mtlr r0
/* 80116B6C 0011374C  4E 80 00 20 */	blr 
.section .sdata2
    .balign 8
.global lbl_804D96F8/*0.0f*/
lbl_804D96F8/*0.0f*/:
	.4byte 0x00000000
.global lbl_804D96FC/*1.0f*/
lbl_804D96FC/*1.0f*/:
	.4byte 0x3F800000
.global lbl_804D9700/*magic conversion*/
lbl_804D9700/*magic conversion*/:
	.4byte 0x43300000
	.4byte 0x80000000
.global lbl_804D9708/*12.0f*/
lbl_804D9708/*12.0f*/:
	.4byte 0x41400000
.global lbl_804D970C/*0.20000000298023224f*/
lbl_804D970C/*0.20000000298023224f*/:
	.4byte 0x3E4CCCCD
.global lbl_804D9710/*14.0f*/
lbl_804D9710/*14.0f*/:
	.4byte 0x41600000
.global lbl_804D9714/*13.0f*/
lbl_804D9714/*13.0f*/:
	.4byte 0x41500000
