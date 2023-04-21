#ifndef MELEE_FT_CHARA_FTSAMUS_FORWARD_H
#define MELEE_FT_CHARA_FTSAMUS_FORWARD_H

#include <platform.h>
#include "ftCommon/forward.h"

typedef enum ftSamus_MotionState {
    ftSs_MS_SpecialLw = ftCo_MS_Count,
    ftSs_MS_SpecialAirLw,
    ftSs_MS_SpecialN_Start,
    ftSs_MS_SpecialN_Loop,
    ftSs_MS_SpecialN_End,
    ftSs_MS_SpecialN_Shoot,
    ftSs_MS_SpecialAirN_Start,
    ftSs_MS_SpecialAirN_Shoot,
    ftSs_MS_SpecialS,

    /// @todo name
    ftSs_MS_SpecialS_Smash,

    ftSs_MS_SpecialAirS,
    ftSs_MS_SpecialAir_Smash,
    ftSs_MS_SpecialHi,
    ftSs_MS_SpecialAirHi,

    /// @todo name
    ftSs_MS_SpecialLw_BombEnd,
    ftSs_MS_SpecialAirLw_Bomb,

    /// @todo name
    ftSs_MS_Zair,
    ftSs_MS_ZairCatch,
} ftSamus_MotionState;

#endif
