#include "itpatapata.h"

#include <placeholder.h>
#include <platform.h>

#include "cm/camera.h"
#include "ft/ftlib.h"

#include "it/forward.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/itCommonItems.h"
#include "it/item.h"
#include "it/items/itnokonoko.h"
#include "lb/lb_00B0.h"
#include "mp/mpcoll.h"
#include "MSL/math.h"

#include <baselib/jobj.h>
#include <baselib/random.h>

ItemStateTable it_803F88C0[] = {
    { 0, NULL, NULL, NULL },
    { 1, itPatapata_UnkMotion1_Anim, itPatapata_UnkMotion1_Phys,
      itPatapata_UnkMotion1_Coll },
    { 1, itPatapata_UnkMotion2_Anim, itPatapata_UnkMotion3_Phys,
      itPatapata_UnkMotion3_Coll },
    { 2, itPatapata_UnkMotion3_Anim, itPatapata_UnkMotion3_Phys,
      itPatapata_UnkMotion3_Coll },
    { -1, itPatapata_UnkMotion4_Anim, itPatapata_UnkMotion4_Phys,
      itPatapata_UnkMotion4_Coll },
    { 3, itPatapata_UnkMotion5_Anim, itPatapata_UnkMotion5_Phys, NULL },
    { 4, itPatapata_UnkMotion6_Anim, itPatapata_UnkMotion6_Phys,
      itPatapata_UnkMotion6_Coll },
    { 1, itPatapata_UnkMotion7_Anim, itPatapata_UnkMotion7_Phys,
      itPatapata_UnkMotion7_Coll },
};

void it_802E05A0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    s32 facing;

    it_8027B730(gobj);
    ip->facing_dir = it_8026B684(&ip->pos);
    if (ip->facing_dir == -1.0f) {
        facing = -1;
    } else {
        facing = 1;
    }
    mpCollSetFacingDir(&ip->x378_itemColl, facing);
    it_8027C56C(gobj, ip->facing_dir);
    ip->xD5C = 0;
    ip->xDC8_word.flags.x15 = 0;
    it_8027542C(gobj);
    it_80275270(gobj);
    ip->xDC8_word.flags.x19 = 1;
    ip->xDD4_itemVar.patapata.x28 = 0xA;
    ip->xDD4_itemVar.patapata.x24 = 0;
    ip->xDD4_itemVar.patapata.x20 = 0;
    ip->xDD4_itemVar.patapata.x40 = 2;
    it_802762BC(ip);
    it_802E0678(gobj);
}

void it_802E0678(Item_GObj* gobj)
{
    PAD_STACK(8);
    it_8027CAD8(gobj);
    it_802E1648(gobj, 1, 2);
}

bool itPatapata_UnkMotion1_Anim(Item_GObj* gobj)
{
    return false;
}

void itPatapata_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.patapata.x28 == 0) {
        it_802E0734(gobj);
        return;
    }
    ip->xDD4_itemVar.patapata.x28 = ip->xDD4_itemVar.patapata.x28 - 1;
}

bool itPatapata_UnkMotion1_Coll(Item_GObj* gobj)
{
    Item* it = gobj->user_data;
    if (it->ground_or_air == GA_Air) {
        it_8026DA08(gobj);
    } else {
        it_8026D564(gobj);
    }
    return false;
}

void it_802E0734(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itPatapataAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;

    switch (ip->xDD4_itemVar.patapata.x40) {
    case 0: {
        s32 x10sq = attrs->x10 * attrs->x10;
        f32 xC = attrs->xC;
        ip->x40_vel.x = ip->facing_dir * attrs->x0->x4;
        ip->x40_vel.y = 0.0f;
        ip->xDD4_itemVar.patapata.x30 = -1.0f * ((2.0f * xC) / x10sq);
        break;
    }
    case 1: {
        f32 half_width;
        s32 frames;
        s32 x24;
        f32 half_height;
        ip->x40_vel.x = ip->facing_dir * attrs->x0->x4;
        half_width = attrs->x14 / 2;
        frames = half_width / attrs->x0->x4;
        ip->xDD4_itemVar.patapata.x20 = frames;
        ip->xDD4_itemVar.patapata.x28 = frames / 2;
        ip->xDD4_itemVar.patapata.x2C =
            -ip->facing_dir * ((2.0f * half_width) / (frames * frames));
        x24 = attrs->x1C / 2;
        half_height = attrs->x18 / 2;
        ip->xDD4_itemVar.patapata.x24 = x24;
        ip->x40_vel.y = -1.0f * (half_height / x24);
        ip->xDD4_itemVar.patapata.x30 = (2.0f * half_height) / (x24 * x24);
        break;
    }
    case 2: {
        s32 x20 = attrs->x24 / 2;
        f32 half_height = attrs->x20 / 2;
        ip->xDD4_itemVar.patapata.x20 = x20;
        ip->x40_vel.y = -1.0f * (half_height / x20);
        ip->xDD4_itemVar.patapata.x30 = (2.0f * half_height) / (x20 * x20);
        break;
    }
    }
    ip->x40_vel.z = 0.0f;
    it_8027C56C(gobj, ip->facing_dir);
    it_802756E0(gobj);
    it_802E1648(gobj, 2, 2);
}

