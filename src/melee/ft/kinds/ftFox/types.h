/**
 * @file types.h
 * @brief Type definitions and structures for Fox
 * @details Defines fighter state variables, motion variables for each special
 * move (Blaster, Fox Illusion, Fire Fox, Reflector, Smash Taunt), and Fox's
 * character attributes. Module prefix: ftFx
 */

#ifndef MELEE_FT_CHARA_FTFOX_TYPES_H
#define MELEE_FT_CHARA_FTFOX_TYPES_H

#include <Runtime/platform.h>

#include <melee/ft/kinds/ftFox/forward.h> // IWYU pragma: export
#include <melee/it/forward.h>
#include <sysdolphin/baselib/forward.h>

#include <dolphin/mtx.h>
#include <melee/lb/types.h>

/**
 * @brief Persistent character-specific variables stored in Fighter struct
 * (0x222C)
 */
struct ftFox_FighterVars {
    /* 0x222C */ HSD_GObj*
        x222C_blasterGObj; ///< Pointer to spawned Blaster item GObj
};

/**
 * @brief Motion variables for Neutral-B (Blaster)
 */
typedef struct ftFoxSpecialN {
    /// 0x2340 - Flag set to allow continuous repeated blaster shots without
    /// holstering
    bool isBlasterLoop;
} ftFoxSpecialN;

/**
 * @brief Motion variables for Side-B (Fox Illusion / Falco Phantasm)
 */
typedef struct ftFoxSpecialS {
    /// 0x2340 - Number of frames to pass before gravity takes effect
    s32 gravityDelay;
    /// 0x2344 through 0x2370 - Ring buffer of 4 previous positions for
    /// illusion ghost trails
    Vec3 ghostEffectPos[4];
    /// 0x2374 through 0x2380 - Ring buffer of 4 previous X rotations for ghost
    /// models
    float blendFrames[4];
    /// 0x2384 - Pointer to spawned Illusion/Phantasm ghost GObj
    HSD_GObj* ghostGObj;
} ftFoxSpecialS;

/**
 * @brief Motion variables for Up-B (Fire Fox / Falco Firebird)
 */
typedef struct ftFoxSpecialHi {
    /// 0x2340 - Number of frames to pass before gravity takes effect during
    /// charge
    s32 gravityDelay;
    /// 0x2344 - Launch angle in radians used to rotate Fox's model bone
    float rotateModel;
    /// 0x2348 - Countdown of remaining travel frames during launch (typically
    /// 42)
    s32 travelFrames;
    /// 0x234C - Elapsed frames counter in launch state (triggers deceleration)
    s32 unk;
    /// 0x2350 - Bounce elapsed counter in launch state
    s32 unk2;
} ftFoxSpecialHi;

/**
 * @brief Motion variables for Down-B (Reflector / Shine)
 */
typedef struct ftFoxSpecialLw {
    /// 0x2340 - Auto lag frames after initializing Reflector if B is not held.
    /// Reflector is immediately released with no lag once these frames pass.
    s32 releaseLag;
    /// 0x2344 - Remaining turnaround frames when changing facing direction (3
    /// frames)
    s32 turnFrames;
    /// 0x2348 - Flag indicating B button has been released
    bool isRelease;
    /// 0x234C - Number of frames to pass before gravity takes effect
    s32 gravityDelay;
} ftFoxSpecialLw;

/**
 * @brief Motion variables for Star Fox Smash Taunt (Corneria / Venom comms)
 */
typedef struct ftFoxAppealS {
    /// 0x2340 - Fox/Falco's facing direction (0 = right, 1 = left) for ASID
    /// lookup
    bool facingDir;
    /// 0x2344 - Incremented every time one of the three stages (Start, Loop,
    /// End) finishes
    s32 animCount;
} ftFoxAppealS;

/**
 * @brief Union of all motion-specific variables for Fox
 */
typedef union ftFox_MotionVars {
    ftFoxSpecialN SpecialN;   ///< Neutral-B (Blaster)
    ftFoxSpecialS SpecialS;   ///< Side-B (Fox Illusion)
    ftFoxSpecialHi SpecialHi; ///< Up-B (Fire Fox)
    ftFoxSpecialLw SpecialLw; ///< Down-B (Reflector)
    ftFoxAppealS AppealS;     ///< Smash Taunt
} ftFox_MotionVars;

/**
 * @brief Character attributes table loaded from character DAT (PlFx.dat)
 */
struct ftFox_DatAttrs {
    // NEUTRAL SPECIAL - BLASTER

