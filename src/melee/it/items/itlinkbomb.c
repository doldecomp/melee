#include "baselib/random.h"

#include "mp/mpcoll.h"

#include "lb/lb_00F9.h"

#include "ft/chara/ftLink/ftLk_AttackAir.h"

#include "ft/ft_0C31.h"

#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"


#include "it/itCharItems.h"
#include "it/inlines.h"
#include "it/item.h"

#include "itlinkbomb.h"

/// @todo Fix these to be in a single file, not math.h
#define M_PI 3.14159265358979323846
#define ABS(x) ((x) < 0 ? -(x) : (x))
static inline f32 fabs_inline(f32 x)
{
    if (x < 0) {
        return -x;
    } else {
        return x;
    }
}

static s8 it_803F68F8[0x28] = {
    0x21,
    0x28,
    0x6A,
    0x6F,
    0x62,
    0x6A,
    0x2D,
    0x3E,
    0x66,
    0x6C,
    0x61,
    0x67,
    0x73,
    0x20,
    0x26,
    0x20,
    0x4A,
    0x4F,
    0x42,
    0x4A,
    0x5F,
    0x55,
    0x53,
    0x45,
    0x5F,
    0x51,
    0x55,
    0x41,
    0x54,
    0x45,
    0x52,
    0x4E,
    0x49,
    0x4F,
    0x4E,
    0x29,
    0,
    0,
    0,
    0,
};
static s8 it_804D5380[8] = { 0x6A, 0x6F, 0x62, 0x6A, 0x2E, 0x68, 0, 0 };
static s8 it_804D5388[8] = { 0x6A, 0x6F, 0x62, 0x6A, 0, 0, 0, 0 };
static Vec3 it_803B8640;


ItemStateTable it_803F6888[] = {
    { 0, it_8029E074, it_8029E218, NULL },
    { 0, it_8029E3D8, it_8029E574, it_8029E5A4 },
    { 1, it_8029E920, it_8029EAF0, it_8029EB3C },
    { 1, it_8029EF84, it_8029F04C, it_8029F098 },
    { 0, it_8029F3DC, it_8029F60C, it_8029F670 },
    { 2, it_8029F934, it_8029F954, it_8029F958 },
    { 0, it_8029FB4C, it_8029FCE8, it_8029FCEC },
};

// 0: This matches all the functions that presumably have an inlined
// it_8029DB5C
//    by using a different inline it_8029DB5C_Inline_Matching
// 1: Presumably the intended method calling it_8029DB5C directly
#define TEST_REAL 0

void it_8029D968(Item_GObj *arg0) {
    Item *item;
    item = GET_ITEM((HSD_GObj*) arg0);
    if ((item->xDC8_word.flags.x13 == false) && ((s32) item->msid != 5)) {
        it_8029F69C((HSD_GObj*) arg0);
    }
}

static void it_8029D9A4(HSD_GObj *arg0, enum_t msid, Item_StateChangeFlags arg2)
{
    Item *item;
    HSD_JObj *jobj;
    f32 x;
    f32 y;
    item = HSD_GObjGetUserData(arg0);
    jobj = item->xBBC_dynamicBoneTable->bones[3];
    y = HSD_JObjGetTranslationY(jobj);
    x = HSD_JObjGetRotationX(jobj);
    if (item->xDD4_itemVar.linkbomb.x0.bits.b0) {
        Item_80268E5C(arg0, msid, arg2 | ITEM_CMD_UPDATE);
    } else {
        Item_80268E5C(arg0, msid, arg2 | ITEM_ANIM_UPDATE);
    }
    HSD_JObjSetTranslateY(jobj, y);
    HSD_JObjSetRotationX(jobj, x);
}

