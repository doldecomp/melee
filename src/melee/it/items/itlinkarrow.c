#include "itlinkarrow.h"

#include "baselib/mtx.h"
#include "db/db.h"
#include "ef/efsync.h"
#include "ft/chara/ftCommon/ftCo_Guard.h"
#include "ft/chara/ftKirby/ftKb_Init.h"
#include "ft/chara/ftLink/ftLk_SpecialN.h"
#include "ft/ft_0C31.h"
#include "ft/ftlib.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/itCharItems.h"
#include "it/itcoll.h"
#include "it/item.h"
#include "lb/lbrefract.h"
#include "lb/lbvector.h"
#include "mp/mpcoll.h"
#include "mp/mplib.h"
#include "sysdolphin/baselib/random.h"

#include <math.h>

// @todo: Remove these once lbcoll is matched.
static inline void fake_HSD_JObjSetRotation(HSD_JObj* jobj, Quaternion* rotate)
{
    HSD_ASSERT(618, jobj);
    HSD_ASSERT(619, rotate);
    jobj->rotate = *rotate;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        ftCo_800C6AFC(jobj);
    }
}

static inline void fake_HSD_JObjSetScale(HSD_JObj* jobj, Vec3* scale)
{
    HSD_ASSERT(760, jobj);
    HSD_ASSERT(761, scale);
    jobj->scale = *scale;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        ftCo_800C6AFC(jobj);
    }
}

static inline void fake_HSD_JObjSetTranslate(HSD_JObj* jobj, Vec3* translate)
{
    HSD_ASSERT(916, jobj);
    HSD_ASSERT(917, translate);
    jobj->translate = *translate;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        ftCo_800C6AFC(jobj);
    }
}

ItemStateTable it_803F6A28[5] = {
    { -1, itLinkarrow_UnkMotion0_Anim, itLinkarrow_UnkMotion0_Phys,
      itLinkarrow_UnkMotion0_Coll },
    { 0, itLinkarrow_UnkMotion1_Anim, itLinkarrow_UnkMotion1_Phys,
      itLinkarrow_UnkMotion1_Coll },
    { -1, itLinkarrow_UnkMotion2_Anim, itLinkarrow_UnkMotion2_Phys,
      itLinkarrow_UnkMotion2_Coll },
    { -1, itLinkarrow_UnkMotion3_Anim, itLinkarrow_UnkMotion3_Phys,
      itLinkarrow_UnkMotion3_Coll },
    { -1, itLinkarrow_UnkMotion4_Anim, itLinkarrow_UnkMotion4_Phys,
      itLinkarrow_UnkMotion4_Coll },
};
f32 numbers[] = { 2, 4, 6, 8, 10, 12, 14, 16 };
f32 numbers_l[] = { 2, 3, 4, 5, 6, 7, 8, 9 };

void it_802A7D8C(HSD_GObj* gobj, int arg1)
{
    Item* item;

    item = GET_ITEM(gobj);
    if ((item->xDD4_itemVar.linkarrow.xB4[0] != NULL) &&
        (item->xDAC_itcmd_var0 == 1U))
    {
        HSD_JObjDispAll(item->xDD4_itemVar.linkarrow.xB4[0], NULL,
                        HSD_GObj_80390EB8(arg1), 0U);
    }
    if ((item->xDD4_itemVar.linkarrow.xB4[1] != NULL) &&
        (item->xDB0_itcmd_var1 == 1U))
    {
        HSD_JObjDispAll(item->xDD4_itemVar.linkarrow.xB4[1], NULL,
                        HSD_GObj_80390EB8(arg1), 0U);
    }
    it_8026EECC(gobj, arg1);
}

