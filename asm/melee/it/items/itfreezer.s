.include "macros.inc"

.section .text

.global it_802CCF9C
it_802CCF9C:
/* 802CCF9C 002C9B7C  7C 08 02 A6 */	mflr r0
/* 802CCFA0 002C9B80  90 01 00 04 */	stw r0, 4(r1)
/* 802CCFA4 002C9B84  38 00 00 00 */	li r0, 0
/* 802CCFA8 002C9B88  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 802CCFAC 002C9B8C  93 E1 00 14 */	stw r31, 0x14(r1)
/* 802CCFB0 002C9B90  93 C1 00 10 */	stw r30, 0x10(r1)
/* 802CCFB4 002C9B94  7C 7E 1B 78 */	mr r30, r3
/* 802CCFB8 002C9B98  80 A3 00 2C */	lwz r5, 0x2c(r3)
/* 802CCFBC 002C9B9C  C0 02 D9 D0 */	lfs f0, it_804DD3B0@sda21(r2)
/* 802CCFC0 002C9BA0  80 85 00 C4 */	lwz r4, 0xc4(r5)
/* 802CCFC4 002C9BA4  83 E4 00 04 */	lwz r31, 4(r4)
/* 802CCFC8 002C9BA8  D0 05 00 2C */	stfs f0, 0x2c(r5)
/* 802CCFCC 002C9BAC  90 05 0D AC */	stw r0, 0xdac(r5)
/* 802CCFD0 002C9BB0  90 05 0D B0 */	stw r0, 0xdb0(r5)
/* 802CCFD4 002C9BB4  48 00 03 19 */	bl it_802CD2EC
/* 802CCFD8 002C9BB8  7F C3 F3 78 */	mr r3, r30
/* 802CCFDC 002C9BBC  C0 3F 00 00 */	lfs f1, 0(r31)
/* 802CCFE0 002C9BC0  4B FA CC FD */	bl it_80279CDC
/* 802CCFE4 002C9BC4  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 802CCFE8 002C9BC8  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 802CCFEC 002C9BCC  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 802CCFF0 002C9BD0  38 21 00 18 */	addi r1, r1, 0x18
/* 802CCFF4 002C9BD4  7C 08 03 A6 */	mtlr r0
/* 802CCFF8 002C9BD8  4E 80 00 20 */	blr

.global it_802CCFFC
it_802CCFFC:
/* 802CCFFC 002C9BDC  4E 80 00 20 */	blr

.global it_802CD000
it_802CD000:
/* 802CD000 002C9BE0  7C 08 02 A6 */	mflr r0
/* 802CD004 002C9BE4  90 01 00 04 */	stw r0, 4(r1)
/* 802CD008 002C9BE8  94 21 FF F8 */	stwu r1, -8(r1)
/* 802CD00C 002C9BEC  4B F9 E8 89 */	bl it_8026B894
/* 802CD010 002C9BF0  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802CD014 002C9BF4  38 21 00 08 */	addi r1, r1, 8
/* 802CD018 002C9BF8  7C 08 03 A6 */	mtlr r0
/* 802CD01C 002C9BFC  4E 80 00 20 */	blr

.global it_802CD020
it_802CD020:
/* 802CD020 002C9C00  7C 08 02 A6 */	mflr r0
/* 802CD024 002C9C04  90 01 00 04 */	stw r0, 4(r1)
/* 802CD028 002C9C08  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 802CD02C 002C9C0C  93 E1 00 14 */	stw r31, 0x14(r1)
/* 802CD030 002C9C10  7C 7F 1B 78 */	mr r31, r3
/* 802CD034 002C9C14  4B FA 5C 39 */	bl it_80272C6C
/* 802CD038 002C9C18  2C 03 00 00 */	cmpwi r3, 0
/* 802CD03C 002C9C1C  40 82 00 0C */	bne .L_802CD048
/* 802CD040 002C9C20  7F E3 FB 78 */	mr r3, r31
/* 802CD044 002C9C24  48 00 00 E9 */	bl it_802CD12C
.L_802CD048:
/* 802CD048 002C9C28  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 802CD04C 002C9C2C  38 60 00 00 */	li r3, 0
/* 802CD050 002C9C30  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 802CD054 002C9C34  38 21 00 18 */	addi r1, r1, 0x18
/* 802CD058 002C9C38  7C 08 03 A6 */	mtlr r0
/* 802CD05C 002C9C3C  4E 80 00 20 */	blr

