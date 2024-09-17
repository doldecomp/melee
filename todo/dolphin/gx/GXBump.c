#include <placeholder.h>

#include <dolphin/gx.h>
#include <dolphin/gx/__GXInit.h>
#include <dolphin/gx/__types.h>
#include <dolphin/gx/GXBump.h>
#include <dolphin/gx/GXEnum.h>

static Vec2 const GXBump_804DE290 = { 1024.0F, 0.0F };

// https://decomp.me/scratch/nTyRU // 1150 (70.51%)
void GXSetTevIndirect(s32 arg0, s32 arg1, u8 arg2, s32 arg3, s32 arg4,
                      s32 arg5, s32 arg6, s32 arg7)
{
    NOT_IMPLEMENTED;
}

void GXSetIndTexMtx(s32 arg0, UNK_T arg1, s32 arg2)
{
    NOT_IMPLEMENTED;
}

// https://decomp.me/scratch/VEhb9 // 355 (96.97%)
void GXSetIndTexCoordScale(s32 arg0, s32 arg1, s32 arg2)
{
    NOT_IMPLEMENTED;
}

void GXSetIndTexOrder(s32 arg0, s32 arg1, s32 arg2)
{
    NOT_IMPLEMENTED;
}

void GXSetNumIndStages(s32 arg0)
{
    __GXContexts.main->x204 =
        (__GXContexts.main->x204 & 0xFFF8FFFF) | (arg0 << 0x10 & 0xFF0000);
    __GXContexts.main->x4F0_flags |= 6;
}

// https://decomp.me/scratch/aRJcf // 362 (79.89%)
void GXSetTevDirect(void)
{
    NOT_IMPLEMENTED;
}

void __GXUpdateBPMask(void)
{
    NOT_IMPLEMENTED;
}

void __GXFlushTextureState(void)
{
    WGPIPE.u8 = GX_LOAD_BP_REG;
    WGPIPE.u32 = __GXContexts.main->x100_data[9];
    set_x2(GX_FALSE);
}
