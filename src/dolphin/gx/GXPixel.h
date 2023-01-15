#ifndef DOLPHIN_GX_GXPIXEL_H
#define DOLPHIN_GX_GXPIXEL_H

#include <dolphin/mtx/types.h>
#include <Runtime/platform.h>

typedef struct _GXFogAdjTbl {
    u16 r[10];
} GXFogAdjTbl;

void GXSetFieldMode(s8, s32);
void GXInitFogAdjTable(struct _GXFogAdjTbl*, u16, Mtx44);
void GXSetFogRangeAdj(s8, u16, struct _GXFogAdjTbl*);

#endif