.global it_802CD060
it_802CD060:
/* 802CD060 002C9C40  4E 80 00 20 */	blr

.global it_802CD064
it_802CD064:
/* 802CD064 002C9C44  7C 08 02 A6 */	mflr r0
/* 802CD068 002C9C48  3C 80 80 2D */	lis r4, it_802CCFFC@ha
/* 802CD06C 002C9C4C  90 01 00 04 */	stw r0, 4(r1)
/* 802CD070 002C9C50  38 84 CF FC */	addi r4, r4, it_802CCFFC@l
/* 802CD074 002C9C54  94 21 FF F8 */	stwu r1, -8(r1)
/* 802CD078 002C9C58  4B FA 10 E5 */	bl it_8026E15C
/* 802CD07C 002C9C5C  38 60 00 00 */	li r3, 0
/* 802CD080 002C9C60  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802CD084 002C9C64  38 21 00 08 */	addi r1, r1, 8
/* 802CD088 002C9C68  7C 08 03 A6 */	mtlr r0
/* 802CD08C 002C9C6C  4E 80 00 20 */	blr

.global it_802CD090
it_802CD090:
/* 802CD090 002C9C70  7C 08 02 A6 */	mflr r0
/* 802CD094 002C9C74  90 01 00 04 */	stw r0, 4(r1)
/* 802CD098 002C9C78  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 802CD09C 002C9C7C  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 802CD0A0 002C9C80  93 C1 00 18 */	stw r30, 0x18(r1)
/* 802CD0A4 002C9C84  7C 7E 1B 78 */	mr r30, r3
/* 802CD0A8 002C9C88  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 802CD0AC 002C9C8C  80 1F 0D B0 */	lwz r0, 0xdb0(r31)
/* 802CD0B0 002C9C90  28 00 00 00 */	cmplwi r0, 0
/* 802CD0B4 002C9C94  41 82 00 24 */	beq .L_802CD0D8
/* 802CD0B8 002C9C98  80 BF 0B BC */	lwz r5, 0xbbc(r31)
/* 802CD0BC 002C9C9C  7F C4 F3 78 */	mr r4, r30
/* 802CD0C0 002C9CA0  C0 22 D9 D4 */	lfs f1, it_804DD3B4@sda21(r2)
/* 802CD0C4 002C9CA4  38 60 04 62 */	li r3, 0x462
/* 802CD0C8 002C9CA8  80 A5 00 14 */	lwz r5, 0x14(r5)
/* 802CD0CC 002C9CAC  4B FA DD 21 */	bl it_8027ADEC
/* 802CD0D0 002C9CB0  38 00 00 00 */	li r0, 0
/* 802CD0D4 002C9CB4  90 1F 0D B0 */	stw r0, 0xdb0(r31)
.L_802CD0D8:
/* 802CD0D8 002C9CB8  80 7F 0E 34 */	lwz r3, 0xe34(r31)
/* 802CD0DC 002C9CBC  2C 03 00 00 */	cmpwi r3, 0
/* 802CD0E0 002C9CC0  41 81 00 2C */	bgt .L_802CD10C
/* 802CD0E4 002C9CC4  80 DF 00 C4 */	lwz r6, 0xc4(r31)
/* 802CD0E8 002C9CC8  7F C4 F3 78 */	mr r4, r30
/* 802CD0EC 002C9CCC  80 BE 00 28 */	lwz r5, 0x28(r30)
/* 802CD0F0 002C9CD0  38 60 04 61 */	li r3, 0x461
/* 802CD0F4 002C9CD4  80 C6 00 04 */	lwz r6, 4(r6)
/* 802CD0F8 002C9CD8  80 06 00 0C */	lwz r0, 0xc(r6)
/* 802CD0FC 002C9CDC  90 1F 0E 34 */	stw r0, 0xe34(r31)
/* 802CD100 002C9CE0  C0 22 D9 D4 */	lfs f1, it_804DD3B4@sda21(r2)
/* 802CD104 002C9CE4  4B FA DC E9 */	bl it_8027ADEC
/* 802CD108 002C9CE8  48 00 00 0C */	b .L_802CD114
.L_802CD10C:
/* 802CD10C 002C9CEC  38 03 FF FF */	addi r0, r3, -1
/* 802CD110 002C9CF0  90 1F 0E 34 */	stw r0, 0xe34(r31)
.L_802CD114:
/* 802CD114 002C9CF4  80 01 00 24 */	lwz r0, 0x24(r1)
/* 802CD118 002C9CF8  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 802CD11C 002C9CFC  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 802CD120 002C9D00  38 21 00 20 */	addi r1, r1, 0x20
/* 802CD124 002C9D04  7C 08 03 A6 */	mtlr r0
/* 802CD128 002C9D08  4E 80 00 20 */	blr

