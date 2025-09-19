#include "itsscope.h"

#include <placeholder.h>
#include <platform.h>

#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"

#define GET_ATTRS(ip)                                                         \
    ((itSScopeAttributes*) (ip)->xC4_article_data->x4_specialAttributes)

/// #it_80291BE0

/// #it_3F14_Logic21_Spawned

itSScopeAttributes* it_80291CCC(Item_GObj* gobj, Vec3* pos)
{
    Item* ip = GET_ITEM(gobj);
    itSScopeAttributes* attrs = GET_ATTRS(ip);
    pos->x = attrs->x34.x;
    pos->y = attrs->x34.y;
    pos->z = attrs->x34.z;
    return attrs;
}

/// #it_80291CF4

/// #it_80291D38

/// #it_80291DAC

/// #it_80291F14

/// #it_80291FA8

/// #it_80292030

bool itSscope_UnkMotion0_Anim(Item_GObj* gobj)
{
    return false;
}

void itSscope_UnkMotion0_Phys(Item_GObj* gobj) {}

/// #itSscope_UnkMotion0_Coll

void it_802920B8(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
}

bool itSscope_UnkMotion3_Anim(Item_GObj* gobj)
{
    return false;
}

/// #itSscope_UnkMotion1_Phys

/// #itSscope_UnkMotion3_Coll

void it_3F14_Logic21_PickedUp(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
}

bool itSscope_UnkMotion2_Anim(Item_GObj* gobj)
{
    return false;
}

void itSscope_UnkMotion2_Phys(Item_GObj* gobj) {}

void it_3F14_Logic21_Dropped(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 3, 6);
}

void it_3F14_Logic21_Thrown(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 3, 6);
}

/// #itSscope_UnkMotion3_Phys

bool it_3F14_Logic21_DmgDealt(Item_GObj* gobj)
{
    itColl_BounceOffVictim(gobj);
    return false;
}

bool it_3F14_Logic21_Clanked(Item_GObj* gobj)
{
    itColl_BounceOffVictim(gobj);
    return false;
}

bool it_3F14_Logic21_HitShield(Item_GObj* gobj)
{
    itColl_BounceOffVictim(gobj);
    return false;
}

/// #it_3F14_Logic21_Reflected

bool it_3F14_Logic21_Reflected(Item_GObj* gobj)
{
    return it_80273030(gobj);
}

/// #it_3F14_Logic21_ShieldBounced

bool it_3F14_Logic21_ShieldBounced(Item_GObj* gobj)
{
    return itColl_BounceOffShield(gobj);
}

void it_3F14_Logic21_EnteredAir(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE);
}

bool itSscope_UnkMotion4_Anim(Item_GObj* gobj)
{
    return false;
}

void itSscope_UnkMotion4_Phys(Item_GObj* gobj) {}

/// #itSscope_UnkMotion4_Coll

void it_3F14_Logic21_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
