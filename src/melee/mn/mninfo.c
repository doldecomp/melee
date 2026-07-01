#include "mninfo.h"

#include "placeholder.h"

#include "gm/gm_1601.h"
#include "gm/gmmain_lib.h"
#include "gm/types.h"
#include "if/ifprize.h"
#include "lb/lbarchive.h"
#include "lb/lbaudio_ax.h"
#include "lb/lblanguage.h"
#include "lb/lbspdisplay.h"
#include "mn/inlines.h"
#include "mn/mnmain.h"
#include "sc/types.h"

#include <sysdolphin/baselib/debug.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjobject.h>
#include <sysdolphin/baselib/gobjplink.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/memory.h>
#include <sysdolphin/baselib/sislib.h>

typedef struct MnInfoTextCursor {
    /* +00 */ u8 pad_x0[8];
    /* +08 */ HSD_Text* left;
    /* +0C */ u8 pad_xC[12];
    /* +18 */ HSD_Text* right;
} MnInfoTextCursor;

typedef struct MnInfoDataLayout {
    AnimLoopSettings anim;
    u32 sis_ids[4];
    char date_format[0xC];
    char time_format[0xC];
    char assert_report[0x18];
    char assert_file[0xC];
    char assert_expr[0xC];
    char top_joint[0x18];
    char top_animjoint[0x1C];
    char top_matanim_joint[0x20];
    char top_shapeanim_joint[0x28];
} MnInfoDataLayout;

u8 mnInfo_804A0968[0x48];
HSD_GObj* mnInfo_804D6C78;
extern GXColor mn_804D4B64;

#pragma push
#pragma dont_inline on
s32 mnInfo_80251A08(s32 arg0)
{
    switch (arg0) { /* irregular */
    case 0x3E:
        return 0;
    case 0x34:
        if (lbLang_IsSettingUS() != 0) {
            return 0;
        }
        return gmMainLib_8015D94C(arg0);
    case 0x35:
        if (lbLang_IsSettingJP() != 0) {
            return 0;
        }
        return gmMainLib_8015D94C(arg0);
    default:
        return gmMainLib_8015D94C(arg0);
    }
}
#pragma pop

#pragma push
#pragma dont_inline on
s32 mnInfo_80251AA4(void)
{
    s32 i;
    s32 var_r30 = 0;

    for (i = 0; i < 0x42; i++) {
        if (mnInfo_80251A08(i) != 0) {
            var_r30++;
        }
    }
    return var_r30;
}
#pragma pop

s32 mnInfo_80251AFC(void)
{
    s32 i;
    s32 j;
    PAD_STACK(8);

    for (i = 0; 0x42 > i; i++) {
        mnInfo_804A0968[i] = i;
    }
    for (i = 0; i < 0x42; i++) {
        for (j = i + 1; j < 0x42; j++) {
            if (mnInfo_80251A08(mnInfo_804A0968[i]) == 0) {
                u8 tmp = mnInfo_804A0968[i];

                mnInfo_804A0968[i] = mnInfo_804A0968[j];
                mnInfo_804A0968[j] = tmp;
            }
        }
    }
    for (i = 0; i < 0x42; i++) {
        for (j = i + 1; j < 0x42; j++) {
            if (mnInfo_80251A08(mnInfo_804A0968[j]) != 0 &&
                (mnInfo_80251A08(mnInfo_804A0968[i]) == 0 ||
                 *gmMainLib_8015D804(mnInfo_804A0968[i]) >
                     *gmMainLib_8015D804(mnInfo_804A0968[j])))
            {
                u8 tmp = mnInfo_804A0968[i];

                mnInfo_804A0968[i] = mnInfo_804A0968[j];
                mnInfo_804A0968[j] = tmp;
            }
        }
    }
    return 0;
}

