#include "mninfo.h"

#include "placeholder.h"

#include "gm/gmmain_lib.h"
#include "gm/gm_1601.h"
#include "gm/types.h"
#include "if/ifprize.h"
#include "lb/lb_00F9.h"
#include "lb/lbarchive.h"
#include "lb/lbaudio_ax.h"
#include "lb/lblanguage.h"
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

StaticModelDesc mnInfo_804A0958;
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

    for (i = 0; i < 0x42; i++) {
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

#pragma push
#pragma dont_inline on
s32 mnInfo_80251D58(MenuInfo_GObj* arg0, s32 arg1, u32 arg3)
{
    char sp34[5];
    char sp30[3];
    char sp2C[3];
    char sp28[3];
    char sp24[3];
    char sp20[3];
    datetime sp18;
    HSD_Text* text;
    HSD_Text** slot;
    MnInfoData* data;

    data = arg0->user_data;
    slot = &data->left_column[arg1];
    if (*slot != NULL) {
        HSD_SisLib_803A5CC4(*slot);
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
        HSD_SisLib_803A6B98(text, 0.0f, 0.0f, "%s.%s.%s", sp24, sp20, sp34);
    } else {
        HSD_SisLib_803A6B98(text, 0.0f, 0.0f, "%s.%s.%s", sp34, sp24, sp20);
    }
    return HSD_SisLib_803A6B98(text, 0.0f, 40.0f, "%s:%s:%s", sp30, sp2C,
                               sp28);
}
#pragma pop

#pragma push
#pragma dont_inline on
void mnInfo_80251F04(MenuInfo_GObj* arg0, u32 arg1, u32 arg2)
{
    s16 sp16;
    HSD_Text* temp_r3_2;
    HSD_Text** temp_r31;
    MnInfoData* temp_r3;

    temp_r3 = arg0->user_data;
    temp_r31 = &temp_r3->right_column[arg1];
    if (temp_r3->right_column[arg1] != NULL) {
        HSD_SisLib_803A5CC4(temp_r3->right_column[arg1]);
    }
    temp_r3_2 = HSD_SisLib_803A5ACC(0, 0, -5.0f, (3.45f * (f32) arg1) + -5.9f,
                                    17.0f, 514.2857f, 142.85715f);
    *temp_r31 = temp_r3_2;
    temp_r3_2->font_size.x = 0.035f;
    temp_r3_2->font_size.y = 0.035f;
    temp_r3_2->default_fitting = 1;
    un_802FE3F8((s32) arg2, 0x4BD, &sp16, NULL);
    HSD_SisLib_803A6368(temp_r3_2, (s32) (u16) sp16);
}
#pragma pop

void fn_80251FE4(void)
{
    MenuInfo_GObj* gobj;
    MnInfoData* data;
    u32 buttons;
    s32 count;
    s32 i;
    u8* trophy;
    MnInfoTextCursor* left;
    MnInfoTextCursor* right;

    data = mnInfo_804D6C78->user_data;
    if (mn_804D6BC8.cooldown != 0) {
        mn_804D6BC8.cooldown -= 1;
        mn_804D6BC8.x2 = 0;
        mn_804D6BC8.x4 = 0;
        return;
    }
    buttons = mn_804A04F0.buttons = mn_80229624(4);
    mn_804A04F0.x10 = 0;
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
            left = (MnInfoTextCursor*) data;
            right = (MnInfoTextCursor*) data;
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

                    gmMainLib_8015D804(id);
                    mnInfo_80251D58(gobj, i, id);
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
            left = (MnInfoTextCursor*) data;
            right = (MnInfoTextCursor*) data;
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

                    gmMainLib_8015D804(id);
                    mnInfo_80251D58(gobj, i, id);
                    mnInfo_80251F04(gobj, i, id);
                }
                trophy++;
            }
        }
    }
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
void mnInfo_802522B8(HSD_GObj* gobj)
{
    s32 count;
    s32 i;
    MnInfoData* data;
    HSD_JObj* jobj;
    HSD_JObj* child;
    PAD_STACK(12);

    jobj = gobj->hsd_obj;
    data = gobj->user_data;
    lb_80011E24(jobj, &child, 2, -1);
    if (data->scroll_idx != 0) {
        HSD_JObjClearFlagsAll(child, JOBJ_HIDDEN);
    } else {
        HSD_JObjSetFlagsAll(child, JOBJ_HIDDEN);
    }
    lb_80011E24(jobj, &child, 1, -1);
    count = 0;
    for (i = 0; i < 0x42; i++) {
        if (mnInfo_80251A08(i) != 0) {
            count++;
        }
    }

    if ((data->scroll_idx + 4) < count) {
        HSD_JObjClearFlagsAll(child, JOBJ_HIDDEN);
    } else {
        HSD_JObjSetFlagsAll(child, JOBJ_HIDDEN);
    }
    mn_8022ED6C(jobj, mnInfo_803EFC08);
}
#pragma pop

void fn_802523B8(HSD_GObj* gobj)
{
    HSD_GObjPLink_80390228(gobj);
}

