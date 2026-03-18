#include "itclimbersstring.h"

#include "ft/chara/ftPopo/ftPp_SpecialS.h"
#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/itCharItems.h"
#include "it/item.h"

#include <dolphin/os/OSError.h>
#include <baselib/gobjplink.h>

/* 2C33B8 */ static void it_802C33B8(Item* item);
/* 2C29E8 */ static void fn_802C29E8(Item_GObj* gobj);

void it_802C2750(Item_GObj* gobj)
{
    int unused[2];
    Item* ip = GET_ITEM(gobj);
    if (ip != NULL) {
        if (gobj != NULL) {
            if (ip->owner != NULL) {
                ftPp_SpecialS_8012114C(ip->owner);
            }
            ip->owner = NULL;
            ip->xDD4_itemVar.it_266F.xC = NULL;
            {
                ItemLink* cur;
                for (cur = (ItemLink*) ip->xDD4_itemVar.it_266F.x4;
                     cur != NULL;)
                {
                    HSD_GObj* cur_gobj = cur->gobj;
                    cur = cur->next;
                    HSD_GObjPLink_80390228(cur_gobj);
                }
            }
        }
        Item_8026A8EC(gobj);
    }
}

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

void it_802C3810(Item_GObj* gobj)
{
    Item* item;
    int unused[2];

    item = gobj->user_data;
    Item_80268E5C(gobj, 2, 2);
    it_8026BB20(gobj);
    item->on_accessory = fn_802C29E8;
}

void it_2725_Logic70_PickedUp(Item_GObj* gobj)
{
    short pad;
    void (*new_var)(Item_GObj* gobj);
    Item* ip = gobj->user_data;
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    it_8026BB44(gobj);
    new_var = &fn_802C28B8;
    ip->on_accessory = *new_var;
}
