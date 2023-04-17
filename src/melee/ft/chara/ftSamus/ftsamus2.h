#ifndef MELEE_FT_CHARA_FTSAMUS_FTSAMUS2_H
#define MELEE_FT_CHARA_FTSAMUS_FTSAMUS2_H

#include <platform.h>

#include <baselib/gobj.h>

f32 ftSs_Init_80128AC8(HSD_GObj* gobj, f32 farg1, f32 farg2);
void ftSs_Init_80128B1C(HSD_GObj*, f32, f32, f32);

void ftSs_SpecialAirLw_Anim(HSD_GObj* gobj);
void ftSs_Init_80128944(HSD_GObj* gobj, f32 farg1, f32 farg2);
void ftSs_SpecialLw_IASA(HSD_GObj* gobj);
void ftSs_SpecialAirLw_IASA(HSD_GObj* gobj);
void ftSs_SpecialLw_Phys(HSD_GObj* gobj);
void ftSs_SpecialAirLw_Phys(HSD_GObj* gobj);
void ftSs_SpecialLw_Coll(HSD_GObj* gobj);
void ftSs_SpecialAirLw_Coll(HSD_GObj* gobj);
int ftSs_SpecialLw_80129100(HSD_GObj* gobj, s32* arg1, s32* arg2);
s32 ftSs_SpecialLw_80129158(HSD_GObj* gobj);
s32 ftSs_SpecialN_801291A8(HSD_GObj* gobj);
bool ftSs_Init_80128A1C(HSD_GObj* gobj, unk_t arg1, f32 farg1);
void ftSs_SpecialLw_Anim(HSD_GObj* gobj);

#endif
