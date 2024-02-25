.include "macros.inc"
.file "ftYs_Init.c"

# 0x8012B6E8 - 0x8012C030
.text
.balign 4

.fn ftYs_Init_8012B6E8, global
/* 8012B6E8 001282C8  7C 08 02 A6 */	mflr r0
/* 8012B6EC 001282CC  90 01 00 04 */	stw r0, 0x4(r1)
/* 8012B6F0 001282D0  94 21 FF A8 */	stwu r1, -0x58(r1)
/* 8012B6F4 001282D4  DB E1 00 50 */	stfd f31, 0x50(r1)
/* 8012B6F8 001282D8  BF 01 00 30 */	stmw r24, 0x30(r1)
/* 8012B6FC 001282DC  7C 7F 1B 78 */	mr r31, r3
/* 8012B700 001282E0  3B 20 00 00 */	li r25, 0x0
/* 8012B704 001282E4  80 A4 00 04 */	lwz r5, 0x4(r4)
/* 8012B708 001282E8  3C 80 80 3D */	lis r4, "@242"@ha
/* 8012B70C 001282EC  80 C3 01 0C */	lwz r6, 0x10c(r3)
/* 8012B710 001282F0  3C 60 80 3D */	lis r3, "@243"@ha
/* 8012B714 001282F4  83 C5 00 0C */	lwz r30, 0xc(r5)
/* 8012B718 001282F8  83 46 00 04 */	lwz r26, 0x4(r6)
/* 8012B71C 001282FC  3B 65 00 08 */	addi r27, r5, 0x8
/* 8012B720 00128300  C3 E2 A0 38 */	lfs f31, "@239"@sda21(r0)
/* 8012B724 00128304  3B 84 EA 50 */	addi r28, r4, "@242"@l
/* 8012B728 00128308  3B A3 EA 70 */	addi r29, r3, "@243"@l
/* 8012B72C 0012830C  48 00 00 B4 */	b .L_8012B7E0
.L_8012B730:
/* 8012B730 00128310  88 1E 00 00 */	lbz r0, 0x0(r30)
/* 8012B734 00128314  80 7F 05 F0 */	lwz r3, 0x5f0(r31)
/* 8012B738 00128318  54 00 10 3A */	slwi r0, r0, 2
/* 8012B73C 0012831C  7C 63 00 2E */	lwzx r3, r3, r0
/* 8012B740 00128320  28 03 00 00 */	cmplwi r3, 0x0
/* 8012B744 00128324  41 82 00 0C */	beq .L_8012B750
/* 8012B748 00128328  80 63 00 08 */	lwz r3, 0x8(r3)
/* 8012B74C 0012832C  48 00 00 08 */	b .L_8012B754
.L_8012B750:
/* 8012B750 00128330  38 60 00 00 */	li r3, 0x0
.L_8012B754:
/* 8012B754 00128334  83 03 00 14 */	lwz r24, 0x14(r3)
/* 8012B758 00128338  C0 22 A0 38 */	lfs f1, "@239"@sda21(r0)
/* 8012B75C 0012833C  7F 03 C3 78 */	mr r3, r24
/* 8012B760 00128340  48 23 9B AD */	bl HSD_AObjSetRate
/* 8012B764 00128344  C0 1A 00 0C */	lfs f0, 0xc(r26)
/* 8012B768 00128348  FC 1F 00 00 */	fcmpu cr0, f31, f0
/* 8012B76C 0012834C  40 82 00 28 */	bne .L_8012B794
/* 8012B770 00128350  28 18 00 00 */	cmplwi r24, 0x0
/* 8012B774 00128354  40 82 00 14 */	bne .L_8012B788
/* 8012B778 00128358  38 6D 87 A0 */	li r3, "@240"@sda21
/* 8012B77C 0012835C  38 80 00 AA */	li r4, 0xaa
/* 8012B780 00128360  38 AD 87 A8 */	li r5, "@241"@sda21
/* 8012B784 00128364  48 25 CA 9D */	bl __assert
.L_8012B788:
/* 8012B788 00128368  C0 18 00 0C */	lfs f0, 0xc(r24)
/* 8012B78C 0012836C  D0 1A 00 0C */	stfs f0, 0xc(r26)
/* 8012B790 00128370  48 00 00 48 */	b .L_8012B7D8
.L_8012B794:
/* 8012B794 00128374  28 18 00 00 */	cmplwi r24, 0x0
/* 8012B798 00128378  40 82 00 14 */	bne .L_8012B7AC
/* 8012B79C 0012837C  38 6D 87 A0 */	li r3, "@240"@sda21
/* 8012B7A0 00128380  38 80 00 AA */	li r4, 0xaa
/* 8012B7A4 00128384  38 AD 87 A8 */	li r5, "@241"@sda21
/* 8012B7A8 00128388  48 25 CA 79 */	bl __assert
.L_8012B7AC:
/* 8012B7AC 0012838C  C0 3A 00 0C */	lfs f1, 0xc(r26)
/* 8012B7B0 00128390  C0 18 00 0C */	lfs f0, 0xc(r24)
/* 8012B7B4 00128394  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8012B7B8 00128398  41 82 00 20 */	beq .L_8012B7D8
/* 8012B7BC 0012839C  38 7C 00 00 */	addi r3, r28, 0x0
/* 8012B7C0 001283A0  4C C6 31 82 */	crclr cr1eq
/* 8012B7C4 001283A4  48 21 9E E5 */	bl OSReport
/* 8012B7C8 001283A8  38 7D 00 00 */	addi r3, r29, 0x0
/* 8012B7CC 001283AC  38 80 00 61 */	li r4, 0x61
/* 8012B7D0 001283B0  38 AD 87 B0 */	li r5, "@244"@sda21
/* 8012B7D4 001283B4  48 25 CA 4D */	bl __assert
.L_8012B7D8:
/* 8012B7D8 001283B8  3B 39 00 01 */	addi r25, r25, 0x1
/* 8012B7DC 001283BC  3B DE 00 01 */	addi r30, r30, 0x1
.L_8012B7E0:
/* 8012B7E0 001283C0  80 1B 00 00 */	lwz r0, 0x0(r27)
/* 8012B7E4 001283C4  7C 19 00 00 */	cmpw r25, r0
/* 8012B7E8 001283C8  41 80 FF 48 */	blt .L_8012B730
/* 8012B7EC 001283CC  BB 01 00 30 */	lmw r24, 0x30(r1)
/* 8012B7F0 001283D0  80 01 00 5C */	lwz r0, 0x5c(r1)
/* 8012B7F4 001283D4  CB E1 00 50 */	lfd f31, 0x50(r1)
/* 8012B7F8 001283D8  38 21 00 58 */	addi r1, r1, 0x58
/* 8012B7FC 001283DC  7C 08 03 A6 */	mtlr r0
/* 8012B800 001283E0  4E 80 00 20 */	blr
.endfn ftYs_Init_8012B6E8

