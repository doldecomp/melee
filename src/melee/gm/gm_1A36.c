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

bool gm_801A45E8(int bit)
{
    return gm_80479D58.unk_10 & (1ULL << bit);
}


u8 gm_801A4624(void)
{
    return gm_80479D58.unk_10;
}

void gm_801A4634(int bit)
{
    gm_80479D58.unk_10 |= 1ULL << bit;
}

void gm_801A4674(int bit)
{
    gm_80479D58.unk_10 &= ~(1ULL << bit);
}

bool gm_801A46B8(int bit)
{
    return gm_80479D58.unk_12 & (1ULL << bit);
}

bool fn_801A46F4(void)
{
    int i;
    for (i = 0; i < 4; i++) {
        HSD_PadStatus* pad = &HSD_PadMasterStatus[(u8) i];
        if (pad->err == 0 && (pad->trigger & 8) && (pad->button & HSD_PAD_X)) {
            return true;
        }
    }
    return false;
}

bool fn_801A47E4(void)
{
    int i;
    for (i = 0; i < 4; i++) {
        HSD_PadStatus* pad = &HSD_PadMasterStatus[(u8) i];
        if (pad->err == 0 && (pad->trigger & 0x10)) {
            return true;
        }
    }
    return false;
}

/// #gm_801A48A4

/// #gm_801A4970

void gm_801A4B08(UNK_T arg0, UNK_T arg1)
{
    gm_80479D58.unk_14 = arg0;
    gm_80479D58.unk_18 = arg1;
}

/// #gm_801A4B1C

void gm_801A4B40(s32 arg0)
{
    M2C_FIELD(&gm_80479D58, s32*, 0x30) = arg0;
}

void gm_801A4B50(s32 arg0)
{
    M2C_FIELD(&gm_80479D58, s32*, 0x34) = arg0;
}

void gm_801A4B60(void)
{
    gm_80479D58.unk_C = 1;
}

void gm_801A4B74(void)
{
    gm_80479D58.unk_C = 2;
}

void gm_801A4B88(struct MinorSceneInfo* info)
{
    gm_804D6720 = info;
}

void* gm_801A4B90(void)
{
    return gm_804D6720->unk_struct_0;
}

void* gm_801A4B9C(void)
{
    return gm_804D6720->unk_struct_1;
}

struct gm_80479D58_t* gm_801A4BA8(void)
{
    return gm_80479D58.unk_0;
}

s32 gm_801A4BB8(void)
{
    return gm_80479D58.unk_8;
}

HSD_GObj* gm_801A4BC8(void)
{
    return gm_804D672C;
}

void fn_801A4BD0(HSD_GObj*) {}

// fully matching when file data sections are split properly
// (this file's bss starts at gm_80479D48)
void gm_801A4BD4(void)
{
    PAD_STACK(0x18);

    gm_80479D58.unk_14 = fn_801A46F4;
    gm_80479D58.unk_18 = fn_801A47E4;
    gm_80479D58.unk_30 = 0;
    gm_80479D58.unk_34 = 0;

    lb_80019880(1.0F/60 * OS_TIMER_CLOCK);
    HSD_GObj_803912E0(&gm_80479D48);
    gm_80479D48.gproc_pri_max = 0x18;
    HSD_SObjLib_804D7960 = HSD_GObj_803912A8(&gm_80479D48, &HSD_SObjLib_8040C3A4);
    HSD_SObjLib_803A44A4();
    gm_80479D48.unk_2 = &gm_80479D58.unk_28;
    HSD_GObj_80391304(&gm_80479D48);
    hsd_80392474();
    un_802FF78C();
    gm_804D672C = GObj_Create(14, 0, 0);
    if (gm_804D672C != NULL) {
        HSD_GObjProc_8038FD54(gm_804D672C, fn_801A4BD0, 0);
    }
    gm_804D6728 = 0;
    gm_804D6724 = 0;
    gm_801A3E88();
    lbAudioAx_8002835C();
    lb_80014534();
}

