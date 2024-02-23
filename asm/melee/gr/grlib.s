.include "macros.inc"
.file "grlib.c"

# 0x00000000 - 0x000009CC
.text
.balign 4

.fn grLib_801C96E8, global
/* 00000000 00000040  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 00000004 00000044  88 63 00 10 */	lbz r3, 0x10(r3)
/* 00000008 00000048  54 63 EF FE */	extrwi r3, r3, 1, 28
/* 0000000C 0000004C  4E 80 00 20 */	blr
.endfn grLib_801C96E8

.fn grLib_801C96F8, global
/* 00000010 00000050  7C 08 02 A6 */	mflr r0
/* 00000014 00000054  90 01 00 04 */	stw r0, 0x4(r1)
/* 00000018 00000058  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 0000001C 0000005C  93 E1 00 24 */	stw r31, 0x24(r1)
/* 00000020 00000060  93 C1 00 20 */	stw r30, 0x20(r1)
/* 00000024 00000064  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 00000028 00000068  3B A5 00 00 */	addi r29, r5, 0x0
/* 0000002C 0000006C  38 A3 00 00 */	addi r5, r3, 0x0
/* 00000030 00000070  38 60 00 00 */	li r3, 0x0
/* 00000034 00000074  48 00 00 01 */	bl hsd_8039F05C
/* 00000038 00000078  7C 7F 1B 79 */	mr. r31, r3
/* 0000003C 0000007C  41 82 00 98 */	beq .L_000000D4
/* 00000040 00000080  80 1F 00 54 */	lwz r0, 0x54(r31)
/* 00000044 00000084  28 00 00 00 */	cmplwi r0, 0x0
/* 00000048 00000088  7C 1E 03 78 */	mr r30, r0
/* 0000004C 0000008C  40 82 00 18 */	bne .L_00000064
/* 00000050 00000090  38 7F 00 00 */	addi r3, r31, 0x0
/* 00000054 00000094  38 80 00 01 */	li r4, 0x1
/* 00000058 00000098  48 00 00 01 */	bl psAddGeneratorAppSRT_begin
/* 0000005C 0000009C  7C 7E 1B 78 */	mr r30, r3
/* 00000060 000000A0  48 00 00 0C */	b .L_0000006C
.L_00000064:
/* 00000064 000000A4  38 00 00 00 */	li r0, 0x0
/* 00000068 000000A8  98 1E 00 A2 */	stb r0, 0xa2(r30)
.L_0000006C:
/* 0000006C 000000AC  28 1E 00 00 */	cmplwi r30, 0x0
/* 00000070 000000B0  40 82 00 14 */	bne .L_00000084
/* 00000074 000000B4  7F E3 FB 78 */	mr r3, r31
/* 00000078 000000B8  48 00 00 01 */	bl hsd_8039D4DC
/* 0000007C 000000BC  38 60 00 00 */	li r3, 0x0
/* 00000080 000000C0  48 00 00 58 */	b .L_000000D8
.L_00000084:
/* 00000084 000000C4  80 7D 00 00 */	lwz r3, 0x0(r29)
/* 00000088 000000C8  80 1D 00 04 */	lwz r0, 0x4(r29)
/* 0000008C 000000CC  90 7E 00 08 */	stw r3, 0x8(r30)
/* 00000090 000000D0  90 1E 00 0C */	stw r0, 0xc(r30)
/* 00000094 000000D4  80 1D 00 08 */	lwz r0, 0x8(r29)
/* 00000098 000000D8  90 1E 00 10 */	stw r0, 0x10(r30)
/* 0000009C 000000DC  48 00 00 01 */	bl Ground_801C0498
/* 000000A0 000000E0  C0 1E 00 24 */	lfs f0, 0x24(r30)
/* 000000A4 000000E4  EC 00 00 72 */	fmuls f0, f0, f1
/* 000000A8 000000E8  D0 1E 00 24 */	stfs f0, 0x24(r30)
/* 000000AC 000000EC  C0 1E 00 28 */	lfs f0, 0x28(r30)
/* 000000B0 000000F0  EC 00 00 72 */	fmuls f0, f0, f1
/* 000000B4 000000F4  D0 1E 00 28 */	stfs f0, 0x28(r30)
/* 000000B8 000000F8  C0 1E 00 2C */	lfs f0, 0x2c(r30)
/* 000000BC 000000FC  EC 00 00 72 */	fmuls f0, f0, f1
/* 000000C0 00000100  D0 1E 00 2C */	stfs f0, 0x2c(r30)
/* 000000C4 00000104  C0 00 00 00 */	lfs f0, "@201"@sda21(r0)
/* 000000C8 00000108  D0 1F 00 2C */	stfs f0, 0x2c(r31)
/* 000000CC 0000010C  D0 1F 00 28 */	stfs f0, 0x28(r31)
/* 000000D0 00000110  D0 1F 00 24 */	stfs f0, 0x24(r31)
.L_000000D4:
/* 000000D4 00000114  7F E3 FB 78 */	mr r3, r31
.L_000000D8:
/* 000000D8 00000118  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 000000DC 0000011C  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 000000E0 00000120  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 000000E4 00000124  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 000000E8 00000128  38 21 00 28 */	addi r1, r1, 0x28
/* 000000EC 0000012C  7C 08 03 A6 */	mtlr r0
/* 000000F0 00000130  4E 80 00 20 */	blr
.endfn grLib_801C96F8

.fn grLib_801C97DC, global
/* 000000F4 00000134  7C 08 02 A6 */	mflr r0
/* 000000F8 00000138  38 C5 00 00 */	addi r6, r5, 0x0
/* 000000FC 0000013C  90 01 00 04 */	stw r0, 0x4(r1)
/* 00000100 00000140  38 A3 00 00 */	addi r5, r3, 0x0
/* 00000104 00000144  38 60 00 00 */	li r3, 0x0
/* 00000108 00000148  94 21 FF F8 */	stwu r1, -0x8(r1)
/* 0000010C 0000014C  48 00 00 01 */	bl hsd_8039F6CC
/* 00000110 00000150  80 01 00 0C */	lwz r0, 0xc(r1)
/* 00000114 00000154  38 21 00 08 */	addi r1, r1, 0x8
/* 00000118 00000158  7C 08 03 A6 */	mtlr r0
/* 0000011C 0000015C  4E 80 00 20 */	blr
.endfn grLib_801C97DC

.fn grLib_801C9808, global
/* 00000120 00000160  7C 08 02 A6 */	mflr r0
/* 00000124 00000164  38 C5 00 00 */	addi r6, r5, 0x0
/* 00000128 00000168  90 01 00 04 */	stw r0, 0x4(r1)
/* 0000012C 0000016C  38 A3 00 00 */	addi r5, r3, 0x0
/* 00000130 00000170  38 60 00 00 */	li r3, 0x0
/* 00000134 00000174  94 21 FF F8 */	stwu r1, -0x8(r1)
/* 00000138 00000178  48 00 00 01 */	bl hsd_8039EFAC
/* 0000013C 0000017C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 00000140 00000180  38 21 00 08 */	addi r1, r1, 0x8
/* 00000144 00000184  7C 08 03 A6 */	mtlr r0
/* 00000148 00000188  4E 80 00 20 */	blr
.endfn grLib_801C9808

