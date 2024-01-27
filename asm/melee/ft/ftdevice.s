.include "macros.inc"
.file "ftdevice.c"

# 0x00000000 - 0x0000021C
.text
.balign 4

.fn ftCo_800C0658, global
/* 00000000 00000040  80 03 04 30 */	lwz r0, 0x430(r3)
/* 00000004 00000044  2C 00 00 00 */	cmpwi r0, 0x0
/* 00000008 00000048  41 82 00 0C */	beq .L_00000014
/* 0000000C 0000004C  38 63 04 08 */	addi r3, r3, 0x408
/* 00000010 00000050  4E 80 00 20 */	blr
.L_00000014:
/* 00000014 00000054  38 63 04 88 */	addi r3, r3, 0x488
/* 00000018 00000058  4E 80 00 20 */	blr
.endfn ftCo_800C0658

.fn ftCo_800C0674, global
/* 0000001C 0000005C  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 00000020 00000060  80 03 04 30 */	lwz r0, 0x430(r3)
/* 00000024 00000064  2C 00 00 00 */	cmpwi r0, 0x0
/* 00000028 00000068  41 82 00 0C */	beq .L_00000034
/* 0000002C 0000006C  38 63 04 08 */	addi r3, r3, 0x408
/* 00000030 00000070  4E 80 00 20 */	blr
.L_00000034:
/* 00000034 00000074  38 63 04 88 */	addi r3, r3, 0x488
/* 00000038 00000078  4E 80 00 20 */	blr
.endfn ftCo_800C0674

.fn ftCo_800C0694, global
/* 0000003C 0000007C  80 03 04 30 */	lwz r0, 0x430(r3)
/* 00000040 00000080  2C 00 00 00 */	cmpwi r0, 0x0
/* 00000044 00000084  41 82 00 0C */	beq .L_00000050
/* 00000048 00000088  38 63 04 08 */	addi r3, r3, 0x408
/* 0000004C 0000008C  48 00 00 08 */	b .L_00000054
.L_00000050:
/* 00000050 00000090  38 63 04 88 */	addi r3, r3, 0x488
.L_00000054:
/* 00000054 00000094  80 63 00 28 */	lwz r3, 0x28(r3)
/* 00000058 00000098  4E 80 00 20 */	blr
.endfn ftCo_800C0694

.fn ftCo_800C06B4, global
/* 0000005C 0000009C  80 63 05 30 */	lwz r3, 0x530(r3)
/* 00000060 000000A0  38 63 00 7B */	addi r3, r3, 0x7b
/* 00000064 000000A4  4E 80 00 20 */	blr
.endfn ftCo_800C06B4

.fn ftCo_800C06C0, global
/* 00000068 000000A8  38 00 00 00 */	li r0, 0x0
/* 0000006C 000000AC  90 00 00 00 */	stw r0, ft_804D6570@sda21(r0)
/* 00000070 000000B0  3C 60 00 00 */	lis r3, ft_80459A68@ha
/* 00000074 000000B4  90 00 00 00 */	stw r0, ft_804D6574@sda21(r0)
/* 00000078 000000B8  90 00 00 00 */	stw r0, ft_804D6578@sda21(r0)
/* 0000007C 000000BC  94 03 00 00 */	stwu r0, ft_80459A68@l(r3)
/* 00000080 000000C0  90 03 00 0C */	stw r0, 0xc(r3)
/* 00000084 000000C4  90 03 00 18 */	stw r0, 0x18(r3)
/* 00000088 000000C8  90 03 00 24 */	stw r0, 0x24(r3)
/* 0000008C 000000CC  4E 80 00 20 */	blr
.endfn ftCo_800C06C0

