#ifndef MELEE_FT_CHARA_FTGAMEWATCH_FORWARD_H
#define MELEE_FT_CHARA_FTGAMEWATCH_FORWARD_H

#include "ft/forward.h"
#include "ftCommon/forward.h"

static MotionFlags const ftGw_MF_Base = Ft_MF_SkipItemVis | Ft_MF_FreezeState;

static MotionFlags const ftGw_MF_Landing = Ft_MF_KeepColAnimHitStatus |
                                           Ft_MF_SkipHit | Ft_MF_KeepSfx |
                                           Ft_MF_SkipParasol;

static MotionFlags const ftGw_MF_LandingAirB = ftGw_MF_Landing | Ft_MF_KeepGfx;

static MotionFlags const ftGw_MF_LandingAirHi =
    ftGw_MF_LandingAirB | Ft_MF_KeepFastFall;

static MotionFlags const ftGw_MF_Attack = ftGw_MF_Base | Ft_MF_KeepSfx;

static MotionFlags const ftGw_MF_AttackLw3 = ftGw_MF_Attack | Ft_MF_SkipHit;

static MotionFlags const ftGw_MF_AttackAirN = ftGw_MF_Attack | ftGw_MF_Landing;

static MotionFlags const ftGw_MF_AttackAirB =
    ftGw_MF_AttackAirN | Ft_MF_KeepGfx;

static MotionFlags const ftGw_MF_AttackAirHi =
    ftGw_MF_AttackAirB | Ft_MF_KeepFastFall;

static MotionFlags const ftGw_MF_AttackS4 =
    ftGw_MF_AttackLw3 | Ft_MF_KeepFastFall | Ft_MF_SkipRumble;

static MotionFlags const ftGw_MF_Attack11 =
    ftGw_MF_Attack | Ft_MF_KeepFastFall | Ft_MF_Unk19;

static MotionFlags const ftGw_MF_Attack100 =
    ftGw_MF_Attack | Ft_MF_KeepColAnimHitStatus | Ft_MF_Unk19;

static MotionFlags const ftGw_MF_Special =
    ftGw_MF_Base | Ft_MF_SkipModel | Ft_MF_UnkUpdatePhys;

static MotionFlags const ftGw_MF_SpecialS = ftGw_MF_Special | Ft_MF_KeepGfx;

static MotionFlags const ftGw_MF_SpecialHi =
    ftGw_MF_Special | Ft_MF_KeepFastFall | Ft_MF_KeepGfx;

static MotionFlags const ftGw_MF_SpecialLwCatch =
    ftGw_MF_Special | Ft_MF_KeepColAnimHitStatus;

static MotionFlags const ftGw_MF_SpecialN =
    ftGw_MF_Special | Ft_MF_KeepFastFall | Ft_MF_SkipThrowException;

static MotionFlags const ftGw_MF_SpecialAirS =
    ftGw_MF_SpecialS | Ft_MF_SkipParasol;

static MotionFlags const ftGw_MF_SpecialAirHi =
    ftGw_MF_SpecialHi | Ft_MF_SkipParasol;

static MotionFlags const ftGw_MF_SpecialAirLwCatch =
    ftGw_MF_SpecialLwCatch | Ft_MF_SkipParasol;

static MotionFlags const ftGw_MF_SpecialAirN =
    ftGw_MF_SpecialN | Ft_MF_SkipParasol;

static MotionFlags const ftGw_MF_SpecialLw =
    ftGw_MF_SpecialLwCatch | Ft_MF_Unk19;

static MotionFlags const ftGw_MF_SpecialAirLw =
    ftGw_MF_SpecialLw | Ft_MF_SkipParasol;

/// Mr. Game & Watch Motion State IDs
typedef enum ftGameWatch_MotionState {
    ftGw_MS_Attack11 = ftCo_MS_Count,
    ftGw_MS_Attack100Start,
    ftGw_MS_Attack100Loop,
    ftGw_MS_Attack100End,
    ftGw_MS_AttackLw3,
    ftGw_MS_AttackS4,
    ftGw_MS_AttackAirN,
    ftGw_MS_AttackAirB,
    ftGw_MS_AttackAirHi,
    ftGw_MS_LandingAirN,
    ftGw_MS_LandingAirB,
    ftGw_MS_LandingAirHi,
    ftGw_MS_SpecialN,
    ftGw_MS_SpecialAirN,
    ftGw_MS_SpecialS1,
    ftGw_MS_SpecialS2,
    ftGw_MS_SpecialS3,
    ftGw_MS_SpecialS4,
    ftGw_MS_SpecialS5,
    ftGw_MS_SpecialS6,
    ftGw_MS_SpecialS7,
    ftGw_MS_SpecialS8,
    ftGw_MS_SpecialS9,
    ftGw_MS_SpecialAirS1,
    ftGw_MS_SpecialAirS2,
    ftGw_MS_SpecialAirS3,
    ftGw_MS_SpecialAirS4,
    ftGw_MS_SpecialAirS5,
    ftGw_MS_SpecialAirS6,
    ftGw_MS_SpecialAirS7,
    ftGw_MS_SpecialAirS8,
    ftGw_MS_SpecialAirS9,
    ftGw_MS_SpecialHi,
    ftGw_MS_SpecialAirHi,
    ftGw_MS_SpecialLw,
    ftGw_MS_SpecialLwCatch,
    ftGw_MS_SpecialLwShoot,
    ftGw_MS_SpecialAirLw,
    ftGw_MS_SpecialAirLwCatch,
    ftGw_MS_SpecialAirLwShoot,
    ftGw_MS_Count,
    ftGw_MS_SelfCount = ftGw_MS_Count - ftCo_MS_Count,
} ftGameWatch_MotionState;

typedef enum ftGw_Submotion {
    ftGw_SM_SpecialN = ftCo_SM_Count,
    ftGw_SM_SpecialAirN,
    ftGw_SM_SpecialS1,
    ftGw_SM_SpecialS2,
    ftGw_SM_SpecialS3,
    ftGw_SM_SpecialS4,
    ftGw_SM_SpecialS5,
    ftGw_SM_SpecialS6,
    ftGw_SM_SpecialS7,
    ftGw_SM_SpecialS8,
    ftGw_SM_SpecialS9,
    ftGw_SM_SpecialAirS1,
    ftGw_SM_SpecialAirS2,
    ftGw_SM_SpecialAirS3,
    ftGw_SM_SpecialAirS4,
    ftGw_SM_SpecialAirS5,
    ftGw_SM_SpecialAirS6,
    ftGw_SM_SpecialAirS7,
    ftGw_SM_SpecialAirS8,
    ftGw_SM_SpecialAirS9,
    ftGw_SM_SpecialHi,
    ftGw_SM_SpecialAirHi,
    ftGw_SM_SpecialLw,
    ftGw_SM_SpecialLwCatch,
    ftGw_SM_SpecialLwShoot,
    ftGw_SM_SpecialAirLw,
    ftGw_SM_SpecialAirLwCatch,
    ftGw_SM_SpecialAirLwShoot,
    ftGw_SM_Count,
    ftGw_SM_SelfCount = ftGw_SM_Count - ftCo_SM_Count,
} ftGw_Submotion;

typedef enum ftGameWatch_PanicLevel {
    ftGw_Panic_Empty,
    ftGw_Panic_Low,
    ftGw_Panic_Mid,
    ftGw_Panic_Full,
} ftGameWatch_PanicLevel;

#endif