void it_802A7E40(Item_GObj* gobj)
{
    int i;
    HSD_JObj* jobj;
    Item* item;
    Quaternion quat;
    Vec3 scale;

    item = gobj->user_data;
    jobj = gobj->hsd_obj;

#if 1
    for (i = 0; i < 3; i++) {
        *(&item->xDD4_itemVar.linkarrow.x48 - i) =
            *(&item->xDD4_itemVar.linkarrow.x3C - i);
        *(&item->xDD4_itemVar.linkarrow.x84 - i) =
            *(&item->xDD4_itemVar.linkarrow.x74 - i);
    }
#else
    item->xDD4_itemVar.linkarrow.x48 = item->xDD4_itemVar.linkarrow.x3C;
    item->xDD4_itemVar.linkarrow.x84 = item->xDD4_itemVar.linkarrow.x74;
    item->xDD4_itemVar.linkarrow.x3C = item->xDD4_itemVar.linkarrow.x30;
    item->xDD4_itemVar.linkarrow.x74 = item->xDD4_itemVar.linkarrow.x64;
    item->xDD4_itemVar.linkarrow.x30 = item->xDD4_itemVar.linkarrow.x24;
    item->xDD4_itemVar.linkarrow.x64 = item->xDD4_itemVar.linkarrow.x54;
#endif

    HSD_JObjGetRotation(jobj, &quat);
    item->xDD4_itemVar.linkarrow.x24 = item->xDD4_itemVar.linkarrow.x18;
    item->xDD4_itemVar.linkarrow.x24.z -= 0.02f;
    item->xDD4_itemVar.linkarrow.x54 = quat;

    for (i = 0; i < 2; i++) {
        if (item->xDD4_itemVar.linkarrow.xB4[i] != NULL) {
            HSD_JObjSetTranslate(item->xDD4_itemVar.linkarrow.xB4[i],
                                 &item->xDD4_itemVar.linkarrow.x24 + i);
            HSD_JObjSetRotation(item->xDD4_itemVar.linkarrow.xB4[i],
                                &item->xDD4_itemVar.linkarrow.x54 + i);
            HSD_JObjGetScale(jobj, &scale);
            HSD_JObjSetScale(item->xDD4_itemVar.linkarrow.xB4[i], &scale);
        }
    }
}

HSD_GObj* it_802A83E0(f32 facing_dir, Fighter_GObj* arg1, Vec3* arg2,
                      Fighter_Part arg3, s32 arg4)
{
    SpawnItem spawn;
    Item_GObj* gobj;
    Item* item;
    itLinkArrowAttributes* attr;

    arg2->z = 0.0f;
    spawn.kind = (ItemKind) arg4;
    spawn.prev_pos = *arg2;
    spawn.pos = spawn.prev_pos;
    spawn.facing_dir = facing_dir;
    spawn.x3C_damage = 0;
    spawn.vel.x = spawn.vel.y = spawn.vel.z = 0.0f;
    spawn.x0_parent_gobj = arg1;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x44_flag.b0 = true;
    spawn.x40 = 0;
    gobj = Item_80268B18(&spawn);

    if (gobj != NULL) {
        item = GET_ITEM((HSD_GObj*) gobj);
        attr = item->xC4_article_data->x4_specialAttributes;
        item->xDB8_itcmd_var3 = 0;
        item->xDB4_itcmd_var2 = 0;
        item->xDB0_itcmd_var1 = 0;
        item->xDAC_itcmd_var0 = 0;
        it_80275158((HSD_GObj*) gobj, attr->x0);
        item->xDD4_itemVar.linkarrow.xA0 = 0;
        item->xDD4_itemVar.linkarrow.xB0 = 0;
        item->xDD4_itemVar.linkarrow.xB4[1] = NULL;
        item->xDD4_itemVar.linkarrow.xB4[0] = NULL;
        item->xDD4_itemVar.linkarrow.xE0 = arg1;
        item->xDD4_itemVar.linkarrow.xC0 =
            ftLib_800869D4(item->xDD4_itemVar.linkarrow.xE0);
        item->xDD4_itemVar.linkarrow.xE4 = -1;
        item->xDD4_itemVar.linkarrow.xEC = 0.0f;
        item->xDD4_itemVar.linkarrow.xE8 = 0.0f;
        Item_8026AB54((HSD_GObj*) gobj, arg1, arg3);
        db_80225DD8(gobj, (Fighter_GObj*) arg1);
    }
    return (HSD_GObj*) gobj;
}

#define INLINE 0

static f32 fn_802A81C4_inline(Item* item)
{
    int i = item->xDD4_itemVar.linkarrow.x9C;
    f32 var_f31 = (numbers_l[i] * HSD_Randf()) + numbers[i];
    return deg_to_rad * var_f31;
}

void fn_802A81C4(HSD_GObj* gobj)
{
    f32 rand;
    f32 var_f32;
    f32 var_f31;
    float* temp_r3;
    u32 temp_r0;

    Item* item = GET_ITEM(gobj);
    HSD_JObj* jobj = HSD_GObjGetHSDObj(gobj);
    switch (item->xDD4_itemVar.linkarrow.x9C) {
    case 0:
    case 2:
    case 4:
    case 6:
#if INLINE
        var_f31 = item->xDD4_itemVar.linkarrow.x94 + fn_802A81C4_inline(item);
#else
        rand = HSD_Randf();
        temp_r3 = (float*) &it_803F6A28 + item->xDD4_itemVar.linkarrow.x9C;
        var_f31 = (temp_r3[31] * rand) + temp_r3[23];
        var_f32 = deg_to_rad * var_f31;
        var_f31 = item->xDD4_itemVar.linkarrow.x94 + var_f32;
#endif
        break;
    case 1:
    case 3:
    case 5:
#if INLINE
        var_f31 = item->xDD4_itemVar.linkarrow.x94 - fn_802A81C4_inline(item);
#else
        rand = HSD_Randf();
        temp_r3 = (float*) &it_803F6A28 + item->xDD4_itemVar.linkarrow.x9C;
        var_f31 = (temp_r3[31] * rand) + temp_r3[23];
        var_f32 = deg_to_rad * var_f31;
        var_f31 = item->xDD4_itemVar.linkarrow.x94 - var_f32;
#endif
        break;
    default:
        var_f31 = item->xDD4_itemVar.linkarrow.x94;
        break;
    }
    HSD_JObjSetRotationZ(jobj, var_f31);
    item->xDD4_itemVar.linkarrow.x9C -= 1;
}

