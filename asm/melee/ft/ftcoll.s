.include "macros.inc"

.section .text  # 0x800763C0 - 0x800DF934

.global func_8007B6A0
func_8007B6A0:
/* 8007B6A0 00078280  7C 08 02 A6 */	mflr r0
/* 8007B6A4 00078284  38 A0 00 00 */	li r5, 0
/* 8007B6A8 00078288  90 01 00 04 */	stw r0, 4(r1)
/* 8007B6AC 0007828C  38 00 00 01 */	li r0, 1
/* 8007B6B0 00078290  94 21 FF F8 */	stwu r1, -8(r1)
/* 8007B6B4 00078294  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8007B6B8 00078298  88 83 22 21 */	lbz r4, 0x2221(r3)
/* 8007B6BC 0007829C  50 04 3E 30 */	rlwimi r4, r0, 7, 0x18, 0x18
/* 8007B6C0 000782A0  38 00 00 02 */	li r0, 2
/* 8007B6C4 000782A4  98 83 22 21 */	stb r4, 0x2221(r3)
/* 8007B6C8 000782A8  38 80 00 09 */	li r4, 9
/* 8007B6CC 000782AC  90 A3 19 90 */	stw r5, 0x1990(r3)
/* 8007B6D0 000782B0  38 A0 00 00 */	li r5, 0
/* 8007B6D4 000782B4  90 03 19 8C */	stw r0, 0x198c(r3)
/* 8007B6D8 000782B8  48 04 48 F9 */	bl func_800BFFD0
/* 8007B6DC 000782BC  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8007B6E0 000782C0  38 21 00 08 */	addi r1, r1, 8
/* 8007B6E4 000782C4  7C 08 03 A6 */	mtlr r0
/* 8007B6E8 000782C8  4E 80 00 20 */	blr 

.global func_8007B6EC
func_8007B6EC:
/* 8007B6EC 000782CC  7C 08 02 A6 */	mflr r0
/* 8007B6F0 000782D0  90 01 00 04 */	stw r0, 4(r1)
/* 8007B6F4 000782D4  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8007B6F8 000782D8  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8007B6FC 000782DC  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8007B700 000782E0  38 60 00 00 */	li r3, 0
/* 8007B704 000782E4  88 1F 22 21 */	lbz r0, 0x2221(r31)
/* 8007B708 000782E8  50 60 3E 30 */	rlwimi r0, r3, 7, 0x18, 0x18
/* 8007B70C 000782EC  98 1F 22 21 */	stb r0, 0x2221(r31)
/* 8007B710 000782F0  80 1F 19 90 */	lwz r0, 0x1990(r31)
/* 8007B714 000782F4  2C 00 00 00 */	cmpwi r0, 0
/* 8007B718 000782F8  40 82 00 34 */	bne lbl_8007B74C
/* 8007B71C 000782FC  80 1F 19 94 */	lwz r0, 0x1994(r31)
/* 8007B720 00078300  2C 00 00 00 */	cmpwi r0, 0
/* 8007B724 00078304  41 82 00 08 */	beq lbl_8007B72C
/* 8007B728 00078308  38 60 00 01 */	li r3, 1
lbl_8007B72C:
/* 8007B72C 0007830C  90 7F 19 8C */	stw r3, 0x198c(r31)
/* 8007B730 00078310  7F E3 FB 78 */	mr r3, r31
/* 8007B734 00078314  48 04 4F 61 */	bl func_800C0694
/* 8007B738 00078318  2C 03 00 09 */	cmpwi r3, 9
/* 8007B73C 0007831C  40 82 00 10 */	bne lbl_8007B74C
/* 8007B740 00078320  38 7F 00 00 */	addi r3, r31, 0
/* 8007B744 00078324  38 80 00 09 */	li r4, 9
/* 8007B748 00078328  48 04 4A B9 */	bl func_800C0200
lbl_8007B74C:
/* 8007B74C 0007832C  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8007B750 00078330  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8007B754 00078334  38 21 00 18 */	addi r1, r1, 0x18
/* 8007B758 00078338  7C 08 03 A6 */	mtlr r0
/* 8007B75C 0007833C  4E 80 00 20 */	blr 

.global func_8007B760
func_8007B760:
/* 8007B760 00078340  7C 08 02 A6 */	mflr r0
/* 8007B764 00078344  90 01 00 04 */	stw r0, 4(r1)
/* 8007B768 00078348  94 21 FF F8 */	stwu r1, -8(r1)
/* 8007B76C 0007834C  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8007B770 00078350  80 03 19 90 */	lwz r0, 0x1990(r3)
/* 8007B774 00078354  7C 04 00 00 */	cmpw r4, r0
/* 8007B778 00078358  40 81 00 08 */	ble lbl_8007B780
/* 8007B77C 0007835C  90 83 19 90 */	stw r4, 0x1990(r3)
lbl_8007B780:
/* 8007B780 00078360  38 00 00 02 */	li r0, 2
/* 8007B784 00078364  90 03 19 8C */	stw r0, 0x198c(r3)
/* 8007B788 00078368  38 80 00 09 */	li r4, 9
/* 8007B78C 0007836C  38 A0 00 00 */	li r5, 0
/* 8007B790 00078370  48 04 48 41 */	bl func_800BFFD0
/* 8007B794 00078374  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8007B798 00078378  38 21 00 08 */	addi r1, r1, 8
/* 8007B79C 0007837C  7C 08 03 A6 */	mtlr r0
/* 8007B7A0 00078380  4E 80 00 20 */	blr 

.global func_8007B7A4
func_8007B7A4:
/* 8007B7A4 00078384  7C 08 02 A6 */	mflr r0
/* 8007B7A8 00078388  90 01 00 04 */	stw r0, 4(r1)
/* 8007B7AC 0007838C  94 21 FF F8 */	stwu r1, -8(r1)
/* 8007B7B0 00078390  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8007B7B4 00078394  80 03 19 94 */	lwz r0, 0x1994(r3)
/* 8007B7B8 00078398  7C 04 00 00 */	cmpw r4, r0
/* 8007B7BC 0007839C  40 81 00 08 */	ble lbl_8007B7C4
/* 8007B7C0 000783A0  90 83 19 94 */	stw r4, 0x1994(r3)
lbl_8007B7C4:
/* 8007B7C4 000783A4  80 03 19 90 */	lwz r0, 0x1990(r3)
/* 8007B7C8 000783A8  2C 00 00 00 */	cmpwi r0, 0
/* 8007B7CC 000783AC  41 82 00 0C */	beq lbl_8007B7D8
/* 8007B7D0 000783B0  38 00 00 02 */	li r0, 2
/* 8007B7D4 000783B4  48 00 00 08 */	b lbl_8007B7DC
lbl_8007B7D8:
/* 8007B7D8 000783B8  38 00 00 01 */	li r0, 1
lbl_8007B7DC:
/* 8007B7DC 000783BC  90 03 19 8C */	stw r0, 0x198c(r3)
/* 8007B7E0 000783C0  38 80 00 09 */	li r4, 9
/* 8007B7E4 000783C4  38 A0 00 00 */	li r5, 0
/* 8007B7E8 000783C8  48 04 47 E9 */	bl func_800BFFD0
/* 8007B7EC 000783CC  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8007B7F0 000783D0  38 21 00 08 */	addi r1, r1, 8
/* 8007B7F4 000783D4  7C 08 03 A6 */	mtlr r0
/* 8007B7F8 000783D8  4E 80 00 20 */	blr 

