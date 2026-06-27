#include "mnevent.h"

#include "db/db.h"
#include "gm/gm_1601.h"
#include "gm/gm_1BA8.h"
#include "gm/gmmain_lib.h"
#include "lb/lb_00F9.h"
#include "lb/lbarchive.h"
#include "lb/lbaudio_ax.h"
#include "mn/inlines.h"
#include "mn/mnmain.h"
#include "mn/types.h"

#include <baselib/debug.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjplink.h>
#include <baselib/gobjproc.h>
#include <baselib/gobjuserdata.h>
#include <baselib/jobj.h>
#include <baselib/memory.h>
#include <baselib/sislib.h>

static inline s32 mnEvent_CountUnlocked(void)
{
    s32 i;
    s32 count = 0;

    for (i = 0; i < 0x33; i++) {
        if (gmMainLib_8015CEFC(i) != 0) {
            count += 1;
        }
    }
    return count;
}

s32 mnEvent_8024CE74(void)
{
    s32 count;

    if (DbLevel > 2) {
        return 0x2A;
    }
    count = mnEvent_CountUnlocked();
    if (count <= 5) {
        return 1;
    }
    if (count <= 9) {
        return 6;
    }
    if (count <= 0xF) {
        return 0xB;
    }
    if (count <= 0x15) {
        return 0x10;
    }
    if (count <= 0x1A) {
        return 0x14;
    }
    if (count >= 0x32) {
        if (gm_80162EC8()) {
            return 0x2A;
        }
        return 0x29;
    }
    if (gm_80164840(0x14) && gm_80164840(7) && gm_80164840(0xF) &&
        gm_80164840(0x15))
    {
        if (gm_80164840(0xA) && gm_80164840(9) && gm_80164840(3) &&
            gm_80164840(0x18) && gm_80164840(0x19) && gm_80164840(0x16) &&
            gm_80164840(0x17))
        {
            return 0x29;
        }
        return 0x1E;
    }
    return 0x15;
}

