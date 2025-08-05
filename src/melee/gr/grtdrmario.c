#include <platform.h>

#include "lb/forward.h"
#include <baselib/forward.h>

#include "gr/granime.h"
#include "gr/grdisplay.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "gr/types.h"
#include "lb/lb_00F9.h"

#include <dolphin/mtx.h>
#include <dolphin/os/OSError.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>

void grtDrMario_8022050C(int);                   /* static */
void grtDrMario_80220510(void);                  /* static */
void grtDrMario_80220580(void);                  /* static */
void grtDrMario_80220584(void);                  /* static */
bool grtDrMario_802205A8(void);                  /* static */
HSD_GObj* grtDrMario_802205B0(s32);              /* static */
void grtDrMario_80220698(Ground_GObj*);             /* static */
bool grtDrMario_802206C4(Ground_GObj*);             /* static */
void grtDrMario_802206CC(Ground_GObj*);             /* static */
void grtDrMario_802206D0(Ground_GObj*);             /* static */
void grtDrMario_802206D4(Ground_GObj*);             /* static */
bool grtDrMario_80220724(Ground_GObj*);             /* static */
void grtDrMario_8022072C(Ground_GObj*);             /* static */
void grtDrMario_80220760(Ground_GObj*);             /* static */
void grtDrMario_80220764(Ground_GObj*);             /* static */
bool grtDrMario_802207B4(Ground_GObj*);             /* static */
void grtDrMario_802207BC(Ground_GObj*);             /* static */
void grtDrMario_802207DC(Ground_GObj*);             /* static */
DynamicsDesc* grtDrMario_802207E0(enum_t);       /* static */
bool grtDrMario_802207E8(Vec3*, int, HSD_JObj*); /* static */

static StageCallbacks grTDr_803E8850[4] = {
    { grtDrMario_80220698, grtDrMario_802206C4, grtDrMario_802206CC,
      grtDrMario_802206D0, 0 },
    { grtDrMario_80220764, grtDrMario_802207B4, grtDrMario_802207BC,
      grtDrMario_802207DC, 0 },
    { grtDrMario_802206D4, grtDrMario_80220724, grtDrMario_8022072C,
      grtDrMario_80220760, (1 << 31) | (1 << 30) },
    { NULL, NULL, NULL, NULL, 0 }
};

StageData grTDr_803E88AC = {
    44,
    grTDr_803E8850,
    "/GrTDr.dat",
    grtDrMario_80220510,
    grtDrMario_8022050C,
    grtDrMario_80220580,
    grtDrMario_80220584,
    grtDrMario_802205A8,
    grtDrMario_802207E0,
    grtDrMario_802207E8,
    1,
};

void grtDrMario_8022050C(int unk0) {}

void grtDrMario_80220510(void)
{
    stage_info.unk8C.b4 = false;
    stage_info.unk8C.b5 = true;

    grtDrMario_802205B0(0);
    grtDrMario_802205B0(1);
    grtDrMario_802205B0(2);
    Ground_801C39C0();
    Ground_801C3BB4();
    Ground_801C4210();
    Ground_801C42AC();
}

void grtDrMario_80220580(void) {}

void grtDrMario_80220584(void)
{
    grZakoGenerator_801CAE04(0);
}

bool grtDrMario_802205A8(void)
{
    return false;
}

HSD_GObj* grtDrMario_802205B0(s32 arg0)
{
    HSD_GObj* gobj;
    StageCallbacks* cb;
    Ground* gp;

    cb = &grTDr_803E8850[arg0];
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
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grtdrmario.c", 0xCC,
                 arg0);
    }
    return gobj;
}

void grtDrMario_80220698(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grtDrMario_802206C4(Ground_GObj* gobj)
{
    return false;
}

void grtDrMario_802206CC(Ground_GObj* gobj) {}

void grtDrMario_802206D0(Ground_GObj* gobj) {}

void grtDrMario_802206D4(Ground_GObj* gobj)
{
    Ground_JObjInline1(gobj);
}

bool grtDrMario_80220724(Ground_GObj* gobj)
{
    return false;
}

void grtDrMario_8022072C(Ground_GObj* gobj)
{
    lb_800115F4();
    Ground_801C2FE0(gobj);
}

void grtDrMario_80220760(Ground_GObj* gobj) {}

void grtDrMario_80220764(Ground_GObj* gobj)
{
    Ground_JObjInline1(gobj);
}

bool grtDrMario_802207B4(Ground_GObj* gobj)
{
    return false;
}

void grtDrMario_802207BC(Ground_GObj* gobj)
{
    Ground_801C2FE0(gobj);
}

void grtDrMario_802207DC(Ground_GObj* gobj) {}

DynamicsDesc* grtDrMario_802207E0(enum_t arg0)
{
    return NULL;
}

bool grtDrMario_802207E8(Vec3* arg0, int arg1, HSD_JObj* arg2)
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
