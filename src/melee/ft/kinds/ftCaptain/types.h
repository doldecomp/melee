/**
 * @file types.h
 * @brief Structs and unions for Captain Falcon and Ganondorf character
 * attributes and motion variables
 * @details Defines character-specific fighter variables, DAT attribute tables,
 * and motion variables for Falcon Punch (SpecialN), Raptor Boost (SpecialS),
 * Falcon Dive (SpecialHi), and Falcon Kick (SpecialLw). Module prefix: ftCa
 */

#ifndef MELEE_FT_CHARA_FTCAPTAIN_TYPES_H
#define MELEE_FT_CHARA_FTCAPTAIN_TYPES_H

#include <Runtime/platform.h>

#include <melee/ft/forward.h>
#include <melee/ft/kinds/ftCaptain/forward.h> // IWYU pragma: export

#include <dolphin/mtx.h>

/**
 * @brief Character-specific persistent fighter variables stored in `fp->u.ca`.
 */
struct ftCaptain_FighterVars {
    /**
     * @brief Flag set to true during Raptor Boost startup state
     * (SpecialSStart). Used to keep track of and clear visual effects on state
     * exit or death.
     */
    /* 0x222C */ u32 during_specials_start;

    /**
     * @brief Flag set to true during Raptor Boost active hit state (SpecialS).
     * Used to manage persistent trail/hit visual effects. Cleared on state
     * exit or death.
     */
    /* 0x2230 */ u32 during_specials;

    u8 _[FIGHTERVARS_SIZE -
         8]; ///< Unused padding up to FIGHTERVARS_SIZE (0x2240)
};

/**
 * @brief Character parameters loaded from character DAT archive (PlCa.dat /
 * PlGn.dat).
 */
struct ftCaptain_DatAttrs {
    /// Neutral-B (Falcon Punch): Minimum control stick range required for
    /// downward angle (Negative Y).
    /* +0 */ float specialn_stick_range_y_neg;

    /// Neutral-B (Falcon Punch): Minimum control stick range required for
    /// upward angle (Positive Y).
    /* +4 */ float specialn_stick_range_y_pos;

    /// Neutral-B (Falcon Punch): Maximum angle deflection from control stick
    /// input (in degrees).
    /* +8 */ float specialn_angle_diff;

    /// Neutral-B (Falcon Punch): Base forward/upward momentum gained when
    /// punch releases in the air.
    /* +C */ float specialn_vel_x;

    /// Neutral-B (Falcon Punch): Velocity decay multiplier applied per frame
    /// during aerial punch drift.
    /* +10 */ float specialn_vel_mul;

    /// Side-B (Raptor Boost): Ground velocity multiplier applied upon
    /// detecting a target.
    /* +14 */ float specials_gr_vel_x;

    /// Side-B (Raptor Boost): Downward gravity acceleration applied during
    /// aerial Raptor Boost.
    /* +18 */ float specials_grav;

    /// Side-B (Raptor Boost): Maximum terminal downward velocity during aerial
    /// Raptor Boost.
    /* +1C */ float specials_terminal_vel;

    /// Side-B (Raptor Boost): Unused parameter 0.
    /* +20 */ float specials_unk0;

    /// Side-B (Raptor Boost): Unused parameter 1.
    /* +24 */ float specials_unk1;

    /// Side-B (Raptor Boost): Unused parameter 2.
    /* +28 */ float specials_unk2;

    /// Side-B (Raptor Boost): Unused parameter 3.
    /* +2C */ float specials_unk3;

    /// Side-B (Raptor Boost): Unused parameter 4.
    /* +30 */ float specials_unk4;

    /// Side-B (Raptor Boost): Unused parameter 5.
    /* +34 */ float specials_unk5;

    /// Side-B (Raptor Boost): Landing lag frames when aerial Raptor Boost
    /// whiffs (misses).
    /* +38 */ float specials_miss_landing_lag;

    /// Side-B (Raptor Boost): Landing lag frames when aerial Raptor Boost hits
    /// a target.
    /* +3C */ float specials_hit_landing_lag;

    /// Up-B (Falcon Dive): Air friction multiplier applied during the upward
    /// leap.
    /* +40 */ float specialhi_air_friction_mul;

    /// Up-B (Falcon Dive): Horizontal air velocity multiplier during ascent.
    /* +44 */ float specialhi_horz_vel;

