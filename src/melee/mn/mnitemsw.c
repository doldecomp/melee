#include "mnitemsw.h"

#include "baselib/gobjgxlink.h"
#include "baselib/gobjobject.h"
#include "mn/inlines.h"
#include "mn/mnmain.h"

#include <baselib/gobj.h>
#include <baselib/gobjplink.h>
#include <baselib/gobjproc.h>
#include <baselib/jobj.h>
#include <baselib/sislib.h>
#include <sysdolphin/baselib/debug.h>
#include <sysdolphin/baselib/gobjuserdata.h>
#include <sysdolphin/baselib/memory.h>
#include <melee/gm/gm_1601.h>
#include <melee/gm/gm_1A3F.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/lb/lb_00F9.h>
#include <melee/lb/lbcardgame.h>
#include <melee/lb/lblanguage.h>
#include <melee/mn/mnmainrule.h>
#include <melee/sc/types.h>

extern StaticModelDesc MenMainCursorIs_Top;
extern StaticModelDesc MenMainConIs_Top;
extern HSD_GObj* mnItemSw_804D6BE8;
extern u8 mn_804D6BB5;

struct MnItemSwTable {
    /* 0x00 */ f32 x00[4][3];
    /* 0x30 */ f32 x30[18];
    /* 0x78 */ f32 items[32];
    /* 0xF8 */ u8 item_order[32];
};

static struct MnItemSwTable mnItemSw_803ED340 = {
    /* x00 */
    {
        { 0.0f, 9.0f, -0.1f },
        { 0.0f, 0.0f, -0.1f },
        { 0.0f, 0.0f, -0.1f },
        { 0.0f, 0.0f, -0.1f },
    },
    /* x30 */
    {
        0.0f,
        10.0f,
        -0.1f,
        0.0f,
        199.0f,
        0.0f,
        10.0f,
        11.0f,
        8.0f,
        9.0f,
        6.0f,
        7.0f,
        4.0f,
        5.0f,
        2.0f,
        3.0f,
        0.0f,
        1.0f,
    },
    /* items */
    {
        0.0f,  1.0f,  2.0f,  3.0f,  4.0f,  5.0f,  6.0f,  7.0f,
        8.0f,  9.0f,  10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f,
        16.0f, 17.0f, 18.0f, 19.0f, 20.0f, 21.0f, 22.0f, 23.0f,
        25.0f, 24.0f, 26.0f, 27.0f, 29.0f, 28.0f, 30.0f, 31.0f,
    },
    /* item_order */
    {
        0x05, 0x12, 0x0A, 0x1E, 0x0D, 0x18, 0x03, 0x0E, 0x17, 0x1B, 0x01,
        0x09, 0x08, 0x07, 0x15, 0x04, 0x06, 0x02, 0x0F, 0x00, 0x11, 0x0B,
        0x1F, 0x1A, 0x14, 0x19, 0x10, 0x16, 0x13, 0x1D, 0x0C, 0x00,
    },
};

static f32 mnItemSw_804D4BA0[2] = { 0.0f, 1.0f };

#pragma dont_inline on
s32 mnItemSw_80233A98(s32 arg0)
{
    switch (arg0) {
    case 19:
        if (lbLang_IsSettingJP()) {
            return (s32) mnItemSw_803ED340.items[arg0];
        }
        return 0x27;
    case 17:
        if (lbLang_IsSettingJP()) {
            return (s32) mnItemSw_803ED340.items[arg0];
        }
        return 0x28;
    case 18:
    default:
        return (s32) mnItemSw_803ED340.items[arg0];
    }
}
#pragma dont_inline reset

