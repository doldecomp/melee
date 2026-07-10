#include "mnmainrule.h"

#include "mnmain.h"

#include "baselib/gobjgxlink.h"
#include "baselib/gobjobject.h"
#include "baselib/gobjuserdata.h"
#include "gm/gm_1A36.h"
#include "gm/gm_1A3F.h"
#include "gm/gmtoulib.h"

#include <sysdolphin/baselib/debug.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjplink.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/memory.h>
#include <sysdolphin/baselib/sislib.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/lb/lbarchive.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lbspdisplay.h>
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

u8 mn_803EC600[] = {
    0x00, 0x03, 0x00, 0x04, 0x00, 0x05, 0x00, 0x06, 0x00, 0x07, 0x00, 0x08,
    0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x40, 0x00, 0x00, 0x00, 0x40, 0x40, 0x00, 0x00, 0x40, 0xC0, 0x00, 0x00,
    0x40, 0xE0, 0x00, 0x00, 0x41, 0x00, 0x00, 0x00, 0x41, 0x10, 0x00, 0x00,
    0x41, 0x20, 0x00, 0x00, 0x41, 0x30, 0x00, 0x00, 0x41, 0x40, 0x00, 0x00,
    0x41, 0x50, 0x00, 0x00, 0x41, 0x60, 0x00, 0x00, 0x41, 0x70, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x42, 0xC6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x43, 0x47, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x41, 0xC0, 0x00, 0x00, 0xBD, 0xCC, 0xCC, 0xCD,
    0x41, 0xC8, 0x00, 0x00, 0x42, 0x44, 0x00, 0x00, 0xBD, 0xCC, 0xCC, 0xCD,
    0x42, 0x48, 0x00, 0x00, 0x42, 0x94, 0x00, 0x00, 0xBD, 0xCC, 0xCC, 0xCD,
    0x42, 0x96, 0x00, 0x00, 0x42, 0xC6, 0x00, 0x00, 0xBD, 0xCC, 0xCC, 0xCD,
    0x00, 0x00, 0x00, 0x00, 0x42, 0xC6, 0x00, 0x00, 0x42, 0x70, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x41, 0xA0, 0x00, 0x00, 0xBD, 0xCC, 0xCC, 0xCD,
    0x00, 0x00, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00,
    0x40, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x80, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x40, 0xC0, 0x00, 0x00, 0x40, 0xE0, 0x00, 0x00,
    0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x41, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x41, 0x20, 0x00, 0x00,
    0x41, 0x30, 0x00, 0x00, 0x41, 0x40, 0x00, 0x00, 0x41, 0x50, 0x00, 0x00,
    0x41, 0x60, 0x00, 0x00, 0x41, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x41, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

AnimLoopSettings mn_803EC734[5] = {
    { 0.0F, 3.0F, -0.1F },   { 20.0F, 23.0F, -0.1F }, { 40.0F, 43.0F, -0.1F },
    { 60.0F, 63.0F, -0.1F }, { 80.0F, 83.0F, -0.1F },
};

AnimLoopSettings mn_803EC770[9] = {
    { 100.0F, 103.0F, -0.1F }, { 120.0F, 123.0F, -0.1F },
    { 140.0F, 143.0F, -0.1F }, { 160.0F, 163.0F, -0.1F },
    { 180.0F, 183.0F, -0.1F }, { 30.0F, 49.0F, -0.1F },
    { 70.0F, 89.0F, -0.1F },   { 90.0F, 109.0F, -0.1F },
    { 50.0F, 69.0F, -0.1F },
};

u8 mn_803EC7DC[8][2] = {
    { 0, 3 }, { 0, 0x63 }, { 0, 2 }, { 5, 0x14 },
    { 0, 4 }, { 0, 0 },    { 0, 0 }, { 0, 0 },
};

static StaticModelDesc* mn_803EC7EC[7] = {
    &MenMainCursorRl01_Top,
    &MenMainCursorRl02_Top,
    &MenMainCursorRl03_Top,
    &MenMainCursorRl04_Top,
    &MenMainCursorRl05_Top,
    NULL,
    NULL,
};

static u16 mn_803EC808[8] = { 2, 9, 2, 4, 2, 0, 0, 0 };

struct mn_803EC818_t mn_803EC818[7] = {
    { 0x26, { 0x27, 0x28, 0x29, 0x00 } }, { 0x2A, { 0x00, 0x00, 0x00, 0x00 } },
    { 0x2D, { 0x2E, 0x2C, 0x00, 0x00 } }, { 0x2F, { 0x00, 0x00, 0x00, 0x00 } },
    { 0x30, { 0x31, 0x32, 0x33, 0x34 } }, { 0x35, { 0x00, 0x00, 0x00, 0x00 } },
    { 0x36, { 0x00, 0x00, 0x00, 0x00 } },
};

f32 mn_804D4B88 = 4.0F;
f32 lbl_804D4B8C = 5.0F;
f32 mn_804D4B90 = 1.0F;
u8 mn_804D4B94[4] = { 1, 0x63, 0x2B, 0 };

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
extern u8 mn_803EC7DC[][2];
extern u8 mn_803EC600[];
extern s32 mn_804D6BD4;

void mnItemSw_802358C0(void);
void mn_802339FC(void);
void mnCharSel_80264070(void);
void mnCharSel_802640A0(void);

static inline u8 mn_8022F538_GetHoveredSelection(void)
{
    return mn_804A04F0.hovered_selection;
}

void fn_8022F538(HSD_GObj* arg0)
{
    struct mn_802307F8_t* data;
    GameRules* rules;
    u8* limits;
    u32 buttons;
    s32 valid;
    u8 hovered;

    PAD_STACK(0x20);

    data = HSD_GObjGetUserData(mn_804D6BD0);
    buttons = mn_80229624(4);
    mn_804A04F0.buttons = buttons;
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
            data = HSD_GObjGetUserData(mn_804D6BD0);
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
        switch ((s32) gm_801A4310()) {
        case 1:
            data = mn_804D6BD0->user_data;
            rules = gmMainLib_8015CC34();
            rules->mode = data->x2;
            rules->time_limit = data->x3;
            rules->handicap = data->x4;
            rules->damage_ratio = data->x5;
            rules->unk_x7 = data->x6;
            rules->stock_count = data->x9;
            mn_80229860(2);
            return;
        default:
            data = mn_804D6BD0->user_data;
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
    }
    if ((buttons & 0x20) != 0) {
        lbAudioAx_80024030(0);
        mn_804A04F0.entering_menu = 0;
        data = mn_804D6BD0->user_data;
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
            if ((s32) mn_804A04F0.hovered_selection == 0) {
                mn_804A04F0.hovered_selection = 6;
            } else {
                mn_804A04F0.hovered_selection--;
            }
            hovered = mn_8022F538_GetHoveredSelection();
            if (gm_801A4310() == 0x1B && hovered == 4) {
                valid = 0;
            } else {
                valid = 1;
            }
        } while (valid == 0);
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
            if ((s32) mn_804A04F0.hovered_selection == 6) {
                mn_804A04F0.hovered_selection = 0;
            } else {
                mn_804A04F0.hovered_selection++;
            }
            hovered = mn_8022F538_GetHoveredSelection();
            if (gm_801A4310() == 0x1B && hovered == 4) {
                valid = 0;
            } else {
                valid = 1;
            }
        } while (valid == 0);
        if (mn_804A04F0.hovered_selection == 1 && data->x2 == 1) {
            mn_804A04F0.confirmed_selection = data->x9;
            return;
        }
        mn_804A04F0.confirmed_selection =
            ((u8*) data)[mn_804A04F0.hovered_selection + 2];
        return;
    }

    if (mn_804A04F0.hovered_selection == 5 ||
        mn_804A04F0.hovered_selection == 6)
    {
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
    u8* var_r29;
    HSD_JObj* temp_r29_2;
    HSD_JObj* temp_r29_3;
    int new_var;
    HSD_JObj* temp_r31;
    HSD_JObj* temp_r28;
    HSD_JObj* temp_r29;
    s32 var_r28;
    u8* var_r29_2;
    HSD_JObj** temp_r27_2;
    s32 var_r27;

    sp14 = mn_804DBDFC;
    if (arg0 == 0) {
        HSD_JObj* temp_r27;
        var_r27 = 0;
        var_r29 = (u8*) &sp14;
        do {
            HSD_JObjSetFlagsAll(data->x58[*var_r29], JOBJ_HIDDEN);
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
        HSD_JObjClearFlagsAll(data->x58[*var_r29_2], JOBJ_HIDDEN);
        var_r28 += 1;
        var_r29_2 += 1;
    } while (var_r28 < 4);
    temp_r28 = data->x58[4];
    HSD_JObjReqAnimAll(temp_r28, mn_804D6BD8);
    HSD_JObjAnimAll(temp_r28);
    temp_r27_2 = data->x58;
    temp_r27_2 = data->x58;
    new_var = arg0;
    temp_r31 = temp_r27_2[2];
    HSD_JObjReqAnimAll(temp_r31, (f32) (u8) (new_var / 10));
    HSD_JObjAnimAll(temp_r31);
    temp_r29 = temp_r27_2[3];
    HSD_JObjReqAnimAll(temp_r29, (f32) (u8) (new_var % 10));
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
    struct {
        s32 time_digits;
        u8 time_digit_extra;
        u8 pad_5[3];
        u16 stock_digits;
        u8 pad_A[8];
    } indices;
    HSD_JObj** jobjs;
    HSD_JObj* jobj;
    struct mn_8022FB88_arg1_t* data;
    s32 i;
    u8* ptr0;
    u8* ptr1;
    u8* ptr2;
    u8* ptr3;
    struct mn_8022FB88_arg1_t* data2;
    u8 val;

    data = mn_804D6BD0->user_data;
    indices.time_digits = mn_804DBE08;
    data2 = data;
    indices.stock_digits = mn_804DBE04;
    indices.time_digit_extra = mn_804DBE0C;
    if (arg0 != 0) {
        i = 0;
        ptr0 = (u8*) &indices.stock_digits;
        do {
            HSD_JObjSetFlagsAll(data->x58[*ptr0], JOBJ_HIDDEN);
            i += 1;
            ptr0 += 1;
        } while (i < 2);
        i = 0;
        ptr1 = (u8*) &indices.time_digits;
        do {
            HSD_JObjClearFlagsAll(data->x58[*ptr1], JOBJ_HIDDEN);
            i += 1;
            ptr1 += 1;
        } while (i < 5);
        mn_8022FB88(data2->x3, data2);
        return;
    }
    i = 0;
    ptr2 = (u8*) &indices.stock_digits;
    do {
        HSD_JObjClearFlagsAll(data->x58[*ptr2], JOBJ_HIDDEN);
        i += 1;
        ptr2 += 1;
    } while (i < 2);
    i = 0;
    ptr3 = (u8*) &indices.time_digits;
    do {
        HSD_JObjSetFlagsAll(data->x58[*ptr3], JOBJ_HIDDEN);
        i += 1;
        ptr3 += 1;
    } while (i < 5);
    val = data->x9;
    jobjs = data->x58;
    jobj = jobjs[7];
    HSD_JObjReqAnimAll(jobj, (f32) (u8) (data->x9 / 10));
    HSD_JObjAnimAll(jobj);
    jobj = jobjs[8];
    HSD_JObjReqAnimAll(jobj, (f32) (u8) (val % 10));
    HSD_JObjAnimAll(jobj);
}

void mn_8022FEC8(HSD_GObj* arg0, HSD_JObj* arg1, u8 arg2, u8 arg3)
{
    struct mn_8022FB88_arg1_t* data;
    HSD_JObj* digit_jobj;
    HSD_JObj* tens_jobj;
    HSD_JObj* ones_jobj;
    f32* frame;
    HSD_JObj** digit_jobjs;
    struct mn_8022FEC8_jobj_ref_t* tens_ref;
    struct mn_8022FEC8_jobj_ref_t* ones_ref;
    u8* base;

    PAD_STACK(0x18);

    data = arg0->user_data;
    base = mn_803EC600;
    switch ((s32) arg2) {
    case 1:
        if (((struct mn_8022FB88_arg1_t*) mn_804D6BD0->user_data)->x2 != 1) {
            mn_8022FB88(arg3, data);
            return;
        }
        digit_jobjs = data->x58;
        digit_jobj = digit_jobjs[7];
        HSD_JObjReqAnimAll(digit_jobj, (f32) (u8) (arg3 / 10));
        HSD_JObjAnimAll(digit_jobj);
        digit_jobj = digit_jobjs[8];
        HSD_JObjReqAnimAll(digit_jobj, (f32) (u8) (arg3 % 10));
        HSD_JObjAnimAll(digit_jobj);
        return;
    case 3:
        tens_ref = data->xA8;
        if (tens_ref == NULL) {
            tens_jobj = NULL;
        } else {
            tens_jobj = tens_ref->x10;
        }
        HSD_JObjReqAnimAll(tens_jobj, (f32) (u8) (arg3 / 10));
        HSD_JObjAnimAll(tens_jobj);
        ones_ref = data->xAC;
        if (ones_ref == NULL) {
            ones_jobj = NULL;
        } else {
            ones_jobj = ones_ref->x10;
        }
        HSD_JObjReqAnimAll(ones_jobj, (f32) (u8) (arg3 % 10));
        HSD_JObjAnimAll(ones_jobj);
        return;
    case 0:
    case 2:
    case 4:
        break;
    case 5:
    case 6:
    default:
        return;
    }

    frame = NULL;
    if ((mn_804A04F0.buttons & 4) != 0) {
        if (arg2 == 0 || arg2 == 2 || arg2 == 4) {
            frame = (f32*) (base + 0x170 +
                            (0xC * (base[0x1DD + (arg2 << 1)] - arg3)));
        }
        HSD_JObjReqAnimAll(arg1, *frame);
    } else {
        if (arg2 == 0 || arg2 == 2 || arg2 == 4) {
            if (arg3 == 0) {
                frame =
                    (f32*) (base + 0x134 + (0xC * base[0x1DD + (arg2 << 1)]));
                (void) frame;
            } else {
                frame = (f32*) (base + 0x134 + (0xC * (arg3 - 1)));
            }
        }
        HSD_JObjReqAnimAll(arg1, *frame);
    }
    HSD_JObjAnimAll(arg1);
}

void mn_80230198(HSD_GObj* gobj, HSD_JObj* jobj, u8 mode)
{
    AnimLoopSettings* settings;
    f32 frame;
    int i;
    PAD_STACK(8);

    switch (mode) {
    case 0:
    case 2:
    case 4:
        frame = mn_8022F298(jobj);
        for (i = 0; i < 5; i++) {
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
        break;
    case 1:
    case 3:
    case 5:
    case 6:
        break;
    }
}

extern MenuKindData mn_803EB6B0[];
extern u8 mn_804D4B96;
extern struct mn_803EC818_t mn_803EC818[];
extern f32 mn_804DBE18;
extern f32 mn_804DBE1C;
extern f32 mn_804DBE20;
extern f32 mn_804DBE24;
extern f32 mn_804DBE28;
extern f32 mn_804DBE2C;
extern s32 mn_804D6BD4;

void mn_80230274(HSD_GObj* arg0, int arg1, int arg2)
{
    HSD_JObj* option_roots[8];
    HSD_JObj* roots[17];
    u16 indices[19];
    u8* base;
    struct mn_802307F8_t* data;
    u8* data8;
    u8 count;
    u8 selected;
    u8 hovered;
    s32 i;
    s32 j;
    s32 visible;
    s32 valid;
    u16* idx;
    AnimLoopSettings* settings;
    HSD_JObj* jobj;

    PAD_STACK(0x28);

    base = mn_803EC600;
    count = mn_803EB6B0[13].selection_count;
    data = arg0->user_data;
    data8 = arg0->user_data;
    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;
    indices[3] = 3;
    indices[4] = 4;
    indices[5] = 5;
    indices[6] = 6;
    indices[7] = 7;
    indices[8] = 8;
    indices[9] = 9;
    indices[10] = 10;
    indices[11] = 11;
    indices[12] = 12;
    indices[13] = 13;
    indices[14] = 14;
    indices[15] = 15;
    i = 16;
    idx = &indices[i];
    while (i < 0x11) {
        *idx = i;
        idx++;
        i++;
    }

    for (i = 0; i < count; i++) {
        if (gm_801A4310() == 0x1B && (u8) i == 4) {
            valid = 0;
        } else {
            valid = 1;
        }
        if (valid != 0) {
            visible = 0;
            for (j = 0; j < i; j++) {
                if (gm_801A4310() == 0x1B && (u8) j == 4) {
                    valid = 0;
                } else {
                    valid = 1;
                }
                if (valid != 0) {
                    visible++;
                }
            }
            if (data->xC[((u16*) base)[(u8) visible]] == NULL) {
                option_roots[i] = NULL;
            } else {
                option_roots[i] = ((struct mn_8022FEC8_jobj_ref_t*)
                                       data->xC[((u16*) base)[(u8) visible]])
                                      ->x10;
            }
        }
    }

    if (arg1 != 0) {
        selected = data->x1;
        lb_8001204C(option_roots[selected], roots, indices, 0x11);
        HSD_JObjSetFlagsAll(roots[16], JOBJ_HIDDEN);
        HSD_JObjSetFlagsAll(roots[13], JOBJ_HIDDEN);
        jobj = roots[2];
        if ((u8) (selected - 5) <= 1) {
            HSD_JObjReqAnimAll(jobj, *(f32*) (base + 0x78));
        } else {
            HSD_JObjReqAnimAll(jobj, *(f32*) (base + 0x60));
        }
        HSD_JObjAnimAll(jobj);
        jobj = roots[7];
        if (selected == 1 &&
            ((struct mn_8022FB88_arg1_t*) mn_804D6BD0->user_data)->x2 == 1)
        {
            HSD_JObjReqAnim(jobj, mn_804D4B88);
        } else {
            HSD_JObjReqAnim(jobj, *(f32*) (base + 0x10 + selected * 8));
        }
        HSD_JObjAnim(jobj);
        HSD_JObjSetFlagsAll(roots[8], JOBJ_HIDDEN);

        hovered = mn_804A04F0.hovered_selection;
        lb_8001204C(option_roots[hovered], roots, indices, 0x11);
        HSD_JObjClearFlagsAll(roots[16], JOBJ_HIDDEN);
        HSD_JObjReqAnimAll(roots[16], *(f32*) (base + 0x48));
        if (hovered != 5 && hovered != 6) {
            HSD_JObjClearFlagsAll(roots[13], JOBJ_HIDDEN);
            HSD_JObjReqAnimAll(roots[13], *(f32*) (base + 0x54));
            HSD_JObjReqAnimAll(roots[2], *(f32*) (base + 0x6C));
            HSD_JObjAnimAll(roots[2]);
        } else {
            HSD_JObjReqAnimAll(roots[2], *(f32*) (base + 0x84));
            HSD_JObjAnimAll(roots[2]);
        }
        if (hovered == 1 &&
            ((struct mn_8022FB88_arg1_t*) mn_804D6BD0->user_data)->x2 == 1)
        {
            HSD_JObjReqAnim(roots[7], lbl_804D4B8C);
        } else {
            HSD_JObjReqAnim(roots[7], *(f32*) (base + 0x14 + hovered * 8));
        }
        HSD_JObjAnim(roots[7]);
        if ((u8) (hovered - 5) <= 1) {
            HSD_JObjClearFlagsAll(roots[8], JOBJ_HIDDEN);
            HSD_JObjReqAnimAll(roots[8], *(f32*) (base + 0x90));
            HSD_JObjAnimAll(roots[8]);
        }
    }

    if (arg2 != 0) {
        mn_8022FEC8(arg0, data->x34[mn_804A04F0.hovered_selection].x0,
                    mn_804A04F0.hovered_selection,
                    mn_804A04F0.confirmed_selection);
    }

    for (i = 0; i < count; i++) {
        u16 focus;

        if (gm_801A4310() == 0x1B && (u8) i == 4) {
            valid = 0;
        } else {
            valid = 1;
        }
        if (valid != 0) {
            lb_8001204C(option_roots[i], roots, indices, 0x11);
            if (arg1 != 0) {
                focus = mn_804A04F0.hovered_selection;
            } else {
                focus = data->x1;
            }
            if (i == focus) {
                mn_8022ED6C(roots[16], (AnimLoopSettings*) (base + 0x48));
            }
            if (i == focus && i != 5 && i != 6) {
                mn_8022ED6C(roots[13], (AnimLoopSettings*) (base + 0x54));
            }
            if ((u32) (i - 5) <= 1) {
                settings =
                    (AnimLoopSettings*) (base + (((u8) (i == focus)) * 0xC) +
                                         0x78);
            } else {
                settings =
                    (AnimLoopSettings*) (base + (((u8) (i == focus)) * 0xC) +
                                         0x60);
            }
            mn_8022ED6C(roots[2], settings);
            mn_8022ED6C(roots[8], (AnimLoopSettings*) (base + 0x90));
            mn_80230198(arg0, data->x34[i].x0, i);
            if (i == 1 && arg2 != 0 && focus == 0) {
                if (mn_804A04F0.confirmed_selection == 1) {
                    HSD_JObjReqAnim(roots[7], mn_804D4B88);
                } else {
                    HSD_JObjReqAnim(roots[7], *(f32*) (base + 0x18));
                }
                HSD_JObjAnim(roots[7]);
                mn_8022FD18((u8) (mn_804A04F0.confirmed_selection != 1));
            }
        }
    }
}

void mn_802307F8(struct mn_802307F8_t* arg0, s32 arg1, s32 arg2)
{
    HSD_Text* text;
    u8 text_id;

    if (arg0->text != NULL) {
        HSD_SisLib_803A5CC4(arg0->text);
        arg0->text = NULL;
    }
    if ((arg1 == 1) && ((u8) arg0->x2 == 1)) {
        text_id = mn_804D4B96;
    } else if ((arg1 == 1) || (arg1 == 3) || ((u32) (arg1 - 5) <= 1U)) {
        text_id = mn_803EC818[arg1].x0;
    } else {
        text_id = *(&mn_803EC818[arg1].x0 + arg2);
    }
    text = HSD_SisLib_803A5ACC(0, 1, mn_804DBE18, mn_804DBE1C, mn_804DBE20,
                               mn_804DBE24, mn_804DBE28);
    arg0->text = text;
    text->font_size.y = text->font_size.x = mn_804DBE2C;
    HSD_SisLib_803A6368(text, text_id);
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
        if (arg1 != 0 || (arg2 != 0 && (kind == 0 || kind == 2 || kind == 4)))
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
    AnimLoopSettings* anim;
    u8* ptr;
    s32 update_menu;
    s32 update_selection;
    s32 update_value;
    u8 state;
    struct mn_802307F8_t* data;

    PAD_STACK(0x18);

    update_menu = 0;
    update_selection = 0;
    update_value = 0;
    data = arg0->user_data;
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
            anim = &mn_803EC770[5];
            break;
        case 2:
            anim = &mn_803EC770[7];
            break;
        case 3:
            anim = &mn_803EC770[6];
            break;
        case 4:
            anim = &mn_803EC770[8];
            break;
        }
        HSD_JObjReqAnim(jobj, anim->start_frame);
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
            anim = &mn_803EC770[5];
            break;
        case 2:
            anim = &mn_803EC770[7];
            break;
        case 3:
            anim = &mn_803EC770[6];
            break;
        case 4:
            anim = &mn_803EC770[8];
            break;
        }
        if (mn_8022F298(jobj) >= anim->end_frame) {
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
        }
        HSD_JObjAnim(jobj);
    }

    if (data->xA == 0 || data->xA == 1 || data->xA == 3) {
        update_selection = data->x1 != mn_804A04F0.hovered_selection;
        if (mn_804A04F0.hovered_selection == 1 && data->x2 == 1) {
            if (data->x9 != mn_804A04F0.confirmed_selection) {
                update_value = 1;
            }
        } else {
            ptr = (u8*) data;
            ptr += mn_804A04F0.hovered_selection;
            if (ptr[2] != mn_804A04F0.confirmed_selection) {
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
            state = mn_804A04F0.confirmed_selection;
            ptr = (u8*) data;
            ptr += data->x1;
            ptr[2] = state;
        }
        data = arg0->user_data;
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

s32 mn_80230D18(struct mn_802307F8_t* arg0, HSD_JObj* arg1, s8 arg2)
{
    GameRules* rules;
    s32 ret;
    s32 i;

    arg0->x0 = mn_804A04F0.cur_menu;
    arg0->x1 = mn_804A04F0.hovered_selection;

    rules = gmMainLib_8015CC34();
    arg0->x4 = rules->handicap;
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
    arg0->text = 0;

    ret = 0;
    for (i = 0; i < 10; i++) {
        ret = lb_80011E24(arg1, &arg0->xC[i], i, -1);
    }
    return ret;
}

HSD_GObj* mn_80230E38(int arg0)
{
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    u16 indices[17];
    HSD_JObj* roots[17];
    StaticModelDesc** descs;
    AnimLoopSettings* settings;
    struct mn_802307F8_t* user_data;
    HSD_JObj* parent;
    u16* count_ptr;
    f32* cursor_frames;
    u16* idx;
    u8* data8;
    u8* data_curr;
    u8* p;
    u8 mode;
    u8 count;
    u8 hovered;
    s32 i;
    s32 j;
    s32 visible;
    s32 valid;
    s32 total_visible;

    PAD_STACK(0x40);
    mode = arg0;
    hovered = mn_804A04F0.hovered_selection;
    count = mn_803EB6B0[13].selection_count;
    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;
    indices[3] = 3;
    indices[4] = 4;
    indices[5] = 5;
    indices[6] = 6;
    indices[7] = 7;
    indices[8] = 8;
    indices[9] = 9;
    indices[10] = 10;
    indices[11] = 11;
    indices[12] = 12;
    indices[13] = 13;
    indices[14] = 14;
    indices[15] = 15;
    i = 16;
    idx = &indices[i];
    while (i < 0x11) {
        *idx = i;
        idx++;
        i++;
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

    user_data = (struct mn_802307F8_t*) HSD_MemAlloc(sizeof(*user_data));
    HSD_ASSERTREPORT(0x575, user_data, "Can't get user_data.\n");
    GObj_InitUserData(gobj, 0, HSD_Free, user_data);
    mn_80230D18(user_data, jobj, mode);
    data8 = (u8*) user_data;
    if (user_data->x1 == 1 &&
        ((struct mn_8022FB88_arg1_t*) mn_804D6BD0->user_data)->x2 == 1)
    {
        mn_804A04F0.confirmed_selection = user_data->x9;
    } else {
        mn_804A04F0.confirmed_selection = data8[user_data->x1 + 2];
    }

    if (mode != 0) {
        jobj = user_data->xC[2];
        switch ((s32) user_data->xA) {
        case 1:
            settings = (AnimLoopSettings*) (mn_803EC600 + 0x1AC);
            break;
        case 3:
            settings = (AnimLoopSettings*) (mn_803EC600 + 0x1B8);
            break;
        }
        HSD_JObjReqAnim(jobj, settings->start_frame);
        HSD_JObjAnim(jobj);
    }

    descs = (StaticModelDesc**) (mn_803EC600 + 0x1EC);
    (void) descs;
    count_ptr = (u16*) (mn_803EC600 + 0x208);
    cursor_frames = (f32*) (mn_803EC600 + 0x10);
    data_curr = data8;
    for (i = 0; i < count;
         cursor_frames += 2, descs++, data_curr += 0x24, count_ptr++, i++)
    {
        visible = 0;
        for (j = 0; j < i; j++) {
            if (gm_801A4310() == 0x1B && (u8) j == 4) {
                valid = 0;
            } else {
                valid = 1;
            }
            if (valid != 0) {
                visible++;
            }
        }
        parent = user_data->xC[((u16*) mn_803EC600)[(u8) visible]];
        total_visible = 0;
        for (j = 0; j < 7; j++) {
            if (gm_801A4310() == 0x1B && (u8) j == 4) {
                valid = 0;
            } else {
                valid = 1;
            }
            if (valid != 0) {
                total_visible++;
            }
        }

        HSD_JObjReqAnim(parent, (f32) total_visible);
        HSD_JObjAnim(parent);

        if (gm_801A4310() == 0x1B && (u8) i == 4) {
            valid = 0;
        } else {
            valid = 1;
        }
        if (valid != 0) {
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
                HSD_JObjReqAnim(roots[7], cursor_frames[(u8) (i == hovered)]);
            }
            HSD_JObjAnim(roots[7]);
            if (hovered != i) {
                HSD_JObjSetFlagsAll(roots[16], JOBJ_HIDDEN);
            }
            if (hovered != i || (u32) (i - 5) <= 1U) {
                HSD_JObjSetFlagsAll(roots[13], JOBJ_HIDDEN);
            }
            if ((u32) (i - 5) <= 1U) {
                settings =
                    (AnimLoopSettings*) (mn_803EC600 +
                                         ((u8) (hovered == i) * 0xC) + 0x78);
            } else {
                settings =
                    (AnimLoopSettings*) (mn_803EC600 +
                                         ((u8) (hovered == i) * 0xC) + 0x60);
            }
            HSD_JObjReqAnimAll(roots[2], settings->start_frame);
            HSD_JObjAnimAll(roots[2]);
            if (hovered != i || (i != 5 && i != 6)) {
                HSD_JObjSetFlagsAll(roots[8], JOBJ_HIDDEN);
            }
            HSD_JObjAddChild(parent, jobj);

            if ((u32) (i - 5) > 1U) {
                jobj = HSD_JObjLoadJoint((*descs)->joint);
                HSD_JObjAddAnimAll(jobj, (*descs)->animjoint,
                                   (*descs)->matanim_joint,
                                   (*descs)->shapeanim_joint);
                HSD_JObjReqAnimAll(jobj, mn_804DBE00);
                HSD_JObjAnimAll(jobj);
                for (j = 0; j < *count_ptr; j++) {
                    lb_80011E24(jobj, (HSD_JObj**) (data_curr + 0x34 + j * 4),
                                j, -1);
                }

                switch (i) {
                case 1: {
                    struct {
                        u32 bytes4;
                        u16 bytes2;
                    } bytes;

                    bytes.bytes4 = mn_804DBE10;
                    bytes.bytes2 = mn_804DBE14;
                    p = (u8*) &bytes.bytes4;
                    for (j = 0; j < 6; j++) {
                        HSD_JObj* text =
                            HSD_JObjLoadJoint(MenMainNmRl_Top.joint);
                        HSD_JObjAddAnimAll(text, MenMainNmRl_Top.animjoint,
                                           MenMainNmRl_Top.matanim_joint,
                                           MenMainNmRl_Top.shapeanim_joint);
                        HSD_JObjAddChild(
                            *(HSD_JObj**) (data8 + 0x58 + p[j] * 4), text);
                    }
                    mn_8022FD18((u8) (((struct mn_8022FB88_arg1_t*)
                                           mn_804D6BD0->user_data)
                                          ->x2 != 1));
                    break;
                }
                case 3: {
                    u8 value = user_data->x5;
                    u16 bytes2;

                    bytes2 = mn_804DBDF8;
                    p = (u8*) &bytes2;
                    for (j = 0; j < 2; j++) {
                        HSD_JObj* text =
                            HSD_JObjLoadJoint(MenMainNmRl_Top.joint);
                        HSD_JObjAddAnimAll(text, MenMainNmRl_Top.animjoint,
                                           MenMainNmRl_Top.matanim_joint,
                                           MenMainNmRl_Top.shapeanim_joint);
                        HSD_JObjAddChild(
                            *(HSD_JObj**) (data8 + 0xA0 + p[j] * 4), text);
                    }
                    {
                        HSD_JObj* digit_jobj = (HSD_JObj*) mn_80231634(
                            *(struct mn_80231634_t**) (data8 + 0xA8));
                        HSD_JObjReqAnimAll(digit_jobj,
                                           (f32) (u8) (value / 10));
                        HSD_JObjAnimAll(digit_jobj);
                        digit_jobj = (HSD_JObj*) mn_80231634(
                            *(struct mn_80231634_t**) (data8 + 0xAC));
                        HSD_JObjReqAnimAll(digit_jobj,
                                           (f32) (u8) (value % 10));
                        HSD_JObjAnimAll(digit_jobj);
                    }
                    break;
                }
                case 0:
                case 2:
                case 4: {
                    u8 value = data8[i + 2];

                    if ((u8) i != 0 && (u8) i != 2 && (u8) i != 4) {
                        settings = NULL;
                    } else if (value == 0) {
                        settings =
                            (AnimLoopSettings*) (mn_803EC600 +
                                                 (*((u8*) (mn_803EC600 +
                                                           0x1DD + i * 2)) *
                                                  0xC) +
                                                 0x134);
                    } else {
                        settings =
                            (AnimLoopSettings*) (mn_803EC600 +
                                                 ((value - 1) * 0xC) + 0x134);
                    }
                    HSD_JObjReqAnimAll(*(HSD_JObj**) (data_curr + 0x34),
                                       settings->end_frame);
                    HSD_JObjAnimAll(*(HSD_JObj**) (data_curr + 0x34));
                    break;
                }
                }

                HSD_JObjAddChild(parent, jobj);
            }
        }
    }

    mn_802307F8(user_data, user_data->x1, mn_804A04F0.confirmed_selection);
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

    PAD_STACK(4);

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
