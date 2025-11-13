#include "gmtou.h"

#include "gm/gmtou.static.h"

#include "placeholder.h"

#include "mn/mnmain.h"

#include <melee/pl/forward.h>

#include <sysdolphin/baselib/controller.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/random.h>
#include <sysdolphin/baselib/sislib.h>
#include <melee/gm/gm_18A5.h>
#include <melee/gm/types.h>
#include <melee/lb/lbarchive.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lbdvd.h>
#include <melee/lb/types.h>
#include <melee/sc/types.h>

// Filename is just a guess, based on some strings in the file
// Seems to be Tournament game code

extern TmBoxArrays* lbl_804771B8;
extern HSD_Archive* lbl_804D6638;
extern HSD_Archive* lbl_804D6660;
extern HSD_Archive* lbl_804D6664;
extern HSD_Archive* lbl_804D6668;
extern SceneDesc* lbl_804D666C;
extern SceneDesc* lbl_804D6670;
extern SceneDesc* lbl_804D6674;
extern u8 lbl_804D6680[8];
static struct TmAnimTimers lbl_80479A58;
extern HSD_Archive* lbl_804D6688;
extern HSD_Archive* lbl_804D668C;

static inline TmData* GetTmData(void)
{
    return gm_8018F634();
}

void gm_8019B8C4_OnEnter(void* arg0)
{
    lbl_804D6668 = NULL;
    lbl_804D6664 = NULL;
    lbl_804D6680[0] = 0;
    lbl_804D6680[2] = 0;
    gm_8018F634();
    lbl_804D6660 = lbArchive_80016DBC("GmTou1p", &lbl_804D666C,
                                      "ScGamTour_scene_data", 0);
    lbl_804D6638 = lbArchive_80016DBC(
        "TmBox.dat", lbl_804771B8->box2, "tournament_box2_array",
        lbl_804771B8->box3, "tournament_box3_array", lbl_804771B8->box4,
        "tournament_box4_array", 0);
    lbl_804D6664 = lbArchive_80016DBC("GmTou3p", &lbl_804D6670,
                                      "ScGamTour_scene_data", 0);
    lbl_804D6668 = lbArchive_80016DBC("GmTou4p", &lbl_804D6674,
                                      "ScGamTour_scene_data", 0);
    HSD_SisLib_803A62A0(0, fn_8018F5F0(), "SIS_TournamentData");
    if (HSD_Randi(2) != 0) {
        lbAudioAx_80023F28(0x5D);
        return;
    }
    lbAudioAx_80023F28(0x5E);
}

void gm_8019B9C8_OnLeave(void* arg0)
{
    lbArchive_80016EFC(lbl_804D6660);
    lbArchive_80016EFC(lbl_804D6638);
    lbArchive_80016EFC(lbl_804D6664);
    lbArchive_80016EFC(lbl_804D6668);
}

void fn_8019BA04(void) {}

/// #fn_8019BA08

void fn_8019BF18(HSD_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);

    if (lbl_80479A58.x4 > 800) {
        lbl_80479A58.x4 = 0;
    }

    fn_8019044C(jobj, lbl_80479A58.x4);
    lbl_80479A58.x4++;
}

void fn_8019BF8C(HSD_GObj* gobj)
{
    s32 selection;
    HSD_JObj* jobj;

    selection = gm_8018F634()->x0;
    jobj = GET_JOBJ(gobj);
    if ((selection <= 0x1A) || (selection >= 0x1F)) {
        if (lbl_80479A58.xE > 0x77U) {
            lbl_80479A58.xE = 0x5A;
        }
    } else if ((selection <= 0x1E) && (lbl_80479A58.xE > 0x9FU)) {
        lbl_80479A58.xE = 0x82;
    }

    fn_8019044C(jobj, lbl_80479A58.xE);
    lbl_80479A58.xE++;
}

/// #fn_8019C048

void fn_8019C3EC(HSD_GObj* gobj)
{
    s32 idx;
    f32 var_f1;
    TmData* tmd;
    HSD_JObj* jobj;

    tmd = gm_8018F634();
    idx = fn_8018F62C(gobj);
    jobj = GET_JOBJ(gobj);
    if (HSD_PadMasterStatus[(u8) idx].err != 0) {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        return;
    }
    HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);

    if ((s32) tmd->x30 == 4) {
        var_f1 = (13.0f * idx) + -19.5f;
    } else if ((s32) tmd->x30 == 3) {
        var_f1 = 6.5f + ((13.0f * idx) - 19.5f);
    } else {
        var_f1 = 6.5f + ((13.0f * (2.0f * idx)) - 19.5f);
    }
    fn_8018FDC4(jobj, 4.5f + var_f1, 3.0f, 666.0f);
    if (lbl_80479A58.x20[idx].x0 == 4) {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
    }
    fn_8019BA08(idx, jobj);
}

