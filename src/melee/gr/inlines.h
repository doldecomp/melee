#ifndef MELEE_GR_INLINES_H
#define MELEE_GR_INLINES_H

#include "gr/granime.h"
#include "gr/ground.h"
#include "gr/types.h"

#include <baselib/forward.h>

#include <baselib/gobj.h>

#define GET_GROUND(gobj) ((Ground*) HSD_GObjGetUserData(gobj))

static inline void Ground_JObjInline1(HSD_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Ground_801C2ED0(jobj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

#endif
