/// @file
/// @todo Restructure this, possibly items/chara/types.h
#ifndef MELEE_IT_ITCHARITEMS_H
#define MELEE_IT_ITCHARITEMS_H

#include <dolphin/mtx/types.h>
#include <baselib/jobj.h>

typedef struct {
    float xDD4;
    float xDD8;
    float xDDC;
    Vec3 xDE0;
} FoxLaserVars;

typedef struct {
    HSD_Joint* xDD4;
    float xDD8;
    HSD_JObj* xDDC;
} FoxIllusionVars;

typedef struct {
    u32 x0;
} itKirbyHammerVars;

typedef struct {
    f32 x0;
    f32 x4;
    f32 x8;
    f32 xC;
    f32 x10;
    f32 x14;
    Vec3 x18;
    Vec3 x24;
    Vec3 x30;
    Vec3 x3C;
    Vec3 x48;
    Quaternion x54;
    Quaternion x64;
    Quaternion x74;
    Quaternion x84;
    f32 x94;
    f32 x98;
    u32 x9C;
    s32 xA0;
    u32 xA4;
    f32 xA8;
    f32 xAC;
    s32 xB0;
    HSD_JObj* xB4[3];
    f32 xC0;
    HSD_GObj* xC4;
    f32 xC8;
    f32 xCC;
    void* xD0;
    f32 xD4;
    f32 xD8;
    f32 xDC;
    HSD_GObj* xE0;
    s32 xE4;
    f32 xE8;
    f32 xEC;
    s32 xF0;
} itLinkArrowVars;

typedef struct {
    f32 x0;
    f32 x4;
    f32 x8;
    f32 xC;
    f32 x10;
    f32 x14;
    f32 x18;
    f32 x1C;
    f32 x20;
    HSD_Joint* x24;
    HSD_Joint* x28;
    f32 x2C;
} itLinkArrowAttributes;

#endif
