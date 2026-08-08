#include "grpura.h"

#include "grdisplay.h"
#include "ground.h"
#include "grzakogenerator.h"
#include "inlines.h"
#include "stage.h"
#include "types.h"

#include <platform.h>

#include "cm/camera.h"
#include "cm/types.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "lb/lbspdisplay.h"
#include "mp/mplib.h"

#include <dolphin/mtx.h>
#include <baselib/debug.h>
#include <baselib/dobj.h>
#include <baselib/gobj.h>
#include <baselib/gobjproc.h>
#include <baselib/jobj.h>
#include <baselib/random.h>
#include <baselib/tobj.h>

struct GrPuModelDesc {
    /* 0x0 */ s32 x0;
    /* 0x4 */ f32 x4;
    /* 0x8 */ s32 x8;
};

struct GrPuVtxMapEntry {
    /* 0x0 */ GrJoint joint;
    /* 0x6 */ s16 x06;
    /* 0x8 */ HSD_JObj* jobj;
};

/* 211CFC */ static void grPura_80211CFC(bool);
/* 211D00 */ static void grPura_80211D00(void);
/* 211DD8 */ static void grPura_80211DD8(void);
/* 211DDC */ static void grPura_80211DDC(void);
/* 211E00 */ static bool grPura_80211E00(void);
/* 211E08 */ static HSD_GObj* setupStageCallbacks(int);
/* 211EF0 */ static void stageGObj0_OnInit(Ground_GObj*);
/* 211F1C */ static bool stageGObj0_Callback1(Ground_GObj*);
/* 211F24 */ static void stageGObj0_GObjProc(Ground_GObj*);
/* 211F28 */ static void stageGObj0_Callback3(Ground_GObj*);
/* 211F2C */ static void stageGObj27_OnInit(Ground_GObj*);
/* 211F58 */ static bool stageGObj27_Callback1(Ground_GObj*);
/* 211F60 */ static void stageGObj27_GObjProc(Ground_GObj*);
/* 211F64 */ static void stageGObj27_Callback3(Ground_GObj*);
/* 211F68 */ static void stageGObj4_OnInit(Ground_GObj*);
/* 211FD0 */ static bool stageGObj4_Callback1(Ground_GObj*);
/* 211FD8 */ static void stageGObj4_GObjProc(Ground_GObj*);
/* 212020 */ static void stageGObj4_Callback3(Ground_GObj*);
/* 212024 */ static void stageGObj1_OnInit(Ground_GObj*);
/* 2120D8 */ static bool stageGObj1_Callback1(Ground_GObj*);
/* 2120E0 */ static void stageGObj1_GObjProc(Ground_GObj*);
/* 21228C */ static void stageGObj1_Callback3(Ground_GObj*);
/* 212290 */ static void stageGObj2_OnInit(Ground_GObj*);
/* 212314 */ static bool stageGObj2_Callback1(Ground_GObj*);
/* 21231C */ static void stageGObj2_GObjProc(Ground_GObj*);
/* 2125EC */ static void stageGObj2_Callback3(Ground_GObj*);
/* 2125F0 */ static UNK_RET grPura_802125F0(HSD_GObj*);
/* 212CD4 */ static void grPura_80212CD4(HSD_GObj*);
/* 212EF4 */ static void grPura_80212EF4(HSD_GObj*);
/* 212FC0 */ static void grPura_80212FC0(HSD_GObj*);
/* 213030 */ static void grPura_80213030(Ground_GObj* arg0);
/* 2130C0 */ static DynamicsDesc* grPura_802130C0(enum_t);
/* 2130C8 */ static bool grPura_802130C8(Vec3* a, int, HSD_JObj*);
/* 2130D0 */ static UNK_RET fn_802130D0(HSD_GObj*, int);
/* 213128 */ static void grPura_80213128(HSD_DObj*);
/* 213224 */ static UNK_RET grPura_80213224(HSD_DObj*);
/* 213250 */ static void grPura_80213250(HSD_JObj*);

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
        stageGObj2_OnInit,
        stageGObj2_Callback1,
        stageGObj2_GObjProc,
        stageGObj2_Callback3,
        0,
    },
    {
        stageGObj4_OnInit,
        stageGObj4_Callback1,
        stageGObj4_GObjProc,
        stageGObj4_Callback3,
        (1 << 30),
    },
    {
        stageGObj2_OnInit,
        stageGObj2_Callback1,
        stageGObj2_GObjProc,
        stageGObj2_Callback3,
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
        stageGObj2_OnInit,
        stageGObj2_Callback1,
        stageGObj2_GObjProc,
        stageGObj2_Callback3,
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
        stageGObj2_OnInit,
        stageGObj2_Callback1,
        stageGObj2_GObjProc,
        stageGObj2_Callback3,
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
        stageGObj2_OnInit,
        stageGObj2_Callback1,
        stageGObj2_GObjProc,
        stageGObj2_Callback3,
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
        stageGObj2_OnInit,
        stageGObj2_Callback1,
        stageGObj2_GObjProc,
        stageGObj2_Callback3,
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
        stageGObj2_OnInit,
        stageGObj2_Callback1,
        stageGObj2_GObjProc,
        stageGObj2_Callback3,
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
        stageGObj2_OnInit,
        stageGObj2_Callback1,
        stageGObj2_GObjProc,
        stageGObj2_Callback3,
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
        stageGObj2_OnInit,
        stageGObj2_Callback1,
        stageGObj2_GObjProc,
        stageGObj2_Callback3,
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
        stageGObj2_OnInit,
        stageGObj2_Callback1,
        stageGObj2_GObjProc,
        stageGObj2_Callback3,
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
        stageGObj2_OnInit,
        stageGObj2_Callback1,
        stageGObj2_GObjProc,
        stageGObj2_Callback3,
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
        stageGObj2_OnInit,
        stageGObj2_Callback1,
        stageGObj2_GObjProc,
        stageGObj2_Callback3,
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
        stageGObj27_OnInit,
        stageGObj27_Callback1,
        stageGObj27_GObjProc,
        stageGObj27_Callback3,
        (1 << 31),
    },
};

