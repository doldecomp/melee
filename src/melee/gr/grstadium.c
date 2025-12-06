/// @todo this file needs to be named "grpstadium.c" for asserts, oops!
#include "grstadium.h"

#include "dolphin/gx/GXStruct.h"

#include <sysdolphin/baselib/archive.h>
#include <sysdolphin/baselib/displayfunc.h>
#include <sysdolphin/baselib/dobj.h>
#include <sysdolphin/baselib/fog.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjobject.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/gobjuserdata.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/memory.h>
#include <sysdolphin/baselib/mobj.h>
#include <sysdolphin/baselib/random.h>
#include <sysdolphin/baselib/sislib.h>
#include <sysdolphin/baselib/wobj.h>
#include <melee/cm/camera.h>
#include <melee/ft/ftlib.h>
#include <melee/gm/gm_unsplit.h>
#include <melee/gr/granime.h>
#include <melee/gr/grdatfiles.h>
#include <melee/gr/grdisplay.h>
#include <melee/gr/grlib.h>
#include <melee/gr/grzakogenerator.h>
#include <melee/gr/inlines.h>
#include <melee/gr/stage.h>
#include <melee/gr/types.h>
#include <melee/lb/lb_00B0.h>
#include <melee/lb/lb_00F9.h>
#include <melee/lb/lbdvd.h>
#include <melee/lb/lbfile.h>
#include <melee/lb/lblanguage.h>
#include <melee/lb/lbvector.h>
#include <melee/mp/mplib.h>
#include <melee/pl/player.h>

static struct {
    int x0;
    int x4;
    int x8;
    int xC;
    int x10;
    int x14;
    int x18;
    u8 r, g, b;
    u32 x20;
    u32 x24;
    u32 x28;
    u32 x2C;
    u32 x30;
    u32 x34;
    u32 x38;
    u32 x3C;
    u32 x40;
    u32 x44;
    s16 x48;
    s16 x4A;
    s16 x4C;
    s16 x4E;
    s16 x50;
}* yaku;

S16Vec3 grPs_803E1248[] = {
    { 1, 3, 0 }, { 2, 3, 0 }, { 3, 4, 0 },
    { 4, 5, 0 }, { 5, 6, 0 }, { 7, 9, 0 },
};

static StageCallbacks grPs_803E126C[] = {
    {
        NULL,
        NULL,
        NULL,
        NULL,
        0,
    },
    {
        grStadium_801D1290,
        grStadium_801D1388,
        grStadium_801D1390,
        grStadium_801D13C4,
        0,
    },
    {
        grStadium_801D13E0,
        grStadium_801D1518,
        grStadium_801D1520,
        grStadium_801D156C,
        0xC0000000,
    },
    {
        grStadium_801D1840,
        grStadium_801D19D0,
        grStadium_801D19D8,
        grStadium_801D19F8,
        0,
    },
    {
        grStadium_801D1648,
        grStadium_801D16D4,
        grStadium_801D16DC,
        grStadium_801D16FC,
        0,
    },
    {
        grStadium_801D1570,
        grStadium_801D15FC,
        grStadium_801D1604,
        grStadium_801D1624,
        0,
    },
    {
        grStadium_801D1720,
        grStadium_801D17E0,
        grStadium_801D17E8,
        grStadium_801D1808,
        0,
    },
    {
        grStadium_801D1DE4,
        grStadium_801D1E10,
        grStadium_801D1E18,
        grStadium_801D1E1C,
        0,
    },
    {
        grStadium_801D1DE4,
        grStadium_801D1E10,
        grStadium_801D1E18,
        grStadium_801D1E1C,
        0,
    },
    {
        grStadium_801D1A38,
        grStadium_801D1B40,
        grStadium_801D1B48,
        grStadium_801D1D84,
        0,
    },
};

StageData grPs_803E1334 = {
    0x10,
    grPs_803E126C,
    "/GrPs",
    grStadium_801D101C,
    grStadium_801D1018,
    grStadium_UnkStage0_OnLoad,
    grStadium_UnkStage0_OnStart,
    grStadium_801D10F0,
    grStadium_801D50B8,
    grStadium_801D50C0,
    1,
    grPs_803E1248,
    ARRAY_SIZE(grPs_803E1248),
};

void grStadium_801D1018(bool unused) {}

void grStadium_801D101C(void)
{
    yaku = Ground_801C49F8();

    stage_info.unk8C.b4 = false;
    stage_info.unk8C.b5 = true;

    grStadium_801D10F8(0);
    grStadium_801D10F8(PsType_Display);
    grStadium_801D10F8(2);

    Ground_801C39C0();
    Ground_801C3BB4();

    mpLib_80057BC0(1);
    mpLib_80057BC0(2);
    mpLib_80057BC0(3);
    mpLib_80057BC0(5);
    mpLib_80057BC0(7);
    mpLib_80057BC0(0);
    mpLib_800581DC(6, 4);
}

void grStadium_UnkStage0_OnLoad(void) {}

void grStadium_UnkStage0_OnStart(void)
{
    grZakoGenerator_801CAE04(0);
}

bool grStadium_801D10F0(void)
{
    return false;
}

/**
 * Creates a specific sub-type of Ground_GObj for Pokemon Stadium
 * (e.g. id=1 for the jumbotron display)
 */
Ground_GObj* grStadium_801D10F8(StadiumGrType id)
{
    Ground_GObj* gobj;
    StageCallbacks* cb;

    cb = &grPs_803E126C[id];
    gobj = Ground_801C14D0(id);

    if (gobj != NULL) {
        Ground* gp = GET_GROUND(gobj);
        gp->x8_callback = NULL;
        gp->xC_callback = NULL;
        GObj_SetupGXLink(gobj, grDisplay_801C5DB0, 3, 0);
        if (cb->callback3 != NULL) {
            gp->x1C_callback = cb->callback3;
        }
        if (cb->callback0 != NULL) {
            cb->callback0(gobj);
        }
        if (cb->callback2 != NULL) {
            HSD_GObjProc_8038FD54(gobj, cb->callback2, 4);
        }
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grpstadium.c", 0x120,
                 id);
    }
    return gobj;
}

void fn_801D11E4(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    CmSubject* cam = Camera_80029020();
    gp->u.display.xF4 = cam;

    if (cam != NULL) {
        float scale = Ground_801C0498();
        gp->u.display.xF4->x8 = 1;
        gp->u.display.xF4->x10.x = 0;
        gp->u.display.xF4->x10.y = 30 * scale;
        gp->u.display.xF4->x10.z = 0;
        gp->u.display.xF4->x40.x = -25 * scale;
        gp->u.display.xF4->x40.y = +25 * scale;
        gp->u.display.xF4->x48.x = +10 * scale;
        gp->u.display.xF4->x48.y = -10 * scale;
    }
}

void grStadium_801D1290(Ground_GObj* gobj)
{
    HSD_MObj* mobj;
    Ground* gp = GET_GROUND(gobj);

    grAnime_801C8138(gobj, gp->map_id, 0);
    grAnime_801C77FC(gobj, 0, 7);
    gp->u.display.xD0 = HSD_ArchiveGetPublicAddress(
        grDatFiles_801C6330(1)->unk0,
        "GrdPStadiumBG_OVDummy_mat6962_GrdPStadiumDummy_0_image_desc");
    if (gp->u.display.xD0 == NULL) {
        OSReport("no such image desc!\n");
    }
    gp->u.display.xC8 = grStadium_801D3138(gobj, gp->u.display.xD0, &mobj);
    gp->u.display.xCC = mobj;
    if (gp->u.display.xC8 == NULL) {
        OSReport("no such tobj!\n");
    }
    grStadium_801D2278(gobj);
    Ground_801C10B8(gobj, fn_801D11E4);
    gp->x11_flags.b012 = 1;
    gobj->render_cb = fn_801D5074;
}

bool grStadium_801D1388(Ground_GObj* gobj)
{
    return false;
}

void grStadium_801D1390(Ground_GObj* gobj)
{
    grStadium_801D1E20();
    grStadium_801D2344(gobj);
}

void grStadium_801D13C4(Ground_GObj* gobj) {}

void fn_801D13C8(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    gp->u.stadium.xC4_b0 = false;
}

/// @todo this is a commonly used inline; it should be moved to random.h
inline int randi(int i)
{
    if (i != 0) {
        return HSD_Randi(i);
    } else {
        return 0;
    }
}

void grStadium_801D13E0(Ground_GObj* gobj)
{
    HSD_MObj* mobj;
    s32 temp_r28;
    s32 var_r27;

    Ground* gr = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);

    Ground_801C2ED0(jobj, gr->map_id);
    grAnime_801C8138(gobj, gr->map_id, 0);
    mobj = (void*) lbDvd_GetPreloadedArchive(0x7D5);
    gr->u.stadium.xCC = mobj;
    if (mobj == NULL) {
        gr->u.stadium.xCC = HSD_MemAlloc(0x50000);
    }
    gr->u.stadium.xC4_b1 = false;
    gr->u.stadium.xD0 = NULL;
    gr->u.stadium.xD4 = 0.0F;
    gr->u.stadium.xDC = 0;
    gr->u.stadium.xDE = 5;
    gr->u.stadium.xE0 = -1;
    gr->u.stadium.xE2 = -1;
    gr->u.stadium.xE4 = grStadium_801D10F8(gr->u.stadium.xDE);
    gr->u.stadium.xE8 = NULL;
    var_r27 = yaku->x4;
    temp_r28 = yaku->x0;
    if (var_r27 > yaku->x0) {
        var_r27 = temp_r28 + randi(var_r27 - temp_r28);
    } else if (var_r27 < temp_r28) {
        var_r27 += randi(temp_r28 - var_r27);
    }
    gr->u.stadium.xD8 = var_r27;
    gr->x11_flags.b012 = 1;
    mpLib_800575B0(0x55);
    mpLib_800575B0(0x6F);
    Ground_801C10B8(gobj, fn_801D13C8);
    gr->u.stadium.xC4_b0 = true;
}

bool grStadium_801D1518(Ground_GObj* gobj)
{
    return false;
}

