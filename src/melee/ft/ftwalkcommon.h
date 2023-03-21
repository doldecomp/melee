#ifndef MELEE_FT_FTWALKCOMMON_H
#define MELEE_FT_FTWALKCOMMON_H

#include "ft/forward.h"
#include "ftCommon/forward.h"

#include "ft/fighter.h"

void ftWalkCommon_800DFCA4(HSD_GObj* gobj, ftCommon_MotionState msid, s32 arg2,
                           f32 arg8, f32 arg9, f32 argA, f32 argB, f32 argC,
                           f32 argD, f32 argE, f32 argF);

void ftWalkCommon_800DFDDC(HSD_GObj* gobj);

void ftWalkCommon_800DFEC8(HSD_GObj* gobj, void (*arg_cb)(HSD_GObj*, f32));

void ftWalkCommon_800E0060(HSD_GObj* gobj);
bool ftWalkCommon_800DFC70(HSD_GObj* gobj);

FtWalkType ftWalkCommon_GetWalkType(HSD_GObj* gobj);

#endif
