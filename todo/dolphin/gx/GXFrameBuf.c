#include <placeholder.h>

#include <dolphin/gx.h>
#include <dolphin/gx/__GXInit.h>
#include <dolphin/gx/__types.h>
#include <dolphin/gx/GXFrameBuf.h>
#include <dolphin/mtx.h>

Vec2 const GXFrameBuf_804DE220 = { 256.0F, 0.0F };
Vec2 const GXFrameBuf_804DE228 = { 176.0F, 0.0F };

GXRenderModeObj GXNtsc480IntDf = {
    0,
    640,
    480,
    480,
    40,
    0,
    640,
    480,
    1,
    0,
    0,
    { { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 } },
    { 8, 8, 10, 12, 10, 8, 8 },
};

GXRenderModeObj GXFrameBuf_804011A4 = {
    0,
    640,
    480,
    480,
    40,
    0,
    640,
    480,
    1,
    0,
    0,
    { { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 } },
    { 0, 0, 21, 22, 21, 0, 0 },
};

GXRenderModeObj GXFrameBuf_804011E0 = {
    2,
    640,
    480,
    480,
    40,
    0,
    640,
    480,
    0,
    0,
    0,
    { { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 } },
    { 0, 0, 21, 22, 21, 0, 0 },
};

GXRenderModeObj GXMpal480IntDf = {
    8,
    640,
    480,
    480,
    40,
    0,
    640,
    480,
    1,
    0,
    0,
    { { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 } },
    { 8, 8, 10, 12, 10, 8, 8 },
};

GXRenderModeObj GXPal528IntDf = {
    4,
    640,
    528,
    528,
    40,
    23,
    640,
    528,
    1,
    0,
    0,
    { { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 } },
    { 8, 8, 10, 12, 10, 8, 8 },
};

void GXSetDispCopySrc(u16 left, u16 top, u16 wd, u16 ht)
{
    __GXContexts.main->x1D0[4] = 0;
    INSERT_FIELD(__GXContexts.main->x1D0[4], left, 10, 0);
    __GXContexts.main->x1D0[4] =
        (__GXContexts.main->x1D0[4] & 0xFFF003FF) | ((top << 10) & 0x03FFFC00);
    INSERT_FIELD(__GXContexts.main->x1D0[4], 73, 8, 24);
    __GXContexts.main->x1D0[5] = 0;
    INSERT_FIELD(__GXContexts.main->x1D0[5], wd - 1, 10, 0);
    INSERT_FIELD(__GXContexts.main->x1D0[5], ht - 1, 10, 10);
    INSERT_FIELD(__GXContexts.main->x1D0[5], 74, 8, 24);
}

void GXSetTexCopySrc(u16 left, u16 top, u16 wd, u16 ht)
{
    __GXContexts.main->x1D0[8] = 0;
    INSERT_FIELD(__GXContexts.main->x1D0[8], left, 10, 0);
    __GXContexts.main->x1D0[8] =
        (((u32) __GXContexts.main->x1D0[8] & 0xFFF003FF) |
         ((u32) (top << 10) & 0x03FFFC00));
    INSERT_FIELD(__GXContexts.main->x1D0[8], 73, 8, 24);
    __GXContexts.main->x1D0[9] = 0;
    INSERT_FIELD(__GXContexts.main->x1D0[9], wd - 1, 10, 0);
    INSERT_FIELD(__GXContexts.main->x1D0[9], ht - 1, 10, 10);
    INSERT_FIELD(__GXContexts.main->x1D0[9], 74, 8, 24);
}

void GXSetDispCopyDst(u16 wd, u16 ht)
{
    s32 val = (s32) ((u32) (wd << 1) & 0xFFFE) >> 5;
    __GXContexts.main->x1D0[6] = 0;
    INSERT_FIELD(__GXContexts.main->x1D0[6], val, 10, 0);
    INSERT_FIELD(__GXContexts.main->x1D0[6], 77, 8, 24);
}

void GXSetTexCopyDst(u16 wd, u16 ht, GXTexFmt fmt, GXBool mipmap)
{
    NOT_IMPLEMENTED;
}

void GXSetDispCopyFrame2Field(s32 arg0)
{
    INSERT_FIELD(__GXContexts.main->x1D0[7], arg0, 2, 12);
    INSERT_FIELD(__GXContexts.main->x1D0[11], 0, 2, 12);
}

void GXSetCopyClamp(s32 arg0)
{
    NOT_IMPLEMENTED;
}

// https://decomp.me/scratch/ZNlNl // 620 (86.81%)
u32 GXSetDispCopyYScale(f32 arg0)
{
    NOT_IMPLEMENTED;
}

void GXSetCopyClear(GXColor clear_clr, u32 clear_z)
{
    NOT_IMPLEMENTED;
}

void GXSetCopyFilter(GXBool aa, u8 sample_pattern[12][2], GXBool vf,
                     u8 vfilter[7])
{
    NOT_IMPLEMENTED;
}

void GXSetDispCopyGamma(s32 arg0)
{
    INSERT_FIELD(__GXContexts.main->x1D0[7], arg0, 2, 7);
}

void GXCopyDisp(void* dest, GXBool clear)
{
    NOT_IMPLEMENTED;
}

void GXCopyTex(void* arg0, GXBool arg1)
{
    NOT_IMPLEMENTED;
}

void GXClearBoundingBox(void)
{
    WGPIPE.u8 = GX_LOAD_BP_REG;
    WGPIPE.u32 = 0x550003FF;
    WGPIPE.u8 = GX_LOAD_BP_REG;
    WGPIPE.u32 = 0x560003FF;
    set_x2(GX_FALSE);
}
