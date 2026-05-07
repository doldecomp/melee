#include "grmutecity.h"

#include "grmutecity.static.h"

#include "types.h"

#include <platform.h>

#include "cm/camera.h"

#include "forward.h"

#include "gr/grdatfiles.h"
#include "gr/grdisplay.h"
#include "gr/grfzerocar.h"
#include "gr/grlib.h"
#include "gr/grmaterial.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "gr/stage.h"
#include "if/ifhazard.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbshadow.h"
#include "lb/lbvector.h"
#include "mp/mplib.h"
#include "MSL/math.h"
#include "MSL/trigf.h"
#include "sysdolphin/baselib/spline.h"

#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>
#include <baselib/lobj.h>
#include <baselib/psappsrt.h>
#include <baselib/psstructs.h>

extern s16 grMc_803E34A4[];
extern Vec3 grMc_803B81B8;

typedef void (*grMc_SpeedFn)(Item_GObj*, Ground*, Vec3*, HSD_GObj*, f32);

typedef struct grMc_CmdEntry {
    s32 frame;
    s16 cmd;
    s16 param;
    f32 fval;
} grMc_CmdEntry;

extern grMc_CmdEntry grMc_803E34E0[];

typedef struct grMc_TrackInitData {
    f32 pos;
    f32 speed;
} grMc_TrackInitData;

extern grMc_TrackInitData grMc_803E3B7C[];

static s32 grMc_8049F440[30];

static StageCallbacks grMc_803E30C4[39] = {
    {
        NULL,
        NULL,
        NULL,
        NULL,
        0,
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
        0,
    },
    {
        grMuteCity_801F044C,
        grMuteCity_801F04A8,
        grMuteCity_801F04B0,
        grMuteCity_801F04B4,
        0,
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
        0,
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
        0,
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
        0,
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
        0,
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
        0,
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
        0,
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
        0,
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
        0,
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
        0,
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
        0,
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
        0,
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
        0,
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
        0,
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
        0,
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
        0,
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
        0,
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
        0,
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
        0,
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
        0,
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
        0,
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
        0,
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
        0,
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
        0,
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
        0,
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
        0,
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
        0,
    },
    {
        grMuteCity_801F01B4,
        grMuteCity_801F0288,
        grMuteCity_801F0290,
        grMuteCity_801F040C,
        0,
    },
    {
        grMuteCity_801EFDF8,
        grMuteCity_801F0118,
        grMuteCity_801F0120,
        grMuteCity_801F01B0,
        0xC0000000,
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
        0,
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
        0,
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
        0,
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
        0,
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
        0,
    },
    {
        grMuteCity_801F0410,
        grMuteCity_801F043C,
        grMuteCity_801F0444,
        grMuteCity_801F0448,
        0,
    },
    {
        grMuteCity_801F0410,
        grMuteCity_801F043C,
        grMuteCity_801F0444,
        grMuteCity_801F0448,
        0,
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
        0,
    },
};

StageData grMc_803E33DC = {
    MUTECITY,
    grMc_803E30C4,
    "/GrMc.dat",
    grMuteCity_801EFC6C,
    grMuteCity_801EFC68,
    grMuteCity_801EFCDC,
    grMuteCity_801EFCE0,
    grMuteCity_801EFD04,
    grMuteCity_801F2BBC,
    grMuteCity_801F2C10,
    0x00000001,
    NULL,
    3,
};

static struct {
    int x0;
    void* x4;
    DynamicsDesc* x8;
    DynamicsDesc* xC;
    u8 pad10[0x1C];
    f32 x2C;
    f32 x30;
    f32 x34;
    f32 x38;
    f32 x3C;
    f32 x40;
    f32 x44;
    f32 x48;
    f32 x4C;
}* grMc_804D69D0;

static s32 grMc_804D69D4;

static f32 light_ref_br = 40000.0f;
static f32 light_ref_dist = 0.99f;
static s32 light_dist_func = 0x1;

void grMuteCity_801EFC68(bool arg) {}

void grMuteCity_801EFC6C(void)
{
    grMc_804D69D0 = Ground_801C49F8();
    stage_info.unk8C.b4 = 0;
    stage_info.unk8C.b5 = 0;
    grMuteCity_801EFD0C(0);
    Ground_801C39C0();
    Ground_801C3BB4();
    grMuteCity_801EFD0C(0x1E);
    un_802FD8C4(grMuteCity_801F28A8());
    un_802FD65C();
}

void grMuteCity_801EFCDC(void) {}

void grMuteCity_801EFCE0(void)
{
    grZakoGenerator_801CAE04(NULL);
}

bool grMuteCity_801EFD04(void)
{
    return false;
}

HSD_GObj* grMuteCity_801EFD0C(int gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grMc_803E30C4[gobj_id];

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
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", __FILE__, 292, gobj_id);
    }

    return gobj;
}

