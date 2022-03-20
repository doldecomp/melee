.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240

.global func_802243F4
func_802243F4:
/* 802243F4 00220FD4  4E 80 00 20 */	blr 
.global lbl_802243F8
lbl_802243F8:
/* 802243F8 00220FD8  7C 08 02 A6 */	mflr r0
/* 802243FC 00220FDC  3C 60 80 4A */	lis r3, stage_info@ha
/* 80224400 00220FE0  90 01 00 04 */	stw r0, 4(r1)
/* 80224404 00220FE4  38 63 E6 C8 */	addi r3, r3, stage_info@l
/* 80224408 00220FE8  38 A3 00 8C */	addi r5, r3, 0x8c
/* 8022440C 00220FEC  94 21 FF F8 */	stwu r1, -8(r1)
/* 80224410 00220FF0  38 80 00 01 */	li r4, 1
/* 80224414 00220FF4  88 03 00 8C */	lbz r0, 0x8c(r3)
/* 80224418 00220FF8  38 60 00 00 */	li r3, 0
/* 8022441C 00220FFC  50 60 1F 38 */	rlwimi r0, r3, 3, 0x1c, 0x1c
/* 80224420 00221000  98 05 00 00 */	stb r0, 0(r5)
/* 80224424 00221004  38 60 00 00 */	li r3, 0
/* 80224428 00221008  88 05 00 00 */	lbz r0, 0(r5)
/* 8022442C 0022100C  50 80 17 7A */	rlwimi r0, r4, 2, 0x1d, 0x1d
/* 80224430 00221010  98 05 00 00 */	stb r0, 0(r5)
/* 80224434 00221014  48 00 00 65 */	bl func_80224498
/* 80224438 00221018  38 60 00 01 */	li r3, 1
/* 8022443C 0022101C  48 00 00 5D */	bl func_80224498
/* 80224440 00221020  38 60 00 02 */	li r3, 2
/* 80224444 00221024  48 00 00 55 */	bl func_80224498
/* 80224448 00221028  4B F9 F5 79 */	bl func_801C39C0
/* 8022444C 0022102C  4B F9 F7 69 */	bl func_801C3BB4
/* 80224450 00221030  4B F9 FD C1 */	bl func_801C4210
/* 80224454 00221034  4B F9 FE 59 */	bl func_801C42AC
/* 80224458 00221038  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8022445C 0022103C  38 21 00 08 */	addi r1, r1, 8
/* 80224460 00221040  7C 08 03 A6 */	mtlr r0
/* 80224464 00221044  4E 80 00 20 */	blr 
.global lbl_80224468
lbl_80224468:
/* 80224468 00221048  4E 80 00 20 */	blr 
.global lbl_8022446C
lbl_8022446C:
/* 8022446C 0022104C  7C 08 02 A6 */	mflr r0
/* 80224470 00221050  38 60 00 00 */	li r3, 0
/* 80224474 00221054  90 01 00 04 */	stw r0, 4(r1)
/* 80224478 00221058  94 21 FF F8 */	stwu r1, -8(r1)
/* 8022447C 0022105C  4B FA 69 89 */	bl func_801CAE04
/* 80224480 00221060  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80224484 00221064  38 21 00 08 */	addi r1, r1, 8
/* 80224488 00221068  7C 08 03 A6 */	mtlr r0
/* 8022448C 0022106C  4E 80 00 20 */	blr 
.global lbl_80224490
lbl_80224490:
/* 80224490 00221070  38 60 00 00 */	li r3, 0
/* 80224494 00221074  4E 80 00 20 */	blr 

