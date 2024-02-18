.include "macros.inc"
.file "ftYs_Init.c"

# 0x00000000 - 0x00000948
.text
.balign 4

.fn ftYs_Init_8012B6E8, global
/* 00000000 00000040  7C 08 02 A6 */	mflr r0
/* 00000004 00000044  90 01 00 04 */	stw r0, 0x4(r1)
/* 00000008 00000048  94 21 FF A8 */	stwu r1, -0x58(r1)
/* 0000000C 0000004C  DB E1 00 50 */	stfd f31, 0x50(r1)
/* 00000010 00000050  BF 01 00 30 */	stmw r24, 0x30(r1)
/* 00000014 00000054  7C 7F 1B 78 */	mr r31, r3
/* 00000018 00000058  3B 20 00 00 */	li r25, 0x0
/* 0000001C 0000005C  80 A4 00 04 */	lwz r5, 0x4(r4)
/* 00000020 00000060  3C 80 00 00 */	lis r4, "@242"@ha
/* 00000024 00000064  80 C3 01 0C */	lwz r6, 0x10c(r3)
/* 00000028 00000068  3C 60 00 00 */	lis r3, "@243"@ha
/* 0000002C 0000006C  83 C5 00 0C */	lwz r30, 0xc(r5)
/* 00000030 00000070  83 46 00 04 */	lwz r26, 0x4(r6)
/* 00000034 00000074  3B 65 00 08 */	addi r27, r5, 0x8
/* 00000038 00000078  C3 E0 00 00 */	lfs f31, "@239"@sda21(r0)
/* 0000003C 0000007C  3B 84 00 00 */	addi r28, r4, "@242"@l
/* 00000040 00000080  3B A3 00 00 */	addi r29, r3, "@243"@l
/* 00000044 00000084  48 00 00 B4 */	b .L_000000F8
.L_00000048:
/* 00000048 00000088  88 1E 00 00 */	lbz r0, 0x0(r30)
/* 0000004C 0000008C  80 7F 05 F0 */	lwz r3, 0x5f0(r31)
/* 00000050 00000090  54 00 10 3A */	slwi r0, r0, 2
/* 00000054 00000094  7C 63 00 2E */	lwzx r3, r3, r0
/* 00000058 00000098  28 03 00 00 */	cmplwi r3, 0x0
/* 0000005C 0000009C  41 82 00 0C */	beq .L_00000068
/* 00000060 000000A0  80 63 00 08 */	lwz r3, 0x8(r3)
/* 00000064 000000A4  48 00 00 08 */	b .L_0000006C
.L_00000068:
/* 00000068 000000A8  38 60 00 00 */	li r3, 0x0
.L_0000006C:
/* 0000006C 000000AC  83 03 00 14 */	lwz r24, 0x14(r3)
/* 00000070 000000B0  C0 20 00 00 */	lfs f1, "@239"@sda21(r0)
/* 00000074 000000B4  7F 03 C3 78 */	mr r3, r24
/* 00000078 000000B8  48 00 00 01 */	bl HSD_AObjSetRate
/* 0000007C 000000BC  C0 1A 00 0C */	lfs f0, 0xc(r26)
/* 00000080 000000C0  FC 1F 00 00 */	fcmpu cr0, f31, f0
/* 00000084 000000C4  40 82 00 28 */	bne .L_000000AC
/* 00000088 000000C8  28 18 00 00 */	cmplwi r24, 0x0
/* 0000008C 000000CC  40 82 00 14 */	bne .L_000000A0
/* 00000090 000000D0  38 60 00 00 */	li r3, "@240"@sda21
/* 00000094 000000D4  38 80 00 AA */	li r4, 0xaa
/* 00000098 000000D8  38 A0 00 00 */	li r5, "@241"@sda21
/* 0000009C 000000DC  48 00 00 01 */	bl __assert
.L_000000A0:
/* 000000A0 000000E0  C0 18 00 0C */	lfs f0, 0xc(r24)
/* 000000A4 000000E4  D0 1A 00 0C */	stfs f0, 0xc(r26)
/* 000000A8 000000E8  48 00 00 48 */	b .L_000000F0
.L_000000AC:
/* 000000AC 000000EC  28 18 00 00 */	cmplwi r24, 0x0
/* 000000B0 000000F0  40 82 00 14 */	bne .L_000000C4
/* 000000B4 000000F4  38 60 00 00 */	li r3, "@240"@sda21
/* 000000B8 000000F8  38 80 00 AA */	li r4, 0xaa
/* 000000BC 000000FC  38 A0 00 00 */	li r5, "@241"@sda21
/* 000000C0 00000100  48 00 00 01 */	bl __assert
.L_000000C4:
/* 000000C4 00000104  C0 3A 00 0C */	lfs f1, 0xc(r26)
/* 000000C8 00000108  C0 18 00 0C */	lfs f0, 0xc(r24)
/* 000000CC 0000010C  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 000000D0 00000110  41 82 00 20 */	beq .L_000000F0
/* 000000D4 00000114  38 7C 00 00 */	addi r3, r28, 0x0
/* 000000D8 00000118  4C C6 31 82 */	crclr cr1eq
/* 000000DC 0000011C  48 00 00 01 */	bl OSReport
/* 000000E0 00000120  38 7D 00 00 */	addi r3, r29, 0x0
/* 000000E4 00000124  38 80 00 61 */	li r4, 0x61
/* 000000E8 00000128  38 A0 00 00 */	li r5, "@244"@sda21
/* 000000EC 0000012C  48 00 00 01 */	bl __assert
.L_000000F0:
/* 000000F0 00000130  3B 39 00 01 */	addi r25, r25, 0x1
/* 000000F4 00000134  3B DE 00 01 */	addi r30, r30, 0x1
.L_000000F8:
/* 000000F8 00000138  80 1B 00 00 */	lwz r0, 0x0(r27)
/* 000000FC 0000013C  7C 19 00 00 */	cmpw r25, r0
/* 00000100 00000140  41 80 FF 48 */	blt .L_00000048
/* 00000104 00000144  BB 01 00 30 */	lmw r24, 0x30(r1)
/* 00000108 00000148  80 01 00 5C */	lwz r0, 0x5c(r1)
/* 0000010C 0000014C  CB E1 00 50 */	lfd f31, 0x50(r1)
/* 00000110 00000150  38 21 00 58 */	addi r1, r1, 0x58
/* 00000114 00000154  7C 08 03 A6 */	mtlr r0
/* 00000118 00000158  4E 80 00 20 */	blr
.endfn ftYs_Init_8012B6E8

