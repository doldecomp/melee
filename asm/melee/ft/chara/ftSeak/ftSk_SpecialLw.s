.include "macros.inc"

.section .text

.L_80114034:
/* 80114034 00110C14  7C 08 02 A6 */	mflr r0
/* 80114038 00110C18  90 01 00 04 */	stw r0, 4(r1)
/* 8011403C 00110C1C  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80114040 00110C20  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80114044 00110C24  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80114048 00110C28  88 1F 22 19 */	lbz r0, 0x2219(r31)
/* 8011404C 00110C2C  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 80114050 00110C30  40 82 00 2C */	bne .L_8011407C
/* 80114054 00110C34  80 BF 05 E8 */	lwz r5, 0x5e8(r31)
/* 80114058 00110C38  38 83 00 00 */	addi r4, r3, 0
/* 8011405C 00110C3C  4C C6 31 82 */	crclr 6
/* 80114060 00110C40  38 60 04 FC */	li r3, 0x4fc
/* 80114064 00110C44  80 A5 02 B0 */	lwz r5, 0x2b0(r5)
/* 80114068 00110C48  4B F4 BD 75 */	bl efSync_Spawn
/* 8011406C 00110C4C  88 1F 22 19 */	lbz r0, 0x2219(r31)
/* 80114070 00110C50  38 60 00 01 */	li r3, 1
/* 80114074 00110C54  50 60 3E 30 */	rlwimi r0, r3, 7, 0x18, 0x18
/* 80114078 00110C58  98 1F 22 19 */	stb r0, 0x2219(r31)
.L_8011407C:
/* 8011407C 00110C5C  3C 60 80 06 */	lis r3, efLib_PauseAll@ha
/* 80114080 00110C60  38 03 BA 40 */	addi r0, r3, efLib_PauseAll@l
/* 80114084 00110C64  3C 60 80 06 */	lis r3, efLib_ResumeAll@ha
/* 80114088 00110C68  90 1F 21 D4 */	stw r0, 0x21d4(r31)
/* 8011408C 00110C6C  38 03 BA C4 */	addi r0, r3, efLib_ResumeAll@l
/* 80114090 00110C70  90 1F 21 D8 */	stw r0, 0x21d8(r31)
/* 80114094 00110C74  38 00 00 00 */	li r0, 0
/* 80114098 00110C78  90 1F 21 BC */	stw r0, 0x21bc(r31)
/* 8011409C 00110C7C  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 801140A0 00110C80  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 801140A4 00110C84  38 21 00 18 */	addi r1, r1, 0x18
/* 801140A8 00110C88  7C 08 03 A6 */	mtlr r0
/* 801140AC 00110C8C  4E 80 00 20 */	blr

.L_801140B0:
/* 801140B0 00110C90  7C 08 02 A6 */	mflr r0
/* 801140B4 00110C94  90 01 00 04 */	stw r0, 4(r1)
/* 801140B8 00110C98  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 801140BC 00110C9C  93 E1 00 14 */	stw r31, 0x14(r1)
/* 801140C0 00110CA0  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 801140C4 00110CA4  88 1F 22 19 */	lbz r0, 0x2219(r31)
/* 801140C8 00110CA8  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 801140CC 00110CAC  40 82 00 2C */	bne .L_801140F8
/* 801140D0 00110CB0  80 BF 05 E8 */	lwz r5, 0x5e8(r31)
/* 801140D4 00110CB4  38 83 00 00 */	addi r4, r3, 0
/* 801140D8 00110CB8  4C C6 31 82 */	crclr 6
/* 801140DC 00110CBC  38 60 04 FD */	li r3, 0x4fd
/* 801140E0 00110CC0  80 A5 00 40 */	lwz r5, 0x40(r5)
/* 801140E4 00110CC4  4B F4 BC F9 */	bl efSync_Spawn
/* 801140E8 00110CC8  88 1F 22 19 */	lbz r0, 0x2219(r31)
/* 801140EC 00110CCC  38 60 00 01 */	li r3, 1
/* 801140F0 00110CD0  50 60 3E 30 */	rlwimi r0, r3, 7, 0x18, 0x18
/* 801140F4 00110CD4  98 1F 22 19 */	stb r0, 0x2219(r31)
.L_801140F8:
/* 801140F8 00110CD8  3C 60 80 06 */	lis r3, efLib_PauseAll@ha
/* 801140FC 00110CDC  38 03 BA 40 */	addi r0, r3, efLib_PauseAll@l
/* 80114100 00110CE0  3C 60 80 06 */	lis r3, efLib_ResumeAll@ha
/* 80114104 00110CE4  90 1F 21 D4 */	stw r0, 0x21d4(r31)
/* 80114108 00110CE8  38 03 BA C4 */	addi r0, r3, efLib_ResumeAll@l
/* 8011410C 00110CEC  90 1F 21 D8 */	stw r0, 0x21d8(r31)
/* 80114110 00110CF0  38 00 00 00 */	li r0, 0
/* 80114114 00110CF4  90 1F 21 BC */	stw r0, 0x21bc(r31)
/* 80114118 00110CF8  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8011411C 00110CFC  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80114120 00110D00  38 21 00 18 */	addi r1, r1, 0x18
/* 80114124 00110D04  7C 08 03 A6 */	mtlr r0
/* 80114128 00110D08  4E 80 00 20 */	blr

 .L_8011412C:
 /* 8011412C 00110D0C  7C 08 02 A6 */	mflr r0
 /* 80114130 00110D10  3C 80 80 14 */	lis r4, ftZd_SpecialLw_8013B4D8@ha
 /* 80114134 00110D14  90 01 00 04 */	stw r0, 4(r1)
 /* 80114138 00110D18  38 00 00 00 */	li r0, 0
 /* 8011413C 00110D1C  38 84 B4 D8 */	addi r4, r4, ftZd_SpecialLw_8013B4D8@l
 /* 80114140 00110D20  94 21 FF F8 */	stwu r1, -8(r1)
 /* 80114144 00110D24  80 A3 00 2C */	lwz r5, 0x2c(r3)
 /* 80114148 00110D28  90 05 21 BC */	stw r0, 0x21bc(r5)
 /* 8011414C 00110D2C  4B F6 AE 7D */	bl ftCommon_8007EFC8
 /* 80114150 00110D30  80 01 00 0C */	lwz r0, 0xc(r1)
 /* 80114154 00110D34  38 21 00 08 */	addi r1, r1, 8
 /* 80114158 00110D38  7C 08 03 A6 */	mtlr r0
 /* 8011415C 00110D3C  4E 80 00 20 */	blr

