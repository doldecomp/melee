#include "itflipper.h"

#include <placeholder.h>
#include <platform.h>

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"

/// #it_80290938

/// #it_3F14_Logic20_Spawned

/// #it_80290A7C

/// #it_80290C38

/// #it_80290CE8

/// #it_80290DD4

void it_80290E78(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itResetVelocity(ip);
    it_8026B390(gobj);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
}

bool itFlipper_UnkMotion0_Anim(Item_GObj* gobj)
{
    return false;
}

void itFlipper_UnkMotion0_Phys(Item_GObj* gobj) {}

bool itFlipper_UnkMotion0_Coll(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_80290F00);
    return false;
}

void it_80290F00(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
}

bool itFlipper_UnkMotion1_Anim(Item_GObj* gobj)
{
    return false;
}

void itFlipper_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itFlipper_UnkMotion1_Coll(Item_GObj* gobj)
{
    it_8026E15C(gobj, it_80290E78);
    return false;
}

void it_3F14_Logic20_PickedUp(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
}

bool itFlipper_UnkMotion2_Anim(Item_GObj* gobj)
{
    return false;
}

void itFlipper_UnkMotion2_Phys(Item_GObj* gobj) {}

/// #it_3F14_Logic20_Dropped

/// #it_3F14_Logic20_Thrown

void it_3F14_Logic20_Dropped(Item_GObj* gobj)
{
    it_3F14_Logic20_Thrown(gobj);
}

/// #itFlipper_UnkMotion3_Anim

/// #itFlipper_UnkMotion3_Phys

/// #itFlipper_UnkMotion3_Coll

/// #it_80291254

void it_8029131C(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 5, 0x12);
}

/// #it_80291344

/// #itFlipper_UnkMotion5_Anim

/// #itFlipper_UnkMotion6_Anim

/// #itFlipper_UnkMotion6_Phys

bool itFlipper_UnkMotion6_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.flipper.xDE8 == 0) {
        it_8026E0F4(gobj);
    }
    return false;
}

/// #it_3F14_Logic20_DmgDealt

/// #it_3F14_Logic20_Clanked

/// #it_3F14_Logic20_HitShield

bool it_3F14_Logic20_Reflected(Item_GObj* gobj)
{
    return it_80273030(gobj);
}

bool it_3F14_Logic20_ShieldBounced(Item_GObj* gobj)
{
    return itColl_BounceOffShield(gobj);
}

/// #it_3F14_Logic20_DmgReceived

void it_3F14_Logic20_EnteredAir(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE);
}

bool itFlipper_UnkMotion4_Anim(Item_GObj* gobj)
{
    return false;
}

void itFlipper_UnkMotion4_Phys(Item_GObj* gobj) {}

bool itFlipper_UnkMotion4_Coll(Item_GObj* gobj)
{
    it_8026E8C4(gobj, it_80290E78, it_80290F00);
    return false;
}

void it_3F14_Logic20_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
