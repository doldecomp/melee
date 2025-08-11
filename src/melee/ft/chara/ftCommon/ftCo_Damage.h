#ifndef GALE01_08D7F0
#define GALE01_08D7F0

#include "ftCommon/forward.h"

/* 08D7F0 */ float ftCo_Damage_CalcAngle(Fighter* fp, float kb_applied);
/* 08D8D8 */ float ftCo_ScaleBy154(float);
/* 08D8E8 */ bool ftCo_8008D8E8(float);
/* 08D930 */ void ftCo_Damage_CalcKnockback(Fighter* fp);
/* 08DB10 */ void ftCo_8008DB10(Fighter_GObj* gobj, enum_t, float);
/* 08DC0C */ void ftCo_Damage_CalcVel(Fighter* fp, float x, float y);
/* 08DCE0 */ void ftCo_8008DCE0(Fighter_GObj* gobj, int, float facing_dir);
/* 08E498 */ bool ftCo_Damage_CheckAirMotion(Fighter* fp);
/* 08E4F0 */ void ftCo_Damage_OnEveryHitlag(Fighter_GObj* gobj);
/* 08E714 */ void ftCo_Damage_OnExitHitlag(Fighter_GObj* gobj);
/* 08E908 */ void ftCo_8008E908(Fighter_GObj* gobj, float);
/* 08E984 */ bool ftCo_8008E984(Fighter* fp);
/* 08E9D0 */ void ftCo_8008E9D0(Fighter_GObj* gobj);
/* 08EB58 */ void ftCo_8008EB58(Fighter_GObj* gobj);
/* 08EC90 */ void ftCo_8008EC90(Fighter_GObj* gobj);
/* 08F744 */ void ftCo_8008F744(Fighter_GObj* gobj);
/* 08F7F0 */ void ftCo_Damage_Anim(Fighter_GObj* gobj);
/* 08FA44 */ void ftCo_Damage_IASA(Fighter_GObj* gobj);
/* 08FB18 */ void ftCo_Damage_Phys(Fighter_GObj* gobj);
/* 08FB64 */ void ftCo_Damage_Coll(Fighter_GObj* gobj);
/* 08FC94 */ void ftCo_8008FC94(Fighter_GObj* gobj);
/* 08FCB8 */ void ftCo_Damage_SetMv8FromKbThreshold(Fighter* fp);
/* 08FD98 */ void ftCo_DamageFly_Anim(Fighter_GObj* gobj);
/* 08FF48 */ void ftCo_DamageFly_IASA(Fighter_GObj* gobj);
/* 08FF84 */ void ftCo_DamageFly_Phys(Fighter_GObj* gobj);
/* 0900EC */ void ftCo_DamageFly_Coll(Fighter_GObj* gobj);
/* 090184 */ void ftCo_80090184(Fighter_GObj* gobj);
/* 0901D0 */ void ftCo_DamageFlyRoll_Anim(Fighter_GObj* gobj);
/* 090324 */ void ftCo_DamageFlyRoll_IASA(Fighter_GObj* gobj);
/* 09035C */ void ftCo_DamageFlyRoll_Phys(Fighter_GObj* gobj);
/* 0904C0 */ void ftCo_DamageFlyRoll_Coll(Fighter_GObj* gobj);
/* 3C5520 */ extern int ftCo_803C5520[2][12];

#endif
