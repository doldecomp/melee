#include "mninfo.h"

#include "placeholder.h"

#include "baselib/gobjuserdata.h"
#include "gm/gm_1601.h"
#include "gm/gmmain_lib.h"
#include "gm/types.h"
#include "if/ifprize.h"
#include "lb/lbarchive.h"
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

#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif
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
#ifdef MUST_MATCH
#pragma pop
#endif

#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif
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
#ifdef MUST_MATCH
#pragma pop
#endif

static inline bool mnInfo_80251AFC_inline(s32 i)
{
    s32 unlock_state = mnInfo_80251A08(mnInfo_804A0968[i]);
    return unlock_state == 0;
}

static inline u32 mnInfo_80251AFC_inline_2(s32 j)
{
    return *gmMainLib_8015D804(mnInfo_804A0968[j]);
}

static inline s32 mnInfo_80251AFC_inline_3(u8* ids, s32 i)
{
    return ids[i];
}

void mnInfo_80251AFC(void)
{
    s32 i;
    s32 j;
    PAD_STACK(8);

    /// @todo Keep #mnInfo_804A0958 before #mnInfo_804A0968 in `.bss`.
    (void) &mnInfo_804A0958;

    for (i = 0; 0x42 > i; i++) {
        mnInfo_804A0968[i] = i;
    }
    for (i = 0; i < 0x42; i++) {
        for (j = i + 1; j < 0x42; j++) {
            if (mnInfo_80251AFC_inline(i)) {
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
                 *gmMainLib_8015D804(mnInfo_80251AFC_inline_3(
                     mnInfo_804A0968, i)) > mnInfo_80251AFC_inline_2(j)))
            {
                u8 tmp = mnInfo_804A0968[i];

                mnInfo_804A0968[i] = mnInfo_804A0968[j];
                mnInfo_804A0968[j] = tmp;
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

#define mnInfo_layout (*(MnInfoDataLayout*) mnInfo_803EFC08)

#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif
s32 mnInfo_80251D58(mnInfo_GObj* arg0, s32 arg1, u32 arg2, u32 arg3)
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
    layout = &mnInfo_layout;
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
#ifdef MUST_MATCH
#pragma pop
#endif

#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif
void mnInfo_80251F04(mnInfo_GObj* arg0, s32 arg1, u32 arg2)
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
#ifdef MUST_MATCH
#pragma pop
#endif

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

inline void mnInfo_CreateEntries(u32 id)
{
    u8* trophy;
    s32 i;
    mnInfo_GObj* gobj;

    gobj = mnInfo_804D6C78;
    trophy = &mnInfo_804A0968[id];
    (void) trophy;
    for (i = 0; i < 4; i++) {
        if (mnInfo_80251A08(*trophy) != 0) {
            id = *trophy;

            mnInfo_80251D58(gobj, i, id, *gmMainLib_8015D804(id));
            mnInfo_80251F04(gobj, i, id);
        }
        trophy++;
    }
}

static inline void mnInfo_FreeEntries(void)
{
    s32 j;
    MnInfoData* data2;
    MnInfoData* data3;

    j = 0;
    data2 = mnInfo_804D6C78->user_data;
    data3 = data2;
    do {
        if (data2->left_column[j] != NULL) {
            HSD_SisLib_803A5CC4(data3->left_column[j]);
            data2->left_column[j] = NULL;
        }
        if (data2->right_column[j] != NULL) {
            HSD_SisLib_803A5CC4(data3->right_column[j]);
            data2->right_column[j] = NULL;
        }
        j++;
    } while (j < 4);
}

void fn_80251FE4(void)
{
    MnInfoData* data;
    u64 buttons;
    s32 count;
    PAD_STACK(0x18);

    data = mnInfo_804D6C78->user_data;
    if (mn_804D6BC8.cooldown != 0) {
        mn_804D6BC8.cooldown -= 1;
        mn_804D6BC8.x2 = 0;
        mn_804D6BC8.x4 = 0;
        return;
    }
    buttons = mn_804A04F0.buttons = mn_80229624(4);
    if (buttons & MenuInput_Back) {
        sfxBack();
        mn_804A04F0.entering_menu = 0;
        mn_80229894(5, 4, 3);
        return;
    }
    if (buttons & MenuInput_Up) {
        if (data->scroll_idx != 0) {
            data->scroll_idx -= 1;
            sfxMove();
            mnInfo_FreeEntries();
            {
                u8* trophy;
                s32 i;
                mnInfo_GObj* gobj;

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
    } else if (buttons & MenuInput_Down) {
        count = mnInfo_CountUnlocked();
        if ((data->scroll_idx + 4) < count) {
            sfxMove();
            data->scroll_idx += 1;
            mnInfo_FreeEntries();
            mnInfo_CreateEntries(data->scroll_idx);
        }
    }
}

#ifdef MUST_MATCH
#pragma push
#pragma auto_inline off
#endif
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
    mn_8022ED6C(jobj, &mnInfo_layout.anim);
}
#ifdef MUST_MATCH
#pragma pop
#endif

void fn_802523B8(HSD_GObj* gobj)
{
    HSD_GObjPLink_80390228(gobj);
}

static inline void fn_802523D8_inline(MnInfoData* data, HSD_GObj* gobj)
{
    HSD_GObjProc* proc;
    HSD_JObj* jobj;
    PAD_STACK(16);
    if (mn_804A04F0.cur_menu != MENU_KIND_DATA_SPECIAL) {
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        proc = HSD_GObj_SetupProc(gobj, fn_802523B8, 0);
        proc->flags_3 = HSD_GObj_804D783C;
        {
            MnInfoData* data2 = GET_MNINFO(gobj);
            MnInfoData* data3 = data2;
            int i;
            HSD_Text* left_null = NULL;
            HSD_Text* right_null = NULL;

            for (i = 0; i < 4; i++) {
                if (data2->left_column[i] != NULL) {
                    HSD_SisLib_803A5CC4(data3->left_column[i]);
                    data2->left_column[i] = left_null;
                }
                if (data2->right_column[i] != NULL) {
                    HSD_SisLib_803A5CC4(data3->right_column[i]);
                    data2->right_column[i] = right_null;
                }
            }

            HSD_SisLib_803A5CC4(data->description);
        }
    } else {
        HSD_JObj* child;
        jobj = gobj->hsd_obj;

        lb_80011E24(jobj, &child, 2, -1);
        if (data->scroll_idx != 0) {
            HSD_JObjClearFlagsAll(child, JOBJ_HIDDEN);
        } else {
            HSD_JObjSetFlagsAll(child, JOBJ_HIDDEN);
        }

        lb_80011E24(jobj, &child, 1, -1);
        if ((data->scroll_idx + 4) < mnInfo_80251AA4()) {
            HSD_JObjClearFlagsAll(child, JOBJ_HIDDEN);
        } else {
            HSD_JObjSetFlagsAll(child, JOBJ_HIDDEN);
        }

        mn_8022ED6C(jobj, &mnInfo_layout.anim);
    }
}

void fn_802523D8(HSD_GObj* gobj)
{
    MnInfoData* data = GET_MNINFO(gobj);
    PAD_STACK(4);
    fn_802523D8_inline(data, gobj);
}

static inline void fn_80252548_inline(MnInfoData* data, HSD_GObj* gobj)
{
    HSD_GObjProc* proc;
    HSD_JObj* jobj;
    s32 i;
    PAD_STACK(16);
    if (mn_804A04F0.cur_menu != MENU_KIND_DATA_SPECIAL) {
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        proc = HSD_GObj_SetupProc(gobj, fn_802523B8, 0);
        proc->flags_3 = HSD_GObj_804D783C;
        {
            MnInfoData* data2 = GET_MNINFO(gobj);
            MnInfoData* data3 = data2;
            int j;
            HSD_Text* left_null = NULL;
            HSD_Text* right_null = NULL;

            for (j = 0; j < 4; j++) {
                if (data2->left_column[j] != NULL) {
                    HSD_SisLib_803A5CC4(data3->left_column[j]);
                    data2->left_column[j] = left_null;
                }
                if (data2->right_column[j] != NULL) {
                    HSD_SisLib_803A5CC4(data3->right_column[j]);
                    data2->right_column[j] = right_null;
                }
            }

            HSD_SisLib_803A5CC4(data->description);
        }
    } else {
        if ((s32) data->anim_timer != 0) {
            data->anim_timer--;
            return;
        }
        for (i = 0; i < 4; i++) {
            if (mnInfo_80251A08(mnInfo_804A0968[i]) != 0) {
                u32 id = mnInfo_804A0968[i];

                mnInfo_80251D58((mnInfo_GObj*) gobj, i, id,
                                *gmMainLib_8015D804(id));
                mnInfo_80251F04((mnInfo_GObj*) gobj, i, id);
            }
        }
        jobj = HSD_JObjLoadJoint(mnInfo_804A0958.joint);
        HSD_GObjObject_80390A70(gobj, HSD_GObj_JObjKind, jobj);
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
}

void fn_80252548(HSD_GObj* gobj)
{
    MnInfoData* data = GET_MNINFO(gobj);
    PAD_STACK(8);
    fn_80252548_inline(data, gobj);
}

StaticModelDesc mnInfo_804A0958;

#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif
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
#ifdef MUST_MATCH
#pragma pop
#endif

s32 mnInfo_80252758(void)
{
    MnInfoData* user_data;
    HSD_GObjProc* proc;
    HSD_GObj* gobj;
    HSD_Archive* archive;
    StaticModelDesc* model = &mnInfo_804A0958;
    char* top_joint = mnInfo_layout.top_joint;
    HSD_AnimJoint** animjoint = &model->animjoint;
    PAD_STACK(8);

    (void) "Can't get user_data.\n";
    (void) __FILE__;
    (void) "user_data";

    mn_804D6BC8.cooldown = 5;
    mn_804A04F0.prev_menu = mn_804A04F0.cur_menu;
    mn_804A04F0.cur_menu = 0x1D;
    mn_804A04F0.hovered_selection = 0;

    archive = mn_804D6BB8;
    lbArchive_LoadSections(
        archive, (void**) &model->joint, top_joint, animjoint,
        mnInfo_layout.top_animjoint, &model->matanim_joint,
        mnInfo_layout.top_matanim_joint, &model->shapeanim_joint,
        mnInfo_layout.top_shapeanim_joint, 0);

    mnInfo_80251AFC();

    gobj = GObj_Create(6, 7, 0x80);
    mnInfo_804D6C78 = gobj;

    user_data = HSD_MemAlloc(sizeof(*user_data));
    if (user_data == NULL) {
        OSReport(mnInfo_layout.assert_report);
        __assert(mnInfo_layout.assert_file, 0x267, mnInfo_layout.assert_expr);
    }
    mnInfo_80252720(user_data);
    GObj_InitUserData(gobj, 0, HSD_Free, user_data);

    proc = HSD_GObj_SetupProc(gobj, (HSD_GObjEvent) fn_80252548, 0);
    proc->flags_3 = HSD_GObj_804D783C;

    {
        MnInfoData* data;
        HSD_Text* text;

        if ((data = gobj->user_data)->description != NULL) {
            HSD_SisLib_803A5CC4(data->description);
        }
        text = HSD_SisLib_803A5ACC(0, 1, -9.5f, 9.1f, 17.0f, 364.68332f,
                                   38.38772f);
        data->description = text;
        text->font_size.x = 0.0521f;
        text->font_size.y = 0.0521f;
        HSD_SisLib_803A6368(text, 0xA3);
    }

    proc = HSD_GObj_SetupProc(GObj_Create(0, 1, 0x80),
                              (HSD_GObjEvent) fn_80251FE4, 0);
    proc->flags_3 = (u16) HSD_GObj_804D783C;
    return (s32) proc;
}
