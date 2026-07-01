#include "gr/gricemt.h"

#include <placeholder.h>
#include <platform.h>

#include "baselib/debug.h"

#include "baselib/forward.h"

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
/* 1F91EC */ static void grIceMt_801F91EC(HSD_GObj* param_1, s16* param_2,
                                          int param_3, int param_4,
                                          int param_5, int param_6,
                                          int param_7, mpLib_Callback param_8);

static const Vec3 grIm_803B8220[] = {
    { 0.0, 0.0, 0.0 },    { -8.0, 15.0, 0.0 }, { 8.0, 15.0, 0.0 },
    { -24.0, 15.0, 0.0 }, { 24.0, 15.0, 0.0 },
};

IceMountainParams* grIm_804D69F4;
HSD_GObj* grIm_804D69F0;
HSD_GObj* grIm_804D69EC;
HSD_GObj* grIm_804D69E8;

typedef struct GrIm825C {
    struct {
        u16 x0;
        u16 x2;
        u16 x4;
        u16 x6;
    } hi;
    u16 x8;
} GrIm825C;
const GrIm825C grIm_803B825C = { { 1, 2, 3, 4 }, 5 };

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
    { 0, 1, 0 },   { 1, 1, 0 },   { 2, 1, 0 },   { 3, 1, 0 },   { 4, 1, 0 },
    { 5, 1, 0 },   { 6, 1, 0 },   { 7, 1, 0 },   { 10, 1, 0 },  { 11, 1, 0 },
    { 12, 1, 0 },  { 13, 1, 0 },  { 14, 1, 0 },  { 15, 1, 0 },  { 16, 1, 0 },
    { 17, 1, 0 },  { 18, 1, 0 },  { 19, 1, 0 },  { 20, 1, 0 },  { 21, 1, 0 },
    { 22, 1, 0 },  { 23, 1, 0 },  { 24, 1, 0 },  { 25, 1, 0 },  { 26, 1, 0 },
    { 27, 1, 0 },  { 28, 1, 0 },  { 29, 1, 0 },  { 30, 1, 0 },  { 31, 1, 0 },
    { 32, 2, 0 },  { 33, 2, 0 },  { 36, 2, 3 },  { 39, 2, 0 },  { 40, 2, 0 },
    { 41, 2, 0 },  { 42, 2, 0 },  { 43, 2, 0 },  { 44, 2, 0 },  { 45, 2, 0 },
    { 46, 2, 0 },  { 47, 2, 0 },  { 48, 2, 0 },  { 49, 2, 0 },  { 50, 2, 0 },
    { 51, 2, 0 },  { 52, 2, 0 },  { 53, 2, 0 },  { 54, 2, 0 },  { 55, 2, 0 },
    { 56, 2, 0 },  { 57, 2, 0 },  { 58, 2, 0 },  { 59, 2, 0 },  { 60, 2, 0 },
    { 61, 2, 0 },  { 62, 2, 0 },  { 63, 2, 0 },  { 64, 2, 0 },  { 65, 2, 0 },
    { 66, 2, 0 },  { 67, 3, 0 },  { 68, 3, 0 },  { 69, 3, 0 },  { 74, 3, 0 },
    { 75, 3, 0 },  { 76, 3, 0 },  { 77, 3, 0 },  { 78, 3, 0 },  { 79, 3, 0 },
    { 80, 3, 0 },  { 81, 3, 0 },  { 82, 3, 0 },  { 83, 3, 0 },  { 84, 3, 0 },
    { 85, 3, 0 },  { 86, 3, 0 },  { 87, 3, 0 },  { 88, 3, 0 },  { 89, 3, 0 },
    { 90, 3, 0 },  { 91, 3, 0 },  { 92, 3, 0 },  { 93, 3, 0 },  { 94, 3, 0 },
    { 95, 3, 0 },  { 96, 3, 0 },  { 97, 3, 0 },  { 98, 3, 0 },  { 99, 3, 0 },
    { 100, 3, 0 }, { 101, 3, 0 }, { 102, 4, 0 }, { 103, 4, 0 }, { 104, 4, 0 },
    { 105, 4, 0 }, { 106, 4, 0 }, { 107, 4, 0 }, { 108, 4, 0 }, { 109, 4, 0 },
    { 110, 4, 0 }, { 111, 4, 0 }, { 113, 4, 2 }, { 114, 4, 3 }, { 115, 4, 4 },
    { 118, 4, 0 }, { 119, 4, 0 }, { 120, 4, 0 }, { 121, 4, 0 }, { 122, 4, 0 },
    { 123, 4, 0 }, { 124, 4, 0 }, { 125, 4, 0 }, { 126, 4, 0 }, { 127, 4, 0 },
    { 128, 4, 0 }, { 129, 4, 0 }, { 130, 4, 0 }, { 131, 4, 0 }, { 132, 4, 0 },
    { 133, 4, 0 }, { 134, 4, 0 }, { 135, 4, 0 }, { 136, 4, 0 }, { 137, 4, 0 },
    { 138, 4, 0 }, { 139, 4, 0 }, { 140, 4, 0 }, { 141, 4, 0 }, { 142, 4, 0 },
    { 143, 5, 0 }, { 144, 5, 0 }, { 145, 5, 0 }, { 146, 5, 0 }, { 152, 5, 0 },
    { 153, 5, 0 }, { 154, 5, 0 }, { 155, 5, 0 }, { 156, 5, 0 }, { 157, 5, 0 },
    { 158, 5, 0 }, { 159, 5, 0 }, { 160, 5, 0 }, { 161, 5, 0 }, { 162, 5, 0 },
    { 163, 5, 0 }, { 164, 5, 0 }, { 165, 5, 0 }, { 166, 5, 0 }, { 167, 5, 0 },
    { 168, 5, 0 }, { 169, 5, 0 }, { 170, 5, 0 }, { 171, 5, 0 }, { 172, 5, 0 },
    { 173, 5, 0 }, { 174, 5, 0 }, { 175, 5, 0 }, { 176, 5, 0 }, { 177, 5, 0 },
    { 178, 5, 0 }, { 179, 5, 0 }, { 180, 6, 0 }, { 181, 6, 0 }, { 182, 6, 0 },
    { 183, 6, 0 }, { 184, 6, 0 }, { 189, 6, 0 }, { 190, 6, 0 }, { 191, 6, 0 },
    { 192, 6, 0 }, { 193, 6, 0 }, { 194, 6, 0 }, { 195, 6, 0 }, { 196, 6, 0 },
    { 197, 6, 0 }, { 198, 6, 0 }, { 199, 6, 0 }, { 200, 6, 0 }, { 201, 6, 0 },
    { 202, 6, 0 }, { 203, 6, 0 }, { 204, 6, 0 }, { 205, 6, 0 }, { 206, 6, 0 },
    { 207, 6, 0 }, { 208, 6, 0 }, { 209, 6, 0 }, { 210, 6, 0 }, { 211, 6, 0 },
    { 212, 6, 0 }, { 213, 6, 0 }, { 214, 6, 0 }, { 215, 6, 0 }, { 216, 6, 0 },
};