static AnimLoopSettings mnInfo_803EFC08[0x12] = {
    { 0.0f, 199.0f, 0.0f },
    { 1.8e-42f, 1.802e-42f, 1.803e-42f },
    { 1.805e-42f, 2.1092525e-16f, 1.379729e31f },
    { 0.0f, 2.109659e-16f, 1.4748028e31f },
    { 0.0f, 225.43028f, 5.083402e31f },
    { 5.085142e31f, 7.153577e22f, 2.817505e20f },
    { 6.162976e-33f, 4.6115556e27f, 2.8237532e23f },
    { 0.0f, 3.0854143e32f, 1.6456562e19f },
    { 1.4757395e20f, 2.405757e8f, 2.6912729e20f },
    { 7.3738955e28f, 1.5307577e19f, 1.6892836e19f },
    { 1.8878586e28f, 2.405757e8f, 2.6912729e20f },
    { 7.3738955e28f, 1.5307577e19f, 1.6244036e19f },
    { 4.5346362e27f, 1.8878586e28f, 2.405757e8f },
    { 2.6912729e20f, 7.3738955e28f, 1.5307577e19f },
    { 1.710508e19f, 2.7487011e20f, 1.6892836e19f },
    { 1.8878586e28f, 2.405757e8f, 2.6912729e20f },
    { 7.3738955e28f, 1.5307577e19f, 1.7539375e19f },
    { 2.8395941e29f, 1.7935375e25f, 7.2243537e28f },
};

#pragma push
#pragma dont_inline on
s32 mnInfo_80251D58(MenuInfo_GObj* arg0, s32 arg1, u32 arg2, u32 arg3)
{
    char sp34[5];
    char sp30[3];
    char sp2C[3];
    char sp28[3];
    char sp24[3];
    char sp20[3];
    datetime sp18;
    HSD_Text** slot;
    HSD_Text* text;
    MnInfoData* data;
    MnInfoDataLayout* layout;

    data = arg0->user_data;
    layout = (MnInfoDataLayout*) mnInfo_803EFC08;
    slot = (HSD_Text**) ((u8*) data + (arg1 * 4));
    if (*(slot += 2) != NULL) {
        HSD_SisLib_803A5CC4(data->left_column[arg1]);
    }
    text = HSD_SisLib_803A6754(0, 1);
    *slot = text;
    text->pos_x = -7.5f;
    text->pos_y = (3.45f * (f32) arg1) + -5.8f;
    text->pos_z = 17.0f;
    text->text_color = mn_804D4B64;
    text->default_alignment = 2;
    text->font_size.x = 0.03f;
    text->font_size.y = 0.03f;
    gm_801692E8(arg3, &sp18);
    mn_8022EA78(sp30, 2, sp18.hour);
    mn_8022EA78(sp2C, 2, sp18.minute);
    mn_8022EA78(sp28, 2, sp18.second);
    mn_8022EA78(sp34, 4, sp18.year);
    mn_8022EA78(sp24, 2, sp18.month);
    mn_8022EA78(sp20, 2, sp18.day);
    if (lbLang_IsSavedLanguageUS() != 0) {
        HSD_SisLib_803A6B98(text, 0.0f, 0.0f, layout->date_format, sp24, sp20,
                            sp34);
    } else {
        HSD_SisLib_803A6B98(text, 0.0f, 0.0f, layout->date_format, sp34, sp24,
                            sp20);
    }
    return HSD_SisLib_803A6B98(text, 0.0f, 40.0f, layout->time_format, sp30,
                               sp2C, sp28);
}
#pragma pop

#pragma push
#pragma dont_inline on
void mnInfo_80251F04(MenuInfo_GObj* arg0, s32 arg1, u32 arg2)
{
    s16 sp16;
    s16 unused;
    HSD_Text** slot;
    HSD_Text* text;
    MnInfoData* data;

    data = arg0->user_data;
    slot = (HSD_Text**) ((u8*) data + (arg1 * 4));
    if (*(slot += 6) != NULL) {
        HSD_SisLib_803A5CC4(data->right_column[arg1]);
    }
    text = HSD_SisLib_803A5ACC(0, 0, -5.0f, (3.45f * (f32) arg1) + -5.9f,
                               17.0f, 514.2857f, 142.85715f);
    *slot = text;
    text->font_size.x = 0.035f;
    text->font_size.y = 0.035f;
    text->default_fitting = 1;
    un_802FE3F8((s32) arg2, 0x4BD, &sp16, NULL);
    HSD_SisLib_803A6368(text, (s32) (u16) sp16);
}
#pragma pop

static inline s32 mnInfo_CountUnlocked(void)
{
    s32 i;
    s32 count = 0;

    for (i = 0; i < 0x42; i++) {
        if (mnInfo_80251A08(i) != 0) {
            count += 1;
        }
    }
    return count;
}

