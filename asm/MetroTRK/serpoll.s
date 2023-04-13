.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240

.global TRKTestForPacket
TRKTestForPacket:
/* 803274DC 003240BC  7C 08 02 A6 */	mflr r0
/* 803274E0 003240C0  90 01 00 04 */	stw r0, 4(r1)
/* 803274E4 003240C4  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 803274E8 003240C8  93 E1 00 14 */	stw r31, 0x14(r1)
/* 803274EC 003240CC  93 C1 00 10 */	stw r30, 0x10(r1)
/* 803274F0 003240D0  48 00 39 55 */	bl TRKPollUART
/* 803274F4 003240D4  7C 7E 1B 79 */	or. r30, r3, r3
/* 803274F8 003240D8  40 81 00 88 */	ble .L_80327580
/* 803274FC 003240DC  38 61 00 08 */	addi r3, r1, 8
/* 80327500 003240E0  38 81 00 0C */	addi r4, r1, 0xc
/* 80327504 003240E4  4B FF F8 11 */	bl TRKGetFreeBuffer
/* 80327508 003240E8  2C 1E 08 80 */	cmpwi r30, 0x880
/* 8032750C 003240EC  40 81 00 4C */	ble .L_80327558
/* 80327510 003240F0  48 00 00 2C */	b .L_8032753C
.L_80327514:
/* 80327514 003240F4  2C 1E 08 80 */	cmpwi r30, 0x880
/* 80327518 003240F8  40 81 00 0C */	ble .L_80327524
/* 8032751C 003240FC  3B E0 08 80 */	li r31, 0x880
/* 80327520 00324100  48 00 00 08 */	b .L_80327528
.L_80327524:
/* 80327524 00324104  7F DF F3 78 */	mr r31, r30
.L_80327528:
/* 80327528 00324108  80 61 00 0C */	lwz r3, 0xc(r1)
/* 8032752C 0032410C  38 9F 00 00 */	addi r4, r31, 0
/* 80327530 00324110  38 63 00 10 */	addi r3, r3, 0x10
/* 80327534 00324114  48 00 39 41 */	bl TRK_ReadUARTN
/* 80327538 00324118  7F DF F0 50 */	subf r30, r31, r30
.L_8032753C:
/* 8032753C 0032411C  2C 1E 00 00 */	cmpwi r30, 0
/* 80327540 00324120  41 81 FF D4 */	bgt .L_80327514
/* 80327544 00324124  80 61 00 0C */	lwz r3, 0xc(r1)
/* 80327548 00324128  38 80 00 FF */	li r4, 0xff
/* 8032754C 0032412C  38 A0 00 06 */	li r5, 6
/* 80327550 00324130  48 00 02 D9 */	bl TRKStandardACK
/* 80327554 00324134  48 00 00 2C */	b .L_80327580
.L_80327558:
/* 80327558 00324138  80 61 00 0C */	lwz r3, 0xc(r1)
/* 8032755C 0032413C  38 9E 00 00 */	addi r4, r30, 0
/* 80327560 00324140  38 63 00 10 */	addi r3, r3, 0x10
/* 80327564 00324144  48 00 39 11 */	bl TRK_ReadUARTN
/* 80327568 00324148  2C 03 00 00 */	cmpwi r3, 0
/* 8032756C 0032414C  40 82 00 14 */	bne .L_80327580
/* 80327570 00324150  80 61 00 0C */	lwz r3, 0xc(r1)
/* 80327574 00324154  93 C3 00 08 */	stw r30, 8(r3)
/* 80327578 00324158  80 61 00 08 */	lwz r3, 8(r1)
/* 8032757C 0032415C  48 00 00 18 */	b .L_80327594
.L_80327580:
/* 80327580 00324160  80 61 00 08 */	lwz r3, 8(r1)
/* 80327584 00324164  2C 03 FF FF */	cmpwi r3, -1
/* 80327588 00324168  41 82 00 08 */	beq .L_80327590
/* 8032758C 0032416C  4B FF F8 51 */	bl TRKReleaseBuffer
.L_80327590:
/* 80327590 00324170  38 60 FF FF */	li r3, -1
.L_80327594:
/* 80327594 00324174  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80327598 00324178  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8032759C 0032417C  38 21 00 18 */	addi r1, r1, 0x18
/* 803275A0 00324180  80 01 00 04 */	lwz r0, 4(r1)
/* 803275A4 00324184  7C 08 03 A6 */	mtlr r0
/* 803275A8 00324188  4E 80 00 20 */	blr

