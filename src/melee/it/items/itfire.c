#include "itfire.h"

#include <placeholder.h>
#include <platform.h>

#include "ef/eflib.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"

/// #it_2725_Logic6_Spawned

void it_802CC740(void) {}

void it_2725_Logic6_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

bool itFire_UnkMotion1_Anim(Item_GObj* gobj)
{
    if (!it_80272C6C(gobj)) {
        it_802CC7D8(gobj);
    }
    return false;
}

void itFire_UnkMotion1_Phys(Item_GObj* gobj) {}

bool itFire_UnkMotion1_Coll(Item_GObj* gobj)
{
    it_8026E7E0(gobj, it_802CC7D4);
    return false;
}

void it_802CC7D4(Item_GObj* gobj) {}

void it_802CC7D8(Item_GObj* gobj) {}

/// #itFire_UnkMotion2_Anim

void itFire_UnkMotion2_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itFireAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
    ip->x40_vel.y += attrs->xC;
}

bool itFire_UnkMotion2_Coll(Item_GObj* gobj)
{
    return false;
}

/// #it_802CC944

bool itFire_UnkMotion0_Anim(Item_GObj* gobj)
{
    it_80279FF8(gobj);
    return false;
}

static void itFire_UnkMotion0_Phys_inline(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    Item_80268E5C(gobj, 1, 2);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
}

void itFire_UnkMotion0_Phys(Item_GObj* gobj)
{
    if (it_8027A09C(gobj)) {
        Item* ip = GET_ITEM(gobj);
        itFireAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
        it_8027ADEC(0x464, gobj, gobj->hsd_obj, 1.10000002384185791016);
        it_80273454(gobj);
        ip->x40_vel.y = attrs->x4;
        itFire_UnkMotion0_Phys_inline(gobj);
        ip->xDD1_flag.b1 = 1;
    }
}

bool itFire_UnkMotion0_Coll(Item_GObj* gobj)
{
    return it_8027A118(gobj, (void (*)(HSD_GObj*)) it_802CC740);
}
