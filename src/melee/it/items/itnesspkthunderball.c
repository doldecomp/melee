#include "itnesspkthunderball.h"

#include "it/inlines.h"
#include "it/it_26B1.h"

/// #it_802AB3F0

/// #it_802AB468

/// #it_802AB4B8

HSD_GObj* it_802AB568(Item_GObj* gobj)
{
    Item* ip;

    if (gobj != NULL) {
        ip = GET_ITEM(gobj);
        if (ip != NULL) {
            return ip->owner;
        }
    }
    return NULL;
}

/// #it_802AB58C

/// #it_802AB90C

/// #it_802AB9C0

/// #it_802ABA4C

/// #itNesspkthunderball_UnkMotion0_Anim

/// #itNesspkthunderball_UnkMotion0_Phys

/// #itNesspkthunderball_UnkMotion0_Coll

bool it_2725_Logic26_DmgDealt(Item_GObj* gobj)
{
    it_802AB90C(gobj);
    return true;
}

bool it_802AC074(Item_GObj* gobj)
{
    it_802AB90C(gobj);
    return true;
}

/// #it_802AC098

bool it_802AC338(Item_GObj* gobj)
{
    it_802AB90C(gobj);
    return true;
}

/// #it_802AC35C

bool it_802AC3F8(Item_GObj* gobj)
{
    it_802AB90C(gobj);
    return true;
}

void it_802AC41C(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
