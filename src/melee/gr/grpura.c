#include "gr/grpura.h"

#include <platform.h>

#include "baselib/gobjgxlink.h"
#include "baselib/gobjproc.h"
#include "baselib/random.h"
#include "cm/camera.h"
#include "gr/grdisplay.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "gr/stage.h"
#include "gr/types.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "mp/mplib.h"

#include <dolphin/mtx.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>
#include <baselib/tobj.h>
#include <sysdolphin/baselib/dobj.h>

StageCallbacks grPu_803E6800[] = {
    { grPura_80211EF0, grPura_80211F1C, grPura_80211F24, grPura_80211F28, 0 },
    { grPura_80212024, grPura_802120D8, grPura_802120E0, grPura_8021228C, 0 },
    { grPura_80212290, grPura_80212314, grPura_8021231C, grPura_802125EC, 0 },
    { grPura_80212290, grPura_80212314, grPura_8021231C, grPura_802125EC, 0 },
    { grPura_80211F68, grPura_80211FD0, grPura_80211FD8, grPura_80212020,
      0x40000000 },
    { grPura_80212290, grPura_80212314, grPura_8021231C, grPura_802125EC, 0 },
    { grPura_80212290, grPura_80212314, grPura_8021231C, grPura_802125EC, 0 },
    { grPura_80212290, grPura_80212314, grPura_8021231C, grPura_802125EC, 0 },
    { grPura_80212290, grPura_80212314, grPura_8021231C, grPura_802125EC, 0 },
    { grPura_80212290, grPura_80212314, grPura_8021231C, grPura_802125EC, 0 },
    { grPura_80212290, grPura_80212314, grPura_8021231C, grPura_802125EC, 0 },
    { grPura_80212290, grPura_80212314, grPura_8021231C, grPura_802125EC, 0 },
    { grPura_80212290, grPura_80212314, grPura_8021231C, grPura_802125EC, 0 },
    { grPura_80212290, grPura_80212314, grPura_8021231C, grPura_802125EC, 0 },
    { grPura_80212290, grPura_80212314, grPura_8021231C, grPura_802125EC, 0 },
    { grPura_80212290, grPura_80212314, grPura_8021231C, grPura_802125EC, 0 },
    { grPura_80212290, grPura_80212314, grPura_8021231C, grPura_802125EC, 0 },
    { grPura_80212290, grPura_80212314, grPura_8021231C, grPura_802125EC, 0 },
    { grPura_80212290, grPura_80212314, grPura_8021231C, grPura_802125EC, 0 },
    { grPura_80212290, grPura_80212314, grPura_8021231C, grPura_802125EC, 0 },
    { grPura_80212290, grPura_80212314, grPura_8021231C, grPura_802125EC, 0 },
    { grPura_80212290, grPura_80212314, grPura_8021231C, grPura_802125EC, 0 },
    { grPura_80212290, grPura_80212314, grPura_8021231C, grPura_802125EC, 0 },
    { grPura_80212290, grPura_80212314, grPura_8021231C, grPura_802125EC, 0 },
    { grPura_80212290, grPura_80212314, grPura_8021231C, grPura_802125EC, 0 },
    { grPura_80212290, grPura_80212314, grPura_8021231C, grPura_802125EC, 0 },
    { grPura_80212290, grPura_80212314, grPura_8021231C, grPura_802125EC, 0 },
    { grPura_80211F2C, grPura_80211F58, grPura_80211F60, grPura_80211F64,
      0x80000000 }
};

StageData grPu_803E6A3C = { 0x11,
                            grPu_803E6800,
                            "/GrPu.dat",
                            grPura_80211D00,
                            grPura_80211CFC,
                            grPura_80211DD8,
                            grPura_80211DDC,
                            grPura_80211E00,
                            grPura_802130C0,
                            grPura_802130C8,
                            1,
                            0,
                            0 };

GXColor grPu_803E6AA0[] = {
    { 0x00, 0x00, 0x00, 0xFF }, { 0x00, 0x00, 0x50, 0xFF },
    { 0x80, 0x80, 0x00, 0xFF }, { 0xFF, 0xFF, 0x00, 0xFF },
    { 0x3F, 0x80, 0x00, 0x00 }, { 0x00, 0x00, 0x00, 0x02 },
    { 0x00, 0x00, 0x00, 0x01 }, { 0x3F, 0x80, 0x00, 0x00 },
    { 0x00, 0x00, 0x00, 0x03 }, { 0x00, 0x00, 0x00, 0x02 },
    { 0x3F, 0x80, 0x00, 0x00 },
};

