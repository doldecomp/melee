#include "grcorneria.h"

#include "grcorneria.static.h"

#include "baselib/sislib.h"
#include "cm/camera.h"
#include "gm/gm_1A45.h"
#include "gm/gmregclear.h"
#include "gr/granime.h"
#include "gr/grdisplay.h"
#include "gr/grlib.h"
#include "gr/grmaterial.h"
#include "gr/ground.h"
#include "gr/grvenom.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "gr/stage.h"
#include "gr/types.h"
#include "if/ifcoget.h"
#include "if/ifstatus.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "mp/mplib.h"

#include <baselib/controller.h>
#include <baselib/debug.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>
#include <baselib/random.h>

int grCn_803E1D80[3] = { 0, 0, 0 };
int grCn_803E2190[5] = { 0, 0, 1, 2, 5 };

int grCn_804D466C = -1;

static void* grCn_804D69A0;
static u32 grCn_804D69A4;
static s32 grCn_804D69A8;
static int grCn_804D69AC;
static s32 grCn_804D69B0;

typedef struct {
    int data[3];
} grCn_Entry;

extern grCn_Entry grCn_803E2204[][5];

typedef struct grCn_Data {
    /* 0x000 */ u8 pad_00[0x30];
    /* 0x030 */ s32 x30[3];
    /* 0x03C */ s32 indices[3];
    /* 0x048 */ s32 x48[3];
    /* 0x054 */ u8 pad_54[0x2DC];
    /* 0x330 */ Vec3 positions[34];
    /* +4C8 */ UNK_T pad2;
    /* 0x4CC */ grCn_Entry entries[][5];
} grCn_Data;

extern grCn_Data grCn_803E1D38;

s32 grCorneria_801DCCFC(void)
{
    f32 temp_f0;
    f32 temp_f2;
    s32 temp_r30;
    s32 var_r31;
    s32 var_r3;
    s32 diff;

    grCn_803E1D38.x30[0] = 0;
    grCn_803E1D38.indices[0] = 0;
    grCn_803E1D38.x48[0] = 0;
    grCn_803E1D38.x30[1] = 0;
    grCn_803E1D38.indices[1] = 0;
    grCn_803E1D38.x48[1] = 0;
    grCn_803E1D38.x30[2] = 0;
    grCn_803E1D38.indices[2] = 0;
    grCn_803E1D38.x48[2] = 0;
    var_r3 = Stage_80225194();
    switch (var_r3) {
    case 0xE9:
    case 0x47:
        grCn_804D69B0 = 1;
        break;
    default:
        grCn_804D69B0 = 0;
        break;
    }
    if (grCn_804D69B0 == 1) {
        grCn_804D69A8 = 0x78;
        return var_r3;
    }
    temp_f0 = M2C_FIELD(grCn_804D69A0, f32*, 0x3C);
    temp_f2 = M2C_FIELD(grCn_804D69A0, f32*, 0x40);
    temp_r30 = (s32) temp_f0;
    var_r3 = (s32) temp_f2;
    var_r31 = (s32) temp_f2;
    if (var_r3 > temp_r30) {
        diff = var_r31 - temp_r30;
        if (diff != 0) {
            var_r3 = HSD_Randi(diff);
        } else {
            var_r3 = 0;
        }
        var_r31 = temp_r30 + var_r3;
    } else if (var_r31 < temp_r30) {
        diff = temp_r30 - var_r31;
        if (diff != 0) {
            var_r3 = HSD_Randi(diff);
        } else {
            var_r3 = 0;
        }
        var_r31 += var_r3;
    }
    grCn_804D69A8 = var_r31;
    return var_r3;
}

/// #grCorneria_801DCE1C

void grCorneria_801DD2C0(void)
{
    void* obj;
    int rand;
    PAD_STACK(32);

    obj = Ground_801C2BA4(3);
    if (obj != NULL) {
        obj = GET_JOBJ(obj);
        if (obj != NULL) {
            HSD_JObjSetFlagsAll(obj, JOBJ_HIDDEN);
        }
    }
    grCorneria_801E0678();
    obj = grCorneria_801DD534(12);
    if (gm_8017E7E0() != 0) {
        rand = HSD_Randi(4) + 4;
    } else {
        rand = HSD_Randi(4);
    }
    grCorneria_801E0F34(obj, rand);
    grCn_804D69AC = 1;
}

extern Vec3 grCn_803B8090;

void grCorneria_801DD350(void)
{
    Vec3 sp14;

    grCn_804D69A0 = Ground_801C49F8();
    stage_info.unk8C.b4 = 0;
    stage_info.unk8C.b5 = 1;
    grCorneria_801DD534(7);
    grCorneria_801DD534(3);
    grCorneria_801DCCFC();
    GET_GROUND(grCorneria_801DD534(8))->gv.corneria.xC4.value = 1;
    GET_GROUND(grCorneria_801DD534(9))->gv.corneria.xC4.value = 1;
    GET_GROUND(grCorneria_801DD534(4))->gv.corneria.xC4.value = 1;
    grCorneria_801DD534(0xB);
    Ground_801C39C0();
    Ground_801C3BB4();
    sp14 = grCn_803B8090;
    lb_80011A50(&sp14, -1, 1.0f, 0.0f, 1.0471976f, -100000.0f, 100000.0f,
                100000.0f, -100000.0f);
    grCn_804D69AC = 1;
    mpLib_80057BC0(0);
    mpLib_80057BC0(1);
    mpLib_80057BC0(2);
    mpLib_80057BC0(5);
    mpLib_80057BC0(6);
    mpLib_80057BC0(7);
}

