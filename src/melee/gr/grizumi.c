#include "gr/grizumi.h"

#include "cm/camera.h"
#include "ft/ftdrawcommon.h"
#include "gr/granime.h"
#include "gr/grdatfiles.h"
#include "gr/grdisplay.h"
#include "gr/grlib.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "gr/types.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "lb/lbdvd.h"
#include "mp/mplib.h"

#include <dolphin/gx/GXTexture.h>
#include <dolphin/mtx.h>
#include <dolphin/os/OSError.h>
#include <baselib/aobj.h>
#include <baselib/archive.h>
#include <baselib/cobj.h>
#include <baselib/debug.h>
#include <baselib/displayfunc.h>
#include <baselib/dobj.h>
#include <baselib/fog.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjproc.h>
#include <baselib/gobjuserdata.h>
#include <baselib/jobj.h>
#include <baselib/lobj.h>
#include <baselib/memory.h>
#include <baselib/object.h>
#include <baselib/random.h>
#include <baselib/state.h>
#include <baselib/tobj.h>
#include <baselib/wobj.h> // IWYU pragma: keep

/// context stuff
typedef struct FountainParams {
    float x0;
    int x4;
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
    float x34;
    float x38;
    float x3C;
    float x40;
    float x44;
    float x48;
    float x4C;
    float x50;
} FountainParams;
typedef struct IzumiReflection {
    Mtx texture_matrix;
    HSD_ImageDesc* image;
} IzumiReflection;
typedef struct IzumiUnkCC {
    u8 pad[0x18];
    HSD_GObj* x18;
} IzumiUnkCC;
#define GET_REFLECTION(gobj) ((IzumiReflection*) HSD_GObjGetUserData(gobj))

FountainParams* grIz_804D6968;
S16Vec3 grIz_803E0D60[] = { { 0, 3, 1 }, { 1, 3, 2 }, { 2, 3, 3 } };
StageCallbacks grIz_803E0D74[] = {
    {
        grIzumi_801CBDD4,
        grIzumi_801CBE00,
        grIzumi_801CBE08,
        grIzumi_801CBE0C,
        0,
    },
    {

        grIzumi_801CBE10,
        grIzumi_801CBE54,
        grIzumi_801CBE5C,
        grIzumi_801CBE60,
        0,

    },
    {
        grIzumi_801CCA64,
        grIzumi_801CCB08,
        grIzumi_801CCB10,
        grIzumi_801CCB14,
        0,
    },
    {
        grIzumi_801CBE64,
        grIzumi_801CC0CC,
        grIzumi_801CC0D4,
        grIzumi_801CC338,
        0xC0000000,
    },
    {
        grIzumi_801CC33C,
        grIzumi_801CC350,
        grIzumi_801CC358,
        grIzumi_801CCA10,
        0,
    },
    {
        grIzumi_801CCA14,
        grIzumi_801CCA54,
        grIzumi_801CCA5C,
        grIzumi_801CCA60,
        0,
    },
    {
        grIzumi_801CCA14,
        grIzumi_801CCA54,
        grIzumi_801CCA5C,
        grIzumi_801CCA60,
        0,
    },
    {
        grIzumi_801CCA14,
        grIzumi_801CCA54,
        grIzumi_801CCA5C,
        grIzumi_801CCA60,
        0,
    },
    {
        grIzumi_801CCA14,
        grIzumi_801CCA54,
        grIzumi_801CCA5C,
        grIzumi_801CCA60,
        0,
    },
    {
        grIzumi_801CCA14,
        grIzumi_801CCA54,
        grIzumi_801CCA5C,
        grIzumi_801CCA60,
        0,
    },
    {
        grIzumi_801CCA14,
        grIzumi_801CCA54,
        grIzumi_801CCA5C,
        grIzumi_801CCA60,
        0,
    },
};
StageData grIz_803E0E5C = {
    0xC,
    grIz_803E0D74,
    "/GrIz.dat",
    grIzumi_801CBB88,
    grIzumi_801CBB84,
    grIzumi_UnkStage0_OnLoad,
    grIzumi_UnkStage0_OnStart,
    grIzumi_801CBCE0,
    grIzumi_801CD278,
    grIzumi_801CD280,
    1,
    grIz_803E0D60,
    3,
};

