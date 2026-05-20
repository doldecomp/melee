#include "gm_1A3F.h"

#include "gm_1A45.h"
#include "gmmain_lib.h"

#include "db/db.h"
#include "gm/gmscdata.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbdvd.h"
#include "lb/lbheap.h"
#include "lb/lbmthp.h"
#include "lb/lbsnap.h"
#include "lb/types.h"
#include "ty/tylist.h"

#include <dolphin/vi.h>
#include <baselib/controller.h>
#include <baselib/devcom.h>
#include <baselib/sislib.h>
#include <baselib/video.h>
#include <melee/gm/types.h>
#include <melee/lb/lb_00B0.h>
#include <melee/lb/lbcardgame.h>
#include <melee/lb/lbcardnew.h>
#include <melee/ty/tydisplay.h>

static GameState gm_80479D30;

void gm_801A3F48(GameScene* scene)
{
    PreloadCacheScene* temp_r31;

    lbDvd_80018CF4(scene->preload);
    switch (scene->info.class_id) {
    case 43:
    case 5:
        HSD_SisLib_803A6048(0xC000);
        break;
    case 8:
        HSD_SisLib_803A6048(0x2400);
        break;
    default:
        HSD_SisLib_803A6048(0x4800);
        break;
    }
    temp_r31 = lbDvd_8001822C();
    if (lbHeap_80015BB8(2) == 0) {
        temp_r31->is_heap_persistent[0] = true;
    }
    if (lbHeap_80015BB8(3) == 0) {
        temp_r31->is_heap_persistent[1] = true;
    }
    lbDvd_80018254();
    lb_8001C5A4();
    lb_8001D1F4();
    lbSnap_8001E27C();
    un_803127D4();
    un_8031C8B8();
}

inline u8 nextScene(GameScene* scenes)
{
    int i;
    u8 var_r3_3;
    GameScene* cur = scenes;

    for (i = 0; scenes[i].idx != 0xFF; i++) {
        if (cur->idx > gm_80479D30.routing.curr_scene) {
            return scenes[i].idx;
        }
        cur++;
    }

    var_r3_3 = scenes[0].idx;
    if (var_r3_3 == 0xFF) {
        var_r3_3 = 0;
    }
    return var_r3_3;
}

inline GameScene* findScene(GameScene* scene)
{
    int i, j;
    for (i = gm_80479D30.routing.curr_scene; i < 0xFF; i++) {
        for (j = 0; scene[j].idx != 0xFF; j++) {
            if (i == scene[j].idx) {
                return &scene[j];
            }
        }
    }
    return NULL;
}

void gm_801A4014(GameMode* mode)
{
    GameSceneHandler* handler;
    GameScene* scene;
    GameState* gm;
    struct GameSceneInfo* info;
    u32 unused[2];

    gm = &gm_80479D30;

    scene = findScene(mode->scenes);

    gm->routing.curr_scene = scene->idx;

    gm_801A3F48(scene);
    if (scene->Prep != NULL) {
        scene->Prep(scene);
    }
    info = &scene->info;
    handler = gm_801A4CE0(scene->info.class_id);
    gm_801A4BD4();
    gm_801A4B88(info);
    if (handler->OnLoad != NULL) {
        handler->OnLoad(info->load_data);
    }
    gm_801A4D34(handler->OnFrame, info);
    if (!gmMainLib_8046B0F0.resetting && handler->OnLeave != NULL) {
        handler->OnLeave(info->leave_data);
    }
    if (!gmMainLib_8046B0F0.resetting) {
        if (scene->Decide != NULL) {
            scene->Decide(scene);
        }

        gm_80479D30.routing.prev_scene = gm->routing.curr_scene;

        if (gm->routing.pending_scene) {
            gm->routing.curr_scene = gm->routing.pending_scene - 1;
            gm->routing.pending_scene = 0;
        } else {
            gm->routing.curr_scene = nextScene(mode->scenes);
        }
    }
    lb_8001CDB4();
    lb_8001B760(0xB);
    lbMthp_8001F800();
    if (gmMainLib_8046B0F0.resetting) {
        lbAudioAx_80027DBC();
        HSD_PadReset();
        while (lb_8001B6F8() == 0xB)
            ;
        if (DVDCheckDisk() == 0) {
            OSResetSystem(1, 0, 0);
        }
        lbMthp_8001F800();
        while (HSD_DevComIsBusy(1))
            ;
        gmMainLib_8015FBA4();
        gm_801A50AC();
        memzero(&gm_80479D30, 0x14);
        gm_801A3EF4();
        gmMainLib_8046B0F0.x0 = true;
        gm_801A42F8(GM_BOOT);
        HSD_VISetBlack(0);
    }
}