.global ftSk_SpecialLw_Enter
ftSk_SpecialLw_Enter:
/* 80114160 00110D40  7C 08 02 A6 */	mflr r0
/* 80114164 00110D44  38 80 01 69 */	li r4, 0x169
/* 80114168 00110D48  90 01 00 04 */	stw r0, 4(r1)
/* 8011416C 00110D4C  38 A0 00 00 */	li r5, 0
/* 80114170 00110D50  38 C0 00 00 */	li r6, 0
/* 80114174 00110D54  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 80114178 00110D58  93 E1 00 34 */	stw r31, 0x34(r1)
/* 8011417C 00110D5C  7C 7F 1B 78 */	mr r31, r3
/* 80114180 00110D60  C0 22 9C C4 */	lfs f1, ftSk_Init_804D96A4@sda21(r2)
/* 80114184 00110D64  C0 42 9C C8 */	lfs f2, ftSk_Init_804D96A8@sda21(r2)
/* 80114188 00110D68  FC 60 08 90 */	fmr f3, f1
/* 8011418C 00110D6C  4B F5 52 21 */	bl Fighter_ChangeMotionState
/* 80114190 00110D70  7F E3 FB 78 */	mr r3, r31
/* 80114194 00110D74  4B F5 AA 11 */	bl ftAnim_8006EBA4
/* 80114198 00110D78  83 FF 00 2C */	lwz r31, 0x2c(r31)
/* 8011419C 00110D7C  38 00 00 00 */	li r0, 0
/* 801141A0 00110D80  38 A1 00 20 */	addi r5, r1, 0x20
/* 801141A4 00110D84  80 7F 02 D4 */	lwz r3, 0x2d4(r31)
/* 801141A8 00110D88  38 80 00 00 */	li r4, 0
/* 801141AC 00110D8C  90 1F 22 00 */	stw r0, 0x2200(r31)
/* 801141B0 00110D90  C0 3F 00 80 */	lfs f1, 0x80(r31)
/* 801141B4 00110D94  C0 03 00 60 */	lfs f0, 0x60(r3)
/* 801141B8 00110D98  EC 01 00 24 */	fdivs f0, f1, f0
/* 801141BC 00110D9C  D0 1F 00 80 */	stfs f0, 0x80(r31)
/* 801141C0 00110DA0  C0 3F 00 84 */	lfs f1, 0x84(r31)
/* 801141C4 00110DA4  C0 03 00 64 */	lfs f0, 0x64(r3)
/* 801141C8 00110DA8  EC 01 00 24 */	fdivs f0, f1, f0
/* 801141CC 00110DAC  D0 1F 00 84 */	stfs f0, 0x84(r31)
/* 801141D0 00110DB0  C0 3F 00 EC */	lfs f1, 0xec(r31)
/* 801141D4 00110DB4  C0 03 00 60 */	lfs f0, 0x60(r3)
/* 801141D8 00110DB8  EC 01 00 24 */	fdivs f0, f1, f0
/* 801141DC 00110DBC  D0 1F 00 EC */	stfs f0, 0xec(r31)
/* 801141E0 00110DC0  80 7F 05 E8 */	lwz r3, 0x5e8(r31)
/* 801141E4 00110DC4  80 63 00 00 */	lwz r3, 0(r3)
/* 801141E8 00110DC8  4B EF 6F E5 */	bl lb_8000B1CC
/* 801141EC 00110DCC  C0 22 9C B8 */	lfs f1, ftSk_Init_804D9698@sda21(r2)
/* 801141F0 00110DD0  38 61 00 20 */	addi r3, r1, 0x20
/* 801141F4 00110DD4  C0 42 9C BC */	lfs f2, ftSk_Init_804D969C@sda21(r2)
/* 801141F8 00110DD8  38 80 00 78 */	li r4, 0x78
/* 801141FC 00110DDC  C0 62 9C C0 */	lfs f3, ftSk_Init_804D96A0@sda21(r2)
/* 80114200 00110DE0  4B EF D7 DD */	bl lb_800119DC
/* 80114204 00110DE4  3C 60 80 11 */	lis r3, .L_80114034@ha
/* 80114208 00110DE8  38 03 40 34 */	addi r0, r3, .L_80114034@l
/* 8011420C 00110DEC  90 1F 21 BC */	stw r0, 0x21bc(r31)
/* 80114210 00110DF0  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 80114214 00110DF4  83 E1 00 34 */	lwz r31, 0x34(r1)
/* 80114218 00110DF8  38 21 00 38 */	addi r1, r1, 0x38
/* 8011421C 00110DFC  7C 08 03 A6 */	mtlr r0
/* 80114220 00110E00  4E 80 00 20 */	blr

