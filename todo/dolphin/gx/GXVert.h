#ifndef _DOLPHIN_GXVERT_H_
#define _DOLPHIN_GXVERT_H_

#include <platform.h>

#include <dolphin/gx/__types.h>

static inline void GXPosition3f32(const f32 x, const f32 y, const f32 z)
{
    WGPIPE.f32 = x;
    WGPIPE.f32 = y;
    WGPIPE.f32 = z;
}

static inline void GXPosition3u16(const u16 x, const u16 y, const u16 z)
{
    WGPIPE.u16 = x;
    WGPIPE.u16 = y;
    WGPIPE.u16 = z;
}

static inline void GXPosition3s16(const s16 x, const s16 y, const s16 z)
{
    WGPIPE.s16 = x;
    WGPIPE.s16 = y;
    WGPIPE.s16 = z;
}

static inline void GXPosition3u8(const u8 x, const u8 y, const u8 z)
{
    WGPIPE.u8 = x;
    WGPIPE.u8 = y;
    WGPIPE.u8 = z;
}

static inline void GXPosition3s8(const s8 x, const s8 y, const s8 z)
{
    WGPIPE.s8 = x;
    WGPIPE.s8 = y;
    WGPIPE.s8 = z;
}

static inline void GXPosition2f32(const f32 x, const f32 y)
{
    WGPIPE.f32 = x;
    WGPIPE.f32 = y;
}

static inline void GXPosition2u16(const u16 x, const u16 y)
{
    WGPIPE.u16 = x;
    WGPIPE.u16 = y;
}

static inline void GXPosition2s16(const s16 x, const s16 y)
{
    WGPIPE.s16 = x;
    WGPIPE.s16 = y;
}

static inline void GXPosition2u8(const u8 x, const u8 y)
{
    WGPIPE.u8 = x;
    WGPIPE.u8 = y;
}

static inline void GXPosition2s8(const s8 x, const s8 y)
{
    WGPIPE.s8 = x;
    WGPIPE.s8 = y;
}

static inline void GXPosition1x8(const u8 index)
{
    WGPIPE.u8 = index;
}

static inline void GXPosition1x16(const u16 index)
{
    WGPIPE.u16 = index;
}

static inline void GXNormal3f32(const f32 nx, const f32 ny, const f32 nz)
{
    WGPIPE.f32 = nx;
    WGPIPE.f32 = ny;
    WGPIPE.f32 = nz;
}

static inline void GXNormal3s16(const s16 nx, const s16 ny, const s16 nz)
{
    WGPIPE.s16 = nx;
    WGPIPE.s16 = ny;
    WGPIPE.s16 = nz;
}

static inline void GXNormal3s8(const s8 nx, const s8 ny, const s8 nz)
{
    WGPIPE.s8 = nx;
    WGPIPE.s8 = ny;
    WGPIPE.s8 = nz;
}

static inline void GXNormal1x8(const u8 index)
{
    WGPIPE.u8 = index;
}

static inline void GXNormal1x16(const u16 index)
{
    WGPIPE.u16 = index;
}

static inline void GXColor4u8(const u8 r, const u8 g, const u8 b, const u8 a)
{
    WGPIPE.u8 = r;
    WGPIPE.u8 = g;
    WGPIPE.u8 = b;
    WGPIPE.u8 = a;
}

static inline void GXColor3u8(const u8 r, const u8 g, const u8 b)
{
    WGPIPE.u8 = r;
    WGPIPE.u8 = g;
    WGPIPE.u8 = b;
}

static inline void GXColor3f32(const f32 r, const f32 g, const f32 b)
{
    WGPIPE.u8 = (u8) (r * 255.0);
    WGPIPE.u8 = (u8) (g * 255.0);
    WGPIPE.u8 = (u8) (b * 255.0);
}

static inline void GXColor1u32(const u32 clr)
{
    WGPIPE.u32 = clr;
}

static inline void GXColor1u16(const u16 clr)
{
    WGPIPE.u16 = clr;
}

static inline void GXColor1x8(const u8 index)
{
    WGPIPE.u8 = index;
}

static inline void GXColor1x16(const u16 index)
{
    WGPIPE.u16 = index;
}

static inline void GXTexCoord2f32(const f32 s, const f32 t)
{
    WGPIPE.f32 = s;
    WGPIPE.f32 = t;
}

static inline void GXTexCoord2u16(const u16 s, const u16 t)
{
    WGPIPE.u16 = s;
    WGPIPE.u16 = t;
}

static inline void GXTexCoord2s16(const s16 s, const s16 t)
{
    WGPIPE.s16 = s;
    WGPIPE.s16 = t;
}

static inline void GXTexCoord2u8(const u8 s, const u8 t)
{
    WGPIPE.u8 = s;
    WGPIPE.u8 = t;
}

static inline void GXTexCoord2s8(const s8 s, const s8 t)
{
    WGPIPE.s8 = s;
    WGPIPE.s8 = t;
}

static inline void GXTexCoord1f32(const f32 s)
{
    WGPIPE.f32 = s;
}

static inline void GXTexCoord1u16(const u16 s)
{
    WGPIPE.u16 = s;
}

static inline void GXTexCoord1s16(const s16 s)
{
    WGPIPE.s16 = s;
}

static inline void GXTexCoord1u8(const u8 s)
{
    WGPIPE.u8 = s;
}

static inline void GXTexCoord1s8(const s8 s)
{
    WGPIPE.s8 = s;
}

static inline void GXTexCoord1x8(const u8 index)
{
    WGPIPE.u8 = index;
}

static inline void GXTexCoord1x16(const u16 index)
{
    WGPIPE.u16 = index;
}

static inline void GXMatrixIndex1u8(const u8 index)
{
    WGPIPE.u8 = index;
}

#endif
