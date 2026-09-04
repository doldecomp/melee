/// @file
/// Neutral Attack - Greenhouse (Attack11)
#ifndef GALE01_14BDB0
#define GALE01_14BDB0

#include <baselib/forward.h>

/* 14BDB0 */ void ftGw_Attack11_ItemGreenhouseSetup(HSD_GObj* gobj);
/* 14BE84 */ void ftGw_Attack11_DecideAction(HSD_GObj* gobj);
/* 14BF48 */ void ftGw_Attack11_ItemGreenhouseSetFlag(HSD_GObj* gobj);
/* 14BF7C */ void ftGw_Attack11_ItemGreenhouseRemove(HSD_GObj* gobj);
/* 14BFD4 */ void ftGw_Attack11_ItemGreenhouseEnterHitlag(HSD_GObj* gobj);
/* 14C004 */ void ftGw_Attack11_ItemGreenhouseExitHitlag(HSD_GObj* gobj);
/* 14C034 */ bool ftGw_Attack11_ItemGreenhouse_CheckAll(HSD_GObj* gobj);
/* 14C05C */ bool ftGw_Attack11_ItemGreenhouse_CheckAttack11(HSD_GObj* gobj);
/* 14C07C */ void ftGw_Attack11_Enter(HSD_GObj* gobj);
/* 14C138 */ void ftGw_Attack11_Anim(HSD_GObj* gobj);
/* 14C174 */ void ftGw_Attack11_IASA(HSD_GObj* gobj);
/* 14C194 */ void ftGw_Attack11_Phys(HSD_GObj* gobj);
/* 14C1B4 */ void ftGw_Attack11_Coll(HSD_GObj* gobj);

#endif
