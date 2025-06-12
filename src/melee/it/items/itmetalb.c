#include "itmetalb.h"

#include "ft/ftlib.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/itcoll.h"
#include "it/item.h"
#include "pl/plbonuslib.h"

ItemStateTable it_803F62C0[] = {
    { -1, it_8029544C, it_80295454, it_80295458 },
    { -1, it_802954C0, it_802954C8, it_802954F8 },
    { -1, it_8029554C, NULL, NULL },
    { -1, it_802954C0, it_8029557C, it_802955AC },
    { -1, it_802956AC, it_802956B4, it_802956B8 },
};

void it_802953C8(Item_GObj* gobj)
{
    Item* it = GET_ITEM(gobj);
    it->xDCE_flag.b7 = 0;
    it_80295498(gobj);
}

void it_802953FC(Item_GObj* gobj)
{
    Item* it = gobj->user_data;
    it->x40_vel.x = it->x40_vel.y = it->x40_vel.z = 0.0f;

    it_8026B390(gobj);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
}

bool it_8029544C(Item_GObj* gobj)
{
    return false;
}

void it_80295454(Item_GObj* gobj)
{
    return;
}

bool it_80295458(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_80295498);
    it_80276CB8(gobj);

    return false;
}

void it_80295498(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
}

bool it_802954C0(Item_GObj* gobj)
{
    return false;
}

void it_802954C8(Item_GObj* gobj)
{
    Item* it = gobj->user_data;
    it_80272860(gobj, it->xCC_item_attr->x10_fall_speed,
                it->xCC_item_attr->x14_fall_speed_max);
}

bool it_802954F8(Item_GObj* gobj)
{
    it_8026E15C(gobj, it_802953FC);

    return false;
}

void it_80295524(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
}

bool it_8029554C(Item_GObj* gobj)
{
    return false;
}

void it_80295554(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE | ITEM_DROP_UPDATE);
}

void it_8029557C(Item_GObj* gobj)
{
    Item* it = gobj->user_data;
    it_80272860(gobj, it->xCC_item_attr->x10_fall_speed,
                it->xCC_item_attr->x14_fall_speed_max);
}

bool it_802955AC(Item_GObj* gobj)
{
    if (it_8026DA08(gobj)) {
        return true;
    }
    return false;
}

bool it_802955E0(Item_GObj* gobj)
{
    Item* it = GET_ITEM(gobj);
    HSD_GObj* go = it_8027236C(gobj);
    PAD_STACK(8);

    if (go != NULL) {
        if (go->classifier == HSD_GOBJ_CLASS_FIGHTER && it->xDCF_flag.b6) {
            ftLib_800871A8(go, gobj);
            pl_8003E17C(ftLib_80086BE0(go) & 0xFF, ftLib_800874BC(go), gobj);
            return true;
        } else {
            it->xCEC_fighterGObj = NULL;
        }
    }

    return true;
}

void it_80295684(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE);
}

bool it_802956AC(Item_GObj* gobj)
{
    return false;
}

void it_802956B4(Item_GObj* gobj)
{
    return;
}

bool it_802956B8(Item_GObj* gobj)
{
    it_8026E8C4(gobj, it_802953FC, it_80295498);

    return false;
}

void it_802956EC(Item_GObj* gobj, HSD_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
