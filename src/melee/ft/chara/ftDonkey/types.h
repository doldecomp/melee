#ifndef MELEE_FT_CHARA_FTDONKEY_TYPES_H
#define MELEE_FT_CHARA_FTDONKEY_TYPES_H

#include <platform.h>

struct ftDonkey_EntityVars {
    /* 0x222C */ s32 x222C;
    /* 0x2230 */ s32 x2230;
};

union ftDonkey_MotionVars {
    struct ftDonkey_SpecialNVars {
        s32 x0;
        s32 x4;
        s32 x8;
        s32 xC;
        s32 x10;
        s32 x14;
    } specialn;

    struct ftDonkey_SpecialLwVars {
        s32 x0;
    } speciallw;

    /// @todo Rename to correct state.
    struct ftDonkey_State5Vars {
        bool x0;
        s32 x4;
        f32 x8;
    } unk5;

    /// @todo Rename to correct state.
    struct ftDonkey_State7Vars {
        s32 x0;
        s32 x4;
        f32 x8;
    } unk7;

    /// @todo Rename to correct state.
    struct ftDonkey_State8Vars {
        s32 x0;
        f32 x4;
    } unk8;
};

#endif