.global ftSk_SpecialAirLw_Enter
ftSk_SpecialAirLw_Enter:
/* 80114224 00110E04  7C 08 02 A6 */	mflr r0
/* 80114228 00110E08  38 80 01 6B */	li r4, 0x16b
/* 8011422C 00110E0C  90 01 00 04 */	stw r0, 4(r1)
/* 80114230 00110E10  38 A0 00 00 */	li r5, 0
/* 80114234 00110E14  38 C0 00 00 */	li r6, 0
/* 80114238 00110E18  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 8011423C 00110E1C  93 E1 00 34 */	stw r31, 0x34(r1)
/* 80114240 00110E20  7C 7F 1B 78 */	mr r31, r3
/* 80114244 00110E24  C0 22 9C C4 */	lfs f1, ftSk_Init_804D96A4@sda21(r2)
/* 80114248 00110E28  C0 42 9C C8 */	lfs f2, ftSk_Init_804D96A8@sda21(r2)
/* 8011424C 00110E2C  FC 60 08 90 */	fmr f3, f1
/* 80114250 00110E30  4B F5 51 5D */	bl Fighter_ChangeMotionState
/* 80114254 00110E34  7F E3 FB 78 */	mr r3, r31
/* 80114258 00110E38  4B F5 A9 4D */	bl ftAnim_8006EBA4
/* 8011425C 00110E3C  83 FF 00 2C */	lwz r31, 0x2c(r31)
/* 80114260 00110E40  38 00 00 00 */	li r0, 0
/* 80114264 00110E44  38 A1 00 20 */	addi r5, r1, 0x20
/* 80114268 00110E48  80 7F 02 D4 */	lwz r3, 0x2d4(r31)
/* 8011426C 00110E4C  38 80 00 00 */	li r4, 0
/* 80114270 00110E50  90 1F 22 00 */	stw r0, 0x2200(r31)
/* 80114274 00110E54  C0 3F 00 80 */	lfs f1, 0x80(r31)
/* 80114278 00110E58  C0 03 00 60 */	lfs f0, 0x60(r3)
/* 8011427C 00110E5C  EC 01 00 24 */	fdivs f0, f1, f0
/* 80114280 00110E60  D0 1F 00 80 */	stfs f0, 0x80(r31)
/* 80114284 00110E64  C0 3F 00 84 */	lfs f1, 0x84(r31)
/* 80114288 00110E68  C0 03 00 64 */	lfs f0, 0x64(r3)
/* 8011428C 00110E6C  EC 01 00 24 */	fdivs f0, f1, f0
/* 80114290 00110E70  D0 1F 00 84 */	stfs f0, 0x84(r31)
/* 80114294 00110E74  C0 3F 00 EC */	lfs f1, 0xec(r31)
/* 80114298 00110E78  C0 03 00 60 */	lfs f0, 0x60(r3)
/* 8011429C 00110E7C  EC 01 00 24 */	fdivs f0, f1, f0
/* 801142A0 00110E80  D0 1F 00 EC */	stfs f0, 0xec(r31)
/* 801142A4 00110E84  80 7F 05 E8 */	lwz r3, 0x5e8(r31)
/* 801142A8 00110E88  80 63 00 00 */	lwz r3, 0(r3)
/* 801142AC 00110E8C  4B EF 6F 21 */	bl lb_8000B1CC
/* 801142B0 00110E90  C0 22 9C B8 */	lfs f1, ftSk_Init_804D9698@sda21(r2)
/* 801142B4 00110E94  38 61 00 20 */	addi r3, r1, 0x20
/* 801142B8 00110E98  C0 42 9C BC */	lfs f2, ftSk_Init_804D969C@sda21(r2)
/* 801142BC 00110E9C  38 80 00 78 */	li r4, 0x78
/* 801142C0 00110EA0  C0 62 9C C0 */	lfs f3, ftSk_Init_804D96A0@sda21(r2)
/* 801142C4 00110EA4  4B EF D7 19 */	bl lb_800119DC
/* 801142C8 00110EA8  3C 60 80 11 */	lis r3, .L_80114034@ha
/* 801142CC 00110EAC  38 03 40 34 */	addi r0, r3, .L_80114034@l
/* 801142D0 00110EB0  90 1F 21 BC */	stw r0, 0x21bc(r31)
/* 801142D4 00110EB4  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 801142D8 00110EB8  83 E1 00 34 */	lwz r31, 0x34(r1)
/* 801142DC 00110EBC  38 21 00 38 */	addi r1, r1, 0x38
/* 801142E0 00110EC0  7C 08 03 A6 */	mtlr r0
/* 801142E4 00110EC4  4E 80 00 20 */	blr

