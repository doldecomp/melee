#include "grhomerun.h"

#include "placeholder.h"

#include <platform.h>

#include "baselib/archive.h"
#include "baselib/debug.h"

#include "baselib/forward.h"

#include "baselib/gobj.h"
#include "baselib/gobjgxlink.h"
#include "baselib/gobjobject.h"
#include "baselib/jobj.h"
#include "baselib/memory.h"
#include "baselib/sislib.h"
#include "cm/camera.h"
#include "ft/ftlib.h"
#include "gm/gmregclear.h"
#include "gr/grdatfiles.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "gr/stage.h"
#include "it/it_26B1.h"
#include "it/types.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "lb/lblanguage.h"
#include "lb/types.h"
#include "mp/mplib.h"

f32 grHr_804D6AD8;
int grHr_804D6ADC;
f32 grHr_804D6AE0;
f32 grHr_804D6AE4;
static void* grHr_804D6AE8;
static int grHr_804D4998[2] = { 0xA, 0 };
static char grHr_804D49A0[] = "/GrHr";
static char grHr_804D49D0[] = "%d";
extern GXColor grHr_804DBC74;
extern f32 grHr_804DBC78;
extern f32 grHr_804DBC7C;
extern f32 grHr_804DBC80;
extern f32 grHr_804DBC84;

typedef struct grHomeRun_MainGroundVars {
    HSD_GObj** gobjs;
    HSD_GObj** jobj_gobjs;
    HSD_Text* xCC;
    HSD_JObj* xD0;
    HSD_GObj* xD4;
    HSD_GObj* rear_gobj;
    HSD_GObj* rear2_gobj;
    HSD_GObj* rear3_gobj;
    HSD_GObj* rear4_gobj;
    struct {
        u8 b0 : 1;
        u8 b1 : 1;
        u8 b2 : 1;
        u8 b3 : 1;
        u8 b4 : 1;
        u8 b5 : 1;
        u8 b6 : 1;
        u8 b7 : 1;
    } xE8_flags;
} grHomeRun_MainGroundVars;

StageCallbacks grHr_803E8140[11] = {
    { grHomeRun_8021C914, grHomeRun_8021CB10, grHomeRun_8021CB18,
      grHomeRun_8021CB1C, 0 },
    { grHomeRun_8021E038, grHomeRun_8021E064, grHomeRun_8021E06C,
      grHomeRun_8021E070, 0 },
    { grHomeRun_8021E074, grHomeRun_8021E0CC, grHomeRun_8021E0D4,
      grHomeRun_8021E18C, 0 },
    { grHomeRun_8021E4C4, grHomeRun_8021E4F0, grHomeRun_8021E4F8,
      grHomeRun_8021E4FC, 0 },
    { grHomeRun_8021DEB4, grHomeRun_8021DEE0, grHomeRun_8021DEE8,
      grHomeRun_8021DEEC, 0 },
    { grHomeRun_8021DEF0, grHomeRun_8021DF48, grHomeRun_8021DF50,
      grHomeRun_8021E008, 0 },
    { grHomeRun_8021E1BC, grHomeRun_8021E1E8, grHomeRun_8021E1F0,
      grHomeRun_8021E1F4, 0 },
    { grHomeRun_8021E1F8, grHomeRun_8021E250, grHomeRun_8021E258,
      grHomeRun_8021E310, 0 },
    { grHomeRun_8021E340, grHomeRun_8021E36C, grHomeRun_8021E374,
      grHomeRun_8021E378, 0 },
    { grHomeRun_8021E37C, grHomeRun_8021E3D4, grHomeRun_8021E3DC,
      grHomeRun_8021E494, 0 },
    { grHomeRun_8021CB20, grHomeRun_8021D678, grHomeRun_8021D680,
      grHomeRun_8021DEB0, 0xC0000000 },
};

typedef struct grHr_StageData {
    StageData stage_data;
    char report_format[0x24];
    char filename[0xC];
} grHr_StageData;

grHr_StageData grHr_803E821C = {
    {
        HOMERUN,
        grHr_803E8140,
        grHr_804D49A0,
        grHomeRun_8021C754,
        grHomeRun_8021C750,
        grHomeRun_8021C7FC,
        grHomeRun_8021C800,
        grHomeRun_8021C824,
        grHomeRun_8021EEB4,
        grHomeRun_8021EEBC,
        1,
        (S16Vec3*) grHr_804D4998,
        1,
    },
    "%s:%d: couldn t get gobj(id=%d)\n",
    "grhomerun.c",
};

void grHomeRun_8021C750(bool arg) {}

