// header for shared private declarations of unsplit GX files
// todo: move into split sections' GX_*.c
#ifndef DOLPHIN_GX_GX_UNKNOWN_001___GX_UNKNOWN_001_H
#define DOLPHIN_GX_GX_UNKNOWN_001___GX_UNKNOWN_001_H

#include <dolphin/types.h>

/* 004DAEEC */ extern const f32 lbl_804DE30C;
/* 004DAEE8 */ extern const f32 lbl_804DE308;
/* 004DAEE0 */ extern const f32 lbl_804DE300[2];
/* 004DAED8 */ extern const f32 lbl_804DE2F8[2];
/* 004DAED4 */ extern const f32 lbl_804DE2F4;
/* 004DAED0 */ extern const f32 lbl_804DE2F0;
/* 004DAEC8 */ extern const f32 lbl_804DE2E8[2];
/* 004DAEC0 */ extern const f32 lbl_804DE2E0[2];
/* 004DAEB8 */ extern const f32 lbl_804DE2D8[2];
/* 004DAEB0 */ extern const f32 lbl_804DE2D0[2];
/* 004DAEA8 */ extern const f32 lbl_804DE2C8[2];
/* 004DAEA0 */ extern const f32 lbl_804DE2C0[2];
/* 004DAE98 */ extern const f32 lbl_804DE2B8[2];
/* 004DAE90 */ extern const f32 lbl_804DE2B0[2];
/* 004DAE88 */ extern const f32 lbl_804DE2A8[2];
/* 004DAE80 */ extern const f32 lbl_804DE2A0[2];
/* 004DAE7C */ extern const f32 lbl_804DE29C;
/* 004DAE78 */ extern const f32 lbl_804DE298;
/* 004DAE6C */ extern const f32 lbl_804DE28C;
/* 004DAE68 */ extern const f32 lbl_804DE288;
/* 004DAE64 */ extern const f32 lbl_804DE284;
/* 004DAE60 */ extern const f32 lbl_804DE280;
/* 004DAE5C */ extern const f32 lbl_804DE27C;
/* 004DAE58 */ extern const f32 lbl_804DE278;
/* 004DAE50 */ extern const f32 lbl_804DE270[2];
/* 004DAE48 */ extern const f32 lbl_804DE268[2];
/* 004DAE08 */ extern const f32 lbl_804DE228[2];
/* 004DAE00 */ extern const f32 lbl_804DE220[2];
/* 004D27D8 */ extern const u32 GX2HWFiltConv[2];
/* 004D27D0 */ extern const u32 GXTexTlutIds[2];
/* 004D27C8 */ extern const u32 GXTexImage3Ids[2];
/* 004D27C0 */ extern const u32 GXTexImage2Ids[2];
/* 004D27B8 */ extern const u32 GXTexImage1Ids[2];
/* 004D27B0 */ extern const u32 GXTexImage0Ids[2];
/* 004D27A8 */ extern const u32 GXTexMode1Ids[2];
/* 004D27A0 */ extern const u32 GXTexMode0Ids[2];
/* 003FE0E8 */ extern const u32 lbl_80401508[8];
/* 0033E050 */ extern void WriteMTXPS4x2(unk_t, s8 *);
/* 0033E01C */ extern void WriteMTXPS3x3from3x4(unk_t, s8 *, s8 *);
/* 0033DFE8 */ extern void WriteMTXPS4x3(unk_t, s8 *, s8 *);
/* 0033DCB4 */ extern void __GXSetRange(f32, f32);
/* 0033C8B4 */ extern void __GXUpdateBPMask();
/* 0033BF8C */ extern void __GXSetSUTexSize();
/* 0033BEC0 */ extern void __SetSURegs(s32, s32);
/* 0033BA08 */ extern void GXLoadTexObjPreLoaded(unk_t, unk_t, s32);
/* 0033B4C8 */ extern void __GetImageTileCount(u32, s16, s16, s32 *, s32 *, s32 *);

#endif
