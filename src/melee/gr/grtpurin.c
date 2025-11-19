#include "grtpurin.h"

#include "gr/grdisplay.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "gr/types.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "lb/types.h"
#include "mp/mplib.h"

#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>
#include <baselib/jobj.h>

StageCallbacks grTPr_803E9338[] = {
    { grTPurin_802232F4, grTPurin_80223320, grTPurin_80223328,
      grTPurin_8022332C, 0 },
    { grTPurin_8022347C, grTPurin_802234CC, grTPurin_802234D4,
      grTPurin_802234F4, 0 },
    { grTPurin_80223330, grTPurin_80223380, grTPurin_80223388,
      grTPurin_80223478, 0xC0000000 },
    { NULL, NULL, NULL, NULL, 0 }
};

StageData grTPr_803E9394 = {
    58,
    grTPr_803E9338,
    "/GrTPr.dat",
    grTPurin_80223164,
    grTPurin_80223160,
    grTpurin_UnkStage0_OnLoad,
    grTpurin_UnkStage0_OnStart,
    grTPurin_80223204,
    grTPurin_802234F8,
    grTPurin_80223578,
    (1 << 0),
};

typedef struct grTPrSpecialParams {
    DynamicsDesc* x0;
} grTPrSpecialParams;

grTPrSpecialParams* grTPr_804D6B10;

void grTPurin_80223160(bool unused)
{
    return;
}

void grTPurin_80223164(void)
{
    grTPr_804D6B10 = Ground_801C49F8();
    stage_info.unk8C.b4 = false;
    stage_info.unk8C.b5 = true;

    grTPurin_8022320C(0);
    grTPurin_8022320C(1);
    grTPurin_8022320C(2);
    Ground_801C39C0();
    Ground_801C3BB4();
    Ground_801C4210();
    Ground_801C42AC();
}

void grTpurin_UnkStage0_OnLoad(void)
{
    return;
}

void grTpurin_UnkStage0_OnStart(void)
{
    grZakoGenerator_801CAE04(0);
}

bool grTPurin_80223204(void)
{
    return false;
}

HSD_GObj* grTPurin_8022320C(int id)
{
    HSD_GObj* gobj;
    StageCallbacks* cb = &grTPr_803E9338[id];
    gobj = Ground_801C14D0(id);

    if (gobj != NULL) {
        Ground* gp = (Ground*) HSD_GObjGetUserData(gobj);
        gp->x8_callback = NULL;
        gp->xC_callback = NULL;
        GObj_SetupGXLink(gobj, grDisplay_801C5DB0, 3, 0);

        if (cb->callback3 != NULL) {
            gp->x1C_callback = cb->callback3;
        }

        if (cb->callback0 != NULL) {
            cb->callback0(gobj);
        }

        if (cb->callback2 != NULL) {
            HSD_GObjProc_8038FD54(gobj, cb->callback2, 4);
        }
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grtpurin.c", 203, id);
    }

    return gobj;
}

void grTPurin_802232F4(Ground_GObj* gobj)
{
    Ground* gp = (Ground*) HSD_GObjGetUserData(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grTPurin_80223320(Ground_GObj* gobj)
{
    return false;
}

void grTPurin_80223328(Ground_GObj* gobj)
{
    return;
}

void grTPurin_8022332C(Ground_GObj* gobj)
{
    return;
}

void grTPurin_80223330(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* joint = (HSD_JObj*) gobj->hsd_obj;
    PAD_STACK(8);

    Ground_801C2ED0(joint, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, false);
}

bool grTPurin_80223380(Ground_GObj* gobj)
{
    return false;
}

void grTPurin_80223388(Ground_GObj* gobj)
{
    s16* pos;
    HSD_JObj* jobj;
    int res;
    Vec3 vec;
    s16 values[8] = { 0x0037, 0x0039, 0x003B, 0x003D,
                      0x003F, 0x0041, 0x0043, 0xFFFF };
    s32 value;

    for (pos = &values[0]; (value = *pos) != -1; ++pos) {
        res = Ground_801C32D4(2, value);
        if (res != -1) {
            jobj = Ground_801C3FA4(gobj, value);
            if ((jobj != NULL) &&
                (lb_8000B1CC(jobj, NULL, &vec), (vec.x < 130.0f)))
            {
                mpJointListAdd(res);
            } else {
                mpLib_80057BC0(res);
            }
        }
    }
    lb_800115F4();
    Ground_801C2FE0(gobj);
}

void grTPurin_80223478(Ground_GObj* gobj)
{
    return;
}

void grTPurin_8022347C(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* joint = (HSD_JObj*) gobj->hsd_obj;
    PAD_STACK(8);

    Ground_801C2ED0(joint, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, false);
}

bool grTPurin_802234CC(Ground_GObj* gobj)
{
    return false;
}

void grTPurin_802234D4(Ground_GObj* gobj)
{
    Ground_801C2FE0(gobj);
}

void grTPurin_802234F4(Ground_GObj* gobj)
{
    return;
}

DynamicsDesc* grTPurin_802234F8(enum_t arg0)
{
    enum_t i;

    if (arg0 != -1) {
        i = mpJointFromLine(arg0);
        if (i != -1) {
            mpLineGetKind(arg0);
            if (i == (0 << 0)) {
                return grTPr_804D6B10->x0;
            }
            if (i == (1 << 0)) {
                return grTPr_804D6B10->x0;
            }
        }
    }
    return 0;
}

bool grTPurin_80223578(Vec3* vec, int arg1, HSD_JObj* jobj)
{
    return true;
}
