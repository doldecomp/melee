.include "macros.inc"

.section .text

.global it_802BD32C
it_802BD32C:
/* 802BD32C 002B9F0C  7C 08 02 A6 */	mflr r0
/* 802BD330 002B9F10  38 E0 00 00 */	li r7, 0
/* 802BD334 002B9F14  90 01 00 04 */	stw r0, 4(r1)
/* 802BD338 002B9F18  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 802BD33C 002B9F1C  93 E1 00 24 */	stw r31, 0x24(r1)
/* 802BD340 002B9F20  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 802BD344 002B9F24  38 60 00 00 */	li r3, 0
/* 802BD348 002B9F28  80 84 00 C4 */	lwz r4, 0xc4(r4)
/* 802BD34C 002B9F2C  80 84 00 04 */	lwz r4, 4(r4)
/* 802BD350 002B9F30  80 C4 00 04 */	lwz r6, 4(r4)
/* 802BD354 002B9F34  3B E4 00 00 */	addi r31, r4, 0
/* 802BD358 002B9F38  2C 06 00 00 */	cmpwi r6, 0
/* 802BD35C 002B9F3C  40 81 00 90 */	ble .L_802BD3EC
/* 802BD360 002B9F40  2C 06 00 08 */	cmpwi r6, 8
/* 802BD364 002B9F44  38 86 FF F8 */	addi r4, r6, -8
/* 802BD368 002B9F48  40 81 00 D4 */	ble .L_802BD43C
/* 802BD36C 002B9F4C  38 04 00 07 */	addi r0, r4, 7
/* 802BD370 002B9F50  54 00 E8 FE */	srwi r0, r0, 3
/* 802BD374 002B9F54  2C 04 00 00 */	cmpwi r4, 0
/* 802BD378 002B9F58  7C 09 03 A6 */	mtctr r0
/* 802BD37C 002B9F5C  38 BF 00 00 */	addi r5, r31, 0
/* 802BD380 002B9F60  40 81 00 BC */	ble .L_802BD43C
.L_802BD384:
/* 802BD384 002B9F64  80 85 00 08 */	lwz r4, 8(r5)
/* 802BD388 002B9F68  38 E7 00 08 */	addi r7, r7, 8
/* 802BD38C 002B9F6C  80 05 00 10 */	lwz r0, 0x10(r5)
/* 802BD390 002B9F70  7C 63 22 14 */	add r3, r3, r4
/* 802BD394 002B9F74  80 85 00 18 */	lwz r4, 0x18(r5)
/* 802BD398 002B9F78  7C 63 02 14 */	add r3, r3, r0
/* 802BD39C 002B9F7C  80 05 00 20 */	lwz r0, 0x20(r5)
/* 802BD3A0 002B9F80  7C 63 22 14 */	add r3, r3, r4
/* 802BD3A4 002B9F84  80 85 00 28 */	lwz r4, 0x28(r5)
/* 802BD3A8 002B9F88  7C 63 02 14 */	add r3, r3, r0
/* 802BD3AC 002B9F8C  80 05 00 30 */	lwz r0, 0x30(r5)
/* 802BD3B0 002B9F90  7C 63 22 14 */	add r3, r3, r4
/* 802BD3B4 002B9F94  80 85 00 38 */	lwz r4, 0x38(r5)
/* 802BD3B8 002B9F98  7C 63 02 14 */	add r3, r3, r0
/* 802BD3BC 002B9F9C  84 05 00 40 */	lwzu r0, 0x40(r5)
/* 802BD3C0 002B9FA0  7C 63 22 14 */	add r3, r3, r4
/* 802BD3C4 002B9FA4  7C 63 02 14 */	add r3, r3, r0
/* 802BD3C8 002B9FA8  42 00 FF BC */	bdnz .L_802BD384
/* 802BD3CC 002B9FAC  48 00 00 70 */	b .L_802BD43C
.L_802BD3D0:
/* 802BD3D0 002B9FB0  7C 07 30 50 */	subf r0, r7, r6
/* 802BD3D4 002B9FB4  7C 07 30 00 */	cmpw r7, r6
/* 802BD3D8 002B9FB8  7C 09 03 A6 */	mtctr r0
/* 802BD3DC 002B9FBC  40 80 00 10 */	bge .L_802BD3EC
.L_802BD3E0:
/* 802BD3E0 002B9FC0  84 04 00 08 */	lwzu r0, 8(r4)
/* 802BD3E4 002B9FC4  7C 63 02 14 */	add r3, r3, r0
/* 802BD3E8 002B9FC8  42 00 FF F8 */	bdnz .L_802BD3E0
.L_802BD3EC:
/* 802BD3EC 002B9FCC  48 0C 31 95 */	bl HSD_Randi
/* 802BD3F0 002B9FD0  80 FF 00 08 */	lwz r7, 8(r31)
/* 802BD3F4 002B9FD4  7F E4 FB 78 */	mr r4, r31
/* 802BD3F8 002B9FD8  80 BF 00 04 */	lwz r5, 4(r31)
/* 802BD3FC 002B9FDC  39 00 FF FF */	li r8, -1
/* 802BD400 002B9FE0  38 C0 00 00 */	li r6, 0
/* 802BD404 002B9FE4  48 00 00 20 */	b .L_802BD424
.L_802BD408:
/* 802BD408 002B9FE8  7C 03 38 00 */	cmpw r3, r7
/* 802BD40C 002B9FEC  40 80 00 08 */	bge .L_802BD414
/* 802BD410 002B9FF0  7C C8 33 78 */	mr r8, r6
.L_802BD414:
/* 802BD414 002B9FF4  80 04 00 10 */	lwz r0, 0x10(r4)
/* 802BD418 002B9FF8  38 84 00 08 */	addi r4, r4, 8
/* 802BD41C 002B9FFC  38 C6 00 01 */	addi r6, r6, 1
/* 802BD420 002BA000  7C E7 02 14 */	add r7, r7, r0
.L_802BD424:
/* 802BD424 002BA004  7C 06 28 00 */	cmpw r6, r5
/* 802BD428 002BA008  40 80 00 0C */	bge .L_802BD434
/* 802BD42C 002BA00C  2C 08 FF FF */	cmpwi r8, -1
/* 802BD430 002BA010  41 82 FF D8 */	beq .L_802BD408
.L_802BD434:
/* 802BD434 002BA014  7D 03 43 78 */	mr r3, r8
/* 802BD438 002BA018  48 00 00 10 */	b .L_802BD448
.L_802BD43C:
/* 802BD43C 002BA01C  54 E0 18 38 */	slwi r0, r7, 3
/* 802BD440 002BA020  7C 9F 02 14 */	add r4, r31, r0
/* 802BD444 002BA024  4B FF FF 8C */	b .L_802BD3D0
.L_802BD448:
/* 802BD448 002BA028  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 802BD44C 002BA02C  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 802BD450 002BA030  38 21 00 28 */	addi r1, r1, 0x28
/* 802BD454 002BA034  7C 08 03 A6 */	mtlr r0
/* 802BD458 002BA038  4E 80 00 20 */	blr