void mnItemSw_80233B68(MnItemSwData* arg0, u32 arg1)
{
    s32 temp_r0;
    u8 var_r0;
    u8 var_r0_2;
    u16* hovered = &mn_804A04F0.hovered_selection;
    u8 sel = (u8) *hovered;

    if (arg1 & 1) {
        switch ((s32) sel) {
        case 0:
            *hovered = 0x1F;
            break;
        case 16:
            *hovered = 0x20;
            break;
        case 31:
            *hovered = 0xF;
            break;
        case 32:
            *hovered = 0x1E;
            break;
        default:
            *hovered = sel - 1;
            break;
        }
        if (((u8) *hovered == 0x1F) || ((u8) *hovered == 0x20)) {
            mn_804A04F0.confirmed_selection = arg0->x21;
            return;
        }
        mn_804A04F0.confirmed_selection = arg0->items[(u8) *hovered];
        return;
    }
    if (arg1 & 2) {
        switch ((s32) sel) {
        case 15:
            *hovered = 0x1F;
            break;
        case 30:
            *hovered = 0x20;
            break;
        case 31:
            *hovered = 0;
            break;
        case 32:
            *hovered = 0x10;
            break;
        default:
            *hovered = sel + 1;
            break;
        }
        if (((u8) *hovered == 0x1F) || ((u8) *hovered == 0x20)) {
            mn_804A04F0.confirmed_selection = arg0->x21;
            return;
        }
        mn_804A04F0.confirmed_selection = arg0->items[(u8) *hovered];
        return;
    }
    if (arg1 & 4) {
        if ((u8) (sel - 0x1F) <= 1U) {
            if ((u8) mn_804A04F0.confirmed_selection == 5) {
                var_r0 = 0;
            } else {
                var_r0 = mn_804A04F0.confirmed_selection + 1;
            }
            mn_804A04F0.confirmed_selection = var_r0;
            return;
        }
        if ((sel >= 0x10U) && (sel < 0x1FU)) {
            *hovered = sel - 0x10;
            if (((u8) *hovered == 0x1F) || ((u8) *hovered == 0x20)) {
                mn_804A04F0.confirmed_selection = arg0->x21;
                return;
            }
            mn_804A04F0.confirmed_selection = arg0->items[(u8) *hovered];
        }
    } else if (arg1 & 8) {
        if ((u8) (sel - 0x1F) <= 1U) {
            if ((u8) mn_804A04F0.confirmed_selection == 0) {
                var_r0_2 = 5;
            } else {
                var_r0_2 = mn_804A04F0.confirmed_selection - 1;
            }
            mn_804A04F0.confirmed_selection = var_r0_2;
            return;
        }
        if (sel < 0x10U) {
            temp_r0 = sel + 0x10;
            if (temp_r0 >= 0x1F) {
                *hovered = 0x1E;
            } else {
                *hovered = (u16) temp_r0;
            }
            if (((u8) *hovered == 0x1F) || ((u8) *hovered == 0x20)) {
                mn_804A04F0.confirmed_selection = arg0->x21;
                return;
            }
            mn_804A04F0.confirmed_selection = arg0->items[(u8) *hovered];
        }
    }
}