MinorSceneHandler* gm_801A4CE0(u8 id)
{
    MinorSceneHandler* cur;
    for (cur = gm_801A50A0(); cur->class_id != 0x2D; cur++) {
        if (cur->class_id == id) {
            return cur;
        }
    }
    return NULL;
}

/// #gm_801A4D34

MinorSceneHandler* gm_801A50A0(void)
{
    return gm_803DA920;
}

MajorScene* gm_801A50AC(void)
{
    return &gm_803DACA4;
}

/// #gm_801A50B8

/// #gm_801A5130

/// #gm_801A51A8

/// #gm_801A5220

s8* gm_801A5244(void)
{
    return &gmMainLib_804D3EE0->unk_590;
}

UNK_T gm_801A5250(void)
{
    return &gm_804D6730;
}

/// #gm_801A5258

/// #gm_801A52D0

/// #gm_801A5360

/// #gm_801A5598

/// #gm_801A55C4

/// #gm_801A55EC

void gm_801A5614(void) {}

/// #gm_801A5618

/// #gm_801A5680

/// #gm_801A5754

/// #gm_801A57A8

/// #gm_801A583C

/// #gm_801A5AF0

/// #gm_801A5C3C

/// #gm_801A5EC8

/// #gm_801A5F00

/// #gm_801A5F64

/// #gm_801A6254

/// #gm_801A6308

/// #gm_801A632C

/// #gm_801A637C

/// #gm_801A64A8

/// #gm_801A659C

/// #gm_801A6630

/// #fn_801A6664

/// #fn_801A6844

/// #fn_801A6868

/// #gm_801A68D8

/// #fn_801A6A48

/// #fn_801A6ACC

/// #fn_801A6B6C

/// #fn_801A6C30

/// #gm_801A6C54

/// #fn_801A6D78

/// #gm_801A6DC0

/// #gm_801A6EE4

/// #gm_801A7070

/// #gm_801A79D4

/// #fn_801A7A44

/// #fn_801A7A68

/// #fn_801A7A8C

/// #gm_801A7B00

/// #fn_801A7FB4

/// #fn_801A80CC

/// #fn_801A80F0

/// #gm_801A8114

/// #fn_801A851C

/// #gm_801A85E4

/// #gm_801A8D54

/// #gm_801A9094

/// #fn_801A9498

/// #fn_801A94BC

/// #gm_801A9630

/// #gm_801A9B30

/// #gm_801A9D0C

/// #gm_801A9DD0

/// #fn_801A9FCC

/// #fn_801AA0E8

/// #gm_801AA110

/// #gm_801AA28C

/// #gm_801AA644

/// #gm_801AA664

/// #gm_801AA688

/// #gm_801AA6D8

/// #gm_801AA6FC

/// #gm_801AA774

/// #gm_801AA7C4

/// #fn_801AA7F8

/// #fn_801AA854

/// #fn_801AAA28

/// #fn_801AAABC

/// #fn_801AAB18

/// #fn_801AAB74

/// #fn_801AB200

/// #fn_801AC67C