.global ftSk_SpecialLw_Anim
ftSk_SpecialLw_Anim:
/* 801142E8 00110EC8  7C 08 02 A6 */	mflr r0
/* 801142EC 00110ECC  90 01 00 04 */	stw r0, 4(r1)
/* 801142F0 00110ED0  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 801142F4 00110ED4  93 E1 00 14 */	stw r31, 0x14(r1)
/* 801142F8 00110ED8  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 801142FC 00110EDC  4B F5 AF 3D */	bl ftAnim_IsFramesRemaining
/* 80114300 00110EE0  2C 03 00 00 */	cmpwi r3, 0
/* 80114304 00110EE4  40 82 00 10 */	bne .L_80114314
/* 80114308 00110EE8  3C 60 80 11 */	lis r3, .L_8011412C@ha
/* 8011430C 00110EEC  38 03 41 2C */	addi r0, r3, .L_8011412C@l
/* 80114310 00110EF0  90 1F 21 BC */	stw r0, 0x21bc(r31)
.L_80114314:
/* 80114314 00110EF4  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80114318 00110EF8  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8011431C 00110EFC  38 21 00 18 */	addi r1, r1, 0x18
/* 80114320 00110F00  7C 08 03 A6 */	mtlr r0
/* 80114324 00110F04  4E 80 00 20 */	blr

.global ftSk_SpecialAirLw_Anim
ftSk_SpecialAirLw_Anim:
/* 80114328 00110F08  7C 08 02 A6 */	mflr r0
/* 8011432C 00110F0C  90 01 00 04 */	stw r0, 4(r1)
/* 80114330 00110F10  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80114334 00110F14  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80114338 00110F18  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8011433C 00110F1C  4B F5 AE FD */	bl ftAnim_IsFramesRemaining
/* 80114340 00110F20  2C 03 00 00 */	cmpwi r3, 0
/* 80114344 00110F24  40 82 00 10 */	bne .L_80114354
/* 80114348 00110F28  3C 60 80 11 */	lis r3, .L_8011412C@ha
/* 8011434C 00110F2C  38 03 41 2C */	addi r0, r3, .L_8011412C@l
/* 80114350 00110F30  90 1F 21 BC */	stw r0, 0x21bc(r31)
.L_80114354:
/* 80114354 00110F34  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80114358 00110F38  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8011435C 00110F3C  38 21 00 18 */	addi r1, r1, 0x18
/* 80114360 00110F40  7C 08 03 A6 */	mtlr r0
/* 80114364 00110F44  4E 80 00 20 */	blr

.global ftSk_SpecialLw_IASA
ftSk_SpecialLw_IASA:
/* 80114368 00110F48  4E 80 00 20 */	blr

.global ftSk_SpecialAirLw_IASA
ftSk_SpecialAirLw_IASA:
/* 8011436C 00110F4C  4E 80 00 20 */	blr

.global ftSk_SpecialLw_Phys
ftSk_SpecialLw_Phys:
/* 80114370 00110F50  7C 08 02 A6 */	mflr r0
/* 80114374 00110F54  90 01 00 04 */	stw r0, 4(r1)
/* 80114378 00110F58  94 21 FF F8 */	stwu r1, -8(r1)
/* 8011437C 00110F5C  4B F7 0B C1 */	bl ft_80084F3C
/* 80114380 00110F60  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80114384 00110F64  38 21 00 08 */	addi r1, r1, 8
/* 80114388 00110F68  7C 08 03 A6 */	mtlr r0
/* 8011438C 00110F6C  4E 80 00 20 */	blr

.global ftSk_SpecialAirLw_Phys
ftSk_SpecialAirLw_Phys:
/* 80114390 00110F70  7C 08 02 A6 */	mflr r0
/* 80114394 00110F74  90 01 00 04 */	stw r0, 4(r1)
/* 80114398 00110F78  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8011439C 00110F7C  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 801143A0 00110F80  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 801143A4 00110F84  80 9F 02 D4 */	lwz r4, 0x2d4(r31)
/* 801143A8 00110F88  7F E3 FB 78 */	mr r3, r31
/* 801143AC 00110F8C  C0 24 00 68 */	lfs f1, 0x68(r4)
/* 801143B0 00110F90  C0 44 00 6C */	lfs f2, 0x6c(r4)
/* 801143B4 00110F94  4B F6 90 E1 */	bl ftCommon_8007D494
/* 801143B8 00110F98  7F E3 FB 78 */	mr r3, r31
/* 801143BC 00110F9C  4B F6 8B 39 */	bl ftCommon_8007CEF4
/* 801143C0 00110FA0  80 01 00 24 */	lwz r0, 0x24(r1)
/* 801143C4 00110FA4  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 801143C8 00110FA8  38 21 00 20 */	addi r1, r1, 0x20
/* 801143CC 00110FAC  7C 08 03 A6 */	mtlr r0
/* 801143D0 00110FB0  4E 80 00 20 */	blr

