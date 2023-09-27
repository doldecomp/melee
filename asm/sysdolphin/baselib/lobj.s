.include "macros.inc"

.section .text

LObjAmnesia:
/* 80367628 00364208  7C 08 02 A6 */	mflr r0
/* 8036762C 0036420C  90 01 00 04 */	stw r0, 4(r1)
/* 80367630 00364210  94 21 FF F8 */	stwu r1, -8(r1)
/* 80367634 00364214  80 0D BF 98 */	lwz r0, default_class@sda21(r13)
/* 80367638 00364218  7C 03 00 40 */	cmplw r3, r0
/* 8036763C 0036421C  40 82 00 0C */	bne .L_80367648
/* 80367640 00364220  38 00 00 00 */	li r0, 0
/* 80367644 00364224  90 0D BF 98 */	stw r0, default_class@sda21(r13)
.L_80367648:
/* 80367648 00364228  3C 80 80 40 */	lis r4, hsdLObj@ha
/* 8036764C 0036422C  38 04 60 C0 */	addi r0, r4, hsdLObj@l
/* 80367650 00364230  7C 03 00 40 */	cmplw r3, r0
/* 80367654 00364234  40 82 00 0C */	bne .L_80367660
/* 80367658 00364238  38 00 00 00 */	li r0, 0
/* 8036765C 0036423C  90 0D BF 9C */	stw r0, current_lights@sda21(r13)
.L_80367660:
/* 80367660 00364240  3C 80 80 40 */	lis r4, hsdLObj@ha
/* 80367664 00364244  38 84 60 C0 */	addi r4, r4, hsdLObj@l
/* 80367668 00364248  80 84 00 14 */	lwz r4, 0x14(r4)
/* 8036766C 0036424C  81 84 00 38 */	lwz r12, 0x38(r4)
/* 80367670 00364250  7D 88 03 A6 */	mtlr r12
/* 80367674 00364254  4E 80 00 21 */	blrl
/* 80367678 00364258  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8036767C 0036425C  38 21 00 08 */	addi r1, r1, 8
/* 80367680 00364260  7C 08 03 A6 */	mtlr r0
/* 80367684 00364264  4E 80 00 20 */	blr

.global LObjInfoInit
LObjInfoInit:
/* 80367688 00364268  7C 08 02 A6 */	mflr r0
/* 8036768C 0036426C  3C 60 80 40 */	lis r3, hsdLObj@ha
/* 80367690 00364270  90 01 00 04 */	stw r0, 4(r1)
/* 80367694 00364274  38 E0 00 40 */	li r7, 0x40
/* 80367698 00364278  39 00 00 D4 */	li r8, 0xd4
/* 8036769C 0036427C  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 803676A0 00364280  93 E1 00 0C */	stw r31, 0xc(r1)
/* 803676A4 00364284  3B E3 60 C0 */	addi r31, r3, hsdLObj@l
/* 803676A8 00364288  3C 60 80 40 */	lis r3, hsdObj@ha
/* 803676AC 0036428C  38 83 72 A8 */	addi r4, r3, hsdObj@l
/* 803676B0 00364290  38 7F 00 00 */	addi r3, r31, 0
/* 803676B4 00364294  38 BF 01 38 */	addi r5, r31, 0x138
/* 803676B8 00364298  38 DF 01 50 */	addi r6, r31, 0x150
/* 803676BC 0036429C  48 01 A5 5D */	bl hsdInitClassInfo
/* 803676C0 003642A0  3C 60 80 36 */	lis r3, LObjRelease@ha
/* 803676C4 003642A4  38 03 74 B4 */	addi r0, r3, LObjRelease@l
/* 803676C8 003642A8  3C 60 80 36 */	lis r3, LObjAmnesia@ha
/* 803676CC 003642AC  90 1F 00 30 */	stw r0, 0x30(r31)
/* 803676D0 003642B0  38 03 76 28 */	addi r0, r3, LObjAmnesia@l
/* 803676D4 003642B4  3C 60 80 36 */	lis r3, LObjLoad@ha
/* 803676D8 003642B8  90 1F 00 38 */	stw r0, 0x38(r31)
/* 803676DC 003642BC  38 03 6E A8 */	addi r0, r3, LObjLoad@l
/* 803676E0 003642C0  90 1F 00 3C */	stw r0, 0x3c(r31)
/* 803676E4 003642C4  80 01 00 14 */	lwz r0, 0x14(r1)
/* 803676E8 003642C8  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 803676EC 003642CC  38 21 00 10 */	addi r1, r1, 0x10
/* 803676F0 003642D0  7C 08 03 A6 */	mtlr r0
/* 803676F4 003642D4  4E 80 00 20 */	blr


.section .sdata
    .balign 8
.global HSD_LObj_804D5D18
HSD_LObj_804D5D18:
    .asciz "lobj.c"
    .balign 4
.global HSD_LObj_804D5D20
HSD_LObj_804D5D20:
    .asciz "0"
    .balign 4
.global HSD_LObj_804D5D24
HSD_LObj_804D5D24:
    .asciz "lobj"
    .balign 4
.global HSD_LObj_804D5D2C
HSD_LObj_804D5D2C:
    .asciz "lobj.h"
    .balign 4
.global HSD_LObj_804D5D34
HSD_LObj_804D5D34:
    .asciz "new"
    .balign 4
.global HSD_LObj_804D5D38
HSD_LObj_804D5D38:
    .4byte NULL
.global HSD_LObj_804D5D3C
HSD_LObj_804D5D3C:
    .asciz "*p"
    .balign 4


.section .sbss
    .balign 8
.global current_lights
current_lights:
    .skip 0x4
.global nb_active_lights
nb_active_lights:
    .skip 0x4
.global lightmask_diffuse
lightmask_diffuse:
    .skip 0x4
.global lightmask_specular
lightmask_specular:
    .skip 0x4
.global lightmask_attnfunc
lightmask_attnfunc:
    .skip 0x4
.global lightmask_alpha
lightmask_alpha:
    .skip 0x4
