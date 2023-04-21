#ifndef MELEE_FT_CHARA_FTPIKACHU_FORWARD_H
#define MELEE_FT_CHARA_FTPIKACHU_FORWARD_H

#include <platform.h>
#include "ftCommon/forward.h"

typedef enum ftPikachu_MotionState {
    ftPk_MS_SpecialN = ftCo_MS_Count,
    ftPk_MS_SpecialAirN,
    ftPk_MS_SpecialS_Start,
    ftPk_MS_SpecialS_Charge,
    ftPk_MS_Unk_345,
    ftPk_MS_SpecialS_Landing,
    ftPk_MS_SpecialS_Launch,
    ftPk_MS_SpecialAirS_Start,
    ftPk_MS_SpecialAirS_Charge,
    ftPk_MS_SpecialAirS,
    ftPk_MS_SpecialAirS_End,
    ftPk_MS_SpecialAirS_Launch,
    ftPk_MS_SpecialHi_Start,
    ftPk_MS_SpecialHi,
    ftPk_MS_SpecialHi_End,
    ftPk_MS_SpecialAirHi_Start,
    ftPk_MS_SpecialAir,
    ftPk_MS_SpecialAir_End,
    ftPk_MS_SpecialLw_Start,
    ftPk_MS_SpecialLw,
    ftPk_MS_SpecialLw_Hit,
    ftPk_MS_SpecialLw_End,
    ftPk_MS_SpecialAirLw_Start,
    ftPk_MS_SpecialAirLw,
    ftPk_MS_SpecialAirLw_Hit,
    ftPk_MS_SpecialAirLw_End,
} ftPikachu_MotionState;

#endif
