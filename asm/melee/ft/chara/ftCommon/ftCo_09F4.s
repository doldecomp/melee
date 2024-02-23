.include "macros.inc"
.file "ftCo_09F4.c"

# 0x00000000 - 0x000003B4
.text
.balign 4

.fn ftCo_8009F480, global
/* 00000000 00000040  7C 08 02 A6 */	mflr r0
/* 00000004 00000044  90 01 00 04 */	stw r0, 0x4(r1)
/* 00000008 00000048  94 21 FF F8 */	stwu r1, -0x8(r1)
/* 0000000C 0000004C  80 63 00 28 */	lwz r3, 0x28(r3)
/* 00000010 00000050  48 00 00 01 */	bl HSD_LObjAnimAll
/* 00000014 00000054  80 01 00 0C */	lwz r0, 0xc(r1)
/* 00000018 00000058  38 21 00 08 */	addi r1, r1, 0x8
/* 0000001C 0000005C  7C 08 03 A6 */	mtlr r0
/* 00000020 00000060  4E 80 00 20 */	blr
.endfn ftCo_8009F480

.fn ftCo_8009F4A4, global
/* 00000024 00000064  7C 08 02 A6 */	mflr r0
/* 00000028 00000068  38 60 00 0C */	li r3, 0xc
/* 0000002C 0000006C  90 01 00 04 */	stw r0, 0x4(r1)
/* 00000030 00000070  38 80 00 03 */	li r4, 0x3
/* 00000034 00000074  38 A0 00 00 */	li r5, 0x0
/* 00000038 00000078  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 0000003C 0000007C  93 E1 00 0C */	stw r31, 0xc(r1)
/* 00000040 00000080  93 C1 00 08 */	stw r30, 0x8(r1)
/* 00000044 00000084  48 00 00 01 */	bl GObj_Create
/* 00000048 00000088  7C 7F 1B 78 */	mr r31, r3
/* 0000004C 0000008C  48 00 00 01 */	bl Ground_801C49B4
/* 00000050 00000090  48 00 00 01 */	bl lb_80011AC4
/* 00000054 00000094  7C 7E 1B 78 */	mr r30, r3
/* 00000058 00000098  93 C0 00 00 */	stw r30, ftCo_804D6568@sda21(r0)
/* 0000005C 0000009C  48 00 00 01 */	bl lb_8000CDC0
/* 00000060 000000A0  90 60 00 00 */	stw r3, ftCo_804D656C@sda21(r0)
/* 00000064 000000A4  7F C3 F3 78 */	mr r3, r30
/* 00000068 000000A8  48 00 00 01 */	bl Ground_801C2374
/* 0000006C 000000AC  88 80 00 00 */	lbz r4, HSD_GObj_804D784A@sda21(r0)
/* 00000070 000000B0  38 7F 00 00 */	addi r3, r31, 0x0
/* 00000074 000000B4  38 BE 00 00 */	addi r5, r30, 0x0
/* 00000078 000000B8  48 00 00 01 */	bl HSD_GObjObject_80390A70
/* 0000007C 000000BC  3C 60 00 00 */	lis r3, ftCo_8009F54C@ha
/* 00000080 000000C0  38 83 00 00 */	addi r4, r3, ftCo_8009F54C@l
/* 00000084 000000C4  38 7F 00 00 */	addi r3, r31, 0x0
/* 00000088 000000C8  38 A0 00 04 */	li r5, 0x4
/* 0000008C 000000CC  38 C0 00 00 */	li r6, 0x0
/* 00000090 000000D0  48 00 00 01 */	bl GObj_SetupGXLink
/* 00000094 000000D4  7F C3 F3 78 */	mr r3, r30
/* 00000098 000000D8  C0 20 00 00 */	lfs f1, ftCo_804D87B0@sda21(r0)
/* 0000009C 000000DC  48 00 00 01 */	bl HSD_LObjReqAnimAll
/* 000000A0 000000E0  3C 60 00 00 */	lis r3, ftCo_8009F480@ha
/* 000000A4 000000E4  38 83 00 00 */	addi r4, r3, ftCo_8009F480@l
/* 000000A8 000000E8  38 7F 00 00 */	addi r3, r31, 0x0
/* 000000AC 000000EC  38 A0 00 01 */	li r5, 0x1
/* 000000B0 000000F0  48 00 00 01 */	bl HSD_GObjProc_8038FD54
/* 000000B4 000000F4  80 01 00 14 */	lwz r0, 0x14(r1)
/* 000000B8 000000F8  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 000000BC 000000FC  83 C1 00 08 */	lwz r30, 0x8(r1)
/* 000000C0 00000100  38 21 00 10 */	addi r1, r1, 0x10
/* 000000C4 00000104  7C 08 03 A6 */	mtlr r0
/* 000000C8 00000108  4E 80 00 20 */	blr
.endfn ftCo_8009F4A4

