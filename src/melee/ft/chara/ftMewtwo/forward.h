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
    ftMt_MS_SpecialNFull,
    ftMt_MS_SpecialNCancel,
    ftMt_MS_SpecialNEnd,
    ftMt_MS_SpecialAirNStart,
    ftMt_MS_SpecialAirNLoop,
    ftMt_MS_SpecialAirNFull,
    ftMt_MS_SpecialAirNCancel,
    ftMt_MS_SpecialAirNEnd,
    ftMt_MS_SpecialS,
    ftMt_MS_SpecialAirS,
    ftMt_MS_SpecialHiStart,
    ftMt_MS_SpecialHi,
    ftMt_MS_SpecialHiLost,
    ftMt_MS_SpecialAirHiStart,
    ftMt_MS_SpecialAirHi,
    ftMt_MS_SpecialAirHiLost,
    ftMt_MS_SpecialLw,
    ftMt_MS_SpecialAirLw,
} ftMewtwo_MotionState;

#endif
