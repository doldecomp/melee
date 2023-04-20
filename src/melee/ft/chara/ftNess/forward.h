#ifndef MELEE_FT_CHARA_FTNESS_FORWARD_H
#define MELEE_FT_CHARA_FTNESS_FORWARD_H

#include "ftCommon/forward.h"

typedef enum ftNess_MotionState {
    ftNs_MS_AttackS4 = ftCo_MS_Count,
    ftNs_MS_AttackHi4,
    ftNs_MS_AttackHi4Charge,
    ftNs_MS_AttackHi4Release,
    ftNs_MS_AttackLw4,
    ftNs_MS_AttackLw4Charge,
    ftNs_MS_AttackLw4Release,
    ftNs_MS_SpecialNStart,
    ftNs_MS_SpecialNHold,
    ftNs_MS_SpecialNRelease,
    ftNs_MS_SpecialNEnd,
    ftNs_MS_SpecialAirNStart,
    ftNs_MS_SpecialAirNHold,
    ftNs_MS_SpecialAirNRelease,
    ftNs_MS_SpecialAirNEnd,
    ftNs_MS_SpecialS,
    ftNs_MS_SpecialAirS,
    ftNs_MS_SpecialHiStart,
    ftNs_MS_SpecialHiHold,
    ftNs_MS_SpecialHiEnd,
    ftNs_MS_SpecialHi,
    ftNs_MS_SpecialAirHiStart,
    ftNs_MS_SpecialAirHiHold,
    ftNs_MS_SpecialAirHiEnd,
    ftNs_MS_SpecialAirHi,
    ftNs_MS_SpecialAirHiRebound,
    ftNs_MS_SpecialLwStart,
    ftNs_MS_SpecialLwHold,
    ftNs_MS_SpecialLwHit,
    ftNs_MS_SpecialLwEnd,
    ftNs_MS_SpecialLwTurn,
    ftNs_MS_SpecialAirLwStart,
    ftNs_MS_SpecialAirLwHold,
    ftNs_MS_SpecialAirLwHit,
    ftNs_MS_SpecialAirLwEnd,
    ftNs_MS_SpecialAirLwTurn,
} ftNess_MotionState;

#endif