.fn grLib_801C9834, global
/* 0000014C 0000018C  7C 08 02 A6 */	mflr r0
/* 00000150 00000190  90 01 00 04 */	stw r0, 0x4(r1)
/* 00000154 00000194  94 21 FF F8 */	stwu r1, -0x8(r1)
/* 00000158 00000198  48 00 00 01 */	bl hsd_8039D4DC
/* 0000015C 0000019C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 00000160 000001A0  38 21 00 08 */	addi r1, r1, 0x8
/* 00000164 000001A4  7C 08 03 A6 */	mtlr r0
/* 00000168 000001A8  4E 80 00 20 */	blr
.endfn grLib_801C9834

.fn grLib_801C9854, global
/* 0000016C 000001AC  7C 08 02 A6 */	mflr r0
/* 00000170 000001B0  90 01 00 04 */	stw r0, 0x4(r1)
/* 00000174 000001B4  94 21 FF F8 */	stwu r1, -0x8(r1)
/* 00000178 000001B8  48 00 00 01 */	bl hsd_8039D5DC
/* 0000017C 000001BC  80 01 00 0C */	lwz r0, 0xc(r1)
/* 00000180 000001C0  38 21 00 08 */	addi r1, r1, 0x8
/* 00000184 000001C4  7C 08 03 A6 */	mtlr r0
/* 00000188 000001C8  4E 80 00 20 */	blr
.endfn grLib_801C9854

.fn grLib_801C9874, global
/* 0000018C 000001CC  7C 08 02 A6 */	mflr r0
/* 00000190 000001D0  90 01 00 04 */	stw r0, 0x4(r1)
/* 00000194 000001D4  94 21 FF F8 */	stwu r1, -0x8(r1)
/* 00000198 000001D8  A0 03 00 16 */	lhz r0, 0x16(r3)
/* 0000019C 000001DC  60 00 00 80 */	ori r0, r0, 0x80
/* 000001A0 000001E0  B0 03 00 16 */	sth r0, 0x16(r3)
/* 000001A4 000001E4  48 00 00 01 */	bl hsd_8039D4DC
/* 000001A8 000001E8  80 01 00 0C */	lwz r0, 0xc(r1)
/* 000001AC 000001EC  38 21 00 08 */	addi r1, r1, 0x8
/* 000001B0 000001F0  7C 08 03 A6 */	mtlr r0
/* 000001B4 000001F4  4E 80 00 20 */	blr
.endfn grLib_801C9874

.fn grLib_801C98A0, global
/* 000001B8 000001F8  7C 08 02 A6 */	mflr r0
/* 000001BC 000001FC  90 01 00 04 */	stw r0, 0x4(r1)
/* 000001C0 00000200  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 000001C4 00000204  93 E1 00 14 */	stw r31, 0x14(r1)
/* 000001C8 00000208  93 C1 00 10 */	stw r30, 0x10(r1)
/* 000001CC 0000020C  7C 7E 1B 79 */	mr. r30, r3
/* 000001D0 00000210  41 82 00 38 */	beq .L_00000208
/* 000001D4 00000214  80 60 00 00 */	lwz r3, hsd_804D78FC@sda21(r0)
/* 000001D8 00000218  48 00 00 28 */	b .L_00000200
.L_000001DC:
/* 000001DC 0000021C  80 03 00 10 */	lwz r0, 0x10(r3)
/* 000001E0 00000220  83 E3 00 00 */	lwz r31, 0x0(r3)
/* 000001E4 00000224  7C 00 F0 40 */	cmplw r0, r30
/* 000001E8 00000228  40 82 00 14 */	bne .L_000001FC
/* 000001EC 0000022C  A0 03 00 16 */	lhz r0, 0x16(r3)
/* 000001F0 00000230  60 00 00 80 */	ori r0, r0, 0x80
/* 000001F4 00000234  B0 03 00 16 */	sth r0, 0x16(r3)
/* 000001F8 00000238  48 00 00 01 */	bl hsd_8039D4DC
.L_000001FC:
/* 000001FC 0000023C  7F E3 FB 78 */	mr r3, r31
.L_00000200:
/* 00000200 00000240  28 03 00 00 */	cmplwi r3, 0x0
/* 00000204 00000244  40 82 FF D8 */	bne .L_000001DC
.L_00000208:
/* 00000208 00000248  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 0000020C 0000024C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 00000210 00000250  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 00000214 00000254  38 21 00 18 */	addi r1, r1, 0x18
/* 00000218 00000258  7C 08 03 A6 */	mtlr r0
/* 0000021C 0000025C  4E 80 00 20 */	blr
.endfn grLib_801C98A0

.fn grLib_801C9908, global
/* 00000220 00000260  7C 08 02 A6 */	mflr r0
/* 00000224 00000264  90 01 00 04 */	stw r0, 0x4(r1)
/* 00000228 00000268  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 0000022C 0000026C  93 E1 00 14 */	stw r31, 0x14(r1)
/* 00000230 00000270  93 C1 00 10 */	stw r30, 0x10(r1)
/* 00000234 00000274  7C 7E 1B 79 */	mr. r30, r3
/* 00000238 00000278  41 82 00 88 */	beq .L_000002C0
/* 0000023C 0000027C  80 60 00 00 */	lwz r3, hsd_804D78FC@sda21(r0)
/* 00000240 00000280  48 00 00 28 */	b .L_00000268
.L_00000244:
/* 00000244 00000284  80 03 00 10 */	lwz r0, 0x10(r3)
/* 00000248 00000288  83 E3 00 00 */	lwz r31, 0x0(r3)
/* 0000024C 0000028C  7C 00 F0 40 */	cmplw r0, r30
/* 00000250 00000290  40 82 00 14 */	bne .L_00000264
/* 00000254 00000294  A0 03 00 16 */	lhz r0, 0x16(r3)
/* 00000258 00000298  60 00 00 80 */	ori r0, r0, 0x80
/* 0000025C 0000029C  B0 03 00 16 */	sth r0, 0x16(r3)
/* 00000260 000002A0  48 00 00 01 */	bl hsd_8039D4DC
.L_00000264:
/* 00000264 000002A4  7F E3 FB 78 */	mr r3, r31
.L_00000268:
/* 00000268 000002A8  28 03 00 00 */	cmplwi r3, 0x0
/* 0000026C 000002AC  40 82 FF D8 */	bne .L_00000244
/* 00000270 000002B0  80 1E 00 14 */	lwz r0, 0x14(r30)
/* 00000274 000002B4  54 00 04 E7 */	rlwinm. r0, r0, 0, 19, 19
/* 00000278 000002B8  40 82 00 48 */	bne .L_000002C0
/* 0000027C 000002BC  28 1E 00 00 */	cmplwi r30, 0x0
/* 00000280 000002C0  40 82 00 0C */	bne .L_0000028C
/* 00000284 000002C4  38 00 00 00 */	li r0, 0x0
/* 00000288 000002C8  48 00 00 08 */	b .L_00000290
.L_0000028C:
/* 0000028C 000002CC  80 1E 00 10 */	lwz r0, 0x10(r30)
.L_00000290:
/* 00000290 000002D0  7C 1E 03 78 */	mr r30, r0
/* 00000294 000002D4  48 00 00 24 */	b .L_000002B8
.L_00000298:
/* 00000298 000002D8  7F C3 F3 78 */	mr r3, r30
/* 0000029C 000002DC  48 00 00 01 */	bl grLib_801C9908
/* 000002A0 000002E0  28 1E 00 00 */	cmplwi r30, 0x0
/* 000002A4 000002E4  40 82 00 0C */	bne .L_000002B0
/* 000002A8 000002E8  38 00 00 00 */	li r0, 0x0
/* 000002AC 000002EC  48 00 00 08 */	b .L_000002B4
.L_000002B0:
/* 000002B0 000002F0  80 1E 00 08 */	lwz r0, 0x8(r30)
.L_000002B4:
/* 000002B4 000002F4  7C 1E 03 78 */	mr r30, r0
.L_000002B8:
/* 000002B8 000002F8  28 1E 00 00 */	cmplwi r30, 0x0
/* 000002BC 000002FC  40 82 FF DC */	bne .L_00000298
.L_000002C0:
/* 000002C0 00000300  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 000002C4 00000304  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 000002C8 00000308  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 000002CC 0000030C  38 21 00 18 */	addi r1, r1, 0x18
/* 000002D0 00000310  7C 08 03 A6 */	mtlr r0
/* 000002D4 00000314  4E 80 00 20 */	blr
.endfn grLib_801C9908

