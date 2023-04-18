#ifndef MELEE_FT_CHARA_FTMEWTWO_TYPES_H
#define MELEE_FT_CHARA_FTMEWTWO_TYPES_H

#include <platform.h>

typedef struct ftMewtwoSpecialHi {
    /// 0x2340 - Number of frames Teleport's zoom animation lasts for
    s32 travelFrames;
    f32 stickX;
    f32 stickY;
    /// 0x234C - ???
    s32 unk4;
    f32 velX;
    f32 velY;
    f32 groundVelX;
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
    f32 chargeLevel;
} ftMewtwoSpecialN;

typedef union ftMewtwo_MotionVars {
    ftMewtwoSpecialN SpecialN;
    ftMewtwoSpecialS SpecialS;
    ftMewtwoSpecialHi SpecialHi;
} ftMewtwo_MotionVars;

#endif
