#include "itseakchain.h"

#include "it/items/itseakchain.static.h"

#include "platform.h"

#include "baselib/forward.h"

#include "baselib/gobjplink.h"
#include "baselib/jobj.h"
#include "dolphin/mtx.h"
#include "ft/ftcoll.h"
#include "ft/ftlib.h"
#include "ftSeak/ftSk_SpecialS.h"

#include "it/forward.h"

#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/itCharItems.h"
#include "it/item.h"
#include "it/items/itlinkhookshot.h"
#include "lb/lbvector.h"

void it_802BAEEC(Item_GObj* gobj)
{
    it_8026B724(gobj);
}

void it_802BAF0C(Item_GObj* gobj)
{
    it_8026B73C(gobj);
}

/// #it_802BAF2C

static void inlineA0(Item_GObj* gobj)
{
    if (gobj != NULL) {
        Item* ip = GET_ITEM(gobj);
        if (ip->owner != NULL) {
            ftSk_SpecialS_80110E4C(ip->owner);
        }
        ip->owner = NULL;
        ip->xDD4_itemVar.seakchain.x8 = NULL;
        {
            ItemLink* cur;
            for (cur = ip->xDD4_itemVar.seakchain.x0; cur != NULL;) {
                HSD_GObj* cur_gobj = cur->gobj;
                cur = cur->next;
                HSD_GObjPLink_80390228(cur_gobj);
            }
        }
    }
}

void it_802BB20C(Item_GObj* gobj)
{
    if (GET_ITEM(gobj) != NULL) {
        inlineA0(gobj);
        Item_8026A8EC(gobj);
    }
}

/// #it_802BB290

void fn_802BB428(Item_GObj* gobj)
{
    it_802BCA30(GET_ITEM(gobj));
}

void fn_802BB44C(Item_GObj* gobj)
{
    Vec3 vec;
    Mtx mtx;
    Item* temp_r30;
    itSeakChain_Attrs* sa;
    ItemLink* link;

    temp_r30 = GET_ITEM(gobj);
    link = temp_r30->xDD4_itemVar.seakchain.x0;
    sa = temp_r30->xC4_article_data->x4_specialAttributes;
    PSMTXIdentity(mtx);
    mtx[0][3] = 0.0f;
    mtx[1][3] = 0.0f;
    mtx[2][3] = 0.1f;
    HSD_JObjSetupMatrix(link->jobj);
    PSMTXConcat(link->jobj->mtx, mtx, mtx);
    vec.x = mtx[0][3];
    vec.y = mtx[1][3];
    vec.z = mtx[2][3];
    switch (it_802BBD64(link, &vec, sa)) {
    case 1:
        link->vel.x *= -sa->x58;
        it_802BCF2C(gobj);
        break;
    case 2:
        it_802BCED4(gobj);
        break;
    }
    it_802BCB88(temp_r30, &vec);
}

void fn_802BB574(Item_GObj* gobj)
{
    Vec3 vec;
    Item* ip = GET_ITEM(gobj);
    itSeakChain_Attrs* sa = ip->xC4_article_data->x4_specialAttributes;
    Mtx mtx;
    ItemLink* link = ip->xDD4_itemVar.seakchain.x0;

    PSMTXIdentity(mtx);
    mtx[0][3] = 0.0f;
    mtx[1][3] = 0.0f;
    mtx[2][3] = 0.1f;
    HSD_JObjSetupMatrix(link->jobj);
    PSMTXConcat(link->jobj->mtx, mtx, mtx);
    vec.x = mtx[0][3];
    vec.y = mtx[1][3];
    vec.z = mtx[2][3];
    switch (it_802BBED0(link, &vec, sa)) {
    case 1:
        link->vel.x *= -sa->x58;
        break;
    case 2:
        it_802BCED4(gobj);
        break;
    }
    it_802BCB88(ip, &vec);
}

