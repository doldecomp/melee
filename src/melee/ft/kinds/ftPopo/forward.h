#ifndef MELEE_FT_CHARA_FTPOPO_FORWARD_H
#define MELEE_FT_CHARA_FTPOPO_FORWARD_H

/**
 * @file forward.h
 * @brief Forward declarations and state enums for Ice Climbers (Popo)
 * @details Defines motion flags, motion state IDs, and submotion indices
 * for Popo and Nana special moves (Neutral-B, Side-B, Up-B, Down-B).
 * Module prefix: ftPp
 */

#include <melee/ft/forward.h>
#include <melee/ft/kinds/ftCommon/forward.h>

/// Base motion flags common to Ice Climber special moves
static MotionFlags const ftPp_MF_Special =
    Ft_MF_SkipModel | Ft_MF_SkipItemVis | Ft_MF_UnkUpdatePhys |
    Ft_MF_FreezeState;

/// Motion flags for Down-B: Blizzard (grounded)
static MotionFlags const ftPp_MF_SpecialLw =
    ftPp_MF_Special | Ft_MF_KeepColAnimHitStatus;

/// Motion flags for Neutral-B: Ice Shot (grounded)
static MotionFlags const ftPp_MF_SpecialN =
    ftPp_MF_Special | Ft_MF_KeepFastFall | Ft_MF_SkipThrowException;

/// Motion flags for Side-B: Squall Hammer (grounded)
static MotionFlags const ftPp_MF_SpecialS =
    ftPp_MF_Special | Ft_MF_KeepGfx | Ft_MF_KeepSfx;

/// Motion flags for Up-B: Belay (grounded)
static MotionFlags const ftPp_MF_SpecialHi =
    ftPp_MF_SpecialS | Ft_MF_KeepFastFall;

/// Motion flags for Down-B: Blizzard (aerial)
static MotionFlags const ftPp_MF_MS_358 =
    ftPp_MF_SpecialLw | Ft_MF_SkipParasol;

/// Motion flags for Neutral-B: Ice Shot (aerial)
static MotionFlags const ftPp_MF_SpecialAirN =
    ftPp_MF_SpecialN | Ft_MF_SkipParasol;

/// Motion flags for Side-B: Squall Hammer (aerial)
static MotionFlags const ftPp_MF_SpecialAirS =
    ftPp_MF_SpecialS | Ft_MF_SkipParasol;

/// Motion flags for Up-B: Belay (aerial)
static MotionFlags const ftPp_MF_SpecialAirHi =
    ftPp_MF_SpecialHi | Ft_MF_SkipParasol;

/// Ground/air collision transition flags for Up-B (Belay)
static MotionFlags const ftPp_MF_SpecialHi_Coll =
    ftCommon_GroundAirColl_MF | Ft_MF_KeepGfx | Ft_MF_SkipHit;

/// Ground/air collision transition flags for Down-B (Blizzard)
static MotionFlags const ftPp_MF_SpecialLw_Coll =
    ftCommon_GroundAirColl_MF | Ft_MF_KeepGfx | Ft_MF_KeepSfx;

/// Ground/air collision transition flags for Side-B (Squall Hammer)
static MotionFlags const ftPp_MF_SpecialS_Coll =
    ftCommon_GroundAirColl_MF | Ft_MF_KeepGfx | Ft_MF_SkipHit | Ft_MF_KeepSfx;

/**
 * @brief Character-specific motion states for Ice Climbers (Popo)
 * @details Covers states 341 through 366 (ftCo_MS_Count + 0 through + 25)
 */
