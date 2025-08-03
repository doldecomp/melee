#ifndef GALE01_099F1C
#define GALE01_099F1C

#include "ftCommon/forward.h"

/* 099F1C */ bool ftCo_80099F1C(Fighter_GObj* gobj);
/* 099F9C */ bool ftCo_80099F9C(Fighter_GObj* gobj);
/* 09A080 */ bool ftCo_8009A080(Fighter_GObj* gobj);
/* 09A134 */ bool ftCo_8009A134(Fighter_GObj* gobj);
/* 09A184 */ void ftCo_8009A184(Fighter_GObj* gobj, FtMotionId msid,
                                MotionFlags mf, float anim_start);
/* 09A228 */ void ftCo_8009A228(Fighter_GObj* gobj);
/* 09A2A8 */ void ftCo_Pass_Anim(Fighter_GObj* gobj);
/* 09A2E4 */ void ftCo_Pass_IASA(Fighter_GObj* gobj);
/* 09A388 */ void ftCo_Pass_Phys(Fighter_GObj* gobj);
/* 09A3A8 */ void ftCo_Pass_Coll(Fighter_GObj* gobj);

#endif
