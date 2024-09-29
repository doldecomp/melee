/// @file
/// @todo A lot of duplicate code here, can maybe be cleaned up with inlines.
#include <platform.h>
#include <placeholder.h>

#include "it/items/forward.h"

#include "itsword.h"

#include "types.h" // IWYU pragma: keep

#include "ft/ftlib.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/itCommonItems.h"
#include "it/item.h"
#include "it/types.h"

#include <common_structs.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>

/* 284E30 */ static void it_80284E30(Item_GObj* gobj);
/* 285084 */ static void it_80285084(Item_GObj* gobj);
/* 285140 */ static void it_80285140(Item_GObj* gobj);
/* 2851FC */ static void it_802851FC(Item_GObj* gobj);
/* 285424 */ static void it_80285424(Item_GObj* gobj);
/* 285580 */ static bool it_80285580(Item_GObj* gobj);
/* 2855C8 */ static void it_802855C8(Item_GObj* gobj);
/* 2855CC */ static bool it_802855CC(Item_GObj* gobj);
/* 2855F8 */ static void it_802855F8(Item_GObj* gobj);
/* 285744 */ static bool it_80285744(Item_GObj* gobj);
/* 28578C */ static void it_8028578C(Item_GObj* gobj);
/* 2857D8 */ static bool it_802857D8(Item_GObj* gobj);
/* 285920 */ static bool it_80285920(Item_GObj* gobj);
/* 285AF4 */ static void it_80285AF4(Item_GObj* gobj);
/* 285AF8 */ static bool it_80285AF8(Item_GObj* gobj);
/* 285F2C */ static bool it_80285F2C(Item_GObj* gobj);
/* 285F74 */ static void it_80285F74(Item_GObj* gobj);
/* 285F78 */ static bool it_80285F78(Item_GObj* gobj);

ItemStateTable it_803F5800[] = {
    { 0, it_80285580, it_802855C8, it_802855CC },
    { 0, it_80285744, it_8028578C, it_802857D8 },
    { 0, it_80285920, it_80285AF4, it_80285AF8 },
    { 1, it_80285744, it_8028578C, it_802857D8 },
    { 0, it_80285F2C, it_80285F74, it_80285F78 },
};

Item_GObj* itSword_Spawn(Vec3* pos)
{
    SpawnItem spawn;
    spawn.kind = It_Kind_Sword;
    spawn.prev_pos = *pos;
    spawn.prev_pos.z = 0;
    spawn.pos = spawn.prev_pos;
    spawn.facing_dir = -1.0f;
    spawn.x3C_damage = 0;
    spawn.vel.x = spawn.vel.y = spawn.vel.z = 0;
    spawn.x0_parent_gobj = NULL;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x44_flag.b0 = true;
    spawn.x40 = 0;
    {
        Item_GObj* gobj = Item_80268B5C(&spawn);
        if (gobj != NULL) {
            it_80285424(gobj);
        }
        return gobj;
    }
}

void it_80284E10(HSD_GObj* gobj, int arg1)
{
    it_8026EECC(gobj, arg1);
}

void it_80284E30(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    float scale_y =
        0.3f * (ip->xDD4_itemVar.sword.x28 *
                (ip->xDD4_itemVar.sword.x4C * ip->xDD4_itemVar.sword.x10));
    HSD_JObjSetScaleY(ip->xBBC_dynamicBoneTable->bones[6], scale_y);
    {
        Vec3 scale;
        if (ip->msid == 2) {
            float temp_scale = 1.5f * ip->xDD4_itemVar.sword.x40 + scale_y;
            scale.x = temp_scale;
            scale.y = scale_y + ip->xDD4_itemVar.sword.x40;
            scale.z = temp_scale;
        } else {
            scale.x = 1.0f;
            scale.y = scale_y;
            scale.z = 1.0f;
        }
        HSD_JObjSetScale(ip->xBBC_dynamicBoneTable->bones[3], &scale);
    }
}