s16 grIm_803E4544[] = {
    0,   1,   2,   3,   4,   5,   6,   7,   8,   9,   10,  11,  12,  13,  14,
    15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,
    30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,
    45,  46,  47,  48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  58,  59,
    60,  61,  62,  63,  64,  65,  66,  67,  68,  69,  70,  71,  72,  73,  74,
    75,  76,  77,  78,  79,  80,  81,  82,  83,  84,  85,  86,  87,  88,  89,
    90,  91,  92,  93,  94,  95,  96,  97,  98,  99,  100, 101, 102, 103, 104,
    105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119,
    120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134,
    135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149,
    150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164,
    165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179,
    180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194,
    195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209,
    210, 211, 212, 213, 214, 215, 216,
};

static void order_sdata2(void)
{
    (void) -20.0f;
    (void) 0.0f;
    (void) 0.5f;
    (void) S32_TO_F32;
}

static void order_data0(void)
{
    (void) __FILE__;
    (void) "i<ICEMT_FIELD_MAX";
}

StageCallbacks grIm_803E4718[] = {
    { grIceMt_801F72D4, grIceMt_801F75DC, grIceMt_801F75E4, grIceMt_801F75E8,
      0 },
    { grIceMt_801F7D94, grIceMt_801F7EE0, grIceMt_801F7EE8, grIceMt_801F7F1C,
      0 },
    { grIceMt_801F7F70, grIceMt_801F8154, grIceMt_801F815C, grIceMt_801F81B4,
      0 },
    { grIceMt_801F8208, grIceMt_801F835C, grIceMt_801F8364, grIceMt_801F8398,
      0 },
    { grIceMt_801F83EC, grIceMt_801F85BC, grIceMt_801F85C4, grIceMt_801F8608,
      0 },
    { grIceMt_801F865C, grIceMt_801F87C0, grIceMt_801F87C8, grIceMt_801F87FC,
      0 },
    { grIceMt_801F8850, grIceMt_801F89A4, grIceMt_801F89AC, grIceMt_801F89E0,
      0 },
    { 0, 0, 0, 0, 0 },
    { grIceMt_801F8A34, grIceMt_801F8B08, grIceMt_801F8B10, grIceMt_801F8C60,
      0xC0000000 },
    { grIceMt_801F75FC, grIceMt_801F7720, grIceMt_801F7728, grIceMt_801F77AC,
      0 },
    { grIceMt_801F785C, grIceMt_801F796C, grIceMt_801F7A2C, grIceMt_801F7D90,
      0 },
};

StageData grIm_803E4800 = {
    ICEMTN,
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
    195,
};

typedef struct GrIm588 {
    s16 a;
    s16 b;
} GrIm588;

static const GrIm588 grIm_804DB588 = { 1, 2 };
static const GrIm588 grIm_804DB58C = { 1, 2 };
static const GrIm588 grIm_804DB590 = { 1, 2 };
static const GrIm588 grIm_804DB594 = { 3, 4 };
static const GrIm588 grIm_804DB598 = { 1, 2 };
static const GrIm588 grIm_804DB59C = { 3, 4 };
static const GrIm588 grIm_804DB5A0 = { 1, 2 };
static const GrIm588 grIm_804DB5A4 = { 3, 4 };

void grIceMt_801F6868(bool id) {}

