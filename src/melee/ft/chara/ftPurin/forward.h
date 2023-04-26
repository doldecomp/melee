#ifndef MELEE_FT_CHARA_FTPURIN_FORWARD_H
#define MELEE_FT_CHARA_FTPURIN_FORWARD_H

#include <platform.h>
#include "ft/forward.h"
#include "ftCommon/forward.h"

static MotionFlags const ftPr_MF_Special ATTRIBUTE_USED =
    Ft_MF_SkipModel | Ft_MF_SkipItemVis | Ft_MF_UnkUpdatePhys |
    Ft_MF_FreezeState;

static MotionFlags const ftPr_MF_SpecialHi ATTRIBUTE_USED =
    ftPr_MF_Special | Ft_MF_KeepFastFall | Ft_MF_KeepGfx;

static MotionFlags const ftPr_MF_SpecialLw ATTRIBUTE_USED =
    ftPr_MF_Special | Ft_MF_KeepColAnimHitStatus;

static MotionFlags const ftPr_MF_SpecialN ATTRIBUTE_USED =
    ftPr_MF_Special | Ft_MF_KeepFastFall | Ft_MF_KeepSfx;

static MotionFlags const ftPr_MF_SpecialS ATTRIBUTE_USED =
    ftPr_MF_Special | Ft_MF_KeepGfx | Ft_MF_KeepSfx;

static MotionFlags const ftPr_MF_SpecialAirHi ATTRIBUTE_USED =
    ftPr_MF_SpecialHi | Ft_MF_SkipParasol;

static MotionFlags const ftPr_MF_SpecialAirLw ATTRIBUTE_USED =
    ftPr_MF_SpecialLw | Ft_MF_SkipParasol;

static MotionFlags const ftPr_MF_SpecialAirN ATTRIBUTE_USED =
    ftPr_MF_SpecialN | Ft_MF_SkipParasol;

static MotionFlags const ftPr_MF_SpecialAirS ATTRIBUTE_USED =
    ftPr_MF_SpecialS | Ft_MF_SkipParasol;

static MotionFlags const ftPr_MF_SpecialNCharged ATTRIBUTE_USED =
    ftPr_MF_SpecialN | Ft_MF_Unk19;

static MotionFlags const ftPr_SpecialAirNCharged ATTRIBUTE_USED =
    ftPr_MF_SpecialNCharged | Ft_MF_SkipParasol;

typedef enum ftPurin_MotionState {
    ftPr_MS_Jump2 = ftCo_MS_Count,
    ftPr_MS_Jump3,
    ftPr_MS_Jump4,
    ftPr_MS_Jump5,
    ftPr_MS_Jump6,
    ftPr_MS_SpecialN_ChargeStartR,
    ftPr_MS_SpecialN_ChargeStartL,
    ftPr_MS_SpecialN_ChargeLoop,
    ftPr_MS_SpecialN_ChargeFull,
    ftPr_MS_SpecialN_ChargeRelease,
    ftPr_MS_SpecialN_StartTurn,
    ftPr_MS_SpecialN_EndR,
    ftPr_MS_SpecialN_EndL,
    ftPr_MS_SpecialAirN_ChargeStartR,
    ftPr_MS_SpecialAirN_ChargeStartL,
    ftPr_MS_SpecialAirN_ChargeLoop,
    ftPr_MS_SpecialAirN_ChargeFull,
    ftPr_MS_SpecialAirN_ChargeRelease,
    ftPr_MS_SpecialAirN_StartTurn,
    ftPr_MS_SpecialAirN_EndR,
    ftPr_MS_SpecialAirN_EndL,
    ftPr_MS_SpecialN_Hit,
    ftPr_MS_SpecialS,
    ftPr_MS_SpecialAirS,
    ftPr_MS_SpecialHiL,
    ftPr_MS_SpecialAirHiL,
    ftPr_MS_SpecialHiR,
    ftPr_MS_SpecialAirHiR,
    ftPr_MS_SpecialLwL,
    ftPr_MS_SpecialAirLwL,
    ftPr_MS_SpecialLwR,
    ftPr_MS_SpecialAirLwR,
} ftPurin_MotionState;

typedef enum ftPr_Submotion {
    ftPr_SM_JumpAerialF1 = ftCo_SM_Count,
    ftPr_SM_JumpAerialF2,
    ftPr_SM_JumpAerialF3,
    ftPr_SM_JumpAerialF4,
    ftPr_SM_JumpAerialF5,
    ftPr_SM_SpecialNStartR,
    ftPr_SM_SpecialNStartL,
    ftPr_SM_SpecialNChargeLoop,
    ftPr_SM_SpecialNChargeFull,
    ftPr_SM_SpecialNChargeRelease,
    ftPr_SM_SpecialNStartTurn,
    ftPr_SM_SpecialNEndR,
    ftPr_SM_SpecialNEndL,
    ftPr_SM_SpecialAirNStartR,
    ftPr_SM_SpecialAirNStartL,
    ftPr_SM_SpecialAirNChargeLoop,
    ftPr_SM_SpecialAirNChargeFull,
    ftPr_SM_SpecialAirNChargeRelease,
    ftPr_SM_SpecialAirNStartTurn,
    ftPr_SM_SpecialAirNEndR,
    ftPr_SM_SpecialAirNEndL,
    ftPr_SM_SpecialNHit,
    ftPr_SM_SpecialS,
    ftPr_SM_SpecialAirS,
    ftPr_SM_SpecialHiL,
    ftPr_SM_SpecialAirHiL,
    ftPr_SM_SpecialHiR,
    ftPr_SM_SpecialAirHiR,
    ftPr_SM_SpecialLwL,
    ftPr_SM_SpecialAirLwL,
    ftPr_SM_SpecialLwR,
    ftPr_SM_SpecialAirLwR,
} ftPr_Submotion;

#endif
