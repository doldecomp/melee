#include "gmpause.h"

#include <melee/gm/gm_1601.h>
#include <melee/gm/types.h>
#include <melee/lb/lb_00F9.h>
#include <melee/lb/lbarchive.h>
#include <melee/sc/types.h>
#include <sysdolphin/baselib/controller.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjobject.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/jobj.h>
#include <math.h>

struct PauseData {
/* +0 */ HSD_JObj* background;
/* +4 */ HSD_JObj* analog_stick;
/* +8 */ HSD_JObj* lras;
/* +C */ HSD_JObj* z;
/* +10 */ HSD_JObj* analog_stick_outline;
/* +14 */ s32 slot;
};

static struct PauseData lbl_80479B10;
static HSD_Archive* lbl_804D6700;
static HSD_GObj* lbl_804D6704;

void fn_801A0E34(HSD_GObj* arg0)
{
    f32 x;
    f32 y;
    HSD_PadStatus* pad;
    PAD_STACK(8);

    if (lbl_80479B10.slot != 99) {
        x = 10.0F * HSD_PadMasterStatus[(u8) lbl_80479B10.slot].nml_stickX;
        y = 10.0F * HSD_PadMasterStatus[(u8) lbl_80479B10.slot].nml_stickY;
        HSD_JObjSetRotationY(lbl_80479B10.analog_stick, +(deg_to_rad * x));
        HSD_JObjSetRotationX(lbl_80479B10.analog_stick, -(deg_to_rad * y));
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
    SceneDesc* scene;
    HSD_GObj* gobj;
    HSD_JObj* jobj;

    lbl_804D6700 = lbArchive_80016DBC("GmPause", &scene, "ScGamPause_scene_data", 0);
    gobj = GObj_Create(0xEU, 2U, 0U);
    lbl_804D6704 = gobj;
    jobj = HSD_JObjLoadJoint(scene->models[0]->joint);
    lbl_80479B10.background = jobj;
    lb_80011E24(jobj, &lbl_80479B10.analog_stick, 1, -1);
    lb_80011E24(jobj, &lbl_80479B10.lras, 9, -1);
    lb_80011E24(jobj, &lbl_80479B10.z, 10, -1);
    lb_80011E24(jobj, &lbl_80479B10.analog_stick_outline, 11, -1);
    lbl_80479B10.analog_stick = HSD_JObjGetChild(lbl_80479B10.analog_stick);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0xBU, 0U);
    gm_8016895C(jobj, scene->models[0], 0);
    HSD_JObjReqAnimAll(jobj, 1.0f);
    HSD_JObjAnimAll(jobj);
    HSD_JObjSetFlagsAll(jobj, 0x10U);
    HSD_GObjProc_8038FD54(gobj, fn_801A0E34, 0U);
    lbl_80479B10.slot = 99;
}