.fn grLib_801C99C0, global
/* 000002D8 00000318  7C 08 02 A6 */	mflr r0
/* 000002DC 0000031C  2C 06 00 00 */	cmpwi r6, 0x0
/* 000002E0 00000320  90 01 00 04 */	stw r0, 0x4(r1)
/* 000002E4 00000324  38 04 00 00 */	addi r0, r4, 0x0
/* 000002E8 00000328  38 C5 00 00 */	addi r6, r5, 0x0
/* 000002EC 0000032C  94 21 FF F8 */	stwu r1, -0x8(r1)
/* 000002F0 00000330  41 82 00 18 */	beq .L_00000308
/* 000002F4 00000334  38 83 00 00 */	addi r4, r3, 0x0
/* 000002F8 00000338  7C 05 03 78 */	mr r5, r0
/* 000002FC 0000033C  38 60 00 00 */	li r3, 0x0
/* 00000300 00000340  48 00 00 01 */	bl hsd_8039EFAC
/* 00000304 00000344  48 00 00 14 */	b .L_00000318
.L_00000308:
/* 00000308 00000348  38 83 00 00 */	addi r4, r3, 0x0
/* 0000030C 0000034C  7C 05 03 78 */	mr r5, r0
/* 00000310 00000350  38 60 00 00 */	li r3, 0x0
/* 00000314 00000354  48 00 00 01 */	bl hsd_8039F6CC
.L_00000318:
/* 00000318 00000358  80 01 00 0C */	lwz r0, 0xc(r1)
/* 0000031C 0000035C  38 21 00 08 */	addi r1, r1, 0x8
/* 00000320 00000360  7C 08 03 A6 */	mtlr r0
/* 00000324 00000364  4E 80 00 20 */	blr
.endfn grLib_801C99C0

.fn grLib_801C9A10, global
/* 00000328 00000368  7C 08 02 A6 */	mflr r0
/* 0000032C 0000036C  3C 60 00 00 */	lis r3, grLib_8049EF58@ha
/* 00000330 00000370  90 01 00 04 */	stw r0, 0x4(r1)
/* 00000334 00000374  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 00000338 00000378  93 E1 00 0C */	stw r31, 0xc(r1)
/* 0000033C 0000037C  3B E3 00 00 */	addi r31, r3, grLib_8049EF58@l
/* 00000340 00000380  38 9F 00 00 */	addi r4, r31, 0x0
/* 00000344 00000384  38 60 00 00 */	li r3, 0x0
/* 00000348 00000388  48 00 00 01 */	bl Ground_801C2D24
/* 0000034C 0000038C  38 60 00 01 */	li r3, 0x1
/* 00000350 00000390  38 9F 00 0C */	addi r4, r31, 0xc
/* 00000354 00000394  48 00 00 01 */	bl Ground_801C2D24
/* 00000358 00000398  38 60 00 02 */	li r3, 0x2
/* 0000035C 0000039C  38 9F 00 18 */	addi r4, r31, 0x18
/* 00000360 000003A0  48 00 00 01 */	bl Ground_801C2D24
/* 00000364 000003A4  38 60 00 03 */	li r3, 0x3
/* 00000368 000003A8  38 9F 00 24 */	addi r4, r31, 0x24
/* 0000036C 000003AC  48 00 00 01 */	bl Ground_801C2D24
/* 00000370 000003B0  7F E3 FB 78 */	mr r3, r31
/* 00000374 000003B4  80 01 00 14 */	lwz r0, 0x14(r1)
/* 00000378 000003B8  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 0000037C 000003BC  38 21 00 10 */	addi r1, r1, 0x10
/* 00000380 000003C0  7C 08 03 A6 */	mtlr r0
/* 00000384 000003C4  4E 80 00 20 */	blr
.endfn grLib_801C9A10

