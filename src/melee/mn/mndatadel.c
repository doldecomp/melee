#include "mn/mndatadel.h"

#include "mn/mndatadel.static.h"

#include "placeholder.h"

#include "baselib/gobj.h"
#include "baselib/gobjgxlink.h"
#include "baselib/gobjobject.h"
#include "baselib/gobjplink.h"
#include "baselib/gobjproc.h"
#include "baselib/gobjuserdata.h"
#include "baselib/jobj.h"
#include "baselib/memory.h"
#include "gm/gm_1601.h"
#include "gm/gm_16F1.h"
#include "gm/gm_1A3F.h"
#include "gm/gmmain_lib.h"
#include "lb/lb_00F9.h"
#include "lb/lbarchive.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbcardgame.h"
#include "lb/lblanguage.h"
#include "mn/inlines.h"
#include "mn/mnmain.h"
#include "mn/mnmainrule.h"
#include "sc/types.h"
#include "sysdolphin/baselib/debug.h"
#include "ty/toy.h"

inline f32 mnDataDel_8024E940_inline(HSD_JObj* arg0)
{
    return mn_8022F298(arg0);
}

void mnDataDel_8024E940(void)
{
    u32 pad1;
    u32 pad2;
    u32 pad3;
    HSD_JObj* sp18;
    int tmp;
    f32 tmp2;
    f32 temp_f31;
    s32* data;
    s32 temp_ret;
    struct MnDataDelGObjUserData* temp_r31;
    int i;
    s32 var_r30;
    u32 pad4;

    temp_r31 = mnDataDel_804D6C68->user_data;
    temp_ret = mn_80231634(
        (struct mn_80231634_t*) temp_r31->x10[mnDataDel_803EF8AC[1]]);
    lb_80011E24((HSD_JObj*) temp_ret, &sp18, 1, -1);
    temp_f31 = mnDataDel_8024E940_inline(sp18);
    HSD_JObjReqAnimAll(sp18, (0, 1.0f));
    mn_8022F3D8(sp18, 0xFFU, MOBJ_MASK);
    tmp2 = temp_f31;
    HSD_JObjAnimAll(sp18);
    tmp = (enum _HSD_TypeMask) 0x480;
    HSD_JObjReqAnimAll(sp18, tmp2);
    mn_8022F3D8(sp18, 0xFFU, tmp);
    HSD_JObjAnimAll((0, sp18));
    temp_r31->x3[1] = 1;
    gm_801647D0();
    gmMainLib_8015F490();
    var_r30 = (i = 0);
    for (i = 0; i < 0x1D; i++) {
        if ((gm_80164430(gm_801641CC(i)) != 0) &&
            ((gm_80164250((u16) i) & (0xFFFF & 0xFF)) != 0))
        {
            var_r30 = 1;
            break;
        }
    }
    if (var_r30 == 0) {
        gm_801641E4(0U, 1U);
    }
    gm_801729EC();
    lb_8001CE00();
}

void mnDataDel_8024EA6C(void)
{
    f32 temp_f31;
    f32 temp_f30;
    struct MnDataDelGObjUserData* temp_r31;
    enum_t lang;
    int i;
    s32 temp_ret;
    u8 pad[0x8];
    HSD_JObj* sp18;
    PAD_STACK(0x10);

    temp_f30 = 1.0f;
    temp_r31 = mnDataDel_804D6C68->user_data;

    for (i = 0; i < 6; i++) {
        temp_ret = mn_80231634(
            (struct mn_80231634_t*) ((struct MnDataDelGObjUserData*)
                                         mnDataDel_804D6C68->user_data)
                ->x10[mnDataDel_803EF8AC[i]]);
        lb_80011E24((HSD_JObj*) temp_ret, &sp18, 1, -1);
        temp_f31 = mn_8022F298(sp18);
        HSD_JObjReqAnimAll(sp18, temp_f30);
        mn_8022F3D8(sp18, 0xFFU, MOBJ_MASK);
        HSD_JObjAnimAll(sp18);
        HSD_JObjReqAnimAll(sp18, temp_f31);
        mn_8022F3D8(sp18, 0xFFU, (enum _HSD_TypeMask) 0x480);
        HSD_JObjAnimAll(sp18);
        temp_r31->x3[i] = 1;
    }

    lang = lbLang_GetSavedLanguage();
    gmMainLib_8015FBA4();
    gm_801A3EF4();
    if (lang == lbLang_GetSavedLanguage()) {
        lbAudioAx_800237A8(0xBF, 0x7F, 0x40);
    } else {
        lbLang_SetSavedLanguage(lang);
        lbAudioAx_80027AB0(0xBF);
    }
    gm_801603B0();
    gmMainLib_8015F588((u8) gmMainLib_8015F4E8());
    gm_801729EC();
    lb_8001CE00();
}

