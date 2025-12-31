#include "grzebes.h"

#include <platform.h>

#include "gr/inlines.h"

/* 1D84A0 */ static void grZebes_801D84A0(bool arg);
/* 1D8528 */ static void grZebes_801D8528(void);
/* 1D8550 */ static bool grZebes_801D8550(void);
/* 1D8558 */ static void grZebes_801D8558(int);
/* 1D8814 */ static bool grZebes_801D8814(Ground_GObj* arg);
/* 1D90FC */ static void grZebes_801D90FC(Ground_GObj* arg);
/* 1D9254 */ static bool grZebes_801D9254(Ground_GObj* arg);
/* 1D93D8 */ static void grZebes_801D93D8(Ground_GObj* arg);
/* 1D9408 */ static bool grZebes_801D9408(Ground_GObj* arg);
/* 1D94EC */ static void grZebes_801D94EC(Ground_GObj* arg);
/* 1D94F0 */ static void fn_801D94F0(Ground_GObj* gobj);
/* 1D95B0 */ static bool grZebes_801D95B0(Ground_GObj* arg);
/* 1D9754 */ static void grZebes_801D9754(Ground_GObj* arg);
/* 1D99D8 */ static bool grZebes_801D99D8(Ground_GObj* arg);
/* 1D9F2C */ static void grZebes_801D9F2C(Ground_GObj* arg);
/* 1D9F7C */ static bool grZebes_801D9F7C(Ground_GObj* arg);
/* 1DA0C0 */ static void grZebes_801DA0C0(Ground_GObj* arg);
/* 1DA3E8 */ static void grZebes_801DA3E8(void);
/* 1DA9D8 */ static void fn_801DA9D8(UNK_T arg0, Ground* gp, float* y,
                                     float z);
/* 1DA9F0 */ static void fn_801DA9F0(UNK_T arg0, Ground* gp, float y,
                                     float* x);
/* 1DCCB8 */ static DynamicsDesc* grZebes_801DCCB8(enum_t arg);
/* 1DCCC0 */ static bool grZebes_801DCCC0(Vec3* arg, int arg0, HSD_JObj* jobj);
/* 4D6990 */ static HSD_GObj* grZe_804D6990;
/* 4D6998 */ static s16 grZe_804D6998;

extern f32 grZe_804DB0B0;

void grZebes_801D84A0(bool arg) {}

void grZebes_801D84A4(void)
{
    grZe_804D6990 = Ground_801C49F8();
    stage_info.unk8C.b4 = 0;
    stage_info.unk8C.b5 = 1;
    grZebes_801D8558(0);
    grZebes_801D8558(1);
    grZebes_801D8558(6);
    grZebes_801D8558(4);
    grZebes_801D8558(8);
    Ground_801C39C0();
    Ground_801C3BB4();
    grZebes_801DA3E8();
}
void grZebes_801D8528(void) {}

/// #grZebes_801D852C

bool grZebes_801D8550(void)
{
    return false;
}

/// #grZebes_801D8558

/// #grZebes_801D8644

bool grZebes_801D8814(Ground_GObj* arg)
{
    return false;
}

/// #grZebes_801D881C

void grZebes_801D90FC(Ground_GObj* arg) {}

/// #grZebes_801D9100

bool grZebes_801D9254(Ground_GObj* arg)
{
    return false;
}

/// #grZebes_801D925C

void grZebes_801D93D8(Ground_GObj* arg) {}

/// #grZebes_801D93DC

bool grZebes_801D9408(Ground_GObj* arg)
{
    return false;
}

/// #grZebes_801D9410

void grZebes_801D94EC(Ground_GObj* arg) {}

void fn_801D94F0(Ground_GObj* gobj)
{
    GET_GROUND(gobj)->gv.zebes.x0_b0 = false;
}

/// #grZebes_801D9508

bool grZebes_801D95B0(Ground_GObj* arg)
{
    return false;
}

/// #grZebes_801D95B8

void grZebes_801D9754(Ground_GObj* arg) {}

/// #fn_801D9758

/// #grZebes_801D9798

bool grZebes_801D99D8(Ground_GObj* arg)
{
    return false;
}

/// #grZebes_801D99E0

void grZebes_801D9F2C(Ground_GObj* arg) {}

void grZebes_801D9F30(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    grAnime_801C8138(gobj, gp->map_id, 0);
    M2C_FIELD(gp, s16*, 0xC4) = 0;
    gp->x11_flags.b012 = 1;
}

bool grZebes_801D9F7C(Ground_GObj* arg)
{
    return false;
}

/// #grZebes_801D9F84

void grZebes_801DA0C0(Ground_GObj* arg) {}

/// #grZebes_801DA0C4

/// #grZebes_801DA254

void grZebes_801DA3E8(void)
{
    grZe_804D6998 = 0;
}

/// #grZebes_801DA3F4

/// #grZebes_801DA4FC

/// #grZebes_801DA528

void fn_801DA9D8(UNK_T arg0, Ground* gp, float* y, float z)
{
    gp->gv.zebes.xC.z += z;
    gp->gv.zebes.xC.y = *y;
}

void fn_801DA9F0(UNK_T arg0, Ground* gp, float y, float* x)
{
    gp->gv.zebes.xC.y += y;
    gp->gv.zebes.xC.x = *x;
}

/// #grZebes_801DAA08

/// #fn_801DAC90

/// #grZebes_801DAE70

/// #grZebes_801DB088

/// #grZebes_801DB3CC

/// #grZebes_801DBB60

/// #grZebes_801DC260

/// #grZebes_801DC408

/// #grZebes_801DC744

/// #grZebes_801DC9DC

/// #fn_801DCB64

/// #fn_801DCBB0

/// #fn_801DCBFC

DynamicsDesc* grZebes_801DCCB8(enum_t arg)
{
    return false;
}

bool grZebes_801DCCC0(Vec3* arg, int arg0, HSD_JObj* jobj)
{
    return true;
}

f32 grZebes_801DCCC8(void)
{
    f32 slope, intercept;
    Ground_801C4368(&slope, &intercept);
    return grZe_804DB0B0 + slope;
}
