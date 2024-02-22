#include <platform.h>
#include "ftCommon/forward.h"

#include <math.h>
#include <placeholder.h>
#include <baselib/gobj.h>
#include <baselib/lobj.h>

/* 09F480 */ static void ftCo_8009F480(ftCo_GObj* gobj);

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

/// #ftCo_8009F4A4

/// #ftCo_8009F54C

/// #ftCo_8009F578

/// #ftCo_8009F5AC

/// #ftCo_8009F75C

/// #ftCo_8009F7F8
