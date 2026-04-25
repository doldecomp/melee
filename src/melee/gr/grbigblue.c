#include "grbigblue.h"

#include "grbigblue.static.h"

#include "grdisplay.h"
#include "grfzerocar.h"
#include "grmaterial.h"
#include "ground.h"
#include "placeholder.h"

#include <platform.h>

#include "baselib/debug.h"
#include "cm/camera.h"
#include "gm/gm_1A45.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "gr/stage.h"
#include "gr/types.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "lb/lbvector.h"
#include "mp/mplib.h"
#include "MSL/math_ppc.h"

#include <math.h>
#include <trigf.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>
#include <baselib/jobj.h>
#include <baselib/memory.h>
#include <baselib/random.h>

#define M_TAU 6.283185307179586

extern ItemKind grBb_803B8120[5];
extern grBb_LineIds grBb_803B8134;

extern f32 grBb_804DB2F0;
extern f32 grBb_804DB2F4;
extern f32 grBb_804DB304;
extern f32 grBb_804DB308;
extern f32 grBb_804DB30C;
extern f32 grBb_804DB310;
extern f32 grBb_804DB3F0;

static grBb_YakumonoParams* grBb_804D69C8;

typedef struct grBb_Data803E2D78 {
    u8 pad_0[0xC];
    s16 xC[30];
    s16 x48[30];
    s16 x84[30];
} grBb_Data803E2D78;

typedef struct grBb_Data803E2EB8 {
    u8 pad_0[0x58];
    u32 x58[4];
} grBb_Data803E2EB8;

u8 grBb_803E2938[0xA8] = { 0 };
extern grBb_Data803E2D78 grBb_803E2D78;
extern grBb_Data803E2EB8 grBb_803E2EB8;

StageCallbacks grBb_803E29E0[] = {
    { grBigBlue_801E5AE4, grBigBlue_801E5B10, grBigBlue_801E5B18,
      grBigBlue_801E5B1C, 0 },
    { grBigBlue_801E6298, grBigBlue_801E6354, grBigBlue_801E635C,
      grBigBlue_801E6360, 40000000 },
    { grBigBlue_801E6200, grBigBlue_801E6288, grBigBlue_801E6290,
      grBigBlue_801E6294, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { grBigBlue_801E5B20, grBigBlue_801E6114, grBigBlue_801E611C,
      grBigBlue_801E6120, 0 },
    { grBigBlue_801E6904, grBigBlue_801E6C58, grBigBlue_801E6C60,
      grBigBlue_801E855C, 0 },
    { grBigBlue_801E6364, grBigBlue_801E687C, grBigBlue_801E6884,
      grBigBlue_801E68B8, 0 },
    { grBigBlue_801E613C, grBigBlue_801E61BC, grBigBlue_801E61C4,
      grBigBlue_801E61FC, 0 },
    { grBigBlue_801E8D64, grBigBlue_801E93D0, grBigBlue_801E93D8,
      grBigBlue_801E9F38, 80000000 },
    { grBigBlue_801E9F3C, grBigBlue_801EA054, grBigBlue_801EA05C,
      grBigBlue_801EAB4C, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 }
};

static const Vec3 grBb_803B8108 = { -1.0F, 0.0F, 0.0F };
static const Vec3 grBb_803B8114 = { 56.0F, 40.0F, 24.0F };

static grBb_TrackEntry grBb_TrackEntries[12] = {
    { 4, 6, 5, 0, { 0, 0, 0 } },    { 19, 21, 20, 0, { 0, 0, 0 } },
    { 7, 9, 8, 0, { 0, 0, 0 } },    { 10, 12, 11, 0, { 0, 0, 0 } },
    { 44, 46, 45, 0, { 0, 0, 0 } }, { 1, 3, 2, 0, { 0, 0, 0 } },
    { 32, 34, 33, 0, { 0, 0, 0 } }, { 35, 37, 36, 0, { 0, 0, 0 } },
    { 38, 40, 39, 0, { 0, 0, 0 } }, { 41, 43, 42, 0, { 0, 0, 0 } },
    { 29, 31, 30, 0, { 0, 0, 0 } }, { 13, 18, 17, 0, { 0, 0, 0 } },
};

void grBigBlue_801E57BC(bool arg) {}

void grBigBlue_801E57C0(void)
{
    u8 pad[8];
    Vec3 direction;
    PAD_STACK(12);

    grBb_804D69C8 = Ground_801C49F8();
    stage_info.unk8C.b4 = 0;
    stage_info.unk8C.b5 = 1;
    grBigBlue_801E59F8(0x1F);
    grBigBlue_801E59F8(0);
    grBigBlue_801E59F8(1);
    grBigBlue_801E59F8(2);
    grBigBlue_801E59F8(0x22);
    grBigBlue_801E59F8(0x21);
    HSD_JObjSetFlagsAll(grBigBlue_801E59F8(0x20)->hsd_obj, 0x10);
    grBigBlue_801E59F8(0x23);
    HSD_JObjSetFlagsAll(grBigBlue_801E59F8(0x24)->hsd_obj, 0x10);
    Ground_801C39C0();
    Ground_801C3BB4();
    mpLib_80058044(0x21);
    mpLib_80058044(0x22);
    mpLib_80058044(0x23);
    mpLib_80058044(0x24);
    mpLib_80058044(0x25);
    mpLib_80058044(0x26);
    mpLib_80058044(0x27);
    mpLib_80058044(0x28);
    mpLib_80058044(0x29);
    mpLib_80058044(0x2A);
    mpLib_80058044(0x2B);
    mpLib_80058044(0x2C);
    mpLib_80058044(0x2D);
    mpLib_80058044(0x2E);
    mpLib_80058044(0x2F);
    mpLib_80058044(0x30);
    mpLib_80058044(0x31);
    mpLib_80058044(0x32);
    mpLib_80058044(0x33);
    mpLib_80058044(0x34);
    mpLib_80058044(0x35);
    mpLib_80058044(0x36);
    mpLib_80058044(0x37);
    mpLib_80058044(0x38);
    mpLib_80058044(0x39);
    mpLib_80058044(0x3A);
    mpLib_80058044(0x3B);
    mpLib_80058044(0x3C);
    mpLib_80058044(0x3D);
    mpLib_80058044(0x3E);
    mpLib_80058044(0x3F);
    mpLib_80058044(0x40);
    mpLib_80058044(0x41);
    direction = grBb_803B8108;
    lb_80011A50(&direction, -1, 1.0F, 0.0F, M_PI / 3, -100000.0F, 100000.0F,
                100000.0F, -100000.0F);
}

void grBigBlue_801E59C8(void) {}

void grBigBlue_801E59CC(void)
{
    grZakoGenerator_801CAE04(NULL);
}

bool grBigBlue_801E59F0(void)
{
    return false;
}

HSD_GObj* grBigBlue_801E59F8(s32 id)
{
    HSD_GObj* gobj;
    StageCallbacks* cbs = &grBb_803E29E0[id];
    gobj = Ground_GetStageGObj(id);
    if (gobj != NULL) {
        Ground* gp = GET_GROUND(gobj);
        gp->x8_callback = NULL;
        gp->xC_callback = NULL;

        GObj_SetupGXLink(gobj, grDisplay_801C5DB0, 3U, 0U);
        if (cbs->callback3 != NULL) {
            gp->x1C_callback = cbs->callback3;
        }
        if (cbs->callback0 != NULL) {
            cbs->callback0(gobj);
        }
        if (cbs->callback2 != NULL) {
            HSD_GObj_SetupProc(gobj, cbs->callback2, 4U);
        }
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grbigblue.c", 0x17E,
                 id);
    }
    return gobj;
}

void grBigBlue_801E5AE4(Ground_GObj* gobj)
{
    grAnime_801C8138(gobj, GET_GROUND(gobj)->map_id, 0);
}

bool grBigBlue_801E5B10(Ground_GObj* arg)
{
    return false;
}

void grBigBlue_801E5B18(Ground_GObj* arg) {}

void grBigBlue_801E5B1C(Ground_GObj* arg) {}

void grBigBlue_801E5B20(Ground_GObj* gobj)
{
    HSD_JObj* jobj = gobj->hsd_obj;
    PAD_STACK(8);

    gobj->render_cb = fn_801EFB9C;

    HSD_JObjSetTranslateX(jobj, grBb_804D69C8->x134_translate.x);
    HSD_JObjSetTranslateY(jobj, grBb_804D69C8->x134_translate.y);
    HSD_JObjSetTranslateZ(jobj, grBb_804D69C8->x134_translate.z);
    HSD_JObjSetScaleX(jobj, grBb_804D69C8->x140_scale);
    HSD_JObjSetScaleY(jobj, grBb_804D69C8->x140_scale);
    HSD_JObjSetScaleZ(jobj, grBb_804D69C8->x140_scale);

    jobj = HSD_JObjGetChild(jobj);
    if (jobj != NULL) {
        HSD_JObjSetTranslateX(jobj, 0.0F);
        HSD_JObjSetTranslateY(jobj, 0.0F);
        HSD_JObjSetTranslateZ(jobj, 0.0F);

        jobj = HSD_JObjGetChild(jobj);
        if (jobj != NULL) {
            HSD_JObjSetTranslateX(jobj, 0.0F);
            HSD_JObjSetTranslateY(jobj, 0.0F);
            HSD_JObjSetTranslateZ(jobj, 0.0F);
        }
    }
}

bool grBigBlue_801E6114(Ground_GObj* arg)
{
    return false;
}

void grBigBlue_801E611C(Ground_GObj* arg) {}

void grBigBlue_801E6120(Ground_GObj* arg) {}

void fn_801E6124(Ground_GObj* gobj)
{
    Ground* g = GET_GROUND(gobj);
    g->gv.bigblue.x0_b1 = false;
}

void grBigBlue_801E613C(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = gobj->hsd_obj;
    PAD_STACK(16);

    grAnime_801C8138(gobj, gp->map_id, 0);
    Ground_801C2ED0(jobj, gp->map_id);
    grBigBlue_801EB004(gobj);
    gp->gv.bigblue.x0_b1 = true;
    Ground_801C10B8(gobj, fn_801E6124);
}

bool grBigBlue_801E61BC(Ground_GObj* arg)
{
    return false;
}

void grBigBlue_801E61C4(Ground_GObj* gobj)
{
    PAD_STACK(16);
    grBigBlue_801EBAF8(gobj);
    lb_800115F4();
    Ground_801C2FE0(gobj);
}

void grBigBlue_801E61FC(Ground_GObj* arg) {}

void grBigBlue_801E6200(Ground_GObj* gobj)
{
    Ground* gp;
    Ground* gp2;
    HSD_JObj* jobj;
    void* filler;

    gp = GET_GROUND(gobj);
    jobj = gobj->hsd_obj;
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp2 = GET_GROUND(gobj);
    gp2->x10_flags.b2 = 0;
    grMaterial_801C8A04(jobj, 0x08000000U);
    grMaterial_801C8858(jobj, 0x20000000U);
    gp->x11_flags.b012 = 1;
}

bool grBigBlue_801E6288(Ground_GObj* arg)
{
    return false;
}

void grBigBlue_801E6290(Ground_GObj* arg) {}

void grBigBlue_801E6294(Ground_GObj* arg) {}

void grBigBlue_801E6298(Ground_GObj* gobj)
{
    HSD_JObj* jobj5;
    HSD_JObj* jobj4;
    HSD_JObj* jobj3;
    HSD_JObj* jobj2;
    HSD_JObj* jobj1;

    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
    jobj1 = Ground_801C3FA4(gobj, 6);
    jobj2 = Ground_801C3FA4(gobj, 7);
    jobj3 = Ground_801C3FA4(gobj, 3);
    jobj4 = Ground_801C3FA4(gobj, 4);
    jobj5 = Ground_801C3FA4(gobj, 2);
    Ground_801C4E70(Ground_801C3FA4(gobj, 5), jobj5, jobj4, jobj3, jobj2,
                    jobj1);
    gp->x11_flags.b012 = 2;
}

bool grBigBlue_801E6354(Ground_GObj* arg)
{
    return false;
}

void grBigBlue_801E635C(Ground_GObj* arg) {}

void grBigBlue_801E6360(Ground_GObj* arg) {}

void grBigBlue_801E6364(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* child;
    HSD_JObj* next;
    HSD_JObj* cur;
    s32 i;
    HSD_JObj* jobj = gobj->hsd_obj;
    HSD_GObj* car_gobj;
    Vec3 scale;
    f32 trans_x;
    f32 scale_base;
    f32 rot_y;

    Ground_801C2ED0(jobj, gp->map_id);

    scale.x = scale.y = scale.z = 1.0F;
    HSD_JObjSetScale(jobj, &scale);

    gp->gv.bigblue.xC8 = HSD_MemAlloc(120);
    HSD_ASSERT(774, gp->gv.bigblue.xC8 != NULL);

    gp->gv.bigblue.xCC = HSD_MemAlloc(30);
    HSD_ASSERT(776, gp->gv.bigblue.xCC != NULL);

    for (i = 0; i < 30; i++) {
        ((HSD_JObj**) gp->gv.bigblue.xC8)[i] =
            Ground_801C3FA4(gobj, grBb_803E2D78.x48[i]);
    }

    car_gobj = grBigBlue_801E59F8(4);
    HSD_ASSERT(783, car_gobj != NULL);
    grFZeroCar_801CAFBC(car_gobj, grBb_803E2D78.x48, 30, 1);

    cur = HSD_JObjGetChild(car_gobj->hsd_obj);
    rot_y = grBb_804DB304;
    scale_base = grBb_804DB2F0;
    trans_x = grBb_804DB308;

    for (i = 0; i < 30; i++) {
        child = HSD_JObjGetChild(cur);
        next = HSD_JObjGetNext(cur);

        HSD_JObjReparent(cur, ((HSD_JObj**) gp->gv.bigblue.xC8)[i]);
        HSD_JObjSetRotationY(cur, rot_y);

        scale.x = scale.y = scale.z = Ground_801C0498() * grBb_804D69C8->xC;

        HSD_JObjSetScale(((HSD_JObj**) gp->gv.bigblue.xC8)[i], &scale);

        HSD_JObjGetScale(child, &scale);
        {
            f32 ratio = scale_base / Ground_801C0498();
            scale.x *= ratio;
            scale.y *= ratio;
            scale.z *= ratio;
        }

        HSD_JObjSetScale(child, &scale);

        if (i == 9) {
            HSD_JObjSetTranslateX(child, trans_x);
        }

        cur = next;
    }

    Ground_801C4A08(car_gobj);
    grBigBlue_801EC6C0(gobj);

    {
        s32 max_val = grBb_804D69C8->x10;
        s32 min_val = grBb_804D69C8->x14;
        s32 result;

        if (max_val > min_val) {
            s32 range = max_val - min_val;
            result = min_val + (range != 0 ? HSD_Randi(range) : 0);
        } else if (max_val < min_val) {
            s32 range = min_val - max_val;
            result = max_val + (range != 0 ? HSD_Randi(range) : 0);
        } else {
            result = max_val;
        }

        *(s16*) ((u8*) gp + 0xD0) = (s16) result;
    }
}

bool grBigBlue_801E687C(Ground_GObj* arg)
{
    return false;
}

void grBigBlue_801E6884(Ground_GObj* gobj)
{
    grBigBlue_801EF424(gobj);
    Ground_801C2FE0(gobj);
}

void grBigBlue_801E68B8(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);

    HSD_Free((void*) gp->gv.bigblue.xC8);
    gp->gv.bigblue.xC8 = NULL;
    HSD_Free((void*) gp->gv.bigblue.xCC);
    gp->gv.bigblue.xCC = NULL;
}

void grBigBlue_801E6904(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = gobj->hsd_obj;
    Vec3 scale;
    PAD_STACK(16);

    Ground_801C2ED0(jobj, gp->map_id);
    gp->x10_flags.b5 = 1;

    scale.x = scale.y = scale.z = 1.0F;
    HSD_JObjSetScale(jobj, &scale);

    grAnime_801C8138(gobj, gp->map_id, 0);

    gp->gv.bigblue.xD4[0] = Ground_801C3FA4(gobj, 1);
    gp->gv.bigblue.xD4[1] = Ground_801C3FA4(gobj, 6);
    gp->gv.bigblue.xD4[2] = Ground_801C3FA4(gobj, 11);

    gp->gv.bigblue.data[0].index = 0;
    gp->gv.bigblue.data[0].x1 = 0;
    gp->gv.bigblue.data[0].x50 = 0;
    gp->gv.bigblue.data[1].index = 1;
    gp->gv.bigblue.data[1].x1 = 0;
    gp->gv.bigblue.data[1].x50 = 0;
    gp->gv.bigblue.data[2].index = 2;
    gp->gv.bigblue.data[2].x1 = 0;
    gp->gv.bigblue.data[2].x50 = 0;
    gp->gv.bigblue.x0_w = 0;

    grBigBlue_801E8978(0, NULL, NULL);

    scale.x = scale.y = scale.z = Ground_801C0498();

    jobj = gp->gv.bigblue.xD4[0];
    HSD_JObjSetScale(jobj, &scale);

    jobj = gp->gv.bigblue.xD4[1];
    HSD_JObjSetScale(jobj, &scale);

    jobj = gp->gv.bigblue.xD4[2];
    HSD_JObjSetScale(jobj, &scale);

    mpJointSetCb1(0, gp, (mpLib_Callback) fn_801E8560);
    mpJointSetCb1(1, gp, (mpLib_Callback) fn_801E8560);
    mpJointSetCb1(2, gp, (mpLib_Callback) fn_801E8560);
}

bool grBigBlue_801E6C58(Ground_GObj* arg)
{
    return false;
}

