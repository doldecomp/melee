#include <dolphin/gx/GXInit.h>
#include <dolphin/base/PPCArch.h>
#include <dolphin/gx/gxprivate.h>
#include <dolphin/gx/GXFifo.h>
#include <dolphin/gx/GXMisc.h>
#include <dolphin/gx/GXAttr.h>
#include <dolphin/gx/GXLight.h>
#include <dolphin/vi/vi.h>

#pragma region variables
extern GXData *const __GXData;
#pragma endregion

extern void *__GXDefaultTexRegionCallback(GXTexRegionCallback); // signature unknown
extern GXFifoObj *GXInit(GXFifoObj *fifo, u32 size);
extern void __GXInitGX();
extern void lbl_8033A75C();
