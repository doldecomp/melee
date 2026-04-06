#include "groldyoshi.h"

#include "types.h"

#include <platform.h>

#include "baselib/random.h"

#include "forward.h"

#include "gr/grdisplay.h"
#include "gr/grlib.h"
#include "gr/grmaterial.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "mp/mplib.h"

#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>

StageCallbacks grOy_803E6488[] = {
    { grOldYoshi_8020E93C, grOldYoshi_8020E968, grOldYoshi_8020E970,
      grOldYoshi_8020E974, 0 },
    { grOldYoshi_8020E978, grOldYoshi_8020E9E0, grOldYoshi_8020E9E8,
      grOldYoshi_8020E9EC, 0 },
    { grOldYoshi_8020EAFC, grOldYoshi_8020EC08, grOldYoshi_8020EC10,
      grOldYoshi_8020EFC8, 0 },
    { grOldYoshi_8020EFCC, grOldYoshi_8020F080, grOldYoshi_8020F088,
      grOldYoshi_8020F2A4, 0 },
    { grOldYoshi_8020E9F0, grOldYoshi_8020EA5C, grOldYoshi_8020EA64,
      grOldYoshi_8020EA88, 0xC0000000 },
    { grOldYoshi_8020EA8C, grOldYoshi_8020EAEC, grOldYoshi_8020EAF4,
      grOldYoshi_8020EAF8, 0 },
};

StageData grOy_803E650C = {
    29,
    grOy_803E6488,
    "/GrOy.dat",
    grOldYoshi_8020E79C,
    grOldYoshi_8020E798,
    grOldYoshi_8020E824,
    grOldYoshi_8020E828,
    grOldYoshi_8020E84C,
    grOldYoshi_8020F404,
    grOldYoshi_8020F40C,
    1,
    0,
    0,
};

static struct {
    s16 x0;
    s16 x2;
    float x4;
    float x8;
    float xC;
    s16 x10;
    s16 x12;
    s16 x14;
    s16 x16;
    s16 x18;
}* grOy_804D6A88;

void grOldYoshi_8020E798(bool arg) {}

void grOldYoshi_8020E79C(void)
{
    grOy_804D6A88 = Ground_801C49F8();
    stage_info.unk8C.b4 = 0;
    stage_info.unk8C.b5 = 1;
    grOldYoshi_8020E854(0);
    grOldYoshi_8020E854(1);
    grOldYoshi_8020E854(4);
    grOldYoshi_8020E854(5);
    grOldYoshi_8020E854(2);
    grOldYoshi_8020E854(3);
    Ground_801C39C0();
    Ground_801C3BB4();
}

void grOldYoshi_8020E824(void) {}

void grOldYoshi_8020E828(void)
{
    grZakoGenerator_801CAE04(NULL);
}

bool grOldYoshi_8020E84C(void)
{
    return false;
}

HSD_GObj* grOldYoshi_8020E854(int gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grOy_803E6488[gobj_id];

    gobj = Ground_GetStageGObj(gobj_id);

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
            HSD_GObj_SetupProc(gobj, callbacks->callback2, 4);
        }

    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "groldyoshi.c", 206,
                 gobj_id);
    }

    return gobj;
}

void grOldYoshi_8020E93C(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grOldYoshi_8020E968(Ground_GObj* arg)
{
    return false;
}

void grOldYoshi_8020E970(Ground_GObj* arg) {}

void grOldYoshi_8020E974(Ground_GObj* arg) {}

void grOldYoshi_8020E978(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);

    grAnime_801C8138(gobj, gp->map_id, 0);
    grMaterial_801C8858(jobj, JOBJ_UNK_B27);
    grMaterial_801C8858(jobj, JOBJ_ROOT_XLU);
    gp->x11_flags.b012 = 2;
}

bool grOldYoshi_8020E9E0(Ground_GObj* arg)
{
    return false;
}

void grOldYoshi_8020E9E8(Ground_GObj* arg) {}

void grOldYoshi_8020E9EC(Ground_GObj* arg) {}

void grOldYoshi_8020E9F0(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);

    Ground_801C2ED0(jobj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->x11_flags.b012 = 1;
    gp->x10_flags.b5 = 1;
}

