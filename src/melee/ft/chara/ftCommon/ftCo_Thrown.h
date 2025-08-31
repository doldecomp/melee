#ifndef MELEE_FTCO_THROWN_H
#define MELEE_FTCO_THROWN_H

#include "ft/forward.h"

/* 0DE3FC */ void ftCo_800DE3FC(Fighter_GObj* gobj, FtMotionId msid,
                                float anim_speed);
/* 0DE508 */ void ftCo_800DE508(Fighter_GObj* gobj);
/* 0DE69C */ void ftCo_ThrownF_Anim(Fighter_GObj* gobj);
/* 0DE6BC */ void ftCo_ThrownF_IASA(Fighter_GObj* gobj);
/* 0DE6C0 */ void ftCo_ThrownF_Phys(Fighter_GObj* gobj);
/* 0DE6C4 */ void ftCo_ThrownF_Coll(Fighter_GObj* gobj);
/* 0DE6C8 */ void ftCo_ThrownB_Anim(Fighter_GObj* gobj);
/* 0DE6E8 */ void ftCo_ThrownB_IASA(Fighter_GObj* gobj);
/* 0DE6EC */ void ftCo_ThrownB_Phys(Fighter_GObj* gobj);
/* 0DE6F0 */ void ftCo_ThrownB_Coll(Fighter_GObj* gobj);
/* 0DE6F4 */ void ftCo_ThrownHi_Anim(Fighter_GObj* gobj);
/* 0DE714 */ void ftCo_ThrownHi_IASA(Fighter_GObj* gobj);
/* 0DE718 */ void ftCo_ThrownHi_Phys(Fighter_GObj* gobj);
/* 0DE71C */ void ftCo_ThrownHi_Coll(Fighter_GObj* gobj);
/* 0DE720 */ void ftCo_ThrownHi_Cam(Fighter_GObj* gobj);
/* 0DE76C */ void ftCo_ThrownLw_Anim(Fighter_GObj* gobj);
/* 0DE78C */ void ftCo_ThrownLw_IASA(Fighter_GObj* gobj);
/* 0DE790 */ void ftCo_ThrownLw_Phys(Fighter_GObj* gobj);
/* 0DE794 */ void ftCo_ThrownLw_Coll(Fighter_GObj* gobj);
/* 0DE798 */ void fn_800DE798(Fighter_GObj* gobj);
/* 0DE798 */ void fn_800DE798(Fighter_GObj* gobj);
/* 0DE7C0 */ void ftCo_800DE7C0(Fighter_GObj* gobj, Fighter_GObj* victim,
                                bool is_upward);
/* 0DE854 */ void ftCo_800DE854(Fighter_GObj* gobj);
/* 0DE920 */ void ftCo_800DE920(Fighter_GObj* gobj, float anim_timer);
/* 0DE974 */ void ftCo_800DE974(Fighter_GObj* gobj);

#endif
