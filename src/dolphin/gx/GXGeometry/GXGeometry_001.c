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
