#include "itlinkhookshot.h"

#include "dolphin/mtx.h"
#include "ef/efsync.h"
#include "ft/chara/ftCommon/ftCo_AirCatch.h"
#include "ft/chara/ftCommon/ftCo_CliffJump.h"
#include "ft/chara/ftCommon/ftCo_DamageFall.h"
#include "ft/ft_081B.h"
#include "ft/ftcliffcommon.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "it/inlines.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbvector.h"
#include "mp/mpcoll.h"
#include "mp/mpisland.h"
#include "mp/mplib.h"
#include "mp/types.h"
#include "sysdolphin/baselib/gobjobject.h"
#include "sysdolphin/baselib/gobjplink.h"
#include "sysdolphin/baselib/jobj.h"

#include <MSL/math_ppc.h>

/* 2A5770 */ static void it_802A5770_inline(ItemLink* link_1,
                                            itLinkHookshotAttributes* arg2,
                                            Fighter* arg3, s32 var_r29);

ItemStateTable it_803F6998[] = { {
                                     -1,
                                     NULL,
                                     itLinkhookshot_UnkMotion0_Phys,
                                     NULL,
                                 },
                                 { -1, itLinkhookshot_UnkMotion8_Anim,
                                   itLinkhookshot_UnkMotion1_Phys, NULL },
                                 { -1, itLinkhookshot_UnkMotion8_Anim,
                                   itLinkhookshot_UnkMotion2_Phys, NULL },
                                 { -1, itLinkhookshot_UnkMotion8_Anim,
                                   itLinkhookshot_UnkMotion3_Phys, NULL },
                                 { -1, itLinkhookshot_UnkMotion8_Anim,
                                   itLinkhookshot_UnkMotion4_Phys, NULL },
                                 { -1, itLinkhookshot_UnkMotion8_Anim,
                                   itLinkhookshot_UnkMotion5_Phys, NULL },
                                 { -1, itLinkhookshot_UnkMotion8_Anim,
                                   itLinkhookshot_UnkMotion6_Phys, NULL },
                                 { -1, itLinkhookshot_UnkMotion8_Anim,
                                   itLinkhookshot_UnkMotion7_Phys, NULL },
                                 { -1, itLinkhookshot_UnkMotion8_Anim,
                                   itLinkhookshot_UnkMotion8_Phys, NULL } };

f32 it_804D6D48;

void it_802A2418(Item_GObj* obj)
{
    Item* item = GET_ITEM((HSD_GObj*) obj);
    item->xDD4_itemVar.linkhookshot.x10 = NULL;
}

void it_802A2428(HSD_GObj* obj)
{
    f32 temp_f1;
    Item* item;
    Item* item_owner;
    HSD_JObj* jobj;

    item = GET_ITEM(obj);
    jobj = HSD_GObjGetHSDObj(obj);
    item_owner = GET_ITEM(item->owner);
    if (item_owner != NULL) {
        temp_f1 = item_owner->scl * item->xCC_item_attr->x60_scale;
        item->scl = temp_f1;
        it_80272F7C(jobj, temp_f1);
    }
}

void it_802A2474(void* arg0)
{
    HSD_ObjFree(&item_link_alloc_data, arg0);
}

void it_802A24A0(HSD_GObj* obj, int arg1)
{
    ItemLink* link;
    link = obj->user_data;
    if (link->flag0) {
        HSD_GObj_JObjCallback(obj, arg1);
    }
}

void it_802A24D0(ItemLink* arg0, f32 arg8)
{
    CollData* coll_data;

    coll_data = &arg0->x30_collData;
    coll_data->cur_pos = arg0->pos;
    coll_data->last_pos = coll_data->cur_pos;
    mpColl_80041EE4(coll_data);
    coll_data->x34_flags.b1234 = 5;
    mpColl_SetECBSource_Fixed(coll_data, NULL, arg8, arg8, arg8, arg8);
}

static bool inline link_fighter_compare(Fighter* fp)
{
    if ((fp->motion_id == 0x168) || (fp->motion_id == 0x169) ||
        (fp->motion_id == 0xD4) || (fp->motion_id == 0xD6))
    {
        return true;
    } else {
        return false;
    }
}

static inline void it_802A2568_inline(ItemLink* temp_r3_3, HSD_JObj* arg1,
                                      HSD_GObj* temp_r3_2, Vec3* pos)
{
    temp_r3_3->x1D4_JObj = arg1;
    temp_r3_3->x1D0_GObj = temp_r3_2;
    temp_r3_3->x8_vel = *pos;
    temp_r3_3->pos = *pos;
    temp_r3_3->flag5 = 1;
    temp_r3_3->flag6 = 1;
    temp_r3_3->flag7 = 1;
    // it_802A43B8(temp_r3_3);
    temp_r3_3->x30_collData.cur_pos = temp_r3_3->pos;
    temp_r3_3->x30_collData.last_pos = temp_r3_3->x30_collData.cur_pos;
}

static inline HSD_JObj* it_link_get_joint(Item* arg0, s32 var_r31)
{
    itLinkHookshotAttributes* temp_r3_4;
    temp_r3_4 = arg0->xC4_article_data->x4_specialAttributes;
    if ((var_r31 % 2) != 0) {
        return HSD_JObjLoadJoint(temp_r3_4->x54);
    } else {
        return HSD_JObjLoadJoint(temp_r3_4->x58);
    }
}

static inline HSD_JObj* it_link_get_joint_c(Item* arg0)
{
    itLinkHookshotAttributes* temp_r3_4;
    temp_r3_4 = arg0->xC4_article_data->x4_specialAttributes;
    return HSD_JObjLoadJoint(temp_r3_4->x5C);
}

static inline f32 it_link_lerp(f32 a, f32 b, f32 t)
{
    return t * a + (1.0F - t) * b;
}

static inline void it_link_attr_math(itLinkHookshotAttributes* attr, s32 arg2,
                                     f32 arg8)
{
    f32 var_f0;
    f32 var_f1;
    if (arg2 != 0) {
        var_f0 = attr->x50;
    } else {
        var_f0 = attr->x4C;
    }
    attr->x30 = attr->x10 * arg8;
    attr->x34 = attr->x14 * arg8;
    attr->x38 = var_f0 * (attr->x18 * arg8);
    attr->x3C = attr->x1C * arg8;
    attr->x40 = var_f0 * (attr->x20 * arg8);
    attr->x44 = var_f0 * (attr->x24 * arg8);
    attr->x48 = attr->x28 * arg8;
    if (arg8 > (f64) 1.875F) {
        var_f1 =
            it_link_lerp(attr->xC * attr->x30, attr->xC * attr->x10, attr->x8);
    } else {
        var_f1 = (f32) attr->xC * attr->x30;
    }
    attr->x2C = (var_f1 * var_f0) / attr->x30;
}

