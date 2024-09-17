#ifndef DOLPHIN_MTX_TYPES_H
#define DOLPHIN_MTX_TYPES_H

#include <platform.h>

#include "dolphin/mtx/forward.h" // IWYU pragma: export

#include <dolphin/mtx.h>

struct Vec2 {
    f32 x, y;
};

struct Vec3 {
    f32 x, y, z;
};

struct Vec4 {
    f32 x, y, z, w;
};

struct U8Vec4 {
    u8 x, y, z, w;
};

struct S8Vec3 {
    s8 x, y, z;
};

struct S16Vec3 {
    s16 x, y, z;
};

struct S32Vec2 {
    s32 x, y;
};

struct S32Vec3 {
    s32 x, y, z;
};

struct IntVec2 {
    int x, y;
};

struct IntVec3 {
    int x, y, z;
};

#endif