.fn ftCo_800C06E8, global
/* 00000090 000000D0  7C 08 02 A6 */	mflr r0
/* 00000094 000000D4  3C C0 00 00 */	lis r6, ft_80459A68@ha
/* 00000098 000000D8  90 01 00 04 */	stw r0, 0x4(r1)
/* 0000009C 000000DC  38 C6 00 00 */	addi r6, r6, ft_80459A68@l
/* 000000A0 000000E0  38 E0 00 00 */	li r7, 0x0
/* 000000A4 000000E4  94 21 FF F8 */	stwu r1, -0x8(r1)
/* 000000A8 000000E8  80 06 00 00 */	lwz r0, 0x0(r6)
/* 000000AC 000000EC  28 00 00 00 */	cmplwi r0, 0x0
/* 000000B0 000000F0  40 82 00 28 */	bne .L_000000D8
/* 000000B4 000000F4  1C 07 00 0C */	mulli r0, r7, 0xc
/* 000000B8 000000F8  7C 66 01 2E */	stwx r3, r6, r0
/* 000000BC 000000FC  7C 66 02 14 */	add r3, r6, r0
/* 000000C0 00000100  90 83 00 04 */	stw r4, 0x4(r3)
/* 000000C4 00000104  90 A3 00 08 */	stw r5, 0x8(r3)
/* 000000C8 00000108  80 60 00 00 */	lwz r3, ft_804D6578@sda21(r0)
/* 000000CC 0000010C  38 03 00 01 */	addi r0, r3, 0x1
/* 000000D0 00000110  90 00 00 00 */	stw r0, ft_804D6578@sda21(r0)
/* 000000D4 00000114  48 00 00 28 */	b .L_000000FC
.L_000000D8:
/* 000000D8 00000118  3C 60 00 00 */	lis r3, ftDevice_803C6B18@ha
/* 000000DC 0000011C  4C C6 31 82 */	crclr cr1eq
/* 000000E0 00000120  38 63 00 00 */	addi r3, r3, ftDevice_803C6B18@l
/* 000000E4 00000124  48 00 00 01 */	bl OSReport
/* 000000E8 00000128  3C 60 00 00 */	lis r3, ftDevice_803C6B40@ha
/* 000000EC 0000012C  38 63 00 00 */	addi r3, r3, ftDevice_803C6B40@l
/* 000000F0 00000130  38 80 00 49 */	li r4, 0x49
/* 000000F4 00000134  38 A0 00 00 */	li r5, ftCo_804D3C18@sda21
/* 000000F8 00000138  48 00 00 01 */	bl __assert
.L_000000FC:
/* 000000FC 0000013C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 00000100 00000140  38 21 00 08 */	addi r1, r1, 0x8
/* 00000104 00000144  7C 08 03 A6 */	mtlr r0
/* 00000108 00000148  4E 80 00 20 */	blr
.endfn ftCo_800C06E8

.fn ftCo_800C0764, global
/* 0000010C 0000014C  7C 08 02 A6 */	mflr r0
/* 00000110 00000150  3C C0 00 00 */	lis r6, ft_80459A68@ha
/* 00000114 00000154  90 01 00 04 */	stw r0, 0x4(r1)
/* 00000118 00000158  38 00 00 02 */	li r0, 0x2
/* 0000011C 0000015C  38 C6 00 00 */	addi r6, r6, ft_80459A68@l
/* 00000120 00000160  7C 09 03 A6 */	mtctr r0
/* 00000124 00000164  94 21 FF F8 */	stwu r1, -0x8(r1)
/* 00000128 00000168  38 E6 00 0C */	addi r7, r6, 0xc
/* 0000012C 0000016C  39 00 00 00 */	li r8, 0x0
.L_00000130:
/* 00000130 00000170  80 07 00 00 */	lwz r0, 0x0(r7)
/* 00000134 00000174  28 00 00 00 */	cmplwi r0, 0x0
/* 00000138 00000178  40 82 00 28 */	bne .L_00000160
/* 0000013C 0000017C  1C 08 00 0C */	mulli r0, r8, 0xc
/* 00000140 00000180  7C C6 02 14 */	add r6, r6, r0
/* 00000144 00000184  90 66 00 0C */	stw r3, 0xc(r6)
/* 00000148 00000188  90 86 00 10 */	stw r4, 0x10(r6)
/* 0000014C 0000018C  90 A6 00 14 */	stw r5, 0x14(r6)
/* 00000150 00000190  80 60 00 00 */	lwz r3, ft_804D6574@sda21(r0)
/* 00000154 00000194  38 03 00 01 */	addi r0, r3, 0x1
/* 00000158 00000198  90 00 00 00 */	stw r0, ft_804D6574@sda21(r0)
/* 0000015C 0000019C  48 00 00 34 */	b .L_00000190
.L_00000160:
/* 00000160 000001A0  38 E7 00 0C */	addi r7, r7, 0xc
/* 00000164 000001A4  39 08 00 01 */	addi r8, r8, 0x1
/* 00000168 000001A8  42 00 FF C8 */	bdnz .L_00000130
/* 0000016C 000001AC  3C 60 00 00 */	lis r3, ftDevice_803C6B4C@ha
/* 00000170 000001B0  4C C6 31 82 */	crclr cr1eq
/* 00000174 000001B4  38 63 00 00 */	addi r3, r3, ftDevice_803C6B4C@l
/* 00000178 000001B8  48 00 00 01 */	bl OSReport
/* 0000017C 000001BC  3C 60 00 00 */	lis r3, ftDevice_803C6B40@ha
/* 00000180 000001C0  38 63 00 00 */	addi r3, r3, ftDevice_803C6B40@l
/* 00000184 000001C4  38 80 00 6F */	li r4, 0x6f
/* 00000188 000001C8  38 A0 00 00 */	li r5, ftCo_804D3C18@sda21
/* 0000018C 000001CC  48 00 00 01 */	bl __assert
.L_00000190:
/* 00000190 000001D0  80 01 00 0C */	lwz r0, 0xc(r1)
/* 00000194 000001D4  38 21 00 08 */	addi r1, r1, 0x8
/* 00000198 000001D8  7C 08 03 A6 */	mtlr r0
/* 0000019C 000001DC  4E 80 00 20 */	blr
.endfn ftCo_800C0764

