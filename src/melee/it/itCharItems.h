/// @file
/// @todo Restructure this, possibly items/chara/types.h
#ifndef MELEE_IT_ITCHARITEMS_H
#define MELEE_IT_ITCHARITEMS_H

#include "lb/types.h"
#include "it/forward.h"
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

typedef struct ItemLink // user_data struct of GObj class 7
{
    struct ItemLink* prev;
    struct ItemLink* next;
    Vec3 x8_vel;
    Vec3 pos;
    Vec3 x20_vec; // Previous position?
    u8 flag0 : 1;
    u8 flag1 : 1;
    u8 flag2 : 1;
    u8 flag3 : 1;
    u8 flag4 : 1;
    u8 flag5 : 1;
    u8 flag6 : 1;
    u8 flag7 : 1;
    CollData x30_collData;
    s32 unk;
    HSD_GObj* x1D0_GObj;
    HSD_JObj* x1D4_JObj;

} ItemLink;

typedef struct {
    ItemLink* x0;
    ItemLink* x4;
    HSD_GObj* x8;
    HSD_JObj* xC;
    void (*x10)(Item_GObj*);
    u8 x14;
    f32 x18;
    f32 x1C;
    f32 x20;
    f32 x24;
    f32 x28;
    f32 x2C;
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

typedef struct {
    UnkFlagStruct x0;
    u8 x1;
    u8 x2;
    u8 x3;
    f32 x4;
    f32 x8;
    f32 xC;
    Item_GObj *x10;
} itLinkBombVars;

typedef struct itLinkBombAttributes {
    /* x0 */ u32 lifetime;
    /* x4 */ f32 x4;
    /* x8 */ f32 x8;
    /* xC */ u32 xC;
    /* x10 */ s32 x10;
    /* x14 */ f32 x14;
    /* x18 */ f32 x18;
    /* x1C */ f32 x1C;
    /* x20 */ f32 x20;
    /* x24 */ f32 x24;
    /* x28 */ f32 x28;
    /* x2C */ f32 x2C;
    /* x30 */ f32 x30;
    /* x28 */ f32 vel[3];
} itLinkBombAttributes;

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

typedef struct {
    f32 x0;
    HSD_GObj *x4;
} itLinkBowVars;

#endif