static inline void it_8029DB5C_Inline_Matching(HSD_GObj *arg0, Item *item, Article *article, itLinkBombAttributes *sa)
{
    Item *item_2;
    ItemStateDesc *item_state_desc;
    HSD_GObj *temp_r31;

    f32 temp_f31;
    f32 temp_f31_2;
    HSD_JObj *temp_r31_2;

    if ((item->xD44_lifeTimer <= sa->xC) && item->xDD4_itemVar.linkbomb.x0.bits.b0 == 0) {
        temp_r31 = arg0->hsd_obj;
        item->xD0_itemStateDesc = &article->xC_itemStates->x0_itemStateDesc[3];
        item_state_desc = item->xD0_itemStateDesc;
        if (item_state_desc != NULL) {
            Item_80268D34(arg0, item_state_desc);
        }
        HSD_JObjAnimAll((HSD_JObj *) temp_r31);
        item->xDD4_itemVar.linkbomb.x0.bits.b0 = true;
    }
    item->xD44_lifeTimer = item->xD44_lifeTimer - 1.0f;
    item_2 = GET_ITEM(arg0);
    if (item_2->xDD4_itemVar.linkbomb.x0.bits.b0 == 0) {
        temp_f31 = item_2->xDD4_itemVar.linkbomb.x8;
        temp_r31_2 = item_2->xBBC_dynamicBoneTable->bones[3];
#if 1
        fake_HSD_JObjAddTranslationY(temp_r31_2, temp_f31);
        temp_f31_2 = item_2->xDD4_itemVar.linkbomb.xC;
        fake_HSD_JObjAddRotationX(temp_r31_2, temp_f31_2);
#else
        HSD_JObjAddTranslationY(temp_r31_2, temp_f31);
        temp_f31_2 = item_2->xDD4_itemVar.linkbomb.xC;
        HSD_JObjAddRotationX(temp_r31_2, temp_f31_2);
#endif
    }
}

static inline void it_8029DB5C_Inline_AnimAdd_Part(HSD_GObj *arg0)
{
    Item *item_2;

    f32 temp_f31;
    f32 temp_f31_2;
    HSD_JObj *temp_r31_2;

    item_2 = GET_ITEM(arg0);
    if (item_2->xDD4_itemVar.linkbomb.x0.bits.b0 == 0) {
        temp_f31 = item_2->xDD4_itemVar.linkbomb.x8;
        temp_r31_2 = item_2->xBBC_dynamicBoneTable->bones[3];
#if 0
        fake_HSD_JObjAddTranslationY(temp_r31_2, temp_f31);
        temp_f31_2 = item_2->xDD4_itemVar.linkbomb.xC;
        fake_HSD_JObjAddRotationX(temp_r31_2, temp_f31_2);
#else
        HSD_JObjAddTranslationY(temp_r31_2, temp_f31);
        temp_f31_2 = item_2->xDD4_itemVar.linkbomb.xC;
        HSD_JObjAddRotationX(temp_r31_2, temp_f31_2);
#endif
    }
}

static inline it_8029DB5C_Inline_TimerCheck_Part(HSD_GObj *arg0, Item *item, Article *article, itLinkBombAttributes *sa)
{
    HSD_GObj *temp_r31;
    ItemStateDesc *item_state_desc;

    if ((item->xD44_lifeTimer <= sa->xC) && item->xDD4_itemVar.linkbomb.x0.bits.b0 == 0) {
        temp_r31 = arg0->hsd_obj;
        item->xD0_itemStateDesc = &article->xC_itemStates->x0_itemStateDesc[3];
        item_state_desc = item->xD0_itemStateDesc;
        if (item_state_desc != NULL) {
            Item_80268D34(arg0, item_state_desc);
        }
        HSD_JObjAnimAll((HSD_JObj *) temp_r31);
        item->xDD4_itemVar.linkbomb.x0.bits.b0 = true;
    }
    item->xD44_lifeTimer -= 1.0F;
}

