#ifndef MELEE_FTCO_SQUAT_H
#define MELEE_FTCO_SQUAT_H

#include "ft/forward.h"

/* 0D5F58 */ bool ftCo_Squat_CheckInput(Fighter_GObj* gobj);
/* 0D5F84 */ bool fn_800D5F84(Fighter_GObj* gobj);
/* 0D5FB0 */ bool ftCo_800D5FB0(Fighter_GObj* gobj);
/* 0D607C */ void ftCo_Squat_Anim(Fighter_GObj* gobj);
/* 0D60B8 */ void ftCo_Squat_IASA(Fighter_GObj* gobj);
/* 0D623C */ void ftCo_Squat_Phys(Fighter_GObj* gobj);
/* 0D625C */ void ftCo_Squat_Coll(Fighter_GObj* gobj);

#endif
