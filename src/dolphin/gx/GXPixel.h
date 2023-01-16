#ifndef DOLPHIN_GX_GXPIXEL_H
#define DOLPHIN_GX_GXPIXEL_H

#include <dolphin/mtx/types.h>
#include <Runtime/platform.h>

typedef struct _GXFogAdjTbl {
    u16 r[10];
} GXFogAdjTbl;

void GXSetFieldMode(int, int);
void GXInitFogAdjTable(GXFogAdjTbl*, u16, Mtx44);
void GXSetFogRangeAdj(s8, u16, GXFogAdjTbl*);
void GXSetPixelFmt(int, int);

#endif
