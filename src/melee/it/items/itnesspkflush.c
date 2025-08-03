#include "it/forward.h"

#include "itnesspkflush.h"

#include "it/inlines.h"
#include "it/it_26B1.h"

/* 2AB29C */ static bool it_802AB29C(Item_GObj* gobj);
/* 2AB2A4 */ static bool it_802AB2A4(Item_GObj* gobj);

Fighter_GObj* it_802AA7E4(Item_GObj* gobj)
{
    return GET_ITEM(gobj)->owner;
}

bool it_802AA7F0(Item_GObj* gobj)
{
    Item* it = GET_ITEM(gobj);
    if (it->msid == 0x2) {
        return 1;
    }
    return 0;
}

/// #it_802AA810

/// #it_802AA8C0

/// #it_802AA9CC

/// #it_802AAA50

/// #it_802AAA80

/// #it_802AAB70

/// #it_802AAD48

/// #it_802AAEE4

/// #it_802AAFDC

void it_802AB128(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itResetVelocity(ip);
}

void it_802AB140(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itResetVelocity(ip);
}

/// #it_802AB158

bool it_802AB29C(Item_GObj* gobj)
{
    return false;
}

bool it_802AB2A4(Item_GObj* gobj)
{
    return false;
}

/// #it_802AB2AC

bool it_802AB3C0(Item_GObj* arg0)
{
    return true;
}

bool it_802AB3C8(Item_GObj* arg0)
{
    return true;
}

void it_802AB3D0(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