void grStadium_801D1520(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    if (!gp->u.stadium.xC4_b0) {
        grStadium_801D4548(gobj);
    }
    lb_800115F4();
    Ground_801C2FE0(gobj);
}

void grStadium_801D156C(Ground_GObj* gobj) {}

void grStadium_801D1570(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Ground_801C2ED0(jobj, gp->map_id);
    Ground_801C3214(gp->map_id);
    mpJointListAdd(4);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->u.stadium.xC4_b0 = false;
    gp->u.stadium.xC4_b1 = false;
    gp->x10_flags.b5 = true;
}

bool grStadium_801D15FC(Ground_GObj* gobj)
{
    return false;
}

void grStadium_801D1604(Ground_GObj* gobj)
{
    Ground_801C2FE0(gobj);
}

void grStadium_801D1624(Ground_GObj* gobj)
{
    mpLib_80057BC0(4);
}

void grStadium_801D1648(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Ground_801C2ED0(jobj, gp->map_id);
    Ground_801C3214(gp->map_id);
    mpJointListAdd(3);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->u.stadium.xC4_b0 = false;
    gp->u.stadium.xC4_b1 = false;
    gp->x10_flags.b5 = true;
}

bool grStadium_801D16D4(Ground_GObj* gobj)
{
    return false;
}

void grStadium_801D16DC(Ground_GObj* gobj)
{
    Ground_801C2FE0(gobj);
}

void grStadium_801D16FC(Ground_GObj* gobj)
{
    mpLib_80057BC0(3);
}

static const Vec3 grPs_803B7F68 = { 0, 0, 0 };

void grStadium_801D1720(Ground_GObj* gobj)
{
    Vec3 sp14;
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);

    Ground_801C2ED0(jobj, gp->map_id);
    Ground_801C3214(gp->map_id);
    mpJointListAdd(5);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->u.stadium9.xC4_b0 = false;
    gp->u.stadium9.xC4_b1 = false;
    sp14 = grPs_803B7F68;
    gp->u.stadium9.xC8 = grLib_801C96F8(0x7546, 0x1E, &sp14);
    gp->x10_flags.b5 = true;
}

bool grStadium_801D17E0(Ground_GObj* gobj)
{
    return false;
}

void grStadium_801D17E8(Ground_GObj* gobj)
{
    Ground_801C2FE0(gobj);
}

void grStadium_801D1808(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    if (gp->u.stadium9.xC8 != NULL) {
        grLib_801C9834(gp->u.stadium9.xC8);
    }
    mpLib_80057BC0(5);
}

void grStadium_801D1840(Ground_GObj* gobj)
{
    HSD_JObj* temp_r3;
    HSD_JObj* temp_r3_2;
    HSD_JObj* temp_r3_3;
    HSD_JObj* temp_r3_4;
    HSD_JObj* temp_r3_5;
    HSD_JObj* temp_r3_6;
    HSD_JObj* temp_r3_7;

    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);

    Ground_801C2ED0(jobj, gp->map_id);
    Ground_801C3214(gp->map_id);
    mpJointListAdd(1);
    mpJointListAdd(2);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->u.stadium9.xC4_b0 = false;
    gp->u.stadium9.xC4_b1 = false;

    temp_r3 = Ground_801C3FA4(gobj, 0x13);
    if (temp_r3 != NULL) {
        grLib_801C9808(0x753F, 0x1E, temp_r3);
    }
    temp_r3_2 = Ground_801C3FA4(gobj, 0x14);
    if (temp_r3_2 != NULL) {
        grLib_801C9808(0x7549, 0x1E, temp_r3_2);
    }
    temp_r3_3 = Ground_801C3FA4(gobj, 0x15);
    if (temp_r3_3 != NULL) {
        grLib_801C9808(0x7549, 0x1E, temp_r3_3);
    }
    temp_r3_4 = Ground_801C3FA4(gobj, 0x16);
    if (temp_r3_4 != NULL) {
        grLib_801C9808(0x753F, 0x1E, temp_r3_4);
    }
    temp_r3_5 = Ground_801C3FA4(gobj, 0x17);
    if (temp_r3_5 != NULL) {
        grLib_801C9808(0x753F, 0x1E, temp_r3_5);
    }
    temp_r3_6 = Ground_801C3FA4(gobj, 0x18);
    if (temp_r3_6 != NULL) {
        grLib_801C9808(0x7549, 0x1E, temp_r3_6);
    }
    temp_r3_7 = Ground_801C3FA4(gobj, 0x19);
    if (temp_r3_7 != NULL) {
        grLib_801C9808(0x753F, 0x1E, temp_r3_7);
    }
    gp->x10_flags.b5 = true;
}

bool grStadium_801D19D0(Ground_GObj* gobj)
{
    return false;
}

void grStadium_801D19D8(Ground_GObj* gobj)
{
    Ground_801C2FE0(gobj);
}

void grStadium_801D19F8(Ground_GObj* gobj)
{
    HSD_JObj* jobj = Ground_801C3FA4(gobj, 0x12);
    if (jobj != NULL) {
        grLib_801C9908(jobj);
    }
    mpLib_80057BC0(1);
    mpLib_80057BC0(2);
}

static const Vec3 grPs_803B7F74 = { 0, 0, 0 };

void grStadium_801D1A38(Ground_GObj* gobj)
{
    Vec3 sp14;
    Ground* gp;
    HSD_JObj* jobj;

    gp = GET_GROUND(gobj);
    jobj = GET_JOBJ(gobj);

    Ground_801C2ED0(jobj, gp->map_id);
    Ground_801C3214(gp->map_id);
    mpJointListAdd(7);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->u.stadium9.xCC_gobj = grStadium_801D10F8(7);
    gp->u.stadium9.xD0_gobj = grStadium_801D10F8(8);
    mpLib_80057BC0(0);
    gp->u.stadium9.xC4_b0 = false;
    gp->u.stadium9.xC4_b1 = false;
    sp14 = grPs_803B7F74;

    gp->u.stadium9.xC8 = grLib_801C96F8(0x7544, 0x1E, &sp14);
    gp->u.stadium9.xD4_jobj = Ground_801C3FA4(gobj, 7);
    HSD_JObjSetFlagsAll(jobj, 8);
    gp->x10_flags.b5 = true;
}

bool grStadium_801D1B40(Ground_GObj* gobj)
{
    return false;
}

void grStadium_801D1B48(Ground_GObj* gobj)
{
    Ground* gp;
    HSD_JObj* jobj;
    f32 scale;

    jobj = GET_JOBJ(gobj);
    gp = GET_GROUND(gobj);
    scale = HSD_JObjGetScaleY(jobj);

    if (gp->u.stadium9.xCC_gobj != NULL) {
        HSD_JObj* jobj = GET_JOBJ(gp->u.stadium9.xCC_gobj);
        HSD_JObjSetScaleY(jobj, scale);
    }

    if (gp->u.stadium9.xD0_gobj != NULL) {
        HSD_JObj* jobj = GET_JOBJ(gp->u.stadium9.xD0_gobj);
        HSD_JObjSetScaleY(jobj, scale);
    }

    HSD_JObjAddRotationZ(gp->u.stadium9.xD4_jobj, -0.5F * deg_to_rad);

    if (gp->u.stadium9.xC4_b0) {
        gp->u.stadium9.xC4_b0 = false;
        mpJointListAdd(0);
    }
    if (gp->u.stadium9.xC4_b1) {
        gp->u.stadium9.xC4_b1 = false;
        mpLib_80057BC0(0);
    }

    Ground_801C2FE0(gobj);
    mpLib_8005667C(0);
}

void grStadium_801D1D84(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);

    if (gp->u.stadium9.xC8 != NULL) {
        grLib_801C9874(gp->u.stadium9.xC8);
    }
    if (gp->u.stadium9.xCC_gobj != NULL) {
        Ground_801C4A08(gp->u.stadium9.xCC_gobj);
    }
    if (gp->u.stadium9.xD0_gobj != NULL) {
        Ground_801C4A08(gp->u.stadium9.xD0_gobj);
    }
    mpLib_80057BC0(7);
}

