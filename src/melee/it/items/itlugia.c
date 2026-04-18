#include "itlugia.h"

#include "placeholder.h"

#include "ef/eflib.h"
#include "gr/stage.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "lb/lb_00B0.h"
#include "lb/lbvector.h"

#include <math.h>
#include <baselib/random.h>

ItemStateTable it_803F7EE8[] = {
    { 0, it_802D1DB4, it_802D1DD8, it_802D1E64 },
    { 1, itLugia_UnkMotion1_Anim, itLugia_UnkMotion1_Phys,
      itLugia_UnkMotion1_Coll },
    { 2, itLugia_UnkMotion2_Anim, itLugia_UnkMotion2_Phys,
      itLugia_UnkMotion2_Coll },
    { 3, itLugia_UnkMotion3_Anim, itLugia_UnkMotion3_Phys,
      itLugia_UnkMotion3_Coll },
    { 4, itLugia_UnkMotion4_Anim, itLugia_UnkMotion4_Phys,
      itLugia_UnkMotion4_Coll },
    { 5, itLugia_UnkMotion5_Anim, itLugia_UnkMotion5_Phys,
      itLugia_UnkMotion5_Coll },
};

ItemStateTable it_803F7F48[] = {
    { 0, it_802D246C, it_802D24A0, it_802D24FC },
};

static inline float my_sqrtf(float x)
{
    u32 pad;

    volatile float y;
    if (x > 0) {
        double guess = __frsqrte((double) x);
        guess = .5 * guess * (3.0 - guess * guess * x);
        guess = .5 * guess * (3.0 - guess * guess * x);
        guess = .5 * guess * (3.0 - guess * guess * x);
        y = (float) (x * guess);
        return y;
    }
    return x;
}

inline float my_sqrtf_accurate(float x)
{
    volatile float y;
    if (x > 0.0f) {
        double guess = __frsqrte((double) x); // returns an approximation to
        guess =
            0.5 * guess * (3.0 - guess * guess * x); // now have 12 sig bits
        guess =
            0.5 * guess * (3.0 - guess * guess * x); // now have 24 sig bits
        guess =
            0.5 * guess * (3.0 - guess * guess * x); // now have 32 sig bits
        guess = 0.5 * guess * (3.0 - guess * guess * x); // extra iteration
        y = (float) (x * guess);
        return y;
    }
    return x;
}

void it_2725_Logic17_Spawned(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itLugiaAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
    ip->xDD4_itemVar.lugia.x64 = ip->pos;
    ip->facing_dir = 0.0f;
    ip->xDAC_itcmd_var0 = 0;
    ip->xDD4_itemVar.lugia.x60 = attrs->x14;
    ip->xDCC_flag.b3 = 0;
    it_802D1D40(gobj);
    it_80279CDC(gobj, attrs->x0);
    ip->xDD4_itemVar.lugia.xE50.x = 0.0f;
}

void it_802D14D0(void) {}

void itLugia_Logic17_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

bool itLugia_UnkMotion1_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    HSD_JObj* child;

    if (jobj == NULL) {
        child = NULL;
    } else {
        child = jobj->child;
    }

    it_8027A160(child, ip);

    if (!it_80272C6C(gobj)) {
        it_802D1580(gobj);
    }

    return false;
}

void itLugia_UnkMotion1_Phys(Item_GObj* gobj)
{
    it_8027A344(gobj);
}

bool itLugia_UnkMotion1_Coll(Item_GObj* gobj)
{
    return false;
}

void it_802D1580(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itLugiaAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
    ip->xDD4_itemVar.lugia.xE50.x = -attrs->x4;
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
}

bool itLugia_UnkMotion2_Anim(Item_GObj* gobj)
{
    HSD_JObj* bone;
    Item* item = GET_ITEM(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);

    if (jobj == NULL) {
        bone = NULL;
    } else {
        bone = jobj->child;
    }

    it_8027A160(bone, item);
    return false;
}

