#ifndef GALE01_08D5FC
#define GALE01_08D5FC

#include "ftCommon/forward.h"

/* 08D5FC */ void ftCo_LandingAir_EnterWithLag(Fighter_GObj* gobj);
/* 08D708 */ void ftCo_LandingAir_EnterWithMsidLag(Fighter_GObj* gobj,
                                                   FtMotionId msid, float lag);
/* 08D78C */ void ftCo_LandingAir_Anim(Fighter_GObj* gobj);
/* 08D7AC */ void ftCo_LandingAir_IASA(Fighter_GObj* gobj);
/* 08D7B0 */ void ftCo_LandingAir_Phys(Fighter_GObj* gobj);
/* 08D7D0 */ void ftCo_LandingAir_Coll(Fighter_GObj* gobj);

#endif