.global ftSk_SpecialLw_Coll
ftSk_SpecialLw_Coll:
/* 801143D4 00110FB4  7C 08 02 A6 */	mflr r0
/* 801143D8 00110FB8  90 01 00 04 */	stw r0, 4(r1)
/* 801143DC 00110FBC  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 801143E0 00110FC0  93 E1 00 14 */	stw r31, 0x14(r1)
/* 801143E4 00110FC4  7C 7F 1B 78 */	mr r31, r3
/* 801143E8 00110FC8  4B F6 E3 21 */	bl ft_80082708
/* 801143EC 00110FCC  2C 03 00 00 */	cmpwi r3, 0
/* 801143F0 00110FD0  40 82 00 0C */	bne .L_801143FC
/* 801143F4 00110FD4  7F E3 FB 78 */	mr r3, r31
/* 801143F8 00110FD8  48 00 00 55 */	bl ftSk_SpecialLw_8011444C
.L_801143FC:
/* 801143FC 00110FDC  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80114400 00110FE0  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80114404 00110FE4  38 21 00 18 */	addi r1, r1, 0x18
/* 80114408 00110FE8  7C 08 03 A6 */	mtlr r0
/* 8011440C 00110FEC  4E 80 00 20 */	blr

.global ftSk_SpecialAirLw_Coll
ftSk_SpecialAirLw_Coll:
/* 80114410 00110FF0  7C 08 02 A6 */	mflr r0
/* 80114414 00110FF4  90 01 00 04 */	stw r0, 4(r1)
/* 80114418 00110FF8  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8011441C 00110FFC  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80114420 00111000  7C 7F 1B 78 */	mr r31, r3
/* 80114424 00111004  4B F6 D8 E9 */	bl ft_80081D0C
/* 80114428 00111008  2C 03 00 00 */	cmpwi r3, 0
/* 8011442C 0011100C  41 82 00 0C */	beq .L_80114438
/* 80114430 00111010  7F E3 FB 78 */	mr r3, r31
/* 80114434 00111014  48 00 00 85 */	bl ftSk_SpecialLw_801144B8
.L_80114438:
/* 80114438 00111018  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8011443C 0011101C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80114440 00111020  38 21 00 18 */	addi r1, r1, 0x18
/* 80114444 00111024  7C 08 03 A6 */	mtlr r0
/* 80114448 00111028  4E 80 00 20 */	blr

.global ftSk_SpecialLw_8011444C
ftSk_SpecialLw_8011444C:
/* 8011444C 0011102C  7C 08 02 A6 */	mflr r0
/* 80114450 00111030  90 01 00 04 */	stw r0, 4(r1)
/* 80114454 00111034  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80114458 00111038  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8011445C 0011103C  93 C1 00 10 */	stw r30, 0x10(r1)
/* 80114460 00111040  7C 7E 1B 78 */	mr r30, r3
/* 80114464 00111044  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80114468 00111048  7F E3 FB 78 */	mr r3, r31
/* 8011446C 0011104C  4B F6 91 69 */	bl ftCommon_8007D5D4
/* 80114470 00111050  3C 80 0C 4C */	lis r4, 0x0C4C508E@ha
/* 80114474 00111054  C0 3F 08 94 */	lfs f1, 0x894(r31)
/* 80114478 00111058  C0 42 9C C8 */	lfs f2, ftSk_Init_804D96A8@sda21(r2)
/* 8011447C 0011105C  7F C3 F3 78 */	mr r3, r30
/* 80114480 00111060  C0 62 9C C4 */	lfs f3, ftSk_Init_804D96A4@sda21(r2)
/* 80114484 00111064  38 A4 50 8E */	addi r5, r4, 0x0C4C508E@l
/* 80114488 00111068  38 80 01 6B */	li r4, 0x16b
/* 8011448C 0011106C  38 C0 00 00 */	li r6, 0
/* 80114490 00111070  4B F5 4F 1D */	bl Fighter_ChangeMotionState
/* 80114494 00111074  3C 60 80 11 */	lis r3, .L_80114034@ha
/* 80114498 00111078  38 03 40 34 */	addi r0, r3, .L_80114034@l
/* 8011449C 0011107C  90 1F 21 BC */	stw r0, 0x21bc(r31)
/* 801144A0 00111080  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 801144A4 00111084  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 801144A8 00111088  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 801144AC 0011108C  38 21 00 18 */	addi r1, r1, 0x18
/* 801144B0 00111090  7C 08 03 A6 */	mtlr r0
/* 801144B4 00111094  4E 80 00 20 */	blr

