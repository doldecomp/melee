#include "itnessbat.h"

#include <placeholder.h>
#include <platform.h>

#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/item.h"

/// #it_802AD478

/// #it_802AD590

void it_802AD6B8(Item_GObj* gobj)
{
    if (gobj != NULL) {
        Item* ip = GET_ITEM(gobj);
        ip->xDD4_itemVar.nessbat.x0 = 0;
        ip->owner = NULL;
        Item_8026A8EC(gobj);
    }
}

/// #it_2725_Logic58_PickedUp

/// #itNessbat_UnkMotion0_Anim

void itNessbat_UnkMotion0_Phys(Item_GObj* gobj) {}

bool itNessbat_UnkMotion0_Coll(Item_GObj* gobj)
{
    return false;
}

/// #itNessbat_UnkMotion1_Anim

void itNessbat_UnkMotion1_Phys(Item_GObj* gobj) {}

bool itNessbat_UnkMotion1_Coll(Item_GObj* gobj)
{
    return false;
}

void itNessBat_Logic58_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