void grStadium_801D1DE4(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grStadium_801D1E10(Ground_GObj* gobj)
{
    return false;
}

void grStadium_801D1E18(Ground_GObj* gobj) {}

void grStadium_801D1E1C(Ground_GObj* gobj) {}

extern Vec3 grPs_803B7F80;

inline void mul_vec(Vec* v, float m)
{
    v->x *= m;
    v->y *= m;
    v->z *= m;
}

void grStadium_801D1E20(void)
{
    if (HSD_Randi(200) == 0) {
        Vec3 spC = { 0, -100, -660 };
        int a = HSD_Randi(2);
        int b = HSD_Randi(200);
        PAD_STACK(4);

        spC.x += (a * 2 - 1) * (b + 100);

        mul_vec(&spC, Ground_801C0498());

        grLib_801C96F8(0x7530, 0x1E, &spC);
    }
}

typedef struct ImageDescWrapper {
    HSD_ImageDesc desc;
    u16 flag : 1;
    u16 x1A, x1C;
} ImageDescWrapper;

#define GET_WRAPPER(x) ((ImageDescWrapper*) HSD_GObjGetUserData(x))

void grStadium_801D1EF8(Ground_GObj* gobj)
{
    HSD_JObj* jobj;

    Ground* gp = GET_GROUND(gobj);
    ImageDescWrapper* wrapper;

    u32 temp_r29;
    HSD_TObj* tobj;

    PAD_STACK(4);

    if (gp->u.display.xF8_0) {
        temp_r29 = gp->u.display.xE8 ^ gp->u.display.xE6;
        if (temp_r29 & 1) {
            jobj = Ground_801C3FA4(gobj, 6);
            if (jobj != NULL) {
                if (gp->u.display.xE6 & 1) {
                    HSD_JObjClearFlags(jobj, 0x10);
                } else {
                    HSD_JObjSetFlags(jobj, 0x10);
                }
            }
        }
        if (temp_r29 & 2) {
            jobj = Ground_801C3FA4(gobj, 3);
            if (jobj != NULL) {
                if (gp->u.display.xE6 & 2) {
                    HSD_JObjClearFlags(jobj, 0x10);
                } else {
                    HSD_JObjSetFlags(jobj, 0x10);
                }
            }
        }
        if (temp_r29 & 8) {
            jobj = Ground_801C3FA4(gobj, 7);
            if (jobj != NULL) {
                if (gp->u.display.xE6 & 8) {
                    HSD_JObjClearFlags(jobj, 0x10);
                } else {
                    HSD_JObjSetFlags(jobj, 0x10);
                }
            }
        }
        if (temp_r29 & 0x10) {
            jobj = Ground_801C3FA4(gobj, 9);
            if (jobj != NULL) {
                if (gp->u.display.xE6 & 0x10) {
                    HSD_JObjClearFlags(jobj, 0x10);
                } else {
                    HSD_JObjSetFlags(jobj, 0x10);
                }
            }
        }
        if (temp_r29 & 4) {
            jobj = Ground_801C3FA4(gobj, 4);
            if (jobj != NULL) {
                if (gp->u.display.xE6 & 4) {
                    HSD_JObjClearFlags(jobj, 0x10);
                } else {
                    HSD_JObjSetFlags(jobj, 0x10);
                }
            }
        }
        if (temp_r29 & 0x20) {
            jobj = Ground_801C3FA4(gobj, 8);
            if (jobj != NULL) {
                if (gp->u.display.xE6 & 0x20) {
                    HSD_JObjClearFlags(jobj, 0x10);
                } else {
                    HSD_JObjSetFlags(jobj, 0x10);
                }
            }
        }
        if (temp_r29 & 0x80) {
            jobj = Ground_801C3FA4(gobj, 5);
            if (jobj != NULL) {
                if (gp->u.display.xE6 & 0x80) {
                    HSD_JObjClearFlags(jobj, 0x10);
                } else {
                    HSD_JObjSetFlags(jobj, 0x10);
                }
            }
        }
        if (temp_r29 & 0x40) {
            jobj = Ground_801C3FA4(gobj, 2);
            if (jobj != NULL) {
                if (gp->u.display.xE6 & 0x40) {
                    HSD_JObjClearFlags(jobj, 0x10);
                } else {
                    HSD_JObjSetFlags(jobj, 0x10);
                }
            }
        }
        switch (gp->u.display.xE4) {
        case 0:
        case 1:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 17:
            tobj = gp->u.display.xC8;
            if (tobj != NULL) {
                if (gp->u.display.xD4 != NULL) {
                    wrapper = GET_WRAPPER(gp->u.display.xD4);
                    tobj->imagedesc = &wrapper->desc;
                    grStadium_801D21E4(gobj, 0);
                }
            }
            break;
        case 7:
            tobj = gp->u.display.xC8;
            if (tobj != NULL) {
                if (gp->u.display.xD8 != NULL) {
                    wrapper = GET_WRAPPER(gp->u.display.xD8);
                    tobj->imagedesc = &wrapper->desc;
                    grStadium_801D21E4(gobj, 1);
                }
            }
            break;
        case 8:
            tobj = gp->u.display.xC8;
            if (tobj != NULL) {
                if (gp->u.display.xDC != NULL) {
                    wrapper = GET_WRAPPER(gp->u.display.xDC);
                    tobj->imagedesc = &wrapper->desc;
                    grStadium_801D21E4(gobj, 1);
                }
            }
            break;
        }
        gp->u.display.xE8 = gp->u.display.xE6;
    }
}

void grStadium_801D21E4(Ground_GObj* gobj, bool arg1)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_MObj* mobj = gp->u.display.xCC;

    if (mobj == NULL) {
        return;
    }

    if (arg1) {
        HSD_MObjClearFlags(mobj, 2);
        HSD_MObjSetFlags(mobj, 1);
        HSD_MObjSetDiffuseColor(mobj, yaku->r, yaku->g, yaku->b);
    } else {
        HSD_MObjSetFlags(mobj, 2);
        HSD_MObjClearFlags(mobj, 1);
    }
    HSD_MObjCompileTev(mobj);
}

void grStadium_801D2278(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    ImageDescWrapper* wrapper;

    gp->u.display.xE4 = 1;
    gp->u.display.xE6 = 1;
    gp->u.display.xE8 = -1;
    gp->u.display.xF8_0 = false;
    gp->u.display.xF8_1 = false;
    gp->u.display.xF8_2 = false;
    gp->u.display.xEA = -1;
    gp->u.display.xEE = 99;
    gp->u.display.xF2 = 0;
    gp->u.display.xD4 = grStadium_801D2BEC();
    gp->u.display.xD8 = grStadium_801D2D78();
    gp->u.display.xDC = grStadium_801D2E24();
    wrapper = GET_WRAPPER(gp->u.display.xDC);
    wrapper->x1A = 200;
    wrapper->x1C = 160;
    gp->u.display.xF4 = NULL;
    grStadium_801D2528(gobj, 0, 0);
}

void grStadium_801D2344(Ground_GObj* g)
{
    Ground_GObj* gobj = g;
    Ground* gp;
    s16 temp_r0;
    ImageDescWrapper* temp_r3_6;
    ImageDescWrapper* temp_r3_8;

    gp = GET_GROUND(gobj);
    temp_r0 = gp->u.display.xE4;
    switch (temp_r0) {
    case 0:
        grStadium_801D4194(gobj);
        break;
    case 1:
        grStadium_801D39A0(gobj);
        if (gp->u.display.xE0-- < 0) {
            grStadium_801D2A60(gobj);
        }
        break;
    case 9:
        grStadium_801D3A0C(gobj);
        if (gp->u.display.xE0-- < 0) {
            grStadium_801D2A60(gobj);
        }
        break;
    case 14:
        grStadium_801D3BBC(gobj);
        if (gp->u.display.xE0-- < 0) {
            grStadium_801D2A60(gobj);
        }
        break;
    case 10:
    case 11:
    case 12:
    case 13:
        grStadium_801D3F40(gobj, gp->u.display.xE4);
        break;
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 15:
    case 16:
        if (gp->u.display.xE0-- < 0) {
            grStadium_801D2A60(gobj);
        }
        break;
    case 7:
        if (gp->u.display.xE0-- < 0) {
            grStadium_801D2A60(gobj);
            break;
        }
        temp_r3_6 = GET_WRAPPER(gp->u.display.xD8);
        temp_r3_6->flag = false;
        break;
    case 8:
        if (gp->u.display.xE0-- < 0 ||
            Player_GetEntity(gp->u.display.xEE) == NULL ||
            Player_8003219C(gp->u.display.xEE))
        {
            grStadium_801D2A60(gobj);
            break;
        }
        temp_r3_8 = GET_WRAPPER(gp->u.display.xDC);
        temp_r3_8->flag = 0;
        if (gp->u.display.xDC == NULL ||
            Player_GetEntity(gp->u.display.xEE) == NULL ||
            Player_8003219C(gp->u.display.xEE) || !grStadium_801D32D0(gobj))
        {
            grStadium_801D2A60(gobj);
        }
        break;
    }
}

typedef struct TextWrapper {
    HSD_ImageDesc desc;
    HSD_Text* x18;
    HSD_Text* x1C;
} TextWrapper;

/// @todo can these inlines be merged?
inline int randi_between_2(int a, int b)
{
    int result = b;
    if (b > a) {
        result = a + randi(b - a);
    } else if (b < a) {
        result = b + randi(a - b);
    }
    return result;
}

inline int randi_between(int a, int b)
{
    if (b > a) {
        return a + randi(b - a);
    } else if (b < a) {
        return b + randi(a - b);
    }
    return b;
}

