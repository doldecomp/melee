.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240

.global ftNess_AttackHi4_Release_Action
ftNess_AttackHi4_Release_Action:
/* 80116494 00113074  7C 08 02 A6 */	mflr r0
/* 80116498 00113078  38 80 01 58 */	li r4, 0x158
/* 8011649C 0011307C  90 01 00 04 */	stw r0, 4(r1)
/* 801164A0 00113080  3C A0 00 04 */	lis r5, 4
/* 801164A4 00113084  38 C0 00 00 */	li r6, 0
/* 801164A8 00113088  94 21 FF B0 */	stwu r1, -0x50(r1)
/* 801164AC 0011308C  93 E1 00 4C */	stw r31, 0x4c(r1)
/* 801164B0 00113090  93 C1 00 48 */	stw r30, 0x48(r1)
/* 801164B4 00113094  93 A1 00 44 */	stw r29, 0x44(r1)
/* 801164B8 00113098  93 81 00 40 */	stw r28, 0x40(r1)
/* 801164BC 0011309C  7C 7C 1B 78 */	mr r28, r3
/* 801164C0 001130A0  C0 22 9D 14 */	lfs f1, lbl_804D96F4/*13.0f*/@sda21(r2)
/* 801164C4 001130A4  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 801164C8 001130A8  C0 42 9C E4 */	lfs f2, lbl_804D96C4/*1.0f*/@sda21(r2)
/* 801164CC 001130AC  C0 62 9C E0 */	lfs f3, lbl_804D96C0/*0.0f*/@sda21(r2)
# SPLIT NO EARLIER THAN HERE
/* 801164D0 001130B0  4B F5 2E DD */	bl Fighter_ActionStateChange_800693AC
/* 801164D4 001130B4  7F 83 E3 78 */	mr r3, r28
/* 801164D8 001130B8  4B F5 86 CD */	bl func_8006EBA4
/* 801164DC 001130BC  83 BC 00 2C */	lwz r29, 0x2c(r28)
/* 801164E0 001130C0  38 00 00 0E */	li r0, 0xe
/* 801164E4 001130C4  90 1D 23 40 */	stw r0, 0x2340(r29)
/* 801164E8 001130C8  80 7D 22 2C */	lwz r3, 0x222c(r29)
/* 801164EC 001130CC  28 03 00 00 */	cmplwi r3, 0
/* 801164F0 001130D0  41 82 00 40 */	beq lbl_80116530
/* 801164F4 001130D4  80 A3 00 2C */	lwz r5, 0x2c(r3)
/* 801164F8 001130D8  3C 80 80 3B */	lis r4, YoyoChargePos@ha
/* 801164FC 001130DC  38 C4 75 A4 */	addi r6, r4, YoyoChargePos@l
/* 80116500 001130E0  80 E5 00 C4 */	lwz r7, 0xc4(r5)
/* 80116504 001130E4  38 81 00 34 */	addi r4, r1, 0x34
/* 80116508 001130E8  80 A6 00 00 */	lwz r5, 0(r6)
/* 8011650C 001130EC  83 C7 00 04 */	lwz r30, 4(r7)
/* 80116510 001130F0  80 06 00 04 */	lwz r0, 4(r6)
/* 80116514 001130F4  90 A1 00 34 */	stw r5, 0x34(r1)
/* 80116518 001130F8  90 01 00 38 */	stw r0, 0x38(r1)
/* 8011651C 001130FC  80 06 00 08 */	lwz r0, 8(r6)
/* 80116520 00113100  90 01 00 3C */	stw r0, 0x3c(r1)
/* 80116524 00113104  48 1A 9A ED */	bl func_802C0010
/* 80116528 00113108  C0 1E 00 18 */	lfs f0, 0x18(r30)
/* 8011652C 0011310C  D0 1D 22 3C */	stfs f0, 0x223c(r29)
lbl_80116530:
/* 80116530 00113110  3C 80 00 03 */	lis r4, 0x000334AA@ha
/* 80116534 00113114  38 7D 00 00 */	addi r3, r29, 0
/* 80116538 00113118  38 84 34 AA */	addi r4, r4, 0x000334AA@l
/* 8011653C 0011311C  38 A0 00 7F */	li r5, 0x7f
/* 80116540 00113120  38 C0 00 40 */	li r6, 0x40
/* 80116544 00113124  4B F7 1F CD */	bl func_80088510
/* 80116548 00113128  C0 3D 21 18 */	lfs f1, 0x2118(r29)
/* 8011654C 0011312C  7F 83 E3 78 */	mr r3, r28
/* 80116550 00113130  4B FF EA 21 */	bl ftNess_YoyoApplyDamage
/* 80116554 00113134  88 1F 22 22 */	lbz r0, 0x2222(r31)
/* 80116558 00113138  38 60 00 01 */	li r3, 1
/* 8011655C 0011313C  50 60 2E B4 */	rlwimi r0, r3, 5, 0x1a, 0x1a
/* 80116560 00113140  3C 60 80 11 */	lis r3, ftNess_YoyoStartTimedRehit@ha
/* 80116564 00113144  98 1F 22 22 */	stb r0, 0x2222(r31)
/* 80116568 00113148  38 03 5C 74 */	addi r0, r3, ftNess_YoyoStartTimedRehit@l
/* 8011656C 0011314C  3C 60 80 11 */	lis r3, ftNess_YoyoUpdateHitPos@ha
/* 80116570 00113150  90 1F 21 C0 */	stw r0, 0x21c0(r31)
/* 80116574 00113154  38 03 4E B8 */	addi r0, r3, ftNess_YoyoUpdateHitPos@l
/* 80116578 00113158  90 1F 21 BC */	stw r0, 0x21bc(r31)
/* 8011657C 0011315C  80 01 00 54 */	lwz r0, 0x54(r1)
/* 80116580 00113160  83 E1 00 4C */	lwz r31, 0x4c(r1)
/* 80116584 00113164  83 C1 00 48 */	lwz r30, 0x48(r1)
/* 80116588 00113168  83 A1 00 44 */	lwz r29, 0x44(r1)
/* 8011658C 0011316C  83 81 00 40 */	lwz r28, 0x40(r1)
/* 80116590 00113170  38 21 00 50 */	addi r1, r1, 0x50
/* 80116594 00113174  7C 08 03 A6 */	mtlr r0
/* 80116598 00113178  4E 80 00 20 */	blr