.global func_8007B7FC
func_8007B7FC:
/* 8007B7FC 000783DC  7C 08 02 A6 */	mflr r0
/* 8007B800 000783E0  38 A0 00 00 */	li r5, 0
/* 8007B804 000783E4  90 01 00 04 */	stw r0, 4(r1)
/* 8007B808 000783E8  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8007B80C 000783EC  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8007B810 000783F0  3B E4 00 00 */	addi r31, r4, 0
/* 8007B814 000783F4  38 80 00 6B */	li r4, 0x6b
/* 8007B818 000783F8  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8007B81C 000783FC  7C 7E 1B 78 */	mr r30, r3
/* 8007B820 00078400  88 03 22 1D */	lbz r0, 0x221d(r3)
/* 8007B824 00078404  38 60 00 01 */	li r3, 1
/* 8007B828 00078408  50 60 0F BC */	rlwimi r0, r3, 1, 0x1e, 0x1e
/* 8007B82C 0007840C  98 1E 22 1D */	stb r0, 0x221d(r30)
/* 8007B830 00078410  38 7E 00 00 */	addi r3, r30, 0
/* 8007B834 00078414  93 FE 20 04 */	stw r31, 0x2004(r30)
/* 8007B838 00078418  48 04 47 99 */	bl func_800BFFD0
/* 8007B83C 0007841C  48 1E FD 4D */	bl func_8026B588
/* 8007B840 00078420  7C 1F 18 00 */	cmpw r31, r3
/* 8007B844 00078424  40 81 00 0C */	ble lbl_8007B850
/* 8007B848 00078428  7F C3 F3 78 */	mr r3, r30
/* 8007B84C 0007842C  48 00 C8 35 */	bl func_80088080
lbl_8007B850:
/* 8007B850 00078430  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8007B854 00078434  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8007B858 00078438  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8007B85C 0007843C  38 21 00 18 */	addi r1, r1, 0x18
/* 8007B860 00078440  7C 08 03 A6 */	mtlr r0
/* 8007B864 00078444  4E 80 00 20 */	blr 

.global func_8007B868
func_8007B868:
/* 8007B868 00078448  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 8007B86C 0007844C  88 04 22 1D */	lbz r0, 0x221d(r4)
/* 8007B870 00078450  54 00 FF FF */	rlwinm. r0, r0, 0x1f, 0x1f, 0x1f
/* 8007B874 00078454  41 82 00 0C */	beq lbl_8007B880
/* 8007B878 00078458  38 60 00 01 */	li r3, 1
/* 8007B87C 0007845C  48 00 00 08 */	b lbl_8007B884
lbl_8007B880:
/* 8007B880 00078460  38 60 00 00 */	li r3, 0
lbl_8007B884:
/* 8007B884 00078464  80 04 19 88 */	lwz r0, 0x1988(r4)
/* 8007B888 00078468  7C 00 18 00 */	cmpw r0, r3
/* 8007B88C 0007846C  40 81 00 08 */	ble lbl_8007B894
/* 8007B890 00078470  7C 03 03 78 */	mr r3, r0
lbl_8007B894:
/* 8007B894 00078474  80 04 19 8C */	lwz r0, 0x198c(r4)
/* 8007B898 00078478  7C 00 18 00 */	cmpw r0, r3
/* 8007B89C 0007847C  4C 81 00 20 */	blelr 
/* 8007B8A0 00078480  7C 03 03 78 */	mr r3, r0
/* 8007B8A4 00078484  4E 80 00 20 */	blr 

.global func_8007B8A8
func_8007B8A8:
/* 8007B8A8 00078488  38 00 00 00 */	li r0, 0
/* 8007B8AC 0007848C  90 03 00 48 */	stw r0, 0x48(r3)
/* 8007B8B0 00078490  80 A4 00 00 */	lwz r5, 0(r4)
/* 8007B8B4 00078494  80 04 00 04 */	lwz r0, 4(r4)
/* 8007B8B8 00078498  90 A3 00 10 */	stw r5, 0x10(r3)
/* 8007B8BC 0007849C  90 03 00 14 */	stw r0, 0x14(r3)
/* 8007B8C0 000784A0  80 04 00 08 */	lwz r0, 8(r4)
/* 8007B8C4 000784A4  90 03 00 18 */	stw r0, 0x18(r3)
/* 8007B8C8 000784A8  4E 80 00 20 */	blr 

.global func_8007B8CC
func_8007B8CC:
/* 8007B8CC 000784AC  80 A4 00 2C */	lwz r5, 0x2c(r4)
/* 8007B8D0 000784B0  90 83 11 98 */	stw r4, 0x1198(r3)
/* 8007B8D4 000784B4  88 05 06 1B */	lbz r0, 0x61b(r5)
/* 8007B8D8 000784B8  98 03 11 9C */	stb r0, 0x119c(r3)
/* 8007B8DC 000784BC  88 05 00 0C */	lbz r0, 0xc(r5)
/* 8007B8E0 000784C0  98 03 11 9D */	stb r0, 0x119d(r3)
/* 8007B8E4 000784C4  4E 80 00 20 */	blr 

.global func_8007B8E8
func_8007B8E8:
/* 8007B8E8 000784C8  80 8D C1 8C */	lwz r4, lbl_804D782C@sda21(r13)
/* 8007B8EC 000784CC  38 00 00 00 */	li r0, 0
/* 8007B8F0 000784D0  80 C4 00 20 */	lwz r6, 0x20(r4)
/* 8007B8F4 000784D4  48 00 00 24 */	b lbl_8007B918
lbl_8007B8F8:
/* 8007B8F8 000784D8  7C 03 30 40 */	cmplw r3, r6
/* 8007B8FC 000784DC  41 82 00 18 */	beq lbl_8007B914
/* 8007B900 000784E0  80 A6 00 2C */	lwz r5, 0x2c(r6)
/* 8007B904 000784E4  80 85 11 98 */	lwz r4, 0x1198(r5)
/* 8007B908 000784E8  7C 04 18 40 */	cmplw r4, r3
/* 8007B90C 000784EC  40 82 00 08 */	bne lbl_8007B914
/* 8007B910 000784F0  90 05 11 98 */	stw r0, 0x1198(r5)
lbl_8007B914:
/* 8007B914 000784F4  80 C6 00 08 */	lwz r6, 8(r6)
lbl_8007B918:
/* 8007B918 000784F8  28 06 00 00 */	cmplwi r6, 0
/* 8007B91C 000784FC  40 82 FF DC */	bne lbl_8007B8F8
/* 8007B920 00078500  4E 80 00 20 */	blr 

