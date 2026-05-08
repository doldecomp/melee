#include "mnmainrule.h"

#include "mnmain.h"

#include "baselib/gobjgxlink.h"
#include "baselib/gobjobject.h"
#include "baselib/gobjuserdata.h"
#include "gm/gm_18A5.h"
#include "gm/gm_1A36.h"
#include "gm/gm_1A3F.h"

#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjplink.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/memory.h>
#include <sysdolphin/baselib/sislib.h>
#include <sysdolphin/baselib/debug.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/lb/lb_00F9.h>
#include <melee/lb/lbarchive.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/sc/types.h>

extern HSD_FogDesc* MenMain_fog;
extern UNK_T MenMain_lights;
extern HSD_CObjDesc* MenMain_cam;
extern StaticModelDesc MenMainBack_Top;
extern StaticModelDesc MenMainPanel_Top;
extern StaticModelDesc MenMainConTop_Top;
extern StaticModelDesc MenMainCursor_Top;
extern StaticModelDesc MenMainConRl_Top;
extern StaticModelDesc MenMainCursorRl_Top;
extern StaticModelDesc MenMainNmRl_Top;
extern StaticModelDesc MenMainCursorTr01_Top;
extern StaticModelDesc MenMainCursorTr02_Top;
extern StaticModelDesc MenMainCursorTr03_Top;
extern StaticModelDesc MenMainCursorTr04_Top;
extern StaticModelDesc MenMainCursorRl01_Top;
extern StaticModelDesc MenMainCursorRl02_Top;
extern StaticModelDesc MenMainCursorRl03_Top;
extern StaticModelDesc MenMainCursorRl04_Top;
extern StaticModelDesc MenMainCursorRl05_Top;
extern StaticModelDesc MenMainConIs_Top;
extern StaticModelDesc MenMainCursorIs_Top;
extern StaticModelDesc MenMainConSs_Top;
extern StaticModelDesc MenMainCursorSs_Top;

struct mn_803EC818_t {
    u8 x0;
    u8 pad_1[4];
};

struct mn_8022FB88_arg1_t {
    u8 pad_0[2];
    u8 x2;
    u8 x3;
    u8 pad_4[5];
    u8 x9;
    u8 pad_A[0x58 - 0x0A];
    HSD_JObj* x58[10];
    u8 pad_80[0xA8 - 0x80];
    struct mn_8022FEC8_jobj_ref_t* xA8;
    struct mn_8022FEC8_jobj_ref_t* xAC;
};

struct mn_8022FEC8_jobj_ref_t {
    u8 pad_0[0x10];
    HSD_JObj* x10;
};

typedef union {
    s32 packed;
    u8 idx[4];
} JObjIndices;

AnimLoopSettings mn_803EC734[5] = {
    { 0.0f, 3.0f, -0.1f },
    { 20.0f, 23.0f, -0.1f },
    { 40.0f, 43.0f, -0.1f },
    { 60.0f, 63.0f, -0.1f },
    { 80.0f, 83.0f, -0.1f },
};

AnimLoopSettings mn_803EC770[9] = {
    { 100.0f, 103.0f, -0.1f },
    { 120.0f, 123.0f, -0.1f },
    { 140.0f, 143.0f, -0.1f },
    { 160.0f, 163.0f, -0.1f },
    { 180.0f, 183.0f, -0.1f },
    { 30.0f, 49.0f, -0.1f },
    { 70.0f, 89.0f, -0.1f },
    { 90.0f, 109.0f, -0.1f },
    { 50.0f, 69.0f, -0.1f },
};

extern f32 mn_804D4B90;
extern u16 mn_804D4B94[2];
extern f32 mn_804D6BD8;
extern u8* mn_804DBDFC;
extern f32 mn_804DBE00;
extern HSD_GObj* mn_804D6BD0;
extern u16 mn_804DBE04;
extern s32 mn_804DBE08;
extern u8 mn_804DBE0C;
extern u16 mn_804DBDF8;
extern u32 mn_804DBE10;
extern u16 mn_804DBE14;
extern u16 mn_803EC7DC[][2];
extern u8 mn_803EC600[];
extern s32 mn_804D6BD4;

void mnItemSw_802358C0(void);
void mn_802339FC(void);
void mnCharSel_80264070(void);
void mnCharSel_802640A0(void);