typedef enum ftPopo_MotionState {
    ftPp_MS_SpecialN = ftCo_MS_Count, ///< 341: Neutral-B (Ice Shot) Grounded
    ftPp_MS_SpecialAirN,              ///< 342: Neutral-B (Ice Shot) Aerial
    ftPp_MS_SpecialS1,        ///< 343: Side-B (Squall Hammer) Solo Grounded
    ftPp_MS_SpecialS2,        ///< 344: Side-B (Squall Hammer) Paired Grounded
    ftPp_MS_SpecialAirS1,     ///< 345: Side-B (Squall Hammer) Solo Aerial
    ftPp_MS_SpecialAirS2,     ///< 346: Side-B (Squall Hammer) Paired Aerial
    ftPp_MS_SpecialHiStart_0, ///< 347: Up-B (Belay) Partnered Grounded Start
    ftPp_MS_SpecialHiThrow_0, ///< 348: Up-B (Belay) Partnered Grounded Throw
    ftPp_MS_SpecialHiThrow2,  ///< 349: Up-B (Belay) Partnered Grounded Popo
                              ///< Rise
    ftPp_MS_SpecialHiStart_1, ///< 350: Up-B (Belay) Solo Fail Grounded Start
    ftPp_MS_SpecialHiThrow_1, ///< 351: Up-B (Belay) Solo Fail Grounded Throw
    ftPp_MS_SpecialAirHiStart_0, ///< 352: Up-B (Belay) Partnered Aerial Start
    ftPp_MS_SpecialAirHiThrow_0, ///< 353: Up-B (Belay) Partnered Aerial Throw
    ftPp_MS_SpecialAirHiThrow2,  ///< 354: Up-B (Belay) Partnered Aerial Popo
                                 ///< Rise
    ftPp_MS_SpecialAirHiStart_1, ///< 355: Up-B (Belay) Solo Fail Aerial Start
    ftPp_MS_SpecialAirHiThrow_1, ///< 356: Up-B (Belay) Solo Fail Aerial Throw
    ftPp_MS_SpecialLw,           ///< 357: Down-B (Blizzard) Grounded
    ftPp_MS_SpecialAirLw,        ///< 358: Down-B (Blizzard) Aerial
    ftPp_MS_SpecialS_0,  ///< 359: Side-B (Squall Hammer) Auxiliary State 0
    ftPp_MS_SpecialS_1,  ///< 360: Side-B (Squall Hammer) Auxiliary State 1
    ftPp_MS_SpecialHi_0, ///< 361: Up-B (Belay) Nana Partnered State 0
    ftPp_MS_SpecialHi_1, ///< 362: Up-B (Belay) Nana Partnered State 1
    ftPp_MS_SpecialHi_2, ///< 363: Up-B (Belay) Nana Partnered State 2
    ftPp_MS_SpecialHi_3, ///< 364: Up-B (Belay) Nana Partnered State 3
    ftPp_MS_SpecialHi_4, ///< 365: Up-B (Belay) Nana Partnered State 4
    ftPp_MS_SpecialHi_5, ///< 366: Up-B (Belay) Nana Partnered State 5
    ftPp_MS_Count,
    ftPp_MS_SelfCount = ftPp_MS_Count - ftCo_MS_Count,
} ftPopo_MotionState;

/**
 * @brief Character-specific submotions for Ice Climbers (Popo)
 * @details Animation submotion IDs corresponding to motion states
 */
typedef enum ftPp_Submotion {
    ftPp_SM_SpecialN = ftCo_SM_Count, ///< Neutral-B (Ice Shot) Grounded
    ftPp_SM_SpecialAirN,              ///< Neutral-B (Ice Shot) Aerial
    ftPp_SM_SpecialS1,                ///< Side-B (Squall Hammer) Solo Grounded
    ftPp_SM_SpecialS2,           ///< Side-B (Squall Hammer) Paired Grounded
    ftPp_SM_SpecialAirS1,        ///< Side-B (Squall Hammer) Solo Aerial
    ftPp_SM_SpecialAirS2,        ///< Side-B (Squall Hammer) Paired Aerial
    ftPp_SM_SpecialHiStart_0,    ///< Up-B (Belay) Partnered Grounded Start
    ftPp_SM_SpecialHiThrow_0,    ///< Up-B (Belay) Partnered Grounded Throw
    ftPp_SM_SpecialHiThrow2,     ///< Up-B (Belay) Partnered Grounded Popo Rise
    ftPp_SM_SpecialHiStart_1,    ///< Up-B (Belay) Solo Fail Grounded Start
    ftPp_SM_SpecialHiThrow_1,    ///< Up-B (Belay) Solo Fail Grounded Throw
    ftPp_SM_SpecialAirHiStart_0, ///< Up-B (Belay) Partnered Aerial Start
    ftPp_SM_SpecialAirHiThrow_0, ///< Up-B (Belay) Partnered Aerial Throw
    ftPp_SM_SpecialAirHiThrow2,  ///< Up-B (Belay) Partnered Aerial Popo Rise
    ftPp_SM_SpecialAirHiStart_1, ///< Up-B (Belay) Solo Fail Aerial Start
    ftPp_SM_SpecialAirHiThrow_1, ///< Up-B (Belay) Solo Fail Aerial Throw
    ftPp_SM_SpecialLw,           ///< Down-B (Blizzard) Grounded
    ftPp_SM_SpecialAirLw,        ///< Down-B (Blizzard) Aerial
    ftPp_SM_SpecialS_0,  ///< Side-B (Squall Hammer) Auxiliary Submotion 0
    ftPp_SM_SpecialS_1,  ///< Side-B (Squall Hammer) Auxiliary Submotion 1
    ftPp_SM_SpecialHi_0, ///< Up-B (Belay) Nana Partnered Submotion 0
    ftPp_SM_SpecialHi_1, ///< Up-B (Belay) Nana Partnered Submotion 1
    ftPp_SM_SpecialHi_2, ///< Up-B (Belay) Nana Partnered Submotion 2
    ftPp_SM_SpecialHi_3, ///< Up-B (Belay) Nana Partnered Submotion 3
    ftPp_SM_SpecialHi_4, ///< Up-B (Belay) Nana Partnered Submotion 4
    ftPp_SM_SpecialHi_5, ///< Up-B (Belay) Nana Partnered Submotion 5
    ftPp_SM_Count,
    ftPp_SM_SelfCount = ftPp_SM_Count - ftCo_SM_Count,
} ftPp_Submotion;

#endif
