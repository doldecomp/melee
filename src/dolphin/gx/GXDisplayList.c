#include <dolphin/gx/forward.h>

#include <dolphin/gx/__GXInit.h>
#include <dolphin/gx/__types.h>
#include <dolphin/gx/GXDisplayList.h>
#include <dolphin/gx/GXEnum.h>
#include <dolphin/gx/GXGeometry.h>

void GXCallDisplayList(s32 arg0, s32 arg1)
{
    if (__GXContexts.main->x4F0_flags) {
        __GXSetDirtyState();
    }

    if (__GXContexts.main->x0.u32 == 0) {
        __GXSendFlushPrim();
    }

    WGPIPE.u8 = GX_CMD_CALL_DL;
    WGPIPE.u32 = arg0;
    WGPIPE.u32 = arg1;
}
