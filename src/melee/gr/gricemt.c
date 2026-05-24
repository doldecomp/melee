#include "gr/gricemt.h"

#include <placeholder.h>
#include <platform.h>

#include "baselib/gobjproc.h"
#include "baselib/random.h"
#include "cm/camera.h"
#include "ef/efsync.h"
#include "ft/ftlib.h"
#include "gm/gm_1601.h"

#include "gr/forward.h"

#include "gr/grdatfiles.h"
#include "gr/grlib.h"
#include "gr/grmaterial.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "gr/stage.h"
#include "gr/types.h"
#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/types.h"
#include "lb/lb_00B0.h"
#include "mp/mplib.h"

#include <m2c_macros.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>

/* 1F8C64 */ static void fn_801F8C64(Item_GObj* gobj, Ground* u1, Vec3* u2,
                                     HSD_GObj* u3, f32 u4);
/* 1F91EC */ void grIceMt_801F91EC(HSD_GObj* param_1, s16* param_2,
                                   int param_3, int param_4, int param_5,
                                   int param_6, int param_7,
                                   mpLib_Callback param_8);

/// StageData grIm_803E8974 = {
///     45,
///     grTFc_803E8918,
///     "/GrTFc.dat",
///     grTFalco_802207F4,
///     grTFalco_802207F0,
///     grTfalco_UnkStage0_OnLoad,
///     grTfalco_UnkStage0_OnStart,
///     grTFalco_80220894,
///     grTFalco_80220ACC,
///     grTFalco_80220B78,
///     1,
/// };

/*struct {
    Vec3 unk0;
    Vec3 unkC;
    Vec3 unk18;
    Vec3 unk24;
    Vec3 unk40;
} grIm_803B8220;*/
static Vec3 grIm_803B8220[] = { { 0.0, 0.0, 0.0 },
                                { -8.0, 15.0, 0.0 },
                                { 8.0, 15.0, 0.0 },
                                { -24.0, 15.0, 0.0 },
                                { 24.0, 15.0, 0.0 } };

HSD_GObj* grIm_804D69E8;
HSD_GObj* grIm_804D69EC;
HSD_GObj* grIm_804D69F0;
IceMountainParams* grIm_804D69F4;

extern char grIm_803E46F8[];

typedef struct GrIm825C {
    struct {
        u32 x0;
        u32 x4;
    } hi;
    u16 x8;
} GrIm825C;
extern const GrIm825C grIm_803B825C;

/// @brief Ice Mountain row data - 12 bytes each.
typedef struct IceMtRowData {
    s32 id; // Row identifier, compared with xAC[i] values
    f32 x4;
    f32 x8;
} IceMtRowData;

IceMtRowData grIm_803E4068[6] = {
    { 1, 180.0f, -180.0f }, { 2, 190.0f, -180.0f }, { 3, 190.0f, -195.0f },
    { 4, 195.0f, -185.0f }, { 5, 190.0f, -200.0f }, { 6, 180.0f, -190.0f },
};

S16Vec3 grIm_803E40B0[] = {
    { 0, 0, 0 }, { 1, 0, 0 }, { 0, 1, 0 }, { 0, 0, 0 }, { 2, 0, 0 }
};

StageCallbacks grIm_803E4718[] = { { grIceMt_801F72D4, grIceMt_801F75DC,
                                     grIceMt_801F75E4, grIceMt_801F75E4, 0 },
                                   { grIceMt_801F7D94, grIceMt_801F7EE0,
                                     grIceMt_801F7EE8, grIceMt_801F7F1C, 0 },
                                   { grIceMt_801F7F70, grIceMt_801F8154,
                                     grIceMt_801F815C, grIceMt_801F81B4, 0 },
                                   { grIceMt_801F8208, grIceMt_801F835C,
                                     grIceMt_801F8364, grIceMt_801F8398, 0 },
                                   { grIceMt_801F83EC, grIceMt_801F85BC,
                                     grIceMt_801F85C4, grIceMt_801F8608, 0 },
                                   { grIceMt_801F865C, grIceMt_801F87C0,
                                     grIceMt_801F87C8, grIceMt_801F87FC, 0 },
                                   { grIceMt_801F8850, grIceMt_801F89A4,
                                     grIceMt_801F89AC, grIceMt_801F89E0, 0 },
                                   { 0, 0, 0, 0, 0 },
                                   { grIceMt_801F8A34, grIceMt_801F8B08,
                                     grIceMt_801F8B10, grIceMt_801F8C60, 0 },
                                   { grIceMt_801F75FC, grIceMt_801F7720,
                                     grIceMt_801F7728, grIceMt_801F77AC, 0 },
                                   { grIceMt_801F785C, grIceMt_801F796C,
                                     grIceMt_801F7A2C, grIceMt_801F7D90, 0 } };

StageData grIm_803E4800 = {
    0x16,
    grIm_803E4718,
    "/GrIm.dat",
    grIceMt_801F686C,
    grIceMt_801F6868,
    grIceMt_801F7080,
    grIceMt_801F71DC,
    grIceMt_801F71E0,
    grIceMt_801FA8F8,
    grIceMt_801FA900,
    1,
    grIm_803E40B0,
    3,
};

extern f32 grIm_804DB574;
extern f32 grIm_804DB578;
typedef struct GrIm588 {
    s16 a;
    s16 b;
} GrIm588;
static const GrIm588 grIm_804DB588 = { 1, 2 };
extern u32 grIm_804DB590;
extern u32 grIm_804DB594;
extern u32 grIm_804DB598;
extern u32 grIm_804DB59C;
extern u32 grIm_804DB5A0;
extern u32 grIm_804DB5A4;
extern f32 grIm_804DB5A8;
extern f32 grIm_804DB5AC;
extern f32 grIm_804DB5B0;
extern f32 grIm_804DB5B4;
extern f32 grIm_804DB5B8;

void grIceMt_801F6868(bool id) {}

#define ICEMT_FIELD_MAX 6