StageData grPu_StageData = {
    Gr_Kind_Pura,
    stage_callbacks,
    "/GrPu.dat",
    grPura_80211D00,
    grPura_80211CFC,
    grPura_80211DD8,
    grPura_80211DDC,
    grPura_80211E00,
    grPura_802130C0,
    grPura_802130C8,
    (1 << 0),
    NULL,
    0,
};

void grPura_80211CFC(bool num) {}

/* 4D6AA0 */ static void* yakumono_param;

void grPura_80211D00(void)
{
    UNUSED u32 unused1;
    UNUSED u32 unused2;
    UNUSED u32 unused3;
    Vec3 cam_offset;

    yakumono_param = Ground_GetYakumonoParam();
    stage_info.unk8C.b4 = 0;
    stage_info.unk8C.b5 = 1;
    setupStageCallbacks(0);
    setupStageCallbacks(1);
    setupStageCallbacks(4);
    Ground_801C39C0();
    Ground_801C3BB4();
    Stage_UnkSetVec3TCam_Offset(&cam_offset);
    Ground_801C3880(0.8f * (Stage_GetCamBoundsTopOffset() - cam_offset.y));
    Ground_801C3890(0.8f * (Stage_GetCamBoundsBottomOffset() - cam_offset.y));
    Ground_801C38A0(0.8f * (Stage_GetCamBoundsLeftOffset() - cam_offset.x));
    Ground_801C38AC(0.8f * (Stage_GetCamBoundsRightOffset() - cam_offset.x));
}

void grPura_80211DD8(void) {}

void grPura_80211DDC(void)
{
    grZakoGenerator_801CAE04(NULL);
}

bool grPura_80211E00(void)
{
    return false;
}

HSD_GObj* grPura_80211E08_noinline(int gobj_id)
{
    return setupStageCallbacks(gobj_id);
};

HSD_GObj* grPura_80211E08_noinline2(int gobj_id)
{
    return grPura_80211E08_noinline(gobj_id);
};

HSD_GObj* setupStageCallbacks(int gobj_id)
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
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", __FILE__, 264, gobj_id);
    }

    return gobj;
}

void stageGObj0_OnInit(Ground_GObj* arg0)
{
    Ground* gp = arg0->user_data;
    grAnime_801C8138(arg0, gp->map_id, 0);
}

bool stageGObj0_Callback1(Ground_GObj* arg0)
{
    return false;
}

void stageGObj0_GObjProc(Ground_GObj* arg0) {}

void stageGObj0_Callback3(Ground_GObj* arg0) {}

void stageGObj27_OnInit(Ground_GObj* arg0)
{
    Ground* gp = arg0->user_data;
    grAnime_801C8138(arg0, gp->map_id, 0);
}

bool stageGObj27_Callback1(Ground_GObj* arg0)
{
    return false;
}

void stageGObj27_GObjProc(Ground_GObj* arg0) {}

void stageGObj27_Callback3(Ground_GObj* arg0) {}

