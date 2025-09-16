#ifndef MELEE_FT_CHARA_FTZELDA_FORWARD_H
#define MELEE_FT_CHARA_FTZELDA_FORWARD_H

#include "ft/forward.h"
#include "ftCommon/forward.h"

static MotionFlags const ftZd_MF_Special =
    Ft_MF_SkipModel | Ft_MF_SkipItemVis | Ft_MF_UnkUpdatePhys |
    Ft_MF_FreezeState;

static MotionFlags const ftZd_MF_SpecialN =
    ftZd_MF_Special | Ft_MF_KeepFastFall | Ft_MF_SkipColAnim;

static MotionFlags const ftZd_MF_SpecialHi =
    ftZd_MF_Special | Ft_MF_KeepFastFall | Ft_MF_KeepGfx;

static MotionFlags const ftZd_MF_SpecialLw =
    ftZd_MF_Special | Ft_MF_KeepColAnimHitStatus;

static MotionFlags const ftZd_MF_SpecialS =
    ftZd_MF_Special | Ft_MF_KeepGfx | Ft_MF_SkipThrowException;

static MotionFlags const ftZd_MF_SpecialAirN =
    ftZd_MF_SpecialN | Ft_MF_SkipParasol;

static MotionFlags const ftZd_MF_SpecialAirHi =
    ftZd_MF_SpecialHi | Ft_MF_SkipParasol;

static MotionFlags const ftZd_MF_SpecialAirLw =
    ftZd_MF_SpecialLw | Ft_MF_SkipParasol;

static MotionFlags const ftZd_MF_SpecialAirS =
    ftZd_MF_SpecialS | Ft_MF_SkipParasol;

typedef enum ftZd_MotionState {
    ftZd_MS_SpecialN = ftCo_MS_Count,
    ftZd_MS_SpecialAirN,
    ftZd_MS_SpecialSStart,
    /* 158 */ ftZd_MS_SpecialSLoop,
    /* 159 */ ftZd_MS_SpecialSEnd,
    /* 15A */ ftZd_MS_SpecialAirSStart,
    /* 15B */ ftZd_MS_SpecialAirSLoop,
    /* 15C */ ftZd_MS_SpecialAirSEnd,
    ftZd_MS_SpecialHiStart_0,
    ftZd_MS_SpecialHiStart_1,
    ftZd_MS_SpecialHi,
    ftZd_MS_SpecialAirHiStart_0,
    ftZd_MS_SpecialAirHiStart_1,
    ftZd_MS_SpecialAirHi,
    ftZd_MS_SpecialLw,
    ftZd_MS_SpecialLw2,
    ftZd_MS_SpecialAirLw,
    ftZd_MS_SpecialAirLw2,
    ftZd_MS_Count,
    ftZd_MS_SelfCount = ftZd_MS_Count - ftCo_MS_Count,
} ftZd_MotionState;

typedef enum ftZd_Submotion {
    ftZd_SM_SpecialN = ftCo_SM_Count,
    ftZd_SM_SpecialAirN,
    ftZd_SM_SpecialSStart,
    ftZd_SM_SpecialSLoop,
    ftZd_SM_SpecialSEnd,
    ftZd_SM_SpecialAirSStart,
    ftZd_SM_SpecialAirSLoop,
    ftZd_SM_SpecialAirSEnd,
    ftZd_SM_SpecialHiStart,
    ftZd_SM_SpecialHi,
    ftZd_SM_SpecialAirHiStart,
    ftZd_SM_SpecialAirHi,
    ftZd_SM_SpecialLw,
    ftZd_SM_SpecialLw2,
    ftZd_SM_SpecialAirLw,
    ftZd_SM_SpecialAirLw2,
    ftZd_SM_Count,
    ftZd_SM_SelfCount = ftZd_SM_Count - ftCo_SM_Count,
} ftZd_Submotion;

#endif
