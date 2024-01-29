/// @file
/// Aerial Attacks (AttackAir)
#ifndef MELEE_FT_CHARA_FTGAMEWATCH_FTGAMEWATCH_ATTACKAIR_H
#define MELEE_FT_CHARA_FTGAMEWATCH_FTGAMEWATCH_ATTACKAIR_H

#include <platform.h>
#include <baselib/forward.h>

/* 14AFC0 */ void ftGw_AttackAirN_ItemParachuteSetup(HSD_GObj* gobj);
/* 14B074 */ void ftGw_AttackAirN_ItemParachuteOnLand(HSD_GObj* gobj);
/* 14B0F0 */ void ftGw_AttackAirN_ItemParachuteSetFlag(HSD_GObj* gobj);
/* 14B12C */ void ftGw_AttackAirN_ItemParachuteRemove(HSD_GObj* gobj);
/* 14B18C */ bool ftGw_AttackAirN_ItemCheckParachuteRemove(HSD_GObj* gobj);
/* 14B1B4 */ void ftGw_AttackAirN_ItemTurtleSetup(HSD_GObj* gobj);
/* 14B2E4 */ void ftGw_AttackAirN_ItemTurtleSetFlag(HSD_GObj* gobj);
/* 14B320 */ void ftGw_AttackAirN_ItemTurtleRemove(HSD_GObj* gobj);
/* 14B380 */ bool ftGw_AttackAirN_ItemCheckTurtleRemove(HSD_GObj* gobj);
/* 14B3A8 */ void ftGw_AttackAirN_ItemSparkySetup(HSD_GObj* gobj);
/* 14B45C */ void ftGw_AttackAirN_ItemSparkyOnLand(HSD_GObj* gobj);
/* 14B4D8 */ void ftGw_AttackAirN_ItemSparkySetFlag(HSD_GObj* gobj);
/* 14B514 */ void ftGw_AttackAirN_ItemSparkyRemove(HSD_GObj* gobj);
/* 14B574 */ void ftGw_AttackAirN_EnterItemHitlag(HSD_GObj* gobj);
/* 14B624 */ bool ftGw_AttackAirN_ItemCheckSparkyRemove(HSD_GObj* gobj);
/* 14B64C */ void ftGw_AttackAirN_DecideAction(HSD_GObj* gobj);
/* 14B6E4 */ void ftGw_AttackAirN_Enter(HSD_GObj* gobj);
/* 14B720 */ void ftGw_AttackAirN_Anim(HSD_GObj* gobj);
/* 14B740 */ void ftGw_AttackAirN_IASA(HSD_GObj* gobj);
/* 14B760 */ void ftGw_AttackAirN_Phys(HSD_GObj* gobj);
/* 14B780 */ void ftGw_AttackAirN_Coll(HSD_GObj* gobj);
/* 14B7A8 */ void ftGw_LandingAirN_Enter(HSD_GObj* gobj);
/* 14B87C */ void ftGw_AttackAirB_Anim(HSD_GObj* gobj);
/* 14B89C */ void ftGw_AttackAirB_IASA(HSD_GObj* gobj);
/* 14B8BC */ void ftGw_AttackAirB_Phys(HSD_GObj* gobj);
/* 14B8DC */ void ftGw_AttackAirB_Coll(HSD_GObj* gobj);
/* 14B904 */ void ftGw_LandingAirB_Enter(HSD_GObj* gobj);
/* 14B9D8 */ void ftGw_AttackAirHi_Anim(HSD_GObj* gobj);
/* 14B9F8 */ void ftGw_AttackAirHi_IASA(HSD_GObj* gobj);
/* 14BA18 */ void ftGw_AttackAirHi_Phys(HSD_GObj* gobj);
/* 14BA38 */ void ftGw_AttackAirHi_Coll(HSD_GObj* gobj);
/* 14BA60 */ void ftGw_LandingAirHi_Enter(HSD_GObj* gobj);
/* 14BB24 */ void ftGw_LandingAirN_Anim(HSD_GObj* gobj);
/* 14BB70 */ void ftGw_LandingAirN_IASA(HSD_GObj* gobj);
/* 14BB74 */ void ftGw_LandingAirN_Phys(HSD_GObj* gobj);
/* 14BB94 */ void ftGw_LandingAirN_Coll(HSD_GObj* gobj);
/* 14BBE0 */ void ftGw_LandingAirB_Init(HSD_GObj* gobj);
/* 14BC0C */ void ftGw_LandingAirB_Anim(HSD_GObj* gobj);
/* 14BC58 */ void ftGw_LandingAirB_IASA(HSD_GObj* gobj);
/* 14BC5C */ void ftGw_LandingAirB_Phys(HSD_GObj* gobj);
/* 14BC7C */ void ftGw_LandingAirB_Coll(HSD_GObj* gobj);
/* 14BCC8 */ void ftGw_LandingAirHi_Init(HSD_GObj* gobj);
/* 14BCF4 */ void ftGw_LandingAirHi_Anim(HSD_GObj* gobj);
/* 14BD40 */ void ftGw_LandingAirHi_IASA(HSD_GObj* gobj);
/* 14BD44 */ void ftGw_LandingAirHi_Phys(HSD_GObj* gobj);
/* 14BD64 */ void ftGw_LandingAirHi_Coll(HSD_GObj* gobj);

#endif
