#include "it/items/itheiho.h"

#include "gr/stage.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/items/itfoods.h"
#include "it/items/itfreeze.h"
#include "it/items/types.h"
#include "MSL/math.h"

#include <baselib/dobj.h>
#include <baselib/gobj.h>
#include <baselib/random.h>

/* 2D8894 */ static void it_802D8894(Item_GObj*);
/* 2D88CC */ static int it_802D88CC(Item_GObj*);
/* 2D88D4 */ static void it_802D88D4(Item_GObj*);
/* 2D8910 */ static int it_802D8910(Item_GObj*);
/* 2D8918 */ static void it_802D8918(Item_GObj*);
/* 2D8984 */ static int it_802D8984(Item_GObj*);
/* 2D8A54 */ static void it_802D8A54(Item_GObj*);
/* 2D8CC8 */ static int it_802D8CC8(Item_GObj*);
/* 2D8DB4 */ static int it_802D8DB4(Item_GObj*);
/* 2D8DBC */ static void it_802D8DBC(Item_GObj*);
/* 2D8E44 */ static int it_802D8E44(Item_GObj*);
/* 2D8E4C */ static int it_802D8E4C(Item_GObj*);
/* 2D8E54 */ static void it_802D8E54(Item_GObj*);
/* 2D8EA4 */ static int it_802D8EA4(Item_GObj*);
/* 2D9168 */ static void it_802D9168(Item_GObj*);
/* 2D9274 */ static int it_802D9274(Item_GObj*);
/* 2D9384 */ static void it_802D9384(Item_GObj*);
/* 2D95F4 */ static int it_802D95F4(Item_GObj*);
/* 2D96B0 */ static void it_802D96B0(HSD_GObj* gobj);
/* 2D9714 */ static void it_802D9714(Item_GObj*);
/* 2D98AC */ static void it_802D98AC(Item_GObj*);
/* 2D98C4 */ static void it_802D98C4(HSD_JObj*, Item*);

ItemStateTable it_803F83F0[] = { { -1, it_802D88CC, it_802D88D4, it_802D8910 },
                                 { 0, it_802D8984, it_802D8A54, it_802D8CC8 },
                                 { -1, it_802D8DB4, it_802D8DBC, it_802D8E44 },
                                 { -1, it_802D8E4C, it_802D8E54, it_802D8EA4 },
                                 { 2, it_802D9274, it_802D9384,
                                   it_802D95F4 } };

void it_802D8618(s32 arg0, Vec3* arg1, s32 arg2, s32 arg3)
{
    Item_GObj* gobj = it_8027B5B0(0xD2, arg1, NULL, NULL, 1);
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.heiho.x20 = (s8) arg0;
    ip->xDD4_itemVar.heiho.x21 = (s8) arg2;
    ip->xDD4_itemVar.heiho.x24 = arg3;
    it_802D8894(gobj);
}

void it_802D8688(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(4);
    it_8027B730(gobj);
    ip->xD5C = 0;
    ip->xDCC_flag.b3 = 0;
    ip->xDD4_itemVar.heiho.x54 = it_8028FAF4(NULL, &ip->pos);
    if (ip->xDD4_itemVar.heiho.x54 != NULL) {
        it_8028F968(ip->xDD4_itemVar.heiho.x54);
        it_8028F9D8(ip->xDD4_itemVar.heiho.x54, &ip->pos, 1.0F);
        it_8028FD7C(ip->xDD4_itemVar.heiho.x54);
    }
    ip->xDD4_itemVar.heiho.x2C = 0;
    ip->xDD4_itemVar.heiho.x22 = 0;
    ip->pos.z = 2.0F;
    it_802762BC(ip);
    if (ip->pos.x < 0.0F) {
        ip->facing_dir = 1.0F;
        HSD_JObjSetRotationY(HSD_GObjGetHSDObj(gobj), 0.0F);
    } else {
        ip->facing_dir = -1.0F;
        HSD_JObjSetRotationY(HSD_GObjGetHSDObj(gobj), 3.1415927F);
    }
    ip->init_facing_dir = 1.0F;
    it_802D8894(gobj);
}

void it_802D8894(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->x40_vel.y = 0.0F;
    ip->x40_vel.x = 0.0F;
    Item_80268E5C((HSD_GObj*) gobj, 0, ITEM_ANIM_UPDATE);
}

