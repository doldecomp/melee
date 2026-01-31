#include "gm_18A5.h"

#include "gm_18A5.static.h"

#include "ft/forward.h"

#include <sysdolphin/baselib/controller.h>
#include <sysdolphin/baselib/fog.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjobject.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/random.h>
#include <melee/gm/gm_unsplit.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/gm/gmtou.h>
#include <melee/lb/lb_00F9.h>
#include <melee/lb/lbarchive.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lblanguage.h>
#include <melee/mn/mnmain.h>
#include <melee/mn/mnstagesel.h>

typedef void (*lbl_803D9FD8_fn)(s32*, u32, u32);

lbl_803D9FD8_fn lbl_803D9FD8[] = {
    fn_801937C4, fn_80193B58, fn_80193FCC, fn_80194658, fn_801949B4,
    fn_80194BC4, fn_80194D84, fn_80194D84, fn_80194D84, NULL,
    fn_80194F30, fn_801953C8, fn_80194F30, fn_80195AF0, fn_80195AF0,
    fn_80195CCC, fn_80194F30, fn_8019610C, fn_8019610C,
};

/// #fn_8018A514

void fn_8018A970(int arg0)
{
    int i;
    for (i = 0; i < 0x40; i++) {
        if (lbl_80473AB8[i].x0 != 0) {
            HSD_GObj* gobj = GObj_Create(0xE, 0x1B, 0);
            gobj->user_data = &lbl_80473AB8[i];
            if (i == 0) {
                HSD_GObjProc_8038FD54(gobj, fn_8018B090, 0);
            }
            GObj_SetupGXLink(gobj, fn_8018E46C, 4, 1);
        }
    }

    if (arg0 < 9) {
        if (arg0 == 1) {
            lbl_80473AB8[5].x5E = 1;
        } else if (arg0 == 3) {
            lbl_80473AB8[10].x32 = 1;
            lbl_80473AB8[11].x5E = 1;
        } else if (arg0 == 5) {
            lbl_80473AB8[23].x5E = 1;
        } else if (arg0 == 7) {
            lbl_80473AB8[46].x5E = 1;
            lbl_80473AB8[47].x5E = 1;
        }
    }
}

/// #fn_8018AA74

/// #fn_8018B090

/// #fn_8018C8D4

/// #fn_8018D50C

/// #fn_8018DC18

/// #fn_8018DF68

/// #fn_8018E46C

/// #fn_8018E618

/// #fn_8018E85C

void fn_8018EC48(void)
{
    mn_8022F138(0x19, 0x1C);
    mn_8022F138(0x12, 0x15);
}

void fn_8018EC7C(void)
{
    mn_8022F0F0(0x1B);
    mn_8022F0F0(0x14);
}

/// #fn_8018ECA8

/// #fn_8018F00C

/// #gm_8018F1B0

int fn_8018F310(int arg0)
{
    int i;
    for (i = 0; i < ARRAY_SIZE(lbl_803D9D20.x59); i++) {
        if (lbl_803D9D20.x59[i] == arg0) {
            return i;
        }
    }
    return -1;
}

u8 fn_8018F3BC(s32 arg0)
{
    return lbl_803D9D20.x59[arg0];
}

int fn_8018F3D0(int arg0)
{
    if (arg0 == 0xE || (arg0 >= 0x10 && arg0 <= 0x13) || arg0 == 0xA) {
        return 1;
    }
    if (arg0 <= 0xD) {
        return 0;
    }
    return 2;
}

int fn_8018F410(void)
{
    int temp_r3;
    int* temp_r30;
    int* temp_r29;

    temp_r30 = &lbl_803D9F0C.x8;
    temp_r29 = &lbl_803D9F0C.x4;
    do {
        temp_r3 = HSD_Randi(0x19);
    } while (lbl_803D9D20.x72[temp_r3] == 0 || lbl_803D9F0C.x0 == temp_r3 ||
             *temp_r29 == temp_r3 || *temp_r30 == temp_r3);
    *temp_r30 = *temp_r29;
    *temp_r29 = lbl_803D9F0C.x0;
    lbl_803D9F0C.x0 = temp_r3;
    return temp_r3;
}

