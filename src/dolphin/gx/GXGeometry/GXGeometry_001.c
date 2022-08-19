#include <dolphin/gx/__types.h>
#include <dolphin/gx/__GXInit.h>
#include <dolphin/gx/GX_unknown_001/__GX_unknown_001.h>

void __GXSetDirtyState(void)
{
    if (__GXContexts.main->x4F0 & 1)
        __GXSetSUTexSize();
    if (__GXContexts.main->x4F0 & 2)
        __GXUpdateBPMask();
    if (__GXContexts.main->x4F0 & 4)
        __GXSetGenMode();
    if (__GXContexts.main->x4F0 & 8)
        __GXSetVCD();
    if (__GXContexts.main->x4F0 & 0x10)
        __GXSetVAT();
    __GXContexts.main->x4F0 = 0;
}

void GXBegin(GXPrimitive type, GXVtxFmt vtxfmt, u16 nverts)
{
    if (__GXContexts.main->x4F0 != 0)
        __GXSetDirtyState();
    if (__GXContexts.main->x0.u32 == 0)
        __GXSendFlushPrim();
    WGPIPE.u8 = vtxfmt | type;
    WGPIPE.u16 = nverts;
}

void __GXSendFlushPrim()
{
    u32 size;
    u32 i;

    GXContext *ctx = __GXContexts.main;
    size = ctx->x4 * ctx->x6;

    WGPIPE.u8 = GX_DRAW_TRIANGLE_STRIP;
    WGPIPE.u16 = ctx->x4;

    for (i = 0; i < size; i += 4)
        WGPIPE.u32 = 0;

    __GXContexts.main->x0.u16[1] = 1;
}

void GXSetLineWidth(u8 width, GXTexOffset texOffsets)
{
    INSERT_FIELD(__GXContexts.main->x7C, width, 8, 0);
    INSERT_FIELD(__GXContexts.main->x7C, texOffsets, 3, 16);
    GX_WRITE_U8(0x61);
    GX_WRITE_U32(__GXContexts.main->x7C);
    __GXContexts.main->x0.u16[1] = 0;
}

void GXSetPointSize(u8 pointSize, GXTexOffset texOffsets)
{
    INSERT_FIELD(__GXContexts.main->x7C, pointSize, 8, 8);
    INSERT_FIELD(__GXContexts.main->x7C, texOffsets, 3, 19);
    GX_WRITE_U8(0x61);
    GX_WRITE_U32(__GXContexts.main->x7C);
    __GXContexts.main->x0.u16[1] = 0;
}

void GXEnableTexOffsets(GXTexCoordID coord, GXBool line_enable, GXBool point_enable)
{
    INSERT_FIELD(__GXContexts.main->xB8[coord], line_enable, 1, 18);
    INSERT_FIELD(__GXContexts.main->xB8[coord], point_enable, 1, 19);
    GX_WRITE_U8(0x61);
    GX_WRITE_U32(__GXContexts.main->xB8[coord]);
    __GXContexts.main->x0.u16[1] = 0;
}

void GXSetCullMode(GXCullMode mode)
{
    switch (mode)
    {
    case GX_CULL_FRONT:
        mode = GX_CULL_BACK;
        break;
    case GX_CULL_BACK:
        mode = GX_CULL_FRONT;
        break;
    }
    INSERT_FIELD(__GXContexts.main->x204, mode, 2, 14);
    __GXContexts.main->x4F0 |= 4;
}

void GXSetCoPlanar(GXBool enable)
{
    INSERT_FIELD(__GXContexts.main->x204, enable, 1, 19);
    GX_WRITE_U8(0x61);
    GX_WRITE_U32(0xFE080000);
    GX_WRITE_U8(0x61);
    GX_WRITE_U32(__GXContexts.main->x204);
}