void it_802A8330(HSD_GObj* gobj)
{
    Item* item;
    f32 pad;
    if (gobj != NULL) {
        item = GET_ITEM(gobj);
        if (item != NULL) {
            if (item->xDD4_itemVar.linkarrow.xB4[0] != NULL) {
                HSD_JObjRemoveAll(item->xDD4_itemVar.linkarrow.xB4[0]);
                item->xDD4_itemVar.linkarrow.xB4[0] = NULL;
            }
            if (item->xDD4_itemVar.linkarrow.xB4[1] != NULL) {
                HSD_JObjRemoveAll(item->xDD4_itemVar.linkarrow.xB4[1]);
                item->xDD4_itemVar.linkarrow.xB4[1] = NULL;
            }
        }
    }
}

void it_802A8398(Item_GObj* gobj, Vec3* pos, Vec3* pos2)
{
    Item* item;
    if (gobj != NULL) {
        item = GET_ITEM(gobj);
        if (item != NULL) {
            item->pos = *pos;
            item->xDD4_itemVar.linkarrow.x18 = *pos2;
        }
    }
}

inline HSD_JObj* it_802A850C_inline(HSD_Joint* joint)
{
    HSD_JObj* var_r30;
    if (joint != NULL) {
        var_r30 = HSD_JObjLoadJoint(joint);
    } else {
        // @todo: This should just return uninitialized, but the
        // formatter doesn't like it.
        return NULL;
    }
    return var_r30;
}

inline void it_802A850C_inline_2(Item_GObj* gobj, Quaternion* quat)
{
    int i;
    Item* item;
    HSD_JObj* jobj;
    item = GET_ITEM(gobj);
    jobj = gobj->hsd_obj;
    HSD_JObjGetRotation(jobj, quat);

    for (i = 0; i < 4; i++) {
        *(&item->xDD4_itemVar.linkarrow.x24 + i) =
            item->xDD4_itemVar.linkarrow.x18;
        (*(&item->xDD4_itemVar.linkarrow.x24 + i)).z -= 0.02f;
        *(&item->xDD4_itemVar.linkarrow.x54 + i) = *quat;
    }
}

void it_802A850C(Item_GObj* gobj, Vec3* arg1, Vec3* arg2, f32 arg3, f32 arg4,
                 f32 arg5)
{
    Item* item;
    HSD_JObj* jobj;
    itLinkArrowAttributes* attr;
    Mtx* matrix;
    u8* data;
    f32 pad[1];
    Vec3 rot;
    f32 pad_3[1];
    Vec3 pos;
    Vec3 sp68;
    f32 pad_8[1];
    u32 sp60;
    f32 pad_10[1];
    Quaternion quat;
    f32 pad_9[3];

    item = GET_ITEM(gobj);
    jobj = gobj->hsd_obj;

    attr = item->xC4_article_data->x4_specialAttributes;
    item->xDD4_itemVar.linkarrow.x94 = arg3;
    it_80275158((HSD_GObj*) gobj, attr->x0 + attr->x18);
    item->xDD4_itemVar.linkarrow.xAC = arg4;
    if ((item->xDD4_itemVar.linkarrow.xE0 != NULL) &&
        (item->owner == item->xDD4_itemVar.linkarrow.xE0))
    {
        it_802A8C7C(gobj);
        data = ftLib_80086630(item->xDD4_itemVar.linkarrow.xE0,
                              (enum Fighter_Part) item->xDC4);
        matrix = (Mtx*) (data + 0x44);
        HSD_MtxGetRotation(*matrix, &rot);
        pos.z = 0.0f;
        pos.y = 0.0f;
        pos.x = 0.0f;
        it_8027429C((HSD_GObj*) gobj, (Vec3*) &pos);
        item->xDC8_word.flags.x14 = 0;
        it_8026B3A8(gobj);
        item->xDD4_itemVar.linkarrow.xA8 =
            (arg4 * ((attr->x8 - attr->x4) / arg5)) + attr->x4;
        item->xDD4_itemVar.linkarrow.xA4 =
            (arg4 * ((attr->x10 - attr->xC) / arg5)) + attr->xC;
        item->facing_dir = ftLib_800865C0(item->xDD4_itemVar.linkarrow.xE0);
        HSD_JObjSetRotationY(jobj,
                             1.5707963267948966 * (f64) item->facing_dir);
        item->pos = *arg1;
        item->xDD4_itemVar.linkarrow.x18 = *arg2;
        item->x40_vel.x =
            item->facing_dir * (item->xDD4_itemVar.linkarrow.xA8 *
                                cosf(item->xDD4_itemVar.linkarrow.x94));
        item->x40_vel.y = item->xDD4_itemVar.linkarrow.xA8 *
                          sinf(item->xDD4_itemVar.linkarrow.x94);
        item->x40_vel.z = 0.0f;
        HSD_JObjSetRotationZ(jobj, item->xDD4_itemVar.linkarrow.x94);
        item->xDD4_itemVar.linkarrow.xA0 = 1;

        it_802A850C_inline_2(gobj, &quat);

        attr = item->xC4_article_data->x4_specialAttributes;
        item->xDD4_itemVar.linkarrow.xB4[0] = it_802A850C_inline(attr->x24);
        attr = item->xC4_article_data->x4_specialAttributes;
        item->xDD4_itemVar.linkarrow.xB4[1] = it_802A850C_inline(attr->x28);

        item->xDD4_itemVar.linkarrow.xB0 = 0;
        it_8026EA20(gobj, &item->xDD4_itemVar.linkarrow.x18, &item->pos, &sp68,
                    (UNK_T) &item->xDD4_itemVar.linkarrow.xE4, &sp60);
    }
}

