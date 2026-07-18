#include "grfigureget.h"

#include <platform.h>

#include "baselib/forward.h"

#include "ft/ftlib.h"
#include "gm/gmregclear.h"

#include "gr/forward.h"

#include "gr/granime.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "gr/stage.h"
#include "gr/types.h"

#include "it/forward.h"

#include "it/inlines.h"
#include "it/items/itcoin.h"
#include "it/types.h"

#include "lb/forward.h"

#include "lb/lb_00B0.h"
#include "lb/lbspdisplay.h"
#include "lb/types.h"

#include "mp/forward.h"

#include "mp/mplib.h"
#include "ty/toy.h"
#include "ty/tydisplay.h"

#include <dolphin/mtx.h>
#include <dolphin/os/OSError.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>

typedef struct grFigureGet_Data {
    s32 x0;
    s32 x4;
    s32 x8;
    f32 xC;
    f32 x10;
    f32 x14;
} grFigureGet_Params;

static Vec3 const grFigureGet_803B8470 = { 0.0f, 0.0f, 0.0f };

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

static grFigureGet_Params* yakumono_param;
extern f32 grFigureGet_804DBB60;
extern f32 grFigureGet_804DBB64;

extern StageInfo stage_info;

void grFigureGet_OnDemoInit(int unused) {}

void grFigureGet_OnInit(void)
{
    yakumono_param = Ground_801C49F8();
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

void grFigureGet_802196F0(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    s32 i0;
    s32 i1;
    s32 i2;
    s32 temp_r3;
    s32 temp_r3_2;
    int* var_r30;
    s32 sp14;
    s32 var_r29_3;
    s32 var_r6;

    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->x8_callback = NULL;
    gp->xC_callback = NULL;
    tyDisplay_8031C2CC();
    i0 = HSD_Randi(3);
    gp->gv.figureget.x10[i0] = Toy_80305058(0, 0x63, 0, 65.0f);
    i1 = i0 + 1;
    if (i1 >= 3) {
        i1 = 0;
    }
    gp->gv.figureget.x10[i1] = Ground_801C5840();
    if (tyDisplay_8031C354(gp->gv.figureget.x10[i1], &sp14, 1, 2) == 0) {
        do {
            temp_r3 = Toy_80305058(2, 0x63, 1, 75.0f);
            sp14 = temp_r3;
        } while (gp->gv.figureget.x10[i1] == temp_r3);
    }
    i1 = i1 + 1;
    if (i1 >= 3) {
        i1 = 0;
    }
    gp->gv.figureget.x10[i1] = sp14;
    for (var_r29_3 = 0; var_r29_3 < 3; var_r29_3++) {
        tyDisplay_8031C454(gp->gv.figureget.x10[var_r29_3]);
    }
    PAD_STACK(8);
    temp_r3_2 = yakumono_param->x4;
    if (temp_r3_2 != 0) {
        var_r6 = HSD_Randi(temp_r3_2);
    } else {
        var_r6 = 0;
    }
    gp->gv.figureget.x0 = yakumono_param->x0 + var_r6;
    gp->gv.figureget.x4 = 0;
    gp->gv.figureget.x8 = 0;
    gp->gv.figureget.xC = 0;
    memzero(gp->gv.figureget.x1C, 0xC);
    memzero(gp->gv.figureget.x28, 0xC);
    memzero(gp->gv.figureget.x34, 0xC);
    mpJointSetCb1(0, gp, grFigureGet_80219B10);
}

bool grFigureGet_80219890(Ground_GObj* gobj)
{
    return false;
}

void grFigureGet_80219898(Ground_GObj* gobj)
{
    u32 pad2;
    HSD_GObj* var_r28;
    Item_GObj* temp_r3_2;
    Point3d pos;
    f32 temp_f1;
    f32 var_f2;
    s32 temp_r0;
    s32 temp_r3;
    s32 temp_r6;
    s32 var_r30;
    s32 var_r3;
    Ground* gp = GET_GROUND(gobj);
    int* var_r29;
    u32 pad;

    for (var_r28 = HSD_GObj_Entities->fighters; var_r28 != NULL;
         var_r28 = var_r28->next)
    {
        ftLib_80086984(var_r28)->joint_id_skip = 0;
    }
    if (gp->gv.figureget.x4 < yakumono_param->x8) {
        temp_r3 = gp->gv.figureget.x0;
        if (temp_r3 == 0) {
            pos = grFigureGet_803B8470;
            gp->gv.figureget.x4 += 1;
            var_f2 = yakumono_param->x10;
            var_f2 = var_f2 - yakumono_param->xC;
            if (var_f2 < 0.0f) {
                var_f2 = -var_f2;
            }
            temp_f1 = 0.5f;
            temp_f1 = var_f2 * temp_f1;
            temp_f1 -= 20.0f;
            if ((s32) temp_f1 != 0) {
                var_r3 = HSD_Randi((s32) temp_f1);
            } else {
                var_r3 = 0;
            }
            pos.x = 20.0f + (f32) var_r3;
            var_r30 = 2;
            if (HSD_Randi(var_r30) == 0) {
                pos.x *= -1.0f;
            }
            pos.y = yakumono_param->x14 + Stage_GetCamBoundsTopOffset();
            temp_r6 = gp->gv.figureget.x4;
            temp_r3_2 = it_802F2094(
                gobj, &pos, gp->gv.figureget.x10[temp_r6 - 1], temp_r6);
            gp->gv.figureget.x34[gp->gv.figureget.x4 - 1] = temp_r3_2;
            it_802F2014(temp_r3_2, 0);
            temp_r3 = yakumono_param->x4;
            if (temp_r3 != 0) {
                var_r3 = HSD_Randi(temp_r3);
            } else {
                var_r3 = 0;
            }
            gp->gv.figureget.x0 = yakumono_param->x0 + var_r3;
        } else {
            gp->gv.figureget.x0 = temp_r3 - 1;
        }
    } else if (grFigureGet_80219C50(gobj) != 0) {
        for (var_r30 = 0; var_r30 < gp->gv.figureget.x8; var_r30++) {
            gm_8017E280((u16) gp->gv.figureget.x1C[var_r30], 1U);
        }
        if (gp->gv.figureget.x8 != 0) {
            if (gp->gv.figureget.x8 == 3) {
                stage_info.flags |= 0x20;
            }
            stage_info.flags |= 0x100;
        } else {
            stage_info.flags |= 0x200;
        }
    }
    lb_800115F4();
}

void grFigureGet_80219B0C(Ground_GObj* gobj) {}

void grFigureGet_80219B10(Ground* gp, s32 arg1, CollData* cd, s32 arg3,
                          mpLib_GroundEnum arg4, f32 arg5)
{
    ECBFlagStruct* tmp;
    HSD_GObj* item_gobj = cd->x0_gobj;
    if (((((s32) (*(tmp = &cd->x34_flags)).b1234) == 5) && item_gobj) &&
        (item_gobj->classifier == 0x6))
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
                if (cd->cur_pos.x <= grFigureGet_804DBB60 &&
                    cd->cur_pos.x >= grFigureGet_804DBB64)
                {
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
