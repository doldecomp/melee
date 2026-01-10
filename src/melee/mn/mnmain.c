#include "mnmain.h"

#include "mn/forward.h"

#include <math.h>
#include <trigf.h>
#include <sysdolphin/baselib/controller.h>
#include <sysdolphin/baselib/displayfunc.h>
#include <sysdolphin/baselib/dobj.h>
#include <sysdolphin/baselib/fog.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjobject.h>
#include <sysdolphin/baselib/gobjplink.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/lobj.h>
#include <sysdolphin/baselib/mobj.h>
#include <melee/gm/gm_unsplit.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/gm/types.h>
#include <melee/lb/lb_00B0.h>
#include <melee/lb/lb_00CE.h>
#include <melee/lb/lbarchive.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lbcardgame.h>
#include <melee/lb/lbcardnew.h>
#include <melee/lb/lblanguage.h>
#include <melee/lb/lbmthp.h>
#include <melee/mn/inlines.h>
#include <melee/mn/mncharsel.h>
#include <melee/mn/mncount.h>
#include <melee/mn/mndatadel.h>
#include <melee/mn/mndeflicker.h>
#include <melee/mn/mndiagram.h>
#include <melee/mn/mnevent.h>
#include <melee/mn/mngallery.h>
#include <melee/mn/mnhyaku.h>
#include <melee/mn/mninfo.h>
#include <melee/mn/mninfobonus.h>
#include <melee/mn/mnlanguage.h>
#include <melee/mn/mnmainrule.h>
#include <melee/mn/mnname.h>
#include <melee/mn/mnsnap.h>
#include <melee/mn/mnsound.h>
#include <melee/mn/mnsoundtest.h>
#include <melee/mn/mnvibration.h>
#include <melee/sc/types.h>

static HSD_GObj* mn_804D6BA8;
static HSD_GObj* mn_804D6BAC;
static HSD_GObj* mn_804D6BB0;
MenuInputState mn_804D6BC8;
HSD_CObjDesc* MenMain_cam;
HSD_FogDesc* MenMain_fog;
LightList** MenMain_lights;
HSD_Archive* mn_804D6BB8;
u8 mn_804D6BB5;
u8 mn_804D6BB4;

MenuFlow mn_804A04F0;

static u16 mn_803EAE68[] = {
    0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xA, 0xB, 0xC, 0xD,
};
static u16 mn_803EAE7C[] = {
    0x2, 0x3, 0x4, 0x9, 0xB, 0xC, 0xD, 0x0,
};
static AnimLoopSettings mn_803EAE8C[0x22][3] = {
    {
        { 0, 99, 0 },
        { 0, 0, 0 },
        { 100, 199, 100 },
    },
    {
        { 200, 249, 200 },
        { 250, 299, 250 },
        { 300, 399, 300 },
    },
    {
        { 400, 449, 400 },
        { 450, 499, 450 },
        { 500, 599, 500 },
    },
    {
        { 600, 649, 600 },
        { 650, 699, 650 },
        { 700, 799, 700 },
    },
    {
        { 800, 849, 800 },
        { 850, 899, 850 },
        { 900, 999, 900 },
    },
    {
        { 1000, 1049, 1000 },
        { 1050, 1099, 1050 },
        { 1100, 1199, 1100 },
    },
    {
        { 1200, 1249, 1220 },
        { 1250, 1299, 1270 },
        { 1300, 1399, 1320 },
    },
    {
        { 1400, 1449, 1420 },
        { 1450, 1499, 1470 },
        { 1500, 1599, 1520 },
    },
    {
        { 1600, 1649, 1620 },
        { 1650, 1699, 1670 },
        { 1700, 1799, 1720 },
    },
    {
        { 1800, 1849, 1820 },
        { 1850, 1899, 1870 },
        { 1900, 1999, 1920 },
    },
    {
        { 2000, 2049, 2020 },
        { 2050, 2099, 2070 },
        { 2100, 2199, 2120 },
    },
    {
        { 2400, 2449, 2420 },
        { 2450, 2499, 2470 },
        { 2500, 2599, 2520 },
    },
    {
        { 2600, 2649, 2620 },
        { 2650, 2699, 2670 },
        { 2700, 2799, 2720 },
    },
    {
        { 2800, 2849, 2820 },
        { 2850, 2899, 2870 },
        { 2900, 2999, 2920 },
    },
    {
        { 3000, 3049, 3020 },
        { 3050, 3099, 3070 },
        { 3100, 3199, 3120 },
    },
    {
        { 6200, 6249, 6220 },
        { 6250, 6299, 6270 },
        { 6300, 6399, 6320 },
    },
    {
        { 6000, 6049, 6020 },
        { 6050, 6099, 6070 },
        { 6100, 6199, 6120 },
    },
    {
        { 6400, 6449, 6420 },
        { 6450, 6499, 6470 },
        { 6500, 6599, 6520 },
    },
    {
        { 3000, 3049, 3020 },
        { 3050, 3099, 3070 },
        { 3100, 3199, 3120 },
    },
    {
        { 3200, 3249, 3220 },
        { 3250, 3299, 3270 },
        { 3300, 3399, 3320 },
    },
    {
        { 3400, 3449, 3420 },
        { 3450, 3499, 3470 },
        { 3500, 3599, 3520 },
    },
    {
        { 3600, 3649, 3620 },
        { 3650, 3699, 3670 },
        { 3700, 3799, 3720 },
    },
    {
        { 3800, 3849, 3820 },
        { 3850, 3899, 3870 },
        { 3900, 3999, 3920 },
    },
    {
        { 4000, 4049, 4020 },
        { 4050, 4099, 4070 },
        { 4100, 4199, 4120 },
    },
    {
        { 4200, 4249, 4220 },
        { 4250, 4299, 4270 },
        { 4300, 4399, 4320 },
    },
    {
        { 4400, 4449, 4420 },
        { 4450, 4499, 4470 },
        { 4500, 4599, 4520 },
    },
    {
        { 4600, 4649, 4620 },
        { 4650, 4699, 4670 },
        { 4700, 4799, 4720 },
    },
    {
        { 4800, 4849, 4820 },
        { 4850, 4899, 4870 },
        { 4900, 4999, 4920 },
    },
    {
        { 5000, 5049, 5020 },
        { 5050, 5099, 5070 },
        { 5100, 5199, 5120 },
    },
    {
        { 5200, 5249, 5220 },
        { 5250, 5299, 5270 },
        { 5300, 5399, 5320 },
    },
    {
        { 7400, 7449, 7420 },
        { 7450, 7499, 7470 },
        { 7500, 7599, 7520 },
    },
    {
        { 7600, 7649, 7620 },
        { 7650, 7699, 7670 },
        { 7700, 7799, 7720 },
    },
    {
        { 7800, 7849, 7820 },
        { 7850, 7899, 7870 },
        { 7900, 7999, 7920 },
    },
    {
        { 5800, 5849, 5820 },
        { 5850, 5899, 5870 },
        { 5900, 5999, 5920 },
    },
};

static AnimLoopSettings mn_803EB354 = { 0, 799, 0 };
static AnimLoopSettings mn_803EB360[2] = {
    { 0, 49, 0 },
    { 50, 99, 50 },
};
static AnimLoopSettings mn_803EB378[2] = {
    { 0, 49, -0.1 },
    { 50, 250, 50 },
};
static AnimLoopSettings mn_803EB390 = { 0, 10, -0.1 };
static AnimLoopSettings mn_803EB39C = { 320, 339, -0.1 };

static AnimLoopSettings mn_803EB3A8 = { 380, 399, -0.1 };
static AnimLoopSettings mn_803EB3B4 = { 360, 379, -0.1 };
static AnimLoopSettings mn_803EB3C0 = { 340, 359, -0.1 };
static float mn_803EB3CC[] = {
    280, 299, -0.1, 300, 319, -0.1, 320, 339, -0.1, 3950, 3999, 3970,
};

static AnimLoopSettings mn_803EB3FC[] = { { 0, 49, 20 },
                                          { 50, 99, 70 },
                                          { 100, 149, 120 },
                                          { 150, 199, 170 },
                                          { 200, 249, 220 } };

static AnimLoopSettings mn_803EB438 = { 3550, 3599, 3570 };

static AnimLoopSettings mn_803EB444[] = {
    { 400, 449, 420 }, { 450, 499, 470 }, { 500, 549, 520 },
    { 550, 599, 570 }, { 600, 649, 620 },
};

static AnimLoopSettings mn_803EB480 = { 3500, 3549, 3520 };

static AnimLoopSettings mn_803EB48C[] = {
    { 700, 749, 720 }, { 750, 799, 770 }, { 800, 849, 820 },
    { 850, 899, 870 }, { 900, 949, 920 },
};

static AnimLoopSettings mn_803EB4C8[] = {
    { 1000, 1049, 1020 },
    { 1050, 1099, 1070 },
    { 1100, 1149, 1120 },
    { 1150, 1199, 1170 },
};

static AnimLoopSettings mn_803EB4F8[] = {
    { 1300, 1349, 1320 }, { 1350, 1399, 1370 }, { 1400, 1449, 1420 },
    { 1450, 1499, 1470 }, { 1500, 1549, 1520 }, { 1550, 1599, 1570 },
};

static AnimLoopSettings mn_803EB540[] = {
    { 1600, 1649, 1620 }, { 1650, 1699, 1670 }, { 1700, 1749, 1720 },
    { 1750, 1799, 1770 }, { 1800, 1849, 1820 },
};

static AnimLoopSettings mn_803EB57C[] = {
    { 2000, 2049, 2020 },
    { 2050, 2099, 2070 },
    { 2100, 2149, 2120 },
};

static AnimLoopSettings mn_803EB5A0[] = {
    { 3150, 3199, 3170 },
    { 3200, 3249, 3220 },
    { 3250, 3299, 3270 },
};

static AnimLoopSettings mn_803EB5C4[] = {
    { 2250, 2299, 2270 },
    { 2300, 2349, 2320 },
    { 2350, 2399, 2370 },
};

static AnimLoopSettings mn_803EB5E8[] = {
    { 2550, 2599, 2570 }, { 2600, 2649, 2620 }, { 2650, 2699, 2670 },
    { 2700, 2749, 2720 }, { 2750, 2799, 2770 }, { 2800, 2849, 2820 },
    { 2850, 2899, 2870 }, { 2900, 2949, 2920 }, { 2900, 2949, 2920 },
    { 2900, 2949, 2920 },
};

static u16 mn_803EB660[] = { 0x81, 0x82, 0x83, 0x84, 0x85, 0x00 };
static u16 mn_803EB66C[] = { 0x86, 0x87, 0x88, 0x89, 0x8A, 0x00 };
static u16 mn_803EB678[] = { 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x00 };
static u16 mn_803EB684[] = { 0x9A, 0x9B, 0x9C, 0x9D, 0x9D, 0x9E };
static u16 mn_803EB690[] = { 0x9F, 0xA0, 0xA1, 0xA2, 0xA3, 0x00 };

static u16 mn_803EB69C[] = {
    0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA,
};

static u16 mn_804D4B30[4] = { 0x8B, 0x8C, 0x8D, 0x00 };
static u16 mn_804D4B38[4] = { 0x96, 0x97, 0x98, 0x99 };
static u16 mn_804D4B40[4] = { 0xA4, 0xA5, 0xA6, 0x00 };
static u16 mn_804D4B48[4] = { 0xA8, 0xA9, 0xAA, 0x00 };

static GXColor mn_804D4B50 = { 0x5A, 0x73, 0xFF, 0xFF };
static GXColor mn_804D4B54 = { 0xFF, 0x5A, 0x41, 0xFF };
static GXColor mn_804D4B58 = { 0x0E, 0xD2, 0x41, 0xFF };
static GXColor mn_804D4B5C = { 0xF0, 0xC8, 0x5A, 0xFF };
static GXColor mn_804D4B60 = { 0x9B, 0x41, 0xFF, 0xFF };

GXColor mn_804D4B64 = { 0xFF, 0xC8, 0x00, 0xFF };

MenuKindData mn_803EB6B0[0x22] = {
    {
        mn_803EB3FC,
        0,
        mn_803EB660,
        0x05,
        mn_8022DB10,
    },
    {
        mn_803EB444,
        20,
        mn_803EB66C,
        0x05,
        mn_8022D7F4,
    },
    {
        mn_803EB48C,
        40,
        mn_803EB678,
        0x05,
        mn_8022D594,
    },
    {
        mn_803EB4C8,
        60,
        mn_804D4B38,
        0x04,
        mn_8022D34C,
    },
    {
        mn_803EB4F8,
        80,
        mn_803EB684,
        0x06,
        mn_8022D104,
    },
    {
        mn_803EB540,
        100,
        mn_803EB690,
        0x05,
        mn_8022CE6C,
    },
    {
        mn_803EB57C,
        120,
        mn_804D4B30,
        0x03,
        mn_8022CC28,
    },
    {
        NULL,
        0,
        NULL,
        0x01,
        NULL,
    },
    {
        NULL,
        0,
        NULL,
        0x01,
        NULL,
    },
    {
        mn_803EB5C4,
        160,
        mn_804D4B48,
        0x03,
        mn_8022C7CC,
    },
    {
        NULL,
        0,
        NULL,
        0x01,
        NULL,
    },
    {
        NULL,
        0,
        NULL,
        0x01,
        NULL,
    },
    {
        mn_803EB5E8,
        200,
        mn_803EB69C,
        0x0A,
        mn_8022C4F4,
    },
    {
        NULL,
        0,
        NULL,
        0x07,
        NULL,
    },
    {
        NULL,
        0,
        NULL,
        0x01,
        NULL,
    },
    {
        NULL,
        0,
        NULL,
        0x06,
        NULL,
    },
    {
        NULL,
        0,
        NULL,
        0x01,
        NULL,
    },
    {
        NULL,
        0,
        NULL,
        0x01,
        NULL,
    },
    {
        NULL,
        0,
        NULL,
        0x01,
        NULL,
    },
    {
        NULL,
        0,
        NULL,
        0x01,
        NULL,
    },
    {
        NULL,
        0,
        NULL,
        0x01,
        NULL,
    },
    {
        NULL,
        0,
        NULL,
        0x01,
        NULL,
    },
    {
        NULL,
        0,
        NULL,
        0x01,
        NULL,
    },
    {
        NULL,
        0,
        NULL,
        0x01,
        NULL,
    },
    {
        NULL,
        0,
        NULL,
        0x01,
        NULL,
    },
    {
        NULL,
        0,
        NULL,
        0x01,
        NULL,
    },
    {
        NULL,
        0,
        NULL,
        0x01,
        NULL,
    },
    {
        NULL,
        0,
        NULL,
        0x01,
        NULL,
    },
    {
        mn_803EB5A0,
        240,
        mn_804D4B40,
        0x03,
        mn_8022CA54,
    },
    {
        NULL,
        0,
        NULL,
        0x01,
        NULL,
    },
    {
        NULL,
        0,
        NULL,
        0x01,
        NULL,
    },
    {
        NULL,
        0,
        NULL,
        0x01,
        NULL,
    },
    {
        NULL,
        0,
        NULL,
        0x01,
        NULL,
    },
    {
        NULL,
        0,
        NULL,
        0x01,
        NULL,
    },
};