.global it_802BD45C
it_802BD45C:
/* 802BD45C 002BA03C  7C 08 02 A6 */	mflr r0
/* 802BD460 002BA040  90 01 00 04 */	stw r0, 4(r1)
/* 802BD464 002BA044  94 21 FF F8 */	stwu r1, -8(r1)
/* 802BD468 002BA048  4B FA D4 85 */	bl Item_8026A8EC
/* 802BD46C 002BA04C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802BD470 002BA050  38 21 00 08 */	addi r1, r1, 8
/* 802BD474 002BA054  7C 08 03 A6 */	mtlr r0
/* 802BD478 002BA058  4E 80 00 20 */	blr

.global it_802BD47C
it_802BD47C:
/* 802BD47C 002BA05C  7C 08 02 A6 */	mflr r0
/* 802BD480 002BA060  90 01 00 04 */	stw r0, 4(r1)
/* 802BD484 002BA064  94 21 FF F8 */	stwu r1, -8(r1)
/* 802BD488 002BA068  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 802BD48C 002BA06C  80 63 0D E4 */	lwz r3, 0xde4(r3)
/* 802BD490 002BA070  28 03 00 00 */	cmplwi r3, 0
/* 802BD494 002BA074  41 82 00 08 */	beq .L_802BD49C
/* 802BD498 002BA078  4B E5 FA ED */	bl ftPe_SpecialLw_UnsetVeg
.L_802BD49C:
/* 802BD49C 002BA07C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802BD4A0 002BA080  38 21 00 08 */	addi r1, r1, 8
/* 802BD4A4 002BA084  7C 08 03 A6 */	mtlr r0
/* 802BD4A8 002BA088  4E 80 00 20 */	blr

