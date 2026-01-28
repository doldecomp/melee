#include "itclimbersstring.h"

#include "it/inlines.h"

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