void grCorneria_801DD478(void)
{
    HSD_GObj* gobj;
    Ground* gp;

    gobj = Ground_801C2BA4(11);
    if (gobj != NULL) {
        Ground_801C4A08(gobj);
    }
    gobj = Ground_801C2BA4(8);
    if (gobj != NULL) {
        Ground_801C4A08(gobj);
    }
    gobj = Ground_801C2BA4(9);
    if (gobj != NULL) {
        Ground_801C4A08(gobj);
    }
    gobj = Ground_801C2BA4(4);
    if (gobj != NULL) {
        Ground_801C4A08(gobj);
    }
    gobj = grCorneria_801DD534(8);
    gp = GET_GROUND(gobj);
    gp->gv.corneria.xC5 = 0;
    grCn_804D69AC = 0;
    Ground_801C53EC(0x55737);
}

void grCorneria_801DD508(void)
{
    grZakoGenerator_801CAE04(NULL);
}

bool grCorneria_801DD52C(void)
{
    return false;
}

StageCallbacks grCn_803E1D8C[19] = {
    { grCorneria_801DD620, grCorneria_801DD64C, grCorneria_801DD654,
      grCorneria_801DD658, 0 },
    { grCorneria_801DDAC4, grCorneria_801DDCE8, grCorneria_801DE024,
      grCorneria_801DE4BC, 0 },
    { grCorneria_801DE8E4, grCorneria_801DEC00, grCorneria_801DED50,
      grCorneria_801DF8CC, 0 },
    { grCorneria_801DD674, grCorneria_801DD9A0, grCorneria_801DD9A8,
      grCorneria_801DDAC0, 0x80000000 },
    { grCorneria_801E0140, grCorneria_801E01A0, grCorneria_801E01A8,
      grCorneria_801E03C4, 0 },
    { grCorneria_801E0DE4, grCorneria_801E0E0C, grCorneria_801E0E14,
      grCorneria_801E0E3C, 0x20000000 },
    { grCorneria_801DFBF0, grCorneria_801DFC1C, grCorneria_801DFC24,
      grCorneria_801DFC28, 0 },
    { grCorneria_801E0C3C, grCorneria_801E0D28, grCorneria_801E0D30,
      grCorneria_801E0DE0, 0x40000000 },
    { grCorneria_801DFC2C, grCorneria_801DFC90, grCorneria_801DFC98,
      grCorneria_801DFEB4, 0 },
    { grCorneria_801DFEB8, grCorneria_801DFF18, grCorneria_801DFF20,
      grCorneria_801E013C, 0 },
    { grCorneria_801DF8D0, grCorneria_801DFBC4, grCorneria_801DFBCC,
      grCorneria_801DFBEC, 0 },
    { grCorneria_801E1054, grCorneria_801E1058, grCorneria_801E1060,
      grCorneria_801E12CC, 0 },
    { grCorneria_801E0F30, grCorneria_801E0F64, grCorneria_801E0F6C,
      grCorneria_801E1030, 0 },
    { grCorneria_Arwing_801DE4C0, grCorneria_801DE560, grCorneria_801DE568,
      grCorneria_801DE8E0, 0 },
    { grCorneria_Arwing_801DE4C0, grCorneria_801DE560, grCorneria_801DE568,
      grCorneria_801DE8E0, 0 },
    { grCorneria_Arwing_801DE4C0, grCorneria_801DE560, grCorneria_801DE568,
      grCorneria_801DE8E0, 0 },
    { grCorneria_Arwing_801DE4C0, grCorneria_801DE560, grCorneria_801DE568,
      grCorneria_801DE8E0, 0 },
    { grCorneria_Arwing_801DE4C0, grCorneria_801DE560, grCorneria_801DE568,
      grCorneria_801DE8E0, 0 },
    { grCorneria_Arwing_801DE4C0, grCorneria_801DE560, grCorneria_801DE568,
      grCorneria_801DE8E0, 0 },
};

#pragma push
#pragma dont_inline on
HSD_GObj* grCorneria_801DD534(int arg0)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grCn_803E1D8C[arg0];

    gobj = Ground_GetStageGObj(arg0);

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
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grcorneria.c", 0x26A,
                 arg0);
    }

    return gobj;
}
#pragma pop

void grCorneria_801DD620(Ground_GObj* gobj)
{
    grAnime_801C8138((HSD_GObj*) gobj, GET_GROUND(gobj)->map_id, 0);
}

bool grCorneria_801DD64C(Ground_GObj* arg)
{
    return false;
}