void mnDataDel_8024EBC8(HSD_JObj* root, u8 unused, u8 a, u8 b)
{
    HSD_JObj* j2;
    HSD_JObj* j1;
    f32 frame;

    lb_80011E24(root, &j1, WARN_JOINT_PANEL_TEXT_BOTTOM, -1);
    HSD_JObjReqAnimAll(j1, a ? 1.0f : 0.0f);
    mn_8022F3D8(j1, 0xff, (HSD_TypeMask) 0x400);
    HSD_JObjAnimAll(j1);

    lb_80011E24(root, &j2, WARN_JOINT_BACKGROUND, -1);
    if (a) {
        if (b) {
            frame = mnDataDel_803EF888.end_frame;
        } else {
            frame = mnDataDel_803EF888.start_frame;
        }
    } else {
        if (b) {
            frame = mnDataDel_803EF894.end_frame;
        } else {
            frame = mnDataDel_803EF894.start_frame;
        }
    }
    HSD_JObjReqAnimAll(j2, frame);
    mn_8022F3D8(j2, 0xff, (HSD_TypeMask) 0x400);
    HSD_JObjAnimAll(j2);
}

/// @brief animates the warning modal
void fn_8024ECCC(HSD_GObj* arg0)
{
    HSD_JObj* root;
    HSD_JObj* panel;
    HSD_JObj* exclaim;
    HSD_JObj* cursor_no;
    HSD_JObj* cursor_yes;
    u8 _pad[10];
    f32 curr_frame;
    HSD_Text* text;
    s32 sis_id;
    u8 visible;
    u8 cursor_idx;
    struct WarnCmnData* data;
    PAD_STACK(16);

    root = GET_JOBJ(arg0);
    data = mnDataDel_804D6C68->user_data;
    lb_80011E24(root, &panel, WARN_JOINT_PANEL, -1);
    if (data->visible != 0) {
        curr_frame = mn_8022F298(root);
        if ((mnDataDel_803EF8A0.start_frame <= curr_frame) &&
            (curr_frame < mnDataDel_803EF8A0.end_frame))
        {
            curr_frame = mn_8022EFD8(panel, &mnDataDel_803EF8A0);
            lb_80011E24(root, &exclaim, WARN_JOINT_EXCLAIM, -1);
            mn_8022EFD8(exclaim, &mnDataDel_803EF8A0);
            if (curr_frame >= mnDataDel_803EF8A0.end_frame) {
                visible = data->visible;
                if (mnDataDel_804D6C6C != NULL) {
                    HSD_SisLib_803A5CC4(mnDataDel_804D6C6C);
                }
                if ((s32) visible == 1) {
                    sis_id = 318;
                } else {
                    sis_id = 319;
                }
                text =
                    HSD_SisLib_803A5ACC(0, 1, lbl_803EF8D4.x, lbl_803EF8D4.y,
                                        lbl_803EF8D4.z, 250.0f, 5.0f);
                mnDataDel_804D6C6C = text;
                text->font_size.x = 0.05f;
                text->font_size.y = 0.05f;
                text->default_alignment = 1;
                HSD_SisLib_803A6368(text, sis_id);
            }
        } else {
            cursor_idx = data->cursor_idx;
            lb_80011E24(root, &cursor_yes, WARN_JOINT_CURSOR_YES, -1);
            lb_80011E24(root, &cursor_no, WARN_JOINT_CURSOR_NO, -1);
            if ((s32) cursor_idx != 0) {
                HSD_JObjReqAnimAll(cursor_yes, 1.0f);
                HSD_JObjReqAnimAll(cursor_no, 0.0f);
            } else {
                HSD_JObjReqAnimAll(cursor_yes, 0.0f);
                HSD_JObjReqAnimAll(cursor_no, 1.0f);
            }
            HSD_JObjAnimAll(cursor_yes);
            HSD_JObjAnimAll(cursor_no);
        }
    } else {
        HSD_SisLib_803A5CC4(mnDataDel_804D6C6C);
        mnDataDel_804D6C6C = NULL;
        HSD_GObjPLink_80390228(arg0);
    }
}

