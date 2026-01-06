#include "itmariocape.h"

#include "ft/chara/ftMario/ftMr_SpecialS.h"
#include "it/inlines.h"
#include "it/it_26B1.h"

void it_802B26C0(Item_GObj* gobj)
{
    it_8026B724(gobj);
}

void it_802B26E0(Item_GObj* gobj)
{
    it_8026B73C(gobj);
}

void it_802B2870(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

void it_2725_Logic41_Destroyed(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->owner != NULL) {
        ftMr_SpecialS_Reset(ip->owner);
    }
}