void fn_80233E10(HSD_GObj* gobj)
{
    MnItemSwData* data;
    u32 buttons;
    s32 i;

    PAD_STACK(0x20);

    data = (MnItemSwData*) mnItemSw_804D6BE8->user_data;
    buttons = mn_80229624(4);
    mn_804A04F0.buttons = buttons;
    i = 0;

    if (buttons & MenuInput_Back) {
        sfxBack();
        mn_804A04F0.entering_menu = 0;
        data = (MnItemSwData*) mnItemSw_804D6BE8->user_data;
        for (i = 0; i < 0x1F; i++) {
            mn_8022E978(mnItemSw_803ED340.item_order[i], data->items[i]);
        }
        gmMainLib_8015CC58()->item_freq = data->x21 - 1;
        lb_8001CE00();
        mn_804D6BC8.cooldown = 5;
        mn_8023164C();
        HSD_GObjPLink_80390228(gobj);
        return;
    }

    if (mnItemSw_804D6BEC != 0) {
        return;
    }

    if (buttons & MenuInput_AButton) {
        if (mn_804A04F0.hovered_selection < 0x1Fu) {
            sfxMove();
            if (mn_804A04F0.confirmed_selection != 0) {
            } else {
                i = 1;
            }
            mn_804A04F0.confirmed_selection = (u8) i;
            data = (MnItemSwData*) mnItemSw_804D6BE8->user_data;
            for (i = 0; i < 0x1F; i++) {
                mn_8022E978(mnItemSw_803ED340.item_order[i], data->items[i]);
            }
            gmMainLib_8015CC58()->item_freq = data->x21 - 1;
            return;
        }
    } else if (buttons & MenuInput_StartButton) {
        sfxForward();
        if ((s32) gm_801A4310() == 1) {
            data = (MnItemSwData*) mnItemSw_804D6BE8->user_data;
            for (i = 0; i < 0x1F; i++) {
                mn_8022E978(mnItemSw_803ED340.item_order[i], data->items[i]);
            }
            gmMainLib_8015CC58()->item_freq = data->x21 - 1;
            lb_8001CE00();
            mn_80229860(2);
            return;
        }
        data = (MnItemSwData*) mnItemSw_804D6BE8->user_data;
        for (i = 0; i < 0x1F; i++) {
            mn_8022E978(mnItemSw_803ED340.item_order[i], data->items[i]);
        }
        gmMainLib_8015CC58()->item_freq = data->x21 - 1;
        lb_8001CE00();
        mn_8022F4CC();
        return;
    }

    if (buttons & 0xF) {
        s32 old_hovered = (s32) mn_804A04F0.hovered_selection;
        s32 old_confirmed = (s32) mn_804A04F0.confirmed_selection;
        mnItemSw_80233B68(data, buttons);
        if (old_hovered != (s32) mn_804A04F0.hovered_selection ||
            old_confirmed != (s32) mn_804A04F0.confirmed_selection)
        {
            sfxMove();
        }
    }
}

HSD_JObj* mnItemSw_8023405C(MnItemSwData* data, u8 idx)
{
    HSD_JObj* cur;
    u8 i;

    if (idx >= 16) {
        cur = HSD_JObjGetChild(data->jobjs[6]);
        for (i = 16; i < idx; i++) {
            cur = HSD_JObjGetNext(cur);
        }
    } else {
        if (data->jobjs[4] == NULL) {
            cur = NULL;
        } else {
            cur = data->jobjs[4]->child;
        }
        for (i = 0; i < idx; i++) {
            cur = HSD_JObjGetNext(cur);
        }
    }
    return cur;
}

void mnItemSw_80234104(HSD_GObj* gobj)
{
    HSD_JObj* sp38;
    u8* order;
    s32 i;
    u8 cursor;
    HSD_JObj* cjobj;
    f32 y_spacing;
    MnItemSwData* data = gobj->user_data;

    HSD_JObjClearFlagsAll(data->jobjs[4], 0x10);
    HSD_JObjClearFlagsAll(data->jobjs[6], 0x10);

    order = mnItemSw_803ED340.item_order;
    for (i = 0; i < 0x1F; i++, order++) {
        HSD_JObj* jobj = mnItemSw_8023405C(data, i);

        if (i != (s32) data->cursor) {
            lb_80011E24(jobj, &sp38, 8, -1);
            HSD_JObjSetFlagsAll(sp38, 0x10);
        }

        lb_80011E24(jobj, &sp38, 3, -1);
        HSD_JObjReqAnimAll(sp38, (f32) mnItemSw_80233A98((s32) *order));
        HSD_JObjAnimAll(sp38);
        HSD_JObjReqAnimAll(sp38, mnItemSw_803ED340.x30[0]);
        mn_8022F3D8(sp38, 1, TOBJ_MASK);
        HSD_JObjAnimAll(sp38);
    }

    cursor = data->cursor;
    cjobj = data->jobjs[2];

    if (cursor == 0x1F || cursor == 0x20) {
        HSD_JObjSetFlagsAll(cjobj, 0x10);
    } else {
        HSD_JObjClearFlagsAll(cjobj, 0x10);
        y_spacing = HSD_JObjGetTranslationY(data->jobjs[5]) -
                    HSD_JObjGetTranslationY(data->jobjs[4]);

        if (cursor < 0x10) {
            HSD_JObjSetTranslateX(cjobj,
                                  HSD_JObjGetTranslationX(data->jobjs[4]));
            HSD_JObjSetTranslateY(cjobj,
                                  y_spacing * (f32) cursor +
                                      HSD_JObjGetTranslationY(data->jobjs[4]));
        } else {
            HSD_JObjSetTranslateX(cjobj,
                                  HSD_JObjGetTranslationX(data->jobjs[6]));
            HSD_JObjSetTranslateY(cjobj,
                                  y_spacing * (f32) (cursor - 0x10) +
                                      HSD_JObjGetTranslationY(data->jobjs[4]));
        }
    }

    HSD_JObjClearFlagsAll(data->jobjs[3], 0x10);
}

