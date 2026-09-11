#ifndef MELEE_GM_1A3F_H
#define MELEE_GM_1A3F_H

#include <melee/gm/forward.h>

/* 1A427C */ void* gm_GetGameModeStateEnterData(GameModeState*);
/* 1A4284 */ void* gm_GetGameModeStateExitData(GameModeState*);
/**
 * @brief Sets the scene index for both the current and previous scene.
 *
 * Sets #GameRouting::curr_scene_idx and #GameRouting::prev_scene_idx on
 * #state_machine.
 *
 * See docs related to #GameModeState.
 *
 * @param arg0 The index of the scene to use. Not to be confused with the scene
 * class_id, which is defined as a GameSceneKind.
 */
/* 1A428C */ void gm_SetGameModeStateId(u8 idx);
/**
 * @brief Sets the scene index for the pending scene
 *
 * Sets #GameRouting::pending_scene_idx on #state_machine to @c arg0 + 1
 *
 * See docs related to #GameModeState.
 *
 * @param arg0 The scene index of the scene preceding the desired pending
 * scene. The method adds +1 to the input. Not to be confused with the scene
 * class_id, which is defined as a #GameSceneKind.
 */
/* 1A42A0 */ void gm_SetNextGameModeStateId(u8 pending_scene);
/* 1A42B4 */ u8 gm_GetPreviousSceneIndex(void);
/* 1A42C4 */ u8 gm_GetCurrentSceneIndex(void);
/**
 * @brief Sets #state_machine's #GameState::pending value to @c true (1).
 * Signaling that the game mode should change after the current scene exits.
 *
 * See also: ::gm_ChangeGameModeAfterCurrentScene, ::gm_SetPendingGameMode,
 * ::runGameMode
 */
/* 1A42D4 */ void gm_SetNewGameModePending(void);
/**
 * @brief Sets #GameRouting::pending_mode on #state_machine to @c pending_mode
 * for use after the current mode exits.
 *
 * Sets the #state_machine #GameRouting::pending_mode to the provided value.
 * The @c pending_mode is read when ::runGameMode exits, ultimately passing
 * the
 * @c pending_mode on to the next invocation of ::runGameMode.
 *
 * Note that subsequent calls to ::gm_SetPendingGameMode or
 * ::gm_ChangeGameModeAfterCurrentScene will override the last one. When a game
 * mode exits, the last call to ::gm_SetPendingGameMode or
 * ::gm_ChangeGameModeAfterCurrentScene wins.
 *
 * See also: ::gm_ChangeGameModeAfterCurrentScene, ::gm_SetNewGameModePending,
 * ::runGameMode
 *
 * @param pending_mode The next game mode to use
 */
/* 1A42E8 */ void gm_SetPendingGameMode(u8 pending_mode);
/**
 * @brief Sets #GameRouting::pending_mode and #GameState::pending on
 * #state_machine to @c pending_mode and @c true (1) for use after the current
 * scene exits,
 *
 * Sets the #state_machine #GameRouting::pending_mode to the provided
 * value, setting #GameState::pending to true (1) in the process.
 * The @c pending_mode is read when ::runGameMode exits, ultimately passing
 * the
 * @c pending_mode on to the next invocation of ::runGameMode.
 *
 * Effectively equivelant to running ::gm_SetPendingGameMode and
 * ::gm_SetNewGameModePending
 *
 * Note that subsequent calls to ::gm_SetPendingGameMode or
 * ::gm_ChangeGameModeAfterCurrentScene will override the last one. When a game
 * mode exits, the last call to ::gm_SetPendingGameMode or
 * ::gm_ChangeGameModeAfterCurrentScene wins.
 *
 * See also: ::gm_SetPendingGameMode, ::gm_SetNewGameModePending,
 * ::runGameMode
 *
 * @param pending_mode The next game mode to use
 */
/* 1A42F8 */ void gm_ChangeGameModeAfterCurrentScene(int pending_mode);
/* 1A4310 */ u8 gm_GetCurrentGameMode(void);
/* 1A4320 */ u8 gm_GetPreviousGameMode(void);
/* 1A4330 */ void gm_SetGameModeOverride(u8 (*)(void));
/* 1A4340 */ bool gm_Is1PMode(u8 mode);
/* 1A4510 */ void gm_801A4510(void);

#endif
