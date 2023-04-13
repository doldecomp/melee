.include "macros.inc"

.section .text, "ax"  # 0x80005940 - 0x803B7240

.global expf
expf:
/* 8000CE50 00009A30  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8000CE54 00009A34  38 A0 00 02 */	li r5, 2
/* 8000CE58 00009A38  C0 02 80 A8 */	lfs f0, lbl_804D7A88@sda21(r2)
/* 8000CE5C 00009A3C  C0 C2 80 98 */	lfs f6, lbl_804D7A78@sda21(r2)
/* 8000CE60 00009A40  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8000CE64 00009A44  40 80 00 10 */	bge lb_8000CE74
/* 8000CE68 00009A48  FC 20 08 50 */	fneg f1, f1
/* 8000CE6C 00009A4C  38 80 00 01 */	li r4, 1
/* 8000CE70 00009A50  48 00 00 08 */	b lb_8000CE78
lb_8000CE74:
/* 8000CE74 00009A54  38 80 00 00 */	li r4, 0
lb_8000CE78:
/* 8000CE78 00009A58  C0 02 80 98 */	lfs f0, lbl_804D7A78@sda21(r2)
/* 8000CE7C 00009A5C  FC 80 08 90 */	fmr f4, f1
/* 8000CE80 00009A60  C8 42 80 A0 */	lfd f2, lbl_804D7A80@sda21(r2)
/* 8000CE84 00009A64  3C 00 43 30 */	lis r0, 0x4330
/* 8000CE88 00009A68  EC 60 08 2A */	fadds f3, f0, f1
lb_8000CE8C:
/* 8000CE8C 00009A6C  7C A3 2B 78 */	mr r3, r5
/* 8000CE90 00009A70  EC 84 00 72 */	fmuls f4, f4, f1
/* 8000CE94 00009A74  6C 63 80 00 */	xoris r3, r3, 0x8000
/* 8000CE98 00009A78  FC A0 18 90 */	fmr f5, f3
/* 8000CE9C 00009A7C  90 61 00 14 */	stw r3, 0x14(r1)
/* 8000CEA0 00009A80  38 A5 00 01 */	addi r5, r5, 1
/* 8000CEA4 00009A84  90 01 00 10 */	stw r0, 0x10(r1)
/* 8000CEA8 00009A88  C8 01 00 10 */	lfd f0, 0x10(r1)
/* 8000CEAC 00009A8C  EC 00 10 28 */	fsubs f0, f0, f2
/* 8000CEB0 00009A90  EC C6 00 32 */	fmuls f6, f6, f0
/* 8000CEB4 00009A94  EC 04 30 24 */	fdivs f0, f4, f6
/* 8000CEB8 00009A98  EC 63 00 2A */	fadds f3, f3, f0
/* 8000CEBC 00009A9C  FC 03 28 00 */	fcmpu cr0, f3, f5
/* 8000CEC0 00009AA0  40 82 FF CC */	bne lb_8000CE8C
/* 8000CEC4 00009AA4  2C 04 00 00 */	cmpwi r4, 0
/* 8000CEC8 00009AA8  41 82 00 0C */	beq lb_8000CED4
/* 8000CECC 00009AAC  C0 02 80 98 */	lfs f0, lbl_804D7A78@sda21(r2)
/* 8000CED0 00009AB0  EC 60 18 24 */	fdivs f3, f0, f3
lb_8000CED4:
/* 8000CED4 00009AB4  FC 20 18 90 */	fmr f1, f3
/* 8000CED8 00009AB8  38 21 00 18 */	addi r1, r1, 0x18
/* 8000CEDC 00009ABC  4E 80 00 20 */	blr

