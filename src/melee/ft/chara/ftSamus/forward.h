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
    ftSs_MS_SpecialNStart,
    ftSs_MS_SpecialNHold,
    ftSs_MS_SpecialNCancel,
    ftSs_MS_SpecialN,
    ftSs_MS_SpecialAirNStart,
    ftSs_MS_SpecialAirN,
    ftSs_MS_SpecialS,
    ftSs_MS_SpecialSSmash,
    ftSs_MS_SpecialAirS,
    ftSs_MS_SpecialAirSSmash,
    ftSs_MS_SpecialHi,
    ftSs_MS_SpecialAirHi,
    ftSs_MS_SpecialLwBomb,
    ftSs_MS_SpecialAirLwBomb,
    ftSs_MS_AirCatch,
    ftSs_MS_AirCatchHit,
} ftSamus_MotionState;

typedef enum ftSs_Submotion {
    ftSs_SM_SpecialLw = ftCo_SM_Count,
    ftSs_SM_SpecialAirLw,
    ftSs_SM_SpecialNStart,
    ftSs_SM_SpecialNHold,
    ftSs_SM_SpecialNCancel,
    ftSs_SM_SpecialN,
    ftSs_SM_SpecialAirNStart,
    ftSs_SM_SpecialAirN,
    ftSs_SM_SpecialS,
    ftSs_SM_SpecialSSmash,
    ftSs_SM_SpecialAirS,
    ftSs_SM_SpecialAirSSmash,
    ftSs_SM_SpecialHi,
    ftSs_SM_SpecialAirHi,
    ftSs_SM_SpecialLwBomb,
    ftSs_SM_SpecialAirLwBomb,
    ftSs_SM_AirCatch,
    ftSs_SM_AirCatchHit,
} ftSs_Submotion;

#endif