void* grPu_803E6E20;

struct HSD_ImageDesc grPu_803E7620 = { &grPu_803E6E20, 32, 32, 4, 0, 0, 0 };

void grPura_80211CFC(bool num) {}

/// #grPura_80211D00

const f32 grPu_804DBA58 = 0.8;
const f32 grPu_804DBA5C = 3600.0;
const f32 grPu_804DBA70 = 0.0;
const f32 grPu_804DBA74 = 2.0;
const f32 grPu_804DBA78 = 30.0;
const f32 grPu_804DBA7C = -30.0;

void grPura_80211D00(void)
{
    HSD_GObj* r3;

    Vec3 cam_offset;
    f32 fVar1;

    Ground_801C49F8();
    stage_info.unk8C.b4 = 0;
    stage_info.unk8C.b5 = 1;
    grPura_80211E08(0);
    grPura_80211E08(1);
    grPura_80211E08(4);
    // r3 = grIzumi_801CBCE8(3);
    // grAnime_801C8780(r3, 3, 0, 0.0f, 1.0f);
    Ground_801C39C0();
    Ground_801C3BB4();
    Stage_UnkSetVec3TCam_Offset(&cam_offset);
    fVar1 = Stage_GetCamBoundsTopOffset();
    Ground_801C3880(grPu_804DBA58 * (fVar1 - cam_offset.y));
    fVar1 = Stage_GetCamBoundsBottomOffset();
    Ground_801C3890(grPu_804DBA58 * (fVar1 - cam_offset.y));
    fVar1 = Stage_GetCamBoundsLeftOffset();
    Ground_801C38A0(grPu_804DBA58 * (fVar1 - cam_offset.x));
    fVar1 = Stage_GetCamBoundsRightOffset();
    Ground_801C38AC(grPu_804DBA58 * ((fVar1 - cam_offset.x)));
}

void grPura_80211DD8(void) {}

/// #grPura_80211DDC
void grPura_80211DDC(void)
{
    grZakoGenerator_801CAE04(0);
}

bool grPura_80211E00(void)
{
    return false;
}

/// #grPura_80211E08
HSD_GObj* grPura_80211E08(int gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grPu_803E6800[gobj_id];

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
//        OSReport("%s:%d: couldn t get gobj(id=%d)\n", __FILE__, __LINE__, gobj_id);
        // clang-format on
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grpura.c", 241,
                 gobj_id);
    }

    return gobj;
}

/// #grPura_80211EF0
void grPura_80211EF0(Ground_GObj* arg0)
{
    Ground* gp = arg0->user_data;
    grAnime_801C8138(arg0, gp->map_id, 0);
}

bool grPura_80211F1C(Ground_GObj* arg0)
{
    return false;
}

void grPura_80211F24(Ground_GObj* arg0) {}

void grPura_80211F28(Ground_GObj* arg0) {}

/// #grPura_80211F2C
void grPura_80211F2C(Ground_GObj* arg0)
{
    Ground* gp = arg0->user_data;
    grAnime_801C8138(arg0, gp->map_id, 0);
}

bool grPura_80211F58(Ground_GObj* arg0)
{
    return false;
}

void grPura_80211F60(Ground_GObj* arg0) {}

void grPura_80211F64(Ground_GObj* arg0) {}

/// #grPura_80211F68
void grPura_80211F68(Ground_GObj* arg0)
{
    Ground* gp = arg0->user_data;
    Ground_801C2ED0(arg0->hsd_obj, gp->map_id);
    grAnime_801C8138(arg0, gp->map_id, 0);
    grPura_80212CD4(arg0);
    grPura_802125F0(arg0);
    grPura_80212FC0(arg0);
}

bool grPura_80211FD0(Ground_GObj* arg0)
{
    return false;
}

void grPura_80211FD8(Ground_GObj* arg0)
{
    grPura_80212EF4(arg0);
    Ground_801C2FE0(arg0);
    // grPura_80213030(arg0);
    mpLib_80055E24(0x18);
    lb_800115F4();
}

