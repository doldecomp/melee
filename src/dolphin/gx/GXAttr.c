#include <dolphin/gx/GXAttr.h>

/* 004D2798 */ extern u32 lbl_804D5BB8[2];
/* 004D2794 */ extern u32 lbl_804D5BB4[4];
/* 004D2790 */ extern u32 lbl_804D5BB0[4];
/* 00339758 */ void GXSetNumTexGens(s8);
/* 00339488 */ void GXSetTexCoordGen2(u32, s32, u32, s32, s32, s32);
/* 00339478 */ extern void GXInvalidateVtxCache();
/* 003393EC */ extern void GXSetArray(s32, s32, s8);
/* 00339350 */ extern void __GXSetVAT();
/* 00338FF4 */ extern void GXSetVtxAttrFmt(s8 vertex_format, s32, s32, s32, s8);
/* 00338FA8 */ extern void GXClearVtxDesc();
/* 00338E40 */ extern void __GXSetVCD();
/* 00338AE0 */ extern void GXSetVtxDesc(u32, s32);
/* 00338988 */ extern void __GXXfVtxSpecs();