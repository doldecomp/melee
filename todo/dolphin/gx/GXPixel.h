#ifndef DOLPHIN_GX_GXPIXEL_H
#define DOLPHIN_GX_GXPIXEL_H

#include <platform.h>

#include <dolphin/gx.h>
#include <dolphin/mtx.h>

typedef struct _GXFogAdjTbl {
    u16 r[10];
} GXFogAdjTbl;

void GXSetFieldMode(int, int);
void GXInitFogAdjTable(GXFogAdjTbl*, u16, Mtx44);
void GXSetFogRangeAdj(s8, u16, GXFogAdjTbl*);
void GXSetPixelFmt(int, int);
void GXSetFieldMask(s32, s8);
void GXSetDstAlpha(u8, u8);
void GXSetDither(u8);
void GXSetZCompLoc(u8);
void GXSetZMode(u8, u32, u32);
void GXSetAlphaUpdate(u8);
void GXSetColorUpdate(u8);
void GXSetBlendMode(s32, s32, s32, s32);
void GXSetFog(s32, GXColor, f32, f32, f32, f32);

#endif