.global func_getWindOffsetVec_8007B924
func_getWindOffsetVec_8007B924:
/* 8007B924 00078504  7C 08 02 A6 */	mflr r0
/* 8007B928 00078508  90 01 00 04 */	stw r0, 4(r1)
/* 8007B92C 0007850C  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 8007B930 00078510  BF 61 00 24 */	stmw r27, 0x24(r1)
/* 8007B934 00078514  7C 7B 1B 78 */	mr r27, r3
/* 8007B938 00078518  7C 9C 23 78 */	mr r28, r4
/* 8007B93C 0007851C  C0 02 89 00 */	lfs f0, lbl_804D82E0@sda21(r2)
/* 8007B940 00078520  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8007B944 00078524  D0 04 00 08 */	stfs f0, 8(r4)
/* 8007B948 00078528  D0 04 00 04 */	stfs f0, 4(r4)
/* 8007B94C 0007852C  D0 04 00 00 */	stfs f0, 0(r4)
/* 8007B950 00078530  88 03 22 24 */	lbz r0, 0x2224(r3)
/* 8007B954 00078534  54 00 EF FF */	rlwinm. r0, r0, 0x1d, 0x1f, 0x1f
/* 8007B958 00078538  40 82 00 A0 */	bne lbl_8007B9F8
/* 8007B95C 0007853C  3C 60 80 46 */	lis r3, lbl_80459A68@ha
/* 8007B960 00078540  3B E3 9A 68 */	addi r31, r3, lbl_80459A68@l
/* 8007B964 00078544  3B C0 00 00 */	li r30, 0
/* 8007B968 00078548  48 00 00 84 */	b lbl_8007B9EC
lbl_8007B96C:
/* 8007B96C 0007854C  80 1F 00 00 */	lwz r0, 0(r31)
/* 8007B970 00078550  28 00 00 00 */	cmplwi r0, 0
/* 8007B974 00078554  7C 1D 03 78 */	mr r29, r0
/* 8007B978 00078558  41 82 00 6C */	beq lbl_8007B9E4
/* 8007B97C 0007855C  80 BF 00 04 */	lwz r5, 4(r31)
/* 8007B980 00078560  38 7B 00 00 */	addi r3, r27, 0
/* 8007B984 00078564  38 9D 00 00 */	addi r4, r29, 0
/* 8007B988 00078568  48 04 50 A1 */	bl func_800C0A28
/* 8007B98C 0007856C  2C 03 00 00 */	cmpwi r3, 0
/* 8007B990 00078570  41 82 00 54 */	beq lbl_8007B9E4
/* 8007B994 00078574  81 9F 00 08 */	lwz r12, 8(r31)
/* 8007B998 00078578  38 7D 00 00 */	addi r3, r29, 0
/* 8007B99C 0007857C  38 9B 00 00 */	addi r4, r27, 0
/* 8007B9A0 00078580  7D 88 03 A6 */	mtlr r12
/* 8007B9A4 00078584  38 A1 00 14 */	addi r5, r1, 0x14
/* 8007B9A8 00078588  4E 80 00 21 */	blrl 
/* 8007B9AC 0007858C  2C 03 00 00 */	cmpwi r3, 0
/* 8007B9B0 00078590  41 82 00 34 */	beq lbl_8007B9E4
/* 8007B9B4 00078594  C0 3C 00 00 */	lfs f1, 0(r28)
/* 8007B9B8 00078598  C0 01 00 14 */	lfs f0, 0x14(r1)
/* 8007B9BC 0007859C  EC 01 00 2A */	fadds f0, f1, f0
/* 8007B9C0 000785A0  D0 1C 00 00 */	stfs f0, 0(r28)
/* 8007B9C4 000785A4  C0 3C 00 04 */	lfs f1, 4(r28)
/* 8007B9C8 000785A8  C0 01 00 18 */	lfs f0, 0x18(r1)
/* 8007B9CC 000785AC  EC 01 00 2A */	fadds f0, f1, f0
/* 8007B9D0 000785B0  D0 1C 00 04 */	stfs f0, 4(r28)
/* 8007B9D4 000785B4  C0 3C 00 08 */	lfs f1, 8(r28)
/* 8007B9D8 000785B8  C0 01 00 1C */	lfs f0, 0x1c(r1)
/* 8007B9DC 000785BC  EC 01 00 2A */	fadds f0, f1, f0
/* 8007B9E0 000785C0  D0 1C 00 08 */	stfs f0, 8(r28)
lbl_8007B9E4:
/* 8007B9E4 000785C4  3B FF 00 0C */	addi r31, r31, 0xc
/* 8007B9E8 000785C8  3B DE 00 01 */	addi r30, r30, 1
lbl_8007B9EC:
/* 8007B9EC 000785CC  80 0D AE D8 */	lwz r0, lbl_804D6578@sda21(r13)
/* 8007B9F0 000785D0  7C 1E 00 00 */	cmpw r30, r0
/* 8007B9F4 000785D4  41 80 FF 78 */	blt lbl_8007B96C
lbl_8007B9F8:
/* 8007B9F8 000785D8  BB 61 00 24 */	lmw r27, 0x24(r1)
/* 8007B9FC 000785DC  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 8007BA00 000785E0  38 21 00 38 */	addi r1, r1, 0x38
/* 8007BA04 000785E4  7C 08 03 A6 */	mtlr r0
/* 8007BA08 000785E8  4E 80 00 20 */	blr 

.global func_8007BA0C
func_8007BA0C:
/* 8007BA0C 000785EC  7C 08 02 A6 */	mflr r0
/* 8007BA10 000785F0  90 01 00 04 */	stw r0, 4(r1)
/* 8007BA14 000785F4  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 8007BA18 000785F8  BF 61 00 1C */	stmw r27, 0x1c(r1)
/* 8007BA1C 000785FC  7C 7B 1B 78 */	mr r27, r3
/* 8007BA20 00078600  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8007BA24 00078604  88 03 22 19 */	lbz r0, 0x2219(r3)
/* 8007BA28 00078608  54 00 D7 FF */	rlwinm. r0, r0, 0x1a, 0x1f, 0x1f
/* 8007BA2C 0007860C  40 82 00 80 */	bne lbl_8007BAAC
/* 8007BA30 00078610  3C 60 80 46 */	lis r3, lbl_80459A74@ha
/* 8007BA34 00078614  3B E3 9A 74 */	addi r31, r3, lbl_80459A74@l
/* 8007BA38 00078618  3B C0 00 00 */	li r30, 0
/* 8007BA3C 0007861C  48 00 00 64 */	b lbl_8007BAA0
lbl_8007BA40:
/* 8007BA40 00078620  80 1F 00 00 */	lwz r0, 0(r31)
/* 8007BA44 00078624  28 00 00 00 */	cmplwi r0, 0
/* 8007BA48 00078628  7C 1D 03 78 */	mr r29, r0
/* 8007BA4C 0007862C  41 82 00 4C */	beq lbl_8007BA98
/* 8007BA50 00078630  83 9F 00 04 */	lwz r28, 4(r31)
/* 8007BA54 00078634  38 7B 00 00 */	addi r3, r27, 0
/* 8007BA58 00078638  38 9D 00 00 */	addi r4, r29, 0
/* 8007BA5C 0007863C  38 BC 00 00 */	addi r5, r28, 0
/* 8007BA60 00078640  48 04 4F C9 */	bl func_800C0A28
/* 8007BA64 00078644  2C 03 00 00 */	cmpwi r3, 0
/* 8007BA68 00078648  41 82 00 30 */	beq lbl_8007BA98
/* 8007BA6C 0007864C  81 9F 00 08 */	lwz r12, 8(r31)
/* 8007BA70 00078650  38 7D 00 00 */	addi r3, r29, 0
/* 8007BA74 00078654  38 9B 00 00 */	addi r4, r27, 0
/* 8007BA78 00078658  7D 88 03 A6 */	mtlr r12
/* 8007BA7C 0007865C  4E 80 00 21 */	blrl 
/* 8007BA80 00078660  2C 03 00 00 */	cmpwi r3, 0
/* 8007BA84 00078664  41 82 00 14 */	beq lbl_8007BA98
/* 8007BA88 00078668  38 7B 00 00 */	addi r3, r27, 0
/* 8007BA8C 0007866C  38 9D 00 00 */	addi r4, r29, 0
/* 8007BA90 00078670  38 BC 00 00 */	addi r5, r28, 0
/* 8007BA94 00078674  48 04 4D E1 */	bl func_800C0874
lbl_8007BA98:
/* 8007BA98 00078678  3B FF 00 0C */	addi r31, r31, 0xc
/* 8007BA9C 0007867C  3B DE 00 01 */	addi r30, r30, 1
lbl_8007BAA0:
/* 8007BAA0 00078680  80 0D AE D4 */	lwz r0, lbl_804D6574@sda21(r13)
/* 8007BAA4 00078684  7C 1E 00 00 */	cmpw r30, r0
/* 8007BAA8 00078688  41 80 FF 98 */	blt lbl_8007BA40
lbl_8007BAAC:
/* 8007BAAC 0007868C  BB 61 00 1C */	lmw r27, 0x1c(r1)
/* 8007BAB0 00078690  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8007BAB4 00078694  38 21 00 30 */	addi r1, r1, 0x30
/* 8007BAB8 00078698  7C 08 03 A6 */	mtlr r0
/* 8007BABC 0007869C  4E 80 00 20 */	blr 

