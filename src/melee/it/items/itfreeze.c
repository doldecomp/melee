#include "itfreeze.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "it/items/itwhitebea.h"

/// #it_8028EB88

/// #it_8028EC98

void it_8028ECE0(Item_GObj* gobj)
{
    GET_ITEM(gobj)->xDD4_itemVar.freeze.unk_1C = NULL;
}

Item* it_8028ECF0(Item_GObj* gobj, Vec3* v)
{
    Item* ip = GET_ITEM(gobj);
    v->x = ip->pos.x;
    v->y = ip->pos.y;
    v->z = ip->pos.z;
    return ip;
}

/// #it_3F14_Logic17_Destroyed

/// #it_3F14_Logic17_Spawned

/// #it_8028EDBC

/// #it_8028EF34

bool itFreeze_UnkMotion0_Anim(Item_GObj* gobj)
{
    return false;
}

void itFreeze_UnkMotion0_Phys(Item_GObj* gobj)
{
    it_8028EDBC(gobj);
}

/// #itFreeze_UnkMotion0_Coll

void it_8028F1D8(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
}

bool itFreeze_UnkMotion3_Anim(Item_GObj* gobj)
{
    return false;
}

void itFreeze_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

/// #itFreeze_UnkMotion1_Coll

void it_3F14_Logic17_PickedUp(Item_GObj* gobj)
{
    Item* item = gobj->user_data;
    Item_GObj* linked;

    if ((linked = (Item_GObj*) item->xDD4_itemVar.freeze.unk_1C) != NULL) {
        it_802E37A4(linked);
        item->xDD4_itemVar.freeze.unk_1C = NULL;
    }

    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
}

bool itFreeze_UnkMotion2_Anim(Item_GObj* gobj)
{
    return false;
}

void it_3F14_Logic17_Dropped(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 1, 6);
}

void it_3F14_Logic17_Thrown(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 3, 6);
}

void itFreeze_UnkMotion3_Phys(Item_GObj* gobj)
{
    Item* ip;
    ItemAttr* it_attr;

    ip = gobj->user_data;
    it_attr = ip->xCC_item_attr;
    it_80272860(gobj, it_attr->x10_fall_speed, it_attr->x14_fall_speed_max);
}

bool itFreeze_UnkMotion3_Coll(Item_GObj* gobj)
{
    if (it_8026DAA8(gobj) != 0) {
        return 1;
    }
    return 0;
}

bool it_3F14_Logic17_DmgDealt(Item_GObj* arg0)
{
    return true;
}

bool it_3F14_Logic17_Clanked(Item_GObj* arg0)
{
    return true;
}

bool it_3F14_Logic17_HitShield(Item_GObj* arg0)
{
    return true;
}

bool it_3F14_Logic17_Absorbed(Item_GObj* arg0)
{
    return true;
}

bool it_3F14_Logic17_Reflected(Item_GObj* gobj)
{
    return it_80273030(gobj);
}

bool it_3F14_Logic17_ShieldBounced(Item_GObj* gobj)
{
    return itColl_BounceOffShield(gobj);
}

bool it_3F14_Logic17_DmgReceived(Item_GObj* arg0)
{
    return true;
}

/// #it_8028F434

bool itFreeze_UnkMotion4_Anim(Item_GObj* gobj)
{
    return false;
}

/// #itFreeze_UnkMotion4_Phys

/// #itFreeze_UnkMotion4_Coll

/// #it_8028F7C8

bool itFreeze_UnkMotion5_Anim(Item_GObj* gobj)
{
    return false;
}

void itFreeze_UnkMotion5_Phys(Item_GObj* gobj) {}

/// #itFreeze_UnkMotion5_Coll

void it_3F14_Logic17_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

/// #it_8028F8E4

/// #it_8028F968

void it_8028F9B8(Item_GObj* gobj)
{
    Item_8026A8EC(gobj);
}
