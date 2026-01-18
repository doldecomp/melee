#include "ithammerhead.h"

#include <placeholder.h>
#include <platform.h>

#include "it/forward.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"

/// #it_80299C48

void it_3F14_Logic40_Spawned(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itHammerheadAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
    it_80275158(gobj, attrs->x4);
}

/// #it_80299D7C

/// #it_3F14_Logic40_PickedUp

bool itHammerhead_UnkMotion1_Anim(Item_GObj* gobj)
{
    return false;
}

void itHammerhead_UnkMotion1_Phys(Item_GObj* gobj) {}

void it_3F14_Logic40_Dropped(Item_GObj* gobj)
{
    it_3F14_Logic40_Thrown(gobj);
}

/// #itHammerhead_UnkMotion2_Anim

void itHammerhead_UnkMotion2_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attr = ip->xCC_item_attr;
    it_80272860(gobj, attr->x10_fall_speed, attr->x14_fall_speed_max);
    it_80274658(gobj, it_804D6D28->x68_float);
}

bool itHammerhead_UnkMotion2_Coll(Item_GObj* gobj)
{
    it_8026E15C(gobj, it_80299F94);
    return false;
}

void it_80299F94(Item_GObj* gobj)
{
    it_80299FB4(gobj);
}

/// #it_80299FB4

/// #itHammerhead_UnkMotion3_Anim

void itHammerhead_UnkMotion3_Phys(Item_GObj* gobj) {}

bool itHammerhead_UnkMotion3_Coll(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_3F14_Logic40_Thrown);
    return false;
}

bool it_3F14_Logic40_DmgDealt(Item_GObj* arg0)
{
    return false;
}

bool it_3F14_Logic40_Clanked(Item_GObj* arg0)
{
    return false;
}

bool it_3F14_Logic40_HitShield(Item_GObj* arg0)
{
    return false;
}

bool it_3F14_Logic40_Reflected(Item_GObj* gobj)
{
    it_80273030(gobj);
    return false;
}

bool it_3F14_Logic40_DmgReceived(Item_GObj* arg0)
{
    return false;
}

void it_3F14_Logic40_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