void gm_801AC6D8(void)
{
    HSD_JObj* jobj_arr[2];
    int const gx_link = 11;

    efLib_8005B4B8();
    efAsync_8006737C(0);
    gm_804D67F8 = HSD_MemAlloc(sizeof(struct gm_804D67F8_t));
    gm_804D67FC = HSD_MemAlloc(sizeof(struct gm_804D67FC_t));
    HSD_SisLib_803A62A0(0, "SdStRoll.dat", "SIS_StRollData");
    HSD_SisLib_803A611C(0, -1, 9, 13, 0, 18, 0, 19);
    lbAudioAx_8002702C(16, lbAudioAx_80026F2C(28));
    lbAudioAx_80027168();
    gm_804D683C = lbArchive_80016DBC(
        "GmStRoll.dat", (void**) &gm_804D6840, "ScGamRegStaffroll_scene_data",
        &gm_804D6844, "ScGamRegStaffrollNames_scene_modelset", 0);
    {
        HSD_GObj* gobj = GObj_Create(17, 19, 0);
        HSD_CObj* cobj = HSD_CObjLoadDesc(gm_804D6840->cameras->desc);
        gm_804D6830 = cobj;
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784B, gm_804D6830);
        GObj_SetupGXLinkMax(gobj, fn_801AA854, 5);
        gobj->gxlink_prios = 0x189;
        HSD_CObjAddAnim(cobj, gm_804D6840->cameras->anims[0]);
        HSD_CObjReqAnim(cobj, 0.0f);
        HSD_GObjProc_8038FD54(gobj, fn_801AA7F8, 0);
    }
    {
        HSD_GObj* gobj = GObj_Create(19, 20, 0);
        HSD_CObj* cobj = HSD_CObjLoadDesc(&gm_803DD0F0);
        gm_804D6834 = cobj;
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784B, cobj);
        GObj_SetupGXLinkMax(gobj, fn_801AAA28, 8);
        gobj->gxlink_prios = 1LL << gx_link;
    }
    {
        HSD_GObj* gobj = GObj_Create(gx_link, 3, 0);
        HSD_LObj* lobj = lb_80011AC4(gm_804D6840->lights);
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784A, lobj);
        GObj_SetupGXLink(gobj, HSD_GObj_LObjCallback, 0, 0);
        HSD_LObjReqAnimAll(lobj, 0.0f);
        HSD_GObjProc_8038FD54(gobj, fn_801AAABC, 0);
    }
    {
        HSD_GObj* gobj = GObj_Create(0xA, 3, 0);
        HSD_Fog* fog = HSD_FogLoadDesc(gm_804D6840->fogs->desc);
        gm_804D6838 = fog;
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7848, fog);
        GObj_SetupGXLink(gobj, HSD_GObj_FogCallback, 3, 0);
        HSD_Fog_8037DE7C(fog, gm_804D6840->fogs->anims[0][0]);
        HSD_FogReqAnim(fog, 0.0f);
        HSD_GObjProc_8038FD54(gobj, fn_801AC67C, 0);
    }
    {
        HSD_GObj* gobj = GObj_Create(3, 5, 0);
        HSD_JObj* jobj = HSD_JObjLoadJoint(gm_804D6840->models[1][0]);
        gm_804D682C = jobj;
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
        GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 3, 0);
        gm_8016895C(jobj, gm_804D6840->models[1], 0);
        HSD_JObjReqAnimAll(jobj, 0.0f);
        {
            if (lbLang_IsSettingUS()) {
                lb_80011E24(jobj, jobj_arr, 103, 20, -1);
                M2C_FIELD(M2C_FIELD(M2C_FIELD(jobj_arr[0]->u.ptcl, void**, 8),
                                    void**, 8),
                          s32*, 0x58) =
                    M2C_FIELD(
                        M2C_FIELD(M2C_FIELD(jobj_arr[1]->u.ptcl, void**, 8),
                                  void**, 8),
                        s32*, 0x58);
            }
        }
        HSD_GObjProc_8038FD54(gobj, fn_801AAB18, 0);
    }
    {
        HSD_GObj* gobj = GObj_Create(14, 15, 0);
        HSD_JObj* jobj = HSD_JObjLoadJoint(gm_804D6844[0][0]);
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
        GObj_SetupGXLink(gobj, NULL, 9, 0);
        gm_8016895C(jobj, gm_804D6844[0], 0);
        HSD_JObjReqAnimAll(jobj, 0.0f);
        {
            ssize_t i;
            HSD_JObj* cur;
            /// @todo Length of #gm_804D6844 is 10
            for (i = 1; i < 10; i++) {
                HSD_JObj* jobj = HSD_JObjLoadJoint(gm_804D6844[i][0]);
                gm_8016895C(jobj, *gm_804D6844[i], 0);
                HSD_JObjReqAnimAll(jobj, 0.0f);
                {
                    for (cur = jobj->child; cur != NULL;) {
                        HSD_JObjReparent(cur, jobj);
                    }
                }
            }
        }
        HSD_GObjProc_8038FD54(gobj, fn_801AAB74, 1);
    }
    {
        HSD_GObj* gobj = GObj_Create(14, 15, 0);
        HSD_JObj* jobj = HSD_JObjLoadJoint(gm_804D6840->models[0][0]);
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
        GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, gx_link, 0);
        gm_8016895C(jobj, gm_804D6840->models[0], 0);
        lb_80011E24(jobj, jobj_arr, ARRAY_SIZE(jobj_arr), 20, -1);
        HSD_JObjReqAnimAll(jobj_arr[0], 0.0f);
        HSD_JObjReqAnimAll(jobj_arr[1], 0.0f);
        HSD_GObjProc_8038FD54(gobj, fn_801AB200, 13);
    }
    lbAudioAx_80027648();
    {
        s32 r = HSD_Randi(5);
        lbAudioAx_80023F28(lbAudioAx_8002305C(gm_801BEFB0(), -r == 0));
        lbBgFlash_800209F4();
        gm_804D6804->x0 = gm_804D6804->x4 = 0.0F;
        memzero(gm_804D67F8, sizeof(struct gm_804D67F8_t));
        gm_80480D58.x0 = 0;
        gm_80480D58.x4 = 0;
        gm_80480D58.x8 = 0;
        gm_80480D58.xC = 0;
        gm_80480D58.x10 = 0;
        gm_80480D58.x14 = 0;
        gm_804D680C = 0;
        gm_804D6810 = 0;
        gm_804D6814 = 0;
        gm_804D6818 = 0;
        gm_804D681C = 1;
        gm_804D6820 = 0;
        gm_804D6824 = gm_804D6828 = 0.0f;
        gm_804D6848 = 0;
        gm_804D684C = 0;
    }
}

