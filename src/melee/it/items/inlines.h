#ifndef MELEE_IT_ITEMS_INLINES_H
#define MELEE_IT_ITEMS_INLINES_H

#include "ef/efasync.h"
#include "ef/eflib.h"
#include "it/inlines.h"
#include "it/it_2725.h"
#include "it/itCharItems.h"
#include "it/item.h"
#include "it/items/itlinkhookshot.h"
#include "it/itmaplib.h"
#include "it/types.h"

#include <math.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>
#include <MSL/math.h>

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

static inline void Item_InitSpawn(SpawnItem* spawn, HSD_GObj* parent,
                                  Vec3* pos, f32 dir)
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

static inline void Item_EnterAirStateWithHitlag(Item_GObj* gobj, enum_t msid)
{
    Item* item = GET_ITEM(gobj);
    it_802762BC(item);
    Item_80268E5C(gobj, msid, ITEM_ANIM_UPDATE);
    item->entered_hitlag = efLib_PauseAll;
    item->exited_hitlag = efLib_ResumeAll;
}

static inline void Item_EnterAirStateWithHitlagAndStateDesc(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    it_802762BC(item);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    item->entered_hitlag = efLib_PauseAll;
    item->exited_hitlag = efLib_ResumeAll;
    it_80273670(gobj, 0, 0.0F);
}

static inline void Item_UpdateRollingShellRotation(Item_GObj* gobj, Item* ip,
                                                   HSD_JObj* jobj,
                                                   const f32* rotation_rate)
{
    it_80276CB8(gobj);
    jobj = HSD_JObjGetChild(jobj);
    HSD_JObjAddRotationY(jobj, *rotation_rate * ABS(ip->x40_vel.x));
}

static inline void Item_ClampAngle(f32* angle)
{
    while (*angle < -M_PI) {
        *angle += M_TAU;
    }
    while (*angle > M_PI) {
        *angle -= M_TAU;
    }
}

static inline void Item_ClampAngleReverse(f32* angle)
{
    while (*angle > M_PI) {
        *angle -= M_TAU;
    }
    while (*angle < -M_PI) {
        *angle += M_TAU;
    }
}

static inline void itUpdateVelocityFromBone(HSD_JObj* jobj, Item* ip,
                                            Vec3* previous_pos)
{
    Vec3 pos;
    Vec3 zero;

    if (jobj != NULL) {
        zero.x = zero.y = zero.z = 0.0F;
        HSD_JObjGetTranslation(jobj, &pos);
        ip->x40_vel.x = ip->facing_dir * (pos.z - previous_pos->z);
        ip->x40_vel.y = pos.y - previous_pos->y;
        ip->x40_vel.z = pos.x - previous_pos->x;
        *previous_pos = pos;
        HSD_JObjSetTranslate(jobj, &zero);
    }
}

static inline bool itReflectItemAndUpdateRotation(Item_GObj* gobj)
{
    const f32 PI_2 = M_PI / 2;
    Item* ip = (Item*) HSD_GObjGetUserData(gobj);
    HSD_JObj* jobj = (HSD_JObj*) HSD_GObjGetHSDObj(gobj);

    it_80273030(gobj);
    HSD_JObjSetRotationY(jobj, PI_2 * ip->facing_dir);
    return false;
}

static inline void Item_InitSpawnOnPlane(SpawnItem* spawn, HSD_GObj* parent,
                                         Vec3* pos, f32 dir)
{
    spawn->prev_pos = *pos;
    spawn->prev_pos.z = 0.0F;
    spawn->pos = spawn->prev_pos;
    spawn->facing_dir = dir;
    spawn->x3C_damage = 0;
    spawn->vel.x = spawn->vel.y = spawn->vel.z = 0.0F;
    spawn->x0_parent_gobj = parent;
    spawn->x4_parent_gobj2 = spawn->x0_parent_gobj;
    spawn->x44_flag.b0 = true;
    spawn->x40 = 0;
}

static inline void Item_InitSpawnOnPlaneNoInitialCollision(SpawnItem* spawn,
                                                           HSD_GObj* parent,
                                                           Vec3* pos, f32 dir)
{
    spawn->prev_pos = *pos;
    spawn->prev_pos.z = 0.0F;
    spawn->pos = spawn->prev_pos;
    spawn->facing_dir = dir;
    spawn->x3C_damage = 0;
    spawn->vel.x = spawn->vel.y = spawn->vel.z = 0.0F;
    spawn->x0_parent_gobj = parent;
    spawn->x4_parent_gobj2 = spawn->x0_parent_gobj;
    spawn->x44_flag.b0 = false;
    spawn->x40 = 0;
}

#endif