.fn ftYs_Init_8012B804, global
/* 8012B804 001283E4  7C 08 02 A6 */	mflr r0
/* 8012B808 001283E8  28 04 00 00 */	cmplwi r4, 0x0
/* 8012B80C 001283EC  90 01 00 04 */	stw r0, 0x4(r1)
/* 8012B810 001283F0  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 8012B814 001283F4  DB E1 00 38 */	stfd f31, 0x38(r1)
/* 8012B818 001283F8  FF E0 08 90 */	fmr f31, f1
/* 8012B81C 001283FC  BF 61 00 24 */	stmw r27, 0x24(r1)
/* 8012B820 00128400  3B 63 00 00 */	addi r27, r3, 0x0
/* 8012B824 00128404  41 82 00 68 */	beq .L_8012B88C
/* 8012B828 00128408  80 64 00 04 */	lwz r3, 0x4(r4)
/* 8012B82C 0012840C  3B A0 00 00 */	li r29, 0x0
/* 8012B830 00128410  83 E3 00 0C */	lwz r31, 0xc(r3)
/* 8012B834 00128414  3B C3 00 08 */	addi r30, r3, 0x8
/* 8012B838 00128418  48 00 00 48 */	b .L_8012B880
.L_8012B83C:
/* 8012B83C 0012841C  88 1F 00 00 */	lbz r0, 0x0(r31)
/* 8012B840 00128420  80 7B 05 F0 */	lwz r3, 0x5f0(r27)
/* 8012B844 00128424  54 00 10 3A */	slwi r0, r0, 2
/* 8012B848 00128428  7C 63 00 2E */	lwzx r3, r3, r0
/* 8012B84C 0012842C  28 03 00 00 */	cmplwi r3, 0x0
/* 8012B850 00128430  41 82 00 0C */	beq .L_8012B85C
/* 8012B854 00128434  80 03 00 08 */	lwz r0, 0x8(r3)
/* 8012B858 00128438  48 00 00 08 */	b .L_8012B860
.L_8012B85C:
/* 8012B85C 0012843C  38 00 00 00 */	li r0, 0x0
.L_8012B860:
/* 8012B860 00128440  FC 20 F8 90 */	fmr f1, f31
/* 8012B864 00128444  7C 1C 03 78 */	mr r28, r0
/* 8012B868 00128448  38 7C 00 00 */	addi r3, r28, 0x0
/* 8012B86C 0012844C  48 23 76 2D */	bl HSD_MObjReqAnim
/* 8012B870 00128450  7F 83 E3 78 */	mr r3, r28
/* 8012B874 00128454  48 23 78 89 */	bl HSD_MObjAnim
/* 8012B878 00128458  3B BD 00 01 */	addi r29, r29, 0x1
/* 8012B87C 0012845C  3B FF 00 01 */	addi r31, r31, 0x1
.L_8012B880:
/* 8012B880 00128460  80 1E 00 00 */	lwz r0, 0x0(r30)
/* 8012B884 00128464  7C 1D 00 00 */	cmpw r29, r0
/* 8012B888 00128468  41 80 FF B4 */	blt .L_8012B83C
.L_8012B88C:
/* 8012B88C 0012846C  BB 61 00 24 */	lmw r27, 0x24(r1)
/* 8012B890 00128470  80 01 00 44 */	lwz r0, 0x44(r1)
/* 8012B894 00128474  CB E1 00 38 */	lfd f31, 0x38(r1)
/* 8012B898 00128478  38 21 00 40 */	addi r1, r1, 0x40
/* 8012B89C 0012847C  7C 08 03 A6 */	mtlr r0
/* 8012B8A0 00128480  4E 80 00 20 */	blr
.endfn ftYs_Init_8012B804

.fn ftYs_Init_8012B8A4, global
/* 8012B8A4 00128484  7C 08 02 A6 */	mflr r0
/* 8012B8A8 00128488  90 01 00 04 */	stw r0, 0x4(r1)
/* 8012B8AC 0012848C  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 8012B8B0 00128490  DB E1 00 28 */	stfd f31, 0x28(r1)
/* 8012B8B4 00128494  93 E1 00 24 */	stw r31, 0x24(r1)
/* 8012B8B8 00128498  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8012B8BC 0012849C  80 8D AE B4 */	lwz r4, p_ftCommonData@sda21(r0)
/* 8012B8C0 001284A0  C0 3F 19 98 */	lfs f1, 0x1998(r31)
/* 8012B8C4 001284A4  7F E3 FB 78 */	mr r3, r31
/* 8012B8C8 001284A8  C0 04 02 60 */	lfs f0, 0x260(r4)
/* 8012B8CC 001284AC  80 9F 02 D4 */	lwz r4, 0x2d4(r31)
/* 8012B8D0 001284B0  EC 01 00 24 */	fdivs f0, f1, f0
/* 8012B8D4 001284B4  C0 22 A0 3C */	lfs f1, "@259"@sda21(r0)
/* 8012B8D8 001284B8  C0 44 00 0C */	lfs f2, 0xc(r4)
/* 8012B8DC 001284BC  80 9F 05 B8 */	lwz r4, 0x5b8(r31)
/* 8012B8E0 001284C0  EC 01 00 28 */	fsubs f0, f1, f0
/* 8012B8E4 001284C4  EF E2 00 32 */	fmuls f31, f2, f0
/* 8012B8E8 001284C8  FC 20 F8 90 */	fmr f1, f31
/* 8012B8EC 001284CC  4B FF FF 19 */	bl ftYs_Init_8012B804
/* 8012B8F0 001284D0  FC 20 F8 90 */	fmr f1, f31
/* 8012B8F4 001284D4  80 9F 05 BC */	lwz r4, 0x5bc(r31)
/* 8012B8F8 001284D8  7F E3 FB 78 */	mr r3, r31
/* 8012B8FC 001284DC  4B FF FF 09 */	bl ftYs_Init_8012B804
/* 8012B900 001284E0  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8012B904 001284E4  CB E1 00 28 */	lfd f31, 0x28(r1)
/* 8012B908 001284E8  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 8012B90C 001284EC  38 21 00 30 */	addi r1, r1, 0x30
/* 8012B910 001284F0  7C 08 03 A6 */	mtlr r0
/* 8012B914 001284F4  4E 80 00 20 */	blr
.endfn ftYs_Init_8012B8A4

.fn ftYs_Init_8012B918, global
/* 8012B918 001284F8  7C 08 02 A6 */	mflr r0
/* 8012B91C 001284FC  90 01 00 04 */	stw r0, 0x4(r1)
/* 8012B920 00128500  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8012B924 00128504  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8012B928 00128508  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8012B92C 0012850C  C0 22 A0 38 */	lfs f1, "@239"@sda21(r0)
/* 8012B930 00128510  80 9F 05 B8 */	lwz r4, 0x5b8(r31)
/* 8012B934 00128514  7F E3 FB 78 */	mr r3, r31
/* 8012B938 00128518  4B FF FE CD */	bl ftYs_Init_8012B804
/* 8012B93C 0012851C  80 9F 05 BC */	lwz r4, 0x5bc(r31)
/* 8012B940 00128520  7F E3 FB 78 */	mr r3, r31
/* 8012B944 00128524  C0 22 A0 38 */	lfs f1, "@239"@sda21(r0)
/* 8012B948 00128528  4B FF FE BD */	bl ftYs_Init_8012B804
/* 8012B94C 0012852C  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8012B950 00128530  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8012B954 00128534  38 21 00 18 */	addi r1, r1, 0x18
/* 8012B958 00128538  7C 08 03 A6 */	mtlr r0
/* 8012B95C 0012853C  4E 80 00 20 */	blr
.endfn ftYs_Init_8012B918

.fn ftYs_Init_OnDeath, global
/* 8012B960 00128540  7C 08 02 A6 */	mflr r0
/* 8012B964 00128544  38 80 00 00 */	li r4, 0x0
/* 8012B968 00128548  90 01 00 04 */	stw r0, 0x4(r1)
/* 8012B96C 0012854C  38 A0 00 00 */	li r5, 0x0
/* 8012B970 00128550  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8012B974 00128554  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8012B978 00128558  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8012B97C 0012855C  4B F4 90 D1 */	bl ftParts_80074A4C
/* 8012B980 00128560  38 00 00 00 */	li r0, 0x0
/* 8012B984 00128564  90 1F 22 38 */	stw r0, 0x2238(r31)
/* 8012B988 00128568  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8012B98C 0012856C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8012B990 00128570  38 21 00 18 */	addi r1, r1, 0x18
/* 8012B994 00128574  7C 08 03 A6 */	mtlr r0
/* 8012B998 00128578  4E 80 00 20 */	blr
.endfn ftYs_Init_OnDeath

