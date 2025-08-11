#include <platform.h>

#include "gr/ground.h"
#include "lb/lb_00B0.h"

#include <dolphin/mtx.h>
#include <baselib/jobj.h>

/* 1CD4A0 */ static void grCastle_801CD4A0(void);
/* 1CD4C8 */ static bool grCastle_801CD4C8(void);
/* 1CD600 */ static bool grCastle_801CD600(Ground_GObj* arg);
/* 1CD608 */ static void grCastle_801CD608(Ground_GObj* arg);
/* 1CD60C */ static void grCastle_801CD60C(Ground_GObj* arg);
/* 1CD8A0 */ static bool grCastle_801CD8A0(Ground_GObj* arg);
/* 1CDC3C */ static bool grCastle_801CDC3C(Ground_GObj* arg);
/* 1CDF50 */ static void grCastle_801CDF50(Ground_GObj* arg);
/* 1CE3A0 */ static void fn_801CE3A0(void);
/* 1CE3A4 */ static bool grCastle_801CE3A4(Ground_GObj* arg);
/* 1CE7E4 */ static void grCastle_801CE7E4(Ground_GObj* arg);
/* 1CE858 */ static bool grCastle_801CE858(Ground_GObj* arg);
/* 1CE8E4 */ void grCastle_801CE8E4(Ground_GObj* arg);
/* 1CE9DC */ static void fn_801CE9DC(void);
/* 1CE9E0 */ static bool grCastle_801CE9E0(Ground_GObj* arg);
/* 1CEAC8 */ static void grCastle_801CEAC8(Ground_GObj* arg);
/* 1CEEFC */ static bool grCastle_801CEEFC(Ground_GObj* arg);
/* 1CF0F0 */ static void grCastle_801CF0F0(Ground_GObj* arg);
/* 1CF300 */ static bool grCastle_801CF300(Ground_GObj* arg);
/* 1CF74C */ static void grCastle_801CF74C(Ground_GObj* arg);
/* 1D0B04 */ static DynamicsDesc* grCastle_801D0B04(enum_t arg);
/* 1D0B0C */ static bool grCastle_801D0B0C(Vec3* v, int arg1, HSD_JObj* jobj);

/// #grCastle_801CD338

/// #grCastle_801CD37C

void grCastle_801CD4A0(void) {}

/// #grCastle_801CD4A4

bool grCastle_801CD4C8(void)
{
    return false;
}

/// #grCastle_801CD4D0

/// #grCastle_801CD5BC

bool grCastle_801CD600(Ground_GObj* arg)
{
    return false;
}

void grCastle_801CD608(Ground_GObj* arg) {}

void grCastle_801CD60C(Ground_GObj* arg) {}

/// #fn_801CD610

/// #grCastle_801CD658

bool grCastle_801CD8A0(Ground_GObj* arg)
{
    return false;
}

/// #grCastle_801CD8A8

/// #grCastle_801CD960

/// #fn_801CD9B4

/// #grCastle_801CDA0C

bool grCastle_801CDC3C(Ground_GObj* arg)
{
    return false;
}

/// #grCastle_801CDC44

void grCastle_801CDF50(Ground_GObj* arg) {}

/// #grCastle_801CDF54

/// #grCastle_801CDFD8

/// #grCastle_801CE054

/// #grCastle_801CE19C

/// #grCastle_801CE260

void fn_801CE3A0(void) {}

bool grCastle_801CE3A4(Ground_GObj* arg)
{
    return false;
}

/// #grCastle_801CE3AC

/// #grCastle_801CE578

void grCastle_801CE7E4(Ground_GObj* arg) {}

/// #grCastle_801CE7E8

bool grCastle_801CE858(Ground_GObj* arg)
{
    return false;
}

/// #grCastle_801CE860

void grCastle_801CE8E4(Ground_GObj* arg) {}

/// #grCastle_801CE8E8

void fn_801CE9DC(void) {}

bool grCastle_801CE9E0(Ground_GObj* arg)
{
    return false;
}

/// #grCastle_801CE9E8

void grCastle_801CEAC8(Ground_GObj* arg) {}

/// #grCastle_801CEACC

bool grCastle_801CEEFC(Ground_GObj* arg)
{
    return false;
}

/// #grCastle_801CEF04

void grCastle_801CF0F0(Ground_GObj* arg) {}

/// #grCastle_801CF0F4

bool grCastle_801CF300(Ground_GObj* arg)
{
    return false;
}

/// #grCastle_801CF308

void grCastle_801CF74C(Ground_GObj* arg) {}

/// #fn_801CF750

/// #grCastle_801CF7B0

/// #grCastle_801CF868

/// #fn_801CFAFC

/// #fn_801CFB68

/// #grCastle_801CFBD4

/// #grCastle_801D0298

/// #grCastle_801D02B8

/// #fn_801D0520

/// #grCastle_801D0550

/// #grCastle_801D059C

/// #grCastle_801D05E8

/// #grCastle_801D0634

/// #grCastle_801D0680

/// #grCastle_801D06CC

/// #grCastle_801D0744

/// #grCastle_801D07BC

/// #grCastle_801D0834

/// #grCastle_801D08AC

/// #fn_801D0924

/// #fn_801D09B8

/// #grCastle_801D0A9C

DynamicsDesc* grCastle_801D0B04(enum_t arg)
{
    return false;
}

bool grCastle_801D0B0C(Vec3* v, int arg1, HSD_JObj* jobj)
{
    Vec3 pos;
    float temp_f30;
    float temp_f31;
    float temp_f31_2;

    temp_f31 = 192.0f;
    temp_f30 = 137.0f;
    temp_f31_2 = temp_f31 * Ground_801C0498();
    if ((v->x > temp_f31_2) && (v->y < (temp_f30 * Ground_801C0498()))) {
        return 0;
    }
    lb_8000B1CC(jobj, NULL, &pos);
    if ((1 + v->y) > pos.y) {
        return 1;
    }
    return 0;
}

/// #grCastle_801D0BBC

/// #grCastle_801D0D24

/// #grCastle_801D0D84

/// #grCastle_801D0FF0
