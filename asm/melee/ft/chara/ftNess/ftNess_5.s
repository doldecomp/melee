.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240
.global ftNess_ItemPKFireSpawn
ftNess_ItemPKFireSpawn:
/* 80116B70 00113750  7C 08 02 A6 */	mflr r0
/* 80116B74 00113754  90 01 00 04 */	stw r0, 4(r1)
/* 80116B78 00113758  94 21 FF B0 */	stwu r1, -0x50(r1)
/* 80116B7C 0011375C  DB E1 00 48 */	stfd f31, 0x48(r1)
/* 80116B80 00113760  DB C1 00 40 */	stfd f30, 0x40(r1)
/* 80116B84 00113764  93 E1 00 3C */	stw r31, 0x3c(r1)
/* 80116B88 00113768  93 C1 00 38 */	stw r30, 0x38(r1)
/* 80116B8C 0011376C  93 A1 00 34 */	stw r29, 0x34(r1)
/* 80116B90 00113770  7C 7D 1B 78 */	mr r29, r3
/* 80116B94 00113774  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80116B98 00113778  88 7F 22 10 */	lbz r3, 0x2210(r31)
/* 80116B9C 0011377C  83 DF 02 D4 */	lwz r30, 0x2d4(r31)
/* 80116BA0 00113780  54 60 CF FF */	rlwinm. r0, r3, 0x19, 0x1f, 0x1f
/* 80116BA4 00113784  41 82 00 18 */	beq lbl_80116BBC
/* 80116BA8 00113788  38 00 00 00 */	li r0, 0
/* 80116BAC 0011378C  50 03 3E 30 */	rlwimi r3, r0, 7, 0x18, 0x18
/* 80116BB0 00113790  98 7F 22 10 */	stb r3, 0x2210(r31)
/* 80116BB4 00113794  38 00 00 01 */	li r0, 1
/* 80116BB8 00113798  48 00 00 08 */	b lbl_80116BC0
lbl_80116BBC:
/* 80116BBC 0011379C  38 00 00 00 */	li r0, 0
lbl_80116BC0:
/* 80116BC0 001137A0  2C 00 00 00 */	cmpwi r0, 0
/* 80116BC4 001137A4  41 82 00 AC */	beq lbl_80116C70
/* 80116BC8 001137A8  80 7F 05 E8 */	lwz r3, 0x5e8(r31)
/* 80116BCC 001137AC  38 A1 00 20 */	addi r5, r1, 0x20
/* 80116BD0 001137B0  38 80 00 00 */	li r4, 0
/* 80116BD4 001137B4  80 63 02 A0 */	lwz r3, 0x2a0(r3)
/* 80116BD8 001137B8  4B EF 45 F5 */	bl lb_8000B1CC
/* 80116BDC 001137BC  C0 7E 00 30 */	lfs f3, 0x30(r30)
/* 80116BE0 001137C0  C0 5F 00 2C */	lfs f2, 0x2c(r31)
/* 80116BE4 001137C4  C0 21 00 20 */	lfs f1, 0x20(r1)
# SPLIT NO LATER THAN HERE
/* 80116BE8 001137C8  C0 02 9D 38 */	lfs f0, lbl_804D9718/*0.0f*/@sda21(r2)
/* 80116BEC 001137CC  EC 23 08 BA */	fmadds f1, f3, f2, f1
/* 80116BF0 001137D0  D0 21 00 20 */	stfs f1, 0x20(r1)
/* 80116BF4 001137D4  C0 41 00 24 */	lfs f2, 0x24(r1)
/* 80116BF8 001137D8  C0 3E 00 34 */	lfs f1, 0x34(r30)
/* 80116BFC 001137DC  EC 22 08 2A */	fadds f1, f2, f1
/* 80116C00 001137E0  D0 21 00 24 */	stfs f1, 0x24(r1)
/* 80116C04 001137E4  D0 01 00 28 */	stfs f0, 0x28(r1)
/* 80116C08 001137E8  80 1F 00 E0 */	lwz r0, 0xe0(r31)
/* 80116C0C 001137EC  2C 00 00 01 */	cmpwi r0, 1
/* 80116C10 001137F0  40 82 00 10 */	bne lbl_80116C20
/* 80116C14 001137F4  C3 FE 00 20 */	lfs f31, 0x20(r30)
/* 80116C18 001137F8  C3 DE 00 24 */	lfs f30, 0x24(r30)
/* 80116C1C 001137FC  48 00 00 0C */	b lbl_80116C28
lbl_80116C20:
/* 80116C20 00113800  C3 FE 00 28 */	lfs f31, 0x28(r30)
/* 80116C24 00113804  C3 DE 00 2C */	lfs f30, 0x2c(r30)
lbl_80116C28:
/* 80116C28 00113808  C0 02 9D 38 */	lfs f0, lbl_804D9718/*0.0f*/@sda21(r2)
/* 80116C2C 0011380C  FC 20 F8 90 */	fmr f1, f31
/* 80116C30 00113810  D0 01 00 1C */	stfs f0, 0x1c(r1)
/* 80116C34 00113814  48 20 F6 0D */	bl cosf
/* 80116C38 00113818  EC 5E 00 72 */	fmuls f2, f30, f1
/* 80116C3C 0011381C  C0 1F 00 2C */	lfs f0, 0x2c(r31)
/* 80116C40 00113820  FC 20 F8 90 */	fmr f1, f31
/* 80116C44 00113824  EC 00 00 B2 */	fmuls f0, f0, f2
/* 80116C48 00113828  D0 01 00 14 */	stfs f0, 0x14(r1)
/* 80116C4C 0011382C  48 20 F7 89 */	bl sinf
/* 80116C50 00113830  EC 1E 00 72 */	fmuls f0, f30, f1
/* 80116C54 00113834  38 7D 00 00 */	addi r3, r29, 0
/* 80116C58 00113838  38 81 00 20 */	addi r4, r1, 0x20
/* 80116C5C 0011383C  38 A1 00 14 */	addi r5, r1, 0x14
/* 80116C60 00113840  D0 01 00 18 */	stfs f0, 0x18(r1)
/* 80116C64 00113844  C0 3F 00 2C */	lfs f1, 0x2c(r31)
/* 80116C68 00113848  EC 5F 00 72 */	fmuls f2, f31, f1
/* 80116C6C 0011384C  48 19 33 E9 */	bl func_802AA054
lbl_80116C70:
/* 80116C70 00113850  80 01 00 54 */	lwz r0, 0x54(r1)
/* 80116C74 00113854  CB E1 00 48 */	lfd f31, 0x48(r1)
/* 80116C78 00113858  CB C1 00 40 */	lfd f30, 0x40(r1)
/* 80116C7C 0011385C  83 E1 00 3C */	lwz r31, 0x3c(r1)
/* 80116C80 00113860  83 C1 00 38 */	lwz r30, 0x38(r1)
/* 80116C84 00113864  83 A1 00 34 */	lwz r29, 0x34(r1)
/* 80116C88 00113868  38 21 00 50 */	addi r1, r1, 0x50
/* 80116C8C 0011386C  7C 08 03 A6 */	mtlr r0
/* 80116C90 00113870  4E 80 00 20 */	blr