void grMuteCity_801EFDF8(Ground_GObj* gobj)
{
    Vec3 sp1C;
    Ground* gp = GET_GROUND(gobj);
    HSD_GObj* lgobj;
    HSD_LObj* lobj;
    PAD_STACK(12);

    grAnime_801C8138(gobj, gp->map_id, 0);
    grAnime_801C775C(gobj, 0, 7, 0.0f, 3600.0f);
    gp->gv.mutecity.xC4 = 0;
    gp->gv.mutecity.xC6 = 0;
    gp->gv.mutecity.xD2 = 0;
    gp->gv.mutecity.xD8 = 0.932775f;
    gp->gv.mutecity.xD4 = 0.932775f;
    gp->gv.mutecity.xD0_flags.b0 = 0;
    gp->gv.mutecity.xDC = Ground_801C3FA4(gobj, 5);
    gp->gv.mutecity.xE0 = Ground_801C3FA4(gobj, 9);
    if (gp->gv.mutecity.xE0->u.spline == NULL) {
        OSReport("not found car spline (R)\n");
        HSD_ASSERT(0x15F, 0);
    }
    if (gp->gv.mutecity.xDC->u.spline == NULL) {
        OSReport("not found car spline (L)\n");
        HSD_ASSERT(0x163, 0);
    }
    gp->gv.mutecity.xD0_flags.b23 = 2;
    gp->gv.mutecity.xE4.x = gp->gv.mutecity.xE4.y = gp->gv.mutecity.xE4.z =
        0.0f;
    gp->gv.mutecity.xF0.x = gp->gv.mutecity.xF0.y = gp->gv.mutecity.xF0.z =
        0.0f;
    gp->gv.mutecity.xFC = Ground_801C3FA4(gobj, 0xC);
    gp->gv.mutecity.x100 = Ground_801C3FA4(gobj, 0xD);
    gp->gv.mutecity.x104 = Ground_801C3FA4(gobj, 0xE);
    gp->gv.mutecity.x108 = Ground_801C3FA4(gobj, 0xF);
    gp->gv.mutecity.x10C = Ground_801C3FA4(gobj, 0x10);
    gp->x10_flags.b5 = 1;
    Stage_UnkSetVec3TCam_Offset(&sp1C);
    gp->gv.mutecity.x114 = Stage_GetCamBoundsTopOffset() - sp1C.y;
    gp->gv.mutecity.x118 = Stage_GetCamBoundsBottomOffset() - sp1C.y;
    gp->gv.mutecity.x11C = Stage_GetCamBoundsLeftOffset() - sp1C.x;
    gp->gv.mutecity.x120 = Stage_GetCamBoundsRightOffset() - sp1C.x;
    gp->gv.mutecity.x124 = Stage_GetBlastZoneTopOffset() - sp1C.y;
    gp->gv.mutecity.x128 = Stage_GetBlastZoneBottomOffset() - sp1C.y;
    gp->gv.mutecity.x12C = Stage_GetBlastZoneLeftOffset() - sp1C.x;
    gp->gv.mutecity.x130 = Stage_GetBlastZoneRightOffset() - sp1C.x;
    gp->gv.mutecity.xC8 = grMuteCity_801EFD0C(0x1D);
    gp->gv.mutecity.xCC = grMuteCity_801EFD0C(2);
    grMuteCity_801F1A34(gp->gv.mutecity.xCC, gobj);
    grMaterial_801C94D8(Ground_801C3FA4(gobj, 0xC));
    grMaterial_801C94D8(Ground_801C3FA4(gobj, 0xC));
    grMaterial_801C94D8(Ground_801C3FA4(gobj, 0xD));
    grMaterial_801C94D8(Ground_801C3FA4(gobj, 0xE));
    grMaterial_801C94D8(Ground_801C3FA4(gobj, 0xF));
    grMaterial_801C94D8(Ground_801C3FA4(gobj, 0x10));
    mpJointSetB10(4);
    mpJointSetCb1(4, gp, fn_801F2B58);
    lgobj = Ground_801C498C();
    gp->gv.mutecity.x110 = NULL;
    if (lgobj != NULL) {
        lobj = (HSD_LObj*) lgobj->hsd_obj;
        if (lobj != NULL) {
            while (lobj != NULL) {
                if ((u32) (lobj->flags & 3) == LOBJ_POINT) {
                    gp->gv.mutecity.x110 = lobj;
                    HSD_LObjSetFlags(gp->gv.mutecity.x110, LOBJ_HIDDEN);
                }
                if (lobj == NULL) {
                    lobj = NULL;
                } else {
                    lobj = lobj->next;
                }
            }
        }
    }
}

bool grMuteCity_801F0118(Ground_GObj* arg)
{
    return false;
}

void grMuteCity_801F0120(Ground_GObj* gobj)
{
    Ground* ground;
    HSD_LObj* lobj;

    ground = GET_GROUND(gobj);
    if (ground->gv.mutecity.x110 != NULL) {
        HSD_LObjSetDistAttn(ground->gv.mutecity.x110, light_ref_dist,
                            light_ref_br, light_dist_func);
    }
    grMuteCity_801F04B8(gobj);
    grMuteCity_801F0948(gobj);
    if (ground->gv.mutecity.xD0_flags.b0 != 0) {
        grMuteCity_801F0D20(gobj);
    }
    grMuteCity_801F1328();
    grMuteCity_801F1A34(ground->gv.mutecity.xCC, gobj);
    Ground_801C2FE0(gobj);
    lb_800115F4();
}

void grMuteCity_801F01B0(Ground_GObj* arg) {}

void grMuteCity_801F01B4(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);

    Ground_801C2ED0(jobj, gp->map_id);
    grMaterial_801C94D8(jobj);
    grAnime_801C8138(gobj, gp->map_id, false);
    grAnime_801C775C(gobj, 0, 7, 0.0f, 3600.0f);
    grAnime_801C7FF8(gobj, 6, 7, 1, 0.0f, 1.0f);
    gp->x10_flags.b5 = 1;
    gp->gv.mutecity2.xC8 = Ground_801C3FA4(gobj, 6);
    gp->gv.mutecity2.xCC = 0.0f;
    gp->gv.mutecity2.xD0 = 0.0f;
    gp->gv.mutecity2.xC4_flags.b0 = 0;
}

bool grMuteCity_801F0288(Ground_GObj* arg)
{
    return false;
}

void grMuteCity_801F0290(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    f32 target = gp->gv.mutecity2.xCC;
    f32 current = gp->gv.mutecity2.xD0;
    f32 diff = target - current;

    if (diff > 0.0f) {
        if (diff < 0.001f) {
            gp->gv.mutecity2.xD0 = target;
        } else {
            gp->gv.mutecity2.xD0 = current + 0.001f;
        }
    } else if (diff < 0.0f) {
        if (diff > -0.001f) {
            gp->gv.mutecity2.xD0 = target;
        } else {
            gp->gv.mutecity2.xD0 = current - 0.001f;
        }
    } else {
        gp->gv.mutecity2.xD0 = target;
    }

    {
        f32 rot_z = HSD_JObjGetRotationZ(gp->gv.mutecity2.xC8);
        HSD_JObjSetRotationZ(gp->gv.mutecity2.xC8,
                             rot_z * gp->gv.mutecity2.xD0);
    }
    grMuteCity_801F290C(gobj);
    Ground_801C2FE0(gobj);
}

void grMuteCity_801F040C(Ground_GObj* arg) {}