void mnItemSw_8023453C(HSD_GObj* gobj, u8 arg1, u8 arg2)
{
    s32 sp40;
    HSD_JObj* sp44;
    HSD_JObj* sp3C;
    f32 anim_val;
    u8 new_cursor;
    HSD_JObj* cjobj;
    MnItemSwData* data = gobj->user_data;
    struct MnItemSwTable* tbl = &mnItemSw_803ED340;

    if (arg1 != 0) {
        u8 old_cursor = data->cursor;

        if (old_cursor == 0x1F || old_cursor == 0x20) {
            u8 x21 = data->x21;
            HSD_JObj* all_jobj = data->jobjs[3];
            if ((u8) mn_804A04F0.hovered_selection == 0x1F ||
                (u8) mn_804A04F0.hovered_selection == 0x20)
            {
                HSD_JObjReqAnimAll(all_jobj, tbl->x30[7 + x21 * 2]);
            } else {
                HSD_JObjReqAnimAll(all_jobj, tbl->x30[6 + x21 * 2]);
            }
            HSD_JObjAnimAll(all_jobj);
        } else {
            HSD_JObj* jobj = mnItemSw_8023405C(data, old_cursor);
            lb_80011E24(jobj, &sp44, 8, -1);
            HSD_JObjSetFlagsAll(sp44, 0x10);
            anim_val = mn_8022F298(sp44);
            lb_80011E24(jobj, &sp44, 3, -1);
            HSD_JObjReqAnimAll(sp44, (f32) mnItemSw_80233A98(
                                         (s32) tbl->item_order[old_cursor]));
            HSD_JObjAnimAll(sp44);
            HSD_JObjReqAnimAll(sp44, tbl->x30[0]);
            mn_8022F3D8(sp44, 1, TOBJ_MASK);
            HSD_JObjAnimAll(sp44);
        }

        new_cursor = (u8) mn_804A04F0.hovered_selection;

        if (new_cursor == 0x1F || new_cursor == 0x20) {
            HSD_JObj* all_jobj = data->jobjs[3];
            u8 conf = mn_804A04F0.confirmed_selection;
            if ((u8) mn_804A04F0.hovered_selection == 0x1F ||
                (u8) mn_804A04F0.hovered_selection == 0x20)
            {
                HSD_JObjReqAnimAll(all_jobj, tbl->x30[7 + conf * 2]);
            } else {
                HSD_JObjReqAnimAll(all_jobj, tbl->x30[6 + conf * 2]);
            }
            HSD_JObjAnimAll(all_jobj);
        } else {
            HSD_JObj* jobj = mnItemSw_8023405C(data, new_cursor);
            lb_80011E24(jobj, &sp44, 8, -1);
            HSD_JObjClearFlagsAll(sp44, 0x10);
            HSD_JObjReqAnimAll(sp44, anim_val);
            HSD_JObjAnimAll(sp44);
            lb_80011E24(jobj, &sp44, 3, -1);
            HSD_JObjReqAnimAll(sp44, (f32) mnItemSw_80233A98(
                                         (s32) tbl->item_order[new_cursor]));
            HSD_JObjAnimAll(sp44);
            HSD_JObjReqAnimAll(sp44, tbl->x30[0]);
            mn_8022F3D8(sp44, 1, TOBJ_MASK);
            HSD_JObjAnimAll(sp44);
        }

        cjobj = data->jobjs[2];
        if ((u8) (new_cursor - 0x1F) <= 1U) {
            HSD_JObjSetFlagsAll(cjobj, 0x10);
        } else {
            f32 y_spacing;
            HSD_JObjClearFlagsAll(cjobj, 0x10);
            y_spacing = HSD_JObjGetTranslationY(data->jobjs[5]) -
                        HSD_JObjGetTranslationY(data->jobjs[4]);

            if (new_cursor < 0x10) {
                HSD_JObjSetTranslateX(cjobj,
                                      HSD_JObjGetTranslationX(data->jobjs[4]));
                HSD_JObjSetTranslateY(
                    cjobj, y_spacing * (f32) new_cursor +
                               HSD_JObjGetTranslationY(data->jobjs[4]));
            } else {
                HSD_JObjSetTranslateX(cjobj,
                                      HSD_JObjGetTranslationX(data->jobjs[6]));
                HSD_JObjSetTranslateY(
                    cjobj, y_spacing * (f32) (new_cursor - 0x10) +
                               HSD_JObjGetTranslationY(data->jobjs[4]));
            }
        }
    }

    if (arg2 != 0) {
        if (mn_804A04F0.hovered_selection == 0x1F ||
            mn_804A04F0.hovered_selection == 0x20)
        {
            HSD_JObj* all_jobj = data->jobjs[3];
            u8 conf = mn_804A04F0.confirmed_selection;
            if ((u8) mn_804A04F0.hovered_selection == 0x1F ||
                (u8) mn_804A04F0.hovered_selection == 0x20)
            {
                HSD_JObjReqAnimAll(all_jobj, tbl->x30[7 + conf * 2]);
            } else {
                HSD_JObjReqAnimAll(all_jobj, tbl->x30[6 + conf * 2]);
            }
            HSD_JObjAnimAll(all_jobj);
        } else {
            u8 confirmed = mn_804A04F0.confirmed_selection;
            HSD_JObj* jobj =
                mnItemSw_8023405C(data, (u8) mn_804A04F0.hovered_selection);
            lb_80011E24(jobj, &sp3C, 2, -1);
            HSD_JObjReqAnimAll(sp3C, mnItemSw_804D4BA0[confirmed]);
            HSD_JObjAnimAll(sp3C);
        }
    }

    {
        u16 sel;
        if (arg1 != 0) {
            sel = mn_804A04F0.hovered_selection;
        } else {
            sel = data->cursor;
        }

        if ((u8) sel != 0x1F && (u8) sel != 0x20) {
            HSD_JObj* jobj = mnItemSw_8023405C(data, (u8) sel);
            lb_80011E24(jobj, &sp44, 8, -1);
            mn_8022ED6C(sp44, (AnimLoopSettings*) &tbl->x30[3]);
            lb_80011E24(jobj, &sp44, 3, -1);
            mn_8022ED6C(sp44, (AnimLoopSettings*) &tbl->x30[0]);
        }
    }
}

