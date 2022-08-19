#ifndef DOLPHIN_GX___GXFIFO_H
#define DOLPHIN_GX___GXFIFO_H

#include <dolphin/gx/__types.h>

/* 004D3EDC */ extern unk_t lbl_804D72FC;
/* 00338814 */ extern void __GXFifoInit();
/* 0033869C */ extern void GXSetGPFifo(GXFifoObj *fifo);
/* 0033858C */ extern void GXSetCPUFifo(GXFifoObj *fifo);
/* 003384A4 */ extern void GXInitFifoBase(GXFifoObj *fifo, void *base, u32 size);

#endif