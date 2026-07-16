#ifndef MELEE_FT_FTTRANSITION_H
#define MELEE_FT_FTTRANSITION_H

#include "ft/fighter.h"
#include "ft/ftcommon.h"

static inline void ftCommon_GroundToAirStateChange(Fighter_GObj* gobj,
                                                   Fighter* fp,
                                                   FtMotionId msid,
                                                   MotionFlags flags)
{
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, msid, flags, fp->cur_anim_frame, 1.0f,
                              0.0f, NULL);
}

static inline void ftCommon_AirToGroundStateChange(Fighter_GObj* gobj,
                                                    Fighter* fp,
                                                    FtMotionId msid,
                                                   MotionFlags flags)
{
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, msid, flags, fp->cur_anim_frame, 1.0f,
                              0.0f, NULL);
}

#endif
