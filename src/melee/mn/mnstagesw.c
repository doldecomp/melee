#include "mnstagesw.h"

#include <sysdolphin/baselib/debug.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjobject.h>
#include <sysdolphin/baselib/gobjplink.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/gobjuserdata.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/memory.h>
#include <sysdolphin/baselib/sislib.h>
#include <melee/gm/gm_1601.h>
#include <melee/gm/gm_1A3F.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/lb/lb_00B0.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lbcardgame.h>
#include <melee/lb/lbspdisplay.h>
#include <melee/mn/mnmain.h>
#include <melee/mn/mnruleplus.h>
#include <melee/sc/types.h>

#define NUM_STAGES 29

typedef struct MnStageSwData {
    u8 x0;
    u8 x1;
    u8 x2[NUM_STAGES];
    u8 x1F;
    HSD_JObj* x20;
    HSD_JObj* x24;
    HSD_JObj* x28;
    HSD_JObj* x2C;
    HSD_JObj* x30;
    HSD_JObj* x34;
    u8 pad_38[8];
    HSD_Text* x40[NUM_STAGES];
} MnStageSwData;

AnimLoopSettings mnStageSw_803ED488[5] = {
    { 0.0f, 199.0f, 0.0f }, { 0.0f, 9.0f, -0.1f }, { 0.0f, 0.0f, -0.1f },
    { 0.0f, 0.0f, -0.1f },  { 0.0f, 0.0f, -0.1f },
};

/// Stage switch toggle indices - maps menu position to internal stage ID
static u8 mnStageSw_803ED4C4[NUM_STAGES] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,
    0x0B, 0x0A, 0x18, 0x1A, 0x1C, 0x0C, 0x0D, 0x0E, 0x0F, 0x10,
    0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x19, 0x1B,
};

/// Stage switch icon indices
static u8 mnStageSw_stageIcons[NUM_STAGES] = {
    0x08, 0x09, 0x11, 0x0A, 0x0C, 0x06, 0x0B, 0x07, 0x0E, 0x0D,
    0x1D, 0x17, 0x0F, 0x10, 0x12, 0x13, 0x14, 0x15, 0x1A, 0x1B,
    0x1C, 0x16, 0x18, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24,
};

static f32 mnStageSw_804D4BB8[2] = { 0.0F, 1.0F };
static HSD_GObj* mnStageSw_804D6BF0;
static s8 mnStageSw_804D6BF4;
extern u8 mn_804D6BB5;
extern StaticModelDesc MenMainConSs_Top;
extern StaticModelDesc MenMainCursorSs_Top;

/* 23593C */ static void mnStageSw_8023593C(HSD_GObj* gobj);
/* 2359C8 */ static void mnStageSw_802359C8(MnStageSwData* data);
/* 235C58 */ static s32 mnStageSw_80235C58(u8 arg0);
/* 235DC8 */ static void mnStageSw_80235DC8(u8* user_data, s32 buttons);
/* 235F80 */ static void fn_80235F80(HSD_GObj* gobj);
/* 236178 */ static void mnStageSw_80236178(MnStageSwData* data, u8 idx);
/* 2364A0 */ static HSD_JObj* mnStageSw_802364A0(MnStageSwData* data, u8 idx);
/* 236548 */ static void mnStageSw_80236548(HSD_GObj* gobj, u8 arg1, u8 arg2);
/* 236998 */ static void fn_80236998(HSD_GObj* gobj);
/* 236CBC */ static HSD_GObj* mnStageSw_80236CBC(s8 arg0);

/// Sync stage toggle states from user data to unlock system.
/// For each stage, if it's unlocked, set its enable state from user_data[i+2].
/// Stack padding required to match original frame size.
/// Pragma prevents inlining - function is called from fn_80235F80, not
/// inlined.
#pragma dont_inline on
static void mnStageSw_8023593C(HSD_GObj* gobj)
{
    s32 i;
    u8* user_data = gobj->user_data;
    u8* p;
    u8 pad[8];
    (void) pad;

    for (i = 0; i < NUM_STAGES; i++) {
        p = mnStageSw_803ED4C4 + (u8) i;
        if (gm_80164430(gm_801641CC(*p)) != 0) {
            gm_801641E4(mnStageSw_803ED4C4[i], user_data[i + 2]);
        }
    }
}
#pragma dont_inline reset

