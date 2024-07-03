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

typedef struct ItemLink ItemLink;

typedef struct {
    ItemLink* x0;
    ItemLink* x4;
    HSD_GObj* x8;
    f32 xC;
    void (*x10)(Item_GObj*);
    u8 x14;
    f32 x18;
    f32 x1C;
    f32 x20;
    f32 x24;
    f32 x28;
    u32 x2C;
    f32 x30;
    f32 x34;
    f32 x38;
    f32 x3C;
    f32 x40;
    f32 x44;
    f32 x48;
    f32 x4C;
    f32 x50;
    f32 x54;
    f32 x58;
    f32 x5C;
    f32 x60;
} itLinkHookshotVars;

typedef struct {
    f32 x0;
    f32 x4;
    f32 x8;
    s32 xC;
    f32 x10;
    f32 x14;
    f32 x18;
    f32 x1C;
    f32 x20;
    f32 x24;
    f32 x28;
    s32 x2C;
    f32 x30;
    f32 x34;
    f32 x38;
    f32 x3C;
    f32 x40;
    f32 x44;
    f32 x48;
    f32 x4C;
    f32 x50;
    HSD_Joint* x54;
    HSD_Joint* x58;
    HSD_Joint* x5C;
} itLinkHookshotAttributes;

#endif
