.include "macros.inc"

.section .text

.global func_802F6948
func_802F6948:
/* 802F6948 002F3528  7C 08 02 A6 */	mflr r0
/* 802F694C 002F352C  90 01 00 04 */	stw r0, 4(r1)
/* 802F6950 002F3530  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 802F6954 002F3534  93 E1 00 14 */	stw r31, 0x14(r1)
/* 802F6958 002F3538  7C 7F 1B 78 */	mr r31, r3
/* 802F695C 002F353C  4B E7 44 F5 */	bl func_8016AE50
/* 802F6960 002F3540  1C BF 00 64 */	mulli r5, r31, 0x64
/* 802F6964 002F3544  3C 80 80 4A */	lis r4, lbl_804A10C8@ha
/* 802F6968 002F3548  38 04 10 C8 */	addi r0, r4, lbl_804A10C8@l
/* 802F696C 002F354C  7C C0 2A 14 */	add r6, r0, r5
/* 802F6970 002F3550  38 E6 00 10 */	addi r7, r6, 0x10
/* 802F6974 002F3554  88 A6 00 10 */	lbz r5, 0x10(r6)
/* 802F6978 002F3558  54 A0 CF FE */	rlwinm r0, r5, 0x19, 0x1f, 0x1f
/* 802F697C 002F355C  28 00 00 01 */	cmplwi r0, 1
/* 802F6980 002F3560  41 82 00 2C */	beq lbl_802F69AC
/* 802F6984 002F3564  38 80 00 01 */	li r4, 1
/* 802F6988 002F3568  50 85 3E 30 */	rlwimi r5, r4, 7, 0x18, 0x18
/* 802F698C 002F356C  98 A7 00 00 */	stb r5, 0(r7)
/* 802F6990 002F3570  88 07 00 00 */	lbz r0, 0(r7)
/* 802F6994 002F3574  50 80 36 72 */	rlwimi r0, r4, 6, 0x19, 0x19
/* 802F6998 002F3578  98 07 00 00 */	stb r0, 0(r7)
/* 802F699C 002F357C  88 03 00 02 */	lbz r0, 2(r3)
/* 802F69A0 002F3580  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 802F69A4 002F3584  41 82 00 08 */	beq lbl_802F69AC
/* 802F69A8 002F3588  98 86 00 09 */	stb r4, 9(r6)
lbl_802F69AC:
/* 802F69AC 002F358C  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 802F69B0 002F3590  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 802F69B4 002F3594  38 21 00 18 */	addi r1, r1, 0x18
/* 802F69B8 002F3598  7C 08 03 A6 */	mtlr r0
/* 802F69BC 002F359C  4E 80 00 20 */	blr 

.global func_802F69C0
func_802F69C0:
/* 802F69C0 002F35A0  7C 08 02 A6 */	mflr r0
/* 802F69C4 002F35A4  90 01 00 04 */	stw r0, 4(r1)
/* 802F69C8 002F35A8  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 802F69CC 002F35AC  93 E1 00 14 */	stw r31, 0x14(r1)
/* 802F69D0 002F35B0  3B E3 00 00 */	addi r31, r3, 0
/* 802F69D4 002F35B4  93 C1 00 10 */	stw r30, 0x10(r1)
/* 802F69D8 002F35B8  3B C4 00 00 */	addi r30, r4, 0
/* 802F69DC 002F35BC  4B E7 44 5D */	bl func_8016AE38
/* 802F69E0 002F35C0  88 03 24 C8 */	lbz r0, 0x24c8(r3)
/* 802F69E4 002F35C4  54 00 DF 7E */	rlwinm r0, r0, 0x1b, 0x1d, 0x1f
/* 802F69E8 002F35C8  28 00 00 01 */	cmplwi r0, 1
/* 802F69EC 002F35CC  41 82 00 18 */	beq lbl_802F6A04
/* 802F69F0 002F35D0  88 03 24 CA */	lbz r0, 0x24ca(r3)
/* 802F69F4 002F35D4  54 00 F7 FF */	rlwinm. r0, r0, 0x1e, 0x1f, 0x1f
/* 802F69F8 002F35D8  41 82 00 0C */	beq lbl_802F6A04
/* 802F69FC 002F35DC  7F C3 F3 78 */	mr r3, r30
/* 802F6A00 002F35E0  48 00 12 31 */	bl func_802F7C30
lbl_802F6A04:
/* 802F6A04 002F35E4  4B E7 44 35 */	bl func_8016AE38
/* 802F6A08 002F35E8  7C 7E 1B 78 */	mr r30, r3
/* 802F6A0C 002F35EC  9B E3 00 0D */	stb r31, 0xd(r3)
/* 802F6A10 002F35F0  4B E7 44 41 */	bl func_8016AE50
/* 802F6A14 002F35F4  1C BF 00 64 */	mulli r5, r31, 0x64
/* 802F6A18 002F35F8  3C 80 80 4A */	lis r4, lbl_804A10C8@ha
/* 802F6A1C 002F35FC  38 04 10 C8 */	addi r0, r4, lbl_804A10C8@l
/* 802F6A20 002F3600  7C C0 2A 14 */	add r6, r0, r5
/* 802F6A24 002F3604  38 E6 00 10 */	addi r7, r6, 0x10
/* 802F6A28 002F3608  88 A6 00 10 */	lbz r5, 0x10(r6)
/* 802F6A2C 002F360C  54 A0 CF FE */	rlwinm r0, r5, 0x19, 0x1f, 0x1f
/* 802F6A30 002F3610  28 00 00 01 */	cmplwi r0, 1
/* 802F6A34 002F3614  41 82 00 2C */	beq lbl_802F6A60
/* 802F6A38 002F3618  38 80 00 01 */	li r4, 1
/* 802F6A3C 002F361C  50 85 3E 30 */	rlwimi r5, r4, 7, 0x18, 0x18
/* 802F6A40 002F3620  98 A7 00 00 */	stb r5, 0(r7)
/* 802F6A44 002F3624  88 07 00 00 */	lbz r0, 0(r7)
/* 802F6A48 002F3628  50 80 36 72 */	rlwimi r0, r4, 6, 0x19, 0x19
/* 802F6A4C 002F362C  98 07 00 00 */	stb r0, 0(r7)
/* 802F6A50 002F3630  88 03 00 02 */	lbz r0, 2(r3)
/* 802F6A54 002F3634  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 802F6A58 002F3638  41 82 00 08 */	beq lbl_802F6A60
/* 802F6A5C 002F363C  98 86 00 09 */	stb r4, 9(r6)
lbl_802F6A60:
/* 802F6A60 002F3640  88 1E 24 CA */	lbz r0, 0x24ca(r30)
/* 802F6A64 002F3644  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 802F6A68 002F3648  41 82 00 48 */	beq lbl_802F6AB0
/* 802F6A6C 002F364C  7F E3 FB 78 */	mr r3, r31
/* 802F6A70 002F3650  4B D3 B9 AD */	bl Player_GetPlayerSlotType
/* 802F6A74 002F3654  2C 03 00 00 */	cmpwi r3, 0
/* 802F6A78 002F3658  41 82 00 14 */	beq lbl_802F6A8C
/* 802F6A7C 002F365C  7F E3 FB 78 */	mr r3, r31
/* 802F6A80 002F3660  4B D3 B9 9D */	bl Player_GetPlayerSlotType
/* 802F6A84 002F3664  2C 03 00 01 */	cmpwi r3, 1
/* 802F6A88 002F3668  40 82 00 28 */	bne lbl_802F6AB0
lbl_802F6A8C:
/* 802F6A8C 002F366C  7F E3 FB 78 */	mr r3, r31
/* 802F6A90 002F3670  4B D3 D1 49 */	bl Player_GetStocks
/* 802F6A94 002F3674  2C 03 00 00 */	cmpwi r3, 0
/* 802F6A98 002F3678  40 82 00 18 */	bne lbl_802F6AB0
/* 802F6A9C 002F367C  7F E3 FB 78 */	mr r3, r31
/* 802F6AA0 002F3680  4B D3 B9 7D */	bl Player_GetPlayerSlotType
/* 802F6AA4 002F3684  54 64 06 3E */	clrlwi r4, r3, 0x18
/* 802F6AA8 002F3688  38 7F 00 00 */	addi r3, r31, 0
/* 802F6AAC 002F368C  4B E7 4E 29 */	bl func_8016B8D4
lbl_802F6AB0:
/* 802F6AB0 002F3690  88 1E 24 C8 */	lbz r0, 0x24c8(r30)
/* 802F6AB4 002F3694  54 00 DF 7E */	rlwinm r0, r0, 0x1b, 0x1d, 0x1f
/* 802F6AB8 002F3698  28 00 00 01 */	cmplwi r0, 1
/* 802F6ABC 002F369C  41 82 00 24 */	beq lbl_802F6AE0
/* 802F6AC0 002F36A0  88 1E 24 CA */	lbz r0, 0x24ca(r30)
/* 802F6AC4 002F36A4  54 00 F7 FF */	rlwinm. r0, r0, 0x1e, 0x1f, 0x1f
/* 802F6AC8 002F36A8  41 82 00 18 */	beq lbl_802F6AE0
/* 802F6ACC 002F36AC  3C 60 80 2F */	lis r3, func_802F7BB4@h
/* 802F6AD0 002F36B0  34 03 7B B4 */	addic. r0, r3, func_802F7BB4@l
/* 802F6AD4 002F36B4  41 82 00 0C */	beq lbl_802F6AE0
/* 802F6AD8 002F36B8  7F E3 FB 78 */	mr r3, r31
/* 802F6ADC 002F36BC  48 00 10 D9 */	bl func_802F7BB4
lbl_802F6AE0:
/* 802F6AE0 002F36C0  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 802F6AE4 002F36C4  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 802F6AE8 002F36C8  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 802F6AEC 002F36CC  38 21 00 18 */	addi r1, r1, 0x18
/* 802F6AF0 002F36D0  7C 08 03 A6 */	mtlr r0
/* 802F6AF4 002F36D4  4E 80 00 20 */	blr 

