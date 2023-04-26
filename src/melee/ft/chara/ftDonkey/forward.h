#ifndef MELEE_FT_CHARA_FTDONKEY_FORWARD_H
#define MELEE_FT_CHARA_FTDONKEY_FORWARD_H

#include <platform.h>
#include "ft/forward.h"
#include "ftCommon/forward.h"

static MotionFlags const ftDk_MF_Special ATTRIBUTE_USED =
    ftCo_MF_Special | Ft_MF_SkipModel | Ft_MF_KeepSfx | Ft_MF_SkipItemVis |
    Ft_MF_UnkUpdatePhys | Ft_MF_FreezeState;

static MotionFlags const ftDk_MF_SpecialN ATTRIBUTE_USED =
    ftDk_MF_Special | Ft_MF_KeepFastFall;

static MotionFlags const ftDk_MF_SpecialS ATTRIBUTE_USED =
    ftDk_MF_Special | Ft_MF_KeepGfx;

static MotionFlags const ftDk_MF_SpecialHi ATTRIBUTE_USED =
    ftDk_MF_Special | Ft_MF_KeepFastFall | Ft_MF_KeepGfx;

static MotionFlags const ftDk_MF_SpecialLwStart ATTRIBUTE_USED =
    ftDk_MF_Special | Ft_MF_KeepColAnimHitStatus;

static MotionFlags const ftDk_MF_SpecialAirN ATTRIBUTE_USED =
    ftDk_MF_Special | Ft_MF_KeepFastFall | Ft_MF_SkipParasol;

static MotionFlags const ftDk_MF_SpecialAirS ATTRIBUTE_USED =
    ftDk_MF_Special | Ft_MF_KeepGfx | Ft_MF_SkipParasol;

static MotionFlags const ftDk_MF_SpecialAirHi ATTRIBUTE_USED =
    ftDk_MF_Special | Ft_MF_KeepFastFall | Ft_MF_KeepGfx | Ft_MF_SkipParasol;

static MotionFlags const ftDk_MF_MS_386 ATTRIBUTE_USED =
    ftDk_MF_Special | Ft_MF_KeepColAnimHitStatus | Ft_MF_SkipParasol;

static MotionFlags const ftDk_MF_SpecialLw ATTRIBUTE_USED =
    ftDk_MF_Special | Ft_MF_KeepColAnimHitStatus | Ft_MF_Unk19;

static MotionFlags const ftDk_MF_MS_350 ATTRIBUTE_USED =
    Ft_MF_KeepSwordTrail | Ft_MF_Unk19 | Ft_MF_SkipModelPartVis;

static MotionFlags const ftDk_MF_Cargo ATTRIBUTE_USED =
    Ft_MF_SkipModel | Ft_MF_SkipAnimVel | Ft_MF_FreezeState | Ft_MF_SkipMetalB;

static MotionFlags const ftDk_MF_CargoThrow ATTRIBUTE_USED =
    ftDk_MF_Cargo | Ft_MF_SkipHit | Ft_MF_SkipItemVis;

static MotionFlags const ftDk_MF_CargoThrowF ATTRIBUTE_USED =
    ftDk_MF_CargoThrow | Ft_MF_KeepFastFall;

static MotionFlags const ftDk_MF_CargoThrowB ATTRIBUTE_USED =
    ftDk_MF_CargoThrow | Ft_MF_KeepGfx;

static MotionFlags const ftDk_MF_CargoThrowHi ATTRIBUTE_USED =
    ftDk_MF_CargoThrow | Ft_MF_KeepFastFall | Ft_MF_KeepGfx;

static MotionFlags const ftDk_MF_CargoThrowLw ATTRIBUTE_USED =
    ftDk_MF_CargoThrow | Ft_MF_KeepColAnimHitStatus;

static MotionFlags const ftDk_MF_CargoWait ATTRIBUTE_USED =
    ftDk_MF_Cargo | Ft_MF_KeepFastFall | Ft_MF_KeepColAnimHitStatus |
    Ft_MF_Unk19;

static MotionFlags const ftDk_MF_CargoTurn ATTRIBUTE_USED =
    ftDk_MF_CargoWait | Ft_MF_KeepAccessory;

static MotionFlags const ftDk_MF_CargoWalk ATTRIBUTE_USED =
    ftDk_MF_CargoWait | Ft_MF_UpdateCmd;

static MotionFlags const ftDk_MF_CargoJump ATTRIBUTE_USED =
    ftDk_MF_CargoWait | Ft_MF_SkipNametagVis;

static MotionFlags const ftDk_MF_MS_360 ATTRIBUTE_USED =
    ftDk_MF_CargoWait | Ft_MF_KeepSwordTrail;

static MotionFlags const ftDk_MF_MS_341 ATTRIBUTE_USED =
    Ft_MF_Unk19 | Ft_MF_SkipModelPartVis;

static MotionFlags const ftDk_MF_Move_53 ATTRIBUTE_USED =
    ftDk_MF_MS_341 | Ft_MF_SkipAnimVel | Ft_MF_Unk06;

