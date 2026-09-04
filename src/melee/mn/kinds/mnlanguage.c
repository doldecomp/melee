#include "baselib/gobjuserdata.h"

#include "gm/forward.h"
#include "sc/forward.h"

#include <baselib/object.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjobject.h>
#include <sysdolphin/baselib/gobjplink.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/memory.h>
#include <sysdolphin/baselib/sislib.h>
#include <melee/lb/lbarchive.h>
#include <melee/lb/lbcardgame.h>
#include <melee/lb/lblanguage.h>
#include <melee/lb/lbspdisplay.h>
#include <melee/mn/inlines.h>
#include <melee/mn/kinds/mnlanguage.h>
#include <melee/mn/mnmain.h>

struct mnUserData {
    u8 x0, x1, x2, x3;
    u32 x4;
};

static HSD_GObj* mn_gobj;
static StaticModelDesc model_desc;
static f32 lang_jobj_frames[LANG_COUNT] = { 1.0f, 0.0f };
static AnimLoopSettings mnLanguage_803EF5A0 = { 0.0f, 19.0f, -0.1f };
static AnimLoopSettings mnLanguage_803EF5AC = { 20.0f, 29.0f, -0.1f };

void mnLanguage_8024BFE0(HSD_GObj* unused)
{
    u64 temp_r3;
    u8 lang;
    {
        struct mnUserData* user_data = HSD_GObjGetUserData(mn_gobj);
        if (mn_804D6BC8.cooldown != 0) {
            mn_804D6BC8.cooldown -= 1;
            mn_804D6BC8.x2 = 0;
            mn_804D6BC8.x4 = 0;
            return;
        }
        temp_r3 = Menu_GetAllInputs();
        if (temp_r3 & MenuInput_Back) {
            sfxBack();
            mn_804A04F0.entering_menu = 0;
            mn_80229894(4, 4, 3);
            return;
        }
        if (temp_r3 & MenuInput_AButton) {
            user_data = HSD_GObjGetUserData(mn_gobj);
            if (user_data->x1 != user_data->x0) {
                lbLang_SetSavedLanguage(user_data->x0);
                lbCardGame_UpdatePowerTime();
                lbAudioAx_80027AB0(0xAD);
                mn_80229860(GM_MENU);
                mn_8022F1A8(1, 9);
                mn_804A04F0.cur_menu = 4;
                mn_804A04F0.hovered_selection = 4;
            }
        } else if (user_data->x2 != 0) {
            if (temp_r3 & (1 << 2)) {
                sfxMove();
                user_data->x0 = user_data->x0 == 0 ? 1 : 0;
                lang = user_data->x0;
                {
                    HSD_JObj* result;
                    PAD_STACK(4);
                    lb_80011E24(mn_gobj->hsd_obj, &result, 1, -1);
                    HSD_JObjReqAnimAll(result, lang_jobj_frames[lang]);
                    mn_8022F3D8(result, -1, JOBJ_MASK);
                    HSD_JObjAnimAll(result);
                }
            } else if (temp_r3 & (1 << 3)) {
                sfxMove();
                user_data->x0 = user_data->x0 == 0 ? 1 : 0;
                lang = user_data->x0;
                {
                    HSD_JObj* result;
                    lb_80011E24(GET_JOBJ(mn_gobj), &result, 1, -1);
                    HSD_JObjReqAnimAll(result, lang_jobj_frames[lang]);
                    mn_8022F3D8(result, -1, JOBJ_MASK);
                    HSD_JObjAnimAll(result);
                }
            }
        }
    }
}

void fn_8024C210(HSD_GObj* gobj)
{
    PAD_STACK(4);
    {
        HSD_JObj* jobj = GET_JOBJ(gobj);
        if (mn_8022EC18(jobj, &mnLanguage_803EF5AC, MOBJ_MASK) >=
            mnLanguage_803EF5AC.end_frame)
        {
            HSD_GObjPLink_80390228(gobj);
        }
    }
}

void fn_8024C270(HSD_GObj* gobj)
{
    HSD_GObjProc* gobjproc;
    Menu* menu = GET_MENU(gobj);
    PAD_STACK(3 * 4);

    if (mn_804A04F0.cur_menu != 23) {
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        gobjproc = HSD_GObj_SetupProc(gobj, fn_8024C210, 0);
        gobjproc->flags_3 = HSD_GObj_804D783C;
        HSD_SisLib_803A5CC4(menu->text);
    }
}