.fn ftYs_Init_OnLoad, global
/* 8012B99C 0012857C  7C 08 02 A6 */	mflr r0
/* 8012B9A0 00128580  90 01 00 04 */	stw r0, 0x4(r1)
/* 8012B9A4 00128584  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 8012B9A8 00128588  BF 61 00 1C */	stmw r27, 0x1c(r1)
/* 8012B9AC 0012858C  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8012B9B0 00128590  83 7F 05 B8 */	lwz r27, 0x5b8(r31)
/* 8012B9B4 00128594  80 7F 01 0C */	lwz r3, 0x10c(r31)
/* 8012B9B8 00128598  28 1B 00 00 */	cmplwi r27, 0x0
/* 8012B9BC 0012859C  83 9F 05 BC */	lwz r28, 0x5bc(r31)
/* 8012B9C0 001285A0  83 C3 00 48 */	lwz r30, 0x48(r3)
/* 8012B9C4 001285A4  83 A3 00 04 */	lwz r29, 0x4(r3)
/* 8012B9C8 001285A8  40 82 00 28 */	bne .L_8012B9F0
/* 8012B9CC 001285AC  3C 60 80 3D */	lis r3, "@273"@ha
/* 8012B9D0 001285B0  4C C6 31 82 */	crclr cr1eq
/* 8012B9D4 001285B4  38 63 EA 7C */	addi r3, r3, "@273"@l
/* 8012B9D8 001285B8  48 21 9C D1 */	bl OSReport
/* 8012B9DC 001285BC  3C 60 80 3D */	lis r3, "@243"@ha
/* 8012B9E0 001285C0  38 63 EA 70 */	addi r3, r3, "@243"@l
/* 8012B9E4 001285C4  38 80 00 71 */	li r4, 0x71
/* 8012B9E8 001285C8  38 AD 87 B0 */	li r5, "@244"@sda21
/* 8012B9EC 001285CC  48 25 C8 35 */	bl __assert
.L_8012B9F0:
/* 8012B9F0 001285D0  C0 02 A0 38 */	lfs f0, "@239"@sda21(r0)
/* 8012B9F4 001285D4  38 7F 00 00 */	addi r3, r31, 0x0
/* 8012B9F8 001285D8  38 9B 00 00 */	addi r4, r27, 0x0
/* 8012B9FC 001285DC  D0 1D 00 0C */	stfs f0, 0xc(r29)
/* 8012BA00 001285E0  4B FF FC E9 */	bl ftYs_Init_8012B6E8
/* 8012BA04 001285E4  38 7F 00 00 */	addi r3, r31, 0x0
/* 8012BA08 001285E8  38 9C 00 00 */	addi r4, r28, 0x0
/* 8012BA0C 001285EC  4B FF FC DD */	bl ftYs_Init_8012B6E8
/* 8012BA10 001285F0  80 7F 01 0C */	lwz r3, 0x10c(r31)
/* 8012BA14 001285F4  38 00 00 27 */	li r0, 0x27
/* 8012BA18 001285F8  80 DF 02 D8 */	lwz r6, 0x2d8(r31)
/* 8012BA1C 001285FC  7C 09 03 A6 */	mtctr r0
/* 8012BA20 00128600  80 63 00 04 */	lwz r3, 0x4(r3)
/* 8012BA24 00128604  38 A6 FF F8 */	subi r5, r6, 0x8
/* 8012BA28 00128608  38 83 FF F8 */	subi r4, r3, 0x8
.L_8012BA2C:
/* 8012BA2C 0012860C  84 64 00 08 */	lwzu r3, 0x8(r4)
/* 8012BA30 00128610  80 04 00 04 */	lwz r0, 0x4(r4)
/* 8012BA34 00128614  94 65 00 08 */	stwu r3, 0x8(r5)
/* 8012BA38 00128618  90 05 00 04 */	stw r0, 0x4(r5)
/* 8012BA3C 0012861C  42 00 FF F0 */	bdnz .L_8012BA2C
/* 8012BA40 00128620  90 DF 02 D4 */	stw r6, 0x2d4(r31)
/* 8012BA44 00128624  38 80 00 56 */	li r4, 0x56
/* 8012BA48 00128628  80 7E 00 00 */	lwz r3, 0x0(r30)
/* 8012BA4C 0012862C  48 13 F9 AD */	bl it_8026B3F8
/* 8012BA50 00128630  80 7E 00 04 */	lwz r3, 0x4(r30)
/* 8012BA54 00128634  38 80 00 58 */	li r4, 0x58
/* 8012BA58 00128638  48 13 F9 A1 */	bl it_8026B3F8
/* 8012BA5C 0012863C  80 7E 00 08 */	lwz r3, 0x8(r30)
/* 8012BA60 00128640  38 80 00 57 */	li r4, 0x57
/* 8012BA64 00128644  48 13 F9 95 */	bl it_8026B3F8
/* 8012BA68 00128648  88 1F 22 26 */	lbz r0, 0x2226(r31)
/* 8012BA6C 0012864C  38 60 00 01 */	li r3, 0x1
/* 8012BA70 00128650  50 60 36 72 */	rlwimi r0, r3, 6, 25, 25
/* 8012BA74 00128654  98 1F 22 26 */	stb r0, 0x2226(r31)
/* 8012BA78 00128658  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8012BA7C 0012865C  BB 61 00 1C */	lmw r27, 0x1c(r1)
/* 8012BA80 00128660  38 21 00 30 */	addi r1, r1, 0x30
/* 8012BA84 00128664  7C 08 03 A6 */	mtlr r0
/* 8012BA88 00128668  4E 80 00 20 */	blr
.endfn ftYs_Init_OnLoad

.fn ftYs_Init_8012BA8C, global
/* 8012BA8C 0012866C  7C 08 02 A6 */	mflr r0
/* 8012BA90 00128670  90 01 00 04 */	stw r0, 0x4(r1)
/* 8012BA94 00128674  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8012BA98 00128678  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8012BA9C 0012867C  7C 7F 1B 78 */	mr r31, r3
/* 8012BAA0 00128680  48 00 27 D1 */	bl ftYs_SpecialS_8012E270
/* 8012BAA4 00128684  7F E3 FB 78 */	mr r3, r31
/* 8012BAA8 00128688  48 00 24 71 */	bl ftYs_SpecialS_8012DF18
/* 8012BAAC 0012868C  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8012BAB0 00128690  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8012BAB4 00128694  38 21 00 18 */	addi r1, r1, 0x18
/* 8012BAB8 00128698  7C 08 03 A6 */	mtlr r0
/* 8012BABC 0012869C  4E 80 00 20 */	blr
.endfn ftYs_Init_8012BA8C

.fn ftYs_Init_8012BAC0, global
/* 8012BAC0 001286A0  80 63 02 D4 */	lwz r3, 0x2d4(r3)
/* 8012BAC4 001286A4  C0 23 01 20 */	lfs f1, 0x120(r3)
/* 8012BAC8 001286A8  4E 80 00 20 */	blr
.endfn ftYs_Init_8012BAC0