/// #grIceMt_801F686C
void grIceMt_801F686C(void)
{
    s32 field30;
    s32 field29;
    s32 field28;
    u32 row_idx;
    s16* xAC;
    s32 id;
    f32 y_pos;
    f32 y_pos2;
    f32 y_pos3;
    f32 y_pos4;
    HSD_GObj* gobj;
    HSD_JObj* jobj;

    grIm_804D69F4 = Ground_801C49F8();
    stage_info.unk8C.b4 = true;
    stage_info.unk8C.b5 = false;
    grIceMt_801F71E8(0);
    grIceMt_801F71E8(8);
    Ground_801C3260(1);
    Ground_801C3260(2);
    Ground_801C3260(3);
    Ground_801C3260(4);
    Ground_801C3260(5);
    Ground_801C3260(6);

    if (Stage_80225194() == 76) {
        // First loop: find row where neither xAC[0] nor xAC[1] matches
        for (row_idx = 0; row_idx < ICEMT_FIELD_MAX; row_idx++) {
            xAC = grIm_804D69F4->xAC;
            id = grIm_803E4068[row_idx].id;
            if (xAC[0] == id) {
                continue;
            }
            if (xAC[1] == id) {
                continue;
            }
            field30 = grIm_803E4068[row_idx].id;
            break;
        }
        HSD_ASSERTMSG(0x258, row_idx < ICEMT_FIELD_MAX, "<ICEMT_FIELD_MAX>");

        // Second loop: find row where xAC[0], xAC[1], and field30 don't match
        for (row_idx = 0; row_idx < ICEMT_FIELD_MAX; row_idx++) {
            xAC = grIm_804D69F4->xAC;
            id = grIm_803E4068[row_idx].id;
            if (xAC[0] == id) {
                continue;
            }
            if (xAC[1] == id) {
                continue;
            }
            if (field30 == id) {
                continue;
            }
            field29 = grIm_803E4068[row_idx].id;
            break;
        }
        HSD_ASSERTMSG(0x261, row_idx < ICEMT_FIELD_MAX, "<ICEMT_FIELD_MAX>");

        // Third loop: find row where xAC[0], xAC[1], field30, and field29
        // don't match
        for (row_idx = 0; row_idx < ICEMT_FIELD_MAX; row_idx++) {
            xAC = grIm_804D69F4->xAC;
            id = grIm_803E4068[row_idx].id;
            if (xAC[0] == id) {
                continue;
            }
            if (xAC[1] == id) {
                continue;
            }
            if (field30 == id) {
                continue;
            }
            if (field29 == id) {
                continue;
            }
            field28 = grIm_803E4068[row_idx].id;
            break;
        }
        HSD_ASSERTMSG(0x26B, row_idx < ICEMT_FIELD_MAX, "<ICEMT_FIELD_MAX>");

        // Calculate Y positions for the 3 topi platforms
        y_pos = Ground_801C0498();
        xAC = grIm_804D69F4->xAC;
        y_pos = grIm_804DB570 * y_pos;
        y_pos = y_pos + grIceMt_801F993C(grIm_803E4068[xAC[0]].id,
                                         grIm_803E4068[xAC[1]].id);
        y_pos2 = y_pos + grIceMt_801F993C(grIm_803E4068[xAC[1]].id, field30);
        y_pos3 = y_pos2 + grIceMt_801F993C(field30, field29);
        y_pos4 = y_pos3 + grIceMt_801F993C(field29, field28);

        // Set up first topi (grIm_804D69E8)
        gobj = grIceMt_801F71E8(grIm_803E4068[xAC[2]].id);
        if (gobj == NULL) {
            __assert(grIm_803E46F8, 0x27C, "bg_gobj");
        }
        jobj = gobj->hsd_obj;
        if (jobj == NULL) {
            __assert(grIm_803E46F8, 0x27D, "jobj");
        }
        HSD_JObjSetTranslateY(jobj, y_pos2);
        grIm_804D69E8 = gobj;

        // Set up second topi (grIm_804D69EC)
        gobj = grIceMt_801F71E8(grIm_803E4068[xAC[3]].id);
        if (gobj == NULL) {
            __assert(grIm_803E46F8, 0x281, "bg_gobj");
        }
        jobj = gobj->hsd_obj;
        if (jobj == NULL) {
            __assert(grIm_803E46F8, 0x282, "jobj");
        }
        HSD_JObjSetTranslateY(jobj, y_pos3);
        grIm_804D69EC = gobj;

        // Set up third topi (grIm_804D69F0)
        gobj = grIceMt_801F71E8(grIm_803E4068[xAC[4]].id);
        if (gobj == NULL) {
            __assert(grIm_803E46F8, 0x286, "bg_gobj");
        }
        jobj = gobj->hsd_obj;
        if (jobj == NULL) {
            __assert(grIm_803E46F8, 0x287, "jobj");
        }
        HSD_JObjSetTranslateY(jobj, y_pos4);
        grIm_804D69F0 = gobj;

        grIceMt_801F71E8(0xA);
    } else {
        grIceMt_801F71E8(9);
        grIm_804D69E8 = NULL;
        grIm_804D69EC = NULL;
        grIm_804D69F0 = NULL;
    }
    Ground_801C39C0();
    Ground_801C3BB4();
}

static inline bool rand_zero(s32 n)
{
    return ((n) ? HSD_Randi(n) : 0) == 0;
}

void grIceMt_801F7080(void)
{
    HSD_GObj* gobj;
    Vec3 x;
    if (grIm_804D69E8) {
        Ground_801C4A08(grIm_804D69E8);
    }
    if (grIm_804D69EC) {
        Ground_801C4A08(grIm_804D69EC);
    }
    if (grIm_804D69F0) {
        Ground_801C4A08(grIm_804D69F0);
    }
    if ((gobj = Ground_801C2BA4(1))) {
        Ground_801C2FE0(gobj);
    }
    if ((gobj = Ground_801C2BA4(2))) {
        Ground_801C2FE0(gobj);
    }
    if ((gobj = Ground_801C2BA4(3))) {
        Ground_801C2FE0(gobj);
    }
    if ((gobj = Ground_801C2BA4(4))) {
        Ground_801C2FE0(gobj);
    }
    if ((gobj = Ground_801C2BA4(5))) {
        Ground_801C2FE0(gobj);
    }
    if ((gobj = Ground_801C2BA4(6))) {
        Ground_801C2FE0(gobj);
    }
    if (Stage_80225194() == 76) {
        grZakoGenerator_801CAE04(&grIm_804D69F4->xBC);
        if (rand_zero(grIm_804D69F4->xB8)) {
            grZakoGenerator_801CAEB0(Ground_801C5840(), Ground_801C5940());
        }

        grZakoGenerator_801CADE0();
    } else {
        grZakoGenerator_801CAE04(NULL);
    }
    x = grIm_803B8220[0];
    grLib_801C96F8(0x7530, 0x1E, &x);
}

void grIceMt_801F71DC(void) {}

bool grIceMt_801F71E0(void)
{
    return false;
}

HSD_GObj* grIceMt_801F71E8(int gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grIm_803E4718[gobj_id];

    gobj = Ground_GetStageGObj(gobj_id);

    if (gobj != NULL) {
        Ground_SetupStageCallbacks(gobj, callbacks);
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "gricemt.c", 0x35C,
                 gobj_id);
    }

    return gobj;
}

/// #grIceMt_801F72D4
/// extern char grIm_803B8220;
extern char grIm_804D4718;
extern char grIm_804D4720;

void grIceMt_801F72D4(Ground_GObj* arg0)
{
    Vec3 v1;
    Vec3 v2;
    Vec3 v3;
    Vec3 v4;
    HSD_JObj* jobj;
    Ground* gp = GET_GROUND(arg0);
    grAnime_801C8138(arg0, gp->map_id, 0);
    jobj = Ground_801C3FA4(arg0, 0x12);
    if (jobj != 0) {
        v1 = grIm_803B8220[1];
        HSD_JObjSetTranslate(jobj, &v1);
    }
    jobj = Ground_801C3FA4(arg0, 0x13);
    if (jobj != 0) {
        v2 = grIm_803B8220[2];
        HSD_JObjSetTranslate(jobj, &v2);
    }
    jobj = Ground_801C3FA4(arg0, 0x14);
    if (jobj != 0) {
        v3 = grIm_803B8220[3];
        HSD_JObjSetTranslate(jobj, &v3);
    }
    jobj = Ground_801C3FA4(arg0, 0x15);
    if (jobj != 0) {
        v4 = grIm_803B8220[4];
        HSD_JObjSetTranslate(jobj, &v4);
    }
    Ground_801C39C0();
    Ground_801C3BB4();
}

bool grIceMt_801F75DC(Ground_GObj* arg0)
{
    return false;
}

void grIceMt_801F75E4(Ground_GObj* arg0) {}

void grIceMt_801F75E8(Ground_GObj* arg0) {}

void fn_801F75EC(HSD_GObj* arg0)
{
    GET_GROUND(arg0)->gv.icemt.xD8 = 0;
}

/// #grIceMt_801F75FC
/// @note This function treats xF4 area as s16 indices during initialization.
/// The same memory is later interpreted as pointers by other functions.
void grIceMt_801F75FC(Ground_GObj* arg0)
{
    u32 iVar1;
    s16 val;
    Ground* gp = GET_GROUND(arg0);
    PAD_STACK(8);
    memzero(&gp->gv.icemt.xDC, 0x18);
    memzero(&gp->gv.icemt.xF4, 0x14);
    do {
        iVar1 = HSD_Randi(6);
        val = gp->gv.icemt.xF4[iVar1];
    } while (val != 0);
    gp->gv.icemt.xF4[iVar1] = *(s16*) grIm_804D69F4;
    gp->gv.icemt.xC4 = (s16) grIm_803E4068[iVar1].id;
    do {
        iVar1 = HSD_Randi(6);
        val = gp->gv.icemt.xF4[iVar1];
    } while (val != 0);
    gp->gv.icemt.xF4[iVar1] = *(s16*) grIm_804D69F4;
    gp->gv.icemt.xC6 = (s16) grIm_803E4068[iVar1].id;
    grIceMt_801FA0BC(&gp->gv.icemt.xC4);
    gp->gv.icemt.xDA = 0;
    gp->gv.icemt.xC8 = 0;
    gp->gv.icemt.xCE = 0;
    gp->gv.icemt.xCA = 0;
    gp->gv.icemt.xCC = 0;
    gp->gv.icemt.xD0 = -1;
    gp->gv.icemt.xD4 = 0;
    gp->gv.icemt.xD8 = 1;
    Ground_801C10B8(arg0, fn_801F75EC);
    return;
}