void itLugia_UnkMotion2_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itLugiaAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
    it_8027A344(gobj);
    if (it_80272C6C(gobj)) {
        ip->xDD4_itemVar.lugia.xE50.x += attrs->x8;
    } else {
        ip->xDD4_itemVar.lugia.xE50.x += attrs->xC;
    }
    ip->x40_vel.y += ip->xDD4_itemVar.lugia.xE50.x;
    if (ip->pos.y > Stage_GetBlastZoneTopOffset()) {
        ip->x40_vel.y = 0.0f;
        it_802D16D4(gobj);
    }
}

bool itLugia_UnkMotion2_Coll(Item_GObj* gobj)
{
    return false;
}

void it_802D16D4(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    Item_80268E5C(gobj, 3, ITEM_ANIM_UPDATE);
    item->entered_hitlag = efLib_PauseAll;
    item->exited_hitlag = efLib_ResumeAll;
}

bool itLugia_UnkMotion3_Anim(Item_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* child;

    if (jobj == NULL) {
        child = NULL;
    } else {
        child = jobj->child;
    }

    it_8027A160(child, ip);

    if (!it_80272C6C(gobj)) {
        it_802D16D4(gobj);
    }

    return false;
}

void itLugia_UnkMotion3_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itLugiaAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
    it_8027A344(gobj);
    if (ip->xDD4_itemVar.lugia.x60-- != 0) {
        ip->x40_vel.z = attrs->x10;
    } else {
        ip->x40_vel.z = 0.0f;
        it_802D1830(gobj);
    }
}

bool itLugia_UnkMotion3_Coll(Item_GObj* gobj)
{
    return false;
}

void it_802D1830(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    f32 prod;
    f32 sqrtval;
    itLugiaAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
    f32 x18, disc;
    PAD_STACK(16);

    Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
    disc = ip->pos.y - ip->xDD4_itemVar.lugia.x64.y;
    x18 = attrs->x18;
    prod = 8.0f * x18;
    sqrtval = my_sqrtf_accurate(-((prod * -disc) - (x18 * x18)));
    ip->xDD4_itemVar.lugia.xE50.x = -((-x18 + sqrtval) / 2);
}

bool itLugia_UnkMotion4_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    HSD_JObj* child;

    if (jobj == NULL) {
        child = NULL;
    } else {
        child = jobj->child;
    }

    it_8027A160(child, ip);

    if (!it_80272C6C(gobj)) {
        Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE);
        ip->entered_hitlag = efLib_PauseAll;
        ip->exited_hitlag = efLib_ResumeAll;
    }

    return false;
}

void itLugia_UnkMotion4_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itLugiaAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
    f32 new_var;
    it_8027A344(gobj);
    ip->xDD4_itemVar.lugia.xE50.x += attrs->x18;
    ip->x40_vel.y = ip->xDD4_itemVar.lugia.xE50.x;
    if ((new_var = ip->x40_vel.y) > 0.0f) {
        ip->x40_vel.y = 0.0f;
        it_802D1A44(gobj);
    }
}

bool itLugia_UnkMotion4_Coll(Item_GObj* gobj)
{
    return false;
}

