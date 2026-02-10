#ifndef MELEE_FT_CHARA_FTNESS_TYPES_H
#define MELEE_FT_CHARA_FTNESS_TYPES_H

#include <platform.h>

#include "ftNess/forward.h" // IWYU pragma: export

#include "lb/types.h"

#include <baselib/forward.h>

#include <common_structs.h>
#include <dolphin/mtx.h>

struct ftNess_FighterVars {
    /* 0x222C */ HSD_GObj* yoyo_gobj;
    /* 0x2230 */ Vec3 yoyo_hitbox_pos;
    /* 0x223C */ float x223C;
    /* 0x2240 */ HSD_GObj* pkflash_gobj;
    /* 0x2244 */ HSD_GObj* pkthunder_gobj;
    /* 0x2248 */ HSD_GObj* bat_gobj;
    /// bool for PK Thunder GFX?
    /* 0x224C */ u32 pkthunder_gfx;
};

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
        /* fp+2340 */ int frames_to_loop_charge_ground;
        /// 0x2344 - Number of extra frames Ness remains in the "charge loop"
        /// animation after releasing PK Flash?
        /* fp+2344 */ int frames_to_loop_charge_air;
        /// 0x2348 - Number of frames to pass before gravity takes effect
        /* fp+2348 */ int falling_acceleration_delay;
        /// 0x234C - Minimum number of frames required to pass for PK Flash to
        /// auto-release if B is not being held
        /* fp+234C */ int charge_release_delay;
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
        float aerialVel;
        /// 0x236C - Set various times but never actually used?
        float unkVar;
        /// 0x2370 - Facing direction change frorm PK Thunder collision
        float facingDir;
        /// 0x2374 through 0x237C - Unused vector
        Vec3 unkVector1;
        /// 0x2380 - bool used in a weird way to switch to PK Thunder 2 GFX
        s32 jibakuGFX;
        /// 0x2384 - Fall acceleration of PK Thunder 2 (Self-Hit)
        float fallAccel;
        /// 0x2388 - Set various times but never actually used?
        float unkVar3;
        /// 0x238C - Set various times but never actually used?
        float unkVar4;
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

/// Special Attributes

typedef struct ftNessAttributes {
    // Neutral Special - PK Flash
    s32 x0_PKFLASH_TIMER1_LOOPFRAMES;
    s32 x4_PKFLASH_TIMER2_LOOPFRAMES;
    s32 x8_PKFLASH_GRAVITY_DELAY;
    s32 xC_PKFLASH_MINCHARGEFRAMES;
    float x10_PKFLASH_UNK1;
    float x14_PKFLASH_FALL_ACCEL;
    float x18_PKFLASH_UNK2;
    float x1C_PKFLASH_LANDING_LAG; // If set to 0, Ness does not enter freefall
                                   // after aerial PK Flash, but loses his
                                   // double jump.
    // Side Special - PK Fire
    float x20_PKFIRE_AERIAL_LAUNCH_TRAJECTORY; // Radians
    float x24_PKFIRE_AERIAL_VELOCITY;
    float x28_PKFIRE_GROUNDED_LAUNCH_TRAJECTORY; // Radians
    float x2C_PKFIRE_GROUNDED_VELOCITY;
    float x30_PKFIRE_SPAWN_X;
    float x34_PKFIRE_SPAWN_Y;
    float x38_PKFIRE_LANDING_LAG;
    // Up Special - PK Thunder
    float x3C_PK_THUNDER_UNK1;
    u32 x40_PK_THUNDER_LOOP1;
    u32 x44_PK_THUNDER_LOOP2;
    u32 x48_PK_THUNDER_GRAVITY_DELAY;
    float x4C_PK_THUNDER_UNK2;
    float x50_PK_THUNDER_FALL_ACCEL;
    // Up Special - PK Thunder 2 (Self-Hit)
    float x54_PK_THUNDER_2_MOMENTUM;
    float x58_PK_THUNDER_2_UNK1;
    float x5C_PK_THUNDER_2_DECELERATION_RATE;
    float x60_PK_THUNDER_2_KNOCKDOWN_ANGLE; // Angle to determine whether to
                                            // enter PK Thunder 2 or DownBound
                                            // state (Ground Only)
    float x64_PK_THUNDER_2_WALLHUG_ANGLE; // Surface angle to determine whether
                                          // PK Thunder 2 wallhugs or bounces
    float x68_PK_THUNDER_2_UNK2;
    float
        x6C_PK_THUNDER_2_FREEFALL_ANIM_BLEND; // Amount of animation blend
                                              // frames Ness goes through when
                                              // entering FallSpecial through
                                              // his SpecialHi Motion States
    float x70_PK_THUNDER_2_LANDING_LAG; // If set to 0, Ness does not enter
                                        // freefall after aerial PK Thunder,
                                        // but loses his double jump.
    // Down Special - PSI Magnet
    float x74_PSI_MAGNET_RELEASE_LAG; // Auto lag frames after initializing PSI
                                      // Magnet if B is not being held. PSI
                                      // Magnet is immediately released with no
                                      // lag once these frames have passed.
    float x78_PSI_MAGNET_UNK1;        // Note: Reminiscent of Fox and Falco's
                               // Reflector turn duration attribute? Unused.
    float x7C_PSI_MAGNET_UNK2; // Note: Reminiscent of Fox and Falco's
                               // Reflector Unk1 attribute? Unused.
    float x80_PSI_MAGNET_UNK3; // Unused.
    s32 x84_PSI_MAGNET_FRAMES_BEFORE_GRAVITY;
    float x88_PSI_MAGNET_MOMENTUM_PRESERVATION;
    float x8C_PSI_MAGNET_FALL_ACCEL;
    float x90_PSI_MAGNET_UNK4;     // Unused.
    float x94_PSI_MAGNET_HEAL_MUL; // Multiplies projectile damage by this
                                   // value and heals result
    AbsorbDesc x98_PSI_MAGNET_ABSORPTION;
    // Up/Down Smash - Yo-Yo
    float xAC_YOYO_CHARGE_DURATION; // Amount of frames Yo-Yo can be charged
    float
        xB0_YOYO_DAMAGE_MUL; // Charged Yo-Yo damage multiplier; 350 by
                             // default, identical to the Smash Charge standard
    float xB4_YOYO_REHIT_RATE; // Amount of frames needed for the Yo-Yo to hit
                               // again after colliding with a hurtbox
    // Forward Smash - Baseball Bat
    ReflectDesc xB8_BASEBALL_BAT;

} ftNessAttributes;

#endif
