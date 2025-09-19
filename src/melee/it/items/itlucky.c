#include "itlucky.h"

#include <placeholder.h>
#include <platform.h>

#include "it/it_26B1.h"
#include "it/it_266F.h"
#include "it/it_2725.h"
#include "it/item.h"

/// #it_802D5050

/// #it_802D50F0

/// #it_802D5124

/// #it_802D51C8

/// #it_802D52E4

/// #it_802D533C

/// #it_802D53AC

void it_802D53F0(Item_GObj* gobj) {}

bool it_802D53F4(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_802D546C);
    return false;
}

/// #it_802D5420

/// #it_802D546C

bool itLucky_UnkMotion5_Anim(Item_GObj* gobj)
{
    return false;
}

/// #itLucky_UnkMotion5_Phys

bool itLucky_UnkMotion5_Coll(Item_GObj* gobj)
{
    it_8026E15C(gobj, it_802D50F0);
    return false;
}

bool itLucky_UnkMotion6_Anim(Item_GObj* gobj)
{
    return false;
}

/// #itLucky_UnkMotion6_Phys

/// #it_802D5560

bool it_802D55DC(Item_GObj* gobj)
{
    it_80279FF8(gobj);
    return false;
}

void it_802D5600(Item_GObj* gobj)
{
    it_8027A09C(gobj);
}

bool it_802D5620(Item_GObj* gobj)
{
    return it_8027A118(gobj, (void (*)(HSD_GObj*)) it_802D5420);
}

/// #it_802D5648

void it_802D56F0(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

/// #it_802D5710

/// #it_2725_Logic44_Spawned

/// #it_802D582C

/// #it_802D5884

void it_802D58BC(Item_GObj* gobj) {}

bool it_802D58C0(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_802D58EC);
    return false;
}

void it_802D58EC(HSD_GObj* gobj)
{
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
}

/// #itLucky_UnkMotion3_Anim

/// #itLucky_UnkMotion3_Phys

bool itLucky_UnkMotion3_Coll(Item_GObj* gobj)
{
    it_8026E15C(gobj, it_802D582C);
    return false;
}

void it_2725_Logic44_PickedUp(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
}

bool itLucky_UnkMotion2_Anim(Item_GObj* gobj)
{
    return false;
}

void itLucky_UnkMotion2_Phys(Item_GObj* gobj) {}

void it_2725_Logic44_Dropped(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 3, ITEM_ANIM_UPDATE);
}

void it_2725_Logic44_EnteredAir(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE);
}

/// #it_802D5A2C

void it_802D5A64(Item_GObj* gobj) {}

/// #it_802D5A68

void it_2725_Logic44_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