/// @todo Shared inline with #fn_802BB784 #fn_802BB574, #fn_802BB44C
void fn_802BB694(Item_GObj* gobj)
{
    Vec3 vec;
    Mtx mtx;
    Item* ip = GET_ITEM(gobj);
    ItemLink* link = ip->xDD4_itemVar.seakchain.x4;
    PSMTXIdentity(mtx);
    mtx[0][3] = 0.0f;
    mtx[1][3] = 0.0f;
    mtx[2][3] = 0.1f;
    HSD_JObjSetupMatrix(link->jobj);
    PSMTXConcat(link->jobj->mtx, mtx, mtx);
    vec.x = mtx[0][3];
    vec.y = mtx[1][3];
    vec.z = mtx[2][3];
    it_802BC080(link, &vec, ip);
    it_802BCB88(ip, &vec);
}

void fn_802BB784(Item_GObj* gobj)
{
    Mtx mtx;
    Item* ip;
    itSeakChain_Attrs* sa;
    ItemLink* link;

    ip = GET_ITEM(gobj);
    link = ip->xDD4_itemVar.seakchain.x4;
    sa = ip->xC4_article_data->x4_specialAttributes;
    PSMTXIdentity(mtx);
    mtx[0][0] = 0.0f;
    mtx[1][0] = 0.0f;
    mtx[2][0] = 0.1f;
    HSD_JObjSetupMatrix(link->jobj);
    PSMTXConcat(link->jobj->mtx, mtx, mtx);
    {
        Vec3 vec;
        vec.x = mtx[0][0];
        vec.y = mtx[1][0];
        vec.z = mtx[2][0];
        if (it_802BC94C(link, &vec, mtx, sa->x54)) {
            it_2725_Logic54_PickedUp(gobj);
        }
        it_802BCB88(ip, &vec);
    }
}

static bool notInSpecialS(Fighter_GObj* gobj)
{
    if (gobj != NULL) {
        enum_t msid = ftLib_80086C0C(gobj);
        if ((msid >= ftSk_MS_SpecialSStart) &&
            (msid <= ftSk_MS_SpecialAirSEnd))
        {
            return false;
        }
        return true;
    }
    return true;
}

bool itSeakchain_UnkMotion4_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(2 * 4);
    if (notInSpecialS(ip->owner)) {
        inlineA0(gobj);
        return true;
    }
    return false;
}

/// #it_802BB938

s32 it_802BBAEC(ItemLink* link, s32 arg1, f32 arg2)
{
    return it_802BB938(link, arg1, arg2);
}

int it_802BBB0C(ItemLink* link, Vec3* offset, Mtx mtx, float scale)
{
    Vec3 pos;
    ItemLink *cur = link->prev, *prev = link;
    int ret = it_802A3C98(&prev->pos, offset, &pos);
    prev->pos.x = pos.x * scale + offset->x;
    prev->pos.y = pos.y * scale + offset->y;
    prev->pos.z = pos.z * scale + offset->z;
    for (; cur != NULL; prev = cur, cur = cur->prev) {
        cur->vel.y -= mtx[1][2];
        it_802A4420(cur);
        it_802A43EC(cur);
        it_802BB938(cur, 0, mtx[0][1]);
        {
            float temp_ret = it_802A3C98(&cur->pos, &prev->pos, &pos);
            ret = temp_ret;
            if (temp_ret > mtx[0][1]) {
                cur->pos.x = pos.x * mtx[0][1] + prev->pos.x;
                cur->pos.y = pos.y * mtx[0][1] + prev->pos.y;
                cur->pos.z = pos.z * mtx[0][1] + prev->pos.z;
            }
        }
    }
    return ret;
}

