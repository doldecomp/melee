#include <platform.h>

#include "lb/forward.h"

#include "gr/grfigure2.h"

#include "gr/granime.h"
#include "gr/grdisplay.h"
#include "gr/grfigure1.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/types.h"
#include "lb/lb_00F9.h"

#include <dolphin/mtx.h>
#include <dolphin/os/OSError.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>

/* 20E274 */ static void grFigure2_8020E274(void);
/* 20E2E4 */ static void grFigure2_UnkStage0_OnLoad(void);
/* 20E2E8 */ static void grFigure2_UnkStage0_OnStart(void);
/* 20E30C */ static bool grFigure2_8020E30C(void);
/* 20E314 */ static HSD_GObj* grFigure2_8020E314(int gobj_id);
/* 20E3FC */ static void grFigure2_8020E3FC(Ground_GObj* gobj);
/* 20E428 */ static bool grFigure2_8020E428(Ground_GObj*);
/* 20E430 */ static void grFigure2_8020E430(Ground_GObj* gobj);
/* 20E434 */ static void grFigure2_8020E434(Ground_GObj*);
/* 20E438 */ static void grFigure2_8020E438(Ground_GObj* gobj);
/* 20E464 */ static bool grFigure2_8020E464(Ground_GObj*);
/* 20E46C */ static void grFigure2_8020E46C(Ground_GObj* gobj);
/* 20E490 */ static void grFigure2_8020E490(Ground_GObj*);
/* 20E494 */ static void grFigure2_8020E494(Ground_GObj* gobj);
/* 20E4E4 */ static bool grFigure2_8020E4E4(Ground_GObj*);
/* 20E4EC */ static void grFigure2_8020E4EC(Ground_GObj* gobj);
/* 20E4F0 */ static void grFigure2_8020E4F0(Ground_GObj*);
/* 20E4F4 */ static DynamicsDesc* grFigure2_8020E4F4(enum_t arg0);
/* 20E4FC */ static bool grFigure2_8020E4FC(Vec3* vector, int number,
                                            HSD_JObj* jobj);

static StageCallbacks grEF2_803E6328[3] = {
    { grFigure2_8020E3FC, grFigure2_8020E428, grFigure2_8020E430,
      grFigure2_8020E434, 0UL },
    { grFigure2_8020E438, grFigure2_8020E464, grFigure2_8020E46C,
      grFigure2_8020E490, 0xC0000000 },
    { grFigure2_8020E494, grFigure2_8020E4E4, grFigure2_8020E4EC,
      grFigure2_8020E4F0, 0UL }
};

StageData grEF2_803E6370 = {
    0x00000045,
    grEF2_803E6328,
    "/GrEF2.dat",
    grFigure2_8020E274,
    grFigure1_8020E270,
    grFigure2_UnkStage0_OnLoad,
    grFigure2_UnkStage0_OnStart,
    grFigure2_8020E30C,
    grFigure2_8020E4F4,
    grFigure2_8020E4FC,
    0x00000001,
    NULL,
    0UL,
};

void* grEF2_804D6A78;

extern StageInfo stage_info;

static void grFigure2_8020E274(void)
{
    grEF2_804D6A78 = Ground_801C49F8();
    stage_info.unk8C.b4 = 0;
    stage_info.unk8C.b5 = 1;
    grFigure2_8020E314(0);
    grFigure2_8020E314(2);
    grFigure2_8020E314(1);
    Ground_801C39C0();
    Ground_801C3BB4();
}
static void grFigure2_UnkStage0_OnLoad(void) {}

static void grFigure2_UnkStage0_OnStart(void)
{
    grZakoGenerator_801CAE04(false);
}

static bool grFigure2_8020E30C(void)
{
    return false;
}

static HSD_GObj* grFigure2_8020E314(int gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grEF2_803E6328[gobj_id];

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
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grfigure2.c", 196,
                 gobj_id);
    }
    return gobj;
}
static void grFigure2_8020E3FC(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    grAnime_801C8138(gobj, gp->map_id, 0);
}

static bool grFigure2_8020E428(Ground_GObj* arg0)
{
    return false;
}

static void grFigure2_8020E430(Ground_GObj* gobj) {}

static void grFigure2_8020E434(Ground_GObj* arg0) {}

static void grFigure2_8020E438(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    Ground_801C2ED0(gobj->hsd_obj, gp->map_id);
}

static bool grFigure2_8020E464(Ground_GObj* arg0)
{
    return false;
}

static void grFigure2_8020E46C(Ground_GObj* gobj)
{
    Ground_801C2FE0(gobj);
    lb_800115F4();
}

static void grFigure2_8020E490(Ground_GObj* arg0) {}

static void grFigure2_8020E494(Ground_GObj* gobj)
{
    u8 _[8];

    Ground* gp = gobj->user_data;
    Ground_801C2ED0(gobj->hsd_obj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

static bool grFigure2_8020E4E4(Ground_GObj* arg0)
{
    return false;
}

static void grFigure2_8020E4EC(Ground_GObj* gobj) {}

static void grFigure2_8020E4F0(Ground_GObj* arg0) {}

static DynamicsDesc* grFigure2_8020E4F4(enum_t arg0)
{
    return NULL;
}

static bool grFigure2_8020E4FC(Vec3* vector, int number, HSD_JObj* jobj)
{
    return true;
}
