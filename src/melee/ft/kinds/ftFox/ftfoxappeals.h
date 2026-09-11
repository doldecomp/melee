#ifndef GALE01_0E5970
#define GALE01_0E5970

#include <Runtime/platform.h>

#include <melee/ft/forward.h>
#include <sysdolphin/baselib/forward.h>

/// Check if Special Taunt has already been performed
/* 0E5970 */ bool ftFx_AppealS_CheckIfUsed(Fighter* fp);
/// Check if Fox/Falco has pressed D-Pad Down
/* 0E59BC */ bool ftFx_AppealS_CheckInput(HSD_GObj* gobj);
/// Fox & Falco's Special Taunt Motion State handler
/* 0E5A90 */ void ftFx_AppealS_Enter(HSD_GObj* gobj);
/// Fox & Falco's Special Taunt Start Animation callback
/* 0E5B18 */ void ftFx_AppealS_Anim(HSD_GObj* gobj);
/// Fox & Falco's Special Taunt Start IASA callback
/* 0E5C38 */ void ftFx_AppealS_IASA(HSD_GObj* gobj);
/// Fox & Falco's Special Taunt Physics callback
/* 0E5C3C */ void ftFx_AppealS_Phys(HSD_GObj* gobj);
/// Fox & Falco's Special Taunt Collision callback
/* 0E5C5C */ void ftFx_AppealS_Coll(HSD_GObj* gobj);

#endif