.fn grLib_801C9A70, global
/* 00000388 000003C8  7C 08 02 A6 */	mflr r0
/* 0000038C 000003CC  2C 03 00 02 */	cmpwi r3, 0x2
/* 00000390 000003D0  90 01 00 04 */	stw r0, 0x4(r1)
/* 00000394 000003D4  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 00000398 000003D8  93 E1 00 14 */	stw r31, 0x14(r1)
/* 0000039C 000003DC  93 C1 00 10 */	stw r30, 0x10(r1)
/* 000003A0 000003E0  3B C4 00 00 */	addi r30, r4, 0x0
/* 000003A4 000003E4  41 82 00 34 */	beq .L_000003D8
/* 000003A8 000003E8  40 80 00 14 */	bge .L_000003BC
/* 000003AC 000003EC  2C 03 00 00 */	cmpwi r3, 0x0
/* 000003B0 000003F0  41 82 00 18 */	beq .L_000003C8
/* 000003B4 000003F4  40 80 00 1C */	bge .L_000003D0
/* 000003B8 000003F8  48 00 00 30 */	b .L_000003E8
.L_000003BC:
/* 000003BC 000003FC  2C 03 00 04 */	cmpwi r3, 0x4
/* 000003C0 00000400  40 80 00 28 */	bge .L_000003E8
/* 000003C4 00000404  48 00 00 1C */	b .L_000003E0
.L_000003C8:
/* 000003C8 00000408  3B E0 00 00 */	li r31, 0x0
/* 000003CC 0000040C  48 00 00 2C */	b .L_000003F8
.L_000003D0:
/* 000003D0 00000410  3B E0 00 01 */	li r31, 0x1
/* 000003D4 00000414  48 00 00 24 */	b .L_000003F8
.L_000003D8:
/* 000003D8 00000418  3B E0 00 02 */	li r31, 0x2
/* 000003DC 0000041C  48 00 00 1C */	b .L_000003F8
.L_000003E0:
/* 000003E0 00000420  3B E0 00 03 */	li r31, 0x3
/* 000003E4 00000424  48 00 00 14 */	b .L_000003F8
.L_000003E8:
/* 000003E8 00000428  38 60 00 00 */	li r3, "@256"@sda21
/* 000003EC 0000042C  38 80 01 22 */	li r4, 0x122
/* 000003F0 00000430  38 A0 00 00 */	li r5, "@257"@sda21
/* 000003F4 00000434  48 00 00 01 */	bl __assert
.L_000003F8:
/* 000003F8 00000438  1C 9F 00 0C */	mulli r4, r31, 0xc
/* 000003FC 0000043C  3C 60 00 00 */	lis r3, grLib_8049EF58@ha
/* 00000400 00000440  38 03 00 00 */	addi r0, r3, grLib_8049EF58@l
/* 00000404 00000444  7C 80 22 14 */	add r4, r0, r4
/* 00000408 00000448  80 64 00 00 */	lwz r3, 0x0(r4)
/* 0000040C 0000044C  80 04 00 04 */	lwz r0, 0x4(r4)
/* 00000410 00000450  90 7E 00 00 */	stw r3, 0x0(r30)
/* 00000414 00000454  90 1E 00 04 */	stw r0, 0x4(r30)
/* 00000418 00000458  80 04 00 08 */	lwz r0, 0x8(r4)
/* 0000041C 0000045C  90 1E 00 08 */	stw r0, 0x8(r30)
/* 00000420 00000460  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 00000424 00000464  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 00000428 00000468  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 0000042C 0000046C  38 21 00 18 */	addi r1, r1, 0x18
/* 00000430 00000470  7C 08 03 A6 */	mtlr r0
/* 00000434 00000474  4E 80 00 20 */	blr
.endfn grLib_801C9A70

.fn grLib_801C9B20, global
/* 00000438 00000478  7C 08 02 A6 */	mflr r0
/* 0000043C 0000047C  90 01 00 04 */	stw r0, 0x4(r1)
/* 00000440 00000480  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 00000444 00000484  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 00000448 00000488  3B E5 00 00 */	addi r31, r5, 0x0
/* 0000044C 0000048C  93 C1 00 18 */	stw r30, 0x18(r1)
/* 00000450 00000490  3B C4 00 00 */	addi r30, r4, 0x0
/* 00000454 00000494  80 A4 00 04 */	lwz r5, 0x4(r4)
/* 00000458 00000498  7F E4 FB 78 */	mr r4, r31
/* 0000045C 0000049C  48 00 00 01 */	bl lb_8000FD48
/* 00000460 000004A0  38 7E 00 00 */	addi r3, r30, 0x0
/* 00000464 000004A4  38 9F 00 00 */	addi r4, r31, 0x0
/* 00000468 000004A8  48 00 00 01 */	bl lb_80011710
/* 0000046C 000004AC  80 01 00 24 */	lwz r0, 0x24(r1)
/* 00000470 000004B0  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 00000474 000004B4  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 00000478 000004B8  38 21 00 20 */	addi r1, r1, 0x20
/* 0000047C 000004BC  7C 08 03 A6 */	mtlr r0
/* 00000480 000004C0  4E 80 00 20 */	blr
.endfn grLib_801C9B20

.fn grLib_801C9B6C, global
/* 00000484 000004C4  7C 08 02 A6 */	mflr r0
/* 00000488 000004C8  90 01 00 04 */	stw r0, 0x4(r1)
/* 0000048C 000004CC  94 21 FF F8 */	stwu r1, -0x8(r1)
/* 00000490 000004D0  48 00 00 01 */	bl lb_8000FD18
/* 00000494 000004D4  80 01 00 0C */	lwz r0, 0xc(r1)
/* 00000498 000004D8  38 21 00 08 */	addi r1, r1, 0x8
/* 0000049C 000004DC  7C 08 03 A6 */	mtlr r0
/* 000004A0 000004E0  4E 80 00 20 */	blr
.endfn grLib_801C9B6C

.fn grLib_801C9B8C, global
/* 000004A4 000004E4  7C 08 02 A6 */	mflr r0
/* 000004A8 000004E8  38 80 00 00 */	li r4, 0x0
/* 000004AC 000004EC  90 01 00 04 */	stw r0, 0x4(r1)
/* 000004B0 000004F0  38 A0 00 00 */	li r5, 0x0
/* 000004B4 000004F4  38 C0 00 00 */	li r6, 0x0
/* 000004B8 000004F8  94 21 FF F8 */	stwu r1, -0x8(r1)
/* 000004BC 000004FC  38 E0 00 00 */	li r7, 0x0
/* 000004C0 00000500  39 00 00 00 */	li r8, 0x0
/* 000004C4 00000504  C0 20 00 00 */	lfs f1, "@201"@sda21(r0)
/* 000004C8 00000508  39 20 00 00 */	li r9, 0x0
/* 000004CC 0000050C  48 00 00 01 */	bl lb_8001044C
/* 000004D0 00000510  80 01 00 0C */	lwz r0, 0xc(r1)
/* 000004D4 00000514  38 21 00 08 */	addi r1, r1, 0x8
/* 000004D8 00000518  7C 08 03 A6 */	mtlr r0
/* 000004DC 0000051C  4E 80 00 20 */	blr
.endfn grLib_801C9B8C

.fn grLib_801C9BC8, local
/* 000004E0 00000520  7C 08 02 A6 */	mflr r0
/* 000004E4 00000524  90 01 00 04 */	stw r0, 0x4(r1)
/* 000004E8 00000528  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 000004EC 0000052C  DB E1 00 20 */	stfd f31, 0x20(r1)
/* 000004F0 00000530  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 000004F4 00000534  83 E3 00 28 */	lwz r31, 0x28(r3)
/* 000004F8 00000538  7F E3 FB 78 */	mr r3, r31
/* 000004FC 0000053C  48 00 00 01 */	bl HSD_JObjAnimAll
/* 00000500 00000540  28 1F 00 00 */	cmplwi r31, 0x0
/* 00000504 00000544  40 82 00 14 */	bne .L_00000518
/* 00000508 00000548  38 60 00 00 */	li r3, "@270"@sda21
/* 0000050C 0000054C  38 80 03 EE */	li r4, 0x3ee
/* 00000510 00000550  38 A0 00 00 */	li r5, "@271"@sda21
/* 00000514 00000554  48 00 00 01 */	bl __assert
.L_00000518:
/* 00000518 00000558  28 1F 00 00 */	cmplwi r31, 0x0
/* 0000051C 0000055C  C3 FF 00 3C */	lfs f31, 0x3c(r31)
/* 00000520 00000560  40 82 00 14 */	bne .L_00000534
/* 00000524 00000564  38 60 00 00 */	li r3, "@270"@sda21
/* 00000528 00000568  38 80 03 E1 */	li r4, 0x3e1
/* 0000052C 0000056C  38 A0 00 00 */	li r5, "@271"@sda21
/* 00000530 00000570  48 00 00 01 */	bl __assert
.L_00000534:
/* 00000534 00000574  C0 3F 00 38 */	lfs f1, 0x38(r31)
/* 00000538 00000578  FC 40 F8 90 */	fmr f2, f31
/* 0000053C 0000057C  48 00 00 01 */	bl Camera_8002A278
/* 00000540 00000580  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 00000544 00000584  CB E1 00 20 */	lfd f31, 0x20(r1)
/* 00000548 00000588  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 0000054C 0000058C  38 21 00 28 */	addi r1, r1, 0x28
/* 00000550 00000590  7C 08 03 A6 */	mtlr r0
/* 00000554 00000594  4E 80 00 20 */	blr
.endfn grLib_801C9BC8