HSD_JObj* it_802A2568(Item* arg0, HSD_JObj* arg1, s32 arg2, f32 arg8)
{
    CollData* temp_r17;
    CollData* temp_r18;
    CollData* temp_r21;
    HSD_GObj* temp_r3_2;
    ItemLink* temp_r3_3;
    ItemLink* var_r18;
    itLinkHookshotAttributes* temp_r3_4;
    ItemLink* var_r19;
    ItemLink* var_r20;
    f32 temp_f7;
    f32 var_f0;
    f32 var_f1;
    s32 temp_r3;
    s32 var_r31;
    itLinkHookshotAttributes* attr;
    itLinkHookshotAttributes* temp_r3_5;
    HSD_JObj* var_r21;
    Vec3 pos;

    attr = arg0->xC4_article_data->x4_specialAttributes;
    pos = it_803B8650;

    it_link_attr_math(attr, arg2, arg8);

    var_r18 = NULL;
    var_r31 = 0;

    while (!(var_r31 >= attr->x2C)) {
        temp_r3_2 = GObj_Create(HSD_GOBJ_CLASS_ITEMLINK, 0xAU, 0U);
        if (temp_r3_2 == NULL) {
            while (var_r18 != NULL) {
                HSD_GObjPLink_80390228(var_r18->x1D0_GObj);
                var_r18 = var_r18->next;
            }
            return NULL;
        }
        temp_r3_3 = HSD_ObjAlloc(&item_link_alloc_data);
        GObj_InitUserData(temp_r3_2, 6U, it_802A2474, temp_r3_3);
        if (var_r31 == 0) {
            temp_r3_3->next = NULL;
            temp_r18 = &temp_r3_3->x30_collData;
            var_r19 = temp_r3_3;

            // it_802A2568_inline(temp_r3_3, arg1, temp_r3_2, &pos);
            temp_r3_3->x1D4_JObj = arg1;
            temp_r3_3->x1D0_GObj = temp_r3_2;
            temp_r3_3->x8_vel = pos;
            temp_r3_3->pos = pos;
            temp_r3_3->flag5 = 0;
            temp_r3_3->flag6 = 0;
            temp_r3_3->flag7 = 0;
            // it_802A43B8(temp_r3_3);
            temp_r3_3->x30_collData.cur_pos = temp_r3_3->pos;
            temp_r3_3->x30_collData.last_pos = temp_r3_3->x30_collData.cur_pos;

            mpColl_80041EE4(temp_r18);
            temp_r18->x34_flags.b1234 = 5;
            mpColl_SetECBSource_Fixed(temp_r18, NULL, arg8, arg8, arg8, arg8);
            HSD_GObjObject_80390A70(temp_r3_2, (u8) HSD_GObj_804D7849,
                                    it_link_get_joint(arg0, var_r31));
            GObj_SetupGXLink(temp_r3_2, it_802A24A0, 6U, 0U);
        } else if (var_r31 == (s32) (attr->x2C - 1)) {
            var_r18->prev = temp_r3_3;
            temp_r21 = &temp_r3_3->x30_collData;
            temp_r3_3->prev = NULL;
            var_r20 = temp_r3_3;
            temp_r3_3->next = var_r18;

            temp_r3_3->x1D4_JObj = arg1;
            temp_r3_3->x1D0_GObj = temp_r3_2;
            temp_r3_3->x8_vel = pos;
            temp_r3_3->pos = pos;
            temp_r3_3->flag5 = 0;
            temp_r3_3->flag6 = 0;
            temp_r3_3->flag7 = 0;
            // it_802A43B8(temp_r3_3);
            temp_r3_3->x30_collData.cur_pos = temp_r3_3->pos;
            temp_r3_3->x30_collData.last_pos = temp_r3_3->x30_collData.cur_pos;

            mpColl_80041EE4(temp_r21);
            temp_r18->x34_flags.b1234 = 5;
            mpColl_SetECBSource_Fixed(temp_r21, NULL, arg8, arg8, arg8, arg8);
            HSD_GObjObject_80390A70(temp_r3_2, (u8) HSD_GObj_804D7849,
                                    it_link_get_joint_c(arg0));
            GObj_SetupGXLink(temp_r3_2, HSD_GObj_JObjCallback, 6U, 0U);
            var_r21 = temp_r3_2->hsd_obj;
        } else {
            var_r18->prev = temp_r3_3;
            temp_r17 = &temp_r3_3->x30_collData;
            temp_r3_3->next = var_r18;

            // it_802A2568_inline(temp_r3_3, arg1, temp_r3_2, &pos);
            temp_r3_3->x1D4_JObj = arg1;
            temp_r3_3->x1D0_GObj = temp_r3_2;
            temp_r3_3->x8_vel = pos;
            temp_r3_3->pos = pos;
            temp_r3_3->flag5 = 1;
            temp_r3_3->flag6 = 1;
            temp_r3_3->flag7 = 1;
            // it_802A43B8(temp_r3_3);
            temp_r3_3->x30_collData.cur_pos = temp_r3_3->pos;
            temp_r3_3->x30_collData.last_pos = temp_r3_3->x30_collData.cur_pos;

            mpColl_80041EE4(temp_r17);
            temp_r18->x34_flags.b1234 = 5;
            mpColl_SetECBSource_Fixed(temp_r17, NULL, arg8, arg8, arg8, arg8);
            HSD_GObjObject_80390A70(temp_r3_2, (u8) HSD_GObj_804D7849,
                                    it_link_get_joint(arg0, var_r31));
            GObj_SetupGXLink(temp_r3_2, it_802A24A0, 6U, 0U);
        }
        temp_r3_3->unk = -1;
        var_r18 = temp_r3_3;
        var_r31 += 1;
    }
    arg0->xDD4_itemVar.linkhookshot.x0 = var_r20;
    arg0->xDD4_itemVar.linkhookshot.x4 = var_r19;
    return var_r21;
}

void it_802A2B10(Item_GObj* arg0)
{
    Item* item;
    Fighter* fp;
    HSD_GObj* gobj;
    ItemLink* item_link;

    if (arg0 != NULL) {
        item = arg0->user_data;
        if (item != NULL) {
            if (item->xDD4_itemVar.linkhookshot.x8 != NULL) {
                fp = GET_FIGHTER(item->xDD4_itemVar.linkhookshot.x8);
                if (fp != NULL) {
                    item->xDD4_itemVar.linkhookshot.x10 = NULL;
                    fp->fv.lk.xC = 0;
                    fp->accessory2_cb = 0;
                    fp->death1_cb = 0;
                    fp->accessory3_cb = 0;
                    item_link = item->xDD4_itemVar.linkhookshot.x0;
                    while (item_link != NULL) {
                        gobj = item_link->x1D0_GObj;
                        item_link = item_link->next;
                        HSD_GObjPLink_80390228(gobj);
                    }
                    Item_8026A8EC(arg0);
                }
            }
        }
    }
}

Item_GObj* it_802A2BA4(Fighter_GObj* arg0, Vec3* arg1, f32 arg2, s32 arg3)
{
    Fighter* fp;
    Item* item;
    Item_GObj* gobj;
    SpawnItem spawn_item;
    s32 var_r27;
    f32 pad[8];

    fp = arg0->user_data;
    if (link_fighter_compare(fp) == 0) {
        return NULL;
    }

    spawn_item.kind = arg3;
    spawn_item.prev_pos = *arg1;
    spawn_item.pos = spawn_item.prev_pos;
    spawn_item.facing_dir = arg2;
    spawn_item.x3C_damage = 0;
    spawn_item.vel.x = spawn_item.vel.y = spawn_item.vel.z = 0.0f;
    spawn_item.x0_parent_gobj = arg0;
    spawn_item.x4_parent_gobj2 = spawn_item.x0_parent_gobj;
    spawn_item.x44_flag.b0 = true;
    spawn_item.x40 = 0;

    gobj = Item_80268B18(&spawn_item);
    if (gobj != NULL) {
        item = gobj->user_data;
        item->xDD4_itemVar.linkhookshot.x14 = 0;
        if (fp->motion_id == 0x168) {
            var_r27 = 1;
        } else {
            var_r27 = 0;
        }
        if (it_802A2568(
                item,
                fp->parts[ftParts_GetBoneIndex(fp, FtPart_RThumbNb)].joint,
                var_r27, fp->x34_scale.y) == NULL)
        {
            Item_8026A8EC(gobj);
            return NULL;
        }
        item->xDD4_itemVar.linkhookshot.x8 = arg0;
        item->xDD4_itemVar.linkhookshot.xC =
            item->xDD4_itemVar.linkhookshot.x0->x1D0_GObj->hsd_obj;
        fp->parts[139].joint = item->xDD4_itemVar.linkhookshot.xC;
        Item_8026AB54((HSD_GObj*) gobj, (HSD_GObj*) arg0,
                      ftParts_GetBoneIndex(fp, FtPart_RThumbNb));
        it_802A2428(gobj);
    }
    if ((enum FighterKind) fp->kind == FTKIND_CLINK) {
        it_804D6D48 = 6.0f;
    } else {
        it_804D6D48 = 6.0f;
    }
    return gobj;
}

bool itLinkhookshot_UnkMotion8_Anim(Item_GObj* arg0)
{
    HSD_JObj* jobj;
    Item* item;
    itLinkHookshotAttributes* attr;
    ItemLink* link_0;
    f32 temp_f0;
    f32 temp_f1;
    s32 var_r5;
    f32 pad[2];

    var_r5 = 0;
    item = GET_ITEM((HSD_GObj*) arg0);
    jobj = arg0->hsd_obj;
    link_0 = item->xDD4_itemVar.linkhookshot.x0;
    attr = item->xC4_article_data->x4_specialAttributes;
    while ((link_0 != NULL) && link_0->flag0) {
        link_0 = link_0->next;
        var_r5 += 1;
    }
    temp_f1 = (f32) var_r5 / (f32) attr->x2C;
    jobj->child->child->rotate.z = 6.2831855f * temp_f1;
    temp_f0 = (f32) ((0.6499999761581421 * (1.0 - (f64) temp_f1)) +
                     0.3499999940395355);
    jobj->child->child->scale.x = temp_f0;
    jobj->child->child->scale.y = temp_f0;
    return 0;
}

void fn_802A2E4C(Item_GObj* arg0);
void fn_802A2E4C(Item_GObj* arg0)
{
    Item* item;
    Fighter* fp;
    f32 pad[1];

    item = GET_ITEM((HSD_GObj*) arg0);
    fp = GET_FIGHTER(item->owner);
    it_802A6944(item, fp->x34_scale.y);

    if (link_fighter_compare(fp) == 0) {
        it_802A2B10(arg0);
    }
}

void itLinkhookshot_UnkMotion0_Phys(Item_GObj* arg0)
{
    Item* item = GET_ITEM((HSD_GObj*) arg0);
    item->xDD4_itemVar.linkhookshot.x10 = fn_802A2E4C;
}

static void inline it_802A2EE4_inline(MtxPtr m, ItemLink* item_link, Vec3* pos)
{
    PSMTXIdentity(m);
    m[0][3] = 0.0F;
    m[1][3] = 0.0F;
    m[2][3] = it_804D6D48;
    HSD_JObjSetupMatrix(item_link->x1D4_JObj);
    PSMTXConcat(item_link->x1D4_JObj->mtx, &m[0], &m[0]);
    pos->x = m[0][3];
    pos->y = m[1][3];
    pos->z = m[2][3];
}

static void inline it_802A2EE4_inline_alt(ItemLink* item_link, Vec3* pos)
{
    f32 zero = 0.0F;
    Mtx m;
    PSMTXIdentity((MtxPtr) &m);
    m[0][3] = zero;
    m[1][3] = zero;
    m[2][3] = it_804D6D48;
    HSD_JObjSetupMatrix(item_link->x1D4_JObj);
    PSMTXConcat(item_link->x1D4_JObj->mtx, (MtxPtr) &m, (MtxPtr) &m);
    pos->x = m[0][3];
    pos->y = m[1][3];
    pos->z = m[2][3];
}