static AnimLoopSettings mnEvent_803EF740 = { 0, 0, -0.1f };
static AnimLoopSettings mnEvent_803EF74C = { 0, 0, -0.1f };
static AnimLoopSettings mnEvent_803EF758 = { 0, 199.0f, 0 };
static Vec3 mnEvent_803EF764 = { -3.8f, -0.6f, 0 };
static Vec3 mnEvent_803EF770 = { 1.0f, -0.6f, 0 };
static char mnEvent_803EF77C[0xC] = {
    0x82, 0x6B, 0x82, 0x96, 0x81, 0x44, 0x20, 0x25, 0x64, 0, 0, 0,
};
static char mnEvent_803EF788[0xC] = "translate";
static char mnEvent_803EF794[9] = "%s:%s %s";
static char mnEvent_803EF7A0[0xD0] = {
    0x81, 0x7C, 0x81, 0x7C, 0x3A, 0x81, 0x7C, 0x81, 0x7C, 0x20, 0x81, 0x7C,
    0x81, 0x7C, 0,    0,    0x43, 0x61, 0x6E, 0x27, 0x74, 0x20, 0x67, 0x65,
    0x74, 0x20, 0x75, 0x73, 0x65, 0x72, 0x5F, 0x64, 0x61, 0x74, 0x61, 0x2E,
    0xA,  0,    0,    0,    0x6D, 0x6E, 0x65, 0x76, 0x65, 0x6E, 0x74, 0x2E,
    0x63, 0,    0,    0,    0x75, 0x73, 0x65, 0x72, 0x5F, 0x64, 0x61, 0x74,
    0x61, 0,    0,    0,    0x4D, 0x65, 0x6E, 0x4D, 0x61, 0x69, 0x6E, 0x43,
    0x6F, 0x6E, 0x45, 0x76, 0x5F, 0x54, 0x6F, 0x70, 0x5F, 0x6A, 0x6F, 0x69,
    0x6E, 0x74, 0,    0,    0x4D, 0x65, 0x6E, 0x4D, 0x61, 0x69, 0x6E, 0x43,
    0x6F, 0x6E, 0x45, 0x76, 0x5F, 0x54, 0x6F, 0x70, 0x5F, 0x61, 0x6E, 0x69,
    0x6D, 0x6A, 0x6F, 0x69, 0x6E, 0x74, 0,    0,    0x4D, 0x65, 0x6E, 0x4D,
    0x61, 0x69, 0x6E, 0x43, 0x6F, 0x6E, 0x45, 0x76, 0x5F, 0x54, 0x6F, 0x70,
    0x5F, 0x6D, 0x61, 0x74, 0x61, 0x6E, 0x69, 0x6D, 0x5F, 0x6A, 0x6F, 0x69,
    0x6E, 0x74, 0,    0,    0x4D, 0x65, 0x6E, 0x4D, 0x61, 0x69, 0x6E, 0x43,
    0x6F, 0x6E, 0x45, 0x76, 0x5F, 0x54, 0x6F, 0x70, 0x5F, 0x73, 0x68, 0x61,
    0x70, 0x65, 0x61, 0x6E, 0x69, 0x6D, 0x5F, 0x6A, 0x6F, 0x69, 0x6E, 0x74,
    0,    0,    0,    0,    0x4D, 0x65, 0x6E, 0x4D, 0x61, 0x69, 0x6E, 0x4D,
    0x61, 0x72, 0x6B, 0x45, 0x76, 0x5F, 0x54, 0x6F, 0x70, 0x5F, 0x6A, 0x6F,
    0x69, 0x6E, 0x74, 0,
};
static s32 mnEvent_804D5028 = 0xCABC9FFF;
static s32 mnEvent_804D502C = 0xFF;
void* mnEvent_804A08F8[4];
void* mnEvent_804A0908;
static char mnEvent_804D5040[3] = "%d";
static char mnEvent_804D5044[4] = { 0x81, 0x7C, 0, 0 };

