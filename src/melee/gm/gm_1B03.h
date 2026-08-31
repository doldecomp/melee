#ifndef GALE01_1B0348
#define GALE01_1B0348

#include "melee/gm/types.h"

#include "melee/mn/forward.h"

/* 1B0348 */ void gm_DetermineSubColors(StartMeleeData*); ///< Character tints?
/* 1B0474 */ void gm_801B0474(StartMeleeData*, MatchEnd*);
/* 1B05F4 */ void gm_801B05F4(PlayerInitData*, int);
/* 1B0620 */ void gm_801B0620(PlayerInitData*, u8 c_kind, u8 color, u8 stocks,
                              u8);
/* 1B0664 */ void gm_801B0664(PlayerInitData*, u8 c_kind, u8 color, u8 stocks,
                              u8);
/* 1B06B0 */ void gm_801B06B0(CSSData*, u8 match_type, s8 c_kind, s8 stocks,
                              s8 color, u8, u8 cpu_level, u8 slot);
/* 1B0730 */ void gm_801B0730(CSSData*, s8* ckind, u8* stocks, u8* color,
                              u8* nametag, u8* cpu_level);
/* 1B07B4 */ void gm_801B07B4(CSSData*, s8, s8, s8, u8, u8, u8);
/* 1B07E8 */ void gm_801B07E8(CSSData*, s8*, s8*, s8*, s8*, u8*);

#endif