/// #fn_8018F410

int fn_8018F4A0(void)
{
    int temp_r3 = mnStageSel_8025BBD4();
    if (!gm_80164430(temp_r3)) {
        printf("This is impossible stage num from mnSelStageRandom() -> stage "
               "%d \n",
               temp_r3);
        __assert("gmtoulib.c", 0x53D, "0");
    }
    return temp_r3;
}

/// #fn_8018F508

#pragma push
#pragma dont_inline on
char* fn_8018F5F0(void)
{
    if (lbLang_IsSavedLanguageUS()) {
        return "SdTou.usd";
    } else {
        return "SdTou.dat";
    }
}
#pragma pop

/// ???
/// tournament uses the user data as just an int
/// it controls various menu jobj states ie animation state, visibility, etc
u32 fn_8018F62C(HSD_GObj* gobj)
{
    return (u32) gobj->user_data;
}

#pragma push
#pragma dont_inline on
TmData* gm_8018F634(void)
{
    return &gm_804771C4;
}
#pragma pop

u32 fn_8018F640(int arg0)
{
    if (arg0 >= 4) {
        arg0 = 4;
    }
    return gm_801A36A0(arg0);
}

u32 fn_8018F674(int arg0)
{
    if (arg0 >= 4) {
        arg0 = 4;
    }
    return gm_801A36C0(arg0);
}

u32 fn_8018F6A8(int arg0)
{
    if (arg0 >= 4) {
        arg0 = 4;
    }
    return gm_801A3680((u8) arg0);
}

int fn_8018F6DC(int arg0)
{
    if (arg0 >= 0x13) {
        if (arg0 == 0x1D) {
            return 5;
        }
        return arg0 - 1;
    }
    return arg0;
}

CharacterKind fn_8018F6FC(CSSIconHud arg0)
{
    if (arg0 >= 0x13) {
        if (arg0 == 0x1D) {
            return 5;
        }
        return arg0 + 1;
    }
    return (CharacterKind) arg0;
}

float fn_8018F71C(int arg0, int arg1)
{
    return arg0 + arg1 * 0x1E;
}

int fn_8018F74C(void)
{
    int i;

    for (i = 0; i < 0x40; i++) {
        if (lbl_80473AB8[i].x1 != 0) {
            break;
        }
    }

    return i;
}

int fn_8018F808(void)
{
    int i;
    int noerrcount = 0;
    for (i = 0; i < 4; i++) {
        if (HSD_PadMasterStatus[(u8) i].err == 0) {
            noerrcount += 1;
        }
    }
    return noerrcount;
}

/// #fn_8018F888

/// #fn_8018FA24

void fn_8018FBD8(void* arg0, s32 arg1)
{
    M2C_FIELD(arg0, s32*, 0x2C) = arg1;
}

/// #fn_8018FBE0

void fn_8018FDC4(HSD_JObj* jobj, float x, float y, float z)
{
    if ((int) x != 666) {
        HSD_JObjSetTranslateX(jobj, x);
    }
    if ((int) y != 666) {
        HSD_JObjSetTranslateY(jobj, y);
    }
    if ((int) z != 666) {
        HSD_JObjSetTranslateZ(jobj, z);
    }
}

void fn_8018FF9C(HSD_JObj* jobj, float x, float y, float z)
{
    if ((int) x != 666) {
        HSD_JObjSetScaleX(jobj, x);
    }
    if ((int) y != 666) {
        HSD_JObjSetScaleY(jobj, y);
    }
    if ((int) z != 666) {
        HSD_JObjSetScaleZ(jobj, z);
    }
}

HSD_GObj* fn_80190174(HSD_CObjDesc* cobjdesc)
{
    HSD_GObj* gobj = GObj_Create(0x13, 0x12, 0);
    HSD_CObj* cobj = HSD_CObjLoadDesc(cobjdesc);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784B, cobj);
    GObj_SetupGXLinkMax(gobj, HSD_GObj_803910D8, 0);
    gobj->gxlink_prios = 7;
    return gobj;
}

