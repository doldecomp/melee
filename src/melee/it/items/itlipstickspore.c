#include "itlipstickspore.h"

#include <placeholder.h>
#include <platform.h>

#include "db/db.h"
#include "ef/efsync.h"

#include "ft/forward.h"
#include "it/forward.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/itcoll.h"
#include "it/item.h"
#include "it/types.h"

#include <trigf.h>
#include <baselib/gobj.h>
#include <MSL/math.h>

/* 29A5F8 */ static bool itLipstickspore_UnkMotion1_Coll(Item_GObj* gobj);

ItemStateTable it_803F6680[] = {
    {
        0,
        itLipstickspore_UnkMotion0_Anim,
        itLipstickspore_UnkMotion0_Phys,
        itLipstickspore_UnkMotion0_Coll,
    },
    {
        1,
        itLipstickspore_UnkMotion1_Anim,
        itLipstickspore_UnkMotion1_Phys,
        itLipstickspore_UnkMotion1_Coll,
    },
};

void it_8029A114(Fighter_GObj* gobj, Vec3* pos, f32 facing_dir, s32 arg4)
{
    Item_GObj* item_gobj;
    SpawnItem spawn;
    PAD_STACK(8);

    spawn.kind = 0x25;
    spawn.prev_pos = *pos;
    spawn.prev_pos.z = 0.0f;
    it_8026BB68(gobj, &spawn.pos);
    spawn.facing_dir = facing_dir;
    spawn.x3C_damage = 0;
    spawn.vel.x = spawn.vel.y = spawn.vel.z = 0.0f;
    spawn.x0_parent_gobj = gobj;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x44_flag.b0 = 1;
    spawn.x40 = 0;
    item_gobj = Item_80268B18(&spawn);
    if (item_gobj != NULL) {
        Item* ip = item_gobj->user_data;
        ip->xDD4_itemVar.lipstickspore.xDD4 = arg4;
        it_8029A31C(item_gobj, gobj, ip);
        db_80225DD8(item_gobj, gobj);
        efSync_Spawn(0x440, item_gobj, pos, &facing_dir);
    }
}

void it_8029A218(HSD_GObj* owner, Vec3* pos, f32 facing_dir, s32 arg4)
{
    SpawnItem spawn;
    Item_GObj* item_gobj;

    spawn.kind = 0x25;
    spawn.prev_pos = *pos;
    spawn.prev_pos.z = 0.0f;
    it_8026BB68(owner, &spawn.pos);
    spawn.facing_dir = facing_dir;
    spawn.x3C_damage = 0;
    spawn.vel.z = 0.0f;
    spawn.vel.y = 0.0f;
    spawn.vel.x = 0.0f;
    spawn.x0_parent_gobj = owner;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x44_flag.b0 = 1;
    spawn.x40 = 0;
    item_gobj = Item_80268B18(&spawn);
    if (item_gobj != NULL) {
        Item* ip = GET_ITEM(item_gobj);
        ip->xDD4_itemVar.lipstickspore.xDD4 = arg4;
        it_8029A498(item_gobj, owner);
        db_80225DD8(item_gobj, owner);
        efSync_Spawn(0x441, item_gobj, pos, &facing_dir);
    }
}

void it_8029A31C(Item_GObj* gobj, Fighter_GObj* owner, Item* unused)
{
    Item* ip = GET_ITEM(gobj);
    itLipstickSporeAttributes* attr =
        ip->xC4_article_data->x4_specialAttributes;
    HitCapsule* hit;

    it_8026B3A8(gobj);
    it_80274740(gobj);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    hit = &ip->x5D4_hitboxes[0].hit;

    switch (ip->xDD4_itemVar.lipstickspore.xDD4) {
    case 0:
        it_80275158(gobj, attr->x10);
        ip->x40_vel.x = ip->facing_dir * (attr->x0 * attr->x8);
        ip->xDD4_itemVar.lipstickspore.xDD8 = ABS(ip->x40_vel.x / attr->x10);
        it_80272460(hit, attr->x18, gobj);
        break;
    case 1:
        it_80275158(gobj, attr->xC);
        ip->x40_vel.x = ip->facing_dir * (attr->x0 * attr->x4);
        ip->xDD4_itemVar.lipstickspore.xDD8 = ABS(ip->x40_vel.x / attr->xC);
        it_80272460(hit, attr->x14, gobj);
        break;
    case 2:
        it_80275158(gobj, attr->xC);
        ip->x40_vel.x = 0.0f;
        ip->xDD4_itemVar.lipstickspore.xDD8 = 0.0f;
        it_80272460(hit, attr->x14, gobj);
        break;
    }
    ip->xDCE_flag.b7 = false;
}

void it_8029A498(Item_GObj* gobj, Fighter_GObj* owner)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(8);

    it_8026B3A8(gobj);
    it_80274740(gobj);
    it_80275158(gobj, 5.0f);
    Item_80268E5C(gobj, 1, 2);

    ip->xDCE_flag.b7 = false;
}

bool itLipstickspore_UnkMotion0_Anim(Item_GObj* gobj)
{
    return it_80273130(gobj);
}

void itLipstickspore_UnkMotion0_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    if (ip->x40_vel.x == 0.0f) {
        return;
    }

    if (ip->xDD4_itemVar.lipstickspore.xDD8 == 0.0f) {
        return;
    }

    if (ip->x40_vel.x > 0.0f) {
        ip->x40_vel.x -= ip->xDD4_itemVar.lipstickspore.xDD8;
    } else {
        ip->x40_vel.x += ip->xDD4_itemVar.lipstickspore.xDD8;
    }

    {
        f32 abs_vel = ip->x40_vel.x;
        if (abs_vel < 0.0f) {
            abs_vel = -abs_vel;
        }
        if (abs_vel < ip->xDD4_itemVar.lipstickspore.xDD8) {
            ip->x40_vel.x = 0.0f;
        }
    }
}

bool itLipstickspore_UnkMotion0_Coll(Item_GObj* gobj)
{
    if (it_8026DFB0(gobj)) {
        return true;
    }
    return false;
}

bool itLipstickspore_UnkMotion1_Anim(Item_GObj* gobj)
{
    return it_80273130(gobj);
}

void itLipstickspore_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itResetVelocity(ip);
}

bool itLipstickspore_UnkMotion1_Coll(Item_GObj* gobj)
{
    return false;
}

bool itLipstickSpore_Logic37_DmgDealt(Item_GObj* arg0)
{
    return true;
}

bool itLipstickSpore_Logic37_Clanked(Item_GObj* arg0)
{
    return true;
}

bool itLipstickSpore_Logic37_HitShield(Item_GObj* arg0)
{
    return true;
}

bool itLipstickSpore_Logic37_Absorbed(Item_GObj* arg0)
{
    return true;
}

bool itLipstickSpore_Logic37_Reflected(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = gobj->hsd_obj;
    PAD_STACK(8);
    it_80273030(gobj);
    HSD_JObjSetRotationZ(jobj, atan2f(ip->x40_vel.y, ip->x40_vel.x));
    return false;
}

bool itLipstickSpore_Logic37_ShieldBounced(Item_GObj* gobj)
{
    itColl_BounceOffShield(gobj);
    return false;
}

void itLipstickSpore_Logic37_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
