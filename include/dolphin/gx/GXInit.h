#ifndef _GXINIT_H_
#define _GXINIT_H_

#include <dolphin/base/PPCArch.h>
#include <dolphin/gx/gxprivate.h>
#include <dolphin/gx/GXFifo.h>
#include <dolphin/gx/GXMisc.h>
#include <dolphin/gx/GXAttr.h>
#include <dolphin/vi/vi.h>

GXFifoObj *GXInit(GXFifoObj *fifo, u32 size);

#endif