.global func_802F6AF8
func_802F6AF8:
/* 802F6AF8 002F36D8  7C 08 02 A6 */	mflr r0
/* 802F6AFC 002F36DC  90 01 00 04 */	stw r0, 4(r1)
/* 802F6B00 002F36E0  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 802F6B04 002F36E4  93 E1 00 14 */	stw r31, 0x14(r1)
/* 802F6B08 002F36E8  7C 7F 1B 78 */	mr r31, r3
/* 802F6B0C 002F36EC  93 C1 00 10 */	stw r30, 0x10(r1)
/* 802F6B10 002F36F0  4B E7 43 29 */	bl func_8016AE38
/* 802F6B14 002F36F4  7C 7E 1B 78 */	mr r30, r3
/* 802F6B18 002F36F8  9B E3 00 0D */	stb r31, 0xd(r3)
/* 802F6B1C 002F36FC  4B E7 43 35 */	bl func_8016AE50
/* 802F6B20 002F3700  1C BF 00 64 */	mulli r5, r31, 0x64
/* 802F6B24 002F3704  3C 80 80 4A */	lis r4, lbl_804A10C8@ha
/* 802F6B28 002F3708  38 04 10 C8 */	addi r0, r4, lbl_804A10C8@l
/* 802F6B2C 002F370C  7C C0 2A 14 */	add r6, r0, r5
/* 802F6B30 002F3710  38 E6 00 10 */	addi r7, r6, 0x10
/* 802F6B34 002F3714  88 A6 00 10 */	lbz r5, 0x10(r6)
/* 802F6B38 002F3718  54 A0 CF FE */	rlwinm r0, r5, 0x19, 0x1f, 0x1f
/* 802F6B3C 002F371C  28 00 00 01 */	cmplwi r0, 1
/* 802F6B40 002F3720  41 82 00 2C */	beq lbl_802F6B6C
/* 802F6B44 002F3724  38 80 00 01 */	li r4, 1
/* 802F6B48 002F3728  50 85 3E 30 */	rlwimi r5, r4, 7, 0x18, 0x18
/* 802F6B4C 002F372C  98 A7 00 00 */	stb r5, 0(r7)
/* 802F6B50 002F3730  88 07 00 00 */	lbz r0, 0(r7)
/* 802F6B54 002F3734  50 80 36 72 */	rlwimi r0, r4, 6, 0x19, 0x19
/* 802F6B58 002F3738  98 07 00 00 */	stb r0, 0(r7)
/* 802F6B5C 002F373C  88 03 00 02 */	lbz r0, 2(r3)
/* 802F6B60 002F3740  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 802F6B64 002F3744  41 82 00 08 */	beq lbl_802F6B6C
/* 802F6B68 002F3748  98 86 00 09 */	stb r4, 9(r6)
lbl_802F6B6C:
/* 802F6B6C 002F374C  88 1E 24 CA */	lbz r0, 0x24ca(r30)
/* 802F6B70 002F3750  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 802F6B74 002F3754  41 82 00 48 */	beq lbl_802F6BBC
/* 802F6B78 002F3758  7F E3 FB 78 */	mr r3, r31
/* 802F6B7C 002F375C  4B D3 B8 A1 */	bl Player_GetPlayerSlotType
/* 802F6B80 002F3760  2C 03 00 00 */	cmpwi r3, 0
/* 802F6B84 002F3764  41 82 00 14 */	beq lbl_802F6B98
/* 802F6B88 002F3768  7F E3 FB 78 */	mr r3, r31
/* 802F6B8C 002F376C  4B D3 B8 91 */	bl Player_GetPlayerSlotType
/* 802F6B90 002F3770  2C 03 00 01 */	cmpwi r3, 1
/* 802F6B94 002F3774  40 82 00 28 */	bne lbl_802F6BBC
lbl_802F6B98:
/* 802F6B98 002F3778  7F E3 FB 78 */	mr r3, r31
/* 802F6B9C 002F377C  4B D3 D0 3D */	bl Player_GetStocks
/* 802F6BA0 002F3780  2C 03 00 00 */	cmpwi r3, 0
/* 802F6BA4 002F3784  40 82 00 18 */	bne lbl_802F6BBC
/* 802F6BA8 002F3788  7F E3 FB 78 */	mr r3, r31
/* 802F6BAC 002F378C  4B D3 B8 71 */	bl Player_GetPlayerSlotType
/* 802F6BB0 002F3790  54 64 06 3E */	clrlwi r4, r3, 0x18
/* 802F6BB4 002F3794  38 7F 00 00 */	addi r3, r31, 0
/* 802F6BB8 002F3798  4B E7 4D 1D */	bl func_8016B8D4
lbl_802F6BBC:
/* 802F6BBC 002F379C  88 1E 24 C8 */	lbz r0, 0x24c8(r30)
/* 802F6BC0 002F37A0  54 00 DF 7E */	rlwinm r0, r0, 0x1b, 0x1d, 0x1f
/* 802F6BC4 002F37A4  28 00 00 01 */	cmplwi r0, 1
/* 802F6BC8 002F37A8  41 82 00 24 */	beq lbl_802F6BEC
/* 802F6BCC 002F37AC  88 1E 24 CA */	lbz r0, 0x24ca(r30)
/* 802F6BD0 002F37B0  54 00 F7 FF */	rlwinm. r0, r0, 0x1e, 0x1f, 0x1f
/* 802F6BD4 002F37B4  41 82 00 18 */	beq lbl_802F6BEC
/* 802F6BD8 002F37B8  3C 60 80 2F */	lis r3, func_802F7AF8@h
/* 802F6BDC 002F37BC  34 03 7A F8 */	addic. r0, r3, func_802F7AF8@l
/* 802F6BE0 002F37C0  41 82 00 0C */	beq lbl_802F6BEC
/* 802F6BE4 002F37C4  7F E3 FB 78 */	mr r3, r31
/* 802F6BE8 002F37C8  48 00 0F 11 */	bl func_802F7AF8
lbl_802F6BEC:
/* 802F6BEC 002F37CC  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 802F6BF0 002F37D0  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 802F6BF4 002F37D4  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 802F6BF8 002F37D8  38 21 00 18 */	addi r1, r1, 0x18
/* 802F6BFC 002F37DC  7C 08 03 A6 */	mtlr r0
/* 802F6C00 002F37E0  4E 80 00 20 */	blr 

