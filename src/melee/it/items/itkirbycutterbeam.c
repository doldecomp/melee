#include "itkirbycutterbeam.h"

#include "db/db.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "it/types.h"

#include <placeholder.h>
#include <platform.h>

void it_8029BAB8(HSD_GObj* gobj, Vec3* pos, float facing_dir)
{
    Item_GObj* spawned_gobj;

    SpawnItem spawn;
    pos->z = 0.0f;
    spawn.kind = It_Kind_Kirby_CBeam;
    spawn.prev_pos = *pos;
    it_8026BB68(gobj, &spawn.pos);
    spawn.facing_dir = facing_dir;
    spawn.x3C_damage = 0;
    spawn.vel.x = spawn.vel.y = spawn.vel.z = 0.0f;
    spawn.x0_parent_gobj = gobj;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x44_flag.b0 = true;
    spawn.x40 = 0;

    spawned_gobj = Item_80268B18(&spawn);
    if (spawned_gobj != NULL) {
        it_8029BB90(spawned_gobj, gobj);
        db_80225DD8(spawned_gobj, gobj);
        it_802750F8(spawned_gobj);
    }
}

/// #it_8029BB90

bool itKirbycutterbeam_UnkMotion0_Anim(Item_GObj* gobj)
{
    return it_80273130(gobj);
}

/// #itKirbycutterbeam_UnkMotion0_Phys

/// #itKirbycutterbeam_UnkMotion0_Coll

bool itKirbyCutterBeam_Logic7_DmgDealt(Item_GObj* arg0)
{
    return false;
}

bool itKirbyCutterBeam_Logic7_Clanked(Item_GObj* arg0)
{
    return true;
}

bool itKirbyCutterBeam_Logic7_Absorbed(Item_GObj* arg0)
{
    return true;
}

/// #it_2725_Logic7_Reflected

/// #it_2725_Logic7_ShieldBounced

bool itKirbyCutterBeam_Logic7_HitShield(Item_GObj* arg0)
{
    return true;
}

void it_8029C4B4(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
