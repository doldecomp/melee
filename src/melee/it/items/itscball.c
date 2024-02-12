#include <baselib/forward.h>

#include "itscball.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/item.h"

#include <baselib/gobj.h>

void it_80294B58(HSD_GObj* gobj); /* static */
void it_80294AD0(HSD_GObj* gobj); /* static */

void it_80294AB0(Item_GObj* arg0)
{
    it_80294B58(arg0);
}

void it_80294AD0(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);

    item->x40_vel.x = item->x40_vel.y = item->x40_vel.z = 0.0F;
    it_8026B390(gobj);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
}

int it_80294B20(HSD_GObj* arg0)
{
    return 0;
}

void it_80294B28(HSD_GObj* arg0) {}

int it_80294B2C(Item_GObj* arg0)
{
    it_8026D62C(arg0, it_80294B58);
    return 0;
}

void it_80294B58(HSD_GObj* arg0)
{
    Item_80268E5C(arg0, 1, ITEM_ANIM_UPDATE);
}

int it_80294B80(HSD_GObj* arg0)
{
    return 0;
}

void it_80294B88(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    ItemAttr* attr = item->xCC_item_attr;
    it_80272860(gobj, attr->x10_fall_speed, attr->x14_fall_speed_max);
}

int it_80294BB8(Item_GObj* arg0)
{
    it_8026E15C(arg0, it_80294AD0);
    return 0;
}

void it_80294BE4(Item_GObj* arg0)
{
    Item_80268E5C((HSD_GObj*) arg0, 2, ITEM_ANIM_UPDATE);
}

int it_80294C0C(HSD_GObj* arg0)
{
    return 0;
}

void it_80294C14(Item_GObj* arg0)
{
    Item_80268E5C((HSD_GObj*) arg0, 1, 6);
}

void it_80294C3C(Item_GObj* arg0)
{
    Item_80268E5C((HSD_GObj*) arg0, 3, 6);
}

int it_80294C64(HSD_GObj* arg0)
{
    return 0;
}

void it_80294C6C(Item_GObj* arg0)
{
    ItemAttr* temp_r4;

    // temp_r4 = arg0->user_data->xCC_item_attr;
    // it_80272860(arg0, temp_r4->x10_fall_speed, temp_r4->x14_fall_speed_max);
    // it_80274658((HSD_GObj*) arg0, it_804D6D28->x68_float);
}

int it_80294CB8(Item_GObj* arg0)
{
    it_8026E15C(arg0, it_80294AD0);
    return 0;
}

void it_80294CE4(Item_GObj* arg0)
{
    Item_80268E5C((HSD_GObj*) arg0, 4, ITEM_ANIM_UPDATE);
}

int it_80294D0C(HSD_GObj* arg0)
{
    return 0;
}

void it_80294D14(HSD_GObj* arg0) {}

int it_80294D18(Item_GObj* arg0)
{
    it_8026E8C4(arg0, it_80294AD0, it_80294B58);
    return 0;
}

bool it_80294D4C(Item_GObj* arg0)
{
    return true;
}

bool it_80294D54(Item_GObj* arg0)
{
    return true;
}

bool it_80294D5C(Item_GObj* arg0)
{
    return it_80273030(arg0);
}

bool it_80294D7C(Item_GObj* arg0)
{
    itColl_BounceOffVictim(arg0);
    return false;
}

ItemStateTable it_803F5740[] = {
    { -1, it_80294B20, it_80294B28, it_80294B2C },
    { -1, it_80294B80, it_80294B88, it_80294BB8 },
    { -1, it_80294C0C, NULL, NULL },
    { 0, it_80294C64, it_80294C6C, it_80294CB8 },
    { -1, it_80294D0C, it_80294D14, it_80294D18 },
};
