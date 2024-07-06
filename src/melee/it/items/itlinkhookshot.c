#include "ft/ftparts.h"

#include "ft/ftcoll.h"


#include "ft/chara/ftLink/forward.h"

#include "itlinkhookshot.h"

#include "ef/efsync.h"
#include "dolphin/mtx/vec.h"
#include "ft/chara/ftCommon/ftCo_AirCatch.h"
#include "ft/chara/ftCommon/ftCo_CliffJump.h"
#include "ft/chara/ftCommon/ftCo_DamageFall.h"
#include "ft/chara/ftCommon/inlines.h"
#include "ft/ft_081B.h"
#include "ft/ftcliffcommon.h"
#include "ft/ftcommon.h"
#include "ft/ftlib.h"
#include "ft/inlines.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/item.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbvector.h"
#include "MetroTRK/intrinsics.h"
#include "mp/mpcoll.h"
#include "mp/mpisland.h"
#include "mp/mplib.h"
#include "mp/types.h"
#include "sysdolphin/baselib/gobjobject.h"
#include "sysdolphin/baselib/gobjplink.h"
#include "sysdolphin/baselib/jobj.h"
#include "sysdolphin/baselib/mtx.h"


ItemStateTable it_803F6998[] = {
    { -1, NULL, it_802A2ED0, NULL, },
    { -1, it_802A2D88, it_802A30FC, NULL },
    { -1, it_802A2D88, it_802A3240, NULL },
    { -1, it_802A2D88, it_802A338C, NULL },
    { -1, it_802A2D88, it_802A34EC, NULL },
    { -1, it_802A2D88, it_802A361C, NULL },
    { -1, it_802A2D88, it_802A3814, NULL },
    { -1, it_802A2D88, it_802A39E8, NULL },
    { -1, it_802A2D88, it_802A3C84, NULL }
};

f32 it_804D6D48;

void it_802A2418(Item_GObj* arg0)
{
    Item* item = GET_ITEM((HSD_GObj*) arg0);
    item->xDD4_itemVar.linkhookshot.x10 = NULL;
}

static inline multiply_scale(Item* item_owner, Item* item)
{
    return item_owner->scl * item->xCC_item_attr->x60_scale;
}

void it_802A2428(HSD_GObj* arg0)
{
    f32 temp_f1;
    Item* item;
    Item* item_owner;
    HSD_JObj* jobj;

    item = GET_ITEM(arg0);
    jobj = HSD_GObjGetHSDObj(arg0);
    item_owner = GET_ITEM(item->owner);
    if (item_owner != NULL) {
        temp_f1 = item_owner->scl * item->xCC_item_attr->x60_scale;
        item->scl = temp_f1;
        it_80272F7C(jobj, temp_f1);
    }
}

void it_802A2474(void* arg0)
{
    HSD_ObjFree(&Item_804A0C38, arg0);
}

void it_802A24A0(HSD_GObj* arg0, int arg1)
{
    ItemLink* item_link;
    item_link = arg0->user_data;
    if (item_link->flag0) {
        HSD_GObj_80391070(arg0, arg1);
    }
}

void it_802A24D0(ItemLink* arg0, f32 arg8)
{
    CollData* coll_data;

    coll_data = &arg0->x30_collData;
    coll_data->cur_topn = arg0->pos;
    coll_data->prev_topn = coll_data->cur_topn;
    mpColl_80041EE4(coll_data);
    coll_data->x34_flags.bits.b1234 = 5;
    mpColl_8004220C(coll_data, NULL, arg8, arg8, arg8, arg8);
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

void fn_802A2E4C(Item_GObj *arg0);
void fn_802A2E4C(Item_GObj *arg0) {
    Item *item;
    Fighter *fp;
    f32 pad[1];

    item = GET_ITEM((HSD_GObj*) arg0);
    fp = GET_FIGHTER(item->owner);
    it_802A6944(item, fp->x34_scale.y);

    if (link_fighter_compare(fp) == 0) {
        it_802A2B10(arg0);
    }
}

void* it_802A2568(Item* arg0, HSD_GObj* arg1, s32 arg2, f32 arg8)
{
    Vec3 pos;
    CollData* temp_r17;
    CollData* temp_r18;
    CollData* temp_r21;
    HSD_GObj* temp_r3_2;
    HSD_JObj* var_r5;
    HSD_JObj* var_r5_2;
    ItemLink* temp_r3_3;
    ItemLink* var_r18;
    ItemLink* var_r19;
    ItemLink* var_r20;
    f32 temp_f7;
    f32 var_f0;
    f32 var_f1;
    s32 temp_r3;
    s32 var_r31;
    itLinkHookshotAttributes* attr;
    itLinkHookshotAttributes* temp_r3_4;
    itLinkHookshotAttributes* temp_r3_5;
    void* var_r21;

    // var_r19 = saved_reg_r19;
    // var_r20 = saved_reg_r20;
    // var_r21 = saved_reg_r21;

    attr = arg0->xC4_article_data->x4_specialAttributes;
    pos = it_803B8650;
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
    if (arg8 > 1.0F) {
        temp_r3 = attr->xC;
        temp_f7 = attr->x8;
        var_f1 = (temp_f7 * ((f32) temp_r3 * attr->x30)) +
                 ((1.0F - temp_f7) * ((f32) temp_r3 * attr->x10));
    } else {
        var_f1 = (f32) attr->xC * attr->x30;
    }
    var_r18 = NULL;
    var_r31 = 0;
    attr->x2C = (var_f1 * var_f0) / attr->x30;

    while (var_r31 >= attr->x2C) {
        temp_r3_2 = GObj_Create(7U, 0xAU, 0U);
        if (temp_r3_2 == NULL) {
            while (var_r18 != NULL) {
                HSD_GObjPLink_80390228(var_r18->x1D0_GObj);
                var_r18 = var_r18->next;
            }
            return NULL;
        }
        temp_r3_3 = HSD_ObjAlloc(&Item_804A0C38);
        GObj_InitUserData(temp_r3_2, 6U, it_802A2474, temp_r3_3);
        if (var_r31 == 0) {
            temp_r3_3->next = NULL;
            temp_r18 = &temp_r3_3->x30_collData;
            var_r19 = temp_r3_3;
            temp_r3_3->x1D4_GObjLinkNext = arg1;
            temp_r3_3->x1D0_GObj = temp_r3_2;
            temp_r3_3->x8_vel = pos;
            temp_r3_3->pos = pos;
            temp_r3_3->flag5 = 1;
            temp_r3_3->flag6 = 1;
            temp_r3_3->flag7 = 1;
            temp_r3_3->x30_collData.cur_topn = temp_r3_3->pos;
            temp_r3_3->x30_collData.prev_topn =
                temp_r3_3->x30_collData.cur_topn;
            mpColl_80041EE4(temp_r18);
            temp_r18->x34_flags.raw = (temp_r18->x34_flags.raw & ~0x78) | 0x28;
            mpColl_8004220C(temp_r18, NULL, arg8, arg8, arg8, arg8);
            temp_r3_4 = arg0->xC4_article_data->x4_specialAttributes;
            if ((var_r31 % 2) != 0) {
                var_r5 = HSD_JObjLoadJoint(temp_r3_4->x54);
            } else {
                var_r5 = HSD_JObjLoadJoint(temp_r3_4->x58);
            }
            HSD_GObjObject_80390A70(temp_r3_2, (u8) HSD_GObj_804D7849, var_r5);
            GObj_SetupGXLink(temp_r3_2, it_802A24A0, 6U, 0U);
        } else if (var_r31 == (s32) (attr->x2C - 1)) {
            var_r18->prev = temp_r3_3;
            temp_r21 = &temp_r3_3->x30_collData;
            temp_r3_3->prev = NULL;
            var_r20 = temp_r3_3;
            temp_r3_3->next = var_r18;
            temp_r3_3->x1D4_GObjLinkNext = arg1;
            temp_r3_3->x1D0_GObj = temp_r3_2;
            temp_r3_3->x8_vel = pos;
            temp_r3_3->pos = pos;
            temp_r3_3->flag5 = 1;
            temp_r3_3->flag6 = 1;
            temp_r3_3->flag7 = 1;
            temp_r3_3->x30_collData.cur_topn = temp_r3_3->pos;
            temp_r3_3->x30_collData.prev_topn =
                temp_r3_3->x30_collData.cur_topn;
            mpColl_80041EE4(temp_r21);
            temp_r21->x34_flags.raw = (temp_r21->x34_flags.raw & ~0x78) | 0x28;
            mpColl_8004220C(temp_r21, NULL, arg8, arg8, arg8, arg8);
            temp_r3_4 = arg0->xC4_article_data->x4_specialAttributes;
            HSD_GObjObject_80390A70(temp_r3_2, (u8) HSD_GObj_804D7849,
                                    HSD_JObjLoadJoint(attr->x5C));
            GObj_SetupGXLink(temp_r3_2, HSD_GObj_80391070, 6U, 0U);
            var_r21 = temp_r3_2->hsd_obj;
        } else {
            var_r18->prev = temp_r3_3;
            temp_r17 = &temp_r3_3->x30_collData;
            temp_r3_3->next = var_r18;
            temp_r3_3->x1D4_GObjLinkNext = arg1;
            temp_r3_3->x1D0_GObj = temp_r3_2;
            temp_r3_3->x8_vel = pos;
            temp_r3_3->pos = pos;
            temp_r3_3->flag5 = 1;
            temp_r3_3->flag6 = 1;
            temp_r3_3->flag7 = 1;
            temp_r3_3->x30_collData.cur_topn = temp_r3_3->pos;
            temp_r3_3->x30_collData.prev_topn =
                temp_r3_3->x30_collData.cur_topn;
            mpColl_80041EE4(temp_r17);
            temp_r17->x34_flags.raw = (temp_r17->x34_flags.raw & ~0x78) | 0x28;
            mpColl_8004220C(temp_r17, NULL, arg8, arg8, arg8, arg8);
            temp_r3_5 = arg0->xC4_article_data->x4_specialAttributes;
            if ((var_r31 % 2) != 0) {
                var_r5_2 = HSD_JObjLoadJoint(temp_r3_5->x54);
            } else {
                var_r5_2 = HSD_JObjLoadJoint(temp_r3_5->x58);
            }
            HSD_GObjObject_80390A70(temp_r3_2, (u8) HSD_GObj_804D7849,
                                    var_r5_2);
            GObj_SetupGXLink(temp_r3_2, it_802A24A0, 6U, 0U);
        }
        temp_r3_3->x30_collData.ecb_lock = -1;
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

Item_GObj *it_802A2BA4(Fighter_GObj *arg0, Vec3 *arg1, f32 arg2, s32 arg3) {
    Fighter *fp;
    Item *item;
    Item_GObj *gobj;
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
    spawn_item.x44_flag.bits.b0 = true;
    spawn_item.x40 = 0;

    gobj = Item_80268B18(&spawn_item);
    if (gobj != NULL) {
        item = gobj->user_data;
        item->xDD4_itemVar.linkhookshot.x14 = 0;
        if ((s32) fp->motion_id == 0x168) {
            var_r27 = 1;
        } else {
            var_r27 = 0;
        }
        if (it_802A2568(item, (HSD_GObj *) fp->parts[ftParts_8007500C(fp, FtPart_RThumbNb)].joint,
                    var_r27, fp->x34_scale.y) == NULL) {
            Item_8026A8EC(gobj);
            return NULL;
        }
        item->xDD4_itemVar.linkhookshot.x8 = (HSD_GObj *) arg0;
        item->xDD4_itemVar.linkhookshot.xC = item->xDD4_itemVar.linkhookshot.x0->x1D0_GObj->hsd_obj;
        (HSD_JObj *)fp->parts = item->xDD4_itemVar.linkhookshot.xC;
        Item_8026AB54((HSD_GObj *) gobj, (HSD_GObj *) arg0, ftParts_8007500C(fp, FtPart_RThumbNb));
        it_802A2428(arg0);
    }
    if ((enum FighterKind) fp->kind == FTKIND_CLINK) {
        it_804D6D48 = 6.0f;
    } else {
        it_804D6D48 = 6.0f;
    }
    return gobj;
}

void it_802A2ED0(Item_GObj* arg0)
{
    Item* item = GET_ITEM((HSD_GObj*) arg0);
    // item->xDD4_itemVar.linkhookshot.x10 = .L_802A2E4C;
}

static void inline it_802A2EE4_inline(MtxPtr m, ItemLink* item_link, Vec3* pos)
{
    PSMTXIdentity(m);
    m[0][3] = 0.0F;
    m[1][3] = 0.0F;
    m[2][3] = it_804D6D48;
    HSD_JObjSetupMatrix((HSD_JObj*) item_link->x1D4_GObjLinkNext);
    PSMTXConcat(((HSD_JObj*) item_link->x1D4_GObjLinkNext)->mtx, &m[0], &m[0]);
    pos->x = m[0][3];
    pos->y = m[1][3];
    pos->z = m[2][3];
}

void it_802A2EE4(Item_GObj* arg0)
{
    HSD_JObj* temp_r26_2;
    ItemLink* temp_r6;

    Item* item;
    Fighter* fp;
    itLinkHookshotAttributes* attr;
    Vec3 pos;
    Vec3 pos_2;
    ItemLink* item_link;
    ItemKind kind;
    s32 var_r0;

    Mtx m;
    f32 pad[2];

    item = arg0->user_data;
    fp = item->owner->user_data;
    attr = item->xC4_article_data->x4_specialAttributes;
    item_link = item->xDD4_itemVar.linkhookshot.x0;

#if 0
    if ((fp->motion_id == 0x168) ||
        (fp->motion_id == 0x169) ||
        (fp->motion_id == 0xD4) ||
        (fp->motion_id == 0xD6)) {
        var_r0 = 1;
    } else {
        var_r0 = 0;
    }
    if ((var_r0 == 0) && (item_link->next->flag0 == 0)) {
        it_802A2B10(arg0);
        return;
    }
#else
    if (link_fighter_compare(fp) && (item_link->next->flag0 == 0)) {
        it_802A2B10(arg0);
        return;
    }
#endif

#if 1
    it_802A2EE4_inline((MtxPtr) &m, item_link, &pos);
#else
    PSMTXIdentity(m);
    m[0][3] = 0.0F;
    m[1][3] = 0.0F;
    m[2][3] = it_804D6D48;
    HSD_JObjSetupMatrix((HSD_JObj*) item_link->x1D4_GObjLinkNext);
    PSMTXConcat(((HSD_JObj*) item_link->x1D4_GObjLinkNext)->mtx, &m[0], &m[0]);
    pos.x = m[0][3];
    pos.y = m[1][3];
    pos.z = m[2][3];
#endif
    switch (it_802A4BFC(item_link, &pos, attr, fp)) {
    case 1:
        if ((s32) fp->motion_id == 0x168) {
            ftCo_800C3CC0((Fighter_GObj*) item->owner);
            it_802A793C((HSD_GObj*) arg0);
            temp_r6 = item->xDD4_itemVar.linkhookshot.x0;
            pos_2 = temp_r6->pos;
            temp_r26_2 =
                (HSD_JObj*) item->xDD4_itemVar.linkhookshot.x0->x1D0_GObj;
            efSync_Spawn(0x41C, temp_r26_2, &pos_2, temp_r6);
            efSync_Spawn(0x3F1, temp_r26_2, &pos_2, fp->facing_dir);
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

void it_802A30FC(Item_GObj* arg0)
{
    Item* item = GET_ITEM((HSD_GObj*) arg0);
    item->xDD4_itemVar.linkhookshot.x10 = it_802A2EE4;
}

void fn_802A3110(HSD_GObj *arg0);
void fn_802A3110(HSD_GObj *arg0) {
    ItemLink* item_link;
    Item* item;
    Fighter* fp;
    itLinkHookshotAttributes* attr;
    Vec3 vec;
    Mtx m;
    f32 pad[3];

    item = arg0->user_data;
    fp = item->owner->user_data;
    attr = item->xC4_article_data->x4_specialAttributes;
    item_link = item->xDD4_itemVar.linkhookshot.x0;

    it_802A2EE4_inline((MtxPtr) &m, item_link, &vec);

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

void it_802A3240(Item_GObj* arg0)
{
    Item* item = GET_ITEM((HSD_GObj*) arg0);
    item->xDD4_itemVar.linkhookshot.x10 = fn_802A3110;
}

void it_802A3254(Item_GObj* arg0)
{
    Item* item;
    Fighter* fp;
    itLinkHookshotAttributes* attr;
    ItemLink* item_link;
    Mtx m;
    Vec3 pos;

    item = arg0->user_data;
    fp = item->owner->user_data;
    attr = item->xC4_article_data->x4_specialAttributes;
    item_link = item->xDD4_itemVar.linkhookshot.x4;

    it_802A2EE4_inline((MtxPtr) &m, item_link, &pos);
    it_802A5770(item_link, &pos, attr, fp);
    it_802A7168(item, &pos, fp->x34_scale.y);
    if (link_fighter_compare(fp) == 0) {
        it_802A77DC(arg0);
    }
}

void it_802A338C(Item_GObj* arg0)
{
    Item* item = GET_ITEM((HSD_GObj*) arg0);
    item->xDD4_itemVar.linkhookshot.x10 = it_802A3254;
}

void fn_802A33A0(Item_GObj *arg0);
void fn_802A33A0(Item_GObj *arg0) {
    ItemLink* item_link;
    Item* item;
    Fighter* fp;
    itLinkHookshotAttributes* attr;
    Vec3 vec;
    Mtx m;
    f32 pad[3];

    item = arg0->user_data;
    fp = item->owner->user_data;
    attr = item->xC4_article_data->x4_specialAttributes;
    item_link = item->xDD4_itemVar.linkhookshot.x0;

    it_802A2EE4_inline((MtxPtr) &m, item_link, &vec);

    if (it_802A5E28(item_link, &vec, attr, fp->x40) != 0) {
        if (link_fighter_compare(fp)) {
            it_802A2B10(arg0);
            return;
        }
        it_802A7688(arg0);
    }

    it_802A7168(item, &vec, fp->x34_scale.y);
}

void it_802A34EC(Item_GObj* arg0)
{
    Item* item = GET_ITEM((HSD_GObj*) arg0);
    item->xDD4_itemVar.linkhookshot.x10 = fn_802A33A0;
}

void it_802A3500(Item_GObj* arg0)
{
    Item* item;
    Fighter* fp;
    itLinkHookshotAttributes* attr;
    ItemLink* item_link;
    Mtx m;
    Vec3 pos;
    f32 pad[3];

    item = arg0->user_data;
    fp = item->owner->user_data;
    attr = item->xC4_article_data->x4_specialAttributes;

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

void it_802A361C(Item_GObj* arg0)
{
    Item* item = GET_ITEM((HSD_GObj*) arg0);
    item->xDD4_itemVar.linkhookshot.x10 = it_802A3500;
}

void it_802A3630(Item_GObj* arg0)
{
    Item* item;
    Fighter* fp;
    itLinkHookshotAttributes* attr;
    ItemLink* item_link;
    Mtx m;
    Vec3 pos;
    int var_r0;

    item = arg0->user_data;
    fp = item->owner->user_data;
    attr = item->xC4_article_data->x4_specialAttributes;
    item_link = item->xDD4_itemVar.linkhookshot.x4;

    item = arg0->user_data;
    fp = item->owner->user_data;

    it_802A2EE4_inline((MtxPtr) &m, item_link, &pos);

    item_link = item->xDD4_itemVar.linkhookshot.x0;

    if (mpLib_800524DC(0, 0, 0, 0, -1, -1, pos.x, pos.y, item_link->pos.x,
                       item_link->pos.y) != 0)
    {
        var_r0 = 1;
    } else if (mpLib_800524DC(0, 0, 0, 0, -1, -1, fp->cur_pos.x, fp->cur_pos.y,
                              item_link->pos.x, item_link->pos.y) != 0)
    {
        var_r0 = 1;
    } else {
        var_r0 = 0;
    }
    if (var_r0 != 0) {
        ftCo_80090780((Fighter_GObj*) item->owner);
        it_802A2B10(arg0);
        return;
    }

    if (it_802A5AE0(item->xDD4_itemVar.linkhookshot.x0, &pos, attr) != 0) {
        it_802A7A04((HSD_GObj*) arg0);
        it_802A7168(item, &pos, fp->x34_scale.y);
        return;
    }
    it_802A7384(item, &pos, fp->x34_scale.y);
    if (fp->ground_or_air != 1) {
        it_802A77DC(arg0);
        return;
    }
    // if (fp->unk668 & 0x100) {
    //     it_802A79A0((HSD_GObj *) arg0);
    // }
}

void it_802A3814(Item_GObj* arg0)
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

void it_802A39E8(Item_GObj* arg0)
{
    Item* item = GET_ITEM((HSD_GObj*) arg0);
    item->xDD4_itemVar.linkhookshot.x10 = it_802A3828;
}

void it_802A39FC(Item_GObj* arg0)
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

    item = arg0->user_data;
    attr = item->xC4_article_data->x4_specialAttributes;
    fp = item->owner->user_data;
    item_link = item->xDD4_itemVar.linkhookshot.x4;

    it_802A2EE4_inline((MtxPtr) &m, item_link, &pos);

    item_link = item->xDD4_itemVar.linkhookshot.x0;

    if (mpLib_800524DC(0, 0, 0, 0, -1, -1, pos.x, pos.y, item_link->pos.x,
                       item_link->pos.y) != 0)
    {
        var_r0 = 1;
    } else if (mpLib_800524DC(0, 0, 0, 0, -1, -1, fp->cur_pos.x, fp->cur_pos.y,
                              item_link->pos.x, item_link->pos.y) != 0)
    {
        var_r0 = 1;
    } else {
        var_r0 = 0;
    }
    if (var_r0 != 0) {
        ftCo_80090780((Fighter_GObj*) item->owner);
        it_802A2B10(arg0);
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
        it_802A77DC(arg0);
        return;
    }
    if (fp->input.x668 & 0x100) {
        it_802A79A0((HSD_GObj*) arg0);
        return;
    }
    fp->mv.lk.specialn.x0.y -= 1.0F;
    if (fp->mv.lk.specialn.x0.y <= 0.0f) {
        ftCo_80090780((Fighter_GObj*) item->owner);
        it_802A2B10(arg0);
    }
}

void it_802A3C84(Item_GObj* arg0)
{
    Item* item = GET_ITEM((HSD_GObj*) arg0);
    item->xDD4_itemVar.linkhookshot.x10 = it_802A39FC;
}

static inline float lk_sqrtf(float x)
{
    double _half = .5;
    double _three = 3.0;
    float y;
    if (x > 0.0f) {
        double guess = __frsqrte((double) x); // returns an approximation to
        guess = _half * guess *
                (_three - guess * guess * x); // now have 12 sig bits
        guess = _half * guess *
                (_three - guess * guess * x); // now have 24 sig bits
        guess = _half * guess *
                (_three - guess * guess * x); // now have 32 sig bits
        y = (float) (x * guess);
        return y;
    }
    return x;
}

static inline Vec3* lk_diff(Vec3* a, Vec3* b, Vec3* result)
{
    result->x = a->x - b->x;
    result->y = a->y - b->y;
    result->z = a->z - b->z;
    return result;
}

inline static float lk_len(Vec3* vec)
{
    return vec->x * vec->x + vec->y * vec->y + vec->z * vec->z;
}

inline static double lk_inv(Vec3* vec)
{
    f64 len;
    f32 inv;
    len = sqrtf(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
    if (len == 0.0F) {
        inv = 0.0F;
    } else {
        inv = 1.0F / len;
    }
    vec->x *= inv;
    vec->y *= inv;
    vec->z *= inv;
}

static inline my_sqrtf(float x)
{
    static const double _half = .5;
    static const double _three = 3.0;

    u8 _[4] = { 0 };

    volatile float y;
    if (x > 0) {
        double guess = __frsqrte((double) x); // returns an approximation to
        guess = _half * guess *
                (_three - guess * guess * x); // now have 12 sig bits
        guess = _half * guess *
                (_three - guess * guess * x); // now have 24 sig bits
        guess = _half * guess *
                (_three - guess * guess * x); // now have 32 sig bits
        y = (float) (x * guess);
        return y;
    }
    return x;
}

static inline float my_lbVector_Len(Vec3* vec)
{
    return my_sqrtf(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
}

static inline Vec3* lbVector_Diff_a(Vec3* a, Vec3* b, Vec3* result)
{
    result->x = a->x - b->x;
    result->y = a->y - b->y;
    result->z = a->z - b->z;
    return result;
}

static inline float lbVector_Len_a(Vec3* vec)
{
    return sqrtf(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
}


static inline float tes(Vec3* arg0, Vec3* arg1, Vec3* arg2)
{
    f32 inv;
    f32 len;
    // lbVector_Diff_a(arg0, arg1, arg2);
    arg2->x = arg0->x - arg1->x;
    arg2->y = arg0->y - arg1->y;
    arg2->z = arg0->z - arg1->z;

    len = sqrtf(arg2->x * arg2->x + arg2->y * arg2->y + arg2->z * arg2->z);
    if (len == (f64)0.0F) {
        inv = (f64)0.0F;
    } else {
        inv = (f64)1.0F / len;
    }
    arg2->x *= inv;
    arg2->y *= inv;
    arg2->z *= inv;
    return len;
}

float it_802A3C98(Vec3* arg0, Vec3* arg1, Vec3* arg2)
{
#if 0
    return tes(arg0, arg1, arg2);
#else
    f32 inv;
    f32 len;
    // lbVector_Diff_a(arg0, arg1, arg2);
    arg2->x = arg0->x - arg1->x;
    arg2->y = arg0->y - arg1->y;
    arg2->z = arg0->z - arg1->z;

    len = sqrtf(arg2->x * arg2->x + arg2->y * arg2->y + arg2->z * arg2->z);
    if (len == (f64)0.0F) {
        inv = (f64)0.0F;
    } else {
        inv = (f64)1.0F / len;
    }
    arg2->x *= inv;
    arg2->y *= inv;
    arg2->z *= inv;
    return len;
#endif
}

s32 it_802A3D90(ItemLink* item_link)
{
    CollData* coll;

    coll = &item_link->x30_collData;
    coll->prev_topn = coll->cur_topn;
    coll->cur_topn = item_link->pos;
    if (mpColl_800471F8(coll)) {
        item_link->flag1 = 1;
    } else {
        item_link->flag1 = 0;
    }
    item_link->pos = coll->cur_topn;
    return coll->env_flags & 0x18FFF;
}
s32 it_802A3E50(ItemLink* item_link, enum FighterKind arg1, f32 arg8)
{
    ItemLink* item_link_next;
    ItemLink* item_link_next_2;
    f32 temp_f2;

    CollData* coll;
    mp_UnkStruct0* mp_island;
    u32 flag;
    s32 flag_2;
    s32 var_r29;

    coll = &item_link->x30_collData;
    item_link_next = item_link->next;
    flag = item_link->flag0;

    if ((item_link_next != NULL) && flag) {
        var_r29 = 1;
    } else {
        var_r29 = 0;
    }
    if (var_r29 != 0) {
        coll->prev_topn = item_link_next->x30_collData.cur_topn;
    } else {
        coll->prev_topn = coll->cur_topn;
    }
    coll->cur_topn = item_link->pos;

    if (var_r29 != 0) {
        item_link_next_2 = item_link->next;
        if (item_link_next_2->flag1 && !item_link->flag1) {
            mp_island =
                mpIsland_8005AB54(item_link_next_2->x30_collData.floor.index);
            if (mp_island != NULL) {
                if ((mp_island->x14 < item_link->pos.x) &&
                    (mp_island->x18 > item_link->pos.y))
                {
                    item_link->pos.x = item_link->pos.x;
                    item_link->pos.y = mp_island->x18;
                    return coll->env_flags & 0x18FFF;
                }
                if ((mp_island->x8 > item_link->pos.x) &&
                    (mp_island->xC > item_link->pos.y))
                {
                    item_link->pos.x = item_link->pos.x;
                    item_link->pos.y = mp_island->x18;
                    return coll->env_flags & 0x18FFF;
                }
            }
        }
    }
    if (item_link->flag1) {
        item_link->flag1 = mpColl_8004B108(coll);
    } else {
        item_link->flag1 = mpColl_800471F8(coll);
    }
    if (coll->env_flags & 0x18000) {
        coll->cur_topn.x = item_link->pos.x;
    } else if ((coll->env_flags & 0xFFF) && (var_r29 != 0) &&
               (item_link->prev != NULL) &&
               (item_link->next->pos.y < item_link->pos.y))
    {
        coll->cur_topn.y += arg8;
    }
    flag_2 = item_link->flag0;
    if (((flag_2 >> 6U) & 1) && (flag == 0) && !((flag_2 >> 5U) & 1)) {
        if (arg1 == FTKIND_CLINK) {
            lbAudioAx_800237A8(0x111BF, 0x7FU, 0x40U);
        } else {
            lbAudioAx_800237A8(0x2714F, 0x7FU, 0x40U);
        }
        item_link->flag2 = 1;
    }
    item_link->pos = coll->cur_topn;
    return coll->env_flags & 0x18FFF;
}

static inline it_802A40D0_test()
{
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
        coll->prev_topn = item_link_next->x30_collData.cur_topn;
    } else {
        coll->prev_topn = coll->cur_topn;
    }
    coll->cur_topn = item_link->pos;

    if (var_r29 != 0) {
        item_link_next_2 = item_link->next;
        if (item_link_next_2->flag1 && !item_link->flag1) {
            mp_island =
                mpIsland_8005AB54(item_link_next_2->x30_collData.floor.index);
            if (mp_island != NULL) {
                if ((mp_island->x14 < item_link->pos.x) &&
                    (mp_island->x18 > item_link->pos.y))
                {
                    item_link->pos.x = item_link->pos.x;
                    item_link->pos.y = mp_island->x18;
                    return coll->env_flags & 0x18FFF;
                }
                if ((mp_island->x8 > item_link->pos.x) &&
                    (mp_island->xC > item_link->pos.y))
                {
                    item_link->pos.x = item_link->pos.x;
                    item_link->pos.y = mp_island->x18;
                    return coll->env_flags & 0x18FFF;
                }
            }
        }
    }
    if (item_link->flag1) {
        item_link->flag1 = mpColl_8004B108(coll);
    } else {
        item_link->flag1 = mpColl_800471F8(coll);
    }
    if (coll->env_flags & 0x18000) {
        coll->cur_topn.x = item_link->pos.x;
    } else if ((coll->env_flags & 0xFFF) && (var_r29 != 0) &&
               (item_link->prev != NULL) &&
               (item_link->next->pos.y < item_link->pos.y))
    {
        coll->cur_topn.y += arg8;
    }
    flag_2 = item_link->flag0;
    item_link->pos = coll->cur_topn;
    return coll->env_flags & 0x18FFF;
}

s32 it_802A42F4(ItemLink* item_link, f32 arg8)
{
    CollData* coll;

    coll = &item_link->x30_collData;
    item_link->x30_collData.prev_topn = item_link->x30_collData.cur_topn;
    item_link->x30_collData.prev_topn.y = arg8;
    item_link->x30_collData.cur_topn = item_link->pos;
    mpColl_800471F8(coll);
    if (mpColl_800471F8(coll)) {
        item_link->flag1 = 1;
    } else {
        item_link->flag1 = 0;
    }
    item_link->pos = coll->cur_topn;
    return coll->env_flags & 0x18FFF;
}

void it_802A43B8(ItemLink* item_link)
{
    item_link->x30_collData.cur_topn = item_link->pos;
    item_link->x30_collData.prev_topn = item_link->x30_collData.cur_topn;
}

void it_802A43EC(ItemLink* item_link)
{
    item_link->x30_collData.prev_topn = item_link->x30_collData.cur_topn;
    item_link->x30_collData.cur_topn = item_link->pos;
}

void it_802A4420(ItemLink* item_link)
{
    item_link->pos.x += item_link->x8_vel.x;
    item_link->pos.y += item_link->x8_vel.y;
    item_link->pos.z += item_link->x8_vel.z;
}

void it_802A4454(ItemLink* item_link)
{
    Vec3 sp10;
    f32 pad[2];

    if (mpLib_80054ED8(item_link->x30_collData.ecb_lock) != 0) {
        mpLib_800567C0(item_link->x30_collData.ecb_lock, &item_link->pos,
                       &sp10);
        item_link->pos.x += sp10.x;
        item_link->pos.y += sp10.y;
        item_link->pos.z += sp10.z;
    }
}

void it_802A44CC(ItemLink* link_0, Vec3* arg1,
                 itLinkHookshotAttributes* arg2, f32 arg8)
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

void it_802A4758(ItemLink* link_0, Vec3* arg1, itLinkHookshotAttributes* arg2, f32 arg8)
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
        link_1->x8_vel.y -= arg2->x3C;
        // it_802A4420(link_1);
        link_1->pos.x += link_1->x8_vel.x;
        link_1->pos.y += link_1->x8_vel.y;
        link_1->pos.z += link_1->x8_vel.z;

        link_1->x30_collData.prev_topn = link_1->x30_collData.cur_topn;
        link_1->x30_collData.cur_topn = link_1->pos;

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

void it_802A49B0(ItemLink* link_0, Vec3* arg1,
                 itLinkHookshotAttributes* arg2, f32 arg8)
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


s32 it_802A4BFC(ItemLink* item_link, Vec3* arg1,
                itLinkHookshotAttributes* attr, Fighter* fp)
{
    s32 flag;
    ItemLink* link_1;
    ItemLink* link_0;
    f64 len;
    Vec3 vec;

    ftLk_DatAttrs* lk_attr;
    Mtx m;
    Vec3 pos;

    link_0 = item_link;
    lk_attr = fp->ft_data->ext_attr;
    switch (fp->motion_id) {
    case 0xD4:
        if (fp->mv.ca.specials.grav == lk_attr->x88) {
            it_802A2EE4_inline((MtxPtr) &m, link_0, &pos);
            link_0->pos = pos;
            link_0->x30_collData.cur_topn = link_0->pos;
            link_0->x30_collData.prev_topn = link_0->x30_collData.cur_topn;
            link_0->flag1 = 1;
        }
        break;
    case 0xD6:
        if (fp->mv.ca.specials.grav == lk_attr->x98) {
            it_802A2EE4_inline((MtxPtr) &m, link_0, &pos);
            link_0->pos = pos;
            link_0->x30_collData.cur_topn = link_0->pos;
            link_0->x30_collData.prev_topn = link_0->x30_collData.cur_topn;
            link_0->flag1 = 1;
        }
        break;
    case 0x168:
        if (fp->mv.ca.specials.grav == lk_attr->xA8) {
            it_802A2EE4_inline((MtxPtr) &m, link_0, &pos);
            link_0->pos = pos;
            link_0->x30_collData.cur_topn = link_0->pos;
            link_0->x30_collData.prev_topn = link_0->x30_collData.cur_topn;
            link_0->flag1 = 1;
        }
        break;
    }

    link_1 = link_0->next;
    link_0->pos.x += link_0->x8_vel.x;
    link_0->pos.y += link_0->x8_vel.y;
    link_0->pos.z += link_0->x8_vel.z;
    flag = it_802A40D0(link_0, attr->x30);
    if (flag & 0x3F) {
        link_0->x30_collData.ecb_lock = link_0->x30_collData.right_wall.index;
    } else if (flag & 0xFC0) {
        link_0->x30_collData.ecb_lock = link_0->x30_collData.left_wall.index;
    }

    for (;;) {
        if (link_1 == NULL) {
            it_802A44CC(item_link, arg1, attr, attr->x30);
            return 2;
        }
        if (link_1->flag0) {
            len = it_802A3C98(&link_1->pos, &link_0->pos, &vec);
            if (len > attr->x30) {
                link_1->pos.x = (vec.x * attr->x30) + item_link->pos.x;
                link_1->pos.y = (vec.y * attr->x30) + item_link->pos.y;
                link_1->pos.z = (vec.z * attr->x30) + item_link->pos.z;
            }
            link_1->x30_collData.prev_topn = link_1->x30_collData.cur_topn;
            link_1->x30_collData.cur_topn = link_1->pos;
        } else {
            len = it_802A3C98(arg1, &link_0->pos, &vec);
            if (len > attr->x30) {
                link_1->pos.x = (vec.x * attr->x30) + link_0->pos.x;
                link_1->pos.y = (vec.y * attr->x30) + link_0->pos.y;
                link_1->pos.z = (vec.z * attr->x30) + link_0->pos.z;
                link_1->flag0 = 1;
                link_1->x30_collData.cur_topn = link_1->pos;
                link_1->x30_collData.prev_topn = link_1->x30_collData.cur_topn;
            } else {
                continue;
            }
        }
        link_0 = link_1;
        link_1 = link_1->next;
    }
    link_1->pos = *arg1;
    link_1->flag0 = 1;
    link_1->x30_collData.cur_topn = link_1->pos;
    link_1->x30_collData.prev_topn = link_1->x30_collData.cur_topn;
    if (flag & 0xFFF) {
        return 1;
    }
    if (flag & 0x6000) {
        return 3;
    }
    if (flag & 0x18000) {
        return 4;
    }
    return 0;
}

s32 it_802A5320(ItemLink *link_0, Vec3 *arg1, itLinkHookshotAttributes *attr, Fighter *fp) {
    s32 flag;
    ItemLink* link_1;
    f64 len;
    Vec3 vec;

    ftLk_DatAttrs* lk_attr;
    Mtx m;
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
    temp_r30 = it_802A40D0(link_0, attr->x30) & 0xFFF;
    var_r29 = 0;

    for (;;) {
        if (link_1 == NULL) {
            it_802A44CC(link_0, arg1, attr, attr->x30);
            return 2;
        }
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
            link_1->x30_collData.prev_topn = link_1->x30_collData.cur_topn;
            link_1->x30_collData.cur_topn = link_1->pos;
        } else {
            len = it_802A3C98(arg1, &link_0->pos, &vec);
            if (len > attr->x30) {
                link_1->pos.x = (vec.x * attr->x30) + link_0->pos.x;
                link_1->pos.y = (vec.y * attr->x30) + link_0->pos.y;
                link_1->pos.z = (vec.z * attr->x30) + link_0->pos.z;
                link_1->flag0 = 1;
                link_1->x30_collData.cur_topn = link_1->pos;
                link_1->x30_collData.prev_topn = link_1->x30_collData.cur_topn;
            } else {
                continue;
            }
            break;
        }
        link_0 = link_1;
        link_1 = link_1->next;
        var_r29 += 1;
    }

    link_1->pos = *arg1;
    link_1->flag0 = 1;
    link_1->x30_collData.cur_topn = link_1->pos;
    link_1->x30_collData.prev_topn = link_1->x30_collData.cur_topn;
    if (temp_r30 != 0) {
        return 1;
    }
    return 0;
}

void it_802A5770(ItemLink *link_0, Vec3 *arg1, itLinkHookshotAttributes *arg2, Fighter *arg3) {
    ItemLink* link_1;
    f32 inv;
    f64 len;
    f32 test[2];
    f32 var_r29;
    Vec3 vec;
    link_1 = link_0->prev;

    while (link_1 != NULL && link_0->flag0) {
        link_0 = link_1->prev;
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

        if (var_r29 == (s32) ((s32) arg2->x2C / 2)) {
            it_802A3E50(link_1, arg3->kind, arg2->x30);
        } else {
            it_802A40D0(link_1, arg2->x30);
        }

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

s32 it_802A5AE0(ItemLink *link_0, Vec3 *arg1, itLinkHookshotAttributes *arg2) {
    ItemLink* link_1;
    f32 len;
    f32 test[2];
    Vec3 vec;

    if (mpLib_80054ED8(link_0->x30_collData.ecb_lock) != 0) {
        mpLib_800567C0(link_0->x30_collData.ecb_lock, &link_0->pos, &vec);
        link_0->pos.x += vec.x;
        link_0->pos.y += vec.y;
        link_0->pos.z += vec.z;
    }
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
                link_1->x30_collData.cur_topn = link_1->pos;
                link_1->x30_collData.prev_topn = link_1->x30_collData.cur_topn;
            } else {
                return 0;
            }
        }
        link_0 = link_1;
        link_1 = link_1->next;
    }
    return 1;
}

void it_802A6944(Item *item, f32 scl) {
    HSD_JObj *jobj;
    ItemLink *item_link;
    Mtx m;
    f32 pad[4];

    item_link = item->xDD4_itemVar.linkhookshot.x0;
    jobj = item_link->x1D0_GObj->hsd_obj;

    HSD_JObjSetupMatrix((HSD_JObj *)item_link->x1D4_GObjLinkNext);
    PSMTXIdentity(m);
    m[0][3] = 0.0F;
    m[1][3] = 0.0F;
    m[2][3] = it_804D6D48;
    PSMTXConcat(((HSD_JObj*) item_link->x1D4_GObjLinkNext)->mtx, &m[0], &m[0]);
    HSD_JObjCopyMtx(jobj, m);
    jobj->flags |= 0x03800000;
    HSD_JObjSetupMatrix(jobj);
}

#if 1
s32 it_802A6A78(ItemLink *link_0, Vec3 *arg1, itLinkHookshotAttributes *arg2, Fighter *arg3) {

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
            link_1->x30_collData.prev_topn = link_1->x30_collData.cur_topn;
            link_1->x30_collData.cur_topn = link_1->pos;
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
                link_1->x30_collData.prev_topn = link_1->x30_collData.cur_topn;
                link_1->x30_collData.cur_topn = link_1->pos;
            }
        }
        link_0 = link_1;
        link_1 = link_1->next;
    }
    it_802A49B0(link_0, arg1, arg2, arg2->x30);
    return 0;
}
#endif

void it_802A6DC8(HSD_JObj *arg0, Vec3 *arg1, Vec3 *arg2) {
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
    PSMTXIdentity((MtxPtr)&m);

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


void it_802A6F80(HSD_JObj *arg0, Vec3 *arg1, Vec3 *arg2, f32 arg3) {
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
    PSMTXIdentity((MtxPtr)&m1);
    PSMTXIdentity((MtxPtr)&m0);

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

    PSMTXConcat((MtxPtr)&m0, (MtxPtr)&m1, (MtxPtr)&m0);
    HSD_JObjCopyMtx(arg0, m0);
    arg0->flags |= 0x03800000;
    HSD_JObjSetMtxDirty(arg0);
}

void it_802A7168(Item *arg0, Vec3 *arg1, f32 arg8) {
    HSD_JObj *jobj;
    Fighter *fp;
    ItemLink *item_link;
    Vec3 vec;
    Vec3 vec_2;
    Vec3 vec_3;
    Vec3 vec_4;
    Vec3 vec_5;
    ItemLink *item_link_prev;
    ItemLink *item_link_prev_2;
    f32 pad[2];

    fp = arg0->owner->user_data;
    if (fp->kind == 6) {
        item_link = arg0->xDD4_itemVar.linkhookshot.x4;
    } else {
        item_link = arg0->xDD4_itemVar.linkhookshot.x4;
    }

    while (!item_link->flag0) {
        item_link = item_link->prev;
    }

    while (item_link != NULL) {
        item_link_prev = item_link->prev;
        if (item_link_prev != NULL) {
            if (item_link_prev->flag0) {
                vec = item_link_prev->pos;
            } else {
                vec = *arg1;
            }
        } else {
            vec = *arg1;
        }
        item_link_prev_2 = item_link->prev;

        if (item_link_prev_2 != NULL) {
            vec_2 = item_link_prev_2->pos;
        } else {
            vec_2 = item_link->pos;
        }
        jobj = item_link->x1D0_GObj->hsd_obj;
        vec_4 = item_link->pos;
        HSD_JObjSetTranslate(jobj, &vec_4);
        vec_5.x = vec_2.x - vec.x;
        vec_5.y = vec_2.y - vec.y;
        vec_5.z = vec_2.z - vec.z;
        it_802A6F80(jobj, &vec_4, &vec_5, arg8);
        item_link = item_link->prev;
    }
}

void it_802A7384(Item *arg0, Vec3 *arg1, f32 arg8) {
    ItemLink* item_link;
    Fighter *fp;
    HSD_JObj *jobj;
    Vec3 vec;
    Vec3 vec2;

    item_link = arg0->xDD4_itemVar.linkhookshot.x4;
    fp = arg0->owner->user_data;

    it_802A7168(arg0, arg1, arg8);

    jobj = item_link->x1D0_GObj->hsd_obj;
    vec = item_link->pos;
    HSD_JObjSetTranslate(jobj, &vec);

    if (fp->facing_dir > 0.0F) {
        vec2.x = 1.0F;
        vec2.y = 0.0F;
        vec2.z = 0.0F;
    } else {
        vec2.x = -1.0F;
        vec2.y = 0.0F;
        vec2.z = 0.0F;
    }
    it_802A6F80(jobj, &vec, &vec2, arg8);
}

static inline it_802A7688_inline(HSD_GObj *arg0)
{
    Item* item;
    Fighter *fp;
    HSD_JObj *jobj;
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

void it_802A7688(Item_GObj *arg0) {
    f32 pad[7];
    Item_80268E5C((HSD_GObj *) arg0, 0, ITEM_ANIM_UPDATE);
    it_802A7688_inline(arg0);
}

void it_802A76EC(HSD_GObj *arg0) {
    Item* item;
    f32 pad[4];
    item = GET_ITEM(arg0);
    Item_80268E5C(arg0, 3, ITEM_ANIM_UPDATE);
    ftColl_8007AFF8(item->xDD4_itemVar.linkhookshot.x8);
    it_802A7688_inline(arg0);
}

void it_802A7764(HSD_GObj *arg0) {
    Item* item;
    f32 pad[4];
    item = GET_ITEM(arg0);
    Item_80268E5C(arg0, 2, ITEM_ANIM_UPDATE);
    ftColl_8007AFF8(item->xDD4_itemVar.linkhookshot.x8);
    it_802A7688_inline(arg0);
}

void it_802A77DC(Item_GObj *arg0) {
    Item* item;
    f32 pad[4];
    item = GET_ITEM((HSD_GObj *)arg0);
    Item_80268E5C((HSD_GObj *)arg0, 4, ITEM_ANIM_UPDATE);
    it_802A7688_inline((HSD_GObj *)arg0);
}

void it_802A7840(HSD_GObj *arg0) {
    Item* item;
    f32 pad[4];
    item = GET_ITEM(arg0);
    Item_80268E5C(arg0, 5, ITEM_ANIM_UPDATE);
    ftColl_8007AFF8(item->xDD4_itemVar.linkhookshot.x8);
    it_802A7688_inline(arg0);
}

void it_802A78B8(HSD_GObj *arg0, Vec3 *arg1, f32 arg2) {
    ItemLink *item_link;
    Item* item;
    f32 pad[2];

    item = GET_ITEM(arg0);
    item_link = item->xDD4_itemVar.linkhookshot.x0;
    item_link->x8_vel = *arg1;
    Item_80268E5C(arg0, 1, ITEM_ANIM_UPDATE);
    it_802A7688_inline(arg0);
}

void it_802A793C(HSD_GObj *arg0) {
    f32 pad[6];
    Item_80268E5C(arg0, 6, ITEM_ANIM_UPDATE);
    it_802A7688_inline(arg0);
}

void it_802A79A0(HSD_GObj *arg0) {
    f32 pad[6];
    Item_80268E5C(arg0, 7, ITEM_ANIM_UPDATE);
    it_802A7688_inline(arg0);
}

void it_802A7A04(HSD_GObj *arg0) {
    Item* item;
    Fighter *fp;
    ftLk_DatAttrs* lk_attr;
    f32 pad[6];

    item = GET_ITEM(arg0);
    fp = item->owner->user_data;
    lk_attr = fp->dat_attrs;

    Item_80268E5C(arg0, 8, ITEM_ANIM_UPDATE);
    it_802A7688_inline(arg0);
    // TODO: should this be its own struct?
    fp->mv.lk.specialn.x0.y = lk_attr->xB8;
}

void it_802A7AAC(HSD_GObj *arg0) {
    Fighter *fp;

    fp = arg0->user_data;
    if (fp->fv.lk.xC != NULL) {
        it_802A2B10(fp->fv.lk.xC);
        return;
    }
    fp->accessory2_cb = NULL;
    fp->death1_cb = NULL;
    fp->accessory3_cb = NULL;
}

void it_802A7AF0(HSD_GObj *arg0) {
    Item *item;
    Fighter *fp;

    fp = arg0->user_data;
    if (fp->fv.lk.xC != NULL) {
        item = GET_ITEM((HSD_GObj*) fp->fv.lk.xC);
        if (item->xDD4_itemVar.linkhookshot.x10) {
            item->xDD4_itemVar.linkhookshot.x10(fp->fv.lk.xC);
        }
    }
}

void it_802A7B34(HSD_GObj *arg0) {
    Fighter *fp;
    Item *item;
    ItemLink *item_link;
    Mtx m;
    itLinkHookshotAttributes* attr;
    Vec3 vec;
    f32 pad[4];

    fp = arg0->user_data;
    if (fp->fv.lk.xC != NULL) {
        item = GET_ITEM(fp->fv.lk.xC);
        item_link = item->xDD4_itemVar.linkhookshot.x0;
        attr = item->xC4_article_data->x4_specialAttributes;

        it_802A2EE4_inline((MtxPtr)&m, item_link, &vec);

        if (it_802A6A78(item_link, &vec, attr, fp) != 0) {
            it_802A6944(item, fp->x34_scale.y);
        } else {
            it_802A7168(item,  &vec, fp->x34_scale.y);
        }
    }
}

void it_802A7D40(Item_GObj *arg0, Item_GObj *arg1) {
    Item* item = GET_ITEM((HSD_GObj*) arg0);
    it_8026B894(arg0, (HSD_GObj *) arg1);
    if ((HSD_GObj *) item->xDD4_itemVar.linkhookshot.x8 == arg1) {
        item->xDD4_itemVar.linkhookshot.x8 = NULL;
    }
}