void grPura_80212020(Ground_GObj* arg0) {}

/// #grPura_80212024
void grPura_80212024(Ground_GObj* arg0)
{
    s16 uVar1;
    Ground* gp = GET_GROUND(arg0);
    grAnime_801C8138(arg0, gp->map_id, 0);
    gp->gv.pura.xC4 = HSD_Randi(2);
    do {
        uVar1 = HSD_Randi(4);
        gp->gv.pura.xC6 = uVar1;
    } while (gp->gv.pura.xC4 == uVar1);
    Ground_801C205C(&grPu_803E6AA0[gp->gv.pura.xC4]);
    Camera_SetBackgroundColor(grPu_803E6AA0[gp->gv.pura.xC4].r,
                              grPu_803E6AA0[gp->gv.pura.xC4].g,
                              grPu_803E6AA0[gp->gv.pura.xC4].b);
    gp->gv.pura.xC8 = 0;
}

bool grPura_802120D8(Ground_GObj* arg0)
{
    return false;
}

/// #grPura_802120E0

void grPura_8021228C(Ground_GObj* arg0) {}

/// #grPura_80212290
void grPura_80212290(Ground_GObj* arg0)
{
    Ground* gp = GET_GROUND(arg0);
    HSD_JObj* jobj = arg0->hsd_obj;
    HSD_ImageDesc* image = grPu_803E6E20;
    HSD_MObjSetToonTextureImage(image);
    lb_80011C18(jobj, 0x1000);
    grPura_80213250(jobj);
    HSD_MObjSetToonTextureImage(0);
    grAnime_801C8138(arg0, gp->map_id, 0);
}

bool grPura_80212314(Ground_GObj* arg0)
{
    return false;
}

/// #grPura_8021231C
void grPura_8021231C(Ground_GObj* arg0)
{
    Ground* gp = GET_GROUND(arg0);
    HSD_JObj* jobj = arg0->hsd_obj;
    Vec3* vec = { 0 };
    Quaternion* quat = { 0 };
    HSD_JObjGetTranslation2(gp->gv.pura2.xC8, vec);
    HSD_JObjSetTranslate(jobj, vec);
    HSD_JObjGetRotation(gp->gv.pura2.xC8, quat);
    HSD_JObjSetRotation(jobj, quat);
    HSD_JObjGetScale(gp->gv.pura2.xC8, vec);
    HSD_JObjSetScale(jobj, vec);

    // HSD_JObjGetFlags(jobj);
    if ((HSD_JObjGetFlags(gp->gv.pura2.xC8) & 0x10) &&
        ((HSD_JObjGetFlags(jobj) & 0x10) == NULL))
    {
        HSD_JObjSetFlagsAll(jobj, 0x10);
    } else if (((HSD_JObjGetFlags(gp->gv.pura2.xC8) & 0x10) == NULL) &&
               (HSD_JObjGetFlags(jobj) & 0x10))
    {
        HSD_JObjClearFlagsAll(jobj, 0x10);
    }
}

void grPura_802125EC(Ground_GObj* arg0) {}

