#ifndef MELEE_GM_1A36_H
#define MELEE_GM_1A36_H

#include <placeholder.h>
#include <platform.h>

#define PAD_ALL_CONTROLLERS 4

/* 1A3680 */ u64 gm_GetButtonsPressed(u8);
/* 1A36A0 */ u64 gm_GetButtonsTriggered(u8);
/* 1A36C0 */ u64 gm_801A36C0(u8);
/* 1A36E0 */ void gm_801A36E0(s32, s32);
/* 1A3714 */ void gm_801A3714(s32, u64, u64);
/* 1A3A74 */ UNK_RET gm_EvaluateAllControllerInputs(UNK_PARAMS);
/* 1A3E88 */ UNK_RET gm_801A3E88(UNK_PARAMS);
/* 1A3EF4 */ void gm_801A3EF4(void);

#endif
