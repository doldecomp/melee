#include "ithouou.h"

#include <placeholder.h>
#include <platform.h>

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"

/// #it_2725_Logic18_Spawned

void it_802D25B8(void) {}

void it_802D25BC(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

/// #itHouou_UnkMotion1_Anim

void itHouou_UnkMotion1_Phys(Item_GObj* gobj)
{
    it_8027A344(gobj);
}

bool itHouou_UnkMotion1_Coll(Item_GObj* gobj)
{
    return false;
}

/// #it_802D2668

/// #itHouou_UnkMotion2_Anim

/// #itHouou_UnkMotion2_Phys

bool itHouou_UnkMotion2_Coll(Item_GObj* gobj)
{
    return false;
}

/// #it_802D27B0

/// #itHouou_UnkMotion3_Anim

/// #itHouou_UnkMotion3_Phys

bool itHouou_UnkMotion3_Coll(Item_GObj* gobj)
{
    return false;
}

/// #it_802D290C

/// #itHouou_UnkMotion4_Anim

/// #itHouou_UnkMotion4_Phys

bool itHouou_UnkMotion4_Coll(Item_GObj* gobj)
{
    return false;
}

/// #it_802D2A58

/// #itHouou_UnkMotion5_Anim

void itHouou_UnkMotion5_Phys(Item_GObj* gobj)
{
    it_8027A344(gobj);
}

bool itHouou_UnkMotion5_Coll(Item_GObj* gobj)
{
    return false;
}

/// #it_802D2B4C

/// #it_802D2BE0

bool it_802D2C54(Item_GObj* gobj)
{
    it_80279FF8(gobj);
    return false;
}

/// #it_802D2C78

bool it_802D2D04(Item_GObj* gobj)
{
    return it_8027A118(gobj, (void (*)(HSD_GObj*)) it_802D25B8);
}

/// #it_802D2D2C

/// #it_2725_Logic42_Spawned

void it_802D2ED0(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

/// #it_802D2EF0

bool it_802D2F3C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xD44_lifeTimer <= 0.0f) {
        return true;
    }
    ip->xD44_lifeTimer -= 1.0f;
    return false;
}

/// #it_802D2F70

bool it_802D2FE8(Item_GObj* gobj)
{
    return it_8026DA08(gobj);
}