u8 mn_802295AC(void)
{
    s32 port_idx = 0;
    while (port_idx < 4) {
        u64 res = gm_801A36A0(port_idx);
        if (res & 0x100000000) {
            return port_idx;
        }
        port_idx += 1;
    }
    return 0;
}

u32 mn_80229624(u32 slot)
{
    u32 ret = 0;
    u64 inputs_repeated;
    u64 inputs_trigger;
    inputs_repeated = gm_801A36C0(slot);
    inputs_trigger = gm_801A36A0(slot);
    if (mn_804D6BC8.cooldown != 0) {
        Menu_DecrementAnimTimer();
        return 0;
    }
    if (inputs_trigger & PAD_BUTTON_A) {
        ret |= MenuEvent_AButton;
    }
    if (inputs_trigger & PAD_BUTTON_START) {
        ret |= MenuEvent_StartButton;
    }
    if (inputs_trigger & PAD_CONFIRM) {
        ret |= MenuEvent_Forward;
    }
    if (inputs_trigger & PAD_CANCEL) {
        ret |= MenuEvent_Back;
    }
    if (inputs_trigger & PAD_TRIGGER_L) {
        ret |= MenuEvent_LTrigger;
    }
    if (inputs_trigger & PAD_TRIGGER_R) {
        ret |= MenuEvent_RTrigger;
    }
    if (inputs_trigger & PAD_BUTTON_X) {
        ret |= MenuEvent_XButton;
    }
    if (inputs_trigger & PAD_BUTTON_Y) {
        ret |= MenuEvent_YButton;
    }
    if (inputs_repeated & PAD_ANY_UP) {
        ret |= MenuEvent_Up;
    }
    if (inputs_repeated & PAD_ANY_DOWN) {
        ret |= MenuEvent_Down;
    }
    if (inputs_repeated & PAD_ANY_LEFT) {
        ret |= MenuEvent_Left;
    }
    if (inputs_repeated & PAD_ANY_RIGHT) {
        ret |= MenuEvent_Right;
    }
    return ret;
}

void mn_80229860(s8 pending_major)
{
    MenuExitData* data = gm_801A4B9C();
    data->pending_major = pending_major;
    gm_801A4B60();
}

static char null_terminator[1] = "\0";

#pragma dont_inline on

void mn_8022EA08(char* buf, u32 num)
{
    int buf_end = mn_8022EB78(num);
    int i;
    for (i = 0; i < buf_end; i++) {
        buf[buf_end - 1 - i] = mn_8022EB24(num, i) + 0x30;
    }
    buf[buf_end] = null_terminator[0];
}

#pragma dont_inline off

#pragma dont_inline on

void mn_8022EA78(char* buf, int buf_end, u32 num)
{
    int i;
    for (i = 0; i < buf_end; i++) {
        buf[buf_end - 1 - i] = mn_8022EB24(num, i) + 0x30;
    }
    buf[buf_end] = null_terminator[0];
}

#pragma dont_inline off


s32 mn_8022EB24(s32 arg0, s32 arg1)
{
    return (arg0 / powi(10, arg1)) % 10;
}

s32 mn_8022EB78(s32 num)
{
    s32 count;
    if (num == 0) {
        return 1;
    }
    count = 0;
    for (;;) {
        if ((num / powi(10, count)) != 0) {
            count += 1;
            if (count < 11) {
                continue;
            }
        }
        break;
    }
    return count;
}

void mn_80229894(s32 arg0, u16 arg1, s32 arg2)
{
    HSD_GObjProc* temp_r3;
    void (*temp_r0)(HSD_GObj*);

    mn_804D6BC8.cooldown = 5;
    mn_804A04F0.prev_menu = mn_804A04F0.cur_menu;
    mn_804A04F0.cur_menu = arg0;
    mn_804A04F0.hovered_selection = arg1;
    HSD_GObj_80390CD4(mn_8022B3A0(arg2));
    HSD_GObjPLink_80390228(HSD_GObj_804D781C);
    temp_r0 = mn_803EB6B0[arg0].think;
    if (temp_r0 != NULL) {
        temp_r3 = HSD_GObjProc_8038FD54(GObj_Create(0, 1, 0x80), temp_r0, 0);
        temp_r3->flags_3 = HSD_GObj_804D783C;
    }
}

/// @brief checks if a menu selection is locked
bool mn_80229938(s32 arg0, s32 arg1)
{
    if (arg0 == 6 && arg1 == 2) {
        if (gmMainLib_8015EDD4()) {
            return true;
        }
        return false;
    }
    if (arg0 == 5 && arg1 == 2) {
        if (gmMainLib_8015EE90()) {
            return true;
        }
        return false;
    }
    if (arg0 == 4 && arg1 == 3) {
        return false;
    }
    if (arg0 == 1 && arg1 == 2) {
        return false;
    }
    if (arg0 == 3) {
        switch (arg1) {
        case 2:
            return false;
        default:
            return true;
        }
    }
    return true;
}

/// @brief returns the amount of unlocked selections
int mn_80229A04(MenuKind kind, int selection)
{
    int i;
    int count = 0;
    for (i = 0; i < selection; i++) {
        if (mn_80229938(kind, i) != false) {
            count++;
        }
    }
    return count;
}

static inline u8 mn_80229A04_dontinline(MenuKind kind, int selection)
{
    return mn_80229A04(kind, selection);
}

/// @brief creates the description text for the hovered selection
static void mn_80229A7C(MainMenuData* data, MenuKind menu_kind, int selection)
{
    HSD_Text* temp_r3;
    HSD_Text* text;
    u16* sis_idx;

    if (data->description != NULL) {
        HSD_SisLib_803A5CC4(data->description);
        data->description = NULL;
    }
    sis_idx = mn_803EB6B0[menu_kind].description_indices;
    if (sis_idx != 0) {
        text = HSD_SisLib_803A5ACC(0, mn_804D6BB4, -9.5f, 9.1f, 17.0f,
                                   364.68332f, 38.38772f);
        data->description = text;
        text->font_size.x = 0.0521f;
        text->font_size.y = 0.0521f;
        HSD_SisLib_803A6368(text, sis_idx[selection]);
    }
}

static inline void mn_80229A7C_dontinline(void* arg0, int arg1, int arg2)
{
    mn_80229A7C(arg0, arg1, arg2);
}

StaticModelDesc MenMainBack_Top;

HSD_GObj* mn_80229B2C(void)
{
    HSD_GObj* temp_r30;
    HSD_JObj* temp_r3;

    temp_r30 = GObj_Create(4, 5, 0x80);
    temp_r3 = HSD_JObjLoadJoint(MenMainBack_Top.joint);
    HSD_GObjObject_80390A70(temp_r30, HSD_GObj_804D7849, temp_r3);
    GObj_SetupGXLink(temp_r30, HSD_GObj_JObjCallback, 2, 0x80);
    HSD_GObjProc_8038FD54(temp_r30, mn_8022EAE0, 0);
    HSD_JObjAddAnimAll(temp_r3, MenMainBack_Top.animjoint,
                       MenMainBack_Top.matanim_joint,
                       MenMainBack_Top.shapeanim_joint);
    HSD_JObjReqAnimAll(temp_r3, 0.0F);
    HSD_JObjAnimAll(temp_r3);
    return temp_r30;
}

StaticModelDesc MenMainPanel_Top;
StaticModelDesc MenMainConTop_Top;
StaticModelDesc MenMainCursor_Top;
StaticModelDesc MenMainConRl_Top;
StaticModelDesc MenMainCursorRl_Top;
StaticModelDesc MenMainNmRl_Top;
StaticModelDesc MenMainCursorTr01_Top;
StaticModelDesc MenMainCursorTr02_Top;
StaticModelDesc MenMainCursorTr03_Top;
StaticModelDesc MenMainCursorTr04_Top;
StaticModelDesc MenMainCursorRl01_Top;
StaticModelDesc MenMainCursorRl02_Top;
StaticModelDesc MenMainCursorRl03_Top;
StaticModelDesc MenMainCursorRl04_Top;
StaticModelDesc MenMainCursorRl05_Top;
StaticModelDesc MenMainConIs_Top;
StaticModelDesc MenMainCursorIs_Top;
StaticModelDesc MenMainConSs_Top;
StaticModelDesc MenMainCursorSs_Top;

void fn_80229BF4(HSD_GObj* gobj)
{
    f32 temp_f1;
    HSD_JObj* temp_r28;
    HSD_JObj* sp20;
    HSD_JObj* sp1C;
    AnimLoopSettings sp10;
    MainMenuPanelData* data;

    temp_r28 = GET_JOBJ(gobj);
    data = gobj->user_data;
    lb_80011E24(temp_r28, &sp20, 4, -1);
    lb_80011E24(temp_r28, &sp1C, 0x29, -1);
    if (data->cur_menu != mn_804A04F0.cur_menu) {
        data->prev_menu = data->cur_menu;
        data->cur_menu = mn_804A04F0.cur_menu;
        if (mn_804A04F0.entering_menu != 0) {
            HSD_JObjReqAnimAll(sp1C,
                               mn_803EAE8C[data->cur_menu][0].start_frame);
            data->state = 0;
        } else {
            HSD_JObjReqAnimAll(sp1C,
                               mn_803EAE8C[data->prev_menu][1].start_frame);
            data->state = 1;
        }
    }
    switch (data->state) {
    case 2:
        mn_8022ED6C(sp1C, &mn_803EAE8C[data->cur_menu][2]);
        break;
    case 0:
    case 1:
        temp_f1 = mn_8022F298(sp1C);
        if (data->state == 0) {
            sp10 = mn_803EAE8C[data->cur_menu][0];
        } else {
            sp10 = mn_803EAE8C[data->prev_menu][1];
        }
        if (temp_f1 >= sp10.end_frame) {
            data->state = 2;
            HSD_JObjReqAnimAll(sp1C,
                               mn_803EAE8C[data->cur_menu][2].start_frame);
        }
        HSD_JObjAnimAll(sp1C);
        break;
    }
    mn_8022ED6C(sp20, &mn_803EB354);
}

HSD_GObj* mn_80229DC0(void)
{
    HSD_JObj* spC;
    HSD_JObj* sp8;
    HSD_GObj* temp_r31;
    HSD_JObj* temp_r3;
    MainMenuPanelData* data;
    u8 tmp;

    temp_r31 = GObj_Create(5, 6, 0x80);
    temp_r3 = HSD_JObjLoadJoint(MenMainPanel_Top.joint);
    HSD_GObjObject_80390A70(temp_r31, HSD_GObj_804D7849, temp_r3);
    GObj_SetupGXLink(temp_r31, HSD_GObj_JObjCallback, 3, 0x80);
    HSD_GObjProc_8038FD54(temp_r31, fn_80229BF4, 0);
    HSD_JObjAddAnimAll(temp_r3, MenMainPanel_Top.animjoint,
                       MenMainPanel_Top.matanim_joint,
                       MenMainPanel_Top.shapeanim_joint);
    lb_80011E24(temp_r3, &spC, 4, -1);
    lb_80011E24(temp_r3, &sp8, 0x29, -1);
    HSD_JObjReqAnimAll(spC, mn_803EB354.start_frame);
    HSD_JObjAnimAll(spC);
    if (mn_804A04F0.cur_menu == 0) {
        HSD_JObjReqAnimAll(sp8,
                           mn_803EAE8C[mn_804A04F0.cur_menu][0].start_frame);
    } else {
        HSD_JObjReqAnimAll(sp8,
                           mn_803EAE8C[mn_804A04F0.cur_menu][2].start_frame);
    }
    HSD_JObjAnimAll(sp8);
    data = HSD_MemAlloc(4);
    if (data == NULL) {
        OSReport("Can't get user_data.\n");
        __assert("mnmain.c", 0x427, "user_data");
    }
    GObj_InitUserData(temp_r31, 0, mn_8022EB04, data);
    tmp = mn_804A04F0.cur_menu;
    data->cur_menu = tmp;
    data->prev_menu = tmp;
    data->state = 0;
    return temp_r31;
}

static const Vec3 mn_803B84E8 = { 0 };
static const Vec3 mn_803B84F4 = { 0 };

/// @brief cursor animation on hover
void mn_80229F60(HSD_GObj* gp, HSD_JObj* root, MainMenuSelection selection)
{
    float temp_f31;
    MainMenuData* data;
    MenuFlow* flow;
    HSD_JObj* jobj;

    HSD_JObj* sp54[7];
    u8 pad50[4];
    Vec3 sp44;
    Vec3 sp38;
    Vec3 sp2C;
    Vec3 sp20;
    u8 pad2[0xC];

    sp44 = mn_803B84E8;
    data = gp->user_data;
    lb_8001204C(root, sp54, mn_803EAE7C, 7);
    jobj = sp54[1];
    flow = &mn_804A04F0;
    HSD_JObjReqAnimAll(jobj, 1.0F);
    HSD_JObjAnimAll(jobj);
    HSD_JObjReqAnim(jobj,
                    mn_803EB6B0[flow->cur_menu].start_frame + selection * 2);
    mn_8022F3D8(jobj, 0xC, TOBJ_MASK);
    mn_8022F3D8(jobj, 0xD, TOBJ_MASK);
    mn_8022F3D8(jobj, 0xE, TOBJ_MASK);
    mn_8022F3D8(jobj, 0xF, TOBJ_MASK);
    mn_8022F3D8(jobj, 0x10, TOBJ_MASK);
    mn_8022F3D8(jobj, 0x11, TOBJ_MASK);
    mn_8022F3D8(jobj, 0x12, TOBJ_MASK);
    mn_8022F3D8(jobj, 0x13, TOBJ_MASK);
    HSD_JObjAnim(jobj);
    HSD_JObjReqAnimAll(
        sp54[0], mn_803EB360[1].start_frame +
                     (mn_8022F298(sp54[0]) - mn_803EB360[0].start_frame));
    HSD_JObjAnimAll(sp54[0]);
    HSD_JObjReqAnimAll(
        sp54[2], mn_803EB378[1].start_frame +
                     (mn_8022F298(sp54[2]) - mn_803EB378[0].start_frame));
    HSD_JObjAnimAll(sp54[2]);
    HSD_JObjReqAnimAll(sp54[3], mn_803EB390.start_frame);
    HSD_JObjAnimAll(sp54[3]);
    HSD_JObjClearFlagsAll(sp54[3], JOBJ_HIDDEN);
    HSD_JObjClearFlagsAll(sp54[4], JOBJ_HIDDEN);

    HSD_JObjSetScaleY(sp54[5], 2.0F);
    HSD_JObjSetScaleY(sp54[6], 2.0F);

    HSD_JObjGetTranslation(sp54[5], &sp20);
    HSD_JObjSetTranslate(sp54[6], &sp20);

    lb_8000B1CC(sp54[5], &sp44, &sp2C);
    lb_8000B1CC(data->tree[41], &sp44, &sp38);
    temp_f31 = atan2f(sp38.y - sp2C.y, sp38.x - sp2C.x);

    HSD_JObjSetRotationZ(sp54[5], temp_f31);
    HSD_JObjSetRotationZ(sp54[6], temp_f31);
}

