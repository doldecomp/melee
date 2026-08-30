#ifndef MELEE_GM_SCDATA_H
#define MELEE_GM_SCDATA_H

#include "melee/gm/types.h"

/* 1A50A0 */ GameScene* gm_GetAllGameScenes(void);
/* 1A50AC */ GameMode* gm_GetAllGameModes(void);
/* 3DDC58 */ extern GameModeState gm_Mode_Classic_States[];
/* 3DE930 */ extern GameModeState gm_Mode_AllStar_States[];
/* 3DECB8 */ extern GameModeState gm_Mode_TargetTest_States[];
/* 3DED00 */ extern GameModeState gm_Mode_10ManVs_States[];
/* 3DED48 */ extern GameModeState gm_Mode_100ManVs_States[];
/* 3DED90 */ extern GameModeState gm_Mode_3Min_States[];
/* 3DEDD8 */ extern GameModeState gm_Mode_15Min_States[];
/* 3DEE20 */ extern GameModeState gm_Mode_EndlessVs_States[];
/* 3DEE68 */ extern GameModeState gm_Mode_CruelVs_States[];
/* 3DEEB0 */ extern GameModeState gm_Mode_SuperSuddenDeath_States[];
/* 3DEF88 */ extern GameModeState gm_Mode_TinyVs_States[];
/* 3DF060 */ extern GameModeState gm_Mode_GiantVs_States[];
/* 3DF138 */ extern GameModeState gm_Mode_StaminaVs_States[];
/* 3DF198 */ extern GameModeState gm_Mode_Homerun_States[];
/* 3DF1E0 */ extern GameModeState gm_Mode_CameraVs_States[];
/* 3DF2B8 */ extern GameModeState gm_Mode_SingleButtonVs_States[];
/* 3DF390 */ extern GameModeState gm_Mode_InvisibleVs_States[];
/* 3DF468 */ extern GameModeState gm_Mode_SlowMo_States[];
/* 3DF540 */ extern GameModeState gm_Mode_LightningVs_States[];
/* 3DF618 */ extern GameModeState gm_Mode_Event_States[];
/* 3DFAA8 */ extern GameModeState gm_Mode_HanyuCss_States[];
/* 3DFB80 */ extern GameModeState gm_Mode_DebugGOver_States[];
/* 3DFBC8 */ extern GameModeState gm_Mode_Opening_States[];
/* 3DFC70 */ extern GameModeState gm_Mode_DebugCutscene_States[];
/* 3DFDD8 */ extern GameModeState gm_Mode_Boot_States[];
/* 3DFE18 */ extern GameModeState gm_Mode_MemCard_States[];
/* 3DFE48 */ extern GameModeState gm_Mode_ChallengerApproach_States[];

#endif
