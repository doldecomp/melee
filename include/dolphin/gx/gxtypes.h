#ifndef _GXTYPES_h_
#define _GXTYPES_h_

#include "dolphin/types.h"

#define GX_FIFO_OBJSIZE		128

typedef enum _GXTexMtx
{
    GX_TEXMTX0  = 30,
    GX_TEXMTX1  = 33,
    GX_TEXMTX2  = 36,
    GX_TEXMTX3  = 39,
    GX_TEXMTX4  = 42,
    GX_TEXMTX5  = 45,
    GX_TEXMTX6  = 48,
    GX_TEXMTX7  = 51,
    GX_TEXMTX8  = 54,
    GX_TEXMTX9  = 57,
    GX_IDENTITY = 60
} GXTexMtx;

typedef enum _GXTexMapID
{
    GX_TEXMAP0,
    GX_TEXMAP1,
    GX_TEXMAP2,
    GX_TEXMAP3,
    GX_TEXMAP4,
    GX_TEXMAP5,
    GX_TEXMAP6,
    GX_TEXMAP7,
    GX_MAX_TEXMAP,
    GX_TEXMAP_NULL = 0xff,
    GX_TEX_DISABLE = 0x100
} GXTexMapID;

typedef enum _GXPTTexMtx
{
    GX_PTTEXMTX0  = 64,
    GX_PTTEXMTX1  = 67,
    GX_PTTEXMTX2  = 70,
    GX_PTTEXMTX3  = 73,
    GX_PTTEXMTX4  = 76,
    GX_PTTEXMTX5  = 79,
    GX_PTTEXMTX6  = 82,
    GX_PTTEXMTX7  = 85,
    GX_PTTEXMTX8  = 88,
    GX_PTTEXMTX9  = 91,
    GX_PTTEXMTX10 = 94,
    GX_PTTEXMTX11 = 97,
    GX_PTTEXMTX12 = 100,
    GX_PTTEXMTX13 = 103,
    GX_PTTEXMTX14 = 106,
    GX_PTTEXMTX15 = 109,
    GX_PTTEXMTX16 = 112,
    GX_PTTEXMTX17 = 115,
    GX_PTTEXMTX18 = 118,
    GX_PTTEXMTX19 = 121,
    GX_PTIDENTITY = 125
} GXPTTexMtx;

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
	u32  xfbMode;
	u8  field_rendering;
	u8  aa;
	u8  sample_pattern[12][2];
	u8  vfilter[7];
} GXRenderModeObj;

typedef struct _GXLightObj
{
    u32 dummy[16];
} GXLightObj;

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

// GXPixelFormat
#define GX_PF_RGB8_Z24      0
#define GX_PF_RGBA6_Z24     1
#define GX_PF_RGB565_Z16    2
#define GX_PF_Z24           3
#define GX_PF_Y8            4
#define GX_PF_U8            5
#define GX_PF_V8            6
#define GX_PF_YUV420        7

// GXCompressedZFormat
#define GX_ZC_LINEAR        0
#define GX_ZC_NEAR          1
#define GX_ZC_MID           2
#define GX_ZC_FAR           3

//GXGamma
#define GX_GM_1_0           0
#define GX_GM_1_7           1
#define GX_GM_2_2           2

#define GX_MAX_Z24          0x00ffffff

#define MAX_GXLIGHT         9

#endif