.fn ftCo_8009F54C, global
/* 000000CC 0000010C  7C 08 02 A6 */	mflr r0
/* 000000D0 00000110  90 01 00 04 */	stw r0, 0x4(r1)
/* 000000D4 00000114  94 21 FF F8 */	stwu r1, -0x8(r1)
/* 000000D8 00000118  80 63 00 28 */	lwz r3, 0x28(r3)
/* 000000DC 0000011C  48 00 00 01 */	bl HSD_LObj_803668EC
/* 000000E0 00000120  48 00 00 01 */	bl HSD_CObjGetCurrent
/* 000000E4 00000124  48 00 00 01 */	bl HSD_LObjSetupInit
/* 000000E8 00000128  80 01 00 0C */	lwz r0, 0xc(r1)
/* 000000EC 0000012C  38 21 00 08 */	addi r1, r1, 0x8
/* 000000F0 00000130  7C 08 03 A6 */	mtlr r0
/* 000000F4 00000134  4E 80 00 20 */	blr
.endfn ftCo_8009F54C

.fn ftCo_8009F578, global
/* 000000F8 00000138  7C 08 02 A6 */	mflr r0
/* 000000FC 0000013C  90 01 00 04 */	stw r0, 0x4(r1)
/* 00000100 00000140  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 00000104 00000144  93 E1 00 14 */	stw r31, 0x14(r1)
/* 00000108 00000148  3B E3 00 00 */	addi r31, r3, 0x0
/* 0000010C 0000014C  38 60 00 00 */	li r3, ftCo_804D3B50@sda21
/* 00000110 00000150  48 00 00 01 */	bl lb_80011AC4
/* 00000114 00000154  90 7F 05 88 */	stw r3, 0x588(r31)
/* 00000118 00000158  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 0000011C 0000015C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 00000120 00000160  38 21 00 18 */	addi r1, r1, 0x18
/* 00000124 00000164  7C 08 03 A6 */	mtlr r0
/* 00000128 00000168  4E 80 00 20 */	blr
.endfn ftCo_8009F578

