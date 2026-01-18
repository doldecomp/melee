#include "grbigblue.h"

#include "grdisplay.h"
#include "grmaterial.h"

#include <platform.h>

#include "baselib/gobjgxlink.h"
#include "baselib/gobjproc.h"
#include "baselib/jobj.h"
#include "gr/inlines.h"
#include "gr/types.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "gr/grzakogenerator.h"

u8 tmpPadData[168] = { 0 };

StageCallbacks grBb_803E29E0[] = {
    { grBigBlue_801E5AE4, grBigBlue_801E5B10, grBigBlue_801E5B18,
      grBigBlue_801E5B1C, 0 },
    { grBigBlue_801E6298, grBigBlue_801E6354, grBigBlue_801E635C,
      grBigBlue_801E6360, 40000000 },
    { grBigBlue_801E6200, grBigBlue_801E6288, grBigBlue_801E6290,
      grBigBlue_801E6294, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { grBigBlue_801E5B20, grBigBlue_801E6114, grBigBlue_801E611C,
      grBigBlue_801E6120, 0 },
    { grBigBlue_801E6904, grBigBlue_801E6C58, grBigBlue_801E6C60,
      grBigBlue_801E855C, 0 },
    { grBigBlue_801E6364, grBigBlue_801E687C, grBigBlue_801E6884,
      grBigBlue_801E68B8, 0 },
    { grBigBlue_801E613C, grBigBlue_801E61BC, grBigBlue_801E61C4,
      grBigBlue_801E61FC, 0 },
    { grBigBlue_801E8D64, grBigBlue_801E93D0, grBigBlue_801E93D8,
      grBigBlue_801E9F38, 80000000 },
    { grBigBlue_801E9F3C, grBigBlue_801EA054, grBigBlue_801EA05C,
      grBigBlue_801EAB4C, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 }
};

void grBigBlue_801E57BC(bool arg) {}

/// #grBigBlue_801E57C0

void grBigBlue_801E59C8(void) {}

void grBigBlue_801E59CC(void)
{
    grZakoGenerator_801CAE04(0);
}

bool grBigBlue_801E59F0(void)
{
    return false;
}

HSD_GObj* grBigBlue_801E59F8(s32 id)
{
    HSD_GObj* gobj;
    StageCallbacks* cbs = &grBb_803E29E0[id];
    gobj = Ground_801C14D0(id);
    if (gobj != NULL) {
        Ground* gp = GET_GROUND(gobj);
        gp->x8_callback = NULL;
        gp->xC_callback = NULL;

        GObj_SetupGXLink(gobj, grDisplay_801C5DB0, 3U, 0U);
        if (cbs->callback3 != NULL) {
            gp->x1C_callback = cbs->callback3;
        }
        if (cbs->callback0 != NULL) {
            cbs->callback0(gobj);
        }
        if (cbs->callback2 != NULL) {
            HSD_GObjProc_8038FD54(gobj, cbs->callback2, 4U);
        }
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grbigblue.c", 0x17E,
                 id);
    }
    return gobj;
}

void grBigBlue_801E5AE4(Ground_GObj* arg0)
{
    grAnime_801C8138(arg0, GET_GROUND(arg0)->map_id, 0);
}

bool grBigBlue_801E5B10(Ground_GObj* arg)
{
    return false;
}

void grBigBlue_801E5B18(Ground_GObj* arg) {}

void grBigBlue_801E5B1C(Ground_GObj* arg) {}

/// #grBigBlue_801E5B20

bool grBigBlue_801E6114(Ground_GObj* arg)
{
    return false;
}

void grBigBlue_801E611C(Ground_GObj* arg) {}

void grBigBlue_801E6120(Ground_GObj* arg) {}

void fn_801E6124(Ground_GObj* gobj)
{
    GET_GROUND(gobj)->gv.bigblue.x0_b0 = false;
}

/// #grBigBlue_801E613C

bool grBigBlue_801E61BC(Ground_GObj* arg)
{
    return false;
}

void grBigBlue_801E61C4(Ground_GObj* gobj)
{
    PAD_STACK(16);
    grBigBlue_801EBAF8(gobj);
    lb_800115F4();
    Ground_801C2FE0(gobj);
}

void grBigBlue_801E61FC(Ground_GObj* arg) {}

