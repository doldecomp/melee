#include "it/forward.h"

#include "itnesspkflush.h"

#include "it/inlines.h"
#include "it/it_26B1.h"

/* 2AB29C */ static bool itNesspkflush_UnkMotion1_Coll(Item_GObj* gobj);
/* 2AB2A4 */ static bool itNesspkflush_UnkMotion2_Coll(Item_GObj* gobj);

Fighter_GObj* it_802AA7E4(Item_GObj* gobj)
{
    return GET_ITEM(gobj)->owner;
}

bool it_802AA7F0(Item_GObj* gobj)
{
    Item* it = GET_ITEM(gobj);
    if (it->msid == 0x2) {
        return 1;
    }
    return 0;
}

/// #it_802AA810

/// #it_802AA8C0

/// #it_2725_Logic102_Destroyed

/// #it_802AAA50

/// #it_802AAA80

/// #itNesspkflush_UnkMotion0_Anim

/// #itNesspkflush_UnkMotion1_Anim

/// #itNesspkflush_UnkMotion2_Anim

/// #itNesspkflush_UnkMotion0_Phys

void itNesspkflush_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itResetVelocity(ip);
}

void itNesspkflush_UnkMotion2_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itResetVelocity(ip);
}

/// #itNesspkflush_UnkMotion0_Coll

bool itNesspkflush_UnkMotion1_Coll(Item_GObj* gobj)
{
    return false;
}

bool itNesspkflush_UnkMotion2_Coll(Item_GObj* gobj)
{
    return false;
}

/// #it_2725_Logic102_Reflected

bool it_2725_Logic102_Clanked(Item_GObj* arg0)
{
    return true;
}

bool it_2725_Logic102_Absorbed(Item_GObj* arg0)
{
    return true;
}

void it_2725_Logic102_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
