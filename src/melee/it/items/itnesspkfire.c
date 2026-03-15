#include "itnesspkfire.h"

#include <placeholder.h>
#include <platform.h>

#include "db/db.h"

#include "it/forward.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "it/items/itnesspkfirepillar.h"
#include "it/types.h"

#include <baselib/gobj.h>
#include <baselib/jobj.h>

void it_802AA054(Item_GObj* gobj, Vec3* pos, Vec3* vel, f32 facing_dir,
                 f32 angle)
{
    SpawnItem spawn;
    PAD_STACK(8);

    spawn.kind = It_Kind_Ness_PKFire;
    spawn.prev_pos = *pos;
    spawn.prev_pos.z = 0.0f;
    it_8026BB68(gobj, &spawn.pos);
    spawn.vel = *vel;
    spawn.facing_dir = facing_dir;
    spawn.x3C_damage = 0;
    spawn.x0_parent_gobj = gobj;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x44_flag.b0 = true;
    spawn.x40 = 0;

    {
        Item_GObj* fire = Item_80268B18(&spawn);
        if (fire != NULL) {
            HSD_JObj* jobj = GET_JOBJ(fire);
            db_80225DD8(fire, gobj);
            it_802AA1D8(fire);
            HSD_JObjSetRotationZ(jobj, angle);
        }
    }
}

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

bool it_2725_Logic23_DmgDealt(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itNessPKFirepillarAttributes* attrs =
        ip->xC4_article_data->x4_specialAttributes;
    Vec3 pos = ip->pos;
    pos.y += attrs->x4;
    itNesspkfirepillar_802AA494(gobj, ip->owner, &pos, ip->facing_dir);
    return true;
}

bool it_2725_Logic23_Clanked(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itNessPKFirepillarAttributes* attrs =
        ip->xC4_article_data->x4_specialAttributes;
    Vec3 pos = ip->pos;
    pos.y += attrs->x4;
    itNesspkfirepillar_802AA494(gobj, ip->owner, &pos, ip->facing_dir);
    return true;
}

bool itNessPKFire_Logic23_Absorbed(Item_GObj* arg0)
{
    return true;
}

bool itNessPKFire_Logic23_HitShield(Item_GObj* arg0)
{
    return true;
}

bool itNessPKFire_Logic23_Reflected(Item_GObj* gobj)
{
    return it_80273030(gobj);
}

bool it_2725_Logic23_ShieldBounced(Item_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    f32 rot_z = HSD_JObjGetRotationZ(jobj);
    HSD_JObjSetRotationZ(jobj, -rot_z);
    return itColl_BounceOffShield(gobj);
}

void it_802AA474(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