static void it_8029DB5C(HSD_GObj *arg0) {
#if 1
    Item *item;
    Article *article;
    itLinkBombAttributes* sa;

    item = GET_ITEM(arg0);
    article = item->xC4_article_data;
    sa = article->x4_specialAttributes;
    if (item->xD44_lifeTimer <= 0.0f) {
        it_8029F69C(arg0);
    } else {

        it_8029DB5C_Inline_TimerCheck_Part(arg0, item, article, sa);
        it_8029DB5C_Inline_AnimAdd_Part(arg0);
    }
#endif

#if 0
    Item *item;
    Article *article;
    itLinkBombAttributes* sa;

    item = arg0->user_data;
    article = item->xC4_article_data;
    sa = article->x4_specialAttributes;
    if (item->xD44_lifeTimer <= 0.0f) {
        it_8029F69C(arg0);
    } else {
        it_8029DB5C_Inline_Matching(arg0, item, article, sa);
    }
#endif

#if 0
    Item *item;
    Article *article;
    itLinkBombAttributes* sa;

    Item *item_2;
    ItemStateDesc *item_state_desc;
    HSD_GObj *temp_r31;

    item = GET_ITEM(arg0);
    article = item->xC4_article_data;
    sa = article->x4_specialAttributes;
    if (item->xD44_lifeTimer <= 0.0f) {
        it_8029F69C( arg0);
    } else {
        if ((item->xD44_lifeTimer <= sa->xC) && item->xDD4_itemVar.linkbomb.x0.bits.b0 == 0) {
            temp_r31 = arg0->hsd_obj;
            item->xD0_itemStateDesc = &article->xC_itemStates->x0_itemStateDesc[3];
            item_state_desc = item->xD0_itemStateDesc;
            if (item_state_desc != NULL) {
                Item_80268D34(arg0, item_state_desc);
            }
            HSD_JObjAnimAll((HSD_JObj *) temp_r31);
            item->xDD4_itemVar.linkbomb.x0.bits.b0 = true;
        }
        item->xD44_lifeTimer -= 1.0F;
        it_8029DB5C_Inline_AnimAdd_Part(arg0);
    }
#endif

#if 0

    Item *item;
    Article *article;
    itLinkBombAttributes* sa;

    Item *item_2;
    ItemStateDesc *item_state_desc;
    HSD_GObj *temp_r31;

    f32 temp_f31;
    f32 temp_f31_2;
    HSD_JObj *temp_r31_2;

    item = GET_ITEM(arg0);
    article = item->xC4_article_data;
    sa = article->x4_specialAttributes;

    if (item->xD44_lifeTimer <= 0.0f) {
        it_8029F69C(arg0);
    } else {
        it_8029DB5C_Inline_TimerCheck_Part(arg0, item, article, sa);
        item_2 = GET_ITEM(arg0);
        if (item_2->xDD4_itemVar.linkbomb.x0.bits.b0 == 0) {
            temp_f31 = item_2->xDD4_itemVar.linkbomb.x8;
            temp_r31_2 = item_2->xBBC_dynamicBoneTable->bones[3];
            HSD_JObjAddTranslationY(temp_r31_2, temp_f31);
            temp_f31_2 = item_2->xDD4_itemVar.linkbomb.xC;
            HSD_JObjAddRotationX(temp_r31_2, temp_f31_2);
        }
    }
#endif


#if 0
    Item *item;
    Article *article;
    itLinkBombAttributes* sa;

    Item *item_2;
    ItemStateDesc *item_state_desc;
    HSD_GObj *temp_r31;

    f32 temp_f31;
    f32 temp_f31_2;
    HSD_JObj *temp_r31_2;
    f32 pad[2];

    item = GET_ITEM(arg0);
    article = item->xC4_article_data;
    sa = article->x4_specialAttributes;

    if (item->xD44_lifeTimer <= 0.0f) {
        it_8029F69C(arg0);
    } else {
        if ((item->xD44_lifeTimer <= sa->xC) && item->xDD4_itemVar.linkbomb.x0.bits.b0 == 0) {
            temp_r31 = arg0->hsd_obj;
            item->xD0_itemStateDesc = &article->xC_itemStates->x0_itemStateDesc[3];
            item_state_desc = item->xD0_itemStateDesc;
            if (item_state_desc != NULL) {
                Item_80268D34(arg0, item_state_desc);
            }
            HSD_JObjAnimAll((HSD_JObj *) temp_r31);
            item->xDD4_itemVar.linkbomb.x0.bits.b0 = true;
        }
        item->xD44_lifeTimer -= 1.0F;
        item_2 = GET_ITEM(arg0);
        if (item_2->xDD4_itemVar.linkbomb.x0.bits.b0 == 0) {
            temp_f31 = item_2->xDD4_itemVar.linkbomb.x8;
            temp_r31_2 = item_2->xBBC_dynamicBoneTable->bones[3];
            HSD_JObjAddTranslationY(temp_r31_2, temp_f31);
            temp_f31_2 = item_2->xDD4_itemVar.linkbomb.xC;
            HSD_JObjAddRotationX(temp_r31_2, temp_f31_2);
        }
    }
#endif



}

