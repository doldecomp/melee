.include "macros.inc"
.file "vi0601.c"

# 0x00000000 - 0x000006A4
.text
.balign 4

.fn un_8031E6CC, global
/* 00000000 00000040  7C 08 02 A6 */	mflr r0
/* 00000004 00000044  90 01 00 04 */	stw r0, 0x4(r1)
/* 00000008 00000048  94 21 FF F8 */	stwu r1, -0x8(r1)
/* 0000000C 0000004C  48 00 00 01 */	bl un_8031CAAC
/* 00000010 00000050  80 01 00 0C */	lwz r0, 0xc(r1)
/* 00000014 00000054  38 21 00 08 */	addi r1, r1, 0x8
/* 00000018 00000058  7C 08 03 A6 */	mtlr r0
/* 0000001C 0000005C  4E 80 00 20 */	blr
.endfn un_8031E6CC

.fn un_8031E6EC, global
/* 00000020 00000060  7C 08 02 A6 */	mflr r0
/* 00000024 00000064  90 01 00 04 */	stw r0, 0x4(r1)
/* 00000028 00000068  94 21 FF F8 */	stwu r1, -0x8(r1)
/* 0000002C 0000006C  80 63 00 28 */	lwz r3, 0x28(r3)
/* 00000030 00000070  48 00 00 01 */	bl HSD_JObjAnimAll
/* 00000034 00000074  80 01 00 0C */	lwz r0, 0xc(r1)
/* 00000038 00000078  38 21 00 08 */	addi r1, r1, 0x8
/* 0000003C 0000007C  7C 08 03 A6 */	mtlr r0
/* 00000040 00000080  4E 80 00 20 */	blr
.endfn un_8031E6EC

.fn un_8031E710, global
/* 00000044 00000084  7C 08 02 A6 */	mflr r0
/* 00000048 00000088  90 01 00 04 */	stw r0, 0x4(r1)
/* 0000004C 0000008C  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 00000050 00000090  93 E1 00 24 */	stw r31, 0x24(r1)
/* 00000054 00000094  93 C1 00 20 */	stw r30, 0x20(r1)
/* 00000058 00000098  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 0000005C 0000009C  7C 7D 1B 78 */	mr r29, r3
/* 00000060 000000A0  80 63 00 28 */	lwz r3, 0x28(r3)
/* 00000064 000000A4  48 00 00 01 */	bl HSD_CObjSetCurrent
/* 00000068 000000A8  2C 03 00 00 */	cmpwi r3, 0x0
/* 0000006C 000000AC  41 82 00 AC */	beq .L_00000118
/* 00000070 000000B0  38 C0 00 00 */	li r6, un_804D6FB4@sda21
/* 00000074 000000B4  88 60 00 00 */	lbz r3, un_804D6FB4@sda21(r0)
/* 00000078 000000B8  88 86 00 01 */	lbz r4, 0x1(r6)
/* 0000007C 000000BC  88 A6 00 02 */	lbz r5, 0x2(r6)
/* 00000080 000000C0  88 C6 00 03 */	lbz r6, 0x3(r6)
/* 00000084 000000C4  48 00 00 01 */	bl HSD_SetEraseColor
/* 00000088 000000C8  80 7D 00 28 */	lwz r3, 0x28(r29)
/* 0000008C 000000CC  38 80 00 01 */	li r4, 0x1
/* 00000090 000000D0  38 A0 00 00 */	li r5, 0x0
/* 00000094 000000D4  38 C0 00 01 */	li r6, 0x1
/* 00000098 000000D8  48 00 00 01 */	bl HSD_CObjEraseScreen
/* 0000009C 000000DC  38 60 00 02 */	li r3, 0x2
/* 000000A0 000000E0  48 00 00 01 */	bl Camera_800310A0
/* 000000A4 000000E4  38 00 00 09 */	li r0, 0x9
/* 000000A8 000000E8  90 1D 00 24 */	stw r0, 0x24(r29)
/* 000000AC 000000EC  3B C0 00 00 */	li r30, 0x0
/* 000000B0 000000F0  38 7D 00 00 */	addi r3, r29, 0x0
/* 000000B4 000000F4  93 DD 00 20 */	stw r30, 0x20(r29)
/* 000000B8 000000F8  38 80 00 07 */	li r4, 0x7
/* 000000BC 000000FC  48 00 00 01 */	bl HSD_GObj_80390ED0
/* 000000C0 00000100  38 60 00 01 */	li r3, 0x1
/* 000000C4 00000104  48 00 00 01 */	bl Camera_800310A0
/* 000000C8 00000108  3B E0 00 08 */	li r31, 0x8
/* 000000CC 0000010C  93 FD 00 24 */	stw r31, 0x24(r29)
/* 000000D0 00000110  38 7D 00 00 */	addi r3, r29, 0x0
/* 000000D4 00000114  38 80 00 07 */	li r4, 0x7
/* 000000D8 00000118  93 DD 00 20 */	stw r30, 0x20(r29)
/* 000000DC 0000011C  48 00 00 01 */	bl HSD_GObj_80390ED0
/* 000000E0 00000120  38 60 00 00 */	li r3, 0x0
/* 000000E4 00000124  48 00 00 01 */	bl Camera_800310A0
/* 000000E8 00000128  93 FD 00 24 */	stw r31, 0x24(r29)
/* 000000EC 0000012C  38 7D 00 00 */	addi r3, r29, 0x0
/* 000000F0 00000130  38 80 00 07 */	li r4, 0x7
/* 000000F4 00000134  93 DD 00 20 */	stw r30, 0x20(r29)
/* 000000F8 00000138  48 00 00 01 */	bl HSD_GObj_80390ED0
/* 000000FC 0000013C  38 00 08 A1 */	li r0, 0x8a1
/* 00000100 00000140  90 1D 00 24 */	stw r0, 0x24(r29)
/* 00000104 00000144  38 7D 00 00 */	addi r3, r29, 0x0
/* 00000108 00000148  38 80 00 07 */	li r4, 0x7
/* 0000010C 0000014C  93 DD 00 20 */	stw r30, 0x20(r29)
/* 00000110 00000150  48 00 00 01 */	bl HSD_GObj_80390ED0
/* 00000114 00000154  48 00 00 01 */	bl HSD_CObjEndCurrent
.L_00000118:
/* 00000118 00000158  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 0000011C 0000015C  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 00000120 00000160  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 00000124 00000164  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 00000128 00000168  38 21 00 28 */	addi r1, r1, 0x28
/* 0000012C 0000016C  7C 08 03 A6 */	mtlr r0
/* 00000130 00000170  4E 80 00 20 */	blr
.endfn un_8031E710

