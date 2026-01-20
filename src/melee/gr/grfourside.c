#include "grfourside.h"

#include "m2c_macros.h"
#include "placeholder.h"

#include <platform.h>

#include "gr/granime.h"
#include "gr/grdisplay.h"
#include "gr/grlib.h"
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
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjproc.h>
#include <baselib/gobjuserdata.h>
#include <baselib/jobj.h>
#include <baselib/random.h>

static struct {
    /* 00 */ int heli_wait;
    /* 04 */ int heli_wait_add;
    /* 08 */ int heli_stay_time;
    /* 0C */ int crane_wait;
    /* 10 */ int crane_wait_add;
    /* 14 */ int crane_iron_wait;
    /* 18 */ int crane_iron_wait_add;
    /* 1C */ float crane_iron_up_min;
    /* 20 */ float crane_iron_up_max;
    /* 24 */ float crane_iron_down_min;
    /* 28 */ float crane_iron_down_max;
    /* 2C */ float crane_iron_spd;
    /* 30 */ float crane_iron_stop_acl;
    /* 34 */ int ufo_wait;
    /* 38 */ float ufo_cs_offs;
    /* 3C */ int ufo_stay_time;
    /* 40 */ int ufo_stay_time_add;
    /* 44 */ u16 ufo_challenge;
    /* 46 */ u16 x46;
    /* 48 */ u16 x48;
}* grFs_804D69D8;

S16Vec3 grFs_803E3CE8[] = {
    {3,1,7},
    {4,5,1},
    {0,6,10}
};

StageCallbacks grFs_803E3CFC[] = {
    { grFourside_801F2EBC, grFourside_801F2EE8,
      grFourside_801F2EF0, grFourside_801F2EF4, 0 },
    { grFourside_801F3154, grFourside_801F326C,
      grFourside_801F3274, grFourside_801F37F8, 0 },
    { grFourside_801F2EF8, grFourside_801F2F24,
      grFourside_801F2F2C, grFourside_801F2F30, 0 },
    { grFourside_801F3C40, grFourside_801F3CC0,
      grFourside_801F3CC8, grFourside_801F3F0C, 0 },
    { grFourside_801F30F0, grFourside_801F3144,
      grFourside_801F314C, grFourside_801F3150, 0 },
    { grFourside_801F37FC, grFourside_801F388C,
      grFourside_801F3894, grFourside_801F3B6C, 0 },
    { grFourside_801F2F34, grFourside_801F3070,
      grFourside_801F3078, grFourside_801F309C, 0xc0000000 }
};

StageData grFs_803E3D94 = {
    21,
    grFs_803E3CFC,
    "/GrFs.dat",
    grFourside_801F2D10,
    grFourside_801F2D0C,
    grFourside_801F2DA0,
    grFourside_801F2DA4,
    grFourside_801F2DC8,
    grFourside_801F41E0,
    grFourside_801F41E8,
    1,
    grFs_803E3CE8,
    3,
};

void grFourside_801F2D0C(bool arg) {}

void grFourside_801F2D10(void)
{
    grFs_804D69D8 = Ground_801C49F8();
    stage_info.unk8C.b4 = false;
    stage_info.unk8C.b5 = true;
    grFourside_801F2DD0(0);
    grFourside_801F2DD0(4);
    grFourside_801F2DD0(6);
    grFourside_801F2DD0(2);
    grFourside_801F2DD0(1);
    grFourside_801F2DD0(3);
    grFourside_801F2DD0(5);
    Ground_801C39C0();
    Ground_801C3BB4();
}

void grFourside_801F2DA0(void) {}

void grFourside_801F2DA4(void)
{
    grZakoGenerator_801CAE04(0);
}

bool grFourside_801F2DC8(void)
{
    return false;
}

/// #grFourside_801F2DD0
HSD_GObj* grFourside_801F2DD0(int gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grFs_803E3CFC[gobj_id];

    gobj = Ground_801C14D0(gobj_id);

    if (gobj != NULL) {
        Ground* gp = GET_GROUND(gobj);
        gp->x8_callback = 0;
        gp->xC_callback = 0;
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
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grfourside.c", 215,
                 gobj_id);
    }

    return gobj;
}