bool grIceMt_801F7720(Ground_GObj* arg0)
{
    return false;
}

/// #grIceMt_801F7728
void grIceMt_801F7728(Ground_GObj* gobj)
{
    u32 unused1;
    float y;
    u32 unused2;
    Ground* gp = gobj->user_data;
    if (gp->gv.icemt.xD8 == 0) {
        grIceMt_801FA364(&gp->gv.corneria.xC8, &y, (HSD_GObjEvent) fn_801F8E58,
                         gobj);
        grIceMt_801F9ACC(
            (HSD_GObj*) &gp->gv.corneria.xC4,
            grIceMt_801F96E0((HSD_GObj*) &gp->gv.corneria.xC4, -y),
            fn_801F9038, gobj);
        grIceMt_801F9668(y);
    }
}

void grIceMt_801F77AC(Ground_GObj* arg0) {}

extern s16 grIm_803E4544[218];

/// #fn_801F77B0
void fn_801F77B0(HSD_GObj* arg0)
{
    Ground* gp = GET_GROUND(arg0);
    u32 i;
    mpLib_Callback cb;
    Ground* gp_out;

    ((UnkFlagStruct*) &gp->gv.icemt.xD8)->b0 = 0;

    for (i = 0; i < 0xD9; i++) {
        mpJointGetCb1(grIm_803E4544[i], &cb, &gp_out);
        if (cb == NULL) {
            mpJointSetCb1(grIm_803E4544[i], gp, grIceMt_801FA7F0);
        }
    }
}

/// #grIceMt_801F785C
void grIceMt_801F785C(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);

    // Index into grIm_803E4068 using row indices from grIm_804D69F4->xAC
    gp->gv.icemt.xC4 = (s16) grIm_803E4068[grIm_804D69F4->xAC[1]].id;
    gp->gv.icemt.xC6 = (s16) grIm_803E4068[grIm_804D69F4->xAC[0]].id;

    grIceMt_801FA0BC(&gp->gv.icemt.xC4);

    gp->gv.icemt.xDC = 0;
    gp->gv.icemt.xE0 = 2;
    gp->gv.icemt.xDE = 0;

    ((UnkFlagStruct*) &gp->gv.icemt.xD8)->b1 = 0;
    ((UnkFlagStruct*) &gp->gv.icemt.xD8)->b2 = 0;
    ((UnkFlagStruct*) &gp->gv.icemt.xD8)->b3 = 0;
    ((UnkFlagStruct*) &gp->gv.icemt.xD8)->b4 = 0;

    gp->gv.icemt.xDA = 0;
    gp->gv.icemt.xE4 = grIm_804DB574;
    gp->gv.icemt.xC8 = 0;
    gp->gv.icemt.xCE = 0;
    gp->gv.icemt.xCA = 0;
    gp->gv.icemt.xCC = 0;
    gp->gv.icemt.xD0 = -1;
    gp->gv.icemt.xD4 = grIm_804DB574;

    ((UnkFlagStruct*) &gp->gv.icemt.xD8)->b0 = 1;

    Ground_801C10B8(gobj, fn_801F77B0);
}

/// #grIceMt_801F796C gricemt.c
bool grIceMt_801F796C(Ground_GObj* arg0)
{
    Ground* gp = arg0->user_data;
    HSD_GObj* mgobj;
    PAD_STACK(8);

    if (gp->gv.icemt.xC4 != -1) {
        mgobj = Ground_801C2BA4(gp->gv.icemt.xC4);
        if (mgobj == NULL) {
            __assert(grIm_803E46F8, 0x475, "mgobj");
        }
        Ground_801C4A08(mgobj);
    }
    if (gp->gv.icemt.xC6 != -1) {
        mgobj = Ground_801C2BA4(gp->gv.icemt.xC6);
        if (mgobj == NULL) {
            __assert(grIm_803E46F8, 0x47A, "mgobj");
        }
        Ground_801C4A08(mgobj);
    }
    grIceMt_801F785C(arg0);
    ((UnkFlagStruct*) &gp->gv.icemt.xD8)->b0 = 0;
    return 0;
}

/// #grIceMt_801F7A2C
void grIceMt_801F7A2C(Ground_GObj* arg0)
{
    Ground* gp = arg0->user_data;
    f32 sp30;
    Vec3 sp24;
    HSD_GObj* fighter;
    HSD_GObj* mgobj;
    HSD_JObj* jobj;
    f32 dist;
    f32 cur;
    f32 step;
    f32 ratio;
    s32 var_r30;
    s32 r;
    PAD_STACK(8);

    if (((UnkFlagStruct*) &gp->gv.icemt.xD8)->b0) {
        return;
    }
    if (!((UnkFlagStruct*) &gp->gv.icemt.xD8)->b2) {
        var_r30 = grIceMt_801FA364(&gp->gv.corneria.xC8, &sp30,
                                   (HSD_GObjEvent) fn_801F9150, arg0);
        if (((UnkFlagStruct*) &gp->gv.icemt.xD8)->b4) {
            fighter = Ground_801C57A4();
            if (fighter != NULL) {
                ftLib_80086644(fighter, &sp24);
                if (!((UnkFlagStruct*) &gp->gv.icemt.xD8)->b1 &&
                    !ftLib_80086EC0(fighter) &&
                    sp24.y > (f32) ((s16*) grIm_804D69F4)[0x98 / 2])
                {
                    ((UnkFlagStruct*) &gp->gv.icemt.xD8)->b1 = 1;
                    gp->gv.icemt.xDA = ((s16*) grIm_804D69F4)[0xA4 / 2];
                }
            }
        }
        if (((UnkFlagStruct*) &gp->gv.icemt.xD8)->b1) {
            gp->gv.icemt.xE4 += grIm_804D69F4->xA0;
            if (gp->gv.icemt.xE4 > grIm_804D69F4->x9C) {
                gp->gv.icemt.xE4 = grIm_804D69F4->x9C;
            }
            gp->gv.icemt.xDA -= 1;
            if (gp->gv.icemt.xDA == 0) {
                ((UnkFlagStruct*) &gp->gv.icemt.xD8)->b1 = 0;
            }
        } else {
            gp->gv.icemt.xE4 -= grIm_804D69F4->xA0;
            if (gp->gv.icemt.xE4 < grIm_804DB574) {
                gp->gv.icemt.xE4 = grIm_804DB574;
            }
        }
        sp30 += gp->gv.icemt.xE4;
    } else {
        mgobj = Ground_801C2BA4(gp->gv.icemt.xC6);
        if (mgobj == NULL) {
            __assert(grIm_803E46F8, 0x4C3, "mgobj");
        }
        jobj = mgobj->hsd_obj;
        if (jobj == NULL) {
            __assert(grIm_803E46F8, 0x4C5, "jobj");
        }
        dist = HSD_JObjGetTranslationY(jobj) -
               (f32) ((s16*) grIm_804D69F4)[0xA8 / 2];
        if (dist < grIm_804DB574) {
            gp->gv.icemt.xD4 = grIm_804DB574;
        } else {
            ratio = gp->gv.icemt.xD4 / grIm_804D69F4->xA0;
            if ((gp->gv.icemt.xD4 * ratio) -
                    (ratio * (0.5f * grIm_804D69F4->xA0 * ratio)) >
                dist)
            {
                gp->gv.icemt.xD4 -= grIm_804D69F4->xA0;
                if (gp->gv.icemt.xD4 < grIm_804D69F4->xA0) {
                    gp->gv.icemt.xD4 = grIm_804D69F4->xA0;
                }
            }
        }
        sp30 = gp->gv.icemt.xD4;
    }
    grIceMt_801F9ACC((Ground_GObj*) &gp->gv.icemt.xC4,
                     grIceMt_801F96E0((HSD_GObj*) &gp->gv.icemt.xC4, -sp30),
                     fn_801F91A8, arg0);
    grIceMt_801F9668(sp30);
    if (gp->gv.icemt.xC4 == -1) {
        ((UnkFlagStruct*) &gp->gv.icemt.xD8)->b2 = 1;
    }
    if (!((UnkFlagStruct*) &gp->gv.icemt.xD8)->b3) {
        if (var_r30 != 0 &&
            gp->gv.icemt.xDE == ((s16*) grIm_804D69F4)[0xA6 / 2])
        {
            ((UnkFlagStruct*) &gp->gv.icemt.xD8)->b3 = 1;
            Ground_801C5750();
            gm_801674C4(0xE, 2, 2, 0, fn_801FA4CC);
            grZakoGenerator_801CAF08();
        }
    } else {
        r = Ground_801C5764();
        switch (r) {
        case 2:
            break;
        case 1:
            Ground_801C1D6C(0x10);
            break;
        }
    }
    ((UnkFlagStruct*) &gp->gv.icemt.xD8)->b4 = 0;
}