.fn ftCo_8009F5AC, global
/* 0000012C 0000016C  7C 08 02 A6 */	mflr r0
/* 00000130 00000170  90 01 00 04 */	stw r0, 0x4(r1)
/* 00000134 00000174  94 21 FF A8 */	stwu r1, -0x58(r1)
/* 00000138 00000178  DB E1 00 50 */	stfd f31, 0x50(r1)
/* 0000013C 0000017C  DB C1 00 48 */	stfd f30, 0x48(r1)
/* 00000140 00000180  93 E1 00 44 */	stw r31, 0x44(r1)
/* 00000144 00000184  93 C1 00 40 */	stw r30, 0x40(r1)
/* 00000148 00000188  7C 7E 1B 78 */	mr r30, r3
/* 0000014C 0000018C  93 A1 00 3C */	stw r29, 0x3c(r1)
/* 00000150 00000190  48 00 00 01 */	bl ftCo_800C0658
/* 00000154 00000194  88 03 00 7C */	lbz r0, 0x7c(r3)
/* 00000158 00000198  7C 7F 1B 78 */	mr r31, r3
/* 0000015C 0000019C  54 00 D7 FF */	extrwi. r0, r0, 1, 25
/* 00000160 000001A0  41 82 01 58 */	beq .L_000002B8
/* 00000164 000001A4  88 1E 22 21 */	lbz r0, 0x2221(r30)
/* 00000168 000001A8  54 00 E7 FF */	extrwi. r0, r0, 1, 27
/* 0000016C 000001AC  41 82 01 1C */	beq .L_00000288
/* 00000170 000001B0  80 7E 00 00 */	lwz r3, 0x0(r30)
/* 00000174 000001B4  C0 20 00 00 */	lfs f1, ftCo_804D87B4@sda21(r0)
/* 00000178 000001B8  C0 1F 00 78 */	lfs f0, 0x78(r31)
/* 0000017C 000001BC  83 A3 00 28 */	lwz r29, 0x28(r3)
/* 00000180 000001C0  EF E1 00 32 */	fmuls f31, f1, f0
/* 00000184 000001C4  28 1D 00 00 */	cmplwi r29, 0x0
/* 00000188 000001C8  40 82 00 14 */	bne .L_0000019C
/* 0000018C 000001CC  38 60 00 00 */	li r3, ftCo_804D3B58@sda21
/* 00000190 000001D0  38 80 02 DA */	li r4, 0x2da
/* 00000194 000001D4  38 A0 00 00 */	li r5, ftCo_804D3B60@sda21
/* 00000198 000001D8  48 00 00 01 */	bl __assert
.L_0000019C:
/* 0000019C 000001DC  C0 20 00 00 */	lfs f1, ftCo_804D87B4@sda21(r0)
/* 000001A0 000001E0  FF E0 F8 50 */	fneg f31, f31
/* 000001A4 000001E4  C0 1F 00 74 */	lfs f0, 0x74(r31)
/* 000001A8 000001E8  C0 5D 00 20 */	lfs f2, 0x20(r29)
/* 000001AC 000001EC  EC 61 00 32 */	fmuls f3, f1, f0
/* 000001B0 000001F0  C8 00 00 00 */	lfd f0, ftCo_804D87B8@sda21(r0)
/* 000001B4 000001F4  FC 20 F8 90 */	fmr f1, f31
/* 000001B8 000001F8  EC 43 00 B2 */	fmuls f2, f3, f2
/* 000001BC 000001FC  FF C2 00 24 */	fdiv f30, f2, f0
/* 000001C0 00000200  FF C0 F0 18 */	frsp f30, f30
/* 000001C4 00000204  48 00 00 01 */	bl sinf
/* 000001C8 00000208  FC 00 08 50 */	fneg f0, f1
/* 000001CC 0000020C  FC 20 F8 90 */	fmr f1, f31
/* 000001D0 00000210  D0 01 00 2C */	stfs f0, 0x2c(r1)
/* 000001D4 00000214  48 00 00 01 */	bl cosf
/* 000001D8 00000218  D0 21 00 30 */	stfs f1, 0x30(r1)
/* 000001DC 0000021C  FC 20 F0 90 */	fmr f1, f30
/* 000001E0 00000220  48 00 00 01 */	bl sinf
/* 000001E4 00000224  C0 01 00 30 */	lfs f0, 0x30(r1)
/* 000001E8 00000228  EC 00 00 72 */	fmuls f0, f0, f1
/* 000001EC 0000022C  FC 20 F0 90 */	fmr f1, f30
/* 000001F0 00000230  D0 01 00 28 */	stfs f0, 0x28(r1)
/* 000001F4 00000234  48 00 00 01 */	bl cosf
/* 000001F8 00000238  C0 01 00 30 */	lfs f0, 0x30(r1)
/* 000001FC 0000023C  38 81 00 28 */	addi r4, r1, 0x28
/* 00000200 00000240  EC 00 00 72 */	fmuls f0, f0, f1
/* 00000204 00000244  D0 01 00 30 */	stfs f0, 0x30(r1)
/* 00000208 00000248  80 7E 05 88 */	lwz r3, 0x588(r30)
/* 0000020C 0000024C  48 00 00 01 */	bl HSD_LObjSetPosition
/* 00000210 00000250  88 1F 00 7C */	lbz r0, 0x7c(r31)
/* 00000214 00000254  54 00 DF FF */	extrwi. r0, r0, 1, 26
/* 00000218 00000258  41 82 00 40 */	beq .L_00000258
/* 0000021C 0000025C  3C 60 00 00 */	lis r3, ftDynamics_803C5794@ha
/* 00000220 00000260  38 63 00 00 */	addi r3, r3, ftDynamics_803C5794@l
/* 00000224 00000264  80 03 00 0C */	lwz r0, 0xc(r3)
/* 00000228 00000268  38 81 00 20 */	addi r4, r1, 0x20
/* 0000022C 0000026C  90 01 00 24 */	stw r0, 0x24(r1)
/* 00000230 00000270  88 1F 00 53 */	lbz r0, 0x53(r31)
/* 00000234 00000274  98 01 00 27 */	stb r0, 0x27(r1)
/* 00000238 00000278  80 01 00 24 */	lwz r0, 0x24(r1)
/* 0000023C 0000027C  90 01 00 20 */	stw r0, 0x20(r1)
/* 00000240 00000280  80 7E 05 88 */	lwz r3, 0x588(r30)
/* 00000244 00000284  48 00 00 01 */	bl HSD_LObjSetColor
/* 00000248 00000288  80 7E 05 88 */	lwz r3, 0x588(r30)
/* 0000024C 0000028C  38 80 00 10 */	li r4, 0x10
/* 00000250 00000290  48 00 00 01 */	bl HSD_LObjSetFlags
/* 00000254 00000294  48 00 00 24 */	b .L_00000278
.L_00000258:
/* 00000258 00000298  80 1F 00 50 */	lwz r0, 0x50(r31)
/* 0000025C 0000029C  38 81 00 1C */	addi r4, r1, 0x1c
/* 00000260 000002A0  90 01 00 1C */	stw r0, 0x1c(r1)
/* 00000264 000002A4  80 7E 05 88 */	lwz r3, 0x588(r30)
/* 00000268 000002A8  48 00 00 01 */	bl HSD_LObjSetColor
/* 0000026C 000002AC  80 7E 05 88 */	lwz r3, 0x588(r30)
/* 00000270 000002B0  38 80 00 10 */	li r4, 0x10
/* 00000274 000002B4  48 00 00 01 */	bl HSD_LObjClearFlags
.L_00000278:
/* 00000278 000002B8  88 1E 22 21 */	lbz r0, 0x2221(r30)
/* 0000027C 000002BC  38 60 00 00 */	li r3, 0x0
/* 00000280 000002C0  50 60 26 F6 */	rlwimi r0, r3, 4, 27, 27
/* 00000284 000002C4  98 1E 22 21 */	stb r0, 0x2221(r30)
.L_00000288:
/* 00000288 000002C8  88 1F 00 7C */	lbz r0, 0x7c(r31)
/* 0000028C 000002CC  54 00 DF FF */	extrwi. r0, r0, 1, 26
/* 00000290 000002D0  41 82 00 10 */	beq .L_000002A0
/* 00000294 000002D4  80 60 00 00 */	lwz r3, ftCo_804D6568@sda21(r0)
/* 00000298 000002D8  48 00 00 01 */	bl HSD_LObj_803668EC
/* 0000029C 000002DC  48 00 00 0C */	b .L_000002A8
.L_000002A0:
/* 000002A0 000002E0  80 60 00 00 */	lwz r3, ftCo_804D656C@sda21(r0)
/* 000002A4 000002E4  48 00 00 01 */	bl HSD_LObjSetCurrentAll
.L_000002A8:
/* 000002A8 000002E8  80 7E 05 88 */	lwz r3, 0x588(r30)
/* 000002AC 000002EC  48 00 00 01 */	bl HSD_LObjAddCurrent
/* 000002B0 000002F0  48 00 00 01 */	bl HSD_CObjGetCurrent
/* 000002B4 000002F4  48 00 00 01 */	bl HSD_LObjSetupInit
.L_000002B8:
/* 000002B8 000002F8  80 01 00 5C */	lwz r0, 0x5c(r1)
/* 000002BC 000002FC  CB E1 00 50 */	lfd f31, 0x50(r1)
/* 000002C0 00000300  CB C1 00 48 */	lfd f30, 0x48(r1)
/* 000002C4 00000304  83 E1 00 44 */	lwz r31, 0x44(r1)
/* 000002C8 00000308  83 C1 00 40 */	lwz r30, 0x40(r1)
/* 000002CC 0000030C  83 A1 00 3C */	lwz r29, 0x3c(r1)
/* 000002D0 00000310  38 21 00 58 */	addi r1, r1, 0x58
/* 000002D4 00000314  7C 08 03 A6 */	mtlr r0
/* 000002D8 00000318  4E 80 00 20 */	blr
.endfn ftCo_8009F5AC

