#include "itkyasarinegg.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"

void itKyasarinegg_UnkMotion1_Coll(Item_GObj* gobj)
{
    it_8026DFB0(gobj);
}

void itKyasarinegg_UnkMotion1_Phys(Item_GObj* gobj)
{
    ItemAttr* attrs = GET_ITEM(gobj)->xCC_item_attr;

    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
    it_80274658(gobj, it_804D6D28->x68_float);
}

s32 itKyasarinegg_UnkMotion3_Coll(Item_GObj* gobj)
{
    if (it_8026DA08(gobj) != 0) {
        return it_2725_Logic28_DmgDealt(gobj);
    }
    return 0;
}

void itKyasarinegg_UnkMotion3_Phys(Item_GObj* gobj)
{
    ItemAttr* attrs = GET_ITEM(gobj)->xCC_item_attr;

    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
    it_80274658(gobj, it_804D6D28->x68_float);
}

void it_2725_Logic28_Dropped(Item_GObj* gobj)
{
    it_2725_Logic28_Thrown(gobj);
}

void itKyasarinegg_UnkMotion4_Anim(Item_GObj* gobj)
{
    it_802751D8(gobj);
}

bool itKyasarinegg_UnkMotion0_Coll(Item_GObj* gobj)
{
    if (it_8026DAA8(gobj) & 0xF) {
        it_802EFCC0(gobj);
    }
    return false;
}

void it_2725_Logic28_PickedUp(Item_GObj* gobj)
{
    Item_80268E5C((HSD_GObj*) gobj, 2, ITEM_ANIM_UPDATE);
}

void it_2725_Logic28_Thrown(Item_GObj* gobj)
{
    Item_80268E5C((HSD_GObj*) gobj, 3, 6);
}

void it_802F0320(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

bool it_2725_Logic28_ShieldBounced(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->msid == 3) {
        itColl_BounceOffShield(gobj);
    }
    return false;
}