/// #grPura_802125F0
void grPura_802125F0(HSD_GObj* arg0)
{
    struct _GXColor thingy = grPu_803E6AA0[5];
    float dVar1 = grPu_804DBA70;
    float dVar2 = grPu_804DBA74;
    int uVar3 = 0;
    int uVar5;
    int uVar6 = 0;
    HSD_GObj* gobj;
    Ground* gp;
    HSD_JObj* jobj;
    do {
        gobj = grPura_80211E08(1);

        if (gobj == NULL) {
            __assert("grpura.c", 0x291, "gobj");
        }
        gp = GET_GROUND(gobj);
        if (gp == NULL) {
            __assert("grpura.c", 0x291, "gp");
        }
        // uVar3 = Ground_801C33C0(4,gp->gv.pura2.xC4);
        gp->gv.pura.xC8 = Ground_801C3FA4(arg0, gp->gv.pura.xC4);
        // uVar3 = Ground_801C3FA4(arg0,uVar3);

        HSD_JObjSetTranslateX(arg0->hsd_obj,
                              HSD_JObjGetTranslationX(gp->gv.pura.xC8));
        HSD_JObjSetTranslateY(arg0->hsd_obj,
                              HSD_JObjGetTranslationY(gp->gv.pura.xC8));
        HSD_JObjSetTranslateZ(arg0->hsd_obj,
                              HSD_JObjGetTranslationZ(gp->gv.pura.xC8));

        if (HSD_JObjGetFlags(gp->gv.pura.xC8) & 0x10) {
            HSD_JObjSetFlagsAll(arg0->hsd_obj, 0x10);
        }
        jobj = gobj->hsd_obj;
        // if (jobj->child) {

        //}
        // everything after this point is very much not done
        HSD_JObjSetTranslateX(arg0->hsd_obj,
                              HSD_JObjGetTranslationX(jobj->child));
        HSD_JObjSetTranslateY(arg0->hsd_obj,
                              HSD_JObjGetTranslationY(jobj->child));
        HSD_JObjSetTranslateZ(arg0->hsd_obj,
                              HSD_JObjGetTranslationZ(jobj->child));

        HSD_JObjSetTranslateX(
            arg0->hsd_obj,
            HSD_JObjGetTranslationX(Ground_801C3FA4(arg0, uVar3)));
        HSD_JObjSetTranslateY(
            arg0->hsd_obj,
            HSD_JObjGetTranslationY(Ground_801C3FA4(arg0, uVar3)));
        HSD_JObjSetTranslateZ(
            arg0->hsd_obj,
            HSD_JObjGetTranslationZ(Ground_801C3FA4(arg0, uVar3)));
        uVar6++;
    } while (uVar6 < 27);
}

/// #grPura_80212CD4

/// #grPura_80212EF4
void grPura_80212EF4(HSD_GObj* arg0)
{
    Ground* gp = GET_GROUND(arg0);
    // HSD_JObjGetFlags();
}

/// #grPura_80212FC0

void grPura_80213030(HSD_JObj* arg0, Vec3* arg1, Vec3* arg2)
{
    u32 uVar1 = 0;
    do {
        lb_8000B1CC(arg0, arg1, arg2);
        uVar1++;
    } while (uVar1 < 42);
    mpJointUpdateBounding(0);
    mpJointUpdateBounding(9);
    mpJointUpdateBounding(24);
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

/// #fn_802130D0
void fn_802130D0(HSD_GObj* arg0, int arg1)
{
    HSD_ImageDesc* image = grPu_803E6E20;
    HSD_MObjSetToonTextureImage(image);
    grDisplay_801C5DB0(arg0, arg1);
    HSD_MObjSetToonTextureImage(0);
}

/// #grPura_80213128

/// #grPura_80213224
void grPura_80213224(HSD_DObj* dobj)
{
    if (dobj != 0) {
        HSD_MObjCompileTev(dobj->mobj);
    }
}

/// #grPura_80213250
void grPura_80213250(HSD_JObj* arg0)
{
    HSD_JObj* jobj = arg0->child;
    HSD_DObj* dobj; // = arg0->child;
    if (jobj) {
        if (jobj->child) {
            grPura_80213250(jobj->child);
        }
        if (jobj->next) {
            grPura_80213250(jobj->next);
        }
        dobj = jobj->u.dobj;
        if (jobj->u.ptcl) {
            grPura_80213128();
        }
        // for(int i = 0;ptcl->next[];i++)
        if (dobj != 0) {
            HSD_MObjCompileTev(dobj->mobj);
        }
    }
    jobj = arg0->next;
    if (jobj) {
        if (jobj->child) {
            grPura_80213250(jobj->child);
        }
        if (jobj->next) {
            grPura_80213250(jobj->next);
        }
        dobj = jobj->u.dobj;
        if (jobj->u.ptcl) {
            grPura_80213128();
        }
        if (dobj != 0) {
            HSD_MObjCompileTev(dobj->mobj);
        }
    }
    dobj = arg0->u.dobj;
    if (dobj) {
        if (jobj->u.ptcl) {
            grPura_80213128();
        }
        if (jobj->next) {
            grPura_80213250(jobj->next);
        }
        dobj = jobj->u.dobj;
        if (dobj != 0) {
            HSD_MObjCompileTev(dobj->mobj);
        }
        if (dobj != 0) {
            HSD_MObjCompileTev(dobj->mobj);
        }
    }
    // HSD_MObjCompileTev();
    // HSD_MObjCompileTev();
    // HSD_MObjCompileTev();
}
