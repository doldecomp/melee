#ifndef _GXTYPES_h_
#define _GXTYPES_h_

#include "dolphin/types.h"

#define GX_FIFO_OBJSIZE		128

typedef struct {
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
	u32  xfbMode;
	u8  field_rendering;
	u8  aa;
	u8  sample_pattern[12][2];
	u8  vfilter[7];
} GXRenderModeObj;

typedef struct _GXColor {
    u8 r, g, b, a;
} GXColor;

typedef struct _GXColorS10 {
    s16 r, g, b, a;
} GXColorS10;

//GXBool
#define GX_FALSE            0
#define GX_TRUE             1
#define GX_DISABLE          0
#define GX_ENABLE           1

//GXAttr
#define GX_VA_PNMTXIDX      0
#define GX_VA_TEX0MTXIDX    1
#define GX_VA_TEX1MTXIDX    2
#define GX_VA_TEX2MTXIDX    3
#define GX_VA_TEX3MTXIDX    4
#define GX_VA_TEX4MTXIDX    5
#define GX_VA_TEX5MTXIDX    6
#define GX_VA_TEX6MTXIDX    7
#define GX_VA_TEX7MTXIDX    8
#define GX_VA_POS           9
#define GX_VA_NRM           10
#define GX_VA_CLR0          11
#define GX_VA_CLR1          12
#define GX_VA_TEX0          13
#define GX_VA_TEX1          14
#define GX_VA_TEX2          15
#define GX_VA_TEX3          16
#define GX_VA_TEX4          17
#define GX_VA_TEX5          18
#define GX_VA_TEX6          19
#define GX_VA_TEX7          20
#define GX_POS_MTX_ARRAY    21
#define GX_NRM_MTX_ARRAY    22
#define GX_TEX_MTX_ARRAY    23
#define GX_LIGHT_ARRAY      24
#define GX_VA_NBT           25
#define GX_VA_MAXATTR       26
#define GX_VA_NULL          0xff

//GXGamma
#define GX_GM_1_0           0
#define GX_GM_1_7           1
#define GX_GM_2_2           2

#define GX_MAX_Z24          0x00ffffff

#endif
