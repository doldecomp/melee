#include "gricemt.static.h"

#include "gr/types.h"

#include <dolphin/types.h>

typedef int (*GrIceMtCb)(Ground_GObj* gobj, int* out);

struct grIceMt_YakumonoParam {
    s16 x0;
    s16 x2;
    s16 x4;
    float x8;
    float xC;
    float x10;
    float x14;
    float x18;
    float x1C;
    float x20;
    float x24;
    float x28;
    float x2C;
    float x30;
    s16 x34;
    s16 x36;
    s16 x38;
    u16 x3A;
    float x3C;
    float x40;
    float x44;
    float x48;
    float x4C;
    float x50;
    float x54;
    float x58;
    float x5C;
    float x60;
    float x64;
    float x68;
    float x6C;
    float x70;
    float x74;
    float x78;
    float x7C;
    float x80;
    float x84;
    float x88;
    float x8C;
    float x90;
    float x94;
    s16 ft_max_y;
    s16 x9E;
    float x9C;
    float xA0;
    s16 xA4;
    s16 xA6;
    s16 xA8;
    s16* field_ixs;
    s16* xB0;
    s16* xB4;
    s16 xB8;
    s16 pad;
    grZakoGenerator_SpawnDesc xBC;
    float xC0;
    float xC4;
    float xC8;
    float xCC;
};

/* 1F6868 */ static void grIceMt_801F6868(bool id);
/* 1F686C */ static void grIceMt_801F686C(void);
/* 1F7080 */ static void grIceMt_801F7080(void);
/* 1F71DC */ static void grIceMt_801F71DC(void);
/* 1F71E0 */ static bool grIceMt_801F71E0(void);
/* 1F71E8 */ static Ground_GObj* setupStageCallbacks(int gobj_id);
/* 1F72D4 */ static void stageGObj0_OnInit(Ground_GObj*);
/* 1F75DC */ static bool stageGObj0_Callback1(Ground_GObj*);
/* 1F75E4 */ static void stageGObj0_GObjProc(Ground_GObj*);
/* 1F75E8 */ static void stageGObj0_Callback3(Ground_GObj*);
/* 1F75EC */ static void fn_801F75EC(Ground_GObj*);
/* 1F75FC */ static void stageGObj9_OnInit(Ground_GObj*);
/* 1F7720 */ static bool stageGObj9_Callback1(Ground_GObj*);
/* 1F7728 */ static void stageGObj9_GObjProc(Ground_GObj*);
/* 1F77AC */ static void stageGObj9_Callback3(Ground_GObj*);
/* 1F77B0 */ static void stageGObj10_UnkGroundCallback(Ground_GObj*);
/* 1F785C */ static void stageGObj10_OnInit(Ground_GObj*);
/* 1F796C */ static bool stageGObj10_Callback1(Ground_GObj*);
/* 1F7A2C */ static void stageGObj10_GObjProc(Ground_GObj*);
/* 1F7D90 */ static void stageGObj10_Callback3(Ground_GObj*);
/* 1F7D94 */ static void stageGObj1_OnInit(Ground_GObj*);
/* 1F7EE0 */ static bool stageGObj1_Callback1(Ground_GObj*);
/* 1F7EE8 */ static void stageGObj1_GObjProc(Ground_GObj*);
/* 1F7F1C */ static void stageGObj1_Callback3(Ground_GObj*);
/* 1F7F70 */ static void stageGObj2_OnInit(Ground_GObj*);
/* 1F8154 */ static bool stageGObj2_Callback1(Ground_GObj*);
/* 1F815C */ static void stageGObj2_GObjProc(Ground_GObj*);
/* 1F81B4 */ static void stageGObj2_Callback3(Ground_GObj*);
/* 1F8208 */ static void stageGObj3_OnInit(Ground_GObj*);
/* 1F835C */ static bool stageGObj3_Callback1(Ground_GObj*);
/* 1F8364 */ static void stageGObj3_GObjProc(Ground_GObj*);
/* 1F8398 */ static void stageGObj3_Callback3(Ground_GObj*);
/* 1F83EC */ static void stageGObj4_OnInit(Ground_GObj*);
/* 1F85BC */ static bool stageGObj4_Callback1(Ground_GObj* param1);
/* 1F85C4 */ static void stageGObj4_GObjProc(Ground_GObj*);
/* 1F8608 */ static void stageGObj4_Callback3(Ground_GObj*);
/* 1F865C */ static void stageGObj5_OnInit(Ground_GObj*);
/* 1F87C0 */ static bool stageGObj5_Callback1(Ground_GObj*);
/* 1F87C8 */ static void stageGObj5_GObjProc(Ground_GObj*);
/* 1F87FC */ static void stageGObj5_Callback3(Ground_GObj*);
/* 1F8850 */ static void stageGObj6_OnInit(Ground_GObj*);
/* 1F89A4 */ static bool stageGObj6_Callback1(Ground_GObj*);
/* 1F89AC */ static void stageGObj6_GObjProc(Ground_GObj*);
/* 1F89E0 */ static void stageGObj6_Callback3(Ground_GObj*);
/* 1F8A34 */ static void stageGObj8_OnInit(Ground_GObj*);
/* 1F8B08 */ static bool stageGObj8_Callback1(Ground_GObj*);
/* 1F8B10 */ static void stageGObj8_GObjProc(Ground_GObj*);
/* 1F8C60 */ static void stageGObj8_Callback3(Ground_GObj*);
/* 1F8CDC */ static void grIceMt_801F8CDC(Ground_GObj*, s16* joint_indices,
                                          int count, HSD_GObj** output_array);
/* 1F8E58 */ static int fn_801F8E58(Ground_GObj*, int* out);
/* 1F9038 */ static int fn_801F9038(Ground_GObj*);
/* 1F9150 */ static int fn_801F9150(Ground_GObj* gobj, int* out);
/* 1F91A8 */ static int fn_801F91A8(Ground_GObj*);
/* 1F929C */ static void grIceMt_801F929C(HSD_GObj* arg0, void* arg1);
/* 1F9668 */ static void grIceMt_801F9668(float);
/* 1F98A8 */ static void grIceMt_801F98A8(HSD_GObj* param1);
/* 1F993C */ static float grIceMt_801F993C(int under_id, int upper_id);
/* 1F9ACC */ static bool
grIceMt_801F9ACC(struct grIceMt_GObj9_GObj10_UnderUpperIdPair* seg_, float y,
                 GrIceMtSegmentLookup ev, Ground_GObj* arg3);
/* 1FA0BC */ static void
grIceMt_801FA0BC(struct grIceMt_GObj9_GObj10_UnderUpperIdPair* ids);
/* 1FA364 */ static bool grIceMt_801FA364(struct grIceMt_FA364_State* state,
                                          float* out, GrIceMtCb cb,
                                          Ground_GObj* gobj);
/* 1FA4CC */ static int fn_801FA4CC(int num);
/* 1FA500 */ static int grIceMt_801FA500(HSD_GObj*, HSD_JObj*);
/* 1FA6D8 */ void grIceMt_801FA6D8(void);
/* 1FA854 */ static void grIceMt_801FA854(void);
/* 1FA8F8 */ static DynamicsDesc* grIceMt_801FA8F8(enum_t id);
/* 1FA900 */ static bool grIceMt_801FA900(Vec3* a, int id, HSD_JObj* jobj);

static HSD_GObj* grIm_804D69E8;
static HSD_GObj* grIm_804D69EC;
static HSD_GObj* grIm_804D69F0;
static struct grIceMt_YakumonoParam* yakumono_param;

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
    int gobj_id;
    f32 x4;
    f32 x8;
} IceMtRowData;

