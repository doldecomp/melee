#ifndef MELEE_FT_CHARA_FTDONKEY_FORWARD_H
#define MELEE_FT_CHARA_FTDONKEY_FORWARD_H

#include <platform.h>

#include "ft/forward.h"
#include "ftCommon/forward.h"

static MotionFlags const ftDk_MF_Special =
    ftCo_MF_Special | Ft_MF_SkipModel | Ft_MF_KeepSfx | Ft_MF_SkipItemVis |
    Ft_MF_UnkUpdatePhys | Ft_MF_FreezeState;

static MotionFlags const ftDk_MF_SpecialN =
    ftDk_MF_Special | Ft_MF_KeepFastFall;

static MotionFlags const ftDk_MF_SpecialS = ftDk_MF_Special | Ft_MF_KeepGfx;

static MotionFlags const ftDk_MF_SpecialHi =
    ftDk_MF_Special | Ft_MF_KeepFastFall | Ft_MF_KeepGfx;

static MotionFlags const ftDk_MF_SpecialLwStart =
    ftDk_MF_Special | Ft_MF_KeepColAnimHitStatus;

static MotionFlags const ftDk_MF_SpecialAirN =
    ftDk_MF_Special | Ft_MF_KeepFastFall | Ft_MF_SkipParasol;

static MotionFlags const ftDk_MF_SpecialAirS =
    ftDk_MF_Special | Ft_MF_KeepGfx | Ft_MF_SkipParasol;

static MotionFlags const ftDk_MF_SpecialAirHi =
    ftDk_MF_Special | Ft_MF_KeepFastFall | Ft_MF_KeepGfx | Ft_MF_SkipParasol;

static MotionFlags const ftDk_MF_MS_386 =
    ftDk_MF_Special | Ft_MF_KeepColAnimHitStatus | Ft_MF_SkipParasol;

static MotionFlags const ftDk_MF_SpecialLw =
    ftDk_MF_Special | Ft_MF_KeepColAnimHitStatus | Ft_MF_Unk19;

static MotionFlags const ftDk_MF_MS_350 =
    Ft_MF_KeepSwordTrail | Ft_MF_Unk19 | Ft_MF_SkipModelPartVis;

static MotionFlags const ftDk_MF_Cargo =
    Ft_MF_SkipModel | Ft_MF_SkipAnimVel | Ft_MF_FreezeState | Ft_MF_SkipMetalB;

static MotionFlags const ftDk_MF_CargoThrow =
    ftDk_MF_Cargo | Ft_MF_SkipHit | Ft_MF_SkipItemVis;

static MotionFlags const ftDk_MF_CargoThrowF =
    ftDk_MF_CargoThrow | Ft_MF_KeepFastFall;

static MotionFlags const ftDk_MF_CargoThrowB =
    ftDk_MF_CargoThrow | Ft_MF_KeepGfx;

static MotionFlags const ftDk_MF_CargoThrowHi =
    ftDk_MF_CargoThrow | Ft_MF_KeepFastFall | Ft_MF_KeepGfx;

static MotionFlags const ftDk_MF_CargoThrowLw =
    ftDk_MF_CargoThrow | Ft_MF_KeepColAnimHitStatus;

static MotionFlags const ftDk_MF_CargoWait =
    ftDk_MF_Cargo | Ft_MF_KeepFastFall | Ft_MF_KeepColAnimHitStatus |
    Ft_MF_Unk19;

static MotionFlags const ftDk_MF_CargoTurn =
    ftDk_MF_CargoWait | Ft_MF_KeepAccessory;

static MotionFlags const ftDk_MF_CargoWalk =
    ftDk_MF_CargoWait | Ft_MF_UpdateCmd;

static MotionFlags const ftDk_MF_CargoJump =
    ftDk_MF_CargoWait | Ft_MF_SkipNametagVis;

static MotionFlags const ftDk_MF_MS_360 =
    ftDk_MF_CargoWait | Ft_MF_KeepSwordTrail;

static MotionFlags const ftDk_MF_MS_341 = Ft_MF_Unk19 | Ft_MF_SkipModelPartVis;

static MotionFlags const ftDk_MF_Move_53 =
    ftDk_MF_MS_341 | Ft_MF_SkipAnimVel | Ft_MF_Unk06;

