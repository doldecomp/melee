#ifndef DOLPHIN_GX_GXFRAMEBUF_H
#define DOLPHIN_GX_GXFRAMEBUF_H

#include <Runtime/platform.h>

extern u32 GXPal528IntDf[16];
extern u32 GXMpal480IntDf[15];

unk_t GXClearBoundingBox(void);
void GXSetDispCopyFrame2Field(s32 arg0);
void GXSetTexCopySrc(s16, s32, u16, u16);
void GXSetTexCopyDst(s32, s32, s32, s32);

#endif
