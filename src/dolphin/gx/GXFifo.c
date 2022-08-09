#include <dolphin/gx/__gx.h>
#include <dolphin/os/OSThread.h>

/* 004D3EF8 */ extern s32 lbl_804D7318;
/* 004D3EF4 */ extern void (*lbl_804D7314)();
/* 004D3EF0 */ extern unk_t lbl_804D7310;
/* 004D3EE8 */ extern OSThread *lbl_804D7308;
/* 004D3EE4 */ extern unk_t lbl_804D7304;
/* 004D3EE0 */ extern unk_t lbl_804D7300;
/* 004D3EDC */ extern unk_t lbl_804D72FC;
/* 004D3ED8 */ extern __GXFifoUnknown *lbl_804D72F8;
/* 004D3ED4 */ extern __GXGPFifo *lbl_804D72F4;
/* 004D3ED0 */ extern unk_t lbl_804D72F0;
/* 0033893C */ extern void __GXWriteFifoIntReset(s8, s32);
/* 003388F0 */ extern void __GXWriteFifoIntEnable(s32, s32);
/* 003388AC */ extern void __GXFifoLink(s8);
/* 00338888 */ extern void __GXFifoReadDisable();
/* 00338860 */ extern void __GXFifoReadEnable();
/* 00338814 */ extern void __GXFifoInit();
/* 0033869C */ extern void GXSetGPFifo(__GXGPFifo *gp_fifo);
/* 0033858C */ extern void GXSetCPUFifo(GXFifoObj *fifo);
/* 00338580 */ extern void GXInitFifoLimits(unk_t, s32, s32);
/* 00338510 */ extern void GXInitFifoPtrs(unk_t, s32, s32);
/* 003384A4 */ extern void GXInitFifoBase(unk_t, unk_t, u32);
/* 00338368 */ extern void GXCPInterruptHandler(OSContext *);