static inline it_8029DD58_inline(Item *item, itLinkBombAttributes *attr, Item_GObj *fighter_gobj, Item_GObj *temp_r3, u8 arg2)
{
    f32 temp_f2;
    it_80275158((HSD_GObj *) temp_r3, attr->lifetime);
    item->xDD4_itemVar.linkbomb.x0.bits.b0 = false;
    item->xDD4_itemVar.linkbomb.x10 = fighter_gobj;
    item->xDD4_itemVar.linkbomb.x0.bits.b2 = false;
    temp_f2 = attr->lifetime - attr->xC;
    item->xDD4_itemVar.linkbomb.x8 = (-2.8000002f / temp_f2) * item->scl;
    item->xDD4_itemVar.linkbomb.xC = (-0.15707964f / temp_f2) * item->scl;
    it_8026BD0C(temp_r3);
    Item_8026AB54((HSD_GObj *) temp_r3, (HSD_GObj *) fighter_gobj, arg2);
}

HSD_GObj *it_8029DD58(Item_GObj *fighter_gobj, Vec3 *arg1, u8 arg2, int arg3, f32 arg4) {
    Item_GObj *temp_r3;
    SpawnItem spawn;
    Item *item; // r26
    itLinkBombAttributes *attr;

    spawn.kind = arg3;
    spawn.prev_pos = *arg1;
    it_8026BB68(fighter_gobj, &spawn.pos);
    spawn.facing_dir = arg4;
    spawn.x3C_damage = 0;
    spawn.vel.z = 0.0F;
    spawn.vel.y = 0.0F;
    spawn.vel.x = 0.0F;
    spawn.x0_parent_gobj = (HSD_GObj *)fighter_gobj;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x44_flag.bits.b0 = true;
    spawn.x40 = 0;
    temp_r3 = Item_80268B18(&spawn);
    if (temp_r3 != NULL) {
        item = GET_ITEM((HSD_GObj *) temp_r3);
        attr = item->xC4_article_data->x4_specialAttributes;
        it_8029DD58_inline(item, attr, fighter_gobj, temp_r3, arg2);
    }
    return (HSD_GObj *) temp_r3;
}

void it_8029DEB0(HSD_GObj *arg0) {
    HSD_JObj *jobj;
    Item *item;
    f32 temp_f30;
    f32 temp_f31;

    it_8029D9A4(arg0, 0, 0);
    it_8026BCF4((Item_GObj *) arg0);
}

int it_8029E074(HSD_GObj *arg0) {
    Item *item;
    Article *article;
    itLinkBombAttributes* sa;
    int pad[5];

    if (it_80272C6C(arg0) == 0) {
        it_8029DEB0(arg0);
    }
#if TEST_REAL
    it_8029DB5C(arg0);
#else
    item = GET_ITEM(arg0);
    article = item->xC4_article_data;
    sa = article->x4_specialAttributes;
    if (item->xD44_lifeTimer <= 0.0f) {
        it_8029F69C(arg0);
    } else {
        it_8029DB5C_Inline_Matching(arg0, item, article, sa);
    }
#endif
    return 0;
}

void it_8029E218(HSD_GObj *arg0) {
    return;
}

void fn_8029E21C(HSD_GObj *arg0) {
    int pad[2];
    it_8029D9A4(arg0, 1, 0x0);
}

int it_8029E3D8(HSD_GObj *arg0) {
    Item *item;
    Article *article;
    itLinkBombAttributes* sa;
    f32 pad[2];

    if (it_80272C6C(arg0) == 0) {
        fn_8029E21C(arg0);
    }

#if TEST_REAL
    it_8029DB5C(arg0);
#else
    item = GET_ITEM(arg0);
    article = item->xC4_article_data;
    sa = article->x4_specialAttributes;
    if (item->xD44_lifeTimer <= 0.0f) {
        it_8029F69C(arg0);
    } else {
        it_8029DB5C_Inline_Matching(arg0, item, article, sa);
    }
#endif

    return 0;
}

void it_8029E574(HSD_GObj *arg0) {
    ItemAttr *temp_r4;

    temp_r4 = GET_ITEM((HSD_GObj*) arg0)->xCC_item_attr;
    it_80272860((Item_GObj *) arg0, temp_r4->x10_fall_speed, temp_r4->x14_fall_speed_max);
}

