#ifndef MELEE_FT_CHARA_FTMEWTWO_FORWARD_H
#define MELEE_FT_CHARA_FTMEWTWO_FORWARD_H

#include "ft/forward.h"
#include "ftCommon/forward.h"

static MotionFlags const ftMt_MF_Special ATTRIBUTE_USED =
    Ft_MF_SkipModel | Ft_MF_SkipItemVis | Ft_MF_UnkUpdatePhys |
    Ft_MF_FreezeState;

static MotionFlags const ftMt_MF_SpecialHiStart ATTRIBUTE_USED =
    ftMt_MF_Special | Ft_MF_KeepFastFall | Ft_MF_KeepGfx;

static MotionFlags const ftMt_MF_SpecialNStart ATTRIBUTE_USED =
    ftMt_MF_Special | Ft_MF_KeepFastFall | Ft_MF_SkipThrowException;

static MotionFlags const ftMt_MF_SpecialLw ATTRIBUTE_USED =
    ftMt_MF_Special | Ft_MF_KeepColAnimHitStatus | Ft_MF_SkipThrowException;

static MotionFlags const ftMt_MF_SpecialAirHiStart ATTRIBUTE_USED =
    ftMt_MF_SpecialHiStart | Ft_MF_SkipParasol;

static MotionFlags const ftMt_MF_SpecialAirNStart ATTRIBUTE_USED =
    ftMt_MF_SpecialNStart | Ft_MF_SkipParasol;

static MotionFlags const ftMt_MF_SpecialAirLw ATTRIBUTE_USED =
    ftMt_MF_SpecialLw | Ft_MF_SkipParasol;

static MotionFlags const ftMt_MF_SpecialS ATTRIBUTE_USED =
    ftMt_MF_Special | Ft_MF_KeepGfx | Ft_MF_SkipColAnim;

static MotionFlags const ftMt_MF_SpecialAirS ATTRIBUTE_USED =
    ftMt_MF_SpecialS | Ft_MF_SkipParasol;

static MotionFlags const ftMt_MF_SpecialN ATTRIBUTE_USED =
    ftMt_MF_SpecialNStart | Ft_MF_Unk19;

static MotionFlags const ftMt_MF_SpecialAirN ATTRIBUTE_USED =
    ftMt_MF_SpecialN | Ft_MF_SkipParasol;

typedef enum ftMewtwo_MotionState {
    ftMt_MS_SpecialNStart = ftCo_MS_Count,
    ftMt_MS_SpecialNLoop,
    ftMt_MS_SpecialNLoopFull,
    ftMt_MS_SpecialNCancel,
    ftMt_MS_SpecialNEnd,
    ftMt_MS_SpecialAirNStart,
    ftMt_MS_SpecialAirNLoop,
    ftMt_MS_SpecialAirNLoopFull,
    ftMt_MS_SpecialAirNCancel,
    ftMt_MS_SpecialAirNEnd,
    ftMt_MS_SpecialS,
    ftMt_MS_SpecialAirS,
    ftMt_MS_SpecialHiStart,
    ftMt_MS_SpecialHiLost,
    ftMt_MS_SpecialHi,
    ftMt_MS_SpecialAirHiStart,
    ftMt_MS_SpecialAirHiLost,
    ftMt_MS_SpecialAirHi,
    ftMt_MS_SpecialLw,
    ftMt_MS_SpecialAirLw,
    ftMt_MS_Count,
    ftMt_MS_SelfCount = ftMt_MS_Count - ftCo_MS_Count,
} ftMewtwo_MotionState;

typedef enum ftMt_Submotion {
    ftMt_SM_SpecialNStart = ftCo_SM_Count,
    ftMt_SM_SpecialNLoop,
    ftMt_SM_SpecialNLoopFull,
    ftMt_SM_SpecialNCancel,
    ftMt_SM_SpecialNEnd,
    ftMt_SM_SpecialAirNStart,
    ftMt_SM_SpecialAirNLoop,
    ftMt_SM_SpecialAirNLoopFull,
    ftMt_SM_SpecialAirNCancel,
    ftMt_SM_SpecialAirNEnd,
    ftMt_SM_SpecialS,
    ftMt_SM_SpecialAirS,
    ftMt_SM_SpecialHiStart,
    ftMt_SM_SpecialHi,
    ftMt_SM_SpecialHiLost,
    ftMt_SM_SpecialAirHiStart,
    ftMt_SM_SpecialAirHi,
    ftMt_SM_SpecialLw,
    ftMt_SM_SpecialAirLw,
    ftMt_SM_Count,
    ftMt_SM_SelfCount = ftMt_SM_Count - ftCo_SM_Count,
} ftMt_Submotion;

#endif
