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
        lbl_80220984,
        lbl_802209B0,
        lbl_802209B8,
        lbl_802209BC,
        FLAGS_ZERO,
    },
    {
        lbl_80220A50,
        lbl_80220AA0,
        lbl_80220AA8,
        lbl_80220AC8,
        FLAGS_ZERO,
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
    lbl_804D6AF8 = func_801C49F8();
    stage_info.unk8C.b4 = false;
    stage_info.unk8C.b5 = true;
    func_8022089C(0);
    func_8022089C(1);
    func_8022089C(2);
    func_801C39C0();
    func_801C3BB4();
    func_801C4210();
    func_801C42AC();
}

void lbl_8022086C(void) {}

void lbl_80220870(void)
{
    func_801CAE04(0);
}

bool lbl_80220894(void)
{
    return false;
}

HSD_GObj* func_8022089C(int id)
{
    HSD_GObj* gobj;

    StageCallbacks* cb = &lbl_803E8918[id];
    gobj = func_801C14D0(id);
    if (gobj != NULL) {
        Map* map = gobj->user_data;
        map->x8_callback = NULL;
        map->xC_callback = NULL;
        GObj_SetupGXLink(gobj, func_801C5DB0, 3, 0);

        if (cb->callback3 != NULL)
            map->x1C_callback = cb->callback3;

        if (cb->callback0 != NULL)
            cb->callback0(gobj);

        if (cb->callback2 != NULL)
            func_8038FD54(gobj, cb->callback2, 4);

    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grtfalco.c", 201, id);
    }

    return gobj;
}

void lbl_80220984(HSD_GObj* gobj)
{
    Map* map = (Map*) HSD_GObjGetUserData(gobj);
    func_801C8138(gobj, map->map_id, 0);
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
    func_800115F4();
    func_801C2FE0(arg0);
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
    func_801C2FE0(gobj);
}

void lbl_80220AC8(HSD_GObj* arg0) {}

bool lbl_80220ACC(enum_t arg0)
{
    if (arg0 != -1) {
        enum_t i = func_80056B6C(arg0);

        if (i != -1 && i == 0) {
            i = func_80054C6C(arg0);

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
