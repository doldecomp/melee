#include <dolphin/gx/GXInit.h>
#include <dolphin/base/PPCArch.h>
#include <dolphin/gx/gxprivate.h>
#include <dolphin/gx/GXFifo.h>
#include <dolphin/gx/GXMisc.h>
#include <dolphin/gx/GXAttr.h>
#include <dolphin/gx/GXLight.h>
#include <dolphin/vi/vi.h>

extern const GXData *__GXData;

extern void *__GXDefaultTexRegionCallback(GXTexRegionCallback); // signature unknown
extern GXFifoObj *GXInit(GXFifoObj *fifo, u32 size);

#pragma region __GXInitGX
extern const s32 lbl_804DE200, lbl_804DE204, lbl_804DE208;
extern const f32 lbl_804DE20C, lbl_804DE210, lbl_804DE214;

extern void __GXInitGX();
#pragma endregion

extern void lbl_8033A75C();
