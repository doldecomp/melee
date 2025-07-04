#ifndef GALE01_0CAE80
#define GALE01_0CAE80

#include <placeholder.h>

#include "ft/forward.h"
#include "ftCommon/forward.h"

/* 0CAE80 */ ftCo_JumpInput ftCo_Jump_GetInput(ftCo_GObj* gobj);
/* 0CAED0 */ bool ftCo_Jump_CheckInput(ftCo_GObj* gobj);
/* 0CAF78 */ bool fn_800CAF78(ftCo_GObj* gobj);
/* 0CB024 */ bool ftCo_800CB024(ftCo_GObj* gobj);
/* 0CB110 */ void ftCo_800CB110(ftCo_GObj*, bool, float);
/* 0CB250 */ void ftCo_Jump_Enter(Fighter_GObj* gobj);
/* 0CB2F8 */ void ftCo_Jump_Anim(ftCo_GObj* gobj);
/* 0CB334 */ void ftCo_Jump_IASA(ftCo_GObj* gobj);
/* 0CB438 */ void ftCo_Jump_Phys_Inner(ftCo_GObj* gobj);
/* 0CB474 */ void ftCo_Jump_Phys(ftCo_GObj* gobj);
/* 0CB4B0 */ void ftCo_Jump_Coll(ftCo_GObj* gobj);

#endif
