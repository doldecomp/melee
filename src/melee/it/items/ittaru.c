#include "ittaru.h"

#include <placeholder.h>
#include <platform.h>

#include "it/it_26B1.h"
#include "it/it_2725.h"

/// #it_3F14_Logic2_Spawned

/// #it_802874F0

/// #it_80287690

/// #itTaru_UnkMotion0_Anim

void itTaru_UnkMotion0_Phys(Item_GObj* gobj) {}

/// #itTaru_UnkMotion0_Coll

/// #it_80287D0C

bool itTaru_UnkMotion1_Anim(Item_GObj* gobj)
{
    return false;
}

/// #itTaru_UnkMotion1_Phys

/// #itTaru_UnkMotion1_Coll

/// #it_3F14_Logic2_PickedUp

bool itTaru_UnkMotion2_Anim(Item_GObj* gobj)
{
    return false;
}

void itTaru_UnkMotion2_Phys(Item_GObj* gobj) {}

void it_3F14_Logic2_Dropped(Item_GObj* gobj)
{
    it_80287F20(gobj);
}

/// #it_3F14_Logic2_Thrown

/// #it_80287F20

/// #itTaru_UnkMotion3_Anim

/// #itTaru_UnkMotion3_Phys

/// #itTaru_UnkMotion3_Coll

void it_80288194(Item_GObj* gobj)
{
    it_802881FC(gobj);
}

/// #it_802881B4

/// #it_802881FC

/// #itTaru_UnkMotion5_Anim

/// #itTaru_UnkMotion5_Phys

/// #itTaru_UnkMotion5_Coll

/// #itTaru_UnkMotion4_Anim

/// #itTaru_UnkMotion4_Phys

bool itTaru_UnkMotion4_Coll(Item_GObj* gobj)
{
    return itTaru_UnkMotion5_Coll(gobj);
}

/// #it_802885C8

bool itTaru_UnkMotion6_Anim(Item_GObj* gobj)
{
    return it_802751D8(gobj);
}

void itTaru_UnkMotion6_Phys(Item_GObj* gobj) {}

bool itTaru_UnkMotion6_Coll(Item_GObj* gobj)
{
    return false;
}

/// #it_802886C4

/// #itTaru_UnkMotion7_Anim

void itTaru_UnkMotion7_Phys(Item_GObj* gobj) {}

bool itTaru_UnkMotion7_Coll(Item_GObj* gobj)
{
    return false;
}

/// #it_3F14_Logic2_DmgDealt

/// #it_3F14_Logic2_Clanked

/// #it_3F14_Logic2_HitShield

/// #it_3F14_Logic2_Reflected

/// #it_3F14_Logic2_DmgReceived

void it_3F14_Logic2_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