void grBigBlue_801E6C60(Ground_GObj* gobj)
{
    s32 i;
    Ground* gp;
    Ground* base;
    i = 0;
    gp = gobj->user_data;
    base = gp;

    do {
        u8 idx = gp->gv.bigblue.data[0].index;
        u8 state = gp->gv.bigblue.data[0].x1;
        HSD_JObj* jobj = gp->gv.bigblue.xD4[idx];

        switch ((s8) state) {
        case 0:
        {
            if ((int) grBigBlue_801E89DC(0) != 0) {
                s32 range = grBb_804D69C8->x8C;
                s32 rand_val;
                Vec3 pos;

                if (range != 0) {
                    rand_val = HSD_Randi(range);
                } else {
                    rand_val = 0;
                }
                gp->gv.bigblue.data[i].x8 = grBb_804D69C8->x88 + rand_val;

                HSD_JObjGetTranslation(jobj, &pos);

                gp->gv.bigblue.data[i].x38 = pos;
                gp->gv.bigblue.data[i].x44.z = 0.0f;
                gp->gv.bigblue.data[i].x44.y = 0.0f;
                gp->gv.bigblue.data[i].x44.x = 0.0f;
                gp->gv.bigblue.data[i].x18.z = 0.0f;
                gp->gv.bigblue.data[i].x18.y = 0.0f;
                gp->gv.bigblue.data[i].x18.x = 0.0f;
                gp->gv.bigblue.data[i].x1 = 1;
            }
            break;
        }
        case 1:
            if ((int) grBigBlue_801E89DC(0) == 0) {
                gp->gv.bigblue.data[i].x1 = 0;
            } else {
            case 2:
                if (gp->gv.bigblue.data[i].x8 <= 0) {
                    Vec3 pos;
                    Vec3 neg_pos;
                    f32 right_y, left_y;
                    s32 found;
                    s32 retries;

                    memzero(&pos, 0xC);
                    memzero(&neg_pos, 0xC);
                    pos.x = 10.0f + Stage_GetBlastZoneRightOffset();
                    neg_pos.x =
                        -(10.0f + Stage_GetBlastZoneRightOffset());

                    right_y =
                        grBigBlue_801EC58C(&pos, NULL, 500.0f);
                    left_y =
                        grBigBlue_801EC58C(&neg_pos, NULL, 500.0f);

                    if (right_y != -3.4028235e38f ||
                        left_y != -3.4028235e38f)
                    {
                        f32 height_range;
                        s32 height_rand;

                        gp->gv.bigblue.data[i].x8 = grBb_804D69C8->x90;
                        height_range =
                            grBb_804D69C8->x94 - grBb_804D69C8->x90;
                        if (height_range < 0.0f) {
                            height_range = -height_range;
                        }
                        if ((s32) height_range != 0) {
                            height_rand =
                                HSD_Randi((s32) height_range);
                        } else {
                            height_rand = 0;
                        }
                        gp->gv.bigblue.data[i].x8 += (f32) height_rand;
                        pos.y = right_y + gp->gv.bigblue.data[i].x8;
                        neg_pos.y = left_y + gp->gv.bigblue.data[i].x8;

                        if (left_y == -F32_MAX) {
                            gp->gv.bigblue.data[i].x2 = (u8) -1;
                        } else if (right_y == -F32_MAX) {
                            gp->gv.bigblue.data[i].x2 = 1;
                        } else {
                            f32 diff =
                                right_y - left_y;
                            if (diff < 0.0f) {
                                diff = -diff;
                            }
                            if (diff < 80.0f) {
                                s8 dir;
                                if (HSD_Randi(2) != 0) {
                                    dir = 1;
                                } else {
                                    dir = -1;
                                }
                                gp->gv.bigblue.data[i].x2 = (u8) dir;
                            } else {
                                s8 dir2;
                                if (right_y < left_y) {
                                    dir2 = -1;
                                } else {
                                    dir2 = 1;
                                }
                                gp->gv.bigblue.data[i].x2 = (u8) dir2;
                            }
                        }

                        if ((int) grBigBlue_801E89DC(1) != 0) {
                            gp->gv.bigblue.data[i].x2 = 1;
                            pos.x = -(10.0f +
                                Stage_GetBlastZoneRightOffset());
                        } else if ((s32) gp->gv.bigblue.data[i].x2 == 1) {
                            pos = neg_pos;
                        }

                        retries = 0;
                        found = 0;
                        for (;;) {
                            Vec3 speeds;

                            speeds = grBb_803B8114;
                            found = grBigBlue_801E8794(
                                jobj, &pos, 0,
                                2.0f * (((f32*) &speeds)[(s8) idx] *
                                        Ground_801C0498()),
                                25.0f);
                            if (found == 0) {
                                Vec3 speeds2;
                                speeds2 = grBb_803B8114;
                                found = grBigBlue_801EAB50(
                                    &pos, 0,
                                    2.0f * (((f32*) &speeds2)[(s8) idx] *
                                            Ground_801C0498()),
                                    25.0f);
                            }
                            if (found == 0) {
                                f32 bound =
                                    grBigBlue_801E8D04();
                                if (pos.y <= bound) {
                                    found = 1;
                                }
                            }
                            if (found == 1) {
                                retries += 1;
                                pos.y += 25.0f;
                                if (retries < 3) {
                                    continue;
                                }
                            }
                            break;
                        }
                        if (found != 0) {
                            pos.y = 10.0f +
                                Stage_GetCamBoundsTopOffset();
                        }
                        if (pos.y == -3.4028235e38f) {
                            pos.y = 10.0f +
                                Stage_GetCamBoundsTopOffset();
                        }

                        HSD_JObjSetTranslate(jobj, &pos);
                        gp->gv.bigblue.data[i].xC.z = pos.y;

                        gp->gv.bigblue.data[i].x38 = pos;
                        gp->gv.bigblue.data[i].x44.x =
                            grBb_804D69C8->x98 *
                            (f32) (s8) gp->gv.bigblue.data[i].x2;
                        gp->gv.bigblue.data[i].x44.y = 0.0f;
                        gp->gv.bigblue.data[i].x44.z = 0.0f;
                        gp->gv.bigblue.data[i].x18.z = 0.0f;
                        gp->gv.bigblue.data[i].x18.y = 0.0f;
                        gp->gv.bigblue.data[i].x18.x = 0.0f;
                        gp->gv.bigblue.data[i].x34 = 0;
                        gp->gv.bigblue.data[i].x2C = 0;
                        gp->gv.bigblue.data[i].x1 = 3;
                        HSD_JObjClearFlagsAll(jobj, 0x10);
                        gp->gv.bigblue.data[i].x50 = 0;
                        {
                            s32 chance = grBb_804D69C8->xB8;
                            s32 spawn;
                            if (chance != 0) {
                                spawn = HSD_Randi(chance);
                            } else {
                                spawn = 0;
                            }
                            if (spawn == 0) {
                                grBigBlue_801E8A1C(i);
                            }
                        }
                        base->gv.arwing.xC4 += 1;
                        if ((int) grBigBlue_801E89DC(2) == 0) {
                            u32 cnt = base->gv.arwing.xC4;
                            if ((s32) cnt >=
                                (s32) grBb_804D69C8->x11C)
                            {
                                s32 max = grBb_804D69C8->x120;
                                if ((s32) cnt <= max &&
                                    ((s32) cnt == max ||
                                     HSD_Randi(2) != 0))
                                {
                                    grBigBlue_801E8978(
                                        2, (void*) 1, jobj);
                                }
                            }
                        }
                        if ((int) grBigBlue_801E89DC(1) == 0) {
                            u32 cnt2 = base->gv.arwing.xC4;
                            if ((s32) cnt2 >= (s32) grBb_804D69C8->xDC &&
                                (s32) gp->gv.bigblue.data[i].x2 == 1 &&
                                ((s32) cnt2 >= (s32) grBb_804D69C8->xE0 ||
                                 HSD_Randi(2) != 0))
                            {
                                grBigBlue_801E8978(
                                    0, NULL, NULL);
                                grBigBlue_801E8978(
                                    1, (void*) 1, jobj);
                                base->gv.arwing.xC4 = 0;
                            }
                        }
                    }
                } else {
                    Ground* bone_ptr = base;
                    Ground* other = base;
                    s32 active_count = 0;
                    s32 j;

                    for (j = 0; j < 3; j++) {
                        if (jobj != bone_ptr->gv.bigblue.xD4[j]) {
                            u8 other_state = other->gv.bigblue.data[j].x1;
                            if ((s8) other_state == 3) {
                                if ((gp->gv.bigblue.data[j].x2 == 1 &&
                                     gp->gv.bigblue.data[j].x38.x <
                                         Stage_GetCamBoundsRightOffset()) ||
                                    (gp->gv.bigblue.data[j].x2 == -1 &&
                                     gp->gv.bigblue.data[j].x38.x >
                                         Stage_GetCamBoundsLeftOffset()))
                                {
                                    active_count++;
                                }
                            } else if ((s8) other_state == 1 &&
                                       gp->gv.bigblue.data[j].x4 == 0)
                            {
                                active_count++;
                            }
                        }
                    }

                    if (active_count <= 1) {
                        gp->gv.bigblue.data[i].x8 = 0;
                    } else {
                        gp->gv.bigblue.data[i].x8 -= 1;
                    }
                }
            }
            break;

        case 3:
        {
            Vec3 cur_pos;
            f32 surface_y;
            Point3d normal;
            Vec3 euler;
            Vec3 fwd, back;
            f32 speed_val;

            HSD_JObjGetTranslation(jobj, &cur_pos);
            surface_y = grBigBlue_801EC58C(
                &cur_pos, &normal, 500.0f);
            if (surface_y == -3.4028235e38f) {
                normal.z = 0.0f;
                *(f32*) &normal = 0.0f;
                normal.y = 1.0f;
            }
            euler.y = 0.0f;
            euler.z = 0.0f;
            euler.x = atan2f(
                -*(f32*) &normal, normal.y);

            {
                Vec3 speeds;
                speeds = grBb_803B8114;
                speed_val = (f32) (s8) gp->gv.bigblue.data[i].x2 *
                            (((f32*) &speeds)[(s8) idx] * Ground_801C0498());
            }
            fwd.x = speed_val;
            fwd.z = 0.0f;
            fwd.y = 0.0f;
            lbVector_ApplyEulerRotation(&fwd, &euler);
            lbVector_Add(&fwd, &cur_pos);

            {
                Vec3 speeds2;
                speeds2 = grBb_803B8114;
                speed_val = (f32) - (s8) gp->gv.bigblue.data[i].x2 *
                                        (((f32*) &speeds2)[(s8) idx] *
                                         Ground_801C0498());
            }
            back.x = speed_val;
            back.z = 0.0f;
            back.y = 0.0f;
            lbVector_ApplyEulerRotation(&back, &euler);
            lbVector_Add(&back, &cur_pos);

            {
                s32 sub_state = gp->gv.bigblue.data[i].x2C;
                s32 phase = gp->gv.bigblue.data[i].x34;

                if (sub_state == 0 || phase == 3) {
                    if (gp->gv.bigblue.data[i].x30 == 0 && sub_state != 0) {
                        gp->gv.bigblue.data[i].xC.y = cur_pos.y;
                        gp->gv.bigblue.data[i].x8 = grBb_804D69C8->xB0;
                        gp->gv.bigblue.data[i].x34 = 1;
                    }
                    gp->gv.bigblue.data[i].xC.x = euler.x;
                    {
                        if (HSD_JObjGetRotationZ(jobj) <
                            gp->gv.bigblue.data[i].xC.x)
                        {
                            f32 delta =
                                0.017453292f * (grBb_804D69C8->x9C *
                                                (gp->gv.bigblue.data[i].xC.x -
                                                 HSD_JObjGetRotationZ(jobj)));
                            HSD_JObjAddRotationZ(jobj, delta);
                            if (HSD_JObjGetRotationZ(jobj) >=
                                gp->gv.bigblue.data[i].xC.x)
                            {
                                HSD_JObjSetRotationZ(
                                    jobj, gp->gv.bigblue.data[i].xC.x);
                            }
                        } else {
                            f32 delta =
                                0.017453292f * (grBb_804D69C8->x9C *
                                                (gp->gv.bigblue.data[i].xC.x -
                                                 HSD_JObjGetRotationZ(jobj)));
                            HSD_JObjAddRotationZ(jobj, delta);
                            if (HSD_JObjGetRotationZ(jobj) <=
                                gp->gv.bigblue.data[i].xC.x)
                            {
                                HSD_JObjSetRotationZ(
                                    jobj, gp->gv.bigblue.data[i].xC.x);
                            }
                        }
                    }
                } else {
                    s32 dir_val;

                    if (gp->gv.bigblue.data[i].x30 == 0) {
                        gp->gv.bigblue.data[i].xC.y = cur_pos.y;
                        gp->gv.bigblue.data[i].x8 = grBb_804D69C8->xB0;
                        gp->gv.bigblue.data[i].x34 = 1;
                    }
                    if (gp->gv.bigblue.data[i].x24 <
                        gp->gv.bigblue.data[i].x28)
                    {
                        dir_val = 1;
                    } else {
                        dir_val = -1;
                    }
                    if (gp->gv.bigblue.data[i].x18.y != (f32) dir_val) {
                        gp->gv.bigblue.data[i].x8 = grBb_804D69C8->xB0;
                        gp->gv.bigblue.data[i].x34 = 1;
                    }
                    gp->gv.bigblue.data[i].x18.y = (f32) dir_val;

                    if (phase == 2) {
                        cur_pos.y += gp->gv.bigblue.data[i].x44.y;
                        gp->gv.bigblue.data[i].xC.x = euler.x;
                        {
                            if (HSD_JObjGetRotationZ(jobj) <
                                gp->gv.bigblue.data[i].xC.x)
                            {
                                f32 delta = 0.017453292f *
                                            (grBb_804D69C8->x9C *
                                             (gp->gv.bigblue.data[i].xC.x -
                                              HSD_JObjGetRotationZ(jobj)));
                                HSD_JObjAddRotationZ(
                                    jobj, delta);
                                if (HSD_JObjGetRotationZ(jobj) >=
                                    gp->gv.bigblue.data[i].xC.x)
                                {
                                    HSD_JObjSetRotationZ(
                                        jobj, gp->gv.bigblue.data[i].xC.x);
                                }
                            } else {
                                f32 delta = 0.017453292f *
                                            (grBb_804D69C8->x9C *
                                             (gp->gv.bigblue.data[i].xC.x -
                                              HSD_JObjGetRotationZ(jobj)));
                                HSD_JObjAddRotationZ(
                                    jobj, delta);
                                if (HSD_JObjGetRotationZ(jobj) <=
                                    gp->gv.bigblue.data[i].xC.x)
                                {
                                    HSD_JObjSetRotationZ(
                                        jobj, gp->gv.bigblue.data[i].xC.x);
                                }
                            }
                        }
                        if (cur_pos.y >= gp->gv.bigblue.data[i].xC.y) {
                            gp->gv.bigblue.data[i].x44.y = 0.0f;
                            gp->gv.bigblue.data[i].x18.z = 0.0f;
                            gp->gv.bigblue.data[i].x18.y = 0.0f;
                            gp->gv.bigblue.data[i].x34 = 4;
                        }
                    } else if (gp->gv.bigblue.data[i].x8 <= 0) {
                        gp->gv.bigblue.data[i].x44.y = grBb_804D69C8->xAC;
                        gp->gv.bigblue.data[i].x8 = grBb_804D69C8->xB4;
                        gp->gv.bigblue.data[i].x34 = 3;
                    } else {
                        f32 prev_x = gp->gv.bigblue.data[i].x24;
                        f32 prev_y = gp->gv.bigblue.data[i].x28;

                        if (prev_x < prev_y) {
                            gp->gv.bigblue.data[i].x18.z =
                                grBb_804D69C8->xA0 * (prev_y - prev_x);
                            if (gp->gv.bigblue.data[i].x18.z >=
                                grBb_804D69C8->xA4)
                            {
                                gp->gv.bigblue.data[i].x18.z =
                                    grBb_804D69C8->xA4;
                            }
                            cur_pos.y -= grBb_804D69C8->xA8;
                        } else {
                            gp->gv.bigblue.data[i].x18.z =
                                -grBb_804D69C8->xA0 * (prev_x - prev_y);
                            if (gp->gv.bigblue.data[i].x18.z <=
                                -grBb_804D69C8->xA4)
                            {
                                gp->gv.bigblue.data[i].x18.z =
                                    -grBb_804D69C8->xA4;
                            }
                            cur_pos.y += grBb_804D69C8->xA8;
                        }
                        {
                            f32 delta =
                                0.017453292f * gp->gv.bigblue.data[i].x18.z;
                            HSD_JObjAddRotationZ(jobj, delta);
                        }
                        {
                            f32 angle_deg = 57.29578f *
                                HSD_JObjGetRotationZ(jobj);
                            if (cur_pos.y <
                                (surface_y +
                                 grBb_804D69C8->x90))
                            {
                                if (angle_deg > 30.0f) {
                                    HSD_JObjSetRotationZ(
                                        jobj, 0.5235988f);
                                }
                                if (angle_deg < -30.0f) {
                                    HSD_JObjSetRotationZ(
                                        jobj, -0.5235988f);
                                }
                            }
                            if (angle_deg > 65.0f) {
                                HSD_JObjSetRotationZ(
                                    jobj, 1.1344640f);
                            }
                            if (angle_deg < -65.0f) {
                                HSD_JObjSetRotationZ(
                                    jobj, -1.1344640f);
                            }
                        }
                        gp->gv.bigblue.data[i].x8 -= 1;
                    }
                }
            }

            {
                f32 cam_top = Stage_GetCamBoundsTopOffset();
                f32 cam_bot = Stage_GetCamBoundsBottomOffset();
                f32 speed3;
                Vec3 probe_pos;
                f32 probe_y;
                f32 coll_y;
                s32 coll_result;
                f32 target_y;
                f32 y_diff;
                f32 y_vel;

                {
                    Vec3 speeds3;
                    speeds3 = grBb_803B8114;
                    speed3 = ((f32*) &speeds3)[(s8) idx] * Ground_801C0498();
                }
                {
                    Vec3 speeds4;
                    f32 speed_off4;
                    speeds4 = grBb_803B8114;
                    speed_off4 =
                        ((f32*) &speeds4)[(s8) idx] * Ground_801C0498();
                    target_y = grBigBlue_801E8B84(
                        cam_top, cam_bot,
                        cur_pos.x - (20.0f + speed3),
                        cur_pos.x + (20.0f + speed_off4));
                }

                probe_pos = cur_pos;
                probe_y = grBigBlue_801EC58C(
                    &probe_pos, NULL, 500.0f);

                {
                    Vec3 speeds5;
                    f32 speed_off5;
                    speeds5 = grBb_803B8114;
                    speed_off5 =
                        ((f32*) &speeds5)[(s8) idx] * Ground_801C0498();
                    coll_result = grBigBlue_801EACE8(
                        jobj, &cur_pos, &coll_y,
                        10.0f + speed_off5,
                        16.5f);
                }

                if (coll_result == 0 ||
                    (coll_result == 1 &&
                     cur_pos.y < coll_y))
                {
                    if (target_y <= probe_y) {
                        if (probe_y == -3.4028235e38f) {
                            gp->gv.bigblue.data[i].xC.z = fwd.y;
                        } else {
                            gp->gv.bigblue.data[i].xC.z =
                                probe_y + gp->gv.bigblue.data[i].x8;
                        }
                    } else {
                        gp->gv.bigblue.data[i].xC.z =
                            target_y + gp->gv.bigblue.data[i].x8;
                    }
                } else if (coll_result == 1) {
                    gp->gv.bigblue.data[i].xC.z =
                        cur_pos.y + (cur_pos.y - coll_y);
                }

                target_y = gp->gv.bigblue.data[i].xC.z;
                y_diff = cur_pos.y - target_y;
                if (y_diff < 0.0f) {
                    y_diff = -y_diff;
                }
                if (y_diff < 0.5f) {
                    y_vel = 0.0f;
                } else if (cur_pos.y < target_y) {
                    y_vel = (target_y - cur_pos.y) /
                        grBb_804D69C8->xBC;
                    if (y_vel > grBb_804D69C8->xC0) {
                        y_vel = grBb_804D69C8->xC0;
                    }
                } else {
                    y_vel = (target_y - cur_pos.y) /
                        grBb_804D69C8->xC4;
                    if (y_vel < -grBb_804D69C8->xC8) {
                        y_vel = -grBb_804D69C8->xC8;
                    }
                }
                cur_pos.y += y_vel;
            }

            {
                f32 x_vel = gp->gv.bigblue.data[i].x44.x;
                HSD_JObjAddTranslationX(jobj, x_vel);
            }
            HSD_JObjSetTranslateY(jobj, cur_pos.y);

            gp->gv.bigblue.data[i].x38 = cur_pos;
            gp->gv.bigblue.data[i].x30 = gp->gv.bigblue.data[i].x2C;
            gp->gv.bigblue.data[i].x2C = 0;
            gp->gv.bigblue.data[i].x28 = 0.0f;
            gp->gv.bigblue.data[i].x24 = 0.0f;

            if (gp->gv.bigblue.data[i].x44.x < 0.0f) {
                if (!(HSD_JObjGetTranslationX(jobj) <
                      -((10.0f + Stage_GetBlastZoneRightOffset())
                        - 50.0f)))
                {
                    goto check_positive;
                }
                goto reset_route;
            }
        check_positive:
            if (gp->gv.bigblue.data[i].x44.x > 0.0f) {
                if (HSD_JObjGetTranslationX(jobj) >
                    (10.0f + Stage_GetBlastZoneRightOffset())
                    - 50.0f)
                {
                reset_route:
                    HSD_JObjSetFlagsAll(jobj, 0x10);
                    HSD_JObjSetRotationZ(jobj, 0.0f);
                    gp->gv.bigblue.data[i].x44.x = 0.0f;
                    gp->gv.bigblue.data[i].x44.y = 0.0f;
                    gp->gv.bigblue.data[i].x44.z = 0.0f;
                    gp->gv.bigblue.data[i].x18.z = 0.0f;
                    gp->gv.bigblue.data[i].x18.y = 0.0f;
                    gp->gv.bigblue.data[i].x18.x = 0.0f;
                    gp->gv.bigblue.data[i].xC.x = 0.0f;
                    gp->gv.bigblue.data[i].x34 = 0;
                    gp->gv.bigblue.data[i].x2C = 0;
                    {
                        s32 range = grBb_804D69C8->x8C;
                        s32 rand_val;
                        if (range != 0) {
                            rand_val = HSD_Randi(range);
                        } else {
                            rand_val = 0;
                        }
                        gp->gv.bigblue.data[i].x4 =
                            (grBb_804D69C8->x88 + rand_val) / 2;
                    }
                    gp->gv.bigblue.data[i].x1 = 1;
                }
            }
            break;
        }
        }
        i++;
    } while (i < 3);

    Ground_801C2FE0(gobj);
}

