#include "itlipstick.h"

#include "it/inlines.h"
#include "it/it_26B1.h"

/// #it_8029570C

/// #it_80295748

/// #it_80295770

/// #it_802957AC

bool itLipstick_UnkMotion0_Anim(Item_GObj* gobj)
{
    return false;
}

void itLipstick_UnkMotion0_Phys(Item_GObj* gobj) {}

/// #itLipstick_UnkMotion0_Coll

/// #it_8029583C

bool itLipstick_UnkMotion4_Anim(Item_GObj* gobj)
{
    return false;
}

/// #itLipstick_UnkMotion1_Phys

/// #itLipstick_UnkMotion1_Coll

/// #it_802958C8

bool itLipstick_UnkMotion2_Anim(Item_GObj* gobj)
{
    GET_ITEM(gobj)->xDAC_itcmd_var0 = 1;
    return false;
}

void itLipstick_UnkMotion2_Phys(Item_GObj* gobj) {}

/// #it_80295908

/// #itLipstick_UnkMotion4_Coll

/// #it_80295974

/// #itLipstick_UnkMotion4_Phys

/// #itLipstick_UnkMotion3_Coll

/// #it_80295ACC

/// #it_80295B08

bool itLipstick_UnkMotion5_Anim(Item_GObj* gobj)
{
    return false;
}

void itLipstick_UnkMotion5_Phys(Item_GObj* gobj) {}

/// #itLipstick_UnkMotion5_Coll

/// #it_80295B70

/// #it_80295BAC

/// #it_80295BCC

/// #it_80295C08

void it_80295C28(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
