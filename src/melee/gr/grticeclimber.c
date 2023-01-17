#include <melee/gr/grticeclimber.h>

#include <dolphin/os/os.h>
#include <melee/gr/granime.h>
#include <melee/gr/grdisplay.h>
#include <melee/gr/ground.h>
#include <melee/gr/grzakogenerator.h>
#include <melee/gr/types.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjproc.h>

/* static */ StageCallbacks lbl_803E8A98[4] = {
    {
        lbl_8022109C,
        lbl_802210C8,
        lbl_802210D0,
        lbl_802210D4,
        FLAGS_ZERO,
    },
    {
        lbl_8022118C,
        lbl_802211DC,
        lbl_802211E4,
        lbl_80221204,
        FLAGS_ZERO,
    },
    {
        lbl_802210D8,
        lbl_8022114C,
        lbl_80221154,
        lbl_80221188,
        (1 << 30) | (1 << 31),
    },
};

StageData lbl_803E8AF4 = {
    47,           lbl_803E8A98, "/GrTIc.dat", lbl_80220F14, func_80220F10,
    lbl_80220F84, lbl_80220F88, lbl_80220FAC, lbl_80221354, lbl_8022135C,
    (1 << 0),
};

void func_80220F10(bool arg0) {}

void lbl_80220F14(void)
{
    stage_info.unk8C.b4 = false;
    stage_info.unk8C.b5 = true;

    func_80220FB4(0);
    func_80220FB4(1);
    func_80220FB4(2);
    func_801C39C0();
    func_801C3BB4();
    func_801C4210();
    func_801C42AC();
}

void lbl_80220F84(void) {}

void lbl_80220F88(void)
{
    func_801CAE04(0);
}

bool lbl_80220FAC(void)
{
    return false;
}

HSD_GObj* func_80220FB4(int id)
{
    /// @todo Cannot be moved below @c cb due to an inline
    HSD_GObj* gobj;

    StageCallbacks* cb = &lbl_803E8A98[id];
    gobj = func_801C14D0(id);

    if (gobj != NULL) {
        Map* map = (Map*) HSD_GObjGetUserData(gobj);
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
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grticeclimber.c", 202,
                 id);
    }

    return gobj;
}

void lbl_8022109C(HSD_GObj* gobj)
{
    Map* map = (Map*) HSD_GObjGetUserData(gobj);
    func_801C8138(gobj, map->map_id, 0);
}

bool lbl_802210C8(HSD_GObj* arg0)
{
    return false;
}

void lbl_802210D0(HSD_GObj* arg0) {}