void fn_8024C2E8(HSD_GObj* gobj)
{
    HSD_GObjProc* gobjproc;
    Menu* menu = gobj->user_data;
    HSD_JObj* jobj = GET_JOBJ(gobj);
    f32 tmp;

    if (mn_804A04F0.cur_menu != 23) {
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        gobjproc = HSD_GObj_SetupProc(gobj, fn_8024C210, 0);
        gobjproc->flags_3 = HSD_GObj_804D783C;
        HSD_SisLib_803A5CC4(menu->text);
        return;
    }

    tmp = mn_8022EC18(jobj, &mnLanguage_803EF5A0, MOBJ_MASK);
    if (tmp == mnLanguage_803EF5A0.end_frame) {
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        gobjproc = HSD_GObj_SetupProc(gobj, fn_8024C270, 0);
        gobjproc->flags_3 = HSD_GObj_804D783C;
        menu->unk2 = 1;
    }
}

#ifdef MUST_MATCH
static void order_sdata2(void)
{
    (void) -9.5f;
    (void) 9.1f;
    (void) 17.0f;
    (void) 364.68332f;
    (void) 38.38772f;
    (void) 0.0521f;
}
#endif

void mnLanguage_8024C3C4(HSD_GObj* arg0)
{
    HSD_GObj* gobj;
    HSD_GObjProc* gobjproc;
    HSD_JObj* jobj;
    HSD_Text* text;
    struct mnUserData* user_data;
    Menu* menu;
    u8 lang;
    PAD_STACK(2 * 4);

    gobj = GObj_Create(HSD_GOBJ_CLASS_ITEM, 7, MOBJ_MASK);
    mn_gobj = gobj;
    jobj = HSD_JObjLoadJoint(model_desc.joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_JObjKind, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 4, MOBJ_MASK);
    HSD_JObjAddAnimAll(jobj, model_desc.animjoint, model_desc.matanim_joint,
                       model_desc.shapeanim_joint);
    HSD_JObjReqAnimAll(jobj, 0.0F);
    HSD_JObjAnimAll(jobj);
    user_data = HSD_MemAlloc(sizeof(*user_data));
    HSD_ASSERTREPORT(355, user_data, "Can't get user_data.\n");
    lang = lbLang_GetSavedLanguage();
    user_data->x0 = lang;
    user_data->x1 = lang;
    user_data->x4 = 0;
    user_data->x2 = 0;
    GObj_InitUserData(gobj, 0, HSD_Free, user_data);
    gobjproc = HSD_GObj_SetupProc(gobj, fn_8024C2E8, 0);
    gobjproc->flags_3 = HSD_GObj_804D783C;
    lang = user_data->x0;
    {
        HSD_JObj* sp1C;
        PAD_STACK(2 * 4);
        lb_80011E24(GET_JOBJ(gobj), &sp1C, 1, -1);
        HSD_JObjReqAnimAll(sp1C, lang_jobj_frames[lang]);
        mn_8022F3D8(sp1C, -1, JOBJ_MASK);
        HSD_JObjAnimAll(sp1C);
    }
    HSD_JObjReqAnimAll(jobj, 0.0F);
    mn_8022F3D8(jobj, -1, MOBJ_MASK);
    HSD_JObjAnimAll(jobj);
    menu = GET_MENU(mn_gobj);
    if (menu->text != NULL) {
        HSD_SisLib_803A5CC4(menu->text);
    }
    Menu_InitCenterText(menu, 0xBF);
}

void mnLanguage_8024C5C0(HSD_GObj* gobj)
{
    HSD_GObjProc* gobjproc;
    HSD_Archive* archive;

    mn_804D6BC8.cooldown = 5;
    mn_804A04F0.prev_menu = mn_804A04F0.cur_menu;
    mn_804A04F0.cur_menu = 23;
    mn_804A04F0.hovered_selection = 0;
    archive = mn_804D6BB8;
    lbArchive_LoadSections(
        archive, (void**) &model_desc.joint, "MenMainConLa_Top_joint",
        &model_desc.animjoint, "MenMainConLa_Top_animjoint",
        &model_desc.matanim_joint, "MenMainConLa_Top_matanim_joint",
        &model_desc.shapeanim_joint, "MenMainConLa_Top_shapeanim_joint", 0);
    mnLanguage_8024C3C4(gobj);
    gobjproc =
        HSD_GObj_SetupProc(GObj_Create(0, 1, 0x80), mnLanguage_8024BFE0, 0);
    gobjproc->flags_3 = HSD_GObj_804D783C;
}
