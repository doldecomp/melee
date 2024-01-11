.include "macros.inc"

.section .text # 0x8031C99C - 0x8031CAFC

.global un_8031C99C
un_8031C99C:
/* 8031C99C 0031957C  3C 80 80 40 */	lis r4, un_803FFFA8@ha
/* 8031C9A0 00319580  54 63 10 3A */	slwi r3, r3, 2
/* 8031C9A4 00319584  38 04 FF A8 */	addi r0, r4, un_803FFFA8@l
/* 8031C9A8 00319588  7C 60 1A 14 */	add r3, r0, r3
/* 8031C9AC 0031958C  80 63 00 00 */	lwz r3, 0(r3)
/* 8031C9B0 00319590  4E 80 00 20 */	blr

.global un_8031C9B4
un_8031C9B4:
/* 8031C9B4 00319594  7C 08 02 A6 */	mflr r0
/* 8031C9B8 00319598  90 01 00 04 */	stw r0, 4(r1)
/* 8031C9BC 0031959C  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8031C9C0 003195A0  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8031C9C4 003195A4  3B E4 00 00 */	addi r31, r4, 0
/* 8031C9C8 003195A8  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8031C9CC 003195AC  3B C3 00 00 */	addi r30, r3, 0
/* 8031C9D0 003195B0  4B E6 1A 71 */	bl gm_8017E440
/* 8031C9D4 003195B4  54 63 06 3E */	clrlwi r3, r3, 0x18
/* 8031C9D8 003195B8  28 03 00 04 */	cmplwi r3, 4
/* 8031C9DC 003195BC  41 82 00 10 */	beq .L_8031C9EC
/* 8031C9E0 003195C0  38 9E 00 00 */	addi r4, r30, 0
/* 8031C9E4 003195C4  38 BF 00 00 */	addi r5, r31, 0
/* 8031C9E8 003195C8  4B E4 AF 11 */	bl gm_801678F8
.L_8031C9EC:
/* 8031C9EC 003195CC  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8031C9F0 003195D0  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8031C9F4 003195D4  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8031C9F8 003195D8  38 21 00 18 */	addi r1, r1, 0x18
/* 8031C9FC 003195DC  7C 08 03 A6 */	mtlr r0
/* 8031CA00 003195E0  4E 80 00 20 */	blr

