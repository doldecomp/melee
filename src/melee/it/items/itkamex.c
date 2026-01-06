#include "itkamex.h"

#include <placeholder.h>
#include <platform.h>

#include "it/forward.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"

/// #it_802CA49C

void it_802CA534(void) {}

void it_802CA538(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

void it_802CA558(Item_GObj* gobj)
{
    PAD_STACK(8);
    it_80273454(gobj);
    it_802CA58C(gobj);
}

/// #it_802CA58C

/// #it_802CA5D8

/// #it_802CA618

/// #it_802CA654

/// #it_802CA6A0

/// #itKamex_UnkMotion1_Anim

/// #itKamex_UnkMotion1_Phys

/// #itKamex_UnkMotion1_Coll

/// #it_802CA8DC

/// #it_802CA938

bool itKamex_UnkMotion2_Anim(Item_GObj* gobj)
{
    if (it_80272C6C(gobj) == 0) {
        return true;
    }
    return false;
}

/// #itKamex_UnkMotion2_Phys

/// #itKamex_UnkMotion2_Coll

/// #it_802CAA40

bool itKamex_UnkMotion3_Anim(Item_GObj* gobj)
{
    it_80279FF8(gobj);
    return false;
}

void itKamex_UnkMotion3_Phys(Item_GObj* gobj)
{
    it_8027A09C(gobj);
}

bool itKamex_UnkMotion3_Coll(Item_GObj* gobj)
{
    return it_8027A118(gobj, (void (*)(HSD_GObj*)) it_802CA558);
}

/// #it_802CAB10

/// #it_2725_Logic31_Spawned

bool it_2725_Logic31_HitShield(Item_GObj* arg0)
{
    return true;
}

bool it_2725_Logic31_DmgDealt(Item_GObj* arg0)
{
    return false;
}

void it_2725_Logic31_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

/// #it_802CADF0

bool it_802CAE60(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (--ip->xD44_lifeTimer <= 0.0f) {
        return true;
    }
    return false;
}

/// #it_802CAE94

bool it_802CAFB4(Item_GObj* gobj)
{
    return it_8026DFB0(gobj);
}