.fn fn_8031E800, global
/* 00000134 00000174  7C 08 02 A6 */	mflr r0
/* 00000138 00000178  90 01 00 04 */	stw r0, 0x4(r1)
/* 0000013C 0000017C  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 00000140 00000180  DB E1 00 20 */	stfd f31, 0x20(r1)
/* 00000144 00000184  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 00000148 00000188  80 63 00 28 */	lwz r3, 0x28(r3)
/* 0000014C 0000018C  28 03 00 00 */	cmplwi r3, 0x0
/* 00000150 00000190  40 82 00 0C */	bne .L_0000015C
/* 00000154 00000194  3B E0 00 00 */	li r31, 0x0
/* 00000158 00000198  48 00 00 08 */	b .L_00000160
.L_0000015C:
/* 0000015C 0000019C  83 E3 00 10 */	lwz r31, 0x10(r3)
.L_00000160:
/* 00000160 000001A0  28 1F 00 00 */	cmplwi r31, 0x0
/* 00000164 000001A4  40 82 00 14 */	bne .L_00000178
/* 00000168 000001A8  38 60 00 00 */	li r3, un_804D5AF8@sda21
/* 0000016C 000001AC  38 80 03 6B */	li r4, 0x36b
/* 00000170 000001B0  38 A0 00 00 */	li r5, un_804D5B00@sda21
/* 00000174 000001B4  48 00 00 01 */	bl __assert
.L_00000178:
/* 00000178 000001B8  C0 20 00 00 */	lfs f1, un_804DE0A8@sda21(r0)
/* 0000017C 000001BC  28 1F 00 00 */	cmplwi r31, 0x0
/* 00000180 000001C0  C0 1F 00 2C */	lfs f0, 0x2c(r31)
/* 00000184 000001C4  EF E1 00 32 */	fmuls f31, f1, f0
/* 00000188 000001C8  40 82 00 14 */	bne .L_0000019C
/* 0000018C 000001CC  38 60 00 00 */	li r3, un_804D5AF8@sda21
/* 00000190 000001D0  38 80 03 08 */	li r4, 0x308
/* 00000194 000001D4  38 A0 00 00 */	li r5, un_804D5B00@sda21
/* 00000198 000001D8  48 00 00 01 */	bl __assert
.L_0000019C:
/* 0000019C 000001DC  D3 FF 00 2C */	stfs f31, 0x2c(r31)
/* 000001A0 000001E0  80 1F 00 14 */	lwz r0, 0x14(r31)
/* 000001A4 000001E4  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 000001A8 000001E8  40 82 00 4C */	bne .L_000001F4
/* 000001AC 000001EC  28 1F 00 00 */	cmplwi r31, 0x0
/* 000001B0 000001F0  41 82 00 44 */	beq .L_000001F4
/* 000001B4 000001F4  40 82 00 14 */	bne .L_000001C8
/* 000001B8 000001F8  38 60 00 00 */	li r3, un_804D5AF8@sda21
/* 000001BC 000001FC  38 80 02 34 */	li r4, 0x234
/* 000001C0 00000200  38 A0 00 00 */	li r5, un_804D5B00@sda21
/* 000001C4 00000204  48 00 00 01 */	bl __assert
.L_000001C8:
/* 000001C8 00000208  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 000001CC 0000020C  38 60 00 00 */	li r3, 0x0
/* 000001D0 00000210  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 000001D4 00000214  40 82 00 10 */	bne .L_000001E4
/* 000001D8 00000218  54 80 06 73 */	rlwinm. r0, r4, 0, 25, 25
/* 000001DC 0000021C  41 82 00 08 */	beq .L_000001E4
/* 000001E0 00000220  38 60 00 01 */	li r3, 0x1
.L_000001E4:
/* 000001E4 00000224  2C 03 00 00 */	cmpwi r3, 0x0
/* 000001E8 00000228  40 82 00 0C */	bne .L_000001F4
/* 000001EC 0000022C  7F E3 FB 78 */	mr r3, r31
/* 000001F0 00000230  48 00 00 01 */	bl HSD_JObjSetMtxDirtySub
.L_000001F4:
/* 000001F4 00000234  28 1F 00 00 */	cmplwi r31, 0x0
/* 000001F8 00000238  40 82 00 14 */	bne .L_0000020C
/* 000001FC 0000023C  38 60 00 00 */	li r3, un_804D5AF8@sda21
/* 00000200 00000240  38 80 03 17 */	li r4, 0x317
/* 00000204 00000244  38 A0 00 00 */	li r5, un_804D5B00@sda21
/* 00000208 00000248  48 00 00 01 */	bl __assert
.L_0000020C:
/* 0000020C 0000024C  D3 FF 00 30 */	stfs f31, 0x30(r31)
/* 00000210 00000250  80 1F 00 14 */	lwz r0, 0x14(r31)
/* 00000214 00000254  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 00000218 00000258  40 82 00 4C */	bne .L_00000264
/* 0000021C 0000025C  28 1F 00 00 */	cmplwi r31, 0x0
/* 00000220 00000260  41 82 00 44 */	beq .L_00000264
/* 00000224 00000264  40 82 00 14 */	bne .L_00000238
/* 00000228 00000268  38 60 00 00 */	li r3, un_804D5AF8@sda21
/* 0000022C 0000026C  38 80 02 34 */	li r4, 0x234
/* 00000230 00000270  38 A0 00 00 */	li r5, un_804D5B00@sda21
/* 00000234 00000274  48 00 00 01 */	bl __assert
.L_00000238:
/* 00000238 00000278  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 0000023C 0000027C  38 60 00 00 */	li r3, 0x0
/* 00000240 00000280  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 00000244 00000284  40 82 00 10 */	bne .L_00000254
/* 00000248 00000288  54 80 06 73 */	rlwinm. r0, r4, 0, 25, 25
/* 0000024C 0000028C  41 82 00 08 */	beq .L_00000254
/* 00000250 00000290  38 60 00 01 */	li r3, 0x1
.L_00000254:
/* 00000254 00000294  2C 03 00 00 */	cmpwi r3, 0x0
/* 00000258 00000298  40 82 00 0C */	bne .L_00000264
/* 0000025C 0000029C  7F E3 FB 78 */	mr r3, r31
/* 00000260 000002A0  48 00 00 01 */	bl HSD_JObjSetMtxDirtySub
.L_00000264:
/* 00000264 000002A4  28 1F 00 00 */	cmplwi r31, 0x0
/* 00000268 000002A8  40 82 00 14 */	bne .L_0000027C
/* 0000026C 000002AC  38 60 00 00 */	li r3, un_804D5AF8@sda21
/* 00000270 000002B0  38 80 03 26 */	li r4, 0x326
/* 00000274 000002B4  38 A0 00 00 */	li r5, un_804D5B00@sda21
/* 00000278 000002B8  48 00 00 01 */	bl __assert
.L_0000027C:
/* 0000027C 000002BC  D3 FF 00 34 */	stfs f31, 0x34(r31)
/* 00000280 000002C0  80 1F 00 14 */	lwz r0, 0x14(r31)
/* 00000284 000002C4  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 00000288 000002C8  40 82 00 4C */	bne .L_000002D4
/* 0000028C 000002CC  28 1F 00 00 */	cmplwi r31, 0x0
/* 00000290 000002D0  41 82 00 44 */	beq .L_000002D4
/* 00000294 000002D4  40 82 00 14 */	bne .L_000002A8
/* 00000298 000002D8  38 60 00 00 */	li r3, un_804D5AF8@sda21
/* 0000029C 000002DC  38 80 02 34 */	li r4, 0x234
/* 000002A0 000002E0  38 A0 00 00 */	li r5, un_804D5B00@sda21
/* 000002A4 000002E4  48 00 00 01 */	bl __assert
.L_000002A8:
/* 000002A8 000002E8  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 000002AC 000002EC  38 60 00 00 */	li r3, 0x0
/* 000002B0 000002F0  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 000002B4 000002F4  40 82 00 10 */	bne .L_000002C4
/* 000002B8 000002F8  54 80 06 73 */	rlwinm. r0, r4, 0, 25, 25
/* 000002BC 000002FC  41 82 00 08 */	beq .L_000002C4
/* 000002C0 00000300  38 60 00 01 */	li r3, 0x1
.L_000002C4:
/* 000002C4 00000304  2C 03 00 00 */	cmpwi r3, 0x0
/* 000002C8 00000308  40 82 00 0C */	bne .L_000002D4
/* 000002CC 0000030C  7F E3 FB 78 */	mr r3, r31
/* 000002D0 00000310  48 00 00 01 */	bl HSD_JObjSetMtxDirtySub
.L_000002D4:
/* 000002D4 00000314  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 000002D8 00000318  CB E1 00 20 */	lfd f31, 0x20(r1)
/* 000002DC 0000031C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 000002E0 00000320  38 21 00 28 */	addi r1, r1, 0x28
/* 000002E4 00000324  7C 08 03 A6 */	mtlr r0
/* 000002E8 00000328  4E 80 00 20 */	blr
.endfn fn_8031E800

