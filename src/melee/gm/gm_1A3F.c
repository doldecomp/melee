#include "gm_1A3F.h"

#include "gm_1A36.h"
#include "gm_1A45.h"
#include "gmmain_lib.h"
#include "gmscdata.h"
#include "types.h"

#include "db/db.h"
#include "lb/lb_00B0.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbcardgame.h"
#include "lb/lbcardnew.h"
#include "lb/lbdvd.h"
#include "lb/lbheap.h"
#include "lb/lbmthp.h"
#include "lb/lbsnap.h"
#include "lb/types.h"
#include "ty/toy.h"
#include "ty/tydisplay.h"

#include <dolphin/vi.h>
#include <baselib/controller.h>
#include <baselib/devcom.h>
#include <baselib/sislib.h>
#include <baselib/video.h>

struct routingInfo {
    u8 curr_mode;     ///< ::GameModeKind
    u8 pending_mode;  ///< ::GameModeKind
    u8 prev_mode;     ///< ::GameModeKind
    u8 curr_state_id; ///< from ::GameModeState::id
    u8 prev_state_id;
    u8 next_state_id;
};
ASSERT_SIZE(struct routingInfo, 0x6);

struct stateMachine {
    struct routingInfo routing;
    struct routingInfo backup_routing;
    u8 pending_mode_change; ///< ::bool
    u8 (*get_override)(void);
};
ASSERT_SIZE(struct stateMachine, 0x14);

/* 1A3F48 */ static void preloadState(GameModeState*);
/* 1A4014 */ static void gm_801A4014(GameMode*);
/* 1A43A0 */ static u8 runGameMode(u8 mode);
/* 479D30 */ static struct stateMachine state_machine;

void preloadState(GameModeState* state)
{
    PreloadedGameModeState* preloaded_state;

    lbDvd_80018CF4(state->preload);
    switch (state->info.scene_kind) {
    case GS_STAFFROLL:
    case GS_RESULTS:
        HSD_SisLib_803A6048(0xC000);
        break;
    case GS_CSS:
        HSD_SisLib_803A6048(0x2400);
        break;
    default:
        HSD_SisLib_803A6048(0x4800);
        break;
    }
    preloaded_state = lbDvd_GetPreloadCacheScene();
    if (lbHeap_80015BB8(2) == 0) {
        preloaded_state->is_heap_persistent[0] = true;
    }
    if (lbHeap_80015BB8(3) == 0) {
        preloaded_state->is_heap_persistent[1] = true;
    }
    lbDvd_80018254();
    lb_8001C5A4();
    lb_8001D1F4();
    lbSnap_8001E27C();
    Toy_803127D4();
    tyDisplay_8031C8B8();
}

static inline u8 firstState(GameModeState* state, u8 next_id)
{
    for (; state->id != (u8) -1; state++) {
        do {
            if (state->id == next_id) {
                break;
            }
        } while (0);
        return state->id;
    }
    return 0;
}

static inline u8 nextState(GameModeState* states)
{
    GameModeState* next = states;
    u8 curr_id = state_machine.routing.curr_state_id;
    int i;
    u8 next_id;
    GameModeState* cur = states;

    for (i = 0; (next_id = next->id) != (u8) -1; i++) {
        if (cur->id > curr_id) {
            return states[i].id;
        }
        cur++;
        next++;
    }

    return firstState(states, next_id);
}

static inline GameModeState* findState(GameModeState* state)
{
    int i, j;
    for (i = state_machine.routing.curr_state_id; i < U8_MAX; i++) {
        for (j = 0; state[j].id != (u8) -1; j++) {
            if (i == state[j].id) {
                return &state[j];
            }
        }
    }
    return NULL;
}

void gm_801A4014(GameMode* mode)
{
    GameScene* scene;
    GameModeState* state;
    struct stateMachine* sm;
    struct GameSceneInfo* info;
    u32 dead; ///< @todo regswap hack
    PAD_STACK(2 * 4);

    sm = &state_machine;
    state = findState(mode->states);
    sm->routing.curr_state_id = state->id;

    preloadState(state);
    if (state->on_enter != NULL) {
        state->on_enter(state);
    }
    info = &state->info;
    scene =
        (GameScene*) ((uintptr_t) gm_FindGameSceneHandler(info->scene_kind) |
                      (dead = 0));
    gm_801A4BD4();
    gm_801A4B88(info);
    if (scene->on_enter != NULL) {
        scene->on_enter(info->enter_data);
    }
    gm_801A4D34(scene->on_frame, info);
    if (!gmMainLib_8046B0F0.resetting && scene->on_exit != NULL) {
        scene->on_exit(info->exit_data);
    }
    if (!gmMainLib_8046B0F0.resetting) {
        if (state->on_exit != NULL) {
            state->on_exit(state);
        }

        state_machine.routing.prev_state_id = sm->routing.curr_state_id;

        if (sm->routing.next_state_id) {
            sm->routing.curr_state_id = sm->routing.next_state_id - 1;
            sm->routing.next_state_id = 0;
        } else {
            sm->routing.curr_state_id = nextState(mode->states);
        }
    }
    lb_8001CDB4();
    lb_8001B760(11);
    lbMthp_8001F800();
    if (gmMainLib_8046B0F0.resetting) {
        lbAudioAx_80027DBC();
        HSD_PadReset();
        while (lb_8001B6F8() == 11);
        if (DVDCheckDisk() == 0) {
            OSResetSystem(1, 0, 0);
        }
        lbMthp_8001F800();
        while (HSD_DevComIsBusy(1));
        gmMainLib_8015FBA4();
        gm_GetAllGameModes();
        memzero(&state_machine, sizeof(state_machine));
        gm_801A3EF4();
        gmMainLib_8046B0F0.skip_intro = true;
        gm_ChangeGameModeAfterCurrentScene(GM_BOOT);
        HSD_VISetBlack(0);
    }
}