void grBigBlue_801E6200(Ground_GObj* arg0)
{
    Ground* gp;
    Ground* temp_r5;
    HSD_JObj* jobj;
    void* filler;

    gp = GET_GROUND(arg0);
    jobj = arg0->hsd_obj;
    grAnime_801C8138(arg0, gp->map_id, 0);
    temp_r5 = GET_GROUND(arg0);
    temp_r5->x10_flags.b2 = 0;
    grMaterial_801C8A04(jobj, 0x08000000U);
    grMaterial_801C8858(jobj, 0x20000000U);
    gp->x11_flags.b012 = 1;
}

bool grBigBlue_801E6288(Ground_GObj* arg)
{
    return false;
}

void grBigBlue_801E6290(Ground_GObj* arg) {}

void grBigBlue_801E6294(Ground_GObj* arg) {}

void grBigBlue_801E6298(Ground_GObj* arg0)
{
    HSD_JObj* temp_r31;
    HSD_JObj* temp_r30;
    HSD_JObj* temp_r29;
    HSD_JObj* temp_r28;
    HSD_JObj* temp_r27;

    Ground* gp = GET_GROUND(arg0);
    grAnime_801C8138(arg0, gp->map_id, 0);
    temp_r27 = Ground_801C3FA4(arg0, 6);
    temp_r28 = Ground_801C3FA4(arg0, 7);
    temp_r29 = Ground_801C3FA4(arg0, 3);
    temp_r30 = Ground_801C3FA4(arg0, 4);
    temp_r31 = Ground_801C3FA4(arg0, 2);
    Ground_801C4E70(Ground_801C3FA4(arg0, 5), temp_r31, temp_r30, temp_r29,
                    temp_r28, temp_r27);
    gp->x11_flags.b012 = 2;
}

bool grBigBlue_801E6354(Ground_GObj* arg)
{
    return false;
}

void grBigBlue_801E635C(Ground_GObj* arg) {}

void grBigBlue_801E6360(Ground_GObj* arg) {}

/// #grBigBlue_801E6364

bool grBigBlue_801E687C(Ground_GObj* arg)
{
    return false;
}

void grBigBlue_801E6884(Ground_GObj* gobj)
{
    grBigBlue_801EF424();
    Ground_801C2FE0(gobj);
}

/// #grBigBlue_801E68B8

/// #grBigBlue_801E6904

bool grBigBlue_801E6C58(Ground_GObj* arg)
{
    return false;
}

/// #grBigBlue_801E6C60

void grBigBlue_801E855C(Ground_GObj* arg) {}

/// #fn_801E8560

/// #grBigBlue_801E8794

/// #grBigBlue_801E8978

/// #grBigBlue_801E89DC

/// #grBigBlue_801E8A1C

/// #grBigBlue_801E8B84

/// #grBigBlue_801E8D04

/// #grBigBlue_801E8D64

bool grBigBlue_801E93D0(Ground_GObj* arg)
{
    return false;
}

/// #grBigBlue_801E93D8

void grBigBlue_801E9F38(Ground_GObj* arg) {}

/// #grBigBlue_801E9F3C

bool grBigBlue_801EA054(Ground_GObj* arg)
{
    return false;
}

/// #grBigBlue_801EA05C

void grBigBlue_801EAB4C(Ground_GObj* arg) {}

/// #grBigBlue_801EAB50

/// #grBigBlue_801EACE8

/// #grBigBlue_801EB004

/// #grBigBlue_801EB4AC

/// #grBigBlue_801EBAF8

/// #grBigBlue_801EC58C

/// #grBigBlue_801EC6C0

/// #grBigBlue_801ECB50

/// #grBigBlue_801ED694

/// #grBigBlue_801EDF44

/// #grBigBlue_801EE398

/// #grBigBlue_801EEF00

/// #grBigBlue_801EF424

/// #fn_801EF60C

/// #grBigBlue_801EF7D8

/// #grBigBlue_801EF844

/// #fn_801EFB9C

DynamicsDesc* grBigBlue_801EFC0C(enum_t arg)
{
    return false;
}

bool grBigBlue_801EFC14(Vec3* a, int b, HSD_JObj* jobj)
{
    Vec3 vec;
    lb_8000B1CC(jobj, NULL, &vec);
    if (a->y > vec.y) {
        return true;
    } else {
        return false;
    }
}
