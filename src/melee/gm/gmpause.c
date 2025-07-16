#include "placeholder.h"
#include "baselib/controller.h"
#include "baselib/gobj.h"
#include "baselib/gobjgxlink.h"
#include "baselib/gobjobject.h"
#include "baselib/gobjproc.h"
#include "baselib/jobj.h"
#include "gm/gm_1601.h"
#include "gm/types.h"
#include "lb/lb_00F9.h"
#include "lb/lbarchive.h"
#include <melee/gm/gmpause.h>

static struct PauseData lbl_80479B10;
static s8 lbl_803DA4B0[0x28] = "!(jobj->flags & JOBJ_USE_QUATERNION)";
static s8 lbl_804D4218[7] = "jobj.h";
static s8 lbl_804D4220[5] = "jobj";
static const f32 lbl_804DA984 = 0.017453292F; // deg2rad
extern HSD_Archive* lbl_804D6700;
extern HSD_GObj* lbl_804D6704;
static char* lbl_803DA4D8;
static s8 lbl_804D4228[8] = "GmPause";

void fn_801A0E34(HSD_GObj* arg0)
{
    f32 x;
    f32 y;
    HSD_PadStatus* pad;
    PAD_STACK(8);

    if (lbl_80479B10.slot != 99) {
        // inline ??
        pad = &HSD_PadMasterStatus[(u8)lbl_80479B10.slot];
        x = 10.0f * pad->nml_stickX;
        y = 10.0f * pad->nml_stickY;
        HSD_JObjSetRotationY(lbl_80479B10.analog_stick, 0.017453292F * x);
        HSD_JObjSetRotationX(lbl_80479B10.background, -(0.017453292F * y));
    }
}

void gm_801A0FEC(s32 slot, u8 flag)
{
    lbl_80479B10.slot = slot;
    HSD_JObjReqAnimAll(lbl_80479B10.background, (f32)(slot + 1));
    // flag is set by match rules
    if (flag != 0) {
        HSD_JObjClearFlagsAll(lbl_80479B10.background, JOBJ_HIDDEN);
        HSD_JObjSetFlagsAll(lbl_80479B10.lras, JOBJ_HIDDEN);
        HSD_JObjSetFlagsAll(lbl_80479B10.z, JOBJ_HIDDEN);
        HSD_JObjSetFlagsAll(lbl_80479B10.analog_stick, JOBJ_HIDDEN);
        HSD_JObjSetFlagsAll(lbl_80479B10.analog_stick_outline, JOBJ_HIDDEN);
        if (flag & 1) {
            HSD_JObjClearFlagsAll(lbl_80479B10.lras, JOBJ_HIDDEN);
        }
        if (flag & 2) {
            HSD_JObjClearFlagsAll(lbl_80479B10.z, JOBJ_HIDDEN);
        }
        if (flag & 4) {
            HSD_JObjClearFlagsAll(lbl_80479B10.analog_stick, JOBJ_HIDDEN);
            HSD_JObjClearFlagsAll(lbl_80479B10.analog_stick_outline, JOBJ_HIDDEN);
        }
    } else {
        HSD_JObjSetFlagsAll(lbl_80479B10.background, JOBJ_HIDDEN);
    }
    HSD_JObjAnimAll(lbl_80479B10.background);
}

void gm_801A10FC(int unused)
{
    lbl_80479B10.slot = 99;
    HSD_JObjSetFlagsAll(lbl_80479B10.background, JOBJ_HIDDEN);
}

void fn_801A1134(void)
{
    HSD_Joint**** joint;
    HSD_GObj* gobj;
    HSD_JObj* jobj;

    lbl_804D6700 = lbArchive_80016DBC("GmPause", &joint, "ScGamPause_scene_data", 0);
    gobj = GObj_Create(0xEU, 2U, 0U);
    lbl_804D6704 = gobj;
    jobj = HSD_JObjLoadJoint(***joint);
    lbl_80479B10.background = jobj;
    lb_80011E24(jobj, &lbl_80479B10.analog_stick, 1, -1);
    lb_80011E24(jobj, &lbl_80479B10.lras, 9, -1);
    lb_80011E24(jobj, &lbl_80479B10.z, 10, -1);
    lb_80011E24(jobj, &lbl_80479B10.analog_stick_outline, 11, -1);
    lbl_80479B10.analog_stick = HSD_JObjGetChild(lbl_80479B10.analog_stick);
    HSD_GObjObject_80390A70(gobj, (u8) HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0xBU, 0U);
    gm_8016895C(jobj, **joint, 0);
    HSD_JObjReqAnimAll(jobj, 1.0f);
    HSD_JObjAnimAll(jobj);
    HSD_JObjSetFlagsAll(jobj, 0x10U);
    HSD_GObjProc_8038FD54(gobj, fn_801A0E34, 0U);
    lbl_80479B10.slot = 99;
}