void grStadium_801D2528(Ground_GObj* gobj, int arg1, int arg2)
{
    Ground* gp = GET_GROUND(gobj);
    int i;
    ImageDescWrapper* temp_r27;
    TextWrapper* temp_r27_1;
    s16 n;

    PAD_STACK(0x8);

    if (gm_8018841C()) {
        switch (arg1) {
        case 1:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
            arg1 = 7;
            break;
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
            __assert("grpstadium.c", 0x536, "0");
            break;
        }
    }
    gp->u.display.xEA = gp->u.display.xE4;
    gp->u.display.xE4 = arg1;
    switch (gp->u.display.xE4) {
    case 0:
        grStadium_801D4194(gobj);
        gp->u.display.xE6 = 0x40;
        gp->u.display.xF8_0 = false;
        gp->u.display.xF8_1 = false;
        if (gp->u.display.xF4 != NULL) {
            gp->u.display.xF4->x8 = 1;
        }
        break;
    case 1:
        grStadium_801D39A0(gobj);
        gp->u.display.xE6 = 0x40;
        gp->u.display.xE0 = yaku->x20;
        gp->u.display.xF8_0 = false;
        gp->u.display.xF8_1 = false;
        if (gp->u.display.xF4 != NULL) {
            gp->u.display.xF4->x8 = 1;
        }
        break;
    case 9:
        grStadium_801D3A0C(gobj);
        gp->u.display.xE6 = 0x40;
        gp->u.display.xE0 = yaku->x24;
        gp->u.display.xF8_0 = false;
        gp->u.display.xF8_1 = false;
        if (gp->u.display.xF4 != NULL) {
            gp->u.display.xF4->x8 = 1;
        }
        break;
    case 14:
        grStadium_801D3BBC(gobj);
        gp->u.display.xE6 = 0x40;
        gp->u.display.xE0 = yaku->x2C;
        gp->u.display.xF8_0 = false;
        gp->u.display.xF8_1 = false;
        if (gp->u.display.xF4 != NULL) {
            gp->u.display.xF4->x8 = 1;
        }
        break;
    case 10:
    case 11:
    case 12:
    case 13:
        grStadium_801D3F40(gobj, gp->u.display.xE4);
        gp->u.display.xE6 = 0x40;
        gp->u.display.xF8_0 = false;
        gp->u.display.xF8_1 = false;
        if (gp->u.display.xF4 != NULL) {
            gp->u.display.xF4->x8 = 1;
        }
        break;
    case 15:
        gp->u.display.xE6 = 0x20;
        gp->u.display.xE0 = yaku->x20;
        if (gp->u.display.xF4 != NULL) {
            gp->u.display.xF4->x8 = 1;
        }
        break;
    case 16:
        gp->u.display.xE6 = 0x80;
        gp->u.display.xE0 = yaku->x20;
        if (gp->u.display.xF4 != NULL) {
            gp->u.display.xF4->x8 = 1;
        }
        break;
    case 7:
        gp->u.display.xE6 = 0x40;
        gp->u.display.xE0 = randi_between_2(yaku->x38, yaku->x3C);
        gp->u.display.xF8_0 = false;
        gp->u.display.xF8_1 = false;
        if (gp->u.display.xF4 != NULL) {
            gp->u.display.xF4->x8 = 1;
        }
        break;
    case 8:
        gp->u.display.xE6 = 0x40;
        gp->u.display.xE0 = randi_between(yaku->x30, yaku->x34);
        n = gp->u.display.xEE++;
        for (i = 0; gp->u.display.xEE != n; gp->u.display.xEE++) {
            if (gp->u.display.xEE >= 6) {
                gp->u.display.xEE = 0;
                if (++i > 2) {
                    gp->u.display.xEE = 0;
                    gp->u.display.xE0 = -1;
                    break;
                }
            }
            if (Player_GetEntity(gp->u.display.xEE) != NULL) {
                break;
            }
        }
        gp->u.display.xF8_0 = false;
        gp->u.display.xF8_1 = false;
        if (gp->u.display.xF4 != NULL) {
            gp->u.display.xF4->x8 = 1;
        }
        break;
    case 17:
        gp->u.display.xE6 = 0x40;
        temp_r27_1 = gp->u.display.xD4->user_data;
        HSD_SisLib_803A7664((void*) temp_r27_1->x1C);
        HSD_SisLib_803A6368((void*) temp_r27_1->x18, 4);
        gp->u.display.xF8_0 = false;
        gp->u.display.xF8_1 = false;
        break;
    case 2:
        gp->u.display.xE6 = 1;
        gp->u.display.xE0 = yaku->x28;
        if (gp->u.display.xF4 != NULL) {
            gp->u.display.xF4->x8 = 0;
        }
        break;
    case 3:
        gp->u.display.xE6 = 2;
        gp->u.display.xE0 = yaku->x28;
        if (gp->u.display.xF4 != NULL) {
            gp->u.display.xF4->x8 = 0;
        }
        break;
    case 4:
        gp->u.display.xE6 = 4;
        gp->u.display.xE0 = yaku->x28;
        if (gp->u.display.xF4 != NULL) {
            gp->u.display.xF4->x8 = 0;
        }
        break;
    case 5:
        gp->u.display.xE6 = 0x10;
        gp->u.display.xE0 = yaku->x28;
        if (gp->u.display.xF4 != NULL) {
            gp->u.display.xF4->x8 = 0;
        }
        break;
    case 6:
        gp->u.display.xE6 = 8;
        gp->u.display.xE0 = yaku->x28;
        if (gp->u.display.xF4 != NULL) {
            gp->u.display.xF4->x8 = 0;
        }
        break;
    }
    if (arg2 != 0) {
        gp->u.display.xE0 = arg2;
    }
}

void grStadium_801D2A60(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    float val;
    int var_r4;

    if (gp->u.display.xF2 >= yaku->x50) {
        gp->u.display.xF2 = 0;
        var_r4 = 0xE;
    } else {
        do {
            val =
                HSD_Randf() * (yaku->x48 + yaku->x4A + yaku->x4C + yaku->x4E);
            if (val - yaku->x48 < 0) {
                var_r4 = 8;
            } else if (val - yaku->x48 - yaku->x4C < 0) {
                var_r4 = 7;
            } else if (val - yaku->x48 - yaku->x4C - yaku->x4A < 0) {
                var_r4 = 1;
            } else if (val - yaku->x48 - yaku->x4C - yaku->x4A - yaku->x4E < 0)
            {
                var_r4 = 15;
            } else {
                var_r4 = 1;
            }
        } while (var_r4 == gp->u.display.xE4 || var_r4 == gp->u.display.xEA);
    }
    gp->u.display.xF2++;
    grStadium_801D2528(gobj, var_r4, 0);
}

static HSD_WObjDesc grPs_803E14D4 = { NULL, { 0.0F, 0.0F, 1.0F }, NULL };
static HSD_WObjDesc grPs_803E14E8 = { NULL, { 0.0F, 0.0F, 0.0F }, NULL };

static HSD_CameraDescPerspective grPs_803E14FC = {
    NULL,
    0,
    1,
    { 0, 0xFA, 0, 0xA0 },
    { 0, 0xFA, 0, 0xA0 },
    &grPs_803E14D4,
    &grPs_803E14E8,
    0.0F,
    NULL,
    0.1F,
    32768.0F,
    30.0F,
    1.3636F,
};

HSD_GObj* grStadium_801D2BEC(void)
{
    HSD_CObj* cobj;
    HSD_GObj* gobj;
    TextWrapper* text;
    HSD_Text* hsd_text;
    UnkArchiveStruct* archive;
    PAD_STACK(4);

    gobj = GObj_Create(0x11, 0x13, 0);
    cobj = lb_80013B14(&grPs_803E14FC);
    HSD_CObjSetOrtho(cobj, 0.0F, -160.0F, 0.0F, 250.0F);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784B, cobj);
    GObj_SetupGXLinkMax(gobj, fn_801D2ED0, 1);
    gobj->gxlink_prios = 2;
    text = HSD_MemAlloc(sizeof(*text));
    GObj_InitUserData(gobj, 3, HSD_Free, text);
    memzero(text, 0x18);
    lb_800121FC(&text->desc, 0xFA, 0xA0, 4, 0x7D2);
    archive = grDatFiles_801C6324();
    HSD_SisLib_803A611C(1, gobj, 9, 0xD, 0, 1, 0, 1);
    HSD_SisLib_804D1124[1] =
        HSD_ArchiveGetPublicAddress(archive->unk0, "SIS_GrPStadiumData");
    text->x18 = HSD_SisLib_803A5ACC(1, 0, 0.0F, 0.0F, 0.0F, 250.0F, 160.0F);
    text->x1C = HSD_SisLib_803A6754(1, 0);
    text->x1C->pos_z = 0.0F;
    hsd_text = text->x1C;
    hsd_text->box_size_x = 250.0F;
    hsd_text->box_size_y = 160.0F;
    return gobj;
}

HSD_GObj* grStadium_801D2D78(void)
{
    HSD_GObj* temp_r3;
    ImageDescWrapper* wrapper;

    temp_r3 = GObj_Create(0x11, 0x12, 0);
    GObj_SetupGXLinkMax(temp_r3, fn_801D2FD0, 3);
    wrapper = HSD_MemAlloc(0x1C);
    GObj_InitUserData(temp_r3, 3, HSD_Free, wrapper);
    memzero(&wrapper->desc, sizeof(wrapper->desc));
    lb_800121FC(&wrapper->desc, 0x280, 0x196, 4, 0x7D3);
    wrapper->flag = true;
    return temp_r3;
}

HSD_GObj* grStadium_801D2E24(void)
{
    HSD_GObj* gobj = GObj_Create(0x11, 0x12, 0);
    ImageDescWrapper* wrapper;
    GObj_SetupGXLinkMax(gobj, fn_801D3084, 3);
    wrapper = HSD_MemAlloc(sizeof(ImageDescWrapper));
    GObj_InitUserData(gobj, 3, HSD_Free, wrapper);
    memzero(&wrapper->desc, sizeof(HSD_ImageDesc));
    lb_800121FC(&wrapper->desc, 0x7C, 0x50, 4, 0x7D4);
    wrapper->flag = false;
    return gobj;
}

void fn_801D2ED0(HSD_GObj* gobj, int unused)
{
    ImageDescWrapper* wrapper;
    Ground* gp2;
    HSD_CObj* cobj;
    HSD_GObj* vision_gobj;
    PAD_STACK(4);

    cobj = GET_COBJ(gobj);
    wrapper = GET_WRAPPER(gobj);
    if (HSD_CObjSetCurrent(cobj) != 0) {
        HSD_SetEraseColor(0, 0, 0, 1);
        HSD_CObjEraseScreen(cobj, 1, 0, 0);
        HSD_FogSet(NULL);
        HSD_GObj_80390ED0(gobj, 7);
        HSD_CObjEndCurrent();
    }
    lb_800122C8(&wrapper->desc, 0, 0, 1);
    vision_gobj = Ground_801C2BA4(PsType_Display);
    if (vision_gobj == NULL) {
        __assert("grpstadium.c", 0x6D2, "vision_gobj");
    }
    gp2 = GET_GROUND(vision_gobj);
    if (gp2 == NULL) {
        __assert("grpstadium.c", 0x6D3, "gp2");
    }
    gp2->u.display.xF8_0 = true;
}

void fn_801D2FD0(Ground_GObj* gobj, int unused)
{
    ImageDescWrapper* wrapper = GET_WRAPPER(gobj);
    HSD_GObj* vision_gobj;
    Ground* gp2;

    if (wrapper->flag) {
        return;
    }

    lb_800122C8(&wrapper->desc, 0, 0x24, 0);
    wrapper->flag = true;

    vision_gobj = Ground_801C2BA4(PsType_Display);
    if (vision_gobj == NULL) {
        __assert("grpstadium.c", 0x6EA, "vision_gobj");
    }

    gp2 = GET_GROUND(vision_gobj);
    if (gp2 == NULL) {
        __assert("grpstadium.c", 0x6EB, "gp2");
    }
    gp2->u.display.xF8_0 = true;
}

void fn_801D3084(HSD_GObj* gobj, int unused)
{
    ImageDescWrapper* wrapper = GET_WRAPPER(gobj);
    HSD_GObj* vision_gobj;
    Ground* gp2;

    if (!wrapper->flag) {
        lb_800122C8(&wrapper->desc, wrapper->x1A, wrapper->x1C, 0);
        wrapper->flag = true;
        vision_gobj = Ground_801C2BA4(PsType_Display);
        if (vision_gobj == NULL) {
            __assert("grpstadium.c", 0x703, "vision_gobj");
        }
        gp2 = GET_GROUND(vision_gobj);
        if (gp2 == NULL) {
            __assert("grpstadium.c", 0x704, "gp2");
        }
        gp2->u.display.xF8_0 = true;
    }
}

