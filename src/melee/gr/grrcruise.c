#include "grrcruise.h"

#include "grdatfiles.h"
#include "grdisplay.h"
#include "grlib.h"
#include "ground.h"
#include "grzakogenerator.h"
#include "inlines.h"
#include "math.h"
#include "placeholder.h"
#include "stage.h"
#include "types.h"

#include <platform.h>

#include "baselib/debug.h"
#include "cm/camera.h"
#include "gm/gm_1A45.h"
#include "lb/lb_00B0.h"
#include "lb/lbspdisplay.h"
#include "lb/lbvector.h"
#include "mp/mplib.h"

#include <math_ppc.h>
#include <trigf.h>
#include <baselib/archive.h>
#include <baselib/dobj.h>
#include <baselib/gobj.h>
#include <baselib/gobjproc.h>
#include <baselib/jobj.h>
#include <baselib/random.h>
#include <sysdolphin/baselib/debug.h>
#include <sysdolphin/baselib/memory.h>

struct grRCruise_YakumonoParam {
    f32 x0;
    f32 x4;
    f32 x8;
    s32 xC;
    s32 x10;
    s32 x14;
    s32 x18;
    s32 x1C;
    s32 x20;
    s32 x24;
    s32 x28;
    f32 x2C;
    f32 x30;
    f32 x34;
    f32 x38;
    s32 x3C;
    s32 x40;
    s32 x44;
};

/* 200460 */ static void fn_80200460(void* user_data, int joint_id,
                                     CollData* coll, int coll_x50,
                                     mpLib_GroundEnum ground_kind,
                                     float delta_y);
/* 200578 */ static void grRCruise_80200578(void* user_data, int joint_id,
                                            CollData* coll, int coll_x50,
                                            mpLib_GroundEnum ground_kind,
                                            float delta_y);
/* 2010A4 */ static void grRCruise_802010A4(void* user_data, int joint_id,
                                            CollData* coll, int coll_x50,
                                            mpLib_GroundEnum ground_kind,
                                            float delta_y);

static void sdata2_order(void)
{
    (void) 0.4f;         // 3e cc cc cd
    (void) 0.0f;         // 00 00 00 00
    (void) 1.0471976f;   // 3f 86 0a 92
    (void) -10000.0f;    // c6 1c 40 00
    (void) 10000.0f;     // 46 1c 40 00
    (void) 0.017453292f; // 3c 8e fa 35
    (void) 10.0f;        // 41 20 00 00
    (void) -1.0f;        // bf 80 00 00
    (void) -350.0f;      // c3 af 00 00
    (void) 1.0f;         // 3f 80 00 00
    (void) 1000.0f;      // 44 7a 00 00
}

S16Vec3 grRc_803E4DA8[] = {
    { 0, 1, 1 },   { 1, 1, 1 },   { 2, 1, 1 },   { 3, 1, 1 },   { 4, 1, 1 },
    { 11, 1, 7 },  { 10, 1, 17 }, { 6, 1, 7 },   { 7, 1, 7 },   { 8, 1, 7 },
    { 9, 1, 7 },   { 12, 1, 19 }, { 13, 1, 18 }, { 14, 1, 18 }, { 15, 1, 18 },
    { 16, 1, 18 }, { 17, 1, 18 }, { 18, 1, 18 }, { 19, 1, 18 }, { 20, 1, 18 },
    { 21, 1, 18 }, { 22, 1, 18 }, { 23, 1, 18 },
};

StageCallbacks grRc_803E4E34[7] = {
    { grRCruise_801FF3B4, grRCruise_801FF3E0, grRCruise_801FF3E8,
      grRCruise_801FF3EC, 0 },
    { grRCruise_801FF5B4, grRCruise_801FF6CC, grRCruise_801FF6D4,
      grRCruise_801FF738, 0xC0000000 },
    { grRCruise_801FF3F0, grRCruise_801FF434, grRCruise_801FF43C,
      grRCruise_801FF440, 0 },
    { grRCruise_801FF924, grRCruise_801FFAD4, grRCruise_801FFADC,
      grRCruise_80200070, 0 },
    { grRCruise_80200074, grRCruise_8020014C, grRCruise_80200154,
      grRCruise_8020045C, 0 },
    { grRCruise_801FF73C, grRCruise_801FF794, grRCruise_801FF79C,
      grRCruise_801FF7A0, 0 },
    { grRCruise_801FF7A4, grRCruise_801FF8DC, grRCruise_801FF8E4,
      grRCruise_801FF920, 0 },
};

struct StageData grRc_803E4ECC = {
    RCRUISE,
    grRc_803E4E34,
    "/GrRc.dat",
    grRCruise_801FF168,
    grRCruise_801FF164,
    grRCruise_801FF298,
    grRCruise_801FF29C,
    grRCruise_801FF2C0,
    grRCruise_80201C50,
    grRCruise_80201C58,
    4,
    grRc_803E4DA8,
    ARRAY_SIZE(grRc_803E4DA8),
};

static struct grRCruise_YakumonoParam* yakumono_param;

void grRCruise_801FF164(bool arg) {}