void fn_80234C24(HSD_GObj* gobj)
{
    MnItemSwData* data;
    struct MnItemSwTable* tbl = &mnItemSw_803ED340;
    f32* anims;
    HSD_JObj* jobj;
    HSD_Text* text;
    s32 menu_changed;
    s32 hovered_changed;
    s32 confirmed_changed;

    PAD_STACK(0x18);

    menu_changed = 0;
    hovered_changed = 0;
    confirmed_changed = 0;
    data = (MnItemSwData*) gobj->user_data;

    {
        u8 state = data->x23;
        if ((state == 0 || state == 1 || state == 3) &&
            data->menu_kind != (u8) mn_804A04F0.cur_menu)
        {
            if ((u8) mn_804A04F0.entering_menu != 0) {
                data->x23 = 4;
            } else if ((mn_804A04F0.buttons & 0x20) != 0) {
                data->x23 = 2;
            }

            state = data->x23;
            jobj = data->jobjs[1];

            switch ((s32) state) {
            case 1:
                anims = tbl->x00[0];
                break;
            case 2:
                anims = tbl->x00[2];
                break;
            case 3:
                anims = tbl->x00[1];
                break;
            case 4:
                anims = tbl->x00[3];
                break;
            }

            HSD_JObjReqAnim(jobj, anims[0]);
            HSD_JObjAnim(jobj);

            state = data->x23;
            if (state == 0 || state == 1 || state == 3) {
                menu_changed = 1;
                hovered_changed = 1;
                confirmed_changed = 1;
            }
        }
    }

    {
        u8 state = data->x23;
        if (state != 0) {
            jobj = data->jobjs[1];

            switch ((s32) state) {
            case 1:
                anims = tbl->x00[0];
                break;
            case 2:
                anims = tbl->x00[2];
                break;
            case 3:
                anims = tbl->x00[1];
                break;
            case 4:
                anims = tbl->x00[3];
                break;
            }

            if (mn_8022F298(jobj) >= anims[1]) {
                state = data->x23;
                switch ((s32) state) {
                case 1:
                case 3:
                    data->x23 = 0;
                    text =
                        HSD_SisLib_803A5ACC(0, (s32) mn_804D6BB5, -14.9527f,
                                            -4.6369f, 17.5f, 200.0f, 300.0f);
                    data->jobjs[7] = (HSD_JObj*) text;
                    text->font_size.x = 0.0521f;
                    text->font_size.y = 0.0521f;
                    HSD_SisLib_803A6368(text, 2);
                    text =
                        HSD_SisLib_803A5ACC(0, (s32) mn_804D6BB5, -0.52099997f,
                                            -4.6369f, 17.5f, 200.0f, 300.0f);
                    data->jobjs[8] = (HSD_JObj*) text;
                    text->font_size.x = 0.0521f;
                    text->font_size.y = 0.0521f;
                    if (lbLang_IsSettingJP() != 0 &&
                        lbLang_IsSavedLanguageUS() != 0)
                    {
                        HSD_SisLib_803A6368(text, 5);
                    } else {
                        HSD_SisLib_803A6368(text, 3);
                    }
                    mnItemSw_80234104(gobj);
                    mnItemSw_804D6BEC = 0;
                    return;
                case 2:
                case 4:
                    HSD_GObjPLink_80390228(gobj);
                    HSD_SisLib_803A5CC4((HSD_Text*) data->jobjs[7]);
                    HSD_SisLib_803A5CC4((HSD_Text*) data->jobjs[8]);
                    return;
                }
            } else {
                HSD_JObjAnim(jobj);
            }
        }
    }

    {
        u8 state = data->x23;
        if (state == 0 || state == 1 || state == 3) {
            if ((s32) data->cursor != (s32) mn_804A04F0.hovered_selection) {
                hovered_changed = 1;
            }
            if ((u16) (mn_804A04F0.hovered_selection - 0x1F) <= 1U) {
                if ((u8) data->x21 != (u8) mn_804A04F0.confirmed_selection) {
                    confirmed_changed = 1;
                }
            } else if ((u8) data->items[mn_804A04F0.hovered_selection] !=
                       (u8) mn_804A04F0.confirmed_selection)
            {
                confirmed_changed = 1;
            }
        }
    }

    mnItemSw_8023453C(gobj, (u8) hovered_changed, (u8) confirmed_changed);

    if (menu_changed != 0) {
        data->menu_kind = (u8) mn_804A04F0.cur_menu;
    }
    if (hovered_changed != 0) {
        data->cursor = (u8) mn_804A04F0.hovered_selection;
    }
    if (confirmed_changed != 0) {
        if (((u16) mn_804A04F0.hovered_selection == 0x1F) ||
            ((u16) mn_804A04F0.hovered_selection == 0x20))
        {
            s32 i;
            MnItemSwData* dat;
            u8* order = tbl->item_order;

            data->x21 = (u8) mn_804A04F0.confirmed_selection;
            dat = (MnItemSwData*) gobj->user_data;
            for (i = 0; i < 0x1F; i++) {
                mn_8022E978(order[i], dat->items[i]);
            }
            gmMainLib_8015CC58()->item_freq = dat->x21 - 1;
            return;
        }
        data->items[mn_804A04F0.hovered_selection] =
            (u8) mn_804A04F0.confirmed_selection;
    }
}

