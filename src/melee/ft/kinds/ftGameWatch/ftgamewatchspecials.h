/// @file
/// Side Special - Judgement (SpecialS)
#ifndef GALE01_14C46C
#define GALE01_14C46C

#include <platform.h>

#include <baselib/forward.h>

/* 14C46C */ void ftGw_SpecialS_ItemJudgementSetup(HSD_GObj* gobj);
/* 14C590 */ void ftGw_SpecialS_ItemJudgementSetFlag(HSD_GObj* gobj);
/* 14C5CC */ void ftGw_SpecialS_ItemJudgementRemove(HSD_GObj* gobj);
/* 14C68C */ bool ftGw_SpecialS_ItemCheckJudgementRemove(HSD_GObj* gobj);
/* 14C6B4 */ int ftGw_SpecialS_GetRandomInt(HSD_GObj* gobj);
/* 14C7A0 */ void ftGw_SpecialS_Enter(HSD_GObj* gobj);
/* 14C828 */ void ftGw_SpecialAirS_Enter(HSD_GObj* gobj);
/* 14C8BC */ void ftGw_SpecialS_Anim(HSD_GObj* gobj);
/* 14C8F8 */ void ftGw_SpecialAirS_Anim(HSD_GObj* gobj);
/* 14C934 */ void ftGw_SpecialS_IASA(HSD_GObj* gobj);
/* 14C938 */ void ftGw_SpecialAirS_IASA(HSD_GObj* gobj);
/* 14C93C */ void ftGw_SpecialS_Phys(HSD_GObj* gobj);
/* 14C974 */ void ftGw_SpecialAirS_Phys(HSD_GObj* gobj);
/* 14CA10 */ void ftGw_SpecialS_Coll(HSD_GObj* gobj);
/* 14CA4C */ void ftGw_SpecialAirS_Coll(HSD_GObj* gobj);

#endif
