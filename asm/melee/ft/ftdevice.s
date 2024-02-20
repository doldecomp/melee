.include "macros.inc"
.file "ftdevice.c"

# 0x800C0658 - 0x800C0874
.text
.balign 4

.fn ftCo_800C0658, global
/* 800C0658 000BD238  80 03 04 30 */	lwz r0, 0x430(r3)
/* 800C065C 000BD23C  2C 00 00 00 */	cmpwi r0, 0x0
/* 800C0660 000BD240  41 82 00 0C */	beq .L_800C066C
/* 800C0664 000BD244  38 63 04 08 */	addi r3, r3, 0x408
/* 800C0668 000BD248  4E 80 00 20 */	blr
.L_800C066C:
/* 800C066C 000BD24C  38 63 04 88 */	addi r3, r3, 0x488
/* 800C0670 000BD250  4E 80 00 20 */	blr
.endfn ftCo_800C0658

.fn ftCo_800C0674, global
/* 800C0674 000BD254  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 800C0678 000BD258  80 03 04 30 */	lwz r0, 0x430(r3)
/* 800C067C 000BD25C  2C 00 00 00 */	cmpwi r0, 0x0
/* 800C0680 000BD260  41 82 00 0C */	beq .L_800C068C
/* 800C0684 000BD264  38 63 04 08 */	addi r3, r3, 0x408
/* 800C0688 000BD268  4E 80 00 20 */	blr
.L_800C068C:
/* 800C068C 000BD26C  38 63 04 88 */	addi r3, r3, 0x488
/* 800C0690 000BD270  4E 80 00 20 */	blr
.endfn ftCo_800C0674

.fn ftCo_800C0694, global
/* 800C0694 000BD274  80 03 04 30 */	lwz r0, 0x430(r3)
/* 800C0698 000BD278  2C 00 00 00 */	cmpwi r0, 0x0
/* 800C069C 000BD27C  41 82 00 0C */	beq .L_800C06A8
/* 800C06A0 000BD280  38 63 04 08 */	addi r3, r3, 0x408
/* 800C06A4 000BD284  48 00 00 08 */	b .L_800C06AC
.L_800C06A8:
/* 800C06A8 000BD288  38 63 04 88 */	addi r3, r3, 0x488
.L_800C06AC:
/* 800C06AC 000BD28C  80 63 00 28 */	lwz r3, 0x28(r3)
/* 800C06B0 000BD290  4E 80 00 20 */	blr
.endfn ftCo_800C0694

.fn ftCo_800C06B4, global
/* 800C06B4 000BD294  80 63 05 30 */	lwz r3, 0x530(r3)
/* 800C06B8 000BD298  38 63 00 7B */	addi r3, r3, 0x7b
/* 800C06BC 000BD29C  4E 80 00 20 */	blr
.endfn ftCo_800C06B4

.fn ftCo_800C06C0, global
/* 800C06C0 000BD2A0  38 00 00 00 */	li r0, 0x0
/* 800C06C4 000BD2A4  90 0D AE D0 */	stw r0, ft_804D6570@sda21(r0)
/* 800C06C8 000BD2A8  3C 60 80 46 */	lis r3, ft_80459A68@ha
/* 800C06CC 000BD2AC  90 0D AE D4 */	stw r0, ftDevice_BuryThingCount@sda21(r0)
/* 800C06D0 000BD2B0  90 0D AE D8 */	stw r0, ft_804D6578@sda21(r0)
/* 800C06D4 000BD2B4  94 03 9A 68 */	stwu r0, ft_80459A68@l(r3)
/* 800C06D8 000BD2B8  90 03 00 0C */	stw r0, 0xc(r3)
/* 800C06DC 000BD2BC  90 03 00 18 */	stw r0, 0x18(r3)
/* 800C06E0 000BD2C0  90 03 00 24 */	stw r0, 0x24(r3)
/* 800C06E4 000BD2C4  4E 80 00 20 */	blr
.endfn ftCo_800C06C0