/// @brief creates the warning modal
void mnDataDel_8024EEC0(void)
{
    HSD_JObj* cursor_yes;
    HSD_JObj* cursor_no;
    HSD_JObj* no;
    HSD_JObj* yes;
    HSD_JObj* root;
    f32 no_pos;
    f32 yes_pos;
    s32 is_english;
    s32 cursor;
    HSD_GObj* wrn_modal;
    struct WarnCmnData* data;
    PAD_STACK(4);

    data = mnDataDel_804D6C68->user_data;
    wrn_modal = GObj_Create(6U, 7U, 0x80U);
    root = HSD_JObjLoadJoint(mnDataDel_804A0938.joint);
    HSD_GObjObject_80390A70(wrn_modal, HSD_GObj_804D7849, root);
    GObj_SetupGXLink(wrn_modal, HSD_GObj_JObjCallback, 6U, 0x80U);
    HSD_GObj_SetupProc(wrn_modal, fn_8024ECCC, 0U);
    HSD_JObjAddAnimAll(root, mnDataDel_804A0938.animjoint,
                       mnDataDel_804A0938.matanim_joint,
                       mnDataDel_804A0938.shapeanim_joint);
    HSD_JObjReqAnimAll(root, mnDataDel_803EF8A0.start_frame);
    HSD_JObjAnimAll(root);
    // hide arrow and progress bar
    JObj_HideChildAtIdx(root, WARN_JOINT_EXCLAIM_ARROW);
    JObj_HideChildAtIdx(root, WARN_JOINT_PROGRESS_BAR);
    cursor = data->cursor_idx;
    lb_80011E24(root, &yes, WARN_JOINT_CURSOR_YES, -1);
    lb_80011E24(root, &no, WARN_JOINT_CURSOR_NO, -1);
    if (cursor != 0) {
        HSD_JObjReqAnimAll(yes, 1.0f);
        HSD_JObjReqAnimAll(no, 0.0f);
    } else {
        HSD_JObjReqAnimAll(yes, 0.0f);
        HSD_JObjReqAnimAll(no, 1.0f);
    }
    HSD_JObjAnimAll(yes);
    HSD_JObjAnimAll(no);

    is_english = lbLang_IsSavedLanguageUS();
    if (is_english != false) {
        lb_80011E24(root, &cursor_yes, WARN_JOINT_CURSOR_YES, -1);
        lb_80011E24(root, &cursor_no, WARN_JOINT_CURSOR_NO, -1);
        yes_pos = HSD_JObjGetTranslationX(cursor_yes);
        no_pos = HSD_JObjGetTranslationX(cursor_no);
        HSD_JObjSetTranslateX(cursor_yes, no_pos);
        HSD_JObjSetTranslateX(cursor_no, yes_pos);
    }
}

