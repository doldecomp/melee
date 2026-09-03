#ifndef MELEE_DB_H
#define MELEE_DB_H

#include <placeholder.h>

#include "melee/ft/forward.h"
#include "melee/it/forward.h"

#include <hsd/controller.h>

typedef enum DbLKind {
    DbLKind_Master = 0,
    DbLKind_NoDebugRom = 1,
    DbLKind_DebugDevelop = 2,
    DbLKind_DebugRom = 3,
    DbLKind_Develop = 4,
} DbLKind;

/* 225374 */ void db_GetGameLaunchButtonState(void);
/* 2254B8 */ void db_Setup(void);
/* 22558C */ HSD_Pad db_ButtonsDown(int player);
/* 2255A4 */ HSD_Pad db_ButtonsPressed(int player);
/* 2255BC */ HSD_Pad db_ButtonsRepeat(int player);
/* 2255D4 */ void db_PrintEntityCounts(void);
/* 2256CC */ void db_PrintThreadInfo(void);
/* 225754 */ void db_RunEveryFrame(void);
/* 225A00 */ void fn_SetupItemAndPokemonMenu(void);
/* 225A54 */ void fn_80225A54(int arg0);
/* 225B0C */ u32 db_ShowEnemyStompRange(void);
/* 225B20 */ u32 db_ShowItemPickupRange(void);
/* 225B34 */ u32 db_ShowCoinPickupRange(void);
/* 225B48 */ void fn_EnableShowCoinPickupRange(void);
/* 225B9C */ void fn_DisableShowCoinPickupRange(void);
/* 225BF0 */ void fn_EnableShowEnemyStompRange(void);
/* 225C44 */ void fn_DisableShowEnemyStompRange(void);
/* 225C8C */ void fn_EnableShowItemPickupRange(void);
/* 225CD4 */ void fn_DisableShowItemPickupRange(void);
/* 225D1C */ s32 db_GetCurrentlySelectedPokemon(void);
/* 225D2C */ void db_DisableItemSpawns(void);
/* 225D40 */ void db_EnableItemSpawns(void);
/* 225D54 */ s32 db_AreItemSpawnsEnabled(void);
/* 225D64 */ void db_80225D64(Item_GObj* item, Fighter_GObj* owner);
/* 225D7C */ void fn_ToggleItemCollisionBubbles(void);
/* 225DD8 */ void db_80225DD8(Item_GObj* item, Fighter_GObj* owner);
/* 225E6C */ void fn_80225E6C(Fighter_GObj* owner, Fighter*);
/* 225F20 */ void db_HandleItemPokemonMenuInput(int player);
/* 2260D4 */ void fn_ShowOrCreateItemAndPokemonMenu(int player);
/* 2261BC */ void fn_UpdateItemAndPokemonMenu(int player);
/* 2262E0 */ void db_CheckAndSpawnItem(int player);
/* 2264C4 */ void fn_CheckItemAndPokemonMenu(int player);
/* 22659C */ void fn_SetupCpuHandicapInfo(void);
/* 22666C */ void fn_UpdateCpuHandicapInfo(void);
/* 226730 */ void fn_CheckCpuHandicapInfo(int arg0);
/* 2267C8 */ void fn_SetupAnimationInfo(void);
/* 2268B8 */ void fn_ToggleMiscFighterVisuals(void);
/* 22697C */ u8 fn_8022697C(Fighter_GObj* owner);
/* 2269C0 */ void fn_UpdateAnimationInfo(void);
/* 226BD4 */ void fn_CheckAnimationInfo(int player);
/* 226E00 */ void fn_SetupMiscStageVisuals(void);
/* 226E0C */ void fn_CheckMiscStageEffects(int arg0);
/* 227174 */ void fn_SetupCameraInfo(void);
/* 227484 */ void fn_CheckCameraInfo(int player, int buttons_down,
                                     int buttons_pressed, f32 cstick_x,
                                     f32 cstick_y);
/* 22873C */ void fn_CheckMiscVisualEffects(int player);
/* 2287C4 */ void fn_Setup5xSpeed(UNK_PARAMS);
/* 2287D8 */ void fn_Check5xSpeed(int player);
/* 228820 */ void fn_Toggle5xSpeed(void);
/* 22886C */ void db_InitScreenshot(void);
/* 22887C */ void db_CheckScreenshot(void);
/* 22892C */ void db_TakeScreenshotIfPending(void);
/* 228A64 */ void db_ClearFPUExceptions(void);
/* 228C4C */ void db_SetupCrashHandler(void);
/* 228CF4 */ void fn_SetupBonusInfo(void);
/* 2291A0 */ void fn_CheckBonusInfo(int arg0);
/* 229220 */ void fn_SetupObjAllocLimiter(void);
/* 229240 */ void fn_UpdateObjAllocLimiter(int arg0);
/* 3EA6C8 */ extern char db_build_timestamp[];
/* 4D4A08 */ extern DbLKind DbLevel;
/* 4D6B20 */ extern bool db_804D6B20;
/* 4D6B24 */ extern char** db_submotion_names;
/* 4D6B28 */ extern char** db_motionstate_names;
/* 4D6B2C */ extern char** db_bonus_names;
/* 4D6B30 */ extern u16 db_gameLaunchButtonState;
/* 4D6B80 */ extern int db_MiscVisualEffectsStatus;

#endif
