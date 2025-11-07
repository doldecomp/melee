#ifndef GALE01_0968C8
#define GALE01_0968C8

#include "ftCommon/forward.h"

/* 0968C8 */ void ftCo_800968C8(Fighter_GObj* gobj);
/* 096900 */ void ftCo_80096900(Fighter_GObj* gobj, int, int,
                                bool allow_interrupt, float, float);
/* 0969D8 */ void ftCo_800969D8(Fighter_GObj* gobj, int, int, int, float,
                                float, float);
/* 096AA0 */ void ftCo_FallSpecial_Anim(Fighter_GObj* gobj);
/* 096AF4 */ void ftCo_FallSpecial_IASA(Fighter_GObj* gobj);
/* 096B44 */ void ftCo_FallSpecial_Phys(Fighter_GObj* gobj);
/* 096C98 */ void ftCo_FallSpecial_Coll(Fighter_GObj* gobj);
/* 096CC8 */ bool ftCo_80096CC8(Fighter_GObj* gobj, int line_id);
/* 096D28 */ void ftCo_80096D28(Fighter_GObj* gobj);

#endif
