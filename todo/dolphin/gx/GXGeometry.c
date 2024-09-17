#include <dolphin/gx.h>
#include <dolphin/gx/__GXInit.h>
#include <dolphin/gx/__types.h>
#include <dolphin/gx/GXAttr.h>
#include <dolphin/gx/GXBump.h>
#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXTexture.h>

static void __GXSetGenMode(void);

void __GXSetDirtyState(void)
{
    if (__GXContexts.main->x4F0_flags & 1) {
        __GXSetSUTexSize();
    }
    if (__GXContexts.main->x4F0_flags & 2) {
        __GXUpdateBPMask();
    }
    if (__GXContexts.main->x4F0_flags & 4) {
        __GXSetGenMode();
    }
    if (__GXContexts.main->x4F0_flags & 8) {
        __GXSetVCD();
    }
    if (__GXContexts.main->x4F0_flags & 0x10) {
        __GXSetVAT();
    }
    __GXContexts.main->x4F0_flags = 0;
}

void GXBegin(GXPrimitive type, GXVtxFmt vtxfmt, u16 nverts)
{
    if (__GXContexts.main->x4F0_flags != 0) {
        __GXSetDirtyState();
    }
    if (__GXContexts.main->x0.u32 == 0) {
        __GXSendFlushPrim();
    }
    WGPIPE.u8 = vtxfmt | type;
    WGPIPE.u16 = nverts;
}

void __GXSendFlushPrim(void)
{
    u32 size;
    u32 i;

    GXContext* ctx = __GXContexts.main;
    size = ctx->x4 * ctx->x6;

    WGPIPE.u8 = GX_DRAW_TRIANGLE_STRIP;
    WGPIPE.u16 = ctx->x4;

    for (i = 0; i < size; i += 4) {
        WGPIPE.u32 = 0;
    }

    set_x2(GX_TRUE);
}

void GXSetLineWidth(u8 width, GXTexOffset texOffsets)
{
    INSERT_FIELD(__GXContexts.main->x7C, width, 8, 0);
    INSERT_FIELD(__GXContexts.main->x7C, texOffsets, 3, 16);
    WGPIPE.u8 = GX_LOAD_BP_REG;
    GX_WRITE_U32(__GXContexts.main->x7C);
    set_x2(GX_FALSE);
}

void GXSetPointSize(u8 pointSize, GXTexOffset texOffsets)
{
    INSERT_FIELD(__GXContexts.main->x7C, pointSize, 8, 8);
    INSERT_FIELD(__GXContexts.main->x7C, texOffsets, 3, 19);
    WGPIPE.u8 = GX_LOAD_BP_REG;
    GX_WRITE_U32(__GXContexts.main->x7C);
    set_x2(GX_FALSE);
}

void GXEnableTexOffsets(GXTexCoordID coord, GXBool line_enable,
                        GXBool point_enable)
{
    INSERT_FIELD(__GXContexts.main->xB8[coord], line_enable, 1, 18);
    INSERT_FIELD(__GXContexts.main->xB8[coord], point_enable, 1, 19);
    WGPIPE.u8 = GX_LOAD_BP_REG;
    WGPIPE.u32 = __GXContexts.main->xB8[coord];
    set_x2(GX_FALSE);
}

void GXSetCullMode(GXCullMode mode)
{
    switch (mode) {
    case GX_CULL_FRONT:
        mode = GX_CULL_BACK;
        break;
    case GX_CULL_BACK:
        mode = GX_CULL_FRONT;
        break;
    }
    INSERT_FIELD(__GXContexts.main->x204, mode, 2, 14);
    __GXContexts.main->x4F0_flags |= 4;
}

void GXSetCoPlanar(GXBool enable)
{
    INSERT_FIELD(__GXContexts.main->x204, enable, 1, 19);
    WGPIPE.u8 = GX_LOAD_BP_REG;
    WGPIPE.u32 = 0xFE080000;
    WGPIPE.u8 = GX_LOAD_BP_REG;
    GX_WRITE_U32(__GXContexts.main->x204);
}

static void __GXSetGenMode(void)
{
    WGPIPE.u8 = GX_LOAD_BP_REG;
    GX_WRITE_U32(__GXContexts.main->x204);
    set_x2(GX_FALSE);
}