.global func_80224498
func_80224498:
/* 80224498 00221078  7C 08 02 A6 */	mflr r0
/* 8022449C 0022107C  90 01 00 04 */	stw r0, 4(r1)
/* 802244A0 00221080  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 802244A4 00221084  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 802244A8 00221088  93 C1 00 18 */	stw r30, 0x18(r1)
/* 802244AC 0022108C  93 A1 00 14 */	stw r29, 0x14(r1)
/* 802244B0 00221090  93 81 00 10 */	stw r28, 0x10(r1)
/* 802244B4 00221094  3B 83 00 00 */	addi r28, r3, 0
/* 802244B8 00221098  1C 1C 00 14 */	mulli r0, r28, 0x14
/* 802244BC 0022109C  3C 60 80 3F */	lis r3, lbl_803E97C0@ha
/* 802244C0 002210A0  3B E3 97 C0 */	addi r31, r3, lbl_803E97C0@l
/* 802244C4 002210A4  38 7C 00 00 */	addi r3, r28, 0
/* 802244C8 002210A8  7F BF 02 14 */	add r29, r31, r0
/* 802244CC 002210AC  4B F9 D0 05 */	bl func_801C14D0
/* 802244D0 002210B0  7C 7E 1B 79 */	or. r30, r3, r3
/* 802244D4 002210B4  41 82 00 70 */	beq lbl_80224544
/* 802244D8 002210B8  83 FE 00 2C */	lwz r31, 0x2c(r30)
/* 802244DC 002210BC  38 00 00 00 */	li r0, 0
/* 802244E0 002210C0  3C 60 80 1C */	lis r3, func_801C5DB0@ha
/* 802244E4 002210C4  90 1F 00 08 */	stw r0, 8(r31)
/* 802244E8 002210C8  38 83 5D B0 */	addi r4, r3, func_801C5DB0@l
/* 802244EC 002210CC  38 7E 00 00 */	addi r3, r30, 0
/* 802244F0 002210D0  90 1F 00 0C */	stw r0, 0xc(r31)
/* 802244F4 002210D4  38 A0 00 03 */	li r5, 3
/* 802244F8 002210D8  38 C0 00 00 */	li r6, 0
/* 802244FC 002210DC  48 16 C1 A1 */	bl GObj_SetupGXLink
/* 80224500 002210E0  80 1D 00 0C */	lwz r0, 0xc(r29)
/* 80224504 002210E4  28 00 00 00 */	cmplwi r0, 0
/* 80224508 002210E8  41 82 00 08 */	beq lbl_80224510
/* 8022450C 002210EC  90 1F 00 1C */	stw r0, 0x1c(r31)
lbl_80224510:
/* 80224510 002210F0  81 9D 00 00 */	lwz r12, 0(r29)
/* 80224514 002210F4  28 0C 00 00 */	cmplwi r12, 0
/* 80224518 002210F8  41 82 00 10 */	beq lbl_80224528
/* 8022451C 002210FC  7D 88 03 A6 */	mtlr r12
/* 80224520 00221100  38 7E 00 00 */	addi r3, r30, 0
/* 80224524 00221104  4E 80 00 21 */	blrl 
lbl_80224528:
/* 80224528 00221108  80 9D 00 08 */	lwz r4, 8(r29)
/* 8022452C 0022110C  28 04 00 00 */	cmplwi r4, 0
/* 80224530 00221110  41 82 00 2C */	beq lbl_8022455C
/* 80224534 00221114  38 7E 00 00 */	addi r3, r30, 0
/* 80224538 00221118  38 A0 00 04 */	li r5, 4
/* 8022453C 0022111C  48 16 B8 19 */	bl func_8038FD54
/* 80224540 00221120  48 00 00 1C */	b lbl_8022455C
lbl_80224544:
/* 80224544 00221124  38 DC 00 00 */	addi r6, r28, 0
/* 80224548 00221128  4C C6 31 82 */	crclr 6
/* 8022454C 0022112C  38 7F 00 90 */	addi r3, r31, 0x90
/* 80224550 00221130  38 9F 00 B4 */	addi r4, r31, 0xb4
/* 80224554 00221134  38 A0 00 C3 */	li r5, 0xc3
/* 80224558 00221138  48 12 11 51 */	bl OSReport
lbl_8022455C:
/* 8022455C 0022113C  7F C3 F3 78 */	mr r3, r30
/* 80224560 00221140  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80224564 00221144  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80224568 00221148  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8022456C 0022114C  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 80224570 00221150  83 81 00 10 */	lwz r28, 0x10(r1)
/* 80224574 00221154  38 21 00 20 */	addi r1, r1, 0x20
/* 80224578 00221158  7C 08 03 A6 */	mtlr r0
/* 8022457C 0022115C  4E 80 00 20 */	blr 
.global lbl_80224580
lbl_80224580:
/* 80224580 00221160  7C 08 02 A6 */	mflr r0
/* 80224584 00221164  38 A0 00 00 */	li r5, 0
/* 80224588 00221168  90 01 00 04 */	stw r0, 4(r1)
/* 8022458C 0022116C  94 21 FF F8 */	stwu r1, -8(r1)
/* 80224590 00221170  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 80224594 00221174  80 84 00 14 */	lwz r4, 0x14(r4)
/* 80224598 00221178  4B FA 3B A1 */	bl func_801C8138
/* 8022459C 0022117C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802245A0 00221180  38 21 00 08 */	addi r1, r1, 8
/* 802245A4 00221184  7C 08 03 A6 */	mtlr r0
/* 802245A8 00221188  4E 80 00 20 */	blr 
.global lbl_802245AC
lbl_802245AC:
/* 802245AC 0022118C  38 60 00 00 */	li r3, 0
/* 802245B0 00221190  4E 80 00 20 */	blr 
.global lbl_802245B4
lbl_802245B4:
/* 802245B4 00221194  4E 80 00 20 */	blr 
.global lbl_802245B8
lbl_802245B8:
/* 802245B8 00221198  4E 80 00 20 */	blr 
.global lbl_802245BC
lbl_802245BC:
/* 802245BC 0022119C  7C 08 02 A6 */	mflr r0
/* 802245C0 002211A0  90 01 00 04 */	stw r0, 4(r1)
/* 802245C4 002211A4  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 802245C8 002211A8  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 802245CC 002211AC  93 C1 00 18 */	stw r30, 0x18(r1)
/* 802245D0 002211B0  7C 7E 1B 78 */	mr r30, r3
/* 802245D4 002211B4  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 802245D8 002211B8  80 63 00 28 */	lwz r3, 0x28(r3)
/* 802245DC 002211BC  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 802245E0 002211C0  4B F9 E8 F1 */	bl func_801C2ED0
/* 802245E4 002211C4  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 802245E8 002211C8  38 7E 00 00 */	addi r3, r30, 0
/* 802245EC 002211CC  38 A0 00 00 */	li r5, 0
/* 802245F0 002211D0  4B FA 3B 49 */	bl func_801C8138
/* 802245F4 002211D4  80 01 00 24 */	lwz r0, 0x24(r1)
/* 802245F8 002211D8  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 802245FC 002211DC  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80224600 002211E0  38 21 00 20 */	addi r1, r1, 0x20
/* 80224604 002211E4  7C 08 03 A6 */	mtlr r0
/* 80224608 002211E8  4E 80 00 20 */	blr 
.global lbl_8022460C
lbl_8022460C:
/* 8022460C 002211EC  38 60 00 00 */	li r3, 0
/* 80224610 002211F0  4E 80 00 20 */	blr 
.global lbl_80224614
lbl_80224614:
/* 80224614 002211F4  7C 08 02 A6 */	mflr r0
/* 80224618 002211F8  90 01 00 04 */	stw r0, 4(r1)
/* 8022461C 002211FC  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80224620 00221200  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80224624 00221204  7C 7F 1B 78 */	mr r31, r3
/* 80224628 00221208  4B DE CF CD */	bl func_800115F4
/* 8022462C 0022120C  7F E3 FB 78 */	mr r3, r31
/* 80224630 00221210  4B F9 E9 B1 */	bl func_801C2FE0
/* 80224634 00221214  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80224638 00221218  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8022463C 0022121C  38 21 00 18 */	addi r1, r1, 0x18
/* 80224640 00221220  7C 08 03 A6 */	mtlr r0
/* 80224644 00221224  4E 80 00 20 */	blr 
.global lbl_80224648
lbl_80224648:
/* 80224648 00221228  4E 80 00 20 */	blr 
.global lbl_8022464C
lbl_8022464C:
/* 8022464C 0022122C  7C 08 02 A6 */	mflr r0
/* 80224650 00221230  90 01 00 04 */	stw r0, 4(r1)
/* 80224654 00221234  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80224658 00221238  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8022465C 0022123C  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80224660 00221240  7C 7E 1B 78 */	mr r30, r3
/* 80224664 00221244  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80224668 00221248  80 63 00 28 */	lwz r3, 0x28(r3)
/* 8022466C 0022124C  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 80224670 00221250  4B F9 E8 61 */	bl func_801C2ED0
/* 80224674 00221254  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 80224678 00221258  38 7E 00 00 */	addi r3, r30, 0
/* 8022467C 0022125C  38 A0 00 00 */	li r5, 0
/* 80224680 00221260  4B FA 3A B9 */	bl func_801C8138
/* 80224684 00221264  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80224688 00221268  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8022468C 0022126C  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80224690 00221270  38 21 00 20 */	addi r1, r1, 0x20
/* 80224694 00221274  7C 08 03 A6 */	mtlr r0
/* 80224698 00221278  4E 80 00 20 */	blr 
.global lbl_8022469C
lbl_8022469C:
/* 8022469C 0022127C  38 60 00 00 */	li r3, 0
/* 802246A0 00221280  4E 80 00 20 */	blr 
.global lbl_802246A4
lbl_802246A4:
/* 802246A4 00221284  7C 08 02 A6 */	mflr r0
/* 802246A8 00221288  90 01 00 04 */	stw r0, 4(r1)
/* 802246AC 0022128C  94 21 FF F8 */	stwu r1, -8(r1)
/* 802246B0 00221290  4B F9 E9 31 */	bl func_801C2FE0
/* 802246B4 00221294  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802246B8 00221298  38 21 00 08 */	addi r1, r1, 8
/* 802246BC 0022129C  7C 08 03 A6 */	mtlr r0
/* 802246C0 002212A0  4E 80 00 20 */	blr 
.global lbl_802246C4
lbl_802246C4:
/* 802246C4 002212A4  4E 80 00 20 */	blr 
.global lbl_802246C8
lbl_802246C8:
/* 802246C8 002212A8  38 60 00 00 */	li r3, 0
/* 802246CC 002212AC  4E 80 00 20 */	blr 
.global lbl_802246D0
lbl_802246D0:
/* 802246D0 002212B0  38 60 00 01 */	li r3, 1
/* 802246D4 002212B4  4E 80 00 20 */	blr 