void it_2725_Logic98_Destroyed(Item_GObj* gobj)
{
    Item* item;
    enum ItemKind temp_r0;

    if (gobj != NULL) {
        item = GET_ITEM(gobj);
        if (item != NULL) {
            if (item->xDD4_itemVar.linkarrow.xA0 == 0) {
                if ((item->xDD4_itemVar.linkarrow.xE0 != NULL) &&
                    (item->owner == item->xDD4_itemVar.linkarrow.xE0))
                {
                    switch (item->kind) {
                    case It_Kind_Link_Arrow:
                    case It_Kind_CLink_Arrow:
                        ftLk_SpecialN_UnsetArrow(
                            item->xDD4_itemVar.linkarrow.xE0);
                        break;
                    case It_Kind_Kirby_CLinkArrow:
                    case It_Kind_Kirby_LinkArrow:
                        ftKb_SpecialNLk800FB418(
                            item->xDD4_itemVar.linkarrow.xE0);
                        break;
                    }
                }
            }
            it_802A8330(gobj);
            item->xDD4_itemVar.linkarrow.xE0 = NULL;
            item->owner = NULL;
            item->xDC8_word.flags.x13 = 0;
        }
    }
}

void it_802A8A7C(Item_GObj* gobj)
{
    if (gobj != NULL) {
        it_802A8330(gobj);
        Item_8026A8EC(gobj);
    }
}

void it_2725_Logic98_PickedUp(Item_GObj* gobj)
{
    Item_80268E5C((HSD_GObj*) gobj, 0, ITEM_ANIM_UPDATE);
}

// Item could be passed to influence stack
static void inline itLinkarrow_UnkMotion1_Anim_inline_s_2(HSD_GObj* gobj,
                                                          Item* item)
{
    HSD_JObj* jobj = gobj->hsd_obj;
    Vec3 scale;
    scale.x = scale.y = scale.z = item->xDD4_itemVar.linkarrow.xC0;
    HSD_JObjSetScale(jobj, &scale);
}

bool itLinkarrow_UnkMotion0_Anim(HSD_GObj* gobj)
{
    Item* item;
    item = GET_ITEM(gobj);
    itLinkarrow_UnkMotion1_Anim_inline_s_2(gobj, item);
    if (item->xDD4_itemVar.linkarrow.xE0 != NULL) {
        if (item->owner == item->xDD4_itemVar.linkarrow.xE0) {
            switch (item->kind) {
            case It_Kind_Link_Arrow:
            case It_Kind_CLink_Arrow:
                if (ftLk_SpecialN_IsActiveAnd2071b6(
                        item->xDD4_itemVar.linkarrow.xE0) != 0)
                {
                    item->xDD4_itemVar.linkarrow.xE0 = NULL;
                    return 1;
                }
                break;
            case It_Kind_Kirby_CLinkArrow:
            case It_Kind_Kirby_LinkArrow:
                if (ftKb_SpecialNLk800FB470(
                        item->xDD4_itemVar.linkarrow.xE0) != 0)
                {
                    item->xDD4_itemVar.linkarrow.xE0 = NULL;
                    return 1;
                }
                break;
            }
        }
    } else {
        return 1;
    }
    return 0;
}

