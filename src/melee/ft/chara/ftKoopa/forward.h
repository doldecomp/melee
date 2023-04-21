#ifndef MELEE_FT_CHARA_FTKOOPA_FORWARD_H
#define MELEE_FT_CHARA_FTKOOPA_FORWARD_H

#include <platform.h>
#include "ftCommon/forward.h"

typedef enum ftKoopa_MotionState {
    ftKp_MS_SpecialNStart = ftCo_MS_Count,
    ftKp_MS_SpecialNLoop,
    ftKp_MS_SpecialNEnd,
    ftKp_MS_SpecialAirNStart,
    ftKp_MS_SpecialAirNLoop,
    ftKp_MS_SpecialAirNEnd,
    ftKp_MS_SpecialS,
    ftKp_MS_SpecialSCatch,
    ftKp_MS_SpecialSCatchAttack,
    ftKp_MS_SpecialSWait,
    ftKp_MS_SpecialSThrowF,
    ftKp_MS_SpecialSThrowB,
    ftKp_MS_SpecialAirS,
    ftKp_MS_SpecialAirSCatch,
    ftKp_MS_SpecialAirSCatchAttack,
    ftKp_MS_SpecialAirSWait,
    ftKp_MS_SpecialAirSThrowF,
    ftKp_MS_SpecialAirSThrowB,
    ftKp_MS_SpecialHi,
    ftKp_MS_SpecialAirHi,
    ftKp_MS_SpecialLwStart,
    ftKp_MS_SpecialAirLw,
    ftKp_MS_SpecialLwLanding,
} ftKoopa_MotionState;

#endif