.global ftNess_SpecialS_StartMotion
ftNess_SpecialS_StartMotion:
/* 80116C94 00113874  7C 08 02 A6 */	mflr r0
/* 80116C98 00113878  38 80 01 64 */	li r4, 0x164
/* 80116C9C 0011387C  90 01 00 04 */	stw r0, 4(r1)
/* 80116CA0 00113880  38 00 00 00 */	li r0, 0
/* 80116CA4 00113884  38 A0 00 00 */	li r5, 0
/* 80116CA8 00113888  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80116CAC 0011388C  38 C0 00 00 */	li r6, 0
/* 80116CB0 00113890  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80116CB4 00113894  93 C1 00 10 */	stw r30, 0x10(r1)
/* 80116CB8 00113898  7C 7E 1B 78 */	mr r30, r3
/* 80116CBC 0011389C  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80116CC0 001138A0  90 1F 22 10 */	stw r0, 0x2210(r31)
/* 80116CC4 001138A4  90 1F 22 00 */	stw r0, 0x2200(r31)
/* 80116CC8 001138A8  C0 22 9D 38 */	lfs f1, lbl_804D9718/*0.0f*/@sda21(r2)
/* 80116CCC 001138AC  C0 42 9D 3C */	lfs f2, lbl_804D971C/*1.0f*/@sda21(r2)
/* 80116CD0 001138B0  FC 60 08 90 */	fmr f3, f1
/* 80116CD4 001138B4  4B F5 26 D9 */	bl Fighter_ChangeMotionState
/* 80116CD8 001138B8  7F C3 F3 78 */	mr r3, r30
/* 80116CDC 001138BC  4B F5 7E C9 */	bl ftAnim_8006EBA4
/* 80116CE0 001138C0  3C 60 80 11 */	lis r3, ftNess_ItemPKFireSpawn@ha
/* 80116CE4 001138C4  38 03 6B 70 */	addi r0, r3, ftNess_ItemPKFireSpawn@l
/* 80116CE8 001138C8  90 1F 21 BC */	stw r0, 0x21bc(r31)
/* 80116CEC 001138CC  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80116CF0 001138D0  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80116CF4 001138D4  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 80116CF8 001138D8  38 21 00 18 */	addi r1, r1, 0x18
/* 80116CFC 001138DC  7C 08 03 A6 */	mtlr r0
/* 80116D00 001138E0  4E 80 00 20 */	blr

