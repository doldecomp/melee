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

typedef enum ftPk_AnimId {
    ftPk_AnimId_SpecialN = ftCo_AnimId_Count,
    ftPk_AnimId_SpecialAirN,
    ftPk_AnimId_SpecialSStart,
    ftPk_AnimId_SpecialSCharge,
    ftPk_AnimId_SpecialSLaunch,
    ftPk_AnimId_Unk300,
    ftPk_AnimId_SpecialSLanding,
    ftPk_AnimId_SpecialAirSStart,
    ftPk_AnimId_SpecialAirSCharge,
    ftPk_AnimId_SpecialAirSLaunch,
    ftPk_AnimId_SpecialAirSEnd,
    ftPk_AnimId_SpecialHiStart,
    ftPk_AnimId_SpecialHi,
    ftPk_AnimId_SpecialHiEnd,
    ftPk_AnimId_SpecialAirHiStart,
    ftPk_AnimId_SpecialAirHi,
    ftPk_AnimId_SpecialAirHiEnd,
    ftPk_AnimId_SpecialLwStart,
    ftPk_AnimId_SpecialLw,
    ftPk_AnimId_SpecialLwHit,
    ftPk_AnimId_SpecialLwEnd,
    ftPk_AnimId_SpecialAirLwStart,
    ftPk_AnimId_SpecialAirLw,
    ftPk_AnimId_SpecialAirLwHit,
    ftPk_AnimId_SpecialAirLwEnd,
} ftPk_AnimId;

#endif