.fn ftYs_Init_OnItemPickup, global
/* 8012BACC 001286AC  7C 08 02 A6 */	mflr r0
/* 8012BAD0 001286B0  90 01 00 04 */	stw r0, 0x4(r1)
/* 8012BAD4 001286B4  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 8012BAD8 001286B8  93 E1 00 24 */	stw r31, 0x24(r1)
/* 8012BADC 001286BC  93 C1 00 20 */	stw r30, 0x20(r1)
/* 8012BAE0 001286C0  7C 9E 23 78 */	mr r30, r4
/* 8012BAE4 001286C4  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 8012BAE8 001286C8  7C 7D 1B 78 */	mr r29, r3
/* 8012BAEC 001286CC  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8012BAF0 001286D0  80 7F 19 74 */	lwz r3, 0x1974(r31)
/* 8012BAF4 001286D4  48 13 F7 C1 */	bl it_8026B2B4
/* 8012BAF8 001286D8  2C 03 00 00 */	cmpwi r3, 0x0
/* 8012BAFC 001286DC  40 82 00 94 */	bne .L_8012BB90
/* 8012BB00 001286E0  80 7F 19 74 */	lwz r3, 0x1974(r31)
/* 8012BB04 001286E4  48 13 F8 1D */	bl it_8026B320
/* 8012BB08 001286E8  2C 03 00 03 */	cmpwi r3, 0x3
/* 8012BB0C 001286EC  41 82 00 4C */	beq .L_8012BB58
/* 8012BB10 001286F0  40 80 00 14 */	bge .L_8012BB24
/* 8012BB14 001286F4  2C 03 00 01 */	cmpwi r3, 0x1
/* 8012BB18 001286F8  41 82 00 18 */	beq .L_8012BB30
/* 8012BB1C 001286FC  40 80 00 28 */	bge .L_8012BB44
/* 8012BB20 00128700  48 00 00 5C */	b .L_8012BB7C
.L_8012BB24:
/* 8012BB24 00128704  2C 03 00 05 */	cmpwi r3, 0x5
/* 8012BB28 00128708  40 80 00 54 */	bge .L_8012BB7C
/* 8012BB2C 0012870C  48 00 00 40 */	b .L_8012BB6C
.L_8012BB30:
/* 8012BB30 00128710  38 7D 00 00 */	addi r3, r29, 0x0
/* 8012BB34 00128714  38 80 00 01 */	li r4, 0x1
/* 8012BB38 00128718  38 A0 00 01 */	li r5, 0x1
/* 8012BB3C 0012871C  4B F4 54 79 */	bl ftAnim_80070FB4
/* 8012BB40 00128720  48 00 00 3C */	b .L_8012BB7C
.L_8012BB44:
/* 8012BB44 00128724  38 7D 00 00 */	addi r3, r29, 0x0
/* 8012BB48 00128728  38 80 00 01 */	li r4, 0x1
/* 8012BB4C 0012872C  38 A0 00 00 */	li r5, 0x0
/* 8012BB50 00128730  4B F4 54 65 */	bl ftAnim_80070FB4
/* 8012BB54 00128734  48 00 00 28 */	b .L_8012BB7C
.L_8012BB58:
/* 8012BB58 00128738  38 7D 00 00 */	addi r3, r29, 0x0
/* 8012BB5C 0012873C  38 80 00 01 */	li r4, 0x1
/* 8012BB60 00128740  38 A0 00 02 */	li r5, 0x2
/* 8012BB64 00128744  4B F4 54 51 */	bl ftAnim_80070FB4
/* 8012BB68 00128748  48 00 00 14 */	b .L_8012BB7C
.L_8012BB6C:
/* 8012BB6C 0012874C  38 7D 00 00 */	addi r3, r29, 0x0
/* 8012BB70 00128750  38 80 00 01 */	li r4, 0x1
/* 8012BB74 00128754  38 A0 00 03 */	li r5, 0x3
/* 8012BB78 00128758  4B F4 54 3D */	bl ftAnim_80070FB4
.L_8012BB7C:
/* 8012BB7C 0012875C  2C 1E 00 00 */	cmpwi r30, 0x0
/* 8012BB80 00128760  41 82 00 10 */	beq .L_8012BB90
/* 8012BB84 00128764  38 7D 00 00 */	addi r3, r29, 0x0
/* 8012BB88 00128768  38 80 00 01 */	li r4, 0x1
/* 8012BB8C 0012876C  4B F4 50 BD */	bl ftAnim_80070C48
.L_8012BB90:
/* 8012BB90 00128770  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 8012BB94 00128774  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 8012BB98 00128778  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 8012BB9C 0012877C  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 8012BBA0 00128780  38 21 00 28 */	addi r1, r1, 0x28
/* 8012BBA4 00128784  7C 08 03 A6 */	mtlr r0
/* 8012BBA8 00128788  4E 80 00 20 */	blr
.endfn ftYs_Init_OnItemPickup

.fn ftYs_Init_OnItemInvisible, global
/* 8012BBAC 0012878C  7C 08 02 A6 */	mflr r0
/* 8012BBB0 00128790  90 01 00 04 */	stw r0, 0x4(r1)
/* 8012BBB4 00128794  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8012BBB8 00128798  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8012BBBC 0012879C  7C 7F 1B 78 */	mr r31, r3
/* 8012BBC0 001287A0  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8012BBC4 001287A4  80 63 19 74 */	lwz r3, 0x1974(r3)
/* 8012BBC8 001287A8  48 13 F6 ED */	bl it_8026B2B4
/* 8012BBCC 001287AC  2C 03 00 00 */	cmpwi r3, 0x0
/* 8012BBD0 001287B0  40 82 00 10 */	bne .L_8012BBE0
/* 8012BBD4 001287B4  38 7F 00 00 */	addi r3, r31, 0x0
/* 8012BBD8 001287B8  38 80 00 01 */	li r4, 0x1
/* 8012BBDC 001287BC  4B F4 50 E9 */	bl ftAnim_80070CC4
.L_8012BBE0:
/* 8012BBE0 001287C0  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8012BBE4 001287C4  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8012BBE8 001287C8  38 21 00 18 */	addi r1, r1, 0x18
/* 8012BBEC 001287CC  7C 08 03 A6 */	mtlr r0
/* 8012BBF0 001287D0  4E 80 00 20 */	blr
.endfn ftYs_Init_OnItemInvisible

.fn ftYs_Init_OnItemVisible, global
/* 8012BBF4 001287D4  7C 08 02 A6 */	mflr r0
/* 8012BBF8 001287D8  90 01 00 04 */	stw r0, 0x4(r1)
/* 8012BBFC 001287DC  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8012BC00 001287E0  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8012BC04 001287E4  7C 7F 1B 78 */	mr r31, r3
/* 8012BC08 001287E8  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8012BC0C 001287EC  80 63 19 74 */	lwz r3, 0x1974(r3)
/* 8012BC10 001287F0  48 13 F6 A5 */	bl it_8026B2B4
/* 8012BC14 001287F4  2C 03 00 00 */	cmpwi r3, 0x0
/* 8012BC18 001287F8  40 82 00 10 */	bne .L_8012BC28
/* 8012BC1C 001287FC  38 7F 00 00 */	addi r3, r31, 0x0
/* 8012BC20 00128800  38 80 00 01 */	li r4, 0x1
/* 8012BC24 00128804  4B F4 50 25 */	bl ftAnim_80070C48
.L_8012BC28:
/* 8012BC28 00128808  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8012BC2C 0012880C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8012BC30 00128810  38 21 00 18 */	addi r1, r1, 0x18
/* 8012BC34 00128814  7C 08 03 A6 */	mtlr r0
/* 8012BC38 00128818  4E 80 00 20 */	blr
.endfn ftYs_Init_OnItemVisible

.fn ftYs_Init_OnItemDrop, global
/* 8012BC3C 0012881C  7C 08 02 A6 */	mflr r0
/* 8012BC40 00128820  38 A0 FF FF */	li r5, -0x1
/* 8012BC44 00128824  90 01 00 04 */	stw r0, 0x4(r1)
/* 8012BC48 00128828  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8012BC4C 0012882C  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8012BC50 00128830  3B E4 00 00 */	addi r31, r4, 0x0
/* 8012BC54 00128834  38 80 00 01 */	li r4, 0x1
/* 8012BC58 00128838  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8012BC5C 0012883C  3B C3 00 00 */	addi r30, r3, 0x0
/* 8012BC60 00128840  4B F4 53 55 */	bl ftAnim_80070FB4
/* 8012BC64 00128844  2C 1F 00 00 */	cmpwi r31, 0x0
/* 8012BC68 00128848  41 82 00 10 */	beq .L_8012BC78
/* 8012BC6C 0012884C  38 7E 00 00 */	addi r3, r30, 0x0
/* 8012BC70 00128850  38 80 00 01 */	li r4, 0x1
/* 8012BC74 00128854  4B F4 50 51 */	bl ftAnim_80070CC4
.L_8012BC78:
/* 8012BC78 00128858  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8012BC7C 0012885C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8012BC80 00128860  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8012BC84 00128864  38 21 00 18 */	addi r1, r1, 0x18
/* 8012BC88 00128868  7C 08 03 A6 */	mtlr r0
/* 8012BC8C 0012886C  4E 80 00 20 */	blr
.endfn ftYs_Init_OnItemDrop

.fn ftYs_Init_LoadSpecialAttrs, global
/* 8012BC90 00128870  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8012BC94 00128874  38 00 00 27 */	li r0, 0x27
/* 8012BC98 00128878  7C 09 03 A6 */	mtctr r0
/* 8012BC9C 0012887C  80 83 01 0C */	lwz r4, 0x10c(r3)
/* 8012BCA0 00128880  80 63 02 D4 */	lwz r3, 0x2d4(r3)
/* 8012BCA4 00128884  80 84 00 04 */	lwz r4, 0x4(r4)
/* 8012BCA8 00128888  38 A3 FF F8 */	subi r5, r3, 0x8
/* 8012BCAC 0012888C  38 84 FF F8 */	subi r4, r4, 0x8
.L_8012BCB0:
/* 8012BCB0 00128890  84 64 00 08 */	lwzu r3, 0x8(r4)
/* 8012BCB4 00128894  80 04 00 04 */	lwz r0, 0x4(r4)
/* 8012BCB8 00128898  94 65 00 08 */	stwu r3, 0x8(r5)
/* 8012BCBC 0012889C  90 05 00 04 */	stw r0, 0x4(r5)
/* 8012BCC0 001288A0  42 00 FF F0 */	bdnz .L_8012BCB0
/* 8012BCC4 001288A4  4E 80 00 20 */	blr
.endfn ftYs_Init_LoadSpecialAttrs