void itLinkarrow_UnkMotion0_Phys(HSD_GObj* gobj)
{
    return;
}

bool itLinkarrow_UnkMotion0_Coll(HSD_GObj* gobj)
{
    return 0;
}

void it_802A8C7C(HSD_GObj* gobj)
{
    Item* item;
    itLinkArrowAttributes* attr;
    item = GET_ITEM(gobj);
    attr = item->xC4_article_data->x4_specialAttributes;
    it_80275158(gobj, attr->x0);
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
}

static int inline it_802A8330_inline(Item_GObj* gobj)
{
    if (it_80273130(gobj) == 1) {
        it_802A8330((HSD_GObj*) gobj);
        return 1;
    }
    return 0;
}

static void inline itLinkarrow_UnkMotion1_Anim_inline(HSD_GObj* gobj, int i)
{
    Item* item;
    HSD_JObj* jobj;
    Vec3 scale;
    item = GET_ITEM(gobj);
    jobj = HSD_GObjGetHSDObj(gobj);
    if (item->xDD4_itemVar.linkarrow.xB4[i] != NULL) {
        it_80272A18(item->xDD4_itemVar.linkarrow.xB4[i]);
        fake_HSD_JObjSetTranslate(item->xDD4_itemVar.linkarrow.xB4[i],
                                  &item->xDD4_itemVar.linkarrow.x30 + i);
        fake_HSD_JObjSetRotation(item->xDD4_itemVar.linkarrow.xB4[i],
                                 &item->xDD4_itemVar.linkarrow.x64 + i);
        HSD_JObjGetScale(jobj, &scale);
        fake_HSD_JObjSetScale(item->xDD4_itemVar.linkarrow.xB4[i], &scale);
    }
}

bool itLinkarrow_UnkMotion1_Anim(HSD_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    {
        HSD_JObj* jobj = HSD_GObjGetHSDObj(gobj);
        Vec3 scale;
        scale.x = scale.y = scale.z = item->xDD4_itemVar.linkarrow.xC0;
        HSD_JObjSetScale(jobj, &scale);
    }

    {
        if (item->xDB4_itcmd_var2 == 0) {
            it_80272460(&item->x5D4_hitboxes[0].hit,
                        item->xDD4_itemVar.linkarrow.xA4, gobj);
            item->xDB4_itcmd_var2 = 1;
        }
    }

    item = GET_ITEM(gobj);
    if (item->xDD4_itemVar.linkarrow.xB0 > 0) {
        item->xDAC_itcmd_var0 = 1;
    }
    if (item->xDD4_itemVar.linkarrow.xB0 > 1) {
        item->xDB0_itcmd_var1 = 1;
    }

    if (item->xDAC_itcmd_var0 == 1) {
        itLinkarrow_UnkMotion1_Anim_inline(gobj, 0);
    }
    if (item->xDB0_itcmd_var1 == 1) {
        itLinkarrow_UnkMotion1_Anim_inline(gobj, 1);
    }

    item->xDD4_itemVar.linkarrow.xB0 += 1;
    return it_802A8330_inline(gobj);
}

void itLinkarrow_UnkMotion1_Phys(HSD_GObj* gobj)
{
    Item* item;
    itLinkArrowAttributes* attr;

    item = gobj->user_data;
    attr = item->xC4_article_data->x4_specialAttributes;
    item->xDD4_itemVar.linkarrow.x18 = item->pos;
    item->x40_vel.y -= ABS(attr->x1C);
}

static inline bool itLinkarrow_UnkMotion1_Coll_inline(Item_GObj* gobj)
{
    u32 sp18;
    Vec3 sp1C;
    Item* item_2 = GET_ITEM(gobj);
    CollData* pp = &item_2->x378_itemColl;
    if ((it_8026EA20(gobj, &item_2->xDD4_itemVar.linkarrow.x18, &item_2->pos,
                     &sp1C, (UNK_T) &item_2->xDD4_itemVar.linkarrow.xE4,
                     &sp18) != 0) &&
        (mpLib_80054ED8(item_2->xDD4_itemVar.linkarrow.xE4) != 0))
    {
        mpColl_80043558(pp, item_2->xDD4_itemVar.linkarrow.xE4);
        mpGetSpeed(item_2->xDD4_itemVar.linkarrow.xE4, &item_2->pos,
                   &item_2->x40_vel);
        item_2->xDD4_itemVar.linkarrow.xE8 =
            item_2->xDD4_itemVar.linkarrow.xEC = atan2f(sp1C.y, sp1C.x);
        return 1;
    }
    return 0;
}