.global TRKGetInput
TRKGetInput:
/* 803275AC 0032418C  7C 08 02 A6 */	mflr r0
/* 803275B0 00324190  90 01 00 04 */	stw r0, 4(r1)
/* 803275B4 00324194  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 803275B8 00324198  93 E1 00 14 */	stw r31, 0x14(r1)
/* 803275BC 0032419C  93 C1 00 10 */	stw r30, 0x10(r1)
/* 803275C0 003241A0  4B FF FF 1D */	bl TRKTestForPacket
/* 803275C4 003241A4  3B C3 00 00 */	addi r30, r3, 0
/* 803275C8 003241A8  2C 1E FF FF */	cmpwi r30, -1
/* 803275CC 003241AC  41 82 00 44 */	beq .L_80327610
/* 803275D0 003241B0  7F C3 F3 78 */	mr r3, r30
/* 803275D4 003241B4  4B FF F7 DD */	bl TRKGetBuffer
/* 803275D8 003241B8  3B E3 00 00 */	addi r31, r3, 0
/* 803275DC 003241BC  38 80 00 00 */	li r4, 0
/* 803275E0 003241C0  4B FF F8 A5 */	bl TRKSetBufferPosition
/* 803275E4 003241C4  38 7F 00 00 */	addi r3, r31, 0
/* 803275E8 003241C8  38 81 00 08 */	addi r4, r1, 8
/* 803275EC 003241CC  4B FF FC 1D */	bl TRKReadBuffer1_ui8
/* 803275F0 003241D0  88 01 00 08 */	lbz r0, 8(r1)
/* 803275F4 003241D4  28 00 00 80 */	cmplwi r0, 0x80
/* 803275F8 003241D8  40 80 00 10 */	bge .L_80327608
/* 803275FC 003241DC  7F C3 F3 78 */	mr r3, r30
/* 80327600 003241E0  48 00 00 29 */	bl TRKProcessInput
/* 80327604 003241E4  48 00 00 0C */	b .L_80327610
.L_80327608:
/* 80327608 003241E8  7F C3 F3 78 */	mr r3, r30
/* 8032760C 003241EC  4B FF F7 D1 */	bl TRKReleaseBuffer
.L_80327610:
/* 80327610 003241F0  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80327614 003241F4  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 80327618 003241F8  38 21 00 18 */	addi r1, r1, 0x18
/* 8032761C 003241FC  80 01 00 04 */	lwz r0, 4(r1)
/* 80327620 00324200  7C 08 03 A6 */	mtlr r0
/* 80327624 00324204  4E 80 00 20 */	blr

.global TRKProcessInput
TRKProcessInput:
/* 80327628 00324208  7C 08 02 A6 */	mflr r0
/* 8032762C 0032420C  38 80 00 02 */	li r4, 2
/* 80327630 00324210  90 01 00 04 */	stw r0, 4(r1)
/* 80327634 00324214  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80327638 00324218  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8032763C 0032421C  3B E3 00 00 */	addi r31, r3, 0
/* 80327640 00324220  38 61 00 08 */	addi r3, r1, 8
/* 80327644 00324224  4B FF F4 59 */	bl TRKConstructEvent
/* 80327648 00324228  3C 60 80 4A */	lis r3, gTRKFramingState@ha
/* 8032764C 0032422C  93 E1 00 10 */	stw r31, 0x10(r1)
/* 80327650 00324230  38 83 4B 28 */	addi r4, r3, gTRKFramingState@l
/* 80327654 00324234  38 61 00 08 */	addi r3, r1, 8
/* 80327658 00324238  38 00 FF FF */	li r0, -1
/* 8032765C 0032423C  90 04 00 00 */	stw r0, 0(r4)
/* 80327660 00324240  4B FF F3 5D */	bl TRKPostEvent
/* 80327664 00324244  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80327668 00324248  38 21 00 18 */	addi r1, r1, 0x18
/* 8032766C 0032424C  80 01 00 04 */	lwz r0, 4(r1)
/* 80327670 00324250  7C 08 03 A6 */	mtlr r0
/* 80327674 00324254  4E 80 00 20 */	blr

.global TRKInitializeSerialHandler
TRKInitializeSerialHandler:
/* 80327678 00324258  3C 60 80 4A */	lis r3, gTRKFramingState@ha
/* 8032767C 0032425C  38 83 4B 28 */	addi r4, r3, gTRKFramingState@l
/* 80327680 00324260  38 00 FF FF */	li r0, -1
/* 80327684 00324264  90 04 00 00 */	stw r0, 0(r4)
/* 80327688 00324268  38 00 00 00 */	li r0, 0
/* 8032768C 0032426C  38 60 00 00 */	li r3, 0
/* 80327690 00324270  98 04 00 08 */	stb r0, 8(r4)
/* 80327694 00324274  90 04 00 0C */	stw r0, 0xc(r4)
/* 80327698 00324278  4E 80 00 20 */	blr

.global TRKTerminateSerialHandler
TRKTerminateSerialHandler:
/* 8032769C 0032427C  38 60 00 00 */	li r3, 0
/* 803276A0 00324280  4E 80 00 20 */	blr

.global usr_put_initialize
usr_put_initialize:
/* 803276A4 00324284  4E 80 00 20 */	blr
