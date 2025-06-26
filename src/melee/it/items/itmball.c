#include <platform.h>
#include <placeholder.h>

#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/itCommonItems.h"
#include "it/types.h"

#include <dolphin/mtx.h>
#include <melee/gr/ground.h>
#include <melee/it/item.h>
#include <melee/lb/lb_00B0.h>

void it_802978DC(Item_GObj* item_gobj)
{
    Item* it = GET_ITEM(item_gobj);
    if (!((it->xDD4_itemVar.chicorita._0[0] >> 6U) & 1)) {
        Item_804A0C64.x1C -= 1;
    }
}

// #it_80297904

void it_80297944(Item_GObj* arg0)
{
    Item* item = GET_ITEM(arg0);
    HSD_JObj* jobj = GET_JOBJ(arg0);
    it_8026B390(arg0);
    item->x40_vel.z = 0.0f;
    item->x40_vel.y = 0.0f;
    item->x40_vel.x = 0.0f;
    Item_80268E5C(arg0, 0, ITEM_ANIM_UPDATE);
}

bool it_8029799C(void)
{
    return false;
}

void it_802979A4(void) {}

/// #it_802979A8

/// #it_802979D4

bool it_80297A1C(void)
{
    return false;
}

/// #it_80297A24

/// #it_80297A54

/// #it_80297ABC

bool it_80297AE4(void)
{
    return false;
}

void it_80297AEC(void) {}

/// #it_80297AF0

/// #it_80297B18

/// #it_80297B40

/// #it_80297B8C

/// #it_80297BB8

/// #it_80297BF8

bool it_80297C84(void)
{
    return false;
}

void it_80297C8C(void) {}

/// #it_80297C90

/// #it_80297CC4

/// #it_80297DD8

/// #it_80297E28

void it_80297E5C(void) {}

/// #it_80297E60

/// #it_80297E8C

/// #it_80297F94

/// #it_80297FC8

/// #it_80297FF8

/// #it_80298060

/// #it_802980A0

s32 it_802980D4(Item_GObj* arg0)
{
    it_8026B3A8(arg0);
    it_802725D4(arg0);
    itColl_BounceOffVictim(arg0);
    return 0;
}

s32 it_80298114(Item_GObj* arg0)
{
    it_8026B3A8(arg0);
    return itColl_BounceOffShield(arg0);
}

void it_80298148(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
