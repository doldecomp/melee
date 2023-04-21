#ifndef MELEE_FT_CHARA_FTDONKEY_TYPES_H
#define MELEE_FT_CHARA_FTDONKEY_TYPES_H

#include <platform.h>

struct ftDK_FighterVars {
    /* 0x222C */ s32 x222C;
    /* 0x2230 */ s32 x2230;
};

struct ftDonkey_FighterVars {
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

typedef struct _ftDonkeyAttributes {
    s32 motion_state;
    s32 x4_motion_state;

    //// used by ftDk_MS_342.c (maybe Cargo Hold) ////
    f32 x8;
    f32 xC;
    f32 x10;
    f32 x14;
    f32 x18;
    f32 x1C;
    /////////////////////////////////////////////////

    struct {
        f32 x20_TURN_SPEED;
        f32 x24_JUMP_STARTUP_LAG;
        f32 x28_LANDING_LAG;
    } cargo_hold;

    //// Giant Punch
    struct {
        s32 x2C_MAX_ARM_SWINGS;
        s32 x30_DAMAGE_PER_SWING;
        f32 x34_PUNCH_HORIZONTAL_VEL;
        f32 x38_LANDING_LAG;
    } SpecialN;

    //// Headbutt
    struct {
        f32 x3C_MIN_STICK_X_MOMENTUM;
        f32 x40_MOMENTUM_TRANSITION_MODIFIER;
        f32 x44_AERIAL_GRAVITY;
    } SpecialS;

    f32 x48_UNKNOWN;

    //// Spinning Kong
    struct {
        f32 x4C_AERIAL_VERTICAL_VELOCITY;
        f32 x50_AERIAL_GRAVITY;
        f32 x54_GROUNDED_HORIZONTAL_VELOCITY;
        f32 x58_AERIAL_HORIZONTAL_VELOCITY;
        f32 x5C_GROUNDED_MOBILITY;
        f32 x60_AERIAL_MOBILITY;
        f32 x64_LANDING_LAG;
    } SpecialHi;

    /// Hand Slap
    struct {
        f32 x68;
        f32 x6C;
        f32 x70;
    } SpecialLw;

} ftDonkeyAttributes;

#endif
