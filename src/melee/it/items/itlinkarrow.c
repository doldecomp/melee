#include "ft/ft_0C31.h"
#include "itlinkarrow.h"

#include "db/db_2253.h"
#include "ef/efsync.h"
#include "ft/chara/ftCommon/ftCo_Guard.h"
#include "ft/chara/ftKirby/ftKb_Init.h"
#include "ft/chara/ftLink/ftLk_SpecialN.h"
#include "ft/ftlib.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/itCharItems.h"
#include "it/item.h"
#include "lb/lbrefract.h"
#include "lb/lbvector.h"
#include "mp/mpcoll.h"
#include "mp/mplib.h"
#include "sysdolphin/baselib/random.h"

#include <math.h>

// s32 it_8026EA20(Item_GObj *, u8 *, Vec3 *, f32 *, f32 *, ? *); /* extern */
// ? it_802787B4(Item_GObj *, ?);                      /* extern */
// f32 ftCo_80094098(HSD_GObj *, f32 *);               /* extern */
// s32 it_802A8B20(HSD_GObj *arg0);                    /* static */
// void it_802A8C70(HSD_GObj *arg0);                   /* static */
// s32 it_802A8C74(HSD_GObj *arg0);                    /* static */
// void it_802A8C7C(Item_GObj *arg0);                  /* static */
// s32 it_802A8CC8(HSD_GObj *arg0);                    /* static */
// void it_802A90F0(HSD_GObj *arg0);                   /* static */
// s32 it_802A9138(Item_GObj *arg0);                   /* static */
// s32 it_802A934C(Item_GObj *arg0);                   /* static */
// void it_802A93B4(HSD_GObj *arg0);                   /* static */
// s32 it_802A943C(HSD_GObj *arg0);                    /* static */
// s32 it_802A9444(HSD_GObj *arg0);                    /* static */
// void it_802A944C(HSD_GObj *arg0);                   /* static */
// s32 it_802A9450(HSD_GObj *arg0);                    /* static */
// void it_802A9458(Item_GObj *arg0);                  /* static */
// s32 it_802A96E4(Item_GObj *arg0);                   /* static */
// void it_802A98E4(HSD_GObj *arg0);                   /* static */
// s32 it_802A98E8(HSD_GObj *arg0);                    /* static */

ItemStateTable it_803F6A28[5] = {
    { -1, it_802A8B20, it_802A8C70, it_802A8C74 },
    { 0, it_802A8CC8, it_802A90F0, it_802A9138 },
    { -1, it_802A934C, it_802A93B4, it_802A943C },
    { -1, it_802A9444, it_802A944C, it_802A9450 },
    { -1, it_802A96E4, it_802A98E4, it_802A98E8 },
};
// char data[] = "translate";
f32 numbers[] = { 2, 4, 6, 8, 10, 12, 14, 16 };
f32 numbers_l[] = { 2, 3, 4, 5, 6, 7, 8, 9 };


// jtbl_803F6AEC:
//     .4byte .L_802A8214
//     .4byte .L_802A8244
//     .4byte .L_802A8214
//     .4byte .L_802A8244
//     .4byte .L_802A8214
//     .4byte .L_802A8244
//     .4byte .L_802A8214
// .global jtbl_803F6B08
// jtbl_803F6B08:
//     .4byte .L_802A973C
//     .4byte .L_802A976C
//     .4byte .L_802A973C
//     .4byte .L_802A976C
//     .4byte .L_802A973C
//     .4byte .L_802A976C
//     .4byte .L_802A973C