int it_802D88CC(Item_GObj* gobj)
{
    return 0;
}

void it_802D88D4(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.heiho.x24 == 0) {
        it_802D8918(gobj);
        return;
    }
    ip->xDD4_itemVar.heiho.x24 = ip->xDD4_itemVar.heiho.x24 - 1;
}

int it_802D8910(Item_GObj* gobj)
{
    return 0;
}

void it_802D8918(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.heiho.x24 = 0;
    it_802D98AC(gobj);
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    it_802D98C4(ip->xBBC_dynamicBoneTable->bones[1], ip);
    ip->on_accessory = it_802D96B0;
}

static inline void it_802D8984_inline(Item_GObj* gobj, int i)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.heiho.x24 = 0;
    Item_80268E5C(gobj, i, ITEM_ANIM_UPDATE);
    it_802D98C4(ip->xBBC_dynamicBoneTable->bones[1], ip);
    ip->on_accessory = it_802D96B0;
}

int it_802D8984(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = HSD_GObjGetHSDObj(gobj);
    HSD_JObj* child = HSD_JObjGetChild(jobj);
    it_802D98C4(ip->xBBC_dynamicBoneTable->bones[1], ip);
    if (it_80272C6C(gobj) == 0) {
        it_802D8984_inline(gobj, 1);
    }
    if (ip->xDD4_itemVar.heiho.x2C > 0x3C0) {
        HSD_AObjSetFlags(child->aobj, 0x10000000U);
    }
    return 0;
}

void it_802D8A54(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    f32* attr = ip->xC4_article_data->x4_specialAttributes;
    PAD_STACK(8);
    ip->x40_vel.x = ip->facing_dir * attr[ip->xDD4_itemVar.heiho.x21 + 1];
    if (ip->xDD4_itemVar.heiho.x2C > 960) {
        ip->x40_vel.y =
            -((-0.04f * ABS(ip->x40_vel.x)) - ip->x40_vel.y);
    }
    it_802D9714(gobj);
    if (ip->xDD4_itemVar.heiho.x24 != 0) {
        HSD_JObjAddRotationY(HSD_GObjGetHSDObj(gobj), 0.15707964f);
        ip->xDD4_itemVar.heiho.x24 -= 1;
        return;
    }
    if (ip->facing_dir == -1.0F) {
        HSD_JObjSetRotationY(HSD_GObjGetHSDObj(gobj), 3.1415927F);
    } else {
        HSD_JObjSetRotationY(HSD_GObjGetHSDObj(gobj), 0);
    }
}

int it_802D8CC8(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    Article* article = ip->xC4_article_data;
    f32* attr = article->x4_specialAttributes;
    s32 temp_r31 = it_8026DA70(gobj);
    if ((ip->xDD4_itemVar.heiho.x24 == 0) && (it_80276308(gobj) != 0)) {
        ip->facing_dir = -ip->facing_dir;
        ip->x40_vel.x = ip->facing_dir * attr[ip->xDD4_itemVar.heiho.x21 + 1];
        ip->xDD4_itemVar.heiho.x24 = 0x14;
    } else if (temp_r31 == 1) {
        it_802D8984_inline(gobj, 1);
    }
    return 0;
}

int it_802D8DB4(Item_GObj* gobj)
{
    return 0;
}

static void it_802D8EC8_inline(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    f32* attr = ip->xC4_article_data->x4_specialAttributes;
    f32 rand = 2.0f * (HSD_Randf() - 0.5F);
    ip->x40_vel.x += attr[5] * rand;
    ip->x40_vel.y = 2.0F;
    ip->x40_vel.z = 1.5f;
    if (ip->facing_dir == -1.0F) {
        HSD_JObjSetRotationY(HSD_GObjGetHSDObj(gobj), 3.1415927F);
    } else {
        HSD_JObjSetRotationY(HSD_GObjGetHSDObj(gobj), 0);
    }
}

void it_802D8DBC(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    ItemAttr* it_attr = ip->xCC_item_attr;
    s32 rand;
    it_80272860(gobj, it_attr->x10_fall_speed, it_attr->x14_fall_speed_max);
    rand = HSD_Randi(3);
    ip->xD3C_spinSpeed = 0.017453292F * ((8.0F * rand) + 1.0F);
    it_80274A64(gobj);
}

