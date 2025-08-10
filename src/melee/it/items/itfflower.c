#include "itfflower.h"

#include "itlgunbeam.h"

#include "ef/eflib.h"
#include "ef/efsync.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"

#include <baselib/gobj.h>

/* 292FF0 */ static void it_80292FF0(Item_GObj* gobj);
/* 293040 */ static bool itFflower_UnkMotion0_Anim(Item_GObj* gobj);
/* 29310C */ static void itFflower_UnkMotion0_Phys(Item_GObj* gobj);
/* 293110 */ static bool itFflower_UnkMotion0_Coll(Item_GObj* gobj);
/* 29313C */ static void it_8029313C(Item_GObj* gobj);
/* 293164 */ static bool itFflower_UnkMotion6_Anim(Item_GObj* gobj);
/* 293210 */ static void itFflower_UnkMotion1_Phys(Item_GObj* gobj);
/* 293240 */ static bool itFflower_UnkMotion1_Coll(Item_GObj* gobj);
/* 2932AC */ static bool itFflower_UnkMotion5_Anim(Item_GObj* gobj);
/* 2933C0 */ static void itFflower_UnkMotion5_Phys(Item_GObj* gobj);
/* 293414 */ static void itFflower_UnkMotion6_Phys(Item_GObj* gobj);
/* 293444 */ static bool itFflower_UnkMotion6_Coll(Item_GObj* gobj);
/* 29355C */ static bool itFflower_UnkMotion7_Anim(Item_GObj* gobj);
/* 293608 */ static void itFflower_UnkMotion7_Phys(Item_GObj* gobj);
/* 29360C */ static bool itFflower_UnkMotion7_Coll(Item_GObj* gobj);

ItemStateTable it_803F6090[] = {
    { 0, itFflower_UnkMotion0_Anim, itFflower_UnkMotion0_Phys, itFflower_UnkMotion0_Coll },
    { 0, itFflower_UnkMotion6_Anim, itFflower_UnkMotion1_Phys, itFflower_UnkMotion1_Coll },
    { 0, itFflower_UnkMotion5_Anim, itFflower_UnkMotion5_Phys, NULL },
    { 1, itFflower_UnkMotion5_Anim, itFflower_UnkMotion5_Phys, NULL },
    { 2, itFflower_UnkMotion5_Anim, itFflower_UnkMotion5_Phys, NULL },
    { 3, itFflower_UnkMotion5_Anim, itFflower_UnkMotion5_Phys, NULL },
    { 4, itFflower_UnkMotion6_Anim, itFflower_UnkMotion6_Phys, itFflower_UnkMotion6_Coll },
    { 0, itFflower_UnkMotion7_Anim, itFflower_UnkMotion7_Phys, itFflower_UnkMotion7_Coll },
};

static inline void msid_check(Item_GObj* gobj, Item* ip)
{
    switch (ip->msid) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 5:
    case 6:
    case 7:
        efLib_DestroyAll(gobj);
        ip->xDD4_itemVar.fflower.x4 = 0;
        break;
    case 4:
        if (ip->xD4C <= 0) {
            efLib_DestroyAll(gobj);
            ip->xDD4_itemVar.fflower.x4 = 0;
        }
        break;
    }
}

Item_GObj* it_80292D48(Vec3* vec)
{
    Item_GObj* gobj;
    SpawnItem spawn;

    spawn.kind = It_Kind_F_Flower;
    spawn.prev_pos = *vec;
    spawn.prev_pos.z = 0.0F;
    spawn.pos = spawn.prev_pos;
    spawn.facing_dir = -1.0F;
    spawn.x3C_damage = 0;
    spawn.vel.z = 0.0F;
    spawn.vel.y = 0.0F;
    spawn.vel.x = 0.0F;
    spawn.x0_parent_gobj = NULL;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x44_flag.b0 = true;
    spawn.x40 = 0.0F;

    gobj = Item_80268B18(&spawn);
    if (gobj != NULL) {
        it_80292FF0(gobj);
    }
    return gobj;
}

void it_80292E04(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    FFlowerAttr* attr = ip->xC4_article_data->x4_specialAttributes;

    ip->xD4C = attr->x0;
    ip->xAC4_ignoreItemID = Item_8026AE60();
    ip->xDD4_itemVar.fflower.x0 = 0;
    ip->xDD4_itemVar.fflower.x4 = 0;
    it_8029313C(gobj);
}

void it_80292E64(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    enum_t msid = ip->msid;

    switch (msid) {
    case 2:
    case 5:
        Item_80268E5C(gobj, 3, ITEM_ANIM_UPDATE);
        break;
    }
}

void it_80292EAC(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    enum_t msid = ip->msid;

    switch (msid) {
    case 3:
    case 4:
        Item_80268E5C(gobj, 5, ITEM_ANIM_UPDATE);
        break;
    case 2:
    case 5:
        break;
    }
}