#define ICEMT_FIELD_MAX 6
#define BLOCK_COLL_JOBJ_MAX 20

void grIceMt_801F686C(void)
{
    s32 field30;
    s32 field29;
    s32 field28;
    u32 i;
    s16* xAC;
    s32 id;
    f32 y_pos;
    f32 y_pos2;
    f32 y_pos3;
    f32 y_pos4;
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    PAD_STACK(0x10);

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
        for (i = 0; i < ICEMT_FIELD_MAX; i++) {
            xAC = grIm_804D69F4->xAC;
            id = grIm_803E4068[i].id;
            if (xAC[0] == id) {
                continue;
            }
            if (xAC[1] == id) {
                continue;
            }
            field30 = grIm_803E4068[i].id;
            break;
        }
        HSD_ASSERT(600, i<ICEMT_FIELD_MAX);

        for (i = 0; i < ICEMT_FIELD_MAX; i++) {
            xAC = grIm_804D69F4->xAC;
            id = grIm_803E4068[i].id;
            if (xAC[0] == id) {
                continue;
            }
            if (xAC[1] == id) {
                continue;
            }
            if (field30 == id) {
                continue;
            }
            field29 = grIm_803E4068[i].id;
            break;
        }
        HSD_ASSERT(609, i<ICEMT_FIELD_MAX);

        for (i = 0; i < ICEMT_FIELD_MAX; i++) {
            xAC = grIm_804D69F4->xAC;
            id = grIm_803E4068[i].id;
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
            field28 = grIm_803E4068[i].id;
            break;
        }
        HSD_ASSERT(619, i<ICEMT_FIELD_MAX);

        y_pos = Ground_801C0498();
        y_pos = grIm_804DB570 * y_pos;
        y_pos =
            y_pos + grIceMt_801F993C(grIm_803E4068[grIm_804D69F4->xAC[0]].id,
                                     grIm_803E4068[grIm_804D69F4->xAC[1]].id);
        y_pos2 =
            y_pos + grIceMt_801F993C(grIm_803E4068[grIm_804D69F4->xAC[1]].id,
                                     grIm_803E4068[field30].id);
        y_pos3 = y_pos2 + grIceMt_801F993C(grIm_803E4068[field30].id,
                                           grIm_803E4068[field29].id);
        y_pos4 = y_pos3 + grIceMt_801F993C(grIm_803E4068[field29].id,
                                           grIm_803E4068[field28].id);

        gobj = grIceMt_801F71E8(grIm_803E4068[grIm_804D69F4->xAC[2]].id);
        HSD_ASSERT(636, gobj);
        jobj = gobj->hsd_obj;
        HSD_ASSERT(637, jobj);
        HSD_JObjSetTranslateY(jobj, y_pos2);
        grIm_804D69E8 = gobj;

        gobj = grIceMt_801F71E8(grIm_803E4068[grIm_804D69F4->xAC[3]].id);
        HSD_ASSERT(641, gobj);
        jobj = gobj->hsd_obj;
        HSD_ASSERT(642, jobj);
        HSD_JObjSetTranslateY(jobj, y_pos3);
        grIm_804D69EC = gobj;

        gobj = grIceMt_801F71E8(grIm_803E4068[grIm_804D69F4->xAC[4]].id);
        HSD_ASSERT(646, gobj);
        jobj = gobj->hsd_obj;
        HSD_ASSERT(647, jobj);
        HSD_JObjSetTranslateY(jobj, y_pos4);
        grIm_804D69F0 = gobj;

        grIceMt_801F71E8(10);
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

#pragma auto_inline off
HSD_GObj* grIceMt_801F71E8(int gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grIm_803E4718[gobj_id];

    gobj = Ground_GetStageGObj(gobj_id);

    if (gobj != NULL) {
        Ground_SetupStageCallbacks(gobj, callbacks);
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", __FILE__, 860, gobj_id);
    }

    return gobj;
}

static void order_data1(void)
{
    (void) "block_num<=BLOCK_COLL_JOBJ_MAX";
    (void) "coll_jobj";
    (void) "block_jobj";
}

void grIceMt_801F72D4(Ground_GObj* arg0)
{
    Vec3 v1;
    Vec3 v2;
    Vec3 v3;
    Vec3 v4;
    HSD_JObj* jobj;
    Ground* gp = GET_GROUND(arg0);
    grAnime_801C8138(arg0, gp->map_id, 0);
    jobj = Ground_801C3FA4(arg0, 18);
    if (jobj != 0) {
        v1 = grIm_803B8220[1];
        HSD_JObjSetTranslate(jobj, &v1);
    }
    jobj = Ground_801C3FA4(arg0, 19);
    if (jobj != 0) {
        v2 = grIm_803B8220[2];
        HSD_JObjSetTranslate(jobj, &v2);
    }
    jobj = Ground_801C3FA4(arg0, 20);
    if (jobj != 0) {
        v3 = grIm_803B8220[3];
        HSD_JObjSetTranslate(jobj, &v3);
    }
    jobj = Ground_801C3FA4(arg0, 21);
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

    /// @todo @c sizeof surrounding struct
    memzero(&gp->gv.icemt.xDC, 24);

    /// @todo @c sizeof surrounding struct
    memzero(&gp->gv.icemt.xF4, 20);

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
        grIceMt_801FA364(&gp->gv.icemt.xC8, &y,
                         (HSD_GObjEvent) (Event) fn_801F8E58, gobj);
        grIceMt_801F9ACC((HSD_GObj*) &gp->gv.icemt.xC4,
                         grIceMt_801F96E0(&gp->gv.icemt, -y), fn_801F9038,
                         gobj);
        grIceMt_801F9668(y);
    }
}