void grCorneria_801DD654(Ground_GObj* arg) {}

void grCorneria_801DD658(Ground_GObj* arg) {}

void grCorneria_801DD65C(Ground_GObj* gobj)
{
    GET_GROUND(gobj)->gv.corneria.xC4.flags.b0 = false;
}

extern grZakoGenerator_Spawn grCn_803E1FE8[];
extern grZakoGenerator_Spawn grCn_803E2000[];

void grCorneria_801DD674(Ground_GObj* ground_gobj)
{
    Vec3 translate;
    HSD_JObj* jobj;
    u32 unused;

    Ground* gr = GET_GROUND(ground_gobj);
    Ground_801C2ED0(ground_gobj->hsd_obj, gr->map_id);
    gr->gv.corneria.xC4.flags.b0 = 1;
    gr->gv.corneria.xC4.flags.b1 = 0;
    gr->gv.corneria.base_x = 0.0f;
    gr->gv.corneria.base_y = 250.0f;
    gr->gv.corneria.xD0 = 0.0f;
    gr->gv.corneria.offset_x = 0.0f;
    gr->gv.corneria.offset_y.val = 0.0f;
    gr->gv.corneria.xE4 = 0.0f;
    gr->gv.corneria.xE8 = 0.0f;
    gr->gv.corneria.xEC = 0.0f;
    gr->gv.corneria.xF0 = 0.0f;
    gr->gv.corneria.xF4 = 0.0f;
    gr->gv.corneria.xF8 = 0.0f;
    gr->gv.corneria.x104 = 0;
    gr->x10_flags.b5 = 1;
    grAnime_801C8138(ground_gobj, gr->map_id, 0);
    grAnime_801C8780(ground_gobj, 3, 0, 0.0f, 1.0f);
    gr->gv.corneria.x128 = grCorneria_801DD534(0);
    jobj = ground_gobj->hsd_obj;
    translate.x = gr->gv.corneria.base_x + gr->gv.corneria.offset_x;
    translate.y = gr->gv.corneria.base_y + gr->gv.corneria.offset_y.val;
    translate.z = 0.0f;
    HSD_JObjSetTranslate(jobj, &translate);
    grCorneria_801E1878(ground_gobj);
    Ground_801C39C0();
    Ground_801C3BB4();
    gr->gv.corneria.x108 = 0;
    gr->gv.corneria.x10C = 0;
    gr->gv.corneria.x118 = 0;
    gr->gv.corneria.x11A = 0;
    gr->gv.corneria.x110 = 0;
    gr->gv.corneria.x114 = 0.0f;
    gr->gv.corneria.left_cannon =
        grMaterial_801C8CFC(0, 0, gr, Ground_801C3FA4(ground_gobj, 2),
                            fn_801E12D0, fn_801E12D4, 0);
    grMaterial_801C8DE0(gr->gv.corneria.left_cannon, 4.0f, 0.0f, 0.0f, 16.0f,
                        0.0f, 0.0f, 4.0f);
    grMaterial_801C8E08(gr->gv.corneria.left_cannon);
    gr->gv.corneria.right_cannon =
        grMaterial_801C8CFC(0, 2, gr, Ground_801C3FA4(ground_gobj, 3),
                            fn_801E12D0, fn_801E12D4, 0);
    grMaterial_801C8E08(gr->gv.corneria.right_cannon);
    grMaterial_801C8DE0(gr->gv.corneria.right_cannon, 4.0f, 0.0f, 0.0f, 16.0f,
                        0.0f, 0.0f, 4.0f);
    HSD_JObjClearFlags(Ground_801C3FA4(ground_gobj, 6), JOBJ_HIDDEN);
    HSD_JObjSetFlags(Ground_801C3FA4(ground_gobj, 5), JOBJ_HIDDEN);
    gr->gv.corneria.xC8 =
        grZakoGenerator_801CA394(grCn_803E1FE8, 1, grCorneria_801E2454, 0.3f);
    gr->gv.corneria.xCC =
        grZakoGenerator_801CA394(grCn_803E2000, 2, grCorneria_801E2480, 0.3f);
    Ground_801C10B8(ground_gobj, grCorneria_801DD65C);
    gr->x11_flags.b012 = 1;
    gr->gv.corneria.x12C = Ground_801C3FA4(ground_gobj, 8);
}

bool grCorneria_801DD9A0(Ground_GObj* arg)
{
    return false;
}

extern Vec3 grCn_803E1F70[5];
extern Vec3 grCn_803E1FAC[5];

