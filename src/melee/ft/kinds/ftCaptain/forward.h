/**
 * @file forward.h
 * @brief Forward declarations and motion state definitions for Captain Falcon
 * / Ganondorf
 * @details Declares type forwards, motion flag bitmasks, motion state indices,
 * and submotion indices used by Captain Falcon and Ganondorf (clone sharing
 * animations). Module prefix: ftCa
 */

#ifndef MELEE_FT_CHARA_FTCAPTAIN_FORWARD_H
#define MELEE_FT_CHARA_FTCAPTAIN_FORWARD_H

#include <melee/ft/forward.h>
#include <melee/ft/kinds/ftCommon/forward.h>

/// Forward declaration of Captain Falcon's character attributes from DAT file.
typedef struct ftCaptain_DatAttrs ftCaptain_DatAttrs;

/// Forward declaration of Captain Falcon's motion state variables union.
typedef union ftCaptain_MotionVars ftCaptain_MotionVars;

/* ==========================================================================
 */
/* Motion Flags */
/* ==========================================================================
 */

/// Base motion flags for Captain Falcon special moves: preserves sound
/// effects.
static MotionFlags const ftCa_MF_Special = ftCo_MF_Special | Ft_MF_KeepSfx;

/// Neutral-B (Falcon Punch): preserves sound effects and fast-fall state.
static MotionFlags const ftCa_MF_SpecialN =
    ftCa_MF_Special | Ft_MF_KeepFastFall;

/// Aerial Neutral-B (Aerial Falcon Punch): skips parasol item interaction.
static MotionFlags const ftCa_MF_SpecialAirN =
    ftCa_MF_SpecialN | Ft_MF_SkipParasol;

/// Side-B (Raptor Boost): preserves visual graphics effects across frames.
static MotionFlags const ftCa_MF_SpecialS = ftCa_MF_Special | Ft_MF_KeepGfx;

/// Aerial Side-B Startup (Aerial Raptor Boost startup): skips parasol
/// interaction.
static MotionFlags const ftCa_MF_SpecialAirSStart =
    ftCa_MF_SpecialS | Ft_MF_SkipParasol;

/// Aerial Side-B Hit (Aerial Raptor Boost spike): skips parasol interaction.
static MotionFlags const ftCa_MF_SpecialAirS =
    ftCa_MF_SpecialS | Ft_MF_SkipParasol;

/// Up-B (Falcon Dive): preserves fast-fall and visual graphics effects.
static MotionFlags const ftCa_MF_SpecialHi =
    ftCo_MF_Special | Ft_MF_KeepFastFall | Ft_MF_KeepGfx;

/// Aerial Up-B (Aerial Falcon Dive): skips parasol interaction.
static MotionFlags const ftCa_MF_SpecialAirHi =
    ftCa_MF_SpecialHi | Ft_MF_SkipParasol;

/// Down-B (Falcon Kick): preserves color animation and hit status.
static MotionFlags const ftCa_MF_SpecialLw =
    ftCa_MF_Special | Ft_MF_KeepColAnimHitStatus;

/// Down-B Rebound (Falcon Kick wall bonk / air end): skips parasol
/// interaction.
static MotionFlags const ftCa_MF_SpecialLwRebound =
    ftCa_MF_SpecialLw | Ft_MF_SkipParasol;

/* ==========================================================================
 */
/* Motion States */
/* ==========================================================================
 */

/**
 * @brief Motion state IDs for Captain Falcon (and Ganondorf).
 * Extends the common motion states (`ftCo_MS_*`).
 */
