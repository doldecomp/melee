#ifndef _GXINIT_H_
#define _GXINIT_H_

#include <platform.h>
#include <dolphin/gx/forward.h>

#include <dolphin/gx/types.h>

GXFifoObj* GXInit(GXFifoObj* fifo, u32 size);

void __GXDefaultTexRegionCallback(void);
unk_t __GXDefaultTlutRegionCallback(u32 arg0);

#endif
