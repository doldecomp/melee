// https://github.com/kiwi515/open_rvl/blob/366b440e58f030aa0aacc9316d2717289d58fe16/include/GX/GXLight.h

#ifndef DOLPHIN_GX_GXLIGHT_H
#define DOLPHIN_GX_GXLIGHT_H

#include <dolphin/gx/__gx.h>

typedef enum _GXAttnFn
{
    GX_ATTN_FN_0,
    GX_ATTN_FN_1,
    GX_ATTN_FN_2,
} GXAttnFn;

typedef enum _GXColorSrc
{
    GX_COLOR_SRC_0,
} GXColorSrc;

typedef enum _GXDiffuseFn
{
    GX_DIFFUSE_FN_0,
} GXDiffuseFn;

typedef enum _GXDistAttnFn
{
    GX_DIST_ATTN_FN_0,
    GX_DIST_ATTN_FN_1,
    GX_DIST_ATTN_FN_2,
    GX_DIST_ATTN_FN_3
} GXDistAttnFn;

typedef enum _GXLightID
{
    GX_LIGHT_ID_0,
} GXLightID;

typedef enum _GXSpotFn
{
    GX_SPOT_FN_0,
    GX_SPOT_FN_1,
    GX_SPOT_FN_2,
    GX_SPOT_FN_3,
    GX_SPOT_FN_4,
    GX_SPOT_FN_5,
    GX_SPOT_FN_6
} GXSpotFn;

typedef struct _GXLightObj
{
    char UNK_0x0[0xC];
    GXColor color; // at 0xC
    f32 aa;        // at 0x10
    f32 ab;        // at 0x14
    f32 ac;        // at 0x18
    f32 ka;        // at 0x1C
    f32 kb;        // at 0x20
    f32 kc;        // at 0x24
    Vec pos;       // at 0x28
    Vec dir;       // at 0x34
} GXLightObj;

void GXInitLightAttn(GXLightObj *lobj, f32, f32, f32, f32, f32, f32);
void GXInitLightAttnA(GXLightObj *lobj, f32, f32, f32);
void GXInitLightAttnK(GXLightObj *lobj, f32, f32, f32);
void GXInitLightSpot(GXLightObj *lobj, f32, GXSpotFn);
void GXInitLightDistAttn(GXLightObj *lobj, f32, f32, GXDistAttnFn);
void GXInitLightPos(GXLightObj *lobj, f32, f32, f32);
void GXGetLightPos(const GXLightObj *lobj, f32 *, f32 *, f32 *);
void GXInitLightDir(GXLightObj *lobj, f32, f32, f32);
void GXGetLightDir(const GXLightObj *lobj, f32 *, f32 *, f32 *);
void GXInitSpecularDir(GXLightObj *lobj, f32, f32, f32);
void GXInitLightColor(GXLightObj *lobj, GXColor *color);
void GXLoadLightObjImm(GXLightObj *lobj, u32);
void GXLoadLightObjIndx(u32, u32);
void GXSetChanAmbColor(GXChannelID chan_id, GXColor *color);
void GXSetChanMatColor(GXChannelID chan_id, GXColor *color);
void GXSetNumChans(u8);
void GXSetChanCtrl(GXChannelID chan_id, u8, GXColorSrc, GXColorSrc color_src, GXLightID light_id, GXDiffuseFn, GXAttnFn);

#endif