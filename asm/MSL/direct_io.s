.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240

.global __fwrite
__fwrite:
/* 803235B0 00320190  7C 08 02 A6 */	mflr r0
/* 803235B4 00320194  90 01 00 04 */	stw r0, 4(r1)
/* 803235B8 00320198  94 21 FF B8 */	stwu r1, -0x48(r1)
/* 803235BC 0032019C  BF 21 00 2C */	stmw r25, 0x2c(r1)
/* 803235C0 003201A0  3B 44 00 00 */	addi r26, r4, 0
/* 803235C4 003201A4  3B 66 00 00 */	addi r27, r6, 0
/* 803235C8 003201A8  3B 83 00 00 */	addi r28, r3, 0
/* 803235CC 003201AC  3B 25 00 00 */	addi r25, r5, 0
/* 803235D0 003201B0  38 7B 00 00 */	addi r3, r27, 0
/* 803235D4 003201B4  38 80 00 00 */	li r4, 0
/* 803235D8 003201B8  48 00 2A C1 */	bl fwide
/* 803235DC 003201BC  2C 03 00 00 */	cmpwi r3, 0
/* 803235E0 003201C0  40 82 00 10 */	bne .L_803235F0
/* 803235E4 003201C4  38 7B 00 00 */	addi r3, r27, 0
/* 803235E8 003201C8  38 80 FF FF */	li r4, -1
/* 803235EC 003201CC  48 00 2A AD */	bl fwide
.L_803235F0:
/* 803235F0 003201D0  7C 1A C9 D7 */	mullw. r0, r26, r25
/* 803235F4 003201D4  7C 1D 03 78 */	mr r29, r0
/* 803235F8 003201D8  41 82 00 1C */	beq .L_80323614
/* 803235FC 003201DC  88 1B 00 0A */	lbz r0, 0xa(r27)
/* 80323600 003201E0  28 00 00 00 */	cmplwi r0, 0
/* 80323604 003201E4  40 82 00 10 */	bne .L_80323614
/* 80323608 003201E8  A0 1B 00 04 */	lhz r0, 4(r27)
/* 8032360C 003201EC  54 00 D7 7F */	rlwinm. r0, r0, 0x1a, 0x1d, 0x1f
/* 80323610 003201F0  40 82 00 0C */	bne .L_8032361C
.L_80323614:
/* 80323614 003201F4  38 60 00 00 */	li r3, 0
/* 80323618 003201F8  48 00 02 60 */	b .L_80323878
.L_8032361C:
/* 8032361C 003201FC  2C 00 00 02 */	cmpwi r0, 2
/* 80323620 00320200  40 82 00 08 */	bne .L_80323628
/* 80323624 00320204  48 00 06 CD */	bl __stdio_atexit
.L_80323628:
/* 80323628 00320208  88 1B 00 05 */	lbz r0, 5(r27)
/* 8032362C 0032020C  3B E0 00 01 */	li r31, 1
/* 80323630 00320210  38 7F 00 00 */	addi r3, r31, 0
/* 80323634 00320214  54 00 EF FF */	rlwinm. r0, r0, 0x1d, 0x1f, 0x1f
/* 80323638 00320218  38 9F 00 00 */	addi r4, r31, 0
/* 8032363C 0032021C  41 82 00 18 */	beq .L_80323654
/* 80323640 00320220  A0 1B 00 04 */	lhz r0, 4(r27)
/* 80323644 00320224  54 00 D7 7E */	rlwinm r0, r0, 0x1a, 0x1d, 0x1f
/* 80323648 00320228  2C 00 00 03 */	cmpwi r0, 3
/* 8032364C 0032022C  41 82 00 08 */	beq .L_80323654
/* 80323650 00320230  38 80 00 00 */	li r4, 0
.L_80323654:
/* 80323654 00320234  2C 04 00 00 */	cmpwi r4, 0
/* 80323658 00320238  40 82 00 18 */	bne .L_80323670
/* 8032365C 0032023C  88 1B 00 04 */	lbz r0, 4(r27)
/* 80323660 00320240  54 00 FF BE */	rlwinm r0, r0, 0x1f, 0x1e, 0x1f
/* 80323664 00320244  28 00 00 02 */	cmplwi r0, 2
/* 80323668 00320248  41 82 00 08 */	beq .L_80323670
/* 8032366C 0032024C  38 60 00 00 */	li r3, 0
.L_80323670:
/* 80323670 00320250  2C 03 00 00 */	cmpwi r3, 0
/* 80323674 00320254  40 82 00 18 */	bne .L_8032368C
/* 80323678 00320258  88 1B 00 04 */	lbz r0, 4(r27)
/* 8032367C 0032025C  54 00 FF BE */	rlwinm r0, r0, 0x1f, 0x1e, 0x1f
/* 80323680 00320260  28 00 00 01 */	cmplwi r0, 1
/* 80323684 00320264  41 82 00 08 */	beq .L_8032368C
/* 80323688 00320268  3B E0 00 00 */	li r31, 0
.L_8032368C:
/* 8032368C 0032026C  88 7B 00 08 */	lbz r3, 8(r27)
/* 80323690 00320270  54 60 DF 7F */	rlwinm. r0, r3, 0x1b, 0x1d, 0x1f
/* 80323694 00320274  40 82 00 24 */	bne .L_803236B8
/* 80323698 00320278  88 1B 00 04 */	lbz r0, 4(r27)
/* 8032369C 0032027C  54 00 EF BD */	rlwinm. r0, r0, 0x1d, 0x1e, 0x1e
/* 803236A0 00320280  41 82 00 18 */	beq .L_803236B8
/* 803236A4 00320284  38 00 00 01 */	li r0, 1
/* 803236A8 00320288  50 03 2E 34 */	rlwimi r3, r0, 5, 0x18, 0x1a
/* 803236AC 0032028C  98 7B 00 08 */	stb r3, 8(r27)
/* 803236B0 00320290  7F 63 DB 78 */	mr r3, r27
/* 803236B4 00320294  4B FF FE 75 */	bl __prep_buffer
.L_803236B8:
/* 803236B8 00320298  88 1B 00 08 */	lbz r0, 8(r27)
/* 803236BC 0032029C  54 00 DF 7E */	rlwinm r0, r0, 0x1b, 0x1d, 0x1f
/* 803236C0 003202A0  28 00 00 01 */	cmplwi r0, 1
/* 803236C4 003202A4  41 82 00 1C */	beq .L_803236E0
/* 803236C8 003202A8  38 00 00 01 */	li r0, 1
/* 803236CC 003202AC  98 1B 00 0A */	stb r0, 0xa(r27)
/* 803236D0 003202B0  38 00 00 00 */	li r0, 0
/* 803236D4 003202B4  38 60 00 00 */	li r3, 0
/* 803236D8 003202B8  90 1B 00 24 */	stw r0, 0x24(r27)
/* 803236DC 003202BC  48 00 01 9C */	b .L_80323878
.L_803236E0:
/* 803236E0 003202C0  28 1D 00 00 */	cmplwi r29, 0
/* 803236E4 003202C4  3B DC 00 00 */	addi r30, r28, 0
/* 803236E8 003202C8  3B 80 00 00 */	li r28, 0
/* 803236EC 003202CC  41 82 00 FC */	beq .L_803237E8
/* 803236F0 003202D0  80 9B 00 20 */	lwz r4, 0x20(r27)
/* 803236F4 003202D4  80 7B 00 18 */	lwz r3, 0x18(r27)
/* 803236F8 003202D8  7C 04 18 40 */	cmplw r4, r3
/* 803236FC 003202DC  40 82 00 0C */	bne .L_80323708
/* 80323700 003202E0  2C 1F 00 00 */	cmpwi r31, 0
/* 80323704 003202E4  41 82 00 E4 */	beq .L_803237E8
.L_80323708:
/* 80323708 003202E8  80 1B 00 1C */	lwz r0, 0x1c(r27)
/* 8032370C 003202EC  7C 63 20 50 */	subf r3, r3, r4
/* 80323710 003202F0  7C 03 00 50 */	subf r0, r3, r0
/* 80323714 003202F4  90 1B 00 24 */	stw r0, 0x24(r27)
.L_80323718:
/* 80323718 003202F8  80 1B 00 24 */	lwz r0, 0x24(r27)
/* 8032371C 003202FC  90 01 00 20 */	stw r0, 0x20(r1)
/* 80323720 00320300  80 01 00 20 */	lwz r0, 0x20(r1)
/* 80323724 00320304  7C 00 E8 40 */	cmplw r0, r29
/* 80323728 00320308  40 81 00 08 */	ble .L_80323730
/* 8032372C 0032030C  93 A1 00 20 */	stw r29, 0x20(r1)
.L_80323730:
/* 80323730 00320310  80 A1 00 20 */	lwz r5, 0x20(r1)
/* 80323734 00320314  28 05 00 00 */	cmplwi r5, 0
/* 80323738 00320318  41 82 00 3C */	beq .L_80323774
/* 8032373C 0032031C  80 7B 00 20 */	lwz r3, 0x20(r27)
/* 80323740 00320320  7F C4 F3 78 */	mr r4, r30
/* 80323744 00320324  4B CD FA B1 */	bl memcpy
/* 80323748 00320328  80 61 00 20 */	lwz r3, 0x20(r1)
/* 8032374C 0032032C  80 1B 00 20 */	lwz r0, 0x20(r27)
/* 80323750 00320330  7F DE 1A 14 */	add r30, r30, r3
/* 80323754 00320334  7C 00 1A 14 */	add r0, r0, r3
/* 80323758 00320338  90 1B 00 20 */	stw r0, 0x20(r27)
/* 8032375C 0032033C  7F 9C 1A 14 */	add r28, r28, r3
/* 80323760 00320340  7F A3 E8 50 */	subf r29, r3, r29
/* 80323764 00320344  80 61 00 20 */	lwz r3, 0x20(r1)
/* 80323768 00320348  80 1B 00 24 */	lwz r0, 0x24(r27)
/* 8032376C 0032034C  7C 03 00 50 */	subf r0, r3, r0
/* 80323770 00320350  90 1B 00 24 */	stw r0, 0x24(r27)
.L_80323774:
/* 80323774 00320354  80 7B 00 24 */	lwz r3, 0x24(r27)
/* 80323778 00320358  28 03 00 00 */	cmplwi r3, 0
/* 8032377C 0032035C  40 82 00 1C */	bne .L_80323798
/* 80323780 00320360  A0 1B 00 04 */	lhz r0, 4(r27)
/* 80323784 00320364  54 00 D7 7E */	rlwinm r0, r0, 0x1a, 0x1d, 0x1f
/* 80323788 00320368  2C 00 00 03 */	cmpwi r0, 3
/* 8032378C 0032036C  40 82 00 0C */	bne .L_80323798
/* 80323790 00320370  7F 9C EA 14 */	add r28, r28, r29
/* 80323794 00320374  48 00 00 54 */	b .L_803237E8
.L_80323798:
/* 80323798 00320378  28 03 00 00 */	cmplwi r3, 0
/* 8032379C 0032037C  41 82 00 10 */	beq .L_803237AC
/* 803237A0 00320380  88 1B 00 04 */	lbz r0, 4(r27)
/* 803237A4 00320384  54 00 FF BF */	rlwinm. r0, r0, 0x1f, 0x1e, 0x1f
/* 803237A8 00320388  40 82 00 30 */	bne .L_803237D8
.L_803237AC:
/* 803237AC 0032038C  38 7B 00 00 */	addi r3, r27, 0
/* 803237B0 00320390  38 80 00 00 */	li r4, 0
/* 803237B4 00320394  4B FF FC A9 */	bl __flush_buffer
/* 803237B8 00320398  2C 03 00 00 */	cmpwi r3, 0
/* 803237BC 0032039C  41 82 00 1C */	beq .L_803237D8
/* 803237C0 003203A0  38 00 00 01 */	li r0, 1
/* 803237C4 003203A4  98 1B 00 0A */	stb r0, 0xa(r27)
/* 803237C8 003203A8  38 00 00 00 */	li r0, 0
/* 803237CC 003203AC  3B A0 00 00 */	li r29, 0
/* 803237D0 003203B0  90 1B 00 24 */	stw r0, 0x24(r27)
/* 803237D4 003203B4  48 00 00 14 */	b .L_803237E8
.L_803237D8:
/* 803237D8 003203B8  28 1D 00 00 */	cmplwi r29, 0
/* 803237DC 003203BC  41 82 00 0C */	beq .L_803237E8
/* 803237E0 003203C0  2C 1F 00 00 */	cmpwi r31, 0
/* 803237E4 003203C4  40 82 FF 34 */	bne .L_80323718
.L_803237E8:
/* 803237E8 003203C8  28 1D 00 00 */	cmplwi r29, 0
/* 803237EC 003203CC  41 82 00 68 */	beq .L_80323854
/* 803237F0 003203D0  2C 1F 00 00 */	cmpwi r31, 0
/* 803237F4 003203D4  40 82 00 60 */	bne .L_80323854
/* 803237F8 003203D8  83 FB 00 18 */	lwz r31, 0x18(r27)
/* 803237FC 003203DC  7C 1E EA 14 */	add r0, r30, r29
/* 80323800 003203E0  83 3B 00 1C */	lwz r25, 0x1c(r27)
/* 80323804 003203E4  38 7B 00 00 */	addi r3, r27, 0
/* 80323808 003203E8  38 81 00 20 */	addi r4, r1, 0x20
/* 8032380C 003203EC  93 DB 00 18 */	stw r30, 0x18(r27)
/* 80323810 003203F0  93 BB 00 1C */	stw r29, 0x1c(r27)
/* 80323814 003203F4  90 1B 00 20 */	stw r0, 0x20(r27)
/* 80323818 003203F8  4B FF FC 45 */	bl __flush_buffer
/* 8032381C 003203FC  2C 03 00 00 */	cmpwi r3, 0
/* 80323820 00320400  41 82 00 14 */	beq .L_80323834
/* 80323824 00320404  38 00 00 01 */	li r0, 1
/* 80323828 00320408  98 1B 00 0A */	stb r0, 0xa(r27)
/* 8032382C 0032040C  38 00 00 00 */	li r0, 0
/* 80323830 00320410  90 1B 00 24 */	stw r0, 0x24(r27)
.L_80323834:
/* 80323834 00320414  80 01 00 20 */	lwz r0, 0x20(r1)
/* 80323838 00320418  7F 63 DB 78 */	mr r3, r27
/* 8032383C 0032041C  93 FB 00 18 */	stw r31, 0x18(r27)
/* 80323840 00320420  7F 9C 02 14 */	add r28, r28, r0
/* 80323844 00320424  93 3B 00 1C */	stw r25, 0x1c(r27)
/* 80323848 00320428  4B FF FC E1 */	bl __prep_buffer
/* 8032384C 0032042C  38 00 00 00 */	li r0, 0
/* 80323850 00320430  90 1B 00 24 */	stw r0, 0x24(r27)
.L_80323854:
/* 80323854 00320434  88 1B 00 04 */	lbz r0, 4(r27)
/* 80323858 00320438  54 00 FF BE */	rlwinm r0, r0, 0x1f, 0x1e, 0x1f
/* 8032385C 0032043C  28 00 00 02 */	cmplwi r0, 2
/* 80323860 00320440  41 82 00 0C */	beq .L_8032386C
/* 80323864 00320444  38 00 00 00 */	li r0, 0
/* 80323868 00320448  90 1B 00 24 */	stw r0, 0x24(r27)
.L_8032386C:
/* 8032386C 0032044C  38 1A FF FF */	addi r0, r26, -1
/* 80323870 00320450  7C 1C 02 14 */	add r0, r28, r0
/* 80323874 00320454  7C 60 D3 96 */	divwu r3, r0, r26
.L_80323878:
/* 80323878 00320458  BB 21 00 2C */	lmw r25, 0x2c(r1)
/* 8032387C 0032045C  80 01 00 4C */	lwz r0, 0x4c(r1)
/* 80323880 00320460  38 21 00 48 */	addi r1, r1, 0x48
/* 80323884 00320464  7C 08 03 A6 */	mtlr r0
/* 80323888 00320468  4E 80 00 20 */	blr
