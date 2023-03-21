#ifndef DOLPHIN_GX_GXPIXEL_H
#define DOLPHIN_GX_GXPIXEL_H

#include <platform.h>
#include <dolphin/gx/forward.h>

#include <dolphin/mtx/types.h>

typedef struct _GXFogAdjTbl {
    u16 r[10];
} GXFogAdjTbl;

void GXSetFieldMode(int, int);
void GXInitFogAdjTable(GXFogAdjTbl*, u16, Mtx44);
void GXSetFogRangeAdj(s8, u16, GXFogAdjTbl*);
void GXSetPixelFmt(int, int);
void GXSetFieldMask(s32, s8);
void GXSetDstAlpha(s32, s32);
void GXSetDither(s32);
void GXSetZCompLoc(s32);
void GXSetZMode(s8, s32, s32);
void GXSetAlphaUpdate(s32);
void GXSetColorUpdate(s32);
void GXSetBlendMode(s32, s32, s32, s32);
void GXSetFog(s32, GXColor, f32, f32, f32, f32);

#endif