void fn_8024F1D4(HSD_GObj* gobj)
{
    HSD_GObjProc* proc;
    struct WarnCmnData* data;
    u32 input;
    PAD_STACK(16);

    data = mnDataDel_804D6C68->user_data;
    input = Menu_GetAllInputs();
    if (input & 0x10) {
        if (data->cursor_idx != 0) {
            mnDataDel_8024EA6C();
        } else {
            sfxBack();
        }
        mn_804D6BC8.cooldown = 5;
        data->visible = 0;
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        proc = HSD_GObj_SetupProc(gobj, fn_8024F840, 0);
        proc->flags_3 = HSD_GObj_804D783C;
    } else if (input & 0x20) {
        sfxBack();
        mn_804D6BC8.cooldown = 5;
        data->visible = 0;
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        proc = HSD_GObj_SetupProc(gobj, fn_8024F840, 0);
        proc->flags_3 = HSD_GObj_804D783C;
    } else if ((input & 8) || (input & 4)) {
        sfxMove();
        if (data->cursor_idx != 0) {
            data->cursor_idx = 0;
        } else {
            data->cursor_idx = 1;
        }
    }
}

void fn_8024F318(HSD_GObj* gobj)
{
    HSD_GObjProc* proc;
    HSD_Text* text;
    HSD_JObj* joint;
    f32 frame;
    s32 sis_id;
    u32 buttons;
    u8 cursor;
    struct MnDataDelGObjUserData* user_data;

    user_data = mnDataDel_804D6C68->user_data;
    buttons = mn_80229624(4U);
    mn_804A04F0.buttons = buttons;
    if (buttons & 0x10) {
        mn_804D6BC8.cooldown = 5;
        cursor = user_data->x0;
        if (cursor == 5) {
            HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
            if (user_data->x2 != 0) {
                user_data->x1 = 2U;
                user_data->x2 = 0U;
                proc = HSD_GObj_SetupProc(gobj, fn_8024F1D4, 0U);
                proc->flags_3 = HSD_GObj_804D783C;
                if (mnDataDel_804D6C6C != NULL) {
                    HSD_SisLib_803A5CC4(mnDataDel_804D6C6C);
                }
                if ((s32) user_data->x1 == 1) {
                    sis_id = 0x13E;
                } else {
                    sis_id = 0x13F;
                }
                text =
                    HSD_SisLib_803A5ACC(0, 1, lbl_803EF8D4.x, lbl_803EF8D4.y,
                                        lbl_803EF8D4.z, 250.0f, 5.0f);
                mnDataDel_804D6C6C = text;
                text->font_size.x = 0.05f;
                text->font_size.y = 0.05f;
                text->default_alignment = 1;
                HSD_SisLib_803A6368(text, sis_id);
                mn_804D6BC8.cooldown = 0xA;
                lbAudioAx_800237A8(0xBD, 0x7F, 0x40);
                return;
            }
            lbAudioAx_80024030(0);
            user_data->x1 = 0U;
            user_data->x2 = 0U;
            proc = HSD_GObj_SetupProc(gobj, fn_8024F840, 0U);
            proc->flags_3 = HSD_GObj_804D783C;
            return;
        }
        if (user_data->x2 != 0) {
            switch ((s32) cursor) {
            case 0:
                joint = (HSD_JObj*) mn_80231634(
                    (struct mn_80231634_t*)
                        user_data->x10[mnDataDel_803EF8AC[0]]);
                lb_80011E24(joint, &joint, 1, -1);
                frame = mn_8022F298(joint);
                HSD_JObjReqAnimAll(joint, 1.0f);
                mn_8022F3D8(joint, 0xFFU, MOBJ_MASK);
                HSD_JObjAnimAll(joint);
                HSD_JObjReqAnimAll(joint, frame);
                mn_8022F3D8(joint, 0xFFU, (enum _HSD_TypeMask) 0x480);
                HSD_JObjAnimAll(joint);
                user_data->x3[0] = 1;
                gm_8016505C();
                gmMainLib_8015F464();
                gm_801729EC();
                lb_8001CE00();
                gmMainLib_8015DB80();
                break;
            case 1:
                mnDataDel_8024E940();
                break;
            case 2:
                joint = (HSD_JObj*) mn_80231634(
                    (struct mn_80231634_t*)
                        user_data->x10[mnDataDel_803EF8AC[2]]);
                lb_80011E24(joint, &joint, 1, -1);
                frame = mn_8022F298(joint);
                HSD_JObjReqAnimAll(joint, 1.0f);
                mn_8022F3D8(joint, 0xFFU, MOBJ_MASK);
                HSD_JObjAnimAll(joint);
                HSD_JObjReqAnimAll(joint, frame);
                mn_8022F3D8(joint, 0xFFU, (enum _HSD_TypeMask) 0x480);
                HSD_JObjAnimAll(joint);
                user_data->x3[2] = 1;
                gmMainLib_8015EEC8();
                gm_801729EC();
                lb_8001CE00();
                break;
            case 3:
                joint = (HSD_JObj*) mn_80231634(
                    (struct mn_80231634_t*)
                        user_data->x10[mnDataDel_803EF8AC[3]]);
                lb_80011E24(joint, &joint, 1, -1);
                frame = mn_8022F298(joint);
                HSD_JObjReqAnimAll(joint, 1.0f);
                mn_8022F3D8(joint, 0xFFU, MOBJ_MASK);
                HSD_JObjAnimAll(joint);
                HSD_JObjReqAnimAll(joint, frame);
                mn_8022F3D8(joint, 0xFFU, (enum _HSD_TypeMask) 0x480);
                HSD_JObjAnimAll(joint);
                user_data->x3[3] = 1;
                gmMainLib_8015F150();
                gmMainLib_8015F260();
                gm_801729EC();
                lb_8001CE00();
                break;
            case 4:
                joint = (HSD_JObj*) mn_80231634(
                    (struct mn_80231634_t*)
                        user_data->x10[mnDataDel_803EF8AC[4]]);
                lb_80011E24(joint, &joint, 1, -1);
                frame = mn_8022F298(joint);
                HSD_JObjReqAnimAll(joint, 1.0f);
                mn_8022F3D8(joint, 0xFFU, MOBJ_MASK);
                HSD_JObjAnimAll(joint);
                HSD_JObjReqAnimAll(joint, frame);
                mn_8022F3D8(joint, 0xFFU, (enum _HSD_TypeMask) 0x480);
                HSD_JObjAnimAll(joint);
                user_data->x3[4] = 1;
                un_80311960();
                gmMainLib_8015F4BC();
                gm_80174238();
                gm_801729EC();
                lb_8001CE00();
                break;
            }
            lbAudioAx_800237A8(0xBE, 0x7F, 0x40);
        } else {
            lbAudioAx_80024030(0);
        }
        user_data->x1 = 0U;
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        proc = HSD_GObj_SetupProc(gobj, fn_8024F840, 0U);
        proc->flags_3 = HSD_GObj_804D783C;
        return;
    }
    if (buttons & 0x20) {
        lbAudioAx_80024030(0);
        mn_804D6BC8.cooldown = 5;
        user_data->x1 = 0U;
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        proc = HSD_GObj_SetupProc(gobj, fn_8024F840, 0U);
        proc->flags_3 = HSD_GObj_804D783C;
        return;
    }
    if ((buttons & 8) || (buttons & 4)) {
        lbAudioAx_80024030(2);
        if (user_data->x2 != 0) {
            user_data->x2 = 0U;
            return;
        }
        user_data->x2 = 1U;
    }
}