void it_80284FC4(Item_GObj* gobj, int arg1, float arg2)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.sword.x4 = 0;
    ip->xDD4_itemVar.sword.x8 = arg1;
    ip->xDD4_itemVar.sword.xC = 1;
    ip->xDD4_itemVar.sword.x10 = 1.0f;
    ip->xDD4_itemVar.sword.x14 = arg2;
    ip->xDD4_itemVar.sword.x18 =
        (ip->xDD4_itemVar.sword.x14 - ip->xDD4_itemVar.sword.x10) / arg1;
}

void it_80285024(Item_GObj* gobj, int arg1)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.sword.x4 = arg1;
    ip->xDD4_itemVar.sword.x8 = 0;
    ip->xDD4_itemVar.sword.xC = -1;
    ip->xDD4_itemVar.sword.x14 = 1.0f;
    ip->xDD4_itemVar.sword.x18 =
        (ip->xDD4_itemVar.sword.x14 - ip->xDD4_itemVar.sword.x10) /
        ip->xDD4_itemVar.sword.x4;
}

/// @todo Shared code with #it_802851FC.
void it_80285084(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.sword.x4 += ip->xDD4_itemVar.sword.xC;
    if (ip->xDD4_itemVar.sword.xC > 0) {
        if (ip->xDD4_itemVar.sword.x4 > ip->xDD4_itemVar.sword.x8) {
            ip->xDD4_itemVar.sword.x4 = ip->xDD4_itemVar.sword.x8;
            ip->xDD4_itemVar.sword.xC = 0;
        }
    } else if (ip->xDD4_itemVar.sword.xC < 0) {
        if (ip->xDD4_itemVar.sword.x4 < ip->xDD4_itemVar.sword.x8) {
            ip->xDD4_itemVar.sword.x4 = ip->xDD4_itemVar.sword.x8;
            ip->xDD4_itemVar.sword.xC = 0;
        }
    }
    ip->xDD4_itemVar.sword.x10 += ip->xDD4_itemVar.sword.x18;
    if (ip->xDD4_itemVar.sword.x18 > 0) {
        if (ip->xDD4_itemVar.sword.x10 > ip->xDD4_itemVar.sword.x14) {
            ip->xDD4_itemVar.sword.x10 = ip->xDD4_itemVar.sword.x14;
            ip->xDD4_itemVar.sword.x18 = 0;
        }
    } else if (ip->xDD4_itemVar.sword.x18 < 0) {
        if (ip->xDD4_itemVar.sword.x10 < ip->xDD4_itemVar.sword.x14) {
            ip->xDD4_itemVar.sword.x10 = ip->xDD4_itemVar.sword.x14;
            ip->xDD4_itemVar.sword.x18 = 0;
        }
    }
}

/// @todo Shared code with #it_802851FC.
void it_80285140(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.sword.x1C += ip->xDD4_itemVar.sword.x24;
    if (ip->xDD4_itemVar.sword.x24 > 0) {
        if (ip->xDD4_itemVar.sword.x1C > ip->xDD4_itemVar.sword.x20) {
            ip->xDD4_itemVar.sword.x1C = ip->xDD4_itemVar.sword.x20;
            ip->xDD4_itemVar.sword.x24 = 0;
        }
    } else if (ip->xDD4_itemVar.sword.x24 < 0) {
        if (ip->xDD4_itemVar.sword.x1C < ip->xDD4_itemVar.sword.x20) {
            ip->xDD4_itemVar.sword.x1C = ip->xDD4_itemVar.sword.x20;
            ip->xDD4_itemVar.sword.x24 = 0;
        }
    }
    ip->xDD4_itemVar.sword.x28 += ip->xDD4_itemVar.sword.x30;
    if (ip->xDD4_itemVar.sword.x30 > 0) {
        if (ip->xDD4_itemVar.sword.x28 > ip->xDD4_itemVar.sword.x2C) {
            ip->xDD4_itemVar.sword.x28 = ip->xDD4_itemVar.sword.x2C;
            ip->xDD4_itemVar.sword.x30 = 0;
        }
    } else if (ip->xDD4_itemVar.sword.x30 < 0) {
        if (ip->xDD4_itemVar.sword.x28 < ip->xDD4_itemVar.sword.x2C) {
            ip->xDD4_itemVar.sword.x28 = ip->xDD4_itemVar.sword.x2C;
            ip->xDD4_itemVar.sword.x30 = 0;
        }
    }
}