.global it_802BD4AC
it_802BD4AC:
/* 802BD4AC 002BA08C  7C 08 02 A6 */	mflr r0
/* 802BD4B0 002BA090  90 01 00 04 */	stw r0, 4(r1)
/* 802BD4B4 002BA094  94 21 FF 70 */	stwu r1, -0x90(r1)
/* 802BD4B8 002BA098  BF 21 00 74 */	stmw r25, 0x74(r1)
/* 802BD4BC 002BA09C  7C DF 33 78 */	mr r31, r6
/* 802BD4C0 002BA0A0  3B A3 00 00 */	addi r29, r3, 0
/* 802BD4C4 002BA0A4  3B 80 00 00 */	li r28, 0
/* 802BD4C8 002BA0A8  38 C0 00 01 */	li r6, 1
/* 802BD4CC 002BA0AC  7C BE 2B 78 */	mr r30, r5
/* 802BD4D0 002BA0B0  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 802BD4D4 002BA0B4  80 64 00 00 */	lwz r3, 0(r4)
/* 802BD4D8 002BA0B8  80 04 00 04 */	lwz r0, 4(r4)
/* 802BD4DC 002BA0BC  90 61 00 44 */	stw r3, 0x44(r1)
/* 802BD4E0 002BA0C0  38 61 00 24 */	addi r3, r1, 0x24
/* 802BD4E4 002BA0C4  90 01 00 48 */	stw r0, 0x48(r1)
/* 802BD4E8 002BA0C8  80 04 00 08 */	lwz r0, 8(r4)
/* 802BD4EC 002BA0CC  90 01 00 4C */	stw r0, 0x4c(r1)
/* 802BD4F0 002BA0D0  80 81 00 44 */	lwz r4, 0x44(r1)
/* 802BD4F4 002BA0D4  80 01 00 48 */	lwz r0, 0x48(r1)
/* 802BD4F8 002BA0D8  C0 02 D7 24 */	lfs f0, it_804DD104@sda21(r2)
/* 802BD4FC 002BA0DC  90 81 00 38 */	stw r4, 0x38(r1)
/* 802BD500 002BA0E0  90 01 00 3C */	stw r0, 0x3c(r1)
/* 802BD504 002BA0E4  80 01 00 4C */	lwz r0, 0x4c(r1)
/* 802BD508 002BA0E8  90 01 00 40 */	stw r0, 0x40(r1)
/* 802BD50C 002BA0EC  D0 21 00 5C */	stfs f1, 0x5c(r1)
/* 802BD510 002BA0F0  B3 81 00 60 */	sth r28, 0x60(r1)
/* 802BD514 002BA0F4  D0 01 00 58 */	stfs f0, 0x58(r1)
/* 802BD518 002BA0F8  D0 01 00 54 */	stfs f0, 0x54(r1)
/* 802BD51C 002BA0FC  D0 01 00 50 */	stfs f0, 0x50(r1)
/* 802BD520 002BA100  93 A1 00 24 */	stw r29, 0x24(r1)
/* 802BD524 002BA104  80 01 00 24 */	lwz r0, 0x24(r1)
/* 802BD528 002BA108  90 01 00 28 */	stw r0, 0x28(r1)
/* 802BD52C 002BA10C  88 01 00 68 */	lbz r0, 0x68(r1)
/* 802BD530 002BA110  50 C0 3E 30 */	rlwimi r0, r6, 7, 0x18, 0x18
/* 802BD534 002BA114  98 01 00 68 */	stb r0, 0x68(r1)
/* 802BD538 002BA118  93 81 00 64 */	stw r28, 0x64(r1)
/* 802BD53C 002BA11C  4B FA B5 DD */	bl Item_80268B18
/* 802BD540 002BA120  7C 7B 1B 79 */	or. r27, r3, r3
/* 802BD544 002BA124  41 82 00 CC */	beq .L_802BD610
/* 802BD548 002BA128  2C 1F 00 63 */	cmpwi r31, 0x63
/* 802BD54C 002BA12C  83 5B 00 2C */	lwz r26, 0x2c(r27)
/* 802BD550 002BA130  40 82 00 54 */	bne .L_802BD5A4
/* 802BD554 002BA134  80 9A 00 C4 */	lwz r4, 0xc4(r26)
/* 802BD558 002BA138  7F 63 DB 78 */	mr r3, r27
/* 802BD55C 002BA13C  83 24 00 04 */	lwz r25, 4(r4)
/* 802BD560 002BA140  C0 39 00 00 */	lfs f1, 0(r25)
/* 802BD564 002BA144  4B FB 7B F5 */	bl it_80275158
/* 802BD568 002BA148  7F 63 DB 78 */	mr r3, r27
/* 802BD56C 002BA14C  4B FF FD C1 */	bl it_802BD32C
/* 802BD570 002BA150  90 7A 0D D8 */	stw r3, 0xdd8(r26)
/* 802BD574 002BA154  7F 63 DB 78 */	mr r3, r27
/* 802BD578 002BA158  80 1A 0D D8 */	lwz r0, 0xdd8(r26)
/* 802BD57C 002BA15C  54 00 18 38 */	slwi r0, r0, 3
/* 802BD580 002BA160  7C 99 02 14 */	add r4, r25, r0
/* 802BD584 002BA164  80 04 00 0C */	lwz r0, 0xc(r4)
/* 802BD588 002BA168  90 1A 0D DC */	stw r0, 0xddc(r26)
/* 802BD58C 002BA16C  88 1A 0D D4 */	lbz r0, 0xdd4(r26)
/* 802BD590 002BA170  53 80 3E 30 */	rlwimi r0, r28, 7, 0x18, 0x18
/* 802BD594 002BA174  98 1A 0D D4 */	stb r0, 0xdd4(r26)
/* 802BD598 002BA178  80 1A 05 18 */	lwz r0, 0x518(r26)
/* 802BD59C 002BA17C  90 1A 0D E4 */	stw r0, 0xde4(r26)
/* 802BD5A0 002BA180  4B FA E7 6D */	bl it_8026BD0C
.L_802BD5A4:
/* 802BD5A4 002BA184  38 7B 00 00 */	addi r3, r27, 0
/* 802BD5A8 002BA188  38 9D 00 00 */	addi r4, r29, 0
/* 802BD5AC 002BA18C  38 BE 00 00 */	addi r5, r30, 0
/* 802BD5B0 002BA190  4B FA D5 A5 */	bl Item_8026AB54
/* 802BD5B4 002BA194  2C 1F 00 0C */	cmpwi r31, 0xc
/* 802BD5B8 002BA198  41 82 00 58 */	beq .L_802BD610
/* 802BD5BC 002BA19C  7F 63 DB 78 */	mr r3, r27
/* 802BD5C0 002BA1A0  4B FB 6F D5 */	bl it_80274594
/* 802BD5C4 002BA1A4  80 7B 00 2C */	lwz r3, 0x2c(r27)
/* 802BD5C8 002BA1A8  80 03 00 10 */	lwz r0, 0x10(r3)
/* 802BD5CC 002BA1AC  2C 00 00 07 */	cmpwi r0, 7
/* 802BD5D0 002BA1B0  41 82 00 2C */	beq .L_802BD5FC
/* 802BD5D4 002BA1B4  40 80 00 10 */	bge .L_802BD5E4
/* 802BD5D8 002BA1B8  2C 00 00 06 */	cmpwi r0, 6
/* 802BD5DC 002BA1BC  40 80 00 14 */	bge .L_802BD5F0
/* 802BD5E0 002BA1C0  48 00 00 30 */	b .L_802BD610
.L_802BD5E4:
/* 802BD5E4 002BA1C4  2C 00 00 63 */	cmpwi r0, 0x63
/* 802BD5E8 002BA1C8  41 82 00 20 */	beq .L_802BD608
/* 802BD5EC 002BA1CC  48 00 00 24 */	b .L_802BD610
.L_802BD5F0:
/* 802BD5F0 002BA1D0  C0 03 00 38 */	lfs f0, 0x38(r3)
/* 802BD5F4 002BA1D4  D0 03 0D E8 */	stfs f0, 0xde8(r3)
/* 802BD5F8 002BA1D8  48 00 00 18 */	b .L_802BD610
.L_802BD5FC:
/* 802BD5FC 002BA1DC  C0 03 00 38 */	lfs f0, 0x38(r3)
/* 802BD600 002BA1E0  D0 03 0D E0 */	stfs f0, 0xde0(r3)
/* 802BD604 002BA1E4  48 00 00 0C */	b .L_802BD610
.L_802BD608:
/* 802BD608 002BA1E8  C0 03 00 38 */	lfs f0, 0x38(r3)
/* 802BD60C 002BA1EC  D0 03 0D E0 */	stfs f0, 0xde0(r3)
.L_802BD610:
/* 802BD610 002BA1F0  7F 63 DB 78 */	mr r3, r27
/* 802BD614 002BA1F4  BB 21 00 74 */	lmw r25, 0x74(r1)
/* 802BD618 002BA1F8  80 01 00 94 */	lwz r0, 0x94(r1)
/* 802BD61C 002BA1FC  38 21 00 90 */	addi r1, r1, 0x90
/* 802BD620 002BA200  7C 08 03 A6 */	mtlr r0
/* 802BD624 002BA204  4E 80 00 20 */	blr