IceMtRowData icemt_field[] = {
    { 1, 180.0f, -180.0f }, { 2, 190.0f, -180.0f }, { 3, 190.0f, -195.0f },
    { 4, 195.0f, -185.0f }, { 5, 190.0f, -200.0f }, { 6, 180.0f, -190.0f },
};

#define ICEMT_FIELD_MAX (ARRAY_SIZE(icemt_field))
#define BLOCK_COLL_JOBJ_MAX 20

GrJoint grIm_803E40B0[] = {
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

static void order_data(void)
{
    (void) -20.0f;
    (void) 0.0f;
    (void) 0.5f;
    (void) S32_TO_F32;
    (void) __FILE__;
    (void) "i<ICEMT_FIELD_MAX";
}

static StageCallbacks stage_callbacks[] = {
    {
        stageGObj0_OnInit,
        stageGObj0_Callback1,
        stageGObj0_GObjProc,
        stageGObj0_Callback3,
        0,
    },
    {
        stageGObj1_OnInit,
        stageGObj1_Callback1,
        stageGObj1_GObjProc,
        stageGObj1_Callback3,
        0,
    },
    {
        stageGObj2_OnInit,
        stageGObj2_Callback1,
        stageGObj2_GObjProc,
        stageGObj2_Callback3,
        0,
    },
    {
        stageGObj3_OnInit,
        stageGObj3_Callback1,
        stageGObj3_GObjProc,
        stageGObj3_Callback3,
        0,
    },
    {
        stageGObj4_OnInit,
        stageGObj4_Callback1,
        stageGObj4_GObjProc,
        stageGObj4_Callback3,
        0,
    },
    {
        stageGObj5_OnInit,
        stageGObj5_Callback1,
        stageGObj5_GObjProc,
        stageGObj5_Callback3,
        0,
    },
    {
        stageGObj6_OnInit,
        stageGObj6_Callback1,
        stageGObj6_GObjProc,
        stageGObj6_Callback3,
        0,
    },
    {
        0,
    },
    {
        stageGObj8_OnInit,
        stageGObj8_Callback1,
        stageGObj8_GObjProc,
        stageGObj8_Callback3,
        (1 << 30) | (1 << 31),
    },
    {
        stageGObj9_OnInit,
        stageGObj9_Callback1,
        stageGObj9_GObjProc,
        stageGObj9_Callback3,
        0,
    },
    {
        stageGObj10_OnInit,
        stageGObj10_Callback1,
        stageGObj10_GObjProc,
        stageGObj10_Callback3,
        0,
    },
};

StageData grIm_StageData = {
    Gr_Kind_Icemt,
    stage_callbacks,
    "/GrIm.dat",
    grIceMt_801F686C,
    grIceMt_801F6868,
    grIceMt_801F7080,
    grIceMt_801F71DC,
    grIceMt_801F71E0,
    grIceMt_801FA8F8,
    grIceMt_801FA900,
    (1 << 0),
    grIm_803E40B0,
    ARRAY_SIZE(grIm_803E40B0),
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

void grIceMt_801F686C(void)
{
    s32 field30;
    s32 field29;
    s32 field28;
    u32 i;
    s16* field_ixs;
    s32 id;
    f32 y_pos;
    f32 y_pos2;
    f32 y_pos3;
    f32 y_pos4;
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    PAD_STACK(0x10);

    yakumono_param = Ground_GetYakumonoParam();
    stage_info.unk8C.b4 = true;
    stage_info.unk8C.b5 = false;
    setupStageCallbacks(0);
    setupStageCallbacks(8);
    Ground_801C3260(1);
    Ground_801C3260(2);
    Ground_801C3260(3);
    Ground_801C3260(4);
    Ground_801C3260(5);
    Ground_801C3260(6);

    if (Stage_80225194() == 76) {
        for (i = 0; i < ICEMT_FIELD_MAX; i++) {
            field_ixs = yakumono_param->field_ixs;
            id = icemt_field[i].gobj_id;
            if (field_ixs[0] == id) {
                continue;
            }
            if (field_ixs[1] == id) {
                continue;
            }
            field30 = icemt_field[i].gobj_id;
            break;
        }
        HSD_ASSERT(600, i<ICEMT_FIELD_MAX);

        for (i = 0; i < ICEMT_FIELD_MAX; i++) {
            field_ixs = yakumono_param->field_ixs;
            id = icemt_field[i].gobj_id;
            if (field_ixs[0] == id) {
                continue;
            }
            if (field_ixs[1] == id) {
                continue;
            }
            if (field30 == id) {
                continue;
            }
            field29 = icemt_field[i].gobj_id;
            break;
        }
        HSD_ASSERT(609, i<ICEMT_FIELD_MAX);

        for (i = 0; i < ICEMT_FIELD_MAX; i++) {
            field_ixs = yakumono_param->field_ixs;
            id = icemt_field[i].gobj_id;
            if (field_ixs[0] == id) {
                continue;
            }
            if (field_ixs[1] == id) {
                continue;
            }
            if (field30 == id) {
                continue;
            }
            if (field29 == id) {
                continue;
            }
            field28 = icemt_field[i].gobj_id;
            break;
        }
        HSD_ASSERT(619, i<ICEMT_FIELD_MAX);

        y_pos = Ground_801C0498();
        y_pos = -20.0f * y_pos;
        y_pos = y_pos + grIceMt_801F993C(
                            icemt_field[yakumono_param->field_ixs[0]].gobj_id,
                            icemt_field[yakumono_param->field_ixs[1]].gobj_id);
        y_pos2 = y_pos + grIceMt_801F993C(
                             icemt_field[yakumono_param->field_ixs[1]].gobj_id,
                             icemt_field[field30].gobj_id);
        y_pos3 = y_pos2 + grIceMt_801F993C(icemt_field[field30].gobj_id,
                                           icemt_field[field29].gobj_id);
        y_pos4 = y_pos3 + grIceMt_801F993C(icemt_field[field29].gobj_id,
                                           icemt_field[field28].gobj_id);

        gobj = setupStageCallbacks(
            icemt_field[yakumono_param->field_ixs[2]].gobj_id);
        HSD_ASSERT(636, gobj);
        jobj = gobj->hsd_obj;
        HSD_ASSERT(637, jobj);
        HSD_JObjSetTranslateY(jobj, y_pos2);
        grIm_804D69E8 = gobj;

        gobj = setupStageCallbacks(
            icemt_field[yakumono_param->field_ixs[3]].gobj_id);
        HSD_ASSERT(641, gobj);
        jobj = gobj->hsd_obj;
        HSD_ASSERT(642, jobj);
        HSD_JObjSetTranslateY(jobj, y_pos3);
        grIm_804D69EC = gobj;

        gobj = setupStageCallbacks(
            icemt_field[yakumono_param->field_ixs[4]].gobj_id);
        HSD_ASSERT(646, gobj);
        jobj = gobj->hsd_obj;
        HSD_ASSERT(647, jobj);
        HSD_JObjSetTranslateY(jobj, y_pos4);
        grIm_804D69F0 = gobj;

        setupStageCallbacks(10);
    } else {
        setupStageCallbacks(9);
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
    if ((gobj = Ground_GetMapGObj(1))) {
        Ground_801C2FE0(gobj);
    }
    if ((gobj = Ground_GetMapGObj(2))) {
        Ground_801C2FE0(gobj);
    }
    if ((gobj = Ground_GetMapGObj(3))) {
        Ground_801C2FE0(gobj);
    }
    if ((gobj = Ground_GetMapGObj(4))) {
        Ground_801C2FE0(gobj);
    }
    if ((gobj = Ground_GetMapGObj(5))) {
        Ground_801C2FE0(gobj);
    }
    if ((gobj = Ground_GetMapGObj(6))) {
        Ground_801C2FE0(gobj);
    }
    if (Stage_80225194() == 76) {
        grZakoGenerator_801CAE04(&yakumono_param->xBC);
        if (rand_zero(yakumono_param->xB8)) {
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

Ground_GObj* setupStageCallbacks(int gobj_id)
{
    Ground_GObj* gobj;
    StageCallbacks* callbacks = &stage_callbacks[gobj_id];

    gobj = Ground_GetStageGObj(gobj_id);

    if (gobj != NULL) {
        /// @todo ::Ground_SetupStageCallbacks
        Ground* gp = GET_GROUND(gobj);
        gp->x8_callback = NULL;
        gp->xC_callback = NULL;
        GObj_SetupGXLink(gobj, grDisplay_801C5DB0, 3, 0);
        if (callbacks->callback3 != NULL) {
            gp->x1C_callback = callbacks->callback3;
        }
        if (callbacks->on_init != NULL) {
            callbacks->on_init(gobj);
        }
        if (callbacks->gobj_proc != NULL) {
            HSD_GObj_SetupProc(gobj, callbacks->gobj_proc, 4);
        }
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", __FILE__, 860, gobj_id);
    }

    return gobj;
}

void stageGObj0_OnInit(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);

    { /// @todo Unrolled loop?
        HSD_JObj* jobj;
        Vec3 v[4];
        {
            int const i = 0;
            int const ix = (ARRAY_SIZE(v) - 1) - i;
            jobj = Ground_801C3FA4(gobj, i + 18);
            if (jobj != NULL) {
                v[ix] = grIm_803B8220[i + 1];
                HSD_JObjSetTranslate(jobj, &v[ix]);
            }
        }
        {
            int const i = 1;
            int const ix = (ARRAY_SIZE(v) - 1) - i;
            jobj = Ground_801C3FA4(gobj, i + 18);
            if (jobj != NULL) {
                v[ix] = grIm_803B8220[i + 1];
                HSD_JObjSetTranslate(jobj, &v[ix]);
            }
        }
        {
            int const i = 2;
            int const ix = (ARRAY_SIZE(v) - 1) - i;
            jobj = Ground_801C3FA4(gobj, i + 18);
            if (jobj != NULL) {
                v[ix] = grIm_803B8220[i + 1];
                HSD_JObjSetTranslate(jobj, &v[ix]);
            }
        }
        {
            int const i = 3;
            int const ix = (ARRAY_SIZE(v) - 1) - i;
            jobj = Ground_801C3FA4(gobj, i + 18);
            if (jobj != NULL) {
                v[ix] = grIm_803B8220[i + 1];
                HSD_JObjSetTranslate(jobj, &v[ix]);
            }
        }
    }
    Ground_801C39C0();
    Ground_801C3BB4();
}

bool stageGObj0_Callback1(Ground_GObj* arg0)
{
    return false;
}

void stageGObj0_GObjProc(Ground_GObj* arg0) {}

void stageGObj0_Callback3(Ground_GObj* arg0) {}

void fn_801F75EC(Ground_GObj* gobj)
{
    GET_GROUND(gobj)->u.icemt9.x14 = 0;
}

void stageGObj9_OnInit(Ground_GObj* gobj)
{
    u32 iVar1;
    s16 val;
    Ground* gp = GET_GROUND(gobj);
    PAD_STACK(8);

    memzero(&gp->u.icemt9.x18, sizeof(gp->u.icemt9.x18));
    memzero(&gp->u.icemt9.x30, sizeof(gp->u.icemt9.x30));

    do {
        iVar1 = HSD_Randi(6);
        val = gp->u.icemt9.x30[iVar1];
    } while (val != 0);
    gp->u.icemt9.x30[iVar1] = yakumono_param->x0;
    gp->u.icemt9.x0.ids.under = icemt_field[iVar1].gobj_id;
    do {
        iVar1 = HSD_Randi(6);
        val = gp->u.icemt9.x30[iVar1];
    } while (val != 0);
    gp->u.icemt9.x30[iVar1] = yakumono_param->x0;
    gp->u.icemt9.x0.ids.upper = icemt_field[iVar1].gobj_id;
    grIceMt_801FA0BC(&gp->u.icemt9.x0.ids);
    gp->u.icemt9.x16 = 0;
    gp->u.icemt9.x0.state.phase = 0;
    gp->u.icemt9.x0.state.burst_count = 0;
    gp->u.icemt9.x0.state.delay = 0;
    gp->u.icemt9.x0.state.lerp_count = 0;
    gp->u.icemt9.x0.state.idx = -1;
    gp->u.icemt9.x0.state.cur = 0.0f;
    gp->u.icemt9.x14 = 1;
    Ground_801C10B8(gobj, fn_801F75EC);
}

bool stageGObj9_Callback1(Ground_GObj* arg0)
{
    return false;
}

void stageGObj9_GObjProc(Ground_GObj* gobj)
{
    u32 unused1;
    float y;
    u32 unused2;
    Ground* gp = gobj->user_data;
    if (gp->u.icemt9.x14 == 0) {
        grIceMt_801FA364(&gp->u.icemt9.x0.state, &y, fn_801F8E58, gobj);
        grIceMt_801F9ACC(&gp->u.icemt9.x0.ids,
                         grIceMt_801F96E0(&gp->u.icemt9.x0.ids, -y),
                         fn_801F9038, gobj);
        grIceMt_801F9668(y);
    }
}

void stageGObj9_Callback3(Ground_GObj* gobj) {}

void stageGObj10_UnkGroundCallback(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    u32 i;
    mpLib_JointCollisionCallback cb;
    void* user_data_out;

    gp->u.icemt10.x14_b0 = false;

    for (i = 0; i < ARRAY_SIZE(grIm_803E4544); i++) {
        mpJointGetCb1(grIm_803E4544[i], &cb, &user_data_out);
        if (cb == NULL) {
            mpJointSetCb1(grIm_803E4544[i], gp, onJointCollision);
        }
    }
}

void stageGObj10_OnInit(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);

    gp->u.icemt10.x0.ids.under =
        icemt_field[yakumono_param->field_ixs[1]].gobj_id;
    gp->u.icemt10.x0.ids.upper =
        icemt_field[yakumono_param->field_ixs[0]].gobj_id;

    grIceMt_801FA0BC(&gp->u.icemt10.x0.ids);

    gp->u.icemt10.x18 = 0;
    gp->u.icemt10.x1C = 2;
    gp->u.icemt10.x1A = 0;

    gp->u.icemt10.x14_b1 = false;
    gp->u.icemt10.x14_b2 = false;
    gp->u.icemt10.x14_b3 = false;
    gp->u.icemt10.x14_b4 = false;

    gp->u.icemt10.x16 = 0;
    gp->u.icemt10.x20 = 0.0f;

    gp->u.icemt10.x0.state.phase = 0;
    gp->u.icemt10.x0.state.burst_count = 0;
    gp->u.icemt10.x0.state.delay = 0;
    gp->u.icemt10.x0.state.lerp_count = 0;
    gp->u.icemt10.x0.state.idx = -1;
    gp->u.icemt10.x0.state.cur = 0.0f;

    gp->u.icemt10.x14_b0 = true;

    Ground_801C10B8(gobj, stageGObj10_UnkGroundCallback);
}

bool stageGObj10_Callback1(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    Ground_GObj* mgobj;
    PAD_STACK(8);

    if (gp->u.icemt10.x0.ids.under != -1) {
        mgobj = Ground_GetMapGObj(gp->u.icemt10.x0.ids.under);
        HSD_ASSERT(1141, mgobj);
        Ground_801C4A08(mgobj);
    }
    if (gp->u.icemt10.x0.ids.upper != -1) {
        mgobj = Ground_GetMapGObj(gp->u.icemt10.x0.ids.upper);
        HSD_ASSERT(1146, mgobj);
        Ground_801C4A08(mgobj);
    }
    stageGObj10_OnInit(gobj);
    gp->u.icemt10.x14_b0 = false;
    return false;
}

void stageGObj10_GObjProc(Ground_GObj* arg0)
{
    Ground* gp = arg0->user_data;
    f32 sp30;
    Vec3 sp24;
    HSD_GObj* fighter_gobj;
    HSD_GObj* mgobj;
    HSD_JObj* jobj;
    f32 dist;
    f32 cur;
    f32 step;
    f32 ratio;
    s32 var_r30;
    s32 r;
    PAD_STACK(8);

    if (gp->u.icemt10.x14_b0) {
        return;
    }
    if (!gp->u.icemt10.x14_b2) {
        var_r30 =
            grIceMt_801FA364(&gp->u.icemt9.x0.state, &sp30, fn_801F9150, arg0);
        if (gp->u.icemt10.x14_b4) {
            fighter_gobj = Ground_GetP1Fighter();
            if (fighter_gobj != NULL) {
                ftLib_80086644(fighter_gobj, &sp24);
                if (!gp->u.icemt10.x14_b1 && !ftLib_80086EC0(fighter_gobj) &&
                    sp24.y > yakumono_param->ft_max_y)
                {
                    gp->u.icemt10.x14_b1 = true;
                    gp->u.icemt10.x16 = yakumono_param->xA4;
                }
            }
        }
        if (gp->u.icemt10.x14_b1) {
            gp->u.icemt10.x20 += yakumono_param->xA0;
            if (gp->u.icemt10.x20 > yakumono_param->x9C) {
                gp->u.icemt10.x20 = yakumono_param->x9C;
            }
            gp->u.icemt10.x16 -= 1;
            if (gp->u.icemt10.x16 == 0) {
                gp->u.icemt10.x14_b1 = 0;
            }
        } else {
            gp->u.icemt10.x20 -= yakumono_param->xA0;
            if (gp->u.icemt10.x20 < 0.0f) {
                gp->u.icemt10.x20 = 0.0f;
            }
        }
        sp30 += gp->u.icemt10.x20;
    } else {
        mgobj = Ground_GetMapGObj(gp->u.icemt10.x0.ids.upper);
        HSD_ASSERT(1219, mgobj);
        jobj = mgobj->hsd_obj;
        HSD_ASSERT(1221, jobj);
        dist = HSD_JObjGetTranslationY(jobj) - yakumono_param->xA8;
        if (dist < 0.0f) {
            gp->u.icemt10.x0.state.cur = 0.0f;
        } else {
            ratio = gp->u.icemt10.x0.state.cur / yakumono_param->xA0;
            if (gp->u.icemt10.x0.state.cur * ratio -
                    (ratio * (0.5f * yakumono_param->xA0 * ratio)) >
                dist)
            {
                gp->u.icemt10.x0.state.cur -= yakumono_param->xA0;
                if (gp->u.icemt10.x0.state.cur < yakumono_param->xA0) {
                    gp->u.icemt10.x0.state.cur = yakumono_param->xA0;
                }
            }
        }
        sp30 = gp->u.icemt10.x0.state.cur;
    }
    grIceMt_801F9ACC(&gp->u.icemt10.x0.ids,
                     grIceMt_801F96E0(&gp->u.icemt10.x0.ids, -sp30),
                     fn_801F91A8, arg0);
    grIceMt_801F9668(sp30);
    if (gp->u.icemt10.x0.ids.under == -1) {
        gp->u.icemt10.x14_b2 = 1;
    }
    if (!gp->u.icemt10.x14_b3) {
        if (var_r30 != 0 && gp->u.icemt.x1A == yakumono_param->xA6) {
            gp->u.icemt10.x14_b3 = true;
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
    gp->u.icemt10.x14_b4 = false;
}

void stageGObj10_Callback3(Ground_GObj* gobj) {}

void stageGObj1_OnInit(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    GrIm588 sp14;
    PAD_STACK(0x4);
    Ground_801C2ED0(gobj->hsd_obj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 0);
    grAnime_801C77FC(gobj, 0, 7);
    gp->u.icemt1.x4 = Ground_801C3FA4(gobj, 3);
    gp->u.icemt1.x8 = Ground_801C3FA4(gobj, 4);
    gp->u.icemt1.xC = Ground_801C3FA4(gobj, 5);
    gp->u.icemt1.x10 = Ground_801C3FA4(gobj, 6);
    gp->u.icemt1.x14 = Ground_801C3FA4(gobj, 18);
    gp->u.icemt1.x18 = Ground_801C3FA4(gobj, 11);
    gp->u.icemt1.x1C = Ground_801C3FA4(gobj, 12);
    gp->u.icemt1.x20 = Ground_801C3FA4(gobj, 13);
    gp->u.icemt1.x24 = Ground_801C3FA4(gobj, 14);
    gp->u.icemt1.x28 = Ground_801C3FA4(gobj, 15);
    gp->u.icemt1.x2C = Ground_801C3FA4(gobj, 16);
    gp->u.icemt1.x30 = Ground_801C3FA4(gobj, 17);
    gp->u.icemt1.x0_b0 = false;
    sp14 = grIm_804DB588;
    grIceMt_801F8CDC(gobj, (s16*) &sp14, 2, gp->u.icemt1.x34);
}

bool stageGObj1_Callback1(Ground_GObj* arg0)
{
    return false;
}

void stageGObj1_GObjProc(Ground_GObj* arg0)
{
    PAD_STACK(8);
    grIceMt_801F98A8(arg0);
    Ground_801C2FE0(arg0);
}

void stageGObj1_Callback3(Ground_GObj* gobj)
{
    int i;
    Ground* gp = gobj->user_data;
    u32 unused[2];

    for (i = 0; i < 2; i++) {
        if (gp->u.icemt1.x34[i] != NULL) {
            grMaterial_801C8CDC(gp->u.icemt1.x34[i]);
        }
    }
}

void stageGObj2_OnInit(Ground_GObj* arg0)
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
    gp->u.icemt1.x4 = Ground_801C3FA4(arg0, 6);
    gp->u.icemt1.x8 = Ground_801C3FA4(arg0, 7);
    gp->u.icemt1.xC = Ground_801C3FA4(arg0, 8);
    gp->u.icemt1.x10 = Ground_801C3FA4(arg0, 9);
    gp->u.icemt1.x14 = Ground_801C3FA4(arg0, 21);
    gp->u.icemt1.x18 = Ground_801C3FA4(arg0, 14);
    gp->u.icemt1.x1C = Ground_801C3FA4(arg0, 15);
    gp->u.icemt1.x20 = Ground_801C3FA4(arg0, 16);
    gp->u.icemt1.x24 = Ground_801C3FA4(arg0, 17);
    gp->u.icemt1.x28 = Ground_801C3FA4(arg0, 18);
    gp->u.icemt1.x2C = Ground_801C3FA4(arg0, 19);
    gp->u.icemt1.x30 = Ground_801C3FA4(arg0, 20);
    gp->u.icemt1.x0_b0 = false;
    sp14 = grIm_804DB58C;
    grIceMt_801F8CDC(arg0, (s16*) &sp14, 2, &gp->u.icemt1.x34[0]);
    grIceMt_801F91EC(arg0, (s16*) ((u8*) gp + 0x100),
                     grIceMt_801FA500(arg0, jobj), -1, 0x25, 0x109, 0x27E,
                     fn_801F9338);
    grIceMt_801F91EC(arg0, &gp->u.icemt.x108[3], grIceMt_801FA500(arg0, jobj2),
                     -1, 38, 265, 638, fn_801F9448);
}

bool stageGObj2_Callback1(Ground_GObj* param1)
{
    return false;
}

void stageGObj2_GObjProc(Ground_GObj* param1)
{
    Ground* gp = GET_GROUND(param1);
    grIceMt_801F929C(param1, &gp->u.icemt1.x34[2]);
    grIceMt_801F929C(param1, &gp->u.icemt.x108[3]);
    grIceMt_801F98A8(param1);
    Ground_801C2FE0(param1);
}

void stageGObj2_Callback3(Ground_GObj* gobj)
{
    int i;
    Ground* gp = gobj->user_data;
    u32 unused[2];

    for (i = 0; i < 2; i++) {
        if (gp->u.icemt1.x34[i] != NULL) {
            grMaterial_801C8CDC(gp->u.icemt1.x34[i]);
        }
    }
}

void stageGObj3_OnInit(Ground_GObj* arg0)
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
    gp->u.icemt1.x4 = Ground_801C3FA4(arg0, 5);
    gp->u.icemt1.x8 = Ground_801C3FA4(arg0, 6);
    gp->u.icemt1.xC = Ground_801C3FA4(arg0, 7);
    gp->u.icemt1.x10 = Ground_801C3FA4(arg0, 8);
    gp->u.icemt1.x14 = Ground_801C3FA4(arg0, 21);
    gp->u.icemt1.x18 = Ground_801C3FA4(arg0, 14);
    gp->u.icemt1.x1C = Ground_801C3FA4(arg0, 15);
    gp->u.icemt1.x20 = Ground_801C3FA4(arg0, 16);
    gp->u.icemt1.x24 = Ground_801C3FA4(arg0, 17);
    gp->u.icemt1.x28 = Ground_801C3FA4(arg0, 18);
    gp->u.icemt1.x2C = Ground_801C3FA4(arg0, 19);
    gp->u.icemt1.x30 = Ground_801C3FA4(arg0, 20);
    gp->u.icemt1.x0_b0 = false;
    sp14.x0 = grIm_804DB590;
    sp14.x4 = grIm_804DB594;
    grIceMt_801F8CDC(arg0, (s16*) &sp14, 4, &gp->u.icemt1.x34[0]);
}

bool stageGObj3_Callback1(Ground_GObj* param1)
{
    return false;
}

void stageGObj3_GObjProc(Ground_GObj* arg0)
{
    grIceMt_801F98A8(arg0);
    Ground_801C2FE0(arg0);
}

void stageGObj3_Callback3(Ground_GObj* gobj)
{
    int i = 0;
    Ground* gp = gobj->user_data;
    u32 unused[2];

    while (i < 4) {
        if (gp->u.icemt1.x34[i] != NULL) {
            grMaterial_801C8CDC(gp->u.icemt1.x34[i]);
        }
        i++;
    }
}

void stageGObj4_OnInit(Ground_GObj* arg0)
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
    gp->u.icemt1.x4 = Ground_801C3FA4(arg0, 8);
    gp->u.icemt1.x8 = Ground_801C3FA4(arg0, 9);
    gp->u.icemt1.xC = Ground_801C3FA4(arg0, 10);
    gp->u.icemt1.x10 = Ground_801C3FA4(arg0, 11);
    gp->u.icemt1.x14 = Ground_801C3FA4(arg0, 23);
    gp->u.icemt1.x18 = Ground_801C3FA4(arg0, 16);
    gp->u.icemt1.x1C = Ground_801C3FA4(arg0, 17);
    gp->u.icemt1.x20 = Ground_801C3FA4(arg0, 18);
    gp->u.icemt1.x24 = Ground_801C3FA4(arg0, 19);
    gp->u.icemt1.x28 = Ground_801C3FA4(arg0, 20);
    gp->u.icemt1.x2C = Ground_801C3FA4(arg0, 21);
    gp->u.icemt1.x30 = Ground_801C3FA4(arg0, 22);
    gp->u.icemt1.x0_b0 = 0;
    sp14.x0 = grIm_804DB598;
    sp14.x4 = grIm_804DB59C;
    grIceMt_801F8CDC(arg0, (s16*) &sp14, 4, &gp->u.icemt1.x34[0]);
    r = grIceMt_801FA500(arg0, jobj3);
    grIceMt_801F91EC(arg0, gp->u.icemt.x108, grIceMt_801FA500(arg0, jobj2), r,
                     117, 265, 638, fn_801F9558);
}

bool stageGObj4_Callback1(Ground_GObj* param1)
{
    return false;
}

void stageGObj4_GObjProc(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    grIceMt_801F929C(gobj, &gp->u.icemt1.x34[4]);
    grIceMt_801F98A8(gobj);
    Ground_801C2FE0(gobj);
}
void stageGObj4_Callback3(Ground_GObj* gobj)
{
    s32 i;
    Ground* gp;
    u32 unused[2];

    gp = gobj->user_data;

    for (i = 0; i < 4; i++) {
        if (gp->u.icemt1.x34[i] != NULL) {
            grMaterial_801C8CDC(gp->u.icemt1.x34[i]);
        }
    }
}

void stageGObj5_OnInit(Ground_GObj* arg0)
{
    Ground* gp = GET_GROUND(arg0);
    GrIm825C sp14;
    PAD_STACK(0x4);
    Ground_801C2ED0(arg0->hsd_obj, gp->map_id);
    grAnime_801C8138(arg0, gp->map_id, 0);
    grAnime_801C77FC(arg0, 0, 7);
    gp->u.icemt1.x4 = Ground_801C3FA4(arg0, 6);
    gp->u.icemt1.x8 = Ground_801C3FA4(arg0, 7);
    gp->u.icemt1.xC = Ground_801C3FA4(arg0, 8);
    gp->u.icemt1.x10 = Ground_801C3FA4(arg0, 9);
    gp->u.icemt1.x14 = Ground_801C3FA4(arg0, 22);
    gp->u.icemt1.x18 = Ground_801C3FA4(arg0, 15);
    gp->u.icemt1.x1C = Ground_801C3FA4(arg0, 16);
    gp->u.icemt1.x20 = Ground_801C3FA4(arg0, 17);
    gp->u.icemt1.x24 = Ground_801C3FA4(arg0, 18);
    gp->u.icemt1.x28 = Ground_801C3FA4(arg0, 19);
    gp->u.icemt1.x2C = Ground_801C3FA4(arg0, 20);
    gp->u.icemt1.x30 = Ground_801C3FA4(arg0, 21);
    gp->u.icemt1.x0_b0 = 0;
    sp14.hi = grIm_803B825C.hi;
    sp14.x8 = grIm_803B825C.x8;
    grIceMt_801F8CDC(arg0, (s16*) &sp14, 5, &gp->u.icemt1.x34[0]);
}

bool stageGObj5_Callback1(Ground_GObj* param1)
{
    return false;
}

void stageGObj5_GObjProc(Ground_GObj* param1)
{
    grIceMt_801F98A8(param1);
    Ground_801C2FE0(param1);
    return;
}

/// @todo Rename: This is callback3 (destroy) for row 5 in stage_callbacks.
/// Destroys HSD_GObj* stored in icemt2.xF8[0-4].
void stageGObj5_Callback3(Ground_GObj* gobj)
{
    u32 unused[2];
    int i;
    Ground* gp = gobj->user_data;
    for (i = 0; i < 5; i++) {
        if (gp->u.icemt1.x34[i] != NULL) {
            grMaterial_801C8CDC(gp->u.icemt1.x34[i]);
        }
    }
}

void stageGObj6_OnInit(Ground_GObj* arg0)
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
    gp->u.icemt1.x4 = Ground_801C3FA4(arg0, 5);
    gp->u.icemt1.x8 = Ground_801C3FA4(arg0, 6);
    gp->u.icemt1.xC = Ground_801C3FA4(arg0, 7);
    gp->u.icemt1.x10 = Ground_801C3FA4(arg0, 8);
    gp->u.icemt1.x14 = Ground_801C3FA4(arg0, 21);
    gp->u.icemt1.x18 = Ground_801C3FA4(arg0, 14);
    gp->u.icemt1.x1C = Ground_801C3FA4(arg0, 15);
    gp->u.icemt1.x20 = Ground_801C3FA4(arg0, 16);
    gp->u.icemt1.x24 = Ground_801C3FA4(arg0, 17);
    gp->u.icemt1.x28 = Ground_801C3FA4(arg0, 18);
    gp->u.icemt1.x2C = Ground_801C3FA4(arg0, 19);
    gp->u.icemt1.x30 = Ground_801C3FA4(arg0, 20);
    gp->u.icemt1.x0_b0 = 0;
    sp14.x0 = grIm_804DB5A0;
    sp14.x4 = grIm_804DB5A4;
    grIceMt_801F8CDC(arg0, (s16*) &sp14, 4, &gp->u.icemt1.x34[0]);
}

bool stageGObj6_Callback1(Ground_GObj* arg0)
{
    return false;
}

void stageGObj6_GObjProc(Ground_GObj* param1)
{
    grIceMt_801F98A8(param1);
    Ground_801C2FE0(param1);
    return;
}

void stageGObj6_Callback3(Ground_GObj* gobj)
{
    Ground* gp;
    int i;
    u32 unused[2];

    gp = gobj->user_data;

    for (i = 0; i < 4; i++) {
        if (gp->u.icemt1.x34[i] != NULL) {
            grMaterial_801C8CDC(gp->u.icemt1.x34[i]);
        }
    }
}

void stageGObj8_OnInit(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);

    grAnime_801C8138(gobj, gp->map_id, 0);
    grAnime_801C77FC(gobj, 0, 7);
    Ground_801C4E70(Ground_801C3FA4(gobj, 1), Ground_801C3FA4(gobj, 2),
                    Ground_801C3FA4(gobj, 3), Ground_801C3FA4(gobj, 4),
                    Ground_801C3FA4(gobj, 5), Ground_801C3FA4(gobj, 6));
    gp->u.icemt_bg.x0 = 0.0f;
    gp->x11_flags.b012 = 2;
}

bool stageGObj8_Callback1(Ground_GObj* arg0)
{
    return false;
}

void stageGObj8_GObjProc(Ground_GObj* arg0)
{
    Ground* gp = GET_GROUND(arg0);
    HSD_JObj* jobj;
    f32 mul;
    f32 cur;
    mul = 0.3f * gp->u.icemt_bg.x0;
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

void stageGObj8_Callback3(Ground_GObj* arg0) {}

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

        archive = grDatFiles_GetArchive();
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

static inline s32 grIceMt_GetRandomIndex(s32 max, s32* list)
{
    return list[max != 0 ? HSD_Randi(max) : 0];
}

static inline void grIceMt_GetRandomTimer(int* out)
{
    s32 a;
    s32 b;
    s32 d;

    a = ((s16*) yakumono_param)[0x36 / 2];
    b = ((s16*) yakumono_param)[0x38 / 2];
    if (a > b) {
        d = a - b;
        a = b + (d != 0 ? HSD_Randi(d) : 0);
    } else if (a < b) {
        d = b - a;
        a = a + (d != 0 ? HSD_Randi(d) : 0);
    }
    *out = a;
}

int fn_801F8E58(Ground_GObj* arg0, int* out)
{
    Ground* gp;
    s32* p;
    s32 i;
    s32 max;
    s32 list[12];
    s32 chosen;

    arg0 = (Ground_GObj*) (gp = arg0->user_data);
    p = &list[max = 0];
    for (i = 0; i < 12; i++) {
        if (gp->u.icemt9.x18[0] == 0 && (Stage_80225194() != 212 || i >= 4)) {
            *p = i;
            p++;
            max++;
        }
        gp = (Ground*) ((u8*) gp + 2);
    }

    HSD_ASSERT(2077, max);
    chosen = grIceMt_GetRandomIndex(max, list);

    gp = (Ground*) arg0;
    for (i = 0; i < 12; i++) {
        if (gp->u.icemt9.x18[0] > 0) {
            gp->u.icemt9.x18[0]--;
        }
        gp = (Ground*) ((u8*) gp + 2);
    }

    gp = (Ground*) arg0;
    gp->u.icemt9.x18[chosen] = yakumono_param->x2;
    grIceMt_GetRandomTimer(out);
    return chosen;
}

int fn_801F9038(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    int idx;
    int i;
    PAD_STACK(8);

    do {
        idx = HSD_Randi(6);
    } while (gp->u.icemt9.x30[idx] != 0 ||
             gp->u.icemt9.x0.ids.under == icemt_field[idx].gobj_id ||
             gp->u.icemt9.x0.ids.upper == icemt_field[idx].gobj_id);

    for (i = 0; i < 6; i++) {
        if (gp->u.icemt9.x30[i] > 0) {
            gp->u.icemt9.x30[i]--;
        }
    }

    gp->u.icemt9.x30[idx] = yakumono_param->x0;

    return icemt_field[idx].gobj_id;
}

int fn_801F9150(Ground_GObj* arg0, int* out)
{
    Ground* gp = arg0->user_data;
    s16 next = 0;
    s32 a;

    while (true) {
        a = yakumono_param->xB0[gp->u.icemt.x1A];
        *out = yakumono_param->xB4[gp->u.icemt.x1A];
        if (a != -1 && *out != -1) {
            gp->u.icemt.x1A++;
            return a;
        }
        gp->u.icemt.x1A = next;
    }
}

int fn_801F91A8(Ground_GObj* gobj)
{
    Ground* gp;
    s32 index;
    s32 result;
    s16* xAC;

    gp = gobj->user_data;
    xAC = yakumono_param->field_ixs;
    index = xAC[gp->u.icemt.x1C];
    result = index;
    if (result == -1) {
        return result;
    }
    result = icemt_field[index].gobj_id;
    gp->u.icemt.x1C++;
    return result;
}

void grIceMt_801F91EC(HSD_GObj* param_1, s16* param_2, int param_3,
                      int param_4, int param_5, int param_6, int param_7,
                      mpLib_JointCollisionCallback param_8)
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

/// @copydoc mpLib_JointCollisionCallback
void fn_801F9338(void* user_data, int joint_id, CollData* coll, int coll_x50,
                 mpLib_GroundEnum ground_kind, float delta_y)
{
    {
        HSD_GObj* gobj;
        Ground* gp = user_data;
        s16* s = gp->u.icemt.x100;
        if ((s32) coll->x34_flags.b1234 == 1 && s[0] == 0) {
            gobj = Ground_GetMapGObj(2);
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
    }
    onJointCollision(user_data, joint_id, coll, coll_x50, ground_kind,
                     delta_y);
}

/// @copydoc mpLib_JointCollisionCallback
void fn_801F9448(void* user_data, int joint_id, CollData* coll, int coll_x50,
                 mpLib_GroundEnum ground_kind, float delta_y)
{
    {
        HSD_GObj* gobj;
        Ground* gp = user_data;
        s16* s = &gp->u.icemt.x108[3];
        if ((s32) coll->x34_flags.b1234 == 1 && s[0] == 0) {
            gobj = Ground_GetMapGObj(2);
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
    }
    onJointCollision(user_data, joint_id, coll, coll_x50, ground_kind,
                     delta_y);
}

/// @copydoc mpLib_JointCollisionCallback
void fn_801F9558(void* user_data, int joint_id, CollData* coll, int coll_x50,
                 mpLib_GroundEnum ground_kind, float delta_y)
{
    {
        HSD_GObj* gobj;
        Ground* gp = user_data;
        s16* s = gp->u.icemt.x108;
        if ((s32) coll->x34_flags.b1234 == 1 && s[0] == 0) {
            gobj = Ground_GetMapGObj(4);
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
    }
    onJointCollision(user_data, joint_id, coll, coll_x50, ground_kind,
                     delta_y);
}

void grIceMt_801F9668(float arg0)
{
    HSD_GObj* bg_gobj;
    Ground* bg_gp;

    bg_gobj = Ground_GetMapGObj(8);
    HSD_ASSERT(0xA37, bg_gobj);
    bg_gp = GET_GROUND(bg_gobj);
    HSD_ASSERT(0xA38, bg_gp);

    bg_gp->u.icemt_bg.x0 = arg0;
}

float grIceMt_801F96E0(struct grIceMt_GObj9_GObj10_UnderUpperIdPair* arg0,
                       float y)
{
    HSD_GObj* mgobj;
    HSD_JObj* jobj2;
    if (arg0->under != -1) {
        HSD_JObj* jobj;
        mgobj = Ground_GetMapGObj(arg0->under);
        HSD_ASSERT(2629, mgobj);
        jobj = GET_JOBJ(mgobj);
        HSD_ASSERT(2630, jobj);
        HSD_JObjAddTranslationY(jobj, y);
    }
    if (arg0->upper != -1) {
        HSD_JObj* jobj;
        mgobj = Ground_GetMapGObj(arg0->upper);
        HSD_ASSERT(2635, mgobj);
        jobj = GET_JOBJ(mgobj);
        jobj2 = jobj;
        HSD_ASSERT(2636, jobj);
        HSD_JObjAddTranslationY(jobj2, y);
    }
}

/// @note Checks bit 6 of icemt2.xC4 (as byte) - clears it and does cleanup.
void grIceMt_801F98A8(Ground_GObj* param1)
{
    Ground* gp = param1->user_data;
    HSD_JObj** ptrs = &gp->u.icemt1.x4;
    PAD_STACK(8);

    if (gp->u.icemt1.x0_b1) {
        gp->u.icemt1.x0_b1 = 0;
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

float grIceMt_801F993C(int under_id, int upper_id)
{
    float y = Ground_801C0498();
    u32 upper_ix;
    u32 under_ix;

    for (upper_ix = 0; upper_ix < ICEMT_FIELD_MAX; upper_ix++) {
        if (under_id == icemt_field[upper_ix].gobj_id) {
            break;
        }
    }
    HSD_ASSERT(2717, upper_ix<ICEMT_FIELD_MAX);

    for (under_ix = 0; under_ix < ICEMT_FIELD_MAX; under_ix++) {
        if (upper_id == icemt_field[under_ix].gobj_id) {
            break;
        }
    }
    HSD_ASSERT(2722, under_ix<ICEMT_FIELD_MAX);

    return -((y * icemt_field[upper_ix].x8) -
             (y * icemt_field[under_ix].x4 + yakumono_param->x40));
}

static inline HSD_GObj* grIceMt_801F71E8_inner2(int id)
{
    return setupStageCallbacks(id);
}

static inline HSD_GObj* grIceMt_801F71E8_noinline2(int id)
{
    return grIceMt_801F71E8_inner2(id);
}

bool grIceMt_801F9ACC(struct grIceMt_GObj9_GObj10_UnderUpperIdPair* ids_,
                      float y, GrIceMtSegmentLookup ev, Ground_GObj* arg3)
{
    struct grIceMt_GObj9_GObj10_UnderUpperIdPair* ids = ids_;
    bool result = false;
    HSD_GObj* mgobj;
    HSD_JObj* jobj;
    Ground* gp;
    HSD_JObj** ptrs;
    HSD_JObj** new_var;
    f32 cur;
    f32 y0;
    f32 y1;
    s32 id;
    PAD_STACK(16);

    if (ids->under == -1 || ids->upper == -1) {
        return false;
    }

    y0 = grIceMt_801F993C(ids->under, ids->upper);
    mgobj = Ground_GetMapGObj(ids->upper);
    HSD_ASSERT(2745, mgobj);
    jobj = mgobj->hsd_obj;
    HSD_ASSERT(2746, jobj);
    cur = HSD_JObjGetTranslationY(jobj);
    if (ABS(cur) < 10.0f) {
        gp = GET_GROUND(Ground_GetMapGObj(ids->upper));
        gp->u.icemt1.x0_b1 = true;
    } else if (ABS(cur + y0) < 10.0f) {
        gp = GET_GROUND(Ground_GetMapGObj(ids->under));
        gp->u.icemt1.x0_b1 = true;
    }
    if (cur < 0.5f * -y0) {
        id = ids->under;
        if (id != -1) {
            gp = GET_GROUND(Ground_GetMapGObj(id));
            if (!gp->u.icemt1.x0_b0) {
                gp->u.icemt1.x0_b0 = true;
                gp->u.icemt1.x0_b1 = true;
            }
        }
        id = ids->upper;
        if (id != -1) {
            gp = GET_GROUND(Ground_GetMapGObj(id));
            gp->u.icemt1.x0_b0 = false;
        }
    } else {
        id = ids->upper;
        if (id != -1) {
            gp = GET_GROUND(Ground_GetMapGObj(id));
            if (!gp->u.icemt1.x0_b0) {
                gp->u.icemt1.x0_b0 = true;
                gp->u.icemt1.x0_b1 = true;
            }
        }
        id = ids->under;
        if (id != -1) {
            gp = GET_GROUND(Ground_GetMapGObj(id));
            gp->u.icemt1.x0_b0 = false;
        }
    }
    if (cur > 0.0f) {
        id = ids->under;
        if (id != -1) {
            mgobj = Ground_GetMapGObj(id);
            HSD_ASSERT(2803, mgobj);
            Ground_801C4A08(mgobj);
        }
        ids->under = ids->upper;
        ids->upper = ev(arg3);
        if (ids->upper != -1) {
            y1 = grIceMt_801F993C(ids->under, ids->upper);
            mgobj = setupStageCallbacks(ids->upper);
            HSD_ASSERT(2814, mgobj);
            jobj = mgobj->hsd_obj;
            HSD_ASSERT(2815, jobj);
            HSD_JObjSetTranslateY(jobj, cur - y1);
            Ground_801C32AC(ids->upper);
            Ground_801C2FE0(mgobj);
            Ground_801C3214(ids->upper);
        }
        mgobj = Ground_GetMapGObj(ids->under);
        if (mgobj != NULL) {
            gp = GET_GROUND(mgobj);
            if (gp != NULL) {
                gp->u.icemt1.x0_b1 = 1;
                gp = GET_GROUND(mgobj);
                new_var = &gp->u.icemt1.x4;
                if (gp->u.icemt1.x0_b1) {
                    gp->u.icemt1.x0_b1 = 0;
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
        result = true;
    } else if (cur < -y0) {
        id = ids->upper;
        if (id != -1) {
            mgobj = Ground_GetMapGObj(id);
            HSD_ASSERT(2835, mgobj);
            Ground_801C4A08(mgobj);
        }
        ids->upper = ids->under;
        ids->under = ev(arg3);
        if (ids->under != -1) {
            y1 = grIceMt_801F993C(ids->under, ids->upper);
            mgobj = setupStageCallbacks(ids->under);
            HSD_ASSERT(2846, mgobj);
            jobj = mgobj->hsd_obj;
            HSD_ASSERT(2847, jobj);
            HSD_JObjSetTranslateY(jobj, y1 + (cur + y0));
            Ground_801C32AC(ids->under);
            Ground_801C2FE0(mgobj);
            Ground_801C3214(ids->under);
        }
        mgobj = Ground_GetMapGObj(ids->upper);
        if (mgobj != NULL) {
            gp = GET_GROUND(mgobj);
            if (gp != NULL) {
                gp->u.icemt1.x0_b1 = true;
                gp = GET_GROUND(mgobj);
                new_var = &gp->u.icemt1.x4;
                if (gp->u.icemt1.x0_b1) {
                    gp->u.icemt1.x0_b1 = false;
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
        result = true;
    }
    if (result) {
        grIceMt_801FA854();
    }
    return result;
}

static inline HSD_JObj** grIceMt_FA0BC_jobjs(Ground* g)
{
    return &g->u.icemt1.x4;
}

void grIceMt_801FA0BC(struct grIceMt_GObj9_GObj10_UnderUpperIdPair* ids)
{
    HSD_GObj* mgobj;
    HSD_JObj* jobj;
    Ground* gp;
    f32 frame;
    PAD_STACK(24);

    frame = grIceMt_801F993C(ids->under, ids->upper);

    if (ids->under != -1) {
        mgobj = setupStageCallbacks(ids->under);
        HSD_ASSERT (2884, mgobj);
        jobj = mgobj->hsd_obj;
        HSD_ASSERT(2886, jobj);
        HSD_JObjSetTranslateY(jobj, -20.0f * Ground_801C0498() + frame);
        Ground_801C3214(ids->under);
        Ground_801C2FE0(mgobj);
        Ground_801C32AC(ids->under);
    }

    if (ids->upper != -1) {
        mgobj = setupStageCallbacks(ids->upper);
        HSD_ASSERT(2896, mgobj);
        jobj = mgobj->hsd_obj;
        HSD_ASSERT(2898, jobj);
        HSD_JObjSetTranslateY(jobj, -20.0f * Ground_801C0498());
        Ground_801C3214(ids->upper);
        Ground_801C2FE0(mgobj);
        Ground_801C32AC(ids->upper);

        gp = mgobj->user_data;
        gp->u.icemt1.x0_b0 = 1;
        gp->u.icemt1.x0_b1 = 1;
        gp = mgobj->user_data;
        {
            HSD_JObj** jobjs = grIceMt_FA0BC_jobjs(gp);
            if (gp->u.icemt1.x0_b1) {
                gp->u.icemt1.x0_b1 = 0;
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

bool grIceMt_801FA364(struct grIceMt_FA364_State* state, f32* out,
                      GrIceMtCb cb, Ground_GObj* gobj)
{
    bool ret = true;
    f32 result;
    int next_delay;
    s16 tmp;

    switch (state->phase) {
    case 0:
        tmp = state->delay;
        state->delay = tmp - 1;
        if (tmp < 0) {
            state->idx = cb(gobj, &next_delay);
            state->delay = (s16) next_delay;
            state->phase = 1;
            state->lerp_count = ((s16*) yakumono_param)[0x34 / 2];
        }
        break;
    case 1:
        state->lerp_count = state->lerp_count - 1;
        tmp = state->lerp_count;
        if (tmp != 0) {
            state->cur += (((f32*) ((u8*) yakumono_param + 4))[state->idx] -
                           state->cur) /
                          (f32) tmp;
            ret = false;
        } else {
            state->phase = 0;
            state->cur = ((f32*) ((u8*) yakumono_param + 4))[state->idx];
        }
        break;
    }

    result = state->cur;
    if (state->burst_count != 0) {
        result = yakumono_param->x3C * Ground_801C0498();
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
            while (true) {
                if (HSD_JObjGetParent(jobj) == NULL) {
                    jobj = NULL;
                    break;
                }
                if (HSD_JObjGetNext(HSD_JObjGetParent(jobj)) != NULL) {
                    jobj = HSD_JObjGetNext(HSD_JObjGetParent(jobj));
                    break;
                }
                jobj = HSD_JObjGetParent(jobj);
            }
        }
        count++;
    }
    if (jobj != NULL) {
        return count;
    }
    return -1;
}

void grIceMt_801FA6D8(void)
{
    HSD_GObj* gobj;
    Ground* gp;

    if (Stage_80225194() == 0x4C) {
        gobj = Ground_GetMapGObj(0xA);
        if (gobj != NULL) {
            gp = gobj->user_data;
            if (gp != NULL) {
                gp->u.icemt.xA = yakumono_param->x3A;
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
        temp_r3 = Ground_GetMapGObj(10);
        if (temp_r3 != NULL) {
            temp_r3_2 = temp_r3->user_data;
            if (temp_r3_2 != NULL) {
                arg0->x = 0;
                arg0->y = -temp_r3_2->u.icemt.x10;
                arg0->z = 0;
                return;
            }
        }
        arg0->z = 0;
        arg0->y = 0;
        arg0->x = 0;
        return;
    }
    temp_r3_3 = Ground_GetMapGObj(9);
    if (temp_r3_3 != NULL) {
        temp_r3_4 = temp_r3_3->user_data;
        if (temp_r3_4 != NULL) {
            arg0->x = 0;
            arg0->y = -temp_r3_4->u.icemt.x10;
            arg0->z = 0;
            return;
        }
    }
    arg0->z = 0;
    arg0->y = 0;
    arg0->x = 0;
}

/// @copydoc mpLib_JointCollisionCallback
void onJointCollision(void* user_data, int joint_id, CollData* coll,
                      int coll_x50, mpLib_GroundEnum ground_kind,
                      float delta_y)
{
    Ground* gp = user_data;
    HSD_GObj* gobj;
    Ground* gp2;
    if (Ground_GetP1Fighter() == coll->x0_gobj) {
        gobj = Ground_GetMapGObj(0xA);
        if (gobj != NULL) {
            gp2 = gobj->user_data;
            if (gp2 != NULL) {
                ((UnkFlagStruct*) &gp2->u.icemt.x14)->b4 = 1;
            }
        }
    }
}

void grIceMt_801FA854(void)
{
    HSD_GObj* gobj = Ground_GetMapGObj(0);
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