.global func_802F6C04
func_802F6C04:
/* 802F6C04 002F37E4  7C 08 02 A6 */	mflr r0
/* 802F6C08 002F37E8  90 01 00 04 */	stw r0, 4(r1)
/* 802F6C0C 002F37EC  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 802F6C10 002F37F0  93 E1 00 14 */	stw r31, 0x14(r1)
/* 802F6C14 002F37F4  7C 7F 1B 78 */	mr r31, r3
/* 802F6C18 002F37F8  93 C1 00 10 */	stw r30, 0x10(r1)
/* 802F6C1C 002F37FC  4B E7 42 1D */	bl func_8016AE38
/* 802F6C20 002F3800  7C 7E 1B 78 */	mr r30, r3
/* 802F6C24 002F3804  9B E3 00 0D */	stb r31, 0xd(r3)
/* 802F6C28 002F3808  4B E7 42 29 */	bl func_8016AE50
/* 802F6C2C 002F380C  1C BF 00 64 */	mulli r5, r31, 0x64
/* 802F6C30 002F3810  3C 80 80 4A */	lis r4, lbl_804A10C8@ha
/* 802F6C34 002F3814  38 04 10 C8 */	addi r0, r4, lbl_804A10C8@l
/* 802F6C38 002F3818  7C C0 2A 14 */	add r6, r0, r5
/* 802F6C3C 002F381C  38 E6 00 10 */	addi r7, r6, 0x10
/* 802F6C40 002F3820  88 A6 00 10 */	lbz r5, 0x10(r6)
/* 802F6C44 002F3824  54 A0 CF FE */	rlwinm r0, r5, 0x19, 0x1f, 0x1f
/* 802F6C48 002F3828  28 00 00 01 */	cmplwi r0, 1
/* 802F6C4C 002F382C  41 82 00 2C */	beq lbl_802F6C78
/* 802F6C50 002F3830  38 80 00 01 */	li r4, 1
/* 802F6C54 002F3834  50 85 3E 30 */	rlwimi r5, r4, 7, 0x18, 0x18
/* 802F6C58 002F3838  98 A7 00 00 */	stb r5, 0(r7)
/* 802F6C5C 002F383C  88 07 00 00 */	lbz r0, 0(r7)
/* 802F6C60 002F3840  50 80 36 72 */	rlwimi r0, r4, 6, 0x19, 0x19
/* 802F6C64 002F3844  98 07 00 00 */	stb r0, 0(r7)
/* 802F6C68 002F3848  88 03 00 02 */	lbz r0, 2(r3)
/* 802F6C6C 002F384C  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 802F6C70 002F3850  41 82 00 08 */	beq lbl_802F6C78
/* 802F6C74 002F3854  98 86 00 09 */	stb r4, 9(r6)
lbl_802F6C78:
/* 802F6C78 002F3858  88 1E 24 CA */	lbz r0, 0x24ca(r30)
/* 802F6C7C 002F385C  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 802F6C80 002F3860  41 82 00 48 */	beq lbl_802F6CC8
/* 802F6C84 002F3864  7F E3 FB 78 */	mr r3, r31
/* 802F6C88 002F3868  4B D3 B7 95 */	bl Player_GetPlayerSlotType
/* 802F6C8C 002F386C  2C 03 00 00 */	cmpwi r3, 0
/* 802F6C90 002F3870  41 82 00 14 */	beq lbl_802F6CA4
/* 802F6C94 002F3874  7F E3 FB 78 */	mr r3, r31
/* 802F6C98 002F3878  4B D3 B7 85 */	bl Player_GetPlayerSlotType
/* 802F6C9C 002F387C  2C 03 00 01 */	cmpwi r3, 1
/* 802F6CA0 002F3880  40 82 00 28 */	bne lbl_802F6CC8
lbl_802F6CA4:
/* 802F6CA4 002F3884  7F E3 FB 78 */	mr r3, r31
/* 802F6CA8 002F3888  4B D3 CF 31 */	bl Player_GetStocks
/* 802F6CAC 002F388C  2C 03 00 00 */	cmpwi r3, 0
/* 802F6CB0 002F3890  40 82 00 18 */	bne lbl_802F6CC8
/* 802F6CB4 002F3894  7F E3 FB 78 */	mr r3, r31
/* 802F6CB8 002F3898  4B D3 B7 65 */	bl Player_GetPlayerSlotType
/* 802F6CBC 002F389C  54 64 06 3E */	clrlwi r4, r3, 0x18
/* 802F6CC0 002F38A0  38 7F 00 00 */	addi r3, r31, 0
/* 802F6CC4 002F38A4  4B E7 4C 11 */	bl func_8016B8D4
lbl_802F6CC8:
/* 802F6CC8 002F38A8  88 1E 24 C8 */	lbz r0, 0x24c8(r30)
/* 802F6CCC 002F38AC  54 00 DF 7E */	rlwinm r0, r0, 0x1b, 0x1d, 0x1f
/* 802F6CD0 002F38B0  28 00 00 01 */	cmplwi r0, 1
/* 802F6CD4 002F38B4  41 82 00 24 */	beq lbl_802F6CF8
/* 802F6CD8 002F38B8  88 1E 24 CA */	lbz r0, 0x24ca(r30)
/* 802F6CDC 002F38BC  54 00 F7 FF */	rlwinm. r0, r0, 0x1e, 0x1f, 0x1f
/* 802F6CE0 002F38C0  41 82 00 18 */	beq lbl_802F6CF8
/* 802F6CE4 002F38C4  3C 60 80 2F */	lis r3, func_802F7C30@h
/* 802F6CE8 002F38C8  34 03 7C 30 */	addic. r0, r3, func_802F7C30@l
/* 802F6CEC 002F38CC  41 82 00 0C */	beq lbl_802F6CF8
/* 802F6CF0 002F38D0  7F E3 FB 78 */	mr r3, r31
/* 802F6CF4 002F38D4  48 00 0F 3D */	bl func_802F7C30
lbl_802F6CF8:
/* 802F6CF8 002F38D8  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 802F6CFC 002F38DC  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 802F6D00 002F38E0  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 802F6D04 002F38E4  38 21 00 18 */	addi r1, r1, 0x18
/* 802F6D08 002F38E8  7C 08 03 A6 */	mtlr r0
/* 802F6D0C 002F38EC  4E 80 00 20 */	blr 

