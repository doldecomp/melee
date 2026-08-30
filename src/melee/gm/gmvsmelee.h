#ifndef MELEE_GM_VSMELEE_H
#define MELEE_GM_VSMELEE_H

#include <platform.h>

#include "mn/forward.h"
#include <melee/gm/forward.h>

/* 1A5244 */ struct VsModeData* gm_801A5244(void);
/* 1A5250 */ u8* gm_801A5250(void); /// Returns KO Star Counts
/* 1A5258 */ void gm_801A5258(u8*, MatchEnd*);
/* 1A52D0 */ bool gm_801A52D0(MatchEnd*);
/* 1A5360 */ u8 gm_801A5360(MatchEnd*);
/* 1A5598 */ void gm_Mode_Vs_OnInit(void);
/* 1A55C4 */ void gm_801A55C4(void); /// Zeroes KO Star Counts
/* 1A55EC */ void gm_Mode_Vs_OnLoad(void);
/* 1A5614 */ void gm_Mode_Vs_OnUnload(void);
/* 1A5618 */ void gm_801A5618(GameModeState*, struct VsModeData*,
                              int); /// CSS_Enter
/* 1A5680 */ void gm_801A5680(GameModeState*, struct VsModeData*); /// CSS_Exit
/* 1A5754 */ void gm_801A5754(GameModeState*,
                              struct VsModeData*); /// SSS_Enter
/* 1A57A8 */ void gm_801A57A8(GameModeState*, struct VsModeData*,
                              u8); /// SSS_Exit
/* 1A583C */ void gm_801A583C(
    GameModeState*, struct VsModeData*,
    void (*callback)(StartMeleeData*, StartMeleeData*),
    void (*callback2)(PlayerInitData*, PlayerInitData*)); /// Match_Enter
/* 1A5AF0 */ void gm_801A5AF0(GameModeState*, u8, u8);    // Match_Exit
/* 1A5C3C */ void
gm_801A5C3C(GameModeState*, struct VsModeData*,
            void (*callback)(StartMeleeData*, StartMeleeData*),
            void (*callback2)(PlayerInitData*,
                              PlayerInitData*)); /// SuddenDeath_Enter ??
/* 1A5EC8 */ void gm_801A5EC8(GameModeState*);   /// SuddenDeath_Exit ??
/* 1A5F00 */ void gm_801A5F00(GameModeState*);   /// Results_Enter ??
/* 1A5F64 */ void gm_801A5F64(GameModeState*, struct VsModeData*,
                              u8); /// Results_Exit ??

#endif