void grBigBlue_801E855C(Ground_GObj* arg) {}

void fn_801E8560(Ground* gp, s32 param, CollData* coll, s32 time_param,
                 s32 env, f32 force)
{
    HSD_JObj* jobj;
    s32 joint_index;
    Vec3 pos;
    f32 dist;
    s32 active_joint;
    PAD_STACK(0x10);

    if ((s32) coll->x34_flags.b1234 != 1 && (s32) coll->x34_flags.b1234 != 3) {
        return;
    }

    if (param == 0) {
        joint_index = 0;
    }
    if (param == 1) {
        joint_index = 1;
    }
    if (param == 2) {
        joint_index = 2;
    }

    jobj = gp->gv.bigblue.xD4[joint_index];

    if ((f32) time_param > 1000.0F) {
        time_param = 1000;
    }

    HSD_JObjGetTranslation2(jobj, &pos);

    {
        f32 dx = pos.x - coll->cur_pos.x;
        f32 dy = pos.y - coll->cur_pos.y;
        dist = sqrtf(dy * dy + dx * dx);
    }

    if (dist > 2.0F) {
        int i;
        active_joint = 0;
        for (i = 0; i < 3; i++) {
            if ((s8) gp->gv.bigblue.data[i].index == joint_index) {
                break;
            }
            active_joint = i + 1;
        }

        if (pos.x < coll->cur_pos.x) {
            gp->gv.bigblue.data[active_joint].x24 +=
                dist * ((f32) time_param / 1000.0F);
        } else {
            gp->gv.bigblue.data[active_joint].x28 +=
                dist * ((f32) time_param / 1000.0F);
        }

        gp->gv.bigblue.data[active_joint].x2C++;
    }
}

bool grBigBlue_801E8794(void* exclude, Vec3* pos, bool checkSecondary,
                        f32 rangeX, f32 rangeY)
{
    Ground* gp = GET_GROUND(Ground_801C2BA4(32));
    bool result = false;
    int i;
    f32 dist;

    for (i = 0; i < 3; i++) {
        if (exclude == gp->gv.bigblue.xD4[i]) {
            continue;
        }

        if ((s32) gp->gv.bigblue.data[i].x1 != 3) {
            continue;
        }

        dist = HSD_JObjGetTranslationX(gp->gv.bigblue.xD4[i]) - pos->x;
        if (dist < 0.0F) {
            dist = -(HSD_JObjGetTranslationX(gp->gv.bigblue.xD4[i]) - pos->x);
        } else {
            dist = HSD_JObjGetTranslationX(gp->gv.bigblue.xD4[i]) - pos->x;
        }

        if (dist < rangeX) {
            dist = HSD_JObjGetTranslationY(gp->gv.bigblue.xD4[i]) - pos->y;
            if (dist < 0.0F) {
                dist =
                    -(HSD_JObjGetTranslationY(gp->gv.bigblue.xD4[i]) - pos->y);
            } else {
                dist = HSD_JObjGetTranslationY(gp->gv.bigblue.xD4[i]) - pos->y;
            }

            if (dist < rangeY) {
                result = true;
                break;
            }
        }

        if (checkSecondary && gp->gv.bigblue.data[i].x2 == -1) {
            result = true;
            break;
        }
    }

    return result;
}

void grBigBlue_801E8978(int index, void* data, void* extra)
{
    u8* gp = (u8*) GET_GROUND(Ground_801C2BA4(32));
    if (extra != NULL) {
        *(void**) (gp + 0xE0) = extra;
    }
    gp += index * 4;
    *(void**) (gp + 0xC8) = data;
}

void* grBigBlue_801E89DC(int arg)
{
    u8* gp = (u8*) GET_GROUND(Ground_801C2BA4(32));
    gp += arg * 4;
    return *(void**) (gp + 0xC8);
}

/// @todo Currently 79.9% match - platform/store use lwzx/stwx instead of
/// add+lwz/stw (addressing mode difference), candPtr init missing slwi+add
void grBigBlue_801E8A1C(int idx)
{
    u8* gp = (u8*) GET_GROUND(Ground_801C2BA4(32));
    HSD_JObj* platform = *(HSD_JObj**) (gp + idx * 4 + 0xD4);
    ItemKind* candPtr;
    ItemKind* validPtr;
    int i;
    int validCount = 0;
    BobOmbRain spawn;
    ItemKind candidates[5];
    ItemKind valid[5];

    candidates[0] = grBb_803B8120[0];
    candidates[1] = grBb_803B8120[1];
    i = 0;
    candPtr = candidates + i;
    candidates[2] = grBb_803B8120[2];
    candidates[3] = grBb_803B8120[3];
    validPtr = valid;
    candidates[4] = grBb_803B8120[4];

    spawn.x0 = NULL;
    spawn.x4 = NULL;

    do {
        if (it_8026D324(*candPtr)) {
            *validPtr = *candPtr;
            validCount++;
            validPtr++;
        }
        i++;
        candPtr++;
    } while (i < 5);

    if (validCount != 0) {
        spawn.x14 = valid[HSD_Randi(validCount)];
        HSD_ASSERT(979, platform != NULL);

        spawn.x8_vec = platform->translate;

        if (spawn.x14 == 4) {
            spawn.x8_vec.y += 15.0F;
        } else {
            spawn.x8_vec.y += 10.0F;
        }

        spawn.x1C.b0 = 1;
        *(HSD_GObj**) (gp + idx * 0x54 + 0x134) = it_8026BE84(&spawn);
    }
}

/// @todo Currently 94.71% match - needs pointer advancement and i variable
f32 grBigBlue_801E8B84(f32 right, f32 left, f32 bottom, f32 top)
{
    u8* gp = (u8*) GET_GROUND(Ground_801C2BA4(33));
    int i = 0;
    f32 result = 0.0F;

    for (i = 0; i < 4; i++) {
        if ((unsigned) (gp[0xD4] >> 2 & 0x3F) != 1U) {
            if (*(f32*) (gp + 0xE4) < right && *(f32*) (gp + 0xE4) > left) {
                if (*(f32*) (gp + 0xE0) < top && *(f32*) (gp + 0xE0) > bottom)
                {
                    if (*(f32*) (gp + 0xE4) > result) {
                        result = *(f32*) (gp + 0xE4);
                    }
                }
            }
        }
        gp += 0x40;
    }

    return result;
}

f32 grBigBlue_801E8D04(void)
{
    f32 val4, val3, val2, val1;
    val1 = Stage_GetCamBoundsRightOffset();
    val2 = Stage_GetCamBoundsLeftOffset();
    val3 = Stage_GetCamBoundsBottomOffset();
    val4 = Stage_GetCamBoundsTopOffset();
    return grBigBlue_801E8B84(val4, val3, val2, val1);
}

void grBigBlue_801E8D64(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = gobj->hsd_obj;
    Vec3 pos;
    Vec3 scale;
    Vec3 translate;
    f32 y_pos;
    PAD_STACK(0x10);

    Ground_801C2ED0(jobj, gp->map_id);
    gp->x10_flags.b5 = 1;

    scale.x = scale.y = scale.z = Ground_801C0498();
    HSD_JObjSetScale(jobj, &scale);

    {
        HSD_GObj* other = Ground_801C2BA4(32);
        Ground* other_gp = other->user_data;
        *(s32*) ((u8*) other_gp + 0xCC) = 1;
    }

    y_pos = grBigBlue_801EC58C(&pos, NULL, grBb_804DB30C);
    if (grBb_804DB310 == y_pos) {
        y_pos = grBb_804DB2F4;
    }

    HSD_JObjSetTranslateX(jobj, 0.0F);

    y_pos += grBb_804D69C8->xCC;
    HSD_JObjSetTranslateY(jobj, y_pos);

    HSD_JObjSetTranslateZ(jobj, 0.0F);

    *(f32*) ((u8*) gp + 0xD8) = 0.0F;
    *(s32*) ((u8*) gp + 0xC8) = (s32) (grBb_804D69C8->xD8);
    *(u8*) ((u8*) gp + 0xC4) = 2;

    grAnime_801C8138(gobj, gp->map_id, 0);

    HSD_JObjGetTranslation2(jobj, &pos);
    {
        f32 inv = 1.0F / Ground_801C0498();
        pos.x *= inv;
        pos.y *= inv;
        pos.z *= inv;
    }

    HSD_JObjGetTranslation2(Ground_801C2CF4(0), &translate);
    lbVector_Add(&translate, &pos);
    HSD_JObjSetTranslate(Ground_801C2CF4(0), &translate);

    HSD_JObjGetTranslation2(Ground_801C2CF4(1), &translate);
    lbVector_Add(&translate, &pos);
    HSD_JObjSetTranslate(Ground_801C2CF4(1), &translate);

    HSD_JObjGetTranslation2(Ground_801C2CF4(2), &translate);
    lbVector_Add(&translate, &pos);
    HSD_JObjSetTranslate(Ground_801C2CF4(2), &translate);

    HSD_JObjGetTranslation2(Ground_801C2CF4(3), &translate);
    lbVector_Add(&translate, &pos);
    HSD_JObjSetTranslate(Ground_801C2CF4(3), &translate);
}

bool grBigBlue_801E93D0(Ground_GObj* arg)
{
    return false;
}

void grBigBlue_801E93D8(Ground_GObj* gobj)
{
    Vec3 pos;
    Vec3 fwd;
    Vec3 back;
    Vec3 normal;
    Vec3 euler;
    s32 _pad_9C;
    Vec3 check_pos;
    Ground* gp = gobj->user_data;
    HSD_JObj* jobj = GET_JOBJ(gobj);
    u8* bp = (u8*) gp;
    PAD_STACK(76);

    HSD_JObjGetTranslation2(jobj, &pos);

    if (grBigBlue_801EC58C(&pos, &normal, 500.0f) == -3.4028235e38f) {
        normal.z = 0.0f;
        normal.x = 0.0f;
        normal.y = 1.0f;
    }

    euler.y = 0.0f;
    euler.x = 0.0f;
    euler.z = atan2f(-normal.x, normal.y);

    fwd.x = 50.0f;
    fwd.z = 0.0f;
    fwd.y = 0.0f;
    lbVector_ApplyEulerRotation(&fwd, &euler);
    lbVector_Add(&fwd, &pos);

    back.x = -50.0f;
    back.z = 0.0f;
    back.y = 0.0f;
    lbVector_ApplyEulerRotation(&back, &euler);
    lbVector_Add(&back, &pos);

    switch ((s8) bp[0xC4]) {
    case 0:
    {
        if (*(s32*) ((u8*) Ground_801C2BA4(32)->user_data + 0xCC) != 0) {
            u32 cars_avail = 0;
            u8* mgp = (u8*) Ground_801C2BA4(32)->user_data;
            s32 count = 0;

            if ((s8) mgp[0xE5] != 0) {
                count = 1;
                if (cars_avail != 0U) {
                    cars_avail =
                        *(u32*)(mgp + ((s8) mgp[0xE4] * 4) + 0xD4);
                }
            }
            {
                u8* p = mgp + 0x54;
                if ((s8) mgp[0x139] != 0) {
                    count++;
                    if (cars_avail != 0U) {
                        cars_avail =
                            *(u32*)(mgp + ((s8) p[0xE4] * 4) + 0xD4);
                    }
                }
                if ((s8) p[0x139] != 0) {
                    if (cars_avail != 0U) {
                    }
                    count++;
                }
            }

            if (count <= 1) {
                f32 height;

                memzero(&pos, 0xC);
                pos.x = Stage_GetBlastZoneLeftOffset() - 50.0f;
                height = grBigBlue_801EC58C(&pos, NULL, 500.0f);
                if (height != -3.4028235e38f) {
                    f32 speed;
                    s32 collided;

                    pos.y = height + grBb_804D69C8->xCC;
                    speed = 140.0f * Ground_801C0498();
                    collided = grBigBlue_801E8794(jobj, &pos, 1,
                        2.0f * (60.0f * Ground_801C0498()), speed);
                    if (collided == 0) {
                        collided = grBigBlue_801EAB50(&pos, 1,
                            2.0f * (60.0f * Ground_801C0498()), 25.0f);
                    }
                    if (collided == 0) {
                        f32 cam_right = Stage_GetCamBoundsRightOffset();
                        f32 cam_left = Stage_GetCamBoundsLeftOffset();
                        f32 cam_bot = Stage_GetCamBoundsBottomOffset();
                        if (pos.y <= grBigBlue_801E8B84(
                                Stage_GetCamBoundsTopOffset(), cam_bot,
                                cam_left, cam_right))
                        {
                            collided = 1;
                        }
                    }
                    if (collided != 0) {
                        pos.y = 30.0f + Stage_GetCamBoundsTopOffset();
                    }
                    if (pos.y == -3.4028235e38f) {
                        HSD_ASSERTREPORT(0x6CB, NULL, "%d %f\n", collided,
                                         (double) -3.4028235e38f);
                    }
                    HSD_JObjSetTranslate(jobj, &pos);
                    *(f32*)(bp + 0xD0) = pos.y;
                    *(f32*)(bp + 0xD8) = grBb_804D69C8->xD0;
                    HSD_JObjClearFlagsAll(jobj, 0x10U);
                    bp[0xC4] = 1;
                }
            }
        }
        break;
    }
    case 1:
        if (pos.x > 0.0f) {
            *(f32*)(bp + 0xD8) = 0.0f;
            *(s32*)(bp + 0xC8) = (s32) grBb_804D69C8->xD8;
            bp[0xC4] = 2;
        } else {
            f32 speed2 = 140.0f * Ground_801C0498();
            if (grBigBlue_801E8794(jobj, &pos, 1,
                    (60.0f * Ground_801C0498()) + 30.0f, speed2) != 0 ||
                grBigBlue_801EAB50(&pos, 1,
                    (60.0f * Ground_801C0498()) + 30.0f,
                    140.0f * Ground_801C0498()) != 0)
            {
                *(f32*)(bp + 0xD8) = 0.0f;
            } else {
                *(f32*)(bp + 0xD8) = grBb_804D69C8->xD0;
            }
        }
        goto block_76;
    case 2:
    {
        s32 timer = *(s32*)(bp + 0xC8);
        if (timer <= 0) {
            u8* mgp = (u8*) Ground_801C2BA4(32)->user_data;
            s32 ctr = 3;
            s32 idx = 0;
            u8* p = mgp;

            *(f32*)(bp + 0xD8) = grBb_804D69C8->xD0;
            bp[0xC4] = 3;

        route_loop:
            if ((s8) p[0xE5] == 0) {
                u8* slot = mgp + (idx * 0x54);
                slot[0xE5] = 2;
                *(s32*)(slot + 0xE8) = 0;
            } else {
                p += 0x54;
                idx++;
                ctr--;
                if (ctr != 0) {
                    goto route_loop;
                }
            }
        } else {
            *(s32*)(bp + 0xC8) = timer - 1;
        }
        goto block_76;
    }
    case 3:
        if (pos.x > (50.0f + Stage_GetBlastZoneRightOffset())) {
            HSD_JObjSetFlagsAll(jobj, 0x10U);
            *(f32*)(bp + 0xD8) = 0.0f;
            *(s32*) ((u8*) Ground_801C2BA4(32)->user_data + 0xCC) = 0;
            {
                u8* mgp2 = (u8*) Ground_801C2BA4(32)->user_data;
                if (jobj != NULL) {
                    *(u32*)(mgp2 + 0xE0) = (u32) jobj;
                }
                *(s32*)(mgp2 + 0xC8) = 1;
            }
            *(f32*)(bp + 0xCC) = 0.0f;
            HSD_JObjSetRotationZ(jobj, 0.0f);
            bp[0xC4] = 0;
        }
        goto block_76;
    default:
    block_76:
    {
        f32 target_z;
        f32 cur_z;
        f32 delta;
        f32 target_y;
        f32 diff_y;
        f32 vy;
        f32 bound_y;
        f32 check_h;

        target_z = euler.z;
        *(f32*)(bp + 0xCC) = target_z;
        cur_z = HSD_JObjGetRotationZ(jobj);
        if (cur_z < *(f32*)(bp + 0xCC)) {
            delta = 0.017453292f *
                    (grBb_804D69C8->xD4 * (*(f32*) (bp + 0xCC) - cur_z));
            HSD_JObjAddRotationZ(jobj, delta);
            if (HSD_JObjGetRotationZ(jobj) >=
                *(f32*)(bp + 0xCC))
            {
                HSD_JObjSetRotationZ(jobj, *(f32*)(bp + 0xCC));
            }
        } else {
            delta = 0.017453292f *
                    (grBb_804D69C8->xD4 *
                     (*(f32*) (bp + 0xCC) - HSD_JObjGetRotationZ(jobj)));
            HSD_JObjAddRotationZ(jobj, delta);
            if (HSD_JObjGetRotationZ(jobj) <=
                *(f32*)(bp + 0xCC))
            {
                HSD_JObjSetRotationZ(jobj, *(f32*)(bp + 0xCC));
            }
        }

        {
            f32 cam_right2 = Stage_GetCamBoundsRightOffset();
            f32 cam_left2 = Stage_GetCamBoundsLeftOffset();
            f32 cam_bot2 = Stage_GetCamBoundsBottomOffset();
            bound_y = grBigBlue_801E8B84(
                Stage_GetCamBoundsTopOffset(), cam_bot2,
                cam_left2, cam_right2);
        }
        check_pos = pos;
        check_h = grBigBlue_801EC58C(&check_pos, NULL, 500.0f);
        if (bound_y <= check_h) {
            if (check_h == -3.4028235e38f) {
                *(f32*)(bp + 0xD0) = fwd.y;
            } else {
                *(f32*)(bp + 0xD0) = check_h + grBb_804D69C8->xCC;
            }
        } else {
            *(f32*)(bp + 0xD0) = bound_y + grBb_804D69C8->xCC;
        }

        target_y = *(f32*)(bp + 0xD0);
        diff_y = pos.y - target_y;
        if (diff_y < 0.0f) {
            diff_y = -diff_y;
        }
        if (diff_y < 0.5f) {
            vy = 0.0f;
        } else if (pos.y < target_y) {
            vy = (target_y - pos.y) / grBb_804D69C8->xE4;
            if (vy > grBb_804D69C8->xE8) {
                vy = grBb_804D69C8->xE8;
            }
        } else {
            vy = (target_y - pos.y) / grBb_804D69C8->xEC;
            if (vy < -grBb_804D69C8->xF0) {
                vy = -grBb_804D69C8->xF0;
            }
        }
        pos.y += vy;

        HSD_JObjAddTranslationX(jobj, *(f32*)(bp + 0xD8));
        HSD_JObjSetTranslateY(jobj, pos.y);
        break;
    }
    }
    Ground_801C2FE0(gobj);
}

void grBigBlue_801E9F38(Ground_GObj* arg) {}