void grCorneria_801DD9A8(Ground_GObj* gobj)
{
    Ground* gp = HSD_GObjGetUserData(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    int i;

    if (!gp->gv.corneria.xC4.flags.b0) {
        f32 speed;

        grCorneria_801E1970(gobj);
        grCorneria_801E2228(gobj);

        speed = -35.0f * Ground_801C0498() - gp->gv.corneria.xD0;
        grZakoGenerator_801CA43C(gp->gv.corneria.xC8, Ground_801C3FA4(gobj, 0),
                                 speed);

        speed = -35.0f * Ground_801C0498() - gp->gv.corneria.xD0;
        grZakoGenerator_801CA43C(gp->gv.corneria.xCC, Ground_801C3FA4(gobj, 0),
                                 speed);

        grCorneria_801E1348(gobj);
        grCorneria_801E0E40();
        grCorneria_801DCE1C();
    }

    for (i = 0; i < 5; i++) {
        lb_8000B1CC(jobj, &grCn_803E1F70[i], &grCn_803E1FAC[i]);
    }

    Ground_801C2FE0(gobj);
    grCorneria_801E1878(gobj);
    grCorneria_801E2110();
    lb_800115F4();
}

void grCorneria_801DDAC0(Ground_GObj* arg) {}

/// #grCorneria_801DDAC4

bool grCorneria_801DDCE8(Ground_GObj* arg)
{
    return false;
}

void grCorneria_801DDCF0(Vec3* vec)
{
    Ground* gp;
    HSD_GObj* gobj;
    PAD_STACK(4);

    gobj = Ground_801C2BA4(3);
    gp = GET_GROUND(gobj);
    vec->x = gp->gv.corneria.offset_x - gp->gv.corneria.xE4;
    vec->y = gp->gv.corneria.offset_y.val - gp->gv.corneria.xE8;
    vec->z = 0.0f;
}

void grCorneria_801DDD4C(Vec3* vec)
{
    Ground* gp;
    HSD_GObj* gobj;
    PAD_STACK(4);

    gobj = Ground_801C2BA4(3);
    gp = GET_GROUND(gobj);
    vec->x = gp->gv.corneria.base_x + gp->gv.corneria.offset_x;
    vec->y = gp->gv.corneria.base_y + gp->gv.corneria.offset_y.val;
    vec->z = 0.0f;
}

void grCorneria_801DDDA8(HSD_GObj* gobj, Vec3* vec)
{
    grCn_Data* data = &grCn_803E1D38;
    Ground* gp2;
    Ground* gp;
    HSD_JObj* jobj;
    u8 unused[12];
    Vec3 pos;
    int idx;
    PAD_STACK(4);

    if (gobj != NULL) {
        gp = gobj->user_data;
        gp2 = Ground_801C2BA4(3)->user_data;
        jobj = Ground_801C3FA4(gobj, 4);
        lb_8000B1CC(jobj, NULL, &pos);
        idx = data->indices[gp->gv.arwing.xC8];
        vec->x = gp2->gv.arwing.xDC + (-pos.z + data->positions[idx].x);
        vec->y = pos.y + data->positions[idx].y;
        vec->z = pos.x + data->positions[idx].z;
    } else {
        vec->z = 0.0f;
        vec->y = 0.0f;
        vec->x = 0.0f;
    }

    if (vec->y <= 100.0f) {
        vec->y = 100.0f;
    }
}

/// #grCorneria_801DDE88

/// #grCorneria_801DE024

void grCorneria_801DE4BC(Ground_GObj* arg) {}

void grCorneria_Arwing_801DE4C0(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    HSD_JObj* jobj = gobj->hsd_obj;
    int* joint_idx;
    int joint_offset;
    int* joints;
    int joint_id;

    Ground_801C2ED0(jobj, gp->map_id);
    gp->gv.arwing.xC8 = grCn_804D69A4;
    joint_idx = grCn_803E1D80;
    joints = grCn_803E2190;
    gp->gv.arwing.xD0 = 0;
    gp->gv.arwing.xDC = 0.0f;
    gp->gv.arwing.xE8 = 0.0f;
    gp->gv.arwing.xE4 = 0.0f;
    gp->gv.arwing.xE0 = 0.0f;
    joint_offset = joint_idx[gp->gv.arwing.xC8];
    joint_id = joints[joint_offset];
    mpJointListAdd(joint_id);

    Ground_801C2ED0(jobj, gp->map_id);
}

bool grCorneria_801DE560(Ground_GObj* arg)
{
    return false;
}

/// #grCorneria_801DE568

void grCorneria_801DE8E0(Ground_GObj* arg) {}

/// #grCorneria_801DE8E4

bool grCorneria_801DEC00(Ground_GObj* arg)
{
    return false;
}

s32 grCorneria_801DEC08(Vec3* pos)
{
    if (pos->x > Stage_GetBlastZoneRightOffset()) {
        return 1;
    }
    if (pos->x < Stage_GetBlastZoneLeftOffset()) {
        return 1;
    }
    if (pos->y > Stage_GetBlastZoneTopOffset()) {
        return 1;
    }
    if (pos->y < Stage_GetBlastZoneBottomOffset()) {
        return 1;
    }
    return 0;
}
s32 grCorneria_801DEC94(Vec3* pos)
{
    if (pos->z > -30.0f) {
        if (pos->x > Stage_GetBlastZoneRightOffset() - 30.0f) {
            return 1;
        }
        if (pos->x < Stage_GetBlastZoneLeftOffset() + 30.0f) {
            return 1;
        }
        if (pos->y > Stage_GetBlastZoneTopOffset() - 30.0f) {
            return 1;
        }
        if (pos->y < Stage_GetBlastZoneBottomOffset() + 30.0f) {
            return 1;
        }
    }
    return 0;
}

/// #grCorneria_801DED50

void grCorneria_801DF8CC(Ground_GObj* arg) {}

/// #grCorneria_801DF8D0

bool grCorneria_801DFBC4(Ground_GObj* arg)
{
    return false;
}

void grCorneria_801DFBCC(Ground_GObj* arg)
{
    grCorneria_801DED50(arg);
}

void grCorneria_801DFBEC(Ground_GObj* arg) {}

void grCorneria_801DFBF0(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138((HSD_GObj*) gobj, gp->map_id, 0);
}

bool grCorneria_801DFC1C(Ground_GObj* arg)
{
    return false;
}

void grCorneria_801DFC24(Ground_GObj* arg) {}

void grCorneria_801DFC28(Ground_GObj* arg) {}

void grCorneria_801DFC2C(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);

    gp->gv.corneria.xC6.value = 0;
    gp->gv.corneria.offset_y.flags.b0 = 0;
    memzero(&gp->gv.corneria.xC8, 0x18);
    gp->gv.corneria.xC4.value = 0;
    gp->x11_flags.b012 = 1;
}
bool grCorneria_801DFC90(Ground_GObj* arg)
{
    return false;
}

