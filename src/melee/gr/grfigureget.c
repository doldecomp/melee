#include "grfigureget.h"

#include <platform.h>

#include "gr/forward.h"

#include "gr/granime.h"
#include "gr/grdisplay.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "gr/types.h"

#include "lb/forward.h"

#include <dolphin/mtx.h>
#include <dolphin/os/OSError.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>

/* 219530 */ static void grFigureGet_80219530(bool);
/* 219534 */ static void grFigureGet_80219534(void);
/* 21959C */ static void grFigureget_UnkStage0_OnLoad(void);
/* 2195A0 */ static void grFigureget_UnkStage0_OnStart(void);
/* 2195C4 */ static bool grFigureGet_802195C4(void);
/* 2195CC */ static HSD_GObj* grFigureGet_802195CC(int);
/* 2196B4 */ static void grFigureGet_802196B4(Ground_GObj*);
/* 2196E0 */ static bool grFigureGet_802196E0(Ground_GObj*);
/* 2196E8 */ static void grFigureGet_802196E8(Ground_GObj*);
/* 2196EC */ static void grFigureGet_802196EC(Ground_GObj*);
/* 2196F0 */ static void grFigureGet_802196F0(Ground_GObj*);
/* 219890 */ static bool grFigureGet_80219890(Ground_GObj*);
/* 219898 */ static void grFigureGet_80219898(Ground_GObj*);
/* 219B0C */ static void grFigureGet_80219B0C(Ground_GObj*);
/* 219C88 */ static DynamicsDesc* grFigureGet_80219C88(enum_t);
/* 219C90 */ static bool grFigureGet_80219C90(Vec3*, int, HSD_JObj*);

static StageCallbacks grFigureGet_803E7D00[2] = {
    { grFigureGet_802196B4, grFigureGet_802196E0, grFigureGet_802196E8,
      grFigureGet_802196EC, 0 },
    { grFigureGet_802196F0, grFigureGet_80219890, grFigureGet_80219898,
      grFigureGet_80219B0C, (1 << 30) | (1 << 31) },
};

StageData grFigureGet_803E7D34 = {
    0x26,
    grFigureGet_803E7D00,
    "/GrNFg.dat",
    grFigureGet_80219534,
    grFigureGet_80219530,
    grFigureget_UnkStage0_OnLoad,
    grFigureget_UnkStage0_OnStart,
    grFigureGet_802195C4,
    grFigureGet_80219C88,
    grFigureGet_80219C90,
    1,
    NULL,
    0,
};

extern UNK_T grFigureGet_804D6AC0;

extern StageInfo stage_info;

void grFigureGet_80219530(bool arg0) {}

void grFigureGet_80219534(void)
{
    grFigureGet_804D6AC0 = Ground_801C49F8();
    stage_info.unk8C.b4 = 0;
    stage_info.unk8C.b5 = 1;
    grFigureGet_802195CC(0);
    grFigureGet_802195CC(1);
    Ground_801C39C0();
    Ground_801C3BB4();
}

void grFigureget_UnkStage0_OnLoad(void) {}

void grFigureget_UnkStage0_OnStart(void)
{
    grZakoGenerator_801CAE04(0);
}

bool grFigureGet_802195C4(void)
{
    return false;
}

HSD_GObj* grFigureGet_802195CC(int gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grFigureGet_803E7D00[gobj_id];

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
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grfigureget.c", 187,
                 gobj_id);
    }

    return gobj;
}

void grFigureGet_802196B4(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grFigureGet_802196E0(Ground_GObj* gobj)
{
    return false;
}

void grFigureGet_802196E8(Ground_GObj* gobj) {}

void grFigureGet_802196EC(Ground_GObj* gobj) {}

/// #grFigureGet_802196F0

bool grFigureGet_80219890(Ground_GObj* gobj)
{
    return false;
}

/// #grFigureGet_80219898

void grFigureGet_80219B0C(Ground_GObj* gobj) {}

/// #fn_80219B10

void grFigureGet_80219C34(HSD_GObj* gobj)
{
    Ground* gp;
    if (gobj == NULL) {
        return;
    }
    gp = GET_GROUND(gobj);
    gp->gv.figureget.xC += 1;
}

int grFigureGet_80219C50(HSD_GObj* gobj)
{
    Ground* gp;
    if (gobj == NULL) {
        return 0;
    }
    gp = GET_GROUND(gobj);
    if (gp->gv.figureget.x8 + gp->gv.figureget.xC >= 3) {
        return 1;
    }
    return 0;
}

DynamicsDesc* grFigureGet_80219C88(enum_t arg0)
{
    return NULL;
}

bool grFigureGet_80219C90(Vec3* arg0, int arg1, HSD_JObj* arg2)
{
    return true;
}