void it_802A2EE4(Item_GObj* arg0)
{
    Vec3 pos;
    Vec3 pos_2;
    ItemKind kind;

    HSD_GObj* temp_r26_2;
    ItemLink* temp_r6;

    Item* item = GET_ITEM(arg0);
    itLinkHookshotAttributes* attr =
        item->xC4_article_data->x4_specialAttributes;
    ItemLink* item_link = item->xDD4_itemVar.linkhookshot.x0;
    Fighter* fp = item->owner->user_data;

    if ((link_fighter_compare(fp) == 0) && (item_link->next->flag0 == 0)) {
        it_802A2B10(arg0);
        return;
    }

    it_802A2EE4_inline_alt(item_link, &pos);
    switch (it_802A4BFC(item_link, &pos, attr, fp)) {
    case 1:
        if ((s32) fp->motion_id == 0x168) {
            ftCo_800C3CC0((Fighter_GObj*) item->owner);
            it_802A793C((HSD_GObj*) arg0);
            temp_r6 = item->xDD4_itemVar.linkhookshot.x0;
            pos_2 = temp_r6->pos;
            temp_r26_2 = item->xDD4_itemVar.linkhookshot.x0->x1D0_GObj;
            efSync_Spawn(0x41C, temp_r26_2, &pos_2, temp_r6);
            efSync_Spawn(0x3F1, temp_r26_2, &pos_2, &fp->facing_dir);
            return;
        }
        item_link->x8_vel.x *= -attr->x0;
        it_802A7764((HSD_GObj*) arg0);
        ftCommon_8007E2F4(fp, 0);
        break;
    case 2:
        it_802A76EC((HSD_GObj*) arg0);
        ftCommon_8007E2F4(fp, 0);
        break;
    }
    it_802A7168(item, &pos, fp->x34_scale.y);
    return;
}

void itLinkhookshot_UnkMotion1_Phys(Item_GObj* arg0)
{
    Item* item = GET_ITEM((HSD_GObj*) arg0);
    item->xDD4_itemVar.linkhookshot.x10 = it_802A2EE4;
}

static inline void mtx_reset(Mtx m)
{
    f32 zero = 0.0F;
    m[0][3] = zero;
    m[1][3] = zero;
    m[2][3] = it_804D6D48;
}

static inline void vec3_eq_mtx(Vec3* vec, Mtx m)
{
    vec->x = m[0][3];
    vec->y = m[1][3];
    vec->z = m[2][3];
}

static void inline fn_802A3110_inline(ItemLink* item_link, Vec3* pos)
{
    Mtx m;
    PSMTXIdentity(m);
    mtx_reset(m);
    HSD_JObjSetupMatrix(item_link->x1D4_JObj);
    PSMTXConcat(item_link->x1D4_JObj->mtx, m, m);
    vec3_eq_mtx(pos, m);
}

void fn_802A3110(HSD_GObj* arg0);
void fn_802A3110(HSD_GObj* arg0)
{
    Vec3 vec;
    f32 pad_3[1];

    Item* item = GET_ITEM(arg0);
    Fighter* fp = item->owner->user_data;
    itLinkHookshotAttributes* attr =
        item->xC4_article_data->x4_specialAttributes;
    ItemLink* item_link = item->xDD4_itemVar.linkhookshot.x0;

    fn_802A3110_inline(item_link, &vec);

    switch (it_802A5320(item_link, &vec, attr, fp)) {
    case 1:
        item_link->x8_vel.x *= -attr->x0;
        break;
    case 2:
        it_802A76EC(arg0);
        break;
    }
    it_802A7168(item, &vec, fp->x34_scale.y);
}

void itLinkhookshot_UnkMotion2_Phys(Item_GObj* arg0)
{
    Item* item = GET_ITEM((HSD_GObj*) arg0);
    item->xDD4_itemVar.linkhookshot.x10 = fn_802A3110;
}

void it_802A3254(Item_GObj* arg0)
{
    Vec3 pos;
    f32 pad[1];
    Mtx m;

    Item* item = GET_ITEM(arg0);
    Fighter* fp = item->owner->user_data;
    itLinkHookshotAttributes* attr =
        item->xC4_article_data->x4_specialAttributes;
    ItemLink* item_link = item->xDD4_itemVar.linkhookshot.x4;

    it_802A2EE4_inline((MtxPtr) &m, item_link, &pos);

    it_802A5770(item_link, &pos, attr, fp);
    it_802A7168(item, &pos, fp->x34_scale.y);
    if (link_fighter_compare(fp) == 0) {
        it_802A77DC(arg0);
    }
}

void itLinkhookshot_UnkMotion3_Phys(Item_GObj* arg0)
{
    Item* item = GET_ITEM((HSD_GObj*) arg0);
    item->xDD4_itemVar.linkhookshot.x10 = it_802A3254;
}

void fn_802A33A0(Item_GObj* arg0);
void fn_802A33A0(Item_GObj* arg0)
{
    ItemLink* item_link;
    Item* item;
    Fighter* fp;
    itLinkHookshotAttributes* attr;
    Vec3 vec;
    Mtx m;
    f32 pad[3];

    item = GET_ITEM((HSD_GObj*) arg0);
    attr = item->xC4_article_data->x4_specialAttributes;
    fp = item->owner->user_data;
    item_link = item->xDD4_itemVar.linkhookshot.x4;

    it_802A2EE4_inline((MtxPtr) &m, item_link, &vec);

    if (it_802A5E28(item_link, &vec, attr, fp->x40) != 0) {
        if (link_fighter_compare(fp)) {
            it_802A2B10(arg0);
            return;
        }
        it_2725_Logic20_PickedUp(arg0);
    }

    it_802A7168(item, &vec, fp->x34_scale.y);
}

void itLinkhookshot_UnkMotion4_Phys(Item_GObj* arg0)
{
    Item* item = GET_ITEM((HSD_GObj*) arg0);
    item->xDD4_itemVar.linkhookshot.x10 = fn_802A33A0;
}

void it_802A3500(Item_GObj* arg0)
{
    ItemLink* item_link;
    Mtx m;
    Vec3 pos;
    f32 pad[3];

    Item* item = GET_ITEM(arg0);
    itLinkHookshotAttributes* attr =
        item->xC4_article_data->x4_specialAttributes;
    Fighter* fp = item->owner->user_data;

    if (item->xDD4_itemVar.linkhookshot.x14 != 0) {
        it_802A2B10(arg0);
        return;
    }

    item_link = item->xDD4_itemVar.linkhookshot.x4;
    it_802A2EE4_inline((MtxPtr) &m, item_link, &pos);
    if (it_802A678C(item_link, &pos, attr, attr->x44) != 0) {
        item->xDD4_itemVar.linkhookshot.x14 = 1;
        return;
    }
    it_802A7168(item, &pos, fp->x34_scale.y);
}

void itLinkhookshot_UnkMotion5_Phys(Item_GObj* arg0)
{
    Item* item = GET_ITEM((HSD_GObj*) arg0);
    item->xDD4_itemVar.linkhookshot.x10 = it_802A3500;
}

static inline bool it_802A3630_inline(Item* item, Vec3* cur_pos, Vec3* pos)
{
    ItemLink* item_link;
    Vec3* item_link_pos;
    item_link = item->xDD4_itemVar.linkhookshot.x0;
    item_link_pos = &item_link->pos;

    if (mpCheckAllRemap(0, 0, 0, 0, -1, -1, pos->x, pos->y, item_link->pos.x,
                        item_link->pos.y) != 0)
    {
        return 1;
    } else if (mpCheckAllRemap(0, 0, 0, 0, -1, -1, cur_pos->x, cur_pos->y,
                               item_link_pos->x, item_link_pos->y) != 0)
    {
        return 1;
    } else {
        return 0;
    }
}

void it_802A3630(Item_GObj* arg0)
{
    Vec3 pos;
    Item* item = GET_ITEM(arg0);
    itLinkHookshotAttributes* attr =
        item->xC4_article_data->x4_specialAttributes;
    Fighter* fp = item->owner->user_data;
    ItemLink* item_link = item->xDD4_itemVar.linkhookshot.x4;

    it_802A2EE4_inline_alt(item->xDD4_itemVar.linkhookshot.x4, &pos);

    if (it_802A3630_inline(item, &fp->cur_pos, &pos) != 0) {
        ftCo_80090780(item->owner);
        it_802A2B10(arg0);
        return;
    }

    if (it_802A5AE0(item->xDD4_itemVar.linkhookshot.x0, &pos, attr) != 0) {
        it_802A7A04(arg0);
        it_802A7168(item, &pos, fp->x34_scale.y);
        return;
    }
    it_802A7384(item, &pos, fp->x34_scale.y);
    if (fp->ground_or_air != 1) {
        it_802A77DC(arg0);
        return;
    }
    if (fp->input.x668 & HSD_PAD_A) {
        it_802A79A0(arg0);
    }
}

void itLinkhookshot_UnkMotion6_Phys(Item_GObj* arg0)
{
    Item* item = GET_ITEM((HSD_GObj*) arg0);
    item->xDD4_itemVar.linkhookshot.x10 = it_802A3630;
}