void grIceMt_801F77AC(Ground_GObj* arg0) {}

/// #fn_801F77B0
void fn_801F77B0(HSD_GObj* arg0)
{
    Ground* gp = GET_GROUND(arg0);
    u32 i;
    mpLib_Callback cb;
    Ground* gp_out;

    ((UnkFlagStruct*) &gp->gv.icemt.xD8)->b0 = 0;

    for (i = 0; i < 217; i++) {
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
    gp->gv.icemt.xE4 = 0.0f;
    gp->gv.icemt.xC8 = 0;
    gp->gv.icemt.xCE = 0;
    gp->gv.icemt.xCA = 0;
    gp->gv.icemt.xCC = 0;
    gp->gv.icemt.xD0 = -1;
    gp->gv.icemt.xD4 = 0.0f;

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
        HSD_ASSERT(1141, mgobj);
        Ground_801C4A08(mgobj);
    }
    if (gp->gv.icemt.xC6 != -1) {
        mgobj = Ground_801C2BA4(gp->gv.icemt.xC6);
        HSD_ASSERT(1146, mgobj);
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
        var_r30 = grIceMt_801FA364(&gp->gv.icemt.xC8, &sp30,
                                   (HSD_GObjEvent) (Event) fn_801F9150, arg0);
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
            if (gp->gv.icemt.xE4 < 0.0f) {
                gp->gv.icemt.xE4 = 0.0f;
            }
        }
        sp30 += gp->gv.icemt.xE4;
    } else {
        mgobj = Ground_801C2BA4(gp->gv.icemt.xC6);
        HSD_ASSERT(0x4C3, mgobj);
        jobj = mgobj->hsd_obj;
        HSD_ASSERT(0x4C5, jobj);
        dist = HSD_JObjGetTranslationY(jobj) -
               (f32) ((s16*) grIm_804D69F4)[0xA8 / 2];
        if (dist < 0.0f) {
            gp->gv.icemt.xD4 = 0.0f;
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
                     grIceMt_801F96E0(&gp->gv.icemt, -sp30), fn_801F91A8,
                     arg0);
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
            gm_801674C4(14, 2, 2, 0, fn_801FA4CC);
            grZakoGenerator_801CAF08();
        }
    } else {
        r = Ground_801C5764();
        switch (r) {
        case 2:
            break;
        case 1:
            Ground_801C1D6C(16);
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
    PAD_STACK(0x4);
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
    grIceMt_801F8CDC(arg0, (s16*) &sp14, 2, gp->gv.icemt2.xF8);
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
        if (gp->gv.icemt2.xF8[i] != NULL) {
            grMaterial_801C8CDC(gp->gv.icemt2.xF8[i]);
        }
    }
}

void grIceMt_801F7F70(Ground_GObj* arg0)
{
    Ground* gp = GET_GROUND(arg0);
    HSD_JObj* jobj;
    HSD_JObj* jobj2;
    GrIm588 sp14;
    PAD_STACK(0x4);
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
    ((UnkFlagStruct*) &gp->gv.icemt2.xC4)->b0 = 0;
    sp14 = grIm_804DB58C;
    grIceMt_801F8CDC(arg0, (s16*) &sp14, 2, &gp->gv.icemt2.xF8[0]);
    grIceMt_801F91EC(arg0, (s16*) ((u8*) gp + 0x100),
                     grIceMt_801FA500(arg0, jobj), -1, 0x25, 0x109, 0x27E,
                     (mpLib_Callback) fn_801F9338);
    grIceMt_801F91EC(arg0, &gp->gv.icemt.x108[3],
                     grIceMt_801FA500(arg0, jobj2), -1, 0x26, 0x109, 0x27E,
                     (mpLib_Callback) fn_801F9448);
}

bool grIceMt_801F8154(Ground_GObj* param1)
{
    return false;
}

void grIceMt_801F815C(Ground_GObj* param1)
{
    Ground* gp = GET_GROUND(param1);
    grIceMt_801F929C(param1, &gp->gv.icemt2.xF8[2]);
    grIceMt_801F929C(param1, &gp->gv.icemt.x108[3]);
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
        if (gp->gv.icemt2.xF8[i] != NULL) {
            grMaterial_801C8CDC(gp->gv.icemt2.xF8[i]);
        }
    }
}

void grIceMt_801F8208(Ground_GObj* arg0)
{
    Ground* gp = GET_GROUND(arg0);
    struct {
        GrIm588 x0;
        GrIm588 x4;
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
    grIceMt_801F8CDC(arg0, (s16*) &sp14, 4, &gp->gv.icemt2.xF8[0]);
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
        if (gp->gv.icemt2.xF8[i] != NULL) {
            grMaterial_801C8CDC(gp->gv.icemt2.xF8[i]);
        }
        i++;
    }
}