/// @brief cursor animation on unhover
void mn_8022A440(HSD_GObj* gp, HSD_JObj* root, MainMenuSelection selection)
{
    HSD_JObj* sp24[7];
    HSD_JObj* r29;
    MenuFlow* flow;
    float f;
    PAD_STACK(0x10);

    lb_8001204C(root, sp24, mn_803EAE7C, 7);
    r29 = sp24[1];
    flow = &mn_804A04F0;
    HSD_JObjReqAnimAll(r29, 0.0F);
    HSD_JObjAnimAll(r29);
    HSD_JObjReqAnim(r29,
                    mn_803EB6B0[flow->cur_menu].start_frame + selection * 2);
    mn_8022F3D8(r29, 0xC, TOBJ_MASK);
    mn_8022F3D8(r29, 0xD, TOBJ_MASK);
    mn_8022F3D8(r29, 0xE, TOBJ_MASK);
    mn_8022F3D8(r29, 0xF, TOBJ_MASK);
    mn_8022F3D8(r29, 0x10, TOBJ_MASK);
    mn_8022F3D8(r29, 0x11, TOBJ_MASK);
    mn_8022F3D8(r29, 0x12, TOBJ_MASK);
    mn_8022F3D8(r29, 0x13, TOBJ_MASK);
    HSD_JObjAnim(r29);
    f = (mn_8022F298(sp24[0]) - mn_803EB360[1].start_frame);
    HSD_JObjReqAnimAll(sp24[0], f + mn_803EB360[0].start_frame);
    HSD_JObjAnimAll(sp24[0]);
    mn_8022F298(sp24[2]);
    HSD_JObjReqAnimAll(sp24[2], mn_803EB378[0].start_frame);
    HSD_JObjAnimAll(sp24[2]);
    HSD_JObjSetFlagsAll(sp24[4], JOBJ_HIDDEN);
}

/// @brief updates cursor animation
void mn_8022A5D0(HSD_GObj* gp, MainMenuSelection selection)
{
    u8 _[8];
    HSD_JObj* spA0[7];
    HSD_JObj* sp84[7];
    HSD_JObj* sp80;
    Vec3 sp74;
    Vec3 sp68;
    Vec3 sp5C;
    Vec3 sp50;
    HSD_JObj* var_r0;
    HSD_JObj* var_r5;
    u16* var_r4;
    u32 temp_r4;
    MainMenuData* data;
    int option_count;
    int var_r26;
    int var_r24;
    int var_r23;
    int temp_r22_2;
    HSD_JObj* temp_r3;
    int i;

    var_r4 = mn_803EAE68;
    sp68 = mn_803B84F4;
    // var_r5 = &spA0[0];
    data = gp->user_data;
    option_count = mn_803EB6B0[data->menu_kind].selection_count;

    for (i = 0; i < option_count; i++) {
        temp_r3 = data->tree[var_r4[i]];
        if (temp_r3 == NULL) {
            var_r0 = NULL;
        } else {
            var_r0 = temp_r3->child;
        }
        spA0[i] = var_r0;
    }
    for (var_r26 = 0; var_r26 < option_count; var_r26++) {
        if (mn_80229938(mn_804A04F0.cur_menu, var_r26) != 0) {
            var_r24 = mn_80229A04(mn_804A04F0.cur_menu, var_r26);
            lb_8001204C(spA0[var_r24], sp84, mn_803EAE7C, 7);
            temp_r22_2 = (selection == var_r26) * 0xC;
            mn_8022ED6C(sp84[0], &mn_803EB360[var_r26 == selection]);
            mn_8022ED6C(sp84[2], &mn_803EB378[var_r26 == selection]);
            if (mn_8022ED6C(sp84[3], &mn_803EB390) >= mn_803EB390.end_frame) {
                HSD_JObjSetFlagsAll(sp84[3], 0x10);
            }
            if (selection == var_r26) {
                if (HSD_JObjGetScaleY(sp84[6]) == 2.0f) {
                    lb_8000B1CC(sp84[5], &sp68, &sp50);
                    lb_8000B1CC(data->tree[41], &sp68, &sp5C);
                    sp74.x = sp5C.x - sp50.x;
                    sp74.y = sp5C.y - sp50.y;
                    sp74.z = sp5C.z - sp50.z;
                    HSD_JObjAddTranslationX(sp84[6], sp74.x / 10.0F);
                    HSD_JObjAddTranslationY(sp84[6], sp74.y / 10.0F);
                    HSD_JObjAddTranslationZ(sp84[6], sp74.z / 10.0F);
                    if ((sp74.x >= 0.0f &&
                         HSD_JObjGetTranslationX(sp84[6]) >= sp74.x) ||
                        (sp74.x < 0.0f &&
                         HSD_JObjGetTranslationX(sp84[6]) <= sp74.x))
                    {
                        HSD_JObjSetTranslate(sp84[6], &sp74);
                        HSD_JObjAddScaleY(sp84[6], -0.2F);
                        HSD_JObjAddScaleY(sp84[5], -0.2F);
                    }
                } else {
                    if (HSD_JObjGetScaleY(sp84[6]) > 0.0f) {
                        HSD_JObjAddScaleY(sp84[6], -0.2F);
                        HSD_JObjAddScaleY(sp84[5], -0.2F);
                        if (HSD_JObjGetScaleY(sp84[6]) <= 0.0f) {
                            HSD_JObjSetScaleY(sp84[6], 0.0F);
                            HSD_JObjSetScaleY(sp84[5], 0.0F);
                            HSD_JObjSetFlagsAll(sp84[4], JOBJ_HIDDEN);
                        }
                    }
                }
            }
        }
    }
}

static inline void UpdateAnimationLoop(HSD_JObj* jobj,
                                       AnimLoopSettings* anim_loop,
                                       bool selection_changed)
{
    float cur_frame = mn_8022F298(jobj);

    // Reset animation if selection changed or current frame is outside loop
    // bounds
    if (selection_changed || cur_frame < anim_loop->start_frame ||
        cur_frame > anim_loop->end_frame)
    {
        HSD_JObjReqAnimAll(jobj, anim_loop->start_frame);
    }
}

inline f32 GetAnimStartFrame(AnimLoopSettings* anim_loop)
{
    return anim_loop->start_frame;
}

inline f32 GetAnimEndFrame(AnimLoopSettings* anim_loop)
{
    return anim_loop->end_frame;
}

void mn_8022ADD8(HSD_GObj* gp, bool selection_changed)
{
    MainMenuData* data;
    HSD_JObj* jobj;
    f32 cur_frame;
    AnimLoopSettings* anim_loop2;
    AnimLoopSettings* anim_loop;

    data = gp->user_data;
    jobj = data->tree[14];
    switch (data->state) {
    case MENU_STATE_EXIT_FROM:
    case MENU_STATE_ENTER_FROM:
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        break;
    case MENU_STATE_IDLE:
    case MENU_STATE_ENTER_TO:
    case MENU_STATE_EXIT_TO:
    case MENU_STATE_5:
        /// @todo there is probably a inline for this whole block
        // seeing how we get the user data again here.
        // GetAnimStartFrame and GetAnimEndFrame are probably fake?
        data = gp->user_data;
        anim_loop2 = mn_803EB6B0[data->menu_kind].anim_loop;
        if (anim_loop2 != NULL) {
            if (data->menu_kind == MENU_KIND_MAIN &&
                data->hovered_selection == SEL_MAIN_DATA &&
                gmMainLib_8015EE90() == 0)
            {
                anim_loop = &mn_803EB438;
            } else if (data->menu_kind == MENU_KIND_1P &&
                       data->hovered_selection == SEL_1P_REG &&
                       gmMainLib_8015EDD4() == 0)
            {
                anim_loop = &mn_803EB480;
            } else {
                anim_loop = &anim_loop2[data->hovered_selection];
            }
            cur_frame = mn_8022F298(jobj);
            if ((u8) selection_changed != false ||
                !(GetAnimStartFrame(anim_loop) <= cur_frame) ||
                !(cur_frame <= GetAnimEndFrame(anim_loop)))
            {
                HSD_JObjReqAnimAll(jobj, GetAnimStartFrame(anim_loop));
            }
            mn_8022ED6C(jobj, anim_loop);
        }
        break;
    }
}

void fn_8022AF10(HSD_GObj* gp)
{
    MainMenuData* data;
    HSD_JObj* jobj;
    AnimLoopSettings* anim_loop;

    data = gp->user_data;
    jobj = data->tree[3];
    switch (data->state) {
    case MENU_STATE_EXIT_FROM:
        anim_loop = &mn_803EB3A8;
        break;
    case MENU_STATE_ENTER_FROM:
        anim_loop = &mn_803EB3C0;
        break;
    }
    if (mn_8022F298(jobj) >= anim_loop->end_frame) {
        switch (data->state) {
        case MENU_STATE_EXIT_FROM:
        case MENU_STATE_ENTER_FROM:
            HSD_GObjPLink_80390228(gp);
            return;
        }
    }
    HSD_JObjAnim(jobj);
}

/// @brief main menu think func that handles the updating
// of objects (animations, text)
void fn_8022AFEC(HSD_GObj* gp)
{
    /// @todo figure out the inlines
    MainMenuData* data;
    MainMenuData* data2;
    HSD_GObjProc* think;
    bool selection_changed;
    HSD_JObj* jobj;
    HSD_JObj* temp_jobj;
    u8 var_r26;
    AnimLoopSettings* anim_loop;
    MainMenuSelection hovered_selection;
    u8 state;
    u8 option_count;
    HSD_JObj* sp20[4];
    PAD_STACK(50);

    var_r26 = 0;
    selection_changed = false;
    data = gp->user_data;
    state = data->state;
    if ((state == MENU_STATE_5 || state <= MENU_STATE_ENTER_TO ||
         state == MENU_STATE_EXIT_TO) &&
        data->menu_kind != mn_804A04F0.cur_menu)
    {
        if (mn_804A04F0.entering_menu != 0) {
            data->state = MENU_STATE_ENTER_FROM;
        } else {
            data->state = MENU_STATE_EXIT_FROM;
        }
        switch (data->state) {
        case MENU_STATE_ENTER_TO:
            anim_loop = &mn_803EB39C;
            break;
        case MENU_STATE_EXIT_FROM:
            anim_loop = &mn_803EB3A8;
            break;
        case MENU_STATE_EXIT_TO:
            anim_loop = &mn_803EB3B4;
            break;
        case MENU_STATE_ENTER_FROM:
            anim_loop = &mn_803EB3C0;
            break;
        }
        jobj = data->tree[3];
        HSD_JObjReqAnim(jobj, anim_loop->start_frame);
        HSD_JObjAnim(jobj);
        if (data->state == MENU_STATE_5 ||
            data->state <= MENU_STATE_ENTER_TO ||
            data->state == MENU_STATE_EXIT_TO)
        {
            var_r26 = 1;
            selection_changed = true;
        } else {
            HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
            think = HSD_GObjProc_8038FD54(gp, fn_8022AF10, 0);
            think->flags_3 = HSD_GObj_804D783C;
        }
    }
    if (data->state == MENU_STATE_ENTER_TO ||
        data->state == MENU_STATE_EXIT_TO)
    {
        jobj = data->tree[3];
        switch (data->state) {
        case MENU_STATE_ENTER_TO:
            anim_loop = &mn_803EB39C;
            break;
        case MENU_STATE_EXIT_TO:
            anim_loop = &mn_803EB3B4;
            break;
        case MENU_STATE_EXIT_FROM:
            anim_loop = &mn_803EB3A8;
            break;
        case MENU_STATE_ENTER_FROM:
            anim_loop = &mn_803EB3C0;
            break;
        }
        if (mn_8022F298(jobj) >= anim_loop->end_frame) {
            switch (data->state) {
            case MENU_STATE_ENTER_TO:
            case MENU_STATE_EXIT_TO:
                data->state = MENU_STATE_IDLE;
                break;
            case MENU_STATE_EXIT_FROM:
            case MENU_STATE_ENTER_FROM:
                HSD_GObjPLink_80390228(gp);
                return;
            }
        }
        HSD_JObjAnim(jobj);
    }
    if (data->state == MENU_STATE_IDLE || data->state == MENU_STATE_ENTER_TO ||
        data->state == MENU_STATE_EXIT_TO)
    {
        if (data->hovered_selection != mn_804A04F0.hovered_selection) {
            selection_changed = true;
        }
        data2 = gp->user_data;
        option_count = mn_803EB6B0[data2->menu_kind].selection_count & 0xFF;
        {
            int i;
            for (i = 0; i < option_count; i++) {
                temp_jobj = data2->tree[mn_803EAE68[i]];
                if (temp_jobj == NULL) {
                    temp_jobj = NULL;
                } else {
                    temp_jobj = temp_jobj->child;
                }
                sp20[i] = temp_jobj;
            }
        }
        if ((u8) selection_changed != false) {
            /// @todo problem spot
            mn_80229F60(
                gp,
                sp20[mn_80229A04_dontinline(mn_804A04F0.cur_menu,
                                            mn_804A04F0.hovered_selection)],
                mn_804A04F0.hovered_selection);
            mn_8022A440(gp,
                        sp20[mn_80229A04_dontinline(mn_804A04F0.cur_menu,
                                                    data->hovered_selection)],
                        mn_804A04F0.prev_menu);
        }
        if ((u8) selection_changed != false) {
            hovered_selection = mn_804A04F0.hovered_selection;
        } else {
            hovered_selection = data2->hovered_selection;
        }
        mn_8022A5D0(gp, (u8) hovered_selection);
    }
    mn_8022ADD8(gp, selection_changed);
    data = gp->user_data;
    if ((u8) selection_changed != false) {
        hovered_selection = mn_804A04F0.hovered_selection;
    } else {
        hovered_selection = data->hovered_selection;
    }
    switch (data->state) {
    case MENU_STATE_ENTER_TO:
    case MENU_STATE_EXIT_TO:
    case MENU_STATE_5:
        break;
    case MENU_STATE_EXIT_FROM:
    case MENU_STATE_ENTER_FROM:
        if (data->description != NULL) {
            data = gp->user_data;
            HSD_SisLib_803A5CC4(data->description);
            data->description = NULL;
        }
        break;
    case MENU_STATE_IDLE:
        if (selection_changed != false) {
            mn_80229A7C_dontinline(data, data->menu_kind, hovered_selection);
        }
        data->description->hidden = 0;
        break;
    }
    if (var_r26 != 0) {
        data->menu_kind = mn_804A04F0.cur_menu;
    }
    if ((u8) selection_changed != false) {
        data->hovered_selection = mn_804A04F0.hovered_selection;
    }
}

