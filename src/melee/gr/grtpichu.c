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

/* 222B98 */ static void grTPichu_80222B98(bool);
/* 222B9C */ static void grTPichu_80222B9C(void);
/* 222C0C */ static void grTpichu_UnkStage0_OnLoad(void);
/* 222C10 */ static void grTpichu_UnkStage0_OnStart(void);
/* 222C34 */ static bool grTPichu_80222C34(void);
/* 222C3C */ static HSD_GObj* grTPichu_80222C3C(int gobj_id);
/* 222D24 */ static void grTPichu_80222D24(Ground_GObj* gobj);
/* 222D50 */ static bool grTPichu_80222D50(Ground_GObj*);
/* 222D58 */ static void grTPichu_80222D58(Ground_GObj*);
/* 222D5C */ static void grTPichu_80222D5C(Ground_GObj*);
/* 222D60 */ static void grTPichu_80222D60(Ground_GObj* gobj);
/* 222DB0 */ static bool grTPichu_80222DB0(Ground_GObj*);
/* 222DB8 */ static void grTPichu_80222DB8(Ground_GObj* gobj);
/* 222DEC */ static void grTPichu_80222DEC(Ground_GObj*);
/* 222DF0 */ static void grTPichu_80222DF0(Ground_GObj* gobj);
/* 222E40 */ static bool grTPichu_80222E40(Ground_GObj*);
/* 222E48 */ static void grTPichu_80222E48(Ground_GObj*);
/* 222E68 */ static void grTPichu_80222E68(Ground_GObj*);
/* 222E6C */ static DynamicsDesc* grTPichu_80222E6C(enum_t);
/* 222E74 */ static bool grTPichu_80222E74(Vec3*, int, HSD_JObj*);

static StageCallbacks grTPc_803E91B0[] = {
    {
        grTPichu_80222D24,
        grTPichu_80222D50,
        grTPichu_80222D58,
        grTPichu_80222D5C,
        0,
    },
    {
        grTPichu_80222DF0,
        grTPichu_80222E40,
        grTPichu_80222E48,
        grTPichu_80222E68,
        0,
    },
    {
        grTPichu_80222D60,
        grTPichu_80222DB0,
        grTPichu_80222DB8,
        grTPichu_80222DEC,
        (1 << 30) | (1 << 31),
    },
    { NULL, NULL, NULL, NULL, 0 },
};

StageData grTPc_803E920C = {
    (1 << 3) | (1 << 4) | (1 << 5),
    grTPc_803E91B0,
    "/GrTPc.dat",
    grTPichu_80222B9C,
    grTPichu_80222B98,
    grTpichu_UnkStage0_OnLoad,
    grTpichu_UnkStage0_OnStart,
    grTPichu_80222C34,
    grTPichu_80222E6C,
    grTPichu_80222E74,
    0,
    NULL,
    0,
};

extern StageInfo stage_info;

static void grTPichu_80222B98(bool arg0) {}

static void grTPichu_80222B9C(void)
{
    stage_info.unk8C.b4 = false;
    stage_info.unk8C.b5 = true;
    grTPichu_80222C3C(0);
    grTPichu_80222C3C(1);
    grTPichu_80222C3C(2);
    Ground_801C39C0();
    Ground_801C3BB4();
    Ground_801C4210();
    Ground_801C42AC();
}

static void grTpichu_UnkStage0_OnLoad(void) {}

static void grTpichu_UnkStage0_OnStart(void)
{
    grZakoGenerator_801CAE04(0);
}

static bool grTPichu_80222C34(void)
{
    return false;
}

static HSD_GObj* grTPichu_80222C3C(int gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grTPc_803E91B0[gobj_id];

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
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grtpichu.c", 0xc2,
                 gobj_id);
    }

    return gobj;
}

static void grTPichu_80222D24(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    grAnime_801C8138(gobj, gp->map_id, 0);
}

static bool grTPichu_80222D50(Ground_GObj* arg0)
{
    return false;
}

static void grTPichu_80222D58(Ground_GObj* arg0) {}

static void grTPichu_80222D5C(Ground_GObj* arg0) {}

static void grTPichu_80222D60(Ground_GObj* gobj)
{
    u8 _[4];

    Ground* gp = GET_GROUND(gobj);
    Ground_801C2ED0(gobj->hsd_obj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

static bool grTPichu_80222DB0(Ground_GObj* arg0)
{
    return false;
}

static void grTPichu_80222DB8(Ground_GObj* gobj)
{
    lb_800115F4();
    Ground_801C2FE0(gobj);
}

static void grTPichu_80222DEC(Ground_GObj* arg0) {}

static void grTPichu_80222DF0(Ground_GObj* gobj)
{
    u8 _[4];

    Ground* gp = GET_GROUND(gobj);
    Ground_801C2ED0(gobj->hsd_obj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

static bool grTPichu_80222E40(Ground_GObj* arg0)
{
    return false;
}

static void grTPichu_80222E48(Ground_GObj* arg0)
{
    Ground_801C2FE0(arg0);
}

static void grTPichu_80222E68(Ground_GObj* arg0) {}

static DynamicsDesc* grTPichu_80222E6C(enum_t arg0)
{
    return NULL;
}

static bool grTPichu_80222E74(Vec3* arg0, int arg1, HSD_JObj* arg2)
{
    return true;
}
