// https://github.com/kiwi515/open_rvl/blob/366b440e58f030aa0aacc9316d2717289d58fe16/include/GX/GXLight.h

#ifndef DOLPHIN_GX_GXLIGHT_H
#define DOLPHIN_GX_GXLIGHT_H

#include <dolphin/gx/__types.h>

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

/* 0033B188 */ extern void GXSetChanCtrl(GXChannelID, u8, GXColorSrc, GXColorSrc, GXLightID, GXDiffuseFn, GXAttnFn);
/* 0033B13C */ extern void GXSetNumChans(u8);
/* 0033AFD4 */ extern void GXSetChanMatColor(GXChannelID, GXColor *);
/* 0033AE6C */ extern void GXSetChanAmbColor(GXChannelID, GXColor *);
/* 0033AD24 */ extern void GXLoadLightObjImm(GXLightObj *, u32);
/* 0033ACFC */ extern void GXInitLightColor(GXLightObj *, GXColor *);
/* 0033ACE0 */ extern void GXInitLightDir(GXLightObj *, f32, f32, f32);
/* 0033ACD0 */ extern void GXInitLightPos(GXLightObj *, f32, f32, f32);
/* 0033AC00 */ extern void GXInitLightDistAttn(GXLightObj *, f32, f32, GXDistAttnFn);
/* 0033AA80 */ extern void GXInitLightSpot(GXLightObj *, f32, GXSpotFn);
/* 0033AA64 */ extern void GXInitLightAttn(GXLightObj *lobj, f32 aa, f32 ab, f32 ac, f32 ka, f32 kb, f32 kc);

#endif