void grIceMt_801F7D90(Ground_GObj* arg0) {}

void grIceMt_801F7D94(Ground_GObj* arg0)
{
    Ground* gp = GET_GROUND(arg0);
    GrIm588 sp14;
    Ground_801C2ED0(arg0->hsd_obj, gp->map_id);
    grAnime_801C8138(arg0, gp->map_id, 0);
    grAnime_801C77FC(arg0, 0, 7);
    gp->gv.icemt2.xC8 = Ground_801C3FA4(arg0, 3);
    gp->gv.icemt2.xCC = Ground_801C3FA4(arg0, 4);
    gp->gv.icemt2.xD0 = Ground_801C3FA4(arg0, 5);
    gp->gv.icemt2.xD4 = Ground_801C3FA4(arg0, 6);
    gp->gv.icemt2.xD8 = Ground_801C3FA4(arg0, 18);
    gp->gv.icemt2.xDC = Ground_801C3FA4(arg0, 11);
    gp->gv.icemt2.xE0 = Ground_801C3FA4(arg0, 12);
    gp->gv.icemt2.xE4 = Ground_801C3FA4(arg0, 13);
    gp->gv.icemt2.xE8 = Ground_801C3FA4(arg0, 14);
    gp->gv.icemt2.xEC = Ground_801C3FA4(arg0, 15);
    gp->gv.icemt2.xF0 = Ground_801C3FA4(arg0, 16);
    gp->gv.icemt2.xF4 = Ground_801C3FA4(arg0, 17);
    ((UnkFlagStruct*) &gp->gv.icemt2.xC4)->b0 = 0;
    sp14 = grIm_804DB588;
    grIceMt_801F8CDC(arg0, (s16*) &sp14, 2, &gp->gv.icemt.xF8[0]);
}

bool grIceMt_801F7EE0(Ground_GObj* arg0)
{
    return false;
}

void grIceMt_801F7EE8(Ground_GObj* arg0)
{
    PAD_STACK(8);
    grIceMt_801F98A8(arg0);
    Ground_801C2FE0(arg0);
}

/// #grIceMt_801F7F1C
void grIceMt_801F7F1C(Ground_GObj* gobj)
{
    int i;
    Ground* gp = gobj->user_data;
    u32 unused[2];

    for (i = 0; i < 2; i++) {
        if (gp->gv.icemt.xF8[i] != NULL) {
            grMaterial_801C8CDC(gp->gv.icemt.xF8[i]);
        }
    }
}

/// #grIceMt_801F7F70
void grIceMt_801F7F70(Ground_GObj* arg0)
{
    Ground* gp = GET_GROUND(arg0);
    HSD_JObj* jobj;
    HSD_JObj* jobj2;
    Ground_801C2ED0(arg0->hsd_obj, gp->map_id);
    grAnime_801C8138(arg0, gp->map_id, 0);
    grAnime_801C77FC(arg0, 0, 7);
    jobj = Ground_801C3FA4(arg0, 4);
    jobj2 = Ground_801C3FA4(arg0, 5);
    gp->gv.icemt2.xC8 = Ground_801C3FA4(arg0, 6);
    gp->gv.icemt2.xCC = Ground_801C3FA4(arg0, 7);
    gp->gv.icemt2.xD0 = Ground_801C3FA4(arg0, 8);
    gp->gv.icemt2.xD4 = Ground_801C3FA4(arg0, 9);
    gp->gv.icemt2.xD8 = Ground_801C3FA4(arg0, 21);
    gp->gv.icemt2.xDC = Ground_801C3FA4(arg0, 14);
    gp->gv.icemt2.xE0 = Ground_801C3FA4(arg0, 15);
    gp->gv.icemt2.xE4 = Ground_801C3FA4(arg0, 16);
    gp->gv.icemt2.xE8 = Ground_801C3FA4(arg0, 17);
    gp->gv.icemt2.xEC = Ground_801C3FA4(arg0, 18);
    gp->gv.icemt2.xF0 = Ground_801C3FA4(arg0, 19);
    gp->gv.icemt2.xF4 = Ground_801C3FA4(arg0, 20);
    // gp->gv.icemt.xD8 = 1;
}

bool grIceMt_801F8154(Ground_GObj* param1)
{
    return false;
}

void grIceMt_801F815C(Ground_GObj* param1)
{
    Ground* gp = GET_GROUND(param1);
    grIceMt_801F929C(param1, &gp->gv.icemt.xF8[2]);
    grIceMt_801F929C(param1, &gp->gv.icemt.x10E);
    grIceMt_801F98A8(param1);
    Ground_801C2FE0(param1);
}

/// #grIceMt_801F81B4
void grIceMt_801F81B4(Ground_GObj* gobj)
{
    int i;
    Ground* gp = gobj->user_data;
    u32 unused[2];

    for (i = 0; i < 2; i++) {
        if (gp->gv.icemt.xF8[i] != NULL) {
            grMaterial_801C8CDC(gp->gv.icemt.xF8[i]);
        }
    }
}

void grIceMt_801F8208(Ground_GObj* arg0)
{
    Ground* gp = GET_GROUND(arg0);
    struct {
        u32 x0;
        u32 x4;
    } sp14;
    PAD_STACK(4);
    Ground_801C2ED0(arg0->hsd_obj, gp->map_id);
    grAnime_801C8138(arg0, gp->map_id, 0);
    grAnime_801C77FC(arg0, 0, 7);
    gp->gv.icemt2.xC8 = Ground_801C3FA4(arg0, 5);
    gp->gv.icemt2.xCC = Ground_801C3FA4(arg0, 6);
    gp->gv.icemt2.xD0 = Ground_801C3FA4(arg0, 7);
    gp->gv.icemt2.xD4 = Ground_801C3FA4(arg0, 8);
    gp->gv.icemt2.xD8 = Ground_801C3FA4(arg0, 21);
    gp->gv.icemt2.xDC = Ground_801C3FA4(arg0, 14);
    gp->gv.icemt2.xE0 = Ground_801C3FA4(arg0, 15);
    gp->gv.icemt2.xE4 = Ground_801C3FA4(arg0, 16);
    gp->gv.icemt2.xE8 = Ground_801C3FA4(arg0, 17);
    gp->gv.icemt2.xEC = Ground_801C3FA4(arg0, 18);
    gp->gv.icemt2.xF0 = Ground_801C3FA4(arg0, 19);
    gp->gv.icemt2.xF4 = Ground_801C3FA4(arg0, 20);
    ((UnkFlagStruct*) &gp->gv.icemt2.xC4)->b0 = 0;
    sp14.x0 = grIm_804DB590;
    sp14.x4 = grIm_804DB594;
    grIceMt_801F8CDC(arg0, (s16*) &sp14, 4, &gp->gv.icemt.xF8[0]);
}

