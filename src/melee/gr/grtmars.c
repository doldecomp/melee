#include <melee/gr/grtmars.h>

#include <dolphin/os/os.h>
#include <melee/gr/granime.h>
#include <melee/gr/grdisplay.h>
#include <melee/gr/ground.h>
#include <melee/gr/grzakogenerator.h>
#include <melee/gr/stage.h>
#include <melee/lb/lbunknown_003.h>
#include <sysdolphin/baselib/gobjgxlink.h>

extern StageInfo stage_info;

static StageCallbacks lbl_803E8EB0[4] = {
    {
        grTMars_80222080,
        grTMars_802220AC,
        grTMars_802220B4,
        grTMars_802220B8,
    },
    {
        grTMars_8022214C,
        grTMars_8022219C,
        grTMars_802221A4,
        grTMars_802221C4,
    },
    {
        grTMars_802220BC,
        grTMars_8022210C,
        grTMars_80222114,
        grTMars_80222148,
        0xC0000000,
    },
};

StageData lbl_803E8F0C = {
    0x00000034,       lbl_803E8EB0,     "/GrTMs.dat",     grTMars_80221EF8,
    grTMars_80221EF4, grTMars_80221F68, grTMars_80221F6C, grTMars_80221F90,
    grTMars_802221C8, grTMars_802221D0, 0x00000001,
};

static void grTMars_80221EF4(int arg0) {}

static void grTMars_80221EF8(void)
{
    stage_info.unk8C.b4 = false;
    stage_info.unk8C.b5 = true;
    grTMars_80221F98(0);
    grTMars_80221F98(1);
    grTMars_80221F98(2);
    Ground_801C39C0();
    Ground_801C3BB4();
    Ground_801C4210();
    Ground_801C42AC();
}

static void grTMars_80221F68(void)
{
    return;
}

static void grTMars_80221F6C(void)
{
    grZakoGenerator_801CAE04(0);
}

static bool grTMars_80221F90(void)
{
    return false;
}

static HSD_GObj* grTMars_80221F98(int id)
{
    HSD_GObj* gobj;
    Ground* gp;
    StageCallbacks* callbacks;

    callbacks = &lbl_803E8EB0[id];
    gobj = Ground_801C14D0(id);

    if (gobj != NULL) {
        gp = gobj->user_data;
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
            func_8038FD54(gobj, callbacks->callback2, 4);
        }
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grtmars.c", 0xC3, id);
    }

    return gobj;
}

static void grTMars_80222080(HSD_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    grAnime_801C8138(gobj, gp->map_id, 0);
}

static bool grTMars_802220AC(HSD_GObj* arg0)
{
    return false;
}

static void grTMars_802220B4(HSD_GObj* arg0)
{
    return;
}

static void grTMars_802220B8(HSD_GObj* arg0)
{
    return;
}

static void grTMars_802220BC(HSD_GObj* gobj)
{
    Ground* gp = gobj->user_data;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Ground_801C2ED0(gobj->hsd_obj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

static bool grTMars_8022210C(HSD_GObj* arg0)
{
    return false;
}

static void grTMars_80222114(HSD_GObj* gobj)
{
    lb_800115F4();
    Ground_801C2FE0(gobj);
}

static void grTMars_80222148(HSD_GObj* arg0) {}

static void grTMars_8022214C(HSD_GObj* gobj)
{
    Ground* gp = gobj->user_data;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Ground_801C2ED0(gobj->hsd_obj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

static bool grTMars_8022219C(HSD_GObj* arg0)
{
    return false;
}

static void grTMars_802221A4(HSD_GObj* gobj)
{
    Ground_801C2FE0(gobj);
}

static void grTMars_802221C4(HSD_GObj* arg0) {}

static bool grTMars_802221C8(int arg0)
{
    return false;
}

static bool grTMars_802221D0(Vec3* arg0, int arg1, HSD_JObj* arg2)
{
    return true;
}
