#include "ittincle.h"

#include "gr/ground.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "lb/lb_00B0.h"

#include <baselib/random.h>
#include <MSL/math.h>

/* 2EC870 */ static void it_802EC870(Item_GObj*, int);

ItemStateTable it_803F9000[] = {
    {
        -1,
        itTincle_UnkMotion0_Anim,
        itTincle_UnkMotion0_Phys,
        itTincle_UnkMotion0_Coll,
    },
    {
        0,
        itTincle_UnkMotion1_Anim,
        itTincle_UnkMotion1_Phys,
        itTincle_UnkMotion1_Coll,
    },
    {
        0,
        itTincle_UnkMotion2_Anim,
        itTincle_UnkMotion2_Phys,
        itTincle_UnkMotion2_Coll,
    },
    {
        0,
        itTincle_UnkMotion3_Anim,
        itTincle_UnkMotion3_Phys,
        itTincle_UnkMotion3_Coll,
    },
    {
        0,
        itTincle_UnkMotion4_Anim,
        itTincle_UnkMotion4_Phys,
        itTincle_UnkMotion4_Coll,
    },
    {
        0,
        itTincle_UnkMotion5_Anim,
        itTincle_UnkMotion5_Phys,
        itTincle_UnkMotion5_Coll,
    },
    {
        1,
        itTincle_UnkMotion7_Anim,
        itTincle_UnkMotion7_Phys,
        itTincle_UnkMotion7_Coll,
    },
    {
        2,
        itTincle_UnkMotion7_Anim,
        itTincle_UnkMotion7_Phys,
        itTincle_UnkMotion7_Coll,
    },
    {
        3,
        itTincle_UnkMotion8_Anim,
        itTincle_UnkMotion8_Phys,
        itTincle_UnkMotion8_Coll,
    },
    {
        4,
        itTincle_UnkMotion9_Anim,
        itTincle_UnkMotion9_Phys,
        itTincle_UnkMotion9_Coll,
    },
    {
        5,
        itTincle_UnkMotion10_Anim,
        itTincle_UnkMotion10_Phys,
        itTincle_UnkMotion10_Coll,
    },
    {
        6,
        itTincle_UnkMotion11_Anim,
        itTincle_UnkMotion11_Phys,
        itTincle_UnkMotion11_Coll,
    },
    {
        6,
        itTincle_UnkMotion12_Anim,
        itTincle_UnkMotion12_Phys,
        itTincle_UnkMotion12_Coll,
    },
};

static void data_ordering(void)
{
    HSD_JObjSetRotationY(NULL, 0.0f);
    HSD_JObjSetRotationY(NULL, 10.0f);
}

extern Vec3 it_803B8740;

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

void it_802EB6DC(Item_GObj* gobj)
{
    s32 randi_result;
    Item* ip = GET_ITEM(gobj);
    itTincleAttributes* sa = ip->xC4_article_data->x4_specialAttributes;
    Item* unused;
    s32 unused2;
    s32 range_i;
    PAD_STACK(8);

    randi_result = HSD_Randi(ABS(sa->x10 - sa->xC));
    ip->pos.x = sa->xC + randi_result;
    ip->pos.y = sa->x14;
    ip->pos.z = 2.0f;
    it_802762BC(ip);
    ip->x40_vel.x = ip->x40_vel.y = ip->x40_vel.z = 0.0f;
    range_i = sa->x4 - sa->x8;
    if (range_i < 0) {
        range_i = -range_i;
    }
    ip->xDD4_itemVar.tincle.x20 = HSD_Randi(range_i);
    ip->xDD4_itemVar.tincle.x24 = 0;
    ip->xDD4_itemVar.tincle.x28 = 0;
    ip->xDD4_itemVar.tincle.x2C = 0;
    ip->xDD4_itemVar.tincle.x34 = 0.0f;
    ip->xDD4_itemVar.tincle.x38 = 0.0f;
    ip->xDD4_itemVar.tincle.x4C = 0.0f;
    it_802756D0(gobj);
    HSD_JObjSetFlagsAll(GET_JOBJ(gobj), 0x10);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    it_802EC9E8(gobj);
}

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

