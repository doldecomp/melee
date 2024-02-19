#include "itkirbyhammer.h"

#include "ft/chara/ftKirby/ftKb_Init.h"
#include "it/inlines.h"

void it_802ADC04(Item_GObj* gobj)
{
    Item* it = GET_ITEM((HSD_GObj*) gobj);

    if (it->owner == NULL) {
        return;
    }
    ftKb_SpecialAirLw_800F539C((ftKb_GObj*) it->owner);
}
