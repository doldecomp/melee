#include "grrcruise.h"

#include "grzakogenerator.h"
#include "placeholder.h"

#include <platform.h>

#include "baselib/debug.h"
#include "cm/camera.h"

#include "forward.h"

#include "gm/gm_1A45.h"
#include "gr/grdatfiles.h"
#include "gr/grdisplay.h"
#include "gr/grlib.h"
#include "gr/ground.h"
#include "gr/inlines.h"
#include "gr/stage.h"
#include "gr/types.h"

#include "lb/forward.h"

#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "lb/lbvector.h"
#include "mp/mplib.h"
#include "sysdolphin/baselib/debug.h"
#include "sysdolphin/baselib/memory.h"

#include <math.h>
#include <baselib/archive.h>
#include <baselib/dobj.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>
#include <baselib/jobj.h>
#include <baselib/random.h>
#include <MSL/math_ppc.h>
#include <MSL/trigf.h>

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

#define grRc_803E5014 \
    (*(struct grRCruise_VanishDesc*) ((u8*) grRc_803E4DA8 + 0x26C))
extern Vec3 grRc_803B8288;
extern s16 grRc_803E4FF0[];
extern s16 grRc_804D4790[4];
const f32 grRc_804DB644;

static struct {
    f32 x0;
    f32 x4;
    f32 x8;
    s32 x0C;
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
}* grRc_804D6A10;

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

    grRc_804D6A10 = Ground_801C49F8();
    stage_info.unk8C.b4 = 1;
    stage_info.unk8C.b5 = 0;
    jgobj = grRCruise_801FF2C8(3);
    gp = GET_GROUND(jgobj);
    gp->gv.rcruise.xC4.b0 = 1;
    jobj = GET_JOBJ(jgobj);
    HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
    grgobj = grRCruise_801FF2C8(3);
    gp2 = GET_GROUND(grgobj);
    gp2->gv.rcruise2.xEC = jgobj;
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

HSD_GObj* grRCruise_801FF2C8(int gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grRc_803E4E34[gobj_id];

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
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", __FILE__, 0x122,
                 gobj_id);
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
    mpJointSetCb1(27, gobj, (mpLib_Callback) (Event) grRCruise_802010A4);
    mpJointSetCb1(36, gobj, (mpLib_Callback) (Event) grRCruise_802010A4);
    mpJointSetCb1(37, gobj, (mpLib_Callback) (Event) grRCruise_802010A4);
    mpJointSetCb1(38, gobj, (mpLib_Callback) (Event) grRCruise_802010A4);
    mpJointSetCb1(39, gobj, (mpLib_Callback) (Event) grRCruise_802010A4);
    mpJointSetCb1(40, gobj, (mpLib_Callback) (Event) grRCruise_802010A4);
    mpJointSetCb1(41, gobj, (mpLib_Callback) (Event) grRCruise_802010A4);
    mpJointSetCb1(42, gobj, (mpLib_Callback) (Event) grRCruise_802010A4);
    mpJointSetCb1(43, gobj, (mpLib_Callback) (Event) grRCruise_802010A4);
    mpJointSetCb1(28, gobj, (mpLib_Callback) (Event) grRCruise_802010A4);
    mpJointSetCb1(29, gobj, (mpLib_Callback) (Event) grRCruise_802010A4);
    mpJointSetCb1(30, gobj, (mpLib_Callback) (Event) grRCruise_802010A4);
    mpJointSetCb1(31, gobj, (mpLib_Callback) (Event) grRCruise_802010A4);
    mpJointSetCb1(32, gobj, (mpLib_Callback) (Event) grRCruise_802010A4);
    mpJointSetCb1(33, gobj, (mpLib_Callback) (Event) grRCruise_802010A4);
    mpJointSetCb1(34, gobj, (mpLib_Callback) (Event) grRCruise_802010A4);
    mpJointSetCb1(35, gobj, (mpLib_Callback) (Event) grRCruise_802010A4);
    gp->gv.rcruise.x10 = 0;
}

void grRCruise_801FF5B4(Ground_GObj* gobj)
{
    Vec3 pos;
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);

    Ground_801C2ED0(jobj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->gv.rcruise.x10 = 1;
    gp->u.map.chikuwa = HSD_MemAlloc(0x198);
    HSD_ASSERT(0x19A, gp->u.map.chikuwa);
    grRCruise_80201410(gobj);
    Ground_801C10B8(gobj, grRCruise_801FF444);
    grRCruise_80200540(gobj);
    grRCruise_80200B48(gobj);
    Ground_801C2FE0(gobj);
    mpLib_80058560();
    pos = grRc_803B8288;
    gp->gv.rcruise.x04 = lb_80011A50(&pos, -1, 0.4f, 0.0f, 1.0471976f,
                                     -10000.0f, 10000.0f, 10000.0f, -10000.0f);
    gp->gv.rcruise.x08 = 0.017453292f;
    gp->gv.rcruise.x0C = 1;
}

