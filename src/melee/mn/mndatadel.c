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
#include "baselib/sislib.h"
#include "gm/gm_16F1.h"
#include "gm/gm_1A3F.h"
#include "gm/gmmain_lib.h"
#include "lb/lb_00F9.h"
#include "lb/lbarchive.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbcardgame.h"
#include "lb/lblanguage.h"
#include "mn/mnmain.h"
#include "sc/types.h"
#include "ty/toy.h"

/* Local declarations for gm_1601 functions with correct signatures */
void gm_801647D0(void);
u16 gm_801641CC(u8);
s32 gm_80164430(void);
s32 gm_80164250(u16);
void gm_801641E4(u8 stage, u8 enable);
void gm_801603B0(void);
void gm_8016505C(void);

void mnDataDel_8024E940(void)
{
    u8 _pad[8];
    HSD_JObj* child;
    u8 _pad2[16];
    f32 frame;
    struct MnDataDelUserData* data;
    s32 i;
    s32 found;
    f32 const_zero;

    data = mnDataDel_804D6C68->user_data;
    lb_80011E24((HSD_JObj*) mn_80231634(data->x10[mnDataDel_803EF8AC.x4]),
                &child, 1, -1);
    frame = mn_8022F298(child);
    const_zero = mnDataDel_804DC1A8;
    HSD_JObjReqAnimAll(child, const_zero);
    mn_8022F3D8(child, 0xFF, MOBJ_MASK);
    HSD_JObjAnimAll(child);
    HSD_JObjReqAnimAll(child, frame);
    mn_8022F3D8(child, 0xFF, 0x480);
    HSD_JObjAnimAll(child);
    data->x4 = 1;
    gm_801647D0();
    gmMainLib_8015F490();
    found = 0;
    i = 0;
    do {
        gm_801641CC((u8) i);
        if (gm_80164430() != 0 && (u8) gm_80164250((u16) i) != 0) {
            found = 1;
            break;
        }
        i++;
    } while (i < 29);
    if (found == 0) {
        gm_801641E4(0, 1);
    }
    gm_801729EC();
    lb_8001CE00();
}
void mnDataDel_8024EA6C(void)
{
    u8 _pad0[8];
    HSD_JObj* child;
    u8 _pad[16];
    f32 frame;
    struct MnDataDelUserData* data;
    s32* select_ptr;
    s32 saved_lang;
    s32 i;
    f32 const_zero;
    s32 offset;

    i = 0;
    select_ptr = &mnDataDel_803EF8AC.x0;
    const_zero = mnDataDel_804DC1A8;
    data = mnDataDel_804D6C68->user_data;
    do {
        lb_80011E24(
            (HSD_JObj*) mn_80231634(
                ((struct MnDataDelUserData*) mnDataDel_804D6C68->user_data)
                    ->x10[*select_ptr]),
            &child, 1, -1);
        frame = mn_8022F298(child);
        HSD_JObjReqAnimAll(child, const_zero);
        mn_8022F3D8(child, 0xFF, MOBJ_MASK);
        HSD_JObjAnimAll(child);
        HSD_JObjReqAnimAll(child, frame);
        mn_8022F3D8(child, 0xFF, 0x480);
        HSD_JObjAnimAll(child);
        offset = i + 3;
        i++;
        ((u8*) data)[offset] = 1;
        select_ptr++;
    } while (i < 6);
    saved_lang = lbLang_GetSavedLanguage();
    gmMainLib_8015FBA4();
    gm_801A3EF4();
    if (saved_lang == lbLang_GetSavedLanguage()) {
        lbAudioAx_800237A8(0xBF, 0x7F, 0x40);
    } else {
        lbLang_SetSavedLanguage(saved_lang);
        lbAudioAx_80027AB0(0xBF);
    }
    gm_801603B0();
    gmMainLib_8015F588((u8) gmMainLib_8015F4E8());
    gm_801729EC();
    lb_8001CE00();
}

