#ifndef MELEE_FT_CHARA_FTFOX_TYPES_H
#define MELEE_FT_CHARA_FTFOX_TYPES_H

#include <platform.h>
#include <baselib/forward.h>

#include <dolphin/mtx/types.h>

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
    f32 blendFrames[4];
    /// 0x2384 - Illusion/Phantasm GObj pointer
    HSD_GObj* ghostGObj;
} ftFoxSpecialS;

typedef struct ftFoxSpecialHi {
    /// 0x2340 - Number of frames to pass before gravity takes effect
    s32 gravityDelay;
    /// 0x2344 - Used to rotate Fox/Falco's model?
    f32 rotateModel;
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

#endif
