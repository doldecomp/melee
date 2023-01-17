#include <dolphin/gx/GXPixel.h>

#include <common_structs.h>
#include <dolphin/gx/__GXBump.h>
#include <dolphin/gx/__GXInit.h>
#include <placeholder.h>

#ifdef MWERKS_GEKKO

s32 lbl_80401508[] = { 0, 1, 2, 3, 4, 4, 4, 5 };

f32 const lbl_804DE298 = 0.0F;
f32 const lbl_804DE29C = 0.5F;
f64 const lbl_804DE2A0 = 1.0L;
Vec2 const lbl_804DE2A8 = { 2.0F, 0.0F };
f64 const lbl_804DE2B0 = 0.5L;
Vec2 const lbl_804DE2B8 = { 8388638.0F, 0.0F };
f64 const lbl_804DE2C0 = 4503601774854144.0L;
f64 const lbl_804DE2C8 = 0.0L;
Vec2 const lbl_804DE2D0 = { 1.0F, 0.0F };
f64 const lbl_804DE2D8 = 3.0L;
Vec2 const lbl_804DE2E0 = { 256.0F, 0.0F };
f64 const lbl_804DE2E8 = 4503599627370496.0L;

unk_t __cvt_fp2unsigned();

#pragma push
asm void GXSetFog(s32, GXColor, f32, f32, f32, f32)
{ // clang-format off
    nofralloc
/* 803407C4 0033D3A4  7C 08 02 A6 */	mflr r0
/* 803407C8 0033D3A8  FC 04 18 00 */	fcmpu cr0, f4, f3
/* 803407CC 0033D3AC  90 01 00 04 */	stw r0, 4(r1)
/* 803407D0 0033D3B0  94 21 FF B8 */	stwu r1, -0x48(r1)
/* 803407D4 0033D3B4  93 E1 00 44 */	stw r31, 0x44(r1)
/* 803407D8 0033D3B8  3B E3 00 00 */	addi r31, r3, 0
/* 803407DC 0033D3BC  93 C1 00 40 */	stw r30, 0x40(r1)
/* 803407E0 0033D3C0  93 A1 00 3C */	stw r29, 0x3c(r1)
/* 803407E4 0033D3C4  3B A4 00 00 */	addi r29, r4, 0
/* 803407E8 0033D3C8  41 82 00 0C */	beq lbl_803407F4
/* 803407EC 0033D3CC  FC 02 08 00 */	fcmpu cr0, f2, f1
/* 803407F0 0033D3D0  40 82 00 14 */	bne lbl_80340804
lbl_803407F4:
/* 803407F4 0033D3D4  C0 62 E8 B8 */	lfs f3, lbl_804DE298(r2)
/* 803407F8 0033D3D8  C0 82 E8 BC */	lfs f4, lbl_804DE29C(r2)
/* 803407FC 0033D3DC  FC A0 18 90 */	fmr f5, f3
/* 80340800 0033D3E0  48 00 00 20 */	b lbl_80340820
lbl_80340804:
/* 80340804 0033D3E4  EC 04 18 28 */	fsubs f0, f4, f3
/* 80340808 0033D3E8  EC A2 08 28 */	fsubs f5, f2, f1
/* 8034080C 0033D3EC  EC 44 00 F2 */	fmuls f2, f4, f3
/* 80340810 0033D3F0  EC 84 00 24 */	fdivs f4, f4, f0
/* 80340814 0033D3F4  EC 00 01 72 */	fmuls f0, f0, f5
/* 80340818 0033D3F8  EC A1 28 24 */	fdivs f5, f1, f5
/* 8034081C 0033D3FC  EC 62 00 24 */	fdivs f3, f2, f0
lbl_80340820:
/* 80340820 0033D400  C0 22 E8 BC */	lfs f1, lbl_804DE29C(r2)
/* 80340824 0033D404  38 60 00 00 */	li r3, 0
/* 80340828 0033D408  C8 02 E8 C0 */	lfd f0, lbl_804DE2A0(r2)
/* 8034082C 0033D40C  48 00 00 0C */	b lbl_80340838
lbl_80340830:
/* 80340830 0033D410  EC 84 00 72 */	fmuls f4, f4, f1
/* 80340834 0033D414  38 63 00 01 */	addi r3, r3, 1
lbl_80340838:
/* 80340838 0033D418  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 8034083C 0033D41C  41 81 FF F4 */	bgt lbl_80340830
/* 80340840 0033D420  C8 02 E8 D0 */	lfd f0, lbl_804DE2B0(r2)
/* 80340844 0033D424  C0 42 E8 C8 */	lfs f2, lbl_804DE2A8(r2)
/* 80340848 0033D428  C0 22 E8 B8 */	lfs f1, lbl_804DE298(r2)
/* 8034084C 0033D42C  48 00 00 0C */	b lbl_80340858
lbl_80340850:
/* 80340850 0033D430  EC 84 00 B2 */	fmuls f4, f4, f2
/* 80340854 0033D434  38 63 FF FF */	addi r3, r3, -1
lbl_80340858:
/* 80340858 0033D438  FC 04 08 40 */	fcmpo cr0, f4, f1
/* 8034085C 0033D43C  40 81 00 0C */	ble lbl_80340868
/* 80340860 0033D440  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 80340864 0033D444  41 80 FF EC */	blt lbl_80340850
lbl_80340868:
/* 80340868 0033D448  3B C3 00 01 */	addi r30, r3, 1
/* 8034086C 0033D44C  C0 02 E8 D8 */	lfs f0, lbl_804DE2B8(r2)
/* 80340870 0033D450  38 00 00 01 */	li r0, 1
/* 80340874 0033D454  C8 42 E8 E0 */	lfd f2, lbl_804DE2C0(r2)
/* 80340878 0033D458  7C 00 F0 30 */	slw r0, r0, r30
/* 8034087C 0033D45C  EC 20 01 32 */	fmuls f1, f0, f4
/* 80340880 0033D460  6C 03 80 00 */	xoris r3, r0, 0x8000
/* 80340884 0033D464  D0 A1 00 28 */	stfs f5, 0x28(r1)
/* 80340888 0033D468  3C 00 43 30 */	lis r0, 0x4330
/* 8034088C 0033D46C  90 61 00 34 */	stw r3, 0x34(r1)
/* 80340890 0033D470  90 01 00 30 */	stw r0, 0x30(r1)
/* 80340894 0033D474  C8 01 00 30 */	lfd f0, 0x30(r1)
/* 80340898 0033D478  EC 00 10 28 */	fsubs f0, f0, f2
/* 8034089C 0033D47C  EC 03 00 24 */	fdivs f0, f3, f0
/* 803408A0 0033D480  D0 01 00 2C */	stfs f0, 0x2c(r1)
/* 803408A4 0033D484  4B FE 20 1D */	bl __cvt_fp2unsigned
/* 803408A8 0033D488  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 803408AC 0033D48C  54 69 02 3E */	clrlwi r9, r3, 8
/* 803408B0 0033D490  88 DD 00 01 */	lbz r6, 1(r29)
/* 803408B4 0033D494  57 C8 02 3E */	clrlwi r8, r30, 8
/* 803408B8 0033D498  54 04 A3 68 */	rlwinm r4, r0, 0x14, 0xd, 0x14
/* 803408BC 0033D49C  50 04 A5 7E */	rlwimi r4, r0, 0x14, 0x15, 0x1f
/* 803408C0 0033D4A0  89 7D 00 02 */	lbz r11, 2(r29)
/* 803408C4 0033D4A4  54 00 A3 18 */	rlwinm r0, r0, 0x14, 0xc, 0xc
/* 803408C8 0033D4A8  88 BD 00 00 */	lbz r5, 0(r29)
/* 803408CC 0033D4AC  50 80 03 7E */	rlwimi r0, r4, 0, 0xd, 0x1f
/* 803408D0 0033D4B0  81 81 00 28 */	lwz r12, 0x28(r1)
/* 803408D4 0033D4B4  54 07 02 3E */	clrlwi r7, r0, 8
/* 803408D8 0033D4B8  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 803408DC 0033D4BC  64 EA EE 00 */	oris r10, r7, 0xee00
/* 803408E0 0033D4C0  38 00 00 61 */	li r0, 0x61
/* 803408E4 0033D4C4  3C 80 CC 01 */	lis r4, 0xCC008000@ha
/* 803408E8 0033D4C8  98 04 80 00 */	stb r0, 0xCC008000@l(r4)
/* 803408EC 0033D4CC  65 27 EF 00 */	oris r7, r9, 0xef00
/* 803408F0 0033D4D0  54 C6 40 2E */	slwi r6, r6, 8
/* 803408F4 0033D4D4  91 44 80 00 */	stw r10, -0x8000(r4)
/* 803408F8 0033D4D8  55 8A A3 68 */	rlwinm r10, r12, 0x14, 0xd, 0x14
/* 803408FC 0033D4DC  51 8A A5 7E */	rlwimi r10, r12, 0x14, 0x15, 0x1f
/* 80340900 0033D4E0  98 04 80 00 */	stb r0, -0x8000(r4)
/* 80340904 0033D4E4  55 89 A3 18 */	rlwinm r9, r12, 0x14, 0xc, 0xc
/* 80340908 0033D4E8  51 49 03 7E */	rlwimi r9, r10, 0, 0xd, 0x1f
/* 8034090C 0033D4EC  90 E4 80 00 */	stw r7, -0x8000(r4)
/* 80340910 0033D4F0  65 07 F0 00 */	oris r7, r8, 0xf000
/* 80340914 0033D4F4  51 66 06 3E */	rlwimi r6, r11, 0, 0x18, 0x1f
/* 80340918 0033D4F8  98 04 80 00 */	stb r0, -0x8000(r4)
/* 8034091C 0033D4FC  90 E4 80 00 */	stw r7, -0x8000(r4)
/* 80340920 0033D500  57 E7 A8 14 */	slwi r7, r31, 0x15
/* 80340924 0033D504  51 27 03 3E */	rlwimi r7, r9, 0, 0xc, 0x1f
/* 80340928 0033D508  54 E7 02 3E */	clrlwi r7, r7, 8
/* 8034092C 0033D50C  98 04 80 00 */	stb r0, -0x8000(r4)
/* 80340930 0033D510  64 E7 F1 00 */	oris r7, r7, 0xf100
/* 80340934 0033D514  90 E4 80 00 */	stw r7, -0x8000(r4)
/* 80340938 0033D518  98 04 80 00 */	stb r0, -0x8000(r4)
/* 8034093C 0033D51C  54 A0 80 1E */	slwi r0, r5, 0x10
/* 80340940 0033D520  50 C0 04 3E */	rlwimi r0, r6, 0, 0x10, 0x1f
/* 80340944 0033D524  54 00 02 3E */	clrlwi r0, r0, 8
/* 80340948 0033D528  64 00 F2 00 */	oris r0, r0, 0xf200
/* 8034094C 0033D52C  90 04 80 00 */	stw r0, -0x8000(r4)
/* 80340950 0033D530  38 00 00 00 */	li r0, 0
/* 80340954 0033D534  B0 03 00 02 */	sth r0, 2(r3)
/* 80340958 0033D538  80 01 00 4C */	lwz r0, 0x4c(r1)
/* 8034095C 0033D53C  83 E1 00 44 */	lwz r31, 0x44(r1)
/* 80340960 0033D540  83 C1 00 40 */	lwz r30, 0x40(r1)
/* 80340964 0033D544  7C 08 03 A6 */	mtlr r0
/* 80340968 0033D548  83 A1 00 3C */	lwz r29, 0x3c(r1)
/* 8034096C 0033D54C  38 21 00 48 */	addi r1, r1, 0x48
/* 80340970 0033D550  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#else

void GXSetFog(s32 arg0, GXColor arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5)
{
    NOT_IMPLEMENTED;
}

#endif

#ifdef MWERKS_GEKKO

#pragma push
asm void GXInitFogAdjTable(GXFogAdjTbl* arg0, u16 arg1, Mtx44 arg2)
{ // clang-format off
    nofralloc
/* 80340974 0033D554  7C 08 02 A6 */	mflr r0
/* 80340978 0033D558  90 01 00 04 */	stw r0, 4(r1)
/* 8034097C 0033D55C  94 21 FF 80 */	stwu r1, -0x80(r1)
/* 80340980 0033D560  DB E1 00 78 */	stfd f31, 0x78(r1)
/* 80340984 0033D564  DB C1 00 70 */	stfd f30, 0x70(r1)
/* 80340988 0033D568  DB A1 00 68 */	stfd f29, 0x68(r1)
/* 8034098C 0033D56C  DB 81 00 60 */	stfd f28, 0x60(r1)
/* 80340990 0033D570  DB 61 00 58 */	stfd f27, 0x58(r1)
/* 80340994 0033D574  DB 41 00 50 */	stfd f26, 0x50(r1)
/* 80340998 0033D578  DB 21 00 48 */	stfd f25, 0x48(r1)
/* 8034099C 0033D57C  DB 01 00 40 */	stfd f24, 0x40(r1)
/* 803409A0 0033D580  DA E1 00 38 */	stfd f23, 0x38(r1)
/* 803409A4 0033D584  93 E1 00 34 */	stw r31, 0x34(r1)
/* 803409A8 0033D588  93 C1 00 30 */	stw r30, 0x30(r1)
/* 803409AC 0033D58C  93 A1 00 2C */	stw r29, 0x2c(r1)
/* 803409B0 0033D590  C8 22 E8 E8 */	lfd f1, lbl_804DE2C8(r2)
/* 803409B4 0033D594  C0 05 00 3C */	lfs f0, 0x3c(r5)
/* 803409B8 0033D598  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 803409BC 0033D59C  40 82 00 30 */	bne lbl_803409EC
/* 803409C0 0033D5A0  C0 45 00 28 */	lfs f2, 0x28(r5)
/* 803409C4 0033D5A4  C0 22 E8 F0 */	lfs f1, lbl_804DE2D0(r2)
/* 803409C8 0033D5A8  C0 65 00 2C */	lfs f3, 0x2c(r5)
/* 803409CC 0033D5AC  EC 42 08 28 */	fsubs f2, f2, f1
/* 803409D0 0033D5B0  C0 05 00 08 */	lfs f0, 8(r5)
/* 803409D4 0033D5B4  EC 21 00 2A */	fadds f1, f1, f0
/* 803409D8 0033D5B8  C0 05 00 00 */	lfs f0, 0(r5)
/* 803409DC 0033D5BC  EC 43 10 24 */	fdivs f2, f3, f2
/* 803409E0 0033D5C0  EC 22 00 72 */	fmuls f1, f2, f1
/* 803409E4 0033D5C4  EF 01 00 24 */	fdivs f24, f1, f0
/* 803409E8 0033D5C8  48 00 00 2C */	b lbl_80340A14
lbl_803409EC:
/* 803409EC 0033D5CC  C0 82 E8 F0 */	lfs f4, lbl_804DE2D0(r2)
/* 803409F0 0033D5D0  C0 05 00 0C */	lfs f0, 0xc(r5)
/* 803409F4 0033D5D4  C0 65 00 2C */	lfs f3, 0x2c(r5)
/* 803409F8 0033D5D8  EC 20 20 28 */	fsubs f1, f0, f4
/* 803409FC 0033D5DC  C0 45 00 28 */	lfs f2, 0x28(r5)
/* 80340A00 0033D5E0  EC 64 18 2A */	fadds f3, f4, f3
/* 80340A04 0033D5E4  C0 05 00 00 */	lfs f0, 0(r5)
/* 80340A08 0033D5E8  FC 20 08 50 */	fneg f1, f1
/* 80340A0C 0033D5EC  EC 43 10 24 */	fdivs f2, f3, f2
/* 80340A10 0033D5F0  EF 01 00 24 */	fdivs f24, f1, f0
lbl_80340A14:
/* 80340A14 0033D5F4  54 80 04 3E */	clrlwi r0, r4, 0x10
/* 80340A18 0033D5F8  CB 62 E9 08 */	lfd f27, lbl_804DE2E8(r2)
/* 80340A1C 0033D5FC  90 01 00 24 */	stw r0, 0x24(r1)
/* 80340A20 0033D600  3F E0 43 30 */	lis r31, 0x4330
/* 80340A24 0033D604  C0 22 E8 C8 */	lfs f1, lbl_804DE2A8(r2)
/* 80340A28 0033D608  EF 42 00 B2 */	fmuls f26, f2, f2
/* 80340A2C 0033D60C  93 E1 00 20 */	stw r31, 0x20(r1)
/* 80340A30 0033D610  C3 82 E8 F0 */	lfs f28, lbl_804DE2D0(r2)
/* 80340A34 0033D614  7C 7E 1B 78 */	mr r30, r3
/* 80340A38 0033D618  C8 01 00 20 */	lfd f0, 0x20(r1)
/* 80340A3C 0033D61C  C3 A2 E8 B8 */	lfs f29, lbl_804DE298(r2)
/* 80340A40 0033D620  3B A0 00 00 */	li r29, 0
/* 80340A44 0033D624  EC 00 D8 28 */	fsubs f0, f0, f27
/* 80340A48 0033D628  CB C2 E8 D0 */	lfd f30, lbl_804DE2B0(r2)
/* 80340A4C 0033D62C  CB E2 E8 F8 */	lfd f31, lbl_804DE2D8(r2)
/* 80340A50 0033D630  C2 E2 E9 00 */	lfs f23, lbl_804DE2E0(r2)
/* 80340A54 0033D634  EF 21 00 24 */	fdivs f25, f1, f0
lbl_80340A58:
/* 80340A58 0033D638  38 1D 00 01 */	addi r0, r29, 1
/* 80340A5C 0033D63C  54 00 28 34 */	slwi r0, r0, 5
/* 80340A60 0033D640  90 01 00 24 */	stw r0, 0x24(r1)
/* 80340A64 0033D644  93 E1 00 20 */	stw r31, 0x20(r1)
/* 80340A68 0033D648  C8 01 00 20 */	lfd f0, 0x20(r1)
/* 80340A6C 0033D64C  EC 00 D8 28 */	fsubs f0, f0, f27
/* 80340A70 0033D650  EC 00 06 72 */	fmuls f0, f0, f25
/* 80340A74 0033D654  EC 00 06 32 */	fmuls f0, f0, f24
/* 80340A78 0033D658  EC 00 00 32 */	fmuls f0, f0, f0
/* 80340A7C 0033D65C  EC 00 D0 24 */	fdivs f0, f0, f26
/* 80340A80 0033D660  EC 5C 00 2A */	fadds f2, f28, f0
/* 80340A84 0033D664  FC 02 E8 40 */	fcmpo cr0, f2, f29
/* 80340A88 0033D668  40 81 00 54 */	ble lbl_80340ADC
/* 80340A8C 0033D66C  FC 20 10 34 */	frsqrte f1, f2
/* 80340A90 0033D670  FC 01 00 72 */	fmul f0, f1, f1
/* 80340A94 0033D674  FC 3E 00 72 */	fmul f1, f30, f1
/* 80340A98 0033D678  FC 02 00 32 */	fmul f0, f2, f0
/* 80340A9C 0033D67C  FC 1F 00 28 */	fsub f0, f31, f0
/* 80340AA0 0033D680  FC 21 00 32 */	fmul f1, f1, f0
/* 80340AA4 0033D684  FC 01 00 72 */	fmul f0, f1, f1
/* 80340AA8 0033D688  FC 3E 00 72 */	fmul f1, f30, f1
/* 80340AAC 0033D68C  FC 02 00 32 */	fmul f0, f2, f0
/* 80340AB0 0033D690  FC 1F 00 28 */	fsub f0, f31, f0
/* 80340AB4 0033D694  FC 21 00 32 */	fmul f1, f1, f0
/* 80340AB8 0033D698  FC 01 00 72 */	fmul f0, f1, f1
/* 80340ABC 0033D69C  FC 3E 00 72 */	fmul f1, f30, f1
/* 80340AC0 0033D6A0  FC 02 00 32 */	fmul f0, f2, f0
/* 80340AC4 0033D6A4  FC 1F 00 28 */	fsub f0, f31, f0
/* 80340AC8 0033D6A8  FC 01 00 32 */	fmul f0, f1, f0
/* 80340ACC 0033D6AC  FC 02 00 32 */	fmul f0, f2, f0
/* 80340AD0 0033D6B0  FC 00 00 18 */	frsp f0, f0
/* 80340AD4 0033D6B4  D0 01 00 14 */	stfs f0, 0x14(r1)
/* 80340AD8 0033D6B8  C0 41 00 14 */	lfs f2, 0x14(r1)
lbl_80340ADC:
/* 80340ADC 0033D6BC  EC 37 00 B2 */	fmuls f1, f23, f2
/* 80340AE0 0033D6C0  4B FE 1D E1 */	bl __cvt_fp2unsigned
/* 80340AE4 0033D6C4  3B BD 00 01 */	addi r29, r29, 1
/* 80340AE8 0033D6C8  54 60 05 3E */	clrlwi r0, r3, 0x14
/* 80340AEC 0033D6CC  B0 1E 00 00 */	sth r0, 0(r30)
/* 80340AF0 0033D6D0  28 1D 00 0A */	cmplwi r29, 0xa
/* 80340AF4 0033D6D4  3B DE 00 02 */	addi r30, r30, 2
/* 80340AF8 0033D6D8  41 80 FF 60 */	blt lbl_80340A58
/* 80340AFC 0033D6DC  80 01 00 84 */	lwz r0, 0x84(r1)
/* 80340B00 0033D6E0  CB E1 00 78 */	lfd f31, 0x78(r1)
/* 80340B04 0033D6E4  CB C1 00 70 */	lfd f30, 0x70(r1)
/* 80340B08 0033D6E8  7C 08 03 A6 */	mtlr r0
/* 80340B0C 0033D6EC  CB A1 00 68 */	lfd f29, 0x68(r1)
/* 80340B10 0033D6F0  CB 81 00 60 */	lfd f28, 0x60(r1)
/* 80340B14 0033D6F4  CB 61 00 58 */	lfd f27, 0x58(r1)
/* 80340B18 0033D6F8  CB 41 00 50 */	lfd f26, 0x50(r1)
/* 80340B1C 0033D6FC  CB 21 00 48 */	lfd f25, 0x48(r1)
/* 80340B20 0033D700  CB 01 00 40 */	lfd f24, 0x40(r1)
/* 80340B24 0033D704  CA E1 00 38 */	lfd f23, 0x38(r1)
/* 80340B28 0033D708  83 E1 00 34 */	lwz r31, 0x34(r1)
/* 80340B2C 0033D70C  83 C1 00 30 */	lwz r30, 0x30(r1)
/* 80340B30 0033D710  83 A1 00 2C */	lwz r29, 0x2c(r1)
/* 80340B34 0033D714  38 21 00 80 */	addi r1, r1, 0x80
/* 80340B38 0033D718  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#else

void GXInitFogAdjTable(GXFogAdjTbl* arg0, u16 arg1, Mtx44 arg2)
{
    NOT_IMPLEMENTED;
}

#endif

#ifdef MWERKS_GEKKO

#pragma push
asm void GXSetFogRangeAdj(s8, u16, GXFogAdjTbl*)
{ // clang-format off
    nofralloc
/* 80340B3C 0033D71C  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 80340B40 0033D720  41 82 00 C0 */	beq lbl_80340C00
/* 80340B44 0033D724  A1 05 00 02 */	lhz r8, 2(r5)
/* 80340B48 0033D728  38 00 00 61 */	li r0, 0x61
/* 80340B4C 0033D72C  A1 45 00 00 */	lhz r10, 0(r5)
/* 80340B50 0033D730  3C C0 CC 01 */	lis r6, 0xCC008000@ha
/* 80340B54 0033D734  55 08 60 26 */	slwi r8, r8, 0xc
/* 80340B58 0033D738  51 48 05 3E */	rlwimi r8, r10, 0, 0x14, 0x1f
/* 80340B5C 0033D73C  98 06 80 00 */	stb r0, 0xCC008000@l(r6)
/* 80340B60 0033D740  38 E0 00 E9 */	li r7, 0xe9
/* 80340B64 0033D744  55 09 02 3E */	clrlwi r9, r8, 8
/* 80340B68 0033D748  50 E9 C0 0E */	rlwimi r9, r7, 0x18, 0, 7
/* 80340B6C 0033D74C  91 26 80 00 */	stw r9, -0x8000(r6)
/* 80340B70 0033D750  38 E0 00 EA */	li r7, 0xea
/* 80340B74 0033D754  54 E9 C0 0E */	slwi r9, r7, 0x18
/* 80340B78 0033D758  A5 45 00 04 */	lhzu r10, 4(r5)
/* 80340B7C 0033D75C  38 E0 00 EB */	li r7, 0xeb
/* 80340B80 0033D760  A1 05 00 02 */	lhz r8, 2(r5)
/* 80340B84 0033D764  55 08 60 26 */	slwi r8, r8, 0xc
/* 80340B88 0033D768  98 06 80 00 */	stb r0, -0x8000(r6)
/* 80340B8C 0033D76C  51 48 05 3E */	rlwimi r8, r10, 0, 0x14, 0x1f
/* 80340B90 0033D770  51 09 02 3E */	rlwimi r9, r8, 0, 8, 0x1f
/* 80340B94 0033D774  91 26 80 00 */	stw r9, -0x8000(r6)
/* 80340B98 0033D778  54 E9 C0 0E */	slwi r9, r7, 0x18
/* 80340B9C 0033D77C  38 E0 00 EC */	li r7, 0xec
/* 80340BA0 0033D780  A1 05 00 06 */	lhz r8, 6(r5)
/* 80340BA4 0033D784  A1 45 00 04 */	lhz r10, 4(r5)
/* 80340BA8 0033D788  55 08 60 26 */	slwi r8, r8, 0xc
/* 80340BAC 0033D78C  51 48 05 3E */	rlwimi r8, r10, 0, 0x14, 0x1f
/* 80340BB0 0033D790  98 06 80 00 */	stb r0, -0x8000(r6)
/* 80340BB4 0033D794  51 09 02 3E */	rlwimi r9, r8, 0, 8, 0x1f
/* 80340BB8 0033D798  91 26 80 00 */	stw r9, -0x8000(r6)
/* 80340BBC 0033D79C  54 E9 C0 0E */	slwi r9, r7, 0x18
/* 80340BC0 0033D7A0  38 E0 00 ED */	li r7, 0xed
/* 80340BC4 0033D7A4  A1 05 00 0A */	lhz r8, 0xa(r5)
/* 80340BC8 0033D7A8  A1 45 00 08 */	lhz r10, 8(r5)
/* 80340BCC 0033D7AC  55 08 60 26 */	slwi r8, r8, 0xc
/* 80340BD0 0033D7B0  51 48 05 3E */	rlwimi r8, r10, 0, 0x14, 0x1f
/* 80340BD4 0033D7B4  98 06 80 00 */	stb r0, -0x8000(r6)
/* 80340BD8 0033D7B8  51 09 02 3E */	rlwimi r9, r8, 0, 8, 0x1f
/* 80340BDC 0033D7BC  91 26 80 00 */	stw r9, -0x8000(r6)
/* 80340BE0 0033D7C0  A1 05 00 0E */	lhz r8, 0xe(r5)
/* 80340BE4 0033D7C4  A1 45 00 0C */	lhz r10, 0xc(r5)
/* 80340BE8 0033D7C8  55 08 60 26 */	slwi r8, r8, 0xc
/* 80340BEC 0033D7CC  51 48 05 3E */	rlwimi r8, r10, 0, 0x14, 0x1f
/* 80340BF0 0033D7D0  98 06 80 00 */	stb r0, -0x8000(r6)
/* 80340BF4 0033D7D4  55 09 02 3E */	clrlwi r9, r8, 8
/* 80340BF8 0033D7D8  50 E9 C0 0E */	rlwimi r9, r7, 0x18, 0, 7
/* 80340BFC 0033D7DC  91 26 80 00 */	stw r9, -0x8000(r6)
lbl_80340C00:
/* 80340C00 0033D7E0  54 85 04 3E */	clrlwi r5, r4, 0x10
/* 80340C04 0033D7E4  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 80340C08 0033D7E8  38 05 01 56 */	addi r0, r5, 0x156
/* 80340C0C 0033D7EC  54 05 05 A8 */	rlwinm r5, r0, 0, 0x16, 0x14
/* 80340C10 0033D7F0  54 60 53 AA */	rlwinm r0, r3, 0xa, 0xe, 0x15
/* 80340C14 0033D7F4  7C A0 03 78 */	or r0, r5, r0
/* 80340C18 0033D7F8  54 05 02 3E */	clrlwi r5, r0, 8
/* 80340C1C 0033D7FC  38 00 00 61 */	li r0, 0x61
/* 80340C20 0033D800  3C 60 CC 01 */	lis r3, 0xCC008000@ha
/* 80340C24 0033D804  98 03 80 00 */	stb r0, 0xCC008000@l(r3)
/* 80340C28 0033D808  64 A5 E8 00 */	oris r5, r5, 0xe800
/* 80340C2C 0033D80C  38 00 00 00 */	li r0, 0
/* 80340C30 0033D810  90 A3 80 00 */	stw r5, -0x8000(r3)
/* 80340C34 0033D814  B0 04 00 02 */	sth r0, 2(r4)
/* 80340C38 0033D818  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#else

void GXSetFogRangeAdj(s8 arg0, u16 arg1, GXFogAdjTbl* arg2)
{
    NOT_IMPLEMENTED;
}

#endif

#ifdef MWERKS_GEKKO

#pragma push
asm void GXSetBlendMode(s32, s32, s32, s32)
{ // clang-format off
    nofralloc
/* 80340C3C 0033D81C  2C 03 00 01 */	cmpwi r3, 1
/* 80340C40 0033D820  39 20 00 01 */	li r9, 1
/* 80340C44 0033D824  41 82 00 10 */	beq lbl_80340C54
/* 80340C48 0033D828  2C 03 00 03 */	cmpwi r3, 3
/* 80340C4C 0033D82C  41 82 00 08 */	beq lbl_80340C54
/* 80340C50 0033D830  39 20 00 00 */	li r9, 0
lbl_80340C54:
/* 80340C54 0033D834  81 0D A5 08 */	lwz r8, __GXContexts(r13)
/* 80340C58 0033D838  20 03 00 03 */	subfic r0, r3, 3
/* 80340C5C 0033D83C  7C 07 00 34 */	cntlzw r7, r0
/* 80340C60 0033D840  39 48 01 D0 */	addi r10, r8, 0x1d0
/* 80340C64 0033D844  81 08 01 D0 */	lwz r8, 0x1d0(r8)
/* 80340C68 0033D848  20 03 00 02 */	subfic r0, r3, 2
/* 80340C6C 0033D84C  55 03 00 3C */	rlwinm r3, r8, 0, 0, 0x1e
/* 80340C70 0033D850  7C 63 4B 78 */	or r3, r3, r9
/* 80340C74 0033D854  90 6A 00 00 */	stw r3, 0(r10)
/* 80340C78 0033D858  7C 00 00 34 */	cntlzw r0, r0
/* 80340C7C 0033D85C  54 E3 30 28 */	rlwinm r3, r7, 6, 0, 0x14
/* 80340C80 0033D860  81 2D A5 08 */	lwz r9, __GXContexts(r13)
/* 80340C84 0033D864  54 08 E1 3C */	rlwinm r8, r0, 0x1c, 4, 0x1e
/* 80340C88 0033D868  84 09 01 D0 */	lwzu r0, 0x1d0(r9)
/* 80340C8C 0033D86C  54 C7 60 26 */	slwi r7, r6, 0xc
/* 80340C90 0033D870  54 86 40 2E */	slwi r6, r4, 8
/* 80340C94 0033D874  54 00 05 66 */	rlwinm r0, r0, 0, 0x15, 0x13
/* 80340C98 0033D878  7C 00 1B 78 */	or r0, r0, r3
/* 80340C9C 0033D87C  90 09 00 00 */	stw r0, 0(r9)
/* 80340CA0 0033D880  54 A4 28 34 */	slwi r4, r5, 5
/* 80340CA4 0033D884  38 60 00 61 */	li r3, 0x61
/* 80340CA8 0033D888  81 2D A5 08 */	lwz r9, __GXContexts(r13)
/* 80340CAC 0033D88C  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 80340CB0 0033D890  38 00 00 00 */	li r0, 0
/* 80340CB4 0033D894  39 49 01 D0 */	addi r10, r9, 0x1d0
/* 80340CB8 0033D898  81 29 01 D0 */	lwz r9, 0x1d0(r9)
/* 80340CBC 0033D89C  55 29 07 FA */	rlwinm r9, r9, 0, 0x1f, 0x1d
/* 80340CC0 0033D8A0  7D 28 43 78 */	or r8, r9, r8
/* 80340CC4 0033D8A4  91 0A 00 00 */	stw r8, 0(r10)
/* 80340CC8 0033D8A8  81 0D A5 08 */	lwz r8, __GXContexts(r13)
/* 80340CCC 0033D8AC  39 28 01 D0 */	addi r9, r8, 0x1d0
/* 80340CD0 0033D8B0  81 08 01 D0 */	lwz r8, 0x1d0(r8)
/* 80340CD4 0033D8B4  55 08 05 1E */	rlwinm r8, r8, 0, 0x14, 0xf
/* 80340CD8 0033D8B8  7D 07 3B 78 */	or r7, r8, r7
/* 80340CDC 0033D8BC  90 E9 00 00 */	stw r7, 0(r9)
/* 80340CE0 0033D8C0  80 ED A5 08 */	lwz r7, __GXContexts(r13)
/* 80340CE4 0033D8C4  39 07 01 D0 */	addi r8, r7, 0x1d0
/* 80340CE8 0033D8C8  80 E7 01 D0 */	lwz r7, 0x1d0(r7)
/* 80340CEC 0033D8CC  54 E7 06 28 */	rlwinm r7, r7, 0, 0x18, 0x14
/* 80340CF0 0033D8D0  7C E6 33 78 */	or r6, r7, r6
/* 80340CF4 0033D8D4  90 C8 00 00 */	stw r6, 0(r8)
/* 80340CF8 0033D8D8  80 CD A5 08 */	lwz r6, __GXContexts(r13)
/* 80340CFC 0033D8DC  38 E6 01 D0 */	addi r7, r6, 0x1d0
/* 80340D00 0033D8E0  80 C6 01 D0 */	lwz r6, 0x1d0(r6)
/* 80340D04 0033D8E4  54 C6 06 EE */	rlwinm r6, r6, 0, 0x1b, 0x17
/* 80340D08 0033D8E8  7C C4 23 78 */	or r4, r6, r4
/* 80340D0C 0033D8EC  90 87 00 00 */	stw r4, 0(r7)
/* 80340D10 0033D8F0  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 80340D14 0033D8F4  38 C4 01 D0 */	addi r6, r4, 0x1d0
/* 80340D18 0033D8F8  80 84 01 D0 */	lwz r4, 0x1d0(r4)
/* 80340D1C 0033D8FC  54 84 02 3E */	clrlwi r4, r4, 8
/* 80340D20 0033D900  64 84 41 00 */	oris r4, r4, 0x4100
/* 80340D24 0033D904  90 86 00 00 */	stw r4, 0(r6)
/* 80340D28 0033D908  98 65 80 00 */	stb r3, 0xCC008000@l(r5)
/* 80340D2C 0033D90C  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 80340D30 0033D910  80 64 01 D0 */	lwz r3, 0x1d0(r4)
/* 80340D34 0033D914  90 65 80 00 */	stw r3, -0x8000(r5)
/* 80340D38 0033D918  B0 04 00 02 */	sth r0, 2(r4)
/* 80340D3C 0033D91C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#else

void GXSetBlendMode(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
    NOT_IMPLEMENTED;
}

#endif

#ifdef MWERKS_GEKKO

// https://decomp.me/scratch/yi6mS // 440 (72.50%)
#pragma push
asm void GXSetColorUpdate(s32)
{ // clang-format off
    nofralloc
/* 80340D40 0033D920  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 80340D44 0033D924  54 60 1D 78 */	rlwinm r0, r3, 3, 0x15, 0x1c
/* 80340D48 0033D928  38 60 00 61 */	li r3, 0x61
/* 80340D4C 0033D92C  38 C4 01 D0 */	addi r6, r4, 0x1d0
/* 80340D50 0033D930  80 84 01 D0 */	lwz r4, 0x1d0(r4)
/* 80340D54 0033D934  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 80340D58 0033D938  54 84 07 76 */	rlwinm r4, r4, 0, 0x1d, 0x1b
/* 80340D5C 0033D93C  7C 80 03 78 */	or r0, r4, r0
/* 80340D60 0033D940  90 06 00 00 */	stw r0, 0(r6)
/* 80340D64 0033D944  38 00 00 00 */	li r0, 0
/* 80340D68 0033D948  98 65 80 00 */	stb r3, 0xCC008000@l(r5)
/* 80340D6C 0033D94C  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 80340D70 0033D950  80 64 01 D0 */	lwz r3, 0x1d0(r4)
/* 80340D74 0033D954  90 65 80 00 */	stw r3, -0x8000(r5)
/* 80340D78 0033D958  B0 04 00 02 */	sth r0, 2(r4)
/* 80340D7C 0033D95C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#else

void GXSetColorUpdate(s32 arg0)
{
    NOT_IMPLEMENTED;
}

#endif

#ifdef MWERKS_GEKKO

// https://decomp.me/scratch/NG4ef // 440 (72.50%)
#pragma push
asm void GXSetAlphaUpdate(s32)
{ // clang-format off
    nofralloc
/* 80340D80 0033D960  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 80340D84 0033D964  54 60 25 36 */	rlwinm r0, r3, 4, 0x14, 0x1b
/* 80340D88 0033D968  38 60 00 61 */	li r3, 0x61
/* 80340D8C 0033D96C  38 C4 01 D0 */	addi r6, r4, 0x1d0
/* 80340D90 0033D970  80 84 01 D0 */	lwz r4, 0x1d0(r4)
/* 80340D94 0033D974  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 80340D98 0033D978  54 84 07 34 */	rlwinm r4, r4, 0, 0x1c, 0x1a
/* 80340D9C 0033D97C  7C 80 03 78 */	or r0, r4, r0
/* 80340DA0 0033D980  90 06 00 00 */	stw r0, 0(r6)
/* 80340DA4 0033D984  38 00 00 00 */	li r0, 0
/* 80340DA8 0033D988  98 65 80 00 */	stb r3, 0xCC008000@l(r5)
/* 80340DAC 0033D98C  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 80340DB0 0033D990  80 64 01 D0 */	lwz r3, 0x1d0(r4)
/* 80340DB4 0033D994  90 65 80 00 */	stw r3, -0x8000(r5)
/* 80340DB8 0033D998  B0 04 00 02 */	sth r0, 2(r4)
/* 80340DBC 0033D99C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#else

void GXSetAlphaUpdate(s32 arg0)
{
    NOT_IMPLEMENTED;
}

#endif

#ifdef MWERKS_GEKKO

// https://decomp.me/scratch/MBnZl // 1345 (55.17%)
#pragma push
asm void GXSetZMode(s8, s32, s32)
{ // clang-format off
    nofralloc
/* 80340DC0 0033D9A0  80 CD A5 08 */	lwz r6, __GXContexts(r13)
/* 80340DC4 0033D9A4  54 60 06 3E */	clrlwi r0, r3, 0x18
/* 80340DC8 0033D9A8  80 66 01 D8 */	lwz r3, 0x1d8(r6)
/* 80340DCC 0033D9AC  38 E6 01 D8 */	addi r7, r6, 0x1d8
/* 80340DD0 0033D9B0  54 86 08 3C */	slwi r6, r4, 1
/* 80340DD4 0033D9B4  54 63 00 3C */	rlwinm r3, r3, 0, 0, 0x1e
/* 80340DD8 0033D9B8  7C 60 03 78 */	or r0, r3, r0
/* 80340DDC 0033D9BC  90 07 00 00 */	stw r0, 0(r7)
/* 80340DE0 0033D9C0  54 A4 25 36 */	rlwinm r4, r5, 4, 0x14, 0x1b
/* 80340DE4 0033D9C4  38 60 00 61 */	li r3, 0x61
/* 80340DE8 0033D9C8  80 ED A5 08 */	lwz r7, __GXContexts(r13)
/* 80340DEC 0033D9CC  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 80340DF0 0033D9D0  38 00 00 00 */	li r0, 0
/* 80340DF4 0033D9D4  39 07 01 D8 */	addi r8, r7, 0x1d8
/* 80340DF8 0033D9D8  80 E7 01 D8 */	lwz r7, 0x1d8(r7)
/* 80340DFC 0033D9DC  54 E7 07 F6 */	rlwinm r7, r7, 0, 0x1f, 0x1b
/* 80340E00 0033D9E0  7C E6 33 78 */	or r6, r7, r6
/* 80340E04 0033D9E4  90 C8 00 00 */	stw r6, 0(r8)
/* 80340E08 0033D9E8  80 CD A5 08 */	lwz r6, __GXContexts(r13)
/* 80340E0C 0033D9EC  38 E6 01 D8 */	addi r7, r6, 0x1d8
/* 80340E10 0033D9F0  80 C6 01 D8 */	lwz r6, 0x1d8(r6)
/* 80340E14 0033D9F4  54 C6 07 34 */	rlwinm r6, r6, 0, 0x1c, 0x1a
/* 80340E18 0033D9F8  7C C4 23 78 */	or r4, r6, r4
/* 80340E1C 0033D9FC  90 87 00 00 */	stw r4, 0(r7)
/* 80340E20 0033DA00  98 65 80 00 */	stb r3, 0xCC008000@l(r5)
/* 80340E24 0033DA04  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 80340E28 0033DA08  80 64 01 D8 */	lwz r3, 0x1d8(r4)
/* 80340E2C 0033DA0C  90 65 80 00 */	stw r3, -0x8000(r5)
/* 80340E30 0033DA10  B0 04 00 02 */	sth r0, 2(r4)
/* 80340E34 0033DA14  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#else

void GXSetZMode(s8 arg0, s32 arg1, s32 arg2)
{
    NOT_IMPLEMENTED;
}

#endif

#ifdef MWERKS_GEKKO

// https://decomp.me/scratch/mQjA0 // 440 (72.50%)
#pragma push
asm void GXSetZCompLoc(s32)
{ // clang-format off
    nofralloc
/* 80340E38 0033DA18  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 80340E3C 0033DA1C  54 60 34 B2 */	rlwinm r0, r3, 6, 0x12, 0x19
/* 80340E40 0033DA20  38 60 00 61 */	li r3, 0x61
/* 80340E44 0033DA24  38 C4 01 DC */	addi r6, r4, 0x1dc
/* 80340E48 0033DA28  80 84 01 DC */	lwz r4, 0x1dc(r4)
/* 80340E4C 0033DA2C  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 80340E50 0033DA30  54 84 06 B0 */	rlwinm r4, r4, 0, 0x1a, 0x18
/* 80340E54 0033DA34  7C 80 03 78 */	or r0, r4, r0
/* 80340E58 0033DA38  90 06 00 00 */	stw r0, 0(r6)
/* 80340E5C 0033DA3C  38 00 00 00 */	li r0, 0
/* 80340E60 0033DA40  98 65 80 00 */	stb r3, 0xCC008000@l(r5)
/* 80340E64 0033DA44  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 80340E68 0033DA48  80 64 01 DC */	lwz r3, 0x1dc(r4)
/* 80340E6C 0033DA4C  90 65 80 00 */	stw r3, -0x8000(r5)
/* 80340E70 0033DA50  B0 04 00 02 */	sth r0, 2(r4)
/* 80340E74 0033DA54  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#else

void GXSetZCompLoc(s32 arg0)
{
    NOT_IMPLEMENTED;
}

#endif

#ifdef MWERKS_GEKKO

// https://decomp.me/scratch/RmAUs // 715 (89.49%)
#pragma push
asm void GXSetPixelFmt(int, int)
{ // clang-format off
    nofralloc
/* 80340E78 0033DA58  80 ED A5 08 */	lwz r7, __GXContexts(r13)
/* 80340E7C 0033DA5C  3C A0 80 40 */	lis r5, lbl_80401508@ha
/* 80340E80 0033DA60  54 66 10 3A */	slwi r6, r3, 2
/* 80340E84 0033DA64  39 07 01 DC */	addi r8, r7, 0x1dc
/* 80340E88 0033DA68  38 05 15 08 */	addi r0, r5, lbl_80401508@l
/* 80340E8C 0033DA6C  80 E7 01 DC */	lwz r7, 0x1dc(r7)
/* 80340E90 0033DA70  7D 20 32 14 */	add r9, r0, r6
/* 80340E94 0033DA74  80 A9 00 00 */	lwz r5, 0(r9)
/* 80340E98 0033DA78  54 E6 00 38 */	rlwinm r6, r7, 0, 0, 0x1c
/* 80340E9C 0033DA7C  54 80 18 38 */	slwi r0, r4, 3
/* 80340EA0 0033DA80  7C C4 2B 78 */	or r4, r6, r5
/* 80340EA4 0033DA84  90 88 00 00 */	stw r4, 0(r8)
/* 80340EA8 0033DA88  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 80340EAC 0033DA8C  38 A4 01 DC */	addi r5, r4, 0x1dc
/* 80340EB0 0033DA90  80 84 01 DC */	lwz r4, 0x1dc(r4)
/* 80340EB4 0033DA94  54 84 07 72 */	rlwinm r4, r4, 0, 0x1d, 0x19
/* 80340EB8 0033DA98  7C 80 03 78 */	or r0, r4, r0
/* 80340EBC 0033DA9C  90 05 00 00 */	stw r0, 0(r5)
/* 80340EC0 0033DAA0  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 80340EC4 0033DAA4  80 A4 01 DC */	lwz r5, 0x1dc(r4)
/* 80340EC8 0033DAA8  7C 07 28 40 */	cmplw r7, r5
/* 80340ECC 0033DAAC  41 82 00 54 */	beq lbl_80340F20
/* 80340ED0 0033DAB0  38 00 00 61 */	li r0, 0x61
/* 80340ED4 0033DAB4  3C 80 CC 01 */	lis r4, 0xCC008000@ha
/* 80340ED8 0033DAB8  98 04 80 00 */	stb r0, 0xCC008000@l(r4)
/* 80340EDC 0033DABC  2C 03 00 02 */	cmpwi r3, 2
/* 80340EE0 0033DAC0  90 A4 80 00 */	stw r5, -0x8000(r4)
/* 80340EE4 0033DAC4  40 82 00 0C */	bne lbl_80340EF0
/* 80340EE8 0033DAC8  38 00 00 01 */	li r0, 1
/* 80340EEC 0033DACC  48 00 00 08 */	b lbl_80340EF4
lbl_80340EF0:
/* 80340EF0 0033DAD0  38 00 00 00 */	li r0, 0
lbl_80340EF4:
/* 80340EF4 0033DAD4  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 80340EF8 0033DAD8  54 00 4B EC */	rlwinm r0, r0, 9, 0xf, 0x16
/* 80340EFC 0033DADC  38 A4 02 04 */	addi r5, r4, 0x204
/* 80340F00 0033DAE0  80 84 02 04 */	lwz r4, 0x204(r4)
/* 80340F04 0033DAE4  54 84 05 EA */	rlwinm r4, r4, 0, 0x17, 0x15
/* 80340F08 0033DAE8  7C 80 03 78 */	or r0, r4, r0
/* 80340F0C 0033DAEC  90 05 00 00 */	stw r0, 0(r5)
/* 80340F10 0033DAF0  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 80340F14 0033DAF4  80 04 04 F0 */	lwz r0, 0x4f0(r4)
/* 80340F18 0033DAF8  60 00 00 04 */	ori r0, r0, 4
/* 80340F1C 0033DAFC  90 04 04 F0 */	stw r0, 0x4f0(r4)
lbl_80340F20:
/* 80340F20 0033DB00  80 09 00 00 */	lwz r0, 0(r9)
/* 80340F24 0033DB04  28 00 00 04 */	cmplwi r0, 4
/* 80340F28 0033DB08  40 82 00 50 */	bne lbl_80340F78
/* 80340F2C 0033DB0C  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 80340F30 0033DB10  38 63 FF FC */	addi r3, r3, -4
/* 80340F34 0033DB14  38 00 00 61 */	li r0, 0x61
/* 80340F38 0033DB18  38 A4 01 D4 */	addi r5, r4, 0x1d4
/* 80340F3C 0033DB1C  80 84 01 D4 */	lwz r4, 0x1d4(r4)
/* 80340F40 0033DB20  54 84 05 E8 */	rlwinm r4, r4, 0, 0x17, 0x14
/* 80340F44 0033DB24  50 64 4D 6C */	rlwimi r4, r3, 9, 0x15, 0x16
/* 80340F48 0033DB28  90 85 00 00 */	stw r4, 0(r5)
/* 80340F4C 0033DB2C  3C 80 CC 01 */	lis r4, 0xCC008000@ha
/* 80340F50 0033DB30  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 80340F54 0033DB34  38 A3 01 D4 */	addi r5, r3, 0x1d4
/* 80340F58 0033DB38  80 63 01 D4 */	lwz r3, 0x1d4(r3)
/* 80340F5C 0033DB3C  54 63 02 3E */	clrlwi r3, r3, 8
/* 80340F60 0033DB40  64 63 42 00 */	oris r3, r3, 0x4200
/* 80340F64 0033DB44  90 65 00 00 */	stw r3, 0(r5)
/* 80340F68 0033DB48  98 04 80 00 */	stb r0, 0xCC008000@l(r4)
/* 80340F6C 0033DB4C  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 80340F70 0033DB50  80 03 01 D4 */	lwz r0, 0x1d4(r3)
/* 80340F74 0033DB54  90 04 80 00 */	stw r0, -0x8000(r4)
lbl_80340F78:
/* 80340F78 0033DB58  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 80340F7C 0033DB5C  38 00 00 00 */	li r0, 0
/* 80340F80 0033DB60  B0 03 00 02 */	sth r0, 2(r3)
/* 80340F84 0033DB64  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#else

void GXSetPixelFmt(int arg0, int arg1)
{
    NOT_IMPLEMENTED;
}

#endif

#ifdef MWERKS_GEKKO

// https://decomp.me/scratch/Eo3bb // 440 (72.50%)
#pragma push
asm void GXSetDither(s32)
{ // clang-format off
    nofralloc
/* 80340F88 0033DB68  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 80340F8C 0033DB6C  54 60 15 BA */	rlwinm r0, r3, 2, 0x16, 0x1d
/* 80340F90 0033DB70  38 60 00 61 */	li r3, 0x61
/* 80340F94 0033DB74  38 C4 01 D0 */	addi r6, r4, 0x1d0
/* 80340F98 0033DB78  80 84 01 D0 */	lwz r4, 0x1d0(r4)
/* 80340F9C 0033DB7C  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 80340FA0 0033DB80  54 84 07 B8 */	rlwinm r4, r4, 0, 0x1e, 0x1c
/* 80340FA4 0033DB84  7C 80 03 78 */	or r0, r4, r0
/* 80340FA8 0033DB88  90 06 00 00 */	stw r0, 0(r6)
/* 80340FAC 0033DB8C  38 00 00 00 */	li r0, 0
/* 80340FB0 0033DB90  98 65 80 00 */	stb r3, 0xCC008000@l(r5)
/* 80340FB4 0033DB94  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 80340FB8 0033DB98  80 64 01 D0 */	lwz r3, 0x1d0(r4)
/* 80340FBC 0033DB9C  90 65 80 00 */	stw r3, -0x8000(r5)
/* 80340FC0 0033DBA0  B0 04 00 02 */	sth r0, 2(r4)
/* 80340FC4 0033DBA4  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#else

void GXSetDither(s32 arg0)
{
    NOT_IMPLEMENTED;
}

#endif

#ifdef MWERKS_GEKKO

#pragma push
asm void GXSetDstAlpha(s32, s32)
{ // clang-format off
    nofralloc
/* 80340FC8 0033DBA8  80 AD A5 08 */	lwz r5, __GXContexts(r13)
/* 80340FCC 0033DBAC  54 66 44 2E */	rlwinm r6, r3, 8, 0x10, 0x17
/* 80340FD0 0033DBB0  84 05 01 D4 */	lwzu r0, 0x1d4(r5)
/* 80340FD4 0033DBB4  38 60 00 61 */	li r3, 0x61
/* 80340FD8 0033DBB8  54 00 00 2E */	rlwinm r0, r0, 0, 0, 0x17
/* 80340FDC 0033DBBC  50 80 06 3E */	rlwimi r0, r4, 0, 0x18, 0x1f
/* 80340FE0 0033DBC0  90 05 00 00 */	stw r0, 0(r5)
/* 80340FE4 0033DBC4  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 80340FE8 0033DBC8  38 00 00 00 */	li r0, 0
/* 80340FEC 0033DBCC  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 80340FF0 0033DBD0  38 E4 01 D4 */	addi r7, r4, 0x1d4
/* 80340FF4 0033DBD4  80 84 01 D4 */	lwz r4, 0x1d4(r4)
/* 80340FF8 0033DBD8  54 84 06 2C */	rlwinm r4, r4, 0, 0x18, 0x16
/* 80340FFC 0033DBDC  7C 84 33 78 */	or r4, r4, r6
/* 80341000 0033DBE0  90 87 00 00 */	stw r4, 0(r7)
/* 80341004 0033DBE4  98 65 80 00 */	stb r3, 0xCC008000@l(r5)
/* 80341008 0033DBE8  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 8034100C 0033DBEC  80 64 01 D4 */	lwz r3, 0x1d4(r4)
/* 80341010 0033DBF0  90 65 80 00 */	stw r3, -0x8000(r5)
/* 80341014 0033DBF4  B0 04 00 02 */	sth r0, 2(r4)
/* 80341018 0033DBF8  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#else

void GXSetDstAlpha(s32 arg0, s32 arg1)
{
    NOT_IMPLEMENTED;
}

#endif

#ifdef MWERKS_GEKKO

#pragma push
asm void GXSetFieldMask(s32, s8)
{ // clang-format off
    nofralloc
/* 8034101C 0033DBFC  54 80 06 3E */	clrlwi r0, r4, 0x18
/* 80341020 0033DC00  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 80341024 0033DC04  54 05 07 FA */	rlwinm r5, r0, 0, 0x1f, 0x1d
/* 80341028 0033DC08  54 60 0D FC */	rlwinm r0, r3, 1, 0x17, 0x1e
/* 8034102C 0033DC0C  7C A0 03 78 */	or r0, r5, r0
/* 80341030 0033DC10  54 05 02 3E */	clrlwi r5, r0, 8
/* 80341034 0033DC14  38 00 00 61 */	li r0, 0x61
/* 80341038 0033DC18  3C 60 CC 01 */	lis r3, 0xCC008000@ha
/* 8034103C 0033DC1C  98 03 80 00 */	stb r0, 0xCC008000@l(r3)
/* 80341040 0033DC20  64 A5 44 00 */	oris r5, r5, 0x4400
/* 80341044 0033DC24  38 00 00 00 */	li r0, 0
/* 80341048 0033DC28  90 A3 80 00 */	stw r5, -0x8000(r3)
/* 8034104C 0033DC2C  B0 04 00 02 */	sth r0, 2(r4)
/* 80341050 0033DC30  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#endif

#ifdef MWERKS_GEKKO

#pragma push
asm void GXSetFieldMode(int arg0, int arg1)
{ // clang-format off
    nofralloc
/* 80341054 0033DC34  7C 08 02 A6 */	mflr r0
/* 80341058 0033DC38  90 01 00 04 */	stw r0, 4(r1)
/* 8034105C 0033DC3C  54 80 B0 92 */	rlwinm r0, r4, 0x16, 2, 9
/* 80341060 0033DC40  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80341064 0033DC44  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80341068 0033DC48  3F E0 CC 01 */	lis r31, 0xCC008000@ha
/* 8034106C 0033DC4C  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80341070 0033DC50  3B C0 00 61 */	li r30, 0x61
/* 80341074 0033DC54  93 A1 00 14 */	stw r29, 0x14(r1)
/* 80341078 0033DC58  7C 7D 1B 78 */	mr r29, r3
/* 8034107C 0033DC5C  80 AD A5 08 */	lwz r5, __GXContexts(r13)
/* 80341080 0033DC60  84 85 00 7C */	lwzu r4, 0x7c(r5)
/* 80341084 0033DC64  54 84 02 90 */	rlwinm r4, r4, 0, 0xa, 8
/* 80341088 0033DC68  7C 80 03 78 */	or r0, r4, r0
/* 8034108C 0033DC6C  90 05 00 00 */	stw r0, 0(r5)
/* 80341090 0033DC70  9B DF 80 00 */	stb r30, 0xCC008000@l(r31)
/* 80341094 0033DC74  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 80341098 0033DC78  80 03 00 7C */	lwz r0, 0x7c(r3)
/* 8034109C 0033DC7C  90 1F 80 00 */	stw r0, -0x8000(r31)
/* 803410A0 0033DC80  4B FF ED 01 */	bl __GXFlushTextureState
/* 803410A4 0033DC84  57 A0 06 3E */	clrlwi r0, r29, 0x18
/* 803410A8 0033DC88  9B DF 80 00 */	stb r30, -0x8000(r31)
/* 803410AC 0033DC8C  64 00 68 00 */	oris r0, r0, 0x6800
/* 803410B0 0033DC90  90 1F 80 00 */	stw r0, -0x8000(r31)
/* 803410B4 0033DC94  4B FF EC ED */	bl __GXFlushTextureState
/* 803410B8 0033DC98  80 01 00 24 */	lwz r0, 0x24(r1)
/* 803410BC 0033DC9C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 803410C0 0033DCA0  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 803410C4 0033DCA4  7C 08 03 A6 */	mtlr r0
/* 803410C8 0033DCA8  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 803410CC 0033DCAC  38 21 00 20 */	addi r1, r1, 0x20
/* 803410D0 0033DCB0  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#else

void GXSetFieldMode(int arg0, int arg1)
{
    NOT_IMPLEMENTED;
}

#endif