.global it_802BD628
it_802BD628:
/* 802BD628 002BA208  7C 08 02 A6 */	mflr r0
/* 802BD62C 002BA20C  38 80 00 00 */	li r4, 0
/* 802BD630 002BA210  90 01 00 04 */	stw r0, 4(r1)
/* 802BD634 002BA214  3C 00 43 30 */	lis r0, 0x4330
/* 802BD638 002BA218  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 802BD63C 002BA21C  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 802BD640 002BA220  93 C1 00 18 */	stw r30, 0x18(r1)
/* 802BD644 002BA224  7C 7E 1B 78 */	mr r30, r3
/* 802BD648 002BA228  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 802BD64C 002BA22C  C8 22 D7 28 */	lfd f1, it_804DD108@sda21(r2)
/* 802BD650 002BA230  80 BF 0D D8 */	lwz r5, 0xdd8(r31)
/* 802BD654 002BA234  6C A5 80 00 */	xoris r5, r5, 0x8000
/* 802BD658 002BA238  90 A1 00 14 */	stw r5, 0x14(r1)
/* 802BD65C 002BA23C  90 01 00 10 */	stw r0, 0x10(r1)
/* 802BD660 002BA240  C8 01 00 10 */	lfd f0, 0x10(r1)
/* 802BD664 002BA244  EC 20 08 28 */	fsubs f1, f0, f1
/* 802BD668 002BA248  4B FB 60 09 */	bl it_80273670
/* 802BD66C 002BA24C  88 1F 0D D4 */	lbz r0, 0xdd4(r31)
/* 802BD670 002BA250  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 802BD674 002BA254  41 82 00 18 */	beq .L_802BD68C
/* 802BD678 002BA258  38 7E 00 00 */	addi r3, r30, 0
/* 802BD67C 002BA25C  38 80 00 04 */	li r4, 4
/* 802BD680 002BA260  38 A0 00 02 */	li r5, 2
/* 802BD684 002BA264  4B FA B7 D9 */	bl Item_80268E5C
/* 802BD688 002BA268  48 00 00 1C */	b .L_802BD6A4
.L_802BD68C:
/* 802BD68C 002BA26C  38 7E 00 00 */	addi r3, r30, 0
/* 802BD690 002BA270  38 80 00 00 */	li r4, 0
/* 802BD694 002BA274  38 A0 00 02 */	li r5, 2
/* 802BD698 002BA278  4B FA B7 C5 */	bl Item_80268E5C
/* 802BD69C 002BA27C  7F C3 F3 78 */	mr r3, r30
/* 802BD6A0 002BA280  4B FA E6 55 */	bl it_8026BCF4
.L_802BD6A4:
/* 802BD6A4 002BA284  88 1F 0D D4 */	lbz r0, 0xdd4(r31)
/* 802BD6A8 002BA288  38 60 00 01 */	li r3, 1
/* 802BD6AC 002BA28C  50 60 3E 30 */	rlwimi r0, r3, 7, 0x18, 0x18
/* 802BD6B0 002BA290  98 1F 0D D4 */	stb r0, 0xdd4(r31)
/* 802BD6B4 002BA294  7F C3 F3 78 */	mr r3, r30
/* 802BD6B8 002BA298  4B FA BE 15 */	bl Item_802694CC
/* 802BD6BC 002BA29C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 802BD6C0 002BA2A0  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 802BD6C4 002BA2A4  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 802BD6C8 002BA2A8  38 21 00 20 */	addi r1, r1, 0x20
/* 802BD6CC 002BA2AC  7C 08 03 A6 */	mtlr r0
/* 802BD6D0 002BA2B0  4E 80 00 20 */	blr
.global it_802BD6D4
it_802BD6D4:
/* 802BD6D4 002BA2B4  38 60 00 00 */	li r3, 0
/* 802BD6D8 002BA2B8  4E 80 00 20 */	blr
.global it_802BD6DC
it_802BD6DC:
/* 802BD6DC 002BA2BC  4E 80 00 20 */	blr
.global it_802BD6E0
it_802BD6E0:
/* 802BD6E0 002BA2C0  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 802BD6E4 002BA2C4  C0 02 D7 20 */	lfs f0, it_804DD100@sda21(r2)
/* 802BD6E8 002BA2C8  C0 23 0D 44 */	lfs f1, 0xd44(r3)
/* 802BD6EC 002BA2CC  EC 01 00 28 */	fsubs f0, f1, f0
/* 802BD6F0 002BA2D0  D0 03 0D 44 */	stfs f0, 0xd44(r3)
/* 802BD6F4 002BA2D4  C0 23 0D 44 */	lfs f1, 0xd44(r3)
/* 802BD6F8 002BA2D8  C0 02 D7 24 */	lfs f0, it_804DD104@sda21(r2)
/* 802BD6FC 002BA2DC  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 802BD700 002BA2E0  4C 40 13 82 */	cror 2, 0, 2
/* 802BD704 002BA2E4  40 82 00 0C */	bne .L_802BD710
/* 802BD708 002BA2E8  38 60 00 01 */	li r3, 1
/* 802BD70C 002BA2EC  4E 80 00 20 */	blr
.L_802BD710:
/* 802BD710 002BA2F0  38 60 00 00 */	li r3, 0
/* 802BD714 002BA2F4  4E 80 00 20 */	blr
.global it_802BD718
it_802BD718:
/* 802BD718 002BA2F8  7C 08 02 A6 */	mflr r0
/* 802BD71C 002BA2FC  90 01 00 04 */	stw r0, 4(r1)
/* 802BD720 002BA300  94 21 FF F8 */	stwu r1, -8(r1)
/* 802BD724 002BA304  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 802BD728 002BA308  80 84 00 CC */	lwz r4, 0xcc(r4)
/* 802BD72C 002BA30C  C0 24 00 10 */	lfs f1, 0x10(r4)
/* 802BD730 002BA310  C0 44 00 14 */	lfs f2, 0x14(r4)
/* 802BD734 002BA314  4B FB 51 2D */	bl it_80272860
/* 802BD738 002BA318  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802BD73C 002BA31C  38 21 00 08 */	addi r1, r1, 8
/* 802BD740 002BA320  7C 08 03 A6 */	mtlr r0
/* 802BD744 002BA324  4E 80 00 20 */	blr

