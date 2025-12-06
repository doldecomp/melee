#include "grgreatbay.h"

#include "placeholder.h"

#include <platform.h>

#include "baselib/psstructs.h"
#include "ft/ftdevice.h"
#include "gr/granime.h"
#include "gr/grdisplay.h"
#include "gr/grlib.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "lb/types.h"
#include "mp/mplib.h"

#include <string.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>

S16Vec3 grGb_803E3E60[] = { { 0, 2, 49 }, { 1, 1, 2 },  { 2, 1, 3 },
                            { 4, 1, 34 }, { 3, 1, 38 }, { 5, 10, 0 } };

StageCallbacks grGb_803E3E84[11] = {
    { grGreatBay_801F4404, grGreatBay_801F4430, grGreatBay_801F4438,
      grGreatBay_801F443C, 0 },
    { grGreatBay_801F4694, grGreatBay_801F4994, grGreatBay_801F499C,
      grGreatBay_801F545C, 0 },
    { grGreatBay_801F454C, grGreatBay_801F4650, grGreatBay_801F4658,
      grGreatBay_801F4690, 0xC0000000 },
    { grGreatBay_801F4440, grGreatBay_801F44A0, grGreatBay_801F44A8,
      grGreatBay_801F44AC, 0 },
    { grGreatBay_801F44B0, grGreatBay_801F4510, grGreatBay_801F4518,
      grGreatBay_801F451C, 0 },
    { grGreatBay_801F598C, grGreatBay_801F59F0, grGreatBay_801F59F8,
      grGreatBay_801F59FC, 0 },
    { grGreatBay_801F598C, grGreatBay_801F59F0, grGreatBay_801F59F8,
      grGreatBay_801F59FC, 0 },
    { grGreatBay_801F598C, grGreatBay_801F59F0, grGreatBay_801F59F8,
      grGreatBay_801F59FC, 0 },
    { grGreatBay_801F598C, grGreatBay_801F59F0, grGreatBay_801F59F8,
      grGreatBay_801F59FC, 0 },
    { grGreatBay_801F5A00, grGreatBay_801F5AF0, grGreatBay_801F5AF8,
      grGreatBay_801F5D48, 0 },
    { grGreatBay_801F5460, grGreatBay_801F55F8, grGreatBay_801F5600,
      grGreatBay_801F5988, 0 }
};

StageData grGb_803E3F6C = {
    (1 << 1) | (1 << 3),
    grGb_803E3E84,
    "/GrGb.dat",
    grGreatBay_801F4240,
    grGreatBay_801F423C,
    grGreatBay_801F42D0,
    grGreatBay_801F42D4,
    grGreatBay_801F42F8,
    grGreatBay_801F680C,
    grGreatBay_801F6814,
    (1 << 0),
    grGb_803E3E60,
    6,
};

typedef struct grGb_804D69E0_t {
    void* x0;
} grGb_804D69E0_t;
grGb_804D69E0_t grGb_804D69E0;

void grGreatBay_801F423C(bool unused)
{
    return;
}

void grGreatBay_801F4240(void)
{
    grGb_804D69E0.x0 = Ground_801C49F8();
    stage_info.unk8C.b4 = false;
    stage_info.unk8C.b5 = true;
    grGreatBay_801F4300(0);
    grGreatBay_801F4300(3);
    grGreatBay_801F4300(4);
    grGreatBay_801F4300(2);
    grGreatBay_801F4300(1);
    grGreatBay_801F4300(9);
    grGreatBay_801F4300(10);
    Ground_801C39C0();
    Ground_801C3BB4();
}

void grGreatBay_801F42D0(void) {}

void grGreatBay_801F42D4(void)
{
    grZakoGenerator_801CAE04(0);
}

bool grGreatBay_801F42F8(void)
{
    return false;
}

HSD_GObj* grGreatBay_801F4300(int gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grGb_803E3E84[gobj_id];

    gobj = Ground_801C14D0(gobj_id);

    if (gobj != NULL) {
        Ground* gp = gobj->user_data;
        gp->x8_callback = NULL;
        gp->xC_callback = NULL;
        GObj_SetupGXLink(gobj, grDisplay_801C5DB0, 3, 0);
        if (callbacks->callback3 != NULL) {
            gp->x1C_callback = callbacks->callback3;
        }
        if (callbacks->callback0 != NULL) {
            callbacks->callback0(gobj);
        }
        if (callbacks->callback2 != NULL) {
            if (gobj_id == 10) {
                HSD_GObjProc_8038FD54(gobj, callbacks->callback2, 5);
            } else {
                HSD_GObjProc_8038FD54(gobj, callbacks->callback2, 4);
            }
        }
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", __FILE__, 247, gobj_id);
    }

    return gobj;
}

