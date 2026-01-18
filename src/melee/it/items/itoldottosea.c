#include "itoldottosea.h"

#include <placeholder.h>
#include <platform.h>

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_2725.h"
#include "it/itCommonItems.h"
#include "it/item.h"
#include "it/items/itwhitebea.h"

/// #it_802E2470

/// #it_2725_Logic8_DmgReceived

/// #it_802E269C

bool itOldottosea_UnkMotion0_Anim(Item_GObj* gobj)
{
    if (!it_80272C6C(gobj)) {
        Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    }
    return false;
}

/// #itOldottosea_UnkMotion0_Phys

bool itOldottosea_UnkMotion0_Coll(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_802E2BC0);
    return it_802E35CC(gobj);
}

/// #it_802E27B4

/// #itOldottosea_UnkMotion2_Anim

/// #itOldottosea_UnkMotion2_Phys

/// #itOldottosea_UnkMotion2_Coll

void it_802E2BC0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itOldottoseaAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    ip->xDD4_itemVar.oldottosea.x28 = 0;
    ip->x40_vel.x *= attr->x4;
    Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE);
}

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

bool itOldottosea_UnkMotion4_Coll(Item_GObj* gobj)
{
    it_8026E414(gobj, it_802E269C);
    return it_802E35CC(gobj);
}

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

bool itOldottosea_UnkMotion3_Coll(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_802E2BC0);
    return it_802E35CC(gobj);
}