.fn ftCo_800C07F8, global
/* 000001A0 000001E0  7C 08 02 A6 */	mflr r0
/* 000001A4 000001E4  3C C0 00 00 */	lis r6, ft_80459A68@ha
/* 000001A8 000001E8  90 01 00 04 */	stw r0, 0x4(r1)
/* 000001AC 000001EC  38 C6 00 00 */	addi r6, r6, ft_80459A68@l
/* 000001B0 000001F0  39 00 00 00 */	li r8, 0x0
/* 000001B4 000001F4  94 21 FF F8 */	stwu r1, -0x8(r1)
/* 000001B8 000001F8  80 06 00 24 */	lwz r0, 0x24(r6)
/* 000001BC 000001FC  28 00 00 00 */	cmplwi r0, 0x0
/* 000001C0 00000200  40 82 00 28 */	bne .L_000001E8
/* 000001C4 00000204  1C 08 00 0C */	mulli r0, r8, 0xc
/* 000001C8 00000208  7C C6 02 14 */	add r6, r6, r0
/* 000001CC 0000020C  90 66 00 24 */	stw r3, 0x24(r6)
/* 000001D0 00000210  90 86 00 28 */	stw r4, 0x28(r6)
/* 000001D4 00000214  90 A6 00 2C */	stw r5, 0x2c(r6)
/* 000001D8 00000218  80 60 00 00 */	lwz r3, ft_804D6570@sda21(r0)
/* 000001DC 0000021C  38 03 00 01 */	addi r0, r3, 0x1
/* 000001E0 00000220  90 00 00 00 */	stw r0, ft_804D6570@sda21(r0)
/* 000001E4 00000224  48 00 00 28 */	b .L_0000020C
.L_000001E8:
/* 000001E8 00000228  3C 60 00 00 */	lis r3, ftDevice_803C6B78@ha
/* 000001EC 0000022C  4C C6 31 82 */	crclr cr1eq
/* 000001F0 00000230  38 63 00 00 */	addi r3, r3, ftDevice_803C6B78@l
/* 000001F4 00000234  48 00 00 01 */	bl OSReport
/* 000001F8 00000238  3C 60 00 00 */	lis r3, ftDevice_803C6B40@ha
/* 000001FC 0000023C  38 63 00 00 */	addi r3, r3, ftDevice_803C6B40@l
/* 00000200 00000240  38 80 00 95 */	li r4, 0x95
/* 00000204 00000244  38 A0 00 00 */	li r5, ftCo_804D3C18@sda21
/* 00000208 00000248  48 00 00 01 */	bl __assert
.L_0000020C:
/* 0000020C 0000024C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 00000210 00000250  38 21 00 08 */	addi r1, r1, 0x8
/* 00000214 00000254  7C 08 03 A6 */	mtlr r0
/* 00000218 00000258  4E 80 00 20 */	blr
.endfn ftCo_800C07F8

# 0x00000000 - 0x00000088
.data
.balign 8

.obj ftDevice_803C6B18, global
	.4byte 0x66696768
	.4byte 0x74657220
	.4byte 0x63686B20
	.4byte 0x64657669
	.4byte 0x63652077
	.4byte 0x696E6420
	.4byte 0x66756E63
	.4byte 0x206E756D
	.4byte 0x206F7665
	.4byte 0x72210A00
.endobj ftDevice_803C6B18

.obj ftDevice_803C6B40, global
	.4byte 0x66746465
	.4byte 0x76696365
	.4byte 0x2E630000
.endobj ftDevice_803C6B40

