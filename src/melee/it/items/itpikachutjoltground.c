#include "itpikachutjoltground.h"

#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"

/* 2B37F0 */ static void itPikachutjoltground_UnkMotion1_Phys(Item_GObj*);

void* it_802B3368(Item_GObj* gobj)
{
    Item* ip;

    if (gobj != NULL) {
        ip = GET_ITEM(gobj);
        if (ip != NULL) {
            return ip->xDD4_itemVar.pikachujoltground.unk_8;
        }
    }
    return NULL;
}

/// #it_802B338C

/// #it_2725_Logic106_Destroyed

void it_802B3544(Item_GObj* gobj)
{
    GET_ITEM(gobj)->xDD4_itemVar.pikachujoltground.unk_8 = 0;
}

/// #it_802B3554

bool itPikachutjoltground_UnkMotion0_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.pikachujoltground.xDE8 = ip->pos;
    return it_80273130(gobj);
}

/// #itPikachutjoltground_UnkMotion1_Anim

/// #itPikachutjoltground_UnkMotion0_Phys

void itPikachutjoltground_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itResetVelocity(ip);
}

/// #itPikachutjoltground_UnkMotion0_Coll

/// #itPikachutjoltground_UnkMotion1_Coll

/// #it_2725_Logic106_DmgDealt

/// #it_2725_Logic106_Reflected

/// #it_2725_Logic106_Clanked

/// #it_2725_Logic106_Absorbed

/// #it_2725_Logic106_HitShield

/// #it_2725_Logic106_ShieldBounced

void itPikachuTJoltGround_Logic106_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
