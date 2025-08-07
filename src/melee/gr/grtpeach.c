#include <platform.h>

#include "lb/forward.h"

#include "grtpeach.h"

#include "gr/granime.h"
#include "gr/grdisplay.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "gr/types.h"
#include "lb/lb_00F9.h"

#include <dolphin/mtx.h>
#include <dolphin/os/OSError.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>

/* 2228B4 */ static void grTPeach_802228B4(bool arg0);
/* 2228B8 */ static void grTPeach_802228B8(void);
/* 222928 */ static void grTPeach_80222928(void);
/* 22292C */ static void grTPeach_8022292C(void);
/* 222950 */ static bool grTPeach_80222950(void);
/* 222958 */ static Ground_GObj* grTPeach_80222958(int arg0);
/* 222A40 */ static void grTPeach_80222A40(Ground_GObj* gobj);
/* 222A6C */ static bool grTPeach_80222A6C(Ground_GObj* gobj);
/* 222A74 */ static void grTPeach_80222A74(Ground_GObj* gobj);
/* 222A78 */ static void grTPeach_80222A78(Ground_GObj* gobj);
/* 222A7C */ static void grTPeach_80222A7C(Ground_GObj* gobj);
/* 222ACC */ static bool grTPeach_80222ACC(Ground_GObj* gobj);
/* 222AD4 */ static void grTPeach_80222AD4(Ground_GObj* gobj);
/* 222B08 */ static void grTPeach_80222B08(Ground_GObj* gobj);
/* 222B0C */ static void grTPeach_80222B0C(Ground_GObj* gobj);
/* 222B5C */ static bool grTPeach_80222B5C(Ground_GObj* gobj);
/* 222B64 */ static void grTPeach_80222B64(Ground_GObj* gobj);
/* 222B84 */ static void grTPeach_80222B84(Ground_GObj* gobj);
/* 222B88 */ static DynamicsDesc* grTPeach_80222B88(enum_t arg0);
/* 222B90 */ static bool grTPeach_80222B90(Vec3* arg0, int arg1,
                                           HSD_JObj* arg2);

StageCallbacks grTPe_803E90F0[4] = {
    {
        grTPeach_80222A40,
        grTPeach_80222A6C,
        grTPeach_80222A74,
        grTPeach_80222A78,
        0,
    },
    {
        grTPeach_80222B0C,
        grTPeach_80222B5C,
        grTPeach_80222B64,
        grTPeach_80222B84,
        0,
    },
    {
        grTPeach_80222A7C,
        grTPeach_80222ACC,
        grTPeach_80222AD4,
        grTPeach_80222B08,
        (1 << 30) | (1 << 31),
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
        0,
    },
};

StageData grTPe_803E914C = {
    (1 << 0) | (1 << 1) | (1 << 2) | (1 << 4) | (1 << 5),
    grTPe_803E90F0,
    "/GrTPe.dat",
    grTPeach_802228B8,
    grTPeach_802228B4,
    grTPeach_80222928,
    grTPeach_8022292C,
    grTPeach_80222950,
    grTPeach_80222B88,
    grTPeach_80222B90,
    (1 << 0),
    NULL,
    0,
};

void grTPeach_802228B4(bool arg0) {}

void grTPeach_802228B8(void)
{
    stage_info.unk8C.b4 = false;
    stage_info.unk8C.b5 = true;

    grTPeach_80222958(0);
    grTPeach_80222958(1);
    grTPeach_80222958(2);
    Ground_801C39C0();
    Ground_801C3BB4();
    Ground_801C4210();
    Ground_801C42AC();
}

void grTPeach_80222928(void) {}

void grTPeach_8022292C(void)
{
    grZakoGenerator_801CAE04(0);
}

bool grTPeach_80222950(void)
{
    return false;
}

Ground_GObj* grTPeach_80222958(int index)
{
    /// @todo Can't move below @c callbacks.
    HSD_GObj* gobj;

    StageCallbacks* callbacks = &grTPe_803E90F0[index];
    gobj = Ground_801C14D0(index);
    if (gobj != NULL) {
        Ground* gp = GET_GROUND(gobj);
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
            HSD_GObjProc_8038FD54(gobj, callbacks->callback2, 4);
        }
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grtpeach.c", 195,
                 index);
    }
    return gobj;
}

void grTPeach_80222A40(Ground_GObj* gobj)
{
    grAnime_801C8138(gobj, GET_GROUND(gobj)->map_id, false);
}

bool grTPeach_80222A6C(Ground_GObj* gobj)
{
    return false;
}

void grTPeach_80222A74(Ground_GObj* gobj) {}

void grTPeach_80222A78(Ground_GObj* gobj) {}

void grTPeach_80222A7C(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Ground_801C2ED0(jobj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, false);
}

bool grTPeach_80222ACC(Ground_GObj* gobj)
{
    return false;
}

void grTPeach_80222AD4(Ground_GObj* gobj)
{
    lb_800115F4();
    Ground_801C2FE0(gobj);
}

void grTPeach_80222B08(Ground_GObj* gobj) {}

void grTPeach_80222B0C(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Ground_801C2ED0(jobj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, false);
}

bool grTPeach_80222B5C(Ground_GObj* gobj)
{
    return false;
}

void grTPeach_80222B64(Ground_GObj* gobj)
{
    Ground_801C2FE0(gobj);
}

void grTPeach_80222B84(Ground_GObj* gobj) {}

DynamicsDesc* grTPeach_80222B88(enum_t arg0)
{
    return NULL;
}

bool grTPeach_80222B90(Vec3* arg0, int arg1, HSD_JObj* arg2)
{
    return true;
}
