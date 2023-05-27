#ifndef MELEE_FT_CHARA_FTCOMMON_INLINES_H
#define MELEE_FT_CHARA_FTCOMMON_INLINES_H

#include <platform.h>
#include "ftCommon/forward.h"

#include "ef/efasync.h"
#include "ft/types.h"

#include <baselib/gobj.h>

static inline void ftCo_SpawnEf(ftCo_GObj* gobj, HSD_JObj* joint, uint arg2,
                                enum_t arg3)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    ftCo_Fighter* fp = gobj->user_data;
    efAsync_Spawn((HSD_GObj*) gobj, &fp->x60C, arg2, arg3, joint);
}

#endif