.fn grLib_801C9C40, local
/* 00000558 00000598  7C 08 02 A6 */	mflr r0
/* 0000055C 0000059C  90 01 00 04 */	stw r0, 0x4(r1)
/* 00000560 000005A0  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 00000564 000005A4  DB E1 00 28 */	stfd f31, 0x28(r1)
/* 00000568 000005A8  93 E1 00 24 */	stw r31, 0x24(r1)
/* 0000056C 000005AC  93 C1 00 20 */	stw r30, 0x20(r1)
/* 00000570 000005B0  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 00000574 000005B4  7C 7D 1B 78 */	mr r29, r3
/* 00000578 000005B8  83 E3 00 28 */	lwz r31, 0x28(r3)
/* 0000057C 000005BC  83 DF 00 7C */	lwz r30, 0x7c(r31)
/* 00000580 000005C0  7F E3 FB 78 */	mr r3, r31
/* 00000584 000005C4  48 00 00 01 */	bl HSD_JObjAnimAll
/* 00000588 000005C8  28 1F 00 00 */	cmplwi r31, 0x0
/* 0000058C 000005CC  40 82 00 14 */	bne .L_000005A0
/* 00000590 000005D0  38 60 00 00 */	li r3, "@270"@sda21
/* 00000594 000005D4  38 80 03 EE */	li r4, 0x3ee
/* 00000598 000005D8  38 A0 00 00 */	li r5, "@271"@sda21
/* 0000059C 000005DC  48 00 00 01 */	bl __assert
.L_000005A0:
/* 000005A0 000005E0  28 1F 00 00 */	cmplwi r31, 0x0
/* 000005A4 000005E4  C3 FF 00 3C */	lfs f31, 0x3c(r31)
/* 000005A8 000005E8  40 82 00 14 */	bne .L_000005BC
/* 000005AC 000005EC  38 60 00 00 */	li r3, "@270"@sda21
/* 000005B0 000005F0  38 80 03 E1 */	li r4, 0x3e1
/* 000005B4 000005F4  38 A0 00 00 */	li r5, "@271"@sda21
/* 000005B8 000005F8  48 00 00 01 */	bl __assert
.L_000005BC:
/* 000005BC 000005FC  C0 3F 00 38 */	lfs f1, 0x38(r31)
/* 000005C0 00000600  FC 40 F8 90 */	fmr f2, f31
/* 000005C4 00000604  48 00 00 01 */	bl Camera_8002A278
/* 000005C8 00000608  28 1E 00 00 */	cmplwi r30, 0x0
/* 000005CC 0000060C  41 82 00 10 */	beq .L_000005DC
/* 000005D0 00000610  80 1E 00 00 */	lwz r0, 0x0(r30)
/* 000005D4 00000614  54 00 00 43 */	rlwinm. r0, r0, 0, 1, 1
/* 000005D8 00000618  41 82 00 0C */	beq .L_000005E4
.L_000005DC:
/* 000005DC 0000061C  7F A3 EB 78 */	mr r3, r29
/* 000005E0 00000620  48 00 00 01 */	bl HSD_GObjPLink_80390228
.L_000005E4:
/* 000005E4 00000624  80 01 00 34 */	lwz r0, 0x34(r1)
/* 000005E8 00000628  CB E1 00 28 */	lfd f31, 0x28(r1)
/* 000005EC 0000062C  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 000005F0 00000630  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 000005F4 00000634  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 000005F8 00000638  38 21 00 30 */	addi r1, r1, 0x30
/* 000005FC 0000063C  7C 08 03 A6 */	mtlr r0
/* 00000600 00000640  4E 80 00 20 */	blr
.endfn grLib_801C9C40

