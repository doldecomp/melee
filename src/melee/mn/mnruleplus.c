#include "mnruleplus.h"

#include "platform.h"

#include <dolphin/os.h>

#include "baselib/debug.h"
#include "baselib/gobj.h"
#include "baselib/gobjgxlink.h"
#include "baselib/gobjobject.h"
#include "baselib/gobjplink.h"
#include "baselib/gobjproc.h"
#include "baselib/gobjuserdata.h"
#include "baselib/jobj.h"
#include "baselib/memory.h"
#include "baselib/sislib.h"
#include "gm/gm_1A3F.h"
#include "gm/gmmain_lib.h"
#include "gm/types.h"

#include "lb/lb_00F9.h"
#include "lb/lbaudio_ax.h"

#include "mn/forward.h"

#include "mn/mnmain.h"
#include "mn/mnmainrule.h"
#include "mn/mnstagesw.h"
#include "sc/types.h"

extern StaticModelDesc MenMainConRl_Top;
extern StaticModelDesc MenMainCursorRl_Top;
extern StaticModelDesc MenMainCursorTr01_Top;
extern StaticModelDesc MenMainCursorTr02_Top;
extern StaticModelDesc MenMainCursorTr03_Top;
extern StaticModelDesc MenMainCursorTr04_Top;
extern StaticModelDesc MenMainNmRl_Top;
extern MenuKindData mn_803EB6B0[];
extern HSD_GObj* mn_804D6BE0;
extern f32 mn_804D6BE4;

static mn_803ED1D0_t mn_803ED1D0 = {
    { 3, 4, 5, 6, 7, 8, 9 },
    { 7, 2, 2, 2, 2, 0 },
    { 20.0f, 21.0f, 22.0f, 23.0f, 24.0f, 25.0f, 26.0f, 27.0f, 28.0f, 29.0f,
      30.0f, 31.0f },
    { 0.0f, 99.0f, 0.0f },
    { 200.0f, 399.0f, 200.0f },
    { { 100.0f, 124.0f, -0.1f }, { 125.0f, 149.0f, -0.1f } },
    { { 150.0f, 174.0f, -0.1f }, { 175.0f, 199.0f, -0.1f } },
    { 0.0f, 99.0f, 60.0f },
};

AnimLoopSettings mn_803ED270[3] = {
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
};

