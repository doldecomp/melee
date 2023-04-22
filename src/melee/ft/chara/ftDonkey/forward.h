#ifndef MELEE_FT_CHARA_FTDONKEY_FORWARD_H
#define MELEE_FT_CHARA_FTDONKEY_FORWARD_H

#include <platform.h>
#include "ft/forward.h"
#include "ftCommon/forward.h"

static Fighter_MotionStateChangeFlags const ftDk_MF_Special =
    (1 << 4) | (1 << 9) | (1 << 18) | (1 << 20) | (1 << 21);

static Fighter_MotionStateChangeFlags const ftDk_MF_SpecialN ATTRIBUTE_USED =
    ftDk_MF_Special | (1 << 0);

static Fighter_MotionStateChangeFlags const ftDk_MF_SpecialS ATTRIBUTE_USED =
    ftDk_MF_Special | (1 << 1);

static Fighter_MotionStateChangeFlags const ftDk_MF_SpecialHi ATTRIBUTE_USED =
    ftDk_MF_Special | (1 << 0) | (1 << 1);

static Fighter_MotionStateChangeFlags const ftDk_MF_SpecialLwStart
    ATTRIBUTE_USED = ftDk_MF_Special | (1 << 2);

static Fighter_MotionStateChangeFlags const ftDk_MF_SpecialAirN
    ATTRIBUTE_USED = ftDk_MF_Special | (1 << 0) | (1 << 10);

static Fighter_MotionStateChangeFlags const ftDk_MF_SpecialAirS
    ATTRIBUTE_USED = ftDk_MF_Special | (1 << 1) | (1 << 10);

static Fighter_MotionStateChangeFlags const ftDk_MF_SpecialAirHi
    ATTRIBUTE_USED = ftDk_MF_Special | (1 << 0) | (1 << 1) | (1 << 10);

static Fighter_MotionStateChangeFlags const ftDk_MF_MS_386 ATTRIBUTE_USED =
    ftDk_MF_Special | (1 << 2) | (1 << 10);

static Fighter_MotionStateChangeFlags const ftDk_MF_SpecialLw ATTRIBUTE_USED =
    ftDk_MF_Special | (1 << 2) | (1 << 19);

static Fighter_MotionStateChangeFlags const ftDk_MF_MS_350 ATTRIBUTE_USED =
    (1 << 17) | (1 << 19) | (1 << 22);

static Fighter_MotionStateChangeFlags const ftDk_MF_Cargo =
    (1 << 4) | (1 << 5) | (1 << 21) | (1 << 23);

static Fighter_MotionStateChangeFlags const ftDk_MF_CargoThrow =
    ftDk_MF_Cargo | (1 << 3) | (1 << 18);

static Fighter_MotionStateChangeFlags const ftDk_MF_CargoThrowF
    ATTRIBUTE_USED = ftDk_MF_CargoThrow | (1 << 0);

static Fighter_MotionStateChangeFlags const ftDk_MF_CargoThrowB
    ATTRIBUTE_USED = ftDk_MF_CargoThrow | (1 << 1);

static Fighter_MotionStateChangeFlags const ftDk_MF_CargoThrowU
    ATTRIBUTE_USED = ftDk_MF_CargoThrow | (1 << 0) | (1 << 1);

static Fighter_MotionStateChangeFlags const ftDk_MF_CargoThrowD
    ATTRIBUTE_USED = ftDk_MF_CargoThrow | (1 << 2);

static Fighter_MotionStateChangeFlags const ftDk_MF_CargoWait =
    ftDk_MF_Cargo | (1 << 0) | (1 << 2) | (1 << 19);

static Fighter_MotionStateChangeFlags const ftDk_MF_CargoTurn ATTRIBUTE_USED =
    ftDk_MF_CargoWait | (1 << 13);

static Fighter_MotionStateChangeFlags const ftDk_MF_CargoWalk ATTRIBUTE_USED =
    ftDk_MF_CargoWait | (1 << 14);

static Fighter_MotionStateChangeFlags const ftDk_MF_CargoJump ATTRIBUTE_USED =
    ftDk_MF_CargoWait | (1 << 15);

static Fighter_MotionStateChangeFlags const ftDk_MF_MS_360 ATTRIBUTE_USED =
    ftDk_MF_CargoWait | (1 << 17);

static Fighter_MotionStateChangeFlags const ftDk_MF_MS_341 =
    (1 << 19) | (1 << 22);

static Fighter_MotionStateChangeFlags const ftDk_MF_Move_53 =
    ftDk_MF_MS_341 | (1 << 5) | (1 << 6);

static Fighter_MotionStateChangeFlags const ftDk_MF_MS_342_Base =
    ftDk_MF_Move_53 | (1 << 2);

static Fighter_MotionStateChangeFlags const ftDk_MF_MS_342 ATTRIBUTE_USED =
    ftDk_MF_MS_342_Base | (1 << 1) | (1 << 14);

static Fighter_MotionStateChangeFlags const ftDk_MF_MS_345 ATTRIBUTE_USED =
    ftDk_MF_MS_342_Base | (1 << 13);

static Fighter_MotionStateChangeFlags const ftDk_MF_MS_348 ATTRIBUTE_USED =
    ftDk_MF_Move_53 | (1 << 0) | (1 << 3) | (1 << 15);

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
