#ifndef MELEE_FT_CHARA_FTMEWTWO_TYPES_H
#define MELEE_FT_CHARA_FTMEWTWO_TYPES_H

#include <platform.h>

#include <baselib/forward.h>

#include "lb/types.h"

#include <common_structs.h>

struct ftMewtwo_FighterVars {
    /* 0x222C */ HSD_GObj* x222C_disableGObj;
    /* 0x2230 */ HSD_GObj*
        x2230_shadowHeldGObj; // GObj of Shadow Ball while in Mewtwo's hands?
    /* 0x2234 */ s32 x2234_shadowBallCharge; // Number of cycles Shadow Ball
                                             // has been charged
    /* 0x2238 */ HSD_GObj* x2238_shadowBallGObj;
    /* 0x223C */ bool x223C_isConfusionBoost;
};

typedef struct ftMewtwoSpecialHi {
    /// 0x2340 - Number of frames Teleport's zoom animation lasts for
    s32 travelFrames;
    float stickX;
    float stickY;
    /// 0x234C - ???
    s32 unk4;
    float velX;
    float velY;
    float groundVelX;
} ftMewtwoSpecialHi;

typedef struct ftMewtwoSpecialS {
    /// 0x2340 - ???
    u8 isConfusionReflect : 1;
} ftMewtwoSpecialS;

typedef struct ftMewtwoSpecialN {
    bool isFull;
    s32 x2344;
    bool x2348;
    s32 releaseLag;
    /// 0x2350 - Charge level of Shadow Ball
    float chargeLevel;
} ftMewtwoSpecialN;

typedef union ftMewtwo_MotionVars {
    ftMewtwoSpecialN SpecialN;
    ftMewtwoSpecialS SpecialS;
    ftMewtwoSpecialHi SpecialHi;
} ftMewtwo_MotionVars;

typedef struct _ftMewtwoAttributes {
    // NEUTRAL SPECIAL - SHADOW BALL (SpecialN/SpecialAirN)

    float x0_MEWTWO_SHADOWBALL_CHARGE_CYCLES; // Number of frames each
                                              // iteration cycle lasts?
    float x4_MEWTWO_SHADOWBALL_GROUND_RECOIL_X;
    float x8_MEWTWO_SHADOWBALL_AIR_RECOIL_X;
    s32 xC_MEWTWO_SHADOWBALL_CHARGE_ITERATIONS; // Number of iterations
                                                // required for full charge
    s32 x10_MEWTWO_SHADOWBALL_RELEASE_LAG;
    float x14_MEWTWO_SHADOWBALL_LANDING_LAG;

    // SIDE SPECIAL - CONFUSION (SpecialS/SpecialAirS)

    float x18_MEWTWO_CONFUSION_AIR_BOOST;
    ReflectDesc x1C_MEWTWO_CONFUSION_REFLECTION;

    // UP SPECIAL - TELEPORT (SpecialHi/SpecialAirHi)

    float x40_MEWTWO_TELEPORT_VEL_DIV_X;
    float x44_MEWTWO_TELEPORT_VEL_DIV_Y;
    float x48_MEWTWO_TELEPORT_GRAVITY;
    float x4C_MEWTWO_TELEPORT_TERMINAL_VELOCITY;
    s32 x50_MEWTWO_TELEPORT_DURATION;
    float x54_MEWTWO_TELEPORT_UNK2;
    float x58_MEWTWO_TELEPORT_STICK_RANGE_MIN;
    float x5C_MEWTWO_TELEPORT_MOMENTUM;
    float x60_MEWTWO_TELEPORT_MOMENTUM_ADD;
    float x64_MEWTWO_TELEPORT_DRIFT;
    s32 x68_MEWTWO_TELEPORT_ANGLE_CLAMP; // Clamp teleport travel if surface
                                         // angle is greater than this value
    float x6C_MEWTWO_TELEPORT_MOMENTUM_END_MUL;
    float x70_MEWTWO_TELEPORT_FREEFALL_MOBILITY;
    float x74_MEWTWO_TELEPORT_LANDING_LAG;

    // DOWN SPECIAL - DISABLE (SpecialLw/SpecialAirLw)

    float x78_MEWTWO_DISABLE_GRAVITY;
    float x7C_MEWTWO_DISABLE_TERMINAL_VELOCITY;
    float x80_MEWTWO_DISABLE_OFFSET_X;
    float x84_MEWTWO_DISABLE_OFFSET_Y;
} ftMewtwoAttributes;

#endif
