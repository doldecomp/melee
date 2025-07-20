#ifndef MELEE_GM_VSMELEE_H
#define MELEE_GM_VSMELEE_H

#include <placeholder.h>
#include <platform.h>
#include "mn/forward.h"
#include <melee/gm/forward.h>

/* 1A5244 */ struct VsModeData* gm_801A5244(void);
/* 1A5250 */ u8 *gm_801A5250(void); /// Returns KO Star Counts
/* 1A5258 */ void gm_801A5258(u8*, MatchEnd*);
/* 1A52D0 */ bool gm_801A52D0(MatchEnd*);
/* 1A5360 */ u8 gm_801A5360(MatchEnd*);
/* 1A5598 */ void gm_801A5598_OnInit(void);
/* 1A55C4 */ void gm_801A55C4(void); /// Zeroes KO Star Counts
/* 1A55EC */ void gm_801A55EC_OnLoad(void);
/* 1A5614 */ void gm_801A5614_OnUnload(void);
/* 1A5618 */ void gm_801A5618(MinorScene*, struct VsModeData*, int); /// CSS_Enter
/* 1A5680 */ void gm_801A5680(MinorScene*, struct VsModeData*); /// CSS_Exit
/* 1A5754 */ void gm_801A5754(MinorScene*, struct VsModeData*); /// SSS_Enter
/* 1A57A8 */ void gm_801A57A8(MinorScene*, struct VsModeData*, s32); /// SSS_Exit
/* 1A583C */ void gm_801A583C(MinorScene*, struct VsModeData*,
    void (*callback)(StartMeleeData*, StartMeleeData*),
    void (*callback2)(PlayerInitData*, PlayerInitData*)); /// Match_Enter
/* 1A5AF0 */ void gm_801A5AF0(MinorScene*, u32, u32); // Match_Exit
/* 1A5C3C */ void gm_801A5C3C(MinorScene*, struct VsModeData*,
    void (*callback)(StartMeleeData*, StartMeleeData*),
    void (*callback2)(PlayerInitData*, PlayerInitData*)); /// SuddenDeath_Enter ??
/* 1A5EC8 */ void gm_801A5EC8(MinorScene*); /// SuddenDeath_Exit ??
/* 1A5F00 */ void gm_801A5F00(MinorScene*); /// Results_Enter ??
/* 1A5F64 */ void gm_801A5F64(MinorScene*, struct VsModeData*, int); /// Results_Exit ??

#endif