.global func_802F6D10
func_802F6D10:
/* 802F6D10 002F38F0  7C 08 02 A6 */	mflr r0
/* 802F6D14 002F38F4  90 01 00 04 */	stw r0, 4(r1)
/* 802F6D18 002F38F8  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 802F6D1C 002F38FC  93 E1 00 14 */	stw r31, 0x14(r1)
/* 802F6D20 002F3900  7C 7F 1B 78 */	mr r31, r3
/* 802F6D24 002F3904  93 C1 00 10 */	stw r30, 0x10(r1)
/* 802F6D28 002F3908  4B E7 41 11 */	bl func_8016AE38
/* 802F6D2C 002F390C  7C 7E 1B 78 */	mr r30, r3
/* 802F6D30 002F3910  9B E3 00 0D */	stb r31, 0xd(r3)
/* 802F6D34 002F3914  4B E7 41 1D */	bl func_8016AE50
/* 802F6D38 002F3918  1C BF 00 64 */	mulli r5, r31, 0x64
/* 802F6D3C 002F391C  3C 80 80 4A */	lis r4, lbl_804A10C8@ha
/* 802F6D40 002F3920  38 04 10 C8 */	addi r0, r4, lbl_804A10C8@l
/* 802F6D44 002F3924  7C C0 2A 14 */	add r6, r0, r5
/* 802F6D48 002F3928  38 E6 00 10 */	addi r7, r6, 0x10
/* 802F6D4C 002F392C  88 A6 00 10 */	lbz r5, 0x10(r6)
/* 802F6D50 002F3930  54 A0 CF FE */	rlwinm r0, r5, 0x19, 0x1f, 0x1f
/* 802F6D54 002F3934  28 00 00 01 */	cmplwi r0, 1
/* 802F6D58 002F3938  41 82 00 2C */	beq lbl_802F6D84
/* 802F6D5C 002F393C  38 80 00 01 */	li r4, 1
/* 802F6D60 002F3940  50 85 3E 30 */	rlwimi r5, r4, 7, 0x18, 0x18
/* 802F6D64 002F3944  98 A7 00 00 */	stb r5, 0(r7)
/* 802F6D68 002F3948  88 07 00 00 */	lbz r0, 0(r7)
/* 802F6D6C 002F394C  50 80 36 72 */	rlwimi r0, r4, 6, 0x19, 0x19
/* 802F6D70 002F3950  98 07 00 00 */	stb r0, 0(r7)
/* 802F6D74 002F3954  88 03 00 02 */	lbz r0, 2(r3)
/* 802F6D78 002F3958  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 802F6D7C 002F395C  41 82 00 08 */	beq lbl_802F6D84
/* 802F6D80 002F3960  98 86 00 09 */	stb r4, 9(r6)
lbl_802F6D84:
/* 802F6D84 002F3964  88 1E 24 CA */	lbz r0, 0x24ca(r30)
/* 802F6D88 002F3968  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 802F6D8C 002F396C  41 82 00 48 */	beq lbl_802F6DD4
/* 802F6D90 002F3970  7F E3 FB 78 */	mr r3, r31
/* 802F6D94 002F3974  4B D3 B6 89 */	bl Player_GetPlayerSlotType
/* 802F6D98 002F3978  2C 03 00 00 */	cmpwi r3, 0
/* 802F6D9C 002F397C  41 82 00 14 */	beq lbl_802F6DB0
/* 802F6DA0 002F3980  7F E3 FB 78 */	mr r3, r31
/* 802F6DA4 002F3984  4B D3 B6 79 */	bl Player_GetPlayerSlotType
/* 802F6DA8 002F3988  2C 03 00 01 */	cmpwi r3, 1
/* 802F6DAC 002F398C  40 82 00 28 */	bne lbl_802F6DD4
lbl_802F6DB0:
/* 802F6DB0 002F3990  7F E3 FB 78 */	mr r3, r31
/* 802F6DB4 002F3994  4B D3 CE 25 */	bl Player_GetStocks
/* 802F6DB8 002F3998  2C 03 00 00 */	cmpwi r3, 0
/* 802F6DBC 002F399C  40 82 00 18 */	bne lbl_802F6DD4
/* 802F6DC0 002F39A0  7F E3 FB 78 */	mr r3, r31
/* 802F6DC4 002F39A4  4B D3 B6 59 */	bl Player_GetPlayerSlotType
/* 802F6DC8 002F39A8  54 64 06 3E */	clrlwi r4, r3, 0x18
/* 802F6DCC 002F39AC  38 7F 00 00 */	addi r3, r31, 0
/* 802F6DD0 002F39B0  4B E7 4B 05 */	bl func_8016B8D4
lbl_802F6DD4:
/* 802F6DD4 002F39B4  88 1E 24 C8 */	lbz r0, 0x24c8(r30)
/* 802F6DD8 002F39B8  54 00 DF 7E */	rlwinm r0, r0, 0x1b, 0x1d, 0x1f
/* 802F6DDC 002F39BC  28 00 00 01 */	cmplwi r0, 1
/* 802F6DE0 002F39C0  41 82 00 24 */	beq lbl_802F6E04
/* 802F6DE4 002F39C4  88 1E 24 CA */	lbz r0, 0x24ca(r30)
/* 802F6DE8 002F39C8  54 00 F7 FF */	rlwinm. r0, r0, 0x1e, 0x1f, 0x1f
/* 802F6DEC 002F39CC  41 82 00 18 */	beq lbl_802F6E04
/* 802F6DF0 002F39D0  3C 60 80 2F */	lis r3, func_802F7D08@h
/* 802F6DF4 002F39D4  34 03 7D 08 */	addic. r0, r3, func_802F7D08@l
/* 802F6DF8 002F39D8  41 82 00 0C */	beq lbl_802F6E04
/* 802F6DFC 002F39DC  7F E3 FB 78 */	mr r3, r31
/* 802F6E00 002F39E0  48 00 0F 09 */	bl func_802F7D08
lbl_802F6E04:
/* 802F6E04 002F39E4  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 802F6E08 002F39E8  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 802F6E0C 002F39EC  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 802F6E10 002F39F0  38 21 00 18 */	addi r1, r1, 0x18
/* 802F6E14 002F39F4  7C 08 03 A6 */	mtlr r0
/* 802F6E18 002F39F8  4E 80 00 20 */	blr 

.global func_802F6E1C
func_802F6E1C:
/* 802F6E1C 002F39FC  7C 08 02 A6 */	mflr r0
/* 802F6E20 002F3A00  90 01 00 04 */	stw r0, 4(r1)
/* 802F6E24 002F3A04  94 21 FF F8 */	stwu r1, -8(r1)
/* 802F6E28 002F3A08  4B FF F6 E1 */	bl func_802F6508
/* 802F6E2C 002F3A0C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802F6E30 002F3A10  38 21 00 08 */	addi r1, r1, 8
/* 802F6E34 002F3A14  7C 08 03 A6 */	mtlr r0
/* 802F6E38 002F3A18  4E 80 00 20 */	blr 

