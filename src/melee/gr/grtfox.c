#include "gr/grtfox.h"

#include <placeholder.h>
#include <platform.h>

#include "gr/granime.h"
#include "gr/grdisplay.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "gr/types.h"

#include "lb/forward.h"

#include "lb/lb_00F9.h"
#include "mp/mplib.h"

#include <baselib/forward.h>

#include <dolphin/mtx.h>
#include <dolphin/os/OSError.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>

void grTFox_80220B80(bool);                  /* static */
void grTFox_80220B84(void);                  /* static */
void grTfox_UnkStage0_OnLoad(void);          /* static */
void grTfox_UnkStage0_OnStart(void);         /* static */
bool grTFox_80220C24(void);                  /* static */
HSD_GObj* grTFox_80220C2C(s32);              /* static */
void grTFox_80220D14(Ground_GObj*);          /* static */
bool grTFox_80220D40(Ground_GObj*);          /* static */
void grTFox_80220D48(Ground_GObj*);          /* static */
void grTFox_80220D4C(Ground_GObj*);          /* static */
void grTFox_80220D50(Ground_GObj*);          /* static */
bool grTFox_80220DA0(Ground_GObj*);          /* static */
void grTFox_80220DA8(Ground_GObj*);          /* static */
void grTFox_80220DDC(Ground_GObj*);          /* static */
void grTFox_80220DE0(Ground_GObj*);          /* static */
bool grTFox_80220E30(Ground_GObj*);          /* static */
void grTFox_80220E38(Ground_GObj*);          /* static */
void grTFox_80220E58(Ground_GObj*);          /* static */
DynamicsDesc* grTFox_80220E5C(enum_t);       /* static */
bool grTFox_80220F08(Vec3*, int, HSD_JObj*); /* static */

typedef struct grTFox_UnkStruct {
    UNK_T unk0;
    UNK_T unk4;
    UNK_T unk8;
    UNK_T unkC;
} grTFox_UnkStruct;

grTFox_UnkStruct* grTFx_804D6B00;

static StageCallbacks grTFx_803E89D8[4] = {
    { grTFox_80220D14, grTFox_80220D40, grTFox_80220D48, grTFox_80220D4C, 0 },
    { grTFox_80220DE0, grTFox_80220E30, grTFox_80220E38, grTFox_80220E58, 0 },
    { grTFox_80220D50, grTFox_80220DA0, grTFox_80220DA8, grTFox_80220DDC,
      (1 << 31) | (1 << 30) },
    { NULL, NULL, NULL, NULL, 0 }
};

StageData grTFx_803E8A34 = {
    46,
    grTFx_803E89D8,
    "/GrTFx.dat",
    grTFox_80220B84,
    grTFox_80220B80,
    grTfox_UnkStage0_OnLoad,
    grTfox_UnkStage0_OnStart,
    grTFox_80220C24,
    grTFox_80220E5C,
    grTFox_80220F08,
    1,
};

void grTFox_80220B80(bool unk) {}

void grTFox_80220B84(void)
{
    grTFx_804D6B00 = Ground_801C49F8();
    stage_info.unk8C.b4 = false;
    stage_info.unk8C.b5 = true;

    grTFox_80220C2C(0);
    grTFox_80220C2C(1);
    grTFox_80220C2C(2);
    Ground_801C39C0();
    Ground_801C3BB4();
    Ground_801C4210();
    Ground_801C42AC();
}

void grTfox_UnkStage0_OnLoad(void) {}

void grTfox_UnkStage0_OnStart(void)
{
    grZakoGenerator_801CAE04(0);
}

bool grTFox_80220C24(void)
{
    return false;
}

HSD_GObj* grTFox_80220C2C(s32 arg0)
{
    HSD_GObj* gobj;
    StageCallbacks* cb;
    Ground* gp;

    cb = &grTFx_803E89D8[arg0];
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
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grtfox.c", 0xCB, arg0);
    }
    return gobj;
}

void grTFox_80220D14(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grTFox_80220D40(Ground_GObj* gobj)
{
    return false;
}

void grTFox_80220D48(Ground_GObj* gobj) {}

void grTFox_80220D4C(Ground_GObj* gobj) {}

void grTFox_80220D50(Ground_GObj* gobj)
{
    Ground_JObjInline1(gobj);
}

bool grTFox_80220DA0(Ground_GObj* gobj)
{
    return false;
}

void grTFox_80220DA8(Ground_GObj* gobj)
{
    lb_800115F4();
    Ground_801C2FE0(gobj);
}

void grTFox_80220DDC(Ground_GObj* gobj) {}

void grTFox_80220DE0(Ground_GObj* gobj)
{
    Ground_JObjInline1(gobj);
}

bool grTFox_80220E30(Ground_GObj* gobj)
{
    return false;
}

void grTFox_80220E38(Ground_GObj* gobj)
{
    Ground_801C2FE0(gobj);
}

void grTFox_80220E58(Ground_GObj* gobj) {}

DynamicsDesc* grTFox_80220E5C(enum_t arg0)
{
    if (arg0 != -1) {
        enum_t i = mpLib_80056B6C(arg0);
        if (i != -1 && i == 1) {
            i = mpLib_80054C6C(arg0);
            if (i == (1 << 0)) {
                return grTFx_804D6B00->unk0;
            }
            if (i == (1 << 1)) {
                return grTFx_804D6B00->unk4;
            }
            if (i == (1 << 2)) {
                return grTFx_804D6B00->unk8;
            }
            if (i == (1 << 3)) {
                return grTFx_804D6B00->unkC;
            }
            return NULL;
        }
    }
    return NULL;
}

bool grTFox_80220F08(Vec3* arg0, int arg1, HSD_JObj* arg2)
{
    return true;
}
