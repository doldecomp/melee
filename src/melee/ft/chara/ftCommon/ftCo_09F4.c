#include <platform.h>
#include <placeholder.h>

#include "ftCommon/forward.h"

#include "ftCo_09F4.h"

#include "ft/ftdevice.h"
#include "gr/ground.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"

#include <math.h>
#include <baselib/cobj.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjproc.h>
#include <baselib/jobj.h>
#include <baselib/lobj.h>

/* 09F480 */ static void ftCo_8009F480(ftCo_GObj* gobj);
/* 09F54C */ static void ftCo_8009F54C(HSD_GObj* gobj, int code);

static HSD_LObj* lobj0;
static HSD_LObj* lobj1;

static float floats[] = { 0, 0.57, 0.57, 0.57, 0 };

static HSD_LightDesc node0 = {
    NULL,           NULL, 0x0005, 0x0000, { 0xFF, 0xFF, 0xFF, 0xFF },
    (void*) floats, 0,    0,
};

/// @todo #node1_t and #node2_t are fake types.
static struct node1_t {
    HSD_LightDesc* x0;
    UNK_T x4;
} node1 = { &node0, NULL };

static struct node2_t {
    /* +0 */ struct node1_t* x0;
    /* +4 */ UNK_T x4;
} node2 = { &node1, NULL };

void ftCo_8009F480(ftCo_GObj* gobj)
{
    HSD_LObjAnimAll(gobj->hsd_obj);
}

void ftCo_8009F4A4(void)
{
    HSD_GObj* gobj = GObj_Create(12, 3, 0);
    HSD_LObj* lobj = lb_80011AC4(Ground_801C49B4());
    lobj0 = lobj;
    lobj1 = lb_8000CDC0(lobj);
    Ground_801C2374(lobj);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784A, lobj);
    GObj_SetupGXLink(gobj, ftCo_8009F54C, 4U, 0U);
    HSD_LObjReqAnimAll(lobj, 0.0F);
    HSD_GObjProc_8038FD54(gobj, ftCo_8009F480, 1);
}

void ftCo_8009F54C(HSD_GObj* gobj, int code)
{
    HSD_LObj_803668EC(gobj->hsd_obj);
    HSD_LObjSetupInit(HSD_CObjGetCurrent());
}

void ftCo_8009F578(Fighter* fp)
{
    fp->x588 = lb_80011AC4((HSD_LightDesc**) &node2.x0);
}

void ftCo_8009F5AC(Fighter* fp)
{
    ftDeviceUnk2* data = ftCo_800C0658(fp);
    if (!data->x7C_b1) {
        return;
    }
    if (fp->x2221_b3) {
        {
            Vec3 position;
            float angle_yz = data->lobj_rot_yz * deg_to_rad;
            float angle_x = data->lobj_rot_x * deg_to_rad *
                            HSD_JObjGetRotationY(GET_JOBJ(fp->gobj)) / M_PI_2;
            position.y = -sinf(-angle_yz);
            position.z = cosf(-angle_yz);
            position.x = position.z * sinf(angle_x);
            position.z *= cosf(angle_x);
            HSD_LObjSetPosition(fp->x588, &position);
        }
        if (data->x7C_b2) {
            GXColor color = node0.color;
            color.a = data->lobj_color.a;
            HSD_LObjSetColor(fp->x588, color);
            HSD_LObjSetFlags(fp->x588, LOBJ_ALPHA);
        } else {
            HSD_LObjSetColor(fp->x588, data->lobj_color);
            HSD_LObjClearFlags(fp->x588, LOBJ_ALPHA);
        }
        fp->x2221_b3 = false;
    }
    if (data->x7C_b2) {
        HSD_LObj_803668EC(lobj0);
    } else {
        HSD_LObjSetCurrentAll(lobj1);
    }
    HSD_LObjAddCurrent(fp->x588);
    HSD_LObjSetupInit(HSD_CObjGetCurrent());
}

void ftCo_8009F75C(Fighter* fp, bool set_alpha)
{
    ftDeviceUnk2* data = ftCo_800C0658(fp);
    if (data->x7C_b1 && data->x7C_b2) {
        if (set_alpha) {
            HSD_LObjSetFlags(fp->x588, LOBJ_ALPHA);
        } else {
            HSD_LObjClearFlags(fp->x588, LOBJ_ALPHA);
        }
        if (set_alpha) {
            HSD_LObj_803668EC(lobj0);
        } else {
            HSD_LObjSetCurrentAll(lobj1);
        }
        HSD_LObjAddCurrent(fp->x588);
        HSD_LObjSetupInit(HSD_CObjGetCurrent());
    }
}

void ftCo_8009F7F8(Fighter* fp)
{
    if (ftCo_800C0658(fp)->x7C_b1) {
        HSD_LObj_803668EC(lobj0);
        HSD_LObjSetupInit(HSD_CObjGetCurrent());
    }
}