.global it_802CD12C
it_802CD12C:
/* 802CD12C 002C9D0C  7C 08 02 A6 */	mflr r0
/* 802CD130 002C9D10  38 80 00 02 */	li r4, 2
/* 802CD134 002C9D14  90 01 00 04 */	stw r0, 4(r1)
/* 802CD138 002C9D18  38 A0 00 02 */	li r5, 2
/* 802CD13C 002C9D1C  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 802CD140 002C9D20  93 E1 00 14 */	stw r31, 0x14(r1)
/* 802CD144 002C9D24  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 802CD148 002C9D28  4B F9 BD 15 */	bl Item_80268E5C
/* 802CD14C 002C9D2C  3C 60 80 06 */	lis r3, efLib_PauseAll@ha
/* 802CD150 002C9D30  38 03 BA 40 */	addi r0, r3, efLib_PauseAll@l
/* 802CD154 002C9D34  3C 60 80 06 */	lis r3, efLib_ResumeAll@ha
/* 802CD158 002C9D38  90 1F 0D 28 */	stw r0, 0xd28(r31)
/* 802CD15C 002C9D3C  38 03 BA C4 */	addi r0, r3, efLib_ResumeAll@l
/* 802CD160 002C9D40  3C 60 80 2D */	lis r3, it_802CD290@ha
/* 802CD164 002C9D44  90 1F 0D 2C */	stw r0, 0xd2c(r31)
/* 802CD168 002C9D48  38 03 D2 90 */	addi r0, r3, it_802CD290@l
/* 802CD16C 002C9D4C  90 1F 0D 20 */	stw r0, 0xd20(r31)
/* 802CD170 002C9D50  38 00 00 00 */	li r0, 0
/* 802CD174 002C9D54  90 1F 0D B0 */	stw r0, 0xdb0(r31)
/* 802CD178 002C9D58  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 802CD17C 002C9D5C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 802CD180 002C9D60  38 21 00 18 */	addi r1, r1, 0x18
/* 802CD184 002C9D64  7C 08 03 A6 */	mtlr r0
/* 802CD188 002C9D68  4E 80 00 20 */	blr

