#include <platform.h>

#include <baselib/forward.h>

#include "mn/mn_2295.h"

#include "gm/gm_1A36.h"
#include "gm/gmmain_lib.h"
#include "lb/lb_00CE.h"
#include "mn/inlines.h"
#include "sc/types.h"

#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/dobj.h>
#include <sysdolphin/baselib/mobj.h>

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

char null_terminator = '\0';

void mn_8022EA08(char* buf, u32 num)
{
    s32 buf_end = mn_8022EB78(num);
    s32 buf_len = buf_end - 1;
    s32 idx = 0;
    while (idx < buf_end) {
        buf[buf_len - idx] = mn_8022EB24(num, idx) + 0x30;
        idx += 1;
    }
    buf[buf_end] = null_terminator;
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

static struct {
    UNK_T x0;
    u32 x4;
    u16* x8;
    u32 xC;
    void (*x10)(HSD_GObj*);
} mn_803EB6B0[0x22] = { 0 };

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

extern u8 mn_804D6BB4;

struct mn_80229A7C_t {
    u8 pad[0xAC];
    UNK_T xAC;
};

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

static u8 bss_pad[0x18];
static StaticModelDesc mn_804A0508;

HSD_GObj* mn_80229B2C(void)
{
    HSD_GObj* temp_r30;
    HSD_JObj* temp_r3;

    temp_r30 = GObj_Create(4, 5, 0x80);
    temp_r3 = HSD_JObjLoadJoint(mn_804A0508.joint);
    HSD_GObjObject_80390A70(temp_r30, HSD_GObj_804D7849, temp_r3);
    GObj_SetupGXLink(temp_r30, HSD_GObj_JObjCallback, 2, 0x80);
    HSD_GObjProc_8038FD54(temp_r30, mn_8022EAE0, 0);
    HSD_JObjAddAnimAll(temp_r3, mn_804A0508.animjoint, mn_804A0508.matanim_joint, mn_804A0508.shapeanim_joint);
    HSD_JObjReqAnimAll(temp_r3, 0.0F);
    HSD_JObjAnimAll(temp_r3);
    return temp_r30;
}

/// #fn_80229BF4

static StaticModelDesc mn_804A0518;
static struct {
    float x0;
    u8 pad[0x20];
} mn_803EAE8C[2] = { 0 };
static float mn_803EAE68[0x100] = { 0 };

HSD_GObj* mn_80229DC0(void)
{
    HSD_JObj* spC;
    HSD_JObj* sp8;
    HSD_GObj* temp_r31;
    HSD_JObj* temp_r3;
    u8* temp_r3_2;

    temp_r31 = GObj_Create(5, 6, 0x80);
    temp_r3 = HSD_JObjLoadJoint(mn_804A0518.joint);
    HSD_GObjObject_80390A70(temp_r31, HSD_GObj_804D7849, temp_r3);
    GObj_SetupGXLink(temp_r31, HSD_GObj_JObjCallback, 3, 0x80);
    HSD_GObjProc_8038FD54(temp_r31, fn_80229BF4, 0);
    HSD_JObjAddAnimAll(temp_r3, mn_804A0518.animjoint, mn_804A0518.matanim_joint, mn_804A0518.shapeanim_joint);
    lb_80011E24(temp_r3, &spC, 4, -1);
    lb_80011E24(temp_r3, &sp8, 0x29, -1);
    HSD_JObjReqAnimAll(spC, mn_803EAE68[0x4EC / 4]);
    HSD_JObjAnimAll(spC);
    if ((u8) mn_804A04F0.x0 == 0) {
        HSD_JObjReqAnimAll(sp8, mn_803EAE8C[mn_804A04F0.x0].x0);
    } else {
        HSD_JObjReqAnimAll(sp8, mn_803EAE8C[mn_804A04F0.x0 + 1].x0);
    }
    HSD_JObjAnimAll(sp8);
    temp_r3_2 = HSD_MemAlloc(4);
    if (temp_r3_2 == NULL) {
        OSReport("Can't get user_data.\n");
        __assert("mnmain.c", 0x427, "user_data");
    }
    GObj_InitUserData(temp_r31, 0, mn_8022EB04, temp_r3_2);
    temp_r3_2[0] = mn_804A04F0.x0;
    temp_r3_2[1] = mn_804A04F0.x0;
    temp_r3_2[3] = 0;
    return temp_r31;
}

/// #mn_80229F60

/// #mn_8022A440

/// #mn_8022A5D0

/// #mn_8022ADD8

/// #fn_8022AF10

/// #fn_8022AFEC

/// #mn_8022B3A0

/// #mn_8022BA1C

/// #fn_8022BCD4

/// #mn_8022BCF8

/// #mn_8022BD6C

/// #mn_8022BD8C

/// #fn_8022BDB4

/// #mn_8022BE34

/// #mn_8022BEDC

/// #mn_8022BFBC

/// #mn_8022C010

/// #mn_8022C068

/// #fn_8022C128

/// #mn_8022C304

/// #mn_8022C4F4

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
    if (mn_8022F218() != 0 && mn_804A04F0.x0 != 0) {
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

/// #mn_8022DDA8_OnEnter

/// #mn_8022E950

/// #mn_8022E978

/// #mn_8022EA08

/// #mn_8022EA78

/// #mn_8022EAE0

/// #mn_8022EB04

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
        HSD_JObjReqAnimAll(jobj, arg1->x);
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

/// #mn_8022EFD8

/// #mn_8022F0F0

/// #mn_8022F138

/// #mn_8022F1A8

/// #mn_8022F218

/// #mn_8022F268

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

/// #mn_8022F360

/// #mn_8022F3D8

/// #mn_8022F410

/// #mn_8022F470

/// #mn_8022F4CC

/// #fn_8022F538

/// #mn_8022FB88

/// #mn_8022FD18

/// #mn_8022FEC8

/// #mn_80230198

/// #mn_80230274

/// #mn_802307F8

/// #mn_802308F0

/// #fn_802309F0

/// #mn_80230D18

/// #mn_80230E38

int mn_80231634(struct mn_80231634_t* arg0)
{
    if (arg0 == NULL) {
        return 0;
    }
    return arg0->x10;
}

/// #mn_8023164C

/// #mn_80231714

/// #mn_802317E4

/// #mn_80231804

/// #mn_80231F80

/// #fn_8023201C

/// #mn_80232458

/// #mn_802324E4

/// #mn_80232660

/// #mn_802327A4

/// #mn_80232D4C

/// #fn_80232F44

/// #mn_80233218

/// #mn_802339FC