void fn_8019C570(HSD_GObj* gobj)
{
    u64 idx;
    HSD_JObj* jobj;
    TmData* tmd = GetTmData();

    idx = fn_8018F62C(gobj);
    jobj = GET_JOBJ(gobj);
    if (HSD_PadMasterStatus[(u8) idx].err != 0) {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        return;
    }
    HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
    if (lbl_80479A58.x20[idx].x0 == 4) {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
    }
    if (tmd->x4B8[idx].x2 != 0) {
        jobj = HSD_JObjGetChild(jobj);
        jobj = HSD_JObjGetNext(jobj);
        fn_8019044C(jobj, 201.0f);
        return;
    }
    jobj = HSD_JObjGetChild(jobj);
    jobj = HSD_JObjGetNext(jobj);
    fn_8019044C(jobj, fn_8018F71C(tmd->x4B8[idx].x1, tmd->x4B8[idx].x3));
}

void fn_8019C6AC(HSD_GObj* gobj)
{
    HSD_JObj* jobj;
    TmData* unused = GetTmData();

    jobj = GET_JOBJ(gobj);

    if (lbl_80479A58.xF > 60) {
        lbl_80479A58.xF = 60;
    }

    fn_8019044C(jobj, (lbl_80479A58.xF + gm_804771C4.x4 * 100 + 100));
    lbl_80479A58.xF++;
}

/// #fn_8019C744

void fn_8019CA38(HSD_GObj* gobj)
{
    s32 idx;
    f32 var_f1;
    HSD_JObj* jobj;
    TmData* tmd;

    tmd = gm_8018F634();
    idx = fn_8018F62C(gobj);
    jobj = GET_JOBJ(gobj);
    if (HSD_PadMasterStatus[(u8) idx].err != 0) {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        return;
    }

    HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
    if ((s32) tmd->x30 == 4) {
        var_f1 = (13.0f * (s32) idx) + -19.5f;
    } else if ((s32) tmd->x30 == 3) {
        var_f1 = 6.5f + ((13.0f * (s32) idx) - 19.5f);
    } else {
        var_f1 = 6.5f + ((13.0f * (2.0f * (s32) idx)) - 19.5f);
    }
    fn_8018FDC4(jobj, var_f1, 666.0f, 666.0f);
    if (lbl_80479A58.x20[idx].x0 == 2) {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
    }

    if ((u32) lbl_80479A58.x6[idx] < 600) {
        lbl_80479A58.x6[idx]++;
    } else {
        lbl_80479A58.x6[idx] = 0;
    }
    fn_8019044C(jobj, lbl_80479A58.x6[idx]);
}

void fn_8019CBFC(HSD_GObj* gobj)
{
    TmData* unused = GetTmData();
    HSD_JObj* jobj = GET_JOBJ(gobj);

    fn_8019044C(jobj, lbl_80479A58.x1C + 0x14);
    if (lbl_80479A58.x1C < 0xAU) {
        lbl_80479A58.x1C++;
    }
}

void fn_8019CC74(HSD_GObj* gobj)
{
    s32 idx;
    f32 var_f1;
    TmData* tmd;
    HSD_JObj* jobj;

    tmd = gm_8018F634();
    idx = fn_8018F62C(gobj);
    jobj = GET_JOBJ(gobj);
    if (HSD_PadMasterStatus[(u8) idx].err == 0) {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        return;
    }
    HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);

    if ((s32) tmd->x30 == 4) {
        var_f1 = (13.0f * (f32) idx) + -19.5f;
    } else if ((s32) tmd->x30 == 3) {
        var_f1 = 6.5f + ((13.0f * (f32) idx) - 19.5f);
    } else {
        var_f1 = 6.5f + ((13.0f * (2.0f * (f32) idx)) - 19.5f);
    }
    fn_8018FDC4(jobj, var_f1, 666.0f, 0.01f);
}