bool grIceMt_801F835C(Ground_GObj* param1)
{
    return false;
}

void grIceMt_801F8364(Ground_GObj* arg0)
{
    grIceMt_801F98A8(arg0);
    Ground_801C2FE0(arg0);
}

/// #grIceMt_801F8398
void grIceMt_801F8398(Ground_GObj* gobj)
{
    int i = 0;
    Ground* gp = gobj->user_data;
    u32 unused[2];

    while (i < 4) {
        if (gp->gv.icemt.xF8[i] != NULL) {
            grMaterial_801C8CDC(gp->gv.icemt.xF8[i]);
        }
        i++;
    }
}

void grIceMt_801F83EC(Ground_GObj* arg0)
{
    Ground* gp = GET_GROUND(arg0);
    HSD_JObj* jobj;
    HSD_JObj* jobj2;
    s32 r;
    struct {
        u32 x0;
        u32 x4;
    } sp14;
    Ground_801C0498();
    Ground_801C2ED0(arg0->hsd_obj, gp->map_id);
    grAnime_801C8138(arg0, gp->map_id, 0);
    grAnime_801C77FC(arg0, 0, 7);
    jobj = Ground_801C3FA4(arg0, 7);
    jobj2 = Ground_801C3FA4(arg0, 5);
    gp->gv.icemt2.xC8 = Ground_801C3FA4(arg0, 8);
    gp->gv.icemt2.xCC = Ground_801C3FA4(arg0, 9);
    gp->gv.icemt2.xD0 = Ground_801C3FA4(arg0, 10);
    gp->gv.icemt2.xD4 = Ground_801C3FA4(arg0, 11);
    gp->gv.icemt2.xD8 = Ground_801C3FA4(arg0, 23);
    gp->gv.icemt2.xDC = Ground_801C3FA4(arg0, 16);
    gp->gv.icemt2.xE0 = Ground_801C3FA4(arg0, 17);
    gp->gv.icemt2.xE4 = Ground_801C3FA4(arg0, 18);
    gp->gv.icemt2.xE8 = Ground_801C3FA4(arg0, 19);
    gp->gv.icemt2.xEC = Ground_801C3FA4(arg0, 20);
    gp->gv.icemt2.xF0 = Ground_801C3FA4(arg0, 21);
    gp->gv.icemt2.xF4 = Ground_801C3FA4(arg0, 22);
    ((UnkFlagStruct*) &gp->gv.icemt2.xC4)->b0 = 0;
    sp14.x0 = grIm_804DB598;
    sp14.x4 = grIm_804DB59C;
    grIceMt_801F8CDC(arg0, (s16*) &sp14, 4, &gp->gv.icemt.xF8[0]);
    r = grIceMt_801FA500(arg0, jobj2);
    grIceMt_801F91EC(arg0, (s16*) ((u8*) gp + 0x108),
                     grIceMt_801FA500(arg0, jobj), r, 0x75, 0x109, 0x27E,
                     (mpLib_Callback) fn_801F9558);
}

bool grIceMt_801F85BC(Ground_GObj* param1)
{
    return false;
}

void grIceMt_801F85C4(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    grIceMt_801F929C(gobj, &gp->gv.icemt.xF8[4]);
    grIceMt_801F98A8(gobj);
    Ground_801C2FE0(gobj);
}
/// #grIceMt_801F8608
void grIceMt_801F8608(Ground_GObj* gobj)
{
    s32 i;
    Ground* gp;
    u32 unused[2];

    gp = gobj->user_data;

    for (i = 0; i < 4; i++) {
        if (gp->gv.icemt.xF8[i] != NULL) {
            grMaterial_801C8CDC(gp->gv.icemt.xF8[i]);
        }
    }
}

void grIceMt_801F865C(Ground_GObj* arg0)
{
    Ground* gp = GET_GROUND(arg0);
    GrIm825C sp14;
    Ground_801C2ED0(arg0->hsd_obj, gp->map_id);
    grAnime_801C8138(arg0, gp->map_id, 0);
    grAnime_801C77FC(arg0, 0, 7);
    gp->gv.icemt2.xC8 = Ground_801C3FA4(arg0, 6);
    gp->gv.icemt2.xCC = Ground_801C3FA4(arg0, 7);
    gp->gv.icemt2.xD0 = Ground_801C3FA4(arg0, 8);
    gp->gv.icemt2.xD4 = Ground_801C3FA4(arg0, 9);
    gp->gv.icemt2.xD8 = Ground_801C3FA4(arg0, 22);
    gp->gv.icemt2.xDC = Ground_801C3FA4(arg0, 15);
    gp->gv.icemt2.xE0 = Ground_801C3FA4(arg0, 16);
    gp->gv.icemt2.xE4 = Ground_801C3FA4(arg0, 17);
    gp->gv.icemt2.xE8 = Ground_801C3FA4(arg0, 18);
    gp->gv.icemt2.xEC = Ground_801C3FA4(arg0, 19);
    gp->gv.icemt2.xF0 = Ground_801C3FA4(arg0, 20);
    gp->gv.icemt2.xF4 = Ground_801C3FA4(arg0, 21);
    ((UnkFlagStruct*) &gp->gv.icemt2.xC4)->b0 = 0;
    sp14.hi = grIm_803B825C.hi;
    sp14.x8 = grIm_803B825C.x8;
    grIceMt_801F8CDC(arg0, (s16*) &sp14, 5, &gp->gv.icemt.xF8[0]);
}

bool grIceMt_801F87C0(Ground_GObj* param1)
{
    return false;
}

/// #grIceMt_801F87C8
void grIceMt_801F87C8(Ground_GObj* param1)
{
    grIceMt_801F98A8(param1);
    Ground_801C2FE0(param1);
    return;
}

/// @todo Rename: This is callback3 (destroy) for row 5 in grIm_803E4718.
/// Destroys HSD_GObj* stored in icemt.xF8[0-4].
void grIceMt_801F87FC(Ground_GObj* gobj)
{
    u32 unused[2];
    int i;
    Ground* gp = gobj->user_data;
    for (i = 0; i < 5; i++) {
        if (gp->gv.icemt.xF8[i] != NULL) {
            grMaterial_801C8CDC(gp->gv.icemt.xF8[i]);
        }
    }
}

void grIceMt_801F8850(Ground_GObj* arg0)
{
    Ground* gp = GET_GROUND(arg0);
    struct {
        u32 x0;
        u32 x4;
    } sp14;
    PAD_STACK(4);
    Ground_801C2ED0(arg0->hsd_obj, gp->map_id);
    grAnime_801C8138(arg0, gp->map_id, 0);
    grAnime_801C77FC(arg0, 0, 7);
    gp->gv.icemt2.xC8 = Ground_801C3FA4(arg0, 5);
    gp->gv.icemt2.xCC = Ground_801C3FA4(arg0, 6);
    gp->gv.icemt2.xD0 = Ground_801C3FA4(arg0, 7);
    gp->gv.icemt2.xD4 = Ground_801C3FA4(arg0, 8);
    gp->gv.icemt2.xD8 = Ground_801C3FA4(arg0, 21);
    gp->gv.icemt2.xDC = Ground_801C3FA4(arg0, 14);
    gp->gv.icemt2.xE0 = Ground_801C3FA4(arg0, 15);
    gp->gv.icemt2.xE4 = Ground_801C3FA4(arg0, 16);
    gp->gv.icemt2.xE8 = Ground_801C3FA4(arg0, 17);
    gp->gv.icemt2.xEC = Ground_801C3FA4(arg0, 18);
    gp->gv.icemt2.xF0 = Ground_801C3FA4(arg0, 19);
    gp->gv.icemt2.xF4 = Ground_801C3FA4(arg0, 20);
    ((UnkFlagStruct*) &gp->gv.icemt2.xC4)->b0 = 0;
    sp14.x0 = grIm_804DB5A0;
    sp14.x4 = grIm_804DB5A4;
    grIceMt_801F8CDC(arg0, (s16*) &sp14, 4, &gp->gv.icemt.xF8[0]);
}