.global it_802CD18C
it_802CD18C:
/* 802CD18C 002C9D6C  7C 08 02 A6 */	mflr r0
/* 802CD190 002C9D70  90 01 00 04 */	stw r0, 4(r1)
/* 802CD194 002C9D74  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 802CD198 002C9D78  93 E1 00 24 */	stw r31, 0x24(r1)
/* 802CD19C 002C9D7C  93 C1 00 20 */	stw r30, 0x20(r1)
/* 802CD1A0 002C9D80  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 802CD1A4 002C9D84  7C 7D 1B 78 */	mr r29, r3
/* 802CD1A8 002C9D88  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 802CD1AC 002C9D8C  4B FA 5A C1 */	bl it_80272C6C
/* 802CD1B0 002C9D90  2C 03 00 00 */	cmpwi r3, 0
/* 802CD1B4 002C9D94  40 82 00 44 */	bne .L_802CD1F8
/* 802CD1B8 002C9D98  83 FD 00 2C */	lwz r31, 0x2c(r29)
/* 802CD1BC 002C9D9C  38 7D 00 00 */	addi r3, r29, 0
/* 802CD1C0 002C9DA0  38 80 00 02 */	li r4, 2
/* 802CD1C4 002C9DA4  38 A0 00 02 */	li r5, 2
/* 802CD1C8 002C9DA8  4B F9 BC 95 */	bl Item_80268E5C
/* 802CD1CC 002C9DAC  3C 60 80 06 */	lis r3, efLib_PauseAll@ha
/* 802CD1D0 002C9DB0  38 03 BA 40 */	addi r0, r3, efLib_PauseAll@l
/* 802CD1D4 002C9DB4  3C 60 80 06 */	lis r3, efLib_ResumeAll@ha
/* 802CD1D8 002C9DB8  90 1F 0D 28 */	stw r0, 0xd28(r31)
/* 802CD1DC 002C9DBC  38 03 BA C4 */	addi r0, r3, efLib_ResumeAll@l
/* 802CD1E0 002C9DC0  3C 60 80 2D */	lis r3, it_802CD290@ha
/* 802CD1E4 002C9DC4  90 1F 0D 2C */	stw r0, 0xd2c(r31)
/* 802CD1E8 002C9DC8  38 03 D2 90 */	addi r0, r3, it_802CD290@l
/* 802CD1EC 002C9DCC  90 1F 0D 20 */	stw r0, 0xd20(r31)
/* 802CD1F0 002C9DD0  38 00 00 00 */	li r0, 0
/* 802CD1F4 002C9DD4  90 1F 0D B0 */	stw r0, 0xdb0(r31)
.L_802CD1F8:
/* 802CD1F8 002C9DD8  4B F5 79 71 */	bl Stage_GetBlastZoneTopOffset
/* 802CD1FC 002C9DDC  C0 1E 00 50 */	lfs f0, 0x50(r30)
/* 802CD200 002C9DE0  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 802CD204 002C9DE4  40 81 00 0C */	ble .L_802CD210
/* 802CD208 002C9DE8  38 60 00 01 */	li r3, 1
/* 802CD20C 002C9DEC  48 00 00 08 */	b .L_802CD214
.L_802CD210:
/* 802CD210 002C9DF0  38 60 00 00 */	li r3, 0
.L_802CD214:
/* 802CD214 002C9DF4  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 802CD218 002C9DF8  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 802CD21C 002C9DFC  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 802CD220 002C9E00  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 802CD224 002C9E04  38 21 00 28 */	addi r1, r1, 0x28
/* 802CD228 002C9E08  7C 08 03 A6 */	mtlr r0
/* 802CD22C 002C9E0C  4E 80 00 20 */	blr

