#ifndef MELEE_FT_CHARA_FTZELDA_FORWARD_H
#define MELEE_FT_CHARA_FTZELDA_FORWARD_H

#include "ft/forward.h"
#include "ftCommon/forward.h"

static MotionFlags const ftZd_MF_Special ATTRIBUTE_USED =
    Ft_MF_SkipModel | Ft_MF_SkipItemVis | Ft_MF_UnkUpdatePhys |
    Ft_MF_FreezeState;

static MotionFlags const ftZd_MF_SpecialN ATTRIBUTE_USED =
    ftZd_MF_Special | Ft_MF_KeepFastFall | Ft_MF_SkipColAnim;

static MotionFlags const ftZd_MF_SpecialHi ATTRIBUTE_USED =
    ftZd_MF_Special | Ft_MF_KeepFastFall | Ft_MF_KeepGfx;

static MotionFlags const ftZd_MF_SpecialLw ATTRIBUTE_USED =
    ftZd_MF_Special | Ft_MF_KeepColAnimHitStatus;

static MotionFlags const ftZd_MF_SpecialS ATTRIBUTE_USED =
    ftZd_MF_Special | Ft_MF_KeepGfx | Ft_MF_SkipThrowException;

static MotionFlags const ftZd_MF_SpecialAirN ATTRIBUTE_USED =
    ftZd_MF_SpecialN | Ft_MF_SkipParasol;

static MotionFlags const ftZd_MF_SpecialAirHi ATTRIBUTE_USED =
    ftZd_MF_SpecialHi | Ft_MF_SkipParasol;

static MotionFlags const ftZd_MF_SpecialAirLw ATTRIBUTE_USED =
    ftZd_MF_SpecialLw | Ft_MF_SkipParasol;

static MotionFlags const ftZd_MF_SpecialAirS ATTRIBUTE_USED =
    ftZd_MF_SpecialS | Ft_MF_SkipParasol;

enum ftZelda_AS {
    ftZd_MS_SpecialN = ftCo_MS_Count,
    ftZd_MS_SpecialAirN,
    ftZd_MS_SpecialS_Start,
    ftZd_MS_SpecialS_Hold,
    ftZd_MS_SpecialS_End,

    ftZd_MS_SpecialAirS_Start,
    ftZd_MS_SpecialAirS_Hold,
    ftZd_MS_SpecialAirS_End,

    ftZd_MS_SpecialHi_Start,
    ftZd_MS_SpecialHi,
    ftZd_MS_SpecialHi_End,

    ftZd_MS_SpecialAirHi_Start,
    ftZd_MS_SpecialAirHi,
    ftZd_MS_SpecialAirHi_End,

    ftZd_MS_SpecialLw,
    ftZd_MS_SpecialLw_End,

    ftZd_MS_SpecialAirLw,
    ftZd_MS_SpecialAirLw_End,
};

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
} ftZd_Submotion;

#endif
