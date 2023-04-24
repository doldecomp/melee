#ifndef MELEE_FT_CHARA_FTMARIO_FORWARD_H
#define MELEE_FT_CHARA_FTMARIO_FORWARD_H

#include "ft/forward.h"
#include "ftCommon/forward.h"

static MotionFlags const ftMr_MF_Special ATTRIBUTE_USED =
    Ft_MF_SkipModel | Ft_MF_SkipItemVis | Ft_MF_UnkUpdatePhys |
    Ft_MF_FreezeState;

static MotionFlags const ftMr_MF_SpecialN ATTRIBUTE_USED =
    ftMr_MF_Special | Ft_MF_KeepFastFall | Ft_MF_SkipThrowException;

static MotionFlags const ftMr_MF_SpecialHi ATTRIBUTE_USED =
    ftMr_MF_Special | Ft_MF_KeepFastFall | Ft_MF_KeepGfx | Ft_MF_KeepSfx;

static MotionFlags const ftMr_MF_SpecialLw ATTRIBUTE_USED =
    ftMr_MF_Special | Ft_MF_KeepColAnimHitStatus | Ft_MF_KeepSfx;

static MotionFlags const ftMr_MF_SpecialAirN ATTRIBUTE_USED =
    ftMr_MF_SpecialN | Ft_MF_SkipParasol;

static MotionFlags const ftMr_MF_SpecialAirHi ATTRIBUTE_USED =
    ftMr_MF_SpecialHi | Ft_MF_SkipParasol;

static MotionFlags const ftMr_MF_SpecialAirLw ATTRIBUTE_USED =
    ftMr_MF_SpecialLw | Ft_MF_SkipParasol;

static MotionFlags const ftMr_MF_SpecialS ATTRIBUTE_USED =
    ftMr_MF_Special | Ft_MF_KeepGfx | Ft_MF_SkipModel | Ft_MF_SkipColAnim;

typedef enum ftMario_MotionState {
    ftMr_MS_AppealR = ftCo_MS_Count,
    ftMr_MS_AppealL,
    ftMr_MS_SpecialN,
    ftMr_MS_SpecialAirN,
    ftMr_MS_SpecialS,
    ftMr_MS_SpecialAirS,
    ftMr_MS_SpecialHi,
    ftMr_MS_SpecialAirHi,
    ftMr_MS_SpecialLw,
    ftMr_MS_SpecialAirLw,
    ftMr_MS_Count,
} ftMario_MotionState;

#endif
