#include "itgamewatchparachute.h"

#include "ftGameWatch/ftGw_AttackAir.h"

#include "it/forward.h"

#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/item.h"

void it_802C6D6C(Item_GObj* item_gobj)
{
    int pad[1];
    Item* item = GET_ITEM(item_gobj);

    if (item != NULL) {
        if (item->owner != NULL) {
            ftGw_AttackAirN_ItemParachuteSetFlag(item->owner);
        }
        Item_8026A8EC(item_gobj);
    }
}

void it_2725_Logic74_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

void it_802C6DB8(Item_GObj* gobj)
{
    it_8026B724(gobj);
}

void it_802C6DD8(Item_GObj* gobj)
{
    it_8026B73C(gobj);
}

void it_2725_Logic74_Destroyed(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->owner != NULL) {
        ftGw_AttackAirN_ItemParachuteSetFlag(ip->owner);
    }
}

void it_2725_Logic74_PickedUp(Item_GObj* item_gobj)
{
    Item* temp_r3;

    temp_r3 = item_gobj->user_data;
    temp_r3->xDAC_itcmd_var0 = 0;
    if ((HSD_GObj*) temp_r3->owner != NULL) {
        Item_80268E5C(item_gobj, 0, ITEM_ANIM_UPDATE);
        Item_802694CC(item_gobj);
    }
}
