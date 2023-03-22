.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240

.global ftNess_SpecialAirHi_Coll
ftNess_SpecialAirHi_Coll:
/* 801198DC 001164BC  7C 08 02 A6 */	mflr r0
/* 801198E0 001164C0  90 01 00 04 */	stw r0, 4(r1)
/* 801198E4 001164C4  94 21 FF 18 */	stwu r1, -0xe8(r1)
/* 801198E8 001164C8  93 E1 00 E4 */	stw r31, 0xe4(r1)
/* 801198EC 001164CC  93 C1 00 E0 */	stw r30, 0xe0(r1)
/* 801198F0 001164D0  7C 7E 1B 78 */	mr r30, r3
/* 801198F4 001164D4  93 A1 00 DC */	stw r29, 0xdc(r1)
/* 801198F8 001164D8  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 801198FC 001164DC  83 BF 02 D4 */	lwz r29, 0x2d4(r31)
/* 80119900 001164E0  80 7F 23 74 */	lwz r3, 0x2374(r31)
/* 80119904 001164E4  80 1F 23 78 */	lwz r0, 0x2378(r31)
/* 80119908 001164E8  90 7F 00 80 */	stw r3, 0x80(r31)
/* 8011990C 001164EC  90 1F 00 84 */	stw r0, 0x84(r31)
/* 80119910 001164F0  80 1F 23 7C */	lwz r0, 0x237c(r31)
/* 80119914 001164F4  90 1F 00 88 */	stw r0, 0x88(r31)
/* 80119918 001164F8  C0 22 9D 80 */	lfs f1, lbl_804D9760/*1.0f*/@sda21(r2)
/* 8011991C 001164FC  C0 1F 00 2C */	lfs f0, 0x2c(r31)
/* 80119920 00116500  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 80119924 00116504  40 82 00 0C */	bne lbl_80119930
/* 80119928 00116508  38 80 00 01 */	li r4, 1
/* 8011992C 0011650C  48 00 00 08 */	b lbl_80119934
lbl_80119930:
/* 80119930 00116510  38 80 FF FF */	li r4, -1
lbl_80119934:
/* 80119934 00116514  7F C3 F3 78 */	mr r3, r30
/* 80119938 00116518  4B F6 89 6D */	bl EnvColl_CheckGroundAndLedge
/* 8011993C 0011651C  2C 03 00 00 */	cmpwi r3, 0
/* 80119940 00116520  41 82 00 B4 */	beq lbl_801199F4
/* 80119944 00116524  38 7F 08 44 */	addi r3, r31, 0x844
/* 80119948 00116528  38 9F 00 80 */	addi r4, r31, 0x80
/* 8011994C 0011652C  4B EF 3C D5 */	bl lbvector_Angle
/* 80119950 00116530  C0 42 9D 94 */	lfs f2, lbl_804D9774/*90.0f*/@sda21(r2)
/* 80119954 00116534  C0 1D 00 64 */	lfs f0, 0x64(r29)
/* 80119958 00116538  C0 62 9D 90 */	lfs f3, lbl_804D9770/*0.01745329238474369f*/@sda21(r2)
/* 8011995C 0011653C  EC 02 00 2A */	fadds f0, f2, f0
/* 80119960 00116540  EC 03 00 32 */	fmuls f0, f3, f0
/* 80119964 00116544  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80119968 00116548  40 81 00 5C */	ble lbl_801199C4
/* 8011996C 0011654C  C0 02 9D 54 */	lfs f0, lbl_804D9734/*0.0f*/@sda21(r2)
/* 80119970 00116550  D0 1F 00 88 */	stfs f0, 0x88(r31)
/* 80119974 00116554  D0 1F 00 84 */	stfs f0, 0x84(r31)
/* 80119978 00116558  D0 1F 00 80 */	stfs f0, 0x80(r31)
/* 8011997C 0011655C  83 BE 00 2C */	lwz r29, 0x2c(r30)
/* 80119980 00116560  80 1D 00 10 */	lwz r0, 0x10(r29)
/* 80119984 00116564  2C 00 01 6F */	cmpwi r0, 0x16f
/* 80119988 00116568  40 80 00 20 */	bge lbl_801199A8
/* 8011998C 0011656C  2C 00 01 66 */	cmpwi r0, 0x166
/* 80119990 00116570  40 80 00 08 */	bge lbl_80119998
/* 80119994 00116574  48 00 00 14 */	b lbl_801199A8
lbl_80119998:
/* 80119998 00116578  7F C3 F3 78 */	mr r3, r30
/* 8011999C 0011657C  4B F4 1E E5 */	bl efLib_DestroyAll
/* 801199A0 00116580  38 00 00 00 */	li r0, 0
/* 801199A4 00116584  90 1D 22 4C */	stw r0, 0x224c(r29)
lbl_801199A8:
/* 801199A8 00116588  C0 22 9D 54 */	lfs f1, lbl_804D9734/*0.0f*/@sda21(r2)
/* 801199AC 0011658C  38 7F 00 00 */	addi r3, r31, 0
/* 801199B0 00116590  38 80 00 00 */	li r4, 0
/* 801199B4 00116594  4B F5 BF 79 */	bl ftParts_8007592C
/* 801199B8 00116598  7F C3 F3 78 */	mr r3, r30
/* 801199BC 0011659C  4B F7 E3 85 */	bl func_80097D40
/* 801199C0 001165A0  48 00 03 7C */	b lbl_80119D3C
lbl_801199C4:
/* 801199C4 001165A4  7F E3 FB 78 */	mr r3, r31
/* 801199C8 001165A8  4B F6 3E 35 */	bl ftCommon_8007D7FC
/* 801199CC 001165AC  3C 80 0C 4C */	lis r4, 0x0C4C508A@ha
/* 801199D0 001165B0  C0 3F 08 94 */	lfs f1, 0x894(r31)
/* 801199D4 001165B4  C0 42 9D 80 */	lfs f2, lbl_804D9760/*1.0f*/@sda21(r2)
/* 801199D8 001165B8  7F C3 F3 78 */	mr r3, r30
/* 801199DC 001165BC  C0 62 9D 54 */	lfs f3, lbl_804D9734/*0.0f*/@sda21(r2)
/* 801199E0 001165C0  38 A4 50 8A */	addi r5, r4, 0x0C4C508A@l
/* 801199E4 001165C4  38 80 01 69 */	li r4, 0x169
/* 801199E8 001165C8  38 C0 00 00 */	li r6, 0
/* 801199EC 001165CC  4B F4 F9 C1 */	bl Fighter_ChangeMotionState
/* 801199F0 001165D0  48 00 03 4C */	b lbl_80119D3C
lbl_801199F4:
/* 801199F4 001165D4  7F C3 F3 78 */	mr r3, r30
/* 801199F8 001165D8  4B F6 78 A1 */	bl ftCliffCommon_80081298
/* 801199FC 001165DC  2C 03 00 00 */	cmpwi r3, 0
/* 80119A00 001165E0  41 82 00 10 */	beq lbl_80119A10
/* 80119A04 001165E4  7F C3 F3 78 */	mr r3, r30
/* 80119A08 001165E8  4B F6 79 69 */	bl ftCliffCommon_80081370
/* 80119A0C 001165EC  48 00 03 30 */	b lbl_80119D3C
lbl_80119A10:
/* 80119A10 001165F0  80 7F 08 24 */	lwz r3, 0x824(r31)
/* 80119A14 001165F4  54 60 04 65 */	rlwinm. r0, r3, 0, 0x11, 0x12
/* 80119A18 001165F8  41 82 01 00 */	beq lbl_80119B18
/* 80119A1C 001165FC  38 7F 08 80 */	addi r3, r31, 0x880
/* 80119A20 00116600  38 9F 00 80 */	addi r4, r31, 0x80
/* 80119A24 00116604  4B EF 3B FD */	bl lbvector_Angle
/* 80119A28 00116608  C0 42 9D 94 */	lfs f2, lbl_804D9774/*90.0f*/@sda21(r2)
/* 80119A2C 0011660C  C0 1D 00 64 */	lfs f0, 0x64(r29)
/* 80119A30 00116610  C0 62 9D 90 */	lfs f3, lbl_804D9770/*0.01745329238474369f*/@sda21(r2)
/* 80119A34 00116614  EC 02 00 2A */	fadds f0, f2, f0
/* 80119A38 00116618  EC 03 00 32 */	fmuls f0, f3, f0
/* 80119A3C 0011661C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80119A40 00116620  40 81 02 FC */	ble lbl_80119D3C
/* 80119A44 00116624  83 BE 00 2C */	lwz r29, 0x2c(r30)
/* 80119A48 00116628  38 9F 08 80 */	addi r4, r31, 0x880
/* 80119A4C 0011662C  38 7D 00 80 */	addi r3, r29, 0x80
/* 80119A50 00116630  4B EF 42 1D */	bl lbvector_Mirror
/* 80119A54 00116634  C0 22 9D 9C */	lfs f1, lbl_804D977C/*0.5f*/@sda21(r2)
/* 80119A58 00116638  C0 1D 00 80 */	lfs f0, 0x80(r29)
/* 80119A5C 0011663C  EC 00 00 72 */	fmuls f0, f0, f1
/* 80119A60 00116640  D0 1D 00 80 */	stfs f0, 0x80(r29)
/* 80119A64 00116644  C0 1D 00 84 */	lfs f0, 0x84(r29)
/* 80119A68 00116648  EC 00 00 72 */	fmuls f0, f0, f1
/* 80119A6C 0011664C  D0 1D 00 84 */	stfs f0, 0x84(r29)
/* 80119A70 00116650  C0 3D 00 80 */	lfs f1, 0x80(r29)
/* 80119A74 00116654  C0 1D 00 84 */	lfs f0, 0x84(r29)
/* 80119A78 00116658  EC 21 00 72 */	fmuls f1, f1, f1
/* 80119A7C 0011665C  EC 00 00 32 */	fmuls f0, f0, f0
/* 80119A80 00116660  EC 21 00 2A */	fadds f1, f1, f0
/* 80119A84 00116664  4B EF 47 19 */	bl lbvector_sqrtf_accurate
/* 80119A88 00116668  C0 3D 01 7C */	lfs f1, 0x17c(r29)
/* 80119A8C 0011666C  7F A3 EB 78 */	mr r3, r29
/* 80119A90 00116670  4B F6 39 B1 */	bl ftCommon_8007D440
/* 80119A94 00116674  C0 3D 00 80 */	lfs f1, 0x80(r29)
/* 80119A98 00116678  C0 02 9D 54 */	lfs f0, lbl_804D9734/*0.0f*/@sda21(r2)
/* 80119A9C 0011667C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80119AA0 00116680  4C 41 13 82 */	cror 2, 1, 2
/* 80119AA4 00116684  40 82 00 0C */	bne lbl_80119AB0
/* 80119AA8 00116688  C0 02 9D 80 */	lfs f0, lbl_804D9760/*1.0f*/@sda21(r2)
/* 80119AAC 0011668C  48 00 00 08 */	b lbl_80119AB4
lbl_80119AB0:
/* 80119AB0 00116690  C0 02 9D 98 */	lfs f0, lbl_804D9778/*-1.0f*/@sda21(r2)
lbl_80119AB4:
/* 80119AB4 00116694  D0 1D 00 2C */	stfs f0, 0x2c(r29)
/* 80119AB8 00116698  7F C3 F3 78 */	mr r3, r30
/* 80119ABC 0011669C  4B FF E0 B5 */	bl ftNess_SpecialHiStopGFX
/* 80119AC0 001166A0  C0 22 9D 54 */	lfs f1, lbl_804D9734/*0.0f*/@sda21(r2)
/* 80119AC4 001166A4  7F C3 F3 78 */	mr r3, r30
/* 80119AC8 001166A8  C0 42 9D 80 */	lfs f2, lbl_804D9760/*1.0f*/@sda21(r2)
/* 80119ACC 001166AC  38 80 01 6E */	li r4, 0x16e
/* 80119AD0 001166B0  FC 60 08 90 */	fmr f3, f1
/* 80119AD4 001166B4  38 A0 00 02 */	li r5, 2
/* 80119AD8 001166B8  38 C0 00 00 */	li r6, 0
/* 80119ADC 001166BC  4B F4 F8 D1 */	bl Fighter_ChangeMotionState
/* 80119AE0 001166C0  7F C3 F3 78 */	mr r3, r30
/* 80119AE4 001166C4  4B F5 50 C1 */	bl ftAnim_8006EBA4
/* 80119AE8 001166C8  C0 1F 08 80 */	lfs f0, 0x880(r31)
/* 80119AEC 001166CC  C0 5F 08 84 */	lfs f2, 0x884(r31)
/* 80119AF0 001166D0  FC 20 00 50 */	fneg f1, f0
/* 80119AF4 001166D4  4B F0 91 3D */	bl atan2f
/* 80119AF8 001166D8  D0 21 00 C4 */	stfs f1, 0xc4(r1)
/* 80119AFC 001166DC  38 9E 00 00 */	addi r4, r30, 0
/* 80119B00 001166E0  38 BD 00 B0 */	addi r5, r29, 0xb0
/* 80119B04 001166E4  4C C6 31 82 */	crclr 6
/* 80119B08 001166E8  38 C1 00 C4 */	addi r6, r1, 0xc4
/* 80119B0C 001166EC  38 60 04 06 */	li r3, 0x406
/* 80119B10 001166F0  4B F4 62 CD */	bl ef_Spawn
/* 80119B14 001166F4  48 00 02 28 */	b lbl_80119D3C
lbl_80119B18:
/* 80119B18 001166F8  54 60 06 BF */	clrlwi. r0, r3, 0x1a
/* 80119B1C 001166FC  41 82 01 10 */	beq lbl_80119C2C
/* 80119B20 00116700  38 7F 08 58 */	addi r3, r31, 0x858
/* 80119B24 00116704  38 9F 00 80 */	addi r4, r31, 0x80
/* 80119B28 00116708  4B EF 3A F9 */	bl lbvector_Angle
/* 80119B2C 0011670C  C0 42 9D 94 */	lfs f2, lbl_804D9774/*90.0f*/@sda21(r2)
/* 80119B30 00116710  C0 1D 00 64 */	lfs f0, 0x64(r29)
/* 80119B34 00116714  C0 62 9D 90 */	lfs f3, lbl_804D9770/*0.01745329238474369f*/@sda21(r2)
/* 80119B38 00116718  EC 02 00 2A */	fadds f0, f2, f0
/* 80119B3C 0011671C  EC 03 00 32 */	fmuls f0, f3, f0
/* 80119B40 00116720  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80119B44 00116724  40 81 00 D8 */	ble lbl_80119C1C
/* 80119B48 00116728  83 BE 00 2C */	lwz r29, 0x2c(r30)
/* 80119B4C 0011672C  38 9F 08 58 */	addi r4, r31, 0x858
/* 80119B50 00116730  38 7D 00 80 */	addi r3, r29, 0x80
/* 80119B54 00116734  4B EF 41 19 */	bl lbvector_Mirror
/* 80119B58 00116738  C0 22 9D 9C */	lfs f1, lbl_804D977C/*0.5f*/@sda21(r2)
/* 80119B5C 0011673C  C0 1D 00 80 */	lfs f0, 0x80(r29)
/* 80119B60 00116740  EC 00 00 72 */	fmuls f0, f0, f1
/* 80119B64 00116744  D0 1D 00 80 */	stfs f0, 0x80(r29)
/* 80119B68 00116748  C0 1D 00 84 */	lfs f0, 0x84(r29)
/* 80119B6C 0011674C  EC 00 00 72 */	fmuls f0, f0, f1
/* 80119B70 00116750  D0 1D 00 84 */	stfs f0, 0x84(r29)
/* 80119B74 00116754  C0 3D 00 80 */	lfs f1, 0x80(r29)
/* 80119B78 00116758  C0 1D 00 84 */	lfs f0, 0x84(r29)
/* 80119B7C 0011675C  EC 21 00 72 */	fmuls f1, f1, f1
/* 80119B80 00116760  EC 00 00 32 */	fmuls f0, f0, f0
/* 80119B84 00116764  EC 21 00 2A */	fadds f1, f1, f0
/* 80119B88 00116768  4B EF 46 15 */	bl lbvector_sqrtf_accurate
/* 80119B8C 0011676C  C0 3D 01 7C */	lfs f1, 0x17c(r29)
/* 80119B90 00116770  7F A3 EB 78 */	mr r3, r29
/* 80119B94 00116774  4B F6 38 AD */	bl ftCommon_8007D440
/* 80119B98 00116778  C0 3D 00 80 */	lfs f1, 0x80(r29)
/* 80119B9C 0011677C  C0 02 9D 54 */	lfs f0, lbl_804D9734/*0.0f*/@sda21(r2)
/* 80119BA0 00116780  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80119BA4 00116784  4C 41 13 82 */	cror 2, 1, 2
/* 80119BA8 00116788  40 82 00 0C */	bne lbl_80119BB4
/* 80119BAC 0011678C  C0 02 9D 80 */	lfs f0, lbl_804D9760/*1.0f*/@sda21(r2)
/* 80119BB0 00116790  48 00 00 08 */	b lbl_80119BB8
lbl_80119BB4:
/* 80119BB4 00116794  C0 02 9D 98 */	lfs f0, lbl_804D9778/*-1.0f*/@sda21(r2)
lbl_80119BB8:
/* 80119BB8 00116798  D0 1D 00 2C */	stfs f0, 0x2c(r29)
/* 80119BBC 0011679C  7F C3 F3 78 */	mr r3, r30
/* 80119BC0 001167A0  4B FF DF B1 */	bl ftNess_SpecialHiStopGFX
/* 80119BC4 001167A4  C0 22 9D 54 */	lfs f1, lbl_804D9734/*0.0f*/@sda21(r2)
/* 80119BC8 001167A8  7F C3 F3 78 */	mr r3, r30
/* 80119BCC 001167AC  C0 42 9D 80 */	lfs f2, lbl_804D9760/*1.0f*/@sda21(r2)
/* 80119BD0 001167B0  38 80 01 6E */	li r4, 0x16e
/* 80119BD4 001167B4  FC 60 08 90 */	fmr f3, f1
/* 80119BD8 001167B8  38 A0 00 02 */	li r5, 2
/* 80119BDC 001167BC  38 C0 00 00 */	li r6, 0
/* 80119BE0 001167C0  4B F4 F7 CD */	bl Fighter_ChangeMotionState
/* 80119BE4 001167C4  7F C3 F3 78 */	mr r3, r30
/* 80119BE8 001167C8  4B F5 4F BD */	bl ftAnim_8006EBA4
/* 80119BEC 001167CC  C0 1F 08 58 */	lfs f0, 0x858(r31)
/* 80119BF0 001167D0  C0 5F 08 5C */	lfs f2, 0x85c(r31)
/* 80119BF4 001167D4  FC 20 00 50 */	fneg f1, f0
/* 80119BF8 001167D8  4B F0 90 39 */	bl atan2f
/* 80119BFC 001167DC  D0 21 00 B8 */	stfs f1, 0xb8(r1)
/* 80119C00 001167E0  38 9E 00 00 */	addi r4, r30, 0
/* 80119C04 001167E4  38 BD 00 B0 */	addi r5, r29, 0xb0
/* 80119C08 001167E8  4C C6 31 82 */	crclr 6
/* 80119C0C 001167EC  38 C1 00 B8 */	addi r6, r1, 0xb8
/* 80119C10 001167F0  38 60 04 06 */	li r3, 0x406
/* 80119C14 001167F4  4B F4 61 C9 */	bl ef_Spawn
/* 80119C18 001167F8  48 00 01 24 */	b lbl_80119D3C
lbl_80119C1C:
/* 80119C1C 001167FC  38 7E 00 00 */	addi r3, r30, 0
/* 80119C20 00116800  38 9F 06 F0 */	addi r4, r31, 0x6f0
/* 80119C24 00116804  4B FF E3 01 */	bl ftNess_SpecialAirHi_CollisionModVel
/* 80119C28 00116808  48 00 01 14 */	b lbl_80119D3C
lbl_80119C2C:
/* 80119C2C 0011680C  54 60 05 33 */	rlwinm. r0, r3, 0, 0x14, 0x19
/* 80119C30 00116810  41 82 01 0C */	beq lbl_80119D3C
/* 80119C34 00116814  38 7F 08 6C */	addi r3, r31, 0x86c
/* 80119C38 00116818  38 9F 00 80 */	addi r4, r31, 0x80
/* 80119C3C 0011681C  4B EF 39 E5 */	bl lbvector_Angle
/* 80119C40 00116820  C0 42 9D 94 */	lfs f2, lbl_804D9774/*90.0f*/@sda21(r2)
/* 80119C44 00116824  C0 1D 00 64 */	lfs f0, 0x64(r29)
/* 80119C48 00116828  C0 62 9D 90 */	lfs f3, lbl_804D9770/*0.01745329238474369f*/@sda21(r2)
/* 80119C4C 0011682C  EC 02 00 2A */	fadds f0, f2, f0
/* 80119C50 00116830  EC 03 00 32 */	fmuls f0, f3, f0
/* 80119C54 00116834  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80119C58 00116838  40 81 00 D8 */	ble lbl_80119D30
/* 80119C5C 0011683C  83 BE 00 2C */	lwz r29, 0x2c(r30)
/* 80119C60 00116840  38 9F 08 6C */	addi r4, r31, 0x86c
/* 80119C64 00116844  38 7D 00 80 */	addi r3, r29, 0x80
/* 80119C68 00116848  4B EF 40 05 */	bl lbvector_Mirror
/* 80119C6C 0011684C  C0 22 9D 9C */	lfs f1, lbl_804D977C/*0.5f*/@sda21(r2)
/* 80119C70 00116850  C0 1D 00 80 */	lfs f0, 0x80(r29)
/* 80119C74 00116854  EC 00 00 72 */	fmuls f0, f0, f1
/* 80119C78 00116858  D0 1D 00 80 */	stfs f0, 0x80(r29)
/* 80119C7C 0011685C  C0 1D 00 84 */	lfs f0, 0x84(r29)
/* 80119C80 00116860  EC 00 00 72 */	fmuls f0, f0, f1
/* 80119C84 00116864  D0 1D 00 84 */	stfs f0, 0x84(r29)
/* 80119C88 00116868  C0 3D 00 80 */	lfs f1, 0x80(r29)
/* 80119C8C 0011686C  C0 1D 00 84 */	lfs f0, 0x84(r29)
/* 80119C90 00116870  EC 21 00 72 */	fmuls f1, f1, f1
/* 80119C94 00116874  EC 00 00 32 */	fmuls f0, f0, f0
/* 80119C98 00116878  EC 21 00 2A */	fadds f1, f1, f0
/* 80119C9C 0011687C  4B EF 45 01 */	bl lbvector_sqrtf_accurate
/* 80119CA0 00116880  C0 3D 01 7C */	lfs f1, 0x17c(r29)
/* 80119CA4 00116884  7F A3 EB 78 */	mr r3, r29
/* 80119CA8 00116888  4B F6 37 99 */	bl ftCommon_8007D440
/* 80119CAC 0011688C  C0 3D 00 80 */	lfs f1, 0x80(r29)
/* 80119CB0 00116890  C0 02 9D 54 */	lfs f0, lbl_804D9734/*0.0f*/@sda21(r2)
/* 80119CB4 00116894  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80119CB8 00116898  4C 41 13 82 */	cror 2, 1, 2
/* 80119CBC 0011689C  40 82 00 0C */	bne lbl_80119CC8
/* 80119CC0 001168A0  C0 02 9D 80 */	lfs f0, lbl_804D9760/*1.0f*/@sda21(r2)
/* 80119CC4 001168A4  48 00 00 08 */	b lbl_80119CCC
lbl_80119CC8:
/* 80119CC8 001168A8  C0 02 9D 98 */	lfs f0, lbl_804D9778/*-1.0f*/@sda21(r2)
lbl_80119CCC:
/* 80119CCC 001168AC  D0 1D 00 2C */	stfs f0, 0x2c(r29)
/* 80119CD0 001168B0  7F C3 F3 78 */	mr r3, r30
/* 80119CD4 001168B4  4B FF DE 9D */	bl ftNess_SpecialHiStopGFX
/* 80119CD8 001168B8  C0 22 9D 54 */	lfs f1, lbl_804D9734/*0.0f*/@sda21(r2)
/* 80119CDC 001168BC  7F C3 F3 78 */	mr r3, r30
/* 80119CE0 001168C0  C0 42 9D 80 */	lfs f2, lbl_804D9760/*1.0f*/@sda21(r2)
/* 80119CE4 001168C4  38 80 01 6E */	li r4, 0x16e
/* 80119CE8 001168C8  FC 60 08 90 */	fmr f3, f1
/* 80119CEC 001168CC  38 A0 00 02 */	li r5, 2
/* 80119CF0 001168D0  38 C0 00 00 */	li r6, 0
/* 80119CF4 001168D4  4B F4 F6 B9 */	bl Fighter_ChangeMotionState
/* 80119CF8 001168D8  7F C3 F3 78 */	mr r3, r30
/* 80119CFC 001168DC  4B F5 4E A9 */	bl ftAnim_8006EBA4
/* 80119D00 001168E0  C0 1F 08 6C */	lfs f0, 0x86c(r31)
/* 80119D04 001168E4  C0 5F 08 70 */	lfs f2, 0x870(r31)
/* 80119D08 001168E8  FC 20 00 50 */	fneg f1, f0
/* 80119D0C 001168EC  4B F0 8F 25 */	bl atan2f
/* 80119D10 001168F0  D0 21 00 AC */	stfs f1, 0xac(r1)
/* 80119D14 001168F4  38 9E 00 00 */	addi r4, r30, 0
/* 80119D18 001168F8  38 BD 00 B0 */	addi r5, r29, 0xb0
/* 80119D1C 001168FC  4C C6 31 82 */	crclr 6
/* 80119D20 00116900  38 C1 00 AC */	addi r6, r1, 0xac
/* 80119D24 00116904  38 60 04 06 */	li r3, 0x406
/* 80119D28 00116908  4B F4 60 B5 */	bl ef_Spawn
/* 80119D2C 0011690C  48 00 00 10 */	b lbl_80119D3C
lbl_80119D30:
/* 80119D30 00116910  38 7E 00 00 */	addi r3, r30, 0
/* 80119D34 00116914  38 9F 06 F0 */	addi r4, r31, 0x6f0
/* 80119D38 00116918  4B FF E1 ED */	bl ftNess_SpecialAirHi_CollisionModVel
lbl_80119D3C:
/* 80119D3C 0011691C  80 01 00 EC */	lwz r0, 0xec(r1)
/* 80119D40 00116920  83 E1 00 E4 */	lwz r31, 0xe4(r1)
/* 80119D44 00116924  83 C1 00 E0 */	lwz r30, 0xe0(r1)
/* 80119D48 00116928  83 A1 00 DC */	lwz r29, 0xdc(r1)
/* 80119D4C 0011692C  38 21 00 E8 */	addi r1, r1, 0xe8
/* 80119D50 00116930  7C 08 03 A6 */	mtlr r0
/* 80119D54 00116934  4E 80 00 20 */	blr
.global ftNess_SpecialAirHiRebound_Coll
ftNess_SpecialAirHiRebound_Coll:
/* 80119D58 00116938  7C 08 02 A6 */	mflr r0
/* 80119D5C 0011693C  38 80 00 00 */	li r4, 0
/* 80119D60 00116940  90 01 00 04 */	stw r0, 4(r1)
/* 80119D64 00116944  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 80119D68 00116948  93 E1 00 24 */	stw r31, 0x24(r1)
/* 80119D6C 0011694C  93 C1 00 20 */	stw r30, 0x20(r1)
/* 80119D70 00116950  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 80119D74 00116954  7C 7D 1B 78 */	mr r29, r3
/* 80119D78 00116958  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 80119D7C 0011695C  4B F6 85 29 */	bl EnvColl_CheckGroundAndLedge
/* 80119D80 00116960  2C 03 00 01 */	cmpwi r3, 1
/* 80119D84 00116964  40 82 00 5C */	bne lbl_80119DE0
/* 80119D88 00116968  C0 02 9D 54 */	lfs f0, lbl_804D9734/*0.0f*/@sda21(r2)
/* 80119D8C 0011696C  D0 1E 00 88 */	stfs f0, 0x88(r30)
/* 80119D90 00116970  D0 1E 00 84 */	stfs f0, 0x84(r30)
/* 80119D94 00116974  D0 1E 00 80 */	stfs f0, 0x80(r30)
/* 80119D98 00116978  83 FD 00 2C */	lwz r31, 0x2c(r29)
/* 80119D9C 0011697C  80 1F 00 10 */	lwz r0, 0x10(r31)
/* 80119DA0 00116980  2C 00 01 6F */	cmpwi r0, 0x16f
/* 80119DA4 00116984  40 80 00 20 */	bge lbl_80119DC4
/* 80119DA8 00116988  2C 00 01 66 */	cmpwi r0, 0x166
/* 80119DAC 0011698C  40 80 00 08 */	bge lbl_80119DB4
/* 80119DB0 00116990  48 00 00 14 */	b lbl_80119DC4
lbl_80119DB4:
/* 80119DB4 00116994  7F A3 EB 78 */	mr r3, r29
/* 80119DB8 00116998  4B F4 1A C9 */	bl efLib_DestroyAll
/* 80119DBC 0011699C  38 00 00 00 */	li r0, 0
/* 80119DC0 001169A0  90 1F 22 4C */	stw r0, 0x224c(r31)
lbl_80119DC4:
/* 80119DC4 001169A4  C0 22 9D 54 */	lfs f1, lbl_804D9734/*0.0f*/@sda21(r2)
# SPLIT NO EARLIER THAN HERE
/* 80119DC8 001169A8  38 7E 00 00 */	addi r3, r30, 0
/* 80119DCC 001169AC  38 80 00 00 */	li r4, 0
/* 80119DD0 001169B0  4B F5 BB 5D */	bl ftParts_8007592C
/* 80119DD4 001169B4  7F A3 EB 78 */	mr r3, r29
/* 80119DD8 001169B8  4B F7 DF 69 */	bl func_80097D40
/* 80119DDC 001169BC  48 00 00 1C */	b lbl_80119DF8
lbl_80119DE0:
/* 80119DE0 001169C0  7F A3 EB 78 */	mr r3, r29
/* 80119DE4 001169C4  4B F6 74 B5 */	bl ftCliffCommon_80081298
/* 80119DE8 001169C8  2C 03 00 00 */	cmpwi r3, 0
/* 80119DEC 001169CC  41 82 00 0C */	beq lbl_80119DF8
/* 80119DF0 001169D0  7F A3 EB 78 */	mr r3, r29
/* 80119DF4 001169D4  4B F6 75 7D */	bl ftCliffCommon_80081370
lbl_80119DF8:
/* 80119DF8 001169D8  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 80119DFC 001169DC  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 80119E00 001169E0  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 80119E04 001169E4  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 80119E08 001169E8  38 21 00 28 */	addi r1, r1, 0x28
/* 80119E0C 001169EC  7C 08 03 A6 */	mtlr r0
/* 80119E10 001169F0  4E 80 00 20 */	blr