void* gm_GetGameSceneLoadData(GameModeState* scene)
{
    return scene->info.enter_data;
}

void* gm_GetGameSceneLeaveData(GameModeState* state)
{
    return state->info.exit_data;
}

void gm_SetSceneIndex(u8 arg0)
{
    state_machine.routing.curr_state_id = arg0;
    state_machine.routing.prev_state_id = arg0;
}

/// @note Actually sets the pending scene to the scene following the input
void gm_SetPendingSceneIndex(u8 next_scene)
{
    state_machine.routing.next_state_id = next_scene + 1;
}

u8 gm_GetPreviousSceneIndex(void)
{
    return state_machine.routing.prev_state_id;
}

u8 gm_GetCurrentSceneIndex(void)
{
    return state_machine.routing.curr_state_id;
}

void gm_SetNewGameModePending(void)
{
    state_machine.pending_mode_change = true;
}

void gm_SetPendingGameMode(u8 pending_mode)
{
    state_machine.routing.pending_mode = pending_mode;
}

void gm_ChangeGameModeAfterCurrentScene(int pending_mode)
{
    state_machine.routing.pending_mode = pending_mode;
    state_machine.pending_mode_change = true;
}

u8 gm_GetCurrentGameMode(void)
{
    return state_machine.routing.curr_mode;
}

u8 gm_GetPreviousGameMode(void)
{
    return state_machine.routing.prev_mode;
}

void gm_SetGameModeOverride(u8 (*mode)(void))
{
    state_machine.get_override = mode;
}

bool gm_Is1PMode(u8 mode)
{
    switch (mode) {
    case GM_CLASSIC:
    case GM_ADVENTURE:
    case GM_ALLSTAR:
    case GM_TARGET_TEST:
    case GM_TRAINING:
    case GM_HOME_RUN_CONTEST:
    case GM_10MAN_VS:
    case GM_100MAN_VS:
    case GM_3MIN_VS:
    case GM_15MIN_VS:
    case GM_ENDLESS_VS:
    case GM_CRUEL_VS:
    case GM_EVENT:
        return true;
    }
    return false;
}

static inline GameMode* findMode(u8 kind)
{
    GameMode* cur;
    for (cur = gm_GetAllGameModes(); cur->kind != GM_COUNT; cur++) {
        if (cur->kind == kind) {
            return cur;
        }
    }
    return NULL;
}

u8 runGameMode(u8 mode_kind)
{
    u8 override;
    GameMode* mode;
    struct stateMachine* sm = &state_machine;
    PAD_STACK(2 * 4);

    mode = findMode(mode_kind);

    state_machine.pending_mode_change = false;
    state_machine.routing.curr_state_id = 0;
    state_machine.routing.prev_state_id = 0;
    state_machine.routing.next_state_id = 0;
    lbDvd_80018F58(mode->preloaded);
    if (mode->on_load != NULL) {
        mode->on_load();
    }
    while (!sm->pending_mode_change) {
        if (state_machine.get_override != NULL &&
            (override = state_machine.get_override(), override != GM_COUNT))
        {
            state_machine.backup_routing = state_machine.routing;
            sm->pending_mode_change = false;
            sm->routing.curr_state_id = 0;
            sm->routing.prev_state_id = 0;
            sm->routing.next_state_id = 0;

            gm_801A4014(findMode(override));
            if (!gmMainLib_8046B0F0.resetting) {
                state_machine.routing = state_machine.backup_routing;
            }
        } else {
            gm_801A4014(mode);
        }
    }
    if (!gmMainLib_8046B0F0.resetting && mode->on_unload != NULL) {
        mode->on_unload();
    }
    return state_machine.routing.pending_mode;
}

/// UnclePunch: Scene_Main
void gm_801A4510(void)
{
    GameMode* modes;
    struct stateMachine* gamestate = &state_machine;
    int i;
    PAD_STACK(2 * 4);

    gm_GetAllGameModes();
    memzero(&state_machine, sizeof(struct stateMachine));
    modes = gm_GetAllGameModes();
    for (i = 0; modes[i].kind != GM_COUNT; i++) {
        if (modes[i].on_init != NULL) {
            modes[i].on_init();
        }
    }
    if (VIGetDTVStatus() != 0 &&
        (db_gameLaunchButtonState & HSD_PAD_B || OSGetProgressiveMode() == 1))
    {
        state_machine.routing.curr_mode = GM_PROGRESSIVE_SCAN;
    } else {
        state_machine.routing.curr_mode = GM_BOOT;
    }
    state_machine.routing.prev_mode = GM_COUNT;

    while (true) {
        u8 next_mode = runGameMode(state_machine.routing.curr_mode);
        if (gmMainLib_8046B0F0.resetting) {
            gmMainLib_8046B0F0.resetting = false;
        }
        gamestate->routing.prev_mode = gamestate->routing.curr_mode;
        gamestate->routing.curr_mode = next_mode;
    }
}
