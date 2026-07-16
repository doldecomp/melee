#ifndef MELEE_IT_INLINES_H
#define MELEE_IT_INLINES_H

#include "ef/eflib.h"
#include "it/item.h"
#include "it/itmaplib.h"
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

static inline void Item_SetEffectHitlagCallbacks(Item* ip)
{
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
}

static inline void Item_EnterStateWithEffectHitlag(Item_GObj* gobj, s32 msid)
{
    Item* ip = GET_ITEM(gobj);
    it_802762BC(ip);
    Item_80268E5C(gobj, msid, ITEM_ANIM_UPDATE);
    ip->entered_hitlag = efLib_PauseAll;
    ip->exited_hitlag = efLib_ResumeAll;
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
