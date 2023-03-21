#ifndef MELEE_FT_CHARA_FTCAPTAIN_FORWARD_H
#define MELEE_FT_CHARA_FTCAPTAIN_FORWARD_H

#include "ft/forward.h"
#include "ftCommon/forward.h"

typedef struct ftCaptainAttributes ftCaptainAttributes;
typedef union ftCaptain_StateVars ftCaptain_StateVars;

typedef enum ftCaptainAction {
    ftCaptain_AS_Swing42_Sword = ftCo_AS_Count,
    ftCaptain_AS_Swing42_2,
    ftCaptain_AS_Swing42_3,
    ftCaptain_AS_Swing42_4,
    ftCaptain_AS_Swing42_5,
    ftCaptain_AS_Swing42_6,
    ftCaptain_AS_SpecialN,
    ftCaptain_AS_SpecialAirN,
    ftCaptain_AS_SpecialS_Start,
    ftCaptain_AS_SpecialS,
    ftCaptain_AS_SpecialAirS_Start,
    ftCaptain_AS_SpecialAirS,
    ftCaptain_AS_SpecialHi,
    ftCaptain_AS_SpecialAirHi,
    ftCaptain_AS_SpecialHi_Catch,
    ftCaptain_AS_SpecialHi_Throw,
} ftCaptainAction;

#endif
