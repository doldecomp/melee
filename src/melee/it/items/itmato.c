#include <platform.h>

#include "itmato.h"

#include "it/inlines.h"
#include "it/itCommonItems.h"
#include "it/types.h"

#include <dolphin/mtx.h>
#include <melee/gr/ground.h>
#include <melee/it/item.h>
#include <melee/lb/lb_00B0.h>

extern void it_8027B730(void);

ItemStateTable it_803F83E0[] = {
    {
        -1,
        it_802D858C,
        it_802D8594,
        it_802D85EC,
    },
};

void it_802D84F8(Item_GObj* item_gobj)
{
    Item* it = GET_ITEM(item_gobj);
    it_8027B730();
    it->facing_dir = 0;
    it->xD5C = 0;
    it->xDCC_flag.b3 = 0;
    it_802D8554(item_gobj);
}

void it_802D8554(Item_GObj* item_gobj)
{
    Item* it = GET_ITEM(item_gobj);
    it->x40_vel.x = it->x40_vel.y = 0;
    Item_80268E5C(item_gobj, 0, ITEM_ANIM_UPDATE);
}

bool it_802D858C(Item_GObj* item_gobj)
{
    return false;
}

void it_802D8594(Item_GObj* item_gobj)
{
    Item* it = GET_ITEM(item_gobj);
    if (it->xDD4_itemVar.mato.x0 != NULL) {
        Vec3 pos;
        lb_8000B1CC(it->xDD4_itemVar.mato.x0, NULL, &pos);
        it->pos = pos;
    }
}

bool it_802D85EC(Item_GObj* item_gobj)
{
    return false;
}

bool it_802D85F4(Item_GObj* item_gobj)
{
    Ground_801C4338();
    return true;
}
