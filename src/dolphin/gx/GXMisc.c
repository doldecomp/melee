#include <dolphin/gx/__gx.h>
#include <dolphin/gx/GXMisc.h>
#include <dolphin/os/OSInterrupt.h>
#include <dolphin/os/OSThread.h>
#include <dolphin/base/PPCArch.h>

/* 004D3F0C */ extern u8 lbl_804D732C[0xC];
/* 004D3F08 */ extern u8 lbl_804D7328[0x4];
/* 004D3F04 */ extern unk_t lbl_804D7324;
/* 004D3F00 */ extern unk_t lbl_804D7320;
/* 0033E0F0 */ extern void GXSetCurrentMtx(s32);
/* 00339BB0 */ extern void __GXPEInit();
/* 00339A38 */ extern void GXPokeZMode(GXColor *, GXColor *, u32);
/* 00339A1C */ extern void GXPokeDither(GXColor *);
/* 00339A08 */ extern void GXPokeDstAlpha(GXColor *, GXColor *);
/* 003399EC */ extern void GXPokeColorUpdate(GXColor *);
/* 00339964 */ extern void GXPokeBlendMode(GXColor *, GXColor *, GXColor *, GXColor *);
/* 00339948 */ extern void GXPokeAlphaUpdate(GXColor *);
/* 00339934 */ extern void GXPokeAlphaRead(GXColor *);
/* 00339920 */ extern void GXPokeAlphaMode(GXColor *, s8);
/* 003398FC */ extern void GXPixModeSync();
/* 003398B0 */ extern void GXWaitDrawDone();
/* 00339818 */ extern void GXSetDrawDone();
/* 003397A0 */ extern void GXSetMisc(s32, s32);