/// @brief sets up a new menu when transitioning from another.
HSD_GObj* mn_8022B3A0(u8 state)
{
    HSD_JObj* sp48[12];
    HSD_JObj* sp2C[7];
    HSD_JObj* cursor_jobj;
    int temp_r31;
    HSD_GObj* gobj;
    HSD_JObj* temp_r16_2;
    u8 hovered_selection;
    int idx;
    u8 var_r16_2;
    AnimLoopSettings* var_r4_3;
    u8 option_count;
    u8 cur_menu;
    MenuKind menu_kind;
    MainMenuData* data;
    AnimLoopSettings* anim_loop;
    int i;
    HSD_JObj* jobj;
    AnimLoopSettings* tmp;
    u8 var_r17;
    u32 var_r17_int;
    HSD_JObj* root_jobj;
    StaticModelDesc* top = &MenMainConTop_Top;
    PAD_STACK(16);

    cur_menu = mn_804A04F0.cur_menu;
    anim_loop = mn_803EB6B0[cur_menu].anim_loop;
    option_count = mn_803EB6B0[cur_menu].selection_count;
    hovered_selection = mn_804A04F0.hovered_selection;

    var_r17 = 0;
    for (i = 0; i < mn_803EB6B0[cur_menu].selection_count; i++) {
        if (mn_80229938(cur_menu, i) != 0) {
            var_r17++;
        }
    }

    var_r17_int = var_r17;
    gobj = GObj_Create(6, 7, 0x80);
    root_jobj = HSD_JObjLoadJoint(top->joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, root_jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 4, 0x80);
    HSD_GObjProc_8038FD54(gobj, fn_8022AFEC, 0);
    HSD_JObjAddAnimAll(root_jobj, top->animjoint, top->matanim_joint,
                       top->shapeanim_joint);
    HSD_JObjReqAnimAll(root_jobj, 0.0F);
    data = HSD_MemAlloc(sizeof(MainMenuData));
    if (data == NULL) {
        OSReport("Can't get user_data.\n");
        __assert("mnmain.c", 0x65D, "user_data");
    }
    GObj_InitUserData(gobj, 0, mn_8022EB04, data);
    data->menu_kind = mn_804A04F0.cur_menu;
    data->hovered_selection = mn_804A04F0.hovered_selection;
    data->state = state;
    data->description = NULL;
    for (idx = 0; idx < 0x2A; idx++) {
        lb_80011E24(root_jobj, &data->tree[idx], idx, -1);
    }
    if (data->state != MENU_STATE_IDLE) {
        switch (data->state) {
        case MENU_STATE_EXIT_TO:
        case MENU_STATE_ENTER_TO:
            HSD_JObjReqAnim(data->tree[3], mn_803EB39C.start_frame);
            break;
        case MENU_STATE_EXIT_FROM:
            HSD_JObjReqAnim(data->tree[3], mn_803EB3B4.start_frame);
            break;
        case MENU_STATE_ENTER_FROM:
        case MENU_STATE_5:
            break;
        }
        HSD_JObjAnim(data->tree[3]);
    }
    for (i = 0; i < option_count; i++) {
        sp48[i] = data->tree[mn_803EAE68[i]];
    }
    for (i = 0; i < option_count; i++) {
        StaticModelDesc* top = &MenMainCursor_Top;
        if (mn_80229938(mn_804A04F0.cur_menu, i) != 0) {
            menu_kind = mn_804A04F0.cur_menu;
            var_r16_2 = mn_80229A04(menu_kind, i);
            HSD_JObjReqAnim(sp48[var_r16_2], var_r17_int);
            HSD_JObjAnim(sp48[var_r16_2]);
            cursor_jobj = HSD_JObjLoadJoint(top->joint);
            HSD_JObjAddAnimAll(cursor_jobj, top->animjoint, top->matanim_joint,
                               top->shapeanim_joint);
            lb_8001204C(cursor_jobj, sp2C, mn_803EAE7C, 7);
            tmp = &mn_803EB378[hovered_selection == i];
            HSD_JObjReqAnim(sp2C[0], mn_803EB360[0].start_frame);
            HSD_JObjAnim(sp2C[0]);
            jobj = sp2C[1];
            HSD_JObjReqAnimAll(jobj, hovered_selection == i);
            HSD_JObjAnimAll(jobj);
            HSD_JObjReqAnim(
                jobj, mn_803EB6B0[mn_804A04F0.cur_menu].start_frame + 2 * i);
            mn_8022F3D8(jobj, 0xC, TOBJ_MASK);
            mn_8022F3D8(jobj, 0xD, TOBJ_MASK);
            mn_8022F3D8(jobj, 0xE, TOBJ_MASK);
            mn_8022F3D8(jobj, 0xF, TOBJ_MASK);
            mn_8022F3D8(jobj, 0x10, TOBJ_MASK);
            mn_8022F3D8(jobj, 0x11, TOBJ_MASK);
            mn_8022F3D8(jobj, 0x12, TOBJ_MASK);
            mn_8022F3D8(jobj, 0x13, TOBJ_MASK);
            HSD_JObjAnim(jobj);
            if (i == hovered_selection) {
                HSD_JObjReqAnimAll(sp2C[2], tmp->start_frame);
            } else {
                HSD_JObjReqAnimAll(sp2C[2], tmp->end_frame);
            }
            HSD_JObjAnimAll(sp2C[2]);
            if (i == hovered_selection) {
                HSD_JObjReqAnim(sp2C[3], mn_803EB390.start_frame);
            } else {
                HSD_JObjSetFlagsAll(sp2C[3], JOBJ_HIDDEN);
            }
            HSD_JObjAnim(sp2C[3]);
            if (i != hovered_selection) {
                HSD_JObjSetFlagsAll(sp2C[4], JOBJ_HIDDEN);
            }
            HSD_JObjAddChild(sp48[var_r16_2], cursor_jobj);
        }
    }
    temp_r16_2 = data->tree[14];
    if (data->menu_kind == 0 && data->hovered_selection == 4 &&
        gmMainLib_8015EE90() == 0)
    {
        var_r4_3 = &mn_803EB438;
    } else if ((data->menu_kind == 1) && (data->hovered_selection == 0) &&
               (gmMainLib_8015EDD4() == 0))
    {
        var_r4_3 = &mn_803EB480;
    } else {
        var_r4_3 = &anim_loop[data->hovered_selection];
    }
    HSD_JObjReqAnimAll(temp_r16_2, var_r4_3->start_frame);
    HSD_JObjAnimAll(temp_r16_2);

    mn_80229A7C(data, data->menu_kind, data->hovered_selection);
    return gobj;
}

static const Vec3 mn_803B8500 = { 0, 1, 0 };

/// @brief updates menu camera rotation from the cstick
void mn_8022BA1C(HSD_GObj* gp)
{
    u8 _[0x10];
    Mtx sp54;
    Vec3 sp48;
    Vec3 sp3C;
    Vec3 sp30;
    Vec3 sp24;
    Vec3 sp18;
    u8 _2[0x8];
    float var_f0;
    float x;
    float var_f31;
    float var_f30;
    float y;
    int i;

    HSD_CObj* cobj = GET_COBJ(gp);
    for (i = 0; i < 4; i++) {
        x = HSD_PadCopyStatus[(u8) i].nml_subStickX;
        y = HSD_PadCopyStatus[(u8) i].nml_subStickY;
        if (!(-0.4F < x && x < 0.4f && -0.4F < y && y < 0.4f)) {
            break;
        }
    }
    if (-0.4F < x && x < 0.4F && -0.4F < y && y < 0.4F) {
        var_f30 = 0.0f;
        var_f31 = 0.0f;
    } else {
        if (-0.4F < x && x < 0.4f) {
            var_f31 = 0.0f;
        } else {
            if (x < 0.0f) {
                var_f0 = -0.4f;
            } else {
                var_f0 = +0.4f;
            }
            var_f31 = 30.0f * ((x - var_f0) / 0.6f);
        }
        if (-0.4F < y && y < 0.4f) {
            var_f30 = 0.0f;
        } else {
            if (y < 0.0f) {
                var_f0 = -0.4f;
            } else {
                var_f0 = +0.4f;
            }
            var_f30 = 30.0f * ((y - var_f0) / 0.6f);
        }
    }
    HSD_CObjInit(cobj, MenMain_cam);
    sp30 = mn_803B8500;
    HSD_CObjGetEyeVector(cobj, &sp48);
    HSD_CObjGetInterest(cobj, &sp18);
    PSVECCrossProduct(&sp30, &sp48, &sp3C);
    PSVECNormalize(&sp3C, &sp3C);
    PSMTXRotAxisRad(sp54, &sp3C, 0.017453292f * var_f30);
    PSMTXMultVec(sp54, &sp48, &sp48);
    PSMTXRotAxisRad(sp54, &sp30, 0.017453292f * var_f31);
    PSMTXMultVec(sp54, &sp48, &sp48);
    PSVECScale(&sp48, &sp48, HSD_CObjGetEyeDistance(cobj));
    PSVECSubtract(&sp18, &sp48, &sp24);
    HSD_CObjSetEyePosition(cobj, &sp24);
}

void fn_8022BCD4(HSD_GObj* gobj, int unused)
{
    HSD_FogSet(gobj->hsd_obj);
}

HSD_GObj* mn_8022BCF8(void)
{
    HSD_GObj* gobj;
    HSD_Fog* fog;

    gobj = GObj_Create(1, 2, 0x80);
    mn_804D6BA8 = gobj;
    fog = HSD_FogLoadDesc(MenMain_fog);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7848, fog);
    GObj_SetupGXLink(gobj, fn_8022BCD4, 1, 0x80);
    return gobj;
}

void mn_8022BD6C(void)
{
    mn_804D6BAC->gxlink_prios = 0;
    mn_804D6BB0->gxlink_prios = 0;
}

void mn_8022BD8C(void)
{
    mn_804D6BAC->gxlink_prios = 0x7F;
    mn_804D6BB0->gxlink_prios = 0x80;
}

void fn_8022BDB4(HSD_GObj* gobj, int unused)
{
    HSD_Fog* fog = GET_FOG(mn_804D6BA8);
    if (HSD_CObjSetCurrent(GET_COBJ(gobj)) != 0) {
        HSD_SetEraseColor(fog->color.r, fog->color.g, fog->color.b,
                          fog->color.a);
        HSD_CObjEraseScreen(GET_COBJ(gobj), 1, 0, 1);
        HSD_GObj_80390ED0(gobj, 7);
        HSD_CObjEndCurrent();
    }
}

HSD_GObj* mn_8022BE34(void)
{
    Vec3 pos;
    HSD_GObj* gobj = GObj_Create(2, 3, 0x80);
    HSD_CObj* cobj;

    mn_804D6BAC = gobj;
    cobj = HSD_CObjLoadDesc(MenMain_cam);
    HSD_CObjGetEyePosition(cobj, &pos);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784B, cobj);
    GObj_SetupGXLinkMax(gobj, fn_8022BDB4, 0);
    gobj->gxlink_prios = 0x7F;
    HSD_GObjProc_8038FD54(gobj, mn_8022BA1C, 0);
    return gobj;
}

void mn_8022BEDC(HSD_GObj* gobj)
{
    HSD_GObj* temp_r3;
    HSD_CObj* cobj;

    mn_804D6BB5 = HSD_SisLib_803A611C(0, gobj, 7, 8, 0x80, 5, 0x80, 0);
    temp_r3 = GObj_Create(2, 3, 0x80);
    mn_804D6BB0 = temp_r3;
    cobj = HSD_CObjLoadDesc(MenMain_cam);
    HSD_GObjObject_80390A70(temp_r3, HSD_GObj_804D784B, cobj);
    GObj_SetupGXLinkMax(temp_r3, HSD_GObj_803910D8, 0);
    temp_r3->gxlink_prios = 0x80;
    HSD_GObjProc_8038FD54(temp_r3, mn_8022BA1C, 0);
    mn_804D6BB4 = HSD_SisLib_803A611C(0, temp_r3, 7, 8, 0x80, 7, 0x80, 0);
}

GXColor* mn_8022BFBC(int arg0)
{
    switch (arg0) {
    case 0:
        return &mn_804D4B50;
    case 1:
        return &mn_804D4B54;
    case 2:
        return &mn_804D4B58;
    case 3:
        return &mn_804D4B5C;
    case 4:
        return &mn_804D4B60;
    }
}

/// @brief gets the menu light color index
int mn_8022C010(int menu_kind, int selection)
{
    if (menu_kind == MENU_KIND_MAIN) {
        return selection;
    }
    switch (menu_kind) {
    case MENU_KIND_1P:
    case MENU_KIND_REG:
    case MENU_KIND_7:
    case MENU_KIND_8:
    case MENU_KIND_STADIUM:
    case MENU_KIND_10:
    case MENU_KIND_33:
        return 0;
    case MENU_KIND_VS:
    case MENU_KIND_11:
    case MENU_KIND_SPECIAL:
    case MENU_KIND_RULES:
    case MENU_KIND_14:
    case MENU_KIND_RULES_EXTRA:
    case MENU_KIND_RULES_ITEMS:
    case MENU_KIND_RULES_STAGE:
    case MENU_KIND_NAME_ENTRY:
        return 1;
    case MENU_KIND_TOY:
        return 2;
    case MENU_KIND_SETTINGS:
    case MENU_KIND_SETTINGS_RUMBLE:
    case MENU_KIND_SETTINGS_SOUND:
    case MENU_KIND_DISPLAY:
    case MENU_KIND_22:
    case MENU_KIND_SETTINGS_LANG:
    case MENU_KIND_SETTINGS_ERASE:
        return 3;
    case MENU_KIND_DATA:
    case MENU_KIND_DATA_SNAP:
    case MENU_KIND_DATA_ARCHIVES:
    case MENU_KIND_27:
    case MENU_KIND_RECORDS:
    case MENU_KIND_DATA_SPECIAL:
    case MENU_KIND_RECORDS_VS:
    case MENU_KIND_RECORDS_BONUS:
    case MENU_KIND_RECORDS_MISC:
        return 4;
    }
}

MenuFlow mn_804A04F0;

inline void mn_8022C068(HSD_LObj* lobj, int unused, int div)
{
    int diff;

    while (!(lobj->flags & LOBJ_POINT)) {
        lobj = lobj->next;
    }
    if (div != 0) {
        diff = mn_804A04F0.light_color->r - lobj->color.r;
        if (diff != 0) {
            lobj->color.r += diff / div;
        }
        diff = mn_804A04F0.light_color->g - lobj->color.g;
        if (diff != 0) {
            lobj->color.g += diff / div;
        }
        diff = mn_804A04F0.light_color->b - lobj->color.b;
        if (diff != 0) {
            lobj->color.b += diff / div;
        }
    } else {
        lobj->color.r = mn_804A04F0.light_color->r;
        lobj->color.g = mn_804A04F0.light_color->g;
        lobj->color.b = mn_804A04F0.light_color->b;
    }
}

void fn_8022C128(HSD_GObj* arg0)
{
    GXColor* color;
    HSD_LObj* lobj = GET_LOBJ(arg0);
    HSD_LObjAnimAll(lobj);

    color = mn_8022BFBC(
        mn_8022C010(mn_804A04F0.cur_menu, mn_804A04F0.hovered_selection));

    if (color != mn_804A04F0.light_color) {
        mn_804A04F0.light_lerp_frames = 0x10;
        mn_804A04F0.light_color = color;
    }
    if (mn_804A04F0.light_lerp_frames != 0) {
        mn_804A04F0.light_lerp_frames--;
        mn_8022C068(lobj, 0, mn_804A04F0.light_lerp_frames);
    }
}

