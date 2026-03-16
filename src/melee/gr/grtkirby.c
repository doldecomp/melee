
#include <platform.h>

#include "gr/granime.h"
#include "gr/grdisplay.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "gr/types.h"

#include "lb/forward.h"

#include "lb/lb_00F9.h"

#include <baselib/forward.h>

#include <dolphin/mtx.h>
#include <dolphin/os/OSError.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>

void grTKirby_80221364(bool);                  /* static */
void grTKirby_80221368(void);                  /* static */
void grTkirby_UnkStage0_OnLoad(void);          /* static */
void grTkirby_UnkStage0_OnStart(void);         /* static */
bool grTKirby_80221400(void);                  /* static */
HSD_GObj* grTKirby_80221408(s32);              /* static */
void grTKirby_802214F0(Ground_GObj*);          /* static */
bool grTKirby_8022151C(Ground_GObj*);          /* static */
void grTKirby_80221524(Ground_GObj*);          /* static */
void grTKirby_80221528(Ground_GObj*);          /* static */
void grTKirby_8022152C(Ground_GObj*);          /* static */
bool grTKirby_8022157C(Ground_GObj*);          /* static */
void grTKirby_80221584(Ground_GObj*);          /* static */
void grTKirby_802215B8(Ground_GObj*);          /* static */
void grTKirby_802215BC(Ground_GObj*);          /* static */
bool grTKirby_8022160C(Ground_GObj*);          /* static */
void grTKirby_80221614(Ground_GObj*);          /* static */
void grTKirby_80221634(Ground_GObj*);          /* static */
DynamicsDesc* grTKirby_80221638(enum_t);       /* static */
bool grTKirby_80221640(Vec3*, int, HSD_JObj*); /* static */

static StageCallbacks grTKb_803E8BB0[4] = {
    { grTKirby_802214F0, grTKirby_8022151C, grTKirby_80221524,
      grTKirby_80221528, 0 },
    { grTKirby_802215BC, grTKirby_8022160C, grTKirby_80221614,
      grTKirby_80221634, 0 },
    { grTKirby_8022152C, grTKirby_8022157C, grTKirby_80221584,
      grTKirby_802215B8, (1 << 31) | (1 << 30) },
    { NULL, NULL, NULL, NULL, 0 }
};

StageData grTKb_803E8C0C = {
    TKIRBY,
    grTKb_803E8BB0,
    "/GrTKb.dat",
    grTKirby_80221368,
    grTKirby_80221364,
    grTkirby_UnkStage0_OnLoad,
    grTkirby_UnkStage0_OnStart,
    grTKirby_80221400,
    grTKirby_80221638,
    grTKirby_80221640,
    1,
};

void grTKirby_80221364(bool unk) {}

void grTKirby_80221368(void)
{
    stage_info.unk8C.b4 = false;
    stage_info.unk8C.b5 = true;

    grTKirby_80221408(0);
    grTKirby_80221408(1);
    grTKirby_80221408(2);
    Ground_801C39C0();
    Ground_801C3BB4();
    Ground_801C4210();
    Ground_801C42AC();
}

void grTkirby_UnkStage0_OnLoad(void) {}

void grTkirby_UnkStage0_OnStart(void)
{
    grZakoGenerator_801CAE04(0);
}

bool grTKirby_80221400(void)
{
    return false;
}

HSD_GObj* grTKirby_80221408(s32 arg0)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grTKb_803E8BB0[arg0];

    gobj = Ground_GetStageGObj(arg0);

    if (gobj != NULL) {
        Ground_SetupStageCallbacks(gobj, callbacks);
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", __FILE__, 0xC3,
                 arg0);
    }

    return gobj;
}

void grTKirby_802214F0(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grTKirby_8022151C(Ground_GObj* gobj)
{
    return false;
}

void grTKirby_80221524(Ground_GObj* gobj) {}

void grTKirby_80221528(Ground_GObj* gobj) {}

void grTKirby_8022152C(Ground_GObj* gobj)
{
    Ground_JObjInline1(gobj);
}

bool grTKirby_8022157C(Ground_GObj* gobj)
{
    return false;
}

void grTKirby_80221584(Ground_GObj* gobj)
{
    lb_800115F4();
    Ground_801C2FE0(gobj);
}

void grTKirby_802215B8(Ground_GObj* gobj) {}

void grTKirby_802215BC(Ground_GObj* gobj)
{
    Ground_JObjInline1(gobj);
}

bool grTKirby_8022160C(Ground_GObj* gobj)
{
    return false;
}

void grTKirby_80221614(Ground_GObj* gobj)
{
    Ground_801C2FE0(gobj);
}

void grTKirby_80221634(Ground_GObj* gobj) {}

DynamicsDesc* grTKirby_80221638(enum_t arg0)
{
    return NULL;
}

bool grTKirby_80221640(Vec3* arg0, int arg1, HSD_JObj* arg2)
{
    return true;
}
/* Warning: struct HSD_Spline is not defined (only forward-declared) */
/* Warning: struct _HSD_Rvalue is not defined (only forward-declared) */
/* Warning: struct _HSD_RObjDesc is not defined (only forward-declared) */
/* Warning: struct _HSD_ExpDesc is not defined (only forward-declared) */
/* Warning: struct _HSD_ByteCodeExpDesc is not defined (only forward-declared)
 */
/* Warning: struct _HSD_IKHintDesc is not defined (only forward-declared) */