.section .sdata2
    .balign 8
.global lbl_804D96C0/*0.0f*/
lbl_804D96C0/*0.0f*/:
    .4byte 0x00000000
.global lbl_804D96C4/*1.0f*/
lbl_804D96C4/*1.0f*/:
    .4byte 0x3F800000
.global lbl_804D96C8/*0.0039059999398887157f*/
lbl_804D96C8/*0.0039059999398887157f*/:
    .4byte 0x3B7FFBCE
.global lbl_804D96CC/*0.5f*/
lbl_804D96CC/*0.5f*/:
    .4byte 0x3F000000
.global lbl_804D96D0/*-1.0f*/
lbl_804D96D0/*-1.0f*/:
    .4byte 0xBF800000
.global lbl_804D96D4/*1.5f*/
lbl_804D96D4/*1.5f*/:
    .4byte 0x3FC00000
.global lbl_804D96D8/*60.0f*/
lbl_804D96D8/*60.0f*/:
    .4byte 0x42700000
    .4byte 0x00000000
.global lbl_804D96E0/*magic conversion*/
lbl_804D96E0/*magic conversion*/:
    .4byte 0x43300000
    .4byte 0x80000000
.global lbl_804D96E8/*12.0f*/
lbl_804D96E8/*12.0f*/:
    .4byte 0x41400000
.global lbl_804D96EC/*0.10000000149011612f*/
lbl_804D96EC/*0.10000000149011612f*/:
    .4byte 0x3DCCCCCD
.global lbl_804D96F0/*14.0f*/
lbl_804D96F0/*14.0f*/:
    .4byte 0x41600000
.global lbl_804D96F4/*13.0f*/
lbl_804D96F4/*13.0f*/:
    .4byte 0x41500000