void grHomeRun_8021C754(void)
{
    Vec3 cam_offset;

    grHr_804D6AE8 = Ground_801C49F8();
    stage_info.unk8C.b4 = false;
    stage_info.unk8C.b5 = true;
    grHomeRun_8021EDD4();
    grHomeRun_8021C82C(0);
    grHomeRun_8021C82C(0xA);
    grHomeRun_8021ED74();
    Ground_801C39C0();
    Ground_801C3BB4();
    Stage_UnkSetVec3TCam_Offset(&cam_offset);
    Ground_801C38AC(3.0f * (Stage_GetCamBoundsRightOffset() - cam_offset.x));
    Ground_801C39B0(3.0f * (Stage_GetBlastZoneRightOffset() - cam_offset.x));
}

void grHomeRun_8021C7FC(void) {}

void grHomeRun_8021C800(void)
{
    grZakoGenerator_801CAE04(NULL);
}

bool grHomeRun_8021C824(void)
{
    return false;
}
#pragma push
#pragma dont_inline on
HSD_GObj* grHomeRun_8021C82C_noinline(int gobj_id);

HSD_GObj* grHomeRun_8021C82C_noinline(int gobj_id)
{
    return grHomeRun_8021C82C(gobj_id);
}
#pragma dont_inline reset
#pragma pop

HSD_GObj* grHomeRun_8021C82C(int gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grHr_803E8140[gobj_id];

    gobj = Ground_GetStageGObj(gobj_id);

    if (gobj != NULL) {
        Ground_SetupStageCallbacks(gobj, callbacks);
    } else {
        OSReport((char*) grHr_803E8140 + 0x110, (char*) grHr_803E8140 + 0x134,
                 0x131, gobj_id);
    }

    return gobj;
}

void grHomeRun_8021C914(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = (HSD_JObj*) gobj->hsd_obj;

    grAnime_801C8138((HSD_GObj*) gobj, gp->map_id, 0);

    HSD_JObjSetScaleX(jobj, grHr_804D6AE4 * HSD_JObjGetScaleX(jobj));
    HSD_JObjSetScaleY(jobj, grHr_804D6AE4 * HSD_JObjGetScaleY(jobj));
    HSD_JObjSetScaleZ(jobj, grHr_804D6AE4 * HSD_JObjGetScaleZ(jobj));
}

bool grHomeRun_8021CB10(Ground_GObj* arg)
{
    return false;
}

void grHomeRun_8021CB18(Ground_GObj* arg) {}

void grHomeRun_8021CB1C(Ground_GObj* arg) {}

