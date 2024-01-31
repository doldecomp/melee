.include "macros.inc"
.file "trigf.c"

# 0x00000000 - 0x000003EC
.text
.balign 4

.fn tanf, global
/* 00000000 00000040  7C 08 02 A6 */	mflr r0
/* 00000004 00000044  90 01 00 04 */	stw r0, 0x4(r1)
/* 00000008 00000048  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 0000000C 0000004C  DB E1 00 18 */	stfd f31, 0x18(r1)
/* 00000010 00000050  DB C1 00 10 */	stfd f30, 0x10(r1)
/* 00000014 00000054  FF C0 08 90 */	fmr f30, f1
/* 00000018 00000058  48 00 00 01 */	bl cos__Ff
/* 0000001C 0000005C  FF E0 08 90 */	fmr f31, f1
/* 00000020 00000060  FC 20 F0 90 */	fmr f1, f30
/* 00000024 00000064  48 00 00 01 */	bl sin__Ff
/* 00000028 00000068  EC 21 F8 24 */	fdivs f1, f1, f31
/* 0000002C 0000006C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 00000030 00000070  CB E1 00 18 */	lfd f31, 0x18(r1)
/* 00000034 00000074  CB C1 00 10 */	lfd f30, 0x10(r1)
/* 00000038 00000078  7C 08 03 A6 */	mtlr r0
/* 0000003C 0000007C  38 21 00 20 */	addi r1, r1, 0x20
/* 00000040 00000080  4E 80 00 20 */	blr
.endfn tanf

# cos(float)
.fn cos__Ff, global
/* 00000044 00000084  7C 08 02 A6 */	mflr r0
/* 00000048 00000088  90 01 00 04 */	stw r0, 0x4(r1)
/* 0000004C 0000008C  94 21 FF F8 */	stwu r1, -0x8(r1)
/* 00000050 00000090  48 00 00 01 */	bl cosf
/* 00000054 00000094  80 01 00 0C */	lwz r0, 0xc(r1)
/* 00000058 00000098  38 21 00 08 */	addi r1, r1, 0x8
/* 0000005C 0000009C  7C 08 03 A6 */	mtlr r0
/* 00000060 000000A0  4E 80 00 20 */	blr
.endfn cos__Ff

# sin(float)
.fn sin__Ff, global
/* 00000064 000000A4  7C 08 02 A6 */	mflr r0
/* 00000068 000000A8  90 01 00 04 */	stw r0, 0x4(r1)
/* 0000006C 000000AC  94 21 FF F8 */	stwu r1, -0x8(r1)
/* 00000070 000000B0  48 00 00 01 */	bl sinf
/* 00000074 000000B4  80 01 00 0C */	lwz r0, 0xc(r1)
/* 00000078 000000B8  38 21 00 08 */	addi r1, r1, 0x8
/* 0000007C 000000BC  7C 08 03 A6 */	mtlr r0
/* 00000080 000000C0  4E 80 00 20 */	blr
.endfn sin__Ff

