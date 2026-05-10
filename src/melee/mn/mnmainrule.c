#include "mnmainrule.h"

#include "mnmain.h"

#include "gm/gm_1A3F.h"
#include "mn/types.h"

#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjplink.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/sislib.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/lb/lb_00F9.h>
#include <melee/lb/lbarchive.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/sc/types.h>

extern HSD_FogDesc* MenMain_fog;
extern UNK_T MenMain_lights;
extern HSD_CObjDesc* MenMain_cam;
extern StaticModelDesc MenMainBack_Top;
extern StaticModelDesc MenMainPanel_Top;
extern StaticModelDesc MenMainConTop_Top;
extern StaticModelDesc MenMainCursor_Top;
extern StaticModelDesc MenMainConRl_Top;
extern StaticModelDesc MenMainCursorRl_Top;
extern StaticModelDesc MenMainNmRl_Top;
extern StaticModelDesc MenMainCursorTr01_Top;
extern StaticModelDesc MenMainCursorTr02_Top;
extern StaticModelDesc MenMainCursorTr03_Top;
extern StaticModelDesc MenMainCursorTr04_Top;
extern StaticModelDesc MenMainCursorRl01_Top;
extern StaticModelDesc MenMainCursorRl02_Top;
extern StaticModelDesc MenMainCursorRl03_Top;
extern StaticModelDesc MenMainCursorRl04_Top;
extern StaticModelDesc MenMainCursorRl05_Top;
extern StaticModelDesc MenMainConIs_Top;
extern StaticModelDesc MenMainCursorIs_Top;
extern StaticModelDesc MenMainConSs_Top;
extern StaticModelDesc MenMainCursorSs_Top;

/// #fn_8022F538

/// #mn_8022FB88

/// #mn_8022FD18

/// #mn_8022FEC8

AnimLoopSettings mn_803EC734[5] = {
    { 0.0F, 3.0F, -0.1F },   { 20.0F, 23.0F, -0.1F }, { 40.0F, 43.0F, -0.1F },
    { 60.0F, 63.0F, -0.1F }, { 80.0F, 83.0F, -0.1F },
};

AnimLoopSettings mn_803EC770[9] = {
    { 100.0F, 103.0F, -0.1F }, { 120.0F, 123.0F, -0.1F },
    { 140.0F, 143.0F, -0.1F }, { 160.0F, 163.0F, -0.1F },
    { 180.0F, 183.0F, -0.1F }, { 30.0F, 49.0F, -0.1F },
    { 70.0F, 89.0F, -0.1F },   { 90.0F, 109.0F, -0.1F },
    { 50.0F, 69.0F, -0.1F },
};

void mn_80230198(UNK_T arg0, HSD_JObj* jobj, u8 mode)
{
    AnimLoopSettings* range;
    f32 frame;
    int i;
    PAD_STACK(8);

    switch (mode) {
    case 0:
    case 2:
    case 4:
        frame = mn_8022F298(jobj);
        for (i = 0; i < 5; i++) {
            range = &mn_803EC770[i];
            if (mn_803EC770[i].start_frame <= frame &&
                frame <= mn_803EC770[i].end_frame)
            {
                break;
            }
            range = &mn_803EC734[i];
            if (mn_803EC734[i].start_frame <= frame &&
                frame <= mn_803EC734[i].end_frame)
            {
                break;
            }
        }
        mn_8022ED6C(jobj, range);
        break;
    case 1:
    case 3:
    case 5:
    case 6:
        break;
    }
}

/// #mn_80230274

extern u8 mn_804D4B96;
extern u8 mn_803EC818[];

void mn_802307F8(struct mn_802307F8_t* data, s32 mode, s32 index)
{
    HSD_Text* text;

    if (data->text != NULL) {
        HSD_SisLib_803A5CC4(data->text);
        data->text = NULL;
    }

    if (mode == 1 && data->x2 == 1) {
        index = mn_804D4B96;
    } else if (mode == 1 || mode == 3 || (u32) (mode - 5) <= 1) {
        index = mn_803EC818[mode * 5];
    } else {
        s32 off = mode * 5;
        index = mn_803EC818[off + index];
    }

    text =
        HSD_SisLib_803A5ACC(0, 1, -9.5F, 8.0F, 17.0F, 364.68332F, 76.77544F);
    data->text = text;
    text->font_size.x = 0.0521F;
    text->font_size.y = 0.0521F;
    HSD_SisLib_803A6368(text, (u8) index);
}

