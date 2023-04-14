#ifndef MELEE_FT_CHARA_FTMARIO_FORWARD_H
#define MELEE_FT_CHARA_FTMARIO_FORWARD_H

#include "ft/forward.h"
#include "ftCommon/forward.h"

typedef enum ftMario_MotionState {
    ftMr_MS_Unk_341 = ftCo_MS_Count,
    ftMr_MS_Unk_342,
    ftMr_MS_SpecialN,
    ftMr_MS_SpecialAirN,
    ftMr_MS_SpecialS,
    ftMr_MS_SpecialAirS,
    ftMr_MS_SpecialHi,
    ftMr_MS_SpecialAirHi,
    ftMr_MS_SpecialLw,
    ftMr_MS_SpecialAirLw,
    ftMario_MS_Count,
} ftMario_MotionState;

#endif