/// @todo these are commonly used inlines; they should be moved to jobj.h

inline HSD_JObj* jobj_next(HSD_JObj* jobj)
{
    if (jobj == NULL) {
        return NULL;
    }
    return jobj->next;
}

inline HSD_JObj* jobj_parent(HSD_JObj* jobj)
{
    if (jobj == NULL) {
        return NULL;
    }
    return jobj->parent;
}

inline HSD_JObj* jobj_child(HSD_JObj* jobj)
{
    if (jobj == NULL) {
        return NULL;
    }
    return jobj->child;
}

HSD_TObj* grStadium_801D3138(Ground_GObj* gobj, HSD_ImageDesc* desc,
                             HSD_MObj** arg2)
{
    HSD_TObj* tobj;
    HSD_DObj* dobj;
    HSD_JObj* jobj;
    HSD_MObj* mobj;

    jobj = GET_JOBJ(gobj);
    while (jobj != NULL) {
        if (union_type_dobj(jobj)) {
            for (dobj = jobj->u.dobj; dobj != NULL; dobj = dobj->next) {
                mobj = dobj->mobj;
                if (mobj != NULL) {
                    tobj = mobj->tobj;
                    for (; tobj != NULL; tobj = tobj->next) {
                        if (tobj->imagedesc == desc) {
                            *arg2 = mobj;
                            return tobj;
                        }
                    }
                }
            }
        }

        if (!(jobj->flags & JOBJ_INSTANCE) && jobj_child(jobj) != NULL) {
            jobj = jobj_child(jobj);
            continue;
        }
        if (jobj_next(jobj) != NULL) {
            jobj = jobj_next(jobj);
            continue;
        }
        while (true) {
            if (jobj_parent(jobj) == NULL) {
                jobj = NULL;
                break;
            }
            if (jobj_next(jobj_parent(jobj)) != NULL) {
                jobj = jobj_next(jobj_parent(jobj));
                break;
            }
            jobj = jobj_parent(jobj);
        }
    }
    return NULL;
}

bool grStadium_801D32D0(Ground_GObj* gobj)
{
    HSD_CObj* cobj;
    Ground* gp;
    HSD_GObj* player_gobj;
    bool var_r28;
    ImageDescWrapper* wrapper;
    Vec3 sp28;
    Vec3 sp1C;

    PAD_STACK(4);

    var_r28 = false;
    gp = GET_GROUND(gobj);

    if ((cobj = GET_COBJ(Camera_80030A50()))) {
        player_gobj = Player_GetEntity(gp->u.display.xEE);
        if (player_gobj != NULL && !Player_8003219C(gp->u.display.xEE)) {
            if ((wrapper = gp->u.display.xDC->user_data)) {
                ftLib_80086B90(player_gobj, &sp28);
                lbVector_WorldToScreen(cobj, &sp28, &sp1C, 0);
                sp1C.x -= 62.0f;
                if (sp1C.x < cobj->viewport.xmin) {
                    sp1C.x = cobj->viewport.xmin;
                    var_r28 = true;
                } else {
                    if (sp1C.x + 124.0f > cobj->viewport.xmax) {
                        var_r28 = true;
                        sp1C.x = cobj->viewport.xmax - 124.0f;
                    }
                }
                sp1C.y -= 40.0f;
                if (sp1C.y < cobj->viewport.ymin) {
                    sp1C.y = cobj->viewport.ymin;
                    var_r28 = true;
                } else {
                    if (sp1C.y + 80.0F > cobj->viewport.ymax) {
                        var_r28 = true;
                        sp1C.y = cobj->viewport.ymax - 80.0f;
                    }
                }
                wrapper->x1A = ((int) sp1C.x >> 1) * 2;
                wrapper->x1C = ((int) sp1C.y >> 1) * 2;

                if (var_r28) {
                    return false;
                } else {
                    return true;
                }
            }
        }
    }
    return false;
}

static const GXColor grPs_804DAF3C = { 0xFF, 0xFF, 0xFF, 0xFF };

/// @todo is there a way to prevent these being upcast to double
/// when passed to variadic sislib functions?
extern const float grPs_804DAF2C;
extern const float grPs_804DAF30;
extern const float grPs_804DAF34;
extern const float grPs_804DAF38;
extern const float grPs_804DAF40;
extern const float grPs_804DAF44;
extern const float grPs_804DAF48;
extern const float grPs_804DAF4C;
extern const float grPs_804DAF50;
extern const float grPs_804DAF54;
extern const float grPs_804DAF58;
extern const float grPs_804DAF5C;
extern const float grPs_804DAF64;
extern const float grPs_804DAF68;
extern const float grPs_804DAF6C;
extern const float grPs_804DAF74;

/// @todo This is only size 0x100 in the object, but a single
/// TextGlyphTexture is size 0x200. Should TextGlyphTexture be smaller?
static TextGlyphTexture grPs_8049F040;

void grStadium_801D3460(Ground_GObj* gobj)
{
    GXColor sp48;
    const char* sp38[4];
    HSD_Text* temp_r3;
    HSD_Text* temp_r3_2;
    HSD_Text* temp_r4;
    StartMeleeRules* rules;
    s16 temp_r0;
    s32 temp_r29_2;
    s32 var_r27;
    s32 var_r28;
    Ground* temp_r29;
    TextWrapper* gp2;
    void* temp_r3_3;
    Ground* gp;
    int i;

    PAD_STACK(0x14);

    gp = GET_GROUND(gobj);
    gp2 = gp->u.display.xD4->user_data;
    sp48 = grPs_804DAF3C;
    if (gp2->x18 == NULL) {
        __assert("grpstadium.c", 0x780U, "gp2->win_static_p");
    }
    if (gp2->x1C == NULL) {
        __assert("grpstadium.c", 0x781U, "gp2->win_dynamic_p");
    }
    HSD_SisLib_803A7664(gp2->x1C);
    temp_r29 = GET_GROUND(Ground_801C2BA4(2));

    HSD_SisLib_804D1124[1][2].textures = &grPs_8049F040;

    HSD_SisLib_803A6530(1, 5, 6);
    temp_r0 = temp_r29->u.stadium.xDE;

    if (temp_r0 == 3) {
        HSD_SisLib_803A660C(1, 5, 9);
    } else if (temp_r0 == 9) {
        HSD_SisLib_803A660C(1, 5, 0xA);
    } else if (temp_r0 == 6) {
        HSD_SisLib_803A660C(1, 5, 0xB);
    } else if (temp_r0 == 4) {
        HSD_SisLib_803A660C(1, 5, 0xC);
    } else {
        HSD_SisLib_803A660C(1, 5, 8);
    }

    HSD_SisLib_803A660C(1, 5, 7);
    HSD_SisLib_803A6368(gp2->x18, 5);
    gp2->x1C->default_kerning = 0;
    if (lbLang_IsSavedLanguageJP() != 0) {
        temp_r3 = gp2->x1C;
        temp_r3->x34.x = 0.3125f;
        temp_r3->x34.y = 0.625f;
    } else {
        temp_r3_2 = gp2->x1C;
        temp_r3_2->x34.x = 0.26f;
        temp_r3_2->x34.y = 0.625f;
    }
    sp48.r = 0xC0;
    sp48.g = 0xC0;
    var_r28 = 0;
    sp48.b = 0xFF;
    var_r27 = 0;
    gp2->x1C->text_color = sp48;
    gp2->x1C->default_alignment = 1;

    for (i = 0; i < 4; i++) {
        if (Player_GetPlayerSlotType(i) != Gm_PKind_NA) {
            const char* character_name = gm_80160A60(i);
            sp38[var_r28] = character_name;
            if (character_name != NULL) {
                var_r28++;
            }
        }
    }

    gp2->x1C->default_fitting = 1;
    if (var_r28 == 1) {
        HSD_SisLib_803A6B98(gp2->x1C, grPs_804DAF30, grPs_804DAF4C, sp38[0]);
    } else if (var_r28 == 2) {
        HSD_SisLib_803A6B98(gp2->x1C, grPs_804DAF2C, grPs_804DAF4C, sp38[0]);
        HSD_SisLib_803A6B98(gp2->x1C, grPs_804DAF50, grPs_804DAF4C, sp38[1]);
    } else if (var_r28 == 3) {
        HSD_SisLib_803A6B98(gp2->x1C, grPs_804DAF2C, grPs_804DAF54, sp38[0]);
        HSD_SisLib_803A6B98(gp2->x1C, grPs_804DAF50, grPs_804DAF54, sp38[1]);
        HSD_SisLib_803A6B98(gp2->x1C, grPs_804DAF30, grPs_804DAF38, sp38[2]);
    } else if (var_r28 == 4) {
        HSD_SisLib_803A6B98(gp2->x1C, grPs_804DAF2C, grPs_804DAF54, sp38[0]);
        HSD_SisLib_803A6B98(gp2->x1C, grPs_804DAF50, grPs_804DAF54, sp38[1]);
        HSD_SisLib_803A6B98(gp2->x1C, grPs_804DAF2C, grPs_804DAF38, sp38[2]);
        HSD_SisLib_803A6B98(gp2->x1C, grPs_804DAF50, grPs_804DAF38, sp38[3]);
    }

    gp2->x1C->default_fitting = 0;
    rules = gm_8016AE50();
    temp_r4 = gp2->x1C;
    temp_r4->x34.x = 0.625f;
    temp_r4->x34.y = 0.625f;

    if ((rules->x10 == 0) | !rules->x0_6) {
        HSD_SisLib_803A6B98(gp2->x1C, grPs_804DAF58, grPs_804DAF5C,
                            "00:00 00");
        return;
    }
    temp_r29_2 = gm_8016AEEC();
    HSD_SisLib_803A6B98(gp2->x1C, grPs_804DAF58, grPs_804DAF5C,
                        "%02d:%02d %02d", temp_r29_2 / 60, temp_r29_2 % 60,
                        gm_8016AF0C());
}

const GXColor grPs_804DAF60 = { 0xC0, 0xC0, 0xFF, 0xFF };