void it_80292EF8(Item_GObj* unused, Vec3* vec)
{
    vec->x = 0.0F;
    vec->y = 5.5F;
    vec->z = 2.5F;
}

void it_80292F14(Item_GObj* gobj, Vec3* arg1, f32 arg8)
{
    Item* ip = GET_ITEM(gobj);

    if (ip->xD4C > 0) {
        if (ip->xDD4_itemVar.fflower.x4 == 0) {
            efSync_Spawn(0x473, gobj, ip->xBBC_dynamicBoneTable->bones[4]);
            ip->xDD4_itemVar.fflower.x4 = 1;
        }
        ip->xD4C -= 1;

        it_802996D0(ip->owner, arg1, ip->xAC4_ignoreItemID, arg8);

        ip->xDD4_itemVar.fflower.x0++;
        ip->xDD4_itemVar.fflower.x0 %= 6;
        if (ip->xDD4_itemVar.fflower.x0 == 0) {
            ip->xAC4_ignoreItemID = Item_8026AE60();
        }
    }
}

void it_80292FF0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    ip->x40_vel.z = 0.0F;
    ip->x40_vel.y = 0.0F;
    ip->x40_vel.x = 0.0F;
    it_8026B390(gobj);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
}

bool itFflower_UnkMotion0_Anim(Item_GObj* gobj)
{
    s32 flag;
    Item* ip = GET_ITEM(gobj);

    PAD_STACK(4);

    msid_check(gobj, ip);

    flag = ip->xDC8_word.flags.x2;
    if (it_80272C6C(gobj) == false) {
        Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
        if (flag != 0) {
            it_80274F10(gobj);
            it_8026BE28(gobj);
        }
    }
    return false;
}

void itFflower_UnkMotion0_Phys(Item_GObj* gobj) {}

bool itFflower_UnkMotion0_Coll(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_8029313C);
    return false;
}

void it_8029313C(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
}

bool itFflower_UnkMotion6_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    msid_check(gobj, ip);

    if (it_80272C6C(gobj) == false) {
        Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    }
    return false;
}

void itFflower_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attr = ip->xCC_item_attr;

    it_80272860(gobj, attr->x10_fall_speed, attr->x14_fall_speed_max);
}

bool itFflower_UnkMotion1_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    if (ip->xD4C != 0) {
        it_8026E15C(gobj, it_80292FF0);
        return false;
    }
    return it_8026DF34(gobj);
}

void it_80293284(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
}

bool itFflower_UnkMotion5_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    PAD_STACK(4);

    msid_check(gobj, ip);

    switch (ip->msid) {
    case 2:
        if (it_80272C6C(gobj) == false) {
            Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
        }
        break;
    case 3:
    case 4:
        if (it_80272C6C(gobj) == false) {
            Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE);
        }
        break;
    case 5:
        if (it_80272C6C(gobj) == false) {
            Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
        }
        break;
    }

    return false;
}

void itFflower_UnkMotion5_Phys(Item_GObj* gobj) {}

void it_802933C4(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 6, ITEM_ANIM_UPDATE);
}

void it_802933EC(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 6, ITEM_ANIM_UPDATE);
}

void itFflower_UnkMotion6_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attr = ip->xCC_item_attr;

    it_80272860(gobj, attr->x10_fall_speed, attr->x14_fall_speed_max);
}

bool itFflower_UnkMotion6_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    if (ip->xD4C != 0) {
        it_8026E15C(gobj, it_80292FF0);
        return false;
    }
    return it_8026DF34(gobj);
}

bool it_80293488(Item_GObj* gobj)
{
    itColl_BounceOffVictim(gobj);
    return false;
}

bool it_802934AC(Item_GObj* gobj)
{
    itColl_BounceOffVictim(gobj);
    return false;
}

bool it_802934D0(Item_GObj* gobj)
{
    itColl_BounceOffVictim(gobj);
    return false;
}

bool it_802934F4(Item_GObj* gobj)
{
    return it_80273030(gobj);
}

bool it_80293514(Item_GObj* gobj)
{
    return itColl_BounceOffShield(gobj);
}

void it_80293534(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 7, ITEM_ANIM_UPDATE);
}

bool itFflower_UnkMotion7_Anim(Item_GObj* gobj)
{
    Item* ip;

    ip = GET_ITEM(gobj);

    msid_check(gobj, ip);

    if (it_80272C6C(gobj) == false) {
        Item_80268E5C(gobj, 7, ITEM_ANIM_UPDATE);
    }
    return false;
}

void itFflower_UnkMotion7_Phys(Item_GObj* gobj) {}

bool itFflower_UnkMotion7_Coll(Item_GObj* gobj)
{
    it_8026E8C4(gobj, it_80292FF0, it_8029313C);
    return false;
}

void it_80293640(Item_GObj* gobj, Item_GObj* ref)
{
    it_8026B894(gobj, ref);
}
