#ifndef MELEE_IT_ITEMS_INLINES_H
#define MELEE_IT_ITEMS_INLINES_H

#include <math.h>

#include <dolphin/mtx.h>
#include <melee/cm/camera.h>
#include <melee/db/db.h>
#include <melee/ef/eflib.h>
#include <melee/it/inlines.h>
#include <melee/it/it_26B1.h>
#include <melee/it/it_2725.h>
#include <melee/it/itCharItems.h>
#include <melee/it/item.h>
#include <melee/it/ithitbox.h>
#include <melee/it/itmaplib.h>
#include <melee/it/itzako.h>
#include <melee/it/kinds/itlinkhookshot.h>
#include <melee/it/types.h>
#include <melee/lb/lbvector.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/jobj.h>

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

static inline Item_GObj*
Item_AttachToParent(Item_GObj* item_gobj, HSD_GObj* parent, Fighter_Part part)
{
    Item_8026AB54(item_gobj, parent, part);
    db_80225DD8(item_gobj, parent);
    return item_gobj;
}

static inline void Item_AttachGameWatchArticle(HSD_GObj* parent,
                                               Fighter_Part part,
                                               Item_GObj* item_gobj,
                                               void** attributes)
{
    Item_AttachToParent(item_gobj, parent, part);
    it_8027CE64(item_gobj, parent, attributes[0]);
}