.global func_802F6E3C
func_802F6E3C:
/* 802F6E3C 002F3A1C  7C 08 02 A6 */	mflr r0
/* 802F6E40 002F3A20  90 01 00 04 */	stw r0, 4(r1)
/* 802F6E44 002F3A24  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 802F6E48 002F3A28  93 E1 00 14 */	stw r31, 0x14(r1)
/* 802F6E4C 002F3A2C  93 C1 00 10 */	stw r30, 0x10(r1)
/* 802F6E50 002F3A30  3B C3 00 00 */	addi r30, r3, 0
/* 802F6E54 002F3A34  1C 9E 00 64 */	mulli r4, r30, 0x64
/* 802F6E58 002F3A38  3C 60 80 4A */	lis r3, lbl_804A10C8@ha
/* 802F6E5C 002F3A3C  38 03 10 C8 */	addi r0, r3, lbl_804A10C8@l
/* 802F6E60 002F3A40  7F E0 22 14 */	add r31, r0, r4
/* 802F6E64 002F3A44  80 7F 00 00 */	lwz r3, 0(r31)
/* 802F6E68 002F3A48  28 03 00 00 */	cmplwi r3, 0
/* 802F6E6C 002F3A4C  41 82 00 08 */	beq lbl_802F6E74
/* 802F6E70 002F3A50  48 09 9E 3D */	bl func_80390CAC
lbl_802F6E74:
/* 802F6E74 002F3A54  80 7F 00 04 */	lwz r3, 4(r31)
/* 802F6E78 002F3A58  28 03 00 00 */	cmplwi r3, 0
/* 802F6E7C 002F3A5C  41 82 00 08 */	beq lbl_802F6E84
/* 802F6E80 002F3A60  48 09 9E 2D */	bl func_80390CAC
lbl_802F6E84:
/* 802F6E84 002F3A64  7F C3 F3 78 */	mr r3, r30
/* 802F6E88 002F3A68  48 00 48 25 */	bl func_802FB6AC
/* 802F6E8C 002F3A6C  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 802F6E90 002F3A70  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 802F6E94 002F3A74  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 802F6E98 002F3A78  38 21 00 18 */	addi r1, r1, 0x18
/* 802F6E9C 002F3A7C  7C 08 03 A6 */	mtlr r0
/* 802F6EA0 002F3A80  4E 80 00 20 */	blr 

.global func_802F6EA4
func_802F6EA4:
/* 802F6EA4 002F3A84  7C 08 02 A6 */	mflr r0
/* 802F6EA8 002F3A88  2C 03 00 08 */	cmpwi r3, 8
/* 802F6EAC 002F3A8C  90 01 00 04 */	stw r0, 4(r1)
/* 802F6EB0 002F3A90  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 802F6EB4 002F3A94  BF 61 00 24 */	stmw r27, 0x24(r1)
/* 802F6EB8 002F3A98  3B A4 00 00 */	addi r29, r4, 0
/* 802F6EBC 002F3A9C  3B 85 00 00 */	addi r28, r5, 0
/* 802F6EC0 002F3AA0  3B C7 00 00 */	addi r30, r7, 0
/* 802F6EC4 002F3AA4  3B E8 00 00 */	addi r31, r8, 0
/* 802F6EC8 002F3AA8  40 82 00 68 */	bne lbl_802F6F30
/* 802F6ECC 002F3AAC  28 1E 00 00 */	cmplwi r30, 0
/* 802F6ED0 002F3AB0  41 82 00 14 */	beq lbl_802F6EE4
/* 802F6ED4 002F3AB4  39 9E 00 00 */	addi r12, r30, 0
/* 802F6ED8 002F3AB8  7D 88 03 A6 */	mtlr r12
/* 802F6EDC 002F3ABC  38 60 FF FF */	li r3, -1
/* 802F6EE0 002F3AC0  4E 80 00 21 */	blrl 
lbl_802F6EE4:
/* 802F6EE4 002F3AC4  28 1F 00 00 */	cmplwi r31, 0
/* 802F6EE8 002F3AC8  41 82 00 14 */	beq lbl_802F6EFC
/* 802F6EEC 002F3ACC  39 9F 00 00 */	addi r12, r31, 0
/* 802F6EF0 002F3AD0  7D 88 03 A6 */	mtlr r12
/* 802F6EF4 002F3AD4  38 60 FF FF */	li r3, -1
/* 802F6EF8 002F3AD8  4E 80 00 21 */	blrl 
lbl_802F6EFC:
/* 802F6EFC 002F3ADC  2C 1D 00 00 */	cmpwi r29, 0
/* 802F6F00 002F3AE0  41 80 00 14 */	blt lbl_802F6F14
/* 802F6F04 002F3AE4  38 7D 00 00 */	addi r3, r29, 0
/* 802F6F08 002F3AE8  38 80 00 7F */	li r4, 0x7f
/* 802F6F0C 002F3AEC  38 A0 00 40 */	li r5, 0x40
/* 802F6F10 002F3AF0  4B D2 C8 99 */	bl func_800237A8
lbl_802F6F14:
/* 802F6F14 002F3AF4  2C 1D 00 00 */	cmpwi r29, 0
/* 802F6F18 002F3AF8  41 80 01 08 */	blt lbl_802F7020
/* 802F6F1C 002F3AFC  38 7C 00 00 */	addi r3, r28, 0
/* 802F6F20 002F3B00  38 80 00 7F */	li r4, 0x7f
/* 802F6F24 002F3B04  38 A0 00 40 */	li r5, 0x40
/* 802F6F28 002F3B08  4B D2 C8 81 */	bl func_800237A8
/* 802F6F2C 002F3B0C  48 00 00 F4 */	b lbl_802F7020
lbl_802F6F30:
/* 802F6F30 002F3B10  1C 83 00 28 */	mulli r4, r3, 0x28
/* 802F6F34 002F3B14  3C 60 80 40 */	lis r3, lbl_803F9628@ha
/* 802F6F38 002F3B18  38 03 96 28 */	addi r0, r3, lbl_803F9628@l
/* 802F6F3C 002F3B1C  7F 60 22 14 */	add r27, r0, r4
/* 802F6F40 002F3B20  93 BB 00 20 */	stw r29, 0x20(r27)
/* 802F6F44 002F3B24  93 9B 00 24 */	stw r28, 0x24(r27)
/* 802F6F48 002F3B28  98 DB 00 11 */	stb r6, 0x11(r27)
/* 802F6F4C 002F3B2C  80 7B 00 00 */	lwz r3, 0(r27)
/* 802F6F50 002F3B30  28 03 00 00 */	cmplwi r3, 0
/* 802F6F54 002F3B34  41 82 00 08 */	beq lbl_802F6F5C
/* 802F6F58 002F3B38  48 09 92 D1 */	bl func_80390228
lbl_802F6F5C:
/* 802F6F5C 002F3B3C  38 60 00 0E */	li r3, 0xe
/* 802F6F60 002F3B40  38 80 00 0E */	li r4, 0xe
/* 802F6F64 002F3B44  38 A0 00 00 */	li r5, 0
/* 802F6F68 002F3B48  48 09 92 89 */	bl func_803901F0
/* 802F6F6C 002F3B4C  80 9B 00 14 */	lwz r4, 0x14(r27)
/* 802F6F70 002F3B50  7C 7D 1B 78 */	mr r29, r3
/* 802F6F74 002F3B54  80 64 00 00 */	lwz r3, 0(r4)
/* 802F6F78 002F3B58  48 07 9E CD */	bl HSD_JObjLoadJoint
/* 802F6F7C 002F3B5C  3B 83 00 00 */	addi r28, r3, 0
/* 802F6F80 002F3B60  3C 80 08 00 */	lis r4, 0x800
/* 802F6F84 002F3B64  4B D1 AC 95 */	bl func_80011C18
/* 802F6F88 002F3B68  88 8D C1 A9 */	lbz r4, lbl_804D7849@sda21(r13)
/* 802F6F8C 002F3B6C  38 7D 00 00 */	addi r3, r29, 0
/* 802F6F90 002F3B70  38 BC 00 00 */	addi r5, r28, 0
/* 802F6F94 002F3B74  48 09 9A DD */	bl func_80390A70
/* 802F6F98 002F3B78  3C 60 80 39 */	lis r3, func_80391070@ha
/* 802F6F9C 002F3B7C  38 83 10 70 */	addi r4, r3, func_80391070@l
/* 802F6FA0 002F3B80  38 7D 00 00 */	addi r3, r29, 0
/* 802F6FA4 002F3B84  38 A0 00 0B */	li r5, 0xb
/* 802F6FA8 002F3B88  38 C0 00 00 */	li r6, 0
/* 802F6FAC 002F3B8C  48 09 96 F1 */	bl GObj_SetupGXLink
/* 802F6FB0 002F3B90  80 9B 00 08 */	lwz r4, 8(r27)
/* 802F6FB4 002F3B94  28 04 00 00 */	cmplwi r4, 0
/* 802F6FB8 002F3B98  41 82 00 10 */	beq lbl_802F6FC8
/* 802F6FBC 002F3B9C  38 7D 00 00 */	addi r3, r29, 0
/* 802F6FC0 002F3BA0  38 A0 00 00 */	li r5, 0
/* 802F6FC4 002F3BA4  48 09 8D 91 */	bl func_8038FD54
lbl_802F6FC8:
/* 802F6FC8 002F3BA8  80 BB 00 14 */	lwz r5, 0x14(r27)
/* 802F6FCC 002F3BAC  38 7C 00 00 */	addi r3, r28, 0
/* 802F6FD0 002F3BB0  38 80 00 00 */	li r4, 0
/* 802F6FD4 002F3BB4  4B D1 51 15 */	bl func_8000C0E8
/* 802F6FD8 002F3BB8  7F 83 E3 78 */	mr r3, r28
/* 802F6FDC 002F3BBC  C0 22 E0 C8 */	lfs f1, lbl_804DDAA8@sda21(r2)
/* 802F6FE0 002F3BC0  48 07 88 DD */	bl HSD_JObjReqAnimAll
/* 802F6FE4 002F3BC4  7F 83 E3 78 */	mr r3, r28
/* 802F6FE8 002F3BC8  48 07 99 41 */	bl HSD_JObjAnimAll
/* 802F6FEC 002F3BCC  88 1B 00 12 */	lbz r0, 0x12(r27)
/* 802F6FF0 002F3BD0  38 60 00 00 */	li r3, 0
/* 802F6FF4 002F3BD4  50 60 3E 30 */	rlwimi r0, r3, 7, 0x18, 0x18
/* 802F6FF8 002F3BD8  98 1B 00 12 */	stb r0, 0x12(r27)
/* 802F6FFC 002F3BDC  88 1B 00 12 */	lbz r0, 0x12(r27)
/* 802F7000 002F3BE0  50 60 36 72 */	rlwimi r0, r3, 6, 0x19, 0x19
/* 802F7004 002F3BE4  98 1B 00 12 */	stb r0, 0x12(r27)
/* 802F7008 002F3BE8  88 1B 00 12 */	lbz r0, 0x12(r27)
/* 802F700C 002F3BEC  50 60 2E B4 */	rlwimi r0, r3, 5, 0x1a, 0x1a
/* 802F7010 002F3BF0  98 1B 00 12 */	stb r0, 0x12(r27)
/* 802F7014 002F3BF4  93 BB 00 00 */	stw r29, 0(r27)
/* 802F7018 002F3BF8  93 DB 00 18 */	stw r30, 0x18(r27)
/* 802F701C 002F3BFC  93 FB 00 1C */	stw r31, 0x1c(r27)
lbl_802F7020:
/* 802F7020 002F3C00  BB 61 00 24 */	lmw r27, 0x24(r1)
/* 802F7024 002F3C04  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 802F7028 002F3C08  38 21 00 38 */	addi r1, r1, 0x38
/* 802F702C 002F3C0C  7C 08 03 A6 */	mtlr r0
/* 802F7030 002F3C10  4E 80 00 20 */	blr 

