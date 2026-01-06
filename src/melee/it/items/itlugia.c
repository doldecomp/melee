#include "itlugia.h"

#include <placeholder.h>
#include <platform.h>

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"

/// #it_2725_Logic17_Spawned

void it_802D14D0(void) {}

void it_2725_Logic17_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

/// #itLugia_UnkMotion1_Anim

void itLugia_UnkMotion1_Phys(Item_GObj* gobj)
{
    it_8027A344(gobj);
}

bool itLugia_UnkMotion1_Coll(Item_GObj* gobj)
{
    return false;
}

/// #it_802D1580

/// #itLugia_UnkMotion2_Anim

/// #itLugia_UnkMotion2_Phys

bool itLugia_UnkMotion2_Coll(Item_GObj* gobj)
{
    return false;
}

/// #it_802D16D4

/// #itLugia_UnkMotion3_Anim

/// #itLugia_UnkMotion3_Phys

bool itLugia_UnkMotion3_Coll(Item_GObj* gobj)
{
    return false;
}

/// #it_802D1830

/// #itLugia_UnkMotion4_Anim

/// #itLugia_UnkMotion4_Phys

bool itLugia_UnkMotion4_Coll(Item_GObj* gobj)
{
    return false;
}

/// #it_802D1A44

/// #itLugia_UnkMotion5_Anim

void itLugia_UnkMotion5_Phys(Item_GObj* gobj)
{
    it_8027A344(gobj);
}

bool itLugia_UnkMotion5_Coll(Item_GObj* gobj)
{
    return false;
}

/// #it_802D1BBC

/// #it_802D1D40

bool it_802D1DB4(Item_GObj* gobj)
{
    it_80279FF8(gobj);
    return false;
}

/// #it_802D1DD8

bool it_802D1E64(Item_GObj* gobj)
{
    return it_8027A118(gobj, (void (*)(HSD_GObj*)) it_802D14D0);
}

/// #it_802D1E8C

/// #it_802D1F64

/// #it_802D208C

/// #it_2725_Logic39_Spawned

/// #it_2725_Logic40_Spawned

/// #it_2725_Logic41_Spawned

void it_802D23D4(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

/// #it_802D23F4

bool it_802D246C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xD44_lifeTimer <= 0.0f) {
        return true;
    }
    ip->xD44_lifeTimer -= 1.0f;
    return false;
}

/// #it_802D24A0

bool it_802D24FC(Item_GObj* gobj)
{
    return it_8026DA08(gobj);
}