void stageGObj4_OnInit(Ground_GObj* arg0)
{
    Ground_JObjInline1(arg0);
    grPura_80212CD4(arg0);
    grPura_802125F0(arg0);
    grPura_80212FC0(arg0);
}

bool stageGObj4_Callback1(Ground_GObj* arg0)
{
    return false;
}

void stageGObj4_GObjProc(Ground_GObj* arg0)
{
    grPura_80212EF4(arg0);
    Ground_801C2FE0(arg0);
    grPura_80213030(arg0);
    mpLib_80055E24(0x18);
    lb_800115F4();
}

void stageGObj4_Callback3(Ground_GObj* arg0) {}

GXColor grPu_803E6AA0[] = {
    { 0x00, 0x00, 0x00, 0xFF },
    { 0x00, 0x00, 0x50, 0xFF },
    { 0x1E, 0x46, 0x00, 0xFF },
    { 0x87, 0x87, 0x00, 0xFF },
};

void stageGObj1_OnInit(Ground_GObj* arg0)
{
    unsigned int uVar1;
    Ground* gp = GET_GROUND(arg0);
    PAD_STACK(16);
    grAnime_801C8138(arg0, gp->map_id, 0);
    gp->x11_flags.b012 = 2;
    gp->u.pura.xC4 = HSD_Randi(4);
    do {
        uVar1 = HSD_Randi(4);
    } while (gp->u.pura.xC4 == (gp->u.pura.xC6 = uVar1));
    Ground_801C205C(&grPu_803E6AA0[gp->u.pura.xC4]);
    Camera_SetBackgroundColor(grPu_803E6AA0[gp->u.pura.xC4].r,
                              grPu_803E6AA0[gp->u.pura.xC4].g,
                              grPu_803E6AA0[gp->u.pura.xC4].b);
    gp->u.pura.xC8 = 0;
}

bool stageGObj1_Callback1(Ground_GObj* arg0)
{
    return false;
}

void stageGObj1_GObjProc(Ground_GObj* arg0)
{
    GXColor spilC;
    GXColor sp18;
    Ground* gp = arg0->user_data;
    f32 t;
    s16 cur;
    unsigned int uVar1;
    UNUSED u8 _pad4[4];
    PAD_STACK(8);

    if ((s16) gp->u.pura.xC8 < 0xE10) {
        spilC = grPu_803E6AA0[gp->u.pura.xC6];
        sp18 = grPu_803E6AA0[gp->u.pura.xC4];
        cur = gp->u.pura.xC8;
        t = (f32) cur / 3600.0f;
        gp->u.pura.xC8 = cur + 1;
        sp18.r =
            (s8) (t * (f32) ((u8) spilC.r - (u8) sp18.r) + (f32) (u8) sp18.r);
        sp18.g =
            (s8) (t * (f32) ((u8) spilC.g - (u8) sp18.g) + (f32) (u8) sp18.g);
        sp18.b =
            (s8) (t * (f32) ((u8) spilC.b - (u8) sp18.b) + (f32) (u8) sp18.b);
        Ground_801C205C(&sp18);
        Camera_SetBackgroundColor(sp18.r, sp18.g, sp18.b);
        return;
    }
    gp->u.pura.xC4 = gp->u.pura.xC6;
    do {
        uVar1 = HSD_Randi(4);
    } while ((s16) gp->u.pura.xC4 == (gp->u.pura.xC6 = uVar1));
    gp->u.pura.xC8 = 0;
}

void stageGObj1_Callback3(Ground_GObj* arg0) {}

/* 3E6AB0 */ static struct GrPuModelDesc grPu_803E6AB0[] = {
    { 0, 1.0F, 2 },   { 1, 1.0F, 3 },   { 2, 1.0F, 5 },   { 3, 1.0F, 6 },
    { 4, 1.0F, 7 },   { 5, 1.0F, 8 },   { 6, 1.0F, 9 },   { 7, 1.0F, 10 },
    { 8, 1.0F, 11 },  { 9, 1.0F, 12 },  { 10, 1.0F, 13 }, { 11, 1.0F, 13 },
    { 12, 1.0F, 13 }, { 13, 1.0F, 14 }, { 14, 1.0F, 15 }, { 15, 1.0F, 16 },
    { 16, 1.0F, 17 }, { 17, 1.0F, 18 }, { 18, 1.0F, 19 }, { 19, 1.0F, 20 },
    { 20, 1.0F, 21 }, { 21, 1.0F, 22 }, { 22, 1.0F, 23 }, { 23, 1.0F, 24 },
    { 24, 1.0F, 25 }, { 25, 1.0F, 26 }, { -1, 1.0F, -1 },
};

