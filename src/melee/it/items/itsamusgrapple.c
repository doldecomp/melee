#include "itsamusgrapple.h"

#include "itlinkhookshot.h"

#include "it/inlines.h"
#include "it/item.h"

void it_2725_Logic53_Spawned(Item_GObj* gobj)
{
    GET_ITEM(gobj)->xDD4_itemVar.samusgrapple.unk_10 = NULL;
}

/// #it_802B7160

/// #it_802B743C

/// #it_802B75FC

/// #it_802B7B84

/// #it_802B7C18

/// #fn_802B7E34

void itSamusgrapple_UnkMotion0_Phys(Item_GObj* gobj)
{
    GET_ITEM(gobj)->xDD4_itemVar.samusgrapple.unk_10 = fn_802B7E34;
}

/// #fn_802B805C

void itSamusgrapple_UnkMotion1_Phys(Item_GObj* gobj)
{
    GET_ITEM(gobj)->xDD4_itemVar.samusgrapple.unk_10 = fn_802B805C;
}

/// #fn_802B8384

void itSamusgrapple_UnkMotion2_Phys(Item_GObj* gobj)
{
    GET_ITEM(gobj)->xDD4_itemVar.samusgrapple.unk_10 = fn_802B8384;
}

/// #fn_802B8524

void itSamusgrapple_UnkMotion3_Phys(Item_GObj* gobj)
{
    GET_ITEM(gobj)->xDD4_itemVar.samusgrapple.unk_10 = fn_802B8524;
}

/// #fn_802B8684

void itSamusgrapple_UnkMotion4_Phys(Item_GObj* gobj)
{
    GET_ITEM(gobj)->xDD4_itemVar.samusgrapple.unk_10 = fn_802B8684;
}

/// #fn_802B8814

void itSamusgrapple_UnkMotion5_Phys(Item_GObj* gobj)
{
    GET_ITEM(gobj)->xDD4_itemVar.samusgrapple.unk_10 = fn_802B8814;
}

/// #fn_802B895C

void itSamusgrapple_UnkMotion6_Phys(Item_GObj* gobj)
{
    GET_ITEM(gobj)->xDD4_itemVar.samusgrapple.unk_10 = fn_802B895C;
}

/// #fn_802B8B54

void itSamusgrapple_UnkMotion7_Phys(Item_GObj* gobj)
{
    GET_ITEM(gobj)->xDD4_itemVar.samusgrapple.unk_10 = fn_802B8B54;
}

/// #fn_802B8D38

void itSamusgrapple_UnkMotion8_Phys(Item_GObj* gobj)
{
    GET_ITEM(gobj)->xDD4_itemVar.samusgrapple.unk_10 = fn_802B8D38;
}

/// #it_802B900C

/// #it_802B91C4

/// #it_802B9328

/// #it_802B99A0

/// #it_802B9CE8

/// #it_802B9FD4

/// #it_802BA194

/// #it_802BA2D8

/// #it_802BA3BC

/// #it_802BA5DC

/// #it_802BA760

void it_2725_Logic53_PickedUp(Item_GObj* gobj)
{
    PAD_STACK(16);
    Item_80268E5C((HSD_GObj*) gobj, 0, ITEM_ANIM_UPDATE);
    it_802A2428(gobj);
}

/// #it_802BA9B8

/// #it_802BAA08

void it_802BAA58(Item_GObj* gobj)
{
    PAD_STACK(16);
    Item_80268E5C((HSD_GObj*) gobj, 4, ITEM_ANIM_UPDATE);
    it_802A2428(gobj);
}

/// #it_802BAA94

/// #it_802BAAE4

/// #it_802BAB40

/// #it_802BAB7C

/// #it_802BABB8

/// #it_802BAC3C

/// #it_802BAC80

/// #it_802BACC4

/// #it_2725_Logic53_EvtUnk
