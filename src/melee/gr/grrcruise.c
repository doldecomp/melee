#include "grrcruise.h"

#include "grzakogenerator.h"

#include <platform.h>
#include <sysdolphin/baselib/dobj.h>

#include "cm/camera.h"
#include "gm/gm_1A45.h"
#include "gr/grdisplay.h"
#include "gr/grlib.h"
#include "gr/ground.h"
#include "gr/inlines.h"
#include "lb/lb_00F9.h"

void grRCruise_801FF164(bool arg) {}

/// #grRCruise_801FF168

void grRCruise_801FF298(void) {}

void grRCruise_801FF29C(void)
{
    grZakoGenerator_801CAE04(0);
}

bool grRCruise_801FF2C0(void)
{
    return false;
}

/// #grRCruise_801FF2C8

void grRCruise_801FF3B4(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138((HSD_GObj*) gobj, gp->map_id, 0);
}

bool grRCruise_801FF3E0(Ground_GObj* arg)
{
    return false;
}

void grRCruise_801FF3E8(Ground_GObj* arg) {}

void grRCruise_801FF3EC(Ground_GObj* arg) {}

void grRCruise_801FF3F0(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->x11_flags.b012 = 2;
}

bool grRCruise_801FF434(Ground_GObj* arg)
{
    return false;
}

void grRCruise_801FF43C(Ground_GObj* arg) {}

void grRCruise_801FF440(Ground_GObj* arg) {}

/// #fn_801FF444

/// #grRCruise_801FF5B4

bool grRCruise_801FF6CC(Ground_GObj* arg)
{
    return false;
}

void grRCruise_801FF6D4(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    if (gp->gv.unk.xD4 == 0) {
        grRCruise_80201588(gobj);
        grRCruise_8020071C(gobj);
        grRCruise_80200C04(gobj);
    }
    lb_800115F4();
    grRCruise_80201110(gobj);
    Ground_801C2FE0(gobj);
}

void grRCruise_801FF738(Ground_GObj* arg) {}

void grRCruise_801FF73C(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    grAnime_801C8138(gobj, gp->map_id, 0);
    HSD_JObjSetFlagsAll(gobj->hsd_obj, JOBJ_HIDDEN);
    HSD_JObjClearFlagsAll(Ground_801C3FA4(gobj, 31), JOBJ_HIDDEN);
}

bool grRCruise_801FF794(Ground_GObj* arg)
{
    return false;
}

void grRCruise_801FF79C(Ground_GObj* arg) {}

void grRCruise_801FF7A0(Ground_GObj* arg) {}

/// #grRCruise_801FF7A4

bool grRCruise_801FF8DC(Ground_GObj* arg)
{
    return false;
}

void grRCruise_801FF8E4(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grLib_801C9B8C(&gp->gv);
    Ground_801C2FE0(gobj);
}

void grRCruise_801FF920(Ground_GObj* arg) {}

/// #grRCruise_801FF924

bool grRCruise_801FFAD4(Ground_GObj* arg)
{
    return false;
}

/// #grRCruise_801FFADC

void grRCruise_80200070(Ground_GObj* arg) {}

/// #grRCruise_80200074

bool grRCruise_8020014C(Ground_GObj* arg)
{
    return false;
}

/// #grRCruise_80200154

void grRCruise_8020045C(Ground_GObj* arg) {}

/// #fn_80200460

void grRCruise_80200540(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    gp->gv.rcruise.x18 = 0.0F;
    gp->gv.rcruise.x14 = 0.0F;
    gp->gv.rcruise.x1C = 0.0F;
    gp->gv.rcruise.x20 = 0.0F;
    gp->gv.rcruise.x34 = 0;
    gp->gv.rcruise.x30 = 0;
    gp->gv.rcruise.x28 = 0.0F;
    gp->gv.rcruise.x24 = 0.0F;
    gp->gv.rcruise.x38 = 0;
    gp->gv.rcruise.x2C = 0;
}

/// #fn_80200578

/// #grRCruise_8020071C

/// #grRCruise_80200B48

/// #grRCruise_80200C04

void fn_802010A4(Ground_GObj* gobj, s32 id, CollData* coll)
{
    Ground* gp = gobj->user_data;
    s32 i;

    if ((s32) coll->x34_flags.b1234 != 1) {
        return;
    }

    for (i = 0; i < 17; i++) {
        struct grRCruise_Entry* entry = &gp->gv.rcruise.entries[i];
        if (entry->x02 == id) {
            if (entry->x00 == 0) {
                entry->x04 = 0;
                entry->x00 = 1;
            }
            entry->x08++;
            return;
        }
    }
}

/// #grRCruise_80201110

/// #grRCruise_80201288

/// #grRCruise_80201410

/// #grRCruise_80201588

void grRCruise_80201918(Vec3* vec)
{
    HSD_GObj* gobj = Ground_801C2BA4(3);
    if (gobj != NULL) {
        Ground* gp = gobj->user_data;
        if (gp != NULL) {
            *vec = *(Vec3*)((u8*)gp + 0xE0);
            return;
        }
    }
    vec->x = vec->y = vec->z = 0.0f;
}

/// #grRCruise_80201988

void grRCruise_80201B60(HSD_JObj* jobj, s32 arg1)
{
    HSD_DObj* dobj;
    HSD_DObj* next;
    PAD_STACK(8);

    dobj = HSD_JObjGetDObj(jobj);
    while (dobj != NULL) {
        if (arg1 != 0) {
            HSD_DObjClearFlags(dobj, 1U);
        } else {
            HSD_DObjSetFlags(dobj, 1U);
        }
        if (dobj != NULL) {
            next = dobj->next;
        } else {
            next = NULL;
        }
        dobj = next;
    }
}

void fn_80201BE0(HSD_GObj* gobj, s32 pass)
{
    if (gm_801A45E8(1) != 0 || gm_801A45E8(2) != 0 || Camera_8003010C() != 0) {
        return;
    }
    grDisplay_801C5DB0(gobj, pass);
}

DynamicsDesc* grRCruise_80201C50(enum_t arg)
{
    return false;
}

bool grRCruise_80201C58(Vec3* arg, int arg0, HSD_JObj* jobj)
{
    return true;
}