extern LightList** MenMain_lights;
MenuFlow mn_804A04F0;

void mn_8022C304(void)
{
    HSD_GObj* gobj;
    HSD_LObj* lobj;
    PAD_STACK(8);

    gobj = GObj_Create(3, 4, 0x80);
    GObj_SetupGXLink(gobj, HSD_GObj_LObjCallback, 0, 0x80);
    HSD_GObjProc_8038FD54(gobj, fn_8022C128, 0);
    lobj = lb_80011AC4(MenMain_lights);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784A, lobj);
    mn_804A04F0.light_lerp_frames = 0;
    mn_804A04F0.light_color = mn_8022BFBC(
        mn_8022C010(mn_804A04F0.cur_menu, mn_804A04F0.hovered_selection));
    mn_8022C068(lobj, 0, mn_804A04F0.light_lerp_frames);
}

static inline void x2_dec(u8 temp_r29)
{
    do {
        if (mn_804A04F0.hovered_selection != 0) {
            mn_804A04F0.hovered_selection--;
        } else {
            mn_804A04F0.hovered_selection = temp_r29 - 1;
        }
    } while (
        !mn_80229938(mn_804A04F0.cur_menu, mn_804A04F0.hovered_selection));
}

static inline void x2_inc(u8 temp_r29)
{
    do {
        if (mn_804A04F0.hovered_selection == temp_r29 - 1) {
            mn_804A04F0.hovered_selection = 0;
        } else {
            mn_804A04F0.hovered_selection++;
        }
    } while (
        !mn_80229938(mn_804A04F0.cur_menu, mn_804A04F0.hovered_selection));
}

/// @brief Special Vs menu think
void mn_8022C4F4(HSD_GObj* gp)
{
    HSD_GObj* gobj;
    HSD_GObjProc* temp_r3_2;
    int selection_count =
        mn_803EB6B0[MENU_KIND_SPECIAL].selection_count & 0xFF;
    MenuExitData* data;
    void (*temp_r28)(HSD_GObj*);
    u32 buttons = mn_80229624(4);

    PAD_STACK(8);

    mn_804A04F0.buttons = buttons;
    if (buttons & MenuEvent_Forward) {
        mn_804D6BC8.cooldown = 5;
        mn_804A04F0.entering_menu = 1;
        switch (mn_804A04F0.hovered_selection) {
        case SEL_SPECIAL_VS_CAMERA:
            lbAudioAx_80024030(1);
            data = gm_801A4B9C();
            data->pending_major = MJ_CAMERA_MODE;
            gm_801A4B60();
            break;
        case SEL_SPECIAL_VS_STAMINA:
            lbAudioAx_80024030(1);
            data = gm_801A4B9C();
            data->pending_major = MJ_STAMINA_VS;
            gm_801A4B60();
            break;
        case SEL_SPECIAL_VS_SUDDEN_DEATH:
            lbAudioAx_80024030(1);
            data = gm_801A4B9C();
            data->pending_major = MJ_SUPER_SUDDEN_DEATH_VS;
            gm_801A4B60();
            break;
        case SEL_SPECIAL_VS_GIANT:
            lbAudioAx_80024030(1);
            data = gm_801A4B9C();
            data->pending_major = MJ_GIANT_VS;
            gm_801A4B60();
            break;
        case SEL_SPECIAL_VS_TINY:
            lbAudioAx_80024030(1);
            data = gm_801A4B9C();
            data->pending_major = MJ_TINY_VS;
            gm_801A4B60();
            break;
        case SEL_SPECIAL_VS_INVISIBLE:
            lbAudioAx_80024030(1);
            data = gm_801A4B9C();
            data->pending_major = MJ_INVISIBLE_VS;
            gm_801A4B60();
            break;
        case SEL_SPECIAL_VS_FIXED_CAMERA:
            lbAudioAx_80024030(1);
            data = gm_801A4B9C();
            data->pending_major = MJ_FIXED_CAMERA_VS;
            gm_801A4B60();
            break;
        case SEL_SPECIAL_VS_SINGLE_BUTTON:
            lbAudioAx_80024030(1);
            data = gm_801A4B9C();
            data->pending_major = MJ_SINGLE_BUTTON_VS;
            gm_801A4B60();
            break;
        case SEL_SPECIAL_VS_LIGHTNING:
            lbAudioAx_80024030(1);
            data = gm_801A4B9C();
            data->pending_major = MJ_LIGHTNING_VS;
            gm_801A4B60();
            break;
        case SEL_SPECIAL_VS_SLOMO:
            lbAudioAx_80024030(1);
            data = gm_801A4B9C();
            data->pending_major = MJ_SLOMO_VS;
            gm_801A4B60();
            break;
        }
    } else if (buttons & MenuEvent_Back) {
        lbAudioAx_80024030(0);
        mn_804A04F0.entering_menu = 0;
        mn_804D6BC8.cooldown = 5;
        mn_804A04F0.prev_menu = mn_804A04F0.cur_menu;
        mn_804A04F0.cur_menu = MENU_KIND_VS;
        mn_804A04F0.hovered_selection = SEL_VS_SPECIAL;
        HSD_GObj_80390CD4(mn_8022B3A0(3));
        HSD_GObjPLink_80390228(HSD_GObj_804D781C);
        if ((temp_r28 = mn_803EB6B0[MENU_KIND_VS].think)) {
            gobj = GObj_Create(0, 1, 0x80);
            temp_r3_2 = HSD_GObjProc_8038FD54(gobj, temp_r28, 0);
            temp_r3_2->flags_3 = HSD_GObj_804D783C;
        }
    } else if (buttons & MenuEvent_Up) {
        lbAudioAx_80024030(2);
        x2_dec(selection_count);
    } else if (buttons & MenuEvent_Down) {
        lbAudioAx_80024030(2);
        x2_inc(selection_count);
    }
}

MenuFlow mn_804A04F0;

static inline u8 mn_8022C7CC_inline(void)
{
    int i;
    for (i = 0; i < 4; i++) {
        if (gm_801A36A0(i) & (1LL << 32)) {
            return i;
        }
    }
    return 0;
}

/// @brief Stadium menu think
void mn_8022C7CC(HSD_GObj* gp)
{
    HSD_GObjProc* think;
    MenuExitData* data;
    int selection_count =
        mn_803EB6B0[MENU_KIND_STADIUM].selection_count & 0xFF;
    void (*temp_r28)(HSD_GObj*);
    u32 buttons = mn_80229624(4);
    PAD_STACK(8);

    mn_804A04F0.buttons = buttons;
    if (buttons & MenuEvent_Forward) {
        mn_804D6BC8.cooldown = 5;
        mn_804A04F0.entering_menu = 1;
        switch (mn_804A04F0.hovered_selection) {
        case SEL_STADIUM_TARGET:
            lbAudioAx_80024030(1);
            gm_801677E8(mn_8022C7CC_inline());
            data = gm_801A4B9C();
            data->pending_major = MJ_TARGET_TEST;
            gm_801A4B60();
            return;
        case SEL_STADIUM_HOMERUN:
            lbAudioAx_80024030(1);
            gm_801677E8(mn_8022C7CC_inline());
            data = gm_801A4B9C();
            data->pending_major = MJ_HOME_RUN_CONTEST;
            gm_801A4B60();
            return;
        case SEL_STADIUM_MULTIMAN:
            lbAudioAx_80024030(1);
            mnHyaku_8024CD64(0);
            HSD_GObjPLink_80390228(gp);
            return;
        }
    } else if (buttons & MenuEvent_Back) {
        lbAudioAx_80024030(0);
        mn_804A04F0.entering_menu = 0;
        mn_804D6BC8.cooldown = 5;
        mn_804A04F0.prev_menu = mn_804A04F0.cur_menu;
        mn_804A04F0.cur_menu = MENU_KIND_1P;
        mn_804A04F0.hovered_selection = SEL_1P_STADIUM;
        HSD_GObj_80390CD4(mn_8022B3A0(3));
        HSD_GObjPLink_80390228(HSD_GObj_804D781C);
        if ((temp_r28 = mn_803EB6B0[1].think)) {
            HSD_GObj* gobj = GObj_Create(0, 1, 0x80);
            think = HSD_GObjProc_8038FD54(gobj, temp_r28, 0);
            think->flags_3 = HSD_GObj_804D783C;
        }
    } else if (buttons & MenuEvent_Up) {
        lbAudioAx_80024030(2);
        x2_dec(selection_count);
    } else if (buttons & MenuEvent_Down) {
        lbAudioAx_80024030(2);
        x2_inc(selection_count);
    }
}

/// @brief Records menu think
void mn_8022CA54(HSD_GObj* gp)
{
    HSD_GObjProc* think;
    u32 buttons;
    void (*temp_r30)(HSD_GObj*);
    PAD_STACK(8);

    buttons = mn_80229624(4);
    mn_804A04F0.buttons = buttons;
    if (buttons & MenuEvent_Forward) {
        mn_804D6BC8.cooldown = 5;
        mn_804A04F0.entering_menu = 1;
        switch ((RecordsMenuSelection) mn_804A04F0.hovered_selection) {
        case SEL_RECORDS_VS:
            lbAudioAx_80024030(1);
            mnDiagram_802437E8(1, 1);
            HSD_GObjPLink_80390228(gp);
            return;
        case SEL_RECORDS_BONUS:
            lbAudioAx_80024030(1);
            mnInfoBonus_80252F8C();
            HSD_GObjPLink_80390228(gp);
            return;
        case SEL_RECORDS_MISC:
            lbAudioAx_80024030(1);
            mnCount_8025186C();
            HSD_GObjPLink_80390228(gp);
            return;
        }
    } else if (buttons & MenuEvent_Back) {
        lbAudioAx_80024030(0);
        mn_804A04F0.entering_menu = 0;
        mn_804D6BC8.cooldown = 5;
        mn_804A04F0.prev_menu = mn_804A04F0.cur_menu;
        mn_804A04F0.cur_menu = MENU_KIND_DATA;
        mn_804A04F0.hovered_selection = (DataMenuSelection) SEL_DATA_RECORDS;
        HSD_GObj_80390CD4(mn_8022B3A0(3));
        HSD_GObjPLink_80390228(HSD_GObj_804D781C);
        if ((temp_r30 = mn_803EB6B0[MENU_KIND_DATA].think)) {
            think =
                HSD_GObjProc_8038FD54(GObj_Create(0, 1, 0x80), temp_r30, 0);
            think->flags_3 = HSD_GObj_804D783C;
        }
    } else if (buttons & MenuEvent_Up) {
        lbAudioAx_80024030(2);
        if ((RecordsMenuSelection) mn_804A04F0.hovered_selection ==
            SEL_RECORDS_VS)
        {
            mn_804A04F0.hovered_selection =
                (RecordsMenuSelection) SEL_RECORDS_MISC;
        } else {
            mn_804A04F0.hovered_selection--;
        }
    } else if (buttons & MenuEvent_Down) {
        lbAudioAx_80024030(2);
        if ((RecordsMenuSelection) mn_804A04F0.hovered_selection ==
            SEL_RECORDS_MISC)
        {
            mn_804A04F0.hovered_selection =
                (RecordsMenuSelection) SEL_RECORDS_VS;
        } else {
            mn_804A04F0.hovered_selection++;
        }
    }
}

/// @brief Regular Match menu think
void mn_8022CC28(HSD_GObj* gp)
{
    HSD_GObjProc* think;
    u32 buttons;
    MenuExitData* data;
    void (*temp_r28)(HSD_GObj*);
    PAD_STACK(8);

    buttons = mn_80229624(4);
    mn_804A04F0.buttons = buttons;
    if (buttons & MenuEvent_Forward) {
        mn_804D6BC8.cooldown = 5;
        mn_804A04F0.entering_menu = 1;
        gm_801677E8(mn_8022C7CC_inline());
        switch ((RegMatchMenuSelection) mn_804A04F0.hovered_selection)
        { /* irregular */
        case SEL_REG_CLASSIC:
            lbAudioAx_80024030(1);
            data = gm_801A4B9C();
            data->pending_major = MJ_CLASSIC;
            gm_801A4B60();
            return;
        case SEL_REG_ADVENTURE:
            lbAudioAx_80024030(1);
            data = gm_801A4B9C();
            data->pending_major = MJ_ADVENTURE;
            gm_801A4B60();
            return;
        case SEL_REG_ALLSTAR:
            lbAudioAx_80024030(1);
            data = gm_801A4B9C();
            data->pending_major = MJ_ALLSTAR;
            gm_801A4B60();
            return;
        }
    } else if (buttons & MenuEvent_Back) {
        lbAudioAx_80024030(0);
        mn_804A04F0.entering_menu = 0;
        mn_804D6BC8.cooldown = 5;
        mn_804A04F0.prev_menu = mn_804A04F0.cur_menu;
        mn_804A04F0.cur_menu = MENU_KIND_1P;
        mn_804A04F0.hovered_selection = (OnePlayerMenuSelection) SEL_1P_REG;
        HSD_GObj_80390CD4(mn_8022B3A0(3));
        HSD_GObjPLink_80390228(HSD_GObj_804D781C);
        if ((temp_r28 = mn_803EB6B0[MENU_KIND_1P].think)) {
            think =
                HSD_GObjProc_8038FD54(GObj_Create(0, 1, 0x80), temp_r28, 0);
            think->flags_3 = HSD_GObj_804D783C;
        }
    } else if (buttons & MenuEvent_Up) {
        lbAudioAx_80024030(2);
        do {
            if (mn_804A04F0.hovered_selection !=
                (RegMatchMenuSelection) SEL_REG_CLASSIC)
            {
                mn_804A04F0.hovered_selection--;
            } else {
                mn_804A04F0.hovered_selection =
                    (RegMatchMenuSelection) SEL_REG_ALLSTAR;
            }
        } while (mn_80229938(6, (s32) mn_804A04F0.hovered_selection) == 0);
    } else if (buttons & MenuEvent_Down) {
        lbAudioAx_80024030(2);
        do {
            if ((RegMatchMenuSelection) mn_804A04F0.hovered_selection ==
                SEL_REG_ALLSTAR)
            {
                mn_804A04F0.hovered_selection =
                    (RegMatchMenuSelection) SEL_REG_CLASSIC;
            } else {
                mn_804A04F0.hovered_selection++;
            }
        } while (mn_80229938(6, (s32) mn_804A04F0.hovered_selection) == 0);
    }
}