.fn ftYs_Init_8012B804, global
/* 0000011C 0000015C  7C 08 02 A6 */	mflr r0
/* 00000120 00000160  28 04 00 00 */	cmplwi r4, 0x0
/* 00000124 00000164  90 01 00 04 */	stw r0, 0x4(r1)
/* 00000128 00000168  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 0000012C 0000016C  DB E1 00 38 */	stfd f31, 0x38(r1)
/* 00000130 00000170  FF E0 08 90 */	fmr f31, f1
/* 00000134 00000174  BF 61 00 24 */	stmw r27, 0x24(r1)
/* 00000138 00000178  3B 63 00 00 */	addi r27, r3, 0x0
/* 0000013C 0000017C  41 82 00 68 */	beq .L_000001A4
/* 00000140 00000180  80 64 00 04 */	lwz r3, 0x4(r4)
/* 00000144 00000184  3B A0 00 00 */	li r29, 0x0
/* 00000148 00000188  83 E3 00 0C */	lwz r31, 0xc(r3)
/* 0000014C 0000018C  3B C3 00 08 */	addi r30, r3, 0x8
/* 00000150 00000190  48 00 00 48 */	b .L_00000198
.L_00000154:
/* 00000154 00000194  88 1F 00 00 */	lbz r0, 0x0(r31)
/* 00000158 00000198  80 7B 05 F0 */	lwz r3, 0x5f0(r27)
/* 0000015C 0000019C  54 00 10 3A */	slwi r0, r0, 2
/* 00000160 000001A0  7C 63 00 2E */	lwzx r3, r3, r0
/* 00000164 000001A4  28 03 00 00 */	cmplwi r3, 0x0
/* 00000168 000001A8  41 82 00 0C */	beq .L_00000174
/* 0000016C 000001AC  80 03 00 08 */	lwz r0, 0x8(r3)
/* 00000170 000001B0  48 00 00 08 */	b .L_00000178
.L_00000174:
/* 00000174 000001B4  38 00 00 00 */	li r0, 0x0
.L_00000178:
/* 00000178 000001B8  FC 20 F8 90 */	fmr f1, f31
/* 0000017C 000001BC  7C 1C 03 78 */	mr r28, r0
/* 00000180 000001C0  38 7C 00 00 */	addi r3, r28, 0x0
/* 00000184 000001C4  48 00 00 01 */	bl HSD_MObjReqAnim
/* 00000188 000001C8  7F 83 E3 78 */	mr r3, r28
/* 0000018C 000001CC  48 00 00 01 */	bl HSD_MObjAnim
/* 00000190 000001D0  3B BD 00 01 */	addi r29, r29, 0x1
/* 00000194 000001D4  3B FF 00 01 */	addi r31, r31, 0x1
.L_00000198:
/* 00000198 000001D8  80 1E 00 00 */	lwz r0, 0x0(r30)
/* 0000019C 000001DC  7C 1D 00 00 */	cmpw r29, r0
/* 000001A0 000001E0  41 80 FF B4 */	blt .L_00000154
.L_000001A4:
/* 000001A4 000001E4  BB 61 00 24 */	lmw r27, 0x24(r1)
/* 000001A8 000001E8  80 01 00 44 */	lwz r0, 0x44(r1)
/* 000001AC 000001EC  CB E1 00 38 */	lfd f31, 0x38(r1)
/* 000001B0 000001F0  38 21 00 40 */	addi r1, r1, 0x40
/* 000001B4 000001F4  7C 08 03 A6 */	mtlr r0
/* 000001B8 000001F8  4E 80 00 20 */	blr
.endfn ftYs_Init_8012B804

.fn ftYs_Init_8012B8A4, global
/* 000001BC 000001FC  7C 08 02 A6 */	mflr r0
/* 000001C0 00000200  90 01 00 04 */	stw r0, 0x4(r1)
/* 000001C4 00000204  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 000001C8 00000208  DB E1 00 28 */	stfd f31, 0x28(r1)
/* 000001CC 0000020C  93 E1 00 24 */	stw r31, 0x24(r1)
/* 000001D0 00000210  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 000001D4 00000214  80 80 00 00 */	lwz r4, p_ftCommonData@sda21(r0)
/* 000001D8 00000218  C0 3F 19 98 */	lfs f1, 0x1998(r31)
/* 000001DC 0000021C  7F E3 FB 78 */	mr r3, r31
/* 000001E0 00000220  C0 04 02 60 */	lfs f0, 0x260(r4)
/* 000001E4 00000224  80 9F 02 D4 */	lwz r4, 0x2d4(r31)
/* 000001E8 00000228  EC 01 00 24 */	fdivs f0, f1, f0
/* 000001EC 0000022C  C0 20 00 00 */	lfs f1, "@259"@sda21(r0)
/* 000001F0 00000230  C0 44 00 0C */	lfs f2, 0xc(r4)
/* 000001F4 00000234  80 9F 05 B8 */	lwz r4, 0x5b8(r31)
/* 000001F8 00000238  EC 01 00 28 */	fsubs f0, f1, f0
/* 000001FC 0000023C  EF E2 00 32 */	fmuls f31, f2, f0
/* 00000200 00000240  FC 20 F8 90 */	fmr f1, f31
/* 00000204 00000244  48 00 00 01 */	bl ftYs_Init_8012B804
/* 00000208 00000248  FC 20 F8 90 */	fmr f1, f31
/* 0000020C 0000024C  80 9F 05 BC */	lwz r4, 0x5bc(r31)
/* 00000210 00000250  7F E3 FB 78 */	mr r3, r31
/* 00000214 00000254  48 00 00 01 */	bl ftYs_Init_8012B804
/* 00000218 00000258  80 01 00 34 */	lwz r0, 0x34(r1)
/* 0000021C 0000025C  CB E1 00 28 */	lfd f31, 0x28(r1)
/* 00000220 00000260  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 00000224 00000264  38 21 00 30 */	addi r1, r1, 0x30
/* 00000228 00000268  7C 08 03 A6 */	mtlr r0
/* 0000022C 0000026C  4E 80 00 20 */	blr
.endfn ftYs_Init_8012B8A4

.fn ftYs_Init_8012B918, global
/* 00000230 00000270  7C 08 02 A6 */	mflr r0
/* 00000234 00000274  90 01 00 04 */	stw r0, 0x4(r1)
/* 00000238 00000278  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 0000023C 0000027C  93 E1 00 14 */	stw r31, 0x14(r1)
/* 00000240 00000280  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 00000244 00000284  C0 20 00 00 */	lfs f1, "@239"@sda21(r0)
/* 00000248 00000288  80 9F 05 B8 */	lwz r4, 0x5b8(r31)
/* 0000024C 0000028C  7F E3 FB 78 */	mr r3, r31
/* 00000250 00000290  48 00 00 01 */	bl ftYs_Init_8012B804
/* 00000254 00000294  80 9F 05 BC */	lwz r4, 0x5bc(r31)
/* 00000258 00000298  7F E3 FB 78 */	mr r3, r31
/* 0000025C 0000029C  C0 20 00 00 */	lfs f1, "@239"@sda21(r0)
/* 00000260 000002A0  48 00 00 01 */	bl ftYs_Init_8012B804
/* 00000264 000002A4  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 00000268 000002A8  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 0000026C 000002AC  38 21 00 18 */	addi r1, r1, 0x18
/* 00000270 000002B0  7C 08 03 A6 */	mtlr r0
/* 00000274 000002B4  4E 80 00 20 */	blr
.endfn ftYs_Init_8012B918

.fn ftYs_Init_OnDeath, global
/* 00000278 000002B8  7C 08 02 A6 */	mflr r0
/* 0000027C 000002BC  38 80 00 00 */	li r4, 0x0
/* 00000280 000002C0  90 01 00 04 */	stw r0, 0x4(r1)
/* 00000284 000002C4  38 A0 00 00 */	li r5, 0x0
/* 00000288 000002C8  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 0000028C 000002CC  93 E1 00 14 */	stw r31, 0x14(r1)
/* 00000290 000002D0  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 00000294 000002D4  48 00 00 01 */	bl ftParts_80074A4C
/* 00000298 000002D8  38 00 00 00 */	li r0, 0x0
/* 0000029C 000002DC  90 1F 22 38 */	stw r0, 0x2238(r31)
/* 000002A0 000002E0  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 000002A4 000002E4  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 000002A8 000002E8  38 21 00 18 */	addi r1, r1, 0x18
/* 000002AC 000002EC  7C 08 03 A6 */	mtlr r0
/* 000002B0 000002F0  4E 80 00 20 */	blr
.endfn ftYs_Init_OnDeath

