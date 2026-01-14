#include "itwhispyapple.h"

#include "it/forward.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "lb/lb_00F9.h"
#include "MSL/math.h"

#include <baselib/random.h>

ItemStateTable it_803F91D0[] = {
    {
        1,
        itWhispyapple_UnkMotion0_Anim,
        itWhispyapple_UnkMotion0_Phys,
        itWhispyapple_UnkMotion0_Coll,
    },
    {
        0,
        itWhispyapple_UnkMotion1_Anim,
        itWhispyapple_UnkMotion1_Phys,
        itWhispyapple_UnkMotion1_Coll,
    },
    {
        0,
        itWhispyapple_UnkMotion5_Anim,
        itWhispyapple_UnkMotion5_Phys,
        itWhispyapple_UnkMotion5_Coll,
    },
    {
        0,
        itWhispyapple_UnkMotion3_Anim,
        itWhispyapple_UnkMotion3_Phys,
        NULL,
    },
    {
        1,
        itWhispyapple_UnkMotion5_Anim,
        itWhispyapple_UnkMotion5_Phys,
        itWhispyapple_UnkMotion5_Coll,
    },
    {
        1,
        itWhispyapple_UnkMotion5_Anim,
        itWhispyapple_UnkMotion5_Phys,
        itWhispyapple_UnkMotion5_Coll,
    },
    {
        0,
        itWhispyapple_UnkMotion6_Anim,
        itWhispyapple_UnkMotion6_Phys,
        itWhispyapple_UnkMotion6_Coll,
    },
    {
        2,
        itWhispyapple_UnkMotion7_Anim,
        itWhispyapple_UnkMotion7_Phys,
        itWhispyapple_UnkMotion7_Coll,
    },
};

static s32 it_803F9250[4] = { 0x68FB4, 0x68FB5, 0x68FB6, 0 };

static bool itWhispyapple_UnkMotion0_Anim_inline(Item_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* child = HSD_JObjGetChild(jobj);
    ip->xD44_lifeTimer -= 1.0f;
    if (ip->msid == 7) {
        HSD_JObjSetFlagsAll(child, 0x10);
    } else if ((ip->xD44_lifeTimer <= it_804D6D28->x34) ||
               (ABS(ip->pos.z) > 1))
    {
        it_802728C8(gobj);
    } else {
        HSD_JObjClearFlagsAll(child, 0x10);
    }
    if (ip->xD44_lifeTimer <= 0.0f) {
        return true;
    }
    return false;
}

Item_GObj* it_802EE200(HSD_GObj* parent, Vec3* pos, f32 threshold1,
                       f32 threshold2)
{
    SpawnItem spawn;
    Item_GObj* gobj;
    Item* ip;
    f32 rand = HSD_Randf();
    f32 facing_dir;
    PAD_STACK(4);

    spawn.pos = *pos;
    spawn.prev_pos = spawn.pos;
    if (HSD_Randi(2) != 0) {
        facing_dir = 1.0f;
    } else {
        facing_dir = -1.0f;
    }
    spawn.facing_dir = facing_dir;
    spawn.x3C_damage = 0;
    spawn.vel.z = 0.0f;
    spawn.vel.y = 0.0f;
    spawn.vel.x = 0.0f;
    spawn.x0_parent_gobj = NULL;
    spawn.x44_flag.b0 = 0;
    spawn.x40 = 0;
    if (it_8026D3CC() == false) {
        rand -= threshold2;
        if (rand < 0.0f) {
            rand = 0.0f;
        }
        threshold2 = 0.0f;
        spawn.kind = It_Kind_WhispyApple;
    } else if (rand < threshold2) {
        spawn.kind = It_Kind_WhispyHealApple;
    } else {
        spawn.kind = It_Kind_WhispyApple;
    }
    gobj = Item_80268B18(&spawn);
    if (gobj != NULL) {
        ip = gobj->user_data;
        it_80274ED8();
        it_802EE374(gobj);
        if (rand < (threshold1 + threshold2)) {
            ip->xDD4_itemVar.whispyapple.xDD8 = 0;
        } else {
            ip->xDD4_itemVar.whispyapple.xDD8 = 1;
            it_8026B3A8(gobj);
        }
        it_802750F8(gobj);
    }
    return gobj;
}

void it_802EE374(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itWhispyAppleAttributes* attrs =
        ip->xC4_article_data->x4_specialAttributes;
    f32 rand;

    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    it_80275158(gobj, (f32) attrs->x8);
    ip->xDD4_itemVar.whispyapple.xDD4_heal = attrs->x4;
    rand = HSD_Randf();
    ip->x40_vel.x = 2.0f * attrs->x18 * rand - attrs->x18;
    ip->x40_vel.y = attrs->x14;
    ip->x40_vel.z = ABS(ip->pos.z / 20.0f);
}

bool itWhispyapple_UnkMotion0_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.whispyapple.xDD8 == 1) {
        it_8026B3A8(gobj);
    }
    return itWhispyapple_UnkMotion0_Anim_inline(gobj);
}

void itWhispyapple_UnkMotion0_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    PAD_STACK(8);

    if (ip->xDD4_itemVar.whispyapple.xDD8 == 1) {
        it_8026B3A8(gobj);
    }
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

static inline void itWhispyapple_UnkMotion0_Coll_inline(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    s32 coll = it_8026DAA8(gobj);
    if (coll & 0xF) {
        Item_8026AE84(ip, it_803F9250[HSD_Randi(3)], 0x7F, 0x40);
        it_80276FC4(gobj, coll);
        if ((coll & 1) && it_8026DBC8(gobj)) {
            it_802EE6A0(gobj);
        }
    }
}

