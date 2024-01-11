#include "gr/grtkirby.h"

#include "gr/granime.h"
#include "gr/grdisplay.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "gr/types.h"
#include "lb/lb_00F9.h"

#include <dolphin/mtx/types.h>
#include <dolphin/os/os.h>
#include <baselib/gobjgxlink.h>
#include <baselib/jobj.h>

void grTKirby_80221364(int);                   /* static */
void grTKirby_80221368(void);                  /* static */
void grTKirby_802213D8(void);                  /* static */
void grTKirby_802213DC(void);                  /* static */
bool grTKirby_80221400(void);                  /* static */
HSD_GObj* grTKirby_80221408(s32);              /* static */
void grTKirby_802214F0(HSD_GObj*);             /* static */
bool grTKirby_8022151C(HSD_GObj*);             /* static */
void grTKirby_80221524(HSD_GObj*);             /* static */
void grTKirby_80221528(HSD_GObj*);             /* static */
void grTKirby_8022152C(HSD_GObj*);             /* static */
bool grTKirby_8022157C(HSD_GObj*);             /* static */
void grTKirby_80221584(HSD_GObj*);             /* static */
void grTKirby_802215B8(HSD_GObj*);             /* static */
void grTKirby_802215BC(HSD_GObj*);             /* static */
bool grTKirby_8022160C(HSD_GObj*);             /* static */
void grTKirby_80221614(HSD_GObj*);             /* static */
void grTKirby_80221634(HSD_GObj*);             /* static */
lb_UnkAnimStruct* grTKirby_80221638(enum_t);   /* static */
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
    48,
    grTKb_803E8BB0,
    "/GrTKb.dat",
    grTKirby_80221368,
    grTKirby_80221364,
    grTKirby_802213D8,
    grTKirby_802213DC,
    grTKirby_80221400,
    grTKirby_80221638,
    grTKirby_80221640,
    1,
};

void grTKirby_80221364(int unk) {}

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

void grTKirby_802213D8(void) {}

void grTKirby_802213DC(void)
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
    StageCallbacks* cb;
    Ground* gp;

    cb = &grTKb_803E8BB0[arg0];
    gobj = Ground_801C14D0(arg0);
    if (gobj != NULL) {
        gp = gobj->user_data;
        gp->x8_callback = 0;
        gp->xC_callback = 0;
        GObj_SetupGXLink(gobj, &grDisplay_801C5DB0, 3, 0);
        if (cb->callback3 != 0U) {
            gp->x1C_callback = cb->callback3;
        }
        if (cb->callback0 != NULL) {
            cb->callback0(gobj);
        }
        if (cb->callback2 != 0U) {
            HSD_GObjProc_8038FD54(gobj, cb->callback2, 4);
        }
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grtkirby.c", 0xC3,
                 arg0);
    }
    return gobj;
}

void grTKirby_802214F0(HSD_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grTKirby_8022151C(HSD_GObj* gobj)
{
    return false;
}

void grTKirby_80221524(HSD_GObj* gobj) {}

void grTKirby_80221528(HSD_GObj* gobj) {}

void grTKirby_8022152C(HSD_GObj* gobj)
{
    Ground_JObjInline1(gobj);
}

bool grTKirby_8022157C(HSD_GObj* gobj)
{
    return false;
}

void grTKirby_80221584(HSD_GObj* gobj)
{
    lb_800115F4();
    Ground_801C2FE0(gobj);
}

void grTKirby_802215B8(HSD_GObj* gobj) {}

void grTKirby_802215BC(HSD_GObj* gobj)
{
    Ground_JObjInline1(gobj);
}

bool grTKirby_8022160C(HSD_GObj* gobj)
{
    return false;
}

void grTKirby_80221614(HSD_GObj* gobj)
{
    Ground_801C2FE0(gobj);
}

void grTKirby_80221634(HSD_GObj* gobj) {}

lb_UnkAnimStruct* grTKirby_80221638(enum_t arg0)
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
