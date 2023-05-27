#ifndef MELEE_FT_CHARA_FTCOMMON_FTCO_DOWN_H
#define MELEE_FT_CHARA_FTCOMMON_FTCO_DOWN_H

#include <platform.h>
#include "ftCommon/forward.h"

#include <placeholder.h>

/* 097D9C */ /* static */ bool ftCo_Down_CheckInput(ftCo_GObj* gobj);
/* 097EAC */ /* static */ void ftCo_80098324(Fighter_GObj* gobj,
                                             FtMotionId msid);
/* 097F08 */ void ftCo_Down_Anim(ftCo_GObj* gobj);
/* 097F44 */ void ftCo_Down_IASA(ftCo_GObj* gobj);
/* 097F48 */ void ftCo_Down_Phys(ftCo_GObj* gobj);
/* 097F68 */ void ftCo_Down_Coll(ftCo_GObj* gobj);

#endif
