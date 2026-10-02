/**
 * @file forward.h
 * @brief Forward declarations and motion flags for Samus
 * @details Declares Samus-specific types, motion flags for her special moves
 * (Neutral-B Charge Shot, Side-B Missile, Up-B Screw Attack, Down-B Bomb, and
 * Zair), and motion state / submotion enums. Module prefix: ftSs
 */

#ifndef MELEE_FT_CHARA_FTSAMUS_FORWARD_H
#define MELEE_FT_CHARA_FTSAMUS_FORWARD_H

#include <melee/ft/forward.h>
#include <melee/ft/kinds/ftCommon/forward.h>

typedef struct Fighter ftSs_Fighter;

/* Base Motion Flags for Samus Special Moves */
static MotionFlags const ftSs_MF_Special =
    Ft_MF_SkipModel | Ft_MF_SkipItemVis | Ft_MF_UnkUpdatePhys |
    Ft_MF_FreezeState;

/* Neutral-B: Charge Shot (Grounded) */
static MotionFlags const ftSs_MF_SpecialN =
    ftSs_MF_Special | Ft_MF_KeepFastFall | Ft_MF_SkipThrowException;

/* Side-B: Homing Missile (Grounded) */
static MotionFlags const ftSs_MF_SpecialS =
    ftSs_MF_Special | Ft_MF_KeepGfx | Ft_MF_SkipThrowException;

/* Down-B: Morph Ball / Bomb Drop (Grounded) */
static MotionFlags const ftSs_MF_SpecialLw =
    ftSs_MF_Special | Ft_MF_KeepColAnimHitStatus | Ft_MF_SkipThrowException;

/* Up-B: Screw Attack (Grounded) */
static MotionFlags const ftSs_MF_SpecialHi =
    ftSs_MF_Special | Ft_MF_KeepFastFall | Ft_MF_KeepGfx | Ft_MF_KeepSfx;

/* Neutral-B: Charge Shot (Aerial) */
static MotionFlags const ftSs_MF_SpecialAirN =
    ftSs_MF_SpecialN | Ft_MF_SkipParasol;

/* Side-B: Homing Missile (Aerial) */
static MotionFlags const ftSs_MF_SpecialAirS =
    ftSs_MF_SpecialS | Ft_MF_SkipParasol;

/* Down-B: Morph Ball / Bomb Drop (Aerial) */
static MotionFlags const ftSs_MF_SpecialAirLw =
    ftSs_MF_SpecialLw | Ft_MF_SkipParasol;

/* Up-B: Screw Attack (Aerial) */
static MotionFlags const ftSs_MF_SpecialAirHi =
    ftSs_MF_SpecialHi | Ft_MF_SkipParasol;

/* Side-B: Super Missile (Smash Input, Grounded) */
static MotionFlags const ftSs_MF_SpecialSSmash =
    ftSs_MF_SpecialS | Ft_MF_SkipRumble;

/* Side-B: Super Missile (Smash Input, Aerial) */
static MotionFlags const ftSs_MF_SpecialAirSSmash =
    ftSs_MF_SpecialSSmash | Ft_MF_SkipParasol;

/* Aerial Z / Grapple Beam Tether Catch */
static MotionFlags const ftSs_MF_ZairCatch =
    Ft_MF_SkipModelPartVis | Ft_MF_SkipMetalB;

/**
 * @brief Samus-specific motion state IDs
 */
typedef enum ftSamus_MotionState {
    ftSs_MS_SpecialLw = ftCo_MS_Count, ///< Down-B: Morph Ball (Ground)
    ftSs_MS_SpecialAirLw,              ///< Down-B: Morph Ball (Air)
    ftSs_MS_SpecialNStart,  ///< Neutral-B: Charge Shot startup (Ground)
    ftSs_MS_SpecialNHold,   ///< Neutral-B: Charge Shot charging loop (Ground)
    ftSs_MS_SpecialNCancel, ///< Neutral-B: Charge Shot charge cancel (Ground)
    ftSs_MS_SpecialN,       ///< Neutral-B: Charge Shot fire (Ground)
    ftSs_MS_SpecialAirNStart, ///< Neutral-B: Charge Shot startup (Air)
    ftSs_MS_SpecialAirN,      ///< Neutral-B: Charge Shot fire (Air)
    ftSs_MS_SpecialS,         ///< Side-B: Homing Missile (Ground)
    ftSs_MS_SpecialSSmash,    ///< Side-B: Super Missile (Ground smash input)
    ftSs_MS_SpecialAirS,      ///< Side-B: Homing Missile (Air)
    ftSs_MS_SpecialAirSSmash, ///< Side-B: Super Missile (Air smash input)
    ftSs_MS_SpecialHi,        ///< Up-B: Screw Attack (Ground)
    ftSs_MS_SpecialAirHi,     ///< Up-B: Screw Attack (Air)
    ftSs_MS_SpecialLwBomb,    ///< Down-B: Bomb Drop release (Ground)
    ftSs_MS_SpecialAirLwBomb, ///< Down-B: Bomb Drop release (Air)
    ftSs_MS_AirCatch,         ///< Aerial Z-air Grapple Beam extend
    ftSs_MS_AirCatchHit,      ///< Aerial Z-air Grapple Beam connect / tether
    ftSs_MS_Count,
    ftSs_MS_SelfCount = ftSs_MS_Count - ftCo_MS_Count,
} ftSamus_MotionState;

/**
 * @brief Samus-specific animation submotion IDs
 */
typedef enum ftSs_Submotion {
    ftSs_SM_SpecialLw = ftCo_SM_Count, ///< Down-B: Morph Ball (Ground)
    ftSs_SM_SpecialAirLw,              ///< Down-B: Morph Ball (Air)
    ftSs_SM_SpecialNStart,  ///< Neutral-B: Charge Shot startup (Ground)
    ftSs_SM_SpecialNHold,   ///< Neutral-B: Charge Shot charging loop (Ground)
    ftSs_SM_SpecialNCancel, ///< Neutral-B: Charge Shot charge cancel (Ground)
    ftSs_SM_SpecialN,       ///< Neutral-B: Charge Shot fire (Ground)
    ftSs_SM_SpecialAirNStart, ///< Neutral-B: Charge Shot startup (Air)
    ftSs_SM_SpecialAirN,      ///< Neutral-B: Charge Shot fire (Air)
    ftSs_SM_SpecialS,         ///< Side-B: Homing Missile (Ground)
    ftSs_SM_SpecialSSmash,    ///< Side-B: Super Missile (Ground smash input)
    ftSs_SM_SpecialAirS,      ///< Side-B: Homing Missile (Air)
    ftSs_SM_SpecialAirSSmash, ///< Side-B: Super Missile (Air smash input)
    ftSs_SM_SpecialHi,        ///< Up-B: Screw Attack (Ground)
    ftSs_SM_SpecialAirHi,     ///< Up-B: Screw Attack (Air)
    ftSs_SM_SpecialLwBomb,    ///< Down-B: Bomb Drop release (Ground)
    ftSs_SM_SpecialAirLwBomb, ///< Down-B: Bomb Drop release (Air)
    ftSs_SM_AirCatch,         ///< Aerial Z-air Grapple Beam extend
    ftSs_SM_AirCatchHit,      ///< Aerial Z-air Grapple Beam connect / tether
    ftSs_SM_Count,
    ftSs_SM_SelfCount = ftSs_SM_Count - ftCo_SM_Count,
} ftSs_Submotion;

#endif