bool itPatapata_UnkMotion2_Anim(Item_GObj* gobj)
{
    PAD_STACK(8);
    if (!it_80272C6C(gobj)) {
        it_802E1648(gobj, 2, 2);
    }
    return false;
}

void itPatapata_UnkMotion3_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itPatapataAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
    PAD_STACK(16);

    if (it_802750E8(gobj, 2) && ip->msid == 2) {
        it_802E0D9C(gobj);
    }
    switch (ip->xDD4_itemVar.patapata.x40) {
    case 0:
        ip->x40_vel.y += ip->xDD4_itemVar.patapata.x30;
        break;
    case 1:
        if (ip->xDD4_itemVar.patapata.x20 == 0) {
            ip->xDD4_itemVar.patapata.x20 = (attrs->x14 / 2) / attrs->x0->x4;
            ip->xDD4_itemVar.patapata.x2C *= -1;
        } else {
            ip->x40_vel.x += ip->xDD4_itemVar.patapata.x2C;
            ip->xDD4_itemVar.patapata.x20 -= 1;
            if (ip->xDD4_itemVar.patapata.x28 == ip->xDD4_itemVar.patapata.x20)
            {
                it_802E0D9C(gobj);
            }
        }
        if (ip->xDD4_itemVar.patapata.x24 == 0) {
            ip->xDD4_itemVar.patapata.x24 = attrs->x1C / 2;
            ip->xDD4_itemVar.patapata.x30 *= -1;
        } else {
            ip->x40_vel.y += ip->xDD4_itemVar.patapata.x30;
            ip->xDD4_itemVar.patapata.x24 -= 1;
        }
        break;
    case 2:
        if (ip->xDD4_itemVar.patapata.x20 == 0) {
            ip->xDD4_itemVar.patapata.x20 = attrs->x24 / 2;
            ip->xDD4_itemVar.patapata.x30 *= -1;
        } else {
            ip->x40_vel.y += ip->xDD4_itemVar.patapata.x30;
            ip->xDD4_itemVar.patapata.x20 -= 1;
        }
        break;
    }
}

bool itPatapata_UnkMotion3_Coll(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    itPatapataAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
    s32 landed = it_8026DA08(gobj);

    if (it_80276308(gobj)) {
        switch (ip->xDD4_itemVar.patapata.x40) {
        case 0:
            if (ip->msid == 2) {
                Item_GObj* gobj2 = gobj; // permuterslop
                it_802E0D9C(gobj2);
            }
            break;
        case 1: {
            f32 width;
            s32 frames;
            ip->x40_vel.x = -ip->facing_dir * attrs->x0->x4;
            ip->xDD4_itemVar.patapata.x20 = frames =
                ((width = attrs->x14) / attrs->x0->x4);
            ip->xDD4_itemVar.patapata.x28 = frames / 2;
            ip->xDD4_itemVar.patapata.x2C =
                ip->facing_dir * ((2.0f * width) / (frames * frames));
            if (ip->msid == 2) {
                it_802E0D9C(gobj);
            }
            break;
        }
        case 2:
            break;
        }
    }
    if (landed) {
        switch (ip->xDD4_itemVar.patapata.x40) {
        case 0: {
            s32 x10 = attrs->x10;
            f32 dir = ip->facing_dir;
            f32 xC = attrs->xC;
            ip->x40_vel.x = dir * attrs->x0->x4;
            ip->x40_vel.y = xC / x10;
            break;
        }
        case 1:
            ip->x40_vel.y *= -1.0f;
            ip->xDD4_itemVar.patapata.x30 *= -1.0f;
            break;
        case 2: {
            s32 frames = attrs->x24;
            f32 height = attrs->x20;
            ip->xDD4_itemVar.patapata.x20 = frames;
            ip->x40_vel.y = height / frames;
            ip->xDD4_itemVar.patapata.x30 =
                -1.0f * ((2.0f * height) / (frames * frames));
            break;
        }
        }
    }
    return false;
}

void it_802E0D9C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itPatapataAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
    switch (ip->xDD4_itemVar.patapata.x40) {
    case 0:
        ip->x40_vel.x = -ip->facing_dir * attrs->x0->x4;
        break;
    case 1:
    case 2:
    default:
        break;
    }
    it_802E1648(gobj, 3, 2);
    ip->facing_dir = -ip->facing_dir;
}

