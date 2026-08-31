#ifndef MELEE_GM_VSMELEE_H
#define MELEE_GM_VSMELEE_H

#include <placeholder.h>
#include <platform.h>

#include "mn/forward.h"

#include "mn/types.h"

#include <melee/gm/forward.h>

typedef void (*gm_StartMeleeCallback)(StartMeleeData* start,
                                      StartMeleeData* vs);
typedef void (*gm_PlayerInitCallback)(PlayerInitData* start,
                                      PlayerInitData* vs);

/* 1A5680 */ void gmVsMelee_ExitCss(GameModeState*,
                                    struct VsModeData*); /// CSS_Exit
/* 1A5EC8 */ void gm_801A5EC8(GameModeState*);
/* 1A5C3C */ void gm_801A5C3C(GameModeState* state, struct VsModeData* vs_data,
                              gm_StartMeleeCallback match_data_cb,
                              gm_PlayerInitCallback player_data_cb);
/* 1A5F00 */ void gm_801A5F00(GameModeState*);
/* 1A5F64 */ void gm_801A5F64(GameModeState*, struct VsModeData*, u8);
/* 1A583C */ void
gm_801A583C(GameModeState*, struct VsModeData*,
            void (*callback)(StartMeleeData*, StartMeleeData*),
            void (*callback2)(PlayerInitData*, PlayerInitData*));
/* 1A5598 */ void gm_Mode_Vs_OnInit(void);
/* 1A57A8 */ void gmVsMelee_ExitSss(GameModeState*, struct VsModeData*, u8);
/* 1A5618 */ void gmVsMelee_EnterCss(GameModeState*, struct VsModeData*,
                                     MatchKind);
/* 1A52D0 */ bool gm_801A52D0(MatchEnd*);
/* 1A5244 */ struct VsModeData* gm_801A5244(void);
/* 4D6860 */ extern UNK_T gm_804D6860[];
/* 47C020 */ extern ResultsMatchInfo gm_8047C020;
/* 47E2A4 */ extern MatchExitInfo gm_8047E2A4;
/* 1A5258 */ void gm_801A5258(u8*, MatchEnd*);
/* 1A5250 */ u8* gmVsMelee_GetKOCounts(void);
/* 1A55EC */ void gm_Mode_Vs_OnLoad(void);
/* 1A5614 */ void gm_Mode_Vs_OnUnload(void);
/* 1A55C4 */ void gmVsMelee_ResetKOCounts(void);
/* 1A5AF0 */ void gm_801A5AF0(GameModeState*, u8, u8);
/* 1A5754 */ void gmVsMelee_EnterSss(GameModeState*, struct VsModeData*);
/* 4807B0 */ extern CSSData gmVsMelee_CssData;
/* 480530 */ extern StartMeleeData gmVsMelee_StartData;
/* 479D98 */ extern MatchExitInfo gm_80479D98;
/* 480668 */ extern SSSData gmVsMelee_SssData;

#endif