.global it_802BD748
it_802BD748:
/* 802BD748 002BA328  7C 08 02 A6 */	mflr r0
/* 802BD74C 002BA32C  38 80 00 02 */	li r4, 2
/* 802BD750 002BA330  90 01 00 04 */	stw r0, 4(r1)
/* 802BD754 002BA334  38 A0 00 06 */	li r5, 6
/* 802BD758 002BA338  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 802BD75C 002BA33C  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 802BD760 002BA340  93 C1 00 28 */	stw r30, 0x28(r1)
/* 802BD764 002BA344  93 A1 00 24 */	stw r29, 0x24(r1)
/* 802BD768 002BA348  7C 7D 1B 78 */	mr r29, r3
/* 802BD76C 002BA34C  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 802BD770 002BA350  83 DD 00 28 */	lwz r30, 0x28(r29)
/* 802BD774 002BA354  4B FA B6 E9 */	bl Item_80268E5C
/* 802BD778 002BA358  80 9F 0D D8 */	lwz r4, 0xdd8(r31)
/* 802BD77C 002BA35C  3C 00 43 30 */	lis r0, 0x4330
/* 802BD780 002BA360  C8 22 D7 28 */	lfd f1, it_804DD108@sda21(r2)
/* 802BD784 002BA364  38 7D 00 00 */	addi r3, r29, 0
/* 802BD788 002BA368  6C 84 80 00 */	xoris r4, r4, 0x8000
/* 802BD78C 002BA36C  90 81 00 1C */	stw r4, 0x1c(r1)
/* 802BD790 002BA370  38 80 00 00 */	li r4, 0
/* 802BD794 002BA374  90 01 00 18 */	stw r0, 0x18(r1)
/* 802BD798 002BA378  C8 01 00 18 */	lfd f0, 0x18(r1)
/* 802BD79C 002BA37C  EC 20 08 28 */	fsubs f1, f0, f1
/* 802BD7A0 002BA380  4B FB 5E D1 */	bl it_80273670
/* 802BD7A4 002BA384  80 9F 0D DC */	lwz r4, 0xddc(r31)
/* 802BD7A8 002BA388  38 7F 05 D4 */	addi r3, r31, 0x5d4
/* 802BD7AC 002BA38C  7F A5 EB 78 */	mr r5, r29
/* 802BD7B0 002BA390  4B FB 4C B1 */	bl it_80272460
/* 802BD7B4 002BA394  C0 3F 0D E0 */	lfs f1, 0xde0(r31)
/* 802BD7B8 002BA398  38 7D 00 00 */	addi r3, r29, 0
/* 802BD7BC 002BA39C  38 9E 00 00 */	addi r4, r30, 0
/* 802BD7C0 002BA3A0  4B FB 6C C5 */	bl it_80274484
/* 802BD7C4 002BA3A4  80 01 00 34 */	lwz r0, 0x34(r1)
/* 802BD7C8 002BA3A8  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 802BD7CC 002BA3AC  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 802BD7D0 002BA3B0  83 A1 00 24 */	lwz r29, 0x24(r1)
/* 802BD7D4 002BA3B4  38 21 00 30 */	addi r1, r1, 0x30
/* 802BD7D8 002BA3B8  7C 08 03 A6 */	mtlr r0
/* 802BD7DC 002BA3BC  4E 80 00 20 */	blr
.global it_802BD7E0
it_802BD7E0:
/* 802BD7E0 002BA3C0  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 802BD7E4 002BA3C4  C0 02 D7 20 */	lfs f0, it_804DD100@sda21(r2)
/* 802BD7E8 002BA3C8  C0 23 0D 44 */	lfs f1, 0xd44(r3)
/* 802BD7EC 002BA3CC  EC 01 00 28 */	fsubs f0, f1, f0
/* 802BD7F0 002BA3D0  D0 03 0D 44 */	stfs f0, 0xd44(r3)
/* 802BD7F4 002BA3D4  C0 23 0D 44 */	lfs f1, 0xd44(r3)
/* 802BD7F8 002BA3D8  C0 02 D7 24 */	lfs f0, it_804DD104@sda21(r2)
/* 802BD7FC 002BA3DC  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 802BD800 002BA3E0  4C 40 13 82 */	cror 2, 0, 2
/* 802BD804 002BA3E4  40 82 00 0C */	bne .L_802BD810
/* 802BD808 002BA3E8  38 60 00 01 */	li r3, 1
/* 802BD80C 002BA3EC  4E 80 00 20 */	blr
.L_802BD810:
/* 802BD810 002BA3F0  38 60 00 00 */	li r3, 0
/* 802BD814 002BA3F4  4E 80 00 20 */	blr
.global it_802BD818
it_802BD818:
/* 802BD818 002BA3F8  7C 08 02 A6 */	mflr r0
/* 802BD81C 002BA3FC  90 01 00 04 */	stw r0, 4(r1)
/* 802BD820 002BA400  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 802BD824 002BA404  93 E1 00 14 */	stw r31, 0x14(r1)
/* 802BD828 002BA408  7C 7F 1B 78 */	mr r31, r3
/* 802BD82C 002BA40C  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 802BD830 002BA410  80 84 00 CC */	lwz r4, 0xcc(r4)
/* 802BD834 002BA414  C0 24 00 10 */	lfs f1, 0x10(r4)
/* 802BD838 002BA418  C0 44 00 14 */	lfs f2, 0x14(r4)
/* 802BD83C 002BA41C  4B FB 50 25 */	bl it_80272860
/* 802BD840 002BA420  80 8D B6 88 */	lwz r4, it_804D6D28@sda21(r13)
/* 802BD844 002BA424  7F E3 FB 78 */	mr r3, r31
/* 802BD848 002BA428  C0 24 00 68 */	lfs f1, 0x68(r4)
/* 802BD84C 002BA42C  4B FB 6E 0D */	bl it_80274658
/* 802BD850 002BA430  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 802BD854 002BA434  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 802BD858 002BA438  38 21 00 18 */	addi r1, r1, 0x18
/* 802BD85C 002BA43C  7C 08 03 A6 */	mtlr r0
/* 802BD860 002BA440  4E 80 00 20 */	blr
.global it_802BD864
it_802BD864:
/* 802BD864 002BA444  7C 08 02 A6 */	mflr r0
/* 802BD868 002BA448  90 01 00 04 */	stw r0, 4(r1)
/* 802BD86C 002BA44C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 802BD870 002BA450  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 802BD874 002BA454  7C 7F 1B 78 */	mr r31, r3
/* 802BD878 002BA458  4B FB 02 31 */	bl it_8026DAA8
/* 802BD87C 002BA45C  54 60 07 3D */	rlwinm. r0, r3, 0, 0x1c, 0x1e
/* 802BD880 002BA460  38 83 00 00 */	addi r4, r3, 0
/* 802BD884 002BA464  41 82 00 20 */	beq .L_802BD8A4
/* 802BD888 002BA468  7F E3 FB 78 */	mr r3, r31
/* 802BD88C 002BA46C  4B FB 97 39 */	bl it_80276FC4
/* 802BD890 002BA470  38 7F 00 00 */	addi r3, r31, 0
/* 802BD894 002BA474  38 80 00 01 */	li r4, 1
/* 802BD898 002BA478  38 A0 00 02 */	li r5, 2
/* 802BD89C 002BA47C  4B FA B5 C1 */	bl Item_80268E5C
/* 802BD8A0 002BA480  48 00 00 14 */	b .L_802BD8B4
.L_802BD8A4:
/* 802BD8A4 002BA484  54 80 07 BF */	clrlwi. r0, r4, 0x1e
/* 802BD8A8 002BA488  41 82 00 0C */	beq .L_802BD8B4
/* 802BD8AC 002BA48C  38 60 00 01 */	li r3, 1
/* 802BD8B0 002BA490  48 00 00 08 */	b .L_802BD8B8
.L_802BD8B4:
/* 802BD8B4 002BA494  38 60 00 00 */	li r3, 0
.L_802BD8B8:
/* 802BD8B8 002BA498  80 01 00 24 */	lwz r0, 0x24(r1)
/* 802BD8BC 002BA49C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 802BD8C0 002BA4A0  38 21 00 20 */	addi r1, r1, 0x20
/* 802BD8C4 002BA4A4  7C 08 03 A6 */	mtlr r0
/* 802BD8C8 002BA4A8  4E 80 00 20 */	blr

