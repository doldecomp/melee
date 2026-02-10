#ifndef MELEE_FT_CHARA_FTDONKEY_TYPES_H
#define MELEE_FT_CHARA_FTDONKEY_TYPES_H

#include <platform.h>

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
        float x8;
    } unk5;

    /// @todo Rename to correct state.
    struct ftDonkey_State7Vars {
        s32 x0;
        s32 x4;
        float x8;
    } unk7;

    /// @todo Rename to correct state.
    struct ftDonkey_State8Vars {
        s32 x0;
        float x4;
    } unk8;
};

typedef struct _ftDonkeyAttributes {
    s32 motion_state;
    s32 x4_motion_state;

    //// used by ftDk_HeavyWalk.c (maybe Cargo Hold) ////
    float x8;
    float xC;
    float x10;
    float x14;
    float x18;
    float x1C;
    /////////////////////////////////////////////////

    struct {
        float x20_TURN_SPEED;
        float x24_JUMP_STARTUP_LAG;
        float x28_LANDING_LAG;
    } cargo_hold;

    //// Giant Punch
    struct {
        s32 x2C_MAX_ARM_SWINGS;
        s32 x30_DAMAGE_PER_SWING;
        float x34_PUNCH_HORIZONTAL_VEL;
        float x38_LANDING_LAG;
    } SpecialN;

    //// Headbutt
    struct {
        float x3C_MIN_STICK_X_MOMENTUM;
        float x40_MOMENTUM_TRANSITION_MODIFIER;
        float x44_AERIAL_GRAVITY;
    } SpecialS;

    float x48_UNKNOWN;

    //// Spinning Kong
    struct {
        float x4C_AERIAL_VERTICAL_VELOCITY;
        float x50_AERIAL_GRAVITY;
        float x54_GROUNDED_HORIZONTAL_VELOCITY;
        float x58_AERIAL_HORIZONTAL_VELOCITY;
        float x5C_GROUNDED_MOBILITY;
        float x60_AERIAL_MOBILITY;
        float x64_LANDING_LAG;
    } SpecialHi;

    /// Hand Slap
    struct {
        float x68;
        float x6C;
        float x70;
    } SpecialLw;

} ftDonkeyAttributes;

#endif
