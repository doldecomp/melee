#include "itchicorita.h"

#include "it/forward.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/itCommonItems.h"
#include "it/item.h"

ItemStateTable it_803F7A98[] = {
    { 0, itChicorita_UnkMotion0_Anim, itChicorita_UnkMotion0_Phys,
      itChicorita_UnkMotion0_Coll },
    { 1, itChicorita_UnkMotion1_Anim, itChicorita_UnkMotion1_Phys,
      itChicorita_UnkMotion1_Coll },
    { -1, itChicorita_UnkMotion2_Anim, itChicorita_UnkMotion2_Phys,
      itChicorita_UnkMotion2_Coll },
};

ItemStateTable it_803F7AC8[] = {
    { 0, itChicoritaleaf_UnkMotion0_Anim, itChicoritaleaf_UnkMotion0_Phys,
      itChicoritaleaf_UnkMotion0_Coll },
};

void it_802C9588(Item_GObj* item_gobj)
{
    Article* article;
    Item* item;
    itChicoritaAttr* attr;
    PAD_STACK(12);

    item = GET_ITEM((HSD_GObj*) item_gobj);
    article = item->xC4_article_data;
    attr = article->x4_specialAttributes;
    it_80279C48(item_gobj, article);
    item->xDD4_itemVar.chicorita.x60 = -1;
    item->xDBC_itcmd_var4.flags.x0 = false;
    it_80279CDC(item_gobj, attr->scale);
    item->xDD4_itemVar.chicorita.x64 = 0.0f;
    it_802C9A74(item_gobj);
    Item_8026AE84(item, 0x2711, 0x7F, 0x40);
}

void it_802C9618(HSD_GObj* item_gobj) {}

void itChicorita_Logic1_EvtUnk(Item_GObj* item_gobj, HSD_GObj* ref_gobj)
{
    it_8026B894(item_gobj, ref_gobj);
}

void it_802C963C(HSD_GObj* item_gobj)
{
    PAD_STACK(8);

    it_80273454((Item_GObj*) item_gobj);
    it_802C9670((Item_GObj*) item_gobj);
}

void it_802C9670(Item_GObj* item_gobj)
{
    Item* item;
    Article* article;
    itChicoritaAttr* attr;

    item = item_gobj->user_data;
    article = item->xC4_article_data;
    attr = article->x4_specialAttributes;
    if (item->xDD4_itemVar.chicorita.x60 == -1) {
        item->xDD4_itemVar.chicorita.x60 = attr->x4;
    }
    Item_80268E5C((HSD_GObj*) item_gobj, 0, ITEM_ANIM_UPDATE);
    item->on_accessory = it_802C989C;
}

bool itChicorita_UnkMotion0_Anim(HSD_GObj* item_gobj)
{
    HSD_JObj* item_jobj;
    Item* item;
    Article* article;
    itChicoritaAttr* attr;

    item_jobj = GET_JOBJ((HSD_GObj*) item_gobj);
    item = GET_ITEM((HSD_GObj*) item_gobj);
    if (item_jobj == NULL) {
        item_jobj = NULL;
    } else {
        item_jobj = item_jobj->child;
    }
    it_8027A160(item_jobj, item);
    if (it_80272C6C((Item_GObj*) item_gobj) == 0) {
        if (item->xDD4_itemVar.chicorita.x60 <= 0) {
            item->xDD4_itemVar.chicorita.x60 = 0;
            it_802C98E4((Item_GObj*) item_gobj);
        } else {
            item->xDD4_itemVar.chicorita.x60--;
            item = item_gobj->user_data;
            article = item->xC4_article_data;
            attr = article->x4_specialAttributes;
            if (item->xDD4_itemVar.chicorita.x60 == -1)
            { // This check will never succeed?
                item->xDD4_itemVar.chicorita.x60 = attr->x4;
            }
            Item_80268E5C(item_gobj, 0, ITEM_ANIM_UPDATE);
            item->on_accessory = it_802C989C;
        }
    }
    return false;
}

