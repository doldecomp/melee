#include <common_structs.h>
#include <dolphin/gx/GXTransform.h>
#include <dolphin/gx/GX_unknown_001.h>
#include <dolphin/gx/GX_unknown_001/__GX_unknown_001.h>
#include <dolphin/gx/__GXInit.h>
#include <dolphin/gx/__GX_unknown_001.h>

f32 const lbl_804DE2F0 = 0.0F;
f32 const lbl_804DE2F4 = 1.0F;
Vec2 const lbl_804DE2F8 = { 0.5F, 0.0F };

#pragma push
asm void GXProject(f32 x, f32 y, f32 z, MtxPtr mtx, f32* pm, f32* vp, f32* sx, f32* sy, f32* sz)
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

void GXSetProjection(f32* proj, s32 projection_type)
{
    __GXContexts.main->projection_type = projection_type;
    __GXContexts.main->projection_v[0] = proj[0];
    __GXContexts.main->projection_v[2] = proj[5];
    __GXContexts.main->projection_v[4] = proj[10];
    __GXContexts.main->projection_v[5] = proj[11];
    if ((s32) projection_type == 1) {
        __GXContexts.main->projection_v[1] = proj[3];
        __GXContexts.main->projection_v[3] = proj[7];
    } else {
        __GXContexts.main->projection_v[1] = proj[2];
        __GXContexts.main->projection_v[3] = proj[6];
    }
    WGPIPE.u8 = 0x10;
    WGPIPE.u32 = 0x61020;
    WGPIPE.f32 = __GXContexts.main->projection_v[0];
    WGPIPE.f32 = __GXContexts.main->projection_v[1];
    WGPIPE.f32 = __GXContexts.main->projection_v[2];
    WGPIPE.f32 = __GXContexts.main->projection_v[3];
    WGPIPE.f32 = __GXContexts.main->projection_v[4];
    WGPIPE.f32 = __GXContexts.main->projection_v[5];
    WGPIPE.u32 = __GXContexts.main->projection_type;
    __GXContexts.main->x0.u16[1] = 1;
}

void GXGetProjectionv(f32* proj)
{
    proj[0] = __GXContexts.main->projection_type;
    proj[1] = __GXContexts.main->projection_v[0];
    proj[2] = __GXContexts.main->projection_v[1];
    proj[3] = __GXContexts.main->projection_v[2];
    proj[4] = __GXContexts.main->projection_v[3];
    proj[5] = __GXContexts.main->projection_v[4];
    proj[6] = __GXContexts.main->projection_v[5];
}

f32 const lbl_804DE308 = 342.0F;
f32 const lbl_804DE30C = 16777215.0F;

asm void WriteMTXPS4x3(Vec2 src[6], Vec2* dst)
{
    // clang-format off
    nofralloc
    psq_l f0, 0(r3), 0, qr0
    psq_l f1, 8(r3), 0, qr0
    psq_l f2, 0x10(r3), 0, qr0
    psq_l f3, 0x18(r3), 0, qr0
    psq_l f4, 0x20(r3), 0, qr0
    psq_l f5, 0x28(r3), 0, qr0
    psq_st f0, 0(r4), 0, qr0
    psq_st f1, 0(r4), 0, qr0
    psq_st f2, 0(r4), 0, qr0
    psq_st f3, 0(r4), 0, qr0
    psq_st f4, 0(r4), 0, qr0
    psq_st f5, 0(r4), 0, qr0
    blr
    // clang-format on
}

// https://decomp.me/scratch/OH9kG // 0 (100%)
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

// https://decomp.me/scratch/VVoAR // 0 (100%)
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

// NOTE: peephole off is needed for following functions to match
// The previous matrix functions were probably inline asm in the original source,
// which triggered the peephole off MWCC bug.

#pragma peephole off
void GXLoadPosMtxImm(void* mtx, s32 arg1)
{
    WGPIPE.u8 = 0x10;
    WGPIPE.u32 = arg1 * 4 | 0xB0000;
    WriteMTXPS4x3(mtx, (void*) &WGPIPE.u8);
}