void it_802A3828(Item_GObj* arg0)
{
    Item* item;
    Fighter* fp;
    itLinkHookshotAttributes* attr;
    ftLk_DatAttrs* lk_attr;
    ItemLink* item_link;
    Mtx m;
    Vec3 pos;
    f32 temp_f30;
    f32 temp_f31;

    item = arg0->user_data;
    fp = item->owner->user_data;
    attr = item->xC4_article_data->x4_specialAttributes;
    lk_attr = fp->dat_attrs;
    item_link = item->xDD4_itemVar.linkhookshot.x4;

    it_802A2EE4_inline((MtxPtr) &m, item_link, &pos);

    temp_f31 = fp->cur_pos.x - pos.x;
    temp_f30 = fp->cur_pos.y - m[1][3];
    if (it_802A5FE0(item->xDD4_itemVar.linkhookshot.x4,
                    item->xDD4_itemVar.linkhookshot.x0, &pos, attr,
                    attr->x40) != 0)
    {
        fp->cur_pos.x = pos.x + temp_f31;
        fp->cur_pos.y = pos.y + temp_f30;
        if ((ftCo_800C3A14((Fighter_GObj*) item->owner) != 0) &&
            (ft_80082E3C((Fighter_GObj*) item->owner) == NULL))
        {
            ftCliffCommon_80081370((Fighter_GObj*) item->owner);
        } else {
            fp->self_vel.x = 0.0f;
            ftCo_8009B390((Fighter_GObj*) item->owner, lk_attr->xB4);
        }
        it_802A2B10(arg0);
        return;
    }
    fp->cur_pos.x = pos.x + temp_f31;
    fp->cur_pos.y = pos.y + temp_f30;
    it_802A7168(item, &pos, fp->x34_scale.y);
    if (fp->ground_or_air != 1) {
        it_802A77DC(arg0);
    }
}

void itLinkhookshot_UnkMotion7_Phys(Item_GObj* arg0)
{
    Item* item = GET_ITEM((HSD_GObj*) arg0);
    item->xDD4_itemVar.linkhookshot.x10 = it_802A3828;
}

void it_802A39FC(Item_GObj* gobj)
{
    Item* item;
    Fighter* fp;
    itLinkHookshotAttributes* attr;
    ItemLink* item_link;
    ItemLink* item_link_2;
    Mtx m;
    Vec3 pos;
    Vec3 pos_2;
    int var_r0;
    f32 temp_f30;
    f32 temp_f30_2;
    f32 temp_f31;
    f32 temp_f0;
    f32 temp_f0_2;

    item = gobj->user_data;
    attr = item->xC4_article_data->x4_specialAttributes;
    fp = item->owner->user_data;
    item_link = item->xDD4_itemVar.linkhookshot.x4;

    it_802A2EE4_inline((MtxPtr) &m, item_link, &pos);

    item_link = item->xDD4_itemVar.linkhookshot.x0;

    if (mpCheckAllRemap(0, 0, 0, 0, -1, -1, pos.x, pos.y, item_link->pos.x,
                        item_link->pos.y) != 0)
    {
        var_r0 = 1;
    } else if (mpCheckAllRemap(0, 0, 0, 0, -1, -1, fp->cur_pos.x,
                               fp->cur_pos.y, item_link->pos.x,
                               item_link->pos.y) != 0)
    {
        var_r0 = 1;
    } else {
        var_r0 = 0;
    }
    if (var_r0 != 0) {
        ftCo_80090780(item->owner);
        it_802A2B10(gobj);
        return;
    }

    temp_f30 = fp->cur_pos.y - pos.y;
    pos_2.x = fp->cur_pos.x;
    temp_f31 = fp->cur_pos.x - pos.x;
    pos_2.y = fp->cur_pos.y;
    pos_2.z = fp->cur_pos.z;
    it_802A6474(item->xDD4_itemVar.linkhookshot.x4,
                item->xDD4_itemVar.linkhookshot.x0, &pos, attr);
    fp->cur_pos.x = pos_2.x + temp_f31;
    fp->cur_pos.y = pos_2.y + temp_f30;
    temp_f0 = fp->self_vel.x + (fp->cur_pos.x - pos_2.x);
    fp->self_vel.x = temp_f0;
    fp->self_vel.y = temp_f0;
    temp_f0_2 = fp->self_vel.y + (fp->cur_pos.y - pos_2.y);
    fp->self_vel.y = temp_f0_2;
    fp->pos_delta.y = temp_f0_2;
    it_802A7384(item, &pos_2, fp->x34_scale.y);
    if (fp->ground_or_air != 1) {
        it_802A77DC(gobj);
        return;
    }
    if (fp->input.x668 & HSD_PAD_A) {
        it_802A79A0(gobj);
        return;
    }
    fp->mv.lk.specialn.x0.y -= 1.0F;
    if (fp->mv.lk.specialn.x0.y <= 0.0f) {
        ftCo_80090780((Fighter_GObj*) item->owner);
        it_802A2B10(gobj);
    }
}

void itLinkhookshot_UnkMotion8_Phys(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    item->xDD4_itemVar.linkhookshot.x10 = it_802A39FC;
}

float it_802A3C98(Vec3* arg0, Vec3* arg1, Vec3* arg2)
{
    f32 inv;
    f32 len;
    arg2->x = arg0->x - arg1->x;
    arg2->y = arg0->y - arg1->y;
    arg2->z = arg0->z - arg1->z;

    len = sqrtf(arg2->x * arg2->x + arg2->y * arg2->y + arg2->z * arg2->z);
    if (len == (f64) 0.0F) {
        inv = (f64) 0.0F;
    } else {
        inv = (f64) 1.0F / len;
    }
    arg2->x *= inv;
    arg2->y *= inv;
    arg2->z *= inv;
    return len;
}

s32 it_802A3D90(ItemLink* item_link)
{
    CollData* coll;

    coll = &item_link->x30_collData;
    coll->last_pos = coll->cur_pos;
    coll->cur_pos = item_link->pos;
    if (mpColl_800471F8(coll)) {
        item_link->flag1 = 1;
    } else {
        item_link->flag1 = 0;
    }
    item_link->pos = coll->cur_pos;
    return coll->env_flags & (Collide_FloorMask | Collide_WallMask);
}

s32 it_802A3E50(ItemLink* item_link, enum FighterKind arg1, f32 arg8)
{
    ItemLink* item_link_next;
    ItemLink* item_link_next_2;
    f32 temp_f2;

    CollData* coll;
    // @todo: This is seemingly the wrong struct; there should
    // be floats at 0x8, 0xC, 0x14, 0x18
    mp_UnkStruct0* mp_island;
    bool flag;
    s32 var_r29;

    coll = &item_link->x30_collData;
    item_link_next = item_link->next;
    flag = item_link->flag1;

    if ((item_link_next != NULL) && item_link_next->flag0) {
        var_r29 = 1;
    } else {
        var_r29 = 0;
    }
    if (var_r29 != 0) {
        coll->last_pos = item_link_next->x30_collData.cur_pos;
    } else {
        coll->last_pos = coll->cur_pos;
    }
    coll->cur_pos = item_link->pos;

    if (var_r29 != 0) {
        item_link_next_2 = item_link->next;
        if (item_link_next_2->flag1 && !item_link->flag1) {
            mp_island =
                mpIsland_8005AB54(item_link_next_2->x30_collData.floor.index);
            if (mp_island != NULL) {
                if ((mp_island->x14.x < item_link->pos.x) &&
                    (mp_island->x14.y > item_link->pos.y))
                {
                    item_link->pos.x = item_link->pos.x;
                    item_link->pos.y = mp_island->x14.y;
                    return coll->env_flags &
                           (Collide_FloorMask | Collide_WallMask);
                }
                if ((mp_island->x8.x > item_link->pos.x) &&
                    (mp_island->x8.y > item_link->pos.y))
                {
                    item_link->pos.x = item_link->pos.x;
                    item_link->pos.y = mp_island->x14.y;
                    return coll->env_flags &
                           (Collide_FloorMask | Collide_WallMask);
                }
            }
        }
    }
    if (item_link->flag1) {
        item_link->flag1 = mpColl_8004B108(coll);
    } else {
        item_link->flag1 = mpColl_800471F8(coll);
    }
    if (coll->env_flags & Collide_FloorMask) {
        coll->cur_pos.x = item_link->pos.x;
    } else if (coll->env_flags & Collide_WallMask && (var_r29 != 0) &&
               (item_link->prev != NULL) &&
               (item_link->next->pos.y < item_link->pos.y))
    {
        coll->cur_pos.y += arg8;
    }
    if (item_link->flag1 && !flag && !item_link->flag2) {
        if (arg1 == FTKIND_CLINK) {
            lbAudioAx_800237A8(0x111BF, 0x7FU, 0x40U);
        } else {
            lbAudioAx_800237A8(0x2714F, 0x7FU, 0x40U);
        }
        item_link->flag2 = 1;
    }
    item_link->pos = coll->cur_pos;
    return coll->env_flags & (Collide_FloorMask | Collide_WallMask);
}

