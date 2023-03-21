#ifndef MELEE_FT_CHARA_FTCAPTAIN_FORWARD_H
#define MELEE_FT_CHARA_FTCAPTAIN_FORWARD_H

#include "ft/forward.h"
#include "ftCommon/forward.h"

typedef struct ftCaptainAttributes ftCaptainAttributes;
typedef union ftCaptain_MotionVars ftCaptain_MotionVars;

typedef enum ftCaptainAction {
    ftCaptain_MS_Swing42_Sword = ftCo_MS_Count,
    ftCaptain_MS_Swing42_2,
    ftCaptain_MS_Swing42_3,
    ftCaptain_MS_Swing42_4,
    ftCaptain_MS_Swing42_5,
    ftCaptain_MS_Swing42_6,
    ftCaptain_MS_SpecialN,
    ftCaptain_MS_SpecialAirN,
    ftCaptain_MS_SpecialS_Start,
    ftCaptain_MS_SpecialS,
    ftCaptain_MS_SpecialAirS_Start,
    ftCaptain_MS_SpecialAirS,
    ftCaptain_MS_SpecialHi,
    ftCaptain_MS_SpecialAirHi,
    ftCaptain_MS_SpecialHi_Catch,
    ftCaptain_MS_SpecialHi_Throw,
} ftCaptainAction;

#endif
