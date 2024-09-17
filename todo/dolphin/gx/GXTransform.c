#include <placeholder.h>

#include <dolphin/gx.h>
#include <dolphin/gx/__GXInit.h>
#include <dolphin/gx/__types.h>
#include <dolphin/gx/GXEnum.h>
#include <dolphin/gx/GXStubs.h>
#include <dolphin/gx/GXTransform.h>

void GXProject(f32 x, f32 y, f32 z, MtxPtr mtx, f32* pm, f32* vp, f32* sx,
               f32* sy, f32* sz)
{
    NOT_IMPLEMENTED;
}

void GXSetProjection(Mtx44 proj, s32 projection_type)
{
    __GXContexts.main->projection_type = projection_type;
    __GXContexts.main->projection_v[0] = proj[0][0];
    __GXContexts.main->projection_v[2] = proj[1][1];
    __GXContexts.main->projection_v[4] = proj[2][2];
    __GXContexts.main->projection_v[5] = proj[2][3];
    if ((s32) projection_type == 1) {
        __GXContexts.main->projection_v[1] = proj[0][3];
        __GXContexts.main->projection_v[3] = proj[1][3];
    } else {
        __GXContexts.main->projection_v[1] = proj[0][2];
        __GXContexts.main->projection_v[3] = proj[1][2];
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

void WriteMTXPS4x3(register float* src, register float* dst)
{
#ifdef MWERKS_GEKKO
    asm { // clang-format off
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
    NOT_IMPLEMENTED;
#endif
}

void WriteMTXPS3x3from3x4(register float* src, register float* dst)
{
#ifdef MWERKS_GEKKO
    asm { // clang-format off
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
    NOT_IMPLEMENTED;
#endif
}

void WriteMTXPS4x2(register float* src, register float* dst)
{
#ifdef MWERKS_GEKKO
    asm { // clang-format off
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
    NOT_IMPLEMENTED;
#endif
}

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
