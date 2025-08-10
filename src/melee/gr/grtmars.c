#include <platform.h>

#include "lb/forward.h"

#include "gr/granime.h"
#include "gr/grdisplay.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/types.h"
#include "lb/lb_00F9.h"

#include <dolphin/mtx.h>
#include <dolphin/os/OSError.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>

/* 221EF4 */ static void grTMars_80221EF4(bool);
/* 221EF8 */ static void grTMars_80221EF8(void);
/* 221F68 */ static void grTmars_UnkStage0_OnLoad(void);
/* 221F6C */ static void grTmars_UnkStage0_OnStart(void);
/* 221F90 */ static bool grTMars_80221F90(void);
/* 221F98 */ static HSD_GObj* grTMars_80221F98(int);
/* 222080 */ static void grTMars_80222080(Ground_GObj*);
/* 2220AC */ static bool grTMars_802220AC(Ground_GObj*);
/* 2220B4 */ static void grTMars_802220B4(Ground_GObj*);
/* 2220B8 */ static void grTMars_802220B8(Ground_GObj*);
/* 2220BC */ static void grTMars_802220BC(Ground_GObj*);
/* 22210C */ static bool grTMars_8022210C(Ground_GObj*);
/* 222114 */ static void grTMars_80222114(Ground_GObj*);
/* 222148 */ static void grTMars_80222148(Ground_GObj*);
/* 22214C */ static void grTMars_8022214C(Ground_GObj*);
/* 22219C */ static bool grTMars_8022219C(Ground_GObj*);
/* 2221A4 */ static void grTMars_802221A4(Ground_GObj*);
/* 2221C4 */ static void grTMars_802221C4(Ground_GObj*);
/* 2221C8 */ static DynamicsDesc* grTMars_802221C8(enum_t);
/* 2221D0 */ static bool grTMars_802221D0(Vec3*, int, HSD_JObj*);

extern StageInfo stage_info;

static StageCallbacks grTMs_803E8EB0[4] = {
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

StageData grTMs_803E8F0C = {
    0x00000034,       grTMs_803E8EB0,   "/GrTMs.dat",     grTMars_80221EF8,
    grTMars_80221EF4, grTmars_UnkStage0_OnLoad, grTmars_UnkStage0_OnStart, grTMars_80221F90,
    grTMars_802221C8, grTMars_802221D0, 0x00000001,
};

static void grTMars_80221EF4(bool arg0) {}

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

static void grTmars_UnkStage0_OnLoad(void)
{
    return;
}

static void grTmars_UnkStage0_OnStart(void)
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

    callbacks = &grTMs_803E8EB0[id];
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
            HSD_GObjProc_8038FD54(gobj, callbacks->callback2, 4);
        }
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grtmars.c", 0xC3, id);
    }

    return gobj;
}

static void grTMars_80222080(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    grAnime_801C8138(gobj, gp->map_id, 0);
}

static bool grTMars_802220AC(Ground_GObj* arg0)
{
    return false;
}

static void grTMars_802220B4(Ground_GObj* arg0)
{
    return;
}

static void grTMars_802220B8(Ground_GObj* arg0)
{
    return;
}

static void grTMars_802220BC(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;

    u8 _[8];

    Ground_801C2ED0(gobj->hsd_obj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

static bool grTMars_8022210C(Ground_GObj* arg0)
{
    return false;
}

static void grTMars_80222114(Ground_GObj* gobj)
{
    lb_800115F4();
    Ground_801C2FE0(gobj);
}

static void grTMars_80222148(Ground_GObj* arg0) {}

static void grTMars_8022214C(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;

    u8 _[8];

    Ground_801C2ED0(gobj->hsd_obj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

static bool grTMars_8022219C(Ground_GObj* arg0)
{
    return false;
}

static void grTMars_802221A4(Ground_GObj* gobj)
{
    Ground_801C2FE0(gobj);
}

static void grTMars_802221C4(Ground_GObj* arg0) {}

static DynamicsDesc* grTMars_802221C8(enum_t arg0)
{
    return NULL;
}

static bool grTMars_802221D0(Vec3* arg0, int arg1, HSD_JObj* arg2)
{
    return true;
}
