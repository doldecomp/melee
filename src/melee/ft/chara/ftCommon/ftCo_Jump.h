#ifndef GALE01_0CAE80
#define GALE01_0CAE80

#include <placeholder.h>

#include "ft/forward.h"
#include "ftCommon/forward.h"

/* 0CAE80 */ ftCo_JumpInput ftCo_Jump_GetInput(Fighter_GObj* gobj);
/* 0CAED0 */ bool ftCo_Jump_CheckInput(Fighter_GObj* gobj);
/* 0CAF78 */ bool fn_800CAF78(Fighter_GObj* gobj);
/* 0CB024 */ bool ftCo_800CB024(Fighter_GObj* gobj);
/* 0CB110 */ void ftCo_800CB110(Fighter_GObj*, bool, float);
/* 0CB250 */ void ftCo_Jump_Enter(Fighter_GObj* gobj);
/* 0CB2F8 */ void ftCo_Jump_Anim(Fighter_GObj* gobj);
/* 0CB334 */ void ftCo_Jump_IASA(Fighter_GObj* gobj);
/* 0CB438 */ void ftCo_Jump_Phys_Inner(Fighter_GObj* gobj);
/* 0CB474 */ void ftCo_Jump_Phys(Fighter_GObj* gobj);
/* 0CB4B0 */ void ftCo_Jump_Coll(Fighter_GObj* gobj);

#endif
