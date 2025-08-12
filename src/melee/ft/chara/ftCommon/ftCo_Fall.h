#ifndef GALE01_0CC730
#define GALE01_0CC730

#include <placeholder.h>

#include "ft/forward.h"
#include "ftCommon/forward.h"

/* 0CC730 */ void ftCo_Fall_Enter(Fighter_GObj* gobj);
/* 0CC830 */ void ftCo_Fall_Enter_YoshiEgg(Fighter_GObj* gobj);
/* 0CC8DC */ void ftCo_Fall_Enter_YoshiEgg_Kirby(Fighter_GObj* gobj);
/* 0CC988 */ void ftCo_800CC988(Fighter_GObj* gobj, float);
/* 0CCA00 */ void ftCo_Fall_Anim(Fighter_GObj* gobj);
/* 0CCAAC */ bool ftCo_Fall_IASA_Inner(Fighter_GObj* gobj);
/* 0CCBE0 */ void ftCo_Fall_Anim_Inner(Fighter_GObj* gobj, float*, FtMotionId,
                                       FtMotionId, FtMotionId);
/* 0CCD34 */ void ftCo_Fall_IASA(Fighter_GObj* gobj);
/* 0CCD58 */ void ftCo_Fall_Phys(Fighter_GObj* gobj);
/* 0CCD78 */ void ftCo_Fall_Coll(Fighter_GObj* gobj);

#endif
