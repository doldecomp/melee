#ifndef MELEE_GM_1A3F_H
#define MELEE_GM_1A3F_H

#include <placeholder.h>

#include <melee/gm/forward.h>

/* 1A3EF4 */ void gm_801A3EF4(void);
/* 1A3F48 */ void gm_801A3F48(GameScene*);
/* 1A4014 */ void gm_801A4014(GameMode*);
/* 1A427C */ void* gm_GetGameSceneLoadDataCallback(GameScene*);
/* 1A4284 */ void* gm_GetGameSceneLeaveDataCallback(GameScene*);
/* 1A428C */ void gm_SetSceneIndex(u8 arg0);
/* 1A42A0 */ void gm_SetPendingSceneIndex(u8 pending_scene);
/* 1A42B4 */ u8 gm_GetPreviousSceneIndex(void);
/* 1A42C4 */ u8 gm_GetCurrentSceneIndex(void);
/* 1A42D4 */ UNK_RET gm_SetNewGameModePending(UNK_PARAMS);
/* 1A42E8 */ void gm_SetPendingGameMode(s8 pending_mode);
/* 1A42F8 */ void gm_ChangeGameModeAfterCurrentScene(int pending_mode);
/* 1A4310 */ u8 gm_GetCurrentGameMode(void);
/* 1A4320 */ u8 gm_GetPreviousGameMode(void);
/* 1A4330 */ void gm_801A4330(u8 (*)(void));
/* 1A4340 */ bool gm_Is1PMode(u8 mode);
/* 1A43A0 */ u8 gm_RunGameMode(u8 arg0);
/* 1A42B4 */ u8 gm_GetPreviousSceneIndex(void);
/* 1A42C4 */ u8 gm_GetCurrentSceneIndex(void);
/* 1A42D4 */ UNK_RET gm_SetNewGameModePending(UNK_PARAMS);
/* 1A42E8 */ void gm_SetPendingGameMode(s8 pending_mode);
/* 1A42F8 */ void gm_ChangeGameModeAfterCurrentScene(int pending_mode);
/* 1A4310 */ u8 gm_GetCurrentGameMode(void);
/* 1A4320 */ u8 gm_GetPreviousGameMode(void);
/* 1A4330 */ void gm_801A4330(u8 (*)(void));
/* 1A4340 */ bool gm_Is1PMode(u8 mode);
/* 1A43A0 */ u8 gm_RunGameMode(u8 mode);
/* 1A4510 */ void gm_801A4510(void);

#endif
