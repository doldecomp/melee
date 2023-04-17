#ifndef MELEE_FT_CHARA_FTLINK_FORWARD_H
#define MELEE_FT_CHARA_FTLINK_FORWARD_H

#include "ftCommon/forward.h"

typedef enum ftLink_MotionState {
    ftLk_MS_AttackS42 = ftCo_MS_Count,
    ftLk_MS_AppealR,
    ftLk_MS_AppealL,
    ftLk_MS_SpecialNCharge,
    ftLk_MS_SpecialNFullyCharged,
    ftLk_MS_SpecialNFire,
    ftLk_MS_SpecialAirNCharge,
    ftLk_MS_SpecialAirNFullyCharged,
    ftLk_MS_SpecialAirNFire,
    ftLk_MS_SpecialSThrow,
    ftLk_MS_SpecialSCatch,
    ftLk_MS_SpecialSThrowEmpty,
    ftLk_MS_SpecialAirSThrow,
    ftLk_MS_SpecialAirSCatch,
    ftLk_MS_SpecialAirSThrowEmpty,
    ftLk_MS_SpecialHi,
    ftLk_MS_SpecialAirHi,
    ftLk_MS_SpecialLw,
    ftLk_MS_SpecialAirLw,
    ftLk_MS_Zair,
    ftLk_MS_ZairCatch,
} ftLink_MotionState;

#endif