void grHomeRun_8021CB20(Ground_GObj* gobj)
{
    static HSD_CameraDescPerspective cobj_desc = {
        NULL,
        0,
        1,
        { 0, 640, 0, 480 },
        { 0, 640, 0, 480 },
        NULL,
        NULL,
        0.0F,
        NULL,
        0.1F,
        32768.0F,
        30.0F,
        1.4F,
    };

    Ground* gp = GET_GROUND(gobj);
    grHomeRun_MainGroundVars* vars =
        (grHomeRun_MainGroundVars*) &gp->gv.homerun;
    HSD_JObj* jobj = GET_JOBJ(gobj);
    UnkArchiveStruct* archive;
    HSD_CObj* cobj;
    s16 i;
    f32 gobjs_num;
    HSD_GObj** gobjs;
    HSD_GObj** jobjs;
    PAD_STACK(24);

    Ground_801C2ED0(jobj, gp->map_id);

    vars->gobjs = HSD_MemAlloc(0x100);
    HSD_ASSERT(0x17A, vars->gobjs);
    gobjs = vars->gobjs;

    vars->jobj_gobjs = HSD_MemAlloc(0x40);
    HSD_ASSERT(0x17B, vars->jobj_gobjs);
    jobjs = vars->jobj_gobjs;

    HSD_JObjSetScaleX(jobj, grHr_804D6AE4 * HSD_JObjGetScaleX(jobj));
    HSD_JObjSetScaleY(jobj, grHr_804D6AE4 * HSD_JObjGetScaleY(jobj));
    HSD_JObjSetScaleZ(jobj, grHr_804D6AE4 * HSD_JObjGetScaleZ(jobj));

    *(u8*) &gp->x10_flags |= 4;
    grAnime_801C8138(gobj, gp->map_id, false);
    mpJointSetCb1(0, gp, (mpLib_Callback) fn_8021E994);

    archive = grDatFiles_801C6324();
    vars->xD4 = GObj_Create(0x11, 0x13, 0);
    cobj = lb_80013B14(&cobj_desc);
    HSD_CObjSetPerspective(cobj, 30.0F, 1.4F);
    HSD_GObjObject_80390A70(vars->xD4, HSD_GObj_804D784B, cobj);
    GObj_SetupGXLinkMax(vars->xD4, (GObj_RenderFunc) (Event) fn_8021EB10, 7);
    vars->xD4->gxlink_prios = 2;
    HSD_SisLib_803A611C(1, vars->xD4, 9, 0xD, 0, 1, 0, 7);
    HSD_SisLib_804D1124[1] =
        HSD_ArchiveGetPublicAddress(archive->unk0, "SIS_GrHomerunData");
    gobjs_num = 2.0F * (1.0F + (2400.0F / (160.0F * Ground_801C0498())));
    HSD_ASSERT(0x1A2, gobjs_num < 64);

    for (i = 0; (f32) i < 1.0F + (2400.0F / (160.0F * Ground_801C0498())); i++)
    {
        gobjs[i] = grHomeRun_8021E500(i);
    }
    for (; i < 64; i++) {
        gobjs[i] = NULL;
    }

    for (i = 0; i < 16; i++) {
        HSD_JObj* child;
        HSD_GObj* gobj;
        jobjs[i] = grHomeRun_8021C82C_noinline(4);
        gobj = jobjs[i];
        HSD_ASSERT(0x1AB, gobj);

        jobj = GET_JOBJ(gobj);
        HSD_ASSERT(0x1AC, jobj);

        HSD_JObjSetScaleX(jobj, grHr_804D6AE4 * HSD_JObjGetScaleX(jobj));
        HSD_JObjSetScaleY(jobj, grHr_804D6AE4 * HSD_JObjGetScaleY(jobj));
        HSD_JObjSetScaleZ(jobj, grHr_804D6AE4 * HSD_JObjGetScaleZ(jobj));

        child = HSD_JObjGetChild(jobj);
        HSD_JObjSetTranslateX(child, 0.0F);
        HSD_JObjSetTranslateX(
            jobj, grHr_804D6AE4 *
                      ((4.0F + (f32) i) * -(160.0F * Ground_801C0498())));
    }

    {
        HSD_GObj* rear_gobj = grHomeRun_8021C82C_noinline(3);
        HSD_ASSERT(0x1BA, rear_gobj);
        vars->rear_gobj = rear_gobj;
        jobj = GET_JOBJ(rear_gobj);
        HSD_ASSERT(0x1BB, jobj);
    }
    HSD_JObjSetTranslateX(jobj, 1.5F * -(2150.99F * Ground_801C0498()));

    {
        HSD_GObj* rear2_gobj = grHomeRun_8021C82C_noinline(3);
        HSD_ASSERT(0x1BD, rear2_gobj);
        vars->rear2_gobj = rear2_gobj;
        jobj = GET_JOBJ(rear2_gobj);
        HSD_ASSERT(0x1BE, jobj);
    }

    HSD_JObjSetTranslateX(jobj, 0.5F * -(2150.99F * Ground_801C0498()));

    {
        HSD_GObj* rear3_gobj = grHomeRun_8021C82C_noinline(3);
        HSD_ASSERT(0x1C0, rear3_gobj);
        vars->rear3_gobj = rear3_gobj;
        jobj = GET_JOBJ(rear3_gobj);
        HSD_ASSERT(0x1C1, jobj);
    }

    HSD_JObjSetTranslateX(jobj, 0.5F * (2150.99F * Ground_801C0498()));

    {
        HSD_GObj* rear4_gobj = grHomeRun_8021C82C_noinline(3);
        HSD_ASSERT(0x1C3, rear4_gobj);
        vars->rear4_gobj = rear4_gobj;
        jobj = GET_JOBJ(rear4_gobj);
        HSD_ASSERT(0x1C4, jobj);
    }

    HSD_JObjSetTranslateX(jobj, 1.5F * (2150.99F * Ground_801C0498()));

    vars->xCC = NULL;
    vars->xD0 = Ground_801C3FA4(gobj, 1);
    vars->xE8_flags.b0 = 0;
}

bool grHomeRun_8021D678(Ground_GObj* arg)
{
    return false;
}

