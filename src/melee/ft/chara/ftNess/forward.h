#ifndef MELEE_FT_CHARA_FTNESS_FORWARD_H
#define MELEE_FT_CHARA_FTNESS_FORWARD_H

#include <platform.h>

#include "ft/forward.h"
#include "ftCommon/forward.h"

static MotionFlags const ftNs_MF_Attack4 =
    Ft_MF_SkipHit | Ft_MF_SkipRumble | Ft_MF_SkipItemVis | Ft_MF_FreezeState;

static MotionFlags const ftNs_MF_AttackHi4 = ftNs_MF_Attack4 | Ft_MF_KeepGfx;

static MotionFlags const ftNs_MF_AttackLw4 =
    ftNs_MF_AttackHi4 | Ft_MF_KeepFastFall;

static MotionFlags const ftNs_MF_AttackHi4Start =
    ftNs_MF_AttackHi4 | Ft_MF_KeepSfx;

static MotionFlags const ftNs_MF_AttackLw4Start =
    ftNs_MF_AttackLw4 | Ft_MF_KeepSfx;

static MotionFlags const ftNs_MF_AttackS4 =
    ftNs_MF_Attack4 | Ft_MF_KeepFastFall | Ft_MF_KeepSfx | Ft_MF_SkipColAnim;

static MotionFlags const ftNs_MF_Special =
    Ft_MF_SkipModel | Ft_MF_SkipItemVis | Ft_MF_UnkUpdatePhys |
    Ft_MF_FreezeState;

static MotionFlags const ftNs_MF_SpecialLw =
    ftNs_MF_Special | Ft_MF_KeepColAnimHitStatus;

static MotionFlags const ftNs_MF_Special_SkipUpdateThrowException =
    ftNs_MF_Special | Ft_MF_SkipThrowException;

static MotionFlags const ftNs_MF_SpecialN =
    ftNs_MF_Special_SkipUpdateThrowException | Ft_MF_KeepFastFall;

static MotionFlags const ftNs_MF_SpecialS =
    ftNs_MF_Special_SkipUpdateThrowException | Ft_MF_KeepGfx;

static MotionFlags const ftNs_MF_SpecialHi = ftNs_MF_SpecialN | Ft_MF_KeepGfx;

static MotionFlags const ftNs_MF_SpecialAirLw =
    ftNs_MF_SpecialLw | Ft_MF_SkipParasol;

static MotionFlags const ftNs_MF_SpecialAirN =
    ftNs_MF_SpecialN | Ft_MF_SkipParasol;

static MotionFlags const ftNs_MF_SpecialAirS =
    ftNs_MF_SpecialS | Ft_MF_SkipParasol;

static MotionFlags const ftNs_MF_SpecialAirHi =
    ftNs_MF_SpecialHi | Ft_MF_SkipParasol;

static MotionFlags const ftNs_MF_SpecialLwLoop =
    ftNs_MF_SpecialLw | Ft_MF_Unk19;

static MotionFlags const ftNs_MF_SpecialAirLwLoop =
    ftNs_MF_SpecialLwLoop | Ft_MF_SkipParasol;

typedef enum ftNess_MotionState {
    ftNs_MS_AttackS4 = ftCo_MS_Count,
    ftNs_MS_AttackHi4,
    ftNs_MS_AttackHi4Charge,
    ftNs_MS_AttackHi4Release,
    ftNs_MS_AttackLw4,
    ftNs_MS_AttackLw4Charge,
    ftNs_MS_AttackLw4Release,
    /* 15C */ ftNs_MS_SpecialNStart,
    /* 15D */ ftNs_MS_SpecialNHold,
    /* 15E */ ftNs_MS_SpecialNRelease,
    /* 15F */ ftNs_MS_SpecialNEnd,
    ftNs_MS_SpecialAirNStart,
    ftNs_MS_SpecialAirNHold,
    ftNs_MS_SpecialAirNRelease,
    ftNs_MS_SpecialAirNEnd,
    ftNs_MS_SpecialS,
    ftNs_MS_SpecialAirS,
    /* 166 */ ftNs_MS_SpecialHiStart,
    /* 167 */ ftNs_MS_SpecialHiHold,
    /* 168 */ ftNs_MS_SpecialHiEnd,
    /* 169 */ ftNs_MS_SpecialHi,
    /* 16A */ ftNs_MS_SpecialAirHiStart,
    /* 16B */ ftNs_MS_SpecialAirHiHold,
    /* 16C */ ftNs_MS_SpecialAirHiEnd,
    /* 16D */ ftNs_MS_SpecialAirHi,
    /* 16E */ ftNs_MS_SpecialAirHiRebound,
    ftNs_MS_SpecialLwStart,
    ftNs_MS_SpecialLwHold,
    ftNs_MS_SpecialLwHit,
    ftNs_MS_SpecialLwEnd,
    ftNs_MS_SpecialLwTurn,
    ftNs_MS_SpecialAirLwStart,
    ftNs_MS_SpecialAirLwHold,
    ftNs_MS_SpecialAirLwHit,
    ftNs_MS_SpecialAirLwEnd,
    ftNs_MS_SpecialAirLwTurn,
    ftNs_MS_Count,
    ftNs_MS_SelfCount = ftNs_MS_Count - ftCo_MS_Count,
} ftNess_MotionState;

typedef enum ftNs_Submotion {
    ftNs_SM_AttackHi4Charge = ftCo_SM_Count,
    ftNs_SM_AttackHi4Release,
    ftNs_SM_AttackLw4Charge,
    ftNs_SM_AttackLw4Release,
    ftNs_SM_SpecialNStart,
    ftNs_SM_SpecialNHold0,
    ftNs_SM_SpecialNHold1,
    ftNs_SM_SpecialNEnd,
    ftNs_SM_SpecialAirNStart,
    ftNs_SM_SpecialAirNHold0,
    ftNs_SM_SpecialAirNHold1,
    ftNs_SM_SpecialAirNEnd,
    ftNs_SM_SpecialS,
    ftNs_SM_SpecialAirS,
    ftNs_SM_SpecialHiStart,
    ftNs_SM_SpecialHiHold,
    ftNs_SM_SpecialHiEnd,
    ftNs_SM_SpecialHi,
    ftNs_SM_SpecialAirHiStart,
    ftNs_SM_SpecialAirHiHold,
    ftNs_SM_SpecialAirHiEnd,
    ftNs_SM_SpecialAirHi,
    ftNs_SM_SpecialAirHiRebound,
    ftNs_SM_SpecialLwStart,
    ftNs_SM_SpecialLwHold,
    ftNs_SM_SpecialLwHit,
    ftNs_SM_SpecialLwEnd,
    ftNs_SM_SpecialAirLwStart,
    ftNs_SM_SpecialAirLwHold,
    ftNs_SM_SpecialAirLwHit,
    ftNs_SM_SpecialAirLwEnd,
    ftNs_SM_Count,
    ftNs_SM_SelfCount = ftNs_SM_Count - ftCo_SM_Count,
} ftNs_Submotion;

#endif
