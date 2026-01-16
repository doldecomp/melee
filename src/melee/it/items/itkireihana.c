#include "itkireihana.h"

#include <placeholder.h>
#include <platform.h>

#include "ef/eflib.h"
#include "it/inlines.h"
#include "it/item.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"

/// #it_2725_Logic15_Spawned

void it_2725_Logic15_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

bool itKireihana_UnkMotion2_Coll(Item_GObj* gobj)
{
    it_8026E248(gobj, it_802D01A0);
    return false;
}

bool itKireihana_UnkMotion4_Coll(Item_GObj* gobj)
{
    it_8026E248(gobj, it_802D062C);
    return false;
}

void itKireihana_UnkMotion3_Phys(Item_GObj* gobj)
{
    it_8027A344(gobj);
}

bool itKireihana_UnkMotion0_Anim(Item_GObj* gobj)
{
    it_80279FF8(gobj);
    return false;
}

void itKireihana_UnkMotion0_Phys(Item_GObj* gobj)
{
    it_8027A09C(gobj);
}

void itKireihana_UnkMotion0_Coll(Item_GObj* gobj)
{
    it_8027A118(gobj, it_802D0138);
}

void it_802D0774(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
}

void it_802D07C0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    Item_80268E5C(gobj, 4, 0x11);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
}