.global un_8031CA04
un_8031CA04:
/* 8031CA04 003195E4  7C 08 02 A6 */	mflr r0
/* 8031CA08 003195E8  90 01 00 04 */	stw r0, 4(r1)
/* 8031CA0C 003195EC  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8031CA10 003195F0  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8031CA14 003195F4  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8031CA18 003195F8  93 A1 00 14 */	stw r29, 0x14(r1)
/* 8031CA1C 003195FC  3B A3 00 00 */	addi r29, r3, 0
/* 8031CA20 00319600  38 60 00 02 */	li r3, 2
/* 8031CA24 00319604  4B D1 46 7D */	bl Camera_800310A0
/* 8031CA28 00319608  38 00 00 09 */	li r0, 9
/* 8031CA2C 0031960C  90 1D 00 24 */	stw r0, 0x24(r29)
/* 8031CA30 00319610  3B C0 00 00 */	li r30, 0
/* 8031CA34 00319614  38 7D 00 00 */	addi r3, r29, 0
/* 8031CA38 00319618  93 DD 00 20 */	stw r30, 0x20(r29)
/* 8031CA3C 0031961C  38 80 00 07 */	li r4, 7
/* 8031CA40 00319620  48 07 44 91 */	bl HSD_GObj_80390ED0
/* 8031CA44 00319624  38 60 00 01 */	li r3, 1
/* 8031CA48 00319628  4B D1 46 59 */	bl Camera_800310A0
/* 8031CA4C 0031962C  3B E0 00 08 */	li r31, 8
/* 8031CA50 00319630  93 FD 00 24 */	stw r31, 0x24(r29)
/* 8031CA54 00319634  38 7D 00 00 */	addi r3, r29, 0
/* 8031CA58 00319638  38 80 00 07 */	li r4, 7
/* 8031CA5C 0031963C  93 DD 00 20 */	stw r30, 0x20(r29)
/* 8031CA60 00319640  48 07 44 71 */	bl HSD_GObj_80390ED0
/* 8031CA64 00319644  38 60 00 00 */	li r3, 0
/* 8031CA68 00319648  4B D1 46 39 */	bl Camera_800310A0
/* 8031CA6C 0031964C  93 FD 00 24 */	stw r31, 0x24(r29)
/* 8031CA70 00319650  38 7D 00 00 */	addi r3, r29, 0
/* 8031CA74 00319654  38 80 00 07 */	li r4, 7
/* 8031CA78 00319658  93 DD 00 20 */	stw r30, 0x20(r29)
/* 8031CA7C 0031965C  48 07 44 55 */	bl HSD_GObj_80390ED0
/* 8031CA80 00319660  38 7D 00 00 */	addi r3, r29, 0
/* 8031CA84 00319664  38 C0 00 01 */	li r6, 1
/* 8031CA88 00319668  38 A0 00 00 */	li r5, 0
/* 8031CA8C 0031966C  4B D1 49 55 */	bl Camera_800313E0
/* 8031CA90 00319670  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8031CA94 00319674  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8031CA98 00319678  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8031CA9C 0031967C  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 8031CAA0 00319680  38 21 00 20 */	addi r1, r1, 0x20
/* 8031CAA4 00319684  7C 08 03 A6 */	mtlr r0
/* 8031CAA8 00319688  4E 80 00 20 */	blr

.global un_8031CAAC
un_8031CAAC:
/* 8031CAAC 0031968C  7C 08 02 A6 */	mflr r0
/* 8031CAB0 00319690  90 01 00 04 */	stw r0, 4(r1)
/* 8031CAB4 00319694  94 21 FF F8 */	stwu r1, -8(r1)
/* 8031CAB8 00319698  4B E6 19 79 */	bl gm_8017E430
/* 8031CABC 0031969C  4B E8 6B E5 */	bl gm_801A36A0
/* 8031CAC0 003196A0  38 00 10 00 */	li r0, 0x1000
/* 8031CAC4 003196A4  38 A0 00 00 */	li r5, 0
/* 8031CAC8 003196A8  7C 84 00 38 */	and r4, r4, r0
/* 8031CACC 003196AC  7C 60 28 38 */	and r0, r3, r5
/* 8031CAD0 003196B0  7C 83 2A 78 */	xor r3, r4, r5
/* 8031CAD4 003196B4  7C 00 2A 78 */	xor r0, r0, r5
/* 8031CAD8 003196B8  7C 60 03 79 */	or. r0, r3, r0
/* 8031CADC 003196BC  41 82 00 14 */	beq .L_8031CAF0
/* 8031CAE0 003196C0  4B D0 6B FD */	bl lbAudioAx_800236DC
/* 8031CAE4 003196C4  4B D0 6B B1 */	bl lbAudioAx_80023694
/* 8031CAE8 003196C8  4B CF 7B 0D */	bl lb_800145F4
/* 8031CAEC 003196CC  4B E8 80 75 */	bl gm_801A4B60
.L_8031CAF0:
/* 8031CAF0 003196D0  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8031CAF4 003196D4  38 21 00 08 */	addi r1, r1, 8
/* 8031CAF8 003196D8  7C 08 03 A6 */	mtlr r0
/* 8031CAFC 003196DC  4E 80 00 20 */	blr


.section .data
    .balign 8
.global un_803FFDA0
un_803FFDA0:
    .asciz "PlCaDViWaitAJ.dat"
    .balign 4
.global un_803FFDB4
un_803FFDB4:
    .asciz "PlDkDViWaitAJ.dat"
    .balign 4
