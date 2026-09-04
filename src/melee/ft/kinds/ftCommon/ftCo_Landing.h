#ifndef MELEE_FTCO_LANDING_H
#define MELEE_FTCO_LANDING_H

#include "ft/forward.h"

/* 0D5AEC */ void ftCo_Landing_Enter(Fighter_GObj* gobj, FtMotionId msid,
                                     bool allow_interrupt, MotionFlags flags,
                                     float anim_start, float anim_speed);
/* 0D5BF8 */ void ftCo_Landing_Enter_Basic(Fighter_GObj* gobj);
/* 0D5C54 */ void ftCo_LandingFallSpecial_Enter_Basic(Fighter_GObj* gobj);
/* 0D5CB0 */ void ftCo_LandingFallSpecial_Enter(Fighter_GObj*,
                                                bool allow_interrupt,
                                                float landing_lag);
/* 0D5D3C */ void ftCo_Landing_Anim(Fighter_GObj* gobj);
/* 0D5D78 */ void ftCo_Landing_IASA(Fighter_GObj* gobj);
/* 0D5F18 */ void ftCo_Landing_Phys(Fighter_GObj* gobj);
/* 0D5F38 */ void ftCo_Landing_Coll(Fighter_GObj* gobj);

#endif