.fn grLib_801C9CEC, global
/* 00000604 00000644  7C 08 02 A6 */	mflr r0
/* 00000608 00000648  90 01 00 04 */	stw r0, 0x4(r1)
/* 0000060C 0000064C  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 00000610 00000650  BF 61 00 14 */	stmw r27, 0x14(r1)
/* 00000614 00000654  3B E3 00 00 */	addi r31, r3, 0x0
/* 00000618 00000658  2C 1F 00 01 */	cmpwi r31, 0x1
/* 0000061C 0000065C  40 82 00 0C */	bne .L_00000628
/* 00000620 00000660  3B 60 00 00 */	li r27, 0x0
/* 00000624 00000664  48 00 00 3C */	b .L_00000660
.L_00000628:
/* 00000628 00000668  2C 1F 00 02 */	cmpwi r31, 0x2
/* 0000062C 0000066C  40 82 00 0C */	bne .L_00000638
/* 00000630 00000670  3B 60 00 01 */	li r27, 0x1
/* 00000634 00000674  48 00 00 2C */	b .L_00000660
.L_00000638:
/* 00000638 00000678  2C 1F 00 03 */	cmpwi r31, 0x3
/* 0000063C 0000067C  40 82 00 0C */	bne .L_00000648
/* 00000640 00000680  3B 60 00 02 */	li r27, 0x2
/* 00000644 00000684  48 00 00 1C */	b .L_00000660
.L_00000648:
/* 00000648 00000688  2C 1F 00 04 */	cmpwi r31, 0x4
/* 0000064C 0000068C  40 82 00 0C */	bne .L_00000658
/* 00000650 00000690  3B 60 00 03 */	li r27, 0x3
/* 00000654 00000694  48 00 00 0C */	b .L_00000660
.L_00000658:
/* 00000658 00000698  38 60 00 00 */	li r3, 0x0
/* 0000065C 0000069C  48 00 00 E8 */	b .L_00000744
.L_00000660:
/* 00000660 000006A0  3C 60 00 00 */	lis r3, stage_info@ha
/* 00000664 000006A4  38 63 00 00 */	addi r3, r3, stage_info@l
/* 00000668 000006A8  3B C3 06 CC */	addi r30, r3, 0x6cc
/* 0000066C 000006AC  80 03 06 CC */	lwz r0, 0x6cc(r3)
/* 00000670 000006B0  28 00 00 00 */	cmplwi r0, 0x0
/* 00000674 000006B4  40 82 00 0C */	bne .L_00000680
/* 00000678 000006B8  38 60 00 00 */	li r3, 0x0
/* 0000067C 000006BC  48 00 00 C8 */	b .L_00000744
.L_00000680:
/* 00000680 000006C0  57 E5 06 3E */	clrlwi r5, r31, 24
/* 00000684 000006C4  38 60 00 03 */	li r3, 0x3
/* 00000688 000006C8  38 80 00 12 */	li r4, 0x12
/* 0000068C 000006CC  48 00 00 01 */	bl GObj_Create
/* 00000690 000006D0  80 9E 00 00 */	lwz r4, 0x0(r30)
/* 00000694 000006D4  7C 7D 1B 78 */	mr r29, r3
/* 00000698 000006D8  80 64 00 00 */	lwz r3, 0x0(r4)
/* 0000069C 000006DC  48 00 00 01 */	bl HSD_JObjLoadJoint
/* 000006A0 000006E0  3B 83 00 00 */	addi r28, r3, 0x0
/* 000006A4 000006E4  88 80 00 00 */	lbz r4, HSD_GObj_804D7849@sda21(r0)
/* 000006A8 000006E8  38 7D 00 00 */	addi r3, r29, 0x0
/* 000006AC 000006EC  38 BC 00 00 */	addi r5, r28, 0x0
/* 000006B0 000006F0  48 00 00 01 */	bl HSD_GObjObject_80390A70
/* 000006B4 000006F4  2C 1F 00 01 */	cmpwi r31, 0x1
/* 000006B8 000006F8  40 82 00 1C */	bne .L_000006D4
/* 000006BC 000006FC  3C 60 00 00 */	lis r3, grLib_801C9BC8@ha
/* 000006C0 00000700  38 83 00 00 */	addi r4, r3, grLib_801C9BC8@l
/* 000006C4 00000704  38 7D 00 00 */	addi r3, r29, 0x0
/* 000006C8 00000708  38 A0 00 01 */	li r5, 0x1
/* 000006CC 0000070C  48 00 00 01 */	bl HSD_GObjProc_8038FD54
/* 000006D0 00000710  48 00 00 18 */	b .L_000006E8
.L_000006D4:
/* 000006D4 00000714  3C 60 00 00 */	lis r3, grLib_801C9C40@ha
/* 000006D8 00000718  38 83 00 00 */	addi r4, r3, grLib_801C9C40@l
/* 000006DC 0000071C  38 7D 00 00 */	addi r3, r29, 0x0
/* 000006E0 00000720  38 A0 00 01 */	li r5, 0x1
/* 000006E4 00000724  48 00 00 01 */	bl HSD_GObjProc_8038FD54
.L_000006E8:
/* 000006E8 00000728  80 9E 00 00 */	lwz r4, 0x0(r30)
/* 000006EC 0000072C  57 60 10 3A */	slwi r0, r27, 2
/* 000006F0 00000730  38 7C 00 00 */	addi r3, r28, 0x0
/* 000006F4 00000734  80 84 00 04 */	lwz r4, 0x4(r4)
/* 000006F8 00000738  38 A0 00 00 */	li r5, 0x0
/* 000006FC 0000073C  38 C0 00 00 */	li r6, 0x0
/* 00000700 00000740  7C 84 00 2E */	lwzx r4, r4, r0
/* 00000704 00000744  48 00 00 01 */	bl HSD_JObjAddAnimAll
/* 00000708 00000748  7F 83 E3 78 */	mr r3, r28
/* 0000070C 0000074C  C0 20 00 00 */	lfs f1, "@201"@sda21(r0)
/* 00000710 00000750  48 00 00 01 */	bl HSD_JObjReqAnimAll
/* 00000714 00000754  2C 1F 00 01 */	cmpwi r31, 0x1
/* 00000718 00000758  40 82 00 28 */	bne .L_00000740
/* 0000071C 0000075C  3C 60 00 00 */	lis r3, HSD_AObjSetFlags@ha
/* 00000720 00000760  4C C6 31 82 */	crclr cr1eq
/* 00000724 00000764  38 C3 00 00 */	addi r6, r3, HSD_AObjSetFlags@l
/* 00000728 00000768  38 7C 00 00 */	addi r3, r28, 0x0
/* 0000072C 0000076C  38 80 00 06 */	li r4, 0x6
/* 00000730 00000770  38 A0 00 20 */	li r5, 0x20
/* 00000734 00000774  38 E0 00 03 */	li r7, 0x3
/* 00000738 00000778  3D 00 20 00 */	lis r8, 0x2000
/* 0000073C 0000077C  48 00 00 01 */	bl HSD_ForeachAnim
.L_00000740:
/* 00000740 00000780  7F A3 EB 78 */	mr r3, r29
.L_00000744:
/* 00000744 00000784  BB 61 00 14 */	lmw r27, 0x14(r1)
/* 00000748 00000788  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 0000074C 0000078C  38 21 00 28 */	addi r1, r1, 0x28
/* 00000750 00000790  7C 08 03 A6 */	mtlr r0
/* 00000754 00000794  4E 80 00 20 */	blr
.endfn grLib_801C9CEC

.fn grLib_801C9E40, global
/* 00000758 00000798  3C 60 00 00 */	lis r3, stage_info@ha
/* 0000075C 0000079C  38 63 00 00 */	addi r3, r3, stage_info@l
/* 00000760 000007A0  A8 63 07 08 */	lha r3, 0x708(r3)
/* 00000764 000007A4  4E 80 00 20 */	blr
.endfn grLib_801C9E40

.fn grLib_801C9E50, global
/* 00000768 000007A8  3C 80 00 00 */	lis r4, stage_info@ha
/* 0000076C 000007AC  38 84 00 00 */	addi r4, r4, stage_info@l
/* 00000770 000007B0  B0 64 07 08 */	sth r3, 0x708(r4)
/* 00000774 000007B4  4E 80 00 20 */	blr
.endfn grLib_801C9E50

