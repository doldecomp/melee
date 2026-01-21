#include "grkinokoroute.h"

#include "ground.h"

#include <platform.h>

#include "cm/camera.h"
#include "ft/ftdevice.h"
#include "ft/ftlib.h"
#include "gr/grlib.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "lb/lb_00B0.h"

#include <baselib/psstructs.h>
#include <baselib/random.h>

static struct {
    int x0;
    int x4;
}* grNKr_804D6A50;

void grKinokoRoute_8020741C(bool arg) {}

void grKinokoRoute_80207420(void)
{
    grNKr_804D6A50 = Ground_801C49F8();
    stage_info.unk8C.b4 = 0;
    stage_info.unk8C.b5 = 1;
    grKinokoRoute_8020754C(2);
    grKinokoRoute_8020754C(0);
    grKinokoRoute_8020754C(1);
    grKinokoRoute_8020754C(3);
}

void grKinokoRoute_80207490(void)
{
    Vec3 pos;
    HSD_GObj* gobj = Ground_801C57A4();
    if (gobj != NULL) {
        ftLib_80086644(gobj, &pos);
        Ground_801C38BC(pos.x, 20.0f + pos.y);
        Camera_8002F3AC();
    }
}

void grKinokoRoute_802074D8(void)
{
    int val;
    grZakoGenerator_801CAE04(&grNKr_804D6A50->x4);
    val = grNKr_804D6A50->x0;
    if (val != 0) {
        val = HSD_Randi(grNKr_804D6A50->x0);
    } else {
        val = 0;
    }
    if (val == 0) {
        grZakoGenerator_801CAEB0(Ground_801C5840(), Ground_801C5940());
    }
    grZakoGenerator_801CADE0();
}

bool grKinokoRoute_80207544(void)
{
    return false;
}

/// #grKinokoRoute_8020754C

/// #grKinokoRoute_80207634

bool grKinokoRoute_802078E8(Ground_GObj* arg)
{
    return false;
}

/// #grKinokoRoute_802078F0

void grKinokoRoute_80207A94(Ground_GObj* arg) {}

void grKinokoRoute_80207A98(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138((HSD_GObj*) gobj, gp->map_id, 0);
    Ground_801C39C0();
    Ground_801C3BB4();
}

bool grKinokoRoute_80207ACC(Ground_GObj* arg)
{
    return false;
}

void grKinokoRoute_80207AD4(Ground_GObj* arg) {}

void grKinokoRoute_80207AD8(Ground_GObj* arg) {}

void grKinokoRoute_80207ADC(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->x11_flags.b012 = 2;
}

bool grKinokoRoute_80207B20(Ground_GObj* arg)
{
    return false;
}

void grKinokoRoute_80207B28(Ground_GObj* arg) {}

void grKinokoRoute_80207B2C(Ground_GObj* arg) {}

void grKinokoRoute_80207B30(HSD_GObj* gobj)
{
    ftCo_800C07F8(gobj, 6, grKinokoRoute_80208660);
}

/// #grKinokoRoute_80207B5C

bool grKinokoRoute_80207C80(Ground_GObj* arg)
{
    return false;
}

/// #grKinokoRoute_80207C88

void grKinokoRoute_80208368(Ground_GObj* arg) {}

/// #grKinokoRoute_8020836C

bool grKinokoRoute_80208480(bool arg)
{
    if (arg == 1) {
        Ground_801C5740(arg);
        return 1;
    }
    return 0;
}

/// #grKinokoRoute_802084B4

/// #grKinokoRoute_80208564

/// #grKinokoRoute_80208660

void grKinokoRoute_802086EC(Vec3* arg0, f32 arg8)
{
    HSD_Generator* gen = grLib_801C96F8(0x7530, 0x1E, arg0);
    if (gen != NULL) {
        HSD_psAppSRT* srt = gen->appsrt;
        srt->scale.x *= arg8;
        srt->scale.y *= arg8;
        srt->scale.z *= arg8;
    }
}

DynamicsDesc* grKinokoRoute_80208754(enum_t arg)
{
    return false;
}

bool grKinokoRoute_8020875C(Vec3* a, int b, HSD_JObj* jobj)
{
    Vec3 vec;
    lb_8000B1CC(jobj, NULL, &vec);
    if (a->y > vec.y) {
        return true;
    } else {
        return false;
    }
}
