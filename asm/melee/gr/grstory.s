.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240

.global func_801E302C
func_801E302C:
/* 801E302C 001DFC0C  4E 80 00 20 */	blr 

.global func_801E3030
func_801E3030:
/* 801E3030 001DFC10  7C 08 02 A6 */	mflr r0
/* 801E3034 001DFC14  90 01 00 04 */	stw r0, 4(r1)
/* 801E3038 001DFC18  94 21 FF F8 */	stwu r1, -8(r1)
/* 801E303C 001DFC1C  4B FE 19 BD */	bl func_801C49F8
/* 801E3040 001DFC20  3C 80 80 4A */	lis r4, lbl_8049E6C8@ha
/* 801E3044 001DFC24  90 6D B3 18 */	stw r3, lbl_804D69B8@sda21(r13)
/* 801E3048 001DFC28  38 64 E6 C8 */	addi r3, r4, lbl_8049E6C8@l
/* 801E304C 001DFC2C  38 A3 00 8C */	addi r5, r3, 0x8c
/* 801E3050 001DFC30  88 03 00 8C */	lbz r0, 0x8c(r3)
/* 801E3054 001DFC34  38 60 00 00 */	li r3, 0
/* 801E3058 001DFC38  50 60 1F 38 */	rlwimi r0, r3, 3, 0x1c, 0x1c
/* 801E305C 001DFC3C  98 05 00 00 */	stb r0, 0(r5)
/* 801E3060 001DFC40  38 80 00 01 */	li r4, 1
/* 801E3064 001DFC44  38 60 00 00 */	li r3, 0
/* 801E3068 001DFC48  88 05 00 00 */	lbz r0, 0(r5)
/* 801E306C 001DFC4C  50 80 17 7A */	rlwimi r0, r4, 2, 0x1d, 0x1d
/* 801E3070 001DFC50  98 05 00 00 */	stb r0, 0(r5)
/* 801E3074 001DFC54  48 00 00 65 */	bl func_801E30D8
/* 801E3078 001DFC58  38 60 00 01 */	li r3, 1
/* 801E307C 001DFC5C  48 00 00 5D */	bl func_801E30D8
/* 801E3080 001DFC60  38 60 00 03 */	li r3, 3
/* 801E3084 001DFC64  48 00 00 55 */	bl func_801E30D8
/* 801E3088 001DFC68  38 60 00 02 */	li r3, 2
/* 801E308C 001DFC6C  48 00 00 4D */	bl func_801E30D8
/* 801E3090 001DFC70  4B FE 09 31 */	bl func_801C39C0
/* 801E3094 001DFC74  4B FE 0B 21 */	bl func_801C3BB4
/* 801E3098 001DFC78  80 01 00 0C */	lwz r0, 0xc(r1)
/* 801E309C 001DFC7C  38 21 00 08 */	addi r1, r1, 8
/* 801E30A0 001DFC80  7C 08 03 A6 */	mtlr r0
/* 801E30A4 001DFC84  4E 80 00 20 */	blr 
/* 801E30A8 001DFC88  4E 80 00 20 */	blr 
/* 801E30AC 001DFC8C  7C 08 02 A6 */	mflr r0
/* 801E30B0 001DFC90  38 60 00 00 */	li r3, 0
/* 801E30B4 001DFC94  90 01 00 04 */	stw r0, 4(r1)
/* 801E30B8 001DFC98  94 21 FF F8 */	stwu r1, -8(r1)
/* 801E30BC 001DFC9C  4B FE 7D 49 */	bl func_801CAE04
/* 801E30C0 001DFCA0  80 01 00 0C */	lwz r0, 0xc(r1)
/* 801E30C4 001DFCA4  38 21 00 08 */	addi r1, r1, 8
/* 801E30C8 001DFCA8  7C 08 03 A6 */	mtlr r0
/* 801E30CC 001DFCAC  4E 80 00 20 */	blr 
/* 801E30D0 001DFCB0  38 60 00 00 */	li r3, 0
/* 801E30D4 001DFCB4  4E 80 00 20 */	blr 

