#ifndef GALE01_0C1D38
#define GALE01_0C1D38

#include <platform.h>
#include "ft/forward.h"
#include "ftCommon/forward.h"

/* 0C1D38 */ bool ftCo_800C1D38(ftCo_GObj* gobj);
/* 0C1E0C */ bool ftCo_800C1E0C(Fighter* fp);
/* 0C1E64 */ void ftCo_800C1E64(ftCo_GObj* gobj, int msid, int timer,
                                int vel_y_exponent, float facing_dir);
/* 0C2028 */ void ftCo_PassiveWall_Anim(ftCo_GObj* gobj);
/* 0C2180 */ void ftCo_PassiveWall_IASA(ftCo_GObj* gobj);
/* 0C22C0 */ void ftCo_PassiveWall_Phys(ftCo_GObj* gobj);
/* 0C2348 */ void ftCo_PassiveWall_Coll(ftCo_GObj* gobj);

#endif
