#include <melee/gr/grtfalco.h>

#include <dolphin/os/os.h>
#include <melee/gr/grdisplay.h>
#include <melee/gr/ground.h>
#include <melee/gr/grzakogenerator.h>
#include <melee/lb/lbunknown_003.h>
#include <melee/mp/mplib.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjgxlink.h>

/* static */ StageCallbacks lbl_803E8918[4] = {
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

StageData lbl_803E8974 = {
    45,
    lbl_803E8918,
    "/GrTFc.dat",
    grTFalco_802207F4,
    grTFalco_802207F0,
    grTFalco_8022086C,
    grTFalco_80220870,
    grTFalco_80220894,
    grTFalco_80220ACC,
    grTFalco_80220B78,
    1,
};

typedef struct grTFalco_UnkStruct {
    s32 unk_0;
    s32 unk_4;
    s32 unk_8;
    s32 unk_C;
} grTFalco_UnkStruct;

grTFalco_UnkStruct* lbl_804D6AF8;

void grTFalco_802207F0(int arg0) {}

void grTFalco_802207F4(void)
{
    lbl_804D6AF8 = Ground_801C49F8();
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

void grTFalco_8022086C(void) {}

void grTFalco_80220870(void)
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

    StageCallbacks* cb = &lbl_803E8918[id];
    gobj = Ground_801C14D0(id);
    if (gobj != NULL) {
        Ground* gp = gobj->user_data;
        gp->x8_callback = NULL;
        gp->xC_callback = NULL;
        GObj_SetupGXLink(gobj, grDisplay_801C5DB0, 3, 0);

        if (cb->callback3 != NULL)
            gp->x1C_callback = cb->callback3;

        if (cb->callback0 != NULL)
            cb->callback0(gobj);

        if (cb->callback2 != NULL)
            func_8038FD54(gobj, cb->callback2, 4);

    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grtfalco.c", 201, id);
    }

    return gobj;
}

void grTFalco_80220984(HSD_GObj* gobj)
{
    Ground* gp = (Ground*) HSD_GObjGetUserData(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grTFalco_802209B0(HSD_GObj* arg0)
{
    return false;
}

void grTFalco_802209B8(HSD_GObj* arg0) {}

void grTFalco_802209BC(HSD_GObj* arg0) {}

void grTFalco_802209C0(HSD_GObj* gobj)
{
    Ground_JObjInline1(gobj);
}

bool grTFalco_80220A10(HSD_GObj* arg0)
{
    return false;
}

void grTFalco_80220A18(HSD_GObj* arg0)
{
    lb_800115F4();
    Ground_801C2FE0(arg0);
}

void grTFalco_80220A4C(HSD_GObj* arg0) {}

void grTFalco_80220A50(HSD_GObj* gobj)
{
    Ground_JObjInline1(gobj);
}

bool grTFalco_80220AA0(HSD_GObj* arg0)
{
    return false;
}

void grTFalco_80220AA8(HSD_GObj* gobj)
{
    Ground_801C2FE0(gobj);
}

void grTFalco_80220AC8(HSD_GObj* arg0) {}

bool grTFalco_80220ACC(enum_t arg0)
{
    if (arg0 != -1) {
        enum_t i = mpLib_80056B6C(arg0);

        if (i != -1 && i == 0) {
            i = mpLib_80054C6C(arg0);

            if (i == (1 << 0))
                return lbl_804D6AF8->unk_0;

            if (i == (1 << 1))
                return lbl_804D6AF8->unk_4;

            if (i == (1 << 2))
                return lbl_804D6AF8->unk_8;

            if (i == (1 << 3))
                return lbl_804D6AF8->unk_C;

            return false;
        }
    }

    return false;
}

bool grTFalco_80220B78(Vec3* arg0, int arg1, HSD_JObj* arg2)
{
    return true;
}