.global func_8007BAC0
func_8007BAC0:
/* 8007BAC0 000786A0  7C 08 02 A6 */	mflr r0
/* 8007BAC4 000786A4  90 01 00 04 */	stw r0, 4(r1)
/* 8007BAC8 000786A8  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 8007BACC 000786AC  BF 41 00 20 */	stmw r26, 0x20(r1)
/* 8007BAD0 000786B0  7C 7A 1B 78 */	mr r26, r3
/* 8007BAD4 000786B4  48 0E F6 F1 */	bl func_8016B1C4
/* 8007BAD8 000786B8  2C 03 00 00 */	cmpwi r3, 0
/* 8007BADC 000786BC  40 82 00 DC */	bne lbl_8007BBB8
/* 8007BAE0 000786C0  80 7A 00 2C */	lwz r3, 0x2c(r26)
/* 8007BAE4 000786C4  88 03 22 1D */	lbz r0, 0x221d(r3)
/* 8007BAE8 000786C8  54 00 FF FF */	rlwinm. r0, r0, 0x1f, 0x1f, 0x1f
/* 8007BAEC 000786CC  41 82 00 0C */	beq lbl_8007BAF8
/* 8007BAF0 000786D0  3B E0 00 01 */	li r31, 1
/* 8007BAF4 000786D4  48 00 00 08 */	b lbl_8007BAFC
lbl_8007BAF8:
/* 8007BAF8 000786D8  3B E0 00 00 */	li r31, 0
lbl_8007BAFC:
/* 8007BAFC 000786DC  80 03 19 88 */	lwz r0, 0x1988(r3)
/* 8007BB00 000786E0  7C 00 F8 00 */	cmpw r0, r31
/* 8007BB04 000786E4  40 81 00 08 */	ble lbl_8007BB0C
/* 8007BB08 000786E8  7C 1F 03 78 */	mr r31, r0
lbl_8007BB0C:
/* 8007BB0C 000786EC  80 03 19 8C */	lwz r0, 0x198c(r3)
/* 8007BB10 000786F0  7C 00 F8 00 */	cmpw r0, r31
/* 8007BB14 000786F4  40 81 00 08 */	ble lbl_8007BB1C
/* 8007BB18 000786F8  7C 1F 03 78 */	mr r31, r0
lbl_8007BB1C:
/* 8007BB1C 000786FC  3C 60 80 46 */	lis r3, lbl_80459A8C@ha
/* 8007BB20 00078700  3B C3 9A 8C */	addi r30, r3, lbl_80459A8C@l
/* 8007BB24 00078704  3B A0 00 00 */	li r29, 0
/* 8007BB28 00078708  48 00 00 74 */	b lbl_8007BB9C
lbl_8007BB2C:
/* 8007BB2C 0007870C  80 1E 00 00 */	lwz r0, 0(r30)
/* 8007BB30 00078710  28 00 00 00 */	cmplwi r0, 0
/* 8007BB34 00078714  7C 1C 03 78 */	mr r28, r0
/* 8007BB38 00078718  41 82 00 5C */	beq lbl_8007BB94
/* 8007BB3C 0007871C  83 7E 00 04 */	lwz r27, 4(r30)
/* 8007BB40 00078720  38 7A 00 00 */	addi r3, r26, 0
/* 8007BB44 00078724  38 9C 00 00 */	addi r4, r28, 0
/* 8007BB48 00078728  38 BB 00 00 */	addi r5, r27, 0
/* 8007BB4C 0007872C  48 04 4E DD */	bl func_800C0A28
/* 8007BB50 00078730  2C 03 00 00 */	cmpwi r3, 0
/* 8007BB54 00078734  41 82 00 40 */	beq lbl_8007BB94
/* 8007BB58 00078738  81 9E 00 08 */	lwz r12, 8(r30)
/* 8007BB5C 0007873C  38 7C 00 00 */	addi r3, r28, 0
/* 8007BB60 00078740  38 9A 00 00 */	addi r4, r26, 0
/* 8007BB64 00078744  7D 88 03 A6 */	mtlr r12
/* 8007BB68 00078748  38 A1 00 18 */	addi r5, r1, 0x18
/* 8007BB6C 0007874C  4E 80 00 21 */	blrl 
/* 8007BB70 00078750  2C 03 00 00 */	cmpwi r3, 0
/* 8007BB74 00078754  41 82 00 20 */	beq lbl_8007BB94
/* 8007BB78 00078758  2C 1F 00 00 */	cmpwi r31, 0
/* 8007BB7C 0007875C  40 82 00 18 */	bne lbl_8007BB94
/* 8007BB80 00078760  80 A1 00 18 */	lwz r5, 0x18(r1)
/* 8007BB84 00078764  38 7A 00 00 */	addi r3, r26, 0
/* 8007BB88 00078768  38 9C 00 00 */	addi r4, r28, 0
/* 8007BB8C 0007876C  38 DB 00 00 */	addi r6, r27, 0
/* 8007BB90 00078770  48 04 4D 11 */	bl func_800C08A0
lbl_8007BB94:
/* 8007BB94 00078774  3B DE 00 0C */	addi r30, r30, 0xc
/* 8007BB98 00078778  3B BD 00 01 */	addi r29, r29, 1
lbl_8007BB9C:
/* 8007BB9C 0007877C  80 0D AE D0 */	lwz r0, lbl_804D6570@sda21(r13)
/* 8007BBA0 00078780  7C 1D 00 00 */	cmpw r29, r0
/* 8007BBA4 00078784  41 80 FF 88 */	blt lbl_8007BB2C
/* 8007BBA8 00078788  2C 1F 00 00 */	cmpwi r31, 0
/* 8007BBAC 0007878C  40 82 00 0C */	bne lbl_8007BBB8
/* 8007BBB0 00078790  7F 43 D3 78 */	mr r3, r26
/* 8007BBB4 00078794  48 04 4F 6D */	bl func_800C0B20
lbl_8007BBB8:
/* 8007BBB8 00078798  BB 41 00 20 */	lmw r26, 0x20(r1)
/* 8007BBBC 0007879C  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 8007BBC0 000787A0  38 21 00 38 */	addi r1, r1, 0x38
/* 8007BBC4 000787A4  7C 08 03 A6 */	mtlr r0
/* 8007BBC8 000787A8  4E 80 00 20 */	blr 

.global func_8007BBCC
func_8007BBCC:
/* 8007BBCC 000787AC  7C 08 02 A6 */	mflr r0
/* 8007BBD0 000787B0  90 01 00 04 */	stw r0, 4(r1)
/* 8007BBD4 000787B4  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 8007BBD8 000787B8  DB E1 00 20 */	stfd f31, 0x20(r1)
/* 8007BBDC 000787BC  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8007BBE0 000787C0  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8007BBE4 000787C4  80 0D AE B8 */	lwz r0, lbl_804D6558@sda21(r13)
/* 8007BBE8 000787C8  C3 E2 89 00 */	lfs f31, lbl_804D82E0@sda21(r2)
/* 8007BBEC 000787CC  28 00 00 00 */	cmplwi r0, 0
/* 8007BBF0 000787D0  41 82 00 80 */	beq lbl_8007BC70
/* 8007BBF4 000787D4  3C 60 80 46 */	lis r3, lbl_80459278@ha
/* 8007BBF8 000787D8  3B E3 92 78 */	addi r31, r3, lbl_80459278@l
/* 8007BBFC 000787DC  3B C0 00 00 */	li r30, 0
/* 8007BC00 000787E0  48 00 00 64 */	b lbl_8007BC64
lbl_8007BC04:
/* 8007BC04 000787E4  80 1F 00 00 */	lwz r0, 0(r31)
/* 8007BC08 000787E8  2C 00 00 02 */	cmpwi r0, 2
/* 8007BC0C 000787EC  41 82 00 34 */	beq lbl_8007BC40
/* 8007BC10 000787F0  40 80 00 4C */	bge lbl_8007BC5C
/* 8007BC14 000787F4  2C 00 00 01 */	cmpwi r0, 1
/* 8007BC18 000787F8  40 80 00 0C */	bge lbl_8007BC24
/* 8007BC1C 000787FC  48 00 00 40 */	b lbl_8007BC5C
/* 8007BC20 00078800  48 00 00 3C */	b lbl_8007BC5C
lbl_8007BC24:
/* 8007BC24 00078804  80 7F 00 0C */	lwz r3, 0xc(r31)
/* 8007BC28 00078808  80 03 00 30 */	lwz r0, 0x30(r3)
/* 8007BC2C 0007880C  28 00 00 0F */	cmplwi r0, 0xf
/* 8007BC30 00078810  40 82 00 2C */	bne lbl_8007BC5C
/* 8007BC34 00078814  C0 03 00 0C */	lfs f0, 0xc(r3)
/* 8007BC38 00078818  EF FF 00 2A */	fadds f31, f31, f0
/* 8007BC3C 0007881C  48 00 00 20 */	b lbl_8007BC5C
lbl_8007BC40:
/* 8007BC40 00078820  80 9F 00 0C */	lwz r4, 0xc(r31)
/* 8007BC44 00078824  80 04 00 30 */	lwz r0, 0x30(r4)
/* 8007BC48 00078828  28 00 00 0F */	cmplwi r0, 0xf
/* 8007BC4C 0007882C  40 82 00 10 */	bne lbl_8007BC5C
/* 8007BC50 00078830  80 7F 00 08 */	lwz r3, 8(r31)
/* 8007BC54 00078834  48 1E F5 81 */	bl func_8026B1D4
/* 8007BC58 00078838  EF FF 08 2A */	fadds f31, f31, f1
lbl_8007BC5C:
/* 8007BC5C 0007883C  3B FF 00 28 */	addi r31, r31, 0x28
/* 8007BC60 00078840  3B DE 00 01 */	addi r30, r30, 1
lbl_8007BC64:
/* 8007BC64 00078844  80 0D AE B8 */	lwz r0, lbl_804D6558@sda21(r13)
/* 8007BC68 00078848  7C 1E 00 40 */	cmplw r30, r0
/* 8007BC6C 0007884C  41 80 FF 98 */	blt lbl_8007BC04
lbl_8007BC70:
/* 8007BC70 00078850  FC 20 F8 90 */	fmr f1, f31
/* 8007BC74 00078854  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 8007BC78 00078858  CB E1 00 20 */	lfd f31, 0x20(r1)
/* 8007BC7C 0007885C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8007BC80 00078860  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8007BC84 00078864  38 21 00 28 */	addi r1, r1, 0x28
/* 8007BC88 00078868  7C 08 03 A6 */	mtlr r0
/* 8007BC8C 0007886C  4E 80 00 20 */	blr 

