#include "itnesspkflushexplode.h"

#include <placeholder.h>
#include <platform.h>

#include "it/forward.h"

#include "it/inlines.h"
#include "it/it_26B1.h"

/* 2AFD44 */ static bool itNesspkflushexplode_UnkMotion0_Coll(Item_GObj* gobj);

/// #it_802AF940

void it_2725_Logic103_Destroyed(Item_GObj* item_gobj)
{
    Item* item;

    if (item_gobj != NULL) {
        item = item_gobj->user_data;
        if (item != NULL) {
            it_802725D4(item_gobj);
            item->owner = NULL;
        }
    }
}

/// #it_802AFA70

/// #itNesspkflushexplode_UnkMotion0_Anim

void itNesspkflushexplode_UnkMotion0_Phys(Item_GObj* gobj)
{
    Item* it = GET_ITEM(gobj);
    it->x40_vel.z = it->x40_vel.y = it->x40_vel.z = 0;
}

bool itNesspkflushexplode_UnkMotion0_Coll(Item_GObj* gobj)
{
    return false;
}

bool it_2725_Logic103_Clanked(Item_GObj* arg0)
{
    return true;
}

bool it_2725_Logic103_Absorbed(Item_GObj* arg0)
{
    return true;
}

bool it_2725_Logic103_ShieldBounced(Item_GObj* arg0)
{
    return true;
}

bool it_2725_Logic103_HitShield(Item_GObj* arg0)
{
    return true;
}

void it_2725_Logic103_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