#if 0
static s8 it_803F6A78[0x4C] = {
    0x74,
    0x72,
    0x61,
    0x6E,
    0x73,
    0x6C,
    0x61,
    0x74,
    0x65,
    0,
    0,
    0,
    0x40,
    0,
    0,
    0,
    0x40,
    0x80,
    0,
    0,
    0x40,
    0xC0,
    0,
    0,
    0x41,
    0,
    0,
    0,
    0x41,
    0x20,
    0,
    0,
    0x41,
    0x40,
    0,
    0,
    0x41,
    0x60,
    0,
    0,
    0x41,
    0x80,
    0,
    0,
    0x40,
    0,
    0,
    0,
    0x40,
    0x40,
    0,
    0,
    0x40,
    0x80,
    0,
    0,
    0x40,
    0xA0,
    0,
    0,
    0x40,
    0xC0,
    0,
    0,
    0x40,
    -0x20,
    0,
    0,
    0x41,
    0,
    0,
    0,
    0x41,
    0x10,
    0,
    0,
};
static s8 it_803F6AC4[0x28] = {
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
static s8 it_804D53B0[8] = { 0x6A, 0x6F, 0x62, 0x6A, 0x2E, 0x68, 0, 0 };
static s8 it_804D53B8[8] = { 0x6A, 0x6F, 0x62, 0x6A, 0, 0, 0, 0 };
static s8 it_804D53C0[8] = { 0x72, 0x6F, 0x74, 0x61, 0x74, 0x65, 0, 0 };
f32 table_test[] = {
    (f32)0x3C8EFA35,
    (f32)0,
    (f32)0x3FF921FB,
    (f32)0x54442D18,
    (f32)0x3F800000,
    (f32)0x40A00000,
    (f32)0x3F000000,
    (f32)0,
    (f32)0x400921FB,
    (f32)0x54442D18,
    (f32)0xC00921FB,
    (f32)0x54442D18
};
#endif

void it_802A7D8C(HSD_GObj* arg0, s32 arg1)
{
    Item* item;

    item = GET_ITEM(arg0);
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
    it_8026EECC(arg0, arg1);
}

void it_802A7E40(Item_GObj* arg0)
{
    int i;
    HSD_JObj* jobj;
    Item* item;
    Quaternion quat;
    Vec3 scale;

    item = arg0->user_data;
    jobj = arg0->hsd_obj;
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
#if 0
        if (item->xDD4_itemVar.linkarrow.xB4[i] != NULL) {
            set_arrow_transform(item->xDD4_itemVar.linkarrow.xB4[i], jobj,
                            &item->xDD4_itemVar.linkarrow.x24 + i, &item->xDD4_itemVar.linkarrow.x54 + i);
        }
#else
        if (item->xDD4_itemVar.linkarrow.xB4[i] != NULL) {
            HSD_JObjSetTranslate(item->xDD4_itemVar.linkarrow.xB4[i],
                                 &item->xDD4_itemVar.linkarrow.x24 + i);
            HSD_JObjSetRotation(item->xDD4_itemVar.linkarrow.xB4[i],
                                &item->xDD4_itemVar.linkarrow.x54 + i);
            HSD_JObjGetScale(jobj, &scale);
            HSD_JObjSetScale(item->xDD4_itemVar.linkarrow.xB4[i], &scale);
        }
#endif
    }
}
HSD_GObj* it_802A83E0(f32 facing_dir, HSD_GObj* arg1, Vec3* arg2, Fighter_Part arg3,
                      s32 arg4)
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
    spawn.x44_flag.bits.b0 = true;
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

#define INLINE 1

static f32 fn_802A81C4_inline(Item *item)
{
    int i = item->xDD4_itemVar.linkarrow.x9C;
    f32 var_f31 = (numbers_l[i] * HSD_Randf()) + numbers[i];
    return 0.017453292f * var_f31; // angle to radian conversion
}