void it_802851FC(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.sword.x34 += ip->xDD4_itemVar.sword.x3C;
    if (ip->xDD4_itemVar.sword.x3C > 0) {
        if (ip->xDD4_itemVar.sword.x34 > ip->xDD4_itemVar.sword.x38) {
            ip->xDD4_itemVar.sword.x34 = ip->xDD4_itemVar.sword.x38;
            ip->xDD4_itemVar.sword.x3C = 0;
        }
    } else if (ip->xDD4_itemVar.sword.x3C < 0) {
        if (ip->xDD4_itemVar.sword.x34 < ip->xDD4_itemVar.sword.x38) {
            ip->xDD4_itemVar.sword.x34 = ip->xDD4_itemVar.sword.x38;
            ip->xDD4_itemVar.sword.x3C = 0;
        }
    }
    ip->xDD4_itemVar.sword.x40 += ip->xDD4_itemVar.sword.x48;
    if (ip->xDD4_itemVar.sword.x48 > 0) {
        if (ip->xDD4_itemVar.sword.x40 > ip->xDD4_itemVar.sword.x44) {
            ip->xDD4_itemVar.sword.x40 = ip->xDD4_itemVar.sword.x44;
            ip->xDD4_itemVar.sword.x48 = 0;
        }
    } else if (ip->xDD4_itemVar.sword.x48 < 0) {
        if (ip->xDD4_itemVar.sword.x40 < ip->xDD4_itemVar.sword.x44) {
            ip->xDD4_itemVar.sword.x40 = ip->xDD4_itemVar.sword.x44;
            ip->xDD4_itemVar.sword.x48 = 0;
        }
    }
}

void it_802852B8(Item_GObj* gobj, float* arg1, float* arg2)
{
    Item* ip = GET_ITEM(gobj);

    float f1 = ip->xDD4_itemVar.sword.x4C * ip->xDD4_itemVar.star.xvel *
               ip->xDD4_itemVar.sword.x28 * 0.3f;

    if (arg1 != NULL) {
        *arg1 = 0.0f;
    }
    if (arg2 != NULL) {
        *arg2 = 10.03f * f1;
    }
}

itSword_UnkBytes* it_80285300(Item_GObj* gobj)
{
    itSword_UnkArticle1* attrs =
        GET_ITEM(gobj)->xC4_article_data->x4_specialAttributes;
    return &attrs->x1C;
}

void it_80285314(Item_GObj* gobj)
{
    it_80272CC0(gobj, 5);
}

void it_80285338(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itSword_UnkArticle1* attrs = ip->xC4_article_data->x4_specialAttributes;
    PAD_STACK(8);
    it_8026B390(gobj);
    ip->x40_vel.x = 0.0f;
    ip->x40_vel.y = attrs->xC;
    ip->x40_vel.z = 0.0f;
    ip->xDD4_itemVar.sword.x0 = 0;
    ip->xDD4_itemVar.sword.x4 = 0;
    ip->xDD4_itemVar.sword.x8 = 0;
    ip->xDD4_itemVar.sword.xC = 0;
    ip->xDD4_itemVar.sword.x10 = 1.0f;
    ip->xDD4_itemVar.sword.x14 = 1.0f;
    ip->xDD4_itemVar.sword.x18 = 0.0f;
    ip->xDD4_itemVar.sword.x1C = 0;
    ip->xDD4_itemVar.sword.x20 = 0;
    ip->xDD4_itemVar.sword.x24 = 0;
    ip->xDD4_itemVar.sword.x28 = 1.0f;
    ip->xDD4_itemVar.sword.x2C = 1.0f;
    ip->xDD4_itemVar.sword.x30 = 0.0f;
    ip->xDD4_itemVar.sword.x34 = 0;
    ip->xDD4_itemVar.sword.x38 = 0;
    ip->xDD4_itemVar.sword.x3C = 0;
    ip->xDD4_itemVar.sword.x40 = 1.0f;
    ip->xDD4_itemVar.sword.x44 = 1.0f;
    ip->xDD4_itemVar.sword.x48 = 0.0f;
    ip->xDD4_itemVar.sword.x50 = 0.0f;
    ip->xDD4_itemVar.sword.x4C =
        HSD_JObjGetScaleY(ip->xBBC_dynamicBoneTable->bones[6]);
    ip->xDD4_itemVar.sword.x54 = 0;
    it_802855F8(gobj);
}

