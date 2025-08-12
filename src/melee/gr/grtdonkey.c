#include "gr/grtdonkey.h"

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

static void grTDonkey_80220228(bool);
static void grTDonkey_8022022C(void);
static void grTdonkey_UnkStage0_OnLoad(void);
static void grTdonkey_UnkStage0_OnStart(void);
static bool grTDonkey_802202C4(void);
static HSD_GObj* grTDonkey_802202CC(int gobj_id);
static void grTDonkey_802203B4(Ground_GObj* gobj);
static bool grTDonkey_802203E0(Ground_GObj*);
static void grTDonkey_802203E8(Ground_GObj*);
static void grTDonkey_802203EC(Ground_GObj*);
static void grTDonkey_802203F0(Ground_GObj* gobj);
static bool grTDonkey_80220440(Ground_GObj*);
static void grTDonkey_80220448(Ground_GObj* gobj);
static void grTDonkey_8022047C(Ground_GObj*);
static void grTDonkey_80220480(Ground_GObj* gobj);
static bool grTDonkey_802204D0(Ground_GObj*);
static void grTDonkey_802204D8(Ground_GObj*);
static void grTDonkey_802204F8(Ground_GObj*);
static DynamicsDesc* grTDonkey_802204FC(enum_t);
static bool grTDonkey_80220504(Vec3*, int, HSD_JObj*);

static StageCallbacks grTDk_803E8790[] = {
    { grTDonkey_802203B4, grTDonkey_802203E0, grTDonkey_802203E8,
      grTDonkey_802203EC, 0 },
    { grTDonkey_80220480, grTDonkey_802204D0, grTDonkey_802204D8,
      grTDonkey_802204F8, 0 },
    { grTDonkey_802203F0, grTDonkey_80220440, grTDonkey_80220448,
      grTDonkey_8022047C, (1 << 30) | (1 << 31) },
    { NULL, NULL, NULL, NULL, 0 },
};

StageData grTDk_803E87EC = {
    43,
    grTDk_803E8790,
    "/GrTDk.dat",
    grTDonkey_8022022C,
    grTDonkey_80220228,
    grTdonkey_UnkStage0_OnLoad,
    grTdonkey_UnkStage0_OnStart,
    grTDonkey_802202C4,
    grTDonkey_802204FC,
    grTDonkey_80220504,
    (1 << 0),
    NULL,
    0,
};

extern StageInfo stage_info;

static void grTDonkey_80220228(bool arg0) {}

static void grTDonkey_8022022C(void)
{
    stage_info.unk8C.b4 = 0;
    stage_info.unk8C.b5 = 1;
    grTDonkey_802202CC(0);
    grTDonkey_802202CC(1);
    grTDonkey_802202CC(2);
    Ground_801C39C0();
    Ground_801C3BB4();
    Ground_801C4210();
    Ground_801C42AC();
}

static void grTdonkey_UnkStage0_OnLoad(void) {}

static void grTdonkey_UnkStage0_OnStart(void)
{
    grZakoGenerator_801CAE04(0);
}

static bool grTDonkey_802202C4(void)
{
    return false;
}

static HSD_GObj* grTDonkey_802202CC(int gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grTDk_803E8790[gobj_id];

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
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grtdonkey.c", 0xc3,
                 gobj_id);
    }

    return gobj;
}
static void grTDonkey_802203B4(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    grAnime_801C8138(gobj, gp->map_id, 0);
}

static bool grTDonkey_802203E0(Ground_GObj* arg0)
{
    return false;
}

static void grTDonkey_802203E8(Ground_GObj* arg0) {}

static void grTDonkey_802203EC(Ground_GObj* arg0) {}

static void grTDonkey_802203F0(Ground_GObj* gobj)
{
    u8 _[8];

    Ground* gp = GET_GROUND(gobj);
    Ground_801C2ED0(gobj->hsd_obj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, false);
}

static bool grTDonkey_80220440(Ground_GObj* arg0)
{
    return false;
}

static void grTDonkey_80220448(Ground_GObj* gobj)
{
    lb_800115F4();
    Ground_801C2FE0(gobj);
}

static void grTDonkey_8022047C(Ground_GObj* arg0) {}

static void grTDonkey_80220480(Ground_GObj* gobj)
{
    u8 _[8];

    Ground* gp = GET_GROUND(gobj);
    Ground_801C2ED0(gobj->hsd_obj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, false);
}

static bool grTDonkey_802204D0(Ground_GObj* arg0)
{
    return false;
}

static void grTDonkey_802204D8(Ground_GObj* arg0)
{
    Ground_801C2FE0(arg0);
}

static void grTDonkey_802204F8(Ground_GObj* arg0) {}

static DynamicsDesc* grTDonkey_802204FC(enum_t arg0)
{
    return NULL;
}

static bool grTDonkey_80220504(Vec3* arg0, int arg1, HSD_JObj* arg2)
{
    return true;
}