.fn ftYs_Init_OnKnockbackEnter, global
/* 8012BCC8 001288A8  7C 08 02 A6 */	mflr r0
/* 8012BCCC 001288AC  38 80 00 01 */	li r4, 0x1
/* 8012BCD0 001288B0  90 01 00 04 */	stw r0, 0x4(r1)
/* 8012BCD4 001288B4  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8012BCD8 001288B8  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8012BCDC 001288BC  7C 7F 1B 78 */	mr r31, r3
/* 8012BCE0 001288C0  C0 22 A0 40 */	lfs f1, "@304"@sda21(r0)
/* 8012BCE4 001288C4  4B F4 48 0D */	bl ftAnim_800704F0
/* 8012BCE8 001288C8  C0 22 A0 40 */	lfs f1, "@304"@sda21(r0)
/* 8012BCEC 001288CC  38 7F 00 00 */	addi r3, r31, 0x0
/* 8012BCF0 001288D0  38 80 00 00 */	li r4, 0x0
/* 8012BCF4 001288D4  4B F4 47 FD */	bl ftAnim_800704F0
/* 8012BCF8 001288D8  C0 22 A0 38 */	lfs f1, "@239"@sda21(r0)
/* 8012BCFC 001288DC  38 7F 00 00 */	addi r3, r31, 0x0
/* 8012BD00 001288E0  38 80 00 03 */	li r4, 0x3
/* 8012BD04 001288E4  38 A0 00 03 */	li r5, 0x3
/* 8012BD08 001288E8  4B F4 4E 81 */	bl ftAnim_ApplyPartAnim
/* 8012BD0C 001288EC  C0 22 A0 38 */	lfs f1, "@239"@sda21(r0)
/* 8012BD10 001288F0  38 7F 00 00 */	addi r3, r31, 0x0
/* 8012BD14 001288F4  38 80 00 04 */	li r4, 0x4
/* 8012BD18 001288F8  38 A0 00 03 */	li r5, 0x3
/* 8012BD1C 001288FC  4B F4 4E 6D */	bl ftAnim_ApplyPartAnim
/* 8012BD20 00128900  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8012BD24 00128904  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8012BD28 00128908  38 21 00 18 */	addi r1, r1, 0x18
/* 8012BD2C 0012890C  7C 08 03 A6 */	mtlr r0
/* 8012BD30 00128910  4E 80 00 20 */	blr
.endfn ftYs_Init_OnKnockbackEnter

.fn ftYs_Init_OnKnockbackExit, global
/* 8012BD34 00128914  7C 08 02 A6 */	mflr r0
/* 8012BD38 00128918  38 80 00 01 */	li r4, 0x1
/* 8012BD3C 0012891C  90 01 00 04 */	stw r0, 0x4(r1)
/* 8012BD40 00128920  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8012BD44 00128924  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8012BD48 00128928  7C 7F 1B 78 */	mr r31, r3
/* 8012BD4C 0012892C  C0 22 A0 38 */	lfs f1, "@239"@sda21(r0)
/* 8012BD50 00128930  4B F4 47 A1 */	bl ftAnim_800704F0
/* 8012BD54 00128934  C0 22 A0 38 */	lfs f1, "@239"@sda21(r0)
/* 8012BD58 00128938  38 7F 00 00 */	addi r3, r31, 0x0
/* 8012BD5C 0012893C  38 80 00 00 */	li r4, 0x0
/* 8012BD60 00128940  4B F4 47 91 */	bl ftAnim_800704F0
/* 8012BD64 00128944  C0 22 A0 38 */	lfs f1, "@239"@sda21(r0)
/* 8012BD68 00128948  38 7F 00 00 */	addi r3, r31, 0x0
/* 8012BD6C 0012894C  38 80 00 03 */	li r4, 0x3
/* 8012BD70 00128950  38 A0 00 02 */	li r5, 0x2
/* 8012BD74 00128954  4B F4 4E 15 */	bl ftAnim_ApplyPartAnim
/* 8012BD78 00128958  C0 22 A0 38 */	lfs f1, "@239"@sda21(r0)
/* 8012BD7C 0012895C  38 7F 00 00 */	addi r3, r31, 0x0
/* 8012BD80 00128960  38 80 00 04 */	li r4, 0x4
/* 8012BD84 00128964  38 A0 00 02 */	li r5, 0x2
/* 8012BD88 00128968  4B F4 4E 01 */	bl ftAnim_ApplyPartAnim
/* 8012BD8C 0012896C  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8012BD90 00128970  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8012BD94 00128974  38 21 00 18 */	addi r1, r1, 0x18
/* 8012BD98 00128978  7C 08 03 A6 */	mtlr r0
/* 8012BD9C 0012897C  4E 80 00 20 */	blr
.endfn ftYs_Init_OnKnockbackExit

.fn ftYs_Init_8012BDA0, global
/* 8012BDA0 00128980  7C 08 02 A6 */	mflr r0
/* 8012BDA4 00128984  38 80 00 02 */	li r4, 0x2
/* 8012BDA8 00128988  90 01 00 04 */	stw r0, 0x4(r1)
/* 8012BDAC 0012898C  94 21 FF A8 */	stwu r1, -0x58(r1)
/* 8012BDB0 00128990  93 E1 00 54 */	stw r31, 0x54(r1)
/* 8012BDB4 00128994  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8012BDB8 00128998  4B F4 F3 09 */	bl ftColl_8007B0C0
/* 8012BDBC 0012899C  80 9F 01 0C */	lwz r4, 0x10c(r31)
/* 8012BDC0 001289A0  3C 60 80 3B */	lis r3, ftYs_Unk1_803B75C0@ha
/* 8012BDC4 001289A4  38 00 00 01 */	li r0, 0x1
/* 8012BDC8 001289A8  C0 02 A0 48 */	lfs f0, ftYs_Init_804D9A28@sda21(r0)
/* 8012BDCC 001289AC  80 84 00 08 */	lwz r4, 0x8(r4)
/* 8012BDD0 001289B0  38 E3 75 C0 */	addi r7, r3, ftYs_Unk1_803B75C0@l
/* 8012BDD4 001289B4  88 A4 00 11 */	lbz r5, 0x11(r4)
/* 8012BDD8 001289B8  38 7F 00 00 */	addi r3, r31, 0x0
/* 8012BDDC 001289BC  38 9F 11 A0 */	addi r4, r31, 0x11a0
/* 8012BDE0 001289C0  90 A1 00 20 */	stw r5, 0x20(r1)
/* 8012BDE4 001289C4  38 A1 00 20 */	addi r5, r1, 0x20
/* 8012BDE8 001289C8  90 01 00 24 */	stw r0, 0x24(r1)
/* 8012BDEC 001289CC  90 01 00 28 */	stw r0, 0x28(r1)
/* 8012BDF0 001289D0  80 C7 00 00 */	lwz r6, 0x0(r7)
/* 8012BDF4 001289D4  80 07 00 04 */	lwz r0, 0x4(r7)
/* 8012BDF8 001289D8  90 C1 00 38 */	stw r6, 0x38(r1)
/* 8012BDFC 001289DC  90 01 00 3C */	stw r0, 0x3c(r1)
/* 8012BE00 001289E0  80 07 00 08 */	lwz r0, 0x8(r7)
/* 8012BE04 001289E4  90 01 00 40 */	stw r0, 0x40(r1)
/* 8012BE08 001289E8  80 C1 00 38 */	lwz r6, 0x38(r1)
/* 8012BE0C 001289EC  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 8012BE10 001289F0  90 C1 00 2C */	stw r6, 0x2c(r1)
/* 8012BE14 001289F4  90 01 00 30 */	stw r0, 0x30(r1)
/* 8012BE18 001289F8  80 01 00 40 */	lwz r0, 0x40(r1)
/* 8012BE1C 001289FC  90 01 00 34 */	stw r0, 0x34(r1)
/* 8012BE20 00128A00  D0 01 00 44 */	stfs f0, 0x44(r1)
/* 8012BE24 00128A04  4B F4 F7 89 */	bl ftColl_8007B5AC
/* 8012BE28 00128A08  80 01 00 5C */	lwz r0, 0x5c(r1)
/* 8012BE2C 00128A0C  83 E1 00 54 */	lwz r31, 0x54(r1)
/* 8012BE30 00128A10  38 21 00 58 */	addi r1, r1, 0x58
/* 8012BE34 00128A14  7C 08 03 A6 */	mtlr r0
/* 8012BE38 00128A18  4E 80 00 20 */	blr
.endfn ftYs_Init_8012BDA0

