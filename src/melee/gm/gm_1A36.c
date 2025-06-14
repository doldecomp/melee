#include <placeholder.h>

#include "gm/gm_1A36.static.h"

#include "gm_1A36.h"
#include "gmmain_lib.h"
#include "types.h"

#include "baselib/fog.h"
#include "baselib/gobjgxlink.h"
#include "baselib/gobjobject.h"
#include "baselib/gobjproc.h"
#include "baselib/lobj.h"
#include "baselib/memory.h"
#include "baselib/random.h"
#include "baselib/sislib.h"
#include "db/db.h"
#include "ef/efasync.h"
#include "ef/eflib.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "lb/lbarchive.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbbgflash.h"
#include "lb/lbcardgame.h"
#include "lb/lbdvd.h"
#include "lb/lblanguage.h"
#include "lb/lbmthp.h"
#include "lb/lbsnap.h"
#include "lb/types.h"
#include "mn/mngallery.h"
#include "mn/types.h"
#include "ty/toy.h"
#include "un/un_2FC9.h"

#include <dolphin/dvd.h>
#include <dolphin/os/OSRtc.h>
#include <dolphin/vi.h>
#include <baselib/controller.h>
#include <baselib/devcom.h>
#include <baselib/sobjlib.h>
#include <baselib/video.h>

u64 gm_801A3680(u8 idx)
{
    return gm_80479C30[(u8) idx].button;
}

u64 gm_801A36A0(u8 idx)
{
    return gm_80479C30[(u8) idx].trigger;
}

u64 gm_801A36C0(u8 idx)
{
    return gm_80479C30[(u8) idx].unk;
}

void gm_801A36E0(s32 idx, s32 arg1)
{
    if (idx == 4) {
        gm_80479C30[0].x28 = arg1;
        gm_80479C30[1].x28 = arg1;
        gm_80479C30[2].x28 = arg1;
        gm_80479C30[3].x28 = arg1;
        return;
    }
    gm_80479C30[idx].x28 = arg1;
}

void gm_801A3714(s32 idx, u64 arg1, u64 arg2)
{
    if (arg1 & gm_80479C30[idx].button) {
        gm_80479C30[idx].button |= arg2;
    }
    if (arg1 & gm_80479C30[idx].repeat) {
        gm_80479C30[idx].repeat |= arg2;
    }
    if (arg1 & gm_80479C30[idx].trigger) {
        gm_80479C30[idx].trigger |= arg2;
    }
    if (arg1 & gm_80479C30[idx].release) {
        gm_80479C30[idx].release |= arg2;
    }
}

void gm_801A3820(s32 idx, u64 arg1, u64 arg2)
{
    u64 val;
    if (arg1 == (arg1 & gm_80479C30[idx].button)) {
        gm_80479C30[idx].button |= arg2;
    }
    if (arg1 == (arg1 & gm_80479C30[idx].repeat)) {
        gm_80479C30[idx].repeat |= arg2;
    }
    if (arg1 == (arg1 & gm_80479C30[idx].button)) {
        if (arg1 & gm_80479C30[idx].trigger) {
            gm_80479C30[idx].trigger |= arg2;
        }
    }
    if (arg1 == (arg1 & gm_80479C30[idx].button)) {
        if (arg1 & gm_80479C30[idx].release) {
            gm_80479C30[idx].release |= arg2;
        }
    }
}

void fn_801A396C(int idx)
{
    if (gm_80479C30[idx].button || gm_80479C30[idx].release) {
        gm_80479C30[idx].unk = gm_80479C30[idx].button;
        gm_80479C30[idx].x28 = gm_80479D24;
        gm_80479C30[idx].x2C = 0;
    }
    if (gm_80479C30[idx].x2C < gm_80479D24) {
        gm_80479C30[idx].x2C++;
    }
    if (gm_80479C30[idx].x28 != 0) {
        gm_80479C30[idx].x28--;
        gm_80479C30[idx].unk = 0;
    }
}