static void order_data(void)
{
    (void) "GrdIzumiStar_TopN_joint";
}

/* 3E6C0C */ static struct GrPuVtxMapEntry grPu_803E6C0C[] = {
    { { 20, 2, 21 }, 0, NULL },
    { { 21, 2, 22 }, 0, NULL },
    { { 22, 2, 23 }, 0, NULL },
    { { 23, 2, 24 }, 0, NULL },
    { { 24, 2, 25 }, 0, NULL },
    { { 25, 2, 26 }, 0, NULL },
    { { 26, 2, 27 }, 0, NULL },
    { { 39, 2, 28 }, 0, NULL },
    { { 284, 12, 21 }, 0, NULL },
    { { 285, 12, 23 }, 0, NULL },
    { { 267, 12, 24 }, 0, NULL },
    { { 261, 12, 25 }, 0, NULL },
    { { 262, 12, 26 }, 0, NULL },
    { { 275, 12, 27 }, 0, NULL },
    { { 276, 12, 28 }, 0, NULL },
    { { 277, 12, 29 }, 0, NULL },
    { { 269, 12, 30 }, 0, NULL },
    { { 270, 12, 31 }, 0, NULL },
    { { 272, 12, 32 }, 0, NULL },
    { { 286, 12, 33 }, 0, NULL },
    { { 180, 8, 23 }, 0, NULL },
    { { 181, 8, 51 }, 0, NULL },
    { { 182, 8, 27 }, 0, NULL },
    { { 183, 8, 30 }, 0, NULL },
    { { 184, 8, 31 }, 0, NULL },
    { { 513, 25, 10 }, 0, NULL },
    { { 514, 25, 13 }, 0, NULL },
    { { 520, 25, 16 }, 0, NULL },
    { { 521, 25, 19 }, 0, NULL },
    { { 522, 25, 22 }, 0, NULL },
    { { 496, 25, 25 }, 0, NULL },
    { { 497, 25, 28 }, 0, NULL },
    { { 500, 25, 31 }, 0, NULL },
    { { 523, 25, 32 }, 0, NULL },
    { { 524, 25, 29 }, 0, NULL },
    { { 527, 25, 26 }, 0, NULL },
    { { 528, 25, 23 }, 0, NULL },
    { { 525, 25, 20 }, 0, NULL },
    { { 526, 25, 17 }, 0, NULL },
    { { 494, 25, 14 }, 0, NULL },
    { { 495, 25, 11 }, 0, NULL },
    { { -1, 0, 0 }, 0, NULL },
    { 0 },
    { 0 },
};

