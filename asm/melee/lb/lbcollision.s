.include "macros.inc"

.section .text, "ax"  # 0x80005BB0 - 0x80008D2C

.global func_8000AB2C
func_8000AB2C:
/* 8000AB2C 0000770C  7C 08 02 A6 */	mflr r0
/* 8000AB30 00007710  38 CD 80 34 */	addi r6, r13, lbl_804D36D4@sda21
/* 8000AB34 00007714  90 01 00 04 */	stw r0, 4(r1)
/* 8000AB38 00007718  94 21 FF 18 */	stwu r1, -0xe8(r1)
/* 8000AB3C 0000771C  DB E1 00 E0 */	stfd f31, 0xe0(r1)
/* 8000AB40 00007720  FF E0 08 90 */	fmr f31, f1
/* 8000AB44 00007724  93 E1 00 DC */	stw r31, 0xdc(r1)
/* 8000AB48 00007728  93 C1 00 D8 */	stw r30, 0xd8(r1)
/* 8000AB4C 0000772C  3B C5 00 00 */	addi r30, r5, 0
/* 8000AB50 00007730  93 A1 00 D4 */	stw r29, 0xd4(r1)
/* 8000AB54 00007734  3B A3 00 00 */	addi r29, r3, 0
/* 8000AB58 00007738  88 06 00 03 */	lbz r0, 3(r6)
/* 8000AB5C 0000773C  28 00 00 FF */	cmplwi r0, 0xff
/* 8000AB60 00007740  40 82 00 0C */	bne lbl_8000AB6C
/* 8000AB64 00007744  38 00 00 00 */	li r0, 0
/* 8000AB68 00007748  48 00 00 08 */	b lbl_8000AB70
lbl_8000AB6C:
/* 8000AB6C 0000774C  38 00 00 02 */	li r0, 2
lbl_8000AB70:
/* 8000AB70 00007750  7C 00 20 40 */	cmplw r0, r4
/* 8000AB74 00007754  40 82 01 64 */	bne lbl_8000ACD8
/* 8000AB78 00007758  88 1D 00 04 */	lbz r0, 4(r29)
/* 8000AB7C 0000775C  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 8000AB80 00007760  40 82 00 30 */	bne lbl_8000ABB0
/* 8000AB84 00007764  80 7D 00 00 */	lwz r3, 0(r29)
/* 8000AB88 00007768  38 9D 00 14 */	addi r4, r29, 0x14
/* 8000AB8C 0000776C  38 BD 00 08 */	addi r5, r29, 8
/* 8000AB90 00007770  48 00 06 3D */	bl func_8000B1CC
/* 8000AB94 00007774  28 1E 00 00 */	cmplwi r30, 0
/* 8000AB98 00007778  41 82 00 08 */	beq lbl_8000ABA0
/* 8000AB9C 0000777C  D3 FD 00 10 */	stfs f31, 0x10(r29)
lbl_8000ABA0:
/* 8000ABA0 00007780  88 1D 00 04 */	lbz r0, 4(r29)
/* 8000ABA4 00007784  38 60 00 01 */	li r3, 1
/* 8000ABA8 00007788  50 60 3E 30 */	rlwimi r0, r3, 7, 0x18, 0x18
/* 8000ABAC 0000778C  98 1D 00 04 */	stb r0, 4(r29)
lbl_8000ABB0:
/* 8000ABB0 00007790  28 1E 00 00 */	cmplwi r30, 0
/* 8000ABB4 00007794  41 82 00 38 */	beq lbl_8000ABEC
/* 8000ABB8 00007798  83 FD 00 00 */	lwz r31, 0(r29)
/* 8000ABBC 0000779C  28 1F 00 00 */	cmplwi r31, 0
/* 8000ABC0 000077A0  40 82 00 14 */	bne lbl_8000ABD4
/* 8000ABC4 000077A4  38 6D 80 60 */	addi r3, r13, lbl_804D3700@sda21
/* 8000ABC8 000077A8  38 80 04 78 */	li r4, 0x478
/* 8000ABCC 000077AC  38 AD 80 68 */	addi r5, r13, lbl_804D3708@sda21
/* 8000ABD0 000077B0  48 37 D6 51 */	bl __assert
lbl_8000ABD4:
/* 8000ABD4 000077B4  7F E3 FB 78 */	mr r3, r31
/* 8000ABD8 000077B8  4B FF D1 91 */	bl HSD_JObjUnkMtxPtr
/* 8000ABDC 000077BC  38 9F 00 44 */	addi r4, r31, 0x44
/* 8000ABE0 000077C0  38 7E 00 00 */	addi r3, r30, 0
/* 8000ABE4 000077C4  38 A1 00 9C */	addi r5, r1, 0x9c
/* 8000ABE8 000077C8  48 33 76 1D */	bl PSMTXConcat
lbl_8000ABEC:
/* 8000ABEC 000077CC  C3 FD 00 20 */	lfs f31, 0x20(r29)
/* 8000ABF0 000077D0  28 1E 00 00 */	cmplwi r30, 0
/* 8000ABF4 000077D4  80 7D 00 08 */	lwz r3, 8(r29)
/* 8000ABF8 000077D8  80 1D 00 0C */	lwz r0, 0xc(r29)
/* 8000ABFC 000077DC  90 61 00 84 */	stw r3, 0x84(r1)
/* 8000AC00 000077E0  90 01 00 88 */	stw r0, 0x88(r1)
/* 8000AC04 000077E4  80 1D 00 10 */	lwz r0, 0x10(r29)
/* 8000AC08 000077E8  90 01 00 8C */	stw r0, 0x8c(r1)
/* 8000AC0C 000077EC  80 7D 00 08 */	lwz r3, 8(r29)
/* 8000AC10 000077F0  80 1D 00 0C */	lwz r0, 0xc(r29)
/* 8000AC14 000077F4  90 61 00 90 */	stw r3, 0x90(r1)
/* 8000AC18 000077F8  90 01 00 94 */	stw r0, 0x94(r1)
/* 8000AC1C 000077FC  80 1D 00 10 */	lwz r0, 0x10(r29)
/* 8000AC20 00007800  90 01 00 98 */	stw r0, 0x98(r1)
/* 8000AC24 00007804  41 82 00 0C */	beq lbl_8000AC30
/* 8000AC28 00007808  3B E1 00 9C */	addi r31, r1, 0x9c
/* 8000AC2C 0000780C  48 00 00 2C */	b lbl_8000AC58
lbl_8000AC30:
/* 8000AC30 00007810  83 FD 00 00 */	lwz r31, 0(r29)
/* 8000AC34 00007814  28 1F 00 00 */	cmplwi r31, 0
/* 8000AC38 00007818  40 82 00 14 */	bne lbl_8000AC4C
/* 8000AC3C 0000781C  38 6D 80 60 */	addi r3, r13, lbl_804D3700@sda21
/* 8000AC40 00007820  38 80 04 78 */	li r4, 0x478
/* 8000AC44 00007824  38 AD 80 68 */	addi r5, r13, lbl_804D3708@sda21
/* 8000AC48 00007828  48 37 D5 D9 */	bl __assert
lbl_8000AC4C:
/* 8000AC4C 0000782C  7F E3 FB 78 */	mr r3, r31
/* 8000AC50 00007830  4B FF D1 19 */	bl HSD_JObjUnkMtxPtr
/* 8000AC54 00007834  3B FF 00 44 */	addi r31, r31, 0x44
lbl_8000AC58:
/* 8000AC58 00007838  38 7F 00 00 */	addi r3, r31, 0
/* 8000AC5C 0000783C  38 81 00 3C */	addi r4, r1, 0x3c
/* 8000AC60 00007840  48 36 E6 B1 */	bl HSD_MtxInverse
/* 8000AC64 00007844  38 61 00 3C */	addi r3, r1, 0x3c
/* 8000AC68 00007848  38 81 00 90 */	addi r4, r1, 0x90
/* 8000AC6C 0000784C  38 A1 00 24 */	addi r5, r1, 0x24
/* 8000AC70 00007850  48 33 7E 39 */	bl PSMTXMUltiVec
/* 8000AC74 00007854  38 61 00 3C */	addi r3, r1, 0x3c
/* 8000AC78 00007858  38 81 00 84 */	addi r4, r1, 0x84
/* 8000AC7C 0000785C  38 A1 00 30 */	addi r5, r1, 0x30
/* 8000AC80 00007860  48 33 7E 29 */	bl PSMTXMUltiVec
/* 8000AC84 00007864  80 61 00 30 */	lwz r3, 0x30(r1)
/* 8000AC88 00007868  FC 20 F8 90 */	fmr f1, f31
/* 8000AC8C 0000786C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8000AC90 00007870  38 A1 00 78 */	addi r5, r1, 0x78
/* 8000AC94 00007874  90 61 00 78 */	stw r3, 0x78(r1)
/* 8000AC98 00007878  80 C1 00 34 */	lwz r6, 0x34(r1)
/* 8000AC9C 0000787C  90 01 00 6C */	stw r0, 0x6c(r1)
/* 8000ACA0 00007880  38 81 00 6C */	addi r4, r1, 0x6c
/* 8000ACA4 00007884  80 01 00 28 */	lwz r0, 0x28(r1)
/* 8000ACA8 00007888  7F E3 FB 78 */	mr r3, r31
/* 8000ACAC 0000788C  90 C1 00 7C */	stw r6, 0x7c(r1)
/* 8000ACB0 00007890  80 C1 00 38 */	lwz r6, 0x38(r1)
/* 8000ACB4 00007894  38 ED 80 38 */	addi r7, r13, lbl_804D36D8@sda21
/* 8000ACB8 00007898  90 01 00 70 */	stw r0, 0x70(r1)
/* 8000ACBC 0000789C  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 8000ACC0 000078A0  90 C1 00 80 */	stw r6, 0x80(r1)
/* 8000ACC4 000078A4  38 CD 80 34 */	addi r6, r13, lbl_804D36D4@sda21
/* 8000ACC8 000078A8  90 01 00 74 */	stw r0, 0x74(r1)
/* 8000ACCC 000078AC  4B FF E9 E9 */	bl func_800096B4
/* 8000ACD0 000078B0  38 60 00 01 */	li r3, 1
/* 8000ACD4 000078B4  48 00 00 08 */	b lbl_8000ACDC
lbl_8000ACD8:
/* 8000ACD8 000078B8  38 60 00 00 */	li r3, 0
lbl_8000ACDC:
/* 8000ACDC 000078BC  80 01 00 EC */	lwz r0, 0xec(r1)
/* 8000ACE0 000078C0  CB E1 00 E0 */	lfd f31, 0xe0(r1)
/* 8000ACE4 000078C4  83 E1 00 DC */	lwz r31, 0xdc(r1)
/* 8000ACE8 000078C8  83 C1 00 D8 */	lwz r30, 0xd8(r1)
/* 8000ACEC 000078CC  83 A1 00 D4 */	lwz r29, 0xd4(r1)
/* 8000ACF0 000078D0  38 21 00 E8 */	addi r1, r1, 0xe8
/* 8000ACF4 000078D4  7C 08 03 A6 */	mtlr r0
/* 8000ACF8 000078D8  4E 80 00 20 */	blr

