// public API of unsplit GX files
#ifndef DOLPHIN_GX_GX_UNKNOWN_001_H
#define DOLPHIN_GX_GX_UNKNOWN_001_H

#include <dolphin/gx/types.h>
#include <dolphin/mtx/mtxtypes.h>

extern const GXRenderModeObj lbl_804011E0;
extern const GXRenderModeObj lbl_804011A4;
extern const GXRenderModeObj GXNtsc480IntDf;

void GXSetDstAlpha(s32, s32);
void GXSetDither(s32);
void GXSetPixelFmt(s32, s32);
void GXSetZCompLoc(s32);
void GXSetZMode(s8, s32, s32);
void GXSetAlphaUpdate(s32);
void GXSetColorUpdate(s32);
void GXSetBlendMode(s32, s32, s32, s32);
void GXSetFogRangeAdj(s8, u16, struct _GXFogAdjTbl*);
void GXInitFogAdjTable(struct _GXFogAdjTbl*, u16,
                       Mtx44Ptr);
void GXSetFog(s32, GXColor, f32, f32, f32, f32);
void GXSetTevColorS10(s32, GXColor*);
void GXSetTevDirect(void);
void GXSetNumIndStages(s32);
void GXSetIndTexOrder(s32, s32, s32);
void GXSetIndTexCoordScale(s32, s32, s32);
void GXSetIndTexMtx(s32, unk_t, s32);
void GXSetTevIndirect(s32, s32, u8, s32, s32, s32, s32,
                      s32);
void GXLoadTlut(unk_t, s32);
void GXInitTlutObj(unk_t, u32, s32, u16);
void GXLoadTexObj(unk_t, s32);
u8 GXGetTexObjFmt(unk_t);
u16 GXGetTexObjHeight(unk_t, f32);
u16 GXGetTexObjWidth(unk_t);
void GXInitTexObjLOD(unk_t, s32, s32, s32, s8, s32, f32,
                     f32, f32);
void GXInitTexObjCI(unk_t, s32, u16, u16, s32, s32, s32,
                    s8);
void GXInitTexObj(unk_t, u32, u16, u16, s32, s32, s32,
                  s8);
s32 GXGetTexBufferSize(u16, u16, u32, u8, u8);
void GXCopyTex(u32, GXBool);
void GXCopyDisp(u32, s8);
void GXSetDispCopyGamma(s32);
void GXSetCopyFilter(s8, u8*, s8, u8*);
void GXSetCopyClear(u8*, s32);
u32 GXSetDispCopyYScale(f32);
void GXSetCopyClamp(s32);
void GXSetTexCopyDst(s32, s32, s32, s32);
void GXSetDispCopyDst(s32);
void GXSetTexCopySrc(s16, s32, s16, s16);
void GXSetDispCopySrc(s16, s32, s16, s16);

#endif
