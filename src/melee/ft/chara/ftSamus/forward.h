#ifndef MELEE_FT_CHARA_FTSAMUS_FORWARD_H
#define MELEE_FT_CHARA_FTSAMUS_FORWARD_H

#include <platform.h>
#include "ft/forward.h"
#include "ftCommon/forward.h"

static MotionFlags const ftSs_MF_Special ATTRIBUTE_USED =
    Ft_MF_SkipModel | Ft_MF_SkipItemVis | Ft_MF_UnkUpdatePhys |
    Ft_MF_FreezeState;

static MotionFlags const ftSs_MF_SpecialN ATTRIBUTE_USED =
    ftSs_MF_Special | Ft_MF_KeepFastFall | Ft_MF_SkipThrowException;

static MotionFlags const ftSs_MF_SpecialS ATTRIBUTE_USED =
    ftSs_MF_Special | Ft_MF_KeepGfx | Ft_MF_SkipThrowException;

static MotionFlags const ftSs_MF_SpecialLw ATTRIBUTE_USED =
    ftSs_MF_Special | Ft_MF_KeepColAnimHitStatus | Ft_MF_SkipThrowException;

static MotionFlags const ftSs_MF_SpecialHi ATTRIBUTE_USED =
    ftSs_MF_Special | Ft_MF_KeepFastFall | Ft_MF_KeepGfx | Ft_MF_KeepSfx;

static MotionFlags const ftSs_MF_SpecialAirN ATTRIBUTE_USED =
    ftSs_MF_SpecialN | Ft_MF_SkipParasol;

static MotionFlags const ftSs_MF_SpecialAirS ATTRIBUTE_USED =
    ftSs_MF_SpecialS | Ft_MF_SkipParasol;

static MotionFlags const ftSs_MF_SpecialAirLw ATTRIBUTE_USED =
    ftSs_MF_SpecialLw | Ft_MF_SkipParasol;

static MotionFlags const ftSs_MF_SpecialAirHi ATTRIBUTE_USED =
    ftSs_MF_SpecialHi | Ft_MF_SkipParasol;

static MotionFlags const ftSs_MF_SpecialSSmash ATTRIBUTE_USED =
    ftSs_MF_SpecialS | Ft_MF_SkipRumble;

static MotionFlags const ftSs_MF_SpecialAirSSmash ATTRIBUTE_USED =
    ftSs_MF_SpecialSSmash | Ft_MF_SkipParasol;

static MotionFlags const ftSs_MF_ZairCatch ATTRIBUTE_USED =
    Ft_MF_SkipModelPartVis | Ft_MF_SkipMetalB;

typedef enum ftSamus_MotionState {
    ftSs_MS_SpecialLw = ftCo_MS_Count,
    ftSs_MS_SpecialAirLw,
    ftSs_MS_SpecialN_Start,
    ftSs_MS_SpecialN_Loop,
    ftSs_MS_SpecialN_End,
    ftSs_MS_SpecialN_Shoot,
    ftSs_MS_SpecialAirN_Start,
    ftSs_MS_SpecialAirN_Shoot,
    ftSs_MS_SpecialS,

    /// @todo name
    ftSs_MS_SpecialS_Smash,

    ftSs_MS_SpecialAirS,
    ftSs_MS_SpecialAir_Smash,
    ftSs_MS_SpecialHi,
    ftSs_MS_SpecialAirHi,

    /// @todo name
    ftSs_MS_SpecialLw_BombEnd,
    ftSs_MS_SpecialAirLw_Bomb,

    /// @todo name
    ftSs_MS_Zair,
    ftSs_MS_ZairCatch,
} ftSamus_MotionState;

typedef enum ftSs_AnimId {
    ftSs_AnimId_SpecialLw = ftCo_AnimId_Count,
    ftSs_AnimId_SpecialAirLw,
    ftSs_AnimId_SpecialNStart,
    ftSs_AnimId_SpecialNLoop,
    ftSs_AnimId_SpecialNEnd,
    ftSs_AnimId_SpecialNShoot,
    ftSs_AnimId_SpecialAirNStart,
    ftSs_AnimId_SpecialAirNShoot,
    ftSs_AnimId_SpecialS,
    ftSs_AnimId_SpecialSSmash,
    ftSs_AnimId_SpecialAirS,
    ftSs_AnimId_SpecialAirSmash,
    ftSs_AnimId_SpecialHi,
    ftSs_AnimId_SpecialAirHi,
    ftSs_AnimId_SpecialLwBombEnd,
    ftSs_AnimId_SpecialAirLwBomb,
    ftCo_AnimId_Zair,
    ftCo_AnimId_ZairCatch,
} ftSs_AnimId;

#endif