void grBigBlue_801E9F3C(Ground_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Ground* gp = gobj->user_data;
    Vec3 v;
    PAD_STACK(8);

    Ground_801C2ED0(jobj, gp->map_id);
    gp->x10_flags.b5 = 1;

    v.x = v.y = v.z = Ground_801C0498();

    HSD_JObjSetScale(jobj, &v);

    ((u8*) gp)[0xC4] = 0;
    *(s32*) ((u8*) GET_GROUND(Ground_801C2BA4(32)) + 0xD0) = 0;
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grBigBlue_801EA054(Ground_GObj* arg)
{
    return false;
}

void grBigBlue_801EA05C(Ground_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Ground* gp = GET_GROUND(gobj);
    Vec3 pos;
    Vec3 half_top;
    Vec3 half_bot;
    Vec3 normal;
    Vec3 euler;
    Vec3 pos2;
    f32 y_check;
    PAD_STACK(0x1c);

    HSD_JObjGetTranslation2(jobj, &pos);

    if (grBigBlue_801EC58C(&pos, &normal, 500.0f) == grBb_804DB310) {
        normal.z = 0.0f;
        normal.x = 0.0f;
        normal.y = 1.0f;
    }

    euler.y = 0.0f;
    euler.x = 0.0f;
    euler.z = atan2f(-normal.x, normal.y);

    half_top.x = 68.0f * Ground_801C0498() * 0.5f;
    half_top.z = 0.0f;
    half_top.y = 0.0f;
    lbVector_ApplyEulerRotation(&half_top, &euler);
    lbVector_Add(&half_top, &pos);

    half_bot.x = -(68.0f * Ground_801C0498() * 0.5f);
    half_bot.z = 0.0f;
    half_bot.y = 0.0f;
    lbVector_ApplyEulerRotation(&half_bot, &euler);
    lbVector_Add(&half_bot, &pos);

    switch (gp->gv.bigblue.x0_w) {
    case 0:
        if (*(s32*) ((u8*) GET_GROUND(Ground_801C2BA4(32)) + 0xD0) != 0) {
            *(s32*) (gp + 0xC8) = 0;
            *(s32*) (gp + 0xD0) = 0;
            *(s32*) (gp + 0xCC) = 0;
            gp->gv.bigblue.x0_w = 1;
        }
        break;

    case 1:
    {
        s32 timer = *(s32*) (gp + 0xC8);
        if (timer <= 0) {
            f32 right_y;
            f32 left_y;
            f32 range;
            s32 r;

            memzero(&pos, 0xC);
            memzero(&half_bot, 0xC);
            pos.x = Stage_GetBlastZoneRightOffset();
            half_bot.x = -Stage_GetBlastZoneRightOffset();

            right_y = grBigBlue_801EC58C(&pos, NULL, 500.0f);
            left_y = grBigBlue_801EC58C(&half_bot, NULL, 500.0f);

            *(f32*) (gp + 0xD4) = grBb_804D69C8->xF4;
            range = grBb_804D69C8->xF8 - grBb_804D69C8->xF4;
            if (range < 0.0f) {
                range = -range;
            }
            if ((s32) range != 0) {
                r = HSD_Randi((s32) range);
            } else {
                r = 0;
            }
            *(f32*) (gp + 0xD4) = *(f32*) (gp + 0xD4) + (f32) r;

            pos.y = right_y + *(f32*) (gp + 0xD4);
            half_bot.y = left_y + *(f32*) (gp + 0xD4);

            if (right_y != grBb_804DB310 || left_y != grBb_804DB310) {
                s32 collision;
                f32 platform_h;
                f32 bounds_y;

                if (left_y == grBb_804DB310) {
                    gp->gv.bigblue.x1 = (u8) (s8) -1;
                } else if (right_y == grBb_804DB310) {
                    gp->gv.bigblue.x1 = 1;
                } else {
                    f32 diff = right_y - left_y;
                    if (diff < 0.0f) {
                        diff = -diff;
                    }
                    if (diff < 80.0f) {
                        s8 dir;
                        if (HSD_Randi(2) != 0) {
                            dir = 1;
                        } else {
                            dir = -1;
                        }
                        gp->gv.bigblue.x1 = (u8) dir;
                    } else {
                        s8 dir;
                        if (right_y < left_y) {
                            dir = -1;
                        } else {
                            dir = 1;
                        }
                        gp->gv.bigblue.x1 = (u8) dir;
                    }
                }

                if ((s8) gp->gv.bigblue.x1 == 1) {
                    pos.x = half_bot.x;
                    pos.y = half_bot.y;
                    pos.z = half_bot.z;
                }

                platform_h = 52.0f * Ground_801C0498();
                collision = grBigBlue_801E8794(jobj, &pos, 0,
                    2.0f * (68.0f * Ground_801C0498()), platform_h);

                if (collision == 0) {
                    f32 cam_top = Stage_GetCamBoundsTopOffset();
                    f32 cam_bot = Stage_GetCamBoundsBottomOffset();
                    f32 cam_left = Stage_GetCamBoundsLeftOffset();
                    f32 cam_right = Stage_GetCamBoundsRightOffset();
                    bounds_y = grBigBlue_801E8B84(cam_top, cam_bot,
                                                  cam_left, cam_right);
                    if (pos.y <= bounds_y) {
                        collision = 1;
                    }
                }

                if (collision == 0) {
                    if (pos.y == grBb_804DB310) {
                        HSD_ASSERTREPORT(
                            0x7CA, NULL, "%s:%d: fly spawn error! (%d/%f)\n",
                            "grbigblue.c", 0x7CA, 0, grBb_804DB310);
                    }

                    HSD_JObjSetTranslate(jobj, &pos);

                    *(f32*) (gp + 0xDC) = pos.y;
                    *(f32*) (gp + 0xEC) = 0.0f;
                    *(f32*) (gp + 0xE8) = 0.0f;
                    *(f32*) (gp + 0xE4) = 0.0f;

                    HSD_JObjClearFlagsAll(jobj, 0x10);
                    gp->gv.bigblue.x0_w = 2;
                }
            }
        } else {
            *(s32*) (gp + 0xC8) = timer - 1;
        }
        break;
    }

    case 2:
    {
        f32 cam_top = Stage_GetCamBoundsTopOffset();
        f32 cam_bot = Stage_GetCamBoundsBottomOffset();
        f32 left_x = pos.x - (68.0f * Ground_801C0498() * 0.5f + 20.0f);
        f32 bounds_y = grBigBlue_801E8B84(cam_top, cam_bot, left_x,
            pos.x + (68.0f * Ground_801C0498() * 0.5f + 20.0f));
        f32 surface_y;
        f32 half_h;
        s32 ace_result;
        f32 vel_y;

        pos2 = pos;

        surface_y = grBigBlue_801EC58C(&pos2, NULL, 500.0f);

        half_h = 52.0f * Ground_801C0498() * 0.5f + 4.0f;
        ace_result = grBigBlue_801EACE8(jobj, &pos, &y_check,
            68.0f * Ground_801C0498() * 0.5f + 10.0f, half_h);

        if (ace_result == 0 ||
            (ace_result == 1 && pos.y < y_check))
        {
            if (bounds_y <= surface_y) {
                if (surface_y == grBb_804DB310) {
                    *(f32*) (gp + 0xDC) = half_top.y;
                } else {
                    *(f32*) (gp + 0xDC) =
                        surface_y + *(f32*) (gp + 0xD4);
                }
            } else {
                *(f32*) (gp + 0xDC) =
                    bounds_y + *(f32*) (gp + 0xD4);
            }
        } else if (ace_result == 1) {
            *(f32*) (gp + 0xDC) = pos.y + (pos.y - y_check);
        }

        {
            f32 target_y = *(f32*) (gp + 0xDC);
            f32 diff = pos.y - target_y;
            if (diff < 0.0f) {
                diff = -diff;
            }
            if (diff < 0.5f) {
                vel_y = 0.0f;
            } else if (pos.y < target_y) {
                f32 max = grBb_804D69C8->x128;
                vel_y = (target_y - pos.y) / grBb_804D69C8->x124;
                if (vel_y > max) {
                    vel_y = max;
                }
            } else {
                f32 min = -grBb_804D69C8->x130;
                vel_y = (target_y - pos.y) / grBb_804D69C8->x12C;
                if (vel_y < min) {
                    vel_y = min;
                }
            }
        }

        pos.y += vel_y;
        HSD_JObjSetTranslateY(jobj, pos.y);

        {
            s32 timer = *(s32*) (gp + 0xCC);
            if (timer <= 0) {
                s32 timer_range = grBb_804D69C8->x110 - grBb_804D69C8->x10C;
                s32 r;
                f32 speed_range;
                s32 speed_r;
                f32 speed;

                if (timer_range < 0) {
                    timer_range = -timer_range;
                }
                if (timer_range != 0) {
                    r = HSD_Randi(timer_range);
                } else {
                    r = 0;
                }
                *(s32*) (gp + 0xCC) = r;
                *(s32*) (gp + 0xCC) += grBb_804D69C8->x10C;

                speed_range =
                    (grBb_804D69C8->x100 - grBb_804D69C8->xFC) / 0.1f;
                if ((s32) speed_range != 0) {
                    speed_r = HSD_Randi((s32) speed_range);
                } else {
                    speed_r = 0;
                }
                speed = (f32) speed_r * 0.1f;
                if (speed == 0.0f) {
                    speed = grBb_804D69C8->xFC;
                }
                *(f32*) (gp + 0xE4) = speed * (f32) (s8) gp->gv.bigblue.x1;
            } else {
                *(s32*) (gp + 0xCC) = timer - 1;
            }
        }

        {
            s32 timer = *(s32*) (gp + 0xD0);
            if (timer <= 0) {
                s32 timer_range = grBb_804D69C8->x110 - grBb_804D69C8->x10C;
                s32 r;
                f32 speed_range;
                s32 speed_r;
                f32 speed;

                if (timer_range < 0) {
                    timer_range = -timer_range;
                }
                if (timer_range != 0) {
                    r = HSD_Randi(timer_range);
                } else {
                    r = 0;
                }
                *(s32*) (gp + 0xD0) = r;
                *(s32*) (gp + 0xD0) += grBb_804D69C8->x10C;

                speed_range =
                    (grBb_804D69C8->x108 - grBb_804D69C8->x104) / 0.1f;
                if ((s32) speed_range != 0) {
                    speed_r = HSD_Randi((s32) speed_range);
                } else {
                    speed_r = 0;
                }
                speed = (f32) speed_r * 0.1f;
                if (speed == 0.0f) {
                    speed = grBb_804D69C8->x104;
                }
                if (HSD_Randi(2) != 0) {
                    speed *= -1.0f;
                }
                *(f32*) (gp + 0xE8) = speed;
            } else {
                *(s32*) (gp + 0xD0) = timer - 1;
            }
        }

        HSD_JObjAddTranslationX(jobj, *(f32*) (gp + 0xE4));
        HSD_JObjAddTranslationY(jobj, *(f32*) (gp + 0xE8));

        if (((s8) gp->gv.bigblue.x1 == -1 &&
             HSD_JObjGetTranslationX(jobj) <
                 -(Stage_GetBlastZoneRightOffset() - 50.0f)) ||
            ((s8) gp->gv.bigblue.x1 == 1 &&
             HSD_JObjGetTranslationX(jobj) >
                 Stage_GetBlastZoneRightOffset() - 50.0f))
        {
            HSD_JObjSetFlagsAll(jobj, 0x10);
            *(f32*) (gp + 0xEC) = 0.0f;
            *(f32*) (gp + 0xE8) = 0.0f;
            *(f32*) (gp + 0xE4) = 0.0f;
            GET_GROUND(Ground_801C2BA4(32))->gv.bigblue.xD0 = 0;
            gp->gv.bigblue.x0_w = 0;
        }
        break;
    }
    }

    Ground_801C2FE0(gobj);
}

void grBigBlue_801EAB4C(Ground_GObj* arg) {}

bool grBigBlue_801EAB50(Vec3* pos, s32 flag, f32 rangeX, f32 rangeY)
{
    HSD_GObj* gobj = Ground_801C2BA4(32);
    Ground* gp = gobj->user_data;
    HSD_JObj* jobj = GET_JOBJ(gobj);
    s32 result = false;
    f32 dist;
    PAD_STACK(32);

    if ((s8) gp->gv.bigblue.x0 == 2) {
        dist = HSD_JObjGetTranslationX(jobj) - pos->x;
        if (dist < 0.0F) {
            dist = -(HSD_JObjGetTranslationX(jobj) - pos->x);
        } else {
            dist = HSD_JObjGetTranslationX(jobj) - pos->x;
        }

        if (dist < rangeX) {
            dist = HSD_JObjGetTranslationY(jobj) - pos->y;
            if (dist < 0.0F) {
                dist = -(HSD_JObjGetTranslationY(jobj) - pos->y);
            } else {
                dist = HSD_JObjGetTranslationY(jobj) - pos->y;
            }

            if (dist < rangeY) {
                result = true;
            }
        }

        if (flag != 0) {
            if ((s8) gp->gv.bigblue.x1 == -1) {
                result = true;
            }
        }
    }

    return result;
}

/// @todo Currently 98.17% match - car section generates fnmsubs instead of
/// fmuls+fsubs; compiler fuses multiply-subtract differently than target
s32 grBigBlue_801EACE8(HSD_JObj* exclude, Vec3* point, f32* out_y,
                       f32 half_range_x, f32 half_range_y)
{
    HSD_GObj* gobj;
    Ground* gp;
    HSD_JObj* jobj;
    Vec3 pos;
    Vec3 hw_left, hw_right;
    Vec3 route_pos;
    f32 best_in_range, best_above;
    f32 left_bound, right_bound, top_bound, bottom_bound;
    f32 left_x, right_x;
    f32 dist;
    f32* p_left;
    f32* p_right;
    s32 i;
    PAD_STACK(0x24);

    gobj = Ground_801C2BA4(32);

    left_bound = point->x - half_range_x;
    right_bound = point->x + half_range_x;
    top_bound = point->y + half_range_y;
    bottom_bound = point->y - half_range_y;

    best_in_range = F32_MAX;
    best_above = -F32_MAX;

    gp = gobj->user_data;
    p_left = &hw_left.x;
    p_right = &hw_right.x;

    for (i = 0; i < 3; i++, p_left++, p_right++) {
        jobj = gp->gv.bigblue.xD4[i];

        if (exclude == jobj) {
            continue;
        }

        if ((int) ((u8*) gp)[0xE5 + i * 0x54] != 3) {
            continue;
        }

        HSD_JObjGetTranslation2(jobj, &pos);

        hw_left = grBb_803B8114;
        left_x = *p_left * Ground_801C0498();
        left_x = pos.x - left_x;

        hw_right = grBb_803B8114;
        right_x = *p_right * Ground_801C0498();
        right_x = pos.x + right_x;

        if ((right_x > left_bound && right_x < right_bound) ||
            (left_x < right_bound && left_x > left_bound))
        {
            if (pos.y > bottom_bound && pos.y < top_bound) {
                dist = point->y - pos.y;
                if (dist < 0.0F) {
                    dist = -dist;
                }
                if (dist < best_in_range) {
                    best_in_range = pos.y;
                }
            } else if (point->y > pos.y && pos.y > best_above) {
                best_above = pos.y;
            }
        }
    }

    /* Route platform */
    gobj = Ground_801C2BA4(36);
    jobj = (HSD_JObj*) gobj->hsd_obj;
    gp = gobj->user_data;

    if (exclude != jobj && (int) gp->gv.bigblue.x0 == 2) {
        HSD_JObjGetTranslation2(jobj, &route_pos);

        left_x = route_pos.x - 68.0F * Ground_801C0498() * 0.5F;
        right_x = route_pos.x + 68.0F * Ground_801C0498() * 0.5F;

        if ((right_x > left_bound && right_x < right_bound) ||
            (left_x < right_bound && left_x > left_bound))
        {
            if (route_pos.y > bottom_bound && route_pos.y < top_bound) {
                dist = point->y - route_pos.y;
                if (dist < 0.0F) {
                    dist = -dist;
                }
                if (dist < best_in_range) {
                    best_in_range = route_pos.y;
                }
            } else if (point->y > route_pos.y && route_pos.y > best_above) {
                best_above = route_pos.y;
            }
        }
    }

    if (F32_MAX != best_in_range) {
        *out_y = best_in_range;
        return 1;
    }
    if (-F32_MAX != best_above) {
        *out_y = best_above;
        return 2;
    }
    return 0;
}

/// @todo Currently 94.90% match - needs bitfield struct for rlwimi
/// generation and stack frame fix (120 vs 112 bytes)
void grBigBlue_801EB004(Ground_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Ground* gp = (Ground*) gobj->user_data;
    Vec3 pos;
    Vec3 scale;
    Vec3 diff;
    Vec3 start_pos;
    Vec3 end_pos;
    HSD_JObj* child;
    HSD_JObj* start_jobj;
    HSD_JObj* end_jobj;
    u32 i;
    grBb_TrackEntry* entry;

    HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);

    scale.x = scale.y = scale.z = 1.0F;
    HSD_JObjSetScale(jobj, &scale);

    scale.x = scale.y = scale.z = Ground_801C0498();

    entry = grBb_TrackEntries;
    for (i = 0; i < 12; i++, entry++) {
        child = Ground_801C3FA4(gobj, entry->jobj_index);

        /* goto required for match: skips to assert block on NULL */
        if (child == NULL) {
            goto assert_block;
        }

        start_jobj = Ground_801C3FA4(gobj, entry->start_index);
        if (start_jobj == NULL) {
            goto assert_block;
        }

        end_jobj = Ground_801C3FA4(gobj, entry->end_index);
        if (end_jobj == NULL) {
            goto assert_block;
        }

        HSD_JObjSetScale(child, &scale);

        lb_8000B1CC(start_jobj, NULL, &start_pos);
        lb_8000B1CC(end_jobj, NULL, &end_pos);
        lbVector_Diff(&end_pos, &start_pos, &diff);

        entry->delta = diff;
        continue;

    assert_block:
        HSD_ASSERT(2328, child);
        HSD_ASSERT(2329, start_jobj);
        HSD_ASSERT(2330, end_jobj);
    }

    *(u16*) (gp + 0xC4) = (*(u16*) (gp + 0xC4) & ~0x1FC0) | (0x7F << 6);

    *(u32*) (gp + 0xC4) =
        (*(u32*) (gp + 0xC4) & ~0x003F8000) | ((u32) 4 << 15);

    *(s8*) (gp + 0xC6) = *(s8*) (gp + 0xC6) & ~0x7F;

    *(f32*) (gp + 0xC8) = -1000.0F * Ground_801C0498();
    *(f32*) (gp + 0xCC) = 10.0F * Ground_801C0498();

    {
        f32 fval = 0.0F * Ground_801C0498();

        *(f32*) (gp + 0xD0) = fval;
        *(f32*) (gp + 0xD4) = fval;
        *(f32*) (gp + 0xD8) = fval;
        *(f32*) (gp + 0xDC) = fval;
        *(s16*) (gp + 0xF0) = 0;
        *(f32*) (gp + 0xF8) = fval;

        *(s8*) (gp + 0xC7) = *(s8*) (gp + 0xC7) & 0x0F;
        gp->gv.bigblue.x0 = gp->gv.bigblue.x0 & ~0x02;
        gp->gv.bigblue.x0 = gp->gv.bigblue.x0 & ~0x04;
    }

    {
        u32 idx = (*(u32*) (gp + 0xC4) >> 15) & 0x7F;
        HSD_JObj* active =
            Ground_801C3FA4(gobj, grBb_TrackEntries[idx].jobj_index);

        HSD_JObjClearFlagsAll(active, JOBJ_HIDDEN);

        pos.x = 0.0F;
        pos.y = grBb_804D69C8->x0 * Ground_801C0498();
        pos.z = 0.0F;

        HSD_JObjSetTranslate(active, &pos);
    }

    {
        u32 idx2 = *(s8*) (gp + 0xC6) & 0x7F;
        HSD_JObj* next =
            Ground_801C3FA4(gobj, grBb_TrackEntries[idx2].jobj_index);
        u32 active_idx;

        HSD_JObjClearFlagsAll(next, JOBJ_HIDDEN);

        active_idx = (*(u32*) (gp + 0xC4) >> 15) & 0x7F;
        pos.x += grBb_TrackEntries[active_idx].delta.x;
        pos.y += grBb_TrackEntries[active_idx].delta.y;
        pos.z += grBb_TrackEntries[active_idx].delta.z;

        HSD_JObjSetTranslate(next, &pos);
    }
}

