#ifndef MELEE_FT_CHARA_FTPEACH_FORWARD_H
#define MELEE_FT_CHARA_FTPEACH_FORWARD_H

#include "ft/forward.h"
#include "ftCommon/forward.h"

static MotionFlags const ftPe_MF_Base ATTRIBUTE_USED =
    Ft_MF_SkipItemVis | Ft_MF_FreezeState;

static MotionFlags const ftPe_MF_FloatAttack ATTRIBUTE_USED =
    ftPe_MF_Base | Ft_MF_SkipParasol;

static MotionFlags const ftPe_MF_FloatAttackAirN ATTRIBUTE_USED =
    ftPe_MF_FloatAttack | Ft_MF_KeepColAnimHitStatus | Ft_MF_SkipHit;

static MotionFlags const ftPe_MF_Move_14 ATTRIBUTE_USED =
    ftPe_MF_FloatAttackAirN | Ft_MF_KeepFastFall;

static MotionFlags const ftPe_MF_FloatAttackAirB ATTRIBUTE_USED =
    ftPe_MF_FloatAttackAirN | Ft_MF_KeepGfx;

static MotionFlags const ftPe_MF_FloatAttackAirHi ATTRIBUTE_USED =
    ftPe_MF_FloatAttackAirN | Ft_MF_KeepFastFall | Ft_MF_KeepGfx;

static MotionFlags const ftPe_MF_Move_17 ATTRIBUTE_USED =
    ftPe_MF_FloatAttack | Ft_MF_SkipModel;

static MotionFlags const ftPe_MF_AttackS4 ATTRIBUTE_USED =
    ftPe_MF_Base | Ft_MF_KeepFastFall | Ft_MF_SkipHit | Ft_MF_KeepSfx |
    Ft_MF_SkipRumble;

static MotionFlags const ftPe_MF_Special ATTRIBUTE_USED =
    ftPe_MF_Base | Ft_MF_SkipModel | Ft_MF_UnkUpdatePhys;

static MotionFlags const ftPe_MF_SpecialN ATTRIBUTE_USED =
    ftPe_MF_Special | Ft_MF_KeepFastFall;

static MotionFlags const ftPe_MF_SpecialHi ATTRIBUTE_USED =
    ftPe_MF_SpecialN | Ft_MF_KeepGfx;

static MotionFlags const ftPe_MF_SpecialLw ATTRIBUTE_USED =
    ftPe_MF_Special | Ft_MF_KeepColAnimHitStatus;

static MotionFlags const ftPe_MF_SpecialS ATTRIBUTE_USED =
    ftPe_MF_Special | Ft_MF_KeepGfx | Ft_MF_KeepSfx;

static MotionFlags const ftPe_MF_SpecialAirN ATTRIBUTE_USED =
    ftPe_MF_SpecialN | Ft_MF_SkipParasol;

static MotionFlags const ftPe_MF_SpecialAirHi ATTRIBUTE_USED =
    ftPe_MF_SpecialHi | Ft_MF_SkipParasol;

static MotionFlags const ftPe_MF_SpecialAirS ATTRIBUTE_USED =
    ftPe_MF_SpecialS | Ft_MF_SkipParasol;

static MotionFlags const ftPe_MF_ParasolOpen ATTRIBUTE_USED =
    Ft_MF_SkipHit | Ft_MF_SkipModel | Ft_MF_Unk06 | Ft_MF_SkipItemVis |
    Ft_MF_SkipModelPartVis;

static MotionFlags const ftPe_MF_ParasolFallSpecial ATTRIBUTE_USED =
    ftPe_MF_ParasolOpen | Ft_MF_Unk19;

typedef enum ftPeach_MotionState {
    ftPe_MS_Float = ftCo_MS_Count,
    ftPe_MS_FloatEndF,
    ftPe_MS_FloatEndB,
    ftPe_MS_FloatAttackAirN,
    ftPe_MS_FloatAttackAirF,
    ftPe_MS_FloatAttackAirB,
    ftPe_MS_FloatAttackAirU,
    ftPe_MS_FloatAttackAirD,
    ftPe_MS_AttackS4_Club,
    ftPe_MS_AttackS4_Pan,
    ftPe_MS_AttackS4_Racket,
    ftPe_MS_SpecialLw,
    ftPe_MS_SpecialAirLw,
    ftPe_MS_SpecialSStart,
    ftPe_MS_SpecialSEnd,
    ftPe_MS_Unk_356,
    ftPe_MS_SpecialAirSStart,
    ftPe_MS_SpecialAirSEnd,
    ftPe_MS_SpecialAirSHit,
    ftPe_MS_SpecialAirS,
    ftPe_MS_SpecialHiStart,
    ftPe_MS_Unk_362,
    ftPe_MS_SpecialAirHiStart,
    ftPe_MS_Unk_364,
    ftPe_MS_SpecialN,
    ftPe_MS_SpecialNAttack,
    ftPe_MS_SpecialAirN,
    ftPe_MS_SpecialAirNAttack,
    ftPe_MS_ParasolOpening,
    ftPe_MS_ParasolOpen,
} ftPeach_MotionState;

typedef enum ftPe_AnimId {
    ftPe_AnimId_Float = ftCo_AnimId_Count,
    ftPe_AnimId_FloatEnd0,
    ftPe_AnimId_FloatEnd1,
    ftPe_AnimId_AttackS4_0,
    ftPe_AnimId_AttackS4_1,
    ftPe_AnimId_AttackS4_2,
    ftPe_AnimId_Unk301,
    ftPe_AnimId_SpecialSStart,
    ftPe_AnimId_SpecialSEnd,
    ftPe_AnimId_SpecialAirS,
    ftPe_AnimId_Unk305,
    ftPe_AnimId_SpecialAirSEnd_0,
    ftPe_AnimId_SpecialAirSEnd_1,
    ftPe_AnimId_SpecialHiStart,
    ftPe_AnimId_MS_362,
    ftPe_AnimId_SpecialAirHiStart,
    ftPe_AnimId_MS_364,
    ftPe_AnimId_SpecialN,
    ftPe_AnimId_SpecialNAttack,
    ftPe_AnimId_SpecialAirN,
    ftPe_AnimId_SpecialAirNAttack,
    ftPe_AnimId_ParasolOpen,
    ftPe_AnimId_ParasolFallSpecial,
} ftPe_AnimId;

#endif