void mnEvent_8024D15C(s32 idx, s32 event_id)
{
    HSD_JObj* jobj_0A;
    HSD_JObj* jobj_0C;
    Vec3 pos;
    Vec3 icon_pos;
    HSD_JObj* jobj_0C_2;
    f32 icon_spacing;
    MnEventData* data;
    HSD_Text** text_slot;
    HSD_Text** icon_slot;
    HSD_JObj* icon_jobj;
    HSD_Text* text;
    HSD_Text* icon_text;
    f32 spacing;
    HSD_JObj* jobj_0A_2;
    s32 is_unlocked;
    HSD_JObj* tree;
    PAD_STACK(0x40);

    tree = mnEvent_804D6C60->hsd_obj;
    data = mnEvent_804D6C60->user_data;
    lb_80011E24(tree, &jobj_0A, 0xA, -1);
    lb_80011E24(tree, &jobj_0C, 0xC, -1);

    spacing = HSD_JObjGetTranslationY(jobj_0A);
    spacing = HSD_JObjGetTranslationY(jobj_0C) - spacing;
    HSD_JObjGetTranslation(jobj_0A, &pos);

    pos.y = -(((f32) idx * spacing) + pos.y);

    if (data->gobjs[idx] != NULL) {
        HSD_GObjPLink_80390228(data->gobjs[idx]);
        data->gobjs[idx] = NULL;
    }

    is_unlocked = gmMainLib_8015CEFC(event_id);
    if (is_unlocked != 0) {
        HSD_GObj* icon_gobj;
        tree = mnEvent_804D6C60->hsd_obj;
        lb_80011E24(tree, &jobj_0A_2, 0xA, -1);
        lb_80011E24(tree, &jobj_0C_2, 0xC, -1);
        icon_spacing = HSD_JObjGetTranslationY(jobj_0A_2);
        icon_spacing = HSD_JObjGetTranslationY(jobj_0C_2) - icon_spacing;
        HSD_JObjGetTranslation(jobj_0A_2, &icon_pos);

        icon_pos.y = icon_pos.y + (f32) idx * icon_spacing;
        icon_gobj = GObj_Create(6, 7, 0x80);
        icon_jobj = HSD_JObjLoadJoint((HSD_Joint*) mnEvent_804A0908);
        HSD_GObjObject_80390A70(icon_gobj, HSD_GObj_804D7849, icon_jobj);
        GObj_SetupGXLink(icon_gobj, HSD_GObj_JObjCallback, 4, 0x80);
        mnEvent_8024D4E0(icon_jobj, &icon_pos);
        data->gobjs[idx] = icon_gobj;
    }

    text_slot = &data->texts[idx];
    if (*text_slot != NULL) {
        HSD_SisLib_803A5CC4(data->texts[idx]);
    }
    text = HSD_SisLib_803A6754(0, 1);
    *text_slot = text;
    text->font_size.x = 0.035f;
    text->font_size.y = 0.035f;
    text->pos_x = pos.x + mnEvent_803EF764.x;
    text->pos_y = pos.y + mnEvent_803EF764.y;
    text->pos_z = 17.0f;
    text->default_kerning = 1;
    *(s32*) &text->text_color = mnEvent_804D5028;
    HSD_SisLib_803A6B98(text, 0.0f, 0.0f, mnEvent_803EF77C, event_id + 1);

    icon_slot = &data->icons[idx];
    if (*icon_slot != NULL) {
        HSD_SisLib_803A5CC4(data->icons[idx]);
    }
    icon_text = HSD_SisLib_803A5ACC(0, 1, pos.x + mnEvent_803EF770.x,
                                    pos.y + mnEvent_803EF770.y, 17.0f,
                                    364.68332f, 38.38772f);
    *icon_slot = icon_text;
    icon_text->font_size.x = 0.035f;
    icon_text->font_size.y = 0.035f;
    HSD_SisLib_803A6368(icon_text,
                        ((gm_801BEBA8((u8) event_id) * 2) & 0x1FE) + 0x154);
}

void mnEvent_8024D4E0(HSD_JObj* jobj, Vec3* translate)
{
    HSD_JObjSetTranslate(jobj, translate);
}

void mnEvent_8024D5B0(HSD_GObj* gobj, u8 event)
{
    HSD_Text* temp_r3_2;
    HSD_Text* temp_r3;
    char sp18[4];
    char sp14[4];
    char sp10[4];
    u32 temp_r30;
    MnEventData* temp_r28;
    u8 temp_r27;

    temp_r28 = gobj->user_data;
    temp_r27 = event;
    temp_r3 = temp_r28->name_text;
    if (temp_r3 != NULL) {
        HSD_SisLib_803A5CC4(temp_r28->name_text);
    }

    temp_r3_2 = HSD_SisLib_803A6754(0, 1);
    temp_r28->name_text = temp_r3_2;
    temp_r3_2->pos_x = 3.8f;
    temp_r3_2->pos_y = 6.9f;
    temp_r3_2->pos_z = 17.0f;
    *(s32*) &temp_r3_2->text_color = mnEvent_804D502C;
    temp_r3_2->default_alignment = 2;
    temp_r3_2->font_size.x = 0.03f;
    temp_r3_2->font_size.y = 0.03f;
    temp_r30 = gmMainLib_8015CF5C((s32) gm_801BEBC0(temp_r27 & 0xFF));
    if ((gm_801BEB8C((u32) gm_801BEBC0((((u32) temp_r27) & 0xFFu) & 0xFFu)) &
         0xFFu) != 0)
    {
        if (gmMainLib_8015CEFC((s32) gm_801BEBC0(event & 0xFFFFFFFFu)) != 0) {
            mn_8022EA78(sp18, 2, (temp_r30 / 60 / 60) % 60);
            mn_8022EA78(sp14, 2, (temp_r30 / 60) % 60);
            mn_8022EA78(sp10, 2,
                        (u32) (s32) ((99.0f * (f32) (temp_r30 % 60)) / 59.0f));
            HSD_SisLib_803A6B98(temp_r3_2, 0.0f, 0.0f, mnEvent_803EF794, sp18,
                                sp14, sp10);
            return;
        }
        temp_r3_2->pos_x = 4.25f;
        temp_r3_2->pos_y = 6.9f;
        temp_r3_2->pos_z = 17.0f;
        temp_r3_2->default_kerning = 1;
        HSD_SisLib_803A6B98(temp_r3_2, 0.0f, 0.0f, mnEvent_803EF7A0, sp18,
                            sp14, sp10);
        return;
    }
    if (gmMainLib_8015CEFC((s32) gm_801BEBC0(event & 0xFFFFFFFFFFFFFFFFu)) !=
        0)
    {
        HSD_SisLib_803A6B98(temp_r3_2, 0.0f, 0.0f, mnEvent_804D5040, temp_r30);
        return;
    }
    temp_r3_2->default_kerning = 1;
    HSD_SisLib_803A6B98(temp_r3_2, 0.0f, 0.0f, mnEvent_804D5044);
}

