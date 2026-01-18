#include "itseakchain.h"

#include "itlinkhookshot.h"

#include "it/forward.h"

#include "it/inlines.h"
#include "it/it_26B1.h"

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

/// #fn_802BB428
s32 fn_802BB428(Item_GObj* gobj)
{
    return it_802BCA30(GET_ITEM(gobj));
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

/// #it_802BCA30

/// #it_802BCB88

/// #it_2725_Logic54_PickedUp

/// #it_802BCED4

/// #it_802BCF2C

/// #it_802BCF84

/// #it_802BCFC4

void it_2725_Logic54_EvtUnk(Item_GObj* arg0, Item_GObj* arg1)
{
    Item* item = GET_ITEM((HSD_GObj*) arg0);
    it_8026B894(arg0, (HSD_GObj*) arg1);
    if ((HSD_GObj*) item->xDD4_itemVar.seakchain.x8 == arg1) {
        item->xDD4_itemVar.seakchain.x8 = NULL;
    }
}