.global un_803FFDC8
un_803FFDC8:
    .asciz "PlFxDViWaitAJ.dat"
    .balign 4
.global un_803FFDDC
un_803FFDDC:
    .asciz "PlGwDViWaitAJ.dat"
    .balign 4
.global un_803FFDF0
un_803FFDF0:
    .asciz "PlKbDViWaitAJ.dat"
    .balign 4
.global un_803FFE04
un_803FFE04:
    .asciz "PlKpDViWaitAJ.dat"
    .balign 4
.global un_803FFE18
un_803FFE18:
    .asciz "PlLkDViWaitAJ.dat"
    .balign 4
.global un_803FFE2C
un_803FFE2C:
    .asciz "PlLgDViWaitAJ.dat"
    .balign 4
.global un_803FFE40
un_803FFE40:
    .asciz "PlMrDViWaitAJ.dat"
    .balign 4
.global un_803FFE54
un_803FFE54:
    .asciz "PlMsDViWaitAj.dat"
    .balign 4
.global un_803FFE68
un_803FFE68:
    .asciz "PlMtDViWaitAJ.dat"
    .balign 4
.global un_803FFE7C
un_803FFE7C:
    .asciz "PlNsDViWaitAJ.dat"
    .balign 4
.global un_803FFE90
un_803FFE90:
    .asciz "PlPeDViWaitAJ.dat"
    .balign 4
.global un_803FFEA4
un_803FFEA4:
    .asciz "PlPkDViWaitAJ.dat"
    .balign 4
.global un_803FFEB8
un_803FFEB8:
    .asciz "PlPpDViWaitAJ.dat"
    .balign 4
.global un_803FFECC
un_803FFECC:
    .asciz "PlPrDViWaitAJ.dat"
    .balign 4
.global un_803FFEE0
un_803FFEE0:
    .asciz "PlSsDViWaitAJ.dat"
    .balign 4
.global un_803FFEF4
un_803FFEF4:
    .asciz "PlYsDViWaitAJ.dat"
    .balign 4
.global un_803FFF08
un_803FFF08:
    .asciz "PlZdDViWaitAJ.dat"
    .balign 4
.global un_803FFF1C
un_803FFF1C:
    .asciz "PlSkDViWaitAJ.dat"
    .balign 4
.global un_803FFF30
un_803FFF30:
    .asciz "PlFcDViWaitAJ.dat"
    .balign 4
.global un_803FFF44
un_803FFF44:
    .asciz "PlClDViWaitAJ.dat"
    .balign 4
.global un_803FFF58
un_803FFF58:
    .asciz "PlDrDViWaitAJ.dat"
    .balign 4
.global un_803FFF6C
un_803FFF6C:
    .asciz "PlFeDViWaitAJ.dat"
    .balign 4
.global un_803FFF80
un_803FFF80:
    .asciz "PlPcDViWaitAJ.dat"
    .balign 4
.global un_803FFF94
un_803FFF94:
    .asciz "PlGnDViWaitAJ.dat"
    .balign 4
.global un_803FFFA8
un_803FFFA8:
    .4byte un_803FFDA0
    .4byte un_803FFDB4
    .4byte un_803FFDC8
    .4byte un_803FFDDC
    .4byte un_803FFDF0
    .4byte un_803FFE04
    .4byte un_803FFE18
    .4byte un_803FFE2C
    .4byte un_803FFE40
    .4byte un_803FFE54
    .4byte un_803FFE68
    .4byte un_803FFE7C
    .4byte un_803FFE90
    .4byte un_803FFEA4
    .4byte un_803FFEB8
    .4byte un_803FFECC
    .4byte un_803FFEE0
    .4byte un_803FFEF4
    .4byte un_803FFF08
    .4byte un_803FFF1C
    .4byte un_803FFF30
    .4byte un_803FFF44
    .4byte un_803FFF58
    .4byte un_803FFF6C
    .4byte un_803FFF80
    .4byte un_803FFF94
