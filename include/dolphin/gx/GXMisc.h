#ifndef _GXMISC_H_
#define _GXMISC_H_

#include <dolphin/os/OSThread.h>

void GXSetCurrentMtx(s32);

/* 004D3F0C */ extern OSThreadQueue GXDrawDoneThreadQueue;
/* 004D3F08 */ extern u8 lbl_804D7328[0x4];
/* 004D3F04 */ extern unk_t lbl_804D7324;
/* 004D3F00 */ extern unk_t lbl_804D7320;
/* 0033E0F0 */ extern void GXSetCurrentMtx(s32);
/* 00339BB0 */ extern void __GXPEInit();
/* 003398FC */ extern void GXPixModeSync();
/* 003398B0 */ extern void GXWaitDrawDone();
/* 00339818 */ extern void GXSetDrawDone();
/* 003397A0 */ extern void GXSetMisc(s32, s32);

#endif