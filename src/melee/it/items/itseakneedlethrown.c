#include "it/forward.h"

#include "itseakneedlethrown.h"

#include "it/inlines.h"
#include "it/it_26B1.h"

/// #it_802AFD8C

/// #it_802AFEA8

void it_802AFEF8(Item_GObj* gobj)
{
    GET_ITEM(gobj)->owner = NULL;
}

/// #it_802AFF08

/// #it_802B00F4

/// #it_802B0210

/// #it_802B024C

/// #it_802B033C

/// #it_802B0444

/// #it_802B0464

void it_802B0544(Item_GObj* gobj) {}

/// #it_802B0548

void it_802B057C(Item_GObj* gobj) {}

void it_802B0580(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itResetVelocity(ip);
}

/// #it_802B0598

/// #it_802B05CC

/// #it_802B0900

/// #it_802B0AB8

bool it_802B0C5C(Item_GObj* gobj)
{
    return false;
}

/// #it_802B0C64

/// #it_802B0D84

/// #it_802B0F34

/// #it_802B10E4

/// #it_802B1294

/// #it_802B14DC

/// #it_802B16E4

void it_802B1890(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