.fn ftYs_Init_8012BE3C, global
/* 8012BE3C 00128A1C  7C 08 02 A6 */	mflr r0
/* 8012BE40 00128A20  38 80 00 00 */	li r4, 0x0
/* 8012BE44 00128A24  90 01 00 04 */	stw r0, 0x4(r1)
/* 8012BE48 00128A28  38 A0 00 00 */	li r5, 0x0
/* 8012BE4C 00128A2C  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 8012BE50 00128A30  93 E1 00 24 */	stw r31, 0x24(r1)
/* 8012BE54 00128A34  93 C1 00 20 */	stw r30, 0x20(r1)
/* 8012BE58 00128A38  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 8012BE5C 00128A3C  7C 7D 1B 78 */	mr r29, r3
/* 8012BE60 00128A40  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 8012BE64 00128A44  4B F4 8C A9 */	bl ftParts_80074B0C
/* 8012BE68 00128A48  38 7D 00 00 */	addi r3, r29, 0x0
/* 8012BE6C 00128A4C  38 80 00 00 */	li r4, 0x0
/* 8012BE70 00128A50  4B F4 F2 51 */	bl ftColl_8007B0C0
/* 8012BE74 00128A54  38 7E 00 00 */	addi r3, r30, 0x0
/* 8012BE78 00128A58  3B FE 01 CC */	addi r31, r30, 0x1cc
/* 8012BE7C 00128A5C  38 80 00 04 */	li r4, 0x4
/* 8012BE80 00128A60  4B F4 91 8D */	bl ftParts_8007500C
/* 8012BE84 00128A64  80 9E 05 E8 */	lwz r4, 0x5e8(r30)
/* 8012BE88 00128A68  54 60 20 36 */	slwi r0, r3, 4
/* 8012BE8C 00128A6C  80 BD 00 2C */	lwz r5, 0x2c(r29)
/* 8012BE90 00128A70  7F A3 EB 78 */	mr r3, r29
/* 8012BE94 00128A74  7C E4 00 2E */	lwzx r7, r4, r0
/* 8012BE98 00128A78  38 85 06 0C */	addi r4, r5, 0x60c
/* 8012BE9C 00128A7C  4C C6 31 82 */	crclr cr1eq
/* 8012BEA0 00128A80  39 1F 00 00 */	addi r8, r31, 0x0
/* 8012BEA4 00128A84  38 A0 00 04 */	li r5, 0x4
/* 8012BEA8 00128A88  38 C0 04 CF */	li r6, 0x4cf
/* 8012BEAC 00128A8C  4B F3 B8 45 */	bl efAsync_Spawn
/* 8012BEB0 00128A90  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 8012BEB4 00128A94  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 8012BEB8 00128A98  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 8012BEBC 00128A9C  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 8012BEC0 00128AA0  38 21 00 28 */	addi r1, r1, 0x28
/* 8012BEC4 00128AA4  7C 08 03 A6 */	mtlr r0
/* 8012BEC8 00128AA8  4E 80 00 20 */	blr
.endfn ftYs_Init_8012BE3C

.fn ftYs_Init_8012BECC, global
/* 8012BECC 00128AAC  7C 08 02 A6 */	mflr r0
/* 8012BED0 00128AB0  38 80 01 55 */	li r4, 0x155
/* 8012BED4 00128AB4  90 01 00 04 */	stw r0, 0x4(r1)
/* 8012BED8 00128AB8  38 A0 00 00 */	li r5, 0x0
/* 8012BEDC 00128ABC  38 C0 00 00 */	li r6, 0x0
/* 8012BEE0 00128AC0  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 8012BEE4 00128AC4  93 E1 00 34 */	stw r31, 0x34(r1)
/* 8012BEE8 00128AC8  7C 7F 1B 78 */	mr r31, r3
/* 8012BEEC 00128ACC  93 C1 00 30 */	stw r30, 0x30(r1)
/* 8012BEF0 00128AD0  93 A1 00 2C */	stw r29, 0x2c(r1)
/* 8012BEF4 00128AD4  C0 22 A0 4C */	lfs f1, ftYs_Init_804D9A2C@sda21(r0)
/* 8012BEF8 00128AD8  C0 42 A0 48 */	lfs f2, ftYs_Init_804D9A28@sda21(r0)
/* 8012BEFC 00128ADC  FC 60 08 90 */	fmr f3, f1
/* 8012BF00 00128AE0  4B F3 D4 AD */	bl Fighter_ChangeMotionState
/* 8012BF04 00128AE4  7F E3 FB 78 */	mr r3, r31
/* 8012BF08 00128AE8  4B F4 2C 9D */	bl ftAnim_8006EBA4
/* 8012BF0C 00128AEC  7F E3 FB 78 */	mr r3, r31
/* 8012BF10 00128AF0  4B F6 65 41 */	bl ftCo_80092450
/* 8012BF14 00128AF4  83 DF 00 2C */	lwz r30, 0x2c(r31)
/* 8012BF18 00128AF8  38 7F 00 00 */	addi r3, r31, 0x0
/* 8012BF1C 00128AFC  38 80 00 01 */	li r4, 0x1
/* 8012BF20 00128B00  4B F4 F1 A1 */	bl ftColl_8007B0C0
/* 8012BF24 00128B04  38 00 00 00 */	li r0, 0x0
/* 8012BF28 00128B08  90 1E 23 4C */	stw r0, 0x234c(r30)
/* 8012BF2C 00128B0C  C0 22 A0 4C */	lfs f1, ftYs_Init_804D9A2C@sda21(r0)
/* 8012BF30 00128B10  D0 3E 23 40 */	stfs f1, 0x2340(r30)
/* 8012BF34 00128B14  80 6D AE B4 */	lwz r3, p_ftCommonData@sda21(r0)
/* 8012BF38 00128B18  C0 03 02 68 */	lfs f0, 0x268(r3)
/* 8012BF3C 00128B1C  D0 1E 23 50 */	stfs f0, 0x2350(r30)
/* 8012BF40 00128B20  90 1E 23 64 */	stw r0, 0x2364(r30)
/* 8012BF44 00128B24  90 1E 23 60 */	stw r0, 0x2360(r30)
/* 8012BF48 00128B28  D0 21 00 1C */	stfs f1, 0x1c(r1)
/* 8012BF4C 00128B2C  D0 21 00 18 */	stfs f1, 0x18(r1)
/* 8012BF50 00128B30  D0 21 00 14 */	stfs f1, 0x14(r1)
/* 8012BF54 00128B34  80 7E 01 0C */	lwz r3, 0x10c(r30)
/* 8012BF58 00128B38  80 9E 05 E8 */	lwz r4, 0x5e8(r30)
/* 8012BF5C 00128B3C  80 63 00 08 */	lwz r3, 0x8(r3)
/* 8012BF60 00128B40  88 03 00 11 */	lbz r0, 0x11(r3)
/* 8012BF64 00128B44  54 00 20 36 */	slwi r0, r0, 4
/* 8012BF68 00128B48  7F A4 00 2E */	lwzx r29, r4, r0
/* 8012BF6C 00128B4C  28 1D 00 00 */	cmplwi r29, 0x0
/* 8012BF70 00128B50  40 82 00 14 */	bne .L_8012BF84
/* 8012BF74 00128B54  38 6D 87 B8 */	li r3, ftYs_Unk2_804D3E58@sda21
/* 8012BF78 00128B58  38 80 03 94 */	li r4, 0x394
/* 8012BF7C 00128B5C  38 AD 87 C0 */	li r5, ftYs_Unk2_804D3E60@sda21
/* 8012BF80 00128B60  48 25 C2 A1 */	bl __assert
.L_8012BF84:
/* 8012BF84 00128B64  80 61 00 14 */	lwz r3, 0x14(r1)
/* 8012BF88 00128B68  80 01 00 18 */	lwz r0, 0x18(r1)
/* 8012BF8C 00128B6C  90 7D 00 38 */	stw r3, 0x38(r29)
/* 8012BF90 00128B70  90 1D 00 3C */	stw r0, 0x3c(r29)
/* 8012BF94 00128B74  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8012BF98 00128B78  90 1D 00 40 */	stw r0, 0x40(r29)
/* 8012BF9C 00128B7C  80 1D 00 14 */	lwz r0, 0x14(r29)
/* 8012BFA0 00128B80  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 8012BFA4 00128B84  40 82 00 4C */	bne .L_8012BFF0
/* 8012BFA8 00128B88  28 1D 00 00 */	cmplwi r29, 0x0
/* 8012BFAC 00128B8C  41 82 00 44 */	beq .L_8012BFF0
/* 8012BFB0 00128B90  40 82 00 14 */	bne .L_8012BFC4
/* 8012BFB4 00128B94  38 6D 87 B8 */	li r3, ftYs_Unk2_804D3E58@sda21
/* 8012BFB8 00128B98  38 80 02 34 */	li r4, 0x234
/* 8012BFBC 00128B9C  38 AD 87 C0 */	li r5, ftYs_Unk2_804D3E60@sda21
/* 8012BFC0 00128BA0  48 25 C2 61 */	bl __assert
.L_8012BFC4:
/* 8012BFC4 00128BA4  80 9D 00 14 */	lwz r4, 0x14(r29)
/* 8012BFC8 00128BA8  38 60 00 00 */	li r3, 0x0
/* 8012BFCC 00128BAC  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 8012BFD0 00128BB0  40 82 00 10 */	bne .L_8012BFE0
/* 8012BFD4 00128BB4  54 80 06 73 */	rlwinm. r0, r4, 0, 25, 25
/* 8012BFD8 00128BB8  41 82 00 08 */	beq .L_8012BFE0
/* 8012BFDC 00128BBC  38 60 00 01 */	li r3, 0x1
.L_8012BFE0:
/* 8012BFE0 00128BC0  2C 03 00 00 */	cmpwi r3, 0x0
/* 8012BFE4 00128BC4  40 82 00 0C */	bne .L_8012BFF0
/* 8012BFE8 00128BC8  7F A3 EB 78 */	mr r3, r29
/* 8012BFEC 00128BCC  48 24 72 FD */	bl HSD_JObjSetMtxDirtySub
.L_8012BFF0:
/* 8012BFF0 00128BD0  7F E3 FB 78 */	mr r3, r31
/* 8012BFF4 00128BD4  4B FF F8 B1 */	bl ftYs_Init_8012B8A4
/* 8012BFF8 00128BD8  7F C3 F3 78 */	mr r3, r30
/* 8012BFFC 00128BDC  4B F6 5D 5D */	bl ftCo_80091D58
/* 8012C000 00128BE0  38 7E 00 00 */	addi r3, r30, 0x0
/* 8012C004 00128BE4  38 80 00 6E */	li r4, 0x6e
/* 8012C008 00128BE8  38 A0 00 7F */	li r5, 0x7f
/* 8012C00C 00128BEC  38 C0 00 40 */	li r6, 0x40
/* 8012C010 00128BF0  4B F5 C1 39 */	bl ft_80088148
/* 8012C014 00128BF4  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 8012C018 00128BF8  83 E1 00 34 */	lwz r31, 0x34(r1)
/* 8012C01C 00128BFC  83 C1 00 30 */	lwz r30, 0x30(r1)
/* 8012C020 00128C00  83 A1 00 2C */	lwz r29, 0x2c(r1)
/* 8012C024 00128C04  38 21 00 38 */	addi r1, r1, 0x38
/* 8012C028 00128C08  7C 08 03 A6 */	mtlr r0
/* 8012C02C 00128C0C  4E 80 00 20 */	blr
.endfn ftYs_Init_8012BECC