.section .data
    .balign 8
.global lbl_803E97C0
lbl_803E97C0:
	.4byte lbl_80224580
	.4byte lbl_802245AC
	.4byte lbl_802245B4
	.4byte lbl_802245B8
    .4byte NULL
	.4byte lbl_8022464C
	.4byte lbl_8022469C
	.4byte lbl_802246A4
	.4byte lbl_802246C4
    .4byte NULL
	.4byte lbl_802245BC
	.4byte lbl_8022460C
	.4byte lbl_80224614
	.4byte lbl_80224648
    .4byte 0xC0000000
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
.global lbl_803E9810
lbl_803E9810:
    .asciz "/GrTFe.dat"
    .balign 4
.global lbl_803E981C
lbl_803E981C:
    .4byte 0x00000040
    .4byte lbl_803E97C0
    .4byte lbl_803E9810
	.4byte lbl_802243F8
	.4byte func_802243F4
	.4byte lbl_80224468
	.4byte lbl_8022446C
	.4byte lbl_80224490
	.4byte lbl_802246C8
	.4byte lbl_802246D0
    .4byte 0x00000001
    .4byte NULL
    .4byte NULL
    .asciz "%s:%d: couldn t get gobj(id=%d)\n"
    .balign 4
    .asciz "grtemblem.c"