/// @brief Data menu think
void mn_8022CE6C(HSD_GObj* gp)
{
    HSD_GObjProc* think;
    HSD_GObjProc* think2;
    u32 buttons;
    void (*temp_r29)(HSD_GObj*);
    void (*temp_r29_2)(HSD_GObj*);

    PAD_STACK(8);

    buttons = mn_80229624(4);
    mn_804A04F0.buttons = buttons;
    if (buttons & MenuEvent_Forward) {
        mn_804A04F0.entering_menu = 1;
        switch ((DataMenuSelection) mn_804A04F0.hovered_selection)
        { /* irregular */
        case SEL_DATA_SNAP:
            lbAudioAx_80024030(1);
            mnSnap_80257F24();
            HSD_GObjPLink_80390228(gp);
            break;
        case SEL_DATA_ARCHIVES:
            lbAudioAx_80024030(1);
            mnGallery_80259868();
            HSD_GObjPLink_80390228(gp);
            break;
        case SEL_DATA_SOUND:
            lbAudioAx_80023694();
            lbAudioAx_800236DC();
            mnSoundTest_8024BEE0(1);
            HSD_GObjPLink_80390228(gp);
            break;
        case SEL_DATA_RECORDS:
            lbAudioAx_80024030(1);
            mn_804D6BC8.cooldown = 5;
            mn_804A04F0.prev_menu = mn_804A04F0.cur_menu;
            mn_804A04F0.cur_menu = MENU_KIND_RECORDS;
            mn_804A04F0.hovered_selection = 0;
            HSD_GObj_80390CD4(mn_8022B3A0(1));
            HSD_GObjPLink_80390228(HSD_GObj_804D781C);
            if ((temp_r29 = mn_803EB6B0[28].think)) {
                think = HSD_GObjProc_8038FD54(GObj_Create(0, 1, 0x80),
                                              temp_r29, 0);
                think->flags_3 = HSD_GObj_804D783C;
            }
            break;
        case SEL_DATA_SPECIAL:
            lbAudioAx_80024030(1);
            mnInfo_80252758();
            HSD_GObjPLink_80390228(gp);
            break;
        }
    } else if (buttons & MenuEvent_Back) {
        lbAudioAx_80024030(0);
        mn_804A04F0.entering_menu = 0;
        mn_804D6BC8.cooldown = 5;
        mn_804A04F0.prev_menu = mn_804A04F0.cur_menu;
        mn_804A04F0.cur_menu = MENU_KIND_MAIN;
        mn_804A04F0.hovered_selection = (MainMenuSelection) SEL_MAIN_DATA;
        HSD_GObj_80390CD4(mn_8022B3A0(3));
        HSD_GObjPLink_80390228(HSD_GObj_804D781C);
        if ((temp_r29_2 = mn_803EB6B0[MENU_KIND_MAIN].think)) {
            think2 =
                HSD_GObjProc_8038FD54(GObj_Create(0, 1, 0x80), temp_r29_2, 0);
            think2->flags_3 = HSD_GObj_804D783C;
        }
    } else if (buttons & MenuEvent_Up) {
        lbAudioAx_80024030(2);
        do {
            if (mn_804A04F0.hovered_selection !=
                (DataMenuSelection) SEL_DATA_SNAP)
            {
                mn_804A04F0.hovered_selection--;
            } else {
                mn_804A04F0.hovered_selection =
                    (DataMenuSelection) SEL_DATA_SPECIAL;
            }
        } while (mn_80229938(5, (s32) mn_804A04F0.hovered_selection) == 0);
    } else if (buttons & MenuEvent_Down) {
        lbAudioAx_80024030(2);
        do {
            if ((DataMenuSelection) mn_804A04F0.hovered_selection ==
                SEL_DATA_SPECIAL)
            {
                mn_804A04F0.hovered_selection =
                    (DataMenuSelection) SEL_DATA_SNAP;
            } else {
                mn_804A04F0.hovered_selection++;
            }
        } while (mn_80229938(5, (s32) mn_804A04F0.hovered_selection) == 0);
    }
}

/// @brief Settings menu think
void mn_8022D104(HSD_GObj* gp)
{
    int selection_count;
    u32 buttons;
    HSD_GObjProc* temp_r3_2;
    void (*temp_r28)(HSD_GObj*);

    PAD_STACK(8);

    selection_count = mn_803EB6B0[MENU_KIND_SETTINGS].selection_count & 0xFF;
    buttons = mn_80229624(4);
    mn_804A04F0.buttons = buttons;
    if (buttons & MenuEvent_Forward) {
        mn_804D6BC8.cooldown = 5;
        mn_804A04F0.entering_menu = 1;
        switch (mn_804A04F0.hovered_selection) {
        case SEL_SETTINGS_RUMBLE:
            lbAudioAx_80024030(1);
            mnVibration_80249174(1);
            HSD_GObjPLink_80390228(gp);
            break;
        case SEL_SETTINGS_SOUND:
            lbAudioAx_80024030(1);
            mnSound_8024A09C(1);
            HSD_GObjPLink_80390228(gp);
            break;
        case SEL_SETTINGS_DISPLAY:
            lbAudioAx_80024030(1);
            mnDeflicker_8024A6C4(1);
            HSD_GObjPLink_80390228(gp);
            break;
        case SEL_SETTINGS_LANG:
            lbAudioAx_80024030(1);
            mnLanguage_8024C5C0((HSD_GObj*) 1);
            HSD_GObjPLink_80390228(gp);
            break;
        case SEL_SETTINGS_ERASE:
            lbAudioAx_80024030(1);
            mnDataDel_80250170();
            HSD_GObjPLink_80390228(gp);
            break;
        }
    } else if (buttons & MenuEvent_Back) {
        lbAudioAx_80024030(0);
        mn_804A04F0.entering_menu = 0;
        mn_804D6BC8.cooldown = 5;
        mn_804A04F0.prev_menu = mn_804A04F0.cur_menu;
        mn_804A04F0.cur_menu = MENU_KIND_MAIN;
        mn_804A04F0.hovered_selection = (MainMenuSelection) SEL_MAIN_SETTINGS;
        HSD_GObj_80390CD4(mn_8022B3A0(3));
        HSD_GObjPLink_80390228(HSD_GObj_804D781C);
        if ((temp_r28 = mn_803EB6B0[MENU_KIND_MAIN].think)) {
            temp_r3_2 =
                HSD_GObjProc_8038FD54(GObj_Create(0, 1, 0x80), temp_r28, 0);
            temp_r3_2->flags_3 = HSD_GObj_804D783C;
        }
    } else if (buttons & MenuEvent_Up) {
        lbAudioAx_80024030(2);
        do {
            if (mn_804A04F0.hovered_selection !=
                (SettingsMenuSelection) SEL_SETTINGS_RUMBLE)
            {
                mn_804A04F0.hovered_selection--;
            } else {
                mn_804A04F0.hovered_selection = (u8) selection_count - 1;
            }
        } while (mn_80229938(4, mn_804A04F0.hovered_selection) == 0);
    } else if (buttons & 2) {
        lbAudioAx_80024030(2);
        do {
            if (mn_804A04F0.hovered_selection == (u8) selection_count - 1) {
                mn_804A04F0.hovered_selection = SEL_SETTINGS_RUMBLE;
            } else {
                mn_804A04F0.hovered_selection++;
            }
        } while (mn_80229938(4, mn_804A04F0.hovered_selection) == 0);
    }
}

/// @brief Trohpy menu think
void mn_8022D34C(HSD_GObj* gp)
{
    HSD_GObjProc* think;
    u32 buttons;
    u8 var_r3;
    MenuExitData* data;
    void (*temp_r28)(HSD_GObj*);
    PAD_STACK(8);

    buttons = mn_80229624(4);
    mn_804A04F0.buttons = buttons;
    if (buttons & MenuEvent_Forward) {
        mn_804D6BC8.cooldown = 5;
        mn_804A04F0.entering_menu = 1;
        gm_801677E8(mn_8022C7CC_inline());
        switch (mn_804A04F0.hovered_selection) {
        case SEL_TOY_GALLERY:
            lbAudioAx_80024030(1);
            data = gm_801A4B9C();
            data->pending_major = MJ_TOY_GALLERY;
            gm_801A4B60();
            return;
        case SEL_TOY_LOTTERY:
            lbAudioAx_80024030(1);
            data = gm_801A4B9C();
            data->pending_major = MJ_TOY_LOTTERY;
            gm_801A4B60();
            return;
        case SEL_TOY_COLLECTION:
            lbAudioAx_80024030(1);
            data = gm_801A4B9C();
            data->pending_major = MJ_TOY_COLLECTION;
            gm_801A4B60();
            return;
        }
    } else if (buttons & MenuEvent_Back) {
        lbAudioAx_80024030(0);
        mn_804A04F0.entering_menu = 0;
        mn_804D6BC8.cooldown = 5;
        mn_804A04F0.prev_menu = mn_804A04F0.cur_menu;
        mn_804A04F0.cur_menu = MENU_KIND_MAIN;
        mn_804A04F0.hovered_selection = (MainMenuSelection) SEL_MAIN_TOY;
        HSD_GObj_80390CD4(mn_8022B3A0(3));
        HSD_GObjPLink_80390228(HSD_GObj_804D781C);
        if ((temp_r28 = mn_803EB6B0[MENU_KIND_MAIN].think)) {
            think =
                HSD_GObjProc_8038FD54(GObj_Create(0, 1, 0x80), temp_r28, 0);
            think->flags_3 = HSD_GObj_804D783C;
        }
    } else if (buttons & MenuEvent_Up) {
        lbAudioAx_80024030(2);
        do {
            if (mn_804A04F0.hovered_selection !=
                (TrophyMenuSelection) SEL_TOY_GALLERY)
            {
                mn_804A04F0.hovered_selection--;
            } else {
                mn_804A04F0.hovered_selection =
                    (TrophyMenuSelection) SEL_TOY_COLLECTION;
            }
        } while (mn_80229938(3, mn_804A04F0.hovered_selection) == 0);
    } else if (buttons & MenuEvent_Down) {
        lbAudioAx_80024030(2);
        do {
            if ((TrophyMenuSelection) mn_804A04F0.hovered_selection ==
                SEL_TOY_COLLECTION)
            {
                mn_804A04F0.hovered_selection = SEL_TOY_GALLERY;
            } else {
                mn_804A04F0.hovered_selection++;
            }
        } while (mn_80229938(3, mn_804A04F0.hovered_selection) == 0);
    }
}

/// @brief Versus menu think
void mn_8022D594(HSD_GObj* gp)
{
    HSD_GObjProc* think;
    HSD_GObjProc* think2;
    u32 buttons;
    void (*temp_r28)(HSD_GObj*);
    void (*temp_r28_2)(HSD_GObj*);
    MenuExitData* data;

    PAD_STACK(8);

    buttons = mn_80229624(4);
    mn_804A04F0.buttons = buttons;
    if (buttons & MenuEvent_Forward) {
        mn_804D6BC8.cooldown = 5;
        mn_804A04F0.entering_menu = 1;
        switch (mn_804A04F0.hovered_selection) {
        case SEL_VS_MELEE:
            lbAudioAx_80024030(1);
            data = gm_801A4B9C();
            data->pending_major = MJ_VS;
            gm_801A4B60();
            break;
        case SEL_VS_TOURNAMENT:
            lbAudioAx_80024030(1);
            data = gm_801A4B9C();
            data->pending_major = MJ_TOURNAMENT;
            gm_801A4B60();
            break;
        case SEL_VS_SPECIAL:
            lbAudioAx_80024030(1);
            mn_804D6BC8.cooldown = 5;
            mn_804A04F0.prev_menu = mn_804A04F0.cur_menu;
            mn_804A04F0.cur_menu = MENU_KIND_SPECIAL;
            mn_804A04F0.hovered_selection =
                (SpecialVsMenuSelection) SEL_SPECIAL_VS_CAMERA;
            HSD_GObj_80390CD4(mn_8022B3A0(1));
            HSD_GObjPLink_80390228(HSD_GObj_804D781C);
            if ((temp_r28 = mn_803EB6B0[MENU_KIND_SPECIAL].think)) {
                think = HSD_GObjProc_8038FD54(GObj_Create(0, 1, 0x80),
                                              temp_r28, 0);
                think->flags_3 = HSD_GObj_804D783C;
            }
            break;
        case SEL_VS_RULES:
            lbAudioAx_80024030(1);
            mn_80231714();
            HSD_GObjPLink_80390228(gp);
            break;
        case SEL_VS_NAME:
            lbAudioAx_80024030(1);
            mnName_8023AC40();
            HSD_GObjPLink_80390228(gp);
            break;
        }
    } else if (buttons & MenuEvent_Back) {
        lbAudioAx_80024030(0);
        mn_804A04F0.entering_menu = 0;
        mn_804D6BC8.cooldown = 5;
        mn_804A04F0.prev_menu = mn_804A04F0.cur_menu;
        mn_804A04F0.cur_menu = MENU_KIND_MAIN;
        mn_804A04F0.hovered_selection = (MainMenuSelection) SEL_MAIN_VS;
        HSD_GObj_80390CD4(mn_8022B3A0(3));
        HSD_GObjPLink_80390228(HSD_GObj_804D781C);
        if ((temp_r28_2 = mn_803EB6B0[MENU_KIND_MAIN].think)) {
            think2 =
                HSD_GObjProc_8038FD54(GObj_Create(0, 1, 0x80), temp_r28_2, 0);
            think2->flags_3 = HSD_GObj_804D783C;
        }
    } else if (buttons & MenuEvent_Up) {
        lbAudioAx_80024030(2);
        if ((VsMenuSelection) mn_804A04F0.hovered_selection == SEL_VS_MELEE) {
            mn_804A04F0.hovered_selection = SEL_VS_NAME;
        } else {
            mn_804A04F0.hovered_selection--;
        }
    } else if (buttons & MenuEvent_Down) {
        lbAudioAx_80024030(2);
        if ((VsMenuSelection) mn_804A04F0.hovered_selection == SEL_VS_NAME) {
            mn_804A04F0.hovered_selection = SEL_VS_MELEE;
        } else {
            mn_804A04F0.hovered_selection++;
        }
    }
}

