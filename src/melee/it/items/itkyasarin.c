#include "itkyasarin.h"

#include "placeholder.h"

#include "gr/grinishie2.h"
#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/itCommonItems.h"
#include "it/item.h"
#include "it/items/itkyasarinegg.h"
#include "MSL/math.h"

#include <baselib/jobj.h>
#include <baselib/random.h>

void itKyasarin_Logic25_Destroyed(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.kyasarin.x20 != NULL) {
        grInishie2_801FD448(ip->xDD4_itemVar.kyasarin.x20);
    }
    ip->xDD4_itemVar.kyasarin.x20 = NULL;
}

void it_802ECD1C(Item_GObj* gobj, Vec3* v)
{
    *v = GET_ITEM(gobj)->pos;
}

HSD_GObj* it_802ECD3C(HSD_GObj* owner, Vec3* pos, f32 facing_dir)
{
    Item_GObj* item_gobj = it_8027B5B0(It_Kind_Kyasarin, pos, NULL, NULL, 1);
    PAD_STACK(84);
    if (item_gobj != NULL) {
        Item* ip = GET_ITEM(item_gobj);
        HSD_JObj* jobj = item_gobj->hsd_obj;
        ip->xDD4_itemVar.kyasarin.x20 = owner;
        ip->xDD4_itemVar.kyasarin.x38 = 0;
        ip->facing_dir = facing_dir;
        ip->xDD4_itemVar.kyasarin.x30 = facing_dir;
        if (ip->facing_dir == 1.0f) {
            HSD_JObjSetRotationY(jobj, (f32) (M_PI * (f64) ip->facing_dir));
        }
        ip->xDCC_flag.b3 = false;
        it_8026B3A8(item_gobj);
        it_802ECEB0(item_gobj);
    }
    return item_gobj;
}

void it_802ECE90(Item_GObj* gobj)
{
    it_8027B730(gobj);
}

void it_802ECEB0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itOldottoseaAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    ip->x40_vel.x = attr->x4 * ip->facing_dir;
    ip->x40_vel.z = 0.0F;
    ip->x40_vel.y = 0.0F;
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
}

bool itKyasarin_UnkMotion0_Anim(Item_GObj* gobj)
{
    if (!it_80272C6C(gobj)) {
        Item* ip = GET_ITEM(gobj);
        itOldottoseaAttributes* attr =
            ip->xC4_article_data->x4_specialAttributes;
        ip->x40_vel.x = attr->x4 * ip->facing_dir;
        ip->x40_vel.z = 0.0F;
        ip->x40_vel.y = 0.0F;
        Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    }
    return false;
}

bool itKyasarin_UnkMotion0_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itKyasarinAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    if (ip->facing_dir == 1.0f) {
        if (ip->pos.x >= attr->x2C) {
            it_802ECFE0(gobj);
        }
    } else {
        if (ip->pos.x <= attr->x28) {
            it_802ECFE0(gobj);
        }
    }
    return false;
}

void it_802ECFE0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itKyasarinAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    it_80273454(gobj);
    ip->xDD4_itemVar.kyasarin.x24 = attr->x8;
}

bool itKyasarin_UnkMotion1_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.kyasarin.x24 = ip->xDD4_itemVar.kyasarin.x24 - 1.0f;
    if (ip->xDD4_itemVar.kyasarin.x24 < 0.0f) {
        it_802ED0D0(gobj);
    }
    return false;
}

bool itKyasarin_UnkMotion3_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.kyasarin.x24 = ip->xDD4_itemVar.kyasarin.x24 - 1.0f;
    if (ip->xDD4_itemVar.kyasarin.x24 < 0.0f) {
        it_802ED25C(gobj);
    }
    return false;
}

void it_802ED0D0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itKyasarinAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    ip->x40_vel.x = -attr->x4 * ip->facing_dir;
    ip->x40_vel.z = 0.0F;
    ip->x40_vel.y = 0.0F;
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
}

bool itKyasarin_UnkMotion2_Anim(Item_GObj* gobj)
{
    if (!it_80272C6C(gobj)) {
        Item* ip = GET_ITEM(gobj);
        itKyasarinAttributes* attr =
            ip->xC4_article_data->x4_specialAttributes;
        ip->x40_vel.x = -attr->x4 * ip->facing_dir;
        ip->x40_vel.z = 0.0F;
        ip->x40_vel.y = 0.0F;
        Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
    }
    return false;
}

bool itKyasarin_UnkMotion2_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itKyasarinAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    if (ip->facing_dir == 1.0F) {
        if (ip->pos.x <= attr->x34) {
            Item_80268E5C(gobj, 3, ITEM_ANIM_UPDATE);
            it_80273454(gobj);
            ip->xDD4_itemVar.kyasarin.x24 = attr->xC;
        }
    } else {
        if (ip->pos.x >= attr->x30) {
            Item_80268E5C(gobj, 3, ITEM_ANIM_UPDATE);
            it_80273454(gobj);
            ip->xDD4_itemVar.kyasarin.x24 = attr->xC;
        }
    }
    return false;
}

