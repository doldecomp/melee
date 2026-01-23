#include "itclinkmilk.h"

#include <placeholder.h>
#include <platform.h>

#include "ft/chara/ftCLink/ftCl_Init.h"
#include "ft/ftlib.h"
#include "it/item.h"
#include "it/it_26B1.h"
#include "it/types.h"

#include <baselib/gobj.h>
#include <baselib/jobj.h>

/// #it_802C8B28

/// FAKE MATCH: Type punning (*(s32*)&) used to force integer store.
/// Original code likely assigned 0 directly or used proper union access.
void it_802C8C34(Item_GObj* gobj)
{
    Item* ip;

    if (gobj != NULL) {
        ip = gobj->user_data;
        if (ip != NULL) {
            *(s32*) &ip->xDD4_itemVar = 0;
            ip->owner = NULL;
            Item_8026A8EC(gobj);
        }
    }
}

/// FAKE MATCH: Local 'zero' variable and Yoda condition (zero == x) used
/// to manipulate register allocation. Original was likely: if (ip->facing_dir == 0.0F)
void it_2725_Logic80_PickedUp(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    f32 zero = 0.0F;

    if (zero == ip->facing_dir) {
        Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    } else {
        Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    }
    Item_802694CC(gobj);
}

/// #itClinkmilk_UnkMotion1_Anim

void itClinkmilk_UnkMotion1_Phys(Item_GObj* gobj) {}

bool itClinkmilk_UnkMotion1_Coll(Item_GObj* gobj)
{
    return false;
}

void it_2725_Logic80_EvtUnk(Item_GObj* gobj, HSD_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