/// functions start here
void grIzumi_801CBB84(bool x)
{
    return;
}

/// https://decomp.me/scratch/94sPw
void grIzumi_801CBB88(void)
{
    HSD_GObj* r3;

    grIz_804D6968 = Ground_801C49F8();
    stage_info.unk8C.b4 = 0;
    stage_info.unk8C.b5 = 1;
    grIzumi_801CBCE8(0);
    grIzumi_801CBCE8(1);
    r3 = grIzumi_801CBCE8(3);
    grAnime_801C8780(r3, 3, 0, 0.0f, 1.0f);
    Ground_801C39C0();
    Ground_801C3BB4();
}

/// https://decomp.me/scratch/4u5TX
void grIzumi_UnkStage0_OnLoad(void)
{
    HSD_GObj* gobj;
    HSD_LObj* lobj;

    gobj = HSD_GObj_Entities->xC;
    while (gobj != NULL) {
        if (HSD_GObjGetClassifier(gobj) == 0xC) {
            lobj = GET_LOBJ(gobj);
            while (lobj != NULL) {
                HSD_ForeachAnim(lobj, LOBJ_TYPE, ALL_TYPE_MASK,
                                HSD_AObjSetFlags, AOBJ_ARG_AU, AOBJ_LOOP);
                lobj = HSD_LObjGetNext(lobj);
            }
            return;
        }
        gobj = HSD_GObjGetNext(gobj);
    }
}

/// https://decomp.me/scratch/9AxrD
void grIzumi_UnkStage0_OnStart(void)
{
    grZakoGenerator_801CAE04(0);
}

bool grIzumi_801CBCE0(void)
{
    return false;
}

/// https://decomp.me/scratch/FVXdq
HSD_GObj* grIzumi_801CBCE8(int gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grIz_803E0D74[gobj_id];

    gobj = Ground_801C14D0(gobj_id);

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
            HSD_GObjProc_8038FD54(gobj, callbacks->callback2, 4);
        }

    } else {
        // clang-format off
//#line 241 "grizumi.c"
///        OSReport("%s:%d: couldn t get gobj(id=%d)\n", __FILE__, __LINE__, gobj_id);
        // clang-format on
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grizumi.c", 241,
                 gobj_id);
    }

    return gobj;
}

/// https://decomp.me/scratch/BcUJr
void grIzumi_801CBDD4(Ground_GObj* gobj)
{
    grAnime_801C8138(gobj, GET_GROUND(gobj)->map_id, 0);
}

bool grIzumi_801CBE00(Ground_GObj* gobj)
{
    return false;
}

void grIzumi_801CBE08(Ground_GObj* gobj)
{
    return;
}

void grIzumi_801CBE0C(Ground_GObj* gobj)
{
    return;
}

void grIzumi_801CBE10(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->x11_flags.b012 = 1;
}

bool grIzumi_801CBE54(Ground_GObj* gobj)
{
    return false;
}

void grIzumi_801CBE5C(Ground_GObj* gobj)
{
    return;
}

void grIzumi_801CBE60(Ground_GObj* gobj)
{
    return;
}