/// @todo Currently partial match - needs register allocation and
/// bitfield rlwimi fixes.
void grBigBlue_801EB4AC(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    s32 count = 0;
    HSD_JObj* jobj;
    grBb_TrackEntry* entry;
    Vec3 sp_pos;
    f32 vel_threshold;
    f32 delta_threshold;
    s32 random_lane;

    /* Hide current lane's jobj */
    HSD_JObjSetFlagsAll(
        Ground_801C3FA4(
            gobj,
            grBb_TrackEntries[(*(u32*) (gp + 0xC4) >> 15) & 0x7F].jobj_index),
        JOBJ_HIDDEN);

    /* Copy current lane to previous lane: rlwimi hw, word, 23, 19, 25 */
    {
        u32 word = *(u32*) (gp + 0xC4);
        u16 hw = *(u16*) (gp + 0xC4);
        hw = (hw & ~0x1FC0) | ((word >> 9) & 0x1FC0);
        *(u16*) (gp + 0xC4) = hw;
    }

    /* Update current lane from next lane: rlwimi word, byte, 15, 10, 16 */
    {
        u8 next = *(u8*) (gp + 0xC6);
        u32 word = *(u32*) (gp + 0xC4);
        word = (word & ~0x003F8000) | (((u32) next << 15) & 0x003F8000);
        *(u32*) (gp + 0xC4) = word;
    }

    /* Get new lane's jobj and position */
    jobj = Ground_801C3FA4(
        gobj, grBb_TrackEntries[*(u8*) (gp + 0xC6) & 0x7F].jobj_index);

    lb_8000B1CC(jobj, NULL, &sp_pos);
    *(f32*) (gp + 0xC8) = sp_pos.x;

    HSD_JObjSetTranslateX(jobj, 0.0F);

    *(f32*) (gp + 0xD0) = sp_pos.z;

    HSD_JObjSetTranslateZ(jobj, 0.0F);

    /* Direction check */
    {
        s16 direction = *(s16*) (gp + 0xF0);

        if (direction == 1) {
            f32 scale = Ground_801C0498();
            f32 speed = grBb_804D69C8->x8;
            f32 vel = *(f32*) (gp + 0xCC);

            if (vel < grBb_804D69C8->x44 * speed * scale) {
                *(s16*) (gp + 0xF0) = 0;
            }
        } else if (direction == -1) {
            f32 scale = Ground_801C0498();
            f32 speed = grBb_804D69C8->x4;
            f32 vel = *(f32*) (gp + 0xCC);

            if (vel > -(speed * scale) * grBb_804D69C8->x44) {
                *(s16*) (gp + 0xF0) = 0;
            }
        } else {
            f32 scale = Ground_801C0498();
            f32 vel = *(f32*) (gp + 0xCC);
            f32 neg_speed = -(grBb_804D69C8->x4 * scale);

            if (vel < neg_speed) {
                *(s16*) (gp + 0xF0) = -1;
            } else {
                f32 scale2 = Ground_801C0498();
                f32 pos_speed = grBb_804D69C8->x8 * scale2;

                if (vel > pos_speed) {
                    *(s16*) (gp + 0xF0) = 1;
                }
            }
        }
    }

    /* Random lane selection loop */
    vel_threshold = 0.0F;
    delta_threshold = 0.0F;

    for (;;) {
        HSD_ASSERT(2414, count <= 1000);
        count++;

        random_lane = HSD_Randi(12);
        entry = &grBb_TrackEntries[random_lane];

        /* If lane 11: check velocity requirement */
        if (random_lane == 11) {
            if (*(f32*) (gp + 0xCC) < vel_threshold) {
                continue;
            }
        }

        /* Reject if same as current lane */
        if (((*(u32*) (gp + 0xC4) >> 15) & 0x7F) == (u32) random_lane) {
            continue;
        }

        /* Direction flag check */
        if (gp->gv.bigblue.x0 & 0x80) {
            if ((u32) random_lane <= 1) {
                break;
            }
            if (random_lane == 4) {
                break;
            }
            continue;
        }

        /* Direction compatibility */
        {
            s16 dir = *(s16*) (gp + 0xF0);

            if (dir == 1) {
                if (entry->delta.y < delta_threshold) {
                    continue;
                }
            }
            if (dir == -1) {
                if (entry->delta.y > delta_threshold) {
                    continue;
                }
            }
        }

        /* Reachability check */
        {
            f32 scale = Ground_801C0498();
            f32 vel = *(f32*) (gp + 0xCC);
            f32 speed = grBb_804D69C8->x8;
            f32 target = speed * scale + vel;
            f32 pos =
                sp_pos.y +
                grBb_TrackEntries[(*(u32*) (gp + 0xC4) >> 15) & 0x7F].delta.y +
                entry->delta.y;

            if (pos < target) {
                continue;
            }
        }
        break;
    }

    /* Store new lane index into gp+0xC6 */
    *(u8*) (gp + 0xC6) = (*(u8*) (gp + 0xC6) & ~0x7F) | (random_lane & 0x7F);

    HSD_ASSERT(979, jobj);

    /* Save current jobj translate (struct copy generates lwz/stw) */
    sp_pos = jobj->translate;

    /* Get new lane jobj and unhide */
    jobj = Ground_801C3FA4(gobj, entry->jobj_index);
    HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);

    /* Add current lane deltas (re-extract lane each time, no CSE) */
    sp_pos.x += grBb_TrackEntries[(*(u32*) (gp + 0xC4) >> 15) & 0x7F].delta.x;
    sp_pos.y += grBb_TrackEntries[(*(u32*) (gp + 0xC4) >> 15) & 0x7F].delta.y;
    sp_pos.z += grBb_TrackEntries[(*(u32*) (gp + 0xC4) >> 15) & 0x7F].delta.z;

    /* Set translate on new jobj (inline expands assert + dirty) */
    HSD_JObjSetTranslate(jobj, &sp_pos);

    /* If lane 11: activate joints and reset bitfield */
    if (random_lane == 11) {
        mpJointListAdd(41);
        mpJointListAdd(42);
        mpJointListAdd(43);
        mpLib_80057BC0(44);
        mpLib_80057BC0(45);
        mpLib_80057BC0(46);
        mpLib_80057BC0(47);
        mpLib_80057BC0(48);
        mpLib_80057BC0(49);
        {
            u8 byte = *(s8*) (gp + 0xC7);
            byte = (byte & ~0xF0) | (0 & 0xF0);
            *(s8*) (gp + 0xC7) = byte;
        }
    }

    /* Switch on random_lane for collision zone activation */
    switch (random_lane) {
    case 0:
        mpLib_80057424(35);
        break;
    case 1:
        mpLib_80057424(50);
        break;
    case 2:
        mpLib_80057424(52);
        mpLib_80057424(53);
        mpLib_80057424(54);
        break;
    case 3:
        mpLib_80057424(55);
        mpLib_80057424(56);
        mpLib_80057424(57);
        break;
    case 4:
        mpLib_80057424(58);
        mpLib_80057424(59);
        mpLib_80057424(60);
        break;
    case 5:
        mpLib_80057424(61);
        mpLib_80057424(62);
        mpLib_80057424(63);
        break;
    case 6:
        mpLib_80057424(51);
        break;
    case 7:
        mpLib_80057424(33);
        break;
    case 8:
        mpLib_80057424(38);
        mpLib_80057424(39);
        mpLib_80057424(40);
        break;
    case 9:
        mpLib_80057424(36);
        mpLib_80057424(37);
        break;
    case 10:
        mpLib_80057424(64);
        mpLib_80057424(65);
        break;
    case 11:
        mpLib_80057424(41);
        mpLib_80057424(42);
        mpLib_80057424(43);
        mpLib_80057424(44);
        mpLib_80057424(45);
        mpLib_80057424(46);
        mpLib_80057424(47);
        mpLib_80057424(48);
        mpLib_80057424(49);
        break;
    }

    mpLib_80058560();
}

void grBigBlue_801EBAF8(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = gobj->hsd_obj;
    Vec3 bone_pos;
    Vec3 vel;
    Vec3 center;
    Vec3 normal_out;
    Vec3 target;
    Vec3 prev;
    f32 target_y;
    f32 rot_z;
    f32 angular_vel;
    grBb_TrackEntry* entry;

    center.x = 0.0F;
    center.z = 0.0F;
    center.y = grBb_804D69C8->x0 * Ground_801C0498();

    prev = *(Vec3*) (gp + 0xC8);

    entry = &grBb_TrackEntries[((*(u32*) (gp + 0xC4)) >> 15) & 0x7F];

    lb_8000B1CC(Ground_801C3FA4(gobj, entry->start_index), NULL, &bone_pos);

    {
        f32 angle = *(f32*) (gp + 0xF8);
        if (angle < 0.0F) {
            angle = -angle;
        }
        if (angle < 0.17453292F &&
            bone_pos.x < -300.0F * Ground_801C0498())
        {
            grBigBlue_801EB4AC(gobj);
        }
    }

    {
        f32 angle = *(f32*) (gp + 0xF8);
        if (angle < 0.0F) {
            angle = -angle;
        }
        if (angle < 0.17453292F) {
            if (bone_pos.x < 0.0F) {
                u8 byte = gp->gv.bigblue.x0;
                if ((byte >> 5) & 1) {
                    gp->gv.bigblue.x0 = byte & ~0x20;
                }
            } else {
                u8 byte = gp->gv.bigblue.x0;
                if (!((byte >> 5) & 1) &&
                    (((*(u32*) (gp + 0xC4)) >> 15) & 0x7F) == 0xB)
                {
                    gp->gv.bigblue.x0 = byte | 0x20;
                }
            }
        }
    }

    if ((((*(u32*) (gp + 0xC4)) >> 15) & 0x7F) == 0xB) {
        u32 state = (*(s8*) (gp + 0xC7) >> 4) & 0xF;
        if (state == 0) {
            *(s8*) (gp + 0xC7) = (*(s8*) (gp + 0xC7) & ~0xF0) | 0x10;
        } else if (state == 1) {
            mpJointListAdd(0x29);
            mpJointListAdd(0x2A);
            mpJointListAdd(0x2B);
            mpLib_80057BC0(0x2C);
            mpLib_80057BC0(0x2D);
            mpLib_80057BC0(0x2E);
            mpLib_80057BC0(0x2F);
            mpLib_80057BC0(0x30);
            mpLib_80057BC0(0x30);
            *(s8*) (gp + 0xC7) = (*(s8*) (gp + 0xC7) & ~0xF0) | 0x20;
        } else if (state == 2) {
            if (*(f32*) (gp + 0xF8) < -0.5235988F) {
                mpJointListAdd(0x2C);
                mpJointListAdd(0x2D);
                mpJointListAdd(0x2E);
                *(s8*) (gp + 0xC7) = (*(s8*) (gp + 0xC7) & ~0xF0) | 0x30;
            }
        } else if (state == 3) {
            if (*(f32*) (gp + 0xF8) < -2.7925267F) {
                mpLib_80057BC0(0x29);
                mpLib_80057BC0(0x2A);
                mpLib_80057BC0(0x2B);
                mpJointListAdd(0x2F);
                mpJointListAdd(0x30);
                mpJointListAdd(0x31);
                *(s8*) (gp + 0xC7) = (*(s8*) (gp + 0xC7) & ~0xF0) | 0x40;
            }
        }
    }

    if (!((gp->gv.bigblue.x0 >> 6) & 1)) {
        target_y = grBigBlue_801EC58C(&center, &normal_out,
                                      20.0F * Ground_801C0498());
    } else {
        target_y = grBigBlue_801EC58C(&center, &normal_out,
                                      120.0F * Ground_801C0498());
    }

    if (target_y != grBb_804DB310 &&
        (!((gp->gv.bigblue.x0 >> 6) & 1) || target_y > center.y))
    {
        f32 max_steer = grBb_804D69C8->x70;
        if (target_y > max_steer) {
            target_y = max_steer;
        } else if (target_y < -max_steer) {
            target_y = -max_steer;
        }

        target.x = center.x;
        target.y = target_y;
        target.z = center.z;

        if ((((*(u32*) (gp + 0xC4)) >> 15) & 0x7F) == 0xB &&
            ((gp->gv.bigblue.x0 >> 5) & 1))
        {
            rot_z = -atan2f(-normal_out.x, normal_out.y);
        } else {
            rot_z = -*(f32*) (gp + 0xF8);
        }

        gp->gv.bigblue.x0 &= ~0x40;
    } else {
        if (!((gp->gv.bigblue.x0 >> 6) & 1)) {
            lbVector_Diff((Vec3*) (gp + 0xD4), (Vec3*) (gp + 0xC8),
                          (Vec3*) (gp + 0xE0));
            {
                f32 speed = grBb_804D69C8->x7C * Ground_801C0498();
                *(f32*) (gp + 0xEC) = sinf(*(f32*) (gp + 0xF8)) * speed;
            }
            gp->gv.bigblue.x0 |= 0x40;
        }

        if (target_y != grBb_804DB310) {
            *(f32*) (gp + 0xEC) =
                -(3.0F * (grBb_804D69C8->x78 * Ground_801C0498()) -
                  *(f32*) (gp + 0xEC));
        } else {
            *(f32*) (gp + 0xEC) =
                -(grBb_804D69C8->x78 * Ground_801C0498() -
                  *(f32*) (gp + 0xEC));
        }

        target.x = center.x;
        target.y = center.y + *(f32*) (gp + 0xEC);
        target.z = center.z;

        rot_z = -*(f32*) (gp + 0xF8);
    }

    angular_vel = rot_z;
    if (rot_z > 0.0F) {
        angular_vel = 0.0F;
    } else {
        f32 abs_rot = rot_z;
        if (abs_rot < 0.0F) {
            abs_rot = -abs_rot;
        }
        if (abs_rot > 0.0034906585F) {
            angular_vel *= grBb_804D69C8->x74;
        }
    }

    vel.x = *(f32*) (gp + 0xC8);
    vel.y = *(f32*) (gp + 0xCC);
    vel.z = *(f32*) (gp + 0xD0);
    lbVector_Sub(&vel, &target);

    if (angular_vel != 0.0F) {
        f32 s = sinf(angular_vel);
        f32 c = (f32) cosf(angular_vel);
        f32 new_y = (f32) ((f64) vel.x * (f64) s + (f64) vel.y * (f64) c);
        vel.x = (f32) ((f64) vel.x * (f64) c - (f64) vel.y * (f64) s);
        vel.y = new_y;
    }

    lbVector_Add(&vel, &center);

    *(f32*) (gp + 0xC8) = vel.x;
    *(f32*) (gp + 0xCC) = vel.y;
    *(f32*) (gp + 0xD0) = vel.z;

    {
        f32 old_rot = *(f32*) (gp + 0xF8);
        *(f32*) (gp + 0xF8) = old_rot + angular_vel;
        if (!((gp->gv.bigblue.x0 >> 5) & 1) && old_rot > 0.0F) {
            if (*(f32*) (gp + 0xF8) <= 0.0F) {
                *(f32*) (gp + 0xF8) = 0.0F;
            }
        }
    }

    {
        f32 rot = *(f32*) (gp + 0xF8);
        if (rot > M_PI) {
            *(f32*) (gp + 0xF8) = (f32) ((f64) rot - M_TAU);
        } else if (rot < -M_PI) {
            *(f32*) (gp + 0xF8) = (f32) ((f64) rot + M_TAU);
        }
    }

    *(f32*) (gp + 0xC8) =
        -(grBb_804D69C8->x6C * Ground_801C0498() - *(f32*) (gp + 0xC8));

    {
        f32 lat_adj = 0.6F * (entry->delta.z / entry->delta.x) *
                      (grBb_804D69C8->x6C * Ground_801C0498());

        if (bone_pos.z > lat_adj) {
            *(f32*) (gp + 0xD0) = *(f32*) (gp + 0xD0) - lat_adj;
        } else if (bone_pos.z < -lat_adj) {
            *(f32*) (gp + 0xD0) = *(f32*) (gp + 0xD0) + lat_adj;
        } else {
            *(f32*) (gp + 0xD0) = *(f32*) (gp + 0xD0) - bone_pos.z;
        }
    }

    HSD_JObjSetTranslateX(jobj, *(f32*) (gp + 0xC8));
    HSD_JObjSetTranslateY(jobj, *(f32*) (gp + 0xCC));
    HSD_JObjSetTranslateZ(jobj, *(f32*) (gp + 0xD0));

    HSD_JObjSetRotationZ(jobj, *(f32*) (gp + 0xF8));

    lbVector_Rotate(&vel, 4, -*(f32*) (gp + 0xF8));
    vel.z = 0.0F;
    vel.x = 0.0F;
    lbVector_Rotate(&vel, 4, *(f32*) (gp + 0xF8));

    {
        HSD_GObj* car = Ground_801C2BA4(2);
        if (car != NULL) {
            HSD_JObjSetTranslate(car->hsd_obj, &vel);
            HSD_JObjSetRotationZ(car->hsd_obj, *(f32*) (gp + 0xF8));
        }
    }

    {
        HSD_GObj* car = Ground_801C2BA4(1);
        if (car != NULL) {
            HSD_JObjSetTranslate(car->hsd_obj, &vel);
            HSD_JObjSetRotationZ(car->hsd_obj, *(f32*) (gp + 0xF8));
        }
    }

    *(Vec3*) (gp + 0xD4) = prev;
}

f32 grBigBlue_801EC58C(Vec3* pos, Vec3* normal_out, f32 half_height)
{
    Vec3 hit_pos;
    Vec3 hit_normal;
    grBb_LineIds local_ids;
    f32 max_y;
    f32 x1;
    f32 top;
    f32 x2;
    f32 bottom;
    u32 i;

    max_y = 0.0F;
    local_ids = grBb_803B8134;

    x1 = pos->x;
    x2 = pos->x;
    top = pos->y + half_height;
    bottom = pos->y - half_height;

    for (i = 0; i < 32; i++) {
        if (mpCheckMultiple(x1, top, x2, bottom, &hit_pos, NULL, NULL,
                            &hit_normal, 1, -1, local_ids.v[i]))
        {
            if (max_y < hit_pos.y) {
                max_y = hit_pos.y;
                if (normal_out != NULL) {
                    *normal_out = hit_normal;
                }
            }
        }
    }

    return max_y;
}