inline MnEventData* GET_EVENTDATA(HSD_GObj* gobj)
{
    return gobj->user_data;
}

void fn_8024E1B4(HSD_GObj* gobj)
{
    HSD_JObj* tree = gobj->hsd_obj;
    MnEventData* tmp;
    MnEventData* data = GET_EVENTDATA(gobj);
    MnEventData* iter;
    int i;

    if (mn_8022EC18(tree, &mnEvent_803EF74C, 0x80) >=
        mnEvent_803EF74C.end_frame)
    {
        tmp = data;
        iter = data;
        for (i = 0; i < 9; i++) {
            if (iter->gobjs[0] != NULL) {
                HSD_GObjPLink_80390228(tmp->gobjs[i]);
                iter->gobjs[0] = NULL;
            }
            if (iter->texts[0] != NULL) {
                HSD_SisLib_803A5CC4(tmp->texts[i]);
                iter->texts[0] = NULL;
            }
            if (iter->icons[0] != NULL) {
                HSD_SisLib_803A5CC4(tmp->icons[i]);
                iter->icons[0] = NULL;
            }
            iter = (MnEventData*) ((u8*) iter + 4);
        }
        HSD_GObjPLink_80390228(gobj);
    }
}

void fn_8024E2A0(HSD_GObj* gobj)
{
    HSD_GObjProc* proc;
    HSD_JObj* jobj;
    HSD_JObj* tree;
    MnEventData* data = gobj->user_data;
    PAD_STACK(8);

    tree = gobj->hsd_obj;

    if (mn_804A04F0.cur_menu != 7) {
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        proc = HSD_GObj_SetupProc(gobj, fn_8024E1B4, 0);
        proc->flags_3 = HSD_GObj_804D783C;
        HSD_SisLib_803A5CC4(data->desc_text);
        HSD_SisLib_803A5CC4(data->name_text);
    } else {
        lb_80011E24(tree, &jobj, 1, -1);
        mn_8022ED6C(jobj, &mnEvent_803EF758);
    }
}

void fn_8024E34C(HSD_GObj* gobj)
{
    HSD_GObjProc* proc;
    HSD_JObj* tree = gobj->hsd_obj;
    MnEventData* data = gobj->user_data;
    PAD_STACK(16);

    if (mn_804A04F0.cur_menu != 7) {
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        proc = HSD_GObj_SetupProc(gobj, fn_8024E1B4, 0);
        proc->flags_3 = HSD_GObj_804D783C;
        HSD_SisLib_803A5CC4(data->desc_text);
        HSD_SisLib_803A5CC4(data->name_text);
    } else {
        float frame = mn_8022EC18(tree, &mnEvent_803EF740, 0x80);
        if (frame == mnEvent_803EF740.end_frame) {
            HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
            proc = HSD_GObj_SetupProc(gobj, fn_8024E2A0, 0);
            proc->flags_3 = HSD_GObj_804D783C;
        }
    }
}