AnimLoopSettings mn_803ED294[7] = {
    { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
};

u8 mn_803ED2E8[16][2] = { 0 };

typedef union {
    s32 packed;
    u8 idx[4];
} JObjIndices;

static JObjIndices mn_804DBE40 = { 0x02030506 };
static f32 mn_804DBE44 = 0.0f;
static JObjIndices mn_804DBE48 = { 0x02030506 };

void fn_8023201C(HSD_GObj* gobj)
{
    MenuRulesPlusData* data = mn_804D6BE0->user_data;
    u32 buttons;

    buttons = mn_80229624(4);
    mn_804A04F0.buttons = buttons;

    if (buttons & 0x200) {
        if ((u16) mn_804A04F0.hovered_selection == 5) {
            lbAudioAx_80024030(1);
            mn_804A04F0.entering_menu = 1;
            {
                MenuRulesPlusData* data2 = mn_804D6BE0->user_data;
                u8 val;
                val = data2->rule_values.time_limit;
                gmMainLib_8015CC34()->stock_time_limit = val;
                val = data2->rule_values.friendly_fire;
                gmMainLib_8015CC34()->friendly_fire = val;
                val = data2->rule_values.pause;
                gmMainLib_8015CC34()->pause = val;
                val = data2->rule_values.score;
                gmMainLib_8015CC34()->score_display = val;
                val = data2->rule_values.sd_penalty;
                gmMainLib_8015CC34()->unk_xc = val;
            }
            mn_804D6BC8.cooldown = 5;
            mnStageSw_80237410();
            HSD_GObjPLink_80390228(gobj);
        }
    } else {
        if (buttons & 0x100) {
            lbAudioAx_80024030(1);
            if ((s32) gm_801A4310() == 1) {
                MenuRulesPlusData* data2 = mn_804D6BE0->user_data;
                u8 val;
                val = data2->rule_values.time_limit;
                gmMainLib_8015CC34()->stock_time_limit = val;
                val = data2->rule_values.friendly_fire;
                gmMainLib_8015CC34()->friendly_fire = val;
                val = data2->rule_values.pause;
                gmMainLib_8015CC34()->pause = val;
                val = data2->rule_values.score;
                gmMainLib_8015CC34()->score_display = val;
                val = data2->rule_values.sd_penalty;
                gmMainLib_8015CC34()->unk_xc = val;
                mn_80229860(2);
                return;
            }
            {
                MenuRulesPlusData* data2 = mn_804D6BE0->user_data;
                u8 val;
                val = data2->rule_values.time_limit;
                gmMainLib_8015CC34()->stock_time_limit = val;
                val = data2->rule_values.friendly_fire;
                gmMainLib_8015CC34()->friendly_fire = val;
                val = data2->rule_values.pause;
                gmMainLib_8015CC34()->pause = val;
                val = data2->rule_values.score;
                gmMainLib_8015CC34()->score_display = val;
                val = data2->rule_values.sd_penalty;
                gmMainLib_8015CC34()->unk_xc = val;
            }
            mn_8022F4CC();
            return;
        }
        if (buttons & 0x20) {
            lbAudioAx_80024030(0);
            mn_804A04F0.entering_menu = 0;
            {
                MenuRulesPlusData* data2 = mn_804D6BE0->user_data;
                u8 val;
                val = data2->rule_values.time_limit;
                gmMainLib_8015CC34()->stock_time_limit = val;
                val = data2->rule_values.friendly_fire;
                gmMainLib_8015CC34()->friendly_fire = val;
                val = data2->rule_values.pause;
                gmMainLib_8015CC34()->pause = val;
                val = data2->rule_values.score;
                gmMainLib_8015CC34()->score_display = val;
                val = data2->rule_values.sd_penalty;
                gmMainLib_8015CC34()->unk_xc = val;
            }
            mn_804D6BC8.cooldown = 5;
            mn_8023164C();
            HSD_GObjPLink_80390228(gobj);
            return;
        }
        if (buttons & 1) {
            s32 visible;
            u8 sel;
            lbAudioAx_80024030(2);
            do {
                if ((s32) mn_804A04F0.hovered_selection == 0) {
                    mn_804A04F0.hovered_selection = 5;
                } else {
                    mn_804A04F0.hovered_selection -= 1;
                }
                sel = (u8) mn_804A04F0.hovered_selection;
                if (gm_801A4310() == 0x1B && sel == 1) {
                    visible = 0;
                } else if (sel == 3) {
                    if (gmMainLib_8015EE0C() != 0) {
                        visible = 1;
                    } else {
                        visible = 0;
                    }
                } else if (sel == 5) {
                    if (gmMainLib_8015EE44() != 0) {
                        visible = 1;
                    } else {
                        visible = 0;
                    }
                } else {
                    visible = 1;
                }
            } while (visible == 0);
            mn_804A04F0.confirmed_selection =
                data->rule_values
                    .values[mn_804A04F0.hovered_selection];
            return;
        }
        if (buttons & 2) {
            s32 visible;
            u8 sel;
            lbAudioAx_80024030(2);
            do {
                if ((s32) mn_804A04F0.hovered_selection == 5) {
                    mn_804A04F0.hovered_selection = 0;
                } else {
                    mn_804A04F0.hovered_selection += 1;
                }
                sel = (u8) mn_804A04F0.hovered_selection;
                if (gm_801A4310() == 0x1B && sel == 1) {
                    visible = 0;
                } else if (sel == 3) {
                    if (gmMainLib_8015EE0C() != 0) {
                        visible = 1;
                    } else {
                        visible = 0;
                    }
                } else if (sel == 5) {
                    if (gmMainLib_8015EE44() != 0) {
                        visible = 1;
                    } else {
                        visible = 0;
                    }
                } else {
                    visible = 1;
                }
            } while (visible == 0);
            mn_804A04F0.confirmed_selection =
                data->rule_values
                    .values[mn_804A04F0.hovered_selection];
            return;
        }
        if ((u16) mn_804A04F0.hovered_selection != 5) {
            u8* bounds = mn_803ED2E8[mn_804A04F0.hovered_selection];
            if (buttons & 4) {
                lbAudioAx_80024030(2);
                if ((u8) mn_804A04F0.confirmed_selection >
                    (u8) bounds[0])
                {
                    mn_804A04F0.confirmed_selection -= 1;
                    return;
                }
                mn_804A04F0.confirmed_selection = bounds[1];
                return;
            }
            if (buttons & 8) {
                lbAudioAx_80024030(2);
                if ((u8) mn_804A04F0.confirmed_selection <
                    (u8) bounds[1])
                {
                    mn_804A04F0.confirmed_selection += 1;
                    return;
                }
                mn_804A04F0.confirmed_selection = bounds[0];
            }
        }
    }
}

/// #mn_80232458 already matched above

AnimLoopSettings* mn_80232458(u8 option, u8 value, u8 direction)
{
    u8 count;

    if (option != 1 && option != 2 && option != 3 && option != 4) {
        return NULL;
    }

    count = mn_803ED2E8[option][1];

    if (direction != 0) {
        if (value == 0) {
            return &mn_803ED270[count];
        }
        return &mn_803ED270[value - 1];
    }
    return &mn_803ED294[count - value];
}

void mn_802324E4(u8 time_limit, MenuRulesPlusData* data)
{
    JObjIndices local_indices;
    HSD_JObj** jobjs;
    HSD_JObj* jobj;
    s32 i;

    jobjs = data->x34[0];
    local_indices = mn_804DBE40;
    if (time_limit == 0) {
        for (i = 0; i < 4; i++) {
            HSD_JObjSetFlagsAll(jobjs[local_indices.idx[i]], 0x10U);
        }
        HSD_JObjReqAnimAll(jobjs[4], 1.0f);
        HSD_JObjAnimAll(jobjs[4]);
        return;
    }
    for (i = 0; i < 4; i++) {
        HSD_JObjClearFlagsAll(jobjs[local_indices.idx[i]], 0x10U);
    }
    HSD_JObjReqAnimAll(jobjs[4], mn_804D6BE4);
    HSD_JObjAnimAll(jobjs[4]);
    jobj = jobjs[2];
    HSD_JObjReqAnimAll(jobj, (f32) (u8) (time_limit / 10));
    HSD_JObjAnimAll(jobj);
    jobj = jobjs[3];
    HSD_JObjReqAnimAll(jobj, (f32) (u8) (time_limit % 10));
    HSD_JObjAnimAll(jobj);
    jobj = jobjs[5];
    HSD_JObjReqAnimAll(jobj, 0.0f);
    HSD_JObjAnimAll(jobj);
    jobj = jobjs[6];
    HSD_JObjReqAnimAll(jobj, 0.0f);
    HSD_JObjAnimAll(jobj);
}

void mn_80232660(HSD_GObj* gobj, HSD_JObj* jobj, u8 option)
{
    extern AnimLoopSettings mn_803ED294[];
    extern AnimLoopSettings mn_803ED270[];
    AnimLoopSettings* settings;
    AnimLoopSettings* p294;
    AnimLoopSettings* p270;
    f32 frame;

    if ((s32) option != 5 && (s32) option < 5 && (s32) option != 0 &&
        (s32) option >= 0)
    {
        frame = mn_8022F298(jobj);
        p294 = mn_803ED294;
        p270 = mn_803ED270;

        do {
            settings = p294;
            if (p294->start_frame <= frame && frame <= p294->end_frame) {
                break;
            }
            settings = p270;
            if (p270->start_frame <= frame && frame <= p270->end_frame) {
                break;
            }
            p294++;
            p270++;
            settings = p294;
            if (p294->start_frame <= frame && frame <= p294->end_frame) {
                break;
            }
            settings = p270;
            if (p270->start_frame <= frame && frame <= p270->end_frame) {
                break;
            }
            p294++;
            p270++;
            settings = p294;
            if (p294->start_frame <= frame && frame <= p294->end_frame) {
                break;
            }
            settings = p270;
        } while (0);

        mn_8022ED6C(jobj, settings);
    }
}

void mn_802327A4(HSD_GObj* gobj, u32 arg1, u32 arg2)
{
    u16 jobj_map[17];
    HSD_JObj* jobj_parts[17];
    HSD_JObj* option_roots[6];
    MenuRulesPlusData* data = gobj->user_data;
    u8 num_options = mn_803EB6B0[15].selection_count;
    s32 i, j, vis_count;
    s32 visible;
    HSD_JObj** root_ptr;
    u16 selected;

    jobj_map[0] = 0;
    jobj_map[1] = 1;
    jobj_map[2] = 2;
    jobj_map[3] = 3;
    jobj_map[4] = 4;
    jobj_map[5] = 5;
    jobj_map[6] = 6;
    jobj_map[7] = 7;
    jobj_map[8] = 8;
    jobj_map[9] = 9;
    jobj_map[10] = 10;
    jobj_map[11] = 11;
    jobj_map[12] = 12;
    jobj_map[13] = 13;
    jobj_map[14] = 14;
    jobj_map[15] = 15;
    {
        u16 val = 0x10;
        u16* p = jobj_map + 16;
        s32 ctr = 17 - 16;
        if (16 < 17) {
            do {
                *p = val;
                p++;
                val++;
            } while (--ctr);
        }
    }

    root_ptr = option_roots;
    i = 0;
    while (i < (s32) num_options) {
        if (gm_801A4310() == 0x1B && (u8) i == 1) {
            visible = 0;
        } else if ((u8) i == 3) {
            if (gmMainLib_8015EE0C() != 0) {
                visible = 1;
            } else {
                visible = 0;
            }
        } else if ((u8) i == 5) {
            if (gmMainLib_8015EE44() != 0) {
                visible = 1;
            } else {
                visible = 0;
            }
        } else {
            visible = 1;
        }
        if (visible != 0) {
            vis_count = 0;
            j = 0;
            while (j < (s32) (u8) i) {
                if (mn_80231F80((u8) j) != 0) {
                    vis_count++;
                }
                j++;
            }
            {
                HSD_JObj* root =
                    data->xC[mn_803ED1D0.x0[vis_count]];
                if (root != NULL) {
                    *root_ptr = root->child;
                } else {
                    *root_ptr = NULL;
                }
            }
        }
        root_ptr++;
        i++;
    }

    if ((s32) arg1 != 0) {
        u8 old_sel = data->hovered_selection;
        u8 new_sel;
        lb_8001204C(option_roots[old_sel], jobj_parts, jobj_map, 17);
        HSD_JObjSetFlagsAll(jobj_parts[16], 0x10);
        HSD_JObjSetFlagsAll(jobj_parts[13], 0x10);
        if (old_sel == 5) {
            HSD_JObjReqAnimAll(jobj_parts[2],
                               mn_803ED1D0.x7C[0].start_frame);
        } else {
            HSD_JObjReqAnimAll(jobj_parts[2],
                               mn_803ED1D0.x64[0].start_frame);
        }
        HSD_JObjAnimAll(jobj_parts[2]);
        HSD_JObjReqAnim(jobj_parts[7],
                         mn_803ED1D0.text_start_frames[old_sel * 2]);
        HSD_JObjAnim(jobj_parts[7]);
        HSD_JObjSetFlagsAll(jobj_parts[8], 0x10);
        new_sel = (u8) mn_804A04F0.hovered_selection;
        lb_8001204C(option_roots[mn_804A04F0.hovered_selection],
                     jobj_parts, jobj_map, 17);
        HSD_JObjClearFlagsAll(jobj_parts[16], 0x10);
        HSD_JObjReqAnimAll(jobj_parts[16],
                           mn_803ED1D0.x4C.start_frame);
        if (new_sel != 5) {
            HSD_JObjClearFlagsAll(jobj_parts[13], 0x10);
            HSD_JObjReqAnimAll(jobj_parts[13],
                               mn_803ED1D0.x58.start_frame);
            HSD_JObjReqAnimAll(jobj_parts[2],
                               mn_803ED1D0.x64[1].start_frame);
            HSD_JObjAnimAll(jobj_parts[2]);
        } else {
            HSD_JObjReqAnimAll(jobj_parts[2],
                               mn_803ED1D0.x7C[1].start_frame);
            HSD_JObjAnimAll(jobj_parts[2]);
        }
        HSD_JObjReqAnim(jobj_parts[7],
                         mn_803ED1D0
                             .text_start_frames[new_sel * 2 + 1]);
        HSD_JObjAnim(jobj_parts[7]);
        if (new_sel == 5) {
            HSD_JObjClearFlagsAll(jobj_parts[8], 0x10);
            HSD_JObjReqAnimAll(jobj_parts[8],
                               mn_803ED1D0.x94.start_frame);
            HSD_JObjAnimAll(jobj_parts[8]);
        }
    }

    if ((s32) arg2 != 0) {
        HSD_JObj* tree =
            data->x34[(u16) mn_804A04F0.hovered_selection][0];
        if ((s32) (u8) mn_804A04F0.hovered_selection != 5 &&
            (s32) (u8) mn_804A04F0.hovered_selection < 5)
        {
            if ((s32) (u8) mn_804A04F0.hovered_selection != 0) {
                if ((s32) (u8) mn_804A04F0.hovered_selection >= 0) {
                    if ((mn_804A04F0.buttons & 4) != 0) {
                        HSD_JObjReqAnimAll(
                            tree,
                            mn_80232458(
                                (u8) mn_804A04F0.hovered_selection,
                                mn_804A04F0.confirmed_selection, 0)
                                ->start_frame);
                    } else {
                        HSD_JObjReqAnimAll(
                            tree,
                            mn_80232458(
                                (u8) mn_804A04F0.hovered_selection,
                                mn_804A04F0.confirmed_selection, 1)
                                ->start_frame);
                    }
                    HSD_JObjAnimAll(tree);
                }
            } else {
                mn_802324E4(mn_804A04F0.confirmed_selection,
                            (MenuRulesPlusData*) gobj->user_data);
            }
        }
    }

    if ((s32) arg1 != 0) {
        selected = mn_804A04F0.hovered_selection;
    } else {
        selected = (u16) data->hovered_selection;
    }

    root_ptr = option_roots;
    i = 0;
    while (i < (s32) num_options) {
        if (gm_801A4310() == 0x1B && (u8) i == 1) {
            visible = 0;
        } else if ((u8) i == 3) {
            if (gmMainLib_8015EE0C() != 0) {
                visible = 1;
            } else {
                visible = 0;
            }
        } else if ((u8) i == 5) {
            if (gmMainLib_8015EE44() != 0) {
                visible = 1;
            } else {
                visible = 0;
            }
        } else {
            visible = 1;
        }
        if (visible != 0) {
            AnimLoopSettings* als;
            lb_8001204C(*root_ptr, jobj_parts, jobj_map, 17);
            if (i == (s32) (u8) selected) {
                mn_8022ED6C(jobj_parts[16], &mn_803ED1D0.x4C);
            }
            if (i == (s32) (u8) selected && i != 5) {
                mn_8022ED6C(jobj_parts[13], &mn_803ED1D0.x58);
            }
            if (i == 5) {
                als = &mn_803ED1D0.x7C[(u8) selected == (u8) i];
            } else {
                als = &mn_803ED1D0.x64[(u8) selected == (u8) i];
            }
            mn_8022ED6C(jobj_parts[2], als);
            mn_8022ED6C(jobj_parts[8], &mn_803ED1D0.x94);
            mn_80232660(gobj, data->x34[i][0], (u8) i);
        }
        root_ptr++;
        i++;
    }
}

void mn_80232D4C(HSD_GObj* gobj, u32 arg1, u32 arg2)
{
    MenuRulesPlusData* data = gobj->user_data;
    u16 selection;
    u8 confirmed;
    u8 desc_idx;
    HSD_Text* text;

    if ((s32) arg1 != 0) {
        selection = mn_804A04F0.hovered_selection;
    } else {
        selection = (u16) data->hovered_selection;
    }

    switch ((s32) data->state) {
    case 4:
        text = data->description;
        if (text != NULL) {
            HSD_SisLib_803A5CC4(text);
            data->description = NULL;
            return;
        }
    case 5:
        return;
    case 3:
    case 1:
        text = data->description;
        if (text == NULL) {
            confirmed = mn_804A04F0.confirmed_selection;
            if (text != NULL) {
                HSD_SisLib_803A5CC4(text);
                data->description = NULL;
            }
            if ((s32) (u8) selection == 0 || (s32) (u8) selection == 5) {
                desc_idx = mn_803ED2E8[(u8) selection][0];
            } else {
                desc_idx = mn_803ED2E8[(u8) selection][confirmed];
            }
            text = HSD_SisLib_803A5ACC(0, 1, -9.5f, 8.0f, 17.0f,
                                       364.68332f, 76.77544f);
            data->description = text;
            text->font_size.x = 0.0521f;
            text->font_size.y = 0.0521f;
            HSD_SisLib_803A6368(text, (s32) desc_idx);
            return;
        }
        break;
    case 0:
        if ((s32) arg1 != 0 ||
            ((s32) arg2 != 0 && (u8) selection != 0 &&
             (u8) selection != 5))
        {
            text = data->description;
            confirmed = mn_804A04F0.confirmed_selection;
            if (text != NULL) {
                HSD_SisLib_803A5CC4(text);
                data->description = NULL;
            }
            if ((s32) (u8) selection == 0 || (s32) (u8) selection == 5) {
                desc_idx = mn_803ED2E8[(u8) selection][0];
            } else {
                desc_idx = mn_803ED2E8[(u8) selection][confirmed];
            }
            text = HSD_SisLib_803A5ACC(0, 1, -9.5f, 8.0f, 17.0f,
                                       364.68332f, 76.77544f);
            data->description = text;
            text->font_size.x = 0.0521f;
            text->font_size.y = 0.0521f;
            HSD_SisLib_803A6368(text, (s32) desc_idx);
        }
        break;
    }
}

void fn_80232F44(HSD_GObj* gobj)
{
    MenuRulesPlusData* data = gobj->user_data;
    AnimLoopSettings* anim_settings;
    s32 menu_changed = 0;
    u32 selection_changed = 0;
    u32 value_changed = 0;
    MenuRulesPlusData* data2;
    u8 val;
    u8 state;
    HSD_JObj* jobj;

    state = data->state;
    if ((state == 0 || state == 1 || state == 3) &&
        (u8) data->menu_kind != (u8) mn_804A04F0.cur_menu)
    {
        if ((u8) mn_804A04F0.entering_menu != 0) {
            data->state = 4;
        } else {
            data->state = 2;
        }
        state = data->state;
        jobj = data->xC[2];
        switch ((s32) state) {
        case 1:
            anim_settings = &mn_803ED294[3];
            break;
        case 2:
            anim_settings = &mn_803ED294[5];
            break;
        case 3:
            anim_settings = &mn_803ED294[4];
            break;
        case 4:
            anim_settings = &mn_803ED294[6];
            break;
        }
        HSD_JObjReqAnim(jobj, anim_settings->start_frame);
        HSD_JObjAnim(jobj);
        state = data->state;
        if (state == 0 || state == 1 || state == 3) {
            menu_changed = 1;
            selection_changed = 1;
            value_changed = 1;
        }
    }

    state = data->state;
    if (state != 0) {
        jobj = data->xC[2];
        switch ((s32) state) {
        case 1:
            anim_settings = &mn_803ED294[3];
            break;
        case 2:
            anim_settings = &mn_803ED294[5];
            break;
        case 3:
            anim_settings = &mn_803ED294[4];
            break;
        case 4:
            anim_settings = &mn_803ED294[6];
            break;
        }
        if (mn_8022F298(jobj) >= anim_settings->end_frame) {
            state = data->state;
            switch ((s32) state) {
            case 3:
            case 1:
                data->state = 0;
                break;
            case 2:
            case 4:
                HSD_GObjPLink_80390228(gobj);
                return;
            }
        }
        HSD_JObjAnim(jobj);
    }
    state = data->state;
    if (state == 0 || state == 1 || state == 3) {
        if ((s32) data->hovered_selection !=
            (s32) mn_804A04F0.hovered_selection)
        {
            selection_changed = 1;
        }
        if (data->rule_values
                .values[mn_804A04F0.hovered_selection] !=
            (u8) mn_804A04F0.confirmed_selection)
        {
            value_changed = 1;
        }
    }
    mn_802327A4(gobj, selection_changed, value_changed);
    mn_80232D4C(gobj, selection_changed, value_changed);
    if (menu_changed != 0) {
        data->menu_kind = (u8) mn_804A04F0.cur_menu;
    }
    if ((s32) selection_changed != 0) {
        data->hovered_selection = (u8) mn_804A04F0.hovered_selection;
    }
    if ((s32) value_changed != 0) {
        data->rule_values.values[data->hovered_selection] =
            (u8) mn_804A04F0.confirmed_selection;
        data2 = gobj->user_data;
        val = data2->rule_values.time_limit;
        gmMainLib_8015CC34()->stock_time_limit = val;
        val = data2->rule_values.friendly_fire;
        gmMainLib_8015CC34()->friendly_fire = val;
        val = data2->rule_values.pause;
        gmMainLib_8015CC34()->pause = val;
        val = data2->rule_values.score;
        gmMainLib_8015CC34()->score_display = val;
        val = data2->rule_values.sd_penalty;
        gmMainLib_8015CC34()->unk_xc = val;
    }
}

HSD_GObj* mn_80233218(MenuState state)
{
    u16 jobj_map[17];
    HSD_JObj* jobj_parts[17];
    HSD_GObj* gobj;
    MenuRulesPlusData* data;
    u8 num_options;
    u8 selected;
    u8 confirmed;
    s32 i, j;
    s32 vis_before;
    s32 vis_total;
    s32 visible;
    HSD_JObj* root_jobj;
    HSD_JObj* option_jobj;
    HSD_JObj* cursor_jobj;
    HSD_JObj* value_jobj;
    StaticModelDesc* desc;
    AnimLoopSettings* als;
    f32* frame_ptr;
    u16* sub_count_ptr;
    GameRules* rules;

    jobj_map[0] = 0;
    jobj_map[1] = 1;
    jobj_map[2] = 2;
    jobj_map[3] = 3;
    jobj_map[4] = 4;
    jobj_map[5] = 5;
    jobj_map[6] = 6;
    jobj_map[7] = 7;
    jobj_map[8] = 8;
    jobj_map[9] = 9;
    jobj_map[10] = 10;
    jobj_map[11] = 11;
    jobj_map[12] = 12;
    jobj_map[13] = 13;
    jobj_map[14] = 14;
    jobj_map[15] = 15;
    for (i = 16; i < 17; i++) {
        jobj_map[i] = (u16) i;
    }

    selected = (u8) mn_804A04F0.hovered_selection;
    num_options = mn_803EB6B0[15].selection_count;

    gobj = GObj_Create(6, 7, 0x80);
    mn_804D6BE0 = gobj;
    root_jobj = HSD_JObjLoadJoint(MenMainConRl_Top.joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, root_jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 4, 0x80);
    HSD_GObj_SetupProc(gobj, fn_80232F44, 0);
    HSD_JObjAddAnimAll(root_jobj, MenMainConRl_Top.animjoint,
                       MenMainConRl_Top.matanim_joint,
                       MenMainConRl_Top.shapeanim_joint);
    HSD_JObjReqAnimAll(root_jobj, 0.0f);
    HSD_JObjAnimAll(root_jobj);

    data = HSD_MemAlloc(sizeof(MenuRulesPlusData));
    if (data == NULL) {
        OSReport("Can't get user_data.\n");
        __assert("mnruleplus.c", 0x3DFU, "user_data");
    }
    GObj_InitUserData(gobj, 0, HSD_Free, data);
    data->menu_kind = mn_804A04F0.cur_menu;
    data->hovered_selection = (u8) mn_804A04F0.hovered_selection;
    data->rule_values.time_limit = gmMainLib_8015CC34()->stock_time_limit;
    data->rule_values.friendly_fire = gmMainLib_8015CC34()->friendly_fire;
    data->rule_values.pause = gmMainLib_8015CC34()->pause;
    data->rule_values.score = gmMainLib_8015CC34()->score_display;
    rules = gmMainLib_8015CC34();
    data->rule_values.sd_penalty = rules->unk_xc;
    data->state = (u8) state;
    data->description = NULL;

    for (i = 0; i < 10; i++) {
        lb_80011E24(root_jobj, &data->xC[i], i, -1);
    }

    mn_804A04F0.confirmed_selection =
        data->rule_values.values[data->hovered_selection];

    if ((u8) state != 0) {
        HSD_JObj* anim_jobj = data->xC[2];
        switch ((s32) data->state) {
        case 2:
            break;
        case 1:
            als = &mn_803ED294[3];
            break;
        case 3:
            als = &mn_803ED294[4];
            break;
        }
        HSD_JObjReqAnim(anim_jobj, als->start_frame);
        HSD_JObjAnim(anim_jobj);
    }

    frame_ptr = mn_803ED1D0.text_start_frames;
    sub_count_ptr = &mn_803ED1D0.xE[1];
    i = 0;
    while (i < (s32) num_options) {
        vis_before = 0;
        j = vis_before;
        while (j < (s32) (u8) i) {
            if (mn_80231F80((u8) j) != 0) {
                vis_before++;
            }
            j++;
        }

        vis_total = 0;
        option_jobj = data->xC[mn_803ED1D0.x0[(u8) vis_before]];
        j = vis_total;
        do {
            if (mn_80231F80((u8) j) != 0) {
                vis_total++;
            }
            j++;
        } while ((s32) (u8) j < 6);

        HSD_JObjReqAnim(option_jobj, (f32) vis_total);
        HSD_JObjAnim(option_jobj);

        if ((gm_801A4310() == 0x1B) && ((u8) i == 1)) {
            visible = 0;
        } else if ((u8) i == 3) {
            if (gmMainLib_8015EE0C() != 0) {
                visible = 1;
            } else {
                visible = 0;
            }
        } else if ((u8) i == 5) {
            if (gmMainLib_8015EE44() != 0) {
                visible = 1;
            } else {
                visible = 0;
            }
        } else {
            visible = 1;
        }

        if (visible != 0) {
            desc = &MenMainCursorRl_Top;
            cursor_jobj = HSD_JObjLoadJoint(MenMainCursorRl_Top.joint);
            HSD_JObjAddAnimAll(cursor_jobj, MenMainCursorRl_Top.animjoint,
                               MenMainCursorRl_Top.matanim_joint,
                               MenMainCursorRl_Top.shapeanim_joint);
            HSD_JObjReqAnimAll(cursor_jobj, 0.0f);
            HSD_JObjAnimAll(cursor_jobj);

            lb_8001204C(cursor_jobj, jobj_parts, jobj_map, 17);

            HSD_JObjReqAnim(jobj_parts[7],
                            frame_ptr[(s32) selected == i]);
            HSD_JObjAnim(jobj_parts[7]);

            if ((s32) selected != i) {
                HSD_JObjSetFlagsAll(jobj_parts[16], 0x10);
            }

            if (((s32) selected != i) || (i == 5)) {
                HSD_JObjSetFlagsAll(jobj_parts[13], 0x10);
            } else {
                HSD_JObjReqAnimAll(jobj_parts[13],
                                   mn_803ED1D0.x58.start_frame);
            }

            if (((s32) selected != i) || (i != 5)) {
                HSD_JObjSetFlagsAll(jobj_parts[8], 0x10);
            }

            if (i == 5) {
                als = &mn_803ED1D0.x7C[(u8) selected == (u8) i];
            } else {
                als = &mn_803ED1D0.x64[(u8) selected == (u8) i];
            }
            HSD_JObjReqAnimAll(jobj_parts[2], als->start_frame);
            HSD_JObjAnimAll(jobj_parts[2]);
            HSD_JObjAddChild(option_jobj, cursor_jobj);

            if (i != 5) {
                switch (i) {
                case 0:
                    desc = &MenMainCursorTr01_Top;
                    break;
                case 1:
                    desc = &MenMainCursorTr02_Top;
                    break;
                default:
                    desc = &MenMainCursorTr03_Top;
                    break;
                case 4:
                    desc = &MenMainCursorTr04_Top;
                    break;
                }

                value_jobj = HSD_JObjLoadJoint(desc->joint);
                HSD_JObjAddAnimAll(value_jobj, desc->animjoint,
                                   desc->matanim_joint,
                                   desc->shapeanim_joint);
                HSD_JObjReqAnimAll(value_jobj, 0.0f);
                HSD_JObjAnimAll(value_jobj);

                j = 0;
                while (j < (s32) *sub_count_ptr) {
                    lb_80011E24(value_jobj, &data->x34[i][j],
                                j, -1);
                    j++;
                }

                if (i != 0) {
                    if (i >= 0 && i < 5) {
                        u8 val = data->rule_values.values[i];
                        AnimLoopSettings* val_als;
                        if ((u8) i != 1 && (u8) i != 2 &&
                            (u8) i != 3 && (u8) i != 4)
                        {
                            val_als = NULL;
                        } else if (val == 0) {
                            val_als =
                                &mn_803ED270[mn_803ED2E8[i][1]];
                        } else {
                            val_als = &mn_803ED270[val - 1];
                        }
                        HSD_JObjReqAnimAll(value_jobj,
                                           val_als->start_frame);
                        HSD_JObjAnimAll(value_jobj);
                    }
                } else {
                    JObjIndices digit_indices = mn_804DBE48;
                    j = 0;
                    do {
                        HSD_JObj* num_jobj =
                            HSD_JObjLoadJoint(MenMainNmRl_Top.joint);
                        HSD_JObjAddAnimAll(num_jobj,
                                           MenMainNmRl_Top.animjoint,
                                           MenMainNmRl_Top.matanim_joint,
                                           MenMainNmRl_Top.shapeanim_joint);
                        HSD_JObjAddChild(
                            data->x34[0][digit_indices.idx[j]], num_jobj);
                        j++;
                    } while (j < 4);
                    mn_802324E4(data->rule_values.time_limit, data);
                }

                HSD_JObjAddChild(option_jobj, value_jobj);
            }
        }
        frame_ptr += 2;
        sub_count_ptr++;
        i++;
    }

    {
        HSD_Text* text = data->description;
        u8 desc_idx;
        confirmed = mn_804A04F0.confirmed_selection;
        if (text != NULL) {
            HSD_SisLib_803A5CC4(text);
            data->description = NULL;
        }
        if ((s32) selected == 0 || (s32) selected == 5) {
            desc_idx = mn_803ED2E8[selected][0];
        } else {
            desc_idx = mn_803ED2E8[selected][confirmed];
        }
        text = HSD_SisLib_803A5ACC(0, 1, -9.5f, 8.0f, 17.0f, 364.68332f,
                                   76.77544f);
        data->description = text;
        text->font_size.x = 0.0521f;
        text->font_size.y = 0.0521f;
        HSD_SisLib_803A6368(text, (s32) desc_idx);
    }

    return gobj;
}

void mn_802339FC(void)
{
    MenuState state;
    HSD_GObjProc* think;

    mn_804A04F0.prev_menu = mn_804A04F0.cur_menu;

    switch (mn_804A04F0.prev_menu) {
    case MENU_KIND_RULES_STAGE:
        mn_804A04F0.cur_menu = MENU_KIND_RULES_EXTRA;
        state = MENU_STATE_EXIT_TO;
        mn_804A04F0.hovered_selection = 5;
        break;
    default:
        mn_804A04F0.cur_menu = MENU_KIND_RULES_EXTRA;
        state = MENU_STATE_ENTER_TO;
        mn_804A04F0.hovered_selection = 0;
        break;
    }

    mn_80233218(state);
    think = HSD_GObj_SetupProc(GObj_Create(0U, 1U, 0x80U),
                               (void (*)(HSD_GObj*)) fn_8023201C, 0U);
    think->flags_3 = HSD_GObj_804D783C;
}