void it_802ED25C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itKyasarinAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    ip->x40_vel.x = attr->x4 * ip->facing_dir;
    ip->x40_vel.z = 0.0F;
    ip->x40_vel.y = 0.0F;
    Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE);
}

bool itKyasarin_UnkMotion4_Anim(Item_GObj* gobj)
{
    if (!it_80272C6C(gobj)) {
        Item* ip = GET_ITEM(gobj);
        itKyasarinAttributes* attr =
            ip->xC4_article_data->x4_specialAttributes;
        ip->x40_vel.x = attr->x4 * ip->facing_dir;
        ip->x40_vel.z = 0.0F;
        ip->x40_vel.y = 0.0F;
        Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE);
    }
    return false;
}

static inline void itKyasarin_UnkMotion4_Coll_inline(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itKyasarinAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    ip->xDD4_itemVar.kyasarin.x2C = attr->x10 + HSD_Randi(attr->x14);
    ip->xDD4_itemVar.kyasarin.x28 = attr->x18 + HSD_Randi(attr->x1C);
    it_80273454(gobj);
    if (HSD_Randi(2) != 0) {
        ip->xDD4_itemVar.kyasarin.x34 = attr->x48;
    } else {
        ip->xDD4_itemVar.kyasarin.x34 = 0;
    }
    it_802ED4F8(gobj);
}

bool itKyasarin_UnkMotion4_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itKyasarinAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    PAD_STACK(16);

    if (ip->facing_dir == 1.0f) {
        if (ip->pos.x >= attr->x2C) {
            itKyasarin_UnkMotion4_Coll_inline(gobj);
        }
    } else {
        if (ip->pos.x <= attr->x28) {
            itKyasarin_UnkMotion4_Coll_inline(gobj);
        }
    }
    return false;
}

void it_802ED4F8(HSD_GObj* gobj)
{
    Item_80268E5C(gobj, 6, ITEM_ANIM_UPDATE);
}

/// #itKyasarin_UnkMotion6_Anim

void it_802ED774(HSD_GObj* gobj)
{
    Item_80268E5C(gobj, 7, ITEM_ANIM_UPDATE);
}

bool itKyasarin_UnkMotion7_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    Vec3 spawn_pos;
    PAD_STACK(4);

    if (!it_80272C6C(gobj)) {
        itKyasarinAttributes* attr =
            ip->xC4_article_data->x4_specialAttributes;
        spawn_pos = ip->pos;
        spawn_pos.x += attr->x38 * ip->facing_dir;
        spawn_pos.y += attr->x3C;
        spawn_pos.z = 0;
        it_802EFA44(gobj, &spawn_pos, ip->facing_dir);
        ip->xDD4_itemVar.kyasarin.x34--;
        if (ip->xDD4_itemVar.kyasarin.x34 <= 0) {
            s32 r = HSD_Randi(attr->x1C);
            ip->xDD4_itemVar.kyasarin.x28 = attr->x18 + r;
            Item_80268E5C(gobj, 6, ITEM_ANIM_UPDATE);
        } else {
            Item_80268E5C(gobj, 7, ITEM_ANIM_UPDATE);
        }
    }
    return false;
}

void it_802ED8BC(HSD_GObj* gobj)
{
    Item_80268E5C(gobj, 5, ITEM_ANIM_UPDATE);
}

bool itKyasarin_UnkMotion5_Anim(Item_GObj* gobj)
{
    if (!it_80272C6C(gobj)) {
        Item_80268E5C(gobj, 5, ITEM_ANIM_UPDATE);
    }
    return false;
}

/// #itKyasarin_UnkMotion8_Anim

bool itKyasarin_UnkMotion9_Anim(Item_GObj* gobj)
{
    if (!it_80272C6C(gobj)) {
        Item_80268E5C(gobj, 9, ITEM_ANIM_UPDATE);
    }
    return false;
}

void itKyasarin_UnkMotion9_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->x40_vel.y -= ip->xCC_item_attr->x10_fall_speed;
}

bool itKyasarin_UnkMotion9_Coll(Item_GObj* gobj)
{
    return it_8027C794(gobj);
}

bool itKyasarin_UnkMotion10_Anim(Item_GObj* gobj)
{
    if (!it_80272C6C(gobj)) {
        Item_80268E5C(gobj, 0xA, ITEM_ANIM_UPDATE);
    }
    return false;
}

void itKyasarin_UnkMotion10_Phys(Item_GObj* gobj) {}

bool itKyasarin_UnkMotion10_Coll(Item_GObj* gobj)
{
    return it_8027C79C(gobj);
}

/// #it_802EDDC0

void it_802EE1E0(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