/// @todo Currently 90.40% match - needs register allocation fix (stmw r24 vs
/// r23) and bitfield write pattern fix (rlwinm+ori vs rlwimi)
#pragma push
#pragma fp_contract on
void grBigBlue_801EC6C0(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    s32 i;
    s32 line_idx;
    s32 idx;
    s32 k;
    u8* car;
    grBb_YakumonoParams* params;
    f32 scale;
    f32 lerp;
    s32 lo;
    s32 hi;
    HSD_JObj* jobj;

    for (i = 0; i < 30; i++) {
        u8 val;
        mpJointSetCb1(grBb_803E2D78.x84[i], gp, (mpLib_Callback) fn_801EF60C);
        HSD_JObjSetFlagsAll(((HSD_JObj**) gp->gv.bigblue.xC8)[i], 16);
        val = HSD_Randi(2) ? 0 : 2;
        ((u8*) gp->gv.bigblue.xCC)[i] = val;
    }

    {
        if (grBb_804D69C8->x18 == 0) {
            grBb_804D69C8->x18 = 1;
        }
    }

    car = (u8*) gp;
    for (k = 0; k < 4; k++, car += 0x40) {
        if (k < grBb_804D69C8->x18) {
            car[0xD4] = (car[0xD4] & ~0xFC) | (4 << 2);

            do {
                line_idx = HSD_Randi(30);
                {
                    u8* p = (u8*) gp;
                    i = 0;
                    if (k > 0) {
                        s32 ctr = k;
                        while (ctr > 0) {
                            u16 hw = *(u16*) (p + 0xD4);
                            if (((hw >> 4) & 0x1F) == line_idx) {
                                break;
                            }
                            p += 0x40;
                            i++;
                            ctr--;
                        }
                    }
                }
            } while (i != k);

            {
                u16 hw = *(u16*) (car + 0xD4);
                hw = (hw & ~0x01F0) | ((line_idx & 0x1F) << 4);
                *(u16*) (car + 0xD4) = hw;
            }

            idx = 0;
            car[0xD4] = (car[0xD4] & ~0x02) | (idx << 1);

            params = grBb_804D69C8;
            scale = Ground_801C0498();
            lerp = (f32) (k + 1) *
                   ((f32) params->x1C * scale / (f32) (params->x18 + 1));

            scale = Ground_801C0498();
            params = grBb_804D69C8;
            *(f32*) (car + 0xE0) = lerp + 0.5F * (-(f32) params->x1C * scale);

            scale = Ground_801C0498();
            params = grBb_804D69C8;
            lerp = params->x2C * scale;

            scale = Ground_801C0498();
            params = grBb_804D69C8;
            *(f32*) (car + 0xE4) = params->x0 * scale + lerp;

            *(f32*) (car + 0xE8) = 0.0F;

            params = grBb_804D69C8;
            scale = Ground_801C0498();
            lerp = (f32) (k + 1) *
                   ((f32) params->x1C * scale / (f32) (params->x18 + 1));

            scale = Ground_801C0498();
            params = grBb_804D69C8;
            *(f32*) (car + 0xD8) = lerp + 0.5F * (-(f32) params->x1C * scale);

            *(f32*) (car + 0xDC) = 0.0F;

            *(f32*) (car + 0xF4) = 0.0F;
            *(f32*) (car + 0xF8) = 0.0F;
            *(f32*) (car + 0xFC) = 0.0F;
            *(f32*) (car + 0x100) = 0.0F;

            *(f32*) (car + 0x104) = (f32) (2.0 * M_PI * HSD_Randf());

            scale = Ground_801C0498();
            params = grBb_804D69C8;
            *(f32*) (car + 0x108) = params->x34 * scale;

            *(f32*) (car + 0x10C) = 0.0F;

            params = grBb_804D69C8;
            hi = (s32) params->x60;
            lo = (s32) params->x5C;
            if (lo > hi) {
                s32 diff = lo - hi;
                if (diff != 0) {
                    lo = hi + HSD_Randi(diff);
                } else {
                    lo = hi + idx;
                }
            } else if (lo < hi) {
                s32 diff = hi - lo;
                if (diff != 0) {
                    lo = lo + HSD_Randi(diff);
                } else {
                    lo = lo + idx;
                }
            }
            *(s32*) (car + 0xF0) = lo;

            {
                Ground_801C5440(gp, k, grBb_803E2EB8.x58[HSD_Randi(4)]);
            }

            *(f32*) (car + 0xEC) = 1.0F;

            HSD_JObjClearFlagsAll(((HSD_JObj**) gp->gv.bigblue.xC8)[line_idx],
                                  16);

            jobj = ((HSD_JObj**) gp->gv.bigblue.xC8)[line_idx];

            HSD_JObjSetTranslate(jobj, (Vec3*) (car + 0xE0));

            ((u8*) gp->gv.bigblue.xCC)[line_idx] = 1;
        } else {
            car[0xD4] = (car[0xD4] & ~0xFC) | (1 << 2);
        }
    }
}
#pragma pop

void grBigBlue_801ECB50(Ground_GObj* gobj)
{
    s32 i = 0;
    Ground* gp = GET_GROUND(gobj);
    s32 free_count = 0;
    s32 reserved_count = 0;
    s32 active_count = 0;

    /* Count free (0) and reserved (2) lanes - 5×6=30 total */
    {
        s32 ctr = 5;
        do {
            u8 val;
            val = *((u8*) gp->gv.bigblue.xCC + i);
            if (val == 0) { free_count++; }
            else if (val == 2) { reserved_count++; }
            i++;
            val = *((u8*) gp->gv.bigblue.xCC + i);
            if (val == 0) { free_count++; }
            else if (val == 2) { reserved_count++; }
            i++;
            val = *((u8*) gp->gv.bigblue.xCC + i);
            if (val == 0) { free_count++; }
            else if (val == 2) { reserved_count++; }
            i++;
            val = *((u8*) gp->gv.bigblue.xCC + i);
            if (val == 0) { free_count++; }
            else if (val == 2) { reserved_count++; }
            i++;
            val = *((u8*) gp->gv.bigblue.xCC + i);
            if (val == 0) { free_count++; }
            else if (val == 2) { reserved_count++; }
            i++;
            val = *((u8*) gp->gv.bigblue.xCC + i);
            if (val == 0) { free_count++; }
            else if (val == 2) { reserved_count++; }
            i++;
        } while (--ctr);
    }

    /* Balance lanes */
    if (free_count == 0) {
        s32 pick;
        if (reserved_count != 0) {
            pick = HSD_Randi(reserved_count);
        } else {
            pick = 0;
        }
        {
            s32 ctr = 3;
            i = 0;
        bal_loop1:
            {
                u8* p = (u8*) gp->gv.bigblue.xCC + i;
                if ((u8)*p == 2 && (pick--, pick < 0)) {
                    *p = 0; free_count++;
                } else { i++;
                p = (u8*) gp->gv.bigblue.xCC + i;
                if ((u8)*p == 2 && (pick--, pick < 0)) {
                    *p = 0; free_count++;
                } else { i++;
                p = (u8*) gp->gv.bigblue.xCC + i;
                if ((u8)*p == 2 && (pick--, pick < 0)) {
                    *p = 0; free_count++;
                } else { i++;
                p = (u8*) gp->gv.bigblue.xCC + i;
                if ((u8)*p == 2 && (pick--, pick < 0)) {
                    *p = 0; free_count++;
                } else { i++;
                p = (u8*) gp->gv.bigblue.xCC + i;
                if ((u8)*p == 2 && (pick--, pick < 0)) {
                    *p = 0; free_count++;
                } else { i++;
                p = (u8*) gp->gv.bigblue.xCC + i;
                if ((u8)*p == 2 && (pick--, pick < 0)) {
                    *p = 0; free_count++;
                } else { i++;
                p = (u8*) gp->gv.bigblue.xCC + i;
                if ((u8)*p == 2 && (pick--, pick < 0)) {
                    *p = 0; free_count++;
                } else { i++;
                p = (u8*) gp->gv.bigblue.xCC + i;
                if ((u8)*p == 2 && (pick--, pick < 0)) {
                    *p = 0; free_count++;
                } else { i++;
                p = (u8*) gp->gv.bigblue.xCC + i;
                if ((u8)*p == 2 && (pick--, pick < 0)) {
                    *p = 0; free_count++;
                } else { i++;
                p = (u8*) gp->gv.bigblue.xCC + i;
                if ((u8)*p == 2 && (pick--, pick < 0)) {
                    *p = 0; free_count++;
                } else {
                    i++;
                    ctr--;
                    if (ctr != 0) {
                        goto bal_loop1;
                    }
                }}}}}}}}}}
            }
        }
    } else if (reserved_count == 0) {
        s32 pick;
        if (free_count != 0) {
            pick = HSD_Randi(free_count);
        } else {
            pick = 0;
        }
        {
            s32 ctr = 3;
            i = 0;
        bal_loop2:
            {
                u8* p = (u8*) gp->gv.bigblue.xCC + i;
                if ((u8)*p == 0 && (pick--, pick < 0)) {
                    *p = 2; reserved_count++;
                } else { i++;
                p = (u8*) gp->gv.bigblue.xCC + i;
                if ((u8)*p == 0 && (pick--, pick < 0)) {
                    *p = 2; reserved_count++;
                } else { i++;
                p = (u8*) gp->gv.bigblue.xCC + i;
                if ((u8)*p == 0 && (pick--, pick < 0)) {
                    *p = 2; reserved_count++;
                } else { i++;
                p = (u8*) gp->gv.bigblue.xCC + i;
                if ((u8)*p == 0 && (pick--, pick < 0)) {
                    *p = 2; reserved_count++;
                } else { i++;
                p = (u8*) gp->gv.bigblue.xCC + i;
                if ((u8)*p == 0 && (pick--, pick < 0)) {
                    *p = 2; reserved_count++;
                } else { i++;
                p = (u8*) gp->gv.bigblue.xCC + i;
                if ((u8)*p == 0 && (pick--, pick < 0)) {
                    *p = 2; reserved_count++;
                } else { i++;
                p = (u8*) gp->gv.bigblue.xCC + i;
                if ((u8)*p == 0 && (pick--, pick < 0)) {
                    *p = 2; reserved_count++;
                } else { i++;
                p = (u8*) gp->gv.bigblue.xCC + i;
                if ((u8)*p == 0 && (pick--, pick < 0)) {
                    *p = 2; reserved_count++;
                } else { i++;
                p = (u8*) gp->gv.bigblue.xCC + i;
                if ((u8)*p == 0 && (pick--, pick < 0)) {
                    *p = 2; reserved_count++;
                } else { i++;
                p = (u8*) gp->gv.bigblue.xCC + i;
                if ((u8)*p == 0 && (pick--, pick < 0)) {
                    *p = 2; reserved_count++;
                } else {
                    i++;
                    ctr--;
                    if (ctr != 0) {
                        goto bal_loop2;
                    }
                }}}}}}}}}}
            }
        }
    }

    /* Count active cars (not in state 1, 7, or 8) */
    {
        u8* bp = (u8*) gp;
        u32 st;
        st = (bp[0xD4] >> 2) & 0x3F;
        if (st != 1 && st != 7 && st != 8) {
            active_count = 1;
        }
        st = (bp[0x114] >> 2) & 0x3F;
        if (st != 1 && st != 7 && st != 8) {
            active_count++;
        }
        st = (bp[0x154] >> 2) & 0x3F;
        if (st != 1 && st != 7 && st != 8) {
            active_count++;
        }
        st = (bp[0x194] >> 2) & 0x3F;
        if (st != 1 && st != 7 && st != 8) {
            active_count++;
        }
    }

    if (active_count == 1) {
        *(s16*)((u8*) gp + 0xD0) -= 1;
    }

    /* Find closest car */
    {
        u8* bp = (u8*) gp;
        f32 closest_dist = 3.4028235e38f;
        s32 ctr = 2;
        u8* car_p = (u8*) gp;
        s32 found_ten = 0;
        s32 closest_lane = -1;
        s32 car_idx = 0;

    car_loop:
        {
            u32 st = (car_p[0xD4] >> 2) & 0x3F;
            if (st == 10) {
                found_ten = 1;
            } else {
                if (st != 1 && st != 7 && st != 8) {
                    f32 dist = *(f32*)(car_p + 0xE0);
                    if (dist < 0.0f) {
                        dist = -dist;
                    }
                    if (dist > 60.0f) {
                        if (closest_dist > dist) {
                            closest_dist = dist;
                            closest_lane = car_idx;
                        }
                    } else {
                        found_ten = 1;
                        goto car_done;
                    }
                }
                car_idx++;
                {
                    u32 st2 = (car_p[0x114] >> 2) & 0x3F;
                    if (st2 == 10) {
                        found_ten = 1;
                    } else {
                        if (st2 != 1 && st2 != 7 && st2 != 8) {
                            f32 dist2 = *(f32*)(car_p + 0x120);
                            if (dist2 < 0.0f) {
                                dist2 = -dist2;
                            }
                            if (dist2 > 60.0f) {
                                if (closest_dist > dist2) {
                                    closest_dist = dist2;
                                    closest_lane = car_idx;
                                }
                            } else {
                                found_ten = 1;
                                goto car_done;
                            }
                        }
                        car_p += 0x80;
                        car_idx++;
                        ctr--;
                        if (ctr != 0) {
                            goto car_loop;
                        }
                    }
                }
            }
        }
    car_done:

        if (found_ten == 0 && closest_lane != -1) {
            u8* target_car = bp + (closest_lane << 6);
            register s32 st_val;
            register u8 byte;

            st_val = 10;
            byte = target_car[0xD4];
#ifdef MWERKS_GEKKO
            asm { rlwimi byte, st_val, 2, 24, 29 }
#endif
            target_car[0xD4] = byte;

            st_val = 4;
            {
                u32 st = (bp[0xD4] >> 2) & 0x3F;
                if ((st == 7 &&
                     *(f32*)(bp + 0xE0) <
                         *(f32*)(target_car + 0xE0)) ||
                    (st == 8 &&
                     *(f32*)(bp + 0xE0) >
                         *(f32*)(target_car + 0xE0)))
                {
                    byte = bp[0xD4];
#ifdef MWERKS_GEKKO
                    asm { rlwimi byte, st_val, 2, 24, 29 }
#endif
                    bp[0xD4] = byte;
                }
            }

            {
                u32 st = (bp[0x114] >> 2) & 0x3F;
                if ((st == 7 &&
                     *(f32*)(bp + 0x120) <
                         *(f32*)(target_car + 0xE0)) ||
                    (st == 8 &&
                     *(f32*)(bp + 0x120) >
                         *(f32*)(target_car + 0xE0)))
                {
                    byte = bp[0x114];
#ifdef MWERKS_GEKKO
                    asm { rlwimi byte, st_val, 2, 24, 29 }
#endif
                    bp[0x114] = byte;
                }
            }

            {
                u8* p2 = bp + 0x80;
                u32 st = (bp[0x154] >> 2) & 0x3F;
                if ((st == 7 &&
                     *(f32*)(p2 + 0xE0) <
                         *(f32*)(target_car + 0xE0)) ||
                    (st == 8 &&
                     *(f32*)(p2 + 0xE0) >
                         *(f32*)(target_car + 0xE0)))
                {
                    byte = p2[0xD4];
#ifdef MWERKS_GEKKO
                    asm { rlwimi byte, st_val, 2, 24, 29 }
#endif
                    p2[0xD4] = byte;
                }
                {
                    u8* p3 = p2 + 0x40;
                    u32 st3 = (p2[0x114] >> 2) & 0x3F;
                    if ((st3 == 7 &&
                         *(f32*)(p3 + 0xE0) <
                             *(f32*)(target_car + 0xE0)) ||
                        (st3 == 8 &&
                         *(f32*)(p3 + 0xE0) >
                             *(f32*)(target_car + 0xE0)))
                    {
                        byte = p3[0xD4];
#ifdef MWERKS_GEKKO
                        asm { rlwimi byte, st_val, 2, 24, 29 }
#endif
                        p3[0xD4] = byte;
                    }
                }
            }
        }
    }

    /* Timer-based car spawn */
    {
        u8* bp = (u8*) gp;
        s16 timer = *(s16*)(bp + 0xD0);
        *(s16*)(bp + 0xD0) = timer - 1;
        if (timer < 0) {
            active_count = -1;
            if ((u32)((bp[0xD4] >> 2) & 0x3F) == 1) {
                active_count = 0;
            } else if ((u32)((bp[0x114] >> 2) & 0x3F) == 1) {
                active_count = 1;
            } else if ((u32)((bp[0x154] >> 2) & 0x3F) == 1) {
                active_count = 2;
            } else if ((u32)((bp[0x194] >> 2) & 0x3F) == 1) {
                active_count = 3;
            }

            if (active_count != -1) {
                s32 right_count = 0;
                s32 left_count = 0;
                s32 direction;
                u32 st;

                st = (bp[0xD4] >> 2) & 0x3F;
                if (st == 7) {
                    right_count = 1;
                } else if (st == 8) {
                    left_count = 1;
                }
                st = (bp[0x114] >> 2) & 0x3F;
                if (st == 7) {
                    right_count++;
                } else if (st == 8) {
                    left_count++;
                }
                st = (bp[0x154] >> 2) & 0x3F;
                if (st == 7) {
                    right_count++;
                } else if (st == 8) {
                    left_count++;
                }
                st = (bp[0x194] >> 2) & 0x3F;
                if (st == 7) {
                    right_count++;
                } else if (st == 8) {
                    left_count++;
                }

                if (right_count == 0 && left_count == 0) {
                    if (HSD_Randi(2) != 0) {
                        direction = 1;
                    } else {
                        direction = -1;
                    }
                } else if (right_count != 0) {
                    direction = -1;
                } else if (left_count != 0) {
                    direction = 1;
                } else {
                    direction = 0;
                }

                if (direction == 1) {
                    s32 pick;
                    s32 pos;
                    s32 cnt;
                    if (free_count != 0) {
                        pick = HSD_Randi(free_count);
                    } else {
                        pick = 0;
                    }
                    cnt = 0x1E;
                    pos = 0;
                spawn_loop1:
                    if ((u8)*((u8*) gp->gv.bigblue.xCC + pos) == 0 &&
                        --pick < 0)
                    {
                        if (grBigBlue_801EE398(
                                gobj, active_count, 5) != 0)
                        {
                            s32 tmin = grBb_804D69C8->x10;
                            s32 tmax = grBb_804D69C8->x14;
                            if (tmin > tmax) {
                                s32 diff = tmin - tmax;
                                if (diff != 0) {
                                    tmin = tmax +
                                        HSD_Randi(diff);
                                } else {
                                    tmin = tmax;
                                }
                            } else if (tmin < tmax) {
                                s32 diff = tmax - tmin;
                                if (diff != 0) {
                                    tmin += HSD_Randi(diff);
                                }
                            }
                            *(s16*)(bp + 0xD0) = (s16) tmin;
                            return;
                        }
                    } else {
                        pos++;
                        cnt--;
                        if (cnt == 0) {
                            return;
                        }
                        goto spawn_loop1;
                    }
                } else if (direction == -1) {
                    s32 pick;
                    s32 pos;
                    s32 cnt;
                    if (reserved_count != 0) {
                        pick = HSD_Randi(reserved_count);
                    } else {
                        pick = 0;
                    }
                    cnt = 0x1E;
                    pos = 0;
                spawn_loop2:
                    if ((u8)*((u8*) gp->gv.bigblue.xCC + pos) == 2 &&
                        --pick < 0)
                    {
                        if (grBigBlue_801EE398(
                                gobj, active_count, 6) != 0)
                        {
                            s32 tmin = grBb_804D69C8->x10;
                            s32 tmax = grBb_804D69C8->x14;
                            if (tmin > tmax) {
                                s32 diff = tmin - tmax;
                                if (diff != 0) {
                                    tmin = tmax +
                                        HSD_Randi(diff);
                                } else {
                                    tmin = tmax;
                                }
                            } else if (tmin < tmax) {
                                s32 diff = tmax - tmin;
                                if (diff != 0) {
                                    tmin += HSD_Randi(diff);
                                }
                            }
                            *(s16*)(bp + 0xD0) = (s16) tmin;
                            return;
                        }
                    } else {
                        pos++;
                        cnt--;
                        if (cnt != 0) {
                            goto spawn_loop2;
                        }
                    }
                }
            }
        }
    }
}

