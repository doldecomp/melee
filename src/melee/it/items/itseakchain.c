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
                /// @todo #ItemLink::x1D0_GObj GObj or JObj?
                HSD_GObj* cur_gobj = cur->x1D0_GObj;
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

/// #fn_802BB44C

/// #fn_802BB574

/// @todo Shared inline with #fn_802BB784
void fn_802BB694(Item_GObj* gobj)
{
    Vec3 vec;
    Mtx mtx;
    Item* ip = GET_ITEM(gobj);
    ItemLink* chain_x4 = ip->xDD4_itemVar.seakchain.x4;
    PSMTXIdentity(mtx);
    mtx[0][3] = 0.0f;
    mtx[1][3] = 0.0f;
    mtx[2][3] = 0.1f;
    HSD_JObjSetupMatrix(chain_x4->x1D4_JObj);
    PSMTXConcat(chain_x4->x1D4_JObj->mtx, mtx, mtx);
    vec.x = mtx[0][3];
    vec.y = mtx[1][3];
    vec.z = mtx[2][3];
    it_802BC080(chain_x4, &vec, ip);
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
    HSD_JObjSetupMatrix(link->x1D4_JObj);
    PSMTXConcat(link->x1D4_JObj->mtx, mtx, mtx);
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

/// #it_802BBB0C

int it_802BBC38(ItemLink* link, Vec3* offset, Mtx arg2, f32 scale)
{
    Point3d origin;
    ItemLink* cur = link->prev;
    ItemLink* prev = link;
    int ret = it_802A3C98(&prev->pos, offset, &origin);
    prev->pos.x = (origin.x * scale) + offset->x;
    prev->pos.y = (origin.y * scale) + offset->y;
    prev->pos.z = (origin.z * scale) + offset->z;
    for (; cur != NULL; prev = cur, cur = cur->prev) {
        float temp_ret;
        cur->x8_vel.y -= arg2[1][2];
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

int it_802BC94C(ItemLink* arg0, Point3d* arg1, Mtx arg2, f32 farg0)
{
    ItemLink *var_r30, *var_r29;
    PAD_STACK(3 * 4);

    for (var_r29 = arg0, var_r30 = arg0->prev;
         var_r30 != NULL && !var_r29->flag0;)
    {
        var_r29 = var_r30;
        var_r30 = var_r30->prev;
    }
    {
        Point3d sp18;
        float var_f1 = it_802A3C98(&var_r29->pos, arg1, &sp18);
        while (var_r30 != NULL && farg0 > var_f1) {
            var_r29->flag0 = false;
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
    ItemLink* chain_x0 = ip->xDD4_itemVar.seakchain.x0;
    HSD_JObj* jobj0 = (HSD_JObj*) chain_x0->x1D0_GObj;
    Mtx mtx;
    Vec3 vec = { 0 };
    PAD_STACK(3 * 4);
    HSD_JObjSetupMatrix(chain_x0->x1D4_JObj);
    PSMTXIdentity(mtx);
    mtx[0][3] = vec.x;
    mtx[1][3] = vec.y;
    mtx[2][3] = vec.z;
    PSMTXConcat(chain_x0->x1D4_JObj->mtx, mtx, mtx);
    HSD_JObjCopyMtx(jobj0, mtx);
    jobj0->flags |=
        JOBJ_USER_DEF_MTX | JOBJ_MTX_INDEP_PARENT | JOBJ_MTX_INDEP_SRT;
    HSD_JObjSetMtxDirty(jobj0);
}

/// #it_802BCB88

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

/// #it_802BCFC4

void itSeakChain_Logic54_EvtUnk(Item_GObj* gobj, Fighter_GObj* ref_gobj)
{
    Item* item = GET_ITEM(gobj);
    it_8026B894(gobj, ref_gobj);
    if (item->xDD4_itemVar.seakchain.x8 == ref_gobj) {
        item->xDD4_itemVar.seakchain.x8 = NULL;
    }
}
