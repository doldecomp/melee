#ifndef MELEE_FT_CHARA_FTCAPTAIN_FORWARD_H
#define MELEE_FT_CHARA_FTCAPTAIN_FORWARD_H

#include "ft/forward.h"
#include "ftCommon/forward.h"

typedef struct ftCaptain_DatAttrs ftCaptain_DatAttrs;
typedef union ftCaptain_MotionVars ftCaptain_MotionVars;

typedef enum ftCaptain_MotionState {
    ftCa_MS_Swing42_Sword = ftCo_MS_Count,
    ftCa_MS_Swing42_2,
    ftCa_MS_Swing42_3,
    ftCa_MS_Swing42_4,
    ftCa_MS_Swing42_5,
    ftCa_MS_Swing42_6,
    ftCa_MS_SpecialN,
    ftCa_MS_SpecialAirN,
    ftCa_MS_SpecialS_Start,
    ftCa_MS_SpecialS,
    ftCa_MS_SpecialAirS_Start,
    ftCa_MS_SpecialAirS,
    ftCa_MS_SpecialHi,
    ftCa_MS_SpecialAirHi,
    ftCa_MS_SpecialHi_Catch,
    ftCa_MS_SpecialHi_Throw,
    ftCa_MS_SpecialLw,
    ftCa_MS_SpecialLw_GroundEnd,
    ftCa_MS_SpecialAirLw,
    ftCa_MS_SpecialAirLw_GroundEnd,
    ftCa_MS_SpecialAirLw_AirEnd,
    ftCa_MS_SpecialLw_AirEnd,
    ftCa_MS_SpecialLw_Rebound,
} ftCaptain_MotionState;

#endif