void grHomeRun_8021D680(Ground_GObj* gobj)
{
    Vec3 pos0;
    CmSubject* subject;
    Ground* gp;
    Ground* gp2;
    HSD_GObj* gobj2;
    HSD_JObj* jobj;
    HSD_Text* text;
    s32 x0;
    s32 x1;
    s32 i;
    f32 scale;
    f32 y;
    f32 z;
    f32 x;

    gp = GET_GROUND(gobj);
    gobj2 = Ground_801C57A4();
    if (gobj2 != NULL) {
        Vec3 cam_interest;
        ftLib_80086644(gobj2, &pos0);
        subject = ftLib_80086B74(gobj2);
        if (subject != NULL) {
            subject->x8 = 1;
            subject->xC_b1 = 1;
        }
        gobj2 = Ground_801C57C8();
        if (gobj2 != NULL) {
            subject = ftLib_80086B74(gobj2);
            if (subject != NULL) {
                subject->x8 = 1;
                subject->xC_b1 = 1;
            }
        }
        {
            HSD_GObj* sandbag_gobj = gm_80180AF4();
            if (sandbag_gobj != NULL) {
                Vec3 pos1;
                ftLib_80086644(sandbag_gobj, &pos1);
                grHomeRun_8021EA30(&pos1.x);
                if (pos1.y < 4.0F &&
                    ((grHomeRun_MainGroundVars*) &gp->gv.homerun)
                            ->xE8_flags.b0 != 0)
                {
                    grHomeRun_8021EAF8();
                }
            }
        }
        ((grHomeRun_MainGroundVars*) &gp->gv.homerun)->xE8_flags.b0 = 0;
        if ((u32) gp->gv.unk.xD0 != 0 && (u32) gp->gv.unk.xCC == 0) {
            Vec3 pos2;
            gp->gv.unk.xCC = (intptr_t) grHomeRun_8021EC58(0);
            lb_8000B1CC((HSD_JObj*) gp->gv.unk.xD0, NULL, &pos2);

            scale = Ground_801C0498();
            z = pos2.z + 0.0F * (grHr_804D6AE4 * scale);

            scale = Ground_801C0498();
            y = -pos2.y + 0.0F * (grHr_804D6AE4 * scale);

            scale = Ground_801C0498();
            text = (HSD_Text*) (intptr_t) gp->gv.unk.xCC;
            text->pos_x = pos2.x + (-1.0F) * (grHr_804D6AE4 * scale);
            text->pos_y = y;
            text->pos_z = z;
        }

        Camera_GetTransformInterest(&cam_interest);
        x0 = (s32) (((cam_interest.x - 2400.0F) /
                     (160.0F * Ground_801C0498())) -
                    1.0F);
        if (x0 < 0) {
            x0 = 0;
        }

        x1 = (s32) (1.0F + ((2400.0F + cam_interest.x) /
                            (160.0F * Ground_801C0498())));
        gp2 = GET_GROUND(
            ((grHomeRun_MainGroundVars*) &gp->gv.homerun)->gobjs[0]);
        if (gp2->gv.homerun.xC4 < x0) {
            {
                HSD_GObj* first_gobj =
                    ((grHomeRun_MainGroundVars*) &gp->gv.homerun)->gobjs[0];
                Ground_801C4A08(first_gobj);
            }
            for (i = 0; i < 63; i++) {
                ((grHomeRun_MainGroundVars*) &gp->gv.homerun)->gobjs[i] =
                    ((grHomeRun_MainGroundVars*) &gp->gv.homerun)
                        ->gobjs[i + 1];
            }
            ((grHomeRun_MainGroundVars*) &gp->gv.homerun)->gobjs[63] = NULL;
        } else if (gp2->gv.homerun.xC4 > x0) {
            gobj2 = grHomeRun_8021E500(gp2->gv.homerun.xC4 - 1);
            for (i = 63; i > 0; i--) {
                ((grHomeRun_MainGroundVars*) &gp->gv.homerun)->gobjs[i] =
                    ((grHomeRun_MainGroundVars*) &gp->gv.homerun)
                        ->gobjs[i - 1];
            }
            ((grHomeRun_MainGroundVars*) &gp->gv.homerun)->gobjs[0] = gobj2;
        }

        for (i = 63; i >= 0; i--) {
            gobj2 = ((grHomeRun_MainGroundVars*) &gp->gv.homerun)->gobjs[i];
            if (gobj2 != NULL) {
                break;
            }
        }
        HSD_ASSERT(0x239, gobj2);
        gp2 = GET_GROUND(gobj2);
        if (gp2->gv.homerun.xC4 > x1) {
            ((grHomeRun_MainGroundVars*) &gp->gv.homerun)->gobjs[i] = NULL;
            Ground_801C4A08(gobj2);
        } else if (gp2->gv.homerun.xC4 < x1) {
            ((grHomeRun_MainGroundVars*) &gp->gv.homerun)->gobjs[i + 1] =
                grHomeRun_8021E500(gp2->gv.homerun.xC4 + 1);
        }

        x = 0.85F * cam_interest.x;
        while (true) {
            f32 diff = x - cam_interest.x;
            if (diff < 0.5F * -(2150.99F * Ground_801C0498())) {
                x += 2150.99F * Ground_801C0498();
            } else if (diff > 0.5F * (2150.99F * Ground_801C0498())) {
                x -= 2150.99F * Ground_801C0498();
            } else {
                break;
            }
        }

        jobj =
            GET_JOBJ(((grHomeRun_MainGroundVars*) &gp->gv.homerun)->rear_gobj);
        HSD_ASSERT(0x257, jobj);
        HSD_JObjSetTranslateX(jobj, x - 1.5F * (2150.99F * Ground_801C0498()));

        jobj = GET_JOBJ(
            ((grHomeRun_MainGroundVars*) &gp->gv.homerun)->rear2_gobj);
        HSD_ASSERT(0x259, jobj);

        HSD_JObjSetTranslateX(jobj, x - 0.5F * (2150.99F * Ground_801C0498()));

        jobj = GET_JOBJ(
            ((grHomeRun_MainGroundVars*) &gp->gv.homerun)->rear3_gobj);
        HSD_ASSERT(0x25B, jobj);

        HSD_JObjSetTranslateX(jobj, x + 0.5F * (2150.99F * Ground_801C0498()));

        jobj = GET_JOBJ(
            ((grHomeRun_MainGroundVars*) &gp->gv.homerun)->rear4_gobj);
        HSD_ASSERT(0x25D, jobj);

        HSD_JObjSetTranslateX(jobj, x + 1.5F * (2150.99F * Ground_801C0498()));

        lb_800115F4();
        Ground_801C2FE0(gobj);
        mpLib_80056758(3, 0.0F, 0.0F, 20000.0F, 0.0F);
        mpJointUpdateBounding(0);
    }
}