.section .sdata2
    .balign 8
.global lbl_804D9730/*5.0f*/
lbl_804D9730/*5.0f*/:
    .4byte 0x40A00000
.global lbl_804D9734/*0.0f*/
lbl_804D9734/*0.0f*/:
    .4byte 0x00000000
.global lbl_804D9738/*8.333333015441895f*/
lbl_804D9738/*8.333333015441895f*/:
    .4byte 0x41055555
.global lbl_804D973C/*12.333333015441895f*/
lbl_804D973C/*12.333333015441895f*/:
    .4byte 0x41455555
.global lbl_804D9740/*1.5707963705062866f*/
lbl_804D9740/*1.5707963705062866f*/:
    .4byte 0x3FC90FDB
    .4byte 0x00000000
.global lbl_804D9748/*6.283185307179586*/
lbl_804D9748/*6.283185307179586*/:
    .4byte 0x401921FB
    .4byte 0x54442D18
.global lbl_804D9750/*3.141592653589793*/
lbl_804D9750/*3.141592653589793*/:
    .4byte 0x400921FB
    .4byte 0x54442D18
.global lbl_804D9758/*1.5707963267948966*/
lbl_804D9758/*1.5707963267948966*/:
    .4byte 0x3FF921FB
    .4byte 0x54442D18