HSD_GObj* fn_801901F8(HSD_CObjDesc* cobjdesc)
{
    HSD_GObj* gobj = GObj_Create(0x13, 0x15, 2);
    HSD_CObj* cobj = HSD_CObjLoadDesc(cobjdesc);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784B, cobj);
    GObj_SetupGXLinkMax(gobj, HSD_GObj_803910D8, 2);
    gobj->gxlink_prios = 0xA;
    return gobj;
}

void fn_8019027C(UNK_T lights)
{
    HSD_GObj* gobj = GObj_Create(0xB, 0x1A, 0);
    HSD_LObj* lobj = lb_80011AC4(lights);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784A, lobj);
    GObj_SetupGXLink(gobj, HSD_GObj_LObjCallback, 1, 0);
}

/// #fn_801902F0

HSD_GObj* fn_8019035C(bool arg0, DynamicModelDesc* model, int arg2, int arg3,
                      int arg4, bool arg5, void (*arg6)(HSD_GObj*), f32 arg8)
{
    HSD_GObj* gobj = GObj_Create(0xE, arg3, 0);
    HSD_JObj* jobj = HSD_JObjLoadJoint(model->joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, arg4, 0);
    if (arg6 != NULL) {
        HSD_GObjProc_8038FD54(gobj, arg6, 0);
    }
    if (arg5) {
        gm_8016895C(jobj, model, arg2);
        HSD_JObjReqAnimAll(jobj, arg8);
        HSD_JObjAnimAll(jobj);
        if (arg0) {
            HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        }
    }
    return gobj;
}

void fn_8019044C(HSD_JObj* jobj, float arg1)
{
    HSD_JObjReqAnimAll(jobj, arg1);
    HSD_JObjAnimAll(jobj);
}

void fn_80190480(float arg8)
{
    if ((int) arg8 == 0) {
        HSD_CObjSetFov(lbl_803D9DD0.cobj, lbl_803D9DD0.xD0);
        return;
    }
    HSD_CObjSetFov(lbl_803D9DD0.cobj, arg8);
}

void fn_801904D0(void)
{
    struct lbl_803D9DD0_t* tmp = &lbl_803D9DD0;
    HSD_CObjSetInterest(tmp->cobj, &lbl_803D9DD0.interest);
    HSD_CObjSetEyePosition(tmp->cobj, &lbl_803D9DD0.eye_position);
}

void fn_80190520(f32 x, f32 y, f32 z)
{
    Vec3 sp14;

    if (((s32) x == 0) && ((s32) y == 0) && ((s32) z == 0)) {
        struct lbl_803D9DD0_t* tmp = &lbl_803D9DD0;
        HSD_CObjSetInterest(tmp->cobj, &lbl_803D9DD0.interest);
        HSD_CObjSetEyePosition(tmp->cobj, &lbl_803D9DD0.eye_position);
        return;
    } else {
        struct lbl_803D9DD0_t* tmp = &lbl_803D9DD0;
        sp14.x = x;
        sp14.y = y;
        sp14.z = z;
        HSD_CObjSetInterest(tmp->cobj, &sp14);
        sp14.z = 415.6922f + z;
        HSD_CObjSetEyePosition(tmp->cobj, &sp14);
    }
}

/// #fn_80190520

static inline int gm_801905F0_inline0(int c_kind)
{
    if (c_kind < CKIND_SEAK) {
        return c_kind;
    }
    if (c_kind == CKIND_GKOOPS) {
        return CKIND_KOOPA;
    }
    return c_kind + 1;
}