void mnEvent_8024E524(s32 event_idx)
{
    HSD_GObj* event_gobj;
    s32 first_event;
    s32 i;
    u8 page;
    s32 event_id;
    u8 event;
    HSD_JObj* jobj_0B;
    HSD_JObj* jobj_0C;
    HSD_JObj* jobj_0A;
    HSD_JObj* jobj_09;
    HSD_GObj* gobj;
    HSD_GObjProc* proc;
    HSD_JObj* tree;
    MnEventData* user_data;
    void** assets;
    f32 y_a;
    f32 y_b;
    f32 y;

    assets = mnEvent_804A08F8;

    gobj = GObj_Create(6, 7, 0x80);
    mnEvent_804D6C60 = gobj;
    tree = HSD_JObjLoadJoint(assets[0]);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, tree);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 4, 0x80);
    HSD_JObjAddAnimAll(tree, assets[1], assets[2], assets[3]);
    HSD_JObjReqAnimAll(tree, 0.0f);
    HSD_JObjAnimAll(tree);

    user_data = HSD_MemAlloc(sizeof(MnEventData));
    HSD_ASSERTREPORT(0x39B, user_data, "Can't get user_data.\n");
    mnEvent_8024E420(user_data, event_idx);
    GObj_InitUserData(gobj, 0, HSD_Free, user_data);

    page = user_data->page;
    (void) page;
    lb_80011E24(tree, &jobj_0A, 0xA, -1);
    lb_80011E24(tree, &jobj_0C, 0xC, -1);
    y_a = HSD_JObjGetTranslationY(jobj_0A);
    y_b = HSD_JObjGetTranslationY(jobj_0C);
    lb_80011E24(tree, &jobj_0B, 0xB, -1);
    y = (f32) page * (y_b - y_a);
    HSD_JObjSetTranslateY(jobj_0B, y);

    proc = HSD_GObj_SetupProc(gobj, fn_8024E34C, 0);
    proc->flags_3 = HSD_GObj_804D783C;
    first_event = user_data->first_event;
    for (i = 0; i < 9; i++) {
        mnEvent_8024D15C(i, first_event + i);
    }

    event =
        gm_801BEBA8((u32) (user_data->first_event + user_data->page) & 0xFF);
    event_gobj = mnEvent_804D6C60;
    event_id = event;
    mnEvent_8024D0CC(event_gobj, (s8) gm_801BEBF8(event_id & 0xFF));
    mnEvent_8024D7E0(event_gobj, event);
    mnEvent_8024D5B0(event_gobj, event_id);
    lb_80011E24(event_gobj->hsd_obj, &jobj_09, 9, -1);
    HSD_JObjReqAnimAll(
        jobj_09, (f32) (u8) gm_801BEB8C(gm_801BEBC0(event_id & 0xFF) & 0xFF));
    HSD_JObjAnimAll(jobj_09);
    mnEvent_8024D014(event_gobj);
}

