#include "gr/grtfalco.h"

#include "gr/grdisplay.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "lb/lb_00F9.h"
#include "mp/mplib.h"

#include <dolphin/os/os.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>

/* static */ StageCallbacks lbl_803E8918[4] = {
    {
        lbl_80220984,
        lbl_802209B0,
        lbl_802209B8,
        lbl_802209BC,
        0,
    },
    {
        lbl_80220A50,
        lbl_80220AA0,
        lbl_80220AA8,
        lbl_80220AC8,
        0,
    },
    {
        lbl_802209C0,
        lbl_80220A10,
        lbl_80220A18,
        lbl_80220A4C,
        (1 << 30) | (1 << 31),
    },
};

StageData lbl_803E8974 = {
    45,
    lbl_803E8918,
    "/GrTFc.dat",
    lbl_802207F4,
    func_802207F0,
    lbl_8022086C,
    lbl_80220870,
    lbl_80220894,
    lbl_80220ACC,
    lbl_80220B78,
    1,
};

typedef struct grTFalco_UnkStruct {
    s32 unk_0;
    s32 unk_4;
    s32 unk_8;
    s32 unk_C;
} grTFalco_UnkStruct;

grTFalco_UnkStruct* lbl_804D6AF8;

void func_802207F0(int arg0) {}

void lbl_802207F4(void)
{
    lbl_804D6AF8 = Ground_801C49F8();
    stage_info.unk8C.b4 = false;
    stage_info.unk8C.b5 = true;
    func_8022089C(0);
    func_8022089C(1);
    func_8022089C(2);
    Ground_801C39C0();
    Ground_801C3BB4();
    Ground_801C4210();
    Ground_801C42AC();
}

void lbl_8022086C(void) {}

void lbl_80220870(void)
{
    grZakoGenerator_801CAE04(0);
}

bool lbl_80220894(void)
{
    return false;
}

HSD_GObj* func_8022089C(int id)
{
    HSD_GObj* gobj;

    StageCallbacks* cb = &lbl_803E8918[id];
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
            func_8038FD54(gobj, cb->callback2, 4);
        }

    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grtfalco.c", 201, id);
    }

    return gobj;
}

void lbl_80220984(HSD_GObj* gobj)
{
    Ground* gp = (Ground*) HSD_GObjGetUserData(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool lbl_802209B0(HSD_GObj* arg0)
{
    return false;
}

void lbl_802209B8(HSD_GObj* arg0) {}

void lbl_802209BC(HSD_GObj* arg0) {}

void lbl_802209C0(HSD_GObj* gobj)
{
    Ground_JObjInline1(gobj);
}

bool lbl_80220A10(HSD_GObj* arg0)
{
    return false;
}

void lbl_80220A18(HSD_GObj* arg0)
{
    lb_800115F4();
    Ground_801C2FE0(arg0);
}

void lbl_80220A4C(HSD_GObj* arg0) {}

void lbl_80220A50(HSD_GObj* gobj)
{
    Ground_JObjInline1(gobj);
}

bool lbl_80220AA0(HSD_GObj* arg0)
{
    return false;
}

void lbl_80220AA8(HSD_GObj* gobj)
{
    Ground_801C2FE0(gobj);
}

void lbl_80220AC8(HSD_GObj* arg0) {}

bool lbl_80220ACC(enum_t arg0)
{
    if (arg0 != -1) {
        enum_t i = mpLib_80056B6C(arg0);

        if (i != -1 && i == 0) {
            i = mpLib_80054C6C(arg0);

            if (i == (1 << 0)) {
                return lbl_804D6AF8->unk_0;
            }

            if (i == (1 << 1)) {
                return lbl_804D6AF8->unk_4;
            }

            if (i == (1 << 2)) {
                return lbl_804D6AF8->unk_8;
            }

            if (i == (1 << 3)) {
                return lbl_804D6AF8->unk_C;
            }

            return false;
        }
    }

    return false;
}

bool lbl_80220B78(Vec3* arg0, int arg1, HSD_JObj* arg2)
{
    return true;
}