void fn_8024F840(HSD_GObj* gobj)
{
    HSD_GObjProc* proc;
    HSD_Text* text;
    HSD_JObj* joint;
    u16 sis_id;
    u32 buttons;
    u8 cursor;
    struct MnDataDelGObjUserData* user_data;

    user_data = mnDataDel_804D6C68->user_data;
    if (mn_804D6BC8.cooldown != 0) {
        mn_804D6BC8.cooldown--;
        mn_804D6BC8.x2 = 0;
        mn_804D6BC8.x4 = 0;
        return;
    }
    buttons = mn_80229624(4U);
    mn_804A04F0.buttons = buttons;
    if (buttons & 0x20) {
        lbAudioAx_80024030(0);
        mn_804A04F0.entering_menu = 0;
        mn_80229894(4, 5U, 3);
        return;
    }
    if ((buttons & 0x10) && ((u8*) &user_data->x3)[user_data->x0] == 0) {
        user_data->x1 = 1;
        user_data->x2 = 0;
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        proc = HSD_GObj_SetupProc(gobj, fn_8024F318, 0U);
        proc->flags_3 = HSD_GObj_804D783C;
        mnDataDel_8024EEC0();
        mn_804D6BC8.cooldown = 0xA;
        lbAudioAx_800237A8(0xBC, 0x7F, 0x40);
        return;
    }
    if (buttons & 1) {
        lbAudioAx_80024030(2);
        joint = (HSD_JObj*) mn_80231634(
            (struct mn_80231634_t*)
                user_data->x10[mnDataDel_803EF8AC[user_data->x0]]);
        mnDataDel_8024EBC8(joint, user_data->x0, 0U, 0U);
        cursor = user_data->x0;
        if (cursor != 0) {
            user_data->x0 = cursor - 1;
        } else {
            user_data->x0 = 5U;
        }
        joint = (HSD_JObj*) mn_80231634(
            (struct mn_80231634_t*)
                user_data->x10[mnDataDel_803EF8AC[user_data->x0]]);
        mnDataDel_8024EBC8(joint, user_data->x0, 1U, 0U);
        user_data = mnDataDel_804D6C68->user_data;
        if (user_data->xC != NULL) {
            HSD_SisLib_803A5CC4(user_data->xC);
        }
        sis_id = mnDataDel_803EF8C8[user_data->x0];
        text = HSD_SisLib_803A5ACC(0, 0, -9.5f, 9.1f, 17.0f, 364.68332f,
                                   38.38772f);
        user_data->xC = text;
        text->font_size.x = 0.0521f;
        text->font_size.y = 0.0521f;
        HSD_SisLib_803A6368(text, (s32) sis_id);
        return;
    }
    if (buttons & 2) {
        lbAudioAx_80024030(2);
        joint = (HSD_JObj*) mn_80231634(
            (struct mn_80231634_t*)
                user_data->x10[mnDataDel_803EF8AC[user_data->x0]]);
        mnDataDel_8024EBC8(joint, user_data->x0, 0U, 0U);
        cursor = user_data->x0;
        if (cursor == 5) {
            user_data->x0 = 0U;
        } else {
            user_data->x0 = cursor + 1;
        }
        joint = (HSD_JObj*) mn_80231634(
            (struct mn_80231634_t*)
                user_data->x10[mnDataDel_803EF8AC[user_data->x0]]);
        mnDataDel_8024EBC8(joint, user_data->x0, 1U, 0U);
        user_data = mnDataDel_804D6C68->user_data;
        if (user_data->xC != NULL) {
            HSD_SisLib_803A5CC4(user_data->xC);
        }
        sis_id = mnDataDel_803EF8C8[user_data->x0];
        text = HSD_SisLib_803A5ACC(0, 0, -9.5f, 9.1f, 17.0f, 364.68332f,
                                   38.38772f);
        user_data->xC = text;
        text->font_size.x = 0.0521f;
        text->font_size.y = 0.0521f;
        HSD_SisLib_803A6368(text, (s32) sis_id);
    }
}

