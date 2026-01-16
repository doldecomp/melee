#include "itpikachuthunder.h"

#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/types.h"

#include <baselib/gobj.h>

int it_802B1DEC(Item_GObj* arg0)
{
    return GET_ITEM(arg0)->xDD4_itemVar.capsule.x4;
}

/// #it_802B1DF8

s32 it_802B1FC8(Item_GObj* gobj)
{
    return it_802B22B8(gobj);
}

/// #it_802B1FE8

/// #it_2725_Logic39_Destroyed

/// #it_802B2080

/// #itPikachuthunder_UnkMotion0_Anim

/// #it_802B211C

bool itPikachuthunder_UnkMotion1_Anim(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    ip->xD44_lifeTimer--;
    if (ip->xD44_lifeTimer <= 0.0f) {
        return true;
    }
    return false;
}

/// #itPikachuthunder_UnkMotion1_Coll

/// #it_802B22B8

/// #itPikachuthunder_UnkMotion2_Anim

bool it_2725_Logic39_DmgDealt(Item_GObj* arg0)
{
    return false;
}

bool it_2725_Logic39_HitShield(Item_GObj* arg0)
{
    return false;
}

bool it_2725_Logic39_Clanked(Item_GObj* arg0)
{
    return false;
}

bool it_2725_Logic39_Absorbed(Item_GObj* arg0)
{
    return false;
}

void it_2725_Logic39_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.pikachuthunder.x38 == ref_gobj) {
        ip->xDD4_itemVar.pikachuthunder.x38 = NULL;
    }
    it_8026B894(gobj, ref_gobj);
}
