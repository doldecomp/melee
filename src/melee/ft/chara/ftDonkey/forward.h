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

typedef enum ftDk_AnimId {
    ftDk_AnimId_MS_341 = ftCo_AnimId_Count,
    ftDk_AnimId_Unk296,
    ftDk_AnimId_MS_342_0,
    ftDk_AnimId_MS_342_1,
    ftDk_AnimId_MS_345,
    ftDk_AnimId_MS_346,
    ftDk_AnimId_MS_347,
    ftDk_AnimId_Unk302,
    ftDk_AnimId_MS_349,
    ftDk_AnimId_MS_350,
    ftDk_AnimId_CargoWait,
    ftDk_AnimId_CargoWalk0,
    ftDk_AnimId_CargoWalk1,
    ftDk_AnimId_CargoWalk2,
    ftDk_AnimId_CargoTurn,
    ftDk_AnimId_Unk310,
    ftDk_AnimId_CargoFall,
    ftDk_AnimId_CargoJump,
    ftDk_AnimId_CargoLanding,
    ftDk_AnimId_MS_360,
    ftDk_AnimId_CargoThrowF,
    ftDk_AnimId_CargoThrowB,
    ftDk_AnimId_CargoThrowHi,
    ftDk_AnimId_CargoThrowLw,
    ftDk_AnimId_SpecialNChargeStart,
    ftDk_AnimId_SpecialNChargeLoop,
    ftDk_AnimId_SpecialNChargeStop,
    ftDk_AnimId_SpecialNEarlyRelease,
    ftDk_AnimId_SpecialNFullRelease,
    ftDk_AnimId_SpecialAirNChargeStart,
    ftDk_AnimId_SpecialAirNChargeLoop,
    ftDk_AnimId_SpecialAirNChargeStop,
    ftDk_AnimId_SpecialAirNEarlyRelease,
    ftDk_AnimId_SpecialAirNFullRelease,
    ftDk_AnimId_SpecialS,
    ftDk_AnimId_SpecialAirS,
    ftDk_AnimId_SpecialHi,
    ftDk_AnimId_SpecialAirHi,
    ftDk_AnimId_SpecialLwStart,
    ftDk_AnimId_SpecialLwLoop,
    ftDk_AnimId_SpecialLwEnd,
    ftDk_AnimId_MS_386,
} ftDk_AnimId;

#endif
