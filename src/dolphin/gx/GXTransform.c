#include <common_structs.h>
#include <placeholder.h>
#include <dolphin/gx/__GX_unknown_001.h>
#include <dolphin/gx/__GXInit.h>
#include <dolphin/gx/GX_unknown_001/__GX_unknown_001.h>
#include <dolphin/gx/GXStubs.h>
#include <dolphin/gx/GXTransform.h>

#ifdef MWERKS_GEKKO

#pragma push
asm void GXProject(f32 x, f32 y, f32 z, MtxPtr mtx, f32* pm, f32* vp, f32* sx,
                   f32* sy, f32* sz)
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
/* 80341188 0033DD68  C0 22 E9 10 */	lfs f1, 0.0F
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
/* 803411D4 0033DDB4  C0 22 E9 14 */	lfs f1, 1.0F
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
/* 80341244 0033DE24  C0 02 E9 14 */	lfs f0, 1.0F
/* 80341248 0033DE28  EC E2 08 2A */	fadds f7, f2, f1
lbl_8034124C:
/* 8034124C 0033DE2C  C0 85 00 08 */	lfs f4, 8(r5)
/* 80341250 0033DE30  FC 20 18 50 */	fneg f1, f3
/* 80341254 0033DE34  C0 A2 E9 18 */	lfs f5, 0.5F
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

#else

void GXProject(f32 x, f32 y, f32 z, MtxPtr mtx, f32* pm, f32* vp, f32* sx,
               f32* sy, f32* sz)
{
    NOT_IMPLEMENTED;
}

#endif

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
    WGPIPE.u8 = GX_LOAD_XF_REG;
    WGPIPE.u32 = 0x61020;
    WGPIPE.f32 = __GXContexts.main->projection_v[0];
    WGPIPE.f32 = __GXContexts.main->projection_v[1];
    WGPIPE.f32 = __GXContexts.main->projection_v[2];
    WGPIPE.f32 = __GXContexts.main->projection_v[3];
    WGPIPE.f32 = __GXContexts.main->projection_v[4];
    WGPIPE.f32 = __GXContexts.main->projection_v[5];
    WGPIPE.u32 = __GXContexts.main->projection_type;
    set_x2(GX_TRUE);
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

#ifdef MWERKS_GEKKO

asm void WriteMTXPS4x3(register float* src, register float* dst)
{ // clang-format off
    psq_l f0, 0(src), 0, qr0
    psq_l f1, 8(src), 0, qr0
    psq_l f2, 0x10(src), 0, qr0
    psq_l f3, 0x18(src), 0, qr0
    psq_l f4, 0x20(src), 0, qr0
    psq_l f5, 0x28(src), 0, qr0
    psq_st f0, 0(dst), 0, qr0
    psq_st f1, 0(dst), 0, qr0
    psq_st f2, 0(dst), 0, qr0
    psq_st f3, 0(dst), 0, qr0
    psq_st f4, 0(dst), 0, qr0
    psq_st f5, 0(dst), 0, qr0
} // clang-format on

#else

void WriteMTXPS4x3(float* src, float* dst)
{
    NOT_IMPLEMENTED;
}

#endif

#ifdef MWERKS_GEKKO

asm void WriteMTXPS3x3from3x4(register float* src, register float* dst)
{ // clang-format off
    psq_l f0, 0(src), 0, qr0
    lfs f1, 8(src)
    psq_l f2, 16(src), 0, qr0
    lfs f3, 0x18(src)
    psq_l f4, 32(src), 0, qr0
    lfs f5, 0x28(src)
    psq_st f0, 0(dst), 0, qr0
    stfs f1, 0(dst)
    psq_st f2, 0(dst), 0, qr0
    stfs f3, 0(dst)
    psq_st f4, 0(dst), 0, qr0
    stfs f5, 0(dst)
} // clang-format on

#else

void WriteMTXPS3x3from3x4(float* src, float* dst)
{
    NOT_IMPLEMENTED;
}

#endif

#ifdef MWERKS_GEKKO

asm void WriteMTXPS4x2(register float* src, register float* dst)
{ // clang-format off
    psq_l f0, 0(src), 0, qr0
    psq_l f1, 8(src), 0, qr0
    psq_l f2, 16(src), 0, qr0
    psq_l f3, 24(src), 0, qr0
    psq_st f0, 0(dst), 0, qr0
    psq_st f1, 0(dst), 0, qr0
    psq_st f2, 0(dst), 0, qr0
    psq_st f3, 0(dst), 0, qr0
} // clang-format on

#else

void WriteMTXPS4x2(float* src, float* dst)
{
    NOT_IMPLEMENTED;
}

#endif

/**
 * @attention peephole off is needed for following functions to match
 * The previous matrix functions were probably inline asm in the original
 * source, which triggered the peephole off MWCC bug.
 */

void GXLoadPosMtxImm(void* mtx, s32 arg1)
{
    WGPIPE.u8 = GX_LOAD_XF_REG;
    WGPIPE.u32 = arg1 * 4 | 0xB0000;
    WriteMTXPS4x3(mtx, (void*) &WGPIPE.u8);
}