bool grIceMt_801F89A4(Ground_GObj* arg0)
{
    return false;
}

void grIceMt_801F89AC(Ground_GObj* param1)
{
    grIceMt_801F98A8(param1);
    Ground_801C2FE0(param1);
    return;
}

void grIceMt_801F89E0(Ground_GObj* gobj)
{
    Ground* gp;
    int i;
    u32 unused[2];

    gp = gobj->user_data;

    for (i = 0; i < 4; i++) {
        if (gp->gv.icemt.xF8[i] != NULL) {
            grMaterial_801C8CDC(gp->gv.icemt.xF8[i]);
        }
    }
}

void grIceMt_801F8A34(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);

    grAnime_801C8138(gobj, gp->map_id, 0);
    grAnime_801C77FC(gobj, 0, 7);
    Ground_801C4E70(Ground_801C3FA4(gobj, 1), Ground_801C3FA4(gobj, 2),
                    Ground_801C3FA4(gobj, 3), Ground_801C3FA4(gobj, 4),
                    Ground_801C3FA4(gobj, 5), Ground_801C3FA4(gobj, 6));
    gp->gv.icemt2.xC4 = 0.0f;
    gp->x11_flags.b012 = 2;
}

bool grIceMt_801F8B08(Ground_GObj* arg0)
{
    return false;
}

void grIceMt_801F8B10(Ground_GObj* arg0)
{
    Ground* gp = GET_GROUND(arg0);
    HSD_JObj* jobj;
    f32 mul;
    f32 cur;
    mul = grIm_804DB5A8 * gp->gv.icemt2.xC4;
    jobj = Ground_801C3FA4(arg0, 8);
    if (jobj == NULL) {
        __assert(grIm_803E46F8, 0x78F, "jobj");
    }
    cur = HSD_JObjGetTranslationY(jobj);
    cur = cur - mul;
    if (cur > grIm_804DB578 * (grIm_804DB5AC * Ground_801C0498())) {
        cur = -(grIm_804DB5AC * Ground_801C0498() - cur);
    } else if (cur < grIm_804DB578 * -(grIm_804DB5AC * Ground_801C0498())) {
        cur += grIm_804DB5AC * Ground_801C0498();
    }
    HSD_JObjSetTranslateY(jobj, cur);
}

void grIceMt_801F8C60(Ground_GObj* arg0) {}

void fn_801F8C64(Item_GObj* gobj, Ground* u1, Vec3* u2, HSD_GObj* u3, f32 u4)
{
    Vec3 pos;
    Item* it = GET_ITEM(gobj);
    grMaterial_801C8E28(gobj);

    HSD_JObjSetFlagsAll(it->xDD4_itemVar.mato.x4, 0x10);
    it_8026B294(gobj, &pos);
    efSync_Spawn(0x445, gobj, &pos);
    Ground_801C53EC(310);
    Camera_80030E44(2, &pos);
}

/// @brief Creates material items and attaches them to Entity05 platform JObjs.
/// @param gobj The Entity05 Ground_GObj
/// @param joint_indices Array of joint indices to get parent JObjs from
/// @param count Number of items to create (max 20)
/// @param output_array Array to store created Item_GObj pointers
void grIceMt_801F8CDC(Ground_GObj* gobj, s16* joint_indices, int count,
                      HSD_GObj** output_array)
{
    Ground* gp = gobj->user_data;
    UnkArchiveStruct* archive;
    void* jobj_desc;
    HSD_JObj* parent_jobjs[20];
    HSD_JObj* parent_jobj;
    HSD_JObj* child_jobj;
    Item_GObj* item;
    int i;
    u8 unused[24];

    archive = grDatFiles_801C6324();
    jobj_desc = archive->unk4->unk8[7].unk0;

    if (count > 20) {
        __assert(grIm_803E46F8, 0x7D4, "count <= 20");
    }

    for (i = 0; i < count; i++) {
        parent_jobjs[i] = Ground_801C3FA4(gobj, joint_indices[i]);
    }

    for (i = 0; i < count; i++) {
        parent_jobj = parent_jobjs[i];
        if (parent_jobj == NULL) {
            __assert(grIm_803E46F8, 0x7E3, "parent_jobj");
        }

        child_jobj = HSD_JObjLoadJoint(jobj_desc);
        if (child_jobj == NULL) {
            __assert(grIm_803E46F8, 0x7E6, "child_jobj");
        }

        HSD_JObjAddChild(parent_jobj, child_jobj);

        item = grMaterial_801C8CFC(8, 0, gp, parent_jobj, NULL, fn_801F8C64,
                                   NULL);
        if (item != NULL) {
            grMaterial_801C8DE0(item, grIm_804DB574, grIm_804DB5B0,
                                grIm_804DB574, grIm_804DB574, grIm_804DB5B4,
                                grIm_804DB574, grIm_804DB5B8);
            grMaterial_801C8E08(item);
            grMaterial_801C8E68(item, 0);
        }
        output_array[i] = item;
    }
}

s32 fn_801F8E58(Ground_GObj* arg0, s32* out)
{
    s32 list[12];
    s32 count;
    s32 i;
    s32 pick;
    s32 chosen;
    Ground* gp;
    s16* timer;
    s16 a;
    s16 b;
    s32 d;

    count = 0;
    gp = arg0->user_data;
    timer = &gp->gv.icemt.xDC;

    {
        Ground* g = gp;
        i = 0;
        do {
            if (g->gv.icemt.xDC == 0 &&
                (Stage_80225194() != 0xD4 || i >= 4))
            {
                list[count] = i;
                count++;
            }
            i++;
            g = (Ground*) ((u8*) g + 2);
        } while (i < 12);
    }

    if (count == 0) {
        __assert(grIm_803E46F8, 0x81D, "max");
    }
    pick = count != 0 ? HSD_Randi(count) : 0;
    chosen = list[pick];

    {
        Ground* g = gp;
        for (i = 0; i < 12; i++) {
            if (g->gv.icemt.xDC > 0) {
                g->gv.icemt.xDC--;
            }
            g = (Ground*) ((u8*) g + 2);
        }
    }

    timer[chosen] = *(s16*) ((u8*) grIm_804D69F4 + 2);
    a = *(s16*) ((u8*) grIm_804D69F4 + 0x36);
    b = *(s16*) ((u8*) grIm_804D69F4 + 0x38);
    if (a > b) {
        d = a - b;
        a = b + (d != 0 ? HSD_Randi(d) : 0);
    } else if (a < b) {
        d = b - a;
        a = a + (d != 0 ? HSD_Randi(d) : 0);
    }
    *out = a;
    return chosen;
}

int fn_801F9038(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    s32 idx;
    s32 i;
    PAD_STACK(8);

    do {
        idx = HSD_Randi(6);
    } while (gp->gv.icemt.xF4[idx] != 0 ||
             gp->gv.icemt.xC4 == grIm_803E4068[idx].id ||
             gp->gv.icemt.xC6 == grIm_803E4068[idx].id);

    for (i = 0; i < 6; i++) {
        if (gp->gv.icemt.xF4[i] > 0) {
            gp->gv.icemt.xF4[i]--;
        }
    }

    gp->gv.icemt.xF4[idx] = *(s16*) grIm_804D69F4;

    return grIm_803E4068[idx].id;
}

s32 fn_801F9150(HSD_GObj* arg0, s32* out)
{
    Ground* gp = arg0->user_data;
    s16 next = 0;
    s16 a;

    while (true) {
        a = grIm_804D69F4->xB0[gp->gv.icemt.xDE];
        *out = grIm_804D69F4->xB4[gp->gv.icemt.xDE];
        if (a != -1 && *out != -1) {
            gp->gv.icemt.xDE++;
            return a;
        }
        gp->gv.icemt.xDE = next;
    }
}

void fn_801F91A4(void) {}