.global func_801E30D8
func_801E30D8:
/* 801E30D8 001DFCB8  7C 08 02 A6 */	mflr r0
/* 801E30DC 001DFCBC  90 01 00 04 */	stw r0, 4(r1)
/* 801E30E0 001DFCC0  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 801E30E4 001DFCC4  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 801E30E8 001DFCC8  93 C1 00 18 */	stw r30, 0x18(r1)
/* 801E30EC 001DFCCC  93 A1 00 14 */	stw r29, 0x14(r1)
/* 801E30F0 001DFCD0  93 81 00 10 */	stw r28, 0x10(r1)
/* 801E30F4 001DFCD4  3B 83 00 00 */	addi r28, r3, 0
/* 801E30F8 001DFCD8  1C 1C 00 14 */	mulli r0, r28, 0x14
/* 801E30FC 001DFCDC  3C 60 80 3E */	lis r3, lbl_803E26F0@ha
/* 801E3100 001DFCE0  3B E3 26 F0 */	addi r31, r3, lbl_803E26F0@l
/* 801E3104 001DFCE4  38 7C 00 00 */	addi r3, r28, 0
/* 801E3108 001DFCE8  7F BF 02 14 */	add r29, r31, r0
/* 801E310C 001DFCEC  4B FD E3 C5 */	bl func_801C14D0
/* 801E3110 001DFCF0  7C 7E 1B 79 */	or. r30, r3, r3
/* 801E3114 001DFCF4  41 82 00 70 */	beq lbl_801E3184
/* 801E3118 001DFCF8  83 FE 00 2C */	lwz r31, 0x2c(r30)
/* 801E311C 001DFCFC  38 00 00 00 */	li r0, 0
/* 801E3120 001DFD00  3C 60 80 1C */	lis r3, func_801C5DB0@ha
/* 801E3124 001DFD04  90 1F 00 08 */	stw r0, 8(r31)
/* 801E3128 001DFD08  38 83 5D B0 */	addi r4, r3, func_801C5DB0@l
/* 801E312C 001DFD0C  38 7E 00 00 */	addi r3, r30, 0
/* 801E3130 001DFD10  90 1F 00 0C */	stw r0, 0xc(r31)
/* 801E3134 001DFD14  38 A0 00 03 */	li r5, 3
/* 801E3138 001DFD18  38 C0 00 00 */	li r6, 0
/* 801E313C 001DFD1C  48 1A D5 61 */	bl func_8039069C
/* 801E3140 001DFD20  80 1D 00 0C */	lwz r0, 0xc(r29)
/* 801E3144 001DFD24  28 00 00 00 */	cmplwi r0, 0
/* 801E3148 001DFD28  41 82 00 08 */	beq lbl_801E3150
/* 801E314C 001DFD2C  90 1F 00 1C */	stw r0, 0x1c(r31)
lbl_801E3150:
/* 801E3150 001DFD30  81 9D 00 00 */	lwz r12, 0(r29)
/* 801E3154 001DFD34  28 0C 00 00 */	cmplwi r12, 0
/* 801E3158 001DFD38  41 82 00 10 */	beq lbl_801E3168
/* 801E315C 001DFD3C  7D 88 03 A6 */	mtlr r12
/* 801E3160 001DFD40  38 7E 00 00 */	addi r3, r30, 0
/* 801E3164 001DFD44  4E 80 00 21 */	blrl 
lbl_801E3168:
/* 801E3168 001DFD48  80 9D 00 08 */	lwz r4, 8(r29)
/* 801E316C 001DFD4C  28 04 00 00 */	cmplwi r4, 0
/* 801E3170 001DFD50  41 82 00 2C */	beq lbl_801E319C
/* 801E3174 001DFD54  38 7E 00 00 */	addi r3, r30, 0
/* 801E3178 001DFD58  38 A0 00 04 */	li r5, 4
/* 801E317C 001DFD5C  48 1A CB D9 */	bl func_8038FD54
/* 801E3180 001DFD60  48 00 00 1C */	b lbl_801E319C
lbl_801E3184:
/* 801E3184 001DFD64  38 DC 00 00 */	addi r6, r28, 0
/* 801E3188 001DFD68  4C C6 31 82 */	crclr 6
/* 801E318C 001DFD6C  38 7F 00 90 */	addi r3, r31, 0x90
/* 801E3190 001DFD70  38 9F 00 B4 */	addi r4, r31, 0xb4
/* 801E3194 001DFD74  38 A0 00 DC */	li r5, 0xdc
/* 801E3198 001DFD78  48 16 25 11 */	bl OSReport
lbl_801E319C:
/* 801E319C 001DFD7C  7F C3 F3 78 */	mr r3, r30
/* 801E31A0 001DFD80  80 01 00 24 */	lwz r0, 0x24(r1)
/* 801E31A4 001DFD84  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 801E31A8 001DFD88  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 801E31AC 001DFD8C  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 801E31B0 001DFD90  83 81 00 10 */	lwz r28, 0x10(r1)
/* 801E31B4 001DFD94  38 21 00 20 */	addi r1, r1, 0x20
/* 801E31B8 001DFD98  7C 08 03 A6 */	mtlr r0
/* 801E31BC 001DFD9C  4E 80 00 20 */	blr 
/* 801E31C0 001DFDA0  7C 08 02 A6 */	mflr r0
/* 801E31C4 001DFDA4  38 A0 00 00 */	li r5, 0
/* 801E31C8 001DFDA8  90 01 00 04 */	stw r0, 4(r1)
/* 801E31CC 001DFDAC  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 801E31D0 001DFDB0  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 801E31D4 001DFDB4  93 C1 00 18 */	stw r30, 0x18(r1)
/* 801E31D8 001DFDB8  7C 7E 1B 78 */	mr r30, r3
/* 801E31DC 001DFDBC  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 801E31E0 001DFDC0  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 801E31E4 001DFDC4  4B FE 4F 55 */	bl func_801C8138
/* 801E31E8 001DFDC8  88 1F 00 11 */	lbz r0, 0x11(r31)
/* 801E31EC 001DFDCC  38 60 00 02 */	li r3, 2
/* 801E31F0 001DFDD0  50 60 2E 34 */	rlwimi r0, r3, 5, 0x18, 0x1a
/* 801E31F4 001DFDD4  98 1F 00 11 */	stb r0, 0x11(r31)
/* 801E31F8 001DFDD8  38 7E 00 00 */	addi r3, r30, 0
/* 801E31FC 001DFDDC  38 80 00 01 */	li r4, 1
/* 801E3200 001DFDE0  4B FE 0D A5 */	bl func_801C3FA4
/* 801E3204 001DFDE4  3C 80 20 00 */	lis r4, 0x2000
/* 801E3208 001DFDE8  4B FE 56 51 */	bl func_801C8858
/* 801E320C 001DFDEC  80 01 00 24 */	lwz r0, 0x24(r1)
/* 801E3210 001DFDF0  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 801E3214 001DFDF4  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 801E3218 001DFDF8  38 21 00 20 */	addi r1, r1, 0x20
/* 801E321C 001DFDFC  7C 08 03 A6 */	mtlr r0
/* 801E3220 001DFE00  4E 80 00 20 */	blr 
/* 801E3224 001DFE04  38 60 00 00 */	li r3, 0
/* 801E3228 001DFE08  4E 80 00 20 */	blr 
/* 801E322C 001DFE0C  4E 80 00 20 */	blr 
/* 801E3230 001DFE10  4E 80 00 20 */	blr 
/* 801E3234 001DFE14  7C 08 02 A6 */	mflr r0
/* 801E3238 001DFE18  90 01 00 04 */	stw r0, 4(r1)
/* 801E323C 001DFE1C  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 801E3240 001DFE20  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 801E3244 001DFE24  93 C1 00 28 */	stw r30, 0x28(r1)
/* 801E3248 001DFE28  7C 7E 1B 78 */	mr r30, r3
/* 801E324C 001DFE2C  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 801E3250 001DFE30  80 63 00 28 */	lwz r3, 0x28(r3)
/* 801E3254 001DFE34  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 801E3258 001DFE38  4B FD FC 79 */	bl func_801C2ED0
/* 801E325C 001DFE3C  C0 22 B8 90 */	lfs f1, lbl_804DB270@sda21(r2)
/* 801E3260 001DFE40  7F C3 F3 78 */	mr r3, r30
/* 801E3264 001DFE44  C0 42 B8 94 */	lfs f2, lbl_804DB274@sda21(r2)
/* 801E3268 001DFE48  38 80 00 00 */	li r4, 0
/* 801E326C 001DFE4C  38 A0 00 07 */	li r5, 7
/* 801E3270 001DFE50  38 C0 00 00 */	li r6, 0
/* 801E3274 001DFE54  4B FE 4D 85 */	bl func_801C7FF8
/* 801E3278 001DFE58  C0 22 B8 90 */	lfs f1, lbl_804DB270@sda21(r2)
/* 801E327C 001DFE5C  7F C3 F3 78 */	mr r3, r30
/* 801E3280 001DFE60  C0 42 B8 94 */	lfs f2, lbl_804DB274@sda21(r2)
/* 801E3284 001DFE64  38 80 00 05 */	li r4, 5
/* 801E3288 001DFE68  38 A0 00 07 */	li r5, 7
/* 801E328C 001DFE6C  38 C0 00 01 */	li r6, 1
/* 801E3290 001DFE70  4B FE 4D 69 */	bl func_801C7FF8
/* 801E3294 001DFE74  80 6D B3 18 */	lwz r3, lbl_804D69B8@sda21(r13)
/* 801E3298 001DFE78  C0 03 00 04 */	lfs f0, 4(r3)
/* 801E329C 001DFE7C  FC 00 00 1E */	fctiwz f0, f0
/* 801E32A0 001DFE80  D8 01 00 18 */	stfd f0, 0x18(r1)
/* 801E32A4 001DFE84  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 801E32A8 001DFE88  D8 01 00 20 */	stfd f0, 0x20(r1)
/* 801E32AC 001DFE8C  2C 00 00 00 */	cmpwi r0, 0
/* 801E32B0 001DFE90  80 61 00 24 */	lwz r3, 0x24(r1)
/* 801E32B4 001DFE94  41 82 00 0C */	beq lbl_801E32C0
/* 801E32B8 001DFE98  48 19 D2 C9 */	bl HSD_Randi
/* 801E32BC 001DFE9C  48 00 00 08 */	b lbl_801E32C4
lbl_801E32C0:
/* 801E32C0 001DFEA0  38 60 00 00 */	li r3, 0
lbl_801E32C4:
/* 801E32C4 001DFEA4  6C 60 80 00 */	xoris r0, r3, 0x8000
/* 801E32C8 001DFEA8  80 8D B3 18 */	lwz r4, lbl_804D69B8@sda21(r13)
/* 801E32CC 001DFEAC  90 01 00 1C */	stw r0, 0x1c(r1)
/* 801E32D0 001DFEB0  3C 60 43 30 */	lis r3, 0x4330
/* 801E32D4 001DFEB4  C8 22 B8 98 */	lfd f1, lbl_804DB278@sda21(r2)
/* 801E32D8 001DFEB8  38 00 00 78 */	li r0, 0x78
/* 801E32DC 001DFEBC  90 61 00 18 */	stw r3, 0x18(r1)
/* 801E32E0 001DFEC0  C0 44 00 00 */	lfs f2, 0(r4)
/* 801E32E4 001DFEC4  38 60 00 01 */	li r3, 1
/* 801E32E8 001DFEC8  C8 01 00 18 */	lfd f0, 0x18(r1)
/* 801E32EC 001DFECC  EC 00 08 28 */	fsubs f0, f0, f1
/* 801E32F0 001DFED0  EC 02 00 2A */	fadds f0, f2, f0
/* 801E32F4 001DFED4  FC 00 00 1E */	fctiwz f0, f0
/* 801E32F8 001DFED8  D8 01 00 20 */	stfd f0, 0x20(r1)
/* 801E32FC 001DFEDC  80 81 00 24 */	lwz r4, 0x24(r1)
/* 801E3300 001DFEE0  90 9F 00 C8 */	stw r4, 0xc8(r31)
/* 801E3304 001DFEE4  90 1F 00 C8 */	stw r0, 0xc8(r31)
/* 801E3308 001DFEE8  88 1F 00 10 */	lbz r0, 0x10(r31)
/* 801E330C 001DFEEC  50 60 17 7A */	rlwimi r0, r3, 2, 0x1d, 0x1d
/* 801E3310 001DFEF0  98 1F 00 10 */	stb r0, 0x10(r31)
/* 801E3314 001DFEF4  80 01 00 34 */	lwz r0, 0x34(r1)
/* 801E3318 001DFEF8  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 801E331C 001DFEFC  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 801E3320 001DFF00  38 21 00 30 */	addi r1, r1, 0x30
/* 801E3324 001DFF04  7C 08 03 A6 */	mtlr r0
/* 801E3328 001DFF08  4E 80 00 20 */	blr 
/* 801E332C 001DFF0C  38 60 00 00 */	li r3, 0
/* 801E3330 001DFF10  4E 80 00 20 */	blr 
/* 801E3334 001DFF14  7C 08 02 A6 */	mflr r0
/* 801E3338 001DFF18  90 01 00 04 */	stw r0, 4(r1)
/* 801E333C 001DFF1C  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 801E3340 001DFF20  93 E1 00 14 */	stw r31, 0x14(r1)
/* 801E3344 001DFF24  7C 7F 1B 78 */	mr r31, r3
/* 801E3348 001DFF28  48 00 00 D1 */	bl func_801E3418
/* 801E334C 001DFF2C  7F E3 FB 78 */	mr r3, r31
/* 801E3350 001DFF30  4B FD FC 91 */	bl func_801C2FE0
/* 801E3354 001DFF34  4B E2 E2 A1 */	bl func_800115F4
/* 801E3358 001DFF38  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 801E335C 001DFF3C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 801E3360 001DFF40  38 21 00 18 */	addi r1, r1, 0x18
/* 801E3364 001DFF44  7C 08 03 A6 */	mtlr r0
/* 801E3368 001DFF48  4E 80 00 20 */	blr 
/* 801E336C 001DFF4C  4E 80 00 20 */	blr 
/* 801E3370 001DFF50  7C 08 02 A6 */	mflr r0
/* 801E3374 001DFF54  90 01 00 04 */	stw r0, 4(r1)
/* 801E3378 001DFF58  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 801E337C 001DFF5C  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 801E3380 001DFF60  93 C1 00 18 */	stw r30, 0x18(r1)
/* 801E3384 001DFF64  7C 7E 1B 78 */	mr r30, r3
/* 801E3388 001DFF68  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 801E338C 001DFF6C  80 63 00 28 */	lwz r3, 0x28(r3)
/* 801E3390 001DFF70  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 801E3394 001DFF74  4B FD FB 3D */	bl func_801C2ED0
/* 801E3398 001DFF78  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 801E339C 001DFF7C  38 7E 00 00 */	addi r3, r30, 0
/* 801E33A0 001DFF80  38 A0 00 00 */	li r5, 0
/* 801E33A4 001DFF84  4B FE 4D 95 */	bl func_801C8138
/* 801E33A8 001DFF88  38 00 00 00 */	li r0, 0
/* 801E33AC 001DFF8C  B0 1F 00 C4 */	sth r0, 0xc4(r31)
/* 801E33B0 001DFF90  38 7E 00 00 */	addi r3, r30, 0
/* 801E33B4 001DFF94  38 80 00 01 */	li r4, 1
/* 801E33B8 001DFF98  4B FE 0B ED */	bl func_801C3FA4
/* 801E33BC 001DFF9C  90 7F 00 C8 */	stw r3, 0xc8(r31)
/* 801E33C0 001DFFA0  80 01 00 24 */	lwz r0, 0x24(r1)
/* 801E33C4 001DFFA4  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 801E33C8 001DFFA8  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 801E33CC 001DFFAC  38 21 00 20 */	addi r1, r1, 0x20
/* 801E33D0 001DFFB0  7C 08 03 A6 */	mtlr r0
/* 801E33D4 001DFFB4  4E 80 00 20 */	blr 
/* 801E33D8 001DFFB8  38 60 00 00 */	li r3, 0
/* 801E33DC 001DFFBC  4E 80 00 20 */	blr 
/* 801E33E0 001DFFC0  7C 08 02 A6 */	mflr r0
/* 801E33E4 001DFFC4  90 01 00 04 */	stw r0, 4(r1)
/* 801E33E8 001DFFC8  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 801E33EC 001DFFCC  93 E1 00 14 */	stw r31, 0x14(r1)
/* 801E33F0 001DFFD0  7C 7F 1B 78 */	mr r31, r3
/* 801E33F4 001DFFD4  4B FD FB ED */	bl func_801C2FE0
/* 801E33F8 001DFFD8  7F E3 FB 78 */	mr r3, r31
/* 801E33FC 001DFFDC  48 00 02 71 */	bl func_801E366C
/* 801E3400 001DFFE0  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 801E3404 001DFFE4  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 801E3408 001DFFE8  38 21 00 18 */	addi r1, r1, 0x18
/* 801E340C 001DFFEC  7C 08 03 A6 */	mtlr r0
/* 801E3410 001DFFF0  4E 80 00 20 */	blr 
/* 801E3414 001DFFF4  4E 80 00 20 */	blr 