void gm_801ACC90(void) {}

UNK_T gm_801ACC94(void)
{
    return &gm_803DD2C0;
}

/// #gm_801ACCA0

/// #gm_801ACD8C

/// #gm_801ACE94

/// #gm_801ACF8C

/// #gm_801AD088

/// #gm_801AD254

/// #gm_801AD620

/// #gm_801AD874

/// #gm_801AD8EC

/// #fn_801AD920

/// #gm_801ADB04

/// #gm_801ADC88

/// #gm_801ADCE4

/// #gm_801ADDA8

/// #gm_801ADDD8

void gm_801ADDD8(void)
{
    memzero(&gm_803DD4D0, sizeof(gm_803DD4D0));
    gm_803DD4D0.unkC = -0x3E7;
    gm_801AEBB0();
}

extern int gm_804D686C;

bool gm_801ADE1C(int arg0, int arg1, f32 arg2, f32 arg3)
{
    HSD_Text* text;
    struct unkd4d0* temp_r0;
    struct unkd4d0* next;
    struct unkd4d0* cur;

    cur = &gm_803DD4D0;
    next = HSD_MemAlloc(sizeof(struct unkd4d0));
    memzero(next, sizeof(struct unkd4d0));
    next->unkC = arg0;
    next->unk10 = arg1;
    next->unk14 = arg2;
    next->unk18 = arg3;

    for (; true; cur = cur->next) {

        if (cur->next != NULL) {
            continue;
        }

        cur->next = next;
        next->unk4 = cur;
        next->next = NULL;
        next->unk8 = NULL;
        next->unk1C = gm_801AECC4(1);
        if (next->unk1C != NULL) {
            HSD_JObjSetTranslateX(GET_JOBJ(next->unk1C), next->unk14);
        }
        if (next->unk1C != NULL) {
            HSD_JObjSetTranslateY(GET_JOBJ(next->unk1C), next->unk18);
        }
        next->unk20 = HSD_SisLib_803A5ACC(3, (s32) gm_804D686C, -14.0f + next->unk14, -9.0f - next->unk18, 0.0f, 30.8f, 4.6f);
        text = next->unk20;
        text->x34.x = 0.079f;
        text->x34.y = 0.079f;
        next->unk20->x4A = 0;
        next->unk20->x48 = 0;
        HSD_SisLib_803A6368(next->unk20, next->unk10);
        break;
    }

    return true;
}

