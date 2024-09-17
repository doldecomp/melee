#ifndef DOLPHIN_GX_GXLIGHT_H
#define DOLPHIN_GX_GXLIGHT_H

#include <platform.h>

#include <dolphin/gx.h>
#include <dolphin/gx/__types.h>
#include <dolphin/gx/GXEnum.h>
#include <dolphin/gx/types.h>
#include <dolphin/mtx.h>

typedef struct _GXLightObj {
    char x0[0xC];  // at 0x00
    GXColor color; // at 0x0C
    f32 aa;        // at 0x10
    f32 ab;        // at 0x14
    f32 ac;        // at 0x18
    f32 ka;        // at 0x1C
    f32 kb;        // at 0x20
    f32 kc;        // at 0x24
    Vec3 pos;      // at 0x28
    Vec3 dir;      // at 0x34
} GXLightObj;

void GXInitLightAttn(GXLightObj* light, f32 aa, f32 ab, f32 ac, f32 ka, f32 kb,
                     f32 kc);
void GXInitLightSpot(GXLightObj* light, f32 angle, GXSpotFn fn);
void GXInitLightDistAttn(GXLightObj* light, f32 ref_distance,
                         f32 ref_brightness, GXDistAttnFn dist_fn);
void GXInitLightPos(GXLightObj* light, f32 x, f32 y, f32 z);
void GXInitLightDir(GXLightObj* light, f32 x, f32 y, f32 z);
void GXInitLightColor(GXLightObj* light, GXColor color);
void GXLoadLightObjImm(GXLightObj* light, GXLightID light_id);
void GXSetChanAmbColor(GXChannelID chan, GXColor* color);
void GXSetChanMatColor(GXChannelID chan, GXColor* color);
void GXSetNumChans(u8 num_chans);
void GXSetChanCtrl(GXChannelID chan, GXBool enable, GXColorSrc amb_src,
                   GXColorSrc mat_src, u32 light_mask, GXDiffuseFn diff_fn,
                   GXAttnFn attn_fn);

#endif