int it_802D8E44(Item_GObj* gobj)
{
    return 0;
}

int it_802D8E4C(Item_GObj* gobj)
{
    return 0;
}

void it_802D8E54(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->x40_vel.y -= ip->xCC_item_attr->x10_fall_speed;
    if (ip->xDD4_itemVar.heiho.x24 != 0) {
        ip->xDD4_itemVar.heiho.x24 -= 1;
        return;
    }
    it_802D9168(gobj);
}

int it_802D8EA4(Item_GObj* gobj)
{
    it_8026DA70(gobj);
    return 0;
}

int it_802D8EC8(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    s32** attr = ip->xC4_article_data->x4_specialAttributes;
    PAD_STACK(32);
    if (ip->xDD4_itemVar.heiho.x54 != NULL) {
        it_8028F8E4(ip->xDD4_itemVar.heiho.x54);
        it_8028FC5C(ip->xDD4_itemVar.heiho.x54);
        ip->xDD4_itemVar.heiho.x54 = NULL;
    }
    ip->xDCC_flag.b3 = 1;
    if (ip->xC9C > (s32) (**attr * 0.8F)) {
        it_8027CE44(gobj);
        it_802D8EC8_inline(gobj);
        it_802D98AC(gobj);
        Item_80268E5C((HSD_GObj*) gobj, 2, ITEM_ANIM_UPDATE);
    } else {
        ip = gobj->user_data;
        if (it_8027B798(gobj, &ip->x40_vel) != 0) {
            it_802762BC(ip);
        }
        ip->xDD4_itemVar.heiho.x24 = 0xC;
        it_802D98AC(gobj);
        Item_80268E5C((HSD_GObj*) gobj, 3, ITEM_ANIM_UPDATE);
    }
    return 0;
}

void it_802D9168(Item_GObj* gobj)
{
    f32 zero = 0.0F;
    Vec3 sp14;
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = HSD_GObjGetHSDObj(gobj);
    ip->xDD4_itemVar.heiho.x24 = 0;
    Stage_UnkSetVec3TCam_Offset(&sp14);

    if (ip->pos.x < sp14.x) {
        HSD_JObjGetRotationY(jobj);
        if (jobj->rotate.y == zero) {
            ip->xDD4_itemVar.heiho.x24 = 0x14;
        }
        ip->facing_dir = -1.0F;
    } else if (ip->pos.x > sp14.x) {
        HSD_JObjGetRotationY(jobj);
        if (jobj->rotate.y != zero) {
            ip->xDD4_itemVar.heiho.x24 = 0x14;
        }
        ip->facing_dir = 1.0F;
    }

    it_802D98AC(gobj);
    Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE);
    it_802D98C4(ip->xBBC_dynamicBoneTable->bones[1], ip);
    ip->on_accessory = it_802D96B0;
}

int it_802D9274(Item_GObj* gobj)
{
    HSD_JObj* child;
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = HSD_GObjGetHSDObj(gobj);
    it_802D98C4(ip->xBBC_dynamicBoneTable->bones[1], ip);
    if (it_80272C6C(gobj) == 0) {
        it_802D8984_inline(gobj, 4);
    }
    child = HSD_JObjGetChild(jobj);
    if (ip->xDD4_itemVar.heiho.x2C > 0x3C0) {
        HSD_AObjSetFlags(child->aobj, 0x10000000U);
    }
    if (ip->xDD4_itemVar.heiho.x2C > 0x3C0) {
        HSD_AObjSetFlags(child->aobj, 0x10000000U);
    } else {
        HSD_AObjSetRate(child->aobj, 2.0F);
    }
    HSD_AObjSetRate(child->u.dobj->mobj->tobj->aobj, 2.0F);
    return 0;
}

