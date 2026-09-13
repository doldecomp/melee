#ifndef MELEE_IT_ITEMS_TYPES_H
#define MELEE_IT_ITEMS_TYPES_H

#include <Runtime/platform.h>

#include <melee/it/kinds/forward.h> // IWYU pragma: export
#include <sysdolphin/baselib/forward.h>

#include <placeholder.h>

/// @todo Size unknown.
struct ItemStateTable {
    enum_t anim_id;

    HSD_GObjPredicate animated;

    HSD_GObjEvent physics_updated;

    HSD_GObjPredicate collided;
};

struct ItemLogicTable {
    ItemStateTable* states;

    HSD_GObjEvent spawned;

    HSD_GObjEvent destroyed;

    HSD_GObjEvent picked_up;

    HSD_GObjEvent dropped;

    HSD_GObjEvent thrown;

    HSD_GObjPredicate dmg_dealt;

    HSD_GObjPredicate dmg_received;

    HSD_GObjEvent entered_air;

    HSD_GObjPredicate reflected;

    HSD_GObjPredicate clanked;

    HSD_GObjPredicate absorbed;

    HSD_GObjPredicate shield_bounced;

    HSD_GObjPredicate hit_shield;

    HSD_GObjInteraction evt_unk;
};

struct itSword_UnkBytes {
    /*   +0 */ f32 x0;
    /*   +4 */ f32 x4;
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