.fn ftCo_800C06E8, global
/* 800C06E8 000BD2C8  7C 08 02 A6 */	mflr r0
/* 800C06EC 000BD2CC  3C C0 80 46 */	lis r6, ft_80459A68@ha
/* 800C06F0 000BD2D0  90 01 00 04 */	stw r0, 0x4(r1)
/* 800C06F4 000BD2D4  38 C6 9A 68 */	addi r6, r6, ft_80459A68@l
/* 800C06F8 000BD2D8  38 E0 00 00 */	li r7, 0x0
/* 800C06FC 000BD2DC  94 21 FF F8 */	stwu r1, -0x8(r1)
/* 800C0700 000BD2E0  80 06 00 00 */	lwz r0, 0x0(r6)
/* 800C0704 000BD2E4  28 00 00 00 */	cmplwi r0, 0x0
/* 800C0708 000BD2E8  40 82 00 28 */	bne .L_800C0730
/* 800C070C 000BD2EC  1C 07 00 0C */	mulli r0, r7, 0xc
/* 800C0710 000BD2F0  7C 66 01 2E */	stwx r3, r6, r0
/* 800C0714 000BD2F4  7C 66 02 14 */	add r3, r6, r0
/* 800C0718 000BD2F8  90 83 00 04 */	stw r4, 0x4(r3)
/* 800C071C 000BD2FC  90 A3 00 08 */	stw r5, 0x8(r3)
/* 800C0720 000BD300  80 6D AE D8 */	lwz r3, ft_804D6578@sda21(r0)
/* 800C0724 000BD304  38 03 00 01 */	addi r0, r3, 0x1
/* 800C0728 000BD308  90 0D AE D8 */	stw r0, ft_804D6578@sda21(r0)
/* 800C072C 000BD30C  48 00 00 28 */	b .L_800C0754
.L_800C0730:
/* 800C0730 000BD310  3C 60 80 3C */	lis r3, ftDevice_803C6B18@ha
/* 800C0734 000BD314  4C C6 31 82 */	crclr cr1eq
/* 800C0738 000BD318  38 63 6B 18 */	addi r3, r3, ftDevice_803C6B18@l
/* 800C073C 000BD31C  48 28 4F 6D */	bl OSReport
/* 800C0740 000BD320  3C 60 80 3C */	lis r3, ftDevice_803C6B40@ha
/* 800C0744 000BD324  38 63 6B 40 */	addi r3, r3, ftDevice_803C6B40@l
/* 800C0748 000BD328  38 80 00 49 */	li r4, 0x49
/* 800C074C 000BD32C  38 AD 85 78 */	li r5, ftCo_804D3C18@sda21
/* 800C0750 000BD330  48 2C 7A D1 */	bl __assert
.L_800C0754:
/* 800C0754 000BD334  80 01 00 0C */	lwz r0, 0xc(r1)
/* 800C0758 000BD338  38 21 00 08 */	addi r1, r1, 0x8
/* 800C075C 000BD33C  7C 08 03 A6 */	mtlr r0
/* 800C0760 000BD340  4E 80 00 20 */	blr
.endfn ftCo_800C06E8