/// #gm_801AE050

void gm_801AE44C(int arg0, float val)
{
    struct unkd4d0* cur;

    for (cur = gm_803DD4D0.next; cur != NULL; cur = cur->next) {
        if (cur->unkC == arg0) {
            HSD_JObj* jobj = GET_JOBJ(cur->unk1C);
            HSD_JObjAddTranslationY(jobj->child->child->child->next, -val);
        }
    }
}

void gm_801AE544(int arg0, float val)
{
    struct unkd4d0* cur;

    for (cur = gm_803DD4D0.next; cur != NULL; cur = cur->next) {
        if (cur->unkC == arg0) {
            HSD_JObj* jobj = GET_JOBJ(cur->unk1C);
            HSD_JObjAddTranslationY(jobj->child->child->child->next->child, -val);
        }
    }
}

/// #gm_801AE640

/// #gm_801AE74C

/// #gm_801AE848

/// #fn_801AE948

void gm_801AEBB0(void)
{
    HSD_GObj* gobj;
    PAD_STACK(4);

    lbArchive_80016DBC("NtMsgWin.dat", &gm_804D6868,
            "ScNtcCommon_scene_data", 0);

    if (lbLang_IsSavedLanguageUS()) {
        HSD_SisLib_803A62A0(3, "SdMsgBox.usd", "SIS_MessageData");
    } else {
        HSD_SisLib_803A62A0(3, "SdMsgBox.dat", "SIS_MessageData");
    }

    gobj = GObj_Create(20, 21, 0);
    {
        HSD_CObj* desc = HSD_CObjLoadDesc(gm_804D6868->cameras[0]);
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784B, desc);
    }
    GObj_SetupGXLinkMax(gobj, HSD_GObj_803910D8, 0);
    gobj->gxlink_prios = 0x4000;

    gm_804D686C = HSD_SisLib_803A611C(3, (u32) gobj, 9, 13, 0, 14, 0, 18);
    HSD_GObjProc_8038FD54(GObj_Create(15, 17, 0), fn_801AE948, 0);
}

HSD_GObj* gm_801AECC4(int model_idx)
{
    HSD_GObj* gobj = GObj_Create(9, 13, 0);
    HSD_JObj* jobj = HSD_JObjLoadJoint(gm_804D6868->models[model_idx]->joint);
    HSD_GObjObject_80390A70(gobj, (u8) HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 14, 0);
    gm_8016895C(jobj, gm_804D6868->models[model_idx], 0);
    HSD_JObjReqAnimAll(jobj, 0.0F);
    HSD_JObjAnimAll(jobj);
    if (model_idx == 1) {
        HSD_JObjSetFlagsAll(jobj->child->child->next->child->next, 0x10);
        HSD_JObjSetFlagsAll(jobj->child->child->next->next, 0x10);
    }
    return gobj;
}

static HSD_PadStatus* get_master_status(u8 i)
{
    return &HSD_PadMasterStatus[i];
}

static HSD_PadStatus* get_copy_status(u8 i)
{
    return &HSD_PadCopyStatus[i];
}

u32 gm_801AEDC8(void)
{
    u32 result = 0;
    int i;
    for (i = 0; i < 4; i++) {
        if (get_master_status(i)->err == 0) {
            result |= get_copy_status(i)->trigger;
        }
    }
    return result;
}
