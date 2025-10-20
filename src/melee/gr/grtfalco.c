#include "gr/grtfalco.h"

#include <placeholder.h>

#include "gr/granime.h"
#include "gr/grdisplay.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "gr/types.h"
#include "lb/lb_00F9.h"

#include "mp/forward.h"

#include "mp/mplib.h"

#include <dolphin/os/OSError.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>

/* static */ StageCallbacks grTFc_803E8918[4] = {
    {
        grTFalco_80220984,
        grTFalco_802209B0,
        grTFalco_802209B8,
        grTFalco_802209BC,
        0,
    },
    {
        grTFalco_80220A50,
        grTFalco_80220AA0,
        grTFalco_80220AA8,
        grTFalco_80220AC8,
        0,
    },
    {
        grTFalco_802209C0,
        grTFalco_80220A10,
        grTFalco_80220A18,
        grTFalco_80220A4C,
        (1 << 30) | (1 << 31),
    },
};

StageData grTFc_803E8974 = {
    45,
    grTFc_803E8918,
    "/GrTFc.dat",
    grTFalco_802207F4,
    grTFalco_802207F0,
    grTfalco_UnkStage0_OnLoad,
    grTfalco_UnkStage0_OnStart,
    grTFalco_80220894,
    grTFalco_80220ACC,
    grTFalco_80220B78,
    1,
};

typedef struct grTFalco_UnkStruct {
    UNK_T unk_0;
    UNK_T unk_4;
    UNK_T unk_8;
    UNK_T unk_C;
} grTFalco_UnkStruct;

grTFalco_UnkStruct* grTFc_804D6AF8;

void grTFalco_802207F0(bool arg0) {}

void grTFalco_802207F4(void)
{
    grTFc_804D6AF8 = Ground_801C49F8();
    stage_info.unk8C.b4 = false;
    stage_info.unk8C.b5 = true;
    grTFalco_8022089C(0);
    grTFalco_8022089C(1);
    grTFalco_8022089C(2);
    Ground_801C39C0();
    Ground_801C3BB4();
    Ground_801C4210();
    Ground_801C42AC();
}

void grTfalco_UnkStage0_OnLoad(void) {}

void grTfalco_UnkStage0_OnStart(void)
{
    grZakoGenerator_801CAE04(0);
}

bool grTFalco_80220894(void)
{
    return false;
}

HSD_GObj* grTFalco_8022089C(int id)
{
    HSD_GObj* gobj;

    StageCallbacks* cb = &grTFc_803E8918[id];
    gobj = Ground_801C14D0(id);
    if (gobj != NULL) {
        Ground* gp = gobj->user_data;
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
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grtfalco.c", 201, id);
    }

    return gobj;
}

void grTFalco_80220984(Ground_GObj* gobj)
{
    Ground* gp = (Ground*) HSD_GObjGetUserData(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grTFalco_802209B0(Ground_GObj* arg0)
{
    return false;
}

void grTFalco_802209B8(Ground_GObj* arg0) {}

void grTFalco_802209BC(Ground_GObj* arg0) {}

void grTFalco_802209C0(Ground_GObj* gobj)
{
    Ground_JObjInline1(gobj);
}

bool grTFalco_80220A10(Ground_GObj* arg0)
{
    return false;
}

void grTFalco_80220A18(Ground_GObj* arg0)
{
    lb_800115F4();
    Ground_801C2FE0(arg0);
}

void grTFalco_80220A4C(Ground_GObj* arg0) {}

void grTFalco_80220A50(Ground_GObj* gobj)
{
    Ground_JObjInline1(gobj);
}

bool grTFalco_80220AA0(Ground_GObj* arg0)
{
    return false;
}

void grTFalco_80220AA8(Ground_GObj* gobj)
{
    Ground_801C2FE0(gobj);
}

void grTFalco_80220AC8(Ground_GObj* arg0) {}

DynamicsDesc* grTFalco_80220ACC(enum_t arg0)
{
    if (arg0 != -1) {
        enum_t i = mpJointFromLine(arg0);

        if (i != -1 && i == 0) {
            i = mpLineGetKind(arg0);

            if (i == CollLine_Floor) {
                return grTFc_804D6AF8->unk_0;
            }

            if (i == CollLine_Ceiling) {
                return grTFc_804D6AF8->unk_4;
            }

            if (i == CollLine_RightWall) {
                return grTFc_804D6AF8->unk_8;
            }

            if (i == CollLine_LeftWall) {
                return grTFc_804D6AF8->unk_C;
            }

            return NULL;
        }
    }

    return NULL;
}

bool grTFalco_80220B78(Vec3* arg0, int arg1, HSD_JObj* arg2)
{
    return true;
}
