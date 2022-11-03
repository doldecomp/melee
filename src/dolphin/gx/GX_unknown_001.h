// public API of unsplit GX files
#ifndef DOLPHIN_GX_GX_UNKNOWN_001_H
#define DOLPHIN_GX_GX_UNKNOWN_001_H

#include <dolphin/gx/types.h>
#include <dolphin/mtx/types.h>

/* 003FDDC0 */ extern const GXRenderModeObj lbl_804011E0;
/* 003FDD84 */ extern const GXRenderModeObj lbl_804011A4;
/* 003FDD48 */ extern const GXRenderModeObj GXNtsc480IntDf;
/* 0033E33C */ extern void GXSetScissor(s32 left, s32 top, s32 width, s32 height);
/* 0033E12C */ extern void GXLoadTexMtxImm(unk_t, u32, s32);
/* 0033E0B0 */ extern void GXLoadNrmMtxImm(unk_t, s32);
/* 0033DCB8 */ extern void GXCallDisplayList(s32, s32);
/* 0033DC34 */ extern void GXSetFieldMode(s8, s32);
/* 0033DBA8 */ extern void GXSetDstAlpha(s32, s32);
/* 0033DB68 */ extern void GXSetDither(s32);
/* 0033DA58 */ extern void GXSetPixelFmt(s32, s32);
/* 0033D71C */ extern void GXSetFogRangeAdj(s8, u16, struct _GXFogAdjTbl*);
/* 0033D554 */ extern void GXInitFogAdjTable(struct _GXFogAdjTbl*, u16, Mtx44Ptr);
/* 0033D3A4 */ extern void GXSetFog(s32, GXColor, f32, f32, f32, f32);
/* 0033C86C */ extern void GXSetTevDirect();
/* 0033C840 */ extern void GXSetNumIndStages(s32);
/* 0033C708 */ extern void GXSetIndTexOrder(s32, s32, s32);
/* 0033C534 */ extern void GXSetIndTexCoordScale(s32, s32, s32);
/* 0033C3D4 */ extern void GXSetIndTexMtx(s32, unk_t, s32);
/* 0033BC4C */ extern void GXLoadTlut(unk_t, s32);
/* 0033BC04 */ extern void GXInitTlutObj(unk_t, u32, s32, u16);
/* 0033BBB0 */ extern void GXLoadTexObj(unk_t, s32);
/* 0033BA00 */ extern u8 GXGetTexObjFmt(unk_t);
/* 0033B9F0 */ extern u16 GXGetTexObjHeight(unk_t, f32);
/* 0033B9E0 */ extern u16 GXGetTexObjWidth(unk_t);
/* 0033B84C */ extern void GXInitTexObjLOD(unk_t, s32, s32, s32, s8, s32, f32, f32, f32);
/* 0033B804 */ extern void GXInitTexObjCI(unk_t, s32, u16, u16, s32, s32, s32, s8);
/* 0033B590 */ extern void GXInitTexObj(unk_t, u32, u16, u16, s32, s32, s32, s8);
/* 0033B36C */ extern s32 GXGetTexBufferSize(u16, u16, u32, u8, u8);
/* 0033A89C */ extern void GXCopyTex(u32, GXBool);
/* 0033A72C */ extern void GXCopyDisp(u32, s8);
/* 0033A710 */ extern void GXSetDispCopyGamma(s32);
/* 0033A4E8 */ extern void GXSetCopyFilter(s8, u8*, s8, u8*);
/* 0033A480 */ extern void GXSetCopyClear(u8*, s32);
/* 0033A3C4 */ extern u32 GXSetDispCopyYScale(f32);
/* 0033A348 */ extern void GXSetCopyClamp(s32);
/* 0033A1AC */ extern void GXSetTexCopyDst(s32, s32, s32, s32);
/* 0033A168 */ extern void GXSetDispCopyDst(s32);
/* 0033A0A8 */ extern void GXSetTexCopySrc(s16, s32, s16, s16);
/* 00339FE8 */ extern void GXSetDispCopySrc(s16, s32, s16, s16);

#endif