void mn_802308F0(HSD_GObj* gobj, int arg1, int arg2)
{
    struct mn_802307F8_t* data = HSD_GObjGetUserData(gobj);
    u16 sel;
    u8 kind;

    if (arg1 != 0) {
        sel = mn_804A04F0.hovered_selection;
    } else {
        sel = data->x1;
    }
    kind = sel;

    switch (data->xA) {
    case 2:
    case 4:
        if (data->text != NULL) {
            HSD_SisLib_803A5CC4(data->text);
            data->text = NULL;
        }
        break;
    case 1:
    case 3:
        if (data->text == NULL) {
            mn_802307F8((struct mn_802307F8_t*) data, kind,
                        mn_804A04F0.confirmed_selection);
        }
        break;
    case 0:
        if (arg1 != 0 || (arg2 != 0 && (kind == 0 || kind == 2 || kind == 4)))
        {
            mn_802307F8((struct mn_802307F8_t*) data, kind,
                        mn_804A04F0.confirmed_selection);
        }
        break;
    case 5:
        break;
    }
}

/// #fn_802309F0

extern s32 mn_804D6BD4;

void mn_80230D18(struct mn_802307F8_t* arg0, HSD_JObj* arg1, int arg2)
{
    int i;

    arg0->x0 = mn_804A04F0.cur_menu;
    arg0->x1 = mn_804A04F0.hovered_selection;
    arg0->x4 = gmMainLib_8015CC34()->handicap;
    if (mn_804D6BD4 == 0 && arg0->x4 == 1) {
        arg0->x4 = 0;
    }
    arg0->x5 = gmMainLib_8015CC34()->damage_ratio;
    arg0->x6 = gmMainLib_8015CC34()->unk_x7;
    arg0->x2 = gmMainLib_8015CC34()->mode;
    arg0->x9 = gmMainLib_8015CC34()->stock_count;
    arg0->x3 = gmMainLib_8015CC34()->time_limit;
    if (gm_801A4310() == 0x1B && arg0->x3 == 0) {
        arg0->x3 = 99;
    }
    arg0->xA = arg2;
    arg0->text = NULL;
    for (i = 0; i < 10; i++) {
        lb_80011E24(arg1, &arg0->jobjs[i], i, -1);
    }
}

/// #mn_80230E38

int mn_80231634(struct mn_80231634_t* arg0)
{
    if (arg0 == NULL) {
        return 0;
    }
    return arg0->x10;
}

void mn_8023164C(void)
{
    HSD_GObjProc* proc;
    s32 mode;

    mn_804A04F0.prev_menu = mn_804A04F0.cur_menu;
    mn_804A04F0.cur_menu = 0xD;

    switch (mn_804A04F0.prev_menu) {
    case 15:
        mn_804A04F0.hovered_selection = 6;
        mode = 3;
        break;
    case 16:
        mn_804A04F0.hovered_selection = 5;
        mode = 3;
        break;
    default:
        mn_804A04F0.hovered_selection = 0;
        mode = 1;
        break;
    }

    proc = HSD_GObj_SetupProc(GObj_Create(0, 1, 0x80), fn_8022F538, 0);
    proc->flags_3 = HSD_GObj_804D783C;
    HSD_GObj_80390CD4(mn_80230E38(mode));
}

extern s32 mn_804D6BD4;

void mn_80231714(void)
{
    HSD_GObjProc* proc;
    s32 mode;

    mn_804A04F0.prev_menu = mn_804A04F0.cur_menu;
    mn_804A04F0.cur_menu = 0xD;

    switch (mn_804A04F0.prev_menu) {
    case 15:
        mn_804A04F0.hovered_selection = 6;
        mode = 3;
        break;
    case 16:
        mn_804A04F0.hovered_selection = 5;
        mode = 3;
        break;
    default:
        mn_804A04F0.hovered_selection = 0;
        mode = 1;
        break;
    }

    proc = HSD_GObj_SetupProc(GObj_Create(0, 1, 0x80), fn_8022F538, 0);
    proc->flags_3 = HSD_GObj_804D783C;
    HSD_GObj_80390CD4(mn_80230E38(mode));
    mn_804D6BD4 = 1;
}

void mn_802317E4(HSD_Archive* archive, int arg1)
{
    mn_80231804(archive, arg1);
}

extern s32 mn_804D6BD4;