void it_802D1A44(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itLugiaAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
    Vec3 pos;

    Item_80268E5C(gobj, 5, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
    ip->xDD4_itemVar.lugia.xE50.y = 1.0f;
    ip->xDD4_itemVar.lugia.xE50.z = 0.7f;
    ip->xDD4_itemVar.lugia.x88 = 0.4f;
    lb_8000B1CC(ip->xBBC_dynamicBoneTable->bones[25], NULL, &pos);
    ip->xDD4_itemVar.lugia.x8C = ip->xDD4_itemVar.lugia.x64;
    ip->xDD4_itemVar.lugia.x8C.y += attrs->x40;
    ip->xDD4_itemVar.lugia.x70 = pos;
    ip->xDD4_itemVar.lugia.xA4 = 0;
    ip->on_accessory = it_802D1BBC;
    ip->xDCC_flag.b3 = 1;
}

bool itLugia_UnkMotion5_Anim(Item_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Item* ip = GET_ITEM(gobj);

    if (jobj == NULL) {
        jobj = NULL;
    } else {
        jobj = jobj->child;
    }
    it_8027A160(jobj, ip);
    if (!it_80272C6C(gobj)) {
        return true;
    }
    return false;
}

void itLugia_UnkMotion5_Phys(Item_GObj* gobj)
{
    it_8027A344(gobj);
}

bool itLugia_UnkMotion5_Coll(Item_GObj* gobj)
{
    return false;
}

void it_802D1BBC(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    if (ip->xDAC_itcmd_var0 != 0) {
        itLugiaAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
        ip->xDD4_itemVar.lugia.xE50.y += attrs->x20;
        ip->xDD4_itemVar.lugia.xE50.z += attrs->x28;
        ip->xDD4_itemVar.lugia.x88 += attrs->x30;

        if (ip->xDD4_itemVar.lugia.xE50.y >= 1.0) {
            ip->xDD4_itemVar.lugia.xE50.y =
                (ip->xDD4_itemVar.lugia.xE50.y - 1.0);
            it_802D1E8C(gobj, 0xC8, attrs->x1C);
            switch (HSD_Randi(3)) {
            case 0:
                Item_8026AE84(ip, 0x274D, 0x7F, 0x40);
                break;
            case 1:
                Item_8026AE84(ip, 0x274E, 0x7F, 0x40);
                break;
            case 2:
                Item_8026AE84(ip, 0x274F, 0x7F, 0x40);
                break;
            }
        }

        if (ip->xDD4_itemVar.lugia.xE50.z >= 1.0) {
            ip->xDD4_itemVar.lugia.xE50.z =
                (ip->xDD4_itemVar.lugia.xE50.z - 1.0);
            it_802D1E8C(gobj, 0xC9, attrs->x24);
        }

        if (ip->xDD4_itemVar.lugia.x88 >= 1.0) {
            ip->xDD4_itemVar.lugia.x88 = (ip->xDD4_itemVar.lugia.x88 - 1.0);
            it_802D1E8C(gobj, 0xCA, attrs->x2C);
        }
    }
}

void it_802D1D40(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_802762BC(ip);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
    it_80273670(gobj, 0, 0.0f);
}

bool it_802D1DB4(Item_GObj* gobj)
{
    it_80279FF8(gobj);
    return false;
}

void it_802D1DD8(Item_GObj* gobj)
{
    if (it_8027A09C(gobj)) {
        Item* old_ip = GET_ITEM(gobj);
        Item* ip;
        it_80273454(gobj);
        ip = GET_ITEM(gobj);
        Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
        ip->entered_hitlag = efLib_PauseAll;
        ip->exited_hitlag = efLib_ResumeAll;
        old_ip->xDD1_flag.b1 = 1;
    }
}

bool it_802D1E64(Item_GObj* gobj)
{
    return it_8027A118(gobj, (void (*)(HSD_GObj*)) it_802D14D0);
}

Item_GObj* it_802D1E8C(Item_GObj* gobj, ItemKind kind, f32 param)
{
    SpawnItem spawn;
    Item* ip = GET_ITEM(gobj);

    spawn.prev_pos = ip->xDD4_itemVar.lugia.x70;
    it_8026BB88(gobj, &spawn.pos);
    spawn.facing_dir = ip->facing_dir;
    spawn.x3C_damage = 0;
    spawn.vel = it_802D1F64(gobj, param);
    spawn.kind = kind;
    spawn.x0_parent_gobj = ip->owner;
    spawn.x4_parent_gobj2 = gobj;
    spawn.x44_flag.b0 = 1;
    spawn.x40 = 0;
    return Item_80268B18(&spawn);
}

static inline float it_802D208C_inline(f32 x, f32 y, f32 z)
{
    return my_sqrtf(x + y + z);
}

Vec3 it_802D1F64(Item_GObj* gobj, f32 param)
{
    Item* ip = GET_ITEM(gobj);
    Vec3 diff;
    f32 dx, dy, dz, tmp, scale;
    PAD_STACK(4);

    it_802D208C(gobj);
    lbVector_Diff(&ip->xDD4_itemVar.lugia.x8C, &ip->xDD4_itemVar.lugia.x70,
                  &diff);
    dx = ip->xDD4_itemVar.lugia.x8C.x - ip->xDD4_itemVar.lugia.x70.x;
    dy = ip->xDD4_itemVar.lugia.x8C.y - ip->xDD4_itemVar.lugia.x70.y;
    // permuterslop
    dz = (tmp = ip->xDD4_itemVar.lugia.x8C.z) - ip->xDD4_itemVar.lugia.x70.z;
    {
        f32 dx2 = dx * dx;
        f32 dy2 = dy * dy;
        f32 dz2 = dz * dz;
        scale = it_802D208C_inline(dx2, dy2, dz2) / param;
    }
    diff.x /= scale;
    diff.y /= scale;
    diff.z /= scale;
    return diff;
}

void it_802D208C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itLugiaAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
    s32 random_offset, new_angle;
    f32 angle;
    Vec3 target;
    f32 dx, dy, dz;

    while (true) {
        random_offset = HSD_Randi(((attrs->x34 - attrs->x38) / 2));

        if (HSD_Rand() % 2 != 0) {
            new_angle = (random_offset +
                         (ip->xDD4_itemVar.lugia.xA4 - attrs->x34 / 2));
        } else {
            new_angle = (random_offset +
                         (ip->xDD4_itemVar.lugia.xA4 + attrs->x38 / 2));
        }

        target = ip->xDD4_itemVar.lugia.x8C;
        angle = deg_to_rad * new_angle;
        target.x += attrs->x3C * cosf(angle);
        target.y += attrs->x3C * sinf(angle);

        // permuterslop
        dx = dz = ip->xDD4_itemVar.lugia.x64.x - target.x;
        dy = ip->xDD4_itemVar.lugia.x64.y - target.y;
        dz = (dz = ip->xDD4_itemVar.lugia.x64.z) - target.z;
        {
            f32 dx2 = dx * dx;
            f32 dy2 = dy * dy;
            f32 dz2 = dz * dz;
            if (it_802D208C_inline(dx2, dy2, dz2) > attrs->x40) {
                ip->xDD4_itemVar.lugia.xA4 += 180;
            } else {
                break;
            }
        }
    }
    ip->xDD4_itemVar.lugia.x8C = target;
}

