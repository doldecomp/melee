#ifndef MELEE_IT_INLINES_H
#define MELEE_IT_INLINES_H

#include "it/it_2725.h"
#include "it/it_3F14.h"
#include "it/types.h"
#include "mp/mplib.h"

#include <baselib/gobj.h>

#define GET_ITEM(gobj) ((Item*) HSD_GObjGetUserData(gobj))

static inline Item* GetItemData(HSD_GObj* gobj)
{
    Item* item_data = gobj->user_data;
    return item_data;
}

static inline void itResetVelocity(Item* ip)
{
    ip->x40_vel.x = ip->x40_vel.y = ip->x40_vel.z = 0.0F;
}

static inline void Item_ApplyFallingPhysics(Item_GObj* gobj)
{
    ItemAttr* attrs = GET_ITEM(gobj)->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
    it_80274658(gobj, it_804D6D28->x68_float);
}

/// Check whether the grapple chain from @p head to the tip @p pos or to its
/// owner @p fp collides with terrain (shared by Link's hookshot and Samus's
/// grapple beam).
static inline bool itGrappleCheckCollision(ItemLink* head, Fighter* fp,
                                           Vec3* pos)
{
    Vec3* head_pos = &head->pos;

    if (mpCheckAllRemap(NULL, NULL, NULL, NULL, -1, -1, pos->x, pos->y,
                        head->pos.x, head->pos.y))
    {
        return true;
    } else if (mpCheckAllRemap(NULL, NULL, NULL, NULL, -1, -1, fp->cur_pos.x,
                               fp->cur_pos.y, head_pos->x, head_pos->y))
    {
        return true;
    } else {
        return false;
    }
}

/// @todo Rename; probably gets a specific joint for items
static inline HSD_JObj* itGetJObjGrandchild(Item_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    HSD_JObj* child;

    if (!jobj) {
        child = NULL;
    } else {
        child = jobj->child;
    }
    if (!child) {
        child = NULL;
    } else {
        child = child->child;
    }
    return child;
}

#endif