static inline void inlineA0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->x40_vel.x = ip->x40_vel.y = ip->x40_vel.z = 0.0f;
    ip->xD50_landNum = 0;
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
}

static inline void inlineB0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    ip->xD50_landNum = 0;
}

static inline void inlineA1(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.sword.x4 = 4;
    ip->xDD4_itemVar.sword.x8 = 0;
    ip->xDD4_itemVar.sword.xC = -1;
    ip->xDD4_itemVar.sword.x14 = 1.0f;
    ip->xDD4_itemVar.sword.x18 =
        (ip->xDD4_itemVar.sword.x14 - ip->xDD4_itemVar.sword.x10) /
        ip->xDD4_itemVar.sword.x4;
}

static inline void inlineA2(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.sword.x1C = 4;
    ip->xDD4_itemVar.sword.x20 = 0;
    ip->xDD4_itemVar.sword.x24 = -1;
    ip->xDD4_itemVar.sword.x2C = 1.0f;
    ip->xDD4_itemVar.sword.x30 =
        (ip->xDD4_itemVar.sword.x2C - ip->xDD4_itemVar.sword.x28) /
        ip->xDD4_itemVar.sword.x1C;
}

static inline void inlineC1(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.sword.x1C = 0;
    ip->xDD4_itemVar.sword.x20 = 4;
    ip->xDD4_itemVar.sword.x24 = 1;
    ip->xDD4_itemVar.sword.x28 = 1.0f;
    ip->xDD4_itemVar.sword.x2C = 2.0f;
    ip->xDD4_itemVar.sword.x30 =
        (ip->xDD4_itemVar.sword.x2C - ip->xDD4_itemVar.sword.x28) / 4;
}

static inline void inlineA3(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itSword_UnkArticle1* attrs = ip->xC4_article_data->x4_specialAttributes;
    ip->xDD4_itemVar.sword.x34 = attrs->x18;
    ip->xDD4_itemVar.sword.x38 = 0;
    ip->xDD4_itemVar.sword.x3C = -1;
    ip->xDD4_itemVar.sword.x44 = attrs->x10;
    ip->xDD4_itemVar.sword.x48 =
        (attrs->x10 - ip->xDD4_itemVar.sword.x40) / attrs->x18;
}

static inline void inlineD1(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itSword_UnkArticle1* attrs = ip->xC4_article_data->x4_specialAttributes;
    ip->xDD4_itemVar.sword.x34 = 0;
    ip->xDD4_itemVar.sword.x38 = attrs->x18;
    ip->xDD4_itemVar.sword.x3C = 1;
    ip->xDD4_itemVar.sword.x40 = attrs->x10;
    ip->xDD4_itemVar.sword.x44 = attrs->x14;
    ip->xDD4_itemVar.sword.x48 = (attrs->x14 - attrs->x10) / attrs->x18;
}

static inline void inlineA4(Item_GObj* gobj)
{
    it_80285084(gobj);
    it_80285140(gobj);
    it_802851FC(gobj);
    it_80284E30(gobj);
}

void it_80285424(Item_GObj* gobj)
{
    inlineA0(gobj);
    inlineA1(gobj);
    inlineA2(gobj);
    inlineA3(gobj);
    inlineA4(gobj);
}

bool it_80285580(Item_GObj* gobj)
{
    inlineA4(gobj);
    return false;
}

void it_802855C8(Item_GObj* gobj) {}