.global func_801E3418
func_801E3418:
/* 801E3418 001DFFF8  7C 08 02 A6 */	mflr r0
/* 801E341C 001DFFFC  90 01 00 04 */	stw r0, 4(r1)
/* 801E3420 001E0000  94 21 FF 80 */	stwu r1, -0x80(r1)
/* 801E3424 001E0004  DB E1 00 78 */	stfd f31, 0x78(r1)
/* 801E3428 001E0008  DB C1 00 70 */	stfd f30, 0x70(r1)
/* 801E342C 001E000C  DB A1 00 68 */	stfd f29, 0x68(r1)
/* 801E3430 001E0010  DB 81 00 60 */	stfd f28, 0x60(r1)
/* 801E3434 001E0014  DB 61 00 58 */	stfd f27, 0x58(r1)
/* 801E3438 001E0018  BF 61 00 44 */	stmw r27, 0x44(r1)
/* 801E343C 001E001C  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 801E3440 001E0020  38 60 00 D2 */	li r3, 0xd2
/* 801E3444 001E0024  48 08 7F 7D */	bl func_8026B3C0
/* 801E3448 001E0028  2C 03 00 00 */	cmpwi r3, 0
/* 801E344C 001E002C  40 82 01 F8 */	bne lbl_801E3644
/* 801E3450 001E0030  80 7E 00 C8 */	lwz r3, 0xc8(r30)
/* 801E3454 001E0034  2C 03 00 00 */	cmpwi r3, 0
/* 801E3458 001E0038  41 82 00 10 */	beq lbl_801E3468
/* 801E345C 001E003C  38 03 FF FF */	addi r0, r3, -1
/* 801E3460 001E0040  90 1E 00 C8 */	stw r0, 0xc8(r30)
/* 801E3464 001E0044  48 00 01 E0 */	b lbl_801E3644
lbl_801E3468:
/* 801E3468 001E0048  80 6D B3 18 */	lwz r3, lbl_804D69B8@sda21(r13)
/* 801E346C 001E004C  C0 03 00 04 */	lfs f0, 4(r3)
/* 801E3470 001E0050  FC 00 00 1E */	fctiwz f0, f0
/* 801E3474 001E0054  D8 01 00 30 */	stfd f0, 0x30(r1)
/* 801E3478 001E0058  80 01 00 34 */	lwz r0, 0x34(r1)
/* 801E347C 001E005C  D8 01 00 38 */	stfd f0, 0x38(r1)
/* 801E3480 001E0060  2C 00 00 00 */	cmpwi r0, 0
/* 801E3484 001E0064  80 61 00 3C */	lwz r3, 0x3c(r1)
/* 801E3488 001E0068  41 82 00 0C */	beq lbl_801E3494
/* 801E348C 001E006C  48 19 D0 F5 */	bl HSD_Randi
/* 801E3490 001E0070  48 00 00 08 */	b lbl_801E3498
lbl_801E3494:
/* 801E3494 001E0074  38 60 00 00 */	li r3, 0
lbl_801E3498:
/* 801E3498 001E0078  6C 60 80 00 */	xoris r0, r3, 0x8000
/* 801E349C 001E007C  80 8D B3 18 */	lwz r4, lbl_804D69B8@sda21(r13)
/* 801E34A0 001E0080  90 01 00 34 */	stw r0, 0x34(r1)
/* 801E34A4 001E0084  3C 60 43 30 */	lis r3, 0x4330
/* 801E34A8 001E0088  C8 22 B8 98 */	lfd f1, lbl_804DB278@sda21(r2)
/* 801E34AC 001E008C  38 00 00 78 */	li r0, 0x78
/* 801E34B0 001E0090  90 61 00 30 */	stw r3, 0x30(r1)
/* 801E34B4 001E0094  C0 44 00 00 */	lfs f2, 0(r4)
/* 801E34B8 001E0098  C8 01 00 30 */	lfd f0, 0x30(r1)
/* 801E34BC 001E009C  EC 00 08 28 */	fsubs f0, f0, f1
/* 801E34C0 001E00A0  EC 02 00 2A */	fadds f0, f2, f0
/* 801E34C4 001E00A4  FC 00 00 1E */	fctiwz f0, f0
/* 801E34C8 001E00A8  D8 01 00 38 */	stfd f0, 0x38(r1)
/* 801E34CC 001E00AC  80 61 00 3C */	lwz r3, 0x3c(r1)
/* 801E34D0 001E00B0  90 7E 00 C8 */	stw r3, 0xc8(r30)
/* 801E34D4 001E00B4  90 1E 00 C8 */	stw r0, 0xc8(r30)
lbl_801E34D8:
/* 801E34D8 001E00B8  38 60 00 06 */	li r3, 6
/* 801E34DC 001E00BC  48 19 D0 A5 */	bl HSD_Randi
/* 801E34E0 001E00C0  88 1E 00 C5 */	lbz r0, 0xc5(r30)
/* 801E34E4 001E00C4  7C 00 07 74 */	extsb r0, r0
/* 801E34E8 001E00C8  7C 00 18 00 */	cmpw r0, r3
/* 801E34EC 001E00CC  41 82 FF EC */	beq lbl_801E34D8
/* 801E34F0 001E00D0  7C 60 07 74 */	extsb r0, r3
/* 801E34F4 001E00D4  2C 03 00 03 */	cmpwi r3, 3
/* 801E34F8 001E00D8  98 1E 00 C5 */	stb r0, 0xc5(r30)
/* 801E34FC 001E00DC  40 80 00 10 */	bge lbl_801E350C
/* 801E3500 001E00E0  C0 02 B8 A0 */	lfs f0, lbl_804DB280@sda21(r2)
/* 801E3504 001E00E4  D0 01 00 20 */	stfs f0, 0x20(r1)
/* 801E3508 001E00E8  48 00 00 0C */	b lbl_801E3514
lbl_801E350C:
/* 801E350C 001E00EC  C0 02 B8 A4 */	lfs f0, lbl_804DB284@sda21(r2)
/* 801E3510 001E00F0  D0 01 00 20 */	stfs f0, 0x20(r1)
lbl_801E3514:
/* 801E3514 001E00F4  80 0D B3 18 */	lwz r0, lbl_804D69B8@sda21(r13)
/* 801E3518 001E00F8  54 7F 10 3A */	slwi r31, r3, 2
/* 801E351C 001E00FC  7C 60 FA 14 */	add r3, r0, r31
/* 801E3520 001E0100  C0 03 00 0C */	lfs f0, 0xc(r3)
/* 801E3524 001E0104  38 60 00 03 */	li r3, 3
/* 801E3528 001E0108  D0 01 00 24 */	stfs f0, 0x24(r1)
/* 801E352C 001E010C  C0 02 B8 A8 */	lfs f0, lbl_804DB288@sda21(r2)
/* 801E3530 001E0110  D0 01 00 28 */	stfs f0, 0x28(r1)
/* 801E3534 001E0114  48 19 D0 4D */	bl HSD_Randi
/* 801E3538 001E0118  80 8D B3 18 */	lwz r4, lbl_804D69B8@sda21(r13)
/* 801E353C 001E011C  7C 7D 1B 78 */	mr r29, r3
/* 801E3540 001E0120  C0 04 00 08 */	lfs f0, 8(r4)
/* 801E3544 001E0124  FC 00 00 1E */	fctiwz f0, f0
/* 801E3548 001E0128  D8 01 00 38 */	stfd f0, 0x38(r1)
/* 801E354C 001E012C  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 801E3550 001E0130  D8 01 00 30 */	stfd f0, 0x30(r1)
/* 801E3554 001E0134  2C 00 00 00 */	cmpwi r0, 0
/* 801E3558 001E0138  80 61 00 34 */	lwz r3, 0x34(r1)
/* 801E355C 001E013C  41 82 00 0C */	beq lbl_801E3568
/* 801E3560 001E0140  48 19 D0 21 */	bl HSD_Randi
/* 801E3564 001E0144  48 00 00 08 */	b lbl_801E356C
lbl_801E3568:
/* 801E3568 001E0148  38 60 00 00 */	li r3, 0
lbl_801E356C:
/* 801E356C 001E014C  2C 03 00 00 */	cmpwi r3, 0
/* 801E3570 001E0150  40 82 00 18 */	bne lbl_801E3588
/* 801E3574 001E0154  38 60 00 03 */	li r3, 3
/* 801E3578 001E0158  48 19 D0 09 */	bl HSD_Randi
/* 801E357C 001E015C  38 03 00 03 */	addi r0, r3, 3
/* 801E3580 001E0160  98 1E 00 C4 */	stb r0, 0xc4(r30)
/* 801E3584 001E0164  48 00 00 0C */	b lbl_801E3590
lbl_801E3588:
/* 801E3588 001E0168  38 00 00 01 */	li r0, 1
/* 801E358C 001E016C  98 1E 00 C4 */	stb r0, 0xc4(r30)
lbl_801E3590:
/* 801E3590 001E0170  38 60 00 02 */	li r3, 2
/* 801E3594 001E0174  48 19 CF ED */	bl HSD_Randi
/* 801E3598 001E0178  2C 03 00 00 */	cmpwi r3, 0
/* 801E359C 001E017C  40 82 00 18 */	bne lbl_801E35B4
/* 801E35A0 001E0180  38 60 00 03 */	li r3, 3
/* 801E35A4 001E0184  48 19 CF DD */	bl HSD_Randi
/* 801E35A8 001E0188  38 03 00 03 */	addi r0, r3, 3
/* 801E35AC 001E018C  98 1E 00 C4 */	stb r0, 0xc4(r30)
/* 801E35B0 001E0190  48 00 00 0C */	b lbl_801E35BC
lbl_801E35B4:
/* 801E35B4 001E0194  38 00 00 01 */	li r0, 1
/* 801E35B8 001E0198  98 1E 00 C4 */	stb r0, 0xc4(r30)
lbl_801E35BC:
/* 801E35BC 001E019C  C3 62 B8 AC */	lfs f27, lbl_804DB28C@sda21(r2)
/* 801E35C0 001E01A0  3B 60 00 00 */	li r27, 0
/* 801E35C4 001E01A4  CB 82 B8 98 */	lfd f28, lbl_804DB278@sda21(r2)
/* 801E35C8 001E01A8  3F 80 43 30 */	lis r28, 0x4330
/* 801E35CC 001E01AC  C3 A2 B8 B0 */	lfs f29, lbl_804DB290@sda21(r2)
/* 801E35D0 001E01B0  C3 C2 B8 A8 */	lfs f30, lbl_804DB288@sda21(r2)
/* 801E35D4 001E01B4  C3 E2 B8 B4 */	lfs f31, lbl_804DB294@sda21(r2)
/* 801E35D8 001E01B8  48 00 00 5C */	b lbl_801E3634
lbl_801E35DC:
/* 801E35DC 001E01BC  6F 60 80 00 */	xoris r0, r27, 0x8000
/* 801E35E0 001E01C0  90 01 00 34 */	stw r0, 0x34(r1)
/* 801E35E4 001E01C4  38 7B 00 00 */	addi r3, r27, 0
/* 801E35E8 001E01C8  38 BD 00 00 */	addi r5, r29, 0
/* 801E35EC 001E01CC  93 81 00 30 */	stw r28, 0x30(r1)
/* 801E35F0 001E01D0  38 81 00 20 */	addi r4, r1, 0x20
/* 801E35F4 001E01D4  C8 01 00 30 */	lfd f0, 0x30(r1)
/* 801E35F8 001E01D8  EC 00 E0 28 */	fsubs f0, f0, f28
/* 801E35FC 001E01DC  EC 1B 00 32 */	fmuls f0, f27, f0
/* 801E3600 001E01E0  FC 00 00 1E */	fctiwz f0, f0
/* 801E3604 001E01E4  D8 01 00 38 */	stfd f0, 0x38(r1)
/* 801E3608 001E01E8  80 C1 00 3C */	lwz r6, 0x3c(r1)
/* 801E360C 001E01EC  48 0F 50 0D */	bl func_802D8618
/* 801E3610 001E01F0  48 19 CF 19 */	bl HSD_Randf
/* 801E3614 001E01F4  EC 01 E8 28 */	fsubs f0, f1, f29
/* 801E3618 001E01F8  80 6D B3 18 */	lwz r3, lbl_804D69B8@sda21(r13)
/* 801E361C 001E01FC  3B 7B 00 01 */	addi r27, r27, 1
/* 801E3620 001E0200  38 03 00 0C */	addi r0, r3, 0xc
/* 801E3624 001E0204  EC 3E 00 32 */	fmuls f1, f30, f0
/* 801E3628 001E0208  7C 1F 04 2E */	lfsx f0, r31, r0
/* 801E362C 001E020C  EC 1F 00 7A */	fmadds f0, f31, f1, f0
/* 801E3630 001E0210  D0 01 00 24 */	stfs f0, 0x24(r1)
lbl_801E3634:
/* 801E3634 001E0214  88 1E 00 C4 */	lbz r0, 0xc4(r30)
/* 801E3638 001E0218  7C 00 07 74 */	extsb r0, r0
/* 801E363C 001E021C  7C 1B 00 00 */	cmpw r27, r0
/* 801E3640 001E0220  41 80 FF 9C */	blt lbl_801E35DC
lbl_801E3644:
/* 801E3644 001E0224  BB 61 00 44 */	lmw r27, 0x44(r1)
/* 801E3648 001E0228  80 01 00 84 */	lwz r0, 0x84(r1)
/* 801E364C 001E022C  CB E1 00 78 */	lfd f31, 0x78(r1)
/* 801E3650 001E0230  CB C1 00 70 */	lfd f30, 0x70(r1)
/* 801E3654 001E0234  CB A1 00 68 */	lfd f29, 0x68(r1)
/* 801E3658 001E0238  CB 81 00 60 */	lfd f28, 0x60(r1)
/* 801E365C 001E023C  CB 61 00 58 */	lfd f27, 0x58(r1)
/* 801E3660 001E0240  38 21 00 80 */	addi r1, r1, 0x80
/* 801E3664 001E0244  7C 08 03 A6 */	mtlr r0
/* 801E3668 001E0248  4E 80 00 20 */	blr 