void* gm_801A427C(GameScene* scene)
{
    return scene->info.load_data;
}

void* gm_801A4284(GameScene* scene)
{
    return scene->info.leave_data;
}

void gm_SetScene(u8 arg0)
{
    gm_80479D30.routing.curr_scene = arg0;
    gm_80479D30.routing.prev_scene = arg0;
}

void gm_SetPendingScene(u8 pending_scene)
{
    gm_80479D30.routing.pending_scene = pending_scene + 1;
}

u8 gm_801A42B4(void)
{
    return gm_80479D30.routing.prev_scene;
}

u8 gm_801A42C4(void)
{
    return gm_80479D30.routing.curr_scene;
}

void gm_801A42D4(void)
{
    gm_80479D30.pending = 1;
}

void gm_801A42E8(s8 pending_mode)
{
    gm_80479D30.routing.pending_mode = pending_mode;
}

void gm_801A42F8(int pending_mode)
{
    gm_80479D30.routing.pending_mode = pending_mode;
    gm_80479D30.pending = 1;
}

u8 gm_801A4310(void)
{
    return gm_80479D30.routing.curr_mode;
}

u8 gm_801A4320(void)
{
    return gm_80479D30.routing.prev_mode;
}

void gm_801A4330(u8 (*arg0)(void))
{
    gm_80479D30.data = arg0;
}

bool gm_801A4340(u8 mode)
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

inline GameMode* findMode(u8 idx)
{
    GameMode* cur;
    for (cur = gm_801A50AC(); cur->idx != GM_COUNT; cur++) {
        if (cur->idx == idx) {
            return cur;
        }
    }
    return NULL;
}

u8 gm_801A43A0(u8 mode_kind)
{
    u8 temp_r3;
    GameMode* mode;
    GameMode* var_r3_2;
    GameState* gamestate = &gm_80479D30;
    u64 unused;

    mode = findMode(mode_kind);

    gm_80479D30.pending = 0;
    gm_80479D30.routing.curr_scene = 0;
    gm_80479D30.routing.prev_scene = 0;
    gm_80479D30.routing.pending_scene = 0;
    lbDvd_80018F58(mode->preload);
    if (mode->Load != NULL) {
        mode->Load();
    }
    while (!gamestate->pending) {
        if (gm_80479D30.data != NULL &&
            (temp_r3 = gm_80479D30.data(), temp_r3 != GM_COUNT))
        {
            gm_80479D30.backup = gm_80479D30.routing;
            gamestate->pending = 0;
            gamestate->routing.curr_scene = 0;
            gamestate->routing.prev_scene = 0;
            gamestate->routing.pending_scene = 0;

            var_r3_2 = findMode(temp_r3);

            gm_801A4014(var_r3_2);
            if (!gmMainLib_8046B0F0.resetting) {
                gm_80479D30.routing = gm_80479D30.backup;
            }
        } else {
            gm_801A4014(mode);
        }
    }
    if (!gmMainLib_8046B0F0.resetting && mode->Unload != NULL) {
        mode->Unload();
    }
    return gm_80479D30.routing.pending_mode;
}

/// UnclePunch: Scene_Main
void gm_801A4510(void)
{
    u32 unused;
    GameMode* modes;
    GameState* gamestate = &gm_80479D30;
    int i;

    gm_801A50AC();
    memzero(&gm_80479D30, sizeof(GameState));
    modes = gm_801A50AC();
    for (i = 0; modes[i].idx != GM_COUNT; i++) {
        if (modes[i].Init != NULL) {
            modes[i].Init();
        }
    }
    if (VIGetDTVStatus() != 0 &&
        (db_gameLaunchButtonState & 0x200 || OSGetProgressiveMode() == 1))
    {
        gm_80479D30.routing.curr_mode = GM_PROGRESSIVE_SCAN;
    } else {
        gm_80479D30.routing.curr_mode = GM_BOOT;
    }
    gm_80479D30.routing.prev_mode = GM_COUNT;

    while (true) {
        u8 major = gm_801A43A0(gm_80479D30.routing.curr_mode);
        if (gmMainLib_8046B0F0.resetting) {
            gmMainLib_8046B0F0.resetting = false;
        }
        gamestate->routing.prev_mode = gamestate->routing.curr_mode;
        gamestate->routing.curr_mode = major;
    }
}