.fn grLib_801C9E60, global
/* 00000778 000007B8  7C 08 02 A6 */	mflr r0
/* 0000077C 000007BC  3C 80 00 00 */	lis r4, stage_info@ha
/* 00000780 000007C0  90 01 00 04 */	stw r0, 0x4(r1)
/* 00000784 000007C4  38 84 00 00 */	addi r4, r4, stage_info@l
/* 00000788 000007C8  94 21 FF F8 */	stwu r1, -0x8(r1)
/* 0000078C 000007CC  80 04 00 88 */	lwz r0, 0x88(r4)
/* 00000790 000007D0  38 83 00 00 */	addi r4, r3, 0x0
/* 00000794 000007D4  2C 00 00 03 */	cmpwi r0, 0x3
/* 00000798 000007D8  40 82 00 14 */	bne .L_000007AC
/* 0000079C 000007DC  7C 83 23 78 */	mr r3, r4
/* 000007A0 000007E0  48 00 00 01 */	bl grRCruise_80201918
/* 000007A4 000007E4  38 60 00 01 */	li r3, 0x1
/* 000007A8 000007E8  48 00 00 48 */	b .L_000007F0
.L_000007AC:
/* 000007AC 000007EC  2C 00 00 13 */	cmpwi r0, 0x13
/* 000007B0 000007F0  40 82 00 14 */	bne .L_000007C4
/* 000007B4 000007F4  7C 83 23 78 */	mr r3, r4
/* 000007B8 000007F8  48 00 00 01 */	bl grBigBlue_801EF7D8
/* 000007BC 000007FC  38 60 00 01 */	li r3, 0x1
/* 000007C0 00000800  48 00 00 30 */	b .L_000007F0
.L_000007C4:
/* 000007C4 00000804  2C 00 00 16 */	cmpwi r0, 0x16
/* 000007C8 00000808  40 82 00 14 */	bne .L_000007DC
/* 000007CC 0000080C  7C 83 23 78 */	mr r3, r4
/* 000007D0 00000810  48 00 00 01 */	bl grIceMt_801FA728
/* 000007D4 00000814  38 60 00 01 */	li r3, 0x1
/* 000007D8 00000818  48 00 00 18 */	b .L_000007F0
.L_000007DC:
/* 000007DC 0000081C  C0 00 00 00 */	lfs f0, "@201"@sda21(r0)
/* 000007E0 00000820  38 60 00 00 */	li r3, 0x0
/* 000007E4 00000824  D0 04 00 08 */	stfs f0, 0x8(r4)
/* 000007E8 00000828  D0 04 00 04 */	stfs f0, 0x4(r4)
/* 000007EC 0000082C  D0 04 00 00 */	stfs f0, 0x0(r4)
.L_000007F0:
/* 000007F0 00000830  80 01 00 0C */	lwz r0, 0xc(r1)
/* 000007F4 00000834  38 21 00 08 */	addi r1, r1, 0x8
/* 000007F8 00000838  7C 08 03 A6 */	mtlr r0
/* 000007FC 0000083C  4E 80 00 20 */	blr
.endfn grLib_801C9E60