void fn_8024FBA4(HSD_GObj* gobj)
{
    s32 i;
    f32 frame;
    struct MnDataDelData* data;
    u8* user_data;
    PAD_STACK(8);

    data = &mnDataDel_803EF870;
    user_data = gobj->user_data;
    frame = mn_8022EE84(GET_JOBJ(gobj), &mnDataDel_803EF870.xC,
                        (enum _HSD_TypeMask) 0x480);
    for (i = 0; i < 6; i++) {
        mn_8022EE84(
            *(HSD_JObj**) (user_data + mnDataDel_803EF8AC[i] * 4 + 0x10),
            &data->xC, (enum _HSD_TypeMask) 0x480);
    }
    if (frame >= data->xC.end_frame) {
        HSD_GObjPLink_80390228(gobj);
    }
}

inline HSD_JObj* fn_8024FC48_inline(int arg0);
inline HSD_JObj* fn_8024FC48_inline(int arg0)
{
    return (HSD_JObj*) arg0;
}

void fn_8024FC48(HSD_GObj* gobj)
{
    s32 i;
    HSD_JObj* jobj;
    u8* user_data;

    user_data = gobj->user_data;

    if (mn_804A04F0.cur_menu != 0x18) {
        HSD_GObjProc* proc;
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        proc = HSD_GObj_SetupProc(gobj, fn_8024FBA4, 0);
        proc->flags_3 = HSD_GObj_804D783C;
        HSD_SisLib_803A5CC4(*(HSD_Text**) (user_data + 0xC));
    } else {
        for (i = 0; i < 6; i++) {
            lb_80011E24(
                fn_8024FC48_inline(mn_80231634(
                    *(struct mn_80231634_t**) ((u8*) gobj->user_data +
                                               mnDataDel_803EF8AC[i] * 4 +
                                               0x10))),
                &jobj, 1, -1);
            if (user_data[0] == i) {
                mn_8022EC18(jobj, &mnDataDel_803EF888, (HSD_TypeMask) 0x400);
            } else {
                mn_8022EC18(jobj, &mnDataDel_803EF894, (HSD_TypeMask) 0x400);
            }
        }
    }
}

