#include "grkinokoroute.h"

#include "ground.h"

#include <platform.h>

#include "cm/camera.h"
#include "ef/efsync.h"
#include "ft/ftdevice.h"
#include "ft/ftlib.h"
#include "gr/grdisplay.h"
#include "gr/grlib.h"
#include "gr/grmaterial.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "lb/lb_00B0.h"

#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>
#include <baselib/jobj.h>
#include <baselib/psstructs.h>
#include <baselib/random.h>

static struct {
    int x0;
    grZakoGenerator_SpawnDesc x4;
}* grNKr_804D6A50;

StageCallbacks grNKr_803E57F0[4] = {
    { grKinokoRoute_80207634, grKinokoRoute_802078E8, grKinokoRoute_802078F0,
      grKinokoRoute_80207A94, 0 },
    { grKinokoRoute_80207ADC, grKinokoRoute_80207B20, grKinokoRoute_80207B28,
      grKinokoRoute_80207B2C, 0 },
    { grKinokoRoute_80207A98, grKinokoRoute_80207ACC, grKinokoRoute_80207AD4,
      grKinokoRoute_80207AD8, 0 },
    { grKinokoRoute_80207B5C, grKinokoRoute_80207C80, grKinokoRoute_80207C88,
      grKinokoRoute_80208368, 0xC0000000 },
};

void grKinokoRoute_8020741C(bool arg) {}

void grKinokoRoute_80207420(void)
{
    grNKr_804D6A50 = Ground_801C49F8();
    stage_info.unk8C.b4 = 0;
    stage_info.unk8C.b5 = 1;
    grKinokoRoute_8020754C(2);
    grKinokoRoute_8020754C(0);
    grKinokoRoute_8020754C(1);
    grKinokoRoute_8020754C(3);
}

void grKinokoRoute_80207490(void)
{
    Vec3 pos;
    HSD_GObj* gobj = Ground_801C57A4();
    if (gobj != NULL) {
        ftLib_80086644(gobj, &pos);
        Ground_801C38BC(pos.x, 20.0f + pos.y);
        Camera_8002F3AC();
    }
}

void grKinokoRoute_802074D8(void)
{
    int val;
    grZakoGenerator_801CAE04(&grNKr_804D6A50->x4);
    val = grNKr_804D6A50->x0;
    if (val != 0) {
        val = HSD_Randi(grNKr_804D6A50->x0);
    } else {
        val = 0;
    }
    if (val == 0) {
        grZakoGenerator_801CAEB0(Ground_801C5840(), Ground_801C5940());
    }
    grZakoGenerator_801CADE0();
}

bool grKinokoRoute_80207544(void)
{
    return false;
}

HSD_GObj* grKinokoRoute_8020754C(int gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grNKr_803E57F0[gobj_id];

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
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", __FILE__, 249, gobj_id);
    }

    return gobj;
}

/// #grKinokoRoute_80207634

bool grKinokoRoute_802078E8(Ground_GObj* arg)
{
    return false;
}

/// #grKinokoRoute_802078F0

void grKinokoRoute_80207A94(Ground_GObj* arg) {}

void grKinokoRoute_80207A98(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138((HSD_GObj*) gobj, gp->map_id, 0);
    Ground_801C39C0();
    Ground_801C3BB4();
}

bool grKinokoRoute_80207ACC(Ground_GObj* arg)
{
    return false;
}

void grKinokoRoute_80207AD4(Ground_GObj* arg) {}

void grKinokoRoute_80207AD8(Ground_GObj* arg) {}

void grKinokoRoute_80207ADC(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->x11_flags.b012 = 2;
}

bool grKinokoRoute_80207B20(Ground_GObj* arg)
{
    return false;
}

void grKinokoRoute_80207B28(Ground_GObj* arg) {}

void grKinokoRoute_80207B2C(Ground_GObj* arg) {}

void grKinokoRoute_80207B30(HSD_GObj* gobj)
{
    ftCo_800C07F8(gobj, 6, grKinokoRoute_80208660);
}

/// #grKinokoRoute_80207B5C

bool grKinokoRoute_80207C80(Ground_GObj* arg)
{
    return false;
}

/// #grKinokoRoute_80207C88

void grKinokoRoute_80208368(Ground_GObj* arg) {}

/// #grKinokoRoute_8020836C

bool grKinokoRoute_80208480(bool arg)
{
    if (arg == 1) {
        Ground_801C5740(arg);
        return 1;
    }
    return 0;
}

void grKinokoRoute_802084B4(HSD_GObj* gobj)
{
    HSD_GObj* gobj2;
    Vec3 sp_vec;
    struct {
        char pad[0xDD8];
        HSD_JObj* jobj;
    }* gp = gobj->user_data;

    HSD_JObjSetFlagsAll(gp->jobj, 0x10);

    gobj2 = Ground_801C2BA4(3);
    if (gobj2 != NULL) {
        void* gp2 = gobj2->user_data;
        if (gp2 != NULL) {
            ((UnkFlagStruct*) ((u8*) gp2 + 0xC4))->b0 = 1;
        }
    }

    lb_8000B1CC(gp->jobj, NULL, &sp_vec);
    efSync_Spawn(0x442, gobj, &sp_vec);
    Camera_80030E44(2, NULL);
    Ground_801C5414(0x136, 0xBA);
    grMaterial_801C8CDC(gobj);
    PAD_STACK(20);
}

void grKinokoRoute_80208564(HSD_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    u32 i;
    s16 depths[] = {
        1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 17,
        18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34,
        35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51,
    };

    for (i = 0; i < 0x33U; i++) {
        HSD_JObj* jobj = Ground_801C3FA4(gobj, depths[i]);
        Item_GObj* item = grMaterial_801C8CFC(
            8, 0, gp, jobj, NULL,
            (void (*)(Item_GObj*, Ground*, Vec3*, HSD_GObj*,
                      f32)) grKinokoRoute_802084B4,
            NULL);
        if (item != NULL) {
            grMaterial_801C8DE0(item, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F,
                                7.0F);
            grMaterial_801C8E08(item);
            grMaterial_801C8E68(item, GA_Ground);
        }
    }
}

bool grKinokoRoute_80208660(s32 arg0, HSD_GObj* gobj)
{
    Vec3 pos;
    Vec3 vel;

    ftLib_80086644(gobj, &pos);
    ftLib_80086684(gobj, &vel);

    if (pos.y < 5.5F && vel.y > 5.5F) {
        f32 scale = ftLib_80086B80(gobj) / 10.0F;
        pos.y = 5.5F;
        grKinokoRoute_802086EC(&pos, scale);
        Ground_801C53EC(0x77A10);
    }

    PAD_STACK(8);
    return false;
}

void grKinokoRoute_802086EC(Vec3* arg0, f32 arg8)
{
    HSD_Generator* gen = grLib_801C96F8(0x7530, 0x1E, arg0);
    if (gen != NULL) {
        HSD_psAppSRT* srt = gen->appsrt;
        srt->scale.x *= arg8;
        srt->scale.y *= arg8;
        srt->scale.z *= arg8;
    }
}

DynamicsDesc* grKinokoRoute_80208754(enum_t arg)
{
    return false;
}

bool grKinokoRoute_8020875C(Vec3* a, int b, HSD_JObj* jobj)
{
    Vec3 vec;
    lb_8000B1CC(jobj, NULL, &vec);
    if (a->y > vec.y) {
        return true;
    } else {
        return false;
    }
}
