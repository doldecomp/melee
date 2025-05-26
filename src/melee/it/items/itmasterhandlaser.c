#include <platform.h>
#include <placeholder.h>

#include "itmasterhandlaser.h"

#include "it/inlines.h"
#include "it/types.h"

#include <baselib/gobj.h>

/// #it_802F0340

/// #it_802F044C

void it_802F046C(Item_GObj* gobj)
{
    if (gobj != NULL) {
        GET_ITEM(gobj)->xDD4_itemVar.masterhandlaser.x0 = true;
    }
}

/// #it_802F0484

/// #it_802F04F0

void it_802F059C(void) {}

bool it_802F05A0(void)
{
    return false;
}

/// #it_802F05A8

/// #it_802F063C