.fn ftYs_Init_OnLoad, global
/* 000002B4 000002F4  7C 08 02 A6 */	mflr r0
/* 000002B8 000002F8  90 01 00 04 */	stw r0, 0x4(r1)
/* 000002BC 000002FC  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 000002C0 00000300  BF 61 00 1C */	stmw r27, 0x1c(r1)
/* 000002C4 00000304  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 000002C8 00000308  83 7F 05 B8 */	lwz r27, 0x5b8(r31)
/* 000002CC 0000030C  80 7F 01 0C */	lwz r3, 0x10c(r31)
/* 000002D0 00000310  28 1B 00 00 */	cmplwi r27, 0x0
/* 000002D4 00000314  83 9F 05 BC */	lwz r28, 0x5bc(r31)
/* 000002D8 00000318  83 C3 00 48 */	lwz r30, 0x48(r3)
/* 000002DC 0000031C  83 A3 00 04 */	lwz r29, 0x4(r3)
/* 000002E0 00000320  40 82 00 28 */	bne .L_00000308
/* 000002E4 00000324  3C 60 00 00 */	lis r3, "@273"@ha
/* 000002E8 00000328  4C C6 31 82 */	crclr cr1eq
/* 000002EC 0000032C  38 63 00 00 */	addi r3, r3, "@273"@l
/* 000002F0 00000330  48 00 00 01 */	bl OSReport
/* 000002F4 00000334  3C 60 00 00 */	lis r3, "@243"@ha
/* 000002F8 00000338  38 63 00 00 */	addi r3, r3, "@243"@l
/* 000002FC 0000033C  38 80 00 71 */	li r4, 0x71
/* 00000300 00000340  38 A0 00 00 */	li r5, "@244"@sda21
/* 00000304 00000344  48 00 00 01 */	bl __assert
.L_00000308:
/* 00000308 00000348  C0 00 00 00 */	lfs f0, "@239"@sda21(r0)
/* 0000030C 0000034C  38 7F 00 00 */	addi r3, r31, 0x0
/* 00000310 00000350  38 9B 00 00 */	addi r4, r27, 0x0
/* 00000314 00000354  D0 1D 00 0C */	stfs f0, 0xc(r29)
/* 00000318 00000358  48 00 00 01 */	bl ftYs_Init_8012B6E8
/* 0000031C 0000035C  38 7F 00 00 */	addi r3, r31, 0x0
/* 00000320 00000360  38 9C 00 00 */	addi r4, r28, 0x0
/* 00000324 00000364  48 00 00 01 */	bl ftYs_Init_8012B6E8
/* 00000328 00000368  80 7F 01 0C */	lwz r3, 0x10c(r31)
/* 0000032C 0000036C  38 00 00 27 */	li r0, 0x27
/* 00000330 00000370  80 DF 02 D8 */	lwz r6, 0x2d8(r31)
/* 00000334 00000374  7C 09 03 A6 */	mtctr r0
/* 00000338 00000378  80 63 00 04 */	lwz r3, 0x4(r3)
/* 0000033C 0000037C  38 A6 FF F8 */	subi r5, r6, 0x8
/* 00000340 00000380  38 83 FF F8 */	subi r4, r3, 0x8
.L_00000344:
/* 00000344 00000384  84 64 00 08 */	lwzu r3, 0x8(r4)
/* 00000348 00000388  80 04 00 04 */	lwz r0, 0x4(r4)
/* 0000034C 0000038C  94 65 00 08 */	stwu r3, 0x8(r5)
/* 00000350 00000390  90 05 00 04 */	stw r0, 0x4(r5)
/* 00000354 00000394  42 00 FF F0 */	bdnz .L_00000344
/* 00000358 00000398  90 DF 02 D4 */	stw r6, 0x2d4(r31)
/* 0000035C 0000039C  38 80 00 56 */	li r4, 0x56
/* 00000360 000003A0  80 7E 00 00 */	lwz r3, 0x0(r30)
/* 00000364 000003A4  48 00 00 01 */	bl it_8026B3F8
/* 00000368 000003A8  80 7E 00 04 */	lwz r3, 0x4(r30)
/* 0000036C 000003AC  38 80 00 58 */	li r4, 0x58
/* 00000370 000003B0  48 00 00 01 */	bl it_8026B3F8
/* 00000374 000003B4  80 7E 00 08 */	lwz r3, 0x8(r30)
/* 00000378 000003B8  38 80 00 57 */	li r4, 0x57
/* 0000037C 000003BC  48 00 00 01 */	bl it_8026B3F8
/* 00000380 000003C0  88 1F 22 26 */	lbz r0, 0x2226(r31)
/* 00000384 000003C4  38 60 00 01 */	li r3, 0x1
/* 00000388 000003C8  50 60 36 72 */	rlwimi r0, r3, 6, 25, 25
/* 0000038C 000003CC  98 1F 22 26 */	stb r0, 0x2226(r31)
/* 00000390 000003D0  80 01 00 34 */	lwz r0, 0x34(r1)
/* 00000394 000003D4  BB 61 00 1C */	lmw r27, 0x1c(r1)
/* 00000398 000003D8  38 21 00 30 */	addi r1, r1, 0x30
/* 0000039C 000003DC  7C 08 03 A6 */	mtlr r0
/* 000003A0 000003E0  4E 80 00 20 */	blr
.endfn ftYs_Init_OnLoad

.fn ftYs_Init_8012BA8C, global
/* 000003A4 000003E4  7C 08 02 A6 */	mflr r0
/* 000003A8 000003E8  90 01 00 04 */	stw r0, 0x4(r1)
/* 000003AC 000003EC  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 000003B0 000003F0  93 E1 00 14 */	stw r31, 0x14(r1)
/* 000003B4 000003F4  7C 7F 1B 78 */	mr r31, r3
/* 000003B8 000003F8  48 00 00 01 */	bl ftYs_SpecialS_8012E270
/* 000003BC 000003FC  7F E3 FB 78 */	mr r3, r31
/* 000003C0 00000400  48 00 00 01 */	bl ftYs_SpecialS_8012DF18
/* 000003C4 00000404  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 000003C8 00000408  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 000003CC 0000040C  38 21 00 18 */	addi r1, r1, 0x18
/* 000003D0 00000410  7C 08 03 A6 */	mtlr r0
/* 000003D4 00000414  4E 80 00 20 */	blr
.endfn ftYs_Init_8012BA8C

.fn ftYs_Init_8012BAC0, global
/* 000003D8 00000418  80 63 02 D4 */	lwz r3, 0x2d4(r3)
/* 000003DC 0000041C  C0 23 01 20 */	lfs f1, 0x120(r3)
/* 000003E0 00000420  4E 80 00 20 */	blr
.endfn ftYs_Init_8012BAC0