bool grOldYoshi_8020EA5C(Ground_GObj* arg)
{
    return false;
}

void grOldYoshi_8020EA64(Ground_GObj* arg0)
{
    Ground_801C2FE0(arg0);
    lb_800115F4();
}

void grOldYoshi_8020EA88(Ground_GObj* arg) {}

void grOldYoshi_8020EA8C(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);

    Ground_801C2ED0(jobj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->x11_flags.b012 = 1;
}

bool grOldYoshi_8020EAEC(Ground_GObj* arg)
{
    return false;
}

void grOldYoshi_8020EAF4(Ground_GObj* arg) {}

void grOldYoshi_8020EAF8(Ground_GObj* arg) {}

s16 grOy_803E6574[] = { 0, 1, 1, 5, 2, 9 };

void grOldYoshi_8020EAFC(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    int i;
    Ground_801C2ED0(jobj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 0);
    for (i = 0; i < 3; i++) {
        gp->gv.oldyoshicloud.cloud[i].xC4_0123 = 0;
        gp->gv.oldyoshicloud.cloud[i].xC4_4 = 0;
        gp->gv.oldyoshicloud.cloud[i].xC4_567 = 0;
        gp->gv.oldyoshicloud.cloud[i].xD4 = 0.0f;
        gp->gv.oldyoshicloud.cloud[i].xD0 = 0.0f;
        gp->gv.oldyoshicloud.cloud[i].xC8 =
            Ground_801C3FA4(gobj, grOy_803E6574[i * 2 + 1]);
        gp->gv.oldyoshicloud.cloud[i].xCC =
            HSD_JObjGetTranslationY(gp->gv.oldyoshicloud.cloud[i].xC8);
        mpJointSetCb1(grOy_803E6574[i * 2], gp, fn_8020F2A8);
    }
    gp->x11_flags.b012 = 1;
}

bool grOldYoshi_8020EC08(Ground_GObj* arg)
{
    return false;
}

