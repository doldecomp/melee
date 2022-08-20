#ifndef DOLPHIN_GX_GXLIGHT_H
#define DOLPHIN_GX_GXLIGHT_H

#include <dolphin/gx/__types.h>

typedef struct _GXLightObj
{
    char x0[0xC];  // at 0x00
    GXColor color; // at 0x0C
    f32 aa;        // at 0x10
    f32 ab;        // at 0x14
    f32 ac;        // at 0x18
    f32 ka;        // at 0x1C
    f32 kb;        // at 0x20
    f32 kc;        // at 0x24
    Vec pos;       // at 0x28
    Vec dir;       // at 0x34
} GXLightObj;

void GXSetChanCtrl(GXChannelID chan, GXBool enable, GXColorSrc amb_src, GXColorSrc mat_src,
                   u32 light_mask, GXDiffuseFn diff_fn, GXAttnFn attn_fn);
void GXSetNumChans(u8);
void GXSetChanMatColor(GXChannelID, GXColor *);
void GXSetChanAmbColor(GXChannelID, GXColor *);
void GXLoadLightObjImm(GXLightObj *, GXLightID);
void GXInitLightColor(GXLightObj *, GXColor *);
void GXInitLightDir(GXLightObj *, f32, f32, f32);
void GXInitLightPos(GXLightObj *, f32, f32, f32);
void GXInitLightDistAttn(GXLightObj *, f32, f32, GXDistAttnFn);
void GXInitLightSpot(GXLightObj *, f32, GXSpotFn);
void GXInitLightAttn(GXLightObj *lobj, f32 aa, f32 ab, f32 ac, f32 ka, f32 kb, f32 kc);

#endif