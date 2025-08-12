#include "itchicorita.h"

#include "it/forward.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/itCommonItems.h"
#include "it/item.h"
#include "it/items/itchicoritaleaf.h"

ItemStateTable it_803F7A98[] = {
    { 0, itChicorita_UnkMotion0_Anim, itChicorita_UnkMotion0_Phys,
      itChicorita_UnkMotion0_Coll },
    { 1, itChicorita_UnkMotion1_Anim, itChicorita_UnkMotion1_Phys,
      itChicorita_UnkMotion1_Coll },
    { -1, itChicorita_UnkMotion2_Anim, itChicorita_UnkMotion2_Phys,
      itChicorita_UnkMotion2_Coll },
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
    // item->xDBC_itcmd_var4 &= ~0x80;
    ((flag32*) item->xDBC_itcmd_var4)->flags.x0 = 0;
    it_80279CDC(item_gobj, attr->scale);
    item->xDD4_itemVar.chicorita.x64 = 0.0f;
    it_802C9A74(item_gobj);
    Item_8026AE84(item, 0x2711, 0x7F, 0x40);
}

void it_802C9618(HSD_GObj* item_gobj) {}

void it_2725_Logic1_EvtUnk(Item_GObj* item_gobj, HSD_GObj* ref_gobj)
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
    Item* item;

    item = item_gobj->user_data;
    // if (((u8) item->xDBC_itcmd_var4 >> 7U) & 1) {
    // if ((((UnkFlagStruct*) item->xDBC_itcmd_var4)->u8 >> 7U) & 1) {
    if (((flag32*) item->xDBC_itcmd_var4)->flags.x0) {
        it_802C9B20((Item_GObj*) item_gobj);
        // item->xDBC_itcmd_var4 &= ~0x80;
        ((flag32*) item->xDBC_itcmd_var4)->flags.x0 = 0;
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
