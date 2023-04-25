#ifndef MELEE_FT_CHARA_FTYOSHI_FORWARD_H
#define MELEE_FT_CHARA_FTYOSHI_FORWARD_H

#include "ft/forward.h"
#include "ftCommon/forward.h"

struct S_UNK_YOSHI1;

/// @todo Fix names
static MotionFlags const ftYs_MF_Special ATTRIBUTE_USED =
    Ft_MF_SkipModel | Ft_MF_SkipItemVis | Ft_MF_UnkUpdatePhys |
    Ft_MF_FreezeState;

static MotionFlags const ftYs_MF_MS_341 ATTRIBUTE_USED = Ft_MF_UnkUpdatePhys;

static MotionFlags const ftYs_MF_ShieldStart ATTRIBUTE_USED =
    Ft_MF_KeepFastFall | Ft_MF_KeepGfx | Ft_MF_SkipModel | Ft_MF_SkipAnimVel |
    Ft_MF_Unk06 | Ft_MF_SkipColAnim | Ft_MF_UnkUpdatePhys;

static MotionFlags const ftYs_MF_ShieldHold ATTRIBUTE_USED =
    Ft_MF_Unk19 | Ft_MF_UnkUpdatePhys;

static MotionFlags const ftYs_MF_SpecialN ATTRIBUTE_USED =
    ftYs_MF_Special | Ft_MF_KeepFastFall;

static MotionFlags const ftYs_MF_SpecialAirHi ATTRIBUTE_USED =
    ftYs_MF_SpecialN | Ft_MF_KeepGfx | Ft_MF_SkipThrowException;

static MotionFlags const ftYs_MF_UnkBase ATTRIBUTE_USED =
    ftYs_MF_Special | Ft_MF_KeepSfx;

static MotionFlags const ftYs_MF_SpecialAirS ATTRIBUTE_USED =
    ftYs_MF_UnkBase | Ft_MF_KeepGfx;

static MotionFlags const ftYs_MF_MS_366 ATTRIBUTE_USED =
    ftYs_MF_UnkBase | Ft_MF_KeepColAnimHitStatus;

static MotionFlags const ftYs_MF_SpecialS ATTRIBUTE_USED =
    ftYs_MF_SpecialN | Ft_MF_SkipParasol;

static MotionFlags const ftYs_MF_MS_365 ATTRIBUTE_USED =
    ftYs_MF_SpecialAirHi | Ft_MF_SkipParasol;

static MotionFlags const ftYs_MF_SpecialHi ATTRIBUTE_USED =
    ftYs_MF_SpecialAirS | Ft_MF_SkipParasol;

static MotionFlags const ftYs_MF_MS_368 ATTRIBUTE_USED =
    ftYs_MF_MS_366 | Ft_MF_SkipParasol;

typedef enum ftYoshi_MotionState {
    ftYs_MS_Unk_341 = ftCo_MS_Count,
    ftYs_MS_Shield_Hold,
    ftYs_MS_Shield_Release,
    ftYs_MS_Shield_Damage,
    ftYs_MS_Shield_Start,
    ftYs_MS_SpecialN,
    ftYs_MS_SpecialN_CatchStart,
    ftYs_MS_SpecialN_Catch,
    ftYs_MS_SpecialAirN,
    ftYs_MS_SpecialAirN_CatchStart,
    ftYs_MS_SpecialAirN_Catch,
    ftYs_MS_SpecialS_Start,
    ftYs_MS_SpecialS,
    ftYs_MS_SpecialS_Turn,
    ftYs_MS_SpecialS_End,
    ftYs_MS_SpecialAirS_Start,
    ftYs_MS_SpecialAirS,
    ftYs_MS_SpecialAirS_Rebound,
    ftYs_MS_SpecialAirS_End,
    ftYs_MS_SpecialHi,
    ftYs_MS_SpecialAirHi,
    ftYs_MS_SpecialLw,
    ftYs_MS_SpecialLw_Land,
    ftYs_MS_SpecialAirLw,

    ftYs_MS_Unk_365,
    ftYs_MS_Unk_366,
    ftYs_MS_Unk_367,
    ftYs_MS_Unk_368,
} ftYoshi_MotionState;

typedef enum ftYs_AnimId {
    ftYs_AnimId_SpecialN = ftCo_AnimId_Count,
    ftYs_AnimId_SpecialNCatch,
    ftYs_AnimId_SpecialAirN,
    ftYs_AnimId_SpecialAirNCatch,
    ftYs_AnimId_SpecialS,
    ftYs_AnimId_SpecialSEnd,
    ftYs_AnimId_SpecialAirSStart,
    ftYs_AnimId_SpecialAirS,
    ftYs_AnimId_SpecialAirSRebound,
    ftYs_AnimId_SpecialAirSEnd,
    ftYs_AnimId_SpecialHi,
    ftYs_AnimId_SpecialAirHi,
    ftYs_AnimId_SpecialLw,
    ftYs_AnimId_SpecialLwLand,
    ftYs_AnimId_SpecialAirLw,
    ftYs_AnimId_MS_365,
    ftYs_AnimId_MS_366,
    ftYs_AnimId_MS_367,
    ftYs_AnimId_MS_368,
} ftYs_AnimId;

#endif