void itLugia_Logic39_Spawned(Item_GObj* gobj)
{
    it_8027ADEC(0x465, gobj, HSD_GObjGetHSDObj(gobj), 0.8f);
    it_802D23F4(gobj);
}

void itLugia_Logic40_Spawned(Item_GObj* gobj)
{
    it_8027ADEC(0x466, gobj, HSD_GObjGetHSDObj(gobj), 0.8f);
    it_802D23F4(gobj);
}

void itLugia_Logic41_Spawned(Item_GObj* gobj)
{
    it_8027ADEC(0x467, gobj, HSD_GObjGetHSDObj(gobj), 0.8f);
    it_802D23F4(gobj);
}

void it_802D23D4(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

void it_802D23F4(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itLugiaAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
    ip->xD44_lifeTimer = attrs->x0;
    it_80274740(gobj);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
    it_8026B3A8(gobj);
}

bool it_802D246C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xD44_lifeTimer <= 0.0f) {
        return true;
    }
    ip->xD44_lifeTimer -= 1.0f;
    return false;
}

void it_802D24A0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    f32* attrs = ip->xC4_article_data->x4_specialAttributes;
    f32 multiplier = 0.0f;

    switch (ip->kind) {
    case 0xC8:
        multiplier = attrs[1];
        break;
    case 0xC9:
        multiplier = attrs[2];
        break;
    case 0xCA:
        multiplier = attrs[3];
        break;
    }

    ip->x40_vel.z *= multiplier;
}

bool it_802D24FC(Item_GObj* gobj)
{
    return it_8026DA08(gobj);
}