.fn cosf, global
/* 00000084 000000C4  7C 08 02 A6 */	mflr r0
/* 00000088 000000C8  3C 60 00 00 */	lis r3, __four_over_pi_m1@ha
/* 0000008C 000000CC  90 01 00 04 */	stw r0, 0x4(r1)
/* 00000090 000000D0  38 63 00 00 */	addi r3, r3, __four_over_pi_m1@l
/* 00000094 000000D4  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 00000098 000000D8  DB E1 00 20 */	stfd f31, 0x20(r1)
/* 0000009C 000000DC  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 000000A0 000000E0  D0 21 00 08 */	stfs f1, 0x8(r1)
/* 000000A4 000000E4  C0 00 00 00 */	lfs f0, __two_over_pi@sda21(r0)
/* 000000A8 000000E8  80 01 00 08 */	lwz r0, 0x8(r1)
/* 000000AC 000000EC  C0 C1 00 08 */	lfs f6, 0x8(r1)
/* 000000B0 000000F0  54 00 00 01 */	clrrwi. r0, r0, 31
/* 000000B4 000000F4  EC 20 01 B2 */	fmuls f1, f0, f6
/* 000000B8 000000F8  41 82 00 1C */	beq .L_000000D4
/* 000000BC 000000FC  C0 00 00 00 */	lfs f0, MSL_TrigF_804DE19C@sda21(r0)
/* 000000C0 00000100  EC 01 00 28 */	fsubs f0, f1, f0
/* 000000C4 00000104  FC 00 00 1E */	fctiwz f0, f0
/* 000000C8 00000108  D8 01 00 10 */	stfd f0, 0x10(r1)
/* 000000CC 0000010C  80 81 00 14 */	lwz r4, 0x14(r1)
/* 000000D0 00000110  48 00 00 18 */	b .L_000000E8
.L_000000D4:
/* 000000D4 00000114  C0 00 00 00 */	lfs f0, MSL_TrigF_804DE19C@sda21(r0)
/* 000000D8 00000118  EC 00 08 2A */	fadds f0, f0, f1
/* 000000DC 0000011C  FC 00 00 1E */	fctiwz f0, f0
/* 000000E0 00000120  D8 01 00 10 */	stfd f0, 0x10(r1)
/* 000000E4 00000124  80 81 00 14 */	lwz r4, 0x14(r1)
.L_000000E8:
/* 000000E8 00000128  54 80 08 3C */	slwi r0, r4, 1
/* 000000EC 0000012C  C8 20 00 00 */	lfd f1, MSL_TrigF_804DE1A8@sda21(r0)
/* 000000F0 00000130  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 000000F4 00000134  C0 43 00 00 */	lfs f2, 0x0(r3)
/* 000000F8 00000138  90 01 00 14 */	stw r0, 0x14(r1)
/* 000000FC 0000013C  3C 00 43 30 */	lis r0, 0x4330
/* 00000100 00000140  C0 63 00 04 */	lfs f3, 0x4(r3)
/* 00000104 00000144  54 9F 07 BE */	clrlwi r31, r4, 30
/* 00000108 00000148  90 01 00 10 */	stw r0, 0x10(r1)
/* 0000010C 0000014C  C0 83 00 08 */	lfs f4, 0x8(r3)
/* 00000110 00000150  C8 01 00 10 */	lfd f0, 0x10(r1)
/* 00000114 00000154  C0 A3 00 0C */	lfs f5, 0xc(r3)
/* 00000118 00000158  EC 00 08 28 */	fsubs f0, f0, f1
/* 0000011C 0000015C  EC 06 00 28 */	fsubs f0, f6, f0
/* 00000120 00000160  EC 02 01 BA */	fmadds f0, f2, f6, f0
/* 00000124 00000164  EC 03 01 BA */	fmadds f0, f3, f6, f0
/* 00000128 00000168  EC 04 01 BA */	fmadds f0, f4, f6, f0
/* 0000012C 0000016C  EF E5 01 BA */	fmadds f31, f5, f6, f0
/* 00000130 00000170  FC 20 F8 90 */	fmr f1, f31
/* 00000134 00000174  48 00 00 01 */	bl fabsf__Ff
/* 00000138 00000178  C0 00 00 00 */	lfs f0, __SQRT_FLT_EPSILON__@sda21(r0)
/* 0000013C 0000017C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 00000140 00000180  40 80 00 24 */	bge .L_00000164
/* 00000144 00000184  3C 60 00 00 */	lis r3, __sincos_on_quadrant@ha
/* 00000148 00000188  57 E4 18 38 */	slwi r4, r31, 3
/* 0000014C 0000018C  38 03 00 00 */	addi r0, r3, __sincos_on_quadrant@l
/* 00000150 00000190  7C 60 22 14 */	add r3, r0, r4
/* 00000154 00000194  C0 23 00 00 */	lfs f1, 0x0(r3)
/* 00000158 00000198  C0 03 00 04 */	lfs f0, 0x4(r3)
/* 0000015C 0000019C  EC 3F 00 7C */	fnmsubs f1, f31, f1, f0
/* 00000160 000001A0  48 00 00 A0 */	b .L_00000200
.L_00000164:
/* 00000164 000001A4  57 E0 07 FF */	clrlwi. r0, r31, 31
/* 00000168 000001A8  EC 9F 07 F2 */	fmuls f4, f31, f31
/* 0000016C 000001AC  41 82 00 50 */	beq .L_000001BC
/* 00000170 000001B0  3C 60 00 00 */	lis r3, __sincos_poly@ha
/* 00000174 000001B4  38 83 00 00 */	addi r4, r3, __sincos_poly@l
/* 00000178 000001B8  C0 44 00 04 */	lfs f2, 0x4(r4)
/* 0000017C 000001BC  3C 60 00 00 */	lis r3, __sincos_on_quadrant@ha
/* 00000180 000001C0  C0 24 00 0C */	lfs f1, 0xc(r4)
/* 00000184 000001C4  38 03 00 00 */	addi r0, r3, __sincos_on_quadrant@l
/* 00000188 000001C8  C0 04 00 14 */	lfs f0, 0x14(r4)
/* 0000018C 000001CC  EC 62 09 3A */	fmadds f3, f2, f4, f1
/* 00000190 000001D0  C0 44 00 1C */	lfs f2, 0x1c(r4)
/* 00000194 000001D4  C0 24 00 24 */	lfs f1, 0x24(r4)
/* 00000198 000001D8  57 E4 18 38 */	slwi r4, r31, 3
/* 0000019C 000001DC  7C 60 22 14 */	add r3, r0, r4
/* 000001A0 000001E0  EC 64 00 FA */	fmadds f3, f4, f3, f0
/* 000001A4 000001E4  C0 03 00 00 */	lfs f0, 0x0(r3)
/* 000001A8 000001E8  EC 44 10 FA */	fmadds f2, f4, f3, f2
/* 000001AC 000001EC  EC 24 08 BE */	fnmadds f1, f4, f2, f1
/* 000001B0 000001F0  EC 3F 00 72 */	fmuls f1, f31, f1
/* 000001B4 000001F4  EC 21 00 32 */	fmuls f1, f1, f0
/* 000001B8 000001F8  48 00 00 48 */	b .L_00000200
.L_000001BC:
/* 000001BC 000001FC  3C 60 00 00 */	lis r3, __sincos_poly@ha
/* 000001C0 00000200  38 83 00 00 */	addi r4, r3, __sincos_poly@l
/* 000001C4 00000204  C0 44 00 00 */	lfs f2, 0x0(r4)
/* 000001C8 00000208  3C 60 00 00 */	lis r3, __sincos_on_quadrant@ha
/* 000001CC 0000020C  C0 24 00 08 */	lfs f1, 0x8(r4)
/* 000001D0 00000210  38 63 00 00 */	addi r3, r3, __sincos_on_quadrant@l
/* 000001D4 00000214  57 E0 18 38 */	slwi r0, r31, 3
/* 000001D8 00000218  EC 62 09 3A */	fmadds f3, f2, f4, f1
/* 000001DC 0000021C  C0 04 00 10 */	lfs f0, 0x10(r4)
/* 000001E0 00000220  C0 44 00 18 */	lfs f2, 0x18(r4)
/* 000001E4 00000224  7C 63 02 14 */	add r3, r3, r0
/* 000001E8 00000228  C0 24 00 20 */	lfs f1, 0x20(r4)
/* 000001EC 0000022C  EC 64 00 FA */	fmadds f3, f4, f3, f0
/* 000001F0 00000230  C0 03 00 04 */	lfs f0, 0x4(r3)
/* 000001F4 00000234  EC 44 10 FA */	fmadds f2, f4, f3, f2
/* 000001F8 00000238  EC 24 08 BA */	fmadds f1, f4, f2, f1
/* 000001FC 0000023C  EC 21 00 32 */	fmuls f1, f1, f0
.L_00000200:
/* 00000200 00000240  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 00000204 00000244  CB E1 00 20 */	lfd f31, 0x20(r1)
/* 00000208 00000248  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 0000020C 0000024C  7C 08 03 A6 */	mtlr r0
/* 00000210 00000250  38 21 00 28 */	addi r1, r1, 0x28
/* 00000214 00000254  4E 80 00 20 */	blr
.endfn cosf

