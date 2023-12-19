#ifndef GALE01_099F1C
#define GALE01_099F1C

#include <platform.h>
#include "ftCommon/forward.h"

/* 099F1C */ bool ftCo_80099F1C(ftCo_GObj* gobj);
/* 099F9C */ bool ftCo_80099F9C(ftCo_GObj* gobj);
/* 09A080 */ bool ftCo_8009A080(ftCo_GObj* gobj);
/* 09A134 */ bool ftCo_8009A134(ftCo_GObj* gobj);
/* 09A184 */ void ftCo_8009A184(ftCo_GObj* gobj, FtMotionId msid,
                                MotionFlags mf, float anim_start);
/* 09A228 */ void ftCo_8009A228(ftCo_GObj* gobj);
/* 09A2A8 */ void ftCo_Pass_Anim(ftCo_GObj* gobj);
/* 09A2E4 */ void ftCo_Pass_IASA(ftCo_GObj* gobj);
/* 09A388 */ void ftCo_Pass_Phys(ftCo_GObj* gobj);
/* 09A3A8 */ void ftCo_Pass_Coll(ftCo_GObj* gobj);

#endif