void grIceMt_801F83EC(Ground_GObj* arg0)
{
    HSD_JObj* jobj3;
    Ground* gp = GET_GROUND(arg0);
    HSD_JObj* jobj = arg0->hsd_obj;
    HSD_JObj* jobj2;
    s32 r;
    struct {
        GrIm588 x0;
        GrIm588 x4;
    } sp14;
    PAD_STACK(0x4);
    Ground_801C0498();
    Ground_801C2ED0(jobj, gp->map_id);
    grAnime_801C8138(arg0, gp->map_id, 0);
    grAnime_801C77FC(arg0, 0, 7);
    jobj2 = Ground_801C3FA4(arg0, 7);
    jobj3 = Ground_801C3FA4(arg0, 5);
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
    grIceMt_801F8CDC(arg0, (s16*) &sp14, 4, &gp->gv.icemt2.xF8[0]);
    r = grIceMt_801FA500(arg0, jobj3);
    grIceMt_801F91EC(arg0, gp->gv.icemt.x108, grIceMt_801FA500(arg0, jobj2), r,
                     0x75, 0x109, 0x27E, (mpLib_Callback) fn_801F9558);
}

bool grIceMt_801F85BC(Ground_GObj* param1)
{
    return false;
}

void grIceMt_801F85C4(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    grIceMt_801F929C(gobj, &gp->gv.icemt2.xF8[4]);
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
        if (gp->gv.icemt2.xF8[i] != NULL) {
            grMaterial_801C8CDC(gp->gv.icemt2.xF8[i]);
        }
    }
}

