#ifndef GALE01_0EBB1C
#define GALE01_0EBB1C

#include "ft/forward.h"
#include <baselib/forward.h>

#include <dolphin/mtx.h>

/* 0EBB1C */ void ftLk_SpecialHi_Enter(HSD_GObj* gobj);
/* 0EBB80 */ void ftLk_SpecialAirHi_Enter(HSD_GObj* gobj);
/* 0EBC10 */ void ftLk_SpecialHi_Anim(HSD_GObj* gobj);
/* 0EBC4C */ void ftLk_SpecialAirHi_Anim(HSD_GObj* gobj);
/* 0EBCAC */ void ftLk_SpecialHi_IASA(HSD_GObj* gobj);
/* 0EBCB0 */ void ftLk_SpecialAirHi_IASA(HSD_GObj* gobj);
/* 0EBCB4 */ void ftLk_SpecialAirHi_Phys(HSD_GObj* gobj);
/* 0EBD30 */ void ftLk_SpecialHi_Phys(HSD_GObj* gobj);
/* 0EBDC0 */ void ftLk_SpecialHi_Coll(HSD_GObj* gobj);
/* 0EBDFC */ void ftLk_SpecialAirHi_Coll(HSD_GObj* gobj);
/* 0EBEC4 */ Fighter_Part ftLk_SpecialHi_ProcessPartLThumbNb(HSD_GObj* gobj);
/* 0EBEEC */ void ftLk_SpecialHi_GetPosWithAdjustedY(HSD_GObj* gobj,
                                                     Vec3* pos);
/* 0EBF20 */ int ftLk_SpecialHi_GetFv4(HSD_GObj* gobj);

#endif
