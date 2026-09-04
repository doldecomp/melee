#ifndef MELEE_FT_CHARA_FTMARIO_FORWARD_H
#define MELEE_FT_CHARA_FTMARIO_FORWARD_H

#include "ft/forward.h"
#include "ftCommon/forward.h"

static MotionFlags const ftMr_MF_Special =
    Ft_MF_SkipModel | Ft_MF_SkipItemVis | Ft_MF_UnkUpdatePhys |
    Ft_MF_FreezeState;

static MotionFlags const ftMr_MF_SpecialN =
    ftMr_MF_Special | Ft_MF_KeepFastFall | Ft_MF_SkipThrowException;

static MotionFlags const ftMr_MF_SpecialHi =
    ftMr_MF_Special | Ft_MF_KeepFastFall | Ft_MF_KeepGfx | Ft_MF_KeepSfx;

static MotionFlags const ftMr_MF_SpecialLw =
    ftMr_MF_Special | Ft_MF_KeepColAnimHitStatus | Ft_MF_KeepSfx;

static MotionFlags const ftMr_MF_SpecialAirN =
    ftMr_MF_SpecialN | Ft_MF_SkipParasol;

static MotionFlags const ftMr_MF_SpecialAirHi =
    ftMr_MF_SpecialHi | Ft_MF_SkipParasol;

static MotionFlags const ftMr_MF_SpecialAirLw =
    ftMr_MF_SpecialLw | Ft_MF_SkipParasol;

static MotionFlags const ftMr_MF_SpecialS =
    ftMr_MF_Special | Ft_MF_KeepGfx | Ft_MF_SkipModel | Ft_MF_SkipColAnim;

typedef enum ftMario_MotionState {
    ftMr_MS_AppealSR = ftCo_MS_Count,
    ftMr_MS_AppealSL,
    ftMr_MS_SpecialN,
    ftMr_MS_SpecialAirN,
    ftMr_MS_SpecialS,
    ftMr_MS_SpecialAirS,
    ftMr_MS_SpecialHi,
    ftMr_MS_SpecialAirHi,
    ftMr_MS_SpecialLw,
    ftMr_MS_SpecialAirLw,
    ftMr_MS_Count,
    ftMr_MS_SelfCount = ftMr_MS_Count - ftCo_MS_Count,
} ftMario_MotionState;

typedef enum ftMr_Submotion {
    ftMr_SM_SpecialN = ftCo_SM_Count,
    ftMr_SM_SpecialAirN,
    ftMr_SM_SpecialS,
    ftMr_SM_SpecialAirS,
    ftMr_SM_SpecialHi,
    ftMr_SM_SpecialAirHi,
    ftMr_SM_SpecialLw,
    ftMr_SM_SpecialAirLw,
    ftMr_SM_Count,
    ftMr_SM_SelfCount = ftMr_SM_Count - ftCo_SM_Count,
} ftMr_Submotion;

#endif