void gm_801905F0(StartMeleeData* arg0)
{
    GameRules* temp_r31 = gmMainLib_8015CC34();
    int i;
    TmVsData sp18;

    gm_80168FC4();
    gm_80167A64(&arg0->rules);
    arg0->rules.is_teams = false;
    arg0->rules.xE = gm_804771C4.x28;
    fn_801640B0(&arg0->rules.x20);
    arg0->rules.x0_0 = temp_r31->mode;
    if (temp_r31->mode != 1) {
        arg0->rules.x0_6 = true;
    } else if (temp_r31->stock_time_limit != 0) {
        arg0->rules.x0_6 = true;
    } else {
        arg0->rules.x0_6 = false;
    }
    if (arg0->rules.x0_6) {
        if (temp_r31->mode != 1) {
            if (temp_r31->time_limit == 0) {
                arg0->rules.x10 = 99 * 60;
            } else {
                arg0->rules.x10 = temp_r31->time_limit * 60;
            }
        } else {
            if (temp_r31->stock_time_limit == 0) {
                arg0->rules.x10 = 99 * 60;
            } else {
                arg0->rules.x10 = temp_r31->stock_time_limit * 60;
            }
        }
    }
    if (arg0->rules.x0_0 == 1) {
        arg0->rules.x2_0 = true;
    }
    arg0->rules.x0_7 = false;
    arg0->rules.x4_2 = false;
    arg0->rules.x4_4 = false;
    arg0->rules.xB = gmMainLib_8015CC58()->item_freq;
    arg0->rules.x2_2 = false;
    arg0->rules.x18 = 0;
    arg0->rules.x34 = 1.0f;
    arg0->rules.x30 = fn_801653E8(temp_r31->damage_ratio);
    arg0->rules.x3_4 = false;
    arg0->rules.x3_5 = false;
    arg0->rules.x3_2 = false;
    arg0->rules.x3_3 = false;
    switch (gmMainLib_8015ED30()) {
    case 1:
        arg0->rules.xC = 0;
        break;
    case 0:
        arg0->rules.xC = -1;
        break;
    case 2:
        arg0->rules.xC = -2;
        break;
    }
    if (temp_r31->pause != 0) {
        arg0->rules.x2_4 = false;
    } else {
        arg0->rules.x2_4 = true;
    }
    if (temp_r31->score_display != 0 && !arg0->rules.x0_3) {
        arg0->rules.x3_0 = true;
    } else {
        arg0->rules.x3_0 = false;
    }
    gm_80167A14(arg0->players);

    for (i = 0; i < 4; i++) {
        if (i < gm_804771C4.x30) {
            arg0->players[i].x20 = 1.0f;
            arg0->players[i].xA = (u8) MIN(gm_804771C4.x4B8[i].x6, 0x78);
            if (gm_804771C4.x4B8[i].x2 != 0) {
                arg0->players[i].c_kind = gm_801905F0_inline0(fn_8018F410());
                arg0->players[i].color =
                    HSD_Randi(gm_80169238(arg0->players[i].c_kind));
            } else {
                arg0->players[i].c_kind =
                    gm_801905F0_inline0(gm_804771C4.x4B8[i].x1);
                arg0->players[i].color = gm_804771C4.x4B8[i].x3;
            }
            arg0->players[i].slot_type = gm_804771C4.x4B8[i].x0;
            arg0->players[i].stocks = temp_r31->stock_count;
            arg0->players[i].sub_color = 0;
            arg0->players[i].team = 0xFF;
            arg0->players[i].xC_b0 = gm_801677F8(i, arg0->players[i].xA);
            if (gm_804771C4.x4B8[i].x0 == 1) {
                arg0->players[i].xC_b0 = false;
            }
            arg0->players[i].xE = 4;
            arg0->players[i].cpu_level = gm_804771C4.x4B8[i].x4;
            arg0->players[i].x12 = 0;
            if (gmMainLib_8015CC34()->handicap != 0) {
                arg0->players[i].x18 = fn_8016419C(gm_804771C4.x4B8[i].x5);
                arg0->players[i].x1C = fn_801641B4(gm_804771C4.x4B8[i].x5);
            } else {
                arg0->players[i].x18 = arg0->players[i].x1C = 1.0F;
            }
        } else {
            arg0->players[i].slot_type = Gm_PKind_NA;
        }
    }

    sp18.stage_id = arg0->rules.xE;
    for (i = 0; i < 4; i++) {
        sp18.slot_type[i] = arg0->players[i].slot_type;
        sp18.char_id[i] = arg0->players[i].c_kind;
        sp18.color[i] = arg0->players[i].color;
    }

    fn_8019EF08(&sp18);
}