.fn un_8031E9B8, global
/* 000002EC 0000032C  7C 08 02 A6 */	mflr r0
/* 000002F0 00000330  38 60 00 0E */	li r3, 0xe
/* 000002F4 00000334  90 01 00 04 */	stw r0, 0x4(r1)
/* 000002F8 00000338  38 80 00 0F */	li r4, 0xf
/* 000002FC 0000033C  38 A0 00 00 */	li r5, 0x0
/* 00000300 00000340  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 00000304 00000344  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 00000308 00000348  93 C1 00 18 */	stw r30, 0x18(r1)
/* 0000030C 0000034C  93 A1 00 14 */	stw r29, 0x14(r1)
/* 00000310 00000350  93 81 00 10 */	stw r28, 0x10(r1)
/* 00000314 00000354  48 00 00 01 */	bl GObj_Create
/* 00000318 00000358  80 80 00 00 */	lwz r4, un_804D6FB0@sda21(r0)
/* 0000031C 0000035C  7C 7D 1B 78 */	mr r29, r3
/* 00000320 00000360  80 64 00 00 */	lwz r3, 0x0(r4)
/* 00000324 00000364  80 63 00 00 */	lwz r3, 0x0(r3)
/* 00000328 00000368  80 63 00 00 */	lwz r3, 0x0(r3)
/* 0000032C 0000036C  48 00 00 01 */	bl HSD_JObjLoadJoint
/* 00000330 00000370  3B C3 00 00 */	addi r30, r3, 0x0
/* 00000334 00000374  88 80 00 00 */	lbz r4, HSD_GObj_804D7849@sda21(r0)
/* 00000338 00000378  38 7D 00 00 */	addi r3, r29, 0x0
/* 0000033C 0000037C  38 BE 00 00 */	addi r5, r30, 0x0
/* 00000340 00000380  48 00 00 01 */	bl HSD_GObjObject_80390A70
/* 00000344 00000384  3C 60 00 00 */	lis r3, HSD_GObj_80391070@ha
/* 00000348 00000388  38 83 00 00 */	addi r4, r3, HSD_GObj_80391070@l
/* 0000034C 0000038C  38 7D 00 00 */	addi r3, r29, 0x0
/* 00000350 00000390  38 A0 00 0B */	li r5, 0xb
/* 00000354 00000394  38 C0 00 00 */	li r6, 0x0
/* 00000358 00000398  48 00 00 01 */	bl GObj_SetupGXLink
/* 0000035C 0000039C  80 80 00 00 */	lwz r4, un_804D6FB0@sda21(r0)
/* 00000360 000003A0  38 7E 00 00 */	addi r3, r30, 0x0
/* 00000364 000003A4  38 A0 00 00 */	li r5, 0x0
/* 00000368 000003A8  80 84 00 00 */	lwz r4, 0x0(r4)
/* 0000036C 000003AC  80 84 00 00 */	lwz r4, 0x0(r4)
/* 00000370 000003B0  48 00 00 01 */	bl gm_8016895C
/* 00000374 000003B4  7F C3 F3 78 */	mr r3, r30
/* 00000378 000003B8  C0 20 00 00 */	lfs f1, un_804DE0AC@sda21(r0)
/* 0000037C 000003BC  48 00 00 01 */	bl HSD_JObjReqAnimAll
/* 00000380 000003C0  7F C3 F3 78 */	mr r3, r30
/* 00000384 000003C4  48 00 00 01 */	bl HSD_JObjAnimAll
/* 00000388 000003C8  3C 60 00 00 */	lis r3, un_8031E6EC@ha
/* 0000038C 000003CC  38 83 00 00 */	addi r4, r3, un_8031E6EC@l
/* 00000390 000003D0  38 7D 00 00 */	addi r3, r29, 0x0
/* 00000394 000003D4  38 A0 00 17 */	li r5, 0x17
/* 00000398 000003D8  48 00 00 01 */	bl HSD_GObjProc_8038FD54
/* 0000039C 000003DC  3B 80 00 00 */	li r28, 0x0
/* 000003A0 000003E0  3C 60 00 00 */	lis r3, fn_8031E800@ha
/* 000003A4 000003E4  57 9E 10 3A */	slwi r30, r28, 2
/* 000003A8 000003E8  3B E3 00 00 */	addi r31, r3, fn_8031E800@l
/* 000003AC 000003EC  48 00 00 6C */	b .L_00000418
.L_000003B0:
/* 000003B0 000003F0  38 1C FF FF */	subi r0, r28, 0x1
/* 000003B4 000003F4  28 00 00 02 */	cmplwi r0, 0x2
/* 000003B8 000003F8  41 81 00 58 */	bgt .L_00000410
/* 000003BC 000003FC  48 00 00 01 */	bl grCorneria_801E1BF0
/* 000003C0 00000400  80 83 00 28 */	lwz r4, 0x28(r3)
/* 000003C4 00000404  28 04 00 00 */	cmplwi r4, 0x0
/* 000003C8 00000408  40 82 00 0C */	bne .L_000003D4
/* 000003CC 0000040C  3B A0 00 00 */	li r29, 0x0
/* 000003D0 00000410  48 00 00 08 */	b .L_000003D8
.L_000003D4:
/* 000003D4 00000414  83 A4 00 10 */	lwz r29, 0x10(r4)
.L_000003D8:
/* 000003D8 00000418  38 9F 00 00 */	addi r4, r31, 0x0
/* 000003DC 0000041C  38 A0 00 02 */	li r5, 0x2
/* 000003E0 00000420  48 00 00 01 */	bl HSD_GObjProc_8038FD54
/* 000003E4 00000424  80 80 00 00 */	lwz r4, un_804D6FB0@sda21(r0)
/* 000003E8 00000428  38 7D 00 00 */	addi r3, r29, 0x0
/* 000003EC 0000042C  38 A0 00 00 */	li r5, 0x0
/* 000003F0 00000430  80 84 00 00 */	lwz r4, 0x0(r4)
/* 000003F4 00000434  7C 84 F0 2E */	lwzx r4, r4, r30
/* 000003F8 00000438  48 00 00 01 */	bl gm_8016895C
/* 000003FC 0000043C  7F A3 EB 78 */	mr r3, r29
/* 00000400 00000440  C0 20 00 00 */	lfs f1, un_804DE0AC@sda21(r0)
/* 00000404 00000444  48 00 00 01 */	bl HSD_JObjReqAnimAll
/* 00000408 00000448  7F A3 EB 78 */	mr r3, r29
/* 0000040C 0000044C  48 00 00 01 */	bl HSD_JObjAnimAll
.L_00000410:
/* 00000410 00000450  3B DE 00 04 */	addi r30, r30, 0x4
/* 00000414 00000454  3B 9C 00 01 */	addi r28, r28, 0x1
.L_00000418:
/* 00000418 00000458  80 60 00 00 */	lwz r3, un_804D6FB0@sda21(r0)
/* 0000041C 0000045C  80 63 00 00 */	lwz r3, 0x0(r3)
/* 00000420 00000460  7C 03 F0 2E */	lwzx r0, r3, r30
/* 00000424 00000464  28 00 00 00 */	cmplwi r0, 0x0
/* 00000428 00000468  40 82 FF 88 */	bne .L_000003B0
/* 0000042C 0000046C  38 60 00 18 */	li r3, 0x18
/* 00000430 00000470  48 00 00 01 */	bl lbAudioAx_80026F2C
/* 00000434 00000474  38 60 00 08 */	li r3, 0x8
/* 00000438 00000478  38 C0 00 00 */	li r6, 0x0
/* 0000043C 0000047C  38 A0 00 08 */	li r5, 0x8
/* 00000440 00000480  48 00 00 01 */	bl lbAudioAx_8002702C
/* 00000444 00000484  48 00 00 01 */	bl lbAudioAx_80027168
/* 00000448 00000488  48 00 00 01 */	bl lbAudioAx_80027648
/* 0000044C 0000048C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 00000450 00000490  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 00000454 00000494  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 00000458 00000498  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 0000045C 0000049C  83 81 00 10 */	lwz r28, 0x10(r1)
/* 00000460 000004A0  38 21 00 20 */	addi r1, r1, 0x20
/* 00000464 000004A4  7C 08 03 A6 */	mtlr r0
/* 00000468 000004A8  4E 80 00 20 */	blr
.endfn un_8031E9B8

