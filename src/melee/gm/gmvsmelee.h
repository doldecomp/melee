#ifndef MELEE_GM_VSMELEE_H
#define MELEE_GM_VSMELEE_H

#include <placeholder.h>
#include <platform.h>
#include "gm/forward.h"
#include "mn/types.h"

/* 1A5244 */ s8* gm_801A5244(void);
/* 1A5250 */ UNK_T gm_801A5250(void);
/* 1A5258 */ void gm_801A5258(u8*, MatchEnd*);
/* 1A52D0 */ bool gm_801A52D0(MatchEnd*);
/* 1A5360 */ s32 gm_801A5360(MatchEnd*);
/* 1A5598 */ UNK_RET gm_801A5598_OnInit(UNK_PARAMS);
/* 1A55C4 */ void gm_801A55C4(void);
/* 1A55EC */ UNK_RET gm_801A55EC_OnLoad(UNK_PARAMS);
/* 1A5614 */ void gm_801A5614_OnUnload(void);
/* 1A5618 */ void gm_801A5618(MinorScene*, VsModeData*, u8); /// CSS Enter
/* 1A5680 */ void gm_801A5680(MinorScene*, VsModeData*); /// CSS Exit
/* 1A5754 */ void gm_801A5754(MinorScene*, VsModeData*); /// SSS Enter
/* 1A57A8 */ UNK_RET gm_801A57A8(UNK_PARAMS);
/* 1A583C */ UNK_RET gm_801A583C(UNK_PARAMS);
/* 1A5AF0 */ void gm_801A5AF0(MinorScene*, u32, u32); // Match_Exit
/* 1A5C3C */ UNK_RET gm_801A5C3C(UNK_PARAMS);
/* 1A5EC8 */ void gm_801A5EC8(MinorScene*);
/* 1A5F00 */ void gm_801A5F00(MinorScene*);
/* 1A5F64 */ UNK_RET gm_801A5F64(UNK_PARAMS);

#endif
