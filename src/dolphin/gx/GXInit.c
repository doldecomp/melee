#include <dolphin/gx/GXInit.h>
#include <dolphin/base/PPCArch.h>
#include <dolphin/gx/gxprivate.h>
#include <dolphin/gx/GXFifo.h>
#include <dolphin/gx/GXMisc.h>
#include <dolphin/gx/GXAttr.h>
#include <dolphin/vi/vi.h>

#pragma region types
// this is probably not right
// see https://decomp.me/scratch/r2ALq
#define GX_INIT_OBJSIZE 0x3C
typedef union
{
    s32 s32[GX_INIT_OBJSIZE / 4];
    u32 u32[GX_INIT_OBJSIZE / 4];
    s16 s16[GX_INIT_OBJSIZE / 2];
    u16 u16[GX_INIT_OBJSIZE / 2];
    s8 s8[GX_INIT_OBJSIZE / 1];
    u8 u8[GX_INIT_OBJSIZE / 1];
    f32 f32[GX_INIT_OBJSIZE / 4];
} __GXInitObj;
#pragma endregion

#pragma region data
extern __GXInitObj lbl_80401168;
extern __GXInitObj lbl_8040121C;
extern __GXInitObj lbl_80401258;
extern __GXFifoLinkObj lbl_804A76C8;
#pragma endregion

extern void *__GXDefaultTexRegionCallback(GXTexRegionCallback); // signature unknown
extern GXFifoObj *GXInit(GXFifoObj *fifo, u32 size);
extern void __GXInitGX();
extern void lbl_8033A75C();