#pragma push
#pragma dont_inline on
void gm_801A3A74(void)
{
    gm_controller_map* controller = gm_80479C30;
    int i;
    for (i = 0; i < 4; i++) {
        controller->button = HSD_PadCopyStatus[i].button;
        controller->trigger = HSD_PadCopyStatus[i].trigger;
        controller->repeat = HSD_PadCopyStatus[i].repeat;
        controller->release = HSD_PadCopyStatus[i].release;
        gm_801A3714(i, 0x1100, ((u64) 1 << (32 + 0)));
        gm_801A3714(i, 0x200, ((u64) 1 << (32 + 1)));
        gm_801A3820(i, 0x1060, ((u64) 1 << (32 + 2)));
        gm_801A3820(i, 0x1160, ((u64) 1 << (32 + 3)));
        gm_801A3714(i, 0x10008, ((u64) 1 << (32 + 4)));
        gm_801A3714(i, 0x20004, ((u64) 1 << (32 + 5)));
        gm_801A3714(i, 0x40001, ((u64) 1 << (32 + 6)));
        gm_801A3714(i, 0x80002, ((u64) 1 << (32 + 7)));
        gm_80479D20(i);
        controller++;
    }
    controller_union.button = 0;
    controller_union.trigger = 0;
    controller_union.repeat = 0;
    controller_union.release = 0;
    controller_union.unk = 0;
    controller_union.x28 = 0;
    controller_union.x2C = 0;
    for (i = 0; i < 4; i++) {
        controller_union.button |= gm_80479C30[i].button;
        controller_union.trigger |= gm_80479C30[i].trigger;
        controller_union.repeat |= gm_80479C30[i].repeat;
        controller_union.release |= gm_80479C30[i].release;
    }
}
#pragma pop

/// #gm_801A3E88

/// #gm_801A3EF4

/// #gm_801A3F48

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

void gm_801A4014(MajorScene* scene)
{
    MinorScene* var_r27;
    MinorSceneHandler* temp_r26;
    struct MinorSceneInfo* temp_r25;
    u32 unused[2];

    var_r27 = getScene(scene->minor_scenes);

    gm_80479D30.nums.curr_minor = var_r27->idx;

    gm_801A3F48(var_r27);
    if (var_r27->Prep != NULL) {
        var_r27->Prep(var_r27);
    }
    temp_r25 = &var_r27->info;
    temp_r26 = gm_801A4CE0(var_r27->info.class_id);
    gm_801A4BD4();
    gm_801A4B88(temp_r25);
    if (temp_r26->OnLoad != NULL) {
        temp_r26->OnLoad(temp_r25->unk_struct_0);
    }
    gm_801A4D34(temp_r26->OnFrame, temp_r25);
    if (gmMainLib_8046B0F0.x4 == 0 && temp_r26->OnLeave != NULL) {
        temp_r26->OnLeave(temp_r25->unk_struct_1);
    }
    if (gmMainLib_8046B0F0.x4 == 0) {
        if (var_r27->Decide != NULL) {
            var_r27->Decide(var_r27);
        }

        gm_80479D30.nums.prev_minor = gm_80479D30.nums.curr_minor;

        if (gm_80479D30.nums.pending_minor) {
            gm_80479D30.nums.curr_minor = gm_80479D30.nums.pending_minor - 1;
            gm_80479D30.nums.pending_minor = 0;
        } else {
            gm_80479D30.nums.curr_minor = matchMinor(scene->minor_scenes);
        }
    }
    lb_8001CDB4();
    lb_8001B760(0xB);
    lbMthp_8001F800();
    if (gmMainLib_8046B0F0.x4 != 0) {
        lbAudioAx_80027DBC();
        HSD_PadReset();
        while (lb_8001B6F8() == 0xB)
            ;
        if (DVDCheckDisk() == 0) {
            OSResetSystem(1, 0, 0);
        }
        lbMthp_8001F800();
        while (HSD_DevComIsBusy(1) != 0)
            ;
        gmMainLib_8015FBA4();
        gm_801A50AC();
        memzero(&gm_80479D30, 0x14);
        gm_801A3EF4();
        gmMainLib_8046B0F0.x0 = 1;
        gm_801A42F8(0x28);
        HSD_VISetBlack(0);
    }
}

