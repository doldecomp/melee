#ifndef GALE01_0ECBC4
#define GALE01_0ECBC4

#include <platform.h>

#include "ftLink/forward.h"
#include <baselib/forward.h>

/* 0ECBC4 */ ftLk_SpecialNIndex ftLk_SpecialN_GetIndex(Fighter_GObj* gobj);
/* 0ECC0C */ void ftLk_SpecialN_UnsetArrow(Fighter_GObj* gobj);
/* 0ECC6C */ void ftLk_SpecialN_UnsetFv14(Fighter_GObj* gobj);
/* 0ECCCC */ bool ftLk_SpecialN_IsActiveAnd2071b6(Fighter_GObj* gobj);
/* 0ECD04 */ void ftLk_SpecialN_ProcessFv10(Fighter_GObj* gobj);
/* 0ECD58 */ void ftLk_SpecialN_ProcessFv14(Fighter_GObj* gobj);
/* 0ECDAC */ void ftLk_SpecialN_Enter(Fighter_GObj* gobj);
/* 0ECF78 */ void ftLk_SpecialAirN_Enter(Fighter_GObj* gobj);
/* 0ED15C */ void ftLk_SpecialNStart_Anim(Fighter_GObj* gobj);
/* 0ED480 */ void ftLk_SpecialNLoop_Anim(Fighter_GObj* gobj);
/* 0ED5B4 */ void ftLk_SpecialNEnd_Anim(Fighter_GObj* gobj);
/* 0ED72C */ void ftLk_SpecialAirNStart_Anim(Fighter_GObj* gobj);
/* 0EDA58 */ void ftLk_SpecialAirNLoop_Anim(Fighter_GObj* gobj);
/* 0EDB8C */ void ftLk_SpecialAirNEnd_Anim(Fighter_GObj* gobj);
/* 0EDD88 */ void ftLk_SpecialNStart_IASA(Fighter_GObj* gobj);
/* 0EDE30 */ void ftLk_SpecialNLoop_IASA(Fighter_GObj* gobj);
/* 0EDEAC */ void ftLk_SpecialNEnd_IASA(Fighter_GObj* gobj);
/* 0EDEB0 */ void ftLk_SpecialAirNStart_IASA(Fighter_GObj* gobj);
/* 0EDF58 */ void ftLk_SpecialAirNLoop_IASA(Fighter_GObj* gobj);
/* 0EDFD4 */ void ftLk_SpecialAirNEnd_IASA(Fighter_GObj* gobj);
/* 0EDFD8 */ void ftLk_SpecialNStart_Phys(Fighter_GObj* gobj);
/* 0EDFF8 */ void ftLk_SpecialNLoop_Phys(Fighter_GObj* gobj);
/* 0EE018 */ void ftLk_SpecialNEnd_Phys(Fighter_GObj* gobj);
/* 0EE038 */ void ftLk_SpecialAirNStart_Phys(Fighter_GObj* gobj);
/* 0EE058 */ void ftLk_SpecialAirNLoop_Phys(Fighter_GObj* gobj);
/* 0EE078 */ void ftLk_SpecialAirNEnd_Phys(Fighter_GObj* gobj);
/* 0EE098 */ void ftLk_SpecialNStart_Coll(Fighter_GObj* gobj);
/* 0EE120 */ void ftLk_SpecialNLoop_Coll(Fighter_GObj* gobj);
/* 0EE1A8 */ void ftLk_SpecialNEnd_Coll(Fighter_GObj* gobj);
/* 0EE2E0 */ void ftLk_SpecialAirNStart_Coll(Fighter_GObj* gobj);
/* 0EE368 */ void ftLk_SpecialAirNLoop_Coll(Fighter_GObj* gobj);
/* 0EE3F0 */ void ftLk_SpecialAirNEnd_Coll(Fighter_GObj* gobj);
/* 3B7520 */ extern ftLk_SpecialN_Vec3Group const ftLk_Init_Vec3Group;

#endif