static MotionFlags const ftDk_MF_MS_342_Base ATTRIBUTE_USED =
    ftDk_MF_Move_53 | Ft_MF_KeepColAnimHitStatus;

static MotionFlags const ftDk_MF_MS_342 ATTRIBUTE_USED =
    ftDk_MF_MS_342_Base | Ft_MF_KeepGfx | Ft_MF_UpdateCmd;

static MotionFlags const ftDk_MF_MS_345 ATTRIBUTE_USED =
    ftDk_MF_MS_342_Base | Ft_MF_KeepAccessory;

static MotionFlags const ftDk_MF_MS_348 ATTRIBUTE_USED =
    ftDk_MF_Move_53 | Ft_MF_KeepFastFall | Ft_MF_SkipHit |
    Ft_MF_SkipNametagVis;

typedef enum ftDk_MotionState {
    ftDk_MS_Unk341 = ftCo_MS_Count,
    ftDk_MS_Unk342,
    ftDk_MS_Unk343,
    ftDk_MS_Unk344,
    ftDk_MS_Unk345,
    ftDk_MS_Unk346,
    ftDk_MS_Unk347,
    ftDk_MS_Unk348,
    ftDk_MS_Unk349,
    ftDk_MS_Unk350,
    ftDk_MS_CargoWait,
    ftDk_MS_CargoWalkSlow,
    ftDk_MS_CargoWalkMiddle,
    ftDk_MS_CargoWalkFast,
    ftDk_MS_CargoTurn,
    ftDk_MS_CargoKneebend,
    ftDk_MS_CargoFall,
    ftDk_MS_CargoJump,
    ftDk_MS_CargoLanding,
    ftDk_MS_Unk360,
    ftDk_MS_CargoThrowF,
    ftDk_MS_CargoThrowB,
    ftDk_MS_CargoThrowHi,
    ftDk_MS_CargoThrowLw,
    ftDk_MS_CargoAirThrowF,
    ftDk_MS_CargoAirThrowB,
    ftDk_MS_CargoAirThrowHi,
    ftDk_MS_CargoAirThrowLw,
    ftDk_MS_SpecialNChargeStart,
    ftDk_MS_SpecialNChargeLoop,
    ftDk_MS_SpecialNChargeStop,
    ftDk_MS_SpecialNEarlyRelease,
    ftDk_MS_SpecialNFullRelease,
    ftDk_MS_SpecialAirNChargeStart,
    ftDk_MS_SpecialAirNChargeLoop,
    ftDk_MS_SpecialAirNChargeStop,
    ftDk_MS_SpecialAirNEarlyRelease,
    ftDk_MS_SpecialAirNFullRelease,
    ftDk_MS_SpecialS,
    ftDk_MS_SpecialAirS,
    ftDk_MS_SpecialHi,
    ftDk_MS_SpecialAirHi,
    ftDk_MS_SpecialLwStart,
    ftDk_MS_SpecialLwLoop,
    ftDk_MS_SpecialLwEnd,
    ftDk_MS_Unk386,
} ftDk_MotionState;

typedef enum ftDk_Submotion {
    ftDk_SM_HeavyWait0 = ftCo_SM_Count,
    ftDk_SM_HeavyWalkSlow,
    ftDk_SM_HeavyWalkMiddle,
    ftDk_SM_HeavyWalkFast,
    ftDk_SM_HeavyTurn,
    ftDk_SM_HeavyWait1,
    ftDk_SM_HeavyFall,
    ftDk_SM_HeavyJump,
    ftDk_SM_HeavyLanding,
    ftDk_SM_HeavyWait2,
    ftDk_SM_ThrowFWait0,
    ftDk_SM_ThrowFWalkSlow,
    ftDk_SM_ThrowFWalkMiddle,
    ftDk_SM_ThrowFWalkFast,
    ftDk_SM_ThrowFTurn,
    ftDk_SM_ThrowFWait1,
    ftDk_SM_ThrowFFall,
    ftDk_SM_ThrowFJump,
    ftDk_SM_ThrowFLanding,
    ftDk_SM_ThrowFWait2,
    ftDk_SM_ThrowFF,
    ftDk_SM_ThrowFB,
    ftDk_SM_ThrowFHi,
    ftDk_SM_ThrowFLw,
    ftDk_SM_SpecialNStart,
    ftDk_SM_SpecialNLoop,
    ftDk_SM_SpecialNCancel,
    ftDk_SM_SpecialN,
    ftDk_SM_SpecialNFull,
    ftDk_SM_SpecialAirNStart,
    ftDk_SM_SpecialAirNLoop,
    ftDk_SM_SpecialAirNCancel,
    ftDk_SM_SpecialAirN,
    ftDk_SM_SpecialAirNFull,
    ftDk_SM_SpecialS,
    ftDk_SM_SpecialAirS,
    ftDk_SM_SpecialHi,
    ftDk_SM_SpecialAirHi,
    ftDk_SM_SpecialLwStart,
    ftDk_SM_SpecialLwLoop,
    ftDk_SM_SpecialLwEnd0,
    ftDk_SM_SpecialLwEnd1,
} ftDk_Submotion;

#endif