s32 it_802A40D0(ItemLink* item_link, f32 arg8)
{
    ItemLink* item_link_next;
    ItemLink* item_link_next_2;
    f32 temp_f2;

    CollData* coll;
    mp_UnkStruct0* mp_island;
    s32 flag_2;
    s32 var_r29;

    coll = &item_link->x30_collData;
    item_link_next = item_link->next;

    if ((item_link_next != NULL) && item_link_next->flag0) {
        var_r29 = 1;
    } else {
        var_r29 = 0;
    }
    if (var_r29 != 0) {
        coll->last_pos = item_link_next->x30_collData.cur_pos;
    } else {
        coll->last_pos = coll->cur_pos;
    }
    coll->cur_pos = item_link->pos;

    if (var_r29 != 0) {
        item_link_next_2 = item_link->next;
        if (item_link_next_2->flag1 && !item_link->flag1) {
            mp_island =
                mpIsland_8005AB54(item_link_next_2->x30_collData.floor.index);
            if (mp_island != NULL) {
                if ((mp_island->x14.x < item_link->pos.x) &&
                    (mp_island->x14.y > item_link->pos.y))
                {
                    item_link->pos.x = item_link->pos.x;
                    item_link->pos.y = mp_island->x14.y;
                    return coll->env_flags &
                           (Collide_FloorMask | Collide_WallMask);
                }
                if ((mp_island->x8.x > item_link->pos.x) &&
                    (mp_island->x8.y > item_link->pos.y))
                {
                    item_link->pos.x = item_link->pos.x;
                    item_link->pos.y = mp_island->x14.y;
                    return coll->env_flags &
                           (Collide_FloorMask | Collide_WallMask);
                }
            }
        }
    }
    if (item_link->flag1) {
        item_link->flag1 = mpColl_8004B108(coll);
    } else {
        item_link->flag1 = mpColl_800471F8(coll);
    }
    if (coll->env_flags & Collide_FloorMask) {
        coll->cur_pos.x = item_link->pos.x;
    } else if ((coll->env_flags & Collide_WallMask) && (var_r29 != 0) &&
               (item_link->prev != NULL) &&
               (item_link->next->pos.y < item_link->pos.y))
    {
        coll->cur_pos.y += arg8;
    }
    flag_2 = item_link->flag0;
    item_link->pos = coll->cur_pos;
    return coll->env_flags & (Collide_FloorMask | Collide_WallMask);
}

s32 it_802A42F4(ItemLink* item_link, f32 arg8)
{
    CollData* coll = &item_link->x30_collData;
    PAD_STACK(1 * 4);
    coll->last_pos = coll->cur_pos;
    coll->last_pos.y = arg8;
    coll->cur_pos = item_link->pos;
    if (mpColl_800471F8(coll)) {
        item_link->flag1 = 1;
    } else {
        item_link->flag1 = 0;
    }
    item_link->pos = coll->cur_pos;
    return coll->env_flags & (Collide_FloorMask | Collide_WallMask);
}

void it_802A43B8(ItemLink* item_link)
{
    item_link->x30_collData.cur_pos = item_link->pos;
    item_link->x30_collData.last_pos = item_link->x30_collData.cur_pos;
}

void it_802A43EC(ItemLink* item_link)
{
    item_link->x30_collData.last_pos = item_link->x30_collData.cur_pos;
    item_link->x30_collData.cur_pos = item_link->pos;
}

void it_802A4420(ItemLink* item_link)
{
    item_link->pos.x += item_link->x8_vel.x;
    item_link->pos.y += item_link->x8_vel.y;
    item_link->pos.z += item_link->x8_vel.z;
}

void it_802A4454(ItemLink* item_link)
{
    f32 pad_2[1];
    Vec3 sp10;
    f32 pad[1];

    if (mpLib_80054ED8(item_link->unk) != 0) {
        mpGetSpeed(item_link->unk, &item_link->pos, &sp10);
        item_link->pos.x += sp10.x;
        item_link->pos.y += sp10.y;
        item_link->pos.z += sp10.z;
    }
}

void it_802A44CC(ItemLink* link_0, Vec3* arg1, itLinkHookshotAttributes* arg2,
                 f32 arg8)
{
    ItemLink* link_1;
    f32 inv;
    f64 len;
    Vec3 vec;
    f32 test[2];

    link_1 = link_0->prev;

    it_802A3C98(&link_0->pos, arg1, &vec);

    link_0->pos.x = (vec.x * arg8) + arg1->x;
    link_0->pos.y = (vec.y * arg8) + arg1->y;
    link_0->pos.z = (vec.z * arg8) + arg1->z;

    while (link_1 != NULL) {
        link_1->x8_vel.y -= arg2->x3C;
        link_1->pos.x += link_1->x8_vel.x;
        link_1->pos.y += link_1->x8_vel.y;
        link_1->pos.z += link_1->x8_vel.z;
        it_802A40D0(link_1, arg2->x30);

        len = it_802A3C98(&link_1->pos, &link_0->pos, &vec);
        if (len > arg2->x30) {
            link_1->pos.x = (vec.x * arg2->x30) + link_0->pos.x;
            link_1->pos.y = (vec.y * arg2->x30) + link_0->pos.y;
            link_1->pos.z = (vec.z * arg2->x30) + link_0->pos.z;
        }
        link_0 = link_1;
        link_1 = link_1->prev;
    }
}

static inline void test_comp(Vec3* vec0, Vec3* vec1, Vec3* vec2, f32* arg2)
{
    vec0->x = (vec2->x * *arg2) + vec1->x;
    vec0->y = (vec2->y * *arg2) + vec1->y;
    vec0->z = (vec2->z * *arg2) + vec1->z;
}

void it_802A4758(ItemLink* link_0, Vec3* arg1, itLinkHookshotAttributes* arg2,
                 f32 arg8)
{
    f32 inv;
    f32 len;
    Vec3 vec;
    f32 test[8];

    ItemLink* link_1 = link_0->prev;

    len = it_802A3C98(&link_0->pos, arg1, &vec);

    link_0->pos.x = (vec.x * arg8) + arg1->x;
    link_0->pos.y = (vec.y * arg8) + arg1->y;
    link_0->pos.z = (vec.z * arg8) + arg1->z;

    while (link_1 != NULL) {
        link_1->x8_vel.y -= arg2->x3C;
        it_802A4420(link_1);

        it_802A43EC(link_1);

        len = it_802A3C98(&link_1->pos, &link_0->pos, &vec);

        if (len > arg2->x30) {
            link_1->pos.x = (vec.x * arg2->x30) + link_0->pos.x;
            link_1->pos.y = (vec.y * arg2->x30) + link_0->pos.y;
            link_1->pos.z = (vec.z * arg2->x30) + link_0->pos.z;
        }

        link_0 = link_1;
        link_1 = link_1->prev;
    }
}

void it_802A49B0(ItemLink* link_0, Vec3* arg1, itLinkHookshotAttributes* arg2,
                 f32 arg8)
{
    ItemLink* link_1;
    f32 inv;
    f64 len;
    f32 test[2];
    Vec3 vec;

    link_1 = link_0->prev;

    it_802A3C98(&link_0->pos, arg1, &vec);

    link_0->pos.x = (vec.x * arg8) + arg1->x;
    link_0->pos.y = (vec.y * arg8) + arg1->y;
    link_0->pos.z = (vec.z * arg8) + arg1->z;

    while (link_1 != NULL) {
        it_802A40D0(link_1, arg2->x30);

        len = it_802A3C98(&link_1->pos, &link_0->pos, &vec);
        if (len > arg2->x30) {
            link_1->pos.x = (vec.x * arg2->x30) + link_0->pos.x;
            link_1->pos.y = (vec.y * arg2->x30) + link_0->pos.y;
            link_1->pos.z = (vec.z * arg2->x30) + link_0->pos.z;
        }
        link_0 = link_1;
        link_1 = link_1->prev;
    }
}