typedef enum ftCaptain_MotionState {
    ftCa_MS_SwordSwing4 =
        ftCo_MS_Count,      ///< Beam Sword forward smash (swing 4)
    ftCa_MS_BatSwing4,      ///< Home-Run Bat forward smash (swing 4)
    ftCa_MS_ParasolSwing4,  ///< Parasol forward smash (swing 4)
    ftCa_MS_HarisenSwing4,  ///< Fan forward smash (swing 4)
    ftCa_MS_StarRodSwing4,  ///< Star Rod forward smash (swing 4)
    ftCa_MS_LipstickSwing4, ///< Lip's Stick forward smash (swing 4)

    // Neutral-B: Falcon Punch / Warlock Punch
    ftCa_MS_SpecialN,    ///< Grounded Neutral-B (Falcon Punch)
    ftCa_MS_SpecialAirN, ///< Aerial Neutral-B (Aerial Falcon Punch)

    // Side-B: Raptor Boost / Gerudo Dragon
    ftCa_MS_SpecialSStart,    ///< Grounded Side-B Startup (Raptor Boost dash)
    ftCa_MS_SpecialS,         ///< Grounded Side-B Hit (Raptor Boost uppercut)
    ftCa_MS_SpecialAirSStart, ///< Aerial Side-B Startup (Aerial Raptor Boost
                              ///< dive)
    ftCa_MS_SpecialAirS, ///< Aerial Side-B Hit (Aerial Raptor Boost meteor
                         ///< spike)

    // Up-B: Falcon Dive / Dark Dive
    ftCa_MS_SpecialHi,      ///< Up-B Grounded/Air Startup & Leap (Falcon Dive)
    ftCa_MS_SpecialAirHi,   ///< Aerial Up-B Leap (Falcon Dive)
    ftCa_MS_SpecialHiCatch, ///< Up-B Grab/Catch (Falcon Dive command grab
                            ///< contact)
    ftCa_MS_SpecialHiThrow, ///< Up-B Explosion Throw (Falcon Dive explosion
                            ///< release)

    // Down-B: Falcon Kick / Wizard's Foot
    ftCa_MS_SpecialLw,    ///< Grounded Down-B (Falcon Kick ground dash)
    ftCa_MS_SpecialLwEnd, ///< Grounded Down-B Ground Recovery (Falcon Kick
                          ///< ground ending)
    ftCa_MS_SpecialAirLw, ///< Aerial Down-B (Aerial Falcon Kick downward dive)
    ftCa_MS_SpecialAirLwEnd,    ///< Aerial Down-B Ground Landing (Falcon Kick
                                ///< landing recovery)
    ftCa_MS_SpecialAirLwEndAir, ///< Aerial Down-B Air Recovery (Falcon Kick
                                ///< air ending)
    ftCa_MS_SpecialLwEndAir,    ///< Grounded Down-B Air Recovery (Falcon Kick
                                ///< running off ledge)
    ftCa_MS_SpecialHiThrow1, ///< Falcon Kick Wall Rebound / Wall Bonk bounce

    ftCa_MS_Count, ///< Total motion states including common states
    ftCa_MS_SelfCount =
        ftCa_MS_Count -
        ftCo_MS_Count, ///< Character-specific motion state count
} ftCaptain_MotionState;

/* ==========================================================================
 */
/* Submotions (Animation IDs) */
/* ==========================================================================
 */

/**
 * @brief Submotion (animation) indices for Captain Falcon.
 */
typedef enum ftCa_Submotion {
    ftCa_SM_SwordSwing4 =
        ftCo_SM_Count,      ///< Beam Sword forward smash animation
    ftCa_SM_BatSwing4,      ///< Home-Run Bat forward smash animation
    ftCa_SM_ParasolSwing4,  ///< Parasol forward smash animation
    ftCa_SM_HarisenSwing4,  ///< Fan forward smash animation
    ftCa_SM_StarRodSwing4,  ///< Star Rod forward smash animation
    ftCa_SM_LipstickSwing4, ///< Lip's Stick forward smash animation

    // Neutral-B: Falcon Punch / Warlock Punch
    ftCa_SM_SpecialN,    ///< Grounded Neutral-B animation
    ftCa_SM_SpecialAirN, ///< Aerial Neutral-B animation

    // Side-B: Raptor Boost / Gerudo Dragon
    ftCa_SM_SpecialSStart,    ///< Grounded Side-B Startup animation
    ftCa_SM_SpecialS,         ///< Grounded Side-B Uppercut animation
    ftCa_SM_SpecialAirSStart, ///< Aerial Side-B Startup animation
    ftCa_SM_SpecialAirS,      ///< Aerial Side-B Meteor Spike animation

    // Up-B: Falcon Dive / Dark Dive
    ftCa_SM_SpecialHi,       ///< Grounded Up-B Leap animation
    ftCa_SM_SpecialAirHi,    ///< Aerial Up-B Leap animation
    ftCa_SM_SpecialHiCatch,  ///< Up-B Grab/Catch animation
    ftCa_SM_SpecialHiThrow0, ///< Up-B Explosion Throw animation

    // Down-B: Falcon Kick / Wizard's Foot
    ftCa_SM_SpecialLw,          ///< Grounded Down-B Kick animation
    ftCa_SM_SpecialLwEnd,       ///< Grounded Down-B Recovery animation
    ftCa_SM_SpecialAirLw,       ///< Aerial Down-B Kick animation
    ftCa_SM_SpecialAirLwEnd,    ///< Aerial Down-B Landing animation
    ftCa_SM_SpecialLwEndAir,    ///< Grounded Down-B Edge Slip animation
    ftCa_SM_SpecialAirLwEndAir, ///< Aerial Down-B Air Recovery animation
    ftCa_SM_SpecialHiThrow1,    ///< Falcon Kick Wall Rebound animation

    ftCa_SM_Count, ///< Total submotions including common
    ftCa_SM_SelfCount =
        ftCa_SM_Count - ftCo_SM_Count, ///< Character-specific submotion count
} ftCa_Submotion;

#endif
