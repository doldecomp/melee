#ifndef MELEE_IT_ITEMS_INLINES_H
#define MELEE_IT_ITEMS_INLINES_H

#include "it/itCharItems.h"
#include "it/items/itlinkhookshot.h"
#include "it/types.h"

static inline void Item_RetractChain(ItemLink* link, Vec3* pos,
                                     f32 target_dist, const f32* max_dist,
                                     ItemLink** next_out, ItemLink** cur_out,
                                     f32* remaining_out)
{
    ItemLink* cur;
    ItemLink* next;
    f32 distance;
    f32 remaining;
    f32 limit;
    Vec3 dir;

    cur = link;
    next = link->prev;

    while (next != NULL && !cur->x2C_b0) {
        cur = next;
        next = next->prev;
    }

    distance = it_802A3C98(&cur->pos, pos, &dir);

    while (next != NULL && target_dist > distance) {
        cur->x2C_b0 = false;
        distance = it_802A3C98(&next->pos, pos, &dir);
        cur = next;
        next = next->prev;
    }

    remaining = distance - target_dist;
    limit = *max_dist;
    if (remaining > limit) {
        remaining = limit;
    }
    *next_out = next;
    *cur_out = cur;
    *remaining_out = remaining;
}

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
