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

typedef enum ftPr_AnimId {
    ftPr_AnimId_MultiJump0 = ftCo_AnimId_Count,
    ftPr_AnimId_MultiJump1,
    ftPr_AnimId_MultiJump2,
    ftPr_AnimId_MultiJump3,
    ftPr_AnimId_MultiJump4,
    ftPr_AnimId_SpecialNChargeStart0,
    ftPr_AnimId_SpecialNChargeStart1,
    ftPr_AnimId_SpecialNChargeLoop,
    ftPr_AnimId_SpecialNChargeFull,
    ftPr_AnimId_SpecialNChargeRelease,
    ftPr_AnimId_SpecialNStartTurn,
    ftPr_AnimId_SpecialNEnd0,
    ftPr_AnimId_SpecialNEnd1,
    ftPr_AnimId_SpecialAirNChargeStart0,
    ftPr_AnimId_SpecialAirNChargeStart1,
    ftPr_AnimId_SpecialAirNChargeLoop,
    ftPr_AnimId_SpecialAirNChargeFull,
    ftPr_AnimId_SpecialAirNChargeRelease,
    ftPr_AnimId_SpecialAirNStartTurn,
    ftPr_AnimId_SpecialAirNEnd0,
    ftPr_AnimId_SpecialAirNEnd1,
    ftPr_AnimId_SpecialNHit,
    ftPr_AnimId_SpecialS,
    ftPr_AnimId_SpecialAirS,
    ftPr_AnimId_SpecialHi0,
    ftPr_AnimId_SpecialAirHi0,
    ftPr_AnimId_SpecialHi1,
    ftPr_AnimId_SpecialAirHi1,
    ftPr_AnimId_SpecialLw0,
    ftPr_AnimId_SpecialAirLw0,
    ftPr_AnimId_SpecialLw1,
    ftPr_AnimId_SpecialAirLw1,
} ftPr_AnimId;

#endif
