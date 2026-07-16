#ifndef MELEE_IT_IT_26B1_INLINE_H
#define MELEE_IT_IT_26B1_INLINE_H

#include "it/it_26B1.h"
#include "it/types.h"

#include <baselib/gobj.h>

extern inline HSD_GObj* itGetOwner(Item_GObj* gobj)
{
    Item* ip = HSD_GObjGetUserData(gobj);
    return ip->owner;
}

extern inline s32 itGetMotionId(Item_GObj* gobj)
{
    Item* ip = HSD_GObjGetUserData(gobj);
    return ip->msid;
}

#endif
