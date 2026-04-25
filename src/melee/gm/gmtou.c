#include "gmtou.h"

#include "gm/gmtou.static.h"

#include "placeholder.h"

#include "baselib/fog.h"
#include "baselib/gobjgxlink.h"
#include "baselib/gobjobject.h"
#include "mn/mnmain.h"

#include <melee/pl/forward.h>

#include <dolphin/os.h>
#include <sysdolphin/baselib/controller.h>
#include <sysdolphin/baselib/dobj.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/mobj.h>
#include <sysdolphin/baselib/random.h>
#include <sysdolphin/baselib/sislib.h>
#include <melee/gm/gm_1601.h>
#include <melee/gm/gm_18A5.h>
#include <melee/gm/gm_1A3F.h>
#include <melee/gm/gm_1A45.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/gm/types.h>
#include <melee/lb/lbarchive.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lbdvd.h>
#include <melee/lb/types.h>
#include <melee/sc/types.h>

/// Filename is just a guess, based on some strings in the file
/// Seems to be Tournament game code

extern TmBoxArrays lbl_804771B8;
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
extern s32 lbl_804D663C;

struct lbl_803DA2E0_t {
    u8 x0[0x20];
    f32 x20[0x29];
};
extern struct lbl_803DA2E0_t lbl_803DA2E0;

extern MatchEnd gm_80477738;
extern s32 lbl_803B7D3C[4];
extern u8* lbl_804DA948;
s32 fn_80166CBC(void*, ssize_t);

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
        "TmBox.dat", &lbl_804771B8.box2, "tournament_box2_array",
        &lbl_804771B8.box3, "tournament_box3_array", &lbl_804771B8.box4,
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

void fn_8019BA04(s32* state) {}

void fn_8019BA08(u8 idx, HSD_JObj* jobj)
{
    TmData* tmd = gm_8018F634();
    s32 i;

    if (tmd->x4B8[idx].x2 != 0) {
        jobj = HSD_JObjGetChild(jobj);
        HSD_JObjSetTranslateZ(jobj, 10000.0f);
        for (i = 1; i <= 0xc; i++) {
            jobj = HSD_JObjGetNext(jobj);
            HSD_JObjSetTranslateZ(jobj, 10000.0f);
        }
        return;
    }

    jobj = HSD_JObjGetChild(jobj);
    HSD_JObjSetTranslateZ(jobj, 10000.0f);

    if (lbl_803DA2E0.x0[tmd->x4B8[idx].x1] == 0) {
        HSD_JObjSetTranslateZ(jobj, 0.0f);
        for (i = 1; i <= 0xc; i++) {
            jobj = HSD_JObjGetNext(jobj);
            HSD_JObjSetTranslateZ(jobj, 10000.0f);
        }
        return;
    }

    for (i = 1; i <= 0xc; i++) {
        jobj = HSD_JObjGetNext(jobj);
        HSD_JObjSetTranslateZ(jobj, 10000.0f);
        if (lbl_803DA2E0.x0[tmd->x4B8[idx].x1] == i) {
            s32 j;
            HSD_JObjSetTranslateZ(jobj, 0.0f);
            for (j = i + 1; j <= 12; j++) {
                jobj = HSD_JObjGetNext(jobj);
                HSD_JObjSetTranslateZ(jobj, 10000.0f);
            }
            return;
        }
    }
}

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

    selection = gm_8018F634()->cur_option;
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

extern s32 lbl_803B7D18[9];

