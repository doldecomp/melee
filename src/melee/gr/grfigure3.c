#include "grfigure3.h"

#include <platform.h>

#include "gr/granime.h"
#include "gr/grdisplay.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/types.h"

#include "lb/forward.h"

#include "lb/lb_00F9.h"

#include <dolphin/mtx.h>
#include <dolphin/os/OSError.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>

static void grFigure3_8020E504(bool number);
static void grFigure3_8020E508(void);
static void grFigure3_UnkStage0_OnLoad(void);
static void grFigure3_UnkStage0_OnStart(void);
static bool grFigure3_8020E5A0(void);
static HSD_GObj* grFigure3_8020E5A8(int gobj_id);
static void grFigure3_8020E690(Ground_GObj* gobj);
static bool grFigure3_8020E6BC(Ground_GObj*);
static void grFigure3_8020E6C4(Ground_GObj* gobj);
static void grFigure3_8020E6C8(Ground_GObj*);
static void grFigure3_8020E6CC(Ground_GObj* gobj);
static bool grFigure3_8020E6F8(Ground_GObj*);
static void grFigure3_8020E700(Ground_GObj* gobj);
static void grFigure3_8020E724(Ground_GObj*);
static void grFigure3_8020E728(Ground_GObj* gobj);
static bool grFigure3_8020E778(Ground_GObj*);
static void grFigure3_8020E780(Ground_GObj* gobj);
static void grFigure3_8020E784(Ground_GObj*);
static DynamicsDesc* grFigure3_8020E788(enum_t);
static bool grFigure3_8020E790(Vec3* vector, int number, HSD_JObj* jobj);

static StageCallbacks grEF2_803E63D8[3] = {
    { grFigure3_8020E690, grFigure3_8020E6BC, grFigure3_8020E6C4,
      grFigure3_8020E6C8, 0UL },
    { grFigure3_8020E6CC, grFigure3_8020E6F8, grFigure3_8020E700,
      grFigure3_8020E724, 0xC0000000 },
    { grFigure3_8020E728, grFigure3_8020E778, grFigure3_8020E780,
      grFigure3_8020E784, 0UL }
};

StageData grEF2_803E6420 = {
    0x00000046,
    grEF2_803E63D8,
    "/GrEF3.dat",
    grFigure3_8020E508,
    grFigure3_8020E504,
    grFigure3_UnkStage0_OnLoad,
    grFigure3_UnkStage0_OnStart,
    grFigure3_8020E5A0,
    grFigure3_8020E788,
    grFigure3_8020E790,
    0x00000001,
    NULL,
    0UL,
};

void* grEF2_804D6A80;

extern StageInfo stage_info;

static void grFigure3_8020E504(bool number) {}

static void grFigure3_8020E508(void)
{
    grEF2_804D6A80 = Ground_801C49F8();
    stage_info.unk8C.b4 = 0;
    stage_info.unk8C.b5 = 1;
    grFigure3_8020E5A8(0);
    grFigure3_8020E5A8(2);
    grFigure3_8020E5A8(1);
    Ground_801C39C0();
    Ground_801C3BB4();
}

static void grFigure3_UnkStage0_OnLoad(void) {}

static void grFigure3_UnkStage0_OnStart(void)
{
    grZakoGenerator_801CAE04(false);
}

static bool grFigure3_8020E5A0(void)
{
    return false;
}

static HSD_GObj* grFigure3_8020E5A8(int gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grEF2_803E63D8[gobj_id];

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
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grfigure3.c", 195,
                 gobj_id);
    }

    return gobj;
}

static void grFigure3_8020E690(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    grAnime_801C8138(gobj, gp->map_id, 0);
}

static bool grFigure3_8020E6BC(Ground_GObj* arg0)
{
    return false;
}

static void grFigure3_8020E6C4(Ground_GObj* gobj) {}

static void grFigure3_8020E6C8(Ground_GObj* arg0) {}

static void grFigure3_8020E6CC(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    Ground_801C2ED0(gobj->hsd_obj, gp->map_id);
}

static bool grFigure3_8020E6F8(Ground_GObj* arg0)
{
    return false;
}

static void grFigure3_8020E700(Ground_GObj* gobj)
{
    Ground_801C2FE0(gobj);
    lb_800115F4();
}

static void grFigure3_8020E724(Ground_GObj* arg0) {}

static void grFigure3_8020E728(Ground_GObj* gobj)
{
    u8 _[8];

    Ground* gp = gobj->user_data;
    Ground_801C2ED0(gobj->hsd_obj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

static bool grFigure3_8020E778(Ground_GObj* arg0)
{
    return false;
}

static void grFigure3_8020E780(Ground_GObj* gobj) {}

static void grFigure3_8020E784(Ground_GObj* arg0) {}

static DynamicsDesc* grFigure3_8020E788(enum_t arg0)
{
    return NULL;
}

static bool grFigure3_8020E790(Vec3* vector, int number, HSD_JObj* jobj)
{
    return true;
}