.fn grLib_801C9EE8, global
/* 00000800 00000840  7C 08 02 A6 */	mflr r0
/* 00000804 00000844  90 01 00 04 */	stw r0, 0x4(r1)
/* 00000808 00000848  94 21 FF A8 */	stwu r1, -0x58(r1)
/* 0000080C 0000084C  DB E1 00 50 */	stfd f31, 0x50(r1)
/* 00000810 00000850  FF E0 08 90 */	fmr f31, f1
/* 00000814 00000854  DB C1 00 48 */	stfd f30, 0x48(r1)
/* 00000818 00000858  DB A1 00 40 */	stfd f29, 0x40(r1)
/* 0000081C 0000085C  93 E1 00 3C */	stw r31, 0x3c(r1)
/* 00000820 00000860  93 C1 00 38 */	stw r30, 0x38(r1)
/* 00000824 00000864  7C 7E 1B 78 */	mr r30, r3
/* 00000828 00000868  80 80 00 00 */	lwz r4, HSD_GObj_Entities@sda21(r0)
/* 0000082C 0000086C  C0 A0 00 00 */	lfs f5, "@314"@sda21(r0)
/* 00000830 00000870  80 A4 00 20 */	lwz r5, 0x20(r4)
/* 00000834 00000874  C0 00 00 00 */	lfs f0, "@201"@sda21(r0)
/* 00000838 00000878  48 00 00 A0 */	b .L_000008D8
.L_0000083C:
/* 0000083C 0000087C  80 65 00 2C */	lwz r3, 0x2c(r5)
/* 00000840 00000880  C0 3E 00 04 */	lfs f1, 0x4(r30)
/* 00000844 00000884  C0 C3 07 98 */	lfs f6, 0x798(r3)
/* 00000848 00000888  C0 83 07 A0 */	lfs f4, 0x7a0(r3)
/* 0000084C 0000088C  C0 43 06 F8 */	lfs f2, 0x6f8(r3)
/* 00000850 00000890  EC 66 20 2A */	fadds f3, f6, f4
/* 00000854 00000894  EC 86 20 28 */	fsubs f4, f6, f4
/* 00000858 00000898  EC 45 10 FA */	fmadds f2, f5, f3, f2
/* 0000085C 0000089C  EC 65 F9 3A */	fmadds f3, f5, f4, f31
/* 00000860 000008A0  EC 22 08 28 */	fsubs f1, f2, f1
/* 00000864 000008A4  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 00000868 000008A8  40 80 00 08 */	bge .L_00000870
/* 0000086C 000008AC  FC 20 08 50 */	fneg f1, f1
.L_00000870:
/* 00000870 000008B0  FC 01 18 40 */	fcmpo cr0, f1, f3
/* 00000874 000008B4  40 81 00 0C */	ble .L_00000880
/* 00000878 000008B8  38 00 00 00 */	li r0, 0x0
/* 0000087C 000008BC  48 00 00 48 */	b .L_000008C4
.L_00000880:
/* 00000880 000008C0  C0 83 07 A4 */	lfs f4, 0x7a4(r3)
/* 00000884 000008C4  C0 C3 07 AC */	lfs f6, 0x7ac(r3)
/* 00000888 000008C8  C0 43 06 F4 */	lfs f2, 0x6f4(r3)
/* 0000088C 000008CC  EC 66 20 2A */	fadds f3, f6, f4
/* 00000890 000008D0  C0 3E 00 00 */	lfs f1, 0x0(r30)
/* 00000894 000008D4  EC 84 30 28 */	fsubs f4, f4, f6
/* 00000898 000008D8  EC 45 10 FA */	fmadds f2, f5, f3, f2
/* 0000089C 000008DC  EC 65 F9 3A */	fmadds f3, f5, f4, f31
/* 000008A0 000008E0  EC 22 08 28 */	fsubs f1, f2, f1
/* 000008A4 000008E4  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 000008A8 000008E8  40 80 00 08 */	bge .L_000008B0
/* 000008AC 000008EC  FC 20 08 50 */	fneg f1, f1
.L_000008B0:
/* 000008B0 000008F0  FC 01 18 40 */	fcmpo cr0, f1, f3
/* 000008B4 000008F4  40 81 00 0C */	ble .L_000008C0
/* 000008B8 000008F8  38 00 00 00 */	li r0, 0x0
/* 000008BC 000008FC  48 00 00 08 */	b .L_000008C4
.L_000008C0:
/* 000008C0 00000900  38 00 00 01 */	li r0, 0x1
.L_000008C4:
/* 000008C4 00000904  2C 00 00 00 */	cmpwi r0, 0x0
/* 000008C8 00000908  41 82 00 0C */	beq .L_000008D4
/* 000008CC 0000090C  38 60 00 01 */	li r3, 0x1
/* 000008D0 00000910  48 00 00 D8 */	b .L_000009A8
.L_000008D4:
/* 000008D4 00000914  80 A5 00 08 */	lwz r5, 0x8(r5)
.L_000008D8:
/* 000008D8 00000918  28 05 00 00 */	cmplwi r5, 0x0
/* 000008DC 0000091C  40 82 FF 60 */	bne .L_0000083C
/* 000008E0 00000920  83 E4 00 24 */	lwz r31, 0x24(r4)
/* 000008E4 00000924  C3 A0 00 00 */	lfs f29, "@314"@sda21(r0)
/* 000008E8 00000928  C3 C0 00 00 */	lfs f30, "@201"@sda21(r0)
/* 000008EC 0000092C  48 00 00 B0 */	b .L_0000099C
.L_000008F0:
/* 000008F0 00000930  7F E3 FB 78 */	mr r3, r31
/* 000008F4 00000934  48 00 00 01 */	bl itGetKind
/* 000008F8 00000938  2C 03 00 A0 */	cmpwi r3, 0xa0
/* 000008FC 0000093C  41 82 00 9C */	beq .L_00000998
/* 00000900 00000940  80 7F 00 2C */	lwz r3, 0x2c(r31)
/* 00000904 00000944  C0 1E 00 04 */	lfs f0, 0x4(r30)
/* 00000908 00000948  C0 83 04 20 */	lfs f4, 0x420(r3)
/* 0000090C 0000094C  C0 63 04 28 */	lfs f3, 0x428(r3)
/* 00000910 00000950  C0 23 03 80 */	lfs f1, 0x380(r3)
/* 00000914 00000954  EC 44 18 2A */	fadds f2, f4, f3
/* 00000918 00000958  EC 64 18 28 */	fsubs f3, f4, f3
/* 0000091C 0000095C  EC 3D 08 BA */	fmadds f1, f29, f2, f1
/* 00000920 00000960  EC 5D F8 FA */	fmadds f2, f29, f3, f31
/* 00000924 00000964  EC 01 00 28 */	fsubs f0, f1, f0
/* 00000928 00000968  FC 00 F0 40 */	fcmpo cr0, f0, f30
/* 0000092C 0000096C  40 80 00 08 */	bge .L_00000934
/* 00000930 00000970  FC 00 00 50 */	fneg f0, f0
.L_00000934:
/* 00000934 00000974  FC 00 10 40 */	fcmpo cr0, f0, f2
/* 00000938 00000978  40 81 00 0C */	ble .L_00000944
/* 0000093C 0000097C  38 00 00 00 */	li r0, 0x0
/* 00000940 00000980  48 00 00 48 */	b .L_00000988
.L_00000944:
/* 00000944 00000984  C0 63 04 2C */	lfs f3, 0x42c(r3)
/* 00000948 00000988  C0 83 04 34 */	lfs f4, 0x434(r3)
/* 0000094C 0000098C  C0 23 03 7C */	lfs f1, 0x37c(r3)
/* 00000950 00000990  EC 44 18 2A */	fadds f2, f4, f3
/* 00000954 00000994  C0 1E 00 00 */	lfs f0, 0x0(r30)
/* 00000958 00000998  EC 63 20 28 */	fsubs f3, f3, f4
/* 0000095C 0000099C  EC 3D 08 BA */	fmadds f1, f29, f2, f1
/* 00000960 000009A0  EC 5D F8 FA */	fmadds f2, f29, f3, f31
/* 00000964 000009A4  EC 01 00 28 */	fsubs f0, f1, f0
/* 00000968 000009A8  FC 00 F0 40 */	fcmpo cr0, f0, f30
/* 0000096C 000009AC  40 80 00 08 */	bge .L_00000974
/* 00000970 000009B0  FC 00 00 50 */	fneg f0, f0
.L_00000974:
/* 00000974 000009B4  FC 00 10 40 */	fcmpo cr0, f0, f2
/* 00000978 000009B8  40 81 00 0C */	ble .L_00000984
/* 0000097C 000009BC  38 00 00 00 */	li r0, 0x0
/* 00000980 000009C0  48 00 00 08 */	b .L_00000988
.L_00000984:
/* 00000984 000009C4  38 00 00 01 */	li r0, 0x1
.L_00000988:
/* 00000988 000009C8  2C 00 00 00 */	cmpwi r0, 0x0
/* 0000098C 000009CC  41 82 00 0C */	beq .L_00000998
/* 00000990 000009D0  38 60 00 01 */	li r3, 0x1
/* 00000994 000009D4  48 00 00 14 */	b .L_000009A8
.L_00000998:
/* 00000998 000009D8  83 FF 00 08 */	lwz r31, 0x8(r31)
.L_0000099C:
/* 0000099C 000009DC  28 1F 00 00 */	cmplwi r31, 0x0
/* 000009A0 000009E0  40 82 FF 50 */	bne .L_000008F0
/* 000009A4 000009E4  38 60 00 00 */	li r3, 0x0
.L_000009A8:
/* 000009A8 000009E8  80 01 00 5C */	lwz r0, 0x5c(r1)
/* 000009AC 000009EC  CB E1 00 50 */	lfd f31, 0x50(r1)
/* 000009B0 000009F0  CB C1 00 48 */	lfd f30, 0x48(r1)
/* 000009B4 000009F4  CB A1 00 40 */	lfd f29, 0x40(r1)
/* 000009B8 000009F8  83 E1 00 3C */	lwz r31, 0x3c(r1)
/* 000009BC 000009FC  83 C1 00 38 */	lwz r30, 0x38(r1)
/* 000009C0 00000A00  38 21 00 58 */	addi r1, r1, 0x58
/* 000009C4 00000A04  7C 08 03 A6 */	mtlr r0
/* 000009C8 00000A08  4E 80 00 20 */	blr
.endfn grLib_801C9EE8

# 0x00000000 - 0x00000048
.section .bss, "wa", @nobits
.balign 8

.obj grLib_8049EF58, local
	.skip 0x48
.endobj grLib_8049EF58

# 0x00000000 - 0x00000020
.section .sdata, "wa"
.balign 8

.obj "@256", local
	.4byte 0x67726C69
	.4byte 0x622E6300
.endobj "@256"

.obj "@257", local
	.2byte 0x3000
.endobj "@257"

.obj gap_09_804D457A_sdata, global
.hidden gap_09_804D457A_sdata
	.2byte 0x0000
.endobj gap_09_804D457A_sdata

.obj "@270", local
	.4byte 0x6A6F626A
	.byte 0x2E, 0x68, 0x00
.endobj "@270"

.obj gap_09_804D4583_sdata, global
.hidden gap_09_804D4583_sdata
	.byte 0x00
.endobj gap_09_804D4583_sdata

.obj "@271", local
	.4byte 0x6A6F626A
	.byte 0x00
.endobj "@271"

.obj gap_09_804D4589_sdata, global
.hidden gap_09_804D4589_sdata
	.4byte 0x00000000
	.byte 0x00, 0x00, 0x00
.endobj gap_09_804D4589_sdata

# 0x00000000 - 0x00000008
.section .sdata2, "a"
.balign 8

.obj "@201", local
	.4byte 0x00000000
.endobj "@201"

.obj "@314", local
	.4byte 0x3F000000
.endobj "@314"