void fn_8022F538(HSD_GObj* arg0)
{
    GameRules* rules;
    u16* limits;
    u32 buttons;
    u8 hovered;
    struct mn_802307F8_t* data;

    data = mn_804D6BD0->user_data;
    buttons = mn_80229624(4);
    ((u32*) &mn_804A04F0.buttons)[1] = buttons;
    ((u32*) &mn_804A04F0.buttons)[0] = 0;
    if ((buttons & 0x200) != 0) {
        if (mn_804A04F0.hovered_selection == 5 ||
            mn_804A04F0.hovered_selection == 6)
        {
            lbAudioAx_80024030(1);
            mn_804A04F0.entering_menu = 1;
            mn_804D6BC8.cooldown = 5;
            switch (mn_804A04F0.hovered_selection) {
            case 5:
                mnItemSw_802358C0();
                HSD_GObjPLink_80390228(arg0);
                break;
            case 6:
                mn_802339FC();
                HSD_GObjPLink_80390228(arg0);
                break;
            }
            rules = gmMainLib_8015CC34();
            rules->mode = data->x2;
            rules->time_limit = data->x3;
            rules->handicap = data->x4;
            rules->damage_ratio = data->x5;
            rules->unk_x7 = data->x6;
            rules->stock_count = data->x9;
            return;
        }
    } else if ((buttons & 0x100) != 0) {
        lbAudioAx_80024030(1);
        rules = gmMainLib_8015CC34();
        rules->mode = data->x2;
        rules->time_limit = data->x3;
        rules->handicap = data->x4;
        rules->damage_ratio = data->x5;
        rules->unk_x7 = data->x6;
        rules->stock_count = data->x9;
        if (gm_801A4310() == 1) {
            mn_80229860(2);
            return;
        }
        if (gm_801A4310() == 0x1B) {
            HSD_SisLib_803A5E70();
            mn_8022EBDC();
            gm_80190EA4();
            return;
        }
        if (gm_801A4310() == 1) {
            mn_80229894(2, 3, 3);
            return;
        }
        HSD_SisLib_803A5E70();
        mn_8022EBDC();
        mnCharSel_802640A0();
        return;
    }
    if ((buttons & 0x20) != 0) {
        lbAudioAx_80024030(0);
        mn_804A04F0.entering_menu = 0;
        rules = gmMainLib_8015CC34();
        rules->mode = data->x2;
        rules->time_limit = data->x3;
        rules->handicap = data->x4;
        rules->damage_ratio = data->x5;
        rules->unk_x7 = data->x6;
        rules->stock_count = data->x9;
        if (gm_801A4310() == 0x1B) {
            HSD_SisLib_803A5E70();
            mn_8022EBDC();
            gm_80190EA4();
            return;
        }
        if (gm_801A4310() == 1) {
            mn_80229894(2, 3, 3);
            return;
        }
        HSD_SisLib_803A5E70();
        mn_8022EBDC();
        mnCharSel_802640A0();
        return;
    }
    if ((buttons & 1) != 0) {
        lbAudioAx_80024030(2);
        do {
            if (mn_804A04F0.hovered_selection == 0) {
                mn_804A04F0.hovered_selection = 6;
            } else {
                mn_804A04F0.hovered_selection--;
            }
            hovered = mn_804A04F0.hovered_selection;
        } while (gm_801A4310() == 0x1B && hovered == 4);
        if (mn_804A04F0.hovered_selection == 1 && data->x2 == 1) {
            mn_804A04F0.confirmed_selection = data->x9;
            return;
        }
        mn_804A04F0.confirmed_selection =
            ((u8*) data)[mn_804A04F0.hovered_selection + 2];
        return;
    }
    if ((buttons & 2) != 0) {
        lbAudioAx_80024030(2);
        do {
            if (mn_804A04F0.hovered_selection == 6) {
                mn_804A04F0.hovered_selection = 0;
            } else {
                mn_804A04F0.hovered_selection++;
            }
            hovered = mn_804A04F0.hovered_selection;
        } while (gm_801A4310() == 0x1B && hovered == 4);
        if (mn_804A04F0.hovered_selection == 1 && data->x2 == 1) {
            mn_804A04F0.confirmed_selection = data->x9;
            return;
        }
        mn_804A04F0.confirmed_selection =
            ((u8*) data)[mn_804A04F0.hovered_selection + 2];
        return;
    }

    if (mn_804A04F0.hovered_selection == 1 && data->x2 == 1) {
        limits = mn_804D4B94;
    } else {
        limits = mn_803EC7DC[mn_804A04F0.hovered_selection];
    }
    if ((buttons & 4) != 0) {
        lbAudioAx_80024030(2);
        if (mn_804A04F0.confirmed_selection > limits[0]) {
            mn_804A04F0.confirmed_selection--;
            if (mn_804A04F0.confirmed_selection == limits[0] &&
                mn_804A04F0.hovered_selection == 1)
            {
                gm_801A36E0(4, 0x19);
            }
        } else {
            mn_804A04F0.confirmed_selection = limits[1];
        }
        if (mn_804D6BD4 == 0 && mn_804A04F0.hovered_selection == 2 &&
            mn_804A04F0.confirmed_selection == 1)
        {
            mn_804A04F0.confirmed_selection = 0;
        }
        if (gm_801A4310() == 0x1B && mn_804A04F0.hovered_selection == 1 &&
            data->x2 != 1 && mn_804A04F0.confirmed_selection == limits[0])
        {
            mn_804A04F0.confirmed_selection = limits[1];
        }
        if (mn_804A04F0.hovered_selection == 2) {
            gmMainLib_8015EA80();
            mnCharSel_80264070();
        }
        return;
    }
    if ((buttons & 8) != 0) {
        lbAudioAx_80024030(2);
        if (mn_804A04F0.confirmed_selection < limits[1]) {
            mn_804A04F0.confirmed_selection++;
            if (mn_804A04F0.confirmed_selection == limits[1] &&
                mn_804A04F0.hovered_selection == 1)
            {
                gm_801A36E0(4, 0x19);
            }
        } else {
            mn_804A04F0.confirmed_selection = limits[0];
        }
        if (mn_804D6BD4 == 0 && mn_804A04F0.hovered_selection == 2 &&
            mn_804A04F0.confirmed_selection == 1)
        {
            mn_804A04F0.confirmed_selection = 2;
        }
        if (gm_801A4310() == 0x1B && mn_804A04F0.hovered_selection == 1 &&
            data->x2 != 1 && mn_804A04F0.confirmed_selection == limits[0])
        {
            mn_804A04F0.confirmed_selection = limits[0] + 1;
        }
        if (mn_804A04F0.hovered_selection == 2) {
            gmMainLib_8015EA80();
            mnCharSel_80264070();
        }
    }
}

void mn_8022FB88(u8 arg0, void* arg1)
{
    struct mn_8022FB88_arg1_t* data = arg1;
    u8* sp14;
    s32 sp10;
    HSD_JObj* temp_r29;
    HSD_JObj* temp_r29_2;
    HSD_JObj* temp_r29_3;
    HSD_JObj* temp_r31;
    HSD_JObj* temp_r28;
    s32 var_r27;
    s32 var_r28;
    u8* var_r29;
    u8* var_r29_2;
    HSD_JObj** temp_r27_2;

    sp14 = mn_804DBDFC;
    if (arg0 == 0) {
        HSD_JObj* temp_r27;
        var_r27 = 0;
        var_r29 = (u8*) &sp14;
        do {
            HSD_JObjSetFlagsAll(data->x58[*var_r29], 0x10U);
            var_r27 += 1;
            var_r29 += 1;
        } while (var_r27 < 4);
        temp_r27 = data->x58[4];
        HSD_JObjReqAnimAll(temp_r27, mn_804D4B90);
        HSD_JObjAnimAll(temp_r27);
        return;
    }
    var_r28 = 0;
    var_r29_2 = (u8*) &sp14;
    do {
        HSD_JObjClearFlagsAll(data->x58[*var_r29_2], 0x10U);
        var_r28 += 1;
        var_r29_2 += 1;
    } while (var_r28 < 4);
    temp_r28 = data->x58[4];
    HSD_JObjReqAnimAll(temp_r28, mn_804D6BD8);
    HSD_JObjAnimAll(temp_r28);
    temp_r27_2 = data->x58;
    temp_r27_2 = data->x58;
    temp_r31 = temp_r27_2[2];
    HSD_JObjReqAnimAll(temp_r31, (f32) (u8) (arg0 / 10));
    HSD_JObjAnimAll(temp_r31);
    temp_r29 = temp_r27_2[3];
    HSD_JObjReqAnimAll(temp_r29, (f32) (u8) (arg0 % 10));
    HSD_JObjAnimAll(temp_r29);
    temp_r29_2 = temp_r27_2[5];
    HSD_JObjReqAnimAll(temp_r29_2, mn_804DBE00);
    HSD_JObjAnimAll(temp_r29_2);
    temp_r29_3 = temp_r27_2[6];
    HSD_JObjReqAnimAll(temp_r29_3, mn_804DBE00);
    HSD_JObjAnimAll(temp_r29_3);
}

