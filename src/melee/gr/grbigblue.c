#include "grbigblue.h"

#include "grdisplay.h"
#include "grfzerocar.h"
#include "grmaterial.h"
#include "ground.h"

#include <platform.h>

#include "baselib/gobjgxlink.h"
#include "baselib/gobjproc.h"
#include "baselib/jobj.h"
#include "baselib/memory.h"
#include "baselib/random.h"
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

#define M_TAU 6.283185307179586

extern StageInfo stage_info;
extern ItemKind grBb_803B8120[5];
typedef struct grBb_LineIds {
    s32 v[32];
} grBb_LineIds;

extern grBb_LineIds grBb_803B8134;

typedef struct grBb_TrackEntry {
    s16 jobj_index;
    s16 start_index;
    s16 end_index;
    s16 pad;
    Vec3 delta;
} grBb_TrackEntry;

typedef struct grBb_YakumonoParams {
    u8 pad[0x44];
    f32 x44;
    u8 pad2[0x134 - 0x48];
    Vec3 x134_translate;
    f32 x140_scale;
} grBb_YakumonoParams;

static grBb_YakumonoParams* grBb_804D69C8;

u8 tmpPadData[168] = { 0 };

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

static const Vec3 grBb_803B8108 = { 0.5F, 0.0F, 0.0F };
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
    u8 sp20[8];
    Vec3 sp14;
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
    sp14 = grBb_803B8108;
    lb_80011A50(&sp14, -1, 1.0F, 0.0F, M_PI / 3, -100000.0F, 100000.0F,
                100000.0F, -100000.0F);
}

void grBigBlue_801E59C8(void) {}

void grBigBlue_801E59CC(void)
{
    grZakoGenerator_801CAE04(0);
}

bool grBigBlue_801E59F0(void)
{
    return false;
}

HSD_GObj* grBigBlue_801E59F8(s32 id)
{
    HSD_GObj* gobj;
    StageCallbacks* cbs = &grBb_803E29E0[id];
    gobj = Ground_801C14D0(id);
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
            HSD_GObjProc_8038FD54(gobj, cbs->callback2, 4U);
        }
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grbigblue.c", 0x17E,
                 id);
    }
    return gobj;
}

void grBigBlue_801E5AE4(Ground_GObj* arg0)
{
    grAnime_801C8138(arg0, GET_GROUND(arg0)->map_id, 0);
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
    GET_GROUND(gobj)->gv.bigblue.x0_b0 = false;
}

