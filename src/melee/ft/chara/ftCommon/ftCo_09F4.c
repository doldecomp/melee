#include <platform.h>
#include "ftCommon/forward.h"

#include "gr/ground.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"

#include <math.h>
#include <placeholder.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjproc.h>
#include <baselib/lobj.h>

/* 09F480 */ static void ftCo_8009F480(ftCo_GObj* gobj);
/* 09F54C */ static void ftCo_8009F54C(HSD_GObj* gobj, int code);

#pragma force_active on

static float const ftCo_804D87B0 = 0;
static float const ftCo_804D87B4 = deg_to_rad;
static double const ftCo_804D87B8 = M_PI_2;
extern UNK_T ftCo_804D6568;
extern UNK_T ftCo_804D656C;
extern UNK_T ftCo_804D3B50;
extern char* ftCo_804D3B58;
extern char* ftCo_804D3B60;

static char ftDynamics_assert_msg_0[] =
    "fp->dynamics_num < Ft_Dynamics_NumMax";
static float ftDynamics_803C5780[] = { 0, 0.57, 0.57, 0.57, 0 };

struct {
    int zero1;
    int zero2;
    u32 flags;
    int neg1;
    float* floats;
    int zero3;
    int zero4;
} ftDynamics_803C5794 = {
    0, 0, 0x00050000, -1, ftDynamics_803C5780, 0, 0,
};

void ftCo_8009F480(ftCo_GObj* gobj)
{
    HSD_LObjAnimAll(gobj->hsd_obj);
}

void ftCo_8009F4A4(void)
{
    HSD_GObj* gobj = GObj_Create(12, 3, 0);
    HSD_LObj* lobj = lb_80011AC4(Ground_801C49B4());
    ftCo_804D6568 = lobj;
    ftCo_804D656C = lb_8000CDC0(lobj);
    Ground_801C2374(lobj);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784A, lobj);
    GObj_SetupGXLink(gobj, ftCo_8009F54C, 4U, 0U);
    HSD_LObjReqAnimAll(lobj, ftCo_804D87B0);
    HSD_GObjProc_8038FD54(gobj, ftCo_8009F480, 1);
}

/// #ftCo_8009F54C

/// #ftCo_8009F578

/// #ftCo_8009F5AC

/// #ftCo_8009F75C

/// #ftCo_8009F7F8