static void mnStageSw_802359C8(MnStageSwData* data)
{
    f32 start_y;
    HSD_Text* text;
    f32 delta_y;
    f32 step_y;
    s32 i;

    start_y = -1.6f + HSD_JObjGetTranslationY(data->x2C);
    step_y = HSD_JObjGetTranslationY(data->x2C);
    delta_y = HSD_JObjGetTranslationY(data->x30);
    (void) delta_y;
    delta_y -= step_y;

    for (i = 0; i < 15; i++) {
        text = HSD_SisLib_803A5ACC(
            0, mn_804D6BB5, 1.0f + HSD_JObjGetTranslationX(data->x2C),
            -((delta_y * (f32) i) + start_y), 17.5f, 160.0f, 300.0f);
        data->x40[i] = text;
        text->font_size.x = 0.0521f;
        text->font_size.y = 0.0521f;
        text->default_alignment = 2;
        text->default_fitting = 1;
        if (gm_80164430(gm_801641CC(mnStageSw_803ED4C4[(u8) i])) != 0) {
            HSD_SisLib_803A6368(text,
                                mnStageSw_stageIcons[mnStageSw_803ED4C4[i]]);
        } else {
            HSD_SisLib_803A6368(text, 0x25);
        }
    }

    for (i = 15; i < NUM_STAGES; i++) {
        text = HSD_SisLib_803A5ACC(
            0, mn_804D6BB5, 1.0f + HSD_JObjGetTranslationX(data->x34),
            -((delta_y * (f32) (i - 15)) + start_y), 17.5f, 160.0f, 300.0f);
        data->x40[i] = text;
        text->font_size.x = 0.0521f;
        text->font_size.y = 0.0521f;
        text->default_alignment = 2;
        text->default_fitting = 1;
        if (gm_80164430(gm_801641CC(mnStageSw_803ED4C4[(u8) i])) != 0) {
            HSD_SisLib_803A6368(text,
                                mnStageSw_stageIcons[mnStageSw_803ED4C4[i]]);
        } else {
            HSD_SisLib_803A6368(text, 0x25);
        }
    }
}

static s32 mnStageSw_80235C58(u8 arg0)
{
    s32 low;
    s32 found;
    s32 i;
    s32 idx;
    u8 high;
    s32 curr;
    s32 next;
    u8 end;
    u8 start;

    if (arg0 < 15) {
        low = 0;
        high = 14;
    } else {
        low = 15;
        high = 28;
    }
    if (arg0 < 15) {
        start = 0;
        end = 14;
    } else {
        start = 15;
        end = 28;
    }

    curr = start;
    while (curr <= end) {
        u8 stage_id = mnStageSw_803ED4C4[(u8) curr];

        if (gm_80164430(gm_801641CC(stage_id)) != 0) {
            found = 0;
            goto loop_done;
        }
        curr++;
    }
    found = 1;
loop_done:
    if (found != 0) {
        return -1;
    }

    if (arg0 < NUM_STAGES &&
        gm_80164430(gm_801641CC(mnStageSw_803ED4C4[arg0])) != 0)
    {
        return arg0;
    }

    idx = arg0;
    i = 1;
    next = idx + 1;
    curr = idx + 1;
    while (true) {
        s32 temp = idx - i;
        s32 prev = temp;

        if (low <= prev &&
            gm_80164430(gm_801641CC(mnStageSw_803ED4C4[(u8) prev])) != 0)
        {
            return prev;
        }
        if (next <= high &&
            gm_80164430(gm_801641CC(mnStageSw_803ED4C4[(u8) curr])) != 0)
        {
            return idx + i;
        }
        next++;
        curr++;
        i++;
    }
}

