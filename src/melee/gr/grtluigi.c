#include <melee/gr/grtluigi.h>

#include <dolphin/os/os.h>
#include <melee/gr/granime.h>
#include <melee/gr/grdisplay.h>
#include <melee/gr/ground.h>
#include <melee/gr/grzakogenerator.h>
#include <melee/gr/types.h>
#include <melee/lb/lbunknown_003.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjgxlink.h>

/* static */ StageCallbacks lbl_803E8DF0[4] = {
    {
        lbl_80221D9C,
        lbl_80221DC8,
        lbl_80221DD0,
        lbl_80221DD4,
        FLAGS_ZERO,
    },
    {
        lbl_80221E68,
        lbl_80221EB8,
        lbl_80221EC0,
        lbl_80221EE0,
        FLAGS_ZERO,
    },
    {
        lbl_80221DD8,
        lbl_80221E28,
        lbl_80221E30,
        lbl_80221E64,
        (1 << 30) | (1 << 31),
    },
};

StageData lbl_803E8E4C = {
    51,
    lbl_803E8DF0,
    "/GrTLg.dat",
    lbl_80221C14,
    func_80221C10,
    lbl_80221C84,
    lbl_80221C88,
    lbl_80221CAC,
    lbl_80221EE4,
    lbl_80221EEC,
    1,
};

void func_80221C10(int arg0) {}

void lbl_80221C14(void)
{
    stage_info.unk8C.b4 = false;
    stage_info.unk8C.b5 = true;

    func_80221CB4(0);
    func_80221CB4(1);
    func_80221CB4(2);
    func_801C39C0();
    func_801C3BB4();
    func_801C4210();
    func_801C42AC();
}

void lbl_80221C84(void) {}

void lbl_80221C88(void)
{
    func_801CAE04(0);
}

bool lbl_80221CAC(void)
{
    return false;
}

HSD_GObj* func_80221CB4(int arg0)
{
    HSD_GObj* gobj;
    StageCallbacks* cb;
    Ground* gp;

    cb = &lbl_803E8DF0[arg0];
    gobj = func_801C14D0(arg0);
    if (gobj != NULL) {
        gp = gobj->user_data;
        gp->x8_callback = 0;
        gp->xC_callback = 0;
        GObj_SetupGXLink(gobj, &func_801C5DB0, 3, 0);
        if (cb->callback3 != 0U) {
            gp->x1C_callback = cb->callback3;
        }
        if (cb->callback0 != NULL) {
            cb->callback0(gobj);
        }
        if (cb->callback2 != 0U) {
            func_8038FD54(gobj, cb->callback2, 4);
        }
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grtluigi.c", 0xC3, arg0);
    }
    return gobj;
}

void lbl_80221D9C(HSD_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    func_801C8138(gobj, gp->map_id, 0);
}

bool lbl_80221DC8(HSD_GObj* arg0)
{
    return false;
}

void lbl_80221DD0(HSD_GObj* arg0) {}

void lbl_80221DD4(HSD_GObj* arg0) {}

void lbl_80221DD8(HSD_GObj* gobj)
{
    Ground_JObjInline1(gobj);
}

bool lbl_80221E28(HSD_GObj* arg0)
{
    return false;
}

void lbl_80221E30(HSD_GObj* arg0)
{
    func_800115F4();
    func_801C2FE0(arg0);
}

void lbl_80221E64(HSD_GObj* arg0) {}

void lbl_80221E68(HSD_GObj* gobj)
{
    Ground_JObjInline1(gobj);
}

bool lbl_80221EB8(HSD_GObj* arg0)
{
    return false;
}

void lbl_80221EC0(HSD_GObj* gobj)
{
    func_801C2FE0(gobj);
}

void lbl_80221EE0(HSD_GObj* arg0) {}

bool lbl_80221EE4(int arg0)
{
    return false;
}

int lbl_80221EEC(Vec3* arg0, int arg1, HSD_JObj* arg2)
{
    return true;
}
