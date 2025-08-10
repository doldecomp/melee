#include <platform.h>

#include <baselib/forward.h>

#include "itspycloak.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"

#include <dolphin/mtx.h>

/* 295C68 */ static void it_80295C68(Item_GObj* gobj);
/* 295CB8 */ static bool itSpycloak_UnkMotion0_Anim(Item_GObj* gobj);
/* 295CC0 */ static void itSpycloak_UnkMotion0_Phys(Item_GObj* gobj);
/* 295CC4 */ static bool itSpycloak_UnkMotion0_Coll(Item_GObj* gobj);
/* 295D04 */ static void it_80295D04(Item_GObj* gobj);
/* 295D2C */ static bool itSpycloak_UnkMotion3_Anim(Item_GObj* gobj);
/* 295D34 */ static void itSpycloak_UnkMotion1_Phys(Item_GObj* gobj);
/* 295D64 */ static bool itSpycloak_UnkMotion1_Coll(Item_GObj* gobj);
/* 295DB8 */ static bool itSpycloak_UnkMotion2_Anim(Item_GObj* gobj);
/* 295DE8 */ static void itSpycloak_UnkMotion3_Phys(Item_GObj* gobj);
/* 295E18 */ static bool itSpycloak_UnkMotion3_Coll(Item_GObj* gobj);
/* 295E74 */ static bool itSpycloak_UnkMotion4_Anim(Item_GObj* gobj);
/* 295E7C */ static void itSpycloak_UnkMotion4_Phys(Item_GObj* gobj);
/* 295E80 */ static bool itSpycloak_UnkMotion4_Coll(Item_GObj* gobj);

void it_80295C48(Item_GObj* gobj)
{
    it_80295D04(gobj);
}

void it_80295C68(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    item->x40_vel.x = item->x40_vel.y = item->x40_vel.z = 0;
    it_8026B390(gobj);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
}

bool itSpycloak_UnkMotion0_Anim(Item_GObj* gobj)
{
    return false;
}

void itSpycloak_UnkMotion0_Phys(Item_GObj* gobj) {}

bool itSpycloak_UnkMotion0_Coll(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_80295D04);
    it_80276CB8(gobj);
    return false;
}

void it_80295D04(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
}

bool itSpycloak_UnkMotion3_Anim(Item_GObj* gobj)
{
    return false;
}

void itSpycloak_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    ItemAttr* attr = item->xCC_item_attr;

    it_80272860(gobj, attr->x10_fall_speed, attr->x14_fall_speed_max);
}

bool itSpycloak_UnkMotion1_Coll(Item_GObj* gobj)
{
    it_8026E15C(gobj, it_80295C68);
    return false;
}

void it_80295D90(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
}

bool itSpycloak_UnkMotion2_Anim(Item_GObj* gobj)
{
    return false;
}

void it_80295DC0(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 1, 6);
}

void itSpycloak_UnkMotion3_Phys(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    ItemAttr* attr = item->xCC_item_attr;

    it_80272860(gobj, attr->x10_fall_speed, attr->x14_fall_speed_max);
}

bool itSpycloak_UnkMotion3_Coll(Item_GObj* gobj)
{
    if (it_8026DA08(gobj)) {
        return true;
    }
    return false;
}

void it_80295E4C(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE);
}

bool itSpycloak_UnkMotion4_Anim(Item_GObj* gobj)
{
    return false;
}

void itSpycloak_UnkMotion4_Phys(Item_GObj* gobj) {}

bool itSpycloak_UnkMotion4_Coll(Item_GObj* gobj)
{
    it_8026E8C4(gobj, it_80295C68, it_80295D04);
    return false;
}

void it_80295EB4(Item_GObj* gobj, HSD_GObj* ref)
{
    it_8026B894(gobj, ref);
}

ItemStateTable it_803F6370[] = {
    { 0, itSpycloak_UnkMotion0_Anim, itSpycloak_UnkMotion0_Phys, itSpycloak_UnkMotion0_Coll },
    { 0, itSpycloak_UnkMotion3_Anim, itSpycloak_UnkMotion1_Phys, itSpycloak_UnkMotion1_Coll },
    { 0, itSpycloak_UnkMotion2_Anim, NULL, NULL },
    { 0, itSpycloak_UnkMotion3_Anim, itSpycloak_UnkMotion3_Phys, itSpycloak_UnkMotion3_Coll },
    { 0, itSpycloak_UnkMotion4_Anim, itSpycloak_UnkMotion4_Phys, itSpycloak_UnkMotion4_Coll },
};