.global func_801E366C
func_801E366C:
/* 801E366C 001E024C  7C 08 02 A6 */	mflr r0
/* 801E3670 001E0250  90 01 00 04 */	stw r0, 4(r1)
/* 801E3674 001E0254  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 801E3678 001E0258  93 E1 00 14 */	stw r31, 0x14(r1)
/* 801E367C 001E025C  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 801E3680 001E0260  A8 9F 00 C4 */	lha r4, 0xc4(r31)
/* 801E3684 001E0264  38 64 FF FF */	addi r3, r4, -1
/* 801E3688 001E0268  7C 80 07 35 */	extsh. r0, r4
/* 801E368C 001E026C  B0 7F 00 C4 */	sth r3, 0xc4(r31)
/* 801E3690 001E0270  40 80 00 2C */	bge lbl_801E36BC
/* 801E3694 001E0274  80 BF 00 C8 */	lwz r5, 0xc8(r31)
/* 801E3698 001E0278  28 05 00 00 */	cmplwi r5, 0
/* 801E369C 001E027C  41 82 00 20 */	beq lbl_801E36BC
/* 801E36A0 001E0280  38 60 00 2C */	li r3, 0x2c
/* 801E36A4 001E0284  38 80 00 00 */	li r4, 0
/* 801E36A8 001E0288  4B FE 61 35 */	bl func_801C97DC
/* 801E36AC 001E028C  38 60 00 14 */	li r3, 0x14
/* 801E36B0 001E0290  48 19 CE D1 */	bl HSD_Randi
/* 801E36B4 001E0294  38 03 00 0A */	addi r0, r3, 0xa
/* 801E36B8 001E0298  B0 1F 00 C4 */	sth r0, 0xc4(r31)
lbl_801E36BC:
/* 801E36BC 001E029C  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 801E36C0 001E02A0  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 801E36C4 001E02A4  38 21 00 18 */	addi r1, r1, 0x18
/* 801E36C8 001E02A8  7C 08 03 A6 */	mtlr r0
/* 801E36CC 001E02AC  4E 80 00 20 */	blr 
/* 801E36D0 001E02B0  38 60 00 00 */	li r3, 0
/* 801E36D4 001E02B4  4E 80 00 20 */	blr 
/* 801E36D8 001E02B8  7C 08 02 A6 */	mflr r0
/* 801E36DC 001E02BC  38 80 00 00 */	li r4, 0
/* 801E36E0 001E02C0  90 01 00 04 */	stw r0, 4(r1)
/* 801E36E4 001E02C4  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 801E36E8 001E02C8  93 E1 00 24 */	stw r31, 0x24(r1)
/* 801E36EC 001E02CC  3B E3 00 00 */	addi r31, r3, 0
/* 801E36F0 001E02D0  38 65 00 00 */	addi r3, r5, 0
/* 801E36F4 001E02D4  38 A1 00 14 */	addi r5, r1, 0x14
/* 801E36F8 001E02D8  4B E2 7A D5 */	bl func_8000B1CC
/* 801E36FC 001E02DC  C0 42 B8 94 */	lfs f2, lbl_804DB274@sda21(r2)
/* 801E3700 001E02E0  C0 3F 00 04 */	lfs f1, 4(r31)
/* 801E3704 001E02E4  C0 01 00 18 */	lfs f0, 0x18(r1)
/* 801E3708 001E02E8  EC 22 08 2A */	fadds f1, f2, f1
/* 801E370C 001E02EC  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 801E3710 001E02F0  40 81 00 0C */	ble lbl_801E371C
/* 801E3714 001E02F4  38 60 00 01 */	li r3, 1
/* 801E3718 001E02F8  48 00 00 08 */	b lbl_801E3720
lbl_801E371C:
/* 801E371C 001E02FC  38 60 00 00 */	li r3, 0
lbl_801E3720:
/* 801E3720 001E0300  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 801E3724 001E0304  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 801E3728 001E0308  38 21 00 28 */	addi r1, r1, 0x28
/* 801E372C 001E030C  7C 08 03 A6 */	mtlr r0
/* 801E3730 001E0310  4E 80 00 20 */	blr 