void* gm_801A427C(MinorScene* scene)
{
    return scene->info.unk_struct_0;
}

void* gm_801A4284(MinorScene* scene)
{
    return scene->info.unk_struct_1;
}

void gm_SetSceneMinor(u8 arg0)
{
    gm_80479D30.nums.curr_minor = arg0;
    gm_80479D30.nums.prev_minor = arg0;
}

void gm_SetScenePendingMinor(int pending_minor)
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

void gm_801A42E8(s8 arg0)
{
    M2C_FIELD(&gm_80479D30, s8*, 1) = arg0;
}

void gm_801A42F8(int arg0)
{
    gm_80479D30.nums.pending_major = arg0;
    gm_80479D30.pending = 1;
}

u8 gm_801A4310(void)
{
    return ((u8*) &gm_80479D30)[0];
}

u8 gm_801A4320(void)
{
    return gm_80479D30.nums.prev_major;
}

void gm_801A4330(u8 (*arg0)())
{
    gm_80479D30.data = arg0;
}

bool gm_801A4340(u8 arg0)
{
    switch (arg0) {
        case 0x3:
        case 0x4:
        case 0x5:
        case 0xF:
        case 0x1C:
        case 0x20:
        case 0x21:
        case 0x22:
        case 0x23:
        case 0x24:
        case 0x25:
        case 0x26:
        case 0x2B:
            return true;
    }
    return false;
}

inline MajorScene* findSceneMatching(u8 idx)
{
    MajorScene* cur;
    for (cur = gm_801A50AC(); cur->idx != 45; cur++) {
        if (cur->idx == idx) {
            return cur;
        }
    }
    return NULL;
}

u8 gm_801A43A0(u8 arg0)
{
    u8 temp_r3;
    MajorScene* var_r30;
    MajorScene* var_r3_2;
    GameState* gamestate = &gm_80479D30;
    u64 unused;

    var_r30 = findSceneMatching(arg0);

    gm_80479D30.pending = 0;
    gm_80479D30.nums.curr_minor = 0;
    gm_80479D30.nums.prev_minor = 0;
    gm_80479D30.nums.pending_minor = 0;
    lbDvd_80018F58(var_r30->preload);
    if (var_r30->Load != NULL) {
        var_r30->Load();
    }
    while (!gamestate->pending) {
        if (gm_80479D30.data != NULL &&
            (temp_r3 = gm_80479D30.data(), temp_r3 != 45))
        {
            gm_80479D30.nums2 = gm_80479D30.nums;
            gamestate->pending = 0;
            gamestate->nums.curr_minor = 0;
            gamestate->nums.prev_minor = 0;
            gamestate->nums.pending_minor = 0;

            var_r3_2 = findSceneMatching(temp_r3);

            gm_801A4014(var_r3_2);
            if (gmMainLib_8046B0F0.x4 == 0) {
                gm_80479D30.nums = gm_80479D30.nums2;
            }
        } else {
            gm_801A4014(var_r30);
        }
    }
    if (gmMainLib_8046B0F0.x4 == 0 && var_r30->Unload != NULL) {
        var_r30->Unload();
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
    for (i = 0; major_scenes[i].idx != 0x2D; i++) {
        if (major_scenes[i].Init != NULL) {
            major_scenes[i].Init();
        }
    }
    if (VIGetDTVStatus() != NULL &&
        (db_gameLaunchButtonState & 0x200 || OSGetProgressiveMode() == 1))
    {
        gm_80479D30.nums.curr_major = 0x27;
    } else {
        gm_80479D30.nums.curr_major = 0x28;
    }
    gm_80479D30.nums.prev_major = 0x2D;

    while (true) {
        u8 major = gm_801A43A0(gm_80479D30.nums.curr_major);
        if (gmMainLib_8046B0F0.x4 != 0) {
            gmMainLib_8046B0F0.x4 = 0;
        }
        gamestate->nums.prev_major = gamestate->nums.curr_major;
        gamestate->nums.curr_major = major;
    }
}