void grHomeRun_8021DEB0(Ground_GObj* arg) {}

void grHomeRun_8021DEB4(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138((HSD_GObj*) gobj, gp->map_id, 0);
}

bool grHomeRun_8021DEE0(Ground_GObj* arg)
{
    return false;
}

void grHomeRun_8021DEE8(Ground_GObj* arg) {}

void grHomeRun_8021DEEC(Ground_GObj* arg) {}

void grHomeRun_8021DEF0(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->gv.unk.xC8 = 0;
    gp->gv.unk.xCC = (int) Ground_801C3FA4(gobj, 1);
}

bool grHomeRun_8021DF48(Ground_GObj* arg)
{
    return false;
}

void grHomeRun_8021DF50(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    if ((u32) gp->gv.unk.xCC != 0) {
        if ((u32) gp->gv.unk.xC8 == 0) {
            Vec3 pos;
            f32 scale;
            f32 y, z;
            HSD_Text* text;

            gp->gv.unk.xC8 = (int) grHomeRun_8021EC58(gp->gv.homerun.xC6);
            lb_8000B1CC((HSD_JObj*) gp->gv.unk.xCC, NULL, &pos);

            scale = Ground_801C0498();
            z = pos.z + 0.0F * (grHr_804D6AE4 * scale);

            scale = Ground_801C0498();
            y = -pos.y + 0.0F * (grHr_804D6AE4 * scale);

            scale = Ground_801C0498();
            text = (HSD_Text*) gp->gv.unk.xC8;
            text->pos_x = pos.x + (-1.0F) * (grHr_804D6AE4 * scale);
            text->pos_y = y;
            text->pos_z = z;
        }
    }
}

void grHomeRun_8021E008(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    if ((u32) gp->gv.unk.xC8 != 0) {
        HSD_SisLib_803A5CC4((HSD_Text*) gp->gv.unk.xC8);
    }
}

void grHomeRun_8021E038(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, false);
}

bool grHomeRun_8021E064(Ground_GObj* arg)
{
    return false;
}

void grHomeRun_8021E06C(Ground_GObj* arg) {}

void grHomeRun_8021E070(Ground_GObj* arg) {}

void grHomeRun_8021E074(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->gv.unk.xC8 = 0;
    gp->gv.unk.xCC = (int) Ground_801C3FA4(gobj, 1);
}

bool grHomeRun_8021E0CC(Ground_GObj* arg)
{
    return false;
}