bool grRCruise_801FF6CC(Ground_GObj* arg)
{
    return false;
}

void grRCruise_801FF6D4(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    if (gp->gv.unk.xD4 == 0) {
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
    Ground* gp = gobj->user_data;
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

char grRc_803E4F44[] = "dynamicsdata_shipflag\0\0\0"
                         "gp->u.scroll.int_jobj\0\0\0"
                         "gp->u.scroll.cam_jobj\0\0\0"
                         "gp->u.scroll.ctr_jobj\0\0\0"
                         "translate\0\0";

void grRCruise_801FF7A4(Ground_GObj* gobj)
{
    Ground_GObj* stage_gobj = gobj;
    Ground* gp = stage_gobj->user_data;
    HSD_JObj* jobj = stage_gobj->hsd_obj;
    UnkArchiveStruct* archive;
    DynamicsDesc* data;
    PAD_STACK(8);

    Ground_801C2ED0(jobj, gp->map_id);
    grAnime_801C8138(stage_gobj, gp->map_id, 0);
    grAnime_801C752C(jobj, 1, 30628, HSD_AObjSetFlags, 3, 0x20000000);
    archive = grDatFiles_801C6324();
    if (archive != NULL && (data = HSD_ArchiveGetPublicAddress(
                                archive->unk0, grRc_803E4F44),
                            data != NULL))
    {
        grLib_801C9B20(Ground_801C3FA4(stage_gobj, 23), data,
                       &gp->gv.rcruise2.xC4);
    } else {
        gp->gv.rcruise2.xC4.data = NULL;
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
    grLib_801C9B8C(&gp->gv);
    Ground_801C2FE0(gobj);
}

void grRCruise_801FF920(Ground_GObj* arg) {}

void grRCruise_801FF924(Ground_GObj* gobj)
{
    // RCruise uses an anim_gobj/int_jobj split not represented by ScrollVars.
    struct grRCruise_ScrollVarsForInit {
        struct {
            u8 b0 : 1;
            u8 b1 : 1;
            u8 b2 : 1;
            u8 b3 : 1;
            u8 b4 : 1;
            u8 b5 : 1;
            u8 b6 : 1;
            u8 b7 : 1;
        } x00;
        u8 pad_01[3];
        Vec3 x04;
        Vec3 x10;
        Vec3 x1C;
        HSD_GObj* anim_gobj;
        HSD_JObj* int_jobj;
        HSD_JObj* cam_jobj;
        HSD_JObj* ctr_jobj;
        HSD_JObj* x34[3];
        HSD_JObj* x40;
    };
    struct grRCruise_ScrollGround {
        u8 pad_00[0x14];
        s32 map_id;
        u8 pad_18[0xAC];
        struct {
            struct grRCruise_ScrollVarsForInit scroll;
        } u;
    };
    struct grRCruise_ScrollGround* gp =
        (struct grRCruise_ScrollGround*) GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    PAD_STACK(0x8);

    gp->u.scroll.x34[0] = Ground_801C3FA4(gobj, 4);
    gp->u.scroll.x34[1] = Ground_801C3FA4(gobj, 5);
    gp->u.scroll.x34[2] = Ground_801C3FA4(gobj, 6);
    gp->u.scroll.x40 = Ground_801C3FA4(gobj, 7);
    gp->u.scroll.int_jobj = Ground_801C3FA4(gobj, 3);
    HSD_ASSERTMSG(0x2B0, gp->u.scroll.int_jobj, grRc_803E4F44 + 0x18);
    gp->u.scroll.cam_jobj = Ground_801C3FA4(gobj, 2);
    HSD_ASSERTMSG(0x2B2, gp->u.scroll.cam_jobj, grRc_803E4F44 + 0x30);

    gp->u.scroll.ctr_jobj = Ground_801C3FA4(gobj, 1);
    HSD_ASSERTMSG(0x2B4, gp->u.scroll.ctr_jobj, grRc_803E4F44 + 0x48);

    HSD_JObjGetTranslation(gp->u.scroll.ctr_jobj, &gp->u.scroll.x04);
    gp->u.scroll.x10.z = grRc_804DB644;
    gp->u.scroll.x10.y = grRc_804DB644;
    gp->u.scroll.x10.x = grRc_804DB644;
    gp->u.scroll.x1C.z = grRc_804DB644;
    gp->u.scroll.x1C.y = grRc_804DB644;
    gp->u.scroll.x1C.x = grRc_804DB644;
    gp->u.scroll.x00.b0 = 0;
    grAnime_801C8138(gobj, gp->map_id, 0);
    grAnime_801C752C(jobj, 1, 30628, HSD_AObjSetFlags, 3, 0x20000000);
    gobj->render_cb = (GObj_RenderFunc) fn_80201BE0;
}

bool grRCruise_801FFAD4(Ground_GObj* arg)
{
    return false;
}

void grRCruise_801FFADC(Ground_GObj* arg0)
{
    Vec3 sp64;
    UNUSED Vec3 pad58;
    Vec3 cam_offset;
    UNUSED f32 pad48;
    Vec3 cam_offset2;
    Vec3 diff;
    Vec3 sp24;
    Vec3 sp18;
    Ground* gp;
    HSD_GObj* gobj;
    HSD_JObj* cam_jobj;
    HSD_JObj* ctr_jobj;
    HSD_JObj* temp_r29_2;
    f32 temp_f31;
    f32 temp_f4;

    HSD_JObj* jobj;
    Ground* anim_gp;
    PAD_STACK(0x8);

    gp = arg0->user_data;
    if (!(((u8) gp->u.scroll.x00 >> 7U) & 1)) {
        Stage_UnkSetVec3TCam_Offset(&cam_offset);
        HSD_ASSERT(0x2E0U, gp->u.scroll.anim_gobj);
        {
            HSD_GObj* anim_gobj = gp->u.scroll.anim_gobj;
            anim_gp = anim_gobj->user_data;
        }
        cam_jobj = anim_gp->u.scroll.cam_jobj;
        ctr_jobj = anim_gp->u.scroll.ctr_jobj;
        Stage_UnkSetVec3TCam_Offset(&cam_offset2);
        lb_8000B1CC(ctr_jobj, NULL, &sp18);
        lb_8000B1CC(cam_jobj, NULL, &sp24);
        lbVector_Diff(&sp24, &sp18, &diff);
        temp_f4 = sp18.z / diff.z;
        sp64.x = -((diff.x * temp_f4) - sp18.x);
        sp64.y = -((diff.y * temp_f4) - sp18.y);
        sp64.z = 0.0f;
        lbVector_Sub(&sp64, &cam_offset2);
        sp64.y += 10.0f;
        lbVector_Diff(&gp->u.scroll.x10, &sp64, &gp->gv.arwing.xE0);
        gp->u.scroll.x10 = sp64;
        sp64.x *= -1.0f;
        sp64.y *= -1.0f;
        sp64.z *= -1.0f;
        lbVector_Add(&sp64, &cam_offset);
        if ((temp_r29_2 = arg0->hsd_obj) != NULL) {
            HSD_JObjSetTranslate(temp_r29_2, &sp64);
            temp_f31 = -350.0f * Ground_801C0498();
            HSD_JObjAddTranslationZ(temp_r29_2, temp_f31);
        }
        gobj = Ground_801C2BA4(2);
        if (gobj != NULL) {
            if ((jobj = gobj->hsd_obj) != NULL) {
                HSD_JObjSetTranslate(jobj, &sp64);
            }
        }
        gobj = Ground_801C2BA4(1);
        if (gobj != NULL) {
            if ((jobj = gobj->hsd_obj) != NULL) {
                HSD_JObjSetTranslate(jobj, &sp64);
            }
        }
        gobj = Ground_801C2BA4(5);
        if (gobj != NULL) {
            if ((jobj = gobj->hsd_obj) != NULL) {
                HSD_JObjSetTranslate(jobj, &sp64);
            }
        }
        gobj = Ground_801C2BA4(6);
        if (gobj != NULL) {
            if ((jobj = gobj->hsd_obj) != NULL) {
                HSD_JObjSetTranslate(jobj, &sp64);
            }
        }
        gobj = Ground_801C2BA4(4);
        if (gobj != NULL) {
            if ((jobj = gobj->hsd_obj) != NULL) {
                HSD_JObjSetTranslate(jobj, &sp64);
            }
        }
    }
}

void grRCruise_80200070(Ground_GObj* arg) {}

void grRCruise_80200074(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    int i;
    HSD_JObj* jobj = GET_JOBJ(gobj);
    PAD_STACK(8);

    Ground_801C2ED0(jobj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 0);
    for (i = 0; i < 3; i++) {
        grAnime_801C8098(gobj, grRc_804D4790[i], 7, 1, 0.0F, 0.0F);
        gp->gv.rcruise.x3C[i].x02 =
            Ground_801C32D4(gp->map_id, grRc_804D4790[i]);
        mpJointSetCb1(gp->gv.rcruise.x3C[i].x02, gobj,
                      (mpLib_Callback) fn_80200460);
        gp->gv.rcruise.x3C[i].x0C = Ground_801C3FA4(gobj, grRc_804D4790[i]);
        gp->gv.rcruise.x3C[i].x08 = 0;
        gp->gv.rcruise.x3C[i].x04 = 0;
        gp->gv.rcruise.x3C[i].x00 = 0;
    }
}

bool grRCruise_8020014C(Ground_GObj* arg)
{
    return false;
}

void grRCruise_80200154(Ground_GObj* gobj)
{
    struct grRCruise_SubEntryFlags {
        u8 b0 : 1;
        u8 b1 : 1;
        u8 b2 : 1;
        u8 b3 : 1;
        u8 b4 : 1;
        u8 b5 : 1;
        u8 b6 : 1;
        u8 b7 : 1;
    };
    Ground* gp = gobj->user_data;
    Ground* gp2 = gp;
    s32 i;

    for (i = 0; i < 3; i++) {
        switch (gp->gv.rcruise.x3C[i].x00) {
        case 0:
            mpJointListAdd(gp2->gv.rcruise.x3C[i].x02);
            grRCruise_80201B60(gp2->gv.rcruise.x3C[i].x0C->child, 1);
            gp->gv.rcruise.x3C[i].x04 = 0;
            gp->gv.rcruise.x3C[i].x00 = 1;
            break;
        case 2:
            if (gp->gv.rcruise.x3C[i].x08 == 0) {
                gp->gv.rcruise.x3C[i].x04 = 0;
                grAnime_801C7A94(gobj, grRc_804D4790[i], 1, grRc_804DB644);
                gp->gv.rcruise.x3C[i].x00 = 3;
            } else if (grAnime_801C83D0(gobj, grRc_804D4790[i], 7) != 0) {
                gp->gv.rcruise.x3C[i].x04 = 0;
                gp->gv.rcruise.x3C[i].x00 = 5;
            }
            break;
        case 3:
            if (gp->gv.rcruise.x3C[i].x04 >= grRc_804D6A10->x0C) {
                gp->gv.rcruise.x3C[i].x04 = 0;
                ((struct grRCruise_SubEntryFlags*) &gp->gv.rcruise.x3C[i]
                     .pad_01)
                    ->b0 = 0;
                gp->gv.rcruise.x3C[i].x00 = 4;
            }
            gp->gv.rcruise.x3C[i].x04++;
            break;
        case 4:
            if (gp->gv.rcruise.x3C[i].x04 % grRc_804D6A10->x14 == 0) {
                ((struct grRCruise_SubEntryFlags*) &gp->gv.rcruise.x3C[i]
                     .pad_01)
                    ->b0 =
                    ((struct grRCruise_SubEntryFlags*) &gp->gv.rcruise.x3C[i]
                         .pad_01)
                        ->b0 ^
                    1;
                if (((struct grRCruise_SubEntryFlags*) &gp->gv.rcruise.x3C[i]
                         .pad_01)
                        ->b0)
                {
                    grRCruise_80201B60(gp2->gv.rcruise.x3C[i].x0C->child, 0);
                } else {
                    grRCruise_80201B60(gp2->gv.rcruise.x3C[i].x0C->child, 1);
                }
            }
            if (gp->gv.rcruise.x3C[i].x04 >= grRc_804D6A10->x10) {
                mpLib_80057BC0(gp2->gv.rcruise.x3C[i].x02);
                grRCruise_80201B60(gp2->gv.rcruise.x3C[i].x0C->child, 0);
                grAnime_801C7BA0(gobj, grRc_804D4790[i], 1, grRc_804DB644);
                grAnime_801C7A94(gobj, grRc_804D4790[i], 1, grRc_804DB644);
                mpLib_80055E9C(gp2->gv.rcruise.x3C[i].x02);
                mpLib_80057424(gp2->gv.rcruise.x3C[i].x02);
                gp->gv.rcruise.x3C[i].x00 = 0;
            }
            gp->gv.rcruise.x3C[i].x04++;
            break;
        case 5:
            if (gp->gv.rcruise.x3C[i].x04 % grRc_804D6A10->x1C == 0) {
                grRCruise_80201B60(gp2->gv.rcruise.x3C[i].x0C->child, 0);
            } else {
                grRCruise_80201B60(gp2->gv.rcruise.x3C[i].x0C->child, 1);
            }
            if (gp->gv.rcruise.x3C[i].x04 >= grRc_804D6A10->x18) {
                mpLib_80057BC0(gp2->gv.rcruise.x3C[i].x02);
                grRCruise_80201B60(gp2->gv.rcruise.x3C[i].x0C->child, 0);
                grAnime_801C7BA0(gobj, grRc_804D4790[i], 1, grRc_804DB644);
                grAnime_801C7A94(gobj, grRc_804D4790[i], 1, grRc_804DB644);
                mpLib_80055E9C(gp2->gv.rcruise.x3C[i].x02);
                mpLib_80057424(gp2->gv.rcruise.x3C[i].x02);
                gp->gv.rcruise.x3C[i].x00 = 0;
            }
            gp->gv.rcruise.x3C[i].x04++;
            break;
        }
        gp->gv.rcruise.x3C[i].x08 = 0;
    }
    Ground_801C2FE0(gobj);
}

void grRCruise_8020045C(Ground_GObj* arg) {}

void fn_80200460(Ground* gp_arg, s32 joint_id, CollData* cd, s32 arg3,
                 mpLib_GroundEnum arg4, f32 arg5)
{
    HSD_GObj* gobj = (HSD_GObj*) gp_arg;
    Ground* gp = HSD_GObjGetUserData(gobj);
    int i;
    PAD_STACK(16);

    if ((s32) cd->x34_flags.b1234 == 1) {
        for (i = 0; i < 3; i++) {
            if (gp->gv.rcruise.x3C[i].x02 == joint_id) {
                u8 state = gp->gv.rcruise.x3C[i].x00;
                if (state == 1 || (u8) (state - 3) <= 1u) {
                    gp->gv.rcruise.x3C[i].x04 = 0;
                    grRCruise_80201B60(gp->gv.rcruise.x3C[i].x0C->child, 1);
                    grAnime_801C7A94(gobj, grRc_804D4790[i], 1, 1.0f);
                    gp->gv.rcruise.x3C[i].x00 = 2;
                }
                gp->gv.rcruise.x3C[i].x08++;
                return;
            }
        }
    }
}

void grRCruise_80200540(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    gp->gv.rcruise.x18 = 0.0F;
    gp->gv.rcruise.x14 = 0.0F;
    gp->gv.rcruise.x1C = 0.0F;
    gp->gv.rcruise.x20 = 0.0F;
    gp->gv.rcruise.x34 = 0;
    gp->gv.rcruise.x30 = 0;
    gp->gv.rcruise.x28 = 0.0F;
    gp->gv.rcruise.x24 = 0.0F;
    gp->gv.rcruise.x38 = 0;
    gp->gv.rcruise.x2C = 0;
}

void grRCruise_80200578(Ground* gp_arg, s32 joint_id, CollData* cd, s32 arg3,
                        mpLib_GroundEnum arg4, f32 arg5)
{
    UNUSED u8 pad[8];
    Point3d pos;
    HSD_GObj* gobj = (HSD_GObj*) gp_arg;
    Ground* gp = HSD_GObjGetUserData(gobj);
    HSD_JObj* jobj = Ground_801C3FA4(gobj, 8);
    f32 dx;
    f32 dy;
    f32 dist;
    PAD_STACK(8);

    if ((s32) cd->x34_flags.b1234 != 1 &&
        (s32) cd->x34_flags.b1234 != 2 &&
        (s32) cd->x34_flags.b1234 != 3)
    {
        return;
    }

    if ((f32) arg3 > 1000.0f) {
        arg3 = 1000;
    }
    lb_8000B1CC(jobj, NULL, &pos);
    dx = pos.x - cd->cur_pos.x;
    dy = pos.y - cd->cur_pos.y;
    dist = sqrtf(dy * dy + dx * dx);
    if (dist > 4.0f) {
        if (pos.x < cd->cur_pos.x) {
            gp->gv.rcruise.x24 += dist * ((f32) arg3 / 1000.0f);
        } else {
            gp->gv.rcruise.x28 += dist * ((f32) arg3 / 1000.0f);
        }
    }
    gp->gv.rcruise.x34++;
}

void grRCruise_8020071C(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    HSD_JObj* jobj = Ground_801C3FA4(gobj, 8);
    HSD_GObj* gobj5 = Ground_801C2BA4(5);
    HSD_JObj* jobj5 = gobj5 != NULL ? Ground_801C3FA4(gobj5, 8) : NULL;
    f32 abs_rot =
        gp->gv.rcruise.x14 < 0.0f ? -gp->gv.rcruise.x14 : gp->gv.rcruise.x14;
    f32 wrapped = abs_rot - (360.0f * (s32) (abs_rot / 360.0f));
    PAD_STACK(8);

    switch (gp->gv.rcruise.x2C) {
    case 0:
        if (gp->gv.rcruise.x34 == 0) {
            gp->gv.rcruise.x1C = gp->gv.rcruise.x14 < 0.0f ? 1.0f : -1.0f;
            gp->gv.rcruise.x20 = grRc_804D6A10->x8 * gp->gv.rcruise.x1C;
            if (wrapped <= 0.2f) {
                gp->gv.rcruise.x20 = 0.0f;
                gp->gv.rcruise.x2C = 0;
            }
        } else if (gp->gv.rcruise.x24 < gp->gv.rcruise.x28) {
            gp->gv.rcruise.x1C = 1.0f;
            gp->gv.rcruise.x20 =
                grRc_804D6A10->x0 * (gp->gv.rcruise.x28 - gp->gv.rcruise.x24);
            if (gp->gv.rcruise.x20 > grRc_804D6A10->x4) {
                gp->gv.rcruise.x20 = grRc_804D6A10->x4;
            }
        } else {
            gp->gv.rcruise.x1C = -1.0f;
            gp->gv.rcruise.x20 =
                -grRc_804D6A10->x0 * (gp->gv.rcruise.x24 - gp->gv.rcruise.x28);
            if (gp->gv.rcruise.x20 < -grRc_804D6A10->x4) {
                gp->gv.rcruise.x20 = -grRc_804D6A10->x4;
            }
        }
        break;
    case 1:
        if (gp->gv.rcruise.x38 == 0) {
            if (gp->gv.rcruise.x34 == 0) {
                gp->gv.rcruise.x1C = gp->gv.rcruise.x14 < 0.0f ? 1.0f : -1.0f;
                gp->gv.rcruise.x20 = grRc_804D6A10->x8 * gp->gv.rcruise.x1C;
                if (wrapped <= 0.2f) {
                    gp->gv.rcruise.x20 = 0.0f;
                    gp->gv.rcruise.x2C = 0;
                }
            } else {
                gp->gv.rcruise.x2C = 0;
            }
        } else {
            gp->gv.rcruise.x38--;
            gp->gv.rcruise.x20 += 0.008f * -gp->gv.rcruise.x1C;
            if (gp->gv.rcruise.x20 < 0.0f ? -gp->gv.rcruise.x20
                                          : gp->gv.rcruise.x20 <= 0.008f)
            {
                gp->gv.rcruise.x20 = 0.0f;
            }
        }
        break;
    }
    gp->gv.rcruise.x14 += gp->gv.rcruise.x20;
    HSD_JObjSetRotationZ(jobj, 0.017453292f * gp->gv.rcruise.x14);
    if (jobj5 != NULL) {
        HSD_JObjSetRotationZ(jobj5, 0.017453292f * gp->gv.rcruise.x14);
    }
    gp->gv.rcruise.x30 = gp->gv.rcruise.x34;
    gp->gv.rcruise.x34 = 0;
    gp->gv.rcruise.x28 = 0.0f;
    gp->gv.rcruise.x24 = 0.0f;
}

s16 grRc_803E4FF0[] = {
    0x20, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30,
    0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0,
    0x06, 0x04, 0,    0,    0x08, 0x05, 0,    0,
    0x10, 0x0A, 0,    0,    0x0B, 0x06, 0,    0,
    0x0C, 0x07, 0,    0,    0x0D, 0x08, 0,    0,
    0x0E, 0x09, 0,    0,    0x0F, 0x08, 0,    0,
    0x13, 0x0C, 0,    1,    0x14, 0x0D, 0,    1,
    0x15, 0x0E, 0,    1,    0x1E, 0x0F, 0,    1,
    0x16, 0x10, 0,    1,    0x17, 0x11, 0,    1,
    0x18, 0x12, 0,    1,    0x19, 0x13, 0,    1,
    0x1A, 0x14, 0,    1,    0x1B, 0x15, 0,    1,
    0x1C, 0x16, 0,    1,    0x1D, 0x17, 0,    1,
};

void grRCruise_80200B48(Ground_GObj* gobj)
{
    Ground* gp;
    HSD_JObj* jobj;
    struct grRCruise_Entry* entry;
    s32 i;

    gp = gobj->user_data;
    for (i = 0; i < 17; i++) {
        entry = &gp->gv.rcruise.entries[i];
        entry->x02 = Ground_801C32D4(gp->map_id, grRc_803E4FF0[i]);
        entry->x14 = Ground_801C3FA4(gobj, grRc_803E4FF0[i]);
        entry->x08 = 0;
        entry->x04 = 0;
        entry->x0C = HSD_JObjGetTranslationY(jobj = entry->x14);
        entry->x00 = 0;
    }
}

inline Ground* grRCruise_80200C04_inline(Ground_GObj* gobj)
{
    return gobj->user_data;
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
    s32 i;

    gp = grRCruise_80200C04_inline(gobj);
    for (i = 0; i < 17; i++) {
        struct grRCruise_Entry* entry = &gp->gv.rcruise.entries[i];

        switch (entry->x00) {
        case 1:
            if (entry->x08 == 0) {
                entry->x04 = 0;
                entry->x00 = 0;
            } else if (entry->x04 >= grRc_804D6A10->x20) {
                entry->x00 = 2;
            } else {
                entry->x04++;
            }
            break;
        case 2:
            if ((entry->x04 % grRc_804D6A10->x28) == 0) {
                f32 range =
                    100.0f * (grRc_804D6A10->x30 - grRc_804D6A10->x2C);
                s32 randi = (s32) range != 0 ? HSD_Randi((s32) range) : 0;
                HSD_JObjSetTranslateY(entry->x14,
                                      entry->x0C + (grRc_804D6A10->x2C +
                                                    ((f32) randi / 100.0f)));
            }
            if (entry->x04 >= grRc_804D6A10->x24) {
                entry->x10 = 0.0f;
                entry->x00 = 3;
            }
            entry->x04++;
            break;
        case 3:
            entry->x10 -= grRc_804D6A10->x34;
            if ((entry->x10 < 0.0f ? -entry->x10 : entry->x10) >
                grRc_804D6A10->x38)
            {
                entry->x10 = -grRc_804D6A10->x38;
            }
            HSD_JObjAddTranslationY(entry->x14, entry->x10);
            if (HSD_JObjGetTranslationY(entry->x14) <=
                Stage_GetCamBoundsBottomOffset())
            {
                entry->x10 = 0.0f;
                grRCruise_80201B60(entry->x14, 0);
                mpLib_80057BC0(entry->x02);
                entry->x04 = 0;
                entry->x00 = 4;
            }
            break;
        case 4:
            if (entry->x04 >= grRc_804D6A10->x3C) {
                HSD_JObjSetTranslateY(entry->x14, entry->x0C);
                mpLib_80055E9C(entry->x02);
                mpLib_80057424(entry->x02);
                grRCruise_80201B60(entry->x14, 1);
                mpJointListAdd(entry->x02);
                entry->x04 = 0;
                ((struct grRCruise_EntryFlags*) &entry->pad_01)->b0 = 0;
                entry->x00 = 5;
            }
            entry->x04++;
            break;
        case 5:
            if ((entry->x04 % grRc_804D6A10->x44) == 0) {
                ((struct grRCruise_EntryFlags*) &entry->pad_01)->b0 =
                    ((struct grRCruise_EntryFlags*) &entry->pad_01)->b0 ^ 1;
                if (((struct grRCruise_EntryFlags*) &entry->pad_01)->b0) {
                    grRCruise_80201B60(entry->x14, 0);
                } else {
                    grRCruise_80201B60(entry->x14, 1);
                }
            }
            if (entry->x04 >= grRc_804D6A10->x40) {
                grRCruise_80201B60(entry->x14, 1);
                entry->x04 = 0;
                entry->x00 = 0;
            }
            entry->x04++;
            break;
        }
        entry->x08 = 0;
    }
}

// TODO: is this GET_GROUND? calling it directly didn't work.
inline Ground* grRCruise_802010A4_inline(Ground_GObj* arg0)
{
    return arg0->user_data;
}

void grRCruise_802010A4(Ground_GObj* gobj, s32 id, CollData* coll)
{
    Ground* gp = grRCruise_802010A4_inline(gobj);
    s32 i;

    if ((s32) coll->x34_flags.b1234 != 1) {
        return;
    }

    for (i = 0; i < 17; i++) {
        struct grRCruise_Entry* entry = &gp->gv.rcruise.entries[i];
        if (entry->x02 == id) {
            if (entry->x00 == 0) {
                entry->x04 = 0;
                entry->x00 = 1;
            }
            entry->x08++;
            return;
        }
    }
}

void grRCruise_80201110(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    f32 angle = atan2f(gp->gv.rcruise.x04->x4.z, gp->gv.rcruise.x04->x4.x);
    angle += gp->gv.rcruise.x08;

    if (angle > 1.0471975430846214) {
        angle = 1.0471976f;
    }
    if (angle < -1.0471975430846214) {
        angle = -1.0471976f;
    }
    gp->gv.rcruise.x04->x4.x = cosf(angle);
    gp->gv.rcruise.x04->x4.z = sinf(angle);
    if ((gp->gv.rcruise.x04->unk_angle_int % 30) == 0 && HSD_Randf() > 0.5) {
        gp->gv.rcruise.x08 = -gp->gv.rcruise.x08;
    }
    if ((gp->gv.rcruise.x04->unk_angle_int % 300) == 0) {
        if (gp->gv.rcruise.x0C != 0) {
            gp->gv.rcruise.x0C = 0;
        } else if (HSD_Randf() > 0.5) {
            gp->gv.rcruise.x0C = 1;
        }
    }
    if (gp->gv.rcruise.x0C != 0) {
        gp->gv.rcruise.x04->unk_scale = 0.3 * HSD_Randf() + 0.2;
        return;
    }
    gp->gv.rcruise.x04->unk_scale = 0.2 * HSD_Randf() + 0.1;
}

inline struct HSD_DObj* grRCruise_80201288_inline(HSD_JObj* arg0)
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

void grRCruise_80201410(Ground_GObj* gobj)
{
    struct grRCruise_VanishDescTable {
        u8 pad[0x26C];
        struct grRCruise_VanishDesc desc[20];
    };
    Ground* gp = gobj->user_data;
    struct grRCruise_VanishDescTable* desc_table;
    u32 i;

    gp->u.map.vanish = HSD_MemAlloc(0xA0);
    HSD_ASSERT(0x5AD, gp->u.map.vanish);

    desc_table = (struct grRCruise_VanishDescTable*) grRc_803E4DA8;
    for (i = 0; i < 20; i++) {
        gp->u.map.vanish[i].jobj =
            Ground_801C3FA4(gobj, desc_table->desc[i].x00);
        HSD_ASSERT(0x5B3, gp->u.map.vanish[i].jobj);
        if (desc_table->desc[i].x04 != 0) {
            HSD_GObj* gobj1;
            HSD_GObj* gobj5;
            s32 joint;

            gp->u.map.vanish[i].x00 = 2;
            joint = desc_table->desc[i].x00;
            gobj5 = Ground_801C2BA4(5);
            if (gobj5 != NULL) {
                gobj1 = Ground_801C2BA4(1);
                if (gobj1 != NULL) {
                    HSD_JObj* jobj = Ground_801C3FA4(gobj5, joint);
                    if (jobj != NULL) {
                        HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
                    }
                    jobj = Ground_801C3FA4(gobj1, joint);
                    if (jobj != NULL) {
                        grRCruise_80201288(jobj, HSD_DObjSetFlags, 1);
                    }
                }
            }
            mpJointListAdd(desc_table->desc[i].x02);
        } else {
            gp->u.map.vanish[i].x00 = 0;
            grAnime_801C7FF8(gobj, desc_table->desc[i].x00, 2, 1, 0.0f,
                             1.0f);
            mpLib_80057BC0(desc_table->desc[i].x02);
        }
    }
}

void grRCruise_80201588(Ground_GObj* gobj)
{
    Point3d pos;
    Ground* gp = gobj->user_data;
    struct grRCruise_VanishDesc* desc;
    u32 i;

    HSD_ASSERT(0x5D6, gp->u.map.vanish);
    PAD_STACK(4);
    desc = &grRc_803E5014;
    for (i = 0; i < 20; i++, desc++) {
        struct grRCruise_VanishEntry* vanish;

        if (desc->x04 != 0) {
            continue;
        }
        vanish = &gp->gv.rcruise.vanish[i];
        switch (vanish->x00) {
        case 0:
            lb_8000B1CC(vanish->jobj, NULL, &pos);
            if (Camera_8003118C(&pos, -20.0f) != 0) {
                gp->gv.rcruise.vanish[i].x00 = 1;
                grAnime_801C7FF8(gobj, desc->x00, 2, 2, 0.0f, 1.0f);
                mpJointListAdd(desc->x02);
                mpLib_80055E9C(desc->x02);
                mpLib_80057424(desc->x02);
            }
            break;
        case 1:
            if (grAnime_801C83D0(gobj, desc->x00, 2) != 0) {
                HSD_GObj* gobj1;
                HSD_GObj* gobj5;
                HSD_JObj* jobj;
                s32 joint;

                gp->gv.rcruise.vanish[i].x00 = 2;
                joint = desc->x00;
                gobj5 = Ground_801C2BA4(5);
                if (gobj5 != NULL) {
                    gobj1 = Ground_801C2BA4(1);
                    if (gobj1 != NULL) {
                        jobj = Ground_801C3FA4(gobj5, joint);
                        if (jobj != NULL) {
                            HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
                        }
                        jobj = Ground_801C3FA4(gobj1, joint);
                        if (jobj != NULL) {
                            grRCruise_80201288(jobj, HSD_DObjSetFlags, 1);
                        }
                    }
                }
            }
            break;
        case 2:
            lb_8000B1CC(vanish->jobj, NULL, &pos);
            if (Camera_8003118C(&pos, -20.0f) == 0) {
                HSD_GObj* gobj1;
                HSD_GObj* gobj5;
                HSD_JObj* jobj;
                s32 joint;

                gp->gv.rcruise.vanish[i].x00 = 3;
                grAnime_801C7FF8(gobj, desc->x00, 2, 3, 0.0f, 1.0f);
                joint = desc->x00;
                gobj5 = Ground_801C2BA4(5);
                if (gobj5 != NULL) {
                    gobj1 = Ground_801C2BA4(1);
                    if (gobj1 != NULL) {
                        jobj = Ground_801C3FA4(gobj5, joint);
                        if (jobj != NULL) {
                            HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
                        }
                        jobj = Ground_801C3FA4(gobj1, joint);
                        if (jobj != NULL) {
                            grRCruise_80201288(jobj, HSD_DObjClearFlags, 1);
                        }
                    }
                }
            }
            break;
        case 3:
            if (grAnime_801C83D0(gobj, desc->x00, 2) != 0) {
                u32 j;

                gp->gv.rcruise.vanish[i].x00 = 0;
                grAnime_801C7FF8(gobj, desc->x00, 2, 1, 0.0f, 1.0f);
                for (j = 0; j < 20; j++) {
                    if ((&grRc_803E5014)[j].x02 == desc->x02 &&
                        gp->gv.rcruise.vanish[j].x00 != 0)
                    {
                        break;
                    }
                }
                if (j == 20) {
                    mpLib_80057BC0(desc->x02);
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
        Ground* gp = gobj->user_data;
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
        s32 joint = mpJointFromLine(line_id);
        s32 result;

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

void grRCruise_80201B60(HSD_JObj* jobj, s32 arg1)
{
    HSD_DObj* dobj;
    HSD_DObj* next;
    PAD_STACK(8);

    dobj = HSD_JObjGetDObj(jobj);
    while (dobj != NULL) {
        if (arg1 != 0) {
            HSD_DObjClearFlags(dobj, 1U);
        } else {
            HSD_DObjSetFlags(dobj, 1U);
        }
        if (dobj != NULL) {
            next = dobj->next;
        } else {
            next = NULL;
        }
        dobj = next;
    }
}

void fn_80201BE0(HSD_GObj* gobj, s32 pass)
{
    if (gm_801A45E8(1) != 0 || gm_801A45E8(2) != 0 || Camera_8003010C() != 0) {
        return;
    }
    grDisplay_801C5DB0(gobj, pass);
}

DynamicsDesc* grRCruise_80201C50(enum_t arg)
{
    return false;
}

bool grRCruise_80201C58(Vec3* arg, int arg0, HSD_JObj* jobj)
{
    return true;
}
