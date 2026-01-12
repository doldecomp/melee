#include "itlucky.h"

#include "m2c_macros.h"

#include <placeholder.h>
#include <platform.h>

#include "ef/eflib.h"

#include "it/forward.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/itCommonItems.h"
#include "it/item.h"
#include "it/items/itegg.h"
#include "lb/lb_00B0.h"
#include "sysdolphin/baselib/random.h"

ItemStateTable it_803F8190[] = {
    {
        -1,
        it_802D55DC,
        it_802D5600,
        it_802D5620,
    },
    {
        -1,
        itLucky_UnkMotion5_Anim,
        itLucky_UnkMotion5_Phys,
        itLucky_UnkMotion5_Coll,
    },
    {
        1,
        it_802D53AC,
        it_802D53F0,
        it_802D53F4,
    },
    {
        2,
        it_802D53AC,
        it_802D53F0,
        it_802D53F4,
    },
    {
        3,
        it_802D53AC,
        it_802D53F0,
        it_802D53F4,
    },
    {
        0,
        itLucky_UnkMotion5_Anim,
        itLucky_UnkMotion5_Phys,
        itLucky_UnkMotion5_Coll,
    },
    {
        -1,
        itLucky_UnkMotion6_Anim,
        itLucky_UnkMotion6_Phys,
        NULL,
    },
};

ItemStateTable it_803F8200[] = {
    {
        -1,
        it_802D5884,
        it_802D58BC,
        it_802D58C0,
    },
    {
        -1,
        itLucky_UnkMotion3_Anim,
        itLucky_UnkMotion3_Phys,
        itLucky_UnkMotion3_Coll,
    },
    {
        -1,
        itLucky_UnkMotion2_Anim,
        itLucky_UnkMotion2_Phys,
        NULL,
    },
    {
        -1,
        itLucky_UnkMotion3_Anim,
        itLucky_UnkMotion3_Phys,
        itLucky_UnkMotion3_Coll,
    },
    {
        -1,
        it_802D5A2C,
        it_802D5A64,
        it_802D5A68,
    },
};

void it_802D5050(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itLuckyAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    PAD_STACK(4);
    ip->facing_dir = 0.0f;
    ip->xDD4_itemVar.lucky.x60 = 2;
    ip->xDD4_itemVar.lucky.x64 = attr->x10 + HSD_Randi(attr->x14);
    it_80279CDC(gobj, attr->x0);
    ip->xDD4_itemVar.lucky.x68 = it_8026D3CC();
    Item_8026AE84(ip, 0x273B, 0x7F, 0x40);
    ip->xDAC_itcmd_var0 = 0;
    it_802D5560(gobj);
}

void it_802D50F0(Item_GObj* gobj)
{
    it_80273454(gobj);
    it_802D533C(gobj);
}

bool it_802D5124(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    bool result = false;
    switch (ip->xDD4_itemVar.lucky.x60) {
    case 2:
        ip->xDD4_itemVar.lucky.x60 = 3;
        break;
    case 3:
        ip->xDD4_itemVar.lucky.x64 -= 1;
        if (ip->xDD4_itemVar.lucky.x64 != 0) {
            ip->xDD4_itemVar.lucky.x60 = 3;
        } else {
            ip->xDD4_itemVar.lucky.x60 = 4;
        }
        break;
    case 4:
        result = true;
        break;
    }
    if (result == false) {
        it_802D533C(gobj);
    }
    return result;
}

void it_802D51C8(HSD_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itLuckyAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    Vec3 vel, pos;
    Item_GObj* spawned;
    f32 facing;
    s32 randi = 0;
    PAD_STACK(4);

    vel.x = attr->x4 * (2.0f * (HSD_Randf() - 0.5f));
    vel.y = attr->x8;
    vel.z = 0.0f;
    facing = (vel.x >= 0.0f) ? 1.0f : -1.0f;
    lb_8000B1CC(ip->xBBC_dynamicBoneTable->bones[32], NULL, &pos);
    pos.z = 0.0f;
    if (ip->xDD4_itemVar.lucky.x68 != 0) {
        randi = HSD_Randi(attr->x18);
    }
    if (randi != 0) {
        spawned = it_802D5710(gobj, &pos, &vel, facing);
    } else {
        spawned = it_80288C88(gobj, &pos, &vel, facing);
    }
    if (spawned != NULL) {
        it_80274ED8();
    }
}

void it_802D52E4(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDAC_itcmd_var0 != 0) {
        it_802D51C8(gobj);
        Item_8026AE84(ip, 0x273C, 0x7F, 0x40);
        ip->xDAC_itcmd_var0 = 0;
    }
}

static inline void it_802D533C_inline(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDAC_itcmd_var0 = 0;
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
}

void it_802D533C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    Item_80268E5C(gobj, ip->xDD4_itemVar.lucky.x60, ITEM_ANIM_UPDATE);
    it_802D533C_inline(gobj);
    ip->on_accessory = it_802D52E4;
}

bool it_802D53AC(Item_GObj* gobj)
{
    Item* _ip = GET_ITEM(gobj); // NOTE: unused
    if (!it_80272C6C(gobj)) {
        return it_802D5124(gobj);
    }
    return false;
}