/// @brief Singleplayer menu think
void mn_8022D7F4(HSD_GObj* gp)
{
    int selection_count;
    HSD_GObjProc* temp_r3_2;
    HSD_GObjProc* temp_r3_3;
    HSD_GObjProc* temp_r3_4;
    u32 buttons;
    void (*temp_r27)(HSD_GObj*);
    MenuExitData* data;

    PAD_STACK(8);

    selection_count = mn_803EB6B0[MENU_KIND_1P].selection_count & 0xFF;
    buttons = mn_80229624(4);
    mn_804A04F0.buttons = buttons;
    if (buttons & MenuEvent_Forward) {
        mn_804A04F0.entering_menu = 1;
        gm_801677E8(mn_8022C7CC_inline());
        switch (mn_804A04F0.hovered_selection) {
        case SEL_1P_REG:
            lbAudioAx_80024030(1);
            mn_804D6BC8.cooldown = 5;
            mn_804A04F0.prev_menu = mn_804A04F0.cur_menu;
            mn_804A04F0.cur_menu = MENU_KIND_REG;
            mn_804A04F0.hovered_selection =
                (RegMatchMenuSelection) SEL_REG_CLASSIC;
            HSD_GObj_80390CD4(mn_8022B3A0(1));
            HSD_GObjPLink_80390228(HSD_GObj_804D781C);
            if ((temp_r27 = mn_803EB6B0[MENU_KIND_REG].think)) {
                temp_r3_2 = HSD_GObjProc_8038FD54(GObj_Create(0, 1, 0x80),
                                                  temp_r27, 0);
                temp_r3_2->flags_3 = HSD_GObj_804D783C;
            }
            break;
        case SEL_1P_STADIUM:
            lbAudioAx_80024030(1);
            mn_804D6BC8.cooldown = 5;
            mn_804A04F0.prev_menu = mn_804A04F0.cur_menu;
            mn_804A04F0.cur_menu = MENU_KIND_STADIUM;
            mn_804A04F0.hovered_selection =
                (StadiumMenuSelection) SEL_STADIUM_TARGET;
            HSD_GObj_80390CD4(mn_8022B3A0(1));
            HSD_GObjPLink_80390228(HSD_GObj_804D781C);
            if ((temp_r27 = mn_803EB6B0[MENU_KIND_STADIUM].think)) {
                temp_r3_3 = HSD_GObjProc_8038FD54(GObj_Create(0, 1, 0x80),
                                                  temp_r27, 0);
                temp_r3_3->flags_3 = HSD_GObj_804D783C;
            }
            break;
        case SEL_1P_EVENT:
            lbAudioAx_80024030(1);
            mnEvent_8024E838(0, 1);
            HSD_GObjPLink_80390228(gp);
            break;
        case SEL_1P_TRAINING:
            lbAudioAx_80024030(1);
            data = gm_801A4B9C();
            data->pending_major = MJ_TRAINING;
            gm_801A4B60();
            break;
        }
    } else if (buttons & MenuEvent_Back) {
        lbAudioAx_80024030(0);
        mn_804A04F0.entering_menu = 0;
        mn_804D6BC8.cooldown = 5;
        mn_804A04F0.prev_menu = mn_804A04F0.cur_menu;
        mn_804A04F0.cur_menu = MENU_KIND_MAIN;
        mn_804A04F0.hovered_selection = (MainMenuSelection) SEL_MAIN_1P;
        HSD_GObj_80390CD4(mn_8022B3A0(3));
        HSD_GObjPLink_80390228(HSD_GObj_804D781C);
        if ((temp_r27 = mn_803EB6B0[MENU_KIND_MAIN].think)) {
            temp_r3_4 =
                HSD_GObjProc_8038FD54(GObj_Create(0, 1, 0x80), temp_r27, 0);
            temp_r3_4->flags_3 = HSD_GObj_804D783C;
        }
    } else if (buttons & MenuEvent_Up) {
        lbAudioAx_80024030(2);
        do {
            if (mn_804A04F0.hovered_selection !=
                (OnePlayerMenuSelection) SEL_1P_REG)
            {
                mn_804A04F0.hovered_selection--;
            } else {
                mn_804A04F0.hovered_selection = (u8) selection_count - 1;
            }
        } while (mn_80229938(1, mn_804A04F0.hovered_selection) == 0);
    } else if (buttons & MenuEvent_Down) {
        lbAudioAx_80024030(2);
        do {
            if (mn_804A04F0.hovered_selection == (u8) selection_count - 1) {
                mn_804A04F0.hovered_selection =
                    (OnePlayerMenuSelection) SEL_1P_REG;
            } else {
                mn_804A04F0.hovered_selection++;
            }
        } while (mn_80229938(1, mn_804A04F0.hovered_selection) == 0);
    }
}

/// @brief Main menu think
void mn_8022DB10(HSD_GObj* gp)
{
    MenuExitData* data;
    MenuKind menu_kind;
    void (*temp_r28)(HSD_GObj*);
    int selection_count;
    u16 hovered_selection;
    HSD_GObjProc* temp_r3_2;
    u32 buttons;

    PAD_STACK(8);

    selection_count = mn_803EB6B0[MENU_KIND_MAIN].selection_count & 0xFF;
    buttons = mn_80229624(4);
    mn_804A04F0.buttons = buttons;
    if (buttons & MenuEvent_Forward) {
        mn_804D6BC8.cooldown = 5;
        mn_804A04F0.entering_menu = 1;
        lbAudioAx_80024030(1);
        mn_804A04F0.prev_menu = mn_804A04F0.cur_menu;
        switch (mn_804A04F0.hovered_selection) {
        case SEL_MAIN_1P:
            menu_kind = MENU_KIND_1P;
            hovered_selection = 0;
            break;
        case SEL_MAIN_VS:
            menu_kind = MENU_KIND_VS;
            hovered_selection = 0;
            break;
        case SEL_MAIN_TOY:
            menu_kind = MENU_KIND_TOY;
            hovered_selection = 0;
            break;
        case SEL_MAIN_SETTINGS:
            menu_kind = MENU_KIND_SETTINGS;
            hovered_selection = 0;
            break;
        case SEL_MAIN_DATA:
            menu_kind = MENU_KIND_DATA;
            hovered_selection = 0;
            break;
        }
        mn_804D6BC8.cooldown = 5;
        mn_804A04F0.prev_menu = mn_804A04F0.cur_menu;
        mn_804A04F0.cur_menu = menu_kind;
        mn_804A04F0.hovered_selection = hovered_selection;
        HSD_GObj_80390CD4(mn_8022B3A0(1));
        HSD_GObjPLink_80390228(HSD_GObj_804D781C);
        /// @todo casting u64 here makes it match, but i dont know why
        if ((temp_r28 = mn_803EB6B0[(u64) menu_kind].think)) {
            temp_r3_2 =
                HSD_GObjProc_8038FD54(GObj_Create(0, 1, 0x80), temp_r28, 0);
            temp_r3_2->flags_3 = HSD_GObj_804D783C;
        }
    } else if (buttons & MenuEvent_Back) {
        lbAudioAx_80024030(0);
        mn_804A04F0.entering_menu = 0;
        mn_804D6BC8.cooldown = 5;
        data = gm_801A4B9C();
        data->pending_major = MJ_TITLE;
        gm_801A4B60();
    } else if (buttons & MenuEvent_Up) {
        lbAudioAx_80024030(2);
        do {
            if (mn_804A04F0.hovered_selection !=
                (MainMenuSelection) SEL_MAIN_1P)
            {
                mn_804A04F0.hovered_selection--;
            } else {
                mn_804A04F0.hovered_selection = (u8) selection_count - 1;
            }
        } while (mn_80229938(0, mn_804A04F0.hovered_selection) == 0);
    } else if (buttons & MenuEvent_Down) {
        lbAudioAx_80024030(2);
        do {
            if (mn_804A04F0.hovered_selection == (u8) selection_count - 1) {
                mn_804A04F0.hovered_selection =
                    (MainMenuSelection) SEL_MAIN_1P;
            } else {
                mn_804A04F0.hovered_selection++;
            }
        } while (mn_80229938(0, mn_804A04F0.hovered_selection) == 0);
    }
}

void mn_8022DD38_OnFrame(void)
{
    MenuExitData* data;
    if (mn_8022F218() && mn_804A04F0.cur_menu != MENU_KIND_MAIN) {
        lbAudioAx_80023694();
        lbAudioAx_80024030(0);
        mn_8022F268();
        gm_801603B0();
        lb_8001B760(0xB);
        lbMthp_8001F800();
        mn_8022EBDC();
        HSD_SisLib_803A5E70();
        data = gm_801A4B9C();
        data->pending_major = MJ_MENU;
        gm_801A4B60();
    }
}

static inline void mn_8022DDA8_inline(u16* sp2B4)
{
    int temp_r29;
    HSD_GObj* gobj;
    HSD_LObj* lobj;

    gobj = GObj_Create(3, 4, 0x80);
    GObj_SetupGXLink(gobj, HSD_GObj_LObjCallback, 0, 0x80);
    HSD_GObjProc_8038FD54(gobj, fn_8022C128, 0);
    lobj = lb_80011AC4(MenMain_lights);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784A, lobj);
    mn_804A04F0.light_lerp_frames = 0;
    temp_r29 = mn_8022C010(mn_804A04F0.cur_menu, *sp2B4);
    mn_804A04F0.light_color = mn_8022BFBC(temp_r29);
    mn_8022C068(lobj, temp_r29, mn_804A04F0.light_lerp_frames);
}

void mn_8022DDA8_OnEnter(MenuEnterData* data)
{
    u16* hovered_selection;
    HSD_GObj* temp_r3_8;
    u8 menu_kind;
    void (*var_r4)(HSD_GObj*);

    u8 _[0x14];

    mn_804D6BC8.cooldown = 0x14;
    mn_804D6BC8.x2 = 0;
    mn_804D6BC8.x4 = 0;
    mn_804A04F0.buttons = 0;
    hovered_selection = &mn_804A04F0.hovered_selection;
    menu_kind = data->menu_kind;
    mn_804A04F0.cur_menu = menu_kind;
    mn_804A04F0.prev_menu = menu_kind;
    *hovered_selection = data->hovered_selection;
    mn_804D6BAC = NULL;
    mn_804D6BB0 = NULL;
    if (data->load_assets != false) {
        mn_804D6BB8 = lbArchive_LoadSymbols(
            "MnMaAll", &MenMainBack_Top.joint, "MenMainBack_Top_joint",
            &MenMainBack_Top.animjoint, "MenMainBack_Top_animjoint",
            &MenMainBack_Top.matanim_joint, "MenMainBack_Top_matanim_joint",
            &MenMainBack_Top.shapeanim_joint,
            "MenMainBack_Top_shapeanim_joint",

            &MenMain_cam, "ScMenMain_cam_int1_camera", &MenMain_lights,
            "ScMenMain_scene_lights", &MenMain_fog, "ScMenMain_fog",

            &MenMainPanel_Top.joint, "MenMainPanel_Top_joint",
            &MenMainPanel_Top.animjoint, "MenMainPanel_Top_animjoint",
            &MenMainPanel_Top.matanim_joint, "MenMainPanel_Top_matanim_joint",
            &MenMainPanel_Top.shapeanim_joint,
            "MenMainPanel_Top_shapeanim_joint",

            &MenMainConTop_Top.joint, "MenMainConTop_Top_joint",
            &MenMainConTop_Top.animjoint, "MenMainConTop_Top_animjoint",
            &MenMainConTop_Top.matanim_joint,
            "MenMainConTop_Top_matanim_joint",
            &MenMainConTop_Top.shapeanim_joint,
            "MenMainConTop_Top_shapeanim_joint",

            &MenMainCursor_Top.joint, "MenMainCursor_Top_joint",
            &MenMainCursor_Top.animjoint, "MenMainCursor_Top_animjoint",
            &MenMainCursor_Top.matanim_joint,
            "MenMainCursor_Top_matanim_joint",
            &MenMainCursor_Top.shapeanim_joint,
            "MenMainCursor_Top_shapeanim_joint",

            &MenMainConRl_Top.joint, "MenMainConRl_Top_joint",
            &MenMainConRl_Top.animjoint, "MenMainConRl_Top_animjoint",
            &MenMainConRl_Top.matanim_joint, "MenMainConRl_Top_matanim_joint",
            &MenMainConRl_Top.shapeanim_joint,
            "MenMainConRl_Top_shapeanim_joint",

            &MenMainCursorRl_Top.joint, "MenMainCursorRl_Top_joint",
            &MenMainCursorRl_Top.animjoint, "MenMainCursorRl_Top_animjoint",
            &MenMainCursorRl_Top.matanim_joint,
            "MenMainCursorRl_Top_matanim_joint",
            &MenMainCursorRl_Top.shapeanim_joint,
            "MenMainCursorRl_Top_shapeanim_joint",

            &MenMainNmRl_Top.joint, "MenMainNmRl_Top_joint",
            &MenMainNmRl_Top.animjoint, "MenMainNmRl_Top_animjoint",
            &MenMainNmRl_Top.matanim_joint, "MenMainNmRl_Top_matanim_joint",
            &MenMainNmRl_Top.shapeanim_joint,
            "MenMainNmRl_Top_shapeanim_joint",

            &MenMainCursorTr01_Top.joint, "MenMainCursorTr01_Top_joint",
            &MenMainCursorTr01_Top.animjoint,
            "MenMainCursorTr01_Top_animjoint",
            &MenMainCursorTr01_Top.matanim_joint,
            "MenMainCursorTr01_Top_matanim_joint",
            &MenMainCursorTr01_Top.shapeanim_joint,
            "MenMainCursorTr01_Top_shapeanim_joint",

            &MenMainCursorTr02_Top.joint, "MenMainCursorTr02_Top_joint",
            &MenMainCursorTr02_Top.animjoint,
            "MenMainCursorTr02_Top_animjoint",
            &MenMainCursorTr02_Top.matanim_joint,
            "MenMainCursorTr02_Top_matanim_joint",
            &MenMainCursorTr02_Top.shapeanim_joint,
            "MenMainCursorTr02_Top_shapeanim_joint",

            &MenMainCursorTr03_Top.joint, "MenMainCursorTr03_Top_joint",
            &MenMainCursorTr03_Top.animjoint,
            "MenMainCursorTr03_Top_animjoint",
            &MenMainCursorTr03_Top.matanim_joint,
            "MenMainCursorTr03_Top_matanim_joint",
            &MenMainCursorTr03_Top.shapeanim_joint,
            "MenMainCursorTr03_Top_shapeanim_joint",

            &MenMainCursorTr04_Top.joint, "MenMainCursorTr04_Top_joint",
            &MenMainCursorTr04_Top.animjoint,
            "MenMainCursorTr04_Top_animjoint",
            &MenMainCursorTr04_Top.matanim_joint,
            "MenMainCursorTr04_Top_matanim_joint",
            &MenMainCursorTr04_Top.shapeanim_joint,
            "MenMainCursorTr04_Top_shapeanim_joint",

            &MenMainCursorRl01_Top.joint, "MenMainCursorRl01_Top_joint",
            &MenMainCursorRl01_Top.animjoint,
            "MenMainCursorRl01_Top_animjoint",
            &MenMainCursorRl01_Top.matanim_joint,
            "MenMainCursorRl01_Top_matanim_joint",
            &MenMainCursorRl01_Top.shapeanim_joint,
            "MenMainCursorRl01_Top_shapeanim_joint",

            &MenMainCursorRl02_Top.joint, "MenMainCursorRl02_Top_joint",
            &MenMainCursorRl02_Top.animjoint,
            "MenMainCursorRl02_Top_animjoint",
            &MenMainCursorRl02_Top.matanim_joint,
            "MenMainCursorRl02_Top_matanim_joint",
            &MenMainCursorRl02_Top.shapeanim_joint,
            "MenMainCursorRl02_Top_shapeanim_joint",

            &MenMainCursorRl03_Top.joint, "MenMainCursorRl03_Top_joint",
            &MenMainCursorRl03_Top.animjoint,
            "MenMainCursorRl03_Top_animjoint",
            &MenMainCursorRl03_Top.matanim_joint,
            "MenMainCursorRl03_Top_matanim_joint",
            &MenMainCursorRl03_Top.shapeanim_joint,
            "MenMainCursorRl03_Top_shapeanim_joint",

            &MenMainCursorRl04_Top.joint, "MenMainCursorRl04_Top_joint",
            &MenMainCursorRl04_Top.animjoint,
            "MenMainCursorRl04_Top_animjoint",
            &MenMainCursorRl04_Top.matanim_joint,
            "MenMainCursorRl04_Top_matanim_joint",
            &MenMainCursorRl04_Top.shapeanim_joint,
            "MenMainCursorRl04_Top_shapeanim_joint",

            &MenMainCursorRl05_Top.joint, "MenMainCursorRl05_Top_joint",
            &MenMainCursorRl05_Top.animjoint,
            "MenMainCursorRl05_Top_animjoint",
            &MenMainCursorRl05_Top.matanim_joint,
            "MenMainCursorRl05_Top_matanim_joint",
            &MenMainCursorRl05_Top.shapeanim_joint,
            "MenMainCursorRl05_Top_shapeanim_joint",

            &MenMainConIs_Top.joint, "MenMainConIs_Top_joint",
            &MenMainConIs_Top.animjoint, "MenMainConIs_Top_animjoint",
            &MenMainConIs_Top.matanim_joint, "MenMainConIs_Top_matanim_joint",
            &MenMainConIs_Top.shapeanim_joint,
            "MenMainConIs_Top_shapeanim_joint",

            &MenMainCursorIs_Top.joint, "MenMainCursorIs_Top_joint",
            &MenMainCursorIs_Top.animjoint, "MenMainCursorIs_Top_animjoint",
            &MenMainCursorIs_Top.matanim_joint,
            "MenMainCursorIs_Top_matanim_joint",
            &MenMainCursorIs_Top.shapeanim_joint,
            "MenMainCursorIs_Top_shapeanim_joint",

            &MenMainConSs_Top.joint, "MenMainConSs_Top_joint",
            &MenMainConSs_Top.animjoint, "MenMainConSs_Top_animjoint",
            &MenMainConSs_Top.matanim_joint, "MenMainConSs_Top_matanim_joint",
            &MenMainConSs_Top.shapeanim_joint,
            "MenMainConSs_Top_shapeanim_joint",

            &MenMainCursorSs_Top.joint, "MenMainCursorSs_Top_joint",
            &MenMainCursorSs_Top.animjoint, "MenMainCursorSs_Top_animjoint",
            &MenMainCursorSs_Top.matanim_joint,
            "MenMainCursorSs_Top_matanim_joint",
            &MenMainCursorSs_Top.shapeanim_joint,
            "MenMainCursorSs_Top_shapeanim_joint",

            0);

        if (lbLang_IsSavedLanguageUS()) {
            HSD_SisLib_803A62A0(0, "SdMenu.usd", "SIS_MenuData");
        } else {
            HSD_SisLib_803A62A0(0, "SdMenu.dat", "SIS_MenuData");
        }
        HSD_SisLib_803A62A0(3, "SdToy.dat", "SIS_ToyData");
        gm_801BA8FC();
        lbAudioAx_8002392C();
    }

    mn_8022DDA8_inline(hovered_selection);
    mn_8022BCF8();
    mn_8022BEDC(mn_8022BE34());
    mn_80229B2C();
    mn_80229DC0();

    switch (data->menu_kind) {
    case MENU_KIND_7:
        mnEvent_8024E838(gm_801BEB80(), 0);
        break;
    case MENU_KIND_33:
        mnHyaku_8024CD64(data->hovered_selection);
        break;
    default:
        temp_r3_8 = GObj_Create(0, 1, 0x80);
        if (!(var_r4 = mn_803EB6B0[mn_804A04F0.cur_menu].think)) {
            var_r4 = mn_8022DB10;
        }
        HSD_GObjProc_8038FD54(temp_r3_8, var_r4, 0);
        mn_8022B3A0(0);
        break;
    }
    lbAudioAx_80023F28(gmMainLib_8015ECB0());
    lb_8001CE00();
}