int fn_801F91A8(Ground_GObj* gobj)
{
    Ground* gp;
    s32 index;
    s32 result;
    s16* xAC;

    gp = gobj->user_data;
    xAC = grIm_804D69F4->xAC;
    index = xAC[gp->gv.icemt.xE0];
    result = index;
    if (result == -1) {
        return result;
    }
    result = grIm_803E4068[index].id;
    gp->gv.icemt.xE0++;
    return result;
}

void grIceMt_801F91EC(HSD_GObj* param_1, s16* param_2, int param_3,
                      int param_4, int param_5, int param_6, int param_7,
                      mpLib_Callback param_8)
{
    Ground* gp = GET_GROUND(param_1);
    param_2[0] = 0;
    param_2[1] = 0;
    param_2[2] = param_3;
    param_2[3] = param_4;
    param_2[4] = param_5;
    param_2[5] = param_6;
    param_2[6] = param_7;
    grAnime_801C7A04(param_1, param_3, 7, 0);
    if (param_4 != -1) {
        grAnime_801C7A04(param_1, param_4, 7, 0);
    }
    mpJointSetCb1(param_5, gp, param_8);
}

/// #grIceMt_801F929C
void grIceMt_801F929C(HSD_GObj* arg0, void* arg1)
{
    s16* p = arg1;

    if (p[0] != 0) {
        p[1] += 1;
        if (p[1] == p[5]) {
            mpLib_80057BC0(p[4]);
        } else if (p[1] == p[6]) {
            mpJointListAdd(p[4]);
        }
        if (grAnime_801C83D0(arg0, p[2], 7)) {
            p[0] = 0;
        }
    }
}

typedef struct GrIceMtAnim {
    /* 0x0 */ s16 active;
    /* 0x2 */ s16 counter;
    /* 0x4 */ s16 joint0;
    /* 0x6 */ s16 joint1;
} GrIceMtAnim;

void fn_801F9338(Ground* gp, int arg1, CollData* arg2, s32 arg3,
                 mpLib_GroundEnum arg4, float arg8)
{
    HSD_GObj* gobj;
    GrIceMtAnim* s = (GrIceMtAnim*) ((u8*) gp + 0x100);
    PAD_STACK(8);
    if ((s32) arg2->x34_flags.b1234 == 1 && s->active == 0) {
        gobj = Ground_801C2BA4(2);
        s->active = 1;
        s->counter = 0;
        grAnime_801C7A04(gobj, s->joint0, 7, grIm_804DB5B4);
        grAnime_801C7B24(gobj, s->joint0, 7, grIm_804DB574);
        grAnime_801C78FC(gobj, s->joint0, 7);
        if (s->joint1 != -1) {
            grAnime_801C7A04(gobj, s->joint1, 7, grIm_804DB5B4);
            grAnime_801C7B24(gobj, s->joint1, 7, grIm_804DB574);
            grAnime_801C78FC(gobj, s->joint1, 7);
        }
    }
    grIceMt_801FA7F0(gp, arg1, arg2, arg3, arg4, arg8);
}

void fn_801F9448(Ground* gp, int arg1, CollData* arg2, s32 arg3,
                 mpLib_GroundEnum arg4, float arg8)
{
    HSD_GObj* gobj;
    GrIceMtAnim* s = (GrIceMtAnim*) ((u8*) gp + 0x10E);
    PAD_STACK(8);
    if ((s32) arg2->x34_flags.b1234 == 1 && s->active == 0) {
        gobj = Ground_801C2BA4(2);
        s->active = 1;
        s->counter = 0;
        grAnime_801C7A04(gobj, s->joint0, 7, grIm_804DB5B4);
        grAnime_801C7B24(gobj, s->joint0, 7, grIm_804DB574);
        grAnime_801C78FC(gobj, s->joint0, 7);
        if (s->joint1 != -1) {
            grAnime_801C7A04(gobj, s->joint1, 7, grIm_804DB5B4);
            grAnime_801C7B24(gobj, s->joint1, 7, grIm_804DB574);
            grAnime_801C78FC(gobj, s->joint1, 7);
        }
    }
    grIceMt_801FA7F0(gp, arg1, arg2, arg3, arg4, arg8);
}

void fn_801F9558(Ground* gp, int arg1, CollData* arg2, s32 arg3,
                 mpLib_GroundEnum arg4, float arg8)
{
    HSD_GObj* gobj;
    GrIceMtAnim* s = (GrIceMtAnim*) ((u8*) gp + 0x108);
    PAD_STACK(8);
    if ((s32) arg2->x34_flags.b1234 == 1 && s->active == 0) {
        gobj = Ground_801C2BA4(4);
        s->active = 1;
        s->counter = 0;
        grAnime_801C7A04(gobj, s->joint0, 7, grIm_804DB5B4);
        grAnime_801C7B24(gobj, s->joint0, 7, grIm_804DB574);
        grAnime_801C78FC(gobj, s->joint0, 7);
        if (s->joint1 != -1) {
            grAnime_801C7A04(gobj, s->joint1, 7, grIm_804DB5B4);
            grAnime_801C7B24(gobj, s->joint1, 7, grIm_804DB574);
            grAnime_801C78FC(gobj, s->joint1, 7);
        }
    }
    grIceMt_801FA7F0(gp, arg1, arg2, arg3, arg4, arg8);
}

void grIceMt_801F9668(float arg8)
{
    HSD_GObj* gobj;
    Ground* gp;

    gobj = Ground_801C2BA4(8);
    if (gobj == NULL) {
        __assert(grIm_803E46F8, 0xA37, "bg_gobj");
    }
    gp = GET_GROUND(gobj);
    if (gp == NULL) {
        __assert(grIm_803E46F8, 0xA38, "bg_gp");
    }

    gp->gv.icemt2.xC4 = arg8;
}

float grIceMt_801F96E0(HSD_GObj* arg0, float farg0)
{
    s16* p = (s16*) arg0;
    HSD_GObj* mgobj;

    if (p[0] != -1) {
        mgobj = Ground_801C2BA4(p[0]);
        if (mgobj == NULL) {
            __assert(grIm_803E46F8, 0xA45, "mgobj");
        }
        if (mgobj->hsd_obj == NULL) {
            __assert(grIm_803E46F8, 0xA46, "jobj");
        }
        HSD_JObjAddTranslationY(mgobj->hsd_obj, farg0);
    }
    if (p[1] != -1) {
        mgobj = Ground_801C2BA4(p[1]);
        if (mgobj == NULL) {
            __assert(grIm_803E46F8, 0xA4B, "mgobj");
        }
        if (mgobj->hsd_obj == NULL) {
            __assert(grIm_803E46F8, 0xA4C, "jobj");
        }
        HSD_JObjAddTranslationY(mgobj->hsd_obj, farg0);
    }
}

/// #grIceMt_801F98A8
/// @note Checks bit 6 of icemt2.xC4 (as byte) - clears it and does cleanup.
void grIceMt_801F98A8(Ground_GObj* param1)
{
    Ground* gp = param1->user_data;
    HSD_JObj** ptrs = &gp->gv.icemt2.xC8;
    PAD_STACK(8);

    if (((UnkFlagStruct*) &gp->gv.icemt2.xC4)->b1) {
        ((UnkFlagStruct*) &gp->gv.icemt2.xC4)->b1 = 0;
        if (ptrs[0]) {
            Ground_801C2D0C(0, ptrs[0]);
        }
        if (ptrs[1]) {
            Ground_801C2D0C(1, ptrs[1]);
        }
        if (ptrs[2]) {
            Ground_801C2D0C(2, ptrs[2]);
        }
        if (ptrs[3]) {
            Ground_801C2D0C(3, ptrs[3]);
        }
    }
}