/// https://decomp.me/scratch/VuF6U
void grIzumi_801CBE64(Ground_GObj* gobj)
{
    HSD_TObj* tobj;
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Ground_801C2ED0(jobj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->x11_flags.b012 = 1;
    gp->x10_flags.b5 = 1;
    gp->gv.izumi.xD0 = Ground_801C3FA4(gobj, 1);
    gp->gv.izumi.xD4 = Ground_801C3FA4(gobj, 2);
    gp->gv.izumi.xC8 = grIzumi_801CCD98();
    tobj = grIzumi_801CD090(gobj, GET_REFLECTION(gp->gv.izumi.xC8)->image);
    if (tobj != NULL) {
        tobj->src = 0;
        tobj->wrap_s = 0;
        tobj->wrap_t = 0;
        tobj->flags = (tobj->flags & ~0x1FF) | 0x103;
    } else {
        // clang-format off
/// this breaks the line numbers in compile errors >:(
//#line 387 "grizumi.c"
///        OSReport("%s:%d:Warning: not found tobj !\n", __FILE__, __LINE__);
        // clang-format on
        OSReport("%s:%d:Warning: not found tobj !\n", "grizumi.c", 387);
    }
    gp->gv.izumi.xC4 = tobj;
    gobj->render_cb = grIzumi_801CD220;
    grIzumi_801CCB18(gobj);
    {
        Vec3 x = { 0, 0, 0 };
        grLib_801C96F8(0x7534, 0x1E, &x);
    }
    {
        Vec3 y = { 0, 1, -27 };
        y.x *= Ground_801C0498();
        y.y *= Ground_801C0498();
        y.z *= Ground_801C0498();
        grLib_801C96F8(0x7536, 0x1E, &y);
    }
    gp->gv.izumi.xCC = grIzumi_801CBCE8(2);
    ((IzumiUnkCC*) HSD_GObjGetUserData(gp->gv.izumi.xCC))->x18 =
        gp->gv.izumi.xC8;
    jobj = Ground_801C3FA4(gobj, 4);
    { // this looks like inlines, but there's a lot of small differences
        u8 _[4] = { 0 };
        Vec3 x38;
        {
            u8 _[8] = { 0 };
        }
        lb_8000B1CC(jobj, NULL, &x38);
        {
            HSD_GObj* plat =
                grIzumi_801CCBDC(grIz_804D6968->x0, &x38, 0, gp->gv.izumi.xD0);
            Ground* platground = GET_GROUND(plat);
            platground->gv.izumi2.xDC = grIz_804D6968->xC;
            platground->x10_flags.b3 = 1;
            platground->x18 = gp->gv.izumi.xC8;
        }
        jobj = Ground_801C3FA4(gobj, 6);
        lb_8000B1CC(jobj, NULL, &x38);
        {
            HSD_GObj* plat =
                grIzumi_801CCBDC(grIz_804D6968->x8, &x38, 1, gp->gv.izumi.xD4);
            Ground* platground = GET_GROUND(plat);
            platground->gv.izumi2.xDC = grIz_804D6968->xC;
            platground->x10_flags.b3 = 1;
            platground->x18 = gp->gv.izumi.xC8;
        }
    }
}

bool grIzumi_801CC0CC(Ground_GObj* gobj)
{
    return false;
}

void grIzumi_801CC0D4(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    if (gp->gv.izumi.xCC != NULL) {
        Ground* gp2 = GET_GROUND(gp->gv.izumi.xCC);
        Vec3 vec;
        if (gp->gv.izumi.xD0 != NULL) {
            HSD_JObjGetTranslation(gp->gv.izumi.xD0, &vec);
            HSD_JObjSetTranslate(gp2->gv.izumi2.xC4, &vec);
            if (vec.y < 0.0f) {
                u32 flags = HSD_JObjGetFlags(gp2->gv.izumi2.xC4);
                if ((flags & 0x10) == 0) {
                    HSD_JObjSetFlagsAll(gp2->gv.izumi2.xC4, 0x10);
                }
            } else {
                u32 flags = HSD_JObjGetFlags(gp2->gv.izumi2.xC4);
                if ((flags & 0x10) != 0) {
                    HSD_JObjClearFlagsAll(gp2->gv.izumi2.xC4, 0x10);
                }
            }
        }
        if (gp->gv.izumi.xD4 != NULL) {
            HSD_JObjGetTranslation(gp->gv.izumi.xD4, &vec);
            HSD_JObjSetTranslate(gp2->gv.izumi2.xC8, &vec);
            if (vec.y < 0.0f) {
                u32 flags = HSD_JObjGetFlags(gp2->gv.izumi2.xC8);
                if ((flags & 0x10) == 0) {
                    HSD_JObjSetFlagsAll(gp2->gv.izumi2.xC8, 0x10);
                }
            } else {
                u32 flags = HSD_JObjGetFlags(gp2->gv.izumi2.xC8);
                if ((flags & 0x10) != 0) {
                    HSD_JObjClearFlagsAll(gp2->gv.izumi2.xC8, 0x10);
                }
            }
        }
    }
    lb_800115F4();
}

void grIzumi_801CC338(Ground_GObj* gobj)
{
    return;
}

void grIzumi_801CC33C(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    gp->x8_callback = NULL;
    gp->xC_callback = NULL;
}

bool grIzumi_801CC350(Ground_GObj* gobj)
{
    return false;
}

static inline int rand_inline(int a, int b)
{
    if (a > b) {
        return b + (a - b != 0 ? HSD_Randi(a - b) : 0);
    } else if (a < b) {
        return a + (b - a != 0 ? HSD_Randi(b - a) : 0);
    } else {
        return a;
    }
}

void grIzumi_801CC358(Ground_GObj* gobj)
{
    bool r29 = false;
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Ground* gp = GET_GROUND(gobj);
    switch (gp->gv.izumi3.xC4) {
    case 0: {
        // 54
        gp->gv.izumi3.xC4 = 1;
        gp->gv.izumi3.xC6 =
            rand_inline(grIz_804D6968->x3C, grIz_804D6968->x38);
        r29 = true;
        break;
    }
    case 1: {
        // e4
        if (gp->gv.izumi3.xC6-- < 0) {
            float f = HSD_Randf() * (grIz_804D6968->x40 + grIz_804D6968->x44 +
                                     grIz_804D6968->x48);
            f -= grIz_804D6968->x40;
            if (f < 0.0) {
                gp->gv.izumi3.xC4 = 2;
                gp->gv.izumi3.xD4 = -1;
                break;
            }
            f -= grIz_804D6968->x48;
            if (f < 0.0) {
                float fff = HSD_Randf();
                float ff = (grIz_804D6968->x1C - grIz_804D6968->x18);
                ff = ff * fff + grIz_804D6968->x18;
                gp->gv.izumi3.xC4 = 2;
                if (gp->gv.izumi3.xD0 < gp->gv.izumi3.xDC) {
                    if (HSD_Randf() < grIz_804D6968->x30) {
                        gp->gv.izumi3.xD4 -= ff;
                    } else {
                        gp->gv.izumi3.xD4 += ff;
                    }
                } else if (gp->gv.izumi3.xD0 > gp->gv.izumi3.xDC) {
                    if (HSD_Randf() < grIz_804D6968->x34) {
                        gp->gv.izumi3.xD4 += ff;
                    } else {
                        gp->gv.izumi3.xD4 -= ff;
                    }
                } else {
                    if (HSD_Randf() < 0.5) {
                        gp->gv.izumi3.xD4 += ff;
                    } else {
                        gp->gv.izumi3.xD4 -= ff;
                    }
                }
                if (gp->gv.izumi3.xD4 > grIz_804D6968->x20) {
                    gp->gv.izumi3.xD4 = grIz_804D6968->x20;
                } else if (gp->gv.izumi3.xD4 < grIz_804D6968->x24) {
                    gp->gv.izumi3.xD4 = grIz_804D6968->x24;
                }
            } else {
                gp->gv.izumi3.xC6 =
                    rand_inline(grIz_804D6968->x3C, grIz_804D6968->x38);
            }
        }
        break;
    }
    case 2: {
        // 2c0
        float f = gp->gv.izumi3.xD4 - gp->gv.izumi3.xD0;
        if (f > 0) {
            if (f < grIz_804D6968->x28) {
                gp->gv.izumi3.xD0 = gp->gv.izumi3.xD4;
                gp->gv.izumi3.xC4 = 0;
            } else {
                gp->gv.izumi3.xD0 += grIz_804D6968->x28;
            }
        } else if (f < 0) {
            if (-f < grIz_804D6968->x2C) {
                gp->gv.izumi3.xD0 = gp->gv.izumi3.xD4;
                if (gp->gv.izumi3.xD0 < grIz_804D6968->x24) {
                    gp->gv.izumi3.xC4 = 3;
                } else {
                    gp->gv.izumi3.xC4 = 0;
                }
            } else {
                gp->gv.izumi3.xD0 -= grIz_804D6968->x2C;
            }
        } else {
            gp->gv.izumi3.xC4 = 0;
        }
        r29 = true;
        break;
    }

    case 3: {
        // 368
        float f;
        gp->gv.izumi3.xC4 = 4;
        gp->gv.izumi3.xC6 =
            rand_inline(grIz_804D6968->x50, grIz_804D6968->x4C);
        HSD_JObjSetFlagsAll(jobj, 0x10);
        HSD_JObjRemoveAnimAll(jobj); ///< @todo float load order (41c)
        f = HSD_JObjGetTranslationY(jobj);
        f += -1.0;
        HSD_JObjSetTranslateY(gp->gv.izumi3.xCC, f);
        break;
    }
    case 4: {
        // 4a4
        if (gp->gv.izumi3.xC6-- < 0) {
            gp->gv.izumi3.xC4 = 2;
            gp->gv.izumi3.xD4 = gp->gv.izumi3.xDC;
            HSD_JObjClearFlagsAll(jobj, 0x10);
            grAnime_801C7FF8(gobj, 0, 7, 0, 0.0f, 1.0f);
            r29 = true;
        }
        break;
    }
    }
    if (r29) {
        HSD_JObj* jobj2 = HSD_JObjGetChild(jobj);
        if (jobj2 != NULL) {
            float f = gp->gv.izumi3.xD0 / (double) gp->gv.izumi3.xD8;
            if (f < 0.01f) {
                f = 0.01f;
            }
            HSD_JObjSetScaleX(jobj2, 0.5f * f + 0.5f);
            HSD_JObjSetScaleY(jobj2, f);
            HSD_JObjSetTranslateY(gp->gv.izumi3.xCC, gp->gv.izumi3.xD0);
        }
    }
    mpLib_80055E9C(gp->gv.izumi3.xC8);
}

void grIzumi_801CCA10(Ground_GObj* gobj)
{
    return;
}

void grIzumi_801CCA14(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->x8_callback = NULL;
    gp->xC_callback = NULL;
}

bool grIzumi_801CCA54(Ground_GObj* gobj)
{
    return false;
}

void grIzumi_801CCA5C(Ground_GObj* gobj)
{
    return;
}

void grIzumi_801CCA60(Ground_GObj* gobj)
{
    return;
}

void grIzumi_801CCA64(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->x8_callback = NULL;
    gp->xC_callback = NULL;
    HSD_GObjGXLink_8039084C(gobj);
    GObj_SetupGXLink(gobj, grDisplay_801C5DB0, 2, 0);
    gp->gv.izumi2.xC4 = Ground_801C3FA4(gobj, 2);
    HSD_JObjSetFlagsAll(gp->gv.izumi2.xC4, 0x10);
    gp->gv.izumi2.xC8 = Ground_801C3FA4(gobj, 3);
    HSD_JObjSetFlagsAll(gp->gv.izumi2.xC8, 0x10);
}

bool grIzumi_801CCB08(Ground_GObj* gobj)
{
    return false;
}

void grIzumi_801CCB10(Ground_GObj* gobj)
{
    return;
}

void grIzumi_801CCB14(Ground_GObj* gobj)
{
    return;
}

void grIzumi_801CCB18(HSD_GObj* gobj)
{
    HSD_Joint* j = HSD_ArchiveGetPublicAddress(grDatFiles_801C6324()->unk0,
                                               "GrdIzumiStar_TopN_joint");
    if (j != NULL) {
        HSD_GObj* sub = Ground_801C1A20(j, -1);
        if (sub != NULL) {
            Ground* gp = GET_GROUND(sub);
            GObj_SetupGXLink(sub, grIzumi_801CCB90, 3, 0);
            gp->x11_flags.b012 = 2;
        }
    }
}

void grIzumi_801CCB90(HSD_GObj* gobj, int renderpass)
{
    /// @remarks i guess PointSize is an inline? seems odd
    u8 _[8] = { 0 };
    HSD_StateSetPointSize(18, 0);
    grDisplay_801C5DB0(gobj, renderpass);
}

HSD_GObj* grIzumi_801CCBDC(float height, Vec3* a, int b, HSD_JObj* jobj)
{
    HSD_GObj* gobj;
    gobj = grIzumi_801CBCE8(4);
    if (gobj != NULL) {
        Ground* gp = GET_GROUND(gobj);
        if (gobj && gobj) {
        } // permuter
        if (gp != NULL) {
            HSD_JObj* jobj2;
            jobj2 = HSD_GObjGetHSDObj(gobj);
            if (jobj2 != NULL) { // permuter
                Vec3 aa = *a;
                HSD_JObjSetTranslate(jobj2, &aa);
                gp->gv.izumi3.xD4 = height;
                gp->gv.izumi3.xD0 = height;
                gp->gv.izumi3.xC8 = b;
                gp->gv.izumi3.xCC = jobj;
                if (height < 0.0f) {
                    gp->gv.izumi3.xC4 = 3;
                } else {
                    gp->gv.izumi3.xC4 = 0;
                    grAnime_801C7FF8(gobj, 0, 7, 0, 0.0f, 1.0f);
                }
                jobj2 = Ground_801C3FA4(gobj, 2);
                if (jobj2 != NULL) {
                    Vec3 vec;
                    u8 _[4];
                    lb_8000B1CC(jobj2, NULL, &vec);
                    gp->gv.izumi3.xD8 = (vec.y - aa.y) / Ground_801C0498();
                } else {
                    gp->gv.izumi3.xD8 = 45.0f;
                }
                grIzumi_801CC358(gobj);
                goto ret; // return has to be after the loop, but idk how to
                          // controlflow it any better
            }
        }
    }

    OSReport("%s:%d:oioi...\n", "grizumi.c", 892);
    while (true) {
    }

ret:
    return gobj;
}

HSD_WObjDesc EyeDesc = { NULL, { 0.0f, 0.0f, 1.0f }, NULL };
HSD_WObjDesc InterestDesc = { NULL, { 0.0f, 0.0f, 0.0f }, NULL };
HSD_CameraDescPerspective ReflectCObjDesc = {
    NULL,
    0,
    1,
    {
        0,
        80,
        0,
        60,
    },
    {
        0,
        80,
        0,
        60,
    },
    &EyeDesc,
    &InterestDesc,
    0.0f,
    NULL,
    0.1f,
    32768.0f,
    30.0f,
    1.2173333168029785f,
};

HSD_GObj* grIzumi_801CCD98(void)
{
    HSD_GObj* gobj = GObj_Create(0x11, 0x12, 0);
    HSD_CObj* cobj = lb_80013B14(&ReflectCObjDesc);
    IzumiReflection* refl;
    UnkArchiveStruct* dat;
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784B, cobj);
    GObj_SetupGXLinkMaxSorted(gobj, grIzumi_801CCEA0, 2);
    refl = HSD_MemAlloc(sizeof(IzumiReflection));
    GObj_InitUserData(gobj, 3, HSD_Free, refl);
    dat = grDatFiles_801C6330(3);
    refl->image = HSD_ArchiveGetPublicAddress(
        dat->unk0, "GrdIzumi_cd_wt_GrdIzumiDummy1_1_image_desc");
    if (refl->image != NULL) {
        memzero(refl->image, sizeof(HSD_ImageDesc));
        lb_800121FC(refl->image, 80, 60, 4, 2001);
    } else {
        OSReport("not found mirror image desc! "
                 "(GrdIzumi_cd_wt_GrdIzumiDummy1_1_image_desc)\n");
        __assert("grizumi.c", 968, "0");
    }
    return gobj;
}

