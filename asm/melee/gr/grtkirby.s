.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240

.global func_80221364
func_80221364:
/* 80221364 0021DF44  4E 80 00 20 */	blr
.global lbl_80221368
lbl_80221368:
/* 80221368 0021DF48  7C 08 02 A6 */	mflr r0
/* 8022136C 0021DF4C  3C 60 80 4A */	lis r3, stage_info@ha
/* 80221370 0021DF50  90 01 00 04 */	stw r0, 4(r1)
/* 80221374 0021DF54  38 63 E6 C8 */	addi r3, r3, stage_info@l
/* 80221378 0021DF58  38 A3 00 8C */	addi r5, r3, 0x8c
/* 8022137C 0021DF5C  94 21 FF F8 */	stwu r1, -8(r1)
/* 80221380 0021DF60  38 80 00 01 */	li r4, 1
/* 80221384 0021DF64  88 03 00 8C */	lbz r0, 0x8c(r3)
/* 80221388 0021DF68  38 60 00 00 */	li r3, 0
/* 8022138C 0021DF6C  50 60 1F 38 */	rlwimi r0, r3, 3, 0x1c, 0x1c
/* 80221390 0021DF70  98 05 00 00 */	stb r0, 0(r5)
/* 80221394 0021DF74  38 60 00 00 */	li r3, 0
/* 80221398 0021DF78  88 05 00 00 */	lbz r0, 0(r5)
/* 8022139C 0021DF7C  50 80 17 7A */	rlwimi r0, r4, 2, 0x1d, 0x1d
/* 802213A0 0021DF80  98 05 00 00 */	stb r0, 0(r5)
/* 802213A4 0021DF84  48 00 00 65 */	bl func_80221408
/* 802213A8 0021DF88  38 60 00 01 */	li r3, 1
/* 802213AC 0021DF8C  48 00 00 5D */	bl func_80221408
/* 802213B0 0021DF90  38 60 00 02 */	li r3, 2
/* 802213B4 0021DF94  48 00 00 55 */	bl func_80221408
/* 802213B8 0021DF98  4B FA 26 09 */	bl func_801C39C0
/* 802213BC 0021DF9C  4B FA 27 F9 */	bl func_801C3BB4
/* 802213C0 0021DFA0  4B FA 2E 51 */	bl func_801C4210
/* 802213C4 0021DFA4  4B FA 2E E9 */	bl func_801C42AC
/* 802213C8 0021DFA8  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802213CC 0021DFAC  38 21 00 08 */	addi r1, r1, 8
/* 802213D0 0021DFB0  7C 08 03 A6 */	mtlr r0
/* 802213D4 0021DFB4  4E 80 00 20 */	blr
.global lbl_802213D8
lbl_802213D8:
/* 802213D8 0021DFB8  4E 80 00 20 */	blr
.global lbl_802213DC
lbl_802213DC:
/* 802213DC 0021DFBC  7C 08 02 A6 */	mflr r0
/* 802213E0 0021DFC0  38 60 00 00 */	li r3, 0
/* 802213E4 0021DFC4  90 01 00 04 */	stw r0, 4(r1)
/* 802213E8 0021DFC8  94 21 FF F8 */	stwu r1, -8(r1)
/* 802213EC 0021DFCC  4B FA 9A 19 */	bl func_801CAE04
/* 802213F0 0021DFD0  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802213F4 0021DFD4  38 21 00 08 */	addi r1, r1, 8
/* 802213F8 0021DFD8  7C 08 03 A6 */	mtlr r0
/* 802213FC 0021DFDC  4E 80 00 20 */	blr
.global lbl_80221400
lbl_80221400:
/* 80221400 0021DFE0  38 60 00 00 */	li r3, 0
/* 80221404 0021DFE4  4E 80 00 20 */	blr

