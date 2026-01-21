#include "itrshell.h"

#include "m2c_macros.h"

#include <placeholder.h>
#include <platform.h>

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"

/// #it_8028CFE0

/// #it_8028D090

/// #it_8028D100

/// #it_8028D26C

s32 it_8028D390(Item_GObj* gobj)
{
    // TODO: clean up with union
    Item* ip = GET_ITEM(gobj);
    s32* decp = &M2C_FIELD(ip, s32*, 0xDEC);
    s32 dec = *decp;

    *decp = dec - 1;
    if (*decp == 0) {
        M2C_FIELD(ip, s32*, 0xDF0) = 1;
    }
    return dec;
}

/// #it_8028D3B8

/// #fn_8028D4A8

/// #it_8028D4E4

f32 it_8028D56C(Item_GObj* gobj, f32 f1, f32 f2)
{
    itRshellAttributes* attrs =
        GET_ITEM(gobj)->xC4_article_data->x4_specialAttributes;
    f32 f = (f1 * -attrs->x14.x) + (-attrs->x14.y * f2);
    return f * attrs->x14.z;
}

/// #it_3F14_Logic15_Spawned

/// #it_8028D62C

bool itRshell_UnkMotion0_Anim(Item_GObj* gobj)
{
    return false;
}

void itRshell_UnkMotion0_Phys(Item_GObj* gobj) {}

/// #itRshell_UnkMotion0_Coll

void it_8028D7F0(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
}

bool itRshell_UnkMotion1_Anim(Item_GObj* gobj)
{
    return false;
}

void itRshell_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itRshell_UnkMotion1_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.rshell.xDE8 != 0) {
        it_8026E32C(gobj, it_8028D62C);
    } else {
        return it_8026DF34(gobj);
    }
    return false;
}

void it_3F14_Logic15_PickedUp(Item_GObj* gobj)
{
    PAD_STACK(8);
    it_80275474(gobj);
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
}

bool itRshell_UnkMotion2_Anim(Item_GObj* gobj)
{
    return false;
}

void itRshell_UnkMotion2_Phys(Item_GObj* gobj) {}

/// #it_3F14_Logic15_Thrown

/// #itRshell_UnkMotion3_Anim

void itRshell_UnkMotion3_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itRshell_UnkMotion3_Coll(Item_GObj* gobj)
{
    it_8026E414(gobj, it_8028D090);
    return false;
}

/// #it_3F14_Logic15_Dropped

/// #itRshell_UnkMotion4_Anim

void itRshell_UnkMotion4_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itRshell_UnkMotion4_Coll(Item_GObj* gobj)
{
    it_8026E414(gobj, it_8028D090);
    return false;
}

/// #it_8028DAE4

/// #itRshell_UnkMotion5_Anim

/// #itRshell_UnkMotion5_Phys

/// #itRshell_UnkMotion5_Coll

/// #it_8028E170

/// #itRshell_UnkMotion6_Anim

void itRshell_UnkMotion6_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itRshell_UnkMotion6_Coll(Item_GObj* gobj)
{
    it_8026E414(gobj, it_8028D090);
    return false;
}

/// #it_3F14_Logic15_EnteredAir

bool itRshell_UnkMotion7_Anim(Item_GObj* gobj)
{
    return false;
}

void itRshell_UnkMotion7_Phys(Item_GObj* gobj) {}

/// #itRshell_UnkMotion7_Coll

/// #it_3F14_Logic15_DmgDealt

/// #it_3F14_Logic15_DmgReceived

bool it_3F14_Logic15_Reflected(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_80273030(gobj);
    ip->xDD4_itemVar.rshell.xDD4 = ip->xD48_halfLifeTimer;
    return false;
}

bool it_3F14_Logic15_Clanked(Item_GObj* gobj)
{
    itColl_BounceOffVictim(gobj);
    return false;
}

/// #it_3F14_Logic15_HitShield

bool it_3F14_Logic15_ShieldBounced(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->msid == 3 || ip->msid == 4) {
        itColl_BounceOffShield(gobj);
    }
    return false;
}

/// #it_8028E6C0

void it_3F14_Logic15_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
