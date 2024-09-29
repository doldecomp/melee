#ifndef MELEE_FT_CHARA_FTPURIN_FORWARD_H
#define MELEE_FT_CHARA_FTPURIN_FORWARD_H

#include <platform.h>

#include "ft/forward.h"
#include "ftCommon/forward.h"

static MotionFlags const ftPr_MF_Special =
    Ft_MF_SkipModel | Ft_MF_SkipItemVis | Ft_MF_UnkUpdatePhys |
    Ft_MF_FreezeState;

static MotionFlags const ftPr_MF_SpecialHi =
    ftPr_MF_Special | Ft_MF_KeepFastFall | Ft_MF_KeepGfx;

static MotionFlags const ftPr_MF_SpecialLw =
    ftPr_MF_Special | Ft_MF_KeepColAnimHitStatus;

static MotionFlags const ftPr_MF_SpecialN =
    ftPr_MF_Special | Ft_MF_KeepFastFall | Ft_MF_KeepSfx;

static MotionFlags const ftPr_MF_SpecialS =
    ftPr_MF_Special | Ft_MF_KeepGfx | Ft_MF_KeepSfx;

static MotionFlags const ftPr_MF_SpecialAirHi =
    ftPr_MF_SpecialHi | Ft_MF_SkipParasol;

static MotionFlags const ftPr_MF_SpecialAirLw =
    ftPr_MF_SpecialLw | Ft_MF_SkipParasol;

static MotionFlags const ftPr_MF_SpecialAirN =
    ftPr_MF_SpecialN | Ft_MF_SkipParasol;

static MotionFlags const ftPr_MF_SpecialAirS =
    ftPr_MF_SpecialS | Ft_MF_SkipParasol;

static MotionFlags const ftPr_MF_SpecialNCharged =
    ftPr_MF_SpecialN | Ft_MF_Unk19;

static MotionFlags const ftPr_SpecialAirNCharged =
    ftPr_MF_SpecialNCharged | Ft_MF_SkipParasol;

typedef enum ftPurin_MotionState {
    ftPr_MS_JumpAerialF1 = ftCo_MS_Count,
    ftPr_MS_JumpAerialF2,
    ftPr_MS_JumpAerialF3,
    ftPr_MS_JumpAerialF4,
    ftPr_MS_JumpAerialF5,
    ftPr_MS_SpecialNStartR,
    ftPr_MS_SpecialNStartL,
    ftPr_MS_SpecialNLoop,
    ftPr_MS_SpecialNFull,
    ftPr_MS_SpecialNRelease,
    ftPr_MS_SpecialNTurn,
    ftPr_MS_SpecialNEndR,
    ftPr_MS_SpecialNEndL,
    ftPr_MS_SpecialAirNStartR,
    ftPr_MS_SpecialAirNStartL,
    ftPr_MS_SpecialAirNChargeLoop,
    ftPr_MS_SpecialAirNChargeFull,
    ftPr_MS_SpecialAirNChargeRelease,
    ftPr_MS_SpecialAirNStartTurn,
    ftPr_MS_SpecialAirNEndR,
    ftPr_MS_SpecialAirNEndL,
    ftPr_MS_SpecialNHit,
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
    ftPr_MS_Count,
    ftPr_MS_SelfCount = ftPr_MS_Count - ftCo_MS_Count,
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
    ftPr_SM_Count,
    ftPr_SM_SelfCount = ftPr_SM_Count - ftCo_SM_Count,
} ftPr_Submotion;

#endif