void grOldYoshi_8020EC10(Ground_GObj* arg)
{
    u16 uVar3;
    int i = 0;
    Ground* gp = arg->user_data;
    HSD_JObj* jobj = arg->user_data;
    do {
        // int test = HSD_Randi(3);
        switch (gp->gv.oldyoshicloud.cloud[i].xC4_0123) {
        case 0:
            if (gp->gv.oldyoshicloud.cloud[i].xC4_4 != 0) {
                // grOldYoshi_8020F31C(0,0,0,0,0,0);
                gp->gv.oldyoshicloud.cloud[i].xD4 = grOldYoshi_8020F31C(
                    gp->gv.oldyoshicloud.cloud[i].xD4, grOy_804D6A88->x8,
                    gp->gv.oldyoshicloud.cloud[i].xD0, grOy_804D6A88->xC,
                    grOy_804D6A88->x4, -grOy_804D6A88->x4);
                gp->gv.oldyoshicloud.cloud[i].xD0 +=
                    gp->gv.oldyoshicloud.cloud[i].xD4;
                if (gp->gv.oldyoshicloud.cloud[i].xD0 > grOy_804D6A88->xC) {
                    gp->gv.oldyoshicloud.cloud[i].xD0 = grOy_804D6A88->xC;
                }
                uVar3 = gp->gv.oldyoshicloud.cloud[i].xC4_567++;
                if (uVar3 > grOy_804D6A88->x0) {
                    gp->gv.oldyoshicloud.cloud[i].xC4_0123 = 1;
                    grAnime_801C7FF8(arg, grOy_803E6574[i * 2 + 1], 2, 1, 0.0f,
                                     1.0);
                    grLib_801C97DC(
                        30000, 30,
                        gp->gv.oldyoshicloud.cloud[i].xC8); // spawn effect
                    gp->gv.oldyoshicloud.cloud[i].xC4_567 = 0;
                }
            } else {
                gp->gv.oldyoshicloud.cloud[i].xD4 = grOldYoshi_8020F31C(
                    gp->gv.oldyoshicloud.cloud[i].xD4, grOy_804D6A88->x8,
                    gp->gv.oldyoshicloud.cloud[i].xD0, 0.0f, grOy_804D6A88->x4,
                    -grOy_804D6A88->x4);
                gp->gv.oldyoshicloud.cloud[i].xD0 +=
                    gp->gv.oldyoshicloud.cloud[i].xD4;
                if (gp->gv.oldyoshicloud.cloud[i].xD0 < 0.0f) {
                    gp->gv.oldyoshicloud.cloud[i].xD0 = 0.0f;
                }
                gp->gv.oldyoshicloud.cloud[i].xC4_567 = 0;
            }
            break;
        case 1:
            if (gp->gv.oldyoshicloud.cloud[i].xC4_567 == grOy_804D6A88->x10) {
                mpLib_80057BC0(grOy_803E6574[i * 2]);
            }
            gp->gv.oldyoshicloud.cloud[i].xC4_567++;
            if (grAnime_801C83D0(arg, grOy_803E6574[i * 2 + 1], 2)) {
                gp->gv.oldyoshicloud.cloud[i].xC4_0123 = 2;
                mpLib_80057BC0(grOy_803E6574[i * 2]);
                HSD_JObjSetFlagsAll(gp->gv.oldyoshicloud.cloud[i].xC8, 16);
                gp->gv.oldyoshicloud.cloud[i].xC4_567 = 0;
            }
            break;
        case 2:
            //                gp->gv.oldyoshicloud.cloud[i].xC4_5++;
            uVar3 = gp->gv.oldyoshicloud.cloud[i].xC4_567++;
            if (uVar3 > grOy_804D6A88->x2) {
                gp->gv.oldyoshicloud.cloud[i].xC4_0123 = 3;
                grAnime_801C7FF8(arg, grOy_803E6574[i * 2 + 1], 2, 2, 0.0f,
                                 1.0);
                gp->gv.oldyoshicloud.cloud[i].xC4_567 = 0;
            }
            break;
        case 3:
            if (gp->gv.oldyoshicloud.cloud[i].xC4_567 == 0) {
                HSD_JObjClearFlagsAll(gp->gv.oldyoshicloud.cloud[i].xC8, 16);
            }
            if (gp->gv.oldyoshicloud.cloud[i].xC4_567 == grOy_804D6A88->x12) {
                mpJointListAdd(grOy_803E6574[i * 2]);
            }
            gp->gv.oldyoshicloud.cloud[i].xC4_567++;
            if (grAnime_801C83D0(arg, grOy_803E6574[i * 2 + 1], 2)) {
                gp->gv.oldyoshicloud.cloud[i].xC4_0123 = 0;
                gp->gv.oldyoshicloud.cloud[i].xC4_567 = 0;
            }
            break;
        }
        HSD_JObjSetTranslateY(gp->gv.oldyoshicloud.cloud[i].xC8,
                              gp->gv.oldyoshicloud.cloud[i].xCC -
                                  gp->gv.oldyoshicloud.cloud[i].xD0);
        gp->gv.oldyoshicloud.cloud[i].xC4_4 = 0;
        i++;
    } while (i < 3);
    Ground_801C2FE0(arg);
    return;
}

void grOldYoshi_8020EFC8(Ground_GObj* arg) {}

static inline s32 randi_between(s32 min, s32 max)
{
    if (max > min) {
        if (min - max != 0) {
            return max + HSD_Randi(max - min);
        } else {
            return max;
        }
    } else if (max < min) {
        if (min - max != 0) {
            return min + HSD_Randi(max - min);
        } else {
            return min;
        }
    } // else {
    //    return min;
    //}
}

/// #grOldYoshi_8020EFCC
void grOldYoshi_8020EFCC(Ground_GObj* arg)
{
    HSD_JObj* jobj = arg->hsd_obj;
    Ground* gp = arg->user_data;
    HSD_JObjSetFlagsAll(jobj, 0x10);
    gp->gv.oldyoshiguest.xC4 =
        rand_range(grOy_804D6A88->x16, grOy_804D6A88->x14);
    gp->gv.oldyoshiguest.xC6 = -1;
    gp->x11_flags.b012 = 2;
    // oldyoshiguest;
}