bool itLinkarrow_UnkMotion1_Coll(Item_GObj* gobj)
{
    HSD_JObj* jobj;
    itLinkArrowAttributes* attr;
    Item* item;

    PAD_STACK(8);

    item = GET_ITEM(gobj);
    jobj = HSD_GObjGetHSDObj(gobj);
    attr = item->xC4_article_data->x4_specialAttributes;

    if (item->facing_dir == 1.0f) {
        item->xDD4_itemVar.linkarrow.x94 =
            atan2f(item->pos.y - item->xDD4_itemVar.linkarrow.x18.y,
                   item->pos.x - item->xDD4_itemVar.linkarrow.x18.x);
    } else {
        item->xDD4_itemVar.linkarrow.x94 =
            -atan2f(item->pos.y - item->xDD4_itemVar.linkarrow.x18.y,
                    item->xDD4_itemVar.linkarrow.x18.x - item->pos.x);
    }
    if (ABS(item->xDD4_itemVar.linkarrow.x94) > attr->x20) {
        item->xDD4_itemVar.linkarrow.x94 =
            (item->xDD4_itemVar.linkarrow.x94 < 0.0f) ? -attr->x20 : attr->x20;
    }
    HSD_JObjSetRotationZ(jobj, item->xDD4_itemVar.linkarrow.x94);
    if (itLinkarrow_UnkMotion1_Coll_inline(gobj) != 0) {
        it_802A9458(gobj);
    }
    it_802A7E40(gobj);
    return 0;
}

bool itLinkarrow_UnkMotion2_Anim(Item_GObj* gobj)
{
    Item* item;
    f32 pad[1];
    item = GET_ITEM(gobj);
    if (ftLib_80086A18(item->xDD4_itemVar.linkarrow.xC4) != 1) {
        return 1;
    }
    return it_802A8330_inline(gobj);
}

void itLinkarrow_UnkMotion2_Phys(HSD_GObj* gobj)
{
    Item* item;
    item = GET_ITEM(gobj);
    item->xDD4_itemVar.linkarrow.xD4 =
        (ftCo_80094098(item->xDD4_itemVar.linkarrow.xC4,
                       &item->xDD4_itemVar.linkarrow.xC8) *
         ftLib_800869D4(item->xDD4_itemVar.linkarrow.xC4));
    item->pos.x = (item->xDD4_itemVar.linkarrow.xD4 *
                   cosf(item->xDD4_itemVar.linkarrow.xD8)) +
                  item->xDD4_itemVar.linkarrow.xC8;
    item->pos.y = (item->xDD4_itemVar.linkarrow.xD4 *
                   sinf(item->xDD4_itemVar.linkarrow.xD8)) +
                  item->xDD4_itemVar.linkarrow.xCC;
    item->pos.z = 0.0f;
}

bool itLinkarrow_UnkMotion2_Coll(HSD_GObj* gobj)
{
    return 0;
}

bool itLinkarrow_UnkMotion3_Anim(HSD_GObj* gobj)
{
    return 0;
}

void itLinkarrow_UnkMotion3_Phys(HSD_GObj* gobj)
{
    return;
}

bool itLinkarrow_UnkMotion3_Coll(HSD_GObj* gobj)
{
    return 0;
}

void it_802A9458(HSD_GObj* gobj)
{
    itLinkArrowAttributes* attr;
    Item* item;
    HSD_JObj* jobj;
    f32 temp_scale;
    Vec3 scale;

    item = GET_ITEM(gobj);
    jobj = HSD_GObjGetHSDObj(gobj);
    temp_scale = item->xDD4_itemVar.linkarrow.xC0;
    attr = item->xC4_article_data->x4_specialAttributes;

    scale.z = temp_scale;
    scale.y = temp_scale;
    scale.x = temp_scale;

    HSD_JObjSetScale(jobj, &scale);
    it_80275158(gobj, attr->x18);
    item->xDD4_itemVar.linkarrow.x9C = HSD_Randi(4) + 3;
    item->xDD4_itemVar.linkarrow.xF0 = 0;
    Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE);
    HSD_JObjSetRotationZ(jobj, item->xDD4_itemVar.linkarrow.x94);
    it_802A8330(gobj);
    switch (item->kind) {
    // @todo: replace with enum names
    case It_Kind_Link_Arrow:
    case It_Kind_Kirby_LinkArrow:
        Item_8026AE84(item, 0x27152, 0x7F, 0x40);
        break;
    case It_Kind_CLink_Arrow:
    case It_Kind_Kirby_CLinkArrow:
        Item_8026AE84(item, 0x111C2, 0x7F, 0x40);
        scale.y = 0.0f;
        scale.x = 0.0f;
        scale.z = 5.0f;
        efSync_Spawn(0x448, gobj, jobj, &scale);
        break;
    }
}

