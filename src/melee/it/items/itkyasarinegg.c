#include "itkyasarinegg.h"

#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"

void itKyasarinegg_UnkMotion1_Coll(Item_GObj* gobj)
{
    it_8026DFB0(gobj);
}

void it_2725_Logic28_Dropped(Item_GObj* gobj)
{
    it_2725_Logic28_Thrown(gobj);
}

void itKyasarinegg_UnkMotion4_Anim(Item_GObj* gobj)
{
    it_802751D8(gobj);
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
