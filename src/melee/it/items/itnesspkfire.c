#include "itnesspkfire.h"

#include <placeholder.h>
#include <platform.h>

#include "it/forward.h"
#include "it/types.h"

#include <baselib/gobj.h>

#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/inlines.h"
#include "it/item.h"

/// #it_802AA054

void it_802AA1D8(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    itNessPKFirepillarAttributes* attrs =
        item->xC4_article_data->x4_specialAttributes;
    Item_80268E5C(item_gobj, 0, ITEM_ANIM_UPDATE);
    it_80275158(item_gobj, attrs->x0);
}

bool itNesspkfire_UnkMotion0_Anim(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    ip->xD44_lifeTimer--;
    if (ip->xD44_lifeTimer <= 0.0f) {
        return true;
    }
    return false;
}

bool itNesspkfire_UnkMotion0_Coll(Item_GObj* gobj)
{
    return it_8026E058(gobj);
}

/// #it_2725_Logic23_DmgDealt

/// #it_2725_Logic23_Clanked

bool it_2725_Logic23_Absorbed(Item_GObj* arg0)
{
    return true;
}

bool it_2725_Logic23_HitShield(Item_GObj* arg0)
{
    return true;
}

bool it_2725_Logic23_Reflected(Item_GObj* gobj)
{
    return it_80273030(gobj);
}

/// #it_2725_Logic23_ShieldBounced

void it_802AA474(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
