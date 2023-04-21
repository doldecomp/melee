#ifndef MELEE_FT_CHARA_FTYOSHI_FORWARD_H
#define MELEE_FT_CHARA_FTYOSHI_FORWARD_H

#include "ftCommon/forward.h"

struct S_UNK_YOSHI1;

typedef enum ftYoshi_MotionState {
    ftYs_MS_Unk_341 = ftCo_MS_Count,
    ftYs_MS_Shield_Hold,
    ftYs_MS_Shield_Release,
    ftYs_MS_Shield_Damage,
    ftYs_MS_Shield_Start,
    ftYs_MS_SpecialN,
    ftYs_MS_SpecialN_CatchStart,
    ftYs_MS_SpecialN_Catch,
    ftYs_MS_SpecialAirN,
    ftYs_MS_SpecialAirN_CatchStart,
    ftYs_MS_SpecialAirN_Catch,
    ftYs_MS_SpecialS_Start,
    ftYs_MS_SpecialS,
    ftYs_MS_SpecialS_Turn,
    ftYs_MS_SpecialS_End,
    ftYs_MS_SpecialAirS_Start,
    ftYs_MS_SpecialAirS,
    ftYs_MS_SpecialAirS_Rebound,
    ftYs_MS_SpecialAirS_End,
    ftYs_MS_SpecialHi,
    ftYs_MS_SpecialAirHi,
    ftYs_MS_SpecialLw,
    ftYs_MS_SpecialLw_Land,
    ftYs_MS_SpecialAirLw,

    ftYs_MS_Unk_365,
    ftYs_MS_Unk_366,
    ftYs_MS_Unk_367,
    ftYs_MS_Unk_368,
} ftYoshi_MotionState;

#endif
