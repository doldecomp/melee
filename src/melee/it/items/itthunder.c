#include "itthunder.h"

#include <placeholder.h>
#include <platform.h>

#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "ef/eflib.h"
#include "it/inlines.h"
#include "it/item.h"

/// #it_2725_Logic7_Spawned

void it_802CCB10(Item_GObj* gobj) {}

void it_802CCB14(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

/// #itThunder_UnkMotion1_Anim

void itThunder_UnkMotion1_Phys(Item_GObj* gobj)
{
    it_8027A344(gobj);
}

bool itThunder_UnkMotion1_Coll(Item_GObj* gobj)
{
    it_8026E15C(gobj, it_802CCB10);
    return false;
}

/// #it_802CCBF8

/// #it_802CCC68

/// #itThunder_UnkMotion2_Anim

/// #itThunder_UnkMotion2_Phys

bool itThunder_UnkMotion2_Coll(Item_GObj* gobj)
{
    return false;
}

void it_802CCE28(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_802762BC(ip);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
    it_80273670(gobj, 0, 0.0f);
}

bool itThunder_UnkMotion0_Anim(Item_GObj* gobj)
{
    it_80279FF8(gobj);
    return false;
}

/// #itThunder_UnkMotion0_Phys

bool itThunder_UnkMotion0_Coll(Item_GObj* gobj)
{
    return it_8027A118(gobj, (void (*)(HSD_GObj*)) it_802CCB10);
}
