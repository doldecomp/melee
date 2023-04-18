#ifndef MELEE_FT_CHARA_FTNESS_TYPES_H
#define MELEE_FT_CHARA_FTNESS_TYPES_H

#include <platform.h>

#include <dolphin/mtx/types.h>

union ftNess_MotionVars {
    struct ftNess_YoyoVars {
        /// 0x2340 - Current frame of Up/Down Smash animation as an integer
        s32 yoyoCurrentFrame;
        /// 0x2344 - Frames until Up/Down Smash hitbox automatically refreshes;
        /// part of why the Yo-Yo Glitch occurs
        s32 yoyoRehitTimer;
        /// 0x2348 - bool to indicate whether Ness can charge the Yo-Yo
        bool isChargeDisable;
        /// 0x234C - bool to indicate whether Yo-Yo hitbox position should
        /// update based on raw Vec3 input (false) or modified calculations
        /// (true)
        bool isPosUpdateMod;
    } attackhi4, attacklw4;

    struct ftNess_SpecialNVars {
        /// 0x2340 - Number of frames Ness remains in the "charge loop"
        /// animation after releasing PK Flash
        s32 flashTimerLoop1;
        /// 0x2344 - Number of extra frames Ness remains in the "charge loop"
        /// animation after releasing PK Flash?
        s32 flashTimerLoop2;
        /// 0x2348 - Number of frames to pass before gravity takes effect
        s32 gravityDelay;
        /// 0x234C - Minimum number of frames required to pass for PK Flash to
        /// auto-release if B is not being held
        s32 flashTimerMin;
    } specialn;

    struct ftNess_SpecialHiVars {
        /// 0x2340 - PK Thunder collision type? Used to check if PK Thunder is
        /// colliding with Ness
        s32 thunderColl;
        /// 0x2344 - Number of frames Ness remains in the "control loop"
        /// animation after PK Thunder despawns
        s32 thunderTimerLoop1;
        /// 0x2348 - Number of extra frames Ness remains in the "control loop"
        /// animation after PK Thunder despawns?
        s32 thunderTimerLoop2;
        /// 0x234C - Number of frames to pass before gravity takes effect
        s32 gravityDelay;
        /// 0x2350 - ???
        Vec3 collPos1;
        /// 0x235C - ???
        Vec3 collPos2;
        /// 0x2368 - Aerial velocity of PK Thunder 2 (Self-Hit)
        f32 aerialVel;
        /// 0x236C - Set various times but never actually used?
        f32 unkVar;
        /// 0x2370 - Facing direction change frorm PK Thunder collision
        f32 facingDir;
        /// 0x2374 through 0x237C - Unused vector
        Vec3 unkVector1;
        /// 0x2380 - bool used in a weird way to switch to PK Thunder 2 GFX
        s32 jibakuGFX;
        /// 0x2384 - Fall acceleration of PK Thunder 2 (Self-Hit)
        f32 fallAccel;
        /// 0x2388 - Set various times but never actually used?
        f32 unkVar3;
        /// 0x238C - Set various times but never actually used?
        f32 unkVar4;
    } specialhi;

    struct ftNess_SpecialLwVars {
        /// 0x2340 - Auto lag frames after initializing PSI Magnet if B is not
        /// being held; PSI Magnet is immediately released with no lag once
        /// these frames have passed
        s32 releaseLag;
        /// 0x2344 - Unused turnaround timer
        s32 turnFrames;
        /// 0x2348 - Check if Ness is no longer holding B
        bool isRelease;
        /// 0x234C - Number of frames to pass before gravity takes effect
        s32 gravityDelay;
        s32 x10;
    } speciallw;
};

#endif