void fn_8024D864(HSD_GObj* gobj)
{
    HSD_JObj* jobj_0C;
    HSD_JObj* jobj_0A;
    HSD_JObj* jobj_0B;
    HSD_JObj* jobj_09;
    MnEventData* data;
    HSD_GObj* event_gobj;
    u64 inputs;
    s32 i;
    s32 first_event;
    s32 selected_event;
    s32 page;
    u8 event;
    f32 y_a;
    f32 y_b;
    PAD_STACK(0x78);

    if (mn_804D6BC8.cooldown != 0) {
        mn_804D6BC8.cooldown -= 1;
        mn_804D6BC8.x2 = 0;
        mn_804D6BC8.x4 = 0;
        return;
    }

    inputs = mn_804A04F0.buttons = mn_80229624(4);

    if (inputs & MenuInput_Back) {
        lbAudioAx_80024030(0);
        mn_804A04F0.entering_menu = 0;
        mn_80229894(1, 1, 3);
        return;
    }

    if (mnEvent_804D6C64 != 0) {
        mnEvent_804D6C64 -= 1;
        return;
    }

    if (mnEvent_804D6C60 == NULL) {
        mnEvent_8024E524(mnEvent_804D6C65);
    }

    data = mnEvent_804D6C60->user_data;
    if (inputs & MenuInput_Confirm) {
        lbAudioAx_80024030(1);
        gm_801BEB74(data->first_event + data->page);
        gm_801677E8(mn_802295AC());
        mn_80229860(0x2B);
        return;
    }

    if (inputs & MenuInput_XButton) {
        s32 max_events = mnEvent_8024CE74();
        if (data->first_event + 9 < max_events ||
            data->first_event != max_events)
        {
            lbAudioAx_80024030(2);
            if (data->first_event + 9 < max_events) {
                data->first_event += 9;
            } else {
                data->first_event = max_events;
            }
            first_event = data->first_event;
            for (i = 0; i < 9; i++) {
                mnEvent_8024D15C(i, first_event + i);
            }
            selected_event = data->first_event + data->page;
            event = gm_801BEBA8((u8) selected_event);
            event_gobj = mnEvent_804D6C60;
            mnEvent_8024D0CC(event_gobj, (s8) gm_801BEBF8(event));
            mnEvent_8024D7E0(event_gobj, event);
            mnEvent_8024D5B0(event_gobj, event);
            lb_80011E24(event_gobj->hsd_obj, &jobj_09, 9, -1);
            HSD_JObjReqAnimAll(jobj_09,
                               (f32) (u8) gm_801BEB8C(gm_801BEBC0(event)));
            HSD_JObjAnimAll(jobj_09);
            mnEvent_8024D014(event_gobj);
        }
    } else if (inputs & MenuInput_YButton) {
        if (data->first_event - 9 >= 0 || data->first_event != 0) {
            lbAudioAx_80024030(2);
            if (data->first_event - 9 >= 0) {
                data->first_event -= 9;
            } else {
                data->first_event = 0;
            }
            first_event = data->first_event;
            for (i = 0; i < 9; i++) {
                mnEvent_8024D15C(i, first_event + i);
            }
            selected_event = data->first_event + data->page;
            event = gm_801BEBA8((u8) selected_event);
            event_gobj = mnEvent_804D6C60;
            mnEvent_8024D0CC(event_gobj, (s8) gm_801BEBF8(event));
            mnEvent_8024D7E0(event_gobj, event);
            mnEvent_8024D5B0(event_gobj, event);
            lb_80011E24(event_gobj->hsd_obj, &jobj_09, 9, -1);
            HSD_JObjReqAnimAll(jobj_09, (f32) gm_801BEB8C(gm_801BEBC0(event)));
            HSD_JObjAnimAll(jobj_09);
            mnEvent_8024D014(event_gobj);
        }
    } else if (inputs & MenuInput_Up) {
        page = data->page;
        if (page != 0) {
            lbAudioAx_80024030(2);
            data->page -= 1;
            lb_80011E24(mnEvent_804D6C60->hsd_obj, &jobj_0A, 0xA, -1);
            lb_80011E24(mnEvent_804D6C60->hsd_obj, &jobj_0C, 0xC, -1);
            y_a = HSD_JObjGetTranslationY(jobj_0A);
            y_b = HSD_JObjGetTranslationY(jobj_0C);
            lb_80011E24(mnEvent_804D6C60->hsd_obj, &jobj_0B, 0xB, -1);
            HSD_JObjSetTranslateY(jobj_0B, (f32) data->page * (y_b - y_a));
            selected_event = data->first_event + data->page;
            event = gm_801BEBA8((u8) selected_event);
            event_gobj = mnEvent_804D6C60;
            mnEvent_8024D0CC(event_gobj, (s8) gm_801BEBF8(event));
            mnEvent_8024D7E0(event_gobj, event);
            mnEvent_8024D5B0(event_gobj, event);
            lb_80011E24(event_gobj->hsd_obj, &jobj_09, 9, -1);
            HSD_JObjReqAnimAll(jobj_09,
                               (f32) (u8) gm_801BEB8C(gm_801BEBC0(event)));
            HSD_JObjAnimAll(jobj_09);
            mnEvent_8024D014(event_gobj);
            return;
        }
        if (data->first_event != 0) {
            lbAudioAx_80024030(2);
            data->first_event -= 1;
            first_event = data->first_event;
            for (i = 0; i < 9; i++) {
                mnEvent_8024D15C(i, first_event + i);
            }
            selected_event = data->first_event + data->page;
            event = gm_801BEBA8((u8) selected_event);
            event_gobj = mnEvent_804D6C60;
            mnEvent_8024D0CC(event_gobj, (s8) gm_801BEBF8(event));
            mnEvent_8024D7E0(event_gobj, event);
            mnEvent_8024D5B0(event_gobj, event);
            lb_80011E24(event_gobj->hsd_obj, &jobj_09, 9, -1);
            HSD_JObjReqAnimAll(jobj_09,
                               (f32) (u8) gm_801BEB8C(gm_801BEBC0(event)));
            HSD_JObjAnimAll(jobj_09);
            mnEvent_8024D014(event_gobj);
        }
    } else if (inputs & MenuInput_Down) {
        page = data->page;
        if (page < 8) {
            lbAudioAx_80024030(2);
            data->page += 1;
            lb_80011E24(mnEvent_804D6C60->hsd_obj, &jobj_0A, 0xA, -1);
            lb_80011E24(mnEvent_804D6C60->hsd_obj, &jobj_0C, 0xC, -1);
            y_a = HSD_JObjGetTranslationY(jobj_0A);
            y_b = HSD_JObjGetTranslationY(jobj_0C);
            lb_80011E24(mnEvent_804D6C60->hsd_obj, &jobj_0B, 0xB, -1);
            HSD_JObjSetTranslateY(jobj_0B, (f32) data->page * (y_b - y_a));
            selected_event = data->first_event + data->page;
            event = gm_801BEBA8((u8) selected_event);
            event_gobj = mnEvent_804D6C60;
            mnEvent_8024D0CC(event_gobj, (s8) gm_801BEBF8(event));
            mnEvent_8024D7E0(event_gobj, event);
            mnEvent_8024D5B0(event_gobj, event);
            lb_80011E24(event_gobj->hsd_obj, &jobj_09, 9, -1);
            HSD_JObjReqAnimAll(jobj_09,
                               (f32) (u8) gm_801BEB8C(gm_801BEBC0(event)));
            HSD_JObjAnimAll(jobj_09);
            mnEvent_8024D014(event_gobj);
            return;
        }
        if (data->first_event < mnEvent_8024CE74()) {
            lbAudioAx_80024030(2);
            data->first_event += 1;
            first_event = data->first_event;
            for (i = 0; i < 9; i++) {
                mnEvent_8024D15C(i, first_event + i);
            }
            selected_event = data->first_event + data->page;
            event = gm_801BEBA8((u8) selected_event);
            event_gobj = mnEvent_804D6C60;
            mnEvent_8024D0CC(event_gobj, (s8) gm_801BEBF8(event));
            mnEvent_8024D7E0(event_gobj, event);
            mnEvent_8024D5B0(event_gobj, event);
            lb_80011E24(event_gobj->hsd_obj, &jobj_09, 9, -1);
            HSD_JObjReqAnimAll(jobj_09,
                               (f32) (u8) gm_801BEB8C(gm_801BEBC0(event)));
            HSD_JObjAnimAll(jobj_09);
            mnEvent_8024D014(event_gobj);
        }
    }
}