.fn ftYs_Init_OnItemPickup, global
/* 000003E4 00000424  7C 08 02 A6 */	mflr r0
/* 000003E8 00000428  90 01 00 04 */	stw r0, 0x4(r1)
/* 000003EC 0000042C  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 000003F0 00000430  93 E1 00 24 */	stw r31, 0x24(r1)
/* 000003F4 00000434  93 C1 00 20 */	stw r30, 0x20(r1)
/* 000003F8 00000438  7C 9E 23 78 */	mr r30, r4
/* 000003FC 0000043C  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 00000400 00000440  7C 7D 1B 78 */	mr r29, r3
/* 00000404 00000444  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 00000408 00000448  80 7F 19 74 */	lwz r3, 0x1974(r31)
/* 0000040C 0000044C  48 00 00 01 */	bl it_8026B2B4
/* 00000410 00000450  2C 03 00 00 */	cmpwi r3, 0x0
/* 00000414 00000454  40 82 00 94 */	bne .L_000004A8
/* 00000418 00000458  80 7F 19 74 */	lwz r3, 0x1974(r31)
/* 0000041C 0000045C  48 00 00 01 */	bl it_8026B320
/* 00000420 00000460  2C 03 00 03 */	cmpwi r3, 0x3
/* 00000424 00000464  41 82 00 4C */	beq .L_00000470
/* 00000428 00000468  40 80 00 14 */	bge .L_0000043C
/* 0000042C 0000046C  2C 03 00 01 */	cmpwi r3, 0x1
/* 00000430 00000470  41 82 00 18 */	beq .L_00000448
/* 00000434 00000474  40 80 00 28 */	bge .L_0000045C
/* 00000438 00000478  48 00 00 5C */	b .L_00000494
.L_0000043C:
/* 0000043C 0000047C  2C 03 00 05 */	cmpwi r3, 0x5
/* 00000440 00000480  40 80 00 54 */	bge .L_00000494
/* 00000444 00000484  48 00 00 40 */	b .L_00000484
.L_00000448:
/* 00000448 00000488  38 7D 00 00 */	addi r3, r29, 0x0
/* 0000044C 0000048C  38 80 00 01 */	li r4, 0x1
/* 00000450 00000490  38 A0 00 01 */	li r5, 0x1
/* 00000454 00000494  48 00 00 01 */	bl ftAnim_80070FB4
/* 00000458 00000498  48 00 00 3C */	b .L_00000494
.L_0000045C:
/* 0000045C 0000049C  38 7D 00 00 */	addi r3, r29, 0x0
/* 00000460 000004A0  38 80 00 01 */	li r4, 0x1
/* 00000464 000004A4  38 A0 00 00 */	li r5, 0x0
/* 00000468 000004A8  48 00 00 01 */	bl ftAnim_80070FB4
/* 0000046C 000004AC  48 00 00 28 */	b .L_00000494
.L_00000470:
/* 00000470 000004B0  38 7D 00 00 */	addi r3, r29, 0x0
/* 00000474 000004B4  38 80 00 01 */	li r4, 0x1
/* 00000478 000004B8  38 A0 00 02 */	li r5, 0x2
/* 0000047C 000004BC  48 00 00 01 */	bl ftAnim_80070FB4
/* 00000480 000004C0  48 00 00 14 */	b .L_00000494
.L_00000484:
/* 00000484 000004C4  38 7D 00 00 */	addi r3, r29, 0x0
/* 00000488 000004C8  38 80 00 01 */	li r4, 0x1
/* 0000048C 000004CC  38 A0 00 03 */	li r5, 0x3
/* 00000490 000004D0  48 00 00 01 */	bl ftAnim_80070FB4
.L_00000494:
/* 00000494 000004D4  2C 1E 00 00 */	cmpwi r30, 0x0
/* 00000498 000004D8  41 82 00 10 */	beq .L_000004A8
/* 0000049C 000004DC  38 7D 00 00 */	addi r3, r29, 0x0
/* 000004A0 000004E0  38 80 00 01 */	li r4, 0x1
/* 000004A4 000004E4  48 00 00 01 */	bl ftAnim_80070C48
.L_000004A8:
/* 000004A8 000004E8  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 000004AC 000004EC  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 000004B0 000004F0  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 000004B4 000004F4  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 000004B8 000004F8  38 21 00 28 */	addi r1, r1, 0x28
/* 000004BC 000004FC  7C 08 03 A6 */	mtlr r0
/* 000004C0 00000500  4E 80 00 20 */	blr
.endfn ftYs_Init_OnItemPickup

.fn ftYs_Init_OnItemInvisible, global
/* 000004C4 00000504  7C 08 02 A6 */	mflr r0
/* 000004C8 00000508  90 01 00 04 */	stw r0, 0x4(r1)
/* 000004CC 0000050C  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 000004D0 00000510  93 E1 00 14 */	stw r31, 0x14(r1)
/* 000004D4 00000514  7C 7F 1B 78 */	mr r31, r3
/* 000004D8 00000518  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 000004DC 0000051C  80 63 19 74 */	lwz r3, 0x1974(r3)
/* 000004E0 00000520  48 00 00 01 */	bl it_8026B2B4
/* 000004E4 00000524  2C 03 00 00 */	cmpwi r3, 0x0
/* 000004E8 00000528  40 82 00 10 */	bne .L_000004F8
/* 000004EC 0000052C  38 7F 00 00 */	addi r3, r31, 0x0
/* 000004F0 00000530  38 80 00 01 */	li r4, 0x1
/* 000004F4 00000534  48 00 00 01 */	bl ftAnim_80070CC4
.L_000004F8:
/* 000004F8 00000538  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 000004FC 0000053C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 00000500 00000540  38 21 00 18 */	addi r1, r1, 0x18
/* 00000504 00000544  7C 08 03 A6 */	mtlr r0
/* 00000508 00000548  4E 80 00 20 */	blr
.endfn ftYs_Init_OnItemInvisible

.fn ftYs_Init_OnItemVisible, global
/* 0000050C 0000054C  7C 08 02 A6 */	mflr r0
/* 00000510 00000550  90 01 00 04 */	stw r0, 0x4(r1)
/* 00000514 00000554  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 00000518 00000558  93 E1 00 14 */	stw r31, 0x14(r1)
/* 0000051C 0000055C  7C 7F 1B 78 */	mr r31, r3
/* 00000520 00000560  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 00000524 00000564  80 63 19 74 */	lwz r3, 0x1974(r3)
/* 00000528 00000568  48 00 00 01 */	bl it_8026B2B4
/* 0000052C 0000056C  2C 03 00 00 */	cmpwi r3, 0x0
/* 00000530 00000570  40 82 00 10 */	bne .L_00000540
/* 00000534 00000574  38 7F 00 00 */	addi r3, r31, 0x0
/* 00000538 00000578  38 80 00 01 */	li r4, 0x1
/* 0000053C 0000057C  48 00 00 01 */	bl ftAnim_80070C48
.L_00000540:
/* 00000540 00000580  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 00000544 00000584  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 00000548 00000588  38 21 00 18 */	addi r1, r1, 0x18
/* 0000054C 0000058C  7C 08 03 A6 */	mtlr r0
/* 00000550 00000590  4E 80 00 20 */	blr
.endfn ftYs_Init_OnItemVisible

.fn ftYs_Init_OnItemDrop, global
/* 00000554 00000594  7C 08 02 A6 */	mflr r0
/* 00000558 00000598  38 A0 FF FF */	li r5, -0x1
/* 0000055C 0000059C  90 01 00 04 */	stw r0, 0x4(r1)
/* 00000560 000005A0  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 00000564 000005A4  93 E1 00 14 */	stw r31, 0x14(r1)
/* 00000568 000005A8  3B E4 00 00 */	addi r31, r4, 0x0
/* 0000056C 000005AC  38 80 00 01 */	li r4, 0x1
/* 00000570 000005B0  93 C1 00 10 */	stw r30, 0x10(r1)
/* 00000574 000005B4  3B C3 00 00 */	addi r30, r3, 0x0
/* 00000578 000005B8  48 00 00 01 */	bl ftAnim_80070FB4
/* 0000057C 000005BC  2C 1F 00 00 */	cmpwi r31, 0x0
/* 00000580 000005C0  41 82 00 10 */	beq .L_00000590
/* 00000584 000005C4  38 7E 00 00 */	addi r3, r30, 0x0
/* 00000588 000005C8  38 80 00 01 */	li r4, 0x1
/* 0000058C 000005CC  48 00 00 01 */	bl ftAnim_80070CC4
.L_00000590:
/* 00000590 000005D0  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 00000594 000005D4  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 00000598 000005D8  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 0000059C 000005DC  38 21 00 18 */	addi r1, r1, 0x18
/* 000005A0 000005E0  7C 08 03 A6 */	mtlr r0
/* 000005A4 000005E4  4E 80 00 20 */	blr
.endfn ftYs_Init_OnItemDrop

.fn ftYs_Init_LoadSpecialAttrs, global
/* 000005A8 000005E8  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 000005AC 000005EC  38 00 00 27 */	li r0, 0x27
/* 000005B0 000005F0  7C 09 03 A6 */	mtctr r0
/* 000005B4 000005F4  80 83 01 0C */	lwz r4, 0x10c(r3)
/* 000005B8 000005F8  80 63 02 D4 */	lwz r3, 0x2d4(r3)
/* 000005BC 000005FC  80 84 00 04 */	lwz r4, 0x4(r4)
/* 000005C0 00000600  38 A3 FF F8 */	subi r5, r3, 0x8
/* 000005C4 00000604  38 84 FF F8 */	subi r4, r4, 0x8
.L_000005C8:
/* 000005C8 00000608  84 64 00 08 */	lwzu r3, 0x8(r4)
/* 000005CC 0000060C  80 04 00 04 */	lwz r0, 0x4(r4)
/* 000005D0 00000610  94 65 00 08 */	stwu r3, 0x8(r5)
/* 000005D4 00000614  90 05 00 04 */	stw r0, 0x4(r5)
/* 000005D8 00000618  42 00 FF F0 */	bdnz .L_000005C8
/* 000005DC 0000061C  4E 80 00 20 */	blr
.endfn ftYs_Init_LoadSpecialAttrs