.global it_802BD8CC
it_802BD8CC:
/* 802BD8CC 002BA4AC  7C 08 02 A6 */	mflr r0
/* 802BD8D0 002BA4B0  38 80 00 03 */	li r4, 3
/* 802BD8D4 002BA4B4  90 01 00 04 */	stw r0, 4(r1)
/* 802BD8D8 002BA4B8  38 A0 00 06 */	li r5, 6
/* 802BD8DC 002BA4BC  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 802BD8E0 002BA4C0  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 802BD8E4 002BA4C4  93 C1 00 18 */	stw r30, 0x18(r1)
/* 802BD8E8 002BA4C8  7C 7E 1B 78 */	mr r30, r3
/* 802BD8EC 002BA4CC  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 802BD8F0 002BA4D0  4B FA B5 6D */	bl Item_80268E5C
/* 802BD8F4 002BA4D4  80 9F 0D D8 */	lwz r4, 0xdd8(r31)
/* 802BD8F8 002BA4D8  3C 00 43 30 */	lis r0, 0x4330
/* 802BD8FC 002BA4DC  C8 22 D7 28 */	lfd f1, it_804DD108@sda21(r2)
/* 802BD900 002BA4E0  38 7E 00 00 */	addi r3, r30, 0
/* 802BD904 002BA4E4  6C 84 80 00 */	xoris r4, r4, 0x8000
/* 802BD908 002BA4E8  90 81 00 14 */	stw r4, 0x14(r1)
/* 802BD90C 002BA4EC  38 80 00 00 */	li r4, 0
/* 802BD910 002BA4F0  90 01 00 10 */	stw r0, 0x10(r1)
/* 802BD914 002BA4F4  C8 01 00 10 */	lfd f0, 0x10(r1)
/* 802BD918 002BA4F8  EC 20 08 28 */	fsubs f1, f0, f1
/* 802BD91C 002BA4FC  4B FB 5D 55 */	bl it_80273670
/* 802BD920 002BA500  80 01 00 24 */	lwz r0, 0x24(r1)
/* 802BD924 002BA504  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 802BD928 002BA508  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 802BD92C 002BA50C  38 21 00 20 */	addi r1, r1, 0x20
/* 802BD930 002BA510  7C 08 03 A6 */	mtlr r0
/* 802BD934 002BA514  4E 80 00 20 */	blr

