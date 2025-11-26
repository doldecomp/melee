#include <platform.h>

#include "baselib/psstructs.h"
#include "ft/ftdevice.h"
#include "ft/ftlib.h"
#include "gr/granime.h"
#include "gr/grdisplay.h"
#include "gr/grlib.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "gr/types.h"

#include "lb/forward.h"

#include "lb/lb_00F9.h"

#include <dolphin/mtx.h>
#include <dolphin/os/OSError.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>

/* 21F840 */ static void grTMario_8021F840(bool);
/* 21F844 */ static void grTMario_8021F844(void);
/* 21F8B4 */ static void grTmario_UnkStage0_OnLoad(void);
/* 21F8B8 */ static void grTmario_UnkStage0_OnStart(void);
/* 21F8DC */ static bool grTMario_8021F8DC(void);
/* 21F8E4 */ static HSD_GObj* grTMario_8021F8E4(s32);
/* 21F9CC */ static void grTMario_8021F9CC(Ground_GObj*);
/* 21F9F8 */ static bool grTMario_8021F9F8(Ground_GObj*);
/* 21FA00 */ static void grTMario_8021FA00(Ground_GObj*);
/* 21FA04 */ static void grTMario_8021FA04(Ground_GObj*);
/* 21FA08 */ static void lbl_8021FA08(HSD_GObj*);
/* 21FA34 */ static void grTMario_8021FA34(Ground_GObj*);
/* 21FA94 */ static bool grTMario_8021FA94(Ground_GObj*);
/* 21FA9C */ static void grTMario_8021FA9C(Ground_GObj*);
/* 21FAD0 */ static void grTMario_8021FAD0(Ground_GObj*);
/* 21FAD4 */ static void grTMario_8021FAD4(Ground_GObj*);
/* 21FB24 */ static bool grTMario_8021FB24(Ground_GObj*);
/* 21FB2C */ static void grTMario_8021FB2C(Ground_GObj*);
/* 21FB4C */ static void grTMario_8021FB4C(Ground_GObj*);
/* 21FB50 */ static int lbl_8021FB50(s32, HSD_GObj*);
/* 21FBE8 */ static void grTMario_8021FBE8(Vec3*, f32);
/* 21FC50 */ static DynamicsDesc* grTMario_8021FC50(enum_t);
/* 21FC58 */ static bool grTMario_8021FC58(Vec3*, int, HSD_JObj*);

StageCallbacks grTMr_803E8548[] = {
    {
        grTMario_8021F9CC,
        grTMario_8021F9F8,
        grTMario_8021FA00,
        grTMario_8021FA04,
        0,
    },
    {
        grTMario_8021FAD4,
        grTMario_8021FB24,
        grTMario_8021FB2C,
        grTMario_8021FB4C,
        0,
    },
    {
        grTMario_8021FA34,
        grTMario_8021FA94,
        grTMario_8021FA9C,
        grTMario_8021FAD0,
        (1 << 30) | (1 << 31),
    },
    { NULL, NULL, NULL, NULL, 0 },
};

StageData grTMr_803E85A4 = {
    40,
    grTMr_803E8548,
    "/GrTMr.dat",
    grTMario_8021F844,
    grTMario_8021F840,
    grTmario_UnkStage0_OnLoad,
    grTmario_UnkStage0_OnStart,
    grTMario_8021F8DC,
    grTMario_8021FC50,
    grTMario_8021FC58,
    (1 << 0),
    NULL,
    0,
};

void grTMario_8021F840(bool unk) {}

void grTMario_8021F844(void)
{
    stage_info.unk8C.b4 = false;
    stage_info.unk8C.b5 = true;

    grTMario_8021F8E4(0);
    grTMario_8021F8E4(1);
    grTMario_8021F8E4(2);
    Ground_801C39C0();
    Ground_801C3BB4();
    Ground_801C4210();
    Ground_801C42AC();
}

void grTmario_UnkStage0_OnLoad(void) {}

void grTmario_UnkStage0_OnStart(void)
{
    grZakoGenerator_801CAE04(0);
}

bool grTMario_8021F8DC(void)
{
    return false;
}

HSD_GObj* grTMario_8021F8E4(s32 arg0)
{
    HSD_GObj* gobj;
    StageCallbacks* cb;
    Ground* gp;

    cb = &grTMr_803E8548[arg0];
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
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grtmario.c", 0xCD,
                 arg0);
    }
    return gobj;
}

void grTMario_8021F9CC(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grTMario_8021F9F8(Ground_GObj* gobj)
{
    return false;
}

void grTMario_8021FA00(Ground_GObj* gobj) {}

void grTMario_8021FA04(Ground_GObj* gobj) {}

void lbl_8021FA08(HSD_GObj* gobj)
{
    ftCo_800C07F8(gobj, 6, lbl_8021FB50);
}

void grTMario_8021FA34(Ground_GObj* gobj)
{
    Ground_JObjInline1(gobj);
    Ground_801C10B8(gobj, lbl_8021FA08);
}

bool grTMario_8021FA94(Ground_GObj* gobj)
{
    return 0;
}

void grTMario_8021FA9C(Ground_GObj* gobj)
{
    lb_800115F4();
    Ground_801C2FE0(gobj);
}

void grTMario_8021FAD0(Ground_GObj* gobj) {}

void grTMario_8021FAD4(Ground_GObj* gobj)
{
    Ground_JObjInline1(gobj);
}

bool grTMario_8021FB24(Ground_GObj* gobj)
{
    return false;
}

void grTMario_8021FB2C(Ground_GObj* gobj)
{
    Ground_801C2FE0(gobj);
}

void grTMario_8021FB4C(Ground_GObj* gobj) {}

int lbl_8021FB50(s32 unk, HSD_GObj* gobj)
{
    f32 temp_f1;
    f32 temp_f31;
    Vec3 current;
    Vec3 previous;
    f32 unused = -120.0f;

    temp_f31 = unused * Ground_801C0498();
    ftLib_80086644(gobj, &current);
    ftLib_80086684(gobj, &previous);
    if ((current.y < temp_f31) && (previous.y > temp_f31)) {
        temp_f1 = ftLib_80086B80(gobj) / 10.0f;
        current.y = temp_f31;
        grTMario_8021FBE8(&current, temp_f1);
        Ground_801C53EC(0x77A10U);
    }
    return 0;
}

void grTMario_8021FBE8(Vec3* vec, f32 arg8)
{
    HSD_psAppSRT* temp_r3_2;
    HSD_Generator* temp_r3;

    temp_r3 = grLib_801C96F8(0x7530, 0x1E, vec);
    if (temp_r3 != NULL) {
        temp_r3_2 = temp_r3->appsrt;
        temp_r3_2->scale.x *= arg8;
        temp_r3_2->scale.y *= arg8;
        temp_r3_2->scale.z *= arg8;
    }
}

DynamicsDesc* grTMario_8021FC50(enum_t arg0)
{
    return NULL;
}

bool grTMario_8021FC58(Vec3* arg0, int arg1, HSD_JObj* arg2)
{
    return true;
}
