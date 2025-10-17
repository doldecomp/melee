#include "itlizardon.h"

#include <placeholder.h>
#include <platform.h>

#include "it/forward.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"

/// #it_802CB8AC

void it_802CB93C(void) {}

void it_802CB940(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

s32 it_802CB960(Item_GObj* gobj)
{
    it_80273454(gobj);
    return it_802CB994(gobj);
}

/// #it_802CB994

/// #itLizardon_UnkMotion1_Anim

void itLizardon_UnkMotion1_Phys(Item_GObj* gobj)
{
    ItemAttr* ip_attr;
    Item* ip = GET_ITEM(gobj);

    if ((enum GroundOrAir) ip->ground_or_air == GA_Air) {
        ip_attr = ip->xCC_item_attr;
        it_80272860(gobj, ip_attr->x10_fall_speed,
                    ip_attr->x14_fall_speed_max);
    }
}

/// #itLizardon_UnkMotion1_Coll

/// #it_802CBAA8

/// #itLizardon_UnkMotion2_Anim

/// #itLizardon_UnkMotion2_Phys

/// #itLizardon_UnkMotion2_Coll

/// #it_802CBD24

/// #it_802CBFE4

bool itLizardon_UnkMotion3_Anim(Item_GObj* gobj)
{
    if (it_80272C6C(gobj) == 0) {
        return true;
    }
    return false;
}

/// #itLizardon_UnkMotion3_Phys

/// #itLizardon_UnkMotion3_Coll

/// #it_802CC0EC

s32 it_802CC160(Item_GObj* gobj)
{
    it_80279FF8(gobj);
    return 0;
}

void it_802CC184(Item_GObj* gobj)
{
    it_8027A09C(gobj);
}

bool it_802CC1A4(Item_GObj* gobj)
{
    return it_8027A118(gobj, (void (*)(HSD_GObj*)) it_802CB960);
}

/// #it_802CC1CC

/// #it_2725_Logic34_Spawned

/// #it_2725_Logic35_Spawned

/// #it_2725_Logic36_Spawned

/// #it_2725_Logic37_Spawned

void it_2725_Logic37_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

bool it_2725_Logic37_Reflected(Item_GObj* gobj)
{
    return it_80273030(gobj);
}

bool it_2725_Logic37_HitShield(Item_GObj* arg0)
{
    return true;
}

bool it_2725_Logic37_Absorbed(Item_GObj* arg0)
{
    return true;
}

/// #it_802CC5D4

bool it_802CC650(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xD44_lifeTimer <= 0.0f) {
        return true;
    }
    ip->xD44_lifeTimer -= 1.0f;
    return false;
}

/// #it_802CC684

/// #it_802CC6C4

bool it_802CC6C4(Item_GObj* gobj)
{
    return it_8026DFB0(gobj);
}