.fn ftYs_Init_OnKnockbackEnter, global
/* 000005E0 00000620  7C 08 02 A6 */	mflr r0
/* 000005E4 00000624  38 80 00 01 */	li r4, 0x1
/* 000005E8 00000628  90 01 00 04 */	stw r0, 0x4(r1)
/* 000005EC 0000062C  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 000005F0 00000630  93 E1 00 14 */	stw r31, 0x14(r1)
/* 000005F4 00000634  7C 7F 1B 78 */	mr r31, r3
/* 000005F8 00000638  C0 20 00 00 */	lfs f1, "@304"@sda21(r0)
/* 000005FC 0000063C  48 00 00 01 */	bl ftAnim_800704F0
/* 00000600 00000640  C0 20 00 00 */	lfs f1, "@304"@sda21(r0)
/* 00000604 00000644  38 7F 00 00 */	addi r3, r31, 0x0
/* 00000608 00000648  38 80 00 00 */	li r4, 0x0
/* 0000060C 0000064C  48 00 00 01 */	bl ftAnim_800704F0
/* 00000610 00000650  C0 20 00 00 */	lfs f1, "@239"@sda21(r0)
/* 00000614 00000654  38 7F 00 00 */	addi r3, r31, 0x0
/* 00000618 00000658  38 80 00 03 */	li r4, 0x3
/* 0000061C 0000065C  38 A0 00 03 */	li r5, 0x3
/* 00000620 00000660  48 00 00 01 */	bl ftAnim_ApplyPartAnim
/* 00000624 00000664  C0 20 00 00 */	lfs f1, "@239"@sda21(r0)
/* 00000628 00000668  38 7F 00 00 */	addi r3, r31, 0x0
/* 0000062C 0000066C  38 80 00 04 */	li r4, 0x4
/* 00000630 00000670  38 A0 00 03 */	li r5, 0x3
/* 00000634 00000674  48 00 00 01 */	bl ftAnim_ApplyPartAnim
/* 00000638 00000678  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 0000063C 0000067C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 00000640 00000680  38 21 00 18 */	addi r1, r1, 0x18
/* 00000644 00000684  7C 08 03 A6 */	mtlr r0
/* 00000648 00000688  4E 80 00 20 */	blr
.endfn ftYs_Init_OnKnockbackEnter

.fn ftYs_Init_OnKnockbackExit, global
/* 0000064C 0000068C  7C 08 02 A6 */	mflr r0
/* 00000650 00000690  38 80 00 01 */	li r4, 0x1
/* 00000654 00000694  90 01 00 04 */	stw r0, 0x4(r1)
/* 00000658 00000698  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 0000065C 0000069C  93 E1 00 14 */	stw r31, 0x14(r1)
/* 00000660 000006A0  7C 7F 1B 78 */	mr r31, r3
/* 00000664 000006A4  C0 20 00 00 */	lfs f1, "@239"@sda21(r0)
/* 00000668 000006A8  48 00 00 01 */	bl ftAnim_800704F0
/* 0000066C 000006AC  C0 20 00 00 */	lfs f1, "@239"@sda21(r0)
/* 00000670 000006B0  38 7F 00 00 */	addi r3, r31, 0x0
/* 00000674 000006B4  38 80 00 00 */	li r4, 0x0
/* 00000678 000006B8  48 00 00 01 */	bl ftAnim_800704F0
/* 0000067C 000006BC  C0 20 00 00 */	lfs f1, "@239"@sda21(r0)
/* 00000680 000006C0  38 7F 00 00 */	addi r3, r31, 0x0
/* 00000684 000006C4  38 80 00 03 */	li r4, 0x3
/* 00000688 000006C8  38 A0 00 02 */	li r5, 0x2
/* 0000068C 000006CC  48 00 00 01 */	bl ftAnim_ApplyPartAnim
/* 00000690 000006D0  C0 20 00 00 */	lfs f1, "@239"@sda21(r0)
/* 00000694 000006D4  38 7F 00 00 */	addi r3, r31, 0x0
/* 00000698 000006D8  38 80 00 04 */	li r4, 0x4
/* 0000069C 000006DC  38 A0 00 02 */	li r5, 0x2
/* 000006A0 000006E0  48 00 00 01 */	bl ftAnim_ApplyPartAnim
/* 000006A4 000006E4  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 000006A8 000006E8  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 000006AC 000006EC  38 21 00 18 */	addi r1, r1, 0x18
/* 000006B0 000006F0  7C 08 03 A6 */	mtlr r0
/* 000006B4 000006F4  4E 80 00 20 */	blr
.endfn ftYs_Init_OnKnockbackExit

.fn ftYs_Init_8012BDA0, global
/* 000006B8 000006F8  7C 08 02 A6 */	mflr r0
/* 000006BC 000006FC  38 80 00 02 */	li r4, 0x2
/* 000006C0 00000700  90 01 00 04 */	stw r0, 0x4(r1)
/* 000006C4 00000704  94 21 FF A8 */	stwu r1, -0x58(r1)
/* 000006C8 00000708  93 E1 00 54 */	stw r31, 0x54(r1)
/* 000006CC 0000070C  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 000006D0 00000710  48 00 00 01 */	bl ftColl_8007B0C0
/* 000006D4 00000714  80 9F 01 0C */	lwz r4, 0x10c(r31)
/* 000006D8 00000718  3C 60 00 00 */	lis r3, ftYs_Unk1_803B75C0@ha
/* 000006DC 0000071C  38 00 00 01 */	li r0, 0x1
/* 000006E0 00000720  C0 00 00 00 */	lfs f0, ftYs_Init_804D9A28@sda21(r0)
/* 000006E4 00000724  80 84 00 08 */	lwz r4, 0x8(r4)
/* 000006E8 00000728  38 E3 00 00 */	addi r7, r3, ftYs_Unk1_803B75C0@l
/* 000006EC 0000072C  88 A4 00 11 */	lbz r5, 0x11(r4)
/* 000006F0 00000730  38 7F 00 00 */	addi r3, r31, 0x0
/* 000006F4 00000734  38 9F 11 A0 */	addi r4, r31, 0x11a0
/* 000006F8 00000738  90 A1 00 20 */	stw r5, 0x20(r1)
/* 000006FC 0000073C  38 A1 00 20 */	addi r5, r1, 0x20
/* 00000700 00000740  90 01 00 24 */	stw r0, 0x24(r1)
/* 00000704 00000744  90 01 00 28 */	stw r0, 0x28(r1)
/* 00000708 00000748  80 C7 00 00 */	lwz r6, 0x0(r7)
/* 0000070C 0000074C  80 07 00 04 */	lwz r0, 0x4(r7)
/* 00000710 00000750  90 C1 00 38 */	stw r6, 0x38(r1)
/* 00000714 00000754  90 01 00 3C */	stw r0, 0x3c(r1)
/* 00000718 00000758  80 07 00 08 */	lwz r0, 0x8(r7)
/* 0000071C 0000075C  90 01 00 40 */	stw r0, 0x40(r1)
/* 00000720 00000760  80 C1 00 38 */	lwz r6, 0x38(r1)
/* 00000724 00000764  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 00000728 00000768  90 C1 00 2C */	stw r6, 0x2c(r1)
/* 0000072C 0000076C  90 01 00 30 */	stw r0, 0x30(r1)
/* 00000730 00000770  80 01 00 40 */	lwz r0, 0x40(r1)
/* 00000734 00000774  90 01 00 34 */	stw r0, 0x34(r1)
/* 00000738 00000778  D0 01 00 44 */	stfs f0, 0x44(r1)
/* 0000073C 0000077C  48 00 00 01 */	bl ftColl_8007B5AC
/* 00000740 00000780  80 01 00 5C */	lwz r0, 0x5c(r1)
/* 00000744 00000784  83 E1 00 54 */	lwz r31, 0x54(r1)
/* 00000748 00000788  38 21 00 58 */	addi r1, r1, 0x58
/* 0000074C 0000078C  7C 08 03 A6 */	mtlr r0
/* 00000750 00000790  4E 80 00 20 */	blr
.endfn ftYs_Init_8012BDA0

