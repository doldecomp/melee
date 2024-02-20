#include "itmariofireball.h"

#include "db/db_2253.h"
#include "ef/efasync.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/itCommonItems.h"
#include "it/item.h"

#include <common_structs.h>
#include <dolphin/mtx/vec.h>
#include <baselib/gobj.h>

void it_8029B6F8(Item_GObj* gobj, Vec3* pos, ItemKind kind, float facing_dir)
{
    Item_GObj* spawned_gobj;

    SpawnItem spawn_item;
    spawn_item.kind = kind;
    spawn_item.prev_pos = *pos;
    spawn_item.prev_pos.z = 0.0f;
    it_8026BB68(gobj, &spawn_item.pos);
    spawn_item.facing_dir = facing_dir;
    spawn_item.x3C_damage = 0;
    spawn_item.vel.x = spawn_item.vel.y = spawn_item.vel.z = 0.0f;
    spawn_item.x0_parent_gobj = gobj;
    spawn_item.x4_parent_gobj2 = spawn_item.x0_parent_gobj;
    spawn_item.x44_flag.bits.b0 = true;
    spawn_item.x40 = 0;

    spawned_gobj = Item_80268B18(&spawn_item);
    it_802C027C(spawned_gobj);
    db_80225DD8(spawned_gobj, gobj);
    it_802750F8(spawned_gobj);
}
