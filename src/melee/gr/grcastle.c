#include "gr/grcastle.h"

#include "placeholder.h"

#include <platform.h>

#include "baselib/psstructs.h"
#include "ft/ftlib.h"

#include "gr/forward.h"

#include "gr/grlib.h"
#include "gr/grmaterial.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "it/it_26B1.h"
#include "lb/lb_00B0.h"

#include <dolphin/mtx.h>
#include <baselib/jobj.h>

unkCastleCallback grCs_803B7F28[] = {
    grCastle_801D0550, grCastle_801D059C, grCastle_801D05E8,
    grCastle_801D0634, grCastle_801D0680,
};

unkCastleCallback2 grCs_803B7F3C[] = {
    grCastle_801D06CC, grCastle_801D0744, grCastle_801D07BC,
    grCastle_801D0834, grCastle_801D08AC,
};

void grCastle_801CD338(bool arg0)
{
    HSD_GObj* gobj;
    HSD_JObj* jobj;

    gobj = Ground_801C2BA4(6);
    if (gobj != NULL) {
        jobj = Ground_801C3FA4(gobj, 4);
        if (jobj != NULL) {
            HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        }
    }
}

/// #grCastle_801CD37C

void grCastle_801CD4A0(void) {}

void grCastle_801CD4A4(void)
{
    grZakoGenerator_801CAE04(0);
}

bool grCastle_801CD4C8(void)
{
    return false;
}

/// #grCastle_801CD4D0

void grCastle_801CD5BC(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->x11_flags.b012 = 2;
}

bool grCastle_801CD600(Ground_GObj* gobj)
{
    return false;
}

void grCastle_801CD608(Ground_GObj* gobj) {}

void grCastle_801CD60C(Ground_GObj* gobj) {}

/// #fn_801CD610

/// #grCastle_801CD658

bool grCastle_801CD8A0(Ground_GObj* gobj)
{
    return false;
}

/// #grCastle_801CD8A8

/// #grCastle_801CD960

/// #fn_801CD9B4

/// #grCastle_801CDA0C

bool grCastle_801CDC3C(Ground_GObj* gobj)
{
    return false;
}

/// #grCastle_801CDC44

void grCastle_801CDF50(Ground_GObj* gobj) {}

/// #grCastle_801CDF54

/// #grCastle_801CDFD8

/// #grCastle_801CE054

/// #grCastle_801CE19C

/// #grCastle_801CE260

void fn_801CE3A0(void) {}

bool grCastle_801CE3A4(Ground_GObj* gobj)
{
    return false;
}

/// #grCastle_801CE3AC

/// #grCastle_801CE578

void grCastle_801CE7E4(Ground_GObj* gobj) {}

/// #grCastle_801CE7E8

bool grCastle_801CE858(Ground_GObj* gobj)
{
    return false;
}

/// #grCastle_801CE860

void grCastle_801CE8E4(Ground_GObj* gobj) {}

/// #grCastle_801CE8E8

void fn_801CE9DC(void) {}

bool grCastle_801CE9E0(Ground_GObj* gobj)
{
    return false;
}

/// #grCastle_801CE9E8

void grCastle_801CEAC8(Ground_GObj* gobj) {}

/// #grCastle_801CEACC

bool grCastle_801CEEFC(Ground_GObj* gobj)
{
    return false;
}

/// #grCastle_801CEF04

void grCastle_801CF0F0(Ground_GObj* gobj) {}

/// #grCastle_801CF0F4

bool grCastle_801CF300(Ground_GObj* gobj)
{
    return false;
}

/// #grCastle_801CF308

void grCastle_801CF74C(Ground_GObj* gobj) {}

/// #fn_801CF750

/// #grCastle_801CF7B0

/// #grCastle_801CF868

/// #fn_801CFAFC

/// #fn_801CFB68

/// #grCastle_801CFBD4

/// #grCastle_801D0298

void grCastle_801D0298(void)
{
    grCastle_801CFBD4();
}

/// #grCastle_801D02B8

/// #fn_801D0520

static inline void grCastle_801D0550_sub(unkCastle* arg0, s32 i)
{
    arg0->x134[i] = 1;
    grMaterial_801C8CDC(arg0->x10C[i]);
    arg0->x10C[i] = NULL;
    Ground_801C53EC(0x53020U);
}

void grCastle_801D0550(void* arg0, unkCastle* arg1)
{
    PAD_STACK(16);
    grCastle_801D0550_sub(arg1, 0);
}

void grCastle_801D059C(void* arg0, unkCastle* arg1)
{
    PAD_STACK(16);
    grCastle_801D0550_sub(arg1, 1);
}

void grCastle_801D05E8(void* arg0, unkCastle* arg1)
{
    PAD_STACK(16);
    grCastle_801D0550_sub(arg1, 2);
}

void grCastle_801D0634(void* arg0, unkCastle* arg1)
{
    PAD_STACK(16);
    grCastle_801D0550_sub(arg1, 3);
}

void grCastle_801D0680(void* arg0, unkCastle* arg1)
{
    PAD_STACK(16);
    grCastle_801D0550_sub(arg1, 4);
}

static void grCastle_801D06CC_sub(unkCastle* arg0, Ground_GObj* gobj, s32 i)
{
    if (ftLib_80086960(gobj) || itGetKind(gobj) != Pokemon_Random) {
        arg0->x134[i] = 1;
        grMaterial_801C8CDC(arg0->x10C[i]);
        arg0->x10C[i] = NULL;
        Ground_801C53EC(0x53020U);
    }
}

void grCastle_801D06CC(void* arg0, unkCastle* arg1, Ground_GObj* gobj)
{
    grCastle_801D06CC_sub(arg1, gobj, 0);
}

void grCastle_801D0744(void* arg0, unkCastle* arg1, Ground_GObj* gobj)
{
    grCastle_801D06CC_sub(arg1, gobj, 1);
}

void grCastle_801D07BC(void* arg0, unkCastle* arg1, Ground_GObj* gobj)
{
    grCastle_801D06CC_sub(arg1, gobj, 2);
}

void grCastle_801D0834(void* arg0, unkCastle* arg1, Ground_GObj* gobj)
{
    grCastle_801D06CC_sub(arg1, gobj, 3);
}

void grCastle_801D08AC(void* arg0, unkCastle* arg1, Ground_GObj* gobj)
{
    grCastle_801D06CC_sub(arg1, gobj, 4);
}

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

void grCastle_801D0A9C(Vec3* arg0, f32 arg8)
{
    HSD_Generator* gen = grLib_801C96F8(0x7530, 0x1E, arg0);
    if (gen != NULL) {
        HSD_psAppSRT* srt = gen->appsrt;
        srt->scale.x *= arg8;
        srt->scale.y *= arg8;
        srt->scale.z *= arg8;
    }
}

/// #grCastle_801D0BBC

/// #grCastle_801D0D24

/// #grCastle_801D0D84

f32 grCastle_801D0FF0(void)
{
    return 50.0f * Ground_801C0498();
}