void grRCruise_801FF168(void)
{
    HSD_GObj* jgobj;
    HSD_GObj* grgobj;
    Ground* gp;
    Ground* gp2;
    HSD_JObj* jobj;
    HSD_GObj* gobj6;
    HSD_GObj* gobj1;
    HSD_GObj* gobj4;

    yakumono_param = Ground_GetYakumonoParam();
    stage_info.unk8C.b4 = 1;
    stage_info.unk8C.b5 = 0;
    jgobj = grRCruise_801FF2C8(3);
    gp = GET_GROUND(jgobj);
    gp->u.rcruise.xC4.b0 = 1;
    jobj = GET_JOBJ(jgobj);
    HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
    grgobj = grRCruise_801FF2C8(3);
    gp2 = GET_GROUND(grgobj);
    gp2->u.rcruise2.xEC = jgobj;
    grRCruise_801FF2C8(0);
    grRCruise_801FF2C8(2);
    grRCruise_801FF2C8(5);
    gobj1 = grRCruise_801FF2C8(1);
    gobj6 = grRCruise_801FF2C8(6);
    gobj4 = grRCruise_801FF2C8(4);
    Ground_801C39C0();
    Ground_801C3BB4();
    grRCruise_801FFADC(grgobj);
    Ground_801C2FE0(gobj1);
    Ground_801C32AC(1);
    Ground_801C2FE0(gobj6);
    Ground_801C32AC(6);
    Ground_801C2FE0(gobj4);
    Ground_801C32AC(4);
    mpLib_80057BC0(11);
}

void grRCruise_801FF298(void) {}

void grRCruise_801FF29C(void)
{
    grZakoGenerator_801CAE04(NULL);
}

bool grRCruise_801FF2C0(void)
{
    return false;
}

Ground_GObj* grRCruise_801FF2C8(int gobj_id)
{
    Ground_GObj* gobj;
    StageCallbacks* callbacks = &grRc_803E4E34[gobj_id];

    gobj = Ground_GetStageGObj(gobj_id);

    if (gobj != NULL) {
        Ground_SetupStageCallbacks(gobj, callbacks);
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", __FILE__, 290, gobj_id);
    }

    return gobj;
}

void grRCruise_801FF3B4(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138((HSD_GObj*) gobj, gp->map_id, 0);
}

bool grRCruise_801FF3E0(Ground_GObj* arg)
{
    return false;
}

void grRCruise_801FF3E8(Ground_GObj* arg) {}

void grRCruise_801FF3EC(Ground_GObj* arg) {}

void grRCruise_801FF3F0(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->x11_flags.b012 = 2;
}

bool grRCruise_801FF434(Ground_GObj* arg)
{
    return false;
}

void grRCruise_801FF43C(Ground_GObj* arg) {}

void grRCruise_801FF440(Ground_GObj* arg) {}

void grRCruise_801FF444(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    mpJointSetCb1(5, gobj, grRCruise_80200578);
    mpJointSetCb1(27, gobj, grRCruise_802010A4);
    mpJointSetCb1(36, gobj, grRCruise_802010A4);
    mpJointSetCb1(37, gobj, grRCruise_802010A4);
    mpJointSetCb1(38, gobj, grRCruise_802010A4);
    mpJointSetCb1(39, gobj, grRCruise_802010A4);
    mpJointSetCb1(40, gobj, grRCruise_802010A4);
    mpJointSetCb1(41, gobj, grRCruise_802010A4);
    mpJointSetCb1(42, gobj, grRCruise_802010A4);
    mpJointSetCb1(43, gobj, grRCruise_802010A4);
    mpJointSetCb1(28, gobj, grRCruise_802010A4);
    mpJointSetCb1(29, gobj, grRCruise_802010A4);
    mpJointSetCb1(30, gobj, grRCruise_802010A4);
    mpJointSetCb1(31, gobj, grRCruise_802010A4);
    mpJointSetCb1(32, gobj, grRCruise_802010A4);
    mpJointSetCb1(33, gobj, grRCruise_802010A4);
    mpJointSetCb1(34, gobj, grRCruise_802010A4);
    mpJointSetCb1(35, gobj, grRCruise_802010A4);
    gp->u.rcruise.x10 = 0;
}

void grRCruise_801FF5B4(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);

    Ground_801C2ED0(jobj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->u.rcruise.x10 = 1;
    gp->u.map.chikuwa = HSD_MemAlloc(sizeof(*gp->u.map.chikuwa));
    HSD_ASSERT(410, gp->u.map.chikuwa);
    grRCruise_80201410(gobj);
    Ground_801C10B8(gobj, grRCruise_801FF444);
    grRCruise_80200540(gobj);
    grRCruise_80200B48(gobj);
    Ground_801C2FE0(gobj);
    mpLib_80058560();
    {
        Vec3 pos = { 1.0f, 0.0f, 0.0f };
        gp->u.rcruise.x4 =
            lb_80011A50(&pos, -1, 0.4f, 0.0f, 60 * deg_to_rad, -10000.0f,
                        +10000.0f, +10000.0f, -10000.0f);
        gp->u.rcruise.x8 = deg_to_rad;
        gp->u.rcruise.xC = 1;
    }
}

bool grRCruise_801FF6CC(Ground_GObj* arg)
{
    return false;
}

void grRCruise_801FF6D4(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    if (gp->u.unk.xD4 == 0) {
        grRCruise_80201588(gobj);
        grRCruise_8020071C(gobj);
        grRCruise_80200C04(gobj);
    }
    lb_800115F4();
    grRCruise_80201110(gobj);
    Ground_801C2FE0(gobj);
}

void grRCruise_801FF738(Ground_GObj* arg) {}

void grRCruise_801FF73C(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
    HSD_JObjSetFlagsAll(gobj->hsd_obj, JOBJ_HIDDEN);
    HSD_JObjClearFlagsAll(Ground_801C3FA4(gobj, 31), JOBJ_HIDDEN);
}

bool grRCruise_801FF794(Ground_GObj* arg)
{
    return false;
}

void grRCruise_801FF79C(Ground_GObj* arg) {}

void grRCruise_801FF7A0(Ground_GObj* arg) {}