/// #grCorneria_801DFC98

void grCorneria_801DFEB4(Ground_GObj* arg) {}

void grCorneria_801DFEB8(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;

    gp->gv.corneria.xC6.flags.b0 = 0;
    grAnime_801C8138((HSD_GObj*) gobj, gp->map_id, 0);
    gp->gv.corneria.xC4.value = 0;
    gp->x11_flags.b012 = 1;
}

bool grCorneria_801DFF18(Ground_GObj* arg)
{
    return false;
}

/// #grCorneria_801DFF20

void grCorneria_801E013C(Ground_GObj* arg) {}

void grCorneria_801E0140(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;

    gp->gv.corneria.xC6.flags.b0 = 0;
    grAnime_801C8138((HSD_GObj*) gobj, gp->map_id, 0);
    gp->gv.corneria.xC4.value = 0;
    gp->x11_flags.b012 = 1;
}

bool grCorneria_801E01A0(Ground_GObj* arg)
{
    return false;
}

/// #grCorneria_801E01A8

void grCorneria_801E03C4(Ground_GObj* arg) {}

/// #grCorneria_801E03C8

/// #grCorneria_801E0678

/// #grCorneria_801E08CC

int grCorneria_801E0A74(f32* arg0)
{
    HSD_GObj* gobj;

    gobj = Ground_801C2BA4(8);
    if (gobj != NULL) {
        f32 x = HSD_JObjGetTranslationX(gobj->hsd_obj);
        if (*arg0 > x - 3200.0f * Ground_801C0498() / 2 &&
            *arg0 < x + 3200.0f * Ground_801C0498() / 2)
        {
            return 8;
        }
    }
    gobj = Ground_801C2BA4(9);
    if (gobj != NULL) {
        f32 x = HSD_JObjGetTranslationX(gobj->hsd_obj);
        if (*arg0 > x - 3200.0f * Ground_801C0498() / 2 &&
            *arg0 < x + 3200.0f * Ground_801C0498() / 2)
        {
            return 9;
        }
    }
    gobj = Ground_801C2BA4(4);
    if (gobj != NULL) {
        f32 x = HSD_JObjGetTranslationX(gobj->hsd_obj);
        if (*arg0 > x - 4800.0f * Ground_801C0498() / 2 &&
            *arg0 < x + 4800.0f * Ground_801C0498() / 2)
        {
            return 4;
        }
    }
    OSReport("grcorneria.c    grCorneriaGetPosMapKind2\n");
    __assert("grcorneria.c", 2507, "0");
    return -1;
}

static inline void clearX10_b2(HSD_GObj* gobj)
{
    GET_GROUND(gobj)->x10_flags.b2 = false;
}

void grCorneria_801E0C3C(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
    clearX10_b2(gobj);
    Ground_801C4E70(Ground_801C3FA4(gobj, 5), Ground_801C3FA4(gobj, 2),
                    Ground_801C3FA4(gobj, 4), Ground_801C3FA4(gobj, 3),
                    Ground_801C3FA4(gobj, 7), Ground_801C3FA4(gobj, 6));
    grMaterial_801C8A04(jobj, JOBJ_UNK_B27);
    grMaterial_801C8858(jobj, JOBJ_ROOT_XLU);
    gp->x11_flags.b012 = 2;
}

bool grCorneria_801E0D28(Ground_GObj* arg)
{
    return false;
}

void grCorneria_801E0D30(Ground_GObj* gobj)
{
    HSD_JObj* jobj;

    if ((jobj = gobj->hsd_obj) != NULL) {
        HSD_JObjSetTranslateY(jobj, -grCorneria_801E2EA0());
    }
}

void grCorneria_801E0DE0(Ground_GObj* arg) {}