void grHomeRun_8021E0D4(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    if ((u32) gp->gv.unk.xCC != 0) {
        if ((u32) gp->gv.unk.xC8 == 0) {
            Vec3 pos;
            f32 scale;
            f32 y, z;
            HSD_Text* text;

            gp->gv.unk.xC8 = (int) grHomeRun_8021EC58(gp->gv.homerun.xC6);
            lb_8000B1CC((HSD_JObj*) gp->gv.unk.xCC, NULL, &pos);

            scale = Ground_801C0498();
            z = pos.z + 0.0F * (grHr_804D6AE4 * scale);

            scale = Ground_801C0498();
            y = -pos.y + 0.0F * (grHr_804D6AE4 * scale);

            scale = Ground_801C0498();
            text = (HSD_Text*) gp->gv.unk.xC8;
            text->pos_x = pos.x + (-1.0F) * (grHr_804D6AE4 * scale);
            text->pos_y = y;
            text->pos_z = z;
        }
    }
}

void grHomeRun_8021E18C(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    if ((u32) gp->gv.unk.xC8 != 0) {
        HSD_SisLib_803A5CC4((HSD_Text*) gp->gv.unk.xC8);
    }
}

void grHomeRun_8021E1BC(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, false);
}

bool grHomeRun_8021E1E8(Ground_GObj* arg)
{
    return false;
}

void grHomeRun_8021E1F0(Ground_GObj* arg) {}

void grHomeRun_8021E1F4(Ground_GObj* arg) {}

void grHomeRun_8021E1F8(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->gv.unk.xC8 = 0;
    gp->gv.unk.xCC = (int) Ground_801C3FA4(gobj, 1);
}

bool grHomeRun_8021E250(Ground_GObj* arg)
{
    return false;
}

void grHomeRun_8021E258(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    if ((u32) gp->gv.unk.xCC != 0) {
        if ((u32) gp->gv.unk.xC8 == 0) {
            Vec3 pos;
            f32 scale;
            f32 y, z;
            HSD_Text* text;

            gp->gv.unk.xC8 = (int) grHomeRun_8021EC58(gp->gv.homerun.xC6);
            lb_8000B1CC((HSD_JObj*) gp->gv.unk.xCC, NULL, &pos);

            scale = Ground_801C0498();
            z = pos.z + 0.0F * (grHr_804D6AE4 * scale);

            scale = Ground_801C0498();
            y = -pos.y + 0.0F * (grHr_804D6AE4 * scale);

            scale = Ground_801C0498();
            text = (HSD_Text*) gp->gv.unk.xC8;
            text->pos_x = pos.x + (-1.0F) * (grHr_804D6AE4 * scale);
            text->pos_y = y;
            text->pos_z = z;
        }
    }
}

void grHomeRun_8021E310(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    if ((u32) gp->gv.unk.xC8 != 0) {
        HSD_SisLib_803A5CC4((HSD_Text*) gp->gv.unk.xC8);
    }
}

void grHomeRun_8021E340(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, false);
}

bool grHomeRun_8021E36C(Ground_GObj* arg)
{
    return false;
}

void grHomeRun_8021E374(Ground_GObj* arg) {}

void grHomeRun_8021E378(Ground_GObj* arg) {}

void grHomeRun_8021E37C(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->gv.unk.xC8 = 0;
    gp->gv.unk.xCC = (int) Ground_801C3FA4(gobj, 1);
}

bool grHomeRun_8021E3D4(Ground_GObj* arg)
{
    return false;
}

void grHomeRun_8021E3DC(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    if ((u32) gp->gv.unk.xCC != 0) {
        if ((u32) gp->gv.unk.xC8 == 0) {
            Vec3 pos;
            f32 scale;
            f32 y, z;
            HSD_Text* text;

            gp->gv.unk.xC8 = (int) grHomeRun_8021EC58(gp->gv.homerun.xC6);
            lb_8000B1CC((HSD_JObj*) gp->gv.unk.xCC, NULL, &pos);

            scale = Ground_801C0498();
            z = pos.z + 0.0F * (grHr_804D6AE4 * scale);

            scale = Ground_801C0498();
            y = -pos.y + 0.0F * (grHr_804D6AE4 * scale);

            scale = Ground_801C0498();
            text = (HSD_Text*) gp->gv.unk.xC8;
            text->pos_x = pos.x + (-1.0F) * (grHr_804D6AE4 * scale);
            text->pos_y = y;
            text->pos_z = z;
        }
    }
}

void grHomeRun_8021E494(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    if ((u32) gp->gv.unk.xC8 != 0) {
        HSD_SisLib_803A5CC4((HSD_Text*) gp->gv.unk.xC8);
    }
}

void grHomeRun_8021E4C4(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, false);
}

bool grHomeRun_8021E4F0(Ground_GObj* arg)
{
    return false;
}

void grHomeRun_8021E4F8(Ground_GObj* arg) {}

