#include "itmetalb.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"

ItemStateTable it_803F62C0[] = {
    { -1, NULL, NULL, NULL }, { -1, NULL, NULL, NULL },
    { -1, NULL, NULL, NULL }, { -1, NULL, NULL, NULL },
    { -1, NULL, NULL, NULL },
};

void it_802953C8(Item_GObj* gobj)
{
    Item* it = GET_ITEM((HSD_GObj*) gobj);
    it->xDCE_flag.bits.b7 = 0;
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
