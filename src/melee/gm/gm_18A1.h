#ifndef MELEE_GM_18A1_H
#define MELEE_GM_18A1_H

#include <melee/gm/forward.h>

#include <dolphin/types.h>

/* 18A160 */ u8 gm_8018A160(u8, u8);
/* 18A188 */ f32 gm_8018A188(u8, u8);
/* 18A1D8 */ f32 gm_8018A1D8(u8, u8);
/* 18A228 */ u8 gm_8018A228(u8 difficulty, u8 stage_slot, u8 idx);
/* 18A25C */ u8 gm_8018A25C(u8 difficulty, u8 stage_slot, u8 arg2);
/* 18A290 */ u8 gm_8018A290(u8 difficulty, u8 stage_slot, u8 idx);
/* 18A2C4 */ f32 gm_8018A2C4(u8, u8);
/* 18A314 */ f32 gm_8018A314(u8, u8);
/* 18A364 */ void fn_8018A364(int);
/* 473A18 */ extern UnkAllstarData gm_80473A18;

#endif
