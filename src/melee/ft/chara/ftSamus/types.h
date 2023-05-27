#ifndef MELEE_FT_CHARA_FTSAMUS_TYPES_H
#define MELEE_FT_CHARA_FTSAMUS_TYPES_H

#include <platform.h>
#include "ft/forward.h"
#include "it/forward.h"
#include <baselib/forward.h>

#include "ftCommon/types.h"

#include <dolphin/mtx/types.h>

struct ftSamus_FighterVars {
    /* 0x222C */ Item_GObj* x222C;
    /* 0x2230 */ s32 x2230;
    /* 0x2234 */ u32 x2234;
    /* 0x2238 */ u32 x2238;
    /* 0x223C */ u32 x223C;

    /* 0x2240 */ u8 x2240;
    /* 0x2241 */ u8 x2241;
    /* 0x2242 */ u8 x2242;
    /* 0x2243 */ u8 x2243;

    /* 0x2244 */ u32 x2244;
    /* 0x2248 */ u32 x2248;
};

typedef struct _ftSamusAttributes {
    f32 x0;
    f32 x4;
    f32 x8;
    f32 xC;
    f32 x10;
    f32 x14;
    f32 x18;
    f32 x1C;
    s32 x20;
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
    f32 x64;
    f32 x68;
    f32 x6C;
    f32 x70;
    Vec3 x74_vec;
    f32 x80;
    ftCollisionBox height_attributes;
    u8 data_filler_4[0xD4 - 0x9C];
} ftSs_DatAttrs;

/// maybe Samus grapple?
struct UNK_SAMUS_S1 {
    HSD_Joint* x0_joint;
    HSD_AnimJoint** x4_anim_joints;
    HSD_AnimJoint* x8_anim_joint;
    HSD_MatAnimJoint* xC_matanim_joint;
};

struct UNK_SAMUS_S2 {
    S32Vec3 intvec;
    Vec3 vec1;
    Vec3 vec2;
    f32 single_float;
};

union ftSamus_MotionVars {
    /// @todo Proper state name.
    struct ftSamus_State2Vars {
        s32 x0;
    } unk2;

    /// @todo Proper state name.
    struct ftSamus_State3Vars {
        s32 x0;
        s32 x4;
        f32 x8;
    } unk3;

    /// @todo Proper state name.
    struct ftSamus_State5Vars {
        s32 x0;
    } unk5;

    /// @todo Proper state name.
    struct ftSamus_State6Vars {
        s32 x0;
    } unk6;
};

#endif