static MotionFlags const ftDk_MF_MS_342_Base =
    ftDk_MF_Move_53 | Ft_MF_KeepColAnimHitStatus;

static MotionFlags const ftDk_MF_MS_342 =
    ftDk_MF_MS_342_Base | Ft_MF_KeepGfx | Ft_MF_UpdateCmd;

static MotionFlags const ftDk_MF_MS_345 =
    ftDk_MF_MS_342_Base | Ft_MF_KeepAccessory;

static MotionFlags const ftDk_MF_MS_348 = ftDk_MF_Move_53 |
                                          Ft_MF_KeepFastFall | Ft_MF_SkipHit |
                                          Ft_MF_SkipNametagVis;

typedef enum ftDk_MotionState {
    ftDk_MS_HeavyWait = ftCo_MS_Count,
    ftDk_MS_HeavyWalkSlow,
    ftDk_MS_HeavyWalkMiddle,
    ftDk_MS_HeavyWalkFast,
    ftDk_MS_HeavyTurn,
    ftDk_MS_HeavyKneebend,
    ftDk_MS_HeavyFall,
    ftDk_MS_HeavyJump,
    ftDk_MS_HeavyLanding,
    ftDk_MS_HeavyWait2,
    ftDk_MS_ThrowFWait0,
    ftDk_MS_ThrowFWalkSlow,
    ftDk_MS_ThrowFWalkMiddle,
    ftDk_MS_ThrowFWalkFast,
    ftDk_MS_ThrowFTurn,
    ftDk_MS_ThrowFKneebend,
    ftDk_MS_ThrowFFall,
    ftDk_MS_ThrowFJump,
    ftDk_MS_ThrowFLanding,
    ftDk_MS_ThrowFWait2,
    ftDk_MS_ThrowFF,
    ftDk_MS_ThrowFB,
    ftDk_MS_ThrowFHi,
    ftDk_MS_ThrowFLw,
    ftDk_MS_ThrowAirFF,
    ftDk_MS_ThrowAirFB,
    ftDk_MS_ThrowAirFHi,
    ftDk_MS_ThrowAirFLw,
    ftDk_MS_SpecialNStart,
    /* 172 */ ftDk_MS_SpecialNLoop,
    ftDk_MS_SpecialNCancel,
    ftDk_MS_SpecialN,
    ftDk_MS_SpecialNFull,
    ftDk_MS_SpecialAirNStart,
    ftDk_MS_SpecialAirNLoop,
    ftDk_MS_SpecialAirNCancel,
    ftDk_MS_SpecialAirN,
    ftDk_MS_SpecialAirNFull,
    ftDk_MS_SpecialS,
    ftDk_MS_SpecialAirS,
    ftDk_MS_SpecialHi,
    ftDk_MS_SpecialAirHi,
    ftDk_MS_SpecialLwStart,
    ftDk_MS_SpecialLwLoop,
    ftDk_MS_SpecialLwEnd0,
    ftDk_MS_SpecialLwEnd1,
    ftDk_MS_Count,
    ftDk_MS_SelfCount = ftDk_MS_Count - ftCo_MS_Count,
} ftDk_MotionState;

typedef enum ftDk_Submotion {
    ftDk_SM_HeavyWait = ftCo_SM_Count,
    ftDk_SM_HeavyWalkSlow,
    ftDk_SM_HeavyWalkMiddle,
    ftDk_SM_HeavyWalkFast,
    ftDk_SM_HeavyTurn,
    ftDk_SM_HeavyKneebend,
    ftDk_SM_HeavyFall,
    ftDk_SM_HeavyJump,
    ftDk_SM_HeavyLanding,
    ftDk_SM_HeavyWait2,
    ftDk_SM_ThrowFWait0,
    ftDk_SM_ThrowFWalkSlow,
    ftDk_SM_ThrowFWalkMiddle,
    ftDk_SM_ThrowFWalkFast,
    ftDk_SM_ThrowFTurn,
    ftDk_SM_ThrowFKneebend,
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
    ftDk_SM_Count,
    ftDk_SM_SelfCount = ftDk_SM_Count - ftCo_SM_Count,
} ftDk_Submotion;

#endif