int it_8029E5A4(Item_GObj *arg0) {
    it_8026E15C(arg0, it_8029F18C);
    return 0;
}

void it_8029E5D0(HSD_GObj* arg0)
{
    Item *item;
    item = GET_ITEM(arg0);
    it_80275414(arg0);
    it_802754A4((Item_GObj*) arg0);
    if (item->msid != 2) {
        it_8029D9A4(arg0, 2, ITEM_DROP_UPDATE);
    } else {
        it_8029D9A4(arg0, 2, ITEM_HIT_PRESERVE | ITEM_DROP_UPDATE);
    }
}

int it_8029E920(HSD_GObj *arg0) {
    Item *item;
    Article *article;
    itLinkBombAttributes* sa;


    if (it_80272C6C(arg0) == 0) {
        item = GET_ITEM(arg0);
        it_8029E5D0(arg0);
    }

#if TEST_REAL
    it_8029DB5C(arg0);
#else
    item = GET_ITEM(arg0);
    article = item->xC4_article_data;
    sa = article->x4_specialAttributes;
    if (item->xD44_lifeTimer <= 0.0f) {
        it_8029F69C(arg0);
    } else {
        it_8029DB5C_Inline_Matching(arg0, item, article, sa);
    }
#endif

    return 0;
}

void it_8029EAF0(Item_GObj *arg0) {
    ItemAttr *temp_r4;

    temp_r4 = GET_ITEM((HSD_GObj *)arg0)->xCC_item_attr;
    it_80272860(arg0, temp_r4->x10_fall_speed, temp_r4->x14_fall_speed_max);
    it_80274658((HSD_GObj *) arg0, it_804D6D28->x68_float);
}

static inline int it_LinkBomb_Inline_VelocityCompare(HSD_GObj *arg0, Vec3 *vel)
{
    Item *item;
    itLinkBombAttributes *sa;
    item = arg0->user_data;
    sa = item->xC4_article_data->x4_specialAttributes;
    if ((fabs_inline(vel->x) > sa->x24) || (fabs_inline(vel->y) > sa->x28)) {
        it_8029F69C(arg0);
        return 1;
    } else {
        return 0;
    }
}

int it_8029EB3C(HSD_GObj *arg0) {
    Item *item;
    s32 temp_r3;
    Vec3 vel;

    item = GET_ITEM(arg0);
    vel = item->x40_vel;
    temp_r3 = it_8026DAA8((Item_GObj *) arg0);
    if (temp_r3 & 0xF) {
        if (!it_LinkBomb_Inline_VelocityCompare(arg0, &vel) && (temp_r3 & 1)) {
            it_802762B0(item);
            it_80275D5C(arg0, &item->xC0C);
            it_8029F18C(arg0);
        }
    }
    return 0;
}

void it_8029EC34(HSD_GObj* arg0)
{
    Item *item;

    item = GET_ITEM(arg0);
    it_80275414(arg0);
    it_802754A4((Item_GObj*) arg0);
    if (item->msid != 3) {
        it_8029D9A4(arg0, 3, ITEM_DROP_UPDATE);
    } else {
        it_8029D9A4(arg0, 3, ITEM_HIT_PRESERVE | ITEM_DROP_UPDATE);
    }
}

static inline void it_8029E3D8_fake_2(HSD_GObj* arg0)
{
    it_8029DB5C(arg0);
}

static inline void it_8029E3D8_fake(HSD_GObj* arg0)
{
    if (it_80272C6C(arg0) == 0) {
        fn_8029E21C(arg0);
    }
    it_8029E3D8_fake_2(arg0);
}

// This should have a non-inlined it_8029DB5C, presumably expanded from
// it_8029E3D8, but I can't figure out how to get a match for it_8029E3D8 that
// calls it_8029DB5C. Not sure if that's related to the unused
// item/specialattributes.
int it_8029EF84(HSD_GObj* arg0)
{
    Item* item;
    Article* article;
    itLinkBombAttributes* sa;

    item = GET_ITEM(arg0);
    article = item->xC4_article_data;
    sa = article->x4_specialAttributes;

    if (it_80272C6C(arg0) == 0) {
        it_8029EC34(arg0);
    }
    it_8029E3D8_fake(arg0);
    return 0;
}