.fn sinf, global
/* 00000218 00000258  7C 08 02 A6 */	mflr r0
/* 0000021C 0000025C  3C 60 00 00 */	lis r3, __four_over_pi_m1@ha
/* 00000220 00000260  90 01 00 04 */	stw r0, 0x4(r1)
/* 00000224 00000264  38 63 00 00 */	addi r3, r3, __four_over_pi_m1@l
/* 00000228 00000268  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 0000022C 0000026C  DB E1 00 20 */	stfd f31, 0x20(r1)
/* 00000230 00000270  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 00000234 00000274  D0 21 00 08 */	stfs f1, 0x8(r1)
/* 00000238 00000278  C0 00 00 00 */	lfs f0, __two_over_pi@sda21(r0)
/* 0000023C 0000027C  80 01 00 08 */	lwz r0, 0x8(r1)
/* 00000240 00000280  C0 C1 00 08 */	lfs f6, 0x8(r1)
/* 00000244 00000284  54 00 00 01 */	clrrwi. r0, r0, 31
/* 00000248 00000288  EC 20 01 B2 */	fmuls f1, f0, f6
/* 0000024C 0000028C  41 82 00 1C */	beq .L_00000268
/* 00000250 00000290  C0 00 00 00 */	lfs f0, MSL_TrigF_804DE19C@sda21(r0)
/* 00000254 00000294  EC 01 00 28 */	fsubs f0, f1, f0
/* 00000258 00000298  FC 00 00 1E */	fctiwz f0, f0
/* 0000025C 0000029C  D8 01 00 10 */	stfd f0, 0x10(r1)
/* 00000260 000002A0  80 81 00 14 */	lwz r4, 0x14(r1)
/* 00000264 000002A4  48 00 00 18 */	b .L_0000027C
.L_00000268:
/* 00000268 000002A8  C0 00 00 00 */	lfs f0, MSL_TrigF_804DE19C@sda21(r0)
/* 0000026C 000002AC  EC 00 08 2A */	fadds f0, f0, f1
/* 00000270 000002B0  FC 00 00 1E */	fctiwz f0, f0
/* 00000274 000002B4  D8 01 00 10 */	stfd f0, 0x10(r1)
/* 00000278 000002B8  80 81 00 14 */	lwz r4, 0x14(r1)
.L_0000027C:
/* 0000027C 000002BC  54 80 08 3C */	slwi r0, r4, 1
/* 00000280 000002C0  C8 20 00 00 */	lfd f1, MSL_TrigF_804DE1A8@sda21(r0)
/* 00000284 000002C4  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 00000288 000002C8  C0 43 00 00 */	lfs f2, 0x0(r3)
/* 0000028C 000002CC  90 01 00 14 */	stw r0, 0x14(r1)
/* 00000290 000002D0  3C 00 43 30 */	lis r0, 0x4330
/* 00000294 000002D4  C0 63 00 04 */	lfs f3, 0x4(r3)
/* 00000298 000002D8  54 9F 07 BE */	clrlwi r31, r4, 30
/* 0000029C 000002DC  90 01 00 10 */	stw r0, 0x10(r1)
/* 000002A0 000002E0  C0 83 00 08 */	lfs f4, 0x8(r3)
/* 000002A4 000002E4  C8 01 00 10 */	lfd f0, 0x10(r1)
/* 000002A8 000002E8  C0 A3 00 0C */	lfs f5, 0xc(r3)
/* 000002AC 000002EC  EC 00 08 28 */	fsubs f0, f0, f1
/* 000002B0 000002F0  EC 06 00 28 */	fsubs f0, f6, f0
/* 000002B4 000002F4  EC 02 01 BA */	fmadds f0, f2, f6, f0
/* 000002B8 000002F8  EC 03 01 BA */	fmadds f0, f3, f6, f0
/* 000002BC 000002FC  EC 04 01 BA */	fmadds f0, f4, f6, f0
/* 000002C0 00000300  EF E5 01 BA */	fmadds f31, f5, f6, f0
/* 000002C4 00000304  FC 20 F8 90 */	fmr f1, f31
/* 000002C8 00000308  48 00 00 01 */	bl fabsf__Ff
/* 000002CC 0000030C  C0 00 00 00 */	lfs f0, __SQRT_FLT_EPSILON__@sda21(r0)
/* 000002D0 00000310  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 000002D4 00000314  40 80 00 34 */	bge .L_00000308
/* 000002D8 00000318  3C 60 00 00 */	lis r3, __sincos_on_quadrant@ha
/* 000002DC 0000031C  57 E4 18 38 */	slwi r4, r31, 3
/* 000002E0 00000320  38 03 00 00 */	addi r0, r3, __sincos_on_quadrant@l
/* 000002E4 00000324  7C 60 22 14 */	add r3, r0, r4
/* 000002E8 00000328  C0 23 00 04 */	lfs f1, 0x4(r3)
/* 000002EC 0000032C  3C 80 00 00 */	lis r4, __sincos_poly@ha
/* 000002F0 00000330  38 84 00 00 */	addi r4, r4, __sincos_poly@l
/* 000002F4 00000334  C0 03 00 00 */	lfs f0, 0x0(r3)
/* 000002F8 00000338  EC 3F 00 72 */	fmuls f1, f31, f1
/* 000002FC 0000033C  C0 44 00 24 */	lfs f2, 0x24(r4)
/* 00000300 00000340  EC 22 00 7A */	fmadds f1, f2, f1, f0
/* 00000304 00000344  48 00 00 A0 */	b .L_000003A4
.L_00000308:
/* 00000308 00000348  57 E0 07 FF */	clrlwi. r0, r31, 31
/* 0000030C 0000034C  EC 9F 07 F2 */	fmuls f4, f31, f31
/* 00000310 00000350  41 82 00 4C */	beq .L_0000035C
/* 00000314 00000354  3C 60 00 00 */	lis r3, __sincos_poly@ha
/* 00000318 00000358  38 83 00 00 */	addi r4, r3, __sincos_poly@l
/* 0000031C 0000035C  C0 44 00 00 */	lfs f2, 0x0(r4)
/* 00000320 00000360  3C 60 00 00 */	lis r3, __sincos_on_quadrant@ha
/* 00000324 00000364  C0 24 00 08 */	lfs f1, 0x8(r4)
/* 00000328 00000368  38 03 00 00 */	addi r0, r3, __sincos_on_quadrant@l
/* 0000032C 0000036C  C0 04 00 10 */	lfs f0, 0x10(r4)
/* 00000330 00000370  EC 62 09 3A */	fmadds f3, f2, f4, f1
/* 00000334 00000374  C0 44 00 18 */	lfs f2, 0x18(r4)
/* 00000338 00000378  C0 24 00 20 */	lfs f1, 0x20(r4)
/* 0000033C 0000037C  57 E4 18 38 */	slwi r4, r31, 3
/* 00000340 00000380  7C 60 22 14 */	add r3, r0, r4
/* 00000344 00000384  EC 64 00 FA */	fmadds f3, f4, f3, f0
/* 00000348 00000388  C0 03 00 00 */	lfs f0, 0x0(r3)
/* 0000034C 0000038C  EC 44 10 FA */	fmadds f2, f4, f3, f2
/* 00000350 00000390  EC 24 08 BA */	fmadds f1, f4, f2, f1
/* 00000354 00000394  EC 21 00 32 */	fmuls f1, f1, f0
/* 00000358 00000398  48 00 00 4C */	b .L_000003A4
.L_0000035C:
/* 0000035C 0000039C  3C 60 00 00 */	lis r3, __sincos_poly@ha
/* 00000360 000003A0  38 83 00 00 */	addi r4, r3, __sincos_poly@l
/* 00000364 000003A4  C0 44 00 04 */	lfs f2, 0x4(r4)
/* 00000368 000003A8  3C 60 00 00 */	lis r3, __sincos_on_quadrant@ha
/* 0000036C 000003AC  C0 24 00 0C */	lfs f1, 0xc(r4)
/* 00000370 000003B0  38 63 00 00 */	addi r3, r3, __sincos_on_quadrant@l
/* 00000374 000003B4  57 E0 18 38 */	slwi r0, r31, 3
/* 00000378 000003B8  EC 62 09 3A */	fmadds f3, f2, f4, f1
/* 0000037C 000003BC  C0 04 00 14 */	lfs f0, 0x14(r4)
/* 00000380 000003C0  C0 44 00 1C */	lfs f2, 0x1c(r4)
/* 00000384 000003C4  7C 63 02 14 */	add r3, r3, r0
/* 00000388 000003C8  C0 24 00 24 */	lfs f1, 0x24(r4)
/* 0000038C 000003CC  EC 64 00 FA */	fmadds f3, f4, f3, f0
/* 00000390 000003D0  C0 03 00 04 */	lfs f0, 0x4(r3)
/* 00000394 000003D4  EC 44 10 FA */	fmadds f2, f4, f3, f2
/* 00000398 000003D8  EC 24 08 BA */	fmadds f1, f4, f2, f1
/* 0000039C 000003DC  EC 3F 00 72 */	fmuls f1, f31, f1
/* 000003A0 000003E0  EC 21 00 32 */	fmuls f1, f1, f0
.L_000003A4:
/* 000003A4 000003E4  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 000003A8 000003E8  CB E1 00 20 */	lfd f31, 0x20(r1)
/* 000003AC 000003EC  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 000003B0 000003F0  7C 08 03 A6 */	mtlr r0
/* 000003B4 000003F4  38 21 00 28 */	addi r1, r1, 0x28
/* 000003B8 000003F8  4E 80 00 20 */	blr
.endfn sinf