.fn fn_8031EB38, global
/* 0000046C 000004AC  7C 08 02 A6 */	mflr r0
/* 00000470 000004B0  90 01 00 04 */	stw r0, 0x4(r1)
/* 00000474 000004B4  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 00000478 000004B8  93 E1 00 14 */	stw r31, 0x14(r1)
/* 0000047C 000004BC  83 E3 00 28 */	lwz r31, 0x28(r3)
/* 00000480 000004C0  7F E3 FB 78 */	mr r3, r31
/* 00000484 000004C4  48 00 00 01 */	bl HSD_CObjAnim
/* 00000488 000004C8  80 7F 00 84 */	lwz r3, 0x84(r31)
/* 0000048C 000004CC  C0 00 00 00 */	lfs f0, un_804DE0B0@sda21(r0)
/* 00000490 000004D0  C0 23 00 04 */	lfs f1, 0x4(r3)
/* 00000494 000004D4  FC 00 08 00 */	fcmpu cr0, f0, f1
/* 00000498 000004D8  41 82 00 1C */	beq .L_000004B4
/* 0000049C 000004DC  C0 00 00 00 */	lfs f0, un_804DE0B4@sda21(r0)
/* 000004A0 000004E0  FC 00 08 00 */	fcmpu cr0, f0, f1
/* 000004A4 000004E4  41 82 00 10 */	beq .L_000004B4
/* 000004A8 000004E8  C0 00 00 00 */	lfs f0, un_804DE0B8@sda21(r0)
/* 000004AC 000004EC  FC 00 08 00 */	fcmpu cr0, f0, f1
/* 000004B0 000004F0  40 82 00 10 */	bne .L_000004C0
.L_000004B4:
/* 000004B4 000004F4  38 60 00 23 */	li r3, 0x23
/* 000004B8 000004F8  38 80 00 00 */	li r4, 0x0
/* 000004BC 000004FC  48 00 00 01 */	bl un_8031C9B4
.L_000004C0:
/* 000004C0 00000500  80 7F 00 84 */	lwz r3, 0x84(r31)
/* 000004C4 00000504  C0 23 00 04 */	lfs f1, 0x4(r3)
/* 000004C8 00000508  C0 03 00 0C */	lfs f0, 0xc(r3)
/* 000004CC 0000050C  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 000004D0 00000510  40 82 00 0C */	bne .L_000004DC
/* 000004D4 00000514  48 00 00 01 */	bl lb_800145F4
/* 000004D8 00000518  48 00 00 01 */	bl gm_801A4B60
.L_000004DC:
/* 000004DC 0000051C  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 000004E0 00000520  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 000004E4 00000524  38 21 00 18 */	addi r1, r1, 0x18
/* 000004E8 00000528  7C 08 03 A6 */	mtlr r0
/* 000004EC 0000052C  4E 80 00 20 */	blr
.endfn fn_8031EB38