void mn_80231804(HSD_Archive* archive, int arg1)
{
    HSD_GObjProc* temp_r3;
    mn_804D6BC8.cooldown = 0x14;
    mn_804D6BC8.x2 = 0;
    mn_804D6BC8.x4 = 0;
    mn_804A04F0.buttons = 0;
    mn_804A04F0.prev_menu = mn_804A04F0.cur_menu;
    mn_804A04F0.cur_menu = 0xD;
    mn_804A04F0.hovered_selection = 0;
    HSD_SisLib_803A5E70();

    lbArchive_LoadSections(
        archive, (void**) &MenMainBack_Top.joint, "MenMainBack_Top_joint",
        &MenMainBack_Top.animjoint, "MenMainBack_Top_animjoint",
        &MenMainBack_Top.matanim_joint, "MenMainBack_Top_matanim_joint",
        &MenMainBack_Top.shapeanim_joint, "MenMainBack_Top_shapeanim_joint",

        &MenMain_cam, "ScMenMain_cam_int1_camera", &MenMain_lights,
        "ScMenMain_scene_lights", &MenMain_fog, "ScMenMain_fog",

        &MenMainPanel_Top.joint, "MenMainPanel_Top_joint",
        &MenMainPanel_Top.animjoint, "MenMainPanel_Top_animjoint",
        &MenMainPanel_Top.matanim_joint, "MenMainPanel_Top_matanim_joint",
        &MenMainPanel_Top.shapeanim_joint, "MenMainPanel_Top_shapeanim_joint",

        &MenMainConRl_Top.joint, "MenMainConRl_Top_joint",
        &MenMainConRl_Top.animjoint, "MenMainConRl_Top_animjoint",
        &MenMainConRl_Top.matanim_joint, "MenMainConRl_Top_matanim_joint",
        &MenMainConRl_Top.shapeanim_joint, "MenMainConRl_Top_shapeanim_joint",

        &MenMainCursorRl_Top.joint, "MenMainCursorRl_Top_joint",
        &MenMainCursorRl_Top.animjoint, "MenMainCursorRl_Top_animjoint",
        &MenMainCursorRl_Top.matanim_joint,
        "MenMainCursorRl_Top_matanim_joint",
        &MenMainCursorRl_Top.shapeanim_joint,
        "MenMainCursorRl_Top_shapeanim_joint",

        &MenMainCursorRl_Top.joint, "MenMainCursorRl_Top_joint",
        &MenMainCursorRl_Top.animjoint, "MenMainCursorRl_Top_animjoint",
        &MenMainCursorRl_Top.matanim_joint,
        "MenMainCursorRl_Top_matanim_joint",
        &MenMainCursorRl_Top.shapeanim_joint,
        "MenMainCursorRl_Top_shapeanim_joint",

        &MenMainNmRl_Top.joint, "MenMainNmRl_Top_joint",
        &MenMainNmRl_Top.animjoint, "MenMainNmRl_Top_animjoint",
        &MenMainNmRl_Top.matanim_joint, "MenMainNmRl_Top_matanim_joint",
        &MenMainNmRl_Top.shapeanim_joint, "MenMainNmRl_Top_shapeanim_joint",

        &MenMainCursorTr01_Top.joint, "MenMainCursorTr01_Top_joint",
        &MenMainCursorTr01_Top.animjoint, "MenMainCursorTr01_Top_animjoint",
        &MenMainCursorTr01_Top.matanim_joint,
        "MenMainCursorTr01_Top_matanim_joint",
        &MenMainCursorTr01_Top.shapeanim_joint,
        "MenMainCursorTr01_Top_shapeanim_joint",

        &MenMainCursorTr02_Top.joint, "MenMainCursorTr02_Top_joint",
        &MenMainCursorTr02_Top.animjoint, "MenMainCursorTr02_Top_animjoint",
        &MenMainCursorTr02_Top.matanim_joint,
        "MenMainCursorTr02_Top_matanim_joint",
        &MenMainCursorTr02_Top.shapeanim_joint,
        "MenMainCursorTr02_Top_shapeanim_joint",

        &MenMainCursorTr03_Top.joint, "MenMainCursorTr03_Top_joint",
        &MenMainCursorTr03_Top.animjoint, "MenMainCursorTr03_Top_animjoint",
        &MenMainCursorTr03_Top.matanim_joint,
        "MenMainCursorTr03_Top_matanim_joint",
        &MenMainCursorTr03_Top.shapeanim_joint,
        "MenMainCursorTr03_Top_shapeanim_joint",

        &MenMainCursorTr04_Top.joint, "MenMainCursorTr04_Top_joint",
        &MenMainCursorTr04_Top.animjoint, "MenMainCursorTr04_Top_animjoint",
        &MenMainCursorTr04_Top.matanim_joint,
        "MenMainCursorTr04_Top_matanim_joint",
        &MenMainCursorTr04_Top.shapeanim_joint,
        "MenMainCursorTr04_Top_shapeanim_joint",

        &MenMainCursorRl01_Top.joint, "MenMainCursorRl01_Top_joint",
        &MenMainCursorRl01_Top.animjoint, "MenMainCursorRl01_Top_animjoint",
        &MenMainCursorRl01_Top.matanim_joint,
        "MenMainCursorRl01_Top_matanim_joint",
        &MenMainCursorRl01_Top.shapeanim_joint,
        "MenMainCursorRl01_Top_shapeanim_joint",

        &MenMainCursorRl02_Top.joint, "MenMainCursorRl02_Top_joint",
        &MenMainCursorRl02_Top.animjoint, "MenMainCursorRl02_Top_animjoint",
        &MenMainCursorRl02_Top.matanim_joint,
        "MenMainCursorRl02_Top_matanim_joint",
        &MenMainCursorRl02_Top.shapeanim_joint,
        "MenMainCursorRl02_Top_shapeanim_joint",

        &MenMainCursorRl03_Top.joint, "MenMainCursorRl03_Top_joint",
        &MenMainCursorRl03_Top.animjoint, "MenMainCursorRl03_Top_animjoint",
        &MenMainCursorRl03_Top.matanim_joint,
        "MenMainCursorRl03_Top_matanim_joint",
        &MenMainCursorRl03_Top.shapeanim_joint,
        "MenMainCursorRl03_Top_shapeanim_joint",

        &MenMainCursorRl04_Top.joint, "MenMainCursorRl04_Top_joint",
        &MenMainCursorRl04_Top.animjoint, "MenMainCursorRl04_Top_animjoint",
        &MenMainCursorRl04_Top.matanim_joint,
        "MenMainCursorRl04_Top_matanim_joint",
        &MenMainCursorRl04_Top.shapeanim_joint,
        "MenMainCursorRl04_Top_shapeanim_joint",

        &MenMainCursorRl05_Top.joint, "MenMainCursorRl05_Top_joint",
        &MenMainCursorRl05_Top.animjoint, "MenMainCursorRl05_Top_animjoint",
        &MenMainCursorRl05_Top.matanim_joint,
        "MenMainCursorRl05_Top_matanim_joint",
        &MenMainCursorRl05_Top.shapeanim_joint,
        "MenMainCursorRl05_Top_shapeanim_joint",

        &MenMainConIs_Top.joint, "MenMainConIs_Top_joint",
        &MenMainConIs_Top.animjoint, "MenMainConIs_Top_animjoint",
        &MenMainConIs_Top.matanim_joint, "MenMainConIs_Top_matanim_joint",
        &MenMainConIs_Top.shapeanim_joint, "MenMainConIs_Top_shapeanim_joint",

        &MenMainCursorIs_Top.joint, "MenMainCursorIs_Top_joint",
        &MenMainCursorIs_Top.animjoint, "MenMainCursorIs_Top_animjoint",
        &MenMainCursorIs_Top.matanim_joint,
        "MenMainCursorIs_Top_matanim_joint",
        &MenMainCursorIs_Top.shapeanim_joint,
        "MenMainCursorIs_Top_shapeanim_joint",

        &MenMainConSs_Top.joint, "MenMainConSs_Top_joint",
        &MenMainConSs_Top.animjoint, "MenMainConSs_Top_animjoint",
        &MenMainConSs_Top.matanim_joint, "MenMainConSs_Top_matanim_joint",
        &MenMainConSs_Top.shapeanim_joint, "MenMainConSs_Top_shapeanim_joint",

        &MenMainCursorSs_Top.joint, "MenMainCursorSs_Top_joint",
        &MenMainCursorSs_Top.animjoint, "MenMainCursorSs_Top_animjoint",
        &MenMainCursorSs_Top.matanim_joint,
        "MenMainCursorSs_Top_matanim_joint",
        &MenMainCursorSs_Top.shapeanim_joint,
        "MenMainCursorSs_Top_shapeanim_joint",

        0);

    mn_804D6BD4 = arg1;
    mn_8022C304();
    mn_8022BCF8();
    mn_8022BEDC(mn_8022BE34());
    mn_80229B2C();
    mn_80229DC0();
    temp_r3 = HSD_GObj_SetupProc(GObj_Create(0, 1, 0x80), fn_8022F538, 0);
    temp_r3->flags_3 = HSD_GObj_804D783C;
    HSD_GObj_80390CD4(mn_80230E38(1));
    lbAudioAx_80023F28(gmMainLib_8015ECB0());
}

bool mn_80231F80(u8 arg0)
{
    if (gm_801A4310() == 0x1B && arg0 == 1) {
        return false;
    }
    if (arg0 == 3) {
        if (gmMainLib_8015EE0C()) {
            return true;
        }
        return false;
    }
    if (arg0 == 5) {
        if (gmMainLib_8015EE44()) {
            return true;
        }
        return false;
    }
    return true;
}
