.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240

.global HSD_PerfInitStat
HSD_PerfInitStat:
/* 8037E1BC 0037AD9C  7C 08 02 A6 */	mflr r0
/* 8037E1C0 0037ADA0  3C 60 80 40 */	lis r3, lbl_80407188@ha
/* 8037E1C4 0037ADA4  90 01 00 04 */	stw r0, 4(r1)
/* 8037E1C8 0037ADA8  38 C3 71 88 */	addi r6, r3, lbl_80407188@l
/* 8037E1CC 0037ADAC  38 00 00 12 */	li r0, 0x12
/* 8037E1D0 0037ADB0  94 21 FF F8 */	stwu r1, -8(r1)
/* 8037E1D4 0037ADB4  7C 09 03 A6 */	mtctr r0
/* 8037E1D8 0037ADB8  38 A6 FF F8 */	addi r5, r6, -8
/* 8037E1DC 0037ADBC  38 86 00 88 */	addi r4, r6, 0x88
lbl_8037E1E0:
/* 8037E1E0 0037ADC0  84 64 00 08 */	lwzu r3, 8(r4)
/* 8037E1E4 0037ADC4  80 04 00 04 */	lwz r0, 4(r4)
/* 8037E1E8 0037ADC8  94 65 00 08 */	stwu r3, 8(r5)
/* 8037E1EC 0037ADCC  90 05 00 04 */	stw r0, 4(r5)
/* 8037E1F0 0037ADD0  42 00 FF F0 */	bdnz lbl_8037E1E0
/* 8037E1F4 0037ADD4  38 66 00 90 */	addi r3, r6, 0x90
/* 8037E1F8 0037ADD8  38 80 00 00 */	li r4, 0
/* 8037E1FC 0037ADDC  38 A0 00 90 */	li r5, 0x90
/* 8037E200 0037ADE0  4B C8 4F 01 */	bl memset
/* 8037E204 0037ADE4  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8037E208 0037ADE8  38 21 00 08 */	addi r1, r1, 8
/* 8037E20C 0037ADEC  7C 08 03 A6 */	mtlr r0
/* 8037E210 0037ADF0  4E 80 00 20 */	blr 

.global HSD_PerfSetStartTime
HSD_PerfSetStartTime:
/* 8037E214 0037ADF4  7C 08 02 A6 */	mflr r0
/* 8037E218 0037ADF8  90 01 00 04 */	stw r0, 4(r1)
/* 8037E21C 0037ADFC  94 21 FF F8 */	stwu r1, -8(r1)
/* 8037E220 0037AE00  4B FC E1 D1 */	bl OSGetTime
/* 8037E224 0037AE04  90 8D C0 5C */	stw r4, lbl_804D76FC@sda21(r13)
/* 8037E228 0037AE08  90 6D C0 58 */	stw r3, lbl_804D76F8@sda21(r13)
/* 8037E22C 0037AE0C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8037E230 0037AE10  38 21 00 08 */	addi r1, r1, 8
/* 8037E234 0037AE14  7C 08 03 A6 */	mtlr r0
/* 8037E238 0037AE18  4E 80 00 20 */	blr 

.global HSD_PerfSetCPUTime
HSD_PerfSetCPUTime:
/* 8037E23C 0037AE1C  7C 08 02 A6 */	mflr r0
/* 8037E240 0037AE20  90 01 00 04 */	stw r0, 4(r1)
/* 8037E244 0037AE24  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8037E248 0037AE28  4B FC E1 A9 */	bl OSGetTime
/* 8037E24C 0037AE2C  80 AD C0 5C */	lwz r5, lbl_804D76FC@sda21(r13)
/* 8037E250 0037AE30  80 0D C0 58 */	lwz r0, lbl_804D76F8@sda21(r13)
/* 8037E254 0037AE34  7C 85 20 10 */	subfc r4, r5, r4
/* 8037E258 0037AE38  7C 60 19 10 */	subfe r3, r0, r3
/* 8037E25C 0037AE3C  4B FA 4B 45 */	bl __cvt_sll_flt
/* 8037E260 0037AE40  3C 60 80 00 */	lis r3, 0x800000F8@ha
/* 8037E264 0037AE44  C8 42 ED 38 */	lfd f2, lbl_804DE718@sda21(r2)
/* 8037E268 0037AE48  80 03 00 F8 */	lwz r0, 0x800000F8@l(r3)
/* 8037E26C 0037AE4C  3C 80 88 89 */	lis r4, 0x88888889@ha
/* 8037E270 0037AE50  38 84 88 89 */	addi r4, r4, 0x88888889@l
/* 8037E274 0037AE54  54 00 F0 BE */	srwi r0, r0, 2
/* 8037E278 0037AE58  7C 04 00 16 */	mulhwu r0, r4, r0
/* 8037E27C 0037AE5C  54 00 D9 7E */	srwi r0, r0, 5
/* 8037E280 0037AE60  90 01 00 0C */	stw r0, 0xc(r1)
/* 8037E284 0037AE64  3C 00 43 30 */	lis r0, 0x4330
/* 8037E288 0037AE68  3C 60 80 40 */	lis r3, lbl_80407218@ha
/* 8037E28C 0037AE6C  90 01 00 08 */	stw r0, 8(r1)
/* 8037E290 0037AE70  C8 01 00 08 */	lfd f0, 8(r1)
/* 8037E294 0037AE74  EC 00 10 28 */	fsubs f0, f0, f2
/* 8037E298 0037AE78  EC 01 00 24 */	fdivs f0, f1, f0
/* 8037E29C 0037AE7C  D0 03 72 18 */	stfs f0, lbl_80407218@l(r3)
/* 8037E2A0 0037AE80  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8037E2A4 0037AE84  38 21 00 10 */	addi r1, r1, 0x10
/* 8037E2A8 0037AE88  7C 08 03 A6 */	mtlr r0
/* 8037E2AC 0037AE8C  4E 80 00 20 */	blr 

