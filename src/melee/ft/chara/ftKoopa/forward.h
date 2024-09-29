#ifndef MELEE_FT_CHARA_FTKOOPA_FORWARD_H
#define MELEE_FT_CHARA_FTKOOPA_FORWARD_H

#include <platform.h>

#include "ft/forward.h"
#include "ftCommon/forward.h"

static MotionFlags const ftKp_MF_Special =
    Ft_MF_SkipModel | Ft_MF_SkipItemVis | Ft_MF_UnkUpdatePhys |
    Ft_MF_FreezeState;

static MotionFlags const ftKp_MF_SpecialN =
    ftKp_MF_Special | Ft_MF_KeepFastFall;

static MotionFlags const ftKp_MF_SpecialS = ftKp_MF_Special | Ft_MF_KeepGfx;

static MotionFlags const ftKp_MF_SpecialHi =
    ftKp_MF_Special | Ft_MF_KeepFastFall | Ft_MF_KeepGfx | Ft_MF_KeepSfx;

static MotionFlags const ftKp_MF_SpecialLwStart =
    ftKp_MF_Special | Ft_MF_KeepColAnimHitStatus | Ft_MF_KeepSfx;

static MotionFlags const ftKp_MF_SpecialNStart =
    ftKp_MF_SpecialN | Ft_MF_SkipParasol;

static MotionFlags const ftKp_MF_SpecialAirS =
    ftKp_MF_SpecialS | Ft_MF_SkipParasol;

static MotionFlags const ftKp_MF_SpecialAirHi =
    ftKp_MF_SpecialHi | Ft_MF_SkipParasol;

static MotionFlags const ftKp_MF_SpecialAirLw =
    ftKp_MF_SpecialLwStart | Ft_MF_SkipParasol;

static MotionFlags const ftKp_MF_SpecialNLoop = ftKp_MF_SpecialN | Ft_MF_Unk19;

static MotionFlags const ftKp_MF_SpecialAirNLoop =
    ftKp_MF_SpecialNLoop | Ft_MF_SkipParasol;

typedef enum ftKoopa_MotionState {
    ftKp_MS_SpecialNStart = ftCo_MS_Count,
    ftKp_MS_SpecialN,
    ftKp_MS_SpecialNEnd,
    ftKp_MS_SpecialAirNStart,
    ftKp_MS_SpecialAirN,
    ftKp_MS_SpecialAirNEnd,
    ftKp_MS_SpecialSStart,
    ftKp_MS_SpecialSHit0_0,
    ftKp_MS_SpecialSHit1,
    ftKp_MS_SpecialSHit0_1,
    ftKp_MS_SpecialSEndF,
    ftKp_MS_SpecialSEndB,
    ftKp_MS_SpecialAirSStart,
    ftKp_MS_SpecialAirSHit0_0,
    ftKp_MS_SpecialAirSHit1,
    ftKp_MS_SpecialAirSHit0_1,
    ftKp_MS_SpecialAirSEndF,
    ftKp_MS_SpecialAirSEndB,
    ftKp_MS_SpecialHi,
    ftKp_MS_SpecialAirHi,
    ftKp_MS_SpecialLw,
    ftKp_MS_SpecialAirLw,
    ftKp_MS_SpecialLwLanding,
    ftKp_MS_Count,
    ftKp_MS_SelfCount = ftKp_MS_Count - ftCo_MS_Count,
} ftKoopa_MotionState;

typedef enum ftKp_Submotion {
    ftKp_SM_SpecialNStart = ftCo_SM_Count,
    ftKp_SM_SpecialN,
    ftKp_SM_SpecialNEnd,
    ftKp_SM_SpecialAirNStart,
    ftKp_SM_SpecialAirN,
    ftKp_SM_SpecialAirNEnd,
    ftKp_SM_SpecialSStart,
    ftKp_SM_SpecialSHit0,
    ftKp_SM_SpecialSHit1,
    ftKp_SM_SpecialSEndF,
    ftKp_SM_SpecialSEndB,
    ftKp_SM_SpecialAirSStart,
    ftKp_SM_SpecialAirSHit0,
    ftKp_SM_SpecialAirSHit1,
    ftKp_SM_SpecialAirSEndF,
    ftKp_SM_SpecialAirSEndB,
    ftKp_SM_SpecialHi,
    ftKp_SM_SpecialAirHi,
    ftKp_SM_SpecialLw,
    ftKp_SM_SpecialAirLw,
    ftKp_SM_SpecialLwLanding,
    ftKp_SM_Count,
    ftKp_SM_SelfCount = ftKp_SM_Count - ftCo_SM_Count,
} ftKp_Submotion;

#endif
