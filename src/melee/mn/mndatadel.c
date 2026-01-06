#include "mn/mndatadel.h"

#include "mn/mndatadel.static.h"

#include "placeholder.h"

#include "baselib/gobj.h"
#include "baselib/gobjgxlink.h"
#include "baselib/gobjobject.h"
#include "baselib/gobjplink.h"
#include "baselib/gobjproc.h"
#include "baselib/jobj.h"
#include "lb/lb_00F9.h"
#include "lb/lblanguage.h"
#include "mn/mnmain.h"
#include "sc/types.h"

/// #mnDataDel_8024E940

/// #mnDataDel_8024EA6C

/// #mnDataDel_8024EBC8                 /* unable to generate initializer:
/// unknown type */

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

    root = GET_JOBJ(arg0);
    data = mnDataDel_804D6C68->user_data;
    lb_80011E24(root, &panel, WARN_JOINT_PANEL, -1);
    if (data->visible != 0) {
        curr_frame = mn_8022F298(root);
        if ((mnDataDel_803EF8A0.start_frame <= curr_frame) &&
            (curr_frame < mnDataDel_803EF8A0.end_frame))
        {
            curr_frame = mn_8022EFD8(panel, &mnDataDel_803EF8A0);
            lb_80011E24(root, &exclaim, WARN_JOINT_EXCLAIM, -1, curr_frame);
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
                text = HSD_SisLib_803A5ACC(
                    0, 1, mnDataDel_803EF870.x64, mnDataDel_803EF870.x68,
                    mnDataDel_803EF870.x6C, 250.0f, 5.0f);
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

/// #fn_8024F1D4

/// #fn_8024F318

/// #fn_8024F840

/// #fn_8024FBA4

/// #fn_8024FC48

/// #fn_8024FD40

/// #mnDataDel_8024FE4C

/// #mnDataDel_80250170