.global HSD_PerfSetDrawTime
HSD_PerfSetDrawTime:
/* 8037E2B0 0037AE90  7C 08 02 A6 */	mflr r0
/* 8037E2B4 0037AE94  90 01 00 04 */	stw r0, 4(r1)
/* 8037E2B8 0037AE98  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8037E2BC 0037AE9C  4B FC E1 35 */	bl OSGetTime
/* 8037E2C0 0037AEA0  80 AD C0 5C */	lwz r5, lbl_804D76FC@sda21(r13)
/* 8037E2C4 0037AEA4  80 0D C0 58 */	lwz r0, lbl_804D76F8@sda21(r13)
/* 8037E2C8 0037AEA8  7C 85 20 10 */	subfc r4, r5, r4
/* 8037E2CC 0037AEAC  7C 60 19 10 */	subfe r3, r0, r3
/* 8037E2D0 0037AEB0  4B FA 4A D1 */	bl __cvt_sll_flt
/* 8037E2D4 0037AEB4  3C 60 80 00 */	lis r3, 0x800000F8@ha
/* 8037E2D8 0037AEB8  C8 42 ED 38 */	lfd f2, lbl_804DE718@sda21(r2)
/* 8037E2DC 0037AEBC  80 03 00 F8 */	lwz r0, 0x800000F8@l(r3)
/* 8037E2E0 0037AEC0  3C 80 88 89 */	lis r4, 0x88888889@ha
/* 8037E2E4 0037AEC4  3C 60 80 40 */	lis r3, lbl_80407218@ha
/* 8037E2E8 0037AEC8  54 00 F0 BE */	srwi r0, r0, 2
/* 8037E2EC 0037AECC  38 84 88 89 */	addi r4, r4, 0x88888889@l
/* 8037E2F0 0037AED0  7C 04 00 16 */	mulhwu r0, r4, r0
/* 8037E2F4 0037AED4  54 00 D9 7E */	srwi r0, r0, 5
/* 8037E2F8 0037AED8  90 01 00 0C */	stw r0, 0xc(r1)
/* 8037E2FC 0037AEDC  3C 00 43 30 */	lis r0, 0x4330
/* 8037E300 0037AEE0  38 63 72 18 */	addi r3, r3, lbl_80407218@l
/* 8037E304 0037AEE4  90 01 00 08 */	stw r0, 8(r1)
/* 8037E308 0037AEE8  C8 01 00 08 */	lfd f0, 8(r1)
/* 8037E30C 0037AEEC  EC 00 10 28 */	fsubs f0, f0, f2
/* 8037E310 0037AEF0  EC 01 00 24 */	fdivs f0, f1, f0
/* 8037E314 0037AEF4  D0 03 00 04 */	stfs f0, 4(r3)
/* 8037E318 0037AEF8  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8037E31C 0037AEFC  38 21 00 10 */	addi r1, r1, 0x10
/* 8037E320 0037AF00  7C 08 03 A6 */	mtlr r0
/* 8037E324 0037AF04  4E 80 00 20 */	blr 

