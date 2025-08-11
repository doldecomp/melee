#include <baselib/forward.h>

#include "itscball.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"

#include <baselib/gobj.h>

/* 294AD0 */ static void it_80294AD0(Item_GObj* gobj);
/* 294B20 */ static bool itScball_UnkMotion0_Anim(HSD_GObj* gobj);
/* 294B28 */ static void itScball_UnkMotion0_Phys(HSD_GObj* gobj);
/* 294B2C */ static bool itScball_UnkMotion0_Coll(Item_GObj* gobj);
/* 294B58 */ static void it_80294B58(HSD_GObj* gobj);
/* 294B80 */ static bool itScball_UnkMotion1_Anim(HSD_GObj* gobj);
/* 294B88 */ static void itScball_UnkMotion1_Phys(Item_GObj* gobj);
/* 294BB8 */ static bool itScball_UnkMotion1_Coll(Item_GObj* gobj);
/* 294C0C */ static bool itScball_UnkMotion2_Anim(HSD_GObj* gobj);
/* 294C64 */ static bool itScball_UnkMotion3_Anim(HSD_GObj* gobj);
/* 294C6C */ static void itScball_UnkMotion3_Phys(Item_GObj* gobj);
/* 294CB8 */ static bool itScball_UnkMotion3_Coll(Item_GObj* gobj);
/* 294D0C */ static bool itScball_UnkMotion4_Anim(HSD_GObj* gobj);
/* 294D14 */ static void itScball_UnkMotion4_Phys(HSD_GObj* gobj);
/* 294D18 */ static bool itScball_UnkMotion4_Coll(Item_GObj* gobj);

ItemStateTable it_803F6220[] = {
    { -1, itScball_UnkMotion0_Anim, itScball_UnkMotion0_Phys, itScball_UnkMotion0_Coll },
    { -1, itScball_UnkMotion1_Anim, itScball_UnkMotion1_Phys, itScball_UnkMotion1_Coll },
    { -1, itScball_UnkMotion2_Anim, NULL, NULL },
    { 0, itScball_UnkMotion3_Anim, itScball_UnkMotion3_Phys, itScball_UnkMotion3_Coll },
    { -1, itScball_UnkMotion4_Anim, itScball_UnkMotion4_Phys, itScball_UnkMotion4_Coll },
};

void it_3F14_Logic30_Spawned(Item_GObj* gobj)
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

bool itScball_UnkMotion0_Anim(HSD_GObj* gobj)
{
    return false;
}

void itScball_UnkMotion0_Phys(HSD_GObj* gobj) {}

bool itScball_UnkMotion0_Coll(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_80294B58);
    return false;
}

void it_80294B58(HSD_GObj* gobj)
{
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
}

bool itScball_UnkMotion1_Anim(HSD_GObj* gobj)
{
    return false;
}

void itScball_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    ItemAttr* attr = item->xCC_item_attr;

    it_80272860(gobj, attr->x10_fall_speed, attr->x14_fall_speed_max);
}

bool itScball_UnkMotion1_Coll(Item_GObj* gobj)
{
    it_8026E15C(gobj, it_80294AD0);
    return false;
}

void it_3F14_Logic30_PickedUp(Item_GObj* gobj)
{
    Item_80268E5C((HSD_GObj*) gobj, 2, ITEM_ANIM_UPDATE);
}

bool itScball_UnkMotion2_Anim(HSD_GObj* gobj)
{
    return false;
}

void it_3F14_Logic30_Dropped(Item_GObj* gobj)
{
    Item_80268E5C((HSD_GObj*) gobj, 1, 6);
}

void it_3F14_Logic30_Thrown(Item_GObj* gobj)
{
    Item_80268E5C((HSD_GObj*) gobj, 3, 6);
}

bool itScball_UnkMotion3_Anim(HSD_GObj* gobj)
{
    return false;
}
void itScball_UnkMotion3_Phys(Item_GObj* gobj)
{
    ItemAttr* attr = GET_ITEM(gobj)->xCC_item_attr;

    it_80272860(gobj, attr->x10_fall_speed, attr->x14_fall_speed_max);
    it_80274658((HSD_GObj*) gobj, it_804D6D28->x68_float);
}

bool itScball_UnkMotion3_Coll(Item_GObj* gobj)
{
    it_8026E15C(gobj, it_80294AD0);
    return false;
}

void it_3F14_Logic30_EnteredAir(Item_GObj* gobj)
{
    Item_80268E5C((HSD_GObj*) gobj, 4, ITEM_ANIM_UPDATE);
}

bool itScball_UnkMotion4_Anim(HSD_GObj* gobj)
{
    return false;
}

void itScball_UnkMotion4_Phys(HSD_GObj* gobj) {}

bool itScball_UnkMotion4_Coll(Item_GObj* gobj)
{
    it_8026E8C4(gobj, it_80294AD0, it_80294B58);
    return false;
}

bool it_3F14_Logic30_DmgDealt(Item_GObj* gobj)
{
    return true;
}

bool it_3F14_Logic30_Clanked(Item_GObj* gobj)
{
    return true;
}

bool it_3F14_Logic30_Reflected(Item_GObj* gobj)
{
    return it_80273030(gobj);
}

bool it_3F14_Logic30_HitShield(Item_GObj* gobj)
{
    itColl_BounceOffVictim(gobj);
    return false;
}