bool grOldYoshi_8020F080(Ground_GObj* arg)
{
    return false;
}
const int grOy_803B83F0[5] = { 1, 2, 3, 4, 5 };
/// #grOldYoshi_8020F088
void grOldYoshi_8020F088(Ground_GObj* arg)
{
    HSD_JObj* jobj = arg->hsd_obj;
    Ground* gp = arg->user_data;
    s16 sVar5;
    float dVar9;
    float dVar10;
    int local34[5];
    if (gp->gv.oldyoshiguest.xC6 == -1) {
        sVar5 = gp->gv.oldyoshiguest.xC4;
        gp->gv.oldyoshiguest.xC4 = sVar5 - 1;
        if (sVar5 < 0) {
            local34[0] = grOy_803B83F0[0];
            local34[1] = grOy_803B83F0[1];
            local34[2] = grOy_803B83F0[2];
            local34[3] = grOy_803B83F0[3];
            local34[4] = grOy_803B83F0[4];
            gp->gv.oldyoshiguest.xC6 = local34[HSD_Randi(5)];
        }
        grAnime_801C8138(arg, gp->map_id, 0);
        dVar10 = HSD_Randf();
        jobj = arg->hsd_obj;
        dVar9 = grOy_804D6A88->x18 * (dVar10 * 2.0f - 1.0f);
        HSD_JObjSetTranslateY(jobj, dVar9);
    } else {
        jobj = Ground_801C3FA4(arg, gp->gv.oldyoshiguest.xC6);
        if (jobj == NULL) {
            return;
        }
        if ((HSD_JObjGetFlags(jobj) & 0x10) != 0) {
            HSD_JObjClearFlagsAll(jobj, 0x10);
        }
        if (grAnime_801C83D0(arg, 0, 7) != 0) {
            HSD_JObjSetFlagsAll(jobj, 0x10);
            gp->gv.oldyoshiguest.xC4 =
                rand_range(grOy_804D6A88->x16, grOy_804D6A88->x14);
            gp->gv.oldyoshiguest.xC6 = -1;
        }
    }
}

void grOldYoshi_8020F2A4(Ground_GObj* arg) {}

void fn_8020F2A8(Ground* gp, s32 param2, CollData* coll, s32 param4,
                 mpLib_GroundEnum param5, float param6)
{
    int i;
    if ((s32) coll->x34_flags.b1234 != 1) {
        return;
    }
    for (i = 0; i < 3; i++) {
        if (param2 == grOy_803E6574[i * 2]) {
            break;
        }
    }
    if (i == 3) {
        return;
    }
    gp->gv.oldyoshicloud.cloud[i].xC4_4 = 1;
    return;
}

// Move related code from Context tab to here
float grOldYoshi_8020F31C(float param1, float param2, float param3,
                          float param4, float param5, float param6)
{
    float fVar1;
    float fVar2;
    float fVar3;
    // fVar2 = param1;
    if (param1 < 0.0f) {
        fVar2 = -param1;
    } else {
        fVar2 = param1;
    }
    fVar3 = (fVar2 / param2);
    // fVar2 = param1;
    if (param1 < 0.0f) {
        fVar2 = -param1;
    } else {
        fVar2 = param1;
    }
    fVar1 = param4 - param3;
    if (fVar1 < 0.0f) {
        fVar1 = -fVar1;
    }
    if (fVar3 * (-param2 * 0.5f * fVar3) + (fVar3 * fVar2) < fVar1 &&
        ((param4 > param3 && param1 > 0.0f) ||
         (param4 < param3 && param1 < 0.0f)))
    {
        if (param1 > 0.0f) {
            param1 = param1 - param2;
        } else if (param1 < 0.0f) {
            param1 = param1 + param2;
        }
    } else {
        if (param4 > param3) {
            param1 = param1 + param2;
        } else if (param4 < param3) {
            param1 = param1 - param2;
        }
    }
    if (param1 > param5) {
        return param5;
    }
    if (param1 > param6) {
        return param1;
    }
    return param6;
}

DynamicsDesc* grOldYoshi_8020F404(enum_t arg)
{
    return NULL;
}

bool grOldYoshi_8020F40C(Vec3* a, int arg, HSD_JObj* joint)
{
    Vec3 b;

    lb_8000B1CC(joint, NULL, &b);

    if (a->y > b.y + -5.0f) {
        return true;
    } else {
        return false;
    }
}