.obj ftDevice_803C6B4C, global
	.4byte 0x66696768
	.4byte 0x74657220
	.4byte 0x63686B20
	.4byte 0x64657669
	.4byte 0x63652063
	.4byte 0x61746368
	.4byte 0x2066756E
	.4byte 0x63206E75
	.4byte 0x6D206F76
	.4byte 0x6572210A
	.4byte 0x00000000
.endobj ftDevice_803C6B4C

.obj ftDevice_803C6B78, global
	.4byte 0x66696768
	.4byte 0x74657220
	.4byte 0x63686B20
	.4byte 0x64657669
	.4byte 0x63652063
	.4byte 0x6F6C6C20
	.4byte 0x66756E63
	.4byte 0x206E756D
	.4byte 0x206F7665
	.4byte 0x72210A00
.endobj ftDevice_803C6B78

# 0x00000000 - 0x00000C58
.section .bss, "wa", @nobits
.balign 8

.obj ft_80459A68, global
	.skip 0xC
.endobj ft_80459A68

.obj ft_80459A74, global
	.skip 0x18
.endobj ft_80459A74

.obj ft_80459A8C, global
	.skip 0xC
.endobj ft_80459A8C

.obj ft_80459A98, global
	.skip 0x90
.endobj ft_80459A98

.obj ft_80459B28, global
	.skip 0x60
.endobj ft_80459B28

.obj ft_80459B88, global
	.skip 0x88
.endobj ft_80459B88

.obj ft_80459C10, global
	.skip 0x90
.endobj ft_80459C10

.obj ft_80459CA0, global
	.skip 0x78
.endobj ft_80459CA0

.obj ft_80459D18, global
	.skip 0x78
.endobj ft_80459D18

.obj ft_80459D90, global
	.skip 0x60
.endobj ft_80459D90

.obj ft_80459DF0, global
	.skip 0x78
.endobj ft_80459DF0

.obj ft_80459E68, global
	.skip 0x60
.endobj ft_80459E68

.obj ft_80459EC8, global
	.skip 0x60
.endobj ft_80459EC8

.obj ft_80459F28, global
	.skip 0x60
.endobj ft_80459F28

.obj ft_80459F88, global
	.skip 0x78
.endobj ft_80459F88

.obj ft_8045A000, global
	.skip 0x90
.endobj ft_8045A000

.obj ft_8045A090, global
	.skip 0x60
.endobj ft_8045A090

.obj ft_8045A0F0, global
	.skip 0x78
.endobj ft_8045A0F0

.obj ft_8045A168, global
	.skip 0x78
.endobj ft_8045A168

.obj ft_8045A1E0, global
	.skip 0x18
.endobj ft_8045A1E0

.obj ft_8045A1F8, global
	.skip 0x78
.endobj ft_8045A1F8

.obj ft_8045A270, global
	.skip 0x60
.endobj ft_8045A270

.obj ft_8045A2D0, global
	.skip 0x60
.endobj ft_8045A2D0

.obj ft_8045A330, global
	.skip 0x78
.endobj ft_8045A330

.obj ft_8045A3A8, global
	.skip 0x78
.endobj ft_8045A3A8

.obj ft_8045A420, global
	.skip 0x60
.endobj ft_8045A420

.obj ft_8045A480, global
	.skip 0x60
.endobj ft_8045A480

.obj ft_8045A4E0, global
	.skip 0x60
.endobj ft_8045A4E0

.obj ft_8045A540, global
	.skip 0x78
.endobj ft_8045A540

.obj ft_8045A5B8, global
	.skip 0x78
.endobj ft_8045A5B8

.obj ft_8045A630, global
	.skip 0x18
.endobj ft_8045A630

.obj ft_8045A648, global
	.skip 0x18
.endobj ft_8045A648

.obj ft_8045A660, global
	.skip 0x18
.endobj ft_8045A660

.obj ft_8045A678, global
	.skip 0x18
.endobj ft_8045A678

.obj ft_8045A690, global
	.skip 0x18
.endobj ft_8045A690

.obj ft_8045A6A8, global
	.skip 0x18
.endobj ft_8045A6A8

# 0x00000000 - 0x00000008
.section .sdata, "wa"
.balign 8

.obj ftCo_804D3C18, global
	.4byte 0x30000000
	.4byte 0x00000000
.endobj ftCo_804D3C18

# 0x00000000 - 0x00000010
.section .sbss, "wa", @nobits
.balign 8

.obj ft_804D6570, global
	.skip 0x4
.endobj ft_804D6570

.obj ft_804D6574, global
	.skip 0x4
.endobj ft_804D6574

.obj ft_804D6578, global
	.skip 0x8
.endobj ft_804D6578
