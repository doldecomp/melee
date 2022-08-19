#ifndef DOLPHIN_GX_GXFIFO_GXFIFO_001_H
#define DOLPHIN_GX_GXFIFO_GXFIFO_001_H

#include <dolphin/gx/types.h>
#include <dolphin/os/OSThread.h>

/* 004D3EF8 */ extern s32 __GXOverflowCount;
/* 004D3EF4 */ extern void (*BreakPointCB)();
/* 004D3EF0 */ extern BOOL GXOverflowSuspendInProgress;
/* 004D3EEC */ extern unk_t lbl_804D730C;
/* 004D3EE8 */ extern OSThread *__GXCurrentThread;
/* 004D3EE4 */ extern unk_t lbl_804D7304;
/* 004D3EE0 */ extern unk_t lbl_804D7300;
/* 0033893C */ extern void __GXWriteFifoIntReset(s8, s32);
/* 003388F0 */ extern void __GXWriteFifoIntEnable(s32, s32);
/* 003388AC */ extern void __GXFifoLink(s8);
/* 00338888 */ extern void __GXFifoReadDisable();
/* 00338860 */ extern void __GXFifoReadEnable();
/* 00338580 */ extern void GXInitFifoLimits(unk_t, s32, s32);
/* 00338510 */ extern void GXInitFifoPtrs(GXFifoObj *fifo, void *readPtr, void *writePtr);

#endif