static void mnStageSw_80235DC8(u8* user_data, s32 buttons)
{
    s32 selection;
    u8 idx;

    idx = mn_804A04F0.hovered_selection;
    if (buttons & 1) {
        do {
            switch (idx) {
            case 0:
                mn_804A04F0.hovered_selection = 14;
                break;
            case 15:
                mn_804A04F0.hovered_selection = 28;
                break;
            default:
                mn_804A04F0.hovered_selection = idx - 1;
                break;
            }
            idx = mn_804A04F0.hovered_selection;
        } while (gm_80164430(gm_801641CC(mnStageSw_803ED4C4[idx])) == 0);
        mn_804A04F0.confirmed_selection = user_data[idx + 2];
        return;
    }

    if (buttons & 2) {
        do {
            switch (idx) {
            case 14:
                mn_804A04F0.hovered_selection = 0;
                break;
            case 28:
                mn_804A04F0.hovered_selection = 15;
                break;
            default:
                mn_804A04F0.hovered_selection = idx + 1;
                break;
            }
            idx = mn_804A04F0.hovered_selection;
        } while (gm_80164430(gm_801641CC(mnStageSw_803ED4C4[idx])) == 0);
        mn_804A04F0.confirmed_selection = user_data[idx + 2];
        return;
    }

    if (buttons & 4) {
        if (idx >= 15 && idx < NUM_STAGES) {
            selection = mnStageSw_80235C58(idx - 15);
            if (selection != -1) {
                mn_804A04F0.hovered_selection = (u8) selection;
                mn_804A04F0.confirmed_selection =
                    user_data[(u8) selection + 2];
            }
        }
    } else if ((buttons & 8) && idx < 15) {
        selection = mnStageSw_80235C58(idx + 15);
        if (selection != -1) {
            mn_804A04F0.hovered_selection = (u8) selection;
            mn_804A04F0.confirmed_selection = user_data[(u8) selection + 2];
        }
    }
}

static void fn_80235F80(HSD_GObj* gobj)
{
    s32 i;
    u8* stage_ids;
    s32 enabled;
    s32 result;
    u32 buttons;
    s32 count;
    u8* user_data;

    user_data = mnStageSw_804D6BF0->user_data;
    {
        u32 tmp = mn_80229624(4U);
        mn_804A04F0.buttons = tmp;
        buttons = tmp;
    }
    count = 0;
    PAD_STACK(0x28);
    if (buttons & 0x20) {
        lbAudioAx_80024030(0);
        mn_804A04F0.entering_menu = 0;
        mnStageSw_8023593C(mnStageSw_804D6BF0);
        lb_8001CE00();
        mn_804D6BC8.cooldown = 5;
        mn_802339FC();
        HSD_GObjPLink_80390228(gobj);
        return;
    }
    if ((u8) mnStageSw_804D6BF4 == 0) {
        if (buttons & 0x200) {
            if (mn_804A04F0.hovered_selection < NUM_STAGES) {
                if (mn_804A04F0.confirmed_selection != 0) {
                    user_data = mnStageSw_804D6BF0->user_data;
                    for (i = count; i < NUM_STAGES; i++) {
                        if (user_data[i + 2] != 0) {
                            count++;
                        }
                    }
                    if (count > 1) {
                        enabled = 0;
                    } else {
                        enabled = 1;
                    }
                    if (enabled != 0) {
                        lbAudioAx_80024030(3);
                    } else {
                        lbAudioAx_80024030(2);
                        mn_804A04F0.confirmed_selection = 0;
                    }
                } else {
                    lbAudioAx_80024030(2);
                    mn_804A04F0.confirmed_selection = 1;
                }
                user_data = mnStageSw_804D6BF0->user_data;
                stage_ids = mnStageSw_803ED4C4;
                i = 0;
                do {
                    if (gm_80164430(gm_801641CC(mnStageSw_803ED4C4[(u8) i])) !=
                        0)
                    {
                        gm_801641E4(*stage_ids, user_data[i + 2]);
                    }
                    i++;
                    stage_ids++;
                } while (i < NUM_STAGES);
                return;
            }
            goto check_dpad;
        }
        if (buttons & 0x100) {
            lbAudioAx_80024030(1);
            result = gm_801A4310();
            switch (result) {
            case 1:
                mnStageSw_8023593C(mnStageSw_804D6BF0);
                lb_8001CE00();
                mn_80229860(2);
                return;
            default:
                mnStageSw_8023593C(mnStageSw_804D6BF0);
                lb_8001CE00();
                mn_8022F4CC();
                return;
            }
        }
    check_dpad:
        if (buttons & 0xF) {
            lbAudioAx_80024030(2);
            mnStageSw_80235DC8(user_data, buttons);
        }
    }
}

