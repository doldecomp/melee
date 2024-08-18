/// @file
/// @todo Restructure this, possibly items/chara/types.h
#ifndef MELEE_IT_ITCHARITEMS_H
#define MELEE_IT_ITCHARITEMS_H

#include "it/forward.h"

#include "lb/types.h"

#include <dolphin/mtx/types.h>
#include <baselib/jobj.h>

typedef struct {
    /* x0 */ s32 xDD4; // gets iterated from 0 to 14 in function (it_802AE200)
                       // that transforms the item model (possibly frame number
                       // of animation?)
    /* x4 */ s32 xDD8;
    /* x8 */ s32 xDDC;
    /* xC */ s32 xDE0;
    /* x10 */ s32
        xDE4; // group 1; gets set to 0 in func (it_802ADF10) that sets item
              // joint locations from corresponding fighter joint locations
    /* x14 */ s32 xDE8; // group 1
    /* x18 */ s32 xDEC; // group 1
    /* x1C */ s32 xDF0; // group 1
    /* x20 */ s32 xDF4; // group 1
    /* x24 */ s32 xDF8; // group 1
    /* x28 */ s32
        xDFC; // group 2; gets set to 0 in func (it_802ADF10) that sets item
              // joint locations from corresponding fighter joint locations
    /* x2C */ s32 xE00;    // group 2
    /* x30 */ s32 xE04;    // group 2
    /* x34 */ s32 xE08;    // group 2
    /* x38 */ s32 xE0C;    // group 2
    /* x3C */ s32 xE10;    // group 2
    /* x40 */ Vec3 xE14;   // group 3; gets set as the vector from fighter's
                           // current position to the joint holding the blaster
                           // on the frame blaster its shot
    /* x4C */ Vec3 xE20;   // group 3
    /* x58 */ Vec3 xE2C;   // group 3
    /* x64 */ Vec3 xE38;   // group 3
    /* x70 */ Vec3 xE44;   // group 3
    /* x7C */ Vec3 xE50;   // group 3
    /* x88 */ f32 angle_1; // xE5C group 4; gets set to an angle value in func
                           // (it_802ADF10) that sets item joint locations from
                           // corresponding fighter joint locations
    /* x8C */ f32 xE60;    // group 4
    /* x90 */ f32 xE64;    // group 4
    /* x94 */ f32 xE68;    // group 4
    /* x98 */ f32 xE6C;    // group 4
    /* x9C */ f32 xE70;    // group 4
    /* x100 */ s32 shoot_flag; // xE74 Matches with action script's shoot flag
                               // (fp->cmd_vars[2]) - 0: no shot this frame, 1:
                               // shoot this frame
    /* x104 */ s32
        visibility_flag; // xE78 Matches with action script's invisibility flag
                         // (fp->cmd_vars[1]) - 0: invisible, 1: visible, 2:
                         // frame of putting away
    /* x108 */ HSD_GObj* owner; // xE7C
} FoxBlasterVars;

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
    Item_GObj* x10;
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
    HSD_GObj* x4;
} itLinkBowVars;

#endif
