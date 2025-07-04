#ifndef GALE01_0C9058
#define GALE01_0C9058

#include <placeholder.h>

#include "ftCommon/forward.h"
#include "it/forward.h"

#include "lb/lbcollision.h"

/* 0C9058 */ void ftCo_Barrel_Death2_Cb(Fighter_GObj* gobj);
/* 0C9078 */ void ftCo_Barrel_Enter(ftCo_GObj* gobj, Item_GObj*);
/* 0C9198 */ void ftCo_Barrel_Take_Dmg_Cb(Fighter_GObj* gobj);
/* 0C91C0 */ void ftCo_Barrel_Anim(ftCo_GObj* gobj);
/* 0C9208 */ void ftCo_Barrel_IASA(ftCo_GObj* gobj);
/* 0C925C */ void ftCo_Barrel_Phys(ftCo_GObj* gobj);
/* 0C9260 */ void ftCo_Barrel_Coll(ftCo_GObj* gobj);
/* 0C9264 */ void ftCo_Barrel_Accessory1_Cb(Fighter_GObj* gobj);
/* 0C92E4 */ void ftCo_800C92E4(Fighter_GObj* gobj, Vec3*, Vec3*,
                                lbColl_80008D30_arg1*, float);

#endif
