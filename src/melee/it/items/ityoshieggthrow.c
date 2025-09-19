#include "ityoshieggthrow.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"

void it_802B2890(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->owner = NULL;
    ip->xDC8_word.flags.x13 = false;
    Item_8026A8EC(gobj);
}

void it_2725_Logic43_PickedUp(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
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

bool itYoshieggthrow_UnkMotion2_Anim(Item_GObj* gobj)
{
    return it_802751D8(gobj);
}

bool it_802B2E5C(Item_GObj* gobj)
{
    return it_80273030(gobj);
}

bool it_802B2F88(Item_GObj* gobj)
{
    return itColl_BounceOffShield(gobj);
}