void fn_8019C048(HSD_GObj* gobj)
{
    TmData* tmd;
    s32 idx;
    HSD_JObj* jobj;
    f32 x;
    u8 state;
    u8 start_frame, cur_frame, end_frame, loop_flag;
    s32 table[9];

    tmd = gm_8018F634();
    idx = fn_8018F62C(gobj);
    jobj = gobj->hsd_obj;

    table[0] = lbl_803B7D18[0];
    table[1] = lbl_803B7D18[1];
    table[2] = lbl_803B7D18[2];
    table[3] = lbl_803B7D18[3];
    table[4] = lbl_803B7D18[4];
    table[5] = lbl_803B7D18[5];
    table[6] = lbl_803B7D18[6];
    table[7] = lbl_803B7D18[7];
    table[8] = lbl_803B7D18[8];

    if ((s8) (u8) HSD_PadMasterStatus[(u8) idx].err != 0) {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        HSD_SisLib_803A7548(tmd->x524[2], (s32) idx, 0.0f, 0.0f);
        return;
    }

    HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);

    state = lbl_80479A58.x1D[idx].x0;
    if (state == 4) {
        HSD_SisLib_803A7548(tmd->x524[2], (s32) idx, 0.0f, 0.0f);
    } else {
        HSD_SisLib_803A7548(tmd->x524[2], (s32) idx, 1.0f, 1.0f);
    }

    {
        u8 players = tmd->x30;
        if ((s32) players == 4) {
            x = (13.0f * (f32) idx) + -19.5f;
        } else if ((s32) players == 3) {
            x = 6.5f + ((13.0f * (f32) idx) - 19.5f);
        } else {
            x = 6.5f + ((13.0f * (2.0f * (f32) idx)) - 19.5f);
        }
    }

    HSD_JObjSetTranslateX(jobj, x);

    tmd->x524[2]->hidden = 0;

    state = lbl_80479A58.x1D[idx].x0;
    lbl_80479A58.x1D[idx].a = ((u16*) table)[state * 3 + 0];
    lbl_80479A58.x1D[idx].c = ((u16*) table)[state * 3 + 1];
    lbl_80479A58.x1D[idx].x2 = ((u16*) table)[state * 3 + 2];

    start_frame = lbl_80479A58.x1D[idx].a;
    cur_frame = lbl_80479A58.x1D[idx].b;
    end_frame = lbl_80479A58.x1D[idx].c;
    loop_flag = lbl_80479A58.x1D[idx].x2;

    if (cur_frame < start_frame) {
        lbl_80479A58.x1D[idx].b = start_frame;
        cur_frame = start_frame;
    }

    if (cur_frame < end_frame) {
        lbl_80479A58.x1D[idx].b = (u8) (cur_frame + 1);
    } else {
        lbl_80479A58.x1D[idx].x1 = 1;
        if (loop_flag != 0) {
            lbl_80479A58.x1D[idx].b = start_frame;
        } else {
            lbl_80479A58.x1D[idx].b = end_frame;
        }
    }

    state = lbl_80479A58.x1D[idx].x0;
    if (state == 0 && lbl_80479A58.x38[idx] == 6) {
        if (lbl_80479A58.x1D[idx].x1 != 0 && (u8) tmd->x4B8[idx].x0 != 0) {
            lbl_80479A58.x1D[idx].x0 = 1;
            lbl_80479A58.x1D[idx].x1 = 0;
        }
    }

    state = lbl_80479A58.x1D[idx].x0;
    if (state == 1) {
        if (lbl_80479A58.x1D[idx].x1 != 0) {
            lbl_80479A58.x1D[idx].x0 = 2;
            lbl_80479A58.x1D[idx].x1 = 0;
        }
    }

    fn_8019044C(jobj, (f32) lbl_80479A58.x1D[idx].b);
}

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
    if (lbl_80479A58.x1D[idx].x0 == 4) {
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
    if (lbl_80479A58.x1D[idx].x0 == 4) {
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

    fn_8019044C(jobj, (lbl_80479A58.xF + gm_804771C4.match_type * 100 + 100));
    lbl_80479A58.xF++;
}

void fn_8019C744(HSD_GObj* gobj)
{
    TmData* tmd;
    s32 idx;
    HSD_JObj* jobj;
    f32 var_f1;

    tmd = gm_8018F634();
    idx = fn_8018F62C(gobj);
    jobj = GET_JOBJ(gobj);

    if ((s32) tmd->x30 == 4) {
        var_f1 = (13.0f * (f32) idx) + -19.5f;
    } else if ((s32) tmd->x30 == 3) {
        var_f1 = 6.5f + ((13.0f * (f32) idx) - 19.5f);
    } else {
        var_f1 = 6.5f + ((13.0f * (2.0f * (f32) idx)) - 19.5f);
    }
    fn_8018FDC4(jobj, 0.3f + var_f1, 10.1f, 666.0f);

    if (lbl_80479A58.x1D[idx].x0 == 4) {
        if (lbl_80479A58.x10[idx] < 0x28U) {
            lbl_80479A58.x10[idx]++;
        }
        HSD_JObjSetTranslateY(jobj, lbl_803DA2E0.x20[lbl_80479A58.x10[idx]]);
    } else {
        lbl_80479A58.x10[idx] = 0;
    }

    if (((s8) HSD_PadMasterStatus[(u8) idx].err != 0) &&
        (tmd->x4B8[idx].x0 != 1))
    {
        HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
        if ((s32) tmd->x30 == 4) {
            var_f1 = (13.0f * (f32) idx) + -19.5f;
        } else if ((s32) tmd->x30 == 3) {
            var_f1 = 6.5f + ((13.0f * (f32) idx) - 19.5f);
        } else {
            var_f1 = 6.5f + ((13.0f * (2.0f * (f32) idx)) - 19.5f);
        }
        fn_8018FDC4(jobj, 0.3f + var_f1, 10.1f, 666.0f);
    }
}

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
    if (lbl_80479A58.x1D[idx].x0 == 2) {
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
    HSD_JObj* jobj = HSD_GObjGetHSDObj(gobj);
    u32 idx = fn_8018F62C(gobj);
    PAD_STACK(20);

    HSD_ASSERT(993, jobj);
    sp28 = jobj->translate.x;
    temp_r27 = tmd->x37[idx].xE;
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
        tmd->x37[idx].xF = tmd->x37[idx].xE;
        fn_8018FDC4(jobj, sp28, 17.0f, 0.01f);
        HSD_SisLib_803A746C(tmd->x534[idx], 0, 10.0f * sp28, -172.0f);
        tmd->x534[idx]->pos_z = 0.01f;
        break;
    }
    if (tmd->x37[idx].x5 != 0) {
        fn_8019044C(jobj, 201.0f);
        return;
    }
    fn_8019044C(jobj, fn_8018F71C(tmd->x37[idx].x3, tmd->x37[idx].x7));
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

void fn_8019D1BC(void)
{
    TmData* tmd;
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    HSD_JObj* c;
    s32 i;
    f32 pos;
    f32 var_f1;
    f32 anim;
    char name_buf[8][0x14];
    PAD_STACK(0xA0);

    tmd = gm_8018F634();

    for (i = 0; i < (s32) tmd->x30; i++) {
        gobj = fn_8019035C(0, lbl_804D6694->models[12], 0, 0x1A, 2, 1,
                           fn_8019C048, (f32) i);
        jobj = GET_JOBJ(gobj);
        HSD_JObjSetTranslateY(jobj, -2.5f);
        fn_8018FBD8(gobj, i);

        c = HSD_JObjGetChild(jobj);
        HSD_MObjRemoveAnimByFlags(c->u.dobj->mobj, 4);
        c = HSD_JObjGetChild(jobj);
        c = HSD_JObjGetNext(c);
        HSD_MObjRemoveAnimByFlags(c->u.dobj->mobj, 4);
        c = HSD_JObjGetChild(jobj);
        c = HSD_JObjGetNext(c);
        c = HSD_JObjGetNext(c);
        HSD_MObjRemoveAnimByFlags(c->u.dobj->mobj, 4);

        if (tmd->x30 == 4) {
            pos = 73.0f + (240.0f * (f32) i + 152.0f);
        } else if (tmd->x30 == 3) {
            pos = 73.0f + (240.0f * (f32) i + 270.0f);
        } else {
            pos = 73.0f + (480.0f * (f32) i + 270.0f);
        }

        fn_8018ECA8((s32) tmd->x4B8[i].x6, (s32) tmd->x4B8[i].x0, 5,
                    0.99f * (pos - 320.0f) - 261.0f, -11.0f, 5);
        tmd->x524[2]->hidden = 1;

        gobj = fn_8019035C(0, lbl_804D6694->models[10], 0, 0x1A, 2, 1,
                           fn_8019C3EC, pos);
        jobj = GET_JOBJ(gobj);
        HSD_JObjSetTranslateY(jobj, -2.5f);
        fn_8018FBD8(gobj, i);
        fn_8019BA08((u8) i, jobj);

        gobj = fn_8019035C(0, lbl_804D6694->models[4], 0, 0x1A, 2, 1,
                           fn_8019C570, pos);
        jobj = GET_JOBJ(gobj);
        fn_8018FBD8(gobj, i);

        if ((s32) tmd->x30 == 4) {
            var_f1 = (13.0f * (f32) i) + -19.5f;
        } else if ((s32) tmd->x30 == 3) {
            var_f1 = 6.5f + ((13.0f * (f32) i) - 19.5f);
        } else {
            var_f1 = 6.5f + ((13.0f * (2.0f * (f32) i)) - 19.5f);
        }
        fn_8018FDC4(jobj, var_f1 - 2.799999f, 4.3f, 0.001f);

        if (tmd->x4B8[i].x2 != 0) {
            c = HSD_JObjGetChild(jobj);
            c = HSD_JObjGetNext(c);
            fn_8019044C(c, 201.0f);
        } else {
            c = HSD_JObjGetChild(jobj);
            c = HSD_JObjGetNext(c);
            fn_8019044C(c,
                        fn_8018F71C(tmd->x4B8[i].x1, tmd->x4B8[i].x3));
        }

        gobj = fn_8019035C(0, lbl_804D6694->models[9], 0, 0x1A, 2, 1,
                           fn_8019C744, pos);
        jobj = GET_JOBJ(gobj);
        HSD_JObjSetTranslateY(jobj, -2.5f);
        fn_8018FBD8(gobj, i);

        if (tmd->x4B8[i].x0 == 0) {
            anim = (f32) i;
        } else {
            anim = 4.0f;
        }
        fn_8019044C(jobj, anim);

        gobj = fn_8019035C(0, lbl_804D6694->models[8], 0, 0x1A, 2, 1,
                           fn_8019CA38, 0.0f);
        jobj = GET_JOBJ(gobj);
        HSD_JObjSetTranslateY(jobj, -2.5f);
        fn_8018FBD8(gobj, i);

        gobj = fn_8019035C(0, lbl_804D6694->models[14], 0, 0x1A, 2, 1,
                           fn_8019CC74, anim);
        jobj = GET_JOBJ(gobj);
        HSD_JObjSetTranslateY(jobj, -2.5f);
        fn_8018FBD8(gobj, i);

        if (tmd->x31 != 0) {
            gobj = fn_8019035C(0, lbl_804D6694->models[11], 0, 0x1A, 2, 1,
                               fn_8019D074, anim);
            jobj = GET_JOBJ(gobj);
            HSD_JObjSetTranslateY(jobj, -2.0f);
            fn_8018FBD8(gobj, i);
            fn_8019044C(jobj, (f32) tmd->x4B8[i].x5);
        }
    }

    fn_8019035C(0, lbl_804D6694->models[1], 0, 0x1A, 2, 1, fn_8019CFA4,
                0.0f);
    fn_8019035C(0, lbl_804D6694->models[5], 0, 0x1A, 2, 1, fn_8019C6AC,
                0.0f);

    {
        HSD_JObj* j16;
        j16 = GET_JOBJ(fn_8019035C(0, lbl_804D6694->models[0], 0, 0x1A, 2,
                                   1, NULL, 0.0f));
        j16 = HSD_JObjGetChild(j16);
        j16 = HSD_JObjGetNext(j16);
        j16 = HSD_JObjGetNext(j16);
        j16 = HSD_JObjGetNext(j16);
        j16 = HSD_JObjGetNext(j16);
        j16 = HSD_JObjGetNext(j16);
        {
            for (i = 0; i <= 0x28; i++) {
                fn_8019044C(j16, (f32) (i + 10));
                lbl_803DA2E0.x20[i] = HSD_JObjGetTranslationY(j16);
            }
        }
    }

    fn_8019035C(0, lbl_804D6694->models[6], 0, 0x1A, 2, 1, fn_8019CBFC,
                0.0f);

    for (i = 0; i < (s32) tmd->x2E; i++) {
        gobj = fn_8019035C(0, lbl_804D6694->models[3], 0, 0x1A, 2, 1,
                           fn_8019CDBC, 0.0f);
        jobj = GET_JOBJ(gobj);
        fn_8018FDC4(jobj, (5.999997f * (f32) tmd->x37[i].xF) - 21.5f,
                    17.0f, 0.01f);

        if (tmd->x37[i].x5 != 0) {
            fn_8019044C(jobj, 201.0f);
        } else {
            fn_8019044C(jobj, fn_8018F71C(tmd->x37[i].x3, tmd->x37[i].x7));
        }

        fn_8018FBD8(gobj, i);
        fn_8018F00C(name_buf[i], tmd->x37[i].x9);

        tmd->x534[i] = HSD_SisLib_803A6754(0, (s32) lbl_804D663C);
        tmd->x534[i]->default_kerning = 1;
        tmd->x534[i]->x4C = 1;
        {
            HSD_Text* text = tmd->x534[i];
            text->font_size.x = 0.1f;
            text->font_size.y = 0.1f;
        }
        tmd->x534[i]->default_alignment = 1;
        HSD_SisLib_803A6B98(tmd->x534[i],
                            10.0f * ((5.999997f * (f32) i) - 21.5f),
                            -172.0f, name_buf[i], 1);
        HSD_SisLib_803A7548(tmd->x534[i], 0, 0.35f, 0.6f);
    }
}

void fn_8019DD60(void)
{
    HSD_GObj* gobj;
    HSD_Text* text;
    TmData* tmd;
    s32 i;
    PAD_STACK(16);

    tmd = gm_8018F634();
    if (tmd->x2C == 0) {
        if ((s32) gm_804771C4.match_type == 1) {
            lbAudioAx_800237A8(0x7545, 0x7F, 0x40);
        } else {
            lbAudioAx_800237A8(0x7546, 0x7F, 0x40);
        }
    }
    tmd->x2C = 0;
    gobj = fn_80190174(lbl_804D6690->cameras->desc);
    fn_801901F8(lbl_804D6690->cameras->desc);
    fn_801902F0((s32) gobj);
    fn_8019027C((UNK_T) lbl_804D6690->lights);
    fn_8019035C(0, lbl_804D6690->models[5], 0, 0x1A, 2, 1, fn_8019BF18,
                0.0f);
    fn_8019035C(0, lbl_804D6690->models[4], 0, 0x1A, 2, 1, fn_8019BF8C,
                0.0f);
    tmd->x524[2] = HSD_SisLib_803A6754(0, (s32) lbl_804D663C);
    tmd->x524[2]->default_kerning = 1;
    text = tmd->x524[2];
    text->font_size.x = 0.054945f;
    text->font_size.y = 0.08f;
    tmd->x524[2]->default_alignment = 1;
    fn_8019D1BC();
    gobj = GObj_Create(0xE, 0x1A, 0);
    {
        HSD_Fog* tmp = HSD_FogLoadDesc(lbl_804D6690->fogs->desc);
        HSD_GObjObject_80390A70(gobj, (u8) HSD_GObj_804D7848, tmp);
    }
    GObj_SetupGXLink(gobj, HSD_GObj_FogCallback, 0, 0);

    lbl_80479A58.x0 = 0;
    lbl_80479A58.x4 = 0;
    lbl_80479A58.xE = 0x50;
    lbl_80479A58.xF = 0;
    for (i = 0; i < (s32) tmd->x30; i++) {
        lbl_80479A58.x18[i] = 0;
        lbl_80479A58.x6[i] = 0;
        lbl_80479A58.x10[i] = 0;
        lbl_80479A58.x1D[i].a = 0;
        lbl_80479A58.x1D[i].b = 0;
        lbl_80479A58.x1D[i].c = 0x1E;
        lbl_80479A58.x1D[i].x1 = 0;
        lbl_80479A58.x1D[i].x2 = 0;
        lbl_80479A58.x1D[i].x0 = 0;
        lbl_80479A58.x38[i] = 6;
    }
}

void gm_8019DF8C_OnFrame(void)
{
    TmVsData vsdata;
    TmData* tmd;
    s32 confirmed;
    s32 i, j;
    u32 buttons;
    u32 pressed;
    PAD_STACK(4);

    tmd = gm_8018F634();
    fn_8018F674(4);
    fn_8018F640(4);

    if (mn_8022F218() != 0) {
        lbAudioAx_80024030(0);
        mn_8022F268();
        gm_801A4B60();
        gm_801A42F8(1);
        return;
    }

    confirmed = 0;
    for (i = 0; i < (s32) tmd->x30; i++) {
        if (lbl_80479A58.x1D[i].x0 == 2 &&
            lbl_80479A58.x1D[i].b >= 0x3CU &&
            (s8)(u8) HSD_PadMasterStatus[(u8) i].err == 0)
        {
            confirmed += 1;
        }
    }

    if (confirmed == (s32) tmd->x30) {
        lbl_80479A58.x0 += 1;
        if ((u32) lbl_80479A58.x0 >= 0x1EU) {
            for (j = 0; j < (s32) tmd->x2E; j++) {
                tmd->x37[j].xF = tmd->x37[j].xE;
            }
            fn_801965C4();
        }
    } else {
        lbl_80479A58.x0 = 0;

        for (i = 0; i < (s32) tmd->x30; i++) {
            if ((s8)(u8) HSD_PadMasterStatus[(u8) i].err == 0) {
                buttons = fn_8018F640(i);
                pressed = fn_8018F674(i);

                /* Abort combo check */
                if (fn_8018F6A8(i) & 0x200) {
                    lbl_80479A58.x18[i] = (u8)(lbl_80479A58.x18[i] + 1);
                    if ((u8) lbl_80479A58.x18[i] > 0x5AU) {
                        lbAudioAx_80024030(1);
                        gm_SetScenePendingMinor(0U);
                        gm_801A4B60();
                        return;
                    }
                    goto check_confirm;
                }
                lbl_80479A58.x18[i] = 0;

            check_confirm: {
                u8 status = lbl_80479A58.x1D[i].x0;
                if (status != 2 && status != 1) {
                    if ((fn_8018F6A8(i) & 0x40) && (fn_8018F6A8(i) & 0x20)) {
                        TmData* p = gm_8018F634();
                        for (j = 0; j < (s32) p->x2E; j++) {
                            if (i != (s32) p->x37[j].xE)
                                continue;
                            goto lr_found;
                        }
                        j = 0;
                    lr_found:
                        tmd->x37[j].x5 = 1;
                        tmd->x4B8[i].x2 = 1;
                    }

                    if (pressed & 0x40001) {
                        u8 chr;
                        lbAudioAx_80024030(2);

                        {
                            TmData* p = gm_8018F634();
                            for (j = 0; j < (s32) p->x2E; j++) {
                                if (i != (s32) p->x37[j].xE)
                                    continue;
                                goto left_found1;
                            }
                            j = 0;
                        left_found1:;
                        }

                        tmd->x37[j].x5 = 0;
                        tmd->x4B8[i].x2 = 0;

                        chr = tmd->x4B8[i].x1;
                        do {
                            if (chr != 0) {
                                chr -= 1;
                            } else {
                                chr = fn_8018F6DC(0x19);
                            }
                        } while (gm_80164840(fn_8018F6FC((CSSIconHud) chr)) ==
                                 0);
                        tmd->x4B8[i].x1 = chr;

                        {
                            TmData* p = gm_8018F634();
                            for (j = 0; j < (s32) p->x2E; j++) {
                                if (i != (s32) p->x37[j].xE)
                                    continue;
                                goto left_found2;
                            }
                            j = 0;
                        left_found2:;
                        }
                        tmd->x37[j].x3 = tmd->x4B8[i].x1;

                        {
                            TmData* p = gm_8018F634();
                            for (j = 0; j < (s32) p->x2E; j++) {
                                if (i != (s32) p->x37[j].xE)
                                    continue;
                                goto left_found3;
                            }
                            j = 0;
                        left_found3:;
                        }
                        tmd->x4B8[i].x3 = 0;
                        tmd->x37[j].x7 = 0;

                    } else if (pressed & 0x80002) {
                        u8 chr;
                        lbAudioAx_80024030(2);

                        {
                            TmData* p = gm_8018F634();
                            for (j = 0; j < (s32) p->x2E; j++) {
                                if (i != (s32) p->x37[j].xE)
                                    continue;
                                goto right_found1;
                            }
                            j = 0;
                        right_found1:;
                        }

                        tmd->x37[j].x5 = 0;
                        tmd->x4B8[i].x2 = 0;

                        chr = tmd->x4B8[i].x1;
                        do {
                            if ((s32) chr < fn_8018F6DC(0x19)) {
                                chr += 1;
                            } else {
                                chr = fn_8018F6DC(0);
                            }
                        } while (gm_80164840(fn_8018F6FC((CSSIconHud) chr)) ==
                                 0);
                        tmd->x4B8[i].x1 = chr;

                        {
                            TmData* p = gm_8018F634();
                            for (j = 0; j < (s32) p->x2E; j++) {
                                if (i != (s32) p->x37[j].xE)
                                    continue;
                                goto right_found2;
                            }
                            j = 0;
                        right_found2:;
                        }
                        tmd->x37[j].x3 = tmd->x4B8[i].x1;

                        {
                            TmData* p = gm_8018F634();
                            for (j = 0; j < (s32) p->x2E; j++) {
                                if (i != (s32) p->x37[j].xE)
                                    continue;
                                goto right_found3;
                            }
                            j = 0;
                        right_found3:;
                        }
                        tmd->x4B8[i].x3 = 0;
                        tmd->x37[j].x7 = 0;
                    }
                }
            }

                if (buttons & 0x1100) {
                    if ((u8) lbl_80479A58.x1D[i].x0 != 2) {
                        u16 char_id;
                        lbAudioAx_80024030(1);
                        lbl_80479A58.x1D[i].x0 = 1;
                        char_id = tmd->x4B8[i].x6;
                        if (char_id <= 0x78U) {
                            gm_80167858(i, (s32) char_id, 0xB, 0x14);
                        } else {
                            gm_80167858(i, 0x78, 0xB, 0x14);
                        }
                    }
                } else if (buttons & 0x200) {
                    if ((u8) lbl_80479A58.x1D[i].x0 == 2) {
                        lbAudioAx_80024030(0);
                        lbl_80479A58.x1D[i].x0 = 3;
                    }
                } else {
                    u8 color_status = lbl_80479A58.x1D[i].x0;
                    if (color_status != 2 && color_status != 1) {
                        if (buttons & 0x400) {
                            /* Down: increment color */
                            if ((s32) tmd->x4B8[i].x3 < (s32)(gm_80169238(fn_8018F6FC((CSSIconHud) tmd->x4B8[i].x1)) - 1)) {
                                tmd->x4B8[i].x3 += 1;
                            }

                            {
                                TmData* p = gm_8018F634();
                                for (j = 0; j < (s32) p->x2E; j++) {
                                    if (i != (s32) p->x37[j].xE) continue;
                                    goto down_found;
                                }
                                j = 0;
                            down_found:;
                            }
                            tmd->x37[j].x7 = tmd->x4B8[i].x3;

                        } else if (buttons & 0x800) {
                            /* Up: decrement color */
                            u8 color = tmd->x4B8[i].x3;
                            if (color != 0) {
                                tmd->x4B8[i].x3 = color - 1;
                            }

                            {
                                TmData* p = gm_8018F634();
                                for (j = 0; j < (s32) p->x2E; j++) {
                                    if (i != (s32) p->x37[j].xE) continue;
                                    goto up_found;
                                }
                                j = 0;
                            up_found:;
                            }
                            tmd->x37[j].x7 = tmd->x4B8[i].x3;
                        }
                    }
                }
            }
        }

        {
            s32 stage;
            if (fn_80196564(tmd) != 0) {
                stage = fn_8019655C();
            } else {
                stage = (s32) tmd->x28;
            }
            vsdata.stage_id = (u32) stage;
        }
        for (i = 0; i < 4; i++) {
            vsdata.slot_type[i] = (Gm_PKind) tmd->x4B8[i].x0;
            vsdata.char_id[i] = fn_8018F6FC((CSSIconHud) tmd->x4B8[i].x1);
            vsdata.color[i] = (u32) tmd->x4B8[i].x3;
        }
        fn_8019EE80(&vsdata);
    }
}

void gm_8019E634(void)
{
    s32 indices[4];
    s32 results[4];
    u8* hbuf_init;
    TmData* tmd;
    s32 hmn_cpu;
    s32 i, j;
    u64 audio_mask;

    tmd = gm_8018F634();
    hmn_cpu = tmd->hmn_cpu_count;

    indices[0] = lbl_803B7D3C[0];
    indices[1] = lbl_803B7D3C[1];
    indices[2] = lbl_803B7D3C[2];
    indices[3] = lbl_803B7D3C[3];

    /* Get match results per player */
    for (i = 0; i < (s32) tmd->x30; i++) {
        results[i] = fn_80166CBC(&gm_80477738, i);
    }

    /* Bubble sort results, keeping indices in parallel */
    for (i = 0; i < (s32)(tmd->x30 - 1); i++) {
        for (j = 0; j < (s32)((tmd->x30 - 1) - i); j++) {
            if (results[j] > results[j + 1]) {
                s32 tr = results[j];
                s32 ti = indices[j];
                results[j] = results[j + 1];
                indices[j] = indices[j + 1];
                results[j + 1] = tr;
                indices[j + 1] = ti;
            }
        }
    }

    /* Handicap adjustment */
    if ((u8) gmMainLib_8015CC34()->handicap == 1) {
        u8* hbuf;

        hbuf_init = lbl_804DA948;
        hbuf = hbuf_init;

        /* Read handicap from x37 entries */
        for (i = 0; i < 4; i++) {
            if (i < (s32) tmd->x30) {
                s32 id = results[i];
                TmData* p = gm_8018F634();
                for (j = 0; j < (s32) p->x2E; j++) {
                    if (id != (s32) p->x37[j].xF) continue;
                    goto found1;
                }
                j = 0;
            found1:
                hbuf[i] = (u8) tmd->x37[j].x2;
            }
        }

        fn_80169000(&gm_80477738, &hbuf_init);

        /* Write back adjusted handicap */
        for (i = 0; i < 4; i++) {
            if (i < (s32) tmd->x30) {
                s32 id = results[i];
                TmData* p = gm_8018F634();
                for (j = 0; j < (s32) p->x2E; j++) {
                    if (id != (s32) p->x37[j].xF) continue;
                    goto found2;
                }
                j = 0;
            found2:
                tmd->x37[j].x2 = hbuf[i];
            }
        }
    }

    /* Assign bracket positions */
    if ((s32) gm_804771C4.match_type == 1) {
        /* Team mode */
        for (i = 0; i < hmn_cpu; i++) {
            s32 id = indices[i];
            TmData* p = gm_8018F634();
            for (j = 0; j < (s32) p->x2E; j++) {
                if (id != (s32) p->x37[j].xF) continue;
                goto found3;
            }
            j = 0;
        found3:
            tmd->x37[j].xE = (tmd->x2E - 1) - i;

            id = tmd->x30 + i;
            p = gm_8018F634();
            for (j = 0; j < (s32) p->x2E; j++) {
                if (id != (s32) p->x37[j].xF) continue;
                goto found4;
            }
            j = 0;
        found4:
            tmd->x37[j].xE = (s8) indices[i];
        }
    } else {
        /* FFA mode */
        for (i = 0; i < hmn_cpu; i++) {
            s32 id = indices[(tmd->x30 - 1) - i];
            TmData* p = gm_8018F634();
            for (j = 0; j < (s32) p->x2E; j++) {
                if (id != (s32) p->x37[j].xF) continue;
                goto found5;
            }
            j = 0;
        found5:
            tmd->x37[j].xE = (tmd->x2E - 1) - i;

            id = tmd->x30 + i;
            p = gm_8018F634();
            for (j = 0; j < (s32) p->x2E; j++) {
                if (id != (s32) p->x37[j].xF) continue;
                goto found6;
            }
            j = 0;
        found6:
            tmd->x37[j].xE = (s8) indices[(tmd->x30 - 1) - i];
        }
    }

    /* Adjust remaining bracket positions */
    for (i = tmd->x30 + hmn_cpu; i < (s32) tmd->x2E; i++) {
        TmData* p = gm_8018F634();
        for (j = 0; j < (s32) p->x2E; j++) {
            if (i != (s32) p->x37[j].xF) continue;
            goto found7;
        }
        j = 0;
    found7:
        tmd->x37[j].xE -= hmn_cpu;
    }

    /* Copy x37 data to x4B8 */
    for (i = 0; i < (s32) tmd->x30; i++) {
        TmData* p;

        p = gm_8018F634();
        for (j = 0; j < (s32) p->x2E; j++) {
            if (i != (s32) p->x37[j].xE) continue;
            goto found8;
        }
        j = 0;
    found8:
        tmd->x4B8[i].x6 = tmd->x37[j].x9;

        p = gm_8018F634();
        for (j = 0; j < (s32) p->x2E; j++) {
            if (i != (s32) p->x37[j].xE) continue;
            goto found9;
        }
        j = 0;
    found9:
        tmd->x4B8[i].x1 = tmd->x37[j].x2;

        p = gm_8018F634();
        for (j = 0; j < (s32) p->x2E; j++) {
            if (i != (s32) p->x37[j].xE) continue;
            goto found10;
        }
        j = 0;
    found10:
        tmd->x4B8[i].x3 = tmd->x37[j].x3;

        p = gm_8018F634();
        for (j = 0; j < (s32) p->x2E; j++) {
            if (i != (s32) p->x37[j].xE) continue;
            goto found11;
        }
        j = 0;
    found11:
        tmd->x4B8[i].x0 = tmd->x37[j].x0;

        p = gm_8018F634();
        for (j = 0; j < (s32) p->x2E; j++) {
            if (i != (s32) p->x37[j].xE) continue;
            goto found12;
        }
        j = 0;
    found12:
        tmd->x4B8[i].x5 = tmd->x37[j].x7;

        p = gm_8018F634();
        for (j = 0; j < (s32) p->x2E; j++) {
            if (i != (s32) p->x37[j].xE) continue;
            goto found13;
        }
        j = 0;
    found13:
        tmd->x4B8[i].x2 = tmd->x37[j].x5;
    }

    /* Debug output + audio preloading */
    audio_mask = 0;
    for (i = 0; i < (s32) tmd->x30; i++) {
        OSReport("ckind:%d\n", (s32) tmd->x4B8[i].x1);
        audio_mask |= lbAudioAx_80026E84((CharacterKind) tmd->x4B8[i].x1);
    }
    lbAudioAx_80026F2C(0x16);
    lbAudioAx_8002702C(6, audio_mask);
    lbAudioAx_80027168();
}

void gm_8019ECAC_OnEnter(void* arg0)
{
    struct {
        u32 stage_id;
        CharacterKind char_id[4];
        u32 color[4];
    } local;
    s32 i;
    u64 audio_mask;
    TmData* tmd;
    PAD_STACK(4);

    tmd = gm_8018F634();
    lbAudioAx_80026F2C(0x12);
    lbAudioAx_8002702C(2, 8);
    lbAudioAx_80027168();
    lbAudioAx_80027648();
    gm_8018F634();
    lbl_804D6688 = lbArchive_80016DBC("GmTou1p", &lbl_804D6690,
                                      "ScGamTour_scene_data", 0);
    lbl_804D668C = lbArchive_80016DBC("GmTou4p", &lbl_804D6694,
                                      "ScGamTour_scene_data", 0);
    HSD_SisLib_803A62A0(0, fn_8018F5F0(), "SIS_TournamentData");
    fn_8019DD60();
    lbAudioAx_80027648();
    lbAudioAx_80023F28(gmMainLib_8015ECB0());

    for (i = 0; i < 4; i++) {
        if (tmd->x4B8[i].x0 != 3) {
            local.char_id[i] = fn_8018F6FC(tmd->x4B8[i].x1);
            local.color[i] = tmd->x4B8[i].x3;
        }
    }

    fn_80196510();
    if (fn_80196564(tmd)) {
        local.stage_id = fn_8019655C();
    } else {
        local.stage_id = tmd->x28;
    }
    fn_80196594(tmd);
    lbDvd_800174BC();

    audio_mask = 0;
    for (i = 0; i < 4; i++) {
        if (tmd->x4B8[i].x0 != 3) {
            audio_mask |= lbAudioAx_80026E84(local.char_id[i]);
        }
    }
    audio_mask |= lbAudioAx_80026EBC(local.stage_id);
    lbAudioAx_80026F2C(0x1C);
    lbAudioAx_8002702C(0xC, audio_mask);
    lbAudioAx_80027168();
    lbAudioAx_80023F28(gmMainLib_8015ECB0());
}

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
