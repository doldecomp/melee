.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240

.global CreateCallbackFat
CreateCallbackFat:
/* 80357708 003542E8  7C 08 02 A6 */	mflr r0
/* 8035770C 003542EC  90 01 00 04 */	stw r0, 4(r1)
/* 80357710 003542F0  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 80357714 003542F4  BF 61 00 14 */	stmw r27, 0x14(r1)
/* 80357718 003542F8  3B 83 00 00 */	addi r28, r3, 0
/* 8035771C 003542FC  3C 60 80 4B */	lis r3, __CARDBlock@ha
/* 80357720 00354300  1C BC 01 10 */	mulli r5, r28, 0x110
/* 80357724 00354304  38 03 8B 38 */	addi r0, r3, __CARDBlock@l
/* 80357728 00354308  7F E0 2A 14 */	add r31, r0, r5
/* 8035772C 0035430C  83 BF 00 D0 */	lwz r29, 0xd0(r31)
/* 80357730 00354310  3B 60 00 00 */	li r27, 0
/* 80357734 00354314  7C 9E 23 79 */	or. r30, r4, r4
/* 80357738 00354318  93 7F 00 D0 */	stw r27, 0xd0(r31)
/* 8035773C 0035431C  41 80 00 C0 */	blt lbl_803577FC
/* 80357740 00354320  7F E3 FB 78 */	mr r3, r31
/* 80357744 00354324  4B FF D6 79 */	bl __CARDGetDirBlock
/* 80357748 00354328  A0 1F 00 BC */	lhz r0, 0xbc(r31)
/* 8035774C 0035432C  38 A0 00 04 */	li r5, 4
/* 80357750 00354330  80 9F 01 0C */	lwz r4, 0x10c(r31)
/* 80357754 00354334  54 00 30 32 */	slwi r0, r0, 6
/* 80357758 00354338  7F C3 02 14 */	add r30, r3, r0
/* 8035775C 0035433C  38 7E 00 00 */	addi r3, r30, 0
/* 80357760 00354340  4B CA BA 95 */	bl memcpy
/* 80357764 00354344  80 9F 01 0C */	lwz r4, 0x10c(r31)
/* 80357768 00354348  38 7E 00 04 */	addi r3, r30, 4
/* 8035776C 0035434C  38 A0 00 02 */	li r5, 2
/* 80357770 00354350  38 84 00 04 */	addi r4, r4, 4
/* 80357774 00354354  4B CA BA 81 */	bl memcpy
/* 80357778 00354358  38 00 00 04 */	li r0, 4
/* 8035777C 0035435C  98 1E 00 34 */	stb r0, 0x34(r30)
/* 80357780 00354360  38 00 FF FF */	li r0, -1
/* 80357784 00354364  3C 60 80 00 */	lis r3, 0x800000F8@ha
/* 80357788 00354368  9B 7E 00 35 */	stb r27, 0x35(r30)
/* 8035778C 0035436C  A0 9F 00 BE */	lhz r4, 0xbe(r31)
/* 80357790 00354370  B0 9E 00 36 */	sth r4, 0x36(r30)
/* 80357794 00354374  9B 7E 00 07 */	stb r27, 7(r30)
/* 80357798 00354378  90 1E 00 2C */	stw r0, 0x2c(r30)
/* 8035779C 0035437C  B3 7E 00 30 */	sth r27, 0x30(r30)
/* 803577A0 00354380  B3 7E 00 32 */	sth r27, 0x32(r30)
/* 803577A4 00354384  90 1E 00 3C */	stw r0, 0x3c(r30)
/* 803577A8 00354388  A0 1E 00 32 */	lhz r0, 0x32(r30)
/* 803577AC 0035438C  54 00 00 3A */	rlwinm r0, r0, 0, 0, 0x1d
/* 803577B0 00354390  60 00 00 01 */	ori r0, r0, 1
/* 803577B4 00354394  B0 1E 00 32 */	sth r0, 0x32(r30)
/* 803577B8 00354398  80 9F 00 C0 */	lwz r4, 0xc0(r31)
/* 803577BC 0035439C  93 64 00 08 */	stw r27, 8(r4)
/* 803577C0 003543A0  A0 1E 00 36 */	lhz r0, 0x36(r30)
/* 803577C4 003543A4  80 9F 00 C0 */	lwz r4, 0xc0(r31)
/* 803577C8 003543A8  B0 04 00 10 */	sth r0, 0x10(r4)
/* 803577CC 003543AC  80 03 00 F8 */	lwz r0, 0x800000F8@l(r3)
/* 803577D0 003543B0  54 1B F0 BE */	srwi r27, r0, 2
/* 803577D4 003543B4  4B FF 4C 1D */	bl OSGetTime
/* 803577D8 003543B8  38 DB 00 00 */	addi r6, r27, 0
/* 803577DC 003543BC  38 A0 00 00 */	li r5, 0
/* 803577E0 003543C0  4B FC B2 29 */	bl __div2i
/* 803577E4 003543C4  90 9E 00 28 */	stw r4, 0x28(r30)
/* 803577E8 003543C8  38 7C 00 00 */	addi r3, r28, 0
/* 803577EC 003543CC  38 9D 00 00 */	addi r4, r29, 0
/* 803577F0 003543D0  4B FF D7 6D */	bl __CARDUpdateDir
/* 803577F4 003543D4  7C 7E 1B 79 */	or. r30, r3, r3
/* 803577F8 003543D8  40 80 00 2C */	bge lbl_80357824
lbl_803577FC:
/* 803577FC 003543DC  38 7F 00 00 */	addi r3, r31, 0
/* 80357800 003543E0  38 9E 00 00 */	addi r4, r30, 0
/* 80357804 003543E4  4B FF BA 6D */	bl __CARDPutControlBlock
/* 80357808 003543E8  28 1D 00 00 */	cmplwi r29, 0
/* 8035780C 003543EC  41 82 00 18 */	beq lbl_80357824
/* 80357810 003543F0  39 9D 00 00 */	addi r12, r29, 0
/* 80357814 003543F4  7D 88 03 A6 */	mtlr r12
/* 80357818 003543F8  38 7C 00 00 */	addi r3, r28, 0
/* 8035781C 003543FC  38 9E 00 00 */	addi r4, r30, 0
/* 80357820 00354400  4E 80 00 21 */	blrl 
lbl_80357824:
/* 80357824 00354404  BB 61 00 14 */	lmw r27, 0x14(r1)
/* 80357828 00354408  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 8035782C 0035440C  38 21 00 28 */	addi r1, r1, 0x28
/* 80357830 00354410  7C 08 03 A6 */	mtlr r0
/* 80357834 00354414  4E 80 00 20 */	blr 

