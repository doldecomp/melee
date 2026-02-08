#include "itseakchain.h"

#include "it/items/itseakchain.static.h"

#include "baselib/jobj.h"

#include "it/forward.h"

#include "ft/ftcoll.h"
#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/itCharItems.h"
#include "it/item.h"

void it_802BAEEC(Item_GObj* gobj)
{
    it_8026B724(gobj);
}

void it_802BAF0C(Item_GObj* gobj)
{
    it_8026B73C(gobj);
}

/// #it_802BAF2C

/// #it_802BB20C

/// #it_802BB290

void fn_802BB428(Item_GObj* gobj)
{
    it_802BCA30(GET_ITEM(gobj));
}

/// #fn_802BB44C

/// #fn_802BB574

/// #fn_802BB694

/// #fn_802BB784

/// #itSeakchain_UnkMotion4_Anim

/// #it_802BB938

s32 it_802BBAEC(ItemLink* link, s32 arg1, f32 arg2)
{
    return it_802BB938(link, arg1, arg2);
}

/// #it_802BBB0C

/// #it_802BBC38

/// #it_802BBD64

/// #it_802BBED0

/// #it_802BC080

/// #it_802BC94C

void it_802BCA30(Item* ip)
{
    struct itSeakChain_ItemVars_x0_t* chain_x0 = ip->xDD4_itemVar.seakchain.x0;
    HSD_JObj* jobj0 = chain_x0->x1D0;
    Mtx mtx;
    Vec3 vec = { 0 };
    PAD_STACK(3 * 4);
    HSD_JObjSetupMatrix(chain_x0->x1D4);
    PSMTXIdentity(mtx);
    mtx[0][3] = vec.x;
    mtx[1][3] = vec.y;
    mtx[2][3] = vec.z;
    PSMTXConcat(chain_x0->x1D4->mtx, mtx, mtx);
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
    ftColl_8007AFF8(ip->xDD4_itemVar.seakchain.x8);
    Item_80268E5C(gobj, 3, ITEM_ANIM_UPDATE);
    ip->on_accessory = (HSD_GObjEvent) fn_802BB694;
}

void it_802BCF2C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ftColl_8007AFF8(ip->xDD4_itemVar.seakchain.x8);
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
    ip->on_accessory = (HSD_GObjEvent) fn_802BB574;
}

void it_802BCF84(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE);
    ip->on_accessory = (HSD_GObjEvent) fn_802BB784;
}

/// #it_802BCFC4

void itSeakChain_Logic54_EvtUnk(Item_GObj* arg0, Item_GObj* arg1)
{
    Item* item = GET_ITEM((HSD_GObj*) arg0);
    it_8026B894(arg0, (HSD_GObj*) arg1);
    if ((HSD_GObj*) item->xDD4_itemVar.seakchain.x8 == arg1) {
        item->xDD4_itemVar.seakchain.x8 = NULL;
    }
}