void grIceMt_801F865C(Ground_GObj* arg0)
{
    Ground* gp = GET_GROUND(arg0);
    GrIm825C sp14;
    PAD_STACK(0x4);
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
    grIceMt_801F8CDC(arg0, (s16*) &sp14, 5, &gp->gv.icemt2.xF8[0]);
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
/// Destroys HSD_GObj* stored in icemt2.xF8[0-4].
void grIceMt_801F87FC(Ground_GObj* gobj)
{
    u32 unused[2];
    int i;
    Ground* gp = gobj->user_data;
    for (i = 0; i < 5; i++) {
        if (gp->gv.icemt2.xF8[i] != NULL) {
            grMaterial_801C8CDC(gp->gv.icemt2.xF8[i]);
        }
    }
}

void grIceMt_801F8850(Ground_GObj* arg0)
{
    Ground* gp = GET_GROUND(arg0);
    struct {
        GrIm588 x0;
        GrIm588 x4;
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
    grIceMt_801F8CDC(arg0, (s16*) &sp14, 4, &gp->gv.icemt2.xF8[0]);
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
        if (gp->gv.icemt2.xF8[i] != NULL) {
            grMaterial_801C8CDC(gp->gv.icemt2.xF8[i]);
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
    mul = 0.3f * gp->gv.icemt2.xC4;
    jobj = Ground_801C3FA4(arg0, 8);
    HSD_ASSERT(1935, jobj);
    cur = HSD_JObjGetTranslationY(jobj);
    cur = cur - mul;
    if (cur > 0.5f * (3500.0f * Ground_801C0498())) {
        cur = -(3500.0f * Ground_801C0498() - cur);
    } else if (cur < 0.5f * -(3500.0f * Ground_801C0498())) {
        cur += 3500.0f * Ground_801C0498();
    }
    HSD_JObjSetTranslateY(jobj, cur);
}

void grIceMt_801F8C60(Ground_GObj* arg0) {}

void fn_801F8C64(Item_GObj* gobj, Ground* u1, Vec3* u2, HSD_GObj* u3, f32 u4)
{
    Vec3 pos;
    Item* it = GET_ITEM(gobj);
    grMaterial_801C8E28(gobj);

    HSD_JObjSetFlagsAll(it->xDD4_itemVar.mato.x4, JOBJ_HIDDEN);
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
void grIceMt_801F8CDC(Ground_GObj* gobj, s16* joint_indices, int block_num,
                      HSD_GObj** output_array)
{
    PAD_STACK(4 * 4);
    {
        Ground* gp = GET_GROUND(gobj);
        int i;
        void* jobj_desc;
        HSD_JObj* parent_jobjs[20];
        HSD_JObj* coll_jobj;
        HSD_JObj* block_jobj;
        Item_GObj* item;
        UnkArchiveStruct* archive;

        archive = grDatFiles_801C6324();
        jobj_desc = archive->unk4->unk8[7].unk0;

        HSD_ASSERT(2004, block_num<=BLOCK_COLL_JOBJ_MAX);

        for (i = 0; i < block_num; i++) {
            parent_jobjs[i] = Ground_801C3FA4(gobj, joint_indices[i]);
        }

        for (i = 0; i < block_num; i++) {
            coll_jobj = parent_jobjs[i];
            HSD_ASSERT(0x7E3, coll_jobj);

            block_jobj = HSD_JObjLoadJoint(jobj_desc);
            HSD_ASSERT(0x7E6, block_jobj);

            HSD_JObjAddChild(coll_jobj, block_jobj);

            item = grMaterial_801C8CFC(8, 0, gp, coll_jobj, NULL, fn_801F8C64,
                                       NULL);
            if (item != NULL) {
                grMaterial_801C8DE0(item, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
                                    6.0f);
                grMaterial_801C8E08(item);
                grMaterial_801C8E68(item, 0);
            }
            output_array[i] = item;
        }
    }
}

s32 fn_801F8E58(Ground_GObj* arg0, s32* out)
{
    Ground* g;
    s32* p;
    s32 list[12];
    s32 i;
    s32 pick;
    s32 chosen;
    Ground* gp;
    s16 a;
    s16 b;
    s32 d;

    s32 max = 0;
    gp = arg0->user_data;

    {
        g = gp;
        p = &list[max];
        for (i = 0; i < 12; i++) {
            if (g->gv.icemt.xDC == 0 && (Stage_80225194() != 0xD4 || i >= 4)) {
                *p = i;
                p++;
                max++;
            }
            g = (Ground*) ((u8*) g + 2);
        }
    }

    HSD_ASSERT(0x81D, max);
    pick = max != 0 ? HSD_Randi(max) : 0;
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

    (&gp->gv.icemt.xDC)[chosen] = *(s16*) ((u8*) grIm_804D69F4 + 2);
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
    s32 a;

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

void fn_801F9338(Ground* gp, int arg1, CollData* arg2, s32 arg3,
                 mpLib_GroundEnum arg4, float arg8)
{
    HSD_GObj* gobj;
    s16* s = gp->gv.icemt.x100;
    PAD_STACK(8);
    if ((s32) arg2->x34_flags.b1234 == 1 && s[0] == 0) {
        gobj = Ground_801C2BA4(2);
        s[0] = 1;
        s[1] = 0;
        grAnime_801C7A04(gobj, s[2], 7, 1.0f);
        grAnime_801C7B24(gobj, s[2], 7, 0.0f);
        grAnime_801C78FC(gobj, s[2], 7);
        if (s[3] != -1) {
            grAnime_801C7A04(gobj, s[3], 7, 1.0f);
            grAnime_801C7B24(gobj, s[3], 7, 0.0f);
            grAnime_801C78FC(gobj, s[3], 7);
        }
    }
    grIceMt_801FA7F0(gp, arg1, arg2, arg3, arg4, arg8);
}

void fn_801F9448(Ground* gp, int arg1, CollData* arg2, s32 arg3,
                 mpLib_GroundEnum arg4, float arg8)
{
    HSD_GObj* gobj;
    s16* s = &gp->gv.icemt.x108[3];
    PAD_STACK(8);
    if ((s32) arg2->x34_flags.b1234 == 1 && s[0] == 0) {
        gobj = Ground_801C2BA4(2);
        s[0] = 1;
        s[1] = 0;
        grAnime_801C7A04(gobj, s[2], 7, 1.0f);
        grAnime_801C7B24(gobj, s[2], 7, 0.0f);
        grAnime_801C78FC(gobj, s[2], 7);
        if (s[3] != -1) {
            grAnime_801C7A04(gobj, s[3], 7, 1.0f);
            grAnime_801C7B24(gobj, s[3], 7, 0.0f);
            grAnime_801C78FC(gobj, s[3], 7);
        }
    }
    grIceMt_801FA7F0(gp, arg1, arg2, arg3, arg4, arg8);
}

void fn_801F9558(Ground* gp, int arg1, CollData* arg2, s32 arg3,
                 mpLib_GroundEnum arg4, float arg8)
{
    HSD_GObj* gobj;
    s16* s = gp->gv.icemt.x108;
    PAD_STACK(8);
    if ((s32) arg2->x34_flags.b1234 == 1 && s[0] == 0) {
        gobj = Ground_801C2BA4(4);
        s[0] = 1;
        s[1] = 0;
        grAnime_801C7A04(gobj, s[2], 7, 1.0f);
        grAnime_801C7B24(gobj, s[2], 7, 0.0f);
        grAnime_801C78FC(gobj, s[2], 7);
        if (s[3] != -1) {
            grAnime_801C7A04(gobj, s[3], 7, 1.0f);
            grAnime_801C7B24(gobj, s[3], 7, 0.0f);
            grAnime_801C78FC(gobj, s[3], 7);
        }
    }
    grIceMt_801FA7F0(gp, arg1, arg2, arg3, arg4, arg8);
}

void grIceMt_801F9668(float arg8)
{
    HSD_GObj* bg_gobj;
    Ground* bg_gp;

    bg_gobj = Ground_801C2BA4(8);
    HSD_ASSERT(0xA37, bg_gobj);
    bg_gp = GET_GROUND(bg_gobj);
    HSD_ASSERT(0xA38, bg_gp);

    bg_gp->gv.icemt2.xC4 = arg8;
}

float grIceMt_801F96E0(struct grIceMt_GroundVars* arg0, float farg0)
{
    HSD_GObj* mgobj;
    HSD_JObj* jobj2;
    if (arg0->xC4 != -1) {
        HSD_JObj* jobj;
        mgobj = Ground_801C2BA4(arg0->xC4);
        HSD_ASSERT(2629, mgobj);
        jobj = GET_JOBJ(mgobj);
        HSD_ASSERT(2630, jobj);
        HSD_JObjAddTranslationY(jobj, farg0);
    }
    if (arg0->xC6 != -1) {
        HSD_JObj* jobj;
        mgobj = Ground_801C2BA4(arg0->xC6);
        HSD_ASSERT(2635, mgobj);
        jobj = GET_JOBJ(mgobj);
        jobj2 = jobj;
        HSD_ASSERT(2636, jobj);
        HSD_JObjAddTranslationY(jobj2, farg0);
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
    HSD_ASSERT(2717, upper_ix<ICEMT_FIELD_MAX);

    for (under_ix = 0; under_ix < ICEMT_FIELD_MAX; under_ix++) {
        if (arg1 == grIm_803E4068[under_ix].id) {
            break;
        }
    }
    HSD_ASSERT(0xAA2, under_ix<ICEMT_FIELD_MAX);

    return -((t * grIm_803E4068[upper_ix].x8) -
             (t * grIm_803E4068[under_ix].x4 + grIm_804D69F4->x40));
}

static inline HSD_GObj* grIceMt_801F71E8_inner2(int id)
{
    return grIceMt_801F71E8(id);
}
static inline HSD_GObj* grIceMt_801F71E8_noinline2(int id)
{
    return grIceMt_801F71E8_inner2(id);
}

int grIceMt_801F9ACC(Ground_GObj* gobj, float y, GrIceMtSegmentLookup ev,
                     Ground_GObj* arg3)
{
    s16* seg = (s16*) gobj;
    s32 did = 0;
    HSD_GObj* mgobj;
    HSD_JObj* jobj;
    Ground* gp;
    HSD_JObj** ptrs;
    HSD_JObj** new_var;
    f32 cur;
    f32 f;
    f32 f2;
    s32 id;
    PAD_STACK(16);

    if (seg[0] == -1 || seg[1] == -1) {
        return 0;
    }
    f = grIceMt_801F993C(seg[0], seg[1]);
    mgobj = Ground_801C2BA4(seg[1]);
    HSD_ASSERT(0xAB9, mgobj);
    jobj = mgobj->hsd_obj;
    HSD_ASSERT(0xABA, jobj);
    cur = HSD_JObjGetTranslationY(jobj);
    if (ABS(cur) < 10.0f) {
        gp = GET_GROUND(Ground_801C2BA4(seg[1]));
        ((UnkFlagStruct*) &gp->gv.icemt2.xC4)->b1 = 1;
    } else if (ABS(cur + f) < 10.0f) {
        gp = GET_GROUND(Ground_801C2BA4(seg[0]));
        ((UnkFlagStruct*) &gp->gv.icemt2.xC4)->b1 = 1;
    }
    if (cur < 0.5f * -f) {
        id = seg[0];
        if (id != -1) {
            gp = GET_GROUND(Ground_801C2BA4(id));
            if (!((UnkFlagStruct*) &gp->gv.icemt2.xC4)->b0) {
                ((UnkFlagStruct*) &gp->gv.icemt2.xC4)->b0 = 1;
                ((UnkFlagStruct*) &gp->gv.icemt2.xC4)->b1 = 1;
            }
        }
        id = seg[1];
        if (id != -1) {
            gp = GET_GROUND(Ground_801C2BA4(id));
            ((UnkFlagStruct*) &gp->gv.icemt2.xC4)->b0 = 0;
        }
    } else {
        id = seg[1];
        if (id != -1) {
            gp = GET_GROUND(Ground_801C2BA4(id));
            if (!((UnkFlagStruct*) &gp->gv.icemt2.xC4)->b0) {
                ((UnkFlagStruct*) &gp->gv.icemt2.xC4)->b0 = 1;
                ((UnkFlagStruct*) &gp->gv.icemt2.xC4)->b1 = 1;
            }
        }
        id = seg[0];
        if (id != -1) {
            gp = GET_GROUND(Ground_801C2BA4(id));
            ((UnkFlagStruct*) &gp->gv.icemt2.xC4)->b0 = 0;
        }
    }
    if (cur > 0.0f) {
        id = seg[0];
        if (id != -1) {
            mgobj = Ground_801C2BA4(id);
            HSD_ASSERT(0xAF3, mgobj);
            Ground_801C4A08(mgobj);
        }
        seg[0] = seg[1];
        seg[1] = ev(arg3);
        if (seg[1] != -1) {
            f2 = grIceMt_801F993C(seg[0], seg[1]);
            mgobj = grIceMt_801F71E8(seg[1]);
            HSD_ASSERT(0xAFE, mgobj);
            jobj = mgobj->hsd_obj;
            HSD_ASSERT(0xAFF, jobj);
            HSD_JObjSetTranslateY(jobj, cur - f2);
            Ground_801C32AC(seg[1]);
            Ground_801C2FE0(mgobj);
            Ground_801C3214(seg[1]);
        }
        mgobj = Ground_801C2BA4(seg[0]);
        if (mgobj != NULL) {
            gp = GET_GROUND(mgobj);
            if (gp != NULL) {
                ((UnkFlagStruct*) &gp->gv.icemt2.xC4)->b1 = 1;
                gp = GET_GROUND(mgobj);
                new_var = &gp->gv.icemt2.xC8;
                if (((UnkFlagStruct*) &gp->gv.icemt2.xC4)->b1) {
                    ((UnkFlagStruct*) &gp->gv.icemt2.xC4)->b1 = 0;
                    ptrs = new_var;
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
        }
        did = 1;
    } else if (cur < -f) {
        id = seg[1];
        if (id != -1) {
            mgobj = Ground_801C2BA4(id);
            HSD_ASSERT(0xB13, mgobj);
            Ground_801C4A08(mgobj);
        }
        seg[1] = seg[0];
        seg[0] = ev(arg3);
        if (seg[0] != -1) {
            f2 = grIceMt_801F993C(seg[0], seg[1]);
            mgobj = grIceMt_801F71E8(seg[0]);
            HSD_ASSERT(0xB1E, mgobj);
            jobj = mgobj->hsd_obj;
            HSD_ASSERT(0xB1F, jobj);
            HSD_JObjSetTranslateY(jobj, f2 + (cur + f));
            Ground_801C32AC(seg[0]);
            Ground_801C2FE0(mgobj);
            Ground_801C3214(seg[0]);
        }
        mgobj = Ground_801C2BA4(seg[1]);
        if (mgobj != NULL) {
            gp = GET_GROUND(mgobj);
            if (gp != NULL) {
                ((UnkFlagStruct*) &gp->gv.icemt2.xC4)->b1 = 1;
                gp = GET_GROUND(mgobj);
                new_var = &gp->gv.icemt2.xC8;
                if (((UnkFlagStruct*) &gp->gv.icemt2.xC4)->b1) {
                    ((UnkFlagStruct*) &gp->gv.icemt2.xC4)->b1 = 0;
                    ptrs = new_var;
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
        }
        did = 1;
    }
    if (did != 0) {
        grIceMt_801FA854();
    }
    return did;
}

static inline HSD_JObj** grIceMt_FA0BC_jobjs(Ground* g)
{
    return &g->gv.icemt2.xC8;
}

void grIceMt_801FA0BC(s16* arg0)
{
    HSD_GObj* mgobj;
    HSD_JObj* jobj;
    Ground* gp;
    f32 frame;
    PAD_STACK(24);

    frame = grIceMt_801F993C(arg0[0], arg0[1]);

    if (arg0[0] != -1) {
        mgobj = grIceMt_801F71E8(arg0[0]);
        HSD_ASSERT (2884, mgobj);
        jobj = mgobj->hsd_obj;
        HSD_ASSERT(2886, jobj);
        HSD_JObjSetTranslateY(jobj, grIm_804DB570 * Ground_801C0498() + frame);
        Ground_801C3214(arg0[0]);
        Ground_801C2FE0(mgobj);
        Ground_801C32AC(arg0[0]);
    }

    if (arg0[1] != -1) {
        mgobj = grIceMt_801F71E8(arg0[1]);
        HSD_ASSERT(2896, mgobj);
        jobj = mgobj->hsd_obj;
        HSD_ASSERT(2898, jobj);
        HSD_JObjSetTranslateY(jobj, grIm_804DB570 * Ground_801C0498());
        Ground_801C3214(arg0[1]);
        Ground_801C2FE0(mgobj);
        Ground_801C32AC(arg0[1]);

        gp = mgobj->user_data;
        ((UnkFlagStruct*) &gp->gv.icemt2.xC4)->b0 = 1;
        ((UnkFlagStruct*) &gp->gv.icemt2.xC4)->b1 = 1;
        gp = mgobj->user_data;
        {
            HSD_JObj** jobjs = grIceMt_FA0BC_jobjs(gp);
            if (((UnkFlagStruct*) &gp->gv.icemt2.xC4)->b1) {
                ((UnkFlagStruct*) &gp->gv.icemt2.xC4)->b1 = 0;
                if (jobjs[0] != NULL) {
                    Ground_801C2D0C(0, jobjs[0]);
                }
                if (jobjs[1] != NULL) {
                    Ground_801C2D0C(1, jobjs[1]);
                }
                if (jobjs[2] != NULL) {
                    Ground_801C2D0C(2, jobjs[2]);
                }
                if (jobjs[3] != NULL) {
                    Ground_801C2D0C(3, jobjs[3]);
                }
            }
        }
    }
    grIceMt_801FA854();
}

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
    s32 (*cb)(HSD_GObj*, s32*) = (s32 (*)(HSD_GObj*, s32*))(Event) cb_;
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
    HSD_JObj* jobj;

    jobj = HSD_GObjGetHSDObj(arg0);
    HSD_ASSERT(0xBB1, jobj);
    jobj = HSD_JObjGetChild(jobj);
    HSD_ASSERT(0xBB2, jobj);

    while (jobj != NULL) {
        if (jobj == arg1) {
            break;
        }
        if (!(jobj->flags & 0x1000) && HSD_JObjGetChild(jobj) != NULL) {
            jobj = HSD_JObjGetChild(jobj);
        } else if (HSD_JObjGetNext(jobj) != NULL) {
            jobj = HSD_JObjGetNext(jobj);
        } else {
            while (HSD_JObjGetParent(jobj) != NULL &&
                   HSD_JObjGetNext(HSD_JObjGetParent(jobj)) == NULL)
            {
                jobj = HSD_JObjGetParent(jobj);
            }
            jobj = HSD_JObjGetNext(HSD_JObjGetParent(jobj));
        }
        count++;
    }
    if (jobj != NULL) {
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
