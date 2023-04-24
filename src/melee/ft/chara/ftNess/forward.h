#ifndef MELEE_FT_CHARA_FTNESS_FORWARD_H
#define MELEE_FT_CHARA_FTNESS_FORWARD_H

#include <platform.h>
#include "ft/forward.h"
#include "ftCommon/forward.h"

static MotionFlags const ftNs_MF_Attack4 ATTRIBUTE_USED =
    Ft_MF_SkipHit | Ft_MF_SkipRumble | Ft_MF_SkipItemVis | Ft_MF_FreezeState;

static MotionFlags const ftNs_MF_AttackHi4 ATTRIBUTE_USED =
    ftNs_MF_Attack4 | Ft_MF_KeepGfx;

static MotionFlags const ftNs_MF_AttackLw4 ATTRIBUTE_USED =
    ftNs_MF_AttackHi4 | Ft_MF_KeepFastFall;

static MotionFlags const ftNs_MF_AttackHi4Start ATTRIBUTE_USED =
    ftNs_MF_AttackHi4 | Ft_MF_KeepSfx;

static MotionFlags const ftNs_MF_AttackLw4Start ATTRIBUTE_USED =
    ftNs_MF_AttackLw4 | Ft_MF_KeepSfx;

static MotionFlags const ftNs_MF_AttackS4 ATTRIBUTE_USED =
    ftNs_MF_Attack4 | Ft_MF_KeepFastFall | Ft_MF_KeepSfx | Ft_MF_SkipColAnim;

static MotionFlags const ftNs_MF_Special ATTRIBUTE_USED =
    Ft_MF_SkipModel | Ft_MF_SkipItemVis | Ft_MF_UnkUpdatePhys |
    Ft_MF_FreezeState;

static MotionFlags const ftNs_MF_SpecialLw ATTRIBUTE_USED =
    ftNs_MF_Special | Ft_MF_KeepColAnimHitStatus;

static MotionFlags const ftNs_MF_Special_SkipUpdateThrowException
    ATTRIBUTE_USED = ftNs_MF_Special | Ft_MF_SkipThrowException;

static MotionFlags const ftNs_MF_SpecialN ATTRIBUTE_USED =
    ftNs_MF_Special_SkipUpdateThrowException | Ft_MF_KeepFastFall;

static MotionFlags const ftNs_MF_SpecialS ATTRIBUTE_USED =
    ftNs_MF_Special_SkipUpdateThrowException | Ft_MF_KeepGfx;

static MotionFlags const ftNs_MF_SpecialHi ATTRIBUTE_USED =
    ftNs_MF_SpecialN | Ft_MF_KeepGfx;

static MotionFlags const ftNs_MF_SpecialAirLw ATTRIBUTE_USED =
    ftNs_MF_SpecialLw | Ft_MF_SkipParasol;

static MotionFlags const ftNs_MF_SpecialAirN ATTRIBUTE_USED =
    ftNs_MF_SpecialN | Ft_MF_SkipParasol;

static MotionFlags const ftNs_MF_SpecialAirS ATTRIBUTE_USED =
    ftNs_MF_SpecialS | Ft_MF_SkipParasol;

static MotionFlags const ftNs_MF_SpecialAirHi ATTRIBUTE_USED =
    ftNs_MF_SpecialHi | Ft_MF_SkipParasol;

static MotionFlags const ftNs_MF_SpecialLwLoop ATTRIBUTE_USED =
    ftNs_MF_SpecialLw | Ft_MF_Unk19;

static MotionFlags const ftNs_MF_SpecialAirLwLoop ATTRIBUTE_USED =
    ftNs_MF_SpecialLwLoop | Ft_MF_SkipParasol;

typedef enum ftNess_MotionState {
    ftNs_MS_AttackS4 = ftCo_MS_Count,
    ftNs_MS_AttackHi4,
    ftNs_MS_AttackHi4Charge,
    ftNs_MS_AttackHi4Release,
    ftNs_MS_AttackLw4,
    ftNs_MS_AttackLw4Charge,
    ftNs_MS_AttackLw4Release,
    ftNs_MS_SpecialNStart,
    ftNs_MS_SpecialNHold,
    ftNs_MS_SpecialNRelease,
    ftNs_MS_SpecialNEnd,
    ftNs_MS_SpecialAirNStart,
    ftNs_MS_SpecialAirNHold,
    ftNs_MS_SpecialAirNRelease,
    ftNs_MS_SpecialAirNEnd,
    ftNs_MS_SpecialS,
    ftNs_MS_SpecialAirS,
    ftNs_MS_SpecialHiStart,
    ftNs_MS_SpecialHiHold,
    ftNs_MS_SpecialHiEnd,
    ftNs_MS_SpecialHi,
    ftNs_MS_SpecialAirHiStart,
    ftNs_MS_SpecialAirHiHold,
    ftNs_MS_SpecialAirHiEnd,
    ftNs_MS_SpecialAirHi,
    ftNs_MS_SpecialAirHiRebound,
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
} ftNess_MotionState;

#endif