.global powf
powf:
/* 8000CEE0 00009AC0  7C 08 02 A6 */	mflr r0
/* 8000CEE4 00009AC4  90 01 00 04 */	stw r0, 4(r1)
/* 8000CEE8 00009AC8  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8000CEEC 00009ACC  C0 02 80 A8 */	lfs f0, lbl_804D7A88@sda21(r2)
/* 8000CEF0 00009AD0  FC 00 08 00 */	fcmpu cr0, f0, f1
/* 8000CEF4 00009AD4  40 82 00 0C */	bne lb_8000CF00
/* 8000CEF8 00009AD8  FC 20 00 90 */	fmr f1, f0
/* 8000CEFC 00009ADC  48 00 00 68 */	b lb_8000CF64
lb_8000CF00:
/* 8000CF00 00009AE0  C0 02 80 98 */	lfs f0, lbl_804D7A78@sda21(r2)
/* 8000CF04 00009AE4  38 80 00 01 */	li r4, 1
/* 8000CF08 00009AE8  C8 62 80 A0 */	lfd f3, lbl_804D7A80@sda21(r2)
/* 8000CF0C 00009AEC  3C 00 43 30 */	lis r0, 0x4330
/* 8000CF10 00009AF0  EC 81 00 28 */	fsubs f4, f1, f0
/* 8000CF14 00009AF4  EC 00 08 2A */	fadds f0, f0, f1
/* 8000CF18 00009AF8  EC C4 00 24 */	fdivs f6, f4, f0
/* 8000CF1C 00009AFC  FC 80 30 90 */	fmr f4, f6
/* 8000CF20 00009B00  EC A6 01 B2 */	fmuls f5, f6, f6
lb_8000CF24:
/* 8000CF24 00009B04  38 84 00 02 */	addi r4, r4, 2
/* 8000CF28 00009B08  EC C6 01 72 */	fmuls f6, f6, f5
/* 8000CF2C 00009B0C  6C 83 80 00 */	xoris r3, r4, 0x8000
/* 8000CF30 00009B10  FC 20 20 90 */	fmr f1, f4
/* 8000CF34 00009B14  90 61 00 14 */	stw r3, 0x14(r1)
/* 8000CF38 00009B18  90 01 00 10 */	stw r0, 0x10(r1)
/* 8000CF3C 00009B1C  C8 01 00 10 */	lfd f0, 0x10(r1)
/* 8000CF40 00009B20  EC 00 18 28 */	fsubs f0, f0, f3
/* 8000CF44 00009B24  EC 06 00 24 */	fdivs f0, f6, f0
/* 8000CF48 00009B28  EC 84 00 2A */	fadds f4, f4, f0
/* 8000CF4C 00009B2C  FC 04 08 00 */	fcmpu cr0, f4, f1
/* 8000CF50 00009B30  40 82 FF D4 */	bne lb_8000CF24
/* 8000CF54 00009B34  C0 02 80 9C */	lfs f0, lbl_804D7A7C@sda21(r2)
/* 8000CF58 00009B38  EC 00 01 32 */	fmuls f0, f0, f4
/* 8000CF5C 00009B3C  EC 22 00 32 */	fmuls f1, f2, f0
/* 8000CF60 00009B40  4B FF FE F1 */	bl expf
lb_8000CF64:
/* 8000CF64 00009B44  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8000CF68 00009B48  38 21 00 18 */	addi r1, r1, 0x18
/* 8000CF6C 00009B4C  7C 08 03 A6 */	mtlr r0
/* 8000CF70 00009B50  4E 80 00 20 */	blr

