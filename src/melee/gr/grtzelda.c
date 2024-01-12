#include "gr/grtzelda.h"

#include "gr/granime.h"
#include "gr/grdisplay.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "gr/types.h"
#include "lb/lb_00F9.h"

#include <dolphin/mtx/types.h>
#include <dolphin/os.h>
#include <baselib/gobjgxlink.h>
#include <baselib/jobj.h>

void grTZelda_80223E2C(int);                   /* static */
void grTZelda_80223E30(void);                  /* static */
void grTZelda_80223EA0(void);                  /* static */
void grTZelda_80223EA4(void);                  /* static */
bool grTZelda_80223EC8(void);                  /* static */
HSD_GObj* grTZelda_80223ED0(s32);              /* static */
void grTZelda_80223FB8(HSD_GObj*);             /* static */
bool grTZelda_80223FE4(HSD_GObj*);             /* static */
void grTZelda_80223FEC(HSD_GObj*);             /* static */
void grTZelda_80223FF0(HSD_GObj*);             /* static */
void grTZelda_80223FF4(HSD_GObj*);             /* static */
bool grTZelda_80224044(HSD_GObj*);             /* static */
void grTZelda_8022404C(HSD_GObj*);             /* static */
void grTZelda_80224080(HSD_GObj*);             /* static */
void grTZelda_80224084(HSD_GObj*);             /* static */
bool grTZelda_802240D4(HSD_GObj*);             /* static */
void grTZelda_802240DC(HSD_GObj*);             /* static */
void grTZelda_802240FC(HSD_GObj*);             /* static */
lb_UnkAnimStruct* grTZelda_80224100(enum_t);   /* static */
bool grTZelda_80224108(Vec3*, int, HSD_JObj*); /* static */

static StageCallbacks grTZd_803E9638[4] = {
    { grTZelda_80223FB8, grTZelda_80223FE4, grTZelda_80223FEC,
      grTZelda_80223FF0, 0 },
    { grTZelda_80224084, grTZelda_802240D4, grTZelda_802240DC,
      grTZelda_802240FC, 0 },
    { grTZelda_80223FF4, grTZelda_80224044, grTZelda_8022404C,
      grTZelda_80224080, (1 << 31) | (1 << 30) },
    { NULL, NULL, NULL, NULL, 0 }
};

StageData grTZd_803E9694 = {
    62,
    grTZd_803E9638,
    "/GrTZd.dat",
    grTZelda_80223E30,
    grTZelda_80223E2C,
    grTZelda_80223EA0,
    grTZelda_80223EA4,
    grTZelda_80223EC8,
    grTZelda_80224100,
    grTZelda_80224108,
    1,
};

void grTZelda_80223E2C(int unk0) {}

void grTZelda_80223E30(void)
{
    stage_info.unk8C.b4 = false;
    stage_info.unk8C.b5 = true;

    grTZelda_80223ED0(0);
    grTZelda_80223ED0(1);
    grTZelda_80223ED0(2);
    Ground_801C39C0();
    Ground_801C3BB4();
    Ground_801C4210();
    Ground_801C42AC();
}

void grTZelda_80223EA0(void) {}

void grTZelda_80223EA4(void)
{
    grZakoGenerator_801CAE04(0);
}

bool grTZelda_80223EC8(void)
{
    return false;
}

HSD_GObj* grTZelda_80223ED0(s32 arg0)
{
    HSD_GObj* gobj;
    StageCallbacks* cb;
    Ground* gp;

    cb = &grTZd_803E9638[arg0];
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
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grtzelda.c", 0xC3,
                 arg0);
    }
    return gobj;
}

void grTZelda_80223FB8(HSD_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grTZelda_80223FE4(HSD_GObj* gobj)
{
    return false;
}

void grTZelda_80223FEC(HSD_GObj* gobj) {}

void grTZelda_80223FF0(HSD_GObj* gobj) {}

void grTZelda_80223FF4(HSD_GObj* gobj)
{
    Ground_JObjInline1(gobj);
}

bool grTZelda_80224044(HSD_GObj* gobj)
{
    return false;
}

void grTZelda_8022404C(HSD_GObj* gobj)
{
    lb_800115F4();
    Ground_801C2FE0(gobj);
}

void grTZelda_80224080(HSD_GObj* gobj) {}

void grTZelda_80224084(HSD_GObj* gobj)
{
    Ground_JObjInline1(gobj);
}

bool grTZelda_802240D4(HSD_GObj* gobj)
{
    return false;
}

void grTZelda_802240DC(HSD_GObj* gobj)
{
    Ground_801C2FE0(gobj);
}

void grTZelda_802240FC(HSD_GObj* gobj) {}

lb_UnkAnimStruct* grTZelda_80224100(enum_t arg0)
{
    return NULL;
}

bool grTZelda_80224108(Vec3* arg0, int arg1, HSD_JObj* arg2)
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
