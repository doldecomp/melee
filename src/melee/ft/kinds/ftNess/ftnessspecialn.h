/// @file
/// PK Flash callbacks (SpecialN)
#ifndef GALE01_116EBC
#define GALE01_116EBC

#include <platform.h>

#include <baselib/forward.h>

/* 116EBC */ bool ftNs_SpecialN_CheckSpecialNHold(HSD_GObj* gobj);
/* 116F00 */ void ftNs_SpecialN_SetNULL(HSD_GObj* gobj);
/* 116F38 */ void ftNs_SpecialN_ItemPKFlushSetNULL(HSD_GObj* gobj);
/* 116F94 */ void ftNs_SpecialNStart_Enter(HSD_GObj* gobj);
/* 117034 */ void ftNs_SpecialAirNStart_Enter(HSD_GObj* gobj);
/* 1170DC */ void ftNs_SpecialNStart_Anim(HSD_GObj* gobj);
/* 1171BC */ void ftNs_SpecialNRelease_Anim(HSD_GObj* gobj);
/* 1172F0 */ void ftNs_SpecialNEnd_Anim(HSD_GObj* gobj);
/* 117378 */ void ftNs_SpecialAirNStart_Anim(HSD_GObj* gobj);
/* 117458 */ void ftNs_SpecialAirNRelease_Anim(HSD_GObj* gobj);
/* 11758C */ void ftNs_SpecialAirNEnd_Anim(HSD_GObj* gobj);
/* 117648 */ void ftNs_SpecialNStart_IASA(HSD_GObj* gobj);
/* 11764C */ void ftNs_SpecialNRelease_IASA(HSD_GObj* gobj);
/* 1176C8 */ void ftNs_SpecialNEnd_IASA(HSD_GObj* gobj);
/* 1176CC */ void ftNs_SpecialAirNStart_IASA(HSD_GObj* gobj);
/* 1176D0 */ void ftNs_SpecialAirNRelease_IASA(HSD_GObj* gobj);
/* 11774C */ void ftNs_SpecialAirNEnd_IASA(HSD_GObj* gobj);
/* 117750 */ void ftNs_SpecialNStart_Phys(HSD_GObj* gobj);
/* 117788 */ void ftNs_SpecialNRelease_Phys(HSD_GObj* gobj);
/* 1177A8 */ void ftNs_SpecialNEnd_Phys(HSD_GObj* gobj);
/* 1177C8 */ void ftNs_SpecialAirNStart_Phys(HSD_GObj* gobj);
/* 117828 */ void ftNs_SpecialAirNRelease_Phys(HSD_GObj* gobj);
/* 117888 */ void ftNs_SpecialAirNEnd_Phys(HSD_GObj* gobj);
/* 1178E8 */ void ftNs_SpecialNStart_Coll(HSD_GObj* gobj);
/* 117954 */ void ftNs_SpecialNRelease_Coll(HSD_GObj* gobj);
/* 1179C0 */ void ftNs_SpecialNEnd_Coll(HSD_GObj* gobj);
/* 117A2C */ void ftNs_SpecialAirNStart_Coll(HSD_GObj* gobj);
/* 117A98 */ void ftNs_SpecialAirNRelease_Coll(HSD_GObj* gobj);
/* 117B04 */ void ftNs_SpecialAirNEnd_Coll(HSD_GObj* gobj);

#endif
