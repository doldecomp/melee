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

/// #mnDataDel_8024EBC8                 /* unable to generate initializer: unknown type */

// void fn_8024ECCC(HSD_GObj* gp)
// {
//     HSD_JObj* sp3C;
//     HSD_JObj* sp38;
//     HSD_JObj* sp20;
//     HSD_JObj* sp1C;
//     HSD_Text* text;
//     f32 temp_f1;
//     f32 temp_f1_2;
//     s32 var_r30;
//     u8 temp_r30_2;
//     u8 temp_r30_3;
//     HSD_JObj* root;
//     struct WarnCmnData* data;

//     root = gp->hsd_obj;
//     data = mnDataDel_804D6C68->user_data;
//     lb_80011E24(root, &sp3C, 2, -1);
//     if ((u8) data->visible != 0) {
//         temp_f1 = mn_8022F298((HSD_JObj* ) root);
//         // M2C_ERROR(/* unknown instruction: cror eq, lt, eq */);
//         if ((mnDataDel_803EF870.x30.start_frame == temp_f1) && (temp_f1 < mnDataDel_803EF870.x30.end_frame)) {
//             temp_f1_2 = mn_8022EFD8(sp3C, (Point3d* ) &mnDataDel_803EF870.x30);
//             lb_80011E24((HSD_JObj* ) root, &sp38, 8, -1, temp_f1_2);
//             mn_8022EFD8(sp38, (Point3d* ) &mnDataDel_803EF870.x30);
//             // M2C_ERROR(/* unknown instruction: cror eq, gt, eq */);
//             if (temp_f1_2 == mnDataDel_803EF870.x30.end_frame) {
//                 temp_r30_2 = data->visible;
//                 if ((HSD_Text* ) mnDataDel_804D6C6C != NULL) {
//                     HSD_SisLib_803A5CC4(mnDataDel_804D6C6C);
//                 }
//                 if ((s32) temp_r30_2 == 1) {
//                     var_r30 = 0x13E;
//                 } else {
//                     var_r30 = 0x13F;
//                 }
//                 text = HSD_SisLib_803A5ACC(0, 1, mnDataDel_803EF870.x64, mnDataDel_803EF870.x68, mnDataDel_803EF870.x6C, 250.0f, 5.0f);
//                 mnDataDel_804D6C6C = text;
//                 text->font_size.x = 0.05f;
//                 text->font_size.y = 0.05f;
//                 text->default_alignment = 1;
//                 HSD_SisLib_803A6368(text, var_r30);
//             }
//         } else {
//             temp_r30_3 = data->cursor_idx;
//             lb_80011E24((HSD_JObj* ) temp_r28, &sp20, 7, -1);
//             lb_80011E24((HSD_JObj* ) temp_r28, &sp1C, 6, -1, temp_f1);
//             if ((s32) temp_r30_3 != 0) {
//                 HSD_JObjReqAnimAll(sp1C, 1.0f);
//                 HSD_JObjReqAnimAll(sp20, 0.0f);
//             } else {
//                 HSD_JObjReqAnimAll(sp1C, 0.0f);
//                 HSD_JObjReqAnimAll(sp20, 1.0f);
//             }
//             HSD_JObjAnimAll(sp1C);
//             HSD_JObjAnimAll(sp20);
//         }
//     } else {
//         HSD_SisLib_803A5CC4(mnDataDel_804D6C6C);
//         mnDataDel_804D6C6C = NULL;
//         HSD_GObjPLink_80390228(gp);
//     }
// }

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
    HSD_JObjAddAnimAll(root, mnDataDel_804A0938.animjoint, mnDataDel_804A0938.matanim_joint, mnDataDel_804A0938.shapeanim_joint);
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