static bool inline itlinkarrow_inline_bool(Item_GObj* gobj)
{
    bool var_r0;
    if (it_80273130(gobj) == 1) {
        it_802A8330((HSD_GObj*) gobj);
        var_r0 = 1;
    } else {
        var_r0 = 0;
    }
    return var_r0;
}

bool itLinkarrow_UnkMotion4_Anim(Item_GObj* gobj)
{
    f32 var_f32;
    Item* item;
    HSD_JObj* jobj;
    f32 var_f31;
    u32 temp_r0;
    float* temp_r3;
    f32 rand;
    f32 pad[3];

    item = GET_ITEM(gobj);
    jobj = HSD_GObjGetHSDObj(gobj);
    switch (item->xDD4_itemVar.linkarrow.x9C) {
    case 0:
    case 2:
    case 4:
    case 6:
        rand = HSD_Randf();
        temp_r3 = (float*) &it_803F6A28 + item->xDD4_itemVar.linkarrow.x9C;
        var_f31 = (temp_r3[31] * rand) + temp_r3[23];
        var_f32 = 0.017453292f * var_f31;
        var_f31 = item->xDD4_itemVar.linkarrow.x94 + var_f32;
        break;
    case 1:
    case 3:
    case 5:
        rand = HSD_Randf();
        temp_r3 = (float*) &it_803F6A28 + item->xDD4_itemVar.linkarrow.x9C;
        var_f31 = (temp_r3[31] * rand) + temp_r3[23];
        var_f32 = 0.017453292f * var_f31;
        var_f31 = item->xDD4_itemVar.linkarrow.x94 - var_f32;
        break;
    default:
        var_f31 = item->xDD4_itemVar.linkarrow.x94;
        break;
    }
    HSD_JObjSetRotationZ(jobj, var_f31);
    item->xDD4_itemVar.linkarrow.x9C -= 1;

    if (itlinkarrow_inline_bool(gobj) != 0) {
        if (item->xDD4_itemVar.linkarrow.xF0 == 0) {
            it_802787B4(gobj, 0x421);
            it_802756D0((HSD_GObj*) gobj);
        }
        it_8026BB44(gobj);
        item->xDCF_flag.b2 = 1;
        item->xDD4_itemVar.linkarrow.xF0 += 1;
        if (item->xDD4_itemVar.linkarrow.xF0 > 0x12C) {
            return 1;
        }
    }
    return 0;
}

void itLinkarrow_UnkMotion4_Phys(HSD_GObj* gobj)
{
    return;
}

bool itLinkarrow_UnkMotion4_Coll(HSD_GObj* gobj)
{
    f32 temp_f0;
    f32 temp_f1;
    f32 temp_f31;
    s32 temp_r4;
    s32 var_r3;

    Vec3 sp18;
    HSD_JObj* jobj;
    Item* item;

    s32 var_r0;

    CollData* pp;

    item = GET_ITEM(gobj);
    jobj = gobj->hsd_obj;
    it_802A7E40((Item_GObj*) gobj);

    // item = gobj->user_data;
    item->xDD4_itemVar.linkarrow.xEC = item->xDD4_itemVar.linkarrow.xE8;
    pp = &item->x378_itemColl;
    if (item->xDD4_itemVar.linkarrow.xE4 != -1) {
        if (mpLib_80054ED8(item->xDD4_itemVar.linkarrow.xE4) != 0) {
            mpColl_80043558(pp, item->xDD4_itemVar.linkarrow.xE4);
            mpGetSpeed(item->xDD4_itemVar.linkarrow.xE4, &item->pos,
                       &item->x40_vel);
            mpLineGetNormal(item->xDD4_itemVar.linkarrow.xE4, &sp18);
            item->xDD4_itemVar.linkarrow.xE8 = atan2f(sp18.y, sp18.x);
        }
        var_r0 = 1;
    } else {
        item->x40_vel.z = 0.0f;
        item->x40_vel.y = 0.0f;
        item->x40_vel.x = 0.0f;
        var_r0 = 0;
    }
    if (var_r0 == 1) {
        temp_f1 = item->xDD4_itemVar.linkarrow.xE8;
        temp_f0 = item->xDD4_itemVar.linkarrow.xEC;
        if (temp_f1 != temp_f0) {
            item->xDD4_itemVar.linkarrow.x94 =
                (f32) (item->xDD4_itemVar.linkarrow.x94 + (temp_f1 - temp_f0));
            HSD_JObjSetRotationZ(jobj, item->xDD4_itemVar.linkarrow.x94);
        }
        return 0;
    }
    return 1;
}

