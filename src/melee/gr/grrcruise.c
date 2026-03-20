#include "grrcruise.h"

#include "grzakogenerator.h"

#include <platform.h>

#include "cm/camera.h"

#include "forward.h"

#include "gm/gm_1A45.h"
#include "gr/grdatfiles.h"
#include "gr/grdisplay.h"
#include "gr/grlib.h"
#include "gr/ground.h"
#include "gr/inlines.h"

#include "lb/forward.h"

#include "lb/lb_00F9.h"
#include "mp/mplib.h"

#include <baselib/archive.h>
#include <baselib/dobj.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>

StageCallbacks grRc_803E4E34[7] = {
    { grRCruise_801FF3B4, grRCruise_801FF3E0, grRCruise_801FF3E8,
      grRCruise_801FF3EC, 0 },
    { grRCruise_801FF5B4, grRCruise_801FF6CC, grRCruise_801FF6D4,
      grRCruise_801FF738, 0xC0000000 },
    { grRCruise_801FF3F0, grRCruise_801FF434, grRCruise_801FF43C,
      grRCruise_801FF440, 0 },
    { grRCruise_801FF924, grRCruise_801FFAD4, grRCruise_801FFADC,
      grRCruise_80200070, 0 },
    { grRCruise_80200074, grRCruise_8020014C, grRCruise_80200154,
      grRCruise_8020045C, 0 },
    { grRCruise_801FF73C, grRCruise_801FF794, grRCruise_801FF79C,
      grRCruise_801FF7A0, 0 },
    { grRCruise_801FF7A4, grRCruise_801FF8DC, grRCruise_801FF8E4,
      grRCruise_801FF920, 0 },
};

extern s16 grRc_803E4FF0[];

static struct {
    int x0;
}* grRc_804D6A10;

void grRCruise_801FF164(bool arg) {}

void grRCruise_801FF168(void)
{
    HSD_GObj* jgobj;
    HSD_GObj* grgobj;
    Ground* gp;
    Ground* gp2;
    HSD_JObj* jobj;
    HSD_GObj* gobj6;
    HSD_GObj* gobj1;
    HSD_GObj* gobj4;

    grRc_804D6A10 = Ground_801C49F8();
    stage_info.unk8C.b4 = 1;
    stage_info.unk8C.b5 = 0;
    jgobj = grRCruise_801FF2C8(3);
    gp = GET_GROUND(jgobj);
    gp->gv.rcruise.xC4.b0 = 1;
    jobj = GET_JOBJ(jgobj);
    HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
    grgobj = grRCruise_801FF2C8(3);
    gp2 = GET_GROUND(grgobj);
    gp2->gv.rcruise2.xEC = jgobj;
    grRCruise_801FF2C8(0);
    grRCruise_801FF2C8(2);
    grRCruise_801FF2C8(5);
    gobj1 = grRCruise_801FF2C8(1);
    gobj6 = grRCruise_801FF2C8(6);
    gobj4 = grRCruise_801FF2C8(4);
    Ground_801C39C0();
    Ground_801C3BB4();
    grRCruise_801FFADC(grgobj);
    Ground_801C2FE0(gobj1);
    Ground_801C32AC(1);
    Ground_801C2FE0(gobj6);
    Ground_801C32AC(6);
    Ground_801C2FE0(gobj4);
    Ground_801C32AC(4);
    mpLib_80057BC0(11);
}

void grRCruise_801FF298(void) {}

void grRCruise_801FF29C(void)
{
    grZakoGenerator_801CAE04(0);
}

bool grRCruise_801FF2C0(void)
{
    return false;
}

HSD_GObj* grRCruise_801FF2C8(int gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grRc_803E4E34[gobj_id];

    gobj = Ground_GetStageGObj(gobj_id);

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
            HSD_GObj_SetupProc(gobj, callbacks->callback2, 4);
        }
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", __FILE__, 290, gobj_id);
    }

    return gobj;
}

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