void mn_8022FD18(u8 arg0)
{
    u16 sp14;
    u8 sp10;
    s32 spC;
    HSD_JObj* jobj;
    struct mn_8022FB88_arg1_t* data;
    s32 i;
    u8* ptr;
    u8 val;

    data = mn_804D6BD0->user_data;
    spC = mn_804DBE08;
    sp14 = mn_804DBE04;
    sp10 = mn_804DBE0C;
    if (arg0 != 0) {
        i = 0;
        ptr = (u8*) &sp14;
        do {
            HSD_JObjSetFlagsAll(data->x58[*ptr], 0x10U);
            i++;
            ptr++;
        } while (i < 2);
        i = 0;
        ptr = (u8*) &spC;
        do {
            HSD_JObjClearFlagsAll(data->x58[*ptr], 0x10U);
            i++;
            ptr++;
        } while (i < 5);
        mn_8022FB88(data->x3, data);
        return;
    }
    i = 0;
    ptr = (u8*) &sp14;
    do {
        HSD_JObjClearFlagsAll(data->x58[*ptr], 0x10U);
        i++;
        ptr++;
    } while (i < 2);
    i = 0;
    ptr = (u8*) &spC;
    do {
        HSD_JObjSetFlagsAll(data->x58[*ptr], 0x10U);
        i++;
        ptr++;
    } while (i < 5);
    val = data->x9;
    jobj = data->x58[7];
    HSD_JObjReqAnimAll(jobj, (f32) (u8) (data->x9 / 10));
    HSD_JObjAnimAll(jobj);
    jobj = data->x58[8];
    HSD_JObjReqAnimAll(jobj, (f32) (u8) (val % 10));
    HSD_JObjAnimAll(jobj);
}

void mn_8022FEC8(HSD_GObj* arg0, HSD_JObj* arg1, u8 arg2, u8 arg3)
{
    HSD_JObj* temp_r28;
    HSD_JObj* temp_r28_2;
    HSD_JObj* var_r28;
    HSD_JObj* var_r28_2;
    f32* var_r8;
    struct mn_8022FB88_arg1_t* temp_r31;
    HSD_JObj** temp_r31_2;
    struct mn_8022FEC8_jobj_ref_t* temp_r3;
    struct mn_8022FEC8_jobj_ref_t* temp_r3_2;
    u8* base;

    temp_r31 = arg0->user_data;
    base = mn_803EC600;
    switch (arg2) {
    case 1:
        if (((struct mn_8022FB88_arg1_t*) mn_804D6BD0->user_data)->x2 != 1) {
            mn_8022FB88(arg3, temp_r31);
            return;
        }
        temp_r31_2 = temp_r31->x58;
        temp_r28 = temp_r31_2[7];
        HSD_JObjReqAnimAll(temp_r28, (f32) (u8) (arg3 / 10));
        HSD_JObjAnimAll(temp_r28);
        temp_r28_2 = temp_r31_2[8];
        HSD_JObjReqAnimAll(temp_r28_2, (f32) (u8) (arg3 % 10));
        HSD_JObjAnimAll(temp_r28_2);
        return;
    case 3:
        temp_r3 = temp_r31->xA8;
        if (temp_r3 == NULL) {
            var_r28 = NULL;
        } else {
            var_r28 = temp_r3->x10;
        }
        HSD_JObjReqAnimAll(var_r28, (f32) (u8) (arg3 / 10));
        HSD_JObjAnimAll(var_r28);
        temp_r3_2 = temp_r31->xAC;
        if (temp_r3_2 == NULL) {
            var_r28_2 = NULL;
        } else {
            var_r28_2 = temp_r3_2->x10;
        }
        HSD_JObjReqAnimAll(var_r28_2, (f32) (u8) (arg3 % 10));
        HSD_JObjAnimAll(var_r28_2);
        return;
    case 0:
    case 2:
    case 4:
        break;
    default:
        return;
    }

    var_r8 = NULL;
    if ((mn_804A04F0.buttons & 4) != 0) {
        var_r8 =
            (f32*) (base + 0x170 + (0xC * (base[0x1DD + (arg2 << 1)] - arg3)));
        HSD_JObjReqAnimAll(arg1, *var_r8);
    } else {
        if (arg3 == 0) {
            var_r8 = (f32*) (base + 0x134 + (0xC * base[0x1DD + (arg2 << 1)]));
        } else {
            var_r8 = (f32*) (base + 0x134 + (0xC * (arg3 - 1)));
        }
        HSD_JObjReqAnimAll(arg1, *var_r8);
    }
    HSD_JObjAnimAll(arg1);
}

void mn_80230198(HSD_GObj* gobj, HSD_JObj* jobj, u8 arg2)
{
    AnimLoopSettings* settings;
    f32 frame;
    s32 i;
    s32 option;

    PAD_STACK(8);

    option = arg2;
    if (option == 3) {
        return;
    }

    if (option >= 3) {
        goto seven;
    }

    if (option == 1) {
        return;
    }
    if (option >= 1) {
        goto func;
    }

    if (option >= 0) {
        goto func;
    }
    return;

seven:
    if (option >= 7) {
        return;
    }
    if (option >= 5) {
        return;
    }

func:
    frame = mn_8022F298(jobj);

    for (i = 0; i != 5; i++) {
        settings = &mn_803EC770[i];
        if (mn_803EC770[i].start_frame <= frame &&
            frame <= mn_803EC770[i].end_frame)
        {
            break;
        }
        settings = &mn_803EC734[i];
        if (mn_803EC734[i].start_frame <= frame &&
            frame <= mn_803EC734[i].end_frame)
        {
            break;
        }
    }

    mn_8022ED6C(jobj, settings);
}

extern MenuKindData mn_803EB6B0[];
extern AnimLoopSettings mn_804D4B88;

extern u8 mn_804D4B96;
extern struct mn_803EC818_t mn_803EC818[];
extern f32 mn_804DBE18;
extern f32 mn_804DBE1C;
extern f32 mn_804DBE20;
extern f32 mn_804DBE24;
extern f32 mn_804DBE28;
extern f32 mn_804DBE2C;