    float x0_FOX_BLASTER_UNK1;
    float x4_FOX_BLASTER_UNK2;
    float x8_FOX_BLASTER_UNK3;
    float xC_FOX_BLASTER_UNK4;
    /// Angle in radians at which Blaster shots are fired
    float x10_FOX_BLASTER_ANGLE;
    /// Velocity at which Blaster shots are fired
    float x14_FOX_BLASTER_VEL;
    /// Landing lag frames when landing with Blaster (0 for Fox = normal fall)
    float x18_FOX_BLASTER_LANDING_LAG;
    /// Item kind for Blaster projectile shot
    ItemKind x1C_FOX_BLASTER_SHOT_ITKIND;
    /// Item kind for Blaster gun model
    ItemKind x20_FOX_BLASTER_GUN_ITKIND;

    // SIDE SPECIAL - FOX ILLUSION / FALCO PHANTASM

    /// Frames required to pass before gravity is applied
    float x24_FOX_ILLUSION_GRAVITY_DELAY;
    /// Horizontal ground velocity divisor
    float x28_FOX_ILLUSION_GROUND_VEL_X;
    float x2C_FOX_ILLUSION_UNK1;
    float x30_FOX_ILLUSION_UNK2;
    /// Ground velocity on dash completion
    float x34_FOX_ILLUSION_GROUND_END_VEL_X;
    /// Ground friction applied during end lag
    float x38_FOX_ILLUSION_GROUND_FRICTION;
    /// Air velocity on dash completion
    float x3C_FOX_ILLUSION_AIR_END_VEL_X;
    /// Air deceleration multiplier
    float x40_FOX_ILLUSION_AIR_MUL_X;
    /// Gravity / fall acceleration during end lag
    float x44_FOX_ILLUSION_FALL_ACCEL;
    /// Terminal fall velocity during end lag
    float x48_FOX_ILLUSION_TERMINAL_VELOCITY;
    /// Horizontal air drift mobility in freefall
    float x4C_FOX_ILLUSION_FREEFALL_MOBILITY;
    /// Landing lag frames if landing in freefall (20 frames)
    float x50_FOX_ILLUSION_LANDING_LAG;

    // UP SPECIAL - FIREFOX / FIREBIRD

    /// Frames before gravity is applied during charge phase
    float x54_FOX_FIREFOX_GRAVITY_DELAY;
    /// Initial horizontal velocity divisor
    float x58_FOX_FIREFOX_VEL_X;
    /// Air momentum preservation multiplier during charge
    float x5C_FOX_FIREFOX_AIR_MOMENTUM_PRESERVE_X;
    /// Fall acceleration during charge
    float x60_FOX_FIREFOX_FALL_ACCEL;
    /// Minimum control stick range required for direction angle change
    float x64_FOX_FIREFOX_DIRECTION_STICK_RANGE_MIN;
    /// Amount of frames Firefox travels (typically ~42 frames)
    float x68_FOX_FIREFOX_DURATION;
    /// Bounce variable threshold
    s32 x6C_FOX_FIREFOX_BOUNCE_VAR;
    /// Frame threshold after which deceleration begins
    float x70_FOX_FIREFOX_DURATION_END;
    /// Launch travel speed
    float x74_FOX_FIREFOX_SPEED;
    /// Reverse acceleration applied near end of launch
    float x78_FOX_FIREFOX_REVERSE_ACCEL;
    /// Ground deceleration at end of launch
    float x7C_FOX_FIREFOX_GROUND_MOMENTUM_END;
    float x80_FOX_FIREFOX_UNK2;
    /// Horizontal velocity multiplier on wall/ceiling bounce (SpecialHiBound)
    float x84_FOX_FIREFOX_BOUND_VEL_X;
    /// Minimum control stick range required to change facing direction
    float x88_FOX_FIREFOX_FACING_STICK_RANGE_MIN;
    /// Horizontal air drift mobility during freefall
    float x8C_FOX_FIREFOX_FREEFALL_MOBILITY;
    /// Landing lag frames if landing during/after Fire Fox (26 frames)
    float x90_FOX_FIREFOX_LANDING_LAG;
    /// Maximum incidence angle offset for wall/ceiling bounce
    float x94_FOX_FIREFOX_BOUND_ANGLE;

    // DOWN SPECIAL - REFLECTOR

    /**
     * Auto lag frames after initializing Reflector if B is not being held.
     * Reflector is immediately released with no lag once these frames have
     * passed.
     */
    float x98_FOX_REFLECTOR_RELEASE_LAG;
    /// Amount of turn frames for changing Reflector facing direction (3
    /// frames)
    float x9C_FOX_REFLECTOR_TURN_FRAMES;
    float xA0_FOX_REFLECTOR_UNK1;
    /// Frames before gravity takes effect (shine stalling)
    s32 xA4_FOX_REFLECTOR_GRAVITY_DELAY;
    /// Horizontal momentum divisor on aerial shine activation
    float xA8_FOX_REFLECTOR_MOMENTUM_PRESERVE_X;
    /// Fall acceleration in reflector
    float xAC_FOX_REFLECTOR_FALL_ACCEL;
    /// Reflector hitbox parameters (damage multiplier, speed multiplier, etc.)
    ReflectDesc xB0_FOX_REFLECTOR_REFLECTION;
};

#endif
