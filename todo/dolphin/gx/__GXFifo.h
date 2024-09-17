#ifndef DOLPHIN_GX___GXFIFO_H
#define DOLPHIN_GX___GXFIFO_H

#include <platform.h>

#include <dolphin/gx/forward.h>

#include <dolphin/gx/__types.h>

void __GXFifoInit(void);
void GXSetGPFifo(GXFifoObj* fifo);
void GXSetCPUFifo(GXFifoObj* fifo);
void GXInitFifoBase(GXFifoObj* fifo, void* base, u32 size);

#endif