void fn_80251FE4(void)
{
    MenuInfo_GObj* gobj;
    MnInfoData* data;
    u64 buttons;
    s32 i;
    s32 count;
    u8* trophy;
    MnInfoTextCursor* cursor_base;
    MnInfoTextCursor* left;
    MnInfoTextCursor* right;
    PAD_STACK(0x20);

    data = mnInfo_804D6C78->user_data;
    if (mn_804D6BC8.cooldown != 0) {
        mn_804D6BC8.cooldown -= 1;
        mn_804D6BC8.x2 = 0;
        mn_804D6BC8.x4 = 0;
        return;
    }
    buttons = mn_804A04F0.buttons = mn_80229624(4);
    if (buttons & MenuInput_Back) {
        lbAudioAx_80024030(0);
        mn_804A04F0.entering_menu = 0;
        mn_80229894(5, 4, 3);
        return;
    }
    if (buttons & MenuInput_Up) {
        if (data->scroll_idx != 0) {
            data->scroll_idx -= 1;
            lbAudioAx_80024030(2);
            i = 0;
            cursor_base = mnInfo_804D6C78->user_data;
            left = cursor_base;
            right = (MnInfoTextCursor*) &((HSD_Text**) cursor_base)[i];
            do {
                if (left->left != NULL) {
                    HSD_SisLib_803A5CC4(right->left);
                    left->left = NULL;
                }
                if (left->right != NULL) {
                    HSD_SisLib_803A5CC4(right->right);
                    left->right = NULL;
                }
                i++;
                left = (MnInfoTextCursor*) ((u8*) left + 4);
                right = (MnInfoTextCursor*) ((u8*) right + 4);
            } while (i < 4);
            gobj = mnInfo_804D6C78;
            trophy = &mnInfo_804A0968[data->scroll_idx];
            for (i = 0; i < 4; i++) {
                if (mnInfo_80251A08(*trophy) != 0) {
                    u8 id = *trophy;

                    mnInfo_80251D58(gobj, i, id, *gmMainLib_8015D804(id));
                    mnInfo_80251F04(gobj, i, id);
                }
                trophy++;
            }
        }
    } else if (buttons & MenuInput_Down) {
        count = 0;
        for (i = 0; i < 0x42; i++) {
            if (mnInfo_80251A08(i) != 0) {
                count++;
            }
        }
        if ((data->scroll_idx + 4) < count) {
            lbAudioAx_80024030(2);
            data->scroll_idx += 1;
            i = 0;
            cursor_base = mnInfo_804D6C78->user_data;
            left = cursor_base;
            right = (MnInfoTextCursor*) &((HSD_Text**) cursor_base)[i];
            do {
                if (left->left != NULL) {
                    HSD_SisLib_803A5CC4(right->left);
                    left->left = NULL;
                }
                if (left->right != NULL) {
                    HSD_SisLib_803A5CC4(right->right);
                    left->right = NULL;
                }
                i++;
                left = (MnInfoTextCursor*) ((u8*) left + 4);
                right = (MnInfoTextCursor*) ((u8*) right + 4);
            } while (i < 4);
            gobj = mnInfo_804D6C78;
            trophy = &mnInfo_804A0968[data->scroll_idx];
            for (i = 0; i < 4; i++) {
                if (mnInfo_80251A08(*trophy) != 0) {
                    u8 id = *trophy;

                    mnInfo_80251D58(gobj, i, id, *gmMainLib_8015D804(id));
                    mnInfo_80251F04(gobj, i, id);
                }
                trophy++;
            }
        }
    }
}

#pragma push
#pragma auto_inline off
void mnInfo_802522B8(HSD_GObj* gobj)
{
    s32 count;
    MnInfoData* data;
    HSD_JObj* jobj;
    HSD_JObj* child;
    PAD_STACK(4);

    jobj = gobj->hsd_obj;
    data = gobj->user_data;
    lb_80011E24(jobj, &child, 2, -1);
    if (data->scroll_idx != 0) {
        HSD_JObjClearFlagsAll(child, JOBJ_HIDDEN);
    } else {
        HSD_JObjSetFlagsAll(child, JOBJ_HIDDEN);
    }
    lb_80011E24(jobj, &child, 1, -1);
    count = mnInfo_CountUnlocked();

    if ((data->scroll_idx + 4) < count) {
        HSD_JObjClearFlagsAll(child, JOBJ_HIDDEN);
    } else {
        HSD_JObjSetFlagsAll(child, JOBJ_HIDDEN);
    }
    mn_8022ED6C(jobj, (AnimLoopSettings*) mnInfo_803EFC08);
}
#pragma pop

