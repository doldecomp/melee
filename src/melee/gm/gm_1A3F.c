#include "gm_1A3F.h"

#include "gm_1A45.h"
#include "gm_1A4C.h"
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

void gm_801A3F48(MinorScene* scene)
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

inline u8 matchMinor(MinorScene* scenes)
{
    int i;
    u8 var_r3_3;
    MinorScene* cur = scenes;

    for (i = 0; scenes[i].idx != 0xFF; i++) {
        if (cur->idx > gm_80479D30.nums.curr_minor) {
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

inline MinorScene* getScene(MinorScene* scene)
{
    int i, j;
    for (i = gm_80479D30.nums.curr_minor; i < 0xFF; i++) {
        for (j = 0; scene[j].idx != 0xFF; j++) {
            if (i == scene[j].idx) {
                return &scene[j];
            }
        }
    }
    return NULL;
}

void gm_801A4014(MajorScene* major_scene)
{
    MinorSceneHandler* handler;
    MinorScene* minor_scene;
    GameState* gm;
    struct MinorSceneInfo* info;
    u32 unused[2];

    gm = &gm_80479D30;

    minor_scene = getScene(major_scene->minor_scenes);

    gm->nums.curr_minor = minor_scene->idx;

    gm_801A3F48(minor_scene);
    if (minor_scene->Prep != NULL) {
        minor_scene->Prep(minor_scene);
    }
    info = &minor_scene->info;
    handler = gm_801A4CE0(minor_scene->info.class_id);
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
        if (minor_scene->Decide != NULL) {
            minor_scene->Decide(minor_scene);
        }

        gm_80479D30.nums.prev_minor = gm->nums.curr_minor;

        if (gm->nums.pending_minor) {
            gm->nums.curr_minor = gm->nums.pending_minor - 1;
            gm->nums.pending_minor = 0;
        } else {
            gm->nums.curr_minor = matchMinor(major_scene->minor_scenes);
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
        gm_801A42F8(MJ_BOOT);
        HSD_VISetBlack(0);
    }
}

void* gm_801A427C(MinorScene* scene)
{
    return scene->info.load_data;
}

void* gm_801A4284(MinorScene* scene)
{
    return scene->info.leave_data;
}

void gm_SetSceneMinor(u8 arg0)
{
    gm_80479D30.nums.curr_minor = arg0;
    gm_80479D30.nums.prev_minor = arg0;
}

void gm_SetScenePendingMinor(u8 pending_minor)
{
    gm_80479D30.nums.pending_minor = pending_minor + 1;
}

u8 gm_801A42B4(void)
{
    return gm_80479D30.nums.prev_minor;
}

u8 gm_801A42C4(void)
{
    return gm_80479D30.nums.curr_minor;
}

void gm_801A42D4(void)
{
    gm_80479D30.pending = 1;
}

void gm_801A42E8(s8 pending_major)
{
    gm_80479D30.nums.pending_major = pending_major;
}

void gm_801A42F8(int pending_major)
{
    gm_80479D30.nums.pending_major = pending_major;
    gm_80479D30.pending = 1;
}

u8 gm_801A4310(void)
{
    return gm_80479D30.nums.curr_major;
}

u8 gm_801A4320(void)
{
    return gm_80479D30.nums.prev_major;
}

void gm_801A4330(u8 (*arg0)(void))
{
    gm_80479D30.data = arg0;
}

bool gm_801A4340(u8 major_scene)
{
    switch (major_scene) {
    case MJ_CLASSIC:
    case MJ_ADVENTURE:
    case MJ_ALLSTAR:
    case MJ_TARGET_TEST:
    case MJ_TRAINING:
    case MJ_HOME_RUN_CONTEST:
    case MJ_10MAN_VS:
    case MJ_100MAN_VS:
    case MJ_3MIN_VS:
    case MJ_15MIN_VS:
    case MJ_ENDLESS_VS:
    case MJ_CRUEL_VS:
    case MJ_EVENT:
        return true;
    }
    return false;
}

inline MajorScene* findSceneMatching(u8 idx)
{
    MajorScene* cur;
    for (cur = gm_801A50AC(); cur->idx != MJ_COUNT; cur++) {
        if (cur->idx == idx) {
            return cur;
        }
    }
    return NULL;
}

u8 gm_801A43A0(u8 major_kind)
{
    u8 temp_r3;
    MajorScene* major_scene;
    MajorScene* var_r3_2;
    GameState* gamestate = &gm_80479D30;
    u64 unused;

    major_scene = findSceneMatching(major_kind);

    gm_80479D30.pending = 0;
    gm_80479D30.nums.curr_minor = 0;
    gm_80479D30.nums.prev_minor = 0;
    gm_80479D30.nums.pending_minor = 0;
    lbDvd_80018F58(major_scene->preload);
    if (major_scene->Load != NULL) {
        major_scene->Load();
    }
    while (!gamestate->pending) {
        if (gm_80479D30.data != NULL &&
            (temp_r3 = gm_80479D30.data(), temp_r3 != MJ_COUNT))
        {
            gm_80479D30.nums2 = gm_80479D30.nums;
            gamestate->pending = 0;
            gamestate->nums.curr_minor = 0;
            gamestate->nums.prev_minor = 0;
            gamestate->nums.pending_minor = 0;

            var_r3_2 = findSceneMatching(temp_r3);

            gm_801A4014(var_r3_2);
            if (!gmMainLib_8046B0F0.resetting) {
                gm_80479D30.nums = gm_80479D30.nums2;
            }
        } else {
            gm_801A4014(major_scene);
        }
    }
    if (!gmMainLib_8046B0F0.resetting && major_scene->Unload != NULL) {
        major_scene->Unload();
    }
    return gm_80479D30.nums.pending_major;
}

// UnclePunch: Scene_Main
void gm_801A4510(void)
{
    u32 unused;
    MajorScene* major_scenes;
    GameState* gamestate = &gm_80479D30;
    int i;

    gm_801A50AC();
    memzero(&gm_80479D30, sizeof(GameState));
    major_scenes = gm_801A50AC();
    for (i = 0; major_scenes[i].idx != MJ_COUNT; i++) {
        if (major_scenes[i].Init != NULL) {
            major_scenes[i].Init();
        }
    }
    if (VIGetDTVStatus() != 0 &&
        (db_gameLaunchButtonState & 0x200 || OSGetProgressiveMode() == 1))
    {
        gm_80479D30.nums.curr_major = MJ_PROGRESSIVE_SCAN;
    } else {
        gm_80479D30.nums.curr_major = MJ_BOOT;
    }
    gm_80479D30.nums.prev_major = MJ_COUNT;

    while (true) {
        u8 major = gm_801A43A0(gm_80479D30.nums.curr_major);
        if (gmMainLib_8046B0F0.resetting) {
            gmMainLib_8046B0F0.resetting = false;
        }
        gamestate->nums.prev_major = gamestate->nums.curr_major;
        gamestate->nums.curr_major = major;
    }
}