.fn __sinit_trigf_c, global
/* 000003BC 000003FC  3C 60 00 00 */	lis r3, tmp_float@ha
/* 000003C0 00000400  38 83 00 00 */	addi r4, r3, tmp_float@l
/* 000003C4 00000404  C0 04 00 00 */	lfs f0, 0x0(r4)
/* 000003C8 00000408  3C 60 00 00 */	lis r3, __four_over_pi_m1@ha
/* 000003CC 0000040C  D4 03 00 00 */	stfsu f0, __four_over_pi_m1@l(r3)
/* 000003D0 00000410  C0 04 00 04 */	lfs f0, 0x4(r4)
/* 000003D4 00000414  D0 03 00 04 */	stfs f0, 0x4(r3)
/* 000003D8 00000418  C0 04 00 08 */	lfs f0, 0x8(r4)
/* 000003DC 0000041C  D0 03 00 08 */	stfs f0, 0x8(r3)
/* 000003E0 00000420  C0 04 00 0C */	lfs f0, 0xc(r4)
/* 000003E4 00000424  D0 03 00 0C */	stfs f0, 0xc(r3)
/* 000003E8 00000428  4E 80 00 20 */	blr
.endfn __sinit_trigf_c

# 0x00000000 - 0x00000010
.rodata
.balign 8

