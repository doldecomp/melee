#ifndef GALE01_08D7F0
#define GALE01_08D7F0

#include "ftCommon/forward.h"

/* 08D7F0 */ float ftCo_Damage_CalcAngle(ftCo_Fighter* fp, float kb_applied);
/* 08D8D8 */ float ftCo_ScaleBy154(float);
/* 08D8E8 */ bool ftCo_8008D8E8(float);
/* 08D930 */ void ftCo_Damage_CalcKnockback(ftCo_Fighter* fp);
/* 08DB10 */ void ftCo_8008DB10(ftCo_GObj* gobj, enum_t, float);
/* 08DC0C */ void ftCo_Damage_CalcVel(ftCo_Fighter* fp, float x, float y);
/* 08DCE0 */ void ftCo_8008DCE0(ftCo_GObj* gobj, int, float facing_dir);
/* 08E498 */ bool ftCo_Damage_CheckAirMotion(ftCo_Fighter* fp);
/* 08E4F0 */ void ftCo_Damage_OnEveryHitlag(ftCo_GObj* gobj);
/* 08E714 */ void ftCo_Damage_OnExitHitlag(ftCo_GObj* gobj);
/* 08E908 */ void ftCo_8008E908(ftCo_GObj* gobj, float);
/* 08E984 */ bool ftCo_8008E984(ftCo_Fighter* fp);
/* 08E9D0 */ void ftCo_8008E9D0(ftCo_GObj* gobj);
/* 08EB58 */ void ftCo_8008EB58(ftCo_GObj* gobj);
/* 08EC90 */ void ftCo_8008EC90(ftCo_GObj* gobj);
/* 08F744 */ void ftCo_8008F744(ftCo_GObj* gobj);
/* 08F7F0 */ void ftCo_Damage_Anim(ftCo_GObj* gobj);
/* 08FA44 */ void ftCo_Damage_IASA(ftCo_GObj* gobj);
/* 08FB18 */ void ftCo_Damage_Phys(ftCo_GObj* gobj);
/* 08FB64 */ void ftCo_Damage_Coll(ftCo_GObj* gobj);
/* 08FC94 */ void ftCo_8008FC94(ftCo_GObj* gobj);
/* 08FCB8 */ void ftCo_Damage_SetMv8FromKbThreshold(ftCo_Fighter* fp);
/* 08FD98 */ void ftCo_DamageFly_Anim(ftCo_GObj* gobj);
/* 08FF48 */ void ftCo_DamageFly_IASA(ftCo_GObj* gobj);
/* 08FF84 */ void ftCo_DamageFly_Phys(ftCo_GObj* gobj);
/* 0900EC */ void ftCo_DamageFly_Coll(ftCo_GObj* gobj);
/* 090184 */ void ftCo_80090184(ftCo_GObj* gobj);
/* 0901D0 */ void ftCo_DamageFlyRoll_Anim(ftCo_GObj* gobj);
/* 090324 */ void ftCo_DamageFlyRoll_IASA(ftCo_GObj* gobj);
/* 09035C */ void ftCo_DamageFlyRoll_Phys(ftCo_GObj* gobj);
/* 0904C0 */ void ftCo_DamageFlyRoll_Coll(ftCo_GObj* gobj);
/* 3C5520 */ extern int ftCo_803C5520[2][12];

#endif