.global it_802BD938
it_802BD938:
/* 802BD938 002BA518  7C 08 02 A6 */	mflr r0
/* 802BD93C 002BA51C  90 01 00 04 */	stw r0, 4(r1)
/* 802BD940 002BA520  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 802BD944 002BA524  93 E1 00 14 */	stw r31, 0x14(r1)
/* 802BD948 002BA528  7C 7F 1B 78 */	mr r31, r3
/* 802BD94C 002BA52C  4B FB 54 65 */	bl itColl_BounceOffVictim
/* 802BD950 002BA530  38 7F 00 00 */	addi r3, r31, 0
/* 802BD954 002BA534  38 80 00 01 */	li r4, 1
/* 802BD958 002BA538  38 A0 00 02 */	li r5, 2
/* 802BD95C 002BA53C  4B FA B5 01 */	bl Item_80268E5C
/* 802BD960 002BA540  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 802BD964 002BA544  38 60 00 00 */	li r3, 0
/* 802BD968 002BA548  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 802BD96C 002BA54C  38 21 00 18 */	addi r1, r1, 0x18
/* 802BD970 002BA550  7C 08 03 A6 */	mtlr r0
/* 802BD974 002BA554  4E 80 00 20 */	blr

.global it_802BD978
it_802BD978:
/* 802BD978 002BA558  7C 08 02 A6 */	mflr r0
/* 802BD97C 002BA55C  90 01 00 04 */	stw r0, 4(r1)
/* 802BD980 002BA560  94 21 FF F8 */	stwu r1, -8(r1)
/* 802BD984 002BA564  4B FB 54 2D */	bl itColl_BounceOffVictim
/* 802BD988 002BA568  38 60 00 00 */	li r3, 0
/* 802BD98C 002BA56C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802BD990 002BA570  38 21 00 08 */	addi r1, r1, 8
/* 802BD994 002BA574  7C 08 03 A6 */	mtlr r0
/* 802BD998 002BA578  4E 80 00 20 */	blr