void GXLoadNrmMtxImm(void* mtx, s32 arg1)
{
    WGPIPE.u8 = GX_LOAD_XF_REG;
    WGPIPE.u32 = (arg1 * 3 + 0x400) | 0x80000;
    WriteMTXPS3x3from3x4(mtx, (void*) &WGPIPE.u8);
}

void GXSetCurrentMtx(s32 arg0)
{
    INSERT_FIELD(__GXContexts.main->x80, arg0, 6, 0);
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
    WGPIPE.u8 = GX_LOAD_XF_REG;
    WGPIPE.u32 = (var_r7 | ((var_r4 - 1) << 0x10));

    if (arg2 == 0) {
        WriteMTXPS4x3(arg0, (void*) &WGPIPE.u8);
    } else {
        WriteMTXPS4x2(arg0, (void*) &WGPIPE.u8);
    }
}

void GXSetViewportJitter(f32 left, f32 top, f32 width, f32 height, f32 nearz,
                         f32 farz, u32 field)
{
    f32 temp_f31;
    f32 temp_f30;
    f32 temp_f29;
    f32 temp_f28;
    f32 temp_f27;
    f32 temp_f26;
    f32 temp_f0;
    f32 w_half;
    f32 h_half;

    if (field == 0) {
        top -= 0.5F;
    }
    w_half = width / 2;
    h_half = height / 2;
    temp_f31 = width / 2;                // f31
    temp_f29 = -height / 2;              // f29
    temp_f27 = (left + w_half) + 342.0F; // f27
    temp_f26 = (top + h_half) + 342.0F;  // f26
    temp_f30 = farz * 16777215.0F;
    temp_f0 = nearz * 16777215.0F; // temp_f0
    temp_f28 = temp_f30 - temp_f0;

    __GXContexts.main->viewport_v[0] = left;
    __GXContexts.main->viewport_v[1] = top;
    __GXContexts.main->viewport_v[2] = width;
    __GXContexts.main->viewport_v[3] = height;
    __GXContexts.main->viewport_v[4] = nearz;
    __GXContexts.main->viewport_v[5] = farz;
    if (__GXContexts.main->x454_pad[0] != 0) {
        __GXSetRange(nearz, __GXContexts.main->x458);
    }
    WGPIPE.u8 = GX_LOAD_XF_REG;
    WGPIPE.u32 = 0x5101A;
    WGPIPE.f32 = temp_f31;
    WGPIPE.f32 = temp_f29;
    WGPIPE.f32 = temp_f28;
    WGPIPE.f32 = temp_f27;
    WGPIPE.f32 = temp_f26;
    WGPIPE.f32 = temp_f30;
    set_x2(GX_TRUE);
}

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
    INSERT_FIELD(__GXContexts.main->xF8, temp_r4, 11, 0);
    INSERT_FIELD(__GXContexts.main->xF8, temp_r8, 11, 12);
    INSERT_FIELD(__GXContexts.main->xFC, temp_r4 + height - 1, 11, 0);
    INSERT_FIELD(__GXContexts.main->xFC, temp_r8 + width - 1, 11, 12);
    WGPIPE.u8 = GX_LOAD_BP_REG;
    WGPIPE.u32 = __GXContexts.main->xF8;
    WGPIPE.u8 = GX_LOAD_BP_REG;
    WGPIPE.u32 = __GXContexts.main->xFC;
    set_x2(GX_FALSE);
}

void GXSetScissorBoxOffset(u32 x_off, u32 y_off)
{
    u32 var1 = (x_off + 342) / 2;
    u32 var2 = (y_off + 342) / 2;
    WGPIPE.u8 = GX_LOAD_BP_REG;
    var1 = ((var1 & 0xFFF003FF) | var2 << 10) & 0xFFFFFF;
    var1 |= 0x59000000;
    WGPIPE.u32 = var1;
    set_x2(GX_FALSE);
}

void GXSetClipMode(s32 mode)
{
    WGPIPE.u8 = GX_LOAD_XF_REG;
    WGPIPE.u32 = 0x1005;
    WGPIPE.u32 = mode;
    set_x2(GX_TRUE);
}

void __GXSetMatrixIndex(s32 arg0)
{
    if (arg0 < 5) {
        WGPIPE.u8 = GX_LOAD_CP_REG;
        WGPIPE.u8 = GX_LOAD_INDX_C;
        WGPIPE.u32 = __GXContexts.main->x80;
        WGPIPE.u8 = GX_LOAD_XF_REG;
        WGPIPE.u32 = 0x1018;
        WGPIPE.u32 = __GXContexts.main->x80;
    } else {
        WGPIPE.u8 = GX_LOAD_CP_REG;
        WGPIPE.u8 = GX_CMD_CALL_DL;
        WGPIPE.u32 = __GXContexts.main->x84;
        WGPIPE.u8 = GX_LOAD_XF_REG;
        WGPIPE.u32 = 0x1019;
        WGPIPE.u32 = __GXContexts.main->x84;
    }
    set_x2(GX_TRUE);
}
