#include "baselib/random.h"

#include "mp/mpcoll.h"

#include "lb/lb_00F9.h"

#include "ft/chara/ftLink/ftLk_AttackAir.h"

#include "ft/ft_0C31.h"

#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"

#include "itlinkbomb.h"

#include "it/itCharItems.h"
#include "it/inlines.h"
#include "it/item.h"
// #include "it/it_26B1.h"

// void it_80272A60(Item_GObj *);                         /* extern */
// void it_80275414(HSD_GObj *);                          /* extern */
// void it_802754A4(Item_GObj *);                         /* extern */
// void it_80275D5C(HSD_GObj *, ECB *);                   /* extern */

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

static inline it_LinkBomb_Inline(HSD_GObj *arg0, Item *item, Article *article, itLinkBombAttributes *sa)
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
        fake_HSD_JObjAddTranslationY(temp_r31_2, temp_f31);
        temp_f31_2 = item_2->xDD4_itemVar.linkbomb.xC;
        fake_HSD_JObjAddRotationX(temp_r31_2, temp_f31_2);
    }
}

void it_8029D968(Item_GObj *arg0) {
    Item *temp_r4;

    temp_r4 = arg0->user_data;
    if (!(((u8) temp_r4->xDC8_word.flags.x13 >> 4U) & 1) && ((s32) temp_r4->msid != 5)) {
        // could be empty?
        it_8029F69C((HSD_GObj *) arg0);
    }
}