/// GX texture data requires 32-byte alignment; the DOL pads 4 bytes before
/// this image to reach 0x803E6E20.
u16 grPu_803E6E20[1024] ATTRIBUTE_ALIGN(32) = {
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
    0xFFFF, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xCE79,
    0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xCE79, 0xCE79, 0xCE79,
    0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79,
    0xCE79, 0xCE79, 0xCE79, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79,
    0xCE79, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
    0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xCE79, 0xCE79,
    0xFFFF, 0xFFFF, 0xCE79, 0xCE79, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79,
    0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79,
    0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79,
    0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79,
    0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79,
    0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79,
    0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79,
    0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79,
    0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79,
    0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79,
    0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79,
    0xCE79, 0xCE79, 0xCE79, 0xFFFF, 0xFFFF, 0xCE79, 0xCE79, 0xFFFF, 0xFFFF,
    0xCE79, 0xCE79, 0xFFFF, 0xFFFF, 0xCE79, 0xCE79, 0xFFFF, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xA534, 0xA534, 0xA534,
    0xA534, 0xA534, 0xA534, 0xA534, 0xA534, 0xA534, 0xA534, 0xA534, 0xA534,
    0xA534, 0xA534, 0xA534, 0xA534, 0xA534, 0xA534, 0xA534, 0xA534, 0xA534,
    0xA534, 0xA534, 0xA534, 0xA534, 0xA534, 0xA534, 0xA534, 0xA534, 0xA534,
    0xA534, 0xA534, 0xA534, 0xA534, 0xA534, 0xA534, 0xA534, 0xA534, 0xA534,
    0xA534, 0xA534, 0xA534, 0xA534, 0xA534, 0xA534, 0xA534, 0xA534, 0xA534,
    0xA534, 0xA534, 0xA534, 0xA534, 0xA534, 0xA534, 0xA534, 0xA534, 0xA534,
    0xA534, 0xA534, 0xA534, 0xA534, 0xA534, 0xA534, 0xA534, 0xA534, 0xA534,
    0xA534, 0xA534, 0xA534, 0xA534, 0xA534, 0xA534, 0xA534, 0xA534, 0xA534,
    0xA534, 0xA534, 0xA534, 0xA534, 0xA534, 0xCE79, 0xCE79, 0xCE79, 0xCE79,
    0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79,
    0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xFFFF, 0xFFFF, 0xCE79, 0xCE79,
    0xFFFF, 0xFFFF, 0xCE79, 0xCE79, 0xFFFF, 0xFFFF, 0xCE79, 0xCE79, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xA534,
    0xA534, 0xA534, 0xA534, 0xA534, 0xA534, 0xA534, 0xA534, 0x8410, 0x8410,
    0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0xA534, 0xA534, 0xA534,
    0xA534, 0xA534, 0xA534, 0xA534, 0xA534, 0x8410, 0x8410, 0x8410, 0x8410,
    0x8410, 0x8410, 0x8410, 0x8410, 0xA534, 0xA534, 0xA534, 0xA534, 0xA534,
    0xA534, 0xA534, 0xA534, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410,
    0x8410, 0x8410, 0xA534, 0xA534, 0xA534, 0xA534, 0xA534, 0xA534, 0xA534,
    0xA534, 0x8410, 0x8410, 0xA534, 0xA534, 0x8410, 0x8410, 0xA534, 0xA534,
    0xA534, 0xA534, 0xA534, 0xA534, 0xA534, 0xA534, 0xA534, 0xA534, 0xA534,
    0xA534, 0xA534, 0xA534, 0xA534, 0xA534, 0xA534, 0xA534, 0xCE79, 0xCE79,
    0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79,
    0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xFFFF, 0xFFFF,
    0xCE79, 0xCE79, 0xFFFF, 0xFFFF, 0xCE79, 0xCE79, 0xFFFF, 0xFFFF, 0xCE79,
    0xCE79, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
    0xFFFF, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410,
    0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410,
    0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410,
    0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410,
    0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410,
    0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0xA534, 0xA534, 0x8410,
    0x8410, 0xA534, 0xA534, 0x8410, 0x8410, 0xA534, 0xA534, 0x8410, 0x8410,
    0xA534, 0xA534, 0xA534, 0xA534, 0xA534, 0xA534, 0xA534, 0xA534, 0xA534,
    0xA534, 0xA534, 0xA534, 0xA534, 0xA534, 0xA534, 0xA534, 0xA534, 0xA534,
    0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79,
    0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79,
    0xFFFF, 0xFFFF, 0xCE79, 0xCE79, 0xFFFF, 0xFFFF, 0xCE79, 0xCE79, 0xFFFF,
    0xFFFF, 0xCE79, 0xCE79, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0x738E, 0x738E, 0x738E, 0x738E, 0x738E, 0x738E,
    0x738E, 0x738E, 0x738E, 0x738E, 0x738E, 0x738E, 0x738E, 0x738E, 0x738E,
    0x738E, 0x738E, 0x738E, 0x738E, 0x738E, 0x738E, 0x738E, 0x738E, 0x738E,
    0x738E, 0x738E, 0x738E, 0x738E, 0x738E, 0x738E, 0x738E, 0x738E, 0x8410,
    0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410,
    0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0xA534,
    0xA534, 0x8410, 0x8410, 0xA534, 0xA534, 0x8410, 0x8410, 0xA534, 0xA534,
    0x8410, 0x8410, 0xA534, 0xA534, 0xA534, 0xA534, 0xA534, 0xA534, 0xA534,
    0xA534, 0xA534, 0xA534, 0xA534, 0xA534, 0xA534, 0xA534, 0xA534, 0xA534,
    0xA534, 0xA534, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79,
    0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79,
    0xCE79, 0xCE79, 0xFFFF, 0xFFFF, 0xCE79, 0xCE79, 0xFFFF, 0xFFFF, 0xCE79,
    0xCE79, 0xFFFF, 0xFFFF, 0xCE79, 0xCE79, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x738E, 0x738E, 0x738E, 0x738E,
    0x738E, 0x738E, 0x738E, 0x738E, 0x738E, 0x738E, 0x738E, 0x738E, 0x738E,
    0x738E, 0x738E, 0x738E, 0x738E, 0x738E, 0x738E, 0x738E, 0x738E, 0x738E,
    0x738E, 0x738E, 0x738E, 0x738E, 0x738E, 0x738E, 0x738E, 0x738E, 0x738E,
    0x738E, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410,
    0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410,
    0x8410, 0xA534, 0xA534, 0x8410, 0x8410, 0xA534, 0xA534, 0x8410, 0x8410,
    0xA534, 0xA534, 0x8410, 0x8410, 0xA534, 0xA534, 0xA534, 0xA534, 0xA534,
    0xA534, 0xA534, 0xA534, 0xA534, 0xA534, 0xA534, 0xA534, 0xA534, 0xA534,
    0xA534, 0xA534, 0xA534, 0xA534, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79,
    0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xCE79,
    0xCE79, 0xCE79, 0xCE79, 0xCE79, 0xFFFF, 0xFFFF, 0xCE79, 0xCE79, 0xFFFF,
    0xFFFF, 0xCE79, 0xCE79, 0xFFFF, 0xFFFF, 0xCE79, 0xCE79, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
};