void it_802EB870(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itTincleAttributes* sa = ip->xC4_article_data->x4_specialAttributes;
    s32 s;
    PAD_STACK(8);

    s = (ABS(sa->x10 - sa->xC) / 2);
    ip->xDD4_itemVar.tincle.x58 = sa->xC + s;
    s = HSD_Randi(ABS(sa->x1C - sa->x20));
    ip->xDD4_itemVar.tincle.x5C = sa->x20 + s;
    ip->x40_vel.y = -sa->x18;
    ip->x40_vel.x = 0.0f;
    HSD_JObjClearFlagsAll(GET_JOBJ(gobj), 0x10);
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    it_802EC9E8(gobj);
}

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

void itTincle_UnkMotion2_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    f32 bounce_count = ip->xDD4_itemVar.tincle.x3C;
    itTincleAttributes* sa = ip->xC4_article_data->x4_specialAttributes;
    PAD_STACK(8);

    if (bounce_count == 0.0f) {
        ip->xDD4_itemVar.tincle.x3C = 2.0f;
        ip->xDD4_itemVar.tincle.x2C = sa->x28 * 2;
        ip->xDD4_itemVar.tincle.x38 *= -1.0f;
    } else {
        s32 half_cycle = ip->xDD4_itemVar.tincle.x2C;
        if (half_cycle == 0) {
            ip->xDD4_itemVar.tincle.x3C = bounce_count - 1.0f;
        } else {
            if (half_cycle < sa->x28) {
                ip->x40_vel.y += ip->xDD4_itemVar.tincle.x38;
            } else {
                ip->x40_vel.y -= ip->xDD4_itemVar.tincle.x38;
            }
            ip->xDD4_itemVar.tincle.x2C -= 1;
        }
    }

    {
        s32 timer = ip->xDD4_itemVar.tincle.x20;
        if (timer != 0) {
            ip->xDD4_itemVar.tincle.x20 = timer - 1;
            return;
        }
    }

    {
        s32 drift_state = ip->xDD4_itemVar.tincle.x24;
        if (drift_state == 0) {
            if (HSD_Randi(sa->x30) == 0) {
                it_802EC870(gobj, 0);
                return;
            }
            ip->x40_vel.x = 0.0f;
            ip->xDD4_itemVar.tincle.x20 = sa->x2C;
            return;
        }
        {
            s32 drift_counter = ip->xDD4_itemVar.tincle.x28;
            if (drift_counter >= drift_state) {
                ip->x40_vel.x = 0.0f;
                ip->xDD4_itemVar.tincle.x34 = 0.0f;
                ip->xDD4_itemVar.tincle.x28 = 0;
                ip->xDD4_itemVar.tincle.x24 = 0;
                ip->xDD4_itemVar.tincle.x20 = sa->x2C;
                return;
            }
            if (drift_counter == (drift_state / 2)) {
                ip->xDD4_itemVar.tincle.x34 *= -1.0f;
            }
            ip->x40_vel.x += ip->xDD4_itemVar.tincle.x34;
            ip->xDD4_itemVar.tincle.x28 += 1;
        }
    }
}

bool itTincle_UnkMotion2_Coll(Item_GObj* gobj)
{
    PAD_STACK(8);
    if (it_8026DAA8(gobj) != 0) {
        it_802EC870(gobj, 1);
    }
    return false;
}

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

void it_802EBFAC(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itTincleAttributes* sa = ip->xC4_article_data->x4_specialAttributes;
    f32 dist = ip->xDD4_itemVar.tincle.x5C - ip->pos.y;
    f32 max_speed = sa->x4C;
    PAD_STACK(16);

    if (dist > max_speed) {
        ip->x40_vel.y = max_speed;
        ip->x40_vel.z = 0.0f;
        ip->x40_vel.x = 0.0f;
        ip->xDD4_itemVar.tincle.x2C = dist;
        {
            f32 vel_y = ip->x40_vel.y;
            ip->xDD4_itemVar.tincle.x38 =
                -(vel_y * vel_y) / (vel_y + (ip->xDD4_itemVar.tincle.x2C * 2));
        }
        ip->xDD4_itemVar.tincle.x20 = 0;
        Item_80268E5C(gobj, 5, ITEM_UNK_0x1);
        return;
    }
    if (ip->xDD4_itemVar.tincle.x30 == 2.0f) {
        ip->x40_vel.y = ip->xDD4_itemVar.tincle.x44;
        ip->x40_vel.z = 0.0f;
        ip->x40_vel.x = 0.0f;
        ip->xDD4_itemVar.tincle.x38 = ip->xDD4_itemVar.tincle.x48;
        ip->xDD4_itemVar.tincle.x2C = ip->xDD4_itemVar.tincle.x40;
        ip->xDD4_itemVar.tincle.x20 = sa->x2C;
        ip->xDD4_itemVar.tincle.x24 = 0;
        Item_80268E5C(gobj, 2, ITEM_UNK_0x1);
        return;
    }
    ip->x40_vel.y = ip->xDD4_itemVar.tincle.x44;
    ip->x40_vel.z = 0.0f;
    ip->x40_vel.x = 0.0f;
    ip->xDD4_itemVar.tincle.x38 = ip->xDD4_itemVar.tincle.x48;
    ip->xDD4_itemVar.tincle.x2C = ip->xDD4_itemVar.tincle.x40;
    Item_80268E5C(gobj, 5, ITEM_UNK_0x1);
}

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