void mnEvent_8024D014(HSD_GObj* gobj)
{
    HSD_JObj* jobj;
    MnEventData* data = gobj->user_data;
    HSD_JObj* tree = gobj->hsd_obj;
    PAD_STACK(8);

    lb_80011E24(tree, &jobj, 3, -1);
    if (data->first_event == 0) {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
    } else {
        HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
    }

    lb_80011E24(tree, &jobj, 2, -1);
    if (data->first_event == mnEvent_8024CE74()) {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
    } else {
        HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
    }
}

void mnEvent_8024D0CC(HSD_GObj* gobj, s32 event)
{
    HSD_JObj* tree = gobj->hsd_obj;
    HSD_JObj* jobj;
    f32 frame;
    FORCE_PAD_STACK_4;

    if (event == 0x21) {
        frame = 25.0f;
    } else {
        frame = gm_80164024(event);
    }

    lb_80011E24(tree, &jobj, 4, -1);
    HSD_JObjReqAnimAll(jobj, frame);
    HSD_JObjAnimAll(jobj);
}

void mnEvent_8024D7E0(HSD_GObj* gobj, s32 idx)
{
    MnEventData* data = gobj->user_data;
    HSD_Text* text;
    s32 sis_idx;
    PAD_STACK(8);

    if (data->desc_text != NULL) {
        HSD_SisLib_803A5CC4(data->desc_text);
    }

    sis_idx = (idx * 2) + 0x155;
    text =
        HSD_SisLib_803A5ACC(0, 1, -9.5f, 8.0f, 17.0f, 364.68332f, 38.38772f);
    data->desc_text = text;
    text->font_size.x = 0.0521f;
    text->font_size.y = 0.0521f;
    HSD_SisLib_803A6368(text, sis_idx);
}