struct HSD_ImageDesc grPu_803E7620 = { &grPu_803E6E20, 32, 32, 4, 0, 0, 0 };

void stageGObj2_OnInit(Ground_GObj* arg0)
{
    Ground* gp = GET_GROUND(arg0);
    HSD_JObj* jobj = arg0->hsd_obj;
    PAD_STACK(8);
    arg0->render_cb = (GObj_RenderFunc) fn_802130D0;
    HSD_MObjSetToonTextureImage(&grPu_803E7620);
    lb_80011C18(jobj, 0x1000);
    grPura_80213250(jobj);
    HSD_MObjSetToonTextureImage(NULL);
    grAnime_801C8138(arg0, gp->map_id, 0);
}

bool stageGObj2_Callback1(Ground_GObj* arg0)
{
    return false;
}

void stageGObj2_GObjProc(Ground_GObj* arg0)
{
    u32 pad2;
    Vec3 vec;
    Vec3 vec2;
    Ground* gp = GET_GROUND(arg0);
    HSD_JObj* jobj = GET_JOBJ(arg0);
    Quaternion quat;

    HSD_JObjGetTranslation2(gp->u.pura2.xC8, &vec);
    HSD_JObjSetTranslate(jobj, &vec);
    HSD_JObjGetRotation(gp->u.pura2.xC8, &quat);
    HSD_JObjSetRotation(jobj, &quat);
    HSD_JObjGetScale(gp->u.pura2.xC8, &vec2);
    HSD_JObjSetScale(jobj, &vec2);

    if ((HSD_JObjGetFlags(gp->u.pura2.xC8) & 0x10) &&
        ((HSD_JObjGetFlags(jobj) & 0x10) == NULL))
    {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
    } else if (((HSD_JObjGetFlags(gp->u.pura2.xC8) & 0x10) == NULL) &&
               (HSD_JObjGetFlags(jobj) & 0x10))
    {
        HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
    }
}

void stageGObj2_Callback3(Ground_GObj* arg0) {}

void grPura_802125F0(HSD_GObj* arg0)
{
    struct GrPuModelDesc* desc = grPu_803E6AB0;
    f32 scale;
    HSD_JObj* jobj;
    u32 i;
    s32 joint;
    HSD_GObj* gobj;
    Ground* gp;
    HSD_JObj* child;
    HSD_JObj* jobj2;
    HSD_JObj* jobj3;

    for (i = 0; i < 27; i++, desc++) {
        if (desc->x8 != -1) {
            gobj = setupStageCallbacks(desc->x8);
            HSD_ASSERT(0x291, gobj);
            gp = GET_GROUND(gobj);
            HSD_ASSERT(0x292, gp);

            gp->u.pura.xC4 = desc->x0;
            joint = Ground_801C33C0(4, gp->u.pura.xC4);
            gp->u.pura2.xC8 = Ground_801C3FA4(arg0, joint);

            jobj = gobj->hsd_obj;
            HSD_JObjSetTranslateX(jobj,
                                  HSD_JObjGetTranslationX(gp->u.pura2.xC8));
            HSD_JObjSetTranslateY(jobj,
                                  HSD_JObjGetTranslationY(gp->u.pura2.xC8));
            HSD_JObjSetTranslateZ(jobj,
                                  HSD_JObjGetTranslationZ(gp->u.pura2.xC8));

            if (HSD_JObjGetFlags(gp->u.pura2.xC8) & 0x10) {
                HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
            }

            jobj = gobj->hsd_obj;
            if (jobj == NULL) {
                child = NULL;
            } else {
                child = jobj->child;
            }
            HSD_JObjSetTranslateX(child, 0.0f);
            HSD_JObjSetTranslateY(child, 0.0f);
            HSD_JObjSetTranslateZ(child, 0.0f);

            scale = HSD_JObjGetScaleX(jobj2 = gp->u.pura2.xC8);
            if (scale < 2.0f) {
                scale *= desc->x4;
            }
            HSD_JObjSetScaleX(jobj2, scale);
            HSD_JObjSetScaleY(jobj2, scale);
            HSD_JObjSetScaleZ(jobj2, scale);

            HSD_JObjSetScaleX(jobj3 = gobj->hsd_obj, scale);
            HSD_JObjSetScaleY(jobj3, scale);
            HSD_JObjSetScaleZ(jobj3, scale);
        }
    }
}