void grCorneria_801E0DE4(Ground_GObj* gobj)
{
    Ground* gr = GET_GROUND(gobj);
    smashTaunt_801E2550(gobj, &gr->gv.smashtaunt);
}

bool grCorneria_801E0E0C(Ground_GObj* arg)
{
    return false;
}

void grCorneria_801E0E14(Ground_GObj* gobj)
{
    Ground* gr = GET_GROUND(gobj);
    grCorneria_801E277C(gobj, &gr->gv.corneria);
}

void grCorneria_801E0E3C(Ground_GObj* arg) {}

void grCorneria_801E0E40(void)
{
    u32 trigger;
    HSD_GObj* wgobj;
    PAD_STACK(8);

    if (!Camera_80030178()) {
        if (!Camera_80030154()) {
            return;
        }
    }

    trigger = HSD_PadMasterStatus[1].trigger;
    if ((trigger & (PAD_TRIGGER_L | PAD_TRIGGER_R)) == 0) {
        return;
    }

    if (Ground_801C2BA4(0xC) != NULL) {
        return;
    }

    if (trigger & PAD_TRIGGER_L) {
        grCn_804D466C -= 1;
    } else {
        grCn_804D466C += 1;
    }

    if (grCn_804D466C < 0) {
        grCn_804D466C = 0;
    }
    if (grCn_804D466C >= 0x14u) {
        grCn_804D466C = 0x13;
    }

    OSReport("talk no = %d\n", grCn_804D466C);
    wgobj = grCorneria_801DD534(0xC);
    if (wgobj == NULL) {
        __assert("grcorneria.c", 0xAC3, "wgobj");
    }
    grCorneria_801E0F34(wgobj, grCn_804D466C);
}

void grCorneria_801E0F30(Ground_GObj* arg) {}

void grCorneria_801E0F34(Ground_GObj* gobj, int val)
{
    Ground* gp = GET_GROUND(gobj);
    gp->gv.arwing.xCC = 0;
    gp->gv.arwing.xC8 = 0;
    if (val < 0) {
        val = 0;
    }
    if (val >= 0x14u) {
        val = 0x13;
    }
    gp->gv.arwing.xC4 = val;
}

bool grCorneria_801E0F64(Ground_GObj* arg)
{
    return false;
}

void grCorneria_801E0F6C(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);

    ifStatus_802F6898();
    un_802FF570();

    if (Ground_801C2BA4(5) == NULL) {
        if (grCorneria_801E2598(gp->gv.arwing.xC4, gp->gv.arwing.xC8)) {
            if ((s32) gp->gv.arwing.xCC-- < 0) {
                HSD_GObj* gobj5 = grCorneria_801DD534(5);
                Ground* gp5 = GET_GROUND(gobj5);
                grCorneria_801E2738(gobj5, &gp5->gv, gp->gv.arwing.xC4,
                                    gp->gv.arwing.xC8);
                gp->gv.arwing.xC8++;
                gp->gv.arwing.xCC = 0;
            }
        } else {
            if ((s32) gp->gv.arwing.xCC-- < 0) {
                Ground_801C4A08(gobj);
            }
        }
    }
}

void grCorneria_801E1030(Ground_GObj* gobj)
{
    ifStatus_802F68F0();
    un_802FF620();
}

void grCorneria_801E1054(Ground_GObj* arg) {}

bool grCorneria_801E1058(Ground_GObj* arg)
{
    return false;
}

/// #grCorneria_801E1060

void grCorneria_801E12CC(Ground_GObj* arg) {}

void fn_801E12D0(Item_GObj* gobj, Ground* gr) {}

void fn_801E12D4(Item_GObj* gobj, Ground* gr, Vec3* pos, HSD_GObj* arg3,
                 f32 damage)
{
    gr->gv.corneria.x114 += damage;
    OSReport("*** Beam Damage! %f\n", damage);
    if (gr->gv.corneria.x114 >= M2C_FIELD(grCn_804D69A0, f32*, 0x38)) {
        gr->gv.corneria.x108 = 4;
        grMaterial_801C8E28((HSD_GObj*) gr->gv.corneria.left_cannon);
        grMaterial_801C8E28((HSD_GObj*) gr->gv.corneria.right_cannon);
    }
}

/// #grCorneria_801E1348

void grCorneria_801E1878(Ground_GObj* gobj)
{
    Vec3 pos;
    Ground* gr = GET_GROUND(gobj);
    HSD_JObj* jobj = gobj->hsd_obj;
    HSD_JObj* target_jobj = gr->gv.corneria.x128->hsd_obj;

    HSD_JObjGetTranslation(jobj, &pos);
    HSD_JObjSetTranslate(target_jobj, &pos);

    Ground_801C39C0();
    Ground_801C3BB4();

    PAD_STACK(12);
}

/// #grCorneria_801E1970

/// #grCorneria_801E1BF0

