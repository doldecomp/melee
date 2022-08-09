#include <dolphin/gx/GXInit.h>
#include <dolphin/base/PPCArch.h>
#include <dolphin/gx/gxprivate.h>
#include <dolphin/gx/GXFifo.h>
#include <dolphin/gx/GXMisc.h>
#include <dolphin/gx/GXAttr.h>
#include <dolphin/gx/GXLight.h>
#include <dolphin/vi/vi.h>

extern const GXContext *__GXContext; // at 0x004A42A8
extern GXContexts __GXContexts;      // at 0x004D2788

extern void *__GXDefaultTexRegionCallback(GXTexRegionCallback); // at 0x003372C0
extern GXFifoObj *GXInit(GXFifoObj *fifo, u32 size);            // at 0x0033733C

#pragma region __GXInitGX
extern const s32 lbl_804DE200; // at 0x004DADE0
extern const s32 lbl_804DE204; // at 0x004DADE4
extern const s32 lbl_804DE208; // at 0x004DADE8
extern const f32 lbl_804DE20C; // at 0x004DADEC
extern const f32 lbl_804DE210; // at 0x004DADF0
extern const f32 lbl_804DE214; // at 0x004DADF4
extern void __GXInitGX();      // at 0x00337B20
#pragma endregion

extern void lbl_8033A75C(); // at 0x0033733C
