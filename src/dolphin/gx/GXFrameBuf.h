#ifndef DOLPHIN_GX_GXFRAMEBUF_H
#define DOLPHIN_GX_GXFRAMEBUF_H

#include <platform.h>

#include <dolphin/gx/forward.h>

#include <dolphin/gx/GXEnum.h>
#include <dolphin/gx/types.h>

extern GXRenderModeObj GXPal528IntDf;
extern GXRenderModeObj GXMpal480IntDf;
extern GXRenderModeObj GXFrameBuf_804011E0;
extern GXRenderModeObj GXFrameBuf_804011A4;
extern GXRenderModeObj GXNtsc480IntDf;

void GXClearBoundingBox(void);
void GXCopyDisp(void*, GXBool);
void GXCopyTex(void*, GXBool);
void GXSetCopyFilter(GXBool, u8[12][2], GXBool, u8[7]);
void GXSetDispCopyDst(u16, u16);
void GXSetDispCopyFrame2Field(s32 arg0);
void GXSetDispCopyFrame2Field(s32 arg0);
void GXSetDispCopyGamma(s32 arg0);
void GXSetDispCopySrc(u16, u16, u16, u16);
u32 GXSetDispCopyYScale(f32);
void GXSetTexCopyDst(u16, u16, GXTexFmt, GXBool);
void GXSetTexCopySrc(u16, u16, u16, u16);
void GXSetCopyClamp(s32);
void GXSetCopyClear(GXColor, u32);

#endif