static s32 grCn_804DB218 = (s32) 0xAEBAD6FF;
static s32 grCn_804DB21C = (s32) 0xD7E4F6FF;
static s32 grCn_804DB220 = (s32) 0xE0ECFAFF;
static s32 grCn_804DB224 = (s32) 0x6A9EADFF;
static s32 grCn_804DB228 = (s32) 0x4F94B5FF;
static s32 grCn_804DB22C = (s32) 0x496E3FFF;
static s32 grCn_804DB230 = (s32) 0x6A9EADFF;
static s32 grCn_804DB234 = (s32) 0x4F94B5FF;
static s32 grCn_804DB238 = (s32) 0x5091FF;

void grCorneria_801E2110(void)
{
    s32 sp28;
    s32 sp24;
    s32 sp20;
    s32 sp1C;
    s32 sp18;
    s32 sp14;
    s32 sp10;
    s32 spC;
    s32 sp8;
    s32 result;

    result = grCorneria_801E08CC();
    if (result == 8) {
        sp28 = grCn_804DB218;
        sp24 = grCn_804DB21C;
        sp20 = grCn_804DB220;
        Ground_801C058C((GXColor*) &sp24);
        Ground_801C05EC((GXColor*) &sp28);
        Ground_801C05A4((GXColor*) &sp24);
        Ground_801C055C((GXColor*) &sp20);
        Ground_801C05BC((GXColor*) &sp20);
        Ground_801C0574((GXColor*) &sp20);
    } else if (result == 9) {
        sp1C = grCn_804DB224;
        sp18 = grCn_804DB228;
        sp14 = grCn_804DB22C;
        Ground_801C058C((GXColor*) &sp18);
        Ground_801C05EC((GXColor*) &sp1C);
        Ground_801C05A4((GXColor*) &sp18);
        Ground_801C055C((GXColor*) &sp14);
        Ground_801C05BC((GXColor*) &sp14);
        Ground_801C0574((GXColor*) &sp14);
    } else if (result == 4) {
        sp10 = grCn_804DB230;
        spC = grCn_804DB234;
        sp8 = grCn_804DB238;
        Ground_801C058C((GXColor*) &spC);
        Ground_801C05EC((GXColor*) &sp10);
        Ground_801C05A4((GXColor*) &spC);
        Ground_801C055C((GXColor*) &sp8);
        Ground_801C05BC((GXColor*) &sp8);
        Ground_801C0574((GXColor*) &sp8);
    }
}

/// #grCorneria_801E2228

HSD_Generator* grCorneria_801E2454(Vec3* vec, s32 arg1)
{
    return grLib_801C96F8(0x7534, 0x1E, vec);
}

HSD_Generator* grCorneria_801E2480(Vec3* vec, s32 arg1)
{
    return grLib_801C96F8(0x7530, 0x1E, vec);
}

/// This triggers for both Corneria and Venom
void smashTaunt_801E24AC(Ground_GObj* gobj, int renderpass)
{
    Ground* gp = GET_GROUND(gobj);
    void* obj;
    PAD_STACK(8);

    if (gm_801A45E8(1) != false || gm_801A45E8(2) != false ||
        Camera_8003010C() != false)
    {
        obj = gp->gv.smashtaunt.xE4;
        if (obj == NULL) {
            return;
        }
        M2C_FIELD(gp->gv.smashtaunt.xE4, u8*, 0x4D) = 1;
        return;
    }
    obj = gp->gv.smashtaunt.xE4;
    if (obj != NULL) {
        M2C_FIELD(gp->gv.smashtaunt.xE4, u8*, 0x4D) = 0;
    }
    grDisplay_801C5DB0(gobj, renderpass);
}

void smashTaunt_801E2550(Ground_GObj* gobj, struct grSmashTaunt_GroundVars* gv)
{
    PAD_STACK(8);

    gv->xE4 = NULL;
    Ground_801C11AC(gobj);
    ifStatus_802F6898();
    un_802FF570();
    gobj->render_cb = smashTaunt_801E24AC;
}

s32 grCorneria_801E2598(u32 arg0, u32 arg1)
{
    int val;

    val = grCn_803E2204[arg0][arg1].data[0];
    return val != 0;
}

/// #grCorneria_801E25C4

void grCorneria_801E2738(HSD_GObj* gobj, void* ptr, u32 idx1, u32 idx2)
{
    grCorneria_801E25C4(gobj, ptr, grCn_803E1D38.entries[idx1][idx2].data[0],
                        grCn_803E1D38.entries[idx1][idx2].data[1],
                        grCn_803E1D38.entries[idx1][idx2].data[2]);
}

/// #grCorneria_801E277C

void grCorneria_801E2A6C(void)
{
    HSD_GObj* gobj;
    PAD_STACK(20);

    if (stage_info.internal_stage_id == CORNERIA) {
        gobj = Ground_801C2BA4(12);
        if (gobj == NULL) {
            return;
        }
        gobj = Ground_801C2BA4(5);
        if (gobj != NULL) {
            Ground_801C5544(GET_GROUND(gobj), 0);
            Ground_801C4A08(gobj);
        }
        HSD_SisLib_803A5F50(1);
    } else if (stage_info.internal_stage_id == VENOM) {
        grVenom_80206CB0(0);
    }
}