.global HSD_PerfSetTotalTime
HSD_PerfSetTotalTime:
/* 8037E328 0037AF08  7C 08 02 A6 */	mflr r0
/* 8037E32C 0037AF0C  90 01 00 04 */	stw r0, 4(r1)
/* 8037E330 0037AF10  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8037E334 0037AF14  4B FC E0 BD */	bl OSGetTime
/* 8037E338 0037AF18  80 AD C0 5C */	lwz r5, lbl_804D76FC@sda21(r13)
/* 8037E33C 0037AF1C  80 0D C0 58 */	lwz r0, lbl_804D76F8@sda21(r13)
/* 8037E340 0037AF20  7C 85 20 10 */	subfc r4, r5, r4
/* 8037E344 0037AF24  7C 60 19 10 */	subfe r3, r0, r3
/* 8037E348 0037AF28  4B FA 4A 59 */	bl __cvt_sll_flt
/* 8037E34C 0037AF2C  3C 60 80 00 */	lis r3, 0x800000F8@ha
/* 8037E350 0037AF30  C8 42 ED 38 */	lfd f2, lbl_804DE718@sda21(r2)
/* 8037E354 0037AF34  80 03 00 F8 */	lwz r0, 0x800000F8@l(r3)
/* 8037E358 0037AF38  3C 80 88 89 */	lis r4, 0x88888889@ha
/* 8037E35C 0037AF3C  3C 60 80 40 */	lis r3, lbl_80407218@ha
/* 8037E360 0037AF40  54 00 F0 BE */	srwi r0, r0, 2
/* 8037E364 0037AF44  38 84 88 89 */	addi r4, r4, 0x88888889@l
/* 8037E368 0037AF48  7C 04 00 16 */	mulhwu r0, r4, r0
/* 8037E36C 0037AF4C  54 00 D9 7E */	srwi r0, r0, 5
/* 8037E370 0037AF50  90 01 00 0C */	stw r0, 0xc(r1)
/* 8037E374 0037AF54  3C 00 43 30 */	lis r0, 0x4330
/* 8037E378 0037AF58  38 63 72 18 */	addi r3, r3, lbl_80407218@l
/* 8037E37C 0037AF5C  90 01 00 08 */	stw r0, 8(r1)
/* 8037E380 0037AF60  C8 01 00 08 */	lfd f0, 8(r1)
/* 8037E384 0037AF64  EC 00 10 28 */	fsubs f0, f0, f2
/* 8037E388 0037AF68  EC 01 00 24 */	fdivs f0, f1, f0
/* 8037E38C 0037AF6C  D0 03 00 08 */	stfs f0, 8(r3)
/* 8037E390 0037AF70  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8037E394 0037AF74  38 21 00 10 */	addi r1, r1, 0x10
/* 8037E398 0037AF78  7C 08 03 A6 */	mtlr r0
/* 8037E39C 0037AF7C  4E 80 00 20 */	blr 

.global HSD_PerfCountEnvelopeBlending
HSD_PerfCountEnvelopeBlending:
/* 8037E3A0 0037AF80  7C 08 02 A6 */	mflr r0
/* 8037E3A4 0037AF84  90 01 00 04 */	stw r0, 4(r1)
/* 8037E3A8 0037AF88  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8037E3AC 0037AF8C  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8037E3B0 0037AF90  3B E3 00 00 */	addi r31, r3, 0
/* 8037E3B4 0037AF94  2C 1F 00 20 */	cmpwi r31, 0x20
/* 8037E3B8 0037AF98  41 80 00 14 */	blt lbl_8037E3CC
/* 8037E3BC 0037AF9C  38 6D A8 98 */	addi r3, r13, lbl_804D5F38@sda21
/* 8037E3C0 0037AFA0  38 80 00 A4 */	li r4, 0xa4
/* 8037E3C4 0037AFA4  38 AD A8 A0 */	addi r5, r13, lbl_804D5F40@sda21
/* 8037E3C8 0037AFA8  48 00 9E 59 */	bl __assert
lbl_8037E3CC:
/* 8037E3CC 0037AFAC  3C 60 80 40 */	lis r3, lbl_80407218@ha
/* 8037E3D0 0037AFB0  38 63 72 18 */	addi r3, r3, lbl_80407218@l
/* 8037E3D4 0037AFB4  57 E0 10 3A */	slwi r0, r31, 2
/* 8037E3D8 0037AFB8  7C 83 02 14 */	add r4, r3, r0
/* 8037E3DC 0037AFBC  80 64 00 10 */	lwz r3, 0x10(r4)
/* 8037E3E0 0037AFC0  38 03 00 01 */	addi r0, r3, 1
/* 8037E3E4 0037AFC4  90 04 00 10 */	stw r0, 0x10(r4)
/* 8037E3E8 0037AFC8  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8037E3EC 0037AFCC  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8037E3F0 0037AFD0  38 21 00 18 */	addi r1, r1, 0x18
/* 8037E3F4 0037AFD4  7C 08 03 A6 */	mtlr r0
/* 8037E3F8 0037AFD8  4E 80 00 20 */	blr 


.section .data
    .balign 8
.global lbl_80407188
lbl_80407188:
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
.global lbl_80407218
lbl_80407218:
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL


.section .sdata
    .balign 8
.global lbl_804D5F38
lbl_804D5F38:
    .asciz "perf.c"
    .balign 4
.global lbl_804D5F40
lbl_804D5F40:
    .asciz "n < 32"
    .balign 4


.section .sbss
    .balign 8
.global lbl_804D76F8
lbl_804D76F8:
	.skip 0x4
.global lbl_804D76FC
lbl_804D76FC:
	.skip 0x4


.section .sdata2
    .balign 8
.global lbl_804DE718
lbl_804DE718:
	.4byte 0x43300000
	.4byte 0x00000000