.global func_8000ACFC
func_8000ACFC:
/* 8000ACFC 000078DC  38 00 00 02 */	li r0, 2
/* 8000AD00 000078E0  7C 09 03 A6 */	mtctr r0
/* 8000AD04 000078E4  38 84 00 74 */	addi r4, r4, 0x74
/* 8000AD08 000078E8  38 A0 00 00 */	li r5, 0
lbl_8000AD0C:
/* 8000AD0C 000078EC  80 04 00 00 */	lwz r0, 0(r4)
/* 8000AD10 000078F0  7C 00 18 40 */	cmplw r0, r3
/* 8000AD14 000078F4  41 82 00 60 */	beq lbl_8000AD74
/* 8000AD18 000078F8  84 04 00 08 */	lwzu r0, 8(r4)
/* 8000AD1C 000078FC  38 A5 00 01 */	addi r5, r5, 1
/* 8000AD20 00007900  7C 00 18 40 */	cmplw r0, r3
/* 8000AD24 00007904  41 82 00 50 */	beq lbl_8000AD74
/* 8000AD28 00007908  84 04 00 08 */	lwzu r0, 8(r4)
/* 8000AD2C 0000790C  38 A5 00 01 */	addi r5, r5, 1
/* 8000AD30 00007910  7C 00 18 40 */	cmplw r0, r3
/* 8000AD34 00007914  41 82 00 40 */	beq lbl_8000AD74
/* 8000AD38 00007918  84 04 00 08 */	lwzu r0, 8(r4)
/* 8000AD3C 0000791C  38 A5 00 01 */	addi r5, r5, 1
/* 8000AD40 00007920  7C 00 18 40 */	cmplw r0, r3
/* 8000AD44 00007924  41 82 00 30 */	beq lbl_8000AD74
/* 8000AD48 00007928  84 04 00 08 */	lwzu r0, 8(r4)
/* 8000AD4C 0000792C  38 A5 00 01 */	addi r5, r5, 1
/* 8000AD50 00007930  7C 00 18 40 */	cmplw r0, r3
/* 8000AD54 00007934  41 82 00 20 */	beq lbl_8000AD74
/* 8000AD58 00007938  84 04 00 08 */	lwzu r0, 8(r4)
/* 8000AD5C 0000793C  38 A5 00 01 */	addi r5, r5, 1
/* 8000AD60 00007940  7C 00 18 40 */	cmplw r0, r3
/* 8000AD64 00007944  41 82 00 10 */	beq lbl_8000AD74
/* 8000AD68 00007948  38 84 00 08 */	addi r4, r4, 8
/* 8000AD6C 0000794C  38 A5 00 01 */	addi r5, r5, 1
/* 8000AD70 00007950  42 00 FF 9C */	bdnz lbl_8000AD0C
lbl_8000AD74:
/* 8000AD74 00007954  28 05 00 0C */	cmplwi r5, 0xc
/* 8000AD78 00007958  40 82 00 0C */	bne lbl_8000AD84
/* 8000AD7C 0000795C  38 60 00 00 */	li r3, 0
/* 8000AD80 00007960  4E 80 00 20 */	blr
lbl_8000AD84:
/* 8000AD84 00007964  38 60 00 01 */	li r3, 1
/* 8000AD88 00007968  4E 80 00 20 */	blr