void grPura_80212CD4(HSD_GObj* arg0)
{
    Ground* gp = arg0->user_data;
    Ground* gp2 = gp;
    HSD_JObj* jobj = HSD_GObjGetHSDObj(arg0);
    s32 i;
    HSD_JObj* node;
    Vec3 subject_pos;

    for (i = 0; 25 > i; i++) {
        gp->u.pura3.xC4[i] = NULL;
        gp->u.pura3.x128[i] = NULL;
    }
    node = HSD_JObjGetChild(jobj);

    if (node != NULL) {
        node = HSD_JObjGetChild(node);
        for (i = 0; i < 25 && node != NULL; i++, node = HSD_JObjGetNext(node))
        {
            if ((gp->u.pura3.x128[i] = Camera_80029020()) != NULL) {
                gp->u.pura3.xC4[i] = node;
                lb_8000B1CC(gp2->u.pura3.xC4[i], NULL, &subject_pos);
                gp->u.pura3.x128[i]->x10 = subject_pos;
                if (HSD_JObjGetFlags(node) & 0x10) {
                    gp->u.pura3.x128[i]->x8 = 1;
                } else {
                    gp->u.pura3.x128[i]->x8 = 0;
                }
                gp->u.pura3.x128[i]->x48.x = 30.0f;
                gp->u.pura3.x128[i]->x48.y = -30.0f;
                gp->u.pura3.x128[i]->x40.x = -30.0f;
                gp->u.pura3.x128[i]->x40.y = 30.0f;
                {
                    CmSubject* subject = gp->u.pura3.x128[i];
                    subject->x2C = subject->x40;
                    subject->x34 = subject->x48;
                }
            }
        }
    }
}

void grPura_80212EF4(HSD_GObj* arg0)
{
    s32 i;
    Ground* gp = arg0->user_data;
    Ground* gp2 = gp;
    Vec3 spC;

    for (i = 0; i < 25; i++) {
        if (gp->u.pura3.xC4[i] != NULL && gp->u.pura3.x128[i] != NULL) {
            lb_8000B1CC(gp2->u.pura3.xC4[i], NULL, &spC);
            gp->u.pura3.x128[i]->x10 = spC;
            if (HSD_JObjGetFlags(gp2->u.pura3.xC4[i]) & 0x10) {
                gp->u.pura3.x128[i]->x8 = 1;
            } else {
                gp->u.pura3.x128[i]->x8 = 0;
            }
        }
    }
}

void grPura_80212FC0(HSD_GObj* arg0)
{
    u32 var_r30;
    for (var_r30 = 0; var_r30 < 0x2A; var_r30++) {
        if (grPu_803E6C0C[var_r30].joint.x != -1) {
            HSD_GObj* temp_r3 =
                Ground_GetMapGObj(grPu_803E6C0C[var_r30].joint.y);
            if (temp_r3 != NULL) {
                grPu_803E6C0C[var_r30].jobj =
                    Ground_801C3FA4(temp_r3, grPu_803E6C0C[var_r30].joint.z);
            }
        }
    }
}

void grPura_80213030(Ground_GObj* arg0)
{
    UNUSED u32 unused1;
    Point3d spC;
    u32 var_r30;

    for (var_r30 = 0; var_r30 < 0x2A; var_r30++) {
        if (grPu_803E6C0C[var_r30].jobj != NULL) {
            lb_8000B1CC(grPu_803E6C0C[var_r30].jobj, NULL, &spC);
            mpVtxSetPos(grPu_803E6C0C[var_r30].joint.x, spC.x, spC.y);
        }
    }
    mpJointUpdateBounding(0);
    mpJointUpdateBounding(9);
    mpJointUpdateBounding(0x18);
    mpJointUpdateBounding(5);
}

DynamicsDesc* grPura_802130C0(enum_t arg0)
{
    return false;
}