.global it_802BD99C
it_802BD99C:
/* 802BD99C 002BA57C  7C 08 02 A6 */	mflr r0
/* 802BD9A0 002BA580  90 01 00 04 */	stw r0, 4(r1)
/* 802BD9A4 002BA584  94 21 FF F8 */	stwu r1, -8(r1)
/* 802BD9A8 002BA588  4B FB 56 89 */	bl it_80273030
/* 802BD9AC 002BA58C  38 60 00 00 */	li r3, 0
/* 802BD9B0 002BA590  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802BD9B4 002BA594  38 21 00 08 */	addi r1, r1, 8
/* 802BD9B8 002BA598  7C 08 03 A6 */	mtlr r0
/* 802BD9BC 002BA59C  4E 80 00 20 */	blr

.global it_802BD9C0
it_802BD9C0:
/* 802BD9C0 002BA5A0  7C 08 02 A6 */	mflr r0
/* 802BD9C4 002BA5A4  90 01 00 04 */	stw r0, 4(r1)
/* 802BD9C8 002BA5A8  94 21 FF F8 */	stwu r1, -8(r1)
/* 802BD9CC 002BA5AC  4B FB 53 E5 */	bl itColl_BounceOffVictim
/* 802BD9D0 002BA5B0  38 60 00 00 */	li r3, 0
/* 802BD9D4 002BA5B4  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802BD9D8 002BA5B8  38 21 00 08 */	addi r1, r1, 8
/* 802BD9DC 002BA5BC  7C 08 03 A6 */	mtlr r0
/* 802BD9E0 002BA5C0  4E 80 00 20 */	blr

.global it_802BD9E4
it_802BD9E4:
/* 802BD9E4 002BA5C4  7C 08 02 A6 */	mflr r0
/* 802BD9E8 002BA5C8  90 01 00 04 */	stw r0, 4(r1)
/* 802BD9EC 002BA5CC  94 21 FF F8 */	stwu r1, -8(r1)
/* 802BD9F0 002BA5D0  4B FB 56 89 */	bl itColl_BounceOffShield
/* 802BD9F4 002BA5D4  38 60 00 00 */	li r3, 0
/* 802BD9F8 002BA5D8  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802BD9FC 002BA5DC  38 21 00 08 */	addi r1, r1, 8
/* 802BDA00 002BA5E0  7C 08 03 A6 */	mtlr r0
/* 802BDA04 002BA5E4  4E 80 00 20 */	blr

.global it_802BDA08
it_802BDA08:
/* 802BDA08 002BA5E8  7C 08 02 A6 */	mflr r0
/* 802BDA0C 002BA5EC  90 01 00 04 */	stw r0, 4(r1)
/* 802BDA10 002BA5F0  94 21 FF F8 */	stwu r1, -8(r1)
/* 802BDA14 002BA5F4  80 A3 00 2C */	lwz r5, 0x2c(r3)
/* 802BDA18 002BA5F8  80 05 0D E4 */	lwz r0, 0xde4(r5)
/* 802BDA1C 002BA5FC  7C 00 20 40 */	cmplw r0, r4
/* 802BDA20 002BA600  40 82 00 0C */	bne .L_802BDA2C
/* 802BDA24 002BA604  38 00 00 00 */	li r0, 0
/* 802BDA28 002BA608  90 05 0D E4 */	stw r0, 0xde4(r5)
.L_802BDA2C:
/* 802BDA2C 002BA60C  4B FA DE 69 */	bl it_8026B894
/* 802BDA30 002BA610  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802BDA34 002BA614  38 21 00 08 */	addi r1, r1, 8
/* 802BDA38 002BA618  7C 08 03 A6 */	mtlr r0
/* 802BDA3C 002BA61C  4E 80 00 20 */	blr


.section .data
    .balign 8
.global it_803F74A8
it_803F74A8:
    .4byte 1
    .4byte it_802BD6D4
    .4byte it_802BD6DC
    .4byte NULL
    .4byte -1
    .4byte it_802BD6E0
    .4byte it_802BD718
    .4byte NULL
    .4byte 2
    .4byte it_802BD7E0
    .4byte it_802BD818
    .4byte it_802BD864
    .4byte 2
    .4byte it_802BD7E0
    .4byte it_802BD818
    .4byte it_802BD864
    .4byte -1
    .4byte it_802BD6D4
    .4byte it_802BD6DC
    .4byte NULL


.section .sdata2
    .balign 8
.global it_804DD100
it_804DD100:
    .4byte 0x3F800000
.global it_804DD104
it_804DD104:
    .4byte 0x00000000
.global it_804DD108
it_804DD108:
    .4byte 0x43300000
    .4byte 0x80000000