.global lb_8000CF74
lb_8000CF74:
/* 8000CF74 00009B54  2C 03 00 00 */	cmpwi r3, 0
/* 8000CF78 00009B58  40 82 00 0C */	bne lb_8000CF84
/* 8000CF7C 00009B5C  38 60 00 00 */	li r3, 0
/* 8000CF80 00009B60  4E 80 00 20 */	blr
lb_8000CF84:
/* 8000CF84 00009B64  2C 04 00 00 */	cmpwi r4, 0
/* 8000CF88 00009B68  41 80 00 78 */	blt lb_8000D000
/* 8000CF8C 00009B6C  38 C0 00 00 */	li r6, 0
/* 8000CF90 00009B70  38 E0 00 01 */	li r7, 1
/* 8000CF94 00009B74  40 81 00 64 */	ble lb_8000CFF8
/* 8000CF98 00009B78  2C 04 00 08 */	cmpwi r4, 8
/* 8000CF9C 00009B7C  38 A4 FF F8 */	addi r5, r4, -8
/* 8000CFA0 00009B80  40 81 00 40 */	ble lb_8000CFE0
/* 8000CFA4 00009B84  38 05 00 07 */	addi r0, r5, 7
/* 8000CFA8 00009B88  54 00 E8 FE */	srwi r0, r0, 3
/* 8000CFAC 00009B8C  2C 05 00 00 */	cmpwi r5, 0
/* 8000CFB0 00009B90  7C 09 03 A6 */	mtctr r0
/* 8000CFB4 00009B94  40 81 00 2C */	ble lb_8000CFE0
lb_8000CFB8:
/* 8000CFB8 00009B98  7C E7 19 D6 */	mullw r7, r7, r3
/* 8000CFBC 00009B9C  7C E7 19 D6 */	mullw r7, r7, r3
/* 8000CFC0 00009BA0  7C E7 19 D6 */	mullw r7, r7, r3
/* 8000CFC4 00009BA4  7C E7 19 D6 */	mullw r7, r7, r3
/* 8000CFC8 00009BA8  7C E7 19 D6 */	mullw r7, r7, r3
/* 8000CFCC 00009BAC  7C E7 19 D6 */	mullw r7, r7, r3
/* 8000CFD0 00009BB0  7C E7 19 D6 */	mullw r7, r7, r3
/* 8000CFD4 00009BB4  7C E7 19 D6 */	mullw r7, r7, r3
/* 8000CFD8 00009BB8  38 C6 00 08 */	addi r6, r6, 8
/* 8000CFDC 00009BBC  42 00 FF DC */	bdnz lb_8000CFB8
lb_8000CFE0:
/* 8000CFE0 00009BC0  7C 06 20 50 */	subf r0, r6, r4
/* 8000CFE4 00009BC4  7C 06 20 00 */	cmpw r6, r4
/* 8000CFE8 00009BC8  7C 09 03 A6 */	mtctr r0
/* 8000CFEC 00009BCC  40 80 00 0C */	bge lb_8000CFF8
lb_8000CFF0:
/* 8000CFF0 00009BD0  7C E7 19 D6 */	mullw r7, r7, r3
/* 8000CFF4 00009BD4  42 00 FF FC */	bdnz lb_8000CFF0
lb_8000CFF8:
/* 8000CFF8 00009BD8  7C E3 3B 78 */	mr r3, r7
/* 8000CFFC 00009BDC  4E 80 00 20 */	blr
lb_8000D000:
/* 8000D000 00009BE0  38 60 00 00 */	li r3, 0
/* 8000D004 00009BE4  4E 80 00 20 */	blr