.global func_80221408
func_80221408:
/* 80221408 0021DFE8  7C 08 02 A6 */	mflr r0
/* 8022140C 0021DFEC  90 01 00 04 */	stw r0, 4(r1)
/* 80221410 0021DFF0  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80221414 0021DFF4  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80221418 0021DFF8  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8022141C 0021DFFC  93 A1 00 14 */	stw r29, 0x14(r1)
/* 80221420 0021E000  93 81 00 10 */	stw r28, 0x10(r1)
/* 80221424 0021E004  3B 83 00 00 */	addi r28, r3, 0
/* 80221428 0021E008  1C 1C 00 14 */	mulli r0, r28, 0x14
/* 8022142C 0021E00C  3C 60 80 3F */	lis r3, lbl_803E8BB0@ha
/* 80221430 0021E010  3B E3 8B B0 */	addi r31, r3, lbl_803E8BB0@l
/* 80221434 0021E014  38 7C 00 00 */	addi r3, r28, 0
/* 80221438 0021E018  7F BF 02 14 */	add r29, r31, r0
/* 8022143C 0021E01C  4B FA 00 95 */	bl func_801C14D0
/* 80221440 0021E020  7C 7E 1B 79 */	or. r30, r3, r3
/* 80221444 0021E024  41 82 00 70 */	beq .L_802214B4
/* 80221448 0021E028  83 FE 00 2C */	lwz r31, 0x2c(r30)
/* 8022144C 0021E02C  38 00 00 00 */	li r0, 0
/* 80221450 0021E030  3C 60 80 1C */	lis r3, func_801C5DB0@ha
/* 80221454 0021E034  90 1F 00 08 */	stw r0, 8(r31)
/* 80221458 0021E038  38 83 5D B0 */	addi r4, r3, func_801C5DB0@l
/* 8022145C 0021E03C  38 7E 00 00 */	addi r3, r30, 0
/* 80221460 0021E040  90 1F 00 0C */	stw r0, 0xc(r31)
/* 80221464 0021E044  38 A0 00 03 */	li r5, 3
/* 80221468 0021E048  38 C0 00 00 */	li r6, 0
/* 8022146C 0021E04C  48 16 F2 31 */	bl GObj_SetupGXLink
/* 80221470 0021E050  80 1D 00 0C */	lwz r0, 0xc(r29)
/* 80221474 0021E054  28 00 00 00 */	cmplwi r0, 0
/* 80221478 0021E058  41 82 00 08 */	beq .L_80221480
/* 8022147C 0021E05C  90 1F 00 1C */	stw r0, 0x1c(r31)
.L_80221480:
/* 80221480 0021E060  81 9D 00 00 */	lwz r12, 0(r29)
/* 80221484 0021E064  28 0C 00 00 */	cmplwi r12, 0
/* 80221488 0021E068  41 82 00 10 */	beq .L_80221498
/* 8022148C 0021E06C  7D 88 03 A6 */	mtlr r12
/* 80221490 0021E070  38 7E 00 00 */	addi r3, r30, 0
/* 80221494 0021E074  4E 80 00 21 */	blrl
.L_80221498:
/* 80221498 0021E078  80 9D 00 08 */	lwz r4, 8(r29)
/* 8022149C 0021E07C  28 04 00 00 */	cmplwi r4, 0
/* 802214A0 0021E080  41 82 00 2C */	beq .L_802214CC
/* 802214A4 0021E084  38 7E 00 00 */	addi r3, r30, 0
/* 802214A8 0021E088  38 A0 00 04 */	li r5, 4
/* 802214AC 0021E08C  48 16 E8 A9 */	bl func_8038FD54
/* 802214B0 0021E090  48 00 00 1C */	b .L_802214CC
.L_802214B4:
/* 802214B4 0021E094  38 DC 00 00 */	addi r6, r28, 0
/* 802214B8 0021E098  4C C6 31 82 */	crclr 6
/* 802214BC 0021E09C  38 7F 00 90 */	addi r3, r31, 0x90
/* 802214C0 0021E0A0  38 9F 00 B4 */	addi r4, r31, 0xb4
/* 802214C4 0021E0A4  38 A0 00 C3 */	li r5, 0xc3
/* 802214C8 0021E0A8  48 12 41 E1 */	bl OSReport
.L_802214CC:
/* 802214CC 0021E0AC  7F C3 F3 78 */	mr r3, r30
/* 802214D0 0021E0B0  80 01 00 24 */	lwz r0, 0x24(r1)
/* 802214D4 0021E0B4  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 802214D8 0021E0B8  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 802214DC 0021E0BC  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 802214E0 0021E0C0  83 81 00 10 */	lwz r28, 0x10(r1)
/* 802214E4 0021E0C4  38 21 00 20 */	addi r1, r1, 0x20
/* 802214E8 0021E0C8  7C 08 03 A6 */	mtlr r0
/* 802214EC 0021E0CC  4E 80 00 20 */	blr
.global lbl_802214F0
lbl_802214F0:
/* 802214F0 0021E0D0  7C 08 02 A6 */	mflr r0
/* 802214F4 0021E0D4  38 A0 00 00 */	li r5, 0
/* 802214F8 0021E0D8  90 01 00 04 */	stw r0, 4(r1)
/* 802214FC 0021E0DC  94 21 FF F8 */	stwu r1, -8(r1)
/* 80221500 0021E0E0  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 80221504 0021E0E4  80 84 00 14 */	lwz r4, 0x14(r4)
/* 80221508 0021E0E8  4B FA 6C 31 */	bl func_801C8138
/* 8022150C 0021E0EC  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80221510 0021E0F0  38 21 00 08 */	addi r1, r1, 8
/* 80221514 0021E0F4  7C 08 03 A6 */	mtlr r0
/* 80221518 0021E0F8  4E 80 00 20 */	blr
.global lbl_8022151C
lbl_8022151C:
/* 8022151C 0021E0FC  38 60 00 00 */	li r3, 0
/* 80221520 0021E100  4E 80 00 20 */	blr
.global lbl_80221524
lbl_80221524:
/* 80221524 0021E104  4E 80 00 20 */	blr
.global lbl_80221528
lbl_80221528:
/* 80221528 0021E108  4E 80 00 20 */	blr
.global lbl_8022152C
lbl_8022152C:
/* 8022152C 0021E10C  7C 08 02 A6 */	mflr r0
/* 80221530 0021E110  90 01 00 04 */	stw r0, 4(r1)
/* 80221534 0021E114  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80221538 0021E118  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8022153C 0021E11C  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80221540 0021E120  7C 7E 1B 78 */	mr r30, r3
/* 80221544 0021E124  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80221548 0021E128  80 63 00 28 */	lwz r3, 0x28(r3)
/* 8022154C 0021E12C  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 80221550 0021E130  4B FA 19 81 */	bl func_801C2ED0
/* 80221554 0021E134  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 80221558 0021E138  38 7E 00 00 */	addi r3, r30, 0
/* 8022155C 0021E13C  38 A0 00 00 */	li r5, 0
/* 80221560 0021E140  4B FA 6B D9 */	bl func_801C8138
/* 80221564 0021E144  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80221568 0021E148  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8022156C 0021E14C  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80221570 0021E150  38 21 00 20 */	addi r1, r1, 0x20
/* 80221574 0021E154  7C 08 03 A6 */	mtlr r0
/* 80221578 0021E158  4E 80 00 20 */	blr
.global lbl_8022157C
lbl_8022157C:
/* 8022157C 0021E15C  38 60 00 00 */	li r3, 0
/* 80221580 0021E160  4E 80 00 20 */	blr
.global lbl_80221584
lbl_80221584:
/* 80221584 0021E164  7C 08 02 A6 */	mflr r0
/* 80221588 0021E168  90 01 00 04 */	stw r0, 4(r1)
/* 8022158C 0021E16C  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80221590 0021E170  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80221594 0021E174  7C 7F 1B 78 */	mr r31, r3
/* 80221598 0021E178  4B DF 00 5D */	bl func_800115F4
/* 8022159C 0021E17C  7F E3 FB 78 */	mr r3, r31
/* 802215A0 0021E180  4B FA 1A 41 */	bl func_801C2FE0
/* 802215A4 0021E184  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 802215A8 0021E188  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 802215AC 0021E18C  38 21 00 18 */	addi r1, r1, 0x18
/* 802215B0 0021E190  7C 08 03 A6 */	mtlr r0
/* 802215B4 0021E194  4E 80 00 20 */	blr
.global lbl_802215B8
lbl_802215B8:
/* 802215B8 0021E198  4E 80 00 20 */	blr
.global lbl_802215BC
lbl_802215BC:
/* 802215BC 0021E19C  7C 08 02 A6 */	mflr r0
/* 802215C0 0021E1A0  90 01 00 04 */	stw r0, 4(r1)
/* 802215C4 0021E1A4  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 802215C8 0021E1A8  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 802215CC 0021E1AC  93 C1 00 18 */	stw r30, 0x18(r1)
/* 802215D0 0021E1B0  7C 7E 1B 78 */	mr r30, r3
/* 802215D4 0021E1B4  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 802215D8 0021E1B8  80 63 00 28 */	lwz r3, 0x28(r3)
/* 802215DC 0021E1BC  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 802215E0 0021E1C0  4B FA 18 F1 */	bl func_801C2ED0
/* 802215E4 0021E1C4  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 802215E8 0021E1C8  38 7E 00 00 */	addi r3, r30, 0
/* 802215EC 0021E1CC  38 A0 00 00 */	li r5, 0
/* 802215F0 0021E1D0  4B FA 6B 49 */	bl func_801C8138
/* 802215F4 0021E1D4  80 01 00 24 */	lwz r0, 0x24(r1)
/* 802215F8 0021E1D8  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 802215FC 0021E1DC  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80221600 0021E1E0  38 21 00 20 */	addi r1, r1, 0x20
/* 80221604 0021E1E4  7C 08 03 A6 */	mtlr r0
/* 80221608 0021E1E8  4E 80 00 20 */	blr
.global lbl_8022160C
lbl_8022160C:
/* 8022160C 0021E1EC  38 60 00 00 */	li r3, 0
/* 80221610 0021E1F0  4E 80 00 20 */	blr
.global lbl_80221614
lbl_80221614:
/* 80221614 0021E1F4  7C 08 02 A6 */	mflr r0
/* 80221618 0021E1F8  90 01 00 04 */	stw r0, 4(r1)
/* 8022161C 0021E1FC  94 21 FF F8 */	stwu r1, -8(r1)
/* 80221620 0021E200  4B FA 19 C1 */	bl func_801C2FE0
/* 80221624 0021E204  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80221628 0021E208  38 21 00 08 */	addi r1, r1, 8
/* 8022162C 0021E20C  7C 08 03 A6 */	mtlr r0
/* 80221630 0021E210  4E 80 00 20 */	blr
.global lbl_80221634
lbl_80221634:
/* 80221634 0021E214  4E 80 00 20 */	blr
.global lbl_80221638
lbl_80221638:
/* 80221638 0021E218  38 60 00 00 */	li r3, 0
/* 8022163C 0021E21C  4E 80 00 20 */	blr
.global lbl_80221640
lbl_80221640:
/* 80221640 0021E220  38 60 00 01 */	li r3, 1
/* 80221644 0021E224  4E 80 00 20 */	blr


.section .data
    .balign 8
.global lbl_803E8BB0
lbl_803E8BB0:
    .4byte lbl_802214F0
    .4byte lbl_8022151C
    .4byte lbl_80221524
    .4byte lbl_80221528
    .4byte NULL
    .4byte lbl_802215BC
    .4byte lbl_8022160C
    .4byte lbl_80221614
    .4byte lbl_80221634
    .4byte NULL
    .4byte lbl_8022152C
    .4byte lbl_8022157C
    .4byte lbl_80221584
    .4byte lbl_802215B8
    .4byte 0xC0000000
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
.global lbl_803E8C00
lbl_803E8C00:
    .4byte 0x2F477254
    .4byte 0x4B622E64
    .4byte 0x61740000
.global lbl_803E8C0C
lbl_803E8C0C:
    .4byte 0x00000030
    .4byte lbl_803E8BB0
    .4byte lbl_803E8C00
    .4byte lbl_80221368
    .4byte func_80221364
    .4byte lbl_802213D8
    .4byte lbl_802213DC
    .4byte lbl_80221400
    .4byte lbl_80221638
    .4byte lbl_80221640
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
    .4byte 0x6772746B
    .4byte 0x69726279
    .4byte 0x2E630000
