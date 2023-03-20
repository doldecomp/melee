#ifndef MELEE_FT_CHARA_FTMARIO_FORWARD_H
#define MELEE_FT_CHARA_FTMARIO_FORWARD_H

#include "ft/forward.h"
#include "ftMario/types.h"

typedef struct ftMario_SpecialS_DatAttrs ftMario_SpecialS_DatAttrs;

typedef enum ftMarioAction {
    ftMario_AS_Unk_341 = ASID_MAX,
    ftMario_AS_Unk_342,
    ftMario_AS_SpecialN,
    ftMario_AS_SpecialAirN,
    ftMario_AS_SpecialS,
    ftMario_AS_SpecialAirS,
    ftMario_AS_SpecialHi,
    ftMario_AS_SpecialAirHi,
    ftMario_AS_SpecialLw,
    ftMario_AS_SpecialAirLw,
    ftMario_AS_Count,
} ftMarioAction;

#endif
