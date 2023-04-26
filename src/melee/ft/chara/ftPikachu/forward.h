#ifndef MELEE_FT_CHARA_FTPIKACHU_FORWARD_H
#define MELEE_FT_CHARA_FTPIKACHU_FORWARD_H

#include <platform.h>
#include "ft/forward.h"
#include "ftCommon/forward.h"

static MotionFlags const ftPk_MF_Special ATTRIBUTE_USED =
    Ft_MF_SkipModel | Ft_MF_SkipItemVis | Ft_MF_UnkUpdatePhys |
    Ft_MF_FreezeState;

static MotionFlags const ftPk_MF_SpecialLw ATTRIBUTE_USED =
    ftPk_MF_Special | Ft_MF_KeepColAnimHitStatus;

static MotionFlags const ftPk_MF_SpecialN ATTRIBUTE_USED =
    ftPk_MF_Special | Ft_MF_KeepFastFall | Ft_MF_SkipThrowException;

static MotionFlags const ftPk_MF_SpecialHi ATTRIBUTE_USED =
    ftPk_MF_Special | Ft_MF_KeepFastFall | Ft_MF_KeepGfx |
    Ft_MF_SkipThrowException;

static MotionFlags const ftPk_MF_SpecialS ATTRIBUTE_USED =
    ftPk_MF_Special | Ft_MF_KeepGfx | Ft_MF_KeepSfx;

static MotionFlags const ftPk_MF_SpecialAirLw ATTRIBUTE_USED =
    ftPk_MF_SpecialLw | Ft_MF_SkipParasol;

static MotionFlags const ftPk_MF_SpecialAirN ATTRIBUTE_USED =
    ftPk_MF_SpecialN | Ft_MF_SkipParasol;

static MotionFlags const ftPk_MF_SpecialAirHi ATTRIBUTE_USED =
    ftPk_MF_SpecialHi | Ft_MF_SkipParasol;

static MotionFlags const ftPk_MF_SpecialAirS ATTRIBUTE_USED =
    ftPk_MF_SpecialS | Ft_MF_SkipParasol;

typedef enum ftPikachu_MotionState {
    ftPk_MS_SpecialN = ftCo_MS_Count,
    ftPk_MS_SpecialAirN,
    ftPk_MS_SpecialS_Start,
    ftPk_MS_SpecialS_Charge,
    ftPk_MS_Unk_345,
    ftPk_MS_SpecialS_Landing,
    ftPk_MS_SpecialS_Launch,
    ftPk_MS_SpecialAirS_Start,
    ftPk_MS_SpecialAirS_Charge,
    ftPk_MS_SpecialAirS,
    ftPk_MS_SpecialAirS_End,
    ftPk_MS_SpecialAirS_Launch,
    ftPk_MS_SpecialHi_Start,
    ftPk_MS_SpecialHi,
    ftPk_MS_SpecialHi_End,
    ftPk_MS_SpecialAirHi_Start,
    ftPk_MS_SpecialAir,
    ftPk_MS_SpecialAir_End,
    ftPk_MS_SpecialLw_Start,
    ftPk_MS_SpecialLw,
    ftPk_MS_SpecialLw_Hit,
    ftPk_MS_SpecialLw_End,
    ftPk_MS_SpecialAirLw_Start,
    ftPk_MS_SpecialAirLw,
    ftPk_MS_SpecialAirLw_Hit,
    ftPk_MS_SpecialAirLw_End,
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
} ftPk_Submotion;

#endif