static void mnStageSw_80236178_noinline(MnStageSwData* data, u8 idx);
static void mnStageSw_80236178_noinline(MnStageSwData* data, u8 idx)
{
    mnStageSw_80236178(data, idx);
}

/// Position stage icon JObj based on index
/// Uses stored reference JObjs to calculate X/Y position
static void mnStageSw_80236178(MnStageSwData* data, u8 idx)
{
    HSD_JObj* jobj;
    HSD_JObj* ref_jobj;
    f32 delta;

    jobj = data->x28;
    HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);

    delta = HSD_JObjGetTranslationY(data->x30) -
            HSD_JObjGetTranslationY(data->x2C);

    if ((u8) idx < 15) {
        ref_jobj = data->x2C;
        HSD_JObjSetTranslateX(jobj, HSD_JObjGetTranslationX(ref_jobj));
        HSD_JObjSetTranslateY(jobj, delta * (f32) (u8) idx +
                                        HSD_JObjGetTranslationY(data->x2C));
    } else {
        ref_jobj = data->x34;
        HSD_JObjSetTranslateX(jobj, HSD_JObjGetTranslationX(ref_jobj));
        HSD_JObjSetTranslateY(jobj, delta * (f32) ((u8) idx - 15) +
                                        HSD_JObjGetTranslationY(data->x2C));
    }
}
static HSD_JObj* mnStageSw_802364A0_noinline(MnStageSwData* data, u8 idx);
static HSD_JObj* mnStageSw_802364A0_noinline(MnStageSwData* data, u8 idx)
{
    return mnStageSw_802364A0(data, idx);
}

/// Get JObj for stage icon at given index
/// Navigates JObj tree stored in data->x2C (idx < 15) or data->x34
/// (idx >= 15)
static HSD_JObj* mnStageSw_802364A0(MnStageSwData* data, u8 idx)
{
    HSD_JObj* jobj;
    u8 i;

    if (idx >= 15) {
        jobj = HSD_JObjGetChild(data->x34);
        for (i = 15; i < idx; i++) {
            jobj = HSD_JObjGetNext(jobj);
        }
        return jobj;
    }
    jobj = HSD_JObjGetChild(data->x2C);
    for (i = 0; i < idx; i++) {
        jobj = HSD_JObjGetNext(jobj);
    }
    return jobj;
}

