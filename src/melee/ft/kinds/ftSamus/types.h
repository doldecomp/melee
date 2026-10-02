/**
 * @file types.h
 * @brief Type definitions and structures for Samus
 * @details Defines Samus's persistent fighter variables (such as Charge Shot
 * state and item pointers), special character attributes loaded from PlSs.dat
 * (ftSs_DatAttrs), grapple beam structures, and per-motion action state
 * variables. Module prefix: ftSs
 */

#ifndef MELEE_FT_CHARA_FTSAMUS_TYPES_H
#define MELEE_FT_CHARA_FTSAMUS_TYPES_H

#include <Runtime/platform.h>

#include <melee/it/forward.h>
#include <sysdolphin/baselib/forward.h>

#include <placeholder.h>

#include <dolphin/mtx.h>
#include <melee/ft/kinds/ftCommon/types.h>

/**
 * @brief Persistent character-specific variables for Samus (stored in
 * Fighter::u.ss)
 */
struct ftSamus_FighterVars {
    /* 0x222C */ Item_GObj*
        x222C; ///< Pointer to active Charge Shot projectile entity
    /* 0x2230 */ s32
        x2230; ///< Current Charge Shot charge level (0 to max charge)
    /* 0x2234 */ u32 x2234;        ///< Visual effect active tracking flag
    /* 0x2238 */ u32 x2238;        ///< Missile count / identifier counter
    /* 0x223C */ Item_GObj* x223C; ///< Secondary item / grapple pointer

    /* 0x2240 */ u8 x2240;
    /* 0x2241 */ u8 x2241;
    /* 0x2242 */ u8 x2242;
    /* 0x2243 */ u8 x2243;

    /* 0x2244 */ u32 x2244; ///< Screw Attack / active effect flag
    /* 0x2248 */ u32 x2248;
};

/**
 * @brief Special attributes loaded from character parameters file (PlSs.dat)
 */
typedef struct _ftSamusAttributes {
    /*  +0 */ float x0; ///< Bomb jump starting frame / offset
    /*  +4 */ float x4; ///< Bomb jump horizontal launch angle factor
    /*  +8 */ float x8; ///< Bomb jump launch velocity magnitude
    /*  +C */ float
        xC; ///< Down-B Morph Ball ground roll walk speed multiplier
    /* +10 */ float
        x10; ///< Down-B Morph Ball air drift max / jump momentum multiplier
    /* +14 */ float x14; ///< Down-B Morph Ball unmorph stick Y threshold
    /* +18 */ float x18; ///< Neutral-B Charge Shot maximum charge level
    /* +1C */ float
        x1C; ///< Neutral-B Charge Shot aerial recoil speed per charge level
    /* +20 */ int x20;   ///< Neutral-B Charge Shot frames per charge increment
    /* +24 */ float x24; ///< Neutral-B Charge Shot aerial firing landing lag
    /* +28 */ float x28; ///< Side-B Missile stick X threshold to trigger Super
                         ///< Missile (smash)
    /* +2C */ float x2C; ///< Side-B Missile initial velocity reduction divisor
    /* +30 */ float x30; ///< Side-B Missile aerial horizontal deceleration
    /* +34 */ float x34; ///< Side-B Missile projectile spawn horizontal offset
    /* +38 */ float x38; ///< Up-B Screw Attack grounded forward leap velocity
    /* +3C */ float x3C; ///< Up-B Screw Attack aerial drift acceleration
    /* +40 */ float x40; ///< Up-B Screw Attack aerial drift max speed
    /* +44 */ float
        x44; ///< Up-B Screw Attack aerial initial vertical velocity
    /* +48 */ float x48; ///< Up-B Screw Attack freefall horizontal speed clamp
    /* +4C */ float
        x4C; ///< Up-B Screw Attack B-reverse turnaround stick X threshold
    /* +50 */ float x50; ///< Up-B Screw Attack landing lag frames
    /* +54 */ float x54; ///< Down-B Bomb drop ground hop vertical velocity
    /* +58 */ float x58; ///< Down-B Bomb drop aerial initial vertical velocity
    /* +5C */ float x5C; ///< Down-B Bomb drop walk max velocity multiplier
    /* +60 */ float
        x60; ///< Down-B Bomb drop aerial drift max velocity multiplier
    /* +64 */ float x64; ///< Down-B Bomb drop walk acceleration multiplier
    /* +68 */ float x68; ///< Down-B Bomb drop aerial drift stick multiplier
    /* +6C */ float
        x6C; ///< Down-B Bomb drop grounded initial velocity retention
    /* +70 */ float
        x70; ///< Down-B Bomb drop aerial initial velocity retention
    /* +74 */ Vec3 x74_vec; ///< Down-B Bomb spawn offset from TopN bone
    /* +80 */ float x80;    ///< Down-B Bomb drop stick Y threshold to unmorph
    /* +84 */ ftCollisionBox
        height_attributes; ///< Height collision box for Morph Ball / crouch
    /* +9C */ s32 x9C;
    /* +A0 */ s32 xA0;
    /* +A4 */ s32 xA4;
    /* +A8 */ s32 xA8;
    /* +AC */ s32 xAC;
    /* +B0 */ s32 xB0;
    /* +B4 */ s32 xB4;
    /* +B8 */ s32 xB8;
    /* +BC */ int xBC;
    /* +C0 */ int xC0;
    /* +C4 */ int xC4;
    /* +C8 */ int xC8;
    /* +CC */ f32 xCC;
    /* +D0 */ UNK_T xD0;
} ftSs_DatAttrs;

/**
 * @brief Samus Grapple Beam joint and animation data
 */
struct UNK_SAMUS_S1 {
    HSD_Joint* x0_joint;
    HSD_AnimJoint** x4_anim_joints;
    HSD_AnimJoint* x8_anim_joint;
    HSD_MatAnimJoint* xC_matanim_joint;
};

/**
 * @brief Motion variables union for Samus's action states (Fighter::mv.ss)
 */
union ftSamus_MotionVars {
    /// SpecialLw (Morph Ball / Bomb Drop) state variables
    struct ftSamus_SpecialLwVars {
        s32 x0; ///< State progression flag (0 = startup, 1 = ball active)
    } speciallw;

    /// SpecialN (Charge Shot) state variables
    struct ftSamus_SpecialNVars {
        s32 x0; ///< Aerial startup flag (0 = ground, 1 = air)
        s32 x4; ///< Charge tick frame counter
        float x8;
    } specialn;

    /// Grapple beam state variables
    struct ftSamus_GrappleVars {
        s32 x0;
        float x4; ///< Grapple beam duration
        float x8;
    } grapple;

    /// SpecialHi (Screw Attack) state variables
    struct ftSamus_SpecialHiVars {
        s32 x0; ///< Turnaround / B-reverse executed flag
    } specialhi;

    /// SpecialLw Jump (Bomb Jump) state variables
    struct ftSamus_SpecialLwJumpVars {
        s32 x0; ///< Morph ball hurtbox state flag
    } speciallw_jump;

    /// Unused/Unknown state vars
    struct ftSamus_State7Vars {
        f32 x0;
    } unk7;
};

#endif