void fn_802A81C4(HSD_GObj* arg0)
{
    f32 rand;
    f32 var_f32;
    f32 var_f31;
    float* temp_r3;
    u32 temp_r0;

    Item *item = GET_ITEM(arg0);
    HSD_JObj* jobj = HSD_GObjGetHSDObj(arg0);
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
        var_f32 = 0.017453292f * var_f31;
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
        var_f32 = 0.017453292f * var_f31;
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

// NOTE(fox): Investigate if funcs that call this inlined don't match.
void it_802A8330(HSD_GObj* arg0)
{
    Item* item;
    f32 pad;
    if (arg0 != NULL) {
        item = GET_ITEM(arg0);
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
    }
    return var_r30;
}

inline void it_802A850C_inline_b(Item* item, int i)
{
    HSD_JObj* var_r30;
    itLinkArrowAttributes* attr;
    attr = item->xC4_article_data->x4_specialAttributes;
    if (attr->x24 != NULL) {
        var_r30 = HSD_JObjLoadJoint(*(&attr->x24 + i));
    }
    item->xDD4_itemVar.linkarrow.xB4[i] = var_r30;
}

inline void it_802A850C_inline_2_1(Item* item, Quaternion quat, int i)
{
    *(&item->xDD4_itemVar.linkarrow.x24 + i) =
        item->xDD4_itemVar.linkarrow.x18;
    (*(&item->xDD4_itemVar.linkarrow.x24 + i)).z -= 0.02f;
    *(&item->xDD4_itemVar.linkarrow.x54 + i) = quat;
}

inline void it_802A850C_inline_2(Item_GObj* arg0, Quaternion* quat)
{
    int i;
    Item* item;
    HSD_JObj* gobj;
    item = GET_ITEM(arg0);
    gobj = arg0->hsd_obj;
    HSD_JObjGetRotation(gobj, quat);

    for (i = 0; i < 4; i++) {
#if 0
        it_802A850C_inline_2_1(item, quat, i);
#else
        *(&item->xDD4_itemVar.linkarrow.x24 + i) =
            item->xDD4_itemVar.linkarrow.x18;
        (*(&item->xDD4_itemVar.linkarrow.x24 + i)).z -= 0.02f;
        *(&item->xDD4_itemVar.linkarrow.x54 + i) = *quat;
#endif
    }
}

void HSD_MtxGetRotation(Mtx m, Vec3* vec);

void it_802A850C(Item_GObj* arg0, Vec3* arg1, Vec3* arg2, f32 arg3, f32 arg4,
                 f32 arg5)
{
    Item* item;
    HSD_JObj* gobj;
    itLinkArrowAttributes* attr;
    Mtx* matrix;
    u8* data;
    f32 pad[1];
    Vec3 rot;
    f32 pad_3[1];
    Vec3 pos;
    Vec3 sp68;
    f32 pad_8[1];
    UNK_T sp60;
    f32 pad_10[1];
    Quaternion quat;
    f32 pad_9[3];

    item = GET_ITEM(arg0);
    gobj = arg0->hsd_obj;

    attr = item->xC4_article_data->x4_specialAttributes;
    item->xDD4_itemVar.linkarrow.x94 = arg3;
    it_80275158((HSD_GObj*) arg0, attr->x0 + attr->x18);
    item->xDD4_itemVar.linkarrow.xAC = arg4;
    if ((item->xDD4_itemVar.linkarrow.xE0 != NULL) &&
        (item->owner == item->xDD4_itemVar.linkarrow.xE0))
    {
        it_802A8C7C((HSD_GObj*) arg0);
        data = ftLib_80086630((Fighter_GObj*) item->xDD4_itemVar.linkarrow.xE0,
                              (enum Fighter_Part) item->xDC4);
        matrix = (Mtx*) (data + 0x44);
        HSD_MtxGetRotation(*matrix, &rot);
        pos.z = 0.0f;
        pos.y = 0.0f;
        pos.x = 0.0f;
        it_8027429C((HSD_GObj*) arg0, (Vec3*) &pos);
        item->xDC8_word.flags.x14 = 0;
        it_8026B3A8(arg0);
        item->xDD4_itemVar.linkarrow.xA8 =
            (arg4 * ((attr->x8 - attr->x4) / arg5)) + attr->x4;
        item->xDD4_itemVar.linkarrow.xA4 =
            (arg4 * ((attr->x10 - attr->xC) / arg5)) + attr->xC;
        item->facing_dir = ftLib_800865C0(item->xDD4_itemVar.linkarrow.xE0);
        HSD_JObjSetRotationY(gobj,
                             1.5707963267948966 * (f64) item->facing_dir);
        item->pos = *arg1;
        item->xDD4_itemVar.linkarrow.x18 = *arg2;
        item->x40_vel.x =
            item->facing_dir * (item->xDD4_itemVar.linkarrow.xA8 *
                                cosf(item->xDD4_itemVar.linkarrow.x94));
        item->x40_vel.y = item->xDD4_itemVar.linkarrow.xA8 *
                          sinf(item->xDD4_itemVar.linkarrow.x94);
        item->x40_vel.z = 0.0f;
        HSD_JObjSetRotationZ(gobj, item->xDD4_itemVar.linkarrow.x94);
        item->xDD4_itemVar.linkarrow.xA0 = 1;

#if 1
        it_802A850C_inline_2(arg0, &quat);
#else
        gobj_3 = arg0->hsd_obj;
        item_2 = GET_ITEM(arg0);
        HSD_JObjGetRotation(gobj_3, &quat);
        for (i = 0; i < 4; i++) {
            *(&item_2->xDD4_itemVar.linkarrow.x24 + i) =
                item_2->xDD4_itemVar.linkarrow.x18;
            (*(&item_2->xDD4_itemVar.linkarrow.x24 + i)).z -= 0.02f;
            *(&item_2->xDD4_itemVar.linkarrow.x54 + i) = quat;
        }
    }
#endif

#if 0
        attr = item->xC4_article_data->x4_specialAttributes;
        if (attr->x24 != NULL) {
            var_r29 = HSD_JObjLoadJoint(attr->x24);
        }
        item->xDD4_itemVar.linkarrow.xB4[0] = var_r29;

        attr = item->xC4_article_data->x4_specialAttributes;
        if (attr->x28 != NULL) {
            var_r29 = HSD_JObjLoadJoint(attr->x28);
        }
        item->xDD4_itemVar.linkarrow.xB4[1] = var_r29;
#else
        // it_802A850C_inline_b(item, 0);
        // it_802A850C_inline_b(item, 1);
        attr = item->xC4_article_data->x4_specialAttributes;
        item->xDD4_itemVar.linkarrow.xB4[0] = it_802A850C_inline(attr->x24);
        attr = item->xC4_article_data->x4_specialAttributes;
        item->xDD4_itemVar.linkarrow.xB4[1] = it_802A850C_inline(attr->x28);
        // for (i = 0; i < 2; i++) {
        //     attr = item->xC4_article_data->x4_specialAttributes;
        //     if (*(&attr->x24 + i) != NULL) {
        //         var_r30 = HSD_JObjLoadJoint(*(&attr->x24 + i));
        //     }
        //     item->xDD4_itemVar.linkarrow.xB4[i] = var_r30;
        // }
#endif

        item->xDD4_itemVar.linkarrow.xB0 = 0;
        it_8026EA20(arg0, &item->xDD4_itemVar.linkarrow.x18, &item->pos, &sp68,
                    &item->xDD4_itemVar.linkarrow.xE4, &sp60);
    }
}