void it_802D9384(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    f32* attr = ip->xC4_article_data->x4_specialAttributes;
    PAD_STACK(8);
    ip->x40_vel.x =
        1.5F * (ip->facing_dir * attr[ip->xDD4_itemVar.heiho.x21 + 1]);
    if (ip->xDD4_itemVar.heiho.x2C > 960) {
        ip->x40_vel.y =
            -((-0.04f * ABS(ip->x40_vel.x)) - ip->x40_vel.y);
    }
    if (ip->xDD4_itemVar.heiho.x24 != 0) {
        HSD_JObjAddRotationY(HSD_GObjGetHSDObj(gobj), 0.15707964f);
        ip->xDD4_itemVar.heiho.x24 -= 1;
        return;
    }
    if (ip->facing_dir == -1.0F) {
        HSD_JObjSetRotationY(HSD_GObjGetHSDObj(gobj), 3.1415927F);
    } else {
        HSD_JObjSetRotationY(HSD_GObjGetHSDObj(gobj), 0);
    }
}

int it_802D95F4(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    Article* article = ip->xC4_article_data;
    f32* attr = article->x4_specialAttributes;
    s32 temp_r31 = it_8026DA70(gobj);
    PAD_STACK(4);
    if ((ip->xDD4_itemVar.heiho.x24 == 0) && (it_80276308(gobj) != 0)) {
        ip->facing_dir = -ip->facing_dir;
        ip->x40_vel.x = ip->facing_dir * attr[ip->xDD4_itemVar.heiho.x21 + 1];
        ip->xDD4_itemVar.heiho.x24 = 0x14;
    } else if (temp_r31 == 1) {
        it_802D9168(gobj);
    }
    return 0;
}

void it_802D96B0(Item_GObj* gobj)
{
    f32 pad[2];
    Vec3 vec;
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.heiho.x54 != NULL) {
        vec = ip->pos;
        vec.z = -2.0F * ip->facing_dir;
        it_8028F9D8(ip->xDD4_itemVar.heiho.x54, &vec, ip->facing_dir);
    }
}

static void inline it_802D9714_inline(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDCC_flag.b3 = 1;
    if (ip->xDD4_itemVar.heiho.x54 != NULL) {
        it_8028F9B8(ip->xDD4_itemVar.heiho.x54);
        ip->xDD4_itemVar.heiho.x54 = NULL;
    }
}

void it_802D9714(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    if ((s8) (u8) ip->xDD4_itemVar.heiho.x22 == 0) {
        if ((ip->pos.x > (20.0F + Stage_GetBlastZoneLeftOffset())) &&
            (ip->pos.x < (Stage_GetBlastZoneRightOffset() - 20.0F)))
        {
            ip->xDD4_itemVar.heiho.x22 = 1;
        }
    } else if (ip->pos.x > (20.0F + Stage_GetBlastZoneRightOffset())) {
        it_802D9714_inline(gobj);
    } else if (ip->pos.x < (Stage_GetBlastZoneLeftOffset() - 20.0F)) {
        it_802D9714_inline(gobj);
    } else if (ip->pos.y > (20.0F + Stage_GetBlastZoneTopOffset())) {
        it_802D9714_inline(gobj);
    } else if (ip->pos.y < (Stage_GetBlastZoneBottomOffset() - 20.0F)) {
        it_802D9714_inline(gobj);
    }
}

void it_802D98AC(Item_GObj* arg0)
{
    Item* ip = arg0->user_data;
    ip->xDD4_itemVar.heiho.x3C.x = 0.0F;
    ip->xDD4_itemVar.heiho.x3C.y = 0.0F;
    ip->xDD4_itemVar.heiho.x3C.z = 0.0F;
}

void it_802D98C4(HSD_JObj* jobj, Item* arg1)
{
    Vec3 vec;
    Vec3 vec2;
    if (jobj != NULL) {
        vec.x = vec.y = vec.z = 0.0F;
        HSD_JObjGetTranslation(jobj, &vec2);
        arg1->x40_vel.x =
            arg1->facing_dir * (vec2.z - arg1->xDD4_itemVar.heiho.x3C.z);
        arg1->x40_vel.y = vec2.y - arg1->xDD4_itemVar.heiho.x3C.y;
        arg1->x40_vel.z = vec2.x - arg1->xDD4_itemVar.heiho.x3C.x;
        arg1->xDD4_itemVar.heiho.x3C = vec2;
        HSD_JObjSetTranslate(jobj, &vec);
    }
}

void it_802D9A0C(Item_GObj* jobj, HSD_GObj* arg1)
{
    it_8026B894(jobj, arg1);
}