/// #fn_80190ABC

#pragma push
#pragma dont_inline on
void gm_80190EA4(void)
{
    int i;
    TmData* tmdata = gm_8018F634();

    fn_80190174(lbl_804D664C->cameras->desc);
    fn_801902F0(0);
    fn_80193308();
    fn_8019027C(lbl_804D664C->lights);
    fn_80193230();
    tmdata->cur_option = 0;

    while (tmdata->cur_option < 7) {
        fn_80190ABC(0);
        fn_80190ABC(2);
        fn_80190ABC(3);
        fn_80190ABC(1);
        tmdata->cur_option += 1;
    }
    if (gm_804771C4.match_type == 0) {
        TmData* tmdata = gm_8018F634();
        fn_8018EC7C();
        fn_8018E618(tmdata->entrants, 1, 4.5f);
        fn_80190480(130.0f);
        fn_80190520(-278.0f, 255.0f, 0.0f);
    }
    tmdata->x20 = 0;

    for (i = 0; i < 64; i++) {
        if (gmMainLib_8015CC34()->handicap == 1) {
            tmdata->x37[i].x1 = 5;
        } else {
            tmdata->x37[i].x1 = 9;
        }
    }
}
#pragma pop

extern struct {
    u8 pad[0xC];
    u16 xC;
} lbl_804799B8;

/// #gm_80190FE4

#pragma dont_inline on
void fn_801910E0(HSD_GObj* gobj)
{
    HSD_JObj* jobj = gobj->hsd_obj;

    if (lbl_804799B8.xC > 800) {
        lbl_804799B8.xC = 0;
    }

    fn_8019044C(jobj, lbl_804799B8.xC);
    lbl_804799B8.xC++;
}
#pragma dont_inline reset

/// #fn_80191154

/// #fn_80191240

/// #fn_801913BC

/// #fn_80191678

/// #fn_8019175C

/// #fn_801918F0

/// #fn_80191A54

/// #fn_80191B5C

/// #fn_80191CA4

/// #fn_80191D38

/// #fn_80191E9C

/// #fn_80191FD4

/// #fn_8019237C

/// #fn_8019249C

#pragma push
#pragma dont_inline on
void fn_80192690(HSD_GObj* gobj)
{
    TmData* tmdata = gm_8018F634();
    HSD_JObj* jobj = gobj->hsd_obj;

    if (tmdata->cur_option <= 9) {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        return;
    }
    HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
    if (tmdata->cur_option < 0x11 || tmdata->cur_option > 0x12) {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        return;
    }
    fn_8018FDC4(jobj, 666.0F, 666.0F, 0.3F);
    fn_8019044C(jobj, tmdata->cur_option - 0x11);
}
#pragma pop

/// #fn_80192758

/// #fn_80192938

/// #fn_80192BB0

/// #fn_80192E6C

#pragma push
#pragma dont_inline on
void fn_80193230(void)
{
    HSD_GObj* gobj;
    HSD_Fog* fog;
    PAD_STACK(4);

    fn_8019035C(0, lbl_804D664C->models[5], 0, 0x1A, 2, 1, fn_801910E0, 0.0F);
    fn_8019035C(0, lbl_804D664C->models[4], 0, 0x1A, 2, 1, fn_80191154, 0.0F);
    fn_80192BB0();
    fn_80192E6C();
    gobj = GObj_Create(0xE, 0x1A, 0);
    fog = HSD_FogLoadDesc(lbl_804D664C->fogs[0].desc);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7848, fog);
    GObj_SetupGXLink(gobj, HSD_GObj_FogCallback, 0, 0);
}
#pragma pop

/// #fn_80193308

/// #fn_801935B8

/// #fn_801937C4

/// #fn_80193B58

/// #fn_80193FCC

/// #fn_80194658

/// #fn_801949B4

/// #fn_80194BC4

/// #fn_80194D84

/// #fn_80194F30

/// #fn_801953C8

/// #fn_80195AF0

/// #fn_80195CCC

/// #fn_8019610C

/// #gm_8019628C_OnFrame