.fn ftYs_Init_8012BE3C, global
/* 00000754 00000794  7C 08 02 A6 */	mflr r0
/* 00000758 00000798  38 80 00 00 */	li r4, 0x0
/* 0000075C 0000079C  90 01 00 04 */	stw r0, 0x4(r1)
/* 00000760 000007A0  38 A0 00 00 */	li r5, 0x0
/* 00000764 000007A4  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 00000768 000007A8  93 E1 00 24 */	stw r31, 0x24(r1)
/* 0000076C 000007AC  93 C1 00 20 */	stw r30, 0x20(r1)
/* 00000770 000007B0  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 00000774 000007B4  7C 7D 1B 78 */	mr r29, r3
/* 00000778 000007B8  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 0000077C 000007BC  48 00 00 01 */	bl ftParts_80074B0C
/* 00000780 000007C0  38 7D 00 00 */	addi r3, r29, 0x0
/* 00000784 000007C4  38 80 00 00 */	li r4, 0x0
/* 00000788 000007C8  48 00 00 01 */	bl ftColl_8007B0C0
/* 0000078C 000007CC  38 7E 00 00 */	addi r3, r30, 0x0
/* 00000790 000007D0  3B FE 01 CC */	addi r31, r30, 0x1cc
/* 00000794 000007D4  38 80 00 04 */	li r4, 0x4
/* 00000798 000007D8  48 00 00 01 */	bl ftParts_8007500C
/* 0000079C 000007DC  80 9E 05 E8 */	lwz r4, 0x5e8(r30)
/* 000007A0 000007E0  54 60 20 36 */	slwi r0, r3, 4
/* 000007A4 000007E4  80 BD 00 2C */	lwz r5, 0x2c(r29)
/* 000007A8 000007E8  7F A3 EB 78 */	mr r3, r29
/* 000007AC 000007EC  7C E4 00 2E */	lwzx r7, r4, r0
/* 000007B0 000007F0  38 85 06 0C */	addi r4, r5, 0x60c
/* 000007B4 000007F4  4C C6 31 82 */	crclr cr1eq
/* 000007B8 000007F8  39 1F 00 00 */	addi r8, r31, 0x0
/* 000007BC 000007FC  38 A0 00 04 */	li r5, 0x4
/* 000007C0 00000800  38 C0 04 CF */	li r6, 0x4cf
/* 000007C4 00000804  48 00 00 01 */	bl efAsync_Spawn
/* 000007C8 00000808  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 000007CC 0000080C  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 000007D0 00000810  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 000007D4 00000814  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 000007D8 00000818  38 21 00 28 */	addi r1, r1, 0x28
/* 000007DC 0000081C  7C 08 03 A6 */	mtlr r0
/* 000007E0 00000820  4E 80 00 20 */	blr
.endfn ftYs_Init_8012BE3C

.fn ftYs_Init_8012BECC, global
/* 000007E4 00000824  7C 08 02 A6 */	mflr r0
/* 000007E8 00000828  38 80 01 55 */	li r4, 0x155
/* 000007EC 0000082C  90 01 00 04 */	stw r0, 0x4(r1)
/* 000007F0 00000830  38 A0 00 00 */	li r5, 0x0
/* 000007F4 00000834  38 C0 00 00 */	li r6, 0x0
/* 000007F8 00000838  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 000007FC 0000083C  93 E1 00 34 */	stw r31, 0x34(r1)
/* 00000800 00000840  7C 7F 1B 78 */	mr r31, r3
/* 00000804 00000844  93 C1 00 30 */	stw r30, 0x30(r1)
/* 00000808 00000848  93 A1 00 2C */	stw r29, 0x2c(r1)
/* 0000080C 0000084C  C0 20 00 00 */	lfs f1, ftYs_Init_804D9A2C@sda21(r0)
/* 00000810 00000850  C0 40 00 00 */	lfs f2, ftYs_Init_804D9A28@sda21(r0)
/* 00000814 00000854  FC 60 08 90 */	fmr f3, f1
/* 00000818 00000858  48 00 00 01 */	bl Fighter_ChangeMotionState
/* 0000081C 0000085C  7F E3 FB 78 */	mr r3, r31
/* 00000820 00000860  48 00 00 01 */	bl ftAnim_8006EBA4
/* 00000824 00000864  7F E3 FB 78 */	mr r3, r31
/* 00000828 00000868  48 00 00 01 */	bl ftCo_80092450
/* 0000082C 0000086C  83 DF 00 2C */	lwz r30, 0x2c(r31)
/* 00000830 00000870  38 7F 00 00 */	addi r3, r31, 0x0
/* 00000834 00000874  38 80 00 01 */	li r4, 0x1
/* 00000838 00000878  48 00 00 01 */	bl ftColl_8007B0C0
/* 0000083C 0000087C  38 00 00 00 */	li r0, 0x0
/* 00000840 00000880  90 1E 23 4C */	stw r0, 0x234c(r30)
/* 00000844 00000884  C0 20 00 00 */	lfs f1, ftYs_Init_804D9A2C@sda21(r0)
/* 00000848 00000888  D0 3E 23 40 */	stfs f1, 0x2340(r30)
/* 0000084C 0000088C  80 60 00 00 */	lwz r3, p_ftCommonData@sda21(r0)
/* 00000850 00000890  C0 03 02 68 */	lfs f0, 0x268(r3)
/* 00000854 00000894  D0 1E 23 50 */	stfs f0, 0x2350(r30)
/* 00000858 00000898  90 1E 23 64 */	stw r0, 0x2364(r30)
/* 0000085C 0000089C  90 1E 23 60 */	stw r0, 0x2360(r30)
/* 00000860 000008A0  D0 21 00 1C */	stfs f1, 0x1c(r1)
/* 00000864 000008A4  D0 21 00 18 */	stfs f1, 0x18(r1)
/* 00000868 000008A8  D0 21 00 14 */	stfs f1, 0x14(r1)
/* 0000086C 000008AC  80 7E 01 0C */	lwz r3, 0x10c(r30)
/* 00000870 000008B0  80 9E 05 E8 */	lwz r4, 0x5e8(r30)
/* 00000874 000008B4  80 63 00 08 */	lwz r3, 0x8(r3)
/* 00000878 000008B8  88 03 00 11 */	lbz r0, 0x11(r3)
/* 0000087C 000008BC  54 00 20 36 */	slwi r0, r0, 4
/* 00000880 000008C0  7F A4 00 2E */	lwzx r29, r4, r0
/* 00000884 000008C4  28 1D 00 00 */	cmplwi r29, 0x0
/* 00000888 000008C8  40 82 00 14 */	bne .L_0000089C
/* 0000088C 000008CC  38 60 00 00 */	li r3, ftYs_Unk2_804D3E58@sda21
/* 00000890 000008D0  38 80 03 94 */	li r4, 0x394
/* 00000894 000008D4  38 A0 00 00 */	li r5, ftYs_Unk2_804D3E60@sda21
/* 00000898 000008D8  48 00 00 01 */	bl __assert
.L_0000089C:
/* 0000089C 000008DC  80 61 00 14 */	lwz r3, 0x14(r1)
/* 000008A0 000008E0  80 01 00 18 */	lwz r0, 0x18(r1)
/* 000008A4 000008E4  90 7D 00 38 */	stw r3, 0x38(r29)
/* 000008A8 000008E8  90 1D 00 3C */	stw r0, 0x3c(r29)
/* 000008AC 000008EC  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 000008B0 000008F0  90 1D 00 40 */	stw r0, 0x40(r29)
/* 000008B4 000008F4  80 1D 00 14 */	lwz r0, 0x14(r29)
/* 000008B8 000008F8  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 000008BC 000008FC  40 82 00 4C */	bne .L_00000908
/* 000008C0 00000900  28 1D 00 00 */	cmplwi r29, 0x0
/* 000008C4 00000904  41 82 00 44 */	beq .L_00000908
/* 000008C8 00000908  40 82 00 14 */	bne .L_000008DC
/* 000008CC 0000090C  38 60 00 00 */	li r3, ftYs_Unk2_804D3E58@sda21
/* 000008D0 00000910  38 80 02 34 */	li r4, 0x234
/* 000008D4 00000914  38 A0 00 00 */	li r5, ftYs_Unk2_804D3E60@sda21
/* 000008D8 00000918  48 00 00 01 */	bl __assert
.L_000008DC:
/* 000008DC 0000091C  80 9D 00 14 */	lwz r4, 0x14(r29)
/* 000008E0 00000920  38 60 00 00 */	li r3, 0x0
/* 000008E4 00000924  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 000008E8 00000928  40 82 00 10 */	bne .L_000008F8
/* 000008EC 0000092C  54 80 06 73 */	rlwinm. r0, r4, 0, 25, 25
/* 000008F0 00000930  41 82 00 08 */	beq .L_000008F8
/* 000008F4 00000934  38 60 00 01 */	li r3, 0x1
.L_000008F8:
/* 000008F8 00000938  2C 03 00 00 */	cmpwi r3, 0x0
/* 000008FC 0000093C  40 82 00 0C */	bne .L_00000908
/* 00000900 00000940  7F A3 EB 78 */	mr r3, r29
/* 00000904 00000944  48 00 00 01 */	bl HSD_JObjSetMtxDirtySub
.L_00000908:
/* 00000908 00000948  7F E3 FB 78 */	mr r3, r31
/* 0000090C 0000094C  48 00 00 01 */	bl ftYs_Init_8012B8A4
/* 00000910 00000950  7F C3 F3 78 */	mr r3, r30
/* 00000914 00000954  48 00 00 01 */	bl ftCo_80091D58
/* 00000918 00000958  38 7E 00 00 */	addi r3, r30, 0x0
/* 0000091C 0000095C  38 80 00 6E */	li r4, 0x6e
/* 00000920 00000960  38 A0 00 7F */	li r5, 0x7f
/* 00000924 00000964  38 C0 00 40 */	li r6, 0x40
/* 00000928 00000968  48 00 00 01 */	bl ft_80088148
/* 0000092C 0000096C  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 00000930 00000970  83 E1 00 34 */	lwz r31, 0x34(r1)
/* 00000934 00000974  83 C1 00 30 */	lwz r30, 0x30(r1)
/* 00000938 00000978  83 A1 00 2C */	lwz r29, 0x2c(r1)
/* 0000093C 0000097C  38 21 00 38 */	addi r1, r1, 0x38
/* 00000940 00000980  7C 08 03 A6 */	mtlr r0
/* 00000944 00000984  4E 80 00 20 */	blr
.endfn ftYs_Init_8012BECC