bool itPatapata_UnkMotion3_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (!it_80272C6C(gobj)) {
        s32 facing;
        if (ip->facing_dir == -1.0f) {
            facing = -1;
        } else {
            facing = 1;
        }
        mpCollSetFacingDir(&ip->x378_itemColl, facing);
        it_8027C56C(gobj, ip->facing_dir);
        {
            f32 vel_x = ip->x40_vel.x;
            if ((vel_x < 0.0f && ip->facing_dir == 1.0f) ||
                (vel_x > 0.0f && ip->facing_dir == -1.0f))
            {
                ip->x40_vel.x *= -1.0f;
            }
        }
        it_802E1648(gobj, 2, 2);
    }
    return false;
}

bool it_2725_Logic4_DmgReceived(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    if (ip->msid == 6) {
        it_802E1694(gobj);
    } else {
        it_802E11E0(gobj);
    }
    return false;
}

bool it_802E0F1C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(8);
    it_802E11E0(gobj);
    Item_8026AE84(ip, 0x12E, 0x7F, 0x40);
    ftLib_80086D40(ip->xCFC, 12, 0);
    return false;
}

void itPatapata_Logic4_PickedUp(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 5, ITEM_ANIM_UPDATE);
}

bool itPatapata_UnkMotion5_Anim(Item_GObj* gobj)
{
    if (!it_80272C6C(gobj)) {
        Item_80268E5C(gobj, 5, ITEM_ANIM_UPDATE);
    }
    return false;
}

void itPatapata_UnkMotion5_Phys(Item_GObj* gobj) {}

void it_2725_Logic4_Dropped(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(16);
    it_8027CBA4(gobj);
    ip->xDD4_itemVar.patapata.x24 = 0;
    ip->xDD4_itemVar.patapata.x20 = 0;
    ip->xDD4_itemVar.patapata.x28 = 2;
    Item_80268E5C(gobj, 7, ITEM_ANIM_UPDATE);
}

bool itPatapata_UnkMotion7_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(8);
    if (ip->xDD4_itemVar.patapata.x28 <= 0) {
        it_8027CAD8(gobj);
        it_802E1648(gobj, 1, 2);
    } else {
        ip->xDD4_itemVar.patapata.x28 -= 1;
    }
    return false;
}

void itPatapata_UnkMotion7_Phys(Item_GObj* gobj) {}

bool itPatapata_UnkMotion7_Coll(Item_GObj* gobj)
{
    it_8026DA08(gobj);
    return false;
}

void it_2725_Logic4_Thrown(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_8027CB3C(gobj);
    it_80274C88(gobj);
    ip->xDD4_itemVar.patapata.x28 = 0;
    ip->xDD4_itemVar.patapata.x24 = 0;
    ip->xDD4_itemVar.patapata.x20 = 0;
    Item_80268E5C(gobj, 6, ITEM_ANIM_UPDATE);
}

bool itPatapata_UnkMotion6_Anim(Item_GObj* gobj)
{
    if (!it_80272C6C(gobj)) {
        Item_80268E5C(gobj, 6, ITEM_ANIM_UPDATE);
    }
    return false;
}

void itPatapata_UnkMotion6_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itPatapata_UnkMotion6_Coll(Item_GObj* gobj)
{
    if (it_8026DAA8(gobj) & 0xF) {
        it_802E1694(gobj);
    }
    return false;
}

void it_802E11E0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itPatapataAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
    s32 coll_facing;
    s32 range;
    s32 rand;
    f32 val;

    ip->init_facing_dir = ip->facing_dir;
    it_8027B798(gobj, &ip->x40_vel);
    ip->facing_dir = ip->init_facing_dir;
    if (ip->facing_dir == -1.0f) {
        coll_facing = -1;
    } else {
        coll_facing = 1;
    }
    mpCollSetFacingDir(&ip->x378_itemColl, coll_facing);
    HSD_JObjSetFlagsAll(ip->xBBC_dynamicBoneTable->bones[0], 0x10);
    HSD_JObjClearFlagsAll(ip->xBBC_dynamicBoneTable->bones[18], 0x10);
    HSD_JObjClearFlagsAll(ip->xBBC_dynamicBoneTable->bones[11], 0x10);
    it_802756D0(gobj);
    it_80274C88(gobj);
    it_80275474(gobj);
    it_802E15B0(gobj);
    ip->xDD4_itemVar.patapata.x20 = (s32) attrs->x28;
    ip->xDD4_itemVar.patapata.x28 = attrs->x2C;
    ip->xDD4_itemVar.patapata.x44 = 0;

    range = (s32) (ABS(attrs->x30) + ABS(attrs->x34));

    rand = HSD_Randi(range);
    val = attrs->x30;
    while (rand != 0) {
        val += 0.1f;
        rand--;
    }
    ip->xDD4_itemVar.patapata.x2C = val;

    rand = HSD_Randi(range);
    val = attrs->x30;
    while (rand != 0) {
        val += 0.1f;
        rand--;
    }
    ip->x40_vel.x += val;

    Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE);
}

