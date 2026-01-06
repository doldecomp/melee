#include "itevyoshiegg.h"

#include <placeholder.h>
#include <platform.h>

#include "gm/gm_1BA8.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"

/// #it_8029B0C8

void it_3F14_Logic42_Destroyed(Item_GObj* gobj)
{
    gm_801BEB68(1);
}

void it_3F14_Logic42_Spawned(Item_GObj* gobj)
{
    Item* it = GET_ITEM((HSD_GObj*) gobj);
    // This should be EvYoshiEgg
    it->xDD4_itemVar.bombhei.xDD4 = 0;
    it_8029B268(gobj);
}

/// #it_8029B1D8

bool itEvyoshiegg_UnkMotion0_Anim(Item_GObj* gobj)
{
    return false;
}

void itEvyoshiegg_UnkMotion0_Phys(Item_GObj* gobj) {}

bool itEvyoshiegg_UnkMotion0_Coll(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_8029B268);
    return false;
}

void it_8029B268(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
}

bool itEvyoshiegg_UnkMotion3_Anim(Item_GObj* gobj)
{
    return false;
}

void itEvyoshiegg_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itEvyoshiegg_UnkMotion1_Coll(Item_GObj* gobj)
{
    it_8026E32C(gobj, it_8029B1D8);
    return false;
}

void it_3F14_Logic42_PickedUp(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
}

bool itEvyoshiegg_UnkMotion2_Anim(Item_GObj* gobj)
{
    return false;
}

void itEvyoshiegg_UnkMotion2_Phys(Item_GObj* gobj) {}

void it_3F14_Logic42_Dropped(Item_GObj* gobj)
{
    it_3F14_Logic42_Thrown(gobj);
}

void it_3F14_Logic42_Thrown(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 3, 6);
}

void itEvyoshiegg_UnkMotion3_Phys(Item_GObj* gobj)
{
    ItemAttr* attrs = GET_ITEM(gobj)->xCC_item_attr;

    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
    it_80274658(gobj, it_804D6D28->x68_float);
}

/// #itEvyoshiegg_UnkMotion3_Coll

/// #itEvyoshiegg_UnkMotion5_Anim

void itEvyoshiegg_UnkMotion5_Phys(Item_GObj* gobj) {}

bool itEvyoshiegg_UnkMotion5_Coll(Item_GObj* gobj)
{
    return false;
}

/// #it_3F14_Logic42_DmgDealt

/// #it_3F14_Logic42_Clanked

/// #it_3F14_Logic42_HitShield

/// #it_3F14_Logic42_Reflected

/// #it_3F14_Logic42_DmgReceived

void it_3F14_Logic42_EnteredAir(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE);
}

bool itEvyoshiegg_UnkMotion4_Anim(Item_GObj* gobj)
{
    return false;
}

void itEvyoshiegg_UnkMotion4_Phys(Item_GObj* gobj) {}

bool itEvyoshiegg_UnkMotion4_Coll(Item_GObj* gobj)
{
    it_8026E8C4(gobj, it_8029B1D8, it_8029B268);
    return false;
}

void it_3F14_Logic42_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
