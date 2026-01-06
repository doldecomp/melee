#include "itbox.h"

#include <placeholder.h>
#include <platform.h>

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"

/// #it_80286088

/// #it_3F14_Logic1_Spawned

/// #it_3F14_Logic1_Destroyed

/// #it_80286248

/// #it_80286340

/// #it_802863BC

/// #fn_80286480

/// #itBox_UnkMotion0_Anim

void itBox_UnkMotion0_Phys(Item_GObj* gobj) {}

/// #itBox_UnkMotion0_Coll

/// #it_8028655C

bool itBox_UnkMotion4_Anim(Item_GObj* gobj)
{
    return false;
}

/// #itBox_UnkMotion1_Phys

bool itBox_UnkMotion1_Coll(Item_GObj* gobj)
{
    it_8026E15C(gobj, fn_80286480);
    return false;
}

void it_3F14_Logic1_PickedUp(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
}

bool itBox_UnkMotion2_Anim(Item_GObj* gobj)
{
    return false;
}

void itBox_UnkMotion2_Phys(Item_GObj* gobj) {}

void it_3F14_Logic1_Thrown(Item_GObj* gobj)
{
    it_8026B3A8(gobj);
    Item_80268E5C(gobj, 3, ITEM_ANIM_UPDATE | ITEM_DROP_UPDATE);
}

/// #itBox_UnkMotion4_Phys

/// #itBox_UnkMotion3_Coll

void it_3F14_Logic1_Dropped(Item_GObj* gobj)
{
    it_8026B3A8(gobj);
    Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE | ITEM_DROP_UPDATE);
}

/// #itBox_UnkMotion4_Coll

/// #it_80286AA4

bool itBox_UnkMotion6_Anim(Item_GObj* gobj)
{
    return it_802751D8(gobj);
}

void itBox_UnkMotion6_Phys(Item_GObj* gobj) {}

bool itBox_UnkMotion6_Coll(Item_GObj* gobj)
{
    return false;
}

/// #it_80286BA0

bool itBox_UnkMotion7_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.box.xDD8 -= 1;
    if (ip->xDD4_itemVar.box.xDD8 > 0) {
        return false;
    }
    return true;
}

void itBox_UnkMotion7_Phys(Item_GObj* gobj) {}

bool itBox_UnkMotion7_Coll(Item_GObj* gobj)
{
    return false;
}

/// #it_3F14_Logic1_DmgDealt

/// #it_3F14_Logic1_Clanked

/// #it_3F14_Logic1_HitShield

/// #it_3F14_Logic1_Reflected

/// #it_3F14_Logic1_DmgReceived

void it_3F14_Logic1_EnteredAir(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE);
}

bool itBox_UnkMotion5_Anim(Item_GObj* gobj)
{
    return false;
}

void itBox_UnkMotion5_Phys(Item_GObj* gobj) {}

bool itBox_UnkMotion5_Coll(Item_GObj* gobj)
{
    it_8026E8C4(gobj, fn_80286480, it_8028655C);
    return false;
}

void it_3F14_Logic1_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

/// #it_802870A4

bool itBox_UnkMotion8_Anim(Item_GObj* gobj)
{
    return false;
}

/// #itBox_UnkMotion8_Phys

bool itBox_UnkMotion8_Coll(Item_GObj* gobj)
{
    return false;
}

/// #it_8028733C
