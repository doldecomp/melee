.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240

.global lbl_80202B6C
lbl_80202B6C:
/* 80202B6C 001FF74C  4E 80 00 20 */	blr 
.global lbl_80202B70
lbl_80202B70:
/* 80202B70 001FF750  7C 08 02 A6 */	mflr r0
/* 80202B74 001FF754  90 01 00 04 */	stw r0, 4(r1)
/* 80202B78 001FF758  94 21 FF F8 */	stwu r1, -8(r1)
/* 80202B7C 001FF75C  4B FC 1E 7D */	bl func_801C49F8
/* 80202B80 001FF760  3C 80 80 4A */	lis r4, lbl_8049E6C8@ha
/* 80202B84 001FF764  90 6D B3 88 */	stw r3, lbl_804D6A28@sda21(r13)
/* 80202B88 001FF768  38 64 E6 C8 */	addi r3, r4, lbl_8049E6C8@l
/* 80202B8C 001FF76C  38 A3 00 8C */	addi r5, r3, 0x8c
/* 80202B90 001FF770  88 03 00 8C */	lbz r0, 0x8c(r3)
/* 80202B94 001FF774  38 60 00 00 */	li r3, 0
/* 80202B98 001FF778  50 60 1F 38 */	rlwimi r0, r3, 3, 0x1c, 0x1c
/* 80202B9C 001FF77C  98 05 00 00 */	stb r0, 0(r5)
/* 80202BA0 001FF780  38 80 00 01 */	li r4, 1
/* 80202BA4 001FF784  38 60 00 00 */	li r3, 0
/* 80202BA8 001FF788  88 05 00 00 */	lbz r0, 0(r5)
/* 80202BAC 001FF78C  50 80 17 7A */	rlwimi r0, r4, 2, 0x1d, 0x1d
/* 80202BB0 001FF790  98 05 00 00 */	stb r0, 0(r5)
/* 80202BB4 001FF794  48 00 00 C5 */	bl func_80202C78
/* 80202BB8 001FF798  38 60 00 04 */	li r3, 4
/* 80202BBC 001FF79C  48 00 00 BD */	bl func_80202C78
/* 80202BC0 001FF7A0  38 60 00 05 */	li r3, 5
/* 80202BC4 001FF7A4  48 00 00 B5 */	bl func_80202C78
/* 80202BC8 001FF7A8  38 60 00 06 */	li r3, 6
/* 80202BCC 001FF7AC  48 00 00 AD */	bl func_80202C78
/* 80202BD0 001FF7B0  38 60 00 01 */	li r3, 1
/* 80202BD4 001FF7B4  48 00 00 A5 */	bl func_80202C78
/* 80202BD8 001FF7B8  38 60 00 03 */	li r3, 3
/* 80202BDC 001FF7BC  48 00 00 9D */	bl func_80202C78
/* 80202BE0 001FF7C0  38 60 00 02 */	li r3, 2
/* 80202BE4 001FF7C4  48 00 00 95 */	bl func_80202C78
/* 80202BE8 001FF7C8  4B FC 0D D9 */	bl func_801C39C0
/* 80202BEC 001FF7CC  4B FC 0F C9 */	bl func_801C3BB4
/* 80202BF0 001FF7D0  48 02 25 A5 */	bl func_80225194
/* 80202BF4 001FF7D4  2C 03 00 3E */	cmpwi r3, 0x3e
/* 80202BF8 001FF7D8  41 82 00 1C */	beq lbl_80202C14
/* 80202BFC 001FF7DC  4B F6 86 3D */	bl func_8016B238
/* 80202C00 001FF7E0  2C 03 00 00 */	cmpwi r3, 0
/* 80202C04 001FF7E4  40 82 00 10 */	bne lbl_80202C14
/* 80202C08 001FF7E8  3C 60 00 06 */	lis r3, 0x00064194@ha
/* 80202C0C 001FF7EC  38 63 41 94 */	addi r3, r3, 0x00064194@l
/* 80202C10 001FF7F0  4B FC 27 DD */	bl func_801C53EC
lbl_80202C14:
/* 80202C14 001FF7F4  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80202C18 001FF7F8  38 21 00 08 */	addi r1, r1, 8
/* 80202C1C 001FF7FC  7C 08 03 A6 */	mtlr r0
/* 80202C20 001FF800  4E 80 00 20 */	blr 
.global lbl_80202C24
lbl_80202C24:
/* 80202C24 001FF804  7C 08 02 A6 */	mflr r0
/* 80202C28 001FF808  3C 60 00 06 */	lis r3, 0x00064193@ha
/* 80202C2C 001FF80C  90 01 00 04 */	stw r0, 4(r1)
/* 80202C30 001FF810  38 63 41 93 */	addi r3, r3, 0x00064193@l
/* 80202C34 001FF814  94 21 FF F8 */	stwu r1, -8(r1)
/* 80202C38 001FF818  4B FC 27 B5 */	bl func_801C53EC
/* 80202C3C 001FF81C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80202C40 001FF820  38 21 00 08 */	addi r1, r1, 8
/* 80202C44 001FF824  7C 08 03 A6 */	mtlr r0
/* 80202C48 001FF828  4E 80 00 20 */	blr 
.global lbl_80202C4C
lbl_80202C4C:
/* 80202C4C 001FF82C  7C 08 02 A6 */	mflr r0
/* 80202C50 001FF830  38 60 00 00 */	li r3, 0
/* 80202C54 001FF834  90 01 00 04 */	stw r0, 4(r1)
/* 80202C58 001FF838  94 21 FF F8 */	stwu r1, -8(r1)
/* 80202C5C 001FF83C  4B FC 81 A9 */	bl func_801CAE04
/* 80202C60 001FF840  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80202C64 001FF844  38 21 00 08 */	addi r1, r1, 8
/* 80202C68 001FF848  7C 08 03 A6 */	mtlr r0
/* 80202C6C 001FF84C  4E 80 00 20 */	blr 
.global lbl_80202C70
lbl_80202C70:
/* 80202C70 001FF850  38 60 00 00 */	li r3, 0
/* 80202C74 001FF854  4E 80 00 20 */	blr 