.global func_8007BC90
func_8007BC90:
/* 8007BC90 00078870  7C 08 02 A6 */	mflr r0
/* 8007BC94 00078874  90 01 00 04 */	stw r0, 4(r1)
/* 8007BC98 00078878  38 00 00 00 */	li r0, 0
/* 8007BC9C 0007887C  94 21 FF B8 */	stwu r1, -0x48(r1)
/* 8007BCA0 00078880  DB E1 00 40 */	stfd f31, 0x40(r1)
/* 8007BCA4 00078884  BF 01 00 20 */	stmw r24, 0x20(r1)
/* 8007BCA8 00078888  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8007BCAC 0007888C  90 1F 1A 60 */	stw r0, 0x1a60(r31)
/* 8007BCB0 00078890  C0 02 89 30 */	lfs f0, lbl_804D8310@sda21(r2)
/* 8007BCB4 00078894  D0 1F 21 6C */	stfs f0, 0x216c(r31)
/* 8007BCB8 00078898  80 6D C1 8C */	lwz r3, lbl_804D782C@sda21(r13)
/* 8007BCBC 0007889C  C3 E2 89 00 */	lfs f31, lbl_804D82E0@sda21(r2)
/* 8007BCC0 000788A0  83 C3 00 24 */	lwz r30, 0x24(r3)
/* 8007BCC4 000788A4  48 00 01 58 */	b lbl_8007BE1C
lbl_8007BCC8:
/* 8007BCC8 000788A8  80 7E 00 2C */	lwz r3, 0x2c(r30)
/* 8007BCCC 000788AC  80 03 0D 0C */	lwz r0, 0xd0c(r3)
/* 8007BCD0 000788B0  3B A3 00 00 */	addi r29, r3, 0
/* 8007BCD4 000788B4  2C 00 00 00 */	cmpwi r0, 0
/* 8007BCD8 000788B8  40 82 01 40 */	bne lbl_8007BE18
/* 8007BCDC 000788BC  88 1D 0D D0 */	lbz r0, 0xdd0(r29)
/* 8007BCE0 000788C0  54 00 EF FF */	rlwinm. r0, r0, 0x1d, 0x1f, 0x1f
/* 8007BCE4 000788C4  41 82 01 34 */	beq lbl_8007BE18
/* 8007BCE8 000788C8  88 1D 0D 09 */	lbz r0, 0xd09(r29)
/* 8007BCEC 000788CC  28 00 00 00 */	cmplwi r0, 0
/* 8007BCF0 000788D0  40 82 01 28 */	bne lbl_8007BE18
/* 8007BCF4 000788D4  3B 40 00 00 */	li r26, 0
/* 8007BCF8 000788D8  3B 7F 00 00 */	addi r27, r31, 0
lbl_8007BCFC:
/* 8007BCFC 000788DC  38 7B 09 14 */	addi r3, r27, 0x914
/* 8007BD00 000788E0  80 1B 09 14 */	lwz r0, 0x914(r27)
/* 8007BD04 000788E4  3B 23 00 00 */	addi r25, r3, 0
/* 8007BD08 000788E8  2C 00 00 00 */	cmpwi r0, 0
/* 8007BD0C 000788EC  41 82 00 FC */	beq lbl_8007BE08
/* 8007BD10 000788F0  80 03 00 30 */	lwz r0, 0x30(r3)
/* 8007BD14 000788F4  28 00 00 08 */	cmplwi r0, 8
/* 8007BD18 000788F8  40 82 00 F0 */	bne lbl_8007BE08
/* 8007BD1C 000788FC  88 03 00 40 */	lbz r0, 0x40(r3)
/* 8007BD20 00078900  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 8007BD24 00078904  41 82 00 10 */	beq lbl_8007BD34
/* 8007BD28 00078908  80 1D 00 C0 */	lwz r0, 0xc0(r29)
/* 8007BD2C 0007890C  2C 00 00 01 */	cmpwi r0, 1
/* 8007BD30 00078910  41 82 00 1C */	beq lbl_8007BD4C
lbl_8007BD34:
/* 8007BD34 00078914  88 03 00 40 */	lbz r0, 0x40(r3)
/* 8007BD38 00078918  54 00 E7 FF */	rlwinm. r0, r0, 0x1c, 0x1f, 0x1f
/* 8007BD3C 0007891C  41 82 00 CC */	beq lbl_8007BE08
/* 8007BD40 00078920  80 1D 00 C0 */	lwz r0, 0xc0(r29)
/* 8007BD44 00078924  2C 00 00 00 */	cmpwi r0, 0
/* 8007BD48 00078928  40 82 00 C0 */	bne lbl_8007BE08
lbl_8007BD4C:
/* 8007BD4C 0007892C  38 7D 00 00 */	addi r3, r29, 0
/* 8007BD50 00078930  38 99 00 00 */	addi r4, r25, 0
/* 8007BD54 00078934  4B F8 EF A9 */	bl func_8000ACFC
/* 8007BD58 00078938  2C 03 00 00 */	cmpwi r3, 0
/* 8007BD5C 0007893C  40 82 00 AC */	bne lbl_8007BE08
/* 8007BD60 00078940  3B 00 00 00 */	li r24, 0
/* 8007BD64 00078944  1C 18 00 44 */	mulli r0, r24, 0x44
/* 8007BD68 00078948  7F 9D 02 14 */	add r28, r29, r0
/* 8007BD6C 0007894C  48 00 00 90 */	b lbl_8007BDFC
lbl_8007BD70:
/* 8007BD70 00078950  C0 3F 00 38 */	lfs f1, 0x38(r31)
/* 8007BD74 00078954  7F 23 CB 78 */	mr r3, r25
/* 8007BD78 00078958  C0 5D 00 38 */	lfs f2, 0x38(r29)
/* 8007BD7C 0007895C  38 9C 0A CC */	addi r4, r28, 0xacc
/* 8007BD80 00078960  C0 62 89 00 */	lfs f3, lbl_804D82E0@sda21(r2)
/* 8007BD84 00078964  38 A0 00 00 */	li r5, 0
/* 8007BD88 00078968  4B F8 C1 45 */	bl func_80007ECC
/* 8007BD8C 0007896C  2C 03 00 00 */	cmpwi r3, 0
/* 8007BD90 00078970  41 82 00 64 */	beq lbl_8007BDF4
/* 8007BD94 00078974  38 7F 00 00 */	addi r3, r31, 0
/* 8007BD98 00078978  38 99 00 00 */	addi r4, r25, 0
/* 8007BD9C 0007897C  38 DD 00 00 */	addi r6, r29, 0
/* 8007BDA0 00078980  38 A0 00 00 */	li r5, 0
/* 8007BDA4 00078984  38 E0 00 00 */	li r7, 0
/* 8007BDA8 00078988  4B FF AA 61 */	bl func_80076808
/* 8007BDAC 0007898C  C0 3D 00 4C */	lfs f1, 0x4c(r29)
/* 8007BDB0 00078990  C0 1F 00 B0 */	lfs f0, 0xb0(r31)
/* 8007BDB4 00078994  EC 21 00 28 */	fsubs f1, f1, f0
/* 8007BDB8 00078998  FC 01 F8 40 */	fcmpo cr0, f1, f31
/* 8007BDBC 0007899C  40 80 00 08 */	bge lbl_8007BDC4
/* 8007BDC0 000789A0  FC 20 08 50 */	fneg f1, f1
lbl_8007BDC4:
/* 8007BDC4 000789A4  C0 1F 21 6C */	lfs f0, 0x216c(r31)
/* 8007BDC8 000789A8  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8007BDCC 000789AC  40 80 00 4C */	bge lbl_8007BE18
/* 8007BDD0 000789B0  80 1D 00 04 */	lwz r0, 4(r29)
/* 8007BDD4 000789B4  38 60 00 01 */	li r3, 1
/* 8007BDD8 000789B8  90 1F 1A 64 */	stw r0, 0x1a64(r31)
/* 8007BDDC 000789BC  90 1F 1A 60 */	stw r0, 0x1a60(r31)
/* 8007BDE0 000789C0  88 1F 22 1B */	lbz r0, 0x221b(r31)
/* 8007BDE4 000789C4  50 60 0F BC */	rlwimi r0, r3, 1, 0x1e, 0x1e
/* 8007BDE8 000789C8  98 1F 22 1B */	stb r0, 0x221b(r31)
/* 8007BDEC 000789CC  D0 3F 21 6C */	stfs f1, 0x216c(r31)
/* 8007BDF0 000789D0  48 00 00 28 */	b lbl_8007BE18
lbl_8007BDF4:
/* 8007BDF4 000789D4  3B 9C 00 44 */	addi r28, r28, 0x44
/* 8007BDF8 000789D8  3B 18 00 01 */	addi r24, r24, 1
lbl_8007BDFC:
/* 8007BDFC 000789DC  88 1D 0A C8 */	lbz r0, 0xac8(r29)
/* 8007BE00 000789E0  7C 18 00 40 */	cmplw r24, r0
/* 8007BE04 000789E4  41 80 FF 6C */	blt lbl_8007BD70
lbl_8007BE08:
/* 8007BE08 000789E8  3B 5A 00 01 */	addi r26, r26, 1
/* 8007BE0C 000789EC  28 1A 00 04 */	cmplwi r26, 4
/* 8007BE10 000789F0  3B 7B 01 38 */	addi r27, r27, 0x138
/* 8007BE14 000789F4  41 80 FE E8 */	blt lbl_8007BCFC
lbl_8007BE18:
/* 8007BE18 000789F8  83 DE 00 08 */	lwz r30, 8(r30)
lbl_8007BE1C:
/* 8007BE1C 000789FC  28 1E 00 00 */	cmplwi r30, 0
/* 8007BE20 00078A00  40 82 FE A8 */	bne lbl_8007BCC8
/* 8007BE24 00078A04  BB 01 00 20 */	lmw r24, 0x20(r1)
/* 8007BE28 00078A08  80 01 00 4C */	lwz r0, 0x4c(r1)
/* 8007BE2C 00078A0C  CB E1 00 40 */	lfd f31, 0x40(r1)
/* 8007BE30 00078A10  38 21 00 48 */	addi r1, r1, 0x48
/* 8007BE34 00078A14  7C 08 03 A6 */	mtlr r0
/* 8007BE38 00078A18  4E 80 00 20 */	blr 

