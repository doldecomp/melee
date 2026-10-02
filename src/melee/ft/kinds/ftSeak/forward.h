/**
 * @file forward.h
 * @brief Forward declarations and motion state definitions for Sheik (ftSeak).
 * @details Contains motion flag bitmasks, motion state enumeration, and
 * submotion enumeration for Sheik's special moves: Needle Storm (Neutral-B),
 * Chain (Side-B), Vanish (Up-B), and Transform (Down-B). Module prefix: ftSk
 * (Fighter: Sheik)
 */

#ifndef MELEE_FT_CHARA_FTSEAK_FORWARD_H
#define MELEE_FT_CHARA_FTSEAK_FORWARD_H

#include <melee/ft/forward.h>
#include <melee/ft/kinds/ftCommon/forward.h>

/// Base motion flags shared across Sheik's special moves
static MotionFlags const ftSk_MF_Special =
    Ft_MF_SkipModel | Ft_MF_SkipItemVis | Ft_MF_UnkUpdatePhys |
    Ft_MF_FreezeState;

/// Motion flags for grounded Side-B (Chain)
static MotionFlags const ftSk_MF_SpecialS = ftSk_MF_Special | Ft_MF_KeepGfx;

/// Motion flags for grounded Down-B (Transform)
static MotionFlags const ftSk_MF_SpecialLw =
    ftSk_MF_Special | Ft_MF_KeepColAnimHitStatus;

/// Motion flags for grounded Neutral-B (Needle Storm)
static MotionFlags const ftSk_MF_SpecialN =
    ftSk_MF_Special | Ft_MF_KeepFastFall | Ft_MF_SkipThrowException;

/// Motion flags for grounded Up-B (Vanish)
static MotionFlags const ftSk_MF_SpecialHi =
    ftSk_MF_SpecialS | Ft_MF_KeepFastFall | Ft_MF_KeepSfx;

/// Motion flags for aerial Side-B (Chain)
static MotionFlags const ftSk_MF_SpecialAirS =
    ftSk_MF_SpecialS | Ft_MF_SkipParasol;

/// Motion flags for aerial Down-B (Transform)
static MotionFlags const ftSk_MF_SpecialAirLw =
    ftSk_MF_SpecialLw | Ft_MF_SkipParasol;

/// Motion flags for aerial Neutral-B (Needle Storm)
static MotionFlags const ftSk_MF_SpecialAirN =
    ftSk_MF_SpecialN | Ft_MF_SkipParasol;

/// Motion flags for aerial Up-B (Vanish)
static MotionFlags const ftSk_MF_SpecialAirHi =
    ftSk_MF_SpecialHi | Ft_MF_SkipParasol;

/// Motion flags for grounded Side-B (Chain) loop state
static MotionFlags const ftSk_MF_SpecialSLoop = ftSk_MF_SpecialS | Ft_MF_Unk19;

/// Motion flags for grounded Neutral-B (Needle Storm) charge loop state
static MotionFlags const ftSk_MF_SpecialNLoop = ftSk_MF_SpecialN | Ft_MF_Unk19;

/// Motion flags for aerial Side-B (Chain) loop state
static MotionFlags const ftSk_MF_SpecialAirSLoop =
    ftSk_MF_SpecialSLoop | Ft_MF_SkipParasol;

/// Motion flags for aerial Neutral-B (Needle Storm) charge loop state
static MotionFlags const ftSk_MF_SpecialAirNLoop =
    ftSk_MF_SpecialNLoop | Ft_MF_SkipParasol;

/**
 * @brief Sheik's character-specific motion states (action states 341-364).
 */
