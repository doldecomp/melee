#ifndef MELEE_EF_INLINES_H
#define MELEE_EF_INLINES_H

#include <math.h>

#include <melee/ef/types.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/jobj.h>

#ifdef M2C
#define GET_EFFECT(gobj) ((EF_Effect*) HSD_GObjGetUserData((HSD_GObj*) gobj))
#else
#define GET_EFFECT(gobj) ((EF_Effect*) HSD_GObjGetUserData(gobj))
#endif

static inline void Effect_SetFacingDir(EF_Effect* effect, f32 facing_dir)
{
    f64 rotation;

    if (facing_dir < 0.0f) {
        rotation = -M_PI_2;
    } else {
        rotation = M_PI_2;
    }
    HSD_JObjSetRotationY(GET_JOBJ(effect->gobj), rotation);
}

#endif