.global func_80202C78
func_80202C78:
/* 80202C78 001FF858  7C 08 02 A6 */	mflr r0
/* 80202C7C 001FF85C  90 01 00 04 */	stw r0, 4(r1)
/* 80202C80 001FF860  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80202C84 001FF864  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80202C88 001FF868  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80202C8C 001FF86C  93 A1 00 14 */	stw r29, 0x14(r1)
/* 80202C90 001FF870  93 81 00 10 */	stw r28, 0x10(r1)
/* 80202C94 001FF874  3B 83 00 00 */	addi r28, r3, 0
/* 80202C98 001FF878  1C 1C 00 14 */	mulli r0, r28, 0x14
/* 80202C9C 001FF87C  3C 60 80 3E */	lis r3, lbl_803E5248@ha
/* 80202CA0 001FF880  3B E3 52 48 */	addi r31, r3, lbl_803E5248@l
/* 80202CA4 001FF884  38 7C 00 00 */	addi r3, r28, 0
/* 80202CA8 001FF888  7F BF 02 14 */	add r29, r31, r0
/* 80202CAC 001FF88C  4B FB E8 25 */	bl func_801C14D0
/* 80202CB0 001FF890  7C 7E 1B 79 */	or. r30, r3, r3
/* 80202CB4 001FF894  41 82 00 70 */	beq lbl_80202D24
/* 80202CB8 001FF898  83 FE 00 2C */	lwz r31, 0x2c(r30)
/* 80202CBC 001FF89C  38 00 00 00 */	li r0, 0
/* 80202CC0 001FF8A0  3C 60 80 1C */	lis r3, func_801C5DB0@ha
/* 80202CC4 001FF8A4  90 1F 00 08 */	stw r0, 8(r31)
/* 80202CC8 001FF8A8  38 83 5D B0 */	addi r4, r3, func_801C5DB0@l
/* 80202CCC 001FF8AC  38 7E 00 00 */	addi r3, r30, 0
/* 80202CD0 001FF8B0  90 1F 00 0C */	stw r0, 0xc(r31)
/* 80202CD4 001FF8B4  38 A0 00 03 */	li r5, 3
/* 80202CD8 001FF8B8  38 C0 00 00 */	li r6, 0
/* 80202CDC 001FF8BC  48 18 D9 C1 */	bl func_8039069C
/* 80202CE0 001FF8C0  80 1D 00 0C */	lwz r0, 0xc(r29)
/* 80202CE4 001FF8C4  28 00 00 00 */	cmplwi r0, 0
/* 80202CE8 001FF8C8  41 82 00 08 */	beq lbl_80202CF0
/* 80202CEC 001FF8CC  90 1F 00 1C */	stw r0, 0x1c(r31)
lbl_80202CF0:
/* 80202CF0 001FF8D0  81 9D 00 00 */	lwz r12, 0(r29)
/* 80202CF4 001FF8D4  28 0C 00 00 */	cmplwi r12, 0
/* 80202CF8 001FF8D8  41 82 00 10 */	beq lbl_80202D08
/* 80202CFC 001FF8DC  7D 88 03 A6 */	mtlr r12
/* 80202D00 001FF8E0  38 7E 00 00 */	addi r3, r30, 0
/* 80202D04 001FF8E4  4E 80 00 21 */	blrl 
lbl_80202D08:
/* 80202D08 001FF8E8  80 9D 00 08 */	lwz r4, 8(r29)
/* 80202D0C 001FF8EC  28 04 00 00 */	cmplwi r4, 0
/* 80202D10 001FF8F0  41 82 00 2C */	beq lbl_80202D3C
/* 80202D14 001FF8F4  38 7E 00 00 */	addi r3, r30, 0
/* 80202D18 001FF8F8  38 A0 00 04 */	li r5, 4
/* 80202D1C 001FF8FC  48 18 D0 39 */	bl func_8038FD54
/* 80202D20 001FF900  48 00 00 1C */	b lbl_80202D3C
lbl_80202D24:
/* 80202D24 001FF904  38 DC 00 00 */	addi r6, r28, 0
/* 80202D28 001FF908  4C C6 31 82 */	crclr 6
/* 80202D2C 001FF90C  38 7F 00 CC */	addi r3, r31, 0xcc
/* 80202D30 001FF910  38 9F 00 F0 */	addi r4, r31, 0xf0
/* 80202D34 001FF914  38 A0 00 E3 */	li r5, 0xe3
/* 80202D38 001FF918  48 14 29 71 */	bl OSReport
lbl_80202D3C:
/* 80202D3C 001FF91C  7F C3 F3 78 */	mr r3, r30
/* 80202D40 001FF920  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80202D44 001FF924  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80202D48 001FF928  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80202D4C 001FF92C  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 80202D50 001FF930  83 81 00 10 */	lwz r28, 0x10(r1)
/* 80202D54 001FF934  38 21 00 20 */	addi r1, r1, 0x20
/* 80202D58 001FF938  7C 08 03 A6 */	mtlr r0
/* 80202D5C 001FF93C  4E 80 00 20 */	blr 
.global lbl_80202D60
lbl_80202D60:
/* 80202D60 001FF940  7C 08 02 A6 */	mflr r0
/* 80202D64 001FF944  38 A0 00 00 */	li r5, 0
/* 80202D68 001FF948  90 01 00 04 */	stw r0, 4(r1)
/* 80202D6C 001FF94C  94 21 FF F8 */	stwu r1, -8(r1)
/* 80202D70 001FF950  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 80202D74 001FF954  80 84 00 14 */	lwz r4, 0x14(r4)
/* 80202D78 001FF958  4B FC 53 C1 */	bl func_801C8138
/* 80202D7C 001FF95C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80202D80 001FF960  38 21 00 08 */	addi r1, r1, 8
/* 80202D84 001FF964  7C 08 03 A6 */	mtlr r0
/* 80202D88 001FF968  4E 80 00 20 */	blr 
.global lbl_80202D8C
lbl_80202D8C:
/* 80202D8C 001FF96C  38 60 00 00 */	li r3, 0
/* 80202D90 001FF970  4E 80 00 20 */	blr 
.global lbl_80202D94
lbl_80202D94:
/* 80202D94 001FF974  4E 80 00 20 */	blr 
.global lbl_80202D98
lbl_80202D98:
/* 80202D98 001FF978  4E 80 00 20 */	blr 
lbl_80202D9C:
/* 80202D9C 001FF97C  7C 08 02 A6 */	mflr r0
/* 80202DA0 001FF980  3C 80 80 20 */	lis r4, lbl_8020349C@ha
/* 80202DA4 001FF984  90 01 00 04 */	stw r0, 4(r1)
/* 80202DA8 001FF988  38 A4 34 9C */	addi r5, r4, lbl_8020349C@l
/* 80202DAC 001FF98C  38 80 00 04 */	li r4, 4
/* 80202DB0 001FF990  94 21 FF F8 */	stwu r1, -8(r1)
/* 80202DB4 001FF994  4B EB D9 35 */	bl func_800C06E8
/* 80202DB8 001FF998  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80202DBC 001FF99C  38 21 00 08 */	addi r1, r1, 8
/* 80202DC0 001FF9A0  7C 08 03 A6 */	mtlr r0
/* 80202DC4 001FF9A4  4E 80 00 20 */	blr 
.global lbl_80202DC8
lbl_80202DC8:
/* 80202DC8 001FF9A8  7C 08 02 A6 */	mflr r0
/* 80202DCC 001FF9AC  38 A0 00 00 */	li r5, 0
/* 80202DD0 001FF9B0  90 01 00 04 */	stw r0, 4(r1)
/* 80202DD4 001FF9B4  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80202DD8 001FF9B8  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80202DDC 001FF9BC  93 C1 00 10 */	stw r30, 0x10(r1)
/* 80202DE0 001FF9C0  7C 7E 1B 78 */	mr r30, r3
/* 80202DE4 001FF9C4  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80202DE8 001FF9C8  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 80202DEC 001FF9CC  4B FC 53 4D */	bl func_801C8138
/* 80202DF0 001FF9D0  38 00 00 00 */	li r0, 0
/* 80202DF4 001FF9D4  90 1F 00 08 */	stw r0, 8(r31)
/* 80202DF8 001FF9D8  3C 60 80 20 */	lis r3, lbl_80202D9C@ha
/* 80202DFC 001FF9DC  38 83 2D 9C */	addi r4, r3, lbl_80202D9C@l
/* 80202E00 001FF9E0  90 1F 00 0C */	stw r0, 0xc(r31)
/* 80202E04 001FF9E4  7F C3 F3 78 */	mr r3, r30
/* 80202E08 001FF9E8  4B FB E2 B1 */	bl func_801C10B8
/* 80202E0C 001FF9EC  88 1F 00 11 */	lbz r0, 0x11(r31)
/* 80202E10 001FF9F0  38 60 00 01 */	li r3, 1
/* 80202E14 001FF9F4  50 60 2E 34 */	rlwimi r0, r3, 5, 0x18, 0x1a
/* 80202E18 001FF9F8  98 1F 00 11 */	stb r0, 0x11(r31)
/* 80202E1C 001FF9FC  88 1F 00 10 */	lbz r0, 0x10(r31)
/* 80202E20 001FFA00  50 60 17 7A */	rlwimi r0, r3, 2, 0x1d, 0x1d
/* 80202E24 001FFA04  98 1F 00 10 */	stb r0, 0x10(r31)
/* 80202E28 001FFA08  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80202E2C 001FFA0C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80202E30 001FFA10  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 80202E34 001FFA14  38 21 00 18 */	addi r1, r1, 0x18
/* 80202E38 001FFA18  7C 08 03 A6 */	mtlr r0
/* 80202E3C 001FFA1C  4E 80 00 20 */	blr 
.global lbl_80202E40
lbl_80202E40:
/* 80202E40 001FFA20  38 60 00 00 */	li r3, 0
/* 80202E44 001FFA24  4E 80 00 20 */	blr 
.global lbl_80202E48
lbl_80202E48:
/* 80202E48 001FFA28  7C 08 02 A6 */	mflr r0
/* 80202E4C 001FFA2C  90 01 00 04 */	stw r0, 4(r1)
/* 80202E50 001FFA30  94 21 FF F8 */	stwu r1, -8(r1)
/* 80202E54 001FFA34  4B E0 E7 A1 */	bl func_800115F4
/* 80202E58 001FFA38  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80202E5C 001FFA3C  38 21 00 08 */	addi r1, r1, 8
/* 80202E60 001FFA40  7C 08 03 A6 */	mtlr r0
/* 80202E64 001FFA44  4E 80 00 20 */	blr 
.global lbl_80202E68
lbl_80202E68:
/* 80202E68 001FFA48  4E 80 00 20 */	blr 
.global lbl_80202E6C
lbl_80202E6C:
/* 80202E6C 001FFA4C  7C 08 02 A6 */	mflr r0
/* 80202E70 001FFA50  38 A0 00 00 */	li r5, 0
/* 80202E74 001FFA54  90 01 00 04 */	stw r0, 4(r1)
/* 80202E78 001FFA58  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 80202E7C 001FFA5C  BF 41 00 10 */	stmw r26, 0x10(r1)
/* 80202E80 001FFA60  7C 7A 1B 78 */	mr r26, r3
/* 80202E84 001FFA64  83 63 00 2C */	lwz r27, 0x2c(r3)
/* 80202E88 001FFA68  80 9B 00 14 */	lwz r4, 0x14(r27)
/* 80202E8C 001FFA6C  4B FC 52 AD */	bl func_801C8138
/* 80202E90 001FFA70  38 00 00 00 */	li r0, 0
/* 80202E94 001FFA74  90 1B 00 08 */	stw r0, 8(r27)
/* 80202E98 001FFA78  38 A0 00 01 */	li r5, 1
/* 80202E9C 001FFA7C  38 7A 00 00 */	addi r3, r26, 0
/* 80202EA0 001FFA80  90 1B 00 0C */	stw r0, 0xc(r27)
/* 80202EA4 001FFA84  38 80 00 09 */	li r4, 9
/* 80202EA8 001FFA88  88 1B 00 11 */	lbz r0, 0x11(r27)
/* 80202EAC 001FFA8C  50 A0 2E 34 */	rlwimi r0, r5, 5, 0x18, 0x1a
/* 80202EB0 001FFA90  98 1B 00 11 */	stb r0, 0x11(r27)
/* 80202EB4 001FFA94  4B FC 10 F1 */	bl func_801C3FA4
/* 80202EB8 001FFA98  3B 63 00 00 */	addi r27, r3, 0
/* 80202EBC 001FFA9C  38 7A 00 00 */	addi r3, r26, 0
/* 80202EC0 001FFAA0  38 80 00 0A */	li r4, 0xa
/* 80202EC4 001FFAA4  4B FC 10 E1 */	bl func_801C3FA4
/* 80202EC8 001FFAA8  3B 83 00 00 */	addi r28, r3, 0
/* 80202ECC 001FFAAC  38 7A 00 00 */	addi r3, r26, 0
/* 80202ED0 001FFAB0  38 80 00 06 */	li r4, 6
/* 80202ED4 001FFAB4  4B FC 10 D1 */	bl func_801C3FA4
/* 80202ED8 001FFAB8  3B A3 00 00 */	addi r29, r3, 0
/* 80202EDC 001FFABC  38 7A 00 00 */	addi r3, r26, 0
/* 80202EE0 001FFAC0  38 80 00 07 */	li r4, 7
/* 80202EE4 001FFAC4  4B FC 10 C1 */	bl func_801C3FA4
/* 80202EE8 001FFAC8  3B C3 00 00 */	addi r30, r3, 0
/* 80202EEC 001FFACC  38 7A 00 00 */	addi r3, r26, 0
/* 80202EF0 001FFAD0  38 80 00 03 */	li r4, 3
/* 80202EF4 001FFAD4  4B FC 10 B1 */	bl func_801C3FA4
/* 80202EF8 001FFAD8  3B E3 00 00 */	addi r31, r3, 0
/* 80202EFC 001FFADC  38 7A 00 00 */	addi r3, r26, 0
/* 80202F00 001FFAE0  38 80 00 04 */	li r4, 4
/* 80202F04 001FFAE4  4B FC 10 A1 */	bl func_801C3FA4
/* 80202F08 001FFAE8  38 9F 00 00 */	addi r4, r31, 0
/* 80202F0C 001FFAEC  38 BE 00 00 */	addi r5, r30, 0
/* 80202F10 001FFAF0  38 DD 00 00 */	addi r6, r29, 0
/* 80202F14 001FFAF4  38 FC 00 00 */	addi r7, r28, 0
/* 80202F18 001FFAF8  39 1B 00 00 */	addi r8, r27, 0
/* 80202F1C 001FFAFC  4B FC 1F 55 */	bl func_801C4E70
/* 80202F20 001FFB00  BB 41 00 10 */	lmw r26, 0x10(r1)
/* 80202F24 001FFB04  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 80202F28 001FFB08  38 21 00 28 */	addi r1, r1, 0x28
/* 80202F2C 001FFB0C  7C 08 03 A6 */	mtlr r0
/* 80202F30 001FFB10  4E 80 00 20 */	blr 
.global lbl_80202F34
lbl_80202F34:
/* 80202F34 001FFB14  38 60 00 00 */	li r3, 0
/* 80202F38 001FFB18  4E 80 00 20 */	blr 
.global lbl_80202F3C
lbl_80202F3C:
/* 80202F3C 001FFB1C  4E 80 00 20 */	blr 
.global lbl_80202F40
lbl_80202F40:
/* 80202F40 001FFB20  4E 80 00 20 */	blr 
.global lbl_80202F44
lbl_80202F44:
/* 80202F44 001FFB24  7C 08 02 A6 */	mflr r0
/* 80202F48 001FFB28  38 A0 00 00 */	li r5, 0
/* 80202F4C 001FFB2C  90 01 00 04 */	stw r0, 4(r1)
/* 80202F50 001FFB30  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80202F54 001FFB34  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80202F58 001FFB38  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80202F5C 001FFB3C  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 80202F60 001FFB40  4B FC 51 D9 */	bl func_801C8138
/* 80202F64 001FFB44  38 00 00 00 */	li r0, 0
/* 80202F68 001FFB48  90 1F 00 08 */	stw r0, 8(r31)
/* 80202F6C 001FFB4C  38 60 00 01 */	li r3, 1
/* 80202F70 001FFB50  90 1F 00 0C */	stw r0, 0xc(r31)
/* 80202F74 001FFB54  88 1F 00 11 */	lbz r0, 0x11(r31)
/* 80202F78 001FFB58  50 60 2E 34 */	rlwimi r0, r3, 5, 0x18, 0x1a
/* 80202F7C 001FFB5C  98 1F 00 11 */	stb r0, 0x11(r31)
/* 80202F80 001FFB60  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80202F84 001FFB64  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80202F88 001FFB68  38 21 00 18 */	addi r1, r1, 0x18
/* 80202F8C 001FFB6C  7C 08 03 A6 */	mtlr r0
/* 80202F90 001FFB70  4E 80 00 20 */	blr 
.global lbl_80202F94
lbl_80202F94:
/* 80202F94 001FFB74  38 60 00 00 */	li r3, 0
/* 80202F98 001FFB78  4E 80 00 20 */	blr 
.global lbl_80202F9C
lbl_80202F9C:
/* 80202F9C 001FFB7C  4E 80 00 20 */	blr 
.global lbl_80202FA0
lbl_80202FA0:
/* 80202FA0 001FFB80  4E 80 00 20 */	blr 
.global lbl_80202FA4
lbl_80202FA4:
/* 80202FA4 001FFB84  7C 08 02 A6 */	mflr r0
/* 80202FA8 001FFB88  38 A0 00 00 */	li r5, 0
/* 80202FAC 001FFB8C  90 01 00 04 */	stw r0, 4(r1)
/* 80202FB0 001FFB90  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80202FB4 001FFB94  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80202FB8 001FFB98  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80202FBC 001FFB9C  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 80202FC0 001FFBA0  4B FC 51 79 */	bl func_801C8138
/* 80202FC4 001FFBA4  38 00 00 00 */	li r0, 0
/* 80202FC8 001FFBA8  90 1F 00 08 */	stw r0, 8(r31)
/* 80202FCC 001FFBAC  38 60 00 02 */	li r3, 2
/* 80202FD0 001FFBB0  90 1F 00 0C */	stw r0, 0xc(r31)
/* 80202FD4 001FFBB4  88 1F 00 11 */	lbz r0, 0x11(r31)
/* 80202FD8 001FFBB8  50 60 2E 34 */	rlwimi r0, r3, 5, 0x18, 0x1a
/* 80202FDC 001FFBBC  98 1F 00 11 */	stb r0, 0x11(r31)
/* 80202FE0 001FFBC0  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80202FE4 001FFBC4  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80202FE8 001FFBC8  38 21 00 18 */	addi r1, r1, 0x18
/* 80202FEC 001FFBCC  7C 08 03 A6 */	mtlr r0
/* 80202FF0 001FFBD0  4E 80 00 20 */	blr 
.global lbl_80202FF4
lbl_80202FF4:
/* 80202FF4 001FFBD4  38 60 00 00 */	li r3, 0
/* 80202FF8 001FFBD8  4E 80 00 20 */	blr 
.global lbl_80202FFC
lbl_80202FFC:
/* 80202FFC 001FFBDC  4E 80 00 20 */	blr 
.global lbl_80203000
lbl_80203000:
/* 80203000 001FFBE0  4E 80 00 20 */	blr 
.global lbl_80203004
lbl_80203004:
/* 80203004 001FFBE4  7C 08 02 A6 */	mflr r0
/* 80203008 001FFBE8  90 01 00 04 */	stw r0, 4(r1)
/* 8020300C 001FFBEC  38 00 00 00 */	li r0, 0
/* 80203010 001FFBF0  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80203014 001FFBF4  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80203018 001FFBF8  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8020301C 001FFBFC  7C 7E 1B 78 */	mr r30, r3
/* 80203020 001FFC00  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80203024 001FFC04  90 1F 00 C4 */	stw r0, 0xc4(r31)
/* 80203028 001FFC08  80 6D B3 88 */	lwz r3, lbl_804D6A28@sda21(r13)
/* 8020302C 001FFC0C  80 63 00 08 */	lwz r3, 8(r3)
/* 80203030 001FFC10  2C 03 00 00 */	cmpwi r3, 0
/* 80203034 001FFC14  41 82 00 0C */	beq lbl_80203040
/* 80203038 001FFC18  48 17 D5 49 */	bl HSD_Randi
/* 8020303C 001FFC1C  48 00 00 08 */	b lbl_80203044
lbl_80203040:
/* 80203040 001FFC20  7C 03 03 78 */	mr r3, r0
lbl_80203044:
/* 80203044 001FFC24  38 03 00 01 */	addi r0, r3, 1
/* 80203048 001FFC28  90 1F 00 C8 */	stw r0, 0xc8(r31)
/* 8020304C 001FFC2C  7F C3 F3 78 */	mr r3, r30
/* 80203050 001FFC30  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 80203054 001FFC34  80 BF 00 C4 */	lwz r5, 0xc4(r31)
/* 80203058 001FFC38  4B FC 50 E1 */	bl func_801C8138
/* 8020305C 001FFC3C  38 00 00 00 */	li r0, 0
/* 80203060 001FFC40  90 1F 00 08 */	stw r0, 8(r31)
/* 80203064 001FFC44  38 60 00 01 */	li r3, 1
/* 80203068 001FFC48  90 1F 00 0C */	stw r0, 0xc(r31)
/* 8020306C 001FFC4C  88 1F 00 11 */	lbz r0, 0x11(r31)
/* 80203070 001FFC50  50 60 2E 34 */	rlwimi r0, r3, 5, 0x18, 0x1a
/* 80203074 001FFC54  98 1F 00 11 */	stb r0, 0x11(r31)
/* 80203078 001FFC58  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8020307C 001FFC5C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80203080 001FFC60  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 80203084 001FFC64  38 21 00 18 */	addi r1, r1, 0x18
/* 80203088 001FFC68  7C 08 03 A6 */	mtlr r0
/* 8020308C 001FFC6C  4E 80 00 20 */	blr 
.global lbl_80203090
lbl_80203090:
/* 80203090 001FFC70  38 60 00 00 */	li r3, 0
/* 80203094 001FFC74  4E 80 00 20 */	blr 
.global lbl_80203098
lbl_80203098:
/* 80203098 001FFC78  7C 08 02 A6 */	mflr r0
/* 8020309C 001FFC7C  38 80 00 00 */	li r4, 0
/* 802030A0 001FFC80  90 01 00 04 */	stw r0, 4(r1)
/* 802030A4 001FFC84  38 A0 00 07 */	li r5, 7
/* 802030A8 001FFC88  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 802030AC 001FFC8C  93 E1 00 14 */	stw r31, 0x14(r1)
/* 802030B0 001FFC90  93 C1 00 10 */	stw r30, 0x10(r1)
/* 802030B4 001FFC94  7C 7E 1B 78 */	mr r30, r3
/* 802030B8 001FFC98  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 802030BC 001FFC9C  4B FC 53 15 */	bl func_801C83D0
/* 802030C0 001FFCA0  2C 03 00 00 */	cmpwi r3, 0
/* 802030C4 001FFCA4  40 82 00 1C */	bne lbl_802030E0
/* 802030C8 001FFCA8  38 7E 00 00 */	addi r3, r30, 0
/* 802030CC 001FFCAC  38 80 00 00 */	li r4, 0
/* 802030D0 001FFCB0  38 A0 00 07 */	li r5, 7
/* 802030D4 001FFCB4  4B FC 53 D1 */	bl func_801C84A4
/* 802030D8 001FFCB8  2C 03 00 00 */	cmpwi r3, 0
/* 802030DC 001FFCBC  41 82 00 AC */	beq lbl_80203188
lbl_802030E0:
/* 802030E0 001FFCC0  80 7F 00 C8 */	lwz r3, 0xc8(r31)
/* 802030E4 001FFCC4  2C 03 00 00 */	cmpwi r3, 0
/* 802030E8 001FFCC8  40 82 00 98 */	bne lbl_80203180
/* 802030EC 001FFCCC  80 7F 00 C4 */	lwz r3, 0xc4(r31)
/* 802030F0 001FFCD0  38 03 00 01 */	addi r0, r3, 1
/* 802030F4 001FFCD4  90 1F 00 C4 */	stw r0, 0xc4(r31)
/* 802030F8 001FFCD8  80 1F 00 C4 */	lwz r0, 0xc4(r31)
/* 802030FC 001FFCDC  2C 00 00 03 */	cmpwi r0, 3
/* 80203100 001FFCE0  40 81 00 0C */	ble lbl_8020310C
/* 80203104 001FFCE4  38 00 00 00 */	li r0, 0
/* 80203108 001FFCE8  90 1F 00 C4 */	stw r0, 0xc4(r31)
lbl_8020310C:
/* 8020310C 001FFCEC  80 1F 00 C4 */	lwz r0, 0xc4(r31)
/* 80203110 001FFCF0  2C 00 00 00 */	cmpwi r0, 0
/* 80203114 001FFCF4  40 82 00 2C */	bne lbl_80203140
/* 80203118 001FFCF8  80 6D B3 88 */	lwz r3, lbl_804D6A28@sda21(r13)
/* 8020311C 001FFCFC  80 63 00 08 */	lwz r3, 8(r3)
/* 80203120 001FFD00  2C 03 00 00 */	cmpwi r3, 0
/* 80203124 001FFD04  41 82 00 0C */	beq lbl_80203130
/* 80203128 001FFD08  48 17 D4 59 */	bl HSD_Randi
/* 8020312C 001FFD0C  48 00 00 08 */	b lbl_80203134
lbl_80203130:
/* 80203130 001FFD10  38 60 00 00 */	li r3, 0
lbl_80203134:
/* 80203134 001FFD14  38 03 00 01 */	addi r0, r3, 1
/* 80203138 001FFD18  90 1F 00 C8 */	stw r0, 0xc8(r31)
/* 8020313C 001FFD1C  48 00 00 30 */	b lbl_8020316C
lbl_80203140:
/* 80203140 001FFD20  2C 00 00 02 */	cmpwi r0, 2
/* 80203144 001FFD24  40 82 00 28 */	bne lbl_8020316C
/* 80203148 001FFD28  80 6D B3 88 */	lwz r3, lbl_804D6A28@sda21(r13)
/* 8020314C 001FFD2C  80 63 00 0C */	lwz r3, 0xc(r3)
/* 80203150 001FFD30  2C 03 00 00 */	cmpwi r3, 0
/* 80203154 001FFD34  41 82 00 0C */	beq lbl_80203160
/* 80203158 001FFD38  48 17 D4 29 */	bl HSD_Randi
/* 8020315C 001FFD3C  48 00 00 08 */	b lbl_80203164
lbl_80203160:
/* 80203160 001FFD40  38 60 00 00 */	li r3, 0
lbl_80203164:
/* 80203164 001FFD44  38 03 00 01 */	addi r0, r3, 1
/* 80203168 001FFD48  90 1F 00 C8 */	stw r0, 0xc8(r31)
lbl_8020316C:
/* 8020316C 001FFD4C  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 80203170 001FFD50  7F C3 F3 78 */	mr r3, r30
/* 80203174 001FFD54  80 BF 00 C4 */	lwz r5, 0xc4(r31)
/* 80203178 001FFD58  4B FC 4F C1 */	bl func_801C8138
/* 8020317C 001FFD5C  48 00 00 0C */	b lbl_80203188
lbl_80203180:
/* 80203180 001FFD60  38 03 FF FF */	addi r0, r3, -1
/* 80203184 001FFD64  90 1F 00 C8 */	stw r0, 0xc8(r31)
lbl_80203188:
/* 80203188 001FFD68  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8020318C 001FFD6C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80203190 001FFD70  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 80203194 001FFD74  38 21 00 18 */	addi r1, r1, 0x18
/* 80203198 001FFD78  7C 08 03 A6 */	mtlr r0
/* 8020319C 001FFD7C  4E 80 00 20 */	blr 
.global lbl_802031A0
lbl_802031A0:
/* 802031A0 001FFD80  4E 80 00 20 */	blr 
.global lbl_802031A4
lbl_802031A4:
/* 802031A4 001FFD84  7C 08 02 A6 */	mflr r0
/* 802031A8 001FFD88  38 80 00 08 */	li r4, 8
/* 802031AC 001FFD8C  90 01 00 04 */	stw r0, 4(r1)
/* 802031B0 001FFD90  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 802031B4 001FFD94  93 E1 00 14 */	stw r31, 0x14(r1)
/* 802031B8 001FFD98  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 802031BC 001FFD9C  4B FC 0D E9 */	bl func_801C3FA4
/* 802031C0 001FFDA0  3C 80 80 20 */	lis r4, lbl_80203498@ha
/* 802031C4 001FFDA4  38 E4 34 98 */	addi r7, r4, lbl_80203498@l
/* 802031C8 001FFDA8  38 C3 00 00 */	addi r6, r3, 0
/* 802031CC 001FFDAC  38 BF 00 00 */	addi r5, r31, 0
/* 802031D0 001FFDB0  38 60 00 00 */	li r3, 0
/* 802031D4 001FFDB4  38 80 00 00 */	li r4, 0
/* 802031D8 001FFDB8  39 00 00 00 */	li r8, 0
/* 802031DC 001FFDBC  39 20 00 00 */	li r9, 0
/* 802031E0 001FFDC0  4B FC 5B 1D */	bl func_801C8CFC
/* 802031E4 001FFDC4  90 7F 00 C4 */	stw r3, 0xc4(r31)
/* 802031E8 001FFDC8  80 6D B3 88 */	lwz r3, lbl_804D6A28@sda21(r13)
/* 802031EC 001FFDCC  80 63 00 14 */	lwz r3, 0x14(r3)
/* 802031F0 001FFDD0  2C 03 00 00 */	cmpwi r3, 0
/* 802031F4 001FFDD4  41 82 00 0C */	beq lbl_80203200
/* 802031F8 001FFDD8  48 17 D3 89 */	bl HSD_Randi
/* 802031FC 001FFDDC  48 00 00 08 */	b lbl_80203204
lbl_80203200:
/* 80203200 001FFDE0  38 60 00 00 */	li r3, 0
lbl_80203204:
/* 80203204 001FFDE4  80 AD B3 88 */	lwz r5, lbl_804D6A28@sda21(r13)
/* 80203208 001FFDE8  38 00 00 00 */	li r0, 0
/* 8020320C 001FFDEC  38 80 00 01 */	li r4, 1
/* 80203210 001FFDF0  80 A5 00 10 */	lwz r5, 0x10(r5)
/* 80203214 001FFDF4  7C 65 1A 14 */	add r3, r5, r3
/* 80203218 001FFDF8  90 7F 00 CC */	stw r3, 0xcc(r31)
/* 8020321C 001FFDFC  98 1F 00 C8 */	stb r0, 0xc8(r31)
/* 80203220 001FFE00  90 1F 00 08 */	stw r0, 8(r31)
/* 80203224 001FFE04  90 1F 00 0C */	stw r0, 0xc(r31)
/* 80203228 001FFE08  88 1F 00 11 */	lbz r0, 0x11(r31)
/* 8020322C 001FFE0C  50 80 2E 34 */	rlwimi r0, r4, 5, 0x18, 0x1a
/* 80203230 001FFE10  98 1F 00 11 */	stb r0, 0x11(r31)
/* 80203234 001FFE14  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80203238 001FFE18  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8020323C 001FFE1C  38 21 00 18 */	addi r1, r1, 0x18
/* 80203240 001FFE20  7C 08 03 A6 */	mtlr r0
/* 80203244 001FFE24  4E 80 00 20 */	blr 
.global lbl_80203248
lbl_80203248:
/* 80203248 001FFE28  38 60 00 00 */	li r3, 0
/* 8020324C 001FFE2C  4E 80 00 20 */	blr 
.global lbl_80203250
lbl_80203250:
/* 80203250 001FFE30  7C 08 02 A6 */	mflr r0
/* 80203254 001FFE34  38 80 00 00 */	li r4, 0
/* 80203258 001FFE38  90 01 00 04 */	stw r0, 4(r1)
/* 8020325C 001FFE3C  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 80203260 001FFE40  DB E1 00 30 */	stfd f31, 0x30(r1)
/* 80203264 001FFE44  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 80203268 001FFE48  93 C1 00 28 */	stw r30, 0x28(r1)
/* 8020326C 001FFE4C  93 A1 00 24 */	stw r29, 0x24(r1)
/* 80203270 001FFE50  7C 7D 1B 78 */	mr r29, r3
/* 80203274 001FFE54  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80203278 001FFE58  4B FC 0D 2D */	bl func_801C3FA4
/* 8020327C 001FFE5C  88 1F 00 C8 */	lbz r0, 0xc8(r31)
/* 80203280 001FFE60  3B C3 00 00 */	addi r30, r3, 0
/* 80203284 001FFE64  7C 00 07 74 */	extsb r0, r0
/* 80203288 001FFE68  2C 00 00 01 */	cmpwi r0, 1
/* 8020328C 001FFE6C  41 82 01 38 */	beq lbl_802033C4
/* 80203290 001FFE70  40 80 01 E4 */	bge lbl_80203474
/* 80203294 001FFE74  2C 00 00 00 */	cmpwi r0, 0
/* 80203298 001FFE78  40 80 00 08 */	bge lbl_802032A0
/* 8020329C 001FFE7C  48 00 01 D8 */	b lbl_80203474
lbl_802032A0:
/* 802032A0 001FFE80  80 7F 00 CC */	lwz r3, 0xcc(r31)
/* 802032A4 001FFE84  2C 03 00 00 */	cmpwi r3, 0
/* 802032A8 001FFE88  40 82 01 10 */	bne lbl_802033B8
/* 802032AC 001FFE8C  80 7F 00 C4 */	lwz r3, 0xc4(r31)
/* 802032B0 001FFE90  38 80 00 02 */	li r4, 2
/* 802032B4 001FFE94  38 A0 00 02 */	li r5, 2
/* 802032B8 001FFE98  48 06 5B A5 */	bl func_80268E5C
/* 802032BC 001FFE9C  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 802032C0 001FFEA0  38 7D 00 00 */	addi r3, r29, 0
/* 802032C4 001FFEA4  38 A0 00 00 */	li r5, 0
/* 802032C8 001FFEA8  4B FC 4E 71 */	bl func_801C8138
/* 802032CC 001FFEAC  80 6D B3 88 */	lwz r3, lbl_804D6A28@sda21(r13)
/* 802032D0 001FFEB0  C0 02 BD 38 */	lfs f0, lbl_804DB718@sda21(r2)
/* 802032D4 001FFEB4  C3 E3 00 18 */	lfs f31, 0x18(r3)
/* 802032D8 001FFEB8  C0 23 00 1C */	lfs f1, 0x1c(r3)
/* 802032DC 001FFEBC  EC 21 F8 28 */	fsubs f1, f1, f31
/* 802032E0 001FFEC0  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 802032E4 001FFEC4  40 80 00 08 */	bge lbl_802032EC
/* 802032E8 001FFEC8  FC 20 08 50 */	fneg f1, f1
lbl_802032EC:
/* 802032EC 001FFECC  FC 00 08 1E */	fctiwz f0, f1
/* 802032F0 001FFED0  D8 01 00 10 */	stfd f0, 0x10(r1)
/* 802032F4 001FFED4  80 01 00 14 */	lwz r0, 0x14(r1)
/* 802032F8 001FFED8  D8 01 00 18 */	stfd f0, 0x18(r1)
/* 802032FC 001FFEDC  2C 00 00 00 */	cmpwi r0, 0
/* 80203300 001FFEE0  80 61 00 1C */	lwz r3, 0x1c(r1)
/* 80203304 001FFEE4  41 82 00 0C */	beq lbl_80203310
/* 80203308 001FFEE8  48 17 D2 79 */	bl HSD_Randi
/* 8020330C 001FFEEC  48 00 00 08 */	b lbl_80203314
lbl_80203310:
/* 80203310 001FFEF0  38 60 00 00 */	li r3, 0
lbl_80203314:
/* 80203314 001FFEF4  6C 60 80 00 */	xoris r0, r3, 0x8000
/* 80203318 001FFEF8  C8 22 BD 40 */	lfd f1, lbl_804DB720@sda21(r2)
/* 8020331C 001FFEFC  90 01 00 14 */	stw r0, 0x14(r1)
/* 80203320 001FFF00  3C 00 43 30 */	lis r0, 0x4330
/* 80203324 001FFF04  28 1E 00 00 */	cmplwi r30, 0
/* 80203328 001FFF08  90 01 00 10 */	stw r0, 0x10(r1)
/* 8020332C 001FFF0C  C8 01 00 10 */	lfd f0, 0x10(r1)
/* 80203330 001FFF10  EC 00 08 28 */	fsubs f0, f0, f1
/* 80203334 001FFF14  EF FF 00 2A */	fadds f31, f31, f0
/* 80203338 001FFF18  40 82 00 14 */	bne lbl_8020334C
/* 8020333C 001FFF1C  38 6D 91 08 */	addi r3, r13, lbl_804D47A8@sda21
/* 80203340 001FFF20  38 80 03 A4 */	li r4, 0x3a4
/* 80203344 001FFF24  38 AD 91 10 */	addi r5, r13, lbl_804D47B0@sda21
/* 80203348 001FFF28  48 18 4E D9 */	bl __assert
lbl_8020334C:
/* 8020334C 001FFF2C  D3 FE 00 38 */	stfs f31, 0x38(r30)
/* 80203350 001FFF30  80 1E 00 14 */	lwz r0, 0x14(r30)
/* 80203354 001FFF34  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 80203358 001FFF38  40 82 00 4C */	bne lbl_802033A4
/* 8020335C 001FFF3C  28 1E 00 00 */	cmplwi r30, 0
/* 80203360 001FFF40  41 82 00 44 */	beq lbl_802033A4
/* 80203364 001FFF44  40 82 00 14 */	bne lbl_80203378
/* 80203368 001FFF48  38 6D 91 08 */	addi r3, r13, lbl_804D47A8@sda21
/* 8020336C 001FFF4C  38 80 02 34 */	li r4, 0x234
/* 80203370 001FFF50  38 AD 91 10 */	addi r5, r13, lbl_804D47B0@sda21
/* 80203374 001FFF54  48 18 4E AD */	bl __assert
lbl_80203378:
/* 80203378 001FFF58  80 9E 00 14 */	lwz r4, 0x14(r30)
/* 8020337C 001FFF5C  38 60 00 00 */	li r3, 0
/* 80203380 001FFF60  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 80203384 001FFF64  40 82 00 10 */	bne lbl_80203394
/* 80203388 001FFF68  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 8020338C 001FFF6C  41 82 00 08 */	beq lbl_80203394
/* 80203390 001FFF70  38 60 00 01 */	li r3, 1
lbl_80203394:
/* 80203394 001FFF74  2C 03 00 00 */	cmpwi r3, 0
/* 80203398 001FFF78  40 82 00 0C */	bne lbl_802033A4
/* 8020339C 001FFF7C  7F C3 F3 78 */	mr r3, r30
/* 802033A0 001FFF80  48 16 FF 49 */	bl HSD_JObjSetMtxDirtySub
lbl_802033A4:
/* 802033A4 001FFF84  38 00 00 00 */	li r0, 0
/* 802033A8 001FFF88  90 1F 00 CC */	stw r0, 0xcc(r31)
/* 802033AC 001FFF8C  38 00 00 01 */	li r0, 1
/* 802033B0 001FFF90  98 1F 00 C8 */	stb r0, 0xc8(r31)
/* 802033B4 001FFF94  48 00 00 C0 */	b lbl_80203474
lbl_802033B8:
/* 802033B8 001FFF98  38 03 FF FF */	addi r0, r3, -1
/* 802033BC 001FFF9C  90 1F 00 CC */	stw r0, 0xcc(r31)
/* 802033C0 001FFFA0  48 00 00 B4 */	b lbl_80203474
lbl_802033C4:
/* 802033C4 001FFFA4  80 1F 00 CC */	lwz r0, 0xcc(r31)
/* 802033C8 001FFFA8  2C 00 00 26 */	cmpwi r0, 0x26
/* 802033CC 001FFFAC  41 82 00 0C */	beq lbl_802033D8
/* 802033D0 001FFFB0  2C 00 00 94 */	cmpwi r0, 0x94
/* 802033D4 001FFFB4  40 82 00 14 */	bne lbl_802033E8
lbl_802033D8:
/* 802033D8 001FFFB8  3C 60 00 06 */	lis r3, 0x00064191@ha
/* 802033DC 001FFFBC  38 63 41 91 */	addi r3, r3, 0x00064191@l
/* 802033E0 001FFFC0  4B FC 20 0D */	bl func_801C53EC
/* 802033E4 001FFFC4  48 00 00 20 */	b lbl_80203404
lbl_802033E8:
/* 802033E8 001FFFC8  2C 00 00 6E */	cmpwi r0, 0x6e
/* 802033EC 001FFFCC  41 82 00 0C */	beq lbl_802033F8
/* 802033F0 001FFFD0  2C 00 00 D2 */	cmpwi r0, 0xd2
/* 802033F4 001FFFD4  40 82 00 10 */	bne lbl_80203404
lbl_802033F8:
/* 802033F8 001FFFD8  3C 60 00 06 */	lis r3, 0x00064192@ha
/* 802033FC 001FFFDC  38 63 41 92 */	addi r3, r3, 0x00064192@l
/* 80203400 001FFFE0  4B FC 1F ED */	bl func_801C53EC
lbl_80203404:
/* 80203404 001FFFE4  38 7D 00 00 */	addi r3, r29, 0
/* 80203408 001FFFE8  38 80 00 00 */	li r4, 0
/* 8020340C 001FFFEC  38 A0 00 07 */	li r5, 7
/* 80203410 001FFFF0  4B FC 4F C1 */	bl func_801C83D0
/* 80203414 001FFFF4  2C 03 00 00 */	cmpwi r3, 0
/* 80203418 001FFFF8  41 82 00 50 */	beq lbl_80203468
/* 8020341C 001FFFFC  80 7F 00 C4 */	lwz r3, 0xc4(r31)
/* 80203420 00200000  38 80 00 00 */	li r4, 0
/* 80203424 00200004  38 A0 00 02 */	li r5, 2
/* 80203428 00200008  48 06 5A 35 */	bl func_80268E5C
/* 8020342C 0020000C  7F C3 F3 78 */	mr r3, r30
/* 80203430 00200010  48 16 C2 85 */	bl func_8036F6B4
/* 80203434 00200014  80 6D B3 88 */	lwz r3, lbl_804D6A28@sda21(r13)
/* 80203438 00200018  80 63 00 14 */	lwz r3, 0x14(r3)
/* 8020343C 0020001C  2C 03 00 00 */	cmpwi r3, 0
/* 80203440 00200020  41 82 00 0C */	beq lbl_8020344C
/* 80203444 00200024  48 17 D1 3D */	bl HSD_Randi
/* 80203448 00200028  48 00 00 08 */	b lbl_80203450
lbl_8020344C:
/* 8020344C 0020002C  38 60 00 00 */	li r3, 0
lbl_80203450:
/* 80203450 00200030  80 8D B3 88 */	lwz r4, lbl_804D6A28@sda21(r13)
/* 80203454 00200034  38 00 00 00 */	li r0, 0
/* 80203458 00200038  80 84 00 10 */	lwz r4, 0x10(r4)
/* 8020345C 0020003C  7C 64 1A 14 */	add r3, r4, r3
/* 80203460 00200040  90 7F 00 CC */	stw r3, 0xcc(r31)
/* 80203464 00200044  98 1F 00 C8 */	stb r0, 0xc8(r31)
lbl_80203468:
/* 80203468 00200048  80 7F 00 CC */	lwz r3, 0xcc(r31)
/* 8020346C 0020004C  38 03 00 01 */	addi r0, r3, 1
/* 80203470 00200050  90 1F 00 CC */	stw r0, 0xcc(r31)
lbl_80203474:
/* 80203474 00200054  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 80203478 00200058  CB E1 00 30 */	lfd f31, 0x30(r1)
/* 8020347C 0020005C  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 80203480 00200060  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 80203484 00200064  83 A1 00 24 */	lwz r29, 0x24(r1)
/* 80203488 00200068  38 21 00 38 */	addi r1, r1, 0x38
/* 8020348C 0020006C  7C 08 03 A6 */	mtlr r0
/* 80203490 00200070  4E 80 00 20 */	blr 
.global lbl_80203494
lbl_80203494:
/* 80203494 00200074  4E 80 00 20 */	blr 
lbl_80203498:
/* 80203498 00200078  4E 80 00 20 */	blr 
lbl_8020349C:
/* 8020349C 0020007C  7C 08 02 A6 */	mflr r0
/* 802034A0 00200080  90 01 00 04 */	stw r0, 4(r1)
/* 802034A4 00200084  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 802034A8 00200088  DB E1 00 38 */	stfd f31, 0x38(r1)
/* 802034AC 0020008C  93 E1 00 34 */	stw r31, 0x34(r1)
/* 802034B0 00200090  3B E5 00 00 */	addi r31, r5, 0
/* 802034B4 00200094  93 C1 00 30 */	stw r30, 0x30(r1)
/* 802034B8 00200098  3B C4 00 00 */	addi r30, r4, 0
/* 802034BC 0020009C  38 81 00 20 */	addi r4, r1, 0x20
/* 802034C0 002000A0  80 6D B3 88 */	lwz r3, lbl_804D6A28@sda21(r13)
/* 802034C4 002000A4  C3 E3 00 00 */	lfs f31, 0(r3)
/* 802034C8 002000A8  38 7E 00 00 */	addi r3, r30, 0
/* 802034CC 002000AC  4B E8 31 79 */	bl func_80086644
/* 802034D0 002000B0  38 7E 00 00 */	addi r3, r30, 0
/* 802034D4 002000B4  38 81 00 14 */	addi r4, r1, 0x14
/* 802034D8 002000B8  4B E8 31 AD */	bl func_80086684
/* 802034DC 002000BC  C0 01 00 24 */	lfs f0, 0x24(r1)
/* 802034E0 002000C0  FC 00 F8 40 */	fcmpo cr0, f0, f31
/* 802034E4 002000C4  40 80 00 5C */	bge lbl_80203540
/* 802034E8 002000C8  C0 01 00 18 */	lfs f0, 0x18(r1)
/* 802034EC 002000CC  FC 00 F8 40 */	fcmpo cr0, f0, f31
/* 802034F0 002000D0  40 81 00 30 */	ble lbl_80203520
/* 802034F4 002000D4  7F C3 F3 78 */	mr r3, r30
/* 802034F8 002000D8  4B E8 36 89 */	bl func_80086B80
/* 802034FC 002000DC  C0 42 BD 48 */	lfs f2, lbl_804DB728@sda21(r2)
/* 80203500 002000E0  38 61 00 20 */	addi r3, r1, 0x20
/* 80203504 002000E4  C0 02 BD 4C */	lfs f0, lbl_804DB72C@sda21(r2)
/* 80203508 002000E8  EC 21 10 24 */	fdivs f1, f1, f2
/* 8020350C 002000EC  D0 01 00 24 */	stfs f0, 0x24(r1)
/* 80203510 002000F0  48 00 00 51 */	bl func_80203560
/* 80203514 002000F4  3C 60 00 06 */	lis r3, 0x00064190@ha
/* 80203518 002000F8  38 63 41 90 */	addi r3, r3, 0x00064190@l
/* 8020351C 002000FC  4B FC 1E D1 */	bl func_801C53EC
lbl_80203520:
/* 80203520 00200100  80 8D B3 88 */	lwz r4, lbl_804D6A28@sda21(r13)
/* 80203524 00200104  38 60 00 01 */	li r3, 1
/* 80203528 00200108  C0 04 00 04 */	lfs f0, 4(r4)
/* 8020352C 0020010C  D0 1F 00 00 */	stfs f0, 0(r31)
/* 80203530 00200110  C0 02 BD 38 */	lfs f0, lbl_804DB718@sda21(r2)
/* 80203534 00200114  D0 1F 00 04 */	stfs f0, 4(r31)
/* 80203538 00200118  D0 1F 00 08 */	stfs f0, 8(r31)
/* 8020353C 0020011C  48 00 00 08 */	b lbl_80203544
lbl_80203540:
/* 80203540 00200120  38 60 00 00 */	li r3, 0
lbl_80203544:
/* 80203544 00200124  80 01 00 44 */	lwz r0, 0x44(r1)
/* 80203548 00200128  CB E1 00 38 */	lfd f31, 0x38(r1)
/* 8020354C 0020012C  83 E1 00 34 */	lwz r31, 0x34(r1)
/* 80203550 00200130  83 C1 00 30 */	lwz r30, 0x30(r1)
/* 80203554 00200134  38 21 00 40 */	addi r1, r1, 0x40
/* 80203558 00200138  7C 08 03 A6 */	mtlr r0
/* 8020355C 0020013C  4E 80 00 20 */	blr 