.section .data
    .balign 8

.global lbl_803B9928
lbl_803B9928:
    .4byte lbl_804D36AC
    .4byte lbl_804D36B0
    .4byte lbl_804D36B4
    .4byte lbl_804D36B8
    .4byte lbl_804D36BC
    .4byte lbl_804D36C0
    .4byte 0x29CF2D41
    .4byte 0x11512000
    .4byte 0x2D411FFF
    .4byte 0x29CFE783
    .4byte 0x29CF0000
    .4byte 0xC4E0187D
    .4byte 0x11513B20
    .4byte 0x11511151
    .4byte 0xD2BF29CF
    .4byte 0x0000D2BF
    .4byte 0x2D4116A0
    .4byte 0x187D36A0
    .4byte 0x0000187D
    .4byte 0x3B20095F
    .4byte 0xC4E016A0
    .4byte 0x00003B20
    .4byte 0x187D095F
    .4byte 0x3B2016A0
    .4byte 0x11512D41
    .4byte 0x29CF0000
    .4byte 0x2D412D41
    .4byte 0x29CF187D
    .4byte 0x29CF36A0
    .4byte 0x187D16A0
    .4byte 0x2D410000
    .4byte 0x2D413B20
    .4byte 0x0000187D
    .4byte 0x36A0E783
    .4byte 0x16A016A0
    .4byte 0x3B20095F
    .4byte 0x2000D2BF
    .4byte 0x1FFF29CF
    .4byte 0xD2BF1151
    .4byte 0x16A0C4E0
    .4byte 0x095F1151
    .4byte 0xC4E01151
    .4byte NULL
    .4byte 0x3FFF187D
    .4byte 0x00003B20
    .4byte 0x16A0E783
    .4byte 0x36A00000
    .4byte 0xE7833B20
    .4byte 0x00003B20
    .4byte 0xE7830000
    .4byte 0x2D41D2BF
    .4byte 0x0000187D
    .4byte 0xC4E00000
    .4byte 0x0000C001
    .4byte 0x0000E783
    .4byte 0xC4E00000
    .4byte 0xD2BFD2BF
    .4byte 0x0000C4E0
    .4byte 0xE783095F
    .4byte 0x3B20E960
    .4byte 0x11512D41
    .4byte 0xD63116A0
    .4byte 0x187DC960
    .4byte 0x187D0000
    .4byte 0xC4E016A0
    .4byte 0xE783C960
    .4byte 0x1151D2BF
    .4byte 0xD631095F
    .4byte 0xC4E0E960
    .4byte 0x11513B20
    .4byte 0xEEAF1FFF
    .4byte 0x2D41E000
    .4byte 0x29CF187D
    .4byte 0xD6312D41
    .4byte 0x0000D2BF
    .4byte 0x29CFE783
    .4byte 0xD6311FFF
    .4byte 0xD2BFE000
    .4byte 0x1151C4E0
    .4byte 0xEEAF0000
    .4byte 0x40000000
    .4byte 0x187D3B20
    .4byte 0x000016A0
    .4byte 0x3B20F6A1
    .4byte 0x2D412D41
    .4byte 0x000029CF
    .4byte 0x2D41EEAF
    .4byte 0x3B20187D
    .4byte 0x000036A0
    .4byte 0x187DE960
    .4byte 0x40000000
    .4byte 0x00003B20
    .4byte 0x0000E783
    .4byte 0x3B20E783
    .4byte 0x000036A0
    .4byte 0xE783E960
    .4byte 0x2D41D2BF
    .4byte 0x000029CF
    .4byte 0xD2BFEEAF
    .4byte 0x0000C000
    .4byte 0x0000187D
    .4byte 0xC4E00000
    .4byte 0x16A0C4E0
    .4byte 0xF6A10000
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x29C72D49
    .4byte 0x114E1FF9
    .4byte 0x2D491FF9
    .4byte 0x29CDE77B
    .4byte 0x29CD0000
    .4byte 0xC4DC1875
    .4byte 0x114B3B24
    .4byte 0x114B114E
    .4byte 0xD2B729C7
    .4byte 0x0000D2B7
    .4byte 0x2D38169F
    .4byte 0x1885369D
    .4byte 0x00001885
    .4byte 0x3B1D095C
    .4byte 0xC4DC1699
    .4byte 0x00003B24
    .4byte 0x1875095C
    .4byte 0x3B241699
    .4byte 0x114E2D49
    .4byte 0x29C70000
    .4byte 0x2D492D38
    .4byte 0x29CD1885
    .4byte 0x29CD369D
    .4byte 0x1885169F
    .4byte 0x2D410000
    .4byte 0x2D413B20
    .4byte 0x0000187D
    .4byte 0x369DE77B
    .4byte 0x169F1699
    .4byte 0x3B24095C
    .4byte 0x1FF9D2B7
    .4byte 0x1FF929C7
    .4byte 0xD2B7114E
    .4byte 0x1699C4DC
    .4byte 0x095C114B
    .4byte 0xC4DC114B
    .4byte NULL
    .4byte 0x4000187D
    .4byte 0x00003B20
    .4byte 0x169FE77B
    .4byte 0x369D0000
    .4byte 0xE77B3B1D
    .4byte 0x00003B24
    .4byte 0xE78B0000
    .4byte 0x2D49D2C8
    .4byte 0x00001885
    .4byte 0xC4E30000
    .4byte 0x0000C000
    .4byte 0x0000E77B
    .4byte 0xC4E30000
    .4byte 0xD2B7D2C8
    .4byte 0x0000C4DC
    .4byte 0xE78B095C
    .4byte 0x3B24E967
    .4byte 0x114E2D49
    .4byte 0xD639169F
    .4byte 0x1885C963
    .4byte 0x187D0000
    .4byte 0xC4E0169F
    .4byte 0xE77BC963
    .4byte 0x114ED2B7
    .4byte 0xD639095C
    .4byte 0xC4DCE967
    .4byte 0x114B3B24
    .4byte 0xEEB51FF9
    .4byte 0x2D49E007
    .4byte 0x29CD1885
    .4byte 0xD6332D41
    .4byte 0x0000D2BF
    .4byte 0x29CDE77B
    .4byte 0xD6331FF9
    .4byte 0xD2B7E007
    .4byte 0x114BC4DC
    .4byte 0xEEB50000
    .4byte 0x40000000
    .4byte 0x18753B24
    .4byte 0x00001699
    .4byte 0x3B24F6A4
    .4byte 0x2D382D49
    .4byte 0x000029C7
    .4byte 0x2D49EEB2
    .4byte 0x3B1D1885
    .4byte 0x0000369D
    .4byte 0x1885E961
    .4byte 0x40000000
    .4byte 0x00003B20
    .4byte 0x0000E783
    .4byte 0x3B1DE77B
    .4byte 0x0000369D
    .4byte 0xE77BE961
    .4byte 0x2D38D2B7
    .4byte 0x000029C7
    .4byte 0xD2B7EEB2
    .4byte 0x0000C000
    .4byte 0x00001875
    .4byte 0xC4DC0000
    .4byte 0x1699C4DC
    .4byte 0xF6A40000
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x9800750B
    .4byte 0x0B04040C
    .4byte 0x0C010107
    .4byte 0x070E0E19
    .4byte 0x1910101A
    .4byte 0x1A020205
    .4byte 0x05141409
    .4byte 0x09141417
    .4byte 0x17151517
    .4byte 0x17161617
    .4byte 0x173E3E09
    .4byte 0x09030305
    .4byte 0x0506061A
    .4byte 0x1A1B1B19
    .4byte 0x19181807
    .4byte 0x0708080C
    .4byte 0x0C0D0D0B
    .4byte 0x0B0A0A0B
    .4byte 0x0B313104
    .4byte 0x04313113
    .4byte 0x13323200
    .4byte 0x0034340F
    .4byte 0x0F363611
    .4byte 0x11383812
    .4byte 0x123A3A15
    .4byte 0x153C3C16
    .4byte 0x163F3F3E
    .4byte 0x3E3F3F40
    .4byte 0x403F3F3D
    .4byte 0x3D3C3C3B
    .4byte 0x3B3A3A39
    .4byte 0x39383837
    .4byte 0x37363635
    .4byte 0x35343433
    .4byte 0x33323233
    .4byte 0x33313133
    .4byte 0x332A2A35
    .4byte 0x352B2B37
    .4byte 0x372C2C39
    .4byte 0x392D2D3B
    .4byte 0x3B2E2E3D
    .4byte 0x3D2F2F40
    .4byte 0x4030303E
    .4byte 0x3E303029
    .4byte 0x29303028
    .4byte 0x282F2F27
    .4byte 0x272E2E26
    .4byte 0x262D2D25
    .4byte 0x252C2C24
    .4byte 0x242B2B23
    .4byte 0x232A2A23
    .4byte 0x23313123
    .4byte 0x231C1C24
    .4byte 0x241D1D25
    .4byte 0x251E1E26
    .4byte 0x261F1F27
    .4byte 0x27202028
    .4byte 0x28212129
    .4byte 0x2922223E
    .4byte 0x3E98000C
    .4byte 0x15151414
    .4byte 0x12120202
    .4byte 0x11111010
    .4byte 0x0F0F0E0E
    .4byte 0x00000101
    .4byte 0x13130404
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0xE0000000
    .4byte 0x3FFFE001
    .4byte 0xE7833B20
    .4byte 0xE0000000
    .4byte 0xC0010000
    .4byte 0x0000C001
    .4byte 0x20000000
    .4byte 0xC001E001
    .4byte 0xC4E0E783
    .4byte 0xE001E783
    .4byte 0xC4E0E001
    .4byte 0xD2BFD2BF
    .4byte 0xE000187D
    .4byte 0xC4E00000
    .4byte 0x187DC4E0
    .4byte 0x1FFF187D
    .4byte 0xC4E01FFF
    .4byte 0x187D3B20
    .4byte 0xE000187D
    .4byte 0x3B20E000
    .4byte 0x2D412D41
    .4byte 0x0000187D
    .4byte 0x3B20E001
    .4byte 0xC0010000
    .4byte 0x0000E783
    .4byte 0xC4E00000
    .4byte 0xD2BFD2BF
    .4byte 0x2000D2BF
    .4byte 0xD2BF2000
    .4byte 0xE783C4E0
    .4byte 0xE0002D41
    .4byte 0xD2BF0000
    .4byte 0x2D41D2BF
    .4byte 0x1FFF2D41
    .4byte 0xD2BF0000
    .4byte 0xC4E0E783
    .4byte 0x0000C001
    .4byte 0x00002000
    .4byte 0xC0010000
    .4byte 0x2000C4E0
    .4byte 0xE7830000
    .4byte 0x2D412D41
    .4byte 0x1FFF3B20
    .4byte 0x187D1FFF
    .4byte 0x2D412D41
    .4byte 0x0000E783
    .4byte 0x3B200000
    .4byte 0x00003FFF
    .4byte 0x20000000
    .4byte 0x3FFF2000
    .4byte 0xE7833B20
    .4byte 0x2000D2BF
    .4byte 0x2D412000
    .4byte 0xC4E0187D
    .4byte 0xE0003B20
    .4byte 0xE7830000
    .4byte 0x3B20E783
    .4byte 0x1FFF3B20
    .4byte 0xE7831FFF
    .4byte 0x40000000
    .4byte 0xE001C4E0
    .4byte 0x187DE001
    .4byte 0xD2BF2D41
    .4byte 0x0000D2BF
    .4byte 0x2D410000
    .4byte 0xC4E0187D
    .4byte 0xE0003B20
    .4byte 0x187DE000
    .4byte 0x40000000
    .4byte 0x00004000
    .4byte NULL
    .4byte 0x3B20187D
    .4byte NULL
    .4byte 0xFFC00000
    .4byte 0x0018FFC5
    .4byte 0x00000018
    .4byte 0x003B0000
    .4byte 0xFFD3FFD3
    .4byte 0x0000FFE8
    .4byte 0xFFC50000
    .4byte 0x002DFFD3
    .4byte 0x0000FFC0
    .4byte NULL
    .4byte 0xFFC5FFE8
    .4byte 0x0000002D
    .4byte 0x002D0000
    .4byte 0x00000040
    .4byte 0x0000FFE8
    .4byte 0x003B0000
    .4byte 0x003BFFE8
    .4byte 0x0000FFD3
    .4byte 0x002D0000
    .4byte 0xFFC50018
    .4byte 0x00000040
    .4byte NULL
    .4byte 0x003B0018
    .4byte 0x9800452C
    .4byte 0x0F2D0E2F
    .4byte 0x0F2D0E2E
    .4byte 0x0E240B25
    .4byte 0x0B140515
    .4byte 0x05080109
    .4byte 0x01020003
    .4byte 0x00060410
    .4byte 0x04070311
    .4byte 0x03050717
    .4byte 0x070F0618
    .4byte 0x06280D2B
    .4byte 0x0D290C2A
    .4byte 0x0C010A1E
    .4byte 0x0A00091F
    .4byte 0x090C020E
    .4byte 0x020D081B
    .4byte 0x082C0F1B
    .4byte 0x082F0F1D
    .4byte 0x082F0F1C
    .4byte 0x0F2E0E27
    .4byte 0x0E250B26
    .4byte 0x0B150516
    .4byte 0x0509010A
    .4byte 0x01030004
    .4byte 0x00100413
    .4byte 0x04110312
    .4byte 0x0317071A
    .4byte 0x07180619
    .4byte 0x062B0D23
    .4byte 0x0D2A0C22
    .4byte 0x0C1E0A21
    .4byte 0x0A1F0920
    .4byte 0x090E020B
    .4byte 0x021B081D
    .4byte 0x08000000
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL


.section .sdata
    .balign 8
.global lbl_804D36A0
lbl_804D36A0:
    .4byte 0xFF000080

.global lbl_804D36A4
lbl_804D36A4:
    .4byte 0xFF00FF80

.global lbl_804D36A8
lbl_804D36A8:
    .4byte 0x80000080

.global lbl_804D36AC
lbl_804D36AC:
    .4byte 0xFFFF0080

.global lbl_804D36B0
lbl_804D36B0:
    .4byte 0x80800080

.global lbl_804D36B4
lbl_804D36B4:
    .4byte 0x00FF0080

.global lbl_804D36B8
lbl_804D36B8:
    .4byte 0x00800080

.global lbl_804D36BC
lbl_804D36BC:
    .4byte 0x0000FF80

.global lbl_804D36C0
lbl_804D36C0:
    .4byte 0x00008080

.global lbl_804D36C4
lbl_804D36C4:
    .4byte 0x00FFFF80

.global lbl_804D36C8
lbl_804D36C8:
    .4byte 0x00808080

.global lbl_804D36CC
lbl_804D36CC:
    .4byte 0x00FF8080

.global lbl_804D36D0
lbl_804D36D0:
    .4byte 0x00804080

.global lbl_804D36D4
lbl_804D36D4:
    .4byte 0x0080FF80