bool mn_8022E950(int arg0)
{
    return gm_80164840(gm_8016400C(arg0));
}

void mn_8022E978(u8 item_idx, u8 enable)
{
    if (enable) {
        gmMainLib_8015CC58()->item_mask |= 1 << item_idx;
    } else {
        gmMainLib_8015CC58()->item_mask &= ~(1 << item_idx);
    }
}

void mn_8022EAE0(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(gobj->hsd_obj);
}

void mn_8022EB04(void* user_data)
{
    HSD_Free(user_data);
}

void mn_8022EBDC(void)
{
    int i;
    for (i = 1; i < 9; i++) {
        mn_8022F0F0(i);
    }
}

float mn_8022EC18(HSD_JObj* arg0, float* arg1, HSD_TypeMask arg2)
{
    float temp_f1;
    float var_f31;

    temp_f1 = mn_8022F298(arg0);
    if (!(arg1[0] <= temp_f1) || !(temp_f1 <= arg1[1])) {
        HSD_JObjReqAnimAll(arg0, *(volatile float*) &arg1[0]);
        mn_8022F3D8(arg0, 0xFFU, arg2);
    }
    if (arg1[2] == -0.1f) {
        var_f31 = mn_8022F298(arg0);
        if (var_f31 < arg1[1]) {
            HSD_JObjAnimAll(arg0);
            var_f31 = mn_8022F298(arg0);
            if (var_f31 > arg1[1]) {
                var_f31 = arg1[1];
                HSD_JObjReqAnimAll(arg0, var_f31);
                mn_8022F3D8(arg0, 0xFFU, arg2);
                HSD_JObjAnimAll(arg0);
            }
        }
    } else {
        HSD_JObjAnimAll(arg0);
        var_f31 = mn_8022F298(arg0);
        if (var_f31 >= arg1[1]) {
            var_f31 = arg1[2] + (var_f31 - arg1[1]);
            HSD_JObjReqAnimAll(arg0, var_f31);
            mn_8022F3D8(arg0, 0xFFU, arg2);
            HSD_JObjAnimAll(arg0);
        }
    }
    return var_f31;
}

/// @brief updates a jobjs animation in accordance to the passed in anim loop
/// setting
/// @param jobj HSD_JObj*
/// @param anim_loop AnimLoopSettings*
/// @return the current frame of the jobjs animation
float mn_8022ED6C(HSD_JObj* jobj, AnimLoopSettings* anim_loop)
{
    float end_frame;
    float cur_frame;

    cur_frame = mn_8022F298(jobj);
    if (!(anim_loop->start_frame <= cur_frame &&
          cur_frame <= anim_loop->end_frame))
    {
        HSD_JObjReqAnimAll(jobj, *(volatile f32*) &anim_loop->start_frame);
    }
    if (anim_loop->loop_frame == -0.1f) {
        cur_frame = mn_8022F298(jobj);
        end_frame = anim_loop->end_frame;
        if (cur_frame < end_frame) {
            HSD_JObjAnimAll(jobj);
            cur_frame = mn_8022F298(jobj);
            end_frame = anim_loop->end_frame;
            if (cur_frame > end_frame) {
                cur_frame = end_frame;
                HSD_JObjReqAnimAll(jobj, cur_frame);
                HSD_JObjAnimAll(jobj);
            }
        }
    } else {
        HSD_JObjAnimAll(jobj);
        cur_frame = mn_8022F298(jobj);
        end_frame = anim_loop->end_frame;
        if (cur_frame >= end_frame) {
            cur_frame = anim_loop->loop_frame + (cur_frame - end_frame);
            HSD_JObjReqAnimAll(jobj, cur_frame);
            HSD_JObjAnimAll(jobj);
        }
    }
    return cur_frame;
}

float mn_8022EE84(HSD_JObj* arg0, AnimLoopSettings* arg1,
                  enum _HSD_TypeMask arg2)
{
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f1;
    f32 var_f31;

    temp_f1 = mn_8022F298(arg0);
    if (!(arg1->start_frame <= temp_f1) || !(temp_f1 <= arg1->end_frame)) {
        HSD_JObjReqAnim(arg0, *(volatile float*) &arg1->start_frame);
        mn_8022F3D8(arg0, 0xFF, arg2);
    }
    if (arg1->loop_frame == -0.1f) {
        var_f31 = mn_8022F298(arg0);
        if (arg1->end_frame != var_f31) {
            HSD_JObjAnim(arg0);
            var_f31 = mn_8022F298(arg0);
            temp_f0 = arg1->end_frame;
            if (var_f31 > temp_f0) {
                var_f31 = temp_f0;
                HSD_JObjReqAnim(arg0, var_f31);
                mn_8022F3D8(arg0, 0xFFU, arg2);
                HSD_JObjAnim(arg0);
            }
        }
    } else {
        HSD_JObjAnim(arg0);
        var_f31 = mn_8022F298(arg0);
        temp_f0_2 = arg1->end_frame;
        if (var_f31 >= temp_f0_2) {
            var_f31 = arg1->loop_frame + (var_f31 - temp_f0_2);
            HSD_JObjReqAnim(arg0, var_f31);
            mn_8022F3D8(arg0, 0xFFU, arg2);
            HSD_JObjAnim(arg0);
        }
    }
    return var_f31;
}

/// @brief updates a jobjs looping animation.
// if the end frame is -0.1f, the animation will stop after reaching the end
// frame.
/// @param arg0 HSD_JObj
/// @param arg1 AnimLoopSettings
float mn_8022EFD8(HSD_JObj* arg0, AnimLoopSettings* arg1)
{
    float temp_f0_2;
    float temp_f1;
    float var_f31;

    temp_f1 = mn_8022F298(arg0);
    if (!(arg1->start_frame <= temp_f1) || !(temp_f1 <= arg1->end_frame)) {
        HSD_JObjReqAnim(arg0, *(volatile float*) &arg1->start_frame);
    }
    if (arg1->loop_frame == -0.1f) {
        var_f31 = mn_8022F298(arg0);
        if (arg1->end_frame != var_f31) {
            HSD_JObjAnim(arg0);
            var_f31 = mn_8022F298(arg0);
            if (var_f31 > arg1->end_frame) {
                var_f31 = arg1->end_frame;
                HSD_JObjReqAnim(arg0, var_f31);
                HSD_JObjAnim(arg0);
            }
        }
    } else {
        HSD_JObjAnim(arg0);
        var_f31 = mn_8022F298(arg0);
        temp_f0_2 = arg1->end_frame;
        if (var_f31 >= temp_f0_2) {
            var_f31 = arg1->loop_frame + (var_f31 - temp_f0_2);
            HSD_JObjReqAnim(arg0, var_f31);
            HSD_JObjAnim(arg0);
        }
    }
    return var_f31;
}

void mn_8022F0F0(int arg0)
{
    HSD_GObj* curr = ((HSD_GObj**) HSD_GObj_Entities)[(u8) arg0];
    PAD_STACK(8);
    while (curr != NULL) {
        HSD_GObj* next = curr->next;
        HSD_GObjPLink_80390228(curr);
        curr = next;
    }
}

void mn_8022F138(u16 arg0, u16 arg1)
{
    int i;
    PAD_STACK(0x18);
    for (i = arg0; i <= arg1; i++) {
        mn_8022F0F0(i);
    }
}

static inline void mn_8022F1A8_inline(u8 arg0)
{
    HSD_GObj* curr = ((HSD_GObj**) HSD_GObj_Entities)[arg0];
    PAD_STACK(8);
    while (curr != NULL) {
        HSD_GObj* next = curr->next;
        HSD_GObj_80390CD4(curr);
        curr = next;
    }
}

void mn_8022F1A8(u16 arg0, u16 arg1)
{
    int i;
    PAD_STACK(8);
    for (i = arg0; i <= arg1; i++) {
        mn_8022F1A8_inline(i);
    }
}

bool mn_8022F218(void)
{
    if (gm_801A36A0(4) & 0x400000000) {
        return true;
    }
    return false;
}

void mn_8022F268(void)
{
    gmMainLib_8015CC34()->unk_x0 = 1;
}

/// @brief returns the current frame of jobjs animation
float mn_8022F298(HSD_JObj* jobj)
{
    HSD_AObj* aobj;
    HSD_DObj* dobj;
    HSD_MObj* mobj;
    HSD_TObj* tobj;

    aobj = jobj->aobj;
    if (aobj != NULL) {
        return aobj->curr_frame;
    }
    dobj = jobj->u.dobj;
    if (dobj != NULL) {
        mobj = dobj->mobj;
        if (mobj != NULL) {
            aobj = mobj->aobj;
            if (aobj != NULL) {
                return aobj->curr_frame;
            }
            tobj = mobj->tobj;
            if (tobj != NULL) {
                aobj = tobj->aobj;
                if (aobj != NULL) {
                    return aobj->curr_frame;
                }
            }
        }
    }
    if (!(jobj->flags & 0x1000)) {
        jobj = jobj->child;
        while (jobj != NULL) {
            float frame = mn_8022F298(jobj);
            if (frame != -1.0f) {
                return frame;
            }
            jobj = jobj->next;
        }
    }
    return -1.0f;
}

void mn_8022F360(HSD_AObj* aobj, void* obj, u32 arg2)
{
    HSD_FObj* fobj = aobj->fobj;
    while (fobj != NULL) {
        if (fobj->obj_type == arg2 || arg2 == 0xFF) {
            HSD_FObjStopAnim(fobj, obj, NULL, 0.0F);
        }
        fobj = fobj->next;
    }
}

void mn_8022F3D8(HSD_JObj* jobj, u8 arg1, HSD_TypeMask mask)
{
    HSD_ForeachAnim(jobj, JOBJ_TYPE, mask, mn_8022F360, AOBJ_ARG_AOU, arg1);
}

#define MY_MAX(x, y) ((x) < (y) ? (y) : (x))
#define MY_MIN(x, y) ((x) > (y) ? (y) : (x))

/**
 * Moves x toward a target value in increments of dx.
 * Returns +1 if x was increased toward the target value,
 * -1 if it was decreased toward the target value,
 * and 0 if it was already at the target and was unchanged.
 */
int mn_8022F410(float* x, float* target, float dx)
{
    if (*x == *target) {
        return 0;
    }
    if (*x < *target) {
        *x = MY_MIN(*x + dx, *target);
        return +1;
    } else {
        *x = MY_MAX(*x - dx, *target);
        return -1;
    }
}

/// Same as mn_8022F410, but for int values instead of float.
int mn_8022F470(int* x, int* target, int dx)
{
    if (*x == *target) {
        return 0;
    }
    if (*x < *target) {
        *x = MY_MIN(*x + dx, *target);
        return +1;
    } else {
        *x = MY_MAX(*x - dx, *target);
        return -1;
    }
}

#pragma push
#pragma dont_inline on
void mn_8022F4CC(void)
{
    if (gm_801A4310() == MJ_TOURNAMENT) {
        HSD_SisLib_803A5E70();
        mn_8022EBDC();
        gm_80190EA4();
        return;
    }
    if (gm_801A4310() == MJ_MENU) {
        mn_80229894(2, 3, 3);
        return;
    }
    HSD_SisLib_803A5E70();
    mn_8022EBDC();
    mnCharSel_802640A0();
}
#pragma pop

// void fn_8022F538(HSD_GObj*) { OSPanic(__FILE__, __LINE__, "not implemented:
// fn_8022F538\n"); } void mn_8022FB88() { OSPanic(__FILE__, __LINE__, "not
// implemented: mn_8022FB88\n"); } void mn_8022FD18() { OSPanic(__FILE__,
// __LINE__, "not implemented: mn_8022FD18\n"); }