void itChicorita_UnkMotion0_Phys(HSD_GObj* item_gobj)
{
    Item* item;
    ItemAttr* attr;
    f32 fall_speed;
    s32 fall_speed_dir;
    f32 item_vel_y;
    s32 item_vel_y_dir;

    item = item_gobj->user_data;
    it_8027A344((Item_GObj*) item_gobj);
    if (item->ground_or_air == GA_Air) {
        attr = item->xCC_item_attr;
        fall_speed = attr->x10_fall_speed;
        if (fall_speed < 0.0f) {
            fall_speed_dir = -1;
        } else {
            fall_speed_dir = 1;
        }
        item_vel_y = item->xDD4_itemVar.chicorita.x64;
        if (item_vel_y < 0.0f) {
            item_vel_y_dir = -1;
        } else {
            item_vel_y_dir = 1;
        }
        if (item_vel_y_dir != fall_speed_dir) {
            if (item_vel_y < 0.0f) {
                item_vel_y = -item_vel_y;
            }
            if (item_vel_y < attr->x14_fall_speed_max) {
                goto block_11;
            }
        } else {
        block_11:
            item->xDD4_itemVar.chicorita.x64 -= fall_speed;
        }
        item->x40_vel.y = item->xDD4_itemVar.chicorita.x64;
        return;
    }
    item->xDD4_itemVar.chicorita.x64 = 0.0f;
}

bool itChicorita_UnkMotion0_Coll(HSD_GObj* item_gobj)
{
    if (((Item*) item_gobj->user_data)->ground_or_air == GA_Air) {
        it_8026E15C((Item_GObj*) item_gobj, it_802C9618);
    } else {
        it_8026D62C((Item_GObj*) item_gobj, it_802C9618);
    }
    return false;
}

void it_802C989C(HSD_GObj* item_gobj)
{
    Item* item = item_gobj->user_data;
    if (item->xDBC_itcmd_var4.flags.x0) {
        it_802C9B20((Item_GObj*) item_gobj);
        item->xDBC_itcmd_var4.flags.x0 = false;
    }
}

void it_802C98E4(Item_GObj* item_gobj)
{
    Item_80268E5C((HSD_GObj*) item_gobj, 1, ITEM_ANIM_UPDATE);
}

bool itChicorita_UnkMotion1_Anim(HSD_GObj* item_gobj)
{
    HSD_JObj* item_jobj;
    Item* item;

    item_jobj = GET_JOBJ((HSD_GObj*) item_gobj);
    item = GET_ITEM((HSD_GObj*) item_gobj);
    if (item_jobj == NULL) {
        item_jobj = NULL;
    } else {
        item_jobj = item_jobj->child;
    }
    it_8027A160(item_jobj, item);
    if (!it_80272C6C((Item_GObj*) item_gobj)) {
        return true;
    }
    return false;
}

void itChicorita_UnkMotion1_Phys(HSD_GObj* item_gobj)
{
    Item* item;
    ItemAttr* attr;
    f32 fall_speed;
    s32 fall_speed_dir;
    f32 item_vel_y;
    s32 item_vel_y_dir;

    item = item_gobj->user_data;
    it_8027A344((Item_GObj*) item_gobj);
    if (item->ground_or_air == GA_Air) {
        attr = item->xCC_item_attr;
        fall_speed = attr->x10_fall_speed;
        if (fall_speed < 0.0f) {
            fall_speed_dir = -1;
        } else {
            fall_speed_dir = 1;
        }
        item_vel_y = item->xDD4_itemVar.chicorita.x64;
        if (item_vel_y < 0.0f) {
            item_vel_y_dir = -1;
        } else {
            item_vel_y_dir = 1;
        }
        if (item_vel_y_dir != fall_speed_dir) {
            if (item_vel_y < 0.0f) {
                item_vel_y = -item_vel_y;
            }
            if (item_vel_y < attr->x14_fall_speed_max) {
                goto block_11;
            }
        } else {
        block_11:
            item->xDD4_itemVar.chicorita.x64 -= fall_speed;
        }
        item->x40_vel.y = item->xDD4_itemVar.chicorita.x64;
        return;
    }
    item->xDD4_itemVar.chicorita.x64 = 0.0f;
}

