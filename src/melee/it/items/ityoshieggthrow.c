#include "ityoshieggthrow.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/item.h"

void it_802B2890(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM((HSD_GObj*) item_gobj);
    item->owner = NULL;
    item->xDC8_word.flags.x13 = false;
    Item_8026A8EC(item_gobj);
}

bool itYoshieggthrow_UnkMotion1_Coll(Item_GObj* gobj)
{
    it_8026E5A0(gobj, it_802B2C38);
    return 0;
}

void it_802B2FA8(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
