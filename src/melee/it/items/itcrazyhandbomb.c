#include "itcrazyhandbomb.h"

#include <placeholder.h>
#include <platform.h>

#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/inlines.h"
#include "it/it_266F.h"

/// #it_802F0F6C

/// #it_802F1030

void itCrazyHandBomb_Logic86_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

bool itCrazyHandBomb_Logic86_DmgDealt(Item_GObj* gobj)
{
    it_802F1344();
    return 1;
}

bool itCrazyHandBomb_Logic86_Reflected(Item_GObj* gobj)
{
    return it_80273030(gobj);
}

/// #it_802F10F8

bool itCrazyhandbomb_UnkMotion0_Anim(Item_GObj* gobj)
{
    return false;
}

/// #itCrazyhandbomb_UnkMotion0_Phys

bool itCrazyhandbomb_UnkMotion0_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->ground_or_air == GA_Air) {
        it_8026E71C(gobj, it_802F1030);
    }
    return false;
}

void it_802F1340(void) {}

/// #it_802F1344

bool itCrazyhandbomb_UnkMotion1_Anim(Item_GObj* gobj)
{
    return it_802751D8(gobj);
}

void itCrazyhandbomb_UnkMotion1_Phys(Item_GObj* gobj) {}

bool itCrazyhandbomb_UnkMotion1_Coll(Item_GObj* gobj)
{
    return false;
}

void it_802F13B0(void) {}
