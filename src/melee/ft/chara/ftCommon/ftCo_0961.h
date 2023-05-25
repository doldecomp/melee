#ifndef GALE01_0963B8
#define GALE01_0963B8

#include <platform.h>
#include "ftCommon/forward.h"

/* 0963B8 */ void ft_800968C8(ftCo_GObj* gobj);
/* 0963F0 */ void ft_80096900(ftCo_GObj* gobj, int, int, bool is_interruptable,
                              float, float);
/* 096590 */ void ftCo_FallSpecial_Anim(ftCo_GObj* gobj);
/* 0965E4 */ void ftCo_FallSpecial_IASA(ftCo_GObj* gobj);
/* 096634 */ void ftCo_FallSpecial_Phys(ftCo_GObj* gobj);
/* 096788 */ void ftCo_FallSpecial_Coll(ftCo_GObj* gobj);
/* 0969D8 */ void ft_800969D8(ftCo_GObj* gobj, int, int, int, float, float,
                              float);

#endif