.global it_802CD230
it_802CD230:
/* 802CD230 002C9E10  80 A3 00 2C */	lwz r5, 0x2c(r3)
/* 802CD234 002C9E14  80 05 0D AC */	lwz r0, 0xdac(r5)
/* 802CD238 002C9E18  28 00 00 00 */	cmplwi r0, 0
/* 802CD23C 002C9E1C  41 82 00 24 */	beq .L_802CD260
/* 802CD240 002C9E20  80 85 00 C4 */	lwz r4, 0xc4(r5)
/* 802CD244 002C9E24  38 60 00 00 */	li r3, 0
/* 802CD248 002C9E28  38 00 00 01 */	li r0, 1
/* 802CD24C 002C9E2C  80 84 00 04 */	lwz r4, 4(r4)
/* 802CD250 002C9E30  C0 04 00 04 */	lfs f0, 4(r4)
/* 802CD254 002C9E34  D0 05 00 44 */	stfs f0, 0x44(r5)
/* 802CD258 002C9E38  90 65 0D AC */	stw r3, 0xdac(r5)
/* 802CD25C 002C9E3C  90 05 0D B0 */	stw r0, 0xdb0(r5)
.L_802CD260:
/* 802CD260 002C9E40  80 05 0D B0 */	lwz r0, 0xdb0(r5)
/* 802CD264 002C9E44  28 00 00 00 */	cmplwi r0, 0
/* 802CD268 002C9E48  4D 82 00 20 */	beqlr
/* 802CD26C 002C9E4C  80 65 00 C4 */	lwz r3, 0xc4(r5)
/* 802CD270 002C9E50  C0 25 00 44 */	lfs f1, 0x44(r5)
/* 802CD274 002C9E54  80 63 00 04 */	lwz r3, 4(r3)
/* 802CD278 002C9E58  C0 03 00 08 */	lfs f0, 8(r3)
/* 802CD27C 002C9E5C  EC 01 00 2A */	fadds f0, f1, f0
/* 802CD280 002C9E60  D0 05 00 44 */	stfs f0, 0x44(r5)
/* 802CD284 002C9E64  4E 80 00 20 */	blr

.global it_802CD288
it_802CD288:
/* 802CD288 002C9E68  38 60 00 00 */	li r3, 0
/* 802CD28C 002C9E6C  4E 80 00 20 */	blr

.global it_802CD290
it_802CD290:
/* 802CD290 002C9E70  7C 08 02 A6 */	mflr r0
/* 802CD294 002C9E74  90 01 00 04 */	stw r0, 4(r1)
/* 802CD298 002C9E78  94 21 FF F8 */	stwu r1, -8(r1)
/* 802CD29C 002C9E7C  80 E3 00 2C */	lwz r7, 0x2c(r3)
/* 802CD2A0 002C9E80  80 87 0E 34 */	lwz r4, 0xe34(r7)
/* 802CD2A4 002C9E84  2C 04 00 00 */	cmpwi r4, 0
/* 802CD2A8 002C9E88  41 81 00 2C */	bgt .L_802CD2D4
/* 802CD2AC 002C9E8C  80 C7 00 C4 */	lwz r6, 0xc4(r7)
/* 802CD2B0 002C9E90  7C 64 1B 78 */	mr r4, r3
/* 802CD2B4 002C9E94  80 A3 00 28 */	lwz r5, 0x28(r3)
/* 802CD2B8 002C9E98  38 60 04 61 */	li r3, 0x461
/* 802CD2BC 002C9E9C  80 C6 00 04 */	lwz r6, 4(r6)
/* 802CD2C0 002C9EA0  80 06 00 0C */	lwz r0, 0xc(r6)
/* 802CD2C4 002C9EA4  90 07 0E 34 */	stw r0, 0xe34(r7)
/* 802CD2C8 002C9EA8  C0 22 D9 D4 */	lfs f1, it_804DD3B4@sda21(r2)
/* 802CD2CC 002C9EAC  4B FA DB 21 */	bl it_8027ADEC
/* 802CD2D0 002C9EB0  48 00 00 0C */	b .L_802CD2DC
.L_802CD2D4:
/* 802CD2D4 002C9EB4  38 04 FF FF */	addi r0, r4, -1
/* 802CD2D8 002C9EB8  90 07 0E 34 */	stw r0, 0xe34(r7)
.L_802CD2DC:
/* 802CD2DC 002C9EBC  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802CD2E0 002C9EC0  38 21 00 08 */	addi r1, r1, 8
/* 802CD2E4 002C9EC4  7C 08 03 A6 */	mtlr r0
/* 802CD2E8 002C9EC8  4E 80 00 20 */	blr