void fn_802523B8(HSD_GObj* gobj)
{
    HSD_GObjPLink_80390228(gobj);
}

void fn_802523D8(HSD_GObj* gobj)
{
    HSD_JObj* sp1C;
    HSD_GObjProc* proc;
    s32 i;
    HSD_JObj* jobj;
    MnInfoData* data;
    MnInfoTextCursor* cursor_base;
    MnInfoTextCursor* read_cursor;
    MnInfoTextCursor* write_cursor;
    HSD_Text* zero_left;
    HSD_Text* zero_right;
    PAD_STACK(16);

    data = gobj->user_data;
    if (mn_804A04F0.cur_menu != MENU_KIND_DATA_SPECIAL) {
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        proc = HSD_GObj_SetupProc(gobj, fn_802523B8, 0);
        i = 0;
        proc->flags_3 = HSD_GObj_804D783C;
        cursor_base = gobj->user_data;
        write_cursor = cursor_base;
        zero_left = (HSD_Text*) i;
        zero_right = (HSD_Text*) i;
        read_cursor = (MnInfoTextCursor*) &((HSD_Text**) cursor_base)[i];
        do {
            if (write_cursor->left != NULL) {
                HSD_SisLib_803A5CC4(read_cursor->left);
                write_cursor->left = zero_left;
            }
            if (write_cursor->right != NULL) {
                HSD_SisLib_803A5CC4(read_cursor->right);
                write_cursor->right = zero_right;
            }
            i += 1;
            write_cursor = (MnInfoTextCursor*) &((HSD_Text**) write_cursor)[1];
            read_cursor = (MnInfoTextCursor*) &((HSD_Text**) read_cursor)[1];
        } while (i < 4);
        HSD_SisLib_803A5CC4(data->description);
        return;
    }
    jobj = gobj->hsd_obj;
    lb_80011E24(jobj, &sp1C, 2, -1);
    if (data->scroll_idx != 0) {
        HSD_JObjClearFlagsAll(sp1C, JOBJ_HIDDEN);
    } else {
        HSD_JObjSetFlagsAll(sp1C, JOBJ_HIDDEN);
    }
    lb_80011E24(jobj, &sp1C, 1, -1);
    if ((data->scroll_idx + 4) < mnInfo_80251AA4()) {
        HSD_JObjClearFlagsAll(sp1C, JOBJ_HIDDEN);
    } else {
        HSD_JObjSetFlagsAll(sp1C, JOBJ_HIDDEN);
    }
    mn_8022ED6C(jobj, (AnimLoopSettings*) mnInfo_803EFC08);
}

void fn_80252548(HSD_GObj* gobj)
{
    HSD_GObjProc* proc;
    HSD_JObj* jobj;
    s32 i;
    u8* trophy;
    MnInfoTextCursor* cursor_base;
    MnInfoTextCursor* read_cursor;
    MnInfoTextCursor* write_cursor;
    HSD_Text* zero_left;
    HSD_Text* zero_right;
    MnInfoData* data;
    PAD_STACK(24);

    data = gobj->user_data;
    if (mn_804A04F0.cur_menu != MENU_KIND_DATA_SPECIAL) {
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        proc = HSD_GObj_SetupProc(gobj, fn_802523B8, 0);
        i = 0;
        proc->flags_3 = HSD_GObj_804D783C;
        cursor_base = gobj->user_data;
        write_cursor = cursor_base;
        zero_left = (HSD_Text*) i;
        zero_right = (HSD_Text*) i;
        read_cursor = (MnInfoTextCursor*) &((HSD_Text**) cursor_base)[i];
        do {
            if (write_cursor->left != NULL) {
                HSD_SisLib_803A5CC4(read_cursor->left);
                write_cursor->left = zero_left;
            }
            if (write_cursor->right != NULL) {
                HSD_SisLib_803A5CC4(read_cursor->right);
                write_cursor->right = zero_right;
            }
            i += 1;
            write_cursor = (MnInfoTextCursor*) &((HSD_Text**) write_cursor)[1];
            read_cursor = (MnInfoTextCursor*) &((HSD_Text**) read_cursor)[1];
        } while (i < 4);
        HSD_SisLib_803A5CC4(data->description);
        return;
    }
    if ((s32) data->anim_timer != 0) {
        data->anim_timer--;
        return;
    }
    trophy = mnInfo_804A0968;
    for (i = 0; i < 4; i++) {
        if (mnInfo_80251A08(*trophy) != 0) {
            u8 id = *trophy;

            mnInfo_80251D58((MenuInfo_GObj*) gobj, i, id,
                            *gmMainLib_8015D804(id));
            mnInfo_80251F04((MenuInfo_GObj*) gobj, i, id);
        }
        trophy++;
    }
    jobj = HSD_JObjLoadJoint(mnInfo_804A0958.joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 4, 0x80);
    HSD_JObjAddAnimAll(jobj, mnInfo_804A0958.animjoint,
                       mnInfo_804A0958.matanim_joint,
                       mnInfo_804A0958.shapeanim_joint);
    HSD_JObjReqAnimAll(jobj, 0.0f);
    mnInfo_802522B8(gobj);
    HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
    proc = HSD_GObj_SetupProc(gobj, fn_802523D8, 0);
    proc->flags_3 = HSD_GObj_804D783C;
}

