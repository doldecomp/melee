#include <common_structs.h>
#include <dolphin/gx/GX_unknown_001.h>
#include <dolphin/gx/GX_unknown_001/__GX_unknown_001.h>
#include <dolphin/gx/__GXInit.h>
#include <dolphin/gx/__GX_unknown_001.h>

f32 const lbl_804DE2F0 = 0.0F;
f32 const lbl_804DE2F4 = 1.0F;
Vec2 const lbl_804DE2F8 = { 0.5F, 0.0F };
f64 const lbl_804DE300 = 4503599627370496.0L;
f32 const lbl_804DE308 = 342.0F;
f32 const lbl_804DE30C = 16777215.0F;

#pragma push
asm unk_t GXProject()
{ // clang-format off
    nofralloc
/* 80341148 0033DD28  C0 83 00 00 */	lfs f4, 0(r3)
/* 8034114C 0033DD2C  C0 03 00 04 */	lfs f0, 4(r3)
/* 80341150 0033DD30  C0 C3 00 10 */	lfs f6, 0x10(r3)
/* 80341154 0033DD34  ED 44 00 72 */	fmuls f10, f4, f1
/* 80341158 0033DD38  C0 A3 00 14 */	lfs f5, 0x14(r3)
/* 8034115C 0033DD3C  ED 20 00 B2 */	fmuls f9, f0, f2
/* 80341160 0033DD40  C0 83 00 20 */	lfs f4, 0x20(r3)
/* 80341164 0033DD44  C0 03 00 24 */	lfs f0, 0x24(r3)
/* 80341168 0033DD48  C1 63 00 08 */	lfs f11, 8(r3)
/* 8034116C 0033DD4C  EC E6 00 72 */	fmuls f7, f6, f1
/* 80341170 0033DD50  EC C5 00 B2 */	fmuls f6, f5, f2
/* 80341174 0033DD54  C1 03 00 18 */	lfs f8, 0x18(r3)
/* 80341178 0033DD58  C0 A3 00 28 */	lfs f5, 0x28(r3)
/* 8034117C 0033DD5C  EC 84 00 72 */	fmuls f4, f4, f1
/* 80341180 0033DD60  EC 40 00 B2 */	fmuls f2, f0, f2
/* 80341184 0033DD64  ED 6B 00 F2 */	fmuls f11, f11, f3
/* 80341188 0033DD68  C0 22 E9 10 */	lfs f1, lbl_804DE2F0(r2)
/* 8034118C 0033DD6C  ED 2A 48 2A */	fadds f9, f10, f9
/* 80341190 0033DD70  C0 04 00 00 */	lfs f0, 0(r4)
/* 80341194 0033DD74  ED 08 00 F2 */	fmuls f8, f8, f3
/* 80341198 0033DD78  EC C7 30 2A */	fadds f6, f7, f6
/* 8034119C 0033DD7C  C1 43 00 0C */	lfs f10, 0xc(r3)
/* 803411A0 0033DD80  ED 2B 48 2A */	fadds f9, f11, f9
/* 803411A4 0033DD84  C0 E3 00 1C */	lfs f7, 0x1c(r3)
/* 803411A8 0033DD88  EC C8 30 2A */	fadds f6, f8, f6
/* 803411AC 0033DD8C  EC 65 00 F2 */	fmuls f3, f5, f3
/* 803411B0 0033DD90  C0 A3 00 2C */	lfs f5, 0x2c(r3)
/* 803411B4 0033DD94  EC 44 10 2A */	fadds f2, f4, f2
/* 803411B8 0033DD98  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 803411BC 0033DD9C  ED 0A 48 2A */	fadds f8, f10, f9
/* 803411C0 0033DDA0  EC 03 10 2A */	fadds f0, f3, f2
/* 803411C4 0033DDA4  EC E7 30 2A */	fadds f7, f7, f6
/* 803411C8 0033DDA8  ED 25 00 2A */	fadds f9, f5, f0
/* 803411CC 0033DDAC  40 82 00 4C */	bne lbl_80341218
/* 803411D0 0033DDB0  FC 00 48 50 */	fneg f0, f9
/* 803411D4 0033DDB4  C0 22 E9 14 */	lfs f1, lbl_804DE2F4(r2)
/* 803411D8 0033DDB8  C0 C4 00 04 */	lfs f6, 4(r4)
/* 803411DC 0033DDBC  C0 A4 00 08 */	lfs f5, 8(r4)
/* 803411E0 0033DDC0  EC 01 00 24 */	fdivs f0, f1, f0
/* 803411E4 0033DDC4  C0 84 00 0C */	lfs f4, 0xc(r4)
/* 803411E8 0033DDC8  C0 64 00 10 */	lfs f3, 0x10(r4)
/* 803411EC 0033DDCC  C0 24 00 14 */	lfs f1, 0x14(r4)
/* 803411F0 0033DDD0  C0 44 00 18 */	lfs f2, 0x18(r4)
/* 803411F4 0033DDD4  EC 29 00 72 */	fmuls f1, f9, f1
/* 803411F8 0033DDD8  EC C8 01 B2 */	fmuls f6, f8, f6
/* 803411FC 0033DDDC  EC A9 01 72 */	fmuls f5, f9, f5
/* 80341200 0033DDE0  EC 87 01 32 */	fmuls f4, f7, f4
/* 80341204 0033DDE4  EC 69 00 F2 */	fmuls f3, f9, f3
/* 80341208 0033DDE8  EC C6 28 2A */	fadds f6, f6, f5
/* 8034120C 0033DDEC  EC E2 08 2A */	fadds f7, f2, f1
/* 80341210 0033DDF0  EC 64 18 2A */	fadds f3, f4, f3
/* 80341214 0033DDF4  48 00 00 38 */	b lbl_8034124C
lbl_80341218:
/* 80341218 0033DDF8  C0 44 00 04 */	lfs f2, 4(r4)
/* 8034121C 0033DDFC  C0 24 00 0C */	lfs f1, 0xc(r4)
/* 80341220 0033DE00  C0 04 00 14 */	lfs f0, 0x14(r4)
/* 80341224 0033DE04  EC A8 00 B2 */	fmuls f5, f8, f2
/* 80341228 0033DE08  C0 C4 00 08 */	lfs f6, 8(r4)
/* 8034122C 0033DE0C  EC 67 00 72 */	fmuls f3, f7, f1
/* 80341230 0033DE10  C0 84 00 10 */	lfs f4, 0x10(r4)
/* 80341234 0033DE14  EC 29 00 32 */	fmuls f1, f9, f0
/* 80341238 0033DE18  C0 44 00 18 */	lfs f2, 0x18(r4)
/* 8034123C 0033DE1C  EC C6 28 2A */	fadds f6, f6, f5
/* 80341240 0033DE20  EC 64 18 2A */	fadds f3, f4, f3
/* 80341244 0033DE24  C0 02 E9 14 */	lfs f0, lbl_804DE2F4(r2)
/* 80341248 0033DE28  EC E2 08 2A */	fadds f7, f2, f1
lbl_8034124C:
/* 8034124C 0033DE2C  C0 85 00 08 */	lfs f4, 8(r5)
/* 80341250 0033DE30  FC 20 18 50 */	fneg f1, f3
/* 80341254 0033DE34  C0 A2 E9 18 */	lfs f5, lbl_804DE2F8(r2)
/* 80341258 0033DE38  EC 46 01 32 */	fmuls f2, f6, f4
/* 8034125C 0033DE3C  C0 65 00 00 */	lfs f3, 0(r5)
/* 80341260 0033DE40  EC 84 01 72 */	fmuls f4, f4, f5
/* 80341264 0033DE44  EC 42 01 72 */	fmuls f2, f2, f5
/* 80341268 0033DE48  EC 40 00 B2 */	fmuls f2, f0, f2
/* 8034126C 0033DE4C  EC 43 10 2A */	fadds f2, f3, f2
/* 80341270 0033DE50  EC 44 10 2A */	fadds f2, f4, f2
/* 80341274 0033DE54  D0 46 00 00 */	stfs f2, 0(r6)
/* 80341278 0033DE58  C0 65 00 0C */	lfs f3, 0xc(r5)
/* 8034127C 0033DE5C  C0 45 00 04 */	lfs f2, 4(r5)
/* 80341280 0033DE60  EC 21 00 F2 */	fmuls f1, f1, f3
/* 80341284 0033DE64  EC 63 01 72 */	fmuls f3, f3, f5
/* 80341288 0033DE68  EC 21 01 72 */	fmuls f1, f1, f5
/* 8034128C 0033DE6C  EC 20 00 72 */	fmuls f1, f0, f1
/* 80341290 0033DE70  EC 22 08 2A */	fadds f1, f2, f1
/* 80341294 0033DE74  EC 23 08 2A */	fadds f1, f3, f1
/* 80341298 0033DE78  D0 27 00 00 */	stfs f1, 0(r7)
/* 8034129C 0033DE7C  C0 45 00 14 */	lfs f2, 0x14(r5)
/* 803412A0 0033DE80  C0 25 00 10 */	lfs f1, 0x10(r5)
/* 803412A4 0033DE84  EC 22 08 28 */	fsubs f1, f2, f1
/* 803412A8 0033DE88  EC 27 00 72 */	fmuls f1, f7, f1
/* 803412AC 0033DE8C  EC 00 00 72 */	fmuls f0, f0, f1
/* 803412B0 0033DE90  EC 02 00 2A */	fadds f0, f2, f0
/* 803412B4 0033DE94  D0 08 00 00 */	stfs f0, 0(r8)
/* 803412B8 0033DE98  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

// https://decomp.me/scratch/2kUst
#pragma push
asm unk_t GXSetProjection()
{ // clang-format off
    nofralloc
/* 803412BC 0033DE9C  80 AD A5 08 */	lwz r5, __GXContexts(r13)
/* 803412C0 0033DEA0  2C 04 00 01 */	cmpwi r4, 1
/* 803412C4 0033DEA4  90 85 04 20 */	stw r4, 0x420(r5)
/* 803412C8 0033DEA8  C0 03 00 00 */	lfs f0, 0(r3)
/* 803412CC 0033DEAC  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 803412D0 0033DEB0  D0 04 04 24 */	stfs f0, 0x424(r4)
/* 803412D4 0033DEB4  C0 03 00 14 */	lfs f0, 0x14(r3)
/* 803412D8 0033DEB8  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 803412DC 0033DEBC  D0 04 04 2C */	stfs f0, 0x42c(r4)
/* 803412E0 0033DEC0  C0 03 00 28 */	lfs f0, 0x28(r3)
/* 803412E4 0033DEC4  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 803412E8 0033DEC8  D0 04 04 34 */	stfs f0, 0x434(r4)
/* 803412EC 0033DECC  C0 03 00 2C */	lfs f0, 0x2c(r3)
/* 803412F0 0033DED0  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 803412F4 0033DED4  D0 04 04 38 */	stfs f0, 0x438(r4)
/* 803412F8 0033DED8  40 82 00 20 */	bne lbl_80341318
/* 803412FC 0033DEDC  C0 03 00 0C */	lfs f0, 0xc(r3)
/* 80341300 0033DEE0  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 80341304 0033DEE4  D0 04 04 28 */	stfs f0, 0x428(r4)
/* 80341308 0033DEE8  C0 03 00 1C */	lfs f0, 0x1c(r3)
/* 8034130C 0033DEEC  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 80341310 0033DEF0  D0 03 04 30 */	stfs f0, 0x430(r3)
/* 80341314 0033DEF4  48 00 00 1C */	b lbl_80341330
lbl_80341318:
/* 80341318 0033DEF8  C0 03 00 08 */	lfs f0, 8(r3)
/* 8034131C 0033DEFC  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 80341320 0033DF00  D0 04 04 28 */	stfs f0, 0x428(r4)
/* 80341324 0033DF04  C0 03 00 18 */	lfs f0, 0x18(r3)
/* 80341328 0033DF08  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 8034132C 0033DF0C  D0 03 04 30 */	stfs f0, 0x430(r3)
lbl_80341330:
/* 80341330 0033DF10  38 00 00 10 */	li r0, 0x10
/* 80341334 0033DF14  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 80341338 0033DF18  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 8034133C 0033DF1C  3C 60 00 06 */	lis r3, 0x00061020@ha
/* 80341340 0033DF20  98 05 80 00 */	stb r0, 0xCC008000@l(r5)
/* 80341344 0033DF24  38 03 10 20 */	addi r0, r3, 0x00061020@l
/* 80341348 0033DF28  90 05 80 00 */	stw r0, -0x8000(r5)
/* 8034134C 0033DF2C  38 00 00 01 */	li r0, 1
/* 80341350 0033DF30  C0 04 04 24 */	lfs f0, 0x424(r4)
/* 80341354 0033DF34  D0 05 80 00 */	stfs f0, -0x8000(r5)
/* 80341358 0033DF38  C0 04 04 28 */	lfs f0, 0x428(r4)
/* 8034135C 0033DF3C  D0 05 80 00 */	stfs f0, -0x8000(r5)
/* 80341360 0033DF40  C0 04 04 2C */	lfs f0, 0x42c(r4)
/* 80341364 0033DF44  D0 05 80 00 */	stfs f0, -0x8000(r5)
/* 80341368 0033DF48  C0 04 04 30 */	lfs f0, 0x430(r4)
/* 8034136C 0033DF4C  D0 05 80 00 */	stfs f0, -0x8000(r5)
/* 80341370 0033DF50  C0 04 04 34 */	lfs f0, 0x434(r4)
/* 80341374 0033DF54  D0 05 80 00 */	stfs f0, -0x8000(r5)
/* 80341378 0033DF58  C0 04 04 38 */	lfs f0, 0x438(r4)
/* 8034137C 0033DF5C  D0 05 80 00 */	stfs f0, -0x8000(r5)
/* 80341380 0033DF60  80 64 04 20 */	lwz r3, 0x420(r4)
/* 80341384 0033DF64  90 65 80 00 */	stw r3, -0x8000(r5)
/* 80341388 0033DF68  B0 04 00 02 */	sth r0, 2(r4)
/* 8034138C 0033DF6C  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t GXGetProjectionv()
{ // clang-format off
    nofralloc
/* 80341390 0033DF70  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80341394 0033DF74  3C 00 43 30 */	lis r0, 0x4330
/* 80341398 0033DF78  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 8034139C 0033DF7C  C8 22 E9 20 */	lfd f1, lbl_804DE300(r2)
/* 803413A0 0033DF80  80 84 04 20 */	lwz r4, 0x420(r4)
/* 803413A4 0033DF84  90 81 00 14 */	stw r4, 0x14(r1)
/* 803413A8 0033DF88  90 01 00 10 */	stw r0, 0x10(r1)
/* 803413AC 0033DF8C  C8 01 00 10 */	lfd f0, 0x10(r1)
/* 803413B0 0033DF90  38 21 00 18 */	addi r1, r1, 0x18
/* 803413B4 0033DF94  EC 00 08 28 */	fsubs f0, f0, f1
/* 803413B8 0033DF98  D0 03 00 00 */	stfs f0, 0(r3)
/* 803413BC 0033DF9C  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 803413C0 0033DFA0  C0 04 04 24 */	lfs f0, 0x424(r4)
/* 803413C4 0033DFA4  D0 03 00 04 */	stfs f0, 4(r3)
/* 803413C8 0033DFA8  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 803413CC 0033DFAC  C0 04 04 28 */	lfs f0, 0x428(r4)
/* 803413D0 0033DFB0  D0 03 00 08 */	stfs f0, 8(r3)
/* 803413D4 0033DFB4  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 803413D8 0033DFB8  C0 04 04 2C */	lfs f0, 0x42c(r4)
/* 803413DC 0033DFBC  D0 03 00 0C */	stfs f0, 0xc(r3)
/* 803413E0 0033DFC0  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 803413E4 0033DFC4  C0 04 04 30 */	lfs f0, 0x430(r4)
/* 803413E8 0033DFC8  D0 03 00 10 */	stfs f0, 0x10(r3)
/* 803413EC 0033DFCC  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 803413F0 0033DFD0  C0 04 04 34 */	lfs f0, 0x434(r4)
/* 803413F4 0033DFD4  D0 03 00 14 */	stfs f0, 0x14(r3)
/* 803413F8 0033DFD8  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 803413FC 0033DFDC  C0 04 04 38 */	lfs f0, 0x438(r4)
/* 80341400 0033DFE0  D0 03 00 18 */	stfs f0, 0x18(r3)
/* 80341404 0033DFE4  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

// https://decomp.me/scratch/rj8VP // 0 (100%)
#pragma push
asm unk_t WriteMTXPS4x3()
{ // clang-format off
    nofralloc
/* 80341408 0033DFE8  E0 03 00 00 */	psq_l f0, 0(r3), 0, qr0
/* 8034140C 0033DFEC  E0 23 00 08 */	psq_l f1, 8(r3), 0, qr0
/* 80341410 0033DFF0  E0 43 00 10 */	psq_l f2, 16(r3), 0, qr0
/* 80341414 0033DFF4  E0 63 00 18 */	psq_l f3, 24(r3), 0, qr0
/* 80341418 0033DFF8  E0 83 00 20 */	psq_l f4, 32(r3), 0, qr0
/* 8034141C 0033DFFC  E0 A3 00 28 */	psq_l f5, 40(r3), 0, qr0
/* 80341420 0033E000  F0 04 00 00 */	psq_st f0, 0(r4), 0, qr0
/* 80341424 0033E004  F0 24 00 00 */	psq_st f1, 0(r4), 0, qr0
/* 80341428 0033E008  F0 44 00 00 */	psq_st f2, 0(r4), 0, qr0
/* 8034142C 0033E00C  F0 64 00 00 */	psq_st f3, 0(r4), 0, qr0
/* 80341430 0033E010  F0 84 00 00 */	psq_st f4, 0(r4), 0, qr0
/* 80341434 0033E014  F0 A4 00 00 */	psq_st f5, 0(r4), 0, qr0
/* 80341438 0033E018  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

// https://decomp.me/scratch/OH9kG // 0 (100%)
#pragma push
asm unk_t WriteMTXPS3x3from3x4()
{ // clang-format off
    nofralloc
/* 8034143C 0033E01C  E0 03 00 00 */	psq_l f0, 0(r3), 0, qr0
/* 80341440 0033E020  C0 23 00 08 */	lfs f1, 8(r3)
/* 80341444 0033E024  E0 43 00 10 */	psq_l f2, 16(r3), 0, qr0
/* 80341448 0033E028  C0 63 00 18 */	lfs f3, 0x18(r3)
/* 8034144C 0033E02C  E0 83 00 20 */	psq_l f4, 32(r3), 0, qr0
/* 80341450 0033E030  C0 A3 00 28 */	lfs f5, 0x28(r3)
/* 80341454 0033E034  F0 04 00 00 */	psq_st f0, 0(r4), 0, qr0
/* 80341458 0033E038  D0 24 00 00 */	stfs f1, 0(r4)
/* 8034145C 0033E03C  F0 44 00 00 */	psq_st f2, 0(r4), 0, qr0
/* 80341460 0033E040  D0 64 00 00 */	stfs f3, 0(r4)
/* 80341464 0033E044  F0 84 00 00 */	psq_st f4, 0(r4), 0, qr0
/* 80341468 0033E048  D0 A4 00 00 */	stfs f5, 0(r4)
/* 8034146C 0033E04C  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

// https://decomp.me/scratch/VVoAR // 0 (100%)
#pragma push
asm unk_t WriteMTXPS4x2()
{ // clang-format off
    nofralloc
/* 80341470 0033E050  E0 03 00 00 */	psq_l f0, 0(r3), 0, qr0
/* 80341474 0033E054  E0 23 00 08 */	psq_l f1, 8(r3), 0, qr0
/* 80341478 0033E058  E0 43 00 10 */	psq_l f2, 16(r3), 0, qr0
/* 8034147C 0033E05C  E0 63 00 18 */	psq_l f3, 24(r3), 0, qr0
/* 80341480 0033E060  F0 04 00 00 */	psq_st f0, 0(r4), 0, qr0
/* 80341484 0033E064  F0 24 00 00 */	psq_st f1, 0(r4), 0, qr0
/* 80341488 0033E068  F0 44 00 00 */	psq_st f2, 0(r4), 0, qr0
/* 8034148C 0033E06C  F0 64 00 00 */	psq_st f3, 0(r4), 0, qr0
/* 80341490 0033E070  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

// https://decomp.me/scratch/7MZFm // 475 (68.33%)
#pragma push
asm unk_t GXLoadPosMtxImm()
{ // clang-format off
    nofralloc
/* 80341494 0033E074  7C 08 02 A6 */	mflr r0
/* 80341498 0033E078  90 01 00 04 */	stw r0, 4(r1)
/* 8034149C 0033E07C  94 21 FF F8 */	stwu r1, -8(r1)
/* 803414A0 0033E080  38 C0 00 10 */	li r6, 0x10
/* 803414A4 0033E084  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 803414A8 0033E088  54 80 10 3A */	slwi r0, r4, 2
/* 803414AC 0033E08C  98 C5 80 00 */	stb r6, 0xCC008000@l(r5)
/* 803414B0 0033E090  64 00 00 0B */	oris r0, r0, 0xb
/* 803414B4 0033E094  90 05 80 00 */	stw r0, -0x8000(r5)
/* 803414B8 0033E098  38 85 80 00 */	addi r4, r5, -32768
/* 803414BC 0033E09C  4B FF FF 4D */	bl WriteMTXPS4x3
/* 803414C0 0033E0A0  80 01 00 0C */	lwz r0, 0xc(r1)
/* 803414C4 0033E0A4  38 21 00 08 */	addi r1, r1, 8
/* 803414C8 0033E0A8  7C 08 03 A6 */	mtlr r0
/* 803414CC 0033E0AC  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

// https://decomp.me/scratch/1k0kv // 175 (89.06%)
#pragma push
asm unk_t GXLoadNrmMtxImm()
{ // clang-format off
    nofralloc
/* 803414D0 0033E0B0  7C 08 02 A6 */	mflr r0
/* 803414D4 0033E0B4  90 01 00 04 */	stw r0, 4(r1)
/* 803414D8 0033E0B8  94 21 FF F8 */	stwu r1, -8(r1)
/* 803414DC 0033E0BC  1C 84 00 03 */	mulli r4, r4, 3
/* 803414E0 0033E0C0  38 04 04 00 */	addi r0, r4, 0x400
/* 803414E4 0033E0C4  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 803414E8 0033E0C8  38 C0 00 10 */	li r6, 0x10
/* 803414EC 0033E0CC  98 C5 80 00 */	stb r6, 0xCC008000@l(r5)
/* 803414F0 0033E0D0  64 00 00 08 */	oris r0, r0, 8
/* 803414F4 0033E0D4  38 85 80 00 */	addi r4, r5, -32768
/* 803414F8 0033E0D8  90 05 80 00 */	stw r0, -0x8000(r5)
/* 803414FC 0033E0DC  4B FF FF 41 */	bl WriteMTXPS3x3from3x4
/* 80341500 0033E0E0  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80341504 0033E0E4  38 21 00 08 */	addi r1, r1, 8
/* 80341508 0033E0E8  7C 08 03 A6 */	mtlr r0
/* 8034150C 0033E0EC  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

// https://decomp.me/scratch/3z4vX // 300 (80%)
#pragma push
asm void GXSetCurrentMtx(s32)
{ // clang-format off
    nofralloc
/* 80341510 0033E0F0  7C 08 02 A6 */	mflr r0
/* 80341514 0033E0F4  90 01 00 04 */	stw r0, 4(r1)
/* 80341518 0033E0F8  94 21 FF F8 */	stwu r1, -8(r1)
/* 8034151C 0033E0FC  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 80341520 0033E100  38 84 00 80 */	addi r4, r4, 0x80
/* 80341524 0033E104  80 04 00 00 */	lwz r0, 0(r4)
/* 80341528 0033E108  54 00 00 32 */	rlwinm r0, r0, 0, 0, 0x19
/* 8034152C 0033E10C  7C 00 1B 78 */	or r0, r0, r3
/* 80341530 0033E110  90 04 00 00 */	stw r0, 0(r4)
/* 80341534 0033E114  38 60 00 00 */	li r3, 0
/* 80341538 0033E118  48 00 03 41 */	bl __GXSetMatrixIndex
/* 8034153C 0033E11C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80341540 0033E120  38 21 00 08 */	addi r1, r1, 8
/* 80341544 0033E124  7C 08 03 A6 */	mtlr r0
/* 80341548 0033E128  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

// https://decomp.me/scratch/7Jh0i // 435 (86.82%)
#pragma push
asm unk_t GXLoadTexMtxImm()
{ // clang-format off
    nofralloc
/* 8034154C 0033E12C  7C 08 02 A6 */	mflr r0
/* 80341550 0033E130  90 01 00 04 */	stw r0, 4(r1)
/* 80341554 0033E134  94 21 FF F8 */	stwu r1, -8(r1)
/* 80341558 0033E138  28 04 00 40 */	cmplwi r4, 0x40
/* 8034155C 0033E13C  41 80 00 14 */	blt lbl_80341570
/* 80341560 0033E140  38 04 FF C0 */	addi r0, r4, -64
/* 80341564 0033E144  54 04 10 3A */	slwi r4, r0, 2
/* 80341568 0033E148  38 E4 05 00 */	addi r7, r4, 0x500
/* 8034156C 0033E14C  48 00 00 08 */	b lbl_80341574
lbl_80341570:
/* 80341570 0033E150  54 87 10 3A */	slwi r7, r4, 2
lbl_80341574:
/* 80341574 0033E154  2C 05 00 01 */	cmpwi r5, 1
/* 80341578 0033E158  40 82 00 0C */	bne lbl_80341584
/* 8034157C 0033E15C  38 80 00 08 */	li r4, 8
/* 80341580 0033E160  48 00 00 08 */	b lbl_80341588
lbl_80341584:
/* 80341584 0033E164  38 80 00 0C */	li r4, 0xc
lbl_80341588:
/* 80341588 0033E168  38 04 FF FF */	addi r0, r4, -1
/* 8034158C 0033E16C  54 00 80 1E */	slwi r0, r0, 0x10
/* 80341590 0033E170  38 C0 00 10 */	li r6, 0x10
/* 80341594 0033E174  3C 80 CC 01 */	lis r4, 0xCC008000@ha
/* 80341598 0033E178  98 C4 80 00 */	stb r6, 0xCC008000@l(r4)
/* 8034159C 0033E17C  7C E0 03 78 */	or r0, r7, r0
/* 803415A0 0033E180  2C 05 00 00 */	cmpwi r5, 0
/* 803415A4 0033E184  90 04 80 00 */	stw r0, -0x8000(r4)
/* 803415A8 0033E188  40 82 00 10 */	bne lbl_803415B8
/* 803415AC 0033E18C  38 84 80 00 */	addi r4, r4, -32768
/* 803415B0 0033E190  4B FF FE 59 */	bl WriteMTXPS4x3
/* 803415B4 0033E194  48 00 00 0C */	b lbl_803415C0
lbl_803415B8:
/* 803415B8 0033E198  38 84 80 00 */	addi r4, r4, -32768
/* 803415BC 0033E19C  4B FF FE B5 */	bl WriteMTXPS4x2
lbl_803415C0:
/* 803415C0 0033E1A0  80 01 00 0C */	lwz r0, 0xc(r1)
/* 803415C4 0033E1A4  38 21 00 08 */	addi r1, r1, 8
/* 803415C8 0033E1A8  7C 08 03 A6 */	mtlr r0
/* 803415CC 0033E1AC  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

// https://decomp.me/scratch/RalqB // 342 (95.18%)
#pragma push
asm unk_t GXSetViewportJitter()
{ // clang-format off
    nofralloc
/* 803415D0 0033E1B0  7C 08 02 A6 */	mflr r0
/* 803415D4 0033E1B4  90 01 00 04 */	stw r0, 4(r1)
/* 803415D8 0033E1B8  94 21 FF A0 */	stwu r1, -0x60(r1)
/* 803415DC 0033E1BC  DB E1 00 58 */	stfd f31, 0x58(r1)
/* 803415E0 0033E1C0  DB C1 00 50 */	stfd f30, 0x50(r1)
/* 803415E4 0033E1C4  DB A1 00 48 */	stfd f29, 0x48(r1)
/* 803415E8 0033E1C8  DB 81 00 40 */	stfd f28, 0x40(r1)
/* 803415EC 0033E1CC  DB 61 00 38 */	stfd f27, 0x38(r1)
/* 803415F0 0033E1D0  DB 41 00 30 */	stfd f26, 0x30(r1)
/* 803415F4 0033E1D4  28 03 00 00 */	cmplwi r3, 0
/* 803415F8 0033E1D8  40 82 00 0C */	bne lbl_80341604
/* 803415FC 0033E1DC  C0 02 E9 18 */	lfs f0, lbl_804DE2F8(r2)
/* 80341600 0033E1E0  EC 42 00 28 */	fsubs f2, f2, f0
lbl_80341604:
/* 80341604 0033E1E4  C1 62 E9 18 */	lfs f11, lbl_804DE2F8(r2)
/* 80341608 0033E1E8  FD 40 20 50 */	fneg f10, f4
/* 8034160C 0033E1EC  C0 02 E9 2C */	lfs f0, lbl_804DE30C(r2)
/* 80341610 0033E1F0  C1 22 E9 28 */	lfs f9, lbl_804DE308(r2)
/* 80341614 0033E1F4  EF E3 02 F2 */	fmuls f31, f3, f11
/* 80341618 0033E1F8  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 8034161C 0033E1FC  EC E4 02 F2 */	fmuls f7, f4, f11
/* 80341620 0033E200  D0 23 04 3C */	stfs f1, 0x43c(r3)
/* 80341624 0033E204  ED 01 F8 2A */	fadds f8, f1, f31
/* 80341628 0033E208  EF C0 01 B2 */	fmuls f30, f0, f6
/* 8034162C 0033E20C  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 80341630 0033E210  EC 22 38 2A */	fadds f1, f2, f7
/* 80341634 0033E214  D0 43 04 40 */	stfs f2, 0x440(r3)
/* 80341638 0033E218  EC 00 01 72 */	fmuls f0, f0, f5
/* 8034163C 0033E21C  EF AA 02 F2 */	fmuls f29, f10, f11
/* 80341640 0033E220  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 80341644 0033E224  EF 69 40 2A */	fadds f27, f9, f8
/* 80341648 0033E228  D0 63 04 44 */	stfs f3, 0x444(r3)
/* 8034164C 0033E22C  EF 49 08 2A */	fadds f26, f9, f1
/* 80341650 0033E230  EF 9E 00 28 */	fsubs f28, f30, f0
/* 80341654 0033E234  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 80341658 0033E238  D0 83 04 48 */	stfs f4, 0x448(r3)
/* 8034165C 0033E23C  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 80341660 0033E240  D0 A3 04 4C */	stfs f5, 0x44c(r3)
/* 80341664 0033E244  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 80341668 0033E248  D0 C3 04 50 */	stfs f6, 0x450(r3)
/* 8034166C 0033E24C  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 80341670 0033E250  88 03 04 54 */	lbz r0, 0x454(r3)
/* 80341674 0033E254  28 00 00 00 */	cmplwi r0, 0
/* 80341678 0033E258  41 82 00 10 */	beq lbl_80341688
/* 8034167C 0033E25C  FC 20 28 90 */	fmr f1, f5
/* 80341680 0033E260  C0 43 04 58 */	lfs f2, 0x458(r3)
/* 80341684 0033E264  4B FF FA 51 */	bl __GXSetRange
lbl_80341688:
/* 80341688 0033E268  38 00 00 10 */	li r0, 0x10
/* 8034168C 0033E26C  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 80341690 0033E270  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 80341694 0033E274  3C 80 00 05 */	lis r4, 0x0005101A@ha
/* 80341698 0033E278  98 05 80 00 */	stb r0, 0xCC008000@l(r5)
/* 8034169C 0033E27C  38 04 10 1A */	addi r0, r4, 0x0005101A@l
/* 803416A0 0033E280  90 05 80 00 */	stw r0, -0x8000(r5)
/* 803416A4 0033E284  38 00 00 01 */	li r0, 1
/* 803416A8 0033E288  D3 E5 80 00 */	stfs f31, -0x8000(r5)
/* 803416AC 0033E28C  D3 A5 80 00 */	stfs f29, -0x8000(r5)
/* 803416B0 0033E290  D3 85 80 00 */	stfs f28, -0x8000(r5)
/* 803416B4 0033E294  D3 65 80 00 */	stfs f27, -0x8000(r5)
/* 803416B8 0033E298  D3 45 80 00 */	stfs f26, -0x8000(r5)
/* 803416BC 0033E29C  D3 C5 80 00 */	stfs f30, -0x8000(r5)
/* 803416C0 0033E2A0  B0 03 00 02 */	sth r0, 2(r3)
/* 803416C4 0033E2A4  80 01 00 64 */	lwz r0, 0x64(r1)
/* 803416C8 0033E2A8  CB E1 00 58 */	lfd f31, 0x58(r1)
/* 803416CC 0033E2AC  CB C1 00 50 */	lfd f30, 0x50(r1)
/* 803416D0 0033E2B0  7C 08 03 A6 */	mtlr r0
/* 803416D4 0033E2B4  CB A1 00 48 */	lfd f29, 0x48(r1)
/* 803416D8 0033E2B8  CB 81 00 40 */	lfd f28, 0x40(r1)
/* 803416DC 0033E2BC  CB 61 00 38 */	lfd f27, 0x38(r1)
/* 803416E0 0033E2C0  CB 41 00 30 */	lfd f26, 0x30(r1)
/* 803416E4 0033E2C4  38 21 00 60 */	addi r1, r1, 0x60
/* 803416E8 0033E2C8  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

// https://decomp.me/scratch/xCqrv // 0 (100%)
#pragma push
asm unk_t GXSetViewport()
{ // clang-format off
    nofralloc
/* 803416EC 0033E2CC  7C 08 02 A6 */	mflr r0
/* 803416F0 0033E2D0  90 01 00 04 */	stw r0, 4(r1)
/* 803416F4 0033E2D4  94 21 FF F8 */	stwu r1, -8(r1)
/* 803416F8 0033E2D8  38 60 00 01 */	li r3, 1
/* 803416FC 0033E2DC  4B FF FE D5 */	bl GXSetViewportJitter
/* 80341700 0033E2E0  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80341704 0033E2E4  38 21 00 08 */	addi r1, r1, 8
/* 80341708 0033E2E8  7C 08 03 A6 */	mtlr r0
/* 8034170C 0033E2EC  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

// https://decomp.me/scratch/cJr19
#pragma push
asm unk_t GXGetViewportv()
{ // clang-format off
    nofralloc
/* 80341710 0033E2F0  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 80341714 0033E2F4  C0 04 04 3C */	lfs f0, 0x43c(r4)
/* 80341718 0033E2F8  D0 03 00 00 */	stfs f0, 0(r3)
/* 8034171C 0033E2FC  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 80341720 0033E300  C0 04 04 40 */	lfs f0, 0x440(r4)
/* 80341724 0033E304  D0 03 00 04 */	stfs f0, 4(r3)
/* 80341728 0033E308  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 8034172C 0033E30C  C0 04 04 44 */	lfs f0, 0x444(r4)
/* 80341730 0033E310  D0 03 00 08 */	stfs f0, 8(r3)
/* 80341734 0033E314  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 80341738 0033E318  C0 04 04 48 */	lfs f0, 0x448(r4)
/* 8034173C 0033E31C  D0 03 00 0C */	stfs f0, 0xc(r3)
/* 80341740 0033E320  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 80341744 0033E324  C0 04 04 4C */	lfs f0, 0x44c(r4)
/* 80341748 0033E328  D0 03 00 10 */	stfs f0, 0x10(r3)
/* 8034174C 0033E32C  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 80341750 0033E330  C0 04 04 50 */	lfs f0, 0x450(r4)
/* 80341754 0033E334  D0 03 00 14 */	stfs f0, 0x14(r3)
/* 80341758 0033E338  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

// https://decomp.me/scratch/R15tQ // 1725 (60.80%)
#pragma push
asm unk_t GXSetScissor()
{ // clang-format off
    nofralloc
/* 8034175C 0033E33C  80 ED A5 08 */	lwz r7, __GXContexts(r13)
/* 80341760 0033E340  39 03 01 56 */	addi r8, r3, 0x156
/* 80341764 0033E344  38 05 FF FF */	addi r0, r5, -1
/* 80341768 0033E348  38 A7 00 F8 */	addi r5, r7, 0xf8
/* 8034176C 0033E34C  80 65 00 00 */	lwz r3, 0(r5)
/* 80341770 0033E350  7C 08 02 14 */	add r0, r8, r0
/* 80341774 0033E354  38 84 01 56 */	addi r4, r4, 0x156
/* 80341778 0033E358  54 63 00 28 */	rlwinm r3, r3, 0, 0, 0x14
/* 8034177C 0033E35C  7C 63 23 78 */	or r3, r3, r4
/* 80341780 0033E360  90 65 00 00 */	stw r3, 0(r5)
/* 80341784 0033E364  38 66 FF FF */	addi r3, r6, -1
/* 80341788 0033E368  55 07 60 26 */	slwi r7, r8, 0xc
/* 8034178C 0033E36C  80 AD A5 08 */	lwz r5, __GXContexts(r13)
/* 80341790 0033E370  7C 84 1A 14 */	add r4, r4, r3
/* 80341794 0033E374  54 03 60 26 */	slwi r3, r0, 0xc
/* 80341798 0033E378  39 05 00 F8 */	addi r8, r5, 0xf8
/* 8034179C 0033E37C  80 08 00 00 */	lwz r0, 0(r8)
/* 803417A0 0033E380  38 C0 00 61 */	li r6, 0x61
/* 803417A4 0033E384  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 803417A8 0033E388  54 00 05 10 */	rlwinm r0, r0, 0, 0x14, 8
/* 803417AC 0033E38C  7C 00 3B 78 */	or r0, r0, r7
/* 803417B0 0033E390  90 08 00 00 */	stw r0, 0(r8)
/* 803417B4 0033E394  38 00 00 00 */	li r0, 0
/* 803417B8 0033E398  80 ED A5 08 */	lwz r7, __GXContexts(r13)
/* 803417BC 0033E39C  39 07 00 FC */	addi r8, r7, 0xfc
/* 803417C0 0033E3A0  80 E8 00 00 */	lwz r7, 0(r8)
/* 803417C4 0033E3A4  54 E7 00 28 */	rlwinm r7, r7, 0, 0, 0x14
/* 803417C8 0033E3A8  7C E4 23 78 */	or r4, r7, r4
/* 803417CC 0033E3AC  90 88 00 00 */	stw r4, 0(r8)
/* 803417D0 0033E3B0  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 803417D4 0033E3B4  38 E4 00 FC */	addi r7, r4, 0xfc
/* 803417D8 0033E3B8  80 87 00 00 */	lwz r4, 0(r7)
/* 803417DC 0033E3BC  54 84 05 10 */	rlwinm r4, r4, 0, 0x14, 8
/* 803417E0 0033E3C0  7C 83 1B 78 */	or r3, r4, r3
/* 803417E4 0033E3C4  90 67 00 00 */	stw r3, 0(r7)
/* 803417E8 0033E3C8  98 C5 80 00 */	stb r6, 0xCC008000@l(r5)
/* 803417EC 0033E3CC  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 803417F0 0033E3D0  80 64 00 F8 */	lwz r3, 0xf8(r4)
/* 803417F4 0033E3D4  90 65 80 00 */	stw r3, -0x8000(r5)
/* 803417F8 0033E3D8  98 C5 80 00 */	stb r6, -0x8000(r5)
/* 803417FC 0033E3DC  80 64 00 FC */	lwz r3, 0xfc(r4)
/* 80341800 0033E3E0  90 65 80 00 */	stw r3, -0x8000(r5)
/* 80341804 0033E3E4  B0 04 00 02 */	sth r0, 2(r4)
/* 80341808 0033E3E8  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

// https://decomp.me/scratch/LBViQ // 645 (62.06%)
#pragma push
asm unk_t GXSetScissorBoxOffset()
{ // clang-format off
    nofralloc
/* 8034180C 0033E3EC  38 A3 01 56 */	addi r5, r3, 0x156
/* 80341810 0033E3F0  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 80341814 0033E3F4  38 04 01 56 */	addi r0, r4, 0x156
/* 80341818 0033E3F8  54 A4 F8 7E */	srwi r4, r5, 1
/* 8034181C 0033E3FC  54 00 F8 7E */	srwi r0, r0, 1
/* 80341820 0033E400  54 84 05 96 */	rlwinm r4, r4, 0, 0x16, 0xb
/* 80341824 0033E404  54 00 50 2A */	slwi r0, r0, 0xa
/* 80341828 0033E408  7C 80 03 78 */	or r0, r4, r0
/* 8034182C 0033E40C  54 05 02 3E */	clrlwi r5, r0, 8
/* 80341830 0033E410  38 00 00 61 */	li r0, 0x61
/* 80341834 0033E414  3C 80 CC 01 */	lis r4, 0xCC008000@ha
/* 80341838 0033E418  98 04 80 00 */	stb r0, 0xCC008000@l(r4)
/* 8034183C 0033E41C  64 A5 59 00 */	oris r5, r5, 0x5900
/* 80341840 0033E420  38 00 00 00 */	li r0, 0
/* 80341844 0033E424  90 A4 80 00 */	stw r5, -0x8000(r4)
/* 80341848 0033E428  B0 03 00 02 */	sth r0, 2(r3)
/* 8034184C 0033E42C  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

// https://decomp.me/scratch/i3OSs // 0 (100%)
#pragma push
asm unk_t GXSetClipMode()
{ // clang-format off
    nofralloc
/* 80341850 0033E430  38 00 00 10 */	li r0, 0x10
/* 80341854 0033E434  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 80341858 0033E438  3C C0 CC 01 */	lis r6, 0xCC008000@ha
/* 8034185C 0033E43C  98 06 80 00 */	stb r0, 0xCC008000@l(r6)
/* 80341860 0033E440  38 A0 10 05 */	li r5, 0x1005
/* 80341864 0033E444  38 00 00 01 */	li r0, 1
/* 80341868 0033E448  90 A6 80 00 */	stw r5, -0x8000(r6)
/* 8034186C 0033E44C  90 66 80 00 */	stw r3, -0x8000(r6)
/* 80341870 0033E450  B0 04 00 02 */	sth r0, 2(r4)
/* 80341874 0033E454  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

// https://decomp.me/scratch/lS9KQ // 0 (100%)
#pragma push
asm unk_t __GXSetMatrixIndex()
{ // clang-format off
    nofralloc
/* 80341878 0033E458  2C 03 00 05 */	cmpwi r3, 5
/* 8034187C 0033E45C  40 80 00 3C */	bge lbl_803418B8
/* 80341880 0033E460  38 00 00 08 */	li r0, 8
/* 80341884 0033E464  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 80341888 0033E468  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 8034188C 0033E46C  98 05 80 00 */	stb r0, 0xCC008000@l(r5)
/* 80341890 0033E470  38 00 00 30 */	li r0, 0x30
/* 80341894 0033E474  38 60 00 10 */	li r3, 0x10
/* 80341898 0033E478  98 05 80 00 */	stb r0, -0x8000(r5)
/* 8034189C 0033E47C  38 00 10 18 */	li r0, 0x1018
/* 803418A0 0033E480  80 84 00 80 */	lwz r4, 0x80(r4)
/* 803418A4 0033E484  90 85 80 00 */	stw r4, -0x8000(r5)
/* 803418A8 0033E488  98 65 80 00 */	stb r3, -0x8000(r5)
/* 803418AC 0033E48C  90 05 80 00 */	stw r0, -0x8000(r5)
/* 803418B0 0033E490  90 85 80 00 */	stw r4, -0x8000(r5)
/* 803418B4 0033E494  48 00 00 38 */	b lbl_803418EC
lbl_803418B8:
/* 803418B8 0033E498  38 00 00 08 */	li r0, 8
/* 803418BC 0033E49C  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 803418C0 0033E4A0  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 803418C4 0033E4A4  98 05 80 00 */	stb r0, 0xCC008000@l(r5)
/* 803418C8 0033E4A8  38 00 00 40 */	li r0, 0x40
/* 803418CC 0033E4AC  38 60 00 10 */	li r3, 0x10
/* 803418D0 0033E4B0  98 05 80 00 */	stb r0, -0x8000(r5)
/* 803418D4 0033E4B4  38 00 10 19 */	li r0, 0x1019
/* 803418D8 0033E4B8  80 84 00 84 */	lwz r4, 0x84(r4)
/* 803418DC 0033E4BC  90 85 80 00 */	stw r4, -0x8000(r5)
/* 803418E0 0033E4C0  98 65 80 00 */	stb r3, -0x8000(r5)
/* 803418E4 0033E4C4  90 05 80 00 */	stw r0, -0x8000(r5)
/* 803418E8 0033E4C8  90 85 80 00 */	stw r4, -0x8000(r5)
lbl_803418EC:
/* 803418EC 0033E4CC  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 803418F0 0033E4D0  38 00 00 01 */	li r0, 1
/* 803418F4 0033E4D4  B0 03 00 02 */	sth r0, 2(r3)
/* 803418F8 0033E4D8  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop
