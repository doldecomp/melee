#ifndef MELEE_FT_CHARA_FTNESS_TYPES_H
#define MELEE_FT_CHARA_FTNESS_TYPES_H

#include <platform.h>
#include "ftNess/forward.h" // IWYU pragma: export
#include <dolphin/mtx/forward.h>
#include <baselib/forward.h>

#include <common_structs.h>

struct ftNess_FighterVars {
    /* 0x222C */ HSD_GObj* yoyo_gobj;
    /* 0x2230 */ Vec3 yoyo_hitbox_pos;
    /* 0x223C */ f32 x223C;
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

// Special Attributes

typedef struct ftNessAttributes {
    // Neutral Special - PK Flash
    s32 x0_PKFLASH_TIMER1_LOOPFRAMES;
    s32 x4_PKFLASH_TIMER2_LOOPFRAMES;
    s32 x8_PKFLASH_GRAVITY_DELAY;
    s32 xC_PKFLASH_MINCHARGEFRAMES;
    f32 x10_PKFLASH_UNK1;
    f32 x14_PKFLASH_FALL_ACCEL;
    f32 x18_PKFLASH_UNK2;
    f32 x1C_PKFLASH_LANDING_LAG; // If set to 0, Ness does not enter freefall
                                 // after aerial PK Flash, but loses his double
                                 // jump.
    // Side Special - PK Fire
    f32 x20_PKFIRE_AERIAL_LAUNCH_TRAJECTORY; // Radians
    f32 x24_PKFIRE_AERIAL_VELOCITY;
    f32 x28_PKFIRE_GROUNDED_LAUNCH_TRAJECTORY; // Radians
    f32 x2C_PKFIRE_GROUNDED_VELOCITY;
    f32 x30_PKFIRE_SPAWN_X;
    f32 x34_PKFIRE_SPAWN_Y;
    f32 x38_PKFIRE_LANDING_LAG;
    // Up Special - PK Thunder
    f32 x3C_PK_THUNDER_UNK1;
    u32 x40_PK_THUNDER_LOOP1;
    u32 x44_PK_THUNDER_LOOP2;
    u32 x48_PK_THUNDER_GRAVITY_DELAY;
    f32 x4C_PK_THUNDER_UNK2;
    f32 x50_PK_THUNDER_FALL_ACCEL;
    // Up Special - PK Thunder 2 (Self-Hit)
    f32 x54_PK_THUNDER_2_MOMENTUM;
    f32 x58_PK_THUNDER_2_UNK1;
    f32 x5C_PK_THUNDER_2_DECELERATION_RATE;
    f32 x60_PK_THUNDER_2_KNOCKDOWN_ANGLE; // Angle to determine whether to
                                          // enter PK Thunder 2 or DownBound
                                          // state (Ground Only)
    f32 x64_PK_THUNDER_2_WALLHUG_ANGLE;   // Surface angle to determine whether
                                          // PK Thunder 2 wallhugs or bounces
    f32 x68_PK_THUNDER_2_UNK2;
    f32 x6C_PK_THUNDER_2_FREEFALL_ANIM_BLEND; // Amount of animation blend
                                              // frames Ness goes through when
                                              // entering FallSpecial through
                                              // his SpecialHi Motion States
    f32 x70_PK_THUNDER_2_LANDING_LAG; // If set to 0, Ness does not enter
                                      // freefall after aerial PK Thunder, but
                                      // loses his double jump.
    // Down Special - PSI Magnet
    f32 x74_PSI_MAGNET_RELEASE_LAG; // Auto lag frames after initializing PSI
                                    // Magnet if B is not being held. PSI
                                    // Magnet is immediately released with no
                                    // lag once these frames have passed.
    f32 x78_PSI_MAGNET_UNK1; // Note: Reminiscent of Fox and Falco's Reflector
                             // turn duration attribute? Unused.
    f32 x7C_PSI_MAGNET_UNK2; // Note: Reminiscent of Fox and Falco's Reflector
                             // Unk1 attribute? Unused.
    f32 x80_PSI_MAGNET_UNK3; // Unused.
    s32 x84_PSI_MAGNET_FRAMES_BEFORE_GRAVITY;
    f32 x88_PSI_MAGNET_MOMENTUM_PRESERVATION;
    f32 x8C_PSI_MAGNET_FALL_ACCEL;
    f32 x90_PSI_MAGNET_UNK4;     // Unused.
    f32 x94_PSI_MAGNET_HEAL_MUL; // Multiplies projectile damage by this value
                                 // and heals result
    AbsorbDesc x98_PSI_MAGNET_ABSORPTION;
    // Up/Down Smash - Yo-Yo
    f32 xAC_YOYO_CHARGE_DURATION; // Amount of frames Yo-Yo can be charged
    f32 xB0_YOYO_DAMAGE_MUL;      // Charged Yo-Yo damage multiplier; 350 by
                             // default, identical to the Smash Charge standard
    f32 xB4_YOYO_REHIT_RATE; // Amount of frames needed for the Yo-Yo to hit
                             // again after colliding with a hurtbox
    // Forward Smash - Baseball Bat
    ReflectDesc xB8_BASEBALL_BAT;

} ftNessAttributes;

#endif
