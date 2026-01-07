#include "itnesspkfire.h"

#include <placeholder.h>
#include <platform.h>

#include "it/forward.h"

#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"

/// #it_802AA054

/// #it_802AA1D8

/// #itNesspkfire_UnkMotion0_Anim

bool itNesspkfire_UnkMotion0_Coll(Item_GObj* gobj)
{
    return it_8026E058(gobj);
}

/// #it_2725_Logic23_DmgDealt

/// #it_2725_Logic23_Clanked

bool it_2725_Logic23_Absorbed(Item_GObj* arg0)
{
    return true;
}

bool it_2725_Logic23_HitShield(Item_GObj* arg0)
{
    return true;
}

bool it_2725_Logic23_Reflected(Item_GObj* gobj)
{
    return it_80273030(gobj);
}

/// #it_2725_Logic23_ShieldBounced

void it_802AA474(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