void it_8029F04C(Item_GObj *arg0) {
    ItemAttr *temp_r4;
    temp_r4 = GET_ITEM((HSD_GObj *) arg0)->xCC_item_attr;
    it_80272860(arg0, temp_r4->x10_fall_speed, temp_r4->x14_fall_speed_max);
    it_80274658((HSD_GObj *) arg0, it_804D6D28->x68_float);
}

int it_8029F098(HSD_GObj *arg0) {
    GET_ITEM(arg0);
    it_8029EB3C(arg0);
    return 0;
}

static inline f32 fsign_inline(f32 x)
{
    if (x >= 0.0F) {
        return 1.0F;
    } else {
        return -1.0F;
    }
}

static inline s32 float_sign_int_inline(f32 x)
{
    if (x == -1.0F) {
        return -1;
    } else {
        return 1;
    }
}

void it_8029F18C(HSD_GObj *arg0) {
    Item *item;
    s32 temp_r0;

    item = arg0->user_data;

    temp_r0 = item->msid;
    if ((temp_r0 != 6) || (temp_r0 != 4)) {
        item->xDD4_itemVar.linkbomb.x4 = fsign_inline(item->x40_vel.x);
        mpColl_800436D8(&item->x378_itemColl, float_sign_int_inline(item->xDD4_itemVar.linkbomb.x4));
        item->xDD4_itemVar.linkbomb.x0.bits.b1 = true;
    } else {
        item->xDD4_itemVar.linkbomb.x0.bits.b1 = false;
        item->x40_vel.z = 0.0f;
        item->x40_vel.y = 0.0f;
        item->x40_vel.x = 0.0f;
    }

    it_8029D9A4(arg0, 4, 0);
}

// This regswap may or may not be related to the fake inline for it_8029DB5C,
// but every other function matches with it.
int it_8029F3DC(HSD_GObj *arg0) {
    Item *item;
    Article *article;
    itLinkBombAttributes* sa;

    if (it_80272C6C(arg0) == 0) {
        it_8029F18C(arg0);
    }
#if TEST_REAL
    it_8029DB5C(arg0);
#else
    item = GET_ITEM(arg0);
    article = item->xC4_article_data;
    sa = article->x4_specialAttributes;
    if (item->xD44_lifeTimer <= 0.0f) {
        it_8029F69C(arg0);
    } else {
        it_8029DB5C_Inline_Matching(arg0, item, article, sa);
    }
#endif

    return 0;
}

// Regswap unrelated to it_8029DB5C
void it_8029F60C(HSD_GObj *gobj) {
    f32 temp_f2;
    Item *item;
    itLinkBombAttributes *sa;

    item = GET_ITEM(gobj);
    sa = item->xC4_article_data->x4_specialAttributes;
    if (item->xDD4_itemVar.linkbomb.x0.bits.b1) {
        temp_f2 = item->x40_vel.x;
        if (temp_f2 != 0.0F) {
            item->x40_vel.x = (sa->x2C * item->xDD4_itemVar.linkbomb.x4) + temp_f2;
        }
        if (fabs_inline(item->x40_vel.x) < sa->x30) {
            item->x40_vel.x = 0.0F;
        }
    }
}

int it_8029F670(Item_GObj *arg0) {
    it_8026D62C(arg0, fn_8029E21C);
    return 0;
}

void it_8029F69C(HSD_GObj* arg0)
{
    HSD_GObj *temp_r0;
    HSD_GObj *temp_r3;
    HSD_JObj *jobj;
    Item *item;
    int pad[2];
    Vec3 item_pos;
    Vec3 const_vec;

    item = GET_ITEM(arg0);
    jobj = HSD_GObjGetHSDObj(arg0);
    it_80275444((Item_GObj*) arg0);
    if (item->xDC8_word.flags.x13) {
        const_vec = it_803B8640;
        it_8027429C(arg0, &const_vec);
        it_802756D0(arg0);
        temp_r0 = item->owner;
        if (temp_r0 != NULL) {
            temp_r3 = (HSD_GObj *)item->xDD4_itemVar.linkbomb.x10;
            if (temp_r0 == temp_r3) {
                ftLk_AttackAir_SetupParts(temp_r3);
            }
        }
    }
    it_8026B3A8((Item_GObj*) arg0);
    it_80273454((Item_GObj*) arg0);
    HSD_JObjSetFlagsAll(jobj, 0x10U);
    it_8026BD24((Item_GObj*) arg0);
    it_8027518C((Item_GObj*) arg0);
    it_802756D0(arg0);
    it_80272A60((Item_GObj*) arg0);
    it_8029D9A4(arg0, 5, 0x0); // inline
    item_pos = item->pos;
    lb_800119DC(&item_pos, 0x78, 1.0f, 0.02f, 1.0471976f);
}

