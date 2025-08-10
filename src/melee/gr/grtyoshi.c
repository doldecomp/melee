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

/* 223B48 */ static void grTYoshi_80223B48(bool);
/* 223B4C */ static void grTYoshi_80223B4C(void);
/* 223BBC */ static void grTyoshi_UnkStage0_OnLoad(void);
/* 223BC0 */ static void grTyoshi_UnkStage0_OnStart(void);
/* 223BE4 */ static bool grTYoshi_80223BE4(void);
/* 223BEC */ static HSD_GObj* grTYoshi_80223BEC(int gobj_id);
/* 223CD4 */ static void grTYoshi_80223CD4(Ground_GObj* gobj);
/* 223D00 */ static bool grTYoshi_80223D00(Ground_GObj*);
/* 223D08 */ static void grTYoshi_80223D08(Ground_GObj*);
/* 223D0C */ static void grTYoshi_80223D0C(Ground_GObj*);
/* 223D10 */ static void grTYoshi_80223D10(Ground_GObj* gobj);
/* 223D60 */ static bool grTYoshi_80223D60(Ground_GObj*);
/* 223D68 */ static void grTYoshi_80223D68(Ground_GObj* gobj);
/* 223D9C */ static void grTYoshi_80223D9C(Ground_GObj*);
/* 223DA0 */ static void grTYoshi_80223DA0(Ground_GObj* gobj);
/* 223DF0 */ static bool grTYoshi_80223DF0(Ground_GObj*);
/* 223DF8 */ static void grTYoshi_80223DF8(Ground_GObj*);
/* 223E18 */ static void grTYoshi_80223E18(Ground_GObj*);
/* 223E1C */ static DynamicsDesc* grTYoshi_80223E1C(enum_t);
/* 223E24 */ static bool grTYoshi_80223E24(Vec3*, int, HSD_JObj*);

static StageCallbacks grTYs_803E9578[] = {
    {
        grTYoshi_80223CD4,
        grTYoshi_80223D00,
        grTYoshi_80223D08,
        grTYoshi_80223D0C,
        0,
    },
    {
        grTYoshi_80223DA0,
        grTYoshi_80223DF0,
        grTYoshi_80223DF8,
        grTYoshi_80223E18,
        0,
    },
    {
        grTYoshi_80223D10,
        grTYoshi_80223D60,
        grTYoshi_80223D68,
        grTYoshi_80223D9C,
        (1 << 30) | (1 << 31),
    },
    { 0 },
};

StageData grTYs_803E95D4 = {
    (1 << 0) | (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5),
    grTYs_803E9578,
    "/GrTYs.dat",
    grTYoshi_80223B4C,
    grTYoshi_80223B48,
    grTyoshi_UnkStage0_OnLoad,
    grTyoshi_UnkStage0_OnStart,
    grTYoshi_80223BE4,
    grTYoshi_80223E1C,
    grTYoshi_80223E24,
    (1 << 0),
    NULL,
    0,
};

extern StageInfo stage_info;

static void grTYoshi_80223B48(bool arg0) {}
static void grTYoshi_80223B4C(void)
{
    stage_info.unk8C.b4 = 0;
    stage_info.unk8C.b5 = 1;
    grTYoshi_80223BEC(0);
    grTYoshi_80223BEC(1);
    grTYoshi_80223BEC(2);
    Ground_801C39C0();
    Ground_801C3BB4();
    Ground_801C4210();
    Ground_801C42AC();
}
static void grTyoshi_UnkStage0_OnLoad(void) {}
static void grTyoshi_UnkStage0_OnStart(void)
{
    grZakoGenerator_801CAE04(false);
}
static bool grTYoshi_80223BE4(void)
{
    return false;
}
static HSD_GObj* grTYoshi_80223BEC(int gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grTYs_803E9578[gobj_id];

    gobj = Ground_801C14D0(gobj_id);
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
            HSD_GObjProc_8038FD54(gobj, callbacks->callback2, 4);
        }
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grtyoshi.c", 0xc3,
                 gobj_id);
    }

    return gobj;
}
static void grTYoshi_80223CD4(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    grAnime_801C8138(gobj, gp->map_id, 0);
}

static bool grTYoshi_80223D00(Ground_GObj* arg0)
{
    return false;
}

static void grTYoshi_80223D08(Ground_GObj* arg0) {}

static void grTYoshi_80223D0C(Ground_GObj* arg0) {}

static void grTYoshi_80223D10(Ground_GObj* gobj)
{
    u8 _[8];

    Ground* gp = gobj->user_data;
    Ground_801C2ED0(gobj->hsd_obj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

static bool grTYoshi_80223D60(Ground_GObj* arg0)
{
    return false;
}

static void grTYoshi_80223D68(Ground_GObj* gobj)
{
    lb_800115F4();
    Ground_801C2FE0(gobj);
}

static void grTYoshi_80223D9C(Ground_GObj* arg0) {}

static void grTYoshi_80223DA0(Ground_GObj* gobj)
{
    u8 _[8];

    Ground* gp = gobj->user_data;
    Ground_801C2ED0(gobj->hsd_obj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

static bool grTYoshi_80223DF0(Ground_GObj* arg0)
{
    return false;
}

static void grTYoshi_80223DF8(Ground_GObj* arg0)
{
    Ground_801C2FE0(arg0);
}

static void grTYoshi_80223E18(Ground_GObj* arg0) {}

static DynamicsDesc* grTYoshi_80223E1C(enum_t arg0)
{
    return NULL;
}

static bool grTYoshi_80223E24(Vec3* arg0, int arg1, HSD_JObj* arg2)
{
    return true;
}