void grGreatBay_801F4404(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grGreatBay_801F4430(Ground_GObj* gobj)
{
    return false;
}

void grGreatBay_801F4438(Ground_GObj* gobj)
{
    return;
}

void grGreatBay_801F443C(Ground_GObj* gobj)
{
    return;
}

void grGreatBay_801F4440(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
    grAnime_801C77FC(gobj, 0, 7);
    gp->x11_flags.b012 = 1;
}

bool grGreatBay_801F44A0(Ground_GObj* gobj)
{
    return false;
}

void grGreatBay_801F44A8(Ground_GObj* gobj)
{
    return;
}

void grGreatBay_801F44AC(Ground_GObj* gobj)
{
    return;
}

void grGreatBay_801F44B0(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
    grAnime_801C77FC(gobj, 0, 7);
    gp->x11_flags.b012 = 3;
}

bool grGreatBay_801F4510(Ground_GObj* gobj)
{
    return false;
}

void grGreatBay_801F4518(Ground_GObj* gobj)
{
    return;
}

void grGreatBay_801F451C(Ground_GObj* gobj)
{
    return;
}

void fn_801F4520(HSD_GObj* gobj)
{
    ftCo_800C07F8(gobj, 6, fn_801F6708);
}

void grGreatBay_801F454C(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);

    Ground_801C2ED0(jobj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->x8_callback = NULL;
    gp->x11_flags.b012 = 1;
    gp->xC_callback = NULL;
    gp->x10_flags.b5 = 1;

    Ground_801C4E70(Ground_801C3FA4(gobj, 4), Ground_801C3FA4(gobj, 1),
                    Ground_801C3FA4(gobj, 3), Ground_801C3FA4(gobj, 2),
                    Ground_801C3FA4(gobj, 6), Ground_801C3FA4(gobj, 5));
    mpLib_80057BC0(1);
    grGreatBay_801F5D4C(gobj);
    Ground_801C10B8(gobj, fn_801F4520);
}

bool grGreatBay_801F4650(Ground_GObj* gobj)
{
    return false;
}

void grGreatBay_801F4658(Ground_GObj* gobj)
{
    grGreatBay_801F5E28(gobj);
    Ground_801C2FE0(gobj);
    lb_800115F4();
}

void grGreatBay_801F4690(Ground_GObj* gobj)
{
    return;
}

/// #grGreatBay_801F4694

bool grGreatBay_801F4994(Ground_GObj* gobj)
{
    return false;
}

/// #grGreatBay_801F499C

void grGreatBay_801F545C(Ground_GObj* gobj)
{
    return;
}

/// #grGreatBay_801F5460

bool grGreatBay_801F55F8(Ground_GObj* gobj)
{
    return false;
}

/// #grGreatBay_801F5600

void fn_801F5914(Ground* arg0, s32 arg1, CollData* arg2, s32 arg3,
                 enum mpLib_GroundEnum arg4, f32 farg0)
{
    s32 temp_r0;
    PAD_STACK(12);

    temp_r0 = arg2->x34_flags.b1234;
    if (temp_r0 == 1 || (s32) temp_r0 == 2 || temp_r0 == 3) {
        arg0->gv.greatbay.x10 =
            ((u32) arg2->env_flags & Collide_LedgeGrabMask);
        arg0->gv.greatbay.x14 = (arg0->gv.greatbay.x14 + 1);
        arg0->gv.greatbay.x1C += arg3 / 100.0f;
    }
}

void grGreatBay_801F5988(Ground_GObj* gobj)
{
    return;
}

void grGreatBay_801F598C(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);

    grAnime_801C8138(gobj, gp->map_id, 0);
    grAnime_801C7A04(gobj, 0, 7, 0.0f);
    gp->x11_flags.b012 = 2;
}

bool grGreatBay_801F59F0(Ground_GObj* gobj)
{
    return false;
}

void grGreatBay_801F59F8(Ground_GObj* gobj)
{
    return;
}

void grGreatBay_801F59FC(Ground_GObj* gobj)
{
    return;
}

/// #grGreatBay_801F5A00

bool grGreatBay_801F5AF0(Ground_GObj* gobj)
{
    return false;
}

/// #grGreatBay_801F5AF8

void grGreatBay_801F5D48(Ground_GObj* gobj)
{
    return;
}

/// #grGreatBay_801F5D4C

/// #grGreatBay_801F5E28

/// #fn_801F60C4

/// #grGreatBay_801F62F8

/// #grGreatBay_801F63F4

/// #grGreatBay_801F660C

/// #grGreatBay_801F66A4

/// #fn_801F6708

void grGreatBay_801F67A4(Vec3* vec, f32 arg8)
{
    HSD_psAppSRT* temp_r3_2;
    HSD_Generator* temp_r3;

    temp_r3 = grLib_801C96F8(0x7537, 0x1E, vec);
    if (temp_r3 != NULL) {
        temp_r3_2 = temp_r3->appsrt;
        temp_r3_2->scale.x *= arg8;
        temp_r3_2->scale.y *= arg8;
        temp_r3_2->scale.z *= arg8;
    }
}

DynamicsDesc* grGreatBay_801F680C(enum_t unused)
{
    return NULL;
}

bool grGreatBay_801F6814(Vec3* a, int _, HSD_JObj* joint)
{
    Vec3 b;
    lb_8000B1CC(joint, NULL, &b);

    if (a->y > b.y) {
        return true;
    } else {
        return false;
    }
}