void it_802EC69C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itTincleAttributes* sa = ip->xC4_article_data->x4_specialAttributes;
    f32 dist;
    PAD_STACK(16);

    ip->pos.z = 0.0f;
    dist = ABS(ip->xDD4_itemVar.tincle.x5C - ip->pos.y);
    if (dist < sa->x44) {
        ip->xDD4_itemVar.tincle.x5C += 20.0f;
        dist += 20.0f;
    }
    ip->x40_vel.y = sa->x50;
    ip->x40_vel.z = 0.0f;
    ip->x40_vel.x = 0.0f;
    ip->xDD4_itemVar.tincle.x2C = dist;
    ip->xDD4_itemVar.tincle.x38 =
        -(ip->x40_vel.y * ip->x40_vel.y) /
        (ip->x40_vel.y + (ip->xDD4_itemVar.tincle.x2C * 2));
    ip->xDD4_itemVar.tincle.x20 = 0;
    it_802762BC(ip);
    it_802756E0(gobj);
    Item_80268E5C(gobj, 0xC, ITEM_UNK_0x1);
    it_802EC9E8(gobj);
}

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

static void it_802EC870(Item_GObj* gobj, int arg1)
{
    Item* ip = GET_ITEM(gobj);
    itTincleAttributes* sa = ip->xC4_article_data->x4_specialAttributes;

    if (arg1 != 0) {
        ip->facing_dir = -ip->facing_dir;
        ip->x40_vel.x *= -1.0f;
        ip->xDD4_itemVar.tincle.x34 *= -1.0f;
        return;
    }

    ip->facing_dir = (ip->pos.x < ip->xDD4_itemVar.tincle.x58) ? 1.0f : -1.0f;
    if (HSD_Randi(3) == 0) {
        ip->facing_dir *= -1.0f;
    }
    if (ip->pos.x < sa->xC) {
        ip->facing_dir = 1.0f;
    }
    if (ip->pos.x > sa->x10) {
        ip->facing_dir = -1.0f;
    }

    {
        f32 abs = ABS(sa->x38 - sa->x34);
        ip->x40_vel.x = abs * HSD_Randf();
    }
    ip->xDD4_itemVar.tincle.x24 = sa->x3C;
    ip->xDD4_itemVar.tincle.x34 =
        (sa->x38 - ip->x40_vel.x) / (ip->xDD4_itemVar.tincle.x24 / 2);
    ip->x40_vel.x = ip->x40_vel.x * ip->facing_dir;
    ip->xDD4_itemVar.tincle.x34 = ip->xDD4_itemVar.tincle.x34 * ip->facing_dir;
    ip->xDD4_itemVar.tincle.x28 = 0;
}

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

Item_GObj* it_802ECA70(HSD_GObj* gobj)
{
    u8 _pad[80];
    Vec3 pos = it_803B8740;
    u8 _pad2[4];
    Item_GObj* new_gobj = it_8027B5B0(It_Kind_Tincle, &pos, NULL, NULL, 1);

    if (new_gobj != NULL) {
        Item* ip = GET_ITEM(new_gobj);

        ip->scl = Ground_801C0498();
        HSD_JObjSetScaleX(new_gobj->hsd_obj, ip->scl);
        HSD_JObjSetScaleY(new_gobj->hsd_obj, ip->scl);
        HSD_JObjSetScaleZ(new_gobj->hsd_obj, ip->scl);
        ip->facing_dir = 0.0f;
        ip->xDD4_itemVar.tincle.x64 = gobj;
        ip->x378_itemColl.joint_id_skip = 5;
        it_802EB6DC(new_gobj);
    }
    return new_gobj;
}

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
