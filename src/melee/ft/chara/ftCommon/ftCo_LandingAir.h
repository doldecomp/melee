#ifndef GALE01_08D5FC
#define GALE01_08D5FC

#include "ft/forward.h"
#include "ftCommon/forward.h"

/* 08D5FC */ void ftCo_LandingAir_EnterWithLag(ftCo_GObj* gobj);
/* 08D708 */ void ftCo_LandingAir_EnterWithMsidLag(ftCo_GObj* gobj,
                                                   FtMotionId msid, float lag);
/* 08D78C */ void ftCo_LandingAir_Anim(ftCo_GObj* gobj);
/* 08D7AC */ void ftCo_LandingAir_IASA(ftCo_GObj* gobj);
/* 08D7B0 */ void ftCo_LandingAir_Phys(ftCo_GObj* gobj);
/* 08D7D0 */ void ftCo_LandingAir_Coll(ftCo_GObj* gobj);

#endif