.fn ftCo_800C0764, global
/* 800C0764 000BD344  7C 08 02 A6 */	mflr r0
/* 800C0768 000BD348  3C C0 80 46 */	lis r6, ft_80459A68@ha
/* 800C076C 000BD34C  90 01 00 04 */	stw r0, 0x4(r1)
/* 800C0770 000BD350  38 00 00 02 */	li r0, 0x2
/* 800C0774 000BD354  38 C6 9A 68 */	addi r6, r6, ft_80459A68@l
/* 800C0778 000BD358  7C 09 03 A6 */	mtctr r0
/* 800C077C 000BD35C  94 21 FF F8 */	stwu r1, -0x8(r1)
/* 800C0780 000BD360  38 E6 00 0C */	addi r7, r6, 0xc
/* 800C0784 000BD364  39 00 00 00 */	li r8, 0x0
.L_800C0788:
/* 800C0788 000BD368  80 07 00 00 */	lwz r0, 0x0(r7)
/* 800C078C 000BD36C  28 00 00 00 */	cmplwi r0, 0x0
/* 800C0790 000BD370  40 82 00 28 */	bne .L_800C07B8
/* 800C0794 000BD374  1C 08 00 0C */	mulli r0, r8, 0xc
/* 800C0798 000BD378  7C C6 02 14 */	add r6, r6, r0
/* 800C079C 000BD37C  90 66 00 0C */	stw r3, 0xc(r6)
/* 800C07A0 000BD380  90 86 00 10 */	stw r4, 0x10(r6)
/* 800C07A4 000BD384  90 A6 00 14 */	stw r5, 0x14(r6)
/* 800C07A8 000BD388  80 6D AE D4 */	lwz r3, ftDevice_BuryThingCount@sda21(r0)
/* 800C07AC 000BD38C  38 03 00 01 */	addi r0, r3, 0x1
/* 800C07B0 000BD390  90 0D AE D4 */	stw r0, ftDevice_BuryThingCount@sda21(r0)
/* 800C07B4 000BD394  48 00 00 34 */	b .L_800C07E8
.L_800C07B8:
/* 800C07B8 000BD398  38 E7 00 0C */	addi r7, r7, 0xc
/* 800C07BC 000BD39C  39 08 00 01 */	addi r8, r8, 0x1
/* 800C07C0 000BD3A0  42 00 FF C8 */	bdnz .L_800C0788
/* 800C07C4 000BD3A4  3C 60 80 3C */	lis r3, ftDevice_803C6B4C@ha
/* 800C07C8 000BD3A8  4C C6 31 82 */	crclr cr1eq
/* 800C07CC 000BD3AC  38 63 6B 4C */	addi r3, r3, ftDevice_803C6B4C@l
/* 800C07D0 000BD3B0  48 28 4E D9 */	bl OSReport
/* 800C07D4 000BD3B4  3C 60 80 3C */	lis r3, ftDevice_803C6B40@ha
/* 800C07D8 000BD3B8  38 63 6B 40 */	addi r3, r3, ftDevice_803C6B40@l
/* 800C07DC 000BD3BC  38 80 00 6F */	li r4, 0x6f
/* 800C07E0 000BD3C0  38 AD 85 78 */	li r5, ftCo_804D3C18@sda21
/* 800C07E4 000BD3C4  48 2C 7A 3D */	bl __assert
.L_800C07E8:
/* 800C07E8 000BD3C8  80 01 00 0C */	lwz r0, 0xc(r1)
/* 800C07EC 000BD3CC  38 21 00 08 */	addi r1, r1, 0x8
/* 800C07F0 000BD3D0  7C 08 03 A6 */	mtlr r0
/* 800C07F4 000BD3D4  4E 80 00 20 */	blr
.endfn ftCo_800C0764

