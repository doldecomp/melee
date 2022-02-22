.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240

.global func_803265A8
func_803265A8:
/* 803265A8 00323188  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 803265AC 0032318C  3C 00 7F 80 */	lis r0, 0x7f80
/* 803265B0 00323190  D0 21 00 08 */	stfs f1, 8(r1)
/* 803265B4 00323194  80 81 00 08 */	lwz r4, 8(r1)
/* 803265B8 00323198  54 83 00 50 */	rlwinm r3, r4, 0, 1, 8
/* 803265BC 0032319C  7C 03 00 00 */	cmpw r3, r0
/* 803265C0 003231A0  41 82 01 1C */	beq lbl_803266DC
/* 803265C4 003231A4  40 80 00 0C */	bge lbl_803265D0
/* 803265C8 003231A8  2C 03 00 00 */	cmpwi r3, 0
/* 803265CC 003231AC  41 82 01 38 */	beq lbl_80326704
lbl_803265D0:
/* 803265D0 003231B0  80 62 E7 D0 */	lwz r3, lbl_804DE1B0@sda21(r2)
/* 803265D4 003231B4  80 C1 00 08 */	lwz r6, 8(r1)
/* 803265D8 003231B8  90 61 00 10 */	stw r3, 0x10(r1)
/* 803265DC 003231BC  80 82 E7 D4 */	lwz r4, lbl_804DE1B4@sda21(r2)
/* 803265E0 003231C0  54 C0 04 3F */	clrlwi. r0, r6, 0x10
/* 803265E4 003231C4  54 C3 4D FE */	srwi r3, r6, 0x17
/* 803265E8 003231C8  90 81 00 14 */	stw r4, 0x14(r1)
/* 803265EC 003231CC  54 C5 02 7E */	clrlwi r5, r6, 9
/* 803265F0 003231D0  38 E3 FF 81 */	addi r7, r3, -127
/* 803265F4 003231D4  54 C8 86 7E */	rlwinm r8, r6, 0x10, 0x19, 0x1f
/* 803265F8 003231D8  41 82 00 A8 */	beq lbl_803266A0
/* 803265FC 003231DC  54 C3 02 5E */	rlwinm r3, r6, 0, 9, 0xf
/* 80326600 003231E0  64 64 3F 80 */	oris r4, r3, 0x3f80
/* 80326604 003231E4  64 A3 3F 80 */	oris r3, r5, 0x3f80
/* 80326608 003231E8  90 81 00 1C */	stw r4, 0x1c(r1)
/* 8032660C 003231EC  54 C0 04 21 */	rlwinm. r0, r6, 0, 0x10, 0x10
/* 80326610 003231F0  90 61 00 18 */	stw r3, 0x18(r1)
/* 80326614 003231F4  41 82 00 14 */	beq lbl_80326628
/* 80326618 003231F8  80 61 00 1C */	lwz r3, 0x1c(r1)
/* 8032661C 003231FC  39 08 00 01 */	addi r8, r8, 1
/* 80326620 00323200  3C 03 00 01 */	addis r0, r3, 1
/* 80326624 00323204  90 01 00 1C */	stw r0, 0x1c(r1)
lbl_80326628:
/* 80326628 00323208  3C 60 80 3C */	lis r3, lbl_803B9154@ha
/* 8032662C 0032320C  C0 41 00 18 */	lfs f2, 0x18(r1)
/* 80326630 00323210  C0 01 00 1C */	lfs f0, 0x1c(r1)
/* 80326634 00323214  55 04 10 3A */	slwi r4, r8, 2
/* 80326638 00323218  38 03 91 54 */	addi r0, r3, lbl_803B9154@l
/* 8032663C 0032321C  C0 21 00 14 */	lfs f1, 0x14(r1)
/* 80326640 00323220  7C 60 22 14 */	add r3, r0, r4
/* 80326644 00323224  6C E0 80 00 */	xoris r0, r7, 0x8000
/* 80326648 00323228  EC C2 00 28 */	fsubs f6, f2, f0
/* 8032664C 0032322C  C0 03 00 00 */	lfs f0, 0(r3)
/* 80326650 00323230  3C 60 80 3C */	lis r3, lbl_803B8F50@ha
/* 80326654 00323234  90 01 00 24 */	stw r0, 0x24(r1)
/* 80326658 00323238  3C 00 43 30 */	lis r0, 0x4330
/* 8032665C 0032323C  EC C6 00 32 */	fmuls f6, f6, f0
/* 80326660 00323240  C0 01 00 10 */	lfs f0, 0x10(r1)
/* 80326664 00323244  90 01 00 20 */	stw r0, 0x20(r1)
/* 80326668 00323248  38 03 8F 50 */	addi r0, r3, lbl_803B8F50@l
/* 8032666C 0032324C  C8 82 E7 E8 */	lfd f4, lbl_804DE1C8@sda21(r2)
/* 80326670 00323250  C8 61 00 20 */	lfd f3, 0x20(r1)
/* 80326674 00323254  7C 60 22 14 */	add r3, r0, r4
/* 80326678 00323258  EC 46 01 B2 */	fmuls f2, f6, f6
/* 8032667C 0032325C  C0 A2 E7 E0 */	lfs f5, lbl_804DE1C0@sda21(r2)
/* 80326680 00323260  EC 06 00 7A */	fmadds f0, f6, f1, f0
/* 80326684 00323264  EC 63 20 28 */	fsubs f3, f3, f4
/* 80326688 00323268  C0 23 00 00 */	lfs f1, 0(r3)
/* 8032668C 0032326C  EC 02 00 32 */	fmuls f0, f2, f0
/* 80326690 00323270  EC 25 08 FA */	fmadds f1, f5, f3, f1
/* 80326694 00323274  EC 06 00 2A */	fadds f0, f6, f0
/* 80326698 00323278  EC 21 00 2A */	fadds f1, f1, f0
/* 8032669C 0032327C  48 00 00 70 */	b lbl_8032670C
lbl_803266A0:
/* 803266A0 00323280  6C E0 80 00 */	xoris r0, r7, 0x8000
/* 803266A4 00323284  C8 22 E7 E8 */	lfd f1, lbl_804DE1C8@sda21(r2)
/* 803266A8 00323288  90 01 00 24 */	stw r0, 0x24(r1)
/* 803266AC 0032328C  3C 00 43 30 */	lis r0, 0x4330
/* 803266B0 00323290  3C 60 80 3C */	lis r3, lbl_803B8F50@ha
/* 803266B4 00323294  C0 42 E7 E0 */	lfs f2, lbl_804DE1C0@sda21(r2)
/* 803266B8 00323298  90 01 00 20 */	stw r0, 0x20(r1)
/* 803266BC 0032329C  55 04 10 3A */	slwi r4, r8, 2
/* 803266C0 003232A0  C8 01 00 20 */	lfd f0, 0x20(r1)
/* 803266C4 003232A4  38 03 8F 50 */	addi r0, r3, lbl_803B8F50@l
/* 803266C8 003232A8  7C 60 22 14 */	add r3, r0, r4
/* 803266CC 003232AC  EC 20 08 28 */	fsubs f1, f0, f1
/* 803266D0 003232B0  C0 03 00 00 */	lfs f0, 0(r3)
/* 803266D4 003232B4  EC 22 00 7A */	fmadds f1, f2, f1, f0
/* 803266D8 003232B8  48 00 00 34 */	b lbl_8032670C
lbl_803266DC:
/* 803266DC 003232BC  54 80 02 7F */	clrlwi. r0, r4, 9
/* 803266E0 003232C0  41 82 00 0C */	beq lbl_803266EC
/* 803266E4 003232C4  C0 21 00 08 */	lfs f1, 8(r1)
/* 803266E8 003232C8  48 00 00 24 */	b lbl_8032670C
lbl_803266EC:
/* 803266EC 003232CC  54 80 00 01 */	rlwinm. r0, r4, 0, 0, 0
/* 803266F0 003232D0  41 82 00 0C */	beq lbl_803266FC
/* 803266F4 003232D4  C0 22 E7 D8 */	lfs f1, lbl_804DE1B8@sda21(r2)
/* 803266F8 003232D8  48 00 00 14 */	b lbl_8032670C
lbl_803266FC:
/* 803266FC 003232DC  C0 22 E7 DC */	lfs f1, lbl_804DE1BC@sda21(r2)
/* 80326700 003232E0  48 00 00 0C */	b lbl_8032670C
lbl_80326704:
/* 80326704 003232E4  C0 02 E7 DC */	lfs f0, lbl_804DE1BC@sda21(r2)
/* 80326708 003232E8  FC 20 00 50 */	fneg f1, f0
lbl_8032670C:
/* 8032670C 003232EC  38 21 00 28 */	addi r1, r1, 0x28
/* 80326710 003232F0  4E 80 00 20 */	blr 


