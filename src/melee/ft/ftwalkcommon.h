#ifndef GALE01_0DFBF8
#define GALE01_0DFBF8

#include "ft/forward.h"
#include "ftCommon/forward.h"

/* 0DFBF8 */ FtWalkType ftWalkCommon_GetWalkType(Fighter_GObj* gobj);
/* 0DFC70 */ bool ftWalkCommon_800DFC70(Fighter_GObj* gobj);
/* 0DFCA4 */ void
ftWalkCommon_800DFCA4(Fighter_GObj* gobj, FtMotionId msid, MotionFlags ms_flags,
                      float anim_start, float slow_anim_frame,
                      float middle_anim_frame, float fast_anim_frame,
                      float slow_anim_rate, float middle_anim_rate,
                      float fast_anim_rate, float accel_mul);
/* 0DFDDC */ void ftWalkCommon_800DFDDC(Fighter_GObj* gobj);
/* 0DFEC8 */ void ftWalkCommon_800DFEC8(Fighter_GObj* gobj,
                                        void (*arg_cb)(Fighter_GObj*, float));
/* 0E0060 */ void ftWalkCommon_800E0060(Fighter_GObj* gobj);

#endif
