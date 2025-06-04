#ifndef MELEE_FT_CHARA_FTGAMEWATCH_TYPES_H
#define MELEE_FT_CHARA_FTGAMEWATCH_TYPES_H

#include <platform.h>

#include "ftGameWatch/forward.h" // IWYU pragma: export
#include <baselib/forward.h>

#include "lb/types.h"

#include <common_structs.h>
#include <dolphin/gx.h>

struct ftGameWatch_FighterVars {
    /* 0x222C */ s32 x222C_judgeVar1;
    /* 0x2230 */ s32 x2230_judgeVar2;
    /* 0x2234 */ u32 x2234;
    /* 0x2238 */ s32 x2238_panicCharge;
    /* 0x223C */ s32 x223C_panicDamage;
    /* 0x2240 */ s32 x2240_chefVar1;
    /* 0x2244 */ s32 x2244_chefVar2;
    /* 0x2248 */ HSD_GObj* x2248_manholeGObj;
    /* 0x224C */ HSD_GObj* x224C_greenhouseGObj;
    /* 0x2250 */ HSD_GObj* x2250_manholeGObj2;
    /* 0x2254 */ HSD_GObj* x2254_fireGObj;
    /* 0x2258 */ HSD_GObj* x2258_parachuteGObj;
    /* 0x225C */ HSD_GObj* x225C_turtleGObj;
    /* 0x2260 */ HSD_GObj* x2260_sparkyGObj;
    /* 0x2264 */ HSD_GObj* x2264_judgementGObj;
    /* 0x2268 */ HSD_GObj* x2268_panicGObj;
    /* 0x226C */ HSD_GObj* x226C_rescueGObj;
};

typedef struct ftGameWatchChef {
    int sausageCount[6];
} ftGameWatchChef;

typedef struct ftGameWatchJudge {
    s32 rollVar[9];
} ftGameWatchJudge;

typedef struct _ftGameWatchAttributes {
    /// MISC. ATTRIBUTES

    /// Mr. Game & Watch's Z-Axis stretch; 0.01 by default
    float x0_GAMEWATCH_WIDTH;

    /// Array of four GXColor values, one for each Mr. Game & Watch costume
    /// color
    GXColor x4_GAMEWATCH_COLOR[4];

    /// Outline color of Mr. Game & Watch's model
    GXColor x14_GAMEWATCH_OUTLINE;

    /// NEUTRAL SPECIAL - CHEF

    /// Allow rapid-firing sausages from this frame onward
    float x18_GAMEWATCH_CHEF_LOOPFRAME;

    /// Maximum amount of sausages created per Chef use
    float x1C_GAMEWATCH_CHEF_MAX;

    /// SIDE SPECIAL - JUDGEMENT

    /// Horizontal momentum preservation value
    float x20_GAMEWATCH_JUDGE_MOMENTUM_PRESERVE;

    /// Multiplies momentum preservation value
    float x24_GAMEWATCH_JUDGE_MOMENTUM_MUL;
    float x28_GAMEWATCH_JUDGE_VEL_Y;
    float x2C_GAMEWATCH_JUDGE_FRICTION1;
    float x30_GAMEWATCH_JUDGE_FRICTION2;

    /// Array of BOOLs that toggle respective Judgement numbers ON/OFF. If a
    /// number is OFF, it is excluded from RNG rolls. Game panics if less than
    /// 2 numbers are ON.
    s32 x34_GAMEWATCH_JUDGE_ROLL[9];

    /// UP SPECIAL - FIRE RESCUE

    /// Minimum control stick range required for directional influence? Also
    /// affects how far Mr. Game & Watch flings horizontally (?)
    float x58_GAMEWATCH_RESCUE_STICK_RANGE;

    /// Radians -- controls how far Mr. Game & Watch can angle Fire Rescue?
    float x5C_GAMEWATCH_RESCUE_ANGLE_UNK;

    /// Landing lag / Freefall toggle
    float x60_GAMEWATCH_RESCUE_LANDING;

    /// DOWN SPECIAL - OIL PANIC

    /// Horizontal momentum preservation value
    float x64_GAMEWATCH_PANIC_MOMENTUM_PRESERVE;

    /// Multiplies momentum preservation value
    float x68_GAMEWATCH_PANIC_MOMENTUM_MUL;

    /// Falling acceleration
    float x6C_GAMEWATCH_PANIC_FALL_ACCEL;

    /// Terminal Y velocity?
    float x70_GAMEWATCH_PANIC_VEL_Y_MAX;

    /// Extra damage added to Oil Panic after formula
    float x74_GAMEWATCH_PANIC_DAMAGE_ADD;

    /// Damage multiplier
    float x78_GAMEWATCH_PANIC_DAMAGE_MUL;
    float x7C_GAMEWATCH_PANIC_TURN_FRAMES;

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
