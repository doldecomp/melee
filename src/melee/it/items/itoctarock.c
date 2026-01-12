#include "itoctarock.h"

#include "math.h"
#include "placeholder.h"

#include "cm/camera.h"
#include "ft/ftlib.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "it/items/itoctarockstone.h"
#include "lb/lb_00B0.h"
#include "mp/mpcoll.h"
#include "sysdolphin/baselib/random.h"

extern f32* it_804D6D40;

ItemStateTable it_803F8B48[] = {
    {
        0,
        itOctarock_UnkMotion0_Anim,
        itOctarock_UnkMotion0_Phys,
        itOctarock_UnkMotion0_Coll,
    },
    {
        1,
        itOctarock_UnkMotion1_Anim,
        itOctarock_UnkMotion1_Phys,
        itOctarock_UnkMotion1_Coll,
    },
    {
        -1,
        itOctarock_UnkMotion2_Anim,
        itOctarock_UnkMotion2_Phys,
        itOctarock_UnkMotion2_Coll,
    },
    {
        3,
        itOctarock_UnkMotion3_Anim,
        itOctarock_UnkMotion3_Phys,
        itOctarock_UnkMotion3_Coll,
    },
    {
        2,
        itOctarock_UnkMotion4_Anim,
        itOctarock_UnkMotion4_Phys,
        itOctarock_UnkMotion4_Coll,
    },
    {
        3,
        itOctarock_UnkMotion5_Anim,
        itOctarock_UnkMotion5_Phys,
        NULL,
    },
    {
        4,
        itOctarock_UnkMotion6_Anim,
        itOctarock_UnkMotion6_Phys,
        itOctarock_UnkMotion6_Coll,
    },
    {
        3,
        itOctarock_UnkMotion7_Anim,
        itOctarock_UnkMotion7_Phys,
        itOctarock_UnkMotion7_Coll,
    },
    {
        3,
        itOctarock_UnkMotion8_Anim,
        itOctarock_UnkMotion8_Phys,
        itOctarock_UnkMotion8_Coll,
    },
};

static inline void itOctarock_SetFacingDir(Item* ip)
{
    s32 dir = (ip->facing_dir == -1.0f) ? -1 : 1;
    mpCollSetFacingDir(&ip->x378_itemColl, dir);
}

void it_802E4A44(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_8027B730(gobj);
    ip->facing_dir = it_8026B684(&ip->pos);
    itOctarock_SetFacingDir(ip);
    it_8027C56C(gobj, ip->facing_dir);
    ip->xD5C = 0;
    ip->xDC8_word.flags.x15 = false;
    it_8027542C(gobj);
    it_80275270(gobj);
    ip->xDC8_word.flags.x19 = true;
    ip->xDD4_itemVar.octarock.x32 = 0;
    it_802E4DB4(gobj);
}

bool it_802E4B00(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itOctarockAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    ip->init_facing_dir = ip->facing_dir;
    ip->xC9C += it_8027CBFC(gobj);
    if (ip->xC9C > *attr->x0 || ip->msid == 6) {
        it_8027C9D8(ip);
        it_802756D0(gobj);
        it_80275474(gobj);
        it_8027CE44(gobj);
        Camera_80030E44(2, &ip->pos);
        if (HSD_Randf() < it_804D6D40[2]) {
            it_802E58A0(gobj);
        } else {
            it_802E57D4(gobj);
        }
    } else {
        it_802E4E6C(gobj);
    }
    return false;
}

void it_802E4C08(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itOctarockAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    it_8027CAD8(gobj);
    ip->xDD4_itemVar.octarock.x32 = attr->x1C;
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
}

bool itOctarock_UnkMotion0_Anim(Item_GObj* gobj)
{
    if (!it_80272C6C(gobj)) {
        Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    }
    return false;
}

void itOctarock_UnkMotion0_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itOctarockAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    if (ip->xDD4_itemVar.octarock.x32 == 0) {
        switch (it_802E52E0(gobj)) {
        case 0:
            ip->xDD4_itemVar.octarock.x32 = attr->x1C;
            break;
        case 1:
            it_802E53C8(gobj);
            break;
        case 2:
            it_802E503C(gobj);
            break;
        }
    } else {
        ip->xDD4_itemVar.octarock.x32--;
    }
    it_8027C8D0(&ip->x40_vel, &ip->x378_itemColl.floor.normal, ip->facing_dir);
    it_8027C0A8(gobj, ip->facing_dir, 0.0f);
}

bool itOctarock_UnkMotion0_Coll(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_802E4DB4);
    return it_8027C794(gobj);
}

