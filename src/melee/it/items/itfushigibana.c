#include "itfushigibana.h"

#include <placeholder.h>
#include <platform.h>

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_2725.h"

/// #it_2725_Logic29_Spawned

/// #it_802D705C

/// #it_802D70A4

bool itFushigibana_UnkMotion0_Anim(Item_GObj* gobj)
{
    it_80279FF8(gobj);
    return false;
}

void itFushigibana_UnkMotion0_Phys(Item_GObj* gobj)
{
    it_8027A09C(gobj);
}

bool itFushigibana_UnkMotion0_Coll(Item_GObj* gobj)
{
    return it_8027A118(gobj, (void (*)(HSD_GObj*)) it_802D705C);
}

/// #it_802D718C

/// #itFushigibana_UnkMotion1_Anim

void itFushigibana_UnkMotion1_Phys(Item_GObj* gobj) {}

/// #itFushigibana_UnkMotion1_Coll

/// #it_802D7328

bool itFushigibana_UnkMotion2_Anim(Item_GObj* gobj)
{
    return false;
}

void itFushigibana_UnkMotion2_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itFushigibana_UnkMotion2_Coll(Item_GObj* gobj)
{
    it_8026E15C(gobj, it_802D705C);
    return false;
}