.global func_802F7034
func_802F7034:
/* 802F7034 002F3C14  7C 08 02 A6 */	mflr r0
/* 802F7038 002F3C18  90 01 00 04 */	stw r0, 4(r1)
/* 802F703C 002F3C1C  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 802F7040 002F3C20  93 E1 00 14 */	stw r31, 0x14(r1)
/* 802F7044 002F3C24  7C 7F 1B 78 */	mr r31, r3
/* 802F7048 002F3C28  4B E7 3D F1 */	bl func_8016AE38
/* 802F704C 002F3C2C  80 83 00 10 */	lwz r4, 0x10(r3)
/* 802F7050 002F3C30  2C 04 00 00 */	cmpwi r4, 0
/* 802F7054 002F3C34  41 82 00 0C */	beq lbl_802F7060
/* 802F7058 002F3C38  38 84 FF FF */	addi r4, r4, -1
/* 802F705C 002F3C3C  48 00 00 08 */	b lbl_802F7064
lbl_802F7060:
/* 802F7060 002F3C40  38 80 FF FF */	li r4, -1
lbl_802F7064:
/* 802F7064 002F3C44  80 A3 00 14 */	lwz r5, 0x14(r3)
/* 802F7068 002F3C48  2C 05 00 00 */	cmpwi r5, 0
/* 802F706C 002F3C4C  41 82 00 0C */	beq lbl_802F7078
/* 802F7070 002F3C50  38 A5 FF FF */	addi r5, r5, -1
/* 802F7074 002F3C54  48 00 00 08 */	b lbl_802F707C
lbl_802F7078:
/* 802F7078 002F3C58  38 A0 FF FF */	li r5, -1
lbl_802F707C:
/* 802F707C 002F3C5C  88 03 00 18 */	lbz r0, 0x18(r3)
/* 802F7080 002F3C60  28 00 00 00 */	cmplwi r0, 0
/* 802F7084 002F3C64  41 82 00 0C */	beq lbl_802F7090
/* 802F7088 002F3C68  7C 06 03 78 */	mr r6, r0
/* 802F708C 002F3C6C  48 00 00 08 */	b lbl_802F7094
lbl_802F7090:
/* 802F7090 002F3C70  38 C0 00 00 */	li r6, 0
lbl_802F7094:
/* 802F7094 002F3C74  89 03 00 0B */	lbz r8, 0xb(r3)
/* 802F7098 002F3C78  28 08 00 00 */	cmplwi r8, 0
/* 802F709C 002F3C7C  41 82 00 18 */	beq lbl_802F70B4
/* 802F70A0 002F3C80  38 68 FF FF */	addi r3, r8, -1
/* 802F70A4 002F3C84  38 FF 00 00 */	addi r7, r31, 0
/* 802F70A8 002F3C88  39 00 00 00 */	li r8, 0
/* 802F70AC 002F3C8C  4B FF FD F9 */	bl func_802F6EA4
/* 802F70B0 002F3C90  48 00 00 70 */	b lbl_802F7120
lbl_802F70B4:
/* 802F70B4 002F3C94  88 E3 00 08 */	lbz r7, 8(r3)
/* 802F70B8 002F3C98  28 07 00 01 */	cmplwi r7, 1
/* 802F70BC 002F3C9C  40 82 00 18 */	bne lbl_802F70D4
/* 802F70C0 002F3CA0  38 FF 00 00 */	addi r7, r31, 0
/* 802F70C4 002F3CA4  38 60 00 00 */	li r3, 0
/* 802F70C8 002F3CA8  39 00 00 00 */	li r8, 0
/* 802F70CC 002F3CAC  4B FF FD D9 */	bl func_802F6EA4
/* 802F70D0 002F3CB0  48 00 00 50 */	b lbl_802F7120
lbl_802F70D4:
/* 802F70D4 002F3CB4  88 03 24 CD */	lbz r0, 0x24cd(r3)
/* 802F70D8 002F3CB8  54 00 D7 FF */	rlwinm. r0, r0, 0x1a, 0x1f, 0x1f
/* 802F70DC 002F3CBC  41 82 00 34 */	beq lbl_802F7110
/* 802F70E0 002F3CC0  28 07 00 06 */	cmplwi r7, 6
/* 802F70E4 002F3CC4  40 82 00 18 */	bne lbl_802F70FC
/* 802F70E8 002F3CC8  38 FF 00 00 */	addi r7, r31, 0
/* 802F70EC 002F3CCC  38 60 00 07 */	li r3, 7
/* 802F70F0 002F3CD0  39 00 00 00 */	li r8, 0
/* 802F70F4 002F3CD4  4B FF FD B1 */	bl func_802F6EA4
/* 802F70F8 002F3CD8  48 00 00 28 */	b lbl_802F7120
lbl_802F70FC:
/* 802F70FC 002F3CDC  38 FF 00 00 */	addi r7, r31, 0
/* 802F7100 002F3CE0  38 60 00 06 */	li r3, 6
/* 802F7104 002F3CE4  39 00 00 00 */	li r8, 0
/* 802F7108 002F3CE8  4B FF FD 9D */	bl func_802F6EA4
/* 802F710C 002F3CEC  48 00 00 14 */	b lbl_802F7120
lbl_802F7110:
/* 802F7110 002F3CF0  38 FF 00 00 */	addi r7, r31, 0
/* 802F7114 002F3CF4  38 60 00 05 */	li r3, 5
/* 802F7118 002F3CF8  39 00 00 00 */	li r8, 0
/* 802F711C 002F3CFC  4B FF FD 89 */	bl func_802F6EA4
lbl_802F7120:
/* 802F7120 002F3D00  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 802F7124 002F3D04  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 802F7128 002F3D08  38 21 00 18 */	addi r1, r1, 0x18
/* 802F712C 002F3D0C  7C 08 03 A6 */	mtlr r0
/* 802F7130 002F3D10  4E 80 00 20 */	blr 