bool grPura_802130C8(Vec3* a, int num, HSD_JObj* joint)
{
    return true;
}

void fn_802130D0(HSD_GObj* arg0, int arg1)
{
    PAD_STACK(8);
    HSD_MObjSetToonTextureImage(&grPu_803E7620);
    grDisplay_801C5DB0(arg0, arg1);
    HSD_MObjSetToonTextureImage(0);
}

void grPura_80213128(HSD_DObj* dobj)
{
    HSD_DObj* iter;
    HSD_DObj* next;
    HSD_DObj* next2;

    if ((next = dobj->next) != NULL) {
        if ((next2 = next->next) != NULL) {
            if (next2->next != NULL) {
                grPura_80213128(next2->next);
            }
            for (iter = next2; iter != NULL; iter = iter->next) {
                grPura_80213224(iter);
            }
            if (next2->mobj != NULL) {
                HSD_MObjCompileTev(next2->mobj);
            }
        }
        for (iter = next; iter != NULL; iter = iter->next) {
            if (iter != NULL) {
                HSD_MObjCompileTev(iter->mobj);
            }
        }
        if (next->mobj != NULL) {
            HSD_MObjCompileTev(next->mobj);
        }
    }
    for (iter = dobj; iter != NULL; iter = iter->next) {
        if (iter != NULL) {
            HSD_MObjCompileTev(iter->mobj);
        }
    }
    if (dobj->mobj != NULL) {
        HSD_MObjCompileTev(dobj->mobj);
    }
}

#pragma dont_inline on
void grPura_80213224(HSD_DObj* dobj)
{
    if (dobj != 0) {
        HSD_MObjCompileTev(dobj->mobj);
    }
}
#pragma dont_inline reset

void grPura_80213250(HSD_JObj* jobj)
{
    HSD_JObj* _perm_alias16145 = jobj->child;
    HSD_JObj* child = _perm_alias16145;
    HSD_DObj* sibling_iter;
    HSD_DObj* iter;
    HSD_DObj* next;
    HSD_DObj* sibling_dobj;
    HSD_DObj* dobj;
    HSD_DObj* self_dobj;
    HSD_DObj* self_iter;
    HSD_DObj* self_next;

    if (child != NULL) {
        if (child->child != NULL) {
            grPura_80213250(child->child);
        }
        if (child->next != NULL) {
            grPura_80213250(child->next);
        }
        if (union_type_dobj(child)) {
            if ((dobj = child->u.dobj) != NULL) {
                if (dobj->next != NULL) {
                    grPura_80213128(dobj->next);
                }
                for (iter = dobj; iter != NULL; iter = iter->next) {
                    grPura_80213224(iter);
                }
                if (dobj->mobj != NULL) {
                    HSD_MObjCompileTev(dobj->mobj);
                }
            }
        }
    }

    {
        HSD_JObj* sibling;
        if ((sibling = jobj->next) != NULL) {
            if (sibling->child != NULL) {
                grPura_80213250(sibling->child);
            }
            if (sibling->next != NULL) {
                grPura_80213250(sibling->next);
            }
            if (union_type_dobj(sibling)) {
                if ((sibling_dobj = sibling->u.dobj) != NULL) {
                    if (sibling_dobj->next != NULL) {
                        grPura_80213128(sibling_dobj->next);
                    }
                    for (sibling_iter = sibling_dobj; sibling_iter != NULL;
                         sibling_iter = sibling_iter->next)
                    {
                        grPura_80213224(sibling_iter);
                    }
                    if (sibling_dobj->mobj != NULL) {
                        HSD_MObjCompileTev(sibling_dobj->mobj);
                    }
                }
            }
        }
    }

    if (union_type_dobj(jobj)) {
        if ((self_dobj = jobj->u.dobj) != NULL) {
            if ((self_next = self_dobj->next) != NULL) {
                if (self_next->next != NULL) {
                    grPura_80213128(self_next->next);
                }
                for (self_iter = self_next; self_iter != NULL;
                     self_iter = self_iter->next)
                {
                    grPura_80213224(self_iter);
                }
                if (self_next->mobj != NULL) {
                    HSD_MObjCompileTev(self_next->mobj);
                }
            }
            for (self_iter = self_dobj; self_iter != NULL;
                 self_iter = self_iter->next)
            {
                if (self_iter != NULL) {
                    HSD_MObjCompileTev(self_iter->mobj);
                }
            }
            if (self_dobj->mobj != NULL) {
                HSD_MObjCompileTev(self_dobj->mobj);
            }
        }
    }
}
