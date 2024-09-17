#ifndef MELEE_FT_CHARA_FTFOX_TYPES_H
#define MELEE_FT_CHARA_FTFOX_TYPES_H

#include <platform.h>

#include "ftFox/forward.h" // IWYU pragma: export
#include "it/forward.h"
#include <baselib/forward.h>

#include "lb/types.h"

#include <common_structs.h>
#include <dolphin/mtx.h>

struct ftFox_FighterVars {
    /* 0x222C */ HSD_GObj* x222C_blasterGObj;
};

typedef struct ftFoxSpecialN {
    /// 0x2340 - Check to allow repeated blaster shots
    bool isBlasterLoop;
} ftFoxSpecialN;

typedef struct ftFoxSpecialS {
    /// 0x2340 - Number of frames to pass before gravity takes effect
    s32 gravityDelay;
    /// 0x2344 through 0x2370 - Related to Illusion/Phantasm model's position?
    Vec3 ghostEffectPos[4];
    /// 0x2374 through 0x2380 - ColAnim blend frames?
    float blendFrames[4];
    /// 0x2384 - Illusion/Phantasm GObj pointer
    HSD_GObj* ghostGObj;
} ftFoxSpecialS;

typedef struct ftFoxSpecialHi {
    /// 0x2340 - Number of frames to pass before gravity takes effect
    s32 gravityDelay;
    /// 0x2344 - Used to rotate Fox/Falco's model?
    float rotateModel;
    /// 0x2348 - Number of frames Firefox/Firebird's launch animation lasts for
    s32 travelFrames;
    /// 0x234C - ???
    s32 unk;
    /// 0x2350 - ???
    s32 unk2;
} ftFoxSpecialHi;

typedef struct ftFoxSpecialLw {
    /// 0x2340 - Auto lag frames after initializing Reflector if B is not being
    /// held. Reflector is immediately released with no lag once these frames
    /// have passed
    s32 releaseLag;
    /// 0x2344 - Number of frames it takes Fox/Falco to turn around on command
    s32 turnFrames;
    /// 0x2348 - Check if Fox/Falco is no longer holding B
    bool isRelease;
    /// 0x234C - Number of frames to pass before gravity takes effect
    s32 gravityDelay;
} ftFoxSpecialLw;

typedef struct ftFoxAppealS {
    /// 0x2340 - Fox/Falco's facing direction as a boolean variable, used to
    /// load indexed ASIDs from the AppealS struct
    bool facingDir;
    /// 0x2344 - Incremented every time one of the three stages of the AppealS
    /// animation is completed
    s32 animCount;
} ftFoxAppealS;

typedef union ftFox_MotionVars {
    ftFoxSpecialN SpecialN;
    ftFoxSpecialS SpecialS;
    ftFoxSpecialHi SpecialHi;
    ftFoxSpecialLw SpecialLw;
    ftFoxAppealS AppealS;
} ftFox_MotionVars;

struct ftFox_DatAttrs {
    // NEUTRAL SPECIAL - BLASTER

    float x0_FOX_BLASTER_UNK1;
    float x4_FOX_BLASTER_UNK2;
    float x8_FOX_BLASTER_UNK3;
    float xC_FOX_BLASTER_UNK4;
    /// Angle at which Blaster shots are fired
    float x10_FOX_BLASTER_ANGLE;
    /// Velocity at which Blaster shots are fired
    float x14_FOX_BLASTER_VEL;
    float x18_FOX_BLASTER_LANDING_LAG;
    ItemKind x1C_FOX_BLASTER_SHOT_ITKIND;
    ItemKind x20_FOX_BLASTER_GUN_ITKIND;

    // SIDE SPECIAL - FOX ILLUSION / FALCO PHANTASM

    float x24_FOX_ILLUSION_GRAVITY_DELAY; // Frames required to pass before
                                          // gravity is applied
    float x28_FOX_ILLUSION_GROUND_VEL_X;  // Horizontal velocity?
    float x2C_FOX_ILLUSION_UNK1;
    float x30_FOX_ILLUSION_UNK2;
    float x34_FOX_ILLUSION_GROUND_END_VEL_X;
    float x38_FOX_ILLUSION_GROUND_FRICTION;
    float x3C_FOX_ILLUSION_AIR_END_VEL_X;
    float x40_FOX_ILLUSION_AIR_MUL_X;
    float x44_FOX_ILLUSION_FALL_ACCEL;
    float x48_FOX_ILLUSION_TERMINAL_VELOCITY;
    float x4C_FOX_ILLUSION_FREEFALL_MOBILITY;
    float x50_FOX_ILLUSION_LANDING_LAG;

    // UP SPECIAL - FIREFOX / FIREBIRD

    float x54_FOX_FIREFOX_GRAVITY_DELAY;
    float x58_FOX_FIREFOX_VEL_X; // Initial velocity
    float x5C_FOX_FIREFOX_AIR_MOMENTUM_PRESERVE_X;
    float x60_FOX_FIREFOX_FALL_ACCEL;
    float x64_FOX_FIREFOX_DIRECTION_STICK_RANGE_MIN; // Minimum control stick
                                                     // range required for
                                                     // direction change
    float
        x68_FOX_FIREFOX_DURATION; // Amount of frames Firefox/Firebird travels
    s32 x6C_FOX_FIREFOX_BOUNCE_VAR;
    float x70_FOX_FIREFOX_DURATION_END;
    float x74_FOX_FIREFOX_SPEED;
    float x78_FOX_FIREFOX_REVERSE_ACCEL; // ???
    float x7C_FOX_FIREFOX_GROUND_MOMENTUM_END;
    float x80_FOX_FIREFOX_UNK2;
    float x84_FOX_FIREFOX_BOUND_VEL_X; // Horizontal velocity of SpecialHiBound
                                       // action state
    float
        x88_FOX_FIREFOX_FACING_STICK_RANGE_MIN; // Minimum control stick range
                                                // required to change
                                                // character's facing direction
    float x8C_FOX_FIREFOX_FREEFALL_MOBILITY;
    float x90_FOX_FIREFOX_LANDING_LAG;
    float x94_FOX_FIREFOX_BOUND_ANGLE;

    // DOWN SPECIAL - REFLECTOR

    /**
     * Auto lag frames after initializing Reflector if B is not being held.
     * Reflector is immediately released with no lag once these frames have
     * passed.
     */
    float x98_FOX_REFLECTOR_RELEASE_LAG;
    /// Amount of turn frames for changing Reflector direction
    float x9C_FOX_REFLECTOR_TURN_FRAMES;
    float xA0_FOX_REFLECTOR_UNK1;
    s32 xA4_FOX_REFLECTOR_GRAVITY_DELAY;
    float xA8_FOX_REFLECTOR_MOMENTUM_PRESERVE_X;
    float xAC_FOX_REFLECTOR_FALL_ACCEL;
    ReflectDesc xB0_FOX_REFLECTOR_REFLECTION;
};

#endif