.global func_802F7134
func_802F7134:
/* 802F7134 002F3D14  7C 08 02 A6 */	mflr r0
/* 802F7138 002F3D18  3C 60 80 40 */	lis r3, lbl_803F9628@ha
/* 802F713C 002F3D1C  90 01 00 04 */	stw r0, 4(r1)
/* 802F7140 002F3D20  38 00 00 00 */	li r0, 0
/* 802F7144 002F3D24  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 802F7148 002F3D28  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 802F714C 002F3D2C  3B E3 96 28 */	addi r31, r3, lbl_803F9628@l
/* 802F7150 002F3D30  90 1F 00 00 */	stw r0, 0(r31)
/* 802F7154 002F3D34  90 1F 00 04 */	stw r0, 4(r31)
/* 802F7158 002F3D38  90 1F 00 28 */	stw r0, 0x28(r31)
/* 802F715C 002F3D3C  90 1F 00 2C */	stw r0, 0x2c(r31)
/* 802F7160 002F3D40  90 1F 00 50 */	stw r0, 0x50(r31)
/* 802F7164 002F3D44  90 1F 00 54 */	stw r0, 0x54(r31)
/* 802F7168 002F3D48  90 1F 00 78 */	stw r0, 0x78(r31)
/* 802F716C 002F3D4C  90 1F 00 7C */	stw r0, 0x7c(r31)
/* 802F7170 002F3D50  90 1F 00 A0 */	stw r0, 0xa0(r31)
/* 802F7174 002F3D54  90 1F 00 A4 */	stw r0, 0xa4(r31)
/* 802F7178 002F3D58  90 1F 00 C8 */	stw r0, 0xc8(r31)
/* 802F717C 002F3D5C  90 1F 00 CC */	stw r0, 0xcc(r31)
/* 802F7180 002F3D60  90 1F 00 F0 */	stw r0, 0xf0(r31)
/* 802F7184 002F3D64  90 1F 00 F4 */	stw r0, 0xf4(r31)
/* 802F7188 002F3D68  90 1F 01 18 */	stw r0, 0x118(r31)
/* 802F718C 002F3D6C  90 1F 01 1C */	stw r0, 0x11c(r31)
/* 802F7190 002F3D70  4B FF C5 01 */	bl func_802F3690
/* 802F7194 002F3D74  80 63 00 00 */	lwz r3, 0(r3)
/* 802F7198 002F3D78  38 81 00 1C */	addi r4, r1, 0x1c
/* 802F719C 002F3D7C  38 BF 01 40 */	addi r5, r31, 0x140
/* 802F71A0 002F3D80  4C C6 31 82 */	crclr 6
/* 802F71A4 002F3D84  38 C0 00 00 */	li r6, 0
/* 802F71A8 002F3D88  4B D1 F9 49 */	bl func_80016AF0
/* 802F71AC 002F3D8C  80 61 00 1C */	lwz r3, 0x1c(r1)
/* 802F71B0 002F3D90  80 03 00 00 */	lwz r0, 0(r3)
/* 802F71B4 002F3D94  90 1F 00 14 */	stw r0, 0x14(r31)
/* 802F71B8 002F3D98  80 61 00 1C */	lwz r3, 0x1c(r1)
/* 802F71BC 002F3D9C  80 03 00 04 */	lwz r0, 4(r3)
/* 802F71C0 002F3DA0  90 1F 00 3C */	stw r0, 0x3c(r31)
/* 802F71C4 002F3DA4  80 61 00 1C */	lwz r3, 0x1c(r1)
/* 802F71C8 002F3DA8  80 03 00 08 */	lwz r0, 8(r3)
/* 802F71CC 002F3DAC  90 1F 00 64 */	stw r0, 0x64(r31)
/* 802F71D0 002F3DB0  80 61 00 1C */	lwz r3, 0x1c(r1)
/* 802F71D4 002F3DB4  80 03 00 0C */	lwz r0, 0xc(r3)
/* 802F71D8 002F3DB8  90 1F 00 8C */	stw r0, 0x8c(r31)
/* 802F71DC 002F3DBC  80 61 00 1C */	lwz r3, 0x1c(r1)
/* 802F71E0 002F3DC0  80 03 00 10 */	lwz r0, 0x10(r3)
/* 802F71E4 002F3DC4  90 1F 00 B4 */	stw r0, 0xb4(r31)
/* 802F71E8 002F3DC8  80 61 00 1C */	lwz r3, 0x1c(r1)
/* 802F71EC 002F3DCC  80 03 00 14 */	lwz r0, 0x14(r3)
/* 802F71F0 002F3DD0  90 1F 00 DC */	stw r0, 0xdc(r31)
/* 802F71F4 002F3DD4  80 61 00 1C */	lwz r3, 0x1c(r1)
/* 802F71F8 002F3DD8  80 03 00 18 */	lwz r0, 0x18(r3)
/* 802F71FC 002F3DDC  90 1F 01 04 */	stw r0, 0x104(r31)
/* 802F7200 002F3DE0  80 61 00 1C */	lwz r3, 0x1c(r1)
/* 802F7204 002F3DE4  80 03 00 1C */	lwz r0, 0x1c(r3)
/* 802F7208 002F3DE8  90 1F 01 2C */	stw r0, 0x12c(r31)
/* 802F720C 002F3DEC  80 01 00 34 */	lwz r0, 0x34(r1)
/* 802F7210 002F3DF0  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 802F7214 002F3DF4  38 21 00 30 */	addi r1, r1, 0x30
/* 802F7218 002F3DF8  7C 08 03 A6 */	mtlr r0
/* 802F721C 002F3DFC  4E 80 00 20 */	blr 