void grFourside_801F2EBC(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grFourside_801F2EE8(Ground_GObj* arg)
{
    return false;
}

void grFourside_801F2EF0(Ground_GObj* arg) {}

void grFourside_801F2EF4(Ground_GObj* arg) {}

void grFourside_801F2EF8(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grFourside_801F2F24(Ground_GObj* arg)
{
    return false;
}

void grFourside_801F2F2C(Ground_GObj* arg) {}

void grFourside_801F2F30(Ground_GObj* arg) {}

/// #grFourside_801F2F34
void grFourside_801F2F34(Ground_GObj* gobj) {
    HSD_GObj* pHVar1;
    Ground* gp = GET_GROUND(gobj);
    Ground_801C2ED0(gobj->hsd_obj, gp->map_id);
    grAnime_801C8138(gobj,gp->map_id,0);
    Ground_801C4E70(Ground_801C3FA4(gobj,7),Ground_801C3FA4(gobj,4),Ground_801C3FA4(gobj,6),Ground_801C3FA4(gobj,5),Ground_801C3FA4(gobj,9),Ground_801C3FA4(gobj,8));
    gobj->render_cb = fn_801F3F74;
    gp->gv.fourside.x0 = Ground_801C3FA4(gobj,2);
    gp->gv.fourside.x4 = Ground_801C3FA4(gobj,3);
    pHVar1 = Ground_801C2BA4(4);
    if (pHVar1) {
        gp->gv.fourside.x8 = pHVar1->hsd_obj;
    } else {
        gp->gv.fourside.x8 = NULL;
    }
    mpJointSetCb1(0,gp,grFourside_801F30A0);
    gp->x10_flags.b5 = 1;
    gp->x11_flags.b012 = 1;
}

bool grFourside_801F3070(Ground_GObj* arg)
{
    return false;
}

void grFourside_801F3078(Ground_GObj* gobj)
{
    Ground_801C2FE0(gobj);
    lb_800115F4();
}

void grFourside_801F309C(Ground_GObj* arg) {}

void grFourside_801F30A0(Ground* unusedr3, s32 unusedr4, CollData* r5, s32 unusedr6, mpLib_GroundEnum unusedr7, float unusedf1)
{
    HSD_GObj* gobj;
    Ground* gp;
    s32 val;
    //PAD_STACK(20);

    gobj = Ground_801C2BA4(5);
    val = M2C_FIELD(r5, u8*, 0x34);
    gp = GET_GROUND(gobj);
    val = ((val >> 3) & 0xF);
    if (val == 1) {
        gp->gv.fourside2.x8 += 1;
    }
}

void grFourside_801F30F0(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    PAD_STACK(4);

    gp->x10_flags.b2 = 0;
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->x11_flags.b012 = 2;
}

bool grFourside_801F3144(Ground_GObj* arg)
{
    return false;
}

void grFourside_801F314C(Ground_GObj* arg) {}

void grFourside_801F3150(Ground_GObj* arg) {}

/// #grFourside_801F3154
void grFourside_801F3154(Ground_GObj* gobj) {
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = gobj->hsd_obj;
    HSD_JObj* crane_iron = Ground_801C3FA4(gobj,4);
    Ground_801C2ED0(jobj,gp->map_id);
    grAnime_801C7FF8(gobj,0,7,0,0.0f,0.0f);
    gp->gv.foursideCrane.x1.b0 = 0;
    gp->gv.foursideCrane.x4 =
        grFs_804D69D8->crane_wait +
        (grFs_804D69D8->crane_wait_add != 0 ? HSD_Randi(grFs_804D69D8->crane_wait_add) : 0);
    gp->gv.foursideCrane.x8 = HSD_JObjGetTranslationY(crane_iron);
    gp->gv.foursideCrane.x8 = gp->gv.foursideCrane.x8 - 10.0F;
    gp->gv.foursideCrane.xC = gp->gv.foursideCrane.x10 = gp->gv.foursideCrane.x8;
    gp->gv.foursideCrane.x0 = 0;
    gp->x10_flags.b5 = 1;
    gp->x11_flags.b012 = 1;
}

bool grFourside_801F326C(Ground_GObj* arg)
{
    return false;
}

/// #grFourside_801F3274
void grFourside_801F3274(Ground_GObj* gobj) {
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = gobj->hsd_obj;
    HSD_JObj* crane_iron = Ground_801C3FA4(gobj,4);
    float fVar1;
    float temp_fVar1;
    //Ground_801C2ED0(jobj,gp->map_id);
    //grAnime_801C7FF8(gobj,0,7,0,0.0f,0.0f);
    switch (gp->gv.foursideCrane.x0) {
        case 0:
            if (gp->gv.foursideCrane.x4 <= 0) {
                if (gp->gv.foursideCrane.x1.b0 == 0u) {
                    grAnime_801C7B24(gobj,0,7,0.0f);
                    grAnime_801C7A04(gobj,0,7,1.0f);
                    gp->gv.foursideCrane.x4 = 0;
                    gp->gv.foursideCrane.x0 = 1;
                } else {
                    grAnime_801C7B24(gobj,0,7,400.0f);
                    grAnime_801C7A04(gobj,0,7,1.0f);
                    gp->gv.foursideCrane.x4 = 0;
                    gp->gv.foursideCrane.x0 = 2;
                }
            } else {
                gp->gv.foursideCrane.x4 -= 1;
            }
            break;
        case 1:
            if (gp->gv.foursideCrane.x4 >= 300) {
                grAnime_801C7A04(gobj,0,7,0.0);
                gp->gv.foursideCrane.x1.b0 = 1;
                gp->gv.foursideCrane.x0 = 3;
            } else {
                gp->gv.foursideCrane.x4 += 1;
            }
            break;
        case 2:
            if (gp->gv.foursideCrane.x4 >= 300) {
                grAnime_801C7A04(gobj,0,7,0.0);
                gp->gv.foursideCrane.x1.b0 = 0;
                gp->gv.foursideCrane.x0 = 3;
            } else {
                gp->gv.foursideCrane.x4 += 1;
            }
            break;
        case 3:
            gp->gv.foursideCrane.x4 =
                grFs_804D69D8->crane_iron_wait +
                (grFs_804D69D8->crane_iron_wait_add != 0 ? HSD_Randi(grFs_804D69D8->crane_iron_wait_add) : 0);
            gp->gv.foursideCrane.x0 = 4;
            break;
        case 4:
            if (gp->gv.foursideCrane.x4 <= 0) {
                gp->gv.foursideCrane.x10 = gp->gv.foursideCrane.x8;
                if (gp->gv.foursideCrane.xC > gp->gv.foursideCrane.x8) {
                    fVar1 = grFs_804D69D8->crane_iron_down_max - grFs_804D69D8->crane_iron_down_min;
                    if (fVar1 < 0.0f) {
                        fVar1 = -fVar1;
                    }
                    temp_fVar1 = grFs_804D69D8->crane_iron_down_min;
                    gp->gv.foursideCrane.x10 =
                        gp->gv.foursideCrane.x10 -
                        (((s32)fVar1 != 0 ? HSD_Randi(fVar1) : 0) +
                        temp_fVar1);
                    gp->gv.foursideCrane.x1.b1 = 0;
                    OSReport("pos = %f : tgrpos = %f\n",gp->gv.foursideCrane.xC,gp->gv.foursideCrane.x10);
                    gp->gv.foursideCrane.x0 = 5;
                } else {
                    fVar1 = grFs_804D69D8->crane_iron_up_max - grFs_804D69D8->crane_iron_up_min;
                    if (fVar1 < 0.0f) {
                        fVar1 = -fVar1;
                    }
                    temp_fVar1 = grFs_804D69D8->crane_iron_down_min;
                    gp->gv.foursideCrane.x10 =
                        gp->gv.foursideCrane.x10 +
                        ((s32)fVar1 != 0 ? HSD_Randi(fVar1) : 0) +
                        temp_fVar1;
                    gp->gv.foursideCrane.x1.b1 = 0;
                    OSReport("pos = %f : tgrpos = %f\n",gp->gv.foursideCrane.xC,gp->gv.foursideCrane.x10);
                    gp->gv.foursideCrane.x0 = 6;
                }
            } else {
                gp->gv.foursideCrane.x4 -= 1;
            }
            break;
        case 5:
            gp->gv.foursideCrane.xC -= grFs_804D69D8->crane_iron_spd;
            if (gp->gv.foursideCrane.xC <= gp->gv.foursideCrane.x10) {
                gp->gv.foursideCrane.xC = gp->gv.foursideCrane.x10;
                gp->gv.foursideCrane.x14 = gp->gv.foursideCrane.x18 = grFs_804D69D8->crane_iron_spd;
                gp->gv.foursideCrane.x1C = grFs_804D69D8->crane_iron_stop_acl;
                grFs_804D69D8->crane_iron_spd;
                gp->gv.foursideCrane.x0 = 7;
            }
            break;
        case 6:
            gp->gv.foursideCrane.xC += grFs_804D69D8->crane_iron_spd;
            if (gp->gv.foursideCrane.xC >= gp->gv.foursideCrane.x10) {
                gp->gv.foursideCrane.x14 = gp->gv.foursideCrane.x18 = grFs_804D69D8->crane_iron_spd;
                gp->gv.foursideCrane.x1C = grFs_804D69D8->crane_iron_stop_acl;
                grFs_804D69D8->crane_iron_spd;
                gp->gv.foursideCrane.x0 = 7;
            }
            break;
        case 7:
            temp_fVar1 = fVar1 = gp->gv.foursideCrane.x1C;
            if (fVar1 < 0.0f) {
                temp_fVar1 = -fVar1;
            }
            if (temp_fVar1 > gp->gv.foursideCrane.x14) {
                gp->gv.foursideCrane.xC = gp->gv.foursideCrane.x10;
                gp->gv.foursideCrane.x4 =
                    grFs_804D69D8->crane_wait +
                    (grFs_804D69D8->crane_wait_add != 0 ? HSD_Randi(grFs_804D69D8->crane_wait_add) : 0);
                gp->gv.foursideCrane.x0 = 0;
            } else {
                gp->gv.foursideCrane.x18 += fVar1;
                gp->gv.foursideCrane.xC += gp->gv.foursideCrane.x18;
                if ((gp->gv.foursideCrane.x1C < 0.0f) && (gp->gv.foursideCrane.xC < gp->gv.foursideCrane.x10)) {
                    gp->gv.foursideCrane.x1C *= -2.0f;
                }
                if ((gp->gv.foursideCrane.x1C > 0.0f) && (gp->gv.foursideCrane.xC > gp->gv.foursideCrane.x10)) {
                    gp->gv.foursideCrane.x1C *= -2.0f;
                }
            }
            break;
    }
    HSD_JObjSetTranslateY(crane_iron,gp->gv.foursideCrane.xC);
    Ground_801C2FE0(gobj);
}

void grFourside_801F37F8(Ground_GObj* arg) {}

/// #grFourside_801F37FC
void grFourside_801F37FC(Ground_GObj* gobj) {
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = gobj->hsd_obj;
    Ground_801C2ED0(jobj,gp->map_id);
    gp->gv.foursideCrane.x4 = grFs_804D69D8->ufo_wait;
    gp->gv.foursideUfo.x0 = 0;
    gp->gv.foursideUfo.x1 = 0xff;
    gp->gv.foursideUfo.x8 = 0;
    gp->gv.foursideUfo.x2 = 0;
    gp->gv.foursideUfo.xC = 0;
    gp->gv.foursideUfo.x3 = 0;
    HSD_JObjSetFlagsAll(jobj,16);
    mpLib_80057BC0(4);
    gp->x10_flags.b5 = 1;
}

bool grFourside_801F388C(Ground_GObj* arg)
{
    return false;
}

/// #grFourside_801F3894

void grFourside_801F3B6C(Ground_GObj* arg) {}

/// #grFourside_801F3B70
void grFourside_801F3B70(Ground_GObj* gobj) {
    Vec local18;
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = Ground_801C3FA4(gobj,1);
    CmSubject* cam;
    float fVar2;
    lb_8000B1CC(jobj,NULL,&local18);
    if(gp->gv.foursideUfo.xC != 0) {
        fVar2 = Stage_GetCamBoundsTopOffset();
        if (local18.y <= fVar2 + grFs_804D69D8->ufo_cs_offs) {
            if (gp->gv.foursideUfo.x3 == 0) {
                gp->gv.foursideUfo.x3 = 1;
            }
            cam = gp->gv.foursideUfo.xC;
            cam->x10 = local18;
            cam->x1C = local18;
            cam->x40.x = -50.0f;
            cam->x40.y = 50.0f;
            cam->x48.x = 15.0f;
            cam->x48.y = -15.0f;
        }
    }
}

void grFourside_801F3C40(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);

    gp->x11_flags.b012 = 1;
    HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
    gp->gv.fourside2.x0 = 0;
    gp->gv.fourside2.x4 =
        grFs_804D69D8->heli_wait +
        (grFs_804D69D8->heli_wait_add != 0 ? HSD_Randi(grFs_804D69D8->heli_wait_add) : 0);
    gp->gv.fourside2.x1 = 0;
}

bool grFourside_801F3CC0(Ground_GObj* arg)
{
    return false;
}

/// #grFourside_801F3CC8

void grFourside_801F3F0C(Ground_GObj* arg) {}

int grFourside_801F3F10(void)
{
    HSD_GObj* gobj = Ground_801C2BA4(3);
    Ground* gp = GET_GROUND(gobj);
    if ((gp->gv.fourside2.x0 == 1 && gp->gv.fourside2.x1 == 0) ||
        (gp->gv.fourside2.x0 == 3 && gp->gv.fourside2.x4 <= 700))
    {
        return 1;
    }
    return 0;
}

/// #fn_801F3F74

DynamicsDesc* grFourside_801F41E0(enum_t arg)
{
    return NULL;
}

bool grFourside_801F41E8(Vec3* a, int arg, HSD_JObj* joint)
{
    u8 _[4];
    Vec3 b;

    lb_8000B1CC(joint, NULL, &b);

    if (a->y > b.y) {
        return true;
    } else {
        return false;
    }
}
