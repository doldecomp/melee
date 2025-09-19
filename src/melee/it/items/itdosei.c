#include "itdosei.h"

#include <placeholder.h>
#include <platform.h>

#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/it_266F.h"
#include "it/it_2725.h"

/// #it_3F14_Logic7_Spawned

/// #fn_80281390

/// #itDosei_UnkMotion0_Anim

void itDosei_UnkMotion0_Phys(Item_GObj* gobj) {}

/// #itDosei_UnkMotion0_Coll

/// #fn_80281734

/// #it_802817A0

/// #itDosei_UnkMotion1_Anim

/// #itDosei_UnkMotion1_Phys

/// #itDosei_UnkMotion1_Coll

/// #it_80281C6C

/// #itDosei_UnkMotion2_Anim

void itDosei_UnkMotion2_Phys(Item_GObj* gobj) {}

/// #itDosei_UnkMotion2_Coll

/// #it_80282074

/// #itDosei_UnkMotion3_Anim

/// #itDosei_UnkMotion3_Phys

bool itDosei_UnkMotion5_Coll(Item_GObj* gobj)
{
    it_8026E15C(gobj, it_802817A0);
    return false;
}

/// #it_3F14_Logic7_PickedUp

/// #itDosei_UnkMotion4_Anim

void itDosei_UnkMotion4_Phys(Item_GObj* gobj) {}

/// #it_3F14_Logic7_Dropped

/// #it_3F14_Logic7_Thrown

bool itDosei_UnkMotion5_Anim(Item_GObj* gobj)
{
    return false;
}

/// #itDosei_UnkMotion5_Phys

/// #it_3F14_Logic7_EnteredAir

bool itDosei_UnkMotion6_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.dosei.xDE4 = ip->pos;
    return false;
}

void itDosei_UnkMotion6_Phys(Item_GObj* gobj) {}

/// #itDosei_UnkMotion6_Coll

/// #it_80282BFC

bool itDosei_UnkMotion8_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.dosei.xDE4 = ip->pos;
    return false;
}

/// #itDosei_UnkMotion8_Phys

bool itDosei_UnkMotion8_Coll(Item_GObj* gobj)
{
    it_8026E15C(gobj, fn_80282CD4);
    return false;
}

/// #fn_80282CD4

/// #itDosei_UnkMotion7_Anim

void itDosei_UnkMotion7_Phys(Item_GObj* gobj) {}

/// #itDosei_UnkMotion7_Coll

/// #it_80282DE4

/// #itDosei_UnkMotion9_Anim

void itDosei_UnkMotion9_Phys(Item_GObj* gobj) {}

/// #itDosei_UnkMotion9_Coll

/// #itDosei_UnkMotion10_Anim

void itDosei_UnkMotion10_Phys(Item_GObj* gobj) {}

/// #itDosei_UnkMotion10_Coll

/// #it_3F14_Logic7_DmgReceived

/// #itDosei_UnkMotion11_Anim

/// #itDosei_UnkMotion11_Phys

bool itDosei_UnkMotion11_Coll(Item_GObj* gobj)
{
    it_8026E15C(gobj, fn_80281390);
    return false;
}

/// #it_3F14_Logic7_DmgDealt

bool it_3F14_Logic7_Reflected(Item_GObj* gobj)
{
    return it_80273030(gobj);
}

bool it_3F14_Logic7_Clanked(Item_GObj* gobj)
{
    itColl_BounceOffVictim(gobj);
    return false;
}

bool it_3F14_Logic7_HitShield(Item_GObj* gobj)
{
    itColl_BounceOffVictim(gobj);
    return false;
}

bool it_3F14_Logic7_ShieldBounced(Item_GObj* gobj)
{
    return itColl_BounceOffShield(gobj);
}

void it_3F14_Logic7_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
