#include "ittincle.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/itCommonItems.h"
#include "it/item.h"
#include "lb/lb_00B0.h"

#include <MSL/math.h>
#include <baselib/random.h>

/* 2EC870 */ static void it_802EC870(Item_GObj*, int);

void it_802EB5C8(Item_GObj* gobj)
{
    Vec3 pos;
    Item* ip = GET_ITEM(gobj);

    it_8027B730(gobj);
    ip->xD5C = 0;
    ip->xDCC_flag.b3 = 0;
    ip->xDC8_word.flags.x15 = 0;
    it_8027542C(gobj);

    lb_8000B1CC(ip->xBBC_dynamicBoneTable->bones[11], NULL, &pos);

    ip->xDD4_itemVar.tincle.x50 = ABS(pos.y - ip->pos.y);

    ip->xDD4_itemVar.tincle.x68 = ip->xC1C;
    it_802EB6DC(gobj);
}

bool itTincle_Logic13_DmgReceived(Item_GObj* gobj)
{
    it_802EC18C(gobj);
    return false;
}

bool itTincle_Logic13_DmgDealt(Item_GObj* gobj)
{
    if (GET_ITEM(gobj)->msid != 7) {
        it_802EC1F4(gobj);
    }
    return false;
}

/// #it_802EB6DC

bool itTincle_UnkMotion0_Anim(Item_GObj* gobj)
{
    return false;
}

void itTincle_UnkMotion0_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.tincle.x20 <= 0) {
        it_802EB870(gobj);
        return;
    }
    ip->xDD4_itemVar.tincle.x20 -= 1;
}

bool itTincle_UnkMotion0_Coll(Item_GObj* gobj)
{
    it_8026DA08(gobj);
    return false;
}

/// #it_802EB870

bool itTincle_UnkMotion1_Anim(Item_GObj* gobj)
{
    return false;
}

void itTincle_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->pos.y <= ip->xDD4_itemVar.tincle.x5C) {
        it_802EBA00(gobj);
    }
}

bool itTincle_UnkMotion1_Coll(Item_GObj* gobj)
{
    it_8026E414(gobj, it_802EBA00);
    return false;
}

void it_802EBA00(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itTincleAttributes* sa = ip->xC4_article_data->x4_specialAttributes;
    f32 dur_f = (f32) sa->x28;
    f32 height = sa->x24;

    ip->x40_vel.z = 0.0f;
    ip->x40_vel.y = 0.0f;
    ip->x40_vel.x = 0.0f;

    ip->xDD4_itemVar.tincle.x20 = sa->x2C;
    ip->x40_vel.y = 0.0f;

    ip->xDD4_itemVar.tincle.x38 = (2.0f * height) / (dur_f * dur_f);
    ip->xDD4_itemVar.tincle.x38 *= 0.5f;

    ip->xDD4_itemVar.tincle.x2C = sa->x28 * 2;
    ip->xDD4_itemVar.tincle.x3C = 2.0f;
    ip->xDD4_itemVar.tincle.x24 = 0;

    it_802756E0(gobj);

    ip->xDC8_word.flags.x1A = 1;

    HSD_JObjClearFlagsAll(GET_JOBJ(gobj), 0x10);

    Item_80268E5C(gobj, 2, ITEM_UNK_0x1);

    it_802EC9E8(gobj);
}

bool itTincle_UnkMotion2_Anim(Item_GObj* gobj)
{
    PAD_STACK(8);
    if (!it_80272C6C(gobj)) {
        Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
    }
    return false;
}

bool itTincle_UnkMotion2_Coll(Item_GObj* gobj)
{
    PAD_STACK(8);
    if (it_8026DAA8(gobj) != 0) {
        it_802EC870(gobj, 1);
    }
    return false;
}

/// #itTincle_UnkMotion2_Phys

/// #itTincle_UnkMotion2_Coll

void it_802EBD14(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(8);
    ip->xDD4_itemVar.tincle.x30 = (f32) ip->msid;
    ip->xDD4_itemVar.tincle.x44 = ip->x40_vel.y;
    ip->xDD4_itemVar.tincle.x48 = ip->xDD4_itemVar.tincle.x38;
    ip->xDD4_itemVar.tincle.x40 = (f32) ip->xDD4_itemVar.tincle.x2C;
    ip->x40_vel.z = 0.0f;
    ip->x40_vel.x = 0.0f;
    ip->x40_vel.y = -ip->xDD4_itemVar.tincle.x54;
    ip->xDD4_itemVar.tincle.x38 = ip->xDD4_itemVar.tincle.x54 / 10.0f;
    ip->xDD4_itemVar.tincle.x20 = 0x13;
    ip->xDD4_itemVar.tincle.x4C = ip->pos.y;
    Item_80268E5C(gobj, 3, ITEM_ANIM_UPDATE);
}

