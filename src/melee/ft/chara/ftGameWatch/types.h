#ifndef MELEE_FT_CHARA_FTGAMEWATCH_TYPES_H
#define MELEE_FT_CHARA_FTGAMEWATCH_TYPES_H

#include <platform.h>
#include <baselib/forward.h>

#include <common_structs.h>

typedef struct ftGameWatchChef {
    s32 sausageCount[5];
} ftGameWatchChef;

typedef struct ftGameWatchJudge {
    s32 rollVar[9];
} ftGameWatchJudge;

typedef struct _ftGameWatchAttributes {
    /// MISC. ATTRIBUTES

    /// Mr. Game & Watch's Z-Axis stretch; 0.01 by default
    f32 x0_GAMEWATCH_WIDTH;

    /// Array of four GXColor values, one for each Mr. Game & Watch costume
    /// color
    s32 x4_GAMEWATCH_COLOR[4];

    /// Outline color of Mr. Game & Watch's model
    s32 x14_GAMEWATCH_OUTLINE;

    /// NEUTRAL SPECIAL - CHEF

    /// Allow rapid-firing sausages from this frame onward
    f32 x18_GAMEWATCH_CHEF_LOOPFRAME;

    /// Maximum amount of sausages created per Chef use
    f32 x1C_GAMEWATCH_CHEF_MAX;

    /// SIDE SPECIAL - JUDGEMENT

    /// Horizontal momentum preservation value
    f32 x20_GAMEWATCH_JUDGE_MOMENTUM_PRESERVE;

    /// Multiplies momentum preservation value
    f32 x24_GAMEWATCH_JUDGE_MOMENTUM_MUL;
    f32 x28_GAMEWATCH_JUDGE_VEL_Y;
    f32 x2C_GAMEWATCH_JUDGE_FRICTION1;
    f32 x30_GAMEWATCH_JUDGE_FRICTION2;

    /// Array of BOOLs that toggle respective Judgement numbers ON/OFF. If a
    /// number is OFF, it is excluded from RNG rolls. Game panics if less than
    /// 2 numbers are ON.
    s32 x34_GAMEWATCH_JUDGE_ROLL[9];

    /// UP SPECIAL - FIRE RESCUE

    /// Minimum control stick range required for directional influence? Also
    /// affects how far Mr. Game & Watch flings horizontally (?)
    f32 x58_GAMEWATCH_RESCUE_STICK_RANGE;

    /// Radians -- controls how far Mr. Game & Watch can angle Fire Rescue?
    f32 x5C_GAMEWATCH_RESCUE_ANGLE_UNK;

    /// Landing lag / Freefall toggle
    f32 x60_GAMEWATCH_RESCUE_LANDING;

    /// DOWN SPECIAL - OIL PANIC

    /// Horizontal momentum preservation value
    f32 x64_GAMEWATCH_PANIC_MOMENTUM_PRESERVE;

    /// Multiplies momentum preservation value
    f32 x68_GAMEWATCH_PANIC_MOMENTUM_MUL;

    /// Falling acceleration
    f32 x6C_GAMEWATCH_PANIC_FALL_ACCEL;

    /// Terminal Y velocity?
    f32 x70_GAMEWATCH_PANIC_VEL_Y_MAX;

    /// Extra damage added to Oil Panic after formula
    f32 x74_GAMEWATCH_PANIC_DAMAGE_ADD;

    /// Damage multiplier
    f32 x78_GAMEWATCH_PANIC_DAMAGE_MUL;
    f32 x7C_GAMEWATCH_PANIC_TURN_FRAMES;

    /// Oil Panic absorption attributes
    AbsorbDesc x80_GAMEWATCH_PANIC_ABSORPTION;
} ftGameWatchAttributes;

typedef union ftGameWatch_MotionVars {
    struct ftGameWatch_Attack11Vars {
        /// 0x2340 - Set to 0 but never used?
        bool unk;
    } Attack11;

    struct ftGameWatch_SpecialNVars {
        /// 0x2340
        bool isChefLoopDisable;
        /// 0x2344 - Maximum number of sausages able to be spawned per Chef use
        s32 maxSausage;
    } SpecialN;

    struct ftGameWatch_SpecialLwVars {
        /// 0x2340 - bool to check if Mr. Game & Watch is no longer holding B
        bool isRelease;
        /// 0x2344 - Number of frames it takes Mr. Game & Watch to turn around
        /// on command
        s32 turnFrames;
    } SpecialLw;
} ftGameWatch_MotionVars;

#endif