void mnEvent_8024E420(MnEventData* data, s32 event_idx)
{
    s32 max_events;
    int i;

    max_events = mnEvent_8024CE74();

    if (event_idx < max_events) {
        data->first_event = event_idx;
        data->page = 0;
    } else {
        data->first_event = max_events;
        data->page = event_idx - max_events;
    }

    data->desc_text = NULL;
    data->name_text = NULL;

    for (i = 0; i < 9; i++) {
        data->gobjs[i] = NULL;
        data->texts[i] = NULL;
        data->icons[i] = NULL;
    }
}

void mnEvent_8024E838(int event_idx, int first_time)
{
    HSD_GObjProc* proc;
    void** arr = mnEvent_804A08F8;
    char* base = (char*) &mnEvent_803EF740;

    mn_804D6BC8.cooldown = 5;
    mn_804A04F0.prev_menu = mn_804A04F0.cur_menu;
    mn_804A04F0.cur_menu = 7;
    mn_804A04F0.hovered_selection = 0;
    mnEvent_804D6C65 = event_idx;

    if (first_time) {
        mnEvent_804D6C64 = 0x14;
    } else {
        mnEvent_804D6C64 = 0;
    }

    mnEvent_804D6C60 = NULL;
    {
        HSD_Archive* archive = mn_804D6BB8;
        lbArchive_LoadSections(archive, arr, base + 0xA0, arr + 1, base + 0xB8,
                               arr + 2, base + 0xD4, arr + 3, base + 0xF4,
                               arr + 4, base + 0x118, 0);
    }

    if (first_time == 0) {
        mnEvent_8024E524(event_idx);
    }

    proc = HSD_GObj_SetupProc(GObj_Create(0, 1, 0x80), fn_8024D864, 0);
    proc->flags_3 = HSD_GObj_804D783C;
}