# 0x00000000 - 0x000003C8
.data
.balign 8

.obj ftYs_Init_MotionStateTable, global
	.4byte 0x00000025
	.4byte 0x00100000
	.4byte 0x01000000
	.4byte ftYs_GuardOn_0_Anim
	.4byte ftYs_GuardOn_0_IASA
	.4byte ftYs_GuardOn_0_Phys
	.4byte ftYs_GuardOn_0_Coll
	.4byte ftCamera_UpdateCameraBox
	.4byte 0xFFFFFFFF
	.4byte 0x00180000
	.4byte 0x01000000
	.4byte ftYs_GuardHold_Anim
	.4byte ftYs_GuardHold_IASA
	.4byte ftYs_GuardHold_Phys
	.4byte ftYs_GuardHold_Coll
	.4byte ftCamera_UpdateCameraBox
	.4byte 0x00000027
	.4byte 0x00100000
	.4byte 0x01000000
	.4byte ftYs_GuardOff_Anim
	.4byte ftYs_GuardOff_IASA
	.4byte ftYs_GuardOff_Phys
	.4byte ftYs_GuardOff_Coll
	.4byte ftCamera_UpdateCameraBox
	.4byte 0x00000028
	.4byte 0x00100000
	.4byte 0x01000000
	.4byte ftYs_GuardDamage_Anim
	.4byte ftYs_GuardDamage_IASA
	.4byte ftYs_GuardDamage_Phys
	.4byte ftYs_GuardDamage_Coll
	.4byte ftCamera_UpdateCameraBox
	.4byte 0x00000025
	.4byte 0x00101073
	.4byte 0x01000000
	.4byte ftYs_GuardOn_1_Anim
	.4byte ftYs_GuardOn_1_IASA
	.4byte ftYs_GuardOn_1_Phys
	.4byte ftYs_GuardOn_1_Coll
	.4byte ftCamera_UpdateCameraBox
	.4byte 0x00000127
	.4byte 0x00340011
	.4byte 0x12000000
	.4byte ftYs_SpecialN1_Anim
	.4byte 0x00000000
	.4byte ftYs_SpecialN1_Phys
	.4byte ftYs_SpecialN1_Coll
	.4byte ftCamera_UpdateCameraBox
	.4byte 0x00000128
	.4byte 0x00340011
	.4byte 0x12000000
	.4byte ftYs_SpecialN1_0_Anim
	.4byte 0x00000000
	.4byte ftYs_SpecialN1_0_Phys
	.4byte ftYs_SpecialN1_0_Coll
	.4byte ftCamera_UpdateCameraBox
	.4byte 0x00000128
	.4byte 0x00340011
	.4byte 0x12000000
	.4byte ftYs_SpecialN1_1_Anim
	.4byte 0x00000000
	.4byte ftYs_SpecialN1_1_Phys
	.4byte ftYs_SpecialN1_1_Coll
	.4byte ftCamera_UpdateCameraBox
	.4byte 0x00000129
	.4byte 0x00340011
	.4byte 0x12000000
	.4byte ftYs_SpecialN2_0_Anim
	.4byte 0x00000000
	.4byte ftYs_SpecialN2_0_Phys
	.4byte ftYs_SpecialN2_0_Coll
	.4byte ftCamera_UpdateCameraBox
	.4byte 0x00000129
	.4byte 0x00340011
	.4byte 0x12000000
	.4byte ftYs_SpecialN2_1_Anim
	.4byte 0x00000000
	.4byte ftYs_SpecialN2_1_Phys
	.4byte ftYs_SpecialN2_1_Coll
	.4byte ftCamera_UpdateCameraBox
	.4byte 0x0000012A
	.4byte 0x00340411
	.4byte 0x12000000
	.4byte ftYs_SpecialAirN1_0_Anim
	.4byte 0x00000000
	.4byte ftYs_SpecialAirN1_0_Phys
	.4byte ftYs_SpecialAirN1_0_Coll
	.4byte ftCamera_UpdateCameraBox
	.4byte 0x0000012B
	.4byte 0x00340411
	.4byte 0x12000000
	.4byte ftYs_SpecialAirN1_1_Anim
	.4byte 0x00000000
	.4byte ftYs_SpecialAirN1_1_Phys
	.4byte ftYs_SpecialAirN1_1_Coll
	.4byte ftCamera_UpdateCameraBox
	.4byte 0x0000012B
	.4byte 0x00340411
	.4byte 0x12000000
	.4byte ftYs_SpecialAirN1_2_Anim
	.4byte 0x00000000
	.4byte ftYs_SpecialAirN1_2_Phys
	.4byte ftYs_SpecialAirN1_2_Coll
	.4byte ftCamera_UpdateCameraBox
	.4byte 0x0000012C
	.4byte 0x00340411
	.4byte 0x12000000
	.4byte ftYs_SpecialAirN2_0_Anim
	.4byte 0x00000000
	.4byte ftYs_SpecialAirN2_0_Phys
	.4byte ftYs_SpecialAirN2_0_Coll
	.4byte ftCamera_UpdateCameraBox
	.4byte 0x0000012C
	.4byte 0x00340411
	.4byte 0x12000000
	.4byte ftYs_SpecialAirN2_1_Anim
	.4byte 0x00000000
	.4byte ftYs_SpecialAirN2_1_Phys
	.4byte ftYs_SpecialAirN2_1_Coll
	.4byte ftCamera_UpdateCameraBox
	.4byte 0x0000012D
	.4byte 0x00340212
	.4byte 0x13000000
	.4byte ftYs_SpecialAirSStart_0_Anim
	.4byte ftYs_SpecialAirSStart_0_IASA
	.4byte ftYs_SpecialAirSStart_0_Phys
	.4byte ftYs_SpecialAirSStart_0_Coll
	.4byte ftCamera_UpdateCameraBox
	.4byte 0x0000012E
	.4byte 0x00340212
	.4byte 0x13000000
	.4byte ftYs_SpecialAirSLoop_0_Anim
	.4byte ftYs_SpecialAirSLoop_0_IASA
	.4byte ftYs_SpecialAirSLoop_0_Phys
	.4byte ftYs_SpecialAirSLoop_0_Coll
	.4byte ftCamera_UpdateCameraBox
	.4byte 0x0000012F
	.4byte 0x00340212
	.4byte 0x13000000
	.4byte ftYs_SpecialAirSLoop_1_Anim
	.4byte ftYs_SpecialAirSLoop_1_IASA
	.4byte ftYs_SpecialAirSLoop_1_Phys
	.4byte ftYs_SpecialAirSLoop_1_Coll
	.4byte ftCamera_UpdateCameraBox
	.4byte 0x00000130
	.4byte 0x00340212
	.4byte 0x13000000
	.4byte ftYs_SpecialAirSEnd_Anim
	.4byte ftYs_SpecialAirSEnd_IASA
	.4byte ftYs_SpecialAirSEnd_Phys
	.4byte ftYs_SpecialAirSEnd_Coll
	.4byte ftCamera_UpdateCameraBox
	.4byte 0x00000131
	.4byte 0x00340612
	.4byte 0x13000000
	.4byte ftYs_SpecialAirSStart_1_Anim
	.4byte ftYs_SpecialAirSStart_1_IASA
	.4byte ftYs_SpecialAirSStart_1_Phys
	.4byte ftYs_SpecialAirSStart_1_Coll
	.4byte ftCamera_UpdateCameraBox
	.4byte 0x00000132
	.4byte 0x00340612
	.4byte 0x13000000
	.4byte ftYs_SpecialAirSLoop_2_Anim
	.4byte ftYs_SpecialAirSLoop_2_IASA
	.4byte ftYs_SpecialAirSLoop_2_Phys
	.4byte ftYs_SpecialAirSLoop_2_Coll
	.4byte ftCamera_UpdateCameraBox
	.4byte 0x00000133
	.4byte 0x00340612
	.4byte 0x13000000
	.4byte ftYs_SpecialAirSLoop_3_Anim
	.4byte ftYs_SpecialAirSLoop_3_IASA
	.4byte ftYs_SpecialAirSLoop_3_Phys
	.4byte ftYs_SpecialAirSLoop_3_Coll
	.4byte ftCamera_UpdateCameraBox
	.4byte 0x00000134
	.4byte 0x00340612
	.4byte 0x13000000
	.4byte ftYs_SpecialAirSLanding_Anim
	.4byte ftYs_SpecialAirSLanding_IASA
	.4byte ftYs_SpecialAirSLanding_Phys
	.4byte ftYs_SpecialAirSLanding_Coll
	.4byte ftCamera_UpdateCameraBox
	.4byte 0x00000135
	.4byte 0x00340113
	.4byte 0x14000000
	.4byte ftYs_SpecialHi_Anim
	.4byte 0x00000000
	.4byte ftYs_SpecialHi_Phys
	.4byte ftYs_SpecialHi_Coll
	.4byte ftCamera_UpdateCameraBox
	.4byte 0x00000136
	.4byte 0x00340513
	.4byte 0x14000000
	.4byte ftYs_SpecialAirHi_Anim
	.4byte 0x00000000
	.4byte ftYs_SpecialAirHi_Phys
	.4byte ftYs_SpecialAirHi_Coll
	.4byte ftCamera_UpdateCameraBox
	.4byte 0x00000137
	.4byte 0x00340214
	.4byte 0x15000000
	.4byte ftYs_SpecialLw_Anim
	.4byte 0x00000000
	.4byte ftYs_SpecialLw_Phys
	.4byte ftYs_SpecialLw_Coll
	.4byte ftCamera_UpdateCameraBox
	.4byte 0x00000138
	.4byte 0x00340214
	.4byte 0x15000000
	.4byte ftYs_SpecialLwLanding_Anim
	.4byte 0x00000000
	.4byte ftYs_SpecialLwLanding_Phys
	.4byte ftYs_SpecialLwLanding_Coll
	.4byte ftCamera_UpdateCameraBox
	.4byte 0x00000139
	.4byte 0x00340614
	.4byte 0x15000000
	.4byte ftYs_SpecialAirLw_Anim
	.4byte 0x00000000
	.4byte ftYs_SpecialAirLw_Phys
	.4byte ftYs_SpecialAirLw_Coll
	.4byte ftCamera_UpdateCameraBox