void grStadium_801D384C(Ground_GObj* gobj)
{
    u8 _[4];
    GXColor sp2C;
    HSD_GObj* temp_r3;
    HSD_Text* temp_r3_2;
    HSD_Text* temp_r3_3;
    HSD_Text* temp_r6;
    s32 temp_r29;
    TextWrapper* gp2;
    Ground* gp = GET_GROUND(gobj);
    PAD_STACK(0x18);

    temp_r3 = gp->u.display.xD4;
    gp2 = temp_r3->user_data;
    sp2C = grPs_804DAF60;
    temp_r29 = gm_801694A0(temp_r3);
    if (gp2->x18 == NULL) {
        __assert("grpstadium.c", 0x812, "gp2->win_static_p");
    }
    if (gp2->x1C == NULL) {
        __assert("grpstadium.c", 0x813, "gp2->win_dynamic_p");
    }
    HSD_SisLib_803A7664(gp2->x1C);
    if (lbLang_IsSavedLanguageJP()) {
        HSD_SisLib_803A6368(gp2->x18, 0xD);
        gp2->x1C->default_kerning = 0;
        temp_r3_2 = gp2->x1C;
        temp_r3_2->x34.x = 1.5f;
        temp_r3_2->x34.y = 1.5f;
        temp_r6 = gp2->x1C;
        temp_r6->text_color = sp2C;
        gp2->x1C->default_alignment = 1;
        HSD_SisLib_803A6B98(gp2->x1C, grPs_804DAF58, grPs_804DAF68, "%d",
                            temp_r29, temp_r6);
    } else {
        HSD_SisLib_803A6368(gp2->x18, 0xD);
        gp2->x1C->default_kerning = 0;
        temp_r3_3 = gp2->x1C;
        temp_r3_3->x34.x = 1.5f;
        temp_r3_3->x34.y = 1.5f;
        gp2->x1C->text_color = sp2C;
        HSD_SisLib_803A6B98(gp2->x1C, grPs_804DAF6C, grPs_804DAF68, "%3d",
                            temp_r29);
    }
}

void grStadium_801D39A0(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    if (gp->u.display.xE4 == 1) {
        if (gm_8016B184() || gp->u.display.xF8_2) {
            grStadium_801D384C(gobj);
        } else {
            grStadium_801D3460(gobj);
        }
    }
}

const GXColor grPs_804DAF70 = { 0xFF, 0xFF, 0xFF, 0xFF };

void grStadium_801D3A0C(Ground_GObj* gobj)
{
    GXColor sp24;
    HSD_Text* temp_r3;
    Ground* gp = GET_GROUND(gobj);
    HSD_GObj* tmp = gp->u.display.xD4;
    TextWrapper* temp_r30 = HSD_GObjGetUserData(tmp);

    sp24 = grPs_804DAF70;
    PAD_STACK(0x10);

    if (temp_r30->x18 == NULL) {
        __assert("grpstadium.c", 0x848, "gp2->win_static_p");
    }
    if (temp_r30->x1C == NULL) {
        __assert("grpstadium.c", 0x849, "gp2->win_dynamic_p");
    }
    HSD_SisLib_803A7664(temp_r30->x1C);
    HSD_SisLib_803A6368(temp_r30->x18, 3);
    temp_r30->x1C->default_kerning = 1;
    sp24.r = 0xC0;
    sp24.g = 0xC0;
    sp24.b = 0xFF;
    temp_r30->x1C->text_color = sp24;
    temp_r30->x1C->default_alignment = 1;
    if (gp->u.display.xF0 == Gm_PKind_Human) {
        temp_r3 = temp_r30->x1C;
        temp_r3->x34.x = 0.625F;
        temp_r3->x34.y = 1.5F;
        HSD_SisLib_803A6B98(temp_r30->x1C, grPs_804DAF58, grPs_804DAF74,
                            "Ｐｌａｙｅｒ %d Ｄｅｆｅａｔｅｄ",
                            gp->u.display.xEE + 1);
    } else {
        temp_r3 = temp_r30->x1C;
        temp_r3->x34.x = 0.42F;
        temp_r3->x34.y = 1.2F;
        HSD_SisLib_803A6B98(temp_r30->x1C, grPs_804DAF58, grPs_804DAF74,
                            "Computer Player Defeated");
    }
}

const float grPs_804DAF2C = 62;
const float grPs_804DAF30 = 124;
const float grPs_804DAF34 = 40;
const float grPs_804DAF38 = 80;
const float grPs_804DAF40 = 0.3125;
const float grPs_804DAF44 = 0.625;
const float grPs_804DAF48 = 0.26;
const float grPs_804DAF4C = 70;
const float grPs_804DAF50 = 186;
const float grPs_804DAF54 = 60;
const float grPs_804DAF58 = 125;
const float grPs_804DAF5C = 120;
const float grPs_804DAF64 = 1.5;
const float grPs_804DAF68 = 52;
const float grPs_804DAF6C = -3;
const float grPs_804DAF74 = 56;

void grStadium_801D3B4C(int arg0, int slot_type)
{
    Ground_GObj* gobj;
    Ground* gp;

    if (stage_info.internal_stage_id == PSTADIUM) {
        gobj = Ground_801C2BA4(PsType_Display);
        gp = GET_GROUND(gobj);
        gp->u.display.xEE = arg0;
        gp->u.display.xF0 = slot_type;
        grStadium_801D2528(gobj, 9, 0);
    }
}

static const U8Vec4 grPs_803B7F8C[] = {
    { 0, 0, 0, 0x50 },
    { 0, 0, 0, 0x40 },
    { 0, 0, 0, 0x30 },
    { 0, 0, 0, 0x20 },
};

void grStadium_801D3BBC(Ground_GObj* arg0)
{
    GXColor sp28[5];
    HSD_GObj* temp_r3;
    HSD_GObj* temp_r3_4;
    HSD_Text* temp_r3_2;
    HSD_Text* temp_r3_3;
    f32 var_f0;
    f32 var_f0_2;
    f32 var_f0_3;
    s32 temp_r29;
    const char* character_name;
    s32 var_r25;
    s32 var_r28;
    s32 var_r30;
    s32 var_r30_2;
    s8 temp_r25;
    u8 temp_r26;
    TextWrapper* temp_r31;
    Ground* gp;
    HSD_GObj* text_gobj;

    var_r30 = 0;
    gp = GET_GROUND(arg0);
    text_gobj = gp->u.display.xD4;
    temp_r31 = text_gobj->user_data;
    if (temp_r31->x18 == NULL) {
        __assert("grpstadium.c", 0x884U, "gp2->win_static_p");
    }
    if (temp_r31->x1C == NULL) {
        __assert("grpstadium.c", 0x885U, "gp2->win_dynamic_p");
    }
    var_r25 = 0;
    do {
        if ((Player_GetPlayerSlotType(var_r25) != Gm_PKind_NA) &&
            (Player_8003219C(var_r25) == 0))
        {
            temp_r3 = Player_GetEntity(var_r25);
            if (temp_r3 != NULL && gm_8016C6C0(temp_r3) == 0) {
                var_r30 += 1;
            }
        }
        var_r25 += 1;
    } while (var_r25 < 6);
    HSD_SisLib_803A7664(temp_r31->x1C);

    if (var_r30 == 1) {
        HSD_SisLib_803A6368(temp_r31->x18, 0xE);
    } else if (var_r30 == 2) {
        HSD_SisLib_803A6368(temp_r31->x18, 0xF);
    } else if (var_r30 == 3) {
        HSD_SisLib_803A6368(temp_r31->x18, 0x10);
    } else if (var_r30 == 4) {
        HSD_SisLib_803A6368(temp_r31->x18, 0x11);
    } else {
        HSD_SisLib_803A6368(temp_r31->x18, 3);
        return;
    }

    temp_r31->x1C->default_kerning = 0;
    temp_r31->x1C->default_alignment = 1;
    temp_r31->x1C->default_fitting = 1;
    if (lbLang_IsSavedLanguageJP() != 0) {
        temp_r3_2 = temp_r31->x1C;
        temp_r3_2->x34.x = 1.0f;
        temp_r3_2->x34.y = 1.0f;
    } else {
        temp_r3_3 = temp_r31->x1C;
        temp_r3_3->x34.x = 0.8f;
        temp_r3_3->x34.y = 1.0f;
        temp_r31->x1C->default_kerning = 1;
    }
    sp28[1] = *(GXColor*) &grPs_803B7F8C[0];
    sp28[2] = *(GXColor*) &grPs_803B7F8C[1];
    var_r28 = 0;
    var_r30_2 = 0;
    sp28[3] = *(GXColor*) &grPs_803B7F8C[2];
    sp28[4] = *(GXColor*) &grPs_803B7F8C[3];
    temp_r29 = sp28[var_r30].r;
    do {
        if (Player_GetPlayerSlotType(var_r30_2) != Gm_PKind_NA &&
            Player_8003219C(var_r30_2) == 0)
        {
            temp_r3_4 = Player_GetEntity(var_r30_2);
            if (temp_r3_4 != NULL && gm_8016C6C0(temp_r3_4) == 0) {
                temp_r25 = Player_GetPlayerSlotType(var_r30_2);
                temp_r26 = gm_8016B168();
                sp28[0] = gm_80160968(gm_80160854(
                    var_r30_2, Player_GetTeam(var_r30_2), temp_r26, temp_r25));
                var_f0 = 1.25f * sp28[0].r;
                if (var_f0 > 255.0f) {
                    var_f0 = 255.0f;
                }
                sp28[0].r = (s8) var_f0;
                var_f0_2 = 1.25f * sp28[0].g;
                if (var_f0_2 > 255.0f) {
                    var_f0_2 = 255.0f;
                }
                sp28[0].r = (u8) (s32) var_f0_2;
                var_f0_3 = 1.25f * sp28[0].b;
                if (var_f0_3 > 255.0f) {
                    var_f0_3 = 255.0f;
                }
                sp28[0].g = (u8) (s32) var_f0_3;
                sp28[0].b = 0xFF;
                temp_r31->x1C->text_color = sp28[0];
                character_name = gm_80160A60(var_r30_2);
                if (character_name != NULL) {
                    HSD_SisLib_803A6B98(temp_r31->x1C, grPs_804DAF58,
                                        (f32) (temp_r29 + var_r28), "%s",
                                        character_name);
                }
                var_r28 += 0x20;
            }
        }
        var_r30_2 += 1;
    } while (var_r30_2 < 6);
}

