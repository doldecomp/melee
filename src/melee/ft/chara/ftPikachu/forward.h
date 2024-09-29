#ifndef MELEE_FT_CHARA_FTPIKACHU_FORWARD_H
#define MELEE_FT_CHARA_FTPIKACHU_FORWARD_H

#include <platform.h>

#include "ft/forward.h"
#include "ftCommon/forward.h"

static MotionFlags const ftPk_MF_Special =
    Ft_MF_SkipModel | Ft_MF_SkipItemVis | Ft_MF_UnkUpdatePhys |
    Ft_MF_FreezeState;

static MotionFlags const ftPk_MF_SpecialLw =
    ftPk_MF_Special | Ft_MF_KeepColAnimHitStatus;

static MotionFlags const ftPk_MF_SpecialN =
    ftPk_MF_Special | Ft_MF_KeepFastFall | Ft_MF_SkipThrowException;

static MotionFlags const ftPk_MF_SpecialHi =
    ftPk_MF_Special | Ft_MF_KeepFastFall | Ft_MF_KeepGfx |
    Ft_MF_SkipThrowException;

static MotionFlags const ftPk_MF_SpecialS =
    ftPk_MF_Special | Ft_MF_KeepGfx | Ft_MF_KeepSfx;

static MotionFlags const ftPk_MF_SpecialAirLw =
    ftPk_MF_SpecialLw | Ft_MF_SkipParasol;

static MotionFlags const ftPk_MF_SpecialAirN =
    ftPk_MF_SpecialN | Ft_MF_SkipParasol;

static MotionFlags const ftPk_MF_SpecialAirHi =
    ftPk_MF_SpecialHi | Ft_MF_SkipParasol;

static MotionFlags const ftPk_MF_SpecialAirS =
    ftPk_MF_SpecialS | Ft_MF_SkipParasol;

typedef enum ftPikachu_MotionState {
    ftPk_MS_SpecialN = ftCo_MS_Count,
    ftPk_MS_SpecialAirN,
    ftPk_MS_SpecialSStart,
    ftPk_MS_SpecialSHold,
    ftPk_MS_SpecialS1,
    ftPk_MS_SpecialSEnd,
    ftPk_MS_SpecialS0,
    ftPk_MS_SpecialAirSStart,
    ftPk_MS_SpecialAirSHold,
    ftPk_MS_SpecialAirS1,
    ftPk_MS_SpecialAirSEnd,
    ftPk_MS_SpecialAirS0,
    ftPk_MS_SpecialHiStart0,
    ftPk_MS_SpecialHiStart1,
    ftPk_MS_SpecialHiEnd,
    ftPk_MS_SpecialAirHiStart0,
    ftPk_MS_SpecialAirHiStart1,
    ftPk_MS_SpecialAirHiEnd,
    ftPk_MS_SpecialLwStart,
    ftPk_MS_SpecialLwLoop0,
    ftPk_MS_SpecialLwLoop1,
    ftPk_MS_SpecialLwEnd,
    ftPk_MS_SpecialAirLwStart,
    ftPk_MS_SpecialAirLwLoop0,
    ftPk_MS_SpecialAirLwLoop1,
    ftPk_MS_SpecialAirLwEnd,
    ftPk_MS_Count,
    ftPk_MS_SelfCount = ftPk_MS_Count - ftCo_MS_Count,
} ftPikachu_MotionState;

typedef enum ftPk_Submotion {
    ftPk_SM_SpecialN = ftCo_SM_Count,
    ftPk_SM_SpecialAirN,
    ftPk_SM_SpecialSStart,
    ftPk_SM_SpecialSHold,
    ftPk_SM_SpecialS0,
    ftPk_SM_SpecialS1,
    ftPk_SM_SpecialSEnd,
    ftPk_SM_SpecialAirSStart,
    ftPk_SM_SpecialAirSHold,
    ftPk_SM_SpecialS,
    ftPk_SM_SpecialAirSEnd,
    ftPk_SM_SpecialHiStart0,
    ftPk_SM_SpecialHiStart1,
    ftPk_SM_SpecialHiEnd,
    ftPk_SM_SpecialAirHiStart0,
    ftPk_SM_SpecialAirHiStart1,
    ftPk_SM_SpecialAirHiEnd,
    ftPk_SM_SpecialLwStart,
    ftPk_SM_SpecialLwLoop0,
    ftPk_SM_SpecialLwLoop1,
    ftPk_SM_SpecialLwEnd,
    ftPk_SM_SpecialAirLwStart,
    ftPk_SM_SpecialAirLwLoop0,
    ftPk_SM_SpecialAirLwLoop1,
    ftPk_SM_SpecialAirLwEnd,
    ftPk_SM_Count,
    ftPk_SM_SelfCount = ftPk_SM_Count - ftCo_SM_Count,
} ftPk_Submotion;

#endif
