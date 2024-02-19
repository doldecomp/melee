#include "itkirbyhammer.h"

#include "ef/efasync.h"
#include "ft/chara/ftKirby/ftKb_Init.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/item.h"

ItemStateTable it_803F6C98[] = { {
    0,
    NULL,
    NULL,
    NULL,
} };

void it_802ADC04(Item_GObj* gobj)
{
    Item* it = GET_ITEM((HSD_GObj*) gobj);

    if (it->owner == NULL) {
        return;
    }
    ftKb_SpecialAirLw_800F539C((ftKb_GObj*) it->owner);
}

void it_802ADC34(Item_GObj* gobj)
{
    Item_8026A8EC(gobj);
}


void it_802ADD88(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
}

void it_802ADDB0(Item_GObj* gobj, HSD_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
