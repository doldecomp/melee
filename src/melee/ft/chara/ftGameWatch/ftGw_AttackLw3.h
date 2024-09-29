/// @file
/// Down Tilt (AttackLw3)
#ifndef GALE01_14AB48
#define GALE01_14AB48

#include <platform.h>

#include <baselib/forward.h>

/* 14AB48 */ void ftGw_AttackLw3_ItemManholeSetup(HSD_GObj* gobj);
/* 14AC40 */ void ftGw_AttackLw3_ItemManholeRemove(HSD_GObj* gobj);
/* 14ACB0 */ void ftGw_AttackLw3_ItemManholeOnDamage(HSD_GObj* gobj);
/* 14AD98 */ bool ftGw_AttackLw3_ItemCheckManholeRemove(HSD_GObj* gobj);
/* 14ADB8 */ void ftGw_AttackLw3_Enter(HSD_GObj* gobj);
/* 14AE3C */ void ftGw_AttackLw3_Anim(HSD_GObj* gobj);
/* 14AE78 */ void ftGw_AttackLw3_IASA(HSD_GObj* gobj);
/* 14AF6C */ void ftGw_AttackLw3_Phys(HSD_GObj* gobj);
/* 14AF8C */ void ftGw_AttackLw3_Coll(HSD_GObj* gobj);

#endif