.global lb_8000D008
lb_8000D008:
/* 8000D008 00009BE8  7C 08 02 A6 */	mflr r0
/* 8000D00C 00009BEC  90 01 00 04 */	stw r0, 4(r1)
/* 8000D010 00009BF0  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8000D014 00009BF4  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8000D018 00009BF8  C0 02 80 C0 */	lfs f0, lbl_804D7AA0@sda21(r2)
/* 8000D01C 00009BFC  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 8000D020 00009C00  40 80 00 18 */	bge lb_8000D038
/* 8000D024 00009C04  C0 02 80 C4 */	lfs f0, lbl_804D7AA4@sda21(r2)
/* 8000D028 00009C08  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 8000D02C 00009C0C  40 81 00 0C */	ble lb_8000D038
/* 8000D030 00009C10  38 00 00 01 */	li r0, 1
/* 8000D034 00009C14  48 00 00 08 */	b lb_8000D03C
lb_8000D038:
/* 8000D038 00009C18  38 00 00 00 */	li r0, 0
lb_8000D03C:
/* 8000D03C 00009C1C  2C 00 00 00 */	cmpwi r0, 0
/* 8000D040 00009C20  41 82 00 7C */	beq lb_8000D0BC
/* 8000D044 00009C24  C0 02 80 C0 */	lfs f0, lbl_804D7AA0@sda21(r2)
/* 8000D048 00009C28  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8000D04C 00009C2C  40 80 00 18 */	bge lb_8000D064
/* 8000D050 00009C30  C0 02 80 C4 */	lfs f0, lbl_804D7AA4@sda21(r2)
/* 8000D054 00009C34  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8000D058 00009C38  40 81 00 0C */	ble lb_8000D064
/* 8000D05C 00009C3C  38 00 00 01 */	li r0, 1
/* 8000D060 00009C40  48 00 00 08 */	b lb_8000D068
lb_8000D064:
/* 8000D064 00009C44  38 00 00 00 */	li r0, 0
lb_8000D068:
/* 8000D068 00009C48  2C 00 00 00 */	cmpwi r0, 0
/* 8000D06C 00009C4C  41 82 00 0C */	beq lb_8000D078
/* 8000D070 00009C50  C0 22 80 A8 */	lfs f1, lbl_804D7A88@sda21(r2)
/* 8000D074 00009C54  48 00 00 C0 */	b lb_8000D134
lb_8000D078:
/* 8000D078 00009C58  C0 02 80 A8 */	lfs f0, lbl_804D7A88@sda21(r2)
/* 8000D07C 00009C5C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8000D080 00009C60  40 80 00 0C */	bge lb_8000D08C
/* 8000D084 00009C64  38 00 FF FF */	li r0, -1
/* 8000D088 00009C68  48 00 00 08 */	b lb_8000D090
lb_8000D08C:
/* 8000D08C 00009C6C  38 00 00 01 */	li r0, 1
lb_8000D090:
/* 8000D090 00009C70  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 8000D094 00009C74  C8 22 80 A0 */	lfd f1, lbl_804D7A80@sda21(r2)
/* 8000D098 00009C78  90 01 00 14 */	stw r0, 0x14(r1)
/* 8000D09C 00009C7C  3C 00 43 30 */	lis r0, 0x4330
/* 8000D0A0 00009C80  C8 42 80 88 */	lfd f2, lbl_804D7A68@sda21(r2)
/* 8000D0A4 00009C84  90 01 00 10 */	stw r0, 0x10(r1)
/* 8000D0A8 00009C88  C8 01 00 10 */	lfd f0, 0x10(r1)
/* 8000D0AC 00009C8C  FC 00 08 28 */	fsub f0, f0, f1
/* 8000D0B0 00009C90  FC 22 00 32 */	fmul f1, f2, f0
/* 8000D0B4 00009C94  FC 20 08 18 */	frsp f1, f1
/* 8000D0B8 00009C98  48 00 00 7C */	b lb_8000D134
lb_8000D0BC:
/* 8000D0BC 00009C9C  C0 02 80 A8 */	lfs f0, lbl_804D7A88@sda21(r2)
/* 8000D0C0 00009CA0  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 8000D0C4 00009CA4  40 81 00 10 */	ble lb_8000D0D4
/* 8000D0C8 00009CA8  EC 21 10 24 */	fdivs f1, f1, f2
/* 8000D0CC 00009CAC  48 01 5D 9D */	bl atanf
/* 8000D0D0 00009CB0  48 00 00 64 */	b lb_8000D134
lb_8000D0D4:
/* 8000D0D4 00009CB4  40 80 00 60 */	bge lb_8000D134
/* 8000D0D8 00009CB8  EC 41 10 24 */	fdivs f2, f1, f2
/* 8000D0DC 00009CBC  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 8000D0E0 00009CC0  40 80 00 08 */	bge lb_8000D0E8
/* 8000D0E4 00009CC4  FC 40 10 50 */	fneg f2, f2
lb_8000D0E8:
/* 8000D0E8 00009CC8  C0 02 80 A8 */	lfs f0, lbl_804D7A88@sda21(r2)
/* 8000D0EC 00009CCC  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8000D0F0 00009CD0  40 80 00 0C */	bge lb_8000D0FC
/* 8000D0F4 00009CD4  3B E0 FF FF */	li r31, -1
/* 8000D0F8 00009CD8  48 00 00 08 */	b lb_8000D100
lb_8000D0FC:
/* 8000D0FC 00009CDC  3B E0 00 01 */	li r31, 1
lb_8000D100:
/* 8000D100 00009CE0  FC 20 10 90 */	fmr f1, f2
/* 8000D104 00009CE4  48 01 5D 65 */	bl atanf
/* 8000D108 00009CE8  6F E0 80 00 */	xoris r0, r31, 0x8000
/* 8000D10C 00009CEC  C8 02 80 90 */	lfd f0, lbl_804D7A70@sda21(r2)
/* 8000D110 00009CF0  90 01 00 14 */	stw r0, 0x14(r1)
/* 8000D114 00009CF4  3C 00 43 30 */	lis r0, 0x4330
/* 8000D118 00009CF8  C8 42 80 A0 */	lfd f2, lbl_804D7A80@sda21(r2)
/* 8000D11C 00009CFC  FC 20 08 28 */	fsub f1, f0, f1
/* 8000D120 00009D00  90 01 00 10 */	stw r0, 0x10(r1)
/* 8000D124 00009D04  C8 01 00 10 */	lfd f0, 0x10(r1)
/* 8000D128 00009D08  FC 00 10 28 */	fsub f0, f0, f2
/* 8000D12C 00009D0C  FC 20 00 72 */	fmul f1, f0, f1
/* 8000D130 00009D10  FC 20 08 18 */	frsp f1, f1
lb_8000D134:
/* 8000D134 00009D14  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8000D138 00009D18  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8000D13C 00009D1C  38 21 00 20 */	addi r1, r1, 0x20
/* 8000D140 00009D20  7C 08 03 A6 */	mtlr r0
/* 8000D144 00009D24  4E 80 00 20 */	blr