void grStadium_801D3F40(Ground_GObj* arg0, int arg1)
{
    Ground* gp = GET_GROUND(arg0);
    HSD_GObj* text_gobj = gp->u.display.xD4;
    TextWrapper* gp2 = text_gobj->user_data;
    PAD_STACK(8);

    if (gp2->x18 == NULL) {
        __assert("grpstadium.c", 0x8E8, "gp2->win_static_p");
    }
    if (gp2->x1C == 0U) {
        __assert("grpstadium.c", 0x8E9, "gp2->win_dynamic_p");
    }
    HSD_SisLib_803A7664(gp2->x1C);
    switch (arg1) {
    case 10:
        HSD_SisLib_803A6368(gp2->x18, 0x12);
        return;
    case 11:
        HSD_SisLib_803A6368(gp2->x18, 0x13);
        return;
    case 12:
        HSD_SisLib_803A6368(gp2->x18, 0x14);
        return;
    case 13:
        HSD_SisLib_803A6368(gp2->x18, 0x15);
        return;
    default:
        HSD_SisLib_803A6368(gp2->x18, 3);
        return;
    }
}

void grStadium_801D4040(void)
{
    if (stage_info.internal_stage_id == PSTADIUM) {
        grStadium_801D2528(Ground_801C2BA4(PsType_Display), 0xB, 0);
    }
}

void grStadium_801D4084(void)
{
    if (stage_info.internal_stage_id == PSTADIUM) {
        grStadium_801D2528(Ground_801C2BA4(PsType_Display), 0xA, 0);
    }
}

void grStadium_801D40C8(void)
{
    if (stage_info.internal_stage_id == PSTADIUM) {
        grStadium_801D2528(Ground_801C2BA4(PsType_Display), 0xC, 0);
    }
}

void grStadium_801D410C(void)
{
    if (stage_info.internal_stage_id == PSTADIUM) {
        grStadium_801D2528(Ground_801C2BA4(PsType_Display), 0xD, 0);
    }
}

void grStadium_801D4150(void)
{
    if (stage_info.internal_stage_id == PSTADIUM) {
        grStadium_801D2528(Ground_801C2BA4(PsType_Display), 1, 0);
    }
}

void grStadium_801D4194(Ground_GObj* arg0)
{
    Ground* gp = GET_GROUND(arg0);
    HSD_GObj* text_gobj = gp->u.display.xD4;
    TextWrapper* gp2 = text_gobj->user_data;
    PAD_STACK(4);

    if (gp2->x18 == NULL) {
        __assert("grpstadium.c", 0x950, "gp2->win_static_p");
    }
    if (gp2->x1C == NULL) {
        __assert("grpstadium.c", 0x951, "gp2->win_dynamic_p");
    }
    HSD_SisLib_803A7664(gp2->x1C);
    HSD_SisLib_803A6368(gp2->x18, 3);
}

void fn_801D4220(int un0, int un1, UNK_T un2, bool cancelflag)
{
    Ground_GObj* map_gobj;
    Ground* gp;

    if (cancelflag) {
        __assert("grpstadium.c", 0x969, "!cancelflag");
    }
    map_gobj = Ground_801C2BA4(2);
    if (map_gobj == NULL) {
        __assert("grpstadium.c", 0x96A, "map_gobj");
    }
    gp = GET_GROUND(map_gobj);
    if (gp == NULL) {
        __assert("grpstadium.c", 0x96B, "gp");
    }
    gp->u.stadium.xC4_b1 = false;
}

bool grStadium_801D42B8(void)
{
    HSD_GObj* map_gobj;
    Ground* temp_r3_2;

    map_gobj = Ground_801C2BA4(2);
    if (map_gobj == NULL) {
        __assert("grpstadium.c", 0x978, "map_gobj");
    }
    temp_r3_2 = grStadium_801D4354(map_gobj);
    if (temp_r3_2 == 0) {
        __assert("grpstadium.c", 0x979, "gp");
    }
    if (temp_r3_2->u.stadium.xC4_b1) {
        return false;
    }
    temp_r3_2->u.stadium.xD0 = grDatFiles_801C6478(temp_r3_2->u.stadium.xCC,
                                                   temp_r3_2->u.stadium.xC8);
    return true;
}

inline bool grStadium_801D42B8_dontinline(void)
{
    return grStadium_801D42B8();
}

Ground* grStadium_801D4354(Ground_GObj* gobj)
{
    return gobj->user_data;
}

char* datfiles[] = {
    "GrPs1.dat",
    "GrPs2.dat",
    "GrPs3.dat",
    "GrPs4.dat",
};

static struct VecScalar {
    Vec3 vec;
    float scalar;
} lbl_803E1630[] = {
    {
        { -50, 5, 50 },
        100,
    },
    {
        { 50, 5, 50 },
        28.28,
    },
    {
        { 70, 5, 30 },
        53.85,
    },
    {
        { 70, 5, -30 },
        5,
    },
    {
        { 50, 5, -50 },
        100,
    },
    {
        { -50, 5, -50 },
        28.28,
    },
    {
        { -70, 5, -30 },
        60,
    },
    {
        { -70, 5, 30 },
        28.28,
    },
    {
        { -50, 5, 50 },
        0,
    },
};

void grStadium_801D435C(Ground_GObj* arg0)
{
    struct VecScalar* cur;
    Ground* gp;
    f32 temp_f0;
    f32 temp_f1_2;
    f32 temp_f1_3;
    f32 var_f31;
    int var_r28;
    Vec3 spC;

    gp = arg0->user_data;
    if (gp->u.stadium.xD4 == 0.0F) {
        int i;
        cur = lbl_803E1630;
        for (i = 0; i < ARRAY_SIZE(lbl_803E1630); i++) {
            gp->u.stadium.xD4 += cur++->scalar;
        }
    }
    var_r28 = 0;
    for (var_r28 = 0; var_r28 < 5; var_r28++) {
        u32 var_r4 = 0;
        var_f31 = gp->u.stadium.xD4 * HSD_Randf();

        for (var_r4 = 0; var_f31 > lbl_803E1630[var_r4].scalar && var_r4 < 8;
             var_r4++)
        {
            var_f31 -= lbl_803E1630[var_r4].scalar;
        }
        lbVector_Diff(&lbl_803E1630[var_r4 + 1].vec, &lbl_803E1630[var_r4].vec,
                      &spC);

        temp_f1_2 = var_f31 / lbl_803E1630[var_r4].scalar;
        spC.x *= temp_f1_2;
        spC.y *= temp_f1_2;
        spC.z *= temp_f1_2;
        lbVector_Add(&spC, &lbl_803E1630[var_r4].vec);
        temp_f1_3 = Ground_801C0498();
        spC.x *= temp_f1_3;
        spC.y *= temp_f1_3;
        spC.z *= temp_f1_3;
        grLib_801C96F8(0x7548, 0x1E, &spC);
    }
}