void it_802A8984(Item_GObj* arg0)
{
    Item* item;
    enum ItemKind temp_r0;

    if (arg0 != NULL) {
        item = GET_ITEM(arg0);
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
            it_802A8330(arg0);
            item->xDD4_itemVar.linkarrow.xE0 = NULL;
            item->owner = NULL;
            item->xDC8_word.flags.x13 = 0;
        }
    }
}

void it_802A8A7C(Item_GObj* arg0)
{
    if (arg0 != NULL) {
        it_802A8330(arg0);
        Item_8026A8EC(arg0);
    }
}

void it_802A8AF8(Item_GObj* arg0)
{
    Item_80268E5C((HSD_GObj*) arg0, 0, ITEM_ANIM_UPDATE);
}

static void inline it_802A8CC8_inline_s(Item *item, HSD_JObj *jobj)
{
    Vec3 scale;
    scale.x = item->xDD4_itemVar.linkarrow.xC0;
    scale.y = item->xDD4_itemVar.linkarrow.xC0;
    scale.z = item->xDD4_itemVar.linkarrow.xC0;
    HSD_JObjSetScale(jobj, &scale);
}

// Item could be passed to influence stack
static void inline it_802A8CC8_inline_s_2(HSD_GObj *gobj, Item *item)
{
    HSD_JObj* jobj = gobj->hsd_obj;
    Vec3 scale;
    scale.x = scale.y = scale.z = item->xDD4_itemVar.linkarrow.xC0;
    HSD_JObjSetScale(jobj, &scale);
}

