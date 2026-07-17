#ifndef ITSHELL_STATIC_H
#define ITSHELL_STATIC_H

#include <platform.h>

#include "it/forward.h"

#include "it/itmaplib.h"
#include "it/types.h"

#include <baselib/jobj.h>
#include <MSL/math.h>

static inline void Item_UpdateRollingShellRotation(Item_GObj* gobj, Item* ip,
                                                   HSD_JObj* jobj,
                                                   const f32* rotation_rate)
{
    it_80276CB8(gobj);
    jobj = HSD_JObjGetChild(jobj);
    HSD_JObjAddRotationY(jobj, *rotation_rate * ABS(ip->x40_vel.x));
}

#endif