.global ftSk_SpecialLw_801144B8
ftSk_SpecialLw_801144B8:
/* 801144B8 00111098  7C 08 02 A6 */	mflr r0
/* 801144BC 0011109C  90 01 00 04 */	stw r0, 4(r1)
/* 801144C0 001110A0  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 801144C4 001110A4  93 E1 00 14 */	stw r31, 0x14(r1)
/* 801144C8 001110A8  93 C1 00 10 */	stw r30, 0x10(r1)
/* 801144CC 001110AC  7C 7E 1B 78 */	mr r30, r3
/* 801144D0 001110B0  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 801144D4 001110B4  7F E3 FB 78 */	mr r3, r31
/* 801144D8 001110B8  4B F6 93 25 */	bl ftCommon_8007D7FC
/* 801144DC 001110BC  3C 80 0C 4C */	lis r4, 0x0C4C508E@ha
/* 801144E0 001110C0  C0 3F 08 94 */	lfs f1, 0x894(r31)
/* 801144E4 001110C4  C0 42 9C C8 */	lfs f2, ftSk_Init_804D96A8@sda21(r2)
/* 801144E8 001110C8  7F C3 F3 78 */	mr r3, r30
/* 801144EC 001110CC  C0 62 9C C4 */	lfs f3, ftSk_Init_804D96A4@sda21(r2)
/* 801144F0 001110D0  38 A4 50 8E */	addi r5, r4, 0x0C4C508E@l
/* 801144F4 001110D4  38 80 01 69 */	li r4, 0x169
/* 801144F8 001110D8  38 C0 00 00 */	li r6, 0
/* 801144FC 001110DC  4B F5 4E B1 */	bl Fighter_ChangeMotionState
/* 80114500 001110E0  3C 60 80 11 */	lis r3, .L_80114034@ha
/* 80114504 001110E4  38 03 40 34 */	addi r0, r3, .L_80114034@l
/* 80114508 001110E8  90 1F 21 BC */	stw r0, 0x21bc(r31)
/* 8011450C 001110EC  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80114510 001110F0  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80114514 001110F4  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 80114518 001110F8  38 21 00 18 */	addi r1, r1, 0x18
/* 8011451C 001110FC  7C 08 03 A6 */	mtlr r0
/* 80114520 00111100  4E 80 00 20 */	blr

.global ftSk_SpecialLw2_Anim
ftSk_SpecialLw2_Anim:
/* 80114524 00111104  7C 08 02 A6 */	mflr r0
/* 80114528 00111108  90 01 00 04 */	stw r0, 4(r1)
/* 8011452C 0011110C  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80114530 00111110  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80114534 00111114  7C 7F 1B 78 */	mr r31, r3
/* 80114538 00111118  4B F5 AD 01 */	bl ftAnim_IsFramesRemaining
/* 8011453C 0011111C  2C 03 00 00 */	cmpwi r3, 0
/* 80114540 00111120  40 82 00 0C */	bne .L_8011454C
/* 80114544 00111124  7F E3 FB 78 */	mr r3, r31
/* 80114548 00111128  4B F7 5D 75 */	bl ft_8008A2BC
.L_8011454C:
/* 8011454C 0011112C  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80114550 00111130  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80114554 00111134  38 21 00 18 */	addi r1, r1, 0x18
/* 80114558 00111138  7C 08 03 A6 */	mtlr r0
/* 8011455C 0011113C  4E 80 00 20 */	blr

.global ftSk_SpecialAirLw2_Anim
ftSk_SpecialAirLw2_Anim:
/* 80114560 00111140  7C 08 02 A6 */	mflr r0
/* 80114564 00111144  90 01 00 04 */	stw r0, 4(r1)
/* 80114568 00111148  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8011456C 0011114C  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80114570 00111150  7C 7F 1B 78 */	mr r31, r3
/* 80114574 00111154  4B F5 AC C5 */	bl ftAnim_IsFramesRemaining
/* 80114578 00111158  2C 03 00 00 */	cmpwi r3, 0
/* 8011457C 0011115C  40 82 00 0C */	bne .L_80114588
/* 80114580 00111160  7F E3 FB 78 */	mr r3, r31
/* 80114584 00111164  4B FB 81 AD */	bl ftCo_800CC730
.L_80114588:
/* 80114588 00111168  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8011458C 0011116C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80114590 00111170  38 21 00 18 */	addi r1, r1, 0x18
/* 80114594 00111174  7C 08 03 A6 */	mtlr r0
/* 80114598 00111178  4E 80 00 20 */	blr

.global ftSk_SpecialLw2_IASA
ftSk_SpecialLw2_IASA:
/* 8011459C 0011117C  4E 80 00 20 */	blr

.global ftSk_SpecialAirLw2_IASA
ftSk_SpecialAirLw2_IASA:
/* 801145A0 00111180  4E 80 00 20 */	blr

.global ftSk_SpecialLw2_Phys
ftSk_SpecialLw2_Phys:
/* 801145A4 00111184  7C 08 02 A6 */	mflr r0
/* 801145A8 00111188  90 01 00 04 */	stw r0, 4(r1)
/* 801145AC 0011118C  94 21 FF F8 */	stwu r1, -8(r1)
/* 801145B0 00111190  4B F7 09 8D */	bl ft_80084F3C
/* 801145B4 00111194  80 01 00 0C */	lwz r0, 0xc(r1)
/* 801145B8 00111198  38 21 00 08 */	addi r1, r1, 8
/* 801145BC 0011119C  7C 08 03 A6 */	mtlr r0
/* 801145C0 001111A0  4E 80 00 20 */	blr

