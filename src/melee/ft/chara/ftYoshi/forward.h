#ifndef MELEE_FT_CHARA_FTYOSHI_FORWARD_H
#define MELEE_FT_CHARA_FTYOSHI_FORWARD_H

#include "ft/forward.h"
#include "ftCommon/forward.h"

struct S_UNK_YOSHI1;
typedef struct ftYs_DatAttrs ftYs_DatAttrs;

/// @todo Fix names
static MotionFlags const ftYs_MF_Special =
    Ft_MF_SkipModel | Ft_MF_SkipItemVis | Ft_MF_UnkUpdatePhys |
    Ft_MF_FreezeState;

static MotionFlags const ftYs_MF_MS_341 = Ft_MF_UnkUpdatePhys;

static MotionFlags const ftYs_MF_ShieldStart =
    Ft_MF_KeepFastFall | Ft_MF_KeepGfx | Ft_MF_SkipModel | Ft_MF_SkipAnimVel |
    Ft_MF_Unk06 | Ft_MF_SkipColAnim | Ft_MF_UnkUpdatePhys;

static MotionFlags const ftYs_MF_ShieldHold =
    Ft_MF_Unk19 | Ft_MF_UnkUpdatePhys;

static MotionFlags const ftYs_MF_SpecialN =
    ftYs_MF_Special | Ft_MF_KeepFastFall;

static MotionFlags const ftYs_MF_SpecialAirHi =
    ftYs_MF_SpecialN | Ft_MF_KeepGfx | Ft_MF_SkipThrowException;

static MotionFlags const ftYs_MF_UnkBase = ftYs_MF_Special | Ft_MF_KeepSfx;

static MotionFlags const ftYs_MF_SpecialAirS = ftYs_MF_UnkBase | Ft_MF_KeepGfx;

static MotionFlags const ftYs_MF_MS_366 =
    ftYs_MF_UnkBase | Ft_MF_KeepColAnimHitStatus;

static MotionFlags const ftYs_MF_SpecialS =
    ftYs_MF_SpecialN | Ft_MF_SkipParasol;

static MotionFlags const ftYs_MF_MS_365 =
    ftYs_MF_SpecialAirHi | Ft_MF_SkipParasol;

static MotionFlags const ftYs_MF_SpecialHi =
    ftYs_MF_SpecialAirS | Ft_MF_SkipParasol;

static MotionFlags const ftYs_MF_MS_368 = ftYs_MF_MS_366 | Ft_MF_SkipParasol;

typedef enum ftYoshi_MotionState {
    ftYs_MS_GuardOn_0 = ftCo_MS_Count,
    ftYs_MS_GuardHold,
    ftYs_MS_GuardOff,
    ftYs_MS_GuardDamage,
    ftYs_MS_GuardOn_1,
    ftYs_MS_SpecialN1,
    ftYs_MS_SpecialN1_0,
    ftYs_MS_SpecialN1_1,
    ftYs_MS_SpecialN2_0,
    ftYs_MS_SpecialN2_1,
    ftYs_MS_SpecialAirN1_0,
    ftYs_MS_SpecialAirN1_1,
    ftYs_MS_SpecialAirN1_2,
    ftYs_MS_SpecialAirN2_0,
    ftYs_MS_SpecialAirN2_1,
    ftYs_MS_SpecialAirSStart_0,
    ftYs_MS_SpecialAirSLoop_0,
    ftYs_MS_SpecialAirSLoop_1,
    ftYs_MS_SpecialAirSEnd,
    ftYs_MS_SpecialAirSStart_1,
    ftYs_MS_SpecialAirSLoop_2,
    ftYs_MS_SpecialAirSLoop_3,
    ftYs_MS_SpecialAirSLanding,
    ftYs_MS_SpecialHi,
    ftYs_MS_SpecialAirHi,
    ftYs_MS_SpecialLw,
    ftYs_MS_SpecialLwLanding,
    ftYs_MS_SpecialAirLw,
    ftYs_MS_Count,
    ftYs_MS_SelfCount = ftYs_MS_Count - ftCo_MS_Count,
} ftYoshi_MotionState;

typedef enum ftYs_Submotion {
    ftYs_SM_SpecialN1 = ftCo_SM_Count,
    ftYs_SM_SpecialN1_0,
    ftYs_SM_SpecialN2_1,
    ftYs_SM_SpecialAirN1_0,
    ftYs_SM_SpecialAirN1_1,
    ftYs_SM_SpecialAirN2,
    ftYs_SM_SpecialSStart,
    ftYs_SM_SpecialSLoop_0,
    ftYs_SM_SpecialSLoop_1,
    ftYs_SM_SpecialSEnd,
    ftYs_SM_SpecialAirSStart,
    ftYs_SM_SpecialAirSLoop_0,
    ftYs_SM_SpecialAirSLoop_1,
    ftYs_SM_SpecialAirSEnd,
    ftYs_SM_SpecialHi,
    ftYs_SM_SpecialAirHi,
    ftYs_SM_SpecialLw,
    ftYs_SM_SpecialLwLanding,
    ftYs_SM_SpecialAirLw,
    ftYs_SM_Count,
    ftYs_SM_SelfCount = ftYs_SM_Count - ftCo_SM_Count,
} ftYs_Submotion;

#endif