.global func_80203560
func_80203560:
/* 80203560 00200140  7C 08 02 A6 */	mflr r0
/* 80203564 00200144  38 A3 00 00 */	addi r5, r3, 0
/* 80203568 00200148  90 01 00 04 */	stw r0, 4(r1)
/* 8020356C 0020014C  38 60 75 3A */	li r3, 0x753a
/* 80203570 00200150  38 80 00 1E */	li r4, 0x1e
/* 80203574 00200154  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80203578 00200158  DB E1 00 10 */	stfd f31, 0x10(r1)
/* 8020357C 0020015C  FF E0 08 90 */	fmr f31, f1
/* 80203580 00200160  4B FC 61 79 */	bl func_801C96F8
/* 80203584 00200164  28 03 00 00 */	cmplwi r3, 0
/* 80203588 00200168  41 82 00 2C */	beq lbl_802035B4
/* 8020358C 0020016C  80 63 00 54 */	lwz r3, 0x54(r3)
/* 80203590 00200170  C0 03 00 24 */	lfs f0, 0x24(r3)
/* 80203594 00200174  EC 00 07 F2 */	fmuls f0, f0, f31
/* 80203598 00200178  D0 03 00 24 */	stfs f0, 0x24(r3)
/* 8020359C 0020017C  C0 03 00 28 */	lfs f0, 0x28(r3)
/* 802035A0 00200180  EC 00 07 F2 */	fmuls f0, f0, f31
/* 802035A4 00200184  D0 03 00 28 */	stfs f0, 0x28(r3)
/* 802035A8 00200188  C0 03 00 2C */	lfs f0, 0x2c(r3)
/* 802035AC 0020018C  EC 00 07 F2 */	fmuls f0, f0, f31
/* 802035B0 00200190  D0 03 00 2C */	stfs f0, 0x2c(r3)
lbl_802035B4:
/* 802035B4 00200194  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 802035B8 00200198  CB E1 00 10 */	lfd f31, 0x10(r1)
/* 802035BC 0020019C  38 21 00 18 */	addi r1, r1, 0x18
/* 802035C0 002001A0  7C 08 03 A6 */	mtlr r0
/* 802035C4 002001A4  4E 80 00 20 */	blr 
.global lbl_802035C8
lbl_802035C8:
/* 802035C8 002001A8  38 60 00 00 */	li r3, 0
/* 802035CC 002001AC  4E 80 00 20 */	blr 
.global lbl_802035D0
lbl_802035D0:
/* 802035D0 002001B0  7C 08 02 A6 */	mflr r0
/* 802035D4 002001B4  38 80 00 00 */	li r4, 0
/* 802035D8 002001B8  90 01 00 04 */	stw r0, 4(r1)
/* 802035DC 002001BC  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 802035E0 002001C0  93 E1 00 24 */	stw r31, 0x24(r1)
/* 802035E4 002001C4  3B E3 00 00 */	addi r31, r3, 0
/* 802035E8 002001C8  38 65 00 00 */	addi r3, r5, 0
/* 802035EC 002001CC  38 A1 00 14 */	addi r5, r1, 0x14
/* 802035F0 002001D0  4B E0 7B DD */	bl func_8000B1CC
/* 802035F4 002001D4  C0 3F 00 04 */	lfs f1, 4(r31)
/* 802035F8 002001D8  C0 01 00 18 */	lfs f0, 0x18(r1)
/* 802035FC 002001DC  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80203600 002001E0  40 81 00 0C */	ble lbl_8020360C
/* 80203604 002001E4  38 60 00 01 */	li r3, 1
/* 80203608 002001E8  48 00 00 08 */	b lbl_80203610
lbl_8020360C:
/* 8020360C 002001EC  38 60 00 00 */	li r3, 0
lbl_80203610:
/* 80203610 002001F0  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 80203614 002001F4  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 80203618 002001F8  38 21 00 28 */	addi r1, r1, 0x28
/* 8020361C 002001FC  7C 08 03 A6 */	mtlr r0
/* 80203620 00200200  4E 80 00 20 */	blr 

