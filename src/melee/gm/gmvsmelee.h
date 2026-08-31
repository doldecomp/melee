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
/* 1A5EC8 */ void gmVsMelee_ExitSuddenDeath(GameModeState*);
/* 1A5C3C */ void
gmVsMelee_EnterSuddenDeath(GameModeState* state, struct VsModeData* vs_data,
                           gm_StartMeleeCallback match_data_cb,
                           gm_PlayerInitCallback player_data_cb);
/* 1A5F00 */ void gmVsMelee_EnterResults(GameModeState*);
/* 1A5F64 */ void gmVsMelee_ExitResults(GameModeState*, struct VsModeData*,
                                        u8);
/* 1A583C */ void
gmVsMelee_EnterVs(GameModeState*, struct VsModeData*,
                  void (*callback)(StartMeleeData*, StartMeleeData*),
                  void (*callback2)(PlayerInitData*, PlayerInitData*));
/* 1A5598 */ void gmVsMelee_Mode_OnInit(void);
/* 1A57A8 */ void gmVsMelee_ExitSss(GameModeState* state, VsModeData* vs,
                                    u8 cancel_state_id);
/* 1A5618 */ void gmVsMelee_EnterCss(GameModeState*, struct VsModeData*,
                                     CSSMatchType);
/* 1A52D0 */ bool gmVsMelee_WasAnyPlayerHuman(MatchEnd*);
/* 1A5244 */ struct VsModeData* gmVsMelee_GetVsData(void);
/* 4D6860 */ extern UNK_T gm_804D6860[];
/* 47C020 */ extern ResultsMatchInfo gmVsMelee_ResultsEnterData;
/* 47E2A4 */ extern MatchExitInfo gmVsMelee_SuddenDeathExitInfo;
/* 1A5258 */ void gmVsMelee_UpdateKOCounts(u8*, MatchEnd*);
/* 1A5250 */ u8* gmVsMelee_GetKOCounts(void);
/* 1A55EC */ void gmVsMelee_Mode_OnLoad(void);
/* 1A5614 */ void gm_Mode_Vs_OnUnload(void);
/* 1A55C4 */ void gmVsMelee_ResetKOCounts(void);
/* 1A5AF0 */ void gmVsMelee_ExitVs(GameModeState*, u8, u8);
/* 1A5754 */ void gmVsMelee_EnterSss(GameModeState*, struct VsModeData*);
/* 4807B0 */ extern CSSData gmVsMelee_CssData;
/* 480530 */ extern StartMeleeData gmVsMelee_StartData;
/* 479D98 */ extern MatchExitInfo gmVsMelee_VsExitInfo;
/* 480668 */ extern SSSData gmVsMelee_SssData;

#endif
