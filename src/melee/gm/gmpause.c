#include "baselib/controller.h"
#include "baselib/jobj.h"
#include "gm/types.h"
#include <melee/gm/gmpause.h>

static struct PauseData lbl_80479B10;
static s8 lbl_803DA4B0[0x28] = "!(jobj->flags & JOBJ_USE_QUATERNION)";
static s8 lbl_804D4218[7] = "jobj.h";
static s8 lbl_804D4220[5] = "jobj";
// static const f32 lbl_804DA984 = 0.017453292F; // deg2rad

void fn_801A0E34(HSD_GObj* arg0)
{
    HSD_PadStatus* pad;
    // struct PauseData* pause_data;
    f32 x;
    f32 y;

    // pause_data = &lbl_80479B10;
    if ((s32)lbl_80479B10.slot != 99) {
        pad = &HSD_PadMasterStatus[(u8)lbl_80479B10.slot];
        x = 10.0f * pad->nml_stickX;
        y = 10.0f * pad->nml_stickY;
        HSD_JObjSetRotationY(lbl_80479B10.analog_stick, 0.017453292F * y);
        HSD_JObjSetRotationX(lbl_80479B10.background, -(0.017453292F * x));
    }
}

/// #gm_801A0FEC

void gm_801A10FC(void)
{
    lbl_80479B10.slot = 99;
    HSD_JObjSetFlagsAll(lbl_80479B10.background, JOBJ_HIDDEN);
}

/// #fn_801A1134
