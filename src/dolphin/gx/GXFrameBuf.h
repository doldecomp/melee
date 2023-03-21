#ifndef DOLPHIN_GX_GXFRAMEBUF_H
#define DOLPHIN_GX_GXFRAMEBUF_H

#include <dolphin/gx/forward.h>

#include <platform.h>

extern GXRenderModeObj GXPal528IntDf;
extern GXRenderModeObj GXMpal480IntDf;
extern GXRenderModeObj lbl_804011E0;
extern GXRenderModeObj lbl_804011A4;
extern GXRenderModeObj GXNtsc480IntDf;

void GXClearBoundingBox(void);
void GXCopyDisp(u32, s8);
void GXCopyTex(u32, GXBool);
void GXSetCopyFilter(s8, u8*, s8, u8*);
void GXSetDispCopyDst(s32 arg0);
void GXSetDispCopyFrame2Field(s32 arg0);
void GXSetDispCopyFrame2Field(s32 arg0);
void GXSetDispCopyGamma(s32 arg0);
void GXSetDispCopySrc(u16 arg0, u32 arg1, u16 arg2, u16 arg3);
u32 GXSetDispCopyYScale(f32);
void GXSetTexCopyDst(s32, s32, s32, s32);
void GXSetTexCopySrc(u16 arg0, u32 arg1, u16 arg2, u16 arg3);
void GXSetCopyClamp(s32);
void GXSetCopyClear(u8*, s32);

#endif
