#ifndef MELEE_IT_ITEMS_TYPES_H
#define MELEE_IT_ITEMS_TYPES_H

#include <Runtime/platform.h>

#include <melee/it/kinds/forward.h> // IWYU pragma: export
#include <sysdolphin/baselib/forward.h>

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

#endif