int it_802BBC38(ItemLink* link, Vec3* offset, Mtx arg2, f32 scale)
{
    Vec3 origin;
    ItemLink* cur = link->prev;
    ItemLink* prev = link;
    int ret = it_802A3C98(&prev->pos, offset, &origin);
    prev->pos.x = (origin.x * scale) + offset->x;
    prev->pos.y = (origin.y * scale) + offset->y;
    prev->pos.z = (origin.z * scale) + offset->z;
    for (; cur != NULL; prev = cur, cur = cur->prev) {
        float temp_ret;
        cur->vel.y -= arg2[1][2];
        it_802A4420(cur);
        it_802A43EC(cur);
        it_802BB938(cur, 0, arg2[0][1]);
        temp_ret = it_802A3C98(&cur->pos, &prev->pos, &origin);
        ret = temp_ret;
        if (temp_ret > arg2[0][1]) {
            cur->pos.x = origin.x * arg2[0][1] + prev->pos.x;
            cur->pos.y = origin.y * arg2[0][1] + prev->pos.y;
            cur->pos.z = origin.z * arg2[0][1] + prev->pos.z;
        }
    }
    return ret;
}

/// #it_802BBD64

/// #it_802BBED0

/// #it_802BC080

int it_802BC94C(ItemLink* arg0, Vec3* arg1, Mtx arg2, f32 farg0)
{
    ItemLink *var_r30, *var_r29;
    PAD_STACK(3 * 4);

    for (var_r29 = arg0, var_r30 = arg0->prev;
         var_r30 != NULL && !var_r29->x2C_b0;)
    {
        var_r29 = var_r30;
        var_r30 = var_r30->prev;
    }
    {
        Vec3 sp18;
        float var_f1 = it_802A3C98(&var_r29->pos, arg1, &sp18);
        while (var_r30 != NULL && farg0 > var_f1) {
            var_r29->x2C_b0 = false;
            var_f1 = it_802A3C98(&var_r30->pos, arg1, &sp18);
            var_r29 = var_r30;
            var_r30 = var_r30->prev;
        }
        {
            float var_f1_2 = var_f1 - farg0;
            it_802BBC38(var_r29, arg1, arg2, MAX(var_f1_2, arg2[0][1]));
        }
    }
    if (var_r30 != NULL) {
        return false;
    }
    return true;
}

void it_802BCA30(Item* ip)
{
    ItemLink* link = ip->xDD4_itemVar.seakchain.x0;
    HSD_JObj* jobj0 = link->gobj->hsd_obj;
    Mtx mtx;
    Vec3 vec = { 0 };
    PAD_STACK(3 * 4);
    HSD_JObjSetupMatrix(link->jobj);
    PSMTXIdentity(mtx);
    mtx[0][3] = vec.x;
    mtx[1][3] = vec.y;
    mtx[2][3] = vec.z;
    PSMTXConcat(link->jobj->mtx, mtx, mtx);
    HSD_JObjCopyMtx(jobj0, mtx);
    jobj0->flags |=
        JOBJ_USER_DEF_MTX | JOBJ_MTX_INDEP_PARENT | JOBJ_MTX_INDEP_SRT;
    HSD_JObjSetMtxDirty(jobj0);
}

