#include "itwstar.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "ef/eflib.h"

/// #it_80294364

/// #it_80294430

/// #it_802944AC

/// #it_3F14_Logic29_Spawned

void it_8029455C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->x40_vel.z = 0.0f;
    ip->x40_vel.y = 0.0f;
    ip->x40_vel.x = 0.0f;
    it_8026B390(gobj);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
}

bool itWstar_UnkMotion0_Anim(Item_GObj* gobj)
{
    return false;
}

/// #itWstar_UnkMotion0_Phys

bool itWstar_UnkMotion0_Coll(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_80294624);
    return false;
}

void it_80294624(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
}

bool itWstar_UnkMotion1_Anim(Item_GObj* gobj)
{
    return false;
}

void itWstar_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itWstar_UnkMotion1_Coll(Item_GObj* gobj)
{
    it_8026E15C(gobj, it_8029455C);
    return false;
}

/// #it_802946B0

/// #it_3F14_Logic29_PickedUp

bool itWstar_UnkMotion3_Anim(Item_GObj* gobj)
{
    return false;
}

void it_3F14_Logic29_Dropped(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 1, 6);
    efLib_DestroyAll(gobj);
}

/// #it_802947CC

/// #itWstar_UnkMotion5_Anim

void itWstar_UnkMotion5_Phys(Item_GObj* gobj) {}

bool itWstar_UnkMotion5_Coll(Item_GObj* gobj)
{
    return false;
}

void it_3F14_Logic29_EnteredAir(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE);
}

bool itWstar_UnkMotion4_Anim(Item_GObj* gobj)
{
    return false;
}

void itWstar_UnkMotion4_Phys(Item_GObj* gobj) {}

bool itWstar_UnkMotion4_Coll(Item_GObj* gobj)
{
    it_8026E8C4(gobj, it_8029455C, it_80294624);
    return false;
}

void it_3F14_Logic30_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
