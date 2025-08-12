#ifndef MELEE_GM_RESULT_H
#define MELEE_GM_RESULT_H

#include <placeholder.h>

#include "baselib/forward.h"
#include "gm/forward.h"
#include <dolphin/mtx.h>
#include "dolphin/gx/GXStruct.h"

struct ResultsPlayerData;

/* 174274 */ MatchEnd* fn_80174274(void);
/* 174284 */ s32 fn_80174284(u8);
/* 174338 */ void fn_80174338(void);
/* 17435C */ void fn_8017435C(void);
/* 174380 */ void fn_80174380(void);
/* 1743A4 */ bool gm_801743A4(enum MatchOutcome);
/* 1743C4 */ UNK_RET fn_801743C4(UNK_PARAMS);
/* 174468 */ UNK_RET fn_80174468(UNK_PARAMS);
/* 1748EC */ UNK_RET fn_801748EC(UNK_PARAMS);
/* 174920 */ void fn_80174920(struct ResultsPlayerData*);
/* 1749B8 */ void fn_801749B8(HSD_GObj*);
/* 174A60 */ UNK_RET fn_80174A60(UNK_PARAMS);
/* 174B4C */ void fn_80174B4C(struct ResultsData*, s32);
/* 174FD0 */ void fn_80174FD0(HSD_JObj*, s32);
/* 175038 */ void fn_80175038(HSD_GObj*, s32);
/* 17507C */ GXColor fn_8017507C(s32);
/* 175240 */ void fn_80175240(s32);
/* 17556C */ void fn_8017556C(s32);
/* 1756E0 */ UNK_RET fn_801756E0(UNK_PARAMS);
/* 175880 */ UNK_RET fn_80175880(UNK_PARAMS);
/* 175A94 */ void fn_80175A94(s32, Vec3*);
/* 175C5C */ void fn_80175C5C(void);
/* 175D34 */ void fn_80175D34(void);
/* 175DC8 */ UNK_RET fn_80175DC8(UNK_PARAMS);
/* 176A6C */ void fn_80176A6C(void);
/* 176BCC */ void fn_80176BCC(HSD_GObj*);
/* 176BF0 */ UNK_RET fn_80176BF0(UNK_PARAMS);
/* 176D18 */ void fn_80176D18(HSD_GObj*);
/* 176D3C */ UNK_RET fn_80176D3C(UNK_PARAMS);
/* 176F60 */ UNK_RET fn_80176F60(UNK_PARAMS);
/* 1771C0 */ UNK_RET fn_801771C0(UNK_PARAMS);
/* 177368 */ void gm_80177368_OnEnter(UNK_T);
/* 177704 */ void gm_80177704_OnLeave(void*);

#endif
