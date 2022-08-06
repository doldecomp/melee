#ifndef _FTFOX_STATEVARS_H_
#define _FTFOX_STATEVARS_H_

#include <types.h>
#include <sysdolphin/baselib/gobj.h>

typedef struct ftFoxSpecialN {

    BOOL isBlasterLoop; // 0x2340 - Check to allow repeated blaster shots

} ftFoxSpecialN;

typedef struct ftFoxSpecialS {

    s32 gravityDelay; // 0x2340 - Number of frames to pass before gravity takes effect
    Vec3 ghostEffectPos[4]; // 0x2344 through 0x2370 - Related to Illusion/Phantasm model's position?
    f32 blendFrames[4]; // 0x2374 through 0x2380 - ColAnim blend frames?
    HSD_GObj* ghostGObj; // 0x2384 - Illusion/Phantasm GObj pointer

} ftFoxSpecialS;

typedef struct ftFoxSpecialHi {

    s32 gravityDelay; // 0x2340 - Number of frames to pass before gravity takes effect
    f32 rotateModel; // 0x2344 - Used to rotate Fox/Falco's model?
    s32 travelFrames; // 0x2348 - Number of frames Firefox/Firebird's launch animation lasts for
    s32 unk; // 0x234C - ???
    s32 unk2; // 0x2350 - ???

} ftFoxSpecialHi;

typedef struct ftFoxSpecialLw {

    s32 releaseLag; // 0x2340 - Auto lag frames after initializing Reflector if B is not being held. Reflector is immediately released with no lag once these frames have passed
    s32 turnFrames; // 0x2344 - Number of frames it takes Fox/Falco to turn around on command
    BOOL isRelease; // 0x2348 - Check if Fox/Falco is no longer holding B
    s32 gravityDelay; // 0x234C - Number of frames to pass before gravity takes effect

} ftFoxSpecialLw;

typedef union ftFoxStateVars {

    ftFoxSpecialN specialN;
    ftFoxSpecialS specialS;
    ftFoxSpecialHi specialHi;
    ftFoxSpecialLw specialLw;

} ftFoxStateVars;

#endif