.section .rodata, "a"
    .balign 8
.global lbl_803B8F50
lbl_803B8F50:
    .4byte 0x00000000
    .4byte 0x3BFF0153
    .4byte 0x3C7E0545
    .4byte 0x3CBDC8D8
    .4byte 0x3CFC14D8
    .4byte 0x3D1CF43E
    .4byte 0x3D3BA2C8
    .4byte 0x3D5A16EC
    .4byte 0x3D785186
    .4byte 0x3D8B29B7
    .4byte 0x3D9A0EBD
    .4byte 0x3DA8D83A
    .4byte 0x3DB78694
    .4byte 0x3DC61A2F
    .4byte 0x3DD4936A
    .4byte 0x3DE2F2A4
    .4byte 0x3DF1383B
    .4byte 0x3DFF648A
    .4byte 0x3E06BBF4
    .4byte 0x3E0DB957
    .4byte 0x3E14AA98
    .4byte 0x3E1B8FE1
    .4byte 0x3E22695B
    .4byte 0x3E29372F
    .4byte 0x3E2FF984
    .4byte 0x3E36B07F
    .4byte 0x3E3D5C48
    .4byte 0x3E43FD03
    .4byte 0x3E4A92D5
    .4byte 0x3E511DE1
    .4byte 0x3E579E4A
    .4byte 0x3E5E1434
    .4byte 0x3E647FBE
    .4byte 0x3E6AE10B
    .4byte 0x3E71383B
    .4byte 0x3E77856E
    .4byte 0x3E7DC8C3
    .4byte 0x3E82012D
    .4byte 0x3E851927
    .4byte 0x3E882C60
    .4byte 0x3E8B3AE5
    .4byte 0x3E8E44C6
    .4byte 0x3E914A10
    .4byte 0x3E944AD1
    .4byte 0x3E974716
    .4byte 0x3E9A3EED
    .4byte 0x3E9D3263
    .4byte 0x3EA02184
    .4byte 0x3EA30C5E
    .4byte 0x3EA5F2FD
    .4byte 0x3EA8D56C
    .4byte 0x3EABB3B9
    .4byte 0x3EAE8DEE
    .4byte 0x3EB16418
    .4byte 0x3EB43641
    .4byte 0x3EB70475
    .4byte 0x3EB9CEC0
    .4byte 0x3EBC952B
    .4byte 0x3EBF57C2
    .4byte 0x3EC2168F
    .4byte 0x3EC4D19C
    .4byte 0x3EC788F4
    .4byte 0x3ECA3CA1
    .4byte 0x3ECCECAC
    .4byte 0x3ECF991F
    .4byte 0x3ED24205
    .4byte 0x3ED4E765
    .4byte 0x3ED7894A
    .4byte 0x3EDA27BC
    .4byte 0x3EDCC2C5
    .4byte 0x3EDF5A6D
    .4byte 0x3EE1EEBD
    .4byte 0x3EE47FBE
    .4byte 0x3EE70D78
    .4byte 0x3EE997F4
    .4byte 0x3EEC1F39
    .4byte 0x3EEEA350
    .4byte 0x3EF12441
    .4byte 0x3EF3A213
    .4byte 0x3EF61CCF
    .4byte 0x3EF8947B
    .4byte 0x3EFB0920
    .4byte 0x3EFD7AC4
    .4byte 0x3EFFE970
    .4byte 0x3F012A95
    .4byte 0x3F025EFD
    .4byte 0x3F0391F3
    .4byte 0x3F04C37A
    .4byte 0x3F05F397
    .4byte 0x3F07224C
    .4byte 0x3F084F9D
    .4byte 0x3F097B8D
    .4byte 0x3F0AA61F
    .4byte 0x3F0BCF56
    .4byte 0x3F0CF736
    .4byte 0x3F0E1DC1
    .4byte 0x3F0F42FB
    .4byte 0x3F1066E7
    .4byte 0x3F118987
    .4byte 0x3F12AADE
    .4byte 0x3F13CAF1
    .4byte 0x3F14E9C0
    .4byte 0x3F16074F
    .4byte 0x3F1723A2
    .4byte 0x3F183EBA
    .4byte 0x3F19589A
    .4byte 0x3F1A7145
    .4byte 0x3F1B88BE
    .4byte 0x3F1C9F07
    .4byte 0x3F1DB422
    .4byte 0x3F1EC813
    .4byte 0x3F1FDADC
    .4byte 0x3F20EC7F
    .4byte 0x3F21FCFF
    .4byte 0x3F230C5E
    .4byte 0x3F241A9F
    .4byte 0x3F2527C3
    .4byte 0x3F2633CE
    .4byte 0x3F273EC1
    .4byte 0x3F28489E
    .4byte 0x3F295169
    .4byte 0x3F2A5923
    .4byte 0x3F2B5FCF
    .4byte 0x3F2C656E
    .4byte 0x3F2D6A02
    .4byte 0x3F2E6D8F
    .4byte 0x3F2F7015
    .4byte 0x3F307198
    .4byte 0x3F317218