.global func_8007BE3C
func_8007BE3C:
/* 8007BE3C 00078A1C  7C 08 02 A6 */	mflr r0
/* 8007BE40 00078A20  90 01 00 04 */	stw r0, 4(r1)
/* 8007BE44 00078A24  94 21 FF 98 */	stwu r1, -0x68(r1)
/* 8007BE48 00078A28  DB E1 00 60 */	stfd f31, 0x60(r1)
/* 8007BE4C 00078A2C  BF 41 00 48 */	stmw r26, 0x48(r1)
/* 8007BE50 00078A30  7C 7D 1B 78 */	mr r29, r3
/* 8007BE54 00078A34  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 8007BE58 00078A38  3C 60 80 3C */	lis r3, lbl_803C0C40@ha
/* 8007BE5C 00078A3C  C0 02 89 00 */	lfs f0, lbl_804D82E0@sda21(r2)
/* 8007BE60 00078A40  3B E3 0C 40 */	addi r31, r3, lbl_803C0C40@l
/* 8007BE64 00078A44  C0 3E 18 98 */	lfs f1, 0x1898(r30)
/* 8007BE68 00078A48  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8007BE6C 00078A4C  41 82 00 2C */	beq lbl_8007BE98
/* 8007BE70 00078A50  FC 00 08 1E */	fctiwz f0, f1
/* 8007BE74 00078A54  D8 01 00 40 */	stfd f0, 0x40(r1)
/* 8007BE78 00078A58  80 01 00 44 */	lwz r0, 0x44(r1)
/* 8007BE7C 00078A5C  2C 00 00 00 */	cmpwi r0, 0
/* 8007BE80 00078A60  41 82 00 10 */	beq lbl_8007BE90
/* 8007BE84 00078A64  D8 01 00 40 */	stfd f0, 0x40(r1)
/* 8007BE88 00078A68  83 61 00 44 */	lwz r27, 0x44(r1)
/* 8007BE8C 00078A6C  48 00 00 10 */	b lbl_8007BE9C
lbl_8007BE90:
/* 8007BE90 00078A70  3B 60 00 01 */	li r27, 1
/* 8007BE94 00078A74  48 00 00 08 */	b lbl_8007BE9C
lbl_8007BE98:
/* 8007BE98 00078A78  3B 60 00 00 */	li r27, 0
lbl_8007BE9C:
/* 8007BE9C 00078A7C  88 1E 22 1C */	lbz r0, 0x221c(r30)
/* 8007BEA0 00078A80  54 00 EF FF */	rlwinm. r0, r0, 0x1d, 0x1f, 0x1f
/* 8007BEA4 00078A84  41 82 00 3C */	beq lbl_8007BEE0
/* 8007BEA8 00078A88  C0 3E 18 34 */	lfs f1, 0x1834(r30)
/* 8007BEAC 00078A8C  C0 1E 18 98 */	lfs f0, 0x1898(r30)
/* 8007BEB0 00078A90  EC 01 00 28 */	fsubs f0, f1, f0
/* 8007BEB4 00078A94  D0 1E 18 34 */	stfs f0, 0x1834(r30)
/* 8007BEB8 00078A98  C0 3E 18 34 */	lfs f1, 0x1834(r30)
/* 8007BEBC 00078A9C  C0 02 89 00 */	lfs f0, lbl_804D82E0@sda21(r2)
/* 8007BEC0 00078AA0  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8007BEC4 00078AA4  40 80 00 1C */	bge lbl_8007BEE0
/* 8007BEC8 00078AA8  FC 00 08 50 */	fneg f0, f1
/* 8007BECC 00078AAC  38 60 00 00 */	li r3, 0
/* 8007BED0 00078AB0  D0 1E 18 98 */	stfs f0, 0x1898(r30)
/* 8007BED4 00078AB4  88 1E 22 1C */	lbz r0, 0x221c(r30)
/* 8007BED8 00078AB8  50 60 1F 38 */	rlwimi r0, r3, 3, 0x1c, 0x1c
/* 8007BEDC 00078ABC  98 1E 22 1C */	stb r0, 0x221c(r30)
lbl_8007BEE0:
/* 8007BEE0 00078AC0  88 1E 22 1C */	lbz r0, 0x221c(r30)
/* 8007BEE4 00078AC4  54 00 EF FF */	rlwinm. r0, r0, 0x1d, 0x1f, 0x1f
/* 8007BEE8 00078AC8  40 82 00 58 */	bne lbl_8007BF40
/* 8007BEEC 00078ACC  C0 3E 18 98 */	lfs f1, 0x1898(r30)
/* 8007BEF0 00078AD0  C0 02 89 04 */	lfs f0, lbl_804D82E4@sda21(r2)
/* 8007BEF4 00078AD4  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8007BEF8 00078AD8  40 81 00 20 */	ble lbl_8007BF18
/* 8007BEFC 00078ADC  38 7F 00 18 */	addi r3, r31, 0x18
/* 8007BF00 00078AE0  4C C6 32 42 */	crset 6
/* 8007BF04 00078AE4  48 2C 97 A5 */	bl OSReport
/* 8007BF08 00078AE8  38 7F 00 34 */	addi r3, r31, 0x34
/* 8007BF0C 00078AEC  38 80 00 B7 */	li r4, 0xb7
/* 8007BF10 00078AF0  38 AD 83 C8 */	addi r5, r13, lbl_804D3A68@sda21
/* 8007BF14 00078AF4  48 30 C3 0D */	bl __assert
lbl_8007BF18:
/* 8007BF18 00078AF8  C0 3E 18 38 */	lfs f1, 0x1838(r30)
/* 8007BF1C 00078AFC  C0 1E 18 98 */	lfs f0, 0x1898(r30)
/* 8007BF20 00078B00  EC 01 00 2A */	fadds f0, f1, f0
/* 8007BF24 00078B04  D0 1E 18 38 */	stfs f0, 0x1838(r30)
/* 8007BF28 00078B08  80 1E 18 3C */	lwz r0, 0x183c(r30)
/* 8007BF2C 00078B0C  7C 1B 00 00 */	cmpw r27, r0
/* 8007BF30 00078B10  40 81 00 08 */	ble lbl_8007BF38
/* 8007BF34 00078B14  93 7E 18 3C */	stw r27, 0x183c(r30)
lbl_8007BF38:
/* 8007BF38 00078B18  38 00 00 01 */	li r0, 1
/* 8007BF3C 00078B1C  48 00 00 08 */	b lbl_8007BF44
lbl_8007BF40:
/* 8007BF40 00078B20  38 00 00 00 */	li r0, 0
lbl_8007BF44:
/* 8007BF44 00078B24  2C 00 00 00 */	cmpwi r0, 0
/* 8007BF48 00078B28  41 82 01 B4 */	beq lbl_8007C0FC
/* 8007BF4C 00078B2C  83 5E 18 94 */	lwz r26, 0x1894(r30)
/* 8007BF50 00078B30  A0 1A 00 00 */	lhz r0, 0(r26)
/* 8007BF54 00078B34  2C 00 00 05 */	cmpwi r0, 5
/* 8007BF58 00078B38  41 82 00 D4 */	beq lbl_8007C02C
/* 8007BF5C 00078B3C  40 80 00 10 */	bge lbl_8007BF6C
/* 8007BF60 00078B40  2C 00 00 04 */	cmpwi r0, 4
/* 8007BF64 00078B44  40 80 00 14 */	bge lbl_8007BF78
/* 8007BF68 00078B48  48 00 00 C4 */	b lbl_8007C02C
lbl_8007BF6C:
/* 8007BF6C 00078B4C  2C 00 00 07 */	cmpwi r0, 7
/* 8007BF70 00078B50  40 80 00 BC */	bge lbl_8007C02C
/* 8007BF74 00078B54  48 00 00 54 */	b lbl_8007BFC8
lbl_8007BF78:
/* 8007BF78 00078B58  83 9E 00 00 */	lwz r28, 0(r30)
/* 8007BF7C 00078B5C  38 7A 00 00 */	addi r3, r26, 0
/* 8007BF80 00078B60  C3 FE 18 98 */	lfs f31, 0x1898(r30)
/* 8007BF84 00078B64  38 9C 00 00 */	addi r4, r28, 0
/* 8007BF88 00078B68  4B FB B2 A5 */	bl func_8003722C
/* 8007BF8C 00078B6C  38 7A 00 00 */	addi r3, r26, 0
/* 8007BF90 00078B70  38 9C 00 00 */	addi r4, r28, 0
/* 8007BF94 00078B74  4B FF A4 B1 */	bl func_80076444
/* 8007BF98 00078B78  80 FA 00 2C */	lwz r7, 0x2c(r26)
/* 8007BF9C 00078B7C  FC 20 F8 90 */	fmr f1, f31
/* 8007BFA0 00078B80  80 BC 00 2C */	lwz r5, 0x2c(r28)
/* 8007BFA4 00078B84  88 87 22 1F */	lbz r4, 0x221f(r7)
/* 8007BFA8 00078B88  88 C5 22 1F */	lbz r6, 0x221f(r5)
/* 8007BFAC 00078B8C  88 67 00 0C */	lbz r3, 0xc(r7)
/* 8007BFB0 00078B90  54 84 EF FE */	rlwinm r4, r4, 0x1d, 0x1f, 0x1f
/* 8007BFB4 00078B94  88 A5 00 0C */	lbz r5, 0xc(r5)
/* 8007BFB8 00078B98  54 C6 EF FE */	rlwinm r6, r6, 0x1d, 0x1f, 0x1f
/* 8007BFBC 00078B9C  88 E7 20 73 */	lbz r7, 0x2073(r7)
/* 8007BFC0 00078BA0  4B FC 2B 71 */	bl func_8003EB30
/* 8007BFC4 00078BA4  48 00 00 68 */	b lbl_8007C02C
lbl_8007BFC8:
/* 8007BFC8 00078BA8  83 7E 00 00 */	lwz r27, 0(r30)
/* 8007BFCC 00078BAC  38 7A 00 00 */	addi r3, r26, 0
/* 8007BFD0 00078BB0  C3 FE 18 98 */	lfs f31, 0x1898(r30)
/* 8007BFD4 00078BB4  38 9B 00 00 */	addi r4, r27, 0
/* 8007BFD8 00078BB8  4B FB B3 F5 */	bl func_800373CC
/* 8007BFDC 00078BBC  38 7A 00 00 */	addi r3, r26, 0
/* 8007BFE0 00078BC0  38 9B 00 00 */	addi r4, r27, 0
/* 8007BFE4 00078BC4  4B FF A4 89 */	bl func_8007646C
/* 8007BFE8 00078BC8  83 9A 00 2C */	lwz r28, 0x2c(r26)
/* 8007BFEC 00078BCC  80 7C 05 18 */	lwz r3, 0x518(r28)
/* 8007BFF0 00078BD0  48 00 A9 71 */	bl func_80086960
/* 8007BFF4 00078BD4  2C 03 00 00 */	cmpwi r3, 0
/* 8007BFF8 00078BD8  41 82 00 34 */	beq lbl_8007C02C
/* 8007BFFC 00078BDC  80 7C 05 18 */	lwz r3, 0x518(r28)
/* 8007C000 00078BE0  FC 20 F8 90 */	fmr f1, f31
/* 8007C004 00078BE4  80 BB 00 2C */	lwz r5, 0x2c(r27)
/* 8007C008 00078BE8  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8007C00C 00078BEC  88 C5 22 1F */	lbz r6, 0x221f(r5)
/* 8007C010 00078BF0  88 83 22 1F */	lbz r4, 0x221f(r3)
/* 8007C014 00078BF4  88 63 00 0C */	lbz r3, 0xc(r3)
/* 8007C018 00078BF8  54 C6 EF FE */	rlwinm r6, r6, 0x1d, 0x1f, 0x1f
/* 8007C01C 00078BFC  88 A5 00 0C */	lbz r5, 0xc(r5)
/* 8007C020 00078C00  54 84 EF FE */	rlwinm r4, r4, 0x1d, 0x1f, 0x1f
/* 8007C024 00078C04  88 FC 0D 93 */	lbz r7, 0xd93(r28)
/* 8007C028 00078C08  4B FC 2B 09 */	bl func_8003EB30
lbl_8007C02C:
/* 8007C02C 00078C0C  C3 FE 18 7C */	lfs f31, 0x187c(r30)
/* 8007C030 00078C10  C0 3E 18 98 */	lfs f1, 0x1898(r30)
/* 8007C034 00078C14  48 2A 68 8D */	bl __cvt_fp2unsigned
/* 8007C038 00078C18  80 1E 18 8C */	lwz r0, 0x188c(r30)
/* 8007C03C 00078C1C  80 BE 18 90 */	lwz r5, 0x1890(r30)
/* 8007C040 00078C20  54 00 10 3A */	slwi r0, r0, 2
/* 8007C044 00078C24  80 DD 00 2C */	lwz r6, 0x2c(r29)
/* 8007C048 00078C28  7C 9F 02 14 */	add r4, r31, r0
/* 8007C04C 00078C2C  80 04 00 6C */	lwz r0, 0x6c(r4)
/* 8007C050 00078C30  2C 00 04 16 */	cmpwi r0, 0x416
/* 8007C054 00078C34  41 82 00 78 */	beq lbl_8007C0CC
/* 8007C058 00078C38  40 80 00 30 */	bge lbl_8007C088
/* 8007C05C 00078C3C  2C 00 03 EB */	cmpwi r0, 0x3eb
/* 8007C060 00078C40  41 82 00 9C */	beq lbl_8007C0FC
/* 8007C064 00078C44  40 80 00 14 */	bge lbl_8007C078
/* 8007C068 00078C48  2C 00 03 E8 */	cmpwi r0, 0x3e8
/* 8007C06C 00078C4C  41 82 00 34 */	beq lbl_8007C0A0
/* 8007C070 00078C50  40 80 00 5C */	bge lbl_8007C0CC
/* 8007C074 00078C54  48 00 00 88 */	b lbl_8007C0FC
lbl_8007C078:
/* 8007C078 00078C58  2C 00 03 ED */	cmpwi r0, 0x3ed
/* 8007C07C 00078C5C  41 82 00 68 */	beq lbl_8007C0E4
/* 8007C080 00078C60  40 80 00 7C */	bge lbl_8007C0FC
/* 8007C084 00078C64  48 00 00 48 */	b lbl_8007C0CC
lbl_8007C088:
/* 8007C088 00078C68  2C 00 04 E7 */	cmpwi r0, 0x4e7
/* 8007C08C 00078C6C  41 82 00 40 */	beq lbl_8007C0CC
/* 8007C090 00078C70  40 80 00 6C */	bge lbl_8007C0FC
/* 8007C094 00078C74  2C 00 04 79 */	cmpwi r0, 0x479
/* 8007C098 00078C78  41 82 00 34 */	beq lbl_8007C0CC
/* 8007C09C 00078C7C  48 00 00 60 */	b lbl_8007C0FC
lbl_8007C0A0:
/* 8007C0A0 00078C80  90 61 00 44 */	stw r3, 0x44(r1)
/* 8007C0A4 00078C84  3C 00 43 30 */	lis r0, 0x4330
/* 8007C0A8 00078C88  C8 22 89 28 */	lfd f1, lbl_804D8308@sda21(r2)
/* 8007C0AC 00078C8C  FC 40 F8 90 */	fmr f2, f31
/* 8007C0B0 00078C90  90 01 00 40 */	stw r0, 0x40(r1)
/* 8007C0B4 00078C94  7F A3 EB 78 */	mr r3, r29
/* 8007C0B8 00078C98  C8 01 00 40 */	lfd f0, 0x40(r1)
/* 8007C0BC 00078C9C  38 9E 18 80 */	addi r4, r30, 0x1880
/* 8007C0C0 00078CA0  EC 20 08 28 */	fsubs f1, f0, f1
/* 8007C0C4 00078CA4  4B FF C4 75 */	bl func_80078538
/* 8007C0C8 00078CA8  48 00 00 34 */	b lbl_8007C0FC
lbl_8007C0CC:
/* 8007C0CC 00078CAC  7C 03 03 78 */	mr r3, r0
/* 8007C0D0 00078CB0  4C C6 31 82 */	crclr 6
/* 8007C0D4 00078CB4  38 BE 18 80 */	addi r5, r30, 0x1880
/* 8007C0D8 00078CB8  38 80 00 00 */	li r4, 0
/* 8007C0DC 00078CBC  4B FE 3D 01 */	bl ef_Spawn
/* 8007C0E0 00078CC0  48 00 00 1C */	b lbl_8007C0FC
lbl_8007C0E4:
/* 8007C0E4 00078CC4  7C 03 03 78 */	mr r3, r0
/* 8007C0E8 00078CC8  4C C6 31 82 */	crclr 6
/* 8007C0EC 00078CCC  38 BE 18 80 */	addi r5, r30, 0x1880
/* 8007C0F0 00078CD0  38 C6 00 2C */	addi r6, r6, 0x2c
/* 8007C0F4 00078CD4  38 80 00 00 */	li r4, 0
/* 8007C0F8 00078CD8  4B FE 3C E5 */	bl ef_Spawn
lbl_8007C0FC:
/* 8007C0FC 00078CDC  BB 41 00 48 */	lmw r26, 0x48(r1)
/* 8007C100 00078CE0  80 01 00 6C */	lwz r0, 0x6c(r1)
/* 8007C104 00078CE4  CB E1 00 60 */	lfd f31, 0x60(r1)
/* 8007C108 00078CE8  38 21 00 68 */	addi r1, r1, 0x68
/* 8007C10C 00078CEC  7C 08 03 A6 */	mtlr r0
/* 8007C110 00078CF0  4E 80 00 20 */	blr 


