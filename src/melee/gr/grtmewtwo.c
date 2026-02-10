#include "grtmewtwo.h"

#include <platform.h>

#include "gr/granime.h"
#include "gr/grdisplay.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "gr/types.h"

#include "lb/forward.h"

#include "lb/lb_00F9.h"

#include "mp/forward.h"

#include "mp/mplib.h"

#include <dolphin/mtx.h>
#include <dolphin/os/OSError.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>

typedef struct grTMewtwo_UnkStruct {
    DynamicsDesc* x0;
    DynamicsDesc* x4;
    DynamicsDesc* xC;
    DynamicsDesc* x8;
    DynamicsDesc* x10;
    DynamicsDesc* x14;
    DynamicsDesc* x1C;
    DynamicsDesc* x18;
} grTMewtwo_UnkStruct;

/* 2221D8 */ static void grTMewtwo_802221D8(bool arg0);
/* 2221DC */ static void grTMewtwo_802221DC(void);
/* 222254 */ static void grTmewtwo_UnkStage0_OnLoad(void);
/* 222258 */ static void grTmewtwo_UnkStage0_OnStart(void);
/* 22227C */ static bool grTMewtwo_8022227C(void);
/* 222284 */ static Ground_GObj* grTMewtwo_80222284(int index);
/* 22236C */ static void grTMewtwo_8022236C(Ground_GObj* gobj);
/* 222398 */ static bool grTMewtwo_80222398(Ground_GObj* gobj);
/* 2223A0 */ static void grTMewtwo_802223A0(Ground_GObj* gobj);
/* 2223A4 */ static void grTMewtwo_802223A4(Ground_GObj* gobj);
/* 2223A8 */ static void grTMewtwo_802223A8(Ground_GObj* gobj);
/* 2223F8 */ static bool grTMewtwo_802223F8(Ground_GObj* gobj);
/* 222400 */ static void grTMewtwo_80222400(Ground_GObj* gobj);
/* 222434 */ static void grTMewtwo_80222434(Ground_GObj* gobj);
/* 222438 */ static void grTMewtwo_80222438(Ground_GObj* gobj);
/* 222488 */ static bool grTMewtwo_80222488(Ground_GObj* gobj);
/* 222490 */ static void grTMewtwo_80222490(Ground_GObj* gobj);
/* 2224B0 */ static void grTMewtwo_802224B0(Ground_GObj* gobj);
/* 2224B4 */ static DynamicsDesc* grTMewtwo_802224B4(enum_t arg0);
/* 2225C8 */ static bool grTMewtwo_802225C8(Vec3* arg0, int arg1,
                                            HSD_JObj* arg2);
/* 3E8FC0 */ static void grTMewtwo_803E8FC0(Ground_GObj* gobj);
/* 4D6B08 */ static grTMewtwo_UnkStruct* grTMewtwo_804D6B08;

static StageCallbacks grTMewtwo_803E8F70[4] = {
    {
        grTMewtwo_8022236C,
        grTMewtwo_80222398,
        grTMewtwo_802223A0,
        grTMewtwo_802223A4,
        0,
    },
    {
        grTMewtwo_80222438,
        grTMewtwo_80222488,
        grTMewtwo_80222490,
        grTMewtwo_802224B0,
        0,
    },
    {
        grTMewtwo_802223A8,
        grTMewtwo_802223F8,
        grTMewtwo_80222400,
        grTMewtwo_80222434,
        (1 << 30) | (1 << 31),
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
        0,
    },
};

StageData grTMewtwo_803E8FCC = {
    (1 << 0) | (1 << 2) | (1 << 4) | (1 << 5),
    grTMewtwo_803E8F70,
    "/GrTMt.dat",
    grTMewtwo_802221DC,
    grTMewtwo_802221D8,
    grTmewtwo_UnkStage0_OnLoad,
    grTmewtwo_UnkStage0_OnStart,
    grTMewtwo_8022227C,
    grTMewtwo_802224B4,
    grTMewtwo_802225C8,
    (1 << 0),
    NULL,
};