.fn un_8031EBBC, global
/* 000004F0 00000530  7C 08 02 A6 */	mflr r0
/* 000004F4 00000534  90 01 00 04 */	stw r0, 0x4(r1)
/* 000004F8 00000538  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 000004FC 0000053C  93 E1 00 14 */	stw r31, 0x14(r1)
/* 00000500 00000540  93 C1 00 10 */	stw r30, 0x10(r1)
/* 00000504 00000544  48 00 00 01 */	bl lbAudioAx_800236DC
/* 00000508 00000548  48 00 00 01 */	bl efLib_8005B4B8
/* 0000050C 0000054C  38 60 00 00 */	li r3, 0x0
/* 00000510 00000550  48 00 00 01 */	bl efAsync_8006737C
/* 00000514 00000554  38 60 00 57 */	li r3, 0x57
/* 00000518 00000558  48 00 00 01 */	bl lbAudioAx_80023F28
/* 0000051C 0000055C  38 60 00 01 */	li r3, 0x1
/* 00000520 00000560  48 00 00 01 */	bl lbAudioAx_80024E50
/* 00000524 00000564  3C 60 00 00 */	lis r3, un_80400108@ha
/* 00000528 00000568  4C C6 31 82 */	crclr cr1eq
/* 0000052C 0000056C  3C 80 00 00 */	lis r4, un_80400114@ha
/* 00000530 00000570  38 A4 00 00 */	addi r5, r4, un_80400114@l
/* 00000534 00000574  38 63 00 00 */	addi r3, r3, un_80400108@l
/* 00000538 00000578  38 80 00 00 */	li r4, un_804D6FB0@sda21
/* 0000053C 0000057C  38 C0 00 00 */	li r6, 0x0
/* 00000540 00000580  48 00 00 01 */	bl lbArchive_80016C64
/* 00000544 00000584  38 60 00 13 */	li r3, 0x13
/* 00000548 00000588  38 80 00 14 */	li r4, 0x14
/* 0000054C 0000058C  38 A0 00 00 */	li r5, 0x0
/* 00000550 00000590  48 00 00 01 */	bl GObj_Create
/* 00000554 00000594  80 80 00 00 */	lwz r4, un_804D6FB0@sda21(r0)
/* 00000558 00000598  7C 7E 1B 78 */	mr r30, r3
/* 0000055C 0000059C  80 64 00 04 */	lwz r3, 0x4(r4)
/* 00000560 000005A0  80 63 00 00 */	lwz r3, 0x0(r3)
/* 00000564 000005A4  48 00 00 01 */	bl lb_80013B14
/* 00000568 000005A8  3B E3 00 00 */	addi r31, r3, 0x0
/* 0000056C 000005AC  88 80 00 00 */	lbz r4, HSD_GObj_804D784B@sda21(r0)
/* 00000570 000005B0  38 7E 00 00 */	addi r3, r30, 0x0
/* 00000574 000005B4  38 BF 00 00 */	addi r5, r31, 0x0
/* 00000578 000005B8  48 00 00 01 */	bl HSD_GObjObject_80390A70
/* 0000057C 000005BC  3C 60 00 00 */	lis r3, un_8031E710@ha
/* 00000580 000005C0  38 83 00 00 */	addi r4, r3, un_8031E710@l
/* 00000584 000005C4  38 7E 00 00 */	addi r3, r30, 0x0
/* 00000588 000005C8  38 A0 00 02 */	li r5, 0x2
/* 0000058C 000005CC  48 00 00 01 */	bl GObj_SetupGXLinkMax
/* 00000590 000005D0  80 80 00 00 */	lwz r4, un_804D6FB0@sda21(r0)
/* 00000594 000005D4  7F E3 FB 78 */	mr r3, r31
/* 00000598 000005D8  80 84 00 04 */	lwz r4, 0x4(r4)
/* 0000059C 000005DC  80 84 00 04 */	lwz r4, 0x4(r4)
/* 000005A0 000005E0  80 84 00 00 */	lwz r4, 0x0(r4)
/* 000005A4 000005E4  48 00 00 01 */	bl HSD_CObjAddAnim
/* 000005A8 000005E8  7F E3 FB 78 */	mr r3, r31
/* 000005AC 000005EC  C0 20 00 00 */	lfs f1, un_804DE0AC@sda21(r0)
/* 000005B0 000005F0  48 00 00 01 */	bl HSD_CObjReqAnim
/* 000005B4 000005F4  7F E3 FB 78 */	mr r3, r31
/* 000005B8 000005F8  48 00 00 01 */	bl HSD_CObjAnim
/* 000005BC 000005FC  3C 60 00 00 */	lis r3, fn_8031EB38@ha
/* 000005C0 00000600  38 83 00 00 */	addi r4, r3, fn_8031EB38@l
/* 000005C4 00000604  38 7E 00 00 */	addi r3, r30, 0x0
/* 000005C8 00000608  38 A0 00 00 */	li r5, 0x0
/* 000005CC 0000060C  48 00 00 01 */	bl HSD_GObjProc_8038FD54
/* 000005D0 00000610  38 60 00 06 */	li r3, 0x6
/* 000005D4 00000614  48 00 00 01 */	bl Camera_80028B9C
/* 000005D8 00000618  48 00 00 01 */	bl lb_8000FCDC
/* 000005DC 0000061C  48 00 00 01 */	bl mpColl_80041C78
/* 000005E0 00000620  38 60 00 40 */	li r3, 0x40
/* 000005E4 00000624  48 00 00 01 */	bl Ground_801C0378
/* 000005E8 00000628  38 60 00 07 */	li r3, 0x7
/* 000005EC 0000062C  38 80 00 00 */	li r4, 0x0
/* 000005F0 00000630  48 00 00 01 */	bl Stage_802251E8
/* 000005F4 00000634  48 00 00 01 */	bl Item_80266FA8
/* 000005F8 00000638  48 00 00 01 */	bl Item_80266FCC
/* 000005FC 0000063C  48 00 00 01 */	bl Stage_8022524C
/* 00000600 00000640  38 60 00 07 */	li r3, 0x7
/* 00000604 00000644  38 80 00 00 */	li r4, 0x0
/* 00000608 00000648  48 00 00 01 */	bl Stage_8022532C
/* 0000060C 0000064C  48 00 00 01 */	bl Camera_80030758
/* 00000610 00000650  90 60 00 00 */	stw r3, un_804D6FB4@sda21(r0)
/* 00000614 00000654  48 00 00 01 */	bl un_8031E9B8
/* 00000618 00000658  38 60 00 0B */	li r3, 0xb
/* 0000061C 0000065C  38 80 00 03 */	li r4, 0x3
/* 00000620 00000660  38 A0 00 00 */	li r5, 0x0
/* 00000624 00000664  48 00 00 01 */	bl GObj_Create
/* 00000628 00000668  80 80 00 00 */	lwz r4, un_804D6FB0@sda21(r0)
/* 0000062C 0000066C  7C 7E 1B 78 */	mr r30, r3
/* 00000630 00000670  80 64 00 08 */	lwz r3, 0x8(r4)
/* 00000634 00000674  48 00 00 01 */	bl lb_80011AC4
/* 00000638 00000678  88 80 00 00 */	lbz r4, HSD_GObj_804D784A@sda21(r0)
/* 0000063C 0000067C  38 A3 00 00 */	addi r5, r3, 0x0
/* 00000640 00000680  38 7E 00 00 */	addi r3, r30, 0x0
/* 00000644 00000684  48 00 00 01 */	bl HSD_GObjObject_80390A70
/* 00000648 00000688  3C 60 00 00 */	lis r3, HSD_GObj_80391044@ha
/* 0000064C 0000068C  38 83 00 00 */	addi r4, r3, HSD_GObj_80391044@l
/* 00000650 00000690  38 7E 00 00 */	addi r3, r30, 0x0
/* 00000654 00000694  38 A0 00 00 */	li r5, 0x0
/* 00000658 00000698  38 C0 00 00 */	li r6, 0x0
/* 0000065C 0000069C  48 00 00 01 */	bl GObj_SetupGXLink
/* 00000660 000006A0  48 00 00 01 */	bl Player_InitAllPlayers
/* 00000664 000006A4  38 60 00 00 */	li r3, 0x0
/* 00000668 000006A8  48 00 00 01 */	bl lbAudioAx_80024E50
/* 0000066C 000006AC  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 00000670 000006B0  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 00000674 000006B4  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 00000678 000006B8  38 21 00 18 */	addi r1, r1, 0x18
/* 0000067C 000006BC  7C 08 03 A6 */	mtlr r0
/* 00000680 000006C0  4E 80 00 20 */	blr
.endfn un_8031EBBC

