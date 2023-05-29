#ifndef MELEE_FT_FTWALKCOMMON_H
#define MELEE_FT_FTWALKCOMMON_H

#include "ft/forward.h"
#include "ftCommon/forward.h"

#include "ft/fighter.h"

void ftWalkCommon_800DFCA4(ftCo_GObj* gobj, FtMotionId msid,
                           MotionFlags ms_flags, float anim_start,
                           float slow_anim_frame, float middle_anim_frame,
                           float fast_anim_frame, float slow_anim_rate,
                           float middle_anim_rate, float fast_anim_rate,
                           float accel_mul);

void ftWalkCommon_800DFDDC(ftCo_GObj* gobj);

void ftWalkCommon_800DFEC8(ftCo_GObj* gobj, void (*arg_cb)(ftCo_GObj*, f32));

void ftWalkCommon_800E0060(ftCo_GObj* gobj);
bool ftWalkCommon_800DFC70(ftCo_GObj* gobj);

FtWalkType ftWalkCommon_GetWalkType(ftCo_GObj* gobj);

#endif