.global lbl_803B9154
lbl_803B9154:
    .4byte 0x3F800000
    .4byte 0x3F7E03F8
    .4byte 0x3F7C0FC1
    .4byte 0x3F7A232D
    .4byte 0x3F783E10
    .4byte 0x3F76603E
    .4byte 0x3F74898D
    .4byte 0x3F72B9D6
    .4byte 0x3F70F0F1
    .4byte 0x3F6F2EB7
    .4byte 0x3F6D7304
    .4byte 0x3F6BBDB3
    .4byte 0x3F6A0EA1
    .4byte 0x3F6865AC
    .4byte 0x3F66C2B4
    .4byte 0x3F652598
    .4byte 0x3F638E39
    .4byte 0x3F61FC78
    .4byte 0x3F607038
    .4byte 0x3F5EE95C
    .4byte 0x3F5D67C9
    .4byte 0x3F5BEB62
    .4byte 0x3F5A740E
    .4byte 0x3F5901B2
    .4byte 0x3F579436
    .4byte 0x3F562B81
    .4byte 0x3F54C77B
    .4byte 0x3F53680D
    .4byte 0x3F520D21
    .4byte 0x3F50B6A0
    .4byte 0x3F4F6475
    .4byte 0x3F4E168A
    .4byte 0x3F4CCCCD
    .4byte 0x3F4B8728
    .4byte 0x3F4A4588
    .4byte 0x3F4907DA
    .4byte 0x3F47CE0C
    .4byte 0x3F46980C
    .4byte 0x3F4565C8
    .4byte 0x3F443730
    .4byte 0x3F430C31
    .4byte 0x3F41E4BC
    .4byte 0x3F40C0C1
    .4byte 0x3F3FA030
    .4byte 0x3F3E82FA
    .4byte 0x3F3D6910
    .4byte 0x3F3C5264
    .4byte 0x3F3B3EE7
    .4byte 0x3F3A2E8C
    .4byte 0x3F392144
    .4byte 0x3F381703
    .4byte 0x3F370FBB
    .4byte 0x3F360B61
    .4byte 0x3F3509E7
    .4byte 0x3F340B41
    .4byte 0x3F330F63
    .4byte 0x3F321643
    .4byte 0x3F311FD4
    .4byte 0x3F302C0B
    .4byte 0x3F2F3ADE
    .4byte 0x3F2E4C41
    .4byte 0x3F2D602B
    .4byte 0x3F2C7692
    .4byte 0x3F2B8F6A
    .4byte 0x3F2AAAAB
    .4byte 0x3F29C84A
    .4byte 0x3F28E83F
    .4byte 0x3F280A81
    .4byte 0x3F272F05
    .4byte 0x3F2655C4
    .4byte 0x3F257EB5
    .4byte 0x3F24A9CF
    .4byte 0x3F23D70A
    .4byte 0x3F23065E
    .4byte 0x3F2237C3
    .4byte 0x3F216B31
    .4byte 0x3F20A0A1
    .4byte 0x3F1FD80A
    .4byte 0x3F1F1166
    .4byte 0x3F1E4CAD
    .4byte 0x3F1D89D9
    .4byte 0x3F1CC8E1
    .4byte 0x3F1C09C1
    .4byte 0x3F1B4C70
    .4byte 0x3F1A90E8
    .4byte 0x3F19D723
    .4byte 0x3F191F1A
    .4byte 0x3F1868C8
    .4byte 0x3F17B426
    .4byte 0x3F17012E
    .4byte 0x3F164FDA
    .4byte 0x3F15A025
    .4byte 0x3F14F209
    .4byte 0x3F144581
    .4byte 0x3F139A86
    .4byte 0x3F12F114
    .4byte 0x3F124925
    .4byte 0x3F11A2B4
    .4byte 0x3F10FDBC
    .4byte 0x3F105A38
    .4byte 0x3F0FB824
    .4byte 0x3F0F177A
    .4byte 0x3F0E7835
    .4byte 0x3F0DDA52
    .4byte 0x3F0D3DCB
    .4byte 0x3F0CA29C
    .4byte 0x3F0C08C1
    .4byte 0x3F0B7034
    .4byte 0x3F0AD8F3
    .4byte 0x3F0A42F8
    .4byte 0x3F09AE41
    .4byte 0x3F091AC7
    .4byte 0x3F088889
    .4byte 0x3F07F781
    .4byte 0x3F0767AB
    .4byte 0x3F06D905
    .4byte 0x3F064B8A
    .4byte 0x3F05BF37
    .4byte 0x3F053408
    .4byte 0x3F04A9FA
    .4byte 0x3F042108
    .4byte 0x3F039930
    .4byte 0x3F03126F
    .4byte 0x3F028CC0
    .4byte 0x3F020821
    .4byte 0x3F01848E
    .4byte 0x3F010204
    .4byte 0x3F008080
    .4byte 0x3F000000
