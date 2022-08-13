// todo: rework GX interdependencies
// this file should not be necessary

#ifndef DOLPHIN_GX___GX_H
#define DOLPHIN_GX___GX_H

#include <dolphin/gx/gxtypes.h>
#include <dolphin/mtx/mtxtypes.h>
#include <dolphin/os/OSContext.h>

// GXFifoObj private fields
typedef struct
{
    unk_t unk0;  // base
    unk_t unk4;  // end
    u32 unk8;    // size
    u32 unkC;    // hiWaterMark
    u32 unk10;   // loWaterMark
    unk_t unk14; // readPtr
    unk_t unk18; // writePtr
    s32 unk1C;
} __GXFifoObj;

typedef void (*GXTexRegionCallback)(void); // signature unknown

// https://github.com/kiwi515/open_rvl/blob/366b440e58f030aa0aacc9316d2717289d58fe16/include/GX/GXInit.h#L9-L41
typedef struct
{
    s16 x0;                                             // at 0x000
    s16 x2;                                             // at 0x002
    u16 x4;                                             // at 0x004
    u16 x6;                                             // at 0x006
    OSContext *x8;                                      // at 0x008
    u32 xC;                                             // at 0x00C
    s32 x10;                                            // at 0x010
    u32 x14;                                            // at 0x014
    u32 x18;                                            // at 0x018
    s32 x1C_data[(0x3C - 0x1C) / 4];                    // at 0x01C
    s32 x3C_data[(0x5C - 0x3C) / 4];                    // at 0x03C
    s32 x5C_data[(0x7C - 0x5C) / 4];                    // at 0x05C
    s32 x7C;                                            // at 0x07C
    s32 x80;                                            // at 0x080
    s32 x84;                                            // at 0x084
    u8 x88_data[0x10];                                  // at 0x088
    u8 x98_data[0x10];                                  // at 0x098
    GXColor ambColors[2];                               // at 0x0A8
    GXColor matColors[2];                               // at 0x0B0
    s32 xB4;                                            // at 0x0B4
    s32 xB8;                                            // at 0x0B8
    u8 xBC_pad[0xF8 - 0xBC];                            // at 0x0BC
    s32 xF8;                                            // at 0x0F8
    s32 xFC;                                            // at 0x0FC
    s32 x100_data[(0x130 - 0x100) / 4];                 // at 0x100
    s32 x130_data[(0x170 - 0x130) / 4];                 // at 0x130
    s32 x170_data[(0x1AC - 0x170) / 4];                 // at 0x170
    u8 x1AC_pad[0x1B0 - 0x1AC];                         // at 0x1AC
    GXTexRegionCallback callbacks[(0x418 - 0x1B0) / 4]; // at 0x1B0
    u8 x418[2];                                         // at 0x418
    s8 x41C;                                            // at 0x41C
    s8 x41D;                                            // at 0x41D
    u8 x41E_pad[0x43C - 0x41E];                         // at 0x41E
    Vec x43C_vec;                                       // at 0x43C
    Vec x448_vec;                                       // at 0x448
    u8 x454_pad[4];                                     // at 0x454
    f32 x458;                                           // at 0x458
    s32 x45C_data[0x20];                                // at 0x45C
    s32 x47C_data[0x20];                                // at 0x47C
    u32 x49C_data[(0x4E8 - 0x49C) / 4];                 // at 0x49C
    u8 x4EC_pad[2];                                     // at 0x4EC
    u8 x4EE;                                            // at 0x4EE
    s32 x4F0;                                           // at 0x4F0
    GXFifoObj *fifo;                                    // at 0x4F4
    u8 x4F8_pad[0x570 - 0x4F8];                         // at 0x4F8
    u32 dirtyFlags;                                     // at 0x570
} GXContext;

typedef struct
{
    s16 x0;
    s16 x2;
    s16 x4;
    s16 x6;
    s16 x8;
} __GXFifoUnknown;

typedef enum _GXChannelID
{
    GX_CHAN_RGB_0,
    GX_CHAN_RGB_1,
    GX_CHAN_ALPHA_0,
    GX_CHAN_ALPHA_1,
    GX_CHAN_RGBA_0,
    GX_CHAN_RGBA_1,
    GX_CHANNEL_ID_6,
    GX_CHANNEL_ID_7,
    GX_CHANNEL_ID_8,
    GX_CHANNEL_ID_INVALID = 0xFF
} GXChannelID;

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
    unk_t ptr;
    f32 f32;

} WGPIPE
#ifndef M2C_CONTEXT
    : 0xCC008000
#endif
    ;

typedef struct
{
    u16 x0;
    s16 x2;
    s16 x4;
    s16 x6;
    u8 x8_pad[0x38 - 0x8];
} __GXGPFifo;

typedef struct
{
    GXContext *main;
    GXContext *null;
} GXContexts;

#pragma region GXInit
extern GXContexts __GXContexts;
#pragma endregion

#pragma region GXFifo
extern unk_t lbl_804D72F0;
extern __GXGPFifo *lbl_804D72F4;
extern __GXFifoUnknown *lbl_804D72F8;
extern unk_t lbl_804D72FC;
void GXInitFifoBase(unk_t, unk_t, u32);
void GXSetCPUFifo(GXFifoObj *fifo);
void GXSetGPFifo(__GXGPFifo *gp_fifo);
void __GXFifoInit();
#pragma endregion

#pragma region GXAttr
void __GXSetVCD();
void __GXSetVAT();
#pragma endregion

#pragma region GXMisc
#pragma endregion

#pragma region GX
extern GXRenderModeObj lbl_80401168, lbl_8040121C, lbl_80401258;

void __GXSetDirtyState();
void func_8033D3A0(s32);
void func_8033D408(s16, s32, s16, s16);
void func_8033F108(unk_t, s8, u32, s32, u32, s32, s32);
void func_8033F228(s32 *, s32, s32);
void func_8033F518(s32);
void func_8033FDA0(GXContext *, s32, u8 *);
s32 func_80341878(s32);
void func_803418FC(u32, u32);

#pragma endregion
#endif