void grBigBlue_801E613C(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = gobj->hsd_obj;
    PAD_STACK(16);

    grAnime_801C8138(gobj, gp->map_id, 0);
    Ground_801C2ED0(jobj, gp->map_id);
    grBigBlue_801EB004(gobj);
    gp->gv.bigblue.x0_b0 = true;
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

void grBigBlue_801E6200(Ground_GObj* arg0)
{
    Ground* gp;
    Ground* temp_r5;
    HSD_JObj* jobj;
    void* filler;

    gp = GET_GROUND(arg0);
    jobj = arg0->hsd_obj;
    grAnime_801C8138(arg0, gp->map_id, 0);
    temp_r5 = GET_GROUND(arg0);
    temp_r5->x10_flags.b2 = 0;
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

void grBigBlue_801E6298(Ground_GObj* arg0)
{
    HSD_JObj* temp_r31;
    HSD_JObj* temp_r30;
    HSD_JObj* temp_r29;
    HSD_JObj* temp_r28;
    HSD_JObj* temp_r27;

    Ground* gp = GET_GROUND(arg0);
    grAnime_801C8138(arg0, gp->map_id, 0);
    temp_r27 = Ground_801C3FA4(arg0, 6);
    temp_r28 = Ground_801C3FA4(arg0, 7);
    temp_r29 = Ground_801C3FA4(arg0, 3);
    temp_r30 = Ground_801C3FA4(arg0, 4);
    temp_r31 = Ground_801C3FA4(arg0, 2);
    Ground_801C4E70(Ground_801C3FA4(arg0, 5), temp_r31, temp_r30, temp_r29,
                    temp_r28, temp_r27);
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

    {
        s16* table = (s16*) ((u8*) tmpPadData + 0x488);
        for (i = 0; i < 30; i++) {
            ((HSD_JObj**) gp->gv.bigblue.xC8)[i] =
                Ground_801C3FA4(gobj, table[i]);
        }
    }

    car_gobj = grBigBlue_801E59F8(4);
    HSD_ASSERT(783, car_gobj != NULL);
    grFZeroCar_801CAFBC(car_gobj, (void*) ((u8*) tmpPadData + 0x44C), 30, 1);

    cur = HSD_JObjGetChild(car_gobj->hsd_obj);
    rot_y = 0.0F;
    scale_base = 1.0F;
    trans_x = -1.0F;

    for (i = 0; i < 30; i++) {
        child = HSD_JObjGetChild(cur);
        next = HSD_JObjGetNext(cur);

        HSD_JObjReparent(cur, ((HSD_JObj**) gp->gv.bigblue.xC8)[i]);
        HSD_JObjSetRotationY(cur, rot_y);

        scale.x = scale.y = scale.z =
            Ground_801C0498() * *(f32*) ((u8*) grBb_804D69C8 + 0xC);

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
        s32 max_val = *(s32*) ((u8*) grBb_804D69C8 + 0x10);
        s32 min_val = *(s32*) ((u8*) grBb_804D69C8 + 0x14);
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
    gp->gv.bigblue.xC8 = 0;
    HSD_Free((void*) gp->gv.bigblue.xCC);
    gp->gv.bigblue.xCC = 0;
}

// @TODO: Currently 99.98% match - near-perfect
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

    gp->gv.bigblue.x10 = Ground_801C3FA4(gobj, 1);
    gp->gv.bigblue.x14 = Ground_801C3FA4(gobj, 6);
    gp->gv.bigblue.x18 = Ground_801C3FA4(gobj, 11);

    gp->gv.bigblue.x20 = 0;
    gp->gv.bigblue.x21 = 0;
    *(s32*) ((u8*) gp + 0x134) = 0;
    ((u8*) gp)[0x138] = 1;
    ((u8*) gp)[0x139] = 0;
    *(s32*) ((u8*) gp + 0x188) = 0;
    ((u8*) gp)[0x18C] = 2;
    ((u8*) gp)[0x18D] = 0;
    *(s32*) ((u8*) gp + 0x1DC) = 0;
    *(s32*) ((u8*) gp + 0xC4) = 0;

    grBigBlue_801E8978(0, NULL, NULL);

    scale.x = scale.y = scale.z = Ground_801C0498();

    jobj = gp->gv.bigblue.x10;
    HSD_JObjSetScale(jobj, &scale);

    jobj = gp->gv.bigblue.x14;
    HSD_JObjSetScale(jobj, &scale);

    jobj = gp->gv.bigblue.x18;
    HSD_JObjSetScale(jobj, &scale);

    mpJointSetCb1(0, gp, (mpLib_Callback) fn_801E8560);
    mpJointSetCb1(1, gp, (mpLib_Callback) fn_801E8560);
    mpJointSetCb1(2, gp, (mpLib_Callback) fn_801E8560);
}

bool grBigBlue_801E6C58(Ground_GObj* arg)
{
    return false;
}

/// #grBigBlue_801E6C60

void grBigBlue_801E855C(Ground_GObj* arg) {}

// @TODO: Currently 87.65% match - register allocation and stack offset
void fn_801E8560(Ground* gp, s32 param, CollData* coll, s32 time_param,
                 s32 env, f32 arg5)
{
    HSD_JObj* jobj;
    s32 joint_index;
    Vec3 pos;
    f32 dx, dy, dist;
    s32 active_joint;
    u8* p;
    PAD_STACK(24);

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

    jobj = *(HSD_JObj**) ((u8*) gp + joint_index * 4 + 0xD4);

    if ((f32) time_param > 1000.0F) {
        time_param = 1000;
    }

    HSD_ASSERT(979, jobj != NULL);

    pos = jobj->translate;

    dx = pos.x - coll->cur_pos.x;
    dy = pos.y - coll->cur_pos.y;
    dist = dy * dy + dx * dx;

    dist = sqrtf(dist);

    if (dist > 2.0F) {
        active_joint = 0;
        if ((s8) ((u8*) gp)[0xE4] != joint_index) {
            p = (u8*) gp + 0x54;
            active_joint = 1;
            if ((s8) ((u8*) gp)[0x138] != joint_index) {
                active_joint = 2;
                if ((s8) p[0x138] != joint_index) {
                    active_joint = 3;
                }
            }
        }

        if (pos.x < coll->cur_pos.x) {
            *(f32*) ((u8*) gp + active_joint * 0x54 + 0x108) +=
                dist * ((f32) time_param / 1000.0F);
        } else {
            *(f32*) ((u8*) gp + active_joint * 0x54 + 0x10C) +=
                dist * ((f32) time_param / 1000.0F);
        }

        (*(s32*) ((u8*) gp + active_joint * 0x54 + 0x110))++;
    }
}

// @TODO: Currently 90.70% match - needs register allocation fix
bool grBigBlue_801E8794(void* arg0, Vec3* pos, bool checkSecondary, f32 rangeX,
                        f32 rangeY)
{
    u8* gp = (u8*) GET_GROUND(Ground_801C2BA4(0x20));
    bool result = false;
    f32 zero = 0.0F;
    int i;
    u8* base1 = gp;
    u8* base2 = gp;
    void* ptr;
    f32 dist;
    PAD_STACK(48);

    for (i = 0; i < 3; i++, base1 += 4, base2 += 0x54) {
        ptr = *(void**) (base1 + 0xD4);

        if (arg0 == ptr) {
            continue;
        }

        if ((s32) base2[0xE5] != 3) {
            continue;
        }

        if (ptr == NULL) {
            __assert(NULL, 993, NULL);
        }
        dist = *(f32*) ((u8*) ptr + 0x38) - pos->x;
        if (dist < zero) {
            ptr = *(void**) (base1 + 0xD4);
            if (ptr == NULL) {
                __assert(NULL, 993, NULL);
            }
            dist = -(*(f32*) ((u8*) ptr + 0x38) - pos->x);
        } else {
            ptr = *(void**) (base1 + 0xD4);
            if (ptr == NULL) {
                __assert(NULL, 993, NULL);
            }
            dist = *(f32*) ((u8*) ptr + 0x38) - pos->x;
        }

        if (dist < rangeX) {
            ptr = *(void**) (base1 + 0xD4);
            if (ptr == NULL) {
                __assert(NULL, 1006, NULL);
            }
            dist = *(f32*) ((u8*) ptr + 0x3C) - pos->y;
            if (dist < zero) {
                ptr = *(void**) (base1 + 0xD4);
                if (ptr == NULL) {
                    __assert(NULL, 1006, NULL);
                }
                dist = -(*(f32*) ((u8*) ptr + 0x3C) - pos->y);
            } else {
                ptr = *(void**) (base1 + 0xD4);
                if (ptr == NULL) {
                    __assert(NULL, 1006, NULL);
                }
                dist = *(f32*) ((u8*) ptr + 0x3C) - pos->y;
            }

            if (dist < rangeY) {
                result = true;
                break;
            }

            if (checkSecondary && (s8) base2[0xE6] == -1) {
                result = true;
                break;
            }
        } else {
            if (checkSecondary && (s8) base2[0xE6] == -1) {
                result = true;
                break;
            }
        }
    }

    return result;
}

void grBigBlue_801E8978(int arg0, void* arg1, void* arg2)
{
    u8* gp = (u8*) GET_GROUND(Ground_801C2BA4(0x20));
    if (arg2 != NULL) {
        *(void**) (gp + 0xE0) = arg2;
    }
    gp += arg0 * 4;
    *(void**) (gp + 0xC8) = arg1;
}

void* grBigBlue_801E89DC(int arg)
{
    u8* gp = (u8*) GET_GROUND(Ground_801C2BA4(0x20));
    gp += arg * 4;
    return *(void**) (gp + 0xC8);
}

// @TODO: Currently 79.9% match - platform/store use lwzx/stwx instead of
// add+lwz/stw (addressing mode difference), candPtr init missing slwi+add
void grBigBlue_801E8A1C(int idx)
{
    u8* gp = (u8*) GET_GROUND(Ground_801C2BA4(0x20));
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

// @TODO: Currently 94.71% match - needs pointer advancement and i variable
f32 grBigBlue_801E8B84(f32 arg1, f32 arg2, f32 arg3, f32 arg4)
{
    u8* gp = (u8*) GET_GROUND(Ground_801C2BA4(0x21));
    int i = 0;
    f32 result = 0.0F;

    for (i = 0; i < 4; i++) {
        if ((unsigned) (gp[0xD4] >> 2 & 0x3F) != 1U) {
            if (*(f32*) (gp + 0xE4) < arg1 &&
                *(f32*) (gp + 0xE4) > arg2)
            {
                if (*(f32*) (gp + 0xE0) < arg4 &&
                    *(f32*) (gp + 0xE0) > arg3)
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

void grBigBlue_801E8D04(void)
{
    f32 val4, val3, val2, val1;
    val1 = HSD_Randf();
    val2 = HSD_Randf();
    val3 = HSD_Randf();
    val4 = HSD_Randf();
    Ground_801C38D0(val4, val3, val2, val1);
}

void grBigBlue_801E8D64(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    HSD_JObj* jobj = gobj->hsd_obj;
    Vec3 pos;
    Vec3 scale;
    Vec3 translate;
    f32 y_pos;
    FORCE_PAD_STACK(16);

    Ground_801C2ED0(jobj, gp->map_id);
    gp->x10_flags.b5 = 1;

    scale.x = scale.y = scale.z = Ground_801C0498();
    HSD_JObjSetScale(jobj, &scale);

    {
        HSD_GObj* other = Ground_801C2BA4(32);
        Ground* other_gp = other->user_data;
        *(s32*) ((u8*) other_gp + 0xCC) = 1;
    }

    y_pos = grBigBlue_801EC58C(&pos, NULL, 0.0F);
    if (y_pos == 0.0F) {
        y_pos = 1.0F;
    }

    HSD_JObjSetTranslateX(jobj, 0.0F);

    y_pos += *(f32*) ((u8*) grBb_804D69C8 + 0xCC);
    HSD_JObjSetTranslateY(jobj, y_pos);

    HSD_JObjSetTranslateZ(jobj, 0.0F);

    *(f32*) ((u8*) gp + 0xD8) = 0.0F;
    *(s32*) ((u8*) gp + 0xC8) =
        (s32) (*(f32*) ((u8*) grBb_804D69C8 + 0xD8));
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

/// #grBigBlue_801E93D8

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
    *(s32*) ((u8*) GET_GROUND(Ground_801C2BA4(0x20)) + 0xD0) = 0;
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grBigBlue_801EA054(Ground_GObj* arg)
{
    return false;
}

/// #grBigBlue_801EA05C

void grBigBlue_801EAB4C(Ground_GObj* arg) {}

bool grBigBlue_801EAB50(Vec3* pos, s32 flag, f32 rangeX, f32 rangeY)
{
    HSD_GObj* gobj = Ground_801C2BA4(0x20);
    u8* gp = (u8*) gobj->user_data;
    HSD_JObj* jobj = GET_JOBJ(gobj);
    s32 result = false;
    f32 dist;
    PAD_STACK(32);

    if ((int) gp[0xC4] == 2) {
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
            if ((s8) gp[0xC5] == -1) {
                result = true;
            }
        }
    }

    return result;
}

// @TODO: Currently 98.17% match - car section generates fnmsubs instead of
// fmuls+fsubs; compiler fuses multiply-subtract differently than target
s32 grBigBlue_801EACE8(HSD_JObj* exclude, Vec3* point, f32* out_y,
                       f32 half_range_x, f32 half_range_y)
{
    HSD_GObj* gobj;
    u8* gp;
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
    PAD_STACK(32);

    gobj = Ground_801C2BA4(0x20);

    left_bound = point->x - half_range_x;
    right_bound = point->x + half_range_x;
    top_bound = point->y + half_range_y;
    bottom_bound = point->y - half_range_y;

    best_in_range = F32_MAX;
    best_above = -F32_MAX;

    gp = (u8*) gobj->user_data;
    p_left = &hw_left.x;
    p_right = &hw_right.x;

    for (i = 0; i < 3; i++, p_left++, p_right++) {
        jobj = *(HSD_JObj**) (gp + 0xD4 + i * 4);

        if (exclude == jobj) {
            continue;
        }

        if ((int) gp[0xE5 + i * 0x54] != 3) {
            continue;
        }

        HSD_JObjGetTranslation2(jobj, &pos);

        hw_left = grBb_803B8114;
        left_x = pos.x - *p_left * Ground_801C0498();

        hw_right = grBb_803B8114;
        right_x = pos.x + *p_right * Ground_801C0498();

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
    gobj = Ground_801C2BA4(0x24);
    jobj = (HSD_JObj*) gobj->hsd_obj;
    gp = (u8*) gobj->user_data;

    if (exclude != jobj && (int) gp[0xC4] == 2) {
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

// @TODO: Currently 94.90% match - needs bitfield struct for rlwimi
// generation and stack frame fix (120 vs 112 bytes)
void grBigBlue_801EB004(Ground_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    u8* gp = (u8*) gobj->user_data;
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

    gp[0xC6] = gp[0xC6] & ~0x7F;

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

        gp[0xC7] = gp[0xC7] & 0x0F;
        gp[0xC4] = gp[0xC4] & ~0x02;
        gp[0xC4] = gp[0xC4] & ~0x04;
    }

    {
        u32 idx = (*(u32*) (gp + 0xC4) >> 15) & 0x7F;
        HSD_JObj* active =
            Ground_801C3FA4(gobj, grBb_TrackEntries[idx].jobj_index);

        HSD_JObjClearFlagsAll(active, JOBJ_HIDDEN);

        pos.x = 0.0F;
        pos.y = *(f32*) grBb_804D69C8 * Ground_801C0498();
        pos.z = 0.0F;

        HSD_JObjSetTranslate(active, &pos);
    }

    {
        u32 idx2 = gp[0xC6] & 0x7F;
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

/// @todo: Currently partial match - needs register allocation and
/// bitfield rlwimi fixes.
void grBigBlue_801EB4AC(Ground_GObj* gobj)
{
    u8* gp = (u8*) gobj->user_data;
    s32 count = 0;
    HSD_JObj* jobj;
    grBb_TrackEntry* entry;
    Vec3 sp_pos;
    f32 f30;
    f32 f31;
    s32 random_lane;

    /* Hide current lane's jobj */
    HSD_JObjSetFlagsAll(
        Ground_801C3FA4(gobj,
            grBb_TrackEntries[
                (*(u32*) (gp + 0xC4) >> 15) & 0x7F].jobj_index),
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
        u8 next = gp[0xC6];
        u32 word = *(u32*) (gp + 0xC4);
        word = (word & ~0x003F8000) | (((u32) next << 15) & 0x003F8000);
        *(u32*) (gp + 0xC4) = word;
    }

    /* Get new lane's jobj and position */
    jobj = Ground_801C3FA4(gobj,
        grBb_TrackEntries[gp[0xC6] & 0x7F].jobj_index);

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
            f32 speed = *(f32*) ((u8*) grBb_804D69C8 + 0x08);
            f32 vel = *(f32*) (gp + 0xCC);

            if (vel < grBb_804D69C8->x44 * speed * scale) {
                *(s16*) (gp + 0xF0) = 0;
            }
        } else if (direction == -1) {
            f32 scale = Ground_801C0498();
            f32 speed = *(f32*) ((u8*) grBb_804D69C8 + 0x04);
            f32 vel = *(f32*) (gp + 0xCC);

            if (vel > -(speed * scale) * grBb_804D69C8->x44) {
                *(s16*) (gp + 0xF0) = 0;
            }
        } else {
            f32 scale = Ground_801C0498();
            f32 vel = *(f32*) (gp + 0xCC);
            f32 neg_speed =
                -(*(f32*) ((u8*) grBb_804D69C8 + 0x04) * scale);

            if (vel < neg_speed) {
                *(s16*) (gp + 0xF0) = -1;
            } else {
                f32 scale2 = Ground_801C0498();
                f32 pos_speed =
                    *(f32*) ((u8*) grBb_804D69C8 + 0x08) * scale2;

                if (vel > pos_speed) {
                    *(s16*) (gp + 0xF0) = 1;
                }
            }
        }
    }

    /* Random lane selection loop */
    f30 = 0.0F;
    f31 = 0.0F;

    for (;;) {
        HSD_ASSERT(2414, count <= 1000);
        count++;

        random_lane = HSD_Randi(12);
        entry = &grBb_TrackEntries[random_lane];

        /* If lane 11: check velocity requirement */
        if (random_lane == 11) {
            if (*(f32*) (gp + 0xCC) < f30) {
                continue;
            }
        }

        /* Reject if same as current lane */
        if (((*(u32*) (gp + 0xC4) >> 15) & 0x7F) == (u32) random_lane) {
            continue;
        }

        /* Direction flag check */
        if (gp[0xC4] & 0x80) {
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
                if (entry->delta.y < f31) {
                    continue;
                }
            }
            if (dir == -1) {
                if (entry->delta.y > f31) {
                    continue;
                }
            }
        }

        /* Reachability check */
        {
            f32 scale = Ground_801C0498();
            f32 vel = *(f32*) (gp + 0xCC);
            f32 speed = *(f32*) ((u8*) grBb_804D69C8 + 0x08);
            f32 target = speed * scale + vel;
            f32 pos = sp_pos.y +
                grBb_TrackEntries[
                    (*(u32*) (gp + 0xC4) >> 15) & 0x7F].delta.y +
                entry->delta.y;

            if (pos < target) {
                continue;
            }
        }
        break;
    }

    /* Store new lane index into gp+0xC6 */
    gp[0xC6] = (gp[0xC6] & ~0x7F) | (random_lane & 0x7F);

    HSD_ASSERT(979, jobj);

    /* Save current jobj translate (struct copy generates lwz/stw) */
    sp_pos = jobj->translate;

    /* Get new lane jobj and unhide */
    jobj = Ground_801C3FA4(gobj, entry->jobj_index);
    HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);

    /* Add current lane deltas (re-extract lane each time, no CSE) */
    sp_pos.x +=
        grBb_TrackEntries[(*(u32*) (gp + 0xC4) >> 15) & 0x7F].delta.x;
    sp_pos.y +=
        grBb_TrackEntries[(*(u32*) (gp + 0xC4) >> 15) & 0x7F].delta.y;
    sp_pos.z +=
        grBb_TrackEntries[(*(u32*) (gp + 0xC4) >> 15) & 0x7F].delta.z;

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
            u8 byte = gp[0xC7];
            byte = (byte & ~0xF0) | (0 & 0xF0);
            gp[0xC7] = byte;
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

/// #grBigBlue_801EBAF8

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

// @TODO: Currently 90.40% match - needs register allocation fix (stmw r24 vs
// r23) and bitfield write pattern fix (rlwinm+ori vs rlwimi)
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
    s16* table;
    f32 scale;
    f32 lerp;
    s32 lo;
    s32 hi;
    HSD_JObj* jobj;

    i = 0;
    table = (s16*) ((u8*) tmpPadData + 0x4C4);

    while (i < 30) {
        u8 val;
        mpJointSetCb1(*table, gp, (mpLib_Callback) fn_801EF60C);
        HSD_JObjSetFlagsAll(((HSD_JObj**) gp->gv.bigblue.xC8)[i], 16);
        val = HSD_Randi(2) ? 0 : 2;
        ((u8*) gp->gv.bigblue.xCC)[i] = val;
        table++;
        i++;
    }

    {
        s32* p = (s32*) ((u8*) grBb_804D69C8 + 0x18);
        if (*p == 0) {
            *p = 1;
        }
    }

    car = (u8*) gp;
    for (k = 0; k < 4; k++, car += 0x40) {
        if (k < *(s32*) ((u8*) grBb_804D69C8 + 0x18)) {
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
            lerp =
                (f32) (k + 1) * ((f32) * (s32*) ((u8*) params + 0x1C) * scale /
                                 (f32) (*(s32*) ((u8*) params + 0x18) + 1));

            scale = Ground_801C0498();
            params = grBb_804D69C8;
            *(f32*) (car + 0xE0) =
                lerp + 0.5F * (-(f32) * (s32*) ((u8*) params + 0x1C) * scale);

            scale = Ground_801C0498();
            params = grBb_804D69C8;
            lerp = *(f32*) ((u8*) params + 0x2C) * scale;

            scale = Ground_801C0498();
            params = grBb_804D69C8;
            *(f32*) (car + 0xE4) =
                *(f32*) ((u8*) params + 0x00) * scale + lerp;

            *(f32*) (car + 0xE8) = 0.0F;

            params = grBb_804D69C8;
            scale = Ground_801C0498();
            lerp =
                (f32) (k + 1) * ((f32) * (s32*) ((u8*) params + 0x1C) * scale /
                                 (f32) (*(s32*) ((u8*) params + 0x18) + 1));

            scale = Ground_801C0498();
            params = grBb_804D69C8;
            *(f32*) (car + 0xD8) =
                lerp + 0.5F * (-(f32) * (s32*) ((u8*) params + 0x1C) * scale);

            *(f32*) (car + 0xDC) = 0.0F;

            *(f32*) (car + 0xF4) = 0.0F;
            *(f32*) (car + 0xF8) = 0.0F;
            *(f32*) (car + 0xFC) = 0.0F;
            *(f32*) (car + 0x100) = 0.0F;

            *(f32*) (car + 0x104) = (f32) (2.0 * M_PI * HSD_Randf());

            scale = Ground_801C0498();
            params = grBb_804D69C8;
            *(f32*) (car + 0x108) = *(f32*) ((u8*) params + 0x34) * scale;

            *(f32*) (car + 0x10C) = 0.0F;

            params = grBb_804D69C8;
            hi = (s32) * (f32*) ((u8*) params + 0x60);
            lo = (s32) * (f32*) ((u8*) params + 0x5C);
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
                u8* snd = (u8*) tmpPadData + HSD_Randi(4) * 4;
                Ground_801C5440(gp, k, *(u32*) (snd + 0x6D8));
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

/// #grBigBlue_801ECB50

/// @todo: Currently partial match - complex car physics simulation
#pragma push
#pragma fp_contract on
void grBigBlue_801ED694(Ground_GObj* gobj, s32 lane)
{
    u8* gp = (u8*) gobj->user_data;
    s32 lane_offset;
    HSD_JObj* jobj;
    s32 active;
    s32 behind;
    f32 f29;
    f32 f30;
    f32 f31_rot;
    f32 f28;
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
                    if (idx != lane &&
                        *(f32*) (gp + 0xE0) <
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
                    if (idx != lane &&
                        *(f32*) (iter + 0xE0) <
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
                    if (idx != lane &&
                        *(f32*) (iter + 0xE0) <
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
                    if (idx != lane &&
                        *(f32*) (iter + 0xE0) <
                            *(f32*) (gp + lane_offset + 0xE0))
                    {
                        behind++;
                    }
                }
            }

            /* Compute ranking-based target */
            {
                f32 scale = Ground_801C0498();
                s32 total = *(s32*) ((u8*) grBb_804D69C8 + 0x1C);
                f29 = (f32)(behind + 1) *
                    ((f32)(active + 1) * scale / (f32) total);
            }

            {
                f32 scale = Ground_801C0498();
                s32 total = *(s32*) ((u8*) grBb_804D69C8 + 0x1C);
                target = 0.5F * (-(f32) total * scale) + f29;
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
    *(f32*) (gp + lane_offset + 0xFC) +=
        *(f32*) (gp + lane_offset + 0x100);

    /* Clamp velocity to +-max_speed*scale */
    {
        f32 scale = Ground_801C0498();
        f32 vel = *(f32*) (gp + lane_offset + 0xFC);
        f32 max_spd = *(f32*) ((u8*) grBb_804D69C8 + 0x24);

        if (vel > max_spd * scale) {
            f32 s2 = Ground_801C0498();
            *(f32*) (gp + lane_offset + 0xFC) =
                *(f32*) ((u8*) grBb_804D69C8 + 0x24) * s2;
        } else {
            f32 s2 = Ground_801C0498();
            f32 lim = *(f32*) ((u8*) grBb_804D69C8 + 0x24) * s2;

            if (vel < -lim) {
                f32 s3 = Ground_801C0498();
                *(f32*) (gp + lane_offset + 0xFC) =
                    -(*(f32*) ((u8*) grBb_804D69C8 + 0x24) * s3);
            }
        }
    }

    /* Position update: xDC += vel, xE0 = xD8 + xDC */
    {
        f32 vel = *(f32*) (gp + lane_offset + 0xFC);
        *(f32*) (gp + lane_offset + 0xDC) += vel;
        *(f32*) (gp + lane_offset + 0xE0) =
            *(f32*) (gp + lane_offset + 0xD8) +
            *(f32*) (gp + lane_offset + 0xDC);
    }

    /* Height/bounce simulation */
    if (!((gp[lane_offset + 0xD4] >> 1) & 1)) {
        f32 scale = Ground_801C0498();
        f32 grav = *(f32*) ((u8*) grBb_804D69C8 + 0x48);

        *(f32*) (gp + lane_offset + 0xF4) += grav * scale;
        *(f32*) (gp + lane_offset + 0xF8) +=
            *(f32*) (gp + lane_offset + 0xF4);

        if (*(f32*) (gp + lane_offset + 0xF8) > 0.0F) {
            *(f32*) (gp + lane_offset + 0xF8) = 0.0F;
            *(f32*) (gp + lane_offset + 0xF4) = 0.0F;
        } else {
            f32 s2 = Ground_801C0498();
            f32 blim = *(f32*) ((u8*) grBb_804D69C8 + 0x4C);

            if (*(f32*) (gp + lane_offset + 0xF8) < -(blim * s2)) {
                f32 s3 = Ground_801C0498();
                *(f32*) (gp + lane_offset + 0xF8) =
                    -(*(f32*) ((u8*) grBb_804D69C8 + 0x4C) * s3);
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
            f30 = *(f32*) ((u8*) grBb_804D69C8 + 0x24) * s1;
            {
                f32 s2 = Ground_801C0498();
                f29 = *(f32*) ((u8*) grBb_804D69C8 + 0x34) * s2;
            }
            {
                f32 s3 = Ground_801C0498();
                f32 curve = *(f32*) ((u8*) grBb_804D69C8 + 0x38);
                f29 = vel * ((curve * s3 - f29) / f30);
            }
            {
                f32 s4 = Ground_801C0498();
                heading_val =
                    *(f32*) ((u8*) grBb_804D69C8 + 0x34) * s4 + f29;
            }
        } else if (vel < 0.0F) {
            f32 s1 = Ground_801C0498();
            f30 = *(f32*) ((u8*) grBb_804D69C8 + 0x24) * s1;
            {
                f32 s2 = Ground_801C0498();
                f29 = *(f32*) ((u8*) grBb_804D69C8 + 0x34) * s2;
            }
            {
                f32 s3 = Ground_801C0498();
                f32 curve = *(f32*) ((u8*) grBb_804D69C8 + 0x30);
                f29 = vel * ((curve * s3 - f29) / f30);
            }
            {
                f32 s4 = Ground_801C0498();
                heading_val =
                    *(f32*) ((u8*) grBb_804D69C8 + 0x34) * s4 + f29;
            }
        } else {
            f32 s1 = Ground_801C0498();
            heading_val = *(f32*) ((u8*) grBb_804D69C8 + 0x34) * s1;
        }
    } else {
        heading_val = 0.0F;
    }

    /* Heading target interpolation */
    {
        f32 ht = *(f32*) (gp + lane_offset + 0x108);
        f32 interp = *(f32*) ((u8*) grBb_804D69C8 + 0x3C);
        ht += interp * (heading_val - ht);
        *(f32*) (gp + lane_offset + 0x108) = ht;
    }

    /* Rotation angle update */
    {
        f32 rotation;
        f32 ang_accel = *(f32*) ((u8*) grBb_804D69C8 + 0x40);

        *(f32*) (gp + lane_offset + 0x104) +=
            (f32) 0.017453292F * ang_accel;
        rotation = *(f32*) (gp + lane_offset + 0x104);

        if (rotation > M_TAU) {
            rotation = (f32)(rotation - M_TAU);
            *(f32*) (gp + lane_offset + 0x104) = rotation;
        }

        f28 = *(f32*) (gp + lane_offset + 0x108) * sinf(rotation);
    }

    /* Compute ground reference level */
    {
        f32 scale = Ground_801C0498();
        f32 drag = *(f32*) ((u8*) grBb_804D69C8 + 0x2C);
        f32 lat = *(f32*) (gp + lane_offset + 0xE4);
        f32 height = *(f32*) (gp + lane_offset + 0xF8);

        f29 = (lat - drag * scale) - height - f28;
    }

    /* Collision/grounding check */
    if ((gp[lane_offset + 0xD4] >> 1) & 1) {
        /* Grounded path */
        f30 = grBigBlue_801EC58C(
            (Vec3*) (gp + lane_offset + 0xE0), &sp_vec,
            (f32) 1.5707963F);

        if (0.0F != f30 && f30 > f29) {
            if (*(f32*) (gp + lane_offset + 0x10C) < 0.0F) {
                u8 byte = gp[lane_offset + 0xD4];
                gp[lane_offset + 0xD4] = (byte & ~0x02);
                goto heading_converge;
            }
        }

        if (0.0F != f30) {
            f32 s = Ground_801C0498();
            f32 decay = *(f32*) ((u8*) grBb_804D69C8 + 0x80);
            *(f32*) (gp + lane_offset + 0x10C) -= 3.0F * decay * s;
        } else {
            f32 s = Ground_801C0498();
            f32 decay = *(f32*) ((u8*) grBb_804D69C8 + 0x80);
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
                *(f32*) (track_gp + 0xCC) -
                *(f32*) (track_gp + 0xD8);
        }
    } else {
        /* Non-grounded path */
        f32 s = Ground_801C0498();
        f30 = grBigBlue_801EC58C(
            (Vec3*) (gp + lane_offset + 0xE0), &sp_vec,
            20.0F * s);

        if (0.0F != f30) {
            f32 s2 = Ground_801C0498();
            f32 drag = *(f32*) ((u8*) grBb_804D69C8 + 0x2C);
            *(f32*) (gp + lane_offset + 0xE4) =
                f28 + *(f32*) (gp + lane_offset + 0xF8) +
                (drag * s2 + f30);
        } else {
            gp[lane_offset + 0xD4] =
                (gp[lane_offset + 0xD4] & ~0x02) | 0x02;
            {
                f32 s2 = Ground_801C0498();
                f29 = *(f32*) ((u8*) grBb_804D69C8 + 0x84) * s2;
            }
            *(f32*) (gp + lane_offset + 0x10C) = sinf(f31_rot) * f29;
        }
    }

heading_converge:
    /* Update rotation: smooth toward target angle */
    if (0.0F != f30 && !((gp[lane_offset + 0xD4] >> 1) & 1)) {
        f32 angle = atan2f(-sp_vec.x, sp_vec.y);
        f32 smooth = *(f32*) ((u8*) grBb_804D69C8 + 0x50);
        f31_rot += smooth * (angle - f31_rot);
    } else {
        f32 target_angle =
            (f32) 0.017453292F *
            *(f32*) ((u8*) grBb_804D69C8 + 0x58);
        f32 damp = *(f32*) ((u8*) grBb_804D69C8 + 0x54);
        f31_rot += damp * (target_angle - f31_rot);
    }

    /* Update jobj transform */
    HSD_JObjSetTranslate(jobj, (Vec3*) (gp + lane_offset + 0xE0));
    HSD_JObjSetRotationZ(jobj, f31_rot);
}
#pragma pop

// @TODO: Currently 87.41% match - compiler CSEs gp+offset into one register
// (4 NV regs) instead of keeping them separate (5 NV regs, stmw r27)
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
    case 7: {
        f32 blast = Stage_GetBlastZoneRightOffset();
        f32 scale = Ground_801C0498();

        if (*(f32*) (gp + offset + 0xE0) >
            blast + *(f32*) ((u8*) grBb_804D69C8 + 0x68) * scale)
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

        if (*(f32*) (gp + offset + 0xE0) <
            blast - *(f32*) ((u8*) grBb_804D69C8 + 0x68) * scale)
        {
            if (0.0F != *(f32*) (gp + offset + 0xEC)) {
                result = 9;
            } else {
                result = 1;
            }
        }
        break;
    }
    case 9:
        if (0.0F == *(f32*) (gp + offset + 0xEC)) {
            result = 1;
        }
        break;
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

/// #grBigBlue_801EE398

// @TODO: Currently 83.62% match - compiler CSEs gp+offset into one register
// (3 NV regs) instead of keeping them separate (4 NV regs with r28 for case 4)
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
            norm = abs_speed / (*(f32*) ((u8*) grBb_804D69C8 + 0x28) * scale);
            if ((f32) * (s32*) (gp + offset + 0xF0) > norm) {
                scale = Ground_801C0498();
                *(f32*) (gp + offset + 0x100) =
                    -(*(f32*) ((u8*) grBb_804D69C8 + 0x28) * scale);
            } else {
                scale = Ground_801C0498();
                *(f32*) (gp + offset + 0x100) =
                    *(f32*) ((u8*) grBb_804D69C8 + 0x28) * scale;
            }
        } else {
            abs_speed = *(f32*) (gp + offset + 0xFC);
            if (abs_speed < 0.0F) {
                abs_speed = -abs_speed;
            }
            scale = Ground_801C0498();
            norm = abs_speed / (*(f32*) ((u8*) grBb_804D69C8 + 0x28) * scale);
            if ((f32) * (s32*) (gp + offset + 0xF0) > norm) {
                scale = Ground_801C0498();
                *(f32*) (gp + offset + 0x100) =
                    *(f32*) ((u8*) grBb_804D69C8 + 0x28) * scale;
            } else {
                scale = Ground_801C0498();
                *(f32*) (gp + offset + 0x100) =
                    -(*(f32*) ((u8*) grBb_804D69C8 + 0x28) * scale);
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
        norm = abs_speed / (*(f32*) ((u8*) grBb_804D69C8 + 0x28) * scale);
        if ((f32) * (s32*) (gp + offset + 0xF0) > norm) {
            if (*(f32*) (gp + offset + 0xE0) < Stage_GetCamBoundsRightOffset())
            {
                scale = Ground_801C0498();
                *(f32*) (gp + offset + 0x100) =
                    *(f32*) ((u8*) grBb_804D69C8 + 0x28) * scale;
                break;
            }
        }
        scale = Ground_801C0498();
        *(f32*) (gp + offset + 0x100) =
            -(*(f32*) ((u8*) grBb_804D69C8 + 0x28) * scale);
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
        norm = abs_speed / (*(f32*) ((u8*) grBb_804D69C8 + 0x28) * scale);
        if ((f32) * (s32*) (gp + offset + 0xF0) > norm) {
            if (*(f32*) (gp + offset + 0xE0) > Stage_GetCamBoundsLeftOffset())
            {
                scale = Ground_801C0498();
                *(f32*) (gp + offset + 0x100) =
                    -(*(f32*) ((u8*) grBb_804D69C8 + 0x28) * scale);
                break;
            }
        }
        scale = Ground_801C0498();
        *(f32*) (gp + offset + 0x100) =
            *(f32*) ((u8*) grBb_804D69C8 + 0x28) * scale;
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
        total = *(f32*) ((u8*) grBb_804D69C8 + 0x28) * scale;
        norm = abs_speed / total;

        if (target > *(f32*) (gp + offset + 0xE0)) {
            if (*(f32*) (gp + offset + 0xFC) < 0.0F) {
                scale = Ground_801C0498();
                *(f32*) (gp + offset + 0x100) =
                    *(f32*) ((u8*) grBb_804D69C8 + 0x28) * scale;
            } else {
                f32 spd;
                f32 pos;
                f32 predicted;

                scale = Ground_801C0498();
                total = *(f32*) ((u8*) grBb_804D69C8 + 0x28) * scale;
                spd = *(f32*) (gp + offset + 0xFC);
                pos = *(f32*) (gp + offset + 0xE0);
                predicted = spd * norm + pos;
                total = 0.5F * total;
                total = norm * total;
                predicted -= norm * total;

                if (predicted < target) {
                    scale = Ground_801C0498();
                    *(f32*) (gp + offset + 0x100) =
                        *(f32*) ((u8*) grBb_804D69C8 + 0x28) * scale;
                } else {
                    scale = Ground_801C0498();
                    *(f32*) (gp + offset + 0x100) =
                        -(*(f32*) ((u8*) grBb_804D69C8 + 0x28) * scale);
                }
            }
        } else {
            if (*(f32*) (gp + offset + 0xFC) > 0.0F) {
                scale = Ground_801C0498();
                *(f32*) (gp + offset + 0x100) =
                    -(*(f32*) ((u8*) grBb_804D69C8 + 0x28) * scale);
            } else {
                f32 spd;
                f32 pos;
                f32 predicted;

                scale = Ground_801C0498();
                total = *(f32*) ((u8*) grBb_804D69C8 + 0x28) * scale;
                spd = *(f32*) (gp + offset + 0xFC);
                pos = *(f32*) (gp + offset + 0xE0);
                predicted = spd * norm + pos;
                total = -total;
                total = 0.5F * total;
                total = norm * total;
                predicted -= norm * total;

                if (predicted < target) {
                    scale = Ground_801C0498();
                    *(f32*) (gp + offset + 0x100) =
                        *(f32*) ((u8*) grBb_804D69C8 + 0x28) * scale;
                } else {
                    scale = Ground_801C0498();
                    *(f32*) (gp + offset + 0x100) =
                        -(*(f32*) ((u8*) grBb_804D69C8 + 0x28) * scale);
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

        *(f32*) (gp + offset + 0x100) =
            *(f32*) ((u8*) grBb_804D69C8 + 0x28) * scale;
        break;
    }

    case 8: {
        f32 scale = Ground_801C0498();

        *(f32*) (gp + offset + 0x100) =
            -(*(f32*) ((u8*) grBb_804D69C8 + 0x28) * scale);
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

// @TODO: Currently 89.49% match - register allocation differs
// @TODO: Currently 98.03% match - float register allocation off by 1
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
        car_i = (u8*) gp;
        changed = 0;
        i = 0;

        while (i < 4) {
            if ((u32) ((car_i[0xD4] >> 2) & 0x3F) == 1U) {
                goto next_i;
            }

            j = 0;
            car_j = (u8*) gp;

            while (j < 4) {
                if (i == j) {
                    goto next_j;
                }

                if ((u32) ((car_j[0xD4] >> 2) & 0x3F) == 1U) {
                    goto next_j;
                }

                diff = *(f32*) (car_i + 0xE0) - *(f32*) (car_j + 0xE0);

                if (diff < zero) {
                    absDiff = -diff;
                } else {
                    absDiff = diff;
                }

                if (absDiff < Ground_801C0498() * (f32) *
                                  (s32*) ((u8*) grBb_804D69C8 + 0x20))
                {
                    f32 adjustment;
                    if (diff > zero) {
                        adjustment = Ground_801C0498() * (f32) *
                                     (s32*) ((u8*) grBb_804D69C8 + 0x20);
                    } else {
                        adjustment = -(Ground_801C0498() * (f32) *
                                       (s32*) ((u8*) grBb_804D69C8 + 0x20));
                    }

                    diff -= adjustment;
                    changed = 1;
                    diff = (f32) (diff * 0.5);

                    *(f32*) (car_i + 0xDC) -= diff;
                    *(f32*) (car_i + 0xE0) -= diff;
                    *(f32*) (car_j + 0xDC) += diff;
                    *(f32*) (car_j + 0xE0) += diff;
                }

            next_j:
                j++;
                car_j += 0x40;
            }

        next_i:
            i++;
            car_i += 0x40;
        }

        k++;
    }
}

// @TODO: Currently 99.98% match - assert string relocation offset
void fn_801EF60C(Ground* gp, s32 joint_id, CollData* coll, s32 arg3, s32 env,
                 f32 arg5)
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

    table = (s16*) ((u8*) tmpPadData + 0x4C4);
    idx = 0;
    while (idx < 30) {
        if (joint_id == *table) {
            break;
        }
        table++;
        idx++;
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

// @TODO: Currently 96.3% match - needs separate float literals for x vs y/z
void grBigBlue_801EF7D8(Vec3* pos)
{
    HSD_GObj* gobj = Ground_801C2BA4(0x22);

    if (gobj != NULL && gobj->user_data != NULL) {
        pos->x = 0.0F;
        pos->y = 0.0F;
        pos->z = 0.0F;
    } else {
        pos->z = 0.0F;
        pos->y = 0.0F;
        pos->x = 0.0F;
    }
}

BOOL grBigBlue_801EF844(enum_t line_id)
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
            return TRUE;
        }
    }
    return FALSE;
}

void fn_801EFB9C(HSD_GObj* gobj, int arg1)
{
    if (gm_801A45E8(1) == 0 && gm_801A45E8(2) == 0) {
        if (Camera_8003010C() != 0) {
            return;
        }
        grDisplay_801C5DB0(gobj, arg1);
    }
}

DynamicsDesc* grBigBlue_801EFC0C(enum_t arg)
{
    return false;
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