void grCorneria_801E2AF4(void)
{
    HSD_GObj* gobj;
    PAD_STACK(20);

    if (stage_info.internal_stage_id == CORNERIA) {
        gobj = Ground_801C2BA4(12);
        if (gobj == NULL) {
            return;
        }
        Ground_801C4A08(gobj);
        gobj = Ground_801C2BA4(5);
        if (gobj != NULL) {
            Ground_801C5544(GET_GROUND(gobj), 0);
            Ground_801C4A08(gobj);
        }
        HSD_SisLib_803A5F50(1);
    } else if (stage_info.internal_stage_id == VENOM) {
        grVenom_80206CB0(1);
    }
}

#pragma push
#pragma dont_inline on
bool grCorneria_801E2B80(void)
{
    int rand;
    HSD_GObj* gobj;
    PAD_STACK(44);

    if (stage_info.internal_stage_id == CORNERIA) {
        if (Ground_801C2BA4(12) != NULL) {
            return false;
        }
        rand = HSD_Randi(5) + 8;
        gobj = grCorneria_801DD534(12);
        HSD_ASSERT(3598, gobj);
        grCorneria_801E0F34(gobj, rand);
        return true;
    } else if (stage_info.internal_stage_id == VENOM) {
        return grVenom_80206BF0(2);
    }
    return true;
}

bool grCorneria_801E2C34(void)
{
    int rand;
    HSD_GObj* gobj;
    PAD_STACK(44);

    if (stage_info.internal_stage_id == CORNERIA) {
        if (Ground_801C2BA4(12) != NULL) {
            return false;
        }
        rand = HSD_Randi(5) + 13;
        gobj = grCorneria_801DD534(12);
        HSD_ASSERT(3598, gobj);
        grCorneria_801E0F34(gobj, rand);
        return true;
    } else if (stage_info.internal_stage_id == VENOM) {
        return grVenom_80206BF0(20);
    }
    return true;
}
#pragma pop

bool grCorneria_801E2CE8(void)
{
    if (stage_info.internal_stage_id == CORNERIA ||
        stage_info.internal_stage_id == VENOM)
    {
        return true;
    }
    return false;
}

bool grCorneria_801E2D14(void)
{
    HSD_GObj* gobj;
    if (stage_info.internal_stage_id == CORNERIA) {
        gobj = Ground_801C2BA4(12);
        if (gobj != NULL) {
            return true;
        }
        return false;
    } else if (stage_info.internal_stage_id == VENOM) {
        gobj = Ground_801C2BA4(8);
        if (gobj != NULL) {
            return true;
        }
        return false;
    }
    return false;
}

bool grCorneria_801E2D90(enum_t line_id)
{
    if (stage_info.internal_stage_id == CORNERIA && line_id != -1) {
        s32 joint = mpJointFromLine(line_id);
        s32 result;

        result = joint == 0 || joint == 1 || joint == 2 || joint == 5 ||
                 joint == 6 || joint == 7;

        if (result) {
            return true;
        }
    }
    return false;
}

bool grCorneria_801E2E50(int line_id)
{
    if (stage_info.internal_stage_id == CORNERIA && line_id != -1) {
        if (mpJointFromLine(line_id) == 4) {
            return true;
        }
    }
    return false;
}

f32 grCorneria_801E2EA0(void)
{
    HSD_GObj* gobj;
    Ground* gp;

    gobj = Ground_801C2BA4(3);
    if (gobj != NULL) {
        gp = GET_GROUND(gobj);
        if (gp != NULL) {
            return gp->gv.corneria.xD0;
        }
    }
    return 0.0f;
}

DynamicsDesc* grCorneria_801E2EE4(enum_t arg)
{
    return NULL;
}

bool grCorneria_801E2EEC(Vec3* v, int arg1, HSD_JObj* jobj)
{
    Vec3 sp14;
    HSD_GObj* temp_r3;
    Ground* temp_r3_2;
    float temp_f31;
    float temp_f31_2;

    lb_8000B1CC(jobj, NULL, &sp14);
    temp_r3 = Ground_801C2BA4(3);
    if (temp_r3 != NULL) {
        temp_r3_2 = temp_r3->user_data;
        if (temp_r3_2 != NULL && temp_r3_2->gv.corneria.x12C == jobj) {
            temp_f31 = 106.0f * Ground_801C0498();
            temp_f31_2 =
                ((v->y - sp14.y) * ((107.0f * Ground_801C0498()) / temp_f31)) +
                sp14.x;
            if (v->x > -((107.0f * Ground_801C0498()) - temp_f31_2)) {
                return false;
            }
        }
    }
    if (v->y > sp14.y) {
        return true;
    }
    return false;
}

f32 grCorneria_801E2FCC(void)
{
    HSD_GObj* gobj;
    Ground* gp;

    gobj = Ground_801C2BA4(3);
    if (gobj != NULL) {
        gp = gobj->user_data;
        if (gp != NULL) {
            return (Ground_801C0498() * -35.0f - gp->gv.corneria.xD0) + 5.0f;
        }
    }
    return -3.4028235e38f;
}
