#ifndef GALE01_0C15F4
#define GALE01_0C15F4

#include <platform.h>

#include "ftCommon/forward.h"

#include <dolphin/mtx.h>

/* 0C15F4 */ bool ftCo_800C15F4(Fighter_GObj* gobj);
/* 0C1718 */ bool ftCo_800C1718(Fighter_GObj* gobj);
/* 0C17CC */ bool ftCo_800C17CC(Fighter_GObj* gobj);
/* 0C18A8 */ void ftCo_800C18A8(Fighter_GObj* gobj, ftCommon_MotionState msid,
                                Vec3* normal, Vec3*);
/* 0C1B2C */ void ftCo_FlyReflect_Anim(Fighter_GObj* gobj);
/* 0C1B64 */ void ftCo_FlyReflect_IASA(Fighter_GObj* gobj);
/* 0C1B84 */ void ftCo_FlyReflect_Phys(Fighter_GObj* gobj);
/* 0C1BA4 */ void ftCo_FlyReflect_Coll(Fighter_GObj* gobj);

#endif