.fn ftCo_800C07F8, global
/* 800C07F8 000BD3D8  7C 08 02 A6 */	mflr r0
/* 800C07FC 000BD3DC  3C C0 80 46 */	lis r6, ft_80459A68@ha
/* 800C0800 000BD3E0  90 01 00 04 */	stw r0, 0x4(r1)
/* 800C0804 000BD3E4  38 C6 9A 68 */	addi r6, r6, ft_80459A68@l
/* 800C0808 000BD3E8  39 00 00 00 */	li r8, 0x0
/* 800C080C 000BD3EC  94 21 FF F8 */	stwu r1, -0x8(r1)
/* 800C0810 000BD3F0  80 06 00 24 */	lwz r0, 0x24(r6)
/* 800C0814 000BD3F4  28 00 00 00 */	cmplwi r0, 0x0
/* 800C0818 000BD3F8  40 82 00 28 */	bne .L_800C0840
/* 800C081C 000BD3FC  1C 08 00 0C */	mulli r0, r8, 0xc
/* 800C0820 000BD400  7C C6 02 14 */	add r6, r6, r0
/* 800C0824 000BD404  90 66 00 24 */	stw r3, 0x24(r6)
/* 800C0828 000BD408  90 86 00 28 */	stw r4, 0x28(r6)
/* 800C082C 000BD40C  90 A6 00 2C */	stw r5, 0x2c(r6)
/* 800C0830 000BD410  80 6D AE D0 */	lwz r3, ft_804D6570@sda21(r0)
/* 800C0834 000BD414  38 03 00 01 */	addi r0, r3, 0x1
/* 800C0838 000BD418  90 0D AE D0 */	stw r0, ft_804D6570@sda21(r0)
/* 800C083C 000BD41C  48 00 00 28 */	b .L_800C0864
.L_800C0840:
/* 800C0840 000BD420  3C 60 80 3C */	lis r3, ftDevice_803C6B78@ha
/* 800C0844 000BD424  4C C6 31 82 */	crclr cr1eq
/* 800C0848 000BD428  38 63 6B 78 */	addi r3, r3, ftDevice_803C6B78@l
/* 800C084C 000BD42C  48 28 4E 5D */	bl OSReport
/* 800C0850 000BD430  3C 60 80 3C */	lis r3, ftDevice_803C6B40@ha
/* 800C0854 000BD434  38 63 6B 40 */	addi r3, r3, ftDevice_803C6B40@l
/* 800C0858 000BD438  38 80 00 95 */	li r4, 0x95
/* 800C085C 000BD43C  38 AD 85 78 */	li r5, ftCo_804D3C18@sda21
/* 800C0860 000BD440  48 2C 79 C1 */	bl __assert
.L_800C0864:
/* 800C0864 000BD444  80 01 00 0C */	lwz r0, 0xc(r1)
/* 800C0868 000BD448  38 21 00 08 */	addi r1, r1, 0x8
/* 800C086C 000BD44C  7C 08 03 A6 */	mtlr r0
/* 800C0870 000BD450  4E 80 00 20 */	blr
.endfn ftCo_800C07F8

# 0x803C6B18 - 0x803C6BA0
.data
.balign 8

.obj ftDevice_803C6B18, local
	.string "fighter chk device wind func num over!\n"
.endobj ftDevice_803C6B18

.obj ftDevice_803C6B40, local
	.string "ftdevice.c\000"
.endobj ftDevice_803C6B40

.obj ftDevice_803C6B4C, local
	.string "fighter chk device catch func num over!\n\000\000\000"
.endobj ftDevice_803C6B4C

.obj ftDevice_803C6B78, local
	.string "fighter chk device coll func num over!\n"
.endobj ftDevice_803C6B78

# 0x80459A68 - 0x8045A6C0
.section .bss, "wa", @nobits
.balign 8

.obj ft_80459A68, global
	.skip 0xC
.endobj ft_80459A68

.obj ftDevice_BuryThings, global
	.skip 0x18
.endobj ftDevice_BuryThings

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

# 0x804D3C18 - 0x804D3C20
.section .sdata, "wa"
.balign 8

.obj ftCo_804D3C18, global
	.4byte 0x30000000
	.4byte 0x00000000
.endobj ftCo_804D3C18

# 0x804D6570 - 0x804D6580
.section .sbss, "wa", @nobits
.balign 8

.obj ft_804D6570, global
	.skip 0x4
.endobj ft_804D6570

.obj ftDevice_BuryThingCount, global
	.skip 0x4
.endobj ftDevice_BuryThingCount

.obj ft_804D6578, global
	.skip 0x8
.endobj ft_804D6578
