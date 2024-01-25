#include <platform.h>
#include "lb/forward.h"
#include <baselib/forward.h>

#include "gr/grtseak.h"

#include "gr/granime.h"
#include "gr/grdisplay.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "gr/types.h"
#include "lb/lb_00F9.h"

#include <dolphin/mtx/types.h>
#include <dolphin/os.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>

void grTSeak_80223864(int);                   /* static */
void grTSeak_80223868(void);                  /* static */
void grTSeak_802238D8(void);                  /* static */
void grTSeak_802238DC(void);                  /* static */
bool grTSeak_80223900(void);                  /* static */
HSD_GObj* grTSeak_80223908(s32);              /* static */
void grTSeak_802239F0(HSD_GObj*);             /* static */
bool grTSeak_80223A1C(HSD_GObj*);             /* static */
void grTSeak_80223A24(HSD_GObj*);             /* static */
void grTSeak_80223A28(HSD_GObj*);             /* static */
void grTSeak_80223A2C(HSD_GObj*);             /* static */
bool grTSeak_80223A7C(HSD_GObj*);             /* static */
void grTSeak_80223A84(HSD_GObj*);             /* static */
void grTSeak_80223AB8(HSD_GObj*);             /* static */
void grTSeak_80223ABC(HSD_GObj*);             /* static */
bool grTSeak_80223B0C(HSD_GObj*);             /* static */
void grTSeak_80223B14(HSD_GObj*);             /* static */
void grTSeak_80223B34(HSD_GObj*);             /* static */
lb_UnkAnimStruct* grTSeak_80223B38(enum_t);   /* static */
bool grTSeak_80223B40(Vec3*, int, HSD_JObj*); /* static */

static StageCallbacks grTSk_803E94B8[4] = {
    { grTSeak_802239F0, grTSeak_80223A1C, grTSeak_80223A24, grTSeak_80223A28,
      0 },
    { grTSeak_80223ABC, grTSeak_80223B0C, grTSeak_80223B14, grTSeak_80223B34,
      0 },
    { grTSeak_80223A2C, grTSeak_80223A7C, grTSeak_80223A84, grTSeak_80223AB8,
      (1 << 31) | (1 << 30) },
    { NULL, NULL, NULL, NULL, 0 }
};

StageData grTSk_803E9514 = {
    60,
    grTSk_803E94B8,
    "/GrTSk.dat",
    grTSeak_80223868,
    grTSeak_80223864,
    grTSeak_802238D8,
    grTSeak_802238DC,
    grTSeak_80223900,
    grTSeak_80223B38,
    grTSeak_80223B40,
    1,
};

void grTSeak_80223864(int unk0) {}

void grTSeak_80223868(void)
{
    stage_info.unk8C.b4 = false;
    stage_info.unk8C.b5 = true;

    grTSeak_80223908(0);
    grTSeak_80223908(1);
    grTSeak_80223908(2);
    Ground_801C39C0();
    Ground_801C3BB4();
    Ground_801C4210();
    Ground_801C42AC();
}

void grTSeak_802238D8(void) {}

void grTSeak_802238DC(void)
{
    grZakoGenerator_801CAE04(0);
}

bool grTSeak_80223900(void)
{
    return false;
}

HSD_GObj* grTSeak_80223908(s32 arg0)
{
    HSD_GObj* gobj;
    StageCallbacks* cb;
    Ground* gp;

    cb = &grTSk_803E94B8[arg0];
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
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grtseak.c", 0xC3, arg0);
    }
    return gobj;
}

void grTSeak_802239F0(HSD_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grTSeak_80223A1C(HSD_GObj* gobj)
{
    return false;
}

void grTSeak_80223A24(HSD_GObj* gobj) {}

void grTSeak_80223A28(HSD_GObj* gobj) {}

void grTSeak_80223A2C(HSD_GObj* gobj)
{
    Ground_JObjInline1(gobj);
}

bool grTSeak_80223A7C(HSD_GObj* gobj)
{
    return false;
}

void grTSeak_80223A84(HSD_GObj* gobj)
{
    lb_800115F4();
    Ground_801C2FE0(gobj);
}

void grTSeak_80223AB8(HSD_GObj* gobj) {}

void grTSeak_80223ABC(HSD_GObj* gobj)
{
    Ground_JObjInline1(gobj);
}

bool grTSeak_80223B0C(HSD_GObj* gobj)
{
    return false;
}

void grTSeak_80223B14(HSD_GObj* gobj)
{
    Ground_801C2FE0(gobj);
}

void grTSeak_80223B34(HSD_GObj* gobj) {}

lb_UnkAnimStruct* grTSeak_80223B38(enum_t arg0)
{
    return NULL;
}

bool grTSeak_80223B40(Vec3* arg0, int arg1, HSD_JObj* arg2)
{
    return true;
}
