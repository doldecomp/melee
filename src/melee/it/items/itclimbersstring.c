#include "itclimbersstring.h"

#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/item.h"

static void it_802C33B8(Item* item);

void fn_802C28B8(Item_GObj* gobj)
{
    it_802C33B8(GET_ITEM(gobj));
}

void it_2725_Logic70_EvtUnk(Item_GObj* arg0, Item_GObj* arg1)
{
    Item* ip = GET_ITEM((HSD_GObj*) arg0);
    it_8026B894(arg0, (HSD_GObj*) arg1);
    if ((HSD_GObj*) ip->xDD4_itemVar.bombhei.xDE0 == arg1) {
        ip->xDD4_itemVar.bombhei.xDE0 = 0;
    }
}

void it_2725_Logic70_PickedUp(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    it_8026BB44(gobj);
    ip->on_accessory = fn_802C28B8;
}