.global ftNess_SpecialAirS_Action
ftNess_SpecialAirS_Action:
/* 80116D04 001138E4  7C 08 02 A6 */	mflr r0
/* 80116D08 001138E8  38 80 01 65 */	li r4, 0x165
/* 80116D0C 001138EC  90 01 00 04 */	stw r0, 4(r1)
/* 80116D10 001138F0  38 00 00 00 */	li r0, 0
/* 80116D14 001138F4  38 A0 00 00 */	li r5, 0
/* 80116D18 001138F8  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80116D1C 001138FC  38 C0 00 00 */	li r6, 0
/* 80116D20 00113900  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80116D24 00113904  93 C1 00 10 */	stw r30, 0x10(r1)
/* 80116D28 00113908  7C 7E 1B 78 */	mr r30, r3
/* 80116D2C 0011390C  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80116D30 00113910  90 1F 22 10 */	stw r0, 0x2210(r31)
/* 80116D34 00113914  90 1F 22 00 */	stw r0, 0x2200(r31)
/* 80116D38 00113918  C0 22 9D 38 */	lfs f1, lbl_804D9718/*0.0f*/@sda21(r2)
# SPLIT NO EARLIER THAN HERE
/* 80116D3C 0011391C  C0 42 9D 3C */	lfs f2, lbl_804D971C/*1.0f*/@sda21(r2)
/* 80116D40 00113920  FC 60 08 90 */	fmr f3, f1
/* 80116D44 00113924  4B F5 26 69 */	bl Fighter_ChangeMotionState
/* 80116D48 00113928  7F C3 F3 78 */	mr r3, r30
/* 80116D4C 0011392C  4B F5 7E 59 */	bl ftAnim_8006EBA4
/* 80116D50 00113930  3C 60 80 11 */	lis r3, ftNess_ItemPKFireSpawn@ha
/* 80116D54 00113934  38 03 6B 70 */	addi r0, r3, ftNess_ItemPKFireSpawn@l
/* 80116D58 00113938  90 1F 21 BC */	stw r0, 0x21bc(r31)
/* 80116D5C 0011393C  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80116D60 00113940  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80116D64 00113944  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 80116D68 00113948  38 21 00 18 */	addi r1, r1, 0x18
/* 80116D6C 0011394C  7C 08 03 A6 */	mtlr r0
/* 80116D70 00113950  4E 80 00 20 */	blr
.section .sdata2
    .balign 8
.global lbl_804D9718/*0.0f*/
lbl_804D9718/*0.0f*/:
    .4byte 0x00000000
.global lbl_804D971C/*1.0f*/
lbl_804D971C/*1.0f*/:
    .4byte 0x3F800000