static inline void it_LinkBomb_Inline_2(HSD_GObj *arg0, enum_t msid, Item_StateChangeFlags arg2)
{
    Item *item;
    HSD_JObj *jobj;
    f32 x;
    f32 y;
    item = arg0->user_data;
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

// TODO: figure out what this is
static void it_8029D9A4(HSD_GObj *arg0, enum_t msid, Item_StateChangeFlags arg2)
{
#if 1
    it_LinkBomb_Inline_2(arg0, msid, arg2);
#else
    Item *item;
    HSD_JObj *jobj;
    f32 x;
    f32 y;
    item = arg0->user_data;
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
#endif
}

void it_8029DB5C(HSD_GObj *arg0) {
    HSD_JObj *temp_r31_2;
    ItemStateDesc *item_state_desc;
    f32 temp_f31;
    f32 temp_f31_2;
    Item *item;
    Item *item_2;
    HSD_GObj *temp_r31;
    Article *article;
    itLinkBombAttributes* sa;
    f32 pad[4];

    // item: r30
    // article: r4
    item = GET_ITEM(arg0);
    article = item->xC4_article_data;

    sa = article->x4_specialAttributes;
    if (item->xD44_lifeTimer <= 0.0f) {
        it_8029F69C(arg0);
        return;
    }
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
    item_2 = arg0->user_data;
    if (item->xDD4_itemVar.linkbomb.x0.bits.b0 == 0) {
        temp_f31 = item_2->xDD4_itemVar.linkbomb.x4;
        temp_r31_2 = item_2->xBBC_dynamicBoneTable->bones[3];
        HSD_JObjAddTranslationY(temp_r31_2, temp_f31);
        temp_f31_2 = item_2->xDD4_itemVar.linkbomb.xC;
        fake_HSD_JObjAddRotationX(temp_r31_2, temp_f31_2);
    }
}

HSD_GObj *it_8029DD58(Item_GObj *fighter_gobj, Vec3 *arg1, u8 arg2, s32 arg3, f32 arg4) {
    Item *item; // r26
    Item_GObj *temp_r3;
    f32 temp_f2;
    itLinkBombAttributes *attr;
    SpawnItem spawn;

    spawn.kind = arg3;
    spawn.prev_pos = *arg1;
    it_8026BB68(fighter_gobj, &spawn.pos);
    spawn.facing_dir = arg4;
    spawn.x3C_damage = 0;
    spawn.vel.z = 0.0f;
    spawn.vel.y = 0.0f;
    spawn.vel.x = 0.0f;
    spawn.x0_parent_gobj = fighter_gobj;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x44_flag.bits.b0 = true;
    spawn.x40 = 0;
    temp_r3 = Item_80268B18(&spawn);
    if (temp_r3 != NULL) {
        item = GET_ITEM(temp_r3->user_data);
        attr = item->xC4_article_data->x4_specialAttributes;
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
    return (HSD_GObj *) temp_r3;
}

void it_8029DEB0(Item_GObj *arg0) {
    HSD_JObj *jobj;
    Item *item;
    f32 temp_f30;
    f32 temp_f31;
    f32 pad[8];

    item = GET_ITEM(arg0);
    jobj = item->xBBC_dynamicBoneTable->bones[3];

    temp_f31 = HSD_JObjGetTranslationY(jobj);
    temp_f30 = HSD_JObjGetRotationX(jobj);
    if (item->xDD4_itemVar.linkbomb.x0.bits.b0) {
        Item_80268E5C((HSD_GObj *) arg0, 0, ITEM_CMD_UPDATE);
    } else {
        Item_80268E5C((HSD_GObj *) arg0, 0, ITEM_ANIM_UPDATE);
    }
    HSD_JObjSetTranslateY(jobj, temp_f31);
    HSD_JObjSetRotationX(jobj, temp_f30);
    it_8026BCF4(arg0);
}

int it_8029E074(HSD_GObj *arg0) {
    Item *item;
    Article *article;
    itLinkBombAttributes* sa;
    int pad[5];

    if (it_80272C6C(arg0) == 0) {
        it_8029D9A4(arg0, 0, 0);
        it_8026BCF4((Item_GObj *) arg0);
    }
    item = arg0->user_data;
    article = item->xC4_article_data;
    sa = article->x4_specialAttributes;
    if (item->xD44_lifeTimer <= 0.0f) {
        it_8029F69C(arg0);
    } else {
        it_LinkBomb_Inline(arg0, item, article, sa);
    }
    return 0;
}

void it_8029E218(HSD_GObj *arg0) {
    return;
}

void fn_8029E21C(HSD_GObj *arg0) {
    f32 pad[3];

    it_LinkBomb_Inline_2(arg0, 1, 0x0);
}

int it_8029E3D8(HSD_GObj *arg0) {
    Item *item;
    Article *article;
    itLinkBombAttributes* sa;
    f32 pad[2];

    if (it_80272C6C(arg0) == 0) {
        it_8029D9A4(arg0, 1, 0);
    }

    item = GET_ITEM(arg0);
    article = item->xC4_article_data;
    sa = article->x4_specialAttributes;

    if (item->xD44_lifeTimer <= 0.0f) {
        it_8029F69C(arg0);
    } else {
        it_LinkBomb_Inline(arg0, item, article, sa);
    }
    return 0;
}

void it_8029E574(Item_GObj *arg0) {
    ItemAttr *temp_r4;

    temp_r4 = GET_ITEM(arg0)->xCC_item_attr;
    it_80272860(arg0, temp_r4->x10_fall_speed, temp_r4->x14_fall_speed_max);
}

int it_8029E5A4(Item_GObj *arg0) {
    it_8026E15C(arg0, it_8029F18C);
    return 0;
}

void it_8029E5D0(Item_GObj *arg0) {
    Item *item;
    f32 pad[2];

    item = GET_ITEM(arg0);
    it_80275414((HSD_GObj*) arg0);
    it_802754A4(arg0);
    if ((s32) item->msid != 2) {
        it_LinkBomb_Inline_2(arg0, 2, ITEM_DROP_UPDATE);
    } else {
        it_LinkBomb_Inline_2(arg0, 2, ITEM_HIT_PRESERVE | ITEM_DROP_UPDATE);
    }
}

int it_8029E920(HSD_GObj *arg0) {
    Item *item;
    Article *article;
    itLinkBombAttributes* sa;
    f32 pad[2];


    if (it_80272C6C(arg0) == 0) {
        item = GET_ITEM(arg0);
        it_80275414(arg0);
        it_802754A4((Item_GObj *) arg0);
        if ((s32) item->msid != 2) {
            it_8029D9A4(arg0, 2, 4);
        } else {
            it_8029D9A4(arg0, 2, 0x14);
        }
    }

    item = GET_ITEM(arg0);
    article = item->xC4_article_data;
    sa = article->x4_specialAttributes;

    if (item->xD44_lifeTimer <= 0.0f) {
        it_8029F69C(arg0);
    } else {
        it_LinkBomb_Inline(arg0, item, article, sa);
    }

    return 0;
}

void it_8029EAF0(Item_GObj *arg0) {
    ItemAttr *temp_r4;

    temp_r4 = GET_ITEM(arg0)->xCC_item_attr;
    it_80272860(arg0, temp_r4->x10_fall_speed, temp_r4->x14_fall_speed_max);
    it_80274658((HSD_GObj *) arg0, it_804D6D28->x68_float);
}

int it_8029EB3C(HSD_GObj *arg0) {
    Vec3 vel;
    Item *item;
    f32 temp_r4;
    f32 var_f1;
    f32 var_f1_2;
    s32 temp_r3;
    s32 var_r0;
    itLinkBombAttributes *sa;
    int i;

    item = GET_ITEM(arg0);
    vel = item->x40_vel;
    temp_r3 = it_8026DAA8(vel.x, arg0);
    if (temp_r3 & 0xF) {
        sa = item->xC4_article_data->x4_specialAttributes;
        var_r0 = 0;
#if 1
        for (i = 0; i < 2; i++) {
            var_f1 = ((f32 *)&vel)[i];
            if (var_f1 < 0.0f) {
                var_f1 = -var_f1;
            }
            // TODO: vel is in wrong address!
            if (var_f1 > sa->vel[i]) {
                it_8029F69C(arg0);
                var_r0 = 1;
                break;
            } else {
                var_r0 = 0;
            }
        }
#else
        var_f1 = vel.x;
        var_f1_2 = vel.y;
        if (var_f1 < 0.0f) {
            var_f1 = -var_f1;
        }
        if (var_f1_2 < 0.0f) {
            var_f1_2 = -var_f1_2;
        }
        if (var_f1 > sa->vel[0]) {
            it_8029F69C(arg0);
            var_r0 = 1;
        }
        else if (var_f1_2 > sa->vel[1]) {
            it_8029F69C(arg0);
            var_r0 = 1;
        }
#endif
        if ((var_r0 == 0) && (temp_r3 & 1)) {
            it_802762B0(item);
            it_80275D5C(arg0, &item->xC0C);
            it_8029F18C(arg0);
        }
    }
    return 0;
}

#if 0
s32 it_8029EB3C(HSD_GObj *arg0) {
    f32 sp20;
    f32 sp1C;
    f32 sp18;
    Item *temp_r5;
    f32 temp_r4;
    f32 var_f1;
    f32 var_f1_2;
    s32 temp_r3;
    s32 var_r0;
    void *temp_r3_2;

    temp_r5 = arg0->user_data;
    temp_r4 = temp_r5->x40_vel.x;
    sp18 = temp_r4;
    sp1C = temp_r5->x40_vel.y;
    sp20 = temp_r5->x40_vel.z;
    temp_r3 = it_8026DAA8(temp_r4, temp_r5);
    if (temp_r3 & 0xF) {
        var_f1 = sp18;
        temp_r3_2 = arg0->user_data->xC4_article_data->x4_specialAttributes;
        if (var_f1 < 0.0f) {
            var_f1 = -var_f1;
        }
        if (!(var_f1 > temp_r3_2->unk24)) {
            var_f1_2 = sp1C;
            if (var_f1_2 < 0.0f) {
                var_f1_2 = -var_f1_2;
            }
            if (var_f1_2 > temp_r3_2->unk28) {
                goto block_7;
            }
            var_r0 = 0;
        } else {
block_7:
            it_8029F69C(arg0);
            var_r0 = 1;
        }
        if ((var_r0 == 0) && (temp_r3 & 1)) {
            it_802762B0(temp_r5);
            it_80275D5C(arg0, &temp_r5->xC0C);
            it_8029F18C(arg0);
        }
    }
    return 0;
}
#endif

void it_8029EC34(Item_GObj *arg0) {
    Item *item;
    f32 pad[2];

    item = arg0->user_data;
    it_80275414((HSD_GObj*) arg0);
    it_802754A4(arg0);
    if (item->msid != 3) {
        it_LinkBomb_Inline_2(arg0, 3, ITEM_DROP_UPDATE);
    } else {
        it_LinkBomb_Inline_2(arg0, 3, ITEM_HIT_PRESERVE | ITEM_DROP_UPDATE);
    }
}


int it_8029EF84(HSD_GObj *arg0) {
    Item *item;
    f32 pad[5];

    if (it_80272C6C(arg0) == 0) {
        item = GET_ITEM(arg0);
        it_80275414(arg0);
        it_802754A4((Item_GObj *) arg0);
        if (item->msid != 3) {
            it_8029D9A4(arg0, 3, ITEM_DROP_UPDATE);
        } else {
            it_8029D9A4(arg0, 3, ITEM_HIT_PRESERVE | ITEM_DROP_UPDATE);
        }
    }
    if (it_80272C6C(arg0) == 0) {
        it_8029D9A4(arg0, 1, 0);
    }
    it_8029DB5C(arg0);
    return 0;
}

void it_8029F04C(Item_GObj *arg0) {
    ItemAttr *temp_r4;

    temp_r4 = GET_ITEM(arg0)->xCC_item_attr;
    it_80272860(arg0, temp_r4->x10_fall_speed, temp_r4->x14_fall_speed_max);
    it_80274658((HSD_GObj *) arg0, it_804D6D28->x68_float);
}

#if 0

s32 it_8029F098(HSD_GObj *arg0) {
    f32 sp24;
    f32 sp20;
    f32 sp1C;
    Item *temp_r30;
    f32 temp_r4;
    f32 var_f1;
    f32 var_f1_2;
    s32 temp_r3;
    s32 var_r0;
    void *temp_r3_2;

    temp_r30 = arg0->user_data;
    temp_r4 = temp_r30->x40_vel.x;
    sp1C = temp_r4;
    sp20 = temp_r30->x40_vel.y;
    sp24 = temp_r30->x40_vel.z;
    temp_r3 = it_8026DAA8(temp_r4);
    if (temp_r3 & 0xF) {
        var_f1 = sp1C;
        temp_r3_2 = arg0->user_data->xC4_article_data->x4_specialAttributes;
        if (var_f1 < 0.0f) {
            var_f1 = -var_f1;
        }
        if (!(var_f1 > temp_r3_2->unk24)) {
            var_f1_2 = sp20;
            if (var_f1_2 < 0.0f) {
                var_f1_2 = -var_f1_2;
            }
            if (var_f1_2 > temp_r3_2->unk28) {
                goto block_7;
            }
            var_r0 = 0;
        } else {
block_7:
            it_8029F69C(arg0);
            var_r0 = 1;
        }
        if ((var_r0 == 0) && (temp_r3 & 1)) {
            it_802762B0(temp_r30);
            it_80275D5C(arg0, &temp_r30->xC0C);
            it_8029F18C(arg0);
        }
    }
    return 0;
}

#endif

void it_8029F18C(HSD_GObj *gobj) {
    f32 var_f0;
    s32 temp_r0;
    s32 var_r4;
    Item *item;
    f32 pad[2];

    // likely another inline
    item = gobj->user_data;
    temp_r0 = item->msid;
    if ((temp_r0 != 6) || (temp_r0 != 4)) {
        if (item->x40_vel.x >= 0.0f) {
            var_f0 = 1.0f;
        } else {
            var_f0 = -1.0f;
        }
        item->xDD4_itemVar.linkbomb.x4 = var_f0;
        if (item->xDD4_itemVar.linkbomb.x4 == -1.0f) {
            var_r4 = -1;
        } else {
            var_r4 = 1;
        }
        mpColl_800436D8(&item->x378_itemColl, var_r4);
        item->xDD4_itemVar.linkbomb.x0.bits.b1 = true;
    } else {
        item->xDD4_itemVar.linkbomb.x0.bits.b1 = false;
        item->x40_vel.z = 0.0f;
        item->x40_vel.y = 0.0f;
        item->x40_vel.x = 0.0f;
    }
    it_LinkBomb_Inline_2(gobj, 4, 0);
}

int it_8029F3DC(HSD_GObj *gobj) {
    f32 var_f0;
    s32 temp_r0;
    s32 var_r4;
    Item *item;
    Article *article;
    itLinkBombAttributes* sa;
    f32 pad[2];

    if (it_80272C6C(gobj) == 0) {
        item = gobj->user_data;
        temp_r0 = item->msid;
        if ((temp_r0 != 6) || (temp_r0 != 4)) {
            if (item->x40_vel.x >= 0.0f) {
                var_f0 = 1.0f;
            } else {
                var_f0 = -1.0f;
            }
            item->xDD4_itemVar.linkbomb.x4 = var_f0;
            if (item->xDD4_itemVar.linkbomb.x4 == -1.0f) {
                var_r4 = -1;
            } else {
                var_r4 = 1;
            }
            mpColl_800436D8(&item->x378_itemColl, var_r4);
            item->xDD4_itemVar.linkbomb.x0.bits.b1 = true;
        } else {
            item->xDD4_itemVar.linkbomb.x0.bits.b1 = false;
            item->x40_vel.z = 0.0f;
            item->x40_vel.y = 0.0f;
            item->x40_vel.x = 0.0f;
        }
        it_8029D9A4(gobj, 4, 0);
        article = item->xC4_article_data;
        sa = article->x4_specialAttributes;
        if (item->xD44_lifeTimer <= 0.0f) {
            it_8029F69C(gobj);
        } else {
            it_LinkBomb_Inline(gobj, item, article, sa);
        }
    }
    return 0;
}

#if 0

s32 it_8029F3DC(HSD_GObj *arg0) {
    HSD_JObj *temp_r30_3;
    ItemStateDesc *temp_r4_2;
    f32 temp_f2;
    f32 temp_f31;
    f32 temp_f31_2;
    f32 var_f0;
    s32 temp_r0;
    s32 var_r4;
    void *temp_r29;
    void *temp_r29_2;
    Item *temp_r30;
    Item *temp_r30_2;
    void *temp_r4;

    if (it_80272C6C(arg0) == 0) {
        temp_r30 = arg0->user_data;
        temp_r0 = temp_r30->unk24;
        if ((temp_r0 != 6) || (temp_r0 != 4)) {
            M2C_ERROR(/* unknown instruction: cror eq, gt, eq */);
            if (temp_r30->unk40 == 0.0f) {
                var_f0 = 1.0f;
            } else {
                var_f0 = -1.0f;
            }
            temp_r30->unkDD8 = var_f0;
            if (temp_r30->unkDD8 == -1.0f) {
                var_r4 = -1;
            } else {
                var_r4 = 1;
            }
            mpColl_800436D8(temp_r30 + 0x378, var_r4);
            temp_r30->xDD4_itemVar.linkbomb.x0 = (u8) (temp_r30->xDD4_itemVar.linkbomb.x0 | 0x40);
        } else {
            temp_r30->xDD4_itemVar.linkbomb.x0 = (u8) (temp_r30->xDD4_itemVar.linkbomb.x0 & ~0x40);
            temp_r30->unk48 = 0.0f;
            temp_r30->unk44 = 0.0f;
            temp_r30->unk40 = 0.0f;
        }
        it_8029D9A4(arg0, 4, 0);
    }
    temp_r29 = arg0->user_data;
    temp_f2 = temp_r29->xD44_lifeTimer;
    temp_r4 = temp_r29->xC4_article_data;
    M2C_ERROR(/* unknown instruction: cror eq, lt, eq */);
    if (temp_f2 == 0.0f) {
        it_8029F69C(arg0);
    } else {
        M2C_ERROR(/* unknown instruction: cror eq, lt, eq */);
        if ((temp_f2 == (f32) temp_r4->unk4->unkC) && !(((u8) temp_r29->xDD4_itemVar.linkbomb.x0 >> 7U) & 1)) {
            temp_r30_2 = arg0->hsd_obj;
            temp_r29->unkD0 = (ItemStateDesc *) (temp_r4->unkC + 0x30);
            temp_r4_2 = temp_r29->unkD0;
            if (temp_r4_2 != NULL) {
                Item_80268D34(arg0, temp_r4_2);
            }
            HSD_JObjAnimAll((HSD_JObj *) temp_r30_2);
            temp_r29->xDD4_itemVar.linkbomb.x0 = (u8) (temp_r29->xDD4_itemVar.linkbomb.x0 | 0x80);
        }
        temp_r29->xD44_lifeTimer = (f32) (temp_r29->xD44_lifeTimer - 1.0f);
        temp_r29_2 = arg0->user_data;
        if (!(((u8) temp_r29_2->xDD4_itemVar.linkbomb.x0 >> 7U) & 1)) {
            temp_f31 = temp_r29_2->unkDDC;
            temp_r30_3 = temp_r29_2->unkBBC->unkC;
            if (temp_r30_3 == NULL) {
                __assert(it_804D5380, 0x45AU, it_804D5388);
            }
            temp_r30_3->translate.y += temp_f31;
            if (!(temp_r30_3->flags & 0x02000000)) {
                ftCo_800C6AFC(temp_r30_3);
            }
            temp_f31_2 = temp_r29_2->unkDE0;
            if (temp_r30_3 == NULL) {
                __assert(it_804D5380, 0x405U, it_804D5388);
            }
            temp_r30_3->rotate.x += temp_f31_2;
            if (!(temp_r30_3->flags & 0x02000000)) {
                ftCo_800C6AFC(temp_r30_3);
            }
        }
    }
    return 0;
}


void it_8029F60C(void *arg0) {
    f32 temp_f2;
    f32 var_f1;
    void *temp_r3;
    void *temp_r4;

    temp_r4 = arg0->unk2C;
    temp_r3 = temp_r4->xC4_article_data->unk4;
    if (((u8) temp_r4->xDD4_itemVar.linkbomb.x0 >> 6U) & 1) {
        temp_f2 = temp_r4->unk40;
        if (temp_f2 != 0.0f) {
            temp_r4->unk40 = (f32) ((temp_r3->unk2C * temp_r4->unkDD8) + temp_f2);
        }
        var_f1 = temp_r4->unk40;
        if (var_f1 < 0.0f) {
            var_f1 = -var_f1;
        }
        if (var_f1 < temp_r3->unk30) {
            temp_r4->unk40 = 0.0f;
        }
    }
}

s32 it_8029F670(Item_GObj *arg0) {
    it_8026D62C(arg0, fn_8029E21C);
    return 0;
}

#endif
void it_8029F69C(Item_GObj *arg0) {
    HSD_GObj *temp_r0;
    HSD_GObj *temp_r3;
    HSD_JObj *jobj;
    Item *jobj_2;
    Item *item;
    Vec3 const_vec;
    Vec3 item_pos;
    f32 pad[2];

    item = GET_ITEM(arg0);
    jobj = arg0->hsd_obj;
    it_80275444(arg0);
    if (item->xDC8_word.flags.x13) {
        // investigate this
        const_vec = it_803B8640;
        it_8027429C((HSD_GObj *) arg0, &const_vec);
        it_802756D0((HSD_GObj *) arg0);
        temp_r0 = item->owner;
        if (temp_r0 != NULL) {
            temp_r3 = item->xDD4_itemVar.linkbomb.x10;
            if (temp_r0 == temp_r3) {
                ftLk_AttackAir_SetupParts(temp_r3);
            }
        }
    }
    it_8026B3A8(arg0);
    it_80273454(arg0);
    HSD_JObjSetFlagsAll(jobj, 0x10U);
    it_8026BD24(arg0);
    it_8027518C(arg0);
    it_802756D0((HSD_GObj *) arg0);
    it_80272A60(arg0);
    it_LinkBomb_Inline_2((HSD_GObj *)arg0, 5, 0x0);
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

#if 0
s32 it_8029F960(Item_GObj *arg0) {
    Item *temp_r4;
    Item *temp_r4_2;
    f32 var_f1;
    f32 var_f1_2;
    s32 var_r0;
    void *temp_r3;
    void *temp_r3_2;

    temp_r4 = arg0->user_data;
    if ((s32) temp_r4->msid != 5) {
        var_f1 = temp_r4->x40_vel.x;
        temp_r3 = temp_r4->xC4_article_data->x4_specialAttributes;
        if (var_f1 < 0.0f) {
            var_f1 = -var_f1;
        }
        if (!(var_f1 > temp_r3->unk24)) {
            var_f1_2 = temp_r4->x40_vel.y;
            if (var_f1_2 < 0.0f) {
                var_f1_2 = -var_f1_2;
            }
            if (var_f1_2 > temp_r3->unk28) {
                goto block_7;
            }
            var_r0 = 0;
        } else {
block_7:
            it_8029F69C((HSD_GObj *) arg0);
            var_r0 = 1;
        }
        if (var_r0 == 0) {
            temp_r4_2 = arg0->user_data;
            temp_r3_2 = temp_r4_2->xC4_article_data->x4_specialAttributes;
            temp_r4_2->facing_dir = -temp_r4_2->facing_dir;
            temp_r4_2->x40_vel.x = temp_r3_2->unk1C * temp_r4_2->facing_dir;
            temp_r4_2->x40_vel.y = temp_r3_2->unk20;
        }
    }
    return 0;
}
#endif

int it_8029FA30(Item_GObj *arg0) {
    Item *item;
    f32 temp_f1;
    itLinkBombAttributes *sa;
    f32 pad[2];

    item = arg0->user_data;
    sa = item->xC4_article_data->x4_specialAttributes;
    if (item->msid != 5) {
        if (item->xCA0 >= sa->x10) {
            it_8029F69C((HSD_GObj *) arg0);
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

#if 0
void it_8029FB24(Item_GObj *arg0) {
    Item_80268E5C((HSD_GObj *) arg0, 6, ITEM_ANIM_UPDATE);
}

s32 it_8029FB4C(HSD_GObj *arg0) {
    HSD_JObj *temp_r31_2;
    ItemStateDesc *temp_r4_2;
    f32 temp_f2;
    f32 temp_f31;
    f32 temp_f31_2;
    Item *temp_r30;
    Item *temp_r30_2;
    void *temp_r31;
    void *temp_r4;

    if (it_80272C6C(arg0) == 0) {
        Item_80268E5C(arg0, 6, ITEM_ANIM_UPDATE);
    }
    temp_r30 = arg0->user_data;
    temp_f2 = temp_r30->xD44_lifeTimer;
    temp_r4 = temp_r30->xC4_article_data;
    M2C_ERROR(/* unknown instruction: cror eq, lt, eq */);
    if (temp_f2 == 0.0f) {
        it_8029F69C(arg0);
    } else {
        M2C_ERROR(/* unknown instruction: cror eq, lt, eq */);
        if ((temp_f2 == (f32) temp_r4->unk4->unkC) && !(((u8) temp_r30->xDD4_itemVar.linkbomb.x0 >> 7U) & 1)) {
            temp_r31 = arg0->hsd_obj;
            temp_r30->unkD0 = (ItemStateDesc *) (temp_r4->unkC + 0x30);
            temp_r4_2 = temp_r30->unkD0;
            if (temp_r4_2 != NULL) {
                Item_80268D34(arg0, temp_r4_2);
            }
            HSD_JObjAnimAll((HSD_JObj *) temp_r31);
            temp_r30->xDD4_itemVar.linkbomb.x0 = (u8) (temp_r30->xDD4_itemVar.linkbomb.x0 | 0x80);
        }
        temp_r30->xD44_lifeTimer = (f32) (temp_r30->xD44_lifeTimer - 1.0f);
        temp_r30_2 = arg0->user_data;
        if (!(((u8) temp_r30_2->xDD4_itemVar.linkbomb.x0 >> 7U) & 1)) {
            temp_f31 = temp_r30_2->unkDDC;
            temp_r31_2 = temp_r30_2->unkBBC->unkC;
            if (temp_r31_2 == NULL) {
                __assert(it_804D5380, 0x45AU, it_804D5388);
            }
            temp_r31_2->translate.y += temp_f31;
            if (!(temp_r31_2->flags & 0x02000000)) {
                ftCo_800C6AFC(temp_r31_2);
            }
            temp_f31_2 = temp_r30_2->unkDE0;
            if (temp_r31_2 == NULL) {
                __assert(it_804D5380, 0x405U, it_804D5388);
            }
            temp_r31_2->rotate.x += temp_f31_2;
            if (!(temp_r31_2->flags & 0x02000000)) {
                ftCo_800C6AFC(temp_r31_2);
            }
        }
    }
    return 0;
}

void it_8029FCE8(void) {

}

s32 it_8029FCEC(Item_GObj *arg0) {
    it_8026E8C4(arg0, it_8029F18C, fn_8029E21C);
    return 0;
}

s32 it_8029FD20(Item_GObj *arg0) {
    return it_80273030(arg0);
}

s32 it_8029FD40(Item_GObj *arg0) {
    itColl_BounceOffVictim(arg0);
    return 0;
}

s32 it_8029FD64(Item_GObj *arg0) {
    return itColl_BounceOffShield(arg0);
}

void it_8029FD84(Item_GObj *arg0, Item_GObj *arg1) {
    Item *temp_r5;

    temp_r5 = arg0->user_data;
    if ((bitwise u32) temp_r5->xDD4_itemVar.star.xvel == arg1) {
        temp_r5->xDD4_itemVar.star.xvel = 0.0f;
    }
    it_8026B894(arg0, (HSD_GObj *) arg1);
}
#endif