void grRCruise_801FF7A4(Ground_GObj* gobj)
{
    Ground_GObj* stage_gobj = gobj;
    Ground* gp = GET_GROUND(stage_gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    UnkArchiveStruct* archive;
    DynamicsDesc* data;

    Ground_801C2ED0(jobj, gp->map_id);
    grAnime_801C8138(stage_gobj, gp->map_id, 0);
    grAnime_801C752C(jobj, 1, 30628, HSD_AObjSetFlags, 3, AOBJ_LOOP);
    archive = grDatFiles_GetArchive();
    if (archive != NULL && (data = HSD_ArchiveGetPublicAddress(
                                archive->unk0, "dynamicsdata_shipflag"),
                            data != NULL))
    {
        grLib_801C9B20(Ground_801C3FA4(stage_gobj, 23), data,
                       &gp->u.rcruise2.xC4);
    } else {
        gp->u.rcruise2.xC4.data = NULL;
    }

    jobj = Ground_801C3FA4(stage_gobj, 10);
    if (jobj != NULL) {
        Ground_801C2D0C(0, jobj);
    }
    jobj = Ground_801C3FA4(stage_gobj, 11);
    if (jobj != NULL) {
        Ground_801C2D0C(1, jobj);
    }
    jobj = Ground_801C3FA4(stage_gobj, 12);
    if (jobj != NULL) {
        Ground_801C2D0C(2, jobj);
    }
    jobj = Ground_801C3FA4(stage_gobj, 13);
    if (jobj != NULL) {
        Ground_801C2D0C(3, jobj);
    }
}

bool grRCruise_801FF8DC(Ground_GObj* arg)
{
    return false;
}

void grRCruise_801FF8E4(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grLib_801C9B8C(&gp->u); ///< @todo What
    Ground_801C2FE0(gobj);
}

void grRCruise_801FF920(Ground_GObj* arg) {}

void grRCruise_801FF924(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    PAD_STACK(0x8);

    gp->u.scroll.x38[0] = Ground_801C3FA4(gobj, 4);
    gp->u.scroll.x38[1] = Ground_801C3FA4(gobj, 5);
    gp->u.scroll.x38[2] = Ground_801C3FA4(gobj, 6);
    gp->u.scroll.x44 = Ground_801C3FA4(gobj, 7);
    gp->u.scroll.int_jobj = Ground_801C3FA4(gobj, 3);
    HSD_ASSERT(0x2B0, gp->u.scroll.int_jobj);
    gp->u.scroll.cam_jobj = Ground_801C3FA4(gobj, 2);
    HSD_ASSERT(0x2B2, gp->u.scroll.cam_jobj);

    gp->u.scroll.ctr_jobj = Ground_801C3FA4(gobj, 1);
    HSD_ASSERT(0x2B4, gp->u.scroll.ctr_jobj);

    HSD_JObjGetTranslation(gp->u.scroll.ctr_jobj, &gp->u.scroll.x4);
    gp->u.scroll.x10.z = 0.0F;
    gp->u.scroll.x10.y = 0.0F;
    gp->u.scroll.x10.x = 0.0F;
    gp->u.scroll.x1C.z = 0.0F;
    gp->u.scroll.x1C.y = 0.0F;
    gp->u.scroll.x1C.x = 0.0F;
    gp->u.scroll.x0 = false;
    grAnime_801C8138(gobj, gp->map_id, 0);
    grAnime_801C752C(jobj, 1, 30628, HSD_AObjSetFlags, 3, 0x20000000);
    gobj->render_cb = fn_80201BE0;
}

bool grRCruise_801FFAD4(Ground_GObj* arg)
{
    return false;
}

static inline void grRCruise_801FFADC_inline(HSD_GObj* gobj, Vec3* sp64)
{
    Vec3 sp18;
    Vec3 sp24;
    Vec3 diff;
    Vec3 cam_offset2;
    UNUSED u8 pad[4] = { 0 };

    Ground* anim_gp = GET_GROUND(gobj);
    HSD_JObj* int_jobj = anim_gp->u.scroll.int_jobj;
    HSD_JObj* cam_jobj = anim_gp->u.scroll.cam_jobj;
    Stage_UnkSetVec3TCam_Offset(&cam_offset2);
    lb_8000B1CC(cam_jobj, NULL, &sp18);
    lb_8000B1CC(int_jobj, NULL, &sp24);
    lbVector_Diff(&sp24, &sp18, &diff);
    sp64->x = -(diff.x * (sp18.z / diff.z) - sp18.x);
    sp64->y = -(diff.y * (sp18.z / diff.z) - sp18.y);
    sp64->z = 0.0f;
    lbVector_Sub(sp64, &cam_offset2);
    sp64->y += 10.0f;
}

void grRCruise_801FFADC(Ground_GObj* arg0)
{
    Vec3 sp64;
    UNUSED Vec3 pad58;
    Vec3 cam_offset;
    Ground* gp;
    HSD_GObj* gobj;
    HSD_JObj* temp_r29_2;

    gp = GET_GROUND(arg0);
    if (!gp->u.scroll.x0) {
        Stage_UnkSetVec3TCam_Offset(&cam_offset);
        HSD_ASSERT(0x2E0, gp->u.scroll.anim_gobj);
        grRCruise_801FFADC_inline(gp->u.scroll.anim_gobj, &sp64);
        lbVector_Diff(&gp->u.scroll.x10, &sp64, &gp->u.scroll.x1C);
        gp->u.scroll.x10 = sp64;
        sp64.x *= -1.0f;
        sp64.y *= -1.0f;
        sp64.z *= -1.0f;
        lbVector_Add(&sp64, &cam_offset);
        if ((temp_r29_2 = arg0->hsd_obj) != NULL) {
            HSD_JObjSetTranslate(temp_r29_2, &sp64);
            HSD_JObjAddTranslationZ(temp_r29_2, -350.0f * Ground_801C0498());
        }
        gobj = Ground_801C2BA4(2);
        if (gobj != NULL) {
            HSD_JObj* jobj;
            if ((jobj = gobj->hsd_obj) != NULL) {
                HSD_JObjSetTranslate(jobj, &sp64);
            }
        }
        gobj = Ground_801C2BA4(1);
        if (gobj != NULL) {
            HSD_JObj* jobj;
            if ((jobj = gobj->hsd_obj) != NULL) {
                HSD_JObjSetTranslate(jobj, &sp64);
            }
        }
        gobj = Ground_801C2BA4(5);
        if (gobj != NULL) {
            HSD_JObj* jobj;
            if ((jobj = gobj->hsd_obj) != NULL) {
                HSD_JObjSetTranslate(jobj, &sp64);
            }
        }
        gobj = Ground_801C2BA4(6);
        if (gobj != NULL) {
            HSD_JObj* jobj;
            if ((jobj = gobj->hsd_obj) != NULL) {
                HSD_JObjSetTranslate(jobj, &sp64);
            }
        }
        gobj = Ground_801C2BA4(4);
        if (gobj != NULL) {
            HSD_JObj* jobj;
            if ((jobj = gobj->hsd_obj) != NULL) {
                HSD_JObjSetTranslate(jobj, &sp64);
            }
        }
    }
}

void grRCruise_80200070(Ground_GObj* arg) {}

static s16 grRc_804D4790[] = {
    0x01,
    0x1A,
    0x33,
};

void grRCruise_80200074(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    int i;

    Ground_801C2ED0(jobj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 0);
    for (i = 0; i < 3; i++) {
        grAnime_801C8098(gobj, grRc_804D4790[i], 7, 1, 0.0F, 0.0F);
        gp->u.rcruise.x3C[i].x2 =
            Ground_801C32D4(gp->map_id, grRc_804D4790[i]);
        mpJointSetCb1(gp->u.rcruise.x3C[i].x2, gobj, fn_80200460);
        gp->u.rcruise.x3C[i].xC = Ground_801C3FA4(gobj, grRc_804D4790[i]);
        gp->u.rcruise.x3C[i].x8 = 0;
        gp->u.rcruise.x3C[i].x4 = 0;
        gp->u.rcruise.x3C[i].x0 = 0;
    }
}

bool grRCruise_8020014C(Ground_GObj* arg)
{
    return false;
}

void grRCruise_80200154(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    Ground* gp2 = gp;
    int i;

    for (i = 0; i < 3; i++) {
        switch (gp->u.rcruise.x3C[i].x0) {
        case 0:
            mpJointListAdd(gp2->u.rcruise.x3C[i].x2);
            grRCruise_80201B60(gp2->u.rcruise.x3C[i].xC->child, 1);
            gp->u.rcruise.x3C[i].x4 = 0;
            gp->u.rcruise.x3C[i].x0 = 1;
            break;
        case 2:
            if (gp->u.rcruise.x3C[i].x8 == 0) {
                gp->u.rcruise.x3C[i].x4 = 0;
                grAnime_801C7A94(gobj, grRc_804D4790[i], 1, 0.0F);
                gp->u.rcruise.x3C[i].x0 = 3;
            } else if (grAnime_801C83D0(gobj, grRc_804D4790[i], 7) != 0) {
                gp->u.rcruise.x3C[i].x4 = 0;
                gp->u.rcruise.x3C[i].x0 = 5;
            }
            break;
        case 3:
            if (gp->u.rcruise.x3C[i].x4 >= yakumono_param->xC) {
                gp->u.rcruise.x3C[i].x4 = 0;
                gp->u.rcruise.x3C[i].x1_b0 = 0;
                gp->u.rcruise.x3C[i].x0 = 4;
            }
            gp->u.rcruise.x3C[i].x4++;
            break;
        case 4:
            if (gp->u.rcruise.x3C[i].x4 % yakumono_param->x14 == 0) {
                gp->u.rcruise.x3C[i].x1_b0 ^= 1;
                if (gp->u.rcruise.x3C[i].x1_b0) {
                    grRCruise_80201B60(gp2->u.rcruise.x3C[i].xC->child, 0);
                } else {
                    grRCruise_80201B60(gp2->u.rcruise.x3C[i].xC->child, 1);
                }
            }
            if (gp->u.rcruise.x3C[i].x4 >= yakumono_param->x10) {
                mpLib_80057BC0(gp2->u.rcruise.x3C[i].x2);
                grRCruise_80201B60(gp2->u.rcruise.x3C[i].xC->child, 0);
                grAnime_801C7BA0(gobj, grRc_804D4790[i], 1, 0.0F);
                grAnime_801C7A94(gobj, grRc_804D4790[i], 1, 0.0F);
                mpLib_80055E9C(gp2->u.rcruise.x3C[i].x2);
                mpLib_80057424(gp2->u.rcruise.x3C[i].x2);
                gp->u.rcruise.x3C[i].x0 = 0;
            }
            gp->u.rcruise.x3C[i].x4++;
            break;
        case 5:
            if (gp->u.rcruise.x3C[i].x4 % yakumono_param->x1C == 0) {
                grRCruise_80201B60(gp2->u.rcruise.x3C[i].xC->child, 0);
            } else {
                grRCruise_80201B60(gp2->u.rcruise.x3C[i].xC->child, 1);
            }
            if (gp->u.rcruise.x3C[i].x4 >= yakumono_param->x18) {
                mpLib_80057BC0(gp2->u.rcruise.x3C[i].x2);
                grRCruise_80201B60(gp2->u.rcruise.x3C[i].xC->child, 0);
                grAnime_801C7BA0(gobj, grRc_804D4790[i], 1, 0.0F);
                grAnime_801C7A94(gobj, grRc_804D4790[i], 1, 0.0F);
                mpLib_80055E9C(gp2->u.rcruise.x3C[i].x2);
                mpLib_80057424(gp2->u.rcruise.x3C[i].x2);
                gp->u.rcruise.x3C[i].x0 = 0;
            }
            gp->u.rcruise.x3C[i].x4++;
            break;
        }
        gp->u.rcruise.x3C[i].x8 = 0;
    }
    Ground_801C2FE0(gobj);
}

void grRCruise_8020045C(Ground_GObj* arg) {}

/// @copydoc mpLib_JointCollisionCallback
void fn_80200460(void* user_data, int joint_id, CollData* coll, int coll_x50,
                 mpLib_GroundEnum ground_kind, float delta_y)
{
    HSD_GObj* gobj = user_data;
    Ground* gp1 = HSD_GObjGetUserData(gobj); ///< @todo weird regswap
    int i;
    PAD_STACK(16);

    if ((s32) coll->x34_flags.b1234 == 1) {
        for (i = 0; i < 3; i++) {
            if (gp1->u.rcruise.x3C[i].x2 == joint_id) {
                u8 state = gp1->u.rcruise.x3C[i].x0;
                if (state == 1 || state == 3 || state == 4) {
                    gp1->u.rcruise.x3C[i].x4 = 0;
                    grRCruise_80201B60(gp1->u.rcruise.x3C[i].xC->child, 1);
                    grAnime_801C7A94(gobj, grRc_804D4790[i], 1, 1.0f);
                    gp1->u.rcruise.x3C[i].x0 = 2;
                }
                gp1->u.rcruise.x3C[i].x8++;
                break;
            }
        }
    }
}

void grRCruise_80200540(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    gp->u.rcruise.x18 = 0.0F;
    gp->u.rcruise.x14 = 0.0F;
    gp->u.rcruise.x1C = 0.0F;
    gp->u.rcruise.x20 = 0.0F;
    gp->u.rcruise.x34 = 0;
    gp->u.rcruise.x30 = 0;
    gp->u.rcruise.x28 = 0.0F;
    gp->u.rcruise.x24 = 0.0F;
    gp->u.rcruise.x38 = 0;
    gp->u.rcruise.x2C = 0;
}

/// @copydoc mpLib_JointCollisionCallback
void grRCruise_80200578(void* user_data, int joint_id, CollData* coll,
                        int coll_x50, mpLib_GroundEnum ground_kind,
                        float delta_y)
{
    PAD_STACK(8);
    {
        Vec3 pos;
        HSD_GObj* gobj = (HSD_GObj*) user_data;
        Ground* gp = HSD_GObjGetUserData(gobj);
        HSD_JObj* jobj = Ground_801C3FA4(gobj, 8);
        f32 dx;
        f32 dy;
        f32 dist;
        PAD_STACK(8);

        if ((s32) coll->x34_flags.b1234 != 1 &&
            (s32) coll->x34_flags.b1234 != 2 &&
            (s32) coll->x34_flags.b1234 != 3)
        {
            return;
        }

        if (coll_x50 > 1000.0f) {
            coll_x50 = 1000;
        }
        lb_8000B1CC(jobj, NULL, &pos);
        dx = pos.x - coll->cur_pos.x;
        dy = pos.y - coll->cur_pos.y;
        dist = sqrtf(dy * dy + dx * dx);
        if (dist > 4.0f) {
            if (pos.x < coll->cur_pos.x) {
                gp->u.rcruise.x24 += dist * (coll_x50 / 1000.0f);
            } else {
                gp->u.rcruise.x28 += dist * (coll_x50 / 1000.0f);
            }
        }
        gp->u.rcruise.x34++;
    }
}

void grRCruise_8020071C(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = Ground_801C3FA4(gobj, 8);
    HSD_JObj* jobj5 = Ground_801C3FA4(Ground_801C2BA4(5), 8);
    f32 abs_rot = ABS(gp->u.rcruise.x18);
    f32 wrapped = abs_rot - (360.0f * (s32) (abs_rot / 360.0f));

    switch (gp->u.rcruise.x2C) {
    case 0:
        if (gp->u.rcruise.x34 == 0) {
            gp->u.rcruise.x1C = gp->u.rcruise.x18 < 0.0f ? 1 : -1;
            gp->u.rcruise.x20 = yakumono_param->x8 * gp->u.rcruise.x1C;
            if (wrapped <= 0.2f) {
                gp->u.rcruise.x20 = 0.0f;
                gp->u.rcruise.x2C = 0;
            }
        } else if (gp->u.rcruise.x24 < gp->u.rcruise.x28) {
            gp->u.rcruise.x1C = 1.0f;
            gp->u.rcruise.x20 =
                yakumono_param->x0 * (gp->u.rcruise.x28 - gp->u.rcruise.x24);
            if (gp->u.rcruise.x20 >= yakumono_param->x4) {
                gp->u.rcruise.x20 = yakumono_param->x4;
            }
        } else {
            gp->u.rcruise.x1C = -1.0f;
            gp->u.rcruise.x20 =
                -yakumono_param->x0 * (gp->u.rcruise.x24 - gp->u.rcruise.x28);
            if (gp->u.rcruise.x20 <= -yakumono_param->x4) {
                gp->u.rcruise.x20 = -yakumono_param->x4;
            }
        }
        break;
    case 1:
        if (gp->u.rcruise.x38 == 0) {
            if (gp->u.rcruise.x34 == 0) {
                gp->u.rcruise.x1C = gp->u.rcruise.x18 < 0.0f ? 1 : -1;
                gp->u.rcruise.x20 = yakumono_param->x8 * gp->u.rcruise.x1C;
                if (wrapped <= 0.2f) {
                    gp->u.rcruise.x20 = 0.0f;
                    gp->u.rcruise.x2C = 0;
                }
            } else {
                gp->u.rcruise.x2C = 0;
            }
        } else {
            gp->u.rcruise.x38--;
            gp->u.rcruise.x20 += 0.008f * -gp->u.rcruise.x1C;
            if ((gp->u.rcruise.x20 < 0.0f ? -gp->u.rcruise.x20
                                          : gp->u.rcruise.x20) <= 0.008f)
            {
                gp->u.rcruise.x20 = 0.0f;
            }
        }
        break;
    }
    gp->u.rcruise.x18 += gp->u.rcruise.x20;
    HSD_JObjSetRotationZ(jobj, 0.017453292f * gp->u.rcruise.x18);
    HSD_JObjSetRotationZ(jobj5, 0.017453292f * gp->u.rcruise.x18);
    gp->u.rcruise.x30 = gp->u.rcruise.x34;
    gp->u.rcruise.x34 = 0;
    gp->u.rcruise.x28 = 0.0f;
    gp->u.rcruise.x24 = 0.0f;
}

s16 grRc_803E4FF0[] = {
    0x20, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30,
    0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28,
};

struct Map_VanishDesc lbl_803E5014[] = {
    { 6, 4, false },  { 8, 5, false },  { 16, 10, false }, { 11, 6, false },
    { 12, 7, false }, { 13, 8, false }, { 14, 9, false },  { 15, 8, false },
    { 19, 12, true }, { 20, 13, true }, { 21, 14, true },  { 30, 15, true },
    { 22, 16, true }, { 23, 17, true }, { 24, 18, true },  { 25, 19, true },
    { 26, 20, true }, { 27, 21, true }, { 28, 22, true },  { 29, 23, true },
};

void grRCruise_80200B48(Ground_GObj* gobj)
{
    Ground* gp;
    HSD_JObj* jobj;
    struct grRCruise_Entry* entry;
    s32 i;

    gp = gobj->user_data;
    for (i = 0; i < (signed) ARRAY_SIZE(grRc_803E4FF0); i++) {
        entry = &gp->u.rcruise.entries[i];
        entry->x2 = Ground_801C32D4(gp->map_id, grRc_803E4FF0[i]);
        entry->x14 = Ground_801C3FA4(gobj, grRc_803E4FF0[i]);
        entry->x8 = 0;
        entry->x4 = 0;
        entry->xC = HSD_JObjGetTranslationY(jobj = entry->x14);
        entry->x0 = 0;
    }
}

void grRCruise_80200C04(Ground_GObj* gobj)
{
    struct grRCruise_EntryFlags {
        u8 b0 : 1;
        u8 b1 : 1;
        u8 b2 : 1;
        u8 b3 : 1;
        u8 b4 : 1;
        u8 b5 : 1;
        u8 b6 : 1;
        u8 b7 : 1;
    };
    Ground* gp;
    int i;

    gp = HSD_GObjGetUserData(gobj);
    for (i = 0; i < (ssize_t) ARRAY_SIZE(grRc_803E4FF0); i++) {
        struct grRCruise_Entry* entry = &gp->u.rcruise.entries[i];

        switch (entry->x0) {
        case 1:
            if (entry->x8 == 0) {
                entry->x4 = 0;
                entry->x0 = 0;
            } else if (entry->x4 >= yakumono_param->x20) {
                entry->x0 = 2;
            } else {
                entry->x4++;
            }
            break;
        case 2:
            if ((entry->x4 % yakumono_param->x28) == 0) {
                f32 range =
                    100.0f * (yakumono_param->x30 - yakumono_param->x2C);
                s32 randi = (s32) range != 0 ? HSD_Randi(range) : 0;
                HSD_JObjSetTranslateY(
                    entry->x14,
                    entry->xC + (yakumono_param->x2C + (randi / 100.0f)));
            }
            if (entry->x4 >= yakumono_param->x24) {
                entry->x10 = 0.0f;
                entry->x0 = 3;
            }
            entry->x4++;
            break;
        case 3:
            entry->x10 -= yakumono_param->x34;
            if ((entry->x10 < 0.0f ? -entry->x10 : entry->x10) >
                yakumono_param->x38)
            {
                entry->x10 = -yakumono_param->x38;
            }
            HSD_JObjAddTranslationY(entry->x14, entry->x10);
            if (HSD_JObjGetTranslationY(entry->x14) <=
                Stage_GetCamBoundsBottomOffset())
            {
                entry->x10 = 0.0f;
                grRCruise_80201B60(entry->x14, 0);
                mpLib_80057BC0(entry->x2);
                entry->x4 = 0;
                entry->x0 = 4;
            }
            break;
        case 4:
            if (entry->x4 >= yakumono_param->x3C) {
                HSD_JObjSetTranslateY(entry->x14, entry->xC);
                mpLib_80055E9C(entry->x2);
                mpLib_80057424(entry->x2);
                grRCruise_80201B60(entry->x14, 1);
                mpJointListAdd(entry->x2);
                entry->x4 = 0;
                ((struct grRCruise_EntryFlags*) &entry->pad_01)->b0 = 0;
                entry->x0 = 5;
            }
            entry->x4++;
            break;
        case 5:
            if ((entry->x4 % yakumono_param->x44) == 0) {
                ((struct grRCruise_EntryFlags*) &entry->pad_01)->b0 =
                    ((struct grRCruise_EntryFlags*) &entry->pad_01)->b0 ^ 1;
                if (((struct grRCruise_EntryFlags*) &entry->pad_01)->b0) {
                    grRCruise_80201B60(entry->x14, 0);
                } else {
                    grRCruise_80201B60(entry->x14, 1);
                }
            }
            if (entry->x4 >= yakumono_param->x40) {
                grRCruise_80201B60(entry->x14, 1);
                entry->x4 = 0;
                entry->x0 = 0;
            }
            entry->x4++;
            break;
        }
        entry->x8 = 0;
    }
}

/// @copydoc mpLib_JointCollisionCallback
void grRCruise_802010A4(void* user_data, int joint_id, CollData* coll,
                        int coll_x50, mpLib_GroundEnum ground_kind,
                        float delta_y)
{
    Ground* gp = HSD_GObjGetUserData(user_data); ///< @todo weird regswap
    s32 i;

    if ((s32) coll->x34_flags.b1234 != 1) {
        return;
    }

    for (i = 0; i < 17; i++) {
        struct grRCruise_Entry* entry = &gp->u.rcruise.entries[i];
        if (entry->x2 == joint_id) {
            if (entry->x0 == 0) {
                entry->x4 = 0;
                entry->x0 = 1;
            }
            entry->x8++;
            break;
        }
    }
}

void grRCruise_80201110(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    f32 angle = atan2f(gp->u.rcruise.x4->x4.z, gp->u.rcruise.x4->x4.x);
    angle += gp->u.rcruise.x8;

    if (angle > 1.0471975430846214) {
        angle = 1.0471976f;
    }
    if (angle < -1.0471975430846214) {
        angle = -1.0471976f;
    }
    gp->u.rcruise.x4->x4.x = cosf(angle);
    gp->u.rcruise.x4->x4.z = sinf(angle);
    if (gp->u.rcruise.x4->unk_angle_int % 30 == 0 && HSD_Randf() > 0.5) {
        gp->u.rcruise.x8 = -gp->u.rcruise.x8;
    }
    if (gp->u.rcruise.x4->unk_angle_int % 300 == 0) {
        if (gp->u.rcruise.xC != 0) {
            gp->u.rcruise.xC = 0;
        } else if (HSD_Randf() > 0.5) {
            gp->u.rcruise.xC = 1;
        }
    }
    if (gp->u.rcruise.xC != 0) {
        gp->u.rcruise.x4->unk_scale = 0.3 * HSD_Randf() + 0.2;
    } else {
        gp->u.rcruise.x4->unk_scale = 0.2 * HSD_Randf() + 0.1;
    }
}

static inline struct HSD_DObj* grRCruise_80201288_inline(HSD_JObj* arg0)
{
    return HSD_JObjGetDObj(arg0);
}

void grRCruise_80201288(HSD_JObj* jobj, void (*callback)(HSD_DObj*, u32),
                        u32 flags)
{
    HSD_DObj* temp_r3;
    HSD_DObj* temp_r3_2;
    HSD_DObj* temp_r3_3;
    HSD_JObj* tmp;
    HSD_JObj* var_r29;
    HSD_JObj* var_r29_2;
    HSD_JObj* var_r3;
    HSD_JObj* var_r3_2;
    HSD_JObj* var_r3_3;
    HSD_JObj* var_r3_4;
    HSD_JObj* tmp2;
    if (jobj != NULL) {
        temp_r3 = grRCruise_80201288_inline(jobj);
        if (temp_r3 != NULL) {
            callback(temp_r3, flags);
        }
        if (jobj == NULL) {
            var_r29 = NULL;
        } else {
            var_r29 = jobj->child;
        }
        if (((tmp = var_r29) != 0L) && (tmp != 0L)) {
            temp_r3_2 = grRCruise_80201288_inline(tmp);
            if (temp_r3_2 != NULL) {
                callback(temp_r3_2, flags);
            }
            if (var_r29 == NULL) {
                var_r3 = NULL;
            } else {
                var_r3 = (tmp2 = tmp->child);
            }
            if (var_r3 != NULL) {
                grRCruise_80201288(var_r3, callback, flags);
            }
            if (tmp == NULL) {
                var_r3_2 = NULL;
            } else {
                var_r3_2 = tmp->next;
            }
            if (var_r3_2 != NULL) {
                grRCruise_80201288(var_r3_2, callback, flags);
            }
        }
        if (jobj == NULL) {
            var_r29_2 = NULL;
        } else {
            var_r29_2 = jobj->next;
        }
        if ((var_r29_2 != NULL) && (var_r29_2 != NULL)) {
            temp_r3_3 = grRCruise_80201288_inline(var_r29_2);
            if (temp_r3_3 != NULL) {
                callback(temp_r3_3, flags);
            }
            if (var_r29_2 == NULL) {
                var_r3_3 = NULL;
            } else {
                var_r3_3 = var_r29_2->child;
            }
            if (var_r3_3 != NULL) {
                grRCruise_80201288(var_r3_3, callback, flags);
            }
            if (var_r29_2 == NULL) {
                var_r3_4 = NULL;
            } else {
                var_r3_4 = var_r29_2->next;
            }
            if (var_r3_4 != NULL) {
                grRCruise_80201288(var_r3_4, callback, flags);
            }
        }
    }
}

static inline void set_hidden_a(int i)
{
    int joint = lbl_803E5014[i].x0;
    HSD_GObj* gobj5 = Ground_801C2BA4(5);
    if (gobj5 != NULL) {
        HSD_GObj* gobj1 = Ground_801C2BA4(1);
        if (gobj1 != NULL) {
            HSD_JObj* jobj = Ground_801C3FA4(gobj5, joint);
            if (jobj != NULL) {
                HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
            }
            jobj = Ground_801C3FA4(gobj1, joint);
            if (jobj != NULL) {
                grRCruise_80201288(jobj, HSD_DObjSetFlags, DOBJ_HIDDEN);
            }
        }
    }
}

static inline void set_hidden_b(int i)
{
    int joint = lbl_803E5014[i].x0;
    HSD_GObj* gobj5 = Ground_801C2BA4(5);
    if (gobj5 != NULL) {
        HSD_GObj* gobj1 = Ground_801C2BA4(1);
        if (gobj1 != NULL) {
            HSD_JObj* jobj = Ground_801C3FA4(gobj5, joint);
            if (jobj != NULL) {
                HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
            }
            jobj = Ground_801C3FA4(gobj1, joint);
            if (jobj != NULL) {
                grRCruise_80201288(jobj, HSD_DObjClearFlags, DOBJ_HIDDEN);
            }
        }
    }
}

void grRCruise_80201410(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    int i;

    gp->u.map.vanish = HSD_MemAlloc(sizeof(lbl_803E5014));
    HSD_ASSERT(1453, gp->u.map.vanish);

    for (i = 0; i < ARRAY_SIZE(lbl_803E5014); i++) {
        gp->u.map.vanish[i].jobj = Ground_801C3FA4(gobj, lbl_803E5014[i].x0);
        HSD_ASSERT(1459, gp->u.map.vanish[i].jobj);
        if (lbl_803E5014[i].x4 != 0) {
            gp->u.map.vanish[i].x0 = 2;
            set_hidden_a(i);
            mpJointListAdd(lbl_803E5014[i].x2);
        } else {
            gp->u.map.vanish[i].x0 = 0;
            grAnime_801C7FF8(gobj, lbl_803E5014[i].x0, 2, 1, 0.0f, 1.0f);
            mpLib_80057BC0(lbl_803E5014[i].x2);
        }
    }
}

void grRCruise_80201588(Ground_GObj* gobj)
{
    Point3d pos;
    Ground* gp = GET_GROUND(gobj);
    int i;

    HSD_ASSERT(0x5D6, gp->u.map.vanish);

    for (i = 0; i < ARRAY_SIZE(lbl_803E5014); i++) {
        if (lbl_803E5014[i].x4 != 0) {
            continue;
        }
        switch (gp->u.map.vanish[i].x0) {
        case 0:
            lb_8000B1CC(gp->u.map.vanish[i].jobj, NULL, &pos);
            if (Camera_8003118C(&pos, -20.0f) != 0) {
                gp->u.map.vanish[i].x0 = 1;
                grAnime_801C7FF8(gobj, lbl_803E5014[i].x0, 2, 2, 0.0f, 1.0f);
                mpJointListAdd(lbl_803E5014[i].x2);
                mpLib_80055E9C(lbl_803E5014[i].x2);
                mpLib_80057424(lbl_803E5014[i].x2);
            }
            break;
        case 1:
            if (grAnime_801C83D0(gobj, lbl_803E5014[i].x0, 2) != 0) {
                gp->u.map.vanish[i].x0 = 2;
                set_hidden_a(i);
            }
            break;
        case 2:
            lb_8000B1CC(gp->u.map.vanish[i].jobj, NULL, &pos);
            if (Camera_8003118C(&pos, -20.0f) == 0) {
                gp->u.map.vanish[i].x0 = 3;
                grAnime_801C7FF8(gobj, lbl_803E5014[i].x0, 2, 3, 0.0f, 1.0f);
                set_hidden_b(i);
            }
            break;
        case 3:
            if (grAnime_801C83D0(gobj, lbl_803E5014[i].x0, 2) != 0) {
                int j;
                gp->u.map.vanish[i].x0 = 0;
                grAnime_801C7FF8(gobj, lbl_803E5014[i].x0, 2, 1, 0.0f, 1.0f);
                for (j = 0; j < ARRAY_SIZE(lbl_803E5014); j++) {
                    if (lbl_803E5014[j].x2 == lbl_803E5014[i].x2 &&
                        gp->u.map.vanish[j].x0 != 0)
                    {
                        break;
                    }
                }
                if (j == ARRAY_SIZE(lbl_803E5014)) {
                    mpLib_80057BC0(lbl_803E5014[i].x2);
                }
            }
            break;
        }
    }
}

void grRCruise_80201918(Vec3* vec)
{
    HSD_GObj* gobj = Ground_801C2BA4(3);
    if (gobj != NULL) {
        Ground* gp = GET_GROUND(gobj);
        if (gp != NULL) {
            *vec = gp->u.scroll.x1C;
            return;
        }
    }
    vec->x = vec->y = vec->z = 0.0f;
}

bool grRCruise_80201988(s32 line_id)
{
    if (stage_info.internal_stage_id == RCRUISE && line_id != -1) {
        int joint = mpJointFromLine(line_id);
        bool result;

        result = joint == 0x1B || joint == 0x24 || joint == 0x25 ||
                 joint == 0x26 || joint == 0x27 || joint == 0x28 ||
                 joint == 0x29 || joint == 0x2A || joint == 0x2B ||
                 joint == 0x1C || joint == 0x1D || joint == 0x1E ||
                 joint == 0x1F || joint == 0x20 || joint == 0x21 ||
                 joint == 0x22 || joint == 0x23;
        if (result) {
            return true;
        }
    }
    return false;
}

void grRCruise_80201B60(HSD_JObj* jobj, bool clear)
{
    HSD_DObj* dobj = HSD_JObjGetDObj(jobj);
    PAD_STACK(4);

    while (dobj != NULL) {
        if (clear) {
            HSD_DObjClearFlags(dobj, DOBJ_HIDDEN);
        } else {
            HSD_DObjSetFlags(dobj, DOBJ_HIDDEN);
        }
        dobj = dobj != NULL ? dobj->next : NULL;
    }
}

void fn_80201BE0(HSD_GObj* gobj, int pass)
{
    if (gm_801A45E8(1) || gm_801A45E8(2) || Camera_8003010C()) {
        return;
    }
    grDisplay_801C5DB0(gobj, pass);
}

DynamicsDesc* grRCruise_80201C50(enum_t arg)
{
    return NULL;
}

bool grRCruise_80201C58(Vec3* arg, int arg0, HSD_JObj* jobj)
{
    return true;
}
