#include "itmaril.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"

/// #it_802D66F8

/// #it_802D6740

/// #it_802D6798

bool it_802D6808(Item_GObj* arg0)
{
    return false;
}

bool it_802D6810(Item_GObj* gobj)
{
    return it_80273030(gobj);
}

bool it_802D6830(Item_GObj* arg0)
{
    return true;
}

bool it_802D6838(Item_GObj* arg0)
{
    return false;
}

bool it_802D6840(Item_GObj* arg0)
{
    return true;
}

bool it_802D6848(Item_GObj* arg0)
{
    return true;
}

void it_802D6850(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

/// #it_2725_Logic28_Spawned

/// #it_802D68FC

bool itMaril_UnkMotion0_Anim(Item_GObj* gobj)
{
    it_80279FF8(gobj);
    return false;
}

void itMaril_UnkMotion0_Phys(Item_GObj* gobj)
{
    it_8027A09C(gobj);
}

bool itMaril_UnkMotion0_Coll(Item_GObj* gobj)
{
    return it_8027A118(gobj, (void (*)(HSD_GObj*)) it_802D69E4);
}

/// #it_802D69E4

/// #it_802D6A54

/// #itMaril_UnkMotion1_Anim

void itMaril_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_8027A344(gobj);
    ip->x40_vel.x = ip->xDD4_itemVar.chicorita.x64;
}

/// #itMaril_UnkMotion1_Coll

void it_802D6DDC(HSD_GObj* gobj)
{
    Item_80268E5C(gobj, 2, ITEM_UNK_0x1);
}

/// #itMaril_UnkMotion2_Anim

void itMaril_UnkMotion2_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itMaril_UnkMotion2_Coll(Item_GObj* gobj)
{
    it_8026E15C(gobj, it_802D69E4);
    return false;
}

/// #itMaril_UnkMotion3_Anim

void itMaril_UnkMotion3_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

/// #it_802D6F00

void it_802D6FB0(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