void fn_8024FD40(HSD_GObj* gobj)
{
    f32 frame;
    s32 i;
    struct MnDataDelGObjUserData* user_data;
    HSD_GObjProc* proc;
    HSD_JObj* jobj;
    PAD_STACK(16);

    jobj = GET_JOBJ(gobj);
    user_data = gobj->user_data;
    if ((u8) mn_804A04F0.cur_menu != 0x18) {
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        proc = HSD_GObj_SetupProc(gobj, fn_8024FBA4, 0);
        proc->flags_3 = HSD_GObj_804D783C;
        HSD_SisLib_803A5CC4(user_data->xC);
        return;
    }
    frame =
        mn_8022EE84(jobj, &mnDataDel_803EF870.x0, (enum _HSD_TypeMask) 0x480);
    for (i = 0; i < 6; i++) {
        mn_8022EE84(user_data->x10[mnDataDel_803EF8AC[i]],
                    &mnDataDel_803EF870.x0, (enum _HSD_TypeMask) 0x480);
    }
    if (frame == mnDataDel_803EF870.x0.end_frame) {
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        proc = HSD_GObj_SetupProc(gobj, fn_8024FC48, 0);
        proc->flags_3 = HSD_GObj_804D783C;
    }
}

void mnDataDel_8024FE4C(u8 arg0)
{
    HSD_JObj* child;
    HSD_GObj* gobj;
    HSD_GObjProc* proc;
    HSD_JObj* root;
    HSD_JObj* joint;
    HSD_Text* text;
    f32 frame;
    s32 enabled;
    s32 i;
    u16 sis_id;
    u8 is_enabled;
    struct MnDataDelGObjUserData* user_data;

    gobj = GObj_Create(6U, 7U, 0x80U);
    mnDataDel_804D6C68 = gobj;
    root = HSD_JObjLoadJoint(mnDataDel_804A0918.joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, root);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 4U, 0x80U);
    HSD_JObjAddAnimAll(root, mnDataDel_804A0918.animjoint,
                       mnDataDel_804A0918.matanim_joint,
                       mnDataDel_804A0918.shapeanim_joint);
    HSD_JObjReqAnimAll(root, 0.0f);
    HSD_JObjAnimAll(root);
    user_data = HSD_MemAlloc(0x30);
    HSD_ASSERTREPORT(0x402, user_data, "Can't get user_data.\n");
    user_data->x0 = arg0;
    user_data->x1 = 0;
    user_data->x2 = 0;
    for (i = 0; i < ARRAY_SIZE(user_data->x3); i++) {
        user_data->x3[i] = 0;
    }
    user_data->xC = NULL;
    GObj_InitUserData(gobj, 0U, HSD_Free, user_data);
    for (i = 0; i < (int) ARRAY_SIZE(user_data->x10); i++) {
        lb_80011E24(root, &user_data->x10[i], i, -1);
    }
    proc = HSD_GObj_SetupProc(gobj, fn_8024FD40, 0U);
    proc->flags_3 = HSD_GObj_804D783C;
    for (i = 0; i < 6; i++) {
        joint = HSD_JObjLoadJoint(mnDataDel_804A0928.joint);
        HSD_JObjAddAnimAll(joint, mnDataDel_804A0928.animjoint,
                           mnDataDel_804A0928.matanim_joint,
                           mnDataDel_804A0928.shapeanim_joint);
        HSD_JObjReqAnimAll(joint, (f32) i);
        HSD_JObjAnimAll(joint);
        HSD_JObjAddChild(user_data->x10[mnDataDel_803EF8AC[i]], joint);
        mnDataDel_8024EBC8(joint, i, user_data->x0 == i, 1U);
        is_enabled = ((u8*) &user_data->x3)[i];
        lb_80011E24(joint, &child, 1, -1);
        frame = mn_8022F298(child);
        if (is_enabled != 0) {
            enabled = 1;
        } else {
            enabled = 0;
        }
        HSD_JObjReqAnimAll(child, (f32) enabled);
        mn_8022F3D8(child, 0xFFU, MOBJ_MASK);
        HSD_JObjAnimAll(child);
        HSD_JObjReqAnimAll(child, frame);
        mn_8022F3D8(child, 0xFFU, (enum _HSD_TypeMask) 0x480);
        HSD_JObjAnimAll(child);
    }
    user_data = gobj->user_data;
    if (user_data->xC != NULL) {
        HSD_SisLib_803A5CC4(user_data->xC);
    }
    sis_id = mnDataDel_803EF8C8[user_data->x0];
    text =
        HSD_SisLib_803A5ACC(0, 0, -9.5f, 9.1f, 17.0f, 364.68332f, 38.38772f);
    user_data->xC = text;
    text->font_size.x = 0.0521f;
    text->font_size.y = 0.0521f;
    HSD_SisLib_803A6368(text, (s32) sis_id);
}

