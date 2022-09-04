#pragma once

#include <melee/ft/ftcommon.h>
#include <melee/ft/ftwalkcommon.h>
#include <melee/lb/lbvector.h>

typedef struct _ftDonkeyAttributes {
    s32 action_state;
    s32 x4_action_state;

    //// used by ftdonkey_walk.c (maybe Cargo Hold) ////
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

void ftDonkey_800DF980(HSD_GObj* fighter_gobj);

s32 ftDonkey_800DFA98(HSD_GObj* fighter_gobj);

void ftDonkey_800DFAE4(HSD_GObj* fighter_gobj, f32);
void ftDonkey_800DFB54(HSD_GObj* fighter_gobj);

void ftDonkey_800E017C(HSD_GObj* fighter_gobj);
void ftDonkey_800E0294(HSD_GObj* fighter_gobj);
void ftDonkey_800E05E4(HSD_GObj* fighter_gobj);
void ftDonkey_800E07B0(HSD_GObj* fighter_gobj);

void ftDonkey_8010D774(HSD_GObj* fighter_gobj);

void ftDonkey_8010DB3C(HSD_GObj* fighter_gobj);
void ftDonkey_8010DE88(HSD_GObj* fighter_gobj);
void ftDonkey_8010DFF8(HSD_GObj* fighter_gobj);

void ftDonkey_8010E0CC(HSD_GObj* fighter_gobj);
void ftDonkey_8010E148(HSD_GObj* fighter_gobj);
void ftDonkey_8010E464(HSD_GObj* fighter_gobj);
void ftDonkey_8010E4EC(HSD_GObj* fighter_gobj);

void ftDonkey_DestroyAllEffects(HSD_GObj* fighter_gobj);