typedef enum ftSeak_MotionState {
    ftSk_MS_SpecialNStart =
        ftCo_MS_Count,    ///< 341: Grounded Neutral-B (Needle Storm) startup
    ftSk_MS_SpecialNLoop, ///< 342: Grounded Neutral-B (Needle Storm) charging
                          ///< loop
    ftSk_MS_SpecialNCancel, ///< 343: Grounded Neutral-B (Needle Storm) shield
                            ///< cancel
    ftSk_MS_SpecialNEnd,    ///< 344: Grounded Neutral-B (Needle Storm) throw
                            ///< needles
    ftSk_MS_SpecialAirNStart, ///< 345: Aerial Neutral-B (Needle Storm) startup
    ftSk_MS_SpecialAirNLoop, ///< 346: Aerial Neutral-B (Needle Storm) charging
                             ///< loop
    ftSk_MS_SpecialAirNCancel, ///< 347: Aerial Neutral-B (Needle Storm) air
                               ///< dodge/cancel
    ftSk_MS_SpecialAirNEnd,    ///< 348: Aerial Neutral-B (Needle Storm) throw
                               ///< needles
    ftSk_MS_SpecialSStart,     ///< 349: Grounded Side-B (Chain) startup
    ftSk_MS_SpecialS,    ///< 350: Grounded Side-B (Chain) active whip loop
    ftSk_MS_SpecialSEnd, ///< 351: Grounded Side-B (Chain) retract/end
    ftSk_MS_SpecialAirSStart, ///< 352: Aerial Side-B (Chain) startup
    ftSk_MS_SpecialAirS,      ///< 353: Aerial Side-B (Chain) active whip loop
    ftSk_MS_SpecialAirSEnd,   ///< 354: Aerial Side-B (Chain) retract/end
    ftSk_MS_SpecialHiStart_0, ///< 355: Grounded Up-B (Vanish) startup /
                              ///< explosion
    ftSk_MS_SpecialHiStart_1, ///< 356: Grounded Up-B (Vanish) invisible travel
    ftSk_MS_SpecialHi, ///< 357: Grounded Up-B (Vanish) reappearance / end
    ftSk_MS_SpecialAirHiStart_0, ///< 358: Aerial Up-B (Vanish) startup /
                                 ///< explosion
    ftSk_MS_SpecialAirHiStart_1, ///< 359: Aerial Up-B (Vanish) invisible
                                 ///< travel
    ftSk_MS_SpecialAirHi,  ///< 360: Aerial Up-B (Vanish) reappearance / end
    ftSk_MS_SpecialLw,     ///< 361: Grounded Down-B (Transform) phase 1
                           ///< (disappearing)
    ftSk_MS_SpecialLw2,    ///< 362: Grounded Down-B (Transform) phase 2
                           ///< (reappearing)
    ftSk_MS_SpecialAirLw,  ///< 363: Aerial Down-B (Transform) phase 1
                           ///< (disappearing)
    ftSk_MS_SpecialAirLw2, ///< 364: Aerial Down-B (Transform) phase 2
                           ///< (reappearing)
    ftSk_MS_Count,
    ftSk_MS_SelfCount = ftSk_MS_Count - ftCo_MS_Count,
} ftSeak_MotionState;

/**
 * @brief Sheik's submotion animation indices.
 */
typedef enum ftSk_Submotion {
    ftSk_SM_SpecialNStart =
        ftCo_SM_Count, ///< Grounded Neutral-B (Needle Storm) startup animation
    ftSk_SM_SpecialNLoop, ///< Grounded Neutral-B (Needle Storm) loop animation
    ftSk_SM_SpecialNCancel, ///< Grounded Neutral-B (Needle Storm) cancel
                            ///< animation
    ftSk_SM_SpecialNEnd, ///< Grounded Neutral-B (Needle Storm) throw animation
    ftSk_SM_SpecialAirNStart,  ///< Aerial Neutral-B (Needle Storm) startup
                               ///< animation
    ftSk_SM_SpecialAirNLoop,   ///< Aerial Neutral-B (Needle Storm) loop
                               ///< animation
    ftSk_SM_SpecialAirNCancel, ///< Aerial Neutral-B (Needle Storm) cancel
                               ///< animation
    ftSk_SM_SpecialAirNEnd,    ///< Aerial Neutral-B (Needle Storm) throw
                               ///< animation
    ftSk_SM_SpecialSStart,     ///< Grounded Side-B (Chain) startup animation
    ftSk_SM_SpecialSEnd,       ///< Grounded Side-B (Chain) retract animation
    ftSk_SM_SpecialS,          ///< Grounded Side-B (Chain) whip loop animation
    ftSk_SM_SpecialAirSStart,  ///< Aerial Side-B (Chain) startup animation
    ftSk_SM_SpecialAirSEnd,    ///< Aerial Side-B (Chain) retract animation
    ftSk_SM_SpecialAirS,       ///< Aerial Side-B (Chain) whip loop animation
    ftSk_SM_SpecialHiStart,    ///< Grounded Up-B (Vanish) startup animation
    ftSk_SM_SpecialHi, ///< Grounded Up-B (Vanish) reappearance animation
    ftSk_SM_SpecialAirHiStart, ///< Aerial Up-B (Vanish) startup animation
    ftSk_SM_SpecialAirHi,      ///< Aerial Up-B (Vanish) reappearance animation
    ftSk_SM_SpecialLw,     ///< Grounded Down-B (Transform) phase 1 animation
    ftSk_SM_SpecialLw2,    ///< Grounded Down-B (Transform) phase 2 animation
    ftSk_SM_SpecialAirLw,  ///< Aerial Down-B (Transform) phase 1 animation
    ftSk_SM_SpecialAirLw2, ///< Aerial Down-B (Transform) phase 2 animation
    ftSk_SM_Count,
    ftSk_SM_SelfCount = ftSk_SM_Count - ftCo_SM_Count,
} ftSk_Submotion;

typedef struct itChainSegment itChainSegment;

#endif
