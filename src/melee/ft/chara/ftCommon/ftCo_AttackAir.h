#ifndef GALE01_08CD68
#define GALE01_08CD68

#include <platform.h>
#include <placeholder.h>

#include "ft/forward.h"
#include "ftCommon/forward.h"

/* 08CD68 */ bool ftCo_AttackAir_CheckItemThrowInput(Fighter_GObj* gobj);
/* 08CE68 */ FtMotionId ftCo_AttackAir_GetMsidFromCStick(Fighter* fp);
/* 08CF70 */ void ftCo_AttackAir_EnterFromCStick(Fighter_GObj* gobj);
/* 08CFAC */ void ftCo_AttackAir_EnterFromMsid(Fighter_GObj* gobj, FtMotionId);
/* 08D010 */ void ftCo_AttackAir_Anim(Fighter_GObj* gobj);
/* 08D08C */ void ftCo_AttackAirN_IASA(Fighter_GObj* gobj);
/* 08D194 */ void ftCo_AttackAirF_IASA(Fighter_GObj* gobj);
/* 08D29C */ void ftCo_AttackAirB_IASA(Fighter_GObj* gobj);
/* 08D3A4 */ void ftCo_AttackAirHi_IASA(Fighter_GObj* gobj);
/* 08D4AC */ void ftCo_AttackAirLw_IASA(Fighter_GObj* gobj);
/* 08D5B4 */ void ftCo_AttackAir_Phys(Fighter_GObj* gobj);
/* 08D5D4 */ void ftCo_AttackAir_Coll(Fighter_GObj* gobj);

#endif