.obj tmp_float, global
	.4byte 0x3E800000
	.4byte 0x3CBE6080
	.4byte 0x34372200
	.4byte 0x2DA44152
.endobj tmp_float

# 0x00000000 - 0x00000018
.data
.balign 8

.obj MSL_TrigF_80400770, global
	.4byte 0x7FFFFFFF
.endobj MSL_TrigF_80400770

.obj MSL_TrigF_80400774, global
	.4byte 0x7F800000
.endobj MSL_TrigF_80400774

.obj __four_over_pi_m1, global
	.4byte 0x00000000
	.4byte 0x00000000
	.4byte 0x00000000
	.4byte 0x00000000
.endobj __four_over_pi_m1

# 0x00000000 - 0x00000018
.section .sdata2, "a"
.balign 8

.obj __two_over_pi, global
	.4byte 0x3F22F983
.endobj __two_over_pi

.obj MSL_TrigF_804DE19C, global
	.4byte 0x3F000000
.endobj MSL_TrigF_804DE19C

.obj __SQRT_FLT_EPSILON__, global
	.4byte 0x39B504F3
.endobj __SQRT_FLT_EPSILON__

.obj gap_11_804DE1A4_sdata2, global
.hidden gap_11_804DE1A4_sdata2
	.4byte 0x00000000
.endobj gap_11_804DE1A4_sdata2

.obj MSL_TrigF_804DE1A8, global
	.4byte 0x43300000
	.4byte 0x80000000
.endobj MSL_TrigF_804DE1A8