void mnDataDel_8024EBC8(HSD_JObj* root, u8 arg1, u8 arg2)
{
    HSD_JObj* child1;
    HSD_JObj* child2;
    f32 anim_frame;
    struct MnDataDelData* data;
    HSD_JObj* root_copy;
    u8 a1;
    u8 a2;

    data = &mnDataDel_803EF870;
    a2 = arg2;
    a1 = arg1;
    root_copy = root;
    lb_80011E24(root_copy, &child1, 4, -1);
    if (a1 != 0) {
        anim_frame = mnDataDel_804DC1A8;
    } else {
        anim_frame = mnDataDel_804DC1AC;
    }
    HSD_JObjReqAnimAll(child1, anim_frame);
    mn_8022F3D8(child1, 0xFF, TOBJ_MASK);
    HSD_JObjAnimAll(child1);
    lb_80011E24(root_copy, &child2, 1, -1);
    if (a1 != 0) {
        if (a2 != 0) {
            anim_frame = data->x18.end_frame;
        } else {
            anim_frame = data->x18.start_frame;
        }
    } else {
        if (a2 != 0) {
            anim_frame = data->x24.end_frame;
        } else {
            anim_frame = data->x24.start_frame;
        }
    }
    HSD_JObjReqAnimAll(child2, anim_frame);
    mn_8022F3D8(child2, 0xFF, TOBJ_MASK);
    HSD_JObjAnimAll(child2);
}