void fn_8019CDBC(HSD_GObj* gobj)
{
    f32 sp28;
    f32 sp24;
    u8 temp_r27;
    TmData* tmd = gm_8018F634();
    HSD_JObj* jobj = GET_JOBJ(gobj);
    u32 idx = fn_8018F62C(gobj);
    PAD_STACK(20);

    HSD_ASSERT(993, jobj);
    sp28 = jobj->translate.x;
    temp_r27 = tmd->x37[idx].xC;
    sp24 = (5.999997f * temp_r27) - 21.5f;
    mn_8022F410(&sp28, &sp24, 0.4f);

    switch (mn_8022F410(&sp28, &sp24, 0.2f)) {
    case 1:
        fn_8018FDC4(jobj, sp28, 19.5f, -6.0f);
        HSD_SisLib_803A746C(tmd->x534[idx], 0, 10.0f * sp28, -197.0f);
        tmd->x534[idx]->pos_z = -6.0f;
        break;
    case -1:
        fn_8018FDC4(jobj, sp28, 15.0f, 6.0f);
        HSD_SisLib_803A746C(tmd->x534[idx], 0, 10.0f * sp28, -152.0f);
        tmd->x534[idx]->pos_z = 6.0f;
        break;
    default:
    case 0:
        tmd->x37[idx].xD = temp_r27;
        fn_8018FDC4(jobj, sp28, 17.0f, 0.01f);
        HSD_SisLib_803A746C(tmd->x534[idx], 0, 10.0f * sp28, -172.0f);
        tmd->x534[idx]->pos_z = 0.01f;
        break;
    }
    if (tmd->x37[idx].x4 != 0) {
        fn_8019044C(jobj, 201.0f);
        return;
    }
    fn_8019044C(jobj, fn_8018F71C(tmd->x37[idx].x2, tmd->x37[idx].x6));
}

void fn_8019CFA4(HSD_GObj* gobj)
{
    TmData* data;
    HSD_JObj* jobj;

    data = GetTmData();
    /// @todo is there a different inline here? seems cursed
    jobj = HSD_JObjGetNext(HSD_JObjGetNext(HSD_JObjGetChild(GET_JOBJ(gobj))));
    // jobj = GET_JOBJ(gobj);

    // jobj = HSD_JObjGetChild(jobj);
    // jobj = HSD_JObjGetNext(jobj);

    // if (jobj == NULL) {
    //     jobj = NULL;
    // } else {
    //     jobj = jobj->next;
    // }

    fn_8019044C(jobj, data->x2E);
    jobj = HSD_JObjGetNext(jobj);
    fn_8019044C(jobj, data->x30);
}

void fn_8019D074(HSD_GObj* gobj)
{
    s32 idx;
    f32 var_f1;
    TmData* tmd;
    HSD_JObj* jobj;

    tmd = gm_8018F634();
    idx = fn_8018F62C(gobj);
    jobj = GET_JOBJ(gobj);
    if (HSD_PadMasterStatus[(u8) idx].err != 0) {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        return;
    }
    HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
    if ((s32) tmd->x30 == 4) {
        var_f1 = (13.0f * idx) + -19.5f;
    } else if ((s32) tmd->x30 == 3) {
        var_f1 = 6.5f + ((13.0f * idx) - 19.5f);
    } else {
        var_f1 = 6.5f + ((13.0f * (2.0f * idx)) - 19.5f);
    }
    fn_8018FDC4(jobj, var_f1, 666.0f, 666.0f);
}

/// #fn_8019D1BC

/// #fn_8019DD60

/// #gm_8019DF8C_OnFrame

/// #gm_8019E634

/// #gm_8019ECAC_OnEnter

void gm_8019EE54_OnLeave(void* arg0)
{
    lbArchive_80016EFC(lbl_804D6688);
    lbArchive_80016EFC(lbl_804D668C);
}

void fn_8019EE80(TmVsData* arg0)
{
    struct GameCache* game_cache;
    s32 i;

    game_cache = &lbDvd_8001822C()->game_cache;
    for (i = 0; i < gm_8018F634()->x30; i++) {
        game_cache->entries[i].char_id = arg0->char_id[i];
        game_cache->entries[i].color = arg0->color[i];
    }

    if (!fn_80196594(gm_8018F634())) {
        game_cache->stage_id = arg0->stage_id;
    }

    lbDvd_80018254();
}

void fn_8019EF08(TmVsData* arg0)
{
    struct GameCache* game_cache;
    s32 i;

    game_cache = &lbDvd_8001822C()->game_cache;
    for (i = 0; i < 4; i++) {
        if (arg0->slot_type[i] != Gm_PKind_NA) {
            game_cache->entries[i].char_id = arg0->char_id[i];
            game_cache->entries[i].color = arg0->color[i];
        }
    }

    lbDvd_80018254();
}
