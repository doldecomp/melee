#include <placeholder.h>

#include "gr/grticeclimber.h"

#include "cm/camera.h"
#include "ef/efsync.h"
#include "gr/granime.h"
#include "gr/grdisplay.h"
#include "gr/grmaterial.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "gr/types.h"
#include "it/inlines.h"
#include "it/types.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"

#include <dolphin/os/OSError.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>
#include <baselib/jobj.h>

/* static */ StageCallbacks grTIc_803E8A98[4] = {
    {
        grTIceClimber_8022109C,
        grTIceClimber_802210C8,
        grTIceClimber_802210D0,
        grTIceClimber_802210D4,
        0,
    },
    {
        grTIceClimber_8022118C,
        grTIceClimber_802211DC,
        grTIceClimber_802211E4,
        grTIceClimber_80221204,
        0,
    },
    {
        grTIceClimber_802210D8,
        grTIceClimber_8022114C,
        grTIceClimber_80221154,
        grTIceClimber_80221188,
        (1 << 30) | (1 << 31),
    },
};

StageData grTIc_803E8AF4 = {
    47,
    grTIc_803E8A98,
    "/GrTIc.dat",
    grTIceClimber_80220F14,
    grTIceClimber_80220F10,
    grTiceclimber_UnkStage0_OnLoad,
    grTiceclimber_UnkStage0_OnStart,
    grTIceClimber_80220FAC,
    grTIceClimber_80221354,
    grTIceClimber_8022135C,
    (1 << 0),
};

void grTIceClimber_80220F10(bool unused) {}

void grTIceClimber_80220F14(void)
{
    stage_info.unk8C.b4 = false;
    stage_info.unk8C.b5 = true;

    grTIceClimber_80220FB4(0);
    grTIceClimber_80220FB4(1);
    grTIceClimber_80220FB4(2);
    Ground_801C39C0();
    Ground_801C3BB4();
    Ground_801C4210();
    Ground_801C42AC();
}

void grTiceclimber_UnkStage0_OnLoad(void) {}

void grTiceclimber_UnkStage0_OnStart(void)
{
    grZakoGenerator_801CAE04(0);
}

bool grTIceClimber_80220FAC(void)
{
    return false;
}

HSD_GObj* grTIceClimber_80220FB4(int id)
{
    HSD_GObj* gobj;
    StageCallbacks* cb = &grTIc_803E8A98[id];
    gobj = Ground_801C14D0(id);

    if (gobj != NULL) {
        Ground* gp = (Ground*) HSD_GObjGetUserData(gobj);
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
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grticeclimber.c", 202,
                 id);
    }

    return gobj;
}

void grTIceClimber_8022109C(Ground_GObj* gobj)
{
    Ground* gp = (Ground*) HSD_GObjGetUserData(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grTIceClimber_802210C8(Ground_GObj* gobj)
{
    return false;
}

void grTIceClimber_802210D0(Ground_GObj* gobj) {}

void grTIceClimber_802210D4(Ground_GObj* gobj) {}

void grTIceClimber_802210D8(Ground_GObj* gobj)
{
    Ground_JObjInline1(gobj);
    grAnime_801C7FF8(gobj, 69, 2, 1, 0.0F, 1.0F);
    grTIceClimber_80221288(gobj);
}

bool grTIceClimber_8022114C(Ground_GObj* gobj)
{
    return false;
}

void grTIceClimber_80221154(Ground_GObj* gobj)
{
    lb_800115F4();
    Ground_801C2FE0(gobj);
}

void grTIceClimber_80221188(Ground_GObj* gobj) {}

void grTIceClimber_8022118C(Ground_GObj* gobj)
{
    Ground_JObjInline1(gobj);
}

bool grTIceClimber_802211DC(Ground_GObj* gobj)
{
    return false;
}

void grTIceClimber_802211E4(Ground_GObj* gobj)
{
    Ground_801C2FE0(gobj);
}

void grTIceClimber_80221204(Ground_GObj* gobj) {}

void grTIceClimber_80221208(Item_GObj* gobj, Ground* u1, Vec3* u2, HSD_GObj* u3, f32 u4)
{
    Vec3 pos;
    Item* it = GET_ITEM(gobj);

    HSD_JObjSetFlagsAll(it->xDD4_itemVar.mato.x4, 0x10);
    lb_8000B1CC(it->xDD4_itemVar.mato.x4, NULL, &pos);
    efSync_Spawn(0x445, gobj, &pos);
    Camera_80030E44(2, 0);
    Ground_801C53EC(310);
    grMaterial_801C8CDC(gobj);
}

s16 grTIc_803E8B5C[] = {
    0,  1,  2,  3,  4,  5,  6,  8,  9,  10, 11, 12, 13, 14,
    15, 16, 17, 18, 19, 20, 21, 22, 44, 45, 46, 47, 48, 49,
    50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, 0,
};

void grTIceClimber_80221288(HSD_GObj* ground_gobj)
{
    Ground* gp = GET_GROUND(ground_gobj);
    int i;

    for (i = 0; grTIc_803E8B5C[i] != -1; i++) {
        enum_t result_0 = Ground_801C33C0(2, grTIc_803E8B5C[i]);
        if (result_0 != -1) {
            Item_GObj* result_1 = grMaterial_801C8CFC(
                0, 0, gp, Ground_801C3FA4(ground_gobj, result_0), 0,
                grTIceClimber_80221208, 0);

            if (result_1 != NULL) {
                grMaterial_801C8DE0(result_1, -1.0F, 0.0F, 0.0F, 1.0F, 0.0F,
                                    0.0F, 4.0F);
                grMaterial_801C8E08(result_1);
            }
        }
    }
}

DynamicsDesc* grTIceClimber_80221354(enum_t gobj)
{
    return NULL;
}

bool grTIceClimber_8022135C(Vec3* vec, int arg1, HSD_JObj* jobj)
{
    return true;
}