void grIzumi_801CCEA0(HSD_GObj* gobj, int renderpass)
{
    Mtx mtx;
    Vec3 vec;
    u8 _[8] = { 0 };
    HSD_CObj* src;
    HSD_CObj* dst;
    IzumiReflection* refl = (IzumiReflection*) HSD_GObjGetUserData(gobj);
    HSD_GObj* src_gobj;
    HSD_CObj* cobj;

    if (refl->image != NULL) {
        cobj = GET_COBJ(gobj);
        ftDrawCommon_80081140();
        Camera_8002A4AC(Camera_80030A50());

        dst = GET_COBJ(gobj);
        src_gobj = Camera_80030A50();
        if (src_gobj != NULL) {
            // uses r0 if put on two lines:
            if ((src = GET_COBJ(src_gobj)) != NULL) {
                HSD_CObjSetNear(dst, HSD_CObjGetNear(src));
                HSD_CObjSetFar(dst, HSD_CObjGetFar(src));
                HSD_CObjSetFov(dst, HSD_CObjGetFov(src));
                HSD_CObjSetAspect(dst, HSD_CObjGetAspect(src));
                HSD_CObjGetEyePosition(src, &vec);
                vec.y = -vec.y;
                HSD_CObjSetEyePosition(dst, &vec);
                HSD_CObjGetInterest(src, &vec);
                vec.y = -vec.y;
                HSD_CObjSetInterest(dst, &vec);
            }
        }
        if (HSD_CObjSetCurrent(cobj)) {
            HSD_SetEraseColor(0xFF, 0xFF, 0xFF, 1);
            HSD_CObjEraseScreen(cobj, 1, 0, 0);
            HSD_LObjDeleteCurrentAll(0);
            Camera_800310A0(0);
            Camera_80031074(1);
            gobj->gxlink_prios = 0x25;
            HSD_GObj_80390ED0(gobj, 3);
            Camera_80031074(0);
            gobj->gxlink_prios = 0x70;
            HSD_GObj_80390ED0(gobj, 7);
            HSD_FogSet(0);
            gobj->gxlink_prios = 0x80;
            HSD_GObj_80390ED0(gobj, 7);
            HSD_CObjEndCurrent();
        }
        lb_800122C8(refl->image, 0, 0, 1);
        MTXLightPerspective(mtx, cobj->projection_param.perspective.fov,
                            cobj->projection_param.perspective.aspect, 0.49f,
                            -0.49f, 0.5f, 0.5f);
        PSMTXConcat(mtx, HSD_CObjGetViewingMtxPtr(cobj), refl->texture_matrix);
        ftDrawCommon_80081118();
    }
}