StaticModelDesc mnInfo_804A0958;

#pragma push
#pragma dont_inline on
void mnInfo_80252720(MnInfoData* data)
{
    data->scroll_idx = 0;
    data->anim_timer = 10;
    data->description = NULL;
    data->left_column[0] = NULL;
    data->right_column[0] = NULL;
    data->left_column[1] = NULL;
    data->right_column[1] = NULL;
    data->left_column[2] = NULL;
    data->right_column[2] = NULL;
    data->left_column[3] = NULL;
    data->right_column[3] = NULL;
}
#pragma pop

s32 mnInfo_80252758(void)
{
    void* sp8;
    MnInfoData* data;
    MnInfoDataLayout* layout;
    MnInfoData* user_data;
    MnInfoData* temp_ret;
    HSD_GObj* menu_gobj;
    HSD_GObjProc* proc;
    HSD_GObjProc* menu_proc;
    HSD_Text* description;
    s32 spC;
    PAD_STACK(8);

    layout = (MnInfoDataLayout*) mnInfo_803EFC08;
    mn_804D6BC8.cooldown = 5;
    mn_804A04F0.prev_menu = mn_804A04F0.cur_menu;
    mn_804A04F0.cur_menu = 0x1D;
    mn_804A04F0.hovered_selection = 0;
    sp8 = layout->top_shapeanim_joint;
    spC = 0;

    lbArchive_LoadSections(
        mn_804D6BB8, (void**) &mnInfo_804A0958.joint, layout->top_joint,
        &mnInfo_804A0958.animjoint, layout->top_animjoint,
        &mnInfo_804A0958.matanim_joint, layout->top_matanim_joint,
        &mnInfo_804A0958.shapeanim_joint, sp8, spC);

    mnInfo_80251AFC();

    menu_gobj = GObj_Create(6, 7, 0x80);
    mnInfo_804D6C78 = menu_gobj;

    temp_ret = HSD_MemAlloc(sizeof(MnInfoData));
    user_data = temp_ret;
    HSD_ASSERTREPORT(0x267, user_data, "Can't get user_data.\n");
    mnInfo_80252720(user_data);
    GObj_InitUserData(menu_gobj, 0, HSD_Free, user_data);

    menu_proc = HSD_GObj_SetupProc(menu_gobj, (HSD_GObjEvent) fn_80252548, 0);
    menu_proc->flags_3 = HSD_GObj_804D783C;

    data = menu_gobj->user_data;
    if (data->description != NULL) {
        HSD_SisLib_803A5CC4(data->description);
    }
    description =
        HSD_SisLib_803A5ACC(0, 1, -9.5f, 9.1f, 17.0f, 364.68332f, 38.38772f);
    data->description = description;
    description->font_size.x = 0.0521f;
    description->font_size.y = 0.0521f;
    HSD_SisLib_803A6368(description, 0xA3);

    proc = HSD_GObj_SetupProc(GObj_Create(0, 1, 0x80),
                              (HSD_GObjEvent) fn_80251FE4, 0);
    proc->flags_3 = (u16) HSD_GObj_804D783C;
    return (s32) proc;
}