void mn_80230274(HSD_GObj* arg0, int arg1, int arg2)
{
    HSD_JObj* roots[17];
    u16 indices[17];
    AnimLoopSettings* settings;
    HSD_JObj* jobj;
    HSD_JObj* option_roots[8];
    s32 i;
    s32 j;
    s32 visible;
    u8 count;
    u8 selected;
    u8 hovered;
    u8* data8;
    struct mn_802307F8_t* data;

    data = arg0->user_data;
    data8 = arg0->user_data;
    count = mn_803EB6B0[15].selection_count;
    for (i = 0; i < 0x11; i++) {
        indices[i] = i;
    }

    for (i = 0; i < count; i++) {
        if (gm_801A4310() == 0x1B && (u8) i == 4) {
            continue;
        }
        visible = 0;
        for (j = 0; j < i; j++) {
            if (!(gm_801A4310() == 0x1B && (u8) j == 4)) {
                visible++;
            }
        }
        if (data->xC[indices[visible]] == NULL) {
            option_roots[i] = NULL;
        } else {
            option_roots[i] =
                ((struct mn_8022FEC8_jobj_ref_t*) data->xC[indices[visible]])
                    ->x10;
        }
    }

    if (arg1 != 0) {
        selected = data->x1;
        lb_8001204C(option_roots[selected], roots, indices, 0x11);
        HSD_JObjSetFlagsAll(roots[16], 0x10U);
        HSD_JObjSetFlagsAll(roots[13], 0x10U);
        jobj = roots[2];
        if ((u8) (selected - 5) <= 1) {
            HSD_JObjReqAnimAll(jobj, *(f32*) (mn_803EC600 + 0x78));
        } else {
            HSD_JObjReqAnimAll(jobj, *(f32*) (mn_803EC600 + 0x60));
        }
        HSD_JObjAnimAll(jobj);
        jobj = roots[7];
        if (selected == 1 &&
            ((struct mn_8022FB88_arg1_t*) mn_804D6BD0->user_data)->x2 == 1)
        {
            HSD_JObjReqAnim(jobj, mn_804D4B88.start_frame);
        } else {
            HSD_JObjReqAnim(jobj, *(f32*) (mn_803EC600 + 0x10 + selected * 8));
        }
        HSD_JObjAnim(jobj);
        HSD_JObjSetFlagsAll(roots[8], 0x10U);

        hovered = mn_804A04F0.hovered_selection;
        lb_8001204C(option_roots[hovered], roots, indices, 0x11);
        HSD_JObjClearFlagsAll(roots[16], 0x10U);
        HSD_JObjReqAnimAll(roots[16], *(f32*) (mn_803EC600 + 0x48));
        if (hovered != 5 && hovered != 6) {
            HSD_JObjClearFlagsAll(roots[13], 0x10U);
            HSD_JObjReqAnimAll(roots[13], *(f32*) (mn_803EC600 + 0x54));
            HSD_JObjReqAnimAll(roots[2], *(f32*) (mn_803EC600 + 0x6C));
            HSD_JObjAnimAll(roots[2]);
        } else {
            HSD_JObjReqAnimAll(roots[2], *(f32*) (mn_803EC600 + 0x84));
            HSD_JObjAnimAll(roots[2]);
        }
        if (hovered == 1 &&
            ((struct mn_8022FB88_arg1_t*) mn_804D6BD0->user_data)->x2 == 1)
        {
            HSD_JObjReqAnim(roots[7], mn_804D4B88.end_frame);
        } else {
            HSD_JObjReqAnim(roots[7], *(f32*) (mn_803EC600 + 0x14 + hovered * 8));
        }
        HSD_JObjAnim(roots[7]);
        if ((u8) (hovered - 5) <= 1) {
            HSD_JObjClearFlagsAll(roots[8], 0x10U);
            HSD_JObjReqAnimAll(roots[8], *(f32*) (mn_803EC600 + 0x90));
            HSD_JObjAnimAll(roots[8]);
        }
    }

    if (arg2 != 0) {
        mn_8022FEC8(arg0, data->x34[mn_804A04F0.hovered_selection].x0,
                    mn_804A04F0.hovered_selection,
                    mn_804A04F0.confirmed_selection);
    }

    for (i = 0; i < count; i++) {
        u8 focus;

        if (gm_801A4310() == 0x1B && (u8) i == 4) {
            continue;
        }
        lb_8001204C(option_roots[i], roots, indices, 0x11);
        if (arg1 != 0) {
            focus = mn_804A04F0.hovered_selection;
        } else {
            focus = data->x1;
        }
        if (i == focus) {
            mn_8022ED6C(roots[16], (AnimLoopSettings*) (mn_803EC600 + 0x48));
        }
        if (i == focus && i != 5 && i != 6) {
            mn_8022ED6C(roots[13], (AnimLoopSettings*) (mn_803EC600 + 0x54));
        }
        if ((u32) (i - 5) <= 1) {
            settings = (AnimLoopSettings*) (mn_803EC600 +
                                            (((u8) (focus == i)) * 0xC) +
                                            0x78);
        } else {
            settings = (AnimLoopSettings*) (mn_803EC600 +
                                            (((u8) (focus == i)) * 0xC) +
                                            0x60);
        }
        mn_8022ED6C(roots[2], settings);
        mn_8022ED6C(roots[8], (AnimLoopSettings*) (mn_803EC600 + 0x90));
        mn_80230198(arg0, data->x34[i].x0, i);
        if (i == 1 && arg2 != 0 && focus == 0) {
            if (mn_804A04F0.confirmed_selection == 1) {
                HSD_JObjReqAnim(roots[7], mn_804D4B88.start_frame);
            } else {
                HSD_JObjReqAnim(roots[7], *(f32*) (mn_803EC600 + 0x18));
            }
            HSD_JObjAnim(roots[7]);
            mn_8022FD18((u8) (mn_804A04F0.confirmed_selection != 1));
        }
    }
}

void mn_802307F8(struct mn_802307F8_t* arg0, s32 arg1, s32 arg2)
{
    HSD_Text* temp_r3_2;
    u8 var_r30;

    if (arg0->text != NULL) {
        HSD_SisLib_803A5CC4(arg0->text);
        arg0->text = NULL;
    }
    if ((arg1 == 1) && ((u8) arg0->x2 == 1)) {
        var_r30 = mn_804D4B96;
    } else if ((arg1 == 1) || (arg1 == 3) || ((u32) (arg1 - 5) <= 1U)) {
        var_r30 = mn_803EC818[arg1].x0;
    } else {
        var_r30 = *(&mn_803EC818[arg1].x0 + arg2);
    }
    temp_r3_2 = HSD_SisLib_803A5ACC(0, 1, mn_804DBE18, mn_804DBE1C,
                                    mn_804DBE20, mn_804DBE24, mn_804DBE28);
    arg0->text = temp_r3_2;
    temp_r3_2->font_size.y = temp_r3_2->font_size.x = mn_804DBE2C;
    HSD_SisLib_803A6368(temp_r3_2, var_r30);
}

