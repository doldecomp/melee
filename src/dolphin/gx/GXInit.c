#include <dolphin/gx/GXInit.h>
#include <dolphin/base/PPCArch.h>
#include <dolphin/gx/__gx.h>
#include <dolphin/gx/GXFifo.h>
#include <dolphin/gx/GXMisc.h>
#include <dolphin/gx/GXAttr.h>
#include <dolphin/gx/GXLight.h>
#include <dolphin/vi/vi.h>

/* 004DADF4 */ extern const f32 lbl_804DE214;
/* 004DADF0 */ extern const f32 lbl_804DE210;
/* 004DADEC */ extern const f32 lbl_804DE20C;
/* 004DADE8 */ extern const s32 lbl_804DE208;
/* 004DADE4 */ extern const s32 lbl_804DE204;
/* 004DADE0 */ extern const s32 lbl_804DE200;
/* 004D2788 */ extern GXContexts __GXContexts;
/* 004A42A8 */ extern const GXContext *__GXContext;
/* 00337B20 */ extern void __GXInitGX();
/* 00337360 */ extern GXFifoObj *GXInit(GXFifoObj *fifo, u32 size);
/* 0033733C */ extern void lbl_8033A75C();
/* 003372C0 */ extern void *__GXDefaultTexRegionCallback(GXTexRegionCallback);
