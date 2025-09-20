#include "itbombhei.h"

#include <placeholder.h>
#include <platform.h>
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/it_266F.h"
#include "it/inlines.h"


/// #it_8027D670

/// #it_8027D730

/// #it_3F14_Logic6_Spawned

/// #it_8027D820

/// #fn_8027DAC8

/// #itBombhei_UnkMotion0_Anim

void itBombhei_UnkMotion0_Phys(Item_GObj* gobj) {}

bool itBombhei_UnkMotion0_Coll(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_8027DE18);
    return false;
}

/// #it_8027DE18

bool itBombhei_UnkMotion1_Anim(Item_GObj* gobj)
{
    return false;
}

void itBombhei_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

/// #itBombhei_UnkMotion1_Coll

/// #it_3F14_Logic6_PickedUp

/// #itBombhei_UnkMotion8_Anim

void itBombhei_UnkMotion8_Phys(Item_GObj* gobj) {}

/// #it_3F14_Logic6_Dropped

/// #it_8027E978

/// #itBombhei_UnkMotion3_Anim

void itBombhei_UnkMotion3_Phys(Item_GObj* gobj) {}

/// #itBombhei_UnkMotion3_Coll

/// #it_8027EE04

/// #itBombhei_UnkMotion2_Anim

void itBombhei_UnkMotion2_Phys(Item_GObj* gobj) {}

/// #itBombhei_UnkMotion2_Coll

/// #it_8027F42C

/// #itBombhei_UnkMotion4_Anim

void itBombhei_UnkMotion4_Phys(Item_GObj* gobj) {}

/// #itBombhei_UnkMotion4_Coll

/// #it_8027F8E0

bool itBombhei_UnkMotion5_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.bombhei.xDE0 != 0) {
        it_8027D820(gobj);
    }
    return false;
}

void itBombhei_UnkMotion5_Phys(Item_GObj* gobj) {}

bool itBombhei_UnkMotion5_Coll(Item_GObj* gobj)
{
    it_8026D62C(gobj, fn_8027FCA8);
    return false;
}

/// #fn_8027FCA8

bool itBombhei_UnkMotion6_Anim(Item_GObj* gobj)
{
    it_8027D820(gobj);
    return false;
}

/// #itBombhei_UnkMotion6_Phys

/// #fn_8028007C

/// #itBombhei_UnkMotion6_Coll

/// #it_3F14_Logic6_Thrown

/// #itBombhei_UnkMotion10_Anim

/// #itBombhei_UnkMotion10_Phys

/// #fn_80280974

/// #itBombhei_UnkMotion10_Coll

/// #it_80280B60

void it_80280DC0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.bombhei.xDDC == 0) {
        it_80280B60(gobj);
    }
}

/// #it_3F14_Logic6_DmgDealt

/// #it_3F14_Logic6_DmgReceived

bool itBombhei_UnkMotion11_Anim(Item_GObj* gobj)
{
    return it_802751D8(gobj);
}

void itBombhei_UnkMotion11_Phys(Item_GObj* gobj) {}

bool itBombhei_UnkMotion11_Coll(Item_GObj* gobj)
{
    return false;
}

/// #it_3F14_Logic6_EnteredAir

bool itBombhei_UnkMotion12_Anim(Item_GObj* gobj)
{
    return false;
}

void itBombhei_UnkMotion12_Phys(Item_GObj* gobj) {}

bool itBombhei_UnkMotion12_Coll(Item_GObj* gobj)
{
    it_8026E8C4(gobj, fn_8027DAC8, it_8027DE18);
    return false;
}

bool it_3F14_Logic6_Clanked(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.bombhei.xDDC == 0) {
        it_80280B60(gobj);
    }
    return false;
}

bool it_3F14_Logic6_Reflected(Item_GObj* gobj)
{
    return it_80273030(gobj);
}

/// #it_3F14_Logic6_HitShield

/// #it_3F14_Logic6_ShieldBounced

void it_3F14_Logic6_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