# 0x803CE6D0 - 0x803CEA98
.data
.balign 8

.obj ftYs_Init_MotionStateTable, global
	.4byte 0x00000025
	.4byte 0x00100000
	.4byte 0x01000000
	.4byte ftYs_GuardOn_0_Anim
	.4byte ftYs_GuardOn_0_IASA
	.4byte ftYs_GuardOn_0_Phys
	.4byte ftYs_GuardOn_0_Coll
	.4byte ftCamera_UpdateCameraBox
	.4byte 0xFFFFFFFF
	.4byte 0x00180000
	.4byte 0x01000000
	.4byte ftYs_GuardHold_Anim
	.4byte ftYs_GuardHold_IASA
	.4byte ftYs_GuardHold_Phys
	.4byte ftYs_GuardHold_Coll
	.4byte ftCamera_UpdateCameraBox
	.4byte 0x00000027
	.4byte 0x00100000
	.4byte 0x01000000
	.4byte ftYs_GuardOff_Anim
	.4byte ftYs_GuardOff_IASA
	.4byte ftYs_GuardOff_Phys
	.4byte ftYs_GuardOff_Coll
	.4byte ftCamera_UpdateCameraBox
	.4byte 0x00000028
	.4byte 0x00100000
	.4byte 0x01000000
	.4byte ftYs_GuardDamage_Anim
	.4byte ftYs_GuardDamage_IASA
	.4byte ftYs_GuardDamage_Phys
	.4byte ftYs_GuardDamage_Coll
	.4byte ftCamera_UpdateCameraBox
	.4byte 0x00000025
	.4byte 0x00101073
	.4byte 0x01000000
	.4byte ftYs_GuardOn_1_Anim
	.4byte ftYs_GuardOn_1_IASA
	.4byte ftYs_GuardOn_1_Phys
	.4byte ftYs_GuardOn_1_Coll
	.4byte ftCamera_UpdateCameraBox
	.4byte 0x00000127
	.4byte 0x00340011
	.4byte 0x12000000
	.4byte ftYs_SpecialN1_Anim
	.4byte 0x00000000
	.4byte ftYs_SpecialN1_Phys
	.4byte ftYs_SpecialN1_Coll
	.4byte ftCamera_UpdateCameraBox
	.4byte 0x00000128
	.4byte 0x00340011
	.4byte 0x12000000
	.4byte ftYs_SpecialN1_0_Anim
	.4byte 0x00000000
	.4byte ftYs_SpecialN1_0_Phys
	.4byte ftYs_SpecialN1_0_Coll
	.4byte ftCamera_UpdateCameraBox
	.4byte 0x00000128
	.4byte 0x00340011
	.4byte 0x12000000
	.4byte ftYs_SpecialN1_1_Anim
	.4byte 0x00000000
	.4byte ftYs_SpecialN1_1_Phys
	.4byte ftYs_SpecialN1_1_Coll
	.4byte ftCamera_UpdateCameraBox
	.4byte 0x00000129
	.4byte 0x00340011
	.4byte 0x12000000
	.4byte ftYs_SpecialN2_0_Anim
	.4byte 0x00000000
	.4byte ftYs_SpecialN2_0_Phys
	.4byte ftYs_SpecialN2_0_Coll
	.4byte ftCamera_UpdateCameraBox
	.4byte 0x00000129
	.4byte 0x00340011
	.4byte 0x12000000
	.4byte ftYs_SpecialN2_1_Anim
	.4byte 0x00000000
	.4byte ftYs_SpecialN2_1_Phys
	.4byte ftYs_SpecialN2_1_Coll
	.4byte ftCamera_UpdateCameraBox
	.4byte 0x0000012A
	.4byte 0x00340411
	.4byte 0x12000000
	.4byte ftYs_SpecialAirN1_0_Anim
	.4byte 0x00000000
	.4byte ftYs_SpecialAirN1_0_Phys
	.4byte ftYs_SpecialAirN1_0_Coll
	.4byte ftCamera_UpdateCameraBox
	.4byte 0x0000012B
	.4byte 0x00340411
	.4byte 0x12000000
	.4byte ftYs_SpecialAirN1_1_Anim
	.4byte 0x00000000
	.4byte ftYs_SpecialAirN1_1_Phys
	.4byte ftYs_SpecialAirN1_1_Coll
	.4byte ftCamera_UpdateCameraBox
	.4byte 0x0000012B
	.4byte 0x00340411
	.4byte 0x12000000
	.4byte ftYs_SpecialAirN1_2_Anim
	.4byte 0x00000000
	.4byte ftYs_SpecialAirN1_2_Phys
	.4byte ftYs_SpecialAirN1_2_Coll
	.4byte ftCamera_UpdateCameraBox
	.4byte 0x0000012C
	.4byte 0x00340411
	.4byte 0x12000000
	.4byte ftYs_SpecialAirN2_0_Anim
	.4byte 0x00000000
	.4byte ftYs_SpecialAirN2_0_Phys
	.4byte ftYs_SpecialAirN2_0_Coll
	.4byte ftCamera_UpdateCameraBox
	.4byte 0x0000012C
	.4byte 0x00340411
	.4byte 0x12000000
	.4byte ftYs_SpecialAirN2_1_Anim
	.4byte 0x00000000
	.4byte ftYs_SpecialAirN2_1_Phys
	.4byte ftYs_SpecialAirN2_1_Coll
	.4byte ftCamera_UpdateCameraBox
	.4byte 0x0000012D
	.4byte 0x00340212
	.4byte 0x13000000
	.4byte ftYs_SpecialAirSStart_0_Anim
	.4byte ftYs_SpecialAirSStart_0_IASA
	.4byte ftYs_SpecialAirSStart_0_Phys
	.4byte ftYs_SpecialAirSStart_0_Coll
	.4byte ftCamera_UpdateCameraBox
	.4byte 0x0000012E
	.4byte 0x00340212
	.4byte 0x13000000
	.4byte ftYs_SpecialAirSLoop_0_Anim
	.4byte ftYs_SpecialAirSLoop_0_IASA
	.4byte ftYs_SpecialAirSLoop_0_Phys
	.4byte ftYs_SpecialAirSLoop_0_Coll
	.4byte ftCamera_UpdateCameraBox
	.4byte 0x0000012F
	.4byte 0x00340212
	.4byte 0x13000000
	.4byte ftYs_SpecialAirSLoop_1_Anim
	.4byte ftYs_SpecialAirSLoop_1_IASA
	.4byte ftYs_SpecialAirSLoop_1_Phys
	.4byte ftYs_SpecialAirSLoop_1_Coll
	.4byte ftCamera_UpdateCameraBox
	.4byte 0x00000130
	.4byte 0x00340212
	.4byte 0x13000000
	.4byte ftYs_SpecialAirSEnd_Anim
	.4byte ftYs_SpecialAirSEnd_IASA
	.4byte ftYs_SpecialAirSEnd_Phys
	.4byte ftYs_SpecialAirSEnd_Coll
	.4byte ftCamera_UpdateCameraBox
	.4byte 0x00000131
	.4byte 0x00340612
	.4byte 0x13000000
	.4byte ftYs_SpecialAirSStart_1_Anim
	.4byte ftYs_SpecialAirSStart_1_IASA
	.4byte ftYs_SpecialAirSStart_1_Phys
	.4byte ftYs_SpecialAirSStart_1_Coll
	.4byte ftCamera_UpdateCameraBox
	.4byte 0x00000132
	.4byte 0x00340612
	.4byte 0x13000000
	.4byte ftYs_SpecialAirSLoop_2_Anim
	.4byte ftYs_SpecialAirSLoop_2_IASA
	.4byte ftYs_SpecialAirSLoop_2_Phys
	.4byte ftYs_SpecialAirSLoop_2_Coll
	.4byte ftCamera_UpdateCameraBox
	.4byte 0x00000133
	.4byte 0x00340612
	.4byte 0x13000000
	.4byte ftYs_SpecialAirSLoop_3_Anim
	.4byte ftYs_SpecialAirSLoop_3_IASA
	.4byte ftYs_SpecialAirSLoop_3_Phys
	.4byte ftYs_SpecialAirSLoop_3_Coll
	.4byte ftCamera_UpdateCameraBox
	.4byte 0x00000134
	.4byte 0x00340612
	.4byte 0x13000000
	.4byte ftYs_SpecialAirSLanding_Anim
	.4byte ftYs_SpecialAirSLanding_IASA
	.4byte ftYs_SpecialAirSLanding_Phys
	.4byte ftYs_SpecialAirSLanding_Coll
	.4byte ftCamera_UpdateCameraBox
	.4byte 0x00000135
	.4byte 0x00340113
	.4byte 0x14000000
	.4byte ftYs_SpecialHi_Anim
	.4byte 0x00000000
	.4byte ftYs_SpecialHi_Phys
	.4byte ftYs_SpecialHi_Coll
	.4byte ftCamera_UpdateCameraBox
	.4byte 0x00000136
	.4byte 0x00340513
	.4byte 0x14000000
	.4byte ftYs_SpecialAirHi_Anim
	.4byte 0x00000000
	.4byte ftYs_SpecialAirHi_Phys
	.4byte ftYs_SpecialAirHi_Coll
	.4byte ftCamera_UpdateCameraBox
	.4byte 0x00000137
	.4byte 0x00340214
	.4byte 0x15000000
	.4byte ftYs_SpecialLw_Anim
	.4byte 0x00000000
	.4byte ftYs_SpecialLw_Phys
	.4byte ftYs_SpecialLw_Coll
	.4byte ftCamera_UpdateCameraBox
	.4byte 0x00000138
	.4byte 0x00340214
	.4byte 0x15000000
	.4byte ftYs_SpecialLwLanding_Anim
	.4byte 0x00000000
	.4byte ftYs_SpecialLwLanding_Phys
	.4byte ftYs_SpecialLwLanding_Coll
	.4byte ftCamera_UpdateCameraBox
	.4byte 0x00000139
	.4byte 0x00340614
	.4byte 0x15000000
	.4byte ftYs_SpecialAirLw_Anim
	.4byte 0x00000000
	.4byte ftYs_SpecialAirLw_Phys
	.4byte ftYs_SpecialAirLw_Coll
	.4byte ftCamera_UpdateCameraBox