.global lbl_804D9760/*1.0f*/
lbl_804D9760/*1.0f*/:
    .4byte 0x3F800000
    .4byte 0x00000000
.global lbl_804D9768/*0.0*/
lbl_804D9768/*0.0*/:
    .4byte 0x00000000
    .4byte 0x00000000
.global lbl_804D9770/*0.01745329238474369f*/
lbl_804D9770/*0.01745329238474369f*/:
    .4byte 0x3C8EFA35
.global lbl_804D9774/*90.0f*/
lbl_804D9774/*90.0f*/:
    .4byte 0x42B40000
.global lbl_804D9778/*-1.0f*/
lbl_804D9778/*-1.0f*/:
    .4byte 0xBF800000
.global lbl_804D977C/*0.5f*/
lbl_804D977C/*0.5f*/:
    .4byte 0x3F000000
.global lbl_804D9780/*0.5*/
lbl_804D9780/*0.5*/:
    .4byte 0x3FE00000
    .4byte 0x00000000
.global lbl_804D9788/*3.0*/
lbl_804D9788/*3.0*/:
    .4byte 0x40080000
    .4byte 0x00000000
.global lbl_804D9790/*9.999999747378752e-05f*/
lbl_804D9790/*9.999999747378752e-05f*/:
    .4byte 0x38D1B717
.global lbl_804D9794/*-9.999999747378752e-05f*/
lbl_804D9794/*-9.999999747378752e-05f*/:
    .4byte 0xB8D1B717
.global lbl_804D9798/*-1.5707963267948966*/
lbl_804D9798/*-1.5707963267948966*/:
    .4byte 0xBFF921FB
    .4byte 0x54442D18
