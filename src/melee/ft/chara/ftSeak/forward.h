#ifndef MELEE_FT_CHARA_FTSEAK_FORWARD_H
#define MELEE_FT_CHARA_FTSEAK_FORWARD_H

#include <platform.h>
#include "ftCommon/forward.h"

typedef enum ftSeak_MotionState {
    ftSk_MS_SpecialN_ChargeStart = ftCo_MS_Count,
    ftSk_MS_SpecialN_ChargeLoop,
    ftSk_MS_SpecialN_ChargeEnd,
    ftSk_MS_SpecialN_Shoot,
    ftSk_MS_SpecialAirN_ChargeStart,
    ftSk_MS_SpecialAirN_ChargeLoop,
    ftSk_MS_SpecialAirN_ChargeEnd,
    ftSk_MS_SpecialAirN_Shoot,
    ftSk_MS_SpecialS_Start,
    ftSk_MS_SpecialS_Loop,
    ftSk_MS_SpecialS_End,
    ftSk_MS_SpecialAirS_Start,
    ftSk_MS_SpecialAirS_Loop,
    ftSk_MS_SpecialAirS_End,
    ftSk_MS_SpecialHi_Start,
    ftSk_MS_SpecialHi,
    ftSk_MS_SpecialHi_End,
    ftSk_MS_SpecialAirHi_Start,
    ftSk_MS_SpecialAirHi,
    ftSk_MS_SpecialAirHi_End,
    ftSk_MS_SpecialLw,
    ftSk_MS_SpecialLw_End,
    ftSk_MS_SpecialAirLw,
    ftSk_MS_SpecialAirLw_End,
} ftSeak_MotionState;

#endif
