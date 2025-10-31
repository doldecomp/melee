#include "ittosakinto.h"

#include "it/it_26B1.h"
#include "it/it_266F.h"
#include "it/it_2725.h"
#include "it/inlines.h"

void it_802C8FC4(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

bool itTosakinto_UnkMotion4_Anim(Item_GObj* gobj)
{
    it_80279FF8(gobj);
    return false;
}

bool itTosakinto_UnkMotion3_Coll(Item_GObj* gobj)
{
    it_8026E15C(gobj, it_802C90E8);
    return false;
}

void itTosakinto_UnkMotion4_Phys(Item_GObj* gobj)
{
    it_8027A09C(gobj);
}

void itTosakinto_UnkMotion4_Coll(Item_GObj* gobj)
{
    it_8027A118(gobj, it_802C8FE4);
}

void itTosakinto_UnkMotion3_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}