bool itTincle_UnkMotion3_Anim(Item_GObj* gobj)
{
    return false;
}

void itTincle_UnkMotion3_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.tincle.x20 == 0) {
        ip->pos.y = ip->xDD4_itemVar.tincle.x4C;
        ip->x40_vel.y = 0.0f;
        it_802EBE5C(gobj);
    } else {
        ip->x40_vel.y += ip->xDD4_itemVar.tincle.x38;
        ip->xDD4_itemVar.tincle.x20 -= 1;
    }
}

bool itTincle_UnkMotion3_Coll(Item_GObj* gobj)
{
    it_8026E414(gobj, it_802EC18C);
    return false;
}

void it_802EBE5C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itTincleAttributes* data = ip->xC4_article_data->x4_specialAttributes;

    ip->xDD4_itemVar.tincle.x30 = (f32) ip->msid;
    ip->xDD4_itemVar.tincle.x44 = ip->x40_vel.y;
    ip->xDD4_itemVar.tincle.x48 = ip->xDD4_itemVar.tincle.x38;
    ip->xDD4_itemVar.tincle.x40 = (f32) ip->xDD4_itemVar.tincle.x2C;

    ip->x40_vel.z = 0.0f;
    ip->x40_vel.y = 0.0f;
    ip->x40_vel.x = 0.0f;

    ip->xDD4_itemVar.tincle.x20 = data->x40;
    ip->xDD4_itemVar.tincle.x4C = ip->pos.y;

    Item_80268E5C(gobj, 4, 2);
}

bool itTincle_UnkMotion4_Anim(Item_GObj* gobj)
{
    return false;
}

void itTincle_UnkMotion4_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itTincleAttributes* sa = ip->xC4_article_data->x4_specialAttributes;
    if (ip->xDD4_itemVar.tincle.x20 == 0) {
        f32 dist;
        ip->x40_vel.y = -sa->x48;
        dist = ip->xDD4_itemVar.tincle.x4C - ip->pos.y;
        if (dist < 0) {
            dist = -dist;
        }
        if (dist > sa->x44) {
            it_802EC18C(gobj);
        }
    } else {
        ip->xDD4_itemVar.tincle.x20 -= 1;
    }
}

bool itTincle_UnkMotion4_Coll(Item_GObj* gobj)
{
    it_8026E414(gobj, it_802EC18C);
    return false;
}

/// #it_802EBFAC

bool itTincle_UnkMotion5_Anim(Item_GObj* gobj)
{
    return false;
}

void itTincle_UnkMotion5_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->x40_vel.y <= 0.0f) {
        ip->x40_vel.z = 0.0f;
        ip->x40_vel.y = 0.0f;
        ip->x40_vel.x = 0.0f;
        ip->xDD4_itemVar.tincle.x38 = 0.0f;
        ip->xDD4_itemVar.tincle.x2C = 0;
        ip->xDD4_itemVar.tincle.x20 = 0;
        it_802EBA00(gobj);
    } else {
        ip->x40_vel.y += ip->xDD4_itemVar.tincle.x38;
    }
}

bool itTincle_UnkMotion5_Coll(Item_GObj* gobj)
{
    it_8026DAA8(gobj);
    return false;
}

void it_802EC18C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(8);
    ip->x40_vel.z = 0.0f;
    ip->x40_vel.y = 0.0f;
    ip->x40_vel.x = 0.0f;
    it_802756D0(gobj);
    ip->xDD4_itemVar.tincle.x20 = 3;
    Item_80268E5C(gobj, 6, 0x12);
    it_802EC9E8(gobj);
}

void it_802EC1F4(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(8);
    ip->x40_vel.z = 0.0f;
    ip->x40_vel.y = 0.0f;
    ip->x40_vel.x = 0.0f;
    it_802756D0(gobj);
    ip->xDD4_itemVar.tincle.x20 = 0;
    Item_80268E5C(gobj, 7, 0x12);
    it_802EC9E8(gobj);
}

bool itTincle_UnkMotion7_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(8);

    if (ip->xDD4_itemVar.tincle.x20 == 0) {
        ip->xDD4_itemVar.tincle.x20 = -1;
        if (ip->msid == 6) {
            Item_80268E5C(gobj, 7, 1);
        }
    } else if (ip->xDD4_itemVar.tincle.x20 > 0) {
        ip->xDD4_itemVar.tincle.x20 -= 1;
    }

    if (!it_80272C6C(gobj)) {
        it_802EC35C(gobj);
    }

    return false;
}

void itTincle_UnkMotion7_Phys(Item_GObj* gobj) {}

bool itTincle_UnkMotion7_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->ground_or_air == GA_Air) {
        it_8026E414(gobj, it_802EC3F4);
    } else {
        if (ip->xDD4_itemVar.tincle.x20 < 0) {
            it_802EC3F4(gobj);
        }
        it_8026D6F4(gobj, it_802EC35C);
    }
    return false;
}

