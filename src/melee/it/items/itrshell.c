#include "itrshell.h"

#include "m2c_macros.h"
#include <placeholder.h>
#include <platform.h>

#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/item.h"
#include "it/it_2725.h"

/// #it_8028CFE0

/// #it_8028D090

/// #it_8028D100

/// #it_8028D26C

s32 it_8028D390(Item_GObj* gobj)
{
    // TODO: clean up with union
    Item* ip = GET_ITEM(gobj);
    s32* decp = &M2C_FIELD(ip, s32*, 0xDEC);
    s32 dec = *decp;

    *decp = dec - 1;
    if (*decp == 0) {
        M2C_FIELD(ip, s32*, 0xDF0) = 1;
    }
    return dec;
}

/// #it_8028D3B8

/// #fn_8028D4A8

/// #it_8028D4E4

/// #it_8028D56C

/// #it_3F14_Logic15_Spawned

/// #it_8028D62C

bool itRshell_UnkMotion0_Anim(Item_GObj* gobj)
{
    return false;
}

void itRshell_UnkMotion0_Phys(Item_GObj* gobj) {}

/// #itRshell_UnkMotion0_Coll

void it_8028D7F0(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
}

bool itRshell_UnkMotion1_Anim(Item_GObj* gobj)
{
    return false;
}

/// #itRshell_UnkMotion1_Phys

/// #itRshell_UnkMotion1_Coll

/// #it_3F14_Logic15_PickedUp

bool itRshell_UnkMotion2_Anim(Item_GObj* gobj)
{
    return false;
}

void itRshell_UnkMotion2_Phys(Item_GObj* gobj) {}

/// #it_3F14_Logic15_Thrown

/// #itRshell_UnkMotion3_Anim

/// #itRshell_UnkMotion3_Phys

/// #itRshell_UnkMotion3_Coll

/// #it_3F14_Logic15_Dropped

/// #itRshell_UnkMotion4_Anim

/// #itRshell_UnkMotion4_Phys

/// #itRshell_UnkMotion4_Coll

/// #it_8028DAE4

/// #itRshell_UnkMotion5_Anim

/// #itRshell_UnkMotion5_Phys

/// #itRshell_UnkMotion5_Coll

/// #it_8028E170

/// #itRshell_UnkMotion6_Anim

/// #itRshell_UnkMotion6_Phys

/// #itRshell_UnkMotion6_Coll

/// #it_3F14_Logic15_EnteredAir

bool itRshell_UnkMotion7_Anim(Item_GObj* gobj)
{
    return false;
}

void itRshell_UnkMotion7_Phys(Item_GObj* gobj) {}

/// #itRshell_UnkMotion7_Coll

/// #it_3F14_Logic15_DmgDealt

/// #it_3F14_Logic15_DmgReceived

/// #it_3F14_Logic15_Reflected

bool it_3F14_Logic15_Clanked(Item_GObj* gobj)
{
    itColl_BounceOffVictim(gobj);
    return false;
}

/// #it_3F14_Logic15_HitShield

/// #it_3F14_Logic15_ShieldBounced

/// #it_8028E6C0

void it_3F14_Logic15_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