extern struct {
    UNK_T x0;
    UNK_T x4;
    UNK_T x8;
} lbl_804771B8;

void gm_801963B4_OnEnter(void* arg0)
{
    const char* filename;
    lbAudioAx_80026F2C(0x12);
    lbAudioAx_8002702C(2, 8);
    lbAudioAx_80027168();
    lbAudioAx_80027648();
    lbl_804D6640 = lbArchive_80016DBC("GmTou1p", &lbl_804D664C,
                                      "ScGamTour_scene_data", 0);
    lbl_804D6644 = lbArchive_80016DBC("GmTou2p", &lbl_804D6650,
                                      "ScGamTour_scene_data", 0);
    lbl_804D6648 = lbArchive_LoadArchive("MnExtAll");
    filename = "TmBox.dat";
    lbl_804D6638 = lbArchive_80016DBC(
        filename, &lbl_804771B8.x0, "tournament_box2_array", &lbl_804771B8.x4,
        "tournament_box3_array", &lbl_804771B8.x8, "tournament_box4_array", 0);
    HSD_SisLib_803A62A0(0, fn_8018F5F0(), "SIS_TournamentData");
    fn_801935B8();
    lbAudioAx_800237A8(0x7539, 0x7F, 0x40);
    lbAudioAx_80023F28(gmMainLib_8015ECB0());
}

/// #gm_801964A4_OnLeave

/// #fn_80196510

s32 fn_8019655C(void)
{
    return lbl_804D4190;
}

bool fn_80196564(TmData* arg0)
{
    if ((arg0->stage_selection_type == 0 && arg0->x32 == 0) ||
        arg0->stage_selection_type == 1)
    {
        return true;
    }
    return false;
}

bool fn_80196594(TmData* arg0)
{
    if ((arg0->stage_selection_type == 2 && arg0->x32 == 0) ||
        arg0->stage_selection_type == 3)
    {
        return true;
    }
    return false;
}

void fn_801965C4(void)
{
    TmData* temp_r3;
    int temp_r4;

    temp_r3 = gm_8018F634();
    temp_r3->x2D = 1;
    temp_r4 = temp_r3->stage_selection_type;

    if (fn_80196594(temp_r3)) {
        temp_r3->x32 = 1;
        gm_SetScenePendingMinor(3);
        gm_801A4B60();
        return;
    }
    if (fn_80196564(temp_r3)) {
        temp_r3->x32 = 1;
        temp_r3->x28 = lbl_804D4190;
    }
    gm_SetScenePendingMinor(4);
    gm_801A4B60();
}

/// #fn_80196684

/// #fn_801967E0

/// #fn_80196CF8

extern struct {
    u8 pad[0x10];
    u16 x10;
    u8 pad2[0x1A - 0x12];
    u8 x1A;
} lbl_804799D8;

#pragma dont_inline on
void fn_80196DBC(HSD_GObj* gobj)
{
    HSD_JObj* jobj = gobj->hsd_obj;

    if (lbl_804799D8.x10 > 800) {
        lbl_804799D8.x10 = 0;
    }

    fn_8019044C(jobj, lbl_804799D8.x10);
    lbl_804799D8.x10++;
}
#pragma dont_inline reset

/// #fn_80196E30

/// #fn_80196EEC

/// #fn_80196FFC

/// #fn_801973F8

/// #fn_801975C8

/// #fn_801976D4

/// #fn_801977AC

/// #fn_80197AF0

/// #fn_80197D4C

/// #fn_80197E18

/// #fn_80197FD8

/// #fn_801981A0

/// #fn_801983E4

/// #fn_80198584

/// #fn_801985D4

/// #fn_80198824

/// #fn_80198BA0

/// #fn_80198C60

/// #fn_80198D18

/// #fn_80198EBC

/// #fn_80199AF0

/// #fn_8019A158

/// #fn_8019A71C

/// #gm_8019A828

/// #fn_8019A86C

/// #fn_8019AF50

/// #gm_8019B2DC_OnFrame

/// #fn_8019B458

/// #fn_8019B81C

/// #fn_8019B860
