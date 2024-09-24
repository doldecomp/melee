#include <baselib/forward.h>

#include "itscball.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"

#include <baselib/gobj.h>

/* 294AD0 */ static void it_80294AD0(Item_GObj* gobj);
/* 294B20 */ static bool it_80294B20(HSD_GObj* gobj);
/* 294B28 */ static void it_80294B28(HSD_GObj* gobj);
/* 294B2C */ static bool it_80294B2C(Item_GObj* gobj);
/* 294B58 */ static void it_80294B58(HSD_GObj* gobj);
/* 294B80 */ static bool it_80294B80(HSD_GObj* gobj);
/* 294B88 */ static void it_80294B88(Item_GObj* gobj);
/* 294BB8 */ static bool it_80294BB8(Item_GObj* gobj);
/* 294C0C */ static bool it_80294C0C(HSD_GObj* gobj);
/* 294C64 */ static bool it_80294C64(HSD_GObj* gobj);
/* 294C6C */ static void it_80294C6C(Item_GObj* gobj);
/* 294CB8 */ static bool it_80294CB8(Item_GObj* gobj);
/* 294D0C */ static bool it_80294D0C(HSD_GObj* gobj);
/* 294D14 */ static void it_80294D14(HSD_GObj* gobj);
/* 294D18 */ static bool it_80294D18(Item_GObj* gobj);

ItemStateTable it_803F6220[] = {
    { -1, it_80294B20, it_80294B28, it_80294B2C },
    { -1, it_80294B80, it_80294B88, it_80294BB8 },
    { -1, it_80294C0C, NULL, NULL },
    { 0, it_80294C64, it_80294C6C, it_80294CB8 },
    { -1, it_80294D0C, it_80294D14, it_80294D18 },
};

void it_80294AB0(Item_GObj* gobj)
{
    it_80294B58(gobj);
}

void it_80294AD0(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);

    item->x40_vel.x = item->x40_vel.y = item->x40_vel.z = 0.0F;
    it_8026B390(gobj);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
}

bool it_80294B20(HSD_GObj* gobj)
{
    return false;
}

void it_80294B28(HSD_GObj* gobj) {}

bool it_80294B2C(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_80294B58);
    return false;
}

void it_80294B58(HSD_GObj* gobj)
{
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
}

bool it_80294B80(HSD_GObj* gobj)
{
    return false;
}

void it_80294B88(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    ItemAttr* attr = item->xCC_item_attr;

    it_80272860(gobj, attr->x10_fall_speed, attr->x14_fall_speed_max);
}

bool it_80294BB8(Item_GObj* gobj)
{
    it_8026E15C(gobj, it_80294AD0);
    return false;
}

void it_80294BE4(Item_GObj* gobj)
{
    Item_80268E5C((HSD_GObj*) gobj, 2, ITEM_ANIM_UPDATE);
}

bool it_80294C0C(HSD_GObj* gobj)
{
    return false;
}

void it_80294C14(Item_GObj* gobj)
{
    Item_80268E5C((HSD_GObj*) gobj, 1, 6);
}

void it_80294C3C(Item_GObj* gobj)
{
    Item_80268E5C((HSD_GObj*) gobj, 3, 6);
}

bool it_80294C64(HSD_GObj* gobj)
{
    return false;
}
void it_80294C6C(Item_GObj* gobj)
{
    ItemAttr* attr = GET_ITEM(gobj)->xCC_item_attr;

    it_80272860(gobj, attr->x10_fall_speed, attr->x14_fall_speed_max);
    it_80274658((HSD_GObj*) gobj, it_804D6D28->x68_float);
}

bool it_80294CB8(Item_GObj* gobj)
{
    it_8026E15C(gobj, it_80294AD0);
    return false;
}

void it_80294CE4(Item_GObj* gobj)
{
    Item_80268E5C((HSD_GObj*) gobj, 4, ITEM_ANIM_UPDATE);
}

bool it_80294D0C(HSD_GObj* gobj)
{
    return false;
}

void it_80294D14(HSD_GObj* gobj) {}

bool it_80294D18(Item_GObj* gobj)
{
    it_8026E8C4(gobj, it_80294AD0, it_80294B58);
    return false;
}

bool it_80294D4C(Item_GObj* gobj)
{
    return true;
}

bool it_80294D54(Item_GObj* gobj)
{
    return true;
}

bool it_80294D5C(Item_GObj* gobj)
{
    return it_80273030(gobj);
}

bool it_80294D7C(Item_GObj* gobj)
{
    itColl_BounceOffVictim(gobj);
    return false;
}
