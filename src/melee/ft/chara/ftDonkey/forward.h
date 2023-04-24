#ifndef MELEE_FT_CHARA_FTDONKEY_FORWARD_H
#define MELEE_FT_CHARA_FTDONKEY_FORWARD_H

#include <platform.h>
#include "ft/forward.h"
#include "ftCommon/forward.h"

static MotionFlags const ftDk_MF_Special ATTRIBUTE_USED =
    ftCo_MF_Special | FtStateChange_SkipUpdateModel |
    FtStateChange_PreserveSfx | FtStateChange_SkipUpdateItemVis |
    FtStateChange_Unk_UpdatePhys | FtStateChange_FreezeState;

static MotionFlags const ftDk_MF_SpecialN ATTRIBUTE_USED =
    ftDk_MF_Special | FtStateChange_PreserveFastFall;

static MotionFlags const ftDk_MF_SpecialS ATTRIBUTE_USED =
    ftDk_MF_Special | FtStateChange_PreserveGfx;

static MotionFlags const ftDk_MF_SpecialHi ATTRIBUTE_USED =
    ftDk_MF_Special | FtStateChange_PreserveFastFall |
    FtStateChange_PreserveGfx;

static MotionFlags const ftDk_MF_SpecialLwStart ATTRIBUTE_USED =
    ftDk_MF_Special | FtStateChange_PreserveColAnimHitStatus;

static MotionFlags const ftDk_MF_SpecialAirN ATTRIBUTE_USED =
    ftDk_MF_Special | FtStateChange_PreserveFastFall |
    FtStateChange_SkipUpdateParasol;

static MotionFlags const ftDk_MF_SpecialAirS ATTRIBUTE_USED =
    ftDk_MF_Special | FtStateChange_PreserveGfx |
    FtStateChange_SkipUpdateParasol;

static MotionFlags const ftDk_MF_SpecialAirHi ATTRIBUTE_USED =
    ftDk_MF_Special | FtStateChange_PreserveFastFall |
    FtStateChange_PreserveGfx | FtStateChange_SkipUpdateParasol;

static MotionFlags const ftDk_MF_MS_386 ATTRIBUTE_USED =
    ftDk_MF_Special | FtStateChange_PreserveColAnimHitStatus |
    FtStateChange_SkipUpdateParasol;

static MotionFlags const ftDk_MF_SpecialLw ATTRIBUTE_USED =
    ftDk_MF_Special | FtStateChange_PreserveColAnimHitStatus |
    FtStateChange_Unk_19;

static MotionFlags const ftDk_MF_MS_350 ATTRIBUTE_USED =
    FtStateChange_PreserveSwordTrail | FtStateChange_Unk_19 |
    FtStateChange_SkipUpdateModelPartVis;

static MotionFlags const ftDk_MF_Cargo ATTRIBUTE_USED =
    FtStateChange_SkipUpdateModel | FtStateChange_SkipUpdateAnimVel |
    FtStateChange_FreezeState | FtStateChange_SkipUpdateMetalB;

static MotionFlags const ftDk_MF_CargoThrow ATTRIBUTE_USED =
    ftDk_MF_Cargo | FtStateChange_SkipUpdateHit |
    FtStateChange_SkipUpdateItemVis;

static MotionFlags const ftDk_MF_CargoThrowF ATTRIBUTE_USED =
    ftDk_MF_CargoThrow | FtStateChange_PreserveFastFall;

static MotionFlags const ftDk_MF_CargoThrowB ATTRIBUTE_USED =
    ftDk_MF_CargoThrow | FtStateChange_PreserveGfx;

static MotionFlags const ftDk_MF_CargoThrowU ATTRIBUTE_USED =
    ftDk_MF_CargoThrow | FtStateChange_PreserveFastFall |
    FtStateChange_PreserveGfx;

static MotionFlags const ftDk_MF_CargoThrowD ATTRIBUTE_USED =
    ftDk_MF_CargoThrow | FtStateChange_PreserveColAnimHitStatus;

static MotionFlags const ftDk_MF_CargoWait ATTRIBUTE_USED =
    ftDk_MF_Cargo | FtStateChange_PreserveFastFall |
    FtStateChange_PreserveColAnimHitStatus | FtStateChange_Unk_19;

static MotionFlags const ftDk_MF_CargoTurn ATTRIBUTE_USED =
    ftDk_MF_CargoWait | FtStateChange_PreserveAccessory;

static MotionFlags const ftDk_MF_CargoWalk ATTRIBUTE_USED =
    ftDk_MF_CargoWait | FtStateChange_UpdateCmd;

static MotionFlags const ftDk_MF_CargoJump ATTRIBUTE_USED =
    ftDk_MF_CargoWait | FtStateChange_SkipUpdateNametagVis;

static MotionFlags const ftDk_MF_MS_360 ATTRIBUTE_USED =
    ftDk_MF_CargoWait | FtStateChange_PreserveSwordTrail;

static MotionFlags const ftDk_MF_MS_341 ATTRIBUTE_USED =
    FtStateChange_Unk_19 | FtStateChange_SkipUpdateModelPartVis;

static MotionFlags const ftDk_MF_Move_53 ATTRIBUTE_USED =
    ftDk_MF_MS_341 | FtStateChange_SkipUpdateAnimVel | FtStateChange_Unk_6;

static MotionFlags const ftDk_MF_MS_342_Base ATTRIBUTE_USED =
    ftDk_MF_Move_53 | FtStateChange_PreserveColAnimHitStatus;

static MotionFlags const ftDk_MF_MS_342 ATTRIBUTE_USED =
    ftDk_MF_MS_342_Base | FtStateChange_PreserveGfx | FtStateChange_UpdateCmd;

static MotionFlags const ftDk_MF_MS_345 ATTRIBUTE_USED =
    ftDk_MF_MS_342_Base | FtStateChange_PreserveAccessory;

static MotionFlags const ftDk_MF_MS_348 ATTRIBUTE_USED =
    ftDk_MF_Move_53 | FtStateChange_PreserveFastFall |
    FtStateChange_SkipUpdateHit | FtStateChange_SkipUpdateNametagVis;

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
    ftDk_MS_CargoThrowU,
    ftDk_MS_CargoThrowD,
    ftDk_MS_CargoAirThrowF,
    ftDk_MS_CargoAirThrowB,
    ftDk_MS_CargoAirThrowU,
    ftDk_MS_CargoAirThrowD,
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

#endif