.global ftSk_SpecialAirLw2_Phys
ftSk_SpecialAirLw2_Phys:
/* 801145C4 001111A4  7C 08 02 A6 */	mflr r0
/* 801145C8 001111A8  90 01 00 04 */	stw r0, 4(r1)
/* 801145CC 001111AC  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 801145D0 001111B0  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 801145D4 001111B4  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 801145D8 001111B8  80 9F 02 D4 */	lwz r4, 0x2d4(r31)
/* 801145DC 001111BC  7F E3 FB 78 */	mr r3, r31
/* 801145E0 001111C0  C0 24 00 68 */	lfs f1, 0x68(r4)
/* 801145E4 001111C4  C0 44 00 6C */	lfs f2, 0x6c(r4)
/* 801145E8 001111C8  4B F6 8E AD */	bl ftCommon_8007D494
/* 801145EC 001111CC  7F E3 FB 78 */	mr r3, r31
/* 801145F0 001111D0  4B F6 89 05 */	bl ftCommon_8007CEF4
/* 801145F4 001111D4  80 01 00 24 */	lwz r0, 0x24(r1)
/* 801145F8 001111D8  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 801145FC 001111DC  38 21 00 20 */	addi r1, r1, 0x20
/* 80114600 001111E0  7C 08 03 A6 */	mtlr r0
/* 80114604 001111E4  4E 80 00 20 */	blr

.global ftSk_SpecialLw2_Coll
ftSk_SpecialLw2_Coll:
/* 80114608 001111E8  7C 08 02 A6 */	mflr r0
/* 8011460C 001111EC  90 01 00 04 */	stw r0, 4(r1)
/* 80114610 001111F0  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80114614 001111F4  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80114618 001111F8  7C 7F 1B 78 */	mr r31, r3
/* 8011461C 001111FC  4B F6 E0 ED */	bl ft_80082708
/* 80114620 00111200  2C 03 00 00 */	cmpwi r3, 0
/* 80114624 00111204  40 82 00 0C */	bne .L_80114630
/* 80114628 00111208  7F E3 FB 78 */	mr r3, r31
/* 8011462C 0011120C  48 00 00 55 */	bl ftSk_SpecialLw_80114680
.L_80114630:
/* 80114630 00111210  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80114634 00111214  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80114638 00111218  38 21 00 18 */	addi r1, r1, 0x18
/* 8011463C 0011121C  7C 08 03 A6 */	mtlr r0
/* 80114640 00111220  4E 80 00 20 */	blr

.global ftSk_SpecialAirLw2_Coll
ftSk_SpecialAirLw2_Coll:
/* 80114644 00111224  7C 08 02 A6 */	mflr r0
/* 80114648 00111228  90 01 00 04 */	stw r0, 4(r1)
/* 8011464C 0011122C  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80114650 00111230  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80114654 00111234  7C 7F 1B 78 */	mr r31, r3
/* 80114658 00111238  4B F6 D6 B5 */	bl ft_80081D0C
/* 8011465C 0011123C  2C 03 00 00 */	cmpwi r3, 0
/* 80114660 00111240  41 82 00 0C */	beq .L_8011466C
/* 80114664 00111244  7F E3 FB 78 */	mr r3, r31
/* 80114668 00111248  48 00 00 85 */	bl ftSk_SpecialLw_801146EC
.L_8011466C:
/* 8011466C 0011124C  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80114670 00111250  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80114674 00111254  38 21 00 18 */	addi r1, r1, 0x18
/* 80114678 00111258  7C 08 03 A6 */	mtlr r0
/* 8011467C 0011125C  4E 80 00 20 */	blr

.global ftSk_SpecialLw_80114680
ftSk_SpecialLw_80114680:
/* 80114680 00111260  7C 08 02 A6 */	mflr r0
/* 80114684 00111264  90 01 00 04 */	stw r0, 4(r1)
/* 80114688 00111268  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8011468C 0011126C  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80114690 00111270  93 C1 00 10 */	stw r30, 0x10(r1)
/* 80114694 00111274  7C 7E 1B 78 */	mr r30, r3
/* 80114698 00111278  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8011469C 0011127C  7F E3 FB 78 */	mr r3, r31
/* 801146A0 00111280  4B F6 8F 35 */	bl ftCommon_8007D5D4
/* 801146A4 00111284  3C 80 0C 4C */	lis r4, 0x0C4C508E@ha
/* 801146A8 00111288  C0 3F 08 94 */	lfs f1, 0x894(r31)
/* 801146AC 0011128C  C0 42 9C C8 */	lfs f2, ftSk_Init_804D96A8@sda21(r2)
/* 801146B0 00111290  7F C3 F3 78 */	mr r3, r30
/* 801146B4 00111294  C0 62 9C C4 */	lfs f3, ftSk_Init_804D96A4@sda21(r2)
/* 801146B8 00111298  38 A4 50 8E */	addi r5, r4, 0x0C4C508E@l
/* 801146BC 0011129C  38 80 01 6C */	li r4, 0x16c
/* 801146C0 001112A0  38 C0 00 00 */	li r6, 0
/* 801146C4 001112A4  4B F5 4C E9 */	bl Fighter_ChangeMotionState
/* 801146C8 001112A8  3C 60 80 11 */	lis r3, .L_801140B0@ha
/* 801146CC 001112AC  38 03 40 B0 */	addi r0, r3, .L_801140B0@l
/* 801146D0 001112B0  90 1F 21 BC */	stw r0, 0x21bc(r31)
/* 801146D4 001112B4  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 801146D8 001112B8  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 801146DC 001112BC  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 801146E0 001112C0  38 21 00 18 */	addi r1, r1, 0x18
/* 801146E4 001112C4  7C 08 03 A6 */	mtlr r0
/* 801146E8 001112C8  4E 80 00 20 */	blr

