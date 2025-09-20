#include "itoldottosea.h"

#include <placeholder.h>
#include <platform.h>

#include "it/inlines.h"
#include "it/it_2725.h"

/// #it_802E2470

/// #it_2725_Logic8_DmgReceived

/// #it_802E269C

/// #itOldottosea_UnkMotion0_Anim

/// #itOldottosea_UnkMotion0_Phys

/// #itOldottosea_UnkMotion0_Coll

/// #it_802E27B4

/// #itOldottosea_UnkMotion2_Anim

/// #itOldottosea_UnkMotion2_Phys

/// #itOldottosea_UnkMotion2_Coll

/// #it_802E2BC0

bool itOldottosea_UnkMotion4_Anim(Item_GObj* gobj)
{
    return false;
}

void itOldottosea_UnkMotion4_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

/// #itOldottosea_UnkMotion4_Coll

/// #it_802E2C80

/// #itOldottosea_UnkMotion5_Anim

void itOldottosea_UnkMotion5_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->ground_or_air == GA_Air) {
        ip->x40_vel.y -= ip->xCC_item_attr->x10_fall_speed;
    }
}

/// #itOldottosea_UnkMotion5_Coll

/// #it_802E2DF4

/// #it_802E2E30

/// #itOldottosea_UnkMotion7_Anim

/// #itOldottosea_UnkMotion7_Phys

/// #itOldottosea_UnkMotion7_Coll

/// #it_802E3098

/// #itOldottosea_UnkMotion3_Anim

void itOldottosea_UnkMotion3_Phys(Item_GObj* gobj) {}

/// #itOldottosea_UnkMotion3_Coll
