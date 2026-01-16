#include "itfushigibana.h"

#include <placeholder.h>
#include <platform.h>

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_2725.h"
#include "ef/eflib.h"
#include "it/it_26B1.h"
#include "it/item.h"

/// #it_2725_Logic29_Spawned

/// #it_802D705C

void it_802D70A4(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_802762BC(ip);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
    it_80273670(gobj, 0, 0.0f);
    it_8026BDB4(gobj);
}

bool itFushigibana_UnkMotion0_Anim(Item_GObj* gobj)
{
    it_80279FF8(gobj);
    return false;
}

void itFushigibana_UnkMotion0_Phys(Item_GObj* gobj)
{
    it_8027A09C(gobj);
}

bool itFushigibana_UnkMotion0_Coll(Item_GObj* gobj)
{
    return it_8027A118(gobj, (void (*)(HSD_GObj*)) it_802D705C);
}

/// #it_802D718C

/// #itFushigibana_UnkMotion1_Anim

void itFushigibana_UnkMotion1_Phys(Item_GObj* gobj) {}

bool itFushigibana_UnkMotion1_Coll(Item_GObj* gobj)
{
    PAD_STACK(8);
    it_8026D62C(gobj, (HSD_GObjEvent) it_802D7328);
    it_80276CB8(gobj);
    return false;
}

/// #it_802D7328

bool itFushigibana_UnkMotion2_Anim(Item_GObj* gobj)
{
    return false;
}

void itFushigibana_UnkMotion2_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itFushigibana_UnkMotion2_Coll(Item_GObj* gobj)
{
    it_8026E15C(gobj, it_802D705C);
    return false;
}