void it_802E4DB4(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itOctarockAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    ip->x40_vel.x *= attr->x4;
    Item_80268E5C(gobj, 2, 3);
}

bool itOctarock_UnkMotion2_Anim(Item_GObj* gobj)
{
    return false;
}

void itOctarock_UnkMotion2_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itOctarock_UnkMotion2_Coll(Item_GObj* gobj)
{
    it_8026E414(gobj, it_802E4C08);
    return it_8027C794(gobj);
}

void it_802E4E6C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (it_8027B798(gobj, &ip->x40_vel)) {
        if (ip->x40_vel.y <= 0.2f) {
            ip->x40_vel.y = 0.2f;
        }
        it_802762BC(ip);
    } else {
        it_802762B0(ip);
    }
    ip->facing_dir = ip->init_facing_dir;
    itOctarock_SetFacingDir(ip);
    Item_80268E5C(gobj, 3, ITEM_ANIM_UPDATE);
}

bool itOctarock_UnkMotion3_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (!it_80272C6C(gobj)) {
        if (ip->ground_or_air == GA_Air) {
            Item_80268E5C(gobj, 3, ITEM_ANIM_UPDATE);
        } else {
            it_802E4C08(gobj);
        }
    }
    return false;
}

void itOctarock_UnkMotion3_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->ground_or_air == GA_Air) {
        ip->x40_vel.y -= ip->xCC_item_attr->x10_fall_speed;
    }
}

bool itOctarock_UnkMotion3_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->ground_or_air == GA_Air) {
        it_8026E414(gobj, it_802E4C08);
    } else {
        it_8026D62C(gobj, it_802E4DB4);
    }
    return it_8027C794(gobj);
}

void it_802E503C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.octarock.x32 = 0x15;
    itResetVelocity(ip);
    ip->xDD4_itemVar.octarock.x2C = 0;
    it_802E5944(gobj);
    it_802762BC(ip);
    Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE);
}

bool itOctarock_UnkMotion4_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itOctarockAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    it_802E595C(ip->xBBC_dynamicBoneTable->bones[1], ip);
    if (ip->xDD4_itemVar.octarock.x32 == 0) {
        Vec3 v;
        PAD_STACK(12);
        lb_8000B1CC(ip->xBBC_dynamicBoneTable->bones[0xE], NULL, &v);
        it_802E8ADC(gobj, &v, (s32) ip->facing_dir, attr->x10, attr->x14,
                    attr->x18);
        Item_8026AE84(ip, 0x137, 0x7F, 0x40);
    }
    if (!it_80272C6C(gobj)) {
        it_8026DA08(gobj);
        ip->xDD4_itemVar.octarock.x32 = 0;
        it_802E4C08(gobj);
    }
    ip->xDD4_itemVar.octarock.x32--;
    return false;
}

void itOctarock_UnkMotion4_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.octarock.x2C == 0 && ip->x40_vel.y > 0.0f) {
        it_802762BC(ip);
        ip->xDD4_itemVar.octarock.x2C = 1;
    }
}

bool itOctarock_UnkMotion4_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(8);
    if (ip->ground_or_air == GA_Ground) {
        if (!it_8026D5CC(gobj)) {
            it_802E4DB4(gobj);
        }
    } else if (it_8026DA70(gobj)) {
        ip->xDD4_itemVar.octarock.x2C = 0;
    } else {
        it_802763E0(gobj);
        ip->pos = ip->x378_itemColl.cur_pos;
    }
    return it_8027C794(gobj);
}

s32 it_802E52E0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itOctarockAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    s32 result = 0;
    HSD_GObj* fighter = ftLib_8008627C(&ip->pos, NULL);

    if (fighter != NULL) {
        f32 facing;
        Vec3 v;
        PAD_STACK(4);
        ftLib_80086644(fighter, &v);
        if (ABS(v.x - ip->pos.x) <= attr->x8) {
            if (ABS(v.y - ip->pos.y) <= attr->xC) {
                if (ip->pos.x < v.x) {
                    facing = 1.0f;
                } else {
                    facing = -1.0f;
                }
                if (facing != ip->facing_dir) {
                    result = 1;
                } else {
                    result = 2;
                }
            }
        }
    }
    return result;
}

void it_802E53C8(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itResetVelocity(ip);
    ip->xDD4_itemVar.octarock.x32 = 0x16;
    ip->xDD4_itemVar.octarock.x2C = 0;
    it_802E5944(gobj);
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
}

