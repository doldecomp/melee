#ifndef MELEE_FT_CHARA_FTSAMUS_TYPES_H
#define MELEE_FT_CHARA_FTSAMUS_TYPES_H

#include <platform.h>
#include <dolphin/mtx/types.h>
#include <baselib/forward.h>

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
    f32 height_attributes[6];
    u8 data_filler_4[0xD4 - 0x9C];
} ftSamusAttributes;

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

union ftSamus_StateVars {
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