f32 grIceMt_801F993C(s32 arg0, s32 arg1)
{
    f32 t = Ground_801C0498();
    u32 upper_ix;
    u32 under_ix;

    for (upper_ix = 0; upper_ix < ICEMT_FIELD_MAX; upper_ix++) {
        if (arg0 == grIm_803E4068[upper_ix].id) {
            break;
        }
    }
    HSD_ASSERTMSG(0xA9D, upper_ix < ICEMT_FIELD_MAX, "upper_ix<ICEMT_FIELD_MAX");

    for (under_ix = 0; under_ix < ICEMT_FIELD_MAX; under_ix++) {
        if (arg1 == grIm_803E4068[under_ix].id) {
            break;
        }
    }
    HSD_ASSERTMSG(0xAA2, under_ix < ICEMT_FIELD_MAX, "under_ix<ICEMT_FIELD_MAX");

    return -((t * grIm_803E4068[upper_ix].x8) -
             (t * grIm_803E4068[under_ix].x4 + grIm_804D69F4->x40));
}

void grIceMt_801F9ACC(Ground_GObj* gobj, float y, GrIceMtSegmentLookup ev,
                      Ground_GObj* arg3)
{
    HSD_GObj* jobj;
    double dVar3;
    double dVar4;
    dVar4 = 0.3;

    jobj = Ground_801C2BA4(4);
    if (jobj == NULL) {
        __assert(grIm_803E46F8, 2629, "mgobj");
    }
    HSD_JObjGetTranslationY(jobj->hsd_obj);
    dVar4 = Ground_801C0498();
    HSD_JObjSetTranslateY(jobj->hsd_obj, y);
    Ground_801C32AC(4);
    Ground_801C32AC(4);
    Ground_801C32AC(4);

    HSD_JObjSetTranslateY(jobj->hsd_obj, y);
    grIceMt_801FA854();
}

/// #grIceMt_801FA0BC

typedef struct grIceMt_FA364_State {
    /* 0x0 */ s16 phase;
    /* 0x2 */ s16 delay;
    /* 0x4 */ s16 lerp_count;
    /* 0x6 */ s16 burst_count;
    /* 0x8 */ s16 idx;
    /* 0xA */ s16 pad;
    /* 0xC */ f32 cur;
} grIceMt_FA364_State;

bool grIceMt_801FA364(void* state_, f32* out, HSD_GObjEvent cb_,
                      Ground_GObj* gobj)
{
    grIceMt_FA364_State* state = state_;
    s32 (*cb)(HSD_GObj*, s32*) = (s32(*)(HSD_GObj*, s32*)) cb_;
    bool ret = true;
    f32 result;
    s32 next_delay;
    s16 tmp;

    switch (state->phase) {
    case 0:
        tmp = state->delay;
        state->delay = tmp - 1;
        if (tmp < 0) {
            state->idx = cb((HSD_GObj*) gobj, &next_delay);
            state->delay = (s16) next_delay;
            state->phase = 1;
            state->lerp_count = ((s16*) grIm_804D69F4)[0x34 / 2];
        }
        break;
    case 1:
        state->lerp_count = state->lerp_count - 1;
        tmp = state->lerp_count;
        if (tmp != 0) {
            state->cur +=
                (((f32*) ((u8*) grIm_804D69F4 + 4))[state->idx] - state->cur) /
                (f32) tmp;
            ret = false;
        } else {
            state->phase = 0;
            state->cur = ((f32*) ((u8*) grIm_804D69F4 + 4))[state->idx];
        }
        break;
    }

    result = state->cur;
    if (state->burst_count != 0) {
        result = grIm_804D69F4->x3C * Ground_801C0498();
        state->burst_count--;
    }
    *out = result;
    return ret;
}

int fn_801FA4CC(int num)
{ // https://decomp.me/scratch/pSJNA
    if (num == 1) {
        Ground_801C5740(num);
        num = 1;
    } else {
        num = 0;
    }
    return num;
}

int grIceMt_801FA500(HSD_GObj* arg0, HSD_JObj* arg1)
{
    s32 count = 0;
    HSD_JObj* node;

    node = arg0->hsd_obj;
    if (node == NULL) {
        __assert(grIm_803E46F8, 0xBB1, "jobj");
    }
    node = HSD_JObjGetChild(node);
    if (node == NULL) {
        __assert(grIm_803E46F8, 0xBB2, "jobj");
    }

    while (node != NULL) {
        if (node == arg1) {
            break;
        }
        if (!(node->flags & 0x1000) && HSD_JObjGetChild(node) != NULL) {
            node = HSD_JObjGetChild(node);
        } else if (HSD_JObjGetNext(node) != NULL) {
            node = HSD_JObjGetNext(node);
        } else {
            while (HSD_JObjGetParent(node) != NULL &&
                   HSD_JObjGetNext(HSD_JObjGetParent(node)) == NULL)
            {
                node = HSD_JObjGetParent(node);
            }
            node = HSD_JObjGetNext(HSD_JObjGetParent(node));
        }
        count++;
    }
    if (node != NULL) {
        return count;
    }
    return -1;
}

/// #grIceMt_801FA6D8
void grIceMt_801FA6D8(HSD_GObj* param1)
{
    HSD_GObj* gobj;
    Ground* gp;

    if (Stage_80225194() == 0x4C) {
        gobj = Ground_801C2BA4(0xA);
        if (gobj != NULL) {
            gp = gobj->user_data;
            if (gp != NULL) {
                gp->gv.icemt.xCE = grIm_804D69F4->x3A;
            }
        }
    }
}

/// extern f32 grIm_804DB574;

void grIceMt_801FA728(Vec3* arg0)
{
    HSD_GObj* temp_r3;
    HSD_GObj* temp_r3_3;
    Ground* temp_r3_2;
    Ground* temp_r3_4;

    if (Stage_80225194() == 0x4C) {
        temp_r3 = Ground_801C2BA4(10);
        if (temp_r3 != NULL) {
            temp_r3_2 = temp_r3->user_data;
            if (temp_r3_2 != NULL) {
                arg0->x = 0;
                arg0->y = -temp_r3_2->gv.icemt.xD4;
                arg0->z = 0;
                return;
            }
        }
        arg0->z = 0;
        arg0->y = 0;
        arg0->x = 0;
        return;
    }
    temp_r3_3 = Ground_801C2BA4(9);
    if (temp_r3_3 != NULL) {
        temp_r3_4 = temp_r3_3->user_data;
        if (temp_r3_4 != NULL) {
            arg0->x = 0;
            arg0->y = -temp_r3_4->gv.icemt.xD4;
            arg0->z = 0;
            return;
        }
    }
    arg0->z = 0;
    arg0->y = 0;
    arg0->x = 0;
}

/// #grIceMt_801FA7F0
void grIceMt_801FA7F0(Ground* gp, s32 arg1, CollData* arg2, s32 arg3,
                      mpLib_GroundEnum arg4, float arg8)
{
    HSD_GObj* gobj;
    Ground* gp2;
    PAD_STACK(8);
    if (Ground_801C57A4() == arg2->x0_gobj) {
        gobj = Ground_801C2BA4(0xA);
        if (gobj != NULL) {
            gp2 = gobj->user_data;
            if (gp2 != NULL) {
                ((UnkFlagStruct*) &gp2->gv.icemt.xD8)->b4 = 1;
            }
        }
    }
}

/// #grIceMt_801FA854
void grIceMt_801FA854(void)
{
    HSD_GObj* gobj = Ground_801C2BA4(0);
    HSD_JObj* jobj;

    if (gobj) {
        jobj = Ground_801C3FA4(gobj, 0x12);
        if (jobj) {
            Ground_801C2D0C(4, jobj);
        }
        jobj = Ground_801C3FA4(gobj, 0x13);
        if (jobj) {
            Ground_801C2D0C(5, jobj);
        }
        jobj = Ground_801C3FA4(gobj, 0x14);
        if (jobj) {
            Ground_801C2D0C(6, jobj);
        }
        jobj = Ground_801C3FA4(gobj, 0x15);
        if (jobj) {
            Ground_801C2D0C(7, jobj);
        }
    }
    return;
}

DynamicsDesc* grIceMt_801FA8F8(enum_t id)
{
    return 0;
}

bool grIceMt_801FA900(Vec3* a, int id, HSD_JObj* jobj)
{
    return true;
}