bool it_802855CC(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_802855F8);
    return false;
}

void it_802855F8(Item_GObj* gobj)
{
    inlineB0(gobj);
    inlineA1(gobj);
    inlineA2(gobj);
    inlineA3(gobj);
    inlineA4(gobj);
}

bool it_80285744(Item_GObj* gobj)
{
    inlineA4(gobj);
    return false;
}

void it_8028578C(Item_GObj* gobj)
{
    ItemAttr* attrs = GET_ITEM(gobj)->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
    it_80274658(gobj, it_804D6D28->x68_float);
}

bool it_802857D8(Item_GObj* gobj)
{
    it_8026E15C(gobj, it_80285424);
    return false;
}

void it_80285804(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    HSD_JObj* child = HSD_JObjGetChild(jobj);
    HSD_JObjClearFlagsAll(child, JOBJ_HIDDEN);
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
    ip->xD50_landNum = 0;
    inlineA1(gobj);
    inlineC1(gobj);
    inlineA4(gobj);
}

bool it_80285920(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itSword_UnkArticle1* attrs = ip->xC4_article_data->x4_specialAttributes;
    if (ip->owner != NULL && ftLib_80086FA8(ip->owner) != 1) {
        inlineA1(gobj);
    }
    if (ip->xDD4_itemVar.sword.x3C == 0) {
        if (ip->xDD4_itemVar.sword.x34 == ip->xDD4_itemVar.sword.x38) {
            if (ip->xDD4_itemVar.sword.x38 == 0) {
                inlineD1(gobj);
            } else if (ip->xDD4_itemVar.sword.x38 == attrs->x18) {
                inlineA3(gobj);
            }
        }
    }

    inlineA4(gobj);
    return false;
}

void it_80285AF4(Item_GObj* gobj) {}

bool it_80285AF8(Item_GObj* gobj)
{
    return false;
}

void it_80285B00(Item_GObj* gobj)
{
    HSD_JObj* child = HSD_JObjGetChild(GET_JOBJ(gobj));

    it_8026B390(gobj);
    HSD_JObjClearFlagsAll(child, JOBJ_HIDDEN);
    Item_80268E5C(gobj, 3, ITEM_ANIM_UPDATE | ITEM_DROP_UPDATE);

    inlineA1(gobj);
    inlineA2(gobj);
    inlineA3(gobj);
    inlineA4(gobj);
}

void it_80285C78(Item_GObj* gobj)
{
    HSD_JObj* child = HSD_JObjGetChild(GET_JOBJ(gobj));

    it_8026B390(gobj);
    HSD_JObjClearFlagsAll(child, JOBJ_HIDDEN);
    Item_80268E5C(gobj, 3, ITEM_ANIM_UPDATE | ITEM_DROP_UPDATE);

    inlineA1(gobj);
    inlineA2(gobj);
    inlineA3(gobj);
    inlineA4(gobj);
}

void it_80285DF0(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE);
    inlineA1(gobj);
    inlineA2(gobj);
    inlineA3(gobj);
    inlineA4(gobj);
}

bool it_80285F2C(Item_GObj* gobj)
{
    inlineA4(gobj);
    return false;
}

void it_80285F74(Item_GObj* gobj) {}

bool it_80285F78(Item_GObj* gobj)
{
    it_8026E8C4(gobj, it_80285424, it_802855F8);
    return false;
}

bool it_80285FAC(Item_GObj* gobj)
{
    if (GET_ITEM(gobj)->msid == 3) {
        itColl_BounceOffVictim(gobj);
    }
    return false;
}

bool it_80285FE0(Item_GObj* gobj)
{
    return it_80273030(gobj);
}

bool it_80286000(Item_GObj* gobj)
{
    itColl_BounceOffVictim(gobj);
    return false;
}

bool it_80286024(Item_GObj* gobj)
{
    itColl_BounceOffVictim(gobj);
    return false;
}

bool itSword_BounceOffShield(Item_GObj* gobj)
{
    return itColl_BounceOffShield(gobj);
}

void it_80286068(Item_GObj* gobj, HSD_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