.endobj ftYs_Init_MotionStateTable

.obj "@242", local
	.string "yoshi matanim frame not same\n"
.endobj "@242"

.obj gap_07_803CEA6E_data, global
.hidden gap_07_803CEA6E_data
	.2byte 0x0000
.endobj gap_07_803CEA6E_data

.obj "@243", local
	.string "ftyoshi.c"
.endobj "@243"

.obj gap_07_803CEA7A_data, global
.hidden gap_07_803CEA7A_data
	.2byte 0x0000
.endobj gap_07_803CEA7A_data

.obj "@273", local
	.string "yoshi parts_model NULL!!\n"
.endobj "@273"

.obj gap_07_803CEA96_data, global
.hidden gap_07_803CEA96_data
	.2byte 0x0000
.endobj gap_07_803CEA96_data

# 0x804D3E40 - 0x804D3E58
.section .sdata, "wa"
.balign 8

.obj "@240", local
	.string "aobj.h"
.endobj "@240"

.obj gap_09_804D3E47_sdata, global
.hidden gap_09_804D3E47_sdata
	.byte 0x00
.endobj gap_09_804D3E47_sdata

.obj "@241", local
	.string "aobj"
.endobj "@241"

.obj gap_09_804D3E4D_sdata, global
.hidden gap_09_804D3E4D_sdata
	.byte 0x00, 0x00, 0x00
.endobj gap_09_804D3E4D_sdata

.obj "@244", local
	.string "0"
.endobj "@244"

.obj gap_09_804D3E52_sdata, global
.hidden gap_09_804D3E52_sdata
	.4byte 0x00000000
	.2byte 0x0000
.endobj gap_09_804D3E52_sdata

# 0x804D9A18 - 0x804D9A28
.section .sdata2, "a"
.balign 8

.obj "@239", local
	.float 0
.endobj "@239"

.obj "@259", local
	.float 1
.endobj "@259"

.obj "@304", local
	.float 3
.endobj "@304"

.obj gap_11_804D9A24_sdata2, global
.hidden gap_11_804D9A24_sdata2
	.4byte 0x00000000
.endobj gap_11_804D9A24_sdata2
