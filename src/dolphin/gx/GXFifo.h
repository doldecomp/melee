#ifndef _GXFIFO_H_
#define _GXFIFO_H_

#include <dolphin/types.h>
#include <dolphin/gx/gxtypes.h>
#include <dolphin/os/OSThread.h>
#include <functions.h>

typedef struct
{
    s16 x0;
    s16 x2;
    s16 x4;
    s16 x6;
    u8 x8_pad[0x38 - 0x8];
} __GXGPFifo;

void GXCPInterruptHandler();
void GXSetCPUFifo(GXFifoObj *fifo);
void GXInitFifoLimits(void *, s32, s32);
void GXInitFifoBase(void *, void *, u32);
void __GXFifoLink(s8);
void GXSetGPFifo(__GXGPFifo *gp_fifo);
void __GXFifoReadEnable();
void __GXFifoReadDisable();
void __GXFifoInit();

// todo: private

// GXFifoObj private fields
typedef struct
{
    void *unk0;  // base
    void *unk4;  // end
    u32 unk8;    // size
    u32 unkC;    // hiWaterMark
    u32 unk10;   // loWaterMark
    void *unk14; // readPtr
    void *unk18; // writePtr
    s32 unk1C;
} __GXFifoObj;

// signature unknown
typedef void (*GXTexRegionCallback)(void);

typedef struct
{
    s16 x0;
    s16 x2;
    u16 x4;
    u16 x6;
    s32 x8;
    s32 xC;
    s32 x10;
    s32 x14;
    s32 x18;
    u8 x1C_pad[0x7C - 0x1C];
    s32 x7C;
    s32 x80;
    s32 x84;
    u8 x88_pad[0xB4 - 0x88];
    s32 xB4;
    s32 xB8;
    u8 xBC_pad[0xF8 - 0xBC];
    s32 xF8;
    s32 xFC;
    s32 x100_data[(0x130 - 0x100) / 4];
    s32 x130_data[(0x170 - 0x130) / 4];
    s32 x170_data[(0x1AC - 0x170) / 4];
    u8 x1AC_pad[0x1B0 - 0x1AC];
    GXTexRegionCallback x1B0_callbacks[(0x418 - 0x1B0) / 4];
    u8 x418_pad[0x41C - 0x418];
    s8 x41C;
    s8 x41D;
    u8 x41E_pad[0x43C - 0x41E];
    Vec x43C_vec;
    Vec x448_vec;
    u8 x454_pad[4];
    f32 x458;
    u8 x45C_pad[0x49C - 0x45C];
    u32 x49C_data[(0x4F0 - 0x49C) / 4];
    s32 x4F0;
    u8 x4F4_pad[0x578 - 0x4F4];
} __GXFifoLinkObj;

typedef struct
{
    __GXFifoLinkObj *fifo_link;
    u32 x8;
} __GXFifoLinkDataContainer;

typedef struct
{
    s16 x0;
    s16 x2;
    s16 x4;
    s16 x6;
    s16 x8;
} __GXFifoUnknown;

extern volatile u8 WGPIPE_OP
#ifndef M2C_CONTEXT
    : 0xCC010000
#endif
    ;

extern volatile union
{

    s8 s8;
    u8 u8;
    s16 s16;
    u16 u16;
    u32 u32;
    s32 s32;
    void* ptr;
    f32 f32;

} WGPIPE
#ifndef M2C_CONTEXT
    : 0xCC008000
#endif
    ;

extern __GXFifoLinkDataContainer lbl_804D5BA8;
extern __GXFifoLinkObj lbl_804A76C8;
extern __GXGPFifo *lbl_804D72F4;

extern void *lbl_804D7300;
extern void *lbl_804D7304;
extern u32 lbl_804D7308;
extern void *lbl_804D7310;
extern __GXFifoUnknown *lbl_804D72F8;
extern f32 lbl_804DE2F8;
extern f32 lbl_804DE308;
extern f32 lbl_804DE30C;

#endif