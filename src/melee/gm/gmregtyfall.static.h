#ifndef MELEE_GM_REG_TY_FALL_STATIC_H
#define MELEE_GM_REG_TY_FALL_STATIC_H

#include "baselib/jobj.h"
#include "ft/ft_0C31.h"

/// @note taken from ft_0C31.c, no idea how to resolve the ftCo inline issues
/// in the codebase

static inline void ftCo_800C6AFC_please_dontinline(HSD_JObj* jobj)
{
    ftCo_800C6AFC(jobj);
}

static inline void ftCo_800C6AFC_dontinline(HSD_JObj* jobj)
{
    ftCo_800C6AFC_please_dontinline(jobj);
}

#define fake_HSD_ASSERT(line, cond)                                           \
    ((cond) ? ((void) 0) : __assert("jobj.h", line, #cond))

inline void fake_tyfall_HSD_JObjSetTranslateX(HSD_JObj* jobj, f32 x)
{
    fake_HSD_ASSERT(932, jobj);
    jobj->translate.x = x;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        ftCo_800C6AFC_dontinline(jobj);
    }
}

inline void fake_tyfall_HSD_JObjSetTranslateY(HSD_JObj* jobj, f32 y)
{
    fake_HSD_ASSERT(947, jobj);
    jobj->translate.y = y;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        ftCo_800C6AFC_dontinline(jobj);
    }
}

inline void fake_tyfall_HSD_JObjSetTranslateZ(HSD_JObj* jobj, f32 z)
{
    fake_HSD_ASSERT(962, jobj);
    jobj->translate.z = z;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        ftCo_800C6AFC_dontinline(jobj);
    }
}

inline void fake_tyfall_HSD_JObjSetRotationY(HSD_JObj* jobj, f32 y)
{
    fake_HSD_ASSERT(660, jobj);
    fake_HSD_ASSERT(661, !(jobj->flags & JOBJ_USE_QUATERNION));
    jobj->rotate.y = y;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        ftCo_800C6AFC_dontinline(jobj);
    }
}

inline void fake_tyfall_HSD_JObjSetScaleX(HSD_JObj* jobj, f32 x)
{
    fake_HSD_ASSERT(776, jobj);
    jobj->scale.x = x;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        ftCo_800C6AFC_dontinline(jobj);
    }
}

inline void fake_tyfall_HSD_JObjSetScaleY(HSD_JObj* jobj, f32 y)
{
    fake_HSD_ASSERT(791, jobj);
    jobj->scale.y = y;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        ftCo_800C6AFC_dontinline(jobj);
    }
}

inline void fake_tyfall_HSD_JObjSetScaleZ(HSD_JObj* jobj, f32 z)
{
    fake_HSD_ASSERT(806, jobj);
    jobj->scale.z = z;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        ftCo_800C6AFC_dontinline(jobj);
    }
}

#endif
