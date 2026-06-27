#ifndef MELEE_GR_INLINES_H
#define MELEE_GR_INLINES_H

#include "gr/granime.h"
#include "gr/grdisplay.h"
#include "gr/ground.h"
#include "gr/types.h"

#include <baselib/forward.h>

#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>
#include <baselib/random.h>

#define GET_GROUND(gobj) ((Ground*) HSD_GObjGetUserData(gobj))

static inline void Ground_JObjInline1(HSD_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Ground_801C2ED0(jobj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

static inline void Ground_SetupStageCallbacks(HSD_GObj* gobj,
                                              StageCallbacks* callbacks)
{
    Ground* gp = GET_GROUND(gobj);
    gp->x8_callback = NULL;
    gp->xC_callback = NULL;
    GObj_SetupGXLink(gobj, grDisplay_801C5DB0, 3, 0);
    if (callbacks->callback3 != NULL) {
        gp->x1C_callback = callbacks->callback3;
    }
    if (callbacks->callback0 != NULL) {
        callbacks->callback0(gobj);
    }
    if (callbacks->callback2 != NULL) {
        HSD_GObj_SetupProc(gobj, callbacks->callback2, 4);
    }
}

#define ZRANDI(n) ((n) != 0 ? HSD_Randi(n) : 0)

static inline int rand_range(int a, int b)
{
    if (a > b) {
        return b + ZRANDI(a - b);
    } else if (a < b) {
        return a + ZRANDI(b - a);
    } else {
        return a;
    }
}

#endif