.fn ftCo_8009F75C, global
/* 000002DC 0000031C  7C 08 02 A6 */	mflr r0
/* 000002E0 00000320  90 01 00 04 */	stw r0, 0x4(r1)
/* 000002E4 00000324  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 000002E8 00000328  93 E1 00 14 */	stw r31, 0x14(r1)
/* 000002EC 0000032C  3B E4 00 00 */	addi r31, r4, 0x0
/* 000002F0 00000330  93 C1 00 10 */	stw r30, 0x10(r1)
/* 000002F4 00000334  3B C3 00 00 */	addi r30, r3, 0x0
/* 000002F8 00000338  48 00 00 01 */	bl ftCo_800C0658
/* 000002FC 0000033C  88 63 00 7C */	lbz r3, 0x7c(r3)
/* 00000300 00000340  54 60 D7 FF */	extrwi. r0, r3, 1, 25
/* 00000304 00000344  41 82 00 5C */	beq .L_00000360
/* 00000308 00000348  54 60 DF FF */	extrwi. r0, r3, 1, 26
/* 0000030C 0000034C  41 82 00 54 */	beq .L_00000360
/* 00000310 00000350  2C 1F 00 00 */	cmpwi r31, 0x0
/* 00000314 00000354  41 82 00 14 */	beq .L_00000328
/* 00000318 00000358  80 7E 05 88 */	lwz r3, 0x588(r30)
/* 0000031C 0000035C  38 80 00 10 */	li r4, 0x10
/* 00000320 00000360  48 00 00 01 */	bl HSD_LObjSetFlags
/* 00000324 00000364  48 00 00 10 */	b .L_00000334
.L_00000328:
/* 00000328 00000368  80 7E 05 88 */	lwz r3, 0x588(r30)
/* 0000032C 0000036C  38 80 00 10 */	li r4, 0x10
/* 00000330 00000370  48 00 00 01 */	bl HSD_LObjClearFlags
.L_00000334:
/* 00000334 00000374  2C 1F 00 00 */	cmpwi r31, 0x0
/* 00000338 00000378  41 82 00 10 */	beq .L_00000348
/* 0000033C 0000037C  80 60 00 00 */	lwz r3, ftCo_804D6568@sda21(r0)
/* 00000340 00000380  48 00 00 01 */	bl HSD_LObj_803668EC
/* 00000344 00000384  48 00 00 0C */	b .L_00000350
.L_00000348:
/* 00000348 00000388  80 60 00 00 */	lwz r3, ftCo_804D656C@sda21(r0)
/* 0000034C 0000038C  48 00 00 01 */	bl HSD_LObjSetCurrentAll
.L_00000350:
/* 00000350 00000390  80 7E 05 88 */	lwz r3, 0x588(r30)
/* 00000354 00000394  48 00 00 01 */	bl HSD_LObjAddCurrent
/* 00000358 00000398  48 00 00 01 */	bl HSD_CObjGetCurrent
/* 0000035C 0000039C  48 00 00 01 */	bl HSD_LObjSetupInit
.L_00000360:
/* 00000360 000003A0  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 00000364 000003A4  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 00000368 000003A8  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 0000036C 000003AC  38 21 00 18 */	addi r1, r1, 0x18
/* 00000370 000003B0  7C 08 03 A6 */	mtlr r0
/* 00000374 000003B4  4E 80 00 20 */	blr
.endfn ftCo_8009F75C