void mn_802308F0(HSD_GObj* gobj, int arg1, int arg2)
{
    struct mn_802307F8_t* data = HSD_GObjGetUserData(gobj);
    u16 sel;
    u8 kind;

    if (arg1 != 0) {
        sel = mn_804A04F0.hovered_selection;
    } else {
        sel = data->x1;
    }
    kind = sel;

    switch (data->xA) {
    case 2:
    case 4:
        if (data->text != NULL) {
            HSD_SisLib_803A5CC4(data->text);
            data->text = NULL;
        }
        break;
    case 1:
    case 3:
        if (data->text == NULL) {
            mn_802307F8((struct mn_802307F8_t*) data, kind,
                        mn_804A04F0.confirmed_selection);
        }
        break;
    case 0:
        if (arg1 != 0 ||
            (arg2 != 0 && (kind == 0 || kind == 2 || kind == 4)))
        {
            mn_802307F8((struct mn_802307F8_t*) data, kind,
                        mn_804A04F0.confirmed_selection);
        }
        break;
    case 5:
        break;
    }
}

void fn_802309F0(HSD_GObj* arg0)
{
    GameRules* rules;
    HSD_JObj* jobj;
    f32* anim;
    u8* base;
    u8* ptr;
    s32 update_menu;
    s32 update_selection;
    s32 update_value;
    u8 state;
    struct mn_802307F8_t* data;

    update_menu = 0;
    update_selection = 0;
    update_value = 0;
    data = arg0->user_data;
    base = mn_803EC600;
    if ((data->xA == 0 || data->xA == 1 || data->xA == 3) &&
        data->x0 != mn_804A04F0.cur_menu)
    {
        if ((u8) (mn_804A04F0.cur_menu - 0xF) <= 1) {
            data->xA = 4;
        } else {
            data->xA = 2;
        }
        state = data->xA;
        jobj = data->xC[2];
        switch (state) {
        case 1:
            anim = (f32*) (base + 0x1AC);
            break;
        case 2:
            anim = (f32*) (base + 0x1C4);
            break;
        case 3:
            anim = (f32*) (base + 0x1B8);
            break;
        case 4:
            anim = (f32*) (base + 0x1D0);
            break;
        default:
            anim = NULL;
            break;
        }
        HSD_JObjReqAnim(jobj, anim[0]);
        HSD_JObjAnim(jobj);
        if (data->xA == 0 || data->xA == 1 || data->xA == 3) {
            update_menu = 1;
            update_selection = 1;
            update_value = 1;
        }
    }

    state = data->xA;
    if (state != 0) {
        jobj = data->xC[2];
        switch (state) {
        case 1:
            anim = (f32*) (base + 0x1AC);
            break;
        case 2:
            anim = (f32*) (base + 0x1C4);
            break;
        case 3:
            anim = (f32*) (base + 0x1B8);
            break;
        case 4:
            anim = (f32*) (base + 0x1D0);
            break;
        default:
            anim = NULL;
            break;
        }
        if (mn_8022F298(jobj) >= anim[1]) {
            switch (data->xA) {
            case 1:
            case 3:
                data->xA = 0;
                break;
            case 2:
            case 4:
                HSD_GObjPLink_80390228(arg0);
                return;
            }
        } else {
            HSD_JObjAnim(jobj);
        }
    }

    if (data->xA == 0 || data->xA == 1 || data->xA == 3) {
        update_selection = mn_804A04F0.hovered_selection != data->x1;
        if (mn_804A04F0.hovered_selection == 1 && data->x2 == 1) {
            if (data->x9 != mn_804A04F0.confirmed_selection) {
                update_value = 1;
            }
        } else {
            ptr = (u8*) data + mn_804A04F0.hovered_selection;
            if (ptr[2] !=
                   mn_804A04F0.confirmed_selection)
            {
                update_value = 1;
            }
        }
    }

    mn_80230274(arg0, update_selection, update_value);
    mn_802308F0(arg0, update_selection, update_value);
    if (update_menu != 0) {
        data->x0 = mn_804A04F0.cur_menu;
    }
    if (update_selection != 0) {
        data->x1 = mn_804A04F0.hovered_selection;
    }
    if (update_value != 0) {
        if (data->x1 == 1 && data->x2 == 1) {
            data->x9 = mn_804A04F0.confirmed_selection;
        } else {
            ((u8*) data)[data->x1 + 2] = mn_804A04F0.confirmed_selection;
        }
        rules = gmMainLib_8015CC34();
        rules->mode = data->x2;
        rules->time_limit = data->x3;
        rules->handicap = data->x4;
        rules->damage_ratio = data->x5;
        rules->unk_x7 = data->x6;
        rules->stock_count = data->x9;
    }
}

extern s32 mn_804D6BD4;

int mn_80230D18(struct mn_802307F8_t* arg0, HSD_JObj* arg1, s8 arg2)
{
    s32 result;
    s32 i;

    arg0->x0 = mn_804A04F0.cur_menu;
    arg0->x1 = mn_804A04F0.hovered_selection;
    arg0->x4 = gmMainLib_8015CC34()->handicap;
    if (mn_804D6BD4 == 0 && arg0->x4 == 1) {
        arg0->x4 = 0;
    }
    arg0->x5 = gmMainLib_8015CC34()->damage_ratio;
    arg0->x6 = gmMainLib_8015CC34()->unk_x7;
    arg0->x2 = gmMainLib_8015CC34()->mode;
    arg0->x9 = gmMainLib_8015CC34()->stock_count;
    arg0->x3 = gmMainLib_8015CC34()->time_limit;
    if (gm_801A4310() == 0x1B && arg0->x3 == 0) {
        arg0->x3 = 0x63;
    }
    arg0->xA = arg2;
    result = 0;
    arg0->text = NULL;
    for (i = 0; i < 10; i++) {
        result = lb_80011E24(arg1, &arg0->xC[i], i, -1);
    }
    return result;
}

