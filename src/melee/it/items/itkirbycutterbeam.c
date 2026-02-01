#include "itkirbycutterbeam.h"

#include <placeholder.h>
#include <platform.h>

#include "it/forward.h"

#include "it/it_26B1.h"
#include "it/it_2725.h"

/// #it_8029BAB8

/// #it_8029BB90

bool itKirbycutterbeam_UnkMotion0_Anim(Item_GObj* gobj)
{
    return it_80273130(gobj);
}

/// #itKirbycutterbeam_UnkMotion0_Phys

/// #itKirbycutterbeam_UnkMotion0_Coll

bool itKirbyCutterBeam_Logic7_DmgDealt(Item_GObj* arg0)
{
    return false;
}

bool itKirbyCutterBeam_Logic7_Clanked(Item_GObj* arg0)
{
    return true;
}

bool itKirbyCutterBeam_Logic7_Absorbed(Item_GObj* arg0)
{
    return true;
}

/// #it_2725_Logic7_Reflected

/// #it_2725_Logic7_ShieldBounced

bool itKirbyCutterBeam_Logic7_HitShield(Item_GObj* arg0)
{
    return true;
}

void it_8029C4B4(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
