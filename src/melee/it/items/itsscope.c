#include "itsscope.h"

#include <placeholder.h>
#include <platform.h>

#include "it/forward.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/itCommonItems.h"
#include "it/item.h"

#define GET_ATTRS(ip)                                                         \
    ((itSScopeAttributes*) (ip)->xC4_article_data->x4_specialAttributes)

HSD_GObj* it_80291BE0(Vec3* arg0)
{
    SpawnItem spawn;
    Item_GObj* gobj;

    spawn.kind = It_Kind_S_Scope;
    spawn.prev_pos = *arg0;
    spawn.pos = spawn.prev_pos;
    spawn.facing_dir = -1.0f;
    spawn.x3C_damage = 0;
    spawn.vel.x = spawn.vel.y = spawn.vel.z = 0.0f;
    spawn.x0_parent_gobj = NULL;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x44_flag.b0 = true;
    spawn.x40 = 0;
    gobj = Item_80268B5C(&spawn);
    if (gobj != NULL) {
        it_80292030(gobj);
    }
    return gobj;
}

void it_3F14_Logic21_Spawned(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xD4C = *(s32*) ip->xC4_article_data->x4_specialAttributes;
    it_802920B8(gobj);
}

itSScopeAttributes* it_80291CCC(Item_GObj* gobj, Vec3* pos)
{
    itSScopeAttributes* attrs = GET_ATTRS(GET_ITEM(gobj));
    pos->x = attrs->x34.x;
    pos->y = attrs->x34.y;
    pos->z = attrs->x34.z;
    return attrs;
}

s32 it_80291CF4(Item_GObj* gobj, s32 arg1)
{
    itSScopeAttributes* attrs = GET_ATTRS(GET_ITEM(gobj));

    if (arg1 <= attrs->x4) {
        return 0;
    }
    if (arg1 < attrs->x8 * 8) {
        return arg1 / 8;
    }
    return 9;
}

/// #it_80291DAC

/// #it_80291F14

/// #it_80291FA8

void it_80292030(Item_GObj* gobj)
{
    Item* temp_r4 = GET_ITEM(gobj);
    temp_r4->x40_vel.z = 0.0f;
    temp_r4->x40_vel.y = 0.0f;
    temp_r4->x40_vel.x = 0.0f;
    it_8026B390(gobj);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
}

bool itSscope_UnkMotion0_Anim(Item_GObj* gobj)
{
    return false;
}

void itSscope_UnkMotion0_Phys(Item_GObj* gobj) {}

bool itSscope_UnkMotion0_Coll(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_802920B8);
    return false;
}

void it_802920B8(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
}

bool itSscope_UnkMotion3_Anim(Item_GObj* gobj)
{
    return false;
}

void itSscope_UnkMotion1_Phys(Item_GObj* gobj)
{
    ItemAttr* attrs = (GET_ITEM(gobj))->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itSscope_UnkMotion3_Coll(Item_GObj* gobj)
{
    if ((GET_ITEM(gobj))->xD4C != 0) {
        it_8026E15C(gobj, (void (*)(HSD_GObj*)) it_80292030);
        return 0;
    }
    return it_8026DF34(gobj);
}

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

void itSscope_UnkMotion3_Phys(Item_GObj* gobj)
{
    ItemAttr* temp_r4 = (GET_ITEM(gobj))->xCC_item_attr;
    it_80272860(gobj, temp_r4->x10_fall_speed, temp_r4->x14_fall_speed_max);
    it_80274658(gobj, it_804D6D28->x68_float);
}

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

bool itSscope_UnkMotion4_Coll(Item_GObj* gobj)
{
    it_8026E8C4(gobj, it_80292030, it_802920B8);
    return false;
}

void it_3F14_Logic21_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