void it_802BCB88(Item* arg0, Vec3* arg1)
{
    ItemLink* link = arg0->xDD4_itemVar.seakchain.x4;
    itSeakChain_Attrs* sa = arg0->xC4_article_data->x4_specialAttributes;
    HSD_JObj* jobj;
    int const divisor = 3;
    int count;
    int stride = sa->x0 / divisor;
    while (!link->x2C_b0) {
        link = link->prev;
    }
    {
        ItemLink* cur;
        ItemLink* prev;
        Vec3 pos0;
        count = 0;
        for (; link != NULL; link = link->prev) {
            cur = link->next;
            if (cur != NULL) {
                if (cur->x2C_b0) {
                    pos0 = cur->pos;
                } else {
                    pos0 = *arg1;
                }
            } else {
                pos0 = *arg1;
            }
            prev = link->prev;
            {
                Vec3 pos1;
                if (prev != NULL) {
                    pos1 = prev->pos;
                } else {
                    pos1 = link->pos;
                }
                {
                    jobj = GET_JOBJ(link->gobj);
                    {
                        Vec3 translate = link->pos;
                        HSD_JObjSetTranslate(jobj, &translate);
                        if (count % stride == 0) {
                            int i;
                            for (i = divisor; i > count / stride; i--) {
                                ftSk_SpecialS_UpdateHitboxes(
                                    arg0->xDD4_itemVar.seakchain.x8,
                                    &translate, i - 1);
                            }
                        }
                        if (link->prev == NULL) {
                            ftSk_SpecialS_UpdateHitboxes(
                                arg0->xDD4_itemVar.seakchain.x8, &translate,
                                divisor);
                        }
                        ++count;
                        {
                            Vec3 dir;
                            dir.x = pos1.x - pos0.x;
                            dir.y = pos1.y - pos0.y;
                            dir.z = pos1.z - pos0.z;
                            lbVector_Normalize(&dir);
                            it_802A6DC8(jobj, &translate, &dir);
                        }
                    }
                    {
                        Mtx mtx;
                        PSMTXCopy(jobj->mtx, mtx);
                        mtx[0][0] *= sa->x4;
                        mtx[1][0] *= sa->x4;
                        mtx[2][0] *= sa->x4;
                        mtx[0][1] *= sa->x4;
                        mtx[1][1] *= sa->x4;
                        mtx[2][1] *= sa->x4;
                        mtx[0][2] *= sa->x4;
                        mtx[1][2] *= sa->x4;
                        mtx[2][2] *= sa->x4;
                        PSMTXCopy(mtx, jobj->mtx);
                        link = link->prev;
                    }
                }
            }
        }
    }
}

void it_2725_Logic54_PickedUp(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    PAD_STACK(4);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    item->on_accessory = fn_802BB428;
}

void it_802BCED4(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(2 * 4);
    ftColl_8007AFF8(ip->xDD4_itemVar.seakchain.x8);
    Item_80268E5C(gobj, 3, ITEM_ANIM_UPDATE);
    ip->on_accessory = fn_802BB694;
}

void it_802BCF2C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(2 * 4);
    ftColl_8007AFF8(ip->xDD4_itemVar.seakchain.x8);
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
    ip->on_accessory = fn_802BB574;
}

void it_802BCF84(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(4);
    Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE);
    ip->on_accessory = fn_802BB784;
}

void it_802BCFC4(Item_GObj* gobj, Vec3* vel)
{
    PAD_STACK(2 * 4);
    {
        Item* ip = GET_ITEM(gobj);
        ItemLink* link = ip->xDD4_itemVar.seakchain.x0;
        Vec3 pos;
        PAD_STACK(2 * 4);
        {
            Mtx mtx;
            PAD_STACK(2 * 4);
            PSMTXIdentity(mtx);
            mtx[0][3] = 0.0f;
            mtx[1][3] = 0.0f;
            mtx[2][3] = 0.1f;
            HSD_JObjSetupMatrix(link->jobj);
            PSMTXConcat(link->jobj->mtx, mtx, mtx);
            {
                pos.x = mtx[0][3];
                pos.y = mtx[1][3];
                pos.z = mtx[2][3];
                link->pos = pos;
            }
            it_8026BB68(ip->xDD4_itemVar.seakchain.x8,
                        &link->coll_data.cur_pos);
            link->coll_data.last_pos = link->coll_data.cur_pos;
            link->x2C_b0 = true;
            link->vel = *vel;
            Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
            ip->on_accessory = fn_802BB44C;
        }
    }
}

void itSeakChain_Logic54_EvtUnk(Item_GObj* gobj, Fighter_GObj* ref_gobj)
{
    Item* item = GET_ITEM(gobj);
    it_8026B894(gobj, ref_gobj);
    if (item->xDD4_itemVar.seakchain.x8 == ref_gobj) {
        item->xDD4_itemVar.seakchain.x8 = NULL;
    }
}
