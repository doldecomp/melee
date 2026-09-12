#ifndef MELEE_GM_1A45_H
#define MELEE_GM_1A45_H

#include <sysdolphin/baselib/forward.h>

#include <melee/gm/types.h>
#include <sysdolphin/baselib/gobj.h>

/* 1A45E8 */ bool gm_GetDbPauseFlag(int bit);
/* 1A4624 */ int gm_801A4624(void);
/* 1A4634 */ void gm_SetDbPauseFlag(int bit);
/* 1A4674 */ void gm_ClearDbPauseFlag(int bit);
/* 1A46B8 */ bool gm_801A46B8(int bit);
/* 1A46F4 */ bool fn_801A46F4(void);
/* 1A47E4 */ bool fn_801A47E4(void);
/* 1A48A4 */ u64 gm_801A48A4(u8);
/* 1A4970 */ void gm_801A4970(struct gm_DbPauseInputHandlers* db_input);
/* 1A4B08 */ void gm_SetDbPauseInputHandlers(bool (*arg0)(void),
                                             bool (*arg1)(void));
/* 1A4B1C */ void gm_801A4B1C(void);
/* 1A4B40 */ void gm_SetPreGObjProcCallback(Event cb);
/* 1A4B50 */ void gm_801A4B50(int);
/* 1A4B60 */ void gm_801A4B60(void);
/* 1A4B74 */ void gm_801A4B74(void);
/* 1A4B88 */ void gm_801A4B88(struct GameSceneInfo*);
/* 1A4B90 */ void* gm_GetCurrentSceneEnterData(void);
/* 1A4B9C */ void* gm_GetCurrentSceneExitData(void);
/* 1A4BA8 */ u32 gm_801A4BA8(void);
/* 1A4BB8 */ u32 gm_801A4BB8(void);
/* 1A4BC8 */ HSD_GObj* gm_801A4BC8(void);
/* 1A4BD0 */ void fn_801A4BD0(HSD_GObj*);
/* 1A4BD4 */ void gm_801A4BD4(void);

/**
 * @brief Finds the #GameScene for a given scene kind.
 *
 * Walks the global #GameScene table (from #gm_GetAllGameScenes)
 * comparing each entry's #GameScene::class_id against @p kind until a
 * match is found or the @c GS_COUNT value is reached.
 *
 * @param kind The #GameSceneKind (passed as a @c u8) to look up.
 * @returns The #GameScene whose #GameScene::class_id equals
 */
/* 1A4CE0 */ GameScene* gm_FindGameSceneHandler(u8 kind);

/**
 * @brief Main per-scene loop invoked from @c gm_801A4014.
 *
 * Runs until #gm_80479D58_t::unk_C becomes non-zero, calling @p on_frame each
 * frame after pad/input processing.
 */
/* 1A4D34 */ void gm_801A4D34(void (*on_frame)(void), GameSceneInfo*);

/* 4D6724 */ extern void (*gm_804D6724)(void);

#endif