static void mnStageSw_80236548(HSD_GObj* gobj, u8 arg1, u8 arg2)
{
    HSD_JObj* hover_anim_jobj;
    HSD_JObj* cursor_jobj;
    HSD_JObj* jobj;
    MnStageSwData* data;
    f32 delta_y;
    f32 frame;
    f32 x;
    u16 hovered;
    u8 sel;

    data = gobj->user_data;
    if (arg1 != 0) {
        jobj = mnStageSw_802364A0_noinline(data, data->x1);
        lb_80011E24(jobj, &hover_anim_jobj, 3, -1);
        HSD_JObjSetFlagsAll(hover_anim_jobj, JOBJ_HIDDEN);
        frame = mn_8022F298(hover_anim_jobj);
        sel = (u8) mn_804A04F0.hovered_selection;
        jobj = mnStageSw_802364A0_noinline(data, sel);
        lb_80011E24(jobj, &hover_anim_jobj, 3, -1);
        HSD_JObjClearFlagsAll(hover_anim_jobj, JOBJ_HIDDEN);
        HSD_JObjReqAnimAll(hover_anim_jobj, frame);
        HSD_JObjAnimAll(hover_anim_jobj);
        cursor_jobj = data->x28;
        HSD_JObjClearFlagsAll(cursor_jobj, JOBJ_HIDDEN);
        delta_y = HSD_JObjGetTranslationY(data->x30) -
                  HSD_JObjGetTranslationY(data->x2C);
        if (sel < 15) {
            x = HSD_JObjGetTranslationX(data->x2C);
            HSD_JObjSetTranslateX(cursor_jobj, x);
            HSD_JObjSetTranslateY(cursor_jobj,
                                  delta_y * (f32) sel +
                                      HSD_JObjGetTranslationY(data->x2C));
        } else {
            x = HSD_JObjGetTranslationX(data->x34);
            HSD_JObjSetTranslateX(cursor_jobj, x);
            HSD_JObjSetTranslateY(cursor_jobj,
                                  delta_y * (f32) (sel - 15) +
                                      HSD_JObjGetTranslationY(data->x2C));
        }
    }
    if (arg2 != 0) {
        HSD_JObj* sp3C;

        arg2 = mn_804A04F0.confirmed_selection;
        jobj = mnStageSw_802364A0_noinline(data,
                                           (u8) mn_804A04F0.hovered_selection);
        lb_80011E24(jobj, &sp3C, 2, -1);
        HSD_JObjReqAnimAll(sp3C, mnStageSw_804D4BB8[arg2]);
        HSD_JObjAnimAll(sp3C);
    }
    if (arg1 != 0) {
        hovered = mn_804A04F0.hovered_selection;
    } else {
        hovered = data->x1;
    }
    sel = hovered;
    lb_80011E24(mnStageSw_802364A0_noinline(data, sel), &hover_anim_jobj, 3,
                -1);
    mn_8022ED6C(hover_anim_jobj, mnStageSw_803ED488);
}

#pragma push
#pragma inline_depth(0)
static void fn_80236998(HSD_GObj* gobj)
{
    u64 pad2;
    HSD_JObj* child;
    HSD_JObj* jobj;
    MnStageSwData* data;
    AnimLoopSettings* anims;
    s32 changed_menu;
    s32 changed_hovered;
    u64 pad3;
    s32 changed_confirmed;
    u8 state;

    changed_menu = 0;
    changed_hovered = 0;
    changed_confirmed = 0;
    data = gobj->user_data;
    state = data->x1F;
    PAD_STACK(4);
    (void) pad2;
    if ((state == 0 || state == 1 || state == 3) &&
        data->x0 != (u8) mn_804A04F0.cur_menu)
    {
        if (mn_804A04F0.entering_menu != 0) {
            data->x1F = 4;
        } else {
            data->x1F = 2;
        }
        switch ((s32) data->x1F) {
        case 1:
            anims = &mnStageSw_803ED488[1];
            break;
        case 2:
            anims = &mnStageSw_803ED488[3];
            break;
        case 3:
            anims = &mnStageSw_803ED488[2];
            break;
        case 4:
            anims = &mnStageSw_803ED488[4];
            break;
        }
        jobj = data->x24;
        HSD_JObjReqAnim(jobj, anims->start_frame);
        HSD_JObjAnim(jobj);
        state = data->x1F;
        if (state == 0 || state == 1 || state == 3) {
            changed_menu = 1;
            changed_hovered = 1;
            changed_confirmed = 1;
        }
    }

    state = data->x1F;
    if (state != 0) {
        jobj = data->x24;
        switch ((s32) state) {
        case 1:
            anims = &mnStageSw_803ED488[1];
            break;
        case 2:
            anims = &mnStageSw_803ED488[3];
            break;
        case 3:
            anims = &mnStageSw_803ED488[2];
            break;
        case 4:
            anims = &mnStageSw_803ED488[4];
            break;
        }
        if (mn_8022F298(jobj) >= anims->end_frame) {
            switch ((s32) data->x1F) {
            case 1:
            case 3: {
                s32 i;

                data->x1F = i = 0;
                mnStageSw_802359C8(data);
                gobj = gobj->user_data;
                HSD_JObjClearFlagsAll(((MnStageSwData*) gobj)->x2C,
                                      JOBJ_HIDDEN);
                HSD_JObjClearFlagsAll(((MnStageSwData*) gobj)->x34,
                                      JOBJ_HIDDEN);
                for (; i < NUM_STAGES; i++) {
                    jobj = mnStageSw_802364A0((MnStageSwData*) gobj, i);
                    if (i != ((MnStageSwData*) gobj)->x1) {
                        lb_80011E24(jobj, &child, 3, -1);
                        HSD_JObjSetFlagsAll(child, JOBJ_HIDDEN);
                    }
                }
                mnStageSw_80236178((MnStageSwData*) gobj,
                                   ((MnStageSwData*) gobj)->x1);
                mnStageSw_804D6BF4 = 0;
                return;
            }
            case 2:
            case 4: {
                s32 i;

                for (i = 0; i < NUM_STAGES; i++) {
                    HSD_SisLib_803A5CC4(data->x40[i]);
                }
                HSD_GObjPLink_80390228(gobj);
                return;
            }
            }
        } else {
            HSD_JObjAnim(jobj);
        }
    }

    state = data->x1F;
    if (state == 0 || state == 1 || state == 3) {
        if ((s32) data->x1 != (s32) mn_804A04F0.hovered_selection) {
            changed_hovered = 1;
        }
        if (data->x2[mn_804A04F0.hovered_selection] !=
            (u8) mn_804A04F0.confirmed_selection)
        {
            changed_confirmed = 1;
        }
    }

    mnStageSw_80236548(gobj, changed_hovered, changed_confirmed);
    if (changed_menu != 0) {
        data->x0 = mn_804A04F0.cur_menu;
    }
    if (changed_hovered != 0) {
        data->x1 = mn_804A04F0.hovered_selection;
    }
    if (changed_confirmed != 0) {
        data->x2[mn_804A04F0.hovered_selection] =
            mn_804A04F0.confirmed_selection;
    }
}
#pragma pop