void it_802D53F0(Item_GObj* gobj) {}

bool it_802D53F4(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_802D546C);
    return false;
}

void it_802D5420(HSD_GObj* gobj)
{
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    it_802756E0(gobj);
    it_802754D4(gobj);
    it_802754BC(gobj);
}

static inline void it_802D546C_inline(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDAC_itcmd_var0 = 0;
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
}

void it_802D546C(Item_GObj* gobj)
{
    Item* _ip = GET_ITEM(gobj); // NOTE: unused
    Item_80268E5C(gobj, 5, ITEM_UNK_0x1);
    it_802D546C_inline(gobj);
}

bool itLucky_UnkMotion5_Anim(Item_GObj* gobj)
{
    return false;
}

void itLucky_UnkMotion5_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itLucky_UnkMotion5_Coll(Item_GObj* gobj)
{
    it_8026E15C(gobj, it_802D50F0);
    return false;
}

bool itLucky_UnkMotion6_Anim(Item_GObj* gobj)
{
    return false;
}

void itLucky_UnkMotion6_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

void it_802D5560(HSD_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_802762BC(ip);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
    it_80273670(gobj, 0, 0.0f);
    it_8026BDB4(gobj);
}

bool it_802D55DC(Item_GObj* gobj)
{
    it_80279FF8(gobj);
    return false;
}

void it_802D5600(Item_GObj* gobj)
{
    it_8027A09C(gobj);
}

bool it_802D5620(Item_GObj* gobj)
{
    return it_8027A118(gobj, it_802D5420);
}

static inline void it_802D5648_inline(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->facing_dir = 0.0f;
    it_802762BC(ip);
    it_802756D0(gobj);
    Item_80268E5C(gobj, 6, ITEM_ANIM_UPDATE);
    it_80273670(gobj, 0, 0.0f);
}

bool it_802D5648(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itLuckyAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
    if (ip->xC9C >= attrs->xC) {
        it_80279D38(gobj);
        it_802D5648_inline(gobj);
    }
    return false;
}

void it_802D56F0(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

static inline Item_GObj* it_802D5710_inline(Item_GObj* gobj, Vec3* pos,
                                            Vec3* vel, f32 facing)
{
    Item* ip = gobj->user_data;
    SpawnItem spawn;
    spawn.kind = Pokemon_Lucky_Egg;
    spawn.prev_pos = *pos;
    spawn.prev_pos.z = 0.0f;
    spawn.pos = spawn.prev_pos;
    spawn.facing_dir = facing;
    spawn.x3C_damage = 0;
    spawn.vel = *vel;
    spawn.x0_parent_gobj = ip->owner;
    spawn.x4_parent_gobj2 = gobj;
    spawn.x44_flag.b0 = true;
    spawn.x40 = 0;
    return Item_80268B18(&spawn);
}

Item_GObj* it_802D5710(Item_GObj* gobj, Vec3* pos, Vec3* vel, f32 facing)
{
    Item_GObj* result = NULL;
    if (gobj != NULL) {
        result = it_802D5710_inline(gobj, pos, vel, facing);
    }
    return result;
}

void it_2725_Logic44_Spawned(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itLuckyAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    PAD_STACK(4);
    it_80275158(gobj, attr->x0);
    ip->xDD4_itemVar.lucky.x60 = M2C_FIELD(attr, s32*, 4); // TODO
    it_802D58EC(gobj);
}

void it_802D582C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(12);
    it_8026B390(gobj);
    ip->x40_vel.x = ip->x40_vel.y = ip->x40_vel.z = 0.0f;
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
}

bool it_802D5884(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xD44_lifeTimer -= 1.0f;
    if (ip->xD44_lifeTimer <= 0.0f) {
        return true;
    }
    return false;
}

void it_802D58BC(Item_GObj* gobj) {}

bool it_802D58C0(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_802D58EC);
    return false;
}

void it_802D58EC(HSD_GObj* gobj)
{
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
}

bool itLucky_UnkMotion3_Anim(Item_GObj* gobj)
{
    return it_802D5884(gobj);
}

void itLucky_UnkMotion3_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itLucky_UnkMotion3_Coll(Item_GObj* gobj)
{
    it_8026E15C(gobj, it_802D582C);
    return false;
}

void it_2725_Logic44_PickedUp(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
}

bool itLucky_UnkMotion2_Anim(Item_GObj* gobj)
{
    return false;
}

void itLucky_UnkMotion2_Phys(Item_GObj* gobj) {}

void it_2725_Logic44_Dropped(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 3, ITEM_ANIM_UPDATE);
}

void it_2725_Logic44_EnteredAir(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE);
}

bool it_802D5A2C(Item_GObj* gobj)
{
    return it_802D5884(gobj);
}

void it_802D5A64(Item_GObj* gobj) {}

bool it_802D5A68(Item_GObj* gobj)
{
    it_8026E8C4(gobj, it_802D582C, it_802D58EC);
    return false;
}

void it_2725_Logic44_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
