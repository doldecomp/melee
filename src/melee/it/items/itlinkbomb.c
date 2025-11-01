#include "itlinkbomb.h"

#include "baselib/random.h"
#include "ft/chara/ftLink/ftLk_AttackAir.h"
#include "ft/ft_0C31.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/itCharItems.h"
#include "it/item.h"
#include "lb/lb_00F9.h"
#include "mp/mpcoll.h"
#include "MSL/math.h"

static Vec3 it_803B8640;

ItemStateTable it_803F6888[] = {
    { 0, itLinkbomb_UnkMotion0_Anim, itLinkbomb_UnkMotion0_Phys, NULL },
    { 0, itLinkbomb_UnkMotion1_Anim, itLinkbomb_UnkMotion1_Phys,
      itLinkbomb_UnkMotion1_Coll },
    { 1, itLinkbomb_UnkMotion2_Anim, itLinkbomb_UnkMotion2_Phys,
      itLinkbomb_UnkMotion2_Coll },
    { 1, itLinkbomb_UnkMotion3_Anim, itLinkbomb_UnkMotion3_Phys,
      itLinkbomb_UnkMotion3_Coll },
    { 0, itLinkbomb_UnkMotion4_Anim, itLinkbomb_UnkMotion4_Phys,
      itLinkbomb_UnkMotion4_Coll },
    { 2, itLinkbomb_UnkMotion5_Anim, itLinkbomb_UnkMotion5_Phys,
      itLinkbomb_UnkMotion5_Coll },
    { 0, itLinkbomb_UnkMotion6_Anim, itLinkbomb_UnkMotion6_Phys,
      itLinkbomb_UnkMotion6_Coll },
};

// @todo This uses the de-duplicated function ftCo_800C6AFC
// which is likely an inline from a header file.
// Come back to this once lbcoll is matched.

static inline void fake_HSD_JObjAddTranslationY(HSD_JObj* jobj, float y)
{
    HSD_ASSERT(1114, jobj);
    jobj->translate.y += y;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        ftCo_800C6AFC(jobj);
    }
}

static inline void fake_HSD_JObjAddRotationX(HSD_JObj* jobj, float x)
{
    HSD_ASSERT(1029, jobj);
    jobj->rotate.x += x;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        ftCo_800C6AFC(jobj);
    }
}

#define TEST_REAL 0

void it_8029D968(Item_GObj* gobj)
{
    Item* item;
    item = GET_ITEM((HSD_GObj*) gobj);
    if ((item->xDC8_word.flags.x13 == false) && ((s32) item->msid != 5)) {
        it_8029F69C((HSD_GObj*) gobj);
    }
}

void it_8029D9A4(HSD_GObj* gobj, enum_t msid, Item_StateChangeFlags arg2)
{
    Item* item;
    HSD_JObj* jobj;
    f32 x;
    f32 y;
    item = HSD_GObjGetUserData(gobj);
    jobj = item->xBBC_dynamicBoneTable->bones[3];
    y = HSD_JObjGetTranslationY(jobj);
    x = HSD_JObjGetRotationX(jobj);
    if (item->xDD4_itemVar.linkbomb.x0.b0) {
        Item_80268E5C(gobj, msid, arg2 | ITEM_CMD_UPDATE);
    } else {
        Item_80268E5C(gobj, msid, arg2 | ITEM_ANIM_UPDATE);
    }
    HSD_JObjSetTranslateY(jobj, y);
    HSD_JObjSetRotationX(jobj, x);
}