.global func_80203624
func_80203624:
/* 80203624 00200204  C0 22 BD 50 */	lfs f1, lbl_804DB730@sda21(r2)
/* 80203628 00200208  4E 80 00 20 */	blr 


.section .data

.global lbl_803E5248
lbl_803E5248:
	.4byte lbl_80202D60
	.4byte lbl_80202D8C
	.4byte lbl_80202D94
	.4byte lbl_80202D98
    .4byte NULL
	.4byte lbl_80203004
	.4byte lbl_80203090
	.4byte lbl_80203098
	.4byte lbl_802031A0
    .4byte NULL
	.4byte lbl_80202DC8
	.4byte lbl_80202E40
	.4byte lbl_80202E48
	.4byte lbl_80202E68
    .4byte 0xC0000000
	.4byte lbl_802031A4
	.4byte lbl_80203248
	.4byte lbl_80203250
	.4byte lbl_80203494
    .4byte NULL
	.4byte lbl_80202E6C
	.4byte lbl_80202F34
	.4byte lbl_80202F3C
	.4byte lbl_80202F40
    .4byte NULL
	.4byte lbl_80202F44
	.4byte lbl_80202F94
	.4byte lbl_80202F9C
	.4byte lbl_80202FA0
    .4byte NULL
	.4byte lbl_80202FA4
	.4byte lbl_80202FF4
	.4byte lbl_80202FFC
	.4byte lbl_80203000
    .4byte NULL
.global lbl_803E52D4
lbl_803E52D4:
    .4byte 0x2F477247
    .4byte 0x642E6461
    .4byte 0x74000000
.global lbl_803E52E0
lbl_803E52E0:
    .4byte 0x00000005
    .4byte lbl_803E5248
    .4byte lbl_803E52D4
	.4byte lbl_80202B70
	.4byte lbl_80202B6C
	.4byte lbl_80202C24
	.4byte lbl_80202C4C
	.4byte lbl_80202C70
	.4byte lbl_802035C8
	.4byte lbl_802035D0
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
    .4byte 0x67726761
    .4byte 0x7264656E
    .4byte 0x2E630000
    .4byte NULL