void mnDataDel_80250170(void)
{
    HSD_GObjProc* proc;

    mn_804D6BC8.cooldown = 5;
    mn_804A04F0.prev_menu = mn_804A04F0.cur_menu;
    mn_804A04F0.cur_menu = 0x18;
    mn_804A04F0.hovered_selection = 0;
    mnDataDel_804D6C6C = NULL;
    lbArchive_LoadSections(
        mn_804D6BB8, (void**) &mnDataDel_804A0918.joint,
        "MenMainConDl_Top_joint", &mnDataDel_804A0918.animjoint,
        "MenMainConDl_Top_animjoint", &mnDataDel_804A0918.matanim_joint,
        "MenMainConDl_Top_matanim_joint", &mnDataDel_804A0918.shapeanim_joint,
        "MenMainConDl_Top_shapeanim_joint", &mnDataDel_804A0928.joint,
        "MenMainCursorDl_Top_joint", &mnDataDel_804A0928.animjoint,
        "MenMainCursorDl_Top_animjoint", &mnDataDel_804A0928.matanim_joint,
        "MenMainCursorDl_Top_matanim_joint",
        &mnDataDel_804A0928.shapeanim_joint,
        "MenMainCursorDl_Top_shapeanim_joint", &mnDataDel_804A0938.joint,
        "MenMainWarCmn_Top_joint", &mnDataDel_804A0938.animjoint,
        "MenMainWarCmn_Top_animjoint", &mnDataDel_804A0938.matanim_joint,
        "MenMainWarCmn_Top_matanim_joint", &mnDataDel_804A0938.shapeanim_joint,
        "MenMainWarCmn_Top_shapeanim_joint", 0);
    mnDataDel_8024FE4C(0U);
    proc = HSD_GObj_SetupProc(GObj_Create(0U, 1U, 0x80U), fn_8024F840, 0U);
    proc->flags_3 = HSD_GObj_804D783C;
}