s32 it_802A4BFC(ItemLink* link_0, Vec3* arg1, itLinkHookshotAttributes* attr,
                Fighter* fp)
{
    s32 flag;
    ItemLink* link_1;
    Vec3 vec;
    f64 len;
    ftLk_DatAttrs* lk_attr = fp->ft_data->ext_attr;
    PAD_STACK(14 * 4);
    if (fp->motion_id == 0xD4) {
        if (fp->mv.ca.specials.grav == lk_attr->x88) {
            Vec3 pos;
            it_802A2EE4_inline_alt(link_0, &pos);
            link_0->pos = pos;
            link_0->x30_collData.cur_pos = link_0->pos;
            link_0->x30_collData.last_pos = link_0->x30_collData.cur_pos;
            link_0->flag1 = 1;
        }
    } else if (fp->motion_id == 0xD6) {
        if (fp->mv.ca.specials.grav == lk_attr->x98) {
            Vec3 pos;
            it_802A2EE4_inline_alt(link_0, &pos);
            link_0->pos = pos;
            link_0->x30_collData.cur_pos = link_0->pos;
            link_0->x30_collData.last_pos = link_0->x30_collData.cur_pos;
            link_0->flag1 = 1;
        }
    } else if (fp->motion_id == 0x168) {
        if (fp->mv.ca.specials.grav == lk_attr->xA8) {
            Vec3 pos;
            it_802A2EE4_inline_alt(link_0, &pos);
            link_0->pos = pos;
            link_0->x30_collData.cur_pos = link_0->pos;
            link_0->x30_collData.last_pos = link_0->x30_collData.cur_pos;
            link_0->flag1 = 1;
        }
    }

    link_1 = link_0->next;
    link_0->pos.x += link_0->x8_vel.x;
    link_0->pos.y += link_0->x8_vel.y;
    link_0->pos.z += link_0->x8_vel.z;
    flag = it_802A40D0(link_0, attr->x30);
    if (flag & Collide_LeftWallMask) {
        link_0->unk = link_0->x30_collData.left_facing_wall.index;
    } else if (flag & Collide_RightWallMask) {
        link_0->unk = link_0->x30_collData.right_facing_wall.index;
    }

    while (link_1 != NULL) {
        if (link_1->flag0) {
            len = it_802A3C98(&link_1->pos, &link_0->pos, &vec);
            if (len > attr->x30) {
                link_1->pos.x = (vec.x * attr->x30) + link_0->pos.x;
                link_1->pos.y = (vec.y * attr->x30) + link_0->pos.y;
                link_1->pos.z = (vec.z * attr->x30) + link_0->pos.z;
            }
            link_1->x30_collData.last_pos = link_1->x30_collData.cur_pos;
            link_1->x30_collData.cur_pos = link_1->pos;
        } else {
            len = it_802A3C98(arg1, &link_0->pos, &vec);
            if (len > attr->x30) {
                link_1->pos.x = (vec.x * attr->x30) + link_0->pos.x;
                link_1->pos.y = (vec.y * attr->x30) + link_0->pos.y;
                link_1->pos.z = (vec.z * attr->x30) + link_0->pos.z;
                link_1->flag0 = 1;
                link_1->x30_collData.cur_pos = link_1->pos;
                link_1->x30_collData.last_pos = link_1->x30_collData.cur_pos;
            } else {
                link_1->pos = *arg1;
                link_1->flag0 = 1;
                link_1->x30_collData.cur_pos = link_1->pos;
                link_1->x30_collData.last_pos = link_1->x30_collData.cur_pos;
                if (flag & Collide_WallMask) {
                    return 1;
                }
                if (flag & Collide_CeilingMask) {
                    return 3;
                }
                if (flag & Collide_FloorMask) {
                    return 4;
                }
                return 0;
            }
        }
        link_0 = link_1;
        link_1 = link_1->next;
    }
    it_802A44CC(link_0, arg1, attr, attr->x30);
    return 2;
}

s32 it_802A5320(ItemLink* link_0, Vec3* arg1, itLinkHookshotAttributes* attr,
                Fighter* fp)
{
    ItemLink* link_1;
    f32 len;
    Vec3 vec;

    Vec3 pos;
    s32 temp_r30;
    int var_r29;

    link_1 = link_0->next;

    link_0->x8_vel.y -= attr->x3C;
    if (link_0->x8_vel.x > attr->x48) {
        link_0->x8_vel.x = link_0->x8_vel.x - attr->x48;
    } else if (link_0->x8_vel.x < -attr->x48) {
        link_0->x8_vel.x = link_0->x8_vel.x + attr->x48;
    } else {
        link_0->x8_vel.x = 0.0f;
    }
    link_0->pos.x += link_0->x8_vel.x;
    link_0->pos.y += link_0->x8_vel.y;
    link_0->pos.z += link_0->x8_vel.z;
    temp_r30 = it_802A40D0(link_0, attr->x30) & Collide_WallMask;
    var_r29 = 0;

    while (link_1 != NULL) {
        if (link_1->flag0) {
            link_1->x8_vel.y -= attr->x3C;
            link_1->pos.x += link_1->x8_vel.x;
            link_1->pos.y += link_1->x8_vel.y;
            link_1->pos.z += link_1->x8_vel.z;
            if (var_r29 == (s32) ((s32) attr->x2C / 2)) {
                it_802A3E50(link_1, fp->kind, attr->x30);
            } else {
                it_802A40D0(link_1, attr->x30);
            }
            len = it_802A3C98(&link_1->pos, &link_0->pos, &vec);
            if (len > attr->x30) {
                link_1->pos.x = (vec.x * attr->x30) + link_0->pos.x;
                link_1->pos.y = (vec.y * attr->x30) + link_0->pos.y;
                link_1->pos.z = (vec.z * attr->x30) + link_0->pos.z;
            }
            link_1->x30_collData.last_pos = link_1->x30_collData.cur_pos;
            link_1->x30_collData.cur_pos = link_1->pos;
        } else {
            len = it_802A3C98(arg1, &link_0->pos, &vec);
            if (len > attr->x30) {
                link_1->pos.x = (vec.x * attr->x30) + link_0->pos.x;
                link_1->pos.y = (vec.y * attr->x30) + link_0->pos.y;
                link_1->pos.z = (vec.z * attr->x30) + link_0->pos.z;
                link_1->flag0 = 1;
                link_1->x30_collData.cur_pos = link_1->pos;
                link_1->x30_collData.last_pos = link_1->x30_collData.cur_pos;
            } else {
                link_1->pos = *arg1;
                link_1->flag0 = 1;
                link_1->x30_collData.cur_pos = link_1->pos;
                link_1->x30_collData.last_pos = link_1->x30_collData.cur_pos;
                if (temp_r30 != 0) {
                    return 1;
                }
                return 0;
            }
            break;
        }
        link_0 = link_1;
        link_1 = link_1->next;
        var_r29 += 1;
    }
    it_802A44CC(link_0, arg1, attr, attr->x30);
    return 2;
}

void it_802A5770_inline(ItemLink* link_1, itLinkHookshotAttributes* arg2,
                        Fighter* arg3, s32 var_r29)
{
    if (var_r29 == arg2->x2C / 2) {
        it_802A3E50(link_1, arg3->kind, arg2->x30);
    } else {
        it_802A40D0(link_1, arg2->x30);
    }
}

// definitely attributes
void it_802A5770(ItemLink* link_0, Vec3* arg1, itLinkHookshotAttributes* arg2,
                 Fighter* arg3)
{
    ItemLink* link_1;
    f32 len;
    s32 var_r29;
    Vec3 vec;
    link_1 = link_0->prev;

    while (link_1 != NULL && link_0->flag0) {
        link_0 = link_1;
        link_1 = link_0->prev;
    }

    link_1->x8_vel.y -= arg2->x3C;
    // it_802A4420(link_1);
    link_1->pos.x += link_1->x8_vel.x;
    link_1->pos.y += link_1->x8_vel.y;
    link_1->pos.z += link_1->x8_vel.z;
    it_802A40D0(link_1, arg2->x30);

    len = it_802A3C98(&link_1->pos, &link_0->pos, &vec);
    if (len > arg2->x30) {
        link_1->pos.x = (vec.x * arg2->x30) + link_0->pos.x;
        link_1->pos.y = (vec.y * arg2->x30) + link_0->pos.y;
        link_1->pos.z = (vec.z * arg2->x30) + link_0->pos.z;
    }

    var_r29 = 0;
    while (link_1 != NULL) {
        link_1->x8_vel.y -= arg2->x3C;
        link_1->pos.x += link_1->x8_vel.x;
        link_1->pos.y += link_1->x8_vel.y;
        link_1->pos.z += link_1->x8_vel.z;

        it_802A5770_inline(link_1, arg2, arg3, var_r29);

        len = it_802A3C98(&link_1->pos, &link_0->pos, &vec);
        if (len > arg2->x30) {
            link_1->pos.x = (vec.x * arg2->x30) + link_0->pos.x;
            link_1->pos.y = (vec.y * arg2->x30) + link_0->pos.y;
            link_1->pos.z = (vec.z * arg2->x30) + link_0->pos.z;
        }
        link_0 = link_1;
        link_1 = link_1->prev;
        var_r29 += 1;
    }

    if (link_0->x8_vel.x > arg2->x48) {
        link_0->x8_vel.x = link_0->x8_vel.x - arg2->x48;
        return;
    }
    if (link_0->x8_vel.x < -arg2->x48) {
        link_0->x8_vel.x = link_0->x8_vel.x + arg2->x48;
        return;
    }
    link_0->x8_vel.x = 0.0f;
}

s32 it_802A5AE0(ItemLink* link_0, Vec3* arg1, itLinkHookshotAttributes* arg2)
{
    ItemLink* link_1;
    f32 len;
    f32 test[2];
    Vec3 vec;

    it_802A4454(link_0);

    link_1 = link_0->next;
    while (link_1 != NULL) {
        if (link_1->flag0) {
            link_1->x8_vel.y -= arg2->x3C;
            // it_802A4420(link_1);
            link_1->pos.x += link_1->x8_vel.x;
            link_1->pos.y += link_1->x8_vel.y;
            link_1->pos.z += link_1->x8_vel.z;
            it_802A40D0(link_1, arg2->x30);

            len = it_802A3C98(&link_1->pos, &link_0->pos, &vec);
            if (len > arg2->x30) {
                link_1->pos.x = (vec.x * arg2->x30) + link_0->pos.x;
                link_1->pos.y = (vec.y * arg2->x30) + link_0->pos.y;
                link_1->pos.z = (vec.z * arg2->x30) + link_0->pos.z;
            }
        } else {
            len = it_802A3C98(arg1, &link_0->pos, &vec);
            if (len > arg2->x30) {
                link_1->pos.x = (vec.x * arg2->x30) + link_0->pos.x;
                link_1->pos.y = (vec.y * arg2->x30) + link_0->pos.y;
                link_1->pos.z = (vec.z * arg2->x30) + link_0->pos.z;
                link_1->flag0 = 1;
                link_1->x30_collData.cur_pos = link_1->pos;
                link_1->x30_collData.last_pos = link_1->x30_collData.cur_pos;
            } else {
                return 0;
            }
        }
        link_0 = link_1;
        link_1 = link_1->next;
    }
    return 1;
}