void GXLoadNrmMtxImm(void* mtx, s32 arg1)
{
    WGPIPE.u8 = 0x10;
    WGPIPE.u32 = (arg1 * 3 + 0x400) | 0x80000;
    WriteMTXPS3x3from3x4(mtx, (void*) &WGPIPE.u8);
}

void GXSetCurrentMtx(s32 arg0)
{
    __GXContexts.main->x80 = (__GXContexts.main->x80 & 0xFFFFFFC0) | arg0;
    __GXSetMatrixIndex(0);
}

void GXLoadTexMtxImm(void* arg0, u32 arg1, s32 arg2)
{
    u32 var_r4;
    s32 var_r7;

    if (arg1 >= 0x40) {
        var_r7 = ((arg1 - 0x40) << 2) + 0x500;
    } else {
        var_r7 = arg1 << 2;
    }
    if (arg2 == 1) {
        var_r4 = 0x8;
    } else {
        var_r4 = 0xC;
    }
    WGPIPE.u8 = 0x10;
    WGPIPE.u32 = (var_r7 | ((var_r4 - 1) << 0x10));

    if (arg2 == 0) {
        WriteMTXPS4x3(arg0, (void*) &WGPIPE.u8);
    } else {
        WriteMTXPS4x2(arg0, (void*) &WGPIPE.u8);
    }
}

// https://decomp.me/scratch/RalqB // 342 (95.18%)
#pragma push
asm void GXSetViewportJitter(f32 left, f32 top, f32 wd, f32 ht, f32 nearz, f32 farz, u32 field)
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

void GXSetViewport(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5)
{
    GXSetViewportJitter(arg0, arg1, arg2, arg3, arg4, arg5, 1);
}

void GXGetViewportv(f32* viewport_v)
{
    viewport_v[0] = __GXContexts.main->viewport_v[0];
    viewport_v[1] = __GXContexts.main->viewport_v[1];
    viewport_v[2] = __GXContexts.main->viewport_v[2];
    viewport_v[3] = __GXContexts.main->viewport_v[3];
    viewport_v[4] = __GXContexts.main->viewport_v[4];
    viewport_v[5] = __GXContexts.main->viewport_v[5];
}

void GXSetScissor(s32 left, s32 top, s32 width, s32 height)
{
    s32 temp_r8 = left + 0x156;
    s32 temp_r4 = top + 0x156;
    __GXContexts.main->xF8 = __GXContexts.main->xF8 & 0xFFFFF800 | temp_r4;
    __GXContexts.main->xF8 = __GXContexts.main->xF8 & 0xFF800FFF | (temp_r8 << 0xC);
    __GXContexts.main->xFC = __GXContexts.main->xFC & 0xFFFFF800 | (temp_r4 + height - 1);
    __GXContexts.main->xFC = __GXContexts.main->xFC & 0xFF800FFF | ((temp_r8 + width - 1) << 0xC);
    WGPIPE.u8 = 0x61;
    WGPIPE.u32 = __GXContexts.main->xF8;
    WGPIPE.u8 = 0x61;
    WGPIPE.u32 = __GXContexts.main->xFC;
    __GXContexts.main->x0.u16[1] = 0;
}

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

void GXSetClipMode(s32 mode)
{
    WGPIPE.u8 = 0x10;
    WGPIPE.u32 = 0x1005;
    WGPIPE.u32 = mode;
    __GXContexts.main->x0.u16[1] = 1;
}

void __GXSetMatrixIndex(s32 arg0)
{
    if (arg0 < 5) {
        WGPIPE.u8 = 8;
        WGPIPE.u8 = 0x30;
        WGPIPE.u32 = __GXContexts.main->x80;
        WGPIPE.u8 = 0x10;
        WGPIPE.u32 = 0x1018;
        WGPIPE.u32 = __GXContexts.main->x80;
    } else {
        WGPIPE.u8 = 8;
        WGPIPE.u8 = 0x40;
        WGPIPE.u32 = __GXContexts.main->x84;
        WGPIPE.u8 = 0x10;
        WGPIPE.u32 = 0x1019;
        WGPIPE.u32 = __GXContexts.main->x84;
    }
    __GXContexts.main->x0.u16[1] = 1;
}