.global ftSk_SpecialLw_801146EC
ftSk_SpecialLw_801146EC:
/* 801146EC 001112CC  7C 08 02 A6 */	mflr r0
/* 801146F0 001112D0  90 01 00 04 */	stw r0, 4(r1)
/* 801146F4 001112D4  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 801146F8 001112D8  93 E1 00 14 */	stw r31, 0x14(r1)
/* 801146FC 001112DC  93 C1 00 10 */	stw r30, 0x10(r1)
/* 80114700 001112E0  7C 7E 1B 78 */	mr r30, r3
/* 80114704 001112E4  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80114708 001112E8  7F E3 FB 78 */	mr r3, r31
/* 8011470C 001112EC  4B F6 90 F1 */	bl ftCommon_8007D7FC
/* 80114710 001112F0  3C 80 0C 4C */	lis r4, 0x0C4C508E@ha
/* 80114714 001112F4  C0 3F 08 94 */	lfs f1, 0x894(r31)
/* 80114718 001112F8  C0 42 9C C8 */	lfs f2, ftSk_Init_804D96A8@sda21(r2)
/* 8011471C 001112FC  7F C3 F3 78 */	mr r3, r30
/* 80114720 00111300  C0 62 9C C4 */	lfs f3, ftSk_Init_804D96A4@sda21(r2)
/* 80114724 00111304  38 A4 50 8E */	addi r5, r4, 0x0C4C508E@l
/* 80114728 00111308  38 80 01 6A */	li r4, 0x16a
/* 8011472C 0011130C  38 C0 00 00 */	li r6, 0
/* 80114730 00111310  4B F5 4C 7D */	bl Fighter_ChangeMotionState
/* 80114734 00111314  3C 60 80 11 */	lis r3, .L_801140B0@ha
/* 80114738 00111318  38 03 40 B0 */	addi r0, r3, .L_801140B0@l
/* 8011473C 0011131C  90 1F 21 BC */	stw r0, 0x21bc(r31)
/* 80114740 00111320  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80114744 00111324  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80114748 00111328  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8011474C 0011132C  38 21 00 18 */	addi r1, r1, 0x18
/* 80114750 00111330  7C 08 03 A6 */	mtlr r0
/* 80114754 00111334  4E 80 00 20 */	blr

.global ftSk_SpecialLw_80114758
ftSk_SpecialLw_80114758:
/* 80114758 00111338  7C 08 02 A6 */	mflr r0
/* 8011475C 0011133C  90 01 00 04 */	stw r0, 4(r1)
/* 80114760 00111340  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80114764 00111344  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80114768 00111348  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8011476C 0011134C  80 1F 00 E0 */	lwz r0, 0xe0(r31)
/* 80114770 00111350  80 BF 02 D4 */	lwz r5, 0x2d4(r31)
/* 80114774 00111354  2C 00 00 00 */	cmpwi r0, 0
/* 80114778 00111358  40 82 00 0C */	bne .L_80114784
/* 8011477C 0011135C  38 80 01 6A */	li r4, 0x16a
/* 80114780 00111360  48 00 00 08 */	b .L_80114788
.L_80114784:
/* 80114784 00111364  38 80 01 6C */	li r4, 0x16c
.L_80114788:
/* 80114788 00111368  C0 25 00 70 */	lfs f1, 0x70(r5)
/* 8011478C 0011136C  38 A0 00 00 */	li r5, 0
/* 80114790 00111370  C0 42 9C C8 */	lfs f2, ftSk_Init_804D96A8@sda21(r2)
/* 80114794 00111374  38 C0 00 00 */	li r6, 0
/* 80114798 00111378  C0 62 9C C4 */	lfs f3, ftSk_Init_804D96A4@sda21(r2)
/* 8011479C 0011137C  4B F5 4C 11 */	bl Fighter_ChangeMotionState
/* 801147A0 00111380  3C 60 80 11 */	lis r3, .L_801140B0@ha
/* 801147A4 00111384  38 03 40 B0 */	addi r0, r3, .L_801140B0@l
/* 801147A8 00111388  90 1F 21 BC */	stw r0, 0x21bc(r31)
/* 801147AC 0011138C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 801147B0 00111390  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 801147B4 00111394  38 21 00 20 */	addi r1, r1, 0x20
/* 801147B8 00111398  7C 08 03 A6 */	mtlr r0
/* 801147BC 0011139C  4E 80 00 20 */	blr
