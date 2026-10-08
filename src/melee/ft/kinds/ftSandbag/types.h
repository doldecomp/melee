#ifndef MELEE_FT_CHARA_FTSANDBAG_TYPES_H
#define MELEE_FT_CHARA_FTSANDBAG_TYPES_H

#include <melee/ft/forward.h>
#include <melee/ft/kinds/ftSandbag/forward.h> // IWYU pragma: export

struct _ftSandbagAttributes {
    u32 x0_pair[2];
};

struct ftSandbag_FighterVars {
    char filler0[FIGHTERVARS_SIZE];
};

#endif