.endobj ftYs_Init_MotionStateTable

.obj "@242", local
	.4byte 0x796F7368
	.4byte 0x69206D61
	.4byte 0x74616E69
	.4byte 0x6D206672
	.4byte 0x616D6520
	.4byte 0x6E6F7420
	.4byte 0x73616D65
	.2byte 0x0A00
.endobj "@242"

.obj gap_07_803CEA6E_data, global
.hidden gap_07_803CEA6E_data
	.2byte 0x0000
.endobj gap_07_803CEA6E_data

.obj "@243", local
	.4byte 0x6674796F
	.4byte 0x7368692E
	.2byte 0x6300
.endobj "@243"

.obj gap_07_803CEA7A_data, global
.hidden gap_07_803CEA7A_data
	.2byte 0x0000
.endobj gap_07_803CEA7A_data

.obj "@273", local
	.4byte 0x796F7368
	.4byte 0x69207061
	.4byte 0x7274735F
	.4byte 0x6D6F6465
	.4byte 0x6C204E55
	.4byte 0x4C4C2121
	.2byte 0x0A00
.endobj "@273"

.obj gap_07_803CEA96_data, global
.hidden gap_07_803CEA96_data
	.2byte 0x0000
.endobj gap_07_803CEA96_data

# 0x00000000 - 0x00000018
.section .sdata, "wa"
.balign 8

.obj "@240", local
	.4byte 0x616F626A
	.byte 0x2E, 0x68, 0x00
.endobj "@240"

.obj gap_09_804D3E47_sdata, global
.hidden gap_09_804D3E47_sdata
	.byte 0x00
.endobj gap_09_804D3E47_sdata

.obj "@241", local
	.4byte 0x616F626A
	.byte 0x00
.endobj "@241"

.obj gap_09_804D3E4D_sdata, global
.hidden gap_09_804D3E4D_sdata
	.byte 0x00, 0x00, 0x00
.endobj gap_09_804D3E4D_sdata

.obj "@244", local
	.2byte 0x3000
.endobj "@244"

.obj gap_09_804D3E52_sdata, global
.hidden gap_09_804D3E52_sdata
	.4byte 0x00000000
	.2byte 0x0000
.endobj gap_09_804D3E52_sdata

# 0x00000000 - 0x00000010
.section .sdata2, "a"
.balign 8

.obj "@239", local
	.4byte 0x00000000
.endobj "@239"

.obj "@259", local
	.4byte 0x3F800000
.endobj "@259"

.obj "@304", local
	.4byte 0x40400000
.endobj "@304"

.obj gap_11_804D9A24_sdata2, global
.hidden gap_11_804D9A24_sdata2
	.4byte 0x00000000
.endobj gap_11_804D9A24_sdata2