.fn ftCo_8009F7F8, global
/* 00000378 000003B8  7C 08 02 A6 */	mflr r0
/* 0000037C 000003BC  90 01 00 04 */	stw r0, 0x4(r1)
/* 00000380 000003C0  94 21 FF F8 */	stwu r1, -0x8(r1)
/* 00000384 000003C4  48 00 00 01 */	bl ftCo_800C0658
/* 00000388 000003C8  88 03 00 7C */	lbz r0, 0x7c(r3)
/* 0000038C 000003CC  54 00 D7 FF */	extrwi. r0, r0, 1, 25
/* 00000390 000003D0  41 82 00 14 */	beq .L_000003A4
/* 00000394 000003D4  80 60 00 00 */	lwz r3, ftCo_804D6568@sda21(r0)
/* 00000398 000003D8  48 00 00 01 */	bl HSD_LObj_803668EC
/* 0000039C 000003DC  48 00 00 01 */	bl HSD_CObjGetCurrent
/* 000003A0 000003E0  48 00 00 01 */	bl HSD_LObjSetupInit
.L_000003A4:
/* 000003A4 000003E4  80 01 00 0C */	lwz r0, 0xc(r1)
/* 000003A8 000003E8  38 21 00 08 */	addi r1, r1, 0x8
/* 000003AC 000003EC  7C 08 03 A6 */	mtlr r0
/* 000003B0 000003F0  4E 80 00 20 */	blr
.endfn ftCo_8009F7F8