.global it_802CD2EC
it_802CD2EC:
/* 802CD2EC 002C9ECC  7C 08 02 A6 */	mflr r0
/* 802CD2F0 002C9ED0  90 01 00 04 */	stw r0, 4(r1)
/* 802CD2F4 002C9ED4  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 802CD2F8 002C9ED8  93 E1 00 14 */	stw r31, 0x14(r1)
/* 802CD2FC 002C9EDC  93 C1 00 10 */	stw r30, 0x10(r1)
/* 802CD300 002C9EE0  7C 7E 1B 78 */	mr r30, r3
/* 802CD304 002C9EE4  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 802CD308 002C9EE8  7F E3 FB 78 */	mr r3, r31
/* 802CD30C 002C9EEC  4B FA 8F B1 */	bl it_802762BC
/* 802CD310 002C9EF0  38 7E 00 00 */	addi r3, r30, 0
/* 802CD314 002C9EF4  38 80 00 00 */	li r4, 0
/* 802CD318 002C9EF8  38 A0 00 02 */	li r5, 2
/* 802CD31C 002C9EFC  4B F9 BB 41 */	bl Item_80268E5C
/* 802CD320 002C9F00  3C 60 80 06 */	lis r3, efLib_PauseAll@ha
/* 802CD324 002C9F04  38 03 BA 40 */	addi r0, r3, efLib_PauseAll@l
/* 802CD328 002C9F08  3C 60 80 06 */	lis r3, efLib_ResumeAll@ha
/* 802CD32C 002C9F0C  90 1F 0D 28 */	stw r0, 0xd28(r31)
/* 802CD330 002C9F10  38 03 BA C4 */	addi r0, r3, efLib_ResumeAll@l
/* 802CD334 002C9F14  90 1F 0D 2C */	stw r0, 0xd2c(r31)
/* 802CD338 002C9F18  38 7E 00 00 */	addi r3, r30, 0
/* 802CD33C 002C9F1C  38 80 00 00 */	li r4, 0
/* 802CD340 002C9F20  C0 22 D9 D0 */	lfs f1, it_804DD3B0@sda21(r2)
/* 802CD344 002C9F24  4B FA 63 2D */	bl it_80273670
/* 802CD348 002C9F28  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 802CD34C 002C9F2C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 802CD350 002C9F30  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 802CD354 002C9F34  38 21 00 18 */	addi r1, r1, 0x18
/* 802CD358 002C9F38  7C 08 03 A6 */	mtlr r0
/* 802CD35C 002C9F3C  4E 80 00 20 */	blr

.global it_802CD360
it_802CD360:
/* 802CD360 002C9F40  7C 08 02 A6 */	mflr r0
/* 802CD364 002C9F44  90 01 00 04 */	stw r0, 4(r1)
/* 802CD368 002C9F48  94 21 FF F8 */	stwu r1, -8(r1)
/* 802CD36C 002C9F4C  4B FA CC 8D */	bl it_80279FF8
/* 802CD370 002C9F50  38 60 00 00 */	li r3, 0
/* 802CD374 002C9F54  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802CD378 002C9F58  38 21 00 08 */	addi r1, r1, 8
/* 802CD37C 002C9F5C  7C 08 03 A6 */	mtlr r0
/* 802CD380 002C9F60  4E 80 00 20 */	blr

