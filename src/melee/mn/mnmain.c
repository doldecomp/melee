#include "mnmain.h"

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
#include <sysdolphin/baselib/mobj.h>
#include <melee/gm/gm_unsplit.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/gm/types.h>
#include <melee/lb/lb_00B0.h>
#include <melee/lb/lb_00CE.h>
#include <melee/lb/lbarchive.h>
#include <melee/lb/lbcardgame.h>
#include <melee/lb/lbcardnew.h>
#include <melee/lb/lblanguage.h>
#include <melee/lb/lbmthp.h>
#include <melee/mn/inlines.h>
#include <melee/mn/mnevent.h>
#include <melee/mn/mnhyaku.h>
#include <melee/sc/types.h>

static HSD_GObj* mn_804D6BA8;
static HSD_GObj* mn_804D6BAC;
static HSD_GObj* mn_804D6BB0;
static u8 mn_804D6BB4;
static u8 mn_804D6BB5;
HSD_Archive* mn_804D6BB8;
static LightList** MenMain_lights;
static HSD_FogDesc* MenMain_fog;
static HSD_CObjDesc* MenMain_cam;
mn_unk2 mn_804D6BC8;

mn_unk1 mn_804A04F0;

static u16 mn_803EAE68[] = {
    0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xA, 0xB, 0xC, 0xD,
};
static u16 mn_803EAE7C[] = {
    0x2, 0x3, 0x4, 0x9, 0xB, 0xC, 0xD, 0x0,
};
static Vec3 mn_803EAE8C[0x22][3] = {
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

static Vec3 mn_803EB354 = { 0, 799, 0 };
static Vec3 mn_803EB360 = { 0, 49, 0 };
static Vec3 mn_803EB36C = { 50, 99, 50 };
static Vec3 mn_803EB378 = { 0, 49, -0.1 };
static Vec3 mn_803EB384 = { 50, 250, 50 };
static Vec3 mn_803EB390 = { 0, 10, -0.1 };
static Vec3 mn_803EB39C = { 320, 339, -0.1 };

static Vec3 mn_803EB3A8 = { 380, 399, -0.1 };
static Vec3 mn_803EB3B4 = { 360, 379, -0.1 };
static Vec3 mn_803EB3C0 = { 340,  359, -0.1 };
static float mn_803EB3CC[] = {
    280,  299,  -0.1,
    300,  319, -0.1,
    320, 339,  -0.1,
    3950, 3999, 3970,
};

static Vec3 mn_803EB3FC[] = {
    { 0, 49, 20 },
    { 50, 99, 70 },
    { 100, 149, 120 },
    { 150, 199, 170 },
    { 200, 249, 220 }
};

static Vec3 mn_803EB438 = { 3550, 3599, 3570 };

static Vec3 mn_803EB444[] = {
    { 400, 449, 420 },
    { 450, 499, 470 },
    { 500, 549, 520 },
    { 550, 599, 570 },
    { 600, 649, 620 },
};

static Vec3 mn_803EB480 = { 3500, 3549, 3520 };

static Vec3 mn_803EB48C[] = {
    { 700, 749, 720 },
    { 750, 799, 770 },
    { 800, 849, 820 },
    { 850, 899, 870 },
    { 900, 949, 920 },
};

static Vec3 mn_803EB4C8[] = {
    { 1000, 1049, 1020 },
    { 1050, 1099, 1070 },
    { 1100, 1149, 1120 },
    { 1150, 1199, 1170 },
};

static Vec3 mn_803EB4F8[] = {
    { 1300, 1349, 1320 },
    { 1350, 1399, 1370 },
    { 1400, 1449, 1420 },
    { 1450, 1499, 1470 },
    { 1500, 1549, 1520 },
    { 1550, 1599, 1570 },
};

static Vec3 mn_803EB540[] = {
    { 1600, 1649, 1620 },
    { 1650, 1699, 1670 },
    { 1700, 1749, 1720 },
    { 1750, 1799, 1770 },
    { 1800, 1849, 1820 },
};

static Vec3 mn_803EB57C[] = {
    { 2000, 2049, 2020 },
    { 2050, 2099, 2070 },
    { 2100, 2149, 2120 },
};

static Vec3 mn_803EB5A0[] = {
    { 3150, 3199, 3170 },
    { 3200, 3249, 3220 },
    { 3250, 3299, 3270 },
};

static Vec3 mn_803EB5C4[] = {
    { 2250, 2299, 2270 },
    { 2300, 2349, 2320 },
    { 2350, 2399, 2370 },
};

static Vec3 mn_803EB5E8[] = {
    { 2550, 2599, 2570 },
    { 2600, 2649, 2620 },
    { 2650, 2699, 2670 },
    { 2700, 2749, 2720 },
    { 2750, 2799, 2770 },
    { 2800, 2849, 2820 },
    { 2850, 2899, 2870 },
    { 2900, 2949, 2920 },
    { 2900, 2949, 2920 },
    { 2900, 2949, 2920 },
};

static u16 mn_803EB660[] = { 0x81, 0x82, 0x83, 0x84, 0x85, 0x00 };
static u16 mn_803EB66C[] = { 0x86, 0x87, 0x88, 0x89, 0x8A, 0x00 };
static u16 mn_803EB678[] = { 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x00 };
static u16 mn_803EB684[] = { 0x9A, 0x9B, 0x9C, 0x9D, 0x9D, 0x9E };
static u16 mn_803EB690[] = { 0x9F, 0xA0, 0xA1, 0xA2, 0xA3, 0x00 };

static u16 mn_803EB69C[] = {
    0xB1, 0xB2,
    0xB3, 0xB4,
    0xB5, 0xB6,
    0xB7, 0xB8,
    0xB9, 0xBA,
};

static u16 mn_804D4B30[4] = { 0x8B, 0x8C, 0x8D, 0x00 };
static u16 mn_804D4B38[4] = { 0x96, 0x97, 0x98, 0x99 };
static u16 mn_804D4B40[4] = { 0xA4, 0xA5, 0xA6, 0x00 };
static u16 mn_804D4B48[4] = { 0xA8, 0xA9, 0xAA, 0x00 };

static struct mn_803EB6B0_t {
    Vec3* x0;
    float x4;
    u16* x8;
    u8 xC;
    void (*x10)(HSD_GObj*);
} mn_803EB6B0[0x22] = {
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

u32 mn_80229624(u32 arg0)
{
    u32 ret = 0;
    u64 inputs_a;
    u64 inputs_b;
    inputs_a = gm_801A36C0(arg0);
    inputs_b = gm_801A36A0(arg0);
    if (mn_804D6BC8.x0 != 0) {
        Menu_DecrementAnimTimer();
        return 0;
    }
    if (inputs_b & 0x100) {
        ret |= MenuEvent_unk4;
    }
    if (inputs_b & 0x1000) {
        ret |= MenuEvent_unk3;
    }
    if (inputs_b & 0x100000000) {
        ret |= MenuEvent_Forward;
    }
    if (inputs_b & 0x200000000) {
        ret |= MenuEvent_Back;
    }
    if (inputs_b & 0x40) {
        ret |= MenuEvent_unk;
    }
    if (inputs_b & 0x20) {
        ret |= MenuEvent_unk2;
    }
    if (inputs_b & 0x400) {
        ret |= MenuEvent_unk5;
    }
    if (inputs_b & 0x800) {
        ret |= MenuEvent_unk6;
    }
    if (inputs_a & 0x1000000000) {
        ret |= MenuEvent_Up;
    }
    if (inputs_a & 0x2000000000) {
        ret |= MenuEvent_Down;
    }
    if (inputs_a & 0x4000000000) {
        ret |= MenuEvent_Left;
    }
    if (inputs_a & 0x8000000000) {
        ret |= MenuEvent_Right;
    }
    return ret;
}

void mn_80229860(s8 arg0)
{
    s8* val = gm_801A4B9C();
    *val = arg0;
    gm_801A4B60();
}

char null_terminator[1] = "\0";

void mn_8022EA08(char* buf, u32 num)
{
    int buf_end = mn_8022EB78(num);
    int i;
    for (i = 0; i < buf_end; i++) {
        buf[buf_end - 1 - i] = mn_8022EB24(num, i) + 0x30;
    }
    buf[buf_end] = null_terminator[0];
}

s32 mn_8022EB24(s32 arg0, s32 arg1)
{
    return (arg0 / powi(0xA, arg1)) % 10;
}

s32 mn_8022EB78(s32 num)
{
    s32 count;
    if (num == 0) {
        return 1;
    }
    count = 0;
    for (;;) {
        if ((num / powi(0xA, count)) != 0) {
            count += 1;
            if (count < 0xB) {
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

    mn_804D6BC8.x0 = 5;
    mn_804A04F0.x1 = mn_804A04F0.x0;
    mn_804A04F0.x0 = arg0;
    mn_804A04F0.x2 = arg1;
    HSD_GObj_80390CD4(mn_8022B3A0(arg2));
    HSD_GObjPLink_80390228(HSD_GObj_804D781C);
    temp_r0 = mn_803EB6B0[arg0].x10;
    if (temp_r0 != NULL) {
        temp_r3 = HSD_GObjProc_8038FD54(GObj_Create(0, 1, 0x80), temp_r0, 0);
        temp_r3->flags_3 = HSD_GObj_804D783C;
    }
}

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

int mn_80229A04(int arg0, int arg1)
{
    int i;
    int count = 0;
    for (i = 0; i < arg1; i++) {
        if (mn_80229938(arg0, i) != 0) {
            count++;
        }
    }
    return count;
}

static u8 mn_80229A04_dontinline(int arg0, int arg1)
{
    return mn_80229A04(arg0, arg1);
}

struct mn_80229A7C_t {
    u8 x0, x1, x2; ///< x0 = menu type, x1 = cursor, x2 = state
    HSD_JObj* x4[42]; ///< these are the menu jobjs, ie buttons, panels, etc
    HSD_Text* xAC; ///< description
};

#pragma push
#pragma dont_inline on
void mn_80229A7C(void* arg0, int arg1, int arg2)
{
    struct mn_80229A7C_t* tmp = arg0;
    HSD_Text* temp_r3;
    HSD_Text* temp_r3_2;
    u16* temp_r31;

    if (tmp->xAC != NULL) {
        HSD_SisLib_803A5CC4(tmp->xAC);
        tmp->xAC = NULL;
    }
    temp_r31 = mn_803EB6B0[arg1].x8;
    if (temp_r31 != 0U) {
        temp_r3_2 = HSD_SisLib_803A5ACC(0, mn_804D6BB4, -9.5f, 9.1f, 17.0f, 364.68332f, 38.38772f);
        tmp->xAC = temp_r3_2;
        temp_r3_2->x24.x = 0.0521f;
        temp_r3_2->x24.y = 0.0521f;
        HSD_SisLib_803A6368(temp_r3_2, temp_r31[arg2]);
    }
}
#pragma pop

static StaticModelDesc MenMainBack_Top;

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

static StaticModelDesc MenMainPanel_Top;
static StaticModelDesc MenMainConTop_Top;
static StaticModelDesc MenMainCursor_Top;
static StaticModelDesc MenMainConRl_Top;
static StaticModelDesc MenMainCursorRl_Top;
static StaticModelDesc MenMainNmRl_Top;
static StaticModelDesc MenMainCursorTr01_Top;
static StaticModelDesc MenMainCursorTr02_Top;
static StaticModelDesc MenMainCursorTr03_Top;
static StaticModelDesc MenMainCursorTr04_Top;
static StaticModelDesc MenMainCursorRl01_Top;
static StaticModelDesc MenMainCursorRl02_Top;
static StaticModelDesc MenMainCursorRl03_Top;
static StaticModelDesc MenMainCursorRl04_Top;
static StaticModelDesc MenMainCursorRl05_Top;
static StaticModelDesc MenMainConIs_Top;
static StaticModelDesc MenMainCursorIs_Top;
static StaticModelDesc MenMainConSs_Top;
static StaticModelDesc MenMainCursorSs_Top;

void fn_80229BF4(HSD_GObj* gobj)
{
    f32 temp_f1;
    void* temp_r28;

    HSD_JObj* sp20;
    HSD_JObj* sp1C;
    Vec3 sp10;

    void* temp_r4;
    struct {
        u8 unk0;
        u8 unk1;
        u8 unk2;
        u8 unk3;
    }* temp_r30;

    temp_r28 = gobj->hsd_obj;
    temp_r30 = gobj->user_data;
    lb_80011E24(temp_r28, &sp20, 4, -1);
    lb_80011E24(temp_r28, &sp1C, 0x29, -1);
    if (temp_r30->unk0 != mn_804A04F0.x0) {
        temp_r30->unk1 = temp_r30->unk0;
        temp_r30->unk0 = mn_804A04F0.x0;
        if (mn_804A04F0.x11 != 0) {
            HSD_JObjReqAnimAll(sp1C, mn_803EAE8C[temp_r30->unk0][0].x);
            temp_r30->unk3 = 0U;
        } else {
            HSD_JObjReqAnimAll(sp1C, mn_803EAE8C[temp_r30->unk1][1].x);
            temp_r30->unk3 = 1U;
        }
    }
    switch (temp_r30->unk3) {
    case 2:
        mn_8022ED6C(sp1C, &mn_803EAE8C[temp_r30->unk0][2]);
        break;
    case 0:
    case 1:
        temp_f1 = mn_8022F298(sp1C);
        if (temp_r30->unk3 == 0) {
            sp10 = mn_803EAE8C[temp_r30->unk0][0];
        } else {
            sp10 = mn_803EAE8C[temp_r30->unk1][1];
        }
        if (temp_f1 >= sp10.y) {
            temp_r30->unk3 = 2;
            HSD_JObjReqAnimAll(sp1C, mn_803EAE8C[temp_r30->unk0][2].x);
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
    u8* temp_r3_2;
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
    HSD_JObjReqAnimAll(spC, mn_803EB354.x);
    HSD_JObjAnimAll(spC);
    if (mn_804A04F0.x0 == 0) {
        HSD_JObjReqAnimAll(sp8, mn_803EAE8C[mn_804A04F0.x0][0].x);
    } else {
        HSD_JObjReqAnimAll(sp8, mn_803EAE8C[mn_804A04F0.x0][2].x);
    }
    HSD_JObjAnimAll(sp8);
    temp_r3_2 = HSD_MemAlloc(4);
    if (temp_r3_2 == NULL) {
        OSReport("Can't get user_data.\n");
        __assert("mnmain.c", 0x427, "user_data");
    }
    GObj_InitUserData(temp_r31, 0, mn_8022EB04, temp_r3_2);
    tmp = mn_804A04F0.x0;
    temp_r3_2[0] = tmp;
    temp_r3_2[1] = tmp;
    temp_r3_2[3] = 0;
    return temp_r31;
}

static const Vec3 mn_803B84E8 = { 0 };
static const Vec3 mn_803B84F4 = { 0 };

void mn_80229F60(HSD_GObj* arg0, HSD_JObj* arg1, int arg2)
{
    float temp_f31;
    struct {
        u8 pad[0xA8];
        HSD_JObj* xA8;
    }* temp_r30;
    mn_unk1* tmp;
    HSD_JObj* jobj;

    HSD_JObj* sp54[7];
    u8 pad50[4];
    Vec3 sp44;
    Vec3 sp38;
    Vec3 sp2C;
    Vec3 sp20;
    u8 pad2[0xC];

    sp44 = mn_803B84E8;
    temp_r30 = arg0->user_data;
    lb_8001204C(arg1, sp54, mn_803EAE7C, 7);
    jobj = sp54[1];
    tmp = &mn_804A04F0;
    HSD_JObjReqAnimAll(jobj, 1.0F);
    HSD_JObjAnimAll(jobj);
    HSD_JObjReqAnim(jobj, mn_803EB6B0[tmp->x0].x4 + arg2 * 2);
    mn_8022F3D8(jobj, 0xC, TOBJ_MASK);
    mn_8022F3D8(jobj, 0xD, TOBJ_MASK);
    mn_8022F3D8(jobj, 0xE, TOBJ_MASK);
    mn_8022F3D8(jobj, 0xF, TOBJ_MASK);
    mn_8022F3D8(jobj, 0x10, TOBJ_MASK);
    mn_8022F3D8(jobj, 0x11, TOBJ_MASK);
    mn_8022F3D8(jobj, 0x12, TOBJ_MASK);
    mn_8022F3D8(jobj, 0x13, TOBJ_MASK);
    HSD_JObjAnim(jobj);
    HSD_JObjReqAnimAll(sp54[0],
                       mn_803EB36C.x + (mn_8022F298(sp54[0]) - mn_803EB360.x));
    HSD_JObjAnimAll(sp54[0]);
    HSD_JObjReqAnimAll(sp54[2],
                       mn_803EB384.x + (mn_8022F298(sp54[2]) - mn_803EB378.x));
    HSD_JObjAnimAll(sp54[2]);
    HSD_JObjReqAnimAll(sp54[3], mn_803EB390.x);
    HSD_JObjAnimAll(sp54[3]);
    HSD_JObjClearFlagsAll(sp54[3], JOBJ_HIDDEN);
    HSD_JObjClearFlagsAll(sp54[4], JOBJ_HIDDEN);

    HSD_JObjSetScaleY(sp54[5], 2.0F);
    HSD_JObjSetScaleY(sp54[6], 2.0F);

    HSD_JObjGetTranslation(sp54[5], &sp20);
    HSD_JObjSetTranslate(sp54[6], &sp20);

    lb_8000B1CC(sp54[5], &sp44, &sp2C);
    lb_8000B1CC(temp_r30->xA8, &sp44, &sp38);
    temp_f31 = atan2f(sp38.y - sp2C.y, sp38.x - sp2C.x);

    HSD_JObjSetRotationZ(sp54[5], temp_f31);
    HSD_JObjSetRotationZ(sp54[6], temp_f31);
}

void mn_8022A440(HSD_GObj* arg0, HSD_JObj* arg1, s32 arg2)
{
    HSD_JObj* sp24[7];
    HSD_JObj* r29;
    mn_unk1* tmp;
    float f;
    PAD_STACK(0x10);

    lb_8001204C(arg1, sp24, mn_803EAE7C, 7);
    r29 = sp24[1];
    tmp = &mn_804A04F0;
    HSD_JObjReqAnimAll(r29, 0.0F);
    HSD_JObjAnimAll(r29);
    HSD_JObjReqAnim(r29, mn_803EB6B0[tmp->x0].x4 + arg2 * 2);
    mn_8022F3D8(r29, 0xC, TOBJ_MASK);
    mn_8022F3D8(r29, 0xD, TOBJ_MASK);
    mn_8022F3D8(r29, 0xE, TOBJ_MASK);
    mn_8022F3D8(r29, 0xF, TOBJ_MASK);
    mn_8022F3D8(r29, 0x10, TOBJ_MASK);
    mn_8022F3D8(r29, 0x11, TOBJ_MASK);
    mn_8022F3D8(r29, 0x12, TOBJ_MASK);
    mn_8022F3D8(r29, 0x13, TOBJ_MASK);
    HSD_JObjAnim(r29);
    f = (mn_8022F298(sp24[0]) - mn_803EB36C.x);
    HSD_JObjReqAnimAll(sp24[0], f + mn_803EB360.x);
    HSD_JObjAnimAll(sp24[0]);
    mn_8022F298(sp24[2]);
    HSD_JObjReqAnimAll(sp24[2], mn_803EB378.x);
    HSD_JObjAnimAll(sp24[2]);
    HSD_JObjSetFlagsAll(sp24[4], JOBJ_HIDDEN);
}

void mn_8022A5D0(HSD_GObj* arg0, int arg1)
{
    u8 pad[8];
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
    struct {
        u8 x0;
        void* x4[(0xA8 - 0x4) / 4];
        HSD_JObj* xA8;
    }* temp_r28;
    int temp_r27;
    int var_r26;
    int var_r24;
    int var_r23;
    int temp_r22_2;
    struct {
        u8 pad[0x10];
        HSD_JObj* unk10;
    }* temp_r3;
    int i;

    var_r4 = mn_803EAE68;
    sp68 = mn_803B84F4;
    // var_r5 = &spA0[0];
    temp_r28 = arg0->user_data;
    temp_r27 = mn_803EB6B0[temp_r28->x0].xC;

    for (i = 0; i < temp_r27; i++) {
        temp_r3 = temp_r28->x4[var_r4[i]];
        if (temp_r3 == NULL) {
            var_r0 = NULL;
        } else {
            var_r0 = temp_r3->unk10;
        }
        spA0[i] = var_r0;
    }
    for (var_r26 = 0; var_r26 < temp_r27; var_r26++) {
        if (mn_80229938(mn_804A04F0.x0, var_r26) != 0) {
            var_r24 = mn_80229A04(mn_804A04F0.x0, var_r26);
            lb_8001204C(spA0[var_r24], sp84, mn_803EAE7C, 7);
            temp_r22_2 = (arg1 == var_r26) * 0xC;
            mn_8022ED6C(sp84[0], &mn_803EB360 + (var_r26 == arg1));
            mn_8022ED6C(sp84[2], &mn_803EB378 + (var_r26 == arg1));
            if (mn_8022ED6C(sp84[3], &mn_803EB390) >= mn_803EB390.y) {
                HSD_JObjSetFlagsAll(sp84[3], 0x10U);
            }
            if (arg1 == var_r26) {
                if (HSD_JObjGetScaleY(sp84[6]) == 2.0f) {
                    lb_8000B1CC(sp84[5], &sp68, &sp50);
                    lb_8000B1CC(temp_r28->xA8, &sp68, &sp5C);
                    sp74.x = sp5C.x - sp50.x;
                    sp74.y = sp5C.y - sp50.y;
                    sp74.z = sp5C.z - sp50.z;
                    HSD_JObjAddTranslationX(sp84[6], sp74.x / 10.0F);
                    HSD_JObjAddTranslationY(sp84[6], sp74.y / 10.0F);
                    HSD_JObjAddTranslationZ(sp84[6], sp74.z / 10.0F);
                    if ((sp74.x >= 0.0f && HSD_JObjGetTranslationX(sp84[6])) >=
                            sp74.x ||
                        (sp74.x < 0.0f && HSD_JObjGetTranslationX(sp84[6])) <=
                            sp74.x)
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

void mn_8022ADD8(HSD_GObj* arg0, int arg1)
{
    f32 temp_f1;
    struct {
        u8 x0;
        u8 x1;
        u8 x2;
        u8 pad[0x3C - 0x3];
        HSD_JObj* x3C;
    }* temp_r30;
    Vec3* var_r29;
    HSD_JObj* temp_r28;
    Vec3* tmp;
    u8 temp_r0;

    temp_r30 = arg0->user_data;
    temp_r28 = temp_r30->x3C;
    switch (temp_r30->x2) {
    case 2:
    case 4:
        HSD_JObjSetFlagsAll(temp_r28, 0x10U);
        break;
    case 0:
    case 1:
    case 3:
    case 5:
        tmp = mn_803EB6B0[temp_r30->x0].x0;
        if (tmp != NULL) {
            if (temp_r30->x0 == 0 && temp_r30->x1 == 4 &&
                gmMainLib_8015EE90() == 0)
            {
                var_r29 = &mn_803EB438;
            } else if (temp_r30->x0 == 1 && temp_r30->x1 == 0 &&
                       gmMainLib_8015EDD4() == 0)
            {
                var_r29 = &mn_803EB480;
            } else {
                var_r29 = &tmp[temp_r30->x1];
            }
            temp_f1 = mn_8022F298(temp_r28);
            if ((u8) arg1 != 0 || !(var_r29->x <= temp_f1) ||
                !(temp_f1 <= var_r29->y))
            {
                HSD_JObjReqAnimAll(temp_r28, var_r29->x);
            }
            mn_8022ED6C(temp_r28, var_r29);
        }
        break;
    }
}

void fn_8022AF10(HSD_GObj* arg0)
{
    struct {
        u16 x0;
        u8 x2;
        u8 pad[0x10 - 0x3];
        HSD_JObj* x10;
    }* temp_r31;
    HSD_JObj* temp_r30;
    Vec3* var_r29;

    temp_r31 = arg0->user_data;
    temp_r30 = temp_r31->x10;
    switch (temp_r31->x2) {
    case 2:
        var_r29 = &mn_803EB3A8;
        break;
    case 4:
        var_r29 = &mn_803EB3C0;
        break;
    }
    if (mn_8022F298(temp_r30) >= var_r29->y) {
        switch (temp_r31->x2) {
        case 2:
        case 4:
            HSD_GObjPLink_80390228(arg0);
            return;
        }
    }
    HSD_JObjAnim(temp_r30);
}

void fn_8022AFEC(HSD_GObj* arg0)
{
    HSD_JObj* sp20[4];
    HSD_GObjProc* temp_r3;
    HSD_JObj* temp_r30;
    struct {
        u8 x0;
        u8 x1;
        u8 x2;
        void* x4[3];
        HSD_JObj* x10;
    }* temp_r30_3;
    HSD_JObj* var_r0;
    Vec3* var_r28;
    struct {
        u8 x0;
        u8 x1;
        u8 x2;
        u8 pad3[0x10 - 0x3];
        HSD_JObj* x10;
    }* temp_r27;
    u8 var_r26;
    u8 var_r25;
    struct mn_80229A7C_t* temp_r24;
    u8 var_r0_2;
    int var_r5;
    u8 temp_r0;
    u8 temp_r0_7;

    struct {
        u8 pad[0x10];
        HSD_JObj* x10;
    }* temp_r3_2;

    PAD_STACK(0x34);

    var_r26 = 0;
    var_r25 = 0;
    temp_r27 = arg0->user_data;
    temp_r0 = temp_r27->x2;
    if ((temp_r0 == 5 || temp_r0 <= 1 || temp_r0 == 3) &&
        temp_r27->x0 != mn_804A04F0.x0)
    {
        if (mn_804A04F0.x11 != 0) {
            temp_r27->x2 = 4U;
        } else {
            temp_r27->x2 = 2U;
        }
        switch (temp_r27->x2) {
        case 1:
            var_r28 = &mn_803EB39C;
            break;
        case 2:
            var_r28 = &mn_803EB3A8;
            break;
        case 3:
            var_r28 = &mn_803EB3B4;
            break;
        case 4:
            var_r28 = &mn_803EB3C0;
            break;
        }
        temp_r30 = temp_r27->x10;
        HSD_JObjReqAnim(temp_r30, var_r28->x);
        HSD_JObjAnim(temp_r30);
        if (temp_r27->x2 == 5 || temp_r27->x2 <= 1 || temp_r27->x2 == 3) {
            var_r26 = 1;
            var_r25 = 1;
        } else {
            HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
            temp_r3 = HSD_GObjProc_8038FD54(arg0, fn_8022AF10, 0U);
            temp_r3->flags_3 = HSD_GObj_804D783C;
        }
    }
    if (temp_r27->x2 == 1 || temp_r27->x2 == 3) {
        temp_r30 = temp_r27->x10;
        switch (temp_r27->x2) {
        case 1:
            var_r28 = &mn_803EB39C;
            break;
        case 3:
            var_r28 = &mn_803EB3B4;
            break;
        case 2:
            var_r28 = &mn_803EB3A8;
            break;
        case 4:
            var_r28 = &mn_803EB3C0;
            break;
        }
        if (mn_8022F298(temp_r30) >= var_r28->y) {
            switch (temp_r27->x2) {
            case 1:
            case 3:
                temp_r27->x2 = 0;
                break;
            case 2:
            case 4:
                HSD_GObjPLink_80390228(arg0);
                return;
            }
        }
        HSD_JObjAnim(temp_r30);
    }
    if (temp_r27->x2 == 0 || temp_r27->x2 == 1 || temp_r27->x2 == 3) {
        if (temp_r27->x1 != mn_804A04F0.x2) {
            var_r25 = 1;
        }
        temp_r30_3 = arg0->user_data;
        temp_r0_7 = mn_803EB6B0[temp_r30_3->x0].xC;
        {
            int i;
            for (i = 0; i < temp_r0_7; i++) {
                temp_r3_2 = temp_r30_3->x4[mn_803EAE68[i]];
                if (temp_r3_2 == NULL) {
                    var_r0 = NULL;
                } else {
                    var_r0 = temp_r3_2->x10;
                }
                sp20[i] = var_r0;
            }
        }
        if (var_r25 != 0) {
            mn_80229F60(
                arg0,
                sp20[mn_80229A04_dontinline(mn_804A04F0.x0, mn_804A04F0.x2)],
                mn_804A04F0.x2);
            mn_8022A440(
                arg0,
                sp20[mn_80229A04_dontinline(mn_804A04F0.x0, temp_r30_3->x1)], mn_804A04F0.x1);
        }
        if (var_r25 != 0) {
            var_r0_2 = mn_804A04F0.x2;
        } else {
            var_r0_2 = temp_r30_3->x1;
        }
        mn_8022A5D0(arg0, var_r0_2);
    }
    mn_8022ADD8(arg0, var_r25);
    temp_r24 = arg0->user_data;
    if (var_r25 != 0) {
        var_r5 = mn_804A04F0.x2;
    } else {
        var_r5 = temp_r24->x1;
    }
    switch (temp_r24->x2) {
    case 1:
    case 3:
    case 5:
        break;
    case 2:
    case 4:
        if (temp_r24->xAC != NULL) {
            HSD_SisLib_803A5CC4(temp_r24->xAC);
            temp_r24->xAC = NULL;
        }
        break;
    case 0:
        if (var_r25 != 0) {
            mn_80229A7C(temp_r24, temp_r24->x0, var_r5);
        }
        temp_r24->xAC->x4D = 0;
        break;
    }
    if (var_r26 != 0) {
        temp_r27->x0 = mn_804A04F0.x0;
    }
    if (var_r25 != 0) {
        temp_r27->x1 = mn_804A04F0.x2;
    }
}

HSD_GObj* mn_8022B3A0(u8 state)
{
    HSD_JObj* sp48[1];
    HSD_JObj* sp2C[5];

    int temp_r31;
    HSD_GObj* gobj;
    HSD_JObj* temp_r16_2;
    HSD_JObj* root_jobj;
    HSD_JObj* cursor_jobj;
    HSD_JObj** temp_r19_2;
    HSD_Text* temp_r3_6;
    int temp_r22_3;
    int temp_r3_3;
    s8 temp_r25;
    int var_r21;
    int var_r19;
    int var_r18;
    int idx;
    u8 var_r17;
    int var_r17_2;
    int var_r16_2;
    struct mn_803EB6B0_t* temp_r19;
    Vec3* var_r4_3;
    u16* temp_r16_4;
    u8 temp_r16_3;
    u8 temp_r17;
    u8 temp_r21;
    u8 temp_r22;
    u8 temp_r22_2;
    struct mn_80229A7C_t* menu_data;
    int i;
    HSD_JObj* jobj;
    Vec3* tmp;

    var_r17 = 0;
    var_r18 = 0;
    temp_r21 = mn_804A04F0.x0;
    temp_r19 = &mn_803EB6B0[temp_r21];
    temp_r22 = mn_803EB6B0[temp_r21].xC;
    temp_r25 = mn_804A04F0.x2;

    while (var_r18 < mn_803EB6B0[temp_r21].xC) {
        if (mn_80229938(temp_r21, var_r18) != 0) {
            var_r17++;
        }
        var_r18++;
    }
    gobj = GObj_Create(6, 7, 0x80);
    root_jobj = HSD_JObjLoadJoint(MenMainConTop_Top.joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, root_jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 4, 0x80);
    HSD_GObjProc_8038FD54(gobj, fn_8022AFEC, 0);
    HSD_JObjAddAnimAll(root_jobj, MenMainConTop_Top.animjoint,
                       MenMainConTop_Top.matanim_joint,
                       MenMainConTop_Top.shapeanim_joint);
    HSD_JObjReqAnimAll(root_jobj, 0.0F);
    menu_data = HSD_MemAlloc(sizeof(*menu_data));
    if (menu_data == NULL) {
        OSReport("Can't get user_data.\n");
        __assert("mnmain.c", 0x65D, "user_data");
    }
    GObj_InitUserData(gobj, 0, mn_8022EB04, menu_data);
    idx = 0;
    menu_data->x0 = (u8) mn_804A04F0.x0;
    menu_data->x1 = (u8) mn_804A04F0.x2;
    menu_data->x2 = state;
    menu_data->xAC = NULL;
    do {
        lb_80011E24(root_jobj, &menu_data->x4[idx], idx, -1);
        idx += 1;
    } while (idx < 0x2A);
    if (menu_data->x2 != 0) {
        switch (menu_data->x2) {
        case 1:
            HSD_JObjReqAnim(menu_data->x4[3], mn_803EB39C.x);
            break;
        case 3:
            HSD_JObjReqAnim(menu_data->x4[3], mn_803EB3B4.x);
            break;
        }
        HSD_JObjAnim(menu_data->x4[3]);
    }
    for (i = 0; i < temp_r22; i++) {
        sp48[i] = menu_data->x4[mn_803EAE68[i]];
    }
    var_r17_2 = 0;
    var_r21 = 0;
    while (var_r17_2 < temp_r22) {
        if (mn_80229938(mn_804A04F0.x0, var_r17_2) != 0) {
            var_r16_2 = 0;
            temp_r22_2 = mn_804A04F0.x0;
            var_r19 = 0;
            var_r16_2 = mn_80229A04(0, var_r17_2);
            temp_r19_2 = &sp48[var_r16_2];
            HSD_JObjReqAnim(*temp_r19_2, (f32) var_r17);
            HSD_JObjAnim(*temp_r19_2);
            cursor_jobj = HSD_JObjLoadJoint(MenMainCursor_Top.joint);
            HSD_JObjAddAnimAll(cursor_jobj, MenMainCursor_Top.animjoint,
                               MenMainCursor_Top.matanim_joint,
                               MenMainCursor_Top.shapeanim_joint);
            lb_8001204C(cursor_jobj, sp2C, mn_803EAE7C, 7);
            temp_r22_3 = temp_r25 == var_r17_2;
            tmp = &mn_803EB378 + temp_r22_3;
            HSD_JObjReqAnim(sp2C[0], mn_803EB360.x);
            HSD_JObjAnim(sp2C[0]);
            jobj = sp2C[1];
            HSD_JObjReqAnimAll(jobj, temp_r25 == var_r17_2);
            HSD_JObjAnimAll(jobj);
            HSD_JObjReqAnim(jobj, mn_803EB6B0[mn_804A04F0.x0].x4 + var_r21);
            mn_8022F3D8(jobj, 0xC, TOBJ_MASK);
            mn_8022F3D8(jobj, 0xD, TOBJ_MASK);
            mn_8022F3D8(jobj, 0xE, TOBJ_MASK);
            mn_8022F3D8(jobj, 0xF, TOBJ_MASK);
            mn_8022F3D8(jobj, 0x10, TOBJ_MASK);
            mn_8022F3D8(jobj, 0x11, TOBJ_MASK);
            mn_8022F3D8(jobj, 0x12, TOBJ_MASK);
            mn_8022F3D8(jobj, 0x13, TOBJ_MASK);
            HSD_JObjAnim(jobj);
            if (var_r17_2 == temp_r25) {
                HSD_JObjReqAnimAll(sp2C[2], tmp->x);
            } else {
                HSD_JObjReqAnimAll(sp2C[2], tmp->y);
            }
            HSD_JObjAnimAll(sp2C[2]);
            if (var_r17_2 == temp_r25) {
                HSD_JObjReqAnim(sp2C[3], mn_803EB390.x);
            } else {
                HSD_JObjSetFlagsAll(sp2C[3], JOBJ_HIDDEN);
            }
            HSD_JObjAnim(sp2C[3]);
            if (var_r17_2 != temp_r25) {
                HSD_JObjSetFlagsAll(sp2C[4], JOBJ_HIDDEN);
            }
            HSD_JObjAddChild(*temp_r19_2, cursor_jobj);
        }
        var_r21 += 2;
        var_r17_2 += 1;
    }
    temp_r16_2 = menu_data->x4[14];
    if ((menu_data->x0 == 0) && (menu_data->x1 == 4) &&
        (gmMainLib_8015EE90() == 0))
    {
        var_r4_3 = &mn_803EB438;
    } else if ((menu_data->x0 == 1) && (menu_data->x1 == 0) &&
               (gmMainLib_8015EDD4() == 0))
    {
        var_r4_3 = &mn_803EB480;
    } else {
        var_r4_3 = &mn_803EB6B0[temp_r21].x0[menu_data->x1];
    }
    HSD_JObjReqAnimAll(temp_r16_2, var_r4_3->x);
    HSD_JObjAnimAll(temp_r16_2);
    temp_r17 = menu_data->x1;
    temp_r16_3 = menu_data->x0;
    if (menu_data->xAC != NULL) {
        HSD_SisLib_803A5CC4(menu_data->xAC);
        menu_data->xAC = NULL;
    }
    temp_r16_4 = mn_803EB6B0[temp_r16_3].x8;
    if (temp_r16_4 != NULL) {
        temp_r3_6 = HSD_SisLib_803A5ACC(0, mn_804D6BB4, -9.5F, 9.1F, 17.0F,
                                        364.68332F, 38.38772F);
        menu_data->xAC = temp_r3_6;
        temp_r3_6->x24.x = 0.0521F;
        temp_r3_6->x24.y = 0.0521F;
        HSD_SisLib_803A6368(temp_r3_6, temp_r16_4[temp_r17]);
    }
    return gobj;
}

static const Vec3 mn_803B8500 = { 0, 1, 0 };

void mn_8022BA1C(HSD_GObj* arg0)
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

    HSD_CObj* temp_r31 = GET_COBJ(arg0);
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
                var_f0 = 0.4f;
            }
            var_f31 = 30.0f * ((x - var_f0) / 0.6f);
        }
        if (-0.4F < y && y < 0.4f) {
            var_f30 = 0.0f;
        } else {
            if (y < 0.0f) {
                var_f0 = -0.4f;
            } else {
                var_f0 = 0.4f;
            }
            var_f30 = 30.0f * ((y - var_f0) / 0.6f);
        }
    }
    HSD_CObjInit(temp_r31, MenMain_cam);
    sp30 = mn_803B8500;
    HSD_CObjGetEyeVector(temp_r31, &sp48);
    HSD_CObjGetInterest(temp_r31, &sp18);
    PSVECCrossProduct(&sp30, &sp48, &sp3C);
    PSVECNormalize(&sp3C, &sp3C);
    PSMTXRotAxisRad(sp54, &sp3C, 0.017453292f * var_f30);
    PSMTXMultVec(sp54, &sp48, &sp48);
    PSMTXRotAxisRad(sp54, &sp30, 0.017453292f * var_f31);
    PSMTXMultVec(sp54, &sp48, &sp48);
    PSVECScale(&sp48, &sp48, HSD_CObjGetEyeDistance(temp_r31));
    PSVECSubtract(&sp18, &sp48, &sp24);
    HSD_CObjSetEyePosition(temp_r31, &sp24);
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

/// #mn_8022BFBC

#pragma push
#pragma dont_inline on
int mn_8022C010(int arg0, int arg1)
{
    if (arg0 == 0) {
        return arg1;
    }
    switch (arg0) {
    case 1:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 33:
        return 0;
    case 2:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
        return 1;
    case 3:
        return 2;
    case 4:
    case 19:
    case 20:
    case 21:
    case 22:
    case 23:
    case 24:
        return 3;
    case 5:
    case 25:
    case 26:
    case 27:
    case 28:
    case 29:
    case 30:
    case 31:
    case 32:
        return 4;
    }
}
#pragma pop

/// #mn_8022C068

/// #fn_8022C128

/// #mn_8022C304

void mn_8022C4F4(HSD_GObj* arg0)
{
    HSD_GObj* gobj;
    HSD_GObjProc* temp_r3_2;
    int temp_r29 = mn_803EB6B0[12].xC;
    u8* data;
    void (*temp_r28)(HSD_GObj*);
    u32 temp_r3 = mn_80229624(4);

    PAD_STACK(8);

    mn_804A04F0.x8 = temp_r3;
    if (temp_r3 & 0x10) {
        mn_804D6BC8.x0 = 5;
        mn_804A04F0.x11 = 1;
        switch (mn_804A04F0.x2) {
        case 0:
            lbAudioAx_80024030(1);
            data = gm_801A4B9C();
            *data = 0xA;
            gm_801A4B60();
            break;
        case 1:
            lbAudioAx_80024030(1);
            data = gm_801A4B9C();
            *data = 0x1F;
            gm_801A4B60();
            break;
        case 2:
            lbAudioAx_80024030(1);
            data = gm_801A4B9C();
            *data = 0x10;
            gm_801A4B60();
            break;
        case 3:
            lbAudioAx_80024030(1);
            data = gm_801A4B9C();
            *data = 0x1E;
            gm_801A4B60();
            break;
        case 4:
            lbAudioAx_80024030(1);
            data = gm_801A4B9C();
            *data = 0x1D;
            gm_801A4B60();
            break;
        case 5:
            lbAudioAx_80024030(1);
            data = gm_801A4B9C();
            *data = 0x11;
            gm_801A4B60();
            break;
        case 6:
            lbAudioAx_80024030(1);
            data = gm_801A4B9C();
            *data = 0x2A;
            gm_801A4B60();
            break;
        case 7:
            lbAudioAx_80024030(1);
            data = gm_801A4B9C();
            *data = 0x2C;
            gm_801A4B60();
            break;
        case 8:
            lbAudioAx_80024030(1);
            data = gm_801A4B9C();
            *data = 0x13;
            gm_801A4B60();
            break;
        case 9:
            lbAudioAx_80024030(1);
            data = gm_801A4B9C();
            *data = 0x12;
            gm_801A4B60();
            break;
        }
    } else if (temp_r3 & 0x20) {
        lbAudioAx_80024030(0);
        mn_804A04F0.x11 = 0;
        mn_804D6BC8.x0 = 5;
        mn_804A04F0.x1 = mn_804A04F0.x0;
        mn_804A04F0.x0 = 2;
        mn_804A04F0.x2 = 2;
        HSD_GObj_80390CD4(mn_8022B3A0(3));
        HSD_GObjPLink_80390228(HSD_GObj_804D781C);
        if ((temp_r28 = mn_803EB6B0[2].x10)) {
            gobj = GObj_Create(0, 1, 0x80);
            temp_r3_2 = HSD_GObjProc_8038FD54(gobj, temp_r28, 0);
            temp_r3_2->flags_3 = HSD_GObj_804D783C;
        }
    } else if (temp_r3 & 1) {
        lbAudioAx_80024030(2);
        do {
            if (mn_804A04F0.x2 != 0) {
                mn_804A04F0.x2--;
            } else {
                mn_804A04F0.x2 = (u8) temp_r29 - 1;
            }
        } while (!mn_80229938(mn_804A04F0.x0, mn_804A04F0.x2));
    } else if (temp_r3 & 2) {
        lbAudioAx_80024030(2);
        do {
            if (mn_804A04F0.x2 == (u8) temp_r29 - 1) {
                mn_804A04F0.x2 = 0;
            } else {
                mn_804A04F0.x2++;
            }
        } while (!mn_80229938(mn_804A04F0.x0, mn_804A04F0.x2));
    }
}

/// #mn_8022C7CC

/// #mn_8022CA54

/// #mn_8022CC28

/// #mn_8022CE6C

/// #mn_8022D104

/// #mn_8022D34C

/// #mn_8022D594

/// #mn_8022D7F4

/// #mn_8022DB10

void mn_8022DD38_OnFrame(void)
{
    u8* tmp;
    if (mn_8022F218() && mn_804A04F0.x0 != 0) {
        lbAudioAx_80023694();
        lbAudioAx_80024030(0);
        mn_8022F268();
        gm_801603B0();
        lb_8001B760(0xB);
        lbMthp_8001F800();
        mn_8022EBDC();
        HSD_SisLib_803A5E70();
        tmp = gm_801A4B9C();
        *tmp = 1;
        gm_801A4B60();
    }
}

u8 data_pad[0xd5c - 0xc4c] = { 0 };

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
    mn_804A04F0.x12 = 0;
    temp_r29 = mn_8022C010(mn_804A04F0.x0, *sp2B4);
    mn_804A04F0.x14 = mn_8022BFBC();
    mn_8022C068(lobj, temp_r29, mn_804A04F0.x12);
}

void mn_8022DDA8_OnEnter(void* arg0_)
{
    struct {
        u8 x0;
        u8 x1;
        u8 x2;
    }* arg0 = arg0_;
    u16* sp2B4;
    HSD_GObj* temp_r3_8;
    u8 temp_r0;
    void (*var_r4)(HSD_GObj*);

    u8 _[0x14];

    mn_804D6BC8.x0 = 0x14;
    mn_804D6BC8.x2 = 0;
    mn_804D6BC8.x4 = 0;
    mn_804A04F0.x8 = 0;
    sp2B4 = &mn_804A04F0.x2;
    temp_r0 = arg0->x0;
    mn_804A04F0.x0 = temp_r0;
    mn_804A04F0.x1 = temp_r0;
    *sp2B4 = arg0->x1;
    mn_804D6BAC = NULL;
    mn_804D6BB0 = NULL;
    if (arg0->x2 != 0) {
        mn_804D6BB8 = lbArchive_LoadSymbols("MnMaAll",
                &MenMainBack_Top.joint, "MenMainBack_Top_joint",
                &MenMainBack_Top.animjoint, "MenMainBack_Top_animjoint",
                &MenMainBack_Top.matanim_joint, "MenMainBack_Top_matanim_joint",
                &MenMainBack_Top.shapeanim_joint, "MenMainBack_Top_shapeanim_joint",

                &MenMain_cam, "ScMenMain_cam_int1_camera",
                &MenMain_lights, "ScMenMain_scene_lights",
                &MenMain_fog, "ScMenMain_fog",

                &MenMainPanel_Top.joint, "MenMainPanel_Top_joint",
                &MenMainPanel_Top.animjoint, "MenMainPanel_Top_animjoint",
                &MenMainPanel_Top.matanim_joint, "MenMainPanel_Top_matanim_joint",
                &MenMainPanel_Top.shapeanim_joint, "MenMainPanel_Top_shapeanim_joint",

                &MenMainConTop_Top.joint, "MenMainConTop_Top_joint",
                &MenMainConTop_Top.animjoint, "MenMainConTop_Top_animjoint",
                &MenMainConTop_Top.matanim_joint, "MenMainConTop_Top_matanim_joint",
                &MenMainConTop_Top.shapeanim_joint, "MenMainConTop_Top_shapeanim_joint",

                &MenMainCursor_Top.joint, "MenMainCursor_Top_joint",
                &MenMainCursor_Top.animjoint, "MenMainCursor_Top_animjoint",
                &MenMainCursor_Top.matanim_joint, "MenMainCursor_Top_matanim_joint",
                &MenMainCursor_Top.shapeanim_joint, "MenMainCursor_Top_shapeanim_joint",

                &MenMainConRl_Top.joint, "MenMainConRl_Top_joint",
                &MenMainConRl_Top.animjoint, "MenMainConRl_Top_animjoint",
                &MenMainConRl_Top.matanim_joint, "MenMainConRl_Top_matanim_joint",
                &MenMainConRl_Top.shapeanim_joint, "MenMainConRl_Top_shapeanim_joint",

                &MenMainCursorRl_Top.joint, "MenMainCursorRl_Top_joint",
                &MenMainCursorRl_Top.animjoint, "MenMainCursorRl_Top_animjoint",
                &MenMainCursorRl_Top.matanim_joint, "MenMainCursorRl_Top_matanim_joint",
                &MenMainCursorRl_Top.shapeanim_joint, "MenMainCursorRl_Top_shapeanim_joint",

                &MenMainNmRl_Top.joint, "MenMainNmRl_Top_joint",
                &MenMainNmRl_Top.animjoint, "MenMainNmRl_Top_animjoint",
                &MenMainNmRl_Top.matanim_joint, "MenMainNmRl_Top_matanim_joint",
                &MenMainNmRl_Top.shapeanim_joint, "MenMainNmRl_Top_shapeanim_joint",

                &MenMainCursorTr01_Top.joint, "MenMainCursorTr01_Top_joint",
                &MenMainCursorTr01_Top.animjoint, "MenMainCursorTr01_Top_animjoint",
                &MenMainCursorTr01_Top.matanim_joint, "MenMainCursorTr01_Top_matanim_joint",
                &MenMainCursorTr01_Top.shapeanim_joint, "MenMainCursorTr01_Top_shapeanim_joint",

                &MenMainCursorTr02_Top.joint, "MenMainCursorTr02_Top_joint",
                &MenMainCursorTr02_Top.animjoint, "MenMainCursorTr02_Top_animjoint",
                &MenMainCursorTr02_Top.matanim_joint, "MenMainCursorTr02_Top_matanim_joint",
                &MenMainCursorTr02_Top.shapeanim_joint, "MenMainCursorTr02_Top_shapeanim_joint",

                &MenMainCursorTr03_Top.joint, "MenMainCursorTr03_Top_joint",
                &MenMainCursorTr03_Top.animjoint, "MenMainCursorTr03_Top_animjoint",
                &MenMainCursorTr03_Top.matanim_joint, "MenMainCursorTr03_Top_matanim_joint",
                &MenMainCursorTr03_Top.shapeanim_joint, "MenMainCursorTr03_Top_shapeanim_joint",

                &MenMainCursorTr04_Top.joint, "MenMainCursorTr04_Top_joint",
                &MenMainCursorTr04_Top.animjoint, "MenMainCursorTr04_Top_animjoint",
                &MenMainCursorTr04_Top.matanim_joint, "MenMainCursorTr04_Top_matanim_joint",
                &MenMainCursorTr04_Top.shapeanim_joint, "MenMainCursorTr04_Top_shapeanim_joint",

                &MenMainCursorRl01_Top.joint, "MenMainCursorRl01_Top_joint",
                &MenMainCursorRl01_Top.animjoint, "MenMainCursorRl01_Top_animjoint",
                &MenMainCursorRl01_Top.matanim_joint, "MenMainCursorRl01_Top_matanim_joint",
                &MenMainCursorRl01_Top.shapeanim_joint, "MenMainCursorRl01_Top_shapeanim_joint",

                &MenMainCursorRl02_Top.joint, "MenMainCursorRl02_Top_joint",
                &MenMainCursorRl02_Top.animjoint, "MenMainCursorRl02_Top_animjoint",
                &MenMainCursorRl02_Top.matanim_joint, "MenMainCursorRl02_Top_matanim_joint",
                &MenMainCursorRl02_Top.shapeanim_joint, "MenMainCursorRl02_Top_shapeanim_joint",

                &MenMainCursorRl03_Top.joint, "MenMainCursorRl03_Top_joint",
                &MenMainCursorRl03_Top.animjoint, "MenMainCursorRl03_Top_animjoint",
                &MenMainCursorRl03_Top.matanim_joint, "MenMainCursorRl03_Top_matanim_joint",
                &MenMainCursorRl03_Top.shapeanim_joint, "MenMainCursorRl03_Top_shapeanim_joint",

                &MenMainCursorRl04_Top.joint, "MenMainCursorRl04_Top_joint",
                &MenMainCursorRl04_Top.animjoint, "MenMainCursorRl04_Top_animjoint",
                &MenMainCursorRl04_Top.matanim_joint, "MenMainCursorRl04_Top_matanim_joint",
                &MenMainCursorRl04_Top.shapeanim_joint, "MenMainCursorRl04_Top_shapeanim_joint",

                &MenMainCursorRl05_Top.joint, "MenMainCursorRl05_Top_joint",
                &MenMainCursorRl05_Top.animjoint, "MenMainCursorRl05_Top_animjoint",
                &MenMainCursorRl05_Top.matanim_joint, "MenMainCursorRl05_Top_matanim_joint",
                &MenMainCursorRl05_Top.shapeanim_joint, "MenMainCursorRl05_Top_shapeanim_joint",

                &MenMainConIs_Top.joint, "MenMainConIs_Top_joint",
                &MenMainConIs_Top.animjoint, "MenMainConIs_Top_animjoint",
                &MenMainConIs_Top.matanim_joint, "MenMainConIs_Top_matanim_joint",
                &MenMainConIs_Top.shapeanim_joint, "MenMainConIs_Top_shapeanim_joint",

                &MenMainCursorIs_Top.joint, "MenMainCursorIs_Top_joint",
                &MenMainCursorIs_Top.animjoint, "MenMainCursorIs_Top_animjoint",
                &MenMainCursorIs_Top.matanim_joint, "MenMainCursorIs_Top_matanim_joint",
                &MenMainCursorIs_Top.shapeanim_joint, "MenMainCursorIs_Top_shapeanim_joint",

                &MenMainConSs_Top.joint, "MenMainConSs_Top_joint",
                &MenMainConSs_Top.animjoint, "MenMainConSs_Top_animjoint",
                &MenMainConSs_Top.matanim_joint, "MenMainConSs_Top_matanim_joint",
                &MenMainConSs_Top.shapeanim_joint, "MenMainConSs_Top_shapeanim_joint",

                &MenMainCursorSs_Top.joint, "MenMainCursorSs_Top_joint",
                &MenMainCursorSs_Top.animjoint, "MenMainCursorSs_Top_animjoint",
                &MenMainCursorSs_Top.matanim_joint, "MenMainCursorSs_Top_matanim_joint",
                &MenMainCursorSs_Top.shapeanim_joint, "MenMainCursorSs_Top_shapeanim_joint",

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

    mn_8022DDA8_inline(sp2B4);
    mn_8022BCF8();
    mn_8022BEDC(mn_8022BE34());
    mn_80229B2C();
    mn_80229DC0();

    switch (arg0->x0) {
    case 7:
        mnEvent_8024E838(gm_801BEB80(), 0);
        break;
    case 33:
        mnHyaku_8024CD64(arg0->x1);
        break;
    default:
        temp_r3_8 = GObj_Create(0, 1, 0x80);
        if (!(var_r4 = mn_803EB6B0[mn_804A04F0.x0].x10)) {
            var_r4 = mn_8022DB10;
        }
        HSD_GObjProc_8038FD54(temp_r3_8, var_r4, 0);
        mn_8022B3A0(0);
        break;
    }
    lbAudioAx_80023F28(gmMainLib_8015ECB0());
    lb_8001CE00();
}

/// #mn_8022E950

/// #mn_8022E978

/// #mn_8022EA08

/// #mn_8022EA78

void mn_8022EAE0(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(gobj->hsd_obj);
}

void mn_8022EB04(void* user_data)
{
    HSD_Free(user_data);
}

/// #mn_8022EB24

/// #mn_8022EB78

/// #mn_8022EBDC

/// #mn_8022EC18

float mn_8022ED6C(HSD_JObj* jobj, Vec3* arg1)
{
    float temp_f0;
    float temp_f1;

    temp_f1 = mn_8022F298(jobj);
    if (!(arg1->x <= temp_f1 && temp_f1 <= arg1->y)) {
        HSD_JObjReqAnimAll(jobj, *(volatile f32*) &arg1->x);
    }
    if (arg1->z == -0.1f) {
        temp_f1 = mn_8022F298(jobj);
        temp_f0 = arg1->y;
        if (temp_f1 < temp_f0) {
            HSD_JObjAnimAll(jobj);
            temp_f1 = mn_8022F298(jobj);
            temp_f0 = arg1->y;
            if (temp_f1 > temp_f0) {
                temp_f1 = temp_f0;
                HSD_JObjReqAnimAll(jobj, temp_f1);
                HSD_JObjAnimAll(jobj);
            }
        }
    } else {
        HSD_JObjAnimAll(jobj);
        temp_f1 = mn_8022F298(jobj);
        temp_f0 = arg1->y;
        if (temp_f1 >= temp_f0) {
            temp_f1 = arg1->z + (temp_f1 - temp_f0);
            HSD_JObjReqAnimAll(jobj, temp_f1);
            HSD_JObjAnimAll(jobj);
        }
    }
    return temp_f1;
}

/// #mn_8022EE84

float mn_8022EFD8(HSD_JObj* arg0, Vec3* arg1)
{
    float temp_f0;
    float temp_f0_2;
    float temp_f1;
    float var_f31;

    temp_f1 = mn_8022F298(arg0);
    if (!(arg1->x <= temp_f1) || !(temp_f1 <= arg1->y)) {
        HSD_JObjReqAnim(arg0, arg1->x);
    }
    if (arg1->z == -0.1f) {
        var_f31 = mn_8022F298(arg0);
        if (arg1->y != var_f31) {
            HSD_JObjAnim(arg0);
            var_f31 = mn_8022F298(arg0);
            temp_f0 = arg1->y;
            if (var_f31 > temp_f0) {
                var_f31 = temp_f0;
                HSD_JObjReqAnim(arg0, var_f31);
                HSD_JObjAnim(arg0);
            }
        }
    } else {
        HSD_JObjAnim(arg0);
        var_f31 = mn_8022F298(arg0);
        temp_f0_2 = arg1->y;
        if (var_f31 >= temp_f0_2) {
            var_f31 = arg1->z + (var_f31 - temp_f0_2);
            HSD_JObjReqAnim(arg0, var_f31);
            HSD_JObjAnim(arg0);
        }
    }
    return var_f31;
}

/// #mn_8022F0F0

void mn_8022F138(u16 arg0, u16 arg1)
{
    HSD_GObj* curr;
    HSD_GObj* next;
    int i;
    PAD_STACK(0x18);
    for (i = arg0; i <= arg1; i++) {
        curr = ((HSD_GObj**) HSD_GObj_Entities)[(u8) i];
        while (curr != NULL) {
            next = curr->next;
            HSD_GObjPLink_80390228(curr);
            curr = next;
        }
    }
}

void mn_8022F1A8(u16 arg0, u16 arg1)
{
    HSD_GObj* curr;
    HSD_GObj* next;
    int i;
    PAD_STACK(8);
    for (i = arg0; i <= arg1; i++) {
        curr = ((HSD_GObj**) HSD_GObj_Entities)[(u8) i];
        while (curr != NULL) {
            next = curr->next;
            HSD_GObj_80390CD4(curr);
            curr = next;
        }
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

/// #mn_8022F410

/// #mn_8022F470

/// #mn_8022F4CC

/// #fn_8022F538

/// #mn_8022FB88

/// #mn_8022FD18