HSD_GObj* mn_80230E38(int arg0)
{
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    HSD_JObj* roots[17];
    StaticModelDesc** descs;
    AnimLoopSettings* settings;
    struct mn_802307F8_t* data;
    u16 counts[8];
    u16 indices[17];
    u8* data8;
    u8* p;
    u8 count;
    u8 hovered;
    s32 i;
    s32 j;
    s32 visible;
    s32 total_visible;
    u32 bytes4;
    u16 bytes2;

    hovered = mn_804A04F0.hovered_selection;
    count = mn_803EB6B0[15].selection_count;
    for (i = 0; i < 0x11; i++) {
        indices[i] = i;
    }

    gobj = GObj_Create(6, 7, 0x80);
    mn_804D6BD0 = gobj;
    jobj = HSD_JObjLoadJoint(MenMainConRl_Top.joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 4, 0x80);
    HSD_GObj_SetupProc(gobj, fn_802309F0, 0);
    HSD_JObjAddAnimAll(jobj, MenMainConRl_Top.animjoint,
                       MenMainConRl_Top.matanim_joint,
                       MenMainConRl_Top.shapeanim_joint);
    HSD_JObjReqAnimAll(jobj, mn_804DBE00);
    HSD_JObjAnimAll(jobj);

    data = (struct mn_802307F8_t*) HSD_MemAlloc(sizeof(*data));
    HSD_ASSERTREPORT(0x575, data, "Can't get user_data.\n");
    GObj_InitUserData(gobj, 0, HSD_Free, data);
    mn_80230D18(data, jobj, arg0);
    data8 = (u8*) data;
    if (data->x1 == 1 &&
        ((struct mn_8022FB88_arg1_t*) mn_804D6BD0->user_data)->x2 == 1)
    {
        mn_804A04F0.confirmed_selection = data->x9;
    } else {
        mn_804A04F0.confirmed_selection = data8[data->x1 + 2];
    }

    if (arg0 != 0) {
        if (data->xA == 1) {
            settings = (AnimLoopSettings*) (mn_803EC600 + 0x1AC);
        } else if (data->xA == 3) {
            settings = (AnimLoopSettings*) (mn_803EC600 + 0x1B8);
        } else {
            settings = (AnimLoopSettings*) (mn_803EC600 + 0x1C4);
        }
        HSD_JObjReqAnim(data->xC[2], settings->start_frame);
        HSD_JObjAnim(data->xC[2]);
    }

    descs = (StaticModelDesc**) (mn_803EC600 + 0x1EC);
    for (i = 0; i < count; i++) {
        visible = 0;
        for (j = 0; j < i; j++) {
            if (!(gm_801A4310() == 0x1B && (u8) j == 4)) {
                visible++;
            }
        }
        total_visible = 0;
        for (j = 0; j < 7; j++) {
            if (!(gm_801A4310() == 0x1B && (u8) j == 4)) {
                total_visible++;
            }
        }

        jobj = data->xC[indices[visible]];
        HSD_JObjReqAnim(jobj, (f32) total_visible);
        HSD_JObjAnim(jobj);

        if (gm_801A4310() == 0x1B && (u8) i == 4) {
            continue;
        }

        jobj = HSD_JObjLoadJoint(MenMainCursorRl_Top.joint);
        HSD_JObjAddAnimAll(jobj, MenMainCursorRl_Top.animjoint,
                           MenMainCursorRl_Top.matanim_joint,
                           MenMainCursorRl_Top.shapeanim_joint);
        HSD_JObjReqAnimAll(jobj, mn_804DBE00);
        HSD_JObjAnimAll(jobj);
        lb_8001204C(jobj, roots, indices, 0x11);
        if (i == 1 &&
            ((struct mn_8022FB88_arg1_t*) mn_804D6BD0->user_data)->x2 == 1)
        {
            HSD_JObjReqAnim(roots[7],
                            ((f32*) &mn_804D4B88)[(u8) (i == hovered)]);
        } else {
            HSD_JObjReqAnim(
                roots[7],
                ((f32*) (mn_803EC600 + 0x10))[i * 2 + (u8) (i == hovered)]);
        }
        HSD_JObjAnim(roots[7]);
        if (hovered != i) {
            HSD_JObjSetFlagsAll(roots[16], 0x10U);
        }
        if (hovered != i || (u32) (i - 5) <= 1U) {
            HSD_JObjSetFlagsAll(roots[13], 0x10U);
        }
        if ((u32) (i - 5) <= 1U) {
            settings = (AnimLoopSettings*) (mn_803EC600 +
                                            ((u8) (hovered == i) * 0xC) +
                                            0x78);
        } else {
            settings = (AnimLoopSettings*) (mn_803EC600 +
                                            ((u8) (hovered == i) * 0xC) +
                                            0x60);
        }
        HSD_JObjReqAnimAll(roots[2], settings->start_frame);
        HSD_JObjAnimAll(roots[2]);
        if (hovered != i || (i != 5 && i != 6)) {
            HSD_JObjSetFlagsAll(roots[8], 0x10U);
        }
        HSD_JObjAddChild(data->xC[indices[visible]], jobj);

        if (i == 5 || i == 6) {
            continue;
        }

        jobj = HSD_JObjLoadJoint(descs[i]->joint);
        HSD_JObjAddAnimAll(jobj, descs[i]->animjoint, descs[i]->matanim_joint,
                           descs[i]->shapeanim_joint);
        HSD_JObjReqAnimAll(jobj, mn_804DBE00);
        HSD_JObjAnimAll(jobj);
        counts[i] = *((u16*) (mn_803EC600 + 0x208 + i * 2));
        for (j = 0; j < counts[i]; j++) {
            lb_80011E24(jobj, (HSD_JObj**) (data8 + 0x34 + i * 0x24 + j * 4), j,
                        -1);
        }

        switch (i) {
        case 1:
            bytes4 = mn_804DBE10;
            bytes2 = mn_804DBE14;
            p = (u8*) &bytes4;
            for (j = 0; j < 4; j++) {
                HSD_JObj* text = HSD_JObjLoadJoint(MenMainNmRl_Top.joint);
                HSD_JObjAddAnimAll(text, MenMainNmRl_Top.animjoint,
                                   MenMainNmRl_Top.matanim_joint,
                                   MenMainNmRl_Top.shapeanim_joint);
                HSD_JObjAddChild(*(HSD_JObj**) (data8 + 0x58 + p[j] * 4), text);
            }
            p = (u8*) &bytes2;
            for (j = 0; j < 2; j++) {
                HSD_JObj* text = HSD_JObjLoadJoint(MenMainNmRl_Top.joint);
                HSD_JObjAddAnimAll(text, MenMainNmRl_Top.animjoint,
                                   MenMainNmRl_Top.matanim_joint,
                                   MenMainNmRl_Top.shapeanim_joint);
                HSD_JObjAddChild(*(HSD_JObj**) (data8 + 0x58 + p[j] * 4), text);
            }
            mn_8022FD18(
                (u8) (((struct mn_8022FB88_arg1_t*) mn_804D6BD0->user_data)->x2 !=
                     1));
            break;
        case 3:
            bytes2 = mn_804DBDF8;
            p = (u8*) &bytes2;
            for (j = 0; j < 2; j++) {
                HSD_JObj* text = HSD_JObjLoadJoint(MenMainNmRl_Top.joint);
                HSD_JObjAddAnimAll(text, MenMainNmRl_Top.animjoint,
                                   MenMainNmRl_Top.matanim_joint,
                                   MenMainNmRl_Top.shapeanim_joint);
                HSD_JObjAddChild(*(HSD_JObj**) (data8 + 0xA0 + p[j] * 4), text);
            }
            HSD_JObjReqAnimAll((HSD_JObj*) mn_80231634(
                                   *(struct mn_80231634_t**) (data8 + 0xA8)),
                               (f32) (u8) (data->x5 / 10));
            HSD_JObjAnimAll((HSD_JObj*) mn_80231634(
                *(struct mn_80231634_t**) (data8 + 0xA8)));
            HSD_JObjReqAnimAll((HSD_JObj*) mn_80231634(
                                   *(struct mn_80231634_t**) (data8 + 0xAC)),
                               (f32) (u8) (data->x5 % 10));
            HSD_JObjAnimAll((HSD_JObj*) mn_80231634(
                *(struct mn_80231634_t**) (data8 + 0xAC)));
            break;
        case 0:
        case 2:
        case 4:
            if (data8[i + 2] == 0) {
                settings = (AnimLoopSettings*) (mn_803EC600 +
                                                (*((u8*) (mn_803EC600 + 0x1DD +
                                                          i * 2)) *
                                                 0xC) +
                                                0x134);
            } else {
                settings = (AnimLoopSettings*) (mn_803EC600 +
                                                ((data8[i + 2] - 1) * 0xC) +
                                                0x134);
            }
            HSD_JObjReqAnimAll(*(HSD_JObj**) (data8 + 0x34 + i * 0x24),
                               settings->end_frame);
            HSD_JObjAnimAll(*(HSD_JObj**) (data8 + 0x34 + i * 0x24));
            break;
        }

        HSD_JObjAddChild(data->xC[indices[visible]], jobj);
    }

    mn_802307F8(data, data->x1, mn_804A04F0.confirmed_selection);
    return gobj;
}

