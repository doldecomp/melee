#include "itclimbersblizzard.h"

#include <placeholder.h>
#include <platform.h>

#include "baselib/random.h"
#include "db/db.h"

#include "it/forward.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/itCharItems.h"
#include "it/item.h"

#include "it/items/forward.h"

#include <math.h>

#define M_TAU 6.283185307179586

#define GET_ATTRS(ip)                                                         \
    ((itClimbersBlizzardAttributes*)                                          \
         ip->xC4_article_data->x4_specialAttributes)

/* 2C2380 */ bool itClimbersBlizzard_UnkMotion0_Anim(Item_GObj* gobj);
/* 2C23B4 */ void itClimbersBlizzard_UnkMotion0_Phys(Item_GObj* gobj);
/* 2C23D4 */ bool itClimbersBlizzard_UnkMotion0_Coll(Item_GObj* gobj);

ItemStateTable it_803F76A8[] = { { 0, itClimbersBlizzard_UnkMotion0_Anim,
                                   itClimbersBlizzard_UnkMotion0_Phys,
                                   itClimbersBlizzard_UnkMotion0_Coll } };

static inline Item_GObj* spawn_item_0z(Item_GObj* gobj, ItemKind kind,
                                       Vec3* pos, f32 facing_dir,
                                       SpawnItem* spawn)
{
    spawn->kind = kind;
    spawn->prev_pos = *pos;
    spawn->prev_pos.z = 0.0f;
    it_8026BB68(gobj, &spawn->pos);
    spawn->facing_dir = facing_dir;
    spawn->x3C_damage = 0;
    spawn->vel.x = spawn->vel.y = spawn->vel.z = 0.0f;
    spawn->x0_parent_gobj = gobj;
    spawn->x4_parent_gobj2 = spawn->x0_parent_gobj;
    spawn->x44_flag.b0 = true;
    spawn->x40 = 0;
    return Item_80268B18(spawn);
}

Item_GObj* itClimbersBlizzard_Spawn(Item_GObj* gobj, Vec3* pos, f32 facing_dir)
{
    SpawnItem spawn;
    Item_GObj* spawned;
    ItemAttr* attr;
    spawned = spawn_item_0z(gobj, It_Kind_IceClimber_Blizzard, pos, facing_dir,
                            &spawn);
    if (spawned != NULL) {
        Item* ip = GET_ITEM(spawned);
        ip->xDD4_itemVar.climbersblizzard.flag0 = 0;
        attr = ip->xCC_item_attr;
        ip->xDD4_itemVar.climbersblizzard.x0 = attr->x60_scale;
        itClimbersBlizzard_802C2248(spawned);
        db_80225DD8(spawned, gobj);
        it_8026B3A8(spawned);
        it_802750F8(spawned);
    }
    return spawned;
}

void itClimbersBlizzard_802C2248(Item_GObj* gobj)
{
    Item* ip;
    f32 temp_f0;
    f32 var_f2;
    f32 var_f31;
    f32 rand;
    itClimbersBlizzardAttributes* attrs;

    ip = GET_ITEM(gobj);
    attrs = GET_ATTRS(ip);
    rand = HSD_Randf();
    var_f2 = attrs->x10 - attrs->xC;
    temp_f0 = (var_f2 * rand) + attrs->xC;
    if (ip->facing_dir == 1.0f) {
        var_f2 = temp_f0;
    } else {
        var_f2 = -temp_f0;
    }
    var_f31 = var_f2 - M_PI_2;
    while (var_f31 < 0.0f) {
        var_f31 += M_TAU;
    }
    while (var_f31 > M_TAU) {
        var_f31 -= M_TAU;
    }
    ip->x40_vel.x = attrs->x4 * cosf(var_f31);
    ip->x40_vel.y = attrs->x4 * sinf(var_f31);
    ip->x40_vel.z = 0.0f;
    it_80275158(gobj, attrs->x0);
    ip->xDD4_itemVar.climbersblizzard.flag0 = 1;
    itClimbersBlizzard_802C2358(gobj);
}

void itClimbersBlizzard_802C2358(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
}

bool itClimbersBlizzard_UnkMotion0_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xD44_lifeTimer <= 0.0f) {
        return true;
    }
    ip->xD44_lifeTimer -= 1.0F;
    return false;
}

void itClimbersBlizzard_UnkMotion0_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itClimbersBlizzardAttributes* attrs = GET_ATTRS(ip);
    ip->x40_vel.y += attrs->x8;
}

bool itClimbersBlizzard_UnkMotion0_Coll(Item_GObj* gobj)
{
    s32 flags = 0;
    it_8026D9A0(gobj);
    flags |= it_80276308(gobj);
    flags |= it_802763E0(gobj);
    return flags;
}

bool itClimbersBlizzard_DmgDealt(Item_GObj* gobj)
{
    return true;
}

bool itClimbersBlizzard_Reflected(Item_GObj* gobj)
{
    return it_80273030(gobj);
}

bool itClimbersBlizzard_Clanked(Item_GObj* gobj)
{
    return true;
}

bool itClimbersBlizzard_HitShield(Item_GObj* gobj)
{
    return true;
}

bool itClimbersBlizzard_Absorbed(Item_GObj* gobj)
{
    return true;
}

bool itClimbersBlizzard_ShieldBounced(Item_GObj* gobj)
{
    return true;
}

void itClimbersBlizzard_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