bool itOctarock_UnkMotion1_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_802E595C(ip->xBBC_dynamicBoneTable->bones[1], ip);
    if (ip->xDD4_itemVar.octarock.x32 == 0) {
        ip->facing_dir = -ip->facing_dir;
        itOctarock_SetFacingDir(ip);
    }
    if (!it_80272C6C(gobj)) {
        it_8026D5CC(gobj);
        ip->xDD4_itemVar.octarock.x32 = 0;
        it_802E4C08(gobj);
        return false;
    }
    ip->xDD4_itemVar.octarock.x32 = ip->xDD4_itemVar.octarock.x32 - 1;
    return false;
}

void itOctarock_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->ground_or_air == GA_Ground && ip->x40_vel.y > 0.0f) {
        it_802762BC(ip);
    }
}

bool itOctarock_UnkMotion1_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(8);
    if (ip->ground_or_air == GA_Ground) {
        if (!it_8026D5CC(gobj)) {
            it_802E4DB4(gobj);
        }
    } else if (it_8026DA70(gobj)) {
        it_802762B0(ip);
    } else {
        it_802763E0(gobj);
        ip->pos = ip->x378_itemColl.cur_pos;
    }
    return it_8027C794(gobj);
}

void it_2725_Logic2_PickedUp(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 5, ITEM_ANIM_UPDATE);
}

bool itOctarock_UnkMotion5_Anim(Item_GObj* gobj)
{
    Item* _ip = GET_ITEM(gobj); // NOTE: unused
    if (!it_80272C6C(gobj)) {
        Item_80268E5C(gobj, 5, ITEM_ANIM_UPDATE);
    }
    return false;
}

void itOctarock_UnkMotion5_Phys(Item_GObj* gobj) {}

void it_2725_Logic2_Dropped(Item_GObj* gobj)
{
    it_8027CBA4(gobj);
    it_802E4DB4(gobj);
}

void it_2725_Logic2_Thrown(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_8027CB3C(gobj);
    ip->xDD4_itemVar.octarock.x32 = 0;
    Item_80268E5C(gobj, 6, ITEM_ANIM_UPDATE);
}

bool itOctarock_UnkMotion6_Anim(Item_GObj* gobj)
{
    if (!it_80272C6C(gobj)) {
        Item_80268E5C(gobj, 6, ITEM_ANIM_UPDATE);
    }
    return false;
}

void itOctarock_UnkMotion6_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itOctarock_UnkMotion6_Coll(Item_GObj* gobj)
{
    return it_8027C824(gobj, NULL);
}

void it_802E57D4(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_802762BC(ip);
    it_8027B964(gobj, 0);
    ip->xDD4_itemVar.octarock.x18 = 0;
    Item_80268E5C(gobj, 7, ITEM_ANIM_UPDATE);
}

bool itOctarock_UnkMotion7_Anim(Item_GObj* gobj)
{
    if (!it_80272C6C(gobj)) {
        Item_80268E5C(gobj, 7, ITEM_ANIM_UPDATE);
    }
    return false;
}

void itOctarock_UnkMotion7_Phys(Item_GObj* gobj) {}

bool itOctarock_UnkMotion7_Coll(Item_GObj* gobj)
{
    return it_8027C79C(gobj);
}

void it_802E58A0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_802762BC(ip);
    it_8027BA54(gobj, &ip->x40_vel);
    it_802762BC(ip);
    Item_80268E5C(gobj, 8, 3);
}

bool itOctarock_UnkMotion8_Anim(Item_GObj* gobj)
{
    return false;
}

void itOctarock_UnkMotion8_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->x40_vel.y -= ip->xCC_item_attr->x10_fall_speed;
}

bool itOctarock_UnkMotion8_Coll(Item_GObj* gobj)
{
    return it_8027C794(gobj);
}

void it_802E5944(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.octarock.x20.x = 0.0f;
    ip->xDD4_itemVar.octarock.x20.y = 0.0f;
    ip->xDD4_itemVar.octarock.x20.z = 0.0f;
}

void it_802E595C(HSD_JObj* jobj, Item* ip)
{
    if (jobj != NULL) {
        Vec3 zero;
        Vec3 pos;
        zero.x = zero.y = zero.z = 0.0f;
        HSD_JObjGetTranslation(jobj, &pos);
        ip->x40_vel.x =
            ip->facing_dir * (pos.z - ip->xDD4_itemVar.octarock.x20.z);
        ip->x40_vel.y = pos.y - ip->xDD4_itemVar.octarock.x20.y;
        ip->x40_vel.z = pos.x - ip->xDD4_itemVar.octarock.x20.x;
        ip->xDD4_itemVar.octarock.x20 = pos;
        HSD_JObjSetTranslate(jobj, &zero);
    }
}

void it_802E5AA4(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