static inline bool check_flag_4020(HSD_JObj* jobj)
{
    if ((jobj->flags & (0x4020)) != 0) {
        return false;
    } else {
        return true;
    }
}

HSD_TObj* grIzumi_801CD090(HSD_GObj* gobj, HSD_ImageDesc* image)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    while (jobj != NULL) {
        if (check_flag_4020(jobj)) {
            HSD_DObj* dobj;
            for (dobj = jobj->u.dobj; dobj != NULL; dobj = dobj->next) {
                if (dobj->mobj != NULL) {
                    HSD_TObj* tobj;
                    for (tobj = dobj->mobj->tobj; tobj != NULL;
                         tobj = tobj->next)
                    {
                        if (tobj->imagedesc == image) {
                            return tobj;
                        }
                    }
                }
            }
        }
        if ((jobj->flags & 0x1000) == 0) {
            if (HSD_JObjGetChild(jobj) != NULL) {
                jobj = HSD_JObjGetChild(jobj);
                continue;
            }
        }
        if (HSD_JObjGetNext(jobj) != NULL) {
            jobj = HSD_JObjGetNext(jobj);
        } else {
            while (true) {
                if (HSD_JObjGetParent(jobj) == NULL) {
                    jobj = NULL;
                    break;
                } else if (HSD_JObjGetNext(HSD_JObjGetParent(jobj)) != NULL) {
                    jobj = HSD_JObjGetNext(HSD_JObjGetParent(jobj));
                    break;
                } else {
                    jobj = HSD_JObjGetParent(jobj);
                }
            }
        }
    }
    return NULL;
}

void grIzumi_801CD220(HSD_GObj* gobj, int renderpass)
{
    Ground* gp = GET_GROUND(gobj);
    IzumiReflection* refl = HSD_GObjGetUserData(gp->gv.izumi.xC8);
    HSD_TObj* tobj = gp->gv.izumi.xC4;
    PSMTXCopy(refl->texture_matrix, tobj->mtx);
    grDisplay_801C5DB0(gobj, renderpass);
}

DynamicsDesc* grIzumi_801CD278(enum_t x)
{
    return NULL;
}

bool grIzumi_801CD280(Vec3* a, int b, HSD_JObj* jobj)
{
    Vec3 vec;
    lb_8000B1CC(jobj, NULL, &vec);
    if (a->y > vec.y) {
        return true;
    } else {
        return false;
    }
}

void grIzumi_801CD2D4(void)
{
    int size = GXGetTexBufferSize(80, 60, 4, '\0', 0);
    lbDvd_80017740(0, 2001, 4, 4, size + 31 & ~31, 0, 7, 16, 0);
}