.section .data
    .balign 8
.global lbl_803C0C40
lbl_803C0C40:
    .4byte 0x0000008D
    .4byte 0x0000008E
    .4byte 0x0000008F
.global lbl_803C0C4C
lbl_803C0C4C:
    .4byte 0x0000006B
    .4byte 0x0000006C
    .4byte 0x0000006D
.global lbl_803C0C58
lbl_803C0C58:
    .asciz "attack power over 500!! %f\n"
    .balign 4
.global lbl_803C0C74
lbl_803C0C74:
    .asciz "ftcoll.c"
    .balign 4
.global lbl_803C0C80
lbl_803C0C80:
    .asciz "damage log over %d!!\n"
    .balign 4
    .asciz "tip log over %d!!\n"
    .balign 4
.global lbl_803C0CAC
lbl_803C0CAC:
    .4byte 0x000003E8
    .4byte 0x000003EA
    .4byte 0x000003E9
    .4byte 0x000003EC
    .4byte 0x00000479
    .4byte 0x000003ED
    .4byte 0xFFFFFFFF
    .4byte 0xFFFFFFFF
    .4byte 0xFFFFFFFF
    .4byte 0x000003E8
    .4byte 0x000003E8
    .4byte 0xFFFFFFFF
    .4byte 0xFFFFFFFF
    .4byte 0x00000416
    .4byte 0xFFFFFFFF
    .4byte 0xFFFFFFFF
    .4byte NULL