.fn un_8031ED50, global
/* 00000684 000006C4  7C 08 02 A6 */	mflr r0
/* 00000688 000006C8  90 01 00 04 */	stw r0, 0x4(r1)
/* 0000068C 000006CC  94 21 FF F8 */	stwu r1, -0x8(r1)
/* 00000690 000006D0  48 00 00 01 */	bl un_8031CAAC
/* 00000694 000006D4  80 01 00 0C */	lwz r0, 0xc(r1)
/* 00000698 000006D8  38 21 00 08 */	addi r1, r1, 0x8
/* 0000069C 000006DC  7C 08 03 A6 */	mtlr r0
/* 000006A0 000006E0  4E 80 00 20 */	blr
.endfn un_8031ED50

# 0x00000000 - 0x00000020
.data
.balign 8

.obj un_80400108, global
	.4byte 0x56693036
	.4byte 0x30312E64
	.4byte 0x61740000
.endobj un_80400108

.obj un_80400114, global
	.4byte 0x76697375
	.4byte 0x616C3036
	.4byte 0x30315363
	.4byte 0x656E6500
	.4byte 0x00000000
.endobj un_80400114

# 0x00000000 - 0x00000010
.section .sdata, "wa"
.balign 8

.obj un_804D5AF8, global
	.4byte 0x6A6F626A
	.4byte 0x2E680000
.endobj un_804D5AF8

.obj un_804D5B00, global
	.4byte 0x6A6F626A
	.4byte 0x00000000
.endobj un_804D5B00

# 0x00000000 - 0x00000018
.section .sdata2, "a"
.balign 8

.obj un_804DE0A8, global
	.4byte 0x3F266666
.endobj un_804DE0A8

.obj un_804DE0AC, global
	.4byte 0x00000000
.endobj un_804DE0AC

.obj un_804DE0B0, global
	.4byte 0x44064000
.endobj un_804DE0B0

.obj un_804DE0B4, global
	.4byte 0x440BC000
.endobj un_804DE0B4

.obj un_804DE0B8, global
	.4byte 0x44110000
.endobj un_804DE0B8

.obj gap_11_804DE0BC_sdata2, global
.hidden gap_11_804DE0BC_sdata2
	.4byte 0x00000000
.endobj gap_11_804DE0BC_sdata2
