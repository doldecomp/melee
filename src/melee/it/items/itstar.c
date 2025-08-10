#include "itstar.h"

#include "it/inlines.h"
#include "it/it_2725.h"
#include "it/itCommonItems.h"
#include "it/types.h"

#include <dolphin/mtx.h>
#include <baselib/random.h>
#include <melee/it/it_266F.h>
#include <melee/it/it_26B1.h>
#include <melee/it/item.h>

ItemStateTable it_803F57A0[] = {
    {
        0,
        itStar_UnkMotion0_Anim,
        itStar_UnkMotion0_Phys,
        itStar_UnkMotion0_Coll,
    },
};

void it_80284644(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    itStar_ItemVars* star = item->xC4_article_data->x4_specialAttributes;
    it_8026B390(item_gobj);
    item->xDD4_itemVar.star.dir = HSD_Randi(2) ? +1.0F : -1.0F;
    item->x40_vel.x = star->xvel * item->xDD4_itemVar.star.dir;
    item->x40_vel.y = star->yvel;
    item->x40_vel.z = 0.0F;
    it_802846D4(item_gobj);
}

void it_802846D4(Item_GObj* item_gobj)
{
    Item_80268E5C(item_gobj, 0, ITEM_ANIM_UPDATE);
}

bool itStar_UnkMotion0_Anim(Item_GObj* item_gobj)
{
    return false;
}

void itStar_UnkMotion0_Phys(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    ItemAttr* attr = item->xCC_item_attr;
    it_80272860(item_gobj, attr->x10_fall_speed, attr->x14_fall_speed_max);
}

bool itStar_UnkMotion0_Coll(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    bool val = false;

    if (it_8026DA08(item_gobj)) {
        Item* item2 = GET_ITEM(item_gobj);
        itStar_ItemVars* star = item2->xC4_article_data->x4_specialAttributes;
        item2->x40_vel.x = star->xvel * item2->xDD4_itemVar.star.dir;
        item2->x40_vel.y = star->yvel;
        Item_80268E5C(item_gobj, 0, ITEM_UNK_0x1 | ITEM_HIT_PRESERVE);
        val = true;
    }
    if (it_80276308(item_gobj)) {
        item->xDD4_itemVar.star.dir = -item->xDD4_itemVar.star.dir;
        item->x40_vel.x = -item->x40_vel.x;
        val = true;
    }
    if (it_802763E0(item_gobj)) {
        if (item->x40_vel.y > 0.0F) {
            item->x40_vel.y = 0.0F;
        }
        val = true;
    }
    if (val) {
        Item_8026AE84(item, 0xFA, 0x7F, 0x40);
    }
    return false;
}

bool it_8028482C(Item_GObj* item_gobj)
{
    return true;
}

void it_80284834(Item_GObj* item_gobj, HSD_GObj* ref)
{
    it_8026B894(item_gobj, ref);
}