.global lb_8000D148
lb_8000D148:
/* 8000D148 00009D28  ED 02 20 28 */	fsubs f8, f2, f4
/* 8000D14C 00009D2C  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 8000D150 00009D30  ED 22 00 F2 */	fmuls f9, f2, f3
/* 8000D154 00009D34  DB E1 00 28 */	stfd f31, 0x28(r1)
/* 8000D158 00009D38  EC 03 08 28 */	fsubs f0, f3, f1
/* 8000D15C 00009D3C  ED 68 02 32 */	fmuls f11, f8, f8
/* 8000D160 00009D40  C1 42 80 C0 */	lfs f10, lbl_804D7AA0@sda21(r2)
/* 8000D164 00009D44  ED 21 49 38 */	fmsubs f9, f1, f4, f9
/* 8000D168 00009D48  ED 60 58 3A */	fmadds f11, f0, f0, f11
/* 8000D16C 00009D4C  FC 0B 50 40 */	fcmpo cr0, f11, f10
/* 8000D170 00009D50  FF E0 58 90 */	fmr f31, f11
/* 8000D174 00009D54  40 80 00 0C */	bge lb_8000D180
/* 8000D178 00009D58  38 60 00 00 */	li r3, 0
/* 8000D17C 00009D5C  48 00 01 64 */	b lb_8000D2E0
lb_8000D180:
/* 8000D180 00009D60  C1 42 80 A8 */	lfs f10, lbl_804D7A88@sda21(r2)
/* 8000D184 00009D64  FC 1F 50 40 */	fcmpo cr0, f31, f10
/* 8000D188 00009D68  40 81 00 54 */	ble lb_8000D1DC
/* 8000D18C 00009D6C  FD 60 F8 34 */	frsqrte f11, f31
/* 8000D190 00009D70  C9 A2 80 B0 */	lfd f13, lbl_804D7A90@sda21(r2)
/* 8000D194 00009D74  C9 82 80 B8 */	lfd f12, lbl_804D7A98@sda21(r2)
/* 8000D198 00009D78  FD 4B 02 F2 */	fmul f10, f11, f11
/* 8000D19C 00009D7C  FD 6D 02 F2 */	fmul f11, f13, f11
/* 8000D1A0 00009D80  FD 5F 62 BC */	fnmsub f10, f31, f10, f12
/* 8000D1A4 00009D84  FD 6B 02 B2 */	fmul f11, f11, f10
/* 8000D1A8 00009D88  FD 4B 02 F2 */	fmul f10, f11, f11
/* 8000D1AC 00009D8C  FD 6D 02 F2 */	fmul f11, f13, f11
/* 8000D1B0 00009D90  FD 5F 62 BC */	fnmsub f10, f31, f10, f12
/* 8000D1B4 00009D94  FD 6B 02 B2 */	fmul f11, f11, f10
/* 8000D1B8 00009D98  FD 4B 02 F2 */	fmul f10, f11, f11
/* 8000D1BC 00009D9C  FD 6D 02 F2 */	fmul f11, f13, f11
/* 8000D1C0 00009DA0  FD 5F 62 BC */	fnmsub f10, f31, f10, f12
/* 8000D1C4 00009DA4  FD 4B 02 B2 */	fmul f10, f11, f10
/* 8000D1C8 00009DA8  FD 5F 02 B2 */	fmul f10, f31, f10
/* 8000D1CC 00009DAC  FD 40 50 18 */	frsp f10, f10
/* 8000D1D0 00009DB0  D1 41 00 24 */	stfs f10, 0x24(r1)
/* 8000D1D4 00009DB4  C1 61 00 24 */	lfs f11, 0x24(r1)
/* 8000D1D8 00009DB8  48 00 00 08 */	b lb_8000D1E0
lb_8000D1DC:
/* 8000D1DC 00009DBC  FD 60 F8 90 */	fmr f11, f31
lb_8000D1E0:
/* 8000D1E0 00009DC0  ED 48 01 B2 */	fmuls f10, f8, f6
/* 8000D1E4 00009DC4  C1 02 80 A8 */	lfs f8, lbl_804D7A88@sda21(r2)
/* 8000D1E8 00009DC8  EC 00 51 7A */	fmadds f0, f0, f5, f10
/* 8000D1EC 00009DCC  EC 09 00 2A */	fadds f0, f9, f0
/* 8000D1F0 00009DD0  FC 00 40 40 */	fcmpo cr0, f0, f8
/* 8000D1F4 00009DD4  40 80 00 08 */	bge lb_8000D1FC
/* 8000D1F8 00009DD8  FC 00 00 50 */	fneg f0, f0
lb_8000D1FC:
/* 8000D1FC 00009DDC  EC 00 58 24 */	fdivs f0, f0, f11
/* 8000D200 00009DE0  FC 00 38 40 */	fcmpo cr0, f0, f7
/* 8000D204 00009DE4  4C 40 13 82 */	cror 2, 0, 2
/* 8000D208 00009DE8  40 82 00 D4 */	bne lb_8000D2DC
/* 8000D20C 00009DEC  ED 01 28 28 */	fsubs f8, f1, f5
/* 8000D210 00009DF0  EC 02 30 28 */	fsubs f0, f2, f6
/* 8000D214 00009DF4  ED 43 28 28 */	fsubs f10, f3, f5
/* 8000D218 00009DF8  ED 08 02 32 */	fmuls f8, f8, f8
/* 8000D21C 00009DFC  EC 00 00 32 */	fmuls f0, f0, f0
/* 8000D220 00009E00  ED 24 30 28 */	fsubs f9, f4, f6
/* 8000D224 00009E04  ED 67 01 F2 */	fmuls f11, f7, f7
/* 8000D228 00009E08  ED 08 00 2A */	fadds f8, f8, f0
/* 8000D22C 00009E0C  EC EA 02 B2 */	fmuls f7, f10, f10
/* 8000D230 00009E10  EC 09 02 72 */	fmuls f0, f9, f9
/* 8000D234 00009E14  FC 08 58 40 */	fcmpo cr0, f8, f11
/* 8000D238 00009E18  EC 07 00 2A */	fadds f0, f7, f0
/* 8000D23C 00009E1C  40 80 00 28 */	bge lb_8000D264
/* 8000D240 00009E20  FC 00 58 40 */	fcmpo cr0, f0, f11
/* 8000D244 00009E24  40 81 00 0C */	ble lb_8000D250
/* 8000D248 00009E28  38 60 00 01 */	li r3, 1
/* 8000D24C 00009E2C  48 00 00 94 */	b lb_8000D2E0
lb_8000D250:
/* 8000D250 00009E30  40 80 00 0C */	bge lb_8000D25C
/* 8000D254 00009E34  38 60 00 00 */	li r3, 0
/* 8000D258 00009E38  48 00 00 88 */	b lb_8000D2E0
lb_8000D25C:
/* 8000D25C 00009E3C  38 60 00 01 */	li r3, 1
/* 8000D260 00009E40  48 00 00 80 */	b lb_8000D2E0
lb_8000D264:
/* 8000D264 00009E44  40 81 00 70 */	ble lb_8000D2D4
/* 8000D268 00009E48  FC 00 58 40 */	fcmpo cr0, f0, f11
/* 8000D26C 00009E4C  40 81 00 54 */	ble lb_8000D2C0
/* 8000D270 00009E50  FC 01 28 40 */	fcmpo cr0, f1, f5
/* 8000D274 00009E54  40 81 00 0C */	ble lb_8000D280
/* 8000D278 00009E58  FC 03 28 40 */	fcmpo cr0, f3, f5
/* 8000D27C 00009E5C  41 80 00 34 */	blt lb_8000D2B0
lb_8000D280:
/* 8000D280 00009E60  FC 01 28 40 */	fcmpo cr0, f1, f5
/* 8000D284 00009E64  40 80 00 0C */	bge lb_8000D290
/* 8000D288 00009E68  FC 03 28 40 */	fcmpo cr0, f3, f5
/* 8000D28C 00009E6C  41 81 00 24 */	bgt lb_8000D2B0
lb_8000D290:
/* 8000D290 00009E70  FC 02 30 40 */	fcmpo cr0, f2, f6
/* 8000D294 00009E74  40 81 00 0C */	ble lb_8000D2A0
/* 8000D298 00009E78  FC 04 30 40 */	fcmpo cr0, f4, f6
/* 8000D29C 00009E7C  41 80 00 14 */	blt lb_8000D2B0
lb_8000D2A0:
/* 8000D2A0 00009E80  FC 02 30 40 */	fcmpo cr0, f2, f6
/* 8000D2A4 00009E84  40 80 00 14 */	bge lb_8000D2B8
/* 8000D2A8 00009E88  FC 04 30 40 */	fcmpo cr0, f4, f6
/* 8000D2AC 00009E8C  40 81 00 0C */	ble lb_8000D2B8
lb_8000D2B0:
/* 8000D2B0 00009E90  38 60 00 01 */	li r3, 1
/* 8000D2B4 00009E94  48 00 00 2C */	b lb_8000D2E0
lb_8000D2B8:
/* 8000D2B8 00009E98  38 60 00 00 */	li r3, 0
/* 8000D2BC 00009E9C  48 00 00 24 */	b lb_8000D2E0
lb_8000D2C0:
/* 8000D2C0 00009EA0  40 80 00 0C */	bge lb_8000D2CC
/* 8000D2C4 00009EA4  38 60 00 01 */	li r3, 1
/* 8000D2C8 00009EA8  48 00 00 18 */	b lb_8000D2E0
lb_8000D2CC:
/* 8000D2CC 00009EAC  38 60 00 01 */	li r3, 1
/* 8000D2D0 00009EB0  48 00 00 10 */	b lb_8000D2E0
lb_8000D2D4:
/* 8000D2D4 00009EB4  38 60 00 01 */	li r3, 1
/* 8000D2D8 00009EB8  48 00 00 08 */	b lb_8000D2E0
lb_8000D2DC:
/* 8000D2DC 00009EBC  38 60 00 00 */	li r3, 0
lb_8000D2E0:
/* 8000D2E0 00009EC0  CB E1 00 28 */	lfd f31, 0x28(r1)
/* 8000D2E4 00009EC4  38 21 00 30 */	addi r1, r1, 0x30
/* 8000D2E8 00009EC8  4E 80 00 20 */	blr


.section .sdata2
    .balign 8
.global lbl_804D7A68
lbl_804D7A68:
    .4byte 0x3FF921FB
    .4byte 0x54442D18
.global lbl_804D7A70
lbl_804D7A70:
    .4byte 0x400921FB
    .4byte 0x54442D18
.global lbl_804D7A78
lbl_804D7A78:
    .4byte 0x3F800000
.global lbl_804D7A7C
lbl_804D7A7C:
    .4byte 0x40000000
.global lbl_804D7A80
lbl_804D7A80:
    .4byte 0x43300000
    .4byte 0x80000000
.global lbl_804D7A88
lbl_804D7A88:
    .4byte 0x00000000
    .4byte 0x00000000
.global lbl_804D7A90
lbl_804D7A90:
    .4byte 0x3FE00000
    .4byte 0x00000000
.global lbl_804D7A98
lbl_804D7A98:
    .4byte 0x40080000
    .4byte 0x00000000
.global lbl_804D7AA0
lbl_804D7AA0:
    .4byte 0x3727C5AC
.global lbl_804D7AA4
lbl_804D7AA4:
    .4byte 0xB727C5AC
