#ifndef MELEE_FT_CHARA_FTSAMUS_TYPES_H
#define MELEE_FT_CHARA_FTSAMUS_TYPES_H

#include <platform.h>
#include <placeholder.h>

#include "it/forward.h"
#include <baselib/forward.h>

#include "ftCommon/types.h"

#include <dolphin/mtx.h>

struct ftSamus_FighterVars {
    /* 0x222C */ Item_GObj* x222C;
    /* 0x2230 */ s32 x2230;
    /* 0x2234 */ u32 x2234;
    /* 0x2238 */ u32 x2238;
    /* 0x223C */ Item_GObj* x223C;

    /* 0x2240 */ u8 x2240;
    /* 0x2241 */ u8 x2241;
    /* 0x2242 */ u8 x2242;
    /* 0x2243 */ u8 x2243;

    /* 0x2244 */ u32 x2244;
    /* 0x2248 */ u32 x2248;
};

typedef struct _ftSamusAttributes {
    /*  +0 */ float x0;
    /*  +4 */ float x4;
    /*  +8 */ float x8;
    /*  +C */ float xC;
    /* +10 */ float x10;
    /* +14 */ float x14;
    /* +18 */ float x18;
    /* +1C */ float x1C;
    /* +20 */ int x20;
    /* +24 */ float x24;
    /* +28 */ float x28;
    /* +2C */ float x2C;
    /* +30 */ float x30;
    /* +34 */ float x34;
    /* +38 */ float x38;
    /* +3C */ float x3C;
    /* +40 */ float x40;
    /* +44 */ float x44;
    /* +48 */ float x48;
    /* +4C */ float x4C;
    /* +50 */ float x50;
    /* +54 */ float x54;
    /* +58 */ float x58;
    /* +5C */ float x5C;
    /* +60 */ float x60;
    /* +64 */ float x64;
    /* +68 */ float x68;
    /* +6C */ float x6C;
    /* +70 */ float x70;
    /* +74 */ Vec3 x74_vec;
    /* +80 */ float x80;
    /* +84 */ ftCollisionBox height_attributes;
    /* +9C */ UNK_T x9C;
    /* +A0 */ UNK_T xA0;
    /* +A4 */ UNK_T xA4;
    /* +A8 */ UNK_T xA8;
    /* +AC */ UNK_T xAC;
    /* +B0 */ UNK_T xB0;
    /* +B4 */ UNK_T xB4;
    /* +B8 */ UNK_T xB8;
    /* +BC */ int xBC;
    /* +C0 */ int xC0;
    /* +C4 */ int xC4;
    /* +C8 */ int xC8;
    /* +CC */ UNK_T xCC;
    /* +D0 */ UNK_T xD0;
} ftSs_DatAttrs;

/// maybe Samus grapple?
struct UNK_SAMUS_S1 {
    HSD_Joint* x0_joint;
    HSD_AnimJoint** x4_anim_joints;
    HSD_AnimJoint* x8_anim_joint;
    HSD_MatAnimJoint* xC_matanim_joint;
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
        float x8;
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