void it_802EC35C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->pos.z = -10.0f;
    Item_80268E5C(gobj, 8, ITEM_ANIM_UPDATE);
}

bool itTincle_UnkMotion8_Anim(Item_GObj* gobj)
{
    return false;
}

void itTincle_UnkMotion8_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itTincle_UnkMotion8_Coll(Item_GObj* gobj)
{
    it_8026E414(gobj, it_802EC3F4);
    return false;
}

void it_802EC3F4(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    ip->x40_vel.z = 0.0f;
    ip->x40_vel.y = 0.0f;
    ip->x40_vel.x = 0.0f;
    ip->xDC8_word.flags.x1A = 0;
    ip->x70_nudge.z = 0.0f;
    ip->x70_nudge.y = 0.0f;
    ip->x70_nudge.x = 0.0f;
    Item_80268E5C(gobj, 9, ITEM_ANIM_UPDATE);
    it_802EC9E8(gobj);
}

bool itTincle_UnkMotion9_Anim(Item_GObj* gobj)
{
    PAD_STACK(8);
    if (it_80272C6C(gobj) == 0) {
        it_802EC4D0(gobj);
    }
    return false;
}

void itTincle_UnkMotion9_Phys(Item_GObj* gobj) {}

bool itTincle_UnkMotion9_Coll(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_802EC35C);
    return false;
}

void it_802EC4D0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itTincleAttributes* data = ip->xC4_article_data->x4_specialAttributes;
    s32 range;
    PAD_STACK(8);

    range = data->x55 - data->x54;
    if (range < 0) {
        range = -range;
    }

    ip->xDD4_itemVar.tincle.x20 = HSD_Randi(range);
    ip->xDD4_itemVar.tincle.x20 += data->x54;

    Item_80268E5C(gobj, 10, 2);
}

/// #itTincle_UnkMotion10_Anim

bool itTincle_UnkMotion10_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(8);

    if (it_80272C6C(gobj) == 0) {
        ip->xDD4_itemVar.tincle.x20--;
        if (ip->xDD4_itemVar.tincle.x20 != 0) {
            Item_80268E5C(gobj, 10, 2);
        } else {
            it_802EC604(gobj);
        }
    }
    return false;
}

void itTincle_UnkMotion10_Phys(Item_GObj* gobj) {}

bool itTincle_UnkMotion10_Coll(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_802EC35C);
    return false;
}

void it_802EC604(HSD_GObj* gobj)
{
    Item_80268E5C(gobj, 0xB, ITEM_ANIM_UPDATE);
}

bool itTincle_UnkMotion11_Anim(Item_GObj* gobj)
{
    PAD_STACK(16);
    if (!it_80272C6C(gobj)) {
        it_802EC69C(gobj);
    }
    return false;
}

void itTincle_UnkMotion11_Phys(Item_GObj* gobj) {}

bool itTincle_UnkMotion11_Coll(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_802EC35C);
    return false;
}

/// #it_802EC69C

bool itTincle_UnkMotion12_Anim(Item_GObj* gobj)
{
    return false;
}

void itTincle_UnkMotion12_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->x40_vel.y <= 0.0f) {
        ip->x40_vel.z = 0.0f;
        ip->x40_vel.y = 0.0f;
        ip->x40_vel.x = 0.0f;
        ip->xDD4_itemVar.tincle.x38 = 0.0f;
        ip->xDD4_itemVar.tincle.x2C = 0;
        ip->xDD4_itemVar.tincle.x20 = 0;
        it_802EBA00(gobj);
    } else {
        ip->x40_vel.y += ip->xDD4_itemVar.tincle.x38;
    }
}

bool itTincle_UnkMotion12_Coll(Item_GObj* gobj)
{
    it_8026DAA8(gobj);
    return false;
}

void it_802EC830(Item_GObj* gobj)
{
    Item_8026A8EC(gobj);
}

void it_802EC850(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

/// #it_802EC870

void it_802EC9E8(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itECB ecb = ip->xDD4_itemVar.tincle.x68;

    switch (ip->msid) {
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
        ecb.top *= 0.5f;
        ecb.right *= 0.5f;
        ecb.left *= 0.5f;
        break;
    }

    it_80275D5C(gobj, &ecb);
}

/// #it_802ECA70

int it_802ECC8C(Item_GObj* arg0)
{
    return GET_ITEM(arg0)->xDD4_itemVar.tincle.x20;
}

void it_802ECC98(Item_GObj* arg0, f32 arg1)
{
    GET_ITEM(arg0)->xDD4_itemVar.tincle.x54 = arg1;
}

void it_802ECCA4(Item_GObj* gobj, s32* kind, Vec3* pos)
{
    Item* ip = GET_ITEM(gobj);
    *pos = ip->pos;
    pos->y += ip->xDD4_itemVar.tincle.x50;
    *kind = ip->msid;
}