.global func_802F7220
func_802F7220:
/* 802F7220 002F3E00  7C 08 02 A6 */	mflr r0
/* 802F7224 002F3E04  3C 60 80 40 */	lis r3, lbl_803F9628@ha
/* 802F7228 002F3E08  90 01 00 04 */	stw r0, 4(r1)
/* 802F722C 002F3E0C  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 802F7230 002F3E10  93 E1 00 14 */	stw r31, 0x14(r1)
/* 802F7234 002F3E14  3B E0 00 00 */	li r31, 0
/* 802F7238 002F3E18  93 C1 00 10 */	stw r30, 0x10(r1)
/* 802F723C 002F3E1C  3B C3 96 28 */	addi r30, r3, lbl_803F9628@l
/* 802F7240 002F3E20  93 A1 00 0C */	stw r29, 0xc(r1)
/* 802F7244 002F3E24  3B A0 00 00 */	li r29, 0
lbl_802F7248:
/* 802F7248 002F3E28  80 7E 00 00 */	lwz r3, 0(r30)
/* 802F724C 002F3E2C  28 03 00 00 */	cmplwi r3, 0
/* 802F7250 002F3E30  41 82 00 0C */	beq lbl_802F725C
/* 802F7254 002F3E34  48 09 8F D5 */	bl func_80390228
/* 802F7258 002F3E38  93 FE 00 00 */	stw r31, 0(r30)
lbl_802F725C:
/* 802F725C 002F3E3C  3B BD 00 01 */	addi r29, r29, 1
/* 802F7260 002F3E40  2C 1D 00 08 */	cmpwi r29, 8
/* 802F7264 002F3E44  3B DE 00 28 */	addi r30, r30, 0x28
/* 802F7268 002F3E48  41 80 FF E0 */	blt lbl_802F7248
/* 802F726C 002F3E4C  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 802F7270 002F3E50  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 802F7274 002F3E54  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 802F7278 002F3E58  83 A1 00 0C */	lwz r29, 0xc(r1)
/* 802F727C 002F3E5C  38 21 00 18 */	addi r1, r1, 0x18
/* 802F7280 002F3E60  7C 08 03 A6 */	mtlr r0
/* 802F7284 002F3E64  4E 80 00 20 */	blr 


.section .data
    .balign 8
.global lbl_803F9598
lbl_803F9598:
    .asciz "DmgNum_scene_models"
    .balign 4
.global lbl_803F95AC
lbl_803F95AC:
    .asciz "DmgMrk_scene_models"
    .balign 4
.global lbl_803F95C0
lbl_803F95C0:
    .asciz "translate"
    .balign 4
    .asciz "Error : gobj dont't get (ifAddMark)\n"
    .balign 4
    .asciz "ifstatus.c"
    .balign 4
    .asciz "Error : jobj dont't get (ifAddMark)\n"
    .balign 4
.global lbl_803F9628
lbl_803F9628:
    .4byte NULL
    .4byte NULL
	.4byte lbl_802F74D0
    .4byte 0x0007C860
    .4byte 0x08000000
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
	.4byte lbl_802F73C4
    .4byte 0x0000C351
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
	.4byte lbl_802F74D0
    .4byte 0x0007C85E
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
	.4byte lbl_802F73C4
    .4byte 0x0007C85D
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
	.4byte lbl_802F73C4
    .4byte 0x0007C857
    .4byte 0x0A000000
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
	.4byte lbl_802F74D0
    .4byte 0x0007C855
    .4byte 0x08000000
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
	.4byte lbl_802F74D0
    .4byte 0x00009C48
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
	.4byte lbl_802F74D0
    .4byte 0x00009C46
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x5363496E
    .4byte 0x66436E74
    .4byte 0x5F736365
    .4byte 0x6E655F6D
    .4byte 0x6F64656C
    .4byte 0x73000000


.section .sdata
    .balign 8
.global lbl_804D57A8
lbl_804D57A8:
	.4byte 0xFFFFFFFF
.global lbl_804D57AC
lbl_804D57AC:
    .asciz "P"
    .byte 0x00
    .byte 0xFF
.global lbl_804D57B0
lbl_804D57B0:
    .asciz "jobj.h"
    .balign 4
.global lbl_804D57B8
lbl_804D57B8:
    .asciz "jobj"
    .balign 4
.global lbl_804D57C0
lbl_804D57C0:
    .asciz "0"
    .balign 4


.section .bss, "wa"
    .balign 8
.global lbl_804A10C8
lbl_804A10C8:
	.skip 0x278


.section .sbss
    .balign 8
.global lbl_804D6D60
lbl_804D6D60:
	.skip 0x1
.global lbl_804D6D61
lbl_804D6D61:
	.skip 0x7


.section .sdata2
    .balign 8
.global lbl_804DDA48
lbl_804DDA48:
	.4byte 0x3F800000
.global lbl_804DDA4C
lbl_804DDA4C:
	.4byte 0x00000000
.global lbl_804DDA50
lbl_804DDA50:
	.4byte 0x40000000
	.4byte 0x00000000
.global lbl_804DDA58
lbl_804DDA58:
	.4byte 0x43300000
	.4byte 0x00000000
.global lbl_804DDA60
lbl_804DDA60:
	.4byte 0x43300000
	.4byte 0x80000000
.global lbl_804DDA68
lbl_804DDA68:
	.4byte 0x43960000
.global lbl_804DDA6C
lbl_804DDA6C:
	.4byte 0x42C80000
.global lbl_804DDA70
lbl_804DDA70:
	.4byte 0x3F01C433
.global lbl_804DDA74
lbl_804DDA74:
	.4byte 0x3F1BB98C
.global lbl_804DDA78
lbl_804DDA78:
	.4byte 0x3E9BB2FF
.global lbl_804DDA7C
lbl_804DDA7C:
	.4byte 0x3F9BB646
.global lbl_804DDA80
lbl_804DDA80:
	.4byte 0x3F4F9DB2
.global lbl_804DDA84
lbl_804DDA84:
	.4byte 0x3DCFAACE
.global lbl_804DDA88
lbl_804DDA88:
	.4byte 0x3FC2A64C
.global lbl_804DDA8C
lbl_804DDA8C:
	.4byte 0xC2C80000
.global lbl_804DDA90
lbl_804DDA90:
	.4byte 0x3E4FAACE
.global lbl_804DDA94
lbl_804DDA94:
	.4byte 0x3F000000
.global lbl_804DDA98
lbl_804DDA98:
	.4byte 0x3F266666
.global lbl_804DDA9C
lbl_804DDA9C:
	.4byte 0x3DCCCCCD
.global lbl_804DDAA0
lbl_804DDAA0:
	.4byte 0x3E800000
	.4byte 0x00000000
.global lbl_804DDAA8
lbl_804DDAA8:
	.4byte 0x00000000
	.4byte 0x00000000
