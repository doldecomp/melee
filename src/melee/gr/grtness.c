#include <platform.h>

#include "lb/forward.h"

#include "gr/granime.h"
#include "gr/grdisplay.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/types.h"
#include "lb/lb_00F9.h"

#include <dolphin/mtx.h>
#include <dolphin/os/OSError.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>

/* 2225D0 */ static void grTNess_802225D0(int);
/* 2225D4 */ static void grTNess_802225D4(void);
/* 222644 */ static void grTNess_80222644(void);
/* 222648 */ static void grTNess_80222648(void);
/* 22266C */ static bool grTNess_8022266C(void);
/* 222674 */ static HSD_GObj* grTNess_80222674(int param_1);
/* 22275C */ static void grTNess_8022275C(HSD_GObj* gobj);
/* 222788 */ static bool grTNess_80222788(HSD_GObj*);
/* 222790 */ static void grTNess_80222790(HSD_GObj*);
/* 222794 */ static void grTNess_80222794(HSD_GObj*);
/* 222798 */ static void grTNess_80222798(HSD_GObj* gobj);
/* 2227E8 */ static bool grTNess_802227E8(HSD_GObj*);
/* 2227F0 */ static void grTNess_802227F0(HSD_GObj* gobj);
/* 222824 */ static void grTNess_80222824(HSD_GObj*);
/* 222828 */ static void grTNess_80222828(HSD_GObj* gobj);
/* 222878 */ static bool grTNess_80222878(HSD_GObj*);
/* 222880 */ static void grTNess_80222880(HSD_GObj* gobj);
/* 2228A0 */ static void grTNess_802228A0(HSD_GObj*);
/* 2228A4 */ static DynamicsDesc* grTNess_802228A4(enum_t);
/* 2228AC */ static bool grTNess_802228AC(Vec3*, int, HSD_JObj*);

static StageCallbacks grTNs_803E9030[] = {
    {
        grTNess_8022275C,
        grTNess_80222788,
        grTNess_80222790,
        grTNess_80222794,
    },
    {
        grTNess_80222828,
        grTNess_80222878,
        grTNess_80222880,
        grTNess_802228A0,
    },
    {
        grTNess_80222798,
        grTNess_802227E8,
        grTNess_802227F0,
        grTNess_80222824,
        (1 << 30) | (1 << 31),
    },
    { 0 },
};

StageData grTNs_803E908C = {
    0x00000036,       grTNs_803E9030,   "/GrTNs.dat",     grTNess_802225D4,
    grTNess_802225D0, grTNess_80222644, grTNess_80222648, grTNess_8022266C,
    grTNess_802228A4, grTNess_802228AC, 0x00000001,
};

static void grTNess_802225D0(int arg0)
{
    return;
}

static void grTNess_802225D4(void)
{
    stage_info.unk8C.b4 = 0;
    stage_info.unk8C.b5 = 1;
    grTNess_80222674(0);
    grTNess_80222674(1);
    grTNess_80222674(2);
    Ground_801C39C0();
    Ground_801C3BB4();
    Ground_801C4210();
    Ground_801C42AC();
}

static void grTNess_80222644(void)
{
    return;
}

static void grTNess_80222648(void)
{
    grZakoGenerator_801CAE04(false);
}

static bool grTNess_8022266C(void)
{
    return false;
}

static HSD_GObj* grTNess_80222674(int id)
{
    HSD_GObj* gobj;
    Ground* gp;
    StageCallbacks* cb = &grTNs_803E9030[id];
    gobj = Ground_801C14D0(id);
    if (gobj != NULL) {
        gp = gobj->user_data;
        gp->x8_callback = NULL;
        gp->xC_callback = NULL;
        GObj_SetupGXLink(gobj, grDisplay_801C5DB0, 3, 0);
        if (cb->callback3 != 0U) {
            gp->x1C_callback = cb->callback3;
        }
        if (cb->callback0 != 0U) {
            cb->callback0(gobj);
        }
        if (cb->callback2 != 0U) {
            HSD_GObjProc_8038FD54(gobj, cb->callback2, 4);
        }
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grtness.c", 0xC3, id);
    }
    return gobj;
}

static void grTNess_8022275C(HSD_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    grAnime_801C8138(gobj, gp->map_id, 0);
}

static bool grTNess_80222788(HSD_GObj* arg0)
{
    return false;
}

static void grTNess_80222790(HSD_GObj* arg0)
{
    return;
}

static void grTNess_80222794(HSD_GObj* arg0)
{
    return;
}

static void grTNess_80222798(HSD_GObj* gobj)
{
    u8 _[8];

    Ground* gp = gobj->user_data;
    Ground_801C2ED0(gobj->hsd_obj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

static bool grTNess_802227E8(HSD_GObj* arg0)
{
    return false;
}

static void grTNess_802227F0(HSD_GObj* gobj)
{
    lb_800115F4();
    Ground_801C2FE0(gobj);
}

static void grTNess_80222824(HSD_GObj* arg0)
{
    return;
}

static void grTNess_80222828(HSD_GObj* gobj)
{
    u8 _[8];

    Ground* gp = gobj->user_data;
    Ground_801C2ED0(gobj->hsd_obj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

static bool grTNess_80222878(HSD_GObj* arg0)
{
    return false;
}

static void grTNess_80222880(HSD_GObj* gobj)
{
    Ground_801C2FE0(gobj);
}

static void grTNess_802228A0(HSD_GObj* arg0)
{
    return;
}

static DynamicsDesc* grTNess_802228A4(enum_t arg0)
{
    return NULL;
}

static bool grTNess_802228AC(Vec3* arg0, int arg1, HSD_JObj* arg2)
{
    return true;
}
