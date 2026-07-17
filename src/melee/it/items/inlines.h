#ifndef MELEE_IT_ITEMS_INLINES_H
#define MELEE_IT_ITEMS_INLINES_H

#include "it/itmaplib.h"
#include "it/types.h"

#include <baselib/jobj.h>
#include <MSL/math.h>

static inline void itGamewatch_InitSpawnItem(SpawnItem* spawn,
                                             HSD_GObj* parent, Vec3* pos,
                                             f32 dir)
{
    spawn->prev_pos = *pos;
    spawn->pos = spawn->prev_pos;
    spawn->facing_dir = dir;
    spawn->x3C_damage = 0;
    spawn->vel.x = spawn->vel.y = spawn->vel.z = 0.0F;
    spawn->x0_parent_gobj = parent;
    spawn->x4_parent_gobj2 = spawn->x0_parent_gobj;
    spawn->x44_flag.b0 = true;
    spawn->x40 = 0;
}

static inline void Item_UpdateRollingShellRotation(Item_GObj* gobj, Item* ip,
                                                   HSD_JObj* jobj,
                                                   const f32* rotation_rate)
{
    it_80276CB8(gobj);
    jobj = HSD_JObjGetChild(jobj);
    HSD_JObjAddRotationY(jobj, *rotation_rate * ABS(ip->x40_vel.x));
}

#endif
