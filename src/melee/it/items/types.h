#ifndef MELEE_IT_ITEMS_TYPES_H
#define MELEE_IT_ITEMS_TYPES_H

#include <placeholder.h>
#include <platform.h>

#include "it/items/forward.h" // IWYU pragma: export
#include <baselib/forward.h>

/// @@todo Size unknown.
struct ItemStateTable {
    /// @at{0} @sz{4}
    enum_t anim_id;

    /// @at{4} @sz{4}
    HSD_GObjPredicate animated;

    /// @at{8} @sz{4}
    HSD_GObjEvent physics_updated;

    /// @at{C} @sz{4}
    HSD_GObjPredicate collided;
};

struct ItemLogicTable {
    /// @at{0} @sz{4}
    ItemStateTable* states;

    /// @at{4} @sz{4}
    HSD_GObjEvent spawned;

    /// @at{8} @sz{4}
    HSD_GObjEvent destroyed;

    /// @at{C} @sz{4}
    HSD_GObjEvent picked_up;

    /// @at{10} @sz{4}
    HSD_GObjEvent dropped;

    /// @at{14} @sz{4}
    HSD_GObjEvent thrown;

    /// @at{18} @sz{4}
    HSD_GObjPredicate dmg_dealt;

    /// @at{1C} @sz{4}
    HSD_GObjPredicate dmg_received;

    /// @at{20} @sz{4}
    HSD_GObjEvent entered_air;

    /// @at{24} @sz{4}
    HSD_GObjPredicate reflected;

    /// @at{28} @sz{4}
    HSD_GObjPredicate clanked;

    /// @at{2C} @sz{4}
    HSD_GObjPredicate absorbed;

    /// @at{30} @sz{4}
    HSD_GObjPredicate shield_bounced;

    /// @at{34} @sz{4}
    HSD_GObjPredicate hit_shield;

    /// @at{38} @sz{4}
    HSD_GObjInteraction evt_unk;
};

struct itSword_UnkBytes {
    /*   +0 */ u8 x0;
    /*   +1 */ u8 x1;
    /*   +2 */ u8 x2;
    /*   +3 */ u8 x3;
    /*   +4 */ u8 x4;
    /*   +5 */ u8 x5;
    /*   +6 */ u8 x6;
    /*   +7 */ u8 x7;
    /*   +8 */ u8 x8;
    /*   +9 */ u8 x9;
    /*   +A */ u8 xA;
    /*   +B */ u8 xB;
    /*   +C */ u8 xC;
    /*   +D */ u8 xD;
    /*   +E */ u8 xE;
    /*   +F */ u8 xF;
    /*  +10 */ u8 x10;
};

struct itSword_UnkArticle1 {
    /*  +0 */ UNK_T x0;
    /*  +4 */ UNK_T x4;
    /*  +8 */ UNK_T x8;
    /*  +C */ float xC;
    /* +10 */ float x10;
    /* +14 */ float x14;
    /* +18 */ int x18;
    /* +1C */ itSword_UnkBytes x1C;
};

#endif