.global CARDCreateAsync
CARDCreateAsync:
/* 80357838 00354418  7C 08 02 A6 */	mflr r0
/* 8035783C 0035441C  90 01 00 04 */	stw r0, 4(r1)
/* 80357840 00354420  94 21 FF B8 */	stwu r1, -0x48(r1)
/* 80357844 00354424  BE E1 00 24 */	stmw r23, 0x24(r1)
/* 80357848 00354428  3B 44 00 00 */	addi r26, r4, 0
/* 8035784C 0035442C  3B 23 00 00 */	addi r25, r3, 0
/* 80357850 00354430  3B 65 00 00 */	addi r27, r5, 0
/* 80357854 00354434  3B 86 00 00 */	addi r28, r6, 0
/* 80357858 00354438  3B A7 00 00 */	addi r29, r7, 0
/* 8035785C 0035443C  38 7A 00 00 */	addi r3, r26, 0
/* 80357860 00354440  4B FC E2 A5 */	bl strlen
/* 80357864 00354444  28 03 00 20 */	cmplwi r3, 0x20
/* 80357868 00354448  40 81 00 0C */	ble lbl_80357874
/* 8035786C 0035444C  38 60 FF F4 */	li r3, -12
/* 80357870 00354450  48 00 01 D4 */	b lbl_80357A44
lbl_80357874:
/* 80357874 00354454  38 79 00 00 */	addi r3, r25, 0
/* 80357878 00354458  38 81 00 1C */	addi r4, r1, 0x1c
/* 8035787C 0035445C  4B FF B9 3D */	bl __CARDGetControlBlock
/* 80357880 00354460  2C 03 00 00 */	cmpwi r3, 0
/* 80357884 00354464  40 80 00 08 */	bge lbl_8035788C
/* 80357888 00354468  48 00 01 BC */	b lbl_80357A44
lbl_8035788C:
/* 8035788C 0035446C  28 1B 00 00 */	cmplwi r27, 0
/* 80357890 00354470  41 82 00 1C */	beq lbl_803578AC
/* 80357894 00354474  80 61 00 1C */	lwz r3, 0x1c(r1)
/* 80357898 00354478  80 83 00 0C */	lwz r4, 0xc(r3)
/* 8035789C 0035447C  7C 1B 23 96 */	divwu r0, r27, r4
/* 803578A0 00354480  7C 00 21 D6 */	mullw r0, r0, r4
/* 803578A4 00354484  7C 00 D8 51 */	subf. r0, r0, r27
/* 803578A8 00354488  41 82 00 0C */	beq lbl_803578B4
lbl_803578AC:
/* 803578AC 0035448C  38 60 FF 80 */	li r3, -128
/* 803578B0 00354490  48 00 01 94 */	b lbl_80357A44
lbl_803578B4:
/* 803578B4 00354494  3C 80 00 01 */	lis r4, 0x0000FFFF@ha
/* 803578B8 00354498  3B C4 FF FF */	addi r30, r4, 0x0000FFFF@l
/* 803578BC 0035449C  4B FF D5 01 */	bl __CARDGetDirBlock
/* 803578C0 003544A0  3B E3 00 00 */	addi r31, r3, 0
/* 803578C4 003544A4  3B 1F 00 00 */	addi r24, r31, 0
/* 803578C8 003544A8  3A E0 00 00 */	li r23, 0
/* 803578CC 003544AC  48 00 00 8C */	b lbl_80357958
lbl_803578D0:
/* 803578D0 003544B0  88 18 00 00 */	lbz r0, 0(r24)
/* 803578D4 003544B4  28 00 00 FF */	cmplwi r0, 0xff
/* 803578D8 003544B8  40 82 00 18 */	bne lbl_803578F0
/* 803578DC 003544BC  57 C0 04 3E */	clrlwi r0, r30, 0x10
/* 803578E0 003544C0  28 00 FF FF */	cmplwi r0, 0xffff
/* 803578E4 003544C4  40 82 00 6C */	bne lbl_80357950
/* 803578E8 003544C8  7E FE BB 78 */	mr r30, r23
/* 803578EC 003544CC  48 00 00 64 */	b lbl_80357950
lbl_803578F0:
/* 803578F0 003544D0  80 81 00 1C */	lwz r4, 0x1c(r1)
/* 803578F4 003544D4  38 78 00 00 */	addi r3, r24, 0
/* 803578F8 003544D8  38 A0 00 04 */	li r5, 4
/* 803578FC 003544DC  80 84 01 0C */	lwz r4, 0x10c(r4)
/* 80357900 003544E0  4B FC BF C9 */	bl memcmp
/* 80357904 003544E4  2C 03 00 00 */	cmpwi r3, 0
/* 80357908 003544E8  40 82 00 48 */	bne lbl_80357950
/* 8035790C 003544EC  80 81 00 1C */	lwz r4, 0x1c(r1)
/* 80357910 003544F0  38 78 00 04 */	addi r3, r24, 4
/* 80357914 003544F4  38 A0 00 02 */	li r5, 2
/* 80357918 003544F8  80 84 01 0C */	lwz r4, 0x10c(r4)
/* 8035791C 003544FC  38 84 00 04 */	addi r4, r4, 4
/* 80357920 00354500  4B FC BF A9 */	bl memcmp
/* 80357924 00354504  2C 03 00 00 */	cmpwi r3, 0
/* 80357928 00354508  40 82 00 28 */	bne lbl_80357950
/* 8035792C 0035450C  38 78 00 00 */	addi r3, r24, 0
/* 80357930 00354510  38 9A 00 00 */	addi r4, r26, 0
/* 80357934 00354514  4B FF F8 21 */	bl __CARDCompareFileName
/* 80357938 00354518  2C 03 00 00 */	cmpwi r3, 0
/* 8035793C 0035451C  41 82 00 14 */	beq lbl_80357950
/* 80357940 00354520  80 61 00 1C */	lwz r3, 0x1c(r1)
/* 80357944 00354524  38 80 FF F9 */	li r4, -7
/* 80357948 00354528  4B FF B9 29 */	bl __CARDPutControlBlock
/* 8035794C 0035452C  48 00 00 F8 */	b lbl_80357A44
lbl_80357950:
/* 80357950 00354530  3B 18 00 40 */	addi r24, r24, 0x40
/* 80357954 00354534  3A F7 00 01 */	addi r23, r23, 1
lbl_80357958:
/* 80357958 00354538  56 E0 04 3E */	clrlwi r0, r23, 0x10
/* 8035795C 0035453C  28 00 00 7F */	cmplwi r0, 0x7f
/* 80357960 00354540  41 80 FF 70 */	blt lbl_803578D0
/* 80357964 00354544  57 C0 04 3E */	clrlwi r0, r30, 0x10
/* 80357968 00354548  28 00 FF FF */	cmplwi r0, 0xffff
/* 8035796C 0035454C  40 82 00 14 */	bne lbl_80357980
/* 80357970 00354550  80 61 00 1C */	lwz r3, 0x1c(r1)
/* 80357974 00354554  38 80 FF F8 */	li r4, -8
/* 80357978 00354558  4B FF B8 F9 */	bl __CARDPutControlBlock
/* 8035797C 0035455C  48 00 00 C8 */	b lbl_80357A44
lbl_80357980:
/* 80357980 00354560  80 61 00 1C */	lwz r3, 0x1c(r1)
/* 80357984 00354564  4B FF D0 35 */	bl __CARDGetFatBlock
/* 80357988 00354568  80 81 00 1C */	lwz r4, 0x1c(r1)
/* 8035798C 0035456C  A0 03 00 06 */	lhz r0, 6(r3)
/* 80357990 00354570  80 64 00 0C */	lwz r3, 0xc(r4)
/* 80357994 00354574  7C 03 01 D6 */	mullw r0, r3, r0
/* 80357998 00354578  7C 00 D8 40 */	cmplw r0, r27
/* 8035799C 0035457C  40 80 00 14 */	bge lbl_803579B0
/* 803579A0 00354580  38 64 00 00 */	addi r3, r4, 0
/* 803579A4 00354584  38 80 FF F7 */	li r4, -9
/* 803579A8 00354588  4B FF B8 C9 */	bl __CARDPutControlBlock
/* 803579AC 0035458C  48 00 00 98 */	b lbl_80357A44
lbl_803579B0:
/* 803579B0 00354590  28 1D 00 00 */	cmplwi r29, 0
/* 803579B4 00354594  41 82 00 0C */	beq lbl_803579C0
/* 803579B8 00354598  7F A0 EB 78 */	mr r0, r29
/* 803579BC 0035459C  48 00 00 0C */	b lbl_803579C8
lbl_803579C0:
/* 803579C0 003545A0  3C 60 80 35 */	lis r3, __CARDDefaultApiCallback@ha
/* 803579C4 003545A4  38 03 22 70 */	addi r0, r3, __CARDDefaultApiCallback@l
lbl_803579C8:
/* 803579C8 003545A8  90 04 00 D0 */	stw r0, 0xd0(r4)
/* 803579CC 003545AC  57 C0 32 B2 */	rlwinm r0, r30, 6, 0xa, 0x19
/* 803579D0 003545B0  7C FF 02 14 */	add r7, r31, r0
/* 803579D4 003545B4  80 61 00 1C */	lwz r3, 0x1c(r1)
/* 803579D8 003545B8  57 DD 04 3E */	clrlwi r29, r30, 0x10
/* 803579DC 003545BC  38 9A 00 00 */	addi r4, r26, 0
/* 803579E0 003545C0  B3 C3 00 BC */	sth r30, 0xbc(r3)
/* 803579E4 003545C4  38 67 00 08 */	addi r3, r7, 8
/* 803579E8 003545C8  38 A0 00 20 */	li r5, 0x20
/* 803579EC 003545CC  80 C1 00 1C */	lwz r6, 0x1c(r1)
/* 803579F0 003545D0  80 06 00 0C */	lwz r0, 0xc(r6)
/* 803579F4 003545D4  7C 1B 03 96 */	divwu r0, r27, r0
/* 803579F8 003545D8  B0 07 00 38 */	sth r0, 0x38(r7)
/* 803579FC 003545DC  4B FC E0 11 */	bl strncpy
/* 80357A00 003545E0  80 81 00 1C */	lwz r4, 0x1c(r1)
/* 80357A04 003545E4  3C 60 80 35 */	lis r3, CreateCallbackFat@ha
/* 80357A08 003545E8  38 A3 77 08 */	addi r5, r3, CreateCallbackFat@l
/* 80357A0C 003545EC  93 84 00 C0 */	stw r28, 0xc0(r4)
/* 80357A10 003545F0  7F 23 CB 78 */	mr r3, r25
/* 80357A14 003545F4  93 3C 00 00 */	stw r25, 0(r28)
/* 80357A18 003545F8  93 BC 00 04 */	stw r29, 4(r28)
/* 80357A1C 003545FC  80 81 00 1C */	lwz r4, 0x1c(r1)
/* 80357A20 00354600  80 04 00 0C */	lwz r0, 0xc(r4)
/* 80357A24 00354604  7C 9B 03 96 */	divwu r4, r27, r0
/* 80357A28 00354608  4B FF D1 35 */	bl __CARDAllocBlock
/* 80357A2C 0035460C  7C 64 1B 79 */	or. r4, r3, r3
/* 80357A30 00354610  40 80 00 10 */	bge lbl_80357A40
/* 80357A34 00354614  80 61 00 1C */	lwz r3, 0x1c(r1)
/* 80357A38 00354618  4B FF B8 39 */	bl __CARDPutControlBlock
/* 80357A3C 0035461C  48 00 00 08 */	b lbl_80357A44
lbl_80357A40:
/* 80357A40 00354620  7C 83 23 78 */	mr r3, r4
lbl_80357A44:
/* 80357A44 00354624  BA E1 00 24 */	lmw r23, 0x24(r1)
/* 80357A48 00354628  80 01 00 4C */	lwz r0, 0x4c(r1)
/* 80357A4C 0035462C  38 21 00 48 */	addi r1, r1, 0x48
/* 80357A50 00354630  7C 08 03 A6 */	mtlr r0
/* 80357A54 00354634  4E 80 00 20 */	blr 