.global __sincos_on_quadrant
__sincos_on_quadrant:
    .4byte 0x00000000
    .4byte 0x3F800000
    .4byte 0x3F800000
    .4byte 0x00000000
    .4byte 0x00000000
    .4byte 0xBF800000
    .4byte 0xBF800000
    .4byte 0x00000000
.global __sincos_poly
__sincos_poly:
    .4byte 0x366CCFAA
    .4byte 0x34A5E129
    .4byte 0xB9AAE275
    .4byte 0xB8196543
    .4byte 0x3C81E0ED
    .4byte 0x3B2335DD
    .4byte 0xBE9DE9E6
    .4byte 0xBDA55DE7
    .4byte 0x3F800000
    .4byte 0x3F490FDB

.section .sdata2, "a"
    .balign 8
.global lbl_804DE1B0
lbl_804DE1B0:
	.4byte 0xBF000030
.global lbl_804DE1B4
lbl_804DE1B4:
	.4byte 0x3EAAAA36
.global lbl_804DE1B8
lbl_804DE1B8:
	.4byte 0x7FFFFFFF
.global lbl_804DE1BC
lbl_804DE1BC:
	.4byte 0x7F800000
.global lbl_804DE1C0
lbl_804DE1C0:
	.4byte 0x3F317218
	.4byte 0x00000000
.global lbl_804DE1C8
lbl_804DE1C8:
	.4byte 0x43300000
	.4byte 0x80000000
