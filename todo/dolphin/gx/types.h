#ifndef DOLPHIN_GX_TYPES_H
#define DOLPHIN_GX_TYPES_H

#include <platform.h>

#include <dolphin/gx/forward.h>

#define GX_FIFO_OBJSIZE 128

struct GXFifoObj {
    u8 pad[GX_FIFO_OBJSIZE];
};

struct GXRenderModeObj {
    u32 viTVMode;
    u16 fbWidth;
    u16 efbHeight;
    u16 xfbHeight;
    u16 viXOrigin;
    u16 viYOrigin;
    u16 viWidth;
    u16 viHeight;
    u32 xfbMode;
    u8 field_rendering;
    u8 aa;
    u8 sample_pattern[12][2];
    u8 vfilter[7];
};

struct GXColor {
    u8 r, g, b, a;
};

struct GXColorS10 {
    s16 r, g, b, a;
};

#define GX_MAX_Z24 0x00ffffff

#endif