int it_8029F934(Item_GObj *arg0) {
    it_802751D8(arg0);
    return;
}

void it_8029F954(HSD_GObj *gobj) {
    return;
}

int it_8029F958(HSD_GObj *gobj) {
    return 0;
}

int it_8029F960(HSD_GObj *arg0) {
    Item *item;
    Item *item_2;
    s32 temp_r3;
    itLinkBombAttributes *sa;

    item = GET_ITEM(arg0);
    if (item->msid != 5) {
        if (!it_LinkBomb_Inline_VelocityCompare(arg0, &item->x40_vel)) {
            item_2 = GET_ITEM(arg0);
            sa = item_2->xC4_article_data->x4_specialAttributes;
            item_2->facing_dir = -item_2->facing_dir;
            item_2->x40_vel.x = sa->x1C * item_2->facing_dir;
            item_2->x40_vel.y = sa->x20;
        }
    }
    return 0;
}

int it_8029FA30(Item_GObj *arg0) {
    Item *item;
    f32 temp_f1;
    itLinkBombAttributes *sa;
    f32 pad[2];

    item = GET_ITEM((HSD_GObj*) arg0);
    sa = item->xC4_article_data->x4_specialAttributes;
    if (item->msid != 5) {
        if (item->xCA0 >= sa->x10) {
            it_8029F69C((HSD_GObj*) arg0);
        } else if (!item->xDD4_itemVar.linkbomb.x0.bits.b2) {
            if (item->x40_vel.x > sa->x30) {
                item->facing_dir = -item->xCCC_incDamageDirection;
                item->x40_vel.x = sa->x14 * item->facing_dir;
            } else {
                temp_f1 = 2.0f * (HSD_Randf() - 0.5f);
                item->x40_vel.x = sa->x14 * temp_f1;
                it_80272980(arg0, temp_f1);
            }
            item->x40_vel.y = sa->x18 * item->facing_dir;
            item->xDD4_itemVar.linkbomb.x0.bits.b2 = true;
        }
    }
    return 0;
}

void it_8029FB24(Item_GObj *arg0) {
    Item_80268E5C((HSD_GObj *) arg0, 6, ITEM_ANIM_UPDATE);
}

int it_8029FB4C(HSD_GObj *arg0) {
    Item *item;
    Article *article;
    itLinkBombAttributes* sa;

    if (it_80272C6C(arg0) == 0) {
        Item_80268E5C(arg0, 6, ITEM_ANIM_UPDATE);
    }

#if TEST_REAL
    it_8029DB5C(arg0);
#else
    item = GET_ITEM(arg0);
    article = item->xC4_article_data;
    sa = article->x4_specialAttributes;
    if (item->xD44_lifeTimer <= 0.0f) {
        it_8029F69C(arg0);
    } else {
        it_8029DB5C_Inline_Matching(arg0, item, article, sa);
    }
#endif

    return 0;
}

void it_8029FCE8(HSD_GObj *gobj) {
    return;
}

int it_8029FCEC(Item_GObj *arg0) {
    it_8026E8C4(arg0, it_8029F18C, fn_8029E21C);
    return 0;
}

int it_8029FD20(Item_GObj *arg0) {
    return it_80273030(arg0);
}

int it_8029FD40(Item_GObj *arg0) {
    itColl_BounceOffVictim(arg0);
    return 0;
}

int it_8029FD64(Item_GObj *arg0) {
    return itColl_BounceOffShield(arg0);
}

void it_8029FD84(Item_GObj *arg0, Item_GObj *arg1) {
    Item* item;
    item = GET_ITEM((HSD_GObj*) arg0);
    if (item->xDD4_itemVar.linkbomb.x10 == arg1) {
        item->xDD4_itemVar.linkbomb.x10 = NULL;
    }
    it_8026B894(arg0, (HSD_GObj *) arg1);
}