bool it_2725_Logic98_DmgDealt(Item_GObj* gobj)
{
    Item* item;
    itLinkArrowAttributes* attr;
    item = GET_ITEM(gobj);
    attr = item->xC4_article_data->x4_specialAttributes;
    item->x40_vel.x *= attr->x14;
    it_802A8330(gobj);
    return 1;
}

bool it_2725_Logic98_Clanked(Item_GObj* gobj)
{
    f32 pad;
    it_802A8330(gobj);
    return 1;
}

bool it_2725_Logic98_HitShield(Item_GObj* gobj)
{
    f32 sp28;
    f32 sp24;
    f32 sp20;
    f32 temp_f0;
    f32 temp_f31;
    s32 temp_cr0_eq;
    s32 var_r3;
    u32 temp_r4;

    Item* item;
    HSD_GObj* temp_r3;
    HSD_JObj* jobj;
    itLinkArrowAttributes* attr;
    Vec3 scale;

    item = GET_ITEM(gobj);
    attr = item->xC4_article_data->x4_specialAttributes;
    if (item->xCF4_fighterGObjUnk != NULL) {
        if (it_80272D40(item->xCF4_fighterGObjUnk) == 0) {
            jobj = gobj->hsd_obj;

            scale.x = item->xDD4_itemVar.linkarrow.xC0;
            scale.y = item->xDD4_itemVar.linkarrow.xC0;
            scale.z = item->xDD4_itemVar.linkarrow.xC0;
            HSD_JObjSetScale(jobj, &scale);

            it_80275158((HSD_GObj*) gobj, attr->x18);
            item->x40_vel.z = 0.0f;
            item->x40_vel.y = 0.0f;
            item->x40_vel.x = 0.0f;
            Item_80268E5C((HSD_GObj*) gobj, 2, ITEM_ANIM_UPDATE);
            it_2725_Logic98_Clanked(gobj);
            item->xDD4_itemVar.linkarrow.xC4 = item->xCF4_fighterGObjUnk;
            temp_f31 = ftLib_800869D4(item->xDD4_itemVar.linkarrow.xC4);
            item->xDD4_itemVar.linkarrow.xD4 =
                temp_f31 * ftCo_80094098(item->xDD4_itemVar.linkarrow.xC4,
                                         &item->xDD4_itemVar.linkarrow.xC8);
            item->xDD4_itemVar.linkarrow.xD8 = atan2f(
                (0.5f * (item->pos.y + item->xDD4_itemVar.linkarrow.x18.y)) -
                    item->xDD4_itemVar.linkarrow.xCC,
                (0.5f * (item->pos.x + item->xDD4_itemVar.linkarrow.x18.x)) -
                    item->xDD4_itemVar.linkarrow.xC8);
            item->pos.x = (item->xDD4_itemVar.linkarrow.xD4 *
                           cosf(item->xDD4_itemVar.linkarrow.xD8)) +
                          item->xDD4_itemVar.linkarrow.xC8;
            item->pos.y = (item->xDD4_itemVar.linkarrow.xD4 *
                           sinf(item->xDD4_itemVar.linkarrow.xD8)) +
                          item->xDD4_itemVar.linkarrow.xCC;
            item->pos.z = 0.0f;
            return 0;
        }
        return 1;
    }
    return 1;
}

bool it_2725_Logic98_Reflected(Item_GObj* gobj)
{
    Item* item;
    HSD_JObj* jobj;

    f32 var_f31;
    f32 temp_f31;
    f32 pad[4];

    item = GET_ITEM(gobj);
    jobj = GET_JOBJ(gobj);
    it_802A8330(gobj);
    item->facing_dir = -item->facing_dir;
    temp_f31 = 1.5707963267948966 * item->facing_dir;
    HSD_JObjSetRotationY(jobj, temp_f31);
    item->x40_vel.x = -item->x40_vel.x;
    item->x40_vel.y = -item->x40_vel.y;
    item->x40_vel.z = 0.0f;
    item->pos.x += item->x40_vel.x;
    item->pos.y += item->x40_vel.y;
    item->pos.z = 0.0f;
    var_f31 = 3.141592653589793 + item->xDD4_itemVar.linkarrow.x94;
    while (var_f31 > 3.141592653589793) {
        var_f31 -= 3.141592653589793;
    }
    while (var_f31 < -3.141592653589793) {
        var_f31 += 3.141592653589793;
    }
    item->xDD4_itemVar.linkarrow.x94 = var_f31;
    HSD_JObjSetRotationZ(jobj, var_f31);
    HSD_JObjSetTranslate(jobj, &item->pos);
    return 0;
}

void it_2725_Logic98_EvtUnk(Item_GObj* gobj, Item_GObj* arg1)
{
    it_8026B894(gobj, (HSD_GObj*) arg1);
}