static inline void Item_StopAndEnterState(Item_GObj* gobj, Item* ip, s32 msid)
{
    itResetVelocity(ip);
    it_8026B390(gobj);
    Item_80268E5C(gobj, msid, ITEM_ANIM_UPDATE);
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

static inline bool Item_UpdateRayAnimation(Item_GObj* gobj, Item* ip,
                                           HSD_JObj* jobj,
                                           const f32* max_scale,
                                           f32 scale_divisor)
{
    f32 dir;
    f32 vel_x;

    ip->x40_vel.x =
        ip->xDD4_itemVar.ray.speed * cosf(ip->xDD4_itemVar.ray.angle);
    ip->x40_vel.y =
        ip->xDD4_itemVar.ray.speed * sinf(ip->xDD4_itemVar.ray.angle);
    ip->x40_vel.z = 0.0F;
    if (ip->x40_vel.x > 0.0F) {
        dir = +1.0F;
    } else {
        dir = -1.0F;
    }
    ip->facing_dir = dir;
    HSD_JObjSetRotationY(jobj, M_PI_2 * ip->facing_dir);
    if (ip->facing_dir == 1.0F) {
        vel_x = -ip->x40_vel.x;
    } else {
        vel_x = +ip->x40_vel.x;
    }
    HSD_JObjSetRotationX(jobj, M_PI + atan2f(ip->x40_vel.y, vel_x));
    ip->xDD4_itemVar.ray.scale +=
        ABS(ip->xDD4_itemVar.ray.speed) / scale_divisor;
    if (ip->xDD4_itemVar.ray.scale > *max_scale) {
        ip->xDD4_itemVar.ray.scale = *max_scale;
    }
    if (ip->xDD4_itemVar.ray.scale < 1e-5F) {
        ip->xDD4_itemVar.ray.scale = 1e-3F;
    }
    HSD_JObjSetScaleZ(jobj, ip->xDD4_itemVar.ray.scale);
    return it_80273130(gobj);
}

static inline bool Item_BounceRayOffShield(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    lbVector_Mirror(&ip->x40_vel, &ip->xC58);
    ip->xDD4_itemVar.ray.scale = 1e-3F;
    ip->xDD4_itemVar.ray.angle = atan2f(ip->x40_vel.y, ip->x40_vel.x);
    while (ip->xDD4_itemVar.ray.angle < 0.0F) {
        ip->xDD4_itemVar.ray.angle += M_TAU;
    }
    while (ip->xDD4_itemVar.ray.angle > M_TAU) {
        ip->xDD4_itemVar.ray.angle -= M_TAU;
    }
    return false;
}

static inline void Item_ResetRayAfterReflection(Item* ip, HSD_JObj* jobj)
{
    HSD_JObjSetScaleZ(jobj, ip->xDD4_itemVar.ray.scale = 1e-3F);
    ip->xDD4_itemVar.ray.angle += M_PI;
    while (ip->xDD4_itemVar.ray.angle < 0.0F) {
        ip->xDD4_itemVar.ray.angle += M_TAU;
    }
    while (ip->xDD4_itemVar.ray.angle > M_TAU) {
        ip->xDD4_itemVar.ray.angle -= M_TAU;
    }
}

static inline void Item_InitSpawnPosition(SpawnItem* spawn, Vec3* pos,
                                          bool on_plane)
{
    spawn->prev_pos = *pos;
    if (on_plane) {
        spawn->prev_pos.z = 0.0F;
    }
    spawn->pos = spawn->prev_pos;
}

static inline void Item_InitSpawnCommonFields(SpawnItem* spawn,
                                              HSD_GObj* parent, f32 facing_dir,
                                              bool initial_collision)
{
    spawn->facing_dir = facing_dir;
    spawn->x3C_damage = 0;
    spawn->vel.x = spawn->vel.y = spawn->vel.z = 0.0F;
    spawn->x0_parent_gobj = parent;
    spawn->x4_parent_gobj2 = spawn->x0_parent_gobj;
    spawn->x44_flag.b0 = initial_collision;
    spawn->x40 = 0;
}

static inline void
Item_InitSpawnPositionFromParent(SpawnItem* spawn, HSD_GObj* parent, Vec3* pos)
{
    spawn->prev_pos = *pos;
    spawn->prev_pos.z = 0.0F;
    it_8026BB68(parent, &spawn->pos);
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
    HSD_JObj* jobj = GET_JOBJ(gobj);

    it_80273030(gobj);
    HSD_JObjSetRotationY(jobj, PI_2 * ip->facing_dir);
    return false;
}

static inline void Item_CopyJObjScale(HSD_JObj* dst, HSD_JObj* src,
                                      Vec3* scale)
{
    scale->x = scale->y = scale->z = HSD_JObjGetScaleY(src);
    HSD_JObjSetScale(dst, scale);
}

static inline void Item_NormalizeAngle(f32* angle)
{
    while (*angle < 0.0F) {
        *angle += M_TAU;
    }
    while (*angle > M_TAU) {
        *angle -= M_TAU;
    }
}

static inline void Item_ClearFlagsAndEnterState(Item_GObj* gobj, Item* ip,
                                                s32 msid)
{
    it_8026B3A8(gobj);
    ip->xDC8_word.flags.x13 = 0;
    it_80272940(gobj);
    Item_80268E5C(gobj, msid, ITEM_ANIM_UPDATE);
}

static inline void Item_UpdateZakoVelocity(Item_GObj* gobj, Item* ip)
{
    it_802762BC(ip);
    it_8027BA54(gobj, &ip->x40_vel);
    it_802762BC(ip);
}

static inline void Item_ZakoDefeat(Item_GObj* gobj, Item* ip)
{
    it_8027C9D8(ip);
    it_802756D0(gobj);
    it_80275474(gobj);
    it_8027CE44(gobj);
    Camera_RequestQuake(QuakeKind_Small, &ip->pos);
}

static inline void Item_InitLinkMtx(Mtx m, f32 z)
{
    PSMTXIdentity(m);
    m[0][3] = 0.0f;
    m[1][3] = 0.0f;
    m[2][3] = z;
}

static inline void Item_InitZakoCollision(Item_GObj* gobj, Item* ip)
{
    ip->xD5C = 0;
    ip->xDC8_word.flags.x15 = 0;
    it_8027542C(gobj);
    it_80275270(gobj);
    ip->xDC8_word.flags.x19 = 1;
}

#endif
