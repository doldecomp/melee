#ifndef MELEE_IT_ITEMS_INLINES_H
#define MELEE_IT_ITEMS_INLINES_H

#include "it/types.h"

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

#endif