s32 it_802A5E28(ItemLink* link_0, Vec3* arg1, itLinkHookshotAttributes* arg2,
                f32 arg8)
{
    ItemLink* link_1;
    f32 len;
    f32 var_f1;
    f32 test[2];
    Vec3 vec;
    f32 testa;

    link_1 = link_0->prev;

    while (link_1 != NULL && !link_0->flag0) {
        link_0 = link_1;
        link_1 = link_0->prev;
    }

    len = it_802A3C98(&link_0->pos, arg1, &vec);

    while ((link_1 != NULL) && (arg8 > len)) {
        link_0->flag0 = 0;
        len = it_802A3C98(&link_1->pos, arg1, &vec);
        link_0 = link_1;
        link_1 = link_1->prev;
    }
    if (len - arg8 > arg2->x30) {
        var_f1 = arg2->x30;
    } else {
        var_f1 = len - arg8;
    }
    it_802A44CC(link_0, arg1, arg2, var_f1);
    if (link_1 != NULL) {
        return 0;
    }
    return 1;
}

s32 it_802A5FE0(ItemLink* link_0, ItemLink* link_0_2, Vec3* arg2,
                itLinkHookshotAttributes* arg3, f32 arg8)
{
    ItemLink* link_1;
    f32 len;
    f32 var_r31;
    Vec3 vec;
    Vec3 vec2;
    f32 var_f31;
    f32 var_f1;

    it_802A4454(link_0_2);

    link_1 = link_0->prev;
    var_r31 = 0;

    vec2 = link_0_2->pos;

    while (link_1 != NULL && link_0->flag0) {
        link_0 = link_1;
        link_1 = link_0->prev;
    }

    it_802A44CC(link_0, arg2, arg3, arg3->x30);

    link_0_2->pos = vec2;

    len = it_802A3C98(&link_0->pos, arg2, &vec);

    while ((link_1 != NULL) && (arg8 > len)) {
        link_0->flag0 = 0;
        len = it_802A3C98(&link_1->pos, arg2, &vec);
        link_0 = link_1;
        link_1 = link_1->prev;
    }
    if (len - arg8 > arg3->x30) {
        var_f1 = arg3->x30;
    } else {
        var_f1 = len - arg8;
    }
    it_802A49B0(link_0, arg2, arg3, var_f1);
    link_0_2->pos = vec2;
    link_1 = link_0_2->next;
    while ((link_1 != NULL) && (arg8 > len)) {
        var_r31 += 1;
        len = it_802A3C98(&link_1->pos, &link_0_2->pos, &vec);
        if (len > arg3->x30) {
            link_1->pos.x = (vec.x * arg3->x30) + link_0_2->pos.x;
            link_1->pos.y = (vec.y * arg3->x30) + link_0_2->pos.y;
            link_1->pos.z = (vec.z * arg3->x30) + link_0_2->pos.z;
        }
        link_0_2 = link_1;
        link_1 = link_1->next;
    }
    len = it_802A3C98(arg2, &link_0_2->pos, &vec);
    if (len > arg3->x30) {
        arg2->x = (vec.x * arg3->x30) + link_0_2->pos.x;
        arg2->y = (vec.y * arg3->x30) + link_0_2->pos.y;
        arg2->z = (vec.z * arg3->x30) + link_0_2->pos.z;
    }
    if (var_r31 != 0) {
        return 0;
    }
    return 1;
}

void it_802A6474(ItemLink* link_0, ItemLink* link_0_2, Vec3* arg2,
                 itLinkHookshotAttributes* arg3)
{
    NOT_IMPLEMENTED;
}

s32 it_802A678C(ItemLink* link_0, Vec3* arg1, itLinkHookshotAttributes* arg2,
                f32 arg8)
{
    ItemLink* link_1;
    f32 inv;
    f32 len;
    Vec3 vec;
    f32 test[2];
    f32 var_f1;

    link_1 = link_0->prev;

    while (link_1 != NULL && !link_0->flag0) {
        link_0 = link_1;
        link_1 = link_0->prev;
    }

    len = it_802A3C98(&link_0->pos, arg1, &vec);

    while (link_1 != NULL && (arg8 > len)) {
        link_0->flag0 = 0;
        len = it_802A3C98(&link_1->pos, arg1, &vec);
        link_0 = link_1;
        link_1 = link_1->prev;
    }
    if (len - arg8 > arg2->x30) {
        var_f1 = arg2->x30;
    } else {
        var_f1 = len - arg8;
    }
    it_802A44CC(link_0, arg1, arg2, var_f1);
    if (link_1 != NULL) {
        return 0;
    }
    return 1;
}

void it_802A6944(Item* item, f32 scl)
{
    Mtx m;
    f32 zero = 0.0F;
    f32 pad[2];

    ItemLink* item_link = item->xDD4_itemVar.linkhookshot.x0;
    HSD_JObj* jobj = item_link->x1D0_GObj->hsd_obj;

    HSD_JObjSetupMatrix(item_link->x1D4_JObj);
    PSMTXIdentity(m);
    m[0][3] = zero;
    m[1][3] = zero;
    m[2][3] = it_804D6D48;
    PSMTXConcat(item_link->x1D4_JObj->mtx, m, m);
    HSD_JObjCopyMtx(jobj, m);
    jobj->flags |= 0x03800000;
    HSD_JObjSetMtxDirty(jobj);
}

s32 it_802A6A78(ItemLink* link_0, Vec3* arg1, itLinkHookshotAttributes* arg2,
                Fighter* arg3)
{
    ItemLink* link_1;
    ftLk_DatAttrs* lk_attr;
    Vec3 vec;
    f64 len;
    f32 inv;

    lk_attr = arg3->ft_data->ext_attr;
    switch (arg3->motion_id) {
    case 0xD4:
        if (arg3->mv.ca.specials.grav < lk_attr->x88) {
            return 1;
        }
        break;
    case 0xD6:
        if (arg3->mv.ca.specials.grav < lk_attr->x98) {
            return 1;
        }
        break;
    case 0x168:
        if (arg3->mv.ca.specials.grav < lk_attr->xA8) {
            return 1;
        }
        break;
    default:
        break;
    }

    link_1 = link_0->next;
    while (link_1 != NULL) {
        if (link_1->flag0) {
            vec.x = link_1->pos.x - link_0->pos.x;
            vec.y = link_1->pos.y - link_0->pos.y;
            vec.z = link_1->pos.z - link_0->pos.z;

            len = sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);

            if (len == 0.0F) {
                inv = 0.0F;
            } else {
                inv = 1.0F / len;
            }
            vec.x *= inv;
            vec.y *= inv;
            vec.z *= inv;
            if (len > arg2->x30) {
                link_1->pos.x = (vec.x * arg2->x30) + link_0->pos.x;
                link_1->pos.y = (vec.y * arg2->x30) + link_0->pos.y;
                link_1->pos.z = (vec.z * arg2->x30) + link_0->pos.z;
            }
            link_1->x30_collData.last_pos = link_1->x30_collData.cur_pos;
            link_1->x30_collData.cur_pos = link_1->pos;
        } else {
            vec.x = arg1->x - link_0->pos.x;
            vec.y = arg1->y - link_0->pos.y;
            vec.z = arg1->z - link_0->pos.z;

            len = sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);

            if (len == 0.0F) {
                inv = 0.0F;
            } else {
                inv = 1.0F / len;
            }
            vec.x *= inv;
            vec.y *= inv;
            vec.z *= inv;
            if (len > arg2->x30) {
                link_1->pos.x = (vec.x * arg2->x30) + link_0->pos.x;
                link_1->pos.y = (vec.y * arg2->x30) + link_0->pos.y;
                link_1->pos.z = (vec.z * arg2->x30) + link_0->pos.z;
                link_1->flag0 = 1;
                link_1->x30_collData.last_pos = link_1->x30_collData.cur_pos;
                link_1->x30_collData.cur_pos = link_1->pos;
            }
        }
        link_0 = link_1;
        link_1 = link_1->next;
    }
    it_802A49B0(link_0, arg1, arg2, arg2->x30);
    return 0;
}

void it_802A6DC8(HSD_JObj* arg0, Vec3* arg1, Vec3* arg2)
{
    Mtx m;
    Vec3 vec1;
    Vec3 vec0;

    lbVector_Normalize(arg2);
    if (arg2->y > 0.9999) {
        vec1.x = -1.0f;
        vec1.y = 0.0f;
        vec1.z = 0.0f;
    } else if (arg2->y < -0.9999) {
        vec1.x = 1.0f;
        vec1.y = 0.0f;
        vec1.z = 0.0f;
    } else {
        vec1.x = 0.0f;
        vec1.y = 1.0f;
        vec1.z = 0.0f;
    }
    PSVECCrossProduct(&vec1, arg2, &vec0);
    PSVECCrossProduct(arg2, &vec0, &vec1);
    lbVector_Normalize(&vec0);
    lbVector_Normalize(&vec1);
    PSMTXIdentity((MtxPtr) &m);

    m[0][0] = vec0.x;
    m[1][0] = vec0.y;
    m[2][0] = vec0.z;

    m[0][1] = vec1.x;
    m[1][1] = vec1.y;
    m[2][1] = vec1.z;

    m[0][2] = arg2->x;
    m[1][2] = arg2->y;
    m[2][2] = arg2->z;

    m[0][3] = arg1->x;
    m[1][3] = arg1->y;
    m[2][3] = arg1->z;

    HSD_JObjCopyMtx(arg0, m);
    arg0->flags |= 0x03800000;
    HSD_JObjSetMtxDirty(arg0);
}