bool itPatapata_UnkMotion4_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.patapata.x28 == 0) {
        itPatapataAttributes* attrs =
            ip->xC4_article_data->x4_specialAttributes;
        s32 toggle;
        ip->xDD4_itemVar.patapata.x28 = attrs->x2C;
        toggle = ip->xDD4_itemVar.patapata.x44 ^ 1;
        ip->xDD4_itemVar.patapata.x44 = toggle;
        if (toggle != 0) {
            HSD_JObjSetFlagsAll(ip->xBBC_dynamicBoneTable->bones[18], 0x10);
            HSD_JObjSetFlagsAll(ip->xBBC_dynamicBoneTable->bones[11], 0x10);
        } else {
            HSD_JObjClearFlagsAll(ip->xBBC_dynamicBoneTable->bones[18], 0x10);
            HSD_JObjClearFlagsAll(ip->xBBC_dynamicBoneTable->bones[11], 0x10);
        }
    } else {
        ip->xDD4_itemVar.patapata.x28 -= 1;
    }
    return false;
}

void itPatapata_UnkMotion4_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itPatapataAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
    HSD_JObjAddTranslationZ(ip->xBBC_dynamicBoneTable->bones[18],
                            ip->xDD4_itemVar.patapata.x2C);
    it_80272860(gobj, attrs->x38, attrs->x3C);
}

bool itPatapata_UnkMotion4_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.patapata.x20 == 0) {
        ip->xDCC_flag.b3 = true;
        return true;
    }
    ip->xDD4_itemVar.patapata.x20 -= 1;
    return false;
}

void it_802E15B0(Item_GObj* gobj)
{
    Vec3 pos;
    Item_GObj* new_gobj;
    Item* new_ip;
    HSD_JObj* jobj = gobj->hsd_obj;
    Item* ip = GET_ITEM(gobj);

    lb_8000B1CC(jobj, NULL, &pos);
    Camera_80030E44(2, &ip->pos);
    new_gobj = it_802DD7F0(ip->xDD4_itemVar.patapata.x40, &pos, &ip->x40_vel,
                           (s32) ip->facing_dir);
    new_ip = GET_ITEM(new_gobj);
    new_ip->xDD4_itemVar.nokonoko.x34 = ip->xCC8_knockback;
    new_ip->xDD4_itemVar.nokonoko.x3C = ip->xCAC_angle;
    new_ip->xDD4_itemVar.nokonoko.x38 = ip->xCCC_incDamageDirection;
    new_ip->xDD4_itemVar.nokonoko.x4 = ip->xDD4_itemVar.patapata.x4;
    ip->xDD4_itemVar.patapata.x4 = -1;
    it_802DCE00(new_gobj);
}

void it_802E1648(Item_GObj* gobj, int arg1, int arg2)
{
    Item* ip = GET_ITEM(gobj);
    Item_80268E5C(gobj, arg1, arg2);
    it_80274CAC(gobj);
    ip->jumped_on = it_802E0F1C;
}

void it_802E1694(Item_GObj* gobj)
{
    PAD_STACK(8);
    it_8027327C(gobj, 0x444, 0x130);
    it_8027CE44(gobj);
    Item_8026A8EC(gobj);
}

void it_802E16D8(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

Item_GObj* it_802E16F8(s32 arg0, Vec3* pos, s32 facing)
{
    Item* ip;
    s32 coll_facing;
    Vec3 vel = { 0 };
    Item_GObj* gobj = it_8027B5B0(0xD4, pos, NULL, &vel, 1);
    PAD_STACK(8);

    if (gobj != NULL) {
        ip = GET_ITEM(gobj);
        ip->facing_dir = (f32) facing;
        it_8027C56C(gobj, ip->facing_dir);
        if (ip->facing_dir == -1.0f) {
            coll_facing = -1;
        } else {
            coll_facing = 1;
        }
        mpCollSetFacingDir(&ip->x378_itemColl, coll_facing);
        ip->xDD4_itemVar.patapata.x40 = arg0;
        if (ip->xDD4_itemVar.patapata.x40 < 2) {
            Item_80268E5C(gobj, 0, 2);
            HSD_JObjAnimAll(gobj->hsd_obj);
        }
        it_8027CAD8(gobj);
        ip = GET_ITEM(gobj);
        Item_80268E5C(gobj, 1, 2);
        it_80274CAC(gobj);
        ip->jumped_on = it_802E0F1C;
    }
    return gobj;
}