HSD_JObj* mnItemSw_80235020(u8 arg0, MnItemSwData* arg1)
{
    HSD_JObj* sp14;
    HSD_JObj* sp10;
    u8 item_val;
    HSD_JObj* jobj;
    u8 hovered;

    hovered = (u8) mn_804A04F0.hovered_selection;
    jobj = HSD_JObjLoadJoint(MenMainCursorIs_Top.joint);
    HSD_JObjAddAnimAll(jobj, MenMainCursorIs_Top.animjoint,
                       MenMainCursorIs_Top.matanim_joint,
                       MenMainCursorIs_Top.shapeanim_joint);
    lb_80011E24(jobj, &sp14, 3, -1);
    item_val = arg0;
    HSD_JObjReqAnimAll(
        sp14,
        (f32) mnItemSw_80233A98((s32) mnItemSw_803ED340.item_order[item_val]));
    HSD_JObjAnimAll(sp14);
    if (arg0 == hovered) {
        HSD_JObjReqAnimAll(sp14, mnItemSw_803ED340.x30[1]);
    } else {
        HSD_JObjReqAnimAll(sp14, mnItemSw_803ED340.x30[0]);
    }
    mn_8022F3D8(sp14, 1, TOBJ_MASK);
    HSD_JObjAnimAll(sp14);
    item_val = arg1->items[arg0];
    lb_80011E24(jobj, &sp10, 2, -1);
    HSD_JObjReqAnimAll(sp10, mnItemSw_804D4BA0[item_val]);
    HSD_JObjAnimAll(sp10);
    lb_80011E24(jobj, &sp14, 8, -1);
    if (arg0 == hovered) {
        HSD_JObjReqAnimAll(sp14, mnItemSw_803ED340.x30[3]);
        HSD_JObjAnimAll(sp14);
    } else {
        HSD_JObjSetFlagsAll(sp14, 0x10);
    }
    return jobj;
}