void it_802A6F80(HSD_JObj* arg0, Vec3* arg1, Vec3* arg2, f32 arg3)
{
    Mtx m1;
    Mtx m0;
    Vec3 vec1;
    Vec3 vec0;

    lbVector_Normalize(arg2);
    if (arg2->y > 0.9999) {
        vec1.x = -1.0f;
        vec1.y = 0.0f;
        vec1.z = 0.0f;
    } else if (arg2->y < -0.9999) {
        vec1.x = 1.0f;
        vec1.y = 0.0f;
        vec1.z = 0.0f;
    } else {
        vec1.x = 0.0f;
        vec1.y = 1.0f;
        vec1.z = 0.0f;
    }
    PSVECCrossProduct(&vec1, arg2, &vec0);
    PSVECCrossProduct(arg2, &vec0, &vec1);
    lbVector_Normalize(&vec0);
    lbVector_Normalize(&vec1);
    PSMTXIdentity(m1);
    PSMTXIdentity(m0);

    m0[0][0] = arg3;
    m0[1][1] = arg3;
    m0[2][2] = arg3;

    m1[0][0] = vec0.x;
    m1[1][0] = vec0.y;
    m1[2][0] = vec0.z;

    m1[0][1] = vec1.x;
    m1[1][1] = vec1.y;
    m1[2][1] = vec1.z;

    m1[0][2] = arg2->x;
    m1[1][2] = arg2->y;
    m1[2][2] = arg2->z;

    m1[0][3] = arg1->x;
    m1[1][3] = arg1->y;
    m1[2][3] = arg1->z;

    PSMTXConcat(m1, m0, m1);
    HSD_JObjCopyMtx(arg0, m1);
    arg0->flags |= 0x03800000;
    HSD_JObjSetMtxDirty(arg0);
}

void it_802A7168(Item* arg0, Vec3* arg1, f32 arg8)
{
    HSD_JObj* jobj;
    Fighter* fp;
    ItemLink* item_link;
    Vec3 vec;
    Vec3 vec_2;
    Vec3 vec_3;
    Vec3 vec_4;
    PAD_STACK(4);

    fp = GET_FIGHTER(arg0->owner);
    if (fp->kind == FTKIND_LINK) {
        item_link = arg0->xDD4_itemVar.linkhookshot.x4;
    } else {
        item_link = arg0->xDD4_itemVar.linkhookshot.x4;
    }

    while (!item_link->flag0) {
        item_link = item_link->prev;
    }

    while (item_link != NULL) {
        if (item_link->next != NULL) {
            if (item_link->next->flag0) {
                vec = item_link->next->pos;
            } else {
                vec = *arg1;
            }
        } else {
            vec = *arg1;
        }

        if (item_link->prev != NULL) {
            vec_2 = item_link->prev->pos;
        } else {
            vec_2 = item_link->pos;
        }
        jobj = GET_JOBJ(item_link->x1D0_GObj);
        vec_3 = item_link->pos;
        HSD_JObjSetTranslate(jobj, &vec_3);
        vec_4.x = vec_2.x - vec.x;
        vec_4.y = vec_2.y - vec.y;
        vec_4.z = vec_2.z - vec.z;
        it_802A6F80(jobj, &vec_3, &vec_4, arg8);
        item_link = item_link->prev;
    }
}

void it_802A7384(Item* arg0, Vec3* arg1, f32 arg8)
{
    NOT_IMPLEMENTED;
}

static inline void it_2725_Logic20_PickedUp_inline(HSD_GObj* arg0)
{
    Item* item;
    Fighter* fp;
    HSD_JObj* jobj;
    f32 temp_f1;
    item = GET_ITEM(arg0);
    jobj = arg0->hsd_obj;
    if (item->owner->user_data != NULL) {
        fp = item->owner->user_data;
        temp_f1 = fp->x34_scale.y * item->xCC_item_attr->x60_scale;
        item->scl = temp_f1;
        it_80272F7C(jobj, temp_f1);
    }
}

void it_2725_Logic20_PickedUp(Item_GObj* arg0)
{
    f32 pad[7];
    Item_80268E5C((HSD_GObj*) arg0, 0, ITEM_ANIM_UPDATE);
    it_2725_Logic20_PickedUp_inline(arg0);
}

void it_802A76EC(HSD_GObj* arg0)
{
    Item* item;
    f32 pad[4];
    item = GET_ITEM(arg0);
    Item_80268E5C(arg0, 3, ITEM_ANIM_UPDATE);
    ftColl_8007AFF8(item->xDD4_itemVar.linkhookshot.x8);
    it_2725_Logic20_PickedUp_inline(arg0);
}

void it_802A7764(HSD_GObj* arg0)
{
    Item* item;
    f32 pad[4];
    item = GET_ITEM(arg0);
    Item_80268E5C(arg0, 2, ITEM_ANIM_UPDATE);
    ftColl_8007AFF8(item->xDD4_itemVar.linkhookshot.x8);
    it_2725_Logic20_PickedUp_inline(arg0);
}

void it_802A77DC(Item_GObj* arg0)
{
    Item* item;
    f32 pad[4];
    item = GET_ITEM((HSD_GObj*) arg0);
    Item_80268E5C((HSD_GObj*) arg0, 4, ITEM_ANIM_UPDATE);
    it_2725_Logic20_PickedUp_inline((HSD_GObj*) arg0);
}

void it_802A7840(HSD_GObj* arg0)
{
    Item* item;
    f32 pad[4];
    item = GET_ITEM(arg0);
    Item_80268E5C(arg0, 5, ITEM_ANIM_UPDATE);
    ftColl_8007AFF8(item->xDD4_itemVar.linkhookshot.x8);
    it_2725_Logic20_PickedUp_inline(arg0);
}

void it_802A78B8(HSD_GObj* arg0, Vec3* arg1, f32 arg2)
{
    ItemLink* item_link;
    Item* item;
    f32 pad[2];

    item = GET_ITEM(arg0);
    item_link = item->xDD4_itemVar.linkhookshot.x0;
    item_link->x8_vel = *arg1;
    Item_80268E5C(arg0, 1, ITEM_ANIM_UPDATE);
    it_2725_Logic20_PickedUp_inline(arg0);
}

void it_802A793C(HSD_GObj* arg0)
{
    f32 pad[6];
    Item_80268E5C(arg0, 6, ITEM_ANIM_UPDATE);
    it_2725_Logic20_PickedUp_inline(arg0);
}

void it_802A79A0(HSD_GObj* arg0)
{
    f32 pad[6];
    Item_80268E5C(arg0, 7, ITEM_ANIM_UPDATE);
    it_2725_Logic20_PickedUp_inline(arg0);
}

void it_802A7A04(HSD_GObj* arg0)
{
    Item* item;
    Fighter* fp;
    ftLk_DatAttrs* lk_attr;
    f32 pad[6];

    item = GET_ITEM(arg0);
    fp = item->owner->user_data;
    lk_attr = fp->dat_attrs;

    Item_80268E5C(arg0, 8, ITEM_ANIM_UPDATE);
    it_2725_Logic20_PickedUp_inline(arg0);
    // @todo: should this be its own struct?
    fp->mv.lk.specialn.x0.y = lk_attr->xB8;
}

void it_802A7AAC(HSD_GObj* arg0)
{
    Fighter* fp;

    fp = arg0->user_data;
    if (fp->fv.lk.xC != NULL) {
        it_802A2B10(fp->fv.lk.xC);
        return;
    }
    fp->accessory2_cb = NULL;
    fp->death1_cb = NULL;
    fp->accessory3_cb = NULL;
}

void it_802A7AF0(HSD_GObj* arg0)
{
    Item* item;
    Fighter* fp;

    fp = arg0->user_data;
    if (fp->fv.lk.xC != NULL) {
        item = GET_ITEM((HSD_GObj*) fp->fv.lk.xC);
        if (item->xDD4_itemVar.linkhookshot.x10) {
            item->xDD4_itemVar.linkhookshot.x10(fp->fv.lk.xC);
        }
    }
}

void it_802A7B34(HSD_GObj* arg0)
{
    Vec3 vec;

    Fighter* fp = GET_FIGHTER(arg0);
    if (fp->fv.lk.xC != NULL) {
        Item* item = GET_ITEM(fp->fv.lk.xC);
        itLinkHookshotAttributes* attr =
            item->xC4_article_data->x4_specialAttributes;
        ItemLink* item_link = item->xDD4_itemVar.linkhookshot.x0;

        it_802A2EE4_inline_alt(item_link, &vec);

        if (it_802A6A78(item_link, &vec, attr, fp) != 0) {
            it_802A6944(item, fp->x34_scale.y);
        } else {
            it_802A7168(item, &vec, fp->x34_scale.y);
        }
    }
}

void it_802A7D40(Item_GObj* arg0, Item_GObj* arg1)
{
    Item* item = GET_ITEM((HSD_GObj*) arg0);
    it_8026B894(arg0, (HSD_GObj*) arg1);
    if ((HSD_GObj*) item->xDD4_itemVar.linkhookshot.x8 == arg1) {
        item->xDD4_itemVar.linkhookshot.x8 = NULL;
    }
}