int mn_80231634(struct mn_80231634_t* arg0)
{
    if (arg0 == NULL) {
        return 0;
    }
    return arg0->x10;
}

void mn_8023164C(void)
{
    HSD_GObjProc* proc;
    s32 mode;

    mn_804A04F0.prev_menu = mn_804A04F0.cur_menu;
    mn_804A04F0.cur_menu = 0xD;

    switch (mn_804A04F0.prev_menu) {
    case 15:
        mn_804A04F0.hovered_selection = 6;
        mode = 3;
        break;
    case 16:
        mn_804A04F0.hovered_selection = 5;
        mode = 3;
        break;
    default:
        mn_804A04F0.hovered_selection = 0;
        mode = 1;
        break;
    }

    proc = HSD_GObj_SetupProc(GObj_Create(0, 1, 0x80), fn_8022F538, 0);
    proc->flags_3 = HSD_GObj_804D783C;
    HSD_GObj_80390CD4(mn_80230E38(mode));
}

void mn_80231714(void)
{
    HSD_GObjProc* proc;
    s32 mode;

    mn_804A04F0.prev_menu = mn_804A04F0.cur_menu;
    mn_804A04F0.cur_menu = 0xD;

    switch (mn_804A04F0.prev_menu) {
    case 15:
        mn_804A04F0.hovered_selection = 6;
        mode = 3;
        break;
    case 16:
        mn_804A04F0.hovered_selection = 5;
        mode = 3;
        break;
    default:
        mn_804A04F0.hovered_selection = 0;
        mode = 1;
        break;
    }

    proc = HSD_GObj_SetupProc(GObj_Create(0, 1, 0x80), fn_8022F538, 0);
    proc->flags_3 = HSD_GObj_804D783C;
    HSD_GObj_80390CD4(mn_80230E38(mode));
    mn_804D6BD4 = 1;
}

void mn_802317E4(HSD_Archive* archive, int arg1)
{
    mn_80231804(archive, arg1);
}

extern s32 mn_804D6BD4;