bool itChicorita_UnkMotion1_Coll(HSD_GObj* item_gobj)
{
    if (((Item*) item_gobj->user_data)->ground_or_air == GA_Air) {
        it_8026E15C((Item_GObj*) item_gobj, it_802C9618);
    } else {
        it_8026D62C((Item_GObj*) item_gobj, it_802C9618);
    }
    return false;
}

void it_802C9A74(Item_GObj* item_gobj)
{
    it_802762BC(item_gobj->user_data);
    Item_80268E5C((HSD_GObj*) item_gobj, 2, ITEM_ANIM_UPDATE);
}

bool itChicorita_UnkMotion2_Anim(HSD_GObj* item_gobj)
{
    it_80279FF8((Item_GObj*) item_gobj);
    return false;
}

void itChicorita_UnkMotion2_Phys(HSD_GObj* item_gobj)
{
    it_8027A09C((Item_GObj*) item_gobj);
}

bool itChicorita_UnkMotion2_Coll(HSD_GObj* item_gobj)
{
    return it_8027A118((Item_GObj*) item_gobj, it_802C963C);
}

void it_802C9B20(Item_GObj* chicorita_gobj)
{
    SpawnItem spawn;
    Item* chicorita;
    itChicoritaLeafAttr* attr;

    chicorita = GET_ITEM((HSD_GObj*) chicorita_gobj);
    attr = chicorita->xC4_article_data->x4_specialAttributes;
    spawn.prev_pos = chicorita->pos;
    spawn.prev_pos.x += attr->x8 * chicorita->facing_dir;
    spawn.prev_pos.y += attr->xC;
    it_8026BB88(chicorita_gobj, &spawn.pos);
    spawn.facing_dir = chicorita->facing_dir;
    spawn.x3C_damage = 0;
    spawn.vel.x = attr->x10 * chicorita->facing_dir;
    spawn.vel.z = spawn.vel.y = 0.0f;
    spawn.x40 = 0;
    spawn.kind = Pokemon_Chicorita_Leaf;
    spawn.x0_parent_gobj = chicorita->owner;
    spawn.x4_parent_gobj2 = (HSD_GObj*) chicorita_gobj;
    spawn.x44_flag.b0 = 1;
    if (Item_80268B18(&spawn)) {
        Item_8026AE84(chicorita, 0x2710, 0x7F, 0x40);
    }
}

void itChicoritaLeaf_Logic30_Spawned(Item_GObj* item_gobj)
{
    Item* item;
    PAD_STACK(12);

    item = GET_ITEM((HSD_GObj*) item_gobj);
    item->xD44_lifeTimer =
        ((itChicoritaLeafAttr*) item->xC4_article_data->x4_specialAttributes)
            ->timer;
    it_80274740(item_gobj);
    it_802C9CC0(item_gobj);
    it_8026B3A8(item_gobj);
    it_80274C60(item_gobj);
}

bool itChicoritaLeaf_Logic30_HitShield(Item_GObj* item_gobj)
{
    return false;
}

void itChicoritaLeaf_Logic30_EvtUnk(Item_GObj* item_gobj, HSD_GObj* ref_gobj)
{
    it_8026B894(item_gobj, ref_gobj);
}

bool itChicoritaLeaf_Logic30_Reflected(Item_GObj* item_gobj)
{
    return it_80273030(item_gobj);
}

void it_802C9CC0(Item_GObj* item_gobj)
{
    Item_80268E5C((HSD_GObj*) item_gobj, 0, ITEM_ANIM_UPDATE);
}

bool itChicoritaleaf_UnkMotion0_Anim(HSD_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    if (item->xD44_lifeTimer <= 0.0f) {
        return true;
    }
    item->xD44_lifeTimer--;
    return false;
}

void itChicoritaleaf_UnkMotion0_Phys(HSD_GObj* item_gobj) {}

bool itChicoritaleaf_UnkMotion0_Coll(HSD_GObj* item_gobj)
{
    return it_8026DFB0((Item_GObj*) item_gobj);
}