/// @brief animates the warning modal
void fn_8024ECCC(HSD_GObj* gobj)
{
    HSD_JObj* panel;
    HSD_JObj* exclaim;
    HSD_JObj* cursor_yes;
    HSD_JObj* cursor_no;
    u8 _pad[16];
    f32 curr_frame;
    HSD_Text* text;
    s32 sis_id;
    u8 visible;
    u8 cursor_idx;
    f32* end_frame_ptr;
    struct MnDataDelData* menu_data;
    HSD_JObj* root;
    struct WarnCmnData* data;

    menu_data = &mnDataDel_803EF870;
    root = gobj->hsd_obj;
    data = mnDataDel_804D6C68->user_data;
    lb_80011E24(root, &panel, WARN_JOINT_PANEL, -1);
    if (data->visible != 0)
    {
        curr_frame = mn_8022F298(root);
        if ((menu_data->x30.start_frame <= curr_frame) && (curr_frame < menu_data->x30.end_frame))
        {
            end_frame_ptr = &menu_data->x30.end_frame;
            curr_frame = mn_8022EFD8(panel, &menu_data->x30);
            lb_80011E24(root, &exclaim, WARN_JOINT_EXCLAIM, -1);
            mn_8022EFD8(exclaim, &menu_data->x30);
            if (curr_frame >= *end_frame_ptr)
            {
                visible = data->visible;
                if (mnDataDel_804D6C6C != NULL) {
                    HSD_SisLib_803A5CC4(mnDataDel_804D6C6C);
                }
                if ((s32) visible == 1) {
                    sis_id = 318;
                } else {
                    sis_id = 319;
                }
                text = HSD_SisLib_803A5ACC(0, 1, menu_data->x64, menu_data->x68, menu_data->x6C, 250.0f, 5.0f);
                mnDataDel_804D6C6C = text;
                text->font_size.x = 0.05f;
                text->font_size.y = 0.05f;
                text->default_alignment = 1;
                HSD_SisLib_803A6368(text, sis_id);
            }
        } else
        {
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
    } else
    {
        HSD_SisLib_803A5CC4(mnDataDel_804D6C6C);
        mnDataDel_804D6C6C = NULL;
        HSD_GObjPLink_80390228(gobj);
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
    HSD_GObjProc_8038FD54(wrn_modal, fn_8024ECCC, 0U);
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

void fn_8024F1D4(HSD_GObj* arg0)
{
    u8 _pad[0x10];
    struct WarnCmnData* data;
    HSD_GObjProc* proc;
    u32 buttons;

    data = mnDataDel_804D6C68->user_data;
    buttons = mn_80229624(4);
    mn_804A04F0.buttons = (u64) buttons;
    if (buttons & 0x10) {
        if (data->cursor_idx != 0) {
            mnDataDel_8024EA6C();
        } else {
            lbAudioAx_80024030(0);
        }
        mn_804D6BC8.cooldown = 5;
        data->visible = 0;
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        proc = HSD_GObjProc_8038FD54(arg0, fn_8024F840, 0);
        proc->flags_3 = HSD_GObj_804D783C;
        return;
    }
    if (buttons & 0x20) {
        lbAudioAx_80024030(0);
        mn_804D6BC8.cooldown = 5;
        data->visible = 0;
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        proc = HSD_GObjProc_8038FD54(arg0, fn_8024F840, 0);
        proc->flags_3 = HSD_GObj_804D783C;
        return;
    }
    if ((buttons & 8) || (buttons & 4)) {
        lbAudioAx_80024030(2);
        if (data->cursor_idx != 0) {
            data->cursor_idx = 0;
            return;
        }
        data->cursor_idx = 1;
    }
}

void fn_8024F318(HSD_GObj* arg0)
{
    HSD_JObj* child;
    u8 _pad[0x58];
    f32 frame;
    struct WarnCmnData* data;
    struct MnDataDelData* data_tbl;
    HSD_GObj* gobj;
    HSD_GObjProc* proc;
    s32 sis_id;
    struct MnDataDelUserData* user_data;
    u32 buttons;
    u8 visible;

    data_tbl = &mnDataDel_803EF870;
    gobj = arg0;
    data = mnDataDel_804D6C68->user_data;
    buttons = mn_80229624(4);
    mn_804A04F0.buttons = (u64) buttons;
    if (buttons & 0x10) {
        mn_804D6BC8.cooldown = 5;
        if (data->x0 == 5) {
            HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
            if (data->cursor_idx != 0) {
                data->visible = 2;
                data->cursor_idx = 0;
                proc = HSD_GObjProc_8038FD54(gobj, fn_8024F1D4, 0);
                proc->flags_3 = HSD_GObj_804D783C;
                visible = data->visible;
                if (mnDataDel_804D6C6C != NULL) {
                    HSD_SisLib_803A5CC4(mnDataDel_804D6C6C);
                }
                if ((s32) visible == 1) {
                    sis_id = 0x13E;
                } else {
                    sis_id = 0x13F;
                }
                {
                    HSD_Text* text = HSD_SisLib_803A5ACC(
                        0, 1, data_tbl->x64, data_tbl->x68, data_tbl->x6C,
                        mnDataDel_804DC1C8, mnDataDel_804DC1CC);
                    f32 size = mnDataDel_804DC1D0;
                    mnDataDel_804D6C6C = text;
                    text->font_size.x = size;
                    text->font_size.y = size;
                    text->default_alignment = 1;
                    HSD_SisLib_803A6368(text, sis_id);
                }
                mn_804D6BC8.cooldown = 10;
                lbAudioAx_800237A8(0xBD, 0x7F, 0x40);
                return;
            }
            lbAudioAx_80024030(0);
            data->visible = 0;
            data->cursor_idx = 0;
            proc = HSD_GObjProc_8038FD54(gobj, fn_8024F840, 0);
            proc->flags_3 = HSD_GObj_804D783C;
            return;
        }
        if (data->cursor_idx != 0) {
            switch ((s32) data->x0) {
            case 0:
                user_data = mnDataDel_804D6C68->user_data;
                lb_80011E24(
                    (HSD_JObj*) mn_80231634(user_data->x10[data_tbl->x3C]),
                    &child, 1, -1);
                frame = mn_8022F298(child);
                HSD_JObjReqAnimAll(child, mnDataDel_804DC1A8);
                mn_8022F3D8(child, 0xFF, MOBJ_MASK);
                HSD_JObjAnimAll(child);
                HSD_JObjReqAnimAll(child, frame);
                mn_8022F3D8(child, 0xFF, 0x480);
                HSD_JObjAnimAll(child);
                user_data->x3 = 1;
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
                user_data = mnDataDel_804D6C68->user_data;
                lb_80011E24(
                    (HSD_JObj*) mn_80231634(user_data->x10[data_tbl->x44]),
                    &child, 1, -1);
                frame = mn_8022F298(child);
                HSD_JObjReqAnimAll(child, mnDataDel_804DC1A8);
                mn_8022F3D8(child, 0xFF, MOBJ_MASK);
                HSD_JObjAnimAll(child);
                HSD_JObjReqAnimAll(child, frame);
                mn_8022F3D8(child, 0xFF, 0x480);
                HSD_JObjAnimAll(child);
                user_data->pad[0] = 1;
                gmMainLib_8015EEC8();
                gm_801729EC();
                lb_8001CE00();
                break;
            case 3:
                user_data = mnDataDel_804D6C68->user_data;
                lb_80011E24(
                    (HSD_JObj*) mn_80231634(user_data->x10[data_tbl->x48]),
                    &child, 1, -1);
                frame = mn_8022F298(child);
                HSD_JObjReqAnimAll(child, mnDataDel_804DC1A8);
                mn_8022F3D8(child, 0xFF, MOBJ_MASK);
                HSD_JObjAnimAll(child);
                HSD_JObjReqAnimAll(child, frame);
                mn_8022F3D8(child, 0xFF, 0x480);
                HSD_JObjAnimAll(child);
                user_data->pad[1] = 1;
                gmMainLib_8015F150();
                gmMainLib_8015F260();
                gm_801729EC();
                lb_8001CE00();
                break;
            case 4:
                user_data = mnDataDel_804D6C68->user_data;
                lb_80011E24(
                    (HSD_JObj*) mn_80231634(user_data->x10[data_tbl->x4C]),
                    &child, 1, -1);
                frame = mn_8022F298(child);
                HSD_JObjReqAnimAll(child, mnDataDel_804DC1A8);
                mn_8022F3D8(child, 0xFF, MOBJ_MASK);
                HSD_JObjAnimAll(child);
                HSD_JObjReqAnimAll(child, frame);
                mn_8022F3D8(child, 0xFF, 0x480);
                HSD_JObjAnimAll(child);
                user_data->pad[2] = 1;
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
        data->visible = 0;
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        proc = HSD_GObjProc_8038FD54(gobj, fn_8024F840, 0);
        proc->flags_3 = HSD_GObj_804D783C;
        return;
    }
    if (buttons & 0x20) {
        lbAudioAx_80024030(0);
        mn_804D6BC8.cooldown = 5;
        data->visible = 0;
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        proc = HSD_GObjProc_8038FD54(gobj, fn_8024F840, 0);
        proc->flags_3 = HSD_GObj_804D783C;
        return;
    }
    if ((buttons & 8) || (buttons & 4)) {
        lbAudioAx_80024030(2);
        if (data->cursor_idx != 0) {
            data->cursor_idx = 0;
            return;
        }
        data->cursor_idx = 1;
    }
}

void fn_8024F840(HSD_GObj* arg0)
{
    u8 _pad[0x34];
    struct MnDataDelUserData* data;
    struct MnDataDelData* menu_data;
    s32 zero;
    struct MnDataDelUserData* data2;
    HSD_GObjProc* proc;
    HSD_Text* text;
    s16 sis_id;
    u32 buttons;

    menu_data = &mnDataDel_803EF870;
    data = mnDataDel_804D6C68->user_data;
    if (mn_804D6BC8.cooldown != 0) {
        mn_804D6BC8.cooldown -= 1;
        mn_804D6BC8.x2 = 0;
        mn_804D6BC8.x4 = 0;
        return;
    }
    buttons = mn_80229624(4);
    zero = 0;
    mn_804A04F0.buttons = (u64) buttons;
    if (buttons & 0x20) {
        lbAudioAx_80024030(0);
        mn_804A04F0.entering_menu = 0;
        mn_80229894(4, 5, 3);
        return;
    }
    if ((buttons & 0x10) && *((u8*)&data->x3 + data->x0) == 0) {
        data->x1 = 1;
        data->x2 = zero;
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        proc = HSD_GObjProc_8038FD54(arg0, fn_8024F318, 0);
        proc->flags_3 = HSD_GObj_804D783C;
        mnDataDel_8024EEC0();
        mn_804D6BC8.cooldown = 10;
        lbAudioAx_800237A8(0xBC, 0x7F, 0x40);
        return;
    }
    zero = 0;
    if (buttons & 1) {
        lbAudioAx_80024030(2);
        data2 = mnDataDel_804D6C68->user_data;
        mnDataDel_8024EBC8((HSD_JObj*) mn_80231634(data2->x10[((s32*)&menu_data->x3C)[data->x0]]), data->x0, 0);
        if (data->x0 != 0) {
            data->x0 = data->x0 - 1;
        } else {
            data->x0 = 5;
        }
        data2 = mnDataDel_804D6C68->user_data;
        mnDataDel_8024EBC8((HSD_JObj*) mn_80231634(data2->x10[((s32*)&menu_data->x3C)[data->x0]]), data->x0, 1);
        data = mnDataDel_804D6C68->user_data;
        text = *(HSD_Text**) &data->pad[7];
        if (text != NULL) {
            HSD_SisLib_803A5CC4(text);
        }
        sis_id = ((s16*)&menu_data->x58)[data->x0];
        text = HSD_SisLib_803A5ACC(0, 0, mnDataDel_804DC1B0, mnDataDel_804DC1B4, mnDataDel_804DC1B8, mnDataDel_804DC1BC, mnDataDel_804DC1C0);
        *(HSD_Text**) &data->pad[7] = text;
        text->font_size.x = mnDataDel_804DC1C4;
        text->font_size.y = mnDataDel_804DC1C4;
        HSD_SisLib_803A6368(text, sis_id);
        return;
    }
    if (buttons & 2) {
        lbAudioAx_80024030(2);
        data2 = mnDataDel_804D6C68->user_data;
        mnDataDel_8024EBC8((HSD_JObj*) mn_80231634(data2->x10[((s32*)&menu_data->x3C)[data->x0]]), data->x0, 0);
        if (data->x0 == 5) {
            data->x0 = 0;
        } else {
            data->x0 = data->x0 + 1;
        }
        data2 = mnDataDel_804D6C68->user_data;
        mnDataDel_8024EBC8((HSD_JObj*) mn_80231634(data2->x10[((s32*)&menu_data->x3C)[data->x0]]), data->x0, 1);
        data = mnDataDel_804D6C68->user_data;
        text = *(HSD_Text**) &data->pad[7];
        if (text != NULL) {
            HSD_SisLib_803A5CC4(text);
        }
        sis_id = ((s16*)&menu_data->x58)[data->x0];
        text = HSD_SisLib_803A5ACC(0, 0, mnDataDel_804DC1B0, mnDataDel_804DC1B4, mnDataDel_804DC1B8, mnDataDel_804DC1BC, mnDataDel_804DC1C0);
        *(HSD_Text**) &data->pad[7] = text;
        text->font_size.x = mnDataDel_804DC1C4;
        text->font_size.y = mnDataDel_804DC1C4;
        HSD_SisLib_803A6368(text, sis_id);
    }
}
void fn_8024FBA4(HSD_GObj* arg0)
{
    u8 _pad[8];
    HSD_JObj* jobj;
    struct MnDataDelData* menu_data;
    s32 i;
    struct MnDataDelUserData* data;
    f32 frame;

    menu_data = &mnDataDel_803EF870;
    jobj = arg0->hsd_obj;
    data = arg0->user_data;
    frame = mn_8022EE84(jobj, &menu_data->xC, 0x480);
    for (i = 0; i < 6; i++) {
        mn_8022EE84((HSD_JObj*) data->x10[((s32*) &menu_data->x3C)[i]],
                    &menu_data->xC, 0x480);
    }
    if (frame >= menu_data->xC.end_frame) {
        HSD_GObjPLink_80390228(arg0);
    }
}
void fn_8024FC48(HSD_GObj* arg0)
{
    u8 _pad[8];
    HSD_JObj* child;
    struct MnDataDelUserData* data;
    struct MnDataDelData* menu_data;
    s32 i;
    HSD_JObj* jobj;
    HSD_GObjProc* proc;

    menu_data = &mnDataDel_803EF870;
    data = arg0->user_data;
    if (mn_804A04F0.cur_menu != 0x18) {
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        proc = HSD_GObjProc_8038FD54(arg0, fn_8024FBA4, 0);
        proc->flags_3 = HSD_GObj_804D783C;
        HSD_SisLib_803A5CC4(*(HSD_Text**) &data->pad[7]);
        return;
    }
    for (i = 0; i < 6; i++) {
        jobj = (HSD_JObj*) mn_80231634(
            ((struct MnDataDelUserData*) arg0->user_data)
                ->x10[((s32*) &menu_data->x3C)[i]]);
        lb_80011E24(jobj, &child, 1, -1);
        if (data->x0 == i) {
            mn_8022EC18(child, (f32*) &menu_data->x18, 0x400);
        } else {
            mn_8022EC18(child, (f32*) &menu_data->x24, 0x400);
        }
    }
}
void fn_8024FD40(HSD_GObj* arg0)
{
    u8 _pad[0x14];
    s32 i;
    struct MnDataDelUserData* data;
    HSD_JObj* jobj;
    struct MnDataDelData* menu_data;
    HSD_GObjProc* proc;
    f32 frame;

    menu_data = &mnDataDel_803EF870;
    jobj = arg0->hsd_obj;
    data = arg0->user_data;
    if (mn_804A04F0.cur_menu != 0x18) {
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        proc = HSD_GObjProc_8038FD54(arg0, fn_8024FBA4, 0);
        proc->flags_3 = HSD_GObj_804D783C;
        HSD_SisLib_803A5CC4(*(HSD_Text**) &data->pad[7]);
        return;
    }
    frame = mn_8022EE84(jobj, &menu_data->x0, 0x480);
    for (i = 0; i < 6; i++) {
        mn_8022EE84((HSD_JObj*) data->x10[((s32*) &menu_data->x3C)[i]],
                    &menu_data->x0, 0x480);
    }
    if (frame == menu_data->x0.end_frame) {
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        proc = HSD_GObjProc_8038FD54(arg0, fn_8024FC48, 0);
        proc->flags_3 = HSD_GObj_804D783C;
    }
}
void mnDataDel_8024FE4C(u8 arg0)
{
    u8 _pad[0x18];
    HSD_JObj* child;
    HSD_GObj* gobj;
    HSD_JObj* root;
    HSD_GObjProc* proc;
    struct MnDataDelData* menu_data;
    StaticModelDesc* model;
    s32 i;
    struct MnDataDelUserData* data;
    HSD_Text* text;

    menu_data = &mnDataDel_803EF870;
    model = &mnDataDel_804A0918;
    gobj = GObj_Create(6, 7, 0x80);
    mnDataDel_804D6C68 = gobj;
    root = HSD_JObjLoadJoint(model->joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, root);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 4, 0x80);
    HSD_JObjAddAnimAll(root, model->animjoint, model->matanim_joint,
                       model->shapeanim_joint);
    HSD_JObjReqAnimAll(root, mnDataDel_804DC1AC);
    HSD_JObjAnimAll(root);
    data = (struct MnDataDelUserData*) HSD_MemAlloc(0x30);
    HSD_ASSERT(0x402, data != NULL);
    data->x0 = arg0;
    data->x1 = 0;
    data->x2 = 0;
    data->x3 = 0;
    data->x4 = 0;
    data->pad[0] = 0;
    data->pad[1] = 0;
    data->pad[2] = 0;
    data->pad[3] = 0;
    *(HSD_Text**) &data->pad[7] = NULL;
    GObj_InitUserData(gobj, 0, HSD_Free, data);
    for (i = 0; i < 8; i++) {
        lb_80011E24(root, (HSD_JObj**) &data->x10[i], i, -1);
    }
    proc = HSD_GObjProc_8038FD54(gobj, fn_8024FD40, 0);
    proc->flags_3 = HSD_GObj_804D783C;
    for (i = 0; i < 6; i++) {
        mnDataDel_8024EBC8(
            (HSD_JObj*) mn_80231634(data->x10[((s32*) &menu_data->x3C)[i]]),
            (u8) i, (u8) (data->x0 == i));
    }
    text = HSD_SisLib_803A5ACC(0, 0, mnDataDel_804DC1B0, mnDataDel_804DC1B4,
                               mnDataDel_804DC1B8, mnDataDel_804DC1BC,
                               mnDataDel_804DC1C0);
    *(HSD_Text**) &data->pad[7] = text;
    text->font_size.x = mnDataDel_804DC1C4;
    text->font_size.y = mnDataDel_804DC1C4;
    HSD_SisLib_803A6368(text, ((s16*) &menu_data->x58)[data->x0]);
}
void mnDataDel_80250170(void)
{
    HSD_GObjProc* proc;
    struct MnDataDelData* data;
    StaticModelDesc* model;

    data = &mnDataDel_803EF870;
    model = &mnDataDel_804A0918;
    mn_804D6BC8.cooldown = 5;
    mn_804A04F0.prev_menu = mn_804A04F0.cur_menu;
    mn_804A04F0.cur_menu = 0x18;
    mn_804A04F0.hovered_selection = 0;
    mnDataDel_804D6C6C = NULL;
    lbArchive_LoadSections(mn_804D6BB8, (void**) model, (char*) data + 0xA0,
                           &model->animjoint, (char*) data + 0xB8,
                           &model->matanim_joint, (char*) data + 0xD4,
                           &model->shapeanim_joint);
    mnDataDel_8024FE4C(0);
    proc = HSD_GObjProc_8038FD54(GObj_Create(0, 1, 0x80), fn_8024F840, 0);
    proc->flags_3 = HSD_GObj_804D783C;
}
