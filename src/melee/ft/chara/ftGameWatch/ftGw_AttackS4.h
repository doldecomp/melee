/// @file
/// Forward Smash (AttackS4)
#ifndef GALE01_14A848
#define GALE01_14A848

#include <platform.h>
#include <baselib/forward.h>

/* 14A848 */ void ftGw_ItemTorchSetup(HSD_GObj* gobj);
/* 14A904 */ void ftGw_AttackS4_ItemTorchSetFlag(HSD_GObj* gobj);
/* 14A938 */ void ftGw_AttackS4_ItemTorchOnDamage(HSD_GObj* gobj);
/* 14A990 */ void ftGw_AttackS4_ItemTorchEnterHitlag(HSD_GObj* gobj);
/* 14A9C0 */ void ftGw_AttackS4_ItemTorchExitHitlag(HSD_GObj* gobj);
/* 14A9F0 */ bool ftGw_AttackS4_ItemCheckTorchRemove(HSD_GObj* gobj);
/* 14AA10 */ void ftGw_AttackS4_Enter(HSD_GObj* gobj);
/* 14AA88 */ void ftGw_AttackS4_Anim(HSD_GObj* gobj);
/* 14AAC4 */ void ftGw_AttackS4_IASA(HSD_GObj* gobj);
/* 14AAF4 */ void ftGw_AttackS4_Phys(HSD_GObj* gobj);
/* 14AB14 */ void ftGw_AttackS4_Coll(HSD_GObj* gobj);

#endif
