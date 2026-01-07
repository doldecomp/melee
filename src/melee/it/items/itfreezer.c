#include "itfreezer.h"

#include <placeholder.h>
#include <platform.h>

#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"

/// #it_802CCF9C

void it_802CCFFC(Item_GObj* gobj) {}

void it_802CD000(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

/// #itFreezer_UnkMotion1_Anim

void itFreezer_UnkMotion1_Phys(Item_GObj* gobj) {}

bool itFreezer_UnkMotion1_Coll(Item_GObj* gobj)
{
    it_8026E15C(gobj, it_802CCFFC);
    return false;
}

/// #it_802CD090

/// #it_802CD12C

/// #itFreezer_UnkMotion2_Anim

/// #itFreezer_UnkMotion2_Phys

bool itFreezer_UnkMotion2_Coll(Item_GObj* gobj)
{
    return false;
}

/// #it_802CD290

/// #it_802CD2EC

bool itFreezer_UnkMotion0_Anim(Item_GObj* gobj)
{
    it_80279FF8(gobj);
    return false;
}

/// #itFreezer_UnkMotion0_Phys

bool itFreezer_UnkMotion0_Coll(Item_GObj* gobj)
{
    return it_8027A118(gobj, (void (*)(HSD_GObj*)) it_802CCFFC);
}