void grHomeRun_8021E4FC(Ground_GObj* arg) {}

HSD_GObj* grHomeRun_8021E500(s16 arg0)
{
    HSD_JObj* jobj;
    s32 gobj_id;
    HSD_GObj* gobj;
    HSD_JObj* child;
    Ground* gp;
    s32 idx;
    f32 offset;

    idx = (arg0 / grHr_804D6ADC) % 4;
    if (idx == 0) {
        if (grHr_804D6ADC - 1 != arg0 % grHr_804D6ADC) {
            gobj_id = 4;
        } else {
            gobj_id = 5;
        }
    } else if (idx == 1) {
        if (grHr_804D6ADC - 1 != arg0 % grHr_804D6ADC) {
            gobj_id = 1;
        } else {
            gobj_id = 2;
        }
    } else if (idx == 2) {
        if (grHr_804D6ADC - 1 != arg0 % grHr_804D6ADC) {
            gobj_id = 6;
        } else {
            gobj_id = 7;
        }
    } else if (idx == 3) {
        if (grHr_804D6ADC - 1 != arg0 % grHr_804D6ADC) {
            gobj_id = 8;
        } else {
            gobj_id = 9;
        }
    } else {
        HSD_ASSERT(0x3D2, 0);
    }

    gobj = grHomeRun_8021C82C_noinline(gobj_id);
    HSD_ASSERT(0x3D5, gobj);
    jobj = GET_JOBJ(gobj);
    HSD_ASSERT(0x3D6, jobj);
    gp = GET_GROUND(gobj);
    HSD_ASSERT(0x3D7, gp);

    HSD_JObjSetScaleX(jobj, grHr_804D6AE4 * HSD_JObjGetScaleX(jobj));
    HSD_JObjSetScaleY(jobj, grHr_804D6AE4 * HSD_JObjGetScaleY(jobj));
    HSD_JObjSetScaleZ(jobj, grHr_804D6AE4 * HSD_JObjGetScaleZ(jobj));

    child = HSD_JObjGetChild(jobj);
    HSD_JObjSetTranslateX(child, 0.0F);

    offset = grHr_804D6AE4 * ((f32) arg0 * (160.0F * Ground_801C0498()));
    gp->gv.homerun.xD0 =
        (160.0F * (grHr_804D6AE4 * Ground_801C0498())) + offset;
    HSD_JObjSetTranslateX(jobj, gp->gv.homerun.xD0);

    gp->gv.homerun.xC6 =
        (s16) ((s32) grHr_804D6AE0 * ((arg0 + 1) / grHr_804D6ADC));
    gp->gv.homerun.xC4 = arg0;
    return gobj;
}

void fn_8021E994(Ground* arg0, s32 arg1, CollData* arg2, s32 arg3,
                 mpLib_GroundEnum arg4, f32 arg5)
{
    HSD_GObj* gobj;
    Ground* gp;
    s32 collKind = arg2->x34_flags.b1234;
    Ground* new_var;
    gobj = Ground_801C2BA4(0xA);
    if (gobj != NULL) {
        gp = (new_var = GET_GROUND(gobj));
        if (gp == NULL) {
            arg2->x34_flags = arg2->x34_flags;
            return;
        }
        if (collKind == 1) {
            gobj = gm_80180AF4();
            if (arg2->x0_gobj == gobj && arg4 == 1) {
                ((grHomeRun_MainGroundVars*) &gp->gv.homerun)->xE8_flags.b0 =
                    1;
            }
        }
    }
}

void grHomeRun_8021EA30(f32* pos)
{
    float new_var;
    f32 result;
    f32 time;

    time = Ground_801C0498();
    result = *pos - 70.0F * (grHr_804D6AE4 * time);

    time = Ground_801C0498();
    new_var = 160.0F * time;
    new_var = ((f32) grHr_804D6ADC) * new_var;
    result /= grHr_804D6AE4 * new_var;
    result *= grHr_804D6AE0;

    if (result < 0.0F) {
        result = 0.0F;
    }

    if (lbLang_IsSavedLanguageUS()) {
        result *= 0.304788;
    }

    stage_info.x6E0 = 100.0F * result;
    PAD_STACK(8);
}

void grHomeRun_8021EAF8(void)
{
    stage_info.flags |= (1 << 7);
}