int it_802A8B20(HSD_GObj* gobj)
{
    Item* item;
    item = GET_ITEM(gobj);
    it_802A8CC8_inline_s_2(gobj, item);
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

void it_802A8C70(HSD_GObj* gobj)
{
    return;
}

int it_802A8C74(HSD_GObj* gobj)
{
    return 0;
}

void it_802A8C7C(HSD_GObj* arg0)
{
    Item* item;
    itLinkArrowAttributes* attr;
    item = GET_ITEM(arg0);
    attr = item->xC4_article_data->x4_specialAttributes;
    it_80275158(arg0, attr->x0);
    Item_80268E5C(arg0, 1, ITEM_ANIM_UPDATE);
}

static int inline it_802A8330_inline(Item_GObj* arg0)
{
    if (it_80273130(arg0) == 1) {
        it_802A8330((HSD_GObj*) arg0);
        return 1;
    }
    return 0;
}

static void inline it_802A8CC8_inline(HSD_GObj* gobj, int i)
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

static void inline it_802A8CC8_inline_2(HSD_GObj* gobj)
{
    Item* item;
    item = gobj->user_data;
    if (item->xDD4_itemVar.linkarrow.xB0 > 0) {
        item->xDAC_itcmd_var0 = 1;
    }
    if (item->xDD4_itemVar.linkarrow.xB0 > 1) {
        item->xDB0_itcmd_var1 = 1;
    }
}

static void inline it_802A8CC8_inline_3(HSD_GObj* gobj)
{
    Item* item;
    item = GET_ITEM(gobj);
    if (item->xDB4_itcmd_var2 == 0) {
        it_80272460(&item->x5D4_hitboxes[0].hit,
                    item->xDD4_itemVar.linkarrow.xA4, gobj);
        item->xDB4_itcmd_var2 = 1;
    }
}

// Item could be passed to influence stack
static void inline it_802A8CC8_inline_s_4(HSD_GObj *gobj)
{
    Item *item = GET_ITEM(gobj);
    HSD_JObj* jobj = gobj->hsd_obj;
    Vec3 scale;
    scale.x = scale.y = scale.z = item->xDD4_itemVar.linkarrow.xC0;
    HSD_JObjSetScale(jobj, &scale);
}

int it_802A8CC8(HSD_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    {
        // use the macros!!
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
        it_802A8CC8_inline(gobj, 0);
    }
    if (item->xDB0_itcmd_var1 == 1) {
        it_802A8CC8_inline(gobj, 1);
    }

    item->xDD4_itemVar.linkarrow.xB0 += 1;
    return it_802A8330_inline(gobj);
}

static void inline it_802A8CC8_inline_s_3(HSD_GObj *gobj)
{
    Item *item = GET_ITEM(gobj);
    HSD_JObj* jobj = gobj->hsd_obj;
    Vec3 scale;
    scale.x = scale.y = scale.z = item->xDD4_itemVar.linkarrow.xC0;
    HSD_JObjSetScale(jobj, &scale);
}

int it_802A8CC8_2(HSD_GObj* gobj)
{
    Item *item = GET_ITEM(gobj);

    // it_802A8CC8_inline_s(item, jobj);

#if 0
    it_802A8CC8_inline_s_3(gobj);
#else
    HSD_JObj* jobj = gobj->hsd_obj;
    Vec3 scale;
    scale.x = scale.y = scale.z = item->xDD4_itemVar.linkarrow.xC0;
    HSD_JObjSetScale(jobj, &scale);
#endif


    // item = GET_ITEM(gobj);
    // if (item->xDD4_itemVar.linkarrow.xB0 > 0) {
    //     item->xDAC_itcmd_var0 = 1;
    // }
    // if (item->xDD4_itemVar.linkarrow.xB0 > 1) {
    //     item->xDB0_itcmd_var1 = 1;
    // }

    if (item->xDB4_itcmd_var2 == 0) {
        it_80272460(&item->x5D4_hitboxes[0].hit,
                    item->xDD4_itemVar.linkarrow.xA4, gobj);
        item->xDB4_itcmd_var2 = 1;
    }

#if 0
    it_802A8CC8_inline_2(gobj);
#else
    item = gobj->user_data;
    if (item->xDD4_itemVar.linkarrow.xB0 > 0) {
        item->xDAC_itcmd_var0 = 1;
    }
    if (item->xDD4_itemVar.linkarrow.xB0 > 1) {
        item->xDB0_itcmd_var1 = 1;
    }
#endif

    if (item->xDAC_itcmd_var0 == 1) {
        it_802A8CC8_inline(gobj, 0);
    }
    if (item->xDB0_itcmd_var1 == 1) {
        it_802A8CC8_inline(gobj, 1);
    }
    item->xDD4_itemVar.linkarrow.xB0 += 1;
    return it_802A8330_inline(gobj);
}

int it_802A8CC8_3(HSD_GObj* gobj)
{
    f32 test;
    Vec3 scale;
    Item *item = GET_ITEM(gobj);
    HSD_JObj* jobj = gobj->hsd_obj;

    scale.x = item->xDD4_itemVar.linkarrow.xC0;
    scale.y = item->xDD4_itemVar.linkarrow.xC0;
    scale.z = item->xDD4_itemVar.linkarrow.xC0;
    HSD_JObjSetScale(jobj, &scale);


    if (item->xDB4_itcmd_var2 == 0) {
        it_80272460(&item->x5D4_hitboxes[0].hit,
                    item->xDD4_itemVar.linkarrow.xA4, gobj);
        item->xDB4_itcmd_var2 = 1;
    }

    item = GET_ITEM(gobj);
    if (item->xDD4_itemVar.linkarrow.xB0 > 0) {
        item->xDAC_itcmd_var0 = 1;
    }
    if (item->xDD4_itemVar.linkarrow.xB0 > 1) {
        item->xDB0_itcmd_var1 = 1;
    }

    if (item->xDAC_itcmd_var0 == 1) {
        it_802A8CC8_inline(gobj, 0);
    }
    if (item->xDB0_itcmd_var1 == 1) {
        it_802A8CC8_inline(gobj, 1);
    }

    item->xDD4_itemVar.linkarrow.xB0 += 1;
    return it_802A8330_inline(gobj);
}

void it_802A90F0(HSD_GObj* gobj)
{
    Item* item;
    itLinkArrowAttributes* attr;

    item = gobj->user_data;
    attr = item->xC4_article_data->x4_specialAttributes;
    item->xDD4_itemVar.linkarrow.x18 = item->pos;
    item->x40_vel.y -= fabs_inline(attr->x1C);
}

static inline bool it_802A9138_inline(Item_GObj* arg0)
{
    Vec3 sp1C;
    UNK_T sp18;
    Item* item_2;
    CollData* pp;
    item_2 = GET_ITEM(arg0);
    pp = &item_2->x378_itemColl;
    if ((it_8026EA20(arg0, &item_2->xDD4_itemVar.linkarrow.x18, &item_2->pos,
                     &sp1C, &item_2->xDD4_itemVar.linkarrow.xE4,
                     &sp18) != 0) &&
        (mpLib_80054ED8(item_2->xDD4_itemVar.linkarrow.xE4) != 0))
    {
        mpColl_80043558(pp, item_2->xDD4_itemVar.linkarrow.xE4);
        mpLib_800567C0(item_2->xDD4_itemVar.linkarrow.xE4, &item_2->pos,
                       &item_2->x40_vel);
        item_2->xDD4_itemVar.linkarrow.xE8 =
            item_2->xDD4_itemVar.linkarrow.xEC = atan2f(sp1C.y, sp1C.x);
        return 1;
    }
    return 0;
}

static inline float it_802A9138_circ(Vec3 a, Vec3 b)
{
    return atan2f(a.y - b.y, a.x - b.x);
}

// offset from jumptable
int it_802A9138(Item_GObj* arg0)
{
    HSD_JObj* jobj;
    f32 temp_f1;
    s32 var_r0;

    s32 test;

    Item* item;
    itLinkArrowAttributes* attr;

    item = GET_ITEM((HSD_GObj*) arg0);
    jobj = HSD_GObjGetHSDObj((HSD_GObj*) arg0);
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
    if (fabs_inline(item->xDD4_itemVar.linkarrow.x94) > attr->x20) {
        item->xDD4_itemVar.linkarrow.x94 =
            (item->xDD4_itemVar.linkarrow.x94 < 0.0f) ? -attr->x20 : attr->x20;
    }
    HSD_JObjSetRotationZ(jobj, item->xDD4_itemVar.linkarrow.x94);
    if (it_802A9138_inline(arg0) != 0) {
        it_802A9458((HSD_GObj*) arg0);
    }
    it_802A7E40(arg0);
    return 0;
}

int it_802A934C(Item_GObj* arg0)
{
    Item* item;
    f32 pad[1];
    item = GET_ITEM(arg0);
    if (ftLib_80086A18(item->xDD4_itemVar.linkarrow.xC4) != 1) {
        return 1;
    }
    return it_802A8330_inline(arg0);
}

void it_802A93B4(HSD_GObj* arg0)
{
    Item* item;
    item = GET_ITEM(arg0);
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

int it_802A943C(HSD_GObj* gobj)
{
    return 0;
}

int it_802A9444(HSD_GObj* gobj)
{
    return 0;
}

void it_802A944C(HSD_GObj* gobj)
{
    return;
}

int it_802A9450(HSD_GObj* gobj)
{
    return 0;
}

void it_802A9458(HSD_GObj* arg0)
{
    itLinkArrowAttributes* attr;
    Item* item;
    HSD_JObj* jobj;
    f32 temp_scale;
    Vec3 scale;

    item = GET_ITEM(arg0);
    jobj = HSD_GObjGetHSDObj(arg0);
    temp_scale = item->xDD4_itemVar.linkarrow.xC0;
    attr = item->xC4_article_data->x4_specialAttributes;

    scale.z = temp_scale;
    scale.y = temp_scale;
    scale.x = temp_scale;

    HSD_JObjSetScale(jobj, &scale);
    it_80275158(arg0, attr->x18);
    item->xDD4_itemVar.linkarrow.x9C = HSD_Randi(4) + 3;
    item->xDD4_itemVar.linkarrow.xF0 = 0;
    Item_80268E5C(arg0, 4, ITEM_ANIM_UPDATE);
    HSD_JObjSetRotationZ(jobj, item->xDD4_itemVar.linkarrow.x94);
    it_802A8330(arg0);
    switch (item->kind) {
    // TODO(fox): replace with enum names
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
        efSync_Spawn(0x448, arg0, jobj, &scale);
        break;
    }
}

static bool inline itlinkarrow_inline_bool(Item_GObj* arg0)
{
    bool var_r0;
    if (it_80273130(arg0) == 1) {
        it_802A8330((HSD_GObj*) arg0);
        var_r0 = 1;
    } else {
        var_r0 = 0;
    }
    return var_r0;
}

// offset from jumptable
int it_802A96E4(Item_GObj* arg0)
{
    // arg0: r3 and r29
    // item: r30
    // jobj: r31 l l
    // item x9C: r0

    f32 var_f32;
    Item* item;
    HSD_JObj* jobj;
    f32 var_f31;
    u32 temp_r0;
    float* temp_r3;
    f32 rand;
    f32 pad[3];

#if 0
    item = GET_ITEM(arg0);
    jobj = arg0->hsd_obj;
    fn_802A81C4_inline(arg0);
#else
    item = GET_ITEM(arg0);
    jobj = HSD_GObjGetHSDObj(arg0);
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

#endif
    if (itlinkarrow_inline_bool(arg0) != 0) {
        if (item->xDD4_itemVar.linkarrow.xF0 == 0) {
            it_802787B4(arg0, 0x421);
            it_802756D0((HSD_GObj*) arg0);
        }
        it_8026BB44(arg0);
        item->xDCF_flag.bits.b2 = 1;
        item->xDD4_itemVar.linkarrow.xF0 += 1;
        if (item->xDD4_itemVar.linkarrow.xF0 > 0x12C) {
            return 1;
        }
    }
    return 0;
}
#if 0
#endif

void it_802A98E4(HSD_GObj* gobj)
{
    return;
}

int it_802A98E8(HSD_GObj* gobj)
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
            mpLib_800567C0(item->xDD4_itemVar.linkarrow.xE4, &item->pos,
                           &item->x40_vel);
            mpLib_80054DFC(item->xDD4_itemVar.linkarrow.xE4, &sp18);
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

int it_802A9A80(Item_GObj* arg0)
{
    Item* item;
    itLinkArrowAttributes* attr;
    item = GET_ITEM(arg0);
    attr = item->xC4_article_data->x4_specialAttributes;
    item->x40_vel.x *= attr->x14;
    it_802A8330(arg0);
    return 1;
}

int it_802A9CE0(Item_GObj* arg0)
{
    f32 pad;
    it_802A8330(arg0);
    return 1;
}

int it_802A9B08(Item_GObj* arg0)
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

    item = GET_ITEM(arg0);
    attr = item->xC4_article_data->x4_specialAttributes;
    if (item->xCF4_fighterGObjUnk != NULL) {
        if (it_80272D40(item->xCF4_fighterGObjUnk) == 0) {
            jobj = arg0->hsd_obj;

            scale.x = item->xDD4_itemVar.linkarrow.xC0;
            scale.y = item->xDD4_itemVar.linkarrow.xC0;
            scale.z = item->xDD4_itemVar.linkarrow.xC0;
            HSD_JObjSetScale(jobj, &scale);

            it_80275158((HSD_GObj*) arg0, attr->x18);
            item->x40_vel.z = 0.0f;
            item->x40_vel.y = 0.0f;
            item->x40_vel.x = 0.0f;
            Item_80268E5C((HSD_GObj*) arg0, 2, ITEM_ANIM_UPDATE);
            it_802A9CE0(arg0);
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

// offset from jumptable
int it_802A9D4C(Item_GObj* arg0)
{
    Item* item;
    HSD_JObj* jobj;

    f32 var_f31;
    f32 temp_f31;
    f32 pad[4];

    item = GET_ITEM(arg0);
    jobj = arg0->hsd_obj;
    // could be func above
    it_802A8330(arg0);
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

void it_802AA034(Item_GObj* arg0, Item_GObj* arg1)
{
    it_8026B894(arg0, (HSD_GObj*) arg1);
}