static inline void it_8029DB5C_Inline_Matching(HSD_GObj* gobj, Item* item,
                                               Article* article,
                                               itLinkBombAttributes* sa)
{
    Item* item_2;
    ItemStateDesc* item_state_desc;
    HSD_GObj* temp_r31;

    f32 temp_f31;
    f32 temp_f31_2;
    HSD_JObj* temp_r31_2;

    if ((item->xD44_lifeTimer <= sa->xC) &&
        item->xDD4_itemVar.linkbomb.x0.b0 == 0)
    {
        temp_r31 = gobj->hsd_obj;
        item->xD0_itemStateDesc = &article->xC_itemStates->x0_itemStateDesc[3];
        item_state_desc = item->xD0_itemStateDesc;
        if (item_state_desc != NULL) {
            Item_80268D34(gobj, item_state_desc);
        }
        HSD_JObjAnimAll((HSD_JObj*) temp_r31);
        item->xDD4_itemVar.linkbomb.x0.b0 = true;
    }
    item->xD44_lifeTimer = item->xD44_lifeTimer - 1.0f;
    item_2 = GET_ITEM(gobj);
    if (item_2->xDD4_itemVar.linkbomb.x0.b0 == 0) {
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

static inline void it_8029DB5C_Inline_AnimAdd_Part(HSD_GObj* gobj)
{
    Item* item_2;

    f32 temp_f31;
    f32 temp_f31_2;
    HSD_JObj* temp_r31_2;

    item_2 = GET_ITEM(gobj);
    if (item_2->xDD4_itemVar.linkbomb.x0.b0 == 0) {
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

static inline void it_8029DB5C_Inline_TimerCheck_Part(HSD_GObj* gobj,
                                                      Item* item,
                                                      Article* article,
                                                      itLinkBombAttributes* sa)
{
    HSD_GObj* temp_r31;
    ItemStateDesc* item_state_desc;

    if ((item->xD44_lifeTimer <= sa->xC) &&
        item->xDD4_itemVar.linkbomb.x0.b0 == 0)
    {
        temp_r31 = gobj->hsd_obj;
        item->xD0_itemStateDesc = &article->xC_itemStates->x0_itemStateDesc[3];
        item_state_desc = item->xD0_itemStateDesc;
        if (item_state_desc != NULL) {
            Item_80268D34(gobj, item_state_desc);
        }
        HSD_JObjAnimAll((HSD_JObj*) temp_r31);
        item->xDD4_itemVar.linkbomb.x0.b0 = true;
    }
    item->xD44_lifeTimer -= 1.0F;
}

void it_8029DB5C(HSD_GObj* gobj)
{
    Item* item;
    Article* article;
    itLinkBombAttributes* sa;

    item = GET_ITEM(gobj);
    article = item->xC4_article_data;
    sa = article->x4_specialAttributes;
    if (item->xD44_lifeTimer <= 0.0f) {
        it_8029F69C(gobj);
    } else {
        it_8029DB5C_Inline_TimerCheck_Part(gobj, item, article, sa);
        it_8029DB5C_Inline_AnimAdd_Part(gobj);
    }
}

static inline void it_8029DD58_inline(Item* item, itLinkBombAttributes* attr,
                                      Item_GObj* fighter_gobj,
                                      Item_GObj* temp_r3, u8 arg2)
{
    f32 temp_f2;
    it_80275158(temp_r3, attr->lifetime);
    item->xDD4_itemVar.linkbomb.x0.b0 = false;
    item->xDD4_itemVar.linkbomb.x10 = fighter_gobj;
    item->xDD4_itemVar.linkbomb.x0.b2 = false;
    temp_f2 = attr->lifetime - attr->xC;
    item->xDD4_itemVar.linkbomb.x8 = (-2.8000002f / temp_f2) * item->scl;
    item->xDD4_itemVar.linkbomb.xC = (-0.15707964f / temp_f2) * item->scl;
    it_8026BD0C(temp_r3);
    Item_8026AB54(temp_r3, fighter_gobj, arg2);
}

HSD_GObj* it_8029DD58(Item_GObj* fighter_gobj, Vec3* arg1, u8 arg2, int arg3,
                      f32 arg4)
{
    Item_GObj* temp_r3;
    SpawnItem spawn;
    Item* item; // r26
    itLinkBombAttributes* attr;

    spawn.kind = arg3;
    spawn.prev_pos = *arg1;
    it_8026BB68(fighter_gobj, &spawn.pos);
    spawn.facing_dir = arg4;
    spawn.x3C_damage = 0;
    spawn.vel.z = 0.0F;
    spawn.vel.y = 0.0F;
    spawn.vel.x = 0.0F;
    spawn.x0_parent_gobj = (HSD_GObj*) fighter_gobj;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x44_flag.b0 = true;
    spawn.x40 = 0;
    temp_r3 = Item_80268B18(&spawn);
    if (temp_r3 != NULL) {
        item = GET_ITEM(temp_r3);
        attr = item->xC4_article_data->x4_specialAttributes;
        it_8029DD58_inline(item, attr, fighter_gobj, temp_r3, arg2);
    }
    return temp_r3;
}

void it_8029DEB0(HSD_GObj* gobj)
{
    HSD_JObj* jobj;
    Item* item;
    f32 temp_f30;
    f32 temp_f31;

    it_8029D9A4(gobj, 0, 0);
    it_8026BCF4((Item_GObj*) gobj);
}

bool itLinkbomb_UnkMotion0_Anim(HSD_GObj* gobj)
{
    Item* item;
    Article* article;
    itLinkBombAttributes* sa;
    int pad[5];

    if (it_80272C6C(gobj) == 0) {
        it_8029DEB0(gobj);
    }
#if TEST_REAL
    it_8029DB5C(gobj);
#else
    item = GET_ITEM(gobj);
    article = item->xC4_article_data;
    sa = article->x4_specialAttributes;
    if (item->xD44_lifeTimer <= 0.0f) {
        it_8029F69C(gobj);
    } else {
        it_8029DB5C_Inline_Matching(gobj, item, article, sa);
    }
#endif
    return 0;
}

void itLinkbomb_UnkMotion0_Phys(HSD_GObj* gobj)
{
    return;
}

void fn_8029E21C(HSD_GObj* gobj)
{
    int pad[2];
    it_8029D9A4(gobj, 1, 0x0);
}

bool itLinkbomb_UnkMotion1_Anim(HSD_GObj* gobj)
{
    Item* item;
    Article* article;
    itLinkBombAttributes* sa;
    f32 pad[2];

    if (it_80272C6C(gobj) == 0) {
        fn_8029E21C(gobj);
    }

#if TEST_REAL
    it_8029DB5C(gobj);
#else
    item = GET_ITEM(gobj);
    article = item->xC4_article_data;
    sa = article->x4_specialAttributes;
    if (item->xD44_lifeTimer <= 0.0f) {
        it_8029F69C(gobj);
    } else {
        it_8029DB5C_Inline_Matching(gobj, item, article, sa);
    }
#endif

    return 0;
}

void itLinkbomb_UnkMotion1_Phys(HSD_GObj* gobj)
{
    ItemAttr* temp_r4;

    temp_r4 = GET_ITEM((HSD_GObj*) gobj)->xCC_item_attr;
    it_80272860((Item_GObj*) gobj, temp_r4->x10_fall_speed,
                temp_r4->x14_fall_speed_max);
}

bool itLinkbomb_UnkMotion1_Coll(Item_GObj* gobj)
{
    it_8026E15C(gobj, it_8029F18C);
    return 0;
}

void it_8029E5D0(HSD_GObj* gobj)
{
    Item* item;
    item = GET_ITEM(gobj);
    it_80275414(gobj);
    it_802754A4((Item_GObj*) gobj);
    if (item->msid != 2) {
        it_8029D9A4(gobj, 2, ITEM_DROP_UPDATE);
    } else {
        it_8029D9A4(gobj, 2, ITEM_HIT_PRESERVE | ITEM_DROP_UPDATE);
    }
}

bool itLinkbomb_UnkMotion2_Anim(HSD_GObj* gobj)
{
    Item* item;
    Article* article;
    itLinkBombAttributes* sa;

    if (it_80272C6C(gobj) == 0) {
        item = GET_ITEM(gobj);
        it_8029E5D0(gobj);
    }

#if TEST_REAL
    it_8029DB5C(gobj);
#else
    item = GET_ITEM(gobj);
    article = item->xC4_article_data;
    sa = article->x4_specialAttributes;
    if (item->xD44_lifeTimer <= 0.0f) {
        it_8029F69C(gobj);
    } else {
        it_8029DB5C_Inline_Matching(gobj, item, article, sa);
    }
#endif

    return 0;
}

void itLinkbomb_UnkMotion2_Phys(Item_GObj* gobj)
{
    ItemAttr* temp_r4;

    temp_r4 = GET_ITEM((HSD_GObj*) gobj)->xCC_item_attr;
    it_80272860(gobj, temp_r4->x10_fall_speed, temp_r4->x14_fall_speed_max);
    it_80274658(gobj, it_804D6D28->x68_float);
}

static inline int it_LinkBomb_Inline_VelocityCompare(HSD_GObj* gobj, Vec3* vel)
{
    Item* item;
    itLinkBombAttributes* sa;
    item = GET_ITEM(gobj);
    sa = item->xC4_article_data->x4_specialAttributes;
    if ((ABS(vel->x) > sa->x24) || (ABS(vel->y) > sa->x28)) {
        it_8029F69C(gobj);
        return 1;
    } else {
        return 0;
    }
}

bool itLinkbomb_UnkMotion2_Coll(HSD_GObj* gobj)
{
    Item* item;
    s32 temp_r3;
    Vec3 vel;

    item = GET_ITEM(gobj);
    vel = item->x40_vel;
    temp_r3 = it_8026DAA8((Item_GObj*) gobj);
    if (temp_r3 & 0xF) {
        if (!it_LinkBomb_Inline_VelocityCompare(gobj, &vel) && (temp_r3 & 1)) {
            it_802762B0(item);
            it_80275D5C(gobj, &item->xC0C);
            it_8029F18C(gobj);
        }
    }
    return 0;
}

void it_8029EC34(HSD_GObj* gobj)
{
    Item* item;

    item = GET_ITEM(gobj);
    it_80275414(gobj);
    it_802754A4((Item_GObj*) gobj);
    if (item->msid != 3) {
        it_8029D9A4(gobj, 3, ITEM_DROP_UPDATE);
    } else {
        it_8029D9A4(gobj, 3, ITEM_HIT_PRESERVE | ITEM_DROP_UPDATE);
    }
}

static inline void itLinkbomb_UnkMotion1_Anim_fake_2(HSD_GObj* gobj)
{
    it_8029DB5C(gobj);
}

static inline void itLinkbomb_UnkMotion1_Anim_fake(HSD_GObj* gobj)
{
    if (it_80272C6C(gobj) == 0) {
        fn_8029E21C(gobj);
    }
    itLinkbomb_UnkMotion1_Anim_fake_2(gobj);
}

// This should have a non-inlined it_8029DB5C, presumably expanded from
// itLinkbomb_UnkMotion1_Anim, but I can't figure out how to get a match for
// itLinkbomb_UnkMotion1_Anim that calls it_8029DB5C. Not sure if that's
// related to the unused item/specialattributes.
bool itLinkbomb_UnkMotion3_Anim(HSD_GObj* gobj)
{
    Item* item;
    Article* article;
    itLinkBombAttributes* sa;

    item = GET_ITEM(gobj);
    article = item->xC4_article_data;
    sa = article->x4_specialAttributes;

    if (it_80272C6C(gobj) == 0) {
        it_8029EC34(gobj);
    }
    itLinkbomb_UnkMotion1_Anim_fake(gobj);
    return 0;
}

void itLinkbomb_UnkMotion3_Phys(Item_GObj* gobj)
{
    ItemAttr* temp_r4;
    temp_r4 = GET_ITEM(gobj)->xCC_item_attr;
    it_80272860(gobj, temp_r4->x10_fall_speed, temp_r4->x14_fall_speed_max);
    it_80274658(gobj, it_804D6D28->x68_float);
}

bool itLinkbomb_UnkMotion3_Coll(HSD_GObj* gobj)
{
    GET_ITEM(gobj);
    itLinkbomb_UnkMotion2_Coll(gobj);
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

void it_8029F18C(HSD_GObj* gobj)
{
    Item* item;
    s32 temp_r0;

    item = gobj->user_data;

    temp_r0 = item->msid;
    if ((temp_r0 != 6) || (temp_r0 != 4)) {
        item->xDD4_itemVar.linkbomb.x4 = fsign_inline(item->x40_vel.x);
        mpCollSetFacingDir(
            &item->x378_itemColl,
            float_sign_int_inline(item->xDD4_itemVar.linkbomb.x4));
        item->xDD4_itemVar.linkbomb.x0.b1 = true;
    } else {
        item->xDD4_itemVar.linkbomb.x0.b1 = false;
        item->x40_vel.z = 0.0f;
        item->x40_vel.y = 0.0f;
        item->x40_vel.x = 0.0f;
    }

    it_8029D9A4(gobj, 4, 0);
}

// This regswap may or may not be related to the fake inline for it_8029DB5C,
// but every other function matches with it.
bool itLinkbomb_UnkMotion4_Anim(HSD_GObj* gobj)
{
    Article* article;
    Item* item;
    itLinkBombAttributes* sa;

    if (it_80272C6C(gobj) == 0) {
        it_8029F18C(gobj);
    }

#if TEST_REAL
    it_8029DB5C(gobj);
#else
    item = GET_ITEM(gobj);
    article = item->xC4_article_data;
    sa = article->x4_specialAttributes;
    if (item->xD44_lifeTimer <= 0.0F) {
        it_8029F69C(gobj);
    } else {
        it_8029DB5C_Inline_Matching(gobj, item, article, sa);
    }
#endif

    return 0;
}

void itLinkbomb_UnkMotion4_Phys(HSD_GObj* gobj)
{
    f32 temp_f2;
    Item* item;
    itLinkBombAttributes* sa;
    f32 zero = 0.0F;

    item = GET_ITEM(gobj);
    sa = item->xC4_article_data->x4_specialAttributes;
    if (item->xDD4_itemVar.linkbomb.x0.b1) {
        temp_f2 = item->x40_vel.x;
        if (temp_f2 != zero) {
            item->x40_vel.x =
                (sa->x2C * item->xDD4_itemVar.linkbomb.x4) + temp_f2;
        }
        if (ABS(item->x40_vel.x) < sa->x30) {
            item->x40_vel.x = zero;
        }
    }
}

bool itLinkbomb_UnkMotion4_Coll(Item_GObj* gobj)
{
    it_8026D62C(gobj, fn_8029E21C);
    return 0;
}

void it_8029F69C(HSD_GObj* gobj)
{
    HSD_GObj* temp_r0;
    HSD_GObj* temp_r3;
    HSD_JObj* jobj;
    Item* item;
    int pad[2];
    Vec3 item_pos;
    Vec3 const_vec;

    item = GET_ITEM(gobj);
    jobj = HSD_GObjGetHSDObj(gobj);
    it_80275444((Item_GObj*) gobj);
    if (item->xDC8_word.flags.x13) {
        const_vec = it_803B8640;
        it_8027429C(gobj, &const_vec);
        it_802756D0(gobj);
        temp_r0 = item->owner;
        if (temp_r0 != NULL) {
            temp_r3 = (HSD_GObj*) item->xDD4_itemVar.linkbomb.x10;
            if (temp_r0 == temp_r3) {
                ftLk_AttackAir_SetupParts(temp_r3);
            }
        }
    }
    it_8026B3A8((Item_GObj*) gobj);
    it_80273454((Item_GObj*) gobj);
    HSD_JObjSetFlagsAll(jobj, 0x10U);
    it_8026BD24((Item_GObj*) gobj);
    it_8027518C((Item_GObj*) gobj);
    it_802756D0(gobj);
    it_80272A60((Item_GObj*) gobj);
    it_8029D9A4(gobj, 5, 0x0); // inline
    item_pos = item->pos;
    lb_800119DC(&item_pos, 0x78, 1.0f, 0.02f, 1.0471976f);
}

bool itLinkbomb_UnkMotion5_Anim(Item_GObj* gobj)
{
    return it_802751D8(gobj);
}

void itLinkbomb_UnkMotion5_Phys(HSD_GObj* gobj)
{
    return;
}

bool itLinkbomb_UnkMotion5_Coll(HSD_GObj* gobj)
{
    return 0;
}

bool it_8029F960(Item_GObj* gobj)
{
    Item* item;
    Item* item_2;
    s32 temp_r3;
    itLinkBombAttributes* sa;

    item = GET_ITEM(gobj);
    if (item->msid != 5) {
        if (!it_LinkBomb_Inline_VelocityCompare(gobj, &item->x40_vel)) {
            item_2 = GET_ITEM(gobj);
            sa = item_2->xC4_article_data->x4_specialAttributes;
            item_2->facing_dir = -item_2->facing_dir;
            item_2->x40_vel.x = sa->x1C * item_2->facing_dir;
            item_2->x40_vel.y = sa->x20;
        }
    }
    return 0;
}

bool it_2725_Logic16_DmgReceived(Item_GObj* gobj)
{
    Item* item;
    f32 temp_f1;
    itLinkBombAttributes* sa;
    f32 pad[2];

    item = GET_ITEM((HSD_GObj*) gobj);
    sa = item->xC4_article_data->x4_specialAttributes;
    if (item->msid != 5) {
        if (item->xCA0 >= sa->x10) {
            it_8029F69C((HSD_GObj*) gobj);
        } else if (!item->xDD4_itemVar.linkbomb.x0.b2) {
            if (item->x40_vel.x > sa->x30) {
                item->facing_dir = -item->xCCC_incDamageDirection;
                item->x40_vel.x = sa->x14 * item->facing_dir;
            } else {
                temp_f1 = 2.0f * (HSD_Randf() - 0.5f);
                item->x40_vel.x = sa->x14 * temp_f1;
                // it_80272980(gobj, temp_f1);
                it_80272980(gobj);
            }
            item->x40_vel.y = sa->x18 * item->facing_dir;
            item->xDD4_itemVar.linkbomb.x0.b2 = true;
        }
    }
    return 0;
}

void it_2725_Logic16_EnteredAir(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 6, ITEM_ANIM_UPDATE);
}

bool itLinkbomb_UnkMotion6_Anim(HSD_GObj* gobj)
{
    Item* item;
    Article* article;
    itLinkBombAttributes* sa;

    if (it_80272C6C(gobj) == 0) {
        Item_80268E5C(gobj, 6, ITEM_ANIM_UPDATE);
    }

#if TEST_REAL
    it_8029DB5C(gobj);
#else
    item = GET_ITEM(gobj);
    article = item->xC4_article_data;
    sa = article->x4_specialAttributes;
    if (item->xD44_lifeTimer <= 0.0f) {
        it_8029F69C(gobj);
    } else {
        it_8029DB5C_Inline_Matching(gobj, item, article, sa);
    }
#endif

    return 0;
}

void itLinkbomb_UnkMotion6_Phys(HSD_GObj* gobj)
{
    return;
}

bool itLinkbomb_UnkMotion6_Coll(Item_GObj* gobj)
{
    it_8026E8C4(gobj, it_8029F18C, fn_8029E21C);
    return 0;
}

bool it_2725_Logic16_Reflected(Item_GObj* gobj)
{
    return it_80273030(gobj);
}

bool it_2725_Logic16_HitShield(Item_GObj* gobj)
{
    itColl_BounceOffVictim(gobj);
    return 0;
}

bool it_2725_Logic16_ShieldBounced(Item_GObj* gobj)
{
    return itColl_BounceOffShield(gobj);
}

void it_8029FD84(Item_GObj* gobj, Item_GObj* arg1)
{
    Item* item;
    item = GET_ITEM((HSD_GObj*) gobj);
    if (item->xDD4_itemVar.linkbomb.x10 == arg1) {
        item->xDD4_itemVar.linkbomb.x10 = NULL;
    }
    it_8026B894(gobj, arg1);
}
