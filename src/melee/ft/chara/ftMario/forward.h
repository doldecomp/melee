#ifndef MELEE_FT_CHARA_FTMARIO_FORWARD_H
#define MELEE_FT_CHARA_FTMARIO_FORWARD_H

#include "ft/forward.h"
#include "ftCommon/forward.h"

#include "ftMario/types.h"

typedef enum ftMario_MotionState {
    ftMario_MS_Unk_341 = ftCo_MS_Count,
    ftMario_MS_Unk_342,
    ftMario_MS_SpecialN,
    ftMario_MS_SpecialAirN,
    ftMario_MS_SpecialS,
    ftMario_MS_SpecialAirS,
    ftMario_MS_SpecialHi,
    ftMario_MS_SpecialAirHi,
    ftMario_MS_SpecialLw,
    ftMario_MS_SpecialAirLw,
    ftMario_MS_Count,
} ftMario_MotionState;

#endif