void grRCruise_801FF444(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    mpJointSetCb1(5, gobj, grRCruise_80200578);
    mpJointSetCb1(27, gobj, (mpLib_Callback) grRCruise_802010A4);
    mpJointSetCb1(36, gobj, (mpLib_Callback) grRCruise_802010A4);
    mpJointSetCb1(37, gobj, (mpLib_Callback) grRCruise_802010A4);
    mpJointSetCb1(38, gobj, (mpLib_Callback) grRCruise_802010A4);
    mpJointSetCb1(39, gobj, (mpLib_Callback) grRCruise_802010A4);
    mpJointSetCb1(40, gobj, (mpLib_Callback) grRCruise_802010A4);
    mpJointSetCb1(41, gobj, (mpLib_Callback) grRCruise_802010A4);
    mpJointSetCb1(42, gobj, (mpLib_Callback) grRCruise_802010A4);
    mpJointSetCb1(43, gobj, (mpLib_Callback) grRCruise_802010A4);
    mpJointSetCb1(28, gobj, (mpLib_Callback) grRCruise_802010A4);
    mpJointSetCb1(29, gobj, (mpLib_Callback) grRCruise_802010A4);
    mpJointSetCb1(30, gobj, (mpLib_Callback) grRCruise_802010A4);
    mpJointSetCb1(31, gobj, (mpLib_Callback) grRCruise_802010A4);
    mpJointSetCb1(32, gobj, (mpLib_Callback) grRCruise_802010A4);
    mpJointSetCb1(33, gobj, (mpLib_Callback) grRCruise_802010A4);
    mpJointSetCb1(34, gobj, (mpLib_Callback) grRCruise_802010A4);
    mpJointSetCb1(35, gobj, (mpLib_Callback) grRCruise_802010A4);
    gp->gv.rcruise.x10 = 0;
}

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

void grRCruise_801FF7A4(Ground_GObj* gobj)
{
    UnkArchiveStruct* archive;
    DynamicsDesc* data;
    Ground* gp;
    HSD_JObj* jobj;

    gp = GET_GROUND(gobj);
    jobj = GET_JOBJ(gobj);
    Ground_801C2ED0(jobj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 0);
    grAnime_801C752C(jobj, 1, 30628, HSD_AObjSetFlags, 3, 0x20000000);
    if ((archive = grDatFiles_801C6324(), archive != NULL) &&
        (data = HSD_ArchiveGetPublicAddress(archive->unk0,
                                            "dynamicsdata_shipflag"),
         data != NULL))
    {
        Ground_801C3FA4(gobj, 23);
        grLib_801C9B20(jobj, data, &gp->gv.rcruise2.xC4);
    } else {
        gp->gv.rcruise2.xC4.data = NULL;
    }

    jobj = Ground_801C3FA4(gobj, 10);
    if (jobj != NULL) {
        Ground_801C2D0C(0, jobj);
    }
    jobj = Ground_801C3FA4(gobj, 11);
    if (jobj != NULL) {
        Ground_801C2D0C(1, jobj);
    }
    jobj = Ground_801C3FA4(gobj, 12);
    if (jobj != NULL) {
        Ground_801C2D0C(2, jobj);
    }
    jobj = Ground_801C3FA4(gobj, 13);
    if (jobj != NULL) {
        Ground_801C2D0C(3, jobj);
    }
}

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

/// #grRCruise_80200578

/// #grRCruise_8020071C

void grRCruise_80200B48(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    s32 i;

    for (i = 0; i < 17; i++) {
        struct grRCruise_Entry* entry = &gp->gv.rcruise.entries[i];
        entry->x02 =
            Ground_801C32D4(gp->map_id, grRc_803E4FF0[i]);
        entry->x14 = Ground_801C3FA4(gobj, grRc_803E4FF0[i]);
        entry->x08 = 0;
        entry->x04 = 0;
        entry->x0C = HSD_JObjGetTranslationY(entry->x14);
        entry->x00 = 0;
    }
}

/// #grRCruise_80200C04

// TODO: is this GET_GROUND? calling it directly didn't work.
inline Ground* grRCruise_802010A4_inline(Ground_GObj* arg0)
{
    return arg0->user_data;
}

void grRCruise_802010A4(Ground_GObj* gobj, s32 id, CollData* coll)
{
    Ground* gp = grRCruise_802010A4_inline(gobj);
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
            *vec = *(Vec3*) ((u8*) gp + 0xE0);
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