void mn_80231804(HSD_Archive* archive, int arg1)
{
    HSD_GObjProc* temp_r3;
    mn_804D6BC8.cooldown = 0x14;
    mn_804D6BC8.x2 = 0;
    mn_804D6BC8.x4 = 0;
    mn_804A04F0.buttons = 0;
    mn_804A04F0.prev_menu = mn_804A04F0.cur_menu;
    mn_804A04F0.cur_menu = 0xD;
    mn_804A04F0.hovered_selection = 0;
    HSD_SisLib_803A5E70();

    lbArchive_LoadSections(
        archive, (void**) &MenMainBack_Top.joint, "MenMainBack_Top_joint",
        &MenMainBack_Top.animjoint, "MenMainBack_Top_animjoint",
        &MenMainBack_Top.matanim_joint, "MenMainBack_Top_matanim_joint",
        &MenMainBack_Top.shapeanim_joint, "MenMainBack_Top_shapeanim_joint",

        &MenMain_cam, "ScMenMain_cam_int1_camera", &MenMain_lights,
        "ScMenMain_scene_lights", &MenMain_fog, "ScMenMain_fog",

        &MenMainPanel_Top.joint, "MenMainPanel_Top_joint",
        &MenMainPanel_Top.animjoint, "MenMainPanel_Top_animjoint",
        &MenMainPanel_Top.matanim_joint, "MenMainPanel_Top_matanim_joint",
        &MenMainPanel_Top.shapeanim_joint, "MenMainPanel_Top_shapeanim_joint",

        &MenMainConRl_Top.joint, "MenMainConRl_Top_joint",
        &MenMainConRl_Top.animjoint, "MenMainConRl_Top_animjoint",
        &MenMainConRl_Top.matanim_joint, "MenMainConRl_Top_matanim_joint",
        &MenMainConRl_Top.shapeanim_joint, "MenMainConRl_Top_shapeanim_joint",

        &MenMainCursorRl_Top.joint, "MenMainCursorRl_Top_joint",
        &MenMainCursorRl_Top.animjoint, "MenMainCursorRl_Top_animjoint",
        &MenMainCursorRl_Top.matanim_joint,
        "MenMainCursorRl_Top_matanim_joint",
        &MenMainCursorRl_Top.shapeanim_joint,
        "MenMainCursorRl_Top_shapeanim_joint",

        &MenMainCursorRl_Top.joint, "MenMainCursorRl_Top_joint",
        &MenMainCursorRl_Top.animjoint, "MenMainCursorRl_Top_animjoint",
        &MenMainCursorRl_Top.matanim_joint,
        "MenMainCursorRl_Top_matanim_joint",
        &MenMainCursorRl_Top.shapeanim_joint,
        "MenMainCursorRl_Top_shapeanim_joint",

        &MenMainNmRl_Top.joint, "MenMainNmRl_Top_joint",
        &MenMainNmRl_Top.animjoint, "MenMainNmRl_Top_animjoint",
        &MenMainNmRl_Top.matanim_joint, "MenMainNmRl_Top_matanim_joint",
        &MenMainNmRl_Top.shapeanim_joint, "MenMainNmRl_Top_shapeanim_joint",

        &MenMainCursorTr01_Top.joint, "MenMainCursorTr01_Top_joint",
        &MenMainCursorTr01_Top.animjoint, "MenMainCursorTr01_Top_animjoint",
        &MenMainCursorTr01_Top.matanim_joint,
        "MenMainCursorTr01_Top_matanim_joint",
        &MenMainCursorTr01_Top.shapeanim_joint,
        "MenMainCursorTr01_Top_shapeanim_joint",

        &MenMainCursorTr02_Top.joint, "MenMainCursorTr02_Top_joint",
        &MenMainCursorTr02_Top.animjoint, "MenMainCursorTr02_Top_animjoint",
        &MenMainCursorTr02_Top.matanim_joint,
        "MenMainCursorTr02_Top_matanim_joint",
        &MenMainCursorTr02_Top.shapeanim_joint,
        "MenMainCursorTr02_Top_shapeanim_joint",

        &MenMainCursorTr03_Top.joint, "MenMainCursorTr03_Top_joint",
        &MenMainCursorTr03_Top.animjoint, "MenMainCursorTr03_Top_animjoint",
        &MenMainCursorTr03_Top.matanim_joint,
        "MenMainCursorTr03_Top_matanim_joint",
        &MenMainCursorTr03_Top.shapeanim_joint,
        "MenMainCursorTr03_Top_shapeanim_joint",

        &MenMainCursorTr04_Top.joint, "MenMainCursorTr04_Top_joint",
        &MenMainCursorTr04_Top.animjoint, "MenMainCursorTr04_Top_animjoint",
        &MenMainCursorTr04_Top.matanim_joint,
        "MenMainCursorTr04_Top_matanim_joint",
        &MenMainCursorTr04_Top.shapeanim_joint,
        "MenMainCursorTr04_Top_shapeanim_joint",

        &MenMainCursorRl01_Top.joint, "MenMainCursorRl01_Top_joint",
        &MenMainCursorRl01_Top.animjoint, "MenMainCursorRl01_Top_animjoint",
        &MenMainCursorRl01_Top.matanim_joint,
        "MenMainCursorRl01_Top_matanim_joint",
        &MenMainCursorRl01_Top.shapeanim_joint,
        "MenMainCursorRl01_Top_shapeanim_joint",

        &MenMainCursorRl02_Top.joint, "MenMainCursorRl02_Top_joint",
        &MenMainCursorRl02_Top.animjoint, "MenMainCursorRl02_Top_animjoint",
        &MenMainCursorRl02_Top.matanim_joint,
        "MenMainCursorRl02_Top_matanim_joint",
        &MenMainCursorRl02_Top.shapeanim_joint,
        "MenMainCursorRl02_Top_shapeanim_joint",

        &MenMainCursorRl03_Top.joint, "MenMainCursorRl03_Top_joint",
        &MenMainCursorRl03_Top.animjoint, "MenMainCursorRl03_Top_animjoint",
        &MenMainCursorRl03_Top.matanim_joint,
        "MenMainCursorRl03_Top_matanim_joint",
        &MenMainCursorRl03_Top.shapeanim_joint,
        "MenMainCursorRl03_Top_shapeanim_joint",

        &MenMainCursorRl04_Top.joint, "MenMainCursorRl04_Top_joint",
        &MenMainCursorRl04_Top.animjoint, "MenMainCursorRl04_Top_animjoint",
        &MenMainCursorRl04_Top.matanim_joint,
        "MenMainCursorRl04_Top_matanim_joint",
        &MenMainCursorRl04_Top.shapeanim_joint,
        "MenMainCursorRl04_Top_shapeanim_joint",

        &MenMainCursorRl05_Top.joint, "MenMainCursorRl05_Top_joint",
        &MenMainCursorRl05_Top.animjoint, "MenMainCursorRl05_Top_animjoint",
        &MenMainCursorRl05_Top.matanim_joint,
        "MenMainCursorRl05_Top_matanim_joint",
        &MenMainCursorRl05_Top.shapeanim_joint,
        "MenMainCursorRl05_Top_shapeanim_joint",

        &MenMainConIs_Top.joint, "MenMainConIs_Top_joint",
        &MenMainConIs_Top.animjoint, "MenMainConIs_Top_animjoint",
        &MenMainConIs_Top.matanim_joint, "MenMainConIs_Top_matanim_joint",
        &MenMainConIs_Top.shapeanim_joint, "MenMainConIs_Top_shapeanim_joint",

        &MenMainCursorIs_Top.joint, "MenMainCursorIs_Top_joint",
        &MenMainCursorIs_Top.animjoint, "MenMainCursorIs_Top_animjoint",
        &MenMainCursorIs_Top.matanim_joint,
        "MenMainCursorIs_Top_matanim_joint",
        &MenMainCursorIs_Top.shapeanim_joint,
        "MenMainCursorIs_Top_shapeanim_joint",

        &MenMainConSs_Top.joint, "MenMainConSs_Top_joint",
        &MenMainConSs_Top.animjoint, "MenMainConSs_Top_animjoint",
        &MenMainConSs_Top.matanim_joint, "MenMainConSs_Top_matanim_joint",
        &MenMainConSs_Top.shapeanim_joint, "MenMainConSs_Top_shapeanim_joint",

        &MenMainCursorSs_Top.joint, "MenMainCursorSs_Top_joint",
        &MenMainCursorSs_Top.animjoint, "MenMainCursorSs_Top_animjoint",
        &MenMainCursorSs_Top.matanim_joint,
        "MenMainCursorSs_Top_matanim_joint",
        &MenMainCursorSs_Top.shapeanim_joint,
        "MenMainCursorSs_Top_shapeanim_joint",

        0);

    mn_804D6BD4 = arg1;
    mn_8022C304();
    mn_8022BCF8();
    mn_8022BEDC(mn_8022BE34());
    mn_80229B2C();
    mn_80229DC0();
    temp_r3 = HSD_GObj_SetupProc(GObj_Create(0, 1, 0x80), fn_8022F538, 0);
    temp_r3->flags_3 = HSD_GObj_804D783C;
    HSD_GObj_80390CD4(mn_80230E38(1));
    lbAudioAx_80023F28(gmMainLib_8015ECB0());
}

bool mn_80231F80(u8 arg0)
{
    if (gm_801A4310() == 0x1B && arg0 == 1) {
        return false;
    }
    if (arg0 == 3) {
        if (gmMainLib_8015EE0C()) {
            return true;
        }
        return false;
    }
    if (arg0 == 5) {
        if (gmMainLib_8015EE44()) {
            return true;
        }
        return false;
    }
    return true;
}
