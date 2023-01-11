#ifndef DOLPHIN_GX_TYPES_H
#define DOLPHIN_GX_TYPES_H

#include <dolphin/gx/GXEnum.h>
#include <Runtime/platform.h>

#define GX_FIFO_OBJSIZE 128
typedef struct _GXFifoObj {
    u8 pad[GX_FIFO_OBJSIZE];
} GXFifoObj;

typedef struct _GXRenderModeObj {
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
} GXRenderModeObj;

typedef struct _GXColor {
    u8 r, g, b, a;
} GXColor;

typedef struct _GXColorS10 {
    s16 r, g, b, a;
} GXColorS10;

#define GX_MAX_Z24 0x00ffffff

#endif
