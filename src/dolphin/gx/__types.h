#ifndef DOLPHIN_GX___TYPES_H
#define DOLPHIN_GX___TYPES_H

#include <dolphin/gx/GXEnum.h>
#include <dolphin/gx/types.h>
#include <dolphin/mtx/types.h>
#include <dolphin/os/OSContext.h>

#define GX_WRITE_U8(ub) WGPIPE.u8 = ((u8*) &ub);

#define GX_WRITE_U16(us) WGPIPE.u16 = (*(u16*) &us);

#define GX_WRITE_U32(ui) WGPIPE.u32 = (*(u32*) &ui);

#define GX_WRITE_F32(f) WGPIPE.f32 = (*(f32*) &f);

#define INSERT_FIELD(reg, value, nbits, shift)                                 \
    (reg) = ((u32) (reg) & ~(((1 << (nbits)) - 1) << (shift))) |               \
            ((u32) (value) << (shift));

// GXFifoObj private fields
typedef struct {
    void* base;      // at 0x00
    void* end;       // at 0x04
    u32 size;        // at 0x08
    u32 hiWaterMark; // at 0x0C
    u32 loWaterMark; // at 0x10
    void* readPtr;   // at 0x14
    void* writePtr;  // at 0x18
    s32 x1C;         // at 0x1C
    u8 x20_pad[4];   // at 0x20
} __GXFifoObj;

typedef void* (*GXTexRegionCallback)(void); // signature unknown

// https://github.com/kiwi515/open_rvl/blob/366b440e58f030aa0aacc9316d2717289d58fe16/include/GX/GXInit.h#L9-L41
typedef struct {
    union {
        u32 u32;
        u16 u16[2];
    } x0;                                               // at 0x000
    u16 x4;                                             // at 0x004
    u16 x6;                                             // at 0x006
    OSContext* x8;                                      // at 0x008
    u32 xC;                                             // at 0x00C
    u32 x10;                                            // at 0x010
    u32 x14;                                            // at 0x014
    u32 x18;                                            // at 0x018
    s32 x1C_data[(0x3C - 0x1C) / 4];                    // at 0x01C
    s32 x3C_data[(0x5C - 0x3C) / 4];                    // at 0x03C
    s32 x5C_data[(0x7C - 0x5C) / 4];                    // at 0x05C
    s32 x7C;                                            // at 0x07C
    s32 x80;                                            // at 0x080
    s32 x84;                                            // at 0x084
    u32 x88_data[4];                                    // at 0x088
    u32 x98_data[4];                                    // at 0x098
    u32 ambColors[2];                                   // at 0x0A8
    u32 matColors[2];                                   // at 0x0B0
    s32 xB8[GX_MAX_TEXCOORD];                           // at 0x0B8
    u8 xD8_pad[0xF8 - 0xD8];                            // at 0x0D8
    s32 xF8;                                            // at 0x0F8
    s32 xFC;                                            // at 0x0FC
    u32 x100_data[(0x130 - 0x100) / 4];                 // at 0x100
    u32 x130_data[(0x170 - 0x130) / 4];                 // at 0x130
    u32 x170_data[(0x1AC - 0x170) / 4];                 // at 0x170
    u8 x1AC_pad[0x1B0 - 0x1AC];                         // at 0x1AC
    GXTexRegionCallback callbacks[(0x1D0 - 0x1B0) / 4]; // at 0x1B0
    u32 x1D0[(0x204 - 0x1D0) / 4];                      // at 0x1D0
    u32 x204;                                           // at 0x204
    u8 x208_pad[0x2D0 - 0x208];                         // at 0x208
    struct {
        u32 unk[4];
    } x2D0[(0x410 - 0x2D0) / 16]; // at 0x2D0
    u32 x410, x414;
    u32 x418;                           // at 0x418
    GXBool x41C;                        // at 0x41C
    GXBool x41D;                        // at 0x41D
    u32 projection_type;                // at 0x420
    f32 projection_v[6];                // at 0x424
    f32 viewport_v[6];                  // at 0x43C
    u8 x454_pad[4];                     // at 0x454
    f32 x458;                           // at 0x458
    s32 x45C_data[0x20 / 4];            // at 0x45C
    s32 x47C_data[0x20 / 4];            // at 0x47C
    u32 x49C_data[(0x4EC - 0x49C) / 4]; // at 0x49C
    u8 x4EC;                            // at 0x4EC
    GXBool x4ED;                        // at 0x4ED
    u8 x4EE;                            // at 0x4EE
    u32 x4F0_flags;                     // at 0x4F0
    GXFifoObj* fifo;                    // at 0x4F4
    u8 x4F8_pad[0x570 - 0x4F8];         // at 0x4F8
    u32 dirtyFlags;                     // at 0x570
} GXContext;

typedef struct {
    u16 z_mode;
    u16 color_settings;
    u16 dst_alpha;
    u16 x6;
    u16 x8;
} GXSettings;

extern volatile u32* __piReg;
extern volatile u16* __peReg;
extern volatile u16* __cpReg;
extern volatile u32* __memReg;

extern volatile union {
    s8 s8;
    u8 u8;
    s16 s16;
    u16 u16;
    u32 u32;
    s32 s32;
    unk_t ptr;
    f32 f32;

} WGPIPE AT_ADDRESS(0xCC008000);

typedef struct {
    u16 x0;
    s16 x2;
    s16 x4;
    s16 x6;
    u8 x8_pad[0x38 - 0x8];
} __GXGPFifo;

typedef struct {
    GXContext* main;
    GXContext* null;
} GXContexts;

typedef struct _GXTexObj {
    u8 x0_pad[0x8];
    u32 dimensions;
    u8 xC_pad[0x8];
    GXTexFmt tex_fmt; // at 0x14
    u8 x18_pad[8];    // at 0x18
} GXTexObj;

#endif