    /// Up-B (Falcon Dive): Air speed multiplier during freefall (FallSpecial)
    /// after the dive.
    /* +48 */ float specialhi_freefall_air_spd_mul;

    /// Up-B (Falcon Dive): Landing lag frames incurred when landing in
    /// freefall or after throw.
    /* +4C */ float specialhi_landing_lag;

    /// Up-B (Falcon Dive): Unused parameter 0.
    /* +50 */ float specialhi_unk0;

    /// Up-B (Falcon Dive): Unused parameter 1.
    /* +54 */ float specialhi_unk1;

    /// Up-B (Falcon Dive): Analog stick horizontal threshold required to
    /// reverse facing direction during startup.
    /* +58 */ float specialhi_input_var;

    /// Up-B (Falcon Dive): Initial value loaded into cmd_vars[1].
    /* +5C */ float specialhi_unk2;

    /// Up-B (Falcon Dive): Gravity acceleration applied during the
    /// post-explosion throw recoil.
    /* +60 */ float specialhi_catch_grav;

    /// Up-B (Falcon Dive): Initial timer/counter value for aerial Up-B state.
    /* +64 */ s32 specialhi_air_var;

    /// Unknown / padding attribute.
    /* +68 */ float x68;

    /// Down-B (Falcon Kick): Down-B unknown parameter 1.
    /* +6C */ u32 speciallw_unk1;

    /// Down-B (Falcon Kick): Angle (in degrees) for foot flame particle effect
    /// during aerial Falcon Kick.
    /* +70 */ float speciallw_flame_particle_angle;

    /// Down-B (Falcon Kick): Speed modifier multiplied into friction on hit
    /// (contact deceleration).
    /* +74 */ float speciallw_on_hit_spd_modifier;

    /// Down-B (Falcon Kick): Maximum hit slowdown counter cap.
    /* +78 */ s32 speciallw_unk2;

    /// Down-B (Falcon Kick): Ground recovery animation speed multiplier on
    /// ground.
    /* +7C */ float speciallw_ground_lag_mul;

    /// Down-B (Falcon Kick): Landing recovery animation speed multiplier when
    /// landing from aerial kick.
    /* +80 */ float speciallw_landing_lag_mul;

    /// Down-B (Falcon Kick): Ground traction multiplier during ground recovery
    /// slide.
    /* +84 */ float speciallw_ground_traction;

    /// Down-B (Falcon Kick): Traction multiplier during aerial kick landing
    /// slide.
    /* +88 */ float speciallw_air_landing_traction;
};

/**
 * @brief Motion variables union stored in `fp->mv.ca`, active during specific
 * special moves.
 */
union ftCaptain_MotionVars {
    /**
     * @brief Motion variables for Side Special (Raptor Boost).
     */
    struct ftCaptainSpecialSVars {
        /* fp+2340 */ float grav; ///< Accumulated downward velocity / gravity
                                  ///< during aerial Raptor Boost
    } specials;

    /**
     * @brief Motion variables for Up Special (Falcon Dive).
     */
    struct ftCaptainSpecialHiVars {
        /* fp+2340 */ u16
            x0; ///< Timer/counter initialized from specialhi_air_var
        /* fp+2342:0 */ u8 x2_b0 : 1; ///< Set to true upon explosion release
                                      ///< to enable post-throw gravity physics
        /* fp+2342:1 */ u8 x2_b1
            : 1; ///< Set to true when turnaround window ends; enables ledge
                 ///< grab / landing lag
        /* fp+2342:2 */ u8 x2_b2 : 1;
        /* fp+2342:3 */ u8 x2_b3 : 1;
        /* fp+2342:4 */ u8 x2_b4 : 1;
        /* fp+2342:5 */ u8 x2_b5 : 1;
        /* fp+2342:6 */ u8 x2_b6 : 1;
        /* fp+2342:7 */ u8 x2_b7 : 1;
        /* fp+2343 */ u8 x3;
        /* fp+2344 */ Vec2
            vel; ///< Cached 2D velocity vector during Falcon Dive ascent
    } specialhi;

    /**
     * @brief Motion variables for Down Special (Falcon Kick).
     */
    struct ftCaptainSpecialLwVars {
        /* fp+2340 */ u16 x0; ///< Hit counter for contact slowdown
        /* fp+2342 */ u16 x2;
        /* fp+2344 */ float friction; ///< Velocity damping multiplier (reduced
                                      ///< upon connecting with a target)
        /* fp+2348 */ s32 x4;
    } speciallw;
};

#endif
