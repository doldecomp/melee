#ifndef MELEE_IT_ITEMS_INLINES_H
#define MELEE_IT_ITEMS_INLINES_H

#include "ef/efasync.h"
#include "it/inlines.h"
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

#define ITEM_SPAWN_SHELL_SPIN_EFFECT(gobj, reset_interval, offset, timer,     \
                                     pos, jobj, prepare_facing, facing_dir)   \
    do {                                                                      \
        (jobj) = GET_JOBJ(gobj);                                              \
        (pos) = (offset);                                                     \
        prepare_facing;                                                       \
        (pos).x *= (facing_dir);                                              \
        efAsync_Spawn((gobj), &GET_ITEM(gobj)->xBC0, 2, 1029, jobj, &(pos));  \
        (timer) = (reset_interval);                                           \
    } while (0)

static inline void Item_SpawnShellSpinEffect(Item_GObj* gobj,
                                             const f32* reset_interval,
                                             const Vec3* offset, Item* ip,
                                             f32* timer, Vec3* pos)
{
    HSD_JObj* jobj;

    ITEM_SPAWN_SHELL_SPIN_EFFECT(gobj, *reset_interval, *offset, *timer, *pos,
                                 jobj, (void) 0, -ip->facing_dir);
}

#endif
