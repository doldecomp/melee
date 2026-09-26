#ifndef MELEE_EF_INLINES_H
#define MELEE_EF_INLINES_H

#include <math.h>

#include <melee/ef/types.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/psstructs.h>

#ifdef M2C
#define GET_EFFECT(gobj) ((EF_Effect*) HSD_GObjGetUserData((HSD_GObj*) gobj))
#else
#define GET_EFFECT(gobj) ((EF_Effect*) HSD_GObjGetUserData(gobj))
#endif

static inline f32 Effect_GetFacingRotationY(f32 facing_dir)
{
    f64 rotation;

    if (facing_dir < 0.0f) {
        rotation = -M_PI_2;
    } else {
        rotation = M_PI_2;
    }
    return rotation;
}

static inline void Effect_SetFacingDir(EF_Effect* effect, f32 facing_dir)
{
    HSD_JObjSetRotationY(GET_JOBJ(effect->gobj),
                         Effect_GetFacingRotationY(facing_dir));
}

static inline void Effect_SetGeneratorPos(HSD_Generator* generator, Vec3* pos)
{
    generator->appsrt->translate = *pos;
}

static inline void Effect_SetGeneratorScale(HSD_Generator* generator,
                                            f32 scale)
{
    generator->appsrt->scale.x = generator->appsrt->scale.y =
        generator->appsrt->scale.z = scale;
}

static inline void Effect_SetRotationZ(EF_Effect* effect, f32 rotation)
{
    HSD_JObjSetRotationZ(GET_JOBJ(effect->gobj), rotation);
}

#endif