.global lbl_803C0CF0
lbl_803C0CF0:
    .asciz "in ftCollisionSetHitStatus illegal parts!\n"
    .balign 4
    .asciz "fighter hit num over!\n"
    .balign 4
    .asciz "fighter dynamics hit num over!\n"
    .balign 4


.section .bss
    .balign 8
.global lbl_80459278
lbl_80459278:
	.skip 0x320
.global lbl_80459598
lbl_80459598:
	.skip 0x320


.section .sdata
    .balign 8
.global lbl_804D3A68
lbl_804D3A68:
    .asciz "0"
    .balign 4


.section .sbss
    .balign 8
.global lbl_804D6558
lbl_804D6558:
	.skip 0x4
.global lbl_804D655C
lbl_804D655C:
	.skip 0x4
.global lbl_804D6560
lbl_804D6560:
	.skip 0x4


.section .sdata2
    .balign 8
.global lbl_804D82E0
lbl_804D82E0:
	.4byte 0x00000000
.global lbl_804D82E4
lbl_804D82E4:
	.4byte 0x43FA0000
.global lbl_804D82E8
lbl_804D82E8:
	.4byte 0x3F000000
.global lbl_804D82EC
lbl_804D82EC:
	.4byte 0x3F800000
.global lbl_804D82F0
lbl_804D82F0:
	.4byte 0xBF800000
	.4byte 0x00000000
.global lbl_804D82F8
lbl_804D82F8:
	.4byte 0x43300000
	.4byte 0x80000000
.global lbl_804D8300
lbl_804D8300:
	.4byte 0x3C8EFA35
	.4byte 0x00000000
.global lbl_804D8308
lbl_804D8308:
	.4byte 0x43300000
	.4byte 0x00000000
.global lbl_804D8310
lbl_804D8310:
	.4byte 0x7F7FFFFF
.global lbl_804D8314
lbl_804D8314:
	.4byte 0x3C23D70A
.global lbl_804D8318
lbl_804D8318:
	.4byte 0x3727C5AC
.global lbl_804D831C
lbl_804D831C:
	.4byte 0x42652EE1