/// Copies the main camera into a target camera
void fn_8021EB10(HSD_GObj* target_cam_gobj)
{
    HSD_GObj* main_cam_gobj;
    HSD_CObj* main_cam_cobj;
    HSD_CObj* target_cam_cobj;

    f32 fov;
    f32 aspect;
    HSD_RectF32 viewport;
    Scissor scissor;
    Vec3 position;

    target_cam_cobj = GET_COBJ(target_cam_gobj);
    main_cam_gobj = Camera_80030A50();
    if (main_cam_gobj) {
        if ((main_cam_cobj = GET_COBJ(main_cam_gobj))) {
            HSD_CObjSetFlags(target_cam_cobj, HSD_CObjGetFlags(main_cam_cobj));
            HSD_CObjGetViewportf(main_cam_cobj, &viewport);
            HSD_CObjSetViewportf(target_cam_cobj, &viewport);
            HSD_CObjGetScissor(main_cam_cobj, &scissor);
            HSD_CObjSetScissor(target_cam_cobj, &scissor);
            target_cam_cobj->u = main_cam_cobj->u;
            HSD_CObjSetNear(target_cam_cobj, HSD_CObjGetNear(main_cam_cobj));
            HSD_CObjSetFar(target_cam_cobj, HSD_CObjGetFar(main_cam_cobj));

            HSD_CObjGetPerspective(main_cam_cobj, &fov, &aspect);
            HSD_CObjSetPerspective(target_cam_cobj, fov, aspect);
            HSD_CObjGetEyePosition(main_cam_cobj, &position);
            HSD_CObjSetEyePosition(target_cam_cobj, &position);
            HSD_CObjGetInterest(main_cam_cobj, &position);
            HSD_CObjSetInterest(target_cam_cobj, &position);
        }
    }
    if (HSD_CObjSetCurrent(target_cam_cobj) != 0) {
        HSD_FogSet(NULL);
        HSD_GObj_80390ED0(target_cam_gobj, 7U);
        HSD_CObjEndCurrent();
    }
}

HSD_Text* grHomeRun_8021EC58(int arg)
{
    GXColor color = { 0xFF, 0xFF, 0xFF, 0xFF };
    HSD_Text* text;
    f32 temp;

    text = HSD_SisLib_803A6754(1, 0);
    text->pos_z = 0.0F;

    temp = grHr_804D6AE4 * Ground_801C0498() * 8.0F;
    text->box_size_x = grHr_804D6AE4 * Ground_801C0498() * 13.0F;
    text->box_size_y = temp;
    text->default_kerning = 0;

    temp = grHr_804D6AE4 * Ground_801C0498() * 0.2F;
    text->x34.x = grHr_804D6AE4 * Ground_801C0498() * 0.2F;
    text->x34.y = temp;
    text->text_color = color;
    text->default_alignment = 1;
    text->default_fitting = 1;
    text->x4C = 1;

    HSD_SisLib_803A6B98(text, 0.0F, -29.0F, "%d", (s32) (f32) arg);

    return text;
}

void grHomeRun_8021ED74(void)
{
    BobOmbRain bobomb_rain;
    HSD_JObj* jobj = Ground_801C2CF4(0x7F);
    bobomb_rain.x0 = NULL;
    bobomb_rain.x4 = NULL;
    bobomb_rain.x14 = 0xB;
    bobomb_rain.x18 = 0;
    bobomb_rain.x1C.b0 = 1;
    lb_8000B1CC(jobj, NULL, &bobomb_rain.x8_vec);
    it_8026BE84(&bobomb_rain);
}

void grHomeRun_8021EDD4(void)
{
    f32 scale;
    f32 max_dist;
    f32 ratio;
    f32 num_ticks;
    f32 dist;

    if (lbLang_IsSavedLanguageJP()) {
        scale = 0.1F;
        max_dist = 50.0F;
    } else {
        scale = 0.3280969F;
        max_dist = 100.0F;
    }

    ratio = max_dist / scale;
    num_ticks = (int) (0.5F + ratio / (160.0F * Ground_801C0498()));

    if (num_ticks < 1.0F) {
        num_ticks = 1.0F;
    }

    dist = 160.0F * Ground_801C0498();
    grHr_804D6AD8 = scale;
    grHr_804D6AE0 = max_dist;
    grHr_804D6ADC = num_ticks;
    grHr_804D6AE4 = ratio / (num_ticks * dist);
}

DynamicsDesc* grHomeRun_8021EEB4(enum_t arg)
{
    return false;
}

bool grHomeRun_8021EEBC(Vec3* a, int b, HSD_JObj* jobj)
{
    Vec3 vec;
    lb_8000B1CC(jobj, NULL, &vec);
    if (a->y > vec.y) {
        return true;
    } else {
        return false;
    }
}

extern f32 grHr_804DBC94;

f32 grHomeRun_8021EF10(void)
{
    return grHr_804DBC94 * Ground_801C0498();
}