void grMuteCity_801F0410(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grMuteCity_801F043C(Ground_GObj* arg)
{
    return false;
}

void grMuteCity_801F0444(Ground_GObj* arg) {}

void grMuteCity_801F0448(Ground_GObj* arg) {}

void grMuteCity_801F044C(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grFZeroCar_801CAFBC(gobj, grMc_803E34A4, 0x1C, 0);
    grMuteCity_801F0F4C(gobj);
    gp->gv.mutecity.xC4 = 0;
}

bool grMuteCity_801F04A8(Ground_GObj* arg)
{
    return false;
}

void grMuteCity_801F04B0(Ground_GObj* arg) {}

void grMuteCity_801F04B4(Ground_GObj* arg) {}

void grMuteCity_801F04B8(Ground_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Ground* gp = GET_GROUND(gobj);
    s32 cmd;
    s32 param;
    f32 fval;
    grMc_CmdEntry* entry;
    f32 frame;
    PAD_STACK(24);

    frame = Ground_801C3F20(jobj);

    if (gp->gv.mutecity.xC6 > 0) {
        gp->gv.mutecity.xC6 -= 1;
        return;
    }

    if (lb_8000B134(Ground_801C3FA4(gobj, 0x1A)) != 0) {
        gp->gv.mutecity.xC4 = 0;
        HSD_JObjReqAnimAll(gp->gv.mutecity.xC8->hsd_obj, 1.0f);
    }

    while (frame >= grMc_803E34E0[gp->gv.mutecity.xC4].frame) {
        entry = &grMc_803E34E0[gp->gv.mutecity.xC4];
        cmd = entry->cmd;
        param = entry->param;
        fval = entry->fval;

        switch (cmd) {
        case 1:
            gp->gv.mutecity.xC6 = entry->param;
            break;
        case 2:
            grAnime_801C7A04(gobj, 0, 1, 0.0f);
            grAnime_801C7A04(gp->gv.mutecity.xC8, 0, 7, 0.0f);
            grAnime_801C7A04(gobj, 0x11, 7, 1.0f);
            grAnime_801C7A04(gp->gv.mutecity.xC8, 6, 7, 1.0f);
            break;
        case 3:
            grAnime_801C7A04(gobj, 0, 1, 1.0f);
            grAnime_801C7A04(gp->gv.mutecity.xC8, 0, 7, 1.0f);
            break;
        case 4:
            mpLib_80057BC0(entry->param);
            break;
        case 5:
            mpJointListAdd(entry->param);
            break;
        case 6:
            grMc_804D69D4 = 0;
            break;
        case 7:
            grMc_804D69D4 = 1;
            break;
        case 8:
            mpLib_80057BC0(4);
            gp->gv.mutecity.xD0_flags.b0 = 0;
            break;
        case 18:
            gp->gv.mutecity.xD0_flags.b1 = 1;
            break;
        case 19:
            gp->gv.mutecity.xD0_flags.b1 = 0;
            break;
        case 9:
            mpJointListAdd(4);
            gp->gv.mutecity.xD0_flags.b0 = 1;
            gp->gv.mutecity.xD4 = fval;
            gp->gv.mutecity.xD8 = fval;
            break;
        case 11: {
            HSD_JObj* j = Ground_801C3FA4(gp->gv.mutecity.xC8, entry->param);
            if (j != NULL) {
                HSD_JObjSetFlagsAll(j, JOBJ_HIDDEN);
            }
            break;
        }
        case 12: {
            HSD_JObj* j = Ground_801C3FA4(gp->gv.mutecity.xC8, entry->param);
            if (j != NULL) {
                HSD_JObjClearFlagsAll(j, JOBJ_HIDDEN);
            }
            break;
        }
        case 13:
            Ground_801C3880(fval * Ground_801C0498());
            if (fval > gp->gv.mutecity.x114) {
                Ground_801C3980(fval +
                                (gp->gv.mutecity.x124 - gp->gv.mutecity.x114));
            }
            break;
        case 14:
            Ground_801C3890(fval * Ground_801C0498());
            if (fval < gp->gv.mutecity.x118) {
                Ground_801C3990(fval +
                                (gp->gv.mutecity.x128 - gp->gv.mutecity.x118));
            }
            break;
        case 15:
            Ground_801C38A0(fval * Ground_801C0498());
            if (fval < gp->gv.mutecity.x11C) {
                Ground_801C39A0(fval +
                                (gp->gv.mutecity.x12C - gp->gv.mutecity.x11C));
            }
            break;
        case 16:
            Ground_801C38AC(fval * Ground_801C0498());
            if (fval > gp->gv.mutecity.x120) {
                Ground_801C39B0(fval +
                                (gp->gv.mutecity.x130 - gp->gv.mutecity.x120));
            }
            break;
        case 17:
            Ground_801C3880(gp->gv.mutecity.x114);
            Ground_801C3890(gp->gv.mutecity.x118);
            Ground_801C38A0(gp->gv.mutecity.x11C);
            Ground_801C38AC(gp->gv.mutecity.x120);
            Ground_801C3980(gp->gv.mutecity.x124);
            Ground_801C3990(gp->gv.mutecity.x128);
            Ground_801C39A0(gp->gv.mutecity.x12C);
            Ground_801C39B0(gp->gv.mutecity.x130);
            break;
        case 21:
            grMaterial_801C9604(gobj, grMc_804D69D0->x0, 0);
            break;
        case 20:
            un_802FD604(entry->param);
            Ground_801C53EC(0x5CC6A);
            break;
        case 22:
            ((Ground*) gp->gv.mutecity.xC8->user_data)->gv.mutecity2.xCC =
                fval;
            break;
        case 23:
            if (param != 0) {
                lbAudioAx_80024D78(2);
            } else {
                lbAudioAx_80024D78(1);
            }
            break;
        case 25:
            if (param != 0) {
                mpLib_80054D68(0x32, 0xC);
                mpLib_80054D68(0x34, 0xC);
            } else {
                mpLib_80054D68(0x32, 0);
                mpLib_80054D68(0x34, 0);
            }
            break;
        case 24: {
            HSD_GObj* bg_gobj = Ground_801C2BA4(0x1D);
            if (bg_gobj != NULL) {
                if (param != 0) {
                    grMaterial_801C9604(bg_gobj, (s32) grMc_804D69D0->x4, 0);
                    if (gp->gv.mutecity.x110 != NULL) {
                        HSD_LObjClearFlags(gp->gv.mutecity.x110, LOBJ_HIDDEN);
                    }
                } else {
                    grMaterial_801C95C4(bg_gobj);
                    if (gp->gv.mutecity.x110 != NULL) {
                        HSD_LObjSetFlags(gp->gv.mutecity.x110, LOBJ_HIDDEN);
                    }
                }
            }
            break;
        }
        case 26:
            gp->gv.mutecity.xD0_flags.b23 = param;
            break;
        }

        gp->gv.mutecity.xC4 += 1;
        if ((u32) gp->gv.mutecity.xC4 == 0x84) {
            gp->gv.mutecity.xC4 = 0;
        }
        if (cmd == 1) {
            break;
        }
    }
}

void grMuteCity_801F0948(Ground_GObj* arg) {}

static inline void grMc_SplineEvalWrapped(Vec3* result, HSD_Spline* spline,
                                          f32 t)
{
    Vec3 a, b;
    f32 frac;
    f32 scale;

    if (t > 0.93f) {
        frac = t - 0.93f;
    } else if (t < 0.01f) {
        frac = 0.06999999f + t;
    } else {
        splGetSplinePoint(result, spline, t);
        return;
    }
    splGetSplinePoint(&a, spline, 0.93f);
    splGetSplinePoint(&b, spline, 0.01f);
    lbVector_Sub(&b, &a);
    scale = frac / 0.07999999f;
    b.x *= scale;
    b.y *= scale;
    b.z *= scale;
    lbVector_Add(&b, &a);
    *result = b;
}

f32 grMuteCity_801F094C(HSD_JObj* arg0, HSD_Spline* arg1, Vec3* arg2,
                        f32 var_f29)
{
    Vec3 sp78;
    Vec3 sp6C;
    Vec3 sp60;
    f32 var_f0;
    f32 var_f1;
    f32 var_f31;
    f32 var_f30;

    grMc_SplineEvalWrapped(&sp78, arg1, var_f29);
    lb_8000B1CC(arg0, &sp78, &sp6C);

    var_f1 = var_f29 - 0.0004f;
    if (var_f1 < 0.0) {
        var_f1 += 1.0f;
    }

    grMc_SplineEvalWrapped(&sp78, arg1, var_f1);
    lb_8000B1CC(arg0, &sp78, &sp60);

    if (sp6C.z > sp60.z) {
        var_f30 = 0.0004f;
    } else {
        var_f30 = -0.0004f;
    }
    var_f31 = -var_f30;

    while ((sp60.z > 0.0f && sp6C.z > 0.0f) ||
           (sp60.z < 0.0f && sp6C.z < 0.0f))
    {
        if (sp6C.z < 0.0f) {
            var_f0 = var_f30;
        } else {
            var_f0 = var_f31;
        }
        var_f29 += var_f0;
        if (var_f29 > 1.0f) {
            var_f29 -= 1.0f;
        } else if (var_f29 < 0.0f) {
            var_f29 += 1.0f;
        }
        sp60 = sp6C;
        grMc_SplineEvalWrapped(&sp78, arg1, var_f29);
        lb_8000B1CC(arg0, &sp78, &sp6C);
    }

    *arg2 = sp6C;
    return var_f29;
}

void grMuteCity_801F0D20(Ground_GObj* gobj)
{
    Vec3 sp28;
    Vec3 sp1C;
    Vec3 sp10;
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj;
    u32 mode;

    jobj = gp->gv.mutecity.xE0;
    gp->gv.mutecity.xD8 =
        grMuteCity_801F094C(jobj, jobj->u.spline, &sp28, gp->gv.mutecity.xD8);
    jobj = gp->gv.mutecity.xDC;
    gp->gv.mutecity.xD4 =
        grMuteCity_801F094C(jobj, jobj->u.spline, &sp1C, gp->gv.mutecity.xD4);
    mpLib_80057424(4);
    mode = gp->gv.mutecity.xD0_flags.b23;

    if (mode == 1) {
        mpLineSetPos(0x31, sp28.x, 30.0f + sp28.y, sp28.x, sp28.y);
        mpLineSetPos(0x35, sp1C.x, sp1C.y, sp1C.x, 30.0f + sp1C.y);
    } else if (mode == 2) {
        f32 angle, angle_fwd, angle_back, tmp;
        angle = atan2f(sp1C.y - sp28.y, sp1C.x - sp28.x);
        angle_fwd = 0.2617994f + angle;
        angle_back = (3.1415927f + angle) - 0.2617994f;
        tmp = (10.0f * sinf(angle_back)) + sp28.y;
        mpLineSetPos(0x31, (10.0f * cosf(angle_back)) + sp28.x, tmp, sp28.x,
                     sp28.y);
        tmp = (10.0f * sinf(angle_fwd)) + sp1C.y;
        mpLineSetPos(0x35, sp1C.x, sp1C.y, (10.0f * cosf(angle_fwd)) + sp1C.x,
                     tmp);
    } else {
        mpLineSetPos(0x31, sp28.x - 5.0f, sp28.y, sp28.x, sp28.y);
        mpLineSetPos(0x35, sp1C.x, sp1C.y, 5.0f + sp1C.x, sp1C.y);
    }

    gp->gv.mutecity.xE4 = sp28;
    gp->gv.mutecity.xF0 = sp1C;
    lbVector_Diff(&sp1C, &sp28, &sp10);
    mpLineSetPos(0x33, (0.35f * sp10.x) + sp28.x, (0.35f * sp10.y) + sp28.y,
                 (0.65f * sp10.x) + sp28.x, (0.65f * sp10.y) + sp28.y);
    mpLib_80055E24(4);
    mpLib_8005667C(4);
}

void grMuteCity_801F0F4C(Ground_GObj* gobj)
{
    f32 pos;
    grMc_TrackInitData* src = grMc_803E3B7C;
    grMc_CarEntry* dst = grMc_8049F4B8;
    s32* idx = grMc_8049F440;
    int i;

    for (i = 0; i < 30; i++) {
        pos = src->pos;
        if (pos > 1.0) {
            pos--;
        } else if (pos < 0.0) {
            pos++;
        }
        dst->x0 = pos;
        dst->x4 = pos;
        dst->xC = src->speed;
        dst->x8 = 0.0f;
        dst->x10 = 0.0f;
        dst->x20 = 0;
        dst->x22_flags.b0 = 0;
        dst->x22_flags.b1 = 0;
        dst->x24 = 0;
        dst->x28 = 0;
        dst++;
        src++;
        *idx++ = i;
    }
}

void grMuteCity_801F106C(s32 i)
{
    f32 var_f0;
    grMc_CarEntry* car = &grMc_8049F4B8[i];
    u16 flags16 = car->x20;

    if (!car->x22_flags.b0) {
        if (flags16 & 1) {
            if (flags16 & 8) {
                car->x8 -= grMc_804D69D0->x4C;
            } else {
                s32 rnd = HSD_Randi(4);
                switch (rnd) {
                case 3:
                    break;
                case 0:
                    car->x8 -= grMc_804D69D0->x4C;
                    break;
                default:
                    if (flags16 & 4) {
                        car->xC += grMc_804D69D0->x44;
                        if (car->xC > 0.9) {
                            car->xC = 0.9f;
                        }
                    } else {
                        car->xC -= grMc_804D69D0->x44;
                        if (car->xC < 0.1) {
                            car->xC = 0.1f;
                        }
                    }
                    break;
                }
            }
        } else {
            car->x8 += grMc_804D69D0->x40;
            if (car->xC > (0.7f + grMc_804D69D0->x48)) {
                car->xC -= grMc_804D69D0->x48;
            } else if (car->xC < (0.3f - grMc_804D69D0->x48)) {
                car->xC += grMc_804D69D0->x48;
            }
        }
        if (flags16 & 8) {
            if (flags16 & 4) {
                car->xC += grMc_804D69D0->x44;
                if (car->xC > 1.0) {
                    car->xC = 1.0f;
                }
            } else {
                car->xC -= grMc_804D69D0->x44;
                if (car->xC < 0.0) {
                    car->xC = 0.0f;
                }
            }
        }
        if (flags16 & 0x10) {
            var_f0 = grMc_804D69D0->x38;
        } else if (flags16 & 0x20) {
            var_f0 = grMc_804D69D0->x3C;
        } else {
            var_f0 = grMc_804D69D0->x34;
        }
        if (car->x8 > var_f0) {
            car->x8 = var_f0;
            return;
        }
        if (car->x8 < 0.0) {
            car->x8 = 0.0f;
        }
    } else {
        if ((car->x4 > 0.827f) && (car->x4 < 0.914f)) {
            if (car->x8 < 0.001f) {
                car->x8 = 0.001f;
            }
        } else {
            car->x8 *= 0.95f;
            if (car->x8 < 0.00001f) {
                car->x8 = 0.0f;
            }
        }
    }
}

void grMuteCity_801F1328(void)
{
    s32* arr = grMc_8049F440;
    int i, j;

    for (i = 1; i < 30; i++) {
        j = i;
        while (j > 0 &&
               grMc_8049F4B8[arr[j]].x0 > grMc_8049F4B8[arr[j - 1]].x0)
        {
            s32 temp = arr[j];
            arr[j] = arr[j - 1];
            arr[j - 1] = temp;
            j--;
        }
    }

    for (i = 0; i < 30; i++) {
        grMc_8049F4B8[arr[i]].x20 = 0;
    }

    for (i = 0; i < 30; i++) {
        grMc_CarEntry* my_car = &grMc_8049F4B8[arr[i]];
        if (my_car->x22_flags.b0) {
            continue;
        }
        for (j = 1; j < 30; j++) {
            s32 idx = i + j;
            grMc_CarEntry* other_car;
            f32 other_pos;
            f32 my_pos;
            f32 dist;

            if (idx >= 30) {
                idx -= 30;
            }
            other_car = &grMc_8049F4B8[arr[idx]];

            if (other_car->x22_flags.b0) {
                continue;
            }

            other_pos = other_car->x4;
            my_pos = my_car->x4;
            if (my_pos > other_pos) {
                dist = my_pos - other_pos;
            } else {
                dist = 1.0f + (my_pos - other_pos);
            }

            if (dist > 0.002) {
                break;
            }
            other_car->x20 |= 1;

            {
                f32 dx = my_car->x14 - other_car->x14;
                f32 dy = my_car->x18 - other_car->x18;
                f32 dz = my_car->x1C - other_car->x1C;
                if (((dz * dz) + ((dx * dx) + (dy * dy))) < 900.0f) {
                    my_car->x20 |= 8;
                    other_car->x20 |= 8;
                }
            }

            if (my_car->xC > other_car->xC) {
                my_car->x20 |= 4;
                other_car->x20 |= 2;
            } else {
                my_car->x20 |= 2;
                other_car->x20 |= 4;
            }
        }
    }

    for (i = 0; i < 5; i++) {
        grMc_8049F4B8[arr[i]].x20 |= 0x10;
    }
    for (i = 25; i < 30; i++) {
        grMc_8049F4B8[arr[i]].x20 |= 0x20;
    }
    for (i = 0; i < 30; i++) {
        grMuteCity_801F106C(i);
    }
}

void grMuteCity_801F173C(float arg0)
{
    grMc_8049F4B8[0].x10 += arg0;
}
void grMuteCity_801F1754(float arg0)
{
    grMc_8049F4B8[1].x10 += arg0;
}
void grMuteCity_801F176C(float arg0)
{
    grMc_8049F4B8[2].x10 += arg0;
}
void grMuteCity_801F1784(f32 arg0)
{
    grMc_8049F4B8[3].x10 += arg0;
}
void grMuteCity_801F179C(f32 arg0)
{
    grMc_8049F4B8[4].x10 += arg0;
}
void grMuteCity_801F17B4(f32 arg0)
{
    grMc_8049F4B8[5].x10 += arg0;
}
void grMuteCity_801F17CC(f32 arg0)
{
    grMc_8049F4B8[6].x10 += arg0;
}
void grMuteCity_801F17E4(f32 arg0)
{
    grMc_8049F4B8[7].x10 += arg0;
}
void grMuteCity_801F17FC(f32 arg0)
{
    grMc_8049F4B8[8].x10 += arg0;
}
void grMuteCity_801F1814(f32 arg0)
{
    grMc_8049F4B8[9].x10 += arg0;
}
void grMuteCity_801F182C(f32 arg0)
{
    grMc_8049F4B8[10].x10 += arg0;
}
void grMuteCity_801F1844(f32 arg0)
{
    grMc_8049F4B8[11].x10 += arg0;
}
void grMuteCity_801F185C(f32 arg0)
{
    grMc_8049F4B8[12].x10 += arg0;
}
void grMuteCity_801F1874(f32 arg0)
{
    grMc_8049F4B8[13].x10 += arg0;
}
void grMuteCity_801F188C(f32 arg0)
{
    grMc_8049F4B8[14].x10 += arg0;
}
void grMuteCity_801F18A4(f32 arg0)
{
    grMc_8049F4B8[15].x10 += arg0;
}
void grMuteCity_801F18BC(f32 arg0)
{
    grMc_8049F4B8[16].x10 += arg0;
}
void grMuteCity_801F18D4(f32 arg0)
{
    grMc_8049F4B8[17].x10 += arg0;
}
void grMuteCity_801F18EC(f32 arg0)
{
    grMc_8049F4B8[18].x10 += arg0;
}
void grMuteCity_801F1904(f32 arg0)
{
    grMc_8049F4B8[19].x10 += arg0;
}
void grMuteCity_801F191C(f32 arg0)
{
    grMc_8049F4B8[20].x10 += arg0;
}
void grMuteCity_801F1934(f32 arg0)
{
    grMc_8049F4B8[21].x10 += arg0;
}
void grMuteCity_801F194C(f32 arg0)
{
    grMc_8049F4B8[22].x10 += arg0;
}
void grMuteCity_801F1964(f32 arg0)
{
    grMc_8049F4B8[23].x10 += arg0;
}
void grMuteCity_801F197C(f32 arg0)
{
    grMc_8049F4B8[24].x10 += arg0;
}
void grMuteCity_801F1994(f32 arg0)
{
    grMc_8049F4B8[25].x10 += arg0;
}

void grMuteCity_801F19AC(f32 arg0)
{
    grMc_8049F4B8[26].x10 += arg0;
}
void grMuteCity_801F19C4(f32 arg0)
{
    grMc_8049F4B8[27].x10 += arg0;
}
void grMuteCity_801F19DC(f32 arg0)
{
    grMc_8049F4B8[28].x10 += arg0;
}
void grMuteCity_801F19F4(f32 arg0)
{
    grMc_8049F4B8[29].x10 += arg0;
}

void grMuteCity_801F1A0C(HSD_GObj* gobj, Ground* gp)
{
    Ground_801C53EC(0x5CC60);
}

void grMuteCity_801F1A34(HSD_GObj* arg0, Ground_GObj* arg1)
{
    Vec3 spE8;
    Vec3 spD8;
    Vec3 spCC;
    Vec3 spC0;
    Vec3 spB4;
    Vec3 spA8;
    Vec3 sp9C;
    Vec3 sp90;
    Vec3 sp74;
    Vec3 sp68;
    Vec3 sp5C;
    Vec3 sp50;
    Vec3 sp44;
    Vec3 sp38;
    Vec3 sp2C;
    Vec3 sp20;
    f32 spFC;
    f32 spF8;
    f32 spF4;
    f32 sp8C;
    f32 sp88;
    f32 sp84;
    f32 sp1C;
    s32 var_r26 = 0;
    Ground* car_gp = arg0->user_data;
    Ground* gp = arg1->user_data;
    HSD_JObj* car_jobj = arg0->hsd_obj;
    HSD_JObj* jobj;
    HSD_JObj* var_r20;
    s32 var_r27 = 0;
    grMc_CarEntry* car;
    grMc_SpeedFn* fn_ptr;
    f32 track_mid;
    f32 var_f31;
    f32 var_f21;
    HSD_Spline* spline;

    Ground_801C0498();
    track_mid = 0.5f * (gp->gv.mutecity.xD4 + gp->gv.mutecity.xD8);
    Camera_GetTransformPosition(&spE8);

    if (car_jobj == NULL) {
        jobj = NULL;
    } else {
        jobj = car_jobj->child;
    }

    {
        s16 timer = car_gp->gv.mutecity.xC4;
        if (timer != 0) {
            car_gp->gv.mutecity.xC4 = timer - 1;
        }
    }

    car = grMc_8049F4B8;
    fn_ptr = (grMc_SpeedFn*) &grMc_803E3B7C[30];

    do {
        car->x4 += car->x8;
        car->x0 += car->x8;
        {
            f32 p = car->x4;
            if (p > 1.0f) {
                car->x4 = p - 1.0f;
            }
        }

        var_f31 = car->x4;

        spline = gp->gv.mutecity.xE0->u.spline;
        if (var_f31 > 0.93f) {
            var_f21 = var_f31 - 0.93f;
            goto block_13;
        }
        if (var_f31 < 0.01f) {
            var_f21 = 0.06999999f + var_f31;
        block_13:
            splGetSplinePoint(&sp68, spline, 0.93f);
            splGetSplinePoint(&sp74, spline, 0.01f);
            lbVector_Sub(&sp74, &sp68);
            {
                f32 ratio = var_f21 / 0.07999999f;
                sp74.x *= ratio;
                sp74.y *= ratio;
                sp74.z *= ratio;
            }
            lbVector_Add(&sp74, &sp68);
            spD8 = sp74;
        } else {
            splGetSplinePoint(&spD8, spline, var_f31);
        }
        lb_8000B1CC(gp->gv.mutecity.xE0, &spD8, &spCC);

        spline = gp->gv.mutecity.xDC->u.spline;
        if (var_f31 > 0.93f) {
            var_f21 = var_f31 - 0.93f;
            goto block_19;
        }
        if (var_f31 < 0.01f) {
            var_f21 = 0.06999999f + var_f31;
        block_19:
            splGetSplinePoint(&sp50, spline, 0.93f);
            splGetSplinePoint(&sp5C, spline, 0.01f);
            lbVector_Sub(&sp5C, &sp50);
            {
                f32 ratio = var_f21 / 0.07999999f;
                sp5C.x *= ratio;
                sp5C.y *= ratio;
                sp5C.z *= ratio;
            }
            lbVector_Add(&sp5C, &sp50);
            spD8.x = sp5C.x;
            spD8.y = sp5C.y;
            spD8.z = sp5C.z;
        } else {
            splGetSplinePoint(&spD8, spline, var_f31);
        }
        lb_8000B1CC(gp->gv.mutecity.xDC, &spD8, &spC0);

        lbVector_Diff(&spC0, &spCC, &spB4);
        lbVector_Normalize(&spB4);

        if (var_f31 > 0.827f && var_f31 < 0.914f) {
            var_f31 = 0.0f;
        }

        spline = gp->gv.mutecity.xE0->u.spline;
        if (var_f31 > 0.93f) {
            var_f21 = var_f31 - 0.93f;
            goto block_28;
        }
        if (var_f31 < 0.01f) {
            var_f21 = 0.06999999f + var_f31;
        block_28:
            lbShadow_8000E9F0(&sp38, spline, 0.93f);
            lbShadow_8000E9F0(&sp44, spline, 0.01f);
            lbVector_Sub(&sp44, &sp38);
            {
                f32 ratio = var_f21 / 0.07999999f;
                sp44.x *= ratio;
                sp44.y *= ratio;
                sp44.z *= ratio;
            }
            lbVector_Add(&sp44, &sp38);
            spA8 = sp44;
        } else {
            lbShadow_8000E9F0(&spA8, spline, var_f31);
        }
        lb_8000B1CC(gp->gv.mutecity.xE0, &spA8, &spA8);
        lb_8000B1CC(gp->gv.mutecity.xE0, NULL, &spD8);
        lbVector_Sub(&spA8, &spD8);
        lbVector_Normalize(&spA8);

        spline = gp->gv.mutecity.xDC->u.spline;
        if (var_f31 > 0.93f) {
            var_f21 = var_f31 - 0.93f;
            goto block_34;
        }
        if (var_f31 < 0.01f) {
            var_f21 = 0.06999999f + var_f31;
        block_34:
            lbShadow_8000E9F0(&sp20, spline, 0.93f);
            lbShadow_8000E9F0(&sp2C, spline, 0.01f);
            lbVector_Sub(&sp2C, &sp20);
            {
                f32 ratio = var_f21 / 0.07999999f;
                sp2C.x *= ratio;
                sp2C.y *= ratio;
                sp2C.z *= ratio;
            }
            lbVector_Add(&sp2C, &sp20);
            sp9C = sp2C;
        } else {
            lbShadow_8000E9F0(&sp9C, spline, var_f31);
        }
        lb_8000B1CC(gp->gv.mutecity.xDC, &sp9C, &sp9C);
        lb_8000B1CC(gp->gv.mutecity.xDC, NULL, &spD8);
        lbVector_Sub(&sp9C, &spD8);
        lbVector_Normalize(&sp9C);

        lbVector_Add(&spA8, &sp9C);
        lbVector_Normalize(&spA8);
        PSVECCrossProduct(&spA8, &spB4, &sp90);
        lbVector_Normalize(&sp90);
        PSVECCrossProduct(&spB4, &sp90, &spA8);
        lbVector_Normalize(&spA8);

        {
            f32 lerp = car->xC;
            spF4 = (3.0f * sp90.x) + (((spC0.x - spCC.x) * lerp) + spCC.x);
            spF8 = (3.0f * sp90.y) + (((spC0.y - spCC.y) * lerp) + spCC.y);
            spFC = (3.0f * sp90.z) + (((spC0.z - spCC.z) * lerp) + spCC.z);
        }
        car->x14 = spF4;
        car->x18 = spF8;
        car->x1C = spFC;

        HSD_JObjSetTranslate(jobj, (Vec3*) &spF4);

        Ground_801C5AEC(&spD8, &spA8, &spB4, &sp90);
        HSD_JObjSetRotationX(jobj, spD8.x);
        HSD_JObjSetRotationY(jobj, spD8.y);
        HSD_JObjSetRotationZ(jobj, spD8.z);

        {
            u16 flags20 = car->x20;
            if ((flags20 & 8) && (flags20 & 2) && car_gp->gv.mutecity.xC4 == 0)
            {
                grLib_801C96F8(0x11A, 0, (Vec3*) &spF4);
                if (var_r26 < 1) {
                    if (spFC < 0.0f) {
                        var_f31 =
                            (spFC * spFC) + ((spF4 * spF4) + (spF8 * spF8));
                        if (var_f31 > 0.0f) {
                            sp1C = sqrtf(var_f31);
                            var_f31 = sp1C;
                        }
                        if (var_f31 < 300.0f) {
                            switch (HSD_Randi(3)) {
                            case 0:
                                Ground_801C5440(car_gp, 0, 0x5CC69);
                                break;
                            case 1:
                                Ground_801C5440(car_gp, 0, 0x5CC68);
                                break;
                            case 2:
                                Ground_801C5440(car_gp, 0, 0x5CC67);
                                break;
                            }
                            Ground_801C5630(car_gp, 0,
                                            1.0f - (var_f31 / 300.0f));
                            var_r26 += 1;
                        }
                    }
                    car_gp->gv.mutecity.xC4 = 7;
                }
            }
        }

        {
            f32 age = car->x10;
            if (age > grMc_804D69D0->x30) {
                if (!car->x22_flags.b0) {
                    grLib_801C98A0(jobj);
                    var_r20 = NULL;
                    car->x28 = 0;
                    grLib_801C96F8(0xE3, 0, (Vec3*) &spF4);
                    if (jobj != NULL) {
                        var_r20 = jobj->child;
                    }
                    HSD_JObjUnref(var_r20);
                    {
                        HSD_JObj* new_jobj = Ground_801C13D0(5, 0);
                        if (new_jobj != NULL) {
                            f32 rand_y;
                            sp84 = grMc_803B81B8.x;
                            sp88 = grMc_803B81B8.y;
                            sp8C = grMc_803B81B8.z;
                            HSD_JObjAddChild(jobj, new_jobj);
                            rand_y = (1.0471976f * HSD_Randf()) - 0.5235988f;
                            HSD_JObjSetTranslateY(new_jobj, rand_y);
                            HSD_JObjSetTranslate(new_jobj, (Vec3*) &sp84);
                        }
                    }
                    {
                        u32 item = (u32) car->x24;
                        if (item != 0) {
                            grMaterial_801C8CDC((HSD_GObj*) item);
                            car->x24 = 0;
                        }
                    }
                    car->x22_flags.b0 = 1;
                }
            } else if (age > grMc_804D69D0->x2C && car->x28 == 0) {
                grMuteCity_801F2AB0(0x116, jobj);
                car->x28 = (s32) jobj;
            }
        }

        if (!car->x22_flags.b0) {
            f32 rel_t = car->x4;
            f32 dist_t;
            if (track_mid < rel_t) {
                dist_t = (1.0f + track_mid) - rel_t;
            } else {
                dist_t = track_mid - rel_t;
            }

            if (dist_t < 0.2f && dist_t > -0.2f) {
                if (spF4 > -200.0f && spF4 < 200.0f && spF8 > -200.0f &&
                    spF8 < 200.0f && -1350.0f < spFC && spFC < 50.0f)
                {
                    Camera_80030E44(1, NULL);
                    if (!car->x22_flags.b1) {
                        if ((gp->gv.mutecity.xD0_flags.b6)) {
                            switch (HSD_Randi(3)) {
                            case 0:
                                Ground_801C53EC(0x5CC66);
                                break;
                            case 1:
                                Ground_801C53EC(0x5CC65);
                                break;
                            case 2:
                                Ground_801C53EC(0x5CC64);
                                break;
                            }
                        } else {
                            switch (HSD_Randi(3)) {
                            case 0:
                                Ground_801C53EC(0x5CC63);
                                break;
                            case 1:
                                Ground_801C53EC(0x5CC62);
                                break;
                            case 2:
                                Ground_801C53EC(0x5CC61);
                                break;
                            }
                        }
                        car->x22_flags.b1 = 1;
                    }
                } else {
                    if (car->x22_flags.b1) {
                        car->x22_flags.b1 = 0;
                    }
                }
            }

            if (spF4 > -200.0f && spF4 < 200.0f && spF8 > -200.0f &&
                spF8 < 200.0f && -100.0f < spFC && spFC < 50.0f)
            {
                if (!car->x22_flags.b0 && car->x24 == 0) {
                    Item_GObj* item_gobj = grMaterial_801C8CFC(
                        0, 2, car_gp, jobj, grMuteCity_801F1A0C, *fn_ptr,
                        NULL);
                    if (item_gobj != NULL) {
                        grMaterial_801C8DE0(item_gobj, 0.0f, 0.0f, -12.0f,
                                            0.0f, 0.0f, 2.0f, 15.0f);
                        grMaterial_801C8E08(item_gobj);
                        car->x24 = (s32) item_gobj;
                    }
                }
            } else {
                u32 item = (u32) car->x24;
                if (item != 0) {
                    grMaterial_801C8CDC((HSD_GObj*) item);
                    car->x24 = 0;
                }
            }
        } else {
            if (spFC > spE8.z || spFC > 5000.0f || spFC < -1500.0f) {
                if (car->x28 != 0) {
                    grLib_801C98A0(jobj);
                    car->x28 = 0;
                }
            } else if (car->x28 == 0) {
                grMuteCity_801F2AB0(0x119, jobj);
                car->x28 = (s32) jobj;
            }
        }

        car++;
        fn_ptr++;
        var_r27 += 1;
        if (jobj == NULL) {
            jobj = NULL;
        } else {
            jobj = jobj->next;
        }
    } while (var_r27 < 0x1E);
}

DynamicModelDesc* grMuteCity_801F28A8(void)
{
    UnkArchiveStruct* archive = grDatFiles_801C6330(0x26);
    UnkStageDat* dat;
    HSD_ASSERT(2135, archive);
    dat = archive->unk4;
    if (dat != NULL) {
        return (DynamicModelDesc*) ((char*) dat->unk8 + 0x7B8);
    }
    return NULL;
}

void grMuteCity_801F290C(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_GObj* lgobj;
    HSD_LObj* lobj;
    s32 i;
    PAD_STACK(16);

    if (grLib_801C96E8(gobj) != 0) {
        if (gp->gv.mutecity2.xC4_flags.b0) {
            lgobj = HSD_GObj_Entities->xC;
            while (lgobj != NULL) {
                if (HSD_GObjGetClassifier(lgobj) == 0xC) {
                    break;
                }
                lgobj = lgobj->next;
            }
            if (lgobj != NULL) {
                lobj = GET_LOBJ(lgobj);
                i = 0;
                while (lobj != NULL) {
                    if (HSD_LObjGetFlags(lobj) & 4) {
                        HSD_LObjSetColor(lobj,
                                         gp->gv.mutecity2.saved_colors[i]);
                        i++;
                        if (i >= 4) {
                            break;
                        }
                    }
                    lobj = HSD_LObjGetNext(lobj);
                }
            }
            gp->gv.mutecity2.xC4_flags.b0 = 0;
        }
    } else {
        lgobj = HSD_GObj_Entities->xC;
        while (lgobj != NULL) {
            if (HSD_GObjGetClassifier(lgobj) == 0xC) {
                break;
            }
            lgobj = lgobj->next;
        }
        if (lgobj != NULL) {
            i = 0;
            lobj = GET_LOBJ(lgobj);
            while (lobj != NULL) {
                if (HSD_LObjGetFlags(lobj) & 4) {
                    if (!gp->gv.mutecity2.xC4_flags.b0) {
                        HSD_LObjGetColor(lobj,
                                         &gp->gv.mutecity2.saved_colors[i]);
                    }
                    HSD_LObjSetColor(lobj, gp->x6C);
                    i++;
                    if (i >= 4) {
                        break;
                    }
                }
                if (lobj == NULL) {
                    lobj = NULL;
                } else {
                    lobj = lobj->next;
                }
            }
        }
        gp->gv.mutecity2.xC4_flags.b0 = 1;
    }
}

void grMuteCity_801F2AB0(s32 arg0, HSD_JObj* arg1)
{
    HSD_Generator* gen;
    HSD_psAppSRT* appsrt;

    gen = grLib_801C9808(arg0, arg0 / 1000, arg1);
    if (gen != NULL) {
        if ((appsrt = gen->appsrt) == NULL) {
            appsrt = psAddGeneratorAppSRT_begin(gen, 0);
            if (appsrt == NULL) {
                return;
            }
        }
        appsrt->xA2 = 0;
        appsrt->scale.x = appsrt->scale.y = appsrt->scale.z =
            Ground_801C0498();
        gen->type &= ~(PSAPPSRT_UNK_B09 | PSAPPSRT_UNK_B10);
        gen->type |= PSAPPSRT_UNK_B11;
        appsrt->gp = gen;
    }
}

void fn_801F2B58(Ground* gp, s32 arg1, CollData* cd, s32 arg3,
                 mpLib_GroundEnum arg4, f32 arg5)
{
    s32 b1234 = cd->x34_flags.b1234;

    if (grMc_804D69D4 != 1) {
        return;
    }

    if ((u32) (b1234 - 2) > 1 && b1234 != 5) {
        return;
    }

    if (arg4 != mpLib_GroundEnum_Unk2) {
        return;
    }

    if (cd->x0_gobj == NULL) {
        return;
    }

    if (cd->x0_gobj->p_link != 9) {
        return;
    }

    if (cd->x0_gobj == NULL) {
        return;
    }

    cd->x34_flags.b7 = 1;
}

DynamicsDesc* grMuteCity_801F2BBC(enum_t arg0)
{
    if (grMc_804D69D4 == 1) {
        if (arg0 == 0x31) {
            return grMc_804D69D0->x8;
        }
        if (arg0 == 0x35) {
            return grMc_804D69D0->x8;
        }
        if ((u32) (arg0 - 0x32) <= 2) {
            return grMc_804D69D0->xC;
        }
    }
    return NULL;
}

bool grMuteCity_801F2C10(Vec3* pos, int arg, HSD_JObj* jobj)
{
    HSD_GObj* gobj;
    Ground* gp;
    f32 x;
    f32 x_min;
    f32 x_max;
    f32 slope;
    f32 y;
    f32 new_var;
    PAD_STACK(8);

    gobj = Ground_801C2BA4(0x1E);
    if (gobj != NULL) {
        gp = gobj->user_data;
        if (gp != NULL) {
            if (gp->gv.mutecity.xFC == jobj || gp->gv.mutecity.x100 == jobj ||
                gp->gv.mutecity.x104 == jobj || gp->gv.mutecity.x108 == jobj ||
                gp->gv.mutecity.x10C == jobj)
            {
                x = pos->x;
                x_min = gp->gv.mutecity.xE4.x;
                if ((new_var = x) < x_min) {
                    return false;
                }
                x_max = gp->gv.mutecity.xF0.x;
                if (x > x_max) {
                    return false;
                }
                slope = (gp->gv.mutecity.xF0.y - gp->gv.mutecity.xE4.y) /
                        (x_max - x_min);
                y = slope * (x - x_min) + gp->gv.mutecity.xE4.y;
                if (pos->y > y - 3.0F) {
                    return true;
                }
                return false;
            }
        }
    }
    return true;
}