void grTMewtwo_802221D8(bool arg0) {}

void grTMewtwo_802221DC(void)
{
    grTMewtwo_804D6B08 = Ground_801C49F8();
    stage_info.unk8C.b4 = false;
    stage_info.unk8C.b5 = true;
    grTMewtwo_80222284(0);
    grTMewtwo_80222284(1);
    grTMewtwo_80222284(2);
    Ground_801C39C0();
    Ground_801C3BB4();
    Ground_801C4210();
    Ground_801C42AC();
}

void grTmewtwo_UnkStage0_OnLoad(void) {}

void grTmewtwo_UnkStage0_OnStart(void)
{
    grZakoGenerator_801CAE04(0);
}

bool grTMewtwo_8022227C(void)
{
    return false;
}

Ground_GObj* grTMewtwo_80222284(int index)
{
    /// @@todo Can't move below @c callbacks.
    HSD_GObj* gobj;

    StageCallbacks* callbacks = &grTMewtwo_803E8F70[index];
    gobj = Ground_801C14D0(index);
    if (gobj != NULL) {
        Ground* gp = GET_GROUND(gobj);
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
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grtmewtwo.c", 201,
                 index);
    }
    return gobj;
}

void grTMewtwo_8022236C(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grTMewtwo_80222398(Ground_GObj* gobj)
{
    return false;
}

void grTMewtwo_802223A0(Ground_GObj* gobj) {}

void grTMewtwo_802223A4(Ground_GObj* gobj) {}

void grTMewtwo_802223A8(Ground_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Ground* gp = GET_GROUND(gobj);
    Ground_801C2ED0(jobj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grTMewtwo_802223F8(Ground_GObj* gobj)
{
    return false;
}

void grTMewtwo_80222400(Ground_GObj* gobj)
{
    lb_800115F4();
    Ground_801C2FE0(gobj);
}

void grTMewtwo_80222434(Ground_GObj* gobj) {}

void grTMewtwo_80222438(Ground_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Ground* gp = GET_GROUND(gobj);
    Ground_801C2ED0(jobj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grTMewtwo_80222488(Ground_GObj* gobj)
{
    return false;
}

void grTMewtwo_80222490(Ground_GObj* gobj)
{
    Ground_801C2FE0(gobj);
}

void grTMewtwo_802224B0(Ground_GObj* gobj) {}

static inline DynamicsDesc* inlineA0(int arg0)
{
    int temp = mpLineGetKind(arg0);
    if (temp == CollLine_Floor) {
        return grTMewtwo_804D6B08->x0;
    } else if (temp == CollLine_Ceiling) {
        return grTMewtwo_804D6B08->x4;
    } else if (temp == CollLine_RightWall) {
        return grTMewtwo_804D6B08->x8;
    } else if (temp == CollLine_LeftWall) {
        return grTMewtwo_804D6B08->xC;
    } else {
        return NULL;
    }
}

static inline DynamicsDesc* inlineA1(int arg0)
{
    int temp = mpLineGetKind(arg0);
    if (temp == CollLine_Floor) {
        return grTMewtwo_804D6B08->x10;
    } else if (temp == CollLine_Ceiling) {
        return grTMewtwo_804D6B08->x14;
    } else if (temp == CollLine_RightWall) {
        return grTMewtwo_804D6B08->x18;
    } else if (temp == CollLine_LeftWall) {
        return grTMewtwo_804D6B08->x1C;
    } else {
        return NULL;
    }
}

DynamicsDesc* grTMewtwo_802224B4(enum_t arg0)
{
    if (arg0 != -1) {
        int temp = mpJointFromLine(arg0);
        if (temp != -1) {
            if (temp == 0) {
                return inlineA0(arg0);
            } else if (temp == 1) {
                return inlineA1(arg0);
            }
        }
    }
    return NULL;
}

bool grTMewtwo_802225C8(Vec3* arg0, int arg1, HSD_JObj* arg2)
{
    return true;
}