# 0x00000000 - 0x00000058
.data
.balign 8

.obj ftDynamics_assert_msg_0, local
	.4byte 0x66702D3E
	.4byte 0x64796E61
	.4byte 0x6D696373
	.4byte 0x5F6E756D
	.4byte 0x203C2046
	.4byte 0x745F4479
	.4byte 0x6E616D69
	.4byte 0x63735F4E
	.4byte 0x756D4D61
	.2byte 0x7800
.endobj ftDynamics_assert_msg_0

.obj gap_07_803C577E_data, global
.hidden gap_07_803C577E_data
	.2byte 0x0000
.endobj gap_07_803C577E_data

.obj ftDynamics_803C5780, local
	.4byte 0x00000000
	.4byte 0x3F11EB85
	.4byte 0x3F11EB85
	.4byte 0x3F11EB85
	.4byte 0x00000000
.endobj ftDynamics_803C5780

.obj ftDynamics_803C5794, global
	.4byte 0x00000000
	.4byte 0x00000000
	.4byte 0x00050000
	.4byte 0xFFFFFFFF
	.4byte ftDynamics_803C5780
	.4byte 0x00000000
	.4byte 0x00000000
.endobj ftDynamics_803C5794

# 0x00000000 - 0x00000020
.section .sdata, "wa"
.balign 8

.obj ftCo_804D3B48, local
	.4byte ftDynamics_803C5794
	.4byte 0x00000000
.endobj ftCo_804D3B48

.obj ftCo_804D3B50, global
	.4byte ftCo_804D3B48
	.4byte 0x00000000
.endobj ftCo_804D3B50

.obj ftCo_804D3B58, global
	.4byte 0x6A6F626A
	.4byte 0x2E680000
.endobj ftCo_804D3B58

.obj ftCo_804D3B60, global
	.4byte 0x6A6F626A
	.4byte 0x00000000
.endobj ftCo_804D3B60

# 0x00000000 - 0x00000008
.section .sbss, "wa", @nobits
.balign 8

.obj ftCo_804D6568, global
	.skip 0x4
.endobj ftCo_804D6568

.obj ftCo_804D656C, global
	.skip 0x4
.endobj ftCo_804D656C

# 0x00000000 - 0x00000010
.section .sdata2, "a"
.balign 8

.obj ftCo_804D87B0, local
	.4byte 0x00000000
.endobj ftCo_804D87B0

.obj ftCo_804D87B4, local
	.4byte 0x3C8EFA35
.endobj ftCo_804D87B4

.obj ftCo_804D87B8, local
	.4byte 0x3FF921FB
	.4byte 0x54442D18
.endobj ftCo_804D87B8