HSD_GObj* mnItemSw_802351A0(s32 arg0)
{
    struct StaticModelDesc* mdl = &MenMainConIs_Top;
    struct MnItemSwTable* tbl = &mnItemSw_803ED340;
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    MnItemSwData* data;
    s32 i;
    f32 y_spacing;
    u8 cursor;
    HSD_JObj* cjobj;

    gobj = GObj_Create(6, 7, 0x80);
    mnItemSw_804D6BE8 = gobj;

    jobj = HSD_JObjLoadJoint(mdl->joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 6, 0x80);
    HSD_GObj_SetupProc(gobj, fn_80234C24, 0);

    HSD_JObjAddAnimAll(jobj, mdl->animjoint, mdl->matanim_joint,
                       mdl->shapeanim_joint);
    HSD_JObjReqAnimAll(jobj, 0.0f);
    HSD_JObjAnimAll(jobj);

    data = HSD_MemAlloc(sizeof(MnItemSwData));
    HSD_ASSERTREPORT(0x3D7, data, "Can't get user_data.\n");

    GObj_InitUserData(gobj, 0, HSD_Free, data);

    data->menu_kind = mn_804A04F0.cur_menu;
    data->cursor = (u8) mn_804A04F0.hovered_selection;

    {
        u8* order = tbl->item_order;
        for (i = 0; (u8) i < 0x1F; i++, order++) {
            data->items[(u8) i] = gm_8016403C(*order);
        }
    }

    data->x21 = gmMainLib_8015CC58()->item_freq + 1;
    data->x23 = (u8) arg0;

    for (i = 0; i < 7; i++) {
        lb_80011E24(jobj, &data->jobjs[i], i, -1);
    }

    if (mn_804A04F0.hovered_selection == 0x1F ||
        mn_804A04F0.hovered_selection == 0x20)
    {
        mn_804A04F0.confirmed_selection = data->x21;
    } else {
        mn_804A04F0.confirmed_selection = data->items[data->cursor];
    }

    y_spacing = HSD_JObjGetTranslationY(data->jobjs[5]) -
                HSD_JObjGetTranslationY(data->jobjs[4]);

    for (i = 0; i < 0x1F; i++) {
        HSD_JObj* item_jobj = mnItemSw_80235020((u8) i, data);
        if (i < 0x10) {
            HSD_JObjAddChild(data->jobjs[4], item_jobj);
            HSD_JObjAddTranslationY(item_jobj, y_spacing * (f32) i);
        } else {
            HSD_JObjAddChild(data->jobjs[6], item_jobj);
            HSD_JObjAddTranslationY(item_jobj, y_spacing * (f32) (i - 0x10));
        }
    }

    HSD_JObjSetFlagsAll(data->jobjs[4], 0x10);
    HSD_JObjSetFlagsAll(data->jobjs[6], 0x10);

    cursor = data->cursor;
    cjobj = data->jobjs[2];

    if (cursor == 0x1F || cursor == 0x20) {
        HSD_JObjSetFlagsAll(cjobj, 0x10);
    } else {
        HSD_JObjClearFlagsAll(cjobj, 0x10);
        y_spacing = HSD_JObjGetTranslationY(data->jobjs[5]) -
                    HSD_JObjGetTranslationY(data->jobjs[4]);

        if (cursor < 0x10) {
            HSD_JObjSetTranslateX(cjobj,
                                  HSD_JObjGetTranslationX(data->jobjs[4]));
            HSD_JObjSetTranslateY(cjobj,
                                  y_spacing * (f32) cursor +
                                      HSD_JObjGetTranslationY(data->jobjs[4]));
        } else {
            HSD_JObjSetTranslateX(cjobj,
                                  HSD_JObjGetTranslationX(data->jobjs[6]));
            HSD_JObjSetTranslateY(cjobj,
                                  y_spacing * (f32) (cursor - 0x10) +
                                      HSD_JObjGetTranslationY(data->jobjs[4]));
        }
    }

    HSD_JObjSetFlagsAll(data->jobjs[2], 0x10);

    {
        u8 hov = (u8) mn_804A04F0.hovered_selection;
        u8 x21 = data->x21;
        HSD_JObj* all_jobj = data->jobjs[3];

        if (hov == 0x1F || hov == 0x20) {
            HSD_JObjReqAnimAll(all_jobj, tbl->x30[7 + x21 * 2]);
        } else {
            HSD_JObjReqAnimAll(all_jobj, tbl->x30[6 + x21 * 2]);
        }
        HSD_JObjAnimAll(all_jobj);
    }

    HSD_JObjSetFlagsAll(data->jobjs[3], 0x10);

    return gobj;
}

void mnItemSw_802358C0(void)
{
    HSD_GObjProc* proc;

    mn_804A04F0.prev_menu = mn_804A04F0.cur_menu;
    mn_804A04F0.cur_menu = 0x10;
    mn_804A04F0.hovered_selection = 0;
    mnItemSw_804D6BEC = 1;
    mnItemSw_802351A0(1);

    proc = HSD_GObj_SetupProc(GObj_Create(0, 1, 0x80), fn_80233E10, 0);
    proc->flags_3 = HSD_GObj_804D783C;
}