void fn_802523D8(HSD_GObj* gobj)
{
    HSD_JObj* sp1C;
    HSD_GObjProc* temp_r3;
    s32 var_r28;
    HSD_JObj* temp_r28;
    MnInfoData* temp_r31;
    MnInfoTextCursor* temp_r3_2;
    MnInfoTextCursor* var_r26;
    MnInfoTextCursor* var_r27;
    PAD_STACK(16);

    temp_r31 = gobj->user_data;
    if (mn_804A04F0.cur_menu != MENU_KIND_DATA_SPECIAL) {
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        temp_r3 = HSD_GObj_SetupProc(gobj, fn_802523B8, 0);
        var_r28 = 0;
        temp_r3->flags_3 = HSD_GObj_804D783C;
        temp_r3_2 = gobj->user_data;
        var_r27 = temp_r3_2;
        var_r26 = temp_r3_2;
        do {
            if (var_r27->left != NULL) {
                HSD_SisLib_803A5CC4(var_r26->left);
                var_r27->left = NULL;
            }
            if (var_r27->right != NULL) {
                HSD_SisLib_803A5CC4(var_r26->right);
                var_r27->right = NULL;
            }
            var_r28 += 1;
            var_r27 = (MnInfoTextCursor*) ((u8*) var_r27 + 4);
            var_r26 = (MnInfoTextCursor*) ((u8*) var_r26 + 4);
        } while (var_r28 < 4);
        HSD_SisLib_803A5CC4(temp_r31->description);
        return;
    }
    temp_r28 = gobj->hsd_obj;
    lb_80011E24(temp_r28, &sp1C, 2, -1);
    if (temp_r31->scroll_idx != 0) {
        HSD_JObjClearFlagsAll(sp1C, JOBJ_HIDDEN);
    } else {
        HSD_JObjSetFlagsAll(sp1C, JOBJ_HIDDEN);
    }
    lb_80011E24(temp_r28, &sp1C, 1, -1);
    if ((temp_r31->scroll_idx + 4) < mnInfo_80251AA4()) {
        HSD_JObjClearFlagsAll(sp1C, JOBJ_HIDDEN);
    } else {
        HSD_JObjSetFlagsAll(sp1C, JOBJ_HIDDEN);
    }
    mn_8022ED6C(temp_r28, mnInfo_803EFC08);
}

void fn_80252548(HSD_GObj* gobj)
{
    HSD_GObjProc* proc;
    HSD_JObj* jobj;
    s32 i;
    u8* trophy;
    MnInfoData* data;
    MnInfoTextCursor* left;
    MnInfoTextCursor* right;

    data = gobj->user_data;
    if (mn_804A04F0.cur_menu != MENU_KIND_DATA_SPECIAL) {
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        proc = HSD_GObj_SetupProc(gobj, fn_802523B8, 0);
        proc->flags_3 = HSD_GObj_804D783C;
        i = 0;
        left = (MnInfoTextCursor*) data;
        right = (MnInfoTextCursor*) data;
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
        HSD_SisLib_803A5CC4(data->description);
        return;
    }
    if (data->anim_timer != 0) {
        data->anim_timer--;
        return;
    }
    trophy = mnInfo_804A0968;
    for (i = 0; i < 4; i++) {
        if (mnInfo_80251A08(*trophy) != 0) {
            u8 id = *trophy;

            gmMainLib_8015D804(id);
            mnInfo_80251D58((MenuInfo_GObj*) gobj, i, id);
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
    s32 spC;
    void* sp8;
    HSD_GObj* temp_r3_2;
    HSD_GObjProc* temp_r3;
    HSD_GObjProc* temp_r3_4;
    HSD_Text* temp_r3_5;
    HSD_Text* temp_r3_6;
    MnInfoData* temp_r3_3;
    MnInfoData* temp_ret;
    MnInfoData* temp_r29;

    mn_804D6BC8.cooldown = 5;
    mn_804A04F0.prev_menu = mn_804A04F0.cur_menu;
    mn_804A04F0.cur_menu = 0x1D;
    mn_804A04F0.hovered_selection = 0;
    sp8 = NULL;
    spC = 0;

    lbArchive_LoadSections(
        mn_804D6BB8, (void**) &mnInfo_804A0958.joint, "MenMainConSs_Top_joint",
        &mnInfo_804A0958.animjoint, "MenMainConSs_Top_animjoint",
        &mnInfo_804A0958.matanim_joint, "MenMainConSs_Top_matanim_joint",
        &mnInfo_804A0958.shapeanim_joint, "MenMainConSs_Top_shapeanim_joint",
        0);

    mnInfo_80251AFC();

    temp_r3_2 = GObj_Create(6, 7, 0x80);
    mnInfo_804D6C78 = temp_r3_2;

    temp_ret = HSD_MemAlloc(sizeof(MnInfoData));
    temp_r3_3 = temp_ret;
    HSD_ASSERTREPORT(0x267, temp_r3_3, "Can't get user_data.\n");
    mnInfo_80252720(temp_r3_3);
    GObj_InitUserData(temp_r3_2, 0, HSD_Free, temp_r3_3);

    temp_r3_4 =
        HSD_GObj_SetupProc(temp_r3_2, (HSD_GObjEvent) fn_80252548, 0);
    temp_r3_4->flags_3 = HSD_GObj_804D783C;

    temp_r29 = temp_r3_2->user_data;
    temp_r3_5 = temp_r29->description;
    if (temp_r3_5 != NULL) {
        HSD_SisLib_803A5CC4(temp_r3_5);
    }
    temp_r3_6 =
        HSD_SisLib_803A5ACC(0, 1, -9.5f, 9.1f, 17.0f, 364.68332f, 38.38772f);
    temp_r29->description = temp_r3_6;
    temp_r3_6->font_size.x = 0.0521f;
    temp_r3_6->font_size.y = 0.0521f;
    HSD_SisLib_803A6368(temp_r3_6, 0xA3);

    temp_r3 = HSD_GObj_SetupProc(GObj_Create(0, 1, 0x80),
                                 (HSD_GObjEvent) fn_80251FE4, 0);
    temp_r3->flags_3 = HSD_GObj_804D783C;
    return (s32) temp_r3;
}
