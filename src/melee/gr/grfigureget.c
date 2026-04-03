#include "grfigureget.h"

#include <platform.h>

#include "baselib/forward.h"
#include "gr/forward.h"

#include "gr/granime.h"
#include "gr/grdisplay.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "gr/types.h"

#include "it/forward.h"

#include "it/inlines.h"
#include "it/items/itcoin.h"
#include "it/types.h"

#include "lb/forward.h"

#include "lb/types.h"

#include "mp/forward.h"

#include <dolphin/mtx.h>
#include <dolphin/os/OSError.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>

/* 219530 */ static void grFigureGet_OnDemoInit(int);
/* 219534 */ static void grFigureGet_OnInit(void);
/* 21959C */ static void grFigureGet_OnLoad(void);
/* 2195A0 */ static void grFigureGet_OnStart(void);
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
/* 219C88 */ static DynamicsDesc* grFigureGet_OnTouchLine(enum_t);
/* 219C90 */ static bool grFigureGet_OnCheckShadowRender(Vec3*, int,
                                                         HSD_JObj*);

static StageCallbacks grFigureGet_803E7D00[2] = {
    { grFigureGet_802196B4, grFigureGet_802196E0, grFigureGet_802196E8,
      grFigureGet_802196EC, 0 },
    { grFigureGet_802196F0, grFigureGet_80219890, grFigureGet_80219898,
      grFigureGet_80219B0C, (1 << 30) | (1 << 31) },
};

StageData grFigureGet_803E7D34 = {
    FIGUREGET,
    grFigureGet_803E7D00,
    "/GrNFg.dat",
    grFigureGet_OnInit,
    grFigureGet_OnDemoInit,
    grFigureGet_OnLoad,
    grFigureGet_OnStart,
    grFigureGet_802195C4,
    grFigureGet_OnTouchLine,
    grFigureGet_OnCheckShadowRender,
    1,
    NULL,
    0,
};

extern UNK_T grFigureGet_804D6AC0;

extern StageInfo stage_info;

void grFigureGet_OnDemoInit(int unused) {}

void grFigureGet_OnInit(void)
{
    grFigureGet_804D6AC0 = Ground_801C49F8();
    stage_info.unk8C.b4 = 0;
    stage_info.unk8C.b5 = 1;
    grFigureGet_802195CC(0);
    grFigureGet_802195CC(1);
    Ground_801C39C0();
    Ground_801C3BB4();
}

void grFigureGet_OnLoad(void) {}

void grFigureGet_OnStart(void)
{
    grZakoGenerator_801CAE04(NULL);
}

bool grFigureGet_802195C4(void)
{
    return false;
}

HSD_GObj* grFigureGet_802195CC(int gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grFigureGet_803E7D00[gobj_id];

    gobj = Ground_GetStageGObj(gobj_id);

    if (gobj != NULL) {
        Ground_SetupStageCallbacks(gobj, callbacks);
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", __FILE__, 187, gobj_id);
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

void grFigureGet_80219B10(Ground* gp, s32 arg1, CollData* cd, s32 arg3,
                          mpLib_GroundEnum arg4, f32 arg5)
{
    HSD_GObj* item_gobj = cd->x0_gobj;
    if ((s32) cd->x34_flags.b1234 == 5 && item_gobj &&
        item_gobj->classifier == HSD_GOBJ_CLASS_ITEM)
    {
        Item* ip = GET_ITEM(cd->x0_gobj);
        if (ip->kind == It_Kind_Coin && gp->gv.figureget.x8 < 3) {
            HSD_GObj* item_gobj = cd->x0_gobj;
            int value = it_802F2020(item_gobj);
            int count = 0;
            int i;
            for (i = 0; i < gp->gv.figureget.x8; i++) {
                if (gp->gv.figureget.x28[i] == cd->x0_gobj) {
                    count++;
                }
            }
            if (count == 0) {
                if (cd->cur_pos.x <= 4.5f && cd->cur_pos.x >= -4.5f) {
                    it_802F202C(cd->x0_gobj);
                    gp->gv.figureget.x28[gp->gv.figureget.x8] = cd->x0_gobj;
                    gp->gv.figureget.x1C[gp->gv.figureget.x8] = value;
                    gp->gv.figureget.x8++;
                }
            }
        }
    }
}

void grFigureGet_80219C34(HSD_GObj* gobj)
{
    Ground* gp;
    if (gobj == NULL) {
        return;
    }
    gp = GET_GROUND(gobj);
    gp->gv.figureget.xC += 1;
}

bool grFigureGet_80219C50(HSD_GObj* gobj)
{
    Ground* gp;
    if (gobj == NULL) {
        return false;
    }
    gp = GET_GROUND(gobj);
    if (gp->gv.figureget.x8 + gp->gv.figureget.xC >= 3) {
        return true;
    }
    return false;
}

DynamicsDesc* grFigureGet_OnTouchLine(enum_t arg0)
{
    return NULL;
}

bool grFigureGet_OnCheckShadowRender(Vec3* arg0, int arg1, HSD_JObj* arg2)
{
    return true;
}
