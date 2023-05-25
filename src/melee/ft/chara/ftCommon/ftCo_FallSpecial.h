#ifndef GALE01_0968C8
#define GALE01_0968C8

#include <platform.h>
#include "ftCommon/forward.h"

/* 0968C8 */ void ft_800968C8(ftCo_GObj* gobj);
/* 096900 */ void ft_80096900(ftCo_GObj* gobj, int, int, bool allow_interrupt,
                              float, float);
/* 0969D8 */ void ft_800969D8(ftCo_GObj* gobj, int, int, int, float, float,
                              float);
/* 096AA0 */ void ftCo_FallSpecial_Anim(ftCo_GObj* gobj);
/* 096AF4 */ void ftCo_FallSpecial_IASA(ftCo_GObj* gobj);
/* 096B44 */ void ftCo_FallSpecial_Phys(ftCo_GObj* gobj);
/* 096C98 */ void ftCo_FallSpecial_Coll(ftCo_GObj* gobj);

#endif