.global lbl_804D36D8
lbl_804D36D8:
    .4byte 0x00408080

.global lbl_804D36DC
lbl_804D36DC:
    .4byte 0xFFFFFF80

.global lbl_804D36E0
lbl_804D36E0:
    .4byte 0xFF800080

.global lbl_804D36E4
lbl_804D36E4:
    .4byte 0x80400080

.global lbl_804D36E8
lbl_804D36E8:
    .4byte 0xFFFFFF80

.global lbl_804D36EC
lbl_804D36EC:
    .4byte 0x80808080

.global lbl_804D36F0
lbl_804D36F0:
    .4byte 0xFFFF0080

.global lbl_804D36F4
lbl_804D36F4:
    .4byte 0x80800080

.global lbl_804D36F8
lbl_804D36F8:
    .4byte 0xFF000080

.global lbl_804D36FC
lbl_804D36FC:
    .4byte 0x80000080

.global lbl_804D3700
lbl_804D3700:
    .asciz "jobj.h"
    .balign 4

.global lbl_804D3708
lbl_804D3708:
    .asciz "jobj"
    .balign 4


.section .sdata2
    .balign 4

.global lbl_804D7A18
lbl_804D7A18:
    .4byte 0x3FE00000
    .4byte 0x00000000

.global lbl_804D7A20
lbl_804D7A20:
    .4byte 0x40080000
    .4byte 0x00000000

.global lbl_804D7A28
lbl_804D7A28:
    .4byte 0x40000000

.global lbl_804D7A2C
lbl_804D7A2C:
    .4byte 0x40800000

.global lbl_804D7A30
lbl_804D7A30:
    .4byte 0x40490FDB

.global lbl_804D7A34
lbl_804D7A34:
    .4byte 0x41A00000

.global lbl_804D7A38
lbl_804D7A38:
    .4byte 0x40400000

.global lbl_804D7A3C
lbl_804D7A3C:
    .4byte 0x3F000000

.global lbl_804D7A40
lbl_804D7A40:
    .4byte 0x40A00000
    .4byte 0x00000000

.global lbl_804D7A48
lbl_804D7A48:
    .4byte 0x43300000
    .4byte 0x00000000

.global lbl_804D7A50
lbl_804D7A50:
    .4byte 0x00000000

.global lbl_804D7A54
lbl_804D7A54:
    .4byte 0xBF800000