/// @todo Currently partial match - complex car physics simulation
#pragma push
#pragma fp_contract on
void grBigBlue_801ED694(Ground_GObj* gobj, s32 lane)
{
    u8* gp = (u8*) gobj->user_data;
    s32 lane_offset;
    HSD_JObj* jobj;
    s32 active;
    s32 behind;
    f32 rank_factor;
    f32 ground_y;
    f32 f31_rot;
    f32 heading_osc;
    f32 heading_val;
    Vec3 sp_vec;

    /* Check and handle lane status */
    {
        s32 status = grBigBlue_801EDF44(gobj, lane);
        if (status != 0) {
            grBigBlue_801EE398(gobj, lane, status);
        }
    }

    if (!grBigBlue_801EEF00(gobj, lane)) {
        return;
    }

    /* Setup per-lane data */
    lane_offset = lane << 6;

    {
        u16 hw = *(u16*) (gp + lane_offset + 0xD4);
        void** arr = *(void***) (gp + 0xC8);
        jobj = (HSD_JObj*) arr[(hw >> 4) & 0x1F];
    }

    HSD_ASSERT(745, jobj);

    f31_rot = jobj->rotate.z;

    {
        u32 state = (gp[lane_offset + 0xD4] >> 2) & 0x3F;
        f32 target;

        if (state == 7 || state == 8) {
            target = *(f32*) (gp + lane_offset + 0xD8);
        } else {
            u8* iter;
            s32 idx;

            active = 0;
            behind = 0;

            /* Lane 0 */
            {
                u32 st = (gp[0xD4] >> 2) & 0x3F;
                idx = 0;
                if (st != 1 && st != 7 && st != 8) {
                    active++;
                    if (idx != lane && *(f32*) (gp + 0xE0) <
                                           *(f32*) (gp + lane_offset + 0xE0))
                    {
                        behind++;
                    }
                }
            }

            /* Lane 1 */
            iter = gp + 0x40;
            {
                u32 st = (gp[0x114] >> 2) & 0x3F;
                idx = 1;
                if (st != 1 && st != 7 && st != 8) {
                    active++;
                    if (idx != lane && *(f32*) (iter + 0xE0) <
                                           *(f32*) (gp + lane_offset + 0xE0))
                    {
                        behind++;
                    }
                }
            }

            /* Lane 2 */
            {
                u32 st = (iter[0x114] >> 2) & 0x3F;
                idx = 2;
                iter += 0x40;
                if (st != 1 && st != 7 && st != 8) {
                    active++;
                    if (idx != lane && *(f32*) (iter + 0xE0) <
                                           *(f32*) (gp + lane_offset + 0xE0))
                    {
                        behind++;
                    }
                }
            }

            /* Lane 3 */
            {
                u32 st = (iter[0x114] >> 2) & 0x3F;
                idx = 3;
                iter += 0x40;
                if (st != 1 && st != 7 && st != 8) {
                    active++;
                    if (idx != lane && *(f32*) (iter + 0xE0) <
                                           *(f32*) (gp + lane_offset + 0xE0))
                    {
                        behind++;
                    }
                }
            }

            /* Compute ranking-based target */
            {
                f32 scale = Ground_801C0498();
                s32 total = grBb_804D69C8->x1C;
                rank_factor = (f32) (behind + 1) *
                              ((f32) (active + 1) * scale / (f32) total);
            }

            {
                f32 scale = Ground_801C0498();
                s32 total = grBb_804D69C8->x1C;
                target = 0.5F * (-(f32) total * scale) + rank_factor;
            }
        }

        /* Convergence step for position index */
        {
            f32 current = *(f32*) (gp + lane_offset + 0xD8);
            f32 diff = target - current;

            if (diff < -0.5F) {
                *(f32*) (gp + lane_offset + 0xD8) = current - 0.5F;
            } else if (diff > 0.5F) {
                *(f32*) (gp + lane_offset + 0xD8) = current + 0.5F;
            } else {
                *(f32*) (gp + lane_offset + 0xD8) = target;
            }
        }
    }

    /* Velocity update: vel += accel */
    *(f32*) (gp + lane_offset + 0xFC) += *(f32*) (gp + lane_offset + 0x100);

    /* Clamp velocity to +-max_speed*scale */
    {
        f32 scale = Ground_801C0498();
        f32 vel = *(f32*) (gp + lane_offset + 0xFC);
        f32 max_spd = grBb_804D69C8->x24;

        if (vel > max_spd * scale) {
            f32 s2 = Ground_801C0498();
            *(f32*) (gp + lane_offset + 0xFC) = grBb_804D69C8->x24 * s2;
        } else {
            f32 s2 = Ground_801C0498();
            f32 lim = grBb_804D69C8->x24 * s2;

            if (vel < -lim) {
                f32 s3 = Ground_801C0498();
                *(f32*) (gp + lane_offset + 0xFC) = -(grBb_804D69C8->x24 * s3);
            }
        }
    }

    /* Position update: xDC += vel, xE0 = xD8 + xDC */
    {
        f32 vel = *(f32*) (gp + lane_offset + 0xFC);
        *(f32*) (gp + lane_offset + 0xDC) += vel;
        *(f32*) (gp + lane_offset + 0xE0) = *(f32*) (gp + lane_offset + 0xD8) +
                                            *(f32*) (gp + lane_offset + 0xDC);
    }

    /* Height/bounce simulation */
    if (!((gp[lane_offset + 0xD4] >> 1) & 1)) {
        f32 scale = Ground_801C0498();
        f32 grav = grBb_804D69C8->x48;

        *(f32*) (gp + lane_offset + 0xF4) += grav * scale;
        *(f32*) (gp + lane_offset + 0xF8) += *(f32*) (gp + lane_offset + 0xF4);

        if (*(f32*) (gp + lane_offset + 0xF8) > 0.0F) {
            *(f32*) (gp + lane_offset + 0xF8) = 0.0F;
            *(f32*) (gp + lane_offset + 0xF4) = 0.0F;
        } else {
            f32 s2 = Ground_801C0498();
            f32 blim = grBb_804D69C8->x4C;

            if (*(f32*) (gp + lane_offset + 0xF8) < -(blim * s2)) {
                f32 s3 = Ground_801C0498();
                *(f32*) (gp + lane_offset + 0xF8) = -(grBb_804D69C8->x4C * s3);
            }
        }
    } else {
        *(f32*) (gp + lane_offset + 0xF8) = 0.0F;
        *(f32*) (gp + lane_offset + 0xF4) = 0.0F;
    }

    /* Heading direction from velocity */
    if (!((gp[lane_offset + 0xD4] >> 1) & 1)) {
        f32 vel = *(f32*) (gp + lane_offset + 0xFC);

        if (vel > 0.0F) {
            f32 s1 = Ground_801C0498();
            ground_y = grBb_804D69C8->x24 * s1;
            {
                f32 s2 = Ground_801C0498();
                rank_factor = grBb_804D69C8->x34 * s2;
            }
            {
                f32 s3 = Ground_801C0498();
                f32 curve = grBb_804D69C8->x38;
                rank_factor = vel * ((curve * s3 - rank_factor) / ground_y);
            }
            {
                f32 s4 = Ground_801C0498();
                heading_val = grBb_804D69C8->x34 * s4 + rank_factor;
            }
        } else if (vel < 0.0F) {
            f32 s1 = Ground_801C0498();
            ground_y = grBb_804D69C8->x24 * s1;
            {
                f32 s2 = Ground_801C0498();
                rank_factor = grBb_804D69C8->x34 * s2;
            }
            {
                f32 s3 = Ground_801C0498();
                f32 curve = grBb_804D69C8->x30;
                rank_factor = vel * ((curve * s3 - rank_factor) / ground_y);
            }
            {
                f32 s4 = Ground_801C0498();
                heading_val = grBb_804D69C8->x34 * s4 + rank_factor;
            }
        } else {
            f32 s1 = Ground_801C0498();
            heading_val = grBb_804D69C8->x34 * s1;
        }
    } else {
        heading_val = 0.0F;
    }

    /* Heading target interpolation */
    {
        f32 ht = *(f32*) (gp + lane_offset + 0x108);
        f32 interp = grBb_804D69C8->x3C;
        ht += interp * (heading_val - ht);
        *(f32*) (gp + lane_offset + 0x108) = ht;
    }

    /* Rotation angle update */
    {
        f32 rotation;
        f32 ang_accel = grBb_804D69C8->x40;

        *(f32*) (gp + lane_offset + 0x104) += (f32) 0.017453292F * ang_accel;
        rotation = *(f32*) (gp + lane_offset + 0x104);

        if (rotation > M_TAU) {
            rotation = (f32) (rotation - M_TAU);
            *(f32*) (gp + lane_offset + 0x104) = rotation;
        }

        heading_osc = *(f32*) (gp + lane_offset + 0x108) * sinf(rotation);
    }

    /* Compute ground reference level */
    {
        f32 scale = Ground_801C0498();
        f32 drag = grBb_804D69C8->x2C;
        f32 lat = *(f32*) (gp + lane_offset + 0xE4);
        f32 height = *(f32*) (gp + lane_offset + 0xF8);

        rank_factor = (lat - drag * scale) - height - heading_osc;
    }

    /* Collision/grounding check */
    if ((gp[lane_offset + 0xD4] >> 1) & 1) {
        /* Grounded path */
        ground_y = grBigBlue_801EC58C((Vec3*) (gp + lane_offset + 0xE0),
                                      &sp_vec, (f32) 1.5707963F);

        if (0.0F != ground_y && ground_y > rank_factor) {
            if (*(f32*) (gp + lane_offset + 0x10C) < 0.0F) {
                u8 byte = gp[lane_offset + 0xD4];
                gp[lane_offset + 0xD4] = (byte & ~0x02);
                /* goto required for match: skip collision/grounding,
                 * jump to rotation convergence */
                goto heading_converge;
            }
        }

        if (0.0F != ground_y) {
            f32 s = Ground_801C0498();
            f32 decay = grBb_804D69C8->x80;
            *(f32*) (gp + lane_offset + 0x10C) -= 3.0F * decay * s;
        } else {
            f32 s = Ground_801C0498();
            f32 decay = grBb_804D69C8->x80;
            *(f32*) (gp + lane_offset + 0x10C) -= decay * s;
        }

        /* Lateral position += angular velocity */
        *(f32*) (gp + lane_offset + 0xE4) +=
            *(f32*) (gp + lane_offset + 0x10C);

        /* Track reference adjustment */
        {
            HSD_GObj* track_gobj = Ground_801C2BA4(34);
            u8* track_gp;

            HSD_ASSERT(3255, track_gobj);
            track_gp = (u8*) track_gobj->user_data;
            HSD_ASSERT(3256, track_gp);
            *(f32*) (gp + lane_offset + 0xE4) +=
                *(f32*) (track_gp + 0xCC) - *(f32*) (track_gp + 0xD8);
        }
    } else {
        /* Non-grounded path */
        f32 s = Ground_801C0498();
        ground_y = grBigBlue_801EC58C((Vec3*) (gp + lane_offset + 0xE0),
                                      &sp_vec, 20.0F * s);

        if (0.0F != ground_y) {
            f32 s2 = Ground_801C0498();
            f32 drag = grBb_804D69C8->x2C;
            *(f32*) (gp + lane_offset + 0xE4) =
                heading_osc + *(f32*) (gp + lane_offset + 0xF8) +
                (drag * s2 + ground_y);
        } else {
            gp[lane_offset + 0xD4] = (gp[lane_offset + 0xD4] & ~0x02) | 0x02;
            {
                f32 s2 = Ground_801C0498();
                rank_factor = grBb_804D69C8->x84 * s2;
            }
            *(f32*) (gp + lane_offset + 0x10C) = sinf(f31_rot) * rank_factor;
        }
    }

heading_converge:
    /* Update rotation: smooth toward target angle */
    if (0.0F != ground_y && !((gp[lane_offset + 0xD4] >> 1) & 1)) {
        f32 angle = atan2f(-sp_vec.x, sp_vec.y);
        f32 smooth = grBb_804D69C8->x50;
        f31_rot += smooth * (angle - f31_rot);
    } else {
        f32 target_angle = (f32) 0.017453292F * grBb_804D69C8->x58;
        f32 damp = grBb_804D69C8->x54;
        f31_rot += damp * (target_angle - f31_rot);
    }

    /* Update jobj transform */
    HSD_JObjSetTranslate(jobj, (Vec3*) (gp + lane_offset + 0xE0));
    HSD_JObjSetRotationZ(jobj, f31_rot);
}
#pragma pop

/// @todo Currently 87.41% match - compiler CSEs gp+offset into one register
/// (4 NV regs) instead of keeping them separate (5 NV regs, stmw r27)
s32 grBigBlue_801EDF44(Ground_GObj* gobj, s32 index)
{
    u8* gp;
    s32 result;
    s32 offset;

    gp = (u8*) gobj->user_data;
    result = 0;
    offset = index << 6;

    switch ((gp[offset + 0xD4] >> 2) & 0x3F) {
    case 1:
        break;
    case 9:
        if (0.0F == *(f32*) (gp + offset + 0xEC)) {
            result = 1;
        }
        break;
    case 7: {
        f32 blast = Stage_GetBlastZoneRightOffset();
        f32 scale = Ground_801C0498();

        if (*(f32*) (gp + offset + 0xE0) > blast + grBb_804D69C8->x68 * scale)
        {
            if (0.0F != *(f32*) (gp + offset + 0xEC)) {
                result = 9;
            } else {
                result = 1;
            }
        }
        break;
    }
    case 8: {
        f32 blast = Stage_GetBlastZoneLeftOffset();
        f32 scale = Ground_801C0498();

        if (*(f32*) (gp + offset + 0xE0) < blast - grBb_804D69C8->x68 * scale)
        {
            if (0.0F != *(f32*) (gp + offset + 0xEC)) {
                result = 9;
            } else {
                result = 1;
            }
        }
        break;
    }
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 10: {
        u8* self;
        s32 counter;
        s32 j;

        self = gp + offset;
        counter = *(s32*) (self + 0xF0);
        *(s32*) (self + 0xF0) = counter - 1;

        if (counter < 0) {
            while (result == 0) {
                s32 rnd = HSD_Randi(4);

                switch (rnd) {
                case 0:
                case 1:
                case 2:
                    result = 4;
                    break;
                case 3: {
                    u8* p = gp;
                    s32 right_cnt = 0;
                    s32 left_cnt = 0;
                    s32 right_10 = 0;
                    s32 left_10 = 0;

                    for (j = 0; j < 4; j++, p += 0x40) {
                        u32 st;

                        if (j == index) {
                            continue;
                        }

                        st = (p[0xD4] >> 2) & 0x3F;

                        if (st == 1) {
                            continue;
                        }
                        if (st == 7) {
                            continue;
                        }
                        if (st == 8) {
                            continue;
                        }

                        if (*(f32*) (p + 0xE0) > *(f32*) (self + 0xE0)) {
                            if (st == 10) {
                                right_10++;
                            } else {
                                right_cnt++;
                            }
                        } else if (*(f32*) (p + 0xE0) < *(f32*) (self + 0xE0))
                        {
                            if (st == 10) {
                                left_10++;
                            } else {
                                left_cnt++;
                            }
                        }
                    }

                    if (right_cnt != 0) {
                        if (left_cnt != 0) {
                            if (right_10 != 0) {
                                if (left_10 != 0) {
                                    break;
                                }
                                result = 8;
                            } else if (left_10 != 0) {
                                result = 7;
                            } else {
                                result = (HSD_Randi(2) != 0) ? 7 : 8;
                            }
                        } else {
                            result = 8;
                        }
                    } else if (left_cnt != 0) {
                        result = 7;
                    }
                    break;
                }
                }
            }
        }

        /* Override: check other platforms heading toward self */
        self = gp + offset;
        for (j = 0; j < 4; j++) {
            u32 st;
            u8* p;

            if (j == index) {
                continue;
            }

            p = gp + j * 0x40;
            st = (p[0xD4] >> 2) & 0x3F;

            if (st == 7) {
                if (*(f32*) (p + 0xE0) < *(f32*) (self + 0xE0)) {
                    result = 7;
                    continue;
                }
            }
            if (st == 8) {
                if (*(f32*) (p + 0xE0) > *(f32*) (self + 0xE0)) {
                    result = 8;
                }
            }
        }

        /* Final threshold check */
        if (*(f32*) (gp + offset + 0xE4) < -2000.0F) {
            result = 1;
        }
        break;
    }
    }

    return result;
}