void grStadium_801D4548(Ground_GObj* gobj)
{
    s32 sp6C;
    s32 sp68;
    s32 sp64;
    Ground* temp_r31;
    Ground_GObj* temp_r3_7;
    int temp_r0_3;
    HSD_GObj* temp_r3;
    int temp_r3_4;
    HSD_GObj* temp_r3_5;
    HSD_GObj* temp_r3_6;
    int temp_r3_8;
    int temp_r4_4;
    int temp_r4_8;
    int var_r28;
    int var_r28_2;
    HSD_JObj* temp_r27_2;
    HSD_JObj* temp_r27_3;
    HSD_JObj* temp_r27_5;
    HSD_JObj* temp_r30;
    f32 temp_f29;
    f32 temp_f30;
    f32 temp_f31;
    f32 var_f29;
    f32 var_f30;
    s16 temp_r0_2;
    s32 temp_r0_4;
    s32 temp_r0_5;
    s32 temp_r27_6;
    s32 temp_r27_7;
    s32 temp_r3_10;
    s32 temp_r3_11;
    s32 temp_r3_12;
    s32 temp_r3_13;
    s32 temp_r5_2;
    s32 var_r29;
    s32 var_r3;
    s32 var_r3_10;
    s32 var_r3_11;
    s32 var_r3_12;
    s32 var_r3_13;
    s32 var_r3_2;
    s32 var_r3_3;
    s32 var_r3_4;
    s32 var_r3_5;
    s32 var_r3_6;
    s32 var_r3_7;
    s32 var_r3_8;
    s32 var_r3_9;
    s32 var_r4;
    Ground* temp_r27;
    HSD_JObj* temp_r27_4;
    Ground* temp_r3_2;
    Ground* temp_r3_9;
    Ground* temp_r6;

    temp_r31 = GET_GROUND(gobj);
    temp_f31 = Ground_801C0498();
    if (gm_8018841C() != 0) {
        return;
    }

    if (Stage_80225194() == 0xF0) {
        temp_r3 = Ground_801C2BA4(PsType_Display);
        if (temp_r3 != NULL) {
            temp_r3_2 = GET_GROUND(temp_r3);
            if (temp_r3_2 != NULL) {
                if (temp_r3_2->u.display.xF4 != NULL) {
                    temp_r3_2->u.display.xF4->x8 = false;
                }
            }
        }
        return;
    }

    switch (temp_r31->u.stadium.xDC) {
    case 0:
        temp_r3_4 = temp_r31->u.stadium.xD8;
        temp_r31->u.stadium.xD8 = temp_r3_4 - 1;
        if (temp_r3_4 < 0) {
            if (temp_r31->u.stadium.xDE == 5) {
                int sp60[] = { 3, 4, 6, 9 };
                do {
                    var_r4 = sp60[HSD_Randi(ARRAY_SIZE(sp60))];
                } while (temp_r31->u.stadium.xE2 == var_r4);
            } else {
                var_r4 = 5;
            }
            temp_r31->u.stadium.xE2 = temp_r31->u.stadium.xE0;
            temp_r31->u.stadium.xE0 = temp_r31->u.stadium.xDE;
            temp_r31->u.stadium.xDE = var_r4;

            if (var_r4 == 5) { // default
                temp_r31->u.stadium.xDC = 2;
                return;
            } else if (var_r4 == 3) { // fire
                var_r29 = 0;
            } else if (var_r4 == 4) { // grass
                var_r29 = 1;
            } else if (var_r4 == 9) { // water
                var_r29 = 2;
            } else if (var_r4 == 6) { // rock
                var_r29 = 3;
            } else {
                __assert("grpstadium.c", 0xA44, "0");
            }
            grAnime_801C65B0(temp_r31->u.stadium.xD0);
            temp_r31->u.stadium.xD0 = NULL;
            temp_r3_5 = Ground_801C2BA4(2);
            if (temp_r3_5 == NULL) {
                __assert("grpstadium.c", 0x99A, "map_gobj");
            }
            temp_r27 = GET_GROUND(temp_r3_5);
            if (temp_r27 == NULL) {
                __assert("grpstadium.c", 0x99B, "gp");
            }
            temp_r27->u.stadium.xC4_b1 = true;
            lbFile_80016580(datfiles[var_r29], (u32) temp_r27->u.stadium.xCC,
                            (void*) &temp_r27->u.stadium.xC8, fn_801D4220,
                            NULL);
            temp_r31->u.stadium.xDC = 1;
            return;
        }
        break;
    case 1:
        if (grStadium_801D42B8_dontinline()) {
            temp_r31->u.stadium.xDC = 2;
            return;
        }
        break;
    case 2:
        temp_r31->u.display.xD8 = NULL;
        temp_r3_6 = Ground_801C2BA4(1);
        if (temp_r3_6 != NULL) {
            temp_r0_2 = temp_r31->u.stadium.xDE;

            var_r29 = temp_r0_2;
            if (var_r29 == 3) {
                var_r29 = 3;
            } else if (var_r29 == 4) {
                var_r29 = 4;
            } else if (var_r29 == 9) {
                var_r29 = 5;
            } else if (var_r29 == 6) {
                var_r29 = 6;
            } else if (var_r29 == 5) {
                var_r29 = 2;
            } else {
                __assert("grpstadium.c", 0xA44, "0");
            }

            grStadium_801D2528(temp_r3_6, var_r29, 0);
        }
        temp_r31->u.stadium.xDC = 3;
        return;
    case 3:
        if (++temp_r31->u.stadium.xD8 > yaku->x10) {
            temp_r6 = GET_GROUND(temp_r31->u.stadium.xE4);
            temp_r6->u.stadium.xC4_b1 = true;
            temp_r31->u.stadium.xDC = 4;
            temp_r31->u.stadium.xD8 = 0;
            Ground_801C53EC(0x75300);
            Ground_801C53EC(0x75301);
            return;
        }
        break;
    case 4:
        temp_r27_2 = GET_JOBJ(temp_r31->u.stadium.xE4);
        temp_f29 = -((temp_f31 * (0.95f / yaku->x14)) -
                     HSD_JObjGetScaleY(temp_r27_2));
        temp_f30 = 0.05f * temp_f31;
        if (temp_f29 > temp_f30) {
            HSD_JObjSetScaleY(temp_r27_2, temp_f29);
        } else {
            HSD_JObjSetScaleY(temp_r27_2, 0.05F);
            temp_r4_4 = temp_r31->u.stadium.xD8;
            temp_r31->u.stadium.xD8 = temp_r4_4 + 1;
            if (temp_r4_4 > yaku->x18) {
                grAnime_801C7A04(temp_r31->u.stadium.xE4, 0, 7, 0.0f);
                temp_r3_7 = grStadium_801D10F8(temp_r31->u.stadium.xDE);
                temp_r27_3 = GET_JOBJ(temp_r3_7);
                HSD_JObjSetScaleY(temp_r27_3, temp_f30);
                HSD_JObjSetTranslateY(temp_r27_3, -10.0F);
                temp_r31->u.stadium.xE8 = temp_r3_7;
                temp_r31->u.stadium.xD8 = 0;
                temp_r31->u.stadium.xDC = 5;
                mpLib_80057528(0x55);
                mpLib_80057528(0x6F);
            }
        }
        grStadium_801D435C(gobj);
        Camera_80030E44(1, NULL);
        return;
    case 5:
        temp_r0_3 = ++temp_r31->u.stadium.xD8;
        if (temp_r0_3 <= yaku->x14) {
            float tmp;
            temp_r30 = temp_r31->u.stadium.xE8->hsd_obj;
            tmp = 0.95f * temp_r0_3 / yaku->x14 + 0.05F;
            HSD_JObjSetScaleY(temp_r30, tmp * temp_f31);
            temp_r4_8 = temp_r31->u.stadium.xD8;
            temp_r0_4 = yaku->x14 / 2;
            if (temp_r4_8 < temp_r0_4) {
                var_f29 =
                    -10.0f * temp_f31 * (1.0f - ((f32) temp_r4_8 / temp_r0_4));
            } else {
                var_f29 = 0.0f;
            }
            HSD_JObjSetTranslateY(temp_r30, var_f29);
            temp_r5_2 = yaku->x14;
            temp_r3_8 = temp_r31->u.stadium.xD8;
            temp_r27_4 = temp_r31->u.stadium.xE4->hsd_obj;
            temp_r0_5 = temp_r5_2 / 2;
            if (temp_r3_8 > temp_r0_5) {
                var_f30 = -10.0f * temp_f31 *
                          (1.0f - ((f32) (temp_r5_2 - temp_r3_8) /
                                   (temp_r5_2 - temp_r0_5)));
            } else {
                var_f30 = 0.0f;
            }
            HSD_JObjSetTranslateY(temp_r27_4, var_f30);
        } else {
            temp_r27_5 = temp_r31->u.stadium.xE8->hsd_obj;
            HSD_JObjSetScaleY(temp_r27_5, temp_f31);
            HSD_JObjSetTranslateY(temp_r27_5, 0.0F);
            temp_r31->u.stadium.xDC = 6;
            Ground_801C4A08(temp_r31->u.stadium.xE4);
            temp_r31->u.stadium.xE4 = temp_r31->u.stadium.xE8;
            temp_r31->u.stadium.xE8 = NULL;
        }
        grStadium_801D435C(gobj);
        Camera_80030E44(1, NULL);
        return;
    case 6:
        temp_r3_9 = temp_r31->u.stadium.xE4->user_data;
        temp_r3_9->u.stadium.xC4_b0 = true;
        mpLib_80058560();
        if (temp_r31->u.stadium.xDE == 5) {
            var_r28 = yaku->x4;
            temp_r27_6 = yaku->x0;
            if (var_r28 > temp_r27_6) {
                temp_r3_10 = var_r28 - temp_r27_6;
                if (temp_r3_10 != 0) {
                    var_r3_10 = HSD_Randi(temp_r3_10);
                } else {
                    var_r3_10 = 0;
                }
                var_r28 = temp_r27_6 + var_r3_10;
            } else if (var_r28 < temp_r27_6) {
                temp_r3_11 = temp_r27_6 - var_r28;
                if (temp_r3_11 != 0) {
                    var_r3_11 = HSD_Randi(temp_r3_11);
                } else {
                    var_r3_11 = 0;
                }
                var_r28 += var_r3_11;
            }
            temp_r31->u.stadium.xD8 = var_r28;
            grAnime_801C65B0((void*) temp_r31->u.stadium.xCC);
            mpLib_800575B0(0x55);
            mpLib_800575B0(0x6F);
        } else {
            var_r28_2 = yaku->xC;
            temp_r27_7 = yaku->x8;
            if (var_r28_2 > temp_r27_7) {
                temp_r3_12 = var_r28_2 - temp_r27_7;
                if (temp_r3_12 != 0) {
                    var_r3_12 = HSD_Randi(temp_r3_12);
                } else {
                    var_r3_12 = 0;
                }
                var_r28_2 = temp_r27_7 + var_r3_12;
            } else if (var_r28_2 < temp_r27_7) {
                temp_r3_13 = temp_r27_7 - var_r28_2;
                if (temp_r3_13 != 0) {
                    var_r3_13 = HSD_Randi(temp_r3_13);
                } else {
                    var_r3_13 = 0;
                }
                var_r28_2 += var_r3_13;
            }
            temp_r31->u.stadium.xD8 = var_r28_2;
        }
        temp_r31->u.stadium.xDC = 0;
        break;
    }
}

/**
 * Check if the display is focused on a specific player
 */
bool grStadium_801D4FF8(int pl_slot)
{
    if (stage_info.internal_stage_id == PSTADIUM) {
        Ground_GObj* gobj = Ground_801C2BA4(PsType_Display);
        if (gobj != NULL) {
            Ground* gp = GET_GROUND(gobj);
            if (gp != NULL && gp->u.display.xE4 == 8 &&
                gp->u.display.xEE == pl_slot)
            {
                return true;
            }
        }
    }
    return false;
}

void fn_801D5074(Ground_GObj* gobj, int arg1)
{
    grStadium_801D1EF8(gobj);
    grDisplay_801C5DB0(gobj, arg1);
}

DynamicsDesc* grStadium_801D50B8(enum_t unused)
{
    return NULL;
}

bool grStadium_801D50C0(Vec3* arg0, int arg1, HSD_JObj* jobj)
{
    Vec3 sp14;
    lb_8000B1CC(jobj, NULL, &sp14);
    if (arg0->y + 1.0F > sp14.y) {
        return true;
    } else {
        return false;
    }
}

void grStadium_801D511C(void)
{
    int size;

    size = GXGetTexBufferSize(0xFA, 0xA0, 4, 0, 0);
    lbDvd_80017740(0, 0x7D2, 4, 4, OSRoundUp32B(size), 0, 7, 0x10, 0);

    size = GXGetTexBufferSize(0x280, 0x196, 4, 0, 0);
    lbDvd_80017740(0, 0x7D3, 4, 4, OSRoundUp32B(size), 0, 7, 0x10, 0);

    size = GXGetTexBufferSize(0x7C, 0x50, 4, 0, 0);
    lbDvd_80017740(0, 0x7D4, 4, 4, OSRoundUp32B(size), 0, 7, 0x10, 0);

    lbDvd_80017740(0, 0x7D5, 4, 4, 0x50000, 0, 7, 0x10, 0);
}
