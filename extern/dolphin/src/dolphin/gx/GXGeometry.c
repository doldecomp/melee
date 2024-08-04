#include <stddef.h>
#include <dolphin/gx.h>
#include <dolphin/os.h>
#include <macros.h>

#include "__gx.h"

void __GXSetDirtyState(void)
{
    if (gx->dirtyState & 1) {
        __GXSetSUTexRegs();
    }
    if (gx->dirtyState & 2) {
        __GXUpdateBPMask();
    }
    if (gx->dirtyState & 4) {
        __GXSetGenMode();
    }
    if (gx->dirtyState & 8) {
        __GXSetVCD();
    }
    if (gx->dirtyState & 0x10) {
        __GXSetVAT();
    }
    gx->dirtyState = 0;
}

void GXBegin(GXPrimitive type, GXVtxFmt vtxfmt, u16 nverts)
{
    ASSERTMSGLINE(0x157, vtxfmt < 8,   "GXBegin: Format Index is out of range");
    ASSERTMSGLINE(0x158, !__GXinBegin, "GXBegin: called inside another GXBegin/GXEnd");

    if (gx->dirtyState != 0) {
        __GXSetDirtyState();
    }
#if DEBUG
    if (!gx->inDispList) {
        __GXVerifyState(vtxfmt);
    }
    __GXinBegin = 1;
#endif
    if (*(u32 *)&gx->vNum != 0) {  // checks both vNum and bpSent
        __GXSendFlushPrim();
    }
    GX_WRITE_U8(vtxfmt | type);
    GX_WRITE_U16(nverts);
}

void __GXSendFlushPrim(void)
{
    u32 i;
    u32 numD = gx->vNum * gx->vLim;

    GX_WRITE_U8(0x98);
    GX_WRITE_U16(gx->vNum);
    for (i = 0; i < numD; i += 4) {
        GX_WRITE_U32(0);
    }
    gx->bpSent = 0;
}

void GXSetLineWidth(u8 width, GXTexOffset texOffsets)
{
    CHECK_GXBEGIN(0x1A8, "GXSetLineWidth");
    SET_REG_FIELD(0x1A9, gx->lpSize, 8, 0, width);
    SET_REG_FIELD(0x1AA, gx->lpSize, 3, 16, texOffsets);
    GX_WRITE_RAS_REG(gx->lpSize);
    gx->bpSent = 1;
}

void GXGetLineWidth(u8 *width, GXTexOffset *texOffsets)
{
    ASSERTMSGLINE(0x1BF, width != NULL && texOffsets != NULL, "GXGet*: invalid null pointer");

    *width      = GET_REG_FIELD(gx->lpSize, 8, 0);
    *texOffsets = GET_REG_FIELD(gx->lpSize, 3, 16);
}

void GXSetPointSize(u8 pointSize, GXTexOffset texOffsets)
{
    CHECK_GXBEGIN(0x1D4, "GXSetPointSize");
    SET_REG_FIELD(0x1D5, gx->lpSize, 8, 8, pointSize);
    SET_REG_FIELD(0x1D6, gx->lpSize, 3, 19, texOffsets);
    GX_WRITE_RAS_REG(gx->lpSize);
    gx->bpSent = 1;
}

void GXGetPointSize(u8 *pointSize, GXTexOffset *texOffsets)
{
    ASSERTMSGLINE(0x1EB, pointSize != NULL && texOffsets != NULL, "GXGet*: invalid null pointer");

    *pointSize  = (int)GET_REG_FIELD(gx->lpSize, 8, 8);
    *texOffsets = GET_REG_FIELD(gx->lpSize, 3, 19);
}

void GXEnableTexOffsets(GXTexCoordID coord, u8 line_enable, u8 point_enable)
{
    CHECK_GXBEGIN(0x201, "GXEnableTexOffsets");

    ASSERTMSGLINE(0x203, coord < 8, "GXEnableTexOffsets: Invalid coordinate Id");

    SET_REG_FIELD(0x205, gx->suTs0[coord], 1, 18, line_enable);
    SET_REG_FIELD(0x206, gx->suTs0[coord], 1, 19, point_enable);
    GX_WRITE_RAS_REG(gx->suTs0[coord]);
    gx->bpSent = 1;
}

void GXSetCullMode(GXCullMode mode)
{
    GXCullMode hwMode;

    CHECK_GXBEGIN(0x21D, "GXSetCullMode");
    switch (mode) {
    case GX_CULL_FRONT: hwMode = GX_CULL_BACK;  break;
    case GX_CULL_BACK:  hwMode = GX_CULL_FRONT; break;
    default:            hwMode = mode;          break;
    }
    SET_REG_FIELD(0x225, gx->genMode, 2, 14, hwMode);
    gx->dirtyState |= 4;
}

void GXGetCullMode(GXCullMode *mode)
{
    GXCullMode hwMode = GET_REG_FIELD(gx->genMode, 2, 14);

    switch (hwMode) {
    case GX_CULL_FRONT: *mode = GX_CULL_BACK;  break;
    case GX_CULL_BACK:  *mode = GX_CULL_FRONT; break;
    default:            *mode = hwMode;        break;
    }
}

void GXSetCoPlanar(GXBool enable)
{
    u32 reg;

    CHECK_GXBEGIN(0x24A, "GXSetCoPlanar");

    SET_REG_FIELD(0x24C, gx->genMode, 1, 19, enable);
    reg = 0xFE080000;
    GX_WRITE_RAS_REG(reg);
    GX_WRITE_RAS_REG(gx->genMode);
}

void __GXSetGenMode(void)
{
    GX_WRITE_RAS_REG(gx->genMode);
    gx->bpSent = 1;
}
