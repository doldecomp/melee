#ifndef MELEE_FT_CHARA_FTLINK_FORWARD_H
#define MELEE_FT_CHARA_FTLINK_FORWARD_H

#include "ft/forward.h"
#include "ftCommon/forward.h"

typedef struct ftLk_DatAttrs ftLk_DatAttrs;
typedef struct ftLk_FighterVars ftLk_FighterVars;
typedef union ftLk_MotionVars ftLk_MotionVars;

static MotionFlags const ftLk_MF_Base0 =
    Ft_MF_SkipModel | Ft_MF_SkipThrowException;

static MotionFlags const ftLk_MF_Base1 = Ft_MF_SkipItemVis | Ft_MF_FreezeState;

static MotionFlags const ftLk_MF_Base2 = ftLk_MF_Base1 | Ft_MF_KeepFastFall;

static MotionFlags const ftLk_MF_Base3 = ftLk_MF_Base0 | Ft_MF_UnkUpdatePhys;

static MotionFlags const ftLk_MF_AttackS42 = ftLk_MF_Base2 | Ft_MF_SkipHit;

static MotionFlags const ftLk_MF_SpecialN = ftLk_MF_Base2 | ftLk_MF_Base3;

static MotionFlags const ftLk_MF_SpecialNFullyCharged =
    ftLk_MF_SpecialN | Ft_MF_Unk19;

static MotionFlags const ftLk_MF_SpecialAirNCharge =
    ftLk_MF_SpecialN | Ft_MF_SkipParasol;

static MotionFlags const ftLk_MF_SpecialAirNFullyCharged =
    ftLk_MF_SpecialNFullyCharged | Ft_MF_SkipParasol;

static MotionFlags const ftLk_MF_SpecialAirNFire =
    ftLk_MF_SpecialAirNCharge | Ft_MF_UnkUpdatePhys;

static MotionFlags const ftLk_MF_SpecialSThrow =
    ftLk_MF_Base3 | ftLk_MF_Base1 | Ft_MF_KeepGfx;

static MotionFlags const ftLk_MF_SpecialSCatch =
    ftLk_MF_SpecialSThrow | Ft_MF_UnkUpdatePhys;

static MotionFlags const ftLk_MF_SpecialAirSThrow =
    ftLk_MF_SpecialSThrow | ftLk_MF_Base3 | Ft_MF_SkipParasol;

static MotionFlags const ftLk_MF_SpecialAirSThrowEmpty =
    ftLk_MF_SpecialSCatch | ftLk_MF_Base1 | Ft_MF_SkipParasol;

static MotionFlags const ftLk_MF_SpecialHi =
    Ft_MF_KeepFastFall | Ft_MF_KeepGfx | Ft_MF_SkipModel | Ft_MF_KeepSfx |
    Ft_MF_SkipItemVis | Ft_MF_UnkUpdatePhys | Ft_MF_FreezeState;

static MotionFlags const ftLk_MF_SpecialLw =
    Ft_MF_KeepColAnimHitStatus | Ft_MF_SkipModel | Ft_MF_SkipItemVis |
    Ft_MF_UnkUpdatePhys | Ft_MF_FreezeState;

static MotionFlags const ftLk_MF_SpecialAirLw =
    ftLk_MF_SpecialLw | Ft_MF_SkipParasol;

static MotionFlags const ftLk_MF_ZairCatch =
    Ft_MF_SkipModelPartVis | Ft_MF_SkipMetalB;

typedef enum ftLink_MotionState {
    ftLk_MS_AttackS42 = ftCo_MS_Count,
    ftLk_MS_AppealSR,
    ftLk_MS_AppealSL,
    ftLk_MS_SpecialNStart,
    ftLk_MS_SpecialNLoop,
    ftLk_MS_SpecialNEnd,
    ftLk_MS_SpecialAirNStart,
    ftLk_MS_SpecialAirNLoop,
    ftLk_MS_SpecialAirNEnd,
    ftLk_MS_SpecialS1,
    ftLk_MS_SpecialS2,
    ftLk_MS_SpecialS1Empty,
    ftLk_MS_SpecialAirS1,
    ftLk_MS_SpecialAirS2,
    ftLk_MS_SpecialAirS1Empty,
    ftLk_MS_SpecialHi,
    ftLk_MS_SpecialAirHi,
    ftLk_MS_SpecialLw,
    ftLk_MS_SpecialAirLw,
    ftLk_MS_AirCatch,
    ftLk_MS_AirCatchHit,
    ftLk_MS_Count,
    ftLk_MS_SelfCount = ftLk_MS_Count - ftCo_MS_Count,
} ftLink_MotionState;

typedef enum ftLk_SpecialNIndex {
    ftLk_SpecialNIndex_Start,
    ftLk_SpecialNIndex_Loop,
    ftLk_SpecialNIndex_End,
    ftLk_SpecialNIndex_AirStart,
    ftLk_SpecialNIndex_AirLoop,
    ftLk_SpecialNIndex_AirEnd,
    ftLk_SpecialNIndex_None,
} ftLk_SpecialNIndex;

typedef enum ftLk_Submotion {
    ftLk_SM_AttackS42 = ftCo_SM_Count,
    ftLk_SM_SpecialNStart,
    ftLk_SM_SpecialNLoop,
    ftLk_SM_SpecialNEnd,
    ftLk_SM_SpecialAirNStart,
    ftLk_SM_SpecialAirNLoop,
    ftLk_SM_SpecialAirNEnd,
    ftLk_SM_SpecialS1,
    ftLk_SM_SpecialS2,
    ftLk_SM_SpecialS1Empty,
    ftLk_SM_SpecialAirS1,
    ftLk_SM_SpecialAirS2,
    ftLk_SM_SpecialAirS1Empty,
    ftLk_SM_SpecialHi,
    ftLk_SM_SpecialAirHi,
    ftLk_SM_SpecialLw,
    ftLk_SM_SpecialAirLw,
    ftLk_SM_AirCatch,
    ftLk_SM_AirCatchHit,
    ftLk_SM_Count,
    ftLk_SM_SelfCount = ftLk_SM_Count - ftCo_SM_Count,
} ftLk_Submotion;

#endif