#pragma push
#pragma fp_contract on
s32 grBigBlue_801EE398(Ground_GObj* gobj, s32 arg1, s32 arg2)
{
    s32 result = 0;
    Ground* gp = gobj->user_data;
    Vec3 pos;

    switch (arg2) {
    case 1: {
        s32 offset = arg1 << 6;
        u8* car_d4 = (u8*) gp + offset + 0xD4;
        u8* car;

        HSD_JObjSetFlagsAll(
            ((HSD_JObj**) gp->gv.bigblue.xC8)
                [(*(u16*) car_d4 >> 4) & 0x1F],
            0x10U);

        car = (u8*) gp + offset;
        if (*(f32*) (car + 0xE0) > 0.0f) {
            ((u8*) gp->gv.bigblue.xCC)
                [(*(u16*) car_d4 >> 4) & 0x1F] = 0;
        } else {
            ((u8*) gp->gv.bigblue.xCC)
                [(*(u16*) car_d4 >> 4) & 0x1F] = 2;
        }
        {
            register s32 st_val;
            register u8 byte;
            st_val = arg2;
            byte = *car_d4;
#ifdef MWERKS_GEKKO
            asm { rlwimi byte, st_val, 2, 24, 29 }
#endif
            result = 1;
            *car_d4 = byte;
        }
        break;
    }

    case 10: {
        s32 offset = arg1 << 6;
        {
            u8* base = (u8*) gp + offset;
            *(s32*) (base + 0xF0) = 0x14;
        }
        {
            s32 d4_off = offset + 0xD4;
            register s32 st_val;
            register u8 byte;
            st_val = arg2;
            result = 1;
            byte = ((u8*) gp)[d4_off];
#ifdef MWERKS_GEKKO
            asm { rlwimi byte, st_val, 2, 24, 29 }
#endif
            ((u8*) gp)[d4_off] = byte;
        }
        break;
    }

    case 2:
    case 3:
    case 4: {
        s32 hi = (s32) grBb_804D69C8->x60;
        s32 lo = (s32) grBb_804D69C8->x5C;

        if (lo > hi) {
            s32 diff = lo - hi;
            s32 rand_val;
            if (diff != 0) {
                rand_val = HSD_Randi(diff);
            } else {
                rand_val = 0;
            }
            lo = hi + rand_val;
        } else if (lo < hi) {
            s32 diff = hi - lo;
            s32 rand_val;
            if (diff != 0) {
                rand_val = HSD_Randi(diff);
            } else {
                rand_val = 0;
            }
            lo += rand_val;
        }
        {
            s32 offset = arg1 << 6;
            {
                u8* base = (u8*) gp + offset;
                *(s32*) (base + 0xF0) = lo;
            }
            {
                s32 d4_off = offset + 0xD4;
                register s32 st_val;
                register u8 byte;
                st_val = arg2;
                result = 1;
                byte = ((u8*) gp)[d4_off];
#ifdef MWERKS_GEKKO
                asm { rlwimi byte, st_val, 2, 24, 29 }
#endif
                ((u8*) gp)[d4_off] = byte;
            }
        }
        break;
    }

    case 5: {
        f32 blast = Stage_GetBlastZoneRightOffset();

        pos.x = (grBb_804D69C8->x68 * Ground_801C0498()) + blast;
        pos.z = 0.0f;
        pos.y = 0.0f;
        pos.y = grBigBlue_801EC58C(&pos, NULL, 1000.0f);

        if (grBb_804DB310 != pos.y) {
            s32 count = 0;
            s32 j;

            for (j = 0; j < 30; j++) {
                if (((u8*) gp->gv.bigblue.xCC)[j] == 0) {
                    count++;
                }
            }

            if (count != 0) {
                s32 pick;
                s32 slot = 0;
                s32 offset;
                u8* car;
                s32 dir;
                u8* car_d4;
                Vec3* car_e0;
                f32* car_ec;
                if (count != 0) {
                    pick = HSD_Randi(count);
                } else {
                    pick = slot;
                }

                for (slot = 0; slot < 30; slot++) {
                    if (((u8*) gp->gv.bigblue.xCC)[slot] == 0) {
                        if (--pick < 0) {
                            break;
                        }
                    }
                }

                offset = arg1 << 6;
                car = (u8*) gp + offset;

                {
                    register s32 slot_val;
                    register u16 hw;
                    slot_val = slot;
                    hw = *(u16*) (car + 0xD4);
#ifdef MWERKS_GEKKO
                    asm { rlwimi hw, slot_val, 4, 23, 27 }
#endif
                    dir = 0;
                    *(u16*) (car + 0xD4) = hw;
                }

                car_d4 = car + 0xD4;
                car_e0 = (Vec3*) (car + 0xE0);
                car_ec = (f32*) (car + 0xEC);

                {
                    register s32 dir_val;
                    register u8 byte;
                    dir_val = dir;
                    byte = car[0xD4];
#ifdef MWERKS_GEKKO
                    asm { rlwimi byte, dir_val, 1, 30, 30 }
#endif
                    car[0xD4] = byte;
                }

                *(f32*) (car + 0xE0) = pos.x;
                *(f32*) (car + 0xE4) =
                    (grBb_804D69C8->x2C * Ground_801C0498()) + pos.y;
                *(f32*) (car + 0xE8) = 0.0f;
                *(f32*) (car + 0xD8) = pos.x;
                *(f32*) (car + 0xDC) = 0.0f;

                *(f32*) (car + 0xF4) = 0.0f;
                *(f32*) (car + 0xF8) = 0.0f;
                *(f32*) (car + 0xFC) = 0.0f;
                *(f32*) (car + 0x100) = 0.0f;
                *(f32*) (car + 0x104) =
                    (f32) (M_TAU * HSD_Randf());
                *(f32*) (car + 0x108) =
                    grBb_804D69C8->x34 * Ground_801C0498();
                *(f32*) (car + 0x10C) = 0.0f;

                {
                    s32 hi = (s32) grBb_804D69C8->x60;
                    s32 lo = (s32) grBb_804D69C8->x5C;
                    if (lo > hi) {
                        s32 diff = lo - hi;
                        s32 rand_val;
                        if (diff != 0) {
                            rand_val = HSD_Randi(diff);
                        } else {
                            rand_val = dir;
                        }
                        lo = hi + rand_val;
                    } else if (lo < hi) {
                        s32 diff = hi - lo;
                        s32 rand_val;
                        if (diff != 0) {
                            rand_val = HSD_Randi(diff);
                        } else {
                            rand_val = dir;
                        }
                        lo += rand_val;
                    }
                    *(s32*) (car + 0xF0) = lo;
                }

                ((u8*) gp->gv.bigblue.xCC)[slot] = 1;
                *car_ec = 0.0f;

                {
                    Ground_801C5440(gp, slot, grBb_803E2EB8.x58[HSD_Randi(4)]);
                }

                Ground_801C5630(gp, arg1, *car_ec);

                {
                    HSD_JObj* jobj;
                    HSD_JObjClearFlagsAll(
                        ((HSD_JObj**) gp->gv.bigblue.xC8)[slot],
                        0x10U);
                    jobj = ((HSD_JObj**) gp->gv.bigblue.xC8)[slot];
                    HSD_JObjSetTranslate(jobj, car_e0);
                }

                {
                    register s32 st_val;
                    register u8 byte;
                    st_val = arg2;
                    byte = *car_d4;
#ifdef MWERKS_GEKKO
                    asm { rlwimi byte, st_val, 2, 24, 29 }
#endif
                    result = 1;
                    *car_d4 = byte;
                }
            }
        }
        break;
    }

    case 6: {
        f32 blast = Stage_GetBlastZoneLeftOffset();

        pos.x = -((grBb_804D69C8->x68 * Ground_801C0498()) - blast);
        pos.z = 0.0f;
        pos.y = 0.0f;
        pos.y = grBigBlue_801EC58C(&pos, NULL, 1000.0f);

        if (grBb_804DB310 != pos.y) {
            s32 count = 0;
            s32 j;

            for (j = 0; j < 30; j++) {
                if (((u8*) gp->gv.bigblue.xCC)[j] == 0) {
                    count++;
                }
            }

            if (count != 0) {
                s32 pick;
                s32 slot = 0;
                s32 offset;
                u8* car;
                s32 dir;
                u8* car_d4;
                Vec3* car_e0;
                f32* car_ec;

                if (count != 0) {
                    pick = HSD_Randi(count);
                } else {
                    pick = slot;
                }

                for (slot = 0; slot < 30; slot++) {
                    if (((u8*) gp->gv.bigblue.xCC)[slot] == 0) {
                        if (--pick < 0) {
                            break;
                        }
                    }
                }

                offset = arg1 << 6;
                car = (u8*) gp + offset;

                {
                    register s32 slot_val;
                    register u16 hw;
                    slot_val = slot;
                    hw = *(u16*) (car + 0xD4);
#ifdef MWERKS_GEKKO
                    asm { rlwimi hw, slot_val, 4, 23, 27 }
#endif
                    dir = 0;
                    *(u16*) (car + 0xD4) = hw;
                }

                car_d4 = car + 0xD4;
                car_e0 = (Vec3*) (car + 0xE0);
                car_ec = (f32*) (car + 0xEC);

                {
                    register s32 dir_val;
                    register u8 byte;
                    dir_val = dir;
                    byte = car[0xD4];
#ifdef MWERKS_GEKKO
                    asm { rlwimi byte, dir_val, 1, 30, 30 }
#endif
                    car[0xD4] = byte;
                }

                *(f32*) (car + 0xE0) = pos.x;
                *(f32*) (car + 0xE4) =
                    (grBb_804D69C8->x2C * Ground_801C0498()) + pos.y;
                *(f32*) (car + 0xE8) = 0.0f;
                *(f32*) (car + 0xD8) = pos.x;
                *(f32*) (car + 0xDC) = 0.0f;

                *(f32*) (car + 0xF4) = 0.0f;
                *(f32*) (car + 0xF8) = 0.0f;
                *(f32*) (car + 0xFC) = 0.0f;
                *(f32*) (car + 0x100) = 0.0f;
                *(f32*) (car + 0x104) =
                    (f32) (M_TAU * HSD_Randf());
                *(f32*) (car + 0x108) =
                    grBb_804D69C8->x34 * Ground_801C0498();
                *(f32*) (car + 0x10C) = 0.0f;

                {
                    s32 hi = (s32) grBb_804D69C8->x60;
                    s32 lo = (s32) grBb_804D69C8->x5C;
                    if (lo > hi) {
                        s32 diff = lo - hi;
                        s32 rand_val;
                        if (diff != 0) {
                            rand_val = HSD_Randi(diff);
                        } else {
                            rand_val = dir;
                        }
                        lo = hi + rand_val;
                    } else if (lo < hi) {
                        s32 diff = hi - lo;
                        s32 rand_val;
                        if (diff != 0) {
                            rand_val = HSD_Randi(diff);
                        } else {
                            rand_val = dir;
                        }
                        lo += rand_val;
                    }
                    *(s32*) (car + 0xF0) = lo;
                }

                ((u8*) gp->gv.bigblue.xCC)[slot] = 1;
                *car_ec = 0.0f;

                {
                    Ground_801C5440(gp, slot, grBb_803E2EB8.x58[HSD_Randi(4)]);
                }

                Ground_801C5630(gp, arg1, *car_ec);

                {
                    HSD_JObj* jobj;
                    HSD_JObjClearFlagsAll(
                        ((HSD_JObj**) gp->gv.bigblue.xC8)[slot],
                        0x10U);
                    jobj = ((HSD_JObj**) gp->gv.bigblue.xC8)[slot];
                    HSD_JObjSetTranslate(jobj, car_e0);
                }

                {
                    register s32 st_val;
                    register u8 byte;
                    st_val = arg2;
                    byte = *car_d4;
#ifdef MWERKS_GEKKO
                    asm { rlwimi byte, st_val, 2, 24, 29 }
#endif
                    result = 1;
                    *car_d4 = byte;
                }
            }
        }
        break;
    }

    case 7:
    case 8: {
        s32 offset = arg1 << 6;
        {
            u8* base = (u8*) gp + offset;
            *(s32*) (base + 0xF0) = 0x3E8;
        }
        {
            s32 d4_off = offset + 0xD4;
            register s32 st_val;
            register u8 byte;
            st_val = arg2;
            result = 1;
            byte = ((u8*) gp)[d4_off];
#ifdef MWERKS_GEKKO
            asm { rlwimi byte, st_val, 2, 24, 29 }
#endif
            ((u8*) gp)[d4_off] = byte;
        }
        break;
    }

    case 9: {
        s32 d4_off = (arg1 << 6) + 0xD4;
        register s32 st_val;
        register u8 byte;
        st_val = arg2;
        byte = ((u8*) gp)[d4_off];
#ifdef MWERKS_GEKKO
        asm { rlwimi byte, st_val, 2, 24, 29 }
#endif
        ((u8*) gp)[d4_off] = byte;
        break;
    }
    }

    return result;
}
#pragma pop

/// @todo Currently 83.62% match - compiler CSEs gp+offset into one register
/// (3 NV regs) instead of keeping them separate (4 NV regs with r28 for case
/// 4)
#pragma push
#pragma fp_contract on
bool grBigBlue_801EEF00(Ground_GObj* gobj, s32 index)
{
    s32 offset;
    u8* gp;

    offset = index << 6;
    gp = (u8*) gobj->user_data;

    switch ((gp[offset + 0xD4] >> 2) & 0x3F) {
    case 1:
        return 0;

    case 10: {
        f32 abs_speed;
        f32 scale;
        f32 norm;

        if (*(f32*) (gp + offset + 0xE0) > 0.0F) {
            abs_speed = *(f32*) (gp + offset + 0xFC);
            if (abs_speed < 0.0F) {
                abs_speed = -abs_speed;
            }
            scale = Ground_801C0498();
            norm = abs_speed / (grBb_804D69C8->x28 * scale);
            if ((f32) * (s32*) (gp + offset + 0xF0) > norm) {
                scale = Ground_801C0498();
                *(f32*) (gp + offset + 0x100) = -(grBb_804D69C8->x28 * scale);
            } else {
                scale = Ground_801C0498();
                *(f32*) (gp + offset + 0x100) = grBb_804D69C8->x28 * scale;
            }
        } else {
            abs_speed = *(f32*) (gp + offset + 0xFC);
            if (abs_speed < 0.0F) {
                abs_speed = -abs_speed;
            }
            scale = Ground_801C0498();
            norm = abs_speed / (grBb_804D69C8->x28 * scale);
            if ((f32) * (s32*) (gp + offset + 0xF0) > norm) {
                scale = Ground_801C0498();
                *(f32*) (gp + offset + 0x100) = grBb_804D69C8->x28 * scale;
            } else {
                scale = Ground_801C0498();
                *(f32*) (gp + offset + 0x100) = -(grBb_804D69C8->x28 * scale);
            }
        }
        break;
    }

    case 2: {
        f32 abs_speed;
        f32 scale;
        f32 norm;

        abs_speed = *(f32*) (gp + offset + 0xFC);
        if (abs_speed < 0.0F) {
            abs_speed = -abs_speed;
        }
        scale = Ground_801C0498();
        norm = abs_speed / (grBb_804D69C8->x28 * scale);
        if ((f32) * (s32*) (gp + offset + 0xF0) > norm) {
            if (*(f32*) (gp + offset + 0xE0) < Stage_GetCamBoundsRightOffset())
            {
                scale = Ground_801C0498();
                *(f32*) (gp + offset + 0x100) = grBb_804D69C8->x28 * scale;
                break;
            }
        }
        scale = Ground_801C0498();
        *(f32*) (gp + offset + 0x100) = -(grBb_804D69C8->x28 * scale);
        break;
    }

    case 3: {
        f32 abs_speed;
        f32 scale;
        f32 norm;

        abs_speed = *(f32*) (gp + offset + 0xFC);
        if (abs_speed < 0.0F) {
            abs_speed = -abs_speed;
        }
        scale = Ground_801C0498();
        norm = abs_speed / (grBb_804D69C8->x28 * scale);
        if ((f32) * (s32*) (gp + offset + 0xF0) > norm) {
            if (*(f32*) (gp + offset + 0xE0) > Stage_GetCamBoundsLeftOffset())
            {
                scale = Ground_801C0498();
                *(f32*) (gp + offset + 0x100) = -(grBb_804D69C8->x28 * scale);
                break;
            }
        }
        scale = Ground_801C0498();
        *(f32*) (gp + offset + 0x100) = grBb_804D69C8->x28 * scale;
        break;
    }

    case 4: {
        f32 target;
        f32 abs_speed;
        f32 scale;
        f32 total;
        f32 norm;

        target = *(f32*) (gp + offset + 0xD8);
        abs_speed = *(f32*) (gp + offset + 0xFC);
        if (abs_speed < 0.0F) {
            abs_speed = -abs_speed;
        }
        scale = Ground_801C0498();
        total = grBb_804D69C8->x28 * scale;
        norm = abs_speed / total;

        if (target > *(f32*) (gp + offset + 0xE0)) {
            if (*(f32*) (gp + offset + 0xFC) < 0.0F) {
                scale = Ground_801C0498();
                *(f32*) (gp + offset + 0x100) = grBb_804D69C8->x28 * scale;
            } else {
                f32 spd;
                f32 pos;
                f32 predicted;

                scale = Ground_801C0498();
                total = grBb_804D69C8->x28 * scale;
                spd = *(f32*) (gp + offset + 0xFC);
                pos = *(f32*) (gp + offset + 0xE0);
                predicted = spd * norm + pos;
                total = 0.5F * total;
                total = norm * total;
                predicted -= norm * total;

                if (predicted < target) {
                    scale = Ground_801C0498();
                    *(f32*) (gp + offset + 0x100) = grBb_804D69C8->x28 * scale;
                } else {
                    scale = Ground_801C0498();
                    *(f32*) (gp + offset + 0x100) =
                        -(grBb_804D69C8->x28 * scale);
                }
            }
        } else {
            if (*(f32*) (gp + offset + 0xFC) > 0.0F) {
                scale = Ground_801C0498();
                *(f32*) (gp + offset + 0x100) = -(grBb_804D69C8->x28 * scale);
            } else {
                f32 spd;
                f32 pos;
                f32 predicted;

                scale = Ground_801C0498();
                total = grBb_804D69C8->x28 * scale;
                spd = *(f32*) (gp + offset + 0xFC);
                pos = *(f32*) (gp + offset + 0xE0);
                predicted = spd * norm + pos;
                total = -total;
                total = 0.5F * total;
                total = norm * total;
                predicted -= norm * total;

                if (predicted < target) {
                    scale = Ground_801C0498();
                    *(f32*) (gp + offset + 0x100) = grBb_804D69C8->x28 * scale;
                } else {
                    scale = Ground_801C0498();
                    *(f32*) (gp + offset + 0x100) =
                        -(grBb_804D69C8->x28 * scale);
                }
            }
        }
        break;
    }

    case 5:
    case 6: {
        u8* p = gp + offset;

        *(f32*) (p + 0x100) = 0.0F;
        *(f32*) (p + 0xEC) += (1.0F / 60.0F);
        if (*(f32*) (p + 0xEC) > 1.0F) {
            *(f32*) (p + 0xEC) = 1.0F;
        }
        Ground_801C5630((Ground*) gp, index, *(f32*) (p + 0xEC));
        break;
    }

    case 7: {
        f32 scale = Ground_801C0498();

        *(f32*) (gp + offset + 0x100) = grBb_804D69C8->x28 * scale;
        break;
    }

    case 8: {
        f32 scale = Ground_801C0498();

        *(f32*) (gp + offset + 0x100) = -(grBb_804D69C8->x28 * scale);
        break;
    }

    case 9: {
        u8* p = gp + offset;

        *(f32*) (p + 0xEC) -= (1.0F / 60.0F);
        if (*(f32*) (p + 0xEC) < 0.0F) {
            *(f32*) (p + 0xEC) = 0.0F;
        }
        Ground_801C5630((Ground*) gp, index, *(f32*) (p + 0xEC));
        break;
    }
    }

    return 1;
}
#pragma pop

/// @todo Currently 98.03% match - float register allocation off by 1
void grBigBlue_801EF424(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    u8* car_i;
    u8* car_j;
    int i, j, k;
    int changed;
    f32 zero;
    f32 diff;
    f32 absDiff;

    grBigBlue_801ECB50(gobj);

    for (i = 0; i < 4; i++) {
        grBigBlue_801ED694(gobj, i);
    }

    zero = 0.0F;
    changed = 1;
    k = 0;

    while (k < 10 && changed != 0) {
        changed = 0;

        for (i = 0, car_i = (u8*) gp; i < 4; i++, car_i += 0x40) {
            if ((u32) ((car_i[0xD4] >> 2) & 0x3F) == 1U) {
                continue;
            }

            for (j = 0, car_j = (u8*) gp; j < 4; j++, car_j += 0x40) {
                if (i == j) {
                    continue;
                }

                if ((u32) ((car_j[0xD4] >> 2) & 0x3F) == 1U) {
                    continue;
                }

                diff = *(f32*) (car_i + 0xE0) - *(f32*) (car_j + 0xE0);

                if (diff < zero) {
                    absDiff = -diff;
                } else {
                    absDiff = diff;
                }

                if (absDiff < Ground_801C0498() * (f32) grBb_804D69C8->x20) {
                    f32 adjustment;
                    if (diff > zero) {
                        adjustment =
                            Ground_801C0498() * (f32) grBb_804D69C8->x20;
                    } else {
                        adjustment =
                            -(Ground_801C0498() * (f32) grBb_804D69C8->x20);
                    }

                    diff -= adjustment;
                    changed = 1;
                    diff = (f32) (diff * 0.5);

                    *(f32*) (car_i + 0xDC) -= diff;
                    *(f32*) (car_i + 0xE0) -= diff;
                    *(f32*) (car_j + 0xDC) += diff;
                    *(f32*) (car_j + 0xE0) += diff;
                }
            }
        }

        k++;
    }
}

/// @todo Currently 99.98% match - assert string relocation offset
void fn_801EF60C(Ground* gp, s32 joint_id, CollData* coll, s32 time_param,
                 s32 env, f32 force)
{
    s32 idx;
    s16* table;
    grBb_YakumonoParams* params;
    u8* p;
    s32 i;
    u16 hw;
    PAD_STACK(8);

    if ((s32) coll->x34_flags.b1234 != 1) {
        return;
    }
    if (env != 1) {
        return;
    }
    table = grBb_803E2D78.x84;

    for (idx = 0; idx < 30; table++, idx++) {
        if (joint_id == *table) {
            break;
        }
    }

    HSD_ASSERT(0xED9, idx != 30);

    params = grBb_804D69C8;
    p = (u8*) gp;

    for (i = 0; i < 4; i++) {
        hw = *(u16*) (p + 0xD4);
        if (((hw >> 4) & 0x1F) == idx) {
            *(f32*) (p + 0xF4) = -coll->x50 * params->x44;
        }
        p += 0x40;
    }
}

void grBigBlue_801EF7D8(Vec3* pos)
{
    HSD_GObj* gobj = Ground_801C2BA4(34);

    if (gobj != NULL && gobj->user_data != NULL) {
        pos->x = grBb_804DB3F0;
        pos->z = pos->y = grBb_804DB2F4;
    } else {
        pos->z = 0.0F;
        pos->y = 0.0F;
        pos->x = 0.0F;
    }
}

bool grBigBlue_801EF844(enum_t line_id)
{
    if (stage_info.internal_stage_id == 19 && line_id != -1) {
        s32 joint = mpJointFromLine(line_id);
        s32 result;

        result = joint == 33 || joint == 35 || joint == 38 || joint == 39 ||
                 joint == 40 || joint == 36 || joint == 37 || joint == 41 ||
                 joint == 42 || joint == 43 || joint == 44 || joint == 45 ||
                 joint == 46 || joint == 47 || joint == 48 || joint == 49 ||
                 joint == 50 || joint == 51 || joint == 52 || joint == 53 ||
                 joint == 54 || joint == 55 || joint == 56 || joint == 57 ||
                 joint == 58 || joint == 59 || joint == 60 || joint == 61 ||
                 joint == 62 || joint == 63 || joint == 64 || joint == 65;

        if (result) {
            return true;
        }
    }
    return false;
}

void fn_801EFB9C(HSD_GObj* gobj, int pass)
{
    if (gm_801A45E8(1) != 0 || gm_801A45E8(2) != 0 || Camera_8003010C() != 0) {
        return;
    }
    grDisplay_801C5DB0(gobj, pass);
}

DynamicsDesc* grBigBlue_801EFC0C(enum_t arg)
{
    return NULL;
}

bool grBigBlue_801EFC14(Vec3* a, int b, HSD_JObj* jobj)
{
    Vec3 vec;
    lb_8000B1CC(jobj, NULL, &vec);
    if (a->y > vec.y) {
        return true;
    } else {
        return false;
    }
}