bool itWhispyapple_UnkMotion0_Coll(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    PAD_STACK(8);

    if (ip->xDD4_itemVar.whispyapple.xDD8 == 1) {
        it_8026B3A8(gobj);
    }
    if (ip->pos.z >= 0.0f) {
        ip->pos.z = 0.0f;
        ip->x40_vel.z = 0.0f;
        if (ip->xDD4_itemVar.whispyapple.xDD8 == 1) {
            it_8026E15C(gobj, it_802EED00);
        } else {
            itWhispyapple_UnkMotion0_Coll_inline(gobj);
        }
    }
    return false;
}

void it_802EE6A0(Item_GObj* gobj)
{
    Item* ip;
    f32 val;

    ip = GET_ITEM(gobj);
    val = 0;
    ip->x40_vel.x = val;
    ip->x40_vel.y = val;
    ip->x40_vel.z = val;
    Item_80268E5C((HSD_GObj*) gobj, 1, ITEM_ANIM_UPDATE);
}

bool itWhispyapple_UnkMotion1_Anim(Item_GObj* gobj)
{
    return itWhispyapple_UnkMotion0_Anim_inline(gobj);
}

void itWhispyapple_UnkMotion1_Phys(Item_GObj* gobj) {}

bool itWhispyapple_UnkMotion1_Coll(Item_GObj* gobj)
{
    it_8026D62C(gobj, fn_802EE7FC);
    return false;
}

void fn_802EE7FC(HSD_GObj* gobj)
{
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
}

bool itWhispyapple_UnkMotion5_Anim(Item_GObj* gobj)
{
    return itWhispyapple_UnkMotion0_Anim_inline(gobj);
}

void itWhispyapple_UnkMotion5_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itWhispyapple_UnkMotion5_Coll(Item_GObj* gobj)
{
    s32 coll;
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(20);

    coll = it_8026DAA8(gobj);
    if (coll & 0xF) {
        Item_8026AE84(ip, it_803F9250[HSD_Randi(3)], 0x7F, 0x40);
        it_80276FC4(gobj, coll);
        if ((coll & 1) && it_8026DBC8(gobj)) {
            it_802EE6A0(gobj);
        }
    }
    return false;
}

void it_802EEA08(Item_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    HSD_JObj* child = HSD_JObjGetChild(jobj);
    HSD_JObjClearFlagsAll(child, 0x10);
    Item_80268E5C(gobj, 3, ITEM_ANIM_UPDATE);
}

bool itWhispyapple_UnkMotion3_Anim(Item_GObj* gobj)
{
    return false;
}

void itWhispyapple_UnkMotion3_Phys(Item_GObj* gobj) {}

void it_802EEA70(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    HSD_JObj* child = HSD_JObjGetChild(jobj);
    Vec3 vec = { 0, 0, 0 };

    it_8026B390(gobj);
    HSD_JObjClearFlagsAll(child, 0x10);
    Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE);
    ip->x40_vel.z = 0.0f;
    ip->x40_vel.y = 0.0f;
    ip->pos.z = 0.0f;
    it_8027429C(gobj, &vec);
}

void it_802EEB28(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    HSD_JObj* child = HSD_JObjGetChild(jobj);
    PAD_STACK(8);

    it_8026B390(gobj);
    HSD_JObjClearFlagsAll(child, 0x10);
    Item_80268E5C(gobj, 5, ITEM_ANIM_UPDATE);
    ip->x40_vel.z = 0.0f;
    ip->pos.z = 0.0f;
}

void it_2725_Logic18_EnteredAir(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 6, ITEM_ANIM_UPDATE);
}

bool itWhispyapple_UnkMotion6_Anim(Item_GObj* gobj)
{
    return itWhispyapple_UnkMotion0_Anim_inline(gobj);
}

void itWhispyapple_UnkMotion6_Phys(Item_GObj* gobj) {}

bool itWhispyapple_UnkMotion6_Coll(Item_GObj* gobj)
{
    it_8026E8C4(gobj, it_802EE6A0, fn_802EE7FC);
    return false;
}

void it_802EED00(Item_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Item* ip = GET_ITEM(gobj);
    Vec3 pos;

    it_8026B3A8(gobj);
    HSD_JObjSetFlagsAll(jobj, 0x10);
    it_8026BD24(gobj);
    it_80275158(gobj, 20.0f);
    it_8026BDB4(gobj);
    ip->x40_vel.z = 0.0f;
    ip->x40_vel.y = 0.0f;
    ip->x40_vel.x = 0.0f;
    it_80272C08(gobj);
    it_802756D0(gobj);
    it_80275444(gobj);
    pos = ip->pos;
    lb_800119DC(&pos, 0x78, 1.0f, 0.02f, 1.0471976f);
    Item_80268E5C(gobj, 7, 0x12);
}

bool itWhispyapple_UnkMotion7_Anim(Item_GObj* gobj)
{
    return itWhispyapple_UnkMotion0_Anim_inline(gobj);
}

void itWhispyapple_UnkMotion7_Phys(Item_GObj* gobj) {}

bool itWhispyapple_UnkMotion7_Coll(Item_GObj* item_gobj)
{
    return false;
}

bool it_802EEED0(Item_GObj* item_gobj)
{
    return true;
}

bool it_802EEED8(Item_GObj* gobj)
{
    it_802725D4(gobj);
    itColl_BounceOffVictim(gobj);
    return false;
}

bool it_802EEF10(Item_GObj* gobj)
{
    return it_80273030(gobj);
}

bool it_802EEF30(Item_GObj* gobj)
{
    it_802725D4(gobj);
    itColl_BounceOffVictim(gobj);
    return false;
}

bool it_802EEF68(Item_GObj* gobj)
{
    return itColl_BounceOffShield(gobj);
}

void it_802EEF88(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
