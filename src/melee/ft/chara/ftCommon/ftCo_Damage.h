#ifndef GALE01_08D7F0
#define GALE01_08D7F0

#include <platform.h>
#include "ftCommon/forward.h"

#include <placeholder.h>

#ifdef M2CTX
struct _m2c_stack_ft_8008DCE0 {
    /* 0x00 */ char pad_0[0x40];
    /* 0x40 */ f32 sp40;
    /* 0x44 */ Vec3 sp44;
    /* 0x50 */ char pad_50[0x78];
}; /* size = 0xC8 */

struct _m2c_stack_ftCo_8008E5A4 {
    /* 0x00 */ char pad_0[0xC];
    /* 0x0C */ f32 spC; /* inferred */
    /* 0x10 */ char pad_10[4];
    /* 0x14 */ Vec3 sp14; /* inferred */
    /* 0x20 */ Vec3 sp20; /* inferred */
    /* 0x2C */ char pad_2C[0x2C];
}; /* size = 0x58 */

extern int ftItemPickup_803C5520[2][12];
#endif

/* 08D7F0 */ float ftCo_Damage_CalcAngle(ftCo_Fighter* fp, float kb_applied);
/* 08D8D8 */ float ft_0877_ScaleBy154(float);
/* 08D8E8 */ bool ft_8008D8E8(float);
/* 08D930 */ void ftCo_Damage_CalcKnockback(ftCo_Fighter* fp);
/* 08DC0C */ /* static */ void ftCo_Damage_CalcVel(ftCo_Fighter* fp, float x,
                                                   float y);
/* 08DCE0 */ void ft_8008DCE0(ftCo_GObj* gobj, int, float facing_dir);
/* 08E5A4 */ /* static */ void ftCo_8008E5A4(ftCo_Fighter* fp);
/* 08E908 */ void ft_8008E908(ftCo_GObj* gobj, float);
/* 08E984 */ bool ft_8008E984(ftCo_Fighter* fp);
/* 08E9D0 */ void ft_8008E9D0(ftCo_GObj* gobj);
/* 08EB58 */ void ft_8008EB58(ftCo_GObj* gobj);
/* 08EC90 */ void ft_8008EC90(ftCo_GObj* gobj);
/* 08F744 */ void ft_8008F744(ftCo_GObj* gobj);
/* 08F7F0 */ void ftCo_Damage_Anim(ftCo_GObj* gobj);
/* 08FA44 */ void ftCo_Damage_IASA(ftCo_GObj* gobj);
/* 08FB18 */ void ftCo_Damage_Phys(ftCo_GObj* gobj);
/* 08FB64 */ void ftCo_Damage_Coll(ftCo_GObj* gobj);
/* 08FC94 */ void ftCo_8008FC94(ftCo_GObj* gobj);
/* 08FD98 */ void ftCo_DamageFly_Anim(ftCo_GObj* gobj);
/* 08FF48 */ void ftCo_DamageFly_IASA(ftCo_GObj* gobj);
/* 08FF84 */ void ftCo_DamageFly_Phys(ftCo_GObj* gobj);
/* 0900EC */ void ftCo_DamageFly_Coll(ftCo_GObj* gobj);
/* 0901D0 */ void ftCo_DamageFlyRoll_Anim(ftCo_GObj* gobj);
/* 090324 */ void ftCo_DamageFlyRoll_IASA(ftCo_GObj* gobj);
/* 09035C */ void ftCo_DamageFlyRoll_Phys(ftCo_GObj* gobj);
/* 0904C0 */ void ftCo_DamageFlyRoll_Coll(ftCo_GObj* gobj);
/* 0DC284 */ void ftCo_800DC284(ftCo_GObj* gobj);

#endif