static HSD_GObj* mnStageSw_80236CBC(s8 arg0)
{
    AnimLoopSettings* anims = mnStageSw_803ED488;
    struct StaticModelDesc* mdl = &MenMainConSs_Top;
    HSD_JObj* jobj;
    HSD_JObj* sp48;
    MnStageSwData* user_data;
    f32 y_spacing;
    u8 hovered;
    HSD_JObj* cursor_anim_jobj;
    s32 i;
    u8 idx;

    HSD_GObj* gobj = GObj_Create(6, 7, 0x80);
    mnStageSw_804D6BF0 = gobj;

    jobj = HSD_JObjLoadJoint(mdl->joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 6, 0x80);
    HSD_GObj_SetupProc(gobj, fn_80236998, 0);

    HSD_JObjAddAnimAll(jobj, mdl->animjoint, mdl->matanim_joint,
                       mdl->shapeanim_joint);
    HSD_JObjReqAnimAll(jobj, 0.0f);
    HSD_JObjAnimAll(jobj);

    user_data = HSD_MemAlloc(sizeof(MnStageSwData));
    HSD_ASSERTREPORT(0x397, user_data, "Can't get user_data.\n");
    GObj_InitUserData(gobj, 0, HSD_Free, user_data);

    user_data->x0 = mn_804A04F0.cur_menu;
    {
        idx = 0;

        user_data->x1 = (u8) mn_804A04F0.hovered_selection;
        user_data->x1F = arg0;
        for (; idx < NUM_STAGES; idx++) {
            u8 stage_id = mnStageSw_803ED4C4[idx];

            if (gm_80164430(gm_801641CC(stage_id)) != 0) {
                user_data->x2[idx] =
                    ((1 << stage_id) & gmMainLib_8015CC58()->stage_mask) != 0;
            } else {
                user_data->x2[idx] = 0;
            }
        }
    }

    for (i = 0; i < 6; i++) {
        lb_80011E24(jobj, &user_data->x20 + i, i, -1);
    }

    mn_804A04F0.confirmed_selection = user_data->x2[user_data->x1];
    y_spacing = HSD_JObjGetTranslationY(user_data->x30) -
                HSD_JObjGetTranslationY(user_data->x2C);
    for (i = 0; i < NUM_STAGES; i++) {
        HSD_JObj* cursor_jobj;
        u8 enabled;
        u8 idx;

        hovered = mn_804A04F0.hovered_selection;
        cursor_jobj = HSD_JObjLoadJoint(MenMainCursorSs_Top.joint);
        HSD_JObjAddAnimAll(cursor_jobj, MenMainCursorSs_Top.animjoint,
                           MenMainCursorSs_Top.matanim_joint,
                           MenMainCursorSs_Top.shapeanim_joint);
        idx = i;
        enabled = user_data->x2[idx];
        lb_80011E24(cursor_jobj, &cursor_anim_jobj, 2, -1);
        HSD_JObjReqAnimAll(cursor_anim_jobj, mnStageSw_804D4BB8[enabled]);
        HSD_JObjAnimAll(cursor_anim_jobj);
        lb_80011E24(cursor_jobj, &sp48, 3, -1);
        if (idx == hovered) {
            HSD_JObjReqAnimAll(sp48, anims[0].start_frame);
            HSD_JObjAnimAll(sp48);
        } else {
            HSD_JObjSetFlagsAll(sp48, JOBJ_HIDDEN);
        }
        if (gm_80164430(gm_801641CC(mnStageSw_803ED4C4[idx])) == 0) {
            HSD_JObjSetFlagsAll(cursor_jobj, JOBJ_HIDDEN);
        }
        if (i < 15) {
            HSD_JObjAddChild(user_data->x2C, cursor_jobj);
            HSD_JObjAddTranslationY(cursor_jobj, y_spacing * (f32) i);
        } else {
            HSD_JObjAddChild(user_data->x34, cursor_jobj);
            HSD_JObjAddTranslationY(cursor_jobj, y_spacing * (f32) (i - 15));
        }
    }

    HSD_JObjSetFlagsAll(user_data->x2C, JOBJ_HIDDEN);

    {
        u8 hovered;
        f32 y_spacing;
        HSD_JObj* cursor;

        HSD_JObjSetFlagsAll(user_data->x34, JOBJ_HIDDEN);
        cursor = user_data->x28;
        hovered = user_data->x1;
        HSD_JObjClearFlagsAll(cursor, JOBJ_HIDDEN);
        y_spacing = HSD_JObjGetTranslationY(user_data->x30) -
                    HSD_JObjGetTranslationY(user_data->x2C);
        if (hovered < 15) {
            HSD_JObjSetTranslateX(cursor,
                                  HSD_JObjGetTranslationX(user_data->x2C));
            HSD_JObjSetTranslateY(cursor,
                                  y_spacing * (f32) hovered +
                                      HSD_JObjGetTranslationY(user_data->x2C));
        } else {
            HSD_JObjSetTranslateX(cursor,
                                  HSD_JObjGetTranslationX(user_data->x34));
            HSD_JObjSetTranslateY(cursor,
                                  y_spacing * (f32) (hovered - 15) +
                                      HSD_JObjGetTranslationY(user_data->x2C));
        }
    }
    HSD_JObjSetFlagsAll(user_data->x28, JOBJ_HIDDEN);
    return gobj;
}

void mnStageSw_80237410(void)
{
    HSD_GObj* gobj;
    HSD_GObjProc* proc;

    mn_804A04F0.prev_menu = mn_804A04F0.cur_menu;
    mn_804A04F0.cur_menu = 0x11;
    mn_804A04F0.hovered_selection = mnStageSw_80235C58(0);
    mnStageSw_804D6BF4 = 1;
    gobj = mnStageSw_80236CBC(1);
    HSD_GObj_80390CD4(gobj);
    gobj = GObj_Create(0, 1, 0x80);
    proc = HSD_GObj_SetupProc(gobj, fn_80235F80, 0);
    proc->flags_3 = HSD_GObj_804D783C;
}
