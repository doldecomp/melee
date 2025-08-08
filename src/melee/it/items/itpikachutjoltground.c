#include "itpikachutjoltground.h"

#include "it/inlines.h"

/* 2B37F0 */ static void itPikachutjoltground_UnkMotion1_Phys(Item_GObj*);

/// #it_802B3368

/// #it_802B338C

/// #it_802B34E4

void it_802B3544(Item_GObj* gobj)
{
    GET_ITEM(gobj)->xDD4_itemVar.pikachujoltground.unk_8 = 0;
}

/// #it_802B3554

/// #itPikachutjoltground_UnkMotion0_Anim

/// #itPikachutjoltground_UnkMotion1_Anim

/// #itPikachutjoltground_UnkMotion0_Phys

void itPikachutjoltground_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itResetVelocity(ip);
}

/// #itPikachutjoltground_UnkMotion0_Coll

/// #itPikachutjoltground_UnkMotion1_Coll

/// #it_802B3A94

/// #it_802B3AF8

/// #it_802B3C44

/// #it_802B3CA8

/// #it_802B3D0C

/// #it_802B3D70

/// #it_802B3EDC