.global it_802CD384
it_802CD384:
/* 802CD384 002C9F64  7C 08 02 A6 */	mflr r0
/* 802CD388 002C9F68  90 01 00 04 */	stw r0, 4(r1)
/* 802CD38C 002C9F6C  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 802CD390 002C9F70  93 E1 00 24 */	stw r31, 0x24(r1)
/* 802CD394 002C9F74  93 C1 00 20 */	stw r30, 0x20(r1)
/* 802CD398 002C9F78  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 802CD39C 002C9F7C  7C 7D 1B 78 */	mr r29, r3
/* 802CD3A0 002C9F80  4B FA CC FD */	bl it_8027A09C
/* 802CD3A4 002C9F84  2C 03 00 00 */	cmpwi r3, 0
/* 802CD3A8 002C9F88  41 82 00 60 */	beq .L_802CD408
/* 802CD3AC 002C9F8C  83 FD 00 2C */	lwz r31, 0x2c(r29)
/* 802CD3B0 002C9F90  7F A3 EB 78 */	mr r3, r29
/* 802CD3B4 002C9F94  4B FA 60 A1 */	bl it_80273454
/* 802CD3B8 002C9F98  83 DD 00 2C */	lwz r30, 0x2c(r29)
/* 802CD3BC 002C9F9C  38 00 FF FF */	li r0, -1
/* 802CD3C0 002C9FA0  38 7D 00 00 */	addi r3, r29, 0
/* 802CD3C4 002C9FA4  90 1E 0E 34 */	stw r0, 0xe34(r30)
/* 802CD3C8 002C9FA8  38 80 00 01 */	li r4, 1
/* 802CD3CC 002C9FAC  38 A0 00 02 */	li r5, 2
/* 802CD3D0 002C9FB0  4B F9 BA 8D */	bl Item_80268E5C
/* 802CD3D4 002C9FB4  3C 60 80 06 */	lis r3, efLib_PauseAll@ha
/* 802CD3D8 002C9FB8  38 03 BA 40 */	addi r0, r3, efLib_PauseAll@l
/* 802CD3DC 002C9FBC  3C 60 80 06 */	lis r3, efLib_ResumeAll@ha
/* 802CD3E0 002C9FC0  90 1E 0D 28 */	stw r0, 0xd28(r30)
/* 802CD3E4 002C9FC4  38 03 BA C4 */	addi r0, r3, efLib_ResumeAll@l
/* 802CD3E8 002C9FC8  3C 60 80 2D */	lis r3, it_802CD090@ha
/* 802CD3EC 002C9FCC  90 1E 0D 2C */	stw r0, 0xd2c(r30)
/* 802CD3F0 002C9FD0  38 03 D0 90 */	addi r0, r3, it_802CD090@l
/* 802CD3F4 002C9FD4  90 1E 0D 20 */	stw r0, 0xd20(r30)
/* 802CD3F8 002C9FD8  38 60 00 01 */	li r3, 1
/* 802CD3FC 002C9FDC  88 1F 0D D1 */	lbz r0, 0xdd1(r31)
/* 802CD400 002C9FE0  50 60 36 72 */	rlwimi r0, r3, 6, 0x19, 0x19
/* 802CD404 002C9FE4  98 1F 0D D1 */	stb r0, 0xdd1(r31)
.L_802CD408:
/* 802CD408 002C9FE8  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 802CD40C 002C9FEC  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 802CD410 002C9FF0  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 802CD414 002C9FF4  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 802CD418 002C9FF8  38 21 00 28 */	addi r1, r1, 0x28
/* 802CD41C 002C9FFC  7C 08 03 A6 */	mtlr r0
/* 802CD420 002CA000  4E 80 00 20 */	blr

.global it_802CD424
it_802CD424:
/* 802CD424 002CA004  7C 08 02 A6 */	mflr r0
/* 802CD428 002CA008  3C 80 80 2D */	lis r4, it_802CCFFC@ha
/* 802CD42C 002CA00C  90 01 00 04 */	stw r0, 4(r1)
/* 802CD430 002CA010  38 84 CF FC */	addi r4, r4, it_802CCFFC@l
/* 802CD434 002CA014  94 21 FF F8 */	stwu r1, -8(r1)
/* 802CD438 002CA018  4B FA CC E1 */	bl it_8027A118
/* 802CD43C 002CA01C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802CD440 002CA020  38 21 00 08 */	addi r1, r1, 8
/* 802CD444 002CA024  7C 08 03 A6 */	mtlr r0
/* 802CD448 002CA028  4E 80 00 20 */	blr


.section .data
    .balign 8
.global it_803F7C70
it_803F7C70:
    .4byte 0
    .4byte it_802CD360
    .4byte it_802CD384
    .4byte it_802CD424
    .4byte 1
    .4byte it_802CD020
    .4byte it_802CD060
    .4byte it_802CD064
    .4byte 2
    .4byte it_802CD18C
    .4byte it_802CD230
    .4byte it_802CD288


.section .sdata2
    .balign 8
.global it_804DD3B0
it_804DD3B0:
    .4byte 0x00000000
.global it_804DD3B4
it_804DD3B4:
    .4byte 0